/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_ExtractRsaPublicKey,1 */

#ifndef CRY_EXTRACTRSAPUBLICKEY_H
#define CRY_EXTRACTRSAPUBLICKEY_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_ExtractRsaPublicKeyConfig.h>

#if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start RSA public key extract computation.
 **
 ** This function requests the start of the RSA public key extract computation
 ** for the given configuration.
 ** The start is performed in Cry_ExtractRsaPublicKeyMainFunction().
 **
 ** \param[in]      cfgId   An identification of the configuration for which
 **                         the start of the RSA public key extract computation
 **                         should be requested.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK  ---
 ** \retval   CSM_E_BUSY    If a service of the RSA public key extract computation is
 **                         already running.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update RSA public key extract computation.
 **
 ** This function requests the update of the RSA public key extract computation
 ** for the given data.
 ** The update is performed in Cry_ExtractRsaPublicKeyMainFunction().
 **
 ** \param[in]      dataPtr     A pointer to the start of an array which
 **                             contains the key that have to extract in
 **                             a CSM-conforming format.
 ** \param[in]      dataLength  Length of the key in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no RSA public key extract computation has been
 **                         started via Csm_AsymPublicKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
      VAR(uint32, AUTOMATIC               ) dataLength
);

/** \brief  Finish RSA public key extract computation.
 **
 ** This function requests the finishing of the RSA public key extract computation
 ** and the storing of the extracted key data in the given buffer.
 ** The finish is performed in Cry_ExtractRsaPublicKeyMainFunction().
 **
 ** \param[in]      keyPtr  A pointer to the structure where to store the
 **                         result.
 **
 ** \returns  Error value.
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no RSA public key extract computation has been
 **                         started via Csm_AsymPublicKeyExtractStart(), yet.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/** \brief  Perform the RSA public key extract computation tasks.
 **
 ** This function performs the actual RSA public key extract computation tasks
 ** which have been requested by the service functions.
 **/
FUNC(void, CRY_CODE) Cry_ExtractRsaPublicKeyMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE) */

#endif /* #ifndef CRY_EXTRACTRSAPUBLICKEY_H */
