#EB_Automotive_Makefile

Icu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Icu_17_TimerIp/ssc/src/Icu_17_TimerIp.c
Icu_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Icu_17_TimerIp_*.c)
Icu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Ccu6_Irq/Ccu6_Irq.c
Icu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Eru_Irq/Eru_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Icu_src_FILES :=
endif

