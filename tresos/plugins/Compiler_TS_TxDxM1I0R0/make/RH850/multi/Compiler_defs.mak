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
COMPILER_DIR    = $(TOOLPATH_COMPILER)
CC              = $(COMPILER_DIR)/ccrh850$(EXE_FILE_SUFFIX)
CCLIB           = $(COMPILER_DIR)/ccrh850$(EXE_FILE_SUFFIX)
ASM             = $(COMPILER_DIR)/ccrh850$(EXE_FILE_SUFFIX)
LINK            = $(COMPILER_DIR)/ccrh850$(EXE_FILE_SUFFIX)
HEX             = $(COMPILER_DIR)/gsrec$(EXE_FILE_SUFFIX)
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)

# ------ compiler specific files (and the corresponding checks)

# ------ define compiler specific include paths
CC_INCLUDE_PATH      +=  $(TOOLPATH_COMPILER)/libsys \
                         $(TOOLPATH_COMPILER)/ansi \
                         $(TOOLPATH_COMPILER)/include/v800

CPP_INCLUDE_PATH     +=  $(TOOLPATH_COMPILER)/libsys \
                         $(TOOLPATH_COMPILER)/ansi \
                         $(TOOLPATH_COMPILER)/include/v800

ASM_INCLUDE_PATH     +=  $(TOOLPATH_COMPILER)/libsys \
                         $(TOOLPATH_COMPILER)/ansi \
                         $(TOOLPATH_COMPILER)/include/v800
