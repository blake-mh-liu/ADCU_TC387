#
# \file
#
# \brief AUTOSAR ApplTemplates
#
# This file contains the implementation of the AUTOSAR
# module ApplTemplates.
#
# \version 6.8.0
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# Disclaimer:
# >>>  Use of an alternative build environment may  <<<
# >>> lead to non-executable or non-compilable code <<<
# 
# Use the build environment delivered with EB tresos AutoCore to
# execute and compile code. If you use an alternative build
# environment, your EB tresos AutoCore version may generate
# non-executable or non-compilable code.
#################################################################

# provide a default target, if nobody else does
.PHONY: default all
default: all
all:

#################################################################
# path sanitation & sensible default project name if none is specified (predefined or overridden later)
WORK_BASE		:= $(subst \,/,$(WORK_BASE))
TEST_BASE		:= $(subst \,/,$(TEST_BASE))
PROJECT_ROOT		:= $(subst \,/,$(PROJECT_ROOT))
PROJECT_NAME		?= $(lastword $(subst /, ,$(PROJECT_ROOT)))
GEN_OUTPUT_PATH		?= $(PROJECT_ROOT)/output/generated
OVERRIDE_GEN_OUTPUT_PATH := $(GEN_OUTPUT_PATH)
TRESOS2_PROJECT_NAME	?= $(PROJECT_NAME)

#################################################################
# include merged makefile if they exist
-include $(PROJECT_ROOT)/util/Merged_Makefile.mak

include common.mak
