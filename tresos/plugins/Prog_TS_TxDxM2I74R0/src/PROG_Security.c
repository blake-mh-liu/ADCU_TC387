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
/*%%   _____________________________   %%  \file PROG_Security.c                 */
/*%%  |                             |  %%  \brief PROG security feature          */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
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
#include "board.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */

#if (PROG_CRY_PRESENT == STD_ON)
#include "PROG_Cry.h"
#endif

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
/*                                                                               */
#define PROG_HSM_IDLE               0U
#define PROG_HSM_UPDATEINIT_BLOCK   1U
#define PROG_HSM_UPDATE_BLOCK       2U
#define PROG_HSM_UPDATE_FINISH      3U

#define PROG_HSM_CHECKSUM_SIZE      16U
#define PROG_HSM_OFFSET_FOR_MAC     0U
/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */
#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
NCS_PRI_VAR u8 m_ubBootAuthenticationStoredEvent;
#endif

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
NCS_PRI_VAR u8 m_ubBootAuthenticationPending;
#if (PROG_CSM_HASH_USED == STD_ON)
/* Hash algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_DIGEST_LENGTH];
#elif (PROG_CSM_MAC_USED == STD_ON)
/* Mac algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_SECURE_CHECKSUM_SIZE_IN_BYTES];
#else
/* nothing */
#endif
#endif

#if (PROG_HSM_MAC_USED == STD_ON)
NCS_PRI_VAR u8 m_ubHsmCurrentStep;
#endif

#if ((PROG_HSM_MAC_USED == STD_ON)&&((PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5)))

NCS_PRI_VAR u8 m_ubUnsignedLB_SecBoot = PROG_E_OK;
#endif /* PROG_HSM_MAC_USED */

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR u32 m_ulBlockAddr;
NCS_PRI_VAR u32 m_ulBlockLength;
#endif

#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))
/* Variable used to indicate the HSM Firmware Update States */
NCS_PRI_VAR u8 m_ubHsmFuUpdateCurrentStep;
#endif /*#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91)) */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
#if (PROG_HSM_MAC_USED == STD_ON)
void PROG_HsmMacGenerateStart(void);
#endif /* PROG_HSM_MAC_USED */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
/*-----------------------------{PROG_SecurityInit}-------------------------------*/
void PROG_SecurityInit(void)
{
    DBG_PROG_SECURITYINIT_ENTRY();

    m_ubBootAuthenticationPending = PROG_NO_AUTHENT;

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    m_ubBootAuthenticationStoredEvent = PROG_NO_EVENT;
#endif

    DBG_PROG_SECURITYINIT_EXIT();
}
/*---------------------------{end PROG_SecurityInit}-----------------------------*/

/*-------------------------{PROG_SecurityPendingOperation}-----------------------*/
tProgBoolean PROG_SecurityPendingOperation(void)
{
    tProgBoolean PendingOperation;
    DBG_PROG_SECURITYPENDINGOPERATION_ENTRY();

    if (PROG_NO_AUTHENT != m_ubBootAuthenticationPending)
    {
        PendingOperation = PROG_TRUE;
    }
    else
    {
        PendingOperation = PROG_FALSE;
    }
    DBG_PROG_SECURITYPENDINGOPERATION_EXIT(PendingOperation);
    return PendingOperation;
}
/*----------------------{end PROG_SecurityPendingOperation}----------------------*/
#endif


/*-----------------------{PROG_UnsignedMacGenerate}----------------------*/
#if((PROG_IMPL_VARIANT == PROG_IMPL_3)|| (PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
void PROG_UnsignedMacGenerate(void)
{
#if (PROG_HSM_MAC_USED == STD_ON)
    /*Variable to loop through all the segments*/
        u8 ubIdx;
    /*Loop through all blocks from the configuration to decide which blocks needs MAC Generation at this stage*/
    for (ubIdx = 0U; ubIdx < PROG_SEGMENT_NB;)
    {
        /*Check if the Logical block has Signature check enabled*/
        if((stConfigSegment[ubIdx].eVerifySignature) != PROG_TRUE)
        {
            /*Logical Block does not have signature check enabled and hence we need to generate the MAC for Secure Boot verification*/
            m_stCurrentSegment.ubSegmentId = ubIdx;
            if(m_ubHsmCurrentStep == PROG_HSM_IDLE)
            {
                /*Call the API only for the first time for a Logical Block*/
                PROG_HsmMacGenerateStart();
            }
            /*Call the HSM Manage Background function to monitor the status of MAC Generation by HSM*/
            PROG_HsmManage();
        }
        else
        {
           /* Do nothing */
        }
        if(m_ubUnsignedLB_SecBoot == PROG_E_OK)
        {
            /*Signature verification is supported for this Logical Block.Nothing to do at this step as the MAC Generation already
            * happens at Submit signature step and proceed to next Logical Block entry in the configuration*/
            /*Previous Unsigned Logical Block MAC Generation is Successfull.Proceed for next entry in the configuration*/
            ubIdx++;
            /* Check if the next segment is signed segment*/
            if((ubIdx < PROG_SEGMENT_NB) && (stConfigSegment[ubIdx].eVerifySignature != PROG_TRUE))
            {
            /*Initialise the Status variable back to init variable*/
                m_ubUnsignedLB_SecBoot = PROG_E_BUSY;
            }
        }
        else if(m_ubUnsignedLB_SecBoot == PROG_E_NOT_OK)
        {
            /*MAC Generation failed for a logical block.Hence we cannot proceed further and we need to return failure status*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_UNSIGNEDMACGEN_FAILED);
            break;
        }
        else
        {
            /*do nothing*/
        }
    }
    if(m_ubUnsignedLB_SecBoot == PROG_E_OK)
    {
        /*MAC is generated successfully for all Logical Blocks.We can proceed for next step*/
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_UNSIGNEDMACGEN_FINISHED);
    }
    else
    {
        /*do nothing*/
    }
#else
    /*HSM is not supported in the configuration.Hence MAC Generation step is not needed and we can proceed to next state*/
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_UNSIGNEDMACGEN_FINISHED);
#endif
}
#endif
/*-----------------------{end PROG_UnsignedMacGenerate}-------------------*/


#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
/*------------------------{PROG_SecurityChecksumNotification}------------------------*/
void PROG_SecurityChecksumNotification(void)
{
    DBG_PROG_SECURITYCHECKSUMNOTIFICATION_ENTRY();

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    if (PROG_BOOT_AUTHENT == m_ubBootAuthenticationPending)
    {
        /* Invalid checksum */
        PROG_CustomInvalidateBootloaderChecksum();

        /* Write checksum */
        PROG_CustomSetBootloaderChecksum(&m_aubChecksum[0U]);

        /* Valid checksum */
        PROG_CustomValidateBootloaderChecksum();

        /* Authentication is finished */
        m_ubBootAuthenticationPending = PROG_NO_AUTHENT;

        /* Check if there is a pending event */
        if (PROG_NO_EVENT != m_ubBootAuthenticationStoredEvent)
        {
            /* Post Event in state machine */
            PROG_HsmEmit(&PROG_HsmScPROG, m_ubBootAuthenticationStoredEvent);
        }
    }
    else if (PROG_APP_AUTHENT == m_ubBootAuthenticationPending)
#endif
    {
#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
#if (PROG_BLU_ACTIVE == STD_ON)
        if (PROG_TRUE == m_ubBLUPattern)
        {
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_BLU_PROGRESS);
        }
        else
#endif /*(PROG_BLU_ACTIVE == STD_ON)*/
        {
#if ((PROG_IMPL_VARIANT == PROG_IMPL_11) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
            /* emit event to go to check memory finished state */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#elif (PROG_IMPL_VARIANT == PROG_IMPL_30)
#if (PROG_HSM_MAC_USED == STD_ON)
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#endif
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
            /* Response shall be sent from Validation Finish state*/
            if((stConfigSegment[m_stCurrentSegment.ubSegmentId].eVerifySignature) == PROG_TRUE)
            {
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5)*/

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
            m_ubBootAuthenticationPending = PROG_NO_AUTHENT;
#if (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Write checksum of the corresponding Block identifier */
            PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubLogicalBlockId);
#else
            /* Write checksum of the corresponding Segment identifier */
            PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubSegmentId);
#endif /*(PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)*/
#endif /*((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            PROG_EnableECCCheck();
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
            /* Send pending response to CheckMemory request or checkprog dep. request */
            UDS_LongRequestEnd(PROG_CRC_COMP_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);

#elif (PROG_IMPL_VARIANT == PROG_IMPL_30)
            /* send positive response only when SecureBoot operations need not be performed*/
            UDS_LongRequestEnd(PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);
#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
            /* Good Checksum/Signature, update ProgrammingStatus */
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_VERIFY, PROG_TRUE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/

            /* Set validity flag */
            PROG_CustomSetAppValidity(PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[PROG_CPD_STARTADDR_OFFSET]), PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[PROG_CPD_ENDADDR_OFFSET]));
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_30)*/
        }
#endif /*PROG_SECURE_APPLI_CHECKSUM_COMPUTATION*/
    }
#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    else
    {
        /* error case */
    }
#endif

    DBG_PROG_SECURITYCHECKSUMNOTIFICATION_EXIT();
}
/*---------------------{end PROG_SecurityChecksumNotification}-----------------------*/
#endif

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
/*------------------------{PROG_SecurityStorePendingEvent}-----------------------*/
void PROG_SecurityStorePendingEvent(u8 EventToStore)
{
    DBG_PROG_SECURITYSTOREPENDINGEVENT_ENTRY(EventToStore);

    /* Store event to be emitted after security computation is finished */
    m_ubBootAuthenticationStoredEvent =  EventToStore;

    DBG_PROG_SECURITYSTOREPENDINGEVENT_EXIT();
}
/*--------------------{end PROG_SecurityStorePendingEvent}-----------------------*/

/*------------------------{PROG_SecurityComputeBootChecksum}-----------------------*/
void PROG_SecurityComputeBootChecksum(void)
{
    DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_ENTRY();

    /* Start Hash computation on configured Bootloader range*/
    m_ubBootAuthenticationPending = PROG_BOOT_AUTHENT;

#if (PROG_CSM_HASH_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    (void)PROG_ComputeHashStart(PROG_CSM_SECURE_HASH_ID,
                                (u8*)PROG_AUTHENTICATED_BOOT_START_ADDR,
                                PROG_AUTHENTICATED_BOOT_START_LENGTH,
                                &m_aubChecksum[0U]);
#else
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)PROG_AUTHENTICATED_BOOT_START_ADDR,
                                PROG_AUTHENTICATED_BOOT_START_LENGTH,
                                &m_aubChecksum[0U]);
#endif

    DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_EXIT();
}
/*--------------------{end PROG_SecurityComputeBootChecksum}-----------------------*/
#endif

#if ((PROG_AUTHENTICATED_BOOT_ENABLE == STD_ON) && (PROG_BOOT_VERIFICATION == STD_ON))
/*-----------------------{PROG_GetComputedBootloaderChecksum}----------------------*/
tProgStatus PROG_GetComputedBootloaderChecksum(u8 * pubComputedChecksum)
{
    tProgStatus eProgStatus;
    tProgBoolean eValidBootloaderChecksum;

    DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_ENTRY(pubComputedChecksum);

    eValidBootloaderChecksum = PROG_CustomIsValidBootloaderChecksum();

    /* Verify checksum validity */
    if (PROG_TRUE == eValidBootloaderChecksum)
    {
        /* Get checksum */
        PROG_CustomGetComputedBootloaderChecksum(pubComputedChecksum);
        eProgStatus = PROG_E_OK;
    }
    else
    {
        /* Checksum is invalid and shall be computed again */
        eProgStatus = PROG_E_NOT_OK;
    }
    DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_EXIT(eProgStatus);
    return eProgStatus;
}
/*-----------------------{end PROG_GetComputedBootloaderChecksum}-------------------*/
#endif


/*------------------------{PROG_SecurityComputeAppChecksum}-----------------------*/
void PROG_SecurityComputeAppChecksum(void)
{
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))
    if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType != PROG_HSM_PARTITION)
    {
#endif
#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_ENTRY();

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
    /* Start Hash computation on configured Application range */
    m_ubBootAuthenticationPending = PROG_APP_AUTHENT;
#endif

#if (PROG_CSM_HASH_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    (void)PROG_ComputeHashStart(PROG_CSM_SECURE_HASH_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#else
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    /* In case of ESS, use start and length from the configuration of the first configured segment */
    if(0U == m_stCurrentSegment.ubLogicalBlockId)
    {
      Prog_GetEssStartAddr(&m_ulBlockAddr);
      Prog_GetEssLength(&m_ulBlockLength);
    }
    else
    {
      /* get start address and length from ESS, subtract 1 because the ESS starts from zero and 1 was added to handle the ESS itself */
      (void)Prog_GetEssLogicalBlockStartAddr(m_stCurrentSegment.ubLogicalBlockId - 1U, &m_ulBlockAddr);
      (void)Prog_GetEssLogicalBlockLength(m_stCurrentSegment.ubLogicalBlockId - 1U, &m_ulBlockLength);
    }

    /* ECC is disabled here because VCC requires the verification of the erased area as well  */
    PROG_DisableECCCheck();
    /* Deviation MISRAC2012-1 */
#if (PROG_HSM_MAC_USED == STD_ON)
    PROG_HsmMacGenerateStart();
#else
    /* Deviation CERTC-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
        (u8*)m_ulBlockAddr,
        m_ulBlockLength,
        &m_aubChecksum[0U]);
#endif /* PROG_HSM_MAC_USED */
#else
#if (PROG_CSM_MAC_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
#if (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
    /* Deviation CERTC-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#else
    /* Deviation CERTC-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#endif /*(PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)*/
#endif /*(PROG_CSM_MAC_USED == STD_ON)*/
#if (PROG_HSM_MAC_USED == STD_ON)
    PROG_HsmMacGenerateStart();
#endif /* PROG_HSM_MAC_USED */
#endif
#endif

    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_EXIT();
#else
#if ((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
    /*Secure Application Checksum Computation feat. is disabled or not supported*/
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
#endif /*(PROG_IMPL_VARIANT != PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5)*/
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#endif /*(PROG_IMPL_VARIANT != PROG_IMPL_90)|| (PROG_IMPL_VARIANT == PROG_IMPL_91)*/
#endif /*(PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)*/
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))
    }
    else
    {
       PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    } /*if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType != PROG_HSM_PARTITION)*/
#endif
}
/*--------------------{end PROG_SecurityComputeAppChecksum}-----------------------*/


#if (PROG_HSM_MAC_USED == STD_ON)
void PROG_HsmMacGenerateStart(void)
{
    /* try to start HSM actions */
    m_ubHsmCurrentStep = PROG_HSM_UPDATEINIT_BLOCK;
#if ( (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5) )
        if((stConfigSegment[m_stCurrentSegment.ubSegmentId].eVerifySignature) != PROG_TRUE)
        {
            m_ubUnsignedLB_SecBoot = PROG_E_BUSY;
        }
#endif
}
#endif /* PROG_HSM_MAC_USED */

void PROG_HsmManage(void)
{
#if ((PROG_HSM_MAC_USED == STD_ON) && (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
    tProgStatus ubLocJobResult;
    u8         *pubLocMemoryAddress;
    u32         ulLocMemorySize;
    u16         ulLocSignLength;
    u8 *pubLocSignForMacCal;
    u32         ulbankOffset;
#if (((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5)) && (PROG_CHECKMEMORY_TYPE != PROG_CHECKMEMORY_BY_BLOCK))
    u8 ubSignBlkId;
    u32         ulVdsLength;
#endif
    ulbankOffset = PROG_HSM_OFFSET_FOR_MAC;
    ubLocJobResult = PROG_E_BUSY;
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
    pubLocSignForMacCal = &m_aubExpectedSignature[0];
    ulLocSignLength = PROG_SIGNATURE_LENGTH;
#else
    ulLocSignLength = 0u;
    pubLocSignForMacCal = NULL_PTR;
#endif

    switch (m_ubHsmCurrentStep)
    {
        case PROG_HSM_UPDATEINIT_BLOCK:
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)m_ulBlockAddr;
            ulLocMemorySize = m_ulBlockLength;
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#elif (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot;
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            ulbankOffset = PROG_CustomCalcInactiveBankReadAddr(PROG_HSM_OFFSET_FOR_MAC);
            pubLocMemoryAddress =(u8 *)( pubLocMemoryAddress + ulbankOffset);
#endif
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#else
#if ( (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5) )
            pubLocMemoryAddress = (u8 *)&m_astVDSlayout;
            ulLocMemorySize = PROG_VDS_SIZE;
#else
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot;
#endif
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            ulbankOffset = PROG_CustomCalcInactiveBankReadAddr(PROG_HSM_OFFSET_FOR_MAC);
            pubLocMemoryAddress =(u8 *)( pubLocMemoryAddress + ulbankOffset);
#endif
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubSegmentId,
                                                           pubLocMemoryAddress,
                                                           ulLocMemorySize);
#endif
            break;

        case PROG_HSM_UPDATE_BLOCK:
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)m_ulBlockAddr;
            ulLocMemorySize = m_ulBlockLength;
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocSignForMacCal,
                                                       ulLocSignLength,
                                                       ulbankOffset,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#elif (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot;
#if (PROG_OTA_DUALBANK_USED == STD_ON)
            ulbankOffset = PROG_CustomCalcInactiveBankReadAddr(PROG_HSM_OFFSET_FOR_MAC);
            pubLocMemoryAddress =(u8 *)( pubLocMemoryAddress + ulbankOffset);
#endif
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocSignForMacCal,
                                                       ulLocSignLength,
                                                       ulbankOffset,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#else
#if ( (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5) )
            pubLocMemoryAddress = (u8 *)&m_astVDSlayout;
            ubSignBlkId = stConfigSegment[m_stCurrentSegment.ubSegmentId].ubBlockIndentifier;
            /* Read Start address and Length to perform Signature verification on the VDS table*/
            /* Deviation MISRAC2012-1 */
            PROG_ReadLengthOfVDS(ubSignBlkId, &ulVdsLength);
            ulLocMemorySize = ulVdsLength;
#else
            /* Deviation MISRAC2012-1 */
           /* Deviation CERTC-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot;
#endif
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubSegmentId,
                                                       pubLocSignForMacCal,
                                                       ulLocSignLength,
                                                       ulbankOffset,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#endif
            break;

        case PROG_HSM_UPDATE_FINISH:
            /* update is OK */
#if ( (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5) )
        if((stConfigSegment[m_stCurrentSegment.ubSegmentId].eVerifySignature) != PROG_TRUE)
        {
            m_ubUnsignedLB_SecBoot = PROG_E_OK;
        }
#endif
            PROG_CustomHsmUpdateFinish(PROG_E_OK);
            PROG_SecurityChecksumNotification();
            m_ubHsmCurrentStep = PROG_HSM_IDLE;
            break;

        case PROG_HSM_IDLE:
        default:
            /* do nothing */
            break;
    }

    if (ubLocJobResult == PROG_E_OK)
    {
        /* go to the next step */
        m_ubHsmCurrentStep++;
    }
    else if (ubLocJobResult == PROG_E_NOT_OK)
    {
        m_ubHsmCurrentStep = PROG_HSM_IDLE;
        /* report failure */
        PROG_CustomHsmUpdateFinish(PROG_E_NOT_OK);
#if ( (PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5) )
        if((stConfigSegment[m_stCurrentSegment.ubSegmentId].eVerifySignature) == PROG_TRUE)
        {
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
        else
        {
            m_ubUnsignedLB_SecBoot = PROG_E_NOT_OK;
        }
#else
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }
    else
    {
        /* do nothing */
    }
#endif /* ((PROG_HSM_MAC_USED == STD_ON) && (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)) */
}

void PROG_HsmFwUpdate(void)
{
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))
    tProgStatus ubLocJobResult;
    u8         *pubLocMemoryAddress;
    u32         ulLocMemorySize;

    ubLocJobResult = PROG_E_BUSY;
    DBG_PROG_HSMFWUPDATE_ENTRY();

    switch (m_ubHsmFuUpdateCurrentStep)
    {
        case PROG_HSM_UPDATEINIT_BLOCK:
            /* Reading HSM data address from RAM to update HSM */
            pubLocMemoryAddress = (u8 *)stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress;
            ulLocMemorySize = (stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEndAddress - stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress + 1U);
            /* A callback to add the HSM Firmware Init related codes */
            ubLocJobResult = PROG_CustomHsmFwUpdateInitBlock(m_stCurrentSegment.ubSegmentId,
                                                           pubLocMemoryAddress,
                                                           ulLocMemorySize);
            break;

        case PROG_HSM_UPDATE_BLOCK:
            /* Reading HSM data address from RAM to update HSM */
            pubLocMemoryAddress = (u8 *)stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress;
            ulLocMemorySize = (stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEndAddress - stConfigSegment[m_stCurrentSegment.ubSegmentId].ulStartAddress + 1U);

            /* A callback to add the HSM Firmware Update Block related codes */
            ubLocJobResult = PROG_CustomHsmFwUpdateBlock(m_stCurrentSegment.ubSegmentId,
                                                   pubLocMemoryAddress,
                                                   ulLocMemorySize);
            break;

        case PROG_HSM_UPDATE_FINISH:
            /* A callback to check the HSM Firmware Update status*/
            ubLocJobResult = PROG_CustomHsmFwUpdateFinish();
            if(ubLocJobResult == PROG_E_OK)
            {
                /* Triggers an event to indicate that the Fw update is successful*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
            }
            m_ubHsmFuUpdateCurrentStep = PROG_HSM_IDLE;
            break;

        case PROG_HSM_IDLE:
        default:
            /* do nothing */
            break;
    }

    if (ubLocJobResult == PROG_E_OK)
    {
        /* go to the next step */
        m_ubHsmFuUpdateCurrentStep++;
    }
    else if (ubLocJobResult == PROG_E_NOT_OK)
    {
        /* Trigger the failed event and returns the state to IDLE */
        m_ubHsmFuUpdateCurrentStep = PROG_HSM_IDLE;
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    else
    {
        /* do nothing */
    }
    DBG_PROG_HSMFWUPDATE_EXIT();
#endif /* #if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))*/
}

void PROG_SecurityCheckHsmFwUpdate(void)
{
    DBG_PROG_SECURITYCHECKHSMFWUPDATE_ENTRY();
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))
    /* Validate if the Block Partition Type is HSM to trigger the Firmware Update */
    if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_HSM_PARTITION)
    {
        /* Trigger PROG_HsmFwUpdate */
        m_ubHsmFuUpdateCurrentStep = PROG_HSM_UPDATEINIT_BLOCK;
    }
    else
    {
        /* Triggers the pass through Event if the ePartitionType is not HSM FW */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
#else/* #if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_91))*/
    {
        /* A pass through, that skips the HSM Firmware update process */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
#endif
    DBG_PROG_SECURITYCHECKHSMFWUPDATE_EXIT();
}
/*-------------------------------------------------------------------------------*/
