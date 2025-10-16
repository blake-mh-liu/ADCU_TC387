/* Mk_core_master_index.h - declare constant of master core index
 *
 * This file contains the declaration of the master core index constant.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_CORE_MASTER_INDEX_H
#define MK_CORE_MASTER_INDEX_H

#ifndef MK_ASM

#include <public/Mk_public_types.h>

/* The core index of the hardware-defined master core.
 *
 * This is not necessarily the same as the AUTOSAR-defined master core.
 * This constant is used to determine which core controls the startup process. If the MPU
 * has a specific core that starts up as a single core, the core ID of this core should
 * be used here. If the cores start symmetrically, the choice is arbitrary.
*/
extern const mk_objectid_t MK_hwMasterCoreIndex;

#endif /* MK_ASM */

#endif /* MK_CORE_MASTER_INDEX_H */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
