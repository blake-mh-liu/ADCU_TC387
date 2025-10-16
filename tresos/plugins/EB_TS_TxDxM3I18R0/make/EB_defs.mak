# \file
#
# \brief Autosar EB
#
# This file contains the implementation of the Autosar
# module EB.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

EB_CORE_PATH         := $(SSC_ROOT)\EB_$(EB_VARIANT)

EB_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += EB
EB_DEPENDENT_PLUGINS := base_make tresos
EB_VERSION           := 2.00.00
EB_DESCRIPTION       := EB Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(EB_CORE_PATH)\include \
   $(EB_OUTPUT_PATH)\include
