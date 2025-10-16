#
# \file
#
# \brief AUTOSAR MicroOs
#
# This file contains the implementation of the AUTOSAR
# module MicroOs.
#
# \version 2.0.232
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2023 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#
# This makefile is used from both the plugin build and the user build environment.
# It must only contain the feature set definitions.
# This file must be compatible with Make on unixoides, so don't use backward slashes in file names.


MK_TRICORE_PREFIX=$(MK_CPUFAMILY_PREFIX)TRICORE$(MK_HYPHEN)

#
# you can add TRICORE specific flags here. Currently not used
#
# PREPROCESSOR_DEFINES += xxxx
# MK_CPUFAMILY_LIB_FLAGS += yyyy

# Editor settings: DO NOT DELETE
# vi:set ts=4:
