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


PROJECT_BINARY      = $(BIN_OUTPUT_PATH)/$(PROJECT).exe
FIRST_BUILD_TARGET := $(PROJECT_BINARY)
MAPFILE             = $(BIN_OUTPUT_PATH)/$(PROJECT).map

LIB_FILE_SUFFIX    := so
LIB_FILE_PREFIX    := lib

# rule for own preprocessor provided
build-prep-file-PROVIDED := true

# only do error checking if building
ifneq (,$(GOALS_BUILD))
  ifndef TOOLCHAIN_VERSION
    $(error TOOLCHAIN_VERSION must be defined for toolchain $(TOOLCHAIN))
  else ifeq (,$(filter 1050,$(TOOLCHAIN_VERSION)))
    $(error Unknown version $(TOOLCHAIN_VERSION) for toolchain $(TOOLCHAIN))
  endif
endif

TOOLPATH_COMPILER := /usr/bin

CC              = $(TOOLPATH_COMPILER)/gcc-10
GCC             = $(TOOLPATH_COMPILER)/gcc-10
CCLIB           = $(TOOLPATH_COMPILER)/ar
LINK            = $(TOOLPATH_COMPILER)/gcc-10
ASM             = $(TOOLPATH_COMPILER)/gcc-10
GPP             = $(TOOLPATH_COMPILER)/cpp-10
DEBUGGER        = $(TOOLPATH_COMPILER)/gdb
OBJCOPY         = $(TOOLPATH_COMPILER)/objcopy
COMPILER_DIR    = $(TOOLPATH_COMPILER)
