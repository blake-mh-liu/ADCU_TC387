#EB_Automotive_Makefile

CanTrcv1_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/CanTrcv_17_V9251/ssc/src/CanTrcv_17_V9251.c
CanTrcv1_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/CanTrcv_17_V9251_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
CanTrcv1_src_FILES :=
endif

