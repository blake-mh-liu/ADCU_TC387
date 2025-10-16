# --------{ EB Automotive Makefile }--------

ABS_FILE_SUFFIX=elf
MAP_FILE_SUFFIX=map
ASM_FILE_SUFFIX=s
HEX_FILE_SUFFIX=mot
EXE_FILE_SUFFIX?=.exe

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(MAP_FILE_SUFFIX)
HEXFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(HEX_FILE_SUFFIX)

# ------ general files (used in common rules)
# ------ add in {TARGET}_{DERIVATE}_Makefile.mak WIN_TOOLCHAIN_USED ?= WIN64
# ------ this is used to handle the Win path for different Diab compilers from 
# ------ accessible Makefile
ifeq ($(WIN_TOOLCHAIN_USED),WIN64)
  COMPILER_DIR    = $(TOOLPATH_COMPILER)/WIN64/bin
else
  COMPILER_DIR    = $(TOOLPATH_COMPILER)/Win32/bin
endif
CC              = $(COMPILER_DIR)/dcc$(EXE_FILE_SUFFIX)
CCLIB           = $(COMPILER_DIR)/dar$(EXE_FILE_SUFFIX)
ASM             = $(COMPILER_DIR)/dcc$(EXE_FILE_SUFFIX)
LINK            = $(COMPILER_DIR)/dld$(EXE_FILE_SUFFIX)
HEX             = $(COMPILER_DIR)/ddump$(EXE_FILE_SUFFIX)
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp$(EXE_FILE_SUFFIX)
