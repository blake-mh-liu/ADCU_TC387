/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_HMACVrfy,1 */

#ifndef CRY_HMACVRFY_H
#define CRY_HMACVRFY_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>          /* !LINKSTO EB_CRY_0002,1 */

#include <Csm_Hash.h>

#include <Cry_HMACVrfyConfig.h> /* !LINKSTO EB_CRY_0002,1 */

#if (CRY_HMAC_VRFY_ENABLED == TRUE)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief Start HMAC verification.
 *
 * This function requests the start of the HMAC verification for the given configuration
 * and key. The start is performed in Cry_HMACVrfyMainFunction().
 *
 * \param[in]  cfgPtr          A pointer to the configuration for which the start of the signature
 *                             verification is requested.
 *
 * \param[in]  keyPtr          A pointer to the key which will be used in the HMAC
 *                             verification.
 *
 * \return Error code
 *
 * \retval CSM_E_OK           If the start was successfully requested.
 * \retval CSM_E_BUSY         If a service of the HMAC verification is already running.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */

extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACVrfyStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)                  cfgPtr,
   P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA)        keyPtr
);

/**
 *
 * \brief Update HMAC verification.
 *
 * This function requests the update of the HMAC verification for the given data.
 * The update is performed in Cry_HMACVrfyMainFunction().
 *
 * \param[in]  dataPtr        A pointer to the start of an array which contains a part of the
 *                            data for which the signature should be created.
 *
 * \param[in]  dataLength     The amount of data in bytes.
 *
 * \return Error code
 *
 * \retval CSM_E_OK          If the update was successfully requested.
 * \retval CSM_E_BUSY        If the main function is processing a requested service at the
 *                           moment.
 * \retval CSM_E_NOT_OK      If no signature verification has been started via
 *                           Cry_HMACVrfyStart(), yet or if the finishing of the HMAC computation is
 *                           already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACVrfyUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);

/**
 *
 * \brief Finish HMAC verification.
 *
 * This function requests the finishing of the HMAC verification and
 * the storing of the signature in the given buffer. The finishing
 * is performed in Cry_HMACVrfyMainFunction().
 *
 * \param[in]   authenticationPtr      A pointer to the start of a buffer where
                                       the generated signature should be stored.
 *
 *
 * \param[in]   authenticationLength   A variable which contains the maximal allowed
 *                                     length for the signature and the actual length of
 *                                     the signature.
 *
 * \param[out]  resultPtr             A pointer to a variable where the result of
 *                                    the HMAC verification will  be stored.
 *
 *
 * \return Error code
 *
 * \retval CSM_E_OK                  If the finishing was successfully requested.
 * \retval CSM_E_BUSY                If the main function is processing a requested service at the
 *                                   moment.
 * \retval CSM_E_NOT_OK              If no HMAC verification has been started via
 *                                   Cry_HMACVrfyStart() yet, or if the finishing of
 *                                   the HMAC computation is already requested.
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_HMACVrfyFinish
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              authenticationPtr,
   uint32                                                authenticationLength,
   P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
);

/**
 *
 * \brief Perform the HMAC verification tasks.
 *
 * This function performs the actual HMAC verification
 * tasks which have been requested by the service functions. When a task has
 * finished, the function Csm_MacVerifyServiceCallbackNotification() is
 * called to inform the CSM of the signature. If the complete signature
 * verification has finished, additionally the function
 * Csm_MacVerifyServiceFinishNotification() is called.
 *
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
extern FUNC(void, CRY_APPL_CODE) Cry_HMACVrfyMainFunction
(
   void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_HMAC_VRFY_ENABLED == TRUE) */

#endif /* CRY_HMACVRFY_H */
