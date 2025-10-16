# \file
#
# \brief AUTOSAR Application_Can
#
# This file contains the implementation of the AUTOSAR
# module Application_Can.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

# This file contains common compiler options for all TRICORE devices using
# the GNU toolchain.

#################################################################
# Configure MCALs to use OS functions for interrupt mapping
# 0: Use Os function for mapping enable/disable global interrupts
# 1: Use compiler inline functions for mapping enable/disable
#MCALUSEINTRINSICS ?= 0
# DON'T use Os mapping currently cause it does NOT work!
MCALUSEINTRINSICS = 1

# Specify include directory for linker scripts (use '/' instead of '\')
CC_OPT += -I$(TOOLPATH_COMPILER)/tricore/include/machine

# Never use tasking copytable for gnu toolchain
CC_OPT += -DUSE_TASKING_INIT=0

# Specify include directory for compiler headers (use '/' instead of '\')
DEPEND_GCC_OPTS += -I$(TOOLPATH_COMPILER)/tricore/include/machine

# Specify compiler symbol
DEPEND_GCC_OPTS += -D_GNU_C_TRICORE_=1

#################################################################
# Define the default options for the assembler

# Export type of preprocessor
ASM_OPT +=


#################################################################
# Define the options for the linker

# Specify include directory for linker scripts
LINK_OPT += -L$(BOARD_PROJECT_PATH)

# Create a map file
LINK_OPT += -Map=$(MAP_FILE)

# EXT_LOCATOR_FILE:
# specify the name for an external locator file
# if no name is given, a default locator file $(BOARD).ldscript is taken
# which is composed in file <board>.mak
EXT_LOCATOR_FILE +=

#################################################################
# General path setup

# Path where the map file should get generated
MAP_FILE = $(BIN_OUTPUT_PATH)\$(PROJECT).map

# Path where the output file should get generated
OUT_FILE = $(BUILD_DIR)\$(PROJECT).out
