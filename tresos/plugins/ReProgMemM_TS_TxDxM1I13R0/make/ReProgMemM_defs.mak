# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

ReProgMemM_CORE_PATH         ?= $(PLUGINS_BASE)\ReProgMemM_$(ReProgMemM_VARIANT)

ReProgMemM_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

ReProgMemM_GEN_FILES          = $(ReProgMemM_OUTPUT_PATH)\include\ReProgMemM_Cfg.h        \
                                $(ReProgMemM_OUTPUT_PATH)\include\ReProgMemM_Interfaces.h \
                                $(ReProgMemM_OUTPUT_PATH)\include\ReProgMemM_Types.h      \
                                $(ReProgMemM_OUTPUT_PATH)\src\ReProgMemM_Cfg.c

TRESOS_GEN_FILES       += $(ReProgMemM_GEN_FILES)

#################################################################
# REGISTRY
SSC_PLUGINS            += ReProgMemM

ReProgMemM_DESCRIPTION       := ReprogMemM

CC_INCLUDE_PATH        +=           \
        $(ReProgMemM_CORE_PATH)\include   \
        $(ReProgMemM_OUTPUT_PATH)\include