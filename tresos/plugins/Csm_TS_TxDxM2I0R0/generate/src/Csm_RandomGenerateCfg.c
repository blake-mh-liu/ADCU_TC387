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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmRandomGenerate/CsmRandomGenerateConfig/*[(CsmRandomGenerateEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_RandomGenerateCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*,'node:value(./CsmRandomGeneratePrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmRandomGeneratePrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmRandomGeneratePrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmRandomGeneratePrimitiveName)"!].h>
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
CONST(Csm_RandomGenerateConfigType, CSM_CONST)
  Csm_RandomGenerateConfigurations[[!"num:i(count(as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmRandomGenerate/CsmRandomGenerateConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmRandomGenerateEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackRandomGenerate)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmRandomGenerate_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackRandomGenerate) and (node:value(./CsmCallbackRandomGenerate) != '')"!][!//
    &[!"node:value(./CsmCallbackRandomGenerate)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmRandomGeneratePrimitiveName)"!],
    &Cry_[!"node:value(./CsmRandomGeneratePrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmRandomGenerateInitConfiguration)"!]),
[!IF "(./CsmRandomGenerateEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmRandomGenerateUsePriorities)"!][!//
[!IF "(./CsmRandomGenerateUsePriorities) = 'true'"!][!//
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
typedef void Csm_RandomGenerateCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

