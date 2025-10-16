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
/*%%   _____________________________   %%  \file PROG_Impl_20.c                  */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
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
 */
/* NOCOV List
 *
 *
 */
/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: INT.36
 * Converting a pointer to integer or integer to pointer
 *
 * Reason:
 * this variable contains a flash memory address that will not be subject to pointer arithmetics no risk of alignment issues.
 *
 *
 * CERTC-2) Deviated Rule: DCL.40
 * Do not create incompatible declarations of the same function or object
 *
 * Reason:
 * Two functions are declared to  provide two different functionalities though.
 * they are almost similar in declarations they wont be functional impact.
 */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */
#if (PROG_COMPRESSION_ENABLE == STD_ON)
#include "PROG_Decomp.h"
#endif
#include "board.h"
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

u8 m_ubNormComEnabled; /* Information if normal Communication is enabled
                        (no reception of CommunicationControl request) */
u8 m_ubIsLocked; /* Information if ECU is locked
                        (no reception of SecurityAccess request) */

/* Buffer use to copy the manage the SBA ticket and AppSwInfo from RAM */
u8 m_aubSwInfo[1024];

tBootStatus m_stBootStatus;
u16 m_uwKeyNBID;

#if (PROG_HSM_UPDATE_ENABLE == STD_ON)
u8 m_aubHsmbuffer[PROG_HSM_BUFFER_LENGTH];
PduLengthType m_ulHsmbufferlength;
u16 m_uwHSMTimeoutCnt;
#endif
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
#define PROG_TOLERANT_FLAG_POS       1
#define PROG_ECU_INERNAL_FLAG_POS    2
#define PROG_HSM_MAX_TIMEOUT         0xFFFFU
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

NCS_PRI_VAR u8* m_pubHeaderAddress;
NCS_PRI_VAR u8 m_aubMessageDigest[PROG_DIGEST_LENGTH];
NCS_PRI_VAR Csm_AsymPublicKeyType m_stProgAsymPublicKey_cbk;

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */



/** \brief general signed header check API
 **
 ** \param[in] pubHeaderAddr data of the Header
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK signed header check pass
 ** \retval PROG_E_NOT_OK Error during signed header check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckSignedHeader(u8 * pubHeaderAddr);
/** \brief Application signed header check API
 **
 ** \param[in] uwXCID XCID valuer
 ** \param[in] uwRegionNbr number of calibration region to check
 ** \param[in] pubHeaderAddr data of the Header
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK application signed header check pass
 ** \retval PROG_E_NOT_OK Error during application signed header check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckApplSignedHeader(u16 uwXCID, u16 uwRegionNbr, const u8 * pubHeaderAddr);
/** \brief Calibration signed header check API
 **
 ** \param[in] uwModuleId module ID to check
 ** \param[in] uwXCID XCID value
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK calibration signed header check pass
 ** \retval PROG_E_NOT_OK Error during calibration signed header check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckCalSignedHeader(u16 uwModuleId, u16 uwXCID);
/** \brief Check ECU ID compare to store one
 **
 ** \param[in] pubEcuId ECU ID to check
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK ECU ID check pass
 ** \retval PROG_E_NOT_OK Error during ECU ID check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckEcuId(const u8* pubEcuId);
/** \brief Check ECU name compare to store one
 **
 ** \param[in] pubEcuName ECU name to check
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK ECU name check pass
 ** \retval PROG_E_NOT_OK Error during ECU name check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckEcuName(const u8* pubEcuName);

/** \brief Check subject name compare to the stored one
 **
 ** \param[in] pubSubjectName subject name to check
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK subject name check pass
 ** \retval PROG_E_NOT_OK Error during subject name check
 **/
NCS_PRI_FCT tProgStatus PROG_CheckSubjectName(const u8* pubSubjectName);


/** \brief Finalize the signed header check
 **
 ** \param[in] Pointer on Signed header address
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK signed header is correct
 ** \retval PROG_E_NOT_OK Error with NBID check
 **/
NCS_PRI_FCT tProgStatus PROG_FinalizeCheckSignedHeader(const u8 * pubHeaderAddr);

/** \brief Verify if header is complete
 **
 ** \param[in] pubHeaderAddr pointer to the header start address
 ** \param[in] ulLength length of the received data
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK header is complete
 ** \retval PROG_E_NOT_OK header is not complete
 **/
NCS_PRI_FCT tProgStatus PROG_CheckCompleteHeader(u8 * pubHeaderAddr,PduLengthType ulLength);

NCS_PRI_FCT u32 PROG_GetAppSwSize(u8 * pubHeaderAddr, u16 uwRegionNbr);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*----------------------------{PROG_Init_Impl20}--------------------------------*/
void PROG_Init_Impl20(void)
{
    PROG_GetPublicKey(&m_stProgAsymPublicKey_cbk);
}
/*----------------------------{end PROG_Init_Impl20}--------------------------------*/

/*----------------------------{PROG_CheckPSIValue}--------------------------------*/
tProgStatus PROG_CheckPSIValue(u8 ubPartitionId, tProgPsiValue ePsiValue)
{
    tProgStatus eProgStatus;
    u8 ubLoopIndex;
    u32 ulPSIAddress;
    u8 aubPSIAddress[PROG_PSI_SIZE] = {0};
    u32 ulMinValueToWrite = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].ulMinValueToWrite;
    const u8* pubValToCheck;

    DBG_PROG_CHECKPSIVALUE_ENTRY(ubPartitionId, ePsiValue);

    /* Get PSI Address */
    eProgStatus = PROG_GetPSIAddress( ubPartitionId, &ulPSIAddress);

    if(eProgStatus == PROG_E_OK)
    {
        /* First check if the PSI is revoked */
        /* Shift the address to get the revoked part */
        ulPSIAddress += ulMinValueToWrite;

        /* set the comparison to revoked configured value */
        pubValToCheck = m_aCfgPSIRevokedValue;

        /* Get revoked PSI value */
        (void)PROG_MemDataAccess(
                m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                PROG_MEM_OPERATION_TYPE_READ,
                ulPSIAddress ,
                PROG_PSI_VAL_SIZE,
                &aubPSIAddress[0]);

        (void)PROG_Custom_MemStatuscheck(); /* poll the busy status to ensure read finish*/

        for(ubLoopIndex = 0U; ubLoopIndex < PROG_PSI_VAL_SIZE; ubLoopIndex++)
        {
            if(aubPSIAddress[ubLoopIndex] != pubValToCheck[ubLoopIndex])
            {
                eProgStatus = PROG_E_CHECK_FAILED;
            }
        }

        if(eProgStatus == PROG_E_CHECK_FAILED)
        {
            /* PSI is not revoked so check if it is programmed */
            if(ePsiValue == PROG_PSI_PROGRAMMED)
            {
                /*called to check if the page is erased or not */
                eProgStatus = PROG_MemCheckPageErasing(
                                    m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                                    ulPSIAddress);
                if(eProgStatus == PROG_E_OK)
                {
                    /* Shift back the address to get the programmed part */
                    ulPSIAddress -= ulMinValueToWrite;
                    /* set the comparison to programmed configured value */
                    pubValToCheck = m_aCfgPSIProgrammedValue;

                    /* Get programmed PSI value */
                    (void)PROG_MemDataAccess(
                            m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                            PROG_MEM_OPERATION_TYPE_READ, ulPSIAddress , PROG_PSI_VAL_SIZE, &aubPSIAddress[0]);

                    (void)PROG_Custom_MemStatuscheck(); /* poll the busy status to ensure read finish*/

                    for(ubLoopIndex = 0U; ubLoopIndex < PROG_PSI_VAL_SIZE; ubLoopIndex++)
                    {
                        if(aubPSIAddress[ubLoopIndex] != pubValToCheck[ubLoopIndex])
                        {
                            eProgStatus = PROG_E_CHECK_FAILED;
                        }
                    }
                }
                /* else : eProgStatus = PROG_E_NOT_OK */
                else
                {
                    eProgStatus = PROG_E_CHECK_FAILED;
                }
            }
        }
        else
        {
            if(ePsiValue == PROG_PSI_PROGRAMMED)
            {
                eProgStatus = PROG_E_CHECK_FAILED;
            }
        }
    }
    DBG_PROG_CHECKPSIVALUE_EXIT(eProgStatus);
    return eProgStatus;
}
/*----------------------------{end PROG_CheckPSIValue}----------------------------*/

/*----------------------------{PROG_Entry_DecompHeader}--------------------*/
void PROG_Entry_DecompHeader(void)
{
#if PROG_COMPRESSION_ENABLE == STD_ON
    tProgStatus eProgStatus;
    DBG_PROG_ENTRY_DECOMPHEADER_ENTRY();

    eProgStatus = PROG_DecompressInit(m_stReprogInfo.ulMemorySizeExpected);

    if(eProgStatus == PROG_E_OK)
    {
        eProgStatus = PROG_DecompressData (&m_stDiagMessageInfo.pubData[10], (m_stDiagMessageInfo.ulLength - 10U));

        if(eProgStatus == PROG_E_OK)
        {
            /* Increment the number of data ask for decompression */
            m_stWriteInfo.ulInDecompDataLength = (u32)((u32)m_stDiagMessageInfo.ulLength - 2U);

        }
        else
        {
            /* Send negative response NRC31 */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;

            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
    {
        /* Send negative response NRC31 */
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;

        /* Emit event PROG_EVENT_FAILED*/
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
#else
    DBG_PROG_ENTRY_DECOMPHEADER_ENTRY();
#endif
    DBG_PROG_ENTRY_DECOMPHEADER_EXIT();
}
/*----------------------------{end PROG_Entry_DecompHeader}----------------*/


/*------------------------{PROG_Entry_ValidateSBASignature}--------------------------*/
void PROG_Entry_ValidateSBASignature(void)
{
    tProgStatus eProgStatus;
    u32 ulDataSize;
    u8 ubIdx;
    u8 * paubSwInfoPublicModulus;

    DBG_PROG_ENTRY_VALIDATESBASIGNATURE_ENTRY( );

    /* Size of the SBA ticket used for signature */
    ulDataSize = 564U;

    /* Call crypto library to verify the root signature */

    /* Get public key */
    paubSwInfoPublicModulus = &m_aubSwInfo[4U + PROG_ECU_NAME_SIZE + PROG_ECU_ID_SIZE + 26U];

    m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */
    for(ubIdx = 0U; /* Modulus */
        ubIdx < m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U];
        ubIdx++)
    {
        u8 ubLocIdx = ubIdx + ((u8)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
        m_stProgAsymPublicKey.data[ubLocIdx] = (u32) paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
        m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
        m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }

    eProgStatus = PROG_VerifySignature
                    (
                            &m_stProgAsymPublicKey,
                            &m_aubSwInfo[2],
                            ulDataSize,
                            &m_aubSwInfo[566]
                    );

    if(eProgStatus == PROG_E_NOT_OK)
    {
        m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_SIGNATURE;
        /* Emit event PROG_EVENT_INIT*/
        PROG_HsmEmit(&PROG_HsmScPROG,
            PROG_HSM_PROG_EV_PROG_EVENT_INIT);
    }
    DBG_PROG_ENTRY_VALIDATESBASIGNATURE_EXIT( );
}
/*----------------------{end PROG_Entry_ValidateSBASignature}------------------------*/


/*------------------------{PROG_SBASignerInfoCheck}--------------------------*/
void PROG_SBASignerInfoCheck(void)
{
    tProgStatus eOperationStatus;
    DBG_PROG_SBASIGNERINFOCHECK_ENTRY();

    /* Check if crypto calculation is finish */
    eOperationStatus = PROG_GetCryptoStatus();

    switch(eOperationStatus)
    {
        case PROG_E_OK:
            /* Emit event PROG_EVENT_VALIDATE_SIGNATURE*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_VALIDATE_SIGNATURE);
            break;
        case PROG_E_BUSY:
            /* Nothing to do */
            break;
        default:
            m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_CERT;
            /* Emit event PROG_EVENT_INIT*/
            PROG_HsmEmit(&PROG_HsmScPROG,
                PROG_HSM_PROG_EV_PROG_EVENT_INIT);
            break;

    }
    DBG_PROG_SBASIGNERINFOCHECK_EXIT();
}
/*----------------------{end PROG_SBASignerInfoCheck}------------------------*/

/*----------------------------{PROG_GetPSIAddress}--------------------------------*/

tProgStatus PROG_GetPSIAddress(u8 ubPartitionId, u32* pulPSIAddress)
{
    tProgStatus eProgStatus;
    u16 uwCalPartitionNbr;

    eProgStatus = PROG_E_OK;

    /* Check if it is the application partition */
    if(ubPartitionId == PROG_SW_APP_ID)
    {
        /* Application Module, get value from static configuration */
        *pulPSIAddress = (u32)PROG_APP_PSI_ADDR;
    }
    else
    {
        /* Get address where is set the number of calibration partitions */
        uwCalPartitionNbr = PROG_GET_CALIB_PARTITION_NB;
        if(ubPartitionId <= (uwCalPartitionNbr + 1U))
        {
            /* Get the PSI address of the requested partition: End address of the last region - PSI size */
            *pulPSIAddress = (u32)((PROG_GET_CALIB_SW_LAST_REGION_ADDR_START(ubPartitionId)
                    + PROG_GET_CALIB_SW_LAST_REGION_SIZE(ubPartitionId)) - PROG_PSI_SIZE);

        }
        else
        {
            eProgStatus = PROG_E_NOT_OK;
        }

    }

    /*return networkstatus stored through reception of Master frame*/
    return eProgStatus;
}
/*----------------------------{end PROG_GetPSIAddress}----------------------------*/


#if (PROG_CHECK_PROGRAMMING_DEPENDENCIES_REQUEST_ENABLE == STD_ON)
/*-----------------{PROG_CheckProgrammingDependencies_Impl20}--------------------*/
    /* Deviation CERTC-2 */
tUdsStatus PROG_CheckProgrammingDependencies_Impl20(PduLengthType *pulLen, u8 *aubUdsData)
{
    tProgStatus eProgStatus = PROG_E_OK;
    u8 ubPartitionId;
    tUdsStatus eUdsStatus = UDS_ACK;
    u32 ulAddress;
    u32 ulSize;
    u16 uwCalPartitionNbr;
    u8 ubECUInternalProgrammingFlag;
    u8 ubProgrammingTolerantConditionsFlag;
    u8 ubProgrammingConditionsFlag;

    if ((NULL_PTR != pulLen) && (NULL_PTR != aubUdsData))
    {
        /* Set response length */
        *pulLen = 9U;
        /* Set Byte 0: ECU Current Programmed State */
        aubUdsData[4U] = 0U;
        /* Set Byte 4: Additional Programming Conditional Flags Status */
        Prog_CustomGetAdditionalProgrammingConditionalFlags(&aubUdsData[8]);

        /* Check if all partition are programmed (PSI == Programmed) */
        ubPartitionId = 1U;

        /* Check if Application is valid, set segment to Application segment */
        m_stCurrentSegment.ubSegmentId = PROG_APP_SEGMENT_ID;

        eProgStatus = PROG_CheckPSIValue(ubPartitionId, PROG_PSI_PROGRAMMED);

        if (PROG_E_OK == eProgStatus)
        {
            ubPartitionId++;
            /* Get address where is set the number of calibration partitions */
            uwCalPartitionNbr = PROG_GET_CALIB_PARTITION_NB;
            while(eProgStatus == PROG_E_OK)
            {
                if(ubPartitionId <= (uwCalPartitionNbr + 1U))
                {

                    /* Get Expected start address for the first region of any partition */
                    ulAddress = PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START(ubPartitionId);

                    /* A region is defined in a partition which is defined segment. The smallest part is chosen to set the calibration partition */
                    ulSize = 0U;

                    /* Call GetSegmentByAddress API to get the current the SegmentId */
                    (void) PROG_GetSegmentByAddress(ulAddress, ulSize, PROG_MEM_OPERATION_TYPE_READ, &m_stCurrentSegment.ubSegmentId);

                    eProgStatus = PROG_CheckPSIValue(ubPartitionId,PROG_PSI_PROGRAMMED);

                    /* When application is valid, check the next calibration partition*/
                    ubPartitionId++;
                }
                else
                {
                    eProgStatus = PROG_E_NOT_OK;
                }

            }

            if (PROG_E_CHECK_FAILED == eProgStatus)
            {
                /* Set Byte 0: calibration software missing*/
                aubUdsData[4] = 0x02;
            }
            else
            {
                /*Nothing to do, byte already set to 0x00 */
            }
        }
        else
        {
            /* Set Byte 0: application software missing*/
            aubUdsData[4] = 0x01;
        }

        /* Set Byte 1: Programming Conditional Flags Supported */
        aubUdsData[5] = 0x06; /* Normal Communications Check Supported/Security Access Check Supported*/

        /* Set Byte 2: Programming Conditional Flags Status */
        aubUdsData[6] = 0x00U | ( (0x04U & (u8)(m_ubNormComEnabled<<2U)) | (0x02U & (u8)(m_ubIsLocked<<1U)) );

        /* Set Byte 3: Current Programming Capability */
        Prog_CustomGetECUInternalProgrammingFlag(&ubECUInternalProgrammingFlag);
        Prog_CustomGetProgrammingTolerantConditionsFlag(&ubProgrammingTolerantConditionsFlag);
        Prog_CustomGetProgrammingConditionsFlag(&ubProgrammingConditionsFlag);

        /* set byte in response array */
        aubUdsData[7] =  0x0U | ubProgrammingConditionsFlag;
        aubUdsData[7] |= (u8)(ubProgrammingTolerantConditionsFlag << PROG_TOLERANT_FLAG_POS);
        aubUdsData[7] |= (u8)(ubECUInternalProgrammingFlag<< PROG_ECU_INERNAL_FLAG_POS);

    }
    else
    {
        eUdsStatus = UDS_ERR_COHE;
    }

    /* Return status to lower layer */
    return (eUdsStatus);

}
/*--------------{end PROG_CheckProgrammingDependencies_Impl20}-------------------*/
#endif  /* (PROG_CHECK_PROGRAMMING_DEPENDENCIES_REQUEST_ENABLE == STD_ON) */

/*----------------------------{PROG_IsValidApplication}-------------------------*/
#if (PROG_APPLI_CHECK_ENABLE == STD_ON)
tProgBoolean PROG_IsValidApplication(void)
{
    tProgBoolean eProgBoolean;
    tProgStatus eProgStatus = PROG_E_OK;
    u8 ubPartitionId;
    u32 ulAddress;
    u32 ulSize;
    u16 uwCalPartitionNbr;
    DBG_PROG_ISVALIDAPPLICATION_ENTRY();

    eProgBoolean = PROG_TRUE;

    /* Check if all partition are programmed (PSI == Programmed) */
    ubPartitionId = 1U;

    /* Check if Application is valid, set segment to Application segment */
    m_stCurrentSegment.ubSegmentId = PROG_APP_SEGMENT_ID;

    eProgStatus = PROG_CheckPSIValue(ubPartitionId,PROG_PSI_PROGRAMMED);

    if (PROG_E_OK == eProgStatus)
    {
        /* When application is valid, check the next partition which are calibration */
        ubPartitionId++;
        /* Get address where is set the number of calibration partitions */
        uwCalPartitionNbr = PROG_GET_CALIB_PARTITION_NB;

        while(eProgStatus == PROG_E_OK)
        {
            if(ubPartitionId <= (uwCalPartitionNbr + 1U))
            {
                /* When application is valid, check the next partition which are calibration */

                /* Get Expected start address for the first region of any partition */
                ulAddress = PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START(ubPartitionId);

                /* A region is defined in a partition which is defined segment. The smallest part is chosen to set the calibration partition */
                ulSize = 0U;

                /* Call GetSegmentByAddress API to get the current the SegmentId */
                (void) PROG_GetSegmentByAddress(ulAddress, ulSize, PROG_MEM_OPERATION_TYPE_READ, &m_stCurrentSegment.ubSegmentId);

                eProgStatus = PROG_CheckPSIValue(ubPartitionId,PROG_PSI_PROGRAMMED);

                /* Check next partition */
                ubPartitionId++;
            }
            else
            {
                eProgStatus = PROG_E_NOT_OK;
            }
        }
    }

    if (PROG_E_CHECK_FAILED == eProgStatus)
    {
        eProgBoolean = PROG_FALSE;
    }
    DBG_PROG_ISVALIDAPPLICATION_EXIT(eProgBoolean);
    return eProgBoolean;
}
#endif /* (PROG_APPLI_CHECK_ENABLE == STD_ON) */
/*----------------------------{end PROG_IsValidApplication}---------------------*/



/*----------------------------{PROG_GetModulePartition}---------------------------*/

tProgStatus PROG_GetModulePartition(u16 uwModuleId, u8 * pubPartitionId, u8 * pubModuleIndex)
{
    tProgStatus eProgStatus;
    u8 ubPartitionId;
    u8 ubModuleIndex;

    eProgStatus = PROG_E_NOT_OK;

    for(ubPartitionId = 2U; (ubPartitionId < (PROG_GET_CALIB_PARTITION_NB + 2U))
                && (eProgStatus != PROG_E_OK); ubPartitionId++)
    {
        for(ubModuleIndex = 0U; ((ubModuleIndex < (PROG_GET_CALIB_SW_MODULE_NBR(ubPartitionId)))
                && (eProgStatus != PROG_E_OK)); ubModuleIndex++)
        {
            if(uwModuleId == PROG_GET_CALIB_SW_MODULE_ID(ubPartitionId,ubModuleIndex))
            {
                /* Module found */
                eProgStatus = PROG_E_OK;
                *pubPartitionId = ubPartitionId;
                *pubModuleIndex = ubModuleIndex;
            }
        }
    }

    return eProgStatus;
}
/*----------------------------{end PROG_GetModulePartition}-----------------------*/

/*------------------------{PROG_SBASignatureCheck}--------------------------*/
void PROG_SBASignatureCheck(void)
{
    tProgStatus eOperationStatus;
    u8 ubSBIFlagToStore;
    DBG_PROG_SBASIGNATURECHECK_ENTRY();

    /* Check if crypto calculation is finish */
    eOperationStatus = PROG_GetCryptoStatus();
    ubSBIFlagToStore = TRUE;

    switch(eOperationStatus)
    {
        case PROG_E_OK:
            /* SBA ticket is valid, enable bypass */
            PROG_SetSBIFlagValue(ubSBIFlagToStore);
            m_stBootStatus.ubSignatureBypass = PROG_SBA_OK;
            /* Emit event PROG_EVENT_INIT*/
            PROG_HsmEmit(&PROG_HsmScPROG,
                PROG_HSM_PROG_EV_PROG_EVENT_INIT);
            break;
        case PROG_E_BUSY:
            /* Nothing to do */
            break;
        default:
            m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_SIGNATURE;
            /* Emit event PROG_EVENT_INIT*/
            PROG_HsmEmit(&PROG_HsmScPROG,
                PROG_HSM_PROG_EV_PROG_EVENT_INIT);
            break;

    }
    DBG_PROG_SBASIGNATURECHECK_EXIT();
}
/*----------------------{end PROG_SBASignatureCheck}------------------------*/

/*------------------------{PROG_ValidateSBATicket}--------------------------*/
u8 PROG_ValidateSBATicket(void)
{
    tProgStatus eProgStatus;
    PROG_HsmEventType eventToPost;
    u16 uwModuleId;
    u8 ubSBIFlagToStore;
    DBG_PROG_VALIDATESBATICKET_ENTRY();

    ubSBIFlagToStore = FALSE;
    PROG_SetSBIFlagValue(ubSBIFlagToStore);

    /* copy the SBA ticket in the RAM buffer m_aubSwInfo*/
    eProgStatus = PROG_CopySBATicket(m_aubSwInfo);

    /* Check ModuleId */
    uwModuleId = (u16)((u16)((u16)m_aubSwInfo[2] << 8U) & 0xFF00U) | (u16)((u16)m_aubSwInfo[3] & 0x00FFU);

    if ((uwModuleId == PROG_SBA_MODULE_ID) && (PROG_E_OK == eProgStatus))
    {
        /* Check ECU Name */
        eProgStatus = PROG_CheckEcuName(&m_aubSwInfo[4]);

        if (eProgStatus == PROG_E_OK)
        {
            /* Check ECU Id */
            eProgStatus = PROG_CheckEcuId(&m_aubSwInfo[4U + PROG_ECU_NAME_SIZE]);

            if (eProgStatus == PROG_E_OK)
            {
                if (m_ubSimulateProgSessionWithResponse == FALSE)
                {
                    /* Emit event PROG_EVENT_VALIDATE_SIGNER_INFO */
                    eventToPost = PROG_HSM_PROG_EV_PROG_EVENT_VALIDATE_SIGNER_INFO;
                }
                else
                {
                    /* Emit event PROG_HSM_PROG_EV_PROG_EVENT_SBA_NRC78 */
                    eventToPost = PROG_HSM_PROG_EV_PROG_EVENT_SBA_NRC78;
                }
            }
            else
            {
                m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_ECU_ID;
                /* Emit event PROG_EVENT_INIT*/
                eventToPost = PROG_HSM_PROG_EV_PROG_EVENT_INIT;
            }
        }
        else
        {
            m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_ECU_NAME;
            /* Emit event PROG_EVENT_INIT*/
            eventToPost = PROG_HSM_PROG_EV_PROG_EVENT_INIT;
        }
    }
    else
    {
        /* Emit event PROG_EVENT_INIT */
        eventToPost = PROG_HSM_PROG_EV_PROG_EVENT_INIT;
    }

    DBG_PROG_VALIDATESBATICKET_EXIT();
    return (u8)eventToPost;
}
/*----------------------{end PROG_ValidateSBATicket}------------------------*/

/*------------------------{PROG_Entry_ValidateSBASignerInfo}--------------------------*/
void PROG_Entry_ValidateSBASignerInfo(void)
{
    tProgStatus eProgStatus;
    u16 uwNBID;
    u16 uwStoredNBID;

    DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_ENTRY();

    uwNBID = (u16)((u16)((u16)m_aubSwInfo[28U + 24U] << 8U) & 0xFF00U) | (u16)((u16)m_aubSwInfo[28U + 24U + 1U] & 0x00FFU);

    eProgStatus = PROG_CheckSubjectName(&m_aubSwInfo[28]);

    if(PROG_E_OK == eProgStatus)
    {
        uwStoredNBID = PROG_GetKeyNBIDValue();

        if(uwNBID >= uwStoredNBID)
        {
            /* Call crypto library to verify the root signature */

            eProgStatus = PROG_VerifySignature
                (
                    &m_stProgAsymPublicKey_cbk,
                    &m_aubSwInfo[4U + PROG_ECU_NAME_SIZE + PROG_ECU_ID_SIZE],
                    282U,
                    &m_aubSwInfo[4U + PROG_ECU_NAME_SIZE + PROG_ECU_ID_SIZE + 282U]
                );

            if(eProgStatus == PROG_E_NOT_OK)
            {
                /* Set boot status info */
                m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_CERT;
                /* Emit event PROG_EVENT_INIT*/
                PROG_HsmEmit(&PROG_HsmScPROG,
                    PROG_HSM_PROG_EV_PROG_EVENT_INIT);
            }
        }
        else
        {
            /* Set boot status info */
            m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_CERT;
            /* Emit event PROG_EVENT_INIT*/
            PROG_HsmEmit(&PROG_HsmScPROG,
                PROG_HSM_PROG_EV_PROG_EVENT_INIT);
        }
    }
    else
    {
        /* Set boot status info */
        m_stBootStatus.ubSignatureBypass |= PROG_ERR_SBA_CERT;
        /* Emit event PROG_EVENT_INIT*/
        PROG_HsmEmit(&PROG_HsmScPROG,
            PROG_HSM_PROG_EV_PROG_EVENT_INIT);
    }
    DBG_PROG_ENTRY_VALIDATESBASIGNERINFO_EXIT();
}
/*----------------------{end PROG_Entry_ValidateSBASignerInfo}------------------------*/

/*----------------------------{PROG_CheckDecompHeaderStatus}--------------------*/
void PROG_CheckDecompHeaderStatus(void)
{
#if PROG_COMPRESSION_ENABLE == STD_ON
    tProgStatus eProgStatus = PROG_E_BUSY;
    u16 uwDataType;
    PduLengthType ullength;
    u8* pubdata;
    tProgDecompressStateType eCompStatus;

    DBG_PROG_CHECKDECOMPHEADERSTATUS_ENTRY();

    ullength = 0U;

    eCompStatus = PROG_GetDecompressedData(&pubdata, &ullength);

    if(ullength > 4U)
    {
        /* Get Data Type */
        uwDataType =    (u16)((u16)((u16)((u16)(pubdata[0]) << 8U) & 0xFF00U) |
                        (u16)((u16)(pubdata[1]) & 0x00FFU));

       if(uwDataType == PROG_DATATYPE_SIGNED)
       {
#if (PROG_HSM_UPDATE_ENABLE == STD_ON)
        if(stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_HSM_PARTITION)
        {
          /* Remove decompression Header from request */
          /*Move SID*/
          m_stDiagMessageInfo.pubData[8U] = m_stDiagMessageInfo.pubData[0];
          /*Move BS*/
          m_stDiagMessageInfo.pubData[9U] = m_stDiagMessageInfo.pubData[1];

          m_stDiagMessageInfo.pubData = &m_stDiagMessageInfo.pubData[8];
          /* Emit event PROG_EVENT_REQ_TD*/
          PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD);
        }
        else
#endif
        {
            /* Check if header is complete, remove datatype from the passed header */
            eProgStatus=PROG_CheckCompleteHeader(&pubdata[2], (ullength-2U));

            if (PROG_E_OK == eProgStatus)
            {
                /* Header has been fully received and decompressed */

                eProgStatus = PROG_CheckSignedHeader(&pubdata[2]);
                if(eProgStatus == PROG_E_OK)
                {
                    m_pubHeaderAddress = &pubdata[2];

                    /* Emit event PROG_EVENT_VALIDATE_SIGNER_INFO */
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_VALIDATE_SIGNER_INFO);
                }
                else
                {
                    /* Send negative response NRC31 */
                    m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;

                    /* Emit event PROG_EVENT_FAILED*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);

                }

            }
            else
            {
                if (eCompStatus == PROG_DECOMP_IN_PROGRESS )
                {
                    /* Not enough data decompressed, wait next call */
                    eProgStatus = PROG_DecompressData (NULL_PTR,0U);
                    if(eProgStatus != PROG_E_OK)
                    {
                        /*Send NRC 72 and assign the Returned Error code to PEC*/
                        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
#if PROG_PEC_ENABLE == STD_ON
                        /*Update the Error code to PEC*/
                        m_uwPEC = PROG_ERR_COMPRESSION;
#endif
                        /*Emit event PROG_EVENT_FAILED*/
                        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                }
                else
                {
                    /* Header is not complete and cannot be processed */
#if PROG_PEC_ENABLE == STD_ON
                    /* Set error in PEC */
                    m_uwPEC = PROG_ERR_MORE_DATA_EXPECTED;
#endif
                    /* Send negative response NRC13 */
                    m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_13;

                    /* Emit event PROG_EVENT_FAILED*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
            }
          }
        }
        else
        {
#if PROG_PEC_ENABLE == STD_ON
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_DATA_TYPE;
#endif
            /* Send negative response NRC31 */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;

            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
#else
    DBG_PROG_CHECKDECOMPHEADERSTATUS_ENTRY();
#endif
    DBG_PROG_CHECKDECOMPHEADERSTATUS_EXIT();
}
/*----------------------------{end PROG_CheckDecompHeaderStatus}----------------*/

#if PROG_TRANSFER_DATA_ENABLE == STD_ON


/*----------------------------{PROG_GetPartitionAddrInAppSWInfo}-----------------*/
u8* PROG_GetPartitionAddrInAppSWInfo(u8* pubHeaderAddr, u8 ubPartitionId, u16 uwRamAccess)
{
    u8* puwPartitionInfoAddr;
    u16 uwPartitionRegionNbr;
    u16 uwPartitionModuleNbr;
    u8 ubLoopIndex;
    u16 uwAddrIndex;

    uwAddrIndex = 0U;
    DBG_PROG_GETPARTITIONADDRINAPPSWINFO_ENTRY(pubHeaderAddr, ubPartitionId,uwRamAccess );

    if ( 0U != uwRamAccess)
    {
        puwPartitionInfoAddr = PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR_FROM_REQ(pubHeaderAddr,uwRamAccess);
    }
    else
    {
        puwPartitionInfoAddr = PROG_GET_CALIB_SW_FIRST_PARTITION_ADDR;
    }

    for (ubLoopIndex = 2U; ubLoopIndex < ubPartitionId; ubLoopIndex++)
    {

        uwPartitionRegionNbr = PROG_GET_U16_VAL(&puwPartitionInfoAddr[uwAddrIndex]);
        uwAddrIndex += ((2U + (uwPartitionRegionNbr*8U)));
        uwPartitionModuleNbr = PROG_GET_U16_VAL(&puwPartitionInfoAddr[uwAddrIndex]);
        uwAddrIndex += ((2U + (uwPartitionModuleNbr*12U)));
    }
    DBG_PROG_GETPARTITIONADDRINAPPSWINFO_EXIT(puwPartitionInfoAddr );
    return &puwPartitionInfoAddr[uwAddrIndex];
}
/*--------------------------{end PROG_GetPartitionAddrInAppSWInfo}---------------*/




/*-----------------------------{PROG_Entry_TD_Header}----------------------------*/
void PROG_Entry_TD_Header(void)
{
    tProgStatus eProgStatus;
    u16 uwDataType;
    DBG_PROG_ENTRY_TD_HEADER_ENTRY();

    /* Get Data Type */
    uwDataType = (u16)((u16)((u16)((u16)m_stDiagMessageInfo.pubData[2] << 8U) & 0xFF00U) | (u16)((u16)m_stDiagMessageInfo.pubData[3U] & 0x00FFU));

    switch(uwDataType)
    {
        case PROG_DATATYPE_SIGNED:
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            /* Check if DFI = 0x00 */
            if(m_stReprogInfo.ubCompRequired == FALSE)
            {
#endif
#if(PROG_HSM_UPDATE_ENABLE == STD_ON)
            if(stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_HSM_PARTITION)
            {
                /* Emit event PROG_EVENT_REQ_TD*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD);
            }
            else
 #endif
            {
                /* Check if header is complete */
                eProgStatus=PROG_CheckCompleteHeader(&m_stDiagMessageInfo.pubData[4], (m_stDiagMessageInfo.ulLength-4U));

                if (PROG_E_OK == eProgStatus)
                {
                    /* Check Signed Header */
                    eProgStatus = PROG_CheckSignedHeader(&m_stDiagMessageInfo.pubData[4]);

                    if(eProgStatus == PROG_E_OK)
                    {
                        m_pubHeaderAddress = &m_stDiagMessageInfo.pubData[4];

                        /* Emit event PROG_EVENT_REQ_TD*/
                        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_VALIDATE_SIGNER_INFO);
                    }
                    else
                    {
                        /* Send negative response NRC31 */
                        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                        /* Emit event PROG_EVENT_FAILED*/
                        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                    }
                }
                else
                {
                    /* Header is not complete and cannot be processed */
#if PROG_PEC_ENABLE == STD_ON
                    /* Set error in PEC */
                    m_uwPEC = PROG_ERR_MORE_DATA_EXPECTED;
#endif
                    /* Send negative response NRC13 */
                    m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_13;
                    /* Emit event PROG_EVENT_FAILED*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
              }
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            }
            else
            {
#if PROG_PEC_ENABLE == STD_ON
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_DATA_TYPE;
#endif
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                /* Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
#endif /*(PROG_COMPRESSION_ENABLE == STD_ON)            */
            break;
#if (PROG_COMPRESSION_ENABLE == STD_ON)
        /* compressed datatype could be whether 0x0401 (ARLE) or 0x0402 (LZMA) */
        case PROG_DATATYPE_COMPRESSED:
            /* Check if DFI = 0x10 */
            if(m_stReprogInfo.ubCompRequired == TRUE)
            {
                /* Data are compressed, check data length*/
                if(m_stDiagMessageInfo.ulLength > 10U)
                {
                    /* Get compressed Data size and add the compression header size*/
                    m_stReprogInfo.ulMemorySizeExpected = PROG_GET_U32_VAL(&m_stDiagMessageInfo.pubData[6]) + PROG_COMP_HEADER_SIZE;

                    m_stReprogInfo.ubCompRequired=TRUE;

                    /* Emit event PROG_EVENT_DECOMP_HEADER*/

                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_DECOMP_HEADER);

                }
                else
                {
#if PROG_PEC_ENABLE == STD_ON
                    /* Set error in PEC */
                    m_uwPEC = PROG_ERR_MORE_DATA_EXPECTED;
#endif
                    /* Send negative response NRC13 */
                    m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_13;
                    /* Emit event PROG_EVENT_FAILED*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);

                }
            }
            else
            {
#if PROG_PEC_ENABLE == STD_ON
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_DATA_TYPE;
#endif
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                /* Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
            break;
#endif /*(PROG_COMPRESSION_ENABLE == STD_ON)            */
        default:
#if PROG_PEC_ENABLE == STD_ON
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_DATA_TYPE;
#endif
            if(m_stDiagMessageInfo.pubData[1] != m_stReprogInfo.ubBlockSequenceCounter)
            {
                /* Send negative response NRC73 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_73;
            }
            else
            {
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            }
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
    }
    DBG_PROG_ENTRY_TD_HEADER_EXIT();
}
/*---------------------------{end PROG_Entry_TD_Header}--------------------------*/
#endif /* if PROG_TRANSFER_DATA_ENABLE == STD_ON */




#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/*-------------------------{PROG_MessageDigestCheck}--------------------------------*/
void PROG_MessageDigestCheck(void)
{
    u8 ubIdx;
    tProgStatus eProgStatus;
    DBG_PROG_MESSAGEDIGESTCHECK_ENTRY();

    eProgStatus = PROG_E_OK;

    for(ubIdx = 0U; ubIdx < PROG_DIGEST_LENGTH; ubIdx++)
    {
        /* Compare digest */
        if(m_aubComputedMessageDigest[ubIdx] != m_aubMessageDigest[ubIdx])
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    if(eProgStatus == PROG_E_OK)
    {
        /* Go to RTE FINISH state, emit event PROG_EVENT_FINISHED */
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
    }
    else
    {
#if PROG_PEC_ENABLE == STD_ON
        /* Set error in PEC */
        m_uwPEC = PROG_ERR_MD;
#endif
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
        /* Go to RTE error state, emit event PROG_EVENT_FAILED*/
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    DBG_PROG_MESSAGEDIGESTCHECK_EXIT();
}
/*-----------------------{end PROG_MessageDigestCheck}------------------------------*/

/*-------------------------{PROG_ComputeMessageDigest}--------------------------------*/
void PROG_ComputeMessageDigest(void)
{
    tProgStatus eCrcStatus;
    DBG_PROG_COMPUTEMESSAGEDIGEST_ENTRY();

    eCrcStatus = PROG_CRC();
    if ( PROG_E_OK == eCrcStatus)
    {
        /* Digest computation is finish */
        PROG_ComputeHashFinish(&m_aubComputedMessageDigest[0]);
    }
    DBG_PROG_COMPUTEMESSAGEDIGEST_EXIT();
}
/*-----------------------{end PROG_ComputeMessageDigest}------------------------------*/

/*-------------------------{PROG_SignatureCheck}--------------------------------*/
void PROG_SignatureCheck(void)
{
    tProgStatus eProgStatus;
    u8 ubIdx;
    u16 uwOffset;

    DBG_PROG_SIGNATURECHECK_ENTRY();

    /* Check if crypto calculation is finish */
    eProgStatus = PROG_GetCryptoStatus();

    switch(eProgStatus)
    {
        case PROG_E_OK:
            /* call API to final signed header check */
            eProgStatus = PROG_FinalizeCheckSignedHeader(m_pubHeaderAddress);

            if(eProgStatus == PROG_E_OK)
            {
                if(m_stCurrentSegment.uwModuleId == PROG_SW_APP_ID)
                {
                    /* Calculate the offset of the digest */
                    uwOffset = ((u16)((u16)((u16)((u16)m_pubHeaderAddress[30] << 8U) & 0xFF00U)
                                | (u16)((u16)m_pubHeaderAddress[31] & 0x00FFU)) * 8U) + 4U;
                }
                else
                {
                    /* No offset for calibration module */
                    uwOffset = 0U;
                }

                for(ubIdx = 0U; ubIdx < PROG_DIGEST_LENGTH; ubIdx++)
                {
                    m_aubMessageDigest[ubIdx] = m_pubHeaderAddress[28U + uwOffset + ubIdx];
                }

                /* Emit event PROG_EVENT_REQ_TD*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD);
            }
            else
            {
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                /* Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
            break;
        case PROG_E_BUSY:
            /* Wait for crypto to finish its treatment */
            break;
        default:
#if (PROG_PEC_ENABLE == STD_ON)
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_SIGNATURE;
#endif
            /* Send negative response NRC31 */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
    }
    DBG_PROG_SIGNATURECHECK_EXIT();
}
/*-----------------------{end PROG_SignatureCheck}------------------------------*/

/*-------------------------{PROG_Entry_ValidateSignature}--------------------------------*/
void PROG_Entry_ValidateSignature(void)
{
    tProgStatus eProgStatus;
    u16 uwModuleId;
    u16 uwRegionNbr;
    u32 ulDataSize;
    u8* pubSignatureAddr;
    u8 ubIdx;
    u8 ubStoredSBIFlag;
    u8 * paubSwInfoPublicModulus;
    u16 uwInnerEnvSign;
    u16 uwHeaderSize;

    DBG_PROG_ENTRY_VALIDATESIGNATURE_ENTRY();

    /* Check Module Id */
    uwModuleId = ((u16)((u16)((u16)m_pubHeaderAddress[0] << 8U) & 0xFF00U) | (u16)(((u16)m_pubHeaderAddress[1]) & 0x00FFU));
    uwRegionNbr = ((u16)((u16)((u16)m_pubHeaderAddress[30] << 8U) & 0xFF00U) | (u16)(((u16)m_pubHeaderAddress[31]) & 0x00FFU));
    eProgStatus = PROG_E_OK;

    if(uwModuleId == PROG_SW_APP_ID)
    {
      uwHeaderSize = 862U + (8U*uwRegionNbr);
      uwInnerEnvSign = (u16)((u16)((u16)m_pubHeaderAddress[uwHeaderSize-4U] << 8U) & 0xFF00U)
                          | (u16)(((u16)m_pubHeaderAddress[uwHeaderSize-3U]) & 0x00FFU);
    }
    else
    {
      uwHeaderSize = 858U;
      uwInnerEnvSign = (u16)((u16)((u16)m_pubHeaderAddress[uwHeaderSize-4U] << 8U) & 0xFF00U)
                          | (u16)(((u16)m_pubHeaderAddress[uwHeaderSize-3U]) & 0x00FFU);
    }
    if(uwInnerEnvSign != PROG_DATATYPE_PLAIN)
    {
#if PROG_PEC_ENABLE == STD_ON
      /* Set error in PEC */
      m_uwPEC = PROG_ERR_DATA_TYPE;
#endif
      /* Wrong param */
      eProgStatus = PROG_E_NOT_OK;
    }

    if(eProgStatus == PROG_E_OK)
    {
      ubStoredSBIFlag = PROG_GetSBIFlagValue();

        if(ubStoredSBIFlag == TRUE)
        {
            (void)PROG_FinalizeCheckSignedHeader(m_pubHeaderAddress);

            /* Emit event PROG_EVENT_REQ_TD*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD);

        }
        else
        {
            if((m_pubHeaderAddress[0] == 0U) && (m_pubHeaderAddress[1] == 1U))
            {
                paubSwInfoPublicModulus = &m_pubHeaderAddress[90U + (uwRegionNbr*8U)];

                ulDataSize = (u32)( 602U + ((u32)((u32)uwRegionNbr & 0x0000FFFFU) * 8U) );

                pubSignatureAddr = &m_pubHeaderAddress[ulDataSize];

                m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */
                for(ubIdx = 0U; /* Modulus */
                    ubIdx < m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U];
                    ubIdx++)
                {
                    u8 ubLocIdx = ubIdx + ((u8)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
                    m_stProgAsymPublicKey.data[ubLocIdx] = (u32) paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
                }
            }
            else
            {
                ulDataSize = 598U;

                pubSignatureAddr = &m_pubHeaderAddress[598];
                paubSwInfoPublicModulus = &m_pubHeaderAddress[86U];
                m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U] = (PROG_KEY_LENGTH/sizeof(u32));/* Modulus size */
                for(ubIdx = 0U; /* Modulus */
                    ubIdx < m_stProgAsymPublicKey.data[(PROG_KEY_LENGTH/sizeof(u32)) + 1U];
                    ubIdx++)
                {
                    u8 ubLocIdx = ubIdx + ((u8)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
                    m_stProgAsymPublicKey.data[ubLocIdx] = (u32) paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
                    m_stProgAsymPublicKey.data[ubLocIdx] |= (u32)((u32)((u32)paubSwInfoPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
                }
            }

            /* Call crypto library to verify the root signature */

            eProgStatus = PROG_VerifySignature
                            (
                                &m_stProgAsymPublicKey,
                                m_pubHeaderAddress,
                                ulDataSize,
                                pubSignatureAddr
                            );

            if(eProgStatus == PROG_E_NOT_OK)
            {
#if (PROG_PEC_ENABLE == STD_ON)
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_SIGNATURE;
#endif
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                /* Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
          }
    }
    else
    {
      /* Send negative response NRC31 */
      m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
      /* Emit event PROG_EVENT_FAILED*/
      PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    DBG_PROG_ENTRY_VALIDATESIGNATURE_EXIT();
}

/*-----------------------{end PROG_Entry_ValidateSignature}------------------------------*/


/*-------------------------{PROG_Entry_ValidateSignerInfo}--------------------------------*/
void PROG_Entry_ValidateSignerInfo(void)
{
    tProgStatus eProgStatus;
    u16 uwModuleId;
    u16 uwRegionNbr;
    u16 uwStoreKeyNBID;
    u16 uwKeyNBID;
    u8* pubDataAddr;
    u8* pubSignatureAddr;

    DBG_PROG_ENTRY_VALIDATESIGNERINFO_ENTRY();

    /* Check Module Id */
    uwModuleId = ((u16)((u16)((u16)m_pubHeaderAddress[0] << 8U) & 0xFF00U) | (u16)(((u16)m_pubHeaderAddress[1U]) & 0x00FFU));

    if(uwModuleId == PROG_SW_APP_ID)
    {
        uwRegionNbr = ((u16)((u16)((u16)m_pubHeaderAddress[30] << 8U) & 0xFF00U) | (u16)(((u16)m_pubHeaderAddress[31U]) & 0x00FFU));
        pubDataAddr = &m_pubHeaderAddress[64U + (uwRegionNbr*8U)];
        pubSignatureAddr = &m_pubHeaderAddress[346U + (uwRegionNbr*8U)];
    }
    else
    {
        pubDataAddr = &m_pubHeaderAddress[60];
        pubSignatureAddr = &m_pubHeaderAddress[342];
    }

    /* Check subject name validity */
    eProgStatus = PROG_CheckSubjectName(pubDataAddr);

    if(eProgStatus == PROG_E_OK)
    {
        /* Get the Key NBID */
        uwStoreKeyNBID = PROG_GetKeyNBIDValue();

        /* Retrieve Key NBID received from signer info pointer */
        uwKeyNBID = ((u16)((u16)((u16)pubDataAddr[24] << 8U) & 0xFF00U) | (u16)(((u16)pubDataAddr[25]) & 0x00FFU));

        /* If the retrieved key NBID is more recent than the stored key NBID */
        if (uwKeyNBID >= uwStoreKeyNBID)
        {
            /* Store the new key NBID to write it in memory at the end the complete successful download */
            m_uwKeyNBID = uwKeyNBID;

            /* Call crypto library to verify the root signature */
            eProgStatus = PROG_VerifySignature(&m_stProgAsymPublicKey_cbk, pubDataAddr, 282U, pubSignatureAddr);

            /* In case of error */
            if(eProgStatus == PROG_E_NOT_OK)
            {
#if (PROG_PEC_ENABLE == STD_ON)
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_ROOT_SIGNATURE;
#endif
                /* Send negative response NRC31 */
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
                /* Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            }
        }
        else
        {
#if (PROG_PEC_ENABLE == STD_ON)
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_KEY_NBID;
#endif
            /* Send negative response NRC31 */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
    {
#if (PROG_PEC_ENABLE == STD_ON)
        /* Set error in PEC */
        m_uwPEC = PROG_ERR_SUBJECT_NAME;
#endif
        /* Send negative response NRC31 */
        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
        /* Emit event PROG_EVENT_FAILED*/
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    DBG_PROG_ENTRY_VALIDATESIGNERINFO_EXIT();
}
/*-----------------------{end PROG_Entry_ValidateSignerInfo}------------------------------*/


/*-------------------------{PROG_SignerInfoCheck}--------------------------------*/
void PROG_SignerInfoCheck(void)
{
    tProgStatus eOperationStatus;

    DBG_PROG_SIGNERINFOCHECK_ENTRY();

    /* Check if crypto calculation is finish */
    eOperationStatus = PROG_GetCryptoStatus();

    switch(eOperationStatus)
    {
        case PROG_E_OK:
            /* Emit event PROG_EVENT_VALIDATE_SIGNATURE*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_VALIDATE_SIGNATURE);
            break;
        case PROG_E_BUSY:
            /* Wait for crypto to finish its treatment */
            break;
        default:
#if (PROG_PEC_ENABLE == STD_ON)
            /* Set error in PEC */
            m_uwPEC=PROG_ERR_ROOT_SIGNATURE;
#endif
            /* Send negative response NRC31 */
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
            /* Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
    }
    DBG_PROG_SIGNERINFOCHECK_EXIT();
}


/*-----------------------{end PROG_SignerInfoCheck}------------------------------*/


#endif /* if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON */




/*----------------------------{PROG_InvalidateSection}---------------------------*/
#if (PROG_ERASE_MEMORY_ENABLE == STD_ON)
tProgStatus PROG_InvalidateSection(u8 ubPartitionId)
{
    tUdsStatus eUdsStatus;
    tProgStatus eProgStatus=PROG_E_OK;
    u8 ubcurrentSegmentId=ubPartitionId;
    u32 ulcurrentAddress;
    u8 ublocalPartitionId=0;
    DBG_PROG_INVALIDATESECTION_ENTRY(ubPartitionId );

    if(ubPartitionId == PROG_SW_APP_ID)
    {
        /* Check if application is valid */
        eProgStatus = PROG_CheckPSIValue(ubPartitionId, PROG_PSI_PROGRAMMED);

        /* Revoke application */
        PROG_WritePSIValue(ubPartitionId, PROG_PSI_REVOKED, &eUdsStatus);

        /* if application was programmed */
        if(eProgStatus == PROG_E_OK)
        {

            /* Revoke all calibration partition starting by the first one (partion number 1 is the application) */
            for(ublocalPartitionId = 2U;((ublocalPartitionId <= (PROG_GET_CALIB_PARTITION_NB + 1U)) && (eUdsStatus == UDS_ACK) ); ublocalPartitionId++)
            {
              /* Get Expected start adress for the first region of any partition */
              ulcurrentAddress = PROG_GET_CALIB_SW_FIRST_REGION_ADDR_START(ublocalPartitionId);
              /* Call GetSegmentByAddress API to get the current SegmentId */
              eProgStatus = PROG_GetSegmentByAddress(ulcurrentAddress, 0U, PROG_MEM_OPERATION_TYPE_READ,  &ubcurrentSegmentId);
              if( (PROG_PROT_CALIBRATION_PARTITION != stConfigSegment[ubcurrentSegmentId].ePartitionType) &&
                  (eProgStatus == PROG_E_OK))
              {
                /* Reset expectedModuleId for calibration programming */
                m_stReprogInfo.uwExpectedModuleId[ublocalPartitionId - 1U] = PROG_GET_CALIB_SW_FIRST_MODULE_ID(ublocalPartitionId);

                PROG_WritePSIValue(ublocalPartitionId, PROG_PSI_REVOKED, &eUdsStatus);

              }
            }
        }
        /* if application was not programmed only set the application to revoked */
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        PROG_WritePSIValue(ubPartitionId, PROG_PSI_REVOKED, &eUdsStatus);

        if(UDS_ACK == eUdsStatus)
        {
            /* Reset expectedModuleId for calibration programming */
            m_stReprogInfo.uwExpectedModuleId[ubPartitionId - 1U] = PROG_GET_CALIB_SW_FIRST_MODULE_ID(ubPartitionId);
        }

#if PROG_PEC_ENABLE == STD_ON
        ubPartitionId++;
        ublocalPartitionId = ubPartitionId;
#endif /*if PROG_PEC_ENABLE == STD_ON*/
    }

    if(eUdsStatus != UDS_ACK)
    {
#if PROG_PEC_ENABLE == STD_ON
        if((ublocalPartitionId - 1U) == PROG_SW_APP_ID)
        {
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_REVOKE_SW;
        }
        else
        {
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_REVOKE_CAL;
        }
#endif /* PROG_PEC_ENABLE == STD_ON */
        /* Set negative status */
        eProgStatus = PROG_E_NOT_OK;
    }
    else
    {
        eProgStatus = PROG_E_OK;
    }
    DBG_PROG_INVALIDATESECTION_EXIT(eProgStatus );
    return eProgStatus;
}
#endif /*  (PROG_ERASE_MEMORY_ENABLE == STD_ON)*/
/*----------------------------{end PROG_InvalidateSection}-----------------------*/

/*----------------------------{PROG_MemDataAccessByRegion}------------------------*/

tProgStatus PROG_MemDataAccessByRegion
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    u32* pulLength,
    tDataBufferType* paubDataBuffer
)
{
    tProgStatus eProgStatus;
    u32 ulRemaningDataToWrite;
    u32 ulOffsetInTD;
    static u32 ulSize;
    u32 ulWriteOffsetInRegion;
    u32 ulDataLength;
    static u32 ulWrittenData;
    static u8 ubRegionIndex;
    static u8 ubExitLoop;
    u8 ubMemoryType;

    ulRemaningDataToWrite = *pulLength;
    ulOffsetInTD = uMemAddress;

    ulSize = 0U;
    ubRegionIndex = 0U;
    ulWrittenData = 0U;
    ubExitLoop = FALSE;

    /* Calculate the size already written in the partition */
    while ((ubRegionIndex < m_stCurrentSegment.ubRegionNbr) && (ulOffsetInTD >= (ulSize + m_stCurrentSegment.astRegion[ubRegionIndex].ulSize)))
    {
        ulSize += m_stCurrentSegment.astRegion[ubRegionIndex].ulSize;
        ubRegionIndex++;
    }

    /* If number of region not exceeded */
    if(ubRegionIndex < m_stCurrentSegment.ubRegionNbr)
    {
        /* Calculate offset in current region */
        ulWriteOffsetInRegion = ulOffsetInTD - ulSize;

        do
        {
            /* Calculate the length to write in the region */
            if(ulRemaningDataToWrite > (m_stCurrentSegment.astRegion[ubRegionIndex].ulSize - ulWriteOffsetInRegion))
            {
                ulDataLength = m_stCurrentSegment.astRegion[ubRegionIndex].ulSize - ulWriteOffsetInRegion;
            }
            else
            {
                ulDataLength = ulRemaningDataToWrite;
            }

            eProgStatus = PROG_MemDataAccess(
                        eMemType,
                        eOperationType,
                        m_stCurrentSegment.astRegion[ubRegionIndex].ulAddress + ulWriteOffsetInRegion,
                        ulDataLength,
                        &paubDataBuffer[ulWrittenData]);

            ulRemaningDataToWrite -= ulDataLength;

            if((ulRemaningDataToWrite > 0U) && ((eProgStatus == PROG_E_OK) || (eProgStatus == PROG_E_BUSY)))
            {

                ubMemoryType = m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType;

                if(ubMemoryType == PROG_MEM_TYPE_FLASH)
                {
#if (PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS)
                    if((ubRegionIndex == 0U)||(eProgStatus == PROG_E_BUSY))
#else
                    if(ubRegionIndex == 0U)
#endif
                    {
                        *pulLength -= ulRemaningDataToWrite;
                        ubExitLoop = TRUE;
                    }
                    else
                    {
                        ubRegionIndex++;
                        ulWriteOffsetInRegion = 0U;
                        ulWrittenData += ulDataLength;

                        if(ubRegionIndex >= m_stCurrentSegment.ubRegionNbr)
                        {
                            eProgStatus = PROG_E_NOT_OK;
                            ubExitLoop = TRUE;
                        }
                    }
                }
                else if(ubMemoryType == PROG_MEM_TYPE_FLASH_EXT)
                {
#if (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS)
                    if((ubRegionIndex == 0U)||(eProgStatus == PROG_E_BUSY))
#else
                    if(ubRegionIndex == 0U)
#endif
                    {
                        *pulLength -= ulRemaningDataToWrite;
                        ubExitLoop = TRUE;
                    }
                    else
                    {
                        ubRegionIndex++;
                        ulWriteOffsetInRegion = 0U;
                        ulWrittenData += ulDataLength;

                        if(ubRegionIndex >= m_stCurrentSegment.ubRegionNbr)
                        {
                            eProgStatus = PROG_E_NOT_OK;
                            ubExitLoop = TRUE;
                        }
                    }

                }
                else if(ubMemoryType == PROG_MEM_TYPE_CUSTOM)
                {
#if (PROG_CUSTOM_MEMORY_MODE == PROG_MEMORY_ASYNCHRONOUS)
                    if((ubRegionIndex == 0U) || (eProgStatus == PROG_E_BUSY))
#else
                    if(ubRegionIndex == 0U)
#endif
                    {
                        *pulLength -= ulRemaningDataToWrite;
                        ubExitLoop = TRUE;
                    }
                    else
                    {
                        ubRegionIndex++;
                        ulWriteOffsetInRegion = 0U;
                        ulWrittenData += ulDataLength;

                        if(ubRegionIndex >= m_stCurrentSegment.ubRegionNbr)
                        {
                            eProgStatus = PROG_E_NOT_OK;
                            ubExitLoop = TRUE;
                        }
                    }
                }
                else
                {
                    /* nothing to do*/
                }
                /* For SwAppInfo set the real length written since it can be not aligned on a flash page */
            }
            else
            {
                ubExitLoop = TRUE;
            }
        }
        while(ubExitLoop == FALSE);
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
    }

    return eProgStatus;

}

/*----------------------------{end PROG_MemDataAccessByRegion}--------------------*/























/*----------------------------{PROG_CheckSignedHeader}----------------------------*/
NCS_PRI_FCT tProgStatus PROG_CheckSignedHeader(u8 * pubHeaderAddr)
{
    tProgStatus eProgStatus;
    u16 uwModuleId;
    u16 uwXCID;

    /* Get Module Id */
    uwModuleId = (u16)((u16)((u16)((u16)pubHeaderAddr[0] << 8U) & 0xFF00U) | (u16)((u16)pubHeaderAddr[1U] & 0x00FFU));
    /* Get BCID/CCID Id */
    uwXCID = (u16)((u16)((u16)((u16)pubHeaderAddr[2] << 8U) & 0xFF00U) | (u16)((u16)pubHeaderAddr[3U] & 0x00FFU));

    /* Check if it is application module */
    if(uwModuleId == PROG_SW_APP_ID)
    {
        /* get the number of region */
        m_stCurrentSegment.ubRegionNbr = pubHeaderAddr[31];

        /* Get AppSwInfo address and Size */

        /* Initialize current segment */
        m_stCurrentSegment.ulSize = 0U;
        m_stCurrentSegment.ulStartAddress = 0U;
        m_stWriteInfo.ulAddressToWrite = 0U;
        m_stDataProgVerification.ulAdd = 0U;
        m_stDataProgVerification.ubAlgo = PROG_VERIFY_HASH;
        eProgStatus = PROG_CheckApplSignedHeader(uwXCID, m_stCurrentSegment.ubRegionNbr, pubHeaderAddr);
    }
    else
    {
        eProgStatus = PROG_CheckCalSignedHeader(uwModuleId,uwXCID);
    }

    if (eProgStatus == PROG_E_OK)
    {
        m_stCurrentSegment.uwModuleId = uwModuleId;

        /* Check ECU name */
        eProgStatus = PROG_CheckEcuName(&pubHeaderAddr[4]);

#if PROG_PEC_ENABLE == STD_ON
        if (eProgStatus != PROG_E_OK)
        {
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_ECU_NAME;
        }
#endif
    }

    if (eProgStatus == PROG_E_OK)
    {
        /* Check ECU ID */
        eProgStatus = PROG_CheckEcuId(&pubHeaderAddr[12]);

#if PROG_PEC_ENABLE == STD_ON
        if (eProgStatus != PROG_E_OK)
        {
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_ECU_ID;
        }
#endif
    }

    return eProgStatus;
}
/*----------------------------{end PROG_CheckSignedHeader}------------------------*/

/*----------------------------{PROG_CheckApplSignedHeader}------------------------*/

NCS_PRI_FCT tProgStatus PROG_CheckApplSignedHeader(u16 uwXCID, u16 uwRegionNbr, const u8 * pubHeaderAddr)
{
    tProgStatus eProgStatus;
    u8 ubRegionIndex;
    u8 ubLocalSegmentId;
    u32 ulStartAddress;
    u32 ulMemorySize;

    eProgStatus = PROG_E_OK;

    if((uwXCID == m_stBootInfoBlock.uwBCID)
            || ( m_stBootInfoBlock.uwBCID == 0xFFFFU)
            || (uwXCID == 0xFFFFU))
    {
        /* Check address/size of every application region */
        for(ubRegionIndex = 0U; ((ubRegionIndex < uwRegionNbr) && (eProgStatus == PROG_E_OK)); ubRegionIndex++)
        {
            /* Check App SW Location Info */
            /* Get start address */
            ulStartAddress = (u32)((((u32)(pubHeaderAddr[32U + (ubRegionIndex * 8U)])) << 24U) & (u32)(0xff000000U));
            ulStartAddress += (u32)((((u32)(pubHeaderAddr[33U + (ubRegionIndex * 8U)])) << 16U) & (u32)(0x00ff0000U)) ;
            ulStartAddress += (u32)((((u32)(pubHeaderAddr[34U + (ubRegionIndex * 8U)])) << 8U) & (u32)(0x0000ff00U)) ;
            ulStartAddress += (u32)(((u32)(pubHeaderAddr[35U + (ubRegionIndex * 8U)])) & (u32)(0x000000ffU));

            /* get length */
            ulMemorySize = (u32)((((u32)(pubHeaderAddr[36U + (ubRegionIndex * 8U)])) << 24U) & (u32)(0xff000000U));
            ulMemorySize += (u32)((((u32)(pubHeaderAddr[37U + (ubRegionIndex * 8U)])) << 16U) & (u32)(0x00ff0000U)) ;
            ulMemorySize += (u32)((((u32)(pubHeaderAddr[38U + (ubRegionIndex * 8U)])) << 8U) & (u32)(0x0000ff00U)) ;
            ulMemorySize += (u32)(((u32)(pubHeaderAddr[39U + (ubRegionIndex * 8U)])) & (u32)(0x000000ffU));


            m_stCurrentSegment.astRegion[ubRegionIndex].ulAddress = ulStartAddress;
            m_stCurrentSegment.astRegion[ubRegionIndex].ulSize = ulMemorySize;
            m_stCurrentSegment.ulSize += ulMemorySize;

            /* Check address */
            eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, ulMemorySize,
                                    PROG_MEM_OPERATION_TYPE_WRITE,
                                    &ubLocalSegmentId);

            if(stConfigSegment[ubLocalSegmentId].ePartitionType != PROG_APPLICATION_PARTITION)
            {
                eProgStatus = PROG_E_NOT_OK;
            }

#if (PROG_COMPRESSION_ENABLE == STD_ON)
            if (m_stReprogInfo.ubCompRequired == FALSE)
#endif
            {
                m_stReprogInfo.ulMemorySizeExpected = m_stCurrentSegment.ulSize;
            }

#if PROG_PEC_ENABLE == STD_ON
            if(eProgStatus != PROG_E_OK)
            {
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_SW_REGION;
            }
#endif
        }

    }
    else
    {
        /* Wrong param */
        eProgStatus = PROG_E_NOT_OK;

#if PROG_PEC_ENABLE == STD_ON
        /* Set error in PEC */
        m_uwPEC = PROG_ERR_BCID;
#endif
    }

    return eProgStatus;
}

/*----------------------------{end PROG_CheckApplSignedHeader}--------------------*/


/*----------------------------{PROG_CheckCalSignedHeader}-------------------------*/
NCS_PRI_FCT tProgStatus PROG_CheckCalSignedHeader(u16 uwModuleId, u16 uwXCID)
{
    tProgStatus eProgStatus;
    u8 ubPartitionId;
    u8 ubModuleIndex;
    u8 ubLocalSegmentId;
    u32 ulStartAddress;
    u32 ulMemorySize;
    u16 uwModuleCCID;

    ubPartitionId = 0U;
    ubModuleIndex = 0U;

    eProgStatus = PROG_GetModulePartition(uwModuleId, &ubPartitionId, &ubModuleIndex);

    if(eProgStatus == PROG_E_OK)
    {
        if(m_stReprogInfo.uwExpectedModuleId[ubPartitionId - 1U] == uwModuleId)
        {
            uwModuleCCID = PROG_GET_CALIB_SW_MODULE_CCID(ubPartitionId,ubModuleIndex);
            if((uwXCID == 0xFFFFU)
                    || ( 0xFFFFU == uwModuleCCID)
                    || (uwXCID == uwModuleCCID))
            {
                /* Check Module range doesn't overlap PSI*/
                if((PROG_GET_CALIB_SW_MODULE_ADDR(ubPartitionId,ubModuleIndex)
                        + PROG_GET_CALIB_SW_MODULE_SIZE(ubPartitionId,ubModuleIndex))
                        <= (((PROG_GET_CALIB_SW_LAST_REGION_ADDR_START(ubPartitionId)
                                + PROG_GET_CALIB_SW_LAST_REGION_SIZE(ubPartitionId))) - PROG_PSI_SIZE))
                {
                    /* Check Cal SW Location Info */
                    ulStartAddress = PROG_GET_CALIB_SW_MODULE_ADDR(ubPartitionId,ubModuleIndex);
                    ulMemorySize = PROG_GET_CALIB_SW_MODULE_SIZE(ubPartitionId,ubModuleIndex);

                    /* For calibration module store size and module ID */
                    m_stCurrentSegment.ulSize = ulMemorySize;
                    m_stWriteInfo.ulAddressToWrite = ulStartAddress;
                    m_stDataProgVerification.ulAdd = ulStartAddress;
                    m_stDataProgVerification.ubAlgo = PROG_VERIFY_HASH;
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            if (m_stReprogInfo.ubCompRequired == FALSE)
#endif
            {
                m_stReprogInfo.ulMemorySizeExpected = m_stCurrentSegment.ulSize;
            }
                    /* Check address */
                    eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, ulMemorySize,
                                            PROG_MEM_OPERATION_TYPE_WRITE,
                                            &ubLocalSegmentId);

                    if((stConfigSegment[ubLocalSegmentId].ePartitionType != PROG_CALIBRATION_PARTITION)&&(stConfigSegment[ubLocalSegmentId].ePartitionType != PROG_PROT_CALIBRATION_PARTITION))
                    {
                        eProgStatus = PROG_E_NOT_OK;
                    }

#if PROG_PEC_ENABLE == STD_ON
                    if(eProgStatus != PROG_E_OK)
                    {
                        /* Set error in PEC */
                        m_uwPEC = PROG_ERR_CAL_REGION;
                    }
#endif
                }
                else
                {
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
            else
            {
#if PROG_PEC_ENABLE == STD_ON
                /* Set error in PEC */
                m_uwPEC = PROG_ERR_CCID;
#endif
                /* Wrong param */
                eProgStatus = PROG_E_NOT_OK;
            }
        }
        else
        {
#if PROG_PEC_ENABLE == STD_ON
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_MODULE_ID;
#endif
            /* Wrong param */
            eProgStatus = PROG_E_NOT_OK;
        }
    }
#if PROG_PEC_ENABLE == STD_ON
    else
    {
        /* Set error in PEC */
        m_uwPEC = PROG_ERR_MODULE_ID;
    }
#endif

    return eProgStatus;
}

/*----------------------------{end PROG_CheckCalSignedHeader}---------------------*/


/*----------------------------{PROG_CheckEcuId}-----------------------------------*/

NCS_PRI_FCT tProgStatus PROG_CheckEcuId(const u8* pubEcuId)
{
    tProgStatus eProgStatus;
    u8 ubLoopIndex;
    u8 ubIDCheckResult;
#if (PROG_USE_ECUID_CALLBACK == STD_ON)
    u8 aubEcuId[PROG_ECU_ID_SIZE];
#endif /*(PROG_USE_ECUID_CALLBACK == STD_ON)*/
    eProgStatus = PROG_E_OK;
    ubIDCheckResult = TRUE;

    for(ubLoopIndex = 0U; ((ubLoopIndex < PROG_ECU_ID_SIZE ) && (ubIDCheckResult == TRUE)); ubLoopIndex++)
    {
        if(pubEcuId[ubLoopIndex] != 0U)
        {
            ubIDCheckResult = FALSE;
        }
    }

    if(ubIDCheckResult == FALSE)
    {
#if (PROG_USE_ECUID_CALLBACK == STD_ON)
        PROG_CustomGetEcuId(&aubEcuId[0]);
#endif /*(PROG_USE_ECUID_CALLBACK == STD_ON)*/
        for(ubLoopIndex = 0U; ((ubLoopIndex < PROG_ECU_ID_SIZE) && (eProgStatus == PROG_E_OK)); ubLoopIndex++)
        {
#if (PROG_USE_ECUID_CALLBACK == STD_OFF)
            if(pubEcuId[ubLoopIndex] != m_stBootInfoBlock.aubEcuId[ubLoopIndex])
            {
                eProgStatus = PROG_E_NOT_OK;
            }
#else
            if(pubEcuId[ubLoopIndex] != aubEcuId[ubLoopIndex])
            {
                eProgStatus = PROG_E_NOT_OK;
            }
#endif /*(PROG_USE_ECUID_CALLBACK == STD_OFF)*/
        }
    }

    return eProgStatus;
}
/*----------------------------{end PROG_CheckEcuId}-------------------------------*/

/*----------------------------{PROG_CheckEcuName}---------------------------------*/

NCS_PRI_FCT tProgStatus PROG_CheckEcuName(const u8* pubEcuName)
{
    tProgStatus eProgStatus;
    u8 ubLoopIndex;

    eProgStatus = PROG_E_OK;

    for(ubLoopIndex = 0U; ((ubLoopIndex < PROG_ECU_NAME_SIZE) && (eProgStatus == PROG_E_OK)); ubLoopIndex++)
    {
        if(pubEcuName[ubLoopIndex] != m_stBootInfoBlock.aubEcuName[ubLoopIndex])
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    return eProgStatus;

}

/*----------------------------{end PROG_CheckEcuName}-----------------------------*/

/*----------------------------{PROG_FinalizeCheckSignedHeader}--------------------*/
NCS_PRI_FCT tProgStatus PROG_FinalizeCheckSignedHeader(const u8 * pubHeaderAddr)
{
    tProgStatus eProgStatus;
    u16 uwModuleId;
    u16 uwRegionNbr;
    u16 uwNBID;
    u16 uwStoredNBID;
    u16 uwHeaderSize;
    u8 ubStoredSBIFlag;

    eProgStatus = PROG_E_OK;
    ubStoredSBIFlag = PROG_GetSBIFlagValue();

    /* Check Module Id */
    uwModuleId = ((u16)((u16)((u16)pubHeaderAddr[0] << 8U) & 0xFF00U) | (u16)(((u16)pubHeaderAddr[1U]) & 0x00FFU));
    uwRegionNbr = ((u16)((u16)((u16)pubHeaderAddr[30] << 8U) & 0xFF00U) | (u16)(((u16)pubHeaderAddr[31U]) & 0x00FFU));

    if(uwModuleId == PROG_SW_APP_ID)
    {
        uwNBID = ((u16)((u16)((u16)pubHeaderAddr[28] << 8U) & 0xFF00U) | (u16)(((u16)pubHeaderAddr[29U]) & 0x00FFU));

        uwStoredNBID = PROG_GetNBIDValue();

        if((uwNBID >= uwStoredNBID) || (ubStoredSBIFlag == TRUE))
        {
            uwHeaderSize = 862U + (8U*uwRegionNbr);


#if (PROG_COMPRESSION_ENABLE == STD_ON)
            if (FALSE == m_stReprogInfo.ubCompRequired)
#endif
            {
                /* Remove Signed Header from request */
                /*Move SID*/
                m_stDiagMessageInfo.pubData[uwHeaderSize] = m_stDiagMessageInfo.pubData[0];
                /*Move BS*/
                m_stDiagMessageInfo.pubData[uwHeaderSize + 1U] = m_stDiagMessageInfo.pubData[1];

                m_stDiagMessageInfo.pubData = &m_stDiagMessageInfo.pubData[uwHeaderSize];
                m_stDiagMessageInfo.ulLength -= uwHeaderSize;
            }
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            else
            {
                /* Remove decompression Header from request */
                /*Move SID*/
                m_stDiagMessageInfo.pubData[8U] = m_stDiagMessageInfo.pubData[0];
                /*Move BS*/
                m_stDiagMessageInfo.pubData[9U] = m_stDiagMessageInfo.pubData[1];

                m_stDiagMessageInfo.pubData = &m_stDiagMessageInfo.pubData[8];
                /* Request Compression lib to removed header data*/
                PROG_DecompWriteDataConfirmation(uwHeaderSize);
            }
#endif
        }
        else
        {
#if PROG_PEC_ENABLE == STD_ON
            /* Set error in PEC */
            m_uwPEC = PROG_ERR_APP_NBID;
#endif
            /* Wrong param */
            eProgStatus = PROG_E_NOT_OK;
        }
    }
    else
    {
        uwHeaderSize = 858U;
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            if (FALSE == m_stReprogInfo.ubCompRequired)
#endif
            {
                /* Remove Signed Header from request */
                /*Move SID*/
                m_stDiagMessageInfo.pubData[uwHeaderSize] = m_stDiagMessageInfo.pubData[0];
                /*Move BS*/
                m_stDiagMessageInfo.pubData[uwHeaderSize + 1U] = m_stDiagMessageInfo.pubData[1];

                m_stDiagMessageInfo.pubData = &m_stDiagMessageInfo.pubData[uwHeaderSize];
                m_stDiagMessageInfo.ulLength -= uwHeaderSize;
            }
#if (PROG_COMPRESSION_ENABLE == STD_ON)
            else
            {
                /* Remove decompression Header from request */
                /*Move SID*/
                m_stDiagMessageInfo.pubData[8U] = m_stDiagMessageInfo.pubData[0];
                /*Move BS*/
                m_stDiagMessageInfo.pubData[9U] = m_stDiagMessageInfo.pubData[1];

                m_stDiagMessageInfo.pubData = &m_stDiagMessageInfo.pubData[8];
                /* Request Compression lib to removed header data*/
                PROG_DecompWriteDataConfirmation(uwHeaderSize);
            }
#endif
    }

    if((ubStoredSBIFlag == FALSE) && (eProgStatus == PROG_E_OK))
    {
        /* Start Hash computation, no data provided within this call*/
        eProgStatus = PROG_ComputeHashStart(PROG_CSM_HASH_FOR_SIGNATURE_ID,NULL_PTR,0U,NULL_PTR);
    }
    return eProgStatus;
}

/*----------------------------{end PROG_FinalizeCheckSignedHeader}----------------*/

/*----------------------------{PROG_CheckCompleteHeader}--------------------*/
NCS_PRI_FCT tProgStatus PROG_CheckCompleteHeader(u8 * pubHeaderAddr,PduLengthType ulLength)
{
    tProgStatus eProgStatus;
    u16 uwModuleId;
    u16 uwRegionNbr;
    u32 ulAppSwInfoSize;

    eProgStatus = PROG_E_NOT_OK;

    if (ulLength >= PROG_MIN_HEADER_SIZE)
    {
        /* Get Module Id */
        uwModuleId = (u16)((u16)((u16)((u16)pubHeaderAddr[0] << 8U) & 0xFF00U) | (u16)((u16)pubHeaderAddr[1U] & 0x00FFU));

        if (PROG_SW_APP_ID == uwModuleId)
        {
            /* Application header */
            if (ulLength >= PROG_MIN_APP_HEADER_SIZE)
            {
                /* Get region number */
                uwRegionNbr = (u16)((u16)((u16)((u16)pubHeaderAddr[30] << 8U) & 0xFF00U) | (u16)((u16)pubHeaderAddr[31U] & 0x00FFU));

                if (ulLength >= (PROG_MIN_APP_HEADER_SIZE + (((PduLengthType)uwRegionNbr-1U)*16U)))
                {
                    /* Get AppSwInfo size */
                    ulAppSwInfoSize = PROG_GetAppSwSize(pubHeaderAddr,uwRegionNbr);
                    if (ulLength >= (PROG_MIN_APP_SIGNED_HEADER_SIZE + (((PduLengthType)uwRegionNbr-1U)*8U) + (PduLengthType)ulAppSwInfoSize))
                    {
                        /* Header is complete */
                        eProgStatus = PROG_E_OK;
                    }
                    else
                    {
                        /* Length is not valid, do nothing, NOK status will be returned */
                    }
                }
                else
                {
                    /* Length is not valid, do nothing, NOK status will be returned */
                }
            }
            else
            {
                /* Length is not valid, do nothing, NOK status will be returned */
            }
        }
        else
        {
            /* Calibration header */
            /* Header is complete */
            eProgStatus = PROG_E_OK;
        }

    }
    else
    {
        /* Length is not valid, do nothing, NOK status will be returned */
    }
    return eProgStatus;
}
/*----------------------------{end PROG_CheckCompleteHeader}----------------*/


/*----------------------------{PROG_GetAppSwSize}---------------------------------*/

NCS_PRI_FCT u32 PROG_GetAppSwSize(u8 * pubHeaderAddr, u16 uwRegionNbr)
{
    u32 ulSize;
    u16 uwModNum;
    u8 ubCalNum;

    ubCalNum = (u8)(PROG_GET_CALIB_PARTITION_NB_FROM_REQ(pubHeaderAddr,uwRegionNbr)+1U);

    uwModNum = (u16)(PROG_GET_CALIB_SW_MODULE_NBR_FROM_REQ(pubHeaderAddr,ubCalNum,uwRegionNbr)*12U);

    /* Deviation MISRAC2012-1 */
    /* Deviation CERTC-1 */
    ulSize = (u32)((u32)((u8*)(&(PROG_GET_CALIB_SW_MODULE_NBR_ADDR_FROM_REQ(pubHeaderAddr,ubCalNum,uwRegionNbr))[2U + uwModNum]))
                /* Deviation MISRAC2012-1 */
               /* Deviation CERTC-1 */
                - (u32)((u8*)(&pubHeaderAddr[860U + (8U * uwRegionNbr)])));

    return ulSize;
}

/*----------------------------{end PROG_GetAppSwSize}-----------------------------*/

/*----------------------------{PROG_CheckSubjectName}-----------------------------*/

NCS_PRI_FCT tProgStatus PROG_CheckSubjectName(const u8* pubSubjectName)
{
    tProgStatus eProgStatus;
    u8 ubLoopIndex;

    eProgStatus = PROG_E_OK;

    for(ubLoopIndex = 0U; ((ubLoopIndex < PROG_SUBJECT_NAME_SIZE) && (eProgStatus == PROG_E_OK)); ubLoopIndex++)
    {
        if(pubSubjectName[ubLoopIndex] != m_stBootInfoBlock.aubSubjectName[ubLoopIndex])
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    return eProgStatus;

}

/*----------------------------{end PROG_CheckSubjectName}-------------------------*/



#endif


/*----------------------------{PROG_HSMUpdate_TD}-----------------------------*/
void PROG_HSMUpdate_TD(void)
{
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
    PduLengthType ullength = 0U;
    u8* pubdata = NULL_PTR;
    u16 uwIdx;
    tProgPECError uwHsmPEC;
    tProgStatus eProgStatus = PROG_E_BUSY;
#if(PROG_COMPRESSION_ENABLE == STD_ON)
    tProgDecompressStateType eCompStatus;
    eCompStatus = PROG_DECOMP_FINISH;
    ullength = 0U;
#else
    OSC_PARAM_UNUSED(ullength);
    OSC_PARAM_UNUSED(pubdata);
#endif

    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

#if(PROG_COMPRESSION_ENABLE == STD_ON)
    if(m_stReprogInfo.ubCompRequired == TRUE)
    {
        eCompStatus = PROG_GetDecompressedData(&pubdata, &ullength);
        if((eCompStatus == PROG_DECOMP_FINISH) || (eCompStatus == PROG_DECOMP_IN_PROGRESS ))
        {
            /*Copy the all Decompressed data from TD request to HSM Buffer*/
            m_ulHsmbufferlength = ullength;
            for(uwIdx = 0U; uwIdx < ullength; uwIdx++)
            {
                m_aubHsmbuffer[uwIdx] = pubdata[uwIdx];
            }
        }
        else
        {
            /*Send NRC 72 and assign the Returned Error code to PEC*/
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
            m_uwPEC = PROG_ERR_COMPRESSION;
            /*Emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
    else
#endif
    {
       /*Copy the all Decompressed data from TD request to HSM Buffer*/
       m_ulHsmbufferlength = m_stDiagMessageInfo.ulLength-2U;
       for(uwIdx = 0U; uwIdx < m_ulHsmbufferlength; uwIdx++)
       {
         m_aubHsmbuffer[uwIdx] = m_stDiagMessageInfo.pubData[uwIdx+2U];
       }
    }
    if( (UDS_ACK == m_stDiagMessageInfo.ubDiagStatus)
#if(PROG_COMPRESSION_ENABLE == STD_ON)
    && ((eCompStatus == PROG_DECOMP_FINISH) || (eCompStatus == PROG_DECOMP_IN_PROGRESS))
#endif
    )
    {
        if(m_uwHSMTimeoutCnt <= PROG_HSM_TIMEOUT)
        {
          /*Call the callback to transfer and receive the response*/
          eProgStatus = Prog_HSMTransferData(&m_aubHsmbuffer[0],m_ulHsmbufferlength, &uwHsmPEC);
          /*Check the respose of the HSM call back*/
          if(eProgStatus != PROG_E_BUSY)
          {
             m_uwHSMTimeoutCnt = 0U;
             if( uwHsmPEC == PROG_PEC_NO_ERROR)
             {
#if(PROG_COMPRESSION_ENABLE == STD_ON)
                if(eCompStatus == PROG_DECOMP_FINISH)
                {
                    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
                    /*Emit event PROG_EVENT_REQ_HSM_FINISH*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_HSMUPDATE_TD_FINISHED);
                }
                else /*(eCompStatus == PROG_DECOMP_IN_PROGRESS)*/
                {
                    PROG_DecompWriteDataConfirmation((u16)(m_ulHsmbufferlength & 0x0000FFFFU));
                    eProgStatus = PROG_DecompressData (NULL_PTR,0U);
                    if(eProgStatus != PROG_E_OK)
                    {
                        /*Send NRC 72 and assign the Returned Error code to PEC*/
                        m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
                        /*Update the Error code to PEC*/
                        m_uwPEC = PROG_ERR_COMPRESSION;
                        /*Emit event PROG_EVENT_FAILED*/
                        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                }
#else
                /*Emit event PROG_EVENT_REQ_HSM_FINISH*/
                m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_HSMUPDATE_TD_FINISHED);
#endif
             }
             else
             {
                /*Send NRC 72 and assign the Returned Error code to PEC*/
                m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
                /*Update the Error code returned to PEC*/
                m_uwPEC = uwHsmPEC;
                /*Emit event PROG_EVENT_FAILED*/
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
             }
          }/*(eProgStatus != PROG_E_BUSY)*/
          else
          {
            /*Do nothing*/
          }
        }
        else
        {
          m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
          m_uwPEC = PROG_ERR_UNDEFINED;
          /*Emit event PROG_EVENT_FAILED*/
          PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
    }
#endif
}

/*----------------------------{end PROG_HSMUpdate_TD}-----------------------------*/


/*----------------------------{PROG_HSMStatusManage}-----------------------------*/

#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
void PROG_HSMStatusManage(void)
{
  if(m_uwHSMTimeoutCnt >= PROG_HSM_MAX_TIMEOUT)
  {
    m_uwHSMTimeoutCnt = 0x00U;
  }
  else
  {
    m_uwHSMTimeoutCnt++;
  }
}
#endif /* if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20)) */

/*----------------------------{end PROG_HSMStatusManage}-----------------------------*/


/*----------------------------{PROG_Entry_HSMUpdate_TDFinish}-----------------------------*/

void PROG_Entry_HSMUpdate_TDFinish(void)
{
#if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
#if(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)
    u8* paubData;
    PduLengthType ulLen;
#endif

    DBG_PROG_EXIT_TD_WRITE_ENTRY();

    if ((PROG_TRUE == m_stWriteInfo.ubTDReceived) && (m_stDiagMessageInfo.ubDiagStatus == UDS_ACK))
    {
#if(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)
        if(PROG_TRUE == m_stMultipleBuffers.eResponsePending)
        {
            /* Send positive response */
            UDS_LongRequestEnd(PROG_TD_RESPONSE_SIZE, m_pubLastBufTxData, UDS_ACK);
        }
#else /*(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)*/
        {
            /* Send positive response */
            UDS_LongRequestEnd(PROG_TD_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);
        }
#endif /*(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)*/
#if (PROG_COMPRESSION_ENABLE == STD_ON)
#if ( PROG_CAL_PRESENT == STD_ON)
        /* Reset Decom variable of current TD */
        m_stWriteInfo.ulInDecompDataLength = 0U;
        PROG_DecompInputParamInit();
#endif
#endif /* (PROG_COMPRESSION_ENABLE == STD_ON) */

        if (m_stDiagMessageInfo.pubData[1] == m_stReprogInfo.ubBlockSequenceCounter)
        {
            PROG_IncrementBlockSequenceCounter();

            /* Increment total number of data received */
            m_stReprogInfo.ulReceivedSizeOfData += (u32)((u32)m_stDiagMessageInfo.ulLength - 2U);

#if (PROG_COMPRESSION_ENABLE == STD_ON)
            /* Increment total number decompress data written */
            m_stReprogInfo.ulTotalDecompDataWrite += m_stWriteInfo.ulWrittenData;
#endif /* (PROG_COMPRESSION_ENABLE == STD_ON) */
        }
        else
        {
            /* nothing to do */
            /* Same block sequence counter received */
            /* it shall not be changed */
        }
    }/*((PROG_TRUE == m_stWriteInfo.ubTDReceived) && (m_stDiagMessageInfo.ubDiagStatus == UDS_ACK))*/
    else
    {
        /* Nothing to do */
        /* TD request has not be fully received */
    }

    /* Reset all variable of current TD */
    m_stWriteInfo.ulDataToBeWritten = 0U;
    m_stWriteInfo.ulWriteLength = 0U;
    m_stWriteInfo.ulWrittenData = 0U;
    m_stWriteInfo.ubTDReceived = PROG_FALSE;

#if(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)
    m_stMultipleBuffers.eResponsePending = PROG_FALSE;
    BlPduR_UnlockBuffer(BLPDUR_OLD_BUFFER);
    BlPduR_GetNextBuffer(&ulLen,&paubData);

    if(paubData != NULL_PTR)
    {
        m_stDiagMessageInfo.pubData = paubData;
        m_stDiagMessageInfo.ulLength = ulLen;
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD);
    }
    else
    {
        m_stMultipleBuffers.eBufferProcessing  = PROG_FALSE;

        /* Look if there was a pending event for another request */
        if (m_stEventInfo.Event != PROG_NO_EVENT)
        {
            /* Store request information */
            m_stDiagMessageInfo.pubData = m_stEventInfo.Data;
            m_stDiagMessageInfo.pubTxData = m_stEventInfo.Data;
            m_stDiagMessageInfo.ulLength = m_stEventInfo.Length;

            /* Post Event in state machine */
            PROG_HsmEmit(&PROG_HsmScPROG, m_stEventInfo.Event);
            m_stEventInfo.Event = PROG_NO_EVENT;
        }
    }
#endif /*(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)*/
#endif /* #if ((PROG_HSM_UPDATE_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20)) */
}
/*----------------------------{end PROG_Entry_HSMUpdate_TDFinish}-----------------------------*/
