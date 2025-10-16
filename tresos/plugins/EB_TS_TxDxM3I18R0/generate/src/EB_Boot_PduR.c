/*********************************************************************************/
/*                                                                               */
/*                                  FR Stack                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               EB BOOT PDUR                                    */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Boot_PduR.c                  */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3  */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
[!NOCODE!]
[!/* Activate generation of EB_Boot_PduR.c file*/!]
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack != 'AUTOSAR'"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
#include <Std_Types.h>      /* Autosar types */
#include "EB_Prj.h"
#include <TSMem.h>          /* EB specific memory functions */
#include <APP_Boot.h>
#include <EB_Trace.h>                        /* Dbg related macros for EB */

/*                                                                               */
/*********************************************************************************/

/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*********************************************************************************/

/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
[!VAR "PDU_MAX"="num:dectoint(count(MultiTpConnections/*))"!]
/* Configuration of different connection in FrTp */
#define TP_PDU_NBR  [!"$PDU_MAX"!]
[!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
/* Init value of the last Extended RxPdu Id */
#define LAST_EXT_PDU_ID_INIT 255U
[!ENDIF!]
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
/* Structure for multiple TP connections */
typedef struct
{
  /* TxPduId */
  PduIdType       TxPduId;
  /* PDU type */
  boolean         IsFunctionalRequest;
[!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
  /* Identifier type of the RxPdu */
  u8              RxPduIdType;
[!ENDIF!]
} TPPduInfoType;
[!ENDIF!]

/** \brief State of a buffer in the TP_UDS module **/
typedef enum
{
  /** \brief Buffer is not in use right now */
  BUF_IDLE,
  /** \brief Buffer is used for reception */
  BUF_RX,
  /** \brief Buffer is used for transmission */
  BUF_TX
} TP_UDS_BufferStateType;

typedef struct
{
  /** \brief Length of valid data in bytes stored in this buffer
   *
   * The length information is used for reception and transmission.*/
  PduLengthType       filledLen;

  /** \brief Holds index of valid data in bytes to be transmitted in this buffer */
  PduLengthType       dataMark;

  /** \brief Holds index of Confirmed data in bytes in this buffer */
  PduLengthType       confirmedDataMark;

  /** \brief State of this buffer */
  TP_UDS_BufferStateType state;

  /** \brief RxPduId which was used to fill the buffer
   *
   * Only valid if the buffer state is BUF_RX  */
  PduIdType           originatingRxPduId;

} TP_UDS_BufferInfoType;

typedef struct
{
  /** \brief location of buffer **/
  uint8 *RxptrBuffer;
  /** \brief status information for this buffer configuration **/
  TP_UDS_BufferInfoType *RxbufferInfo;
    /** \brief location of buffer **/
  uint8 *TxptrBuffer;
  /** \brief Size of this buffer **/
  PduLengthType size;
} TP_UDS_BufferConfigType;

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

#define EB_BUFF_TP_WRAP_START_SEC_VAR
#include <MemMap.h>
static uint8 TPFuncBuffer[TP_RX_FUNC_BUFFERSIZE];
static uint8 TPRxPhysBuffer[TP_RX_PHYS_BUFFERSIZE];
static uint8 TPTxPhysBuffer[TP_RX_PHYS_BUFFERSIZE];
#define EB_BUFF_TP_WRAP_STOP_SEC_VAR
#include <MemMap.h>

static TP_UDS_BufferInfoType TP_UDS_TxBufferInfo = { 0, 0, 0, BUF_IDLE, 0 };
static TP_UDS_BufferConfigType TP_UDS_TxBufferConfig = { NULL_PTR,
                                                         NULL_PTR,
                                                         NULL_PTR,
                                                         0 };

static TP_UDS_BufferInfoType TP_UDS_RxPhysBufferInfo = { 0, 0, 0, BUF_IDLE, 0 };
static TP_UDS_BufferConfigType TP_UDS_RxPhysBufferConfig = { &TPRxPhysBuffer[0],
                                                             &TP_UDS_RxPhysBufferInfo,
                                                             &TPTxPhysBuffer[0],
                                                             TP_RX_PHYS_BUFFERSIZE
                                                           };

static TP_UDS_BufferInfoType TP_UDS_RxFuncBufferInfo = { 0, 0, 0, BUF_IDLE, 0 };
static TP_UDS_BufferConfigType TP_UDS_RxFuncBufferConfig = { &TPFuncBuffer[0],
                                                             &TP_UDS_RxFuncBufferInfo,
                                                             &TPFuncBuffer[0],
                                                             TP_RX_FUNC_BUFFERSIZE
                                                           };


[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
[!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
/* Identifier of the last Extended RxPdu Id */
static PduIdType LastRxPduIdExtended = LAST_EXT_PDU_ID_INIT;
[!ENDIF!]

/* Current PduId (Index in EB_PduInfo) */
static PduIdType TPPhyPduIndex[PDUR_MAX_PHY_RX_ALLOWED];
static PduIdType TPFuncPduIndex;
static TPPduInfoType TPTxPduInfo[PDUR_MAX_TX_ALLOWED];

static u8 TPTxPduCount = 0U;


[!VAR "PDU_IDX"="1"!]
static const TPPduInfoType TPPduInfo[TP_PDU_NBR]={[!/*
    For each MultiTpConnections defined in EB
    */!]
    [!FOR "PDU_IDX" = "1" TO "$PDU_MAX"!]
    [!VAR "TXPDU"="num:MultiTpConnections/*[number($PDU_IDX)]/TxPdu"!]
    [!VAR "ADDRESS_TYPE"="MultiTpConnections/*[number($PDU_IDX)]/AddressType"!]
    /* RxPdu [!"num:dectoint(($PDU_IDX)-1)"!]*/
    {
        [!WS"8"!][!"$TXPDU"!]U,[!WS"12"!]/* TxPduId */
        [!WS"8"!][!IF "$ADDRESS_TYPE = 'FUNCTIONAL'"!]TRUE[!ELSE!]FALSE[!ENDIF!][!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!],[!ENDIF!][!WS"9"!]/* IsPduFunctional */
[!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
        [!VAR "CANTP_RX_IDX" = "1"!]
        [!VAR "CANTP_RX_MAX" = "num:dectoint(count(as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*))"!]
        [!FOR "CANTP_RX_IDX" = "1" TO "$CANTP_RX_MAX"!][!/*
        Collect the corresponding reference according to Id configured in CanTpRxNsdu
        */!]
        [!IF "($PDU_IDX)-1 = num:dectoint(number(as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*[number($CANTP_RX_IDX)]/CanTpRxNSduId))"!]
        [!VAR "CANTP_RX_PDU_REF" = "name(node:ref(as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*[number($CANTP_RX_IDX)]/CanTpRxNPdu/CanTpRxNPduRef))"!][!/*
        Collect the corresponding Can Id Type according to Id reference defined in CanIfRxPduCfg
        */!][!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!]
        [!IF "$CANTP_RX_PDU_REF = name(node:ref(CanIfRxPduRef))"!]
        [!WS"8"!][!IF "text:match(CanIfRxPduCanIdType,'EXTENDED*')"!]EXTENDED_ID[!ELSE!]STANDARD_ID[!ENDIF!][!WS"4"!]/* Can Identifier Type */
        [!ENDIF!]
        [!ENDLOOP!]
        [!ENDIF!]
        [!ENDFOR!]
[!ENDIF!]
    },
    [!ENDFOR!]
};
[!ENDIF!]
/* Number of received request with transmission not yet done */
static u8 TPPhyPduCount = 0U;
static u8 TPFuncPduCount = 0U;

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
static TP_UDS_BufferConfigType *TP_UDS_GetBufferConfig (PduIdType PduId);
/*                                                                               */
/*********************************************************************************/


/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/

/*--------------------------------[TP_RxEnable]----------------------------------*/
/* Function used to lock message reception buffers */
tTpStatus TP_RxEnable (tTpMsgIdx uMsgIdx, tTpRxEnable uRxEnable)
{
  /* Return status */
  tTpStatus eStatus;

  DBG_TP_RXENABLE_ENTRY(uMsgIdx, uRxEnable);

  eStatus = TP_ERR_OK;

  /* set state of buffer to BUF_RX/BUF_IDLE based on uMsgIdx */
  if (uMsgIdx < TP_MSG_MAX)
  {
    if (uRxEnable == TP_RX_ENABLE_ON )
    {
      if((uMsgIdx == PDUR_FUNCTIONALREQ_TPSDU) && (uMsgIdx != m_ubTpMsgIdxNrc78))
      {
        TP_UDS_RxFuncBufferInfo.state = BUF_IDLE;
      }
      else if ((uMsgIdx == PDUR_BL_DIAGREQ_TPSDU) && (uMsgIdx != m_ubTpMsgIdxNrc78))
      {
        TP_UDS_RxPhysBufferInfo.state = BUF_IDLE;
      }
      else
      {
        eStatus = TP_ERR_IDX;
      }
    }
    else
    {
      if(uMsgIdx == PDUR_FUNCTIONALREQ_TPSDU)
      {
        TP_UDS_RxFuncBufferInfo.state = BUF_RX;
      }
      else
      {
        TP_UDS_RxPhysBufferInfo.state = BUF_RX;
      }
    }
  }
  /* The message index input parameter is out of range, then error */
  else
  {
    eStatus = TP_ERR_IDX;
  }

  DBG_TP_RXENABLE_EXIT(eStatus);
  return eStatus;
}


/*------------------------------[TP_SetMsgData]----------------------------------*/
/* Function used to trigger transmission */
tTpStatus TP_SetMsgData (tTpMsgIdx uMsgIdx, u16 uwLen, u8 *paubData)
{
    tTpStatus retVal = TP_ERR_LEN;
    PduIdType RxPduId;
    PduInfoType TxInformation;
    Std_ReturnType RetCode;

    DBG_TP_SETMSGDATA_ENTRY(uMsgIdx,uwLen,paubData);

    if((paubData != NULL_PTR) && (uwLen != 0U))
    {
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
        if (PDUR_BL_DIAGREQ_TPSDU == uMsgIdx)
        {
            /* Get the Id of the RxPdu */
            RxPduId = TPPhyPduIndex[0U];

            /* For Extended RxPdu */
            if (EXTENDED_ID == TPPduInfo[RxPduId].RxPduIdType)
            {
                /* Get the Id of the corresponding TxPdu defined in configuration */
                TPTxPduInfo[TPTxPduCount] = TPPduInfo[RxPduId];

                /* Update the Identifier of the last Extended RxPdu */
                LastRxPduIdExtended = RxPduId;
            }
            /* For Standard RxPdu */
            else
            {
                /* If no extended RxPdu Identifier was already stored */
                if (LAST_EXT_PDU_ID_INIT == LastRxPduIdExtended)
                {
                    /* Get the Id of the corresponding TxPdu defined in configuration */
                    TPTxPduInfo[TPTxPduCount] = TPPduInfo[RxPduId];
                }
                /* If an extended RxPdu Identifier was already stored */
                else
                {
                    /* Get the last Extended RxPdu Id stored */
                    TPTxPduInfo[TPTxPduCount] = TPPduInfo[LastRxPduIdExtended];
                }
            }
        }
        else
        {
            RxPduId = TPFuncPduIndex;
            TPTxPduInfo[TPTxPduCount] = TPPduInfo[RxPduId];
        }
    [!ELSE!]
        if (PDUR_BL_DIAGREQ_TPSDU == uMsgIdx)
        {
            RxPduId = TPPhyPduIndex[0U];
            TPTxPduInfo[TPTxPduCount] = TPPduInfo[RxPduId];
        }
        else
        {
            RxPduId = TPFuncPduIndex;
            TPTxPduInfo[TPTxPduCount] = TPPduInfo[RxPduId];
        }
    [!ENDIF!]
[!ELSE!]
        RxPduId = PDUR_TX_TPSDU;
        OSC_PARAM_UNUSED(uMsgIdx);
[!ENDIF!]

        TP_UDS_TxBufferConfig.TxptrBuffer = paubData;
        TP_UDS_TxBufferInfo.filledLen = uwLen;
        TxInformation.SduDataPtr = NULL_PTR;
        TxInformation.SduLength = (PduLengthType)uwLen;

[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
        RetCode = PduR_EBTransmit(TPTxPduInfo[TPTxPduCount].TxPduId, &TxInformation);
[!ELSE!]
        RetCode = PduR_EBTransmit(RxPduId, &TxInformation);
[!ENDIF!]

        if (0U == RetCode)
        {
            retVal = TP_ERR_OK;
        }
    }

[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    /* Increment the number of PDU stored in TPTxPduInfo buffer */
    TPTxPduCount++;
[!ENDIF!]


    DBG_TP_SETMSGDATA_EXIT(retVal);
    return retVal;
}

/*----------------------------------{TP_SetMsgDataCopy}--------------------------------*/
tTpStatus TP_SetMsgDataCopy (tTpMsgIdx uMsgIdx, u16 uwLen, u8 *paubData)
{
    tTpStatus eStatus;

    DBG_TP_SETMSGDATACOPY_ENTRY(uMsgIdx,uwLen,paubData);

    eStatus = TP_SetMsgData(uMsgIdx, uwLen, paubData);

    DBG_TP_SETMSGDATACOPY_EXIT(eStatus);
    return eStatus;
}

/*------------------------------[TP_GetMsgData]----------------------------------*/
/* Function used to get pointer/length of received message data */
tTpStatus TP_GetMsgData (tTpMsgIdx uMsgIdx, u16 *puwLen, u8 **paubData)
{
  /* Return status */
  tTpStatus eStatus = TP_ERR_OK;
  TP_UDS_BufferConfigType *curRxBufferConfig = NULL_PTR;
  TP_UDS_BufferInfoType *curRxBufferInfo = NULL_PTR;

  DBG_TP_GETMSGDATA_ENTRY(uMsgIdx,puwLen,paubData);

  /* The message index input parameter is in expected range */
  if(uMsgIdx < TP_MSG_MAX)
  {
    curRxBufferConfig = TP_UDS_GetBufferConfig(uMsgIdx);
    curRxBufferInfo = curRxBufferConfig->RxbufferInfo;

    if((puwLen != NULL_PTR) && (paubData != NULL_PTR))
    {
        /* Read the message length */
        *puwLen = curRxBufferInfo->filledLen;
        /* Read the message data buffer address */
        *paubData = curRxBufferConfig->RxptrBuffer;

        TP_UDS_ReleaseBuffers(uMsgIdx);
    }
  }
  /* The message index input parameter is out of range, then error */
  else
  {
      eStatus = TP_ERR_IDX;
  }

  DBG_TP_GETMSGDATA_EXIT(eStatus);
  /* Return the status */
  return (eStatus);
}

/* Functions of TP currently stubbed */
/* frame reception used for streaming currently not implemented */
tTpStatus TP_ReceiveFrame (tTpMsgIdx uMsgIdx)
{
  OSC_PARAM_UNUSED(uMsgIdx);

  return TP_ERR_OK;
}


/*------------------------------[TP_ComNAsInd]----------------------------------*/
/* not needed, Com API not called when using Fr stack */
void TP_ComNAsInd (tTpMsgIdx uMsgIdx)
{
  OSC_PARAM_UNUSED(uMsgIdx);

  return;
}


/*------------------------------[TP_ComTxConf]----------------------------------*/
/* not needed, Com API not called when using Fr stack */
void TP_ComTxConf (tTpMsgIdx uMsgIdx)
{
  OSC_PARAM_UNUSED(uMsgIdx);

  return;
}

/*------------------------------[TP_ComTxConfFC]----------------------------------*/
/* not needed, Com API not called when using Fr stack */
void TP_ComTxConfFC (tTpMsgIdx uMsgIdx)
{
  OSC_PARAM_UNUSED(uMsgIdx);

  return;
}

/*---------------------------------[TP_SendMsg]-----------------------------------*/
/* sending of message is triggered in TP_SetMsgData */
tTpStatus TP_SendMsg (tTpMsgIdx uMsgIdx)
{
  OSC_PARAM_UNUSED(uMsgIdx);

  return TP_ERR_OK;
}


/*---------------------------------[TP_Init]-------------------------------------*/
/* not needed */
void TP_Init(void)
{
  ;
}


/*---------------------------------[TP_Manage]----------------------------------*/
/* not needed */
void TP_Manage(void)
{
  ;
}

/*----------------------[EB_StartOfReception]----------------------------*/
/* request buffer for TP message reception */
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
#define RX_PDU_ID LocalRxPduId
[!ELSE!]
#define RX_PDU_ID RxPduId
[!ENDIF!]
FUNC(BufReq_ReturnType, PDUR_CODE) EB_StartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  TP_UDS_BufferConfigType *curRxBufferConfig;
  TP_UDS_BufferInfoType *curRxBufferInfo;
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
  PduIdType LocalRxPduId;

  DBG_EB_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr);

  /*Check Pdu in PduConfig*/
  if (RxPduId < TP_PDU_NBR)
  {
    /*Check if functional or physical management shall be done*/
    if(TRUE == TPPduInfo[RxPduId].IsFunctionalRequest)
    {
        RX_PDU_ID = PDUR_FUNCTIONALREQ_TPSDU;
    }
    else
    {
        RX_PDU_ID = PDUR_BL_DIAGREQ_TPSDU;
    }
[!ENDIF!]
    if(((RX_PDU_ID == PDUR_BL_DIAGREQ_TPSDU) && (TPPhyPduCount < PDUR_MAX_PHY_RX_ALLOWED))
       || ((RX_PDU_ID == PDUR_FUNCTIONALREQ_TPSDU) && (TPFuncPduCount < PDUR_MAX_FUNC_RX_ALLOWED)))
    {
        curRxBufferConfig = TP_UDS_GetBufferConfig(RX_PDU_ID);
        curRxBufferInfo = curRxBufferConfig->RxbufferInfo;

        if((BufferSizePtr != NULL_PTR) && (RX_PDU_ID < NUMBER_OF_RXBUFFERS))
        {
          if(BUF_IDLE != curRxBufferInfo->state)
          {
              curRxBufferInfo->state = BUF_IDLE;

              if(RX_PDU_ID == PDUR_BL_DIAGREQ_TPSDU)
              {
                  TP_RxIndFullDuplex( (tTpMsgIdx)PDUR_BL_DIAGREQ_TPSDU, TP_MSG_STATUS_NPDU);
              }
              else
              {
                  TP_RxInd( (tTpMsgIdx)PDUR_FUNCTIONALREQ_TPSDU, TP_MSG_STATUS_COM_NOK );
              }
          }

          if(TpSduLength == 0U)
          {
          /*  When the API is invoked with TpSduLength equal to 0,
           *  the value BUFREQ_OK shall be returned and BufferSizePtr shall be set to the
           *  free size of the Rx buffer.
           */
          *BufferSizePtr = curRxBufferConfig->size;
          retVal = BUFREQ_OK;
		  PROG_TpStartOfReceptionInd(TP_MSG_STATUS_OK);
          }
          else if(TpSduLength <= (curRxBufferConfig->size))
          {
          /* allocate Rx buffer */
          curRxBufferInfo->state              = BUF_RX;
          /* store the received DataLength */
          curRxBufferInfo->filledLen          = TpSduLength;
          /* remember RX_PDU_ID */
          curRxBufferInfo->originatingRxPduId = RX_PDU_ID;
          /* set current dataMark to 0 to signal where to copy new data. */
          curRxBufferInfo->dataMark = 0U;
          /* Update size of the allocated buffer to caller */
          *BufferSizePtr = curRxBufferConfig->size;

          retVal = BUFREQ_OK;
		  PROG_TpStartOfReceptionInd(TP_MSG_STATUS_OK);
          }
          else
          {
          retVal = BUFREQ_E_OVFL;
		  PROG_TpStartOfReceptionInd(TP_MSG_STATUS_COM_NOK);
          }

          if(BUFREQ_OK == retVal)
          {
            /* Stop the Session Timer */
            EB_StopSessionTimer();
          }
        }
        else
        {
          retVal = BUFREQ_E_NOT_OK;
		  PROG_TpStartOfReceptionInd(TP_MSG_STATUS_COM_NOK);
        }
    }
    else
    {
      retVal = BUFREQ_E_NOT_OK;
	  PROG_TpStartOfReceptionInd(TP_MSG_STATUS_COM_NOK);
    }
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
  }
  else
  {
    /*Unknow PduId*/
    retVal = BUFREQ_E_NOT_OK;
	PROG_TpStartOfReceptionInd(TP_MSG_STATUS_COM_NOK);
  }
[!ELSE!]
  DBG_EB_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr);
[!ENDIF!]
  DBG_EB_STARTOFRECEPTION_EXIT(retVal);
  return retVal;
}
#undef RX_PDU_ID

/*--------------------------[EB_CopyRxData]-------------------------------*/
/* Copy receive TP buffer to the wrapper receive buffer for every received segment */
FUNC(BufReq_ReturnType, PDUR_CODE) EB_CopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  TP_UDS_BufferConfigType *curRxBufferConfig = NULL_PTR;
  TP_UDS_BufferInfoType *curRxBufferInfo = NULL_PTR;
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
  PduIdType LocalRxPduId;

  DBG_EB_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr);

  /*Check if functional or physical management shall be done*/
  if(TRUE == TPPduInfo[RxPduId].IsFunctionalRequest)
  {
      LocalRxPduId = PDUR_FUNCTIONALREQ_TPSDU;
  }
  else
  {
      LocalRxPduId = PDUR_BL_DIAGREQ_TPSDU;
  }
[!ELSE!]
  DBG_EB_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr);
[!ENDIF!]

  if((PduInfoPtr != NULL_PTR) && (BufferSizePtr != NULL_PTR))
  {
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    curRxBufferConfig = TP_UDS_GetBufferConfig(LocalRxPduId);
[!ELSE!]
    curRxBufferConfig = TP_UDS_GetBufferConfig(RxPduId);
[!ENDIF!]
    curRxBufferInfo = curRxBufferConfig->RxbufferInfo;

    if ((curRxBufferInfo->state) == BUF_RX)
    {
      if ((PduInfoPtr->SduLength == 0U) || (PduInfoPtr->SduDataPtr == NULL_PTR))
      {
        /* return available buffer size */
        *BufferSizePtr = (curRxBufferConfig->size) - (curRxBufferInfo->dataMark);
        retVal = BUFREQ_OK;
      }
      else
      {
        if(((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) <= (curRxBufferInfo->filledLen))
        {
          /* copy payload into receive buffer */
          TS_MemCpy(&(curRxBufferConfig->RxptrBuffer[curRxBufferInfo->dataMark]),
                    PduInfoPtr->SduDataPtr, (uint16)PduInfoPtr->SduLength
                   );

           curRxBufferInfo->dataMark = (curRxBufferInfo->dataMark) + (PduInfoPtr->SduLength);

           /* Return remaining free space in receive buffer after completion of this call */
          *BufferSizePtr = (curRxBufferConfig->size) - (curRxBufferInfo->dataMark);

[!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
          /* Call TP streaming except for the last segment */
          if(((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) < (curRxBufferInfo->filledLen))
          {
            TP_StreamingFrameReceived((curRxBufferInfo->dataMark - 2U),curRxBufferConfig->RxptrBuffer);
          }
[!ENDIF!]
          retVal = BUFREQ_OK;
        }
        else
        {
          retVal = BUFREQ_E_NOT_OK;
        }
     }
    }
    else
    {
      /* No reception initiated on this RxPduId */
      *BufferSizePtr = 0U;
    }
  }
  else
  {
    retVal = BUFREQ_E_NOT_OK;
  }

  DBG_EB_COPYRXDATA_EXIT(retVal);
  return retVal;
}


/*--------------------------[EB_TpRxIndication]-----------------------------*/
/* forward RxIndication */
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
#define RX_PDU_ID LocalRxPduId
[!ELSE!]
#define RX_PDU_ID RxPduId
[!ENDIF!]
FUNC(void, PDUR_CODE) EB_TpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
)
{
    TP_UDS_BufferConfigType *curRxBufferConfig;
    TP_UDS_BufferInfoType *curRxBufferInfo;
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    PduIdType LocalRxPduId;

    DBG_EB_TPRXINDICATION_ENTRY(RxPduId,Result);

    /*Check if functional or physical management shall be done*/
    if(TRUE == TPPduInfo[RxPduId].IsFunctionalRequest)
    {
        RX_PDU_ID = PDUR_FUNCTIONALREQ_TPSDU;
    }
    else
    {
        RX_PDU_ID = PDUR_BL_DIAGREQ_TPSDU;
    }
[!ELSE!]
    DBG_EB_TPRXINDICATION_ENTRY(RxPduId,Result);
[!ENDIF!]

    curRxBufferConfig = TP_UDS_GetBufferConfig(RX_PDU_ID);
    curRxBufferInfo = curRxBufferConfig->RxbufferInfo;

    if(Result == NTFRSLT_OK)
    {
        if(RX_PDU_ID == PDUR_BL_DIAGREQ_TPSDU)
        {
            TP_RxIndFullDuplex( (tTpMsgIdx)PDUR_BL_DIAGREQ_TPSDU, TP_MSG_STATUS_OK );
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
            /* Store the PDU index and increment the number of frame in treatment */
            TPPhyPduIndex[TPPhyPduCount] = RxPduId;
[!ENDIF!]
            TPPhyPduCount++;
        }
        else
        { /* If message received is a TP with supressPosBit set */
            if((curRxBufferConfig->RxptrBuffer[0] == UDS_SRV_TP) && (curRxBufferConfig->RxptrBuffer[1] == 0x80U) && (curRxBufferInfo->filledLen == 2U))
            {
                /* Only reload S3 timer */
                UDS_ReloadTStopDiag();
            }
            else
            {
                TP_RxInd( (tTpMsgIdx)PDUR_FUNCTIONALREQ_TPSDU, TP_MSG_STATUS_OK );
                /* Store the PDU index and increment the number of frame in treatment */
                TPFuncPduCount++;
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
                TPFuncPduIndex = RxPduId;
[!ENDIF!]
            }
        }
    }
    else /* buffer must be freed */
    {
        if(RX_PDU_ID == PDUR_BL_DIAGREQ_TPSDU)
        {
            TP_RxIndFullDuplex( (tTpMsgIdx)PDUR_BL_DIAGREQ_TPSDU, TP_MSG_STATUS_COM_NOK );
        }
        else
        {
            TP_RxInd( (tTpMsgIdx)PDUR_FUNCTIONALREQ_TPSDU, TP_MSG_STATUS_COM_NOK );
        }
    }

    DBG_EB_TPRXINDICATION_EXIT();
}
#undef RX_PDU_ID

/*----------------------------[EB_CopyTxData]-------------------------------*/
/* Copy transmission TP buffer */
FUNC(BufReq_ReturnType, PDUR_CODE) EB_CopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  DBG_EB_COPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr);

  OSC_PARAM_UNUSED(TxPduId);

  if(PduInfoPtr != NULL_PTR)
  {
    if(PduInfoPtr->SduLength == 0U)
    {
      /* FrTp polls length of transmission, supply length of data */
      *AvailableDataPtr = TP_UDS_TxBufferInfo.filledLen;
      retVal = BUFREQ_OK;
    }
    else if (RetryInfoPtr == NULL_PTR)
    {
      /* copy data */
      TS_MemCpy(PduInfoPtr->SduDataPtr, &TP_UDS_TxBufferConfig.TxptrBuffer[TP_UDS_TxBufferInfo.dataMark],
                (uint16)PduInfoPtr->SduLength);
      TP_UDS_TxBufferInfo.dataMark += PduInfoPtr->SduLength;
      *AvailableDataPtr = TP_UDS_TxBufferInfo.filledLen - TP_UDS_TxBufferInfo.dataMark;

      retVal = BUFREQ_OK;
    }
    else
    {
      retVal = BUFREQ_E_NOT_OK;
    }
  }
  else
  {
    retVal = BUFREQ_E_NOT_OK;
  }

  DBG_EB_COPYTXDATA_EXIT(retVal);

  return retVal;
}


/*--------------------------[EB_TpTxConfirmation]---------------------------*/
/* forward TxConfirmation */
FUNC(void, PDUR_CODE) EB_TpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
)
{
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    boolean ubIsTxFunctional;

    DBG_EB_TPTXCONFIRMATION_ENTRY(TxPduId,Result);

    ubIsTxFunctional = TPTxPduInfo[0].IsFunctionalRequest;

    if (TPTxPduCount > 0U)
    {
        TPTxPduCount--;

        if(TPTxPduCount == 1U)
        {
            TPTxPduInfo[0].IsFunctionalRequest = TPTxPduInfo[1].IsFunctionalRequest;
        }
    }
[!ENDIF!]

    if(Result == NTFRSLT_OK)
    {
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
        if(FALSE == ubIsTxFunctional)
[!ELSE!]
        if(TxPduId == PDUR_TX_TPSDU_CONF)
[!ENDIF!]
        {
            TP_TxConfFullDuplex( (tTpMsgIdx)PDUR_BL_DIAGREQ_TPSDU, TP_MSG_STATUS_OK );
        }
        else
        {
            TP_TxConf( (tTpMsgIdx)PDUR_FUNCTIONALREQ_TPSDU, TP_MSG_STATUS_OK );
        }
    }
    else if(Result == NTFRSLT_E_TIMEOUT_A)
    {
        APP_ComNAsInd((tComFrameIdx) TxPduId);
    }
    else
    {
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
        if(FALSE == ubIsTxFunctional)
[!ELSE!]
        if(TxPduId == PDUR_TX_TPSDU_CONF)
[!ENDIF!]
        {
            TP_TxConfFullDuplex( (tTpMsgIdx)PDUR_BL_DIAGREQ_TPSDU, TP_MSG_STATUS_COM_NOK );
        }
        else
        {
            TP_TxConf( (tTpMsgIdx)PDUR_FUNCTIONALREQ_TPSDU, TP_MSG_STATUS_COM_NOK );
        }
    }

    if(PDUR_TX_TPSDU_CONF == m_ubTpMsgIdxNrc78)
    {
        /* free Tx communication channel only */
        TP_UDS_ReleaseBuffers(PDUR_PHYRESP_TPSDU);
    }
    else
    {
        /* free communication channel */
        TP_UDS_ReleaseBuffers(PDUR_ALL_PDU);
    }

    DBG_EB_TPTXCONFIRMATION_EXIT();
}


/*--------------------------[TP_UDS_ReleaseBuffers]------------------------------*/
/* Function to release Rx and Tx buffers */
void TP_UDS_ReleaseBuffers(tTpMsgIdx uMsgIdx)
{
  TP_UDS_BufferInfoType *curBufferInfo;

  DBG_TP_UDS_RELEASEBUFFERS_ENTRY(uMsgIdx);

  switch(uMsgIdx)
  {
    case PDUR_BL_DIAGREQ_TPSDU :
        curBufferInfo = &TP_UDS_RxPhysBufferInfo;

        curBufferInfo->state = BUF_IDLE;
        /* reset filled buffer length */
        curBufferInfo->filledLen = 0;
        /* reset buffer data marking variables */
        curBufferInfo->confirmedDataMark = 0U;
        curBufferInfo->dataMark = 0U;
    break;

    case PDUR_FUNCTIONALREQ_TPSDU :
        curBufferInfo = &TP_UDS_RxFuncBufferInfo;

        curBufferInfo->state = BUF_IDLE;
        /* reset filled buffer length */
        curBufferInfo->filledLen = 0;
        /* reset buffer data marking variables */
        curBufferInfo->confirmedDataMark = 0U;
        curBufferInfo->dataMark = 0U;
    break;
    case PDUR_PHYRESP_TPSDU :
        curBufferInfo = &TP_UDS_TxBufferInfo;

        curBufferInfo->state = BUF_IDLE;
        /* reset filled buffer length */
        curBufferInfo->filledLen = 0;
        /* reset buffer data marking variables */
        curBufferInfo->confirmedDataMark = 0U;
        curBufferInfo->dataMark = 0U;
    break;
    default:
        curBufferInfo = &TP_UDS_TxBufferInfo;

        curBufferInfo->state = BUF_IDLE;
        /* reset filled buffer length */
        curBufferInfo->filledLen = 0;
        /* reset buffer data marking variables */
        curBufferInfo->confirmedDataMark = 0U;
        curBufferInfo->dataMark = 0U;

        curBufferInfo = &TP_UDS_RxFuncBufferInfo;

        curBufferInfo->state = BUF_IDLE;
        /* reset filled buffer length */
        curBufferInfo->filledLen = 0;
        /* reset buffer data marking variables */
        curBufferInfo->confirmedDataMark = 0U;
        curBufferInfo->dataMark = 0U;
    break;
  }

  DBG_TP_UDS_RELEASEBUFFERS_EXIT();

}

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------[TP_UDS_GetBufferConfig]------------------------------*/
/* Function to get buffer config from PduId */
static TP_UDS_BufferConfigType *TP_UDS_GetBufferConfig (PduIdType PduId)
{
  TP_UDS_BufferConfigType *BufferConfig;

  if(PduId == PDUR_BL_DIAGREQ_TPSDU)
  {
    BufferConfig = &TP_UDS_RxPhysBufferConfig;
  }
  else if(PduId == PDUR_FUNCTIONALREQ_TPSDU)
  {
    BufferConfig = &TP_UDS_RxFuncBufferConfig;
  }
  else
  {
    BufferConfig = NULL_PTR;
  }
  return BufferConfig;
}

/*-------------------------[TP_UDS_GetBufferSize]------------------------------*/
/* Function to get buffer size from PduId */
PduLengthType TP_UDS_GetBufferSize (PduIdType PduId)
{
  TP_UDS_BufferConfigType *BufferConfig;
  PduLengthType UDS_BufferSize=0;

  if(PduId == PDUR_BL_DIAGREQ_TPSDU)
  {
    BufferConfig = &TP_UDS_RxPhysBufferConfig;
    UDS_BufferSize = BufferConfig->size;
  }
  else if(PduId == PDUR_FUNCTIONALREQ_TPSDU)
  {
    BufferConfig = &TP_UDS_RxFuncBufferConfig;
    UDS_BufferSize = BufferConfig->size;
  }
  else
  {
    BufferConfig = NULL_PTR;
  }
  return UDS_BufferSize;
}
/*********************************************************************************/
/* Name: TP_SwapBuffer                                                           */
/*-------------------------------------------------------------------------------*/
/* Description: Allow to swap both buffer for full duplex management             */
/*********************************************************************************/
tTpStatus TP_SwapBuffer(tTpMsgIdx uMsgIdx)
{
    tTpStatus eTpStatus;
    u8* pubTemp;

    DBG_TP_SWAPBUFFER_ENTRY(uMsgIdx);

    eTpStatus = TP_ERR_OK;

    if (uMsgIdx < TP_MSG_MAX)
    {
        /* Swap the Rx and Tx buffer */
        pubTemp = TP_UDS_RxPhysBufferConfig.RxptrBuffer;
        TP_UDS_RxPhysBufferConfig.RxptrBuffer = TP_UDS_RxPhysBufferConfig.TxptrBuffer;
        TP_UDS_RxPhysBufferConfig.TxptrBuffer = pubTemp;
    }
    /* The message index input parameter is out of range, then error */
    else
    {
        eTpStatus = TP_ERR_IDX;
    }

    DBG_TP_SWAPBUFFER_EXIT(eTpStatus);
    return eTpStatus;
}
/* - End TP_SwapBuffer                                                           */
/*-------------------------------------------------------------------------------*/



/*----------------------[PDUR_APP_Wrapper_TriggerTransmit]-------------------------*/
/* Function stubbed to allow compilation */
Std_ReturnType PDUR_APP_Wrapper_TriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType retVal = E_OK;

  OSC_PARAM_UNUSED(TxPduId);
  OSC_PARAM_UNUSED(PduInfoPtr);

  return retVal;
}

/*----------------------[PDUR_APP_Wrapper_TxConfirmation]-------------------------*/
/* Function stubbed to allow compilation */
void PDUR_APP_Wrapper_TxConfirmation
(
        PduIdType TxPduId
)
{
  OSC_PARAM_UNUSED(TxPduId);

  return;
}

/*----------------------[PDUR_APP_Wrapper_RxIndication]-------------------------*/
/* Function to get Network status */
void PDUR_APP_Wrapper_RxIndication
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
  DBG_PDUR_APP_WRAPPER_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

    /* Check if NEtworkStatus PDU is received
     * Config shall be done in FrIf/FrIfConfig/FrIfConfig/FrIfPdu/<pdu>/FrIfUpperLayerHandleId
     * and reported in EB_Boot_PduR.h
     */
[!IF "as:modconf('Prog')/General/Network_Management = 'true'"!]
    if(PDUR_APP_NETWORKSTATUS_PDUIDX == RxPduId)
    {
        /* get the first 2 bytes as NetworkStatus Signal and update PROG*/
        PROG_SetNetworkStatus((uint16) ( (uint16)((uint16)(PduInfoPtr->SduDataPtr[0]) << 8U) | (uint16)(PduInfoPtr->SduDataPtr[1]) ));
    }
    else
    {
        /*no processing for other Pdus*/
    }
[!ELSE!]
    OSC_PARAM_UNUSED(RxPduId);
    OSC_PARAM_UNUSED(PduInfoPtr);
[!ENDIF!]
  DBG_PDUR_APP_WRAPPER_RXINDICATION_EXIT();
  return;
}

/*----------------------{EB_GetCurrentRxPdu}-------------------------------*/
/* Function to get Current RxPduId */
void EB_GetCurrentRxPdu(u8 * ubCurrentRxPduId)
{
    DBG_EB_GETCURRENTRXPDU_ENTRY(ubCurrentRxPduId);
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    *ubCurrentRxPduId = (u8)(TPPhyPduIndex[0] & 0x00FFU);
[!ELSE!]
    *ubCurrentRxPduId = 0U;
[!ENDIF!]
    DBG_EB_GETCURRENTRXPDU_EXIT();
}
/*----------------------{end EB_GetCurrentRxPdu}----------------------------*/

/*----------------------{EB_SetCurrentRxPdu}--------------------------------*/
/* Function to get Current RxPduId */
void EB_SetCurrentRxPdu(u8 ubCurrentRxPduId)
{
    DBG_EB_SETCURRENTRXPDU_ENTRY(ubCurrentRxPduId);
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
    TPPhyPduIndex[0] = (u16)(ubCurrentRxPduId);
[!ELSE!]
    OSC_PARAM_UNUSED(ubCurrentRxPduId);
[!ENDIF!]
    DBG_EB_SETCURRENTRXPDU_EXIT();
}
/*----------------------{end EB_SetCurrentRxPdu}----------------------------*/

/*----------------------{EB_TxConf}-----------------------------------------*/
/* Function to get Current RxPduId */
void EB_TxConf(tTpMsgIdx uMsgIdx)
{
    DBG_EB_TXCONF_ENTRY(uMsgIdx);
    /* if txconf is not for NRC_78 */
    if(uMsgIdx != m_ubTpMsgIdxNrc78)
    {
        /* Check if for physical or functional */
        if(uMsgIdx == PDUR_BL_DIAGREQ_TPSDU)
        {
            if(TPPhyPduCount > 0U)
            {
                /* Decrement the number of physical PDU received */
                TPPhyPduCount--;
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
                if (TPPhyPduCount == 0U)
                {
                    /* Reinit element 0 */
                    TPPhyPduIndex[TPPhyPduCount] = 0U;
                }
                else
                {
                    /* Shift the element 1 to element 0 then reinit element 0 */
                    TPPhyPduIndex[0] = TPPhyPduIndex[TPPhyPduCount];
                    TPPhyPduIndex[TPPhyPduCount] = 0U;
                }
[!ENDIF!]
            }

        }
        else
        {
[!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
            /* Reinit functional variable (only  allowed at a time) */
            TPFuncPduIndex = 0U;
[!ENDIF!]
            TPFuncPduCount = 0U;
        }
    }
    DBG_EB_TXCONF_EXIT();
}
/*----------------------{end EB_TxConf}-------------------------------------*/
/*==================[end of file]===========================================*/
