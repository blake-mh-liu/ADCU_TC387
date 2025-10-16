/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, EB_CSM0694_RsaSsaV15Verify,1 */

#ifndef CRY_RSASSAV15VERIFY_H
#define CRY_RSASSAV15VERIFY_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                        /* !LINKSTO EB_CRY_0002,1 */
#include <Csm_Hash.h>
#include <Cry_LN.h>
#include <Cry_RsaSsaV15VerifyConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Start signature verification.
 *
 * This function requests the start of the RSASSA-PKCS1-v1_5 signature
 * verification for the given configuration and key. The start is performed in
 * Cry_RsaSsaV15VerifyMainFunction().
 *
 * \param[in] cfgPtr a pointer to the configuration for which the start of the signature
 *                   verification should be requested.
 * \param[in] keyPtr a pointer to the key which should be used in the signature
 *                   verification.
 * \return Error code
 *
 * \retval CSM_E_OK   If the update was successfully requested.
 * \retval CSM_E_BUSY If a service of the RSASSA-PKCS1-v1_5 signature verification is already
 *                    running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15VerifyStart
(
  P2CONST(void,                  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);


/** \brief Update signature verification.
 *
 * This function requests the update of the RSASSA-PKCS1-v1_5 signature
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
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15VerifyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
);


/** \brief Finish signature verification.
 *
 * This function requests the finishing of the RSASSA-PKCS1-v1_5 signature verification and
 * the storing of the signature in the given signature buffer. The finishing
 * is performed in Cry_SigPKCS1VrfyMainFunction().
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
 *                       Cry_SigPKCS1VrfyStart(), yet.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15VerifyFinish
(
  P2CONST(uint8,              AUTOMATIC, CRY_APPL_DATA) signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
);


/** \brief Perform the RSASSA-PKCS1-v1_5 verification tasks.
 *
 * This function performs the actual RSASSA-PKCS1-v1_5 signature verification
 * tasks which have been requested by the service functions. When a task has
 * finished, the function Csm_SignatureVerifyServiceCallbackNotification() is
 * called to inform the CSM of the signature. If the complete signature
 * verification has finished, additionally the function
 * Csm_SignatureVerifyServiceFinishNotification() is called.
 *
 */
extern FUNC(void, CRY_APPL_CODE) Cry_RsaSsaV15VerifyMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON) */

#endif /* CRY_RSASSAV15VERIFY_H */
