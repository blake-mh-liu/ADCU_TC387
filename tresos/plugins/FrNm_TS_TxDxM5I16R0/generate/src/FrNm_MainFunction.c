/**
 * \file
 *
 * \brief AUTOSAR FrNm
 *
 * This file contains the implementation of the AUTOSAR
 * module FrNm.
 *
 * \version 5.16.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*===============================[includes]=================================*/
[!INCLUDE "../../generate_macros/FrNm_Macros.m"!][!//
[!CALL "GetSynchronizedPncShutdownEnabled"!]
[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmMultiCoreSupport)) and
      (node:existsAndTrue($SynchronizedPncShutdownEnabled))
    "!]
#define FRNM_NO_CFGCLASSMIX_REQUIRED
#ifndef FRNM_NO_PBCFG_REQUIRED
#define FRNM_NO_PBCFG_REQUIRED
#endif
#include <FrNm_Int.h>          /* FrNm internal interface */
[!ELSE!]
#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */
/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT
[!ENDIF!] [!/* [!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmMultiCoreSupport)) and
             *       (node:existsAndTrue($SynchronizedPncShutdownEnabled)) and
             *       ($PncShutdownActiveChannels > 0)"!]
             */!]

/*===========================[macro definitions]============================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*=====================[external constants]=================================*/

/*=====================[internal constants]=================================*/

/*=======================[external data]====================================*/

/*=======================[internal data]====================================*/

/*=====================[external functions definitions]=====================*/

[!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGeneral/FrNmMultiCoreSupport)) and
      (node:existsAndTrue($SynchronizedPncShutdownEnabled))
     "!]
#define FRNM_START_SEC_CODE
#include <FrNm_MemMap.h>
FUNC(void, FRNM_CODE) FrNm_RequestSynchronizedPncShutdown_Nm_To_FrNm_RcvFnct (void)
{
  Nm_PnSyncShutdown_Nm_To_BusNm_DataType data;

  while (SchM_Receive_FrNm_FrNm_RequestSynchronizedPncShutdown_Nm_To_FrNm_DataGet(&data) == SCHM_E_OK)
  {
    (void) FrNm_RequestSynchronizedPncShutdown(data.Channel, data.PncId);
  }
}
#define FRNM_STOP_SEC_CODE
#include <FrNm_MemMap.h>
[!ENDIF!][!//


/*=====================[external Non API function definitions]==============*/

/*=====================[internal functions definitions]=====================*/

/*==============================[end of file]===============================*/
