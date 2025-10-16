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




ABS_FILE_SUFFIX=dll
PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
COMPILER_DIR    = $(TOOLPATH_COMPILER)
LIB_FILE_SUFFIX = lib

SBS_BUILD       = $(COMPILER_DIR)/bin/sbsbuild.exe
CC              = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/gcc.exe
GPP             = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/g++.exe
CCLIB           = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/ar.exe
LINK            = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/g++.exe
ASM             = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/gcc.exe
OBJCOPY         = $(COMPILER_DIR)/common/ext-tools/mingw32/bin/objcopy.exe
GCC             = $(MAKE_ROOT)/tools/gcc/bin/cpp.exe


CC_INCLUDE_PATH += $(COMPILER_DIR)/common/include

ifeq (,$(realpath $(SBS_BUILD)))
  $(error FILE DOES NOT EXIST SBS_BUILD $(SBS_BUILD) $(realpath $(SBS_BUILD)))
endif

ifeq (,$(realpath $(CC)))
  $(error FILE DOES NOT EXIST CC $(CC) $(realpath $(CC)))
endif

ifeq (,$(realpath $(CCLIB)))
  $(error FILE DOES NOT EXIST CCLIB $(CCLIB) $(realpath $(CCLIB)))
endif

ifeq (,$(realpath $(ASM)))
  $(error FILE DOES NOT EXIST ASM $(ASM) $(realpath $(ASM)))
endif

ifeq (,$(realpath $(LINK)))
  $(error FILE DOES NOT EXIST LINK $(LINK) $(realpath $(LINK)))
endif

#add compiler dir to PATH variable
export PATH:=$(PATH);$(COMPILER_DIR)/common/ext-tools/mingw32/bin