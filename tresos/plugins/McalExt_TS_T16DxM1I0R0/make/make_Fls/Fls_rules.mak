#EB_Automotive_Makefile

Fls_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fls_17_Dmu/ssc/src/Fls_17_Dmu.c
Fls_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fls_17_Dmu/ssc/src/Fls_17_Dmu_ac.c
Fls_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Fls_17_Dmu_*.c)
Fls_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Fls_Irq/Fls_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Fls_src_FILES :=
endif

