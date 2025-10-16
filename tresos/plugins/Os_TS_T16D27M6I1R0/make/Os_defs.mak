#
# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \version 6.1.256
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS
ifeq ($(Os_CORE_PATH),)
  AutosarOS_CORE_PATH    = $(PLUGINS_BASE)/Os_TS_T16D27M6I1R0
  AutosarOS_LIB_PATH     = $(PLUGINS_BASE)/Os_$(Os_VARIANT)/lib
else
  AutosarOS_CORE_PATH    = $(realpath $(Os_CORE_PATH)/..)/Os_TS_T16D27M6I1R0
  AutosarOS_LIB_PATH     = $(Os_CORE_PATH)/lib
endif

OS_ARCH := TRICORE
OS_CPU := TC38XQ

include $(AutosarOS_CORE_PATH)/make/Os_definitions.mak
# There is no assembly file for target WINDOWS
ifneq ($(TARGET),WINDOWS)
ifeq (,$(filter $(OS_ASM_FILE_SUFFIX),$(ASM_FILE_SUFFIX))$(filter %.$(OS_ASM_FILE_SUFFIX),$(ASM_FILTER_LIST)))
$(error ASM_FILE_SUFFIX/ASM_FILTER_LIST does not match file names - expected '$(OS_ASM_FILE_SUFFIX)', got '$(ASM_FILE_SUFFIX)/$(ASM_FILTER_LIST)')
endif
endif

#########################
# Editor settings: DO NOT DELETE
# vi:set ts=4:
