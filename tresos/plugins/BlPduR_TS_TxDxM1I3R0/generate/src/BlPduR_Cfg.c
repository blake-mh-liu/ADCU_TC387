/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                           BlPduR configuration                                */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Cfg.c                       */
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
[!NOCODE!]
[!MACRO "GetIDFromSDU", "SduInfo"!]
    [!VAR "PduRDestInfo" = "0"!][!/*
    Parse all the DestPdu configured
    */!][!LOOP "as:modconf('PduR')/*/PduRRoutingTables/*/PduRRoutingTable/PduRRoutingPath/*/PduRDestPdu/*"!][!/*
        Check if the SDU is the same as the one in BlPduR
        */!] [!IF "$SduInfo = PduRDestPduRef"!][!/*
            if found store the Pdu linked to this Sdu
            */!][!VAR "PduRDestInfo" = "../../PduRSrcPdu/PduRSrcPduRef"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$PduRDestInfo = 0"!]
        [!ERROR "The SduReference in Rx Reference of BlPduR is not referenced in PduR"!]
    [!ELSE!]
        [!VAR "PduInfo" = "0"!][!/*
        Parse all the CanTpRxNSdu configured
        */!][!LOOP "as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*"!][!/*
            Check if the SDU is the same as the one in BlPduR
            */!][!IF "$PduRDestInfo = CanTpRxNSduRef"!][!/*
                if found store the Pdu linked to this Sdu
                */!][!VAR "PduInfo" = "CanTpRxNPdu/CanTpRxNPduRef"!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$PduInfo = 0"!]
            [!ERROR "The SduReference in Rx Reference of BlPduR is not referenced in CanTp"!]
        [!ELSE!][!/*
            Parse all the CanIfRxPduCfg configured
            */!][!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!][!/*
                Check if the PDU is the same as the one retrieve from CanTp
                */!][!IF "$PduInfo = CanIfRxPduRef"!][!/*
                    if found retrieve the CanId linked to it
                    */!][!WS "4"!][!"num:inttohex(CanIfRxPduCanId)"!]U,
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDMACRO!]

[!MACRO "GetIDFromPDU", "PduInfo"!][!/*
    Parse all the CanIfRxPduCfg configured
    */!][!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!][!/*
        Check if the PDU is the same as the one retrieve from CanTp
        */!][!IF "$PduInfo = CanIfRxPduRef"!][!/*
            if found retrieve the CanId linked to it
            */!][!WS "4"!][!"num:inttohex(CanIfRxPduCanId)"!]U
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDMACRO!]

[!ENDNOCODE!]
[!CODE!]
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"

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
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*********************************************************************************/

/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */

/*                                                                               */
/*********************************************************************************/

tRxPdu stRxPdu[BLPDUR_MAX_RX_PDU_NUM+BLPDUR_SHARED_RX_PDU_NUM] =
{
[!VAR "RxIdx" = "0"!]
[!FOR "IDX" = "1" TO "count(PduConnection/*/RxPdu/*)" STEP "1"!]
    [!VAR "ConnectionCount" = "0"!]
    [!LOOP "PduConnection/*"!]
    [!VAR "ConnectionName" = "node:name(.)"!]
        [!LOOP "RxPdu/*"!]
            [!IF "Id = num:i($RxIdx)"!]
                [!VAR "RxIdx" = "$RxIdx + 1"!]
    {
        [!"num:dectoint($ConnectionCount)"!]U,[!WS "18"!]/* ConnectionNum  */
        BLPDUR_[!"Type"!],[!WS "4"!]/* AddressingType */
[!IF "as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup != 'OFF' and node:exists(as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup)"!]
        [!FOR "GROUP_IDX" = "1" TO "count(as:modconf('BlPduR')/IDGroup/*)" STEP "1"!]
            [!FOR "CONNECT_IDX" = "1" TO "count(as:modconf('BlPduR')/IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*)" STEP "1"!]
                [!IF "$ConnectionName = name(node:ref(as:modconf('BlPduR')/IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[num:i($CONNECT_IDX)]/ConnectionRef))"!]
        [!"num:i(($GROUP_IDX)-1)"!]U,[!WS "17"!]/* Active Group */
                [!ENDIF!]
            [!ENDFOR!]
        [!ENDFOR!]
[!ENDIF!]
        [!"Id"!]U,[!WS "17"!]/* RxPduId */
[!NOCODE!][!/* if network is CAN */!][!ENDNOCODE!]
[!IF "(as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true') and (../../LinConnection = 'false')"!]
        [!NOCODE!][!/* find RX SDU ref and match */!][!ENDNOCODE!]
        [!VAR "ECUC_RX_SDU_REF" = "name(node:ref(Ref))"!]
        [!VAR "IsSduMatched" = "0"!]
        [!LOOP "as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*"!]
            [!IF "$ECUC_RX_SDU_REF = name(node:ref(CanTpRxNSduRef))"!]
                [!NOCODE!][!/* find RX SDU ref in CanTp */!][!ENDNOCODE!]
                [!VAR "IsSduMatched" = "1"!]
                [!NOCODE!][!/* find RX PDU ref and match */!][!ENDNOCODE!]
                [!VAR "ECUC_RX_PDU_REF" = "name(node:ref(CanTpRxNPdu/CanTpRxNPduRef))"!]
                [!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!]
                    [!IF "$ECUC_RX_PDU_REF = name(node:ref(CanIfRxPduRef))"!]
                        [!NOCODE!][!/* check CAN ID type */!][!ENDNOCODE!]
                        [!WS "8"!][!IF "text:match(CanIfRxPduCanIdType,'EXTENDED*')"!]BLPDUR_EXTENDED_CAN_ID[!ELSE!]BLPDUR_STANDARD_CAN_ID[!ENDIF!][!WS "1"!]/* RxPduType */
                    [!ENDIF!]
                [!ENDLOOP!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!NOCODE!][!/* this RX SDU is not CAN */!][!ENDNOCODE!]
        [!IF "$IsSduMatched = 0"!]
            [!WS "8"!]BLPDUR_NOT_CAN_ID[!WS "1"!]/* RxPduType */
        [!ENDIF!]
[!NOCODE!][!/* if network is not CAN */!][!ENDNOCODE!]
[!ELSE!][!WS "8"!]BLPDUR_NOT_CAN_ID[!WS "1"!]/* RxPduType */
[!ENDIF!]
    },
            [!ENDIF!]
        [!ENDLOOP!]
        [!VAR "ConnectionCount" = "$ConnectionCount + 1"!]
    [!ENDLOOP!]
[!ENDFOR!]
[!VAR "ConnectionCount" = "0"!]
[!LOOP "PduConnection/*"!]
    [!VAR "ConnectionName" = "node:name(.)"!]
    [!IF "ShareFunctionalId = 'true'"!]
    {
        [!"num:dectoint($ConnectionCount)"!]U,[!WS "18"!]/* ConnectionNum  */
        BLPDUR_FUNCTIONAL,[!WS "4"!]/* AddressingType */
        [!IF "as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup != 'OFF' and node:exists(as:modconf('BlPduR')/MultipleIdentifier/MultipleIdentifierGroup)"!]
            [!FOR "GROUP_IDX" = "1" TO "count(as:modconf('BlPduR')/IDGroup/*)" STEP "1"!]
                [!FOR "CONNECT_IDX" = "1" TO "count(as:modconf('BlPduR')/IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*)" STEP "1"!]
                    [!IF "$ConnectionName = name(node:ref(as:modconf('BlPduR')/IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[num:i($CONNECT_IDX)]/ConnectionRef))"!]
        [!"num:i(($GROUP_IDX)-1)"!]U,[!WS "17"!]/* Active Group */
                    [!ENDIF!]
                [!ENDFOR!]
            [!ENDFOR!]
        [!ENDIF!]
        [!"(node:ref(SharedPduReference))/Id"!]U,[!WS "17"!]/* RxPduId */
[!NOCODE!][!/* if network is CAN */!][!ENDNOCODE!]
[!IF "(as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true') and (../../LinConnection = 'false')"!]
        [!NOCODE!][!/* find RX SDU ref and match */!][!ENDNOCODE!]
        [!VAR "ECUC_RX_SDU_REF" = "name(node:ref((node:ref(SharedPduReference))/Ref))"!]
        [!VAR "IsSduMatched" = "0"!]
        [!LOOP "as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpRxNSdu/*"!]
            [!IF "$ECUC_RX_SDU_REF = name(node:ref(CanTpRxNSduRef))"!]
                [!NOCODE!][!/* find RX SDU ref in CanTp */!][!ENDNOCODE!]
                [!VAR "IsSduMatched" = "1"!]
                [!NOCODE!][!/* find RX PDU ref and match */!][!ENDNOCODE!]
                [!VAR "ECUC_RX_PDU_REF" = "name(node:ref(CanTpRxNPdu/CanTpRxNPduRef))"!]
                [!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!]
                    [!IF "$ECUC_RX_PDU_REF = name(node:ref(CanIfRxPduRef))"!]
                        [!NOCODE!][!/* check CAN ID type */!][!ENDNOCODE!]
                        [!WS "8"!][!IF "text:match(CanIfRxPduCanIdType,'EXTENDED*')"!]BLPDUR_EXTENDED_CAN_ID[!ELSE!]BLPDUR_STANDARD_CAN_ID[!ENDIF!][!WS "1"!]/* RxPduType */
                    [!ENDIF!]
                [!ENDLOOP!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!NOCODE!][!/* this RX SDU is not CAN */!][!ENDNOCODE!]
        [!IF "$IsSduMatched = 0"!]
            [!WS "8"!]BLPDUR_NOT_CAN_ID[!WS "1"!]/* RxPduType */
        [!ENDIF!]
[!NOCODE!][!/* if network is not CAN */!][!ENDNOCODE!]
[!ELSE!][!WS "8"!]BLPDUR_NOT_CAN_ID[!WS "1"!]/* RxPduType */
[!ENDIF!]
    },
    [!VAR "RxIdx" = "$RxIdx + 1"!]
    [!ENDIF!]
    [!VAR "ConnectionCount" = "$ConnectionCount + 1"!]
[!ENDLOOP!]
};

/* RQD_BLPDUR_CFG_082 */
tPduConnection stPduConnection[BLPDUR_MAX_PDU_CONNECTION] =
{
[!VAR "ConnectionCount" = "0"!]
[!LOOP "PduConnection/*"!]
    {
    [!IF "LinConnection = 'false'"!]
        BLPDUR_[!"name(node:ref(TxPduRef))"!],   /* TxPdu  */
        [!"TesterAddress"!]U,                     /* TestAddress */
        NULL_PTR                                  /* tx buffer in use */
    [!ELSE!]
        BLPDUR_LIN_TX_PDU,                       /* Lin Tx Pdu, will have a specific use */
        0U,                                      /* Lin has no specific tester address */
        NULL_PTR                                 /* tx buffer in use */
    [!ENDIF!]
    },
    [!VAR "ConnectionCount" = "$ConnectionCount + 1"!]
[!ENDLOOP!]
};
/* RQD_BLPDUR_INIT_013 */
uint8 BlPduRRxPhysBuffer[BLPDUR_RX_PHY_BUFFER_NUM][BLPDUR_RX_PHYS_BUFFERSIZE];
tBufferInfoType stRxPhysBufferInfo[BLPDUR_RX_PHY_BUFFER_NUM] =
{
    [!FOR "BUFFERIDX" = "1" TO "General/RxBufferNum" STEP "1"!]
    {
        0U,                 /* filledLen          */
        0U,                 /* dataMark           */
        BLPDUR_BUFF_IDLE,   /* state              */
        0U,                 /* originatingRxPduId */
        0U,                 /* counter */
        FALSE               /* locked */
    },
    [!ENDFOR!]
};

tBufferConfigType stRxPhysBufferConfig[BLPDUR_RX_PHY_BUFFER_NUM] =
{
    [!FOR "BUFFERIDX" = "1" TO "General/RxBufferNum" STEP "1"!]
    {
        &BlPduRRxPhysBuffer[[!"num:i($BUFFERIDX - 1)"!]][0U],[!WS "2"!]/* ptrBuffer   */
        &stRxPhysBufferInfo[[!"num:i($BUFFERIDX - 1)"!]],[!WS "6"!]/* bufferInfo  */
        BLPDUR_RX_PHYS_BUFFERSIZE,[!WS "3"!]/* Buffer size */
    },
    [!ENDFOR!]
};

uint8 BlPduRRxSmallBuffer[BLPDUR_MAX_RX_PDU_NUM][BLPDUR_RX_SMALL_BUFFERSIZE];
tBufferInfoType stRxSmallBufferInfo[BLPDUR_MAX_RX_PDU_NUM] =
{ /* RQD_BLPDUR_INIT_019 */
    [!FOR "BUFFERIDX" = "1" TO "count(PduConnection/*/RxPdu/*)" STEP "1"!]
    {
        0U,                 /* filledLen          */
        0U,                 /* dataMark           */
        BLPDUR_BUFF_IDLE,   /* state              */
        0U,                 /* originatingRxPduId */
        0U,                 /* counter*/
        FALSE               /* locked */
    },
    [!ENDFOR!]
};

tBufferConfigType stRxSmallBufferConfig[BLPDUR_MAX_RX_PDU_NUM] =
{
    [!FOR "BUFFERIDX" = "1" TO "num:i(count(PduConnection/*/RxPdu/*)) + 1" STEP "1"!]
    {
        &BlPduRRxSmallBuffer[[!"num:i($BUFFERIDX - 1)"!]][0U],[!WS "2"!]/* ptrBuffer   */
        &stRxSmallBufferInfo[[!"num:i($BUFFERIDX - 1)"!]],[!WS "6"!]/* bufferInfo  */
        BLPDUR_RX_SMALL_BUFFERSIZE,[!WS "3"!]/* Buffer size */
    },
    [!ENDFOR!]
};



[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!][!/*
Get all the ID for all the ID group configured
*/!][!FOR "GROUP_IDX" = "1" TO "count(IDGroup/*)" STEP "1"!]
/* Tab for all CanId configured in a connection */
Can_IdType auCanId_[!"num:i($GROUP_IDX - 1)"!][BLPDUR_CONNECTION_NUM_ID_GR_[!"num:i($GROUP_IDX - 1)"!]] =
{
[!/*In each group parse all the connection configured
    */!][!FOR "CONNECT_IDX" = "1" TO "count(IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*)" STEP "1"!]
        [!SELECT "node:ref(IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[num:i($CONNECT_IDX)]/ConnectionRef)"!][!/*
            In each connection parse all the RxPdu configured
            */!][!LOOP "RxPdu/*"!][!/*
                Get the Can ID of all Pdu configured from the referenced SDU
                */!][!CALL "GetIDFromSDU", "SduInfo"="Ref"!]
            [!ENDLOOP!]
            [!IF "ShareFunctionalId = 'true'"!]
                [!CALL "GetIDFromSDU", "SduInfo"="(node:ref(SharedPduReference))/Ref"!]
            [!ENDIF!]
        [!ENDSELECT!]
        [!IF "( (as:modconf('BlPduR')/SleepManagement/Grouping_NM_Message = 'true') and ((IDGroup/*[num:i($GROUP_IDX)]/ConnectionReflist/*[num:i($CONNECT_IDX)]/ConnectionRef) = (as:modconf('BlPduR')/SleepManagement/PduConnectionGroupRef)) )"!]
            [!CALL "GetIDFromPDU", "PduInfo"="as:modconf('BlPduR')/SleepManagement/IDGroupPDURef"!]
        [!ENDIF!]
    [!ENDFOR!]
};
[!ENDFOR!]
[!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('CanIf'))"!]
[!IF "MultipleIdentifier/MultipleIdentifierGroup != 'OFF'"!]
/* Tab that defines all the ID group */
const tMultipleIdConfig stMultipleIdConfig[BLPDUR_ID_GROUP_NUM] =
{
    [!FOR "GROUP_IDX" = "1" TO "count(IDGroup/*)" STEP "1"!]
    {
        &auCanId_[!"num:i($GROUP_IDX - 1)"!][0],                   /* Pointer to the tab that list the Can ID of the group ID */
        BLPDUR_CONNECTION_NUM_ID_GR_[!"num:i($GROUP_IDX - 1)"!],   /* Number of can ID in the ID group */
[!IF "MultipleIdentifier/MultipleIdentifierGroup = 'CAN_NOTIFICATION'"!]
        [!"num:inttohex(IDGroup/*[num:i($GROUP_IDX)]/ArchitectureId)"!]U, /* Architecture ID that is link to this group ID */
[!ENDIF!]
    },
    [!ENDFOR!]
};
[!ENDIF!]
[!ENDIF!]
[!ENDCODE!]

