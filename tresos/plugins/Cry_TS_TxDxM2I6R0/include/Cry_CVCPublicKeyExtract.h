/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_CVCPublicKeyExtract,1 */

#ifndef CRY_CVCPUBLICKEYEXTRACT_H
#define CRY_CVCPUBLICKEYEXTRACT_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                            /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_CVCPublicKeyExtractConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**  \brief  Start RSA public key extract computation.
 **
 ** This function requests the start of the RSA public key extract computation
 ** for the given configuration.
 ** The start is performed in Cry_CVCPublicKeyExtractMainFunction().
 **
 ** \param[in]      cfgPtr  A pointer to the configuration for which the start of the RSA public
 **                 key extraction is requested.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_NOT_OK  ---
 ** \retval   CSM_E_BUSY    If a service of the RSA public key extract computation is
 **                         already running.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/** \brief  Update RSA public key extract computation.
 **
 ** This function requests the update of the RSA public key extract computation
 ** for the given data.
 ** The update is performed in Cry_CVCPublicKeyExtractMainFunction().
 ** Update is called twice:
 ** 1) Cry_CVCPublicKeyExtractUpdate is first called with the Root certificate (in some documents
 ** Verify cv) changing the state of the state machine and preparing
 ** Cry_CVCPublicKeyExtractMainFunction to extract the key
 **
 ** 2) Another call of the Cry_CVCPublicKeyExtractUpdate is with Signing certificate
 ** (in some docs Key cv)
 ** changing the state of state machine and preparing Cry_CVCPublicKeyExtractMainFunction for
 ** verifying
 ** (with the previous extracted key from root cv)
 **
 ** \param[in]      dataPtr     A pointer to the start of an array which
 **                             contains the key that have to extract in
 **                             a CSM-conforming format.
 ** \param[in]      dataLength  Length of the key data in bytes.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no RSA public key extract computation was
 **                         started via Csm_SymKeyExtractStart() beforehand.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
          uint32                            dataLength
);

/** \brief  Finish RSA public key extract computation.
 **
 ** This function requests the finishing of the RSA public key extract computation
 ** and the storing of the extracted key data in the given buffer.
 ** The finish is performed in Cry_CVCPublicKeyExtractMainFunction().
 **
 ** \param[out]      keyPtr  A pointer to the structure where to store the
 **                         result.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If no RSA public key extract computation was
 **                         started via Csm_SymKeyExtractStart() beforehand.
 ** \retval   CSM_E_BUSY    If the main function is currently processing
 **                         a requested service.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/** \brief  Perform the RSA public key extract computation tasks.
 **
 ** This function performs the actual RSA public key extract computation tasks
 ** which have been requested by the service functions.
 **/
extern FUNC(void, CRY_CODE) Cry_CVCPublicKeyExtractMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CVCPUBLICKEYEXTRACT_H */
