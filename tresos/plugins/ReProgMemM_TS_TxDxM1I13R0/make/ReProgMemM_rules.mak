# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

ReProgMemM_src_FILES     := $(ReProgMemM_CORE_PATH)\src\ReProgMemM.c        \
                            $(ReProgMemM_OUTPUT_PATH)\src\ReProgMemM_Cfg.c

#################################################################
# standard mode settings

LIBRARIES_TO_BUILD += ReProgMemM_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
