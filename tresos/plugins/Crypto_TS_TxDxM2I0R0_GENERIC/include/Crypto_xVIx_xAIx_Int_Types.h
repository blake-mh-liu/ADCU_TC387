/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_TYPES_H
#define CRYPTO_XVIX_XAIX_INT_TYPES_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <TSAutosar.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0002,1 */
#include <TSMem.h>      /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0003,1 */

#include <Csm_Types.h>               /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0004,1 */

#include <Crypto_xVIx_xAIx_Types.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0005,1 */
#include <Crypto_xVIx_xAIx_KeyManagement_Types.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0006,1 */
#include <Crypto_xVIx_xAIx_Version.h>              /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Types.h/0007,1 */

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_CDOSTATE_IDLE)
#error CRYPTO_XVIX_XAIX_CDOSTATE_IDLE is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CDOStateType::CRYPTO_XVIX_XAIX_CDOSTATE_IDLE
 **         Crypto driver object is idle.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOStateType/0001,1 */
#define CRYPTO_XVIX_XAIX_CDOSTATE_IDLE 0x00U

#if (defined CRYPTO_XVIX_XAIX_CDOSTATE_BUSY)
#error CRYPTO_XVIX_XAIX_CDOSTATE_BUSY is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CDOStateType::CRYPTO_XVIX_XAIX_CDOSTATE_BUSY
 **         Crypto driver object is busy.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOStateType/0001,1 */
#define CRYPTO_XVIX_XAIX_CDOSTATE_BUSY 0x01U

#if (defined CRYPTO_XVIX_XAIX_KEY_EMPTY)
#error CRYPTO_XVIX_XAIX_KEY_EMPTY is already defined
#endif
/** \brief  Member jobPrimitiveInfo->cryIfKeyId of a job is not set. **/
#define CRYPTO_XVIX_XAIX_KEY_EMPTY 0xFFFFFFFFU

#if (defined CRYPTO_XVIX_XAIX_CBK_EMPTY)
#error CRYPTO_XVIX_XAIX_CBK_EMPTY is already defined
#endif
/** \brief  Member jobPrimitiveInfo->callbackId of a job is not set. **/
#define CRYPTO_XVIX_XAIX_CBK_EMPTY 0xFFFFFFFFU

#if (defined CRYPTO_XVIX_XAIX_SID_EMPTY)
#error CRYPTO_XVIX_XAIX_SID_EMPTY is already defined
#endif
/** \brief  Identifies a not real SID **/
#define CRYPTO_XVIX_XAIX_SID_EMPTY 0xFFU

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_NONE)
#error CRYPTO_XVIX_XAIX_CALLBACK_NONE is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_NONE. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_NONE 0x00U

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_START)
#error CRYPTO_XVIX_XAIX_CALLBACK_START is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_START. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_START 0x01U

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_UPDATE)
#error CRYPTO_XVIX_XAIX_CALLBACK_UPDATE is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_UPDATE. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_UPDATE 0x02U

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_FINISH)
#error CRYPTO_XVIX_XAIX_CALLBACK_FINISH is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_FINISH. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_FINISH 0x03U

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_CANCEL)
#error CRYPTO_XVIX_XAIX_CALLBACK_CANCEL is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_CANCEL. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_CANCEL 0x04U

#if (defined CRYPTO_XVIX_XAIX_CALLBACK_RESET)
#error CRYPTO_XVIX_XAIX_CALLBACK_RESET is already defined
#endif
/** \brief  Crypto_xVIx_xAIx_CallbackType::CRYPTO_XVIX_XAIX_CALLBACK_RESET. **/
#define CRYPTO_XVIX_XAIX_CALLBACK_RESET 0x05U

#if (defined CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
#error CRYPTO_XVIX_XAIX_PROCESSING_BOTH is already defined
#endif
/** \brief  Crypto_ProcessingType::CRYPTO_XVIX_XAIX_PROCESSING_BOTH. **/
#define CRYPTO_XVIX_XAIX_PROCESSING_BOTH 0x03U

#if (defined CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN)
#error CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN is already defined
#endif
/** \brief  Maximum Key Derive Job list len . **/
#define CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN 0x02U

#if (defined CRYPTO_XVIX_XAIX_RSAENCODE_HEADERSIZE)
#error CRYPTO_XVIX_XAIX_RSAENCODE_HEADERSIZE is already defined
#endif
/** \brief  Size of the array which will hold the sequence of RSA key material in DER format. **/
#define CRYPTO_XVIX_XAIX_RSAENCODE_HEADERSIZE 0x05U

/** \brief  Crypto stack key element CRYPTO_KE_SIGNATURE_CURVETYPE, which is not provided by Csm in ACG-8
**/
#ifndef CRYPTO_KE_SIGNATURE_CURVETYPE
    #define CRYPTO_KE_SIGNATURE_CURVETYPE 0x001DU
#else
    #if CRYPTO_KE_SIGNATURE_CURVETYPE != 0x001DU
        #error Key element "CRYPTO_KE_SIGNATURE_CURVETYPE" has an incorrect value. It should be 0x001DU
    #endif
#endif /* #ifndef CRYPTO_KE_SIGNATURE_CURVETYPE */

/*==================[type definitions]============================================================*/

/* forward typedefs */

/** \brief  Forward declaration of Crypto_xVIx_xAIx_CDOPrimitiveType.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOPrimitiveType/0001,1 */
typedef struct Crypto_xVIx_xAIx_CDOPrimitiveStruct Crypto_xVIx_xAIx_CDOPrimitiveType;

/* general, independent types */

#if (CPU_TYPE == CPU_TYPE_32)
  /** \brief  This type resembles the size type in relation to the system. **/
  typedef uint32 Crypto_xVIx_xAIx_SizeType;
#elif (CPU_TYPE == CPU_TYPE_64) /* #if (CPU_TYPE == CPU_TYPE_32) */
  /** \brief  This type resembles the size type in relation to the system. **/
  typedef uint64 Crypto_xVIx_xAIx_SizeType;
#else /* #if (CPU_TYPE == CPU_TYPE_32) */
  #error Unsupported CPU_TYPE
#endif /* #if (CPU_TYPE == CPU_TYPE_32) */

/** \brief  Type to indicate the type of callback **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CallbackType/0001,1 */
typedef uint8 Crypto_xVIx_xAIx_CallbackType;

/* function pointer data types */

/** \brief  The function pointer type that describes a function pointer to be used for referencing
 **         the standardized APIs provided by any implementation of a cryptographic primitive
 **         within the Crypto module.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType/0001,1 */
typedef P2FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_APPL_CODE, Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType)
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);

/** \brief  The function pointer type that describes a function pointer to be used for referencing
 **         the standardized callback API provided by any implementation of a cryptographic
 **         primitive within the Crypto module.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveApiCbkPtrType/0001,1 */
typedef P2FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_APPL_CODE, Crypto_xVIx_xAIx_PrimitiveApiCbkPtrType)
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);

/** \brief  The function pointer type that describes a function pointer to be used for referencing
 **         the action and transition functions the state machine that realizes a cryptographic
 **         primitive is composed of.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveStateFunctionType/0001,1 */
typedef P2FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_APPL_CODE, Crypto_xVIx_xAIx_PrimitiveStateFunctionType)
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);

/* data types related to Primitives */

/** \brief  The enumeration type that describes the possible states of a state machine that
 **         realizes a cryptographic primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveStateIdentifierType/0001,1 */
typedef uint8 Crypto_xVIx_xAIx_PrimitiveStateIdentifierType;

/** \brief  The structured data type that describes an entry of the cryptographic primitive state
 **         machine transition table.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveStateTransitionType/0001,1 */
typedef struct
{
  Crypto_xVIx_xAIx_PrimitiveStateFunctionType fcnTransition;

  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType nxtState;
  Crypto_ProcessingType                         processingType;
  uint8                                         event;
}
Crypto_xVIx_xAIx_PrimitiveStateTransitionType;

/** \brief  The structured data type that describes an entry of the cryptographic primitive state
 **         machine action table.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveStateActionType/0001,1 */
typedef struct
{
  Crypto_xVIx_xAIx_PrimitiveStateFunctionType fcnAction;
}
Crypto_xVIx_xAIx_PrimitiveStateActionType;

/** \brief  The structured data type that describes the basic representation of a cryptographic
 **         primitive.
 **         This description includes the identification of the cryptographic primitive by its
 **         service (<SRV>), family (<FAM>) and mode( <MOD>), as well as function pointers to
 **         standardized APIs provided by any implementation of a cryptographic primitive within
 **         a Crypto module.
 **         Instances of this data type are referenced by Crypto_xVIx_xAIx_CDOPrimitiveCnfgType.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_PrimitiveDescriptionType/0001,1 */
typedef struct
{
  CONST(Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType, CRYPTO_xVIx_xAIx_CONST) fcnMain;
  CONST(Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType, CRYPTO_xVIx_xAIx_CONST) fcnProcess;
  CONST(Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType, CRYPTO_xVIx_xAIx_CONST) fcnCancel;
  CONST(Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType, CRYPTO_xVIx_xAIx_CONST) fcnReset;
  CONST(Crypto_xVIx_xAIx_PrimitiveApiFcnPtrType, CRYPTO_xVIx_xAIx_CONST) fcnRestart;
  CONST(Crypto_xVIx_xAIx_PrimitiveApiCbkPtrType, CRYPTO_xVIx_xAIx_CONST) fcnCallback;

  CONST(Crypto_ServiceInfoType,     CRYPTO_xVIx_xAIx_CONST) service;
  CONST(Crypto_AlgorithmFamilyType, CRYPTO_xVIx_xAIx_CONST) family;
  CONST(Crypto_AlgorithmModeType,   CRYPTO_xVIx_xAIx_CONST) mode;
}
Crypto_xVIx_xAIx_PrimitiveDescriptionType;

/** \brief  This description includes non-constant definition Crypto_PrimitiveInfoType
 **         to be used in the computations regarding secondary job.
 **/
typedef struct
{
  uint32                   resultLength;
  Crypto_ServiceInfoType   service;
  Crypto_AlgorithmInfoType algorithm;
}
Crypto_xVIx_xAIx_NonConstPrimitiveInfoType;

/* data types related specific to a single Crypto Driver Object */

/** \brief  The structured data type that describes the constant part of the representation of a
 **         cryptographic primitive as used by a CDO.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOPrimitiveCnfgType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) description;
    CONSTP2VAR(void,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) workspace;
         CONST(uint32,                                               CRYPTO_xVIx_xAIx_CONST) workspaceSize;
    CONSTP2VAR(void,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) heap;
         CONST(uint16,                                               CRYPTO_xVIx_xAIx_CONST) heapSize;
}
Crypto_xVIx_xAIx_CDOPrimitiveCnfgType;

/** \brief  The structured data type that describes the run-time variable part of the representation
 **         of a cryptographic primitive as used by a CDO.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOPrimitiveDataType/0001,1 */
typedef struct
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) P1;
}
Crypto_xVIx_xAIx_CDOPrimitiveDataType;

/** \brief  The structured data type that describes an extended representation of a cryptographic
 **         primitive as used by a CDO.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOPrimitiveType/0001,1 */
struct Crypto_xVIx_xAIx_CDOPrimitiveStruct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
  CONSTP2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,     AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) P2;
  CONSTP2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,     AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) R1;
};

/* data types generally related to Crypto Driver Object */

/** \brief  Different states a Crypto Driver Object can have.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOStateType/0001,1 */
typedef uint8 Crypto_xVIx_xAIx_CDOStateType;

/** \brief  The structured data type that describes the constant part of the execution context of
 **         a crypto driver object.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOCnfgType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) primitiveList;
         CONST(uint32,                                       CRYPTO_xVIx_xAIx_CONST) primitiveListLength;
         CONST(boolean,                                      CRYPTO_xVIx_xAIx_CONST) useForKMn;
         CONST(uint32,                                       CRYPTO_xVIx_xAIx_CONST) defaultRandomKeyId;
}
Crypto_xVIx_xAIx_CDOCnfgType;

/** \brief  The structured data type that describes the run-time variable part of the execution
 **         context of a crypto driver object.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDODataType/0001,1 */
typedef struct
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitiveCurrent;
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobCurrent;

  Crypto_xVIx_xAIx_CDOStateType state;

  boolean jobCurrentIsProcessed;
  boolean jobCurrentSecondaryIsProcessed;
  boolean jobCurrentDefaultRandomIsProcessed;
}
Crypto_xVIx_xAIx_CDODataType;

/** \brief  The structured data type that describes the execution context of a crypto driver object.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CDOType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_CDOCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_CDODataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
}
Crypto_xVIx_xAIx_CDOType;

/* date types related to Crypto Keys */

/** \brief  The enumeration data type that describes whether a crypto key is invalid or valid.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyStateType/0001,1 */
typedef uint8 Crypto_xVIx_xAIx_KeyStateType;

/** \brief  The structured data type that describes the basic representation of a key element.
 **         This description includes the description of the meaning of the key element, as well as its size, etc.
 **         Instances of this data type are referenced by Crypto_xVIx_xAIx_KeyElementCnfgType.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyElementDescriptionType/0001,1 */
typedef struct
{
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) id;
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) maxSize;

  CONSTP2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) initValue;

  CONST(uint8, CRYPTO_xVIx_xAIx_CONST) readAccess;
  CONST(uint8, CRYPTO_xVIx_xAIx_CONST) writeAccess;

  CONST(boolean, CRYPTO_xVIx_xAIx_CONST) allowPartialAccess;
  CONST(boolean, CRYPTO_xVIx_xAIx_CONST) persistent;

  VAR(uint8, CRYPTO_xVIx_xAIx_CONST) format;
}
Crypto_xVIx_xAIx_KeyElementDescriptionType;

/** \brief  The structured data type that describes the constant part of a crypto key element.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyElementCnfgType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyElementDescriptionType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) description;
}
Crypto_xVIx_xAIx_KeyElementCnfgType;

/** \brief  The structured data type that describes the run-time variable part of a crypto key
 **         element.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyElementDataType/0001,1 */
typedef struct
{
  uint32 size;
  uint32 readLock;

  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) data;

  boolean writeLock;
}
Crypto_xVIx_xAIx_KeyElementDataType;

/** \brief  The structured data type that describes a crypto key element.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyElementType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyElementCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_KeyElementDataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
}
Crypto_xVIx_xAIx_KeyElementType;

/** \brief  The structured data type that describes the constant part of a crypto key.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyCnfgType/0001,1 */
typedef struct
{
         CONST(uint32,                                     CRYPTO_xVIx_xAIx_CONST) keyDeriveIterations;
         CONST(uint32,                                     CRYPTO_xVIx_xAIx_CONST) keyElementsCount;
         CONST(uint32,                                     CRYPTO_xVIx_xAIx_CONST) persistentKeyElementsCount;
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) keyElements;
}
Crypto_xVIx_xAIx_KeyCnfgType;

/** \brief  The structured data type that describes the run-time variable part of the of a crypto
 **         key.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyDataType/0001,1 */
typedef struct
{
  Crypto_xVIx_xAIx_KeyStateType keyState;
}
Crypto_xVIx_xAIx_KeyDataType;

/** \brief  The structured data type that describes a crypto key.
 **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_KeyDataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
}
Crypto_xVIx_xAIx_KeyType;

/** \brief  The function pointer type that describes KDF Process Function.
 **/
typedef P2FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_APPL_CODE, Crypto_xVIx_xAIx_KDFPrimitivesFcnPtrType)
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
        uint32                                                 jobsLength,
  P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
        uint32                                                 wkspDataLen,
        uint32                                                 cryptoKeyId,
        uint32                                                 targetCryptoKeyId
);

/** \brief  The structured data type that describes KDF primtive index and primitive output len.
 **/
typedef struct
{
  uint8  primitiveIndex;
  uint32 primitiveOutputLength;
}
Crypto_xVIx_xAIx_KDFPrimitiveJobInfo_Type;

/** \brief  The structured data type that describes KDF configure data for Kmn Interface.
 **/
typedef struct
{
  Crypto_xVIx_xAIx_KDFPrimitiveJobInfo_Type keyDeriveJobs[CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN];
  uint8                                     keyDeriveJobsLength;
  uint8                                     keyDeriveProcessJobsIndex;
}
Crypto_xVIx_xAIx_KDFPrimitivesConfig_Type;

/** \brief  The structured data type that describes RSA key element information of DER type for Kmn Interface.
 **/
typedef struct
{
  uint8  header[CRYPTO_XVIX_XAIX_RSAENCODE_HEADERSIZE];
  uint8  header_length;
  uint8  sign_length;
  uint16 data_length;
  uint16 der_length;
}
Crypto_xVIx_xAIx_RsaKeyElementInfo_Type;

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_TYPES_H */

/*==================[end of file]=================================================================*/

