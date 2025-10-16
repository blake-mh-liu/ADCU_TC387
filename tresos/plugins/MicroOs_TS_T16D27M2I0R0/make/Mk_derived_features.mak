#
# \file
#
# \brief AUTOSAR MicroOs
#
# This file contains the implementation of the AUTOSAR
# module MicroOs.
#
# \version 2.0.232
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2023 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#
# This makefile is used from both the plugin build and the user build environment.
# It must only contain the feature set definitions.
# This file must be compatible with Make on unixoides, so don't use backward slashes in file names.

ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MkFeature_Multicore := enabled
else
MkFeature_Multicore := disabled
endif

ifeq ($(MK_MEM_PROT),MK_MEM_PROT_MPU)
MkFeature_Mpu := enabled
endif
ifeq ($(MK_MEM_PROT),MK_MEM_PROT_MMU)
MkFeature_Mmu := enabled
endif
