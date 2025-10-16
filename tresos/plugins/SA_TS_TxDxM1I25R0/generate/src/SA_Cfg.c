/*********************************************************************************/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cfg.c                        */
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



/******************************** FILE INCLUSION *********************************/
/*                                                                               */
#include "EB_Prj.h"
[!AUTOSPACING!]

[!IF "not((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001'))"!]
[!IF "node:exists(as:modconf('ProgJLR')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord'))"!]
const u8 m_aubStaticKey[SA_STATIC_KEY_LEN] = {[!"num:inttohex(General/Static_Key_0)"!]U, [!"num:inttohex(General/Static_Key_1)"!]U, [!"num:inttohex(General/Static_Key_2)"!]U, [!"num:inttohex(General/Static_Key_3)"!]U, [!"num:inttohex(General/Static_Key_4)"!]U};
[!ENDIF!]
 [!ENDIF!]
 
 [!IF "node:exists(as:modconf('CryIf'))"!]
/* SA-Csm Job configurations*/
  [!VAR "SACsmJobIndex" = "0"!]
  [!VAR "CsmRandomGenerateJobIndex" = "255"!]
  [!VAR "CsmRandomSeedJobIndex" = "255"!]
  [!VAR "CsmSignatureJobIndex" = "255"!]
  [!VAR "CsmMACVerification_MsgAuthJobIndex" = "255"!]
  [!VAR "CsmMACGenerate_MsgAuthJobIndex" = "255"!]
  [!VAR "CsmAES_EncryptionJobIndex" = "255"!]
  [!VAR "CsmAES_DecryptionJobIndex" = "255"!]
  [!VAR "CsmMACVerification_PooJobIndex" = "255"!]
  [!VAR "CsmMACGenerate_PooJobIndex" = "255"!]


[!IF "(node:exists(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId))"!]
   [!VAR "CsmRandomGenerateJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
   [!VAR "SACsmJobIndex"= "$SACsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId))"!]
    [!VAR "CsmRandomSeedJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
    [!VAR "SACsmJobIndex" = "$SACsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId))"!]
    [!VAR "CsmSignatureJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
    [!VAR "SACsmJobIndex" = "$SACsmJobIndex + 1"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId))"!]
    [!VAR "CsmMACVerification_MsgAuthJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId))"!]
    [!VAR "CsmMACGenerate_MsgAuthJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId))"!]
    [!VAR "CsmAES_EncryptionJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId))"!]
    [!VAR "CsmAES_DecryptionJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId))"!]
    [!VAR "CsmMACVerification_PooJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId))"!]
    [!VAR "CsmMACGenerate_PooJobIndex" = "num:dectoint(number($SACsmJobIndex))"!]
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
[!ENDIF!]
[!IF "number($SACsmJobIndex) > 0"!]
const tSACsmJobConf m_astSACsmJobConf[SA_CSM_NUMCONF_JOBS] =
{
[!IF "number($CsmRandomGenerateJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId))"!]),
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!]PROG_FALSE,
[!WS "8"!]PROG_FALSE,
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmRandomSeedJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId))"!]),
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmRandomSeed/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmSignatureJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId))"!]),
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!]0U,
[!WS "8"!]PROG_FALSE,
[!WS "8"!]PROG_FALSE,
[!WS "8"!][!IF "(as:modconf('SA')/General/SignatureVerify/Allow2CustomCsmStartPreprocess) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmMACVerification_MsgAuthJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CSM_MACVERIFY_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACVERIFY_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACVERIFY_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmMACGenerate_MsgAuthJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CSM_MACGEN_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACGEN_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACGEN_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmAES_EncryptionJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true'"!]SA_CSM_AESENCRYPT_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_AESENCRYPT_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_AESENCRYPT_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmAES_DecryptionJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true'"!]SA_CSM_AESDECRYPT_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_AESDECRYPT_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_AESDECRYPT_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmMACVerification_PooJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CSM_MACVERIFYPOO_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACVERIFYPOO_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACVERIFYPOO_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2Cancel_OngoingJobs) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]},
[!ENDIF!]
[!IF "number($CsmMACGenerate_PooJobIndex) != 255"!]
[!WS "4"!]{
[!WS "8"!]SA_CSM_INDEX([!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId))"!]),
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CSM_MACGENPOO_KEYID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACGENPOO_KEYELEID[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true'"!]SA_CRYPTO_MACGENPOO_KEYSIZE[!WS "18"!][!ELSE!]0U[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "8"!][!IF "(as:modconf('SA')/General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true'"!]PROG_TRUE[!WS "18"!][!ELSE!]PROG_FALSE[!WS "17"!][!ENDIF!],
[!WS "8"!]PROG_FALSE,
[!WS "4"!]}
[!ENDIF!]
};
[!ENDIF!]
[!ENDIF!]
