/* Os_salsa.h
 *
 * This file maps the required SALSA service names onto existing OS services.
 *
 * The content of this file is not integrated into the normal OS files because
 * the names do not conform to the AUTOSAR nameing scheme. These names were
 * specified in the requirements, so they must be used.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_SALSA_H
#define OS_SALSA_H

#ifndef OS_ASM

#include <Os_types.h>

extern os_uint8_t GetStackUsage(os_taskid_t);
extern os_uint8_t GetSystemStackUsage(void);

#endif  /* OS_ASM */

#endif  /* OS_SALSA_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
