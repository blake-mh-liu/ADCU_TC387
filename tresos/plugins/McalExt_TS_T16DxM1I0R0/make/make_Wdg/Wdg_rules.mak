#EB_Automotive_Makefile

Wdg_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/Wdg_17_Scu/ssc/src/Wdg_17_Scu.c
Wdg_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/Wdg_17_Scu_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Wdg_src_FILES :=
endif

