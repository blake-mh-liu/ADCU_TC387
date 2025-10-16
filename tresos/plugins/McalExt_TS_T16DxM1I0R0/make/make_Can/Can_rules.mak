#EB_Automotive_Makefile

Can_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Can_17_McmCan/ssc/src/Can_17_McmCan.c
Can_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Can_17_McmCan_*.c)
Can_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Can_Irq/Can_17_McmCan_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Can_src_FILES :=
endif

