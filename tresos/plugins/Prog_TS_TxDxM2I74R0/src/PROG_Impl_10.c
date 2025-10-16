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
/*%%   _____________________________   %%  \file PROG_Impl_10.c                  */
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
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* check memory routine status */
u8 m_ubCheckMemoryStatus;
/* Number of check memory failed requests */
u8 m_ubFailedCheckMemoryCount;
/* boolean to indicate whether the verification table of the software part is downloaded or not */
tProgBoolean m_ubVerificationTablePresent;
/* For Blank check */
u32 m_ulBlankCheckLastAddress;
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
/* validity variable to be checked before the activation of the SBL*/
tProgStatus m_ubSblVerficationStatus;
#else
/* software part ID that is being downloaded */
u8 m_ubSoftwarePartID;
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
#define PROG_DATA_BLOCKS_LENGTH_OFFSET      4U
#define PROG_DATA_BLOCKS_HASH_OFFSET        8U
#define PROG_DATA_BLOCKS_USEFUL_DATA_SIZE   40U
#define PROG_DATA_BLOCKS_COUNT_SIZE         2U
#define PROG_VBT_FORMAT_ID_SIZE             2U
#define PROG_EXPECTED_VBT_FORMAT_ID         0x0000U
#define PROG_SOFTWARE_PART_FINISHED         0xFFU
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/* Hash comparison status for each data block */
NCS_PRI_VAR tProgStatus m_aubHashComparisonStatus[PROG_MAX_RD_PER_BLOCK];
/* Data block block which is being downloaded */
NCS_PRI_VAR u16 m_uwCurrentDataBlock;
/* Digest compuated by crypto for the data block */
NCS_PRI_VAR u8 m_aubComputedDigest[PROG_DIGEST_LENGTH];
/* Count of bytes of data not written but still needs to be included in hash calculation */
NCS_PRI_VAR u32 m_ulRemainingUnwrittenData;
/* Added 8 to include start address and length */
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
NCS_PRI_VAR u8 m_aubDataToBeSigned[PROG_SBL_VBT_LENGTH + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN];
#else
NCS_PRI_VAR u8 m_aubDataToBeSigned[(PROG_MAX_RD_PER_BLOCK*PROG_DATA_BLOCKS_USEFUL_DATA_SIZE) + 4U + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN];
/* used to ensure the order of data blocks download within a software part */
NCS_PRI_VAR tProgAddressType m_ulLastWrittenAddress;
#endif
/* This variable will hold the value of the actual length of the data written for the VBT, to be checked later with the expected length of VBT */
u32 m_ulVBTWrittenData;
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/** \brief extracts the data block digest from the verification block table
 **
 ** \param[out] u8* digest values of the data block
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetDigestFromVBT(u16 uwDataBlockIndex,u8*aubDigest);

/** \brief extracts the data block length from the verification block table
 **
 ** \param[out] u32* length of the data block
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetLengthFromVBT(u16 uwDataBlockIndex,u32*ulLength);

/** \brief extracts the data block start address from the verification block table
 **
 ** \param[out] u32* start address of the data block
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetStartAddressFromVBT(u16 uwDataBlockIndex,u32*ulStartAddress);

/** \brief provide the verification block table length
 **
 ** \param[out] pulVBTLength length of VBT
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetVBTLength(u32* pulVBTLength);

/** \brief provide the verification block table address
 **
 ** \param[out] u32* address of VBT
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetVBTAddress(u32 * pulVBTAddress);

/** \brief check that the 'not-downloaded' areas are erased or set to a known value (for SBL)
 **
 ** \param[in] void
 **
 ** \return tProgStatus status of the blank check
 **/
NCS_PRI_VAR tProgStatus PROG_CheckNonProgrammedAreas(void);

/** \brief Do the check that the 'not-downloaded' areas are erased or set to a known value (for SBL)
 **
 ** \param[in] u8 ubSegmentId id of the segment to check within the block
 **
 ** \param[in] u32 ulSegmentStartAddr address of the segment to check within the block
 **
 ** \param[in] u32 ulSegmentSize size of the segment to check within the block
 **
 ** \return void
 **/
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR void PROG_BlankCheck(u16 ubSegmentId, u32 ulSegmentStartAddr);
#else
NCS_PRI_VAR void PROG_BlankCheck(u16 ubSegmentId, u32 ulSegmentStartAddr, u32 ulSegmentSize);
#endif
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
/** \brief Do the check that the 'not-downloaded' areas are erased or set to a known value (for SBL)
 **
 ** \return tProgStatus
 **/
NCS_PRI_VAR tProgStatus PROG_CheckESSCoverageOfProgrammableMemory(void);
/** \brief extracts the data block number from the verification block table
 **
 ** \param[in] void
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetDataBlockNbrFromVBT(u16 *uwBlockNumber);
#endif

/** \brief checks on the format and the length of the verification block table
 **
 ** \param[in] void
 **
 ** \return tProgStatus
 **/
NCS_PRI_VAR tProgStatus PROG_VerifyVBTFormatAndLength(void);

/** \brief checks on the array containing the results of hash comparison for each data block
 **
 ** \param[in] void
 **
 ** \return tProgStatus
 **/
NCS_PRI_VAR tProgStatus PROG_CheckHashResults(void);

/** \brief reads the format ID of the verification block table of the currently downloaded block
 **
 ** \param[out] u16 VBT format ID
 **
 ** \return void
 **/
NCS_PRI_VAR void PROG_GetVBTFormat(u16 *uwFormatID);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

void PROG_Init_Impl10(void)
{
  u8 ubIdx;

  for(ubIdx = 0; ubIdx < PROG_MAX_RD_PER_BLOCK; ubIdx++)
  {
    m_aubHashComparisonStatus[ubIdx] = PROG_E_NOT_OK;
  }

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
  m_ubSblVerficationStatus = PROG_E_NOT_OK;
#else
  m_ubSoftwarePartID = PROG_SOFTWARE_PART_FINISHED;
#endif

  m_ubVerificationTablePresent = FALSE;
  m_ubFailedCheckMemoryCount   = 0;
  m_ubCheckMemoryStatus        = PROG_VERIFICATION_PASSED;
  m_ulRemainingUnwrittenData   = 0;
}

void PROG_Impl10_Entry_CheckMemoryFailed(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
  tProgStatus eProgStatus;
#endif
  /* Increment count of failed check memory attempts */
  m_ubFailedCheckMemoryCount++;
  m_ubVerificationTablePresent = FALSE;

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
  eProgStatus = PROG_CustomSetDownloadVerificationSuccess(m_stCurrentSegment.ubLogicalBlockId, m_stCurrentSegment.ubSegmentId,PROG_FALSE);
  m_ubSoftwarePartID = PROG_SOFTWARE_PART_FINISHED;
  if (PROG_E_NOT_OK == eProgStatus)
  {
    m_ubCheckMemoryStatus = PROG_VALIDITY_STORAGE_FAIL;
  }
#else
  m_ubSblVerficationStatus = PROG_E_NOT_OK;
#endif
  m_stDiagMessageInfo.pubTxData[PROG_RC_CHK_MEMORY_STATUS_INDEX]                = (u8) (PROG_ROUTINE_FINISHED_OK | PROG_ROUTINE_TYPE_1);
  m_stDiagMessageInfo.pubTxData[PROG_RC_CHK_MEMORY_RESULT_INDEX]                = (u8) m_ubCheckMemoryStatus;
  m_stDiagMessageInfo.ulLength = PROG_CHK_MEMORY_RESPONSE_SIZE;
  m_stDiagMessageInfo.ubDiagStatus = UDS_ACK;

  /* Send response */
  UDS_LongRequestEnd(m_stDiagMessageInfo.ulLength, m_stDiagMessageInfo.pubTxData, m_stDiagMessageInfo.ubDiagStatus);


}

void PROG_Impl10_AdjustAddressForHash(u32*ulAddress)
{
  u32 ulStartAddress;

  PROG_GetStartAddressFromVBT(m_uwCurrentDataBlock , &ulStartAddress);
  /* The address in the RD is smaller than the one in the VBT, start the hash from the address mentioned in the VBT */
  if((*ulAddress) < ulStartAddress)
  {
    (*ulAddress) = ulStartAddress;
  }
  /* the two start addresses are the same, do not change (the case where the address in the RD  is greater than the one in VBT is rejected) */
  else
  {

  }

}

void PROG_Impl10_AdjustLengthForHash(u32*ulReadLength)
{
  u32 ulLength;

  PROG_GetLengthFromVBT(m_uwCurrentDataBlock , &ulLength);
  /* Case to protect overflow of ulReadLength*/
  if(m_stDataProgVerification.ulCnt >= ulLength)
  {
    (*ulReadLength) = 0;
  }
  /* adjust length to match the size of the VBT */
  else if( ((*ulReadLength) + m_stDataProgVerification.ulCnt) > ulLength)
  {
    (*ulReadLength) = ulLength - m_stDataProgVerification.ulCnt;
  }
  /* length is within the range */
  else
  {

  }
}

void PROG_Impl10_FinalizeHash(void)
{
  tDataBufferType m_aubHashedData[PROG_CRC_CALC_SIZE];
  u32 ulReadLength;
  u32 ulLength;

  PROG_GetLengthFromVBT(m_uwCurrentDataBlock , &ulLength);

  if(TRUE ==  m_ubVerificationTablePresent)
  {
    /* No more data to be hashed  */
    if(m_stDataProgVerification.ulCnt >= ulLength)
    {
      PROG_ComputeHashFinish(&m_aubComputedDigest[0]);
    }
    /* Hash more data (data which are not sent in TDs) */
    else
    {
      m_ulRemainingUnwrittenData = ulLength - m_stDataProgVerification.ulCnt;

      if(PROG_CRC_CALC_SIZE <= m_ulRemainingUnwrittenData)
      {
        ulReadLength = PROG_CRC_CALC_SIZE;
      }
      else
      {
        ulReadLength = m_ulRemainingUnwrittenData;
      }

      (void)PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                          PROG_MEM_OPERATION_TYPE_READ, m_stDataProgVerification.ulAdd,
                          ulReadLength,&m_aubHashedData[0]);

      PROG_ComputeHashUpdate(m_aubHashedData, ulReadLength);

      m_stDataProgVerification.ulAdd += ulReadLength;
      m_stDataProgVerification.ulCnt += ulReadLength;
    }
  }
  else
  {
    /* emit event PROG_EVENT_CRYPTO_FINISH, go to RTE finished */
    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
  }
}

void PROG_Impl10_Do_HashMoreUnwrittenData(void)
{
  tDataBufferType m_aubHashedData[PROG_CRC_CALC_SIZE];
  tProgCryState eCryptoState;
  tProgStatus eCryptoStatus;
  u32 ulReadLength;
  u32 ulLength;

  PROG_GetLengthFromVBT(m_uwCurrentDataBlock , &ulLength);

  eCryptoState = PROG_GetCryptoState();
  eCryptoStatus = PROG_GetCryptoStatus();

  if((PROG_E_OK == eCryptoStatus) &&  (PROG_HASH_END == eCryptoState))
  {
    /* No more data to be hashed  */
    if(m_stDataProgVerification.ulCnt >= ulLength)
    {
      PROG_ComputeHashFinish(&m_aubComputedDigest[0]);
    }
    /* Hash more data (data which are not sent in TDs) */
    else
    {
      m_ulRemainingUnwrittenData = ulLength - m_stDataProgVerification.ulCnt;

      if(PROG_CRC_CALC_SIZE <= m_ulRemainingUnwrittenData)
      {
        ulReadLength = PROG_CRC_CALC_SIZE;
      }
      else
      {
        ulReadLength = m_ulRemainingUnwrittenData;
      }

      (void)PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,
                          PROG_MEM_OPERATION_TYPE_READ, m_stDataProgVerification.ulAdd,
                          ulReadLength,&m_aubHashedData[0]);

      PROG_ComputeHashUpdate(m_aubHashedData, ulReadLength);

      m_stDataProgVerification.ulAdd += ulReadLength;
      m_stDataProgVerification.ulCnt += ulReadLength;
    }
  }
}

void PROG_Impl10_CompareDataBlockHash(void)
{
  u8 ubIdx;
  u8 ubLoopIndex;
  u8 aubDigest[PROG_DIGEST_LENGTH];
  tProgStatus ubDataBlockStatus = PROG_E_OK;

  PROG_GetDigestFromVBT(m_uwCurrentDataBlock , &aubDigest[0]);

  if(TRUE ==  m_ubVerificationTablePresent)
  {
      for (ubLoopIndex = 0; ((ubLoopIndex < PROG_DIGEST_LENGTH)&&(PROG_E_OK == ubDataBlockStatus)); ubLoopIndex++)
      {
           /* compare hash */
           if (m_aubComputedDigest[ubLoopIndex] != aubDigest[ubLoopIndex])
           {
               ubDataBlockStatus = PROG_E_NOT_OK;
           }
      }

      /* update the hash status in the data block array */
      m_aubHashComparisonStatus[m_uwCurrentDataBlock] = ubDataBlockStatus;
      /* Current data block is finished, move to the next data block */
      m_uwCurrentDataBlock++;
  }
  else
  {
    /* VBT is now downloaded */
    m_ubVerificationTablePresent = TRUE;

    /* reset data block index */
    m_uwCurrentDataBlock = 0;

#if (PROG_COMPRESSION_ENABLE == STD_ON)
    if (TRUE == m_stReprogInfo.ubCompRequired)
    {
        m_ulVBTWrittenData = m_stReprogInfo.ulTotalDecompDataWrite;
    }
    else
#endif /* (PROG_COMPRESSION_ENABLE == STD_ON) */
    {
        m_ulVBTWrittenData = m_stReprogInfo.ulReceivedSizeOfData;
    }

    /* VBT is now downloaded, set all hash status to not ok */
    for(ubIdx = 0; ubIdx < PROG_MAX_RD_PER_BLOCK; ubIdx++)
    {
      m_aubHashComparisonStatus[ubIdx] = PROG_E_NOT_OK;
    }
  }
}

void PROG_Impl10_CheckDataBlocksResult(void)
{
   tProgStatus ubProgStatus = PROG_E_OK;

   /* Check length and format of verification block table */
   ubProgStatus = PROG_VerifyVBTFormatAndLength();

   /* Length and format are ok */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Check if any of data blocks failed the hash test */
     ubProgStatus = PROG_CheckHashResults();
   }

   /* Hash comparison is ok */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Check that the non programmed areas are blank */
     ubProgStatus = PROG_CheckNonProgrammedAreas();
   }

   /* All non-programmed areas are blank */
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
   if(PROG_E_OK == ubProgStatus)
   {
     /* Check that ESS covers all programmable memory */
     ubProgStatus = PROG_CheckESSCoverageOfProgrammableMemory();
   }
#endif
   /* ESS covers all programmable memory */
   if(PROG_E_OK == ubProgStatus)
   {
     /* Get the result of the Certificate verification */
     ubProgStatus = PROG_CustomCheckCertificateVerification();
     if (PROG_E_NOT_OK == ubProgStatus)
     {
        m_ubCheckMemoryStatus = PROG_CERTIFICATE_FAILED;
     }
   }

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

void PROG_Impl10_GenerateMac(void)
{
#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
  PROG_SecurityComputeAppChecksum();
#else
  /* Nothing to do in case of PBL, simulate crypto event finished */
  PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#endif
}
/* Deviation CERTC-1 */
tProgBoolean PROG_Impl10_IsVerificationTableAddress(tProgAddressType ulAddress)
{
  tProgBoolean eProgBoolean;
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
  u32 ulVBTAddress;
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
  if(ulAddress == PROG_SBL_VBT_START_ADDRESS)
#else
   /* SBL variant */
   /* Address of VBT is get from ESS */
   (void)PROG_GetVBTAddress(&ulVBTAddress);
   if(ulAddress == ulVBTAddress)
#endif

  {
    eProgBoolean = TRUE;
    /* This function is called from RD context which means that a new VBT will be downloaded */
    m_ubVerificationTablePresent = FALSE;
    /* save the length to be written of VBT */
    m_ulVBTWrittenData = m_stReprogInfo.ulMemorySizeExpected;
  }
  else
  {
    eProgBoolean = FALSE;
  }

  return eProgBoolean;
}
/* Deviation CERTC-1 */
tProgBoolean PROG_Impl10_IsVerificationTablePresent(void)
{
  return m_ubVerificationTablePresent;
}

void PROG_Impl10_Entry_SignatureCheck(void)
{
    u32 ulVBTAddress;
    u32 ulVBTSize;
    u32 ulVBTLength;
    u16 uwIdx;
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    u16 uwDataBlockNbr;
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    ulVBTAddress = PROG_SBL_VBT_START_ADDRESS;
#else
    /* SBL variant */
    /* Address of VBT is get from ESS */
    (void)PROG_GetVBTAddress(&ulVBTAddress);
    /* in case of ESS assume one continuous block */
    if(0U == m_stCurrentSegment.ubLogicalBlockId)
    {
        uwDataBlockNbr = 1;
    }
    else
    {
        PROG_GetDataBlockNbrFromVBT(&uwDataBlockNbr);
    }

#endif

    PROG_GetVBTLength(&ulVBTLength);

    if(m_ulVBTWrittenData == ulVBTLength)
    {
        ulVBTSize = m_ulVBTWrittenData;

        /* Initialize the status of check memory to "passed" */
        m_ubCheckMemoryStatus = PROG_VERIFICATION_PASSED;

        /* Start Address */
        m_aubDataToBeSigned[0] = (u8)((ulVBTAddress & 0xFF000000U) >> 24U);
        m_aubDataToBeSigned[1] = (u8)((ulVBTAddress & 0x00FF0000U) >> 16U);
        m_aubDataToBeSigned[2] = (u8)((ulVBTAddress & 0x0000FF00U) >> 8U);
        m_aubDataToBeSigned[3] = (u8)(ulVBTAddress & 0x000000FFU);

        /* Length */
        m_aubDataToBeSigned[4] = (u8)((ulVBTSize & 0xFF000000U) >> 24U);
        m_aubDataToBeSigned[5] = (u8)((ulVBTSize & 0x00FF0000U) >> 16U);
        m_aubDataToBeSigned[6] = (u8)((ulVBTSize & 0x0000FF00U) >> 8U);
        m_aubDataToBeSigned[7] = (u8)(ulVBTSize & 0x000000FFU);

        /* Read VBT */
        (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress,ulVBTSize, &m_aubDataToBeSigned[8U]);

        /* One step signature calculation on the actual data of VBT (without padding) */
        PROG_GetPublicKey(&m_stProgAsymPublicKey);

        for(uwIdx = 0U; (uwIdx < PROG_SIGNATURE_LENGTH); uwIdx++)
        {
            /* Copy the signature into global varible to use whenever needed */
            m_aubExpectedSignature[uwIdx] = m_stDiagMessageInfo.pubData[PROG_RC_CHK_MEMORY_SIGNATURE_INDEX + uwIdx];
        }

        (void)PROG_VerifySignature
        (
            &m_stProgAsymPublicKey,
            m_aubDataToBeSigned,
            ulVBTSize + PROG_ERASE_ADDR_LEN + PROG_ERASE_SIZE_LEN,
            &m_aubExpectedSignature[0]
        );

    }
    else
    {
        /* Send response */
        UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_31);
    }

}

tProgStatus PROG_Impl10_ValidateDataBlockAddress(tProgAddressType ulAddress)
{
  tProgStatus eProgStatus = PROG_E_OK;
  u32 ulStartAddressInVBT;

  if(TRUE == m_ubVerificationTablePresent)
  {
    PROG_GetStartAddressFromVBT(m_uwCurrentDataBlock,&ulStartAddressInVBT);
    /* the hash area starts before the written area (this case is rejected because
      it will complicate the on fly hash calculation */
    if(ulStartAddressInVBT < ulAddress)
    {
      eProgStatus = PROG_E_NOT_OK;
      /* Send negative response NRC31 */
      m_stDiagMessageInfo.ubDiagStatus = UDS_NRC_31;
    }
  }

  return eProgStatus;
}

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
tProgStatus PROG_ExtractEraseParameters_Impl11(tSegmentType * pstSegment)
{

    tProgStatus eESSStatus;

    tProgStatus eProgStatus;
    u8 ubBlockNbr;
    u32 ulBlockAddr;
    u32 ulBlockLength;
    u8 ubBlockId;
    u8 ubLoopIndex;
#if (PROG_ERASE_CHECK_TYPE == PROG_BLOCK_ERASE_CHECK)
    tProgEraseStatus eEraseStatus;
#endif

    eProgStatus = PROG_E_OK;

    /* ESS Management */
    /* Identify if it is ESS block that shall be erased */
    if (stConfigSegment[pstSegment->ubSegmentId].ePartitionType == PROG_ESS_PARTITION)
    {
        /* ESS shall be erased => All ECU memory shall be erased */
#if (PROG_ERASE_CHECK_TYPE == PROG_BLOCK_ERASE_CHECK)
        /* Check if logical block is already erased, index 0 is reserved for ESS */
        eEraseStatus = PROG_CustomGetEraseStatus(0U);

        if(PROG_E_ERASED == eEraseStatus)
        {
            pstSegment->ubLogicalBlockId = 0U;
            eProgStatus = PROG_E_BYPASS;
        }
        else
#endif /*(PROG_ERASE_CHECK_TYPE == PROG_BLOCK_ERASE_CHECK)*/
        {
            /* Construct Segment Structure (Address)*/
            pstSegment->ulStartAddress = stConfigSegment[0U].ulEraseStartAddress;
            pstSegment->ubLogicalBlockId = 0U;

            /* Construct Segment Structure (Size)*/
            pstSegment->ulSize = (stConfigSegment[PROG_SEGMENT_NB - 1U].ulEraseEndAddress -
                                stConfigSegment[0U].ulEraseStartAddress) + 1U;
            pstSegment->ubSegmentNbr = stCfgBlock[0U].ubSegmentNbr;
        }
    }
    else
    {
        /* Not ESS memory shall be erased */
        /* Check if ESS is present in memory and valid */
        eESSStatus = Prog_GetEssValidityStatus();
        if (PROG_E_OK == eESSStatus)
        {
            /* Find if memory range to erase is defined in ESS */
            eESSStatus = Prog_GetEssLogicalBlockNbr(&ubBlockNbr);
            if (PROG_E_OK == eESSStatus)
            {
                ubBlockId = 0xFFU;
                for (ubLoopIndex = 0U; ((ubLoopIndex < ubBlockNbr) && (0xFFU == ubBlockId)); ubLoopIndex++)
                {
                    eESSStatus = Prog_GetEssLogicalBlockStartAddr(ubLoopIndex, &ulBlockAddr);
                    if ((PROG_E_OK == eESSStatus) && (pstSegment->ulStartAddress >= ulBlockAddr))
                    {
                        eESSStatus = Prog_GetEssLogicalBlockLength(ubLoopIndex, &ulBlockLength);
                        if ((PROG_E_OK == eESSStatus) && ((pstSegment->ulStartAddress + pstSegment->ulSize) <= (ulBlockAddr + ulBlockLength)))
                        {
                            /* Matching block has been found */
                            ubBlockId = ubLoopIndex;
                        }
                    }
                }
                if (0xFFU == ubBlockId)
                {
                    /* No matching block found in ESS, send negative response */
                    eProgStatus = PROG_E_NOT_OK;
                }
                else
                {
                    /* Save Block index, add 1 as index 0 is reserved for ESS */
                    pstSegment->ubLogicalBlockId = ubBlockId + 1U;
#if (PROG_ERASE_CHECK_TYPE == PROG_BLOCK_ERASE_CHECK)
                    /* Check if logical block is already erased, index 0 is reserved for ESS */
                    eEraseStatus = PROG_CustomGetEraseStatus(pstSegment->ubLogicalBlockId);

                    if(PROG_E_ERASED == eEraseStatus)
                    {
                        eProgStatus = PROG_E_BYPASS;
                    }
#endif /*(PROG_ERASE_CHECK_TYPE == PROG_BLOCK_ERASE_CHECK)*/

                }
            }
            else
            {
                /* Error in ESS, erase cannot be performed */
                eProgStatus = PROG_E_NOT_OK;
            }
        }
        else
        {
            /* ESS is not present, erase cannot be performed */
            eProgStatus = PROG_E_NOT_OK;
        }
    }
    return eProgStatus;
}
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
tProgStatus PROG_RD_Check_Impl11(u32 ulStartAddress, u32 ulMemorySize, u8 ubLocalSegmentId, u8 * pubBlockIndex)
{

    tProgStatus eESSStatus;

    tProgStatus eProgStatus = PROG_E_OK;
    u8 ubBlockNbr;
    u32 ulBlockAddr;
    u32 ulBlockLength;
    u8 ubBlockId;
    u8 ubLoopIndex;

    /* ESS Management */
    /* Identify if it is ESS block is addressed */
    if (stConfigSegment[ubLocalSegmentId].ePartitionType == PROG_ESS_PARTITION)
    {
       /* Another software part is being downloaded, abort */
       if((m_ubSoftwarePartID !=PROG_SOFTWARE_PART_FINISHED) && (m_ubSoftwarePartID !=0))
       {
         eProgStatus = PROG_E_NOT_OK;
       }
       else
       {
         /* index 0 is reserved for ESS */
         m_ubSoftwarePartID = 0U;
         *pubBlockIndex = 0U;
       }
    }
    else
    {
      /* Check if the data block to be downloaded is in order only if VBT is downloaded */
      if( ((ulStartAddress > m_ulLastWrittenAddress) && (TRUE ==  m_ubVerificationTablePresent)) || (FALSE ==  m_ubVerificationTablePresent) )
      {
        /* Not ESS memory */
        /* Check if ESS is present in memory and valid */
        eESSStatus = Prog_GetEssValidityStatus();
        if (PROG_E_OK == eESSStatus)
        {
            /* Find if memory range to erase is defined in ESS */
            eESSStatus = Prog_GetEssLogicalBlockNbr(&ubBlockNbr);
            if (PROG_E_OK == eESSStatus)
            {
                ubBlockId = 0xFFU;
                for (ubLoopIndex = 0U; ((ubLoopIndex < ubBlockNbr) && (0xFFU == ubBlockId)); ubLoopIndex++)
                {
                    eESSStatus = Prog_GetEssLogicalBlockStartAddr(ubLoopIndex, &ulBlockAddr);
                    if ((PROG_E_OK == eESSStatus) && (ulStartAddress >= ulBlockAddr))
                    {
                        eESSStatus = Prog_GetEssLogicalBlockLength(ubLoopIndex, &ulBlockLength);
                        if ((PROG_E_OK == eESSStatus) && ((ulStartAddress + ulMemorySize) <= (ulBlockAddr + ulBlockLength)))
                        {
                          /* Another sofwtare part is being downloaded */
                          if( (m_ubSoftwarePartID !=PROG_SOFTWARE_PART_FINISHED) && (m_ubSoftwarePartID != (ubLoopIndex + 1U)) )
                          {
                            eProgStatus = PROG_E_NOT_OK;
                          }
                          else
                          {
                            /* Matching block has been found */
                            ubBlockId = ubLoopIndex;
                          }

                        }
                    }
                }
                if (0xFFU == ubBlockId)
                {
                    /* No matching block found in ESS, send negative response */
                    eProgStatus = PROG_E_NOT_OK;
                }
                else
                {
                    /* Save Block index, add 1 as index 0 is reserved for ESS */
                    *pubBlockIndex = ubBlockId + 1U;
                    m_ubSoftwarePartID = ubBlockId + 1U;
                    /* update the address of the last written data */
                    m_ulLastWrittenAddress = ulStartAddress + ulMemorySize - 1U;
                }
            }
            else
            {
                /* Error in the ESS, no access allowed  */
                eProgStatus = PROG_E_NOT_OK;
            }
        }
        else
        {
            /* ESS is not present, no access allowed */
            eProgStatus = PROG_E_NOT_OK;
        }
      }
      else
      {
        /* data block order is not respected */
        eProgStatus = PROG_E_NOT_OK;
      }
    }
    return eProgStatus;
}
#endif

tUdsStatus PROG_WriteProdKey(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;
    eStatus = PROG_GenericRequest(pulLen, aubUdsData,
            PROG_HSM_PROG_EV_PROG_EVENT_REQ_WRITE_KEY);
    return (eStatus);
}

tUdsStatus PROG_ReadProdKey(PduLengthType *pulLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;
    if((pulLen != NULL_PTR) && (aubUdsData != NULL_PTR))
    {
        if(TRUE == Prog_CustomIsProdKeyPresent())
        {
          eStatus = UDS_ACK;
          *pulLen = PROG_RK_RESPONSE_SIZE;
          Prog_CustomReadKeyChecksum(&aubUdsData[3]);
        }
        else
        {
          eStatus = UDS_NRC_22;
        }
    }
    else
    {
        eStatus = UDS_NRC_31;
    }

    return (eStatus);
}

void PROG_Impl10_Entry_CheckReceivedKey(void)
{
  if(TRUE == Prog_CustomIsProdKeyPresent())
  {
    PROG_Send_NRC(UDS_NRC_22);
  }
  else
  {
    (void)PROG_ComputeHashStart(PROG_CSM_HASH_ID,NULL_PTR,0U,NULL_PTR);
  }
}

void PROG_Impl10_Do_CheckHashOfKey(void)
{
  tProgCryState eCryptoState;
  tProgStatus eCryptoStatus;

  eCryptoState = PROG_GetCryptoState();
  eCryptoStatus = PROG_GetCryptoStatus();

  if(PROG_E_NOT_OK != eCryptoStatus)
  {
    if(PROG_HASH_END == eCryptoState)
    {
      PROG_ComputeHashFinish(&m_aubComputedDigest[0]);
    }
    else if(PROG_HASH_START_END == eCryptoState)
    {
      PROG_ComputeHashUpdate(&m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX], PROG_KEY_LENGTH + PROG_MOD_LENGTH);
    }
    else
    {
      /* do nothing */
    }
  }
  else
  {
    /* go to CRYPTO_FAILURE state */
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    /* Send negative response */
    UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_31);
  }
}

void PROG_Impl10_Entry_WriteKeyFinished(void)
{
  u8 ubLoopIndex;
  tProgStatus ubHashStatus = PROG_E_OK;
  u32 ulExponent;

  for (ubLoopIndex = 0U; ((ubLoopIndex < PROG_DIGEST_LENGTH)&&(PROG_E_OK == ubHashStatus)); ubLoopIndex++)
  {
       /* compare hash */
       if (m_aubComputedDigest[ubLoopIndex] != m_stDiagMessageInfo.pubData[PROG_PROD_KEY_HASH_INDEX + ubLoopIndex])
       {
         ubHashStatus = PROG_E_NOT_OK;
       }
  }

  if(PROG_E_OK == ubHashStatus)
  {
    /* Call callback to write the checksum and the key in non volatile memory */
    ulExponent =  (u32)((u32)(m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX + PROG_KEY_LENGTH]) << 24U);
    ulExponent |=  (u32)((u32)(m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX + PROG_KEY_LENGTH + 1U]) << 16U);
    ulExponent |=  (u32)((u32)(m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX + PROG_KEY_LENGTH + 2U]) << 8U);
    ulExponent |=  (u32)(m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX + PROG_KEY_LENGTH + 3U]);
    Prog_CustomWriteKey(ulExponent, &m_stDiagMessageInfo.pubData[PROG_PROD_KEY_INDEX], &m_stDiagMessageInfo.pubData[PROG_PROD_KEY_HASH_INDEX]);

    /* Send positive response with same data then request*/
    UDS_LongRequestEnd(PROG_WK_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);
  }
  else
  {
    /* Send negative response */
    UDS_LongRequestEnd(PROG_NRC_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_31);
  }
}

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
void PROG_Impl10_SoftwarePartFinished(void)
{
  m_ubSoftwarePartID = PROG_SOFTWARE_PART_FINISHED;
}
#endif

tProgStatus PROG_Impl10_CheckMemoryAllowed(void)
{
    tProgStatus eProgStatus = PROG_E_NOT_OK;

#if (PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED == STD_ON)
    /* Accept only two check memory attempts */
    if (m_ubFailedCheckMemoryCount < PROG_CHECK_MEMORY_MAX_ATTEMPTS)
    {
        eProgStatus = PROG_E_OK;
    }
    else
    {
        /* Do nothing */
    }

    /* If the transition is not allowed, send NRC 24 */
    if (PROG_E_NOT_OK == eProgStatus)
#endif
    {
        /* Send negative response NRC 24 */
        UDS_LongRequestEnd(PROG_CHK_MEMORY_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_NRC_24);
    }

    return eProgStatus;
}

NCS_PRI_VAR void PROG_GetVBTLength(u32* pulVBTLength)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    /* Read VBT Length from RAM Memory*/
    *pulVBTLength = PROG_SBL_VBT_LENGTH;
#else
    /* VBT Length for ESS */
    if (0U == m_stCurrentSegment.ubLogicalBlockId)
    {
        /* VBT of ESS is obtained here */
        (void)Prog_GetEss_VBTLength(pulVBTLength);
    }
    else
    {
        /* VBT Length is obtained for APPL/CALIB  */
        (void)Prog_GetAPPL_VBTLength(m_stCurrentSegment.ubLogicalBlockId - 1U, pulVBTLength);
    }
#endif
}


NCS_PRI_VAR void PROG_GetVBTAddress(u32 * pulVBTAddress)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
  /* Read VBT from Memory  */
  /* SBL is always in the RAM */
  *pulVBTAddress = PROG_SBL_VBT_START_ADDRESS;
#else
   /* SBL variant */
    if (0U == m_stCurrentSegment.ubLogicalBlockId)
    {
        /* VBT of ESS is required here */
        (void)Prog_GetEssVerifTable(pulVBTAddress);
    }
    else
    {
       /* Address of VBT is get from ESS, subtract one because the ess data is not included in the ess  */
       (void)Prog_GetEssLogicalBlockVerifTable(m_stCurrentSegment.ubLogicalBlockId - 1U, pulVBTAddress);
    }
#endif
}

NCS_PRI_VAR void PROG_GetStartAddressFromVBT(u16 uwDataBlockIndex,u32*ulStartAddress)
{
  u8 aubData[PROG_ERASE_ADDR_LEN];

  u32 ulVBTAddress;

  PROG_GetVBTAddress(&ulVBTAddress);
  ulVBTAddress += PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET + (PROG_DATA_BLOCKS_USEFUL_DATA_SIZE * (u32)uwDataBlockIndex);

  /* Read VBT from Memory  */
  (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_ERASE_ADDR_LEN, aubData);

  (*ulStartAddress) = (u32)((u32)(aubData[0]) << 24U);
  (*ulStartAddress) |= (u32)((u32)(aubData[1]) << 16U);
  (*ulStartAddress) |= (u32)((u32)(aubData[2]) << 8U);
  (*ulStartAddress) |= (u32)(aubData[3]);

}

NCS_PRI_VAR void PROG_GetLengthFromVBT(u16 uwDataBlockIndex,u32*ulLength)
{
  u8 aubData[PROG_ERASE_SIZE_LEN];

  u32 ulVBTAddress;

  PROG_GetVBTAddress(&ulVBTAddress);

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
  /* Read VBT from Memory  */
  /* SBL is always in the RAM */
  (void)PROG_MemDataAccess( PROG_MEM_TYPE_RAM,PROG_MEM_OPERATION_TYPE_READ,

      ulVBTAddress + PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET + PROG_DATA_BLOCKS_LENGTH_OFFSET + (PROG_DATA_BLOCKS_USEFUL_DATA_SIZE * (u32)uwDataBlockIndex),
      PROG_ERASE_SIZE_LEN, aubData);
#else
   /* SBL variant */
   ulVBTAddress += PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET + PROG_DATA_BLOCKS_LENGTH_OFFSET + (PROG_DATA_BLOCKS_USEFUL_DATA_SIZE * (u32)uwDataBlockIndex);
  (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_ERASE_SIZE_LEN, aubData);
#endif
  (*ulLength) = (u32)((u32)(aubData[0]) << 24U);
  (*ulLength) |= (u32)((u32)(aubData[1]) << 16U);
  (*ulLength) |= (u32)((u32)(aubData[2]) << 8U);
  (*ulLength) |= (u32)(aubData[3]);

}

NCS_PRI_VAR void PROG_GetDigestFromVBT(u16 uwDataBlockIndex,u8*aubDigest)
{
  u8 aubData[PROG_DIGEST_LENGTH];
  u8 ubIdx;

  u32 ulVBTAddress;

  PROG_GetVBTAddress(&ulVBTAddress);

   ulVBTAddress += PROG_DATA_BLOCKS_USEFUL_DATA_OFFSET + PROG_DATA_BLOCKS_HASH_OFFSET + (PROG_DATA_BLOCKS_USEFUL_DATA_SIZE * (u32)uwDataBlockIndex);

   /* Read hash value from memory */

  (void)PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_DIGEST_LENGTH, aubData);

  /* Hash value */
  for(ubIdx = 0; ubIdx <PROG_DIGEST_LENGTH; ubIdx++)
  {
    aubDigest[ubIdx] = aubData[ubIdx];

  }

}
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR void PROG_BlankCheck(u16 ubSegmentId, u32 ulSegmentStartAddr)
#else
NCS_PRI_VAR void PROG_BlankCheck(u16 ubSegmentId, u32 ulSegmentStartAddr, u32 ulSegmentSize)
#endif
{
    tProgStatus ubProgStatus = PROG_E_OK;
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    u32 ulPage;
    u32 ulNbPages;
#else
    u32 ulLoop;
    u32 ulBlankSize;
    u8  ubBlankValue;
#endif
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    ulNbPages = (ulSegmentStartAddr - m_ulBlankCheckLastAddress) / m_astCfgMemory[stConfigSegment[ubSegmentId].ubMemoryIdx].ulMinValueToWrite;
    for (ulPage = 0U; ((ulPage < ulNbPages) && (ubProgStatus == PROG_E_OK)); ulPage++)
    {
        ubProgStatus = PROG_MemCheckPageErasing(
                    m_astCfgMemory[stConfigSegment[ubSegmentId].ubMemoryIdx].eMemoryType,
                    m_ulBlankCheckLastAddress);
        if(ubProgStatus == PROG_E_NOT_OK)
        {
            m_ubCheckMemoryStatus = PROG_BLANK_CHECK_FAILED;
        }
        m_ulBlankCheckLastAddress+= m_astCfgMemory[stConfigSegment[ubSegmentId].ubMemoryIdx].ulMinValueToWrite;
    }
#else /* (PROG_IMPL_VARIANT == PROG_IMPL_11) */
    /* Size of SBL Blank space */
    ulBlankSize = ulSegmentStartAddr - m_ulBlankCheckLastAddress;
    ubBlankValue = PROG_SBL_BLANK_VALUE;
    /* Fill the table to be written for the blank space */
    for(ulLoop = 0U; ulLoop < ulBlankSize; ulLoop++)
    {
        /* Write in RAM */
        ubProgStatus = PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[ubSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_WRITE,
            m_ulBlankCheckLastAddress,
            1U,
            &ubBlankValue);
        m_ulBlankCheckLastAddress+= 1U;
    }
/* CHECK: NOPARSE */
/* NOCOV-UNITARYTEST */
    if(ubProgStatus == PROG_E_NOT_OK)
    {
        m_ubCheckMemoryStatus = PROG_BLANK_CHECK_FAILED;
    }
/* CHECK: PARSE */
    m_ulBlankCheckLastAddress+= ulSegmentSize;
#endif
}
NCS_PRI_VAR tProgStatus PROG_CheckNonProgrammedAreas(void)
{
    tProgStatus ubProgStatus = PROG_E_OK;
    u8 ubIdx;
    u16 uwIdx;
    u8 ubLoop;
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    u16 uwDataBlockNbr;
    u32 ulStartAddress;
#endif
    u8 ubSegmentIsNotProgrammed;
    /* Check if all configured segments were programmed and do the blank check on the non programmed segments (at all) */
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    /* Get the logical block number of segments from VBT*/
    if(0U == m_stCurrentSegment.ubLogicalBlockId)
    {
      uwDataBlockNbr = 1U;
    }
    else
    {
    PROG_GetDataBlockNbrFromVBT(&uwDataBlockNbr);
    }
    /* Plus VBT*/
    for (uwIdx = 0U; uwIdx < (uwDataBlockNbr + 1U); uwIdx++)
#else
    for (uwIdx = 0U; uwIdx < stCfgBlock[m_stCurrentSegment.ubLogicalBlockId].ubSegmentNbr; uwIdx++)
#endif
    {
        ubSegmentIsNotProgrammed = PROG_TRUE;
        for (ubLoop = 0U; ((ubLoop < m_stSegList.ubSegNbr) && (ubSegmentIsNotProgrammed == PROG_TRUE)); ubLoop++)
        {
            if (uwIdx == m_stSegList.astSeg[ubLoop].ubSegmentId)
            {
                ubSegmentIsNotProgrammed = PROG_FALSE;
            }
        }
        if (PROG_TRUE == ubSegmentIsNotProgrammed)
        {
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            PROG_GetStartAddressFromVBT(uwIdx , &ulStartAddress);
            m_ulBlankCheckLastAddress = ulStartAddress;
            PROG_BlankCheck(uwIdx, ulStartAddress);
#else
            m_ulBlankCheckLastAddress = stConfigSegment[uwIdx].ulStartAddress;
            PROG_BlankCheck(uwIdx, stConfigSegment[uwIdx].ulStartAddress, (stConfigSegment[uwIdx].ulEndAddress - stConfigSegment[uwIdx].ulStartAddress));
#endif
        }
    }
   /* Blank check on all non-programmed areas */
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)

    m_ulBlankCheckLastAddress = stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseStartAddress; /* Block start address */
    for (ubIdx = 0U; ((ubIdx < m_stSegList.ubSegNbr) && (m_ubCheckMemoryStatus != PROG_BLANK_CHECK_FAILED)); ubIdx++)
    {
        PROG_BlankCheck(m_stSegList.astSeg[ubIdx].ubSegmentId, m_stSegList.astSeg[ubIdx].ulStartAddress);
        m_ulBlankCheckLastAddress = m_stSegList.astSeg[ubIdx].ulStartAddress + m_stSegList.astSeg[ubIdx].ulSize;

    }

    if ((m_ulBlankCheckLastAddress < stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseEndAddress)  && (m_ubCheckMemoryStatus != PROG_BLANK_CHECK_FAILED))
    {
        /* Blank check on the rest of the memory */
        PROG_BlankCheck(m_stCurrentSegment.ubSegmentId, stConfigSegment[m_stCurrentSegment.ubSegmentId].ulEraseEndAddress);
    }
#else

    m_ulBlankCheckLastAddress = stConfigSegment[stCfgBlock[m_stCurrentSegment.ubLogicalBlockId].ubFirstSegmentId].ulStartAddress; /* Fisrt configured segment start address */

    for (ubIdx = 0U; ((ubIdx < m_stSegList.ubSegNbr) && (m_ubCheckMemoryStatus != PROG_BLANK_CHECK_FAILED)); ubIdx++)
    {
        PROG_BlankCheck(m_stSegList.astSeg[ubIdx].ubSegmentId, m_stSegList.astSeg[ubIdx].ulStartAddress, m_stSegList.astSeg[ubIdx].ulSize);


    }

#endif

    if (m_ubCheckMemoryStatus == PROG_BLANK_CHECK_FAILED)
    {
        ubProgStatus = PROG_E_NOT_OK;
    }


   return ubProgStatus;
}

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR tProgStatus PROG_CheckESSCoverageOfProgrammableMemory(void)
{
    tProgStatus eESSStatus = PROG_E_OK;
    u8  ubBlockFound;
    u8  ubAllBlocksFound = PROG_TRUE;
    u16 uwIdx;
    u8  ubBlockNbr;
    u32 ulBlockAddr;
    u32 ulBlockLength;
    u8  ubLoopIndex;

    /* Check if ESS covers all programmable memory */

    /* Get the number of Logical blocks defined in the ESS */
    eESSStatus = Prog_GetEssLogicalBlockNbr(&ubBlockNbr);

    if (PROG_E_OK == eESSStatus)
    {
        /* Check that all configured segments are included in ESS */
        for (uwIdx = 1U; ((uwIdx < PROG_SEGMENT_NB) && (PROG_TRUE == ubAllBlocksFound)); uwIdx++) /* ESS is segment 0*/
        {
            ubBlockFound = PROG_FALSE;
            for (ubLoopIndex = 0U; ((ubLoopIndex < ubBlockNbr) && (PROG_FALSE == ubBlockFound)); ubLoopIndex++)
            {
                eESSStatus = Prog_GetEssLogicalBlockStartAddr(ubLoopIndex, &ulBlockAddr);
                if ((PROG_E_OK == eESSStatus) && (stConfigSegment[uwIdx].ulEraseStartAddress >= ulBlockAddr))
                {
                    eESSStatus = Prog_GetEssLogicalBlockLength(ubLoopIndex, &ulBlockLength);
                    if ((PROG_E_OK == eESSStatus) && ((stConfigSegment[uwIdx].ulEraseEndAddress - stConfigSegment[uwIdx].ulEraseStartAddress) <= ulBlockLength))
                    {
                        /* Matching block has been found for segment uwIdx */
                        ubBlockFound = PROG_TRUE;
                    }
                    else
                    {
                        /* Nothing to do. Block is not found yet */
                    }
                }
                else
                {
                    /* Nothing to do. Block is not found yet */
                }
            }
            if (PROG_FALSE == ubBlockFound)
            {
                /* No matching block found in ESS*/
                eESSStatus = PROG_E_NOT_OK;
                ubAllBlocksFound = PROG_FALSE;
                m_ubCheckMemoryStatus = PROG_ESS_MEM_COVERAGE_FAIL;
            }
            else
            {
                /* Nothing to do. Block is found in ESS */
            }

        }
    }
    else
    {
        m_ubCheckMemoryStatus = PROG_ESS_MEM_COVERAGE_FAIL;
    }

    return eESSStatus;

}
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR void PROG_GetDataBlockNbrFromVBT(u16 *uwBlockNumber)
{
  u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
  u32 ulVBTAddress;

   /* SBL variant */
   /* Address of VBT is get from ESS, subtract one because the ess data is not included in the ess   */
   (void)Prog_GetEssLogicalBlockVerifTable(m_stCurrentSegment.ubLogicalBlockId - 1U, &ulVBTAddress);
   ulVBTAddress += PROG_DATA_BLOCKS_COUNT_MSB_OFFSET;
  (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);
  (*uwBlockNumber)  = (u16)((u16)(aubData[0]) << 8U);
  (*uwBlockNumber) |= (u16)(aubData[1]);
}

NCS_PRI_VAR void PROG_GetVBTFormat(u16 *uwFormatID)
{
  u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
  u32 ulVBTAddress;

   /* SBL variant */
   /* Address of VBT is get from ESS, subtract one because the ess data is not included in the ess   */
   (void)Prog_GetEssLogicalBlockVerifTable(m_stCurrentSegment.ubLogicalBlockId - 1U, &ulVBTAddress);
  (void)PROG_MemDataAccess( m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_VBT_FORMAT_ID_SIZE, aubData);
  (*uwFormatID)  = (u16)((u16)(aubData[0]) << 8U);
  (*uwFormatID) |= (u16)(aubData[1]);
}
#endif

NCS_PRI_VAR tProgStatus PROG_VerifyVBTFormatAndLength(void)
{
  u16 uwDataBlockNbr = 0U;
  /* value different than 0 because the current format ID is already 0 */
  u16 uwVBTFormat = 0xEBEBU;
  tProgStatus ubProgStatus = PROG_E_OK;
  u32 ulExpectedLength;
  u8 aubData[2];
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
  u32 ulVBTAddress;
#endif

  /* Check Format */
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
  /* SBL variant */
  /* in case of ESS assume one continuous block */
  if(0U == m_stCurrentSegment.ubLogicalBlockId)
  {
    (void)Prog_GetEssVerifTable(&ulVBTAddress);
    ubProgStatus = PROG_MemDataAccess(m_astCfgMemory[stConfigSegment[m_stCurrentSegment.ubSegmentId].ubMemoryIdx].eMemoryType ,PROG_MEM_OPERATION_TYPE_READ, ulVBTAddress, PROG_VBT_FORMAT_ID_SIZE, aubData);
    if(PROG_E_OK == ubProgStatus)
    {
      uwVBTFormat = (u16)((u16)aubData[0] << 8U);
      uwVBTFormat |= (u16)aubData[1];
    }

  }
  else
  {
    PROG_GetVBTFormat(&uwVBTFormat);
  }
#else
  ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VBT_START_ADDRESS, PROG_VBT_FORMAT_ID_SIZE, aubData);
  if(PROG_E_OK == ubProgStatus)
  {
    uwVBTFormat = (u16)((u16)aubData[0] << 8U);
    uwVBTFormat |= (u16)aubData[1];
  }
#endif
  if(PROG_E_OK == ubProgStatus)
  {
    if(uwVBTFormat != (u16)PROG_EXPECTED_VBT_FORMAT_ID)
    {
      ubProgStatus = PROG_E_NOT_OK;
      m_ubCheckMemoryStatus = PROG_INVALID_VBT_FORMAT_LENGTH;
    }
  }

  /* format is ok, check length  */
  if(PROG_E_OK == ubProgStatus)
  {
    /* Check Length */
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    /* SBL variant */
    /* in case of ESS assume one continuous block */
    if(0U == m_stCurrentSegment.ubLogicalBlockId)
    {
      uwDataBlockNbr = 1U;
    }
    else
    {
      PROG_GetDataBlockNbrFromVBT(&uwDataBlockNbr);
    }
#else
    ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VBT_START_ADDRESS + PROG_DATA_BLOCKS_COUNT_MSB_OFFSET, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);
    if(PROG_E_OK == ubProgStatus)
    {
      uwDataBlockNbr = (u16)((u16)aubData[0] << 8U);
      uwDataBlockNbr |= (u16)aubData[1];
    }
    if(PROG_E_OK == ubProgStatus)
#endif
    {
      ulExpectedLength = PROG_VBT_FORMAT_ID_SIZE + PROG_DATA_BLOCKS_COUNT_SIZE + ((u32)uwDataBlockNbr*PROG_DATA_BLOCKS_USEFUL_DATA_SIZE);

      if(m_ulVBTWrittenData != ulExpectedLength)
      {
        ubProgStatus = PROG_E_NOT_OK;
        m_ubCheckMemoryStatus = PROG_INVALID_VBT_FORMAT_LENGTH;
      }
    }
  }

  return ubProgStatus;
}

NCS_PRI_VAR tProgStatus PROG_CheckHashResults(void)
{
   tProgStatus ubProgStatus = PROG_E_OK;
   u16 uwIdx;
   u16 uwDataBlockNbr = 0U;

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
   u8 aubData[PROG_DATA_BLOCKS_COUNT_SIZE];
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
   /* SBL variant */
   /* in case of ESS assume one continuous block */
   if(0U == m_stCurrentSegment.ubLogicalBlockId)
   {
     uwDataBlockNbr = 1U;
   }
   else
   {
     PROG_GetDataBlockNbrFromVBT(&uwDataBlockNbr);
   }
#else
   ubProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_RAM ,PROG_MEM_OPERATION_TYPE_READ, PROG_SBL_VBT_START_ADDRESS + PROG_DATA_BLOCKS_COUNT_MSB_OFFSET, PROG_DATA_BLOCKS_COUNT_SIZE, aubData);
   if(PROG_E_OK == ubProgStatus)
   {
     uwDataBlockNbr = (u16)((u16)aubData[0] << 8U);
     uwDataBlockNbr |= (u16)aubData[1];
   }
   else
   {
     m_ubCheckMemoryStatus = PROG_READ_ERROR_FOR_HASH;
   }

   if(PROG_E_OK == ubProgStatus)
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_11)*/
   {
     /* Check that all data blocks are downloaded and their hash is correct */
     for(uwIdx = 0U; uwIdx < uwDataBlockNbr; uwIdx++)
     {
       ubProgStatus |= m_aubHashComparisonStatus[uwIdx];
     }

     if(PROG_E_NOT_OK == ubProgStatus)
     {
       m_ubCheckMemoryStatus = PROG_WRONG_HASH;
     }
   }

   return ubProgStatus;
}
/*----------------------------------{PROG_ReadKeyProgrammedStatus}---------------------------------------*/
#if(PROG_SA_AUTHENTICATION_METHOD == PROG_SA_AUTHENTICATION_0001 )
#if(PROG_SA_SECUREDKEYS_STATUSREAD == STD_ON )
tUdsStatus PROG_ReadKeyProgrammedStatus(PduLengthType *pulLen, u8 *aubUdsData)
{
    if (SA_GetSecuredKeysStatus() == SA_E_OK)
    {
        aubUdsData[PROG_SA_AM_READKEYSTATUS_STATUSINDEX] = PROG_SA_AM_KEYS_PROGRAMMED;
    }
    else
    {
        aubUdsData[PROG_SA_AM_READKEYSTATUS_STATUSINDEX] = PROG_SA_AM_KEYS_NOT_PROGRAMMED;
    }
    aubUdsData[PROG_SA_AM_READKEYSTATUS_SECLEVINDEX] = PROG_SA_AM_READKEYSTATUS_SECLEV_SUPPORTED;
    aubUdsData[PROG_SA_AM_READKEYSTATUS_NUMSECLEVINDEX] = PROG_SA_AM_READKEYSTATUS_NUMSECLEVS_SUPPORTED ;
    *pulLen = PROG_SA_AM_READKEYSTATUS_RESPLEN;

    return UDS_ACK;
}
#endif /* (PROG_SA_SECUREDKEYS_STATUSREAD == STD_ON ) */
#endif /*(PROG_SA_AUTHENTICATION_METHOD == PROG_SA_AUTHENTICATION_0001 )*/
/*----------------------------------{end PROG_ReadKeyProgrammedStatus}------------------------------------*/
#endif
