/* Mk_board.h - board specific ASIL header file for the TriboardTC397 board
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board.h 37087 2019-07-19 08:59:25Z miwi261726 $
*/

#ifndef MK_BOARD_H
#define MK_BOARD_H

/* Verify that the version of the board files matches the version of the microkernel */
#include <Mk_Version.h>
#include <Mk_board_version_check.h>

#include <public/Mk_timeconversion.h>
#include "Mk_board_tpsticks.h"

#include <Mk_board_tc3.h>


/* TC38XQ processors have 4 cores.
 *
 * Core 0 and 1 have a lockstep partner.
 *
 * Cores 2 and 3 have no lockstep partners, so they need
 * the MPU register check according to the Infineon safety manual.
*/
#define MK_CFG_C2_MPU_REGISTER_CHECK	1
#define MK_CFG_C3_MPU_REGISTER_CHECK	1

#endif
/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
