[!/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('J1939TP_VARS_M'))"!][!/*
*/!][!VAR "J1939TP_VARS_M"="'true'"!][!/*

*** Mainfunction period Value ***
*/!][!VAR "J1939TpMainFunctionPeriodValue" = "(J1939TpGeneral/J1939TpMainFunctionPeriod)"!][!/*

*** CanFD Tx channels' count ***
*/!][!VAR "CanFDTxChannelCounter" = "num:i(count(as:modconf('J1939Tp')[1]/J1939TpConfiguration/eb-list::*[1]/J1939TpTxChannel/eb-list::*[node:existsAndTrue(J1939TpTxCanFDSupport)]))"!][!/*

*** CanFD Rx channels' count ***
*/!][!VAR "CanFDRxChannelCounter" = "num:i(count(as:modconf('J1939Tp')[1]/J1939TpConfiguration/eb-list::*[1]/J1939TpRxChannel/eb-list::*[node:existsAndTrue(J1939TpRxCanFDSupport)]))"!][!/*

*** J1939Tp General container ***
*/!][!VAR "T1" = "'0.750'"!][!/*        TIMER0 = 750ms
*/!][!VAR "T2" = "'1.250'"!][!/*        TIMER1 = 1250ms
*/!][!VAR "T3" = "'1.250'"!][!/*        TIMER2 = 1250ms
*/!][!VAR "T4" = "'1.050'"!][!/*        TIMER3 = 1050ms
*/!][!VAR "T5" = "'3.0'"!][!/*          TIMER5 = 3000ms
*/!][!VAR "Tr" = "'0.200'"!][!/*        RESPONSE TIME = 200ms
*/!][!IF "node:exists(J1939TpGeneral/J1939TpTBAMMinTimeout) "!][!/*
*/!][!VAR "Tbammin" = "(J1939TpGeneral/J1939TpTBAMMinTimeout)"!][!/*   BAM MINIMUM TIMER in ms
*/!][!ELSE!][!/*
*/!][!VAR "Tbammin" = "'0.050'"!][!/*   BAM MINIMUM TIMER = 50ms
*/!][!ENDIF!][!/*
*/!][!VAR "Th" = "'0.500'"!][!/*        HOLD TIME = 500ms
*/!][!VAR "Tbammax" = "'0.200'"!][!/*   BAM MAXIMUM TIMER = 200ms
*/!][!IF "node:exists(J1939TpGeneral/J1939TpTxConfirmationTimeOut) "!][!/*
*/!][!VAR "TxConfirmationTimeOut" = "(J1939TpGeneral/J1939TpTxConfirmationTimeOut)"!][!/*   TxConfirmation TimeOut in seconds
*/!][!ELSE!][!/*
*/!][!VAR "TxConfirmationTimeOut" = "(J1939TpGeneral/J1939TpMainFunctionPeriod)"!][!/*   Reliable TxConfirmation TimeOut isn't enabled
*/!][!ENDIF!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//