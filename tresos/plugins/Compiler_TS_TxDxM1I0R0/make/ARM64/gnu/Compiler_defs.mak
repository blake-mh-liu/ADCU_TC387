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
ASM_FILE_SUFFIX=s
HEX_FILE_SUFFIX=mot
EXE_FILE_SUFFIX?=.exe

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map
HEXFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(HEX_FILE_SUFFIX)


# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)/bin
CC              = $(COMPILER_DIR)/aarch64-elf-gcc$(EXE_FILE_SUFFIX)
GPP             = $(COMPILER_DIR)/aarch64-elf-g++$(EXE_FILE_SUFFIX)
CCLIB           = $(COMPILER_DIR)/aarch64-elf-ar$(EXE_FILE_SUFFIX)
ASM             = $(CC)
LINK            = $(GPP)
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)
OBJCPY          = $(COMPILER_DIR)/aarch64-elf-objcopy$(EXE_FILE_SUFFIX)

# ------ compiler specific files (and the corresponding checks)
CPP              = $(COMPILER_DIR)/aarch64-elf-g++$(EXE_FILE_SUFFIX)

ifeq (,$(realpath $(CC)))
  $(error FILE DOES NOT EXIST CC $(CC))
endif

ifeq (,$(realpath $(CCLIB)))
  $(error FILE DOES NOT EXIST CCLIB $(CCLIB))
endif

ifeq (,$(realpath $(GCC)))
  $(error FILE DOES NOT EXIST CPP $(GCC))
endif

ifeq (,$(realpath $(CPP)))
  $(error FILE DOES NOT EXIST CPP $(CPP))
endif

