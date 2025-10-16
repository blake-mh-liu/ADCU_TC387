/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                BLPDUR configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLPDUR_Types.h                     */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
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
[!CODE!]
#ifndef BLPDUR_TYPES_H
#define BLPDUR_TYPES_H


#define BLPDUR_MKR_0          0xE1U
#define BLPDUR_MKR_1          0xB2U

typedef u8 tRxPduType;
#define BLPDUR_STANDARD_CAN_ID 0U
#define BLPDUR_EXTENDED_CAN_ID 1U
#define BLPDUR_NOT_CAN_ID      2U

typedef u8 tBlPduRStatus;
#define BLPDUR_E_NOT_OK       0U
#define BLPDUR_E_OK           1U
#define BLPDUR_E_IDLE         2U
#define BLPDUR_E_BUSY         3U

typedef u8 tAddressingType;
#define BLPDUR_PHYSICAL       UDS_ADDR_PHYSICAL
#define BLPDUR_FUNCTIONAL     UDS_ADDR_FUNCTIONAL

typedef TPParameterType tTpParameterId;
/*Should be in accordance with PduR type TPParameterType*/
/* Separation Time */
#define BLPDUR_TP_STMIN     TP_STMIN
/* Block Size */
#define BLPDUR_TP_BS        TP_BS
/* The Band width control parameter used in FlexRay transport protocol module. */
#define BLPDUR_TP_BC        TP_BC


/** \brief State of a buffer in the TP_UDS module **/
typedef enum
{
  /** \brief Buffer is not in use right now */
    BLPDUR_BUFF_IDLE,
  /** \brief Buffer is used for reception */
    BLPDUR_BUF_RX_IN_PROGRESS,
    /** \brief Buffer is qued for processing */
    BLPDUR_BUFF_RXQUEUED,
    /** \brief Buffer is qued for processing */
    BLPDUR_BUFF_TXQUEUED,
    /** \brief Buffer is used for processing the request */
    BLPDUR_BUFF_RXPROCESSING,

    BLPDUR_BUFF_TXPROCESSING,

    BLPDUR_BUFF_LOCKED
} tBufferStateType;

typedef struct
{
  /** \brief Length of valid data in bytes stored in this buffer
   *
   * The length information is used for reception and transmission.*/
  PduLengthType       filledLen; /* RQD_BLPDUR_TYPES_049 */

  /** \brief Holds index of valid data in bytes to be transmitted in this buffer */
  PduLengthType       dataMark; /* RQD_BLPDUR_TYPES_050 */

  /** \brief State of this buffer */
  tBufferStateType state; /* RQD_BLPDUR_TYPES_051 */

  /** \brief RxPduId which was used to fill the buffer
   *
   * Only valid if the buffer state is BUF_RX  */
  PduIdType           originatingRxPduId; /* RQD_BLPDUR_TYPES_052 */

  uint32              counter; /* RQD_BLPDUR_TYPES_053 */

  /* buffer is locked*/
  u8                  locked;  /* RQD_BLPDUR_TYPES_054 */

} tBufferInfoType;

typedef struct
{
  /** \brief location of buffer **/
  uint8 *ptrBuffer; /* RQD_BLPDUR_TYPES_055 */
  /** \brief status information for this buffer  **/
  tBufferInfoType *bufferInfo; /* RQD_BLPDUR_TYPES_056 */
  /** \brief Size of this buffer **/
  PduLengthType size; /* RQD_BLPDUR_TYPES_057 */
} tBufferConfigType;


typedef struct
{
    /** \brief Connection number of the Rx PDU **/
    u8 ConnectionNum;
    /** \brief Addressing type of the PDU : Physical, Functional **/
    tAddressingType AddressingType;
[!IF "as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup != 'OFF' and node:exists(as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup)"!]
    /** \brief Group Index of the Rx PDU **/
    u8 GroupId;
[!ENDIF!]
    /** \brief Rx PDU Id**/
    u8 RxPduId;
    /** \brief Rx PDU Type **/
    tRxPduType RxPduType;
} tRxPdu;

typedef struct
{
    /** \brief Tx Pdu value for the connection **/
    u16 TxPdu;
    /** \brief Tester address linked to the Tx connection **/
    u16 TestAddress;

    tBufferConfigType* TxBufCfgPtr;
} tPduConnection;

[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!]
typedef struct
{
    /** \brief Pointer to the tab that list the Can ID of the group ID **/
    Can_IdType* GroupCanIdPtr;
    /** \brief Number of can ID in the ID group **/
    u8 NumOfIdInGroup;
[!IF "MultipleIdentifier/MultipleIdentifierGroup = 'CAN_NOTIFICATION'"!]
    /** \brief Number of can ID in the ID group **/
    u8 ArchitectureId;
[!ENDIF!]
}tMultipleIdConfig;
[!ENDIF!]
[!ENDIF!]

/** \brief State of a simulate Rx request treatment **/
typedef enum
{
    /** \brief Simulate Rx Request treatment is not yet started */
    BLPDUR_SIM_RX_REQ_UNINITIALIZED,
    /** \brief Simulate Rx Request treatment has started */
    BLPDUR_SIM_RX_REQ_IN_PROGRESS,
    /** \brief Simulate Rx Request treatment is now finished */
    BLPDUR_SIM_RX_REQ_DONE
}tSimRxReqStateType;


/* Patch for compile version */
typedef u8 tTpMsgIdx;
#define TP_MSG_STATUS_OK        BLPDUR_E_OK
#define EB_Send_TPFrame         BlPduR_Send_TPFrame
#define EB_Init                 BlPduR_Init
#define EB_SetTesterAddress     BlPduR_SetTesterAddress
#define EB_Com_Deactivate       BlPduR_Custom_Com_Deactivate
#define EB_SimulateRxRequest    BlPduR_SimulateRxRequest

/*definitions needed to support FR Network*/
#define EB_IsNetworkSynchronized    BlPduR_IsNetworkSynchronized
#define EB_AllSlots 		    BlPduR_AllSlots
#define EB_Init2 		    BlPduR_Init2
#ifndef EB_TRUE
#define EB_TRUE 		    BLPDUR_TRUE
#endif
#endif      /* BLPDUR_TYPES_H */
[!ENDCODE!]

