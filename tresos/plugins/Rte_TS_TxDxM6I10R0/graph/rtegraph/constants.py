"""
 Copyright (C) Elektrobit Automotive GmbH
 All rights exclusively reserved for Elektrobit Automotive GmbH,
 unless expressly agreed to otherwise.
"""


class Style:
    def __init__(self, name, shape=None, color=None, fontcolor='black'):
        self.name = name
        self.shape = shape
        self.color = color
        self.fontcolor = fontcolor

# for color names see https://www.graphviz.org/doc/info/colors.html#x11
# for shapes see https://graphviz.org/doc/info/shapes.html

# Guidelines:
# - use rect shape for buffers/memory
#  use oval shape for everything that runs
#  if unsure, use oval shape
# - use red/green color only if you want to show that something is "good" or "bad" e.g. if something is optimized or not
# - use postfix: _STYLE


EVENT_STYLE = Style("Event", "rect", 'lightblue')
TASK_STYLE = Style("Task/Isr", "oval", 'lightgoldenrod')
UNKNOWN_TASK_STYLE = Style("Unkown Task/Isr", "oval", '#D2691E')
EXECUTABLE_STYLE = Style("Runnable/BswModuleEntity", "oval", 'darkseagreen3')
API_STYLE = Style("API", "oval", 'orange')
CALLBACK_STYLE = Style("Callback", "oval", 'darkorange3')
VDI_STYLE = Style("Variable Data Instance", "oval", "lightgrey")
OI_STYLE = Style("Operation Instance", "oval", "mediumslateblue")
PARAMETER_INSTANCE_STYLE = Style(
    "Parameter Data Instance", "oval", "springgreen4")
MODE_DECLARATION_GROUP_INSTANCE_STYLE = Style(
    "Mode Declaration Group Instance", "oval", "pink4")
TRIGGER_INSTANCE_STYLE = Style("Trigger Instance", "oval", "wheat3")
BUFFER_STYLE = Style("Buffer", "rect", "lightskyblue")
DHB_BUFFER_STYLE = Style("Data Handle Buffer", "rect", "lightcyan")
RB_BUFFER_STYLE = Style("Receive Buffer", "rect", "mediumturquoise")
IP_CHANNEL_STYLE = Style("IP Channel", "rect", "powderblue")
SIGNAL_GROUP_MAPPING_STYLE = Style("Signal Group Mapping", "rect", "indianred")
SIGNAL_GROUP_STYLE = Style("Signal Group", "rect", "orchid4")
SIGNAL_STYLE = Style("Signal", "rect", "orchid")
OPTIMIZED_EXCLUSIVE_AREA_STYLE = Style(
    "Optimized Exclusive Area", "ellipse", "limegreen")
NOT_OPTIMIZED_EXCLUSIVE_AREA_STYLE = Style(
    "Not optimized Exclusive Area", "ellipse", "lightcoral")
OPTIMIZATION_REASON_STYLE = Style(
    "Optimization Reason", "rect", "white", "blue")
DATA_CONSISTENCY_STYLE = Style("Data Consistency", "oval", "burlywood")
INTER_RUNNABLE_VARIABLE_STYLE = Style(
    "Interrunnable Variable", "rect", "olivedrab")
EA_STYLE = Style("Interrunnable Variable", "rect", "limegreen")
LOCAL_PARAMETER_INSTANCE_STYLE = Style(
    "Local Parameter Data Instance", "rect", "lightsalmon3")
TIME_STYLE = Style("Time", "rect", "mediumturquoise")
SIMPLE_STYLE = Style("Simple", "oval", "white")
SWC_STYLE = Style("SWC", "rect", "mediumturquoise")
RUNNABLE_CAT1_STYLE = Style("Runnable (category 1)", "oval", 'darkseagreen3')
RUNNABLE_CAT2_STYLE = Style("Runnable (category 2)", "oval", 'lightcoral')
WAITPOINT_STYLE = Style("Waitpoint", "oval", 'firebrick2')
IPDU_STYLE = Style("IPDU", "rect", "gold")
VDI_LOWEST_TIMEOUT_STYLE = Style("Variable Data Instance\nLowest Timeout", "oval", "palegreen")

RECORD = "record"
RECTANGLE = "rectangle"

LIGHT_BLUE = 'lightblue'
YELLOW = 'yellow'
BLACK = 'black'
PINK = 'pink'
RED = 'red'
LIGHT_GREEN = '#90EE90'
WHITE = 'white'
BLUE = 'blue'
BROWN = '#D2691E'

DEFAULT_CLUSTER = 'default'
