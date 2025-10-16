/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EDDSAGEN_H
#define CRY_EDDSAGEN_H

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_Cry_EdDSAGen,1 */

/*==[Includes]================================================================*/
#include <Std_Types.h>

#include <Csm.h>
#include <Csm_Hash.h>
#include <Csm_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>
#include <Cry_EdDSAGenConfig.h>

#if (CRY_EDDSA_GEN_ENABLED == STD_ON)

/*==[Macros]==================================================================*/


/*==[Types]===================================================================*/
/** \brief The private key used for creating a signature */
typedef struct
{
  /** \brief Dummy element to make the type compatible with the Csm key type. */
  uint32         length;
  /** \brief The secret which has to be a b-bit string. */
  Cry_LNWordType D[CRY_EdDSA_NUM_LEN_WORDS];
}
Cry_EdDSAGenKeyType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_0178,1 */
/** \brief                          Start signature generation.
 *
 *                                  This function requests the start of the EdDSA signature
 *                                  generation for the given configuration and key.
 *                                  The start is performed in Cry_EdDSAGenMainFunction().
 *
 * \param[in]       cfgPtr          A pointer to the configuration for which the start of the
 *                                  signature generation should be requested.
 * \param[in]       privateKeyPtr   A pointer to the key which should be used in the signature
 *                                  generation.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the service can be started.
 *  \retval         CSM_E_BUSY      If another instance of this service is already running.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)                   cfgPtr,
   P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRY_APPL_DATA) privateKeyPtr
);

/* !LINKSTO CS_SECURE_CRY_0179,1 */
/** \brief                          Update signature generation.
 *
 *                                  This function requests the update of the EdDSA signature
 *                                  generation for the given data.
 *                                  The update is performed in Cry_EdDSAGenMainFunction().
 *
 * \param[in]       dataPtr         A pointer to the start of an array which contains data or
 *                                  a part of the data for which the signature should be created.
 * \param[in]       dataLength      The amount of bytes of data.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the update was successfully requested.
 *  \retval         CSM_E_NOT_OK    If no signature generation has been started
 *                                  via Cry_EdDSAGenStart().
 *  \retval         CSM_E_BUSY      If the main function is processing a requested service at the
 *                                  moment.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);

/* !LINKSTO CS_SECURE_CRY_0180,1 */
/** \brief                          Finish signature generation.
 *
 *                                  This function requests the finishing of the EdDSA signature
 *                                  generation and the storing of the signature in the given
 *                                  result buffer.
 *                                  The finishing is performed in Cry_EdDSAGenMainFunction().
 *
 * \param[out]      resultPtr       A pointer to the start of a buffer which holds the signature.
 * \param[out]      resultLengthPtr Length of the signature in bytes.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the finish was successfully requested.
 *  \retval         CSM_E_NOT_OK    If no signature generation has been started
 *                                  via Cry_EdDSAGenStart().
 *  \retval         CSM_E_BUSY      If the main function is processing a requested service at the
 *                                  moment.
 */
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenFinish
(
   P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) resultPtr,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr
);

/* !LINKSTO CS_SECURE_CRY_0181,1 */
/** \brief     Perform the EdDSAGen tasks.
 *
 *             This function performs the actual EdDSA signature generation tasks which
 *             have been requested by the service functions. When a task has finished, the
 *             function Csm_SignatureGenerateCallbackNotification() is called to inform the
 *             CSM of the result. If the complete signature generation has finished,
 *             additionally the function Csm_SignatureGenerateServiceFinishNotification() is called.
 */
extern FUNC(void, CRY_APPL_CODE) Cry_EdDSAGenMainFunction
(
   void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* if (CRY_EDDSA_GEN_ENABLED == STD_ON) */

#endif /* CRY_EDDSAGEN_H */
