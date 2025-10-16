#EB_Automotive_Makefile

#################################################################
# DEFINITIONS
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/inc/FlsLoader_*.h)
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/src/FlsLoader_*.c)
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/FlsLoader/ssc/inc
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/include/FlsLoader
