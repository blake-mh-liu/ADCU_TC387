#################################################################
#
# NAME:     TriboardTC29XT_MK..mak
#
# FUNCTION: This file is part of the Autosar SC build environment.
#
# (c) by Elektrobit Automotive GmbH
#

##################################################################
#
# TOOLCHAIN mapping
#
OS_TOOLCHAIN=$(TOOLCHAIN)

ifeq ($(TOOLCHAIN),gcc)
OS_TOOLCHAIN=gnu
endif
ifeq ($(TOOLCHAIN),gnu)
OS_TOOLCHAIN=gnu
endif
ifeq ($(TOOLCHAIN),tasking)
OS_TOOLCHAIN=tasking
endif
ifeq ($(TOOLCHAIN),dcc)
OS_TOOLCHAIN=diab
endif

##################################################################
# DEFINITIONS
#
ifeq ($(OS_BOARD_DIR), )
OS_BOARD_DIR=$(BOARD_PROJECT_PATH)
endif

CC_INCLUDE_PATH      += $(OS_BOARD_DIR)
CPP_INCLUDE_PATH     += $(OS_BOARD_DIR)
ASM_INCLUDE_PATH     += $(OS_BOARD_DIR)

LIBRARIES_TO_BUILD   += mkboard
mkboard_PATH         := 
mkboard_FILES        := $(OS_BOARD_DIR)/Mk_board.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_entry.s
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_bootword_tc2xx.s
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_board_setupclocks_tc2xx.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_board_startupautosarcores.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_board_setstmdebugmode.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_board_demostartup.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_TRICORE_board_setupcache.c

#################################################################
# ENTRY_SYMBOLS :
# list of required symbols to keep
#
ENTRY_SYMBOLS := MK_Entry MK_StartupExceptionTable MK_ExceptionTable MK_InterruptTable MK_QM_TRICORE_bootblock

ifeq ($(OS_TOOLCHAIN),gnu)
LINK_OPT += $(patsubst %,-u %,$(ENTRY_SYMBOLS))
else
ifeq ($(OS_TOOLCHAIN),tasking)
LINK_OPT += $(patsubst %,-e %,$(ENTRY_SYMBOLS))
else
ifeq ($(OS_TOOLCHAIN),diab)
LINK_OPT += $(patsubst %,-u %,$(ENTRY_SYMBOLS))
else
$(error Unsupported Toolchain $(TOOLCHAIN))
endif
endif
endif

######################## Defines for Linker file generation for Memory protected systems ############

OS_GENLD = $(OS_BOARD_DIR)/genld-TRICORE-Mk.pl

ifeq ($(OS_TOOLCHAIN),tasking)
OS_GENLD_OPT += -include $(OS_BOARD_DIR)/memdefs-tasking.ldscript
ifneq ($(filter $(CC_OPT),-DUSE_TASKING_CINIT=1),)
OS_GENLD_OPT += -use-tasking-init
endif
endif

#/* !LINKSTO      Microkernel.LinkerScript.GroupAlign,1
# * !doctype      src
# */
LOC_FILE = $(PROJECT_ROOT)/output/generated/$(MK_CPUFAMILY)-$(OS_TOOLCHAIN).ldscript

# Only needed for OS-Demo: IO region for LED-access
MK_MR_START_Port33 = "MK_RSA_Port33=0xF003D300"
MK_MR_LIMIT_Port33 = "MK_RLA_Port33=0xF003D400"

ifeq ($(AutosarOS_CORE_PATH),)
      AutosarOS_CORE_PATH= $(SSC_ROOT)\MicroOs_$(MicroOs_VARIANT)
endif

ifeq ($(MK_NUM_THREADSTACK_SLOTS),)
MK_NUM_THREADSTACK_SLOTS=0
endif


OS_APP_SPECS = \
$(foreach app,$(APPLICATIONS),-app $(app) -core $(OS_CORE_$(app)) $(app)_gen.$(OBJ_FILE_SUFFIX) $(OBJS_$(app)) \
  $(foreach task,$(TASKS_$(app)),-task $(task) $(OBJS_$(task)))  \
  $(foreach isr,$(ISRS_$(app)),-isr $(isr) $(OBJS_$(isr))) \
  $(foreach mr, $(MEMREG_$(app)), -memregsym $(mr) $(MEMREGSYM_$(mr))) \
)

OS_APP_SPECS += \
  $(foreach mr, $(MEMREG_OS_SYSTEM), -memregsym $(mr) $(MEMREGSYM_$(mr)))

# Remove all memory regions which are assigned to an application from
# the global list of memory regions
MK_UNASSIGNED_MEMORYREGIONS = \
  $(filter-out $(MEMREG_OS_SYSTEM), \
    $(filter-out $(foreach app, $(APPLICATIONS), $(MEMREG_$(app))), $(MK_MEMORYREGIONS)) \
  )

MK_MR_SPECS = $(foreach mr,$(MK_UNASSIGNED_MEMORYREGIONS),-mr $(mr) $(MK_MR_START_$(mr)) $(MK_MR_LIMIT_$(mr)) $(MK_MR_BSTART_$(mr)) $(MK_MR_IDATA_$(mr)))

OS_DEF_SPECS  = $(foreach obj,$(TASKS_OS_SYSTEM) $(ISRS_OS_SYSTEM),-sysobj $(obj))

include $(OS_BOARD_DIR)/TriboardTC2.mak

$(LOC_FILE): $(OS_BOARD_DIR)/TRICORE-$(OS_TOOLCHAIN).ldscript $(OS_GENLD)
	$(AutosarOS_CORE_PATH)\bin\cygtools\perl \
		$(OS_GENLD) \
		$(OS_GENLD_OPT) \
		-backend $(OS_TOOLCHAIN) \
		-o $@ \
		-include $(OS_BOARD_DIR)/TRICORE-$(OS_TOOLCHAIN).ldscript \
		-numcores $(OS_N_CORES_MAX) \
		-corecsas $(OS_TRICORE_NCSA_LIST) \
		-num-thread-slots $(MK_NUM_THREADSTACK_SLOTS) \
		$(OS_APP_SPECS) \
		$(OS_DEF_SPECS) \
		$(MK_MR_SPECS)


#################################################################
# TRACE32_APP_PATH, TRACE32_CONFIG_PATH
# Paths to the Trace32 Debugger binary and config
TRACE32_PATH ?= d:\wrk\prj\xsc_Project\tools\bin\T32_TRICORE
TRACE32_APP_PATH ?= $(TRACE32_PATH)\bin\windows64