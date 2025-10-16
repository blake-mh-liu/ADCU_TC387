#
# \file
#
# \brief AUTOSAR J1939Nm
#
# This file contains the implementation of the AUTOSAR
# module J1939Nm.
#
# \version 1.1.13
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

J1939Nm_lib_FILES      +=

J1939Nm_src_FILES      := $(J1939Nm_CORE_PATH)/src/J1939Nm.c \
                      $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_Cfg.c \
                      $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_Lcfg.c \

LIBRARIES_TO_BUILD += J1939Nm_src

# Fill the list with post build configuration files needed to build the post build binary.
J1939Nm_pbconfig_FILES := $(realpath $(J1939Nm_OUTPUT_PATH)/src/J1939Nm_PBcfg.c)

ifneq ($(strip $(J1939Nm_pbconfig_FILES)),)
LIBRARIES_PBCFG_TO_BUILD += J1939Nm_pbconfig
LIBRARIES_TO_BUILD += J1939Nm_pbconfig
endif

define defineCanIfLibOutputPATH
$(1)_OBJ_OUTPUT_PATH += $(CanIf_lib_LIB_OUTPUT_PATH)
endef

$(foreach SRC,$(basename $(notdir $(subst \,/,$(J1939Nm_lib_FILES)))),$(eval $(call defineCanIfLibOutputPATH,$(SRC))))

# J1939Nm_Wrapper_src_FILES      := $(J1939Nm_Wrapper_OUTPUT_PATH)/src/J1939Nm_Wrapper.c

# LIBRARIES_TO_BUILD += J1939Nm_Wrapper_src
#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




