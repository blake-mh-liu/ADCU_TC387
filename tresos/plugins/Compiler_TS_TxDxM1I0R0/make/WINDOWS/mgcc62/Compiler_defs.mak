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

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...
TOOLPATH_COMPILER_INTERN := $(PLUGINS_BASE)/Platforms_$(Platforms_VARIANT)/tools/mingw-gcc-6.2.0/bin
COMPILER_SFXARCHIVE      := $(PLUGINS_BASE)/Platforms_$(Platforms_VARIANT)/tools/mingw-gcc-6.2.0/MinGw$(EXE_FILE_SUFFIX)

# check is necessary, TOOLPATH_COMPILER is always set on CC, for WINDOWS it is set empty
ifeq (,$(strip $(TOOLPATH_COMPILER)))
  # TOOLPATH_COMPILER is set on CC ?= does not work, workaround :=
  TOOLPATH_COMPILER        := $(TOOLPATH_COMPILER_INTERN)
endif
# till here
#######

CC              = $(TOOLPATH_COMPILER)/gcc$(EXE_FILE_SUFFIX)
GPP             = $(TOOLPATH_COMPILER)/g++$(EXE_FILE_SUFFIX)
CCLIB           = $(TOOLPATH_COMPILER)/ar$(EXE_FILE_SUFFIX)
LINK            = $(TOOLPATH_COMPILER)/g++$(EXE_FILE_SUFFIX)
ASM             = $(TOOLPATH_COMPILER)/gcc$(EXE_FILE_SUFFIX)
OBJCOPY         = $(TOOLPATH_COMPILER)/objcopy$(EXE_FILE_SUFFIX)
GCC             = $(MAKE_ROOT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)

LIB_FILE_SUFFIX = lib

COMPILER_DIR    = $(TOOLPATH_COMPILER)
DEBUGGER        = $(TOOLPATH_COMPILER)/gdb$(EXE_FILE_SUFFIX)

build-prep-file-PROVIDED := true

flat_filter_opt = $(filter-out -fsanitize%,$1)

#######
# needs to be removed if compiler is not in Platforms anymore
# from here ...
# check if internal compiler is used
ifeq ($(TOOLPATH_COMPILER),$(TOOLPATH_COMPILER_INTERN))
  ifeq (,$(realpath $(CC)))
    # compiler not found: unzip it
    OUTPUT_SHELL:= $(shell $(COMPILER_SFXARCHIVE) -y)#-suppresslaunch
  endif
endif
# till here
#######

ifeq (,$(realpath $(CC)))
  $(error FILE DOES NOT EXIST GCC $(CC))
endif

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...

# ensure the compiler directory is in the path!
ifeq (,$(realpath $(subst ;,/libgomp-1.dll ,$(subst \,/,$(PATH));)))
  export PATH:=$(TOOLPATH_COMPILER);$(PATH)
endif

