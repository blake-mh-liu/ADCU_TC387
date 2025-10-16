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

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),Csm)
LIB_VARIANTS                  += Csm_BASE
endif
endif

Csm_CORE_PATH                 := $(SSC_ROOT)\Csm_$(Csm_VARIANT)
Csm_OUTPUT_PATH               := $(AUTOSAR_BASE_OUTPUT_PATH)

Csm_GEN_FILES                 :=                                    \
  $(Csm_CORE_PATH)\generate\include\Csm_Cfg.h                       \
  $(Csm_CORE_PATH)\generate\include\Csm_AsymPrivateKeyWrapAsymCfg.h \
  $(Csm_CORE_PATH)\generate\include\Csm_AsymPrivateKeyWrapSymCfg.h  \
  $(Csm_CORE_PATH)\generate\include\Csm_AsymPublicKeyExtractCfg.h   \
  $(Csm_CORE_PATH)\generate\include\Csm_ChecksumCfg.h               \
  $(Csm_CORE_PATH)\generate\include\Csm_HashCfg.h                   \
  $(Csm_CORE_PATH)\generate\include\Csm_MacGenerateCfg.h            \
  $(Csm_CORE_PATH)\generate\include\Csm_MacVerifyCfg.h              \
  $(Csm_CORE_PATH)\generate\include\Csm_RandomGenerateCfg.h         \
  $(Csm_CORE_PATH)\generate\include\Csm_RandomSeedCfg.h             \
  $(Csm_CORE_PATH)\generate\include\Csm_SignatureGenerateCfg.h      \
  $(Csm_CORE_PATH)\generate\include\Csm_SignatureVerifyCfg.h        \
  $(Csm_CORE_PATH)\generate\include\Csm_SymBlockEncryptCfg.h        \
  $(Csm_CORE_PATH)\generate\include\Csm_SymBlockDecryptCfg.h        \
  $(Csm_CORE_PATH)\generate\include\Csm_SymEncryptCfg.h             \
  $(Csm_CORE_PATH)\generate\include\Csm_SymDecryptCfg.h             \
  $(Csm_CORE_PATH)\generate\include\Csm_SymKeyExtractCfg.h          \
  $(Csm_CORE_PATH)\generate\include\Csm_SymKeyWrapAsymCfg.h         \
  $(Csm_CORE_PATH)\generate\include\Csm_SymKeyWrapSymCfg.h         

Csm_lib_LIB_OUTPUT_PATH       := $(Csm_CORE_PATH)\lib

#################################################################
# REGISTRY

SSC_PLUGINS                   += Csm
Csm_DEPENDENT_PLUGINS         := base_make tresos
Csm_VERSION                   := 2.00.00
Csm_DESCRIPTION               := Csm Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH               += \
  $(Csm_CORE_PATH)\include     \
  $(Csm_CORE_PATH)\lib_include \
  $(Csm_OUTPUT_PATH)\include

ASM_INCLUDE_PATH              +=
CPP_INCLUDE_PATH              +=

