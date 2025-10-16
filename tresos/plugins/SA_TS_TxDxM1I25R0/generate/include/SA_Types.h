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
/*%%   _____________________________   %%  \file SA_Types.h                   */
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

#ifndef SA_TYPES_H
#define SA_TYPES_H

#include "SA_Cfg.h"
#include <ComStack_Cfg.h>

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Csm.h"
[!IF "(as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Std_Types.h"
[!ENDIF!]
[!ENDIF!]

typedef u8 tSaStatus;
#define SA_E_STATUS_UNKNOWN 0x00U
#define SA_E_OK             0x01U
#define SA_E_NOT_OK         0x02U
#define SA_E_BUSY           0x03U
/*Following are for Anti-scanning*/
#define SA_E_NOK_INVALID_KEY      0x04U
[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define SA_E_NOK_AS_LOCKED        0x05U
[!ENDIF!]
/*Following are for Request Seed Limit*/
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define SA_E_NOK_AS_LIMIT_RS        0x06U
[!ENDIF!]
[!IF "General/Security_Access_Rs_Delay_Timer != '0'"!]
#define SA_E_NOK_RS_DELAY_LOCKED        0x07U
[!ENDIF!]

[!IF "((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001'))"!]
/*SA_AM0001 Procedure specific Status Values*/
#define SA_SA2AWATINGTIME_EXPIRED       0x08U
#define SA_AM0001_PROCESSING_FAILED     0x09U
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
typedef u8 tSaCsmState;
[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random')"!]
#define SA_CSM_STATE_INIT               0x00U
#define SA_IDLE                         0x01U
#define SA_SEED_GEN_STATE_INIT          0x02U
#define SA_SEED_GEN_STATE_START         0x03U
#define SA_SEED_GEN_STATE_UPDATE        0x05U
#define SA_RANDOM_GEN_STATE_GENERATE    0x06U
#define SA_RANDOM_GEN_STATE_STANDBY     0x07U
[!ENDIF!]
[!IF "(as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#define SA_SIGNATURE_CHECK_START        0x08U
#define SA_SIGNATURE_CHECK_UPDATE       0x09U
#define SA_SIGNATURE_CHECK_STANDBY      0x0CU
#define SA_SIGNATURE_CHECK_FINISH       0x0AU
[!ENDIF!]
[!ENDIF!]

/* SA boolean type */
#define SA_FALSE               0U
#define SA_TRUE                1U
typedef u8 tSaBoolean;

[!IF "node:exists(as:modconf('Prog')) and (as:modconf('Prog')/General/Enable_Compression = 'true')"!]
/*
* Number of bits allocated to indices into the text window
*/
#define LZSS_INDEX_BIT_COUNT      (u8)10U
/*
* Number of bits allocated for the length of an encode phrase
*/
#define LZSS_LENGTH_BIT_COUNT     (u8)4U
/*
* Size of the sliding window
*/
#define LZSS_WINDOW_SIZE          (u16)((u16)(1U) << LZSS_INDEX_BIT_COUNT )
/*
* Number of bytes to encode a byte array.
* Used to calculate if compression should be done or not
*/
#define LZSS_BREAK_EVEN   (u8)( ( 1U + LZSS_INDEX_BIT_COUNT + LZSS_LENGTH_BIT_COUNT ) / 9U )
/*
* End of stream indicator
*/
#define LZSS_END_OF_STREAM        (u8)0U

#define LZSS_MOD_WINDOW( a )      (u16)( ( a ) & ( LZSS_WINDOW_SIZE - 1U ) )

#define SA_DECOMP_OUT_BUF_SIZE   [!"num:i(General/Decomp_Out_Buffer_size)"!]U

#define SA_DECOMP_INIT              0x01U
#define SA_DECOMP_UNCOMPRESSED      0x02U
#define SA_DECOMP_COMPRESSPOS       0x04U
#define SA_DECOMP_COMPRESSLEN       0x08U
#define SA_DECOMP_COMPLETE          0x10U
#define SA_DECOMP_IN_PROGRESS       0x20U
#define SA_DECOMP_FINISH            0x40U
#define SA_ERR_NULL_PTR             0x80U
typedef u8 tDecompressStateType;
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
typedef struct
{
 u8 ubRequestCounter ;       /*Request seed limit counter*/
 u32 ulTimer;                /*Request seed limit Timer*/
}tLimitReqSeedInfo;
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
typedef struct
{
 u8 ubRetryCnt;              /*Anti-scanning retry counter*/
 u32 ulLockTimer;            /*Anti-scanning Lock Timer*/
 tSaBoolean ubAsLocked;      /*Anti-scanning Lock State */
}tAntiscanInfo;
[!ENDIF!]

[!IF "((node:exists(as:modconf('ProgVCC'))) and ((node:exists(as:modconf('SA')/General/SA_AM_TYPE)) and (as:modconf('SA')/General/SA_AM_TYPE = 'Authentication Method 0001')))"!]

 typedef struct{
  Csm_SymKeyType const* CsmKeyPtr; /*Pointer to Key(Optional, depends the HW or SW Engine used)*/
  u32 DataLen;   /*Data Length for Mac computation*/
  u32 MACLen;    /*MAC Checksum Length*/
  u32* MACLenPtr;/*Pointer to MAC Checksum Length*/
  u8* DataPtr;   /*Pointer to data on which the MAC computation shall be performed*/
  u8* MACPtr;    /*Pointer to the computed/stored MAC Checksum*/
  u8 CsmCfdID;   /*Tresos CSM Configuration ID*/
  } tSA_MACAlgo;

  typedef struct{
  Csm_SymKeyType const* CsmKeyPtr;  /*Pointer to Key(Optional, depends the HW or SW Engine used)*/
  u32 IVLen;      /*Length or the Size of the Initialization Vector*/
  u32 CTLen;      /*Length or the Size of the Encrypted data*/
  u32 PTLen;      /*Length or the Size of the non-encrypted or decrypted data*/
  u32* PTLenptr;  /*Ponter to PTLen*/
  u32* CTLenptr;  /*Pointer to CTLen*/
  u8 * IVptr;     /*Pointer to IVLen*/
  u8 *PTptr;      /*Pointer to non-encrypted or decrypted data*/
  u8* CTptr;      /*Pointer to Encrypted data*/
  u8 CsmCfdID;    /*Tresos CSM Configuration ID*/
  }tSA_AESCTRAlgo;

  typedef struct  {
  u32 DataLength; /*Length or the Size of the data to be concatenated*/
  u8 * DataPtr;   /*Pointer to the data to be concatenated*/
  }tSA_ConcatenatePar;

  /*Variable type specific to SA AM 0001*/
  typedef u32 tSA_AuthenticationState;
[!ENDIF!]

[!IF "node:exists(as:modconf('CryIf'))"!]
typedef struct
{
	  u32 ubCsmJobId; /* Corresponding Csm Job ID */
	  u32 ubCsmKeyID; /* KeyID assigned by Crypto Driver */
	  u32 ubCryptoElementId; /* KeyElementID assigned by the Crypto Driver */
	  u32 ubCryptoKeyLength; /* KeyLength stored in the Crypto Driver */
	  boolean ubAllowJobCancellation; /* Cancel all ongoing Csm Jobs */
	  boolean ubAllowKeySet; /* Enable to set the key and the keystatus in the Crypto driver */
	  boolean ubAllowCustCsmPreProc; /* TRUE if the Custom Preprocessing before the CsmStart is expected (eg.: DER Key encoding )*/
 }tSACsmJobConf;
 
/* Below are the Csm ASR v4.3 depreciated typedef and macros that are needed for the Bootloader */
#define Csm_ReturnType                   Std_ReturnType
#define Csm_VerifyResultType             Crypto_VerifyResultType
#ifndef CSM_E_OK
#define CSM_E_OK                         E_OK
#endif
#ifndef CSM_E_NOT_OK
#define CSM_E_NOT_OK                     E_NOT_OK
#endif
#ifndef CSM_E_VER_OK
#define CSM_E_VER_OK                     CRYPTO_E_VER_OK
#endif
#ifndef CSM_E_VER_NOT_OK
#define CSM_E_VER_NOT_OK                 CRYPTO_E_VER_NOT_OK
#endif
#ifndef CSM_E_BUSY
#define CSM_E_BUSY                       CRYPTO_E_BUSY
#endif
[!ENDIF!]


[!IF "(as:modconf('SA')/General/Compare_Key_Type = 'Custom')"!]
typedef u8 Dcm_NegativeResponseType;
[!ENDIF!]
#endif      /* SA_TYPES_H */
