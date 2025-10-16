#EB_Automotive_Makefile

Pwm_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Pwm_17_GtmCcu6/ssc/src/Pwm_17_GtmCcu6.c
Pwm_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Pwm_17_GtmCcu6_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Pwm_src_FILES :=
endif

