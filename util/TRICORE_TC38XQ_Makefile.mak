# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2018 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# BOARD:
# This variable defines the used hardware (it is called board because
# of the usage of evaluation boards).
#
# For example:
# BOARD = eva168_2
#
BOARD_DEFAULT  = TriboardTC387TH
BOARD         ?= $(BOARD_DEFAULT)$(BOARD_SUFFIX)

#################################################################
# TARGET:
# default target of this project
TARGET      ?= TRICORE
DERIVATE    ?= TC38XQ

#################################################################
# COMPIlER:
# The build structure of the SSC allows to switch the compiler by
# changing the used compiler plugin. A compiler plugin is a set
# of makefile that implements the "Compiler Makefile Interface".
# Up to four makefile belongs to such an interface. These makefiles are:
#
# $(PROJECT_ROOT)\util\<compiler_plugin>_cfg.mak
# $(PROJECT_ROOT)\core\plugins\<compiler_plugin>_check.mak
# $(PROJECT_ROOT)\core\plugins\<compiler_plugin>_defs.mak
# $(PROJECT_ROOT)\core\plugins\<compiler_plugin>_rules.mak
#
# The variable COMPILER must contain the name of one <compiler_plugin>.
#
# For example:
# COMPILER = tricore_tasking
#
# Tasking is the default toolchain for TRICORE
#
TOOLCHAIN    ?= tasking
COMPILER     ?= ${TARGET}_${DERIVATE}_${TOOLCHAIN}

#add DEPEND_GCC_OPTS to remove depend error for DEM Events
DEPEND_GCC_OPTS     += -D__$(TARGET) -DDEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES

#################################################################
# ASM_FILES_TO_BUILD:
# The variable ASM_FILES_TO_BUILD should contain a list of assembler files.
# These files will be built to object files.
#
# For example:
# ASM_FILES_TO_BUILD = $(PROJECT_ROOT)\source\asm\myasmfile.asm vectortable.asm
# or
# ASM_FILES_TO_BUILD = $(PROJECT_ROOT)\source\asm\myasmfile.asm \
#	$(PROJECT_ROOT)\source\application\vectortable.asm
#
# The suffix _ASM_OPT allows the definition of special options for the
# assembler.
#
# myasmfile_ASM_OPT = ->special assembler options for a file
#
ASM_FILES_TO_BUILD += 

#################################################################
# EXCLUDE_MAKE_DEPEND :
# exclude files from dependency processing
#
EXCLUDE_MAKE_DEPEND += 

