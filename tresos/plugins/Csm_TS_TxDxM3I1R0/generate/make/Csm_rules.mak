#
# \file
#
# \brief AUTOSAR Csm
#
# This file contains the implementation of the AUTOSAR
# module Csm.
#
# \version 3.1.33
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
[!INCLUDE "../include/Csm_Macros.m"!]
[!AUTOSPACING!]

Csm_lib_FILES                       +=
Csm_src_FILES                       += \
[!SELECT "as:modconf('Csm')[1]"!]
  [!IF "$Csm_Rte_Enabled_All = 'true'"!]
    [!LOOP "node:refs(CsmMainFunction/*/CsmMainFunctionPartitionRef)"!]
      [!VAR "vEcucPartition" = "node:name(.)"!]
      [!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $vEcucPartition]))"!]
  $(Csm_OUTPUT_PATH)/src/Csm_[!"string($vEcucPartition)"!].c \
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDSELECT!]
  $(Csm_CORE_PATH)/src/Csm.c           \
  $(Csm_CORE_PATH)/src/Csm_Int.c       \
  $(Csm_OUTPUT_PATH)/src/Csm_Cfg.c     \
  $(Csm_OUTPUT_PATH)/src/Csm_Int_Cfg.c

LIBRARIES_TO_BUILD                  += Csm_src
DIRECTORIES_TO_CREATE               += $(Csm_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD                   +=
CPP_FILES_TO_BUILD                  +=
ASM_FILES_TO_BUILD                  +=

MAKE_CLEAN_RULES                    +=
MAKE_GENERATE_RULES                 +=
MAKE_COMPILE_RULES                  +=
MAKE_CONFIG_RULES                   +=
#MAKE_ADD_RULES                      +=
#MAKE_DEBUG_RULES                    +=

$(foreach SRC,$(basename $(notdir $(Csm_lib_FILES))),$(eval $(SRC)_OBJ_OUTPUT_PATH:=(Csm_lib_LIB_OUTPUT_PATH)))

#================================================================
# DEPENDENCIES (only for assembler files)

#================================================================
# RULES

