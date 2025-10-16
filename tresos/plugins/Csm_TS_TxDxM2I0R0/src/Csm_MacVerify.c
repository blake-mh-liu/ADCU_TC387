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

/* !LINKSTO CSM0006, 1
 */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 11.4 (advisory)
 *   "A cast should not be performed between a pointer to object type and a different pointer to
 *    object type."
 *
 *   Reason:
 *   The Csm SWS demands differing but compatible types for RTE interface functions and the
 *   underlying Csm API functions.
 */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   A cast shall not be performed between a pointer to object type and a pointer to a different
 *   object type.
 *
 *   Reason:
 *   The Csm SWS demands differing but compatible types for RTE interface functions and the
 *   underlying Csm API functions.
 */

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_MacVerify.h>
#include <Csm_MacVerifyCfg.h>

/* !LINKSTO EB_CSM0677_02, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#if (CSM_MACVERIFY_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)

#define CSM_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CSM_SDS_0004,1 */
/** \brief Calls the Cry primitives mainfunction in a loop for synchronous job processing
 *
 * \pre    The primitives API function has returned with CSM_E_OK
 * \post   The primitives ha finished its computation and invoked the Csm callback
 * \return the computation result passed by the primitive to the Csm callback
 * \retval CSM_E_OK                  The computation was successful
 * \retval CSM_E_NOT_OK              The computation failed
 * \retval CSM_E_BUSY                The computation has been aborted
 * \retval CSM_E_SMALL_BUFFER        The provided buffer is too small
 * \retval CSM_E_ENTROPY_EXHAUSTION  The entropy of the random number generator is exhausted
 * \retval userdefined               Further user defined values are possible
 */
static FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifySynchronousMainCall
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */



/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/** \brief The run state of the service.
 **/
VAR(boolean, CSM_VAR) Csm_MacVerifyIsRunning = FALSE;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Id of the current configuration.
 **/
VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_MacVerifyCurrentConfigId;

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification return value
 **/
volatile VAR(Csm_ReturnType, CSM_VAR) Csm_MacVerify_Ret_CallbackNotification = CSM_E_OK;
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        completely finished the currently computeted service.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_MacVerify_Flg_ServiceFinishNotification = FALSE;
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        finished the current start, updated or finish computation.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_MacVerify_Flg_CallbackNotification = FALSE;
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

#if (CSM_MACVERIFY_RTE_INTERFACE_ENABLED == STD_ON)

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteMacVerifyStart]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0777_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteMacVerifyStart
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(SymKeyType,       AUTOMATIC, CSM_APPL_DATA) key
)
{
  Std_ReturnType retVal;

  /* Deviation MISRA-1 <START> */
  /* Deviation MISRAC2012-1 <START> */
  retVal = (Std_ReturnType) Csm_MacVerifyStart
                            (
                              pdav0,
                              (P2CONST(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA)) key
                            );
  /* Deviation MISRA-1 <STOP> */
  /* Deviation MISRAC2012-1 <STOP> */

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteMacVerifyUpdate]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0777_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteMacVerifyUpdate
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataBuffer,
          uint32                                      dataLength
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_MacVerifyUpdate
                            (
                              pdav0,
                              dataBuffer,
                              dataLength
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteMacVerifyFinish]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0777_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteMacVerifyFinish
(
          Csm_ConfigIdType                                pdav0,
  P2CONST(uint8,                AUTOMATIC, CSM_APPL_DATA) MacBuffer,
          uint32                                          MacLength,
    P2VAR(Csm_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_MacVerifyFinish
                            (
                              pdav0,
                              MacBuffer,
                              MacLength,
                              resultBuffer
                            );

  return retVal;
}

#endif /* #if (CSM_MACVERIFY_RTE_INTERFACE_ENABLED == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyStart]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO CSM0128, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyStart
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0046, 1
   */
  if ( cfgId >= (sizeof(Csm_MacVerifyConfigurations   ) /
                 sizeof(Csm_MacVerifyConfigurations[0])
                )
     )
  {
    RetVal = CSM_E_NOT_OK;
  }
  /* !LINKSTO EB_Csm_Immediate_Restart,1 */
#if (CSM_MACVERIFY_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  /* !LINKSTO EB_CSM0017_Busy, 1
   */
  else
#if (CSM_USEPRIORITIES_ENABLED == STD_ON)
  if ( ((Csm_MacVerifyIsRunning == TRUE)
       /* !LINKSTO EB_CSMPrio, 1 */
       && (
        (Csm_MacVerifyConfigurations[cfgId].CsmMacVerifyUsePriorities == FALSE) ||
        (Csm_MacVerifyConfigurations[cfgId].PrimitiveStartFct !=
         Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].PrimitiveStartFct))
        )
       && ((Csm_MacVerifyConfigurations[cfgId].CsmMacVerifyEnableRestart == FALSE) ||
        (Csm_MacVerifyCurrentConfigId != cfgId)) )
#else
  if ( (Csm_MacVerifyIsRunning == TRUE) &&
       ((Csm_MacVerifyConfigurations[cfgId].CsmMacVerifyEnableRestart == FALSE) ||
        (Csm_MacVerifyCurrentConfigId != cfgId)) )
#endif /* #if (CSM_USEPRIORITIES_ENABLED == STD_ON) */
  {
    RetVal = CSM_E_BUSY;
  }
#endif /* #if (CSM_IMMEDIATE_RESTART_ENABLED == STD_OFF) */
  else
  {
    /* !LINKSTO EB_CSM0017_Restart, 1
     */

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
    Csm_MacVerify_Ret_CallbackNotification = CSM_E_NOT_OK;
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_MacVerifyConfigurations[cfgId].
      PrimitiveStartFct
      (
        Csm_MacVerifyConfigurations[cfgId].PrimitiveConfigPtr,
        keyPtr
      );

    /* !LINKSTO EB_CSM0017_Restart_OK, 1
     */
    if ( RetVal == CSM_E_OK )
    {
      Csm_MacVerifyIsRunning = TRUE;

      /* !LINKSTO EB_CSMPrio_2, 1 */
      Csm_MacVerifyCurrentConfigId = cfgId;
#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
      /* !LINKSTO CSM0047, 1
       */
      /* !LINKSTO EB_CSM_SDS_0006,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_MacVerifySynchronousMainCall();
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */
    }
    else if ( RetVal != CSM_E_BUSY )
    {
      /* !LINKSTO EB_CSM0017_Restart_Error, 2
       * Something went wrong in Cry, e.g. invalid arguments were provided.
       * In this case, the Cry is assumed to have aborted all running services.
       */
      Csm_MacVerifyIsRunning = FALSE;
    }
    else
    {
      /* The RetVal is CSM_E_BUSY, hence the former calculation continues and
       * no action needs to be taken.
       */
    }
  }

  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyUpdate]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0134_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0050, 1
   */
  if ( (Csm_MacVerifyIsRunning       == FALSE) ||
       (Csm_MacVerifyCurrentConfigId != cfgId)
     )
  {
    /* !LINKSTO CSM0657, 1
     */
    RetVal = CSM_E_NOT_OK;
  }
  else
  {
    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].
      PrimitiveUpdateFct
      (
        dataPtr,
        dataLength
      );

    if ( RetVal == CSM_E_NOT_OK )
    {
      Csm_MacVerifyIsRunning = FALSE;
    }

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0052,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_MacVerifySynchronousMainCall();
    }
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyFinish]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0141_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyFinish
(
          Csm_ConfigIdType                                cfgId,
  P2CONST(uint8,                AUTOMATIC, CSM_APPL_DATA) MacPtr,
          uint32                                          MacLength,
    P2VAR(Csm_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) resultPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0056, 1
   */
  if ( (Csm_MacVerifyIsRunning       == FALSE) ||
       (Csm_MacVerifyCurrentConfigId != cfgId)
     )
  {
    /* !LINKSTO CSM0658, 1
     */
    RetVal = CSM_E_NOT_OK;
  }
  else
  {
    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].
      PrimitiveFinishFct
      (
        MacPtr,
        MacLength,
        resultPtr
      );

    if ( CSM_E_NOT_OK == RetVal )
    {
      Csm_MacVerifyIsRunning = FALSE;
    }

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0058,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_MacVerifySynchronousMainCall();
      Csm_MacVerifyIsRunning = FALSE;
    }
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}


#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyMainFunction]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_MacVerifyMainFunction
(
  void
)
{
  if ( Csm_MacVerifyIsRunning == TRUE )
  {
    /* !LINKSTO CSM0469, 1
     */
    Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].
    PrimitiveMainFct();
  }
}
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyCallbackNotification]---------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0455, 1
 */
/* !LINKSTO CSM0039, 1
 */
FUNC(void, CSM_CODE) Csm_MacVerifyCallbackNotification
(
  Csm_ReturnType result
)
{
#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)

    Csm_MacVerify_Flg_CallbackNotification = TRUE;
    Csm_MacVerify_Ret_CallbackNotification = result;

    if (NULL_PTR                                                                                 !=
        Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].CallbackFct
       )
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  {
      /* !LINKSTO EB_CSM_SDS_0003,1 */
      (void) Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].
           CallbackFct(result);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyServiceFinishNotification]----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0457, 1
 */
FUNC(void, CSM_CODE) Csm_MacVerifyServiceFinishNotification
(
  void
)
{
#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)

  Csm_MacVerify_Flg_ServiceFinishNotification = TRUE;

#else /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

  Csm_MacVerifyIsRunning = FALSE;

#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MacVerifyInit]-------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_MacVerifyInit
(
  void
)
{
  /* !LINKSTO CSM0021, 1
   */
  Csm_MacVerifyIsRunning = FALSE;
}


/*==================[internal function definitions]===============================================*/

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)

static FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifySynchronousMainCall
  (void)
{
  Csm_ReturnType returnVal;
  /* !LINKSTO CSM0035, 1
   */
  Csm_MacVerify_Flg_CallbackNotification = FALSE;
  Csm_MacVerify_Flg_ServiceFinishNotification = FALSE;

  /* !LINKSTO EB_CSM_SDS_0005,1 */
  while ((Csm_MacVerify_Flg_CallbackNotification      == FALSE) &&
         (Csm_MacVerify_Flg_ServiceFinishNotification == FALSE)
        )
  {
    Csm_MacVerifyConfigurations[Csm_MacVerifyCurrentConfigId].
    PrimitiveMainFct();
  }
  /* !LINKSTO EB_CSM_SDS_0007,1 */
  returnVal = Csm_MacVerify_Ret_CallbackNotification;
  return returnVal;
}
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>
/*================================================================================================*/

#else  /* #if (CSM_MACVERIFY_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_MacVerify_EmptyTranslationUnit_t;

#endif /* #if (CSM_MACVERIFY_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

