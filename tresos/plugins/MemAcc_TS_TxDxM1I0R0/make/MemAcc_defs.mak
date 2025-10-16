#
# \file
#
# \brief AUTOSAR MemAcc
#
# This file contains the implementation of the AUTOSAR
# module MemAcc.
#
# \version 1.0.10
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

MemAcc_CORE_PATH         ?= $(PLUGINS_BASE)/MemAcc_$(MemAcc_VARIANT)

MemAcc_OUTPUT_PATH       ?= $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY

MemAcc_DEPENDENT_PLUGINS := base_make tresos
MemAcc_VERSION           := 1.00.00
MemAcc_DESCRIPTION       := MemAcc Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH       += \
   $(MemAcc_CORE_PATH)/include \
   $(MemAcc_OUTPUT_PATH)/include