/* Mk_u_libgetntasks.c
 *
 * This file contains the MK_LibGetNTasks() function.
 *
 * This function returns the number of configured tasks.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_task.h>
#include <public/Mk_public_api.h>

/* MK_LibGetNTasks() returns the number of configured tasks.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_objquantity_t MK_LibGetNTasks(void)
{
	return MK_nTasks;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
