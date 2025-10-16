#
# \file
#
# \brief AUTOSAR Compiler
#
# This file contains the implementation of the AUTOSAR
# module Compiler.
#
# \version 1.0.16
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2017 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


ABS_FILE_SUFFIX=elf
#define ASM_FILE_SUFFIX as workaround for Os (ASCOS-5483)
ASM_FILE_SUFFIX=asm
HEX_FILE_SUFFIX=mot
EXE_FILE_SUFFIX?=.exe

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map
HEXFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(HEX_FILE_SUFFIX)


# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)/bin
ifneq ($(DISABLE_DEFAULT_CC),YES)
CC              = $(COMPILER_DIR)/arm-eabi-gcc$(EXE_FILE_SUFFIX)
endif
ifneq ($(DISABLE_DEFAULT_CCLIB),YES)
CCLIB           = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/ar$(EXE_FILE_SUFFIX)
endif
ASM             = $(CC)
ifneq ($(DISABLE_DEFAULT_LINK),YES)
LINK            = $(COMPILER_DIR)/arm-eabi-ld$(EXE_FILE_SUFFIX)
endif
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)


# ------ compiler specific files (and the corresponding checks)
ifneq ($(DISABLE_DEFAULT_CPP),YES)
CPP              = $(COMPILER_DIR)/arm-eabi-cpp$(EXE_FILE_SUFFIX)
endif
