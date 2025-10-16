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

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_RandomSeed.h>
#include <Csm_RandomSeedCfg.h>

/* !LINKSTO EB_CSM0677_02, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#if (CSM_RANDOMSEED_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)

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
static FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomSeedSynchronousMainCall
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */



/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/** \brief The run state of the service.
 **/
VAR(boolean, CSM_VAR) Csm_RandomSeedIsRunning = FALSE;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Id of the current configuration.
 **/
VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_RandomSeedCurrentConfigId;

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification return value
 **/
volatile VAR(Csm_ReturnType, CSM_VAR) Csm_RandomSeed_Ret_CallbackNotification = CSM_E_OK;
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        completely finished the currently computeted service.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_RandomSeed_Flg_ServiceFinishNotification = FALSE;
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        finished the current start, updated or finish computation.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_RandomSeed_Flg_CallbackNotification = FALSE;
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

#if (CSM_RANDOMSEED_RTE_INTERFACE_ENABLED == STD_ON)

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteRandomSeedStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0778, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteRandomSeedStart
(
  Csm_ConfigIdType pdav0
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_RandomSeedStart
                            (
                              pdav0
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteRandomSeedUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0778, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteRandomSeedUpdate
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) seedBuffer,
          uint32                                      seedLength
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_RandomSeedUpdate
                            (
                              pdav0,
                              seedBuffer,
                              seedLength
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteRandomSeedFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0778, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteRandomSeedFinish
(
  Csm_ConfigIdType pdav0
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_RandomSeedFinish
                            (
                              pdav0
                            );

  return retVal;
}

#endif /* #if (CSM_RANDOMSEED_RTE_INTERFACE_ENABLED == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedStart]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO CSM0149, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomSeedStart
(
  Csm_ConfigIdType cfgId
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0046, 1
   */
  if ( cfgId >= (sizeof(Csm_RandomSeedConfigurations   ) /
                 sizeof(Csm_RandomSeedConfigurations[0])
                )
     )
  {
    RetVal = CSM_E_NOT_OK;
  }
  /* !LINKSTO EB_Csm_Immediate_Restart,1 */
#if (CSM_RANDOMSEED_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  /* !LINKSTO EB_CSM0017_Busy, 1
   */
  else
#if (CSM_USEPRIORITIES_ENABLED == STD_ON)
  if ( ((Csm_RandomSeedIsRunning == TRUE)
       /* !LINKSTO EB_CSMPrio, 1 */
       && (
        (Csm_RandomSeedConfigurations[cfgId].CsmRandomSeedUsePriorities == FALSE) ||
        (Csm_RandomSeedConfigurations[cfgId].PrimitiveStartFct !=
         Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].PrimitiveStartFct))
        )
       && ((Csm_RandomSeedConfigurations[cfgId].CsmRandomSeedEnableRestart == FALSE) ||
        (Csm_RandomSeedCurrentConfigId != cfgId)) )
#else
  if ( (Csm_RandomSeedIsRunning == TRUE) &&
       ((Csm_RandomSeedConfigurations[cfgId].CsmRandomSeedEnableRestart == FALSE) ||
        (Csm_RandomSeedCurrentConfigId != cfgId)) )
#endif /* #if (CSM_USEPRIORITIES_ENABLED == STD_ON) */
  {
    RetVal = CSM_E_BUSY;
  }
#endif /* #if (CSM_IMMEDIATE_RESTART_ENABLED == STD_OFF) */
  else
  {
    /* !LINKSTO EB_CSM0017_Restart, 1
     */

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
    Csm_RandomSeed_Ret_CallbackNotification = CSM_E_NOT_OK;
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */

    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_RandomSeedConfigurations[cfgId].
      PrimitiveStartFct
      (
        Csm_RandomSeedConfigurations[cfgId].PrimitiveConfigPtr
      );

    /* !LINKSTO EB_CSM0017_Restart_OK, 1
     */
    if ( RetVal == CSM_E_OK )
    {
      Csm_RandomSeedIsRunning = TRUE;

      /* !LINKSTO EB_CSMPrio_2, 1 */
      Csm_RandomSeedCurrentConfigId = cfgId;
#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
      /* !LINKSTO CSM0047, 1
       */
      /* !LINKSTO EB_CSM_SDS_0006,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_RandomSeedSynchronousMainCall();
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */
    }
    else if ( RetVal != CSM_E_BUSY )
    {
      /* !LINKSTO EB_CSM0017_Restart_Error, 2
       * Something went wrong in Cry, e.g. invalid arguments were provided.
       * In this case, the Cry is assumed to have aborted all running services.
       */
      Csm_RandomSeedIsRunning = FALSE;
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
/*----[Csm_RandomSeedUpdate]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0156_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomSeedUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                                      seedLength
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0050, 1
   */
  if ( (Csm_RandomSeedIsRunning       == FALSE) ||
       (Csm_RandomSeedCurrentConfigId != cfgId)
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
      Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].
      PrimitiveUpdateFct
      (
        seedPtr,
        seedLength
      );

    if ( RetVal == CSM_E_NOT_OK )
    {
      Csm_RandomSeedIsRunning = FALSE;
    }

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0052,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_RandomSeedSynchronousMainCall();
    }
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedFinish]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0163_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomSeedFinish
(
  Csm_ConfigIdType cfgId
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0056, 1
   */
  if ( (Csm_RandomSeedIsRunning       == FALSE) ||
       (Csm_RandomSeedCurrentConfigId != cfgId)
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
      Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].
      PrimitiveFinishFct
      (
      );

    if ( CSM_E_NOT_OK == RetVal )
    {
      Csm_RandomSeedIsRunning = FALSE;
    }

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0058,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_RandomSeedSynchronousMainCall();
      Csm_RandomSeedIsRunning = FALSE;
    }
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}


#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedMainFunction]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_RandomSeedMainFunction
(
  void
)
{
  if ( Csm_RandomSeedIsRunning == TRUE )
  {
    /* !LINKSTO CSM0469, 1
     */
    Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].
    PrimitiveMainFct();
  }
}
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedCallbackNotification]--------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0455, 1
 */
/* !LINKSTO CSM0039, 1
 */
FUNC(void, CSM_CODE) Csm_RandomSeedCallbackNotification
(
  Csm_ReturnType result
)
{
#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)

    Csm_RandomSeed_Flg_CallbackNotification = TRUE;
    Csm_RandomSeed_Ret_CallbackNotification = result;

    if (NULL_PTR                                                                                 !=
        Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].CallbackFct
       )
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  {
      /* !LINKSTO EB_CSM_SDS_0003,1 */
      (void) Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].
           CallbackFct(result);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedServiceFinishNotification]---------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0457, 1
 */
FUNC(void, CSM_CODE) Csm_RandomSeedServiceFinishNotification
(
  void
)
{
#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)

  Csm_RandomSeed_Flg_ServiceFinishNotification = TRUE;

#else /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */

  Csm_RandomSeedIsRunning = FALSE;

#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RandomSeedInit]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_RandomSeedInit
(
  void
)
{
  /* !LINKSTO CSM0021, 1
   */
  Csm_RandomSeedIsRunning = FALSE;
}


/*==================[internal function definitions]===============================================*/

#if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON)

static FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomSeedSynchronousMainCall
  (void)
{
  Csm_ReturnType returnVal;
  /* !LINKSTO CSM0035, 1
   */
  Csm_RandomSeed_Flg_CallbackNotification = FALSE;
  Csm_RandomSeed_Flg_ServiceFinishNotification = FALSE;

  /* !LINKSTO EB_CSM_SDS_0005,1 */
  while ((Csm_RandomSeed_Flg_CallbackNotification      == FALSE) &&
         (Csm_RandomSeed_Flg_ServiceFinishNotification == FALSE)
        )
  {
    Csm_RandomSeedConfigurations[Csm_RandomSeedCurrentConfigId].
    PrimitiveMainFct();
  }
  /* !LINKSTO EB_CSM_SDS_0007,1 */
  returnVal = Csm_RandomSeed_Ret_CallbackNotification;
  return returnVal;
}
#endif /* #if (CSM_RANDOMSEED_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>
/*================================================================================================*/

#else  /* #if (CSM_RANDOMSEED_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_RandomSeed_EmptyTranslationUnit_t;

#endif /* #if (CSM_RANDOMSEED_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

