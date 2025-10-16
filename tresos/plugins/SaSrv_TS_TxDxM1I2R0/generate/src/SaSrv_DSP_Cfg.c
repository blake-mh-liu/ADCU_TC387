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
#include <Rte_SaSrv.h>
#include <SaSrv_Trace.h> /* DBG related macros for EB */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define SaSrv_START_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Array holding the configuration data for each configured security access level. */
CONST(SaSrv_DSP_SecurityLevelCfgType, SaSrv_CONST) SaSrv_DSP_SecurityLevelCfg[SASRV_DSP_NO_SECURITY_LEVELS] =
{
[!LOOP "SaSrvSecurityLevelConfig/*"!]
  [!VAR "SecurityLevelConfigName" = "node:name(.)"!]
  /* Security access level config [!"$SecurityLevelConfigName"!] */
  {
    /* Configuration flag to enable Static Seed */
    [!IF "./SaSrvStaticSeedEnable = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
    /* Configuration variable to store number of failed attempts of SecurityAccess sequences */
    [!"node:value(node:ref(./SaSrvSecurityLevelRef)/DcmDspSecurityNumAttDelay)"!]U
  },
[!ENDLOOP!]
};

#define SaSrv_STOP_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_NvMService_GetErrorStatus
(
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) ResultPtr,
        uint8                              CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_ENTRY(
                                                ResultPtr,
                                                CfgId
                                               );

  switch (CfgId)
  {
    [!LOOP "SaSrvSecurityLevelConfig/*"!][!//
    case [!"@index"!]U:
    {
      RetVal = Rte_Call_NvMService_[!"node:name(.)"!]_GetErrorStatus(ResultPtr);
      break;
    }

    [!ENDLOOP!][!//
    default:
    {
      break;
    }
  }

  DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_EXIT(RetVal);

  return RetVal;
}

FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_NvMService_WriteBlock
(
  P2CONST(void, AUTOMATIC, SaSrv_CONST) DataPtr,
  uint8                                 CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_ENTRY(
                                            DataPtr,
                                            CfgId
                                           );

  switch (CfgId)
  {
    [!LOOP "SaSrvSecurityLevelConfig/*"!][!//
    case [!"@index"!]U:
    {
      RetVal = Rte_Call_NvMService_[!"node:name(.)"!]_WriteBlock(DataPtr);
      break;
    }

    [!ENDLOOP!][!//
    default:
    {
      break;
    }
  }

  DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_EXIT(RetVal);

  return RetVal;
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
[!ENDSELECT!][!//
