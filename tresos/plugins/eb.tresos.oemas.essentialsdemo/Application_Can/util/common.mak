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
# UTIL_DIR:
# The user can define own makefiles in the util directory
# of the application (included by name pattern by global.mak)
UTIL_DIR := $(PROJECT_ROOT)\util

#################################################################
# GEN_OUTPUT_PATH:
# output location for generated files, use default location
# if not set from environment
#
GEN_OUTPUT_PATH ?= $(PROJECT_ROOT)\output\generated

#################################################################
# MAKE_CFG:
# File which defines the location of the EB tresos Studio plugin
# make. This file must be created before the build process is
# started in order to find the build environment used in this
# particular project.
#
MAKE_CFG := $(GEN_OUTPUT_PATH)\make\Make_cfg.mak

# USE_LEGACY_MAKECFG: If 'true' generate $(MAKE_CFG) in legacy mode,
# otherwise in project mode.
ifndef USE_LEGACY_MAKECFG
ifeq ($(TESTING_USE_PROJECTIMPORT),true)
USE_LEGACY_MAKECFG := false
else
USE_LEGACY_MAKECFG := $(if $(TRESOS2_PROJECT_NAME),false,true)
endif
endif #USE_LEGACY_MAKECFG

-include $(MAKE_CFG)

#################################################################
# include platform specific makefiles
#
-include $(strip $(TARGET))_Makefile.mak
-include $(strip $(TARGET))_$(strip $(DERIVATE))_Makefile.mak

#################################################################
# PROJECT_NAME:
# This variable defines the project name or merely the architecture
# independent part of the  project name used for creating
# the fully expanded name of the project (Make variable PROJECT).
# If it is not set explicitly the directory name is taken as project
# name
#
PROJECT_NAME ?= $(notdir $(subst /util,,$(CURDIR)))

#################################################################
# PROJECT:
# This variable defines the project name and thus the final names
# of the generated files.
#
PROJECT := $(TARGET)_$(DERIVATE)_$(PROJECT_NAME)

#################################################################
# setup CPU
#
CPU ?= $(TARGET)

#################################################################
# set TOOLPATH_COMPILER from user environment if possible
#
ifneq ($(TOOLPATH_COMPILER_$(TARGET)),)
TOOLPATH_COMPILER ?= $(TOOLPATH_COMPILER_$(TARGET))
endif

#################################################################
# CC_FILES_TO_BUILD:
# The variable CC_FILES_TO_BUILD should contain a list of C source
# files which are built in to object files.
#
# For example:
# CC_FILES_TO_BUILD = $(PROJECT_ROOT)\source\application\test\file1.c \
#   $(PROJECT_ROOT)\source\application\test\file2.c \
#   $(PROJECT_ROOT)\source\application\test\file3.c
#
# ATTENTION:
# Please use the following syntax: *.c
#
# The _INCLUDE and the _CC_OPT suffixes can be used for each source file
# in order to define a special include path or own compiler options for
# the source file.
#
# For example:
# file1_CC_OPT =   -> use special compiler options
# file1_INCLUDE =  -> use special include path
#
CC_FILES_TO_BUILD += $(wildcard $(PROJECT_ROOT)/source/template/*.c) \
                     $(wildcard $(PROJECT_ROOT)/source/template/$(TARGET)/*.c) \
                     $(wildcard $(PROJECT_ROOT)/source/template/$(TARGET)/$(DERIVATE)/*.c) \
                     $(wildcard $(PROJECT_ROOT)/source/stubs/*.c) \
                     $(wildcard $(PROJECT_ROOT)/source/stubs/$(TARGET)/*.c) \
                     $(wildcard $(PROJECT_ROOT)/source/stubs/$(TARGET)/$(DERIVATE)/*.c) \
		     $(wildcard $(PROJECT_ROOT)/output/generated/templates/CanTrcv_Callout_Stubs.c)

#################################################################
# CPP_FILES_TO_BUILD:
# The variable CPP_FILES_TO_BUILD should contain a list of C++ source
# files which are built in to object files.
#
# For example:
# CPP_FILES_TO_BUILD = $(PROJECT_ROOT)\source\application\test\file4.cpp \
#   $(PROJECT_ROOT)\source\application\test\file5.cpp \
#   $(PROJECT_ROOT)\source\application\test\file6.cpp
#
# ATTENTION:
# Please use the following syntax: *.cpp
#
# The _INCLUDE and the _CPP_OPT suffixes can be used for each source file
# in order to define a special include path or own compiler options for
# the source file.
#
# For example:
# file4_CPP_OPT =   -> use special compiler options
# file4_INCLUDE =  -> use special include path
#
#
CPP_FILES_TO_BUILD +=

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
# LIBRARIES_TO_BUILD:
# The variable LIBRARIES_TO_BUILD is a list that should contains the
# names of all application libraries. These libraries are used to
# manage all source files of the application. In this makefile two
# further entries are necessary for each application library. One
# specifies the directory where the source files of the library can be
# found, the other specifies the name of the source files that should
# be used to build the library.
# For example:
# LIBRARIES_TO_BUILD = modell_blinker modell_light
#
# modell_blinker_PATH = C:\Work\ecu_projects\application\m_blinker
# modell_blinker_FILES = blinker_main.c blinker_init.c blinker_cyclic.c
#
# modell_light_PATH = C:\Work\ecu_projects\application\m_ligth
# modell_light_FILES = light_main.c light_on.c light_off.c
#
# The following optional suffixes can be used for each source file:
# _INCLUDE and _CC_OPT
#
# source_file_name_INCLUDE  -> the include paths for this source file
# source_file_name_CC_OPT   -> the compiler options for this source file
#
# For example:
# light_main_INCLUDE = C:\Work\ecu_projects\application\m_light\include
# light_main_CC_OPT = -my own compiler options-
#
# ATTENTION:
# After changing the LIBRARIES_TO_BUILD, the following option is necessary:
# make depend
# Otherwise you get an inconsistent build structure.
#
# ATTENTION:
# Blanks are not allowed in directories and file names!
#
# ATTENTION:
# If make reports an error like -The input line is too long- by calling
# the linker or the library builder the count of configured libraries
# (or source files per library) will be to long.
#
# The count of configurable libraries is limited. The limitation of
# libraries depends on the version of the windows prompt (cmd.exe)
# witch depends on the used operating system. The program make use the
# windows prompt to call the linker. Therefore the length of a linker
# call and the length of a library builder call has the limitation
# of the windows prompt. The maximal length of
# a cmd.exe command is:
#
# Windows XP	8196 characters
# Windows 2000	2048 characters
#
LIBRARIES_TO_BUILD +=

#################################################################
# LIBRARIES_LINK_ONLY:
# This variable defines additional libraries. These libraries are
# not building during the build process. They must exist therefore.
#
# For example:
# LIBRARIES_LINK_ONLY = c:\Programme\matlab\libs\matlab.a
#
LIBRARIES_LINK_ONLY +=

#################################################################
# OBJECTS_LINK_ONLY :
# This variable defines additional objects. These objects are
# not building during the build process. They must exist therefore.
#
# For example:
# OBJECTS_LINK_ONLY = c:\Programme\matlab\libs\matlabobj.obj
#
OBJECTS_LINK_ONLY   +=

#################################################################
# CC_INCLUDE_PATH, CPP_INCLUDE_PATH and ASM_INCLUDE_PATH:
# The paths to own user include files. The paths must be preceded
# by no option . If more than one path is used, you will have
# to separate them by spaces.
#
# For example:
# CC_INCLUDE_PATH= c:\ssc_st10\my_include_folder \
#                    c:\more_includes
#
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\stubs
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\stubs\$(TARGET)
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\stubs\$(TARGET)\$(DERIVATE)
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\template
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\template\$(TARGET)
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\template\$(TARGET)\$(DERIVATE)
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\boards\$(BOARD)
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\config
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\output\generated\templates
CC_INCLUDE_PATH  += $(PROJECT_ROOT)\source\config\$(TOOLCHAIN)
CPP_INCLUDE_PATH +=
ASM_INCLUDE_PATH += $(PROJECT_ROOT)\source\boards\$(BOARD)

#################################################################
# The Application Makefile (Makefile.mak) contains the variable
# COMPILER_MODE. This variable defines, how the include paths and
# the flags (parameters) will be passed to the compiler. Normally,
# all parameters are passed by the windows command line but
# Windows 2000 has a restriction of 2048 characters
# (Windows XP - 8192). Therefore the Customer Build Environment
# supports up to three different compiler parameter modes.
#
# GLOBAL_OPTION_FILE:
# Before calling the compiler, a global parameter file is
# created by the Compiler Makefile Plugin. This file contains
# all include paths and the compiler flags. It is used
# for all source files. This means that the options
# <source_file>_CC_OPT and <source_file>_INCLUDE have no effect.
# This is the initial compiler mode.
#
# NO_OPTION_FILE mode:
# All parameters are passed using the command line. If the include
# paths are longer than the limitations of the command line,
# the make run will abort with an error message.
#
# LOCAL_OPTION_FILE:
# If the value LOCAL_OPTION_FILE is set, a parameter file with
# the include paths and compiler flags will be created for each
# source file. The make process will be VERY slow when this option
# is used. The advantage is, that different include path and
# parameters can be defined for every source file. If you do not
# need this feature, you should not use this option.
#
COMPILER_MODE ?= GLOBAL_OPTION_FILE

#################################################################
# global preprocessor options:
# (setting of controller family/derivate)
#
PREPROCESSOR_DEFINES   += ts_arch_family ts_arch_derivate
ts_arch_family_KEY     := TS_ARCH_FAMILY
ts_arch_derivate_KEY   := TS_ARCH_DERIVATE
ts_arch_family_VALUE   := TS_$(CPU)
ts_arch_derivate_VALUE := TS_$(DERIVATE)

#################################################################
# DEPEND_GCC_OPTS:
# The gcc compiler is used to solve the dependencies for all source
# files. The command -make depend- creates a dependency file for
# each source file in the folder [output/depend] Some source files
# contain preprocessor statements which will cause an error if an
# expected macro will not exists. Therefore the variable DEPEND_GCC_OPTS
# allows the definition of macros for the preprocessor of the gcc
# compiler.
#
# ATTENTION:
# If the gcc reports any errors by calling the command make depend
# you must add own macros to the variable DEPEND_GCC_OPTS to solve this
# problem.
#
DEPEND_GCC_OPTS +=

#################################################################
# UTILITIES:
#
UTILITIES +=

#################################################################
# EXCLUDE_MAKE_DEPEND :
# exclude files from dependency processing
#
# XXX: in board directories
#
EXCLUDE_MAKE_DEPEND +=

#################################################################
# ATTENTION:
# In order to increase the speed of executing make commands, the checking of
# the user configuration can be switched off. This is only to be
# done if this makefile contains a real valid configuration.
# In order to disable the configuration checks, use the value YES for
# the variable DISABLE_CONFIGURATION_CHECKS. Afterwards if errors occur
# you should set the value of DISABLE_CONFIGURATION_CHECKS back to NO.
#
DISABLE_CONFIGURATION_CHECKS = NO

ifeq ($(USE_LEGACY_MAKECFG),true)
#################################################################
# include the project settings  (legacy mode only)
#################################################################
-include $(PROJECT_ROOT)\util\project_settings.mak
endif

#################################################################
# enable the generic compiler plugin if it isn't already enabled
#################################################################
ifeq ($(filter compiler,$(COMPILER)),)
COMPILER += compiler
endif

#################################################################
# setup TRESOS_BASE and TRESOS2_BASE
#################################################################
TRESOS2_BASE := $(TRESOS_BASE)
SSC_ROOT     ?= $(TRESOS2_BASE)\plugins

#################################################################
# The version of this makefile
USER_MAKEFILE_VERSION =

#################################################################
# first target to initially set up the project configuration;
# this target shall be only invoked for the default target;
# if a specific target is given, skip the rule
#################################################################
all: $(MAKE_CFG)
mak: $(MAKE_CFG)

#################################################################
# NOW start build process

#################################################################
# Check the variable SSC_ROOT. Blanks are not allowed.
ifneq ($(word 2,$(SSC_ROOT)),)
$(error The variable SSC_ROOT=$(SSC_ROOT) is not valid. Blanks are not \
allowed in this variable. Please edit the file launch.bat and change the \
name of the directory SSC_ROOT)
endif
#################################################################
# Check mandatory variables are not empty
ifeq ($(TARGET),)
$(error The variable TARGET is not set)
endif
ifeq ($(DERIVATE),)
$(error The variable DERIVATE is not set)
endif
ifeq ($(TOOLCHAIN),)
$(error The variable TOOLCHAIN is not set)
endif
ifeq ($(PROJECT_ROOT),)
$(error The variable PROJECT_ROOT is not set)
endif
ifeq ($(TRESOS_BASE),)
$(error The variable TRESOS_BASE is not set)
endif

#################################################################
# Include the global makefile to start the build process

ifeq ($(wildcard $(subst \,/,$(PROJECT_ROOT)/util/global.mak)), )
# Check the variable Make_VARIANT
# The include of global.mak shall only be done if the file can
# be found.
# When a project is generated for the first time, Make_VARIANT
# is not yet set, thus global.mak cannot be found.
# use default global.mak
-include $(SSC_ROOT)\Make_$(Make_VARIANT)\make\global.mak
else
# global.mak exist in the util folder of the application
-include $(PROJECT_ROOT)\util\global.mak
endif

#################################################################
# generate linker file when all object files are known
-include $(BOARD_PROJECT_PATH)\$(BOARD)_link.mak

#################################################################
# For debugging purposes: target that prints environment into
# log file "make.set.log".
generate_env:
	set > make.set.log

#################################################################
# Targets to generate the build environment config file

ifeq ($(USE_LEGACY_MAKECFG),true)

# legacy mode

$(MAKE_CFG):
	@echo **********************************************
	@echo * GENERATING build environment config (legacy)
	@if not exist $(dir $@) mkdir $(dir $@)
	@echo TRESOS2_ECU_ID           := ECU > $@
	@echo PROJECT_OUTPUT_PATH      := $(PROJECT_ROOT)\output>> $@
	@echo GEN_OUTPUT_PATH          := $$(PROJECT_OUTPUT_PATH)\generated>> $@
	@echo AUTOSAR_BASE_OUTPUT_PATH := $$(GEN_OUTPUT_PATH)>> $@
	@echo **********************************************

# for tests in project mode but with legacy Make_cfg.mak,
# remove the file generated by tresos Studio after the "make generate" call,
# and let it recreate by the build environment on the next make call
ifneq ($(TRESOS2_PROJECT_NAME),)
generate:
	@del $(MAKE_CFG)
endif

else

# project mode

# Do not replace "$(TRESOS_BASE)\bin\tresos_cmd.bat" with variable
# $(TRESOS2_GENERATOR) as the makefile where it is defined cannot
# be included before $(MAKE_CFG) is created and included
$(MAKE_CFG):
	@echo ****************************************
	@echo * GENERATING build environment config
ifneq ($(TRESOS2_USE_TMP_WORKSPACE),)
	@if exist $(TRESOS2_TMPWKSP) del /f /s /q $(TRESOS2_TMPWKSP) > nul
	call $(TRESOS_BASE)\bin\tresos_cmd.bat -data $(TRESOS2_TMPWKSP) importProject $(PROJECT_ROOT)
	call $(TRESOS_BASE)\bin\tresos_cmd.bat $(TRESOS2_USER_OPTIONS) -data $(TRESOS2_TMPWKSP) make generate_project_data $(TRESOS2_PROJECT_NAME)
else
	call $(TRESOS_BASE)\bin\tresos_cmd.bat $(TRESOS2_USER_OPTIONS) make generate_project_data $(TRESOS2_PROJECT_NAME)
endif
	@echo ****************************************

endif
