#EB_Automotive_Makefile

Mcu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Mcu/ssc/src/Mcu.c
Mcu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Mcu/ssc/src/Mcu_17_TimerIp.c
Mcu_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Mcu_17_TimerIp_*.c)
Mcu_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Mcu_*.c)
Mcu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Gtm_Irq/Gtm_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Mcu_src_FILES :=
endif

