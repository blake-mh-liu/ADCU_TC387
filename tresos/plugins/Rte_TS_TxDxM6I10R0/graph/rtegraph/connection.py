"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""

# Class for connection between nodes


class Connection:
    def __init__(self, src, dest, label, color, style=None, fontsize='11', direction=None, arrowhead="normal", arrowtail="normal", weight=None, constraint=None):
        """
        CTor creates new Connection
        :param src: source node of the connection
        :param dest: destination node of the connection
        :param label: label to be added on the connection (edge)
        :param color: color of the connection (edge)
        :param style: style of the connection (edge)
        :param fontsize: fontsize of the connection (edge)
        :param direction: direction of the connection (edge)
        :param arrowhead: arrowhead of the connection (edge)
        :param arrowtail: arrowtail of the connection (edge)
        :param weight: weight of the connection (edge)
        :param constraint: constraint of the connection (edge)
        """
        self._src = src
        self._dest = dest
        self._label = label
        self._color = color
        self._style = style
        self._fontsize = fontsize
        self._direction = direction
        self._arrowhead = arrowhead
        self._arrowtail = arrowtail
        self._weight = weight
        self._constraint = constraint

    def generate(self, sub_graph):
        """
        Generates the connection to the sub_graph.
        :param sub_graph: the graph that will contain this self connection
        """
        sub_graph.edge(self._src.id, self._dest.id, label=self._label, color=self._color, style=self._style, fontsize=self._fontsize,
                       dir=self._direction, arrowhead=self._arrowhead, arrowtail=self._arrowtail, weight=self._weight, constraint=self._constraint)

    def get_id(self):
        """
        Gets the unique id of this connection
        """
        return self._src.id + "_" + self._dest.id

    def __repr__(self):
        return 'Connection( src:' + self._src.id + ', dest:' + self._dest.id + ')'
