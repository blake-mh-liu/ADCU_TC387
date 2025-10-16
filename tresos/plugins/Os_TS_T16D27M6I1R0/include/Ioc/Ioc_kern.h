/* Ioc_kern.h
 *
 * Declarations for in-kernel IOC
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef MULTICORE_IOC_KERN_H
#define MULTICORE_IOC_KERN_H

#include <Os_types.h>

extern os_memoryaccess_t OS_KernIocCheckMemoryAccess( const void *data, os_size_t len );

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
