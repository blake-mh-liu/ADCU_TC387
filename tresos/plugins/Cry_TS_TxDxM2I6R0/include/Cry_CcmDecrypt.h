/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_CCMDecrypt,1 */

#ifndef CRY_CCMDECRYPT_H
#define CRY_CCMDECRYPT_H

/*==[Includes]================================================================*/

#include <Cry_CcmDecryptConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start the symmetric decryption.
 **
 ** This function starts the SymDecrypt service which will
 ** decrypt blocks of data.
 **
 ** \param[in]      cfgPtr            The service configuration.
 ** \param[in]      keyPtr            Pointer to the key to be used.
 ** \param[in]      initVectorPtr     Holds a pointer to the key which has to be used
 **                                   during the symmetrical decryption computation.
 ** \param[in]      initVectorLength  Holds the length in bytes of the initialisation vector
 **                                   which has to be used during the symmetrical
 **                                   decryption computation.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK      If the service can be started.
 ** \retval   CSM_E_NOT_OK  If the key is invalid.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmDecryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr,
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) initVectorPtr,
          uint32                                    initVectorLength
);

/** \brief  Stream data to be decrypted (Single-Shot only).
 **
 ** This function streams data to be decrypted into the CSE.
 **
 ** \param[in]      iputTextPtr        A pointer to the start of an array which contains the
 **                                    constant cipher text that shall be decrypted.
 ** \param[in]      iputTextLength     Length of the constant cipher text in bytes.
 ** \param[out]     oputTextPtr        A pointer to the start of an array where the decrypted
 **                                    text will be stored.
 ** \param[in,out]  oputTextLengthPtr  Holds a pointer to a memory location in which the length
 **                                    information in bytes is stored. On calling this function this
 **                                    parameter shall contain the size of the buffer provided
 **                                    by oputTextPtr. When the request has finished, the amount
 **                                    of data that has been decrypted shall be stored.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK            If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK        If the service has not been started.
 ** \retval   CSM_E_BUSY          If another instance of this service is already
 **                               running.
 ** \retval   CSM_E_SMALL_BUFFER  If the result buffer is too small for the
 **                               decrypted data.
 **/
extern FUNC(Csm_ReturnType,CRY_CODE) Cry_CcmDecryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                            iputTextLength,
    P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
);

/** \brief  Finish decrypt.
 **
 ** This function finishes the decryption.
 **
 ** \param[out]     oputTextPtr        A pointer to the start of an array where the decrypted
 **                                    text will be stored.
 ** \param[in,out]  oputTextLengthPtr  Holds a pointer to a memory location in which the length
 **                                    information in bytes is stored. On calling this function this
 **                                    parameter shall contain the size of the buffer provided
 **                                    by oputTextPtr. When the request has finished, the amount
 **                                    of data that has been decrypted shall be stored.
 **
 ** \returns  Error code
 **
 ** \retval   CSM_E_OK            If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK        If the service has not been started.
 ** \retval   CSM_E_BUSY          If another instance of this service is already
 **                               running.
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_CcmDecryptFinish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
);

/** \brief  Perform primitive tasks.
 **
 ** This function performs periodic tasks of the primitive that may be
 ** necessary (e.g. checking if a CSE command has to be sent or if a
 ** CSE command has finished). This function is called by a
 ** corresponding CSM main function.
 **/
extern FUNC(void, CRY_CODE) Cry_CcmDecryptMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #ifndef CRY_CCMDECRYPT_H */
