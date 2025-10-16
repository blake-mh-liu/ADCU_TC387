# \file
#
# \brief Autosar SA
#
# This file contains the implementation of the Autosar
# module SA.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

SA_CORE_PATH         := $(SSC_ROOT)\SA_$(SA_VARIANT)

SA_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += SA
SA_DEPENDENT_PLUGINS := base_make tresos
SA_VERSION           := 2.00.00
SA_DESCRIPTION       := SA Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(SA_CORE_PATH)\include \
   $(SA_OUTPUT_PATH)\include
