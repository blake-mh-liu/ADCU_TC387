#
# \file
#
# \brief AUTOSAR J1939Rm
#
# This file contains the implementation of the AUTOSAR
# module J1939Rm.
#
# \version 1.1.15
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS
J1939Rm_CORE_PATH             ?= $(PLUGINS_BASE)/J1939Rm_$(J1939Rm_VARIANT)
J1939Rm_OUTPUT_PATH           ?= $(AUTOSAR_BASE_OUTPUT_PATH)
J1939Rm_Wrapper_OUTPUT_PATH   := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY

J1939Rm_GEN_FILES             := $(J1939Rm_OUTPUT_PATH)/include/J1939Rm_Cfg.h \
                                 $(J1939Rm_OUTPUT_PATH)/include/J1939Rm_PBcfg.h \
                                 $(J1939Rm_OUTPUT_PATH)/include/J1939Rm_Lcfg.h \
                                 $(J1939Rm_OUTPUT_PATH)/include/J1939Rm_SymbolicNames_PBcfg.h \
                                 $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_Cfg.c \
                                 $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_PBcfg.c \
                                 $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_Lcfg.c \
SSC_PLUGINS           += J1939Rm
J1939Rm_DEPENDENT_PLUGINS := base_make tresos
J1939Rm_VERSION           := 1.00.00
J1939Rm_DESCRIPTION       := J1939Rm Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(J1939Rm_CORE_PATH)/include \
   $(J1939Rm_CORE_PATH)/src                              \
   $(J1939Rm_OUTPUT_PATH)/include
