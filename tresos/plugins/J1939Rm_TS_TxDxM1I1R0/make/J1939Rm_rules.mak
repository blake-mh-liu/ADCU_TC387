#
# \file
#
# \brief AUTOSAR J1939Rm
#
# This file contains the implementation of the AUTOSAR
# module J1939Rm.
#
# \version 1.1.15
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

J1939Rm_src_FILES      := $(J1939Rm_CORE_PATH)/src/J1939Rm.c \
                          $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_Lcfg.c   \
                      $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_Cfg.c \
					  

LIBRARIES_TO_BUILD += J1939Rm_src

# Fill the list with post build configuration files needed to build the post build binary.
J1939Rm_pbconfig_FILES := $(realpath $(J1939Rm_OUTPUT_PATH)/src/J1939Rm_PBcfg.c)

ifneq ($(strip $(J1939Rm_pbconfig_FILES)),)
LIBRARIES_PBCFG_TO_BUILD += J1939Rm_pbconfig
LIBRARIES_TO_BUILD += J1939Rm_pbconfig
endif

# J1939Rm_Wrapper_src_FILES      := $(J1939Rm_Wrapper_OUTPUT_PATH)/src/J1939Rm_Wrapper.c

# LIBRARIES_TO_BUILD += J1939Rm_Wrapper_src
#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




