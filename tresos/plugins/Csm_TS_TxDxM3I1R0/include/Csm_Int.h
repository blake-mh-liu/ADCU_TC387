/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \version 3.1.33
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CSM_INT_H
#define CSM_INT_H

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

#include <Csm_Int_Cfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_8
#include <Csm_MemMap.h>

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
/** \brief  Variable that represents whether the Csm module is fully initialized.
 **/
/* !LINKSTO CSM.Dsn.Api/Datas/00001,1 */
extern VAR(boolean, CSM_VAR) Csm_Initialized;
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_8
#include <Csm_MemMap.h>

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/** \brief   Enqueue a job into the queue
 **
 ** This function stores the job within a queue element and stores the queue element within the
 ** queue according to the job priority. If the queue is full, this function will record an error.
 **
 ** \param[in]  csmQueuePtr          Queue in which the job shall be inserted
 ** \param[in]  csmJobPtr            Job that shall be put into the queue
 **
 ** \returns    Result of the queueing attempt
 **
 ** \retval     E_OK                 Job was successfully put into the queue
 ** \retval     E_NOT_OK             Request failed, Job was not put into the queue
 ** \retval     CRYPTO_E_QUEUE_FULL  Job could not be enqueued, because the queue is full
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_QueuePushJob
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) csmQueuePtr,
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) csmJobPtr
);

/** \brief  Remove the referenced job from the queue
 **
 ** This function will search the referenced job in the queue. If it is part of the queue, the job
 ** is removed.
 **
 ** \param[in]  csmQueuePtr          Queue from which the job shall be removed
 ** \param[in]  csmJobPtr            Job that shall be removed
 **
 ** \returns    Result of the request
 **
 ** \retval     E_OK                 Job was successfully removed
 ** \retval     E_NOT_OK             Job is currently not enqueued within the referenced queue
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_QueueDelJob
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) csmQueuePtr,
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) csmJobPtr
);

/** \brief  MainFunction execution for one queue
 **
 ** This function is to be called from cyclically called MainFunction to process the requested jobs.
 ** The Csm_Main shall check the queue for jobs to pass to the underlying CRYIF.
 **
 ** \param[in]  queueIndex          Queue to be processed
 **/
extern FUNC(void, CSM_CODE) Csm_Main
(
  uint32      queueIndex
);

#if ((CSM_API_ENABLED_SERVICE_AEADDECRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_AEADDECRYPT
#define RTE_SCHM_SWCBSW_CSM_AEADDECRYPT

/** \brief  Uses the given data to perform an AEAD encryption and stores the ciphertext and the
 **         MAC in the memory locations pointed by the ciphertext pointer and Tag pointer.
 **
 ** \param[in]      jobId                 Holds the identifier of the job using the CSM
 **                                       service.
 ** \param[in]      mode                  Indicates which operation mode(s) to perfom.
 ** \param[in]      ciphertextPtr         Contains the pointer to the data to be decrypted.
 ** \param[in]      ciphertextLength      Contains the number of bytes to decrypt.
 ** \param[in]      associatedDataPtr     Contains the pointer to the associated data.
 ** \param[in]      associatedDataLength  Contains the length in bytes of the associated data.
 ** \param[in]      tagPtr                Contains the pointer to the Tag to be verified.
 ** \param[in]      tagLength             Contains the length in bytes of the Tag to be
 **                                       verified.
 ** \param[out]     plaintextPtr          Contains the pointer to the data where the decrypted
 **                                       data shall be stored.
 ** \param[in,out]  plaintextLengthPtr    Holds a pointer to the memory location in which the
 **                                       output length in bytes of the paintext is stored. On
 **                                       calling this function, this parameter shall contain
 **                                       the size of the buffer provided by plaintextPtr. When
 **                                       the request has finished, the actual length of the
 **                                       returned value shall be stored.
 ** \param[out]     verifyPtr             Contains the pointer to the result of the
 **                                       verification.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 **
 ** \ServiceID{::CSM_SID_AEADDECRYPT}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
          uint32                                              ciphertextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
          uint32                                              tagLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_AEADDECRYPT */
#endif /* #if ((CSM_API_ENABLED_SERVICE_AEADDECRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_AEADENCRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_AEADENCRYPT
#define RTE_SCHM_SWCBSW_CSM_AEADENCRYPT

/** \brief  Uses the given input data to perform a AEAD encryption and stores the ciphertext
 **         and the MAC in the memory locations pointed by the ciphertext pointer and Tag
 **         pointer.
 **
 ** \param[in]      jobId                 Holds the identifier of the job using the CSM
 **                                       service.
 ** \param[in]      mode                  Indicates which operation mode(s) to perfom.
 ** \param[in]      plaintextPtr          Contains the pointer to the data to be encrypted.
 ** \param[in]      plaintextLength       Contains the number of bytes to encrypt.
 ** \param[in]      associatedDataPtr     Contains the pointer to the associated data.
 ** \param[in]      associatedDataLength  Contains the number of bytes of the associated data.
 ** \param[out]     ciphertextPtr         Contains the pointer to the data where the encrypted
 **                                       data shall be stored.
 ** \param[in,out]  ciphertextLengthPtr   Holds a pointer to the memory location in which the
 **                                       output length in bytes of the ciphertext is stored.
 **                                       On calling this function, this parameter shall
 **                                       contain the size of the buffer in bytes provided by
 **                                       resultPtr. When the request has finished, the actual
 **                                       length of the returned value shall be stored.
 ** \param[out]     tagPtr                Contains the pointer to the data where the Tag shall
 **                                       be stored.
 ** \param[in,out]  tagLengthPtr          Holds a pointer to the memory location in which the
 **                                       output length in bytes of the Tag is stored. On
 **                                       calling this function, this parameter shall contain
 **                                       the size of the buffer in bytes provided by
 **                                       resultPtr. When the request has finished, the actual
 **                                       length of the returned value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 **
 ** \ServiceID{::CSM_SID_AEADENCRYPT}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
          uint32                                              plaintextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_AEADENCRYPT */
#endif /* #if ((CSM_API_ENABLED_SERVICE_AEADENCRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_GENERAL == STD_ON) && (CSM_RTE_ENABLED_SERVICE_GENERAL == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) && (CSM_API_ENABLED_SERVICE_SYNCHRONOUS == STD_OFF)) || (CSM_API_VERSION == CSM_API_VERSION_440) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_CANCELJOB
#define RTE_SCHM_SWCBSW_CSM_CANCELJOB

/** \brief  Removes the job in the Csm Queue and calls the job's callback with the result
 **         CRYPTO_E_JOB_CANCELED. It also passes the cancellation command to the CryIf to try
 **         to cancel the job in the Crypto Driver.
 **
 ** \param[in]  job   Holds the identifier of the job to be canceled.
 ** \param[in]  mode  Not used, just for interface compatibility provided.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \ServiceID{::CSM_SID_CANCELJOB}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Non Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
  uint32                   job,
  Crypto_OperationModeType mode
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_CANCELJOB */
#endif /* #if ((CSM_API_ENABLED_SERVICE_GENERAL == STD_ON) && (CSM_RTE_ENABLED_SERVICE_GENERAL == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) && (CSM_API_ENABLED_SERVICE_SYNCHRONOUS == STD_OFF)) || (CSM_API_VERSION == CSM_API_VERSION_440) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_CERTIFICATEPARSE
#define RTE_SCHM_SWCBSW_CSM_CERTIFICATEPARSE

/** \brief  This function shall dispatch the certificate parse function to the CRYIF.
 **
 ** \param[in]  keyId  Holds the identifier of the key to be used for the certificate parsing.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      Request successful
 ** \retval   E_NOT_OK  Request Failed
 **
 ** \ServiceID{::CSM_SID_CERTIFICATEPARSE}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse
(
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_CERTIFICATEPARSE */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_CERTIFICATEVERIFY
#define RTE_SCHM_SWCBSW_CSM_CERTIFICATEVERIFY

/** \brief  Verifies the certificate stored in the key referenced by verifyKeyId with the
 **         certificate stored in the key referenced by keyId. Note: Only certificates stored
 **         in the same Crypto Driver can be verified against each other. If the key element
 **         CRYPTO_KE_CERTIFICATE_CURRENT_TIME is used for the verification of the validity
 **         period of the certificate indentified by verifyKeyId, it shall have the same format
 **         as the timestamp in the certificate.
 **
 ** \param[in]   keyId             Holds the identifier of the key which shall be used to
 **                                validate the certificate.
 ** \param[in]   verifyCryIfKeyId  Holds the identifier of the key containing the certificate
 **                                to be verified.
 ** \param[out]  verifyPtr         Holds a pointer to the memory location which will contain
 **                                the result of the certificate verification.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      Request successful
 ** \retval   E_NOT_OK  Request Failed
 **
 ** \ServiceID{::CSM_SID_CERTIFICATEVERIFY}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify
(
        uint32                                             keyId,
        uint32                                             verifyCryIfKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_CERTIFICATEVERIFY */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_SERVICE_DECRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_DECRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_DECRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_DECRYPT
#define RTE_SCHM_SWCBSW_CSM_DECRYPT

/** \brief  Decrypts the given encrypted data and store the decrypted plaintext in the memory
 **         location pointed by the result pointer.
 **
 ** \param[in]      jobId            Holds the identifier of the job using the CSM service.
 ** \param[in]      mode             Indicates which operation mode(s) to perfom.
 ** \param[in]      dataPtr          Contains the pointer to the data to be decrypted.
 ** \param[in]      dataLength       Contains the number of bytes to decrypt.
 ** \param[out]     resultPtr        Contains the pointer to the memory location where the
 **                                  decrypted data shall be stored.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the output
 **                                  length information is stored in bytes. On calling this
 **                                  function, this parameter shall contain the size of the
 **                                  buffer provided by resultPtr. When the request has
 **                                  finished, the actual length of the returned value shall be
 **                                  stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_DECRYPT}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_DECRYPT */
#endif /* #if ((CSM_API_ENABLED_SERVICE_DECRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_DECRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_DECRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_ENCRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_ENCRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_ENCRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_ENCRYPT
#define RTE_SCHM_SWCBSW_CSM_ENCRYPT

/** \brief  Encrypts the given data and store the ciphertext in the memory location pointed by
 **         the result pointer.
 **
 ** \param[in]      jobId            Holds the identifier of the job using the CSM service.
 ** \param[in]      mode             Indicates which operation mode(s) to perfom.
 ** \param[in]      dataPtr          Contains the pointer to the data to be encrypted.
 ** \param[in]      dataLength       Contains the number of bytes to encrypt.
 ** \param[out]     resultPtr        Contains the pointer to the data where the encrypted data
 **                                  shall be stored.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the output
 **                                  length information is stored in bytes. On calling this
 **                                  function, this parameter shall contain the size of the
 **                                  buffer provided by resultPtr. When the request has
 **                                  finished, the actual length of the returned value shall be
 **                                  stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_ENCRYPT}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_ENCRYPT */
#endif /* #if ((CSM_API_ENABLED_SERVICE_ENCRYPT == STD_ON) && (CSM_RTE_ENABLED_SERVICE_ENCRYPT == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_ENCRYPT_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_HASH == STD_ON) && (CSM_RTE_ENABLED_SERVICE_HASH == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_HASH_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_HASH
#define RTE_SCHM_SWCBSW_CSM_HASH

/** \brief  Uses the given data to perform the hash calculation and stores the hash.
 **
 ** \param[in]      jobId            Holds the identifier of the job using the CSM service.
 ** \param[in]      mode             Indicates which operation mode(s) to perfom.
 ** \param[in]      dataPtr          Contains the pointer to the data for which the hash shall
 **                                  be computed.
 ** \param[in]      dataLength       Contains the number of bytes to be hashed.
 ** \param[out]     resultPtr        Contains the pointer to the data where the hash value
 **                                  shall be stored.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the output
 **                                  length in bytes is stored. On calling this function, this
 **                                  parameter shall contain the size of the buffer provided by
 **                                  resultPtr. When the request has finished, the actual
 **                                  length of the returned value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                   request successful
 ** \retval   E_NOT_OK               request failed
 ** \retval   CRYPTO_E_BUSY          request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL    request failed, the queue is full
 ** \retval   CRYPTO_E_SMALL_BUFFER  the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_HASH}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_HASH */
#endif /* #if ((CSM_API_ENABLED_SERVICE_HASH == STD_ON) && (CSM_RTE_ENABLED_SERVICE_HASH == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_HASH_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYCOPY
#define RTE_SCHM_SWCBSW_CSM_KEYCOPY

/** \brief  This function shall copy all key elements from the source key to a target key.
 **
 ** \param[in]  keyId        Holds the identifier of the key whose key element shall be the
 **                          source element.
 ** \param[in]  targetKeyId  Holds the identifier of the key whose key element shall be the
 **                          destination element.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        Request successful
 ** \retval   E_NOT_OK                    Request Failed
 ** \retval   CRYPTO_E_BUSY               Request Failed, Crypto Driver Object is Busy
 ** \retval   CRYPTO_E_KEY_NOT_AVAILABLE  Request failed, the requested key element is not available
 ** \retval   CRYPTO_E_KEY_READ_FAIL      Request failed, not allowed to extract key element
 ** \retval   CRYPTO_E_KEY_WRITE_FAIL     Request failed, not allowed to write key element
 ** \retval   CRYPTO_E_KEY_SIZE_MISMATCH  Request failed, key element sizes are not compatible
 **
 ** \ServiceID{::CSM_SID_KEYCOPY}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
  uint32 keyId,
  uint32 targetKeyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYCOPY */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYDERIVE
#define RTE_SCHM_SWCBSW_CSM_KEYDERIVE

/** \brief  Derives a new key by using the key elements in the given key identified by the
 **         keyId. The given key contains the key elements for the password and salt. The
 **         derived key is stored in the key element with the id 1 of the key identified by
 **         targetCryptoKeyId.
 **
 ** \param[in]  keyId        Holds the identifier of the key which is used for key derivation.
 ** \param[in]  targetKeyId  Holds the identifier of the key which is used to store the derived
 **                          key.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK           Request successful
 ** \retval   E_NOT_OK       Request Failed
 ** \retval   CRYPTO_E_BUSY  Request Failed, Crypto Driver Object is Busy
 **
 ** \ServiceID{::CSM_SID_KEYDERIVE}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
  uint32 keyId,
  uint32 targetKeyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYDERIVE */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPY
#define RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPY

/** \brief  This function shall copy a key elements from one key to a target key.
 **
 ** \param[in]  keyId               Holds the identifier of the key whose key element shall be
 **                                 the source element.
 ** \param[in]  keyElementId        Holds the identifier of the key element which shall be the
 **                                 source for the copy operation.
 ** \param[in]  targetKeyId         Holds the identifier of the key whose key element shall be
 **                                 the destination element.
 ** \param[in]  targetKeyElementId  Holds the identifier of the key element which shall be the
 **                                 destination for the copy operation.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        Request successful
 ** \retval   E_NOT_OK                    Request Failed
 ** \retval   CRYPTO_E_BUSY               Request Failed, Crypto Driver Object is Busy
 ** \retval   CRYPTO_E_KEY_NOT_AVAILABLE  Request failed, the requested key element is not available
 ** \retval   CRYPTO_E_KEY_READ_FAIL      Request failed, not allowed to extract key element
 ** \retval   CRYPTO_E_KEY_WRITE_FAIL     Request failed, not allowed to write key element
 ** \retval   CRYPTO_E_KEY_SIZE_MISMATCH  Request failed, key element sizes are not compatible
 **
 ** \ServiceID{::CSM_SID_KEYELEMENTCOPY}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for the same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 targetKeyId,
  uint32 targetKeyElementId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPY */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTGET
#define RTE_SCHM_SWCBSW_CSM_KEYELEMENTGET

/** \brief  Retrieves the key element bytes from a specific key element of the key identified
 **         by the keyId and stores the key element in the memory location pointed by the key
 **         pointer.
 **
 ** \param[in]      keyId         Holds the identifier of the key from which a key element
 **                               shall be extracted.
 ** \param[in]      keyElementId  Holds the identifier of the key element to be extracted.
 ** \param[out]     keyPtr        Holds the pointer to the memory location where the key shall
 **                               be copied to.
 ** \param[in,out]  keyLengthPtr  Holds a pointer to the memory location in which the output
 **                               buffer length in bytes is stored. On calling this function,
 **                               this parameter shall contain the buffer length in bytes of
 **                               the keyPtr. When the request has finished, the actual size of
 **                               the written input bytes shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        request successful
 ** \retval   E_NOT_OK                    request failed
 ** \retval   CRYPTO_E_BUSY               Request Failed, Crypto Driver Object is Busy
 ** \retval   CRYPTO_E_KEY_NOT_AVAILABLE  request failed, the requested key element is not available
 ** \retval   CRYPTO_E_KEY_READ_FAIL      Request failed because read access was denied
 ** \retval   CRYPTO_E_SMALL_BUFFER       the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_KEYELEMENTGET}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
        uint32                            keyId,
        uint32                            keyElementId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTGET */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTSET
#define RTE_SCHM_SWCBSW_CSM_KEYELEMENTSET

/** \brief  Sets the given key element bytes to the key identified by keyId.
 **
 ** \param[in]  keyId         Holds the identifier of the key for which a new material shall be
 **                           set.
 ** \param[in]  keyElementId  Holds the identifier of the key element to be written.
 ** \param[in]  keyPtr        Holds the pointer to the key element bytes to be processed.
 ** \param[in]  keyLength     Contains the number of key element bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        request successful
 ** \retval   E_NOT_OK                    request failed
 ** \retval   CRYPTO_E_BUSY               Request Failed, Crypto Driver Object is Busy
 ** \retval   CRYPTO_E_KEY_WRITE_FAIL     Request failed because write access was denied
 ** \retval   CRYPTO_E_KEY_NOT_AVAILABLE  Request failed because the key is not available
 ** \retval   CRYPTO_E_KEY_SIZE_MISMATCH  Request failed, key element size does not match size of provided data
 **
 ** \ServiceID{::CSM_SID_KEYELEMENTSET}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Non Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
          uint32                            keyId,
          uint32                            keyElementId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
          uint32                            keyLength
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTSET */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCPUBVAL
#define RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCPUBVAL

/** \brief  Calculates the public value of the current user for the key exchange and stores the
 **         public key in the memory location pointed by the public value pointer.
 **
 ** \param[in]      keyId                 Holds the identifier of the key which shall be used
 **                                       for the key exchange protocol.
 ** \param[out]     publicValuePtr        Contains the pointer to the data where the public
 **                                       value shall be stored.
 ** \param[in,out]  publicValueLengthPtr  Holds a pointer to the memory location in which the
 **                                       public value length information is stored. On calling
 **                                       this function, this parameter shall contain the size
 **                                       of the buffer provided by publicValuePtr. When the
 **                                       request has finished, the actual length of the
 **                                       returned value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_KEYEXCHANGECALCPUBVAL}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
        uint32                            keyId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCPUBVAL */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCSECRET
#define RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCSECRET

/** \brief  Calculates the shared secret key for the key exchange with the key material of the
 **         key identified by the keyId and the partner public key. The shared secret key is
 **         stored as a key element in the same key.
 **
 ** \param[in]  keyId                     Holds the identifier of the key which shall be used
 **                                       for the key exchange protocol.
 ** \param[in]  partnerPublicValuePtr     Holds the pointer to the memory location which
 **                                       contains the partner's public value.
 ** \param[in]  partnerPublicValueLength  Contains the length of the partner's public value in
 **                                       bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                   Request successful
 ** \retval   E_NOT_OK               Request Failed
 ** \retval   CRYPTO_E_BUSY          Request Failed, Crypto Driver Object is Busy
 ** \retval   CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_KEYEXCHANGECALCSECRET}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
          uint32                            partnerPublicValueLength
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYEXCHANGECALCSECRET */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYGENERATE
#define RTE_SCHM_SWCBSW_CSM_KEYGENERATE

/** \brief  Generates new key material and store it in the key identified by keyId.
 **
 ** \param[in]  keyId  Holds the identifier of the key for which a new material shall be
 **                    generated.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      Request successful
 ** \retval   E_NOT_OK  Request Failed
 **
 ** \ServiceID{::CSM_SID_KEYGENERATE}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYGENERATE */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYSETVALID
#define RTE_SCHM_SWCBSW_CSM_KEYSETVALID

/** \brief  Sets the key state of the key identified by keyId to valid.
 **
 ** \param[in]  keyId  Holds the identifier of the key for which a new material shall be
 **                    validated.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK           request successful
 ** \retval   E_NOT_OK       request failed
 ** \retval   CRYPTO_E_BUSY  Request Failed, Crypro Driver Object is Busy
 **
 ** \ServiceID{::CSM_SID_KEYSETVALID}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Non Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYSETVALID */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_SERVICE_MACGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_MACGENERATE
#define RTE_SCHM_SWCBSW_CSM_MACGENERATE

/** \brief  Uses the given data to perform a MAC generation and stores the MAC in the memory
 **         location pointed to by the MAC pointer.
 **
 ** \param[in]      jobId         Holds the identifier of the job using the CSM service.
 ** \param[in]      mode          Indicates which operation mode(s) to perfom.
 ** \param[in]      dataPtr       Contains the pointer to the data for which the MAC shall be
 **                               computed.
 ** \param[in]      dataLength    Contains the number of bytes to be hashed.
 ** \param[out]     macPtr        Contains the pointer to the data where the MAC shall be
 **                               stored.
 ** \param[in,out]  macLengthPtr  Holds a pointer to the memory location in which the output
 **                               length in bytes is stored. On calling this function, this
 **                               parameter shall contain the size of the buffer provided by
 **                               macPtr. When the request has finished, the actual length of
 **                               the returned MAC shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_MACGENERATE}
 ** \Synchronicity{Asynchronous or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) macLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_MACGENERATE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_MACGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_MACVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACVERIFY == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACVERIFY_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_MACVERIFY
#define RTE_SCHM_SWCBSW_CSM_MACVERIFY

/** \brief  Verifies the given MAC by comparing if the MAC is generated with the given data.
 **
 ** \param[in]   jobId       Indicates which operation mode(s) to perfom.
 ** \param[in]   mode        Indicates which operation mode(s) to perfom.
 ** \param[in]   dataPtr     Holds a pointer to the data for which the MAC shall be verified.
 ** \param[in]   dataLength  Contains the number of data bytes for which the MAC shall be
 **                          verified.
 ** \param[in]   macPtr      Holds a pointer to the MAC to be verified.
 ** \param[in]   macLength   Contains the MAC length in BITS to be verified.
 ** \param[out]  verifyPtr   Holds a pointer to the memory location, which will hold the result
 **                          of the MAC verification.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 **
 ** \ServiceID{::CSM_SID_MACVERIFY}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
          uint32                                              macLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_MACVERIFY */
#endif /* #if ((CSM_API_ENABLED_SERVICE_MACVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACVERIFY == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_MACVERIFY_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_RANDOMGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_RANDOMGENERATE
#define RTE_SCHM_SWCBSW_CSM_RANDOMGENERATE

/** \brief  Generate a random number and stores it in the memory location pointed by the result
 **         pointer.
 **
 ** \param[in]      jobId            Holds the identifier of the job using the CSM service.
 ** \param[out]     resultPtr        Holds a pointer to the memory location which will hold the
 **                                  result of the random number generation.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the result
 **                                  length in bytes is stored. On calling this function, this
 **                                  parameter shall contain the number of random bytes, which
 **                                  shall be stored to the buffer provided by resultPtr. When
 **                                  the request has finished, the actual length of the
 **                                  returned value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                         request successful
 ** \retval   E_NOT_OK                     request failed
 ** \retval   CRYPTO_E_BUSY                request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL          request failed, the queue is full
 ** \retval   CRYPTO_E_ENTROPY_EXHAUSTION  request failed, entropy of random number generator is exhausted
 **
 ** \ServiceID{::CSM_SID_RANDOMGENERATE}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
        uint32                            jobId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_RANDOMGENERATE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_RANDOMGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_RANDOMSEED
#define RTE_SCHM_SWCBSW_CSM_RANDOMSEED

/** \brief  This function shall dispatch the random seed function to the configured crypto
 **         driver object.
 **
 ** \param[in]  keyId       Holds the identifier of the key for which a new seed shall be
 **                         generated.
 ** \param[in]  seedPtr     Holds a pointer to the memory location which contains the data to
 **                         feed the seed.
 ** \param[in]  seedLength  Contains the length of the seed in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      Request successful
 ** \retval   E_NOT_OK  Request Failed
 **
 ** \ServiceID{::CSM_SID_RANDOMSEED}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                            seedLength
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_RANDOMSEED */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */

#if ((CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_SIGNATUREGENERATE
#define RTE_SCHM_SWCBSW_CSM_SIGNATUREGENERATE

/** \brief  Uses the given data to perform the signature calculation and stores the signature
 **         in the memory location pointed by the result pointer.
 **
 ** \param[in]      jobId            Holds the identifier of the job using the CSM service.
 ** \param[in]      mode             Indicates which operation mode(s) to perform.
 ** \param[in]      dataPtr          Contains the pointer to the data to be signed.
 ** \param[in]      dataLength       Contains the number of bytes to sign.
 ** \param[out]     resultPtr        Contains the pointer to the data where the signature shall
 **                                  be stored.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the output
 **                                  length in bytes of the signature is stored. On calling
 **                                  this function, this parameter shall contain the size of
 **                                  the buffer provided by resultPtr. When the request has
 **                                  finished, the actual length of the returned value shall be
 **                                  stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_SIGNATUREGENERATE}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_SIGNATUREGENERATE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if ((CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U)))
#ifndef RTE_SCHM_SWCBSW_CSM_SIGNATUREVERIFY
#define RTE_SCHM_SWCBSW_CSM_SIGNATUREVERIFY

/** \brief  Verifies the given MAC by comparing if the signature is generated with the given
 **         data.
 **
 ** \param[in]   jobId            Holds the identifier of the job using the CSM service.
 ** \param[in]   mode             The Crypto_JobInfoType job with the corresponding jobId shall
 **                               be modified in the following way:.
 ** \param[in]   dataPtr          Contains the pointer to the data to be verified.
 ** \param[in]   dataLength       Contains the number of data bytes.
 ** \param[in]   signaturePtr     Holds a pointer to the signature to be verified.
 ** \param[in]   signatureLength  Contains the signature length in bytes.
 ** \param[out]  verifyPtr        Holds a pointer to the memory location, which will hold the
 **                               result of the signature verification.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    request successful
 ** \retval   E_NOT_OK                request failed
 ** \retval   CRYPTO_E_BUSY           request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_SMALL_BUFFER   the provided buffer is too small to store the result
 **
 ** \ServiceID{::CSM_SID_SIGNATUREVERIFY}
 ** \Synchronicity{Sync or Async, dependend on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) signaturePtr,
          uint32                                              signatureLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_SIGNATUREVERIFY */
#endif /* #if ((CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON) && (((CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) && (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_SYNC == STD_OFF)) || (CSM_PRT_COUNT != 0U))) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U))
#ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPYPARTIAL
#define RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPYPARTIAL

/** \brief  Copies a key element to another key element in the same crypto driver. The
 **         keyElementSourceOffset and keyElementCopyLength allows to copy just a part of the
 **         source key element into the destination. The offset into the target key is also
 **         specified with this function.
 **
 ** \param[in]  keyId                   Holds the identifier of the key whose key element shall
 **                                     be the source element for copy operation.
 ** \param[in]  keyElementId            Holds the identifier of the key element which shall be
 **                                     the source for the copy operation.
 ** \param[in]  keyElementSourceOffset  This is the offset of the source key element indicating
 **                                     the start index of the copy operation.
 ** \param[in]  keyElementTargetOffset  This is the offset of the destination key element
 **                                     indicating the start index of the copy operation.
 ** \param[in]  keyElementCopyLength    Specifies the number of bytes that shall be copied.
 ** \param[in]  targetKeyId             Holds the identifier of the key whose key element shall
 **                                     be the destination element.
 ** \param[in]  targetKeyElementId      Holds the identifier of the key element which shall be
 **                                     the destination for the copy operation.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        Request successful
 ** \retval   E_NOT_OK                    Request failed
 ** \retval   CRYPTO_E_BUSY               Request failed, Crypto Driver Object is busy
 ** \retval   CRYPTO_E_KEY_NOT_AVAILABLE  Request failed, the requested key element is not available
 ** \retval   CRYPTO_E_KEY_READ_FAIL      Request failed, not allowed to extract key element
 ** \retval   CRYPTO_E_KEY_WRITE_FAIL     Request failed, not allowed to write key element
 ** \retval   CRYPTO_E_KEY_SIZE_MISMATCH  Request failed, key element sizes are not compatible
 ** \retval   CRYPTO_E_KEY_EMPTY          Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_KEYELEMENTCOPYPARTIAL}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant, but not for the same keyId}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 keyElementSourceOffset,
  uint32 keyElementTargetOffset,
  uint32 keyElementCopyLength,
  uint32 targetKeyId,
  uint32 targetKeyElementId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_KEYELEMENTCOPYPARTIAL */
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_RTE_ENABLED_KEYMNGMNT == STD_ON) && (CSM_PRT_COUNT != 0U)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYSETVALID
#define RTE_SCHM_SWCBSW_CSM_JOBKEYSETVALID

/** \brief  Stores the key if necessary and sets the key state of the key identified by keyId
 **         to valid.
 **
 ** \param[in]  jobId  Holds the identifier of the job using the CSM service.
 ** \param[in]  keyId  Holds the identifier of the key for which a new material shall be
 **                    validated.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK           Request successful
 ** \retval   E_NOT_OK       Request failed
 ** \retval   CRYPTO_E_BUSY  Request failed, Crypro Driver Object is busy
 **
 ** \ServiceID{::CSM_SID_JOBKEYSETVALID}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
  uint32 jobId,
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYSETVALID */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBRANDOMSEED
#define RTE_SCHM_SWCBSW_CSM_JOBRANDOMSEED

/** \brief  This function shall dispatch the random seed function to the configured crypto
 **         driver object.
 **
 ** \param[in]  jobId       Holds the identifier of the job using the CSM service.
 ** \param[in]  keyId       Holds the identifier of the key for which a new seed shall be
 **                         generated.
 ** \param[in]  seedPtr     Holds a pointer to the memory location which contains the data to
 **                         feed the seed.
 ** \param[in]  seedLength  Contains the length of the seed in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   CRYPTO_E_BUSY           Request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 **
 ** \ServiceID{::CSM_SID_JOBRANDOMSEED}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
          uint32                            jobId,
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                            seedLength
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBRANDOMSEED */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYGENERATE
#define RTE_SCHM_SWCBSW_CSM_JOBKEYGENERATE

/** \brief  Generates new key material and stores it in the key identified by keyId.
 **
 ** \param[in]  jobId  Holds the identifier of the job using the CSM service.
 ** \param[in]  keyId  Holds the identifier of the key for which a new material shall be
 **                    generated.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   CRYPTO_E_BUSY           Request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBKEYGENERATE}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
  uint32 jobId,
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYGENERATE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYDERIVE
#define RTE_SCHM_SWCBSW_CSM_JOBKEYDERIVE

/** \brief  Derives a new key by using the key elements in the given key identified by the
 **         keyId. The given key contains the key elements for the password and salt. The
 **         derived key is stored in the key element with the id 1 of the key identified by
 **         targetCryptoKeyId.
 **
 ** \param[in]  jobId        Holds the identifier of the job using the CSM service.
 ** \param[in]  keyId        Holds the identifier of the key which is used for key derivation.
 ** \param[in]  targetKeyId  Holds the identifier of the key which is used to store the derived
 **                          key.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                        Request successful
 ** \retval   E_NOT_OK                    Request failed
 ** \retval   CRYPTO_E_BUSY               Request failed, service is still busy
 ** \retval   CRYPTO_E_QUEUE_FULL         Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_READ_FAIL      Request failed, not allowed to extract key element
 ** \retval   CRYPTO_E_KEY_WRITE_FAIL     Request failed, not allowed to write key element
 ** \retval   CRYPTO_E_KEY_NOT_VALID      Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_SIZE_MISMATCH  Request failed, key element sizes are not compatible
 ** \retval   CRYPTO_E_KEY_EMPTY          Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBKEYDERIVE}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive
(
  uint32 jobId,
  uint32 keyId,
  uint32 targetKeyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYDERIVE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCPUBVAL
#define RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCPUBVAL

/** \brief  Calculates the public value of the current user for the key exchange and stores the
 **         public key in the memory location pointed by the public value pointer.
 **
 ** \param[in]      jobId                 Holds the identifier of the job using the CSM
 **                                       service.
 ** \param[in]      keyId                 Holds the identifier of the key which shall be used
 **                                       for the key exchange protocol.
 ** \param[out]     publicValuePtr        Contains the pointer to the data where the public
 **                                       value shall be stored.
 ** \param[in,out]  publicValueLengthPtr  Holds a pointer to the memory location in which the
 **                                       public value length information is stored. On calling
 **                                       this function, this parameter shall contain the size
 **                                       of the buffer provided by publicValuePtr. When the
 **                                       request has finished, the actual length of the
 **                                       returned value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   CRYPTO_E_BUSY           Request failed, service is still busy
 ** \retval   CRYPTO_E_SMALL_BUFFER   The provided buffer is too small to store the result
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBKEYEXCHANGECALCPUBVAL}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
        uint32                            jobId,
        uint32                            keyId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCPUBVAL */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCSECRET
#define RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCSECRET

/** \brief  Calculates the shared secret key for the key exchange with the key material of the
 **         key identified by the keyId and the partner public key. The shared secret key is
 **         stored as a key element in the same key.
 **
 ** \param[in]  jobId                     Holds the identifier of the job using the CSM
 **                                       service.
 ** \param[in]  keyId                     Holds the identifier of the key which shall be used
 **                                       for the key exchange protocol.
 ** \param[in]  partnerPublicValuePtr     Holds the pointer to the memory location which
 **                                       contains the partner's public value.
 ** \param[in]  partnerPublicValueLength  Contains the length of the partner's public value in
 **                                       bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   E_BUSY                  Request failed, Crypto Driver Object is busy
 ** \retval   CRYPTO_E_SMALL_BUFFER   The provided buffer is too small to store the result
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBKEYEXCHANGECALCSECRET}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
          uint32                            jobId,
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
          uint32                            partnerPublicValueLength
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBKEYEXCHANGECALCSECRET */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEPARSE
#define RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEPARSE

/** \brief  This function shall dispatch the certificate parse function to the CRYIF.
 **
 ** \param[in]  jobId  Holds the identifier of the job using the CSM service.
 ** \param[in]  keyId  Holds the identifier of the key to be used for the certificate parsing.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   E_BUSY                  Request failed, Crypto Driver Object is busy
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBCERTIFICATEPARSE}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateParse
(
  uint32 jobId,
  uint32 keyId
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEPARSE */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if ((CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON))
#ifndef RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEVERIFY
#define RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEVERIFY

/** \brief  Verifies the certificate stored in the key referenced by verifyKeyId with the
 **         certificate stored in the key referenced by keyId. Note: Only certificates stored
 **         in the same Crypto Driver can be verified against each other. If the key element
 **         CRYPTO_KE_CERTIFICATE_CURRENT_TIME is used for the verification of the validity
 **         period of the certificate indentified by verifyKeyId, it shall have the same format
 **         as the timestamp in the certificate.
 **
 ** \param[in]   jobId        Holds the identifier of the job using the CSM service.
 ** \param[in]   keyId        Holds the identifier of the key which shall be used to validate
 **                           the certificate.
 ** \param[in]   verifyKeyId  Holds the identifier of the key containing the certificate to be
 **                           verified.
 ** \param[out]  verifyPtr    Holds a pointer to the memory location which will contain the
 **                           result of the certificate verification.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                    Request successful
 ** \retval   E_NOT_OK                Request failed
 ** \retval   E_BUSY                  Request failed, Crypto Driver Object is busy
 ** \retval   CRYPTO_E_QUEUE_FULL     Request failed, the queue is full
 ** \retval   CRYPTO_E_KEY_NOT_VALID  Request failed, the key's state is 'invalid'
 ** \retval   CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element
 **
 ** \ServiceID{::CSM_SID_JOBCERTIFICATEVERIFY}
 ** \Synchronicity{Sync or Async, depending on the job configuration}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateVerify
(
        uint32                                             jobId,
        uint32                                             keyId,
        uint32                                             verifyKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_JOBCERTIFICATEVERIFY */
#endif /* #if ((CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON) && (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON)) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/** \brief  Notifies the CSM that a job has finished. This function is used by the underlying
 **         layer (CRYIF).
 **
 ** \param[in]  job     Holds a pointer to the job, which has finished.
 ** \param[in]  result  Contains the result of the cryptographic operation.
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(void, CSM_CODE) Csm_Int_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CSM_INT_H */

/*==================[end of file]=================================================================*/

