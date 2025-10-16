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


#################################################################
# REGISTRY

Cal_lib_FILES      :=

Cal_src_FILES      += $(Cal_CORE_PATH)\src\Cal_AsymPublicKeyExtract.c \
                      $(Cal_CORE_PATH)\src\Cal_Hash.c \
                      $(Cal_CORE_PATH)\src\Cal_KeyDerive.c \
                      $(Cal_CORE_PATH)\src\Cal_KeyExchange.c \
                      $(Cal_CORE_PATH)\src\Cal_MacGenerate.c \
                      $(Cal_CORE_PATH)\src\Cal_MacVerify.c \
                      $(Cal_CORE_PATH)\src\Cal_Random.c \
                      $(Cal_CORE_PATH)\src\Cal_SignatureVerify.c \
                      $(Cal_CORE_PATH)\src\Cal_SymBlockDecrypt.c \
                      $(Cal_CORE_PATH)\src\Cal_SymBlockEncrypt.c \
                      $(Cal_CORE_PATH)\src\Cal_SymDecrypt.c \
                      $(Cal_CORE_PATH)\src\Cal_SymKeyExtract.c \
                      $(Cal_CORE_PATH)\src\Cal_Compress.c \
                      $(Cal_CORE_PATH)\src\Cal_Decompress.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_AsymPublicKeyExtract_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_Hash_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_KeyDerive_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_KeyExchange_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_MacGenerate_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_MacVerify_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_Random_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_SignatureVerify_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_SymBlockDecrypt_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_SymBlockEncrypt_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_SymDecrypt_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_SymKeyExtract_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_Compress_Cfg.c \
                      $(Cal_OUTPUT_PATH)\src\Cal_Decompress_Cfg.c

LIBRARIES_TO_BUILD     += Cal_src

DIRECTORIES_TO_CREATE += $(Cal_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD       +=
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

MAKE_CLEAN_RULES        +=
MAKE_GENERATE_RULES     +=
MAKE_COMPILE_RULES      +=
#MAKE_DEBUG_RULES       +=
MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES         +=


define defineCalLibOutputPATH
$(1)_OBJ_OUTPUT_PATH    := $(Cal_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(Cal_lib_FILES)))),\
$(eval $(call defineCalLibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES

