#ifndef PROG_CRY_H
#define PROG_CRY_H

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
/*%%   _____________________________   %%  \file PROG_Cry.h                      */
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
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!AUTOSPACING!]
#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
typedef u8 tProgCryState;
#define PROG_IDLE                          0x00U
#define PROG_SIGNATURE_CHECK_START         0x01U
#define PROG_SIGNATURE_CHECK_UPDATE        0x02U
#define PROG_SIGNATURE_CHECK_UPDATE_END    0x03U
#define PROG_SIGNATURE_CHECK_FINISH        0x04U
#define PROG_HASH_START                    0x05U
#define PROG_HASH_START_END                0x06U
#define PROG_HASH_UPDATE                   0x07U
#define PROG_HASH_END                      0x08U
#define PROG_HASH_FINISH                   0x09U
#define PROG_SIGNATURE_CHECK_START_END     0x0AU
#define PROG_MAC_GENERATE_START            0x0BU
#define PROG_MAC_GENERATE_START_END        0x0CU
#define PROG_MAC_GENERATE_UPDATE           0x0DU
#define PROG_MAC_GENERATE_UPDATE_END       0x0EU
#define PROG_MAC_GENERATE_FINISH           0x0FU
#define PROG_CSM_JOBCANCEL_INPROGRESS      0x10U
#define PROG_SIGNATURE_CHECK_STREAMSTART   0x11U
#define PROG_SIGNATURE_CHECK_STREAMSTART_DONE   0x91U
[!IF "node:exists(as:modconf('CryIf'))"!]
/* Macros needed when Csm ASR v4.3 or higher stack is used.
 * The values represented by the macros below are generated
 * as a result of the bitwise operations performed during the
 * Prog-Crypto job execution */
#define PROG_SIGNATURE_CHECK_START_DONE    0x81U
#define PROG_SIGNATURE_CHECK_UPDATE_DONE   0x82U
#define PROG_SIGNATURE_CHECK_FINISH_DONE   0x84U
#define PROG_SIGNATURE_CHECK_FINISH_TXCONF 0x44U
#define PROG_HASH_START_DONE               0x85U
#define PROG_HASH_UPDATE_DONE              0x87U
#define PROG_HASH_FINISH_DONE              0x89U
#define PROG_HASH_FINISH_TXCONF            0x49U
#define PROG_MAC_GENERATE_START_DONE       0x8BU
#define PROG_MAC_GENERATE_UPDATE_DONE      0x8DU
#define PROG_MAC_GENERATE_FINISH_DONE      0x8FU
#define PROG_CSM_JOBCANCEL_DONE            0x90U
[!ENDIF!]
/* Define the structure of a public key used for signature verification */
typedef struct
{
    const u8* pubKeyModulus;
    uint32 ulKeyModulusSize;
    const u8* pubKeyExponent;
    uint32 ulKeyExponentSize;
}tKeyStructure;

[!IF "node:exists(as:modconf('Csm'))"!]

[!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
[!IF "node:exists(as:modconf('ProgJLR')) or (node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid'))"!]
  [!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
  [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
    [!IF "Segments/*[number($SEGMENT_IDX)]/SignatureVerification = 'true'"!]
      [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
      [!VAR "SEGMENT_IDX"="$SEGMENT_MAX"!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/* define the ID of each configuration */
#define PROG_CSM_SIG_VERIFY_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/GM/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!])
#define PROG_CSM_HASH_FOR_SIGNATURE_ID    CSM_INDEX([!"name(as:ref(as:modconf('Prog')/GM/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!])
[!ELSEIF "node:exists(as:modconf('ProgVCC'))"!]
#define PROG_CSM_SIG_VERIFY_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!])
#define PROG_CSM_HASH_ID                  CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!])
[!ELSEIF "node:exists(as:modconf('ProgFord'))"!]
#define PROG_CSM_SIG_VERIFY_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!])
#define PROG_CSM_HASH_ID                  CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!])
[!ELSEIF "node:exists(as:modconf('ProgJLR'))"!]
#define PROG_CSM_SIG_VERIFY_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!])
#define PROG_CSM_HASH_FOR_SIGNATURE_ID    CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!])
[!ELSEIF "((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') and ($SIGNATUREVERIFCATIONENABLED = 'true'))
       or  (node:exists(as:modconf('ProgOEMInd')) and (OemInd/Checksum_Algo = 'Signature'))
       or ((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'))
       or   node:exists(as:modconf('ProgVAG'))
       or   node:exists(as:modconf('ProgDAG'))"!]
#define PROG_CSM_SIG_VERIFY_ID            CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/SignatureVerification/ProgCsmSignatureVerifyConfigId))"!])
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgOEMInd')) and (OemInd/Checksum_Algo = 'Hash256' or OemInd/Checksum_Algo = 'Hash512')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
#define PROG_CSM_HASH_FOR_SIGNATURE_ID    CSM_INDEX([!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/HashVerification/ProgCsmHashConfigId))"!])
[!ENDIF!]

[!ENDIF!]

/* Define the size of the modulus and exponent used for signature verification */
#define PROG_MODULUS_SIZE                 256U
#define PROG_EXPONENT_SIZE                3U

[!IF "Decryption/Enable_Csm_Decryption = 'true'"!]
/* Encryption-Decryption state */
extern tProgCryState m_eEncryptDecryptState;
[!ENDIF!]
/*                                                                               */
/*-------------------------------------------------------------------------------*/

#endif /* (PROG_CRY_PRESENT == STD_ON) */
#endif      /* PROG_CRY_H */
