#
# \file
#
# \brief AUTOSAR MicroOs
#
# This file contains the implementation of the AUTOSAR
# module MicroOs.
#
# \version 2.0.232
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2023 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.



#################################################################
# DEFINITIONS

MicroOs_CORE_PATH       ?= $(PLUGINS_BASE)/MicroOs_$(MicroOs_VARIANT)

include $(MicroOs_CORE_PATH)/make/Mk_make_translation_layer.mak

MicroOs_INC_PATH        := $(MicroOs_CORE_PATH)/include

MicroOs_SRC_PATH        := $(MicroOs_CORE_PATH)/src
MicroOs_CPUFAMILYSRC_PATH    := $(MicroOs_SRC_PATH)/$(MK_CPUFAMILY)

MicroOs_LIBSRC_PATH     := $(MicroOs_CORE_PATH)/lib_src
MicroOs_LIBSRCCPUFAMILY_PATH := $(MicroOs_LIBSRC_PATH)/$(MK_CPUFAMILY)
MicroOs_LIBSRCKERN_PATH := $(MicroOs_LIBSRC_PATH)/kernel
MicroOs_LIBSRCUSER_PATH := $(MicroOs_LIBSRC_PATH)/user
MicroOs_LIBSRCQM_PATH   := $(MicroOs_LIBSRC_PATH)/QM

MicroOs_MAKE_PATH       := $(MicroOs_CORE_PATH)/make
MicroOs_MAKECPUFAMILY_PATH   := $(MicroOs_MAKE_PATH)/$(MK_CPUFAMILY)
MicroOs_MAKECPU_PATH    := $(MicroOs_MAKECPUFAMILY_PATH)/$(MK_CPU)

ifeq ($(MK_LIB_OUTPUT_BASEPATH),)
# if MK_LIB_OUTPUT_BASEPATH wasn't set or if it is empty, use the default
# we use override here in case someone does a "make MK_LIB_OUTPUT_BASEPATH= depend"
override MK_LIB_OUTPUT_BASEPATH = $(MicroOs_CORE_PATH)/lib/$(MK_CPU)_$(MK_TOOL)
endif

MicroOs_OUTPUT_PATH     ?= $(AUTOSAR_BASE_OUTPUT_PATH)

MicroOs_OUTPUT_INC      := $(MicroOs_OUTPUT_PATH)/include
MicroOs_OUTPUT_SRC      := $(MicroOs_OUTPUT_PATH)/src
MicroOs_OUTPUT_MAKE     := $(MicroOs_OUTPUT_PATH)/make

MicroOs_GEN_FILES       := \
		$(MicroOs_OUTPUT_SRC)/$(MicroOs_SrcFile_prefix)gen_global.c \
		$(MicroOs_OUTPUT_INC)/$(MicroOs_SrcFile_prefix)gen_config.h \
		$(MicroOs_OUTPUT_INC)/$(MicroOs_SrcFile_prefix)gen_user.h \
		$(MicroOs_OUTPUT_MAKE)/$(MicroOs_SrcFile_prefix)gen_objects.make \

MicroOs_SrcFile_prefix  = Mk_
MicroOs_File_prefix     = Mk_
MicroOs_Arch_prefix     = $(MicroOs_File_prefix)$(MK_CPUFAMILY)_

TRESOS_GEN_FILES        += $(MicroOs_GEN_FILES)

#################################################################
# REGISTRY
SSC_PLUGINS               += MicroOs

# Now suck in the architecture- and derivative-specific make definitions
# needed at this early position for possible library build flags
MK_DEF_MAKEDIR := $(MicroOs_MAKE_PATH)
include $(MK_DEF_MAKEDIR)/Mk_defs_includes.mak

# The variable 'MK_MAXCORES' must be defined at this point, so that the
# 'file inclusion mechanism' based on the 'sort' function works properly.
# This mechanism is used in those 'MicroOs_filelists*.mak' files included next.
ifndef MK_MAXCORES
$(error "The variable MK_MAXCORES is not defined. \
Please define it in the file 'Mk_defs_$(MK_CPUFAMILY)_$(MK_CPU).mak'.")
endif

# Include the file lists. Derivative list is only included if present.
-include $(MicroOs_MAKECPU_PATH)/MicroOs_filelists_$(MK_CPU).mak
include $(MicroOs_MAKECPUFAMILY_PATH)/MicroOs_filelists_$(MK_CPUFAMILY).mak
include $(MicroOs_MAKE_PATH)/MicroOs_filelists.mak

ifneq ($(MK_CPUFAMILY_LIB_FLAGS),)
MK_CPUFAMILY_LIB_FLAG_SUFFIX=_$(MK_CPUFAMILY_LIB_FLAGS)
endif

# Names of the libraries
MK_KERNEL_LIB_NAME = MicroOs_libMkKern_n$(MK_CPUFAMILY_LIB_FLAG_SUFFIX)
MK_USER_LIB_NAME   = MicroOs_libMkUser_n$(MK_CPUFAMILY_LIB_FLAG_SUFFIX)

# Now we can construct all the lists of files that asc_Make needs.
$(MK_KERNEL_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCKERN_PATH)/$(MicroOs_File_prefix)k_, \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_LIBSRCKERN_KLIB_BASELIST)))

$(MK_KERNEL_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCCPUFAMILY_PATH)/$(MicroOs_Arch_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C)))

$(MK_KERNEL_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCCPUFAMILY_PATH)/$(MicroOs_Arch_prefix), \
		$(addsuffix .$(ASM_FILE_SUFFIX), \
			$(MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S)))

$(MK_USER_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCUSER_PATH)/$(MicroOs_File_prefix)u_, \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_LIBSRCUSER_ULIB_BASELIST)))

$(MK_USER_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCQM_PATH)/$(MicroOs_File_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_LIBSRCQM_ULIB_BASELIST)))

$(MK_USER_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCCPUFAMILY_PATH)/$(MicroOs_Arch_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_LIBSRCCPUFAMILY_ULIB_BASELIST_C)))

$(MK_USER_LIB_NAME)_FILES += \
	$(addprefix $(MicroOs_LIBSRCCPUFAMILY_PATH)/$(MicroOs_Arch_prefix), \
		$(addsuffix .$(ASM_FILE_SUFFIX), \
			$(MK_LIBSRCCPUFAMILY_ULIB_BASELIST_S)))

# list for non lib C and S files
MK_SRC_C_NAME     = MicroOs_srcMkC
MK_SRC_S_NAME     = MicroOs_srcMkS
# possibility to put all together in one lib
MK_SRC_LIB_NAME   = MicroOs_libMk_src

$(MK_SRC_C_NAME)_FILES += \
	$(addprefix $(MicroOs_SRC_PATH)/$(MicroOs_SrcFile_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_SRC_CFG_BASELIST)))

$(MK_SRC_C_NAME)_FILES += \
	$(addprefix $(MicroOs_OUTPUT_SRC)/$(MicroOs_SrcFile_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_GEN_CFG_BASELIST)))

$(MK_SRC_C_NAME)_FILES += \
	$(addprefix $(MicroOs_CPUFAMILYSRC_PATH)/$(MicroOs_SrcFile_prefix), \
		$(addsuffix .$(CC_FILE_SUFFIX), \
			$(MK_SRCCPUFAMILY_BASELIST_C)))

$(MK_SRC_S_NAME)_FILES += \
	$(addprefix $(MicroOs_CPUFAMILYSRC_PATH)/$(MicroOs_SrcFile_prefix), \
		$(addsuffix .$(ASM_FILE_SUFFIX), \
			$(MK_SRCCPUFAMILY_BASELIST_S)))

$(MK_SRC_LIB_NAME)_FILES = $($(MK_SRC_C_NAME)_FILES) $($(MK_SRC_S_NAME)_FILES)

DIRECTORIES_TO_CREATE += $(MK_LIB_OUTPUT_BASEPATH)

ifneq ($(BUILD_MODE),LIB)
DIRECTORIES_TO_CREATE += $(MK_LIB_OUTPUT_BASEPATH)/$(MK_KERNEL_LIB_NAME)
DIRECTORIES_TO_CREATE += $(MK_LIB_OUTPUT_BASEPATH)/$(MK_USER_LIB_NAME)
endif

$(MK_KERNEL_LIB_NAME)_LIB_OUTPUT_PATH = $(MK_LIB_OUTPUT_BASEPATH)
$(MK_USER_LIB_NAME)_LIB_OUTPUT_PATH = $(MK_LIB_OUTPUT_BASEPATH)

ifneq ($(BUILD_MODE),LIB)

define defineMkKernOutputPATH
$(1)_OBJ_OUTPUT_PATH = $(MK_LIB_OUTPUT_BASEPATH)/$(MK_KERNEL_LIB_NAME)
endef

define defineMkUserOutputPATH
$(1)_OBJ_OUTPUT_PATH = $(MK_LIB_OUTPUT_BASEPATH)/$(MK_USER_LIB_NAME)
endef

else

define defineMkKernOutputPATH
$(1)_OBJ_OUTPUT_PATH = $(PROJECT_ROOT)/output/obj
endef

define defineMkUserOutputPATH
$(1)_OBJ_OUTPUT_PATH = $(PROJECT_ROOT)/output/obj
endef

endif

define defineMkSrcOutputPATH
$(1)_OBJ_OUTPUT_PATH = $(PROJECT_ROOT)/output/obj
endef

# Standard include paths
CC_INCLUDE_PATH += $(MicroOs_OUTPUT_INC)
CC_INCLUDE_PATH += $(MicroOs_INC_PATH)

CPP_INCLUDE_PATH += $(MicroOs_OUTPUT_INC)
CPP_INCLUDE_PATH += $(MicroOs_INC_PATH)

ASM_INCLUDE_PATH += $(MicroOs_OUTPUT_INC)
ASM_INCLUDE_PATH += $(MicroOs_INC_PATH)
ASM_INCLUDE_PATH += $(PROJECT_ROOT)/include

# define output paths for all intermediate files - we store them next to their libraries
$(foreach SRC,$(basename $(notdir $(subst \,/,$($(MK_KERNEL_LIB_NAME)_FILES)))),$(eval $(call defineMkKernOutputPATH,$(SRC))))
$(foreach SRC,$(basename $(notdir $(subst \,/,$($(MK_USER_LIB_NAME)_FILES)))),$(eval $(call defineMkUserOutputPATH,$(SRC))))
$(foreach SRC,$(basename $(notdir $(subst \,/,$($(MK_SRC_C_NAME)_FILES)))),$(eval $(call defineMkSrcOutputPATH,$(SRC))))
$(foreach SRC,$(basename $(notdir $(subst \,/,$($(MK_SRC_S_NAME)_FILES)))),$(eval $(call defineMkSrcOutputPATH,$(SRC))))
$(foreach SRC,$(basename $(notdir $(subst \,/,$($(MK_SRC_LIB_NAME)_FILES)))),$(eval $(call defineMkSrcOutputPATH,$(SRC))))

