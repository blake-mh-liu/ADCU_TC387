/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_CMACGen,1 */

#ifndef CRY_CMACGEN_H
#define CRY_CMACGEN_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>                /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_CMACGenConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if (CRY_CMAC_GEN_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief Start CMAC generation.
 *
 * This function requests the start of the CMAC generation for the given configuration
 * and key. The start is performed in Cry_CMACGenMainFunction().
 *
 * \param[in]  cfgPtr a pointer to the configuration for which the start of the CMAC
 *                    generation is requested.
 *
 * \param[in]  keyPtr a pointer to the key which will be used in the CMAC
 *                    generation.
 *
 * \return Error code
 *
 * \retval CSM_E_OK   If the start was successfully requested.
 * \retval CSM_E_BUSY If a service of the CMAC generation is already running.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/**
 *
 * \brief Update CMAC generation.
 *
 * This function requests the update of the CMAC generation for the given data.
 * The update is performed in Cry_CMACGenMainFunction().
 *
 * \param[in]  dataPtr A pointer to the start of an array which contains a part of the
 *                     data for which the CMAC will be generated.
 *
 * \param[in]  dataLength The amount of data in bytes.
 *
 * \return Error code
 *
 * \retval CSM_E_OK     If the update was successfully requested.
 * \retval CSM_E_BUSY   If the main function is processing a requested service at the
 *                      moment.
 * \retval CSM_E_NOT_OK If no CMAC generation has been started via
 *                      Cry_CMACGenStart() yet or if the finishing of the CMAC computation is
 *                      already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/**
 *
 * \brief Finish CMAC generation.
 *
 * This function requests the finishing of the CMAC
 * generation and the storing of the CMAC in the given result buffer. The
 * finishing is performed in Cry_CMACGenMainFunction().
 *
 * \param[out]  resultPtr A pointer to the start of a buffer where the generated
 *                        CMAC will be stored.
 *
 * \param[in,out]  resultLengthPtr A pointer to a variable which contains the maximal allowed
 *                                 length for the CMAC in bits and where the actual length of the
 *                                 CMAC will be stored.
 *
 * \param[in]  TruncationIsAllowed Is truncation of the result allowed or must an error be
 *                                 returned when the result buffer is too small?
 *
 * \return Error code
 *
 * \retval CSM_E_OK     If the finishing was successfully requested.
 * \retval CSM_E_BUSY   If the main function is processing a requested service at the
 *                      moment.
 * \retval CSM_E_NOT_OK If no CMAC generation has been started via
 *                      Cry_CMACGenStart() yet or if the finishing of the CMAC computation is
 *                      already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenFinish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 TruncationIsAllowed
);

/**
 *
 * \brief Perform the CMAC generation tasks.
 *
 * This function performs the actual CMAC generation
 * tasks which have been requested by the service functions. When a task has
 * finished, the function Csm_MacGenerateServiceCallbackNotification() is
 * called to inform the CSM of the result. If the complete CMAC generation
 * has finished, additionally the function
 * Csm_MacGenerateServiceFinishNotification() is called.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(void, CRY_CODE) Cry_CMACGenMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) */

#endif /* CRY_CMACGEN_H */
