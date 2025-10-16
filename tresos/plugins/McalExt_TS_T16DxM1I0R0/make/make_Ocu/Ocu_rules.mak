#EB_Automotive_Makefile

Ocu_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Ocu/ssc/src/Ocu.c
Ocu_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Ocu_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Ocu_src_FILES :=
endif

