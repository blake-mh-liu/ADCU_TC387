#EB_Automotive_Makefile

#################################################################
# DEFINITIONS
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/inc/Fls_17_Dmu_*.h)
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/src/Fls_17_Dmu_*.c)
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fls_17_Dmu/ssc/inc
