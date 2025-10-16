#EB_Automotive_Makefile

Lin_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Lin_17_AscLin/ssc/src/Lin_17_AscLin.c
Lin_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Lin_17_AscLin_*.c)
Lin_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/AscLin_Irq/AscLin_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Lin_src_FILES :=
endif

