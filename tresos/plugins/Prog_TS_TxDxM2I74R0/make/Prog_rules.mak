# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

Prog_src_FILES      := \
     $(Prog_CORE_PATH)\src\PROG_Prg.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_80.c \
     $(Prog_CORE_PATH)\src\PROG_Encrypt.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_20.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_30.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_10.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_90.c \
     $(Prog_CORE_PATH)\src\PROG_Impl_0.c \
     $(Prog_CORE_PATH)\src\PROG_Cust_AppliCheck.c \
     $(Prog_CORE_PATH)\src\PROG_Cust_Crc.c \
     $(Prog_CORE_PATH)\src\PROG_Cust_Init.c \
     $(Prog_CORE_PATH)\src\PROG_Cust_SBL.c \
     $(Prog_CORE_PATH)\src\PROG_Mem.c \
     $(Prog_CORE_PATH)\src\PROG_Cry.c \
     $(Prog_CORE_PATH)\src\PROG_Security.c \
     $(Prog_CORE_PATH)\src\PROG_Decomp.c \
     $(Prog_CORE_PATH)\src\PROG_Driver.c \
     $(Prog_CORE_PATH)\src\PROG_Erase.c \
     $(Prog_CORE_PATH)\src\PROG_ResumeReprog.c \
     $(Prog_OUTPUT_PATH)\src\PROG_Cfg.c

LIBRARIES_TO_BUILD += Prog_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




