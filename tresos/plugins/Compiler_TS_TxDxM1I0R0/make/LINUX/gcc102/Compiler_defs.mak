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


PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).exe
FIRST_BUILD_TARGET := $(PROJECT_BINARY)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map

#######
# Must be changed when the compiler package is available
TOOLPATH_COMPILER_INTERN := /usr/bin

# check is necessary, TOOLPATH_COMPILER is always set on CC, for LINUX it is set empty
ifeq (,$(strip $(TOOLPATH_COMPILER)))
  # TOOLPATH_COMPILER is set on CC ?= does not work, workaround :=
  TOOLPATH_COMPILER        := $(TOOLPATH_COMPILER_INTERN)
endif
# till here
#######

CC              = $(TOOLPATH_COMPILER)/gcc
GPP             = $(TOOLPATH_COMPILER)/g++
CCLIB           = $(TOOLPATH_COMPILER)/ar
LINK            = $(TOOLPATH_COMPILER)/g++
ASM             = $(TOOLPATH_COMPILER)/gcc
OBJCOPY         = $(TOOLPATH_COMPILER)/objcopy
GCC             = $(TOOLPATH_COMPILER)/cpp

LIB_FILE_SUFFIX = lib

COMPILER_DIR    = $(TOOLPATH_COMPILER)
DEBUGGER        = $(TOOLPATH_COMPILER)/gdb

build-prep-file-PROVIDED := true

flat_filter_opt = $(filter-out -fsanitize%,$1)

ifeq (,$(realpath $(GCC)))
  $(error FILE DOES NOT EXIST GCC $(GCC))
endif

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...

# ensure the compiler directory is in the path!
ifeq (,$(realpath $(subst ;,/libgomp-1.dll ,$(subst \,/,$(PATH));)))
  export PATH:=$(TOOLPATH_COMPILER);$(PATH)
endif

