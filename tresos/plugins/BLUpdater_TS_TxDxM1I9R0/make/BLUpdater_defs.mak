# \file
#
# \brief Autosar BLUpdater
#
# This file contains the implementation of the Autosar
# module BLUpdater.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

BLUpdater_CORE_PATH         := $(SSC_ROOT)\BLUpdater_$(BLUpdater_VARIANT)

BLUpdater_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += BLUpdaterpdater
BLUpdater_DEPENDENT_PLUGINS := base_make tresos
BLUpdater_VERSION           := 1.00.00
BLUpdater_DESCRIPTION       := BLUpdater Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(BLUpdater_CORE_PATH)\include \
   $(BLUpdater_OUTPUT_PATH)\include
