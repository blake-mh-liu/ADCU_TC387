#ifndef PROG_ENCRYPT_H
#define PROG_ENCRYPT_H

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
/*%%   _____________________________   %%  \file PROG_Encrypt.h                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2020 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!AUTOSPACING!]
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/* Data structure for decrypted data */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"
#endif

[!IF "node:exists(as:modconf('Csm'))"!]
 [!IF "Decryption/Enable_Csm_Decryption = 'true'"!]
#define PROG_CSM_DECRYPTION_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Decryption/ProgCsmDecryptionConfigId))"!])
 [!ENDIF!]
[!ENDIF!]

/* Status of encryption or decryption operation */
#define PROG_NO_OPERATION_IN_PROGRESS      0x00U
#define PROG_ENCRYPTION_IN_PROGRESS        0x55U
#define PROG_DECRYPTION_IN_PROGRESS        0xAAU

/* Decrypption state machine */
#define PROG_DECRYPTION_START              0x15U
#define PROG_DECRYPTION_START_END          0x16U
#define PROG_DECRYPTION_UPDATE             0x17U
#define PROG_DECRYPTION_UPDATE_END         0x18U
#define PROG_DECRYPTION_FINISH             0x19U
#define PROG_DECRYPTION_FINISH_END         0x1AU
#define PROG_DECRYPTION_START_DONE         0x95U
#define PROG_DECRYPTION_UPDATE_DONE        0x97U
#define PROG_DECRYPTION_FINISH_DONE        0x99U
/** \brief Evaluates the result of Crypto operation
 **
 ** \param[out] eCsmStatus is the status returned from the Csm
 ** module for the last or current Crypto operation
 **
 **/
extern void PROG_CsmDecryptionCheckResult(Csm_ReturnType eCsmStatus);

#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */
#endif      /* PROG_ENCRYPT_H */
