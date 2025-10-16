#
# \file
#
# \brief AUTOSAR Compiler
#
# This file contains the implementation of the AUTOSAR
# module Compiler.
#
# \version 1.0.16
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2017 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# this file just references the compiler_defs.mak makfiles
# in the TOOLCHAIN directory
ifeq (,$(filter $(TOOLCHAIN),gcc bcgcc mgcc62 bcgcc101))
$(error Unsupported toolchain for target WINDOWS: $(TOOLCHAIN))
endif
include $(Compiler_CORE_PATH)/make/$(TARGET)/$(TOOLCHAIN)/Compiler$(DEFS_FILE_SUFFIX)

# for GNU compilers use GNU debugger, so default debug rules are overridden
ALTERNATIVE_DEBUG_RULES := yes
