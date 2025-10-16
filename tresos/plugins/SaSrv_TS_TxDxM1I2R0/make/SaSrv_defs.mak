#
# \file
#
# \brief AUTOSAR SaSrv
#
# This file contains the implementation of the AUTOSAR
# module SaSrv.
#
# \version 1.2.0
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

SaSrv_CORE_PATH         ?= $(PLUGINS_BASE)/SaSrv_$(SaSrv_VARIANT)

SaSrv_OUTPUT_PATH       ?= $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY

SaSrv_DEPENDENT_PLUGINS := base_make tresos
SaSrv_VERSION           := 1.00.00
SaSrv_DESCRIPTION       := Security Access Server

CC_INCLUDE_PATH        += \
   $(SaSrv_CORE_PATH)/include \
   $(SaSrv_OUTPUT_PATH)/include
