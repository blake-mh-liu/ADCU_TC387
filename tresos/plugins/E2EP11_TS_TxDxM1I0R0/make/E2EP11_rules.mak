#
# \file
#
# \brief AUTOSAR E2EP11
#
# This file contains the implementation of the AUTOSAR
# module E2EP11.
#
# \version 1.0.3
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

E2EP11_src_FILES      :=  \
  $(E2EP11_CORE_PATH)/src/E2E_P11.c \
  $(E2EP11_CORE_PATH)/src/E2E_P11_E2EXf.c

LIBRARIES_TO_BUILD += E2EP11_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
