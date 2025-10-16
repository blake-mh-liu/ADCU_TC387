/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_RsaSsaPssVerify,1 */

#ifndef CRY_RSASSAPSSVERIFY_H
#define CRY_RSASSAPSSVERIFY_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                        /* !LINKSTO EB_CRY_0002,1 */
#include <Csm_Hash.h>
#include <Cry_LN.h>
#include <Cry_RsaSsaPssVerifyConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if(CRY_RSASSAPSSVERIFY_ENABLED == TRUE)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Start signature verification.
 *
 * This function requests the start of the RSASSA-PSS signature
 * verification for the given configuration and key. The start is performed in
 * Cry_RsaSsaPssVerifyMainFunction().
 *
 * \param[in] cfgPtr a pointer to the configuration for which the start of the signature
 *                   verification should be requested.
 * \param[in] keyPtr a pointer to the key which should be used in the signature
 *                   verification.
 * \return Error code
 *
 * \retval CSM_E_OK   If the update was successfully requested.
 * \retval CSM_E_BUSY If a service of the RSASSA-PSS signature verification is already
 *                    running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaPssVerifyStart
(
  P2CONST(void,                  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);


/** \brief Update signature verification.
 *
 * This function requests the update of the RSASSA-PSS signature
 * verification for the given data. The update is performed in
 * Cry_SigPKCS1VrfyMainFunction().
 *
 * \param[in] dataPtr    a pointer to the start of an array which contains a part of the
 *                       data for which the signature should be created.
 * \param[in] dataLength The amount of bytes of data.
 *
 * \return Error code
 *
 * \retval CSM_E_OK      If the update was successfully requested.
 * \retval CSM_E_BUSY    If the main function is processing a requested service at the moment.
 * \retval CSM_E_NOT_OK  If no signature verification has been started via
 *                       Cry_SigPKCS1VrfyStart(), yet.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaPssVerifyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
);


/** \brief Finish signature verification.
 *
 * This function requests the finishing of the RSASSA-PSS signature verification and
 * the storing of the signature in the given signature buffer. The finishing
 * is performed in Cry_RsaSsaPssVerifyMainFunction().
 *
 * \param[in]  signaturePtr    a pointer to the start of a buffer which holds the signature.
 * \param[in]  signatureLength Length of the signature in bytes.
 * \param[out] resultPtr       Verification result.
 *
 * \return Error code
 *
 * \retval CSM_E_OK      If the finish was successfully requested.
 * \retval CSM_E_BUSY    If the main function is processing a requested service at the moment.
 * \retval CSM_E_NOT_OK  If no signature verification has been started via
 *                       Cry_RsaSsaPssVerifyStart(), yet.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaPssVerifyFinish
(
  P2CONST(uint8,              AUTOMATIC, CRY_APPL_DATA) signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
);


/** \brief Perform the RSASSA-PSS-Verify tasks.
 *
 * This function performs the actual RSASSA-PSS signature verification
 * tasks which have been requested by the service functions. When a task has
 * finished, the function Csm_SignatureVerifyServiceCallbackNotification() is
 * called to inform the CSM of the signature. If the complete signature
 * verification has finished, additionally the function
 * Csm_SignatureVerifyServiceFinishNotification() is called.
 *
 */
extern FUNC(void, CRY_APPL_CODE) Cry_RsaSsaPssVerifyMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if(CRY_RSASSAPSSVERIFY_ENABLED == TRUE) */

#endif /* CRY_RSASSAPSSVERIFY_H */
