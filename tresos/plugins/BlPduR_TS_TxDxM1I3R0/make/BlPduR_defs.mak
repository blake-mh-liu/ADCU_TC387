# \file
#
# \brief Autosar BlPduR
#
# This file contains the implementation of the Autosar
# module BlPduR.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

BlPduR_CORE_PATH         := $(SSC_ROOT)\BlPduR_$(BlPduR_VARIANT)

BlPduR_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += BlPduR
BlPduR_DEPENDENT_PLUGINS := base_make tresos
BlPduR_VERSION           := 1.00.00
BlPduR_DESCRIPTION       := BlPduR Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(BlPduR_CORE_PATH)\include \
   $(BlPduR_OUTPUT_PATH)\include
