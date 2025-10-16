# \file
#
# \brief AUTOSAR Csm
#
# This file contains the implementation of the AUTOSAR
# module Csm.
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

Csm_lib_FILES                 :=

Csm_src_FILES                 +=                         \
  $(Csm_CORE_PATH)\src\Csm.c                             \
  $(Csm_CORE_PATH)\src\Csm_AsymPrivateKeyWrapAsym.c      \
  $(Csm_CORE_PATH)\src\Csm_AsymPrivateKeyWrapSym.c       \
  $(Csm_CORE_PATH)\src\Csm_AsymPublicKeyExtract.c        \
  $(Csm_CORE_PATH)\src\Csm_Checksum.c                    \
  $(Csm_CORE_PATH)\src\Csm_Hash.c                        \
  $(Csm_CORE_PATH)\src\Csm_MacGenerate.c                 \
  $(Csm_CORE_PATH)\src\Csm_MacVerify.c                   \
  $(Csm_CORE_PATH)\src\Csm_RandomGenerate.c              \
  $(Csm_CORE_PATH)\src\Csm_RandomSeed.c                  \
  $(Csm_CORE_PATH)\src\Csm_SignatureGenerate.c           \
  $(Csm_CORE_PATH)\src\Csm_SignatureVerify.c             \
  $(Csm_CORE_PATH)\src\Csm_SymBlockEncrypt.c             \
  $(Csm_CORE_PATH)\src\Csm_SymBlockDecrypt.c             \
  $(Csm_CORE_PATH)\src\Csm_SymEncrypt.c                  \
  $(Csm_CORE_PATH)\src\Csm_SymDecrypt.c                  \
  $(Csm_CORE_PATH)\src\Csm_SymKeyExtract.c               \
  $(Csm_CORE_PATH)\src\Csm_SymKeyWrapAsym.c              \
  $(Csm_CORE_PATH)\src\Csm_SymKeyWrapSym.c               \
  $(Csm_OUTPUT_PATH)\src\Csm_AsymPrivateKeyWrapAsymCfg.c \
  $(Csm_OUTPUT_PATH)\src\Csm_AsymPrivateKeyWrapSymCfg.c  \
  $(Csm_OUTPUT_PATH)\src\Csm_AsymPublicKeyExtractCfg.c   \
  $(Csm_OUTPUT_PATH)\src\Csm_ChecksumCfg.c               \
  $(Csm_OUTPUT_PATH)\src\Csm_HashCfg.c                   \
  $(Csm_OUTPUT_PATH)\src\Csm_MacGenerateCfg.c            \
  $(Csm_OUTPUT_PATH)\src\Csm_MacVerifyCfg.c              \
  $(Csm_OUTPUT_PATH)\src\Csm_RandomGenerateCfg.c         \
  $(Csm_OUTPUT_PATH)\src\Csm_RandomSeedCfg.c             \
  $(Csm_OUTPUT_PATH)\src\Csm_SignatureGenerateCfg.c      \
  $(Csm_OUTPUT_PATH)\src\Csm_SignatureVerifyCfg.c        \
  $(Csm_OUTPUT_PATH)\src\Csm_SymBlockEncryptCfg.c        \
  $(Csm_OUTPUT_PATH)\src\Csm_SymBlockDecryptCfg.c        \
  $(Csm_OUTPUT_PATH)\src\Csm_SymEncryptCfg.c             \
  $(Csm_OUTPUT_PATH)\src\Csm_SymDecryptCfg.c             \
  $(Csm_OUTPUT_PATH)\src\Csm_SymKeyExtractCfg.c          \
  $(Csm_OUTPUT_PATH)\src\Csm_SymKeyWrapAsymCfg.c         \
  $(Csm_OUTPUT_PATH)\src\Csm_SymKeyWrapSymCfg.c         

LIBRARIES_TO_BUILD            += Csm_src

DIRECTORIES_TO_CREATE         += $(Csm_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD             +=
CPP_FILES_TO_BUILD            +=
ASM_FILES_TO_BUILD            +=

MAKE_CLEAN_RULES              +=
MAKE_GENERATE_RULES           +=
MAKE_COMPILE_RULES            +=
MAKE_CONFIG_RULES             +=
#MAKE_ADD_RULES               +=
#MAKE_DEBUG_RULES             +=

define defineCsmLibOutputPATH
$(1)_OBJ_OUTPUT_PATH          := $(Csm_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(Csm_lib_FILES)))),\
$(eval $(call defineCsmLibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES

