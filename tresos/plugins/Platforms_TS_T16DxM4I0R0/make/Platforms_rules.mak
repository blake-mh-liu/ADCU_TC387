#
# \file
#
# \brief AUTOSAR Platforms
#
# This file contains the implementation of the AUTOSAR
# module Platforms.
#
# \version 4.0.2
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

#Platforms_src_FILES      := $(Platforms_CORE_PATH)/src\

Platforms_src_FILES      := $(Platforms_MCAL_LIB)

ifneq ($(Platforms_src_FILES),)
LIBRARIES_TO_BUILD += Platforms_src
endif

#################################################################
# RULES
