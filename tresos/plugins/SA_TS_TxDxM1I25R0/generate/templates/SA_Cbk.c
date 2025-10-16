/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               SA layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.c                        */
/*%%  |                             |  %%  \brief SA layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "board.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
/** \brief API that calculates the security access key
 **
 ** This callback is called on reception of SecurityAccess service to perfom
 ** computation of the security key based on a random seed.
 **
 ** \param[in] aubSeed Address of the seed array
 ** \param[out] aubCalculatedKey Address where the calculated key will be copied
 **/
void SA_CustomCalculateKey(u8 * aubSeed, u8 * aubCalculatedKey)
{
    OSC_PARAM_UNUSED(aubSeed);
    OSC_PARAM_UNUSED(aubCalculatedKey);
}

/** \brief Get the Random number for unlocking the security.
 **
 ** Callback is called: This callback is called on the reception of securityaccess service to generate the seed
 ** 
 ** Callback shall implement: customer specific generation algorithm
 **
 ** \param[out] aubSeed Address of the seed array
 **
 **/
void SA_CustomGetRandomSeed(u8 * aubSeed)
{
    OSC_PARAM_UNUSED(aubSeed);
}
#endif /*(SA_SEED_TYPE != SA_SEED_CSM_RANDOM)*/

[!IF "((node:exists(General/SignatureVerify/Allow2CustomCsmStartPreprocess)) and (node:value(General/SignatureVerify/Allow2CustomCsmStartPreprocess) = 'true'))"!]
/** \brief This Optional Callback used for the Custom Csm Implementation, called before the Csm Start mode of operation.
 **
 ** Callback is called: Before the start of Csm operation, after all successful job cancel operations(if cancellation is enabled)
 **
 ** Callback shall implement: the Custom operation such as Key DER encoding or set IV or just the notification about the start of the 
 ** crypto operation or any custom operation needed for the Integration.
 **
 ** \param[in,out] ubKeyPtr is the pointer to the address of the key buffer
 ** \param[in]     ulCsmJobId is the Csm Job ID for which the key pointer could be updated or read
 **
 ** \return state
 ** \retval E_OK Treatment finished successfully
 ** \retval E_NOT_OK Error happened during treatment
 **/
Csm_ReturnType SA_CustomCsmStrtPreproc(const u8** ubKeyPtr, u32 ulCsmJobId)
{
    OSC_PARAM_UNUSED(ubKeyPtr);
    OSC_PARAM_UNUSED(ulCsmJobId);
    return E_OK;
}
[!ENDIF!]

#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that stores the security access anti-scanning retry counter
 **
 ** This callback is called on reception of SecurityAccess service in case
 ** anti-scanning feature is activated. The counter value provided as parameter
 ** shall be stored in non-volatile memory.
 **
 ** \param[in] RetryCntValue Value of security access anti-scanning retry counter
 **/
void SA_CustomStoreAsRetryCnt(u8 RetryCntValue)
{
    OSC_PARAM_UNUSED(RetryCntValue);
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/


#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that restores the security access anti-scanning retry counter
 **
 ** This callback is called at Bootloader startup (if anti-scanning feature is
 ** activated) to get the retry counter value from non-volatile memory.
 **
 ** \return Value of security access anti-scanning retry counter
 **/
u8 SA_CustomRestoreAsRetryCnt(void)
{
    u8 RetAsRetryCnt = 0;
    /*Fetch from NVM*/
    return RetAsRetryCnt;
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
/** \brief Get the last random number stored
 **
 ** Called in SA_GenerateRandomCallback when Csm is in SA_SEED_GEN_STATE_START state
 **
 ** \param[out] aubDataRandomNumber Generated random number array
 **/
void SA_CustomGetLastRandomNumber(u8* aubDataRandomNumber)
{
    OSC_PARAM_UNUSED(aubDataRandomNumber);
}

/** \brief Store the generated random number
 **
 ** Called in SA_GenerateRandomCallback when Csm is in SA_RANDOM_GEN_STATE_GENERATE state
 **
 ** \param[in] pubDataRandomNumber Generated random number array
 **/
void SA_CustomStoreRandomNumber(u8* pubDataRandomNumber)
{
    OSC_PARAM_UNUSED(pubDataRandomNumber);
}


/*Public Key:EC172B93AD5E563BF4932C70E1245034C35467EF2EFD4D64EBF819683467E2BF*/

const u32 m_ulSAPublicExponent = 0UL;

const u8 m_aubSAPublicModulus[32] =
    {
        0xEC, 0x17, 0x2B, 0x93, 0xAD, 0x5E, 0x56, 0x3B,
        0xF4, 0x93, 0x2C, 0x70, 0xE1, 0x24, 0x50, 0x34,
        0xC3, 0x54, 0x67, 0xEF, 0x2E, 0xFD, 0x4D, 0x64,
        0xEB, 0xF8, 0x19, 0x68, 0x34, 0x67, 0xE2, 0xBF,
    };

/** \brief Get the public key when using asymmetric cryptography. Used in SA_InitCrypto
 **
 ** \param[out] paubPublicModulus Pointer to public key modulus array
 ** \param[out] pulPublicExponent Pointer to public key exponent
 **
 **/
/*---------------------------{PROG_CustomGetAsymPublicKey}-----------------------------*/
void SA_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent)
{
    *paubPublicModulus = m_aubSAPublicModulus;
    *pulPublicExponent = m_ulSAPublicExponent;
}
/*------------------------{end PROG_CustomGetAsymPublicKey}--------------------------*/

[!IF "((node:exists(as:modconf('ProgVCC'))) and ((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001')))"!]
 [!IF "not(node:exists(as:modconf('CryIf')))"!]
 const Csm_SymKeyType m_aubSaAesKeyData=
 {
     16U,
     {
         0xEBEBEBEBU,
         0xEBEBEBEBU,
         0xEBEBEBEBU,
         0xEBEBEBEBU
     }
 };
 /** \brief Get the AES key for AES Encryption and Decryption.
  **
  ** \param[out] paubKeyData Pointer to AES key modulus array
  ** \param[out] pubCsmCfgID for which the key shall be retrieved
  **
  **/
 void SA_CustomGetAESCTRKey(Csm_SymKeyType const ** paubKeyData, u8 pubCsmCfgID)
 {
     OSC_PARAM_UNUSED(pubCsmCfgID);
     OSC_PARAM_UNUSED(paubKeyData);
 }

 const Csm_SymKeyType m_aubSaMacKeyData=
 {
     16U,
      {
         0xBEBEBEBEU,
         0xBEBEBEBEU,
         0xBEBEBEBEU,
         0xBEBEBEBEU
      }
 };

 /** \brief Get the MAC key for MAC Verification and MAC Generation.
  **
  ** \param[out] paubKeyData Pointer to MAC key modulus array
  ** \param[out] pubCsmCfgID for which the key shall be retrieved
  **
  **/
 void SA_CustomGetMACKey(Csm_SymKeyType const** paubKeyData, u8 pubCsmCfgID)
 {
     OSC_PARAM_UNUSED(pubCsmCfgID);
     OSC_PARAM_UNUSED(paubKeyData);
 }
[!ELSE!]
[!IF "((node:exists(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Encryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Decryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACVerification_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true')) "!]
 /** \brief Get the AES key for AES Encryption and Decryption.
  **
  ** \param[out] paubKeyData Pointer to AES key modulus array
  ** \param[out] pubCsmCfgID for which the key shall be retrieved
  **
  **/
 void SA_CustomGetAESCTRKey(Csm_SymKeyType const** paubKeyData, u8 pubCsmCfgID)
 {
     OSC_PARAM_UNUSED(pubCsmCfgID);
     OSC_PARAM_UNUSED(paubKeyData);
 }

 /** \brief Get the MAC key for MAC Verification and MAC Generation.
  **
  ** \param[out] paubKeyData Pointer to MAC key modulus array
  ** \param[out] pubCsmCfgID for which the key shall be retrieved
  **
  **/
 void SA_CustomGetMACKey(Csm_SymKeyType const** paubKeyData, u8 pubCsmCfgID)
 {
     OSC_PARAM_UNUSED(pubCsmCfgID);
     OSC_PARAM_UNUSED(paubKeyData);
 }
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]




[!IF "(node:exists(as:modconf('ProgFord'))
      and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'))
      and (as:modconf('SA')/General/Compare_Key_Type = 'Custom')
      and (as:modconf('SA')/General/Custom_OEM_callback_for_Comparekey = 'true')"!]
/** \brief This function will compare the Received with the calculated Key and return the result.
 **
 ** Callback is called: upon the reception of the Key request. This callback is provided by Ford.
**  FORD wants to use their own function do both the key calculation and the comparison so 
**  Ford can delete the necessary secret information 
 ** as quickly as possible
 **
 **
 ** Callback shall implement: This call back should have the Ford specific key calculation and comparison
 ** with the received key. The result of the comparion is stored in ErroCode which is Output Parameter.
 **
 ** \param[IN] ReceivedKey Pointer to key received
 ** \param[IN] Pointer to generated Seed
 ** \param[out] ErrorCode result of the comparison
 **
 ** \return True/Fals based on key comparison.
 **/
Std_ReturnType SAS_CompareKeyLevel01(const uint8* ReceivedKey, const uint8* Seed, Dcm_NegativeResponseType* ErrorCode)
{
     OSC_PARAM_UNUSED(ReceivedKey);
     OSC_PARAM_UNUSED(Seed);
     OSC_PARAM_UNUSED(ErrorCode);
    return E_OK;
}
[!ENDIF!]
