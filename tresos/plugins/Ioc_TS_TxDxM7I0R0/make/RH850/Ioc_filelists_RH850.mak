# Ioc_filelist_RH850.mak - lists of files that go into the Ioc build
#
# This file just contains lists of files that go into various parts of the
# build for the RH850 Architecture.
# The file is also included into the unsupported make so it must be compatible.

ifneq ($(OS_N_CORES),1)
IOC_SRC_USER_BASELIST += interlock_osspinlock
endif
