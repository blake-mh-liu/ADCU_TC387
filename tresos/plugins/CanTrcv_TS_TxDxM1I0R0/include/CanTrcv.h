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

#if (!defined CANTRCV_H)
#define CANTRCV_H
/*==================[inclusions]=================================================================*/
#include <TSAutosar.h>
#include <Can_GeneralTypes.h>
#include <CanTrcv_Cfg.h>

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

extern FUNC(void, CANTRCV_CODE) CanTrcv_Init(void);

extern FUNC(void, CANTRCV_CODE) CanTrcv_MainFunction(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType OpMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType* OpMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetBusWuReason(uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetWakeupMode(uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvWufFlag(uint8 Transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeFlag(uint8 Transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeup(uint8 Transceiver);

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

#endif /* if !defined( CANTRCV_H ) */
/*==================[end of file]================================================================*/
