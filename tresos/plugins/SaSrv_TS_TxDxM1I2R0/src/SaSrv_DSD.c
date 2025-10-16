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

/*==================[includes]====================================================================*/

#include <SaSrv_DSP.h>
#include <SaSrv_DSD.h>
#include <Rte_SaSrv.h>
#include <SaSrv_Trace.h> /* DBG related macros for EB */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/** \brief Returns the security level configuration index
 **
 ** Returns the index in the context array for the provided security level
 **
 ** \param[in]  Level     Security level.
 **
 ** \return Security level configuration index.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(uint8, SaSrv_CODE) SaSrv_DSD_Level2CfgIdx
(
  uint8 Level
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/* !LINKSTO swdd.DSD.GetSeed, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_GetSeed
(
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Seed,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           Level
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8          CfgId  = SaSrv_DSD_Level2CfgIdx(Level);

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSD_GETSEED_ENTRY(
                              OpStatus,
                              Seed,
                              ErrorCode,
                              Level
                             );

  if ((Seed != NULL_PTR) && (ErrorCode != NULL_PTR))
  {
    /* !LINKSTO swdd.DSD.GetSeed.OpStatusOk, 1 */
    if (OpStatus == DCM_INITIAL)
    {
      RetVal = SaSrv_DSP_GetSeed(
                                  OpStatus,
                                  Seed,
                                  ErrorCode,
                                  CfgId
                                );
    }
    else if (
             (OpStatus == DCM_PENDING) ||
             (OpStatus == DCM_CANCEL )
            )
    {
      /* !LINKSTO swdd.DSD.GetSeed.InvalidData.ReportDet.InvalidData, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSEED, SASRV_INVALID_DATA);

      /* !LINKSTO swdd.DSD.GetSeed.InvalidData.Return.NotOk, 1 */
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      RetVal     = E_NOT_OK;
    }
    else
    {
      if (OpStatus == DCM_FORCE_RCRRP_OK)
      {
        /* !LINKSTO swdd.DSD.GetSeed.DCM_FORCE_RCRRP_OK.Return.Ok, 1 */
        *ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
        RetVal     = E_OK;
      }
      else
      {
        /* !LINKSTO swdd.DSD.GetSeed.InvalidData.ReportDet.InvalidData2, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSEED, SASRV_INVALID_DATA);

        /* !LINKSTO swdd.DSD.GetSeed.InvalidData.Return.NotOk2, 1 */
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        RetVal     = E_NOT_OK;
      }
    }
  }
  else
  {
    if (ErrorCode != NULL_PTR)
    {
      /* !LINKSTO swdd.DSD.GetSeed.NULL_PTR.ReportDet.ParamPointer, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSEED, SASRV_PARAM_POINTER);

      /* !LINKSTO swdd.DSD.GetSeed.NULL_PTR.Return.NotOk, 1 */
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      RetVal     = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO swdd.DSD.GetSeed.NULL_PTR.ReportDet.ParamPointer2, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSEED, SASRV_PARAM_POINTER);

      /* !LINKSTO swdd.DSD.GetSeed.NULL_PTR.Return.NotOk2, 1 */
      RetVal     = E_NOT_OK;
    }
  }

  DBG_SASRV_DSD_GETSEED_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSD.CompareKey, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_CompareKey
(
  P2CONST(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Key,
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           Level
)
{
  Std_ReturnType RetVal   = E_NOT_OK;
  uint8          CfgId    = SaSrv_DSD_Level2CfgIdx(Level);

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSD_COMPAREKEY_ENTRY(
                                 Key,
                                 OpStatus,
                                 ErrorCode,
                                 Level
                                );

  if ((Key != NULL_PTR) && (ErrorCode != NULL_PTR))
  {
    /* !LINKSTO swdd.DSD.CompareKey.OpStatusOk, 1 */
    if (OpStatus == DCM_INITIAL)
    {
      RetVal = SaSrv_DSP_CompareKey(
                                    Key,
                                    OpStatus,
                                    ErrorCode,
                                    CfgId
                                   );
    }
    else if (
             (OpStatus == DCM_PENDING) ||
             (OpStatus == DCM_CANCEL )
            )
    {
      /* !LINKSTO swdd.DSD.CompareKey.InvalidData.ReportDet.InvalidData, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_COMPAREKEY, SASRV_INVALID_DATA);

      /* !LINKSTO swdd.DSD.CompareKey.InvalidData.Return.NotOk, 1 */
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      RetVal     = E_NOT_OK;
    }
    else
    {
      if (OpStatus == DCM_FORCE_RCRRP_OK)
      {
        /* !LINKSTO swdd.DSD.CompareKey.DCM_FORCE_RCRRP_OK.Return.Ok, 1 */
        *ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
        RetVal     = E_OK;
      }
      else
      {
        /* !LINKSTO swdd.DSD.CompareKey.InvalidData.ReportDet.InvalidData2, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_COMPAREKEY, SASRV_INVALID_DATA);

        /* !LINKSTO swdd.DSD.CompareKey.InvalidData.Return.NotOk2, 1 */
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        RetVal     = E_NOT_OK;
      }
    }
  }
  else
  {
    if (ErrorCode != NULL_PTR)
    {
      /* !LINKSTO swdd.DSD.CompareKey.NULL_PTR.ReportDet.ParamPointer, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_COMPAREKEY, SASRV_PARAM_POINTER);

      /* !LINKSTO swdd.DSD.CompareKey.NULL_PTR.Return.NotOk, 1 */
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      RetVal     = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO swdd.DSD.CompareKey.NULL_PTR.ReportDet.ParamPointer2, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_COMPAREKEY, SASRV_PARAM_POINTER);

      /* !LINKSTO swdd.DSD.CompareKey.NULL_PTR.Return.NotOk2, 1 */
      RetVal = E_NOT_OK;
    }
  }

  DBG_SASRV_DSD_COMPAREKEY_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSD.SetSecurityAttemptCounter, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_SetSecurityAttemptCounter
(
  SaSrv_Dcm_OpStatusType OpStatus,
  uint8                  AttemptCounter,
  uint8                  Level
)
{
  Std_ReturnType RetVal   = E_NOT_OK;
  uint8          CfgId    = SaSrv_DSD_Level2CfgIdx(Level);

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_ENTRY(
                                                OpStatus,
                                                AttemptCounter,
                                                Level
                                               );

  /* !LINKSTO swdd.DSD.SetSecurityAttemptCounter.OpStatusOk, 2 */
  if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
  {
    RetVal = SaSrv_DSP_SetSecurityAttemptCounter(
                                                  OpStatus,
                                                  AttemptCounter,
                                                  CfgId
                                                );
  }
  else
  {
    if (OpStatus == DCM_FORCE_RCRRP_OK)
    {
      /* !LINKSTO swdd.DSD.SetSecurityAttemptCounter.DCM_FORCE_RCRRP_OK.Return.Ok, 1 */
      RetVal = E_OK;
    }
    else
    {
      /* !LINKSTO swdd.DSD.SetSecurityAttemptCounter.InvalidData.ReportDet.InvalidData, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_SETSECURITYATTEMPTCOUNTER, SASRV_INVALID_DATA);

      /* !LINKSTO swdd.DSD.SetSecurityAttemptCounter.InvalidData.Return.NotOk, 1 */
      RetVal = E_NOT_OK;
    }
  }

  DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSD.GetSecurityAttemptCounter, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_GetSecurityAttemptCounter
(
        SaSrv_Dcm_OpStatusType             OpStatus,
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) AttemptCounter,
        uint8                              Level
)
{
  Std_ReturnType RetVal   = E_NOT_OK;
  uint8          CfgId    = SaSrv_DSD_Level2CfgIdx(Level);

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_ENTRY(
                                                OpStatus,
                                                AttemptCounter,
                                                Level
                                               );

  if (AttemptCounter != NULL_PTR)
  {
    /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.OpStatusOk, 1 */
    if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
    {
      RetVal = SaSrv_DSP_GetSecurityAttemptCounter(
                                                    OpStatus,
                                                    AttemptCounter,
                                                    CfgId
                                                  );
    }
    else
    {
      if (OpStatus == DCM_FORCE_RCRRP_OK)
      {
        /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.DCM_FORCE_RCRRP_OK.Return.Ok, 1 */
        RetVal = E_OK;
      }
      else
      {
        /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.InvalidData.ReportDet.InvalidData, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSECURITYATTEMPTCOUNTER, SASRV_INVALID_DATA);

        /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.InvalidData.Return.NotOk, 1 */
        RetVal = E_NOT_OK;
      }
    }
  }
  else
  {
    /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.NULL_PTR.ReportDet.ParamPointer, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_GETSECURITYATTEMPTCOUNTER, SASRV_PARAM_POINTER);

    /* !LINKSTO swdd.DSD.GetSecurityAttemptCounter.NULL_PTR.Return.NotOk, 1 */
    RetVal = E_NOT_OK;
  }

  DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_EXIT(RetVal);

  return RetVal;
}

#if (SASRV_HANDLE_ENTROPY == STD_ON)
/* !LINKSTO swdd.DSD.Init, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSD_Init
(
  void
)
{
  DBG_SASRV_DSD_INIT_ENTRY();

  SaSrv_DSP_Init();

  DBG_SASRV_DSD_INIT_EXIT();
}

/* !LINKSTO swdd.DSD.DeInit, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSD_DeInit
(
  void
)
{
  DBG_SASRV_DSD_DEINIT_ENTRY();

  SaSrv_DSP_DeInit();

  DBG_SASRV_DSD_DEINIT_EXIT();
}
#endif /* #if (SASRV_HANDLE_ENTROPY == STD_ON) */

/* !LINKSTO swdd.DSD.MainFunction, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSD_MainFunction
(
  void
)
{
  DBG_SASRV_DSD_MAINFUNCTION_ENTRY();

  SaSrv_DSP_MainFunction();

  DBG_SASRV_DSD_MAINFUNCTION_EXIT();
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

static FUNC(uint8, SaSrv_CODE) SaSrv_DSD_Level2CfgIdx
(
  uint8 Level
)
{
  uint8 CfgId;

  /* This function cannot be called with an invalid security level
   * as it's selected from the configuration */
  /* CHECK: NOPARSE */
  for(CfgId = 0U; CfgId < SASRV_NO_SECURITY_LEVELS; CfgId++)
  {
    if (SaSrv_DSD_SecurityLevelCfg[CfgId].level == Level)
    {
      break;
    }
  }
  /* CHECK: PARSE */
  return CfgId;
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*================================================================================================*/

/*==================[end of file]=================================================================*/
