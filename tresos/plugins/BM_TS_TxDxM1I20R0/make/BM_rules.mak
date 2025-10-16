# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

BM_src_FILES      := \
     $(BM_CORE_PATH)\src\BM_Prg.c \
     $(BM_CORE_PATH)\src\BM_SecureBoot.c \
     $(BM_CORE_PATH)\src\BM_Security.c
     
     
ifneq ("$(wildcard $(BM_OUTPUT_PATH)/src/BM_Cfg.c)","")
    BM_src_FILES      += $(BM_OUTPUT_PATH)\src\BM_Cfg.c
endif
	 
LIBRARIES_TO_BUILD += BM_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




