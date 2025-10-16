/**
 * \file
 *
 * \brief AUTOSAR CanTrcv
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTrcv.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2015 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=================================================================*/
#include <TSAutosar.h>
#include <Can_GeneralTypes.h>
#include <CanTrcv.h>
#include <CanIf_Cbk.h>
#include <CanIf.h>

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/
CanTrcv_TrcvWakeupReasonType CanTrcv_WUReason = CANTRCV_WU_BY_BUS;

/*==================[internal data]==============================================================*/
static boolean CanTrcv_IsInit = FALSE;
static boolean CanTrcv_WakeFlag = FALSE;
static CanTrcv_TrcvModeType CanTrcv_TrcvMode = CANTRCV_TRCVMODE_STANDBY;
static CanTrcv_TrcvWakeupModeType CanTrcv_TrcvWakeupMode = CANTRCV_WUMODE_ENABLE;

/*==================[external function definitions]==============================================*/

FUNC(void, CANTRCV_CODE) CanTrcv_Init(void)
{
    CanTrcv_IsInit = TRUE;
}

FUNC(void, CANTRCV_CODE) CanTrcv_MainFunction(void)
{
    if (CanTrcv_IsInit)
    {
    }
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType OpMode)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if (CanTrcv_IsInit)
    {
        CanTrcv_TrcvMode = OpMode;
        CanIf_TrcvModeIndication(Transceiver, OpMode);
#if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
        if (OpMode == CANTRCV_TRCVMODE_NORMAL)
        {
            CanIf_ConfirmPnAvailability(Transceiver);
        }
#endif /* #if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType* OpMode)
{
    Std_ReturnType RetVal = E_NOT_OK;
    TS_PARAM_UNUSED(Transceiver);
    if (CanTrcv_IsInit)
    {
        *OpMode = CanTrcv_TrcvMode;
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetBusWuReason(uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason)
{
    Std_ReturnType RetVal = E_NOT_OK;
    TS_PARAM_UNUSED(Transceiver);
    if (CanTrcv_IsInit)
    {
        *reason = CanTrcv_WUReason;
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetWakeupMode(uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
    Std_ReturnType RetVal = E_NOT_OK;
    TS_PARAM_UNUSED(Transceiver);
    if (CanTrcv_IsInit)
    {
        CanTrcv_TrcvWakeupMode = TrcvWakeupMode;
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvWufFlag(uint8 Transceiver)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if (CanTrcv_IsInit)
    {
        CanTrcv_WakeFlag = FALSE;
        if (CanTrcv_TrcvMode == CANTRCV_TRCVMODE_NORMAL)
        {
            CanTrcv_TrcvMode = CANTRCV_TRCVMODE_STANDBY;
        }
#if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
        CanIf_ClearTrcvWufFlagIndication(Transceiver);
#endif /* #if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeFlag(uint8 Transceiver)
{
    Std_ReturnType RetVal = E_NOT_OK;
    
    if (CanTrcv_IsInit)
    {
        if ((CanTrcv_WakeFlag)&&(CanTrcv_TrcvWakeupMode == CANTRCV_WUMODE_ENABLE))
        {
#if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
            CanIf_CheckTrcvWakeFlagIndication(Transceiver);
#endif /* #if (CANTRCV_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
        }
        RetVal = E_OK;
    }
    return RetVal;
}

FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeup(uint8 Transceiver)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if (CanTrcv_IsInit)
    {
        if ((CanTrcv_WakeFlag)&&(CanTrcv_TrcvWakeupMode == CANTRCV_WUMODE_ENABLE))
        {
            RetVal = E_OK;
        }
    }
    return RetVal;
}
