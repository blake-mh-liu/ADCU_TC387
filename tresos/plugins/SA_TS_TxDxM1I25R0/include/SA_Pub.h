#ifndef SA_PUB_H
#define SA_PUB_H

/*===============================================================================*/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Pub.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

#include "SA_Types.h"
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
#if (SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)
/* Limit request seed counter */
extern tLimitReqSeedInfo m_stLimitReqSeed;
#endif /*(SA_LIMIT_NB_REQUEST_SEED_ENABLED == STD_ON)*/

#if (SA_CSMASR43_USED == STD_ON)
/* Array of Prog-Csm JobConf */
extern const tSACsmJobConf m_astSACsmJobConf[SA_CSM_NUMCONF_JOBS];
#endif


/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/** \brief Initialize layer
 **
 ** This function initializes the SA layer, shall be called only once at ECU startup
 **
 **/
extern void SA_Init(void);

/** \brief Manage the SA layer periodic task
**
** This function is the periodic function managing the SA layer
**
**/
extern void SA_Manage(void);

/** \brief Compute the key from an static key and a random Seed
 **
 ** This function is called upon correct SA1 request
 ** It first call SA_GetRandomValue to get a random value.
 ** Then it computes the key following an algorithm from this random seed
 ** and a static key predefined.
 ** The random generated Seed is then send back to lower layer.
 **
 ** \return Result of GetSeed action
 ** \param[out] aubSeed Output buffer to send back the random Seed
 **
 **/
extern tSaStatus SA_GetSeed(u8* aubSeed);

/** \brief Compare the received and calcluated key
 **
 ** This function is called upon correct SA2 request
 ** It compare the received key from the diagnostic request to the one calculated into SA_ComputeSeed
 ** It then return the result
 **
 ** \param[in] aubReceivedKey input buffer with the received key from the network
 **
 ** \return Result of comparison
 ** \retval PROG_STATUS_OK Both key are the same
 ** \retval PROG_STATUS_NOT_OK Both key are different
 **
 **/
extern tSaStatus SA_CompareKey(u8* aubReceivedKey);

#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && (PROG_CAL_PRESENT == STD_OFF))

/** \brief Decompression variable initialization
 **
 ** This function is called at init and for each request Download
 ** to intialize all decompression variable.
 **
 **/
extern void SA_DecompressInit (void);

/** \brief reinit decompression input param
 **
 ** This function Reinitializes the input decompression parameter after each TD
 **
 **/
extern void SA_DecompInputParamInit(void);


/** \brief store the data to be decompress
 **
 ** This function is used to store the data received from the network to
 ** an input buffer. The decompression will be done asynchronously afterward.
 **
 ** \param[in] pubData Input buffer where the data to decompress are stored
 ** \param[in] ulDataLength Length of data to decompress from the buffer
 **
 **/
extern void SA_DecompressData(u8* pubData, PduLengthType ulDataLength);

/** \brief decompress a byte of the input buffer
 **
 ** This function Decompress a byte of the input buffer data with LZSS algorithm.
 ** Each decompressed byte is then store into an Output buffer
 **
 **/
extern void SA_DecompressManage(void);

/** \brief Accessor to get the decompressed data
 **
 ** This function allows to get the decompressed data from the buffer
 **
 ** \param[out] pubDecompData Output buffer where the data decompressed are copied
 ** \param[out] pulDecompressLength Total length of data decompressed
 **
 **/
extern tDecompressStateType SA_GetDecompressedData(u8** pubDecompData, PduLengthType* pulDecompressLength);

/** \brief freed the written data from output buffer
 **
 ** This function allows to freed the written data from output buffer
 **
 ** \param[in] uwLength length written with sucess that shall be freed from output buffer
 **
 **/
extern void SA_DecompWriteDataConfirmation(u16 uwLength);
#endif

#if (SA_USE_CRYPTO == STD_ON)
/** \brief API is a unique callback called by CSM module to treat random generation, encryption, decryption, hash and signature verification
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
#if (SA_CSMASR43_USED == STD_OFF)
extern Std_ReturnType SA_CsmNotification(Csm_ReturnType eCsmResult);
#endif
extern tSaCsmState m_eSaCsmState;
extern u8* m_pubDataRandomNumber;
extern u8 m_aubLastRandomNumber[SA_RANDOM_NUMBER_LENGTH];
extern u8 m_aubCurrentRandomNumber[SA_RANDOM_NUMBER_LENGTH];
extern tSaBoolean m_ubGenRandReqReceived;
extern Csm_AsymPublicKeyType m_stAsymPublicKey;
extern const u8* m_pubCryptoSignature;
extern u8 m_ubVerifSigUpdateReqReceived;
extern Csm_VerifyResultType m_ubVerifyResult;
#endif /*(SA_USE_CRYPTO == STD_ON)*/

#if (SA_STATIC_SEED_ENABLED == STD_ON)
extern u8 m_ubLastSeedWasUsed;
extern u8 m_aubLastSeed[SA_SEED_LEN];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

/** \brief API called by PROG module to get the SecurityAccess status
**
**
**/
extern tSaStatus SA_GetStatus(void);

extern tSaStatus m_eSaStatus;

#if (SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)

/*Variable to store the MAC algo parameters needed for MAC generation and Verification*/
extern tSA_MACAlgo m_stMACpar;

/*Variable to store the AES algo parameters needed for Encryption and Decryption*/
extern tSA_AESCTRAlgo m_stAESCTRpar;

/*Stores the pointer to the Request-Response Buffer of SA1 and SA2 Request/Response*/
extern u8 * m_pubSAReqResptr;

extern u8 m_ubMacVerificationResult;

/*Stores the Secured Key Programming Status*/
extern tSaStatus m_ubSaAllKeysStatus;

/** \brief Manages the Authentication Method 0001 Procedure Sequence and Transitions
 **
 ** This function triggers start of operation for every state of Authentication Method 0001,
 ** also sets the next state of operation.
 **
 **/
extern void SA_AuthMethod0001(void);

/** \brief Concatenate the input block of data and store in a given output buffer
 **
 ** This function concatenates the input block of data and stores in a given output buffer.
 **
 **/
extern void SA_ConcatenateAndStoreData(tSA_ConcatenatePar *aubInputData, u32 ulInputbufCount, u8 * aubStore);

/** \brief Set the status of the current state and set the response to be sent in the event of failure
 **
 ** This function sets/resets the status of the current state by resetting the Busy status and, in the
 ** event of failure sets the State staus to failure and decides the type of response to be sent.
 **
 **/
extern void SA_AM0001_SetStatus(tSaStatus eSaStatus);

/** \brief Retrieve the Current State
 **
 ** This function retrieves the current state of Authentication Method 0001 procedure.
 **
 **/
extern tSA_AuthenticationState SA_AM0001_GetState(void);

/** \brief Set the Authentication Method 0001 State
 **
 ** This function sets the current state of the Authentication Method 0001 procedure.
 **
 **/
extern void SA_AM0001_SetState(tSA_AuthenticationState ulAuthentication0001State);

#if (SA_SECUREDKEYS_STATUSREAD == STD_ON)
/** \brief Retrieves SA programmed Key status
 **
 ** This function retrieves the status of the Stored secure-keys used for the
 ** SA Authentication Method 0001 procedure
 **
 **/
extern tSaStatus SA_GetSecuredKeysStatus(void);

/** \brief Sets the SA programmed Key status
 **
 ** This function sets the SA programmed Key status of the Authentication Method 0001 procedure.
 **
 **/
extern void SA_SetSecuredKeyStatus(Csm_ReturnType eCsmResult);

#endif

#endif/*SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/

#endif      /* SA_PUB_H */
