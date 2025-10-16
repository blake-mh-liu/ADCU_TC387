#ifndef EA_CFG_H
#define EA_CFG_H
/**
 * \file
 *
 * \brief AUTOSAR Ea
 *
 * This file contains the implementation of the AUTOSAR
 * module Ea.
 *
 * \version 5.12.23
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[includes]==============================================*/
/* !LINKSTO Ea.SWS_Ea_00083,1, Ea.ASR40.SWS_Ea_00113,1  */
#include <MemIf_Types.h>         /* Memory Abstraction Interface Types */
[!IF "((node:exists(EaGeneral/EaMemAccUsage)) and (node:existsAndTrue(EaGeneral/EaMemAccUsage)))"!][!//
#include <MemAcc.h>
[!ELSE!][!//
#include <Eep.h>                 /* EEPROM Header */
[!ENDIF!]
[!IF "((node:exists(EaGeneral/EaNvmJobErrorNotification)) and
(EaGeneral/EaNvmJobErrorNotification != '') and (EaGeneral/EaNvmJobErrorNotification != 'NULL_PTR'))
or ((node:exists(EaGeneral/EaNvmJobEndNotification)) and 
(EaGeneral/EaNvmJobEndNotification != '') and (EaGeneral/EaNvmJobEndNotification != 'NULL_PTR'))"!]
#include <NvM_Cbk.h>            /* NVRAM Manager callback API */
[!ENDIF!]
/*==================[macros]================================================*/
/* !LINKSTO Ea.ECUC_Ea_00120,1 */
#if (defined EA_DEV_ERROR_DETECT)
#error EA_DEV_ERROR_DETECT is already defined
#endif
/** \brief Flag to en/disable development error detection for the Ea */
#define EA_DEV_ERROR_DETECT      [!//
[!IF "node:existsAndTrue(EaGeneral/EaDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined EA_VERSION_INFO_API)
#error EA_VERSION_INFO_API is already defined
#endif
/** \brief Provide API function Ea_GetVersionInfo() */
#define EA_VERSION_INFO_API      [!//
[!IF "node:existsAndTrue(EaGeneral/EaVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined EA_POLLING_MODE)
#error EA_POLLING_MODE is already defined
#endif
/** \brief Indicates if polling is enabled or not. */
#define EA_POLLING_MODE          [!//
[!IF "node:existsAndTrue(EaGeneral/EaPollingMode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined EA_VIRTUAL_PAGE_SIZE)
#error EA_VIRTUAL_PAGE_SIZE is already defined
#endif
/** \brief size of virtual page in bytes. */
#define EA_VIRTUAL_PAGE_SIZE     [!"EaGeneral/EaVirtualPageSize"!]U

/** \brief Precompiler switch to support new ASR21-11 module MemAcc
 **
 ** Precompiler switch to support new ASR21-11 module MemAcc. */
#if (defined EA_USE_MEMACC)
#error EA_USE_MEMACC is already defined
#endif
[!IF "(node:exists(EaGeneral/EaMemAccUsage) and (node:existsAndTrue(EaGeneral/EaMemAccUsage)))"!][!//
#define EA_USE_MEMACC                    STD_ON
[!ELSE!]
#define EA_USE_MEMACC                    STD_OFF
[!ENDIF!]

[!//
[!IF "(node:exists(EaGeneral/EaMemAccUsage) and (node:existsAndTrue(EaGeneral/EaMemAccUsage)))"!][!//
#define EA_ALIGNMENT_VALUE [!"node:value(node:ref(EaGeneral/EaBufferAlignmentValue)/MemAccBufferAlignmentValue)"!]U
[!ELSE!]
#define EA_ALIGNMENT_VALUE 1U
[!ENDIF!]

#if (defined EA_SET_MODE_SUPPORTED)
#error EA_SET_MODE_SUPPORTED is already defined
#endif
/** \brief Indicates if Ea_SetMode() is enabled or not. */
#define EA_SET_MODE_SUPPORTED    [!//
[!IF "node:existsAndTrue(EaGeneral/EaSetModeSupported)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!NOCODE!][!//
--- Get general configuration parameters
[!VAR "thisVirtualPageSize" = "EaGeneral/EaVirtualPageSize"!]
---  Generate internal buffer size
[!IF "node:exists(EaGeneral/EaBuffer) and (num:i(EaGeneral/EaBuffer) >= num:i(2*$thisVirtualPageSize))"!]
  [!VAR "thisTempBufferLength" = "num:i(EaGeneral/EaBuffer)"!]
[!ELSE!]
  [!VAR "thisTempBufferLength" = "num:i(2*$thisVirtualPageSize)"!]
[!ENDIF!]
--- Minimum buffer size is: 2 * 1 Byte (VLEC) + 1 Byte (IF) = 3 Byte
[!IF "$thisTempBufferLength < 3"!]
  [!VAR "thisTempBufferLength" = "num:i(3)"!]
[!ENDIF!]
[!ENDNOCODE!][!//

#if (defined EA_TEMPBUFFER_LENGTH)
#error EA_TEMPBUFFER_LENGTH is already defined
#endif
/** \brief Temporary buffer length */
#define EA_TEMPBUFFER_LENGTH     [!"$thisTempBufferLength"!]U

#if (defined EA_NUMBEROFBLOCKS)
#error EA_NUMBEROFBLOCKS is already defined
#endif
/** \brief Number of blocks configured. */
#define EA_NUMBEROFBLOCKS        [!"num:i(count(EaBlockConfiguration/eb-list::*))"!]U

#if (defined EA_LOWERLAYER_ERASE_VALUE)
#error EA_LOWERLAYER_ERASE_VALUE is already defined
#endif
/** \brief Erase pattern as published by the Eep driver */
[!IF "(node:exists(EaGeneral/EaMemAccUsage) and (node:existsAndTrue(EaGeneral/EaMemAccUsage)))"!][!//
#define EA_LOWERLAYER_ERASE_VALUE  [!"EaGeneral/EaDriverErasedValue"!]U
[!ELSE!]
#define EA_LOWERLAYER_ERASE_VALUE  [!"as:modconf('Eep')[1]/EepPublishedInformation/EepEraseValue"!]U
[!ENDIF!]

/* -----------[Lower Layer function Adaptation]-------------- */
[!IF "(node:exists(EaGeneral/EaMemAccUsage) and (node:existsAndTrue(EaGeneral/EaMemAccUsage)))"!][!//

/* !LINKSTO Ea.EaMemAccUsage.ApiCompliance,1 */
#define EA_MEMACC_AREA_ID [!"node:value(node:ref(EaGeneral/EaBufferAlignmentValue)/MemAccAddressAreaId)"!]U

#define Ea_LowerLayer_Write(a,b,c) MemAcc_Write(EA_MEMACC_AREA_ID, (a), (b), (c))
#define Ea_LowerLayer_Read(a,b,c) MemAcc_Read(EA_MEMACC_AREA_ID, (a), (b), (c))
#define Ea_LowerLayer_GetJobResult() Ea_MemAcc_GetConsolidatedJobResult()
#define Ea_LowerLayer_GetStatus() MemAcc_GetJobStatus(EA_MEMACC_AREA_ID)
#define Ea_LowerLayer_Cancel() MemAcc_Cancel(EA_MEMACC_AREA_ID)
#define Ea_LowerLayer_Erase(a,b) MemAcc_Erase(EA_MEMACC_AREA_ID, (a), (b))
/*data types*/
typedef MemAcc_AddressType Ea_LowerLayer_AddressType;
typedef MemAcc_LengthType Ea_LowerLayer_LengthType;
[!ELSE!]
#define Ea_LowerLayer_Write(a,b,c) Eep_Write((a), (b), (c))
#define Ea_LowerLayer_Read(a,b,c) Eep_Read( (a), (b), (c))
#define Ea_LowerLayer_GetJobResult() Eep_GetJobResult()
#define Ea_LowerLayer_GetStatus() Eep_GetJobStatus()
#define Ea_LowerLayer_Cancel() Eep_Cancel()
#define Ea_LowerLayer_Erase(a,b) Eep_Erase( (a), (b))
/*data types*/
typedef Eep_AddressType Ea_LowerLayer_AddressType;
typedef Eep_LengthType Ea_LowerLayer_LengthType;
[!ENDIF!]
/* -----------[Callback function names to upper layer module]-------------- */

#if (defined EA_JOB_END_NFY_CBK)
#error EA_JOB_END_NFY_CBK is already defined
#endif
/** \brief Callback function in upper layer to indicate successful job
 * completion. */
#define EA_JOB_END_NFY_CBK()     [!//
[!IF "node:exists(EaGeneral/EaNvmJobEndNotification) and
(EaGeneral/EaNvmJobEndNotification != '') and (EaGeneral/EaNvmJobEndNotification != 'NULL_PTR')"!][!//
[!"EaGeneral/EaNvmJobEndNotification"!]()[!ELSE!]do {} while (0)[!ENDIF!]

#if (defined EA_JOB_ERROR_NTY_CBK)
#error EA_JOB_ERROR_NTY_CBK is already defined
#endif
/** \brief Callback function in upper layer to indicate unsuccessful job
 * completion. */
#define EA_JOB_ERROR_NTY_CBK()   [!//
[!IF "node:exists(EaGeneral/EaNvmJobErrorNotification) and
(EaGeneral/EaNvmJobErrorNotification != '') and (EaGeneral/EaNvmJobErrorNotification != 'NULL_PTR')"!][!//
[!"EaGeneral/EaNvmJobErrorNotification"!]()[!ELSE!]do {} while (0)[!ENDIF!]

/* -----------[Symbolic names for the Ea blocks]--------------------------- */

[!LOOP "EaBlockConfiguration/eb-list::*"!][!//
#if (defined EaConf_EaBlockConfiguration_[!"as:name(.)"!])
#error EaConf_EaBlockConfiguration_[!"as:name(.)"!] is already defined
#endif
/** \brief Symbolic name for the Ea Block Number [!"EaBlockNumber"!] */
#define EaConf_EaBlockConfiguration_[!"as:name(.)"!]   [!"EaBlockNumber"!]U

#ifndef EA_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#if (defined [!"as:name(.)"!])
#error [!"as:name(.)"!] is already defined
#endif
#define [!"as:name(.)"!]   [!"EaBlockNumber"!]U
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#if (defined Ea_[!"as:name(.)"!])
#error Ea_[!"as:name(.)"!] is already defined
#endif
#define Ea_[!"as:name(.)"!] [!"EaBlockNumber"!]U
#endif /* ifndef EA_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef EA_CFG_H */
/*==================[end of file]===========================================*/
