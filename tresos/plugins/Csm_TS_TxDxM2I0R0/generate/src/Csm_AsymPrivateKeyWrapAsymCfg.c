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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymConfig/*[(CsmAsymPrivateKeyWrapAsymEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_AsymPrivateKeyWrapAsymCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymConfig/*,'node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!].h>
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
CONST(Csm_AsymPrivateKeyWrapAsymConfigType, CSM_CONST)
  Csm_AsymPrivateKeyWrapAsymConfigurations[[!"num:i(count(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmAsymPrivateKeyWrapAsymEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackAsymPrivateKeyWrapAsym)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmAsymPrivateKeyWrapAsym_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackAsymPrivateKeyWrapAsym) and (node:value(./CsmCallbackAsymPrivateKeyWrapAsym) != '')"!][!//
    &[!"node:value(./CsmCallbackAsymPrivateKeyWrapAsym)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapAsymPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmAsymPrivateKeyWrapAsymInitConfiguration)"!]),
[!IF "(./CsmAsymPrivateKeyWrapAsymEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmAsymPrivateKeyWrapAsymUsePriorities)"!][!//
[!IF "(./CsmAsymPrivateKeyWrapAsymUsePriorities) = 'true'"!][!//
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
typedef void Csm_AsymPrivateKeyWrapAsymCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

