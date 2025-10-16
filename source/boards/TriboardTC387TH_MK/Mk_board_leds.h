/* Mk_board_leds.h - board specific header file for the TriboardTC397 board
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board_leds.h 30218 2017-09-05 10:35:09Z aniv261689 $
*/
#ifndef MK_QMBOARD_LEDS_H
#define MK_QMBOARD_LEDS_H

#include <public/Mk_public_types.h>

/*
 * Function prototypes for working with LESs
*/

extern void leds_init_tc3x7th();
extern void leds_set_tc3x7th(mk_uint32_t x);
extern mk_uint32_t leds_get_tc3x7th();

#define	LEDS_INIT()		leds_init_tc3x7th()
#define	LEDS_SET(x)		leds_set_tc3x7th((x))
#define LEDS_GET()		leds_get_tc3x7th()

#endif
