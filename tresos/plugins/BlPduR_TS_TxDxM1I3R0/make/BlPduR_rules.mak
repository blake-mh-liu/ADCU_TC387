# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

BlPduR_src_FILES      := \
     $(BlPduR_OUTPUT_PATH)\src\BlPduR_Cfg.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Prg.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Lin.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Buf_Mng.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Conn_Treatment.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_PduR.c \

LIBRARIES_TO_BUILD += BlPduR_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




