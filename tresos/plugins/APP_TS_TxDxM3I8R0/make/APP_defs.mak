# \file
#
# \brief Autosar APP
#
# This file contains the implementation of the Autosar
# module APP.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

APP_CORE_PATH         := $(SSC_ROOT)\APP_$(APP_VARIANT)

APP_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += APP
APP_DEPENDENT_PLUGINS := base_make tresos
APP_VERSION           := 2.00.00
APP_DESCRIPTION       := APP Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=
