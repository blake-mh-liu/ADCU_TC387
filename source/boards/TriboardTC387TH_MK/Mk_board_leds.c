/* Mk_board_leds.c - board specific file for Triboard
 * 
 * Defines functions to initialize, write and read board LEDs.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board_leds.c 30256 2017-09-11 12:51:59Z aniv261689 $
*/

#include <Mk_board_leds.h>

/*
 * LEDs on TC39X7TH are connected to Port 20 and Port 33
*/
#define	TMPL_P20_ADDR				0xF003B400u
#define	TMPL_P33_ADDR				0xF003C100u

#ifndef MK_ASM
/*
 * GPIO port configuration structure
*/
struct tmpl_qmtricoreport_s 
{
	mk_reg32_t	out;									/* 0x00u -	Output register				*/
	mk_reg32_t	omr;									/* 0x04u -	Output modification reg.	*/
	mk_reg32_t	id;										/* 0x08u -	Port identification reg.	*/
	mk_reg32_t	reserved1;								/* 0x0Cu -	reserved					*/
	mk_reg32_t	iocr0;									/* 0x10u -	I/O Control register 0		*/
	mk_reg32_t	iocr4;									/* 0x14u -	I/O Control register 4		*/
	mk_reg32_t	iocr8;									/* 0x18u -	I/O Control register 8		*/
	mk_reg32_t	iocr12;									/* 0x1Cu -	I/O Control register 12		*/
	mk_reg32_t	reserved2;								/* 0x20u -	reserved					*/
	mk_reg32_t	in;										/* 0x24u -	Input register				*/
	mk_reg32_t	reserved3[6];							/* 0x28u -	reserved					*/
	mk_reg32_t	pdr[2];									/* 0x40u -	Pad driver mode	registers	*/
	mk_reg32_t	reserved4[2];							/* 0x48u -	reserved					*/
	mk_reg32_t	esr;									/* 0x50u -	Emergency stop register		*/
	mk_reg32_t	reserved5[43];							/* 0x54u -	the rest of the registers	*/
};
typedef struct tmpl_qmtricoreport_s  tmpl_qmtricoreport_t;
#endif

void leds_init_tc3x7th()
{
	tmpl_qmtricoreport_t * const port20 = (tmpl_qmtricoreport_t *)TMPL_P20_ADDR;
	tmpl_qmtricoreport_t * const port33 = (tmpl_qmtricoreport_t *)TMPL_P33_ADDR;

	port20->iocr8 = 0x80101010u;
	port20->iocr12 = 0x10808080u;
	port33->iocr4 = 0x80808080u;
}

void leds_set_tc3x7th(mk_uint32_t x)
{
	tmpl_qmtricoreport_t * const port20 = (tmpl_qmtricoreport_t *)TMPL_P20_ADDR;
	tmpl_qmtricoreport_t * const port33 = (tmpl_qmtricoreport_t *)TMPL_P33_ADDR;

	port20->out = (port20->out & ~0x7800u) | (((~(x))&0xF0u) << 7u);
	port33->out = (port33->out & ~0x00F0u) | (((~(x))&0x0Fu) << 4u);
}

mk_uint32_t leds_get_tc3x7th()
{
	tmpl_qmtricoreport_t * const port20 = (tmpl_qmtricoreport_t *)TMPL_P20_ADDR;
	tmpl_qmtricoreport_t * const port33 = (tmpl_qmtricoreport_t *)TMPL_P33_ADDR;

	return (((port20->out >> 7u) & 0xF0u) | ((port33->out >> 4u) & 0x0Fu));
}