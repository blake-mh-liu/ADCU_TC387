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
/*%%   _____________________________   %%  \file PROG_Impl_90.c                  */
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

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.40
 * Do not create incompatible declarations of the same function or object
 *
 * Reason:
 * Two functions are declared to  provide two different functionalities though.
 * they are almost similar in declarations they wont be functional impact.
 *
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
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* Validate Application routine status */
u8 m_ubValidateMemoryStatus;
u8 aubSwitchRoutineCmpltReq[PROG_SWITCHING_SIZEOF_D071_RDID];

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
/* This variable holds the data for Update and switching key feature */
tstUpdateSwitchKeyDataType stUpdateSwitchKeyData;
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

#define PROG_DATA_BLOCKS_COUNT_MSB_OFFSET   2U
#define PROG_DATA_BLOCKS_COUNT_LSB_OFFSET   3U
#define PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET 4U
#define PROG_DATA_BLOCKS_HASH_OFFSET        8U
#define PROG_DATA_BLOCKS_USEFUL_DATA_SIZE   40U
#define PROG_DATA_BLOCKS_COUNT_SIZE         2U
#define PROG_VS_VERSION_SIZE             2U
#define PROG_VERIFICATION_PASSED            0x02U
#define PROG_VERIFICATION_FAILED            0x01U
#define PROG_SIGNATURE_SIZE                 0x100U
#define PROG_SIGNATURE_OFFSET               0x100U

/* Routine 7013 Data Indexes */
#define PROG_DEVPUBLICKEY_POS                            104U
#define PROG_PRODPUBLICKEY_POS                           (PROG_DEVPUBLICKEY_POS + PROG_DEVPUBLICKEY_SIZE)
#define PROG_TOKENPUBLICKEY_POS                          (PROG_DEVPUBLICKEY_POS + PROG_DEVPUBLICKEY_SIZE + PROG_PRODPUBLICKEY_SIZE)
#define PROG_KEYSWITCH_KEYINDEX_POS                      40U
#define PROG_KEYSWITCH_MESSAGESTAT_POS                   39U


/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/* Hash value for each data block */
NCS_PRI_VAR tDataBlockType m_aubHashValueBlock[PROG_MAX_RD_PER_BLOCK];
/* Data block block which is being downloaded */
NCS_PRI_VAR u16 m_uwCurrentDataBlock;
/* Digest compuated by crypto for the data block */
NCS_PRI_VAR u8 m_aubComputedDigest[PROG_DIGEST_LENGTH];
/* Added 8 to include start address and length */
#if (PROG_IMPL_VARIANT == PROG_IMPL_90)
NCS_PRI_VAR u8 m_aubDataToBeSigned[PROG_SBL_VS_LENGTH + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN];
#else
NCS_PRI_VAR u8 m_aubDataToBeSigned[(PROG_MAX_RD_PER_BLOCK*PROG_DATA_BLOCKS_USEFUL_DATA_SIZE) + 4U + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN];
#endif
/* This variable will hold the value of the actual length of the data written for the VS, to be checked later with the expected length of VS */
NCS_PRI_VAR u32 m_ulVSWrittenData;
/* Hash compuated by crypto for the in use Public Key in DER Format */
NCS_PRI_VAR u8 m_aubComputedDerKey[PROG_DIGEST_LENGTH];
/*Pointer to store the address of In use Public Key in DER Format*/
const u8 * ptrDERFormat;
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/** \brief extracts the data block digest from the verification Structure
 **
 ** \param[out] u8* digest values of the data block
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetDigestFromVS(u16 uwDataBlockIndex,u8*aubDigest);


/** \brief provide the verification Structure address
 **
 ** \param[out] u32* address of VS
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetVSAddress(u32 * pulVSAddress);

/** \brief provide the Signature address
 **
 ** \param[out] u32* address of VS
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetSignatureAddress(u32 * pulSignatureAddress);

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
/** \brief Do the check that the 'not-downloaded' areas are erased or set to a known value (for SBL)
 **
 ** \return tProgStatus
 **/
/** \brief extracts the data block number from the verification Structure
 **
 ** \param[in] void
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetDataBlockNbrFromVS(u16 *uwBlockNumber);
#endif

/** \brief checks on the Version and the length of the verification Structure
 **
 ** \param[in] void
 **
 ** \return tProgStatus
 **/
NCS_PRI_VAR tProgStatus PROG_VerifyVSVersionAndLength(void);

/** \brief checks on the array containing the results of hash comparison for each data block
 **
 ** \param[in] void
 **
 ** \return tProgStatus
 **/
NCS_PRI_VAR tProgStatus PROG_CheckHashResults(void);

/** \brief reads the Version of the verification Structure of the currently downloaded block
 **
 ** \param[out] u16 Version
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetVSVersion(u16 *uwVersion);

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
/** \brief extracts the routine data
 **
 ** \param[out] u8 *pubProgSwitchingKeyRoutineResult stores the status incase of failure.
 ** \param[in] const u8 * pubUdsData contains the request.
 ** \param[in] PduLengthType ulDataLength contains the length of the request.
 ** \param[out] tstUpdateSwitchKeyDataType* pstUpdateSwitchKeyData stores the required data.
 **
 ** \return PROG_E_OK incase of success
 **         PROG_E_NOT_OK incase of failure
 **/
NCS_PRI_VAR tProgStatus PROG_ExtractKeyUpdateRoutineData(const u8 * pubUdsData,
        PduLengthType ulDataLength, tstUpdateSwitchKeyDataType* pstUpdateSwitchKeyData, u8 *pubProgSwitchingKeyRoutineResult);


/** \brief verifies the routine length and returns the NRC if length was not the expected one
 **
 ** \param[in] const u8 * pubUdsData contains the request.
 ** \param[in] PduLengthType ulDataLength contains the length of the request.
 **
 ** \return
 **/
NCS_PRI_VAR void PROG_Impl90_VerifySwitchKeyRoutineReqlength(const u8 * pubUdsData, const PduLengthType ulDataLength);
#endif

/** \brief provide the verification Structure length
 **
 ** \param[out] u32* length of VS
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetLogicalBlockVerifStructureLength(u32 * pulVSLength);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

void PROG_Init_Impl90(void)
{
  u8 ubIdx;
  u8 ubIndex;

  for(ubIdx = 0; ubIdx < PROG_MAX_RD_PER_BLOCK; ubIdx++)
  {
    for(ubIndex = 0; ubIndex < PROG_DIGEST_LENGTH; ubIndex++)
    {
        m_aubHashValueBlock[ubIdx].aubDigest[ubIndex] = 0x00;
    }
  }

  m_ubValidateMemoryStatus        = PROG_VALIDITY_ROUTINE_NOTEXEC;
}

/*----------------------------{PROG_Impl90_ApplicationValidatyStatus}-------------------------*/
void PROG_Impl90_ApplicationValidatyStatus(void)
{

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
  tProgBoolean eProgAppValidityStatus;
    eProgAppValidityStatus = PROG_IsValidApplication();

    m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_STATUS_INDEX]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
    if(eProgAppValidityStatus == TRUE)
    {
        m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_RESULT_INDEX]                = (u8) PROG_VERIFICATION_PASSED;
    }
    else
    {
       m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_RESULT_INDEX]                = (u8) PROG_VERIFICATION_FAILED;
    }
    m_stDiagMessageInfo.ulLength = PROG_VAL_MEMORY_RESPONSE_SIZE;
    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
#endif
}

/*----------------------------{PROG_Impl90_Entry_ValidateFinish}-------------------------*/
void PROG_Impl90_Entry_ValidateFinish(void)
{
    /* Post Event in state machine */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_TX_CONF);

    m_ubValidateMemoryStatus = PROG_SIGNATURE_PASSED;

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    (void)PROG_CustomSetDownloadVerificationSuccess(0, m_stCurrentSegment.ubSegmentId, PROG_TRUE);

    m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_STATUS_INDEX]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
    m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_RESULT_INDEX]                = (u8) PROG_VERIFICATION_PASSED;
    m_stDiagMessageInfo.ulLength = PROG_VAL_MEMORY_RESPONSE_SIZE;
    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
#endif
}
/*----------------------------{end PROG_Impl90_Entry_ValidateFinish}-------------------------*/

void PROG_Impl90_Entry_ValidateFailed(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)

  (void)PROG_CustomSetDownloadVerificationSuccess(0, m_stCurrentSegment.ubSegmentId,PROG_FALSE);

  m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_STATUS_INDEX]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
  m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_RESULT_INDEX]                = (u8) PROG_VERIFICATION_FAILED;
  m_stDiagMessageInfo.ulLength = PROG_VAL_MEMORY_RESPONSE_SIZE;
#else
  m_stDiagMessageInfo.pubTxData[PROG_RC_VAL_MEMORY_STATUS_INDEX]                = (u8) (PROG_ROUTINE_FINISHED_NOK | PROG_ROUTINE_TYPE_1);
  m_stDiagMessageInfo.ulLength = PROG_ACTIVE_SBL_RESPONSE_SIZE;
#endif
  m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

  /* Send response */
  UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);


}

void PROG_Impl90_FinalizeHash(void)
{

  tProgBoolean eProgBoolean_VS;
  tProgBoolean eProgBoolean_Sig;

#if (PROG_CRY_PRESENT == STD_ON)
  tProgStatus eProgStatus = PROG_E_OK;
#endif

  eProgBoolean_VS  = PROG_Impl90_IsSignatureAddress(m_stCurrentSegment.ulStartAddress);
  eProgBoolean_Sig = PROG_Impl90_IsVerificationStructureAddress(m_stCurrentSegment.ulStartAddress);

  if((FALSE == eProgBoolean_VS) && (FALSE == eProgBoolean_Sig))
  {
        PROG_ComputeHashFinish(&m_aubComputedDigest[0]);
#if (PROG_CRY_PRESENT == STD_ON)
        eProgStatus = PROG_GetCryptoStatus();

        /* If errors occurred */
        if (PROG_E_NOT_OK == eProgStatus)
        {
            m_stDiagMessageInfo.ulLength = PROG_NRC_SIZE;
            m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_72;
            /* Go to RTE error state, emit event PROG_EVENT_FAILED*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        }
        else
        {
            /* If Crypto return ok, event  PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH will be sent */
            /* If Crypto is busy, nothing to do */
        }
#endif
  }
  else
  {
    /* emit event PROG_EVENT_CRYPTO_FINISH, go to RTE finished */
    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
  }
}

void PROG_Impl90_CompareDataBlockHash(void)
{
  u8 ubIdx;
  u8 ubLoopIndex;
  tProgBoolean eProgBoolean_VS;
  tProgBoolean eProgBoolean_Sig;

  eProgBoolean_VS = PROG_Impl90_IsVerificationStructureAddress(m_stCurrentSegment.ulStartAddress);
  eProgBoolean_Sig = PROG_Impl90_IsSignatureAddress(m_stCurrentSegment.ulStartAddress);

  if((FALSE == eProgBoolean_VS) && (FALSE == eProgBoolean_Sig))
  {

      for (ubLoopIndex = 0; (ubLoopIndex < PROG_DIGEST_LENGTH); ubLoopIndex++)
      {
          m_aubHashValueBlock[m_uwCurrentDataBlock].aubDigest[ubLoopIndex] = m_aubComputedDigest[ubLoopIndex];
      }
      /* Current data block is finished, move to the next data block */
      m_uwCurrentDataBlock++;
  }
  else if (TRUE == PROG_Impl90_IsVerificationStructureAddress(m_stCurrentSegment.ulStartAddress))
  {
    /* VS is now downloaded */
    /* reset data block index */
    m_uwCurrentDataBlock = 0;

    /* VS is now downloaded, set all hash status to not ok */
    for(ubIdx = 0; ubIdx < PROG_MAX_RD_PER_BLOCK; ubIdx++)
    {
      for(ubLoopIndex = 0; ubLoopIndex < PROG_DIGEST_LENGTH; ubLoopIndex++)
      {
          m_aubHashValueBlock[ubIdx].aubDigest[ubLoopIndex] = 0x00;
      }
    }
  }
  else
  {
      /* Do nothing Signature is downloaded */
  }
}

void PROG_Impl90_CheckDataBlocksResult(void)
{
   tProgStatus ubProgStatus = PROG_E_OK;

   /* Check length and Version of verification Structure */
   ubProgStatus = PROG_VerifyVSVersionAndLength();

   /* Length and Version are ok */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Check if any of data blocks failed the hash test */
    ubProgStatus = PROG_CheckHashResults();
   }

   /* VS Blocks are ok */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Check if any of VS blocks mismatch occur */
    ubProgStatus = PROG_CustomCheckVSBlocksMismatch(&m_ubValidateMemoryStatus);
   }

   /* Hash comparison is ok */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Emit event PROG_EVENT_FINISHED*/
     PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
   }
   else
   {
     /* emit event PROG_EVENT_FAILED*/
     PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
   }

}
/* Deviation CERTC-1 */
tProgBoolean PROG_Impl90_IsVerificationStructureAddress(tProgAddressType ulAddress)
{
  tProgBoolean eProgBoolean;
  u32 ulVSAddress;
  u32 ulVSLength;

   /* Get Address of VS  */
  (void)PROG_GetVSAddress(&ulVSAddress);
  if((ulVSAddress >= ulAddress) && (ulVSAddress < (ulAddress + m_stReprogInfo.ulMemorySizeExpected)) )
  {
    eProgBoolean = TRUE;
    /* This function is called from RD context which means that a new VS will be downloaded */
    /* save the length to be written of VS */
    (void)PROG_GetLogicalBlockVerifStructureLength(&ulVSLength);
    m_ulVSWrittenData = ulVSLength;
  }
  else
  {
    eProgBoolean = FALSE;
  }

  return eProgBoolean;
}

tProgBoolean PROG_Impl90_IsSignatureAddress(tProgAddressType ulAddress)
{
  tProgBoolean eProgBoolean;
  u32 ulSignatureAddress;

   /* Get Address of Signature  */
   (void)PROG_GetSignatureAddress(&ulSignatureAddress);
  if((ulSignatureAddress >= ulAddress) && (ulSignatureAddress < (ulAddress + m_stReprogInfo.ulMemorySizeExpected)))
  {
    eProgBoolean = TRUE;
  }
  else
  {
    eProgBoolean = FALSE;
  }

  return eProgBoolean;
}

void PROG_Impl90_TransmitNRC78(void)
{
#if (PROG_SIGNFIN_SENDFRP == STD_OFF)
    /*Send NRC78 response*/
    PROG_SendNRC78();
#else
    /* Post Event in state machine */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_TX_CONF);
#endif
}

void PROG_Impl90_Entry_SignatureCheck(void)
{
    u32 ulVSAddress;
    u32 ulSignatureAddress;
    u32 ulVSSize;

    /* Get Address of VS */
    (void)PROG_GetVSAddress(&ulVSAddress);
    (void)PROG_GetSignatureAddress(&ulSignatureAddress);


    ulVSSize = m_ulVSWrittenData;

    /* Initialize the status of check memory to "Failed" */
    m_ubValidateMemoryStatus = PROG_WRONG_SIGNATURE;

    /* Start Address */
    m_aubDataToBeSigned[0] = (u8)((ulVSAddress & 0xFF000000U) >> 24U);
    m_aubDataToBeSigned[1] = (u8)((ulVSAddress & 0x00FF0000U) >> 16U);
    m_aubDataToBeSigned[2] = (u8)((ulVSAddress & 0x0000FF00U) >> 8U);
    m_aubDataToBeSigned[3] = (u8)(ulVSAddress & 0x000000FFU);

    /* Length */
    m_aubDataToBeSigned[4] = (u8)((ulVSSize & 0xFF000000U) >> 24U);
    m_aubDataToBeSigned[5] = (u8)((ulVSSize & 0x00FF0000U) >> 16U);
    m_aubDataToBeSigned[6] = (u8)((ulVSSize & 0x0000FF00U) >> 8U);
    m_aubDataToBeSigned[7] = (u8)(ulVSSize & 0x000000FFU);

    /* Read VS */
    (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVSAddress,ulVSSize, &m_aubDataToBeSigned[8]);
    /*Read Signature*/
    (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulSignatureAddress, PROG_SIGNATURE_SIZE, &m_aubExpectedSignature[0]);

    /* One step signature calculation on the actual data of VS (without padding) */
    PROG_GetPublicKey(&m_stProgAsymPublicKey);
    (void)PROG_VerifySignature
    (
        &m_stProgAsymPublicKey,
        m_aubDataToBeSigned,
        ulVSSize + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN,
        &m_aubExpectedSignature[0]
    );
}


NCS_PRI_VAR void PROG_GetVSAddress(u32 * pulVSAddress)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_90)
  /* Read VS from Memory  */
  /* SBL is always in the RAM */
  *pulVSAddress = PROG_SBL_VS_START_ADDRESS;
#else
       /* SBL variant */
       /* Get Address of VS  */
       (void)Prog_GetLogicalBlockVerifStructure(m_stCurrentSegment.ubSegmentId, pulVSAddress);
#endif
}

NCS_PRI_VAR void PROG_GetSignatureAddress(u32 * pulSignatureAddress)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_90)
  /* Read VS from Memory  */
  /* SBL is always in the RAM */
  *pulSignatureAddress = PROG_SBL_VS_START_ADDRESS - PROG_SIGNATURE_OFFSET;
#else
       /* SBL variant */
       /* Get Address of Signature  */
       (void)Prog_GetLogicalBlockSignature(m_stCurrentSegment.ubSegmentId, pulSignatureAddress);
#endif
}


NCS_PRI_VAR void PROG_GetDigestFromVS(u16 uwDataBlockIndex,u8*aubDigest)
{
  u8 aubData[PROG_DIGEST_LENGTH];
  u8 ubIdx;

  u32 ulVSAddress;

  PROG_GetVSAddress(&ulVSAddress);

   ulVSAddress += PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET + PROG_DATA_BLOCKS_HASH_OFFSET + (PROG_DATA_BLOCKS_USEFUL_DATA_SIZE * (u32)uwDataBlockIndex);

   /* Read hash value from memory */

  (void)PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVSAddress, PROG_DIGEST_LENGTH, aubData);

  /* Hash value */
  for(ubIdx = 0; ubIdx <PROG_DIGEST_LENGTH; ubIdx++)
  {
    aubDigest[ubIdx] = aubData[ubIdx];

  }

}

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
NCS_PRI_VAR void PROG_GetDataBlockNbrFromVS(u16 *uwBlockNumber)
{
  u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
  u32 ulVSAddress;
  tProgStatus ubProgStatus = PROG_E_OK;

   /* SBL variant */
   /* Get Address of VS  */
   (void)Prog_GetLogicalBlockVerifStructure(m_stCurrentSegment.ubSegmentId, &ulVSAddress);
   ulVSAddress += PROG_DATA_BLOCKS_COUNT_MSB_OFFSET;
  ubProgStatus = PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVSAddress, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);

   if(PROG_E_OK == ubProgStatus)
   {
      (*uwBlockNumber)  = (u16)((u16)(aubData[0]) << 8);
      (*uwBlockNumber) |= (u16)(aubData[1]);
   }
   else
   {
       m_ubValidateMemoryStatus = PROG_VS_MEMORY_READERROR;
   }
}

NCS_PRI_VAR void PROG_GetVSVersion(u16 *uwVersion)
{
  u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
  u32 ulVSAddress;
  tProgStatus ubProgStatus = PROG_E_OK;

   /* SBL variant */
   (void)Prog_GetLogicalBlockVerifStructure(m_stCurrentSegment.ubSegmentId, &ulVSAddress);
  ubProgStatus = PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVSAddress, PROG_VS_VERSION_SIZE, aubData);

  if(PROG_E_OK == ubProgStatus)
  {
      (*uwVersion)  = (u16)((u16)(aubData[0]) << 8);
      (*uwVersion) |= (u16)(aubData[1]);
  }
  else
  {
       m_ubValidateMemoryStatus = PROG_VS_MEMORY_READERROR;
  }
}
#endif

NCS_PRI_VAR tProgStatus PROG_VerifyVSVersionAndLength(void)
{
  u16 uwDataBlockNbr = 0U;
  /* value different than 0 because the current version ID is already 0 */
  u16 uwVSVersion = 0xEBEBU;
  tProgStatus ubProgStatus = PROG_E_OK;
  u32 ulExpectedLength;
#if (PROG_IMPL_VARIANT == PROG_IMPL_90)
  u8 aubData[2];
#endif

  /* Check Version */
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
  /* SBL variant */
    PROG_GetVSVersion(&uwVSVersion);
#else
  ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VS_START_ADDRESS, PROG_VS_VERSION_SIZE, aubData);
  if(PROG_E_OK == ubProgStatus)
  {
    uwVSVersion = (u16)((u16)aubData[0] << 8);
    uwVSVersion |= (u16)aubData[1];
  }
  else
  {
    m_ubValidateMemoryStatus = PROG_VS_MEMORY_READERROR;
  }

#endif
  if(PROG_E_OK == ubProgStatus)
  {
    if(uwVSVersion != (u16)PROG_EXPECTED_VS_VERSION)
    {
      ubProgStatus = PROG_E_NOT_OK;
      m_ubValidateMemoryStatus = PROG_INVALID_VS_VERSION;
    }
  }

  /* Version is ok, check length  */
  if(PROG_E_OK == ubProgStatus)
  {
    /* Check Length */
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    /* SBL variant */
      PROG_GetDataBlockNbrFromVS(&uwDataBlockNbr);
#else
    ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VS_START_ADDRESS + PROG_DATA_BLOCKS_COUNT_MSB_OFFSET, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);
    if(PROG_E_OK == ubProgStatus)
    {
      uwDataBlockNbr = (u16)((u16)aubData[0] << 8);
      uwDataBlockNbr |= (u16)aubData[1];
    }
    else
    {
      m_ubValidateMemoryStatus = PROG_VS_MEMORY_READERROR;
    }
    if(PROG_E_OK == ubProgStatus)
#endif
    {
      ulExpectedLength = PROG_VS_VERSION_SIZE + PROG_DATA_BLOCKS_COUNT_SIZE + ((u32)uwDataBlockNbr*PROG_DATA_BLOCKS_USEFUL_DATA_SIZE);

      if(m_ulVSWrittenData != ulExpectedLength)
      {
        ubProgStatus = PROG_E_NOT_OK;
        m_ubValidateMemoryStatus = PROG_INVALID_VS_BLKNBR;
      }
    }
  }

  return ubProgStatus;
}

NCS_PRI_VAR tProgStatus PROG_CheckHashResults(void)
{
   tProgStatus ubProgStatus = PROG_E_OK;
   u16 uwIdx;
   u16 uwDataBlockNbr = 0;
   u8 ubLoopIndex;
   u8 aubDigest[PROG_DIGEST_LENGTH];
   tProgStatus ubDataBlockStatus = PROG_E_OK;

#if (PROG_IMPL_VARIANT == PROG_IMPL_90)
   u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
   /* SBL variant */
    PROG_GetDataBlockNbrFromVS(&uwDataBlockNbr);

#else
   ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VS_START_ADDRESS + PROG_DATA_BLOCKS_COUNT_MSB_OFFSET, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);
   if(PROG_E_OK == ubProgStatus)
   {
     uwDataBlockNbr = (u16)((u16)aubData[0] << 8);
     uwDataBlockNbr |= (u16)aubData[1];
   }
   else
   {
     m_ubValidateMemoryStatus = PROG_VS_MEMORY_READERROR;
   }

   if(PROG_E_OK == ubProgStatus)
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_91)*/
   {
     /* Check that all data blocks are downloaded and their hash is correct */
     for(uwIdx = 0; uwIdx < uwDataBlockNbr; uwIdx++)
     {
          /*Get the current blocks Digest from VS*/
          PROG_GetDigestFromVS(uwIdx , &aubDigest[0]);

          for (ubLoopIndex = 0; ((ubLoopIndex < PROG_DIGEST_LENGTH)&&(PROG_E_OK == ubDataBlockStatus)); ubLoopIndex++)
          {
               /* Compare with stored Digest value from RTE */
               if (m_aubHashValueBlock[uwIdx].aubDigest[ubLoopIndex] != aubDigest[ubLoopIndex])
               {
                  ubDataBlockStatus = PROG_E_NOT_OK;
               }
          }
          /* update the hash status in the data block array */
          ubProgStatus |= ubDataBlockStatus;

     }

     if(PROG_E_NOT_OK == ubProgStatus)
     {
       m_ubValidateMemoryStatus = PROG_WRONG_HASH;
     }
   }

   return ubProgStatus;
}

/* ************************************************************************
 * Read DID D03F Callback to read the in use Public Key Hash.
 * When the Callback is called,it will trigger the state machine with event
 * event PROG_EVENT_REQ_PUBLIC_KEY_HASH
 * ************************************************************************
 */
tUdsStatus PROG_ReadPublicKeyHash(PduLengthType *pulLen, u8 *aubUdsData)
{
  tUdsStatus eStatus;
  /*Trigger the event to read the Public Key Hash*/
  eStatus = PROG_GenericRequest(pulLen, aubUdsData,
            PROG_HSM_PROG_EV_PROG_EVENT_REQ_PUBLIC_KEY_HASH);
  return (eStatus);
}

/* ************************************************************************
 * PROG_EntryPublicKeyHash is called from Prog State Machine.
 * First Public Key is retrieved and then it is converted into DER Format
 * Hash Start API is called to initiate the hashing mechanisms
 * ************************************************************************
 */
void PROG_EntryPublicKeyHash(void)
{
  /*call API to get the in use Public Key*/
  (void)PROG_GetPublicKey(&m_stProgAsymPublicKey);
  /*Assign the Key to DER Pointer*/
  ptrDERFormat = (const u8*)&m_stProgAsymPublicKey;
  /*Call Callback to get the Key in DER Format*/
  (void)PROG_CustomGetDERFormat(&ptrDERFormat);
  /*Call Hash Start API to initiate the Hash calculation*/
  (void)PROG_ComputeHashStart(PROG_CSM_HASH_ID,NULL_PTR,0U,NULL_PTR);

}

/* ************************************************************************
 * PROG_DoPublicKeyHash is called from Prog State Machine.
 * Hash Do is called once Hash Initiaition is completed and
 * Once Hash Do is completed successfully,Hash Finish is called to get the
 * Computed Hash.If there is failure during Hash Calculation,NRC 22 is returned
 * ************************************************************************
 */
void PROG_DoPublicKeyHash(void)
{
  /*Variable to track the Crypto State Machine*/
  tProgCryState eCryptoState;
  /*Variable to know the status of Crypto Operation*/
  tProgStatus   eCryptoStatus;
  /*Call the state machine and status API to know the current status*/
  eCryptoState  = PROG_GetCryptoState();
  eCryptoStatus = PROG_GetCryptoStatus();

  if(PROG_E_NOT_OK != eCryptoStatus)
  {
    /*Operation has either completed successfully or it is in progress*/
    if(PROG_HASH_END == eCryptoState)
    {
      /*Do operation is completed.Call the Finish Operation*/
      PROG_ComputeHashFinish(&m_aubComputedDerKey[0]);
    }
    else if(PROG_HASH_START_END == eCryptoState)
    {
      /*Hash Initiation operation is completed.Call the Do operation*/
      PROG_ComputeHashUpdate(ptrDERFormat, PROG_KEY_DER_LENGTH);
    }
    else
    {
      /* Operation in Progress.do nothing */
    }
  }
  else
  {
    /* go to CRYPTO_FAILURE state */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    /* Send negative response "Conditions Not Correct" */
    UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_22);
  }


}

/* ************************************************************************
 * PROG_FinishPublicKeyHash is called from Prog State Machine.
 * Data is copied to tester buffer and response is sent
 * ************************************************************************
 */
void PROG_FinishPublicKeyHash(void)
{
  u8 ubLoopIndex = 0U;

  for (ubLoopIndex = 0U; (ubLoopIndex < PROG_DIGEST_LENGTH); ubLoopIndex++)
  {
    /*Copy the Hash buffer to Tester Buffer for length 32 bytes*/
    m_stDiagMessageInfo.pubTxData[ubLoopIndex+3U] =   m_aubComputedDerKey[ubLoopIndex];

  }
  /*Update the total length of Response*/
  m_stDiagMessageInfo.ulLength      = PROG_DIGEST_LENGTH + 3U;

  /*Call Callback to copy the hash into location to be accessed in Applicative SW*/
  (void)Prog_CustomReadPublicKeyHash(&m_aubComputedDerKey[0]);

  /* Send positive response with in use Public Key Hash Computed */
  UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, UDS_ACK);

}

/*-----------------------------{PROG_PBL_RD_Check}------------------------------*/
tProgStatus PROG_PBL_RD_Check(void)
{
    tProgStatus eProgStatus;
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    eProgStatus = PROG_E_NOT_OK;
    PROG_Send_NRC(UDS_NRC_31);
#else
    eProgStatus = PROG_RD_Check();
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_91)*/
    return eProgStatus;
}
/*-----------------------------{end PROG_PBL_RD_Check}--------------------------*/

/*-----------------------------{PROG_FailedPublicKeyHash}------------------------------*/
void PROG_FailedPublicKeyHash(void)
{

    /* Send negative response "Conditions Not Correct" */
    UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_22);
}
/*-----------------------------{end PROG_FailedPublicKeyHash}--------------------------*/
/* Deviation CERTC-1 */
void PROG_Impl90_Entry_UpdateSwitchingKeys_ValidateHeader(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    tProgStatus ubProgStatus = PROG_E_OK;

    /* Stores the status of the routine */
    u8 ubProgSwitchingKeyRoutineResult = PROG_UPDATESWITCHINGKEY_STAT_UNKNOWN;

    /* Check the request Min and Max lenght based on the Mode */
    PROG_Impl90_VerifySwitchKeyRoutineReqlength(&m_stDiagMessageInfo.pubData[0],m_stDiagMessageInfo.ulLength);

    /* Call back to verify the header */
    ubProgStatus = PROG_CustomVerifyUpdateSwitchKeyHeader(&m_stDiagMessageInfo.pubData[0],
                        (m_stDiagMessageInfo.ulLength), &ubProgSwitchingKeyRoutineResult);

    if(ubProgStatus == PROG_E_OK)
    {
        if(m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_MESSAGESTAT_POS] == PROG_SWITCH_TO_PRODUCTION_KEY)
        {
            if(m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_KEYINDEX_POS] == PROG_USE_TOKEN_KEY_SIGN)
            {
                /* Switch to Production Key and Mode set to Production */
                ubProgStatus = PROG_CustomUpdateActiveKeyStatAndMode(PROG_USE_PRODPUB_KEY, PROG_SWITCH_TO_PRODUCTION_KEY, &ubProgSwitchingKeyRoutineResult);
                if(ubProgStatus == PROG_E_OK)
                {
                    /* emit event PROG_HSM_PROG_EV_PROG_EVENT_FINISHED */
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
                }
                else
                {
                    /* emit event PROG_EVENT_FAILED */
                    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                    /* update the error code in Global structure */
                    stUpdateSwitchKeyData.RoutineResult = ubProgSwitchingKeyRoutineResult;
                }
            }
            else
            {
                /* emit event PROG_EVENT_FAILED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                /* update the error code in Global structure */
                stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_SYNCHP_DOESNOT_MATCH;
            }
        }
        else
        {
            /* emit event PROG_HSM_PROG_EV_PROG_EVENT_UPDATE_SWITCHING_KEY_SIGNATURE_CHECK */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_UPDATE_SWITCHING_KEY_SIGNATURE_CHECK);
        }
    }
    else
    {
        /* emit event PROG_EVENT_FAILED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* update the error code in Global structure */
        stUpdateSwitchKeyData.RoutineResult = ubProgSwitchingKeyRoutineResult;
    }
#endif
}



void PROG_Impl90_Entry_Routine_SignatureCheck(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    u16 m_uwSignatureIndex;

    /* Stores the length of routine info SID + Info + RID */
    u8 m_ubRotuineInfo;

    /* Initialize the status of Routine signature to "Failed" */
    /* m_ubValidateKeyRoutineStatus = PROG_WRONG_SIGNATURE; */
    m_uwSignatureIndex = 0u;
    m_ubRotuineInfo = 4u;

    /* One step signature calculation on the actual data of VS (without padding) */
    /* we need to calculate the signature for Routine data (Header + Payload) and compare it wit SynchP */
    if( (m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_MESSAGESTAT_POS] >= PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_COMMANDED_EXIT) &&
                (m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_MESSAGESTAT_POS] <= PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_N_IGN) )
    {
        /* Check the key Index is proper or not */
        if(m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_KEYINDEX_POS] == PROG_USE_TOKEN_KEY_SIGN)
        {
            /* Read the Token Public key */
            PROG_GetPublicKeyToValidateKeyRoutine(&m_stProgAsymPublicKey, PROG_USE_TOKEN_KEY_SIGN);
            m_uwSignatureIndex = (u16)((u16)PROG_SWITCHINGKEY_HEADER_SIZE + (u16)PROG_SWITCHINGKEY_PAYLOAD_WITHOUTUPDATEKEYS + (u16)m_ubRotuineInfo);
            (void)PROG_VerifySignature
            (
                &m_stProgAsymPublicKey,
                &m_stDiagMessageInfo.pubData[4],
                (u32)((u32)m_uwSignatureIndex - (u32)m_ubRotuineInfo),
                &m_stDiagMessageInfo.pubData[m_uwSignatureIndex]
            );
        }
        else
        {
            /* emit event PROG_EVENT_FAILED */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            /* update the error code in Global structure */
            stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_TOKN_OK_PASSED_APPL;
        }
    }
    else if(m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_MESSAGESTAT_POS] == PROG_UPDATE_PUBLIC_KEYS)
    {
        /* Check the key Index is proper or not */
        if(m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_KEYINDEX_POS] == PROG_USE_SECRET_KEY_SIGN)
        {
            /* Read the Secret Public key */
            PROG_GetPublicKeyToValidateKeyRoutine(&m_stProgAsymPublicKey, PROG_USE_SECRET_KEY_SIGN);
            m_uwSignatureIndex = (u16)((u16)PROG_SWITCHINGKEY_HEADER_SIZE + (u16)PROG_SWITCHINGKEY_PAYLOAD_WITHUPDATEKEYS + (u16)m_ubRotuineInfo);
            (void)PROG_VerifySignature
            (
                &m_stProgAsymPublicKey,
                &m_stDiagMessageInfo.pubData[4],
                (u32)((u32)m_uwSignatureIndex - (u32)m_ubRotuineInfo),
                &m_stDiagMessageInfo.pubData[m_uwSignatureIndex]
            );
        }
        else
        {
            /* emit event PROG_EVENT_FAILED */
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            /* update the error code in Global structure */
            stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_TOKN_OK_PASSED_APPL;
        }
    }
    else
    {
         /* emit event PROG_EVENT_FAILED */
         PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
         /* update the Mode not within the range */
         stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_WRONG_SIGNATURE;
    }
#endif
}

/* Deviation CERTC-1 */
void PROG_Impl90_Entry_UpdateSwitchingKey_PerformAction(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    tProgStatus eProgStatus = PROG_E_OK;
    u8 ubProgSwitchingKeyRoutineResult;

    /* Stores the header status the routine */
    u8 ubProgRCMsgStat    = PROG_UPDATESWITCHINGKEY_STAT_UNKNOWN;

    /* Stores the header status the routine */
    ubProgSwitchingKeyRoutineResult = PROG_UPDATESWITCHINGKEY_STAT_UNKNOWN;
    /*store the Mode/Message status to in local variable */
    ubProgRCMsgStat = stUpdateSwitchKeyData.ubMsgStat;

    /* Extract Routine Data */
    eProgStatus = PROG_ExtractKeyUpdateRoutineData(&m_stDiagMessageInfo.pubData[0],
            (m_stDiagMessageInfo.ulLength), &stUpdateSwitchKeyData, &ubProgSwitchingKeyRoutineResult);

    if(eProgStatus == PROG_E_OK)
    {
        /* Check the request is to update the Keys */
        if(ubProgRCMsgStat == PROG_UPDATE_PUBLIC_KEYS)
        {
            eProgStatus = PROG_CustomUpdateProductionKey(&stUpdateSwitchKeyData.ubDevPublicKey[0], &ubProgSwitchingKeyRoutineResult);
            eProgStatus = PROG_CustomUpdateDevelopmentKey(&stUpdateSwitchKeyData.ubProdPublicKey[0], &ubProgSwitchingKeyRoutineResult);
            eProgStatus = PROG_CustomUpdateTokenKey(&stUpdateSwitchKeyData.ubTokenPublicKey[0], &ubProgSwitchingKeyRoutineResult);

            if(eProgStatus == PROG_E_OK)
            {
                /* emit event PROG_HSM_PROG_EV_PROG_EVENT_FINISHED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
            }
            else
            {
                /* emit event PROG_EVENT_FAILED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                /* update the error code in Global structure */
                stUpdateSwitchKeyData.RoutineResult = ubProgSwitchingKeyRoutineResult;
            }
        }
        else
        {
            /* Switch to Development Key and  update the Mode*/
            eProgStatus = PROG_CustomUpdateActiveKeyStatAndMode(PROG_USE_DEVPUB_KEY, ubProgRCMsgStat, &ubProgSwitchingKeyRoutineResult);
            if(eProgStatus == PROG_E_OK)
            {
                /* emit event PROG_HSM_PROG_EV_PROG_EVENT_FINISHED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
            }
            else
            {
                /* emit event PROG_EVENT_FAILED */
                PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                /* update the error code in Global structure */
                stUpdateSwitchKeyData.RoutineResult = ubProgSwitchingKeyRoutineResult;
            }
        }

    }
    else
    {
        /* emit event PROG_EVENT_FAILED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* update the error code in Global structure */
        stUpdateSwitchKeyData.RoutineResult = ubProgSwitchingKeyRoutineResult;
    }
#endif
}


#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
tProgStatus PROG_ExtractKeyUpdateRoutineData(const u8 * pubUdsData,
        PduLengthType ulDataLength, tstUpdateSwitchKeyDataType* pstUpdateSwitchKeyData, u8 *pubProgSwitchingKeyRoutineResult)
{
    tProgStatus eProgStatus = PROG_E_OK;

    u16 LoopIndex = 0;

    if( (pubUdsData[PROG_KEYSWITCH_MESSAGESTAT_POS] <= PROG_UPDATE_PUBLIC_KEYS) )
    {
        /* updates the message status */
        pstUpdateSwitchKeyData -> ubMsgStat = pubUdsData[PROG_KEYSWITCH_MESSAGESTAT_POS];


        if( (pubUdsData[PROG_KEYSWITCH_KEYINDEX_POS] == 0U) ||
            (pubUdsData[PROG_KEYSWITCH_KEYINDEX_POS] == 1U) )
        {
            pstUpdateSwitchKeyData->ubKeyIndex = pubUdsData[PROG_KEYSWITCH_KEYINDEX_POS];

            /* Copy the Key Data */
            if(pstUpdateSwitchKeyData -> ubMsgStat == PROG_UPDATE_PUBLIC_KEYS)
            {
                /* Copy the Dev Public Key */
                for(LoopIndex=0;LoopIndex<PROG_DEVPUBLICKEY_SIZE ;LoopIndex++)
                {
                    pstUpdateSwitchKeyData->ubDevPublicKey[LoopIndex] =  pubUdsData[PROG_DEVPUBLICKEY_POS + LoopIndex];
                }

                /* Copy the Prod Public Key */
                for(LoopIndex=0;LoopIndex<PROG_PRODPUBLICKEY_SIZE ;LoopIndex++)
                {
                    pstUpdateSwitchKeyData->ubProdPublicKey[LoopIndex] =  pubUdsData[PROG_PRODPUBLICKEY_POS + LoopIndex];
                }

                /* Copy the Token Public Key */
                for(LoopIndex=0;LoopIndex<PROG_TOKENPUBLICKEY_SIZE ;LoopIndex++)
                {
                    pstUpdateSwitchKeyData->ubTokenPublicKey[LoopIndex] =  pubUdsData[PROG_TOKENPUBLICKEY_POS + LoopIndex];
                }
            }
            else
            {
                eProgStatus = PROG_E_OK;
            }
        }
        else
        {
            eProgStatus = PROG_E_NOT_OK;
            *pubProgSwitchingKeyRoutineResult = PROG_SWITCHINGKEY_WRONG_SIGNATURE;
        }
    }
    else
    {
        eProgStatus = PROG_E_NOT_OK;
        *pubProgSwitchingKeyRoutineResult = PROG_SWITCHINGKEY_WRONG_SIGNATURE;
    }
    OSC_PARAM_UNUSED(ulDataLength);

    return eProgStatus;
}
#endif

/* Deviation CERTC-1 */
void PROG_Impl90_Entry_UpdateSwitchingKeyFinished(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    u8 eProg_UpdateSwitchRC_Result  = 0;
    tProgStatus eProgStatus = PROG_E_OK;

    /* copy the data of Routine status from Global variable to eProg_UpdateSwitchRC_Result */

    /* call-back to Copy the Routine request as the processing was success */
    eProgStatus = PROG_CustomCopySwitchingKeyRequest(&m_stDiagMessageInfo.pubData[0], (m_stDiagMessageInfo.ulLength), &eProg_UpdateSwitchRC_Result);
    if(eProgStatus == PROG_E_OK)
    {
        /* eProg_UpdateSwitchRC_Result = (u8) stUpdateSwitchKeyData.RoutineResult; */
        eProg_UpdateSwitchRC_Result = PROG_SWITCHINGKEY_TOKEN_APPLIED;
        /* Update the Tx buffer with response */
        m_stDiagMessageInfo.pubTxData[4]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);

        m_stDiagMessageInfo.pubTxData[5]                = (u8) eProg_UpdateSwitchRC_Result;
        m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
        m_stDiagMessageInfo.ulLength = 0x06;
        /* Send response */
        UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
    }
    else
    {
        /* emit event PROG_EVENT_FAILED */
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
        /* update the error code in Global structure */
        stUpdateSwitchKeyData.RoutineResult = eProg_UpdateSwitchRC_Result;
    }


#endif
}

/* Deviation CERTC-1 */
void PROG_Impl90_Entry_UpdateSwitchingKeyFailed(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    u8 eProg_UpdateSwitchRC_Result  = 0;

    /* copy the data of Routine status from Global variable to eProg_UpdateSwitchRC_Result */
    eProg_UpdateSwitchRC_Result = (u8) stUpdateSwitchKeyData.RoutineResult;

    /* Update the status into the diag buffer */
    m_stDiagMessageInfo.pubTxData[4]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
    m_stDiagMessageInfo.pubTxData[5]                = (u8) eProg_UpdateSwitchRC_Result;
    m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;
    m_stDiagMessageInfo.ulLength = 0x06;
    /* Send response */
    UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);
#endif
}


tUdsStatus PROG_ReadLastSucessSwitchingRCRRequest(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;

    if((pulLen != NULL_PTR) && (aubUdsData != NULL_PTR))
    {
          eStatus = UDS_ACK;
          *pulLen = PROG_SWITCHING_SIZEOF_D071_RDID + 3u;
          Prog_CustomReadLastSuccessSwitchingKeyRCReqest(&aubUdsData[3]);
    }
    else
    {
        eStatus = UDS_NRC_31;
    }

    return (eStatus);
}


#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
void PROG_SetErrorCodeSwitchingKeyFailure(void)
{

    u8 ubSwitchingKeyMode;

    ubSwitchingKeyMode = m_stDiagMessageInfo.pubData[PROG_KEYSWITCH_MESSAGESTAT_POS];
    if(ubSwitchingKeyMode == PROG_UPDATE_PUBLIC_KEYS)
    {
        stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_WRONG_PAYLOAD_SIGNATURE_ROTATION_ONLY;
    }
    else
    {
        stUpdateSwitchKeyData.RoutineResult = PROG_SWITCHINGKEY_WRONG_SIGNATURE;
    }
}
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_91) */


#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
void PROG_Impl90_VerifySwitchKeyRoutineReqlength(const u8 * pubUdsData, const PduLengthType ulDataLength)
{
    /* Check for Min length */
    if((pubUdsData[PROG_KEYSWITCH_MESSAGESTAT_POS] <= PROG_SWITCH_DEVELOPMENT_KEY_UNTILL_N_IGN))
    {
        if(ulDataLength != PROG_SWITCHINGKEY_RC_MINLEN)
        {
            /* Expected length does not match - NRC_13 */
            UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_13);
        }
    }
    /* Check for Max length */
    else if(pubUdsData[PROG_KEYSWITCH_MESSAGESTAT_POS] == PROG_UPDATE_PUBLIC_KEYS)
    {
        if(ulDataLength != PROG_SWITCHINGKEY_RC_MAXLEN)
        {
            /* Expected length does not match - NRC_13 */
            UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_13);
        }
    }
    else
    {
        /* Message status verification is done as part of header verification, we can skip operation here */
    }
}
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_91) */
/* Deviation CERTC-1 */
NCS_PRI_VAR void PROG_GetLogicalBlockVerifStructureLength(u32* pulVSLength)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_91)
    u32 ulVSAddress;

    /* Get Address of VS */
    (void)PROG_GetVSAddress(&ulVSAddress);
    /* SBL variant */
    /* Get Length of VS */
    if (ulVSAddress == m_stCurrentSegment.ulStartAddress)
    {
        /* If only VS download request is received */
        *pulVSLength = m_stReprogInfo.ulMemorySizeExpected;
    }
    else
    {
        /* If combined VS and Signature download request is received */
        *pulVSLength = (u32)(m_stReprogInfo.ulMemorySizeExpected - PROG_SIGNATURE_SIZE);
    }
#else
    /* Read VS from Configuration  */
    *pulVSLength = PROG_SBL_VS_LENGTH;
#endif
}

#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91) */
