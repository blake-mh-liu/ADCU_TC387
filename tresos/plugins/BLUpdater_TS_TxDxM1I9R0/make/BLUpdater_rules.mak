# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

BLUpdater_src_FILES      := \
     $(BLUpdater_CORE_PATH)\src\BLUpdater_Prg.c \
     
     
ifneq ("$(wildcard $(BLUpdater_OUTPUT_PATH)/src/BLUpdater_Cfg.c)","")
    BLUpdater_src_FILES      += $(BLUpdater_OUTPUT_PATH)\src\BLUpdater_Cfg.c
endif
	 
LIBRARIES_TO_BUILD += BLUpdater_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




