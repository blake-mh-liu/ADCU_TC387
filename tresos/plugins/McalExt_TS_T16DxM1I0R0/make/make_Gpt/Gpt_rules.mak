#EB_Automotive_Makefile

Gpt_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Gpt/ssc/src/Gpt.c
Gpt_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Gpt_*.c)
Gpt_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Gpt12_Irq/Gpt12_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Gpt_src_FILES :=
endif

