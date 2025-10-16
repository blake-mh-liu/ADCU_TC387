#
# \file
#
# \brief AUTOSAR Crypto
#
# This file contains the implementation of the AUTOSAR
# module Crypto.
#
# \version 2.0.39
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#================================================================
# DEFINITIONS

#================================================================
# REGISTRY
[!INCLUDE "../include/Crypto_xVIx_xAIx_Macros.m"!]
[!AUTOSPACING!]

Crypto_xVIx_xAIx_lib_FILES          +=
Crypto_xVIx_xAIx_src_FILES          += \
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!]
[!FOR "i" = "1" TO "$PrimitivesPoolListSize"!]
  [!VAR "primitive" = "string(text:split($PrimitivesPoolListShrt)[position() = $i])"!]
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int_CPr_[!"$primitive"!].c) \
[!ENDFOR!]
[!IF "node:exists(./CryptoKeys)"!]
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_KeyManagement.c) \
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int_KeyManagement.c) \
  [!LOOP "./CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*"!]
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int_KMn_[!"text:replace(node:value(.), 'CRYPTO_KMN_', '')"!].c) \
  [!ENDLOOP!]
[!ENDIF!]
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx.c) \
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int.c) \
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int_Lib_LN.c) \
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/instance/$(Crypto_xVIx_xAIx_INSTANCE)/src/Crypto_xVIx_xAIx_Int_Lib_Ecc.c) \
  $(subst /,\,$(Crypto_xVIx_xAIx_OUTPUT_PATH)/src/Crypto_xVIx_xAIx_Int_Cfg.c)

LIBRARIES_TO_BUILD                  += Crypto_xVIx_xAIx_src
DIRECTORIES_TO_CREATE               += $(Crypto_xVIx_xAIx_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD                   +=
CPP_FILES_TO_BUILD                  +=
ASM_FILES_TO_BUILD                  +=

MAKE_CLEAN_RULES                    +=
MAKE_GENERATE_RULES                 +=
MAKE_COMPILE_RULES                  +=
MAKE_CONFIG_RULES                   +=

define defineCryptoLibOutputPATH
$(1)_OBJ_OUTPUT_PATH                := $(Crypto_xVIx_xAIx_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(Crypto_xVIx_xAIx_lib_FILES)))),$(eval $(call defineCryptoLibOutputPATH,$(SRC))))

#================================================================
# DEPENDENCIES (only for assembler files)
#

#================================================================
# RULES

