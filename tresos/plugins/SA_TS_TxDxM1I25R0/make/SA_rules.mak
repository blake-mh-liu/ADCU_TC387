# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

SA_src_FILES      := \
     $(SA_CORE_PATH)\src\SA_Prg.c \
     $(SA_CORE_PATH)\src\SA_AuthMethod0001.c \
     $(SA_CORE_PATH)\src\SA_Decomp.c \
     $(SA_OUTPUT_PATH)\src\SA_Cfg.c
	 
LIBRARIES_TO_BUILD += SA_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




