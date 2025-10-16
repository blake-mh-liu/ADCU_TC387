#EB_Automotive_Makefile

I2c_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/I2c/ssc/src/I2c.c
I2c_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/I2c_*.c)
I2c_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/AppSw/Tricore/DemoMcal/Demo_Irq/I2c_Irq/I2c_Irq.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
I2c_src_FILES :=
endif

