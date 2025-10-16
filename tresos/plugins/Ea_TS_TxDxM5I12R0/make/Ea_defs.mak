#
# \file
#
# \brief AUTOSAR Ea
#
# This file contains the implementation of the AUTOSAR
# module Ea.
#
# \version 5.12.23
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

Ea_CORE_PATH      ?= $(PLUGINS_BASE)/Ea_$(Ea_VARIANT)

Ea_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY

Ea_DEPENDENT_PLUGINS := base_make tresos
Ea_VERSION           := 2.00.00
Ea_DESCRIPTION       := Ea Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH      += \
   $(Ea_CORE_PATH)/include \
   $(Ea_OUTPUT_PATH)/include
