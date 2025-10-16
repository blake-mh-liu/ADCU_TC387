/*********************************************************************************/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                  SA layer                                     */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

#ifndef SA_CBK_H
#define SA_CBK_H

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Csm.h"
[!ENDIF!]
 
[!IF "(as:modconf('SA')/General/Security_Algorithm_Type = 'Standard')"!]
/* Include header file that contains the standard algorithm function*/
#include "PROG_SecurityAlgorithm.h"
[!ENDIF!]

[!IF "((node:exists(General/SignatureVerify/Allow2CustomCsmStartPreprocess)) and (node:value(General/SignatureVerify/Allow2CustomCsmStartPreprocess) = 'true'))"!]
extern Csm_ReturnType SA_CustomCsmStrtPreproc(const u8** ubKeyPtr, u32 ulCsmJobId);
[!ENDIF!]
/*--------------------------------{SA_CustomCalculateKey}------------------------*/
extern void SA_CustomCalculateKey(u8 * aubSeed, u8 * aubCalculatedKey);

/*--------------------------------{SA_CustomGetRandomSeed}------------------------*/
extern void SA_CustomGetRandomSeed(u8 * aubSeed);

/*--------------------------------{SA_CustomStoreAsRetryCnt}---------------------*/
extern void SA_CustomStoreAsRetryCnt(u8 RetryCntValue);

/*--------------------------------{SA_CustomRestoreAsRetryCnt}-------------------*/
extern u8 SA_CustomRestoreAsRetryCnt(void);

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
/*--------------------------------{SA_CustomGetLastRandomNumber}-------------------*/
extern void SA_CustomGetLastRandomNumber(u8* aubDataRandomNumber);

/*--------------------------------{SA_CustomStoreRandomNumber}-------------------*/
extern void SA_CustomStoreRandomNumber(u8* pubDataRandomNumber);

extern void SA_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent);

[!ENDIF!]

[!IF "( (node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001'))"!]
 [!IF "not(node:exists(as:modconf('CryIf')))"!]
extern void SA_CustomGetMACKey(Csm_SymKeyType const ** pubKeyptr, u8 ubCsmCfdID);
extern void SA_CustomGetAESCTRKey(Csm_SymKeyType const ** pubKeyptr, u8 ubCsmCfdID);
[!ELSE!]
[!IF "((node:exists(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Encryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Decryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACVerification_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true')) "!]
extern void SA_CustomGetMACKey(Csm_SymKeyType const ** pubKeyptr, u8 ubCsmCfdID);
extern void SA_CustomGetAESCTRKey(Csm_SymKeyType const ** pubKeyptr, u8 ubCsmCfdID);
[!ENDIF!]
[!ENDIF!]
[!ENDIF!]


[!IF "(node:exists(as:modconf('ProgFord'))
      and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'))
      and (as:modconf('SA')/General/Compare_Key_Type = 'Custom')
      and (as:modconf('SA')/General/Custom_OEM_callback_for_Comparekey = 'true')"!]
extern Std_ReturnType SAS_CompareKeyLevel01(const uint8* ReceivedKey, const uint8* Seed, Dcm_NegativeResponseType* ErrorCode);
[!ENDIF!]

#endif      /* SA_CBK_H */
