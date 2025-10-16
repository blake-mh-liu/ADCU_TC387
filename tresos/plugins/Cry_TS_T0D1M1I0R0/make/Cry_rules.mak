# \file
#
# \brief AUTOSAR Cry
#
# This file contains the implementation of the AUTOSAR
# module Cry.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

Cry_lib_FILES                 :=

Cry_src_FILES                 +=                    \
  $(Cry_CORE_PATH)\src\Cry_AsymPrivateKeyWrapAsym.c \
  $(Cry_CORE_PATH)\src\Cry_AsymPrivateKeyWrapSym.c  \
  $(Cry_CORE_PATH)\src\Cry_AsymPublicKeyExtract.c   \
  $(Cry_CORE_PATH)\src\Cry_Checksum.c               \
  $(Cry_CORE_PATH)\src\Cry_Hash.c                   \
  $(Cry_CORE_PATH)\src\Cry_MacGenerate.c            \
  $(Cry_CORE_PATH)\src\Cry_MacVerify.c              \
  $(Cry_CORE_PATH)\src\Cry_RandomGenerate.c         \
  $(Cry_CORE_PATH)\src\Cry_RandomSeed.c             \
  $(Cry_CORE_PATH)\src\Cry_SignatureGenerate.c      \
  $(Cry_CORE_PATH)\src\Cry_SignatureVerify.c        \
  $(Cry_CORE_PATH)\src\Cry_SymBlockEncrypt.c        \
  $(Cry_CORE_PATH)\src\Cry_SymBlockDecrypt.c        \
  $(Cry_CORE_PATH)\src\Cry_SymEncrypt.c             \
  $(Cry_CORE_PATH)\src\Cry_SymDecrypt.c             \
  $(Cry_CORE_PATH)\src\Cry_SymKeyExtract.c          \
  $(Cry_CORE_PATH)\src\Cry_SymKeyWrapAsym.c         \
  $(Cry_CORE_PATH)\src\Cry_SymKeyWrapSym.c         

LIBRARIES_TO_BUILD            += Cry_src

DIRECTORIES_TO_CREATE         += $(Cry_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD             +=
CPP_FILES_TO_BUILD            +=
ASM_FILES_TO_BUILD            +=

MAKE_CLEAN_RULES              +=
MAKE_GENERATE_RULES           +=
MAKE_COMPILE_RULES            +=
MAKE_CONFIG_RULES             +=
#MAKE_ADD_RULES               +=
#MAKE_DEBUG_RULES             +=

define defineCryLibOutputPATH
$(1)_OBJ_OUTPUT_PATH          := $(Cry_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(Cry_lib_FILES)))),\
$(eval $(call defineCryLibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES

