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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymKeyExtract/CsmSymKeyExtractConfig/*[(CsmSymKeyExtractEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SymKeyExtractCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*,'node:value(./CsmSymKeyExtractPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSymKeyExtractPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSymKeyExtractPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSymKeyExtractPrimitiveName)"!].h>
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
CONST(Csm_SymKeyExtractConfigType, CSM_CONST)
  Csm_SymKeyExtractConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSymKeyExtractEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSymKeyExtract)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSymKeyExtract_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSymKeyExtract) and (node:value(./CsmCallbackSymKeyExtract) != '')"!][!//
    &[!"node:value(./CsmCallbackSymKeyExtract)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSymKeyExtractPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSymKeyExtractPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSymKeyExtractPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSymKeyExtractPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSymKeyExtractInitConfiguration)"!]),
[!IF "(./CsmSymKeyExtractEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSymKeyExtractUsePriorities)"!][!//
[!IF "(./CsmSymKeyExtractUsePriorities) = 'true'"!][!//
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
typedef void Csm_SymKeyExtractCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

