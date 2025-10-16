/* *--------{ EB Automotive C Source File }-------- */
#ifndef  J1939DCM_INTERNAL_TYPES_H
#define  J1939DCM_INTERNAL_TYPES_H

/*==================[includes]===============================================*/
/* Types from configuration */
#include <J1939Dcm_Types.h>
/*#include "J1939Dcm_MemMap.h"*/
/*==================[type definitions]=======================================*/
/* definition of pointer to Service function  */
typedef J1939Dcm_DmResponseType (* J1939Dcm_DMFunctionPointerType)( VAR(J1939Dcm_OpStatusType, AUTOMATIC) OpStatus,
                                    P2VAR(J1939Dcm_MsgContextType, AUTOMATIC, J1939DCM_VAR) pMsgContext,
                                    VAR(uint8, AUTOMATIC) NodeId );

typedef  struct
{
    /* Pointer to DM processing function */
    CONST(J1939Dcm_DMFunctionPointerType, J1939DCM_CONST) DMFunctionPtr;
    /* PGN of the configured DM */
    CONST(uint16, J1939DCM_CONST) PGN;
    /* TX Information  */
    /* bit 7 shows if transmission is on IF(InterFace) or TP(TransportProtocol) */
    /* bits 0..6 gives the TxPduId index in table J1939Dcm_TxPduIds */
    CONST(uint8, J1939DCM_CONST) TxInfo;
    /* ComM Channel information, index in J1939Dcm_ComMChannels */
    CONST(uint8, J1939DCM_CONST) ComMChannelIdx;
    /* special information depending on DM */
    CONST(uint8, J1939DCM_CONST) SpecialInfo;
}J1939Dcm_DMMessageType;

typedef  struct
{
    /* PGN of the configured DM */
    CONST(uint16, J1939DCM_CONST) PGN;
    /* Gives the RxPduId index in table J1939Dcm_RxPduIds*/
    CONST(uint8, J1939DCM_CONST) RxPduIdIdx;
    /* ComM Channel information, index in J1939Dcm_ComMChannels */
    CONST(uint8, J1939DCM_CONST) ComMChannelIdx;
}J1939Dcm_Rx_DMMessageType;

typedef  struct
{
    /* Pointer to DM processing function */
    CONST(uint16, J1939DCM_CONST) PduSymbolicName;
    /* J1939Dcm Tx Pdu Id */
    CONST(uint16, J1939DCM_CONST) J1939DcmTxPduId;
    /* PGN of the configured DM */
    CONST(uint8, J1939DCM_CONST) MetaDataLength;
}J1939Dcm_TxPduType;

typedef  struct
{
    /* Pointer to DM processing function */
    CONST(uint16, J1939DCM_CONST) PduSymbolicName;
    /* J1939Dcm Rx Pdu Id */
    CONST(uint16, J1939DCM_CONST) J1939DcmRxPduId;
    /* PGN of the configured DM */
    CONST(uint8, J1939DCM_CONST) MetaDataLength;
}J1939Dcm_RxPduType;

typedef  struct
{
    /* node symbolic name */
    CONST(uint8, J1939DCM_CONST) NodeSymbolicName;
    /* J1939Nm Node Preferred Address */
    CONST(uint8, J1939DCM_CONST) J1939NmNodePreferredAddress;
#if( J1939DCM_DM01_AVAILABLE == STD_ON )
    /* DM1 index in J1939Dcm_ConfiguredDMs per each node. */
    CONST(uint8, J1939DCM_CONST) DM1Idx;
#endif /* ( J1939DCM_DM01_AVAILABLE == STD_ON ) */
    /* Index of the first configured DM message for the current node */
    /* in the J1939Dcm_ConfiguredDMs table */
    CONST(uint8, J1939DCM_CONST) FirstDMIdx;
    /* Index of the last configured DM message for the current node */
    /* in the J1939Dcm_ConfiguredDMs table */
    CONST(uint8, J1939DCM_CONST) LastDMIdx;
    /* Index of the first configured ComM Channel for the current node */
    /* in the J1939Dcm_ComMChannels table */
    CONST(uint8, J1939DCM_CONST) FirstComMChannelIdx;
    /* Index of the first configured ComM Channel for the current node */
    /* in the J1939Dcm_ComMChannels table */
    CONST(uint8, J1939DCM_CONST) LastComMChannelIdx;
}J1939Dcm_NodesInfoType;


#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
/* Buffer types */
typedef struct
{
    VAR(J1939Dcm_MsgLenType, J1939DCM_VAR)  Sent_Bytes_Tx;
    VAR(J1939Dcm_MsgLenType, J1939DCM_VAR)  Bytes_To_Send_Tx;
}J1939Dcm_TPTxInfoType;
#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */

typedef struct
{
    CONST(uint8, J1939DCM_CONST) u8DTCStatusFilter;
    CONST(uint8, J1939DCM_CONST) u8DTCKind;
}J1939Dcm_SetDTCFilterType;

typedef struct
{
    /* Index of the DM message in the J1939Dcm_ConfiguredDMs table */
    VAR(uint8, J1939DCM_VAR) DMIdx;

    /* Priority of the Requested PG. */
    VAR(uint8, J1939DCM_VAR) priority;

    /* Source address of the Requested PG. */
    VAR(uint8, J1939DCM_VAR) receivedsourceAddress;

    /* NodePreferred address of the Requested PG. */
    VAR(uint8, J1939DCM_VAR) NodePreferredAddress;

    /* Destination address of the Requested PG */
    VAR(uint8, J1939DCM_VAR) destAddress;

    /* The node address for each requested DM. */
    VAR(uint8, J1939DCM_VAR) NodeId;

    /* J1939Rm User Id. */
    VAR(uint8, J1939DCM_VAR) J1939RmUserId;
}J1939Dcm_MetaDataInfoType;

typedef struct
{
    /* Used to monitor 6 seconds hold timeouts*/
    VAR(uint16, J1939DCM_VAR)   J1939Dcm_HoldTimerTicks;
    /* Indicates the State of the Hold Timer */
    VAR(uint8, J1939DCM_VAR)    J1939DcmTimerState;
    /* Indicates the DM-13 broadcast mode - Setup/Hold */
    VAR(uint8, J1939DCM_VAR)    J1939DcmBroadcastMode;
    /* This flag is set when Broadcast Transmission is enabled from Application*/
    VAR(boolean, J1939DCM_VAR)  J1939DcmBroadcastStatus;

}J1939Dcm_DM13_StatusInfoType;

#endif /* J1939DCM_INTERNAL_TYPES_H */
