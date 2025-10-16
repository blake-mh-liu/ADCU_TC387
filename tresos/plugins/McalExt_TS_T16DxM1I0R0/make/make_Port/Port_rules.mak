#EB_Automotive_Makefile

Port_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Port/ssc/src/Port.c
Port_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Port_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Port_src_FILES :=
endif

