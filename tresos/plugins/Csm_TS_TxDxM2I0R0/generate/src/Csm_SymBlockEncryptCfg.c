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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymBlockEncrypt/CsmSymBlockEncryptConfig/*[(CsmSymBlockEncryptEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SymBlockEncryptCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptConfig/*,'node:value(./CsmSymBlockEncryptPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSymBlockEncryptPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSymBlockEncryptPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSymBlockEncryptPrimitiveName)"!].h>
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
CONST(Csm_SymBlockEncryptConfigType, CSM_CONST)
  Csm_SymBlockEncryptConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSymBlockEncryptEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSymBlockEncrypt)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSymBlockEncrypt_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSymBlockEncrypt) and (node:value(./CsmCallbackSymBlockEncrypt) != '')"!][!//
    &[!"node:value(./CsmCallbackSymBlockEncrypt)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSymBlockEncryptPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSymBlockEncryptPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSymBlockEncryptPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSymBlockEncryptPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSymBlockEncryptInitConfiguration)"!]),
[!IF "(./CsmSymBlockEncryptEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSymBlockEncryptUsePriorities)"!][!//
[!IF "(./CsmSymBlockEncryptUsePriorities) = 'true'"!][!//
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
typedef void Csm_SymBlockEncryptCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

