/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP                                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Prg.c                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.0 BL3                */
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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (advisory)
 *   A pointer parameter in a function prototype should be declared as pointer to const
 *   if the pointer is not used to modify the addressed object.
 *
 *   Reason:
 *   The MISRA rule is not violated. This pointer will be used once the function is completed by customer.
 */


/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Prj.h"
#include <APP_Trace.h>                /* Dbg related macros for EB */
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

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/* Interrupt context */
NCS_PRI_VAR u8 m_ubItContext;

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
/* - Public Functions                                                            */

/*--------------------------{APP_InterruptEnable}--------------------------------------*/
void APP_InterruptEnable (u8 ebStatus)
{
    DBG_APP_INTERRUPTENABLE_ENTRY(ebStatus);

[!IF "node:exists(as:modconf('Platforms'))"!]
    BoardEnableInterrupts();
[!ELSE!]
    /* Implement here a treatment for a critical section exit. */
    /* Interrupts must be resumed. */
    m_ubItContext = ebStatus;
[!ENDIF!]

    DBG_APP_INTERRUPTENABLE_EXIT();
}
/*--------------------------{end APP_InterruptEnable}----------------------------------*/

/*--------------------------{APP_InterruptDisable}--------------------------------------*/
u8 APP_InterruptDisable (void)
{
    u8 eContext = 0U;

    DBG_APP_INTERRUPTDISABLE_ENTRY();

[!IF "node:exists(as:modconf('Platforms'))"!]
    BoardDisableInterrupts();
[!ELSE!]
    /* Implement here a treatment for a critical section entry. */
    /* Interrupts must be suspended. */
    eContext = m_ubItContext;
[!ENDIF!]

    DBG_APP_INTERRUPTDISABLE_EXIT(eContext);
    return (eContext);
}
/*--------------------------{end APP_InterruptDisable}----------------------------------*/


/*--------------------------{APP_Init}--------------------------------------*/
void APP_Init (void)
{
    DBG_APP_INIT_ENTRY();
    DBG_APP_INIT_EXIT();
}
/*--------------------------{end APP_Init}----------------------------------*/





/*--------------------------{APP_Manage}--------------------------------------*/
void APP_Manage (void)
{
    DBG_APP_MANAGE_ENTRY();
    DBG_APP_MANAGE_EXIT();
}
/*--------------------------{end APP_Manage}----------------------------------*/

[!IF "node:exists(as:modconf('Com'))"!][!AUTOSPACING!]
/*--------------------------{APP_ComNAsInd}--------------------------------------*/
void APP_ComNAsInd (tComFrameIdx uFrameIdx)
{
    DBG_APP_COMNASIND_ENTRY(uFrameIdx);

    OSC_PARAM_UNUSED(uFrameIdx);

    DBG_APP_COMNASIND_EXIT();
}
/*--------------------------{end APP_ComNAsInd}----------------------------------*/

/*--------------------------{APP_ComTxTimeoutInd}--------------------------------------*/
tComStatus APP_ComTxTimeoutInd (tComFrameIdx uFrameIdx)
{
    DBG_APP_COMTXTIMEOUTIND_ENTRY(uFrameIdx);

    OSC_PARAM_UNUSED(uFrameIdx);

    DBG_APP_COMTXTIMEOUTIND_EXIT(COM_ERR_OK);

    return COM_ERR_OK;
}
/*--------------------------{end APP_ComTxTimeoutInd}----------------------------------*/

/*--------------------------{APP_ComTxConf}--------------------------------------*/
void APP_ComTxConf (tComFrameIdx uFrameIdx)
{
    DBG_APP_COMTXCONF_ENTRY(uFrameIdx);

    OSC_PARAM_UNUSED(uFrameIdx);

    DBG_APP_COMTXCONF_EXIT();
}
/*--------------------------{end APP_ComTxConf}----------------------------------*/

/*--------------------------{APP_ComModeModifyExtension}--------------------------------------*/
void APP_ComModeModifyExtension (tComMode eCurMode)
{
    DBG_APP_COMMODEMODIFYEXTENSION_ENTRY(eCurMode);

    OSC_PARAM_UNUSED(eCurMode);

    DBG_APP_COMMODEMODIFYEXTENSION_EXIT();
}
/*--------------------------{end APP_ComModeModifyExtension}----------------------------------*/

/*--------------------------{APP_ComBackInd}--------------------------------------*/
void APP_ComBackInd (tComMonNodeIdx uNodeIdx)
{
    DBG_APP_COMBACKIND_ENTRY(uNodeIdx);

    switch (uNodeIdx)
    {
    [!LOOP "as:modconf('Com')/Monitoring/*"!][!AUTOSPACING!]
        case COM_NODE_IDX_[!"name(.)"!]:
        break;
    [!ENDLOOP!][!AUTOSPACING!]
    default:
        /* Nothing to do */
        break;
    }
    DBG_APP_COMBACKIND_EXIT();

}
/*--------------------------{end APP_ComBackInd}----------------------------------*/

/*--------------------------{APP_ComLossInd}--------------------------------------*/
void APP_ComLossInd (tComMonNodeIdx uNodeIdx)
{
    DBG_APP_COMLOSSIND_ENTRY(uNodeIdx);

    switch (uNodeIdx)
    {
    [!LOOP "as:modconf('Com')/Monitoring/*"!][!AUTOSPACING!]
        case COM_NODE_IDX_[!"name(.)"!]:
        break;
    [!ENDLOOP!][!AUTOSPACING!]

    default:
        /* Nothing to do */
        break;
    }
     DBG_APP_COMLOSSIND_EXIT();
}
/*--------------------------{end APP_ComLossInd}----------------------------------*/

/*--------------------------{APP_ComTxFrameInd}--------------------------------------*/
void APP_ComTxFrameInd (tComFrameIdx uFrameIdx)
{
     DBG_APP_COMTXFRAMEIND_ENTRY(uFrameIdx);

    OSC_PARAM_UNUSED(uFrameIdx);

     DBG_APP_COMTXFRAMEIND_EXIT();
}
/*--------------------------{end APP_ComTxFrameInd}----------------------------------*/

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
    [!IF "CbkOnRxFrame_callback = 'APP'"!][!AUTOSPACING!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
        [!IF "CbkOnRxFrame != ''"!][!AUTOSPACING!]
            [!VAR "TMP_CBK" = "CbkOnRxFrame"!][!AUTOSPACING!]
            [!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
            [!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
                [!IF "CbkOnRxFrame = $TMP_CBK"!][!AUTOSPACING!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
                    [!ENDIF!][!AUTOSPACING!]
                [!ENDIF!][!AUTOSPACING!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
            [!ELSE!][!AUTOSPACING!]
/*--------------------------{[!"CbkOnRxFrame"!]}--------------------------------------*/
u8 [!"CbkOnRxFrame"!](tComFrameIdx uFrameIdx)
{
    OSC_PARAM_UNUSED(uFrameIdx);

    return COM_RX_IND_CHECK_OK;
}
/*--------------------------{end [!"CbkOnRxFrame"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
    [!IF "CbkOnRxData_callback = 'APP'"!][!AUTOSPACING!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
        [!IF "CbkOnRxData != ''"!][!AUTOSPACING!]
            [!VAR "TMP_CBK" = "CbkOnRxData"!][!AUTOSPACING!]
            [!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
            [!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
                [!IF "CbkOnRxData = $TMP_CBK"!][!AUTOSPACING!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
                    [!ENDIF!][!AUTOSPACING!]
                [!ENDIF!][!AUTOSPACING!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
            [!ELSE!]
/*--------------------------{[!"CbkOnRxData"!]}--------------------------------------*/
void [!"CbkOnRxData"!](tComFrameIdx uFrameIdx)
{
    OSC_PARAM_UNUSED(uFrameIdx);
}
/*--------------------------{end [!"CbkOnRxData"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
    [!IF "CbkOnRxInvalidDLC_callback = 'APP'"!][!AUTOSPACING!]
        [!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
        [!IF "CbkOnRxInvalidDLC != ''"!][!AUTOSPACING!]
            [!VAR "TMP_CBK" = "CbkOnRxInvalidDLC"!][!AUTOSPACING!]
            [!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
            [!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
            [!LOOP "as:modconf('Com')[1]/ComConfig/*/Frames/*[Direction = 'Reception']"!][!AUTOSPACING!]
                [!IF "CbkOnRxInvalidDLC = $TMP_CBK"!][!AUTOSPACING!]
                    [!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
                    [!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
                        [!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
                    [!ENDIF!][!AUTOSPACING!]
                [!ENDIF!][!AUTOSPACING!]
            [!ENDLOOP!]
            [!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
            [!ELSE!]
/*--------------------------{[!"CbkOnRxInvalidDLC"!]}--------------------------------------*/
void [!"CbkOnRxInvalidDLC"!](tComFrameIdx uFrameIdx)
{
    OSC_PARAM_UNUSED(uFrameIdx);
}
/*--------------------------{end [!"CbkOnRxInvalidDLC"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

/*--------------------------{APP_COM_MonNodeStatusInd}--------------------------------------*/
void APP_COM_MonNodeStatusInd(tComMonNodeIdx uNodeIdx, tComMonStatus eFrameStatus)
{
    DBG_APP_COM_MONNODESTATUSIND_ENTRY(uNodeIdx, eFrameStatus);

    OSC_PARAM_UNUSED(uNodeIdx);
    OSC_PARAM_UNUSED(eFrameStatus);

    DBG_APP_COM_MONNODESTATUSIND_EXIT();
}
/*--------------------------{end APP_COM_MonNodeStatusInd}----------------------------------*/
[!ENDIF!][!/* End of IF "node:exists(as:modconf('COM'))" */!][!AUTOSPACING!]

[!IF "node:exists(as:modconf('Can'))"!]
/*--------------------------{CAN_BusOffInd}--------------------------------------*/
void CAN_BusOffInd (void)
{
     DBG_CAN_BUSOFFIND_ENTRY();

    /* Set CAN HW to BusOff and unlock upper layer (TP) with CAN_TxFail function */
#if (CAN_CTRL_NB>1)
    CAN_BusOff(NM_CAN_BUS_IDX);
#else
    CAN_BusOff();
#endif

    /* Set COM to BUS_OFF: CAN is desactivated */
    (void) COM_ModeModify(COM_MODE_BUS_OFF);

    /* Set COM to BUS_ON: CAN is activated */
    (void) COM_ModeModify(COM_MODE_BUS_ON);

    /* Set CAN HW to BusOn */
#if (CAN_CTRL_NB>1)
    CAN_BusOn(NM_CAN_BUS_IDX);
#else
    CAN_BusOn();
#endif

    DBG_CAN_BUSOFFIND_EXIT();
}
/*--------------------------{end CAN_BusOffInd}----------------------------------*/
[!ENDIF!]

[!/* Check CAN exists and has multi bit Timing arrow */!]
[!IF "as:modconf('Can')/Controller_Configuration/*[1]/MultiBaudRate_APPCallback = 'true'"!]
    [!NOCODE!]
    [!/* Check if multi baudrate configured in CAN */!]
    [!VAR "MULTIBAUDRATE" = "0"!]
    [!FOR "CANCtrlCfg" = "1" TO "count(as:modconf('Can')/Controller_Configuration/*)" STEP "1"!]
        [!IF "num:i(count(as:modconf('Can')/Controller_Configuration/*[position()=$CANCtrlCfg]/Bit_Timing_configuration/*)) > 1"!]
            [!VAR "MULTIBAUDRATE" = "1"!]
        [!ENDIF!]
    [!ENDFOR!]
    [!ENDNOCODE!]
    [!IF "$MULTIBAUDRATE = 1"!]
/*--------------------------{CAN_GetBaudRateIdx}--------------------------------------*/
u8 CAN_GetBaudRateIdx (CTRLIDX_VOID)
{
    u8 eIndex = 0U;
    
    DBG_CAN_GETBAUDRATEIDX_ENTRY();

    DBG_CAN_GETBAUDRATEIDX_EXIT(eIndex);
    return (eIndex);
}
/*--------------------------{end CAN_GetBaudRateIdx}----------------------------------*/
    [!ENDIF!]
[!ENDIF!][!/* End of If CAN present in Stack */!]
[!IF "node:exists(as:modconf('Uds'))"!]
/*--------------------------{UDS_P2AboutToExpireInd}--------------------------------------*/
void UDS_P2AboutToExpireInd(void)
{
    DBG_UDS_P2ABOUTTOEXPIREIND_ENTRY();
    DBG_UDS_P2ABOUTTOEXPIREIND_EXIT();
}
/*--------------------------{end UDS_P2AboutToExpireInd}----------------------------------*/
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Uds')/Service/*"!][!AUTOSPACING!]
[!IF "Callback_Origin = 'APP'"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/*--------------------------{[!"Callback"!]}--------------------------------------*/
/* Deviation MISRA-1 */
 tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
 {
     OSC_PARAM_UNUSED(puwLen);
     OSC_PARAM_UNUSED(aubUdsData);

     return UDS_ACK;
 }
/*--------------------------{end [!"Callback"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Uds')/Service_DID/*"!][!AUTOSPACING!]
[!IF "Callback_Origin = 'APP'"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service_DID/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/*--------------------------{[!"Callback"!]}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    *puwLen = 3U;
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end [!"Callback"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Uds')/Routine_Control/*"!][!AUTOSPACING!]
[!IF "Callback_Origin = 'APP'"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Routine_Control/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/*--------------------------{[!"Callback"!]}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end [!"Callback"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "as:modconf('Uds')/Service_OBD/*"!][!AUTOSPACING!]
[!IF "Callback_Origin = 'APP'"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service_OBD/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/*--------------------------{[!"Callback"!]}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end [!"Callback"!]}----------------------------------*/
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]


/*--------------------------{APP_UdsSessionStatusInd}--------------------------------------*/
void APP_UdsSessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{
    DBG_APP_UDSSESSIONSTATUSIND_ENTRY(eUdsNewSessType, eUdsOldSessType, eUdsChangingCause);

    OSC_PARAM_UNUSED(eUdsOldSessType);
    OSC_PARAM_UNUSED(eUdsChangingCause);
    OSC_PARAM_UNUSED(eUdsNewSessType);

    DBG_APP_UDSSESSIONSTATUSIND_EXIT();
}
/*--------------------------{end APP_UdsSessionStatusInd}----------------------------------*/
[!ENDIF!][!/* End of IF "node:exists(as:modconf('Uds'))" */!][!AUTOSPACING!]

/*--------------------------{APP_TpDataBufferEmptyInd}--------------------------------------*/
void APP_TpDataBufferEmptyInd (tTpMsgIdx uMsgIdx)
{
    DBG_APP_TPDATABUFFEREMPTYIND_ENTRY(uMsgIdx);

    OSC_PARAM_UNUSED(uMsgIdx);

    DBG_APP_TPDATABUFFEREMPTYIND_EXIT();
}
/*--------------------------{end APP_TpDataBufferEmptyInd}----------------------------------*/

/*--------------------------{APP_TpTxConf}--------------------------------------*/
void APP_TpTxConf (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    DBG_APP_TPTXCONF_ENTRY(uMsgIdx, ebStatus);

    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);

    DBG_APP_TPTXCONF_EXIT();
}
/*--------------------------{end APP_TpTxConf}----------------------------------*/

/*--------------------------{APP_TpRxInd}--------------------------------------*/
void APP_TpRxInd (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    DBG_APP_TPRXIND_ENTRY(uMsgIdx, ebStatus);

    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);

    DBG_APP_TPRXIND_EXIT();
}
/*--------------------------{end APP_TpRxInd}----------------------------------*/

/*--------------------------{APP_TpRxEnableInd}--------------------------------------*/
void APP_TpRxEnableInd (tTpMsgIdx uMsgIdx, tTpRxEnable uRxEnable)
{
    DBG_APP_TPRXENABLEIND_ENTRY(uMsgIdx, uRxEnable);

    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(uRxEnable);

    DBG_APP_TPRXENABLEIND_EXIT();
}
/*--------------------------{end APP_TpRxEnableInd}----------------------------------*/

[!IF "node:exists(as:modconf('Uds'))"!]
/*-------------------------------------------------------------------------------*/

/*--------------------------{APP_GetUdsDataBufferInd}--------------------------------------*/
/* Deviation MISRA-1 */
void APP_GetUdsDataBufferInd(u16 *uwLen, u8 *paubUdsData, tTpMsgIdx uMsgIdx, tUdsStatus eStatusRxReq)
{
    DBG_APP_GETUDSDATABUFFERIND_ENTRY(uwLen, paubUdsData, uMsgIdx, eStatusRxReq);

    OSC_PARAM_UNUSED(uwLen);
    OSC_PARAM_UNUSED(paubUdsData);
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(eStatusRxReq);

    DBG_APP_GETUDSDATABUFFERIND_EXIT();
}

/*--------------------------{end APP_GetUdsDataBufferInd}----------------------------------*/
[!ENDIF!]

[!IF "node:exists(as:modconf('Can'))"!]
#if (CAN_WAKE_UP_DETECTION  == CAN_WAKE_UP_ACTIVATE)
/*--------------------------{APP_CanWakeUpInd}--------------------------------------*/
void APP_CanWakeUpInd (void)
{
    DBG_APP_CANWAKEUPIND_ENTRY();
    DBG_APP_CANWAKEUPIND_EXIT();
}
/*--------------------------{end APP_CanWakeUpInd}----------------------------------*/
#endif
/*--------------------------{APP_CanCtrlModeErrorInd}--------------------------------------*/
void APP_CanCtrlModeErrorInd (tCanErrors uErrorID)
{
    DBG_APP_CANCTRLMODEERRORIND_ENTRY(uErrorID);

    OSC_PARAM_UNUSED(uErrorID);

    DBG_APP_CANCTRLMODEERRORIND_EXIT();
}
/*--------------------------{end APP_CanCtrlModeErrorInd}----------------------------------*/
[!ENDIF!]

/*--------------------------{NCS_SdfVariableCoherencyError}--------------------------------------*/
void NCS_SdfVariableCoherencyError(u16 uwParam)
{
    DBG_NCS_SDFVARIABLECOHERENCYERROR_ENTRY(uwParam);

    OSC_PARAM_UNUSED(uwParam);
    
    DBG_NCS_SDFVARIABLECOHERENCYERROR_EXIT();
}
/*--------------------------{end NCS_SdfVariableCoherencyError}----------------------------------*/

/*--------------------------{NCS_SdfVariableRangeError}--------------------------------------*/
void NCS_SdfVariableRangeError(u16 uwParam)
{
    DBG_NCS_SDFVARIABLERANGEERROR_ENTRY(uwParam);
    
    OSC_PARAM_UNUSED(uwParam);
    
    DBG_NCS_SDFVARIABLERANGEERROR_EXIT();
}
/*--------------------------{end NCS_SdfVariableRangeError}----------------------------------*/


