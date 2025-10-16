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

#################################################################
# Toolchain settings
#################################################################
# TOOLPATH_COMPILER:
# Path to the tasking compiler and linker.
# It is checked, if an environment variable
# $(SSC_TRICORE_277_TOOLPATH_COMPILER) exists.
# If so, this variable is taken for TOOLPATH_COMPILER
# If it doesn't exist, TOOLPATH_COMPILER must be set by user
# (modify command in line following the ifeq).
#
# For example:
TOOLPATH_COMPILER ?= C:\tools\Compiler\TASKING\TriCore_v5.0r2\ctc

#################################################################
# TASKING_MODE:
#
# To compile a C source file the C compiler and the assembler must
# be called. This can be done by one call of the control program cctc
# or by a call of the compiler ctc and the assembler astc. The variable
# TASKING_MODE allows to select the kind of the tool chain call.
# Valid values are CONTROL_PROGRAM and COMPILER_ASSEMBLER.
TASKING_MODE = CONTROL_PROGRAM


#################################################################
# Define the options for the compiler


# select processor
CC_OPT += --core=tc1.6.x

# Keep intermediate files.
CC_OPT += -t

# Compile in ISO-C:99 mode
CC_OPT += --iso=99

# Set TriCore EABI compliant mode (don't use half-word alignment)
CC_OPT += --eabi-compliant

# --integer-enumeration: always treat enum-types as int (32 bit)
# Tasking: http://issues.tasking.com/?issueid=160-39612
CC_OPT += --integer-enumeration

# Specify source language option:
# - no ISO C99 comments (double-slash)
# - no gcc extensions
# - optimize across volatile accesses
# - unrelaxed const check for string literals
CC_OPT += --language=-comments,-gcc,+volatile,-strings

# choose optimal code for switches
CC_OPT += --switch=auto

# minimum alignment = 0 (default)
CC_OPT += --align=0

# 0 byte threshold for putting data in __near field.
# This prevents the compiler from moving data out of sections,
# where the OS expects it to be located for its protection features.
CC_OPT += --default-near-size=0

# threshold for putting data in __a0 field
CC_OPT += --default-a0-size=0

# threshold for putting data in __a1 field
CC_OPT += --default-a1-size=0

# Optimize: "more" (default), no compact, no forward store, no const propagation
# -OO: Switch off "Forward store" optimization
# Tasking: http://issues.tasking.com/?issueid=160-39613
# -OP: Switch off "Constant propagation" optimization
# Tasking: http://issues.tasking.com/?issueid=160-38438
CC_OPT += -O2ROP

# Optimize for code size (0=speed, ..., 4=code size)
CC_OPT += --tradeoff=4

# Generate symbolic debug information
CC_OPT += -g

# Merge C source code with generated assembly code in the output
CC_OPT += --source

# Option only available for compiler v5...
#CC_OPT += --fp-model=cflnrStz

# Add definition of the used Tricore architecture for the OS
CC_OPT += -DOS_TRICOREARCH=OS_TRICOREARCH_16EP

# Add definition of the used target cpu for the OS
CC_OPT += -DOS_CPU=OS_TC29XT

# use extended Compiler_CfgExtMcal.h
CC_OPT += -DCOMPILERCFG_EXTENSION_MCAL_FILE

# define ECUM_PROVIDE_LEGACY_SYMBOLIC_NAMES
CC_OPT += -DECUM_PROVIDE_LEGACY_SYMBOLIC_NAMES

ASM_OPT += -mt
ASM_OPT += -g

# Select target cpu
ASM_OPT += -D__CPU_TC29XT__ -D__CPU__=tc29x

# Add debug information
ASM_OPT += -gAHLs

# Emit locals EQU and non-EQU symbols (docu: "-equs")
ASM_OPT += --emit-locals=-equ,-symbols

# Allow generic instructions, optimize instruction size
ASM_OPT += -Ogs

# Set maximum number of emitted errors
ASM_OPT += --error-limit=42


#################################################################
# Define the options for the linker

# Tell linker about LINK_PLACE options
LINK_OPT += $(LINK_PLACE)

# Link against the C library
LINK_OPT += -lc
# Link again the rt library (64 bit support)
LINK_OPT += -lrt
LINK_OPT += -I$(BOARD_PROJECT_PATH)
LINK_OPT += -M$(MAP_FILE)
LINK_OPT += -OCLtxY
# link library for fpu
LINK_OPT +=--library=fp_fpu
# Safety Os requires its own initialization code
LINK_OPT += --user-provided-initialization-code
LINK_OPT += --munch
LINK_OPT += -t
# Linker archive options: insert-replace/create/update
AR_OPT += -rcu

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

#################################################################
# Define the options for preprocessing *.s files before being fed
# into the assembler.

# Add definition of the used Tricore architecture for the OS
ASS_OPT += -DOS_TRICOREARCH=OS_TRICOREARCH_16EP

