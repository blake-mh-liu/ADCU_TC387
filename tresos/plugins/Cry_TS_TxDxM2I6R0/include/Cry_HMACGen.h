/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_HMACGen,1 */

#ifndef CRY_HMACGEN_H
#define CRY_HMACGEN_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>                /* !LINKSTO EB_CRY_0002,1 */
#include <Csm_Hash.h>
#include <Cry_HMACGenConfig.h> /* !LINKSTO EB_CRY_0002,1 */
#if (CRY_HMAC_GEN_ENABLED == TRUE)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief Start HMAC generation.
 *
 * This function requests the start of the HMAC
 * generation for the given configuration and key. The start is performed in
 * Cry_HMACGenMainFunction().
 *
 * \param[in]  cfgPtr  A pointer to the configuration for which the start of the signature
 *                     generation should be requested.
 *
 * \param[in]  keyPtr  A pointer to the key which should be used in the signature
 *                     generation.
 *
 * \return Error code
 *
 * \retval CSM_E_OK   If the start was successfully requested.
 * \retval CSM_E_BUSY If a service of the HMAC generation is already running.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */

extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACGenStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)                   cfgPtr,
   P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA)         keyPtr
);

/**
 *
 * \brief Update HMAC generation.
 *
 * This function requests the update of the HMAC generation for the given data.
 * The update is performed in Cry_HMACGenMainFunction().
 *
 * \param[in]  dataPtr       A pointer to the start of an array which contains a part of the
 *                           data for which the signature should be created.
 *
 * \param[in]  dataLength    The amount of data in bytes.
 *
 * \return Error code
 *
 * \retval CSM_E_OK          If the update was successfully requested.
 * \retval CSM_E_BUSY        If the main function is processing a requested service at the
 *                           moment.
 * \retval CSM_E_NOT_OK      If no HMAC generation has been started via
 *                           Cry_HMACGenStart() yet or if the finishing of the HMAC computation is
 *                           already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACGenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);

/**
 *
 * \brief Finish HMAC generation.
 *
 * This function requests the finishing of the HMAC
 * generation and the storing of the signature in the given result buffer. The
 * finishing is performed in Cry_HMACGenMainFunction().
 *
 * \param[out]      resultPtr            A pointer to the start of a buffer where the generated
 *                                       HMAC will be stored.
 *
 * \param[in,out]   resultLengthPtr      A pointer to a variable which contains the maximal allowed
 *                                       length for the HMAC in bits and where the actual length of
 *                                       the HMAC will be stored.
 *
 * \param[in]      TruncationIsAllowed  Is truncation of the result allowed or should an error be
 *                                      returned when the result buffer is too small.
 *
 * \return Error code
 *
 * \retval CSM_E_OK          If the finish was successfully requested.
 * \retval CSM_E_BUSY        If the main function is processing a requested service at the
 *                           moment.
 * \retval CSM_E_NOT_OK      If no HMAC generation has been started via
 *                           Cry_HMACGenStart() yet or if the finishing of the HMAC computation is
 *                           already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACGenFinish
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
   boolean                                 TruncationIsAllowed
);

/**
 *
 * \brief Perform the HMAC generation tasks.
 *
 * This function performs the actual HMAC generation
 * tasks which have been requested by the service functions. When a task has
 * finished, the function Csm_MacGenerateServiceCallbackNotification() is
 * called to inform the CSM of the result. If the complete HMAC generation
 * has finished, additionally the function
 * Csm_MacGenerateServiceFinishNotification() is called.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(void, CRY_APPL_CODE) Cry_HMACGenMainFunction
(
   void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_HMAC_GEN_ENABLED == TRUE) */

#endif /* CRY_HMACGEN_H */
