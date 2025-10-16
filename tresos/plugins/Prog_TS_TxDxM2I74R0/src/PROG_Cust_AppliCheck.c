/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cust_AppliCheck.c          */
/*%%  |                             |  %%  \brief PROG Application check feature */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
 /* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any other type
 *
 *   Reason:
 * This cast is unavoidable since retrieve the function address from a pointer
 *
 * MISRAC2012-2) Deviated Rule: 11.4 (advisory)
 * Convertion should not be performed between a pointer to object and an integer type
 *
 *   Reason:
 * This cast is unavoidable since we addressed a defined software memory area.
 */
 /* NOCOV List
 *
 * NOCOV-NCS_UNITARY_TEST:
 *   code is deactivated for test.
 *
 * Reason:
 * Test are performed under WINDOWS environment.
 *
 */
/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: INT.36
 * Converting a pointer to integer or integer to pointer
 *
 * Reason:
 * this variable contains a flash memory address that will not be subject to pointer arithmetics no risk of alignment issues.
*/
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
#if ((PROG_IMPL_VARIANT  == PROG_IMPL_1) || (PROG_IMPL_VARIANT  == PROG_IMPL_2))
#include "fblFrameworkPublicApi.h"
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)) */
#include "board.h"
#if PROG_WATCHDOG_ENABLE == STD_ON
#include "Watchdog.h"
#endif
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
#if (PROG_PARTIAL_VERIFY_CRC == STD_ON)
u8 m_ubActivePartialVerifyCrc; /* Indicate if Routine VerifyPartialSoftwareChecksum is in progress */
#endif

#if (PROG_CVN_CHECK == STD_ON)
tProgBoolean m_eCvnCheckInProgress;
#endif /* PROG_CVN_CHECK == STD_ON */
/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#if ( ((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)))\
    || ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_2))\
    || ((PROG_PRE_INIT_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2)))\
    )
#define PROG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
u32* pulProgFramework_Api_Array_Ptr;
#define PROG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define PROG_FRAMEWORK_E_OK         1U
#define PROG_FRAMEWORK_E_NOT_OK     0U
#endif /* (((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)))\
        || ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_2))\
        || ((PROG_PRE_INIT_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2)))) */
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11))
#define PROG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
NCS_PRI_VAR u32 m_ulCompTimeoutFLag;
#define PROG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11))*/

#if ((PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_30))
/* Information for the CRC calculation */
NCS_PRI_VAR u16 m_uwExpectedCks;
#endif /* ((PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_30))*/

#if ( ((PROG_APPLI_CHECK_ENABLE == STD_ON) || (PROG_ERASE_MEMORY_ENABLE == STD_ON)) \
    && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO_EB == STD_ON))
NCS_PRI_VAR u8 m_aubMagicNumValue[PROG_MAGIC_NUM_SIZE];
#endif


#if (PROG_CVN_CHECK == STD_ON)
u8 m_aubExpectedCvn[PROG_CVN_LENGTH];
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))
NCS_PRI_VAR tDataBufferType m_aubHashData[PROG_CRC_CALC_SIZE];
#endif
/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if ((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11)))
NCS_PRI_FCT tProgStatus PROG_ReadCompErrorStatus(void);
NCS_PRI_FCT void PROG_CompleteCompatibleInd (tProgCompTimeoutStatus eProgCompTimeoutStatus);
NCS_PRI_FCT tProgCompleteStatus PROG_CompleteCompatibleCheck (void);
#endif /*((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11)))*/
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*-----------------------{PROG_Entry_AutoControl}--------------------------------*/
void PROG_Entry_AutoControl(void)
{
#if PROG_AUTOCONTROL_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2) \
    ||(PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)\
	|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
    DBG_PROG_ENTRY_AUTOCONTROL_ENTRY();
    /* Send NRC 78 before starting the autocontrol check */
    UDS_StopNRC78Timer();
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2)
        ||(PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)
        || (PROG_IMPL_VARIANT == PROG_IMPL_5))*/
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11))
    tProgCompleteStatus eProgCompStatus;
    tProgStatus eProgStatus;

    DBG_PROG_ENTRY_AUTOCONTROL_ENTRY();

    /* Read the flag in No inti RAM to verify if an error occurred during last Complete compatible call */
    eProgStatus = PROG_ReadCompErrorStatus();
    /* Check if no error occurred */
    if (PROG_E_OK == eProgStatus)
    {
        eProgCompStatus = PROG_CompleteCompatibleCheck ();
    }
    else
    {
        eProgCompStatus = PROG_APPL_INVALID;

        /* Call callback to deactivate the watchdog and clear flag in RAM no init */
        /* This will allow a new complete and compatible check */
        PROG_CompleteCompatibleInd(PROG_COMPLETECOMPATIBLE_ERROR);
    }

    m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1); /* Positive response for Routine type 1 */
    m_stDiagMessageInfo.pubData[5] = (u8)((u32)(eProgCompStatus >> 24U) & 0x000000ffU);
    m_stDiagMessageInfo.pubData[6] = (u8)((u32)(eProgCompStatus >> 16U) & 0x000000ffU);
    m_stDiagMessageInfo.pubData[7] = (u8)((u32)(eProgCompStatus >> 8U) & 0x000000ffU);
    m_stDiagMessageInfo.pubData[8] = (u8)(eProgCompStatus & 0x000000ffU);

    UDS_LongRequestEnd(PROG_AUTOCONTROL_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubData, UDS_ACK);
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11))*/
#else
    DBG_PROG_ENTRY_AUTOCONTROL_ENTRY();
#endif
    DBG_PROG_ENTRY_AUTOCONTROL_EXIT();
}
/*-----------------------{End PROG_Entry_AutoControl}----------------------------------*/

#if PROG_AUTOCONTROL_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2) \
    ||(PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)\
	|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
/*-----------------------{PROG_AutoControl_Process}--------------------------------*/
void PROG_AutoControl_Process(void)
{
    tProgCompleteStatus eProgCompStatus;
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2))
    u8 ubVerifySectionCrcReturn = PROG_FRAMEWORK_E_NOT_OK;
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
    tpulVerifySectionCrc pulVerifySectionCrc;

    DBG_PROG_AUTOCONTROL_PROCESS_ENTRY();
    /*Address of verifySection Api*/
    pulVerifySectionCrc = (tpulVerifySectionCrc) pulProgFramework_Api_Array_Ptr[11];
    /* Check if the address is correct */
    ubVerifySectionCrcReturn = pulVerifySectionCrc();
/* CHECK: PARSE */
#else
    DBG_PROG_AUTOCONTROL_PROCESS_ENTRY();
    ubVerifySectionCrcReturn = verifySectionCrc();
#endif

    if ( PROG_FRAMEWORK_E_NOT_OK == ubVerifySectionCrcReturn)
    {
        eProgCompStatus = PROG_APPL_INVALID;
    }
    else
    {
        eProgCompStatus = PROG_APPL_VALID;
    }
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)||(PROG_IMPL_VARIANT == PROG_IMPL_5))
    DBG_PROG_AUTOCONTROL_PROCESS_ENTRY();
    /* Check if the address is correct */
    eProgCompStatus = PROG_VerifySectionCrc();
#else
    DBG_PROG_AUTOCONTROL_PROCESS_ENTRY();
#endif

    m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_SELFTERM | PROG_ROUTINE_PREDIF | PROG_ROUTINE_RESAVAILABLE); /* Positive response */
    m_stDiagMessageInfo.pubData[5] = (u8)(eProgCompStatus & 0x000000ffU);

    UDS_LongRequestEnd(PROG_AUTOCONTROL_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubData, UDS_ACK);
    DBG_PROG_AUTOCONTROL_PROCESS_EXIT();
}
/*-----------------------{End PROG_AutoControl_Process}----------------------------------*/
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2)
        ||(PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)
        || (PROG_IMPL_VARIANT == PROG_IMPL_5))*/
#endif /* PROG_AUTOCONTROL_ENABLE == STD_ON */

#if ((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11)))
/*----------------------------{PROG_CompleteCompatibleCheck}-----------------------------*/
NCS_PRI_FCT tProgCompleteStatus PROG_CompleteCompatibleCheck (void)
{
    tProgCompleteStatus eProgCompStatus;
    ptCompleteCompatibleCallOut pCompleteCompatibleCallOut;
    /* Deviation MISRAC2012-2 */
    u32* pulStartCompAddr;
    u32* pulEndCompAddr;
    /* Deviation MISRAC2012-2 */
    u32* pulEndCompAddrTemp;
    u32* pCompCompaFuncTemp;

    eProgCompStatus = PROG_APPL_INVALID;
    /* Deviation MISRAC2012-2 */
   /* Deviation CERTC-1 */
    pulStartCompAddr = (u32*)PROG_COMP_BLK_START_ADDR;
    /* Deviation MISRAC2012-2 */
   /* Deviation CERTC-1 */
    pulEndCompAddrTemp = (u32*)(PROG_COMP_BLK_START_ADDR + PROG_COMP_BLK_END_SIG_ADDR_OFFSET);

    /* Disable ECC error as the address maybe erased */
    PROG_DisableECCCheck();
    /* Get the 64 bits of the start complete and compatible signature */
    if ((PROG_START_COMP_BLK_HIGH == pulStartCompAddr[0]) && (PROG_START_COMP_BLK_LOW == pulStartCompAddr[1]))
    {
        /* Get the 64 bits of the end complete and compatible signature */
        /* Deviation MISRAC2012-2 */
       /* Deviation CERTC-1 */
        pulEndCompAddr = (u32*)*pulEndCompAddrTemp;

        if ((PROG_END_COMP_BLK_HIGH == pulEndCompAddr[0]) && (PROG_END_COMP_BLK_LOW == pulEndCompAddr[1]))
        {
            /* Call callback to activate the watchdog and write flag in RAM no init */
            PROG_CompleteCompatibleInd(PROG_COMPLETECOMPATIBLE_START);

            /* Deviation MISRAC2012-2 */
            /* Deviation CERTC-1 */
            pCompCompaFuncTemp = (u32*)(PROG_COMP_BLK_START_ADDR + PROG_COMP_BLK_FUNC_ADDR_OFFSET);

            /* Get the complete and compatible function address */
            /* Deviation MISRAC2012-1 */
            /* Deviation CERTC-1 */
            pCompleteCompatibleCallOut = (ptCompleteCompatibleCallOut)*pCompCompaFuncTemp;

            /* Call the callOut function */
            eProgCompStatus = pCompleteCompatibleCallOut();

            /* Call callback to deactivate the watchdog and clear flag in RAM no init */
            PROG_CompleteCompatibleInd(PROG_COMPLETECOMPATIBLE_END);
        }
    }
    /* enable ECC */
    PROG_EnableECCCheck();

    return eProgCompStatus;
}
/*-----------------------{End PROG_CompleteCompatibleCheck}--------------------------------*/


/*-----------------------{PROG_ReadCompErrorStatus}------------------------------------*/
NCS_PRI_FCT tProgStatus PROG_ReadCompErrorStatus(void)
{
    tProgStatus eProgStatus;

    if(m_ulCompTimeoutFLag == PROG_COMP_NO_ERROR)
    {
        eProgStatus = PROG_E_OK;
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    return eProgStatus;
}
/*-----------------------{End PROG_ReadCompErrorStatus}--------------------------------*/

/*-----------------------{PROG_CompleteCompatibleInd}----------------------------------*/
NCS_PRI_FCT void PROG_CompleteCompatibleInd (tProgCompTimeoutStatus eProgCompTimeoutStatus)
{
    switch(eProgCompTimeoutStatus)
    {
        case PROG_COMPLETECOMPATIBLE_START:
            m_ulCompTimeoutFLag = PROG_COMP_ERROR;
            /* Set watchdog to 15ms */
            Watchdog_SetTimeoutValue(PROG_COMP_TIMEOUT_VALUE);
            break;

        case PROG_COMPLETECOMPATIBLE_END:
            /* Set watchdog to its initial value */
            Watchdog_SetTimeoutValue(PROG_INIT_TIMEOUT_VALUE);
            /* ReSet error flag because function return in time */
            m_ulCompTimeoutFLag = PROG_COMP_NO_ERROR;
            break;
        default:
            /* Reset error flag to allow check on next startup */
            m_ulCompTimeoutFLag = PROG_COMP_NO_ERROR;
            break;
    }
}
/*-----------------------{End PROG_CompleteCompatibleInd}------------------------------*/
#endif /*((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_10)||(PROG_IMPL_VARIANT == PROG_IMPL_11)))*/

/*----------------------------{PROG_MemStartErasing}-----------------------------*/
#if (PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT != PROG_IMPL_80)
#if PROG_ERASE_TYPE == PROG_ERASE_BY_ADDR
tProgStatus PROG_MemStartErasing(tProgAddressType ulStartAddress,
        u32 ulEraseLength, tUdsStatus * ErrorCode)
#elif ((PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID) || (PROG_ERASE_TYPE == PROG_ERASE_BY_DYNAMIC_PARTITION_ID))
tProgStatus PROG_MemStartErasing(u8 ubBlockId, tUdsStatus * ErrorCode)
#endif
{
    tProgStatus eProgStatus = PROG_E_NOT_OK;
#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
    u8 ubInvalidateSectionReturn;
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
    tpulinvalidateSection pulinvalidateSection;

    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /*Address of invalidateSection Api*/
    pulinvalidateSection = (tpulinvalidateSection) pulProgFramework_Api_Array_Ptr[10];

    /*Call InvalidateSection API in framework before erasing the section*/
    ubInvalidateSectionReturn = pulinvalidateSection((uint32)ulStartAddress);
/* CHECK: PARSE */
#else
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /*Call InvalidateSection API in framework before erasing the section*/
    ubInvalidateSectionReturn = invalidateSection((uint32)ulStartAddress);
#endif
    if (PROG_FRAMEWORK_E_OK == ubInvalidateSectionReturn)
    {
        eProgStatus = PROG_E_OK;
    }
    else
    {
        *ErrorCode = UDS_NRC_22;
    }
    OSC_PARAM_UNUSED(ulEraseLength);
/* #endif (PROG_IMPL_VARIANT == PROG_IMPL_2)*/
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5) || (PROG_IMPL_VARIANT == PROG_IMPL_30) \
        || ((PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_ERASE_ALL == STD_OFF) && (PROG_ERASE_TYPE == PROG_ERASE_BY_ADDR)))
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /* Call applicative callback */
    eProgStatus = PROG_InvalidateSection(ulStartAddress, ulEraseLength, ErrorCode);
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_11))
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /* Call applicative callback */
    eProgStatus = PROG_InvalidateBlock(m_stCurrentSegment.ubLogicalBlockId);
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEraseLength);
    OSC_PARAM_UNUSED(ErrorCode);
#elif (PROG_IMPL_VARIANT == PROG_IMPL_91)
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /* Call applicative callback */
    eProgStatus = PROG_InvalidateBlock(m_stCurrentSegment.ubSegmentId);
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEraseLength);
    OSC_PARAM_UNUSED(ErrorCode);
#elif PROG_IMPL_VARIANT == PROG_IMPL_20
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /*Call InvalidateSection API  before erasing the section*/
    eProgStatus = PROG_InvalidateSection(ubBlockId);
    if (PROG_E_OK != eProgStatus)
    {
        *ErrorCode = UDS_NRC_72;
    }
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) \
    || ((PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_ERASE_ALL == STD_ON)) || ((PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))) \
    || (PROG_IMPL_VARIANT == PROG_IMPL_31)
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
    /*Call InvalidateSection API  before erasing the section*/
    eProgStatus = PROG_InvalidateSection_BlockID(ubBlockId);
#if(PROG_PARTIAL_VERIFY_CRC == STD_ON)
    /*Erase partial verification infos for the block*/
    PROG_CustomClearPartProgSegList(ubBlockId);
#endif /* #if(PROG_PARTIAL_VERIFY_CRC == STD_ON) */
    if (PROG_E_OK != eProgStatus)
    {
        *ErrorCode = UDS_NRC_72;
    }
#else
    DBG_PROG_MEMSTARTERASING_ENTRY(ubBlockId,ErrorCode);
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_2)   */
    DBG_PROG_MEMSTARTERASING_EXIT(eProgStatus);
    return eProgStatus;
}
#endif /* (PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT != PROG_IMPL_80) */
/*----------------------------{end PROG_MemStartErasing}-------------------------*/

/*----------------------------{PROG_InvalidateSection_BlockID}-----------------------------*/
#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_ERASE_ALL == STD_OFF) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID)) && (PROG_APPLI_CHECK_ALGO_EB == STD_ON))
tProgStatus PROG_InvalidateSection_BlockID(u8 ubBlockId)
{
    tProgStatus eProgStatus;
    u32 ulAddress;
    u8 ubIdx;

    /* Retrieve address of the validity flag */
    ulAddress = ((stConfigSegment[stCfgBlock[ubBlockId].ubFirstSegmentId + stCfgBlock[ubBlockId].ubSegmentNbr - 1u].ulEraseEndAddress
                - m_astCfgMemory[stConfigSegment[stCfgBlock[ubBlockId].ubFirstSegmentId + stCfgBlock[ubBlockId].ubSegmentNbr - 1u].ubMemoryIdx].ulMinValueToWrite)
                + 1U);

    eProgStatus = PROG_MemCheckPageErasing(m_astCfgMemory[stConfigSegment[ubBlockId].ubMemoryIdx].eMemoryType,ulAddress);

    if (eProgStatus == PROG_E_OK)
    {

        for(ubIdx = 0U; ubIdx < PROG_MAGIC_NUM_SIZE; ubIdx++)
        {
            m_aubMagicNumValue[ubIdx] = m_aCfgMagicNumRevokedValue[ubIdx];
        }

        /* Read section flag into flash */
        eProgStatus = PROG_MemDataAccess(
                m_astCfgMemory[stConfigSegment[ubBlockId].ubMemoryIdx].eMemoryType,
                PROG_MEM_OPERATION_TYPE_WRITE,
                ulAddress,
                PROG_MIN_VAL_TO_WRITE,
                m_aubMagicNumValue);
    }
    else
    {
        /* Page is already written in memory, skip writing to avoid re-writing that can cause ECC errors */
        eProgStatus = PROG_E_OK;
    }

    DBG_PROG_INVALIDATESECTION_EXIT(eProgStatus);
    return eProgStatus;
}
#endif /* if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60)) */
/*--------------------------{end PROG_InvalidateSection_BlockID}-------------------------*/


/*----------------------------{PROG_InvalidateSection}-----------------------------*/
#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO_EB == STD_ON))
tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress,
        u32 ulEraseLength, tUdsStatus * ErrorCode)
{
    tProgStatus eProgStatus;
    u32 ulAddress;
    u8 iSegment;
    u8 ubIdx;

    DBG_PROG_INVALIDATESECTION_ENTRY(ulStartAddress,ulEraseLength,ErrorCode);
    eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, ulEraseLength, PROG_MEM_OPERATION_TYPE_ERASE, &iSegment);

    if (eProgStatus == PROG_E_OK)
    {
        /* Retrieve address of the Invalid flag */
        ulAddress = ((stConfigSegment[iSegment].ulEraseEndAddress - (2U*PROG_MIN_VAL_TO_WRITE)) + 1U);
#if (PROG_OTA_DUALBANK_USED == STD_ON)
        ulAddress = PROG_CustomCalcInactiveBankWriteAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/

        eProgStatus = PROG_MemCheckPageErasing(m_astCfgMemory[stConfigSegment[iSegment].ubMemoryIdx].eMemoryType,ulAddress);

        if (eProgStatus == PROG_E_OK)
        {

            for(ubIdx = 0U; ubIdx < PROG_MAGIC_NUM_SIZE; ubIdx++)
            {
                m_aubMagicNumValue[ubIdx] = m_aCfgMagicNumRevokedValue[ubIdx];
            }

            /* Read section flag into flash */
            eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[iSegment].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_WRITE,
                    ulAddress,
                    PROG_MIN_VAL_TO_WRITE,
                    m_aubMagicNumValue);
        }
        else
        {
            /* Page is already written in memory, skip writing to avoid re-writing that can cause ECC errors */
            eProgStatus = PROG_E_OK;
        }
    }

    if (eProgStatus != PROG_E_OK)
    {
        *ErrorCode = UDS_NRC_72;
    }

    DBG_PROG_INVALIDATESECTION_EXIT(eProgStatus);
    return eProgStatus;
}
#endif /* if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60)) */
/*--------------------------{end PROG_InvalidateSection}-------------------------*/

#if PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON
/*----------------------------{PROG_Check_Prg_Dep_Check}-------------------------*/
tProgStatus PROG_Check_Prg_Dep_Check(void)
{
    tProgStatus eProgStatus;
#if !((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    tProgBoolean eProgBoolean;
#endif
    u8 ubLocalSegmentId;
    u32 ulSize;
    u32 ulAddress;

    DBG_PROG_CHECK_PRG_DEP_CHECK_ENTRY();
#if !((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    eProgBoolean = PROG_CheckValidAppl();
#endif

#if !((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    if (PROG_TRUE == eProgBoolean)
    {
#endif
        /* Retrieve address to check */
        ulAddress = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[4U]);

        /* retrieve and store the length to calculate the CRC */
        ulSize = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[8U]);

#if !((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
        eProgStatus = PROG_GetSegmentByAddress(ulAddress, ulSize, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);
#endif
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    /* Check if start address is inside a segment*/
    eProgStatus = PROG_GetSegmentByAddress(ulAddress, 1U, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);
        if(eProgStatus == PROG_E_OK)
        {
            /* Check if end address is inside a segment*/
            eProgStatus=PROG_GetSegmentByAddress((ulAddress + ulSize - 1U), 1U, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);
#endif
                if(eProgStatus == PROG_E_OK)
                {
                    PROG_CRCSetParam(ulAddress, ulSize,PROG_VERIFY_CRC, PROG_FALSE);
                    /* update current segmentID */
                    m_stCurrentSegment.ubSegmentId = ubLocalSegmentId;
                }
                else
                {
                    PROG_Send_NRC(UDS_NRC_31);
#if ((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))||\
    ((PROG_IMPL_VARIANT == PROG_IMPL_90)||(PROG_IMPL_VARIANT == PROG_IMPL_91))
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
                }
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
        }
        else
        {
            PROG_Send_NRC(UDS_NRC_31);
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
#endif
#if !((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
        PROG_Send_NRC(UDS_NRC_31);
#if ((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_5))
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }
#endif
    DBG_PROG_CHECK_PRG_DEP_CHECK_EXIT(eProgStatus);
    return eProgStatus;
}
/*-------------------------{End PROG_Check_Prg_Dep_Check}------------------------*/

/*---------------------{PROG_Entry_CheckDependenciesFinish}----------------------*/
void PROG_Entry_CheckDependenciesFinish(void)
{
#if((PROG_CRC_CALCULATION != PROG_NO_CRC) || ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4)||\
    (PROG_IMPL_VARIANT == PROG_IMPL_5))||((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)))
    u16 uwCrcVal;
#endif /*#if(PROG_CRC_CALCULATION != PROG_NO_CRC)*/

    DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_ENTRY();
#if((PROG_CRC_CALCULATION != PROG_NO_CRC) || ((PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4)||\
    (PROG_IMPL_VARIANT == PROG_IMPL_5))||((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91)))
    PROG_GetCrcValue(&uwCrcVal);
#if((PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4)||(PROG_IMPL_VARIANT == PROG_IMPL_5))
    m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_SELFTERM | PROG_ROUTINE_PREDIF | PROG_ROUTINE_RESAVAILABLE); /* Positive response */
#elif((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
    m_stDiagMessageInfo.pubData[4] = (u8)(PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1); /* Positive response */
#endif
    m_stDiagMessageInfo.pubData[5] = (u8)((uwCrcVal >> 8U) & 0x00FFU);
    m_stDiagMessageInfo.pubData[6] = (u8)(uwCrcVal & 0x00FFU);

    m_stDiagMessageInfo.ulLength = PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE;
    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
    if( (m_stDiagMessageInfo.pubData[1] & 0x80U) != 0x00U)
    {
        /* Reset suppress positive response bit in response*/
        m_stDiagMessageInfo.pubTxData[1] = (u8)(0x01U);
#if (PROG_SUPPRESS_POSITIVE_RESPONSE == FALSE)
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
#else
        m_stDiagMessageInfo.ulLength = 0x00U;
        /* Response shall not be sent */
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
#endif
    }
    else
    {
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
#endif /*(PROG_CRC_CALCULATION != PROG_NO_CRC)*/
    DBG_PROG_ENTRY_CHECKDEPENDENCIESFINISH_EXIT();
}
/*-----------------{End PROG_Entry_CheckDependenciesFinish}----------------------*/

#if((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2) || \
    (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4) || \
    (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91) || \
    (PROG_IMPL_VARIANT == PROG_IMPL_5))
/*-------------------------{PROG_Do_CheckPrgDependencies}------------------------*/
void PROG_Do_CheckPrgDependencies(void)
{

    tProgStatus eProgStatus;
    eProgStatus = PROG_CRC();

    DBG_PROG_DO_CHECKPRGDEPENDENCIES_ENTRY();

    if (PROG_E_OK == eProgStatus)
    {

        /* Emit event PROG_EVENT_CRC_CAL_FINISH */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRC_CAL_FINISH);

    }
    else if (PROG_E_NOT_OK == eProgStatus)
    {
      /* Emit event PROG_EVENT_FAILED */
      PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /*Send response*/
      PROG_Send_NRC(UDS_NRC_72);
    }
    else
    {
      /*Nothing to do*/
    }
    DBG_PROG_DO_CHECKPRGDEPENDENCIES_EXIT();
}
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_2)*/
/*--------------------{End PROG_Do_CheckPrgDependencies}-------------------------*/
#endif /*PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON*/

/*----------------------------{PROG_CheckValidAppl}-----------------------------*/
#if (PROG_APPLI_CHECK_ENABLE == STD_ON)
tProgBoolean PROG_CheckValidAppl(void)
{
    tProgBoolean eProgCompStatus;
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))
    u8 ubisValidApplicationRes;
#ifndef NCS_UNITARY_TEST
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
    tpulisValidApplication pfulisValidApplication;

    DBG_PROG_CHECKVALIDAPPL_ENTRY();
    /*Address of invalidateSection Api*/
    pfulisValidApplication = (tpulisValidApplication) pulProgFramework_Api_Array_Ptr[14];

    /* Call Framework callback that will indicate if application is valid */
    ubisValidApplicationRes = pfulisValidApplication();
/* CHECK: PARSE */
#else
    DBG_PROG_CHECKVALIDAPPL_ENTRY();
    ubisValidApplicationRes = isValidApplication();
#endif

    if (PROG_FRAMEWORK_E_OK != ubisValidApplicationRes)
    {
        eProgCompStatus = PROG_FALSE;
    }
    else
    {
        eProgCompStatus = PROG_TRUE;
    }
    /*#endif ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2)) */
#elif ( (PROG_IMPL_VARIANT == PROG_IMPL_3) || (PROG_IMPL_VARIANT == PROG_IMPL_4)   ||  \
        (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91) || \
        (PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31) || \
        (PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || \
        (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_20) || \
        (PROG_IMPL_VARIANT == PROG_IMPL_80) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
    DBG_PROG_CHECKVALIDAPPL_ENTRY();
    /* Call callback that will indicate if application is valid */
    eProgCompStatus = PROG_IsValidApplication();
#elif (PROG_IMPL_VARIANT == PROG_IMPL_10)
    u32 ulisValidApplicationRes;

    DBG_PROG_CHECKVALIDAPPL_ENTRY();

    ulisValidApplicationRes = PROG_CompleteCompatibleCheck();

    if(PROG_APPL_VALID != ulisValidApplicationRes)
    {
        eProgCompStatus = PROG_FALSE;
    }
    else
    {
        eProgCompStatus = PROG_TRUE;
    }
#else
    DBG_PROG_CHECKVALIDAPPL_ENTRY();
    eProgCompStatus = PROG_TRUE;
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_20) */
    DBG_PROG_CHECKVALIDAPPL_EXIT(eProgCompStatus);
    return eProgCompStatus;
}
#endif /* (PROG_APPLI_CHECK_ENABLE == STD_ON) */
/*----------------------------{end PROG_CheckValidAppl}-------------------------*/

/*----------------------------{PROG_IsValidApplication}-------------------------*/
#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO_EB == STD_ON))
tProgBoolean PROG_IsValidApplication(void)
{
    tProgBoolean eProgBoolean;
    u8 ubIdx;
    tProgStatus eProgStatus;
    u32 ulAddress;
    u16 uwLoopIndex;
    u8 aubValidyValue[PROG_MIN_VAL_TO_WRITE];

    DBG_PROG_ISVALIDAPPLICATION_ENTRY();
    eProgBoolean = PROG_TRUE;
#if (PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)
    for(ubIdx = 0U; ((ubIdx < PROG_SEGMENT_NB) && (eProgBoolean == PROG_TRUE)); ubIdx++)
#else
    for(ubIdx = 0U; ((ubIdx < PROG_BLOCK_NB) && (eProgBoolean == PROG_TRUE)); ubIdx++)
#endif
    {
        if ( stConfigSegment[ubIdx].eValidityCheck == PROG_TRUE)
        {
#if (PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)
            /* Retrieve address of the Invalid flag */
            ulAddress = ((stConfigSegment[ubIdx].ulEraseEndAddress
                        - (2U*m_astCfgMemory[stConfigSegment[ubIdx].ubMemoryIdx].ulMinValueToWrite))
                        + 1U);
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            /* Calculated address on active bank */
            ulAddress = PROG_CustomCalcActiveBankReadAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/
            /* Read section flag into flash */
            eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[ubIdx].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_READ,
                    ulAddress,
                    PROG_MAGIC_NUM_SIZE,
                    aubValidyValue);
#else
            /* Retrieve address of the Invalid flag */
            ulAddress = ((stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ulEraseEndAddress
                        - (2U*m_astCfgMemory[stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ubMemoryIdx].ulMinValueToWrite))
                        + 1U);
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            /* Calculated address on active bank */
            ulAddress = PROG_CustomCalcActiveBankReadAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/
            /* Read section flag into flash */
            eProgStatus = PROG_MemDataAccess(
                            m_astCfgMemory[stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ubMemoryIdx].eMemoryType,
                            PROG_MEM_OPERATION_TYPE_READ,
                            ulAddress,
                            PROG_MAGIC_NUM_SIZE,
                            aubValidyValue);
#endif

            if ( eProgStatus == PROG_E_OK)
            {
                for(uwLoopIndex = 0U; uwLoopIndex < PROG_MAGIC_NUM_SIZE; uwLoopIndex++)
                {
                    if(aubValidyValue[uwLoopIndex] != m_astCfgMemory[stConfigSegment[ubIdx].ubMemoryIdx].ubEraseValue)
                    {
                        eProgBoolean = PROG_FALSE;
                    }
                }
            }
            else
            {
                eProgBoolean = PROG_FALSE;
            }

            if ((eProgStatus == PROG_E_OK) && (eProgBoolean == PROG_TRUE))
            {
#if (PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)
                /* Retrieve address of the valid flag */
                ulAddress = ((stConfigSegment[ubIdx].ulEraseEndAddress
                            - (m_astCfgMemory[stConfigSegment[ubIdx].ubMemoryIdx].ulMinValueToWrite))
                            + 1U);
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            /* Calculated address on active bank */
            ulAddress = PROG_CustomCalcActiveBankReadAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/
                /* Read section flag into flash */
                eProgStatus = PROG_MemDataAccess(
                        m_astCfgMemory[stConfigSegment[ubIdx].ubMemoryIdx].eMemoryType,
                        PROG_MEM_OPERATION_TYPE_READ,
                        ulAddress,
                        PROG_MAGIC_NUM_SIZE,
                        aubValidyValue);
#else
                /* Retrieve address of the valid flag */
                ulAddress = ((stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ulEraseEndAddress
                            - m_astCfgMemory[stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ubMemoryIdx].ulMinValueToWrite)
                            + 1U);
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            /* Calculated address on active bank */
            ulAddress = PROG_CustomCalcActiveBankReadAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/
                /* Read section flag into flash */
                eProgStatus = PROG_MemDataAccess(
                                m_astCfgMemory[stConfigSegment[stCfgBlock[ubIdx].ubFirstSegmentId + stCfgBlock[ubIdx].ubSegmentNbr - 1u].ubMemoryIdx].eMemoryType,
                                PROG_MEM_OPERATION_TYPE_READ,
                                ulAddress,
                                PROG_MAGIC_NUM_SIZE,
                                aubValidyValue);
#endif

                if (PROG_E_OK == eProgStatus)
                {
                    for (uwLoopIndex = 0U; uwLoopIndex < PROG_MAGIC_NUM_SIZE; uwLoopIndex++)
                    {
                        if(aubValidyValue[uwLoopIndex] != m_aCfgMagicNumProgrammedValue[uwLoopIndex])
                        {
                            eProgBoolean = PROG_FALSE;
                        }
                    }
                }
                else
                {
                    eProgBoolean = PROG_FALSE;
                }
            }
        }
    }

    DBG_PROG_ISVALIDAPPLICATION_EXIT(eProgBoolean);
    return eProgBoolean;
}
#endif /* ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO == PROG_EB)) */
/*----------------------------{end PROG_IsValidApplication}---------------------*/

/*----------------------------{PROG_CustomSetDownloadVerificationSuccess}-------------------------*/
#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO_EB == STD_ON))
tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess)
{
    tProgStatus eProgStatus;
    u8 ubIdx;
    u32 ulAddress;

#if (PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)

    OSC_PARAM_UNUSED(ubLogicalBlockId);

    /* Retrieve address of the validity flag */
    ulAddress = ((stConfigSegment[ubLogicalSegmentId].ulEraseEndAddress
                - m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].ulMinValueToWrite)
                + 1U);
#else
    /* Retrieve address of the validity flag */
    ulAddress = ((stConfigSegment[stCfgBlock[ubLogicalBlockId].ubFirstSegmentId + stCfgBlock[ubLogicalBlockId].ubSegmentNbr - 1u].ulEraseEndAddress
                - m_astCfgMemory[stConfigSegment[stCfgBlock[ubLogicalBlockId].ubFirstSegmentId + stCfgBlock[ubLogicalBlockId].ubSegmentNbr - 1u].ubMemoryIdx].ulMinValueToWrite)
                + 1U);
#endif /*(PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)*/

#if (PROG_OTA_DUALBANK_USED == STD_ON)
    ulAddress = PROG_CustomCalcInactiveBankWriteAddr(ulAddress);
#endif /*(PROG_OTA_DUALBANK_USED == STD_ON)*/


    if (PROG_TRUE == ubCompareSuccess)
    {
        for (ubIdx = 0U; ubIdx < PROG_MAGIC_NUM_SIZE; ubIdx++)
        {
            m_aubMagicNumValue[ubIdx] = m_aCfgMagicNumProgrammedValue[ubIdx];
        }
    }
    else
    {
        for(ubIdx = 0U; ubIdx < PROG_MAGIC_NUM_SIZE; ubIdx++)
        {
            m_aubMagicNumValue[ubIdx] = m_aCfgMagicNumRevokedValue[ubIdx];
        }
    }

#if (PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)
    /* Read section flag into flash */
    eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_WRITE,
                    ulAddress,
                    m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].ulMinValueToWrite,
                    m_aubMagicNumValue);
#else
    OSC_PARAM_UNUSED(ubLogicalSegmentId);
    /* Read section flag into flash */
    eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[stCfgBlock[ubLogicalBlockId].ubFirstSegmentId + stCfgBlock[ubLogicalBlockId].ubSegmentNbr - 1u].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_WRITE,
                    ulAddress,
                    m_astCfgMemory[stConfigSegment[stCfgBlock[ubLogicalBlockId].ubFirstSegmentId + stCfgBlock[ubLogicalBlockId].ubSegmentNbr - 1u].ubMemoryIdx].ulMinValueToWrite,
                    m_aubMagicNumValue);
#endif /*(PROG_ERASE_TYPE != PROG_ERASE_BY_BLOCK_ID)*/

#if ( (PROG_REPROGMEMM_ENABLED == STD_ON)                         \
      ||((PROG_FLASHWRAPPER_ENABLED == STD_ON)                    \
      &&((PROG_RAM_MODE == PROG_MEMORY_ASYNCHRONOUS)              \
      || (PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS)            \
      || (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS)        \
      || (PROG_CUSTOM_MEMORY_MODE == PROG_MEMORY_ASYNCHRONOUS))))
    /* Modification to support asynchronous memory access and to not have a false UDS_NRC_72 at PROG_CRC_COMPARE */
    if (PROG_E_BUSY == eProgStatus)
    {
        eProgStatus = PROG_E_OK;
    }
#endif


    return eProgStatus;
}
#endif /* ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60) && (PROG_APPLI_CHECK_ALGO == PROG_EB)) */
/*----------------------------{end PROG_CustomSetDownloadVerificationSuccess}---------------------*/

/*-------------------------{PROG_CheckProgrammingRequest}-----------------------*/

tProgBoolean PROG_CheckProgrammingRequest(void)
{
    tProgBoolean eBootFromAppli;

#if PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT != PROG_IMPL_2) && (PROG_IMPL_VARIANT != PROG_IMPL_4) \
    && (PROG_IMPL_VARIANT != PROG_IMPL_11) && (PROG_IMPL_VARIANT != PROG_IMPL_91))
    u8 eStatus;
#endif
#endif /* PROG_CHECK_PROGRAMMING_REQUEST_ENABLE */

    DBG_PROG_CHECKPROGRAMMINGREQUEST_ENTRY();
    eBootFromAppli = PROG_FALSE;

#if PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT != PROG_IMPL_2) && (PROG_IMPL_VARIANT != PROG_IMPL_4) \
    && (PROG_IMPL_VARIANT != PROG_IMPL_11)&& (PROG_IMPL_VARIANT != PROG_IMPL_91))
    eStatus = BoardIsSwReset();

    if (PROG_TRUE == eStatus)
    {
#if ((PROG_IMPL_VARIANT != PROG_IMPL_2) && (PROG_IMPL_VARIANT != PROG_IMPL_4))
        eStatus = PROG_CheckProgRequest();

        if (PROG_BOOT_REPROG == eStatus)

#endif
        {
            /* comming from application must stay in boot */
            eBootFromAppli = TRUE;
        }
        else
        {
            /* must jump in application after tested it */
            /* eBootFromAppli already set to FALSE */
        }

    }
    else
    {
        /* Nothing */
        /* eBootFromAppli already set to PROG_FALSE */
    }
#endif /*if ((PROG_IMPL_VARIANT != PROG_IMPL_2) && (PROG_IMPL_VARIANT != PROG_IMPL_4)
    && (PROG_IMPL_VARIANT != PROG_IMPL_11)&& (PROG_IMPL_VARIANT != PROG_IMPL_91)) */


#endif /* PROG_CHECK_PROGRAMMING_REQUEST_ENABLE */
    DBG_PROG_CHECKPROGRAMMINGREQUEST_EXIT(eBootFromAppli);
    return eBootFromAppli;
}


/*--------------------------{end PROG_CheckProgrammingRequest}---------------------*/

/*----------------------------{PROG_SwitchApplicationMode}-------------------------*/

void PROG_SwitchApplicationMode(void)
{
#if PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    u32 ulAddrStartAPP;
    ptAPPL_START_ADDR pfuAPPL_START_ADDR;
#endif/* #if (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_90) */
#endif /* PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON */

    DBG_PROG_SWITCHAPPLICATIONMODE_ENTRY();

#if PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON
    /* Disable all interruption before the jump */
    BoardDisableInterrupts();
    /* Stop all communications on the network */
    EB_Com_Deactivate();
    /* Call PROG_SwitchApplicationModeInd callback to notify upper layers that switching to application will happen*/
    PROG_SwitchApplicationModeInd();

#if PROG_WATCHDOG_ENABLE == STD_ON
    /* Trigger Watchdog before jumping in Application */
    Watchdog_Trigger();
#endif

#if (!((PROG_IMPL_VARIANT == PROG_IMPL_2) || (PROG_IMPL_VARIANT == PROG_IMPL_4) \
    || (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)))
    /* Jump in application */
    PROG_JumpToApplication();
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_1) */

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    /* get jump address from ESS */
    Prog_GetEssApplicationStartAddress(&ulAddrStartAPP);
    /* get the address of the application to jump in */
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    pfuAPPL_START_ADDR = (ptAPPL_START_ADDR)(ulAddrStartAPP);
    /* Jump in application */
    pfuAPPL_START_ADDR();
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_10)|| (PROG_IMPL_VARIANT == PROG_IMPL_90) */
#endif /* PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON */
    DBG_PROG_SWITCHAPPLICATIONMODE_EXIT();
}

/*----------------------------{end PROG_SwitchApplicationMode}----------------------*/
/*----------------------------{PROG_Entry_ChecksumByRange}-------------------------*/

void PROG_Entry_ChecksumByRange(void)
{
#if ((PROG_IMPL_VARIANT == PROG_IMPL_30) && (PROG_RANGE_CKS == STD_ON))
    u32 ulStartAddress;
    u32 ulEndAddress;
    u32 ulSize;
    u8 ubLocalSegmentId;
    tProgStatus eProgStatus;

    DBG_PROG_ENTRY_CHECKSUMBYRANGE_ENTRY();

    /* Retrieve start address */
    ulStartAddress = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[4U]);

    /* Retrieve end address */
    ulEndAddress = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[8U]);

    /* Retrieve expected Checksum */
    m_uwExpectedCks = PROG_RetrieveRequestData16(&m_stDiagMessageInfo.pubData[12U]);

    /*Calculate data length*/
    ulSize = (ulEndAddress - ulStartAddress) + 1U;

    /*PROG_GetSegmentByAddress is called with a size of 1 just to check if the start address and
    end address are inside of a segment. This is used in the case of Range CRC Calculation to avoid
    errors when the CRC is calculated on multiple segments that are separated by a gap. */

    /* Check if start address is inside a segment*/
    eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, 1U, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);
    if(eProgStatus == PROG_E_OK)
    {
        /* Check if end address is inside a segment*/
        eProgStatus=PROG_GetSegmentByAddress((ulEndAddress - 1U), 1U, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);
        if(eProgStatus == PROG_E_OK)
        {
            /*Initialize the Checksum calculation*/
            PROG_CRCSetParam(ulStartAddress, ulSize, PROG_VERIFY_CRC, PROG_FALSE);

            /* update current segmentID */
            m_stCurrentSegment.ubSegmentId = ubLocalSegmentId;

            /*call also the custom callback*/
            PROG_CustomStartChecksumCalc();

#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
            /*Set the Programming status: CKS Good Size/Address*/
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_SIZE, PROG_TRUE);
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_ADDRESS, PROG_TRUE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/
        }
        else
        {
            PROG_Send_NRC(UDS_NRC_31);

            /*Send PROG_EVENT_FINISHED event*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED );

#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
            /*Set the Programming status: CKS Wrong Size/Address*/
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_SIZE, PROG_FALSE);
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_ADDRESS, PROG_FALSE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/
        }
    }
    else
    {
        PROG_Send_NRC(UDS_NRC_31);

        /*Send PROG_EVENT_FINISHED event*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);

#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
        /*Set the Programming status: CKS Wrong Size/Address*/
        PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_SIZE, PROG_FALSE);
        PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_ADDRESS, PROG_FALSE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/
    }
    DBG_PROG_ENTRY_CHECKSUMBYRANGE_EXIT();
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_30) && (PROG_RANGE_CKS == STD_ON)) */
}

/*----------------------------{end PROG_Entry_ChecksumByRange}---------------------*/
/*----------------------------{PROG_RangeChecksumFinish}-------------------------*/

tProgStatus PROG_RangeChecksumFinish(void)
{
#if ((PROG_IMPL_VARIANT == PROG_IMPL_30) && (PROG_RANGE_CKS == STD_ON))
    u16 uwCalculatedCrc;
    tProgStatus eProgStatus;

    DBG_PROG_RANGECHECKSUMFINISH_ENTRY();
    /*call custom checksum calculation callback*/
    eProgStatus = PROG_CustomChecksumCalc(&uwCalculatedCrc);
    if(PROG_E_OK == eProgStatus)
    {
        if(m_uwExpectedCks == uwCalculatedCrc)
        {
            /*Indicate CRC calc. is done and the result is ok*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
        }
        else
        {
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            /* Send NEGATIVE RESPONSE */
            UDS_LongRequestEnd(PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_72);
#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
            /*Wrong Checksum, update ProgrammingStatus*/
            PROG_SetProgrammingStatus( PROG_RC_CHECKSUM_VERIFY, PROG_FALSE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/
        }
    }
    else if(PROG_E_BUSY == eProgStatus)
    {
        /*Checksum calculation on going*/
    }
    else /*(PROG_E_NOT_OK == eProgStatus)*/
    {
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* Send NEGATIVE RESPONSE */
        UDS_LongRequestEnd(PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_72);
#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
        /*Wrong Checksum, update ProgrammingStatus*/
        PROG_SetProgrammingStatus( PROG_RC_CHECKSUM_VERIFY, PROG_FALSE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/
    }
    DBG_PROG_RANGECHECKSUMFINISH_EXIT(eProgStatus);
    return eProgStatus;

#else
    return PROG_E_OK;
#endif /* ((PROG_IMPL_VARIANT == PROG_IMPL_30) && (PROG_RANGE_CKS == STD_ON)) */
}

/*----------------------------{end PROG_RangeChecksumFinish}---------------------*/
/*----------------------------{PROG_RetrieveRequestData32}---------------------*/
u32 PROG_RetrieveRequestData32(u8 * pubBufferIn)
{
    /* Data to return */
    u32 ulData;
    /* Shift Index */
    u8 ubShift;
    /* Current Index of buffer to copy */
    u16 uwIdx;
    /* End Index of buffer to copy */
    u16 uwEndIndex;

    /* Initialization */
    ulData = 0x00000000;
    uwEndIndex = 3U;
    ubShift = 4U;

    /* Copy each byte of the buffer */
    for (uwIdx = 0; uwIdx <= uwEndIndex; uwIdx++)
    {
        /* Decrease shift index */
        ubShift--;
        ulData |= (u32)(((u32)(pubBufferIn[uwIdx])) << (8U * ubShift));
    }

    return ulData;
}
/*----------------------------{end PROG_RetrieveRequestData32}---------------------*/
/*----------------------------{PROG_RetrieveRequestData16}---------------------*/
u16 PROG_RetrieveRequestData16(u8 * pubBufferIn)
{
    /* Data to return */
    u16 uwData;
    /* Shift Index */
    u8 ubShift;
    /* Current Index of buffer to copy */
    u16 uwIdx;
    /* End Index of buffer to copy */
    u16 uwEndIndex;

    /* Initialization */
    uwData = 0x0000;
    uwEndIndex = 1U;
    ubShift = 2U;

    /* Copy each byte of the buffer */
    for (uwIdx = 0; uwIdx <= uwEndIndex; uwIdx++)
    {
      /* Decrease shift index */
      ubShift--;
      uwData |= (u16)(((u16)(pubBufferIn[uwIdx])) << (8U * ubShift));
    }

    return uwData;
}
/*----------------------------{end PROG_RetrieveRequestData16}---------------------*/

#if ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40))
/*-----------------------------{PROG_PartialVerificationCrc}--------------------------------*/
tUdsStatus PROG_PartialVerificationCrc(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;
    DBG_PROG_REQUESTSEED_ENTRY(pulLen,aubUdsData );

    eStatus = PROG_GenericRequest(pulLen, aubUdsData,
            PROG_HSM_PROG_EV_PROG_EVENT_REQ_PART_SW_VERIF);
    DBG_PROG_REQUESTSEED_EXIT(eStatus);
    return (eStatus);
}
/*---------------------------{end PROG_PartialVerificationCrc}------------------------------*/
#endif /*((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40)) */


/*---------------------------{PROG_Entry_PartialVerificationCrc}-----------------------------*/
void PROG_Entry_PartialVerificationCrc(void)
{
#if ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40))
#if (PROG_CVN_CHECK == STD_ON)
    u8 ubIdx;
#endif /* PROG_CVN_CHECK == STD_ON */
    u16 uwBlockIdentifier = 0U;
    u8 ubBlockId = 0U;
    u8 ubSegIndex;
    u8 ubSegNbr;
    u8 ubTempBlockIdLen;
    u32 aulSegProgSize[PROG_MAX_RD_PER_BLOCK];
    tProgStatus eProgStatus;
    u8 ubLoopIndex;
    u8 ubCrcCvnLength;
    u8 ubCrcCvnLengthlsb;
    tProgStatus eIndexFound;
    eProgStatus = PROG_E_OK;
    eIndexFound = PROG_E_NOT_OK;
    m_ubActivePartialVerifyCrc = TRUE;
    /* Extract block ID */
    ubTempBlockIdLen = (u8)(m_stDiagMessageInfo.pubData[PROG_RC_ROUTINE_INFO_BASE_INDEX] >> 4U);

    if (ubTempBlockIdLen == PROG_PART_VERIF_BLOCKID_LEN_1BYTE)
    {
        uwBlockIdentifier = (u16) m_stDiagMessageInfo.pubData[PROG_RC_PART_VERIF_BLOCKID_BASE_INDEX];
    }
    else if (ubTempBlockIdLen == PROG_PART_VERIF_BLOCKID_LEN_2BYTES)
    {
        uwBlockIdentifier = PROG_RetrieveRequestData16(&m_stDiagMessageInfo.pubData[PROG_RC_PART_VERIF_BLOCKID_BASE_INDEX]);
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    if (PROG_E_OK == eProgStatus)
    {
        /* Find the index table from block identifier */
        for (ubLoopIndex = 0U;
            (ubLoopIndex < PROG_BLOCK_NB) && (PROG_E_NOT_OK == eIndexFound);
            ubLoopIndex++)
        {
            /* Find the corresponding index of block in the table */
            if (stCfgBlock[ubLoopIndex].uwBlockIdentifier == uwBlockIdentifier)
            {
                /* Index has been found, parsing of index will stop here */
                eIndexFound = PROG_E_OK;

                /* Update the block index with the stCfgBlock table index */
                ubBlockId = ubLoopIndex;
            }
        }

        if (PROG_E_OK == eIndexFound)
        {
            /* Get the stored data about the programmed segments */
            PROG_CustomGetPartProgSegList(ubBlockId, aulSegProgSize, &ubSegNbr);

            if (0U != ubSegNbr)
            {
                m_stSegList.ubSegNbr = ubSegNbr;
                for (ubSegIndex = 0; ubSegIndex < m_stSegList.ubSegNbr; ubSegIndex++)
                {
                    m_stSegList.astSeg[ubSegIndex].ulSize = aulSegProgSize[ubSegIndex];
                    m_stSegList.astSeg[ubSegIndex].ulStartAddress = stConfigSegment[stCfgBlock[ubBlockId].ubFirstSegmentId + ubSegIndex].ulStartAddress;
                    m_stSegList.astSeg[ubSegIndex].ubSegmentId = stCfgBlock[ubBlockId].ubFirstSegmentId + ubSegIndex;
                }
/* 2 possible cases for the received request:
- Only CRC is checked
- Only CVN is checked
*/
                /* Retrieve the length to know if CRC or CVN */
                ubCrcCvnLength = m_stDiagMessageInfo.pubData[PROG_RC_ROUTINE_INFO_BASE_INDEX + 1U];
                /*Retrieve the Lower Nibble of Byte #4 to check if it is having only 0x00 value*/
                ubCrcCvnLengthlsb = (m_stDiagMessageInfo.pubData[PROG_RC_ROUTINE_INFO_BASE_INDEX] & 0x0FU);
                if ((ubCrcCvnLength == PROG_CRC32_LENGTH) && (ubCrcCvnLengthlsb == 0x00U) && (m_stDiagMessageInfo.ulLength == ((PduLengthType)PROG_PARTIAL_SW_ROUTINE_CRC_LEN + ubTempBlockIdLen - 1U)))
                {
/* Only CRC computation is performed (in case where signature and CRC shall be performed in transfered data and not in flashed data, signature is skipped)*/
#if (PROG_CRC_CALCULATION != PROG_NO_CRC)
#if (PROG_CRC_CALCULATION == PROG_TD_CRC32)
                    /* Extract expected CRC */
                    m_ulExpectedCks = PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[6U + (u16)ubTempBlockIdLen]);
#endif
/* CHECK: NOPARSE */
/* NOCOV-FEATURE_NOT_USED */
#if (PROG_CRC_CALCULATION == PROG_TD_CRC16)
                    /* Extract expected CRC */
                    m_uwExpectedCks = PROG_RetrieveRequestData16(&m_stDiagMessageInfo.pubData[6U + (u16)ubTempBlockIdLen]);
#endif
/* CHECK: PARSE */
#if (PROG_GET_EXPECTED_CRC_ENABLED == STD_ON)
                    /* Extract expected CRC */
                    if (m_ulExpectedCks == 0U)
                    {
                        /* expected CRC not in the request, use callback to get it */
                        PROG_CustomGetExpectedCrc(m_stCurrentSegment.ubLogicalBlockId, &m_ulExpectedCks);
                    }
#endif /* #if (PROG_GET_EXPECTED_CRC_ENABLED == STD_ON) */

#if (PROG_SEG_LIST_CKS == STD_ON)
                    /* Init CRC calculation for first segment */
                    PROG_CRCSetParam(m_stSegList.astSeg[0U].ulStartAddress, m_stSegList.astSeg[0U].ulSize, PROG_VERIFY_CRC, PROG_FALSE);
                    m_stCurrentSegment.ubLogicalBlockId = ubBlockId;
                    m_stCurrentSegment.ubSegmentId = m_stSegList.astSeg[0U].ubSegmentId;

                    /* Init the segment list CRC index */
                    m_stSegList.ubSegListCrcIndex = 0U;
#endif /* #if(PROG_SEG_LIST_CKS == STD_ON) */
#endif /*endif ((PROG_CRC_CALCULATION != PROG_NO_CRC) */
                }
#if (PROG_CVN_CHECK == STD_ON)
                /* Check the length of CVN and the length of the routine (23 or 24 bytes): 23 bytes + block ID length -1 */
                else if ((ubCrcCvnLength == PROG_CVN_LENGTH) && (ubCrcCvnLengthlsb == 0x00U) &&(m_stDiagMessageInfo.ulLength == ((PduLengthType)PROG_PARTIAL_SW_ROUTINE_CVN_LEN + ubTempBlockIdLen - 1U)))
                {
                    /* Set CVN check is in progress */
                    m_eCvnCheckInProgress = PROG_TRUE;
                    for (ubIdx=0; ubIdx < PROG_CVN_LENGTH; ubIdx++)
                    {
                        /* Extract expected CVN from 7th or 8th element: 4 + 2 + block ID length */
                        m_aubExpectedCvn[ubIdx] = (u8)(m_stDiagMessageInfo.pubData[(PROG_RC_ROUTINE_INFO_BASE_INDEX+2U+ubTempBlockIdLen)+ubIdx]);
                    }
                    /* Launch CVN verification */
                    eProgStatus = PROG_CustomCvnVerification(ubBlockId, &m_aubExpectedCvn[0]);
                    (void)PROG_CheckPartialSwCvnStatus(eProgStatus);
                }
#endif /*endif (PROG_CVN_CHECK == STD_ON)*/
                else
                {
                    /* Send POSITIVE RESPONSE with failed routine status */
                    m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_NOK;

                    /* Set length and status of */
                    m_stDiagMessageInfo.ulLength     = PROG_CRC_COMP_RESPONSE_SIZE;
                    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

                    /* Emit event PROG_EVENT_FINISHED */
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

                    /* Send response */
                    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
                }
            }
            else
            {
                /* Send POSITIVE RESPONSE with failed routine status */
                m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_NOK;

                /* Set length and status of */
                m_stDiagMessageInfo.ulLength     = PROG_CRC_COMP_RESPONSE_SIZE;
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

                /* Emit event PROG_EVENT_FINISHED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

                /* Send response */
                UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
            }
        }
        else
        {
                /* Send POSITIVE RESPONSE with failed routine status */
                m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_NOK;

                /* Set length and status of */
                m_stDiagMessageInfo.ulLength     = PROG_CRC_COMP_RESPONSE_SIZE;
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

                /* Emit event PROG_EVENT_FINISHED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

                /* Send response */
                UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
        }
    }
    else
    {
                /* Send POSITIVE RESPONSE with failed routine status */
                m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_NOK;

                /* Set length and status of */
                m_stDiagMessageInfo.ulLength     = PROG_CRC_COMP_RESPONSE_SIZE;
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

                /* Emit event PROG_EVENT_FINISHED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

                /* Send response */
                UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
#endif /*((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40)) */
}
/*------------------------{end PROG_Entry_PartialVerificationCrc}--------------------------*/

/*---------------------------{PROG_Exit_PartialVerificationCrc}-----------------------------*/
void PROG_Exit_PartialVerificationCrc(void)
{
#if ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40))
    /* Store active state */
    m_stSegList.ubSegNbr = 0;
    m_ubActivePartialVerifyCrc = FALSE;
#endif /* ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40)) */
}
/*------------------------{end PROG_Exit_PartialVerificationCrc}--------------------------*/

/*---------------------------{PROG_CheckPartialSegmentListCrc}-----------------------------*/
void PROG_CheckPartialSegmentListCrc(void)
{
#if ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40))
    if (m_stSegList.ubSegListCrcIndex < (m_stSegList.ubSegNbr - 1U))
    {
        m_stSegList.ubSegListCrcIndex++;

        PROG_CRCSetParam(m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ulStartAddress,
                        m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ulSize,
                        m_stDataProgVerification.ubAlgo,
                        PROG_TRUE);

        m_stCurrentSegment.ubSegmentId = m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ubSegmentId;
    }
    else
    {
        /* Computation is finished */
#if (PROG_CRC_CALCULATION != PROG_NO_CRC)
        if (PROG_VERIFY_CRC == m_stDataProgVerification.ubAlgo)
        {
#if (PROG_CRC_CALCULATION == PROG_TD_CRC32)
            /* Store calculated CRC */
            PROG_CustomWriteCRC(m_stDataProgVerification.ulVal);
#else
/* CHECK: NOPARSE */
/* NOCOV-FEATURE_NOT_USED */
            /* Store calculated CRC */
            PROG_CustomWriteCRC((u32)m_stDataProgVerification.uwVal);
/* CHECK: PARSE */
#endif

            /* Compare the CRCs*/
            /* the return code is not needed because the result of the compare is
            treated using events by the Prog<OEM> state machine*/
            (void)PROG_CRC_Compare();
        }
        else
#endif
/* CHECK: NOPARSE */
/* NOCOV-FEATURE_NOT_USED */
        {
            /* couldn't happen, error case */
        }
/* CHECK: PARSE */
    }
#endif /* ((PROG_PARTIAL_VERIFY_CRC == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_40)) */
}
/*------------------------{end PROG_CheckPartialSegmentListCrc}--------------------------*/

/*-------------------------------{PROG_CheckPartialSwCvnStatus}----------------------------------*/
#if (PROG_CVN_CHECK == STD_ON)
tProgStatus PROG_CheckPartialSwCvnStatus(tProgStatus eProgStatus)
{
    tProgStatus eProgStatusRet = eProgStatus;

    if (eProgStatus != PROG_E_BUSY)
    {
        if (eProgStatus == PROG_E_OK)
        {
            /* Send POSITIVE RESPONSE with same data than request*/
            m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_OK;
        }
        else
        {
            /* Send POSITIVE RESPONSE with failed routine status */
            m_stDiagMessageInfo.pubTxData[4] = PROG_ROUTINE_FINISHED_NOK;
            eProgStatusRet                   = PROG_E_OK;
        }
        /* Set length and status of */
        m_stDiagMessageInfo.ulLength     = PROG_CRC_COMP_RESPONSE_SIZE;
        m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
        /* CVN check terminated, reset the flag */
        m_eCvnCheckInProgress            = PROG_FALSE;

        /* Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
        /* Send response */
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
    else
    {
        /* Nothing to do */
    }
    return eProgStatusRet;
}
#endif /* PROG_CVN_CHECK == STD_ON */
/*-----------------------------{end PROG_CheckPartialSwCvnStatus}-----------------------------*/

#if((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))
/*-------------------------------{PROG_Entry_LogicalBlockHash}----------------------------------*/
void PROG_Entry_LogicalBlockHash(void)
{
#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))
    u8 ubSegIndex;
    u8 ubSegNbr;
    u8 ubLoopIndex;
    u32 aulSegProgSize[PROG_MAX_RD_PER_BLOCK];
    u16 uwBlockIdentifier = 0U;
    u8 ubBlockId = 0U;
    tProgStatus eIndexFound = PROG_E_NOT_OK;

    DBG_PROG_ENTRY_LOGICALBLOCKHASH_ENTRY();

    /* Extract block ID */
    uwBlockIdentifier = (u16) m_stDiagMessageInfo.pubData[PROG_RC_LOGICAL_BLOCK_NUMBER_INDEX];

    /* Find the index table from block identifier */
    for (ubLoopIndex = 0U; (ubLoopIndex < PROG_BLOCK_NB) && (PROG_E_NOT_OK == eIndexFound); ubLoopIndex++)
    {
        /* Find the corresponding index of block in the table */
        if (stCfgBlock[ubLoopIndex].uwBlockIdentifier == uwBlockIdentifier)
        {
            /* Index has been found, parsing of index will stop here */
            eIndexFound = PROG_E_OK;

            /* Update the block index with the stCfgBlock table index */
            ubBlockId = ubLoopIndex;
        }
    }

    if (PROG_E_OK == eIndexFound)
    {
        /* Get the stored data about the programmed segments */
        PROG_CustomGetPartProgSegList(ubBlockId, aulSegProgSize, &ubSegNbr);

        if (0U != ubSegNbr)
        {
            m_stSegList.ubSegNbr = ubSegNbr;

            for (ubSegIndex = 0; ubSegIndex < m_stSegList.ubSegNbr; ubSegIndex++)
            {
                m_stSegList.astSeg[ubSegIndex].ulSize = aulSegProgSize[ubSegIndex];
                m_stSegList.astSeg[ubSegIndex].ulStartAddress = stConfigSegment[stCfgBlock[ubBlockId].ubFirstSegmentId + ubSegIndex].ulStartAddress;
                m_stSegList.astSeg[ubSegIndex].ubSegmentId = stCfgBlock[ubBlockId].ubFirstSegmentId + ubSegIndex;
            }

            /* Init CRC calculation for first segment */
            PROG_CRCSetParam(m_stSegList.astSeg[0U].ulStartAddress, m_stSegList.astSeg[0U].ulSize, PROG_VERIFY_HASH, PROG_FALSE);
            m_stCurrentSegment.ubLogicalBlockId = ubBlockId;
            m_stCurrentSegment.ubSegmentId = m_stSegList.astSeg[0U].ubSegmentId;

            /* Init the segment list CRC index */
            m_stSegList.ubSegListCrcIndex = 0U;

            /* Call crypto library to start the hash computation */
            (void) PROG_ComputeHashStart(PROG_CSM_HASH_FOR_SIGNATURE_ID, NULL_PTR, 0U, NULL_PTR);
        }
        else
        {
            /* Block invalid: erased or never programmed or corrupted, send NEGATIVE RESPONSE */
            for (ubLoopIndex = 0; (ubLoopIndex < PROG_DIGEST_LENGTH);  ubLoopIndex++)
            {
                /* store 0xFF as return value of hash */
                m_stDiagMessageInfo.pubTxData[PROG_RC_ROUTINE_STATUS_BASE_INDEX + ubLoopIndex] = 0xFF;
            }

            m_stDiagMessageInfo.ulLength = PROG_LOGICAL_BLOCK_HASH_RESP_SIZE;
            m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

            UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);

            /* Emit event failed */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
        }

    }
    else
    {
        m_stDiagMessageInfo.ulLength = PROG_NRC_SIZE;
        /* Block id not found, send NEGATIVE RESPONSE */
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, UDS_NRC_31);

        /* Emit event failed */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
    DBG_PROG_ENTRY_LOGICALBLOCKHASH_EXIT();
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))*/
}
/*-------------------------------{end PROG_Entry_LogicalBlockHash}--------------------------------------*/

/*-------------------------------{PROG_ComputeBlockHash}--------------------------------------*/
tProgStatus PROG_ComputeBlockHash(void)
{
    tProgStatus eProgStatus = PROG_E_BUSY;
#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))
    u32 ulWriteSizeOfData;
    u32 ulReadLength;
    u32 ulStartAddress;
    #if (PROG_CRY_PRESENT == STD_ON)
    u32 ulAddr;
    tProgCryState eCryState;
#endif /*(PROG_CRY_PRESENT == STD_ON)*/
    u8 ubAddressShift = 0;

    DBG_PROG_COMPUTEBLOCKHASH_ENTRY();

    ulWriteSizeOfData = m_stReprogInfo.ulReceivedSizeOfData;

#if (PROG_CRY_PRESENT == STD_ON)

    eCryState = PROG_GetCryptoState();

    if ((PROG_HASH_START != eCryState) && (PROG_HASH_UPDATE != eCryState) && (PROG_HASH_FINISH != eCryState))
#endif /*(PROG_CRY_PRESENT == STD_ON)*/
    {
        /* Is there still data to use for programming verification */
        if (m_stDataProgVerification.ulCnt < ulWriteSizeOfData)
        {
            /* Specific case to manage: For some OEM, hash shall be computed also on Address and Length of the received segment
             => Add address and Length on the first Prog_CRC call for this segment */
#if (PROG_COMPUTE_HASH_WITH_ADDR_LEN == STD_ON)
            if (0U == m_stDataProgVerification.ulCnt)
            {
#if PROG_COMPUTE_HASH_WITH_PHYS_ADDR == STD_ON
                /* Apply offset on address */
                if (PROG_MEM_TYPE_FLASH == m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType)
                {
                    /* Internal Flash */
                    ulAddr = (u32)(m_stDataProgVerification.ulAdd + PROG_FLASH_ADDR_OFFSET);
                }
#if (PROG_FLASH_EXT_MEMORY_USE == PROG_TRUE)
                else if (PROG_MEM_TYPE_FLASH_EXT == m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType)
                {
                    /* external Flash */
                    ulAddr = (u32)( m_stDataProgVerification.ulAdd - PROG_FLASH_EXT_ADDR_OFFSET);
                }
#endif
#if (PROG_CUSTOM_MEMORY_USE == PROG_TRUE)
                else if (PROG_MEM_TYPE_CUSTOM == m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType)
                {
                    /* Custom Memory */
                    ulAddr = (u32)(m_stDataProgVerification.ulAdd - PROG_CUSTOM_MEMORY_ADDR_OFFSET);
                }
#endif
                else
#endif /* PROG_COMPUTE_HASH_WITH_PHYS_ADDR == STD_ON */
                {
                    /* RAM */
                    ulAddr = m_stDataProgVerification.ulAdd;
                }
                m_aubHashData[0U] = (u8)(ulAddr >> 24U);
                m_aubHashData[1U] = (u8)(ulAddr >> 16U);
                m_aubHashData[2U] = (u8)(ulAddr >> 8U);
                m_aubHashData[3U] = (u8)(ulAddr);
                m_aubHashData[4U] = (u8)(m_stCurrentSegment.ulSize >> 24U);
                m_aubHashData[5U] = (u8)(m_stCurrentSegment.ulSize >> 16U);
                m_aubHashData[6U] = (u8)(m_stCurrentSegment.ulSize >> 8U);
                m_aubHashData[7U] = (u8)(m_stCurrentSegment.ulSize);

                ubAddressShift = 8U;
            }
            else
            {
                /* Nothing to do */
            }
#endif /*((PROG_COMPUTE_HASH_WITH_ADDR_LEN == STD_ON)*/
            if ((ulWriteSizeOfData - m_stDataProgVerification.ulCnt) >= (PROG_CRC_CALC_SIZE - (u32) ubAddressShift))
            {
                ulReadLength = PROG_CRC_CALC_SIZE - (u32) ubAddressShift;
            }
            else
            {
                ulReadLength = (ulWriteSizeOfData - m_stDataProgVerification.ulCnt - (u32) ubAddressShift);
            }

            /* Calculate the read address                    */
            /* The read is done using the logical address */
            ulStartAddress = m_stDataProgVerification.ulAdd;

            eProgStatus =
                PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_READ, ulStartAddress, ulReadLength, &m_aubHashData[ubAddressShift]);

            if (PROG_E_NOT_OK != eProgStatus)
            {

                PROG_ComputeHashUpdate(m_aubHashData, (u32)(ulReadLength + (u32) ubAddressShift));

                /* increment Hash calculated length */
                m_stDataProgVerification.ulAdd += ulReadLength;
                m_stDataProgVerification.ulCnt += ulReadLength;

                /* return status BUSY */
                eProgStatus = PROG_E_BUSY;

            }
        }
        else
        {
            /* Emit event PROG_EVENT_CRC_FINISH*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRC_FINISH);
            /* return status OK */
            eProgStatus = PROG_E_OK;
        }
    }
#if (PROG_CRY_PRESENT == STD_ON)
    else
    {
        eProgStatus = PROG_E_BUSY;
    }
    DBG_PROG_COMPUTEBLOCKHASH_EXIT(eProgStatus);
#endif /*(PROG_CRY_PRESENT == STD_ON)*/

#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))*/
    /* return status */
    return eProgStatus;
}
/*-----------------------------{end PROG_ComputeBlockHash}------------------------------------*/

/*-------------------------------{PROG_LogicalBlockHashFinish}----------------------------------*/
void PROG_LogicalBlockHashFinish(void)
{
#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))
    u8 ubLoopIndex;
    tProgStatus eProgStatus = PROG_E_NOT_OK;

    DBG_PROG_LOGICALBLOCKHASHFINISH_ENTRY();

    m_stSegList.ubSegNbr = 0;

#if (PROG_CRY_PRESENT == STD_ON)
   eProgStatus = PROG_GetCryptoStatus();
#endif
    /* If no errors occurred */
    if (PROG_E_OK == eProgStatus)
    {
        for (ubLoopIndex = 0; ((ubLoopIndex < PROG_DIGEST_LENGTH) && (PROG_E_OK == eProgStatus));  ubLoopIndex++)
        {
            /* store hash */
            m_stDiagMessageInfo.pubTxData[PROG_RC_ROUTINE_STATUS_BASE_INDEX + ubLoopIndex] = m_aubComputedMessageDigest[ubLoopIndex];
        }

        m_stDiagMessageInfo.ulLength = PROG_LOGICAL_BLOCK_HASH_RESP_SIZE;
        m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
    else
    {
        m_stDiagMessageInfo.ulLength = PROG_NRC_SIZE;
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;

        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
    DBG_PROG_LOGICALBLOCKHASHFINISH_EXIT();
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_31) && (PROG_REPROG_TYPE == PROG_STANDARD_REPROG))*/
}
/*-----------------------------{end PROG_LogicalBlockHashFinish}-----------------------------*/
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_31))*/
