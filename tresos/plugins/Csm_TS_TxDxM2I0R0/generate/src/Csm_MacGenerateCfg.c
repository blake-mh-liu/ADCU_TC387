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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmMacGenerate/CsmMacGenerateConfig/*[(CsmMacGenerateEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_MacGenerateCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateConfig/*,'node:value(./CsmMacGeneratePrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmMacGeneratePrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmMacGeneratePrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmMacGeneratePrimitiveName)"!].h>
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
CONST(Csm_MacGenerateConfigType, CSM_CONST)
  Csm_MacGenerateConfigurations[[!"num:i(count(as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmMacGenerateEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackMacGenerate)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmMacGenerate_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackMacGenerate) and (node:value(./CsmCallbackMacGenerate) != '')"!][!//
    &[!"node:value(./CsmCallbackMacGenerate)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmMacGeneratePrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmMacGeneratePrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmMacGeneratePrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmMacGeneratePrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmMacGenerateInitConfiguration)"!]),
[!IF "(./CsmMacGenerateEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmMacGenerateUsePriorities)"!][!//
[!IF "(./CsmMacGenerateUsePriorities) = 'true'"!][!//
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
typedef void Csm_MacGenerateCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

