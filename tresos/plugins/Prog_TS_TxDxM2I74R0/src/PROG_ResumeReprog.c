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
/*%%   _____________________________   %%  \file PROG_ResumeReprog.c             */
/*%%  |                             |  %%  \brief Resume a reprogramming         */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2018 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/


/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/* Storage of RD param during erasing in case of resume */
tRDParam m_stRDParam;
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

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

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

#define PROG_RESUM_ADDR_SIZE    4U

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

#if PROG_RESUM_REPROG == STD_ON
/** \brief Perform the start of resume process
 **
 ** This function is called when resume shall be done to start resume operations
 **
 ** \param[in] ubBlockId BlockId to resume
 ** \param[in] ubRDSegmentId Segment to resume
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  start succeed
 ** \retval PROG_E_NOT_OK  start failed
 **
 **/
tProgStatus PROG_ResReprog_StartResume(u8 ubBlockId,u8 ubRDSegmentId);
#endif

/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
#if (PROG_IMPL_VARIANT == PROG_IMPL_50)
/*-------------------------{PROG_Entry_ResumeVerification}-----------------------*/
void PROG_Entry_ResumeVerification(void)
{
#if PROG_RESUM_REPROG == STD_ON

    if (UDS_ACK == m_stDiagMessageInfo.ubDiagStatus)
    {

        PROG_RestoreResumeInfo();
        (void)PROG_ComputeHashStart(PROG_CSM_HASH_FOR_SIGNATURE_ID,NULL_PTR,0U,NULL_PTR);


        /* Init the segment list CRC index */
        m_stSegList.ubSegListCrcIndex = 0U;
        if (m_stSegList.ubSegNbr == 0U)
        {
            /*no need to recompute hash*/
            /* Emit event PROG_EVENT_FINISHED */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

        }
        else
        {
            /* Init CRC calculation for first segment */
            PROG_CRCSetParam(m_stSegList.astSeg[0U].ulStartAddress, m_stSegList.astSeg[0U].ulSize, PROG_VERIFY_HASH, PROG_FALSE);
            m_stCurrentSegment.ubSegmentId = m_stSegList.astSeg[0U].ubSegmentId;

        }
    }
    else
    {
        /*Error was detected Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }

#endif
}
/*--------------------{end PROG_Entry_ResumeVerification}------------------------*/
#endif

/*----------------------------{PROG_GetResumeAddress}----------------------------*/
#if PROG_RESUM_REPROG == STD_ON
tUdsStatus PROG_GetResumeAddress(PduLengthType *pulLen, u8 *aubUdsData)
{
    u8 LogicalBlockId;
    u32 ResumeAddress;
    tUdsStatus eUdsStatus;

    if((pulLen != NULL_PTR) && (aubUdsData != NULL_PTR))
    {
        /* Set Memory address size */
        aubUdsData[3U] = PROG_RESUM_ADDR_SIZE;
        for (LogicalBlockId = 0U; LogicalBlockId < PROG_BLOCK_NB; LogicalBlockId++)
        {
            ResumeAddress = PROG_CustomGetResumeAddress(LogicalBlockId);
            aubUdsData[4U + (PROG_RESUM_ADDR_SIZE*LogicalBlockId)] = (u8)(ResumeAddress >> 24U);
            aubUdsData[5U + (PROG_RESUM_ADDR_SIZE*LogicalBlockId)] = (u8)(ResumeAddress >> 16U);
            aubUdsData[6U + (PROG_RESUM_ADDR_SIZE*LogicalBlockId)] = (u8)(ResumeAddress >> 8U);
            aubUdsData[7U + (PROG_RESUM_ADDR_SIZE*LogicalBlockId)] = (u8)(ResumeAddress);
        }
        *pulLen = (PROG_BLOCK_NB * PROG_RESUM_ADDR_SIZE) + 4U;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        eUdsStatus = UDS_ERR_COHE;
    }

    return eUdsStatus;
}
#endif
/*-------------------------{end PROG_GetResumeAddress}---------------------------*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_50)
/*----------------------{PROG_ResReprog_CheckSegmentListVerif}-------------------*/
void PROG_ResReprog_CheckSegmentListVerif(void)
{
#if PROG_RESUM_REPROG == STD_ON
    if (m_stSegList.ubSegListCrcIndex < (m_stSegList.ubSegNbr-1U))
    {
        m_stSegList.ubSegListCrcIndex++;
        PROG_CRCSetParam(m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ulStartAddress,  m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ulSize, m_stDataProgVerification.ubAlgo, PROG_TRUE);
        m_stCurrentSegment.ubSegmentId = m_stSegList.astSeg[m_stSegList.ubSegListCrcIndex].ubSegmentId;

    }
    else
    {
        /* Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);

    }
#endif
}
/*------------------{end PROG_ResReprog_CheckSegmentListVerif}-------------------*/
#endif

/*-------------------------{PROG_ResReprog_EraseStatusCheck}-------------------------*/
#if PROG_RESUM_REPROG == STD_ON
void PROG_ResReprog_EraseStatusCheck(u8 ubBlockId)
{
    u8 ubSegmentNbr;
    u8 ubSegmentId;

    (void)PROG_GetSegmentByBlockId(ubBlockId, &ubSegmentId, &ubSegmentNbr);
    PROG_CustomStoreResumeAddress(ubBlockId, stConfigSegment[ubSegmentId].ulStartAddress);
}
#endif
/*--------------------{end PROG_ResReprog_EraseStatusCheck}---------------------*/

/*-------------------------{PROG_ResReprog_EraseStatusCheck}-------------------------*/
#if PROG_RESUM_REPROG == STD_ON
tProgStatus PROG_ResReprog_CheckResume(u32 ulAddress, u8 ubBlockId, tProgBoolean *ubResumeNeed)
{
    u8           ubRDSegmentId;
    u8           ubSegmentId;
    u8           ubSegmentNbr;
    u32          ulResumeAddress;
    tProgStatus  eProgStatus = PROG_E_NOT_OK;
    tProgEraseStatus eEraseStatus;

    *ubResumeNeed = FALSE;

    ulResumeAddress = PROG_CustomGetResumeAddress(ubBlockId);

    if (ulAddress == ulResumeAddress)
    {
        /* Get Id of the addressed segment and id of the first segment of the block */
        (void)PROG_GetSegmentByAddress(ulAddress,1U, PROG_MEM_ACCESS_TYPE_WRITE, & ubRDSegmentId);
        (void)PROG_GetSegmentByBlockId(ubBlockId, &ubSegmentId, &ubSegmentNbr);

        if (ubRDSegmentId == ubSegmentId)
        {
            /* Check if logical block is already erased */
            eEraseStatus=PROG_CustomGetEraseStatus(ubBlockId);

            if (PROG_E_ERASED == eEraseStatus)
            {
                /* Block is erase, no resume is required */
                eProgStatus = PROG_E_OK;
            }
            else
            {
                /* Resume shall be done */
                eProgStatus = PROG_ResReprog_StartResume(ubBlockId,ubRDSegmentId);
                *ubResumeNeed = TRUE;
            }
        }
        else
        {
            /* Resume shall be done */
            eProgStatus = PROG_ResReprog_StartResume(ubBlockId,ubRDSegmentId);
            *ubResumeNeed = TRUE;
        }
    }
    else
    {
        /* Get segment Id of RequestDownload address and of ResumeAddress to identify if they belong to same segment */
        (void)PROG_GetSegmentByAddress(ulAddress,1U, PROG_MEM_ACCESS_TYPE_WRITE, &ubRDSegmentId);
        (void)PROG_GetSegmentByAddress(ulResumeAddress,1U, PROG_MEM_ACCESS_TYPE_WRITE, &ubSegmentId);

        if (ubRDSegmentId == ubSegmentId)
        {
            /* if same segment, that means that a resume address has already been stored for this segment => don't update ResumeAddress */
            eProgStatus = PROG_E_OK;
        }
        else
        {
            /* This is the first download for this segment, store address as new ResumeAddress  */
            PROG_CustomStoreResumeAddress(ubBlockId,ulAddress);
            eProgStatus = PROG_E_OK;
        }
    }

    return eProgStatus;
}
#endif
/*--------------------{end PROG_ResReprog_EraseStatusCheck}---------------------*/

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------{Prog_ResReprog_StartResume}-------------------------*/
#if PROG_RESUM_REPROG == STD_ON
tProgStatus PROG_ResReprog_StartResume(u8 ubBlockId,u8 ubRDSegmentId)
{

    tProgStatus  eProgStatus;

    eProgStatus = PROG_CheckProgrammingCounter(ubBlockId);
    if (PROG_E_OK == eProgStatus)
    {
        /* store current RD param */
        m_stRDParam.ulStartAddress = m_stCurrentSegment.ulStartAddress;
        m_stRDParam.ulMemorySize = m_stCurrentSegment.ulSize;
        /*Prepare erasing of the current segment*/
        m_stCurrentSegment.ulStartAddress=stConfigSegment[ubRDSegmentId].ulEraseStartAddress;
        m_stCurrentSegment.ubLogicalBlockId=ubBlockId;

        m_stCurrentSegment.ulSize=(stConfigSegment[ubRDSegmentId].ulEraseEndAddress -
                                                stConfigSegment[ubRDSegmentId].ulEraseStartAddress) + 1U;
        m_stCurrentSegment.ubSegmentNbr=1U;

        /* Emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_RESUME);

    }
    else
    {
        /* Resume cannot be done, programming counter has reached its maximum */
        /* or Programming Counter incrementation operation returned an error */
    }

    return eProgStatus;
}
#endif
/*-----------------------{end Prog_ResReprog_StartResume}-----------------------*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_50)
/*-----------------------{PROG_Entry_Resume_Finish}------------------------------*/
void PROG_Entry_Resume_Finish(void)
{

    /*Restore RD param*/
    m_stCurrentSegment.ulStartAddress = m_stRDParam.ulStartAddress;
    m_stCurrentSegment.ulSize = m_stRDParam.ulMemorySize;
    m_stReprogInfo.ulReceivedSizeOfData = 0U;

    /* Reset Prog verification variable */
    m_stDataProgVerification.ulCnt = 0U;
    m_stDataProgVerification.ulAdd = m_stCurrentSegment.ulStartAddress;

    /* prepare response */
    m_stDiagMessageInfo.pubTxData[1U] = PROG_SIZE_OF_NB_BLOCK_LEN;
    m_stDiagMessageInfo.pubTxData[2U] = (u8)(
            (u16)(PROG_MAX_BYTE_IN_TD >> 8U) & 0x00FFU);
    m_stDiagMessageInfo.pubTxData[3U] = (u8)(PROG_MAX_BYTE_IN_TD & 0x00FFU);

    if(m_stDiagMessageInfo.ubDiagStatus == UDS_ACK)
    {
        /* Send positive response*/
        UDS_LongRequestEnd(PROG_RD_RESPONSE_SIZE,
            m_stDiagMessageInfo.pubTxData, UDS_ACK);
    }
    else
    {
        /* Send negative response*/
        UDS_LongRequestEnd(PROG_RD_RESPONSE_SIZE,
            m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }

}
/*---------------------{end PROG_Entry_Resume_Finish}----------------------------*/
#endif /* if (PROG_IMPL_VARIANT == PROG_IMPL_50)*/

