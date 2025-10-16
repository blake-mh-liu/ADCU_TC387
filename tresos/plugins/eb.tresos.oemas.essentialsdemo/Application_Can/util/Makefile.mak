# \file
#
# \brief AUTOSAR Application_Can
#
# This file contains the implementation of the AUTOSAR
# module Application_Can.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
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

#################################################################
# For GNU Make we must explicitly set SHELL to cmd.exe,
# since otherwise it would try to use sh.exe.
SHELL := cmd.exe

#################################################################
# include merged makefile if it exists
-include $(PROJECT_ROOT)\util\Merged_Makefile.mak

#################################################################
# additional C source files to be built
#################################################################

CC_FILES_TO_BUILD += 

#################################################################
# tresos settings
#################################################################
TRESOS2_WORKSPACE_DIR = $(PROJECT_ROOT)\..
TRESOS2_USER_OPTIONS += -data $(TRESOS2_WORKSPACE_DIR)
TRESOS2_PROJECT_NAME = $(PROJECT_NAME)
TRESOS2_USER_OPTIONS += -Dinfo=false
TRESOS2_USER_OPTIONS += -DmergeConfigs=true

# We want project mode, not legacy.
USE_LEGACY_MAKECFG := false

-include common.mak
