/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 8.8 (required)
 *   "An external object or function shall be declared in one and only one file."
 *
 *   Reason:
 *   For each provided Csm service, the used callback functions are declared independent from the
 *   callbacks used for other services. The redundant redeclaration of callback functions are caused
 *   by certain test configurations, which use the same callback for
 *   different Csm services.
 */


#ifndef CSM_SYMKEYEXTRACTCFG_H
#define CSM_SYMKEYEXTRACTCFG_H

[!VAR "ServiceEnabled" = "'false'"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

#include <Csm_Cfg.h>
#include <Csm_Types.h>

/*==================[macros]======================================================================*/

/* !LINKSTO CSM0015, 1
 */
#if (defined CSM_SYMKEYEXTRACT_ENABLED)
#error CSM_SYMKEYEXTRACT_ENABLED is already defined
#endif
[!IF "$ServiceEnabled = 'true'"!][!//
#define  CSM_SYMKEYEXTRACT_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMKEYEXTRACT_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMKEYEXTRACT_RTE_INTERFACE_ENABLED)
#error CSM_SYMKEYEXTRACT_RTE_INTERFACE_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Rte Interface for the SymKeyExtract service. */
[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymKeyExtract/CsmSymKeyExtractConfig/*[(CsmSymKeyExtractEnableRteInterface = 'true')]) > 0)"!][!//
#define  CSM_SYMKEYEXTRACT_RTE_INTERFACE_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMKEYEXTRACT_RTE_INTERFACE_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED)
#error CSM_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Macro indicating whether the immediate restart feature is enabled for the SymKeyExtract service. */
[!IF "CsmSymKeyExtract/CsmSymKeyExtractImmediateRestart = 'true'"!][!//
#define  CSM_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED)
#error CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Synchronous Interface for the SymKeyExtract service. */
[!IF "(CsmGeneral/CsmUseSyncJobProcessing = 'true')"!][!//
#define  CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED  STD_OFF
[!ENDIF!][!//

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO CSM0026, 1
 */
[!VAR "CsmSymKeyExtractConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*"!][!//
#if (defined [!"node:name(.)"!])
#error [!"node:name(.)"!] is already defined
#endif
#define [!"node:name(.)"!] (Csm_ConfigIdType)[!"num:i($CsmSymKeyExtractConfigIndex)"!]U
[!VAR "CsmSymKeyExtractConfigIndex" = "$CsmSymKeyExtractConfigIndex + 1"!][!//
[!ENDLOOP!][!//

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[type definitions]============================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO EB_CSM0074_01, 1
 */
/** \struct  Csm_SymKeyExtractConfigType
 ** \brief   Structure which contains the configuration for a symmetrical key extraction
 **          service
 **//**
 ** \var     Csm_SymKeyExtractConfigType::CallbackFct
 ** \brief   A pointer to the callback function which has to be called when
 **          the current start, update, or finish computation is completed.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::PrimitiveStartFct
 ** \brief   A pointer to the start function of the primitive.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::PrimitiveUpdateFct
 ** \brief   A pointer to the update function of the primitive.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::PrimitiveFinishFct
 ** \brief   A pointer to the finish function of the primitive.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::PrimitiveMainFct
 ** \brief   A pointer to the main function of the primitive.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::PrimitiveConfigPtr
 ** \brief   A pointer to the configuration object of the primitive.
 **//**
 ** \var     Csm_SymKeyExtractConfigType::CsmSymKeyExtractEnableRestart
 ** \brief   A constant to the enable cancel configuration object of the primitive.
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
 **//**
 ** \var     Csm_SymKeyExtractConfigType::CsmSymKeyExtractUsePriorities
 ** \brief   A constant to the enable priority handling of the primitive.
[!ENDIF!][!//
 **/
typedef struct
{
  /* !LINKSTO CSM0032, 1
   */
  Csm_CallbackType CallbackFct;
  /* !LINKSTO CSM0701, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void, AUTOMATIC, CSM_APPL_DATA) cfgPtr
  );

  /* !LINKSTO EB_CSM0702_01, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) dataPtr,
            uint32                            dataLength
  );

  /* !LINKSTO EB_CSM0703_01, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveFinishFct)
  (
    P2VAR(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA) keyPtr
  );

  /* !LINKSTO CSM0773, 1
  */
  P2FUNC(void, CSM_APPL_CODE, PrimitiveMainFct)
  (
    void
  );

  /* !LINKSTO CSM0732, 1
   */
  P2CONST(void, AUTOMATIC, CSM_APPL_CONST) PrimitiveConfigPtr;

  CONST(boolean, CSM_CONST) CsmSymKeyExtractEnableRestart;
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
  CONST(boolean, CSM_CONST) CsmSymKeyExtractUsePriorities;
[!ENDIF!][!//
}
Csm_SymKeyExtractConfigType;

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external function declarations]==============================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!IF "((node:value(CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*[CsmSymKeyExtractEnableRteInterface = 'false']) > 0)) and (node:value(CsmSymKeyExtract/CsmSymKeyExtractConfig/*/CsmCallbackSymKeyExtract) != '')"!][!//
#define CSM_START_SEC_CODE
#include <MemMap.h>

[!ENDIF!][!//
[!//
[!VAR "CsmCallback" = "''"!][!//
[!//

[!LOOP "node:order(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*[node:exists(./CsmCallbackSymKeyExtract)],'node:value(./CsmCallbackSymKeyExtract)')"!][!//
[!IF "$CsmCallback != node:value(./CsmCallbackSymKeyExtract)"!][!//
[!VAR "CsmCallback" = "node:value(./CsmCallbackSymKeyExtract)"!][!//
/* !LINKSTO CSM0037, 1
 */

/* Deviation MISRA-1 <START> */
extern FUNC(Std_ReturnType, CSM_APPL_CODE) [!"node:value(./CsmCallbackSymKeyExtract)"!]
(
  Csm_ReturnType Result
);
/* Deviation MISRA-1 <STOP> */

[!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "((node:value(as:modconf('Csm')/CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*[CsmSymKeyExtractEnableRteInterface = 'false']) > 0)) and (node:value(CsmSymKeyExtract/CsmSymKeyExtractConfig/*/CsmCallbackSymKeyExtract) != '')"!][!//
#define CSM_STOP_SEC_CODE
#include <MemMap.h>

[!ENDIF!][!//
[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external constants]==========================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
#define CSM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0025, 1
 */
extern CONST(Csm_SymKeyExtractConfigType, CSM_CONST)
  Csm_SymKeyExtractConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*))"!]];

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_SYMKEYEXTRACTCFG_H */

