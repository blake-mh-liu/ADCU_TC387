#
# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \version 6.1.256
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#
# This makefile is used from both the plugin build and the user build environment
# It must only include the feature set definitions

# List of all Os features with individual file selection
#  - CheckForDispatch: Provide the OS_CheckForDispatch function to the hw-specific part
#  - GenericLeaveKernel: Enable to include generic leave kernel function
#  - GenericReturnFromCall: Enable to include generic return from call implementation
#  - GenericTimestamp: enable the generic timestamp functionality of the kernel
#  - SharedTimestampAndCounterTimer: Enable if the timestamp and a hw counter can share a timer
#  - SharedTimestampAndExecTimer: Enable if the timestamp and execution timer can share a timer
#  - CacheOperations: Enable if software operations to ensure cache coherency are needed. Disable
#                     if no cache is used on RAMs at all, or if the hardware takes care of coherency
#
#  - GenericMMU: generic MMU support functionality in the kernel
#  - GenericMMU_GetMem: with GenericMMU, use the plain Os_GetMem() function
#  - GenericMMU_GetMemAlign: with GenericMMU, use the OS_GetMemAligned() function
#  - GenericMMU_PageMap with GenericMMU, use the generic page mapper
#  - GenericMMU_PadReadOnly with GenericMMU, use the generic function for padding read-only RAM regions
#
#  - Multicore: Enabled on multicore processors
OS_FEATURELIST := \
	ARC_MPUv2 ARC_DWTimer PADecoratedStorage CheckForDispatch CacheOperations \
	ARMSpinlocks ARM_SEMA42 ARM_MPUv8 ARM_TIMER_ARC ARM_TIMER_BTM ARM_TIMER_DTM ARM_TIMER_EPIT ARM_TIMER_FS_STM \
	ARM_TIMER_GLOBALTIMER ARM_TIMER_GPT ARM_TIMER_INTRVL ARM_TIMER_GPTIMER ARM_TIMER_MTU ARM_TIMER_N \
	ARM_TIMER_PMU ARM_TIMER_RLT ARM_TIMER_TI_ECAP ARM_TIMER_TI_EPWM ARM_TIMER_TI_GPT \
	ARM_TIMER_TI_RTI ARM_TIMER_TMR ARM_TIMER_TMU ARM_TIMER_TTC ARM_TIMER_MCT ARM_TIMESTAMP_GPTIMER \
	ARM_TIMESTAMP_OTC ARM_INT_GIC ARM_INT_GICV3 ARM_INT_IUNIT ARM_INT_TI_VIM \
	ARM_INT_TI_VIM_HW_PRIO ARM_INT_VIC ARM_INT_VICV2 ARM_INT_TI_VIM_SW CM_CPUSS CM_FPU\
	GenericLeaveKernel GenericReturnFromCall GenericTimestamp GenericMMU GenericMMU_GetMem \
	GenericMMU_GetMemAlign GenericMMU_PageMap GenericMMU_PadReadOnly \
	SharedTimestampAndCounterTimer SharedTimestampAndExecTimer Multicore \
	PA_DPM PA_SIU PA_MC CM_EXACCESS_MONITOR PA_timer_EMIOS PA_timer_STM PA_timer_PIC PA_PIC PA_MMU \
	PA_SMPU PA_MPU PA_MPU0

# only needs to be there if the derivative needs to override the defaults defined below
-include $(OS_FEATURELIST_MAKEDIR)/$(TARGET)/$(OS_CPU)/Os_featureselection_$(TARGET)_$(OS_CPU).mak

# only needs to be there if the architecture needs to override the defaults defined below
-include $(OS_FEATURELIST_MAKEDIR)/$(TARGET)/Os_featureselection_$(TARGET).mak

DIRMERGE_SETTINGS_TAG_OsFeature_ARMSpinlocks ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_SEMA42 ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_MPUv8 ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_ARC ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_BTM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_DTM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_EPIT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_FS_STM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_GLOBALTIMER ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_GPT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_INTRVL ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_GPTIMER ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_MTU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_N ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_PMU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_RLT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TI_ECAP ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TI_EPWM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TI_GPT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TI_RTI ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TMR ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TMU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_TTC ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMER_MCT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMESTAMP_GPTIMER ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_TIMESTAMP_OTC ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_GIC ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_GICV3 ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_IUNIT ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_TI_VIM_HW_PRIO ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_TI_VIM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_VIC ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_VICV2 ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARM_INT_TI_VIM_SW ?= disabled

DIRMERGE_SETTINGS_TAG_OsFeature_CM_CPUSS ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_CM_FPU ?= disabled

# Exlusive load/store instructions work on single-core derivatives. For multi-core derivatives
# they only work if some sort of global monitors are implemented.
DIRMERGE_SETTINGS_TAG_OsFeature_CM_EXACCESS_MONITOR ?= enabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARC_MPUv2 ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_ARC_DWTimer ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PADecoratedStorage ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PAHasReservations ?= disabled

# Following three methods are available in different PA derivatives for core activation.
DIRMERGE_SETTINGS_TAG_OsFeature_PA_DPM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_SIU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_MC ?= disabled
# Following timers are available on different PA derivatives.
DIRMERGE_SETTINGS_TAG_OsFeature_PA_timer_EMIOS ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_timer_STM ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_timer_PIC ?= disabled
# This interrupt controller doesn't exists on modern PA derivatives, so disable this by default.
DIRMERGE_SETTINGS_TAG_OsFeature_PA_PIC ?= disabled
# MemoryProtection implementation for PA derivatives
DIRMERGE_SETTINGS_TAG_OsFeature_PA_MMU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_SMPU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_MPU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_PA_MPU0 ?= disabled

DIRMERGE_SETTINGS_TAG_OsFeature_GenericMMU ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericMMU_GetMem ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericMMU_GetMemAlign ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericMMU_PageMap ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericMMU_PadReadOnly ?= disabled

DIRMERGE_SETTINGS_TAG_OsFeature_CacheOperations ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_CheckForDispatch ?= enabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericLeaveKernel ?= enabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericReturnFromCall ?= disabled
DIRMERGE_SETTINGS_TAG_OsFeature_GenericTimestamp ?= enabled
DIRMERGE_SETTINGS_TAG_OsFeature_SharedTimestampAndCounterTimer ?= enabled
DIRMERGE_SETTINGS_TAG_OsFeature_SharedTimestampAndExecTimer ?= enabled

DIRMERGE_SETTINGS_TAG_OsFeature_Multicore ?= enabled

