"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

from .constants import *
import re
from collections import OrderedDict

# Class representing one node


class Node:
    def __init__(self, id, label, color, shape, clusterid, fontcolor, url):
        """
        CTor creates new Node
        :param id: id of the node
        :param label: text to be added in the node
        :param color: color of the node
        :param shape: the node's generated shape
        :param clusterid: the id of the cluster owns this node
        :param fontcolor: the color of the text for this node
        :param url: link to other diagram
        """
        self.id = id
        self._label = label
        self._color = color if(color is not None) else WHITE
        self._shape = shape if(shape is not None) else ""
        self._clusterid = clusterid if(
            clusterid is not None) else DEFAULT_CLUSTER
        self._fontcolor = fontcolor
        self._url = url

    def generate(self, subgraph):
        """
        generates the node to the given subgraph
        :param subgraph: the subgraph to add the node to
        """
        subgraph.node(self.id, label=self._label, fillcolor=self._color, shape=self._shape, style='filled', fontcolor=self._fontcolor, URL=self._url)

    @staticmethod
    def get_or_create_node(nodes, cluster, xmlelement, text, style, url):
        """
        Create node from the given xmlelement and uses the passed property names 
        as label in the diagram
        :param nodes: dictionary of all nodes to check if the node already exist
        :param cluster: cluster to add the node to
        :param xmlelement: xml element that contains info to create this node
        :param text: text for that node which can contain xml paths that are resolved if written as "{{<xml path>}}"
        :param style: style of the node
        :param url: link to other diagram
        :return: either the already existing node or the newly created one
        """
        element_id = cluster.id + "_" + xmlelement.get("id")
        return Node.get_or_create_node_with_customized_id(element_id, nodes, cluster, xmlelement, text, style, url)

    @staticmethod
    def get_node(nodes, cluster, xmlelement):
        element_id = cluster.id + "_" + xmlelement.get("id")
        return nodes.get(element_id)

    @staticmethod
    def get_or_create_node_with_customized_id(customizedid, nodes, cluster, xmlelement=None, text="", style=None, url=None):
        """
        Create node from the given xmlelement with custom id
        :param customizedid: custom id of the node 
        :param nodes: dictionary of all nodes to check if the node already exist
        :param cluster: cluster to add the node to
        :param xmlelement: xml element that contains info to create this node
        :param text: text for that node which can contain xml paths that are resolved if written as "{{<xml path>}}"
        :param style: style of the node
        :param url: link to other diagram
        :return: either the already existing node or the newly created one
        """
        element_id = customizedid
        node = nodes.get(element_id)
        if node is None:
            if xmlelement is not None:
                template_text_to_value = OrderedDict()
                for m in re.finditer(r"{{([^{}]+)}}", text):
                    xml_expression = m.group(1)
                    value = None
                    if xmlelement.find(xml_expression) is not None:
                        value = xmlelement.find(xml_expression).text
                    else:
                        value = xmlelement.get(xml_expression)
                    template_text_to_value[m.group(0)] = value
                if template_text_to_value:
                    template_text_to_value = OrderedDict(
                        (re.escape(k), v) for k, v in template_text_to_value.items())
                    pattern = re.compile("|".join(template_text_to_value.keys()))
                    text = pattern.sub(
                        lambda m: template_text_to_value[re.escape(m.group(0))], text)
            text = text.replace('\n', '\\n')
            node = Node(element_id, text, style.color,
                        style.shape, cluster.id, style.fontcolor, url)
            nodes[element_id] = node
            cluster.add_node(node)
        return node

    def __repr__(self):
        return 'Node(' + self.id + ',' + self._label + ')'
