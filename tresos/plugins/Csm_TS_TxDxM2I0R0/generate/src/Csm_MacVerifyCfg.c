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

[!VAR "ServiceEnabled" = "'false'"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmMacVerify/CsmMacVerifyConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmMacVerify/CsmMacVerifyConfig/*[(CsmMacVerifyEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_MacVerifyCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmMacVerify/CsmMacVerifyConfig/*,'node:value(./CsmMacVerifyPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmMacVerifyPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmMacVerifyPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmMacVerifyPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
#define CSM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0025, 1
 */
/* !LINKSTO CSM0535, 1
 */
CONST(Csm_MacVerifyConfigType, CSM_CONST)
  Csm_MacVerifyConfigurations[[!"num:i(count(as:modconf('Csm')/CsmMacVerify/CsmMacVerifyConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmMacVerify/CsmMacVerifyConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmMacVerifyEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackMacVerify)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmMacVerify_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackMacVerify) and (node:value(./CsmCallbackMacVerify) != '')"!][!//
    &[!"node:value(./CsmCallbackMacVerify)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmMacVerifyPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmMacVerifyPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmMacVerifyPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmMacVerifyPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmMacVerifyInitConfiguration)"!]),
[!IF "(./CsmMacVerifyEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmMacVerifyUsePriorities)"!][!//
[!IF "(./CsmMacVerifyUsePriorities) = 'true'"!][!//
    TRUE
[!ELSE!][!//
    FALSE
[!ENDIF!][!//
[!ENDIF!][!//
  },
[!ENDLOOP!][!//
};

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

[!IF "$ServiceEnabled != 'true'"!][!//
[!//
/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_MacVerifyCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

