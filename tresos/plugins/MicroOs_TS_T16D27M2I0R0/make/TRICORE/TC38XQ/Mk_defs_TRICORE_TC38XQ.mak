#################################################################
#
# NAME:      Mk_defs_TRICORE_TC38XQ.mak
#
# FUNCTION:  This file is part of the Autosar SC build environment.
# PROJECT :  AutosarOS
#
# TOOLCHAIN: GNU Make 3.8
#
# (c) Elektrobit Automotive GmbH
#
#################################################################

# Number of cores available on this derivate

MK_MAXCORES := 4

# Invalid TOS values are present on TC3s and on TC2s which have exactly two cores.
MkFeature_TricoreTosValueValidityCheck := enabled

# Editor settings: DO NOT DELETE
# vi:set ts=4:
