#
# \file
#
# \brief AUTOSAR Det
#
# This file contains the implementation of the AUTOSAR
# module Det.
#
# \version 6.5.15
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

Det_src_FILES      := \
    $(Det_CORE_PATH)/src/Det.c \
    $(Det_CORE_PATH)/src/Det_Rte.c \
    $(Det_CORE_PATH)/src/Det_ASR32_Rte.c \
    $(Det_CORE_PATH)/src/Det_ASR40_Rte.c \
    $(Det_CORE_PATH)/src/Det_ASR43_Rte.c

LIBRARIES_TO_BUILD += Det_src

#################################################################
# RULES
