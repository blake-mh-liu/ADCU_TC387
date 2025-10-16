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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmRandomSeed/CsmRandomSeedConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmRandomSeed/CsmRandomSeedConfig/*[(CsmRandomSeedEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_RandomSeedCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmRandomSeed/CsmRandomSeedConfig/*,'node:value(./CsmRandomSeedPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmRandomSeedPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmRandomSeedPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmRandomSeedPrimitiveName)"!].h>
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
CONST(Csm_RandomSeedConfigType, CSM_CONST)
  Csm_RandomSeedConfigurations[[!"num:i(count(as:modconf('Csm')/CsmRandomSeed/CsmRandomSeedConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmRandomSeed/CsmRandomSeedConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmRandomSeedEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackRandomSeed)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmRandomSeed_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackRandomSeed) and (node:value(./CsmCallbackRandomSeed) != '')"!][!//
    &[!"node:value(./CsmCallbackRandomSeed)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmRandomSeedPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmRandomSeedPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmRandomSeedPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmRandomSeedPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmRandomSeedInitConfiguration)"!]),
[!IF "(./CsmRandomSeedEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmRandomSeedUsePriorities)"!][!//
[!IF "(./CsmRandomSeedUsePriorities) = 'true'"!][!//
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
typedef void Csm_RandomSeedCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

