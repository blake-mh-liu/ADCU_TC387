#
# \file
#
# \brief AUTOSAR MemAcc
#
# This file contains the implementation of the AUTOSAR
# module MemAcc.
#
# \version 1.0.10
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

MemAcc_src_FILES :=  \
    $(MemAcc_CORE_PATH)/src/MemAcc.c \
    $(MemAcc_CORE_PATH)/src/MemAcc_Queue.c \
    $(MemAcc_OUTPUT_PATH)/src/MemAcc_Lcfg.c

LIBRARIES_TO_BUILD  += MemAcc_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
