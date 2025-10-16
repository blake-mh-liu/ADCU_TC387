# \file
#
# \brief AUTOSAR Cpl
#
# This file contains the implementation of the AUTOSAR
# module Cpl.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2013 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),CplStub_40)
LIB_VARIANTS += CplStub_40_BASE
endif
endif

CplStub_40_CORE_PATH           := $(SSC_ROOT)\CplStub_40_$(CplStub_40_VARIANT)

CplStub_40_OUTPUT_PATH         := $(AUTOSAR_BASE_OUTPUT_PATH)

CplStub_40_GEN_FILES           :=

CplStub_40_lib_LIB_OUTPUT_PATH := $(CplStub_40_CORE_PATH)\lib

#################################################################
# REGISTRY
SSC_PLUGINS           += CplStub_40
CplStub_40_DEPENDENT_PLUGINS := base_make tresos
CplStub_40_VERSION           := 2.00.00
CplStub_40_DESCRIPTION       := CplStub_40 Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH       += \
   $(CplStub_40_CORE_PATH)\include \
   $(CplStub_40_CORE_PATH)\lib_include \
   $(CplStub_40_OUTPUT_PATH)\include

ASM_INCLUDE_PATH      +=
CPP_INCLUDE_PATH      +=
