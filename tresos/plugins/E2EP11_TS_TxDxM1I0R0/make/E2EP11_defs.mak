#
# \file
#
# \brief AUTOSAR E2EP11
#
# This file contains the implementation of the AUTOSAR
# module E2EP11.
#
# \version 1.0.3
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

E2EP11_CORE_PATH         ?= $(PLUGINS_BASE)/E2EP11_$(E2EP11_VARIANT)

E2EP11_OUTPUT_PATH       ?= $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY

E2EP11_DEPENDENT_PLUGINS := base_make tresos
E2EP11_VERSION           := 2.00.00
E2EP11_DESCRIPTION       := E2EP11 Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(E2EP11_CORE_PATH)/include
