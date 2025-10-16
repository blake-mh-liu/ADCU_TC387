/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Dcm.Dsn.File.RoutineControl.Impl,1 */
/* This file contains the implementation of the Diagnostic Service RoutineControl */

/* tasking Deviation List
 *
 *  TASKING-1) Deviated Rule: W549
 *    W549: condition is always true
 *
 *    Reason:
 *    This warning is a false positive. The false condition (which terminates the loop) is reached.
 *    This is proven by the coverage metrics and by the fact that the while loop is not infinite.
 *
 *  TASKING-2) Deviated Rule: W549
 *    W549: condition is always true
 *
 *    Reason:
 *    Condition depends on preprocessor settings that is configuration specific. Under certain configurations
 *    the conditions can be either always true or always false. This does not pose any functional risk.
 */

/*===============================[includes]======================================================*/

#include <Dcm_Trace.h>
#include <TSAutosar.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <Dcm_DspExternal.h>
#include <TSMem.h>

#include <Dcm_Dsp_SvcH_RoutineControl.h>
#include <Dcm_Dsl_SecurityLevelHandler.h>
#if((DCM_DSP_NUM_REQUESTCONTROL_CFG != 0) && (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON))
#include <Dcm_Dsp_SvcH_RequestControlOfOnBoardSysTstComp.h>
#endif

#if (DCM_DSP_USE_SERVICE_0X31 == STD_ON)

/*==================[macro definitions]==========================================================*/

#if (defined DCM_ROUTINE_CONTROL_START)
  #error "DCM_ROUTINE_CONTROL_START is already defined"
#endif
/** \brief Macro for routine control subfunction Start */
#define DCM_ROUTINE_CONTROL_START                        (0x01U)

#if (defined DCM_ROUTINE_CONTROL_STOP)
  #error "DCM_ROUTINE_CONTROL_STOP is already defined"
#endif
/** \brief Macro for routine control subfunction Stop */
#define DCM_ROUTINE_CONTROL_STOP                         (0x02U)

#if (defined DCM_ROUTINE_CONTROL_REQUESTRESULTS)
  #error "DCM_ROUTINE_CONTROL_REQUESTRESULTS is already defined"
#endif
/** \brief Macro for routine control subfunction Request Results */
#define DCM_ROUTINE_CONTROL_REQUESTRESULTS               (0x03U)

#if (defined DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH)
  #error "DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH is already defined"
#endif
/** \brief  Macro for routine control subfunction Request Results */
#define DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH               (0x03U)

#if (defined DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE)
  #error "DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE is already defined"
#endif
/** \brief Macro for size of response header, SubFunction 1 byte and RoutineID 2 bytes */
#define DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE          (0x03U)

#if (defined DCM_ROUTINE_CONTROL_INFOBYTE_SIZE)
  #error "DCM_ROUTINE_CONTROL_INFOBYTE_SIZE is already defined"
#endif
/** \brief Macro for size of InfoByte */
#define DCM_ROUTINE_CONTROL_INFOBYTE_SIZE                (0x08U)

/** \brief Upper 8 bits of the 16 bits RID that are recognized as OBD TIDs.
 **        The range goes from 0xE000 to 0xE1FF */
#if (defined DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0)
  #error "DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0 is already defined"
#endif
#define DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0             (0xE0U)

#if (defined DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1)
  #error "DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1 is already defined"
#endif
#define DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1             (0xE1U)

/** \brief Macros for LockStatus used by RoutineControl service */
#if (defined DCM_TRYING_LOCK)
  #error "DCM_TRYING_LOCK is already defined"
#endif
#define DCM_TRYING_LOCK                                  (0x00U)

#if (defined DCM_EXECUTING_ROUTINECONTROL_SERVICE)
  #error "DCM_EXECUTING_ROUTINECONTROL_SERVICE is already defined"
#endif

#define DCM_EXECUTING_ROUTINECONTROL_SERVICE             (0x01U)

/** \brief Macro for checking if a routine is in the OBDOnUDS (0xE000- 0xE1FF) range
 **
 ** \inputValue RoutineIdHighByte The high byte of the routine identifier
 **
 ** \returns TRUE          Routine identifier is in the OBDOnUDS range
 ** \returns FALSE         Routine identifier is not in the OBDOnUDS range
 */
#if (defined DCM_ROUTINE_IS_IN_OBD_ON_UDS_RANGE)
  #error "DCM_ROUTINE_IS_IN_OBD_ON_UDS_RANGE is already defined"
#endif
#define DCM_ROUTINE_IS_IN_OBD_ON_UDS_RANGE(RoutineIdHighByte) \
          (((RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0) || \
            (RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1)) ? TRUE : FALSE)

/** \brief Macro to determine whether RoutineControl (0x31) UDS service is able to read TIDs
 **        via OBD service $08.
 */
#if (defined DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM)
  #error "DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM is already defined"
#endif

#if((DCM_DSP_NUM_REQUESTCONTROL_CFG != 0) && \
    (DCM_DSP_ENABLE_OBD_MIRROR == STD_ON))

#define DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM                         STD_ON

#else

#define DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM                         STD_OFF

#endif

/** \brief Macros for routine processing types:
 **
 **  DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND           - Routine not supported.
 **  DCM_ROUTINE_PROCESS_AS_UDS_FOUND               - Routine processed as UDS
 **  DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY        - Routine processed as OBD availability
 **  DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY    - Routine processed as OBD non availability
 **  DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY - Routine processed as OBDOnUDS availability
 */

/** \brief The requested routine is not supported. */
#if (defined DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND)
  #error "DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND is already defined"
#endif
#define DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND                                  (0xFFU)

/** \brief The requested routine shall be processed as an UDS routine,
 **        by invoking the respective callout or client-server interface.
 */
#if (defined DCM_ROUTINE_PROCESS_AS_UDS_FOUND)
  #error "DCM_ROUTINE_PROCESS_AS_UDS_FOUND is already defined"
#endif
#define DCM_ROUTINE_PROCESS_AS_UDS_FOUND                                      (0x01U)

#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)

/** \brief The requested routine shall be processed as an OBD availability routine.
 **        A bitmap of the supported TIDs and RIDs (if configuration parameter
           DcmDspRidAvailabilityCalculation is enabled) shall be calculated.
 */
#if (defined DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY)
  #error "DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY is already defined"
#endif
#define DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY                               (0x02U)

/** \brief The requested routine shall be processed as an OBD non-availability routine.
 **        The OBD sub-system shall try to read the mirrored TID identifier
 **        equal with the least significant byte of the requested routine identifier.
 */
#if (defined DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY)
  #error "DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY is already defined"
#endif
#define DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY                           (0x03U)

#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */

#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)

/** \brief The requested routine shall be processed as an OBDOnUDS availability routine.
 **        A bitmap of the supported RIDs shall be calculated.
 */
#if (defined DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY)
  #error "DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY is already defined"
#endif
#define DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY                        (0x04U)

#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

/*==================[type definitions]===========================================================*/

/** \brief This type contains the information needed while processing service
* RoutineControl(0x31) */
typedef struct
{

  /** \brief This variable holds the sub-service handler, extracted from
   **        RoutineControl(0x31) request in the DCM_INITIAL state.
   **        This variable is used in each call of the RoutineControl handler to call the
   **        sub-service handler.
   */
  Dcm_GenericServiceHandlerType SubServiceHandler;

#if (DCM_NUM_ROUTINES > 0)

  /** \brief This variable holds the configuration index of the current processing routine.
   */
  uint16 CurrentRoutineConfigIndex;

#endif /* #if ((DCM_NUM_ROUTINES > 0) */

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

  /** \brief This variable is used to control access to RoutineControl resources.
   */
  Dcm_MutexType RoutineOperationsLock;

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)

  /** \brief This variable is used to identify if there it was requested
   *         a routine which is not supported (not configured or not used).
   *         It is set as TRUE if DcmDspRoutineEnableDefaultInterfaces
   *         configuration parameter is set to TRUE and an unconfigured or an unused routine
   *         is found.
   *         It is set to FALSE at initialization or after the Default Interfaces
   *         (Dcm_DefaultRoutineStart,Dcm_DefaultRoutineStop or Dcm_DefaultRoutineRequestRoutineResults)
   *         are called from application.
   */
  boolean UnsupportedRoutine;

#endif /*#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)*/

}
Dcm_RoutineControlInfoContextType;

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief This function is used to execute the RoutineControl service functionality
           after the RoutineInfoContext has been locked.
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send a "response pending" immediately
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_ServiceExecution(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

/** \brief UDS service 0x31 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send a "response pending" immediately
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

/** \brief UDS service 0x31 internal service handler
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send a "response pending" immediately
 */

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#if (DCM_NUM_ROUTINES > 0)
/** \brief This function searches the RoutineId in the configuration and gets the routine
 **        configuration index. In this function binary search approach is used,
 **        in order to reduce the searching time by dividing the searching scope into two sets,
 **        first checking in which set the routine resides, continuing the search within that set.
 **
 ** \param[in]    RoutineIdHighByte MSB (most significant byte) of the routine identifier
 ** \param[in]    RoutineIdLowByte LSB (least significant byte) of the routine identifier
 **
 ** \retval TRUE          Routine was found in the configuration
 ** \retval FALSE         Routine was not found in the configuration
 */
STATIC FUNC(boolean, DCM_CODE) Dcm_Dsp_RoutineControl_SetCurrentRoutine(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte);

/** \brief This function checks if the routine is allowed to be executed in the current session
 **
 ** \retval TRUE          Routine is allowed in the current session
 ** \retval FALSE         Routine is not allowed in the current session
 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSession(void);

/** \brief This function checks if the routine is allowed to be executed in the current security level
 **
 ** \retval TRUE          Routine is allowed in the current security level
 ** \retval FALSE         Routine is not allowed in the current security level
 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSecurityLevel(void);

#endif /*#if (DCM_NUM_ROUTINES > 0)*/

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
/** \brief This function checks if the routine is allowed to be executed in the current mode condition
 **
 ** \retval TRUE          Routine can be executed in the current mode condition
 ** \retval FALSE         Routine can not be executed in the current mode condition
 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_ModeRuleResult(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) CurrentNrc);
#endif /*DCM_MODEDECLARATION_SUPPORT */

#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
/** \brief This function calls a default Application function for every requested routine
 **        which is not supported and handles the API function result.
 **
 ** \param[in]    OpStatus Operation mode of the function.
 ** \param[in]    SubServiceID SubService for the unsupported routine.
 ** \param[out]   pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_UnsupportedRoutineHandler(
  uint8 SubServiceID,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /*(DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)*/

#if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
     ((DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) || \
      (DCM_NUM_ROUTINES > 0)))
/** \brief This function is used to handle byte shifting of the routine response info in case
 **         there is added one more byte to the response using the application interface
 **         Dcm_AddRoutineInfoByte
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval NONE
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
               ((DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) || \
                 (DCM_NUM_ROUTINES > 0))) */

/** \brief This function is used to initialize the Dcm_RoutineControlInfoContextType
 **
 ** \param[inout] RoutineControlContextPtr Pointer to the routine context to be initialized
 **
 ** \retval NONE
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_InfoContextInit(
  P2VAR(Dcm_RoutineControlInfoContextType, AUTOMATIC, DCM_VAR) RoutineControlContextPtr);

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

/** \brief This function is used to switch the Dcm_RoutineControlContextPtr
 **        in order to point at the UDS context (Dcm_RoutineControlUDSContext)
 **        or OBD context (Dcm_RoutineControlOBDContext)
 **
 ** \param[inout] RoutineIdHighByte MSB (most significant byte) of the routine identifier
 **
 ** \retval NONE
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SetContextPointer(
  uint8 RoutineIdHighByte);

/** \brief Function to lock the routine context
 **
 **
 ** \retval DCM_E_OK                Routine context successfully locked
 ** \retval DCM_E_RESOURCE_LOCKED   Routine context locked and not available
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_LockService(void);

/** \brief Function to unlock the routine context after it was locked
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_UnlockService(void);

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

#if (DCM_NUM_ROUTINES > 0)
#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
/** \brief Function to check the configured routines in the OBDonUDS range (0xE000 - 0xE1FF).
 **        Function does not look through all configured routines, only routines that are configured
 **        in the OBDonUDS range (0xE000 - 0xE1FF).
 **
 ** \param[in]    RequestedRoutineIdHighByte MSB (most significant byte) of the routine identifier
 ** \param[in]    RequestedRoutineIdLowByte LSB (least significant byte) of the routine identifier
 ** \param[inout] ResponseBuffer pointer to the response buffer
 **
 ** \retval True    At least one supported routine was found
 ** \retval False   No supported routine was found
 */
STATIC FUNC(boolean, DCM_CODE) Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability(
  uint8 RequestedRoutineIdHighByte,
  uint8 RequestedRoutineIdLowByte,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) ResponseBuffer);

#endif /* (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */
#endif /* #if (DCM_NUM_ROUTINES > 0) */

#if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
     (((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && \
       (DCM_NUM_ROUTINES > 0))|| \
      (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)))

/** \brief Function to add the InfoByte in the diagnostic response
 **        for the following routine processing types:
 **         - DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY
 **         - DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY
 **         - DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_OBDOnUDS_AddInfoByte(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#endif /* #if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
               (((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && \
                (DCM_NUM_ROUTINES > 0))|| \
               (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON))) */

/** \brief Function to check the requested routine identifier and determine the routine type:
 **
 ** \param[in]    RequestedRoutineIdHighByte MSB (most significant byte) of the routine identifier
 ** \param[in]    RequestedRoutineIdLowByte LSB (least significant byte) of the routine identifier
 **
 ** \retval  DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND           - Routine not supported.
 ** \retval  DCM_ROUTINE_PROCESS_AS_UDS_FOUND               - Routine processed as UDS
 ** \retval  DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY        - Routine processed as OBD availability
 ** \retval  DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY    - Routine processed as OBD availability
 ** \retval  DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY - Routine processed as OBDOnUDS availability
 */
STATIC FUNC(uint8, DCM_CODE) Dcm_Dsp_RoutineControl_DetermineRoutineType(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte);

#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
/** \brief Function for processing a routine as an OBD availability, function shall look over
 **        the supported TIDs and RIDs (if configuration parameter
 **        DcmDspRidAvailabilityCalculation is enabled) in the requested availability range in order
 **        to create a bitmap and send it as a positive response, in case neither TIDs and RIDs
 **        are not supported in the requested availability range, the function shall
 **        send a 0x31(requestOutRange) NRC.
 **
 ** \param[in]    RequestedRoutineIdHighByte MSB (most significant byte) of the routine identifier
 ** \param[in]    RequestedRoutineIdLowByte LSB (least significant byte) of the routine identifier
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier
 **
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineAsOBDAvailability(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */

#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
/** \brief Function for processing a routine as an UDS availability, function shall look over
 **        the supported RIDs in the requested availability range in order to create a bitmap and
 **        send it as a positive response, in case neither TIDs and RIDs are not supported
 **        in the requested availability range, the function shall send a 0x31(requestOutRange) NRC.
 **
 ** \param[in]    RequestedRoutineIdHighByte MSB (most significant byte) of the routine identifier
 ** \param[in]    RequestedRoutineIdLowByte LSB (least significant byte) of the routine identifier
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier
 **
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineAsUDSAvailability(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

#if ((DCM_NUM_ROUTINES > 0U) || \
     (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON))
/** \brief Function for processing a routine as UDS, function shall extract the sub-service from the
 **        diagnostic request message and call the respective sub-service handler (Start/Stop/RequestResults)
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier
 **
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineViaUDSInterface(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);
#endif /* #if ((DCM_NUM_ROUTINES > 0U) || \
               (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)) */
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[external constants declarations]============================================*/

/*===================[internal constants declarations]===========================================*/

/*==================[external data declarations]=================================================*/

/*==================[internal data declarations]=================================================*/

#if (((DCM_NUM_ROUTINES > 0U) && \
      (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)) || \
      (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON))

#define DCM_START_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

/* If at least one routine is configured */
#if ((DCM_NUM_ROUTINES > 0U) && (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006))

/** \brief Array holding the status of each routine. If the NRC policy ISOVersion 2006 is selected,
 *         this array is used to determine if a requested routine is started.
 *         The index of Dcm_DspRoutineStatus array corresponds to the index from Dcm_DspRoutineConfig
 *         array that contains the routine configuration.
 */
STATIC VAR(uint8, DCM_CONST) Dcm_RoutineControl_RoutineStatus[DCM_NUM_ROUTINES];

#endif /*#if((DCM_NUM_ROUTINES > 0U) &&
             (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)) */

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

/** \brief This variable holds if the RoutineControl service has locked
 **        the RoutineControlOperations unit.
 ** This variable can have the following states:
 ** DCM_TRYING_LOCK                       - The RoutineControlOperations is not locked by
 **                                         RoutineControl (0x31) service
 ** DCM_EXECUTING_ROUTINECONTROL_SERVICE  - The RoutineControlOperations is locked by
 **                                         RoutineControl (0x31) service
 */
STATIC VAR(uint8, DCM_CONST) Dcm_RoutineControl_LockStatus[DCM_NUM_UDS_STACKS];

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

#define DCM_STOP_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

#endif /* #if (((DCM_NUM_ROUTINES > 0U) &&
                (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)) ||
                (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)) */

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/** \brief Dcm_RoutineControlUDSContext is used to hold information regarding the processing of
 *  an UDS routine.
 *
 *  Rationale for mapping Dcm_RoutineControlUDSContext and Dcm_RoutineControlOBDContext
 *  to CLEARED memory section, used for not explicitly initialized variables.
 *  Members of Dcm_RoutineControlContext are initialized and accessed as described below:
 *  SubServiceHandler: Initialized in Dcm_Dsp_RoutineControl_SvcStart() before being accessed
 *                     from Dcm_Dsp_RoutineControl_SvcCont().
 *
 *  CurrentRoutineConfigIndex: Initialized in Dcm_Dsp_RoutineControl_SetCurrentRoutine() before
 *                             being accessed from
 *                             Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSession().
 *
 *  RoutineOperationsLock: Initialized in Dcm_Dsp_RoutineControl_InfoContextInit() before being
 *                         accessed from Dcm_Dsp_RoutineControl_SvcH().
 *  UnsupportedRoutine: Initialized in Dcm_Dsp_RoutineControl_SvcStart() before being
 *                      accessed from:
 *                       * Dcm_Dsp_RoutineControl_StartRoutine_SSvcH()
 *                       * Dcm_Dsp_RoutineControl_StopRoutine_SSvcH()
 *                       * Dcm_Dsp_RoutineControl_RequestResults_SSvcH()
 */
STATIC VAR(Dcm_RoutineControlInfoContextType, DCM_VAR) Dcm_RoutineControlUDSContext;

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

/** \brief Dcm_RoutineControlOBDContext is used to hold information regarding the processing of
 *  an OBD routine.
 */
STATIC VAR(Dcm_RoutineControlInfoContextType, DCM_VAR) Dcm_RoutineControlOBDContext;

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

/** \brief Dcm_RoutineControlContextPtr is used as a switch between UDS and OBD contexts.
 */
STATIC P2VAR(Dcm_RoutineControlInfoContextType, AUTOMATIC, DCM_VAR) Dcm_RoutineControlContextPtr;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* Initializes the control structures of all Routine elements used for the
   RoutineControl (0x31) service handler */
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.Initialization,1 */
FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_Init(void)
{
#if ((DCM_NUM_ROUTINES > 0U) && (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006))

  /* Initialize array holding the status information of each routine */
  TS_MemSet(Dcm_RoutineControl_RoutineStatus,DCM_ROUTINE_INACTIVE,DCM_NUM_ROUTINES);

#endif /* #if ((DCM_NUM_ROUTINES > 0U) &&
               (DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)) */

  /* Initialize UDS routine context */
  Dcm_Dsp_RoutineControl_InfoContextInit(&Dcm_RoutineControlUDSContext);

  /* Initialize routine context pointer */
  Dcm_RoutineControlContextPtr = NULL_PTR;

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

  /* Initialize array holding the lock status information of stack */
  TS_MemSet(Dcm_RoutineControl_LockStatus,DCM_TRYING_LOCK,DCM_NUM_UDS_STACKS);

  /* Initialize OBD routine context */
  Dcm_Dsp_RoutineControl_InfoContextInit(&Dcm_RoutineControlOBDContext);

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.SvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

  uint8_least StackIndex = 0U;
  boolean StackIndexFound = FALSE;

  /* Get protocol index */
  Dcm_ProtocolIndexType ProtocolIndex = Dcm_Dsl_Supervisor_GetProcessingProtocolIndex(
                          DCM_RX_CONNECTION_ID_FROM_RXPDUID(pMsgContext->dcmRxPduId), DCM_EXTERNAL);

  /* Get protocol configuration for current HSM instance */
  CONSTP2CONST(Dcm_ProtocolConfigType, AUTOMATIC, DCM_CONST) CurProtocolConfig =
                                                                &DCM_PROTOCOL_CONFIG(ProtocolIndex);

  /* Get stack number */
  Dcm_ProtocolStackNumberType StackNumber = CurProtocolConfig->StackNumber;

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

  DBG_DCM_DSP_ROUTINECONTROL_SVCH_ENTRY(OpStatus,pMsgContext);

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

  while ((StackIndex < DCM_NUM_UDS_STACKS) && (StackIndexFound == FALSE))
  {
    if (Dcm_StackContextIndex[StackIndex] == StackNumber)
    {
      StackIndexFound = TRUE;
    }
    else
    {
      StackIndex++;
    }
  }

  switch(Dcm_RoutineControl_LockStatus[StackIndex])
  {
    case DCM_TRYING_LOCK:
    {
      if((OpStatus != DCM_CANCEL) &&
         (OpStatus != DCM_CONFIRMED_OK) &&
         (OpStatus != DCM_CONFIRMED_NOK))
      {
        /* Ensure ServiceProcessStatus is either DCM_INITIAL or DCM_PENDING,
         * expectation is when trying to get the lock, the SvcH shall be call with OpStatus set to
         * DCM_INITIAL, or in case the SvcH could not get the lock from the first try,
         * it shall try again with OpStatus set to DCM_PENDING. */
        DCM_PRECONDITION_ASSERT((OpStatus == DCM_INITIAL) ||
                                (OpStatus == DCM_PENDING), DCM_INTERNAL_API_ID);

        /* !LINKSTO Dcm.EB.RoutineControl.ISO2013.NRCsOrder,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.ISO2006.NRCsOrder,1 */
        /* !LINKSTO Dcm.Dsn.IB.RoutineControl.NRCsOrder.ISO2006,1 */
        /* !LINKSTO Dcm.Dsn.IB.RoutineControl.NRCsOrder.ISO2013,1 */
        /* Check minimal request length */
        if (pMsgContext->reqDataLen < DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.MinimalLength.NRC0x13,2 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
          ServiceProcessStatus = DCM_E_DONE;
        }
        else
        {
          Std_ReturnType LockStatus = DCM_E_RESOURCE_LOCKED;

          /* Set the Dcm_RoutineControlContextPtr, requestData contains the subServiceId
             as the ExtractSubServiceHandler has not been yet called */
          Dcm_Dsp_RoutineControl_SetContextPointer(pMsgContext->reqData[1U]);

          /* Retrieve lock status of the context */
          LockStatus = Dcm_Dsp_RoutineControl_LockService();

          /* Check the status of the context lock */
          if (LockStatus == DCM_E_RESOURCE_LOCKED)
          {
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsPending.Postpone,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsPending.Postpone,1 */
            ServiceProcessStatus = DCM_E_PENDING;
          }
          else
          {
            DCM_POSTCONDITION_ASSERT(LockStatus == DCM_E_OK, DCM_INTERNAL_API_ID);

            /* Set LockStatus to DCM_EXECUTING_ROUTINECONTROL_SERVICE */
            Dcm_RoutineControl_LockStatus[StackIndex] = DCM_EXECUTING_ROUTINECONTROL_SERVICE;

            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.CSOperation.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.InvokedCallout.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotUsed.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.OBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.NewNonOBDonUDSRoutine.NonOBDonUDSRoutineAlreadyRunningOnDifferentStack.RoutineNotConfigured.DefaultRoutines.ReturnsDifferentThenPending.ProcessInParallel,1 */

            /* Call ServiceExecution */
            ServiceProcessStatus = Dcm_Dsp_RoutineControl_ServiceExecution(DCM_INITIAL, pMsgContext);
          }
        }
      }
      /* SvcH is called first with OpStatus DCM_CANCEL, to avoid calling
         Dcm_Dsp_RoutineControl_ServiceExecution without first initializing
         the Dcm_RoutineControlContextPtr */
      else if (OpStatus == DCM_CANCEL)
      {
        ServiceProcessStatus = DCM_E_DONE;
      }
      else
      {
        /* Call ServiceExecution */
        ServiceProcessStatus = Dcm_Dsp_RoutineControl_ServiceExecution(OpStatus, pMsgContext);
      }
    }
    break;

    case DCM_EXECUTING_ROUTINECONTROL_SERVICE:
    {
      /* Set the Dcm_RoutineControlContextPtr, requestData does not contain the subServiceId
         as the ExtractSubServiceHandler has been called */
      Dcm_Dsp_RoutineControl_SetContextPointer(pMsgContext->reqData[0U]);

      /* Call ServiceExecution */
      ServiceProcessStatus = Dcm_Dsp_RoutineControl_ServiceExecution(OpStatus,pMsgContext);
    }
    break;

    /* CHECK: NOPARSE */
    default:
    {
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_SVCID_ROUTINECONTROL);
      ServiceProcessStatus = DCM_E_DONE;
    }
    break;
    /* CHECK: PARSE */
  }

  /* Ensure ServiceProcessStatus is different than DCM_E_ABORT */
  DCM_PRECONDITION_ASSERT(ServiceProcessStatus != DCM_E_ABORT, DCM_INTERNAL_API_ID);

  /* Check if processing is finished and release the locks,
   * When SvcH is called with OpStatus set to either DCM_CONFIRMED_OK or DCM_CONFIRMED_NOK,
   * the processing of the service is expected to be finished and state of the locks to be unlocked,
   * no need for them to be unlocked, if try to unlock an already unlocked mutex, it will result
   * in reaching a DET error from Dcm_Internal_ReleaseLock() function. */
  if (
      (((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING) || (OpStatus == DCM_CANCEL) || (OpStatus == DCM_FORCE_RCRRP_OK)) &&
       (Dcm_RoutineControl_LockStatus[StackIndex] == DCM_EXECUTING_ROUTINECONTROL_SERVICE) &&
       (ServiceProcessStatus == DCM_E_DONE))
      )
  {
    /* Release the locks */
    Dcm_RoutineControl_LockStatus[StackIndex] = DCM_TRYING_LOCK;
    Dcm_Dsp_RoutineControl_UnlockService();

    /* Reset the Dcm_RoutineControlContextPtr */
    Dcm_RoutineControlContextPtr = NULL_PTR;
  }

#else

  /* Set the Dcm_RoutineControlContextPtr to point the UDS context */
  Dcm_RoutineControlContextPtr = &Dcm_RoutineControlUDSContext;

  /* Call ServiceExecution */
  ServiceProcessStatus = Dcm_Dsp_RoutineControl_ServiceExecution(OpStatus, pMsgContext);

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

  DBG_DCM_DSP_ROUTINECONTROL_SVCH_EXIT(ServiceProcessStatus,OpStatus,pMsgContext);

  return ServiceProcessStatus;
}

#if((DCM_NUM_ROUTINES > 0) || (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON))
/* !LINKSTO Dcm.EB.RoutineControl.SubFunction.StartRoutine,1 */
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.StartRoutine.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_StartRoutine_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

#if (DCM_NUM_ROUTINES > 0)
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;
  Std_ReturnType RoutineSubfunctionResult = E_NOT_OK;
#endif /* #if (DCM_NUM_ROUTINES > 0) */
#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
  /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnconfiguredRoutine.Start.InitialCall,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnusedRoutine.Start.InitialCall,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.UnconfiguredOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.ConfiguredOBDRID.UnusedOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
  /* Verify if an unsupported routine is requested */
  if(TRUE == Dcm_RoutineControlContextPtr->UnsupportedRoutine)
  {
    /* Call the UnsupportedRoutineHandler with Start sub-function */
    ServiceProcessStatus = Dcm_Dsp_RoutineControl_UnsupportedRoutineHandler(DCM_ROUTINE_CONTROL_START,
                                                                            OpStatus,
                                                                            pMsgContext);
  }
  else
#endif /* #if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) */
  {
#if (DCM_NUM_ROUTINES > 0)
    /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.InvokeCalloutXXX_Start,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.InvokeCalloutXXX_Start,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.InvokeCSOperationXXX_Start,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.InvokeCSOperationXXX_Start,2 */
    /* Call function handler for request to application to start a routine */
    RoutineSubfunctionResult = Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex].StartFncHandler(
        OpStatus, pMsgContext, &ErrorCode);

    if(OpStatus != DCM_CANCEL)
    {
      switch (RoutineSubfunctionResult)
      {
        case DCM_E_NOT_OK:
        {
          if (ErrorCode != 0x00U)
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.ReturnNOK.DiffNRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.ReturnNOK.DiffNRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsNotOk.TransmitNRC,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
          }
          else
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.ReturnNOK.NRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.ReturnNOK.NRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsNotOk.TransmitNRC0x22,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          }
          ServiceProcessStatus = DCM_E_DONE;
        }
        break;

        case DCM_E_OK:
        {
#if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)
          Dcm_RoutineControl_RoutineStatus[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex] = DCM_ROUTINE_STARTED;
#endif /* #if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006) */

          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsOk.PositiveResponse,1 */
          /* If the routine was successful, write the sub-function and the routine Id in the response */
          pMsgContext->resData[0U] = DCM_ROUTINE_CONTROL_START;
          pMsgContext->resData[1U] = pMsgContext->reqData[0U];
          pMsgContext->resData[2U] = pMsgContext->reqData[1U];
#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
        /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StartRoutine.AddRoutineInfoByte.Call,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsOk.InvokeAddInfoByte,1 */
        Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(pMsgContext);
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.ReturnOK.DiffNRC0x00,3 */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.ReturnOK.DiffNRC0x00,3 */
          ServiceProcessStatus = DCM_E_DONE;
        }
        break;

#if (DCM_ROUTINECONTROL_USE_RTE == STD_ON)
        case DCM_E_NO_DATA:
        {
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.ReturnNoData,1 */
          ServiceProcessStatus = DCM_E_PENDING;
        }
        break;
#endif /*(DCM_ROUTINECONTROL_USE_RTE == STD_ON)*/

        case DCM_E_PENDING:
        case DCM_E_FORCE_RCRRP:
        {
          /* For DCM_E_PENDING and DCM_E_FORCE_RCRRP return the respective value */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.ReturnForceRCRRP,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.ReturnForceRCRRP,1 */
          ServiceProcessStatus = RoutineSubfunctionResult;
        }
        break;

        default:
        {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.Unknown.ReturnValue.Det,3 */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.Unknown.ReturnValue.Det,3 */
          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsUnsupportedCode.DET,1 */
          DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLSTART, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.Callout.Unknown.ReturnValue,4 */
          /* !LINKSTO Dcm.EB.RoutineControl.XxxStart.CS.Unknown.ReturnValue,4 */
          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          ServiceProcessStatus = DCM_E_DONE;
        }
        break;
      }
    }
    else
    {
      ServiceProcessStatus = DCM_E_DONE;
    }
#endif /*#if (DCM_NUM_ROUTINES > 0)*/
  }
  return ServiceProcessStatus;
}

/* !LINKSTO Dcm.EB.RoutineControl.SubFunction.StopRoutine,1 */
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.StopRoutine.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_StopRoutine_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

#if (DCM_NUM_ROUTINES > 0)
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;
#endif /*#if (DCM_NUM_ROUTINES > 0)*/
#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
  /* Verify if an unsupported routine is requested */
  if(TRUE == Dcm_RoutineControlContextPtr->UnsupportedRoutine)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnconfiguredRoutine.Stop.InitialCall,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnusedRoutine.Stop.InitialCall,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.UnconfiguredOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.ConfiguredOBDRID.UnusedOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2*/
    /* Call the UnsupportedRoutineHandler with Stop sub-function */
    ServiceProcessStatus = Dcm_Dsp_RoutineControl_UnsupportedRoutineHandler(DCM_ROUTINE_CONTROL_STOP,
                                                                            OpStatus,
                                                                            pMsgContext);
  }
  else
#endif /* #if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) */
  {
#if (DCM_NUM_ROUTINES > 0)
    /* Get pointer to routine configuration table  */
    P2CONST(Dcm_DspRoutineServicesType, AUTOMATIC, DCM_CONST) CurrentRoutineConfig
      = &Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex];

    if (OpStatus == DCM_INITIAL)
    {
      if (CurrentRoutineConfig->StopFncHandler == NULL_PTR)
      {
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspStopRoutineSupported,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.UnconfiguredSubFunction.TransmitNRC0x12,2 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
        ServiceProcessStatus = DCM_E_DONE;
      }
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.ISO2013,1 */
#if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)
      else
      {
        if (Dcm_RoutineControl_RoutineStatus[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex] != DCM_ROUTINE_STARTED)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.ISO2006.NRC0x24,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
          ServiceProcessStatus = DCM_E_DONE;
        }
      }
#endif /* #if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006) */
    }

    /* If the processing was not previously terminated by an error */
    if (ServiceProcessStatus != DCM_E_DONE)
    {
      Std_ReturnType RoutineSubfunctionResult = E_NOT_OK;

      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.InvokeCSOperationXXX_Stop,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.InvokeCSOperationXXX_Stop,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.SubFunctionConfigured.InvokeCalloutXXX_Stop,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.SubFunctionConfigured.InvokeCalloutXXX_Stop,2 */
      /* Call function handler for request to application to stop a routine */
      RoutineSubfunctionResult =
        CurrentRoutineConfig->StopFncHandler(OpStatus, pMsgContext, &ErrorCode);

      if(OpStatus != DCM_CANCEL)
      {
        switch (RoutineSubfunctionResult)
        {
          case DCM_E_NOT_OK:
          {
            if (ErrorCode != 0x00U)
            {
              /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.ReturnNOK.DiffNRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.ReturnNOK.DiffNRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsNotOk.TransmitNRC,1 */
              Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
            }
            else
            {
              /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.ReturnNOK.NRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.ReturnNOK.NRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsNotOk.TransmitNRC0x22,1 */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            }
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;

          case DCM_E_OK:
          {
#if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)
            Dcm_RoutineControl_RoutineStatus[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex] = DCM_ROUTINE_STOPPED;
#endif /* #if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006) */

            /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsOk.PositiveResponse,1 */
            /* If the routine was successful, write the subfunction and the routine Id in the response */
            pMsgContext->resData[0U] = DCM_ROUTINE_CONTROL_STOP;
            pMsgContext->resData[1U] = pMsgContext->reqData[0U];
            pMsgContext->resData[2U] = pMsgContext->reqData[1U];
#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
          /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StopRoutine.AddRoutineInfoByte.Call,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsOk.InvokeAddInfoByte,1 */
          Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(pMsgContext);
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */

            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.ReturnOK.DiffNRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.ReturnOK.DiffNRC0x00,3 */
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;

#if (DCM_ROUTINECONTROL_USE_RTE == STD_ON)
          case DCM_E_NO_DATA:
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.ReturnNoData,1 */
            ServiceProcessStatus = DCM_E_PENDING;
          }
          break;
#endif /*(DCM_ROUTINECONTROL_USE_RTE == STD_ON)*/

          case DCM_E_PENDING:
          case DCM_E_FORCE_RCRRP:
          {
            /* For DCM_E_PENDING and DCM_E_FORCE_RCRRP return the respective value */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.ReturnForceRCRRP,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.ReturnForceRCRRP,1 */
            ServiceProcessStatus = RoutineSubfunctionResult;
          }
          break;

          default:
          {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.Unknown.ReturnValue.Det,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.Unknown.ReturnValue.Det,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsUnsupportedCode.DET,1 */
            DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLSTOP, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.Callout.Unknown.ReturnValue,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxStop.CS.Unknown.ReturnValue,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;
        }
      }
      else
      {
        ServiceProcessStatus = DCM_E_DONE;
      }
    }
#endif /*#if (DCM_NUM_ROUTINES > 0)*/
  }
  return ServiceProcessStatus;
}

/* !LINKSTO Dcm.EB.RoutineControl.SubFunction.RequestsRoutineResults,1 */
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.RequestResultsRoutine.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_RequestResults_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

#if (DCM_NUM_ROUTINES > 0)
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;
#endif /*#if (DCM_NUM_ROUTINES > 0)*/
#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
  /* Verify if an unsupported routine is requested */
  if(TRUE == Dcm_RoutineControlContextPtr->UnsupportedRoutine)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnconfiguredRoutine.RequestResults.InitialCall,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnusedRoutine.RequestResults.InitialCall,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.UnconfiguredOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.ConfiguredOBDRID.UnusedOBDRID.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Enabled.InvokeDefaultInterface,2 */
    /* Call the UnsupportedRoutineHandler with RequestResults sub-function */
    ServiceProcessStatus = Dcm_Dsp_RoutineControl_UnsupportedRoutineHandler(DCM_ROUTINE_CONTROL_REQUESTRESULTS,
                                                                            OpStatus,
                                                                            pMsgContext);
  }
  else
#endif /* #if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) */
  {
#if (DCM_NUM_ROUTINES > 0)
    /* get pointer to routine configuration table  */
    P2CONST(Dcm_DspRoutineServicesType, AUTOMATIC, DCM_CONST) CurrentRoutineConfig
      = &Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex];

    if (OpStatus == DCM_INITIAL)
    {
      if (CurrentRoutineConfig->RequestResultsFncHandler == NULL_PTR)
      {
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRequestResultsRoutineSupported,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.UnconfiguredSubFunction.TransmitNRC0x12,2 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
        ServiceProcessStatus = DCM_E_DONE;
      }
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.ISO2013,1 */
#if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006)
      else
      {
        if (Dcm_RoutineControl_RoutineStatus[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex] == DCM_ROUTINE_INACTIVE)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.ISO2006.NRC0x24,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
          ServiceProcessStatus = DCM_E_DONE;
        }
      }
#endif /* #if(DCM_NRC_POLICY_ISO_VERSION == DCM_ISO14229_2006) */
    }

    /* If the processing was not previously terminated by an error */
    if (ServiceProcessStatus != DCM_E_DONE)
    {
      Std_ReturnType RoutineSubfunctionResult = E_NOT_OK;

      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.SubFunctionConfigured.InvokeCalloutXXX_RequestResults,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.DcmDspEnableObdMirrorDisabled.VerificationCheckPassed.InvokeCSOperationXXX_RequestResults,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.InvokeCSOperationXXX_RequestResults,2 */
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.UnconfiguredDcmDspRoutineTidRef.VerificationCheckPassed.SubFunctionConfigured.InvokeCalloutXXX_RequestResults,2 */
      /* Call function handler for request to application, the results of a routine */
      RoutineSubfunctionResult =
        CurrentRoutineConfig->RequestResultsFncHandler(OpStatus, pMsgContext,&ErrorCode);

      if(OpStatus != DCM_CANCEL)
      {
        switch (RoutineSubfunctionResult)
        {
          case DCM_E_NOT_OK:
          {
            if (ErrorCode != 0x00U)
            {
              /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.ReturnNOK.DiffNRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.ReturnNOK.DiffNRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsNotOk.TransmitNRC,1 */
              Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
            }
            else
            {
              /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.ReturnNOK.NRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.ReturnNOK.NRC0x00,3 */
              /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsNotOk.TransmitNRC0x22,1 */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            }
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;

          case DCM_E_OK:
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.ReturnOK.DiffNRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.ReturnOK.DiffNRC0x00,3 */
            /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsOk.PositiveResponse,1 */
            pMsgContext->resData[0U] = DCM_ROUTINE_CONTROL_REQUESTRESULTS;
            pMsgContext->resData[1U] = pMsgContext->reqData[0U];
            pMsgContext->resData[2U] = pMsgContext->reqData[1U];

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
        /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.RequestRoutineResults.AddRoutineInfoByte.Call,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsOk.InvokeAddInfoByte,1 */
        Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(pMsgContext);
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;

#if (DCM_ROUTINECONTROL_USE_RTE == STD_ON)
          case DCM_E_NO_DATA:
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.ReturnNoData,1 */
            ServiceProcessStatus = DCM_E_PENDING;
          }
          break;
#endif /*(DCM_ROUTINECONTROL_USE_RTE == STD_ON)*/

          case DCM_E_PENDING:
          case DCM_E_FORCE_RCRRP:
          {
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.ReturnForceRCRRP,1 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.ReturnForceRCRRP,1 */
            /* For DCM_E_PENDING and DCM_E_FORCE_RCRRP return the respective value */
            ServiceProcessStatus = RoutineSubfunctionResult;
          }
          break;

          default:
          {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.Unknown.ReturnValue.Det,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.Unknown.ReturnValue.Det,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsUnsupportedCode.DET,1 */
            DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLROUTINERESULTS, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.Callout.Unknown.ReturnValue,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.XxxRequestResults.CS.Unknown.ReturnValue,4 */
            /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
            ServiceProcessStatus = DCM_E_DONE;
          }
          break;
        }
      }
      else
      {
        ServiceProcessStatus = DCM_E_DONE;
      }
    }
#endif /*#if (DCM_NUM_ROUTINES > 0)*/
  }
  return ServiceProcessStatus;
}
#endif /* #if((DCM_NUM_ROUTINES > 0) || (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)) */
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if (DCM_NUM_ROUTINES > 0)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.SetCurrentRoutine,1 */
STATIC FUNC(boolean, DCM_CODE) Dcm_Dsp_RoutineControl_SetCurrentRoutine(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte)
{
  boolean RoutineIdFound = FALSE;

  /* Routine Identifier */
  const uint16 RoutineId = (uint16) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(RoutineIdHighByte,
                                                                            RoutineIdLowByte);

  uint16_least HighRidIndex = DCM_NUM_ROUTINES - 1U;
  uint16_least LowRidIndex  = 0U;

  /* Set the current Routine index to an invalid value */
  Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex = DCM_NUM_ROUTINES;

  /* Ensure the requested routine identifier is within the configured routine range */
  if ((RoutineId >= Dcm_DspRoutineConfig[LowRidIndex].Identifier) && (RoutineId <= Dcm_DspRoutineConfig[HighRidIndex].Identifier))
  {
    /* Deviation TASKING-1 */
    while (HighRidIndex >= LowRidIndex)
    {
      /* Divide the set */
      const uint16_least MiddleRidIndex = LowRidIndex + ((HighRidIndex - LowRidIndex) >> 1U);

      /* Find in which half of the divided set the routine identifier resides */
      if (RoutineId < Dcm_DspRoutineConfig[MiddleRidIndex].Identifier)
      {
        /* Continue searching in the lower half of the set */
        HighRidIndex = MiddleRidIndex - 1U;
      }
      else if (RoutineId > Dcm_DspRoutineConfig[MiddleRidIndex].Identifier)
      {
        /* Continue searching in the higher half of the set */
        LowRidIndex = MiddleRidIndex + 1U;
      }
      else
      {
        /* Routine identifier found */
        Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex = (uint16) MiddleRidIndex;
        RoutineIdFound = TRUE;
        break;
      }
    }
  }

  return RoutineIdFound;
}
#endif /*#if (DCM_NUM_ROUTINES > 0)*/

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.ServiceExecution,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_ServiceExecution(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  switch (OpStatus)
  {
    case DCM_INITIAL:
      ServiceProcessStatus = Dcm_Dsp_RoutineControl_SvcStart(pMsgContext);
      break;
    case DCM_PENDING:
    case DCM_FORCE_RCRRP_OK:
    case DCM_CANCEL:
      ServiceProcessStatus = Dcm_Dsp_RoutineControl_SvcCont(OpStatus, pMsgContext);
      break;

    /* Nothing to do for DCM_CONFIRMED_OK and DCM_CONFIRMED_NOK */
    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      ServiceProcessStatus = DCM_E_DONE;
      break;

    /* CHECK: NOPARSE */
    default:
    {
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_SVCID_ROUTINECONTROL);
      ServiceProcessStatus = DCM_E_DONE;
    }
    break;
    /* CHECK: PARSE */
  }

  return ServiceProcessStatus;
}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.SvcStart,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  DCM_PRECONDITION_ASSERT(Dcm_RoutineControlContextPtr != NULL_PTR, DCM_INTERNAL_API_ID);

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_OFF)
  /* !LINKSTO Dcm.EB.RoutineControl.ISO2013.NRCsOrder,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.ISO2006.NRCsOrder,1 */
  /* !LINKSTO Dcm.Dsn.IB.RoutineControl.NRCsOrder.ISO2006,1 */
  /* !LINKSTO Dcm.Dsn.IB.RoutineControl.NRCsOrder.ISO2013,1 */
  /* Check minimal request length */
  if (pMsgContext->reqDataLen < DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.MinimalLength.NRC0x13,2 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    ServiceProcessStatus = DCM_E_DONE;
  }
  else
#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_OFF) */
  {
    /* Flag to indicate if the Routine Handler can be called to perform the routine request.
     * It is set as TRUE when:
     * (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) and an unsupported (unconfigured or unused)
     * routine is requested
     * or
     * (DCM_ROUTINE_DEFAULT_INTERFACES == STD_OFF) and all verifications for supported
     * requested routine have been successful.
     * It is initialized with FALSE.*/

    /* Routine Identifier */
    const uint8 RoutineIdHighByte = (uint8)pMsgContext->reqData[1U];
    const uint8 RoutineIdLowByte  = (uint8)pMsgContext->reqData[2U];

    const uint8 RoutineIsProcessedAs = Dcm_Dsp_RoutineControl_DetermineRoutineType(
                                                                                  RoutineIdHighByte,
                                                                                  RoutineIdLowByte);

    /* Deviation TASKING-2 */
    switch (RoutineIsProcessedAs)
    {
      /* This case handles an unsupported routine, two scenarios can apply to this case:
       *  1) DCM_ROUTINE_DEFAULT_INTERFACES is set to STD_OFF
       *       -> 0x31 (RequestOutOfRange) NRC shall be transmitted;
       *  2) DCM_ROUTINE_DEFAULT_INTERFACES is set to STD_ON
       *      -> DefaultRoutines interfaces shall be called; */
      case DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND:
      {
#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
        {
          /* The following flag is set to TRUE when an unsupported
           * (not configured or not used) routine is found */
          Dcm_RoutineControlContextPtr->UnsupportedRoutine = TRUE;
          /* The unsupported routine is allowed to be handled by setting
           * the flag to TRUE.*/
          ServiceProcessStatus = Dcm_Dsp_RoutineControl_ProcessRoutineViaUDSInterface(pMsgContext);
        }
#else
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Disabled.UnconfiguredRoutine,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Disabled.UnusedRoutine,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.ConfiguredOBDRID.UnusedOBDRID.DefaultRoutines.Disabled.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorDisabled.UnconfiguredOBDRID.DefaultRoutines.Disabled.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Disabled.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.UnconfiguredNonAvailabityTID.NoTIDsAreSupported.DefaultRoutines.Disabled.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.NoTIDsAreSupported.DefaultRoutines.Disabled.TransmitNRC0x31,2 */
        /* Verification failed; set the RequestOutOfRange error code for unsupported RIDs */
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          ServiceProcessStatus = DCM_E_DONE;
        }
#endif /* #if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) */
      }
      break;

#if (DCM_NUM_ROUTINES > 0)
      /* This case handles supported UDS routines, it does the following checks in this order:
       *   1) Session check -> in case of failure 0x31 (RequestOutOfRange) NRC shall be transmitted;
       *   2) Security check -> in case of failure 0x33 (SecurityAccessDenied) NRC shall be transmitted;
       *   3) ModeRule check -> the NRC set by the ModeRule shall be transmitted;
       *   4) SubFunction check -> in case of failure 0x12 (SubFunctionNotSupported) NRC shall be transmitted;
       * After all the checks mentioned above are executed successfully the RoutineControl unit
       * shall invoke the respective callouts or client-server interfaces in order to read data
       * from the requested routine. */
      case DCM_ROUTINE_PROCESS_AS_UDS_FOUND:
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
        Dcm_NegativeResponseCodeType CurrentNrc = DCM_E_GENERALREJECT;
#endif /*#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)*/

        if (Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSession() == FALSE)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.WrongSession,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.WrongSession,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.WrongSession,1 */
          /* Verification failed; set the respective error code */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          ServiceProcessStatus = DCM_E_DONE;
        }
        else if (Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSecurityLevel() == FALSE)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.WrongSecurityLevel,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.WrongSecurityLevel,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.WrongSecurityLevel,1 */
          /* Verification failed; set the respective error code */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SECURITYACCESSDENIED);
          ServiceProcessStatus = DCM_E_DONE;
        }
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
        else if (Dcm_Dsp_RoutineControl_ModeRuleResult(&CurrentNrc) == FALSE)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.ModeCondition,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.ModeCondition,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.ModeCondition,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, CurrentNrc);
          ServiceProcessStatus = DCM_E_DONE;
        }
#endif
        else /* If all verifications have been successful, call the Routine handler */
        {
          ServiceProcessStatus = Dcm_Dsp_RoutineControl_ProcessRoutineViaUDSInterface(pMsgContext);
        }
      }
      break;
#endif /*#if (DCM_NUM_ROUTINES > 0)*/

      /* Case only available when configuration parameter "DcmDspEnableObdMirror" is set to "True".
       * This case handles non-availability OBD routines, two scenarios can apply to this case:
       *   1) The requested routine in the OBD (0xE000 - 0xE0FF) range is not supported;
       *   2) The requested routine in the OBD (0xE000 - 0xE0FF) range is supported and
       *      configuration parameter DcmDspRoutineTidRef references a TID;
       * A shell function to the OBD Service $08 is used to read data from the mirrored TID. */
#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
      case DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY:
      {

        /* !LINKSTO Dcm.EB.RoutineControl.OBDRange.NonAvailabilityTID,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.InvokeCalloutXXX_RequestControl,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.InvokeCSOperationXXX_RequestControl,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsOk.PositiveResponse,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsUnsupportedCode.DET,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsNotOk.TransmitNRC0x22,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsUnsupportedCode.TransmitNRC0x22,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.ConfiguredNonAvailabityTID.UnusedNonAvailabityTID.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnconfiguredOBDRID.UnconfiguredNonAvailabityTID.AtLeastOneTIDisSupported.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.ConfiguredNonAvailabityTID.UnusedNonAvailabityTID.TransmitNRC0x31,2 */
        /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.ConfiguredOBDRID.UnusedOBDRID.UnconfiguredNonAvailabityTID.AtLeastOneTIDisSupported.TransmitNRC0x31,2 */
#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
        /* Call the handler for this service through a shell which takes care
         * of the fact that the request and response messages are of UDS type */
        Std_ReturnType RequestControlResult = Dcm_DspInternal_ReqCtrlViaRoutineCtrl_UDSShell(
                                                                                       pMsgContext);

        /* Add RoutineInfoByte if the shell returned E_OK. */
        if (RequestControlResult == E_OK)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsOk.InvokeAddInfoByte,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsOk.PositiveResponseWithInfoByte,1 */
          Dcm_Dsp_RoutineControl_OBDOnUDS_AddInfoByte(pMsgContext);
        }
#else
        (void)Dcm_DspInternal_ReqCtrlViaRoutineCtrl_UDSShell(pMsgContext);
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */

        ServiceProcessStatus = DCM_E_DONE;
      }
      break;

      /* Case only available when configuration parameter "DcmDspEnableObdMirror" is set to "True".
       * This case handles the availability of OBD and UDS routines (If configuration parameter
       * DcmDspRidAvailabilityCalculation is set to 'True') from OBD range (0xE000 - 0xE0FF).
       * OBD TID availability is achieved by calling the UDS shell of OBD service $08.
       * UDS RID availability is achieved by calling
       * Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability() function.
       * UDS availability is calculated on top of the already calculated OBD availability response
       * present already in the buffer, if OBD availability was successful, depending of the
       * bit position which needs to be set to '1' this may overwrite the already existing '1'
       * set by the OBD calculation. */
      case DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY:
      {
        if (pMsgContext->reqDataLen != DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.AvailabilityOBDonUDSRID.OBDonUDSRange.RequestLengthGreaterThan4Bytes.TransmitNRC0x13,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationDisabled.DcmDspEnableObdMirrorEnabled.AvailabilityOBDRID.E0Range.RequestLengthGreaterThan4Bytes.TransmitNRC0x13,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
          Dcm_Dsp_RoutineControl_ProcessRoutineAsOBDAvailability(RoutineIdHighByte,
                                                                  RoutineIdLowByte,
                                                                  pMsgContext);
        }
        ServiceProcessStatus = DCM_E_DONE;
      }
      break;
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */

      /* Case only available when configuration parameter "DcmDspRidAvailabilityCalculation" is set
       * to "True".
       * This case handles the availability of UDS routines from OBDOnUDS range (0xE000 - 0xE1FF).
       * UDS RID availability is achieved by calling
       * Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability() function.
       * If configuration parameter 'DcmDspEnableObdMirror' is set to 'True', UDS availability of
       * routines which are requested in the OBD range (0xE000 - 0xE0FF) shall be handled in
       * DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY case. */
#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
      case DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY:
      {
        if (pMsgContext->reqDataLen != DCM_ROUTINE_CONTROL_MIN_REQ_LENGTH)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.AvailabilityOBDonUDSRID.OBDonUDSRange.RequestLengthGreaterThan4Bytes.TransmitNRC0x13,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
          Dcm_Dsp_RoutineControl_ProcessRoutineAsUDSAvailability(RoutineIdHighByte,
                                                                 RoutineIdLowByte,
                                                                 pMsgContext);
        }
        ServiceProcessStatus = DCM_E_DONE;
      }
      break;
#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

      /* CHECK: NOPARSE */
      default:
      {
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      }
        break;
      /* CHECK: PARSE */

    } /* switch(RoutineIsProcessedAs) */
  }

  return ServiceProcessStatus;
}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.SvcCont,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  DCM_PRECONDITION_ASSERT(
    Dcm_RoutineControlContextPtr->SubServiceHandler != NULL_PTR, DCM_INTERNAL_API_ID);

  DCM_PRECONDITION_ASSERT(Dcm_RoutineControlContextPtr != NULL_PTR, DCM_INTERNAL_API_ID);

  /* Call the respective sub-service handler */
  ServiceProcessStatus = Dcm_RoutineControlContextPtr->SubServiceHandler(OpStatus, pMsgContext);

  return ServiceProcessStatus;
}

#if (DCM_NUM_ROUTINES > 0)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.IsRoutineAvailableInCurrentSession,1 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSession(void)
{
  boolean RoutineIsAvailableInCurrentSession = FALSE;

  /* Get pointer to routine configuration info table  */
  P2CONST(Dcm_DspRoutineServicesInfoType, AUTOMATIC, DCM_CONST) CurrentRoutineConfigInfo
    = Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex].RoutineInfoRef;

  if (CurrentRoutineConfigInfo->NumSesLevels > 0U)
  {
    Dcm_SesCtrlType CurrentSesionCtrl;
    uint8_least SessionIdx;

    /* No need to check the return value - at this point Dcm_GetSesCtrlType() will return E_OK
     * Dcm is initialized and &CurrentSesionCtrl is not NULL */
    (void)Dcm_GetSesCtrlTypeExt(&CurrentSesionCtrl);

    /* check if routine is allowed in current session */
    for (SessionIdx = 0U;
        (SessionIdx < CurrentRoutineConfigInfo->NumSesLevels) && (FALSE == RoutineIsAvailableInCurrentSession);
        SessionIdx++)
    {
      if ((CurrentRoutineConfigInfo->SessionRef[SessionIdx] == DCM_ALL_SESSION_LEVEL) ||
          (CurrentRoutineConfigInfo->SessionRef[SessionIdx] == CurrentSesionCtrl))
      {
        RoutineIsAvailableInCurrentSession = TRUE;
      }
    }
  }
  else
  {
    RoutineIsAvailableInCurrentSession = TRUE;
  }

  return RoutineIsAvailableInCurrentSession;
}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.IsRoutineAvailableInSecLevel,1 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_IsRoutineAvailableInCurrentSecurityLevel(void)
{
  boolean RoutineIsAvailableInCurrentSecLevel = FALSE;

  /* Get pointer to routine configuration info table  */
  P2CONST(Dcm_DspRoutineServicesInfoType, AUTOMATIC, DCM_CONST) CurrentRoutineConfigInfo
    = Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex].RoutineInfoRef;

  if (CurrentRoutineConfigInfo->NumSecLevels != 0U)
  {
    /* Get current security level */
    Dcm_SecLevelType CurrentSecLevel = Dcm_Dsl_SecurityLevelHandler_GetSecurityLevel();

    /* If DCM is not in locked state */
    if (CurrentSecLevel != DCM_SEC_LEV_LOCKED)
    {
      uint8_least SecurityLevelIndex;

      /* Check if Routine is allowed with current security level */
      for (SecurityLevelIndex = 0U;
          (SecurityLevelIndex < CurrentRoutineConfigInfo->NumSecLevels) && (FALSE == RoutineIsAvailableInCurrentSecLevel);
          SecurityLevelIndex++)
      {
        if (CurrentRoutineConfigInfo->SecurityLevelRef[SecurityLevelIndex] == CurrentSecLevel)
        {
          RoutineIsAvailableInCurrentSecLevel = TRUE;
        }
      }
    }
  }
  else
  {
    RoutineIsAvailableInCurrentSecLevel = TRUE;
  }

  return RoutineIsAvailableInCurrentSecLevel;
}

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.ModeRuleResult,1 */
STATIC FUNC (boolean, DCM_CODE) Dcm_Dsp_RoutineControl_ModeRuleResult(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) CurrentNrc)
{
  /* Variable for mode rule result - false means that the mode rule check failed */
  boolean ModeRuleCheckResult = FALSE;

  /* Get pointer to routine configuration info table  */
  P2CONST(Dcm_DspRoutineServicesType, AUTOMATIC, DCM_CONST) CurrentRoutineConfig
    = &Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex];

  if (CurrentRoutineConfig->ModeRuleRoutineFunction != NULL_PTR)
  {
    /* Invoke the mode rule function for the service
     * If the mode rule resulted in failure CurrentNrc will have the calculated nrc,
     * else zero which implies there is no failure */
    ModeRuleCheckResult = CurrentRoutineConfig->ModeRuleRoutineFunction(CurrentNrc);
  }
  else
  {
    ModeRuleCheckResult = TRUE;
  }

  return ModeRuleCheckResult;
}
#endif /*DCM_MODEDECLARATION_SUPPORT */
#endif /*#if (DCM_NUM_ROUTINES > 0)*/

#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.UnsupportedRoutineHandler,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_UnsupportedRoutineHandler(
  uint8 SubServiceID,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;
  Std_ReturnType RoutineSubfunctionResult = E_NOT_OK;
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;

  /* 2-byte Unsupported Routine Identifier */
  const uint8 RoutineIdHighByte = pMsgContext->reqData[0U];
  const uint8 RoutineIdLowByte = pMsgContext->reqData[1U];
  const Dcm_RoutineIDType RoutineID = (Dcm_RoutineIDType) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(RoutineIdHighByte, RoutineIdLowByte);

  /* Unsupported Routine Control Option Record length*/
  const uint32 InDataLength = pMsgContext->reqDataLen - 2U;

  /* Call the Application default functions for the requested SubService */
  switch(SubServiceID)
  {
    case DCM_ROUTINE_CONTROL_START:
    {
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.Dcm_DefaultRoutineStart,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.Cancellation.Timeout,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.Cancellation.ProtocolPreemption,1 */
      /* Call the API default function for Start SubService with different OpStatus.
       * If the request has been cancelled, the API function will be called with DCM_CANCEL OpStatus. */
      RoutineSubfunctionResult = Dcm_DefaultRoutineStart(OpStatus,
                                                         RoutineID,
                                                         (uint8*)&pMsgContext->reqData[2],
                                                         InDataLength,
                                                         (uint8*)&pMsgContext->resData[3],
                                                         (uint32*)&pMsgContext->resDataLen,
                                                         &ErrorCode);
    }
    break;

    case DCM_ROUTINE_CONTROL_STOP:
    {
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.Dcm_DefaultRoutineStop,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.Cancellation.Timeout,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.Cancellation.ProtocolPreemption,1 */
      /* Call the API default function for Stop SubService with different OpStatus.
       * If the request has been cancelled, the API function will be called with DCM_CANCEL OpStatus. */
      RoutineSubfunctionResult = Dcm_DefaultRoutineStop(OpStatus,
                                                        RoutineID,
                                                        (uint8*)&pMsgContext->reqData[2],
                                                        InDataLength,
                                                        (uint8*)&pMsgContext->resData[3],
                                                        (uint32*)&pMsgContext->resDataLen,
                                                        &ErrorCode);
    }
    break;

    case DCM_ROUTINE_CONTROL_REQUESTRESULTS:
    {
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.Dcm_DefaultRoutineRequestRoutineResults,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.Cancellation.Timeout,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.Cancellation.ProtocolPreemption,1 */
      /* Call the API default function for RequestResults SubService with different OpStatus.
       * If the request has been cancelled, the API function will be called with DCM_CANCEL OpStatus. */
      RoutineSubfunctionResult = Dcm_DefaultRoutineRequestRoutineResults(OpStatus,
                                                                         RoutineID,
                                                                         (uint8*)&pMsgContext->reqData[2],
                                                                         InDataLength,
                                                                         (uint8*)&pMsgContext->resData[3],
                                                                         (uint32*)&pMsgContext->resDataLen,
                                                                         &ErrorCode);
    }
    break;

    /* CHECK: NOPARSE */
    default:
    {
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_SVCID_ROUTINECONTROL);
    }
    break;
   /* CHECK: PARSE */
  }

  if(OpStatus != DCM_CANCEL)
  {
    /* Verify the API default function result */
    switch (RoutineSubfunctionResult)
    {
      /* Request was not successful */
      case E_NOT_OK:
      {
        if (ErrorCode != DCM_E_POSITIVERESPONSE)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.NRC,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.NRC,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.NRC,1 */
          /* The value of the Nrc parameter is set */
          Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
        }
        else
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.0x00,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.0x00,1 */
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.0x00,1 */
          /* ConditionsNotCorrect(0x22) NRC is set */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        }
        /* After the unsupported routine is handled, the flag is set as FALSE */
        Dcm_RoutineControlContextPtr->UnsupportedRoutine = FALSE;
        ServiceProcessStatus = DCM_E_DONE;
      }
      break;

      /* Request was successful */
      case E_OK:
      {
        /* If the routine was successful, write the sub-function and the routine Id in the response */
        pMsgContext->resData[0U] = SubServiceID;
        pMsgContext->resData[1U] = pMsgContext->reqData[0U];
        pMsgContext->resData[2U] = pMsgContext->reqData[1U];
        pMsgContext->resDataLen += 3U;

        /* After the unsupported routine is handled, the flag is set as FALSE */
        Dcm_RoutineControlContextPtr->UnsupportedRoutine = FALSE;

        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.OK,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.OK,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.OK,1 */
        ServiceProcessStatus = DCM_E_DONE;
      }
      break;

      /* Request is not yet finished, further call(s) required to finish */
      case DCM_E_PENDING:
      {
        /* For DCM_E_PENDING return the respective value */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.Pending,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.Pending,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.Pending,1 */
        /* Retry the call in next main function cycle */
        ServiceProcessStatus = DCM_E_PENDING;
      }
      break;

      /* The result of the API function is unknown */
      default:
      {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        /* If the Error code is unknown, report the DCM_E_INTERFACE_RETURN_VALUE DET error */
        if(SubServiceID == DCM_ROUTINE_CONTROL_START)
        {
            /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.UnsupportedError.DET,1 */
            DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLSTART, DCM_E_INTERFACE_RETURN_VALUE);
        }
        else if(SubServiceID == DCM_ROUTINE_CONTROL_STOP)
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.UnsupportedError.DET,1 */
          DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLSTOP, DCM_E_INTERFACE_RETURN_VALUE);
        }
        else
        {
          /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.UnsupportedError.DET,2 */
          DCM_DET_REPORT_ERROR(DCM_SVCID_ROUTINECONTROLROUTINERESULTS, DCM_E_INTERFACE_RETURN_VALUE);
        }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

        /* After the unsupported routine is handled, the flag is set as FALSE */
        Dcm_RoutineControlContextPtr->UnsupportedRoutine = FALSE;

        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Start.UnsupportedError.NRC,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.Stop.UnsupportedError.NRC,1 */
        /* !LINKSTO Dcm.EB.RoutineControl.DefaultRoutines.Enabled.UnsupportedRoutine.RequestResults.UnsupportedError.NRC,1 */
        /* GeneralReject (0x10) is set for an unknown Error code */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
        ServiceProcessStatus = DCM_E_DONE;
      }
      break;
    }
  }
  /* OpStatus value is DCM_CANCEL */
  else
  {
    /* The result of this call is ignored */
    ServiceProcessStatus = DCM_E_DONE;
  }

  return ServiceProcessStatus;
}
#endif /*#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)*/

#if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
     ((DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) || \
      (DCM_NUM_ROUTINES > 0)))
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.RoutineInfoByteHandler,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  /* 2-byte Routine Identifier */
  const uint8 RoutineIdHighByte = pMsgContext->reqData[0U];
  const uint8 RoutineIdLowByte  = pMsgContext->reqData[1U];
  const Dcm_RoutineIDType RoutineID = (Dcm_RoutineIDType) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(RoutineIdHighByte, RoutineIdLowByte);

  /* Variable to check if a byte was requested to be added from the application */
  boolean RoutineInfoByteStatus = FALSE;

  /* Variable to store the byte to be added in the response message */
  uint8 Dcm_RoutineInfoByte = 0U;

  /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.Dcm_AddRoutineInfoByte,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StartRoutine.AddRoutineInfoByte.Call,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StopRoutine.AddRoutineInfoByte.Call,1 */
  /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.RequestRoutineResults.AddRoutineInfoByte.Call,1 */
  /* Check if a byte was requested to be added from the application */
  RoutineInfoByteStatus = Dcm_AddRoutineInfoByte(RoutineID, &Dcm_RoutineInfoByte);

  if(pMsgContext->resMaxDataLen > pMsgContext->resDataLen)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsOk.PositiveResponseWithoutInfoByte,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsOk.PositiveResponseWithoutInfoByte,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsOk.PositiveResponseWithoutInfoByte,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.SupportedNonAvailabityTID.XXX_RequestControl.ReturnsOk.PositiveResponseWithoutInfoByte,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.PositiveResponseWithoutInfoByte,2 */
    if(TRUE == RoutineInfoByteStatus)
    {
      /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StartRoutine.AddRoutineInfoByte.TRUE,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.StopRoutine.AddRoutineInfoByte.TRUE,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.RequestRoutineResults.AddRoutineInfoByte.TRUE,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.StartRoutine.SupportedOBDRID.XXX_Start.ReturnsOk.PositiveResponseWithInfoByte,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.StopRoutine.SupportedOBDRID.XXX_Stop.ReturnsOk.PositiveResponseWithInfoByte,1 */
      /* !LINKSTO Dcm.EB.RoutineControl.RequestRoutineResults.SupportedOBDRID.XXX_RequestResults.ReturnsOk.PositiveResponseWithInfoByte,1 */
      /* Shift the response message by 1 byte after the Routine ID */
      Dcm_DspInternal_ShiftBitsInBuffer(pMsgContext->resData,
                                        DCM_GET_BITS(DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE),
                                        DCM_GET_BITS(DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE) + DCM_ROUTINE_CONTROL_INFOBYTE_SIZE,
                                        DCM_GET_BITS((pMsgContext->resDataLen - DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE)),
                                        FALSE);

      /* Write the byte from the application to the first byte after RoutineID and
       * increase the message length by 1 */
      pMsgContext->resData[DCM_ROUTINE_CONTROL_RESPONS_HEADER_SIZE] = Dcm_RoutineInfoByte;
      pMsgContext->resDataLen += 1U;
    }
  }
  else
  {
    /* !LINKSTO Dcm.EB.RoutineControl.RoutineInfoByte.Enabled.ResponseTooLong.TransmitNRC0x14,1 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_RESPONSETOOLONG);
  }
}
#endif /* #if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
               ((DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) || \
                 (DCM_NUM_ROUTINES > 0))) */

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.InfoContextInit,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_InfoContextInit(
  P2VAR(Dcm_RoutineControlInfoContextType, AUTOMATIC, DCM_VAR) RoutineControlContextPtr)
{
  RoutineControlContextPtr->SubServiceHandler = NULL_PTR;

#if (DCM_NUM_ROUTINES > 0)

  RoutineControlContextPtr->CurrentRoutineConfigIndex = DCM_NUM_ROUTINES;

#endif /* #if (DCM_NUM_ROUTINES > 0) */

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

  RoutineControlContextPtr->RoutineOperationsLock = DCM_MUTEX_UNLOCKED;

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

#if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)
  RoutineControlContextPtr->UnsupportedRoutine = FALSE;
#endif /* #if (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON) */
}

#if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON)

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.SetContextPointer,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_SetContextPointer(
  uint8 RoutineIdHighByte)
{

  /* Check if routine is in OBD range 0xE000U - 0xE1FFU */
  if ((RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0) ||
      (RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1))
  {
    /* Set the Dcm_RoutineControlContextPtr to point the OBD context */
    Dcm_RoutineControlContextPtr = &Dcm_RoutineControlOBDContext;
  }
  else
  {
    /* Set the Dcm_RoutineControlContextPtr to point the UDS context */
    Dcm_RoutineControlContextPtr = &Dcm_RoutineControlUDSContext;
  }
}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.LockService,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_LockService(void)
{
  Std_ReturnType RetVal = DCM_E_RESOURCE_LOCKED;

  RetVal = Dcm_Internal_GetLock(&Dcm_RoutineControlContextPtr->RoutineOperationsLock);

  return RetVal;
}

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.UnlockService,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_UnlockService(void)
{
  Dcm_Internal_ReleaseLock(&Dcm_RoutineControlContextPtr->RoutineOperationsLock);
}

#endif /* #if (DCM_ROUTINE_PARALLEL_PROCESSING == STD_ON) */

#if ((DCM_NUM_ROUTINES > 0) && \
     (DCM_RID_AVAILABILITY_CALCULATION == STD_ON))
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OBDOnUDS.CheckRoutineAvailability,1 */
STATIC FUNC(boolean, DCM_CODE) Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability(
  uint8 RequestedRoutineIdHighByte,
  uint8 RequestedRoutineIdLowByte,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) ResponseBuffer
)
{
  uint16_least RoutineTabIndex = 0U;

  /* Variable is set to True, in the following scenarios/condition/cases:
   *   - a supported routine is found in the requested availability range
   *    - a supported routine is found in the sub-sequent range of the requested availability range
   *
   * Variable is returned by the function in order to send a positive (availability bitmap)
   * or a 0x31 (requestOutRange) NRC.
  */
  boolean AtLeastOneNonAvailabilityRoutineIsFound = FALSE;

  /* Cycle through the routines in the OBDonUDS range (0xE000 - 0xE1FF) */
  for (RoutineTabIndex = Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexStart;
      (RoutineTabIndex <= Dcm_Dsp_RoutineControl_OBDOnUDS_RoutineIndexEnd);
       RoutineTabIndex++)
  {

    const uint8 ConfiguredRoutineIdHighByte = (Dcm_DspRoutineConfig[RoutineTabIndex].Identifier >> 8U);

    /* Check RIDs that are in the requested availability range */
    if (ConfiguredRoutineIdHighByte == RequestedRoutineIdHighByte)
    {
       /* Call the Dcm_OBDSupport_UpdateAvailableInfoWithID() function for
        * updating the corresponding supported RIDs in the bitmap response.
        * Parameter usage:
        *   - low byte (LSB) of the configured routine
        *   - requested availability range
        *   - pointer to the response buffer */
      const Std_ReturnType ResponseUpdateResult = Dcm_OBDSupport_UpdateAvailableInfoWithID(
                        ((uint8)(Dcm_DspRoutineConfig[RoutineTabIndex].Identifier & DCM_UINT8_MAX)),
                                                                          RequestedRoutineIdLowByte,
                                                                                    ResponseBuffer);

      /* Check if there is at least one routine configured within requested availability range */
      if ((AtLeastOneNonAvailabilityRoutineIsFound == FALSE) &&
          (ResponseUpdateResult == DCM_E_OK))
      {
        AtLeastOneNonAvailabilityRoutineIsFound = TRUE;
      }
    }

    /* Check if there is there any routine configured in the 0xE100 - 0xE1FF range
     * In case a routine 0xE100 - 0xE1FF is configured, the last bit of the response is set to 1,
     * This allows the tester to be aware of configured routines in 0xE100 - 0xE1FF range,
     * when requesting any availability from the 0xE000 - 0xE0FF range
     * With routines being sorted, in order to save execution time, when a availability routine from
     * the 0xE000 - 0xE0FF range is requested after reaching the first configured routine from the
     * 0xE100 - 0xE1FF range, the AtLeastOneNonAvailabilityRoutineIsFound is set to True and the for
     * loop is breaked. */
    if ((RequestedRoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0) &&
        (ConfiguredRoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE1))
    {
      /* The lenght of availability bitmap is 4 bytes, last bit(position 0 in the byte),
         of the last byte is set to 1 */
      DCM_UINT8_SET_BIT(ResponseBuffer[3U], 0U);

      /* In the scenarios/cases when an availability routine from the E0 range is requested and
       * the last bit from the availability bitmap is set to 1 by a routine which is configured
       * in the sub-sequent range, this variable shall be set again
       * if a routine is configured in the E1 range. */
      AtLeastOneNonAvailabilityRoutineIsFound = TRUE;
      break;
    }
  }

  return AtLeastOneNonAvailabilityRoutineIsFound;
}

#endif /* #if ((DCM_NUM_ROUTINES > 0) && \
               (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)) */

#if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
     (((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && \
       (DCM_NUM_ROUTINES > 0)) || \
      (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)))
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.OBDOnUDS.AddInfoByte,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_OBDOnUDS_AddInfoByte(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  /* Set request data pointer to received data without sub-service Ids */
  pMsgContext->reqData = &pMsgContext->reqData[1U];

  /* Decrement the reqData length as sub-function is removed */
  pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

  Dcm_Dsp_RoutineControl_RoutineInfoByteHandler(pMsgContext);
}

#endif /* #if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) && \
             (((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && \
               (DCM_NUM_ROUTINES > 0)) || \
               (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON))) */

/* !LINKSTO Dcm.Dsn.IB.RoutineControl.DetermineRoutineType,1 */
STATIC FUNC(uint8, DCM_CODE) Dcm_Dsp_RoutineControl_DetermineRoutineType(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte)
{
  uint8 RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND;

#if (DCM_NUM_ROUTINES > 0)
  /* Check if the requested routine identifier is supported.
   * Two cases can be reached:
   *   1) Routine is supported in OBD range and TID reference is configured
   *     -> DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY
   *   2) Routine is supported
   *     -> DCM_ROUTINE_PROCESS_AS_UDS_FOUND */
  if ((Dcm_Dsp_RoutineControl_SetCurrentRoutine(RoutineIdHighByte, RoutineIdLowByte)) == TRUE)
  {
#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
    /* Check if the requested routine identifier is in the OBD range (0xE000 - 0xE0FF) */
    if (RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0)
    {
      /* Check if the requested routine identifier has a TID refence set */
      if (Dcm_DspRoutineConfig[Dcm_RoutineControlContextPtr->CurrentRoutineConfigIndex].UseOBDInterface == TRUE)
      {
        /* If a configured routine has a TID refference configured then it cannot be an availability,
         * availability TIDs cannot be configured thus cannot be referenced by any routine */
        DCM_PRECONDITION_ASSERT((DCM_IS_AVAILABILITY_OBDSUBID(RoutineIdLowByte) == FALSE), DCM_INTERNAL_API_ID);
        RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY;
      }
      else
      {
        RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_FOUND;
      }
    }
    else
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */
    {
      RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_FOUND;
    }
  }
  else
  /* Below scenarios apply only for unsupported routines:
   *   1) Unsupported availability routine in OBD range (0xE000 - 0xE0FF)
   *     -> DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY
   *
   *   2) Unsupported non availability routine in OBD range (0xE000 - 0xE0FF)
   *     -> DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY
   *
   *   3) Unsupported availability routine in OBDOnUDS range (0xE000 - 0xE1FF)
   *     -> DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY
   *
   *   4) Unsupported availability routine
   *     -> DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND */
#endif /* #if (DCM_NUM_ROUTINES > 0) */
  {
    /* Check if the requested routine identifier is in the OBDOnUDS range (0xE000 - 0xE1FF) */
    if (DCM_ROUTINE_IS_IN_OBD_ON_UDS_RANGE(RoutineIdHighByte) == TRUE)
    {
      /* Check if the requested routine identifier is availability
       * Below scenarios apply to unsupported availability routines */
      if(DCM_IS_AVAILABILITY_OBDSUBID(RoutineIdLowByte) == TRUE)
      {
#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
        /* Check if the requested routine identifier is in the OBD range (0xE000 - 0xE0FF) */
        if (RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0)
        {
          RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_OBD_AVAILABILITY;
        }
        else
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */
        {
#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
          RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_OBD_ON_UDS_AVAILABILITY;
#else
          RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND;
#endif
        }
      }
      /* Below scenarios apply to unsupported non-availability routines */
      else
      {
#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
        /* Check if the requested routine identifier is in the OBD range (0xE000 - 0xE0FF) */
        if (RoutineIdHighByte == DCM_DSP_OBD_RID_RANGE_HIGH_BYTE_0xE0)
        {
          RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_OBD_NON_AVAILABILITY;
        }
        else
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */
        {
          RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND;
        }
      }
    }
    else
    {
      RoutineIsProcessedAs = DCM_ROUTINE_PROCESS_AS_UDS_NOT_FOUND;
    }
  }

  return RoutineIsProcessedAs;
}

#if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.ProcessRoutineAsOBDAvailability,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineAsOBDAvailability(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
#if ((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && (DCM_NUM_ROUTINES > 0))
  boolean AtLeastOneNonAvailabilityRoutineIsFound = FALSE;
#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
  boolean AddRoutineInfoByte = FALSE;
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */

  /* Call the handler for this service through a shell which takes care
   * of calculating availability bitmap for the OBD side (TIDs). */
  /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.AtLeastOneTIDisSupported.PositiveResponse,3 */
#if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) || \
(DCM_RID_AVAILABILITY_CALCULATION == STD_ON))
  Std_ReturnType RequestControlResult = Dcm_DspInternal_ReqCtrlViaRoutineCtrl_UDSShell(
                                                                                       pMsgContext);

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
  if (RequestControlResult == E_OK)
  {
    AddRoutineInfoByte = TRUE;
  }
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */

#else
  (void)Dcm_DspInternal_ReqCtrlViaRoutineCtrl_UDSShell(pMsgContext);
#endif /* #if ((DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) || \
     ((DCM_RID_AVAILABILITY_CALCULATION == STD_ON) && (DCM_NUM_ROUTINES > 0))) */

#if ((DCM_NUM_ROUTINES == 0) || \
     (DCM_RID_AVAILABILITY_CALCULATION == STD_OFF))

  TS_PARAM_UNUSED(RoutineIdHighByte);
  TS_PARAM_UNUSED(RoutineIdLowByte);

#endif /* #if ((DCM_NUM_ROUTINES == 0) || \
               (DCM_RID_AVAILABILITY_CALCULATION == STD_OFF)) */

#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
#if (DCM_NUM_ROUTINES > 0)
  if (RequestControlResult == E_NOT_OK)
  {
    /* Clear the response buffer in order to avoid
    * having garbage data from the previous request */
    TS_MemSet(&(pMsgContext->resData[3U]), 0U, 4U);
  }

  /* Call function which calculates the availability bitmap for the rotines */
  AtLeastOneNonAvailabilityRoutineIsFound =
                                           Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability(
                                                                       RoutineIdHighByte,
                                                                       RoutineIdLowByte,
                                                                       &(pMsgContext->resData[3U]));

  /* Check if there is at least one TID found in the requested availability range */
  if (RequestControlResult == E_NOT_OK)
  {
    /* No TID is found, check if at least one RID is found in the requested availability range */
    if (AtLeastOneNonAvailabilityRoutineIsFound == TRUE)
    {
      /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.DcmDspEnableObdMirrorEnabled.UnsupportedAvailabilityOBDonUDSRID.AvailabilityRIDsAndTIDs,1 */
      pMsgContext->resData[0U] = pMsgContext->reqData[0U];
      pMsgContext->resData[1U] = RoutineIdHighByte;
      pMsgContext->resData[2U] = RoutineIdLowByte;

      /* Set response lenght to 7 bytes: 1 byte (subServiceId) + 1 byte (RoutineHighByte)
      + 1 byte (RoutineLowByte) + 4 bytes for availability */
      pMsgContext->resDataLen = 7U;

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
      /* AddRoutineInfoByte variable is overwritten in case the OBD sub-system finds a supported TID
       * and a supported RID is also found. */
      AddRoutineInfoByte = TRUE;
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */
    }
    else
    {
      /* No supported TID/RID are found in the requested availability range,
       * send requestOutRange(0x31) NRC */
      /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.UnsupportedAvailabilityOBDonUDSRID.E0Range.TIDsAndRIDsNotSupported.TransmitNRC0x31,1 */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    }
  }

#else

  if (RequestControlResult == E_NOT_OK)
  {
    /* No supported TID is found in the requested availability range,
     * send requestOutRange(0x31) NRC */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }
#endif /* #if(DCM_NUM_ROUTINES > 0) */
#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
  if (AddRoutineInfoByte == TRUE)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.UnsupportedAvailabilityOBDonUDSRID.InvokeAddInfoByte,1 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.PositiveResponseWithInfoByte,2 */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspEnableObdMirrorEnabled.UnsupportedOBDRID.AvailabityTID.AtLeastOneTIDisSupported.InvokeAddInfoByte,3 */
    Dcm_Dsp_RoutineControl_OBDOnUDS_AddInfoByte(pMsgContext);
  }
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */
}
#endif /* #if (DCM_ROUTINE_ENABLE_OBD_SUBSYSTEM == STD_ON) */

#if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.ProcessRoutineAsUDSAvailability,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineAsUDSAvailability(
  uint8 RoutineIdHighByte,
  uint8 RoutineIdLowByte,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{

#if (DCM_NUM_ROUTINES == 0)

  TS_PARAM_UNUSED(RoutineIdHighByte);
  TS_PARAM_UNUSED(RoutineIdLowByte);

#endif /* #if (DCM_NUM_ROUTINES == 0) */

#if (DCM_NUM_ROUTINES > 0)
  boolean AtLeastOneNonAvailabilityRoutineIsFound = FALSE;

  /* Clear the response buffer in order to avoid
  * having garbage data from the previous request */
  TS_MemSet(&(pMsgContext->resData[3U]), 0U, 4U);

  /* Call function which calculates the availability bitmap for the rotines */
  AtLeastOneNonAvailabilityRoutineIsFound =
                                   Dcm_Dsp_RoutineControl_OBDOnUDS_CheckRoutineAvailability(
                                                                       RoutineIdHighByte,
                                                                       RoutineIdLowByte,
                                                                       &(pMsgContext->resData[3U]));

  /* Check if at least one routine is found in the requested availability range */
  if (AtLeastOneNonAvailabilityRoutineIsFound == TRUE)
  {
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.DcmDspEnableObdMirrorDisabled.UnsupportedAvailabilityOBDonUDSRID.AvailabilityRIDs,1 */
    pMsgContext->resData[0U] = pMsgContext->reqData[0U];
    pMsgContext->resData[1U] = RoutineIdHighByte;
    pMsgContext->resData[2U] = RoutineIdLowByte;

    /* Set response lenght to 7 bytes: 1 byte (subServiceId) + 1 byte (RoutineHighByte)
    + 1 byte (RoutineLowByte) + 4 bytes for availability */
    pMsgContext->resDataLen = 7U;

#if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON)
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.UnsupportedAvailabilityOBDonUDSRID.InvokeAddInfoByte,1 */
    Dcm_Dsp_RoutineControl_OBDOnUDS_AddInfoByte(pMsgContext);
#endif /* #if (DCM_ROUTINE_ROUTINEINFOBYTE == STD_ON) */
  }
  else
#endif /* #if (DCM_NUM_ROUTINES > 0) */
  {
    /* No supported routine is found in the requested availability range,
     * send requestOutRange(0x31) NRC */
    /* !LINKSTO Dcm.EB.RoutineControl.DcmDspRidAvailabilityCalculationEnabled.UnsupportedAvailabilityOBDonUDSRID.E1Range.RIDsNotSupported.TransmitNRC0x31,1 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }
}

#endif /* #if (DCM_RID_AVAILABILITY_CALCULATION == STD_ON) */

#if ((DCM_NUM_ROUTINES > 0U) || \
     (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON))
/* !LINKSTO Dcm.Dsn.IB.RoutineControl.ProcessRoutineViaUDSInterface,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RoutineControl_ProcessRoutineViaUDSInterface(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  /* Extract the sub-service identifier from the current request */
  const uint8 SubServiceIdentifier = pMsgContext->reqData[0U];

  /* Verify if the sub-service identifier is valid*/
  if ((SubServiceIdentifier != DCM_ROUTINE_CONTROL_START) &&
      (SubServiceIdentifier != DCM_ROUTINE_CONTROL_STOP) &&
      (SubServiceIdentifier != DCM_ROUTINE_CONTROL_REQUESTRESULTS))
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
    ServiceProcessStatus = DCM_E_DONE;
  }
  else
  {
    Dcm_RoutineControlContextPtr->SubServiceHandler =
                  Dcm_Dsp_ExtractSubServiceHandler(DCM_INITIAL, pMsgContext);

    ServiceProcessStatus = Dcm_Dsp_RoutineControl_SvcCont(DCM_INITIAL, pMsgContext);
  }

  return ServiceProcessStatus;
}
#endif /* #if ((DCM_NUM_ROUTINES > 0U) || \
               (DCM_ROUTINE_DEFAULT_INTERFACES == STD_ON)) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if(DCM_DSP_USE_SERVICE_0X31 == STD_ON) */

/*==================[end of file]================================================================*/
