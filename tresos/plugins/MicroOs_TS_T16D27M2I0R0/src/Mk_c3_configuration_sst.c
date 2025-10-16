/* Mk_c3_configuration_sst.c
 *
 * This file contains the configuration items for the SST feature for core 3.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <configuration/Mk_c3_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if ((MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) == 0) || (MK_CFG_C3_NSSTS == 0)

/* This constant ensures that this file is a valid C compilation unit.
 * It also serves to identify which cores are not used in the compiled system.
 * Hint: nm foo.elf | grep NOT_USED
*/
const mk_uint8_t MK_c3_sst_NOT_USED = 0xebu;

#else

mk_sstcounter_t MK_c3_sstCounters[MK_CFG_C3_NSSTS];					/* = {0} */

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
