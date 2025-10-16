#EB_Automotive_Makefile

Dio_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Dio/ssc/src/Dio.c
Dio_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Dio_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Dio_src_FILES :=
endif

