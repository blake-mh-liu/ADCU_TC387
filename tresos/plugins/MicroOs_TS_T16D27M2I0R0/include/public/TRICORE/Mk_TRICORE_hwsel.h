/* Mk_TRICORE_hwsel.h
 *
 * Definitions for TRICORE-specific header file selection.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_HWSEL_H
#define MK_TRICORE_HWSEL_H

#define MK_HWSEL_PUB_API					<public/TRICORE/Mk_TRICORE_api.h>
#define MK_HWSEL_PUB_CHARACTERISTICS		<public/TRICORE/Mk_TRICORE_characteristics.h>
#define MK_HWSEL_PUB_EXCEPTIONINFO			<public/TRICORE/Mk_TRICORE_exceptioninfo.h>

#define MK_HWSEL_PRV_ASM					<private/TRICORE/Mk_TRICORE_asm.h>
#define MK_HWSEL_PRV_CORE					<private/TRICORE/Mk_TRICORE_core.h>
#define MK_HWSEL_PRV_EXCEPTIONHANDLING		<private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#define MK_HWSEL_PRV_INTERRUPTCONTROLLER	<private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#define MK_HWSEL_PRV_MEMORYPROTECTION		<private/TRICORE/Mk_TRICORE_memoryprotection.h>
#define MK_HWSEL_PRV_STARTUP				<private/TRICORE/Mk_TRICORE_startup.h>
#define MK_HWSEL_PRV_THREAD					<private/TRICORE/Mk_TRICORE_thread.h>
#define MK_HWSEL_PRV_ACCOUNTING				<private/TRICORE/Mk_TRICORE_accounting.h>
#define MK_HWSEL_PRV_SST					<private/TRICORE/Mk_TRICORE_sst.h>

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
