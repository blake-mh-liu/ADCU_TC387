# \file
#
# \brief ProgOEMInd
#
# This file contains the implementation of the 
# module ProgOEMInd.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

ProgOEMInd_CORE_PATH         := $(SSC_ROOT)\ProgOEMInd_$(ProgOEMInd_VARIANT)

ProgOEMInd_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += ProgOEMInd
ProgOEMInd_DEPENDENT_PLUGINS := base_make tresos
ProgOEMInd_VERSION           := 2.00.00
ProgOEMInd_DESCRIPTION       := ProgOEMInd Basic Software Makefile PlugIn
CC_INCLUDE_PATH       +=    \
   $(ProgOEMInd_CORE_PATH)\include \
   $(ProgOEMInd_OUTPUT_PATH)\include
