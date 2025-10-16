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


EXE_FILE_SUFFIX ?=.exe

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT)$(EXE_FILE_SUFFIX)
FIRST_BUILD_TARGET := $(PROJECT_BINARY)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map

CC              = $(TOOLPATH_COMPILER)/bin/bcgcc$(EXE_FILE_SUFFIX)
CCLIB           = $(TOOLPATH_COMPILER)/bin/ar$(EXE_FILE_SUFFIX)
LINK            = $(TOOLPATH_COMPILER)/bin/bcgcc$(EXE_FILE_SUFFIX)
ASM             = $(TOOLPATH_COMPILER)/bin/bcgcc$(EXE_FILE_SUFFIX)
GCC             = $(MAKE_ROOT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)
COMPILER_DIR    = $(TOOLPATH_COMPILER)
# bcgcc compiler is located in /usr/local of cygwin,
# but uses objcopy and debugger of gcc which is located in /bin
OBJCOPY        ?= $(TOOLPATH_COMPILER)/../../bin/objcopy$(EXE_FILE_SUFFIX)
DEBUGGER       ?= $(TOOLPATH_COMPILER)/../../bin/gdb$(EXE_FILE_SUFFIX)

ifeq (,$(realpath $(GCC)))
  $(error FILE DOES NOT EXIST GCC $(GCC))
endif