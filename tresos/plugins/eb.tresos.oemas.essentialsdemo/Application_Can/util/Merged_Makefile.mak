# don't generate code for Os_MemoryProtection.xdm (enables MemoryProtection)
TRESOS2_NOGEN_PLUGINS += Os_MemoryProtection

# don't generate code for MicroKernel Os
TRESOS2_NOGEN_PLUGINS += MicroOs

# enable MicroKernel Os plugin
ENABLED_PLUGINS += MicroOs

# Settings for Multicore: Use other board directory
BOARD = TriboardTC29XT_MK

# EB Dem provides ASR3 and ASR4 symbolic names per default
# Disable for TC29XT cause MCAL drivers define own symbolic names and these
# clash with Dem compatibility mode, only ASR4.0.3 defines will be generated
CC_OPT += -DDEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
##################################################################
# user options
# define COMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES as a fix to ASCCANSM-469
CC_OPT += -DCOMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
CC_OPT += -DCANSM_NO_SYMBOLS_WITHOUT_PREFIX
##################################################################

#################################################################
# include merged makefile if they exist
-include $(PROJECT_ROOT)\util\$(TARGET)\Merged_Makefile.mak

# enable Resource plugin in make environment
ENABLED_PLUGINS += Resource

#################################################################
#
# Add the toolchain specific MemMap configuration to the list of
# config files and make sure that tresos does not expect a
# module of that name.
#

TRESOS2_NOGEN_PLUGINS += MemMap_Platforms

ATOMICS_USE_GENERIC_IMPL := 1

# ATOMICS_USER_MULTICORE_CASE
# Assume the single-core case.
PREPROCESSOR_DEFINES += TS_ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_KEY = ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_VALUE = 0
