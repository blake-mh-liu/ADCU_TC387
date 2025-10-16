# \file
#
# \brief AUTOSAR Cpl
#
# This file contains the implementation of the AUTOSAR
# module Cpl.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2013 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS


#################################################################
# REGISTRY

CplStub_40_lib_FILES      :=

CplStub_40_src      += $(CplStub_40_CORE_PATH)\src\Cpl_Stub.c


LIBRARIES_TO_BUILD     += CplStub_40_src

DIRECTORIES_TO_CREATE += $(CplStub_40_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD       +=
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

MAKE_CLEAN_RULES        +=
MAKE_GENERATE_RULES     +=
MAKE_COMPILE_RULES      +=
#MAKE_DEBUG_RULES       +=
MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES         +=


define defineCplStub_40LibOutputPATH
$(1)_OBJ_OUTPUT_PATH    := $(CplStub_40_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(CplStub_40_lib_FILES)))),\
$(eval $(call defineCplStub_40LibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
