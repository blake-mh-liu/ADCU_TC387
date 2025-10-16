"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

"""
    What does the diagram show?
    The diagram shows the context for every runnable/schedulable which is either one or multiple tasks or other runnables/schedulables in between (direct calling chains).
    If a runnable is mapped to a BSW entity, this mapping is shown too.

    What is the purpose of the diagram?
    With the help of the diagram, it is possible to better understand the context in which each runnable/schedulable can run.

    Disclaimer: This script for generating the diagram is only an example and does not claim to be complete or correct. It is only
    a support to better understand the internal data model of the generator and the decisions made during the code generation. 
"""


from rtegraph import graph_generator
from rtegraph.constants import *
from collections import OrderedDict
from scripts.tasks_graph import *

def get_or_create_executable_and_callers(graph_generator, cluster, executable, executable_to_task_mappings, task_map, already_mapped=False):
    executable_node = graph_generator.get_node(cluster, executable)
    if executable_node is not None:
        return executable_node  # executable and it's callers/tasks already exists
    else:
        executable_node = graph_generator.get_or_create_node(
            cluster, executable, "{{name}}\nsymbol: {{entryPoint}}", style=EXECUTABLE_STYLE)
    found_context = False
    if not already_mapped:
        mapped_executable = graph_generator.find_and_resolve_reference(
            executable, "mappedExecutableInstanceRef")
        if mapped_executable is not None:
            found_context = True
            mapped_executable_node = get_or_create_executable_and_callers(
                graph_generator, cluster, mapped_executable, executable_to_task_mappings, task_map, True)
            graph_generator.connect(
                mapped_executable_node, executable_node, cluster, label="SwcBswMapping")
    task_event_mappings = executable_to_task_mappings.get(executable, [])

    for mapping in task_event_mappings:
        taskname = mapping.findtext("taskName")
        task = task_map.get(taskname)
        if task is not None:
            found_context = True
            task_node = add_task_node(graph_generator, cluster, task, True)
            event_name = mapping.findtext("eventName")
            position = mapping.findtext("position")                
            graph_generator.connect(
                task_node, executable_node, cluster, label="Pos " + position+": " + event_name)
    called_executables = graph_generator.find_and_resolve_references(
        executable, "directCallers/directCallerRef")
    for called_executable in called_executables:
        found_context = True
        called_executable_node = get_or_create_executable_and_callers(
            graph_generator, cluster, called_executable, executable_to_task_mappings, task_map)
        graph_generator.connect(
            called_executable_node, executable_node, cluster, label="(direct call)")
    if not found_context:
        task_node = graph_generator.get_or_create_node_with_customized_id(
            'unknownTask' + cluster.id, cluster, text="Unkown Task", style=UNKNOWN_TASK_STYLE)
        graph_generator.connect(task_node, executable_node, cluster)
    return executable_node


def create_executable_to_task_mappings(graph_generator):
    root = graph_generator.get_model_root()
    executable_to_task_mappings = OrderedDict()
    for event_mapping in root.findall("events/*/taskEventMappings/*"):
        executable_to_task_mappings.setdefault(graph_generator.find_and_resolve_reference(
            event_mapping, "executableRef"), []).append(event_mapping)
    for event_mapping in root.findall("events/modeSwitchEventGroupInstance/*/*/modeSwitchEventInstances/*/taskEventMappings/*"):
        executable_to_task_mappings.setdefault(graph_generator.find_and_resolve_reference(
            event_mapping, "executableRef"), []).append(event_mapping)
    return executable_to_task_mappings


def create_task_map(root):
    task_map = OrderedDict()
    for task in root.findall("partitions/partition/tasks/task") + root.findall("partitions/partition/Interrupts/Interrupt"):
        task_map[task.findtext("name")] = task
    return task_map

def create_graphs(graph_generator, list_only=False, select=None):
    graph_generator.set_title("Runnable/Schedulable Context")
    root = graph_generator.get_model_root()

    executables = root.findall("partitions/*/softwareComponents/*/runnables/*") + root.findall("partitions/*/bswModules/*/bsnps/*/bswModuleEntities/*")
    if not executables:
        return False

    executable_to_task_mappings = create_executable_to_task_mappings(graph_generator)
    task_map = create_task_map(root)

    for executable in executables:
        entry_point = executable.findtext("entryPoint")
        name = executable.findtext("name")
        if select and entry_point != select:
            continue
        cluster = graph_generator.get_or_create_cluster(entry_point, entry_point)
        if list_only:
            return

        get_or_create_executable_and_callers(
            graph_generator, cluster, executable, executable_to_task_mappings, task_map)
