/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/* Code-Metric Deviation List
 *
 * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 92 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-2) Deviated Rule: HIS_V(G)
 * not 24 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                           /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.c/0004,1 */
#include <Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Cfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)
/** \brief  Processes the job on the driver object.
 **
 ** This functions calls the processJob function of the primitive given by the job. The primitive
 ** is executed on the given driver object. The primitive will be executed as secondary primitive
 ** and hence will not release the driver object after processing is done.
 **
 ** \params[in]  objectId  The Id of the driver object the job shall be executed on.
 ** \params[in]  job       The job that shall be executed.
 **
 ** \returns  The result of the process function.
 **
 ** \retval  E_OK                   Process function successful.
 ** \retval  E_NOT_OK               Process function failed.
 ** \retval  CRYPTO_E_JOB_CANCELED  Process function failed, because job using this primitive
 **                                 was cancelled.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */
/** \brief  This is a dummy callback for the primitives executed in KeyManagement.
 **
 ** This function is used as callback for primitives, that are executed as secondary primitive
 ** inside the KeyManagement because additional primitives will be executed aftewards.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 ** \param[in]      cbkType    The type (none, start, update, finish, cancel) of the callback.
 ** \param[in]      cbkResult  The result of the callback.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK  Always returns this value.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)

/** \brief  The PrimitiveType for the dummy primitive. **/
CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_Primitive =
{
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Callback,
  0U,
  0U,
  0U
};

/** \brief  The CDOPrimitiveCnfgType for the dummy primitive. **/
CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_PrimitiveCnfg =
{
  &Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_Primitive,
  NULL_PTR,
  0U,
  NULL_PTR,
  0U
};

/** \brief  The dummy primitive used if a KeyManagement job shall be executed as secondary job. **/
CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_DummyPrimitive =
{
  &Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_PrimitiveCnfg,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR
};

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
/* --- Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Process ------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)
/* Deviation CODEMETRIC-1, CODEMETRIC-2 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId,
          uint32                                                 targetCryptoKeyId
)
{
  uint32 repeatCounter = 0U;
  uint32 primitiveOutputLength = *jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr;
  uint32 keyOutLengthSum = 0U;
  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0014,1 */
  uint32 counter         = 0U;
  uint8  counterBuff[4U] = {0U};
  uint8  counterLen      = 4U;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) passWordKeyPtr  = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) fixedInfoKeyPtr = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) deriveKeyPtr    = NULL_PTR;

  Std_ReturnType retVal             = E_NOT_OK;
  Std_ReturnType lockResult         = E_NOT_OK;
  boolean        fromPrimitive      = FALSE;

  TS_PARAM_UNUSED(jobsLength);
  TS_PARAM_UNUSED(wkspDataPtr);
  TS_PARAM_UNUSED(wkspDataLen);

  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0006,1 */
  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0007,1 */
  /* Get the Password Infor from key element */
  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                      CRYPTO_KE_KEYDERIVATION_PASSWORD,
                                                     &passWordKeyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  if (E_OK == retVal)
  {
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(lockResult, passWordKeyPtr, fromPrimitive);
    if (E_OK == lockResult)
    {
      /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0008,1 */
      /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0009,1 */
      /* Get the Fixed Infor from key element */
      retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                          CRYPTO_XVIX_XAIX_KE_KEYDERIVATION_FIXEDINFOID,
                                                        &fixedInfoKeyPtr,
                                                          FALSE,
                                                          CRYPTO_XVIX_XAIX_SID_EMPTY
                                                        );
      if (E_OK == retVal)
      {
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(lockResult, fixedInfoKeyPtr, fromPrimitive);
        if (E_OK == lockResult)
        {
          /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0010,1 */
          /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0011,1 */
          /* Get the Derive Key Info from key element */
          retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( targetCryptoKeyId,
                                                              CRYPTO_XVIX_XAIX_KDF_DERIVED_KEY_ELEMENT_ID,
                                                              &deriveKeyPtr,
                                                              FALSE,
                                                              CRYPTO_XVIX_XAIX_SID_EMPTY
                                                            );
          if (E_OK == retVal)
          {
            /* CHECK: NOPARSE */
            /* Defensive programming:
            * Primitive Output muss not be zero in any cases.
            * */
            if (0U != primitiveOutputLength)
            /* CHECK: PARSE */
            {
              /* Deviation TASKING-1 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(lockResult, deriveKeyPtr, fromPrimitive);
              if (E_OK == lockResult)
              {
                /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0012,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0013,1 */
                repeatCounter = (uint32)(1U + ((deriveKeyPtr->data->size - 1U) / primitiveOutputLength));
                /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0015,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0016,1 */
                for (counter = 1U; counter <= repeatCounter; counter++)
                {
                  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0017,1 */
                  counterBuff[0U] = (uint8)(counter >> 24U);
                  counterBuff[1U] = (uint8)(counter >> 16U);
                  counterBuff[2U] = (uint8)(counter >> 8U);
                  counterBuff[3U] = (uint8)(counter);

                  if ((deriveKeyPtr->data->size - keyOutLengthSum) < primitiveOutputLength)
                  {
                    primitiveOutputLength = deriveKeyPtr->data->size - keyOutLengthSum;
                  }

                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = &deriveKeyPtr->data->data[keyOutLengthSum];
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &primitiveOutputLength;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_START;
                  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_UPDATE;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = counterBuff;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = counterLen;
                  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

                  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0018,1 */
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_UPDATE;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = passWordKeyPtr->data->data;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = passWordKeyPtr->data->size;
                  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

                  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0019,1 */
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_UPDATE;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = fixedInfoKeyPtr->data->data;
                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = fixedInfoKeyPtr->data->size;
                  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

                  jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_FINISH;
                  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

                  /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0020,1 */
                  keyOutLengthSum += primitiveOutputLength;
                }
                /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0021,1 */
                Crypto_xVIx_xAIx_Keys[targetCryptoKeyId].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_VALID;

                CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(deriveKeyPtr);
              }
              else
              {
                /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0006,2 */
                /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0013,2 */
                retVal = E_NOT_OK;
              }
            }
          }
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(fixedInfoKeyPtr);
        }
        else
        {
          /* Not able to lock the Fixed Infor key element*/
          retVal = E_NOT_OK;
        }
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(passWordKeyPtr);
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0004,2 */
      retVal = E_NOT_OK;
    }
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr;

  /* This function can not fail because it will only be called if the primitive exists in the CDO */
  (void) Crypto_xVIx_xAIx_CheckJobPrimitive(objectId, job, &primitivePtr);
  primitivePtr->data->P1 = &Crypto_xVIx_xAIx_KEYDERIVE_SINGLESTEPKDF_NOTSET_DummyPrimitive;

  Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = job;

  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = primitivePtr;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  return primitivePtr->cnfg->description->fcnProcess(objectId, job, primitivePtr);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */
/* --- Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Callback ----------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);
  TS_PARAM_UNUSED(cbkType);
  TS_PARAM_UNUSED(cbkResult);

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

