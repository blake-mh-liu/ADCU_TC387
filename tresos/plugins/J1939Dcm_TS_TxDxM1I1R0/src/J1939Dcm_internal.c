/* *--------{ EB Automotive C Source File }-------- */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 17.8 (Advisory)
 *    A function parameter should not be modified.
 *
 *    Reason:
 *    - function parameter shall be modified , to implement related functionality
 */


/* Include J1939Dcm header file, this is used for Dcm specific types and services compiler switches */
#include <J1939Dcm.h>
/* include own header */
#include <J1939Dcm_internal.h>

#include <J1939Dcm_Lcfg.h>


#define  J1939DCM_START_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

FUNC(void, J1939DCM_CODE) J1939Dcm_Memcpy(P2VAR(uint8, AUTOMATIC, J1939DCM_VAR) lp_Dst,
                                       P2CONST(uint8, AUTOMATIC, AUTOMATIC) lp_Src,
                                       VAR(uint32, AUTOMATIC) luw_Nb)
{
    DBG_J1939DCM_MEMCPY_ENTRY(lp_Dst, lp_Src, luw_Nb);
    while ( (uint32)0 != luw_Nb)
    {
    /* Deviation MISRAC2012-1 <1> */
        *(lp_Dst) = *(lp_Src);
        lp_Dst++;
        lp_Src++;
    /* Deviation MISRAC2012-1 <1> */
        luw_Nb--;
    }
    DBG_J1939DCM_MEMCPY_EXIT(lp_Dst, lp_Src, luw_Nb);
}


#define  J1939DCM_STOP_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>



