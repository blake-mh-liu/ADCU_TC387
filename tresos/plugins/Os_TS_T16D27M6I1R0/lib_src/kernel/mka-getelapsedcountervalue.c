/* mkl-getelapsedcountervalue.c
 *
 * This file contains the GetElapsedCounterValue function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_autosar.h>

/*
 * GetElapsedCounterValue() places the value of the specified counter into the first referenced variable
 * and the difference between the new value and the old value (modulo MAXALLOWEDVALUE) into the second
 * referenced variable.
 *
 * WARNING: this function cannot be ASIL because it calls a QM function in the OS.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
StatusType GetElapsedCounterValue(CounterType counterId, TickRefType value, TickRefType elapsedValue)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	TickType tmpTick;
	StatusType ret;

	/* COVPT-1 */
	ret = GetCounterValue(counterId, &tmpTick);

	if (ret == E_OK)
	{
		*elapsedValue = OS_CounterSub(tmpTick, *value, OS_counterTableBase[counterId].maxallowedvalue);
		*value = tmpTick;
	}

	return ret;
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mka_getelapsedcountervalue_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
