# \file
#
# \brief Autosar CanTrcv
#
# This file contains the implementation of the Autosar
# module CanTrcv.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2015 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

CanTrcv_src_FILES := $(CanTrcv_CORE_PATH)/src/CanTrcv.c           \

LIBRARIES_TO_BUILD += CanTrcv_src

#################################################################
# RULES
