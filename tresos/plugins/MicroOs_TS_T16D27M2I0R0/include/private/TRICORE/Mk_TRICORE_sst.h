/* Mk_TRICORE_sst.h
 *
 * TRICORE-specific declaration/implementation of the hardware abstraction
 * of the simple schedule table (SST) feature.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_SST_H
#define MK_TRICORE_SST_H

#include <public/Mk_public_api.h>

#ifndef MK_ASM

/* These functions provide the hardware abstraction for the SST feature.
*/
extern mk_boolean_t MK_HwCheckTickerId(mk_objectid_t);
extern void MK_HwInitTicker(mk_objectid_t);
extern void MK_HwStartTicker(mk_objectid_t, mk_tick_t);
extern void MK_HwStopTicker(mk_objectid_t);
extern void MK_HwReloadTicker(mk_objectid_t, mk_tick_t);

#endif /* MK_ASM */
#endif /* MK_TRICORE_SST_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
