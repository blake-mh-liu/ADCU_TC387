#
# \file
#
# \brief AUTOSAR MicroOs
#
# This file contains the implementation of the AUTOSAR
# module MicroOs.
#
# \version 2.0.232
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2023 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.



#################################################################
# DEFINITIONS

#################################################################
# REGISTRY
LIBRARIES_TO_BUILD     += $(MK_KERNEL_LIB_NAME) $(MK_USER_LIB_NAME)

ifeq ($(MK_SRC_LIB),y)
# create a project library from all src/* or generated files
LIBRARIES_TO_BUILD     += $(MK_SRC_LIB_NAME)

else # $(MK_SRC_LIB) == n

CC_FILES_TO_BUILD += $($(MK_SRC_C_NAME)_FILES)
ASM_FILES_TO_BUILD += $($(MK_SRC_S_NAME)_FILES)

MicroOs_CC_FILES_TO_BUILD += $($(MK_SRC_C_NAME)_FILES)
MicroOs_ASM_FILES_TO_BUILD += $($(MK_SRC_S_NAME)_FILES)

endif # $(MK_SRC_LIB) == y

# Disable code-size computation when GLOBAL_LIB caching is used: There will be
# no compiled object files to compute code size from.
ifneq (,GLOBAL_LIB_ENABLE)
NO_CODESIZE = 1
endif

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES

.PHONY: checkmd5

checkmd5:
	@cd "$(TRESOS2_BASE)" && \
  checksums\checkmd5.bat
