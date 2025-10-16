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
#include <Csm_SymKeyWrapSym.h>
#include <Csm_SymKeyWrapSymCfg.h>

/* !LINKSTO EB_CSM0677_02, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#if (CSM_SYMKEYWRAPSYM_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

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
static FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyWrapSymSynchronousMainCall
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */



/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/** \brief The run state of the service.
 **/
VAR(boolean, CSM_VAR) Csm_SymKeyWrapSymIsRunning = FALSE;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Id of the current configuration.
 **/
VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_SymKeyWrapSymCurrentConfigId;

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification return value
 **/
volatile VAR(Csm_ReturnType, CSM_VAR) Csm_SymKeyWrapSym_Ret_CallbackNotification = CSM_E_OK;
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        completely finished the currently computeted service.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_SymKeyWrapSym_Flg_ServiceFinishNotification = FALSE;
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        finished the current start, updated or finish computation.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_SymKeyWrapSym_Flg_CallbackNotification = FALSE;
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

#if (CSM_SYMKEYWRAPSYM_RTE_INTERFACE_ENABLED == STD_ON)

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymKeyWrapSymStart]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0795_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymKeyWrapSymStart
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(SymKeyType,       AUTOMATIC, CSM_APPL_DATA) key,
  P2CONST(SymKeyType,       AUTOMATIC, CSM_APPL_DATA) wrappingKey
)
{
  Std_ReturnType retVal;

  /* Deviation MISRA-1 <START> */
  /* Deviation MISRAC2012-1 <START> */
  retVal = (Std_ReturnType) Csm_SymKeyWrapSymStart
                            (
                              pdav0,
                              (P2CONST(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA)) key,
                              (P2CONST(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA)) wrappingKey
                            );
  /* Deviation MISRA-1 <STOP> */
  /* Deviation MISRAC2012-1 <STOP> */

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymKeyWrapSymUpdate]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0795_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymKeyWrapSymUpdate
(
        Csm_ConfigIdType                            pdav0,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) dataBuffer,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) dataLength
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_SymKeyWrapSymUpdate
                            (
                              pdav0,
                              dataBuffer,
                              dataLength
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymKeyWrapSymFinish]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0795_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymKeyWrapSymFinish
(
  Csm_ConfigIdType pdav0
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_SymKeyWrapSymFinish
                            (
                              pdav0
                            );

  return retVal;
}

#endif /* #if (CSM_SYMKEYWRAPSYM_RTE_INTERFACE_ENABLED == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO CSM0739, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyWrapSymStart
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) wrappingKeyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0046, 1
   */
  if ( cfgId >= (sizeof(Csm_SymKeyWrapSymConfigurations   ) /
                 sizeof(Csm_SymKeyWrapSymConfigurations[0])
                )
     )
  {
    RetVal = CSM_E_NOT_OK;
  }
  /* !LINKSTO EB_Csm_Immediate_Restart,1 */
#if (CSM_SYMKEYWRAPSYM_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  /* !LINKSTO EB_CSM0017_Busy, 1
   */
  else
#if (CSM_USEPRIORITIES_ENABLED == STD_ON)
  if ( ((Csm_SymKeyWrapSymIsRunning == TRUE)
       /* !LINKSTO EB_CSMPrio, 1 */
       && (
        (Csm_SymKeyWrapSymConfigurations[cfgId].CsmSymKeyWrapSymUsePriorities == FALSE) ||
        (Csm_SymKeyWrapSymConfigurations[cfgId].PrimitiveStartFct !=
         Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].PrimitiveStartFct))
        )
       && ((Csm_SymKeyWrapSymConfigurations[cfgId].CsmSymKeyWrapSymEnableRestart == FALSE) ||
        (Csm_SymKeyWrapSymCurrentConfigId != cfgId)) )
#else
  if ( (Csm_SymKeyWrapSymIsRunning == TRUE) &&
       ((Csm_SymKeyWrapSymConfigurations[cfgId].CsmSymKeyWrapSymEnableRestart == FALSE) ||
        (Csm_SymKeyWrapSymCurrentConfigId != cfgId)) )
#endif /* #if (CSM_USEPRIORITIES_ENABLED == STD_ON) */
  {
    RetVal = CSM_E_BUSY;
  }
#endif /* #if (CSM_IMMEDIATE_RESTART_ENABLED == STD_OFF) */
  else
  {
    /* !LINKSTO EB_CSM0017_Restart, 1
     */

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    Csm_SymKeyWrapSym_Ret_CallbackNotification = CSM_E_NOT_OK;
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_SymKeyWrapSymConfigurations[cfgId].
      PrimitiveStartFct
      (
        Csm_SymKeyWrapSymConfigurations[cfgId].PrimitiveConfigPtr,
        keyPtr,
        wrappingKeyPtr
      );

    /* !LINKSTO EB_CSM0017_Restart_OK, 1
     */
    if ( RetVal == CSM_E_OK )
    {
      Csm_SymKeyWrapSymIsRunning = TRUE;

      /* !LINKSTO EB_CSMPrio_2, 1 */
      Csm_SymKeyWrapSymCurrentConfigId = cfgId;
#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
      /* !LINKSTO CSM0047, 1
       */
      /* !LINKSTO EB_CSM_SDS_0006,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymKeyWrapSymSynchronousMainCall();
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
    }
    else if ( RetVal != CSM_E_BUSY )
    {
      /* !LINKSTO EB_CSM0017_Restart_Error, 2
       * Something went wrong in Cry, e.g. invalid arguments were provided.
       * In this case, the Cry is assumed to have aborted all running services.
       */
      Csm_SymKeyWrapSymIsRunning = FALSE;
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
/*----[Csm_SymKeyWrapSymUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0740_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyWrapSymUpdate
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) dataLengthPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0050, 1
   */
  if ( (Csm_SymKeyWrapSymIsRunning       == FALSE) ||
       (Csm_SymKeyWrapSymCurrentConfigId != cfgId)
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
      Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].
      PrimitiveUpdateFct
      (
        dataPtr,
        dataLengthPtr
      );

    if ( RetVal == CSM_E_NOT_OK )
    {
      Csm_SymKeyWrapSymIsRunning = FALSE;
    }

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0052,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymKeyWrapSymSynchronousMainCall();
    }
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0741_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyWrapSymFinish
(
  Csm_ConfigIdType cfgId
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0056, 1
   */
  if ( (Csm_SymKeyWrapSymIsRunning       == FALSE) ||
       (Csm_SymKeyWrapSymCurrentConfigId != cfgId)
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
      Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].
      PrimitiveFinishFct
      (
      );

    if ( CSM_E_NOT_OK == RetVal )
    {
      Csm_SymKeyWrapSymIsRunning = FALSE;
    }

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0058,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymKeyWrapSymSynchronousMainCall();
      Csm_SymKeyWrapSymIsRunning = FALSE;
    }
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}


#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymMainFunction]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_SymKeyWrapSymMainFunction
(
  void
)
{
  if ( Csm_SymKeyWrapSymIsRunning == TRUE )
  {
    /* !LINKSTO CSM0469, 1
     */
    Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].
    PrimitiveMainFct();
  }
}
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymCallbackNotification]-----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0455, 1
 */
/* !LINKSTO CSM0039, 1
 */
FUNC(void, CSM_CODE) Csm_SymKeyWrapSymCallbackNotification
(
  Csm_ReturnType result
)
{
#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

    Csm_SymKeyWrapSym_Flg_CallbackNotification = TRUE;
    Csm_SymKeyWrapSym_Ret_CallbackNotification = result;

    if (NULL_PTR                                                                                 !=
        Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].CallbackFct
       )
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  {
      /* !LINKSTO EB_CSM_SDS_0003,1 */
      (void) Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].
           CallbackFct(result);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymServiceFinishNotification]------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0457, 1
 */
FUNC(void, CSM_CODE) Csm_SymKeyWrapSymServiceFinishNotification
(
  void
)
{
#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

  Csm_SymKeyWrapSym_Flg_ServiceFinishNotification = TRUE;

#else /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

  Csm_SymKeyWrapSymIsRunning = FALSE;

#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymKeyWrapSymInit]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_SymKeyWrapSymInit
(
  void
)
{
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymKeyWrapSymIsRunning = FALSE;
}


/*==================[internal function definitions]===============================================*/

#if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)

static FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyWrapSymSynchronousMainCall
  (void)
{
  Csm_ReturnType returnVal;
  /* !LINKSTO CSM0035, 1
   */
  Csm_SymKeyWrapSym_Flg_CallbackNotification = FALSE;
  Csm_SymKeyWrapSym_Flg_ServiceFinishNotification = FALSE;

  /* !LINKSTO EB_CSM_SDS_0005,1 */
  while ((Csm_SymKeyWrapSym_Flg_CallbackNotification      == FALSE) &&
         (Csm_SymKeyWrapSym_Flg_ServiceFinishNotification == FALSE)
        )
  {
    Csm_SymKeyWrapSymConfigurations[Csm_SymKeyWrapSymCurrentConfigId].
    PrimitiveMainFct();
  }
  /* !LINKSTO EB_CSM_SDS_0007,1 */
  returnVal = Csm_SymKeyWrapSym_Ret_CallbackNotification;
  return returnVal;
}
#endif /* #if (CSM_SYMKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>
/*================================================================================================*/

#else  /* #if (CSM_SYMKEYWRAPSYM_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_SymKeyWrapSym_EmptyTranslationUnit_t;

#endif /* #if (CSM_SYMKEYWRAPSYM_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

