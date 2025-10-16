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


ABS_FILE_SUFFIX   =elf
MAP_FILE_SUFFIX   =map
HEX_FILE_SUFFIX   =mot
EXE_FILE_SUFFIX  ?=.exe

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(MAP_FILE_SUFFIX)
HEXFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(HEX_FILE_SUFFIX)

# override globale make default suffixes
ASM_FILE_SUFFIX   =s

# ------ general files (used in common rules)
# ------ add in {TARGET}_{DERIVATE}_Makefile.mak WIN_TOOLCHAIN_USED ?= WIN64
# ------ this is used to handle the Win path for different Diab compilers from 
# ------ accessible Makefile
ifeq ($(WIN_TOOLCHAIN_USED),WIN64)
  COMPILER_DIR    = $(TOOLPATH_COMPILER)/WIN64/bin
else
  COMPILER_DIR    = $(TOOLPATH_COMPILER)/Win32/bin
endif
CC              = $(COMPILER_DIR)/dcc$(EXE_FILE_SUFFIX)
CCLIB           = $(COMPILER_DIR)/dar$(EXE_FILE_SUFFIX)

# By Default assembler uses 'das.exe' driver. Based on the customer
# request we can use dcc.exe instead. For that set DISABLE_DEFAULT_ASM = YES
# in {TARGET}_{DERIVATE}_{COMPILER}_cfg.mak
# for Diab 7.0.3.0 'asarm.exe' used as assembler

DIAB_VERSION := $(subst diab-,,$(lastword $(subst \, ,$(subst /, ,$(TOOLPATH_COMPILER)))))

ifeq ($(DISABLE_DEFAULT_ASM),YES)
ASM              = $(COMPILER_DIR)/dcc$(EXE_FILE_SUFFIX)
else ifneq (,$(filter 7.0.3.0,$(DIAB_VERSION)))
ASM              = $(TOOLPATH_COMPILER)/../llvm-9.0.1.1/WIN64/bin/asarm$(EXE_FILE_SUFFIX)
else
ASM              = $(COMPILER_DIR)/das$(EXE_FILE_SUFFIX)
endif

# By Default linker uses 'dld.exe' driver. Based on the customer
# request we can use dcc.exe instead. For that set DISABLE_DEFAULT_LINK = YES
# in {TARGET}_{DERIVATE}_Makefile_cfg.mak and define LINK path there.
ifneq ($(DISABLE_DEFAULT_LINK),YES)
LINK            = $(COMPILER_DIR)/dld$(EXE_FILE_SUFFIX)
endif

HEX             = $(COMPILER_DIR)/ddump$(EXE_FILE_SUFFIX)
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)
