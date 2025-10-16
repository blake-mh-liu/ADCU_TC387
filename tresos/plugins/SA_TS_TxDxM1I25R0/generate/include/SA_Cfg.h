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
/*%%   _____________________________   %%  \file SA_Cfg.h                        */
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
[!AUTOSPACING!]
#ifndef SA_CFG_H
#define SA_CFG_H

 [!IF "node:exists(as:modconf('CryIf'))"!]

 /* SA table Index of the jobs configured */
 [!VAR "SACsmJobIndex" = "0"!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId))"!]
 [!WS "0"!]#define SA_CSMRANDOMGENERATEJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId))"!]
 [!WS "0"!]#define SA_CSMRANDOMSEEDJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId))"!]
 [!WS "0"!]#define SA_CSMSIGNATUREJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId))"!]
 [!WS "0"!]#define SA_CSMMACVERIFMSGAUTHJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_MACVERIFY_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_MACVERIFY_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_MACVERIFY_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId))"!]
 [!WS "0"!]#define SA_CSMMACGENMSGAUTHJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_MACGEN_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_MACGEN_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_MACGEN_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId))"!]
 [!WS "0"!]#define SA_CSMAESENCRYPTJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_AESENCRYPT_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_AESENCRYPT_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_AESENCRYPT_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId))"!]
 [!WS "0"!]#define SA_CSMAESDECRYPTJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_AESDECRYPT_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_AESDECRYPT_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_AESDECRYPT_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]
 
 [!IF "(node:exists(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId))"!]
 [!WS "0"!]#define SA_CSMMACVERIFPOOJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_MACVERIFYPOO_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_MACVERIFYPOO_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_MACVERIFYPOO_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]

 [!IF "(node:exists(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId))"!]
 [!WS "0"!]#define SA_CSMMACGENPOOJOBINDEX                    [!"num:dectoint(number($SACsmJobIndex))"!]U
 [!WS "0"!]#define SA_CSMTABID_[!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId))"!][!WS "15"!][!"num:dectoint(number($SACsmJobIndex))"!]U
 [!VAR "SACsmJobIndex"= "num:dectoint(number($SACsmJobIndex + 1))"!]
  [!IF "(as:modconf('SA')/General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true'"!]
     [!//The position of the key element in the crypto driver shall be fixed(default index) and shall be double-checked by the integrator, especially when using more than 1 key element ID for a single key type!]
     [!VAR "KEYELEPOSNUM"="1"!]
/*Signature Verification Key Parameters*/
#define SA_CSM_MACGENPOO_KEYID[!WS "18"!][!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_MACGENPOO_KEYELEID [!WS "12"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
#define SA_CRYPTO_MACGENPOO_KEYSIZE  [!WS "13"!][!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementSize)"!]U
   [!ENDIF!]
 [!ENDIF!]

 [!WS "0"!]#define SA_CSM_NUMCONF_JOBS                   [!"num:dectoint($SACsmJobIndex)"!]U

[!IF "number($SACsmJobIndex) > 0"!]
 #define SA_CSMASR43_USED                 STD_ON
 #define SA_Csm_MainFunction                 Crypto_MainFunction
 #define SA_CSM_INDEX(job_name)              SA_CSMTABID_##job_name
 #define SA_CSM_ALLJOBS_COUNT             [!"num:i(count(as:modconf('Csm')/CsmJobs/CsmJob/*))"!]U
[!ELSE!]
#define SA_CSMASR43_USED                 STD_OFF
#define SA_Csm_MainFunction              Csm_MainFunction
[!ENDIF!]
 [!ELSE!]
 #define SA_CSMASR43_USED                 STD_OFF
 #define SA_Csm_MainFunction              Csm_MainFunction
 #define SA_CSM_INDEX(job_name)                job_name
 [!ENDIF!]
 
[!IF "((node:exists(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Encryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Decryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACVerification_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true')) "!]
#define SA_CSM_SETKEY_ENABLED             STD_ON
[!ELSE!]
#define SA_CSM_SETKEY_ENABLED             STD_OFF
[!ENDIF!]

 [!IF "((node:exists(General/CsmRandomSeed/Allow2Cancel_OngoingJobs)) and (node:value(General/CsmRandomSeed/Allow2Cancel_OngoingJobs) = 'true')) or
 ((node:exists(General/CsmMACVerification_Poo/Allow2Cancel_OngoingJobs)) and (node:value(General/CsmMACVerification_Poo/Allow2Cancel_OngoingJobs) = 'true')) or
 ((node:exists(General/CsmMACVerification_MsgAuth/Allow2Cancel_OngoingJobs)) and (node:value(General/CsmMACVerification_MsgAuth/Allow2Cancel_OngoingJobs) = 'true'))"!]
#define SA_CSM_CANCELJOB_ENABLED             STD_ON
  [!ELSE!]
#define SA_CSM_CANCELJOB_ENABLED             STD_OFF
[!ENDIF!]

 [!IF "((node:exists(General/CsmAES_Encryption/AllowECB2CTR)) and (node:value(General/CsmAES_Encryption/AllowECB2CTR) = 'true')) or
 ((node:exists(General/CsmAES_Decryption/AllowECB2CTR)) and (node:value(General/CsmAES_Decryption/AllowECB2CTR) = 'true'))"!]
#define SA_ECB2CTR_ENABLED             STD_ON
  [!ELSE!]
#define SA_ECB2CTR_ENABLED             STD_OFF
[!ENDIF!]

[!IF "((node:exists(General/SignatureVerify/Allow2CustomCsmStartPreprocess)) and (node:value(General/SignatureVerify/Allow2CustomCsmStartPreprocess) = 'true'))"!]
#define SA_CUSTOM_CSMSTARTPREPROCESS_ENABLED             STD_ON
[!ELSE!]
#define SA_CUSTOM_CSMSTARTPREPROCESS_ENABLED             STD_OFF
[!ENDIF!]

/* Timer period in milliseconds for the SA periodic task */
/* The minimum value accepted for SA_MANAGE_PERIOD is 1 */
/* Range : (1 .. 100) */
#define SA_MANAGE_PERIOD                [!"num:i(General/MANAGE_PERIOD)"!]U


#define SA_SECURITY_ALOGORITHM_STANDARD    0X00U
#define SA_SECURITY_ALOGORITHM_CUSTOM      0X01U
#define SA_SECURITY_ALOGORITHM_UNDEFINED   0XFFU
#define SA_COMPRESSION_ENABLED            0x01U
#define SA_COMPRESSION_DISABLED           0x02U
[!IF "node:exists(as:modconf('Prog')) and (as:modconf('Prog')/General/Enable_Compression = 'true')"!]
#define SA_COMPRESSION_STATE              SA_COMPRESSION_ENABLED
[!ELSE!]
#define SA_COMPRESSION_STATE              SA_COMPRESSION_DISABLED
[!ENDIF!]


#define SA_CHALLENGE_BIT 64U /* Size of PROG_SA_CHALLENGE_BYTE in bit, 8*8 = 64 */

#define SA_SEED_STANDARD    0x00U
#define SA_SEED_CSM_RANDOM  0x01U
[!IF "((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001'))"!]
#define SA1_MSGREQ_SIZE                   54U
#define SA1_MSGRES_SIZE                   68U
#define SA2_MSGREQ_SIZE                   52U
#define SA2_MSGRES_SIZE                   2U
#define SA_SEED_LEN_AM0001                (SA1_MSGRES_SIZE - 2U)
#define SA_KEY_LEN_AM0001                 (SA2_MSGREQ_SIZE - 2U)
#define SA_SEED_LEN                       SA_SEED_LEN_AM0001
#define SA_KEY_LEN                        SA_KEY_LEN_AM0001
#define SA_RANDOM_NUMBER_LENGTH           16U
 [!ELSE!]
#define SA_SEED_LEN   ([!"num:dectoint(General/Security_Access_Seed_Length)"!]U)
#define SA_KEY_LEN   ([!"num:dectoint(General/Security_Access_Key_Length)"!]U)
#define SA_STATIC_KEY_LEN 5U     /* size of the static key */
#define SA_RANDOM_NUMBER_LENGTH           SA_SEED_LEN
  [!ENDIF!]

#define SA_SEED_TYPE                       [!WS "20"!][!IF "as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random'"!] SA_SEED_CSM_RANDOM[!ELSE!]SA_SEED_STANDARD[!ENDIF!]

[!IF "as:modconf('SA')/General/Seed_Type = 'Standard'"!]
 
#define SA_SECURITY_ALOGORITHM_TYPE       [!WS "20"!][!IF "as:modconf('SA')/General/Security_Algorithm_Type = 'Standard'"!]SA_SECURITY_ALOGORITHM_STANDARD[!ELSE!]SA_SECURITY_ALOGORITHM_CUSTOM[!ENDIF!]
[!ENDIF!]

#define SA_COMPARE_KEY_STANDARD         0x00U
#define SA_COMPARE_KEY_VERIFY_SIGNATURE 0x01U
#define SA_COMPARE_KEY_AM0001           0x02U
#define SA_COMPARE_KEY_CUSTOM           0x03U

#define SA_COMPARE_KEY_TYPE               [!WS "20"!] [!IF "General/Compare_Key_Type = 'Verify_Signature'"!]SA_COMPARE_KEY_VERIFY_SIGNATURE
                                           [!ELSEIF "General/Compare_Key_Type = 'SA_AM_0001'"!]SA_COMPARE_KEY_AM0001
                                           [!ELSEIF "General/Compare_Key_Type = 'Custom'"!]SA_COMPARE_KEY_CUSTOM
                                           [!ELSE!]SA_COMPARE_KEY_STANDARD[!ENDIF!]


[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#define SA_USE_CRYPTO                  STD_ON

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random')"!]
[!IF "(node:exists(as:modconf('CryIf')))"!] 
#define SA_CSM_RANDOM_GENERATE_ID       [!"(as:ref(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId)/CsmJobId)"!]
#define SA_CSM_RANDOM_SEED_ID           [!"(as:ref(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId)/CsmJobId)"!]
#define SA_CSM_RANDOM_SEED_KEYID        [!"node:value(as:ref(as:ref(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
[!ELSE!]
#define SA_CSM_RANDOM_GENERATE_ID       [!"name(as:ref(as:modconf('SA')/General/CsmRandomGenerate/CsmRandomGenerateConfigId))"!]
#define SA_CSM_RANDOM_SEED_ID           [!"name(as:ref(as:modconf('SA')/General/CsmRandomSeed/CsmRandomSeedConfigId))"!]
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgJLR')) and (as:modconf('SA')/General/Compare_Key_Type != 'Verify_Signature')"!]
#define SA_SECURITY_ALOGORITHM_TYPE       [!WS "20"!][!IF "as:modconf('SA')/General/Security_Algorithm_Type = 'Standard'"!]SA_SECURITY_ALOGORITHM_STANDARD[!ELSE!]SA_SECURITY_ALOGORITHM_CUSTOM[!ENDIF!]
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature'"!]
[!IF "(node:exists(as:modconf('CryIf')))"!] 
[!VAR "KEYELEPOSNUM"="1"!]
#define SA_CSM_SIG_VERIFY_ID           [!"(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId)/CsmJobId)"!]
#define SA_CSM_SIG_VERIFY_KEYID        [!"node:value(as:ref(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId)/CsmJobKeyRef)/CsmKeyId)"!]U
#define SA_CRYPTO_SIGN_KEYELEID        [!"(as:ref(as:ref(as:ref(as:ref(as:ref(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId)/CsmJobKeyRef)/CsmKeyRef)/CryIfKeyRef)/CryptoKeyTypeRef)/CryptoKeyElementRef/*[number($KEYELEPOSNUM)])/CryptoKeyElementId)"!]U
[!ELSE!]
#define SA_CSM_SIG_VERIFY_ID           [!"name(as:ref(as:modconf('SA')/General/SignatureVerify/CsmSignatureVerifyConfigId))"!]
[!ENDIF!]
#define SA_SIGNATURE_LENGTH             SA_KEY_LEN
[!IF "node:exists(as:modconf('ProgDAG'))"!]
#define SA_PUBLIC_KEY_LENGTH            32U
#define SA_CRY_EXPONENT_ENABLED       STD_OFF
[!ELSEIF "node:exists(as:modconf('ProgFCA'))"!]
#define SA_PUBLIC_KEY_LENGTH            256U
#define SA_CRY_EXPONENT_ENABLED       STD_ON
[!ENDIF!]
[!ENDIF!]

[!ELSE!]
#define SA_USE_CRYPTO                   STD_OFF
[!ENDIF!]

[!IF "General/Security_Access_Rs_Delay_Timer != '0'"!]
#define SA_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_ON
/* Request Seed delay Timer Load value */
#define  SA_RS_DELAY_TIMER                   [!"num:i(General/Security_Access_Rs_Delay_Timer div General/MANAGE_PERIOD)"!]U
[!ELSE!]
#define SA_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_OFF
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define SA_ANTISCANNING_ENABLED            STD_ON
/* Anti-scanning Timer Load value */
#define  SA_AS_LOCK_TIMER                  [!"num:i(General/Security_Access_As_Timer div General/MANAGE_PERIOD)"!]U
/* Anti-scanning Retry Counter value */
#define SA_AS_MAX_NB_RETRY                 [!"num:i(General/Security_Access_As_Retry_Counter)"!]U
[!ELSE!]
#define SA_ANTISCANNING_ENABLED            STD_OFF
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define SA_LIMIT_NB_REQUEST_SEED_ENABLED           STD_ON
/* Anti-scanning Timer Load value */
#define  SA_RS_LIMIT_TIMER                 [!"num:i(General/Security_Access_RS_Timer div General/MANAGE_PERIOD)"!]U
/* Anti-scanning Retry Counter value */
#define SA_RS_LIMIT_COUNTER                 [!"num:i(General/Security_Access_RS_Retry_Counter)"!]U
[!ELSE!]
#define SA_LIMIT_NB_REQUEST_SEED_ENABLED            STD_OFF
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Static_Seed = 'true')"!]
#define SA_STATIC_SEED_ENABLED            STD_ON
[!ELSE!]
#define SA_STATIC_SEED_ENABLED            STD_OFF
[!ENDIF!]

#define SA_AUTHENTICATION_0001 0x0001U
#define SA_AUTHENTICATION_OFF  0xFFFFU
[!IF "((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001'))"!]
#define SA_AUTHENTICATION_METHOD SA_AUTHENTICATION_0001

#define SA1_MSGID              0x0001U
#define SA1_RESPONSE_MSGID     0x0002U
#define SA2_MSGID              0x0003U
#define SA_MACSIZE             16U
#define SA_MSGAUTHCODE_MACSIZE 16U

#define SA1_MSGSIZE_WITHOUT_MACVALUE (SA1_MSGREQ_SIZE - SA_MSGAUTHCODE_MACSIZE)
#define SA2_MSGSIZE_WITHOUT_MACVALUE (SA2_MSGREQ_SIZE - SA_MSGAUTHCODE_MACSIZE)
#define SA1_RESSIZE_WITHOUT_MACVALUE (SA1_MSGRES_SIZE - SA_MSGAUTHCODE_MACSIZE)

#define SA_CLIENT_RNDNUM_SIZE    16U
#define SA1_AESCTR_IVOFFSET       6U
#define SA1_AESCTR_CTOFFSET_REQ  22U
#define SA1_AESCTR_CTOFFSET_RES  20U
#define SA_CLIENT_POO_SIZE       16U
#define SA2_AESCTR_PTLEN         16U
#define SA1_AESCTR_IVOFFSET_RES   4U
#define SA2_AESCTR_IVOFFSET       4U
#define SA2_AESCTR_CTOFFSET      20U
#define SA_AESCTR_IVLEN          16U
#define SA_AESCTR_BLOCKSIZE      16U

#define SA2_MAX_AWAIT_TIME       [!"num:i(num:i(General/SA2_Awaiting_MaxTime) * num:i(General/MANAGE_PERIOD))"!]U
#define SA_SERVER_RNDNUM_SIZE    16U
#define SA1_ENCRYPTION_DATALEN   32U
#define SA_AM0001_MAXBUF         64U
#define SA_UDS_ACK               0x40U
/* States of SA Authetication Method 0001, order of successive state transition is from
 * the top to the bottom in the below list */
#define SA_AM0001_IDLE                       0x00000000U
#define SA_VRFYMSG_AUTHCODE_SA1              0x00000001U
#define SA_DECRYPT_REQDATA_SA1               0x00000002U
#define SA_SEEDGEN_RNDIV                     0x00000004U
#define SA_SEEDGEN_RNDSERVER                 0x00000008U
#define SA_SEEDGEN_SERVERPOO                 0x00000010U
#define SA_SEEDGEN_SERVERPOO_SUCCESS         0x00000020U
#define SA_SEEDGEN_SERVERPOO_ENCRYPT         0x00000020U
#define SA_SEEDGEN_SERVERPOO_ENCRYBLK2       0x40000020U
#define SA_SEEDGEN_MSGAUTHCODE               0x00000040U
#define SA_SEEDGEN_MSGAUTHCODE_SUCCESS       0x00000080U
#define SA_SEND_SA1RES                       0x00000080U
#define SA_SEND_SA1RES_AWAIT_TXCONF          0x40000100U
#define SA_AWAIT_SA2REQ                      0x00000100U
#define SA_AWAIT_SA2REQ_BUSY                 0x40000200U
#define SA_VRFYMSG_AUTHCODE_SA2              0x00000200U
#define SA_DECRYPT_REQDATA_SA2               0x00000400U
#define SA_KEYUNLOCK                         0x00000800U
#define SA_KEYUNLOCK_SUCCESS                 0x00001000U

/* Failure states of SA Authetication Method 0001 corresponding to the above states,
 * MSB bit of any state indicate failure in that particular state*/
#define SA_VRFYMSG_AUTHCODE_SA1_FAILED       0x80000002U
#define SA_DECRYPT_REQDATA_SA1_FAILED        0x80000004U
#define SA_SEEDGEN_RNDIV_FAILED              0x80000008U
#define SA_SEEDGEN_RNDSERVER_FAILED          0x80000010U
#define SA_SEEDGEN_SERVERPOO_FAILED          0x80000020U
#define SA_SEEDGEN_SERVERPOO_ENCRYPT_FAILED  0x80000040U
#define SA_SEEDGEN_MSGAUTHCODE_FAILED        0x80000080U
#define SA_SEND_SA1RES_FAILED                0x80000100U
#define SA_AWAITSA2_TIMEEXPIRED              0x80000200U
#define SA_VRFYMSG_AUTHCODE_SA2_FAILED       0x80000400U
#define SA_DECRYPT_REQDATA_SA2_FAILED        0x80000800U
#define SA_KEYUNLOCK_FAILED                  0x80001000U

/*Bit Position to indicate Busy and Failure in the active State Respectively*/
#define SA_AM0001_STATE_BUSY                 0x40000000U
#define SA_AM0001_STATE_FAILED               0x80000000U

/*SA-Crypto Operation states*/
#define SA_MAC_VERIFY_FINISH                 0x10U
#define SA_MAC_VERIFY_UPDATE                 0x11U
#define SA_MAC_VERIFY_START                  0x12U
#define SA_CSM_MAC_VERIFICATION_USED         STD_ON
#define SA_MAC_GENERATE_FINISH               0x13U
#define SA_MAC_GENERATE_UPDATE               0x14U
#define SA_MAC_GENERATE_START                0x15U
#define SA_CSM_MAC_GENERATION_USED           STD_ON
#define SA_AES_DECRYPT_FINISH                0x16U
#define SA_AES_DECRYPT_UPDATE                0x17U
#define SA_AES_DECRYPT_START                 0x18U
#define SA_CSM_AESCTR_DECRYPTION_USED        STD_ON
#define SA_AES_ENCRYPT_FINISH                0x19U
#define SA_AES_ENCRYPT_UPDATE                0x1AU
#define SA_AES_ENCRYPT_START                 0x1BU
#define SA_CSM_AESCTR_ENCRYPTION_USED        STD_ON

/* Indicate that the waiting time for SA2 request has Expired */
#define SA_E_WAITING_SA2_NOT_OK              SA_E_NOT_OK
[!IF "(node:exists(as:modconf('CryIf')))"!] 
#define SA_CSM_MAC_MSGCODEVERIFY_ID          [!"(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId)/CsmJobId)"!]
#define SA_CSM_AESCTR_DECRYPT_ID             [!"(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId)/CsmJobId)"!]
#define SA_CSM_MAC_POOGEN_ID                 [!"(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId)/CsmJobId)"!]
#define SA_CSM_AESCTR_ENCRYPT_ID             [!"(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId)/CsmJobId)"!]
#define SA_CSM_MAC_MSGCODEGEN_ID             [!"(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId)/CsmJobId)"!]
#define SA_CSM_MAC_POOVRFY_ID                [!"(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId)/CsmJobId)"!]
[!ELSE!]
#define SA_CSM_MAC_MSGCODEVERIFY_ID          [!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_MsgAuth/CsmMACVerification_MsgAuthConfigId))"!]
#define SA_CSM_AESCTR_DECRYPT_ID             [!"name(as:ref(as:modconf('SA')/General/CsmAES_Decryption/CsmAES_DecryptionConfigId))"!]
#define SA_CSM_MAC_POOGEN_ID                 [!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_Poo/CsmMACGenerate_PooConfigId))"!]
#define SA_CSM_AESCTR_ENCRYPT_ID             [!"name(as:ref(as:modconf('SA')/General/CsmAES_Encryption/CsmAES_EncryptionConfigId))"!]
#define SA_CSM_MAC_MSGCODEGEN_ID             [!"name(as:ref(as:modconf('SA')/General/CsmMACGenerate_MsgAuth/CsmMACGenerate_MsgAuthConfigId))"!]
#define SA_CSM_MAC_POOVRFY_ID                [!"name(as:ref(as:modconf('SA')/General/CsmMACVerification_Poo/CsmMACVerification_PooConfigId))"!]
[!ENDIF!]
[!VAR "DID_PRESENT" = "0"!]
[!IF "not(node:exists(as:modconf('CryIf')))"!] 
#ifndef SA_CUSTOMGETMACKEY
#define SA_CUSTOMGETMACKEY STD_ON
#endif

#ifndef SA_CUSTOMGETAESCTRKEY
#define SA_CUSTOMGETAESCTRKEY STD_ON
#endif

#ifndef SA_SECUREDKEYS_STATUSREAD
#define SA_SECUREDKEYS_STATUSREAD STD_OFF
#endif
[!ELSE!]
[!IF "((node:exists(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_MsgAuth/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Encryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Encryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmAES_Decryption/Allow2SetCryptoKey)) and (node:value(General/CsmAES_Decryption/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACVerification_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACVerification_Poo/Allow2SetCryptoKey) = 'true')) or
((node:exists(General/CsmMACGenerate_Poo/Allow2SetCryptoKey)) and (node:value(General/CsmMACGenerate_Poo/Allow2SetCryptoKey) = 'true')) "!]
#ifndef SA_CUSTOMGETMACKEY
#define SA_CUSTOMGETMACKEY STD_ON
#endif

#ifndef SA_CUSTOMGETAESCTRKEY
#define SA_CUSTOMGETAESCTRKEY STD_ON
#endif
[!ELSE!]
#ifndef SA_CUSTOMGETMACKEY
#define SA_CUSTOMGETMACKEY STD_OFF
#endif

#ifndef SA_CUSTOMGETAESCTRKEY
#define SA_CUSTOMGETAESCTRKEY STD_OFF
#endif
[!ENDIF!]
[!VAR "DID_PRESENT" = "0"!]
[!IF "(node:exists(as:modconf('Uds')))"!]
[!/* Check if any service DID is configured with PROG_ReadKeyProgrammedStatus callback */!]
[!LOOP "as:modconf('Uds')/Service_DID/*"!]
    [!IF "(Callback = 'PROG_ReadKeyProgrammedStatus')"!]
        [!VAR "DID_PRESENT" = "1"!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]
#ifndef SA_SECUREDKEYS_STATUSREAD
[!IF "$DID_PRESENT = 1"!]
#define SA_SECUREDKEYS_STATUSREAD STD_ON
[!ELSE!]
#define SA_SECUREDKEYS_STATUSREAD STD_OFF
[!ENDIF!]
#endif
[!ENDIF!]
[!ELSE!]
#define SA_AUTHENTICATION_METHOD             SA_AUTHENTICATION_OFF
#define SA_CSM_AESCTR_ENCRYPTION_USED        STD_OFF
#define SA_CSM_AESCTR_DECRYPTION_USED        STD_OFF
#define SA_CSM_MAC_GENERATION_USED           STD_OFF
#define SA_CSM_MAC_VERIFICATION_USED         STD_OFF
[!IF "(node:exists(as:modconf('ProgJLR'))) or (node:exists(as:modconf('ProgVCC'))) or (node:exists(as:modconf('ProgFord')))"!]
extern const u8 m_aubStaticKey[SA_STATIC_KEY_LEN];
[!ENDIF!]
[!ENDIF!]

#ifndef SA_SECURITY_ALOGORITHM_TYPE
#define SA_SECURITY_ALOGORITHM_TYPE       SA_SECURITY_ALOGORITHM_UNDEFINED
#endif

[!IF "as:modconf('SA')/General/Compare_Key_Type = 'Custom'"!]
#define SA_COMPAREKEY_OEMCUSTOM_API       [!WS "20"!][!IF "General/Custom_OEM_callback_for_Comparekey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!ELSE!]
#define SA_COMPAREKEY_OEMCUSTOM_API       STD_OFF
[!ENDIF!]

#endif      /* SA_CFG_H */
