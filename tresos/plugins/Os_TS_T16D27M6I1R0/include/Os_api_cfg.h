/* Os_api_cfg.h - configuration dependent OS API
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_API_CFG_H
#define OS_API_CFG_H

#include <Os_types.h>
#include <Os_user.h>
#include <Os_alci.h>
#include <Os_kernel.h>

#if (OS_KERNEL_TYPE==OS_MICROKERNEL)
#error "Os_api_cfg.h should not be used in a microkernel environment"
#endif

#if (OS_N_CORES > 1)

#define StartCore(coreid, status)			OS_StartCore(OS_GetPhysicalCoreId(coreid), (status))
#define GetSpinlock(s)						OS_GetSpinlock((s))
#define TryToGetSpinlock(lockid, status)	OS_UserTryToGetSpinlock((lockid), (status))
#define ReleaseSpinlock(s)					OS_UserReleaseSpinlock((s))
#define ShutdownAllCores(r)					OS_UserShutdownAllCores(r)

#else

#define StartCore(coreid, status)			do { *(status) = (OS_GetKernelData()->inFunction != OS_INBOOT) ? \
												E_OS_ACCESS : E_OS_STATE; } while (0)
#define GetSpinlock(s)						E_OS_ID
#define TryToGetSpinlock(lockid, status)	E_OS_ID
#define ReleaseSpinlock(s)					E_OS_ID
#define ShutdownAllCores(r)					ShutdownOS(r)

#endif /* OS_N_CORES > 1 */

#endif


/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
