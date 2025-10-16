#ifndef SA_PRIV_H
#define SA_PRIV_H

/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Priv.h                     */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
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
/* - Private Variables                                                            */
#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON))
extern u8 m_aubSeedForSASApi[SA_RANDOM_NUMBER_LENGTH];
#endif /* ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API == STD_ON)) */

#if (SA_USE_CRYPTO == STD_ON)
#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)
extern u32 m_ulSA2waitTime;
#endif /*#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)*/
#endif /*(SA_USE_CRYPTO == STD_ON)*/

#if (SA_CSMASR43_USED == STD_ON)
extern uint32 m_aubCurrentRandomNumberlen;
#endif /*SA_CSMASR43_USED*/

#if ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) || ((SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_CUSTOM) && (SA_COMPAREKEY_OEMCUSTOM_API != STD_ON)))
extern u8 m_aubCalculatedKey[SA_KEY_LEN];
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)*/

#if (SA_ANTISCANNING_ENABLED == STD_ON)
extern tAntiscanInfo m_stAntiscanInfo;
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/

#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && (PROG_CAL_PRESENT == STD_OFF))
/* Decompression algorithm variable */
extern tDecompressStateType m_uDecompressState;
extern u16 m_uwWinPos;
extern u8 m_ubOutByte;
extern u16 m_uwMatchPos;
extern u8 m_ubMatchLen;
extern u8 m_ubBitCount;

/* decompression status */
extern tDecompressStateType m_uDecompStatus;

/* Input buffer variable */
extern u8* m_pubInDecompBuf;
extern PduLengthType m_ulInBufLength;
extern u16 m_uwDecompIdx;

/* Output buffer variables */
extern u8 m_aubOutDecompBuf[SA_DECOMP_OUT_BUF_SIZE];
extern u16 m_uwOutBufPosition;
extern u16 m_uwOutBufLength;
#endif

#if(SA_AUTHENTICATION_METHOD == SA_AUTHENTICATION_0001)

extern u8 m_ubAesBlockIndex;
extern u8 m_ubAESCTR_Blockcount;
extern u8 m_aubMacValue[SA_MACSIZE];
extern u8 m_aubAesCtrClientRndNum[SA_CLIENT_RNDNUM_SIZE];
extern u8 m_aubAesCtrServerRndNum[SA_SERVER_RNDNUM_SIZE];
extern tSA_AuthenticationState m_ulAuthentication0001State;
extern u8 m_aubIV_Aligned16[SA_AESCTR_IVLEN];
extern u8 m_aubSaAm0001BufAligned16[SA_AM0001_MAXBUF];

extern tSaStatus m_ubSaStatus;
extern Csm_ReturnType m_ubCsmStatus;
extern tSA_ConcatenatePar m_aubConcatenatedataptr[2U];
#endif
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */


#if (SA_USE_CRYPTO == STD_ON)
/** \brief API called by SA_Init to initialize the cryptographic management for SecurityAccess
 **
 **/
extern void SA_InitCrypto(void);

/** \brief API called by SA_GetSeed to initialize  generation of the random value used in the Seed calculation
 **
 ** \param[in] aubRandomNumber
 **
 ** \return
 ** \retval SA_E_OK
 ** \retval SA_E_NOT_OK
 ** \retval SA_E_NOK_INVALID_KEY
 ** \retval SA_E_NOK_AS_LOCKED
 ** \retval SA_FALSE
 ** \retval SA_TRUE
 **/
extern tSaStatus SA_GenerateRandomNumber(u8* aubRandomNumber);

/** \brief API called by CSM module for the generation of the random value used in the Seed calculation
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern void SA_GenerateRandomCallback(Csm_ReturnType eCsmResult);

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
/** \brief API called by CSM module for the hash computation and the signature verification
 **
 ** \param[in] eCsmResult Csm signature verification or hash treatment result
 **
 **/
extern void SA_SignatureVerifAndHashCallback(Csm_ReturnType eCsmResult);
/** \brief API that is called by SA_GenerateRandomCallback to start the verification of a signature
 **
 ** \param[in] pstPublicKeyProgFormat Public key pointer
 **
 **/
extern void SA_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey);


/** \brief API called by SA_CompareKey to update the verification of a signature
 **
 ** \param[in] pubSignature Received signature to verify
 **
 **/
extern void SA_VerifySignatureUpdate(const u8* pubSignature);

extern void SA_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey);
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
#endif /*(SA_USE_CRYPTO == STD_ON)*/

/** \brief API used to block the security access requests after a number of unlock failures
 **
 ** \param[in] ubKeyMatch Key match boolean (true if match false if not)
 **
 **/
extern tSaStatus SA_Antiscanning(u8 ubKeyMatch);
#if(SA_CSM_CANCELJOB_ENABLED == STD_ON)
/** \brief API used to block the security access requests after a number of unlock failures
 **
 ** \param[in] ubKeyMatch Key match boolean (true if match false if not)
 **
 **/
extern Csm_ReturnType SA_CsmCancelActiveJobs(void);
#endif
#if(SA_CSM_SETKEY_ENABLED == STD_ON)
/** \brief API used to block the security access requests after a number of unlock failures
 **
 ** \param[in] ubKeyMatch Key match boolean (true if match false if not)
 **
 **/
extern Csm_ReturnType SA_CsmSetKeys(Csm_SymKeyType const * ubKeyPtr, u8 ubSACsmJobTabId);
#endif
#if (SA_CSM_AESCTR_ENCRYPTION_USED == STD_ON)
/** \brief API called by CSM module for the Encryption of the data using AES-CTR Algo
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern void SA_CsmAESEncryptCallback(Csm_ReturnType eCsmResult);
#endif

#if (SA_CSM_AESCTR_DECRYPTION_USED == STD_ON)
/** \brief API called by CSM module for the Decryption of the AES-CTR encrypted Algo
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern void SA_CsmAESDecryptCallback(Csm_ReturnType eCsmResult);
#endif

#if (SA_CSMASR43_USED == STD_ON)
/** \brief API is a unique callback called by CSM module to treat random generation, encryption, decryption, hash and signature verification
 **
 ** \param[in] job        Job ID of CSM
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern FUNC(void, CSM_APPL_CODE)SA_CsmNotification(P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result);
#endif

#if (SA_CSM_MAC_GENERATION_USED == STD_ON)
/** \brief API called by CSM module for the MAC Generation
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern void SA_CsmMacGenerateCallback(Csm_ReturnType eCsmResult);
#endif

#if (SA_CSM_MAC_VERIFICATION_USED == STD_ON)
/** \brief API called by CSM module for the MAC Verification
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern void SA_CsmMacVerifyCallback(Csm_ReturnType eCsmResult);
#endif
/*                                                                               */
/*-------------------------------------------------------------------------------*/


#endif      /* SA_PRIV_H */
