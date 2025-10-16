#EB_Automotive_Makefile

Dma_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Dma/ssc/src/Dma.c
Dma_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Dma_*.c)
Dma_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/Dma_Irq/Dma_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Dma_src_FILES :=
endif

