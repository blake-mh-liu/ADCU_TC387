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
#include <Csm_AsymPrivateKeyWrapAsym.h>
#include <Csm_AsymPrivateKeyWrapAsymCfg.h>

/* !LINKSTO EB_CSM0677_02, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#if (CSM_ASYMPRIVATEKEYWRAPASYM_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

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
static FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapAsymSynchronousMainCall
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */



/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/** \brief The run state of the service.
 **/
VAR(boolean, CSM_VAR) Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Id of the current configuration.
 **/
VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_AsymPrivateKeyWrapAsymCurrentConfigId;

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification return value
 **/
volatile VAR(Csm_ReturnType, CSM_VAR) Csm_AsymPrivateKeyWrapAsym_Ret_CallbackNotification = CSM_E_OK;
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        completely finished the currently computeted service.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_AsymPrivateKeyWrapAsym_Flg_ServiceFinishNotification = FALSE;
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        finished the current start, updated or finish computation.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_AsymPrivateKeyWrapAsym_Flg_CallbackNotification = FALSE;
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

#if (CSM_ASYMPRIVATEKEYWRAPASYM_RTE_INTERFACE_ENABLED == STD_ON)

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteAsymPrivateKeyWrapAsymStart]--------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0800_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteAsymPrivateKeyWrapAsymStart
(
          Csm_ConfigIdType                              pdav0,
  P2CONST(AsymPrivateKeyType, AUTOMATIC, CSM_APPL_DATA) key,
  P2CONST(AsymPublicKeyType,  AUTOMATIC, CSM_APPL_DATA) wrappingKey
)
{
  Std_ReturnType retVal;

  /* Deviation MISRA-1 <START> */
  /* Deviation MISRAC2012-1 <START> */
  retVal = (Std_ReturnType) Csm_AsymPrivateKeyWrapAsymStart
                            (
                              pdav0,
                              (P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_DATA)) key,
                              (P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_DATA)) wrappingKey
                            );
  /* Deviation MISRA-1 <STOP> */
  /* Deviation MISRAC2012-1 <STOP> */

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteAsymPrivateKeyWrapAsymUpdate]-------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0800_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteAsymPrivateKeyWrapAsymUpdate
(
        Csm_ConfigIdType                            pdav0,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) dataBuffer,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) dataLength
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_AsymPrivateKeyWrapAsymUpdate
                            (
                              pdav0,
                              dataBuffer,
                              dataLength
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteAsymPrivateKeyWrapAsymFinish]-------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0800_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteAsymPrivateKeyWrapAsymFinish
(
  Csm_ConfigIdType pdav0
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_AsymPrivateKeyWrapAsymFinish
                            (
                              pdav0
                            );

  return retVal;
}

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_RTE_INTERFACE_ENABLED == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymStart]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO CSM0748, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapAsymStart
(
          Csm_ConfigIdType                                  cfgId,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2CONST(Csm_AsymPublicKeyType,  AUTOMATIC, CSM_APPL_DATA) wrappingKeyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0046, 1
   */
  if ( cfgId >= (sizeof(Csm_AsymPrivateKeyWrapAsymConfigurations   ) /
                 sizeof(Csm_AsymPrivateKeyWrapAsymConfigurations[0])
                )
     )
  {
    RetVal = CSM_E_NOT_OK;
  }
  /* !LINKSTO EB_Csm_Immediate_Restart,1 */
#if (CSM_ASYMPRIVATEKEYWRAPASYM_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  /* !LINKSTO EB_CSM0017_Busy, 1
   */
  else
#if (CSM_USEPRIORITIES_ENABLED == STD_ON)
  if ( ((Csm_AsymPrivateKeyWrapAsymIsRunning == TRUE)
       /* !LINKSTO EB_CSMPrio, 1 */
       && (
        (Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].CsmAsymPrivateKeyWrapAsymUsePriorities == FALSE) ||
        (Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].PrimitiveStartFct !=
         Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].PrimitiveStartFct))
        )
       && ((Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].CsmAsymPrivateKeyWrapAsymEnableRestart == FALSE) ||
        (Csm_AsymPrivateKeyWrapAsymCurrentConfigId != cfgId)) )
#else
  if ( (Csm_AsymPrivateKeyWrapAsymIsRunning == TRUE) &&
       ((Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].CsmAsymPrivateKeyWrapAsymEnableRestart == FALSE) ||
        (Csm_AsymPrivateKeyWrapAsymCurrentConfigId != cfgId)) )
#endif /* #if (CSM_USEPRIORITIES_ENABLED == STD_ON) */
  {
    RetVal = CSM_E_BUSY;
  }
#endif /* #if (CSM_IMMEDIATE_RESTART_ENABLED == STD_OFF) */
  else
  {
    /* !LINKSTO EB_CSM0017_Restart, 1
     */

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    Csm_AsymPrivateKeyWrapAsym_Ret_CallbackNotification = CSM_E_NOT_OK;
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].
      PrimitiveStartFct
      (
        Csm_AsymPrivateKeyWrapAsymConfigurations[cfgId].PrimitiveConfigPtr,
        keyPtr,
        wrappingKeyPtr
      );

    /* !LINKSTO EB_CSM0017_Restart_OK, 1
     */
    if ( RetVal == CSM_E_OK )
    {
      Csm_AsymPrivateKeyWrapAsymIsRunning = TRUE;

      /* !LINKSTO EB_CSMPrio_2, 1 */
      Csm_AsymPrivateKeyWrapAsymCurrentConfigId = cfgId;
#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
      /* !LINKSTO CSM0047, 1
       */
      /* !LINKSTO EB_CSM_SDS_0006,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_AsymPrivateKeyWrapAsymSynchronousMainCall();
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
    }
    else if ( RetVal != CSM_E_BUSY )
    {
      /* !LINKSTO EB_CSM0017_Restart_Error, 2
       * Something went wrong in Cry, e.g. invalid arguments were provided.
       * In this case, the Cry is assumed to have aborted all running services.
       */
      Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;
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
/*----[Csm_AsymPrivateKeyWrapAsymUpdate]----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0749_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapAsymUpdate
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) dataLengthPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0050, 1
   */
  if ( (Csm_AsymPrivateKeyWrapAsymIsRunning       == FALSE) ||
       (Csm_AsymPrivateKeyWrapAsymCurrentConfigId != cfgId)
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
      Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].
      PrimitiveUpdateFct
      (
        dataPtr,
        dataLengthPtr
      );

    if ( RetVal == CSM_E_NOT_OK )
    {
      Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;
    }

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0052,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_AsymPrivateKeyWrapAsymSynchronousMainCall();
    }
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymFinish]----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0750_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapAsymFinish
(
  Csm_ConfigIdType cfgId
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0056, 1
   */
  if ( (Csm_AsymPrivateKeyWrapAsymIsRunning       == FALSE) ||
       (Csm_AsymPrivateKeyWrapAsymCurrentConfigId != cfgId)
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
      Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].
      PrimitiveFinishFct
      (
      );

    if ( CSM_E_NOT_OK == RetVal )
    {
      Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;
    }

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0058,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_AsymPrivateKeyWrapAsymSynchronousMainCall();
      Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;
    }
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}


#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymMainFunction]----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapAsymMainFunction
(
  void
)
{
  if ( Csm_AsymPrivateKeyWrapAsymIsRunning == TRUE )
  {
    /* !LINKSTO CSM0469, 1
     */
    Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].
    PrimitiveMainFct();
  }
}
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymCallbackNotification]--------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0455, 1
 */
/* !LINKSTO CSM0039, 1
 */
FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapAsymCallbackNotification
(
  Csm_ReturnType result
)
{
#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

    Csm_AsymPrivateKeyWrapAsym_Flg_CallbackNotification = TRUE;
    Csm_AsymPrivateKeyWrapAsym_Ret_CallbackNotification = result;

    if (NULL_PTR                                                                                 !=
        Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].CallbackFct
       )
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  {
      /* !LINKSTO EB_CSM_SDS_0003,1 */
      (void) Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].
           CallbackFct(result);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymServiceFinishNotification]---------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0457, 1
 */
FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapAsymServiceFinishNotification
(
  void
)
{
#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

  Csm_AsymPrivateKeyWrapAsym_Flg_ServiceFinishNotification = TRUE;

#else /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

  Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_AsymPrivateKeyWrapAsymInit]------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapAsymInit
(
  void
)
{
  /* !LINKSTO CSM0021, 1
   */
  Csm_AsymPrivateKeyWrapAsymIsRunning = FALSE;
}


/*==================[internal function definitions]===============================================*/

#if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

static FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapAsymSynchronousMainCall
  (void)
{
  Csm_ReturnType returnVal;
  /* !LINKSTO CSM0035, 1
   */
  Csm_AsymPrivateKeyWrapAsym_Flg_CallbackNotification = FALSE;
  Csm_AsymPrivateKeyWrapAsym_Flg_ServiceFinishNotification = FALSE;

  /* !LINKSTO EB_CSM_SDS_0005,1 */
  while ((Csm_AsymPrivateKeyWrapAsym_Flg_CallbackNotification      == FALSE) &&
         (Csm_AsymPrivateKeyWrapAsym_Flg_ServiceFinishNotification == FALSE)
        )
  {
    Csm_AsymPrivateKeyWrapAsymConfigurations[Csm_AsymPrivateKeyWrapAsymCurrentConfigId].
    PrimitiveMainFct();
  }
  /* !LINKSTO EB_CSM_SDS_0007,1 */
  returnVal = Csm_AsymPrivateKeyWrapAsym_Ret_CallbackNotification;
  return returnVal;
}
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>
/*================================================================================================*/

#else  /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_AsymPrivateKeyWrapAsym_EmptyTranslationUnit_t;

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPASYM_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

