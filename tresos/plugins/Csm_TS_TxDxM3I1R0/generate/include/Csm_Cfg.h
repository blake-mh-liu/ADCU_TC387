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
[!/* ====================================================================================== */!][!//
[!INCLUDE "Csm_Macros.m"!][!//
[!/* ====================================================================================== */!][!//
[!//

#ifndef CSM_CFG_H
#define CSM_CFG_H

/* !LINKSTO CSM.Dsn.SWS_Csm_00003,1 */

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

#include <Csm_Types.h>

/*==================[macros]======================================================================*/

/** \brief  Csm instance id
 **/
#ifdef CSM_INSTANCE_ID
  #error CSM_INSTANCE_ID is already defined
#endif
#define  CSM_INSTANCE_ID                          0x00U

/** \brief  General APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00001,1 */
#ifdef CSM_API_ENABLED_VERSIONINFO
  #error CSM_API_ENABLED_VERSIONINFO is already defined
#endif
#define  CSM_API_ENABLED_VERSIONINFO                           [!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Development Error detect enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00002,1 */
#ifdef CSM_API_ENABLED_DEVERRORDETECT
  #error CSM_API_ENABLED_DEVERRORDETECT is already defined
#endif
#define  CSM_API_ENABLED_DEVERRORDETECT                        [!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmDevErrorDetect) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Deprecated APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00003,1 */
#ifdef CSM_API_ENABLED_USEDEPRECATED
  #error CSM_API_ENABLED_USEDEPRECATED is already defined
#endif
#define  CSM_API_ENABLED_USEDEPRECATED                         [!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmUseDeprecated)  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Key management APIs enabled/disabled infos
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00004,1 */
#ifdef CSM_API_ENABLED_KEYMNGMNT
  #error CSM_API_ENABLED_KEYMNGMNT is already defined
#endif
#define  CSM_API_ENABLED_KEYMNGMNT                             [!IF "$Csm_Api_Enabled_KeyMngmnt                = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  General services interfaces enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00005,1 */
#ifdef CSM_API_ENABLED_SERVICE_GENERAL
  #error CSM_API_ENABLED_SERVICE_GENERAL is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_API_ENABLED_SERVICE_GENERAL                       [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*/CsmJobPrimitiveRef)/*/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!][!//
#define  CSM_API_ENABLED_SERVICE_GENERAL                       [!IF "$Csm_Api_Enabled_Srv                      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Asynchronous service interfaces enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00006,1 */
#ifdef CSM_API_ENABLED_SERVICE_ASYNCHRONOUS
  #error CSM_API_ENABLED_SERVICE_ASYNCHRONOUS is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_ASYNCHRONOUS                  [!IF "$Csm_Flg_Async                            = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Synchronous service interfaces enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00007,1 */
#ifdef CSM_API_ENABLED_SERVICE_SYNCHRONOUS
  #error CSM_API_ENABLED_SERVICE_SYNCHRONOUS is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_SYNCHRONOUS                   [!IF "$Csm_Flg_Sync                             = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADDecrypt APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_AEADDECRYPT
  #error CSM_API_ENABLED_SERVICE_AEADDECRYPT is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_AEADDECRYPT                   [!IF "$Csm_Api_Enabled_AEADDecrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADEncrypt APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_AEADENCRYPT
  #error CSM_API_ENABLED_SERVICE_AEADENCRYPT is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_AEADENCRYPT                   [!IF "$Csm_Api_Enabled_AEADEncrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Decrypt APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_DECRYPT
  #error CSM_API_ENABLED_SERVICE_DECRYPT is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_DECRYPT                       [!IF "$Csm_Api_Enabled_Decrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Encrypt APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_ENCRYPT
  #error CSM_API_ENABLED_SERVICE_ENCRYPT is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_ENCRYPT                       [!IF "$Csm_Api_Enabled_Encrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Hash APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_HASH
  #error CSM_API_ENABLED_SERVICE_HASH is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_HASH                          [!IF "$Csm_Api_Enabled_Hash                     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateParse APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE
  #error CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE           [!IF "$Csm_Api_Enabled_JobCertificateParse      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateVerify APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY
  #error CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY          [!IF "$Csm_Api_Enabled_JobCertificateVerify     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyDerive APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBKEYDERIVE
  #error CSM_API_ENABLED_SERVICE_JOBKEYDERIVE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBKEYDERIVE                  [!IF "$Csm_Api_Enabled_JobKeyDerive             = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcPubVal APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL
  #error CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL      [!IF "$Csm_Api_Enabled_JobKeyExchangeCalcPubVal = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcSecret APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET
  #error CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET      [!IF "$Csm_Api_Enabled_JobKeyExchangeCalcSecret = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyGenerate APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBKEYGENERATE
  #error CSM_API_ENABLED_SERVICE_JOBKEYGENERATE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBKEYGENERATE                [!IF "$Csm_Api_Enabled_JobKeyGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeySetValid APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBKEYSETVALID
  #error CSM_API_ENABLED_SERVICE_JOBKEYSETVALID is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBKEYSETVALID                [!IF "$Csm_Api_Enabled_JobKeySetValid           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobRandomSeed APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_JOBRANDOMSEED
  #error CSM_API_ENABLED_SERVICE_JOBRANDOMSEED is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_JOBRANDOMSEED                 [!IF "$Csm_Api_Enabled_JobRandomSeed            = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacGenerate APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_MACGENERATE
  #error CSM_API_ENABLED_SERVICE_MACGENERATE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_MACGENERATE                   [!IF "$Csm_Api_Enabled_MacGenerate              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacVerify APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_MACVERIFY
  #error CSM_API_ENABLED_SERVICE_MACVERIFY is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_MACVERIFY                     [!IF "$Csm_Api_Enabled_MacVerify                = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service RandomGenerate APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_RANDOMGENERATE
  #error CSM_API_ENABLED_SERVICE_RANDOMGENERATE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_RANDOMGENERATE                [!IF "$Csm_Api_Enabled_RandomGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureGenerate APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE
  #error CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE             [!IF "$Csm_Api_Enabled_SignatureGenerate        = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureVerify APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00008,1 */
#ifdef CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY
  #error CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY is already defined
#endif
#define  CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY               [!IF "$Csm_Api_Enabled_SignatureVerify          = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Key management RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00009,1 */
#ifdef CSM_RTE_ENABLED_KEYMNGMNT
  #error CSM_RTE_ENABLED_KEYMNGMNT is already defined
#endif
#define  CSM_RTE_ENABLED_KEYMNGMNT                             [!IF "$Csm_Rte_Enabled_KeyMngmnt                = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  General services RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00010,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_GENERAL
  #error CSM_RTE_ENABLED_SERVICE_GENERAL is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_GENERAL                       [!IF "$Csm_Rte_Enabled_Srv                      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  General services RTE Optimized Async Wrapper interfaces enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00025,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_GENERAL_OAW
  #error CSM_RTE_ENABLED_SERVICE_GENERAL_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_GENERAL_OAW                   [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/*/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!][!//
#define  CSM_RTE_ENABLED_SERVICE_GENERAL_OAW                   [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/*/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service AEADDecrypt RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_SYNC
  #error CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_SYNC                   [!IF "$Csm_Flg_Sync_AEADDecrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADDecrypt RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_AEADDECRYPT
  #error CSM_RTE_ENABLED_SERVICE_AEADDECRYPT is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_AEADDECRYPT                   [!IF "$Csm_Rte_Enabled_AEADDecrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADDecrypt RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW
  #error CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW               [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmAEADDecrypt/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW               [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmAEADDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service AEADEncrypt RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_SYNC
  #error CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_SYNC                   [!IF "$Csm_Flg_Sync_AEADEncrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADEncrypt RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_AEADENCRYPT
  #error CSM_RTE_ENABLED_SERVICE_AEADENCRYPT is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_AEADENCRYPT                   [!IF "$Csm_Rte_Enabled_AEADEncrypt              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service AEADEncrypt RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW
  #error CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW               [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmAEADEncrypt/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW               [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmAEADEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service Decrypt RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_DECRYPT_SYNC
  #error CSM_RTE_ENABLED_SERVICE_DECRYPT_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_DECRYPT_SYNC                       [!IF "$Csm_Flg_Sync_Decrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Decrypt RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_DECRYPT
  #error CSM_RTE_ENABLED_SERVICE_DECRYPT is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_DECRYPT                       [!IF "$Csm_Rte_Enabled_Decrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Decrypt RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW
  #error CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW                   [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmDecrypt/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW                   [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmDecrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service Encrypt RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_ENCRYPT_SYNC
  #error CSM_RTE_ENABLED_SERVICE_ENCRYPT_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_ENCRYPT_SYNC                       [!IF "$Csm_Flg_Sync_Encrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Encrypt RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_ENCRYPT
  #error CSM_RTE_ENABLED_SERVICE_ENCRYPT is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_ENCRYPT                       [!IF "$Csm_Rte_Enabled_Encrypt                  = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Encrypt RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW
  #error CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW                   [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmEncrypt/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW                   [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmEncrypt/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service Hash RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_HASH_SYNC
  #error CSM_RTE_ENABLED_SERVICE_HASH_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_HASH_SYNC                          [!IF "$Csm_Flg_Sync_Hash                     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Hash RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_HASH
  #error CSM_RTE_ENABLED_SERVICE_HASH is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_HASH                          [!IF "$Csm_Rte_Enabled_Hash                     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service Hash RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_HASH_OAW
  #error CSM_RTE_ENABLED_SERVICE_HASH_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_HASH_OAW                      [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmHash/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_HASH_OAW                      [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmHash/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobCertificateParse RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_SYNC           [!IF "$Csm_Flg_Sync_JobCertificateParse      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateParse RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE           [!IF "$Csm_Rte_Enabled_JobCertificateParse      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateParse RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW       [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobCertificateParse/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW       [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobCertificateParse/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobCertificateVerify RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_SYNC          [!IF "$Csm_Flg_Sync_JobCertificateVerify     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateVerify RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY          [!IF "$Csm_Rte_Enabled_JobCertificateVerify     = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobCertificateVerify RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW      [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobCertificateVerify/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW      [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobCertificateVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobKeyDerive RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_SYNC                  [!IF "$Csm_Flg_Sync_JobKeyDerive             = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyDerive RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE                  [!IF "$Csm_Rte_Enabled_JobKeyDerive             = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyDerive RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW              [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyDerive/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW              [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyDerive/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobKeyExchangeCalcPubVal RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_SYNC      [!IF "$Csm_Flg_Sync_JobKeyExchangeCalcPubVal = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcPubVal RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL      [!IF "$Csm_Rte_Enabled_JobKeyExchangeCalcPubVal = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcPubVal RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW  [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcPubVal/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW  [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcPubVal/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobKeyExchangeCalcSecret RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_SYNC      [!IF "$Csm_Flg_Sync_JobKeyExchangeCalcSecret = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcSecret RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET      [!IF "$Csm_Rte_Enabled_JobKeyExchangeCalcSecret = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyExchangeCalcSecret RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW  [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcSecret/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW  [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyExchangeCalcSecret/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobKeyGenerate RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_SYNC                [!IF "$Csm_Flg_Sync_JobKeyGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyGenerate RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE                [!IF "$Csm_Rte_Enabled_JobKeyGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeyGenerate RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW            [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyGenerate/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW            [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeyGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobKeySetValid RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_SYNC                [!IF "$Csm_Flg_Sync_JobKeySetValid           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeySetValid RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID                [!IF "$Csm_Rte_Enabled_JobKeySetValid           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobKeySetValid RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW            [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeySetValid/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW            [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobKeySetValid/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service JobRandomSeed RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_SYNC
  #error CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_SYNC                 [!IF "$Csm_Flg_Sync_JobRandomSeed            = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobRandomSeed RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED
  #error CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED                 [!IF "$Csm_Rte_Enabled_JobRandomSeed            = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service JobRandomSeed RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW
  #error CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW             [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobRandomSeed/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW             [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmJobRandomSeed/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service MacGenerate RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_MACGENERATE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_MACGENERATE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_MACGENERATE_SYNC                   [!IF "$Csm_Flg_Sync_MacGenerate              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacGenerate RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_MACGENERATE
  #error CSM_RTE_ENABLED_SERVICE_MACGENERATE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_MACGENERATE                   [!IF "$Csm_Rte_Enabled_MacGenerate              = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacGenerate RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW
  #error CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW               [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmMacGenerate/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW               [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmMacGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service MacVerify RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_MACVERIFY_SYNC
  #error CSM_RTE_ENABLED_SERVICE_MACVERIFY_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_MACVERIFY_SYNC                     [!IF "$Csm_Flg_Sync_MacVerify                = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacVerify RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_MACVERIFY
  #error CSM_RTE_ENABLED_SERVICE_MACVERIFY is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_MACVERIFY                     [!IF "$Csm_Rte_Enabled_MacVerify                = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service MacVerify RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW
  #error CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW                 [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmMacVerify/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW                 [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmMacVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service RandomGenerate RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_SYNC                [!IF "$Csm_Flg_Sync_RandomGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service RandomGenerate RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE
  #error CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE                [!IF "$Csm_Rte_Enabled_RandomGenerate           = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service RandomGenerate RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW
  #error CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW            [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmRandomGenerate/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW            [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmRandomGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service SignatureGenerate RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_SYNC
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_SYNC             [!IF "$Csm_Flg_Sync_SignatureGenerate        = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureGenerate RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE             [!IF "$Csm_Rte_Enabled_SignatureGenerate        = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureGenerate RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW         [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmSignatureGenerate/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW         [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmSignatureGenerate/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  Service SignatureVerify RTEs syncronous info
 **/
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_SYNC
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_SYNC is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_SYNC               [!IF "$Csm_Flg_Sync_SignatureVerify          = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureVerify RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00011,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY is already defined
#endif
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY               [!IF "$Csm_Rte_Enabled_SignatureVerify          = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Service SignatureVerify RTE Optimized Async Wrapper APIs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00026,1 */
#ifdef CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW
  #error CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW is already defined
#endif
[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW           [!IF "num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmSignatureVerify/*/*[(contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS') or (starts-with(node:name(.), 'CsmJob'))]))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define  CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW           [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmAsyncJobInterfaceUseDataReferences) = 'true' and num:i(0) != num:i(count(node:refs(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true']/CsmJobPrimitiveRef)/CsmSignatureVerify/*/*[contains(node:name(.),'Processing') and node:value(.) = 'CSM_ASYNCHRONOUS']))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDIF!][!//

/** \brief  General RTE enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00012,1 */
#ifdef CSM_RTE_ENABLED
  #error CSM_RTE_ENABLED is already defined
#endif
#define  CSM_RTE_ENABLED                                   [!IF "$Csm_Rte_Enabled_All                      = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Callback notification RTEs enabled/disabled info
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00028,1 */
#ifdef CSM_RTE_ENABLED_CALLBACK
  #error CSM_RTE_ENABLED_CALLBACK is already defined
#endif
#define  CSM_RTE_ENABLED_CALLBACK                   [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false' and $Csm_Rte_Enabled_Callback = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* --- Jobs --- */

[!INDENT "0"!][!//
[!VAR "MAXLEN" = "num:i(13)"!][!//
[!LOOP "as:modconf('Csm')/CsmJobs/CsmJob/*"!][!//
  [!IF "$MAXLEN < num:i(string-length(node:name(.)))"!][!VAR "MAXLEN" = "num:i(string-length(node:name(.)))"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!LOOP "as:modconf('Csm')/CsmJobs/CsmJob/*"!][!//
/** \brief  Csm job 'CsmConf_CsmJob_[!"node:name(.)"!]'
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00013,1 */
#ifdef CsmConf_CsmJob_[!"node:name(.)"!]
  #error CsmConf_CsmJob_[!"node:name(.)"!] is already defined
#endif
#define  CsmConf_CsmJob_[!"node:name(.)"!]  [!"substring($SPACE, 1, $MAXLEN - string-length(node:name(.)))"!][!CALL "HEX", "_value" = "node:value(CsmJobId)"!]U

[!ENDLOOP!][!//
[!ENDINDENT!][!//
/** \brief  Number of Csm jobs
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00014,1 */
#ifdef CSM_JOB_COUNT
  #error CSM_JOB_COUNT is already defined
#endif
#define  CSM_JOB_COUNT  [!"substring($SPACE, 1, $MAXLEN - 13)"!][!CALL "HEX", "_value" = "num:i(count(as:modconf('Csm')/CsmJobs/CsmJob/*))"!]U

/* --- Keys --- */

[!INDENT "0"!][!//
[!VAR "MAXLEN" = "num:i(13)"!][!//
[!LOOP "as:modconf('Csm')/CsmKeys/CsmKey/*"!][!//
  [!IF "$MAXLEN < num:i(string-length(node:name(.)))"!][!VAR "MAXLEN" = "num:i(string-length(node:name(.)))"!][!ENDIF!][!//
[!ENDLOOP!][!//
/** \brief  The value representing an empty key in Crypto_JobPrimitiveInfoType
 **/
#ifdef CSM_KEY_EMPTY
  #error CSM_KEY_EMPTY is already defined
#endif
#define  CSM_KEY_EMPTY  [!"substring($SPACE, 1, $MAXLEN - 13)"!]0xFFFFFFFFU

[!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440'"!][!//
[!LOOP "as:modconf('Csm')/CsmKeys/CsmKey/*"!][!//
#ifdef [!"node:name(.)"!]
  #error CsmConf_CsmKey_[!"node:name(.)"!] is already defined
#endif
#define  CsmConf_CsmKey_[!"node:name(.)"!]  [!"substring($SPACE, 1, $MAXLEN - string-length(node:name(.)))"!][!IF "node:refvalid(CsmKeyRef) and not(node:empty(CsmKeyRef))"!][!CALL "HEX", "_value" = "num:i(node:value(CsmKeyId))"!]U [!ELSE!]CSM_KEY_EMPTY[!ENDIF!]

[!ENDLOOP!][!//
[!ELSE!][!//
[!LOOP "as:modconf('Csm')/CsmKeys/CsmKey/*"!][!//
/** \brief  The Csm key '[!"node:name(.)"!]'
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00015,1 */
#ifdef [!"node:name(.)"!]
  #error [!"node:name(.)"!] is already defined
#endif
#define  [!"node:name(.)"!]  [!"substring($SPACE, 1, $MAXLEN - string-length(node:name(.)))"!][!IF "node:refvalid(CsmKeyRef) and not(node:empty(CsmKeyRef))"!][!CALL "HEX", "_value" = "num:i(node:value(CsmKeyId))"!]U [!ELSE!]CSM_KEY_EMPTY[!ENDIF!]

[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//
/** \brief  Number of Csm keys
 **/
/* !LINKSTO CSM.Dsn.Api/Macros/00016,1 */
#ifdef CSM_KEY_COUNT
  #error CSM_KEY_COUNT is already defined
#endif
#define  CSM_KEY_COUNT  [!"substring($SPACE, 1, $MAXLEN - 13)"!][!CALL "HEX", "_value" = "num:i(count(as:modconf('Csm')/CsmKeys/CsmKey/*))"!]U

#if (defined CSM_API_ENABLED_KEYSETINVALID)
#error CSM_API_ENABLED_KEYSETINVALID is already defined
#endif
/** \brief  Should Csm_KeySetInvalid function be activated? **/
/* !LINKSTO CSM.Dsn.Api/Macros/00030,1 */
#define  CSM_API_ENABLED_KEYSETINVALID                [!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbEnhancementApiCsmKeySetInvalid) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CSM_API_ENABLED_KEYGETSTATUS)
#error CSM_API_ENABLED_KEYGETSTATUS is already defined
#endif
/** \brief  Should Csm_KeyGetStatus function be activated? **/
/* !LINKSTO CSM.Dsn.Api/Macros/00029,1 */
#define  CSM_API_ENABLED_KEYGETSTATUS                [!IF "node:value(./CsmEbGeneral/CsmEbMisc/CsmEbEnhancementApiCsmKeyGetStatus) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* --- Misc ------------------------------------------------------------------------------------- */

#ifdef CSM_API_VERSION
  #error CSM_API_VERSION is already defined
#endif
/** \brief  tbd **/
/* !LINKSTO CSM.Dsn.Api/Macros/00022,1 */
#define CSM_API_VERSION [!"node:value(./CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion)"!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

#define CSM_START_SEC_CONST_UNSPECIFIED
#include <Csm_MemMap.h>

/* --- PrimitiveInfo ---------------------------------------------------------------------------- */

/** \brief  Configured instances of Crypto_PrimitiveInfoType referenced in configured
 **         instances of Crypto_JobPrimitiveInfoType
 **/
[!LOOP "as:modconf('Csm')/CsmJobs/CsmJob/*"!][!//
[!IF "false() = node:empty(./CsmJobPrimitiveRef) and true() = node:refvalid(./CsmJobPrimitiveRef)"!][!//
extern CONST(Crypto_PrimitiveInfoType, CSM_CONST) Csm_PI_[!"node:name(.)"!]_[!"node:name(node:ref(./CsmJobPrimitiveRef))"!];
[!ENDIF!][!//
[!ENDLOOP!][!//

/* --- JobPrimitiveInfo ------------------------------------------------------------------------- */

/** \brief  Configured instances of Crypto_JobPrimitiveInfoType referenced in configured
 **         instances of Crypto_JobType
 **/
[!LOOP "as:modconf('Csm')/CsmJobs/CsmJob/*"!][!//
extern CONST(Crypto_JobPrimitiveInfoType, CSM_CONST) Csm_JPI_[!"node:name(.)"!];
[!ENDLOOP!][!//

/* --- JobInfo ---------------------------------------------------------------------------------- */

/** \brief  Configured instances of Crypto_JobInfoType referenced in configured
 **         instances of Crypto_JobType
 **/
[!LOOP "as:modconf('Csm')/CsmJobs/CsmJob/*"!][!//
extern CONST(Crypto_JobInfoType, CSM_CONST) Csm_JI_[!"node:name(.)"!];
[!ENDLOOP!][!//

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <Csm_MemMap.h>

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <Csm_MemMap.h>

/* --- Jobs ------------------------------------------------------------------------------------- */

/** \brief  List of configured Csm jobs
 **/
extern VAR(Crypto_JobType, CSM_APPL_DATA) Csm_JobConfigurations[CSM_JOB_COUNT];

#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Csm_MemMap.h>

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/* --- Mainfunctions --- */
[!IF "count(CsmMainFunction/*) = 0"!][!//
/** \brief  API to be called cyclically to process the requested jobs. The Csm_MainFunction
 **         shall check the queues for jobs to pass to the underlying CRYIF.
 **
 ** \ServiceID{::CSM_SID_MAINFUNCTION}
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Non Reentrant}
 **/

#if ((CSM_API_ENABLED_SERVICE_ASYNCHRONOUS == STD_ON) && ((CSM_RTE_ENABLED == STD_OFF) || (!defined(CSM_SRC))))
#ifndef RTE_SCHM_SWCBSW_CSM_MAINFUNCTION
#define RTE_SCHM_SWCBSW_CSM_MAINFUNCTION

extern FUNC(void, CSM_CODE) Csm_MainFunction
(
  void
);

#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_MAINFUNCTION */
#endif /* #if ((CSM_API_ENABLED_SERVICE_ASYNCHRONOUS == STD_ON) && ((CSM_RTE_ENABLED == STD_OFF) || (!defined(CSM_SRC)))) */
[!ENDIF!][!//

[!IF "count(CsmMainFunction/*) != 0"!][!//
/** \brief  API to be called cyclically to process the requested jobs. The Csm_MainFunction shall
 **         check the queues for jobs to pass to the underlying CRYIF. Per configured
 **         CsmMainFunction instance one Csm_MainFunction_<shortName> shall be implemented. Hereby
 **         <shortName> is the short name of the CsmMainFunction configuration container in the ECU
 **         configuration.
 **
 ** \Synchronicity{Synchronous}
 ** \Reentrancy{Non Reentrant}
 **/
 /**@{*/
#if ((CSM_RTE_ENABLED == STD_OFF) || (!defined(CSM_SRC)))
[!LOOP "as:modconf('Csm')/CsmMainFunction/*"!][!//

#ifndef RTE_SCHM_SWCBSW_CSM_MAINFUNCTION_[!"text:toupper(node:name(.))"!]
#define RTE_SCHM_SWCBSW_CSM_MAINFUNCTION_[!"text:toupper(node:name(.))"!]
extern FUNC(void, CSM_CODE) Csm_MainFunction_[!"node:name(.)"!]
(
  void
);
#endif /* #ifndef RTE_SCHM_SWCBSW_CSM_MAINFUNCTION_[!"text:toupper(node:name(.))"!] */
[!ENDLOOP!][!//
#endif /* #if ((CSM_RTE_ENABLED == STD_OFF) || (!defined(CSM_SRC))) */
/**@}*/
[!ENDIF!][!//

/* --- Callbacks --- */

/** \brief  Declarations of configured Csm callbacks
 **/
/* !LINKSTO CSM.Dsn.Api/Funcs/00001,1 */
[!LOOP "as:modconf('Csm')/CsmCallbacks/CsmCallback/*[not(node:empty(./CsmCallbackFunc))]"!][!//
extern FUNC(void, CSM_APPL_CODE) [!"node:value(./CsmCallbackFunc)"!]
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job, Std_ReturnType result
);
[!ENDLOOP!][!//

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CSM_CFG_H */

/*==================[end of file]=================================================================*/

