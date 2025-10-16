# Ioc_make_translation_layer.mak
#
# A file to perform translations between the inconsistent definitions used
# in asc_Make, asc_Base.asc_Platforms etc. and what the IOC
# Makefiles expect.
#
# (c) Elektrobit Automotive GmbH

IOC_CPUFAMILY := $(TARGET)
IOC_CPU := $(DERIVATE)

# TOOLCHAIN mapping

IOC_TOOLCHAIN=$(TOOLCHAIN)

ifeq ($(TOOLCHAIN),multi)
IOC_TOOLCHAIN=ghs
endif

ifeq ($(TOOLCHAIN),gcc)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),gcc4)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),bcgcc)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),bcgcc101)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),mgcc45)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),mgcc62)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),mgcc101)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),clang)
IOC_TOOLCHAIN=gnu
endif

ifeq ($(TOOLCHAIN),dcc)
IOC_TOOLCHAIN=diab
endif

ifeq ($(TOOLCHAIN),cw)
IOC_TOOLCHAIN=cw
endif

ifeq ($(TOOLCHAIN),taskingvx)
IOC_TOOLCHAIN=tasking
endif

IOC_TOOL = $(IOC_TOOLCHAIN)

# Standard preprocessor defines
PREPROCESSOR_DEFINES += ioc_cpufamily ioc_cpu ioc_tool

ioc_cpufamily_KEY     = IOC_CPUFAMILY
ioc_cpufamily_VALUE   = IOC_$(IOC_CPUFAMILY)

ioc_cpu_KEY      = IOC_CPU
ioc_cpu_VALUE    = IOC_$(IOC_CPU)

ioc_tool_KEY     = IOC_TOOL
ioc_tool_VALUE   = IOC_$(IOC_TOOL)




