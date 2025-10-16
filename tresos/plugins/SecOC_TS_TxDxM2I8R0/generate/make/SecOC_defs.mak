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

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),SecOC)
LIB_VARIANTS += SecOC_BASE
endif
endif

SecOC_CORE_PATH           ?= $(PLUGINS_BASE)/SecOC_$(SecOC_VARIANT)

SecOC_OUTPUT_PATH         ?= $(AUTOSAR_BASE_OUTPUT_PATH)

SecOC_GEN_FILES           += \
[!SELECT "as:modconf('SecOC')[1]"!]
  [!IF "node:value(SecOCEbGeneral/SecOCRteUsage) = 'true'"!]
    [!LOOP "node:refs(SecOCMainFunctionRx/*/SecOCMainFunctionRxPartitionRef)"!]
      [!VAR "ecucPartition" = "node:name(.)"!]
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Rx_[!"string($ecucPartition)"!].h \
    [!ENDLOOP!]
    [!LOOP "node:refs(SecOCMainFunctionTx/*/SecOCMainFunctionTxPartitionRef)"!]
      [!VAR "ecucPartition" = "node:name(.)"!]
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Tx_[!"string($ecucPartition)"!].h \
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDSELECT!]
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Cfg.h     \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Lcfg.h    \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_PBcfg.h   \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Rx_Cfg.h  \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Tx_Cfg.h  \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_Types.h   \
                             $(SecOC_OUTPUT_PATH)/include/SecOC_SymbolicNames_PBcfg.h

SecOC_lib_LIB_OUTPUT_PATH ?= $(SecOC_CORE_PATH)/lib

#################################################################
# REGISTRY

SecOC_DEPENDENT_PLUGINS := base_make tresos
SecOC_VERSION           := 2.00.00
SecOC_DESCRIPTION       := SecOC Basic Software Makefile PlugIn for AUTOSAR

CC_INCLUDE_PATH       += \
   $(SecOC_CORE_PATH)/include \
   $(SecOC_CORE_PATH)/src \
   $(SecOC_OUTPUT_PATH)/include

ASM_INCLUDE_PATH      +=
CPP_INCLUDE_PATH      +=

