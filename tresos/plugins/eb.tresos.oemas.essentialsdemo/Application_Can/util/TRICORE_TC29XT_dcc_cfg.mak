# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2015 Elektrobit Automotive GmbH
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
TOOLPATH_COMPILER ?= C:/tools/Compiler/Wind_River_Compiler_5.9.4.8-Tricore/WindRiver/diab/5.9.4.8

#################################################################
# Define the options for the compiler

# Target: TC27xAstep16P
# Note: this target is selected by the MCAL options
# M: far absolute addressing
# G: All Single Hardware Floating Point
# cross: Use Ram Disk for I/O
#CPUSWITCH = -tTC27xAstep16PMG:cross

DEPEND_GCC_OPTS += -I$(TOOLPATH_COMPILER)/include/diab
CC_OPT += -I$(TOOLPATH_COMPILER)/include/diab

# Requested by customer
# M: far absolute addressing
# F: single hardware, double software floating point
# cross: Use Ram Disk for I/O
CPUSWITCH = -tTC29x16PMF:cross

# select processor
CC_OPT += $(CPUSWITCH)
CC_OPT += -c

# Follow the C89 standard for C
CC_OPT += -Xdialect-c89
# Disable use of the “COMMON” feature so that the compiler or assembler will allocate each uninitialized public
# variable in the .bss section for the module defining it, and the linker will require exactly one definition of each public
# variable.
CC_OPT += -Xno-common
# Align functions on 4-byte boundaries.
CC_OPT += -Xalign-functions=4
# Favor floating-point performance over conformance to the IEEE754 floating-point standard.
CC_OPT += -Xfp-fast
# Place each function in its own CODE section class.
CC_OPT += -Xsection-split=1
# Always create and keep a .s file without the need for a separate compilation with the -S option
CC_OPT += -Xkeep-assembly-file=2
# Generate symbolic debugger information and do most optimizations.
CC_OPT += -g3
CC_OPT += -ew4084 # turn "invalid combination of type specifiers" (MCAL)

# Disable warnings:
# 4177: entity-kind "entity" was declared but never referenced (MCAL)
# 4550: entity-kind "entity” was set but never used (MCAL)
# 4549: entity-kind "entity” is used before its value is set (MCAL)
# 4068: integer conversion resulted in a change of sign (MCAL)
# 5388: (MCAL, OS)
CC_OPT += -ei4177,4550,4549,4068,5388

# TCDIAB-13607 : Diab throws a wrong warning - "volatile qualifier discarded"
# See https://knowledge.windriver.com/?title=Content_Lookup&id=TCDIAB-13607
CC_OPT += -ei1824

# Enable Standard compiler optimizations
CC_OPT += -XO
# some define from MCAL options
CC_OPT += -D_DIABDATA_C_TRICORE_=1
DEPEND_GCC_OPTS += -D_DIABDATA_C_TRICORE_=1

# Create and keep assembly file
#CC_OPT += -Xkeep-assembly-file
# Output source as comments in assembly file
#CC_OPT += -Xpass-source
# Generate warnings on functions without previous prototype
#CC_OPT += -Xforce-prototypes
# Generate warnings on suspicious/non-portable code.
#CC_OPT += -Xlint
#CC_OPT += -Xlink-time-lint
# Disable debug optimization of type information
#CC_OPT += -Xdebug-struct-all
# Optimize for size rather than speed.
#CC_OPT += -Xsize-opt
#CC_OPT += -ei1516 # disable "parameter x is never used"
#CC_OPT += -ei1517 # disable "function OS_MTCR is never used"
#CC_OPT += -ei1522 # disable "statement not reached"
#CC_OPT += -ei1604 # disable "Useless assignment to variable x. Assigned value not used."
#CC_OPT += -ei1606 # disable "conditional expression or part of it is always true/false"
#CC_OPT += -ei5388 # disable "conversion from pointer to same-sized integral type (potential portability problem)"
#CC_OPT += -ei5844 # disable "function "main" has no prototype"

# the smallest signed or unsigned integer type permitted by the range of values
# for an enumeration that is sufficient to represent the values of the
# enumeration constants is used
CC_OPT += -Xenum-is-best

#################################################################
# Define the default options for the assembler

ASM_OPT += $(CPUSWITCH)
ASM_OPT += -c
# Generate debug line and file information
ASM_OPT += -Xasm-debug-on
# Select DWARF 2 format for debug information
ASM_OPT += -Xdebug-dwarf2

#################################################################
# Define the options for the linker
LINK_OPT += $(CPUSWITCH)
# Generate map file
LINK_OPT += -m6
# Use ELF as output file format
#LINK_OPT += -Xelf
# This one outputs warnings of the type "warning: Cannot find matching input sections"
#LINK_OPT += -Xcheck-input-patterns
# Check for overlapping output sections
#LINK_OPT += -Xcheck-overlapping
# Library with routines for conversions between floating point and other types
#LINK_OPT += -limpfp
# Standard C library
LINK_OPT += -lc
# Use legacy (pre-release 5.6) libraries. This is the default. The new libraries imply C99
#LINK_OPT += -Xlibc-old
# Perform link-time lint
#LINK_OPT += -Xlink-time-lint
# Remove unreferenced sections
#LINK_OPT += -Xremove-unused-sections

# Linker archive options: insert-replace/create/update
AR_OPT += -r -c

# EXT_LOCATOR_FILE:
# specify the name for an external locator file
# if no name is given, a default locator file $(BOARD).ldscript is taken
# which is composed in file <board>.mak
EXT_LOCATOR_FILE +=

