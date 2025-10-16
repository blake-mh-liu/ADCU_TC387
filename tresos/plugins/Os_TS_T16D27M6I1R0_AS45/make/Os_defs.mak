#
# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \version 6.1.256
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2024 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.


# define release variant for conditionals in generic makefiles
OS_RELEASE_SUFFIX := AS45

# redirect AS45 to common OS plugin
ifeq ($(Os_CORE_PATH),)
  include $(PLUGINS_BASE)/Os_TS_T16D27M6I1R0/make/Os_defs.mak
else
  include $(realpath $(Os_CORE_PATH)/..)/Os_TS_T16D27M6I1R0/make/Os_defs.mak
endif
