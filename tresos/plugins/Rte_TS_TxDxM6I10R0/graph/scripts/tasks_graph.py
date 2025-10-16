"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows the generated tasks and all runnables/schedulables running in that task which are either directly mapped
    i.e. via an event-to-task mapping or directly called from another runnable/schedulable (direct calling chain).
    In addition, it shows if a runnable/schedulable needs an explicit or implicit waitpoint and is thus of category 2. An explicit
    waitpoint is a waitpoint that is explicitly configured in the model e.g. to configure a blocking API whereas an
    implicit waitpoint is shown if the Rte implementation requires a WaitEvent() call.
    If a runnable/schedulable has such a waitpoint it is colored red, otherwise green.
    
    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand if a task needs to be an extended task. If at least one runnable/schedulable
    which is running in that task needs a waitpoint, then it is of category 2 and thus the whole task needs a wait state, too (extended task).
    By looking at the diagram, it is possible to easily identify such runnables/schedulables and to know which one caused the task to be extended.
    Please note: There are many more conditions that need to be checked whether a task is basic or extended. This diagram mainly focuses on
    the calling chains and possible wait points.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""




from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict

task_to_groups = None
def create_cooperative_task_groups(graph_generator):
    root = graph_generator.get_model_root()
    cooperative_task_groups = root.findall("cooperativeTaskGroups/*")
    global task_to_groups
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

def add_task_node(graph_generator, cluster, task, with_link):
    if task_to_groups is None:
        create_cooperative_task_groups(graph_generator)
    task_node = graph_generator.get_or_create_node(cluster, task, """{{name}}
Runtime Priority: {{runtimePriority}}
Configured Priority: {{configuredPriority}}
Schedule: {{taskSchedule}}
Internal Resource: {{internalResourceName}}
Cooperative groups: """ + str(task_to_groups[task] if task_to_groups.get(task) is not None else "-"), style=TASK_STYLE, url=("../tasks_graph/"+task.findtext("name")+".gv.svg") if with_link else None)
    return task_node

def add_executable(graph_generator, cluster, executable):
    category = executable.findtext("category")
    executable_node = graph_generator.get_or_create_node(cluster, executable, "{{name}}\nsymbol: {{entryPoint}}", style=(
        RUNNABLE_CAT2_STYLE if category == "CAT2" else RUNNABLE_CAT1_STYLE), url="../executable_context_graph/"+executable.findtext("entryPoint")+".gv.svg")
    if executable.findtext("waitPoints") == "true":
        waitpoint_node = graph_generator.get_or_create_node_with_customized_id(
            cluster.id+"_"+executable.get("id")+"_wpExplicit", cluster, text="Explicit\nWaitpoint", style=WAITPOINT_STYLE)        
        graph_generator.connect(executable_node, waitpoint_node, cluster)
    for api in graph_generator.find_and_resolve_references(executable, "apis/apiRef"):
        found_direct_call_executable = False
        for direct_called_executable in graph_generator.find_and_resolve_references(api, "directCalledExecutables/executableRef"):
            found_direct_call_executable = True
            api_node = graph_generator.get_or_create_node(
                cluster, api, "{{externalName}}", style=API_STYLE)
            direct_executable_node = add_executable(
                graph_generator, cluster, direct_called_executable)
            graph_generator.connect(executable_node, api_node, cluster)
            graph_generator.connect(api_node, direct_executable_node, cluster)
        oi = graph_generator.find_and_resolve_reference(
            api, "operationInstanceRef")
        if oi != None and not found_direct_call_executable: #ignore waitpoint if inherited from directly called runnable
            if oi.findtext("synchronousWaitPointRequired") == "true": 
                api_node = graph_generator.get_or_create_node(
                    cluster, api, "{{externalName}}", style=API_STYLE)
                waitpoint_node = graph_generator.get_or_create_node_with_customized_id(
                    cluster.id+"_"+api_node.id+"_wpImplicit", cluster, text="Implicit\nWaitpoint", style=WAITPOINT_STYLE)
                graph_generator.connect(executable_node, api_node, cluster)
                graph_generator.connect(api_node, waitpoint_node, cluster)

    return executable_node

def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Tasks")
    root = graph_generator.get_model_root()
    tasks = root.findall("partitions/partition/tasks/task") + \
        root.findall("partitions/partition/Interrupts/Interrupt")

    if not tasks:
        return False

    for task in tasks:
        name = task.findtext("name")
        if select and name != select:
            continue
        cluster = graph_generator.get_or_create_cluster(name, name)
        if list_only:
            continue
        task_node = add_task_node(graph_generator, cluster, task, False)
        for event in graph_generator.find_and_resolve_references(task, "eventInstances/eventInstanceRef"):
            # todo consider mode switch event groups
            if event.tag == "modeSwitchEventGroupInstance":
                task_event_mappings = event.findall(
                    "*/*/modeSwitchEventInstances/*/taskEventMappings/taskEventMapping")
            else:
                task_event_mappings = event.findall(
                    "taskEventMappings/taskEventMapping")

            for task_event_mapping in task_event_mappings:
                executable = graph_generator.find_and_resolve_reference(
                    task_event_mapping, "executableRef")
                executable_node = add_executable(
                    graph_generator, cluster, executable)
                event_name = task_event_mapping.findtext("eventName")
                position = task_event_mapping.findtext("position")
                graph_generator.connect(
                    task_node, executable_node, cluster, label="Pos " + position+": " + event_name)
