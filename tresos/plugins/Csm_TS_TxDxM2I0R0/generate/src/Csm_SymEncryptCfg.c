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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymEncrypt/CsmSymEncryptConfig/*[(CsmSymEncryptEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SymEncryptCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*,'node:value(./CsmSymEncryptPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSymEncryptPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSymEncryptPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSymEncryptPrimitiveName)"!].h>
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
CONST(Csm_SymEncryptConfigType, CSM_CONST)
  Csm_SymEncryptConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSymEncryptEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSymEncrypt)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSymEncrypt_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSymEncrypt) and (node:value(./CsmCallbackSymEncrypt) != '')"!][!//
    &[!"node:value(./CsmCallbackSymEncrypt)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSymEncryptPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSymEncryptPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSymEncryptPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSymEncryptPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSymEncryptInitConfiguration)"!]),
[!IF "(./CsmSymEncryptEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSymEncryptUsePriorities)"!][!//
[!IF "(./CsmSymEncryptUsePriorities) = 'true'"!][!//
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
typedef void Csm_SymEncryptCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

