/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

#ifndef CANTSYN_INT_CFG_H
#define CANTSYN_INT_CFG_H

/*==================[inclusions]============================================*/
[!INCLUDE "CanTSyn_PrecompileMacros.m"!][!//
[!CALL "isIcvGenerationSupported"!][!//
[!CALL "isIcvVerificationSupported"!][!//
#include <CanTSyn_Int_Stc.h>     /* multicore types */

[!IF "($isIcvGenerationSupported = 'true') or ($isIcvVerificationSupported = 'true')"!]
#include <StbM.h>
#include <Csm.h>
[!ENDIF!]
/*==================[macros]================================================*/
[!IF "$isMulticoreEnabled = 'true'"!]

[!CALL "numberOfEcuCPartitionsUsedByCanTSyn"!]
#if (defined CANTSYN_NUMBER_OF_PARTITIONS)
#error CANTSYN_NUMBER_OF_PARTITIONS is already defined.
#endif
/** \brief Total number of partitions */
#define CANTSYN_NUMBER_OF_PARTITIONS  [!"num:i($numberOfEcuCPartitionsUsedByCanTSyn)"!]U

[!CALL "isOnlyTimeDomainMFAllocUsed"!]
#if (defined CANTSYN_ISONLY_TIMEDOMAINMFALLOC_USED)
#error CANTSYN_ISONLY_TIMEDOMAINMFALLOC_USED is already defined.
#endif
/** \brief Checks if only time domain MF allocation is used or not */
#define CANTSYN_ISONLY_TIMEDOMAINMFALLOC_USED  STD_[!IF "$isOnlyTimeDomainMFAllocUsed = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

[!ELSE!]

#if (defined CANTSYN_NUMBER_OF_PARTITIONS)
#error CANTSYN_NUMBER_OF_PARTITIONS is already defined.
#endif
/** \brief Dummy number of partitions */
#define CANTSYN_NUMBER_OF_PARTITIONS  255U

[!ENDIF!]
#if (defined CANTSYN_MAX_TRANSMIT_RETRIES)
#error CANTSYN_MAX_TRANSMIT_RETRIES is already defined.
#endif
/** \brief Transmit retries support */
#define CANTSYN_MAX_TRANSMIT_RETRIES  STD_[!IF "(node:exists(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMaxNumberOfTransmitRetries)) and (node:value(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMaxNumberOfTransmitRetries) > '0')"!]ON[!ELSE!]OFF[!ENDIF!]

[!IF "node:exists(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMaxNumberOfTransmitRetries)"!]
#if (defined CANTSYN_MAX_NUMBER_OF_TRANSMIT_RETRIES)
#error CANTSYN_MAX_NUMBER_OF_TRANSMIT_RETRIES is already defined.
#endif
/** \brief Max number of transmit retries */
#define CANTSYN_MAX_NUMBER_OF_TRANSMIT_RETRIES  [!"num:i(node:value(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMaxNumberOfTransmitRetries))"!]U
[!ENDIF!]

/* !LINKSTO CanTSyn.ASR22-11.SWS_CanTSyn_00205,1 */

[!IF "($isIcvGenerationSupported = 'true') or ($isIcvVerificationSupported = 'true')"!]

#if (defined CANTSYN_FRESHNESS_MAX_LENGTH)
#error CANTSYN_FRESHNESS_MAX_LENGTH is already defined
#endif /* if (defined CANTSYN_FRESHNESS_MAX_LENGTH) */

/** \brief Max possible size for array holding freshness value.  */
#define CANTSYN_FRESHNESS_MAX_LENGTH  8U 

[!ENDIF!]

/* ----- defensive programming macros ----- */ 



/*------------------[Defensive programming]---------------------------------*/
[!SELECT "CanTSynDefensiveProgramming"!][!//

#if (defined CANTSYN_DEFENSIVE_PROGRAMMING_ENABLED)
#error CANTSYN_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define CANTSYN_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANTSYN_PRECONDITION_ASSERT_ENABLED)
#error CANTSYN_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define CANTSYN_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true') and (CanTSynPrecondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANTSYN_POSTCONDITION_ASSERT_ENABLED)
#error CANTSYN_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define CANTSYN_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true') and (CanTSynPostcondAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED)
#error CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true') and (CanTSynUnreachAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANTSYN_INVARIANT_ASSERT_ENABLED)
#error CANTSYN_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define CANTSYN_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true') and (CanTSynInvariantAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANTSYN_STATIC_ASSERT_ENABLED)
#error CANTSYN_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define CANTSYN_STATIC_ASSERT_ENABLED           [!//
[!IF "(../CanTSynGeneral/CanTSynDevErrorDetect  = 'true') and (CanTSynDefProgEnabled = 'true') and (CanTSynStaticAssertEnabled = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


/*==================[type definitions]======================================*/

[!CALL "isFvUsedInIcvGeneration"!]
[!CALL "isFvUsedInIcvVerification"!]

[!IF "$isIcvGenerationSupported = 'true'"!]
/** \brief Defines the type of CanTSyn master shared variables used for ICV generation. */
typedef struct
{
  VAR(uint32, TYPEDEF) ComputedIcvLength;  /* Pointer location where Csm will store the computed ICV length */
[!IF "$isFvUsedInIcvGeneration = 'true'"!]
  VAR(uint32, TYPEDEF) IcvGenerationFvLength; /* Length of freshness value */
  VAR(uint32, TYPEDEF) IcvGenerationFvTruncLength; /* Truncated length of freshness value */
[!ENDIF!]
  VAR(uint16, TYPEDEF) IcvGenerationTimeout; /* Time to wait for ICV generation. */
  VAR(uint8, TYPEDEF) IcvGenerationState; /* Flag to check the ICV generation progress. */
  VAR(uint8, TYPEDEF) TruncatedFv[CANTSYN_FRESHNESS_MAX_LENGTH]; /* Used to store the truncated freshness value for async ICV generation */
}CanTSyn_IcvMasterType;
[!ENDIF!]

[!IF "$isIcvVerificationSupported = 'true'"!]
/** \brief Defines the type of CanTSyn slave shared variables used for ICV verification. */
typedef struct
{
  VAR(StbM_VirtualLocalTimeType, TYPEDEF) T5VLT; /* T5 virtual local time */
[!IF "$isFvUsedInIcvVerification = 'true'"!]
  VAR(uint32, TYPEDEF) IcvVerificationFvLength; /* Length of freshness value */
  VAR(uint32, TYPEDEF) IcvVerificationFvTruncLength; /* Truncated length of freshness value */
[!ENDIF!]
  VAR(uint16, TYPEDEF) IcvVerificationAttempts; /* Number of ICV verification attempts that are to be carried out when the verification of the ICV failed */
  VAR(uint16, TYPEDEF) IcvVerificationTimeout; /* Time to wait for ICV verification. */
  VAR(uint8, TYPEDEF) IcvVerificationState; /* used for the state machine of auth message processing */
  VAR(Crypto_VerifyResultType, TYPEDEF) IcvVerificationResult; /* used to store the result of Csm_MacVerify or Csm_SignatureVerify */
  VAR(boolean, TYPEDEF) IcvFvRecovError;
}CanTSyn_IcvSlaveType;
[!ENDIF!]

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define CANTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

[!IF "$isMulticoreEnabled = 'true'"!]
[!CALL "CreatePartitionRefList"!]
[!VAR "lastPartitionRef"!][!ENDVAR!][!//
[!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
[!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
  [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
  [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
    [!IF "not($lastPartitionRef = $ecucPartitionRefName)"!][!//
    [!CALL "GetNumberOfConnectedTimeDomains", "ecuCPartitionName" = "$ecucPartitionRefName"!][!//
/** \brief Function pointer list of all time domains which are connected to [!"$ecucPartitionRefName"!] partition */
extern CONST(uint16, CANTSYN_APPL_CONST) CanTSyn_[!"$ecucPartitionRefName"!]_TimeDomainsList[[!"num:i($connectedTimeDomainCounter)"!]];
    [!ENDIF!][!//
    [!VAR "lastPartitionRef" = "$ecucPartitionRefName"!][!//
[!ENDFOR!][!//

[!IF "$isMulticoreEnabled = 'true'"!]
[!IF "$isOnlyTimeDomainMFAllocUsed = 'false'"!][!//
  [!VAR "partitionRefName" = "concat('EcucPartition_',num:i($numberOfEcuCPartitionsUsedByCanTSyn - 1))"!][!//
  [!CALL "GetNumberOfTimeDomainsNotConnectedToAnyPartition"!][!//
/** \brief Function pointer list of all time domains which are not connected to any partition */
extern CONST(uint16, CANTSYN_APPL_CONST) CanTSyn_[!"$partitionRefName"!]_TimeDomainsList[[!"num:i($notConnectedTimeDomainCounter)"!]];
[!ENDIF!][!//

[!CALL "numberOfEcuCPartitionsUsedByCanTSyn"!][!//
/** \brief Array of structures which contain information related to each partition which is connected to CanTSyn time domains */
extern CONST(CanTSyn_PartitionCfgType, CANTSYN_APPL_CONST) CanTSyn_PartitionTimeDomainsList[[!"num:i($numberOfEcuCPartitionsUsedByCanTSyn)"!]];
[!ENDIF!][!//
[!ENDIF!]

#define CANTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define CANTSYN_START_SEC_CODE
#include <CanTSyn_MemMap.h>

/** \brief CanTSyn Rx main function
 **
 ** Processes TimeSlavePdus decoupled from the reception events
 **
 ** This function has to be called periodically by the BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction_Rx(uint8 partitionIdx);


/** \brief CanTSyn Tx main function
 **
 ** Processes TimeMasterPdus decoupled from the transmit confirmation events
 **
 ** This function has to be called by the BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction_Tx(uint8 partitionIdx);

#define CANTSYN_STOP_SEC_CODE
#include <CanTSyn_MemMap.h>


[!IF "$isMulticoreEnabled = 'true'"!]
[!CALL "createSlaveTimeDomainMFAlloc"!]
[!LOOP "text:split($createSlaveTimeDomainMFAlloc,';')"!]
  [!VAR "qName" = "text:split(.,':')[1]"!]
  [!VAR "partitionName" = "text:split(.,':')[2]"!]
  [!VAR "qName" = "concat('CanTSyn_', $MulticoreVendorID, '_', $partitionName, $qName)"!]
  
#ifndef RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]
#define RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_START_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

/** \brief CanTSyn Rx main function
 **
 ** Processes decoupled RxPdus
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_CODE) [!"$qName"!](void);

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

#endif /* RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!] */
[!ENDLOOP!][!//Rx


[!CALL "createMasterTimeDomainMFAlloc"!]
[!LOOP "text:split($createMasterTimeDomainMFAlloc,';')"!]
  [!VAR "qName" = "text:split(.,':')[1]"!]
  [!VAR "partitionName" = "text:split(.,':')[2]"!]
  [!VAR "qName" = "concat('CanTSyn_', $MulticoreVendorID, '_', $partitionName, $qName)"!]

#ifndef RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]
#define RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_START_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

/** \brief CanTSyn Tx main function
 **
 ** Performs the processes of the activities that are not directly initiated by
 ** the calls from CAN driver.
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_CODE) [!"$qName"!](void);
#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

#endif /* RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!] */
[!ENDLOOP!][!//Tx
[!ENDIF!]



/*==================[internal function definitions]=========================*/
#endif /* ifndef CANTSYN_INT_CFG_H */
/*==================[end of file]============================================*/
[!ENDCODE!][!//

