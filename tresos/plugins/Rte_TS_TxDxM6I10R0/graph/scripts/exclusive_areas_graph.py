"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    This diagram shows all exclusive areas and their accessing runnables/schedulables up to the task context in which they are running.
    If a runnable/schedulable is directly called by another runnable/schedulable, the calling chain is included, too. Exclusive areas that are colored
    green, are optimized meaning that even if a lock is configured, the Rte decided that it is not necessary, otherwise they are
    colored red.
    
    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand the Rte generators decision why a certain exclusive area is
    optimized or not optimized. By looking at the tasks at the end of the chain, it can be decided whether they can preempt each
    other (and thus a lock is necessary) or not.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation.    
"""




from rtegraph import graph_generator
from rtegraph.constants import *
from scripts.executable_context_graph import *

def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Exclusive Areas")
    root = graph_generator.get_model_root()
    exclusive_areas = root.xpath(
        "partitions/*/softwareComponents/*/exclusiveAreas/* | partitions/*/bswModules/*/exclusiveAreas/*")
    if not exclusive_areas:
        return False

    executable_to_task_mappings = create_executable_to_task_mappings(graph_generator)
    task_map = create_task_map(root)

    for exclusivearea in exclusive_areas:
        clusterid = exclusivearea.get('id')
        # add function to add a cluster, get it and use it
        cluster_name = exclusivearea.getparent().getparent().findtext("name") + '-' + exclusivearea.findtext("name")
        if select and cluster_name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(clusterid, cluster_name)
        if list_only:
            continue
        dc = exclusivearea.findtext("dataConsistencyMechanism")
        exclusiveareanode = graph_generator.get_or_create_node(cluster, exclusivearea, """{{name}}
Configured DC: {{configuredDataConsistencyMechanism}}
Current DC: {{dataConsistencyMechanism}}
Component: {{../../componentTypeName}}
Instance: {{../../name}}""", style=(
            OPTIMIZED_EXCLUSIVE_AREA_STYLE if dc == "No_Data_Consistency" else NOT_OPTIMIZED_EXCLUSIVE_AREA_STYLE))

        for executable in graph_generator.find_and_resolve_references(exclusivearea, "runsInsideExecutableInstances/executableRef"):
            executable_node = get_or_create_executable_and_callers(
                graph_generator, cluster, executable, executable_to_task_mappings, task_map)
            graph_generator.connect(
                executable_node, exclusiveareanode, cluster, label="runs inside")

        for executable in graph_generator.find_and_resolve_references(exclusivearea, "canEnterExecutableInstances/executableRef"):
            executable_node = get_or_create_executable_and_callers(
                graph_generator, cluster, executable, executable_to_task_mappings, task_map)
            graph_generator.connect(
                executable_node, exclusiveareanode, cluster, label="can enter")
