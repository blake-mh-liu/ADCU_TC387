#EB_Automotive_Makefile

Fr_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fr_17_Eray/ssc/src/Fr_17_Eray.c
Fr_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Fr_17_Eray_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Fr_src_FILES :=
endif

