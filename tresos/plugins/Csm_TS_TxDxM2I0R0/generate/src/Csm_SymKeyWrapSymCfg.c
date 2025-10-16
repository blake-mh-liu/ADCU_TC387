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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSymKeyWrapSym/CsmSymKeyWrapSymConfig/*[(CsmSymKeyWrapSymEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SymKeyWrapSymCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymConfig/*,'node:value(./CsmSymKeyWrapSymPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSymKeyWrapSymPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSymKeyWrapSymPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSymKeyWrapSymPrimitiveName)"!].h>
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
CONST(Csm_SymKeyWrapSymConfigType, CSM_CONST)
  Csm_SymKeyWrapSymConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSymKeyWrapSymEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSymKeyWrapSym)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSymKeyWrapSym_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSymKeyWrapSym) and (node:value(./CsmCallbackSymKeyWrapSym) != '')"!][!//
    &[!"node:value(./CsmCallbackSymKeyWrapSym)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSymKeyWrapSymPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSymKeyWrapSymPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSymKeyWrapSymPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSymKeyWrapSymPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSymKeyWrapSymInitConfiguration)"!]),
[!IF "(./CsmSymKeyWrapSymEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSymKeyWrapSymUsePriorities)"!][!//
[!IF "(./CsmSymKeyWrapSymUsePriorities) = 'true'"!][!//
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
typedef void Csm_SymKeyWrapSymCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

