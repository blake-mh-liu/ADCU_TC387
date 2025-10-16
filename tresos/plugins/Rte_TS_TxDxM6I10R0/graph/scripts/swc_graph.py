"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows events, runnables and APIs of the software components and their connection to other software components via ports and data/operation/trigger/mode instances.

    What is the purpose of the diagram?
    With the help of the diagram, it is possible to get an overview about the Rte relevant insights of a software component as well as the connected ports and port elements.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""

from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict
from collections import namedtuple
from abc import ABC, abstractmethod

# create connected ports/data instances


class PortConnectionQuery():
    def __init__(self, find_data_instances_of_port, find_connected_data_instances_of_p_port, find_connected_data_instances_of_r_port, check_for_require_side, target_element_of_api, style, find_signals_of_data_instance_of_p_port=[], find_signals_of_data_instance_of_r_port=[],  not_allowed_type_for_data_instance=[], find_signal_mappings_of_data_instance_of_p_port=[], find_signal_mappings_of_data_instance_of_r_port=[]):
        self.find_data_instances_of_port = find_data_instances_of_port
        self.find_connected_data_instances_of_p_port = find_connected_data_instances_of_p_port
        self.find_connected_data_instances_of_r_port = find_connected_data_instances_of_r_port
        self.check_for_require_side = check_for_require_side
        self.target_element_of_api = target_element_of_api
        self.not_allowed_type_for_data_instance = not_allowed_type_for_data_instance
        self.find_signals_of_data_instance_of_p_port = find_signals_of_data_instance_of_p_port
        self.find_signals_of_data_instance_of_r_port = find_signals_of_data_instance_of_r_port
        self.find_signal_mappings_of_data_instance_of_p_port = find_signal_mappings_of_data_instance_of_p_port
        self.find_signal_mappings_of_data_instance_of_r_port = find_signal_mappings_of_data_instance_of_r_port
        self.style = style


port_connection_queries = [
    PortConnectionQuery(find_data_instances_of_port="variableDataInstances/*",
                        find_connected_data_instances_of_p_port=[
                            "connectedVariableDataInstances/variableDataInstanceRef"],
                        find_connected_data_instances_of_r_port=[
                            "connectedVariableDataInstances/variableDataInstanceRef"],
                        check_for_require_side="rVariableDataInstance",
                        target_element_of_api="variableDataInstanceRef",
                        find_signals_of_data_instance_of_r_port=[
                            "interPartitionReceiveSignals/receiveSignalRef", "intraPartitionReceiveSignals/receiveSignalRef"],
                        find_signals_of_data_instance_of_p_port=[
                            "interPartitionSendSignals/sendSignalRef", "intraPartitionSendSignals/sendSignalRef"],
                        find_signal_mappings_of_data_instance_of_r_port=[
                            "interPartitionReceiveSignalGroupMappings/receiveSignalGroupMappingRef", "intraPartitionReceiveSignalGroupMappings/receiveSignalGroupMappingRef"],
                        find_signal_mappings_of_data_instance_of_p_port=[
                            "interPartitionSendSignalGroupMappings/sendSignalGroupMappingRef", "intraPartitionSendSignalGroupMappings/sendSignalGroupMappingRef"],
                        style=VDI_STYLE),
    PortConnectionQuery(find_data_instances_of_port="operationInstances/*",
                        find_connected_data_instances_of_p_port=[
                            "intraPartition/operationInstanceRef", "interPartition/operationInstanceRef"],
                        find_connected_data_instances_of_r_port=[
                            "intraPartitionPOperationInstanceRef", "interPartitionPOperationInstanceRef"],
                        check_for_require_side="rOperationInstance",
                        target_element_of_api="operationInstanceRef",
                        style=OI_STYLE),
    PortConnectionQuery(find_data_instances_of_port="modeDeclarationGroupInstances/*",
                        find_connected_data_instances_of_p_port=[
                            "intraPartition/rModeDeclarationGroupInstanceRef", "intraPartition/rModeDeclarationGroupInstanceRef"],
                        find_connected_data_instances_of_r_port=[
                            "intraPartitionPModeDeclarationGroupInstanceRef", "interPartitionPModeDeclarationGroupInstanceRef"],
                        check_for_require_side="swcRModeDeclarationGroupInstance",
                        target_element_of_api="modeDeclarationGroupInstanceRef",
                        style=MODE_DECLARATION_GROUP_INSTANCE_STYLE),
    PortConnectionQuery(find_data_instances_of_port="parameterDataInstances/*",
                        find_connected_data_instances_of_p_port=[
                            "intraPartition/rParameterDataInstanceRef"],
                        find_connected_data_instances_of_r_port=[
                            "intraPartitionPParameterDataInstanceRef"],
                        check_for_require_side="rParameterDataInstance",
                        target_element_of_api="parameterDataInstanceRef",
                        not_allowed_type_for_data_instance=[
                            "localParameterDataInstance"],
                        style=PARAMETER_INSTANCE_STYLE),
    PortConnectionQuery(find_data_instances_of_port="triggerInstances/*",
                        find_connected_data_instances_of_p_port=[
                            "intraPartition/rTriggerRef", "interPartition/rTriggerRef"],
                        find_connected_data_instances_of_r_port=[
                            "releasedTriggerRef"],
                        check_for_require_side="swcExternalRTrigger",
                        target_element_of_api="pTriggerRef",
                        not_allowed_type_for_data_instance=["internalTriggerPoint"],
                        style=TRIGGER_INSTANCE_STYLE)]


def add_event(graph_generator, swc_cluster, ib_cluster, event, runnable_node):
    event_names = []
    for event_name in event.findall("taskEventMappings/taskEventMapping/eventName"):
        event_names.append(event_name.text)

    data_instances = []
    attributes = ""
    event_cluster = ib_cluster
    if event.tag == "timingEventInstance":
        attributes = "offset: {{offsetNanos}}\nperiod: {{periodNanos}}"
    elif event.tag == "dataReceivedEventInstance" or event.tag == "dataReceiveErrorEventInstance":
        data_instances = graph_generator.find_and_resolve_references(
            event, "rVariableDataInstances/rVariableDataInstanceRef")
    elif event.tag == "dataSendCompletedEventInstance" or event.tag == "dataWriteCompletedEventInstance":
        data_instances = [graph_generator.find_and_resolve_reference(
            event, "pVariableDataInstanceRef")]
    elif event.tag == "operationInvokedEventInstance":
        data_instances = graph_generator.find_and_resolve_references(
            event, "pOperationInstances/pOperationInstanceRef")
    elif event.tag == "asynchronousServerCallReturnsEventInstance":
        client = graph_generator.find_and_resolve_reference(event, "clientRef")
        if client is not None:
            roi = graph_generator.find_and_resolve_reference(
                client, "rOperationInstanceRef")
            if roi is not None:
                data_instances = [roi]
    elif event.tag == "modeSwitchEventInstance":
        mse_group_instance = event.getparent().getparent().getparent().getparent()
        mse_group_cluster = graph_generator.get_or_create_cluster(mse_group_instance.get(
            "id"), "Mode Switch Group", parent_cluster=ib_cluster, color="dimgrey")
        parent = event.getparent().getparent()
        if parent.tag == "onEntryInstance":
            event_cluster = graph_generator.get_or_create_cluster(
                mse_group_cluster.id+"onEntry", "on entry", parent_cluster=mse_group_cluster, color="grey")
            attributes = "mode: " + \
                graph_generator.find_and_resolve_reference(
                    parent, "modeDeclarationRef").findtext("name")
        if parent.tag == "onExitInstance":
            event_cluster = graph_generator.get_or_create_cluster(
                mse_group_cluster.id+"onExit", "on exit", parent_cluster=mse_group_cluster, color="grey")
            attributes = "mode: " + \
                graph_generator.find_and_resolve_reference(
                    parent, "modeDeclarationRef").findtext("name")
        if parent.tag == "onTransitionInstance":
            event_cluster = graph_generator.get_or_create_cluster(
                mse_group_cluster.id+"onTransition", "on transition", parent_cluster=mse_group_cluster, color="grey")
            attributes = "modes: " + graph_generator.find_and_resolve_reference(parent, "modeDeclarationFromRef").findtext(
                "name") + " ➔ " + graph_generator.find_and_resolve_reference(parent, "modeDeclarationToRef").findtext("name")
        p_mode_decl_group_instance = graph_generator.find_and_resolve_reference(
            event.getparent().getparent().getparent().getparent(), "modeDeclarationGroupInstanceRef")
        if p_mode_decl_group_instance is not None:
            data_instances.extend(graph_generator.find_and_resolve_references(
                p_mode_decl_group_instance, "intraPartition/rModeDeclarationGroupInstanceRef"))
            data_instances.extend(graph_generator.find_and_resolve_references(
                p_mode_decl_group_instance, "interPartition/rModeDeclarationGroupInstanceRef"))
    elif event.tag == "externalTriggerOccurredEventInstance":
        p_trigger = graph_generator.find_and_resolve_reference(
            event, "pTriggerRef")
        if p_trigger is not None:
            data_instances.extend(graph_generator.find_and_resolve_references(
                p_trigger, "intraPartition/rTriggerRef"))
            data_instances.extend(graph_generator.find_and_resolve_references(
                p_trigger, "interPartition/rTriggerRef"))

    event_node = graph_generator.get_or_create_node(
        event_cluster, event, event.tag+"\n"+attributes, style=EVENT_STYLE)
    for data_instance in data_instances:
        data_instance_node = graph_generator.get_node_from_any_subcluster(
            swc_cluster, data_instance)
        if data_instance_node is not None:
            graph_generator.connect(
                data_instance_node, event_node, swc_cluster, color="darkblue")
    graph_generator.connect(event_node, runnable_node, ib_cluster)


def add_data_instance(graph_generator, data_instance, is_require_instance, swc_cluster, ib_cluster, provide_ports_cluster, require_ports_cluster, pr_ports_cluster, api_node, runnable_node):
    if data_instance is not None:
        if is_require_instance:
            instance_node = graph_generator.get_node_from_any_subcluster(
                require_ports_cluster, data_instance)
            if instance_node is None:
                instance_node = graph_generator.get_node_from_any_subcluster(
                    pr_ports_cluster, data_instance)
            graph_generator.connect(api_node, runnable_node,
                                   ib_cluster, direction="back")
            graph_generator.connect(instance_node, api_node,
                                   swc_cluster, direction="back")
        else:
            instance_node = graph_generator.get_node_from_any_subcluster(
                provide_ports_cluster, data_instance)
            if instance_node is None:
                instance_node = graph_generator.get_node_from_any_subcluster(
                    pr_ports_cluster, data_instance)
            graph_generator.connect(runnable_node, api_node, ib_cluster)
            graph_generator.connect(api_node, instance_node, swc_cluster)
        return instance_node


def add_or_create_runnable(graph_generator, ib_cluster, runnable):
    return graph_generator.get_or_create_node(ib_cluster, runnable, "{{name}}\nentryPoint: {{entryPoint}}", style=EXECUTABLE_STYLE, url="../executable_context_graph/"+runnable.findtext("entryPoint")+".gv.svg")


def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Software Component")
    root = graph_generator.get_model_root()

    swcs = root.findall("partitions/*/softwareComponents/*")
    if not swcs:
        return False

    executable_to_task_mappings = OrderedDict()
    for event_mapping in root.findall("events/*/taskEventMappings/*"):
        executable_to_task_mappings.setdefault(graph_generator.find_and_resolve_reference(
            event_mapping, "executableRef"), []).append(event_mapping)
    for event_mapping in root.findall("events/modeSwitchEventGroupInstance/*/*/modeSwitchEventInstances/*/taskEventMappings/*"):
        executable_to_task_mappings.setdefault(graph_generator.find_and_resolve_reference(
            event_mapping, "executableRef"), []).append(event_mapping)

    for swc in swcs:
        swc_name = swc.findtext("name")
        cluster_name = swc_name+"_connections"
        if select and cluster_name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(
            swc_name, cluster_name)
        if list_only:
            continue
        partition = swc.getparent().getparent()
        software_components = partition.findall("softwareComponents/*")
        # create swc cluster with internal behavior and r/p port clusters
        swc_cluster = graph_generator.get_or_create_cluster(
            swc_name, swc_name+"\n(Partition: "+partition.findtext("name")+")", parent_cluster=cluster, color="darkgrey")
        ib_cluster = graph_generator.get_or_create_cluster(
            "internalBehavior", "", parent_cluster=swc_cluster)
        require_ports_cluster = graph_generator.get_or_create_cluster(
            "rports", "R-Ports", parent_cluster=swc_cluster, color="grey")
        provide_ports_cluster = graph_generator.get_or_create_cluster(
            "pports", "P-Ports", parent_cluster=swc_cluster, color="grey")
        pr_ports_cluster = graph_generator.get_or_create_cluster(
            "prports", "PR-Ports", parent_cluster=swc_cluster, color="grey")
        ports = swc.findall("providePorts/*") + swc.findall("requirePorts/*")
        add_ports_and_data_instances(ports, pr_ports_cluster, require_ports_cluster,
                                     provide_ports_cluster, graph_generator, ib_cluster, swc_cluster)
        # create all events first, because later we might connect the api (i.e. Rte_IrTrigger) of a runnable with another event
        add_events(swc, graph_generator, ib_cluster,
                   executable_to_task_mappings, swc_cluster)
        add_runnables_and_ap_is(swc, graph_generator, ib_cluster, swc_cluster,
                               provide_ports_cluster, require_ports_cluster, pr_ports_cluster)
        add_and_connect_counterpart_port(
            ports, graph_generator, pr_ports_cluster, require_ports_cluster, provide_ports_cluster, cluster)


def add_and_connect_counterpart_port(ports, graph_generator, pr_ports_cluster, require_ports_cluster, provide_ports_cluster, cluster):
    for port in ports:
        source_port_name = port.findtext("name")
        port_type = port.getparent().tag
        for query in port_connection_queries:
            if not graph_generator.find_and_resolve_references(port, query.find_data_instances_of_port):
                continue
            target_vdis = []

            if port_type == "requirePorts":
                for q in query.find_connected_data_instances_of_r_port:
                    target_vdis += graph_generator.find_and_resolve_references(
                        port, query.find_data_instances_of_port + "/" + q)
            else:
                for q in query.find_connected_data_instances_of_p_port:
                    target_vdis += graph_generator.find_and_resolve_references(
                        port, query.find_data_instances_of_port + "/" + q)
            connected_to_port = set()
            for target_vdi in target_vdis:
                connected_to_port.add(target_vdi.getparent().getparent())
            all_connected_to_same_port = (len(connected_to_port) == 1)

            if port.findtext("PRPort") == "true":
                port_parent_cluster = pr_ports_cluster
            elif port_type == "requirePorts":
                port_parent_cluster = require_ports_cluster
            else:
                port_parent_cluster = provide_ports_cluster

            for source_vdi in port.findall(query.find_data_instances_of_port):
                is_rvdi = (source_vdi.tag == query.check_for_require_side)
                source_vdi_name = source_vdi.findtext("name")

                source_vdi_node = graph_generator.get_node_from_any_subcluster(
                    port_parent_cluster, source_vdi)
                if all_connected_to_same_port:
                    # only create a cluster for the whole port if all vdis are connected to the same port
                    # otherwise the diagram results in many different crossovers
                    port_node = graph_generator.get_cluster(
                        source_port_name, port_parent_cluster)
                    cluster_for_connected = graph_generator.get_or_create_cluster(
                        port_node.id, "connected to\n"+source_port_name, parent_cluster=cluster)
                else:
                    # create a cluster not for the whole port but only for the vdi
                    cluster_for_connected = graph_generator.get_or_create_cluster(
                        source_vdi_node.id, "connected to\n"+source_vdi_name, parent_cluster=cluster)

                target_vdis = []
                signals = []
                signal_mappings = []
                if is_rvdi:
                    for q in query.find_connected_data_instances_of_r_port:
                        target_vdis += graph_generator.find_and_resolve_references(
                            source_vdi, q)
                    for q in query.find_signals_of_data_instance_of_r_port:
                        signals += graph_generator.find_and_resolve_references(
                            source_vdi, q)
                    for q in query.find_signal_mappings_of_data_instance_of_r_port:
                        signal_mappings += graph_generator.find_and_resolve_references(
                            source_vdi, q)
                else:
                    for q in query.find_connected_data_instances_of_p_port:
                        target_vdis += graph_generator.find_and_resolve_references(
                            source_vdi, q)
                    for q in query.find_signals_of_data_instance_of_p_port:
                        signals += graph_generator.find_and_resolve_references(
                            source_vdi, q)
                    for q in query.find_signal_mappings_of_data_instance_of_p_port:
                        signal_mappings += graph_generator.find_and_resolve_references(
                            source_vdi, q)

                for target_vdi in target_vdis:
                    port = target_vdi.getparent().getparent()
                    port_name = port.findtext("name")
                    port_type = port.getparent().tag
                    swc = port.getparent().getparent()
                    swc_name = swc.findtext("name")
                    partition = swc.getparent().getparent()
                    target_swc_cluster = graph_generator.get_or_create_cluster(swc_name, swc_name+(("\n(Partition:"+partition.findtext(
                        "name")+")") if partition.tag == "partition" else ""), parent_cluster=cluster_for_connected, color="darkgrey", url=swc_name+"_connections.gv.svg")
                    if port.findtext("PRPort") == "true":
                        target_port_parent_cluster = graph_generator.get_or_create_cluster(
                            "prports", "PR-Ports", parent_cluster=target_swc_cluster, color="grey")
                    elif port_type == "requirePorts":
                        target_port_parent_cluster = graph_generator.get_or_create_cluster(
                            "rports", "R-Ports", parent_cluster=target_swc_cluster, color="grey")
                    else:
                        target_port_parent_cluster = graph_generator.get_or_create_cluster(
                            "pports", "P-Ports", parent_cluster=target_swc_cluster, color="grey")
                    target_port_cluster = graph_generator.get_or_create_cluster(
                        port_name, port_name, parent_cluster=target_port_parent_cluster, color="dimgray")
                    target_vdi_node = graph_generator.get_or_create_node(
                        target_port_cluster, target_vdi, "{{name}}", style=query.style)
                    if is_rvdi:
                        graph_generator.connect(
                            target_vdi_node, source_vdi_node, cluster)
                    else:
                        graph_generator.connect(
                            source_vdi_node, target_vdi_node, cluster)

                for signal in signals:
                    signal_node = graph_generator.get_or_create_node(
                        cluster_for_connected, signal, "{{name}}", style=SIGNAL_STYLE)
                    if is_rvdi:
                        graph_generator.connect(
                            signal_node, source_vdi_node, cluster)
                    else:
                        graph_generator.connect(
                            source_vdi_node, signal_node, cluster)
                for signal_mapping in signal_mappings:
                    signal_group = signal_mapping.getparent().getparent()
                    if signal_group is not None:
                        signal_group_node = graph_generator.get_or_create_node(
                            cluster_for_connected, signal_group, "{{name}}", style=SIGNAL_GROUP_STYLE)
                        if is_rvdi:
                            graph_generator.connect(
                                signal_group_node, source_vdi_node, cluster)
                        else:
                            graph_generator.connect(
                                source_vdi_node, signal_group_node, cluster)


def add_runnables_and_ap_is(swc, graph_generator, ib_cluster, swc_cluster, provide_ports_cluster, require_ports_cluster, pr_ports_cluster):
    for runnable in swc.findall("runnables/*"):
        runnable_node = add_or_create_runnable(
            graph_generator, ib_cluster, runnable)
        for api in graph_generator.find_and_resolve_references(runnable, "apis/apiRef"):
            api_name_groups = api.findtext("externalName").split('_')
            api_name = '_'.join(api_name_groups[:2])
            api_node = graph_generator.get_or_create_node(
                ib_cluster, api, api_name, style=API_STYLE)
            found_api_to_data_instance_access = False
            for query in port_connection_queries:
                di = graph_generator.find_and_resolve_reference(
                    api, query.target_element_of_api)
                if di is not None and di.tag not in query.not_allowed_type_for_data_instance:
                    di_node = add_data_instance(graph_generator, di, di is not None and di.tag == query.check_for_require_side,
                                               swc_cluster, ib_cluster, provide_ports_cluster, require_ports_cluster, pr_ports_cluster, api_node, runnable_node)
                    found_api_to_data_instance_access = True
                    break

            if not found_api_to_data_instance_access:
                graph_generator.connect(runnable_node, api_node, ib_cluster)
                ir_var = graph_generator.find_and_resolve_reference(
                    api, "interRunnableVariableRef")
                if ir_var is not None:
                    ir_var_node = graph_generator.get_or_create_node(
                        ib_cluster, ir_var, "{{name}}", style=INTER_RUNNABLE_VARIABLE_STYLE)
                    graph_generator.connect(api_node, ir_var_node, swc_cluster)
                exclusive_area = graph_generator.find_and_resolve_reference(
                    api, "exclusiveAreaRef")
                if exclusive_area is not None:
                    ea_node = graph_generator.get_or_create_node(
                        ib_cluster, exclusive_area, "{{name}}", style=EA_STYLE)
                    graph_generator.connect(api_node, ea_node, swc_cluster)
                parameter_instance = graph_generator.find_and_resolve_reference(
                    api, "parameterDataInstanceRef")
                if parameter_instance is not None:
                    param_node = graph_generator.get_or_create_node(
                        ib_cluster, parameter_instance, "{{name}}", style=LOCAL_PARAMETER_INSTANCE_STYLE)
                    graph_generator.connect(api_node, param_node, swc_cluster)
                internal_p_trigger_instance = graph_generator.find_and_resolve_reference(
                    api, "pTriggerRef")
                if internal_p_trigger_instance is not None:
                    for trigger_event in graph_generator.find_and_resolve_references(internal_p_trigger_instance, "swcInternalRTrigger/triggerEvents/triggerEventRef"):
                        event_node = graph_generator.get_node_from_any_subcluster(
                            ib_cluster, trigger_event)
                        graph_generator.connect(api_node, event_node, swc_cluster)
                    for dc_runnable in graph_generator.find_and_resolve_references(internal_p_trigger_instance, "swcInternalRTrigger/directCalledEventMappings/directCalledEventMapping/executableRef"):
                        runnable_node = graph_generator.get_node_from_any_subcluster(
                            ib_cluster, dc_runnable)
                        graph_generator.connect(
                            api_node, runnable_node, swc_cluster)


def add_events(swc, graph_generator, ib_cluster, executable_to_task_mappings, swc_cluster):
    for runnable in swc.findall("runnables/*"):
        # create runnable node
        runnable_node = add_or_create_runnable(
            graph_generator, ib_cluster, runnable)
        for mapping in executable_to_task_mappings.get(runnable, []):
            event = mapping.getparent().getparent()
            # create and connect event node
            add_event(graph_generator, swc_cluster,
                     ib_cluster, event, runnable_node)


def add_ports_and_data_instances(ports, pr_ports_cluster, require_ports_cluster, provide_ports_cluster, graph_generator, ib_cluster, swc_cluster):
    for port in ports:
        port_name = port.findtext("name")
        port_type = port.getparent().tag
        # create port cluster
        if port.findtext("PRPort") == "true":
            port_parent_cluster = pr_ports_cluster
        elif port_type == "requirePorts":
            port_parent_cluster = require_ports_cluster
        else:
            port_parent_cluster = provide_ports_cluster
        port_cluster = graph_generator.get_or_create_cluster(
            port_name, port_name, parent_cluster=port_parent_cluster, color="dimgray")
        for query in port_connection_queries:
            for di in port.findall(query.find_data_instances_of_port):
                di_node = graph_generator.get_or_create_node(
                    port_cluster, di, "{{name}}", style=query.style)
                # handle direct calls
                for executable in graph_generator.find_and_resolve_references(di, "directCalledEventMappings/directCalledEventMapping/executableRef"):
                    runnable_node = add_or_create_runnable(
                        graph_generator, ib_cluster, executable)
                    graph_generator.connect(
                        di_node, runnable_node, swc_cluster, color="darkblue")
                for executable in graph_generator.find_and_resolve_references(di, "directCalledEventMapping/executableRef"):
                    runnable_node = add_or_create_runnable(
                        graph_generator, ib_cluster, executable)
                    graph_generator.connect(
                        di_node, runnable_node, swc_cluster, color="darkblue")
