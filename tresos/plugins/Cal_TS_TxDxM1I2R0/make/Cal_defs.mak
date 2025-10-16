# \file
#
# \brief AUTOSAR Cal
#
# This file contains the implementation of the AUTOSAR
# module Cal.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2013 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),Cal)
LIB_VARIANTS += Cal_BASE
endif
endif

Cal_CORE_PATH           := $(SSC_ROOT)\Cal_$(Cal_VARIANT)

Cal_OUTPUT_PATH         := $(AUTOSAR_BASE_OUTPUT_PATH)

Cal_GEN_FILES           += $(Cal_CORE_PATH)\generate\include\Cal_AsymPublicKeyExtract_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Hash_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_KeyDerive_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_KeyExchange_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_MacGenerate_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_MacVerify_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Random_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_SignatureVerify_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_SymBlockDecrypt_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_SymBlockEncrypt_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_SymDecrypt_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_SymKeyExtract_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Types_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Compress_Cfg.h \
                           $(Cal_CORE_PATH)\generate\include\Cal_Decompress_Cfg.h

Cal_lib_LIB_OUTPUT_PATH := $(Cal_CORE_PATH)\lib

#################################################################
# REGISTRY
SSC_PLUGINS           += Cal
Cal_DEPENDENT_PLUGINS := base_make tresos
Cal_VERSION           := 2.00.00
Cal_DESCRIPTION       := Cal Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH       += \
   $(Cal_CORE_PATH)\include \
   $(Cal_CORE_PATH)\lib_include \
   $(Cal_OUTPUT_PATH)\include

ASM_INCLUDE_PATH      +=
CPP_INCLUDE_PATH      +=

