"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

from collections import OrderedDict

# Class representing one Cluster


class Cluster(object):
    def __init__(self, id, label, color, style, url):
        """
        CTor creates new Cluster
        :param id: id of the new cluster
        :param label: label to be added in the graph for the cluster
        :param color: background color
        :param style: style
        :param url: link to other diagram
        """
        self._id = id
        self.label = label
        self._color = color
        self._nodes = OrderedDict()
        self.clusters = OrderedDict()
        self._ranks = OrderedDict()
        self._connections = OrderedDict()
        self._style = style
        self._url = url
        self.parent = None
        self.rank = None

    def add_cluster(self, cluster):
        """
        Adds a sub-cluster inside the current cluster.
        :param cluster: the cluster to be added
        """
        self.clusters[cluster.id] = cluster
        cluster.parent = self

    @property
    def id(self):
        return (self.parent.id + "_" + self._id) if self.parent is not None else self._id

    @id.setter
    def id(self, value):
        self._id = id

    def add_node(self, node):
        """
        Adds a node to the cluster.
        :param node: node to be added
        """
        self._nodes[node.id] = node

    def _get_last_added_node(self):
        """
        :return: the last node added to the cluster
        """
        last_key = list(self._nodes.keys())[- 1]
        return self._nodes[last_key]

    def add_connection(self, connection):
        """
        Adds a connection to the cluster.
        :param connection: connection to be added
        """
        self._connections[connection.get_id()] = connection

    def generate(self, main_graph):
        """
        Generate the contents(nodes, connection, sub-clusters etc) inside the cluster.
        :param main_graph: the graph that will contain this self cluster
        """
        with main_graph.subgraph(name='cluster' + self.id) as sub_graph:
            sub_graph.attr(label=self.label, style=self._style,
                           color=self._color, rankdir="TB", rank=self.rank, URL=self._url)
            if len(self.clusters) > 0:
                for cluster in self.clusters.values():
                    cluster.generate(sub_graph)
            for node in self._nodes.values():
                node.generate(sub_graph)
            for connection in self._connections.values():
                connection.generate(sub_graph)

    def __repr__(self):
        return 'Cluster(' + self.label + ',' + str(self.id) + ')'
