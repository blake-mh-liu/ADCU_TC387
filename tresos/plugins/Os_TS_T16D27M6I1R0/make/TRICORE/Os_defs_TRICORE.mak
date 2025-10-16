#################################################################
#
# This makefile contains derivative-specific definitions for building the OS.
#
# Copyright Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.
#
#################################################################

OS_ASM_FILE_SUFFIX:=s

OS_TRICORE_PREFIX=$(OS_ARCH_PREFIX)

#########################
# TRICORE src/ DIRECTORY
#
ifeq ($(OS_KERNEL_TYPE),MICROKERNEL)
OS_OBJS_ARCH =
else
ifneq ($(BUILD_MODE),LIB)
ASM_FILES_TO_BUILD += \
	$(AutosarOS_SRC_PATH)/TRICORE/$(OS_TRICORE_PREFIX)interruptvectors.$(OS_ASM_FILE_SUFFIX)

EXCLUDE_MAKE_DEPEND  += \
	$(AutosarOS_SRC_PATH)/TRICORE/$(OS_TRICORE_PREFIX)interruptvectors.$(OS_ASM_FILE_SUFFIX)
endif

OS_OBJS_ARCH +=													\
	$(addprefix $(AutosarOS_SRC_PATH)/TRICORE/,					\
		Os_configuration_TRICORE.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)initcsalist.$(CC_FILE_SUFFIX) 		\
		$(OS_TRICORE_PREFIX)startupchecks.$(CC_FILE_SUFFIX)		\
	)
endif

Os_src_FILES += $(OS_OBJS_ARCH)


############################
#  TRICORE COMMON lib
#
ifeq ($(OS_KERNEL_TYPE),MICROKERNEL)
OS_KLIB_OBJS_ARCH =										\
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,		\
		$(OS_TRICORE_PREFIX)timer-stm.$(CC_FILE_SUFFIX)	\
	)
OS_ULIB_OBJS_ARCH =
else
OS_KLIB_OBJS_ARCH = \
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,						\
		$(OS_TRICORE_PREFIX)callapphook.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)callhook.$(CC_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)callisr.$(CC_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)callnontrustedisr.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)cat1interrupt.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)cat2interrupt.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)enterprotectedmode.$(CC_FILE_SUFFIX)		\
		$(OS_TRICORE_PREFIX)exceptionvectors.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)exceptionstartup.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)findtasksp.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)freecxlist.$(OS_ASM_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)freecxlistto.$(OS_ASM_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)grab1csa.$(OS_ASM_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)grab2csa.$(OS_ASM_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)killcalledcontext.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)idle.$(OS_ASM_FILE_SUFFIX)						\
		$(OS_TRICORE_PREFIX)initsp.$(OS_ASM_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)initmodule.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)initarchtricore.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)sethookprotection.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)setisrprotection.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)setprotection.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)setupcache.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)starttask.$(CC_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)syscall.$(OS_ASM_FILE_SUFFIX)					\
		$(OS_TRICORE_PREFIX)syscallstartup.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)takespinlock.$(OS_ASM_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap0handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap1handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap2handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap3handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap4handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap5handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)trap7handler.$(CC_FILE_SUFFIX)				\
		$(OS_TRICORE_PREFIX)unknowninterrupt.$(OS_ASM_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)intirconfigdriver.$(CC_FILE_SUFFIX)			\
		$(OS_TRICORE_PREFIX)timer-stm.$(CC_FILE_SUFFIX)					\
	 )																	\
	 $(addprefix $(AutosarOS_LIB_SRC_PATH)/kernel/,						\
		$(OS_KERN_PREFIX)triggerinterrupt.$(CC_FILE_SUFFIX)				\
	 )																	\
		$(OS_KLIB_OBJS_DERIVATE)

OS_ULIB_OBJS_ARCH = \
	$(OS_ULIB_OBJS_ARCH_COMMON)												\
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,							\
		$(OS_TRICORE_PREFIX)$(OS_USER_PREFIX)taskreturn.$(OS_ASM_FILE_SUFFIX)	\
	)


# On multicore processors, TRICORE-startcore is always needed, because the selected
# core may not be boot core and therefore needs to be started first.
ifneq ($(OS_N_CORES_MAX),1)
Os_src_FILES += \
	$(AutosarOS_SRC_PATH)/TRICORE/$(OS_TRICORE_PREFIX)startcore.$(CC_FILE_SUFFIX)
endif

ifneq ($(OS_N_CORES),1)

OS_ULIB_OBJS_ARCH += \
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,						\
		$(OS_TRICORE_PREFIX)$(OS_USER_PREFIX)shutdownallcores.$(OS_ASM_FILE_SUFFIX)	\
	)

ifeq ($(OS_AUTOSAR_SPINLOCKS),TRUE)
OS_ULIB_OBJS_ARCH += \
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,				\
		TRICORE-user-releasespinlock.$(OS_ASM_FILE_SUFFIX)		\
		TRICORE-user-trytogetspinlock.$(OS_ASM_FILE_SUFFIX)		\
	)
endif
endif

OS_ELIB_OBJS_ARCH = \
	$(addprefix $(AutosarOS_LIB_SRC_PATH)/TRICORE/,						\
		$(OS_TRICORE_PREFIX)$(OS_ERROR_INFIX)-ArchTrapHandler.$(CC_FILE_SUFFIX)	\
	)
endif

ifneq ($(OBJ_OUTPUT_PATH),)
OS_OBJ_DIR = $(OBJ_OUTPUT_PATH)
else
OS_OBJ_DIR = $(OBJ_DIR)
endif
$(OS_OBJ_DIR)/$(OS_TRICORE_PREFIX)interruptvectors.o: $(AutosarOS_OUTPUT_PATH)/include/Os_config.h

# Include derivative-specific makefiles. In most cases it suffices to distinguish Tricore families.
ifneq (,$(findstring TC2,$(OS_CPU)))
include $(AutosarOS_CORE_PATH)/make/$(OS_ARCH)/Os_defs_TRICORE_TC2_common.mak
endif
ifneq (,$(findstring TC3,$(OS_CPU)))
include $(AutosarOS_CORE_PATH)/make/$(OS_ARCH)/Os_defs_TRICORE_TC3_common.mak
endif
ifneq (,$(findstring TC4,$(OS_CPU)))
include $(AutosarOS_CORE_PATH)/make/$(OS_ARCH)/Os_defs_TRICORE_TC4_common.mak
endif

-include $(AutosarOS_CORE_PATH)/make/$(OS_ARCH)/$(OS_CPU)/Os_defs_$(OS_ARCH)_$(OS_CPU).mak

# Editor settings: DO NOT DELETE
# vi:set ts=4:
