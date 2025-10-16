import os
import glob
import importlib.util
import argparse
from lxml import etree
from rtegraph import graph_generator
from timeit import default_timer as timer


def load_graph_modules():
    modules = []
    for module_file_path in glob.glob(os.path.join(os.path.join(os.path.dirname(os.path.realpath(__file__)), "scripts"), "*.py")):
        file_name = os.path.basename(module_file_path)[:-3]
        spec = importlib.util.spec_from_file_location(file_name, module_file_path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        modules.append(module)
    return modules


__modules = load_graph_modules()

def addModeDecGrList(tree):
    mode_dec_gr_elements = tree.xpath(".//*[contains(local-name(), 'ModeDeclarationGroupInstance') and substring-after(local-name(), 'ModeDeclarationGroupInstance') = '']")
    for mode in mode_dec_gr_elements:
        parent = etree.Element('modeDeclarationGroupInstances')
        mode_parent = mode.getparent()
        mode_parent.append(parent)
        parent.append(mode)

def main(args):
    print("Parsing xml...", end="", flush=True)
    tree = etree.parse(args.input)
    elements = tree.findall('//*[@id]')
    addModeDecGrList(tree)
    all_name_elements = {elements[i].get(
        "id"): elements[i] for i in range(0, len(elements))}
    root = tree.getroot()
    print("done")
    for module in __modules:
        name = module.__name__
        if name in args.gen or "all" in args.gen:
            if not args.gSingle or name == args.gSingle[0]:
                start = timer()
                graph_gen = graph_generator.GraphGenerator(
                    root, all_name_elements, args)
                if args.gSingle and args.gSingle[1] == 'list':
                    module.create_graphs(graph_gen, list_only = True)
                    available_graphs = graph_gen.get_cluster_names()
                    print(*available_graphs, sep = "\n")
                else:
                    print("Generate diagram " + name + "...", end="", flush=True)
                    if module.create_graphs(graph_gen, select = (args.gSingle[1].replace("\\n", "\n") if args.gSingle else None)) is not False:
                        if args.gSingle and not graph_gen.has_clusters():
                            raise KeyError("Diagram " + args.gSingle[1] + " of graph " + name + " doesn't exist")
                        if args.allInOne:
                            graph_gen.generate_graph(
                                filename=name, source_file_only=args.noRendering)
                        else:
                            graph_gen.generate_graph_per_cluster(
                                folder_name=name, source_file_only=args.noRendering)
                        end = timer()
                        print("done (" + "{:.2f}".format(end - start) + " seconds)")
                    else:
                        print("skipped")



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # Add default options
    requiredArgs = parser.add_argument_group('required arguments')
    requiredArgs.add_argument("-i", "--input", required=True,
                        help="Provide path to the Rte model file")
    requiredArgs.add_argument("-o", "--output", required=True,
                        help="Output folder where the graph needs to be generated")
    diagrams = []
    for module in __modules:
        diagrams.append(module.__name__)
    parser.add_argument("-g", "--gen", default='all', nargs=1,
                        help="Generates all diagrams of the given graph(s) category (all is default)", choices=["all"]+diagrams)
    parser.add_argument("-gSingle", required=False, metavar=('graph', '(diagram | list)'),
                help='Generates one diagram of the given graph category. If you want to list all available diagrams of a given graph, use \'list\' as the diagram name', nargs=2)                        
    parser.add_argument("-allInOne", required=False, action="store_true",
                        help="Generates all clusters in one diagram. Please note that Graphviz doesn't handle large diagrams properly.")
    parser.add_argument("-noLegend", required=False, action="store_true",
                        help="Avoids the generation of the legend")
    parser.add_argument("-noNames", required=False, action="store_true",
                        help="Generates no names for the elements of the diagram (not supported for all diagrams)")
    parser.add_argument("-noRendering", required=False, action="store_true",
                        help="Generates Graphviz source files without rendering them (faster)")
    main(parser.parse_args())
