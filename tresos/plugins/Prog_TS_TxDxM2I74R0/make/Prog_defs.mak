# \file
#
# \brief Autosar Prog
#
# This file contains the implementation of the Autosar
# module Prog.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Prog_CORE_PATH         := $(SSC_ROOT)\Prog_$(Prog_VARIANT)

Prog_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += Prog
Prog_DEPENDENT_PLUGINS := base_make tresos
Prog_VERSION           := 2.00.00
Prog_DESCRIPTION       := Prog Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(Prog_CORE_PATH)\include \
   $(Prog_OUTPUT_PATH)\include
