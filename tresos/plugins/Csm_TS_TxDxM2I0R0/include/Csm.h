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

/* !LINKSTO CSM0005, 1
 */

#ifndef CSM_H
#define CSM_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_Version.h>

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

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Initialization of of the CSM.
 **
 ** This function initializes all configured services of the CSM.
 **/
extern FUNC(void, CSM_CODE) Csm_Init
(
  void
);

#if ((CSM_SYNCJOBPROCESSING_ENABLED == STD_OFF) && (CSM_RTE_ENABLED == STD_OFF))

/** \brief Perform the CSM tasks.
 **
 ** This function performs the actual computations of the CSM services.
 **/
extern FUNC(void, CSM_CODE) Csm_MainFunction
(
  void
);

#endif /* #if (CSM_SYNCJOBPROCESSING_ENABLED == STD_OFF && CSM_RTE_ENABLED == STD_OFF) */

#if (CSM_GETVERSIONINFO_ENABLED == STD_ON)

/** \brief  This function can be used to get information about the version of the Csm.
 **
 ** \param[out]  versionInfo  A pointer to a variable where the version information should
 **                           be stored.
 **/
extern FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versionInfo
);

#endif /* #if (CSM_GETVERSIONINFO_ENABLED == STD_ON) */

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_H */

/*==================[end of file]=================================================================*/

