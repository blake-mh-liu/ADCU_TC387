/**
 * \file
 *
 * \brief AUTOSAR SecOC
 *
 * This file contains the implementation of the AUTOSAR
 * module SecOC.
 *
 * \version 2.8.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[deviations]==================================================================*/

/*  Misra-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * Function like macro leads to unreachable code compiler.
 *
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This is a bug in the tasking compiler and should be fixed with v6.1r1.
 */

/*==================[includes]====================================================================*/

#include <SecOC_Rx_Int.h>
#include <SecOC_Tx_Int.h>

#if (STD_ON == SECOC_INCLUDE_RTE)
#if (SECOC_NR_PARTITIONS == 0U)
#include <Rte_SecOC.h>
#endif
#endif /* #if (STD_ON == SECOC_INCLUDE_RTE) */

/*==================[macros]======================================================================*/

/** \brief Defined value which indicates that the PDU ID is not corresponding to SecOC
 */
#if (defined SECOC_UNKNOWN_PDU)
#error SECOC_UNKNOWN_PDU already defined
#endif /* #if (defined SECOC_UNKNOWN_PDU) */
#define SECOC_UNKNOWN_PDU      0U

/** \brief Defined value which indicates that the PDU ID corresponds
 **        to a configured authentic PDU ID
 */
#if (defined SECOC_AUTH_PDU)
#error SECOC_AUTH_PDU already defined
#endif /* #if (defined SECOC_AUTH_PDU) */
#define SECOC_AUTH_PDU  1U

/** \brief Defined value which indicates that the PDU ID corresponds
 **        to a configured cryptographic PDU ID
 */
#if (defined SECOC_CRYPTO_PDU)
#error SECOC_CRYPTO_PDU already defined
#endif /* #if (defined SECOC_CRYPTO_PDU) */
#define SECOC_CRYPTO_PDU    2U

/** \brief Defined value which indicates that the PDU ID corresponds
 **        to a configured secured PDU ID
 */
#if (defined SECOC_SECURED_PDU)
#error SECOC_SECURED_PDU already defined
#endif /* #if (defined SECOC_SECURED_PDU) */
#define SECOC_SECURED_PDU    3U

#if (SECOC_NUMBER_RX_PDUS > 0)
#if (STD_ON == SECOC_PDU_SECURED_AREA)
/** \brief Macro to calculate the sum of the Rx minimum required authentic data length
 *         that is comprised of the offset position and the length of the secured area,
 *         when the secured area is used
 */
#if (defined SECOC_RX_SECAREA_MIN_AUTHDATALEN)
#error SECOC_RX_SECAREA_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_RX_SECAREA_MIN_AUTHDATALEN) */
#define SECOC_RX_SECAREA_MIN_AUTHDATALEN(Id) ((uint32)(SECOC_GET_RX_SECURED_AREA_LEN((Id))) + \
                                              (uint32)(SECOC_GET_RX_SECURED_AREA_OFFSET((Id))))
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */

#if (STD_ON == SECOC_RX_USE_MESS_LINKER)
/** \brief Macro to calculate the sum of the Rx minimum required authentic data length
 *         that is comprised of the offset position and the length of the message link,
 *         when the message link is used
 */
#if (defined SECOC_RX_MSGLINK_MIN_AUTHDATALEN)
#error SECOC_RX_MSGLINK_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_RX_MSGLINK_MIN_AUTHDATALEN) */
#define SECOC_RX_MSGLINK_MIN_AUTHDATALEN(Id) ((uint32)SecOC_RxConfig[(Id)].MessageLinkLength + \
                                              (uint32)SecOC_RxConfig[(Id)].MessageLinkPos)
#endif /* #if (STD_ON == SECOC_RX_USE_MESS_LINKER) */
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

#if (SECOC_NUMBER_TX_PDUS > 0)
#if (STD_ON == SECOC_PDU_SECURED_AREA)
/** \brief Macro to calculate the sum of the Tx minimum required authentic data length
 *         that is comprised of the offset position and the length of the secured area,
 *         when the secured area is used
 */
#if (defined SECOC_TX_SECAREA_MIN_AUTHDATALEN)
#error SECOC_TX_SECAREA_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_TX_SECAREA_MIN_AUTHDATALEN) */
#define SECOC_TX_SECAREA_MIN_AUTHDATALEN(Id) ((uint32)(SECOC_GET_TX_SECURED_AREA_LEN((Id))) + \
                                              (uint32)(SECOC_GET_TX_SECURED_AREA_OFFSET((Id))))
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */

#if (STD_ON == SECOC_TX_USE_MESS_LINKER)
/** \brief Macro to calculate the sum of the Tx minimum required authentic data length
 *         that is comprised of the offset position and the length of the message link,
 *         when the message link is used
 */
#if (defined SECOC_TX_MSGLINK_MIN_AUTHDATALEN)
#error SECOC_TX_MSGLINK_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_TX_MSGLINK_MIN_AUTHDATALEN) */
#define SECOC_TX_MSGLINK_MIN_AUTHDATALEN(Id) ((uint32)SecOC_TxConfig[(Id)].MessageLinkLength + \
                                              (uint32)SecOC_TxConfig[(Id)].MessageLinkPos)
#endif /* #if (STD_ON == SECOC_TX_USE_MESS_LINKER) */
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#if (SECOC_NUMBER_RX_PDUS > 0)

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/** \brief Function to determine if the external received PDU ID corresponds to an internal
 *         equivalent index, converts the external ID into the internal equivalent Index
 *         and checks whether the received ID is for a secured/authentic/cryptographic PDU.
 * \param[in,out] rxPduIdx    in: received PDU ID  out: internal equivalent Index
 * \param[out]    rxPduType   Contains the PDU type (eq. authentic, cryptographic)
 * \returns whether the external PDU has an internal equivalent Index
 * \retval TRUE   an internal equivalent Index was found
 * \retval FALSE  an internal equivalent Index was not found
 */
static FUNC(boolean, SECOC_CODE) SecOC_RxCheckForPduIdx
(
  P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) rxPduIdx,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) rxPduType
);

#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
/** \brief Function used to determine whether the incoming PDU can be stored or not,
 *         i.e. whether the required buffer to store the incoming PDU is free or not.
 * \param[in]        pduIdx     Contains the PDU ID
 * \returns whether the required buffer is free or not
 * \retval TRUE      the buffer it is free, can be used
 * \retval FALSE     the buffer it isn't free
 */
static FUNC(boolean, SECOC_CODE) SecOC_RxCheckBufferAvailability
(
  uint16 pduIdx
);
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */

/** \brief Function to determine whether the incoming PDU which will be received via IF API
 *         is valid based on its length, i.e. whether its actual length corresponds
 *         to the required length.
 * \param[in,out] pduLength  in: The length of the incoming PDU that needs to be verified
 *                           out: The length that will be copied from the incoming PDU
 * \param[in]     pduIdx     Contains the PDU ID
 * \param[in]     pduType    Contains the PDU type (e.q. authentic, cryptographic)
 * \returns whether the external PDU has the required length
 * \retval BUFREQ_OK        the length of the PDU is the required one
 * \retval BUFREQ_E_NOT_OK  the length of the PDU is not the required one
 */
static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingIfPdu
(
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) pduLength,
        uint16                              pduIdx,
        uint8                               pduType
);

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
/** \brief Function to determine whether the incoming authentic or cryptographic PDU which will be
 *         received via IF API is valid based on its length, i.e. whether its actual length
 *         corresponds to the required length.
 * \param[in,out] pduLength  in: The length of the incoming PDU that needs to be verified
 *                           out: The length that will be copied from the incoming PDU
 * \param[in]     pduIdx     Contains the PDU ID
 * \param[in]     pduType    Contains the PDU type (e.q. authentic, cryptographic)
 * \returns whether the external PDU has the required length
 * \retval BUFREQ_OK        the length of the PDU is the required one
 * \retval BUFREQ_E_NOT_OK  the length of the PDU is not the required one
 */
static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingIfPduCol
(
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) pduLength,
        uint16                              pduIdx,
        uint8                               pduType
);
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (STD_ON == SECOC_RX_USETP)
/** \brief Function to determine whether the incoming PDU which will be received via TP APIs
 *         is valid based on its length, i.e. whether its actual length corresponds
 *         to the required length.
 * \param[in] pduLength  The length of the incoming PDU that needs to be verified
 * \param[in] pduIdx     Contains the PDU ID
 * \param[in] pduType    Contains the PDU type (e.q. authentic, cryptographic)
 * \returns whether the external PDU has the required length
 * \retval BUFREQ_OK        the length of the PDU is the required one
 * \retval BUFREQ_E_NOT_OK  the length of the PDU is not the required one
 */
static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingTpPdu
(
  uint32 pduLength,
  uint16 pduIdx,
  uint8  pduType
);
#endif /* #if (STD_ON == SECOC_RX_USETP) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

#if (SECOC_NUMBER_TX_PDUS > 0)
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/** \brief Function used to determine whether the incoming PDU can be stored or not,
 *         i.e. whether the required buffer to store the incoming PDU is free or not.
 * \param[in]        pduIdx     Contains the PDU ID
 * \returns whether the required buffer is free or not
 * \retval TRUE      the buffer it is free, can be used
 * \retval FALSE     the buffer it isn't free
 */
static FUNC(uint8, SECOC_CODE) SecOC_TxCheckBufferAvailability
(
  uint16 pduIdx
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

VAR(uint8, SECOC_VAR) SecOC_PB_PduBuffer[SECOC_PB_PDU_MEM_SIZE];

VAR(uint8, SECOC_VAR) SecOC_PB_IntBuffer[SECOC_PB_INT_MEM_SIZE];

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/*==================[variables for Rx side]=======================================================*/

/*==================[variables for Tx side]=======================================================*/

#if (SECOC_NUMBER_TX_PDUS > 0)
#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)

#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/**
 * \brief Flag which indicates the bypass mechanism state (enabled or disabled)
 */
VAR(uint8, SECOC_VAR) SecOC_TxBypassAuthRoutineState;

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

/*==================[variables for Rx and Tx side]================================================*/

#define SECOC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <SecOC_MemMap.h>

P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) SecOC_ConfigPtr;

#define SECOC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <SecOC_MemMap.h>

#define SECOC_START_SEC_VAR_INIT_8
#include <SecOC_MemMap.h>

/**
 * \brief Initialization status of the SecOC. It is declared as volatile to
 *        prevent the compiler from reordering accesses to this variable because
 *        we rely on the sequence of assignments in SecOC_Init() and SecOC_DeInit()
 */
volatile VAR(SecOC_StateType, SECOC_VAR) SecOC_InitStatus = SECOC_UNINIT;

#define SECOC_STOP_SEC_VAR_INIT_8
#include <SecOC_MemMap.h>

/*==================[external function definitions]===============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00106,1 */
FUNC(void, SECOC_CODE) SecOC_Init
(
  P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) config
)
{
  P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) LocalConfigPtr = config;

  /* Post Build Initializations */
  /* !LINKSTO SecOC.PB.Impl.PbCfgM,1 */
#if (SECOC_PBCFGM_SUPPORT_ENABLED == STD_ON)
  if (LocalConfigPtr == NULL_PTR)
  {
    PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;

    if (E_OK == PbcfgM_GetConfig(SECOC_MODULE_ID, SECOC_INSTANCE_ID, &ModuleConfig))
    {
      LocalConfigPtr = (P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST)) ModuleConfig;
    }
  }
#endif /* #if (SECOC_PBCFGM_SUPPORT_ENABLED == STD_ON) */

  if(SecOC_IsValidConfig(LocalConfigPtr) == E_OK)
  {
    /* Deviation MISRAC2012-1 */
    if (
        (SECOC_PB_PDU_MEM_SIZE >= LocalConfigPtr->PduBufferSize) &&
        (SECOC_PB_INT_MEM_SIZE >= LocalConfigPtr->IntBufferSize)
       )
    {
      /* Set the pointer to the post-build configuration */
      SecOC_ConfigPtr = LocalConfigPtr;
      /* Deviation MISRAC2012-1 */
      TS_MemBZero
      (
        SecOC_PB_PduBuffer,
        SECOC_PB_PDU_MEM_SIZE
      );
      /* Deviation MISRAC2012-1 */
      TS_MemBZero
      (
        SecOC_PB_IntBuffer,
        SECOC_PB_INT_MEM_SIZE
      );

      /* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00054,1 */
#if (SECOC_NUMBER_RX_PDUS > 0)
      SecOC_Rx_Init();
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#if (SECOC_NUMBER_TX_PDUS > 0)
      SecOC_Tx_Init();
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

      /* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00106,1 */
      SecOC_InitStatus = SECOC_INIT;
    }
  }
}

/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00161,1 */
FUNC(void, SECOC_CODE) SecOC_DeInit
(
  void
)
{
  /* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00161,1 */
  SecOC_InitStatus = SECOC_UNINIT;

  /* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00157,1 */
#if (SECOC_NUMBER_RX_PDUS > 0)
  SecOC_Rx_DeInit();
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#if (SECOC_NUMBER_TX_PDUS > 0)
  SecOC_Tx_DeInit();
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
}

#if (STD_ON == SECOC_VERSION_INFO_API)
/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00107,1, SecOC.ASR430.RxTx.SWS_SecOC_00103,2 */
FUNC(void, SECOC_CODE) SecOC_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SECOC_APPL_DATA) versioninfo
)
{
  if (NULL_PTR != versioninfo)
  {
    versioninfo->vendorID         = SECOC_VENDOR_ID;
    versioninfo->moduleID         = SECOC_MODULE_ID;
    versioninfo->sw_major_version = SECOC_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = SECOC_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = SECOC_SW_PATCH_VERSION;
  }
}
#endif /* #if (STD_ON == SECOC_VERSION_INFO_API) */

FUNC(Std_ReturnType, SECOC_CODE) SecOC_IsValidConfig
(
  P2CONST(void, AUTOMATIC, SECOC_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType retVal = E_NOT_OK;
  P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) ConfigPtr = voidConfigPtr;

  if(ConfigPtr != NULL_PTR)
  {
    /* Check if the configuration fits to the platform */
    if(TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
    {
      /* Validate the post build configuration against the compile time configuration */
      if(SECOC_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if(SecOC_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the Published information in post build configuration against the
           * Published information in compile time configuration
           */
          if(SECOC_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
          {
            /* Indicate that the configuration is valid */
            retVal = E_OK;
          }
        }
      }
    }
  }

  return retVal;
}

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00112,1 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Transmit
(
          PduIdType                                id,
  P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (SECOC_NUMBER_TX_PDUS > 0)
  uint16 pduIdx       = (uint16) id;

  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00108,1 */
  if (
      (SECOC_INIT           == SecOC_InitStatus                 ) &&
      (NULL_PTR             != info                             ) &&
      (SECOC_NUMBER_TX_PDUS >  id                               ) &&
      (info->SduLength      <= SECOC_GET_TX_AUTH_PDU_LEN(pduIdx))
     )
  {
#if (STD_ON == SECOC_PDU_SECURED_AREA)
    /* !LINKSTO SecOC.ASR431.Tx.SWS_SecOC_00313,1 */
    if (info->SduLength >= SECOC_TX_SECAREA_MIN_AUTHDATALEN(pduIdx))
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
    {
#if (SECOC_TX_USE_MESS_LINKER == STD_ON)
      if (
          (SecOC_TxConfig[pduIdx].UseSecPduCollection == FALSE) ||
          (
           info->SduLength >= SECOC_REQUIREDBYTES(SECOC_TX_MSGLINK_MIN_AUTHDATALEN(pduIdx))
          )
         )
#endif /* #if (SECOC_TX_USE_MESS_LINKER == STD_ON) */
      {
        SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
        if (SECOC_BUFFER_FREE == SecOC_TxCheckBufferAvailability(pduIdx))
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
        {
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
          /* Set the buffer used flag to true, to prevent reception of other authentic PDUs
           * that are using the same buffer
           */
          /* CHECK: NOPARSE
           * Function like macro leads to unreachable code compiler (Wind River Diab) warning
           */
          /* Deviation MISRAC2012-1 */
          SECOC_TX_SET_BUFFER_LVL1_STATUS(pduIdx, SECOC_BUFFER_USED);
          /* CHECK: PARSE */
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
          if (
              (
                (SecOC_TxConfig[pduIdx].UseDynamicLength == TRUE) &&
                (info->SduLength      <= SECOC_GET_TX_AUTH_PDU_LEN(pduIdx))
              )
              ||
              (
                (SecOC_TxConfig[pduIdx].UseDynamicLength == FALSE) &&
                (info->SduLength      == SECOC_GET_TX_AUTH_PDU_LEN(pduIdx))
              )
             )
          {
            /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00006,1 */
            SecOC_TxData[pduIdx].ReceivedAuthPdu.SduLength = info->SduLength;
            /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00110,1, SecOC.ASR20-11.Tx.SWS_SecOC_00252,1 */
            TS_MemCpy(SecOC_TxData[pduIdx].ReceivedAuthPdu.SduDataPtr, info->SduDataPtr, info->SduLength);

            SecOC_TxData[pduIdx].TransmitEvent = SECOC_TXEVENT_TRANSMIT;

            retVal = E_OK;
          }

        }
        SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
      }
    }

    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00024,1 */
#if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON)
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00021,1 */
    if (TRUE == SecOC_TxConfig[pduIdx].UseSyncProcessing)
    {
      SecOC_Tx_ProcessPduStates(pduIdx);
    }
#endif /* #if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON) */
  }
#else /* #if (SECOC_NUMBER_TX_PDUS > 0) */
  SECOC_PARAM_UNUSED(id);
  SECOC_PARAM_UNUSED(info);
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) #else */

  return retVal;
}

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00113,1 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_CancelTransmit
(
  PduIdType  id
)
{
  Std_ReturnType retVal = E_NOT_OK;
#if (SECOC_NUMBER_TX_PDUS > 0)
  uint16         pduIdx = (uint16) id;
  if ((SECOC_INIT == SecOC_InitStatus) && (SECOC_NUMBER_TX_PDUS > pduIdx))
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00076,1, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
#if (STD_ON == SECOC_PDUR_SECOCCANCELTRANSMIT)
    retVal = PduR_SecOCCancelTransmit((PduIdType) SECOC_GET_TX_SEC_PDU_ID_AT_PDUR(pduIdx));
#else /* #if (STD_ON == SECOC_PDUR_SECOCCANCELTRANSMIT) */
    retVal = E_OK;
#endif /* #if (STD_ON == SECOC_PDUR_SECOCCANCELTRANSMIT) #else */

    SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_CANCEL;
    SecOC_TxData[pduIdx].TransmitEvent = SECOC_TXEVENT_NONE;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
    SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
    /* CHECK: NOPARSE
     * Function like macro leads to unreachable code compiler (Wind River Diab) warning
     */
    /* Deviation MISRAC2012-1 */
    SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
    /* CHECK: PARSE */
    SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
  }
#else /* #if (SECOC_NUMBER_TX_PDUS > 0) */
  SECOC_PARAM_UNUSED(id);
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) #else */
  return retVal;
}

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00127,1 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TriggerTransmit
(
        PduIdType                                TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (SECOC_NUMBER_TX_PDUS > 0U)

  if (
      (SECOC_INIT == SecOC_InitStatus) &&
      (NULL_PTR   != PduInfoPtr      )
     )
  {
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) bufferPtr = NULL_PTR;
    PduLengthType bufferLength = 0U;
    uint16 pduIdx;
    boolean idFound = FALSE;

    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
    {
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
      if (SecOC_TxConfig[pduIdx].UseSecPduCollection == TRUE)
      {
        if (TxPduId == SecOC_TxConfig[pduIdx].PduIdForSentAuthPduAtSecOC)
        {
          bufferPtr = SecOC_TxData[pduIdx].SentAuthPdu.SduDataPtr;
          bufferLength = SecOC_TxData[pduIdx].SentAuthPdu.SduLength;
          idFound = TRUE;
        }
        else
        if (TxPduId == SecOC_TxConfig[pduIdx].PduIdForCryptoPduAtSecOC)
        {
          bufferPtr = SecOC_TxData[pduIdx].CryptoPdu.SduDataPtr;
          bufferLength = SecOC_TxData[pduIdx].CryptoPdu.SduLength;
          idFound = TRUE;
        }
        else
        {
          /* Do nothing as the received ID is not for SecOC */
        }
      }
      else
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
      {
        if (TxPduId == SecOC_TxConfig[pduIdx].PduIdForSecuredPduAtSecOC)
        {
          bufferPtr = SecOC_TxData[pduIdx].SecuredPdu.SduDataPtr;
          bufferLength = SecOC_TxData[pduIdx].SecuredPdu.SduLength;
          idFound = TRUE;
        }
      }

      if (idFound == TRUE)
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00150,1 */
        if (
            (SecOC_TxData[pduIdx].State == SECOC_TX_STATE_WAITFORCONFIRMATION) &&
            (PduInfoPtr->SduLength      >= bufferLength                      )
           )
        {
          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00068,1 */
          /* Copy the Secured I-PDU in the lower layer's buffer */
          TS_MemCpy(PduInfoPtr->SduDataPtr, bufferPtr, bufferLength);

          /* Provide the length of the copied data */
          PduInfoPtr->SduLength = bufferLength;

          retVal = E_OK;
        }
        break;
      }
    }
  }
#else /* #if (SECOC_NUMBER_TX_PDUS > 0) */
  SECOC_PARAM_UNUSED(TxPduId);
  SECOC_PARAM_UNUSED(PduInfoPtr);
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) #else */

  return retVal;
}

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00126,1 */
FUNC(void, SECOC_CODE) SecOC_TxConfirmation
(
  PduIdType id
)
{
#if (SECOC_NUMBER_TX_PDUS > 0)
  uint16 pduIdx;

  if (SECOC_INIT == SecOC_InitStatus)
  {
    boolean idFound = FALSE;

    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
    {
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
      if (SecOC_TxConfig[pduIdx].UseSecPduCollection == TRUE)
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSentAuthPduAtSecOC)
        {
          idFound = TRUE;

          if (SecOC_TxData[pduIdx].PduRConfirmationForCrypto == SECOC_TXEVENT_TXCONFIRMATION_OK)
          {
            /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00270,1 */
            PduR_SecOCTxConfirmation(SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx));
            SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_NONE;
            SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_TXCONFIRMATION_OK;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
            /* CHECK: NOPARSE
             * Function like macro leads to unreachable code compiler (Wind River Diab) warning
             */
            /* Deviation MISRAC2012-1 */
            SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
            /* CHECK: PARSE */
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
          }
          else
          {
            SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_TXCONFIRMATION_OK;
          }
        }
        else
        if (id == SecOC_TxConfig[pduIdx].PduIdForCryptoPduAtSecOC)
        {
          idFound = TRUE;

          if (SecOC_TxData[pduIdx].PduRConfirmationForAuth == SECOC_TXEVENT_TXCONFIRMATION_OK)
          {
            /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00270,1 */
            PduR_SecOCTxConfirmation(SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx));
            SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_NONE;
            SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_TXCONFIRMATION_OK;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
            /* CHECK: NOPARSE
             * Function like macro leads to unreachable code compiler (Wind River Diab) warning
             */
            /* Deviation MISRAC2012-1 */
            SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
            /* CHECK: PARSE */
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
          }
          else
          {
            SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_TXCONFIRMATION_OK;
          }
        }
        else
        {
          /* Do nothing as the received ID is not related to this secured PDU collection */
        }
      }
      else
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSecuredPduAtSecOC)
        {
          idFound = TRUE;

          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00063,1, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
          PduR_SecOCTxConfirmation(SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx));
          SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_TXCONFIRMATION_OK;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
          /* CHECK: NOPARSE
           * Function like macro leads to unreachable code compiler (Wind River Diab) warning
           */
          /* Deviation MISRAC2012-1 */
          SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
          /* CHECK: PARSE */
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
        }
      }

      if (idFound == TRUE)
      {
        break;
      }
    }
  }
#else /* #if (SECOC_NUMBER_TX_PDUS > 0) */
  SECOC_PARAM_UNUSED(id);
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) #else */
}

#if (STD_ON == SECOC_TX_USETP)
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00129,1, SecOC.ASR430.RxTx.SWS_SecOC_00103,2 */
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyTxData
(
        PduIdType                                  id,
  P2VAR(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
  P2VAR(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) retry,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) availableDataPtr
)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

#if (SECOC_NUMBER_TX_PDUS > 0)

  if ((SECOC_INIT == SecOC_InitStatus) && (NULL_PTR != info) && (NULL_PTR != availableDataPtr))
  {
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) copiedDataLengthPtr = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) bufferPtr = NULL_PTR;
    PduLengthType totalPduLength = 0U;
    uint16 pduIdx;
    boolean idFound = FALSE;

    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
    {
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
      if (SecOC_TxConfig[pduIdx].UseSecPduCollection == TRUE)
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSentAuthPduAtSecOC)
        {
          copiedDataLengthPtr = &SecOC_TxData[pduIdx].CopiedDataFromAuthLength;
          totalPduLength = SecOC_TxData[pduIdx].SentAuthPdu.SduLength;
          bufferPtr = SecOC_TxData[pduIdx].SentAuthPdu.SduDataPtr;
          idFound = TRUE;
        }
        else
        if (id == SecOC_TxConfig[pduIdx].PduIdForCryptoPduAtSecOC)
        {
          copiedDataLengthPtr = &SecOC_TxData[pduIdx].CopiedDataFromCryptoLength;
          totalPduLength = SecOC_TxData[pduIdx].CryptoPdu.SduLength;
          bufferPtr = SecOC_TxData[pduIdx].CryptoPdu.SduDataPtr;
          idFound = TRUE;
        }
        else
        {
          /* Do nothing as the received ID is not for SecOC */
        }
      }
      else
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSecuredPduAtSecOC)
        {
          copiedDataLengthPtr = &SecOC_TxData[pduIdx].CopiedDataFromSecLength;
          totalPduLength = SecOC_TxData[pduIdx].SecuredPdu.SduLength;
          bufferPtr = SecOC_TxData[pduIdx].SecuredPdu.SduDataPtr;
          idFound = TRUE;
        }
      }

      if (idFound == TRUE)
      {
        if (SECOC_TX_STATE_WAITFORCONFIRMATION == SecOC_TxData[pduIdx].State)
        {
          PduLengthType remainingBytes;

          retVal = BUFREQ_OK;

          if ( (NULL_PTR != retry) && (TP_DATARETRY  == retry->TpDataState))
          {
            /* copy previously copied data again. */

            if (retry->TxTpDataCnt < *copiedDataLengthPtr)
            {
              *copiedDataLengthPtr -= retry->TxTpDataCnt;
            }
            else
            {
              retVal = BUFREQ_E_NOT_OK;
            }
          }

          remainingBytes = totalPduLength - *copiedDataLengthPtr;

          if (remainingBytes < info->SduLength)
          {
            /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00129,1 */
            retVal = BUFREQ_E_BUSY;
            *availableDataPtr = remainingBytes;
          }

          if (BUFREQ_OK == retVal)
          {
            /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00073,1, SecOC.ASR430.Tx.SWS_SecOC_00129,1 */
            if ((info->SduLength > 0U) && (info->SduDataPtr == NULL_PTR))
            {
              retVal = BUFREQ_E_NOT_OK;
            }
            else
            {
              TS_MemCpy
              (
                  info->SduDataPtr,
                  &bufferPtr[*copiedDataLengthPtr],
                  info->SduLength
              );
              *copiedDataLengthPtr += info->SduLength;
              *availableDataPtr = (remainingBytes - info->SduLength);
            }
          }
        }
        break;
      }
    }
  }
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
  return retVal;
}

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00152,1 */
FUNC(void, SECOC_CODE) SecOC_TpTxConfirmation
(
  PduIdType      id,
  Std_ReturnType result
)
{
#if (SECOC_NUMBER_TX_PDUS > 0)
  uint16 pduIdx;

  if (SECOC_INIT == SecOC_InitStatus)
  {
    boolean idFound = FALSE;

    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
    {
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
      if (SecOC_TxConfig[pduIdx].UseSecPduCollection == TRUE)
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSentAuthPduAtSecOC)
        {
          idFound = TRUE;

          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00077,1 */
          if (E_OK == result)
          {
            SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_TXCONFIRMATION_OK;
          }
          else
          {
            SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_TXCONFIRMATION_NOT_OK;
          }
        }
        else
        if (id == SecOC_TxConfig[pduIdx].PduIdForCryptoPduAtSecOC)
        {
          idFound = TRUE;

          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00077,1 */
          if (E_OK == result)
          {
            SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_TXCONFIRMATION_OK;
          }
          else
          {
            SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_TXCONFIRMATION_NOT_OK;
          }
        }
        else
        {
          /* Do nothing as the received ID is not for SecOC */
        }

        if (TRUE == idFound)
        {
          if ((SecOC_TxData[pduIdx].PduRConfirmationForAuth != SECOC_TXEVENT_NONE)  &&
              (SecOC_TxData[pduIdx].PduRConfirmationForCrypto != SECOC_TXEVENT_NONE)
             )
          {
            if ((SecOC_TxData[pduIdx].PduRConfirmationForAuth == SECOC_TXEVENT_TXCONFIRMATION_OK)  &&
                (SecOC_TxData[pduIdx].PduRConfirmationForCrypto == SECOC_TXEVENT_TXCONFIRMATION_OK)
               )
            {
              /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00270,1 */
              /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00074,2, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
              PduR_SecOCTpTxConfirmation
                (SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx), E_OK);
            }
            else
            {
              /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00270,1 */
              /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00074,2, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
              PduR_SecOCTpTxConfirmation
                (SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx), E_NOT_OK);
            }
            SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_NONE;
            SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_NONE;
            SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_TXCONFIRMATION_OK;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
            /* CHECK: NOPARSE
             * Function like macro leads to unreachable code compiler (Wind River Diab) warning
             */
            /* Deviation MISRAC2012-1 */
            SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
            /* CHECK: PARSE */
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
          }
        }
      }
      else
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
      {
        if (id == SecOC_TxConfig[pduIdx].PduIdForSecuredPduAtSecOC)
        {
          idFound = TRUE;

          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00077,1, SecOC.ASR430.Tx.SWS_SecOC_00074,2, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
          PduR_SecOCTpTxConfirmation
            (SECOC_GET_TX_ULAUTH_PDU_ID_AT_PDUR(pduIdx), result);

          SecOC_TxData[pduIdx].PduREvent = SECOC_TXEVENT_TXCONFIRMATION_OK;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
          /* CHECK: NOPARSE
           * Function like macro leads to unreachable code compiler (Wind River Diab) warning
           */
          /* Deviation MISRAC2012-1 */
          SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
          /* CHECK: PARSE */
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
        }
      }

      if (idFound == TRUE)
      {

        break;
      }
    }
  }
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
}
#endif /* #if (STD_ON == SECOC_TX_USETP) */

#if (STD_ON == SECOC_RX_USETP)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00130,1, SecOC.EB.Rx.SWS_SecOC_00024,1 */
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_StartOfReception
(
        PduIdType                                  id,
#if (STD_OFF == SECOC_ASR403_API)
  P2VAR(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
        PduLengthType                              TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

#if (SECOC_NUMBER_RX_PDUS > 0)
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00109,1 */
  if (
      (SECOC_INIT == SecOC_InitStatus) &&
      (NULL_PTR   != bufferSizePtr   )
     )
  {
    uint16 pduIdx = (uint16) id;
    uint8 pduType = SECOC_UNKNOWN_PDU;

    if (TRUE == SecOC_RxCheckForPduIdx(&pduIdx, &pduType))
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00214,1, SecOC.ASR430.Rx.SWS_SecOC_00215,1 */
      if (
          (FALSE                     == SecOC_RxData[pduIdx].PduInProcess     ) ||
          (SECOC_REJECT_INCOMING_PDU != SecOC_RxConfig[pduIdx].ReceptionStrategy)
         )
      {
        if (TpSduLength == 0U)
        {
          bufReqRetVal = BUFREQ_OK;
        }
        else
        {
        /* !LINKSTO SecOC.ASR430.SWS_SecOC_00181,1 */
        bufReqRetVal = SecOC_RxCheckIncomingTpPdu(TpSduLength, pduIdx, pduType);
        }

        if (BUFREQ_OK == bufReqRetVal)
        {
          P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) receivedDataLenPtr;
#if (STD_OFF == SECOC_ASR403_API)
          P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) localBufferPtr;
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
          PduLengthType localBufferSize;
          PduLengthType inputBufferSize = *bufferSizePtr;

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
          if (pduType == SECOC_AUTH_PDU)
          {
#if (STD_OFF == SECOC_ASR403_API)
            localBufferPtr = SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr;
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
            localBufferSize = SECOC_GET_RX_AUTH_PDU_LEN(pduIdx);
            receivedDataLenPtr = &SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength;
          }
          else
          if (pduType == SECOC_CRYPTO_PDU)
          {
#if (STD_OFF == SECOC_ASR403_API)
            localBufferPtr = SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr;
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
            localBufferSize = SECOC_GET_RX_CRYPTO_PDU_LEN(pduIdx);
            receivedDataLenPtr = &SecOC_RxData[pduIdx].CryptoPdu.SduLength;
          }
          else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
          {
#if (STD_OFF == SECOC_ASR403_API)
            localBufferPtr = SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduDataPtr;
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
            localBufferSize = SECOC_GET_RX_SECURED_PDU_LEN(pduIdx);
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
            if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
            {
              localBufferSize = SecOC_Rx_GetQueueCapacity(pduIdx);
            }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
            receivedDataLenPtr = &SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength;
          }

          *receivedDataLenPtr = 0U;

#if (STD_OFF == SECOC_ASR403_API)
          if (NULL_PTR != info)
          {
            if (info->SduLength <= localBufferSize)
            {
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
              /* Receive a secured PDU */
              if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
              {
                /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00216,1 */
                bufReqRetVal = SecOC_Rx_WritePduToQueue(pduIdx,
                                                                      info->SduDataPtr,
                                                                      info->SduLength,
                                                                      TpSduLength
                                                                     );
                if (BUFREQ_OK == bufReqRetVal)
                {
                  *receivedDataLenPtr = info->SduLength;
                }
              }
              else
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
              {
                *receivedDataLenPtr = info->SduLength;
                /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00111,1 */
                TS_MemCpy(localBufferPtr, info->SduDataPtr, info->SduLength);
              }
            }
            else
            {
              bufReqRetVal = BUFREQ_E_OVFL;
            }
          }
#else /* #if (STD_OFF == SECOC_ASR403_API) */
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
          /* Initiate the reception of a secured PDU */
          if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
          {
            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00216,1 */
            bufReqRetVal = SecOC_Rx_WritePduToQueue(pduIdx,
                                                                  NULL_PTR,
                                                                  0U,
                                                                  TpSduLength
                                                                 );
          }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
#endif /* #if (STD_OFF == SECOC_ASR403_API) #else */

          inputBufferSize =
              localBufferSize - *receivedDataLenPtr;

#if ((STD_OFF == SECOC_ASR403_API) || \
     ((STD_ON == SECOC_ASR403_API) && (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)))
          if (BUFREQ_OK != bufReqRetVal)
          {
            *receivedDataLenPtr = 0U;
          }
          else
#endif /*#if ((STD_OFF == SECOC_ASR403_API) || ((STD_ON == SECOC_ASR403_API) && (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON))) */
          {
            *bufferSizePtr = inputBufferSize;
            SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_STARTRECEPTION;
          }
        }
      }
      else
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00215,1 */
        bufReqRetVal = BUFREQ_E_OVFL;
      }

      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
    }
  }

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

  return bufReqRetVal;
}

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00128,1, SecOC.ASR430.RxTx.SWS_SecOC_00103,2 */
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyRxData
(
          PduIdType                                  id,
  P2CONST(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

#if (SECOC_NUMBER_RX_PDUS > 0)
  uint16 pduIdx = (uint16) id;

  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00109,1 */
  if (
      (SECOC_INIT == SecOC_InitStatus) &&
      (NULL_PTR   != info            ) &&
      (NULL_PTR   != bufferSizePtr   )
     )
  {
    uint8 pduType = SECOC_UNKNOWN_PDU;
    boolean idFound = FALSE;

    idFound = SecOC_RxCheckForPduIdx(&pduIdx, &pduType);

    if (
        (TRUE                         == idFound                         ) &&
        (SECOC_RXEVENT_STARTRECEPTION == SecOC_RxData[pduIdx].PduREvent)
       )
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

      /* CHECK: NOPARSE */
      /* Defensive programming: if this function is called, the SecOC_RxData[pduIdx].PduInProcess
       * will be TRUE when PduR event is SECOC_RXEVENT_STARTRECEPTION or
       * when is FALSE the overflow strategy is set to REPLACE.
       */
      if (
          (FALSE                     == SecOC_RxData[pduIdx].PduInProcess     ) ||
          (SECOC_REJECT_INCOMING_PDU != SecOC_RxConfig[pduIdx].ReceptionStrategy)
         )
      /* CHECK: PARSE */
      {
        P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) receivedDataLenPtr;
        P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) localBufferPtr;
        PduLengthType localBufferSize = 0U;

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
        if (pduType == SECOC_AUTH_PDU)
        {
          localBufferPtr = SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr;
          localBufferSize = SECOC_GET_RX_AUTH_PDU_LEN(pduIdx);
          receivedDataLenPtr = &SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength;
        }
        else
        if (pduType == SECOC_CRYPTO_PDU)
        {
          localBufferPtr = SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr;
          localBufferSize = SECOC_GET_RX_CRYPTO_PDU_LEN(pduIdx);
          receivedDataLenPtr = &SecOC_RxData[pduIdx].CryptoPdu.SduLength;
        }
        else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
        {
          localBufferPtr = SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduDataPtr;
          localBufferSize = SECOC_GET_RX_SECURED_PDU_LEN(pduIdx);
          receivedDataLenPtr = &SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength;
        }

        if (localBufferSize >= (*receivedDataLenPtr + info->SduLength))
        {
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
          if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
          {
            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00216,1 */
            bufReqRetVal = SecOC_Rx_WritePduToQueue(pduIdx,
                                                                  info->SduDataPtr,
                                                                  info->SduLength,
                                                                  0U
                                                                 );
          }
          else
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
          {
            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00128,1 */
            bufReqRetVal = BUFREQ_OK;

            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00111,1, SecOC.ASR430.Rx.SWS_SecOC_00083,1, SecOC.ASR430.Rx.SWS_SecOC_00205,1 */
            TS_MemCpy
            (
              &localBufferPtr[*receivedDataLenPtr],
              info->SduDataPtr,
              info->SduLength
            );
          }
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
          if (BUFREQ_OK != bufReqRetVal)
          {
            bufReqRetVal = BUFREQ_E_NOT_OK;
          }
          else
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
          {
            /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00003,1 */
            *receivedDataLenPtr += info->SduLength;
            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00128,1 */
            *bufferSizePtr = localBufferSize - *receivedDataLenPtr;
          }
        }
      }

      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
    }
  }
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

  return bufReqRetVal;
}

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00125,1 */
FUNC(void, SECOC_CODE) SecOC_TpRxIndication
(
  PduIdType      id,
  Std_ReturnType result
)
{
#if (SECOC_NUMBER_RX_PDUS > 0)

  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00084,1 */
  if (SECOC_INIT == SecOC_InitStatus)
  {
    uint16 pduIdx = (uint16) id;
    uint8 pduType = SECOC_UNKNOWN_PDU;
    boolean idFound = FALSE;
    BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

    idFound = SecOC_RxCheckForPduIdx(&pduIdx, &pduType);

    if (
        (SECOC_RXEVENT_STARTRECEPTION  == SecOC_RxData[pduIdx].PduREvent) &&
        (idFound                       == TRUE                            )
       )
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

      if (result == E_OK)
      {
        if (pduType == SECOC_SECURED_PDU)
        {
          bufReqRetVal = SecOC_RxCheckIncomingTpPdu(SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength, pduIdx, pduType);
          if (bufReqRetVal == BUFREQ_OK)
          {
          SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;
          }
        }
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
        else
        {
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
          if(
             (SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE == SecOC_RxData[pduIdx].VerifyStatusOverride)
             &&
             (pduType == SECOC_AUTH_PDU)
            )
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
          if(
             (
               (SECOC_OVERRIDE_SKIP_UNTIL_NOTICE == SecOC_RxData[pduIdx].VerifyStatusOverride) ||
               (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT  == SecOC_RxData[pduIdx].VerifyStatusOverride)
             )
             &&
             (pduType == SECOC_AUTH_PDU)
            )
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
          {
            SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;
            /* Clear both events to ensure a clean start for the next receiving procedure */
            SecOC_RxData[pduIdx].PduRIndicationForAuth   = SECOC_RXEVENT_NONE;
            SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
          }
          else
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
          {
            if (pduType == SECOC_AUTH_PDU)
            {
              bufReqRetVal = SecOC_RxCheckIncomingTpPdu(SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength,
                                                      pduIdx,
                                                      pduType
                                                     );
              if (bufReqRetVal == BUFREQ_OK)
              {
              SecOC_RxData[pduIdx].PduRIndicationForAuth = SECOC_RXEVENT_RXINDICATION;
              }
            }
            else
            {
              bufReqRetVal = SecOC_RxCheckIncomingTpPdu(SecOC_RxData[pduIdx].CryptoPdu.SduLength,
                                                      pduIdx,
                                                      pduType
                                                     );
              if (bufReqRetVal == BUFREQ_OK)
              {
              SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_RXINDICATION;
              }
            }

            if (
                ( SecOC_RxData[pduIdx].PduRIndicationForAuth == SECOC_RXEVENT_RXINDICATION   ) &&
                ( SecOC_RxData[pduIdx].PduRIndicationForCrypto == SECOC_RXEVENT_RXINDICATION )
               )
            {
              /* Set the PduR event to indicate that both PDUs were received and verification
               * procedure can start
               */
              SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;

              /* Clear both events to ensure a clean start for the next receiving procedure */
              SecOC_RxData[pduIdx].PduRIndicationForAuth = SECOC_RXEVENT_NONE;
              SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
            }
          }
        }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
      }
      else
      {
        if ((pduType == SECOC_AUTH_PDU) || (pduType == SECOC_SECURED_PDU))
        {
          /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00089,1, SecOC.ASR430.Rx.SWS_SecOC_00087_3,1 */
          SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_NONE;
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
          if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
          {
            SecOC_Rx_DropPduFromQueue(pduIdx);
          }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
        }
      }

      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00018,1 */
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00015,1 */
      if (TRUE == SecOC_RxConfig[pduIdx].UseSyncProcessing)
      {
        SecOC_Rx_ProcessPduStates(pduIdx);
      }
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
    }
  }
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
}
#endif /* #if (STD_ON == SECOC_RX_USETP) */

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00124,1, SecOC.EB.Rx.SWS_SecOC_00025,1 */
FUNC(void, SECOC_CODE) SecOC_RxIndication
(
          PduIdType                                id,
#if (STD_ON == SECOC_ASR403_API)
    P2VAR(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
#else /* #if (STD_ON == SECOC_ASR403_API) */
  P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
#endif /* #if (STD_ON == SECOC_ASR403_API) #else */
)
{
#if (SECOC_NUMBER_RX_PDUS > 0)

  if (
      (SECOC_INIT == SecOC_InitStatus) &&
      (NULL_PTR   != info            )
     )
  {
    PduLengthType pduLength = info->SduLength;
    uint16 pduIdx = (uint16) id;
    uint8 pduType = SECOC_UNKNOWN_PDU;

    if (TRUE  == SecOC_RxCheckForPduIdx(&pduIdx, &pduType))
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
      if (TRUE == SecOC_RxCheckBufferAvailability(pduIdx))
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00214,1, SecOC.ASR430.Rx.SWS_SecOC_00215,1 */
        if (
            (FALSE                     == SecOC_RxData[pduIdx].PduInProcess     ) ||
            (SECOC_REJECT_INCOMING_PDU != SecOC_RxConfig[pduIdx].ReceptionStrategy)
           )
        {
          BufReq_ReturnType bufReqRetVal;

          /* Check if the incoming PDU has a valid length */
          bufReqRetVal = SecOC_RxCheckIncomingIfPdu(&pduLength, pduIdx, pduType);

          if (bufReqRetVal == BUFREQ_OK)
          {
            P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) localBufferPtr = NULL_PTR;
#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
            if (SecOC_RxData[pduIdx].BufferUsed != NULL_PTR)
            {
              *SecOC_RxData[pduIdx].BufferUsed = TRUE;
            }
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */
            if (pduType == SECOC_SECURED_PDU)
            {
              SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;
              /* Store internally the PDU length for later processing */
              SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength = pduLength;
              /* Set the proper buffer to store the incoming PDU */
              localBufferPtr = SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduDataPtr;
            }
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
            else
            if (pduType == SECOC_AUTH_PDU)
            {
              SecOC_RxData[pduIdx].PduRIndicationForAuth = SECOC_RXEVENT_RXINDICATION;
              /* Store internally the PDU length for later processing */
              SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength = pduLength;
              /* Set the proper buffer to store the incoming PDU */
              localBufferPtr = SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr;
            }
            else
            {
              SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_RXINDICATION;
              /* Store internally the PDU length for later processing */
              SecOC_RxData[pduIdx].CryptoPdu.SduLength = pduLength;
              /* Set the proper buffer to store the incoming PDU */
              localBufferPtr = SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr;
            }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
            if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
            {
              /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00216,1 */
              bufReqRetVal = SecOC_Rx_WritePduToQueue(pduIdx,
                                                                    info->SduDataPtr,
                                                                    pduLength,
                                                                    pduLength
                                                                   );
            }
            else
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
            {
              /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00111,1, SecOC.ASR430.Rx.SWS_SecOC_00078,1, SecOC.ASR430.Rx.SWS_SecOC_00205,1 */
              TS_MemCpy(localBufferPtr, info->SduDataPtr, pduLength);
            }

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
            if(
               (SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE == SecOC_RxData[pduIdx].VerifyStatusOverride)
               &&
               (pduType == SECOC_AUTH_PDU)
              )
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
            if(
               (
                 (SECOC_OVERRIDE_SKIP_UNTIL_NOTICE == SecOC_RxData[pduIdx].VerifyStatusOverride) ||
                 (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT  == SecOC_RxData[pduIdx].VerifyStatusOverride)
               )
               &&
               (pduType == SECOC_AUTH_PDU)
              )
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
            {
              SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;
              /* Clear both events to ensure a clean start for the next receiving procedure */
              SecOC_RxData[pduIdx].PduRIndicationForAuth = SECOC_RXEVENT_NONE;
              SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
            }
            else
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
            {

              if (
                    ( SecOC_RxData[pduIdx].PduRIndicationForAuth == SECOC_RXEVENT_RXINDICATION   ) &&
                    ( SecOC_RxData[pduIdx].PduRIndicationForCrypto == SECOC_RXEVENT_RXINDICATION )
                 )
              {
                /* Set the PduR event to indicate that both PDUs were received and verification
                 * procedure can start
                 */
                SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_RXINDICATION;

                /* Clear both events to ensure a clean start for the next receiving procedure */
                SecOC_RxData[pduIdx].PduRIndicationForAuth   = SECOC_RXEVENT_NONE;
                SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
              }
            }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
            if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[pduIdx].ReceptionStrategy)
            {
              if ((BUFREQ_OK != bufReqRetVal) &&
                  (SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY(pduIdx) == TRUE)
                 )
              {
                SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_NONE;
                SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength = 0U;
              }
            }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
          }
        }
      }

      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

        /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00018,1 */
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00015,1 */
      if (TRUE == SecOC_RxConfig[pduIdx].UseSyncProcessing)
      {
        SecOC_Rx_ProcessPduStates(pduIdx);
      }
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
    }
  }
#else /* #if (SECOC_NUMBER_RX_PDUS > 0) */
  SECOC_PARAM_UNUSED(id);
  SECOC_PARAM_UNUSED(info);
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) #else */
}

#if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_OFF)
#if (SECOC_NUMBER_RX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00171,1 */
FUNC(void, SECOC_CODE) SecOC_MainFunctionRx
(
  void
)
{
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00172,1 */
  if (SECOC_INIT == SecOC_InitStatus)
  {
    uint16 pduIdx;

    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00174,1 */
    /* Deviation TASKING-1 */
    for (pduIdx = 0U; SECOC_NUMBER_RX_PDUS > pduIdx; pduIdx++)
    {
/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00018,1 */
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00017,1 */
      if (FALSE == SecOC_RxConfig[pduIdx].UseSyncProcessing)
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
      {
        /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00001,1 */
        SecOC_Rx_ProcessPduStates(pduIdx);
      }
    }
  }
}
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #ifdef (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_OFF) */

#if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_OFF)
#if (SECOC_NUMBER_TX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00176,1 */
FUNC(void, SECOC_CODE) SecOC_MainFunctionTx
(
  void
)
{
  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00177,1 */
  if (SECOC_INIT == SecOC_InitStatus)
  {
    uint16 pduIdx;

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00179,1 */
    /* Deviation TASKING-1 */
    for (pduIdx = 0U; SECOC_NUMBER_TX_PDUS > pduIdx; pduIdx++)
    {
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00024,1 */
#if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00023,2 */
      if (
          (SecOC_TxConfig[pduIdx].UseSyncProcessing == FALSE                             ) ||
          (SecOC_TxData[pduIdx].State               == SECOC_TX_STATE_WAITFORCONFIRMATION)
         )
#endif /* #if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON) */
      {
        /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
        SecOC_Tx_ProcessPduStates(pduIdx);
      }
    }
  }
}
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
#endif /* #ifdef (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_OFF) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00029,1 */
FUNC(void, SECOC_CODE) SecOC_BypassAuthRoutine
(
  boolean state
)
{
  SecOC_TxBypassAuthRoutineState = state;
}

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */

/*==================[internal function definitions]===============================================*/

#if (SECOC_NUMBER_RX_PDUS > 0)

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(boolean, SECOC_CODE) SecOC_RxCheckForPduIdx
(
  P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) rxPduIdx,
  P2VAR(uint8,  AUTOMATIC, SECOC_APPL_DATA) rxPduType
)
{
  boolean idFound = FALSE;
  uint16 confPduIdx;

  /* Change the external PDU ID into the equivalent internal configuration PDU ID */
  for (confPduIdx = 0U; ((confPduIdx < SECOC_NUMBER_RX_PDUS) && (idFound == FALSE)); confPduIdx++)
  {
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    if (SecOC_RxConfig[confPduIdx].UseSecPduCollection == TRUE)
    {
      if (SecOC_RxConfig[confPduIdx].PduIdForCryptoPduAtSecOC == *rxPduIdx)
      {
        *rxPduIdx = confPduIdx;
        *rxPduType = SECOC_CRYPTO_PDU;
        idFound = TRUE;
      }
      else
      if (SecOC_RxConfig[confPduIdx].PduIdForReceivedAuthPduAtSecOC == *rxPduIdx)
      {
        *rxPduIdx = confPduIdx;
        *rxPduType = SECOC_AUTH_PDU;
        idFound = TRUE;
      }
      else
      {
        /* Do nothing as the received ID is not for SecOC */
      }
    }
    else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
    {
      if (SecOC_RxConfig[confPduIdx].PduIdForSecuredPduAtSecOC == *rxPduIdx)
      {
        *rxPduIdx = confPduIdx;
        *rxPduType = SECOC_SECURED_PDU;
        idFound = TRUE;
      }
    }
  }

  if (idFound == FALSE)
  {
    *rxPduIdx = 0U;
  }

  return idFound;
}

#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
static FUNC(boolean, SECOC_CODE) SecOC_RxCheckBufferAvailability
(
  uint16 pduIdx
)
{
  boolean bufferAvailable = FALSE;

  if (NULL_PTR != SecOC_RxData[pduIdx].BufferUsed)
  {
#if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL)
    if (TRUE == SecOC_RxConfig[pduIdx].UseSecPduCollection)
    {
      if (
          (FALSE == *SecOC_RxData[pduIdx].BufferUsed) ||
          (
            ( SecOC_RxData[pduIdx].PduRIndicationForAuth == SECOC_RXEVENT_RXINDICATION   ) ||
            ( SecOC_RxData[pduIdx].PduRIndicationForCrypto == SECOC_RXEVENT_RXINDICATION )
          )
        )
      {
        bufferAvailable = TRUE;
      }
    }
    else
#endif /* #if (STD_ON == SECOC_RX_USE_SECURED_PDU_COL) */
    {
      if (FALSE == *SecOC_RxData[pduIdx].BufferUsed)
      {
        bufferAvailable = TRUE;
      }
    }
  }
  else
  {
    bufferAvailable = TRUE;
  }

  return bufferAvailable;
}
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */

static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingIfPdu
(
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) pduLength,
        uint16                              pduIdx,
        uint8                               pduType
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

  /* Is the incoming PDU the secured PDU? */
  if (pduType == SECOC_SECURED_PDU)
  {
    if (SecOC_RxConfig[pduIdx].UseDynamicLength == TRUE)
    {
      if (*pduLength > SECOC_GET_RX_SECURED_PDU_LEN(pduIdx))
      {
        *pduLength = SECOC_GET_RX_SECURED_PDU_LEN(pduIdx);
      }

      bufReqRetVal = BUFREQ_OK;
    }
    else
    {
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
      if (*pduLength >= SECOC_GET_RX_SECURED_PDU_LEN(pduIdx))
      {
        *pduLength = SECOC_GET_RX_SECURED_PDU_LEN(pduIdx);
        bufReqRetVal = BUFREQ_OK;
      }
    }
  }
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
  else
  {
    bufReqRetVal = SecOC_RxCheckIncomingIfPduCol(pduLength, pduIdx, pduType);
  }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

  return bufReqRetVal;
}

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingIfPduCol
(
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) pduLength,
        uint16                              pduIdx,
        uint8                               pduType
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

  /* Is the incoming PDU the authentic PDU? */
  if (pduType == SECOC_AUTH_PDU)
  {
    if (SecOC_RxConfig[pduIdx].UseDynamicLength == TRUE)
    {
      if (*pduLength > SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN(pduIdx))
      {
        *pduLength = SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN(pduIdx);
      }

      bufReqRetVal = BUFREQ_OK;
    }
    else
    {
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
      if (*pduLength >= SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN(pduIdx))
      {
        *pduLength = SECOC_GET_RX_RECEIVED_AUTH_PDU_LEN(pduIdx);
        bufReqRetVal = BUFREQ_OK;
      }
    }
  }
  /* The incoming PDU is a cryptographic PDU */
  else
  {
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
    if (*pduLength == SECOC_GET_RX_CRYPTO_PDU_LEN(pduIdx))
    {
      bufReqRetVal = BUFREQ_OK;
    }
  }

  return bufReqRetVal;
}
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (STD_ON == SECOC_RX_USETP)
static FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_RxCheckIncomingTpPdu
(
  uint32 pduLength,
  uint16 pduIdx,
  uint8  pduType
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;

  /* Is the incoming PDU the secured PDU? */
  if (pduType == SECOC_SECURED_PDU)
  {
    if (SecOC_RxConfig[pduIdx].UseDynamicLength == TRUE)
    {
      if (pduLength <= SECOC_GET_RX_SECURED_PDU_LEN(pduIdx))
      {
        bufReqRetVal = BUFREQ_OK;
      }
    }
    else
    {
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
      if (pduLength == SECOC_GET_RX_SECURED_PDU_LEN(pduIdx))
      {
        bufReqRetVal = BUFREQ_OK;
      }
    }
  }
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
  /* Is the incoming PDU the authentic PDU? */
  else
  if (pduType == SECOC_AUTH_PDU)
  {
    if (SecOC_RxConfig[pduIdx].UseDynamicLength == TRUE)
    {
      if (pduLength <= SECOC_GET_RX_AUTH_PDU_LEN(pduIdx))
      {
        bufReqRetVal = BUFREQ_OK;
      }
    }
    else
    {
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
      if (pduLength == SECOC_GET_RX_AUTH_PDU_LEN(pduIdx))
      {
        bufReqRetVal = BUFREQ_OK;
      }
    }
  }
  /* The incoming PDU is a cryptographic PDU */
  else
  {
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00268,1 */
    if (pduLength == SECOC_GET_RX_CRYPTO_PDU_LEN(pduIdx))
    {
      bufReqRetVal = BUFREQ_OK;
    }
  }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

  return bufReqRetVal;
}
#endif /* #if (STD_ON == SECOC_RX_USETP) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

#if (SECOC_NUMBER_TX_PDUS > 0)
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(uint8, SECOC_CODE) SecOC_TxCheckBufferAvailability
(
  uint16 pduIdx
)
{
  uint8 bufferStatus;

  /* CHECK: NOPARSE
   * Function like macro leads to unreachable code compiler (Wind River Diab) warning
   */
  SECOC_TX_GET_BUFFER_LVL1_STATUS(pduIdx, bufferStatus);
  /* CHECK: PARSE */

  if (
      (SECOC_BUFFER_FREE == bufferStatus) ||
      (
        /* Deviation TASKING-1 */
        (SECOC_BUFFER_USED      == bufferStatus                        ) &&
        (SECOC_TXEVENT_TRANSMIT == SecOC_TxData[pduIdx].TransmitEvent)
      )
     )
  {
    bufferStatus = SECOC_BUFFER_FREE;
  }

  return bufferStatus;
}

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

/*==================[end of file]=================================================================*/

