/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EDDSAVRFY_H
#define CRY_EDDSAVRFY_H

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_Cry_EdDSAVrfy,1 */
/*==[Includes]================================================================*/
#include <Std_Types.h>

#include <Csm.h>
#include <Csm_Hash.h>
#include <Csm_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>
#include <Cry_EdDSAVrfyConfig.h>

#if (CRY_EDDSA_VRFY_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/** \brief The public key used for verifying a signature */
typedef struct
{
  /** \brief Dummy element to make the type compatible with the Csm key type. */
  uint32         length;

  /** \brief An EdDSA public key is a curve point, which is created by
   *         multiplying the s with Point B, encoded in b bits.
   */
  Cry_LNWordType A[CRY_EdDSA_NUM_LEN_WORDS];
}
Cry_EdDSAVrfyKeyType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_0173,1 */
/** \brief                          Start signature verification.
 *
 *                                  This function requests the start of the EdDSA signature
 *                                  verification for the given configuration and key.
 *                                  The start is performed in Cry_EdDSAVrfyMainFunction().
 *
 * \param[in]       cfgPtr          A pointer to the configuration for which the start of the
 *                                  signature verification should be requested.
 * \param[in]       keyPtr          A pointer to the key which should be used in the signature
 *                                  verification.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the service can be started.
 *  \retval         CSM_E_NOT_OK    If the key is invalid.
 *  \retval         CSM_E_BUSY      If another instance of this service is already running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)     cfgPtr,
   P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/* !LINKSTO CS_SECURE_CRY_0174,1 */
/** \brief                          Update signature verification.
 *
 *
 *                                  This function requests the update of the EdDSA signature
 *                                  verification for the given data.
 *                                  The update is performed in Cry_EdDSAVrfyMainFunction().
 *
 * \param[in]       dataPtr         A pointer to the start of an array which contains a part of the
 *                                  data for which the signature should be created.
 * \param[in]       dataLength      The amount of bytes of data.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the service can be started.
 *  \retval         CSM_E_NOT_OK    If the key is invalid.
 *  \retval         CSM_E_BUSY      If another instance of this service is already running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);

/* !LINKSTO CS_SECURE_CRY_0175,1 */
/** \brief                          Finish signature verification.
 *
 *                                  This function requests the finishing of the EdDSA signature
 *                                  verification and the storing of the signature in the given
 *                                  result buffer.
 *                                  The finishing is performed in Cry_EdDSAVrfyMainFunction().
 *
 * \param[in]       signaturePtr    A pointer to the start of a buffer which holds the signature.
 * \param[in]       signatureLength Length of the signature in bytes.
 * \param[out]      resultPtr       Verification result.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the service can be started.
 *  \retval         CSM_E_NOT_OK    If the key is invalid.
 *  \retval         CSM_E_BUSY      If another instance of this service is already running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyFinish
(
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              signaturePtr,
    uint32                                                signatureLength,
    P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
);

/* !LINKSTO CS_SECURE_CRY_0176,1 */
/** \brief     Perform the EdDSAVrfy tasks.
 *
 *             This function performs the actual EdDSA signature verification tasks which
 *             have been requested by the service functions. When a task has finished, the
 *             function Csm_SignatureVerifyCallbackNotification() is called to inform the
 *             CSM of the result. If the complete signature verification has finished,
 *             additionally the function Csm_SignatureVerifyServiceFinishNotification() is called.
 */
extern FUNC(void, CRY_APPL_CODE) Cry_EdDSAVrfyMainFunction
(
   void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_EDDSA_VRFY_ENABLED == STD_ON) */

#endif /* CRY_EDDSAVRFY_H */
