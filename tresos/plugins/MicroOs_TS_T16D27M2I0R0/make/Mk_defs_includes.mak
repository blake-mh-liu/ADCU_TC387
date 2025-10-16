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
#
# The purpose of this file is to make sure that all defs and feature files are included in the same order
# in plugin and user build environment.
#

ifndef MK_DEFS_INCLUDES_MAK
MK_DEFS_INCLUDES_MAK := 1

-include $(BUNDLE_BASE)/src/Autosar/make/$(TARGET)/Mk_derivates_$(TARGET).mak
MK_CPUFAMILY ?= $(TARGET)
MK_CPU ?= $(DERIVATE)


# Check whether we know our path.
ifeq ($(MK_DEF_MAKEDIR),)
$(error MK_DEF_MAKEDIR is not set.)
endif
ifeq ($(MK_CPUFAMILY),)
$(error MK_CPUFAMILY is not set.)
endif
ifeq ($(MK_CPU),)
$(error MK_CPU is not set.)
endif

# Now actually include these files.
# We don't use the ?= operator for these variables.
# Instead we go from general to specialized, so more specialized files can override
# the variables of more general files.
#
# - Mk_defs_$(MK_CPUFAMILY).mak:
#       Contains default values for the current MK_CPUFAMILY.
#       This are variables which can also be found in C headers as well as explicitly set features.
# - Mk_defs_$(MK_CPUFAMILY)_$(MK_CPU).mak:
#       Contains values for the current derivative.
#       This are variables which can also be found in C headers as well as explicitly set features.
# - Mk_derived_features_$(MK_CPUFAMILY).mak:
#       Derives target-specific feature variables from the C header variables
#       which were defined in the first two headers.
# - Mk_derived_features.mak:
#       Derives common feature variables from the C header variables
#       which were defined in the first two headers.
#
include $(MK_DEF_MAKEDIR)/$(MK_CPUFAMILY)/Mk_defs_$(MK_CPUFAMILY).mak
-include $(MK_DEF_MAKEDIR)/$(MK_CPUFAMILY)/$(MK_CPU)/Mk_defs_$(MK_CPUFAMILY)_$(MK_CPU).mak
-include $(MK_DEF_MAKEDIR)/$(MK_CPUFAMILY)/Mk_derived_features_$(MK_CPUFAMILY).mak
include $(MK_DEF_MAKEDIR)/Mk_derived_features.mak


endif
# include guard
