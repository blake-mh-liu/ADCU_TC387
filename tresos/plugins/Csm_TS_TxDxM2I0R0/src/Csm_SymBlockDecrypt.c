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
#include <Csm_SymBlockDecrypt.h>
#include <Csm_SymBlockDecryptCfg.h>

/* !LINKSTO EB_CSM0677_02, 1
 */
#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)

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
static FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptSynchronousMainCall
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */



/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/** \brief The run state of the service.
 **/
VAR(boolean, CSM_VAR) Csm_SymBlockDecryptIsRunning = FALSE;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Id of the current configuration.
 **/
VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_SymBlockDecryptCurrentConfigId;

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification return value
 **/
volatile VAR(Csm_ReturnType, CSM_VAR) Csm_SymBlockDecrypt_Ret_CallbackNotification = CSM_E_OK;
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        completely finished the currently computeted service.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_SymBlockDecrypt_Flg_ServiceFinishNotification = FALSE;
/** \brief Synchronous mode callback notification flag used for indicating that the primitive has
 **        finished the current start, updated or finish computation.
 **/
STATIC VAR(boolean, CSM_VAR) Csm_SymBlockDecrypt_Flg_CallbackNotification = FALSE;
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

#if (CSM_SYMBLOCKDECRYPT_RTE_INTERFACE_ENABLED == STD_ON)

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymBlockDecryptStart]---------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0781_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymBlockDecryptStart
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(SymKeyType,       AUTOMATIC, CSM_APPL_DATA) key
)
{
  Std_ReturnType retVal;

  /* Deviation MISRA-1 <START> */
  /* Deviation MISRAC2012-1 <START> */
  retVal = (Std_ReturnType) Csm_SymBlockDecryptStart
                            (
                              pdav0,
                              (P2CONST(Csm_SymKeyType, AUTOMATIC, CSM_APPL_DATA)) key
                            );
  /* Deviation MISRA-1 <STOP> */
  /* Deviation MISRAC2012-1 <STOP> */

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymBlockDecryptUpdate]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0781_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymBlockDecryptUpdate
(
          Csm_ConfigIdType                            pdav0,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) cipherTextBuffer,
          uint32                                      cipherTextLength,
    P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) plainTextBuffer,
    P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) plainTextLength
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_SymBlockDecryptUpdate
                            (
                              pdav0,
                              cipherTextBuffer,
                              cipherTextLength,
                              plainTextBuffer,
                              plainTextLength
                            );

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_RteSymBlockDecryptFinish]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CSM0781_01, 1
 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RteSymBlockDecryptFinish
(
  Csm_ConfigIdType pdav0
)
{
  Std_ReturnType retVal;

  retVal = (Std_ReturnType) Csm_SymBlockDecryptFinish
                            (
                              pdav0
                            );

  return retVal;
}

#endif /* #if (CSM_SYMBLOCKDECRYPT_RTE_INTERFACE_ENABLED == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptStart]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO CSM0187, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptStart
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0046, 1
   */
  if ( cfgId >= (sizeof(Csm_SymBlockDecryptConfigurations   ) /
                 sizeof(Csm_SymBlockDecryptConfigurations[0])
                )
     )
  {
    RetVal = CSM_E_NOT_OK;
  }
  /* !LINKSTO EB_Csm_Immediate_Restart,1 */
#if (CSM_SYMBLOCKDECRYPT_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  /* !LINKSTO EB_CSM0017_Busy, 1
   */
  else
#if (CSM_USEPRIORITIES_ENABLED == STD_ON)
  if ( ((Csm_SymBlockDecryptIsRunning == TRUE)
       /* !LINKSTO EB_CSMPrio, 1 */
       && (
        (Csm_SymBlockDecryptConfigurations[cfgId].CsmSymBlockDecryptUsePriorities == FALSE) ||
        (Csm_SymBlockDecryptConfigurations[cfgId].PrimitiveStartFct !=
         Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].PrimitiveStartFct))
        )
       && ((Csm_SymBlockDecryptConfigurations[cfgId].CsmSymBlockDecryptEnableRestart == FALSE) ||
        (Csm_SymBlockDecryptCurrentConfigId != cfgId)) )
#else
  if ( (Csm_SymBlockDecryptIsRunning == TRUE) &&
       ((Csm_SymBlockDecryptConfigurations[cfgId].CsmSymBlockDecryptEnableRestart == FALSE) ||
        (Csm_SymBlockDecryptCurrentConfigId != cfgId)) )
#endif /* #if (CSM_USEPRIORITIES_ENABLED == STD_ON) */
  {
    RetVal = CSM_E_BUSY;
  }
#endif /* #if (CSM_IMMEDIATE_RESTART_ENABLED == STD_OFF) */
  else
  {
    /* !LINKSTO EB_CSM0017_Restart, 1
     */

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
    Csm_SymBlockDecrypt_Ret_CallbackNotification = CSM_E_NOT_OK;
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

    /* !LINKSTO CSM0506, 1
     */
    RetVal =
      Csm_SymBlockDecryptConfigurations[cfgId].
      PrimitiveStartFct
      (
        Csm_SymBlockDecryptConfigurations[cfgId].PrimitiveConfigPtr,
        keyPtr
      );

    /* !LINKSTO EB_CSM0017_Restart_OK, 1
     */
    if ( RetVal == CSM_E_OK )
    {
      Csm_SymBlockDecryptIsRunning = TRUE;

      /* !LINKSTO EB_CSMPrio_2, 1 */
      Csm_SymBlockDecryptCurrentConfigId = cfgId;
#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
      /* !LINKSTO CSM0047, 1
       */
      /* !LINKSTO EB_CSM_SDS_0006,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymBlockDecryptSynchronousMainCall();
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */
    }
    else if ( RetVal != CSM_E_BUSY )
    {
      /* !LINKSTO EB_CSM0017_Restart_Error, 2
       * Something went wrong in Cry, e.g. invalid arguments were provided.
       * In this case, the Cry is assumed to have aborted all running services.
       */
      Csm_SymBlockDecryptIsRunning = FALSE;
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
/*----[Csm_SymBlockDecryptUpdate]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0192_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) cipherTextPtr,
          uint32                                      cipherTextLength,
    P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) plainTextPtr,
    P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) plainTextLengthPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0050, 1
   */
  if ( (Csm_SymBlockDecryptIsRunning       == FALSE) ||
       (Csm_SymBlockDecryptCurrentConfigId != cfgId)
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
      Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].
      PrimitiveUpdateFct
      (
        cipherTextPtr,
        cipherTextLength,
        plainTextPtr,
        plainTextLengthPtr
      );

    if ( RetVal == CSM_E_NOT_OK )
    {
      Csm_SymBlockDecryptIsRunning = FALSE;
    }

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0052,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymBlockDecryptSynchronousMainCall();
    }
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptFinish]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0023, 1
 */
/* !LINKSTO EB_CSM0199_01, 1
 */
FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptFinish
(
  Csm_ConfigIdType cfgId
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO CSM0056, 1
   */
  if ( (Csm_SymBlockDecryptIsRunning       == FALSE) ||
       (Csm_SymBlockDecryptCurrentConfigId != cfgId)
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
      Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].
      PrimitiveFinishFct
      (
      );

    if ( CSM_E_NOT_OK == RetVal )
    {
      Csm_SymBlockDecryptIsRunning = FALSE;
    }

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
    if (CSM_E_OK == RetVal)
    {
      /* !LINKSTO EB_CSM_SDS_0006,1, CSM0058,1, EB_CSM_SDS_0008,1 */
      RetVal = Csm_SymBlockDecryptSynchronousMainCall();
      Csm_SymBlockDecryptIsRunning = FALSE;
    }
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  }
  return RetVal;
}


#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptMainFunction]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_SymBlockDecryptMainFunction
(
  void
)
{
  if ( Csm_SymBlockDecryptIsRunning == TRUE )
  {
    /* !LINKSTO CSM0469, 1
     */
    Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].
    PrimitiveMainFct();
  }
}
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptCallbackNotification]---------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0455, 1
 */
/* !LINKSTO CSM0039, 1
 */
FUNC(void, CSM_CODE) Csm_SymBlockDecryptCallbackNotification
(
  Csm_ReturnType result
)
{
#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)

    Csm_SymBlockDecrypt_Flg_CallbackNotification = TRUE;
    Csm_SymBlockDecrypt_Ret_CallbackNotification = result;

    if (NULL_PTR                                                                                 !=
        Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].CallbackFct
       )
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */
  {
      /* !LINKSTO EB_CSM_SDS_0003,1 */
      (void) Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].
           CallbackFct(result);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptServiceFinishNotification]----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0457, 1
 */
FUNC(void, CSM_CODE) Csm_SymBlockDecryptServiceFinishNotification
(
  void
)
{
#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)

  Csm_SymBlockDecrypt_Flg_ServiceFinishNotification = TRUE;

#else /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

  Csm_SymBlockDecryptIsRunning = FALSE;

#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_SymBlockDecryptInit]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CSM_CODE) Csm_SymBlockDecryptInit
(
  void
)
{
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymBlockDecryptIsRunning = FALSE;
}


/*==================[internal function definitions]===============================================*/

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)

static FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptSynchronousMainCall
  (void)
{
  Csm_ReturnType returnVal;
  /* !LINKSTO CSM0035, 1
   */
  Csm_SymBlockDecrypt_Flg_CallbackNotification = FALSE;
  Csm_SymBlockDecrypt_Flg_ServiceFinishNotification = FALSE;

  /* !LINKSTO EB_CSM_SDS_0005,1 */
  while ((Csm_SymBlockDecrypt_Flg_CallbackNotification      == FALSE) &&
         (Csm_SymBlockDecrypt_Flg_ServiceFinishNotification == FALSE)
        )
  {
    Csm_SymBlockDecryptConfigurations[Csm_SymBlockDecryptCurrentConfigId].
    PrimitiveMainFct();
  }
  /* !LINKSTO EB_CSM_SDS_0007,1 */
  returnVal = Csm_SymBlockDecrypt_Ret_CallbackNotification;
  return returnVal;
}
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>
/*================================================================================================*/

#else  /* #if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_SymBlockDecrypt_EmptyTranslationUnit_t;

#endif /* #if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

