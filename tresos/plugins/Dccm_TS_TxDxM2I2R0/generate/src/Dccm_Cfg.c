/***************************************************************************
 *
 * \file Dccm_Cfg.c
 *
 * \brief Dccm configuration
 *
 * Copyright 2020 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears in a single function.
 *
 * Reason:
 * The current file serves as a template for code generation, and the actual file used by the
 * source code is generated prior to compilation based on the module's configuration. Because the
 * function is in a file that is treated as static code, and the script that generates the constant
 * will not work there, it is not technically possible to move the script code that generates the
 * definition of the constant in the single function that uses the constant.
 */

/*==================[inclusions]=================================================================*/

#include <Dccm_Internal.h>
#include <Dccm_Cfg.h>

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

#define DCCM_START_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

/* Initialize global arrays holding the values of each TxPduId/RxPduId for all configured functional
 * and physical communication protocols.
 */

/* Array of physical addresses */
/* Deviation MISRAC2012-1 <START> */
[!IF "num:i(count(DccmPhysicalPduIds/eb-list::*)) = '0'"!][!//
CONST(Dccm_PduIdsConfigurationType,DCCM_CONST) Dccm_PhysicalPduIdsArray[1U] =
{
  [!INDENT "2"!][!//
    /* EcuId, TxPduId, RxPduId, PduRTxPduId */
    { 0U, 0U, 0U, 0U},
  [!ENDINDENT!][!//
};
[!ELSE!][!//
CONST(Dccm_PduIdsConfigurationType,DCCM_CONST) Dccm_PhysicalPduIdsArray[[!"num:i(count(DccmPhysicalPduIds/eb-list::*))"!]U] =
{
  [!INDENT "2"!][!//
    [!LOOP "util:distinct(node:order(DccmPhysicalPduIds/eb-list::*, 'DccmPhysicalEcuId'))"!][!//
      [!VAR "EcuId" = "num:integer(DccmPhysicalEcuId)"!][!//
      [!VAR "TxPduId" = "num:integer(DccmPhysicalTxPduId)"!][!//
      [!VAR "RxPduId" = "num:integer(DccmPhysicalRxPduId)"!][!//
      /* EcuId, TxPduId, RxPduId, PduRTxPduId */[!//
      [!IF "node:exists(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*[PduRSrcPdu/PduRSrcPduRef = node:current()/DccmPhysicalTxPduIdRef])"!]
        { [!"$EcuId"!]U, [!"$TxPduId"!]U, [!"$RxPduId"!]U, [!"as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*[PduRSrcPdu/PduRSrcPduRef = node:current()/DccmPhysicalTxPduIdRef][1]/PduRSrcPdu/PduRSourcePduHandleId"!]U},[!//
      [!ELSE!]
        [!ERROR!] Pdu [!"node:current()/DccmPhysicalTxPduIdRef"!] is not referenced by any PduRSrcPdu [!ENDERROR!]
      [!ENDIF!]
    [!ENDLOOP!][!//
  [!ENDINDENT!][!//
};
[!ENDIF!][!//
/* Deviation MISRAC2012-1 <STOP> */

/* Array of functional addresses */
/* Deviation MISRAC2012-1 <START> */
[!IF "num:i(count(DccmFunctionalPduIds/eb-list::*)) = '0'"!][!//
CONST(Dccm_PduIdsConfigurationType,DCCM_CONST) Dccm_FunctionalPduIdsArray[1U] =
{
  [!INDENT "2"!][!//
    /* EcuId, TxPduId, RxPduId, PduRTxPduId */
    { 0U, 0U, 0U, 0U},
  [!ENDINDENT!][!//
};
[!ELSE!][!//
CONST(Dccm_PduIdsConfigurationType,DCCM_CONST) Dccm_FunctionalPduIdsArray[[!"num:i(count(DccmFunctionalPduIds/eb-list::*))"!]U] =
{
  [!INDENT "2"!][!//
    [!LOOP "util:distinct(node:order(DccmFunctionalPduIds/eb-list::*, 'DccmFunctionalEcuId'))"!][!//
      [!VAR "EcuId" = "num:integer(DccmFunctionalEcuId)"!][!//
      [!VAR "TxPduId" = "num:integer(DccmFunctionalTxPduId)"!][!//
      [!VAR "RxPduId" = "num:integer(DccmFunctionalRxPduId)"!][!//
      /* EcuId, TxPduId, RxPduId, PduRTxPduId */[!//
      [!IF "node:exists(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*[PduRSrcPdu/PduRSrcPduRef = node:current()/DccmFunctionalTxPduIdRef])"!]
        { [!"$EcuId"!]U, [!"$TxPduId"!]U, [!"$RxPduId"!]U, [!"as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*[PduRSrcPdu/PduRSrcPduRef = node:current()/DccmFunctionalTxPduIdRef][1]/PduRSrcPdu/PduRSourcePduHandleId"!]U},[!//
      [!ELSE!]
        [!ERROR!] Pdu [!"node:current()/DccmFunctionalTxPduIdRef"!] is not referenced by any PduRSrcPdu [!ENDERROR!]
      [!ENDIF!]
    [!ENDLOOP!][!//
  [!ENDINDENT!][!//
};
[!ENDIF!][!//
/* Deviation MISRAC2012-1 <STOP> */

#define DCCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

/*==================[end of file]================================================================*/
