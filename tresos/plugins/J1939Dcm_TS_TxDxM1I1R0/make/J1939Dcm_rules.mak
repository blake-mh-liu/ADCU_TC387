#
# \file
#
# \brief AUTOSAR J1939Dcm
#
# This file contains the implementation of the AUTOSAR
# module J1939Dcm.
#
# \version 1.1.14
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

J1939Dcm_src_FILES      := $(J1939Dcm_CORE_PATH)/src/J1939Dcm.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM03_11.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM04_25.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM05.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM19.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM20.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM21.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM26.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM29.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_internal.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_ReportDTC.c \
                           $(J1939Dcm_OUTPUT_PATH)/src/J1939Dcm_Lcfg.c \
                           $(J1939Dcm_CORE_PATH)/src/J1939Dcm_DM13.c

LIBRARIES_TO_BUILD += J1939Dcm_src

# Fill the list with post build configuration files needed to build the post build binary.
J1939Dcm_pbconfig_FILES := $(wildcard $(J1939Dcm_OUTPUT_PATH)/src/J1939Dcm_PBcfg.c)

# only add J1939Dcm_pbconfig to the libraries to build if there are really post-build config files
# present
ifneq ($(strip $(J1939Dcm_pbconfig_FILES)),)
LIBRARIES_PBCFG_TO_BUILD += J1939Dcm_pbconfig
LIBRARIES_TO_BUILD += J1939Dcm_pbconfig
endif

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




