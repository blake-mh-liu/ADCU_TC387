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


#ifndef CSM_RANDOMGENERATECFG_H
#define CSM_RANDOMGENERATECFG_H

[!VAR "ServiceEnabled" = "'false'"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*))"!][!//
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
#if (defined CSM_RANDOMGENERATE_ENABLED)
#error CSM_RANDOMGENERATE_ENABLED is already defined
#endif
[!IF "$ServiceEnabled = 'true'"!][!//
#define  CSM_RANDOMGENERATE_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_RANDOMGENERATE_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_RANDOMGENERATE_RTE_INTERFACE_ENABLED)
#error CSM_RANDOMGENERATE_RTE_INTERFACE_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Rte Interface for the RandomGenerate service. */
[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmRandomGenerate/CsmRandomGenerateConfig/*[(CsmRandomGenerateEnableRteInterface = 'true')]) > 0)"!][!//
#define  CSM_RANDOMGENERATE_RTE_INTERFACE_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_RANDOMGENERATE_RTE_INTERFACE_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_RANDOMGENERATE_IMMEDIATE_RESTART_ENABLED)
#error CSM_RANDOMGENERATE_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Macro indicating whether the immediate restart feature is enabled for the RandomGenerate service. */
[!IF "CsmRandomGenerate/CsmRandomGenerateImmediateRestart = 'true'"!][!//
#define  CSM_RANDOMGENERATE_IMMEDIATE_RESTART_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_RANDOMGENERATE_IMMEDIATE_RESTART_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED)
#error CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED is already defined
#endif
/** \brief Macro indicating whether there is an Synchronous Interface for the RandomGenerate service. */
[!IF "(CsmGeneral/CsmUseSyncJobProcessing = 'true')"!][!//
#define  CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED  STD_OFF
[!ENDIF!][!//

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO CSM0026, 1
 */
[!VAR "CsmRandomGenerateConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*"!][!//
#if (defined [!"node:name(.)"!])
#error [!"node:name(.)"!] is already defined
#endif
#define [!"node:name(.)"!] (Csm_ConfigIdType)[!"num:i($CsmRandomGenerateConfigIndex)"!]U
[!VAR "CsmRandomGenerateConfigIndex" = "$CsmRandomGenerateConfigIndex + 1"!][!//
[!ENDLOOP!][!//

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[type definitions]============================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
/* !LINKSTO EB_CSM0074_01, 1
 */
/** \struct  Csm_RandomGenerateConfigType
 ** \brief   Structure which contains the configuration for a random generate
 **          service
 **//**
 ** \var     Csm_RandomGenerateConfigType::CallbackFct
 ** \brief   A pointer to the callback function which has to be called when
 **          the current computation is completed.
 **//**
 ** \var     Csm_RandomGenerateConfigType::PrimitiveFct
 ** \brief   A pointer to the function of the primitive.
 **//**
 ** \var     Csm_RandomGenerateConfigType::PrimitiveMainFct
 ** \brief   A pointer to the main function of the primitive.
 **//**
 ** \var     Csm_RandomGenerateConfigType::PrimitiveConfigPtr
 ** \brief   A pointer to the configuration object of the primitive.
 **//**
 ** \var     Csm_RandomGenerateConfigType::CsmRandomGenerateEnableRestart
 ** \brief   A constant to the enable cancel configuration object of the primitive.
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
 **//**
 ** \var     Csm_RandomGenerateConfigType::CsmRandomGenerateUsePriorities
 ** \brief   A constant to the enable priority handling of the primitive.
[!ENDIF!][!//
 **/
typedef struct
{
  /* !LINKSTO CSM0032, 1
   */
  Csm_CallbackType CallbackFct;
  /* !LINKSTO CSM0704, 1
   */
  P2FUNC(Csm_ReturnType, CSM_APPL_CODE, PrimitiveFct)
  (
    P2CONST(void,   AUTOMATIC, CSM_APPL_DATA) cfgPtr,
      P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) resultPtr,
            uint32                            resultLength
  );

  /* !LINKSTO CSM0773, 1
  */
  P2FUNC(void, CSM_APPL_CODE, PrimitiveMainFct)
  (
    void
  );

  /* !LINKSTO CSM0733, 1
   */
  P2CONST(void, AUTOMATIC, CSM_APPL_CONST) PrimitiveConfigPtr;

  CONST(boolean, CSM_CONST) CsmRandomGenerateEnableRestart;
[!IF "node:exists(CsmGeneral/CsmUsePriorities) and node:value(CsmGeneral/CsmUsePriorities) = 'true'"!][!//
  CONST(boolean, CSM_CONST) CsmRandomGenerateUsePriorities;
[!ENDIF!][!//
}
Csm_RandomGenerateConfigType;

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external function declarations]==============================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!IF "((node:value(CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*[CsmRandomGenerateEnableRteInterface = 'false']) > 0)) and (node:value(CsmRandomGenerate/CsmRandomGenerateConfig/*/CsmCallbackRandomGenerate) != '')"!][!//
#define CSM_START_SEC_CODE
#include <MemMap.h>

[!ENDIF!][!//
[!//
[!VAR "CsmCallback" = "''"!][!//
[!//

[!LOOP "node:order(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*[node:exists(./CsmCallbackRandomGenerate)],'node:value(./CsmCallbackRandomGenerate)')"!][!//
[!IF "$CsmCallback != node:value(./CsmCallbackRandomGenerate)"!][!//
[!VAR "CsmCallback" = "node:value(./CsmCallbackRandomGenerate)"!][!//
/* !LINKSTO CSM0037, 1
 */

/* Deviation MISRA-1 <START> */
extern FUNC(Std_ReturnType, CSM_APPL_CODE) [!"node:value(./CsmCallbackRandomGenerate)"!]
(
  Csm_ReturnType Result
);
/* Deviation MISRA-1 <STOP> */

[!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "((node:value(as:modconf('Csm')/CsmGeneral/CsmRteUsage) != 'true') or (count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*[CsmRandomGenerateEnableRteInterface = 'false']) > 0)) and (node:value(CsmRandomGenerate/CsmRandomGenerateConfig/*/CsmCallbackRandomGenerate) != '')"!][!//
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
extern CONST(Csm_RandomGenerateConfigType, CSM_CONST)
  Csm_RandomGenerateConfigurations[[!"num:i(count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*))"!]];

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_RANDOMGENERATECFG_H */

