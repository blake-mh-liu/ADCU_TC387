# \file
#
# \brief Autosar CanTrcv
#
# This file contains the implementation of the Autosar
# module CanTrcv.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2011 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

CanTrcv_CORE_PATH      = $(SSC_ROOT)/CanTrcv_$(CanTrcv_VARIANT)
CanTrcv_OUTPUT_PATH    = $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS          += CanTrcv
CanTrcv_DEPENDENT_PLUGINS := base_make tresos
CanTrcv_VERSION           := 1.00.00
CanTrcv_DESCRIPTION       := CanTrcv Basic Software Makefile PlugIn for Autosar

TRESOS_GEN_FILES   += $(CanTrcv_GEN_FILES)

CC_INCLUDE_PATH      += \
    $(CanTrcv_CORE_PATH)/include                          \
