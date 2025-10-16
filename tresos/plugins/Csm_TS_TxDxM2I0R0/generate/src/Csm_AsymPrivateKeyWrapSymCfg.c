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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymConfig/*[(CsmAsymPrivateKeyWrapSymEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_AsymPrivateKeyWrapSymCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymConfig/*,'node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!].h>
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
CONST(Csm_AsymPrivateKeyWrapSymConfigType, CSM_CONST)
  Csm_AsymPrivateKeyWrapSymConfigurations[[!"num:i(count(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmAsymPrivateKeyWrapSymEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackAsymPrivateKeyWrapSym)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmAsymPrivateKeyWrapSym_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackAsymPrivateKeyWrapSym) and (node:value(./CsmCallbackAsymPrivateKeyWrapSym) != '')"!][!//
    &[!"node:value(./CsmCallbackAsymPrivateKeyWrapSym)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmAsymPrivateKeyWrapSymPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmAsymPrivateKeyWrapSymInitConfiguration)"!]),
[!IF "(./CsmAsymPrivateKeyWrapSymEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmAsymPrivateKeyWrapSymUsePriorities)"!][!//
[!IF "(./CsmAsymPrivateKeyWrapSymUsePriorities) = 'true'"!][!//
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
typedef void Csm_AsymPrivateKeyWrapSymCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

