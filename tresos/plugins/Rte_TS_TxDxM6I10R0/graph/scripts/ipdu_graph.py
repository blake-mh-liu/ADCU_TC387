"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows the connections of IPDU to the Com signals/signal groups and variable data instance.
    The signal/signal group block contains attributes:
    - name of the signal/signal group
    - hasUpdateBit: shows whether timeout is IPDU (ComUpdateBitPosition is not present) or signal based
    - COM Timeout(SvcAs): Com timeout calculated by Rte and updated by Service Needs Assistant. This is the smallest non zero AliveTimeout
      per IPDU/signal
    - group signals in case of signal group block
    The variable data instance block contains attributes:
    - name of variable data instance
    - configured AliveTimeout in sec.
    - ComTimeoutFactor: this is the factor to calculate real timeout = ComTimeoutFactor * COM Timeout(SvcAs)
    
    What is the purpose of the diagram?
    With the help of the diagram, it is possible to get an overview about the Com relevant insights of configured IPDUs and corresponding signals and signal groups as well as the connected variable data instances.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""




from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict
    
def add_rvdi(graph_generator, cluster, rvdi, sig_or_sig_group_name, sig_or_sig_group, smallestNonZeroAliveTimeout, has_update_bit):    
                rvdi_name = rvdi.findtext("name")
                if smallestNonZeroAliveTimeout == rvdi.findtext("aliveTimeoutSecs"):
                    vdi_style = VDI_LOWEST_TIMEOUT_STYLE
                else:
                    vdi_style = VDI_STYLE
                attribute_alive_timeout = "AliveTimeout: " + rvdi.findtext("aliveTimeoutSecs") + "s"
                rec_transf_to_timeout_factors = rvdi.find("receiveTransformables2comTimeoutFactors/entry/key[.=\""+sig_or_sig_group_name+"\"]/..")  
                com_timeout_factor = "ComTimeoutFactor: "
                if rec_transf_to_timeout_factors is not None:
                    com_timeout_factor = com_timeout_factor + rec_transf_to_timeout_factors.findtext("value") 
                else:
                    com_timeout_factor = com_timeout_factor + "0"            
                rvdi_node = graph_generator.get_or_create_node_with_customized_id(
                rvdi.get("id")+sig_or_sig_group.get("id"), cluster, text=rvdi_name+"\n"+attribute_alive_timeout+"\n"+com_timeout_factor, style=vdi_style)
                return rvdi_node
                
def add_sig_or_sig_group(graph_generator, cluster, pdu, pdu_node, sig_or_sig_group, container_ref, sig_or_sig_group_style): 
            sig_or_sig_group_name = sig_or_sig_group.findtext("name")
            has_update_bit = graph_generator.find_and_resolve_reference(sig_or_sig_group, container_ref).findtext("hasUpdateBitPosition")
            attribute_alive_timeout_handler = sig_or_sig_group.find("aliveTimeoutHandler")
            if len(attribute_alive_timeout_handler) != 0:            
                smallestNonZeroAliveTimeout = sig_or_sig_group.find("aliveTimeoutHandler").findtext("smallestNonZeroAliveTimeout")
                if has_update_bit == "false":
                    title = "I-PDU based timeout (without update bits)"
                else:
                    title = "Signal/Signal Group Based timeout (with update bits)"
                title += "\n Resulting Timeout: " + smallestNonZeroAliveTimeout
                
                if has_update_bit == "false":
                    cluster_id = pdu.get('id')+ "timeout"
                    cluster_color = "beige"
                else:
                    cluster_id = sig_or_sig_group.get('id')+"timeout"
                    cluster_color = None
                    
                sig_or_sig_group_cluster = graph_generator.get_or_create_cluster(cluster_id, title, cluster_color, parent_cluster=cluster)
            else:
                smallestNonZeroAliveTimeout = 0
                sig_or_sig_group_cluster = cluster

            group_signal_names = "\n"                
            if sig_or_sig_group.tag == "receiveSignalGroup":
                group_signals = sig_or_sig_group.findall("receiveSignals/receiveSignal")                
                for group_signal in group_signals:
                    group_signal_names = group_signal_names + group_signal.findtext("name")+"\n"
            sig_or_sig_group_node = graph_generator.get_or_create_node(
            sig_or_sig_group_cluster, sig_or_sig_group, sig_or_sig_group_name+group_signal_names, style=sig_or_sig_group_style)
            graph_generator.connect(pdu_node, sig_or_sig_group_node, cluster)
            
            for rvdi in graph_generator.find_and_resolve_references(sig_or_sig_group, "rVariableDataInstances/rVariableDataInstanceRef"):
                rvdi_node = add_rvdi(graph_generator, sig_or_sig_group_cluster, rvdi, sig_or_sig_group_name, sig_or_sig_group, smallestNonZeroAliveTimeout, has_update_bit)
                graph_generator.connect(
                       sig_or_sig_group_node, rvdi_node, sig_or_sig_group_cluster)
                       
def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Timeouts")
    root = graph_generator.get_model_root()
    pdus = root.findall("partitions/partition/receiveIpdus/receiveIpdu")

    if not pdus:
        return False

    for pdu in pdus:
        pdu_name = pdu.findtext("name")
        if select and pdu_name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(pdu.get('id'), pdu_name)
        if list_only:
            continue
        pdu_node = graph_generator.get_or_create_node(
            cluster, pdu, pdu_name, style=IPDU_STYLE)
        for signal in graph_generator.find_and_resolve_references(pdu, "receiveSignals/receiveSignalRef"):                  
            add_sig_or_sig_group(graph_generator, cluster, pdu, pdu_node, signal, "signalContainerRef", SIGNAL_STYLE)
                   
        for signal_group in graph_generator.find_and_resolve_references(pdu, "receiveSignalGroups/receiveSignalGroupRef"):                 
            add_sig_or_sig_group(graph_generator, cluster, pdu, pdu_node, signal_group, "signalGroupContainerRef", SIGNAL_GROUP_STYLE)
