#EB_Automotive_Makefile

Dsadc_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Dsadc/ssc/src/Dsadc.c
Dsadc_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Dsadc_*.c)
Dsadc_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Dsadc_Irq/Dsadc_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Dsadc_src_FILES :=
endif

