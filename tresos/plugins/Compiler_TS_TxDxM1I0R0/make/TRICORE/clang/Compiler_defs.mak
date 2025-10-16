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
EXE_FILE_SUFFIX=.exe


PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map

# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)/bin
CC              = $(COMPILER_DIR)/clang$(EXE_FILE_SUFFIX)
GPP             = $(COMPILER_DIR)/ld.lld$(EXE_FILE_SUFFIX)
CCLIB           = $(COMPILER_DIR)/llvm-ar$(EXE_FILE_SUFFIX)
ASM             = $(CC)
LINK            = $(COMPILER_DIR)/ld.lld$(EXE_FILE_SUFFIX)
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)


# Clang binutils supports 'llvm-objcopy.exe' and 'tricore-objcopy' driver. By Default binutils uses 'llvm-objcopy.exe' driver.
# Based on the installed compiler package we can use either of them. For using 'tricore-objcopy.exe' set DISABLE_DEFAULT_OBJCPY=YES
# in {TARGET}_{DERIVATE}_Makefile_cfg.mak.
# For full installation              : tricore-objcopy.exe
# For custom / minimal installation  : llvm-objcopy.exe

ifeq ($(DISABLE_DEFAULT_OBJCPY),)
$(error DISABLE_DEFAULT_OBJCPY is not defined. Please check Compiler_defs.mak of the toolchain)
endif

ifneq ($(DISABLE_DEFAULT_OBJCPY),YES)
OBJCPY          = $(COMPILER_DIR)/llvm-objcopy$(EXE_FILE_SUFFIX)
HEX_FILE_SUFFIX=ihex
else
ifneq (,$(wildcard $(TOOLPATH_COMPILER)/bin/tricore-objcopy.exe))
$(info OBJCPY = tricore-objcopy.exe is used as full installation is detected)
OBJCPY          = $(COMPILER_DIR)/tricore-objcopy$(EXE_FILE_SUFFIX)
HEX_FILE_SUFFIX=srec
else
$(error tricore-objcopy.exe is not found as custom / minimal installation is detected. Use full installation to use tricore-objcopy.exe) 
endif
endif

# ------ compiler specific files (and the corresponding checks)
CPP              = $(CC)

