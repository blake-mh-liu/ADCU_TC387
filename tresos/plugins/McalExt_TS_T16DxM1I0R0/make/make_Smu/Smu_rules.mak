#EB_Automotive_Makefile

Smu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Smu/ssc/src/Smu.c
Smu_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Smu_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Smu_src_FILES :=
endif

