#
# \file
#
# \brief AUTOSAR J1939Nm
#
# This file contains the implementation of the AUTOSAR
# module J1939Nm.
#
# \version 1.1.13
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS
J1939Nm_CORE_PATH             ?= $(PLUGINS_BASE)/J1939Nm_$(J1939Nm_VARIANT)
J1939Nm_OUTPUT_PATH           ?= $(AUTOSAR_BASE_OUTPUT_PATH)

J1939Nm_GEN_FILES             := $(J1939Nm_OUTPUT_PATH)/include/J1939Nm_Cfg.h \
                                 $(J1939Nm_OUTPUT_PATH)/include/J1939Nm_Lcfg.h \
                                 $(J1939Nm_OUTPUT_PATH)/include/J1939Nm_PBcfg.h \
                                 $(J1939Nm_OUTPUT_PATH)/include/J1939Nm_SymbolicNames_PBcfg.h \
                                 $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_Cfg.c \
                                 $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_Lcfg.c \
                                 $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_PBcfg.c \

J1939Nm_Wrapper_OUTPUT_PATH   := $(AUTOSAR_BASE_OUTPUT_PATH)

TRESOS_GEN_FILES              += $(J1939Nm_GEN_FILES)
#################################################################
# REGISTRY

J1939Nm_DEPENDENT_PLUGINS := base_make tresos
J1939Nm_VERSION           := 1.00.00
J1939Nm_DESCRIPTION       := J1939Nm Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH           +=  $(J1939Nm_CORE_PATH)/include \
                              $(J1939Nm_CORE_PATH)/src \
                              $(J1939Nm_OUTPUT_PATH)/include \
