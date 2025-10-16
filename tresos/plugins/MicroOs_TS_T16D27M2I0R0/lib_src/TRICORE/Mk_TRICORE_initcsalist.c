/* Mk_TRICORE_initcsalist.c
 *
 * This file contains the special function MK_InitCsaList().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 *  A conversion should not be performed between a pointer to object
 *  and an integer type.
 *
 * Reason:
 *  The cast to 'mk_upperctx_t *' is required, because the pointer's raw value
 *  is obtained from hardware, which has no notion of C language types.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_panictailcall.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_startup.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/TRICORE/Mk_TRICORE_exceptionfunctions.h>

/* MK_InitCsaList() - initialize the global CSA list, set FCX, LCX and PCXI accordingly.
 *
 * Parameters:
 *  csaStart - The begin of the CSA area.
 *  csaLimit - The end of the CSA area.
 *
 * This function must never be called from C code!
 *
 * The function is intended to be called only from assembly language code at startup. It expects
 * that the very first CSA from the CSA region defined by csaStart and csaLimit is already
 * used to call this function. It then links the remaining space of that region to a new list of
 * CSAs that are used as freelist (FCX).
 *
 * Before calling, it is essential to ensure that the CSA memory cannot be modified by any
 * outside agency. Disabling interrupts guarantees this for the processor, but for
 * other bus masters such as DMA controllers and the other cores on a multi-core microcontroller
 * further measures may be necessary.
 *
 * This function must only be called by MK_BootCsaList.
 * The arguments csaStart and csaLimit must be read from the rsa and rla fields of
 * the calling core's MK_coreCsas entry.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_InitCsaList, 3
 * !doctype src
*/

MK_ATTR_NO_STACKPROT void MK_InitCsaList(mk_uint32_t csaStart, mk_uint32_t csaLimit)
{
	/* It should be possible to call this function before there is any stack available (currently not required).
	 * Since TriCore has enough registers available, this should not be a problem.
	*/
	mk_uint32_t cx;
	mk_uint32_t fcx;
	mk_uint32_t nCx;
	mk_uint32_t limitIdx;
	mk_uint32_t i;
	mk_upperctx_t *ctx;
	mk_upperctx_t *p_ctx_1;
	mk_address_t a_ctx_1;

	/* Total number of contexts available
	 *
	 * This calculation may return an invalid value when the start/limit symbols are not properly aligned. This is,
	 * however, not a problem, since the result is not used before the correct alignment has been successfully tested.
	*/
	nCx = (csaLimit - csaStart) / sizeof(mk_upperctx_t);

	/* Check that CSA start and end addresses has correct alignment (64 bytes) and that
	 * start address is not greater (or equal) to end address. If the constraint on the start
	 * address is violated, it is possible that we didn't even arrive here.
	 *
	 * Moreover, if all bits of the addresses are contained in MK_CSA_MASK,
	 * these addresses can be correctly represented by FCX, LCX and PCXI.
	*/
	if ( ((csaStart & (~MK_CSA_MASK)) != 0u)
			|| ((csaLimit & (~MK_CSA_MASK)) != 0u)
			|| (csaStart >= csaLimit) )
	{
		/* We are now calling the panic stop function despite knowing that there are no CSAs.
		 * Optimizing compilers are likely to implement this as an unconditional jump in which
		 * case everything will be fine. Otherwise we will end up in the FCU-exception.
		 * This exception is expected to be handled in a way that does not continue microkernel startup.
		*/
		MK_StartupPanicTailCall(MK_panic_MisalignedSymbol);
	}
	else if ( nCx < MK_NCSAMIN )
	{
		/* Call to MK_StartupPanic may fail. See comment above.
		*/
		MK_StartupPanicTailCall(MK_panic_InsufficientResources);
	}
	else
	{
		/* Initialize CSAs starting from the second one (the first one has been used
		 * to call this function and is currently on the used-list).
		*/
		/* Deviation MISRAC2012-1 <+1> */
		ctx = (mk_upperctx_t *)csaStart;

		/* FCX register needs to point to second element
		*/
		p_ctx_1 = &(ctx[1]);
		a_ctx_1 = (mk_address_t)p_ctx_1;
		fcx = MK_AddrToPcx(a_ctx_1);
		cx = fcx;

		/* Now build rest of list (except last element which gets a special treatment)
		*/
		for ( i=1; i<(nCx-1u); i++)
		{
			cx++;
			ctx[i].pcxi = cx;
		}

		/* Tail of list. Terminated using 0.
		*/
		ctx[i].pcxi = 0;

		/* Finally set FCX register to head of the newly created list.
		*/
		MK_MTFCX(fcx);

		/* Index of the CSA which will become LCX, counted from the second CSA.
		 * This CSA is followed by MK_NCSAEXTRA CSAs in the list.
		*/
		limitIdx = nCx - MK_NCSAEXTRA - 2u;

		/* Low water mark --> LCX register. An exception occurs if FCX reaches here.
		*/
		MK_MTLCX(fcx + limitIdx);

		/* Wait until the free list becomes visible.
		*/
		MK_ISYNC();
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
