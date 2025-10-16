"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows the scheduling of the tasks mapped to a particular taskchain and gives an overview of the 
    timing in which each of the tasks are executed.
    
    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand the scheduling of the tasks in a taskchain.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""

from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict


def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Task Chains")
    root = graph_generator.get_model_root()
    task_chains = root.findall("partitions/*/taskChains/*")
    if not task_chains:
        return False

    graph_generator.enable_new_rank()

    position = 0
    for task_chain in task_chains:
        task_chain_name = task_chain.findtext("name")
        if graph_generator.get_cluster(task_chain_name) != None:
            # inter-partition task chains appear in every partition, skip second (same) one
            continue
        if select and task_chain_name != select:
            continue        
        cluster = graph_generator.get_or_create_cluster(
            task_chain_name, task_chain_name)
        if list_only:
            continue            
        last_time_node = None
        time = 0
        for task_list in task_chain.findall("taskSequenceTable/taskList"):
            task_list_cluster = graph_generator.get_or_create_cluster(
                "taskList" + task_chain_name + str(position), "", parent_cluster=cluster, style="invis")
            task_list_cluster.rank = "same"
            last_task = None
            time_node_of_task_chain = None
            position += 1
            period = 0
            for task in graph_generator.find_and_resolve_references(task_list, "tasks/taskRef"):
                taskname = task.findtext("name")
                task_node = graph_generator.get_or_create_node_with_customized_id(task.get(
                    "id")+str(position), task_list_cluster, text=taskname, style=TASK_STYLE, url="../tasks_graph/"+taskname+".gv.svg")
                if time_node_of_task_chain is None:
                    period = int(task.findtext("periodNanos"))/1000000
                    time_node_of_task_chain = graph_generator.get_or_create_node_with_customized_id(
                        "time"+str(position), task_list_cluster, text=str(time)+" ms", style=TIME_STYLE)
                    graph_generator.connect(task_node, time_node_of_task_chain, task_list_cluster, style="invis")
                    time += period
                if last_task is not None:
                    graph_generator.connect(
                        task_node, last_task, task_list_cluster, direction="back")
                last_task = task_node
            if last_time_node is not None:
                graph_generator.connect(
                    last_time_node, time_node_of_task_chain, cluster, style="dashed")
            last_time_node = time_node_of_task_chain
