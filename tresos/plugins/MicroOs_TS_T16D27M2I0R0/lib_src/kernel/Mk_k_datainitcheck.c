/* Mk_k_datainitcheck.c
 *
 * This file contains the function MK_DataInitCheck().
 * The function performs a simple test that the .data and .bss sections of the microkernel
 * have been initialized.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>

/* MK_DataInitCheck() performs a simple test that the .data and .bss sections of the microkernel
 * have been initialized. To ensure that it has been called correctly it also checks the
 * 128-bit startup key against the value expected at the expected call.
 *
 * !LINKSTO Microkernel.Function.MK_DataInitCheck, 1
 * !doctype src
*/
void MK_DataInitCheck(mk_uint32_t p1, mk_uint32_t p2, mk_uint32_t p3, mk_uint32_t p4)
{
	/* This is effectively a comparison for equality ("==") of each of the key parameters
	 * to its respective expected MK_ENDKEY.
	*/
	if ( ( (p1 ^ MK_ENDKEY_1) |
		   (p2 ^ MK_ENDKEY_2) |
		   (p3 ^ MK_ENDKEY_3) |
		   (p4 ^ MK_ENDKEY_4) ) == 0u )
	{
		/* Test MK_Ram.
		*/
		if ( (MK_initTestData == MK_INITTEST_VALUE) && (MK_initTestBss == 0u) )
		{
#if MK_MAXCORES <= 1		/* not on multi-core systems */
			/* The two variables are OK. Now trash their values so that even a soft reset won't get a false result.
			*/
			MK_initTestData = MK_INITTEST_TRASH;
			MK_initTestBss = MK_INITTEST_TRASH;
#endif
		}
		else
		{
			MK_StartupPanic(MK_panic_DataSectionsNotInitialized);
		}
#if MK_MAXCORES > 1
		/* Test MK_Ram_CX.
		*/
		{
			/* The kernel control variables aren't set up, so use MK_HwGetCoreIndex.
			 *
			 * We use mk_uint32_t instead of mk_objectid_t for the core id, since we use it in unsigned
			 * calculations in the following. At this point, the coreId will never be negative, so this
			 * is safe.
			*/
			mk_uint32_t coreId = (mk_uint32_t) MK_HwGetCoreIndex();
			mk_uint32_t *pData = MK_initTestDataTable[coreId];
			mk_uint32_t *pBss = MK_initTestBssTable[coreId];

			if ( (*pData == (MK_INITTEST_VALUE + coreId)) && (*pBss == 0u) )
			{
				/* The two variables are OK.
				 * Now trash their values so that even a soft reset won't get a false result.
				*/
				*pData = MK_INITTEST_TRASH + coreId;
				*pBss = MK_INITTEST_TRASH;
			}
			else
			{
				MK_StartupPanic(MK_panic_DataSectionsNotInitialized);
			}
		}
#endif
	}
	else
	{
		MK_StartupPanic(MK_panic_IncorrectStartupKey);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
