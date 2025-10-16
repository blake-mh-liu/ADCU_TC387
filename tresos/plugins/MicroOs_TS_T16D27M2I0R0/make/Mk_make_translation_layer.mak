# Mk_make_translation_layer.mak
#
# A file to perform translations between the inconsistent definitions used
# in asc_Make, asc_Base, asc_Platforms etc. and what the microkernel
# Makefiles expect.
#
# (c) Elektrobit Automotive GmbH

MK_CPUFAMILY := TRICORE
MK_CPU := TC38XQ

# TOOLCHAIN mapping

MK_TOOLCHAIN=$(TOOLCHAIN)

ifeq ($(TOOLCHAIN),multi)
MK_TOOLCHAIN=ghs
endif

ifeq ($(TOOLCHAIN),gcc)
MK_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),gcc4)
MK_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),bcgcc)
MK_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),mgcc45)
MK_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),linaro)
MK_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),dcc)
MK_TOOLCHAIN=diab
endif

ifeq ($(TOOLCHAIN),cw)
MK_TOOLCHAIN=cw
endif

ifeq ($(TOOLCHAIN),taskingvx)
MK_TOOLCHAIN=tasking
endif

MK_TOOL = $(MK_TOOLCHAIN)

# Standard preprocessor defines
PREPROCESSOR_DEFINES += mk_cpufamily mk_cpu mk_tool

mk_cpufamily_KEY     = MK_CPUFAMILY
mk_cpufamily_VALUE   = MK_$(MK_CPUFAMILY)

mk_cpu_KEY      = MK_CPU
mk_cpu_VALUE    = MK_$(MK_CPU)

mk_tool_KEY     = MK_TOOL
mk_tool_VALUE   = MK_$(MK_TOOL)




