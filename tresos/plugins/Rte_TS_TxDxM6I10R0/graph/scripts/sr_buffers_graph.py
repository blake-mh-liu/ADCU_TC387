"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows all S/R connections between senders and receivers and their related buffers. Each cluster/diagram shows one connection where a connection is defined as
    a group of RVariableDataInstances (instances of a require variable data prototypes) that have the same data source (same PVariableDataInstances and
    same receive signals/signal groups) or all PVariableDataInstances (instances of a provide variable data prototypes) if they don't have any receivers.
    The diagram includes the affected sender and receiver runnables and their context in which they are running as well as the S/R APIs, callbacks and signals.
    It shows the data flow from the sender runnables to the implicit or global buffers and back to the connected receivers.
    Please note that some feature are not supported or not correctly shown in this diagram. For examples transformers or receivers
    that need to identify the sender by a sender id.

    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand how the Rte allocates the implicit and global buffers. It shows the relevant information to make a 
    decision how many buffers are needed and if buffer sharing is possible between implicit and explicit senders/receivers.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""


from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict
READ = 1
WRITE = 2
SIGNAL = 1
SIGNAL_GROUP = 2

__no_names = True
__vdi_to_runnables = None
__signal_to_callback = OrderedDict()
__signal_group_to_callback = OrderedDict()

__runnable_to_task_mapping = OrderedDict()


def __add_vdi(graph_generator, cluster, vdi):
    # create vdi node
    swc = vdi.getparent().getparent().getparent().getparent()
    partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, swc.getparent().getparent())
    swc_cluster = __add_or_get_swc_cluster(
        graph_generator, partition_cluster, swc)
    attributes = (vdi.tag if __no_names else "{{id}}")
    if vdi.findtext("statusRequired") == 'true':
        attributes += "\n- status is required"
    port = vdi.getparent().getparent()
    is_pr_port = port.findtext("PRPort") == 'true'
    port_cluster = graph_generator.get_or_create_cluster(swc.findtext("name")+"."+port.findtext(
        "name"), port.findtext("name")+(" (PR port)" if is_pr_port else ""), color="dimgrey", parent_cluster=swc_cluster)
    return graph_generator.get_or_create_node(port_cluster, vdi, attributes, style=VDI_STYLE)


def __add_dhv(graph_generator, cluster, dhv):
    struct_type = graph_generator.find_and_resolve_reference(dhv, "dataTypeRef")
    dhb_struct_type = graph_generator.find_and_resolve_reference(
        struct_type, "lastTypeOfTypeReferenceChain")
    members = dhb_struct_type.findall("elements/*/name")
    member_names = ', '.join([member.text for member in members])
    # create dhb node
    partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, graph_generator.find_and_resolve_reference(dhv, "writerPartitionRef"))
    buffer_cluster = __add_or_get_partition_buffer_cluster(
        graph_generator, partition_cluster)
    dhb = graph_generator.get_or_create_node(buffer_cluster, dhv,
                                            ("DataHandleBuffer" if __no_names else "{{name}}")+"""
(""" + member_names+")", style=DHB_BUFFER_STYLE)


def __add_or_get_swc_cluster(graph_generator, cluster, swc):
    name = swc.findtext("name")
    return graph_generator.get_or_create_cluster(name, name, color="darkgray", parent_cluster=cluster, url="../swc_graph/"+name+"_connections.gv.svg")


def __add_or_get_partition_buffer_cluster(graph_generator, cluster):
    return graph_generator.get_or_create_cluster("Buffers", "Buffers", color="darkgray", parent_cluster=cluster)


def __add_or_get_partition_node(graph_generator, cluster, partition):
    name = partition.findtext("name")
    core_id = partition.findtext("coreId")
    return graph_generator.get_or_create_cluster(name, "" if not name else (("Partition" if __no_names else name[1:])+"(core:"+core_id+")"), color="lightgrey", parent_cluster=cluster)


def __add_runnable_and_apis(graph_generator, cluster, root, runnable, vdi, direction, receive_buffers=[], ip_channels=[]):
    runnable_id = runnable.get("id")
    swc = runnable.getparent().getparent()
    partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, swc.getparent().getparent())
    swc_cluster = __add_or_get_swc_cluster(
        graph_generator, partition_cluster, swc)
    for api in graph_generator.find_and_resolve_references(runnable, "apis/apiRef"):
        api_name = api.tag
        runnable_vdi = graph_generator.find_and_resolve_reference(
            api, "variableDataInstanceRef")
        if vdi == runnable_vdi and api_name != "iWriteRefAPIFunction" and api_name != "iReadRefAPIFunction":
            # ignore ref APIs since they always come with the iWrite/iRead API and only make the diagram bigger

            # create runnable node
            runnable_node = graph_generator.get_or_create_node(swc_cluster, runnable,
                                                             ("Runnable" if __no_names else "{{name}}"),
                                                             style=EXECUTABLE_STYLE, url="../executable_context_graph/"+runnable.findtext("entryPoint")+".gv.svg")
            # create API node
            api_attributes = api_name if __no_names else "{{externalName}}"
            if api_name == "iWriteAPIFunction" or api_name == "iReadAPIFunction":
                api_attributes += "\nstatus type: {{dataHandleTypeReq}}"
                if api.findtext("isMappedToTaskWithSubsequentSchedulePoint") == "true":
                    api_attributes += "\nisMappedToTaskWithSubsequentSchedulePoint"
            api_node = graph_generator.get_or_create_node(
                swc_cluster, api, api_attributes, style=API_STYLE)
            vdi_node = graph_generator.get_node_from_any_subcluster(cluster, vdi)
            dhb = graph_generator.find_and_resolve_reference(
                api, "dataHandleVariableRef")
            if dhb is not None:
                dhb_node = graph_generator.get_node_from_any_subcluster(
                    cluster, dhb)
                # connect API to DHB node
                if direction == READ:
                    graph_generator.connect(dhb_node, api_node, cluster)
                    if api.findtext("copyFromReceiveBufferOrIPChannelOrParameterBufferRequired") == "true":
                        # copy is required, connect RB/IPChannel with DHB
                        if receive_buffers:
                            rb_node = graph_generator.get_node_from_any_subcluster(
                                cluster, receive_buffers[0])
                            graph_generator.connect(
                                rb_node, dhb_node, cluster, "update before runnable")
                        if ip_channels:
                            channel_node = graph_generator.get_node(
                                cluster, ip_channels[0])
                            graph_generator.connect(
                                channel_node, dhb_node, cluster, "update before runnable")
                else:
                    graph_generator.connect(api_node, dhb_node, cluster)
                    for rb in receive_buffers:
                        rb_node = graph_generator.get_node_from_any_subcluster(
                            cluster, rb)
                        graph_generator.connect(
                            dhb_node, rb_node, cluster, "update after runnable")
                    for channel in ip_channels:
                        channel_node = graph_generator.get_node(cluster, channel)
                        graph_generator.connect(
                            dhb_node, channel_node, cluster, "update after runnable")
            for dhb in graph_generator.find_and_resolve_references(api, "dataHandleVariableRefs/dataHandleVariableRef"):
                # find DHBs for IWrites
                dhb_node = graph_generator.get_node_from_any_subcluster(
                    cluster, dhb)
                if dhb_node is not None:  # might be None in case a pvdi writes to a DHB of another RVDI that doesn't have the same data source with the RVDI that is shown in the diagram
                    # connect API to DHB node
                    graph_generator.connect(api_node, dhb_node, cluster)
            if direction == READ:
                # connect API to runnable
                graph_generator.connect(
                    api_node, runnable_node, cluster, direction="back", style="dotted")
                # connect rvdi to API node
                graph_generator.connect(
                    vdi_node, api_node, cluster, arrowhead="none", style="dashed")
            if direction == WRITE:
                # connect runnable to API
                graph_generator.connect(
                    runnable_node, api_node, cluster, style="dotted")
                # connect API to pvdi node
                graph_generator.connect(
                    api_node, vdi_node, cluster, arrowhead="none", style="dashed")
            if api_name in ["readAPIFunction", "dReadAPIFunction", "writeAPIFunction", "sendAPIFunction", "receiveNonBlockingAPIFunction", "receiveBlockingAPIFunction"]:
                # only connect explicit APIs to receive buffer / channels (no implicit and no other APIs like IsUpdated)
                for rb in receive_buffers:
                    rb_node = graph_generator.get_node_from_any_subcluster(
                        cluster, rb)
                    if direction == READ:
                        graph_generator.connect(rb_node, api_node, cluster)
                    else:
                        graph_generator.connect(api_node, rb_node, cluster)
                for channel in ip_channels:
                    channel_node = graph_generator.get_node(cluster, channel)
                    if direction == READ:
                        graph_generator.connect(channel_node, api_node, cluster)
                    else:
                        graph_generator.connect(api_node, channel_node, cluster)


def __add_receive_buffer(graph_generator, cluster, rb, rvdi_node):
    partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, rb.getparent().getparent())
    buffer_cluster = __add_or_get_partition_buffer_cluster(
        graph_generator, partition_cluster)
    rb_node = graph_generator.get_or_create_node(
        buffer_cluster, rb, "ReceiveBuffer" if __no_names else "{{name}}", style=RB_BUFFER_STYLE)


def __add_send_signal(graph_generator, cluster, signal, pvdi, is_intra_partition, signal_type):
    if signal_type == SIGNAL_GROUP:
        # convert signal group mapping to signal group
        signal = signal.getparent().getparent()
    signal_partition = signal.getparent().getparent()
    signal_partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, signal_partition)
    signal_node = graph_generator.get_or_create_node(signal_partition_cluster, signal, ("Signal" if signal_type == SIGNAL else "Signal_Group")
                                                   if __no_names else "{{name}}", style=SIGNAL_STYLE if signal_type == SIGNAL else SIGNAL_GROUP_STYLE)
    if is_intra_partition:
        send_write_api = graph_generator.find_and_resolve_reference(
            pvdi, "sendWriteAPIRef")
        if send_write_api is not None:
            send_write_api_node = graph_generator.get_node_from_any_subcluster(
                cluster, send_write_api)
            if send_write_api_node is not None:
                graph_generator.connect(
                    send_write_api_node, signal_node, signal_partition_cluster)
        for dhb in graph_generator.find_and_resolve_references(pvdi, "dataHandleVariableRefs/dataHandleVariableRef"):
            dhb_node = graph_generator.get_node_from_any_subcluster(cluster, dhb)
            if dhb_node is not None:
                graph_generator.connect(
                    dhb_node, signal_node, signal_partition_cluster)
    else:
        for channel in graph_generator.find_and_resolve_references(pvdi, "mappedIpChannelRefs/mappedIpChannelRef"):
            channel_node = graph_generator.get_node_from_any_subcluster(
                cluster, channel)
            if channel_node is not None:
                if signal_type == SIGNAL:
                    for send_signal in graph_generator.find_and_resolve_references(channel, "sendSignals/sendSignalRef"):
                        if send_signal == signal:
                            graph_generator.connect(
                                channel_node, signal_node, cluster)
                else:
                    for send_signal_group_mapping in graph_generator.find_and_resolve_references(channel, "sendSignalGroupMappings/sendSignalGroupMappingRef"):
                        if send_signal_group_mapping.getparent().getparent() == signal:
                            graph_generator.connect(
                                channel_node, signal_node, cluster)


def __add_receive_signal(graph_generator, cluster, signal, rvdi, is_intra_partition, signal_type):
    if signal_type == SIGNAL_GROUP:
        # convert signal group mapping to signal group
        signal = signal.getparent().getparent()
    signal_partition = signal.getparent().getparent()
    signal_partition_cluster = __add_or_get_partition_node(
        graph_generator, cluster, signal_partition)
    signal_node = graph_generator.get_or_create_node(signal_partition_cluster, signal, ("Signal" if signal_type == SIGNAL else "Signal_Group")
                                                   if __no_names else "{{name}}", style=SIGNAL_STYLE if signal_type == SIGNAL else SIGNAL_GROUP_STYLE)
    callback = (__signal_to_callback if signal_type ==
                SIGNAL else __signal_group_to_callback).get(signal.get("id"))
    if callback is not None:
        callback_node = graph_generator.get_or_create_node(
            signal_partition_cluster, callback, "Reception callback " if __no_names else "{{id}}", style=CALLBACK_STYLE)
        graph_generator.connect(signal_node, callback_node, cluster)
        if is_intra_partition:
            rb = graph_generator.find_and_resolve_reference(
                rvdi, "receiveBufferRef")
            if rb is not None:
                rb_node = graph_generator.get_node_from_any_subcluster(
                    signal_partition_cluster, rb)
                if rb_node is not None:
                    graph_generator.connect(
                        callback_node, rb_node, signal_partition_cluster)
        else:
            channel = graph_generator.find_and_resolve_reference(
                rvdi, "mappedIpChannelRef")
            if channel is not None:
                channel_node = graph_generator.get_node_from_any_subcluster(
                    cluster, channel)
                if channel_node is not None:
                    graph_generator.connect(callback_node, channel_node, cluster)
    elif rvdi.findtext("directlyReadFromCom") == "true":
        read_api = graph_generator.find_and_resolve_reference(
            rvdi, "readReceiveAPIRef")
        if read_api is not None:
            read_api_node = graph_generator.get_node_from_any_subcluster(
                cluster, read_api)
            if read_api_node is not None:
                graph_generator.connect(signal_node, read_api_node, cluster)


def __add_ip_channel(graph_generator, cluster, ip_channel):
    channel_node = graph_generator.get_or_create_node(
        cluster, ip_channel, "IpChannel" if __no_names else "{{name}}", style=IP_CHANNEL_STYLE, url="../ip_channel_data_consistency_graph/"+ip_channel.findtext("name")+".gv.svg")
    return channel_node


def __add_rvdi_with_children(graph_generator, cluster, root, rvdi_group):
    for rvdi in rvdi_group:
        for dhv in graph_generator.find_and_resolve_references(rvdi, "dataHandleVariableRefs/dataHandleVariableRef"):
            # create dhbs of rvdi
            __add_dhv(graph_generator, cluster, dhv)
        # create rvdi node
        rvdi_node = __add_vdi(graph_generator, cluster, rvdi)
        rb = graph_generator.find_and_resolve_reference(
            rvdi, "receiveBufferRef")
        if rb is not None:
            rb_node = __add_receive_buffer(
                graph_generator, cluster, rb, rvdi_node)
        ip_channel = graph_generator.find_and_resolve_reference(
            rvdi, "mappedIpChannelRef")
        if ip_channel is not None:
            channel_node = __add_ip_channel(graph_generator, cluster, ip_channel)
        for runnable in __vdi_to_runnables.get(rvdi, dict()).keys():
            # create runnable with API nodes
            __add_runnable_and_apis(graph_generator, cluster, root, runnable, rvdi, READ, [
                                    rb] if rb is not None else [], [ip_channel] if ip_channel is not None else [])
        for signal in graph_generator.find_and_resolve_references(rvdi, "intraPartitionReceiveSignals/receiveSignalRef"):
            __add_receive_signal(graph_generator, cluster,
                                 signal, rvdi, True, SIGNAL)
        for signal in graph_generator.find_and_resolve_references(rvdi, "interPartitionReceiveSignals/receiveSignalRef"):
            __add_receive_signal(graph_generator, cluster,
                                 signal, rvdi, False, SIGNAL)
        for signal_group in graph_generator.find_and_resolve_references(rvdi, "intraPartitionReceiveSignalGroupMappings/receiveSignalGroupMappingRef"):
            __add_receive_signal(graph_generator, cluster,
                                 signal_group, rvdi, True, SIGNAL_GROUP)
        for signal_group in graph_generator.find_and_resolve_references(rvdi, "interPartitionReceiveSignalGroupMappings/receiveSignalGroupMappingRef"):
            __add_receive_signal(graph_generator, cluster,
                                 signal_group, rvdi, False, SIGNAL_GROUP)


def __add_pvdi_with_children(graph_generator, cluster, root, pvdi, rvdi_group):
    # create pvdi
    pvdi_node = __add_vdi(graph_generator, cluster, pvdi)
    # connect pvdi to rvdis
    for rvdi in graph_generator.find_and_resolve_references(pvdi, "connectedVariableDataInstances/variableDataInstanceRef"):
        if rvdi in rvdi_group:
            rvdi_node = graph_generator.get_node_from_any_subcluster(
                cluster, rvdi)
            graph_generator.connect(pvdi_node, rvdi_node, cluster, style="dashed")
    # create ip channel of pvdi
    channels = []
    for ip_channel in graph_generator.find_and_resolve_references(pvdi, "mappedIpChannelRefs/mappedIpChannelRef"):
        # do not show ip channels from provider if they are not related to the shown rvdis and if they have no signal references
        # alternative: in addition to diagrams for all rvdis, we would also need diagrams for all receive signals/signal groups
        dest_rvdis = graph_generator.find_and_resolve_references(
            ip_channel, "destRVariableDataInstances/rVariableDataInstanceRef")
        if set(rvdi_group).intersection(dest_rvdis) or graph_generator.find_and_resolve_references(ip_channel, "sendSignals/sendSignalRef") or graph_generator.find_and_resolve_references(ip_channel, "sendSignalGroupMappings/sendSignalGroupMappingRef"):
            __add_ip_channel(graph_generator, cluster, ip_channel)
            channels.append(ip_channel)
    # create dhbs of pvdi
    receive_buffers = []
    for rvdi in rvdi_group:
        rb = graph_generator.find_and_resolve_reference(
            rvdi, "receiveBufferRef")
        if rb is not None and rb not in receive_buffers:
            receive_buffers.append(rb)
    for dhb in graph_generator.find_and_resolve_references(pvdi, "dataHandleVariableRefs/dataHandleVariableRef"):
        __add_dhv(graph_generator, cluster, dhb)
        dhb_node = graph_generator.get_node(cluster, dhb)

    # runnables of pvdi
    for runnable in __vdi_to_runnables.get(pvdi, dict()).keys():
        __add_runnable_and_apis(
            graph_generator, cluster, root, runnable, pvdi, WRITE, receive_buffers, channels)

    for signal_group_mapping in graph_generator.find_and_resolve_references(pvdi, "interPartitionSendSignalGroupMappings/sendSignalGroupMappingRef"):
        __add_send_signal(graph_generator, cluster,
                          signal_group_mapping, pvdi, False, SIGNAL_GROUP)
    for signal_group_mapping in graph_generator.find_and_resolve_references(pvdi, "intraPartitionSendSignalGroupMappings/sendSignalGroupMappingRef"):
        __add_send_signal(graph_generator, cluster,
                          signal_group_mapping, pvdi, True, SIGNAL_GROUP)
    for signal in graph_generator.find_and_resolve_references(pvdi, "interPartitionSendSignals/sendSignalRef"):
        __add_send_signal(graph_generator, cluster, signal, pvdi, False, SIGNAL)
    for signal in graph_generator.find_and_resolve_references(pvdi, "intraPartitionSendSignals/sendSignalRef"):
        __add_send_signal(graph_generator, cluster, signal, pvdi, True, SIGNAL)


def find_related_rvdis_all(graph_generator, rvdi, rvdi_group):
    if rvdi not in rvdi_group:
        rvdi_group[rvdi] = None
        for pvdi in graph_generator.find_and_resolve_references(rvdi, "connectedVariableDataInstances/variableDataInstanceRef"):
            for rvdi_of_pvdi in graph_generator.find_and_resolve_references(pvdi, "connectedVariableDataInstances/variableDataInstanceRef"):
                find_related_rvdis_all(graph_generator, rvdi_of_pvdi, rvdi_group)


def find_related_rvdis_common_data_source(graph_generator, rvdi, rvdi_group, data_source_to_rvdis):
    data_source = rvdi.findtext("dataSource/uniqueIdentifier")
    if data_source:
        rvdi_group.update(OrderedDict.fromkeys(data_source_to_rvdis[data_source]))
    else:
        rvdi_group[rvdi] = None


def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Data Handle Buffers")
    root = graph_generator.get_model_root()
    global __no_names
    __no_names = graph_generator.get_args().noNames

    # build map of callbacks to signal/signal groups
    global __signal_group_to_callback
    for signal_group_reception_callback in root.findall("partitions/*/callbacks/signalGroupReceptionCallback"):
        __signal_group_to_callback[signal_group_reception_callback.findtext(
            "receiveSignalGroupRef")] = signal_group_reception_callback

    global __signal_to_callback
    for signal_reception_callback in root.findall("partitions/*/callbacks/signalReceptionCallback"):
        __signal_to_callback[signal_reception_callback.findtext(
            "receiveSignalRef")] = signal_reception_callback

    # build map of vdi to runnables for fast access
    runnables = root.findall("partitions/*/softwareComponents/*/runnables/*")
    global __vdi_to_runnables
    __vdi_to_runnables = OrderedDict()
    for runnable in runnables:
        for api in graph_generator.find_and_resolve_references(runnable, "apis/apiRef"):
            vdi = graph_generator.find_and_resolve_reference(
                api, "variableDataInstanceRef")
            if vdi not in __vdi_to_runnables.keys():
                # use ordered dict instead of set to preserver insertion order
                __vdi_to_runnables[vdi] = OrderedDict()
            __vdi_to_runnables[vdi][runnable] = None

    # build map of runnables to tasks
    for task_event_mapping in root.findall("events/*/taskEventMappings/taskEventMapping"):
        executable = graph_generator.find_and_resolve_reference(
            task_event_mapping, "executableRef")
        for task in graph_generator.find_and_resolve_references(task_event_mapping, "../../tasks/taskRef"):
            __runnable_to_task_mapping.setdefault(executable, []).append(task)

    # find rvdis with common data source
    data_source_to_rvdis = OrderedDict()
    rvdis = OrderedDict.fromkeys(root.findall(
        "partitions/*/softwareComponents/*/requirePorts/*/variableDataInstances/*"))
    for rvdi in rvdis.keys():
        data_source_to_rvdis.setdefault(rvdi.findtext(
            "dataSource/uniqueIdentifier"), []).append(rvdi)
    while rvdis:
        rvdi_group = OrderedDict()
        rvdi = next(iter(rvdis))
        # either
        # find_related_rvdis_all(graph_generator, rvdi, rvdi_group)
        # or
        find_related_rvdis_common_data_source(
            graph_generator, rvdi, rvdi_group, data_source_to_rvdis)
        rvdi_group = list(rvdi_group.keys())
        for rvdi_to_delete in rvdi_group:
            rvdis.pop(rvdi_to_delete, None)

        cluster_name = "\n".join(r.get("id") for r in rvdi_group)

        # put each connection scenario in a new box
        if select and cluster_name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(
            rvdi.get("id"), cluster_name)
        if not list_only:
            __add_rvdi_with_children(graph_generator, cluster, root, rvdi_group)
            pvdi_group = list()
            for rvdi in rvdi_group:
                for incompatible_rvdi in graph_generator.find_and_resolve_references(rvdi, "notCompatibleRVariableDataInstances/rVariableDataInstanceRef"):
                    rvdi_node = graph_generator.get_node_from_any_subcluster(
                        cluster, rvdi)
                    incompatible_rvdi_node = graph_generator.get_node_from_any_subcluster(
                        cluster, incompatible_rvdi)
                    if incompatible_rvdi_node is not None:  # shouldn't be None
                        graph_generator.connect(rvdi_node, incompatible_rvdi_node, cluster,
                                            label="incompatible", color="red", arrowhead="none", undirected=True, constraint="false")
                # do two iterations (first rvdis and children, then connected pvids) otherwise it might happend that e.g. a DHB is not yet available that is referenced by a pvdi
                for pvdi in graph_generator.find_and_resolve_references(rvdi, "connectedVariableDataInstances/variableDataInstanceRef"):
                    if pvdi not in pvdi_group:
                        pvdi_group.append(pvdi)
                        __add_pvdi_with_children(
                            graph_generator, cluster, root, pvdi, rvdi_group)

    pvdis = root.findall(
        "partitions/*/softwareComponents/*/providePorts/*/variableDataInstances/*")
    for pvdi in pvdis:
        if not graph_generator.find_and_resolve_references(pvdi, "connectedVariableDataInstances/variableDataInstanceRef"):
            cluster_name = pvdi.get("id")
            if select and cluster_name != select:
                continue
            cluster = graph_generator.get_or_create_cluster(
                cluster_name, cluster_name)
            if list_only:
                continue
            __add_pvdi_with_children(graph_generator, cluster, root, pvdi, [])
