# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

EB_src_FILES      := \
     $(EB_OUTPUT_PATH)\src\EB_Cfg.c \
     $(EB_OUTPUT_PATH)\src\EB_Prg.c
    
ifneq ("$(wildcard $(EB_OUTPUT_PATH)/src/EB_Boot_PduR.c)","")
    EB_src_FILES      += $(EB_OUTPUT_PATH)\src\EB_Boot_PduR.c
endif

ifneq ("$(wildcard $(EB_OUTPUT_PATH)/src/EB_FullDuplex.c)","")
    EB_src_FILES      += $(EB_OUTPUT_PATH)\src\EB_FullDuplex.c
endif
     
LIBRARIES_TO_BUILD += EB_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




