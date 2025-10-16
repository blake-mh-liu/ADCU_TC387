# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

ProgOEMInd_src_FILES      := \
    $(ProgOEMInd_CORE_PATH)\src\PROG_Hsm.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_HsmPROGData.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_HsmPROGFnct.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_DoubleGuard.c

LIBRARIES_TO_BUILD += ProgOEMInd_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
