#EB_Automotive_Makefile

#################################################################
# DEFINITIONS
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/inc/Fr_17_Eray_*.h)
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/src/Fr_17_Eray_*.c)
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fr_17_Eray/ssc/inc
