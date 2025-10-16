/* Mk_board_tool_diab.c - tool and board specific file for TriboardTC397XX
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board_tool_diab.c 29747 2017-07-14 10:48:04Z fach271474 $
*/

#include <private/Mk_tool_diab.h>

#ifdef MK_CompilerStackCheckGuard
#define _ILONG              1   /* int is long */
#define _SIZE_T_LONG_LONG   0   /* size_t isn't long long */
#include <stdint.h>
const uintptr_t MK_CompilerStackCheckGuard = 0xeb15c00lu;
#endif

const char boardNoDiab = 'X';

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
