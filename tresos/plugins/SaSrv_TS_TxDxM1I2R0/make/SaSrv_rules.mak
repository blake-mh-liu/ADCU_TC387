#
# \file
#
# \brief AUTOSAR SaSrv
#
# This file contains the implementation of the AUTOSAR
# module SaSrv.
#
# \version 1.2.0
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

SaSrv_src_FILES      := \
  $(SaSrv_CORE_PATH)/src/SaSrv_DSD.c \
  $(SaSrv_CORE_PATH)/src/SaSrv_DSP.c \
  $(SaSrv_OUTPUT_PATH)/src/SaSrv_DSD_Cfg.c \
  $(SaSrv_OUTPUT_PATH)/src/SaSrv_DSP_Cfg.c \
  $(SaSrv_OUTPUT_PATH)/src/SaSrv_DSP_COTS_Cfg.c \  

LIBRARIES_TO_BUILD   += SaSrv_src

#################################################################
# RULES
