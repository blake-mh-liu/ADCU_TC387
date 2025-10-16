#
# \file
#
# \brief AUTOSAR SecOC
#
# This file contains the implementation of the AUTOSAR
# module SecOC.
#
# \version 2.8.14
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS
[!AUTOSPACING!]

#################################################################
# REGISTRY

SecOC_lib_FILES      :=

SecOC_src_FILES      += \
[!SELECT "as:modconf('SecOC')[1]"!]
  [!IF "node:value(SecOCEbGeneral/SecOCRteUsage) = 'true'"!]
    [!LOOP "node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef)"!]
      [!VAR "ecucPartition" = "node:name(.)"!]
                        $(SecOC_OUTPUT_PATH)/src/SecOC_Rx_[!"string($ecucPartition)"!].c \
    [!ENDLOOP!]
    [!LOOP "node:refs(SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)"!]
      [!VAR "ecucPartition" = "node:name(.)"!]
                        $(SecOC_OUTPUT_PATH)/src/SecOC_Tx_[!"string($ecucPartition)"!].c \
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDSELECT!]
                        $(SecOC_CORE_PATH)/src/SecOC.c           \
                        $(SecOC_CORE_PATH)/src/SecOC_Rx.c        \
                        $(SecOC_CORE_PATH)/src/SecOC_Tx.c        \
                        $(SecOC_OUTPUT_PATH)/src/SecOC_Lcfg.c    \
                        $(SecOC_OUTPUT_PATH)/src/SecOC_PBcfg.c   \
                        $(SecOC_OUTPUT_PATH)/src/SecOC_Rx_Cfg.c  \
                        $(SecOC_OUTPUT_PATH)/src/SecOC_Tx_Cfg.c

LIBRARIES_TO_BUILD     += SecOC_src

# Fill the list with post build configuration files needed to build the post build binary.
SecOC_pbconfig_FILES := $(wildcard $(SecOC_OUTPUT_PATH)/src/SecOC_PBcfg.c)

ifneq ($(strip $(SecOC_pbconfig_FILES)),)
LIBRARIES_PBCFG_TO_BUILD += SecOC_pbconfig
LIBRARIES_TO_BUILD += SecOC_pbconfig
endif

DIRECTORIES_TO_CREATE += $(SecOC_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD       +=
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

MAKE_CLEAN_RULES        +=
MAKE_GENERATE_RULES     +=
MAKE_COMPILE_RULES      +=
MAKE_CONFIG_RULES       +=

define defineSecOCLibOutputPATH
$(1)_OBJ_OUTPUT_PATH    := $(SecOC_lib_LIB_OUTPUT_PATH)
endef

$(foreach SRC,$(basename $(notdir $(subst \,/,$(SecOC_lib_FILES)))),\
$(eval $(call defineSecOCLibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES

