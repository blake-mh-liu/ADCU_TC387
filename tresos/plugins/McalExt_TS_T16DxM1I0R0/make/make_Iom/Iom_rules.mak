#EB_Automotive_Makefile

Iom_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Iom/ssc/src/Iom.c
Iom_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Iom_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Iom_src_FILES :=
endif

