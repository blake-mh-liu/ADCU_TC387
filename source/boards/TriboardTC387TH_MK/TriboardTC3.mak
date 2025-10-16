#################################################################
#
# NAME:     TriboardTC3.mak
#
# FUNCTION: This file is part of the Autosar SC build environment.
#
# (c) by Elektrobit Automotive GmbH
# - all rights reserved -
#

##################################################################
# DEFINITIONS
#

mkboard_FILES        += $(OS_BOARD_DIR)/Mk_board_leds.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_board_tool_diab.c
mkboard_FILES        += $(OS_BOARD_DIR)/Mk_protectRamFromExternal.s

