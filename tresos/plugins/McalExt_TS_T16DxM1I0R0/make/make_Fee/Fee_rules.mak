#EB_Automotive_Makefile

Fee_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Fee/ssc/src/Fee.c
Fee_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Fee_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Fee_src_FILES :=
endif

