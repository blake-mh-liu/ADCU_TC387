# \file
#
# \brief Autosar Uds
#
# This file contains the implementation of the Autosar
# module Uds.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Uds_CORE_PATH         := $(SSC_ROOT)\Uds_$(Uds_VARIANT)

Uds_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += Uds
Uds_DEPENDENT_PLUGINS := base_make tresos
Uds_VERSION           := 2.00.00
Uds_DESCRIPTION       := Uds Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(Uds_CORE_PATH)\include \
   $(Uds_OUTPUT_PATH)\include
