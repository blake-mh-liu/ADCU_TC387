"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

import os
import sys
from lxml import etree
from graphviz import Digraph
from collections import OrderedDict

from .imports import *


class GraphGenerator:
    def __init__(self, root, all_name_elements, args):
        self.__root = root
        self.__all_name_elements = all_name_elements
        self.__nodes = OrderedDict()
        self.__connections = OrderedDict()
        self.__clusters = OrderedDict()
        self.__subclusters = OrderedDict()
        self.__legend_cluster = None
        self.__args = args
        self.__title = None
        self.__newrank = None

    def get_args(self):
        return self.__args

    def get_model_root(self):
        """
        :return: the root node of the Rte xml model
        """
        return self.__root

    def enable_new_rank(self):
        """
        Sets the graphviz newrank feature to true
        """
        self.__newrank = "true"

    def new_cluster(self, id, label, color=None, style="filled", url=None):
        """
        Create a new cluster with the given arguments
        :param id: id of the cluster
        :param label: label to added in the generated graph
        :param color: color to be generated in the graph
        :param style: style of the new cluster
        :param url: link to other diagram
        :return: newly created cluster
        """
        return Cluster(id, label, color, style, url)

    def get_or_create_cluster(self, id, label, color=None, parent_cluster=None, style="filled", url=None):
        """
        Gets a cluster with the given id if it already exist, 
        else creates a new one.
        :param id: id of the cluster
        :param label: label to added in the generated graph
        :param color: color to be generated in the graph
        :param parent_cluster: the cluster in which the (sub) cluster shall be created
        :paramt style: the style of that cluster
        :param url: link to other diagram
        :return: an already existing cluster with this id or the new created one
        """
        if parent_cluster is not None:
            key = parent_cluster.id + "_" + id
            if key in self.__subclusters.keys():
                return self.__subclusters[key]
            self.__subclusters[key] = self.new_cluster(id, label, color, style, url)
            parent_cluster.add_cluster(self.__subclusters[key])
            return self.__subclusters[key]
        else:
            if id in self.__clusters.keys():
                return self.__clusters[id]
            self.__clusters[id] = self.new_cluster(id, label, color, style, url)
            return self.__clusters[id]

    def get_cluster_names(self):
        """
        Gets the name of all generated clusters
        """
        cluster_names = []
        for cluster in self.__clusters.values():
            if cluster is not self.__legend_cluster:
                cluster_names.append(cluster.label.replace("\n","\\n"))
        return cluster_names
    
    def has_clusters(self):
        return bool(self.__clusters)

    def get_cluster(self, id, parent_cluster=None):
        """
        Gets a cluster with the given id if it already exist, 
        else returns None
        :param id: id of the cluster
        :param parent_cluster: the parent cluster that contains the cluster
        :return: an already existing cluster with this id or None
        """
        if parent_cluster is not None:
            key = parent_cluster.id + "_" + id
            return self.__subclusters.get(key)
        else:
            return self.__clusters.get(id)

    def get_or_create_node(self, cluster, xmlelement, text, style, url=None):
        """
        Gets a Node for the given xml element if already exist,
        else creates a new Node and uses the passed property names 
        as label in the diagram
        :param cluster: cluster to add the node to
        :param xmlelement: xml element that contains info to create this node
        :param text: text for that node which can contain xml paths that are resolved if written as "{{<xml path>}}"
        :param style: style of the node
        :param url: link to other diagram
        :return: either the already existing node or the newly created one
        """
        self.add_legend(style=style)
        return Node.get_or_create_node(self.__nodes, cluster, xmlelement, text, style, url)

    def get_node(self, cluster, xmlelement):
        """
        Gets a Node for the given xml element if already exist,
        otherwise None is returned
        :param cluster: cluster that contains the node
        :param xmlelement: xml element to search for
        :return: the found node or None if it doesn't exist 
        """
        return Node.get_node(self.__nodes, cluster, xmlelement)

    def get_node_from_any_subcluster(self, cluster, xmlelement):
        """
        Gets a Node from the cluster or any subclusters for the given xml element
        otherwise None is returned
        :param cluster: cluster or any subcluster that contains the node
        :param xmlelement: xml element to search for
        :return: the found node or None if it doesn't exist         
        """
        if cluster is not None:
            node = Node.get_node(self.__nodes, cluster, xmlelement)
            if node is not None:
                return node
            for subcluster in cluster.clusters.values():
                ret = self.get_node_from_any_subcluster(subcluster, xmlelement)
                if ret is not None:
                    return ret
        else:
            for subcluster in self.__subclusters.values():
                node = Node.get_node(self.__nodes, subcluster, xmlelement)
                if node is not None:
                    return node
        return None

    def get_or_create_node_with_customized_id(self, customizedid, cluster, xmlelement=None, text="", style=None, url=None):
        """
        Gets a Node for the given customizedid if already exist,
        else creates a new Node
        :param customizedid: custom id of the node 
        :param cluster: cluster to add the node to
        :param xmlelement: xml element that contains info to create this node
        :param text: text for that node which can contain xml paths that are resolved if written as "{{<xml path>}}"
        :param style: shastylepe of the node
        :param url: link to other diagram
        :return: either the already existing node or the newly created one
        """
        self.add_legend(style=style)
        return Node.get_or_create_node_with_customized_id(customizedid, self.__nodes, cluster, xmlelement, text, style, url)

    def connect(self, src, dest, cluster, label=None, color=BLACK, style=None, direction=None, arrowhead=None, arrowtail=None, weight=None, constraint=None, undirected=False):
        """
        Creates connection between the 2 given nodes.
        :param src: source node of the connection
        :param dest: destination node of the connection
        :param cluster: cluster that will contain this connection
        :param label: label to be added on the connection (edge)
        :param color: color of the connection (edge)
        :param style: style of the connection (edge)
        :param direction: direction of the connection (edge)
        :param arrowhead: arrowhead of the connection (edge)
        :param arrowtail: arrowtail of the connection (edge)
        :param weight: weight of the connection (edge)
        :param constraint: constraint of the connection (edge)
        :param undirected: if set to True, no new connection will be created if it already exists for the other direction
        """
        key = src.id + '_' + dest.id + '_' + cluster.id
        rev_key = dest.id + '_' + src.id + '_' + cluster.id
        if key not in self.__connections or (undirected and rev_key not in self.__connections):
            connection = Connection(src, dest, label if(label is not None) else "", color, style=style,
                                    direction=direction, arrowhead=arrowhead, arrowtail=arrowtail, weight=weight, constraint=constraint)
            self.__connections[key] = connection
            cluster.add_connection(connection)

    def generate_graph(self, filename, compound='true', rankdir="LR", ranksep="0.2", bgcolor="#F0F0FF", fontcolor="#0000A0", fontsize="13", source_file_only=False):
        """
        generates the graph for all the clusters in a single svg.
        :param filename: the file name to be generated
        :param compound: if true to allow edges between different clusters
        :param rankdir: set the direction of the graph layout
        :param ranksep: This is the minimum vertical distance between the bottom of the nodes 
        in one rank and the tops of nodes in the next
        :param bgcolor: background color of the generated graph
        :param fontcolor: the color used for text
        :param fontsize: font size used for text
        :param source_file_only: only generate the graphviz source file 
        """
        name = self.__title if self.__title is not None else filename
        maingraph = Digraph(comment=name)
        maingraph.attr(compound=compound, rankdir=rankdir, ranksep=ranksep, bgcolor=bgcolor,
                       fontcolor=fontcolor, fontsize=fontsize, label=name, newrank=self.__newrank)
        if not self.__args.noLegend:
            self.__legend_cluster.generate(maingraph)  # Adds the legend

        for cluster in self.__clusters.values():
            if cluster is not self.__legend_cluster:
                cluster.generate(maingraph)

        # Need the dot to be added to the enviroment variable to be able to generate the svg directly from the python script
        # so the default should be the dot and then generate the svg from the merged make file
        maingraph.format = 'svg'
        try:
            output_path = os.path.join(self.__args.output, filename+".gv").replace("/",os.path.sep)
            if source_file_only:
                maingraph.save(output_path)
            else:
                #maingraph.render(output_path, view=False) doesn't support long paths
                maingraph.save(output_path)
                svg_file = open(output_path+".svg", "wb")
                svg_file.write(maingraph.pipe())
                svg_file.close()
        except Exception as e:
            print('An exception occurred: {}'.format(e))
            print("error while generating graph " + filename+".gv", file=sys.stderr)


    def generate_graph_per_cluster(self, folder_name, compound='true', rankdir="LR", ranksep="0.2", bgcolor="#F0F0FF", fontcolor="#0000A0", fontsize="13", source_file_only=False):
        """
        generates a graph(svg) for each main cluster
        :param folder_name: the folder name where all graphs shall be generated
        :param compound: if true to allow edges between different clusters
        :param rankdir: set the direction of the graph layout
        :param ranksep: This is the minimum vertical distance between the bottom of the nodes 
        in one rank and the tops of nodes in the next
        :param bgcolor: background color of the generated graph
        :param fontcolor: the color used for text
        :param fontsize: font size used for text
        :param source_file_only: only generate the graphviz source file 
        """
        file_id = 0
        for cluster in self.__clusters.values():
            if cluster is not self.__legend_cluster:
                suffix = cluster.label.replace("\n", ".")
                maingraph = Digraph(comment=suffix)
                maingraph.attr(compound=compound, rankdir=rankdir, ranksep=ranksep, bgcolor=bgcolor,
                               fontcolor=fontcolor, fontsize=fontsize, label=cluster.label, newrank=self.__newrank)
                if not self.__args.noLegend:
                    self.__legend_cluster.generate(
                        maingraph)  # Adds the legend
                cluster.generate(maingraph)  # Add the cluster
                maingraph.format = 'svg'
                if len(suffix) > 100:
                    suffix = suffix[:96]
                    suffix = suffix + "__" + str(file_id)
                    file_id = file_id + 1
                try:
                    output_path = os.path.join(os.path.join(
                        self.__args.output, folder_name), suffix).replace("/",os.path.sep)+".gv"
                    if source_file_only:
                        maingraph.save(output_path)
                    else:
                        #maingraph.render(output_path, view=False) doesn't support long paths
                        maingraph.save(output_path)
                        svg_file = open(output_path+".svg", "wb")
                        svg_file.write(maingraph.pipe())
                        svg_file.close()
                except Exception as e:
                    print('An exception occurred: {}'.format(e))
                    print("error while generating graph " +
                          suffix, file=sys.stderr)

    def get_element_by_id(self, elementid):
        """
        get xml element by its id
        :param elementid: the id of the xml element to return
        :return: the element that have this id and None otherwise
        """
        return self.__all_name_elements.get(elementid)

    def find_and_resolve_reference(self, xml_element, xml_path):
        """
        Resolves an xml idref from a given path of an xml element
        :param xml_element: the xml element that contains the path
        :paramt xml_path: the path of the xml element where the idref is located
        :return: the resolved element or None
        """        
        return self.get_element_by_id(xml_element.findtext(xml_path))

    def find_and_resolve_references(self, xml_element, xml_path):
        """
        Resolves a list of xml idrefs from a given path of an xml element
        :param xml_element: the xml element that contains the path
        :paramt xml_path: the path of the xml element where the idrefs are located
        :return: the resolved elements or an empty list
        """              
        refs = xml_element.findall(xml_path)
        elements = []
        for ref in refs:
            elements.append(self.get_element_by_id(ref.text))
        return elements

    def add_legend(self, style):
        """
        Add legend to the generated graph. This is helpful when 
        there are multiple shapes/colors in a graph and can be used
        to identify each one of them.
        :param style: style of the legend node
        """
        if self.__legend_cluster == None:
            self.__legend_cluster = self.new_cluster(
                '-1', 'Legend for shapes in the diagram')
            self.__clusters['-1'] = self.__legend_cluster
        node_id = style.name + '_legend_node'
        legend_node = Node.get_or_create_node_with_customized_id(
            node_id, self.__nodes, self.__legend_cluster, text=style.name, style=style)
        self.__legend_cluster.add_node(legend_node)

    def set_title(self, title):
        """
        Sets the title of the diagram
        :param title: the title to set
        """         
        self.__title = title
