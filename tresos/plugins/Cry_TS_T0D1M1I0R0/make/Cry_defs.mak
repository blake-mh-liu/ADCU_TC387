# \file
#
# \brief AUTOSAR Cry
#
# This file contains the implementation of the AUTOSAR
# module Cry.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),Cry)
LIB_VARIANTS                  += Cry_BASE
endif
endif

Cry_CORE_PATH                 ?= $(PLUGINS_BASE)\Cry_$(Cry_VARIANT)
Cry_OUTPUT_PATH               ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Cry_GEN_FILES                 :=

Cry_lib_LIB_OUTPUT_PATH       := $(Cry_CORE_PATH)\lib

#################################################################
# REGISTRY

SSC_PLUGINS                   += Cry
Cry_DEPENDENT_PLUGINS         := base_make tresos
Cry_VERSION                   := 1.00.00
Cry_DESCRIPTION               := Cry Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH               += \
  $(Cry_CORE_PATH)\include     \
  $(Cry_CORE_PATH)\lib_include \
  $(Cry_OUTPUT_PATH)\include

ASM_INCLUDE_PATH              +=
CPP_INCLUDE_PATH              +=

