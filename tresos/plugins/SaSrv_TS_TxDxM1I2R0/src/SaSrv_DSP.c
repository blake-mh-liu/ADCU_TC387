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

#include <SaSrv_DSP_COTS_Cfg.h>

#include <Rte_SaSrv.h>
#include <SaSrv_Trace.h> /* DBG related macros for EB */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

#if (SASRV_HANDLE_ENTROPY == STD_ON)
/** \brief Handles the entropy of the random number generator
 **
 ** This function shall be used whenever the random number generator
 ** is not able to generate a new seed due to entropy exhaustion.
 **
 ** \return Standard Return Code
 ** \RetVal E_OK     Seed was refreshed successfully.
 ** \RetVal E_NOT_OK Seed was not refreshed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_HandleEntropy
(
  void
);
#endif

/** \brief Get the NvM status for written false attempts counter
 **
 ** Handles the error status after the NvM_WriteBlock() for false attempts counter
 **
 ** \param[in]  CfgId     Index in the security levels configuration array.
 **
 ** \return Standard Return Code
 ** \RetVal E_OK     Seed was refreshed successfully.
 ** \RetVal E_NOT_OK Seed was not refreshed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetStatusWriteFalseAttemptsCounter
(
  uint8 CfgId
);

/** \brief Get the false attempts counter from NvM
 **
 ** Reads the value of the false attempts counter local mirror from NvM
 **
 ** \param[in]  CfgId     Index in the security levels configuration array.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(void, SaSrv_CODE) SaSrv_DSP_ReadFalseAttemptsCounter
(
  uint8 CfgId
);

/** \brief Generate a 16 byte long random number
 **
 ** This function generates a 16 byte long random number.
 **
 ** \param[in]  CfgId     Index in the security levels configuration array.
 **
 ** \return Standard Return Code
 ** \RetVal E_OK     No Error.
 ** \RetVal E_NOT_OK Generation of the random number failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_RandomGenerateService
(
  uint8 CfgId
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define SaSrv_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Context information for all security levels */
VAR(SaSrv_DSP_SecurityLevelCtxType, SaSrv_VAR) SaSrv_DSP_SecurityLevelCtx[SASRV_DSP_NO_SECURITY_LEVELS];

#define SaSrv_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal data]===============================================================*/

#define SaSrv_START_SEC_VAR_INIT_8
#include <SaSrv_MemMap.h>

/* When using SHE all the input/output buffers must be provided in a 16-byte aligned
 * memory location(address ending in 00) otherwise the operation will fail.
 * This is achieved by using target specific #pragma in the above memory section.
 */

/** \brief Buffer used to store the server random number, generated with Csm_RandomGenerate() */
static VAR(uint8, SaSrv_VAR) SaSrv_DSP_InBuf[SASRV_DSP_NO_SECURITY_LEVELS][SASRV_RNG_SIZE] = SASRV_DSP_INIT_BUFFER;

/** \brief Buffer used to store the server key, generated with Csm_MacGenerate() */
static VAR(uint8, SaSrv_VAR) SaSrv_DSP_AUXBuf[SASRV_DSP_NO_SECURITY_LEVELS][SASRV_MAC_SIZE] = SASRV_DSP_INIT_BUFFER;

#define SaSrv_STOP_SEC_VAR_INIT_8
#include <SaSrv_MemMap.h>

#if (SASRV_HANDLE_ENTROPY == STD_ON)
#define SaSrv_START_SEC_VAR_CLEARED_8
#include <SaSrv_MemMap.h>

/** \brief Buffer used to store the entropy which is received via a getter API and set with
 *         via Csm key management APIs (RandomSeed)
 */
static VAR(uint8, SaSrv_VAR) SaSrv_DSP_Entropy[SASRV_ENTROPY_SIZE] = {0U};

#define SaSrv_STOP_SEC_VAR_CLEARED_8
#include <SaSrv_MemMap.h>
#endif

/*==================[external function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/* !LINKSTO swdd.DSP.GetSeed, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetSeed
(
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Seed,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 MacLen = SASRV_MAC_SIZE;


  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_GETSEED_ENTRY(
                              OpStatus,
                              Seed,
                              ErrorCode,
                              CfgId
                             );

  (void)OpStatus;

  if(
      (SaSrv_DSP_SecurityLevelCfg[CfgId].staticSeedEnable    == FALSE) ||
      (SaSrv_DSP_SecurityLevelCtx[CfgId].staticSeedGenerated == FALSE)
    )
  {
    /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.GenerateNew, 1 */
    RetVal = SaSrv_DSP_RandomGenerateService(CfgId);

    if(RetVal == E_OK)
    {
      /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.GenerateNew, 1 */
      TS_MemCpy(Seed, SaSrv_DSP_InBuf[CfgId], SASRV_RNG_SIZE);



      /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.GenerateNew, 1 */
      RetVal = SaSrv_DSP_COTS_MACGenerateService(
                                                  SaSrv_DSP_InBuf[CfgId],
                                                  16,
                                                  SaSrv_DSP_AUXBuf[CfgId],
                                                  &MacLen,
                                                  CfgId
                                                );

      if (RetVal == E_OK)
      {
        if (MacLen == SASRV_MAC_SIZE)
        {
          SASRV_ENTER_CRITICAL_SECTION();
          /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.SetGenerated, 1 */
          SaSrv_DSP_SecurityLevelCtx[CfgId].staticSeedGenerated = TRUE;
          SASRV_EXIT_CRITICAL_SECTION();

          /* !LINKSTO swdd.DSP.GetSeed.Ok.Return.Ok, 1 */
          *ErrorCode = DCM_E_POSITIVERESPONSE;
          RetVal     = E_OK;
        }
        else
        {
          /* !LINKSTO swdd.DSP.GetSeed.Csm.MAC.LengthNotOk.ReportDet.CryptoFailed, 1 */
          SASRV_DET_REPORT_ERROR(SASRV_SERVID_MACGENERATE, SASRV_CRYPTO_FAILED);

          /* !LINKSTO swdd.DSP.GetSeed.Csm.MAC.LengthNotOk.Return.NotOk, 1 */
          *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
          RetVal = E_NOT_OK;
        }
      }
      else
      {
        /* !LINKSTO swdd.DSP.GetSeed.Csm.MAC.RetValNotOk.ReportDet.CryptoFailed, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_MACGENERATE, SASRV_CRYPTO_FAILED);

        /* !LINKSTO swdd.DSP.GetSeed.Csm.MAC.RetValNotOk.Return.NotOk, 1 */
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        RetVal = E_NOT_OK;
      }

    }
    else
    {
      /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.RetValNotOk.Return.NotOk, 1 */
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      RetVal = E_NOT_OK;
    }
  }
  else
  {
    /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.UseGenerated.RespData, 1 */
    TS_MemCpy(Seed, SaSrv_DSP_InBuf[CfgId], SASRV_RNG_SIZE);

    /* !LINKSTO swdd.DSP.GetSeed.StaticSeed.UseGenerated.RespCode, 1 */
    *ErrorCode = DCM_E_POSITIVERESPONSE;
    RetVal     = E_OK;
  }

  DBG_SASRV_DSP_GETSEED_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSP.CompareKey, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_CompareKey
(
  P2CONST(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Key,
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_COMPAREKEY_ENTRY(
                                 Key,
                                 OpStatus,
                                 ErrorCode,
                                 CfgId
                                );

  (void)OpStatus;
  (void)CfgId;

  if (E_OK == TS_MemCmp(Key, SaSrv_DSP_AUXBuf[CfgId], SASRV_MAC_SIZE))
  {
    SASRV_ENTER_CRITICAL_SECTION();
    /* !LINKSTO swdd.DSP.CompareKey.StaticSeed.ClearGenerated, 1 */
    SaSrv_DSP_SecurityLevelCtx[CfgId].staticSeedGenerated = FALSE;
    SASRV_EXIT_CRITICAL_SECTION();

    /* !LINKSTO swdd.DSP.CompareKey.Ok.Return.Ok, 1 */
    *ErrorCode = DCM_E_POSITIVERESPONSE;
    RetVal     = E_OK;
  }
  else
  {
    /* !LINKSTO swdd.DSP.CompareKey.InvalidKey.Return.InvalidKey, 1 */
    *ErrorCode = DCM_E_INVALIDKEY;
    RetVal     = SASRV_E_COMPARE_KEY_FAILED;
  }

  DBG_SASRV_DSP_COMPAREKEY_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSP.SetSecurityAttemptCounter, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_SetSecurityAttemptCounter
(
  SaSrv_Dcm_OpStatusType OpStatus,
  uint8                  AttemptCounter,
  uint8                  CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_ENTRY(
                                                OpStatus,
                                                AttemptCounter,
                                                CfgId
                                               );

  if (OpStatus == DCM_INITIAL)
  {
    SASRV_ENTER_CRITICAL_SECTION();
    /* !LINKSTO swdd.DSP.SetSecurityAttemptCounter.NvM.StoreReceivedValue, 1 */
    SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter       = AttemptCounter;
    SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounterMirror = AttemptCounter;
    SASRV_EXIT_CRITICAL_SECTION();

    /* !LINKSTO swdd.DSP.SetSecurityAttemptCounter.NvM.WriteBlock, 1 */
    if (
         E_OK ==
         SaSrv_DSP_NvMService_WriteBlock
         (
           &SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounterMirror,
           CfgId
         )
       )
    {
      /* !LINKSTO swdd.DSP.SetSecurityAttemptCounter.NvM.StoragePending.Return.Pending, 1 */
      RetVal = SASRV_DSP_DCM_E_PENDING;
    }
    else
    {
      /* !LINKSTO swdd.DSP.SetSecurityAttemptCounter.NvM.RetValNotOk.ReportDet.WriteBlockFailed, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_WRITEBLOCK_FAILED);

      /* !LINKSTO swdd.DSP.SetSecurityAttemptCounter.NvM.RetValNotOk.Return.NotOk, 1 */
      RetVal = E_NOT_OK;
    }
  }
  else
  {
    RetVal = SaSrv_DSP_GetStatusWriteFalseAttemptsCounter(CfgId);
  }

  DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_EXIT(RetVal);

  return RetVal;
}

/* !LINKSTO swdd.DSP.GetSecurityAttemptCounter, 1 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetSecurityAttemptCounter
(
        SaSrv_Dcm_OpStatusType             OpStatus,
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) AttemptCounter,
        uint8                              CfgId
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  (void)OpStatus;

  /* Deviation MISRAC2012-1 */
  DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_ENTRY(
                                                OpStatus,
                                                AttemptCounter,
                                                CfgId
                                               );

  SASRV_ENTER_CRITICAL_SECTION();
  if(SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone == TRUE)
  {
    /* !LINKSTO swdd.DSP.GetSecurityAttemptCounter.RetrieveStoredValue, 2 */
    *AttemptCounter = SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter;
    RetVal          = E_OK;
  }
  else
  {
    /* !LINKSTO swdd.DSP.GetSecurityAttemptCounter.Pending, 1 */
    RetVal = SASRV_DSP_DCM_E_PENDING;
  }
  SASRV_EXIT_CRITICAL_SECTION();

  DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_EXIT(RetVal);

  return RetVal;
}

#if (SASRV_HANDLE_ENTROPY == STD_ON)
/* !LINKSTO swdd.DSP.Init, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSP_Init
(
  void
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ErrorStatus = E_NOT_OK;

  DBG_SASRV_DSP_INIT_ENTRY();

  /* !LINKSTO swdd.DSP.Init.NvM.Seed.Status, 1 */
  RetVal = Rte_Call_NvMService_KeyManagement_GetErrorStatus(&ErrorStatus);

  if (RetVal == E_OK)
  {
    if (ErrorStatus == NVM_REQ_RESTORED_FROM_ROM)
    {
      /* !LINKSTO swdd.DSP.Init.NvM.ErrorStatus.RestoredFromRom, 1 */
      (void)SaSrv_DSP_HandleEntropy();
    }
  }
  else
  {
    /* !LINKSTO swdd.DSP.Init.NvM.RetValNotOk.ReportDet.ReadAllFailed, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_READALL_FAILED);
  }

  DBG_SASRV_DSP_INIT_EXIT();
}

/* !LINKSTO swdd.DSP.DeInit, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSP_DeInit
(
  void
)
{
  DBG_SASRV_DSP_DEINIT_ENTRY();

  DBG_SASRV_DSP_DEINIT_EXIT();
}
#endif /* #if (SASRV_HANDLE_ENTROPY == STD_ON) */

/* !LINKSTO swdd.DSP.MainFunction, 1 */
FUNC(void, SaSrv_CODE) SaSrv_DSP_MainFunction
(
  void
)
{
  uint8 CfgId = 0U;

  DBG_SASRV_DSP_MAINFUNCTION_ENTRY();

  for (CfgId = 0U; CfgId < SASRV_DSP_NO_SECURITY_LEVELS; CfgId++)
  {
    SaSrv_DSP_ReadFalseAttemptsCounter(CfgId);
  }

  DBG_SASRV_DSP_MAINFUNCTION_EXIT();
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

#if (SASRV_HANDLE_ENTROPY == STD_ON)
static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_HandleEntropy
(
  void
)
{
  Std_ReturnType RetVal  = E_NOT_OK;

  /* !LINKSTO swdd.HandleEntropy, 1 */
  RetVal = Rte_Call_HandleEntropy_GetEntropy(SaSrv_DSP_Entropy);

  if (RetVal == E_OK)
  {
    /* !LINKSTO swdd.Csm_KeyManagement, 1 */
    (void)SASRV_DSP_RTE_CALL_KEYMANAGEMENT_KEYSETVALID();

    /* !LINKSTO swdd.Csm_KeyManagement, 1 */
    RetVal = SASRV_DSP_RTE_CALL_KEYMANAGEMENT_RANDOMSEED(SaSrv_DSP_Entropy, SASRV_ENTROPY_SIZE);

    if (RetVal != E_OK)
    {
      /* !LINKSTO swdd.DSP.GetSeed.Csm.RandomSeed.RetValNotOk.ReportDet.CryptoFailed, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_RANDOM_SEED, SASRV_CRYPTO_FAILED);
    }
  }
  else
  {
    /* !LINKSTO swdd.DSP.GetSeed.Swc.GetEntropy.RetValNotOk.ReportDet.CryptoFailed, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_GET_ENTROPY, SASRV_ENTROPY_FAILED);
  }

  return RetVal;
}
#endif

/* EA Behavior: Generate random number */
static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_RandomGenerateService
(
  uint8 CfgId
)
{
          uint32 RNGSize = SASRV_RNG_SIZE;
  Std_ReturnType RetVal  = E_NOT_OK;

  RetVal = Rte_Call_CsmRandomGenerate_RandomGenerate(SaSrv_DSP_InBuf[CfgId], &RNGSize);

  if (RetVal == SASRV_E_ENTROPY_EXHAUSTION)
  {
    /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.RetValEntropy.ReportDet.EntropyExhaustion, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_RNG_GENERATION, SASRV_RNG_ENTROPYEXHAUSTION);

#if (SASRV_HANDLE_ENTROPY == STD_ON)
    /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.RetValExhaustion.HandleEntropy, 1 */
    RetVal = SaSrv_DSP_HandleEntropy();

    if (RetVal == E_OK)
    {
      /* !LINKSTO swdd.DSP.GetSeed.Csm.RetryRNG, 1 */
      RetVal = Rte_Call_CsmRandomGenerate_RandomGenerate(SaSrv_DSP_InBuf[CfgId], &RNGSize);

      if (RetVal != E_OK)
      {
        /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.RetValNotOk.ReportDet.CryptoFailed, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_RNG_GENERATION, SASRV_CRYPTO_FAILED);

        RetVal = E_NOT_OK;
      }
      else
      {
        if (RNGSize != SASRV_RNG_SIZE)
        {
          /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.InvalidLength.ReportDet.CryptoFailed, 1 */
          SASRV_DET_REPORT_ERROR(SASRV_SERVID_RNG_GENERATION, SASRV_CRYPTO_FAILED);

          RetVal = E_NOT_OK;
        }
        else
        {
          RetVal = E_OK;
        }
      }
    }
#else
    RetVal = E_NOT_OK;
#endif
  }
  else if (RetVal != E_OK)
  {
    /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.RetValNotOk.ReportDet.CryptoFailed, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_RNG_GENERATION, SASRV_CRYPTO_FAILED);

    RetVal = E_NOT_OK;
  }
  else
  {
    if (RNGSize != SASRV_RNG_SIZE)
    {
      /* !LINKSTO swdd.DSP.GetSeed.Csm.RNG.InvalidLength.ReportDet.CryptoFailed, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_RNG_GENERATION, SASRV_CRYPTO_FAILED);

      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
  }

  return RetVal;
}

static FUNC(void, SaSrv_CODE) SaSrv_DSP_ReadFalseAttemptsCounter
(
  uint8 CfgId
)
{
  uint8 errorStatus = NVM_REQ_NOT_OK;

  /* !LINKSTO swdd.MainFunc.NvM.ReadAll.Status, 1 */
  if (SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone == FALSE)
  {
    if (E_OK == SaSrv_DSP_NvMService_GetErrorStatus(&errorStatus, CfgId))
    {
      switch(errorStatus)
      {
        case NVM_REQ_OK:
        {
          SASRV_ENTER_CRITICAL_SECTION();
          SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter =
            SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounterMirror;
          /* Read all operation was finalized successfully */
          SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone = TRUE;
          SASRV_EXIT_CRITICAL_SECTION();
        }
        break;

        case NVM_REQ_PENDING:
        {
          SASRV_ENTER_CRITICAL_SECTION();
          if(SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfFalseAttemptsCounterRetries <
             SASRV_DSP_NR_OF_ATTEMPT_COUNTER_RETRY)
          {
            /* !LINKSTO swdd.MainFunc.NvM.ReadAll.Pending, 2 */
            SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone = FALSE;
            SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfFalseAttemptsCounterRetries++;
          }
          else
          {
            /* !LINKSTO swdd.MainFunc.NvM.ReadAll.PendingFailed, 1 */
            SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter =
              SaSrv_DSP_SecurityLevelCfg[CfgId].maxNumberOfFailedAttempts;
            /* Read all operation failed */
            SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone = TRUE;
            SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfFalseAttemptsCounterRetries = 0U;

            /* !LINKSTO swdd.MainFunc.NvM.StatusNotOk.ReportDet.ReadAllFailed, 1 */
            SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_READALL_FAILED);
          }
          SASRV_EXIT_CRITICAL_SECTION();
        }
        break;

        case NVM_REQ_NOT_OK:
        default:
        {
          SASRV_ENTER_CRITICAL_SECTION();
          /* !LINKSTO swdd.MainFunc.NvM.ReadAllFailed.SetCounter, 2 */
          SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter =
            SaSrv_DSP_SecurityLevelCfg[CfgId].maxNumberOfFailedAttempts;
          /* Read all operation failed */
          SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone = TRUE;
          SASRV_EXIT_CRITICAL_SECTION();

          /* !LINKSTO swdd.MainFunc.NvM.StatusNotOk.ReportDet.ReadAllFailed, 1 */
          SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_READALL_FAILED);
        }
        break;
      }
    }
    else
    {
      SASRV_ENTER_CRITICAL_SECTION();
      SaSrv_DSP_SecurityLevelCtx[CfgId].falseAttemptsCounter =
        SaSrv_DSP_SecurityLevelCfg[CfgId].maxNumberOfFailedAttempts;
      /* Read all operation failed */
      SaSrv_DSP_SecurityLevelCtx[CfgId].readAllDone = TRUE;
      SASRV_EXIT_CRITICAL_SECTION();

      /* !LINKSTO swdd.MainFunc.NvM.RetValNotOk.ReportDet.ReadAllFailed, 1 */
      SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_READALL_FAILED);
    }
  }
}

static FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetStatusWriteFalseAttemptsCounter
(
  uint8 CfgId
)
{
  Std_ReturnType RetVal      = E_NOT_OK;
  uint8          errorStatus = NVM_REQ_NOT_OK;

  if (E_OK == SaSrv_DSP_NvMService_GetErrorStatus(&errorStatus, CfgId))
  {
    switch(errorStatus)
    {
      case NVM_REQ_OK:
      {
        SASRV_ENTER_CRITICAL_SECTION();
        /* !LINKSTO swdd.MainFunc.NvM.StatusOK, 1 */
        SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries = 0U;
        SASRV_EXIT_CRITICAL_SECTION();

        RetVal = E_OK;
      }
      break;

      case NVM_REQ_PENDING:
      {
        if(SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries <
           SASRV_DSP_NR_OF_WRITE_ATTEMPT_COUNTER_RETRY)
        {
          SASRV_ENTER_CRITICAL_SECTION();
          /* !LINKSTO swdd.MainFunc.NvM.StatusAfterWrite.Pending, 2 */
          SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries++;
          SASRV_EXIT_CRITICAL_SECTION();

          RetVal = SASRV_DSP_DCM_E_PENDING;
        }
        else
        {
          SASRV_ENTER_CRITICAL_SECTION();
          /* !LINKSTO swdd.MainFunc.NvM.StatusAfterWrite.PendingMax, 1 */
          SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries = 0U;
          SASRV_EXIT_CRITICAL_SECTION();

          /* !LINKSTO swdd.MainFunc.NvM.StatusNotOk.ReportDet.WriteBlockFailed, 1 */
          SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_WRITEBLOCK_FAILED);
        }
      }
      break;

      case NVM_REQ_NOT_OK:
      default:
      {
        SASRV_ENTER_CRITICAL_SECTION();
        /* Write block operation failed */
        SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries = 0U;
        SASRV_EXIT_CRITICAL_SECTION();

        /* !LINKSTO swdd.MainFunc.NvM.StatusNotOk.ReportDet.WriteBlockFailed, 1 */
        SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_WRITEBLOCK_FAILED);
      }
      break;
    }
  }
  else
  {
    SASRV_ENTER_CRITICAL_SECTION();
    /* Write block operation failed */
    SaSrv_DSP_SecurityLevelCtx[CfgId].numberOfWriteFalseAttemptsCounterRetries = 0U;
    SASRV_EXIT_CRITICAL_SECTION();

    /* !LINKSTO swdd.MainFunc.NvM.RetValNotOk.ReportDet.WriteBlockFailed, 1 */
    SASRV_DET_REPORT_ERROR(SASRV_SERVID_NVM_SERVICES, SASRV_WRITEBLOCK_FAILED);
  }

  return RetVal;
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*================================================================================================*/

/*==================[end of file]=================================================================*/
