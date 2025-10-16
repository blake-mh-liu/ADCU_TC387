/**
 * \file
 *
 * \brief AUTOSAR SaSrv
 *
 * This file contains the implementation of the AUTOSAR
 * module SaSrv.
 *
 * \version 1.2.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule:  11.1
 *    "Conversions shall not be performed between a pointer to a function and any other type.
 *
 *   Reason:
 *   The debug and trace macro must accept any type of function pointer thus a cast to a specific
 *   function pointer is necessary.
 */

/*================================================================================================*/

[!AUTOSPACING!][!//
[!SELECT "as:modconf('SaSrv')"!][!//

/*==================[includes]====================================================================*/

#include <SaSrv_DSP_Cfg.h>
#include <SaSrv_DSP_COTS_Cfg.h>
#include <Rte_SaSrv.h>
#include <SaSrv_Trace.h> /* DBG related macros for EB */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_COTS_MACGenerateService
(
  P2CONST(uint8,  AUTOMATIC, SaSrv_CONST    ) DataPtr,
          uint32                              DataLength,
    P2VAR(uint8,  AUTOMATIC, SaSrv_APPL_DATA) MacPtr,
    P2VAR(uint32, AUTOMATIC, SaSrv_APPL_DATA) MacLengthPtr,
          uint8                               CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_COTS_MACGENERATESERVICE_ENTRY(
                                         DataPtr,
                                         DataLength,
                                         MacPtr,
                                         MacLengthPtr,
                                         CfgId
                                        );

  switch (CfgId)
  {
    [!LOOP "SaSrvSecurityLevelConfig/*"!][!//
      [!VAR "Indentation" = "string-length(node:name(.))"!]
    case [!"@index"!]U:
    {
      RetVal = Rte_Call_CsmMacGenerate_[!"node:name(.)"!]_MacGenerate(DataPtr,
      [!WS "$Indentation + 53"!]                                      DataLength,
      [!WS "$Indentation + 53"!]                                      MacPtr,
      [!WS "$Indentation + 53"!]                                      MacLengthPtr
      [!WS "$Indentation + 52"!]                                      );
      break;
    }
    [!ENDLOOP!][!//
    default:
    {
      break;
    }
  }

  DBG_SASRV_DSP_COTS_MACGENERATESERVICE_EXIT(RetVal);

  return RetVal;
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
[!ENDSELECT!][!//
