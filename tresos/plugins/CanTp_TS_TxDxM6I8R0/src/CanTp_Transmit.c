/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \version 6.8.63
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason: False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */

/*==================[inclusions]=============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Api.h>         /* CanTp API declarations */
#include <CanTp_Internal.h>    /* internal macros and variables */
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */


#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

#if(CANTP_PARALLEL_CHANNELS_ENABLED == STD_ON)

/** \brief Get the locked channel or the first released channel
 **
 ** This function returns the index of the channel.
 **
 ** \param[in]  TxNSduId      TxNSduId for the current TxNSdu that shall be transmitted
 ** \param[out] ChannelIdxPtr Address to write the channel index to
 **
 ** \return Result of the function
 ** \retval E_OK The first released channel or the locked one, was found and written to the address
 ** \retval E_NOT_OK No free channel was found
 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_GetTxChannelIndex
(
  P2VAR(CanTp_TxChannelType, AUTOMATIC, AUTOMATIC) ChannelIdxPtr,
  PduIdType TxNSduId
)
{

  Std_ReturnType Result = E_NOT_OK;
  CanTp_ChType idx;
  CanTp_ChType NoOfChannels = 0U;


  /* Deviation TASKING-1 */
  for(idx = 0; idx < CANTP_MAX_TX_CHANNELS; idx++)
  {
    P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
    ChannelPtr = &CanTp_Channel[idx];

    if(CANTP_CH_GET_MODE(ChannelPtr) == CANTP_CH_MODE_TX)
    {
      /* Check if locked channels, were already locked for the current RxNSduId */
      if(ChannelPtr->NSduId == TxNSduId)
      {
        /* channel was found */
        Result = E_OK;
        break;
      }
    }
    /* count channels */
    NoOfChannels++;
  }

  /* search the first free channel */
  if(E_NOT_OK == Result)
  {
    NoOfChannels = 0U;

    /* Deviation TASKING-1 */
    for(idx = 0U; idx < CANTP_MAX_TX_CHANNELS; idx++)
    {
      P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
      ChannelPtr = &CanTp_Channel[idx];

      if(CANTP_CH_GET_MODE(ChannelPtr) != CANTP_CH_MODE_TX)
      {
        /* channel was found */
        Result = E_OK;
        break;
      }

      /* count channels */
      NoOfChannels++;
    }
  }

  if(Result == E_OK)
  {
    /* save channel's index */
    *ChannelIdxPtr = NoOfChannels;
  }

  return Result;
}

/** \brief Get the locked Tx channel for the corresponding N-SDU
 **
 ** This function returns the index of the locked channel.
 **
 ** \param[in]  TxNSduId      TxNSduId for the current TxNSdu that shall be transmitted
 ** \param[out] ChannelIdxPtr Address to write the channel index to
 **
 ** \return Result of the function
 ** \retval E_OK The locked channel of the N-SDU was found and written to the address
 ** \retval E_NOT_OK No channel involved in transmission with the TxNSduId was found
 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_GetLockedTxChannelIndex
(
  P2VAR(CanTp_TxChannelType, AUTOMATIC, AUTOMATIC) ChannelIdxPtr,
  PduIdType TxNSduId
)
{
  Std_ReturnType Result = E_NOT_OK;
  CanTp_TxChannelType idx;
  boolean TxNSduFound = FALSE;

  /* Deviation TASKING-1 */
  for(idx = 0; idx < CANTP_MAX_TX_CHANNELS; idx++)
  {
    P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
    ChannelPtr = &CanTp_Channel[idx];

    if(CANTP_CH_GET_MODE(ChannelPtr) == CANTP_CH_MODE_TX)
    {
      /* Check if locked channels, were already locked for the current TxNSduId */
      if(ChannelPtr->NSduId == TxNSduId)
      {
        /* channel was found */
        TxNSduFound = TRUE;
        break;
      }
    }
  }

  if(TxNSduFound == (boolean)TRUE)
  {
    /* save channel's index */
    *ChannelIdxPtr = idx;
    Result = E_OK;
  }

  return Result;
}
#endif /* CANTP_PARALLEL_CHANNELS_ENABLED == STD_ON */

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */



#if(CANTP_PROVIDE_API_FUNCTIONS == STD_ON)

/** \brief CanTp_Transmit()
 **
 ** This API-Service is used to request the transfer of segmented data.
 **
 ** \param[in] CanTpTxSduId  N-Sdu Id, which shall be used for sending
 ** \param[in] CanTpTxInfoPtr  pointer with length information of the frame
 **
 ** \retval E_NOT_OK transmit request failed
 ** \retval E_OK transmit request successful
 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit
(
  PduIdType CanTpTxSduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr
)
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
{
  Std_ReturnType  Ret = E_NOT_OK; /* return value */

  DBG_CANTP_TRANSMIT_ENTRY(CanTpTxSduId, CanTpTxInfoPtr);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  /* check CanTp state - possible DET and return on error */
  if(CanTp_InitVars.State != CANTP_ON)
  {
    CANTP_DET_REPORT_ERROR(
        CANTP_MODULE_ID,
        CANTP_INSTANCE_ID,
        CANTP_API_TRANSMIT,
        CANTP_E_UNINIT
    );
  }

  /* check PduId range - possible DET and return on error */
  else if(CanTpTxSduId >= CanTp_CfgPtr->NumberTxNSdus)
  {
    /* call DET with error ERRORCODE */
    CANTP_DET_REPORT_ERROR(
        CANTP_MODULE_ID,
        CANTP_INSTANCE_ID,
        CANTP_API_TRANSMIT,
        CANTP_E_PARAM_ID
    );
  }

  /* check for Null pointer - possible DET and return on error */
  /* if pointer is null */
  else if(CanTpTxInfoPtr == NULL_PTR)
  {
    CANTP_DET_REPORT_ERROR(
        CANTP_MODULE_ID,
        CANTP_INSTANCE_ID,
        CANTP_API_TRANSMIT,
        CANTP_E_PARAM_POINTER
    );
  }

  /* Check: 0 < N-SDU length */
  else if(CanTpTxInfoPtr->SduLength == 0U)
  {
    /* call DET with error CANTP_E_INVALID_TX_LENGTH */
    CANTP_DET_REPORT_ERROR(
        CANTP_MODULE_ID,
        CANTP_INSTANCE_ID,
        CANTP_API_TRANSMIT,
        CANTP_E_INVALID_TX_LENGTH
    );
  }
  else
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
  {
#if (CANTP_METADATA_CHANNELS == STD_ON)
    PduIdType MetaDataLLPduId; /*Pdu*/
    PduIdType MetadataULPduId; /*Sdu*/
    PduIdType MetadataLLFcPduId; /*Fc*/
    uint32 Metadata_NSdu = 0U;
    uint32 Metadata_Fc = 0U;
    PduInfoType CanTpTxPdu;
    PduInfoType CanTpRxFcPdu;
    PduInfoType MetadataPduInfo;
#endif
    P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;

    /* counter for channels */
    CanTp_TxChannelType Channel;
    Std_ReturnType ChannelFound = E_NOT_OK;
    Std_ReturnType ValidLength = E_NOT_OK;

    /* get channel's index */
    CANTP_GET_TX_CH_INDEX(Channel, CanTpTxSduId, ChannelFound);

#if(CANTP_PARALLEL_CHANNELS_ENABLED == STD_ON)
    if(E_OK == ChannelFound)
#endif /* CANTP_PARALLEL_CHANNELS_ENABLED == STD_ON */
    {
      uint8 NPciSize_SF;
      uint8 MaxUnSegMsgLength;

      ChannelPtr = &CanTp_Channel[Channel];

#if(CANTP_CANFD_ENABLED == STD_ON)
      if(CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId).LSduMaxLength > CANTP_NPDU_LENGTH_8)
      {
        NPciSize_SF = CANTP_SF_FD_NPCI_SIZE;
      }
      else
#endif /* CANTP_CANFD_ENABLED == STD_ON */
      {
        NPciSize_SF = CANTP_SF_NPCI_SIZE;
      }

      /* For checking whether data will fit in a SF or segmented Tx is required */
      MaxUnSegMsgLength = CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId).LSduMaxLength
          - NPciSize_SF
          - CANTP_GET_FIRST_N_PCI_BYTE(&CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId));

      CANTP_ENTER_CRITICAL_SECTION();

      /* lock channel if channel is IDLE and not currently locked */
      if(
      (ChannelPtr->State == CANTP_CH_IDLE)
      && (FALSE == CANTP_IS_CHANNEL_LOCKED(ChannelPtr))
      )
      {
        CANTP_LOCK_CHANNEL(ChannelPtr);

        /* set new state */
        if(CanTpTxInfoPtr->SduLength <= MaxUnSegMsgLength)
        {
          /* setup channel correctly */
          ChannelPtr->NSduId = CanTpTxSduId;
          ChannelPtr->TotalLength = CanTpTxInfoPtr->SduLength;

          /* timeout to request for a buffer is Cs */
          ChannelPtr->Ticks = CANTP_GET_TX_PDU_N_CS(&CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId));

#if(CANTP_DISTRIBUTED_CHANNEL_SUPPORT == STD_OFF)
          CANTP_INC_NON_IDLE_CHANNELS();  /* increment the used channels counter */
#else
          CanTp_NonIdleChannelArray[ChannelPtr->Partition]++;
#endif
          DBG_CANTP_CHANNEL_STATE_GRP(Channel, ChannelPtr->State, CANTP_CH_TX_BUFREQ_SF);

          /* this is a single frame */
          TS_AtomicAssign8(ChannelPtr->State, CANTP_CH_TX_BUFREQ_SF);

#if (CANTP_METADATA_CHANNELS == STD_ON)
          MetadataULPduId = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).MetadataULPduId; /*Sdu*/
          MetaDataLLPduId = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).MetadataLLPduId; /*Pdu*/

          /* !LINKSTO CanTp.EB.CanTpMetaDataParallelHandling_SF_Transmission, 1 */
          (void)EcuC_GetMetaDataCanId(MetadataULPduId, &CanTpTxPdu, &Metadata_NSdu); /*get metadata for Sdu*/
          (void)EcuC_SetMetaDataCanId(MetaDataLLPduId, &MetadataPduInfo, Metadata_NSdu); /*set metadata for Pdu*/
#endif

          ValidLength = E_OK;
        }
        else
        {
          /* check if functional addressing is used with long frames */
          if(CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId).Tatype != CANTP_FUNCTIONAL)
          {
            /* setup channel correctly */
            ChannelPtr->NSduId = CanTpTxSduId;
            ChannelPtr->TotalLength = CanTpTxInfoPtr->SduLength;

            /* timeout to request for a buffer is Cs */
            ChannelPtr->Ticks = CANTP_GET_TX_PDU_N_CS(&CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId));

#if(CANTP_DISTRIBUTED_CHANNEL_SUPPORT == STD_OFF)
            CANTP_INC_NON_IDLE_CHANNELS();  /* increment the used channels counter */
#else
            CanTp_NonIdleChannelArray[ChannelPtr->Partition]++;
#endif

            DBG_CANTP_CHANNEL_STATE_GRP(Channel, ChannelPtr->State, CANTP_CH_TX_BUFREQ_FF);

            /* this is a long frame */
            TS_AtomicAssign8(ChannelPtr->State, CANTP_CH_TX_BUFREQ_FF);

#if (CANTP_METADATA_CHANNELS == STD_ON)
            MetadataULPduId = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).MetadataULPduId; /*Sdu*/
            MetaDataLLPduId = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).MetadataLLPduId; /*Pdu*/
            MetadataLLFcPduId = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).MetadataLLFcPduId; /*Fc*/

            /* !LINKSTO CanTp.EB.CanTpMetaDataParallelHandling_FF_Transmission, 1 */
            (void)EcuC_GetMetaDataCanId(MetadataULPduId, &CanTpTxPdu, &Metadata_NSdu); /*get metadata for Sdu*/
            (void)EcuC_SetMetaDataCanId(MetaDataLLPduId, &MetadataPduInfo, Metadata_NSdu); /*set metadata for Pdu*/

            (void)EcuC_GetMetaDataCanId(MetadataLLFcPduId, &CanTpRxFcPdu, &Metadata_Fc); /*get metadata for Fc*/
            ChannelPtr->MetadataFc=Metadata_Fc;
#endif
            ValidLength = E_OK;
          }
        }
        Ret = E_OK;
      }
      CANTP_LEAVE_CRITICAL_SECTION();

      if(Ret == E_OK)
      {
        if(ValidLength == E_NOT_OK)
        {
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
          CANTP_DET_REPORT_ERROR(
              CANTP_MODULE_ID,
              CANTP_INSTANCE_ID,
              CANTP_API_TRANSMIT,
              CANTP_E_INVALID_TATYPE
          );
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
          /* segmented frames are not allowed for functional addressing */
          Ret = E_NOT_OK;
        }

        CanTp_HandlePostponedFlags(ChannelPtr);

        /* unlock channel*/
        CANTP_UNLOCK_CHANNEL(ChannelPtr);
      }
    }
  }

  DBG_CANTP_TRANSMIT_EXIT(Ret, CanTpTxSduId, CanTpTxInfoPtr);

  return Ret;
} /* CanTp_Transmit() */
#else /* => CANTP_JUMPTABLE_MODE == CANTP_JUMPTABLE_CLIENT */
{
  Std_ReturnType  Ret = E_NOT_OK;
  DBG_CANTP_TRANSMIT_ENTRY(CanTpTxSduId, CanTpTxInfoPtr);
  Ret = (CanTp_EntryTablePtr->Transmit)(CanTpTxSduId, CanTpTxInfoPtr);
  DBG_CANTP_TRANSMIT_EXIT(Ret, CanTpTxSduId, CanTpTxInfoPtr);
  return Ret;
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#endif /* CANTP_PROVIDE_API_FUNCTIONS == STD_ON */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
