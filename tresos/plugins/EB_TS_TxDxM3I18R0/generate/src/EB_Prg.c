/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                EB configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Prg.c                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3                */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined.
 *
 * Reason:
 * Static keyword is automatically removed and these variables are not used in test environment.
 */

[!AUTOSPACING!]
[!NOCODE!][!VAR "CNT_IDX" = "0"!]
[!MACRO "GetCanCtrlIdx", "CtrlName"!]
    [!VAR "CRTL_IDX" = "0"!]
    [!LOOP "as:modconf('Can')/Controller_Configuration/*"!]
        [!VAR "CNT_IDX" = "$CNT_IDX + 1"!]
        [!/* Index of the Controller */!]
        [!IF "$CtrlName = name(.)"!]
            [!VAR "CUR_CTRL_IDX" = "$CRTL_IDX"!]
        [!ENDIF!]
        [!VAR "CRTL_IDX" = "$CRTL_IDX + 1"!]
    [!ENDLOOP!]
[!ENDMACRO!]
[!MACRO "GetCanCtrlIdxAutosar", "CtrlNameAutosar"!]
    [!VAR "CRTL_IDX" = "0"!]
    [!LOOP "as:modconf('Can')/CanConfigSet/*[1]/CanController/*"!]
        [!VAR "CNT_IDX" = "$CNT_IDX + 1"!]
        [!/* Index of the Controller */!]
        [!IF "$CtrlNameAutosar = name(.)"!]
            [!VAR "CUR_CTRL_IDX" = "$CRTL_IDX"!]
        [!ENDIF!]
        [!VAR "CRTL_IDX" = "$CRTL_IDX + 1"!]
    [!ENDLOOP!]
[!ENDMACRO!]
[!VAR "IndexFound" = "0"!]

[!/* DO NOT ERASE "TMP_INDEX_CFG" LINE !!! */!]
[!/* USE FOR MANAGING MULTI CONF LOOP */!]
[!VAR "TMP_INDEX_CFG" = "0"!]

[!/* Variable used for space incrementation in generated code */!]
[!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!][!VAR "WSBase" = "8"!][!ELSE!][!VAR "WSBase" = "0"!][!ENDIF!]
[!VAR "FunctionalMsgExist" = "0"!]
[!VAR "FullDuplexUses" = "0"!]
[!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
    [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd')  and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
        [!VAR "FunctionalMsgExist" = "1"!]
    [!ENDIF!]
    [!IF "as:modconf('Tp')/Message/*[position()=$MsgNB]/Mode = 'Full_Duplex'"!]
        [!VAR "FullDuplexUses" = "1"!]
    [!ENDIF!]
[!ENDFOR!]
[!ENDNOCODE!]

[!CODE!]
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Prj.h"
[!IF "(as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR')"!]
#include <PduR.h>
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
/* - Header Files: all CAN layers                                                */
#include <CanSM_ComM.h>
    [!ENDIF!]
#ifdef NCS_UNITARY_TEST
#include <Platforms_Modules.h>
#else
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
#endif
[!ENDIF!]
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
[!IF "(as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR')"!]
#define PROG_CTRLIDX 0
[!ENDIF!]


[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
[!IF "node:exists(as:modconf('Com'))"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*  Generation of an array aubCOMRxFrame that is providing the mapping between frame index
*   in Com module and SourceAddress (last 8 bits of identifier) */
NCS_PRI_VAR const u16 aubCOMRxFrame[COM_RX_FRAME_MAX] =
    {
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
[!WS "8"!]0x[!"substring(num:inttohex(node:value('Identifier')), string-length(node:value('Identifier')))"!]U,
            [!ENDLOOP!]
    };
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
    [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
/*  Generation of an array that is providing the mapping between Tp message index
*   and TesterAddress */
/* Deviation MISRAC2012-1 */
NCS_PRI_VAR const tTpTesterAddrRef aubTpTesterAddrRef[EB_TP_PHYS_MESS_NBR] =
[!WS "4"!]{
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!IF "node:value('Adressing_Mode') = 'Physical'"!]
                [!WS "8"!]{
                [!WS "12"!]TP_MSG_IDX_[!"name(.)"!],
                [!SELECT "node:ref(ComTxFrameRef)"!]
                    [!IF "string-length(node:value('Identifier')) > 8"!]
                        [!WS "12"!]0x[!"substring(num:inttohex(node:value('Identifier')), string-length(node:value('Identifier'))-2,2)"!]U
                    [!ELSE!]
                        [!WS "12"!]0x00U
                    [!ENDIF!]
                [!ENDSELECT!]
                [!WS "8"!]},
            [!ENDIF!]
        [!ENDLOOP!]
        [!WS "4"!]};
    [!ENDIF!][!/* End of OSEK */!]
    [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
/*  Generation of an array that is providing the mapping between Tp message index
*   and TesterAddress */
/* Deviation MISRAC2012-1 */
NCS_PRI_VAR const tTpTesterAddrRef aubTpTesterAddrRef[EB_TP_PHYS_MESS_NBR] =
        [!WS "4"!]{
        [!LOOP "as:modconf('EB')/Communication/TxPdus/*"!]
            [!WS "8"!]{
            [!WS "12"!]TP_MSG_IDX_[!"name(.)"!],    /* TxPdus Name */
            [!WS "12"!][!"num:inttohex(node:value('TesterAddress'))"!]U,[!WS "11"!]/* Tester identifier */
            [!VAR "REF_EB_ECUC" = "name(node:ref(TxPduRef))"!]
            [!LOOP "as:modconf('CanTp')/CanTpConfig/*/CanTpChannel/*/CanTpTxNSdu/*"!]
                [!IF "$REF_EB_ECUC = name(node:ref(CanTpTxNSduRef))"!]
                [!VAR "REF_CANTP_ECUC" = "name(node:ref(CanTpRxFcNPdu/CanTpRxFcNPduRef))"!]
                [!LOOP "as:modconf('CanIf')/CanIfInitCfg/*/CanIfRxPduCfg/*"!]
                    [!IF "$REF_CANTP_ECUC = name(node:ref(CanIfRxPduRef))"!]
                    [!WS "12"!][!"num:inttohex(CanIfRxPduCanId)"!]U,     /* Can Identifier */
                        [!IF "text:match(CanIfRxPduCanIdType,'EXTENDED*')"!][!WS "12"!]EXTENDED_ID[!ELSE!][!WS "12"!]STANDARD_ID[!ENDIF!][!WS "6"!]/* Can Identifier Type */
                    [!ENDIF!]
                [!ENDLOOP!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!WS "8"!]},
        [!ENDLOOP!]
        [!WS "4"!]};
    [!ENDIF!][!/* End of AUTOSAR */!]
[!ENDIF!][!/* End of BM_SOURCE_ADDRESS_CHECK */!]
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

[!IF "node:exists(as:modconf('Com')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF " (num:i(as:modconf('Com')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
NCS_PRI_VAR u8 m_ubComManageCnt;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF " (num:i(as:modconf('Tp')/TpGeneral/TpManagePeriod) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
NCS_PRI_VAR u8 m_ubTpManageCnt;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
NCS_PRI_VAR u8 m_ubStreamingSetting;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds')) and (count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1) and as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    [!IF "$FullDuplexUses = 0"!]
/* Private variable to memorize the value of the TP message Idx used for response pending (NRC78) */
NCS_PRI_VAR u8 m_ubTpMsgIdxNrc78;
    [!ELSE!]
/* Variable to memorize the value of the TP message Idx used for response pending (NRC78) */
u8 m_ubTpMsgIdxNrc78;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!IF " (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
NCS_PRI_VAR u8 m_ubDiagManageCnt;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
    [!IF " (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
NCS_PRI_VAR u8 m_ubProgManageCnt;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
    [!IF " (num:i(as:modconf('SA')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
NCS_PRI_VAR u8 m_ubSAManageCnt;
    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
/* Flag to notice TpRx indication */
[!LOOP "as:modconf('Tp')/Message/*"!]
    [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
        [!IF "Mode = 'Half_Duplex'"!]
NCS_PRI_VAR u8 m_uEbTpMsgFlagIdx[!"name(.)"!];
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!ENDIF!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
NCS_PRI_VAR u16 m_ubTesterAddress;
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
NCS_PRI_VAR u8 *m_paubTpBuffer;
[!ENDIF!]
[!ENDIF!]

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */



[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/** \brief Look for message matching a source address
 **
 ** Allow findind the message matching a source address.
 ** \param[in] ubSourceAddress Source addres
 ** \param[out] uMsgIdx Index of the message matching source address
 ** \return Result of the search
 ** \retval TRUE     Message has been found
 ** \retval FALSE    No message found
 **/
NCS_PRI_FCT u8 EB_GetMessageIdBySourceAddress(u16 ubSourceAddress, tTpMsgIdx * uMsgIdx);

[!ENDIF!]


[!/* This API only exists if at least one value of STMIN > EB_Manage_Period */!]
[!IF "node:exists(as:modconf('Tp'))and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!VAR "NbOfSTMinLargerThanEBManage" = "0"!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!/* Does this configuration has TP channel which has STMin <= EB_MANAGE_PERIOD ? */!]
            [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                [!VAR "NbOfSTMinLargerThanEBManage" = "$NbOfSTMinLargerThanEBManage + 1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!IF "$NbOfSTMinLargerThanEBManage != 0"!]
/** \brief Reception of segmented frame
 **
 ** This internal function allows to receive segmented frames.
 **
 **/
NCS_PRI_FCT void EB_TpReqManage(void);
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
/** \brief UDS response management for a segmented message
 **
 ** This internal function allows:
 ** - to get UDS positive or negative from UDS layer
 ** - to sent this response with TP
 **
 **/
NCS_PRI_FCT void EB_TpRxMsgManage(void);
    [!ENDIF!]

    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
/** \brief EB Data buffer for a segmented message
 **
 ** This internal function allows:
 ** - to get Tp receive frame Data Buffer
 **
 ** \param[in] uwLen pointer on data length
 ** \param[in,out] paubUdsData pointer on data
 ** \param[in] uMsgIdx TP message index
 ** \param[in] eStatusMsgData status of the received or send message data function
 ** \param[in] ubAdressingMode TP Addressing Mode
 ** \param[in] ubAddressingType TP Addressing type
 **
 **/
NCS_PRI_FCT void EB_TpRxMsgDataBuffer (u16 uwLen, u8 *paubUdsData, tTpMsgIdx uMsgIdx, tTpStatus eStatusMsgData, u8 ubAdressingMode, u8 ubAddressingType);
    [!ENDIF!]
[!ENDIF!]

/*                                                                               */
/*********************************************************************************/


/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

 /*----------------------------------{EB_Init}--------------------------------*/
 void EB_Init(void)
 {
    DBG_EB_INIT_ENTRY();

    EB_Init1();
    EB_Init2();

    DBG_EB_INIT_EXIT();
 }
/*----------------------------------{end EB_Init}----------------------------*/

/*----------------------------------{EB_Init1}--------------------------------*/
void EB_Init1(void)
{
    DBG_EB_INIT1_ENTRY();
[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!VAR "Cnt" = "0"!]
    [!IF "node:exists(as:modconf('Com'))"!]
        [!IF " (num:i(as:modconf('Com')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    m_ubComManageCnt = 0U;
        [!ENDIF!]
    [!ENDIF!]
    [!IF "node:exists(as:modconf('Tp'))"!]
        [!IF " (num:i(as:modconf('Tp')/TpGeneral/TpManagePeriod) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    m_ubTpManageCnt = 0U;
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!] [!/* as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'*/!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!IF " (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    m_ubDiagManageCnt = 0U;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    /* Flag to notice TpRx indication initialization */
    [!LOOP "as:modconf('Tp')/Message/*"!]
        [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
            [!IF "Mode = 'Half_Duplex'"!]
    m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_FALSE;
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!IF "node:exists(as:modconf('Uds')) and (count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1)and as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    m_ubTpMsgIdxNrc78 = EB_NO_NRC_78;
    [!ENDIF!]
    [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
    m_ubStreamingSetting = EB_STREAMING_ALLOWED;
    [!ENDIF!]
[!ENDIF!]

    /* Init */
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'FLEXRAY'"!]

    /* Start FlexRay Controller */
        [!IF "node:exists(as:modconf('PduR'))"!]
    PduR_Init(BASE_PDUR_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('Fr'))"!]
    Fr_Init(BASE_FR_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrIf'))"!]
    FrIf_Init(BASE_FRIF_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrTp'))"!]
    FrTp_Init(BASE_FRTP_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('FrSM'))"!]
    FrSM_Init(BASE_FRSM_CONFIG_PTR);
    (void)FrSM_RequestComMode(0U, COMM_FULL_COMMUNICATION);
        [!ENDIF!]
    [!ENDIF!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'CAN'"!]

    /* Start Can Controller */
        [!IF "node:exists(as:modconf('PduR'))"!]
    PduR_Init(BASE_PDUR_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('Can'))"!]
    Can_Init(BASE_CAN_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanIf'))"!]
    CanIf_Init(BASE_CANIF_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanTp'))"!]
    CanTp_Init(BASE_CANTP_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('CanSM'))"!]
    CanSM_Init(BASE_CANSM_CONFIG_PTR);
    (void)CanSM_RequestComMode(0U, COMM_FULL_COMMUNICATION);
        [!ENDIF!]
    [!ENDIF!]
    [!IF "as:modconf('EB')/General/Protocol_Type = 'ETHERNET'"!]

    /* Start Ethernet Controller */
        [!IF "node:exists(as:modconf('EthTrcv'))"!]
    EthTrcv_Init(BASE_ETHTRCV_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('Eth'))"!]
    Eth_Init(BASE_ETH_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('EthIf'))"!]
    EthIf_Init(BASE_ETHIF_CONFIG_PTR);
        [!ENDIF!]
        [!IF "not(node:exists(as:modconf('EthSM')))"!]
            [!IF "node:exists(as:modconf('EthIf'))"!]
                [!IF "node:exists(as:modconf('Eth'))"!]
    EthIf_ControllerInit(0U, 0U);
    EthIf_SetControllerMode(0U, ETH_MODE_ACTIVE);
                [!ENDIF!]
                [!IF "node:exists(as:modconf('EthTrcv'))"!]
    EthIf_TransceiverInit(0U, 0U);
    EthIf_SetTransceiverMode(0U, ETHTRCV_MODE_ACTIVE);
                [!ENDIF!]
            [!ENDIF!]
        [!ELSE!]
    EthSM_Init(BASE_ETHSM_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('TcpIp'))"!]
    TcpIp_Init(BASE_TCPIP_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('SoAd'))"!]
    SoAd_Init(BASE_SOAD_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('DoIP'))"!]
    DoIP_Init(BASE_DOIP_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('PduR'))"!]
    PduR_Init(BASE_PDUR_CONFIG_PTR);
        [!ENDIF!]
        [!IF "node:exists(as:modconf('EthSM'))"!]
    (void)EthSM_RequestComMode(0U, COMM_FULL_COMMUNICATION);
        [!ELSEIF "node:exists(as:modconf('TcpIp'))"!]
    (void)TcpIp_RequestComMode(0U, TCPIP_STATE_ONLINE);
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!IF "$FullDuplexUses = 1"!]
    /* Full Duplex variable initialization */
    EB_InitFullDuplex();
    [!ENDIF!]
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF "node:exists(as:modconf('Com'))"!]
    COM_Init ();
        [!IF "as:modconf('Com')/General/IL_included  = 'true'"!]
    IL_Init ();
        [!ENDIF!]
    [!ENDIF!]
    [!IF "node:exists(as:modconf('Can'))"!]
    CAN_Init ();
    CAN_Desactivate();
    CAN_BitTimeCfg();
    /* OSCEB-101: Do not call CAN_Activate */
    /* It will be done only when all MBX are really configured */
    [!ENDIF!]
    [!IF "node:exists(as:modconf('Tp'))"!]
    TP_Init ();
    [!ENDIF!]
[!ENDIF!][!/* as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'*/!]
[!IF "node:exists(as:modconf('Uds'))"!]
    UDS_Init ();
[!ENDIF!]
[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF "node:exists(as:modconf('Can'))"!]
    /* Preprocess symbol to desactivate CAN tranceiver */
#ifndef EB_DISABLE_CAN_TRCV
    /* Map the EN, STB\ and NERR pins of the CAN transceiver on the CPU  */
    /* TJA1040 CAN transceiver in NORMAL mode (EN and STB\ are put to 1) */
        [!IF "num:dectoint(count(as:modconf('Can')/Controller_Configuration/*)) > 1"!]
            [!IF "node:exists(as:modconf('Can')/Controller_Configuration)"!]
                [!CALL "GetCanCtrlIdx", "CtrlName"="name(node:ref(General/Can_Controller_Ref))"!]
    CAN_TransceiverPinCfg(CAN_CTRL_[!"num:i($CUR_CTRL_IDX)"!]);
    CAN_SetTransceiverMode (CAN_CTRL_[!"num:i($CUR_CTRL_IDX)"!], 1U, 1U);
            [!ELSEIF "node:exists(as:modconf('Can')/CanConfigSet)"!]
                [!CALL "GetCanCtrlIdxAutosar", "CtrlNameAutosar"="name(node:ref(General/Can_Controller_Ref_Autosar))"!]
    CAN_TransceiverPinCfg(CAN_CTRL_[!"num:i($CUR_CTRL_IDX)"!]);
    CAN_SetTransceiverMode (CAN_CTRL_[!"num:i($CUR_CTRL_IDX)"!], 1U, 1U);
            [!ELSE!]
    CAN_TransceiverPinCfg(CAN_CTRL_[!"General/Can_Controller"!]);
    CAN_SetTransceiverMode (CAN_CTRL_[!"General/Can_Controller"!], 1U, 1U);
            [!ENDIF!]
        [!ELSE!]
    CAN_TransceiverPinCfg();
    CAN_SetTransceiverMode (1U, 1U);
        [!ENDIF!]
#endif
    [!ENDIF!][!/*node:exists(as:modconf('Can'))*/!]
    [!IF "node:exists(as:modconf('Com'))"!]
    (void)COM_ModeModify (COM_MODE_BUS_ON);
    [!ENDIF!][!/*node:exists(as:modconf('Com'))*/!]
[!ENDIF!] [!/* as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'*/!]
    DBG_EB_INIT1_EXIT();
}
/*----------------------------------{end EB_Init1}----------------------------*/

/*----------------------------------{EB_Init2}--------------------------------*/
void EB_Init2(void)
{
    DBG_EB_INIT2_ENTRY();
    /* Initialization of manage counters */
[!IF "node:exists(as:modconf('Prog'))"!]
    [!IF " (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    m_ubProgManageCnt = 0U;
    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
    [!IF " (num:i(as:modconf('SA')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    m_ubSAManageCnt = 0U;
    [!ENDIF!]
[!ENDIF!]

    /* Init */
[!IF "node:exists(as:modconf('Flash'))"!]
    FLASH_Init ();
[!ENDIF!]
[!IF "node:exists(as:modconf('Prog'))"!]
    PROG_Init ();
[!ENDIF!]
[!IF "node:exists(as:modconf('SA'))"!]
    SA_Init ();
[!ENDIF!]
    DBG_EB_INIT2_EXIT();
}
/*----------------------------------{end EB_Init2}----------------------------*/


[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*----------------------{EB_GetMessageIdBySourceAddress}----------------------*/
NCS_PRI_FCT u8 EB_GetMessageIdBySourceAddress(u16 ubSourceAddress, tTpMsgIdx * uMsgIdx)
{
    u8          ubLoopIndex;
    u8          ubIdFound = FALSE;

    if ( ubSourceAddress == EB_ALL_TESTER_ADDRESS)
    {
        *uMsgIdx = aubTpTesterAddrRef[0].TpIdx;
        ubIdFound = TRUE;
    }
    else
    {
        /* look for TP Index matching the Tester Address, if not found index 0 is used */
        for (ubLoopIndex = 0; ((ubIdFound == FALSE) && (ubLoopIndex < EB_TP_PHYS_MESS_NBR)); ubLoopIndex++)
        {
            if (aubTpTesterAddrRef[ubLoopIndex].TesterAddress == ubSourceAddress)
            {
                *uMsgIdx = aubTpTesterAddrRef[ubLoopIndex].TpIdx;
                ubIdFound = TRUE;
            }

        }
    }
    return ubIdFound;
}
/*------------------end EB_GetMessageIdBySourceAddress}----------------------*/
[!ENDIF!]



[!/* This API only exists if at least one value of STMIN > EB_Manage_Period */!]
[!IF "node:exists(as:modconf('Tp')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!VAR "NbOfSTMinLargerThanEBManage" = "0"!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!/* Does this configuration has TP channel which has STMin <= EB_MANAGE_PERIOD ? */!]
            [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                [!VAR "NbOfSTMinLargerThanEBManage" = "$NbOfSTMinLargerThanEBManage + 1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!IF "$NbOfSTMinLargerThanEBManage != 0"!]
/*----------------------------------{EB_TpReqManage}--------------------------------*/
NCS_PRI_FCT void EB_TpReqManage (void)
{
    [!VAR "TMP_CNT" = "0"!]
    [!LOOP "as:modconf('Tp')/Message/*"!]
        [!VAR "TMP_CNT" = "1"!]
    [!ENDLOOP!]
    [!IF "$TMP_CNT = 1"!]
    /* Function status */
    tComStatus eStatus;
    /* Tp frame reception flag */
    u8 ebRxFlag;
    [!ENDIF!]

    [!LOOP "as:modconf('Com')/ComConfig/*"!]
        [!VAR "TMP_NAME_CFG" = "@name"!]
        [!VAR "TMP_INDEX_CFG" = "@index"!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!IF "$TMP_INDEX_CFG = 0"!]
    switch(ubConfigurationSelection)
    {
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ELSE!]
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ENDIF!]
        [!ENDIF!]
        [!LOOP "Frames/*"!]
            [!VAR "FRAMES_IDX" = "name(.)"!]
            [!VAR "IDX_FOUND" = "0"!]
            [!LOOP "as:modconf('Tp')/Message/*"!]
                [!VAR "TP_CHANNEL_NAME" = "@name"!]
                [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
                    [!IF "Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd'"!]
                        [!IF "$FRAMES_IDX = name(node:ref(ComRxFrameRef))"!]
                            [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                                [!VAR "IDX_FOUND" = "1"!]
                            [!ELSE!]
                                [!WARNING!]With the current configuration of [!"$TP_CHANNEL_NAME"!] channel, STMin value <= EB_MANAGE_PERIOD. Therefore, EB layer scheduling is not fast enough to ensure the correct treatment of the received segments (some segments could be lost). In order to ensure the segmentation process, the stack will manage it in the interrupt routine[!ENDWARNING!]
                            [!ENDIF!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$IDX_FOUND = 1"!]
            [!WS "$WSBase + 4"!]/* Check if a Diagnostic request frame has been received */
            [!WS "$WSBase + 4"!]eStatus = COM_GetFrameRxFlag (COM_FRAME_IDX_[!"$FRAMES_IDX"!], &ebRxFlag);

            [!WS "$WSBase + 4"!]/* EB CAN layer function has been well executed */
            [!WS "$WSBase + 4"!]if (eStatus == COM_ERR_OK)
            [!WS "$WSBase + 4"!]{
                [!WS "$WSBase + 8"!]/* A Diagnostic request frame has been received */
                [!WS "$WSBase + 8"!]if (ebRxFlag == COM_TRUE)
                [!WS "$WSBase + 8"!]{
                    [!LOOP "as:modconf('Tp')/Message/*"!]
                        [!IF "Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd'"!]
                            [!IF "$FRAMES_IDX = name(node:ref(ComRxFrameRef))"!]
                                [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                    [!WS "$WSBase + 12"!](void)TP_ReceiveFrame (TP_MSG_IDX_[!"name(.)"!]);
                                [!ENDIF!]
                            [!ENDIF!]
                        [!ENDIF!]
                    [!ENDLOOP!]
                [!WS "$WSBase + 8"!]}
                [!WS "$WSBase + 4"!]}
            [!ENDIF!]
        [!ENDLOOP!]
        [!LOOP "Frames/*"!]
            [!VAR "FRAMES_IDX" = "name(.)"!]
            [!VAR "IDX_FOUND" = "0"!]
            [!LOOP "as:modconf('Tp')/Message/*"!]
            [!VAR "TP_CHANNEL_NAME" = "@name"!]
            [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
                [!IF "Type = 'App'"!]
                    [!IF "$FRAMES_IDX = name(node:ref(ComRxFrameRef))"!]
                        [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                            [!VAR "IDX_FOUND" = "1"!]
                        [!ELSE!]
                            [!WARNING!]With the current configuration of [!"$TP_CHANNEL_NAME"!] channel, STMin value <= EB_MANAGE_PERIOD. Therefore, EB layer scheduling is not fast enough to ensure the correct treatment of the received segments (some segments could be lost). In order to ensure the segmentation process, the stack will manage it in the interrupt routine[!ENDWARNING!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$IDX_FOUND = 1"!]
            [!WS "$WSBase + 4"!]/* Check if an App request frame has been received */
            [!WS "$WSBase + 4"!]eStatus = COM_GetFrameRxFlag (COM_FRAME_IDX_[!"$FRAMES_IDX"!], &ebRxFlag);
            [!WS "$WSBase + 4"!]/* EB CAN layer function has been well executed */
            [!WS "$WSBase + 4"!]if (eStatus == COM_ERR_OK)
            [!WS "$WSBase + 4"!]{
                [!WS "$WSBase + 8"!]/* An App request frame has been received */
                [!WS "$WSBase + 8"!]if (ebRxFlag == COM_TRUE)
                [!WS "$WSBase + 8"!]{
                    [!LOOP "as:modconf('Tp')/Message/*"!]
                        [!IF "Type = 'App'"!]
                            [!IF "$FRAMES_IDX = name(node:ref(ComRxFrameRef))"!]
                                [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                    [!WS "$WSBase + 12"!](void)TP_ReceiveFrame (TP_MSG_IDX_[!"name(.)"!]);
                                [!ENDIF!]
                            [!ENDIF!]
                        [!ENDIF!]
                    [!ENDLOOP!]
                [!WS "$WSBase + 8"!]}
            [!WS "$WSBase + 4"!]}
            [!ENDIF!]
        [!ENDLOOP!]

        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!WS "8"!]}
            [!WS "8"!]break;

            [!IF "$TMP_INDEX_CFG = num:i(count(as:modconf('Com')[1]/ComConfig/*)+(-1))"!]
        default:
            /* Nothing to do */
            break;
    }
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
}
/*----------------------------------{end EB_TpReqManage}----------------------------*/
    [!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
/*----------------------------------{EB_TpRxMsgDataBuffer}--------------------------------*/
NCS_PRI_FCT void EB_TpRxMsgDataBuffer (u16 uwLen, u8 *paubUdsData, tTpMsgIdx uMsgIdx,tTpStatus eStatusMsgData, u8 ubAdressingMode, u8 ubAddressingType)
{

[!IF "$FunctionalMsgExist = 1"!]
    u8 ubError;
    /* No error detected */
    ubError = EB_FALSE;
[!ENDIF!]

        if (eStatusMsgData == TP_ERR_OK)
        {
            PduLengthType ulRxBufferSize;
            tUdsBoolean eStatusRxReq;
            [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
            /* The UDS buffer size is read from the configuration parameter TP_Buffer_Size_Functional and TP_Buffer_Size_Physical*/
            ulRxBufferSize = TP_UDS_GetBufferSize(uMsgIdx);
            [!ELSE!]
            /* For CAN, the buffer size is set to the 4096 Bytes*/
            ulRxBufferSize = EB_CAN_BUFFERSIZE;
            [!ENDIF!]
            /* Diagnostic request treatment */
            eStatusRxReq = UDS_RxRequestWithAddrMode (&uwLen, paubUdsData, ulRxBufferSize, ubAdressingMode, ubAddressingType);

            /* Callout to APP to indicate/update if necessary the data buffer*/
            APP_GetUdsDataBufferInd(&uwLen, paubUdsData, uMsgIdx, eStatusRxReq);

            if (eStatusRxReq == UDS_TRUE)
            {
                /* Answer to the request only it is asked by DIAG layer */
                if (uwLen > 0U)
                {
                    /* Write the answer message data */
                    eStatusMsgData = TP_SetMsgData (uMsgIdx, uwLen, paubUdsData);

                    /* The message data update is complete without any error */
                    if (eStatusMsgData == TP_ERR_OK)
                    {
                        /* Send the Diagnostic answer message */
                        (void)TP_SendMsg (uMsgIdx);
                    }
                    else
                    {
                        [!IF "$FunctionalMsgExist = 1"!]
                        ubError = EB_TRUE;
                        [!ELSE!]
                        /* Nothing to do */
                        [!ENDIF!]
                    }
                }
                else
                {
                    [!IF "$FunctionalMsgExist = 1"!]
                    ubError = EB_TRUE;
                    [!ELSE!]
                    /* Nothing to do */
                    [!ENDIF!]
                }
            }
            [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
            /* In the case of a NRC 78 */
            else if (eStatusRxReq == UDS_NRC_78)
            {
                /* Memorize the TpMsgIdx in order to manage the next possible NRC78 */
                /* coming later with UDS_LongRequestResponseInd callback */
                m_ubTpMsgIdxNrc78 = uMsgIdx;
                [!IF "$FunctionalMsgExist = 1"!]
                /* Lock all functional channel during response pending to avoid any buffer problem */
                    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                        [!WS "16"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                        [!ENDIF!]
                    [!ENDFOR!]
                [!ENDIF!]
                /* TP reception is locked while current long request is pending */
                (void)TP_RxEnable(m_ubTpMsgIdxNrc78, TP_RX_ENABLE_OFF);
            }
            [!ENDIF!]
            else
            {
                [!IF "$FunctionalMsgExist = 1"!]
                /* Invalid parameter for function UDS_RxRequest */
                ubError = EB_TRUE;
                [!ELSE!]
                /* Nothing to do */
                [!ENDIF!]
            }
        }
        else
        {
            [!IF "$FunctionalMsgExist = 1"!]
            ubError = EB_TRUE;
            [!ELSE!]
            /* Nothing to do */
            [!ENDIF!]
        }
[!IF "$FunctionalMsgExist = 1"!]
        /* If an error happened unlock all TP channel */
        if (EB_TRUE == ubError)
        {
            [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                [!WS "12"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
                [!ENDIF!]
            [!ENDFOR!]
        }
[!ENDIF!]

}
/*----------------------------------{end EB_TpRxMsgDataBuffer}----------------------------*/
    [!ENDIF!]
[!ENDIF!]



[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
/*----------------------------------{EB_TpRxMsgManage}--------------------------------*/
NCS_PRI_FCT void EB_TpRxMsgManage (void)
{
[!NOCODE!]
    [!MACRO "Code_Get_Physical_Diag_Msg", "FunctionalMsgIdx"!]
    [!LOOP "as:modconf('Tp')/Message/*"!]
        [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd') and Adressing_Mode = 'Physical' and ComTxFrameRef= $FunctionalMsgIdx"!]
uMsgIdx = TP_MSG_IDX_[!"name(.)"!];
        [!ENDIF!]
    [!ENDLOOP!]
    [!ENDMACRO!]
[!ENDNOCODE!]
    [!LOOP "as:modconf('Tp')/Message/*"!]
    [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
        [!IF "Mode = 'Half_Duplex'"!]
    /* Check if a complete TP frame has been received */
    if ( EB_TRUE == m_uEbTpMsgFlagIdx[!"name(.)"!])
    {
        /* Data and length of the Diagnostic messages */
        u8 *paubUdsData;
        u16 uwLen;
        tTpMsgIdx uMsgIdx;
        /* Transport Protocol functions return status */
        tTpStatus eStatus ;

        /* Reset indication flag */
        m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_FALSE;

        uMsgIdx = TP_MSG_IDX_[!"name(.)"!];

        /* Read the received message data */
        eStatus = TP_GetMsgData (uMsgIdx, &uwLen, &paubUdsData);
[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN'"!]
        [!IF "Adressing_Mode = 'Functional'"!]
        /* ISO/FDIS 15765-4:2004(E) p12 */
        /* Always response with peer to peer identifier and never to broadcast */

        [!WS "8"!][!CALL "Code_Get_Physical_Diag_Msg", "FunctionalMsgIdx"="ComTxFrameRef"!][!CR!]
        [!ENDIF!]
[!ENDIF!]

        /* EB data buffer */
        EB_TpRxMsgDataBuffer(uwLen, paubUdsData, uMsgIdx, eStatus, [!IF "Adressing_Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSE!]UDS_ADDR_FUNCTIONAL[!ENDIF!], [!IF "Type = 'Diag'"!]UDS_TYPE_DIAG[!ELSEIF "Type = 'Obd'"!]UDS_TYPE_OBD[!ELSEIF "Type = 'Diag_Obd'"!]UDS_TYPE_DIAG_OBD[!ENDIF!]);

    }/* End of Uds message */

        [!ENDIF!]
    [!ENDIF!]
    [!ENDLOOP!]
}
/*----------------------------------{end EB_TpRxMsgManage}----------------------------*/
    [!ENDIF!]
[!ENDIF!]
/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */

[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
[!IF "node:exists(as:modconf('Com'))"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
FUNC(boolean, COM_APPL_CODE) Com_EBRxFrameAutosar
(
uint8 Hrh,
Can_IdType CanId,
uint8 CanDlc,
const uint8 *CanSduPtr
)
{
    /* Source Tester Address */
    VAR(uint8, AUTOMATIC) m_ubSourceTesterAddress;

    /* Index of Message corresponding to Can Identifier */
    VAR(uint8, AUTOMATIC) ubLoopIndex;
    VAR(uint8, AUTOMATIC) ubIdFound = FALSE;
    VAR(uint8, AUTOMATIC) ubCanIdType;

    /* Result */
    VAR(boolean, AUTOMATIC) ubCheckResult = (boolean)FALSE;

    DBG_COM_EBRXFRAMEAUTOSAR_ENTRY(Hrh,CanId,CanDlc,CanSduPtr);

    /* Filter the most significant bit */
    CanId = (uint32)(CanId & 0x1FFFFFFFU);

    /* Look for the identifier in the mapping table and collect Can Identifier type */
    for (ubLoopIndex = 0; ((ubIdFound == FALSE) && (ubLoopIndex < EB_TP_PHYS_MESS_NBR)); ubLoopIndex++)
    {
        /* If the Can Identifier has been found in the table */
        if (aubTpTesterAddrRef[ubLoopIndex].CanId == CanId)
        {
            /* Collect the Can Identifier */
            ubCanIdType = aubTpTesterAddrRef[ubLoopIndex].CanIdType;

            /* For Extended Can Identifiers */
            if (EXTENDED_ID == ubCanIdType)
            {
                /* Extract Source Tester Address from Frame Id (last two bytes) */
                m_ubSourceTesterAddress = (uint8)(CanId & ((Can_IdType)0xFF));
            }
            /* For Standard Can Identifiers */
            else
            {
                /* Nothing to do as Standard Identifiers are not filtered */
            }

            /* Set the flag to mention that the Can Identifier has been found */
            ubIdFound = TRUE;
        }
    }

    /* If the Can Identifier was found */
    if (TRUE == ubIdFound)
    {
        /* For Extended Identifiers */
        if (EXTENDED_ID == ubCanIdType)
        {
            /* If no Tester Address has been selected yet */
            if (EB_ALL_TESTER_ADDRESS == m_ubTesterAddress)
            {
                /* The Check Result is OK */
                ubCheckResult = (boolean)TRUE;

                /* Store the extracted Tester Address in order to compare it with */
                /* tester Address of future received frames */
                EB_SetTesterAddress(m_ubSourceTesterAddress);
            }
            /* A Tester Address was already stored */
            else
            {
                /* If the allowed Tester Address is the same that Source Tester Address */
                if (m_ubTesterAddress == m_ubSourceTesterAddress)
                {
                    /* The Check Result is OK */
                    ubCheckResult = (boolean)TRUE;
                }
                /* If the allowed Tester Address is not the same that Target Address */
                else
                {
                    /* The Check Result is KO */
                    ubCheckResult = (boolean)FALSE;
                }
            }
        }
        /* All Standard identifiers are allowed */
        else
        {
            /* The Check Result is OK */
            ubCheckResult = (boolean)TRUE;
        }
    }
    /* No Can Identifier was found */
    else
    {
        /* The Check Result is KO */
        ubCheckResult = (boolean)FALSE;
    }

    DBG_COM_EBRXFRAMEAUTOSAR_EXIT(ubCheckResult);
    /* return the result */
    return ubCheckResult;
}
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('EB')/General/Protocol_Type = 'CAN' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
[!IF "node:exists(as:modconf('Com'))"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*----------------------------------{COM_EBRxFrame}--------------------------------*/
u8 Com_EBRxFrame(u8 ubFrameIndex)
{

    u8 ubCheckResult;
    DBG_COM_EBRXFRAME_ENTRY(ubFrameIndex);
    if(m_ubTesterAddress == EB_ALL_TESTER_ADDRESS)
    {
        ubCheckResult = COM_RX_IND_CHECK_OK;

        /* Select the current Tester Address */
        EB_SetTesterAddress(aubCOMRxFrame[ubFrameIndex]);
    }
    else
    {
        if(m_ubTesterAddress == aubCOMRxFrame[ubFrameIndex])
        {
            ubCheckResult = COM_RX_IND_CHECK_OK;
        }
        else
        {
            ubCheckResult = COM_RX_IND_CHECK_REJECT;
        }
    }
    DBG_COM_EBRXFRAME_EXIT(ubCheckResult);
    return ubCheckResult;
}
/*----------------------------------{end COM_EBRxFrame}----------------------------*/
[!ENDIF!]
[!ENDIF!]

/*----------------------------------{COM_NAsInd}--------------------------------*/
void COM_NAsInd (tComFrameIdx uFrameIdx)
{
    DBG_COM_NASIND_ENTRY(uFrameIdx);
[!IF "node:exists(as:modconf('Tp'))"!]
    /* For the Transport Protocol, N_As indication
       Associate the COM frame to the TP message */
    [!LOOP "as:modconf('Com')/ComConfig/*"!]
        [!VAR "TMP_NAME_CFG" = "@name"!]
        [!VAR "TMP_INDEX_CFG" = "@index"!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!IF "$TMP_INDEX_CFG = 0"!]
    switch(ubConfigurationSelection)
    {
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ELSE!]
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ENDIF!]
        [!ENDIF!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
    [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComTxFrameRef))"!])
    [!WS "$WSBase + 4"!]{
        [!WS "$WSBase + 8"!]TP_ComNAsInd (TP_MSG_IDX_[!"name(.)"!]);
    [!WS "$WSBase + 4"!]}
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!WS "8"!]}
            [!WS "8"!]break;

            [!IF "$TMP_INDEX_CFG = num:i(count(as:modconf('Com')[1]/ComConfig/*)+(-1))"!]
        default:
            /* Nothing to do */
            break;
    }
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]

    APP_ComNAsInd(uFrameIdx);

    DBG_COM_NASIND_EXIT();
}
/*----------------------------------{end COM_NAsInd}----------------------------*/


[!IF "(node:exists(as:modconf('Com')))"!]
/*----------------------------------{COM_TxTimeoutInd}--------------------------------*/
tComStatus COM_TxTimeoutInd (tComFrameIdx uFrameIdx)
{
    tComStatus eStatus;
    DBG_COM_TXTIMEOUTIND_ENTRY(uFrameIdx);

    /* Careful APP_ComTxTimeoutInd must be called first,                */
    /* in case of a DIAG frame, eStatus is overwritten (COM_ERR_ABORT), */
    /* and frame transmission is then cancelled (COM)                   */
    eStatus = APP_ComTxTimeoutInd(uFrameIdx);

[!IF "node:exists(as:modconf('Tp'))"!]
    /* For the Transport Protocol, N_As indication
       Associate the COM frame to the TP message */
    [!LOOP "as:modconf('Com')/ComConfig/*"!]
        [!VAR "TMP_NAME_CFG" = "@name"!]
        [!VAR "TMP_INDEX_CFG" = "@index"!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!IF "$TMP_INDEX_CFG = 0"!]
    switch(ubConfigurationSelection)
    {
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ELSE!]
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ENDIF!]
        [!ENDIF!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
    [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComTxFrameRef))"!])
    [!WS "$WSBase + 4"!]{
        [!WS "$WSBase + 8"!]eStatus = COM_ERR_ABORT;
    [!WS "$WSBase + 4"!]}
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!WS "8"!]}
            [!WS "8"!]break;

            [!IF "$TMP_INDEX_CFG = num:i(count(as:modconf('Com')[1]/ComConfig/*)+(-1))"!]
        default:
            /* Nothing to do */
            break;
    }
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]
    DBG_COM_TXTIMEOUTIND_ENTRY(eStatus);
    return eStatus;
}
/*----------------------------------{end COM_TxTimeoutInd}----------------------------*/
[!ENDIF!]


/*----------------------------------{COM_TxConf}--------------------------------*/
[!IF "node:exists(as:modconf('Can'))"!]
void COM_TxConf (tComFrameIdx uFrameIdx)
{
    DBG_COM_TXCONF_ENTRY(uFrameIdx);
[!IF "node:exists(as:modconf('Tp'))"!]
    [!LOOP "as:modconf('Com')/ComConfig/*"!]
        [!VAR "TMP_NAME_CFG" = "@name"!]
        [!VAR "TMP_INDEX_CFG" = "@index"!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!IF "$TMP_INDEX_CFG = 0"!]
    switch(ubConfigurationSelection)
    {
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ELSE!]
        case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
        {
            [!ENDIF!]
        [!ENDIF!]
    [!WS "$WSBase + 4"!]/* For the Transport Protocol, Tx confirmation
    [!WS "$WSBase + 4"!]   Associate the COM frame to the TP message */
    [!LOOP "as:modconf('Tp')/Message/*"!]
        [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
            [!IF "Mode = 'Half_Duplex'"!]
    [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComTxFrameRef))"!])
    [!WS "$WSBase + 4"!]{
        [!WS "$WSBase + 8"!]TP_ComTxConf (TP_MSG_IDX_[!"name(.)"!]);
    [!WS "$WSBase + 4"!]}
                    [!ELSE!]
    [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComTxFrameRef))"!])
    [!WS "$WSBase + 4"!]{
        [!WS "$WSBase + 8"!]TP_ComTxConf (TP_MSG_IDX_[!"name(.)"!]);
    [!WS "$WSBase + 4"!]}
    [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComTxFCFrameRef))"!])
    [!WS "$WSBase + 4"!]{
        [!WS "$WSBase + 8"!]TP_ComTxConfFC (TP_MSG_IDX_[!"name(.)"!]);
    [!WS "$WSBase + 4"!]}
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
        [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
            [!WS "8"!]}
            [!WS "8"!]break;

            [!IF "$TMP_INDEX_CFG = num:i(count(as:modconf('Com')[1]/ComConfig/*)+(-1))"!]
        default:
            /* Nothing to do */
            break;
    }
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]

    APP_ComTxConf(uFrameIdx);

    DBG_COM_TXCONF_EXIT();
}
[!ENDIF!]
/*----------------------------------{end COM_TxConf}----------------------------*/


/*----------------------------------{COM_ComBackInd}--------------------------------*/
void COM_ComBackInd (tComMonNodeIdx uNodeIdx)
{
    DBG_COM_COMBACKIND_ENTRY(uNodeIdx);
    APP_ComBackInd (uNodeIdx);
    DBG_COM_COMBACKIND_EXIT();
}
/*----------------------------------{end COM_ComBackInd}----------------------------*/


/*----------------------------------{COM_ComLossInd}--------------------------------*/
void COM_ComLossInd (tComMonNodeIdx uNodeIdx)
{
    DBG_COM_COMLOSSIND_ENTRY(uNodeIdx);
    APP_ComLossInd (uNodeIdx);
    DBG_COM_COMLOSSIND_EXIT();
}
/*----------------------------------{end COM_ComLossInd}----------------------------*/


/*----------------------------------{COM_ModeModifyExtension}--------------------------------*/
void COM_ModeModifyExtension (tComMode eCurMode)
{
    DBG_COM_MODEMODIFYEXTENSION_ENTRY(eCurMode);
    [!IF "node:exists(as:modconf('Tp'))"!]
    /* OSCEB-73 : Init TP layer when the COM layer switches to BUS_ON mode */
    if (COM_MODE_BUS_ON == eCurMode)
    {
        TP_Init();
    }

    [!ENDIF!]
    APP_ComModeModifyExtension (eCurMode);
    DBG_COM_MODEMODIFYEXTENSION_EXIT();
}
/*----------------------------------{end COM_ModeModifyExtension}----------------------------*/


/*----------------------------------{COM_TxFrameInd}--------------------------------*/
void COM_TxFrameInd (tComFrameIdx uFrameIdx)
{
    DBG_COM_TXFRAMEIND_ENTRY(uFrameIdx);
    APP_ComTxFrameInd (uFrameIdx);
    DBG_COM_TXFRAMEIND_EXIT();
}
/*----------------------------------{end COM_TxFrameInd}----------------------------*/


/*----------------------------------{COM_MonNodeStatusInd}--------------------------------*/
void COM_MonNodeStatusInd(tComMonNodeIdx uNodeIdx, tComMonStatus eFrameStatus)
{
    DBG_COM_MONNODESTATUSIND_ENTRY(uNodeIdx, eFrameStatus);
    /* APP indication for default management */
    APP_COM_MonNodeStatusInd(uNodeIdx, eFrameStatus);
    DBG_COM_MONNODESTATUSIND_EXIT();
}
/*----------------------------------{end COM_MonNodeStatusInd}----------------------------*/

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
    [!IF "CbkOnRxFrame_callback = 'EB'"!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
        [!IF "CbkOnRxFrame != ''"!]
            [!VAR "TMP_CBK" = "CbkOnRxFrame"!]
            [!VAR "TMP_CNT2" = "0"!]
            [!VAR "TMP_CNT" = "0"!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
                [!IF "CbkOnRxFrame = $TMP_CBK"!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!]
            [!ELSE!]
/*----------------------------------{[!"CbkOnRxFrame"!]}--------------------------------*/
u8 [!"CbkOnRxFrame"!](tComFrameIdx uFrameIdx)
{
    OSC_PARAM_UNUSED(uFrameIdx);
    /* No dummy code here because for some compilers provoks an ERROR */
    /* QAC warning accepted for this case */
    return COM_RX_IND_CHECK_OK;
}
/*----------------------------------{end [!"CbkOnRxFrame"!]}----------------------------*/
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
    [!IF "CbkOnRxData_callback = 'EB'"!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
        [!IF "CbkOnRxData != ''"!]
            [!VAR "TMP_CBK" = "CbkOnRxData"!]
            [!VAR "TMP_CNT2" = "0"!]
            [!VAR "TMP_CNT" = "0"!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
                [!IF "CbkOnRxData = $TMP_CBK"!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!]
            [!ELSE!]
/*----------------------------------{[!"CbkOnRxData"!]}--------------------------------*/
void [!"CbkOnRxData"!](tComFrameIdx uFrameIdx)
{
        /* No dummy code here because for some compilers provoks an ERROR */
        /* QAC warning accepted for this case */
}
/*----------------------------------{end [!"CbkOnRxData"!]}----------------------------*/
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!/* This API only exists if at least one value of STMIN <= EB_Manage_Period */!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!VAR "NbOfSTMinLowerThanEBManage" = "0"!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!/* Does this configuration has TP channel which has STMin <= EB_MANAGE_PERIOD ? */!]
            [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) >= num:i(Rx_STmin)"!]
                [!VAR "NbOfSTMinLowerThanEBManage" = "$NbOfSTMinLowerThanEBManage + 1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!IF "$NbOfSTMinLowerThanEBManage != 0"!]
/*----------------------------------{COM_CbkRxTpSegUnderIT}--------------------------------*/
void COM_CbkRxTpSegUnderIT (tComFrameIdx uFrameIdx)
{
    DBG_COM_CBKRXTPSEGUNDERIT_ENTRY(uFrameIdx);

    /* For the Transport Protocol, this API links */
    /* the COM frame to the right TP message      */
    [!/* Multiconfiguration management: create switch case */!]
    [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1"!]
    switch(ubConfigurationSelection)
    {
    [!ENDIF!]
        [!/* For each COM configuration */!]
        [!LOOP "as:modconf('Com')/ComConfig/*"!]
        [!VAR "TMP_INDEX_CFG" = "@index"!]
        [!VAR "TMP_NAME_CFG" = "@name"!]
        [!VAR "TMP_NbTpChannelAtSameCfg" = "0"!]
            [!/* For each TP channel */!]
            [!LOOP "as:modconf('Tp')/Message/*"!]
                [!/* Test if TP channel belongs to current configuration */!]
                [!IF "substring-before(substring-after(ComRxFrameRef,"/Com/Com/"),"/") = $TMP_NAME_CFG"!]
                    [!/* Then test for this channel if STMin <= EB_MANAGE_PERIOD */!]
                    [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) >= num:i(Rx_STmin)"!]
                    [!VAR "TMP_NbTpChannelAtSameCfg" = "$TMP_NbTpChannelAtSameCfg +1"!]
                        [!/* Generate 'case' only for the first TP channel with STMin <= EB_MANAGE_PERIOD */!]
                        [!IF "(num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1 ) and ($TMP_NbTpChannelAtSameCfg = 1)"!]
                            [!WS "8"!]case COM_CONFIG_IDX_[!"$TMP_INDEX_CFG"!]:
                            [!WS "8"!]{
                        [!ENDIF!]
            [!WS "$WSBase + 4"!]if (uFrameIdx == COM_FRAME_IDX_[!"name(node:ref(ComRxFrameRef))"!])
            [!WS "$WSBase + 4"!]{
            [!WS "$WSBase + 8"!](void)TP_ReceiveFrame (TP_MSG_IDX_[!"name(.)"!]);
            [!WS "$WSBase + 4"!]}
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!/* Generate 'break' only if at least one TP channel with STMin <= EB_MANAGE_PERIOD */!]
            [!IF "(num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1 )and ($TMP_NbTpChannelAtSameCfg > 0)"!]
            [!WS "8"!]}
            [!WS "8"!]break;

            [!ENDIF!]
        [!ENDLOOP!]
        [!/* Multiconfiguration management: end of switch case */!]
        [!IF "(num:i(count(as:modconf('Com')[1]/ComConfig/*)) > 1 ) and ($TMP_INDEX_CFG  = num:i(count(as:modconf('Com')[1]/ComConfig/*)+(-1)))"!]
        default:
            /* Nothing to do */
            break;
    }
        [!ENDIF!]
    DBG_COM_CBKRXTPSEGUNDERIT_EXIT();
}
/*----------------------------------{end COM_CbkRxTpSegUnderIT}----------------------------*/
    [!ENDIF!]
[!ENDIF!]

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
    [!IF "CbkOnRxInvalidDLC_callback = 'EB'"!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
        [!IF "CbkOnRxInvalidDLC != ''"!]
            [!VAR "TMP_CBK" = "CbkOnRxInvalidDLC"!]
            [!VAR "TMP_CNT2" = "0"!]
            [!VAR "TMP_CNT" = "0"!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!]
                [!IF "CbkOnRxInvalidDLC = $TMP_CBK"!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!]
            [!ELSE!]
/*----------------------------------{[!"CbkOnRxInvalidDLC"!]}--------------------------------*/
void [!"CbkOnRxInvalidDLC"!](tComFrameIdx uFrameIdx)
{
        /* No dummy code here because for some compilers provoks an ERROR */
        /* QAC warning accepted for this case */
}
/*----------------------------------{end [!"CbkOnRxInvalidDLC"!]}----------------------------*/
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('Can')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
#if (CAN_WAKE_UP_DETECTION  == CAN_WAKE_UP_ACTIVATE)
/*----------------------------------{CAN_WakeUpInd}--------------------------------*/
void CAN_WakeUpInd (void)
{
    DBG_CAN_WAKEUPIND_ENTRY();
    APP_CanWakeUpInd ();
    DBG_CAN_WAKEUPIND_EXIT();
}
/*----------------------------------{end CAN_WakeUpInd}----------------------------*/
#endif


/*----------------------------------{CAN_CtrlModeErrorInd}--------------------------------*/
void CAN_CtrlModeErrorInd (tCanErrors uErrorID)
{
    DBG_CAN_CTRLMODEERRORIND_ENTRY(uErrorID);
    APP_CanCtrlModeErrorInd (uErrorID);
    DBG_CAN_CTRLMODEERRORIND_EXIT();
}
/*----------------------------------{end CAN_CtrlModeErrorInd}----------------------------*/
[!ENDIF!]

/*----------------------------------{EB_Manage}--------------------------------*/
void EB_Manage (void)
{
    DBG_EB_MANAGE_ENTRY();
[!//
[!/* This API only exists if at least one value of STMIN > EB_Manage_Period */!]
[!IF "node:exists(as:modconf('Tp')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!VAR "NbOfSTMinLargerThanEBManage" = "0"!]
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!/* Does this configuration has TP channel which has STMin <= EB_MANAGE_PERIOD ? */!]
            [!IF "num:i(as:modconf('EB')/General/MANAGE_PERIOD) < num:i(Rx_STmin)"!]
                [!VAR "NbOfSTMinLargerThanEBManage" = "$NbOfSTMinLargerThanEBManage + 1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!IF "$NbOfSTMinLargerThanEBManage != 0"!]
    /* Scheduler to receive a segmented frame */
    /* For segmented communication, EB_TpReqManage must be called first */
    EB_TpReqManage();

    [!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
        [!IF "$FullDuplexUses = 1"!]
    /* Scheduler to link segmented frames to UDS for full duplex */
    EB_TpRxMsgManageFullDuplex();
        [!ENDIF!]
    /* Scheduler to link segmented frames to UDS */
    EB_TpRxMsgManage();
    [!ENDIF!]
[!ENDIF!]
[!//
[!IF "node:exists(as:modconf('CanTp')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    /* CanTp Main Function */
    CanTp_MainFunction();
[!ENDIF!]
[!//
[!IF "node:exists(as:modconf('Tp')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF " (num:i(as:modconf('Tp')/TpGeneral/TpManagePeriod) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    /* Scheduler for TP */
    /* For segmented communication, TP_Manage must be called before COM_Manage */
    if (m_ubTpManageCnt >= ((TP_MANAGE_PERIOD / EB_MANAGE_PERIOD) - 1U))
    {
        m_ubTpManageCnt = 0U;

        /* Transport protocol management */
        TP_Manage();
    }
    else
    {
        m_ubTpManageCnt ++;
    }
    [!ELSE!]
    /* Transport protocol management */
    TP_Manage();
    [!ENDIF!]

[!ENDIF!]
[!//

[!IF "node:exists(as:modconf('Com')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    [!IF " (num:i(as:modconf('Com')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    /* Scheduler for COM */
    if (m_ubComManageCnt >= ((COM_MANAGE_PERIOD / EB_MANAGE_PERIOD) - 1U))
    {
        m_ubComManageCnt = 0U;

        /* Communication management */
        COM_Manage ();
    }
    else
    {
        m_ubComManageCnt ++;
    }
    [!ELSE!]
    /* Communication management */
    COM_Manage ();
    [!ENDIF!]

[!ENDIF!]
[!//
[!IF "node:exists(as:modconf('Uds'))"!]
    /* Scheduler for Diagnostic */
    [!IF " (num:i(as:modconf('Uds')/General/UDS_MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    if (m_ubDiagManageCnt >= ((UDS_MANAGE_PERIOD / EB_MANAGE_PERIOD) - 1U))
    {
        m_ubDiagManageCnt = 0U;

        /* Diagnostic management */
        UDS_Manage ();
    }
    else
    {
        m_ubDiagManageCnt ++;
    }
    [!ELSE!]
    /* Diagnostic management */
    UDS_Manage ();
    [!ENDIF!]
[!ENDIF!]
[!//
[!IF "node:exists(as:modconf('Prog'))"!]
    [!IF " (num:i(as:modconf('Prog')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    /* Scheduler for PROG */
    if (m_ubProgManageCnt >= ((PROG_MANAGE_PERIOD / EB_MANAGE_PERIOD) - 1U))
    {
        m_ubProgManageCnt = 0U;

        /* PROG */
        PROG_Manage();
    }
    else
    {
        m_ubProgManageCnt ++;
    }
    [!ELSE!]
    /* PROG management */
    PROG_Manage();
    [!ENDIF!]

[!ENDIF!]
[!//
[!IF "node:exists(as:modconf('SA'))"!]
    [!IF " (num:i(as:modconf('SA')/General/MANAGE_PERIOD) != num:i(as:modconf('EB')/General/MANAGE_PERIOD))"!]
    /* Scheduler for SA */
    if (m_ubSAManageCnt >= ((SA_MANAGE_PERIOD / EB_MANAGE_PERIOD) - 1U))
    {
        m_ubSAManageCnt = 0U;

        /* SA management */
        SA_Manage();
    }
    else
    {
        m_ubSAManageCnt ++;
    }
    [!ELSE!]
    /* SA management */
    SA_Manage();
    [!ENDIF!]
[!ENDIF!]
    DBG_EB_MANAGE_EXIT();
}
/*----------------------------------{end EB_Manage}----------------------------*/


[!IF "node:exists(as:modconf('Tp'))"!]
/*----------------------------------{TP_DataBufferEmptyInd}--------------------------------*/
void TP_DataBufferEmptyInd (tTpMsgIdx uMsgIdx)
{
    DBG_TP_DATABUFFEREMPTYIND_ENTRY(uMsgIdx);
    APP_TpDataBufferEmptyInd(uMsgIdx);
    DBG_TP_DATABUFFEREMPTYIND_EXIT();
}
/*----------------------------------{end TP_DataBufferEmptyInd}----------------------------*/


/*----------------------------------{TP_TxConf}--------------------------------*/
void TP_TxConf (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    DBG_TP_TXCONF_ENTRY(uMsgIdx, ebStatus);
[!IF "node:exists(as:modconf('Uds')) and (count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1)"!]
  [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    /* NRC_78 TxConf is received */
    if ( uMsgIdx == m_ubTpMsgIdxNrc78 )
    {
        /* Transmission to UDS */
        UDS_LongRequestRespTxConf();
    }
    /* If not in response pending state unlock all TP channel */
    else
    {
    [!IF "$FunctionalMsgExist = 1"!]
        /* Enable all TP functional channel after physical transmission are done*/
      [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
          [!WS "8"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "as:modconf('Uds')/General/RELOAD_TSTOPDIAG = 'true'"!]
        {
            switch(uMsgIdx)
            {
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
      [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd')"!]
                case TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!]:
      [!ENDIF!]
    [!ENDFOR!]
                    /* UnLock all physical channels after sending response */
                    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Physical'"!]
                        [!WS "08"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
                        [!ENDIF!]
                    [!ENDFOR!]
                    UDS_ReloadTStopDiag();
                    break;
                default:
                    /* Nothing to do */
                    break;
            }
        }
  [!ENDIF!]
  [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    }
  [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    EB_TxConf(uMsgIdx);
[!ENDIF!]
    APP_TpTxConf(uMsgIdx, ebStatus);
[!IF "node:exists(as:modconf('Prog'))"!]
    PROG_TpTxConf(uMsgIdx, ebStatus);
[!ENDIF!]
    DBG_TP_TXCONF_EXIT();
}
/*----------------------------------{end TP_TxConf}----------------------------*/


/*----------------------------------{TP_RxInd}--------------------------------*/
void TP_RxInd (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    DBG_TP_RXIND_ENTRY(uMsgIdx, ebStatus);

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "DIAG_MESS_NB" = "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')])"!]
    [!IF "$DIAG_MESS_NB > 0"!]
    if (ebStatus == TP_MSG_STATUS_OK)
    {
        switch(uMsgIdx)
        {
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
                [!IF "Mode = 'Half_Duplex'"!]
            case TP_MSG_IDX_[!"name(.)"!]:
                /* Notification for scheduling */
                m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_TRUE;

                [!IF "$FunctionalMsgExist = 1"!]
                /* Lock all functional channel to avoid any buffer problem */
                    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                        [!WS "24"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                        [!ENDIF!]
                    [!ENDFOR!]
                [!ENDIF!]
                break;

                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
            default:
                /* Nothing to do */
                break;
        }
    }
        [!IF "as:modconf('Uds')/General/RELOAD_TSTOPDIAG = 'true'"!]
    else
    {
        /* Reload UDS S3 timer */
        UDS_ReloadTStopDiag();
    }
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]

    APP_TpRxInd (uMsgIdx, ebStatus);
[!IF "node:exists(as:modconf('Prog'))"!]
    PROG_TpRxInd (uMsgIdx, ebStatus);
[!ENDIF!]

    DBG_TP_RXIND_EXIT(uMsgIdx, ebStatus);
}
/*----------------------------------{end TP_RxInd}----------------------------*/


/*----------------------------------{TP_RxEnableInd}--------------------------------*/
void TP_RxEnableInd (tTpMsgIdx uMsgIdx, tTpRxEnable uRxEnable)
{
    DBG_TP_RXENABLEIND_ENTRY(uMsgIdx, uRxEnable);
    [!IF "node:exists(as:modconf('Uds')) and (count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1) and as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    /* A long request is still pending */
    if ( (uMsgIdx == m_ubTpMsgIdxNrc78) && (TP_RX_ENABLE_ON == uRxEnable))
    {
        [!IF "$FunctionalMsgExist = 1"!]
         /* relock all functional TP channel if response pending is running */
            [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                [!WS "8"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                [!ENDIF!]
            [!ENDFOR!]
        [!ENDIF!]
        /* Re lock the TP channel because NRC_78 is not completed */
        (void)TP_RxEnable(m_ubTpMsgIdxNrc78, TP_RX_ENABLE_OFF);
    }

    else
    {
        /* Nothing to do */
    }
    [!ENDIF!]

    APP_TpRxEnableInd(uMsgIdx, uRxEnable);
    DBG_TP_RXENABLEIND_EXIT();
}
/*----------------------------------{end TP_RxEnableInd}----------------------------*/

[!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
/*----------------------------------{TP_StreamingFrameReceived}---------------------*/
void TP_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData)
{
    DBG_TP_STREAMINGFRAMERECEIVED_ENTRY(ulReceivedDataLength, aubData);
    /* If the streaming is allowed forward the information to PROG */
    if(m_ubStreamingSetting == EB_STREAMING_ALLOWED)
    {
        PROG_StreamingFrameReceived(ulReceivedDataLength,aubData);
    }
    DBG_TP_STREAMINGFRAMERECEIVED_EXIT();
}
/*----------------------------------{end TP_StreamingFrameReceived}-----------------*/

/*----------------------------------{EB_SetStreamingStatus}-------------------------*/
void EB_SetStreamingStatus(u8 ubStreamingState)
{
    DBG_EB_SETSTREAMINGSTATUS_ENTRY(ubStreamingState);
    /* If the streaming is allowed forward the information to PROG */
    if(ubStreamingState == EB_STREAMING_FORBIDDEN)
    {
        m_ubStreamingSetting = EB_STREAMING_FORBIDDEN;
    }
    else
    {
        m_ubStreamingSetting = EB_STREAMING_ALLOWED;
    }
    DBG_EB_SETSTREAMINGSTATUS_EXIT();
}
/*----------------------------------{end EB_SetStreamingStatus}----------------------*/
[!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('Uds'))"!]

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Uds')/Service/*"!]
[!IF "Callback_Origin = 'EB'"!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
[!IF "Callback != ''"!]
[!VAR "TMP_CBK" = "Callback"!]
[!VAR "TMP_CNT2" = "0"!]
[!VAR "TMP_CNT" = "0"!]
[!LOOP "../../Service/*"!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!]
[!IF "Callback = $TMP_CBK"!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!]
[!ELSE!]
/*----------------------------------{[!"Callback"!]}--------------------------------*/
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*----------------------------------{end [!"Callback"!]}----------------------------*/
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Uds')/Service_DID/*"!]
[!IF "Callback_Origin = 'EB'"!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
[!IF "Callback != ''"!]
[!VAR "TMP_CBK" = "Callback"!]
[!VAR "TMP_CNT2" = "0"!]
[!VAR "TMP_CNT" = "0"!]
[!LOOP "../../Service_DID/*"!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!]
[!IF "Callback = $TMP_CBK"!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!]
[!ELSE!]
/*----------------------------------{[!"Callback"!]}--------------------------------*/
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    *puwLen = 3U;
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*----------------------------------{end [!"Callback"!]}----------------------------*/
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Uds')/Routine_Control/*"!]
[!IF "Callback_Origin = 'EB'"!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
[!IF "Callback != ''"!]
[!VAR "TMP_CBK" = "Callback"!]
[!VAR "TMP_CNT2" = "0"!]
[!VAR "TMP_CNT" = "0"!]
[!LOOP "../../Routine_Control/*"!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!]
[!IF "Callback = $TMP_CBK"!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!]
[!ELSE!]
/*----------------------------------{[!"Callback"!]}--------------------------------*/
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*----------------------------------{end [!"Callback"!]}----------------------------*/
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]

[!VAR "TMP_CNT1" = "0"!]
[!LOOP "as:modconf('Uds')/Service_OBD/*"!]
[!IF "Callback_Origin = 'EB'"!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!]
[!IF "Callback != ''"!]
[!VAR "TMP_CBK" = "Callback"!]
[!VAR "TMP_CNT2" = "0"!]
[!VAR "TMP_CNT" = "0"!]
[!LOOP "../../Service_OBD/*"!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!]
[!IF "Callback = $TMP_CBK"!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!]
[!ELSE!]
/*----------------------------------{[!"Callback"!]}--------------------------------*/
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*----------------------------------{end [!"Callback"!]}----------------------------*/
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]


/*----------------------------------{UDS_SessionStatusInd}--------------------------------*/
void UDS_SessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{
    DBG_UDS_SESSIONSTATUSIND_ENTRY(eUdsNewSessType, eUdsOldSessType,eUdsChangingCause );
[!IF "node:exists(as:modconf('Prog'))"!]
    if(eUdsNewSessType == UDS_SESSION_PROGRAMMING)
    {
        /* action to perform on programming session opening */
        PROG_OpenProgrammingSession();
    }
    else
    {
        /* if leaving programming session */
        if(eUdsOldSessType == UDS_SESSION_PROGRAMMING)
        {

            PROG_CloseProgrammingSession(eUdsChangingCause);
        }
        else
        {
            /* Nothing to do */
        }
    }

    APP_UdsSessionStatusInd (eUdsNewSessType, eUdsOldSessType, eUdsChangingCause);
[!ELSE!]
    OSC_PARAM_UNUSED(eUdsNewSessType);
    OSC_PARAM_UNUSED(eUdsOldSessType);
    OSC_PARAM_UNUSED(eUdsChangingCause);
[!ENDIF!]
    DBG_UDS_SESSIONSTATUSIND_EXIT();
}
/*----------------------------------{end UDS_SessionStatusInd}----------------------------*/

[!IF "(count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1) and as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
/*----------------------------------{UDS_LongRequestResponseInd}--------------------------------*/
tUdsStatus UDS_LongRequestResponseInd (u16 uwLen, u8 *aubUdsData)
{
    tTpStatus eStatus ;
[!IF "$FullDuplexUses = 1"!]
    u8 ubTpMsgIdxNrc78;
[!ENDIF!]

    DBG_UDS_LONGREQUESTRESPONSEIND_ENTRY(uwLen, aubUdsData);

    if (aubUdsData == NULL)
    {
        eStatus = UDS_ERR_COHE;
    }
    else
    {
        /* Write the answer message data */
        eStatus = TP_SetMsgData(m_ubTpMsgIdxNrc78, uwLen, aubUdsData);

        /* The message data update is complete without any error */
        if (eStatus == TP_ERR_OK)
        {
            /* Send the Diagnostic answer message */
            (void)TP_SendMsg(m_ubTpMsgIdxNrc78);
        }

         /* NRC_78 tranmission request */
        if ((aubUdsData[0] == UDS_NRC) && (aubUdsData[2] == UDS_NRC_78))
        {
            /* nothing to do */
            /* NRC_78 will be sent */
        }
        else
        {
            [!IF "$FunctionalMsgExist = 1"!]
            /* Unlock TP channels because NRC_78 is completed */
                [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                    [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                        [!WS "12"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
                    [!ENDIF!]
                [!ENDFOR!]
            [!ENDIF!]
            /* Unlock TP channel because NRC_78 is completed */
            (void)TP_RxEnable(m_ubTpMsgIdxNrc78, TP_RX_ENABLE_ON);
[!IF "$FullDuplexUses = 1"!]
            /* Store the m_ubTpMsgIdxNrc78 global variable locally */
            ubTpMsgIdxNrc78 = m_ubTpMsgIdxNrc78;
[!ENDIF!]
            /* End of long request, flag is reset */
            m_ubTpMsgIdxNrc78 = EB_NO_NRC_78;
            [!LOOP "as:modconf('Tp')/Message/*"!]
                [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
                    [!IF "Mode = 'Full_Duplex'"!]
             /* Simulate TxConf to notify that the request treatment is over and free the buffer */
             if((uwLen == 0U) && (ubTpMsgIdxNrc78 == TP_MSG_IDX_[!"name(.)"!]))
             {
                 TP_TxConfFullDuplex(ubTpMsgIdxNrc78,TP_MSG_STATUS_OK);
             }
                    [!ELSE!]
                        [!IF "as:modconf('EB')/Communication/EnableMultipleTpConnection = 'true'"!]
             if((uwLen == 0U) && (ubTpMsgIdxNrc78 == TP_MSG_IDX_[!"name(.)"!]))
             {
                 TP_TxConf(ubTpMsgIdxNrc78,TP_MSG_STATUS_OK);
             }
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!]
        }
        eStatus = UDS_ACK;
    }
    DBG_UDS_LONGREQUESTRESPONSEIND_EXIT(eStatus);
    return eStatus;
}
/*----------------------------------{end UDS_LongRequestResponseInd}----------------------------*/
[!ENDIF!]
[!ENDIF!]

/*----------------------------{EB_IsNetworkSynchronized}------------------------------*/
u8 EB_IsNetworkSynchronized(u8 * frCycle)
{
    u8 SynchroStatus;
[!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY') and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    /* Check if Flexray network is synchronized */
    u16 frMacroTick = 0U;
    DBG_EB_ISNETWORKSYNCHRONIZED_ENTRY(frCycle);

    if (FrIf_GetGlobalTime(PROG_CTRLIDX, frCycle, &frMacroTick) == E_OK)
    {
        SynchroStatus = EB_TRUE;
    }
    else
    {
        SynchroStatus = EB_FALSE;
    }
[!ELSE!]
    *frCycle = 0U;
    SynchroStatus = EB_TRUE;
[!ENDIF!]
    DBG_EB_ISNETWORKSYNCHRONIZED_EXIT(SynchroStatus);
return SynchroStatus;
}
/*-------------------------{end EB_IsNetworkSynchronized}-------------------------------*/

/*------------------------------------{EB_AllSlots}------------------------------------*/
void EB_AllSlots(void)
{
[!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY') and as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    [!IF "(as:modconf('FrSM')/FrSMGeneral/FrSMKeySlotOnlyModeEnable = 'true')"!]
    /* Request AllSlots mode */
    (void)FrSM_AllSlots(0U);
    [!ENDIF!]
[!ENDIF!]
}
/*------------------------------------{end EB_AllSlots}------------------------------------*/

/*----------------------------{EB_Com_Deactivate}------------------------------*/
void EB_Com_Deactivate(void)
{
    DBG_EB_COM_DEACTIVATE_ENTRY();
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]
    /* Stop FlexRay communication */
    (void)FrSM_RequestComMode(0U, COMM_NO_COMMUNICATION);
    [!ENDIF!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]
    /* Stop Can communication */
    (void)CanSM_RequestComMode(0U, COMM_NO_COMMUNICATION);
    [!ENDIF!]
    [!IF "(as:modconf('EB')/General/Protocol_Type = 'ETHERNET')"!]
    /* Stop Ethernet communication */
        [!IF "node:exists(as:modconf('EthSM'))"!]
    (void)EthSM_RequestComMode(0U, COMM_NO_COMMUNICATION);
        [!ELSE!]
    (void) TcpIp_RequestComMode(0U, TCPIP_STATE_OFFLINE);
        [!ENDIF!]
    [!ENDIF!]
[!ELSE!]
    /* Stop Can communication */
    (void)COM_ModeModify(COM_MODE_OFF);
[!ENDIF!]
    DBG_EB_COM_DEACTIVATE_EXIT();
}
/*-------------------------{end EB_Com_Deactivate}-------------------------------*/

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*----------------------------{EB_SetTesterAddress}------------------------------*/
void EB_SetTesterAddress(u16 ubTesterAddress)
{
    DBG_EB_SETTESTERADDRESS_ENTRY(ubTesterAddress);
    m_ubTesterAddress = ubTesterAddress;
    DBG_EB_SETTESTERADDRESS_EXIT();
}
/*-------------------------{end EB_SetTesterAddress}-----------------------------*/
[!ENDIF!]

[!IF "node:exists(as:modconf('Prog'))"!]
/*----------------------------{EB_Send_TPFrame}------------------------------*/
void EB_Send_TPFrame(u16 uwLen, u8 *paubUdsData)
{
    tTpMsgIdx   uMsgIdx = 0;
    tTpStatus   eStatus;
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
    u8          ubIdFound;
[!ENDIF!]

    DBG_EB_SEND_TPFRAME_ENTRY(uwLen, paubUdsData);

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
    ubIdFound = EB_GetMessageIdBySourceAddress(m_ubTesterAddress,&uMsgIdx);
[!ELSE!]
    /* Get the index of the Diag message */
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Physical'"!]
          [!IF "$MsgNB <= 1"!]
    uMsgIdx = TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!];
          [!ELSE!]
            [!ERROR "More than 1 physical Diag message, please use BM_SOURCE_ADDRESS_CHECK from BM !!!"!]
          [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]

[!ENDIF!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true' and node:exists(as:modconf('Prog'))"!]
    if (TRUE == ubIdFound)
[!ENDIF!]
    {
        /* Write the answer message data */
        eStatus = TP_SetMsgDataCopy(uMsgIdx, uwLen, paubUdsData);

        if(eStatus == TP_ERR_OK)
        {
            (void)TP_SendMsg(uMsgIdx);
        }
    }
    DBG_EB_SEND_TPFRAME_EXIT();
}
/*-------------------------{end EB_Send_TPFrame}-----------------------------*/
[!ENDIF!]

/*----------------------------{EB_SimulateRxRequest}------------------------------*/
void EB_SimulateRxRequest(u16 uwLen, u8 * paubUdsData, PduLengthType ulUdsDataSize, u8 ubWithResp)
{
[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    tTpMsgIdx   uMsgIdx = 0;
    u8          ubIdFound;
    u16         uwLen2;
    u16         uwLoopIndex;
    tUdsBoolean eUdsBoolean;
[!ENDIF!]
    DBG_EB_SIMULATERXREQUEST_ENTRY(uwLen, paubUdsData, ulUdsDataSize, ubWithResp);

    if (ubWithResp == TRUE)
    {
    /* Lock all TP channel to avoid responding to avoid receiving other requests if response to request has not been sent yet */
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Physical'"!]
        [!WS "8"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
        [!ENDIF!]
    [!ENDFOR!]
    }

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true' and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
    /* Memorize the TpMsgIdx in order to manage the next possible NRC78 */
    /* coming later with UDS_LongRequestResponseInd callback */

    ubIdFound = EB_GetMessageIdBySourceAddress(m_ubTesterAddress,&uMsgIdx);

    /* Store the pointer to Rx buff: call GetMsgData only to get the address of the received buffer */
    (void)TP_GetMsgData (uMsgIdx, &uwLen2, &m_paubTpBuffer);

    /* copy data to TP buffer */
    for (uwLoopIndex = 0; uwLoopIndex < uwLen; uwLoopIndex++)
    {
        m_paubTpBuffer[uwLoopIndex] = paubUdsData[uwLoopIndex];
    }

    eUdsBoolean = UDS_RxRequest(&uwLen, m_paubTpBuffer, ulUdsDataSize);

    if (UDS_NRC_78 == eUdsBoolean)
    {
        if (TRUE == ubIdFound)
        {
            m_ubTpMsgIdxNrc78 = uMsgIdx;
        }
        else
        {
            m_ubTpMsgIdxNrc78 = EB_NO_NRC_78;
        }

        [!IF "$FunctionalMsgExist = 1"!]
        /* Lock all functional channel during response pending to avoid any buffer problem */
            [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                [!WS "8"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                [!ENDIF!]
            [!ENDFOR!]
        [!ENDIF!]

        /* TP reception is locked while current long request is pending */
        (void)TP_RxEnable(m_ubTpMsgIdxNrc78, TP_RX_ENABLE_OFF);
    }
    else
    {
        /* copy back data to TP buffer to be send*/
        for (uwLoopIndex = 0; uwLoopIndex < uwLen; uwLoopIndex++)
        {
            paubUdsData[uwLoopIndex] = m_paubTpBuffer[uwLoopIndex];
        }
    }

[!ELSE!]
    (void)UDS_RxRequest(&uwLen, paubUdsData,ulUdsDataSize);
[!ENDIF!]
     DBG_EB_SIMULATERXREQUEST_EXIT();
}
/*-------------------------{end EB_SimulateRxRequest}-----------------------------*/

/*----------------------------{EB_StopSessionTimer}------------------------------*/
void EB_StopSessionTimer(void)
{
    DBG_EB_STOPSESSIONTIMER_ENTRY();

[!IF "node:exists(as:modconf('Uds'))"!]
    /* Stop the session Timer */
    UDS_StopSessionTimer();
[!ENDIF!]

    DBG_EB_STOPSESSIONTIMER_EXIT();
}
/*-------------------------{end EB_StopSessionTimer}-----------------------------*/

[!ENDCODE!]

