"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict
from scripts.tasks_graph import *

"""
    What does the diagram show?
    For every inter-partition shared memory buffer (IP Channel) it shows all producers on the left hand side and all consumers on the right hand side.
    For every core, the existing consumers/producers are grouped. The calculated data consistency mechanism (core-global/core-local) is shown.

    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand the Rte generators decision why certain Rte APIs that access that buffer
    use a certain locking mechanism. 

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""


def __add_core_producer_consumer_cluster(graph_generator, cluster, ip_channel, ip_channel_node, task_to_groups, tasks, dc, producer_consumer_cores):
    is_producer = dc.findtext("isProducer") == 'true'
    consumer_or_producer_text = "producer" if is_producer else "consumer"
    core_id = dc.findtext("coreId")
    if core_id not in producer_consumer_cores.get(is_producer, []):
        # core is not a consumer/producer, so skip it
        return
    dc_type = dc.findtext("dataConsistencyMechanismType")
    spinlock_required = dc.findtext("isSpinlockRequired") == 'true'
    producer_consumer_cluster = graph_generator.get_or_create_cluster(
        consumer_or_producer_text, consumer_or_producer_text.capitalize(), parent_cluster=cluster)
    producer_consumer_core_cluster = graph_generator.get_or_create_cluster(
        core_id, "Core " + core_id, parent_cluster=producer_consumer_cluster)
    graph_generator.get_or_create_node_with_customized_id(
        producer_consumer_core_cluster.id+"dc", producer_consumer_core_cluster, text=dc_type, style=DATA_CONSISTENCY_STYLE)
    if spinlock_required:
        graph_generator.get_or_create_node_with_customized_id(
            producer_consumer_core_cluster.id+"spinlock", producer_consumer_core_cluster, text="Spinlock", style=DATA_CONSISTENCY_STYLE)
    tasks_per_core = tasks.get((core_id, is_producer), [])
    if tasks_per_core:
        for task in tasks_per_core:
            producer_consumer_node = add_task_node(graph_generator, producer_consumer_core_cluster, task, True)
            if is_producer:
                graph_generator.connect(
                    producer_consumer_node, ip_channel_node, cluster)
            else:
                graph_generator.connect(
                    ip_channel_node, producer_consumer_node, cluster)
    else:
        unkown_task_node = graph_generator.get_or_create_node_with_customized_id(
            producer_consumer_core_cluster.id+"_unkown", producer_consumer_core_cluster, text="Unknown Task", style=UNKNOWN_TASK_STYLE)
        if is_producer:
            graph_generator.connect(unkown_task_node, ip_channel_node, cluster)
        else:
            graph_generator.connect(ip_channel_node, unkown_task_node, cluster)
    if ip_channel.findtext(consumer_or_producer_text+"Info/unknownTaskContext") == 'true':
        graph_generator.get_or_create_node_with_customized_id(
            producer_consumer_cluster.id+"_unkown", producer_consumer_cluster, text="Unknown " + consumer_or_producer_text, style=UNKNOWN_TASK_STYLE)

def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("IP Channel Data Consistencies")
    root = graph_generator.get_model_root()
    ip_channels = root.findall("ipChannels/*")
    if not ip_channels:
        return False
    if root.findtext("ecuc/rte/interPartitionCommunication") == "Ioc":
        return False  # no data consistency diagrams for Ioc

    cooperative_task_groups = root.findall("cooperativeTaskGroups/*")
    task_to_groups = OrderedDict()
    group_id = 0
    for task_group in cooperative_task_groups:
        group_id += 1
        tasks = graph_generator.find_and_resolve_references(
            task_group, "taskRef")
        for task in tasks:
            if task not in task_to_groups:
                task_to_groups[task] = set()
            task_to_groups[task].add(group_id)

    for ip_channel in ip_channels:
        ip_channel_id = ip_channel.get('id')
        cluster_name = ip_channel.findtext("name")
        if select and cluster_name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(
            ip_channel_id, cluster_name)
        if list_only:
            continue
        ip_channel_node = graph_generator.get_or_create_node(cluster, ip_channel, """{{name}}
queued: {{queued}}
atomic access: {{atomicAccess}}""", style=IP_CHANNEL_STYLE)
        tasks = OrderedDict()
        for task in graph_generator.find_and_resolve_references(ip_channel, "producerInfo/tasks/taskRef"):
            core_id = task.findtext("../../coreId")
            tasks.setdefault((core_id, True), []).append(task)
        for task in graph_generator.find_and_resolve_references(ip_channel, "consumerInfo/tasks/taskRef"):
            core_id = task.findtext("../../coreId")
            tasks.setdefault((core_id, False), []).append(task)
        producer_consumer_cores = OrderedDict()
        for producer_core in ip_channel.findall("producerInfo/coreIds/coreId"):
            producer_consumer_cores.setdefault(
                True, []).append(producer_core.text)
        for consumer_core in ip_channel.findall("consumerInfo/coreIds/coreId"):
            producer_consumer_cores.setdefault(
                False, []).append(consumer_core.text)
        for dc in ip_channel.findall("coreDataConsistencyMechanisms/*"):
            __add_core_producer_consumer_cluster(
                graph_generator, cluster, ip_channel, ip_channel_node, task_to_groups, tasks, dc, producer_consumer_cores)
