/**
 * \file
 *
 * \brief AUTOSAR Fee
 *
 * This file contains the implementation of the AUTOSAR
 * module Fee.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* This file contains code for Fee initialization */
/*==================[inclusions]============================================*/
#include <Fee.h>                /* External API declarations  */
#include <Fee_Internal.h>       /* Internal function prototypes and internal defines and declarations*/
#include <TSMem.h>              /* Memory Routines */
#if (FEE_PROD_ERROR_DETECT == STD_ON)
/* !LINKSTO Fee.ASR40.SWS_Fee_00060,1 */
#include <Dem.h>                /* General Dem header file */
#endif
#include <Crc.h>                /* Crc public header file  */
#include <Fee_Initialization.h> /* Not needed. Included only to prevent warning. */

/*==================[macros]=================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/** \brief Function to decide the next step after Footer reading */
INLINE STATIC FUNC(void, FEE_CODE) Fee_FooterReadNextStep(void);

#if FEE_USE_BLANKCHECK == STD_OFF
/** \brief Function to read the next block info or the next buffer of block infos */
INLINE STATIC FUNC(void, FEE_CODE) Fee_ReadNextBlockInfo(void);

/** \brief Function to read the next buffer of block infos */
STATIC FUNC(void, FEE_CODE) Fee_ReadNextBufferOfBlockInfos(void);

/** \brief Function to fill the cache after each Fee_LowerLayer_Read of block infos */
STATIC FUNC(boolean, FEE_CODE) Fee_FillCache(void);

#else /* #if FEE_USE_BLANKCHECK == STD_OFF */
/** \brief Function to read the next block info or the next buffer of block infos */
STATIC FUNC(void, FEE_CODE) Fee_BcNextBlockInfo(void);
#endif /* #if FEE_USE_BLANKCHECK == STD_OFF */

/** \brief Function to go cache the next section or finish StartUp1 */
STATIC FUNC(void, FEE_CODE) Fee_SectionCachedGoToNextStep(void);

/** \brief Function to determine if there is any possible block info left to be cached in section,
 *         otherwise change the section for further caching. */
STATIC FUNC(void, FEE_CODE) Fee_CheckExitCaching(void);

/** \brief Function to cache one block info if valid */
INLINE STATIC FUNC(void, FEE_CODE) Fee_ProcessBlockInfo(void);

/** \brief Function to verify if the block needs to be chached, and where(FeeCache or FeeSwRestartCache).
           Calls the Fee_CacheBlockAddress function if all the preconditions for caching are met. */
STATIC FUNC(void, FEE_CODE) Fee_CacheIfNewerInstance
(
  Fee_LowerLayer_AddressType BlockAddress,
  uint16 BlockLength,
  uint16 BlockIndex
);

/** \brief Function to save the data address of the block in cache.
 *         It returns TRUE if the block was cached. */
STATIC FUNC(boolean, FEE_CODE) Fee_CacheBlockAddress
(
  Fee_LowerLayer_AddressType * CacheObject,
  Fee_LowerLayer_AddressType BlockAddress,
  uint16 BlockLength,
  uint16 BlockIndex
);

/** \brief Function to check the validity of the currently read section management (header/footer).
 *         Also memorizes the erase counter if it is the greatest and establish the newest section.
 *
 * \revtal - the validity of the section management object.
 */
STATIC FUNC(Fee_SectionStatus_t, FEE_CODE) Fee_CheckSectionManagementValidity(void);

/** \brief Function to check and set the status of the currently read section management (header/footer)
 *         based on the validity of the section management object.
 *
 * \param[in] HeaderOrFooter - type of section management object
 * \param[in] Validity - validity of the section management object
 *
 * \revtal - the status of the section management object.
 */
STATIC FUNC(Fee_SectionStatus_t, FEE_CODE) Fee_GetSectionManagementStatus
(
    void
);

/** \brief Function to set the section status of the currently processed section,
 *         based on both section management objects statuses.
 *
 * \param[in] HeaderStatus - the status of the section's header
 * \param[in] FooterStatus - the status of the section's footer
 */
STATIC FUNC(void, FEE_CODE) Fee_DecideSectionStatus
(
    Fee_SectionStatus_t HeaderStatus,
    Fee_SectionStatus_t FooterStatus
);

/** \brief Function to iterate through the already set sections statuses and decide
 * the actual Active section and the oldest section */
STATIC FUNC(void, FEE_CODE) Fee_HandleSectionChaining(void);

/** \brief Function to find the best candidate for the Active section. */
STATIC FUNC(void, FEE_CODE) Fee_CheckForAnchorSection(void);

/** \brief Function that returns TRUE if the currently read header is marked as To Be Erased,
 *         otherwise returns FALSE. */
STATIC FUNC(boolean, FEE_CODE) Fee_IsHeaderMarkedAsToBeErased(void);

/** \brief Function that returns TRUE if the currently read header is marked as Active,
 *         otherwise returns FALSE. */
STATIC FUNC(boolean, FEE_CODE) Fee_IsHeaderMarkedAsActive(void);

/** \brief Function that returns TRUE if the currently read footer is marked as To Be Erased,
 *         otherwise returns FALSE. */
STATIC FUNC(boolean, FEE_CODE) Fee_IsFooterMarkedAsToBeErased(void);

/** \brief Function that returns TRUE if the currently read footer is marked as Active,
 *         otherwise returns FALSE. */
STATIC FUNC(boolean, FEE_CODE) Fee_IsFooterMarkedAsActive(void);

/** \brief Function that handles the finalization of Startup1 and decide the next steps. */
STATIC FUNC(void, FEE_CODE) Fee_StartUp1Finished(void);

/** \brief Function to validate the block information data address is consistent with the current section boundries.
 *        The function will return TRUE is the block data address is betweeen the current working section boundries, otherise will return FALSE.
 *
 * \param[in] BlockLength - Block length
 * \param[in] BlockDataAddress - Block Data Address
 */
STATIC FUNC(boolean, FEE_CODE) Fee_ValidateDataAddress( const uint16 BlockLength, const Fee_LowerLayer_AddressType BlockDataAddress);

#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
/** \brief Function that handles activity when critical block was found in flash */
STATIC FUNC(boolean, FEE_CODE) Fee_CriticalBlockInit(void);
#endif /* (FEE_CRITICAL_BLOCK_NUMBER != 0U) */

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

#if (FEE_USE_BLANKCHECK == STD_ON)
/*--------------------------[Fee_SfOnEntryBlankCheckHeader]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckHeader
(
  void
)
{
#if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON)
  /* !LINKSTO Fee.ConsistencyPatterns.SectionHeader.Read.Startup,1 */
  /* Blank check the footer's end pattern */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET,
                             FEE_CONSISTENCY_PATTERN_SIZE))
#else /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
  /* !LINKSTO Fee.Dsn.BlankCheck.SectionManagement,1 */
  /* Blank check the footer's management object */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_SECTION_MARKER_SIZE_AL,
                             FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL))
#endif /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckHeader]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckHeader
(
  void
)
{
  Fee_SectionStatus_t TempSectionStatus;
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Blank check of the header finished */
  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* Simulate the read of an empty field */
    TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_SECTION_MARKER_SIZE_AL],
              ((uint8)FEE_FLASH_ERASE_VALUE),
              ((uint32)FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL));
    /* Set the Header's status */
    TempSectionStatus = Fee_GetSectionManagementStatus();
    Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = TempSectionStatus;
    /* Check the footer's Erasable marker */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER_ERASABLE);
  }
  /* previous flash job has failed */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.SectionManagementRefused,1 */
      /* Simulate the read of a corrupted field */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_SECTION_MARKER_SIZE_AL],
                ((uint8)0x00),
                ((uint32)FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL));
      /* Set the Header's status */
      TempSectionStatus = Fee_GetSectionManagementStatus();
      Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = TempSectionStatus;
      /* Check the footer's Erasable marker */
      FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER_ERASABLE);
    }
    else
    {
      /* Header is written. Read it! */
      FEE_TRIGGER_TRANS(FEE_INIT_READ_HEADER);
    }
  }
}

/*--------------------------[Fee_SfOnEntryBlankCheckFooter]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckFooter
(
  void
)
{
#if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON)
  /* !LINKSTO Fee.ConsistencyPatterns.SectionHeader.Read.Startup,1 */
  /* Will be blank checked either the end pattern or the footer's management */
  Fee_LowerLayer_LengthType BlankCheckSize = (Fee_Gv.Fee_BufferIndex == 0U) ? FEE_CONSISTENCY_PATTERN_SIZE : FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL;
  Fee_LowerLayer_AddressType BlankCheckAddress = FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET - Fee_Gv.Fee_BufferIndex;
#else /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
  Fee_LowerLayer_LengthType BlankCheckSize = FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL;
  Fee_LowerLayer_AddressType BlankCheckAddress = FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) +  FEE_SECTION_MARKER_SIZE_AL;
#endif /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */

  /* !LINKSTO Fee.Dsn.BlankCheck.SectionManagement,1 */
  /* Blank check the footer's management object */
  /* In case of consistency pattern, it will be blank checked either the end pattern or the footer's management */
  if (E_OK == Fee_LowerLayer_BlankCheck(BlankCheckAddress,
                             BlankCheckSize))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckFooter]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckFooter
(
  void
)
{
  Fee_SectionStatus_t FooterStatus;
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  /* Blank check of footer finished */
  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
#if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON)
    if(Fee_Gv.Fee_BufferIndex == 0U)
    {
      /* The pattern is blank. Also blank check the footer's management for possible redundancy restoration. */
      Fee_Gv.Fee_BufferIndex = FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET - FEE_SECTION_MARKER_SIZE_AL;
      FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER);
    }
    else
#endif /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
    {
      /* Simulate the read of an empty field */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_SECTION_MARKER_SIZE_AL + FEE_FOOTER_BUFFER_IDX_FOR_CRASH],
          ((uint8)FEE_FLASH_ERASE_VALUE),
          ((uint32)FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL));
      /* Set the Footer's status */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.06,1 */
      FooterStatus = Fee_GetSectionManagementStatus();
      /* Now we know the status of the header and the status of the footer. Decide the section's overall status */
      Fee_DecideSectionStatus(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus, FooterStatus);
      Fee_FooterReadNextStep();
    }
  }
  /* previous flash job has failed */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.SectionManagementRefused,1 */
      /* Simulate the read of a corrupted field */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_SECTION_MARKER_SIZE_AL + FEE_FOOTER_BUFFER_IDX_FOR_CRASH],
          ((uint8)0x00),
          ((uint32)FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL));
      /* Set the Footer's status */
      FooterStatus = Fee_GetSectionManagementStatus();
      /* Now we know the status of the header and the status of the footer. Decide the section's overall status */
      Fee_DecideSectionStatus(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus, FooterStatus);
      Fee_FooterReadNextStep();
    }
    else
    {
      /* Header is written. Read it! */
      FEE_TRIGGER_TRANS(FEE_INIT_READ_FOOTER);
    }
  }
}

/*--------------------------[Fee_SfOnEntryBlankCheckHeaderActive]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckHeaderActive
(
  void
)
{
  /* !LINKSTO Fee.Dsn.BlankCheck.SectionMarkers,1 */
  /* Blank check the active marker in header */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_HEADER_ACTIVE_MARKER_OFFSET,
              FEE_SECTION_MARKER_SIZE_AL))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckHeaderActive]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckHeaderActive
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Read of section 0 headers completed successfully */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.ActiveRefused,1 */
      /* Better consider the section as active. These kind of branches shall never be reached anyway. */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET],
                ((uint8)FEE_SECTION_STATUS_ACTIVE),
                ((uint32)FEE_SECTION_MARKER_SIZE_AL));
    }
    else
    {
      if (MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult)
      {
        /* Simulate the read of an empty field */
        TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET],
                  ((uint8)FEE_FLASH_ERASE_VALUE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
      else
      {
        /* Simulate the read of a marked field */
        TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET],
                  ((uint8)FEE_SECTION_STATUS_ACTIVE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
    }
    /* Check the Header management */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_HEADER);
  }
}

/*--------------------------[Fee_SfOnEntryBlankCheckFooterActive]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckFooterActive
(
  void
)
{
  /* !LINKSTO Fee.Dsn.BlankCheck.SectionMarkers,1 */
  /* Blank check the active marker in header */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) - FEE_FOOTER_BUFFER_IDX_FOR_CRASH,
                             FEE_FOOTER_BUFFER_IDX_FOR_CRASH + FEE_SECTION_MARKER_SIZE_AL))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckFooterActive]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckFooterActive
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Read of section 0 headers completed successfully */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.ActiveRefused,1 */
      /* Better consider the section as active. These kind of branches shall never be reached anyway. */
      TS_MemSet(Fee_Gv.FeeBuffPtr,
                ((uint8)FEE_SECTION_STATUS_ACTIVE),
                ((uint32)FEE_SECTION_MARKER_SIZE_AL + FEE_FOOTER_BUFFER_IDX_FOR_CRASH));
    }
    else
    {
      if (MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult)
      {
        /* Simulate the read of an empty field */
        TS_MemSet(Fee_Gv.FeeBuffPtr,
                  ((uint8)FEE_FLASH_ERASE_VALUE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL + FEE_FOOTER_BUFFER_IDX_FOR_CRASH));
      }
      else
      {
        /* Simulate the read of a marked field */
        TS_MemSet(Fee_Gv.FeeBuffPtr,
                  ((uint8)FEE_SECTION_STATUS_ACTIVE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL + FEE_FOOTER_BUFFER_IDX_FOR_CRASH));
      }
    }
    /* Check the Footer's management */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER);
  }
}

/*--------------------------[Fee_SfOnEntryBlankCheckHeaderErasable]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckHeaderErasable
(
  void
)
{
  /* !LINKSTO Fee.Dsn.BlankCheck.SectionMarkers,1 */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex),
                             FEE_SECTION_MARKER_SIZE_AL))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckHeaderErasable]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckHeaderErasable
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Read of section 0 headers completed successfully */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.ErasableRefused,1 */
      /* Better consider the section as non-erasable. These kind of branches shall never be reached anyway. */
      TS_MemSet(Fee_Gv.FeeBuffPtr,
                ((uint8)FEE_FLASH_ERASE_VALUE),
                ((uint32)FEE_SECTION_MARKER_SIZE_AL));
    }
    else
    {
      if (MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult)
      {
        /* Simulate the read of an empty field */
        TS_MemSet(Fee_Gv.FeeBuffPtr,
                  ((uint8)FEE_FLASH_ERASE_VALUE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
      else
      {
        /* Simulate the read of an marked field */
        TS_MemSet(Fee_Gv.FeeBuffPtr,
                  ((uint8)FEE_SECTION_STATUS_ERASABLE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
    }
    /* Check the Active marker for header */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_HEADER_ACTIVE);
  }
}

/*--------------------------[Fee_SfOnEntryBlankCheckFooterErasable]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBlankCheckFooterErasable
(
  void
)
{
  /* !LINKSTO Fee.Dsn.BlankCheck.SectionMarkers,1 */
  /* FEE_HEADER_ACTIVE_MARKER_OFFSET is intentionally used here as the footer's markers swap positions compared to header's */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_HEADER_ACTIVE_MARKER_OFFSET,
                             FEE_SECTION_MARKER_SIZE_AL))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBlankCheckFooterErasable]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfBlankCheckFooterErasable
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();
  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Read of section 0 headers completed successfully */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.BlankCheck.ErasableRefused,1 */
      /* Better consider the section as non-erasable. These kind of branches shall never be reached anyway. */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET + FEE_FOOTER_BUFFER_IDX_FOR_CRASH],
                ((uint8)FEE_FLASH_ERASE_VALUE),
                ((uint32)FEE_SECTION_MARKER_SIZE_AL));
    }
    else
    {
      if (MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult)
      {
        /* Simulate the read of an empty field */
        TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET + FEE_FOOTER_BUFFER_IDX_FOR_CRASH],
                  ((uint8)FEE_FLASH_ERASE_VALUE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
      else
      {
        /* Simulate the read of an marked field */
        TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET + FEE_FOOTER_BUFFER_IDX_FOR_CRASH],
                  ((uint8)FEE_SECTION_STATUS_ERASABLE),
                  ((uint32)FEE_SECTION_MARKER_SIZE_AL));
      }
    }
    /* Check the Active marker for header */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER_ACTIVE);
  }
}
#endif /* #if (FEE_USE_BLANKCHECK == STD_ON) */

/*--------------------------[Fee_SfOnEntryInitReadHeader]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryInitReadHeader
(
  void
)
{
#if (FEE_USE_BLANKCHECK == STD_OFF)
  /* Clear the content of the buffer */
  TS_MemSet(Fee_Gv.FeeBuffPtr, ((uint8)FEE_FLASH_ERASE_VALUE), FEE_HEADER_SIZE);

  if (E_OK == Fee_LowerLayer_Read(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex),
                       Fee_Gv.FeeBuffPtr,
                       FEE_HEADER_SIZE))
#else /* #if (FEE_USE_BLANKCHECK == STD_ON) */
  /* Call flash read to read the header 0 fields and their corresponding markers */
  if (E_OK == Fee_LowerLayer_Read(FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_SECTION_MARKER_SIZE_AL,
                       &Fee_Gv.FeeBuffPtr[FEE_SECTION_MARKER_SIZE_AL],
                       FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL))
#endif /* #if (FEE_USE_BLANKCHECK == STD_ON) */
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfInitReadHeader]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfInitReadHeader
(
  void
)
{
  Fee_SectionStatus_t TempSectionStatus;
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }
  /* Read of section 0 headers completed successfully */
  else
  {
    if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
    {
      /* If the current header has an invalid ConfigId mark the section as Inconsistent */
      TempSectionStatus = Fee_GetSectionManagementStatus();
      Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = TempSectionStatus;
    }
    /* previous flash job has failed */
    else
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.FailureHandling.Behaviour.Startup1.HeaderFailed,1 */
      Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = FEE_SECTION_INCONSISTENT;
    }
#if (FEE_USE_BLANKCHECK == STD_ON)
    /* Check the Footer's Erasable marker */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_FOOTER_ERASABLE);
#else /* #if (FEE_USE_BLANKCHECK == STD_ON) */
    /* Check the Footer */
    FEE_TRIGGER_TRANS(FEE_INIT_READ_FOOTER);
#endif /* #if (FEE_USE_BLANKCHECK == STD_ON) */
  }
}

/*--------------------------[Fee_SfOnEntryInitReadFooter]-------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryInitReadFooter
(
  void
)
{
#if (FEE_USE_BLANKCHECK == STD_OFF)
  /* Clear the content of the buffer */
  TS_MemSet(Fee_Gv.FeeBuffPtr, ((uint8)FEE_FLASH_ERASE_VALUE), ((uint32)FEE_HEADER_SIZE + (uint32)FEE_FOOTER_BUFFER_IDX_FOR_CRASH));
  /* Call flash read to read the footer and its corresponding markers */
  if (E_OK == Fee_LowerLayer_Read(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) - FEE_FOOTER_BUFFER_IDX_FOR_CRASH,
                       Fee_Gv.FeeBuffPtr,
                       (Fee_LowerLayer_LengthType)FEE_HEADER_SIZE + FEE_FOOTER_BUFFER_IDX_FOR_CRASH))
#else /* #if (FEE_USE_BLANKCHECK == STD_OFF) */
  /* Call flash read to read the footer */
  if (E_OK == Fee_LowerLayer_Read(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) + FEE_SECTION_MARKER_SIZE_AL,
                       &Fee_Gv.FeeBuffPtr[FEE_FOOTER_BUFFER_IDX_FOR_CRASH + FEE_SECTION_MARKER_SIZE_AL],
                       FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL))
#endif /* #if (FEE_USE_BLANKCHECK == STD_OFF) */
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfInitReadFooter]--------------------------*/

FUNC(void, FEE_CODE) Fee_SfInitReadFooter
(
  void
)
{
  Fee_SectionStatus_t FooterStatus;
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  /* Read of footer finished */
  else
  {
    /* Read of footer completed successfully */
    if((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.06,1 */
      FooterStatus = Fee_GetSectionManagementStatus();
    }
    /* previous flash job failed */
    else
    {
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dns.FailureHandling.Behaviour.Startup1.FooterFailed,1 */
      FooterStatus = FEE_SECTION_INCONSISTENT;
    }

    /* Now we know the status of the header and the status of the footer. Decide the section's overall status */
    Fee_DecideSectionStatus(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus, FooterStatus);
    Fee_FooterReadNextStep();
  }
}

/*--------------------------[Fee_SfOnEntryInitFillCache]---------------------*/
#if (FEE_USE_BLANKCHECK == STD_OFF)
FUNC(void, FEE_CODE) Fee_SfOnEntryInitFillCache
(
  void
)
{
  /* First read of block infos will always be of a FEE_INIT_BUFFER_SIZE */
  Fee_Gv.Fee_BufferIndex = FEE_INIT_BUFFER_SIZE;

  Fee_Gv.FeeWorkingDataAddress = FEE_DATA_ADDRESS(Fee_Gv.FeeWorkingSectionIndex);
  Fee_Gv.FeeWorkingInfoAddress = FEE_FIRST_BLOCK_INFO_ADDRESS(Fee_Gv.FeeWorkingSectionIndex);

  /* Call flash read to read the block infos to buffer from the section to be
   * filled into cache */
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.FillCacheWithBlockInfos,1 */
  if (E_OK == Fee_LowerLayer_Read(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) - FEE_INIT_BUFFER_SIZE, Fee_Gv.FeeBuffPtr, FEE_INIT_BUFFER_SIZE))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfInitFillCache]----------------------------*/

FUNC(void, FEE_CODE) Fee_SfInitFillCache
(
  void
)
{
  boolean FreeSectionSpaceFound = FALSE; /* if cache filling is completed */
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* Fill the Cache using the block infos read from flash to buffer */
    FreeSectionSpaceFound = Fee_FillCache();

    if(FALSE == FreeSectionSpaceFound)
    {
      /* If block infos are yet to be read from the current section */
      Fee_CheckExitCaching();
    }
    else
    {
      /* Section cached. */
      Fee_SectionCachedGoToNextStep();
    }
  }

  /* previous flash job failed */
  else
  {
    /* !LINKSTO Fee.Dsn.FlashRead.BlockInfos.Fails,1 */
    (void)Fee_FlsJobFailed();
    FEE_TRIGGER_TRANS(FEE_INIT_BLOCK_BY_BLOCK);
  }
}

/*--------------------------[Fee_SfOnEntryInitBlockByBlock]---------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryInitBlockByBlock
(
  void
)
{
  /* The last block info found in the previous buffer valid or not led to and FeeInitializationInfoAddress update.
   * Otherwise, if the last block infos corresponding area has been found empty than we must take
   * Fee_NumberOfMarginBlockInfos into consideration */
  if (E_OK == Fee_LowerLayer_Read(Fee_Gv.FeeWorkingInfoAddress - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE),
                       &Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex - (uint16)FEE_BLOCKINFO_SIZE],
                       FEE_BLOCKINFO_SIZE))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfInitBlockByBlock]----------------------------*/

FUNC(void, FEE_CODE) Fee_SfInitBlockByBlock
(
  void
)
{
  boolean FreeSectionSpaceFound = FALSE; /* if cache filling is completed */

  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* Fill the Cache using the block infos read from flash to buffer */
    FreeSectionSpaceFound = Fee_FillCache();

    /* This is the ultimate exit condition:
     *  */
    if(FALSE == FreeSectionSpaceFound)
    {
      if(Fee_Gv.Fee_BufferIndex == 0U)
      {
        /* If block infos are yet to be read from the current section */
        Fee_CheckExitCaching();
      }
      else
      {
        Fee_ReadNextBlockInfo();
      }
    }
    else
    {
      /* Section cached. */
      Fee_SectionCachedGoToNextStep();
    }
  }
  else
  {
    /* Update also the Fee_BufferIndex by going to the next block info */
    Fee_Gv.Fee_BufferIndex -= FEE_BLOCKINFO_SIZE;
    /* !LINKSTO Fee.Dsn.FlashRead.BlockInfoByBlockInfo.Fails,1 */
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      /* Increment LostSectionSize with BBS */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.InvalidLastBlockInfos,1 */
      Fee_Gv.FeeLostSectionSize += FEE_BIGGEST_BLOCK_SIZE;
    }
    else
    {
      /* A failing block stamp read means an interrupted block stamp write.
       * Block data should not be considered as written. */
    }
    (void)Fee_FlsJobFailed();
    /* FeeInitializationInfoAddress must be updated in order to jump over the messed block info("+ 1") */
    /* and eventually empty area */
    Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos + (uint32)1U) * (uint32)FEE_BLOCKINFO_SIZE);
    /* Reset Fee_NumberOfMarginBlockInfos as the failed block info is considered not empty
     * in order to be on the safe side */
    Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;

    Fee_CheckExitCaching();
  }
}

#else /* #if (FEE_USE_BLANKCHECK == STD_OFF) */
/*--------------------------[Fee_SfOnEntryBcWrittenMarker]---------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBcWrittenMarker
(
  void
)
{
  Fee_Gv.FeeWorkingDataAddress = FEE_DATA_ADDRESS(Fee_Gv.FeeWorkingSectionIndex);
  Fee_Gv.FeeWorkingInfoAddress = FEE_FIRST_BLOCK_INFO_ADDRESS(Fee_Gv.FeeWorkingSectionIndex);

  /* Call flash read to read the block infos to buffer from the section to be
   * filled into cache */
  /* !LINKSTO Fee.Dsn.BlankCheck.WrittenMarker,1 */
  if (E_OK == Fee_LowerLayer_BlankCheck(FEE_FOOTER_ADDRESS(Fee_Gv.FeeWorkingSectionIndex) - FEE_VIRTUAL_PAGE_SIZE, FEE_VIRTUAL_PAGE_SIZE))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBcWrittenMarker]----------------------------*/

FUNC(void, FEE_CODE) Fee_SfBcWrittenMarker
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* !LINKSTO Fee.Dsn.BlankCheck.WrittenMarkerBlank,1 */
    /* Clear the first byte of Written Marker to simulate reading erased value */
    TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_BLOCKSTAMP_SIZE_AL],
        ((uint8)FEE_FLASH_ERASE_VALUE),
        ((uint32)1U));
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_BLOCK_STAMP);
  }

  /* blank check failed */
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      /* The blank check job was refused twice. Skip the BI */
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.FlashRead.BlockInfoByBlockInfo.Fails,1 */
      /* Increment LostSectionSize with BBS */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.InvalidLastBlockInfos,1 */
      Fee_Gv.FeeLostSectionSize += FEE_BIGGEST_BLOCK_SIZE;
      /* FeeInitializationInfoAddress must be updated in order to jump over the messed block info("+ 1") */
      /* and eventually empty area */
      Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos + (uint32)1U) * (uint32)FEE_BLOCKINFO_SIZE);
      /* Reset Fee_NumberOfMarginBlockInfos as the failed block info is considered not empty
       * in order to be on the safe side */
      Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;

      Fee_CheckExitCaching();
    }
    else
    {
      /* Mark the first byte of Written Marker to simulate reading maker's value */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_BLOCKSTAMP_SIZE_AL],
          ((uint8)FEE_WRITTEN_MARKER_PATTERN),
          ((uint32)1U));
      FEE_TRIGGER_TRANS(FEE_READ_BLOCK_STAMP);
    }
  }
}

/*--------------------------[Fee_SfOnEntryBcBlockStamp]---------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryBcBlockStamp
(
  void
)
{
  /* !LINKSTO Fee.Dsn.BlankCheck.BlockStamp,1 */
  Fee_LowerLayer_AddressType BlankCheckAddress;

  BlankCheckAddress = (Fee_Gv.FeeWorkingInfoAddress
                       - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE));
  /* If something was found with the last read the FeeInitializationInfoAddress
   * has been already updated to the next one (and Fee_NumberOfMarginBlockInfos is 0).
   * Else, if the area was found empty we must skip the empty area and read
   * the next possible block info. */
  /* Read the next block info */
  if (E_OK == Fee_LowerLayer_BlankCheck(BlankCheckAddress, FEE_BLOCKSTAMP_SIZE_AL))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  /* flash job was refused */
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfBcBlockStamp]----------------------------*/

FUNC(void, FEE_CODE) Fee_SfBcBlockStamp
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* Set the EmptyBlockInfoDetected flag because an empty block info was detected */
    Fee_Gv.Fee_NumberOfMarginBlockInfos++;
    /* First empty block management information found, try to read the second block info */
    if (Fee_Gv.Fee_NumberOfMarginBlockInfos < FEE_DATA_INFO_MARGIN)
    {
      /* do nothing, go to the next BI */
      Fee_BcNextBlockInfo();
    }
    /* The configured number of empty block management info found, set the completed flag */
    else
    {
      /* If the last block info was inconsistent than possibly written biggest blocks size
       * must be considered. Otherwise Fee_Gv.FeeLostSectionSize should be 0 */
      Fee_Gv.FeeWorkingDataAddress += Fee_Gv.FeeLostSectionSize;
      /* Set the flag to indicate that all block infos in the current section are read */
      Fee_SectionCachedGoToNextStep();
    }
  }
  else
  {
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      /* The blank check job was refused twice. Skip the BI */
      (void)Fee_FlsJobFailed();
      /* !LINKSTO Fee.Dsn.FlashRead.BlockInfoByBlockInfo.Fails,1 */
      /* Increment LostSectionSize with BBS */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.InvalidLastBlockInfos,1 */
      Fee_Gv.FeeLostSectionSize += FEE_BIGGEST_BLOCK_SIZE;
      /* FeeInitializationInfoAddress must be updated in order to jump over the messed block info("+ 1") */
      /* and eventually empty area */
      Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos + (uint32)1U) * (uint32)FEE_BLOCKINFO_SIZE);
      /* Reset Fee_NumberOfMarginBlockInfos as the failed block info is considered not empty
       * in order to be on the safe side */
      Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;

      Fee_CheckExitCaching();
    }
    else
    {
      /* !LINKSTO Fee.Dsn.BlankCheck.BlockStamp,1 */
      FEE_TRIGGER_TRANS(FEE_READ_BLOCK_STAMP);
    }
  }
}

/*--------------------------[Fee_SfOnEntryReadBlockStamp]---------------------*/

FUNC(void, FEE_CODE) Fee_SfOnEntryReadBlockStamp
(
  void
)
{
  /* The last block info found in the previous buffer valid or not led to and FeeInitializationInfoAddress update.
   * Otherwise, if the last block infos corresponding area has been found empty than we must take
   * Fee_NumberOfMarginBlockInfos into consideration */
  if (E_OK == Fee_LowerLayer_Read(Fee_Gv.FeeWorkingInfoAddress - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE),
                       Fee_Gv.FeeBuffPtr,
                       FEE_BLOCKSTAMP_SIZE))
  {
    /* Reset retry counter */
    Fee_Gv.FeeRetryStateCounter = FEE_STATE_MAX_RETRIES;
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_SfReadBlockStamp]----------------------------*/

FUNC(void, FEE_CODE) Fee_SfReadBlockStamp
(
  void
)
{
  FEE_GET_FLASH_JOB_RESULT();

  if (MEMIF_JOB_PENDING == Fee_Gv.FeeFlashJobResult)
  {
    /* Do nothing; flash job is not complete */
  }

  else if ((MEMIF_JOB_OK == Fee_Gv.FeeFlashJobResult) && (!FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK)))
  {
    /* !LINKSTO Fee.Dsn.BlankCheck.BlockStampBlank,1 */
    Fee_ProcessBlockInfo();
    /* Update the block info address */
    Fee_Gv.FeeWorkingInfoAddress -= FEE_BLOCKINFO_SIZE;
    /* If empty block infos had been found before we should take them into acount */
    Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE);
    /* Something different than empty was detected, reset the counter */
    Fee_Gv.Fee_NumberOfMarginBlockInfos = 0;

    Fee_CheckExitCaching();
  }
  else
  {
    /* !LINKSTO Fee.Dsn.FlashRead.BlockInfoByBlockInfo.Fails,1 */
    if(FEE_CHECK_FLAG(FEE_FLASH_FINAL_REFUSAL_MASK))
    {
      /* Increment LostSectionSize with BBS */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.InvalidLastBlockInfos,1 */
      Fee_Gv.FeeLostSectionSize += FEE_BIGGEST_BLOCK_SIZE;
    }
    else
    {
      /* A failing block stamp read means an interrupted block stamp write.
       * Block data should not be considered as written. */
    }
    (void)Fee_FlsJobFailed();
    /* FeeInitializationInfoAddress must be updated in order to jump over the messed block info("+ 1") */
    /* and eventually empty area */
    Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos + (uint32)1U) * (uint32)FEE_BLOCKINFO_SIZE);
    /* Reset Fee_NumberOfMarginBlockInfos as the failed block info is considered not empty
     * in order to be on the safe side */
    Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;

    Fee_CheckExitCaching();
  }
}
#endif /* #if FEE_USE_BLANKCHECK == STD_ON */
/*==================[internal constants]====================================*/

/*==================[internal function definitions]=========================*/

/*--------------------------[Fee_FooterReadNextStep]-------------------------*/

INLINE STATIC FUNC(void, FEE_CODE) Fee_FooterReadNextStep
(
  void
)
{
  Fee_Gv.Fee_BufferIndex = 0U;
  if(Fee_Gv.FeeWorkingSectionIndex != (FEE_NUMBER_OF_SECTIONS - 1U))
  {
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.02,1 */
    Fee_Gv.FeeWorkingSectionIndex = Fee_Gv.FeeWorkingSectionIndex + (uint8)1;
#if FEE_USE_BLANKCHECK == STD_ON
    /* Proceed with checking next section's header */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_HEADER_ERASABLE);
#else /* #if FEE_USE_BLANKCHECK == STD_ON */
    /* Proceed with next section's header */
    FEE_TRIGGER_TRANS(FEE_INIT_READ_HEADER);
#endif /* #if FEE_USE_BLANKCHECK == STD_ON */
  }
  else
  {
    /* Find the active section and start searching for blocks */
    Fee_HandleSectionChaining();

    /* Go to the Active section if exist, otherwise to the newest full section */
    Fee_Gv.FeeWorkingSectionIndex = Fee_Gv.FeeActiveSectionIndex;
    /* We have to verify if the "to be Active" section is really Active and it is ready to be used */
    if(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus == FEE_SECTION_ACTIVE)
    {
#if FEE_USE_BLANKCHECK == STD_ON
      /* Clear the Fee buffer for simulating Written Marker read */
      TS_MemSet(&Fee_Gv.FeeBuffPtr[FEE_BLOCKSTAMP_SIZE_AL],
          ((uint8)FEE_FLASH_ERASE_VALUE),
          ((uint32)FEE_VIRTUAL_PAGE_SIZE));
      /* !LINKSTO Fee.Dsn.BlankCheck.WrittenMarker,1 */
      FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_W_MARKER);
#else
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfos.01,1 */
      FEE_TRIGGER_TRANS(FEE_INIT_FILL_CACHE);
#endif
    }
    else
    {
      Fee_SectionCachedGoToNextStep();
    }
  }
}

/*--------------------------[Fee_CheckExitCaching]----------------------------------*/
STATIC FUNC(void, FEE_CODE) Fee_CheckExitCaching
(
  void
)
{
  /* This exit condition checks whether the next block info to be read is not already in the margin area.
   * It's useful for read failures and also as an optimized exit condition for anticipating margin area
   * and not reading the whole margin to find out that it's empty anyway. If the margin is corrupted and
   * Fee cannot find 4 consecutive blank block infos, this condition offers an exit point as well. */
  if (Fee_Gv.FeeWorkingInfoAddress <
      (Fee_Gv.FeeWorkingDataAddress
       + (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos
                                            + (uint32)FEE_DATA_INFO_MARGIN)
                            * (uint32)FEE_BLOCKINFO_SIZE)))
  {
    /* The section is cached */
    Fee_SectionCachedGoToNextStep();
  }
  else
  {
    /* There is still more data to be cached in this section. */
    switch(Fee_State)
    {
#if FEE_USE_BLANKCHECK == STD_OFF
    case FEE_INIT_FILL_CACHE:
      Fee_ReadNextBufferOfBlockInfos();
      break;

    case FEE_INIT_BLOCK_BY_BLOCK:
      Fee_ReadNextBlockInfo();
      break;

#else /* FEE_USE_BLANKCHECK == STD_OFF */
      /* !LINKSTO Fee.Dsn.BlankCheck.WrittenMarker,1 */
    case FEE_BLANK_CHECK_W_MARKER:
    case FEE_BLANK_CHECK_BLOCK_STAMP:
    case FEE_READ_BLOCK_STAMP:
      Fee_BcNextBlockInfo();
      break;
#endif /* FEE_USE_BLANKCHECK == STD_OFF */

    /* CHECK: NOPARSE */
    default:
      FEE_UNREACHABLE_CODE_ASSERT(FEE_INTERNAL_API_ID);
      break; /* Caution: this 'break' is required by MISRA-C:2004 */
      /* CHECK: PARSE */
    }
  }
}

/*--------------------------[Fee_ValidateDataAddress]-------------------------------*/
STATIC FUNC(boolean, FEE_CODE) Fee_ValidateDataAddress
(
  const uint16 BlockLength,
  const Fee_LowerLayer_AddressType BlockDataAddress
)
{
  boolean RetValue = FALSE;
  /* if block length is invalid then block is either erased or invalidated and no data address validation is needed */
  if (BlockLength != FEE_INVALID_SIZE)
  {
    if ((BlockDataAddress >= Fee_Gv.FeeWorkingDataAddress) && (BlockDataAddress <= Fee_Gv.FeeWorkingInfoAddress))
    {
      RetValue = TRUE;
    }
  }
  else
  {
    RetValue = TRUE;
  }
  return RetValue;
}

/*--------------------------[Fee_ProcessBlockInfo]----------------------------------*/
INLINE STATIC FUNC(void, FEE_CODE) Fee_ProcessBlockInfo
(
  void
)
{
  /* Get data from the block info */
  const uint16 BlockLength =
      FEE_READ_WORD(Fee_Gv.FeeBuffPtr, Fee_Gv.Fee_BufferIndex + FEE_BLOCKLENGTH_INDEX);
  const uint16 BlockNumber =
      FEE_READ_WORD(Fee_Gv.FeeBuffPtr, Fee_Gv.Fee_BufferIndex + FEE_BLOCKNUMBER_INDEX);
  const Fee_LowerLayer_AddressType BlockDataAddress =
      FEE_READ_DWORD(Fee_Gv.FeeBuffPtr, Fee_Gv.Fee_BufferIndex + FEE_BLOCKDATAADDRESS_INDEX);
#if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON)
  const uint8 BlkSCounter = Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex + FEE_BLKSCOUNTER_INDEX];
#endif /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
  const uint8 Checksum = Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex + FEE_CHECKSUM_INDEX];
  const Std_ReturnType ComputedChecksum =
      Fee_CalculateChecksum(&(Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex]), FEE_CHECKSUM_NUMBER_OF_BYTES);
  uint16 IntBlockIndex;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksOFF,1 */
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksON,1 */
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInconsistent.02,1 */
  /* Validate the checksum field of the block info together with the block address location */
  if ((ComputedChecksum == Checksum) && (Fee_ValidateDataAddress(BlockLength, BlockDataAddress) == TRUE))
  {
#if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON)
    if (BlkSCounter != Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SCounter)
    {
      /* The block info is not fully written. Some it might be and the other part
       * is a possible shadow of an older writing. Considering that some projects write a particular block
       * many times, the checksum might very well be right. (this case applies if either the ECC matches or it's
       * deactivated) This measure is used in order to avoid an end pattern for the block stamp. */
    }
    else
#endif /* #if (FEE_CONSISTENCY_PATTERN_ENABLED == STD_ON) */
    {
      IntBlockIndex = Fee_SearchConfigTable(BlockNumber);
      /* Check whether the block number has been configured in the BlockCfg Table */
      if (IntBlockIndex < FEE_NO_OF_CONFIGURED_BLOCKS)
      {
        Fee_BlockCfgPtr = &Fee_BlockCfg[IntBlockIndex];
        /* Check whether the found block needs to be chached */
        Fee_CacheIfNewerInstance(BlockDataAddress, BlockLength, IntBlockIndex);
      }
      /* The block is not present in the new configuration */
      else
      {
#if (FEE_NUMBER_NOT_CONFIGURED_BLOCKS > 0U)
        uint32 NotConfigFoundBlocksUsedSize = Fee_GetNotConfigFoundBlocksUsedSize();
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.SwitchNotConfiguredBlocks,1 */
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfos.02,1 */
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlocksSearchStop.SwNotConfigBlocksON,1 */
        if(IntBlockIndex == 0xFFFFU)
        {
          if(
              ((Fee_Gv.FeeNbOfNotCfgBlocksFound + FEE_NO_OF_CONFIGURED_BLOCKS) < FEE_TOTAL_NUMBER_OF_BLOCKS)
              &&
              (BlockLength <= FEE_NOT_CONFIGURED_BLOCKS_DATA_SIZE)
              &&
              (( FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength)
                  + FEE_BLOCKINFO_SIZE
                  + NotConfigFoundBlocksUsedSize
              )
                  <=
                  FEE_NOT_CONFIGURED_BLOCKS_TOTAL_SIZE
              )
          )
          {
            IntBlockIndex = Fee_Gv.FeeNbOfNotCfgBlocksFound + FEE_NO_OF_CONFIGURED_BLOCKS;
            /* memorize its configuration */
            Fee_NotCfgBlocks[Fee_Gv.FeeNbOfNotCfgBlocksFound].FeeBlockSize = BlockLength;
            Fee_NotCfgBlocks[Fee_Gv.FeeNbOfNotCfgBlocksFound].FeeBlockNumber = BlockNumber;
            Fee_NotCfgBlocks[Fee_Gv.FeeNbOfNotCfgBlocksFound].FeeBlockAlignedSize = (uint16)FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
            Fee_BlockCfgPtr = &Fee_NotCfgBlocks[Fee_Gv.FeeNbOfNotCfgBlocksFound];
            Fee_Gv.FeeNbOfNotCfgBlocksFound++;
            /* This block is now the first time found and cached */
            (void)Fee_CacheBlockAddress(Fee_Gv.FeeCache, BlockDataAddress, BlockLength, IntBlockIndex);
          }
          else
          {
            /* !LINKSTO Fee.FeeNumberOfNotConfigBlocks.BlocksLost,1 */
            /* The current block can not be switched and it will be lost. */
            FEE_DET_REPORT_ERROR(FEE_MAINFUNCTION_API_ID, FEE_E_NOT_CFG_BLK_LOST);
            FEE_SET_FLAG(FEE_NOT_CFG_BLK_LOST_MASK);
            /* Update the data address with the offset given by the block's data address and it's length,
             * so that it points to the start of the next block.
             * Cache cannot be updated as this block is not configured now */
            if(BlockLength != FEE_INVALID_SIZE)
            {
              Fee_Gv.FeeWorkingDataAddress = BlockDataAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
            }
            else
            {
              /* The block was either invalidated or erased by the user.
               * Therefore the data address must not be updated because no data was written. */
            }
          }
        }
        else
        {
          uint32 OldAlignedSize = Fee_NotCfgBlocks[(IntBlockIndex - FEE_NO_OF_CONFIGURED_BLOCKS)].FeeBlockAlignedSize;
          if(
              (BlockLength <= FEE_NOT_CONFIGURED_BLOCKS_DATA_SIZE)
              &&
              (
                  ( FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength)
                      + NotConfigFoundBlocksUsedSize
                      - OldAlignedSize
                  )
                  <=
                  FEE_NOT_CONFIGURED_BLOCKS_TOTAL_SIZE
              )
          )
          {
            Fee_BlockCfgPtr = &Fee_NotCfgBlocks[(IntBlockIndex - FEE_NO_OF_CONFIGURED_BLOCKS)];
            Fee_CacheIfNewerInstance(BlockDataAddress, BlockLength, IntBlockIndex);
          }
          else
          {
            /* !LINKSTO Fee.FeeNumberOfNotConfigBlocks.BlocksLost,1 */
            /* The current block can not be switched and it will be lost. */
            FEE_DET_REPORT_ERROR(FEE_MAINFUNCTION_API_ID, FEE_E_NOT_CFG_BLK_LOST);
            FEE_SET_FLAG(FEE_NOT_CFG_BLK_LOST_MASK);
            /* Update the data address with the offset given by the block's data address,
             * it's length, so that it points to the start of the next block.
             * Cache cannot be updated as this block is not configured now */
            Fee_Gv.FeeWorkingDataAddress = BlockDataAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
          }
        }
#else
        /* Update the data address with the offset given by the block's data address and it's length,
         * so that it points to the start of the next block.
         * Cache cannot be updated as this block is not configured now */
        if(BlockLength != FEE_INVALID_SIZE)
        {
          Fee_Gv.FeeWorkingDataAddress = BlockDataAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
        }
        else
        {
          /* The block was either invalidated or erased by the user.
           * Therefore the data address must not be updated because no data was written. */
        }
#endif
      }
    }
  }
  else
  {
    /* The block info is not valid. Consider the worst case scenario */
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.InvalidLastBlockInfos,1 */
    Fee_Gv.FeeLostSectionSize += FEE_BIGGEST_BLOCK_SIZE;
  }
}

/*------------------------------[Fee_CacheIfPreconditionsMet]--------------------------*/
STATIC FUNC(void, FEE_CODE) Fee_CacheIfNewerInstance
(
  Fee_LowerLayer_AddressType BlockAddress,
  uint16 BlockLength,
  uint16 BlockIndex
)
{
  if (Fee_Gv.FeeCache[BlockIndex] == FEE_ZERO_BLOCKADDRESS)
  {
#if (FEE_NUMBER_NOT_CONFIGURED_BLOCKS > 0U)
    if (BlockIndex >= FEE_NO_OF_CONFIGURED_BLOCKS)
    {
      (void)Fee_CacheBlockAddress(Fee_Gv.FeeCache, BlockAddress, BlockLength, BlockIndex);
    }
    else
#endif
    {
      if(TRUE == Fee_CacheBlockAddress(Fee_Gv.FeeCache, BlockAddress, BlockLength, BlockIndex))
      {
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlocksSearchStop.SwNotConfigBlocksOFF,1 */
        Fee_Gv.FeeNbOfBlocksFound++;
      }
    }
  }
  else
  {
     /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoFound,1 */
    /* If the highest priority switch has been detected memorize the addresses of all the blocks that were switched or
     * needs to be switched, just in case the switch will be restarted. */
    if(
        (FEE_CHECK_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK) && (Fee_Gv.FeeWorkingSectionIndex == Fee_Gv.FeeOldestSectionIndex))
        &&
        (Fee_Gv.FeeCache[BlockIndex] >= FEE_DATA_ADDRESS(Fee_Gv.FeeActiveSectionIndex))
        &&
        (Fee_Gv.FeeCache[BlockIndex] < FEE_SECTION_END_ADDRESS(Fee_Gv.FeeActiveSectionIndex))
       )
    {
      (void)Fee_CacheBlockAddress(Fee_Gv.FeeSwRestartCache, BlockAddress, BlockLength, BlockIndex);
    }
    else
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoCacheIfNewer,1 */
      /* Cache the block address only if this instance is newer than previous one cached */
      if (
           (Fee_Gv.FeeCache[BlockIndex] > FEE_SECTION_START_ADDRESS(Fee_Gv.FeeWorkingSectionIndex))
           &&
           (Fee_Gv.FeeCache[BlockIndex] < FEE_SECTION_END_ADDRESS(Fee_Gv.FeeWorkingSectionIndex))
         )
      {
#if (FEE_NUMBER_NOT_CONFIGURED_BLOCKS > 0U)
        /* !LINKSTO Fee.FeeNotConfigBlocks.SizeReconfigured,1 */
        /* Update the not configured block size */
        if (BlockIndex >= FEE_NO_OF_CONFIGURED_BLOCKS)
        {
          Fee_NotCfgBlocks[BlockIndex - FEE_NO_OF_CONFIGURED_BLOCKS].FeeBlockSize = BlockLength;
          Fee_NotCfgBlocks[BlockIndex - FEE_NO_OF_CONFIGURED_BLOCKS].FeeBlockAlignedSize = (uint16)FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
        }
        else
        {
          /* The block is configured. Nothing to be updated. */
        }
#endif
        (void)Fee_CacheBlockAddress(Fee_Gv.FeeCache, BlockAddress, BlockLength, BlockIndex);
      }
      else
      {
        /* Update the data address with the offset given by the block's data address and it's length,
         * so that it points to the start of the next block. */
        if(BlockLength != FEE_INVALID_SIZE)
        {
          Fee_Gv.FeeWorkingDataAddress = BlockAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
        }
        else
        {
          /* The block was either invalidated or erased by the user.
           * Therefore the data address must not be updated because no data was written. */
        }
      }
    }
  }
}

/*------------------------------[Fee_CacheBlockAddress]--------------------------*/
STATIC FUNC(boolean, FEE_CODE) Fee_CacheBlockAddress
(
  Fee_LowerLayer_AddressType * CacheObject,
  Fee_LowerLayer_AddressType BlockAddress,
  uint16 BlockLength,
  uint16 BlockIndex
)
{
  boolean AddressCached = FALSE;

  if(FEE_INVALID_SIZE == BlockLength)
  {
    AddressCached = TRUE;
    if(FEE_INVALID_BLOCKADDRESS(Fee_Gv.FeeWorkingSectionIndex) == BlockAddress)
    {
      /* Store the address of the block data in the cache table */
      CacheObject[BlockIndex] = BlockAddress;
    }
    else
    {
      /* The block must be erased, therefore save its inconsistent address. */
      CacheObject[BlockIndex] = FEE_INCONSISTENT_BLOCKADDRESS(Fee_Gv.FeeWorkingSectionIndex);
    }
  }
  else
  {
    /* Valid block info found, reset the section lost estimated size */
    Fee_Gv.FeeLostSectionSize = 0U;
    /* Check if the data address read from the flash memory is valid
     * (the data address is in the range of addresses of the current section) */
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksON,1 */
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksOFF,1 */
    if ((BlockAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength)) <= (Fee_Gv.FeeWorkingInfoAddress - (FEE_BLOCKINFO_SIZE * FEE_DATA_INFO_MARGIN)))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.WrittenMarker,1 */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.WrittenMarkerValidity,1 */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksOFF,1 */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfoValidity.SwitchNotConfiguredBlocksON,1 */
      /* Check if the WrittenMarker is written even partially */
      if(FEE_HAS_ATLEAST_ONEBYTE_OF(&Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex + FEE_BLOCKSTAMP_SIZE_AL], FEE_WRITTEN_MARKER_PATTERN))
      {
        if ((Fee_BlockCfgPtr->FeeBlockSize == BlockLength) || (BlockIndex >= FEE_NO_OF_CONFIGURED_BLOCKS))
        {
#if (FEE_DYNAMIC_BLOCK_LENGTH == STD_ON)
           /* Update block size only if the block is among the configured ones */
           if(BlockIndex < FEE_NO_OF_CONFIGURED_BLOCKS)
           {
              /* The length must be set to the current configured value, for the case when the same block
               * has already been found, in the same section, with the old length.
               * (just like in the function Fee_SfWriteWrittenMarker) */
              Fee_Gv.FeeOldSizes[BlockIndex] = BlockLength;
           }
#endif
          AddressCached = TRUE;
          /* Store the address of the block data in the cache table */
          CacheObject[BlockIndex] = BlockAddress;
        }
        /* Block size is reconfigured */
        else
        {
#if (FEE_DYNAMIC_BLOCK_LENGTH == STD_ON)
          /* Store the old length of the block */
          /* !LINKSTO Fee.Dsn.DynamicBlockLength.Init,1 */
          Fee_Gv.FeeOldSizes[BlockIndex] = BlockLength;
          AddressCached = TRUE;
          /* Store the address of the block data in the cache table */
          CacheObject[BlockIndex] = BlockAddress;
#endif
        }
      }
      else
      {
        /* Do not cache the block as the data writing was interrupted. */
      }
      /* Update the data address with the offset given by the block's data address, it's length
       * and the length of the block number), so that it points to the start of the next block. */
      Fee_Gv.FeeWorkingDataAddress = BlockAddress + FEE_ALLIGNED_TO_VIRTUAL_PAGE(BlockLength);
    }
    /* In case the data address read from the flash memory is out of bounds,
     * Fee's data address (Fee_Gv.FeeInitializationDataAddress) can not be updated. */
    else
    {
      /* the block was found at an invalid address, therefore this block is not considered */
      /* DataAddress is already updated */
    }
  }

return AddressCached;
}

#if FEE_USE_BLANKCHECK == STD_OFF
/*--------------------------[Fee_FillCache]----------------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_FillCache
(
  void
)
{
  boolean FreeSectionSpaceFound = FALSE;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfosSearch,1 */
  do{
    /* Go to the index which contains the next block info written to the section */
    Fee_Gv.Fee_BufferIndex -= FEE_BLOCKINFO_SIZE;

    /* Check whether all block infos are read */
    if (TRUE == Fee_CheckBlockInfoErased(Fee_Gv.Fee_BufferIndex))
    {
      /* Set the EmptyBlockInfoDetected flag because an empty block info was detected */
      Fee_Gv.Fee_NumberOfMarginBlockInfos++;
      /* First empty block management information found, try to read the second block info */
      if (Fee_Gv.Fee_NumberOfMarginBlockInfos < FEE_DATA_INFO_MARGIN)
      {
        /* do nothing, go to the next BI */
      }
      /* The configured number of empty block management info found, set the completed flag */
      else
      {
        /* If the last block info was inconsistent than possibly written biggest blocks size
         * must be considered. Otherwise Fee_Gv.FeeLostSectionSize should be 0 */
        Fee_Gv.FeeWorkingDataAddress += Fee_Gv.FeeLostSectionSize;
        /* Section completed. Reset Fee_Gv.FeeLostSectionSize */
        Fee_Gv.FeeLostSectionSize = 0U;
        /* Reset the empty block infos counter */
        Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;
        /* Set the flag to indicate that all block infos in the current section are read */
        FreeSectionSpaceFound = TRUE;
      }
    }
    else
    {
      Fee_ProcessBlockInfo();
      /* Update the block info address */
      Fee_Gv.FeeWorkingInfoAddress -= FEE_BLOCKINFO_SIZE;
      /* If empty block infos had been found before we should take them into acount */
      Fee_Gv.FeeWorkingInfoAddress -= (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE);
      /* Something different than empty was detected, reset the counter */
      Fee_Gv.Fee_NumberOfMarginBlockInfos = 0;
    }
  }/* Check each element in the buffer till all block infos are read */
  while (((FALSE == FreeSectionSpaceFound) && (Fee_Gv.Fee_BufferIndex != 0U)) && (Fee_State == FEE_INIT_FILL_CACHE));

  return FreeSectionSpaceFound;
}

/*--------------------------[Fee_ReadNextBufferOfBlockInfos]---------------------*/

STATIC FUNC(void, FEE_CODE) Fee_ReadNextBufferOfBlockInfos
(
  void
)
{
  Fee_LowerLayer_AddressType RemainingInfoSize = ((Fee_Gv.FeeWorkingInfoAddress + (Fee_LowerLayer_AddressType)FEE_BLOCKINFO_SIZE)
                                      - Fee_Gv.FeeWorkingDataAddress)
                                      - (Fee_LowerLayer_AddressType)((uint32)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos + (uint32)FEE_DATA_INFO_MARGIN) * (uint32)FEE_BLOCKINFO_SIZE);

  Fee_LowerLayer_AddressType ReadAddress;
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.FillCacheWithBlockInfos,1 */
  /* Check the remaining size to be read for caching */
  if(RemainingInfoSize < FEE_INIT_BUFFER_SIZE)
  {
    /* Read the remaining chunk of block infos in section */
    Fee_Gv.Fee_BufferIndex = (uint16)((RemainingInfoSize / FEE_BLOCKINFO_SIZE) * FEE_BLOCKINFO_SIZE);
  }
  else
  {
    /* Read a FEE_INIT_BUFFER_SIZE of block infos */
    Fee_Gv.Fee_BufferIndex = FEE_INIT_BUFFER_SIZE;
  }
  ReadAddress = (((Fee_Gv.FeeWorkingInfoAddress + (Fee_LowerLayer_AddressType)FEE_BLOCKINFO_SIZE)
      - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE))
      - (Fee_LowerLayer_AddressType)Fee_Gv.Fee_BufferIndex);
  if (E_OK == Fee_LowerLayer_Read(ReadAddress, Fee_Gv.FeeBuffPtr, Fee_Gv.Fee_BufferIndex))
  {
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  /* flash job was refused */
  else
  {
    Fee_FlsJobRefused();
  }
}

/*--------------------------[Fee_ReadNextBlockInfo]---------------------*/

INLINE STATIC FUNC(void, FEE_CODE) Fee_ReadNextBlockInfo
(
  void
)
{
  Fee_LowerLayer_AddressType ReadAddress;
  /* Go on reading the next block info if there is anything left to read in the problematic buffer size */
  if(Fee_Gv.Fee_BufferIndex >= FEE_BLOCKINFO_SIZE)
  {
    ReadAddress = (Fee_Gv.FeeWorkingInfoAddress - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE));
    /* If something was found with the last read the FeeInitializationInfoAddress
     * has been already updated to the next one (and Fee_NumberOfMarginBlockInfos is 0).
     * Else, if the area was found empty we must skip the empty area and read
     * the next possible block info. */
    /* Read the next block info */
    if (E_OK == Fee_LowerLayer_Read(ReadAddress,
        &Fee_Gv.FeeBuffPtr[Fee_Gv.Fee_BufferIndex - (uint16)FEE_BLOCKINFO_SIZE],
        FEE_BLOCKINFO_SIZE))
    {
      Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
    }
    /* flash job was refused */
    else
    {
      Fee_FlsJobRefused();
    }
  }
  else
  {
    /* The problematic Fee buffer is completely checked */
    Fee_State = FEE_INIT_FILL_CACHE;
    /* Read the next buffer all at once */
    Fee_ReadNextBufferOfBlockInfos();
  }
}

#else /* #if FEE_USE_BLANKCHECK == STD_OFF */
/*--------------------------[Fee_BcNextBlockInfo]---------------------*/

STATIC FUNC(void, FEE_CODE) Fee_BcNextBlockInfo
(
  void
)
{
  Fee_LowerLayer_AddressType BlankCheckAddress;

  BlankCheckAddress = (Fee_Gv.FeeWorkingInfoAddress
                 - (Fee_LowerLayer_AddressType)((uint32)Fee_Gv.Fee_NumberOfMarginBlockInfos * (uint32)FEE_BLOCKINFO_SIZE))
                 + FEE_BLOCKSTAMP_SIZE_AL;
  Fee_State = FEE_BLANK_CHECK_W_MARKER;
  /* If something was found with the last read the FeeInitializationInfoAddress
   * has been already updated to the next one (and Fee_NumberOfMarginBlockInfos is 0).
   * Else, if the area was found empty we must skip the empty area and read
   * the next possible block info. */
  /* Read the next block info */
  if (E_OK == Fee_LowerLayer_BlankCheck(BlankCheckAddress, FEE_VIRTUAL_PAGE_SIZE))
  {
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_PENDING;
  }
  /* flash job was refused */
  else
  {
    Fee_FlsJobRefused();
  }
}
#endif /* #if FEE_USE_BLANKCHECK == STD_OFF */

/*--------------------------[Fee_SectionCachedGoToNextStep]---------------------*/

STATIC FUNC(void, FEE_CODE) Fee_SectionCachedGoToNextStep
(
  void
)
{
  boolean ActiveReachedSecondTime = FALSE;
#if (FEE_NUMBER_NOT_CONFIGURED_BLOCKS != 0U)
  boolean Condition = TRUE;
#endif
  /* before going to the next section update the working addresses for the Active section */
  if(Fee_Gv.FeeInfoAddress == 0U)
  {
    Fee_Gv.FeeInfoAddress = Fee_Gv.FeeWorkingInfoAddress;
    Fee_Gv.FeeDataAddress = Fee_Gv.FeeWorkingDataAddress;
  }
  else
  {
#if (FEE_IMMEDIATE_SPACE_RESERVED != 0U)
    /* !LINKSTO Fee.Dsn.ImmediateSpaceReserved.Init,1 */
    if ((FEE_CHECK_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK)) &&
        (Fee_Gv.FeeInfoAddressReserved == 0U))
    {
      Fee_Gv.FeeInfoAddressReserved = Fee_Gv.FeeWorkingInfoAddress;
      Fee_Gv.FeeDataAddressReserved = Fee_Gv.FeeWorkingDataAddress;
    }
    else
    {
      /* Do nothing */
    }
#endif /* (FEE_IMMEDIATE_SPACE_RESERVED != 0U) */
    /* Nothing to do, Active section has already been checked */
  }
  /* Section completed. Reset Fee_Gv.FeeLostSectionSize and Fee_NumberOfMarginBlockInfos */
  Fee_Gv.FeeLostSectionSize = 0U;
  Fee_Gv.Fee_NumberOfMarginBlockInfos = 0U;
  Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONDECREMENT(Fee_Gv.FeeWorkingSectionIndex);
  /* If the current working section has no data it must not be cached.
   * Therefore search for a section with valid data */
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlockInfos.03,1 */
  while((Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus != FEE_SECTION_ACTIVE) &&
      (ActiveReachedSecondTime == FALSE))
  {
    /* Exit condition, in order to avoid deadlock if no section is valid or no section with markers */
    if(Fee_Gv.FeeWorkingSectionIndex == Fee_Gv.FeeActiveSectionIndex)
    {
      ActiveReachedSecondTime = TRUE;
    }
    else
    {
      Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONDECREMENT(Fee_Gv.FeeWorkingSectionIndex);
    }
  }
  /* Exit condition. We arrived where we started from */
  if(Fee_Gv.FeeWorkingSectionIndex == Fee_Gv.FeeActiveSectionIndex)
  {
    ActiveReachedSecondTime = TRUE;
  }
#if (FEE_NUMBER_NOT_CONFIGURED_BLOCKS != 0U)
  Condition = FEE_CHECK_FLAG(FEE_NOT_CFG_BLK_LOST_MASK);
  if((ActiveReachedSecondTime == TRUE)
      /* Even if all the blocks are found, Fee shall still discover the old instances,
       * in case of possible restart switch situation. */
       /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlocksSearchStop.SwNotConfigBlocksOFF,1 */
      || (((Fee_Gv.FeeNbOfBlocksFound == FEE_NO_OF_CONFIGURED_BLOCKS) &&
          (!FEE_CHECK_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK)))
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlocksSearchStop.SwNotConfigBlocksON,1 */
          && Condition)
    )
#else
  if((ActiveReachedSecondTime == TRUE)
      /* Even if all the blocks are found, Fee shall still discover the old instances,
       * in case of possible restart switch situation. */
       /* !LINKSTO Fee.Dsn.Initialization.Startup1.BlocksSearchStop.SwNotConfigBlocksOFF,1 */
      || ((Fee_Gv.FeeNbOfBlocksFound == FEE_NO_OF_CONFIGURED_BLOCKS) &&
          (!FEE_CHECK_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK)))
    )
#endif
  {
    /* First part of initialization is complete. */
    Fee_StartUp1Finished();
  }
  else
  {
#if FEE_USE_BLANKCHECK == STD_ON
    /* !LINKSTO Fee.Dsn.BlankCheck.WrittenMarker,1 */
    FEE_TRIGGER_TRANS(FEE_BLANK_CHECK_W_MARKER);
#else
    FEE_TRIGGER_TRANS(FEE_INIT_FILL_CACHE);
#endif
  }
}

/*--------------------------[Fee_CheckSectionManagementValidity]----------------------------------*/

STATIC FUNC(Fee_SectionStatus_t, FEE_CODE) Fee_CheckSectionManagementValidity
(
    void
)
{
  const uint8 * OffsetBuffer = &Fee_Gv.FeeBuffPtr[FEE_FOOTER_BUFFER_IDX_FOR_CRASH];
  const uint8 ReadConfigId = FEE_READ_BYTE(OffsetBuffer, FEE_CIDFIELD_OFFSET);
  const uint8 ReadECounterCrc = FEE_READ_BYTE(OffsetBuffer, FEE_ECRCFIELD_OFFSET);
  const uint8 ReadCidCrc = FEE_READ_BYTE(OffsetBuffer, FEE_CRCFIELD_OFFSET);
  const uint8 SectionCounter = FEE_READ_BYTE(OffsetBuffer, FEE_SECTIONCOUNTERFIELD_OFFSET);
  const uint32 EraseCounter = FEE_READ_DWORD(OffsetBuffer, FEE_SECTION_MANAGEMENT_OFFSET);
  uint8 ComputedCrc_SMgt;
  uint8 ComputedCrc_ECnt;
  uint8 i;
  boolean SectionErased = TRUE;
  Fee_SectionStatus_t  RetValue;

  /* Check if the section management data is erased */
  for (i=0U;i<7U;i++)
  {
    if (OffsetBuffer[FEE_SECTION_MANAGEMENT_OFFSET + i] != FEE_FLASH_ERASE_VALUE)
    {
      SectionErased = FALSE;
      break;
    }
    else
    {
      /* Continue checking */
    }
  }

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.01,1 */
  if(SectionErased == TRUE)
  {
    RetValue = FEE_SECTION_ERASED;
  }
  else
  {
    ComputedCrc_SMgt = Crc_CalculateCRC8(&OffsetBuffer[FEE_CIDFIELD_OFFSET], FEE_CID_CRC_COMPUTE_SIZE, FEE_CRC_START_VALUE, TRUE);
    /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.03,2 */
    if((ReadCidCrc == ComputedCrc_SMgt) && ((ReadConfigId == FEE_CONFIG_ID) || (ReadConfigId == FEE_LEGACY_CONFIG_ID)))
    {
      RetValue = FEE_SECTION_EMPTY;
      /* Header valid / section consistent. Memorize its counter. */
      Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SCounter = SectionCounter;

      /* If valid check the erase counter and save its value if it is the highest found until now */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.04,1 */
      /* !LINKSTO Fee.Sections.HeaderSecured,1 */
      ComputedCrc_ECnt = Crc_CalculateCRC8(&OffsetBuffer[FEE_SECTION_MANAGEMENT_OFFSET], FEE_ECOUNTER_CRC_COMPUTE_SIZE, FEE_CRC_START_VALUE, TRUE);
      if(ReadECounterCrc == ComputedCrc_ECnt)
      {
        /* !LINKSTO Fee.SectionEraseCounter,1 */
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.12,1 */
        if(EraseCounter > Fee_Gv.SectionEraseCounter)
        {
          Fee_Gv.SectionEraseCounter = EraseCounter;
        }
        else
        {
          /* This is not the section with the highest counter */
        }
      }
    }
    else
    {
      RetValue = FEE_SECTION_INCONSISTENT;
    }
  }
  return RetValue;
}

/*--------------------------[Fee_GetSectionManagementStatus]----------------------------------*/

STATIC FUNC(Fee_SectionStatus_t, FEE_CODE) Fee_GetSectionManagementStatus
(
    void
)
{
    /* CHECK: NOPARSE */
  boolean (*IsMarkedAsToBeErased)(void);
  boolean (*IsMarkedAsActive)(void);
    /* CHECK: PARSE */

  Fee_SectionStatus_t  SectionManagementStatus;
#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
  boolean FirstBlockInfoEmpty = TRUE;
#endif

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.06,1 */
  SectionManagementStatus = Fee_CheckSectionManagementValidity();

  if(Fee_State == FEE_INIT_READ_HEADER)
  {
    IsMarkedAsActive = &Fee_IsHeaderMarkedAsActive;
    IsMarkedAsToBeErased = &Fee_IsHeaderMarkedAsToBeErased;
  }
  else
  {
    IsMarkedAsActive = &Fee_IsFooterMarkedAsActive;
    IsMarkedAsToBeErased = &Fee_IsFooterMarkedAsToBeErased;
#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
    FirstBlockInfoEmpty = Fee_CheckBlockInfoErased(0U);
#endif
  }

  if(IsMarkedAsToBeErased())
  {
    if(SectionManagementStatus == FEE_SECTION_EMPTY)
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      SectionManagementStatus = FEE_SECTION_ERASABLE;
    }
    else
    {
      /* FEE_SECTION_ERASED  or  FEE_SECTION_INCONSISTENT */
      SectionManagementStatus = FEE_SECTION_ERASABLE_INCONSISTENT;
    }
  }
  else
  {
#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
    if(IsMarkedAsActive() || (FirstBlockInfoEmpty == FALSE))
#else
    if(IsMarkedAsActive())
#endif
    {
      if(SectionManagementStatus == FEE_SECTION_EMPTY)
      {
        /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
        SectionManagementStatus = FEE_SECTION_ACTIVE;
      }
      else
      {
        /* FEE_SECTION_ERASED  or  FEE_SECTION_INCONSISTENT */
        SectionManagementStatus = FEE_SECTION_ACTIVE_INCONSISTENT;
      }
    }
    else
    {
      /* Remains FEE_SECTION_ERASED  or  FEE_SECTION_INCONSISTENT or FEE_SECTION_EMPTY */
    }
  }

  return SectionManagementStatus;
}

/*--------------------------[Fee_IsHeaderMarkedAsToBeErased]---------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_IsHeaderMarkedAsToBeErased
(
    void
)
{
  boolean RetValue;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.MarkerValidity,1 */
  if(FEE_HAS_ATLEAST_ONEBYTE_OF(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ERASABLE_MARKER_OFFSET], FEE_SECTION_STATUS_ERASABLE))
  {
    RetValue = TRUE;
  }
  else
  {
    RetValue = FALSE;
  }
  return RetValue;
}

/*--------------------------[Fee_IsHeaderMarkedAsActive]---------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_IsHeaderMarkedAsActive
(
    void
)
{
  boolean RetValue;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.MarkerValidity,1 */
  if(FEE_HAS_ATLEAST_ONEBYTE_OF(&Fee_Gv.FeeBuffPtr[FEE_HEADER_ACTIVE_MARKER_OFFSET], FEE_SECTION_STATUS_ACTIVE))
  {
    RetValue = TRUE;
  }
  else
  {
    RetValue = FALSE;
  }
  return RetValue;
}

/*--------------------------[Fee_IsFooterMarkedAsToBeErased]---------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_IsFooterMarkedAsToBeErased
(
    void
)
{
  boolean RetValue;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.MarkerValidity,1 */
  if(FEE_HAS_ATLEAST_ONEBYTE_OF(&(Fee_Gv.FeeBuffPtr[(FEE_HEADER_ACTIVE_MARKER_OFFSET + FEE_FOOTER_BUFFER_IDX_FOR_CRASH)]), FEE_SECTION_STATUS_ERASABLE))
  {
    RetValue = TRUE;
  }
  else
  {
    RetValue = FALSE;
  }
  return RetValue;
}

/*--------------------------[Fee_IsFooterMarkedAsActive]---------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_IsFooterMarkedAsActive
(
    void
)
{
  boolean RetValue;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.MarkerValidity,1 */
  if(FEE_HAS_ATLEAST_ONEBYTE_OF(&(Fee_Gv.FeeBuffPtr[(FEE_HEADER_ERASABLE_MARKER_OFFSET + FEE_FOOTER_BUFFER_IDX_FOR_CRASH)]), FEE_SECTION_STATUS_ACTIVE))
  {
    RetValue = TRUE;
  }
  else
  {
    RetValue = FALSE;
  }
  return RetValue;
}

/*--------------------------[Fee_DecideSectionStatus]----------------------------------*/

STATIC FUNC(void, FEE_CODE) Fee_DecideSectionStatus
(
    Fee_SectionStatus_t HeaderStatus,
    Fee_SectionStatus_t FooterStatus
)
{
  Fee_SectionStatus_t * WorkingSectionStatus = &Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus;
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.03,2 */
  /* !LINKSTO Fee.Dns.FailureHandling.Behaviour.Startup1.BothSectionManagementObjectsFailed,1 */
  switch(HeaderStatus)
  {
  case FEE_SECTION_ERASED:
    if((FooterStatus == FEE_SECTION_ACTIVE_INCONSISTENT) ||
        (FooterStatus == FEE_SECTION_ERASABLE_INCONSISTENT) ||
        (FooterStatus == FEE_SECTION_ERASED))
    {
      *WorkingSectionStatus = FEE_SECTION_INCONSISTENT;
    }
    else
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FooterStatus;
    }
    break;

  case FEE_SECTION_INCONSISTENT:
    if((FooterStatus == FEE_SECTION_ACTIVE) ||
        (FooterStatus == FEE_SECTION_ERASABLE) ||
        (FooterStatus == FEE_SECTION_EMPTY))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FooterStatus;
    }
    else
    {
      *WorkingSectionStatus = FEE_SECTION_INCONSISTENT;
    }
    break;

  case FEE_SECTION_EMPTY:
    if(FooterStatus == FEE_SECTION_ERASED)
    {
      *WorkingSectionStatus = FEE_SECTION_NO_FOOTER;
    }
    else if((FooterStatus == FEE_SECTION_INCONSISTENT) ||
        (FooterStatus == FEE_SECTION_EMPTY))
    {
      *WorkingSectionStatus = FEE_SECTION_EMPTY;
    }
    else if((FooterStatus == FEE_SECTION_ACTIVE) ||
        (FooterStatus == FEE_SECTION_ACTIVE_INCONSISTENT))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
      *WorkingSectionStatus = FEE_SECTION_ACTIVE;
    }
    else /* FEE_SECTION_ERASABLE_INCONSISTENT or FEE_SECTION_ERASABLE */
    {
#if (FEE_USE_BLANKCHECK == STD_ON)
      /* !LINKSTO Fee.Dsn.BlankCheck.ErasableBitFlip,1 */
      /* The status remains empty. */
#else /* #if (FEE_USE_BLANKCHECK == STD_ON) */
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE;
#endif /* #if (FEE_USE_BLANKCHECK == STD_ON) */
    }
    break;

  case FEE_SECTION_ACTIVE:
    if((FooterStatus == FEE_SECTION_ERASABLE) ||
        (FooterStatus == FEE_SECTION_ERASABLE_INCONSISTENT))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE;
    }
    else
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
      *WorkingSectionStatus = FEE_SECTION_ACTIVE;
    }
    break;
  case FEE_SECTION_ERASABLE:
    if((FooterStatus == FEE_SECTION_EMPTY) ||
        (FooterStatus == FEE_SECTION_ACTIVE))
    {
#if (FEE_USE_BLANKCHECK == STD_ON)
      /* !LINKSTO Fee.Dsn.BlankCheck.ErasableBitFlip,1 */
      *WorkingSectionStatus = FEE_SECTION_ACTIVE;
#else
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE_HEADER;
#endif
    }
    else
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE;
    }
    break;
  case FEE_SECTION_ACTIVE_INCONSISTENT:
    if((FooterStatus == FEE_SECTION_EMPTY) ||
        (FooterStatus == FEE_SECTION_ACTIVE))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.07,1 */
      *WorkingSectionStatus = FEE_SECTION_ACTIVE;
    }
    else if(FooterStatus == FEE_SECTION_ERASABLE)
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE;
    }
    else
    {
      *WorkingSectionStatus = FEE_SECTION_INCONSISTENT;
    }
    break;
  case FEE_SECTION_ERASABLE_INCONSISTENT:
    if((FooterStatus == FEE_SECTION_EMPTY) ||
        (FooterStatus == FEE_SECTION_ACTIVE))
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE_HEADER;
    }
    else if(FooterStatus == FEE_SECTION_ERASABLE)
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.08,1 */
      *WorkingSectionStatus = FEE_SECTION_ERASABLE;
    }
    else
    {
      *WorkingSectionStatus = FEE_SECTION_INCONSISTENT;
    }
    break;

    /* CHECK: NOPARSE */
    default:
      FEE_UNREACHABLE_CODE_ASSERT(FEE_INTERNAL_API_ID);
      break; /* Caution: this 'break' is required by MISRA-C:2004 */
      /* CHECK: PARSE */
  }

  Fee_CheckForAnchorSection();
}

/*--------------------------[Fee_CheckForAnchorSection]----------------------------------*/

STATIC FUNC(void, FEE_CODE) Fee_CheckForAnchorSection
(
    void
)
{
  Fee_SectionStatus_t * WorkingSectionStatus = &Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus;
  uint8 DiferenceBetweenSectionIndexes;

  if (Fee_Gv.FeeActiveSectionIndex != 255U)
  {
    DiferenceBetweenSectionIndexes = Fee_Gv.FeeWorkingSectionIndex - Fee_Gv.FeeActiveSectionIndex;
    if((*WorkingSectionStatus == FEE_SECTION_ACTIVE) &&
        (Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SCounter == FEE_BYTESUM(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeActiveSectionIndex].SCounter,
            DiferenceBetweenSectionIndexes)))
    {
      /* Newer active section was found */
      Fee_Gv.FeeActiveSectionIndex = Fee_Gv.FeeWorkingSectionIndex;
    }
    else
    {
      /* The section is either not active or the counter is smaller. */
    }
  }
  else /* No active section was found yet. */
  {
    if(*WorkingSectionStatus == FEE_SECTION_ACTIVE)
    {
      /* The first active section has been found */
      Fee_Gv.FeeActiveSectionIndex = Fee_Gv.FeeWorkingSectionIndex;
    }
    else /* Get the oldest Empty section in the Fee_Gv.FeeOldestSectionIndex */
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.15,1 */
      if(Fee_Gv.FeeOldestSectionIndex != 255U)
      {
        DiferenceBetweenSectionIndexes = FEE_NUMBER_OF_SECTIONS - (Fee_Gv.FeeWorkingSectionIndex - Fee_Gv.FeeOldestSectionIndex);
        if(((*WorkingSectionStatus == FEE_SECTION_EMPTY) || (*WorkingSectionStatus == FEE_SECTION_NO_FOOTER)) &&
            (Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeOldestSectionIndex].SCounter == FEE_BYTESUM(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SCounter,
                DiferenceBetweenSectionIndexes)))
        {
          /* The oldest empty section has been found */
          Fee_Gv.FeeOldestSectionIndex = Fee_Gv.FeeWorkingSectionIndex;
        }
        else
        {
          /* Either the section is newer or it's not empty. */
        }
      }
      else /* No empty section has been found yet. */
      {
        if((*WorkingSectionStatus == FEE_SECTION_EMPTY) || (*WorkingSectionStatus == FEE_SECTION_NO_FOOTER))
        {
          /* The first empty section has been found */
          Fee_Gv.FeeOldestSectionIndex = Fee_Gv.FeeWorkingSectionIndex;
        }
        else
        {
          /* This section is not consistent. Ignore it. */
        }
      }
    }
  }
}

/*--------------------------[Fee_HandleSectionChaining]----------------------------------*/

STATIC FUNC(void, FEE_CODE) Fee_HandleSectionChaining
(
    void
)
{
  uint8 DiferenceBetweenSectionIndexes = 0U;
  boolean OldestActiveSectionFound = FALSE;
  boolean AllSectionsInconsistent = FALSE;

  /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.09,2 */
  /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.10,2 */

  /* Start with the anchor section, the newest active one */
  if(Fee_Gv.FeeActiveSectionIndex != 255U)
  {
    /* This is the newest active section, taken as a reference */
    Fee_Gv.FeeOldestSectionIndex = Fee_Gv.FeeActiveSectionIndex;
    Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONINCREMENT(Fee_Gv.FeeActiveSectionIndex);
  }
  else
  {
    /* We found an empty section as the anchor section? */
    if(Fee_Gv.FeeOldestSectionIndex != 255U)
    {
      /* This is the oldest empty section, taken as a reference */
      Fee_Gv.FeeActiveSectionIndex = Fee_Gv.FeeOldestSectionIndex;
      Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONINCREMENT(Fee_Gv.FeeOldestSectionIndex);
    }
    /* There is not anchor section. All the sections must be revalidated at startup2. */
    else
    {
      Fee_Gv.FeeWorkingSectionIndex = 0U;
      Fee_Gv.FeeOldestSectionIndex = 0U;
      Fee_Gv.FeeActiveSectionIndex = 0U;

      AllSectionsInconsistent = TRUE;
    }

    /* No data can be retrieved at init. */
#ifdef FEE_E_DATA_RECOVERED_DEM_EVENT_ID
    /* If neither of the section headers could be read successfully, a production
     * error shall be raised. Additionally, the entire flash shall be erased as part
     * of start-up in order to restore Fee's functionality.
     */
    /* !LINKSTO Fee.FailureHandling.Behaviour.Startup1.ProductionError,1 */
    /* Notify user by reporting a production error */
    Dem_ReportErrorStatus(FEE_E_DATA_RECOVERED_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
  }

  if(AllSectionsInconsistent == FALSE)
  {
    /* Go through sections in order to find the newest Active section */
    while(Fee_Gv.FeeWorkingSectionIndex != Fee_Gv.FeeActiveSectionIndex)
    {
      switch(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus)
      {
      case FEE_SECTION_ACTIVE:
        if(OldestActiveSectionFound == FALSE)
        {
          OldestActiveSectionFound = TRUE;
          Fee_Gv.FeeOldestSectionIndex = Fee_Gv.FeeWorkingSectionIndex;
        }
        else
        {
          /* There are other active section inbetween. Carry on */
        }
        Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = FEE_SECTION_ACTIVE;

        break;

      case FEE_SECTION_EMPTY:
      case FEE_SECTION_NO_FOOTER:
        DiferenceBetweenSectionIndexes = FEE_SECTIONDIF(Fee_Gv.FeeWorkingSectionIndex,Fee_Gv.FeeActiveSectionIndex);
        if(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SCounter != FEE_BYTESUM(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeActiveSectionIndex].SCounter,
            DiferenceBetweenSectionIndexes))
        {
          /* This section is considered inconsistent */
          /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.14,1 */
          Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeWorkingSectionIndex].SectionStatus = FEE_SECTION_INCONSISTENT;
        }
        else
        {
          /* It's a valid empty section. Carry on */
          /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.13,1 */
        }
        break;

      default:
        /* Could be FEE_SECTION_INCONSISTENT, FEE_SECTION_ERASABLE, FEE_SECTION_ERASABLE_HEADER, FEE_SECTION_ERASED */
        break; /* Caution: this 'break' is required by MISRA-C:2004 */
      }

      Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONINCREMENT(Fee_Gv.FeeWorkingSectionIndex);
    }

    if(FEE_SECTIONINCREMENT(Fee_Gv.FeeActiveSectionIndex) == Fee_Gv.FeeOldestSectionIndex)
    {
      /* !LINKSTO Fee.Dsn.Initialization.Startup1.Sections.11,1 */
      /* There is a switch-no-suspend situation. Set the flag. */
      FEE_SET_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK);
    }
    else
    {
      /* Nothing to do. */
    }
  }
  else
  {
    /* Startup2 will handle the revalidation of the sections. */
  }
}

/*--------------------------[Fee_StartUp1Finished]----------------------------------*/

STATIC FUNC(void, FEE_CODE) Fee_StartUp1Finished
(
    void
)
{
  if(Fee_Gv.Fee_SectionManagement[Fee_Gv.FeeActiveSectionIndex].SectionStatus == FEE_SECTION_ACTIVE)
  {
    if(FEE_CHECK_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK))
    {
      Fee_Gv.FeeMode = FEE_MODE_SWITCH;
      /* Check how much space is needed for high priority switch */
      Fee_Gv.FeeSwitchRequiredSpace = Fee_CalculateSSRequiredSpace();
      /* !LINKSTO Fee.Dsn.Initialization.Idle,1 */
      /* This must be the only time the Idle state is triggered in highest priority switch.
       * The reason is for accepting read requests for ReadAll */
      /* !LINKSTO Fee.Dns.SS.RestartSwitch.TriggerAfterInit,1 */
    }
    else
    {
      Fee_Gv.FeeMode = FEE_MODE_STARTUP2;
      /* The Active section is ACTIVE. StartUp2 must start with the next section. */
      Fee_Gv.FeeWorkingSectionIndex = FEE_SECTIONINCREMENT(Fee_Gv.FeeActiveSectionIndex);
      /* !LINKSTO Fee.Dsn.Initialization.Idle,1 */
      /* !LINKSTO Fee.ASR40.SWS_Fee_00169,1 */
    }
#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
    if (TRUE == Fee_CriticalBlockInit())
    {
      /* Do nothing. The critical block related activity has been handled already. */
    }
    else
#endif /* (FEE_CRITICAL_BLOCK_NUMBER != 0U) */
    {
      /* If there is no job to be processed Fee will go Idle. */
      Fee_InitiateJob();
    }
  }
  else
  {
    Fee_Gv.FeeMode = FEE_MODE_STARTUP2;
    /* The active section is either empty or inconsistent. StartUp2 must start with it. */
    Fee_Gv.FeeWorkingSectionIndex = Fee_Gv.FeeActiveSectionIndex;
    FEE_SET_FLAG(FEE_HIGHEST_INTERNAL_PRIORITY_MASK);
    Fee_StartUp2();
  }
}

#if (FEE_CRITICAL_BLOCK_NUMBER != 0U)
/*--------------------------[Fee_CriticalBlockInit]----------------------------------*/

STATIC FUNC(boolean, FEE_CODE) Fee_CriticalBlockInit
(
    void
)
{
  boolean CriticalBlockFound = TRUE;
  const uint16 CriticalBlockIndex = Fee_SearchConfigTable(FEE_CRITICAL_BLOCK_NUMBER);
  /* Check whether the critical block was found. */
  if (FALSE == Fee_IsCriticalBlockErased(CriticalBlockIndex))
  {
    /* For symmetry. Just as the critical block has just been written.
     * This time FeeCriticalState should always be Idle because Fee is still in initialization phase
     * and ReadAll has not been performed yet. */
    Fee_Gv.FeeCriticalState = FEE_IDLE;
    if (FEE_NO_JOB != Fee_Gv.FeeJob)
    {
      /* Any job for a non-critical block must be canceled in order to make room for critical jobs. */
      if (CriticalBlockIndex != Fee_Gv.FeeIntBlockIndex)
      {
        /* !LINKSTO Fee.FeeCriticalBlock.CancelNvMJob,1 */
        Fee_CancelJob();
        /* It's not NvM that canceled this job. NvM is the only one that should. Consider job as failed. */
        Fee_Gv.FeeJobResult = MEMIF_JOB_FAILED;
        /* Call NVM's error notification function */
        FEE_NVM_JOB_ERROR_NOTIFICATION();
        /* Freeze Fee */
        /* !LINKSTO Fee.FeeCriticalBlock.InitFreeze,1 */
        FEE_TRIGGER_TRANS(FEE_CRITICAL_FROZEN);
      }
      else
      {
        /* Read or EraseImmediate job for critical block will be done. */
        /* !LINKSTO Fee.FeeCriticalBlock.StopBlockJobs,1 */
        Fee_InitiateJob();
      }
    }
    else
    {
      /* Freeze Fee */
      /* !LINKSTO Fee.FeeCriticalBlock.InitFreeze,1 */
      FEE_TRIGGER_TRANS(FEE_CRITICAL_FROZEN);
    }
  }
  else
  {
    CriticalBlockFound = FALSE;
  }
  return CriticalBlockFound;
}

#endif /* (FEE_CRITICAL_BLOCK_NUMBER != 0U) */

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*==================[end of file]===========================================*/
