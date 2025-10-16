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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractConfig/*[(CsmAsymPublicKeyExtractEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_AsymPublicKeyExtractCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractConfig/*,'node:value(./CsmAsymPublicKeyExtractPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!].h>
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
CONST(Csm_AsymPublicKeyExtractConfigType, CSM_CONST)
  Csm_AsymPublicKeyExtractConfigurations[[!"num:i(count(as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmAsymPublicKeyExtractEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackAsymPublicKeyExtract)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmAsymPublicKeyExtract_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackAsymPublicKeyExtract) and (node:value(./CsmCallbackAsymPublicKeyExtract) != '')"!][!//
    &[!"node:value(./CsmCallbackAsymPublicKeyExtract)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmAsymPublicKeyExtractPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmAsymPublicKeyExtractInitConfiguration)"!]),
[!IF "(./CsmAsymPublicKeyExtractEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmAsymPublicKeyExtractUsePriorities)"!][!//
[!IF "(./CsmAsymPublicKeyExtractUsePriorities) = 'true'"!][!//
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
typedef void Csm_AsymPublicKeyExtractCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

