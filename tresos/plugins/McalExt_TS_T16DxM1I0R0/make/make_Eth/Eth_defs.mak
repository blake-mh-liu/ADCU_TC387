#EB_Automotive_Makefile

#################################################################
# DEFINITIONS
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/inc/Eth_17_GEthMacV2_*.h)
McalExt_GEN_FILES      += $(wildcard $(McalExt_OUTPUT_PATH)/src/Eth_17_GEthMacV2_*.c)
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Eth_17_GEthMacV2/ssc/inc
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)\include\Eth
