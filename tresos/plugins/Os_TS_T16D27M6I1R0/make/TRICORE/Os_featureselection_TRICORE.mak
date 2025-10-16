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

#
# This makefile is used from both the plugin build and the user build environment
# It must only include the feature set definitions

DIRMERGE_SETTINGS_TAG_OsFeature_GenericTimestamp ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_CheckForDispatch ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_SharedTimestampAndExecTimer ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_SharedTimestampAndCounterTimer ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericLeaveKernel ?= disabled
