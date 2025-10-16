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

LIB_FILE_SUFFIX    := lib
# rule for own preprocessor provided
build-prep-file-PROVIDED := true

# only do error checking if building
ifneq (,$(GOALS_BUILD))
  ifndef TOOLCHAIN_VERSION
    $(error TOOLCHAIN_VERSION must be defined for toolchain $(TOOLCHAIN))
  else ifeq (,$(filter 1010 1050,$(TOOLCHAIN_VERSION)))
    $(error Unknown version $(TOOLCHAIN_VERSION) for toolchain $(TOOLCHAIN))
  endif
endif

# set path of compiler toolchain
ifeq (1010,$(TOOLCHAIN_VERSION))
  TOOLPATH_COMPILER := $(subst \,/,$(DEVTOOLS_BASE)/mingw-bcgcc-10.1.0)
else ifeq (1050,$(TOOLCHAIN_VERSION))
  TOOLPATH_COMPILER := $(subst \,/,$(DEVTOOLS_BASE)/mingw-gcc-10.5.0-r2)
endif
# ensure the compiler directory is in the path
ifeq (,$(filter $(TOOLPATH_COMPILER)/bin,$(subst ;,$(BLANK),$(subst \,/,$(PATH)))))
  export PATH:=$(subst /,\,$(TOOLPATH_COMPILER)/bin);$(PATH)
endif

CC             := $(TOOLPATH_COMPILER)/bin/gcc.exe
GCC            := $(TOOLPATH_COMPILER)/bin/gcc.exe
CCLIB          := $(TOOLPATH_COMPILER)/bin/ar.exe
LINK           := $(TOOLPATH_COMPILER)/bin/gcc.exe
ASM            := $(TOOLPATH_COMPILER)/bin/gcc.exe
GPP            := $(TOOLPATH_COMPILER)/bin/cpp.exe
DEBUGGER       := $(TOOLPATH_COMPILER)/bin/gdb.exe
OBJCOPY        := $(TOOLPATH_COMPILER)/bin/objcopy.exe
COMPILER_DIR   := $(TOOLPATH_COMPILER)/bin
