#EB_Automotive_Makefile

FlsLoader_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/FlsLoader/ssc/src/FlsLoader.c
FlsLoader_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/McIsar/Src/Mcal/Tricore/FlsLoader/ssc/src/FlsLoader_Platform.c
FlsLoader_src_FILES += $(wildcard $(McalExt_OUTPUT_PATH)/src/FlsLoader_*.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
FlsLoader_src_FILES :=
endif

