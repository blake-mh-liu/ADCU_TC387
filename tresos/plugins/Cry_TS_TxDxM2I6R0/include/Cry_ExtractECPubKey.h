/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_ExtractECPubKey,1 */

#ifndef CRY_EXTRACTECPUBKEY_H
#define CRY_EXTRACTECPUBKEY_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_ExtractECPubKeyConfig.h>

#if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/**
 *
 * \enum Cry_ExtractECPubKeyStateType
 * \brief Internal states of the elliptic curve public key extraction.
 *
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_IDLE
 * \brief The algorithm is in the idle state.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_START
 * \brief The initialization of the algorithm is in progress.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED
 * \brief The initialization of the algorithm is completed.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_UPDATE
 * \brief The algorithm was provided with input data.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED
 * \brief The algorithm finished copying data to the internal buffer and
 *        is waiting for the user-provided output buffer.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_FINISH
 * \brief The algorithm is converting the user-provided byte array to long number representation.
 *//**
 * \var Cry_ExtractECPubKeyStateType::CRY_EXTRACT_ECPUBKEY_STATE_ERROR
 * \brief An error occurred due to the user provided data.
 */
typedef enum
{
  CRY_EXTRACT_ECPUBKEY_STATE_IDLE,
  CRY_EXTRACT_ECPUBKEY_STATE_START,
  CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED,
  CRY_EXTRACT_ECPUBKEY_STATE_UPDATE,
  CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED,
  CRY_EXTRACT_ECPUBKEY_STATE_FINISH,
  CRY_EXTRACT_ECPUBKEY_STATE_ERROR
}
Cry_ExtractECPubKeyStateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/**
 * \struct Cry_ExtractECPubKeyCtxType
 * \brief Structure which contains the context of the elliptic curve public key extraction.
 *//**
 * \var Cry_ExtractECPubKeyCtxType::keyLvl
 * \brief Stores the ammount of bytes currently copied in Cry's internal buffer.
 *//**
 * \var Cry_ExtractECPubKeyCtxType::keyLen
 * \brief Stores the length of the key provided by the user during the initialization
 *        of the algorithm.
 *//**
 * \var Cry_ExtractECPubKeyCtxType::oputDataPtr
 * \brief Stores the address of the user-provided output buffer
 *//**
 * \var Cry_ExtractECPubKeyCtxType::ctxState
 * \brief Stores the internal state of the elliptic curve public key extraction algorithm.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::ctxError
 * \brief Stores the error code which should be returned when the current task finishes.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::keyBuf
 * \brief Stores the user-provided key data.
 */
typedef struct
{
  uint32                                                 keyLvl;
  uint32                                                 keyLen;
  P2VAR(Cry_ECKeyType, TYPEDEF,  CRY_APPL_DATA )         oputDataPtr;
  Cry_ExtractECPubKeyStateType                           ctxState;
  Csm_ReturnType                                         ctxError;
  uint8                                                  keyBuf[CRY_ECPUBKEY_BUFLEN];
}
Cry_ExtractECPubKeyCtxType;

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start asym public key extract computation.
 **
 ** This function requests the start of the asym public key extract computation
 ** for the given configuration.
 ** The start is performed in Cry_ExtractECPubKeyMainFunction().
 **
 ** \param[in]      cfgId   An identification of the configuration for which
 **                         the start of the asym public key extract computation
 **                         should be requested.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK            If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK        If the configuration used is not recognised or
 **                               if the asym public key extract computation has allready been
 **                               started via Cry_ExtractECPubKeyStart()
 ** \retval   CSM_E_BUSY          If a service of the asym public key extract computation is
 **                               already running.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update asym public key extract computation.
 **
 ** This function requests the update of the asym public key extract computation
 ** for the given data.
 ** The update is performed in Cry_ExtractECPubKeyMainFunction().
 **
 ** \param[in]      dataPtr       A pointer to the start of an array which
 **                               contains the key that have to extract in
 **                               a CSM-conforming format.
 ** \param[in]      dataLength    Length of the key in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK            If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK        If no asym public key extract computation has been
 **                               started via Cry_ExtractECPubKeyStart() yet, or
 **                               if a NULL pointer is assigned as the data array
 ** \retval   CSM_E_BUSY          If the main function is currently processing
 **                               a requested service.
 ** \retval   CSM_E_SMALL_BUFFER  If the dataLength size is greater then the expected
 **                               public key size.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                    dataLength
);

/** \brief  Finish asym public key extract computation.
 **
 ** This function requests the finishing of the asym public key extract computation
 ** and the storing of the extracted key data in the given buffer.
 ** The finish is performed in Cry_ExtractECPubKeyMainFunction().
 **
 ** \param[in]      keyPtr  A pointer to the structure where to store the
 **                         result.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK            If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK        If no asym public key extract computation has been
 **                               started via Cry_ExtractECPubKeyStart() yet.
 ** \retval   CSM_E_BUSY          If the main function is currently processing
 **                               a requested service.
 ** \retval   CSM_E_SMALL_BUFFER  If the size of the structure where to store the result
 **                               is smaller than the current publick key size.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/** \brief  Perform the asym public key extract computation tasks.
 **
 ** This function performs the actual asym public key extract computation tasks
 ** which have been requested by the service functions. The function calls
 ** the main function of the configured primitive to perform the tasks.
 **/
FUNC(void, CRY_CODE) Cry_ExtractECPubKeyMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) */

#endif /* #ifndef CRY_EXTRACTECPUBKEY_H */
