/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <Csm_Cfg.h>
#include <Csm_Types.h>
#include <Csm_Version.h>

#if (CSM_RTE_ENABLED == STD_ON)
#include <Rte_Csm.h>
#endif

#include <Csm_AsymPrivateKeyWrapAsym.h>
#include <Csm_AsymPrivateKeyWrapSym.h>
#include <Csm_AsymPublicKeyExtract.h>
#include <Csm_Checksum.h>
#include <Csm_Hash.h>
#include <Csm_MacGenerate.h>
#include <Csm_MacVerify.h>
#include <Csm_RandomGenerate.h>
#include <Csm_RandomSeed.h>
#include <Csm_SignatureGenerate.h>
#include <Csm_SignatureVerify.h>
#include <Csm_SymBlockEncrypt.h>
#include <Csm_SymBlockDecrypt.h>
#include <Csm_SymEncrypt.h>
#include <Csm_SymDecrypt.h>
#include <Csm_SymKeyExtract.h>
#include <Csm_SymKeyWrapAsym.h>
#include <Csm_SymKeyWrapSym.h>

#include <SchM_Csm.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_Init]----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0646, 1
 */
FUNC(void, CSM_CODE) Csm_Init
(
  void
)
{
#if (CSM_ASYMPRIVATEKEYWRAPASYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_AsymPrivateKeyWrapAsymInit();
#endif
#if (CSM_ASYMPRIVATEKEYWRAPSYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_AsymPrivateKeyWrapSymInit();
#endif
#if (CSM_ASYMPUBLICKEYEXTRACT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_AsymPublicKeyExtractInit();
#endif
#if (CSM_CHECKSUM_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_ChecksumInit();
#endif
#if (CSM_HASH_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_HashInit();
#endif
#if (CSM_MACGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_MacGenerateInit();
#endif
#if (CSM_MACVERIFY_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_MacVerifyInit();
#endif
#if (CSM_RANDOMGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_RandomGenerateInit();
#endif
#if (CSM_RANDOMSEED_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_RandomSeedInit();
#endif
#if (CSM_SIGNATUREGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SignatureGenerateInit();
#endif
#if (CSM_SIGNATUREVERIFY_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SignatureVerifyInit();
#endif
#if (CSM_SYMBLOCKENCRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymBlockEncryptInit();
#endif
#if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymBlockDecryptInit();
#endif
#if (CSM_SYMENCRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymEncryptInit();
#endif
#if (CSM_SYMDECRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymDecryptInit();
#endif
#if (CSM_SYMKEYEXTRACT_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymKeyExtractInit();
#endif
#if (CSM_SYMKEYWRAPASYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymKeyWrapAsymInit();
#endif
#if (CSM_SYMKEYWRAPSYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0021, 1
   */
  Csm_SymKeyWrapSymInit();
#endif
}

#if (CSM_SYNCJOBPROCESSING_ENABLED == STD_OFF)
/*------------------------------------------------------------------------------------------------*/
/*----[Csm_MainFunction]--------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0477, 1
 */
/* !LINKSTO CSM0479, 1
 */
FUNC(void, CSM_CODE) Csm_MainFunction
(
  void
)
{
  SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();

#if (CSM_ASYMPRIVATEKEYWRAPASYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_AsymPrivateKeyWrapAsymMainFunction();
#endif
#if (CSM_ASYMPRIVATEKEYWRAPSYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_AsymPrivateKeyWrapSymMainFunction();
#endif
#if (CSM_ASYMPUBLICKEYEXTRACT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_AsymPublicKeyExtractMainFunction();
#endif
#if (CSM_CHECKSUM_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_ChecksumMainFunction();
#endif
#if (CSM_HASH_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_HashMainFunction();
#endif
#if (CSM_MACGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_MacGenerateMainFunction();
#endif
#if (CSM_MACVERIFY_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_MacVerifyMainFunction();
#endif
#if (CSM_RANDOMGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_RandomGenerateMainFunction();
#endif
#if (CSM_RANDOMSEED_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_RandomSeedMainFunction();
#endif
#if (CSM_SIGNATUREGENERATE_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SignatureGenerateMainFunction();
#endif
#if (CSM_SIGNATUREVERIFY_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SignatureVerifyMainFunction();
#endif
#if (CSM_SYMBLOCKENCRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymBlockEncryptMainFunction();
#endif
#if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymBlockDecryptMainFunction();
#endif
#if (CSM_SYMENCRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymEncryptMainFunction();
#endif
#if (CSM_SYMDECRYPT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymDecryptMainFunction();
#endif
#if (CSM_SYMKEYEXTRACT_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymKeyExtractMainFunction();
#endif
#if (CSM_SYMKEYWRAPASYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymKeyWrapAsymMainFunction();
#endif
#if (CSM_SYMKEYWRAPSYM_ENABLED == STD_ON)
  /* !LINKSTO CSM0480, 1
   */
  /* !LINKSTO CSM0469, 1
   */
  Csm_SymKeyWrapSymMainFunction();
#endif

  SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
}
#endif /* #if (CSM_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/*------------------------------------------------------------------------------------------------*/
/*----[Csm_GetVersionInfo]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CSM0707, 1
 */
#if (CSM_GETVERSIONINFO_ENABLED == STD_ON)

/* !LINKSTO CSM0705, 1
 */
FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versionInfo
)
{
  if (NULL_PTR != versionInfo)
  {
    /* !LINKSTO CSM0706, 1
     */
    versionInfo->vendorID         = CSM_VENDOR_ID;
    versionInfo->moduleID         = CSM_MODULE_ID;
    versionInfo->sw_major_version = CSM_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = CSM_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = CSM_SW_PATCH_VERSION;
  }
}

#endif /* #if (CSM_GETVERSIONINFO_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

/*==================[end of file]=================================================================*/

