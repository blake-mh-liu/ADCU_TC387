#
# \file
#
# \brief AUTOSAR J1939Dcm
#
# This file contains the implementation of the AUTOSAR
# module J1939Dcm.
#
# \version 1.1.14
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS
J1939Dcm_CORE_PATH             ?= $(PLUGINS_BASE)/J1939Dcm_$(J1939Dcm_VARIANT)
J1939Dcm_OUTPUT_PATH           ?= $(AUTOSAR_BASE_OUTPUT_PATH)
J1939Dcm_GEN_FILES             := $(J1939Dcm_OUTPUT_PATH)/include/J1939Dcm_PBcfg.h \
                                  $(J1939Dcm_OUTPUT_PATH)/include/J1939Dcm_SymbolicNames_PBcfg.h \
                                  $(J1939Dcm_OUTPUT_PATH)/src/J1939Dcm_PBcfg.c \

TRESOS_GEN_FILES               += $(J1939Dcm_GEN_FILES)
#################################################################
# REGISTRY

J1939Dcm_DEPENDENT_PLUGINS := base_make tresos
J1939Dcm_VERSION           := 1.00.00
J1939Dcm_DESCRIPTION       := J1939Dcm Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    		\
   $(J1939Dcm_CORE_PATH)/include	\
   $(J1939Dcm_CORE_PATH)/src       	\
   $(J1939Dcm_OUTPUT_PATH)/include
