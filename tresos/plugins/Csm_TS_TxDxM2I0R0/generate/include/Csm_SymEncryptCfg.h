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


#ifndef CSM_SYMENCRYPTCFG_H
#define CSM_SYMENCRYPTCFG_H

[!VAR "ServiceEnabled" = "'false'"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*))"!][!//
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
#if (defined CSM_SYMENCRYPT_ENABLED)
#error CSM_SYMENCRYPT_ENABLED is already defined
#endif
[!IF "$ServiceEnabled = 'true'"!][!//
#define  CSM_SYMENCRYPT_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMENCRYPT_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMENCRYPT_RTE_INTERFACE_ENABLED)
#error CSM_SYMENCRYPT_RTE_INTERFACE_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Rte Interface for the SymEncrypt service. */
[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymEncrypt/CsmSymEncryptConfig/*[(CsmSymEncryptEnableRteInterface = 'true')]) > 0)"!][!//
#define  CSM_SYMENCRYPT_RTE_INTERFACE_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMENCRYPT_RTE_INTERFACE_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMENCRYPT_IMMEDIATE_RESTART_ENABLED)
#error CSM_SYMENCRYPT_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Macro indicating whether the immediate restart feature is enabled for the SymEncrypt service. */
[!IF "CsmSymEncrypt/CsmSymEncryptImmediateRestart = 'true'"!][!//
#define  CSM_SYMENCRYPT_IMMEDIATE_RESTART_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMENCRYPT_IMMEDIATE_RESTART_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_SYMENCRYPT_SYNCJOBPROCESSING_ENABLED)
#error CSM_SYMENCRYPT_SYNCJOBPROCESSING_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Synchronous Interface for the SymEncrypt service. */
[!IF "(CsmGeneral/CsmUseSyncJobProcessing = 'true')"!][!//
#define  CSM_SYMENCRYPT_SYNCJOBPROCESSING_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYMENCRYPT_SYNCJOBPROCESSING_ENABLED  STD_OFF
[!ENDIF!][!//

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO CSM0026, 1
 */
[!VAR "CsmSymEncryptConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*"!][!//
#if (defined [!"node:name(.)"!])
#error [!"node:name(.)"!] is already defined
#endif
#define [!"node:name(.)"!] (Csm_ConfigIdType)[!"num:i($CsmSymEncryptConfigIndex)"!]U
[!VAR "CsmSymEncryptConfigIndex" = "$CsmSymEncryptConfigIndex + 1"!][!//
[!ENDLOOP!][!//

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[type definitions]============================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO EB_CSM0074_01, 1
 */
/** \struct  Csm_SymEncryptConfigType
 ** \brief   Structure which contains the configuration for a symmetrical encryption
 **          service
 **//**
 ** \var     Csm_SymEncryptConfigType::CallbackFct
 ** \brief   A pointer to the callback function which has to be called when
 **          the current start, update, or finish computation is completed.
 **//**
 ** \var     Csm_SymEncryptConfigType::PrimitiveStartFct
 ** \brief   A pointer to the start function of the primitive.
 **//**
 ** \var     Csm_SymEncryptConfigType::PrimitiveUpdateFct
 ** \brief   A pointer to the update function of the primitive.
 **//**
 ** \var     Csm_SymEncryptConfigType::PrimitiveFinishFct
 ** \brief   A pointer to the finish function of the primitive.
 **//**
 ** \var     Csm_SymEncryptConfigType::PrimitiveMainFct
 ** \brief   A pointer to the main function of the primitive.
 **//**
 ** \var     Csm_SymEncryptConfigType::PrimitiveConfigPtr
 ** \brief   A pointer to the configuration object of the primitive.
 **//**
 ** \var     Csm_SymEncryptConfigType::CsmSymEncryptEnableRestart
 ** \brief   A constant to the enable cancel configuration object of the primitive.
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
 **//**
 ** \var     Csm_SymEncryptConfigType::CsmSymEncryptUsePriorities
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
    P2CONST(void,           AUTOMATIC, CSM_APPL_DATA) cfgPtr,
    P2CONST(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA) keyPtr,
    P2CONST(uint8,          AUTOMATIC, CSM_APPL_DATA) InitVectorPtr,
            uint32                                    InitVectorLength
  );

  /* !LINKSTO EB_CSM0702_01, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) plainTextPtr,
            uint32                            plainTextLength,
      P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) cipherTextPtr,
      P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) cipherTextLengthPtr
  );

  /* !LINKSTO EB_CSM0703_01, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveFinishFct)
  (
    P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) cipherTextPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) cipherTextLengthPtr
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

  CONST(boolean, CSM_CONST) CsmSymEncryptEnableRestart;
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
  CONST(boolean, CSM_CONST) CsmSymEncryptUsePriorities;
[!ENDIF!][!//
}
Csm_SymEncryptConfigType;

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external function declarations]==============================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!IF "((node:value(CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*[CsmSymEncryptEnableRteInterface = 'false']) > 0)) and (node:value(CsmSymEncrypt/CsmSymEncryptConfig/*/CsmCallbackSymEncrypt) != '')"!][!//
#define CSM_START_SEC_CODE
#include <MemMap.h>

[!ENDIF!][!//
[!//
[!VAR "CsmCallback" = "''"!][!//
[!//

[!LOOP "node:order(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*[node:exists(./CsmCallbackSymEncrypt)],'node:value(./CsmCallbackSymEncrypt)')"!][!//
[!IF "$CsmCallback != node:value(./CsmCallbackSymEncrypt)"!][!//
[!VAR "CsmCallback" = "node:value(./CsmCallbackSymEncrypt)"!][!//
/* !LINKSTO CSM0037, 1
 */

/* Deviation MISRA-1 <START> */
extern FUNC(Std_ReturnType, CSM_APPL_CODE) [!"node:value(./CsmCallbackSymEncrypt)"!]
(
  Csm_ReturnType Result
);
/* Deviation MISRA-1 <STOP> */

[!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "((node:value(as:modconf('Csm')/CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*[CsmSymEncryptEnableRteInterface = 'false']) > 0)) and (node:value(CsmSymEncrypt/CsmSymEncryptConfig/*/CsmCallbackSymEncrypt) != '')"!][!//
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
extern CONST(Csm_SymEncryptConfigType, CSM_CONST)
  Csm_SymEncryptConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*))"!]];

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_SYMENCRYPTCFG_H */

