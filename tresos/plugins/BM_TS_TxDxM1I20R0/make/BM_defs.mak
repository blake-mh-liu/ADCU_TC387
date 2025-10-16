# \file
#
# \brief Autosar BM
#
# This file contains the implementation of the Autosar
# module BM.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

BM_CORE_PATH         := $(SSC_ROOT)\BM_$(BM_VARIANT)

BM_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += BM
BM_DEPENDENT_PLUGINS := base_make tresos
BM_VERSION           := 2.00.00
BM_DESCRIPTION       := BM Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(BM_CORE_PATH)\include \
   $(BM_OUTPUT_PATH)\include
