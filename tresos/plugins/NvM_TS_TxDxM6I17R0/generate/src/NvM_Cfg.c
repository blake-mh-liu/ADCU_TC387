/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \version 6.17.36
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!INCLUDE "../include/NvM_Include.m"!][!//
[!IF "(count(as:modconf('NvM')[1]/NvMCommon/NvMEcucPartitionRef/eb-list::*) > 1)"!][!//
  [!VAR "PartitionsCallbacksPacked" = "'='"!][!//
  [!LOOP "as:modconf('NvM')[1]/NvMCommon/NvMEcucPartitionRef/eb-list::*"!][!//
    [!VAR "SatellitePartitionName" = "substring-after((.),'EcucPartitionCollection/')"!][!/*
    === callbacks counters are initialized in a packed xml like format using tags: 
       - each set of callbacks counters starts and ends with the partition name tag;
       - each counter starts and ends with a short name of the callback as tags;
       - =,+,- tags are used because the postion() function can't work with index 0, because of a misfortunate language issue	   ==    
    */!][!VAR "PartitionsCallbacksPacked" = "concat($PartitionsCallbacksPacked,$SatellitePartitionName,'+-Init-0-Init--Single-0-Single--Read-0-Read--Write-0-Write-+',$SatellitePartitionName)"!][!//
  [!ENDLOOP!][!//
  [!VAR "PartitionsCallbacksPacked" = "concat($PartitionsCallbacksPacked,'=')"!][!//
  [!VAR "BswDistributionEnabled" = "'true'"!][!//
[!ELSE!][!//
  [!VAR "BswDistributionEnabled" = "'false'"!][!//
[!ENDIF!][!//
[!MACRO "GetCallbackIndex", "PartitionName", "CallbackType"!][!/*
    === each time a counter needs to be incremented, the xml like string is unpacked, first by partition name, and then by the proper callback type;
	the value is taken and incremented and afterwards the string is rebuilt with the new value, but keeping all the other callback values unchanged ==    
    */!][!INDENT "0"!][!//
  [!VAR "PartitionStartTag" = "text:split($PartitionsCallbacksPacked,$PartitionName)[position() = 1]"!][!//
  [!VAR "PackedCallbacksIdxs" = "text:split($PartitionsCallbacksPacked,$PartitionName)[position() = 2]"!][!//
  [!VAR "PartitionEndTag" = "text:split($PartitionsCallbacksPacked,$PartitionName)[position() = 3]"!][!//
  [!VAR "CallbackStartTag" = "text:split($PackedCallbacksIdxs,$CallbackType)[position() = 1]"!][!//
  [!VAR "CallbackIndexText" = "text:split($PackedCallbacksIdxs,$CallbackType)[position() = 2]"!][!//
  [!VAR "CallbackIndex" = "num:integer($CallbackIndexText)"!][!//
  [!VAR "CallbackIndexIncremented" = "num:integer($CallbackIndex + 1)"!][!//
  [!VAR "CallbackEndTag" = "text:split($PackedCallbacksIdxs,$CallbackType)[position() = 3]"!][!//
  [!VAR "PartitionsCallbacksPacked" = "concat($PartitionStartTag,$PartitionName,$CallbackStartTag,$CallbackType,$CallbackIndexIncremented,$CallbackType,$CallbackEndTag,$PartitionName,$PartitionEndTag)"!][!//
  [!"$CallbackIndex"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule 11.1 (Required):
 *    Conversions shall not be performed between a pointer to a function and any other type.
 *
 *    Reason: The conversion is done to exactly the configured version of callback.
 *
 *  MISRAC2012-2) Deviated Rule: 20.10 (advisory)
 *           "The # and ## preprocessor operators should not be used."
 *
 *           Reason:
 *           Concatenation(##) operator is used by pre compile time parameter. It doesn't
 *           have any negative impact on code.
 *
 */

/*==================[inclusions]=============================================*/
#if (defined NVM_INTERNAL_USE)
#error NVM_INTERNAL_USE already defined
#endif
/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE

#include <TSAutosar.h>

#include <NvM.h>
#include <NvM_FunctionIntern.h> /* for initialization of NvM_CalcCrc */
#include <NvM_DataIntern.h>   /* extern definition of NvM_ConfigurationId */
#include <NvM_CalcCrc.h>      /* Extern definitions of unit 'CalcCrc'. */

#if (NVM_INCLUDE_RTE == STD_ON)
# include <Rte_NvM.h>
# include <Rte_NvMData.h>
[!IF "$BswDistributionEnabled = 'true'"!][!//
#include <SchM_NvM.h>
[!LOOP "as:modconf('NvM')[1]/NvMCommon/NvMEcucPartitionRef/eb-list::*"!][!/*
  */!][!IF "as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef != (.)"!][!/*
    */!][!VAR "PartitionName" = "substring-after(name(),'EcucPartitionCollection/')"!][!/*
*/!]#include <NvM_[!"$PartitionName"!]_Lcfg.h>
[!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!ENDIF!]
#endif

/*==================[macros]================================================*/

[!IF "count(NvMBlockDescriptor/eb-list::*[NvMNvramBlockIdentifier > 1 and node:existsAndTrue(NvMExtraBlockChecks)]) > 0"!][!//
#if (defined NVM_JOIN)
#error NVM_JOIN is already defined
#endif
/** \brief Concatenate the arguments X and Y after they are expanded by the
 ** preprocessor.
 **
 ** These are just helper macros used in the definition of NVM_ASSERT_STC().
 **/
#define NVM_JOIN(X,Y)  NVM_JOIN1(X,Y)

#if (defined NVM_JOIN1)
#error NVM_JOIN1 is already defined
#endif
/* Deviation MISRAC2012-2 */
#define NVM_JOIN1(X,Y) X##Y

/** \brief Check static assertion at compile time
 **
 ** \param expr logical expression to be evaluated at compile time
 **
 ** If \a expr evaluates to FALSE the compiler will abort with an error
 ** because array with a negative number of elements are forbidden in C.  If
 ** \a expr is TRUE the macro expands to a legal typedef.
 **
 ** The usage of this macro does \e not lead to additional resource usage in
 ** the resulting binary code.
 **
 ** The macro should be used were preprocessor #if directives cannot evaluate
 ** expressions but where these expressions can still be evaluated before
 ** runtime. E.g. expressions containig sizeof() functions used on types may
 ** be checked: NVM_ASSERT_STC(sizeof(Mod_SomeType) < 16U)
 **
 ** \note Macro may only be used at places in the code where typedefs are
 ** allowed.
 **/

#if (defined NVM_ASSERT_STC)
#error NVM_ASSERT_STC is already defined
#endif
/* Deviation MISRAC2012-2 <+2> */
#define NVM_ASSERT_STC(expr)\
 typedef uint8 NVM_JOIN(AssertFailedInLine,__LINE__)[(expr)?1:-1]

[!LOOP "NvMBlockDescriptor/eb-list::*[NvMNvramBlockIdentifier > 0 and node:existsAndTrue(NvMExtraBlockChecks)]"!][!//
[!IF "(node:exists(NvMRamBlockDataAddress)) and (NvMRamBlockDataAddress != '')"!][!//
  [!IF "text:indexOf(node:value(NvMRamBlockDataAddress), '&') = 0"!][!//
    [!IF "((node:existsAndTrue(NvMBlockUseCrc)) and (node:exists(NvMBlockCrcType)) and (node:existsAndTrue(NvMUserProvidesSpaceForBlockAndCrc)) and (NvMBlockCrcType = 'NVM_CRC8'))"!][!//
      [!VAR "CRCSize" = "1"!][!//
    [!ELSEIF "((node:existsAndTrue(NvMBlockUseCrc)) and (node:exists(NvMBlockCrcType)) and (node:existsAndTrue(NvMUserProvidesSpaceForBlockAndCrc)) and (NvMBlockCrcType = 'NVM_CRC16'))"!][!//
      [!VAR "CRCSize" = "2"!][!//
    [!ELSEIF "((node:existsAndTrue(NvMBlockUseCrc)) and (node:exists(NvMBlockCrcType)) and (node:existsAndTrue(NvMUserProvidesSpaceForBlockAndCrc)) and (NvMBlockCrcType = 'NVM_CRC32'))"!][!//
      [!VAR "CRCSize" = "4"!][!//
    [!ELSE!][!//
      [!VAR "CRCSize" = "0"!][!//
    [!ENDIF!][!//
    /* BlockIdentifier: [!"NvMNvramBlockIdentifier"!] - RamBlockDataAddress: [!"NvMRamBlockDataAddress"!] */
    [!IF "$CRCSize = 0"!][!//
    /* Length = [!"NvMNvBlockLength"!]U (Block length) */
    [!ELSE!][!//
    /* Length = [!"NvMNvBlockLength"!]U (Block length) + [!"num:integer($CRCSize)"!]U (CRC length) = [!"num:integer(NvMNvBlockLength + $CRCSize)"!]U (Total length) */
    [!ENDIF!][!//
    NVM_ASSERT_STC([!"num:integer(NvMNvBlockLength + $CRCSize)"!]U == sizeof([!"text:replace(NvMRamBlockDataAddress,'^\&','')"!]));
  [!ELSE!][!//
    [!WARNING!]The block size check is only performed if configured value starts with "&". Please check the RAM block for [!"as:name(.)"!][!ENDWARNING!]
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "(node:exists(NvMRomBlockDataAddress)) and (NvMRomBlockDataAddress != '')"!][!//
  [!IF "text:indexOf(node:value(NvMRomBlockDataAddress), '&') = 0"!][!//
    /* BlockIdentifier: [!"NvMNvramBlockIdentifier"!] - RomBlockDataAddress: [!"NvMRomBlockDataAddress"!] */
    /* Length = [!"NvMNvBlockLength"!]U */
    NVM_ASSERT_STC([!"NvMNvBlockLength"!]U == sizeof([!"text:replace(NvMRomBlockDataAddress,'^\&','')"!]));
  [!ELSE!][!//
    [!WARNING!]The block size check is only performed if configured value starts with "&". Please check the ROM block for [!"as:name(.)"!][!ENDWARNING!]
  [!ENDIF!][!//
[!ENDIF!][!//

[!ENDLOOP!][!//

[!ENDIF!][!//

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/
[!IF "$BswDistributionEnabled = 'true'"!][!/*
*/!][!VAR "MasterPartition" = "as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef"!][!/*
*/!][!VAR "MasterPartitionName" = "substring-after($MasterPartition,'EcucPartitionCollection/')"!][!/*
*/!][!IF "($InitCallbackArraySize > 0)"!]

/* Deviation MISRAC2012-1 */
STATIC CONST(NvM_CallbackFctPtr,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_InitBlockCallbacks[[!"$InitCallbackArraySize"!]];
[!ENDIF!][!/*
*/!][!IF "($SingleCallbackArraySize > 0)"!]

/* Deviation MISRAC2012-1 */
STATIC CONST(NvM_CallbackFctPtr,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_SingleBlockCallbacks[[!"$SingleCallbackArraySize"!]];
[!ENDIF!][!/*
*/!][!IF "($ReadCallbackArraySize > 0)"!]

STATIC CONST(NvM_NvToRamCopyCallbackType,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_ReadBlockCallbacks[[!"$ReadCallbackArraySize"!]];
[!ENDIF!][!/*
*/!][!IF "($WriteCallbackArraySize > 0)"!]

STATIC CONST(NvM_RamToNvCopyCallbackType,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_WriteBlockCallbacks[[!"$WriteCallbackArraySize"!]];
[!ENDIF!][!/*
*/!][!ENDIF!]
/*==================[external constants]=====================================*/

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_START_SEC_CONFIG_DATA_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
#endif
/* !LINKSTO NvM.SWS_NvM_00138,1, NvM.SWS_NvM_00143,1, NvM.SWS_NvM_00443,1, NvM.SWS_NvM_00140,1 */
CONST(NvM_BlockDescriptorType,NVM_CONST) NvM_BlockDescriptorTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS]=
{
  /** \brief  block 0:  NvM internal block, used to manage multi block requests. */[!/*
   *   Configuration: Block 0 must not be configurable by the user.
   *   The following default values must be set automatically.
*/!]
  {
    NULL_PTR,    /* initBlockCallback */
    NULL_PTR,    /* singleBlockCallback */[!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseSyncMechanism))]) != 0"!][!/*
    */!]
    NULL_PTR,    /* readRamFromNvCallback */[!/*
    */!]
    NULL_PTR,    /* writeRamToNvCallback */[!/*
    */!][!ENDIF!]
    NULL_PTR,    /* romBlockDataAddress */
    NULL_PTR,    /* ramBlockDataAddress */
    0U,  /* blockDesc */
    0U,  /* nvBlockLength */
    0U,  /* BlockBaseNumber */
    0U,  /* nvBlockIdentifier*/
    0xFFFFU,  /* ramBlockCrcIndex */[!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCRCCompMechanism))]) != 0"!]
    0xFFFFU,  /* nvBlockCrcIndex */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMWriteVerification))]) != 0"!]
    0U,   /* verifyDataSize */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMPreWriteDataComp))]) != 0"!]
    0U,   /* preWriteDataCompDataSize */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "(count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMEnBlockCheck))]) != 0)"!]
    0U,  /* bcBlockIdx */[!/*
    */!][!ENDIF!]
    0U,  /* nvBlockNum */
    0U,  /* romBlockNum */[!/*
    */!][!IF "node:existsAndTrue(NvMCommon/NvMJobPrioritization)"!]
    0U,  /* blockJobPriority */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(NvMMaxNumOfWriteRetries > 0)]) != 0"!]
    0U,  /* writeRetryLimit */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(NvMBlockDescriptor/eb-list::*[(NvMMaxNumOfReadRetries > 0)]) != 0"!]
    0U,  /* readRetryLimit */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "node:existsAndTrue(NvMCommon/NvMCommonCryptoSecurityParameters/NvMEnableCryptoSecurityHooks)"!]
    0U  /* CryptoExtraInfoSize */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "(count(NvMCommon/NvMEcucPartitionRef/eb-list::*) > 1)"!]
    (uint8)[!"name(as:modconf('Os')[1]/OsApplication/eb-list::*[OsAppEcucPartitionRef = as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef])"!]  /* OsApplication symbolic name */[!/*
    */!][!ENDIF!]
  }[!/*
   */!][!VAR "CRCLength"="0"!][!/*
   */!][!VAR "NvCRCLength"="0"!][!/*
   */!][!VAR "BcBlkIdx"="0"!][!/*
   */!][!VAR "OsAppSymbolicName"="''"!][!/*
   */!][!VAR "PartitionSymbolicName"="''"!][!/*
   */!][!LOOP "util:distinct(node:order(NvMBlockDescriptor/eb-list::*, 'NvMNvramBlockIdentifier'))"!][!/*
    */!][!IF "$BswDistributionEnabled = 'true'"!][!/*
    */!][!VAR "CrtBlkPartitionRef"="NvMBlockEcucPartitionRef"!][!/*
    */!][!VAR "OsAppSymbolicName"="name(as:modconf('Os')[1]/OsApplication/eb-list::*[string(OsAppEcucPartitionRef) = $CrtBlkPartitionRef])"!][!/*
    */!][!VAR "PartitionSymbolicName"="substring-after($CrtBlkPartitionRef,'EcucPartitionCollection/')"!][!/*
    */!][!ENDIF!],

  /* NVM_BLOCK_[!"as:name(.)"!] */[!/*
   */!]
  {[!/*
    */!]
    [!IF "$BswDistributionEnabled = 'true'"!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteInitBlockPort) and (not(node:empty(NvMRPortInterfacesASRVersion)))) or ((node:exists(NvMInitBlockCallback)) and (NvMInitBlockCallback != ''))"!][!/*
    */!][!VAR "CbKIndex"!][!INDENT "0"!][!/*
      */!][!CALL "GetCallbackIndex", "PartitionName" = "$PartitionSymbolicName", "CallbackType" = "'-Init-'"!][!/*
      */!][!ENDINDENT!][!ENDVAR!][!/*
    */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    &NvM_1_[!"$PartitionSymbolicName"!]_InitBlockCallbacks[[!"$CbKIndex"!]][!/*
      */!][!ELSE!][!/*
       */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteInitBlockPort) and (not(node:empty(NvMRPortInterfacesASRVersion))))"!][!/*
      */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    (NvM_CallbackFctPtr)[!/*
	*/!][!IF "(node:existsAndTrue(ASR2011CallbackEnabled))"!][!/*
	*/!]&Rte_Call_NvM_PNInitBlock_ASR2011_[!"as:name(.)"!]_InitBlock[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
    */!]&Rte_Call_PNInitBlock_[!"as:name(.)"!]_InitBlock[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
    */!]&Rte_Call_NvM_PNInitBlock_ASR32_[!"as:name(.)"!]_InitBlock[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
    */!]&Rte_Call_NvM_PNInitBlock_ASR40_[!"as:name(.)"!]_InitBlock[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
    */!]&Rte_Call_NvM_PNInitBlock_ASR42_[!"as:name(.)"!]_InitBlock[!/*
    */!][!ENDIF!][!/*
    */!][!ELSEIF "(node:exists(NvMInitBlockCallback)) and (NvMInitBlockCallback != '')"!][!/*
    */!]/* Deviation MISRAC2012-1 */
    (NvM_CallbackFctPtr)&[!"NvMInitBlockCallback"!][!/*
    */!][!ELSE!][!/*
       */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ENDIF!], /* initBlockCallback */
    [!IF "$BswDistributionEnabled = 'true'"!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteJobFinishedPort) and (not(node:empty(NvMRPortInterfacesASRVersion)))) or ((node:exists(NvMSingleBlockCallback)) and (NvMSingleBlockCallback != ''))"!][!/*
    */!][!VAR "CbKIndex"!][!INDENT "0"!][!/*
      */!][!CALL "GetCallbackIndex", "PartitionName" = "$PartitionSymbolicName", "CallbackType" = "'-Single-'"!][!/*
      */!][!ENDINDENT!][!ENDVAR!][!/*
    */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    &NvM_1_[!"$PartitionSymbolicName"!]_SingleBlockCallbacks[[!"$CbKIndex"!]][!/*
      */!][!ELSE!][!/*
       */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!][!/*
    */!][!IF "(node:existsAndTrue(NvMProvideRteJobFinishedPort) and node:existsAndTrue(../../NvMCommon/NvMRteUsage) and (not(node:empty(NvMRPortInterfacesASRVersion))))"!][!/*
      */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    (NvM_CallbackFctPtr)[!/*
	*/!][!IF "(node:existsAndTrue(ASR2011CallbackEnabled))"!][!/*
	*/!]&Rte_Call_NvM_PNJobFinished_ASR2011_[!"as:name(.)"!]_JobFinished[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
    */!]&Rte_Call_PNJobFinished_[!"as:name(.)"!]_JobFinished[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
    */!]&Rte_Call_NvM_PNJobFinished_ASR32_[!"as:name(.)"!]_JobFinished[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
    */!]&Rte_Call_NvM_PNJobFinished_ASR40_[!"as:name(.)"!]_JobFinished[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
    */!]&Rte_Call_NvM_PNJobFinished_ASR42_[!"as:name(.)"!]_JobFinished[!/*
    */!][!ENDIF!][!/*
    */!][!ELSEIF "(node:exists(NvMSingleBlockCallback)) and (NvMSingleBlockCallback != '')"!][!/*
    */!]/* Deviation MISRAC2012-1 */
    (NvM_CallbackFctPtr)&[!"NvMSingleBlockCallback"!][!/*
    */!][!ELSE!][!/*
    */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ENDIF!], /* singleBlockCallback */[!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[node:existsAndTrue(NvMBlockUseSyncMechanism)]) != 0"!]
    [!IF "$BswDistributionEnabled = 'true'"!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteMirrorPort) and (not(node:empty(NvMRPortInterfacesASRVersion)))) or (not(node:empty(NvMReadRamBlockFromNvCallback)) and node:existsAndTrue(NvMBlockUseSyncMechanism))"!][!/*
    */!][!VAR "CbKIndex"!][!INDENT "0"!][!/*
      */!][!CALL "GetCallbackIndex", "PartitionName" = "$PartitionSymbolicName", "CallbackType" = "'-Read-'"!][!/*
      */!][!ENDINDENT!][!ENDVAR!][!/*
    */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    &NvM_1_[!"$PartitionSymbolicName"!]_ReadBlockCallbacks[[!"$CbKIndex"!]][!/*
      */!][!ELSE!][!/*
       */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteMirrorPort) and (not(node:empty(NvMRPortInterfacesASRVersion))))"!][!/*
      */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    (NvM_NvToRamCopyCallbackType)[!/*
    */!][!IF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
    */!]&Rte_Call_PMirror_[!"as:name(.)"!]_ReadRamBlockFromNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR32_[!"as:name(.)"!]_ReadRamBlockFromNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR40_[!"as:name(.)"!]_ReadRamBlockFromNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR42_[!"as:name(.)"!]_ReadRamBlockFromNvm[!/*
    */!][!ENDIF!][!/*
    */!][!ELSEIF "not(node:empty(NvMReadRamBlockFromNvCallback)) and (node:existsAndTrue(NvMBlockUseSyncMechanism))"!][!/*
    */!]&[!"NvMReadRamBlockFromNvCallback"!][!/*
    */!][!ELSE!][!/*
    */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ENDIF!], /* readRamFromNvCallback */
    [!IF "$BswDistributionEnabled = 'true'"!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteMirrorPort) and (not(node:empty(NvMRPortInterfacesASRVersion)))) or (not(node:empty(NvMWriteRamBlockToNvCallback)) and node:existsAndTrue(NvMBlockUseSyncMechanism))"!][!/*
    */!][!VAR "CbKIndex"!][!INDENT "0"!][!/*
      */!][!CALL "GetCallbackIndex", "PartitionName" = "$PartitionSymbolicName", "CallbackType" = "'-Write-'"!][!/*
      */!][!ENDINDENT!][!ENDVAR!][!/*
    */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    &NvM_1_[!"$PartitionSymbolicName"!]_WriteBlockCallbacks[[!"$CbKIndex"!]][!/*
      */!][!ELSE!][!/*
       */!]NULL_PTR[!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!][!/*
    */!][!IF "(node:existsAndTrue(../../NvMCommon/NvMRteUsage) and node:existsAndTrue(NvMProvideRteMirrorPort) and (not(node:empty(NvMRPortInterfacesASRVersion))))"!][!/*
      */!]/* !LINKSTO NvM.Block.R-PortInterfacesAsrVersion.Interfaces,1 */
    /* Deviation MISRAC2012-1 */
    (NvM_RamToNvCopyCallbackType)[!/*
    */!][!IF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
    */!]&Rte_Call_PMirror_[!"as:name(.)"!]_WriteRamBlockToNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR32_[!"as:name(.)"!]_WriteRamBlockToNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR40_[!"as:name(.)"!]_WriteRamBlockToNvm[!/*
    */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
    */!]&Rte_Call_NvM_PMirror_ASR42_[!"as:name(.)"!]_WriteRamBlockToNvm[!/*
    */!][!ENDIF!][!/*
    */!][!ELSEIF "not(node:empty(NvMWriteRamBlockToNvCallback)) and (node:existsAndTrue(NvMBlockUseSyncMechanism))"!][!/*
    */!]&[!"NvMWriteRamBlockToNvCallback"!][!/*
    */!][!ELSE!][!/*
    */!]NULL_PTR[!/*
   */!][!ENDIF!][!/*
    */!][!ENDIF!], /* writeRamToNvCallback */[!/*
    */!][!ENDIF!]
    [!IF "(node:exists(NvMRomBlockDataAddress)) and (NvMRomBlockDataAddress != '')"!][!"NvMRomBlockDataAddress"!][!ELSE!]NULL_PTR[!ENDIF!], /* romBlockDataAddress */
    [!IF "(node:exists(NvMRamBlockDataAddress)) and (NvMRamBlockDataAddress != '')"!][!"NvMRamBlockDataAddress"!][!ELSE!]NULL_PTR[!ENDIF!], /* ramBlockDataAddress */[!/*
    === Caclulate blockDesc ==    */!]
    [!VAR "blockDesc"="0"!][!/*
    */!][!IF "node:existsAndTrue(NvMBlockUseCrc)"!][!/*
    */!][!IF "(node:exists(NvMCalcRamBlockCrc)) and (node:existsAndTrue(NvMCalcRamBlockCrc))"!][!VAR "blockDesc"="$blockDesc + 8"!][!ENDIF!][!/*
    */!][!IF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC32')"!][!VAR "blockDesc"="$blockDesc + 3"!][!/*
    */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC16')"!][!VAR "blockDesc"="$blockDesc + 2"!][!/*
    */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC8')"!][!VAR "blockDesc"="$blockDesc + 1"!][!ENDIF!][!/*
    */!][!ENDIF!][!/*
    */!][!IF "node:existsAndTrue(NvMBlockWriteProt)"!][!VAR "blockDesc"="$blockDesc + 16"!][!ENDIF!][!/*
    */!][!IF "node:existsAndTrue(NvMWriteBlockOnce)"!][!VAR "blockDesc"="$blockDesc + 32"!][!ENDIF!][!/*
    */!][!IF "node:existsAndTrue(NvMResistantToChangedSw)"!][!VAR "blockDesc"="$blockDesc + 64"!][!ENDIF!][!/*
    */!][!IF "NvMBlockManagementType = 'NVM_BLOCK_REDUNDANT'"!][!VAR "blockDesc"="$blockDesc + 128"!][!ENDIF!][!/*
    */!][!IF "NvMBlockManagementType = 'NVM_BLOCK_DATASET'"!][!VAR "blockDesc"="$blockDesc + 256"!][!ENDIF!][!/*
    */!][!IF "(node:exists(NvMSelectBlockForReadAll)) and (node:existsAndTrue(NvMSelectBlockForReadAll))"!][!VAR "blockDesc"="$blockDesc + 512"!][!ENDIF!][!/*
    */!][!IF "(node:exists(NvMSelectBlockForWriteAll)) and (node:existsAndTrue(NvMSelectBlockForWriteAll))"!][!VAR "blockDesc"="$blockDesc + 262144"!][!ENDIF!][!/*
    */!][!VAR "blockDesc"="$blockDesc +  bit:shl(NvMNvramDeviceId, 10)"!][!/*
    === 'Use internal buffer' flag : Set Bit 13 (+8192) if internal buffer shall be used ===
    Internal buffer shall be used if:
      1. Crc is enabled but is not stored inside the RAM block.
      2. Write Verification or Static BlockID Check is enabled.
      5. Crypto security handling is used
      3. Block management type is NVM_BLOCK_REDUNDANT.
      4. Block management type is NVM_BLOCK_DATASET.
    */!][!IF "(((node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndFalse(NvMUserProvidesSpaceForBlockAndCrc))) or
               (node:existsAndTrue(NvMWriteVerification)) or
               (node:existsAndTrue(NvMPreWriteDataComp)) or
               (node:existsAndTrue(NvMStaticBlockIDCheck)) or
               (node:existsAndTrue(NvMEnableBlockCryptoSecurityHandling)) or
               (NvMBlockManagementType = 'NVM_BLOCK_REDUNDANT') or
               (NvMBlockManagementType = 'NVM_BLOCK_DATASET'))"!][!/*
    */!][!VAR "blockDesc"="$blockDesc + 8192"!][!ENDIF!][!/*
    === 'Advanced Recovery' flag : Set Bit 14 (+16384) if Advanced Recovery shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMAdvancedRecovery)"!][!VAR "blockDesc"="$blockDesc + 16384"!][!ENDIF!][!/*
    === 'Write Verification' flag : Set Bit 15 (+32768) if Write Verification shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMWriteVerification)"!][!VAR "blockDesc"="$blockDesc + 32768"!][!ENDIF!][!/*
    === 'Static Block Id' flag : Set Bit 16 (+65536) if Static Block Id shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMStaticBlockIDCheck)"!][!VAR "blockDesc"="$blockDesc + 65536"!][!ENDIF!][!/*
    === 'Use Mirror' flag : Set Bit 17 (+131072) if Explicit Synchronization shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMBlockUseSyncMechanism)"!][!VAR "blockDesc"="$blockDesc + 131072"!][!ENDIF!][!/*
    === 'Job status info' flag : Set Bit 19 (+524288) if BswM Block
    status information shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMBswMBlockStatusInformation)"!][!VAR "blockDesc"="$blockDesc + 524288"!][!ENDIF!][!/*
    === 'User provides space for CRC' flag : Set Bit 20 (+1048576) if the user reserved space for CRC in the RAM block === */!][!/*
    */!][!IF "NvMNvramBlockIdentifier = '1'"!][!VAR "blockDesc"="$blockDesc + 1048576"!][!/* !LINKSTO NvM.CrcStorage.Config.Block1,1
    */!][!ELSE!][!/*
    */!][!IF "((node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndTrue(NvMUserProvidesSpaceForBlockAndCrc)))"!][!VAR "blockDesc"="$blockDesc + 1048576"!][!ENDIF!][!/*
    */!][!ENDIF!][!/*
    === 'User provides space for Validation' flag : Set Bit 21 (+1048576) if AutoValidate enabled=== */!][!/*
    */!][!IF "(node:exists(NvMBlockUseAutoValidation)) and (node:existsAndTrue(NvMBlockUseAutoValidation))"!][!VAR "blockDesc"="$blockDesc + 2097152"!][!ENDIF!][!/*
    === 'Use NvMSetRamBlockStatus' flag : Set Bit 22 (+4194304) if NvMSetRamBlockStatus shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMBlockUseSetRamBlockStatus)"!][!VAR "blockDesc"="$blockDesc + 4194304"!][!ENDIF!][!/*
    === 'Use Data Comparison' flag : Set Bit 23 (+8388608) if Data Comparison shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMPreWriteDataComp)"!][!VAR "blockDesc"="$blockDesc + 8388608"!][!ENDIF!][!/*
    === 'Use CRCComp Mechanism' flag : Set Bit 24 (+16777216) if CRC Comparison shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMBlockUseCRCCompMechanism)"!][!VAR "blockDesc"="$blockDesc + 16777216"!][!ENDIF!][!/*
    === 'Use FirstInitAll Mechanism' flag : Set Bit 25 (+33554432) if FirstInitAll shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMSelectBlockForFirstInitAll)"!][!VAR "blockDesc"="$blockDesc + 33554432"!][!ENDIF!][!/*
    === 'Use ASR2011 callbacks format' flag : Set Bit 26 (+67108864) if ASR2011 callbacks format shall be used === */!][!/*
    */!][!IF "(node:existsAndTrue(ASR2011CallbackEnabled))"!][!VAR "blockDesc"="$blockDesc + 67108864"!][!ENDIF!][!/*
    === 'Use Crypto handling Hooks' flag : Set Bit 27 (+134217728) if Crypto handling Hooks shall be used === */!][!/*
    */!][!IF "node:existsAndTrue(NvMEnableBlockCryptoSecurityHandling)"!][!VAR "blockDesc"="$blockDesc + 134217728"!][!ENDIF!][!/*
    */!][!"num:inttohex($blockDesc,8)"!]U,  /* blockDesc */
    [!"NvMNvBlockLength"!]U,  /* nvBlockLength */
    [!IF "NvMNvramBlockIdentifier = '1'"!][!/*
      */!][!VAR "Block1Size"="NvMNvBlockLength"!][!/*
    */!][!ENDIF!]
    [!VAR "NvMBlockBaseNumber"="bit:shl((NvMNvBlockBaseNumber),num:i(as:modconf('NvM')[1]/NvMCommon/NvMDatasetSelectionBits))"!]
    [!"$NvMBlockBaseNumber"!]U,  /* nvBlockBaseNumber */
    [!"NvMNvramBlockIdentifier"!]U,   /* nvBlockIdentifier*/
    [!IF "(node:exists(NvMCalcRamBlockCrc)) and (node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndTrue(NvMCalcRamBlockCrc))"!][!/*
    */!][!"num:i($CRCLength)"!]U[!/*
    */!][!IF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC8')"!][!/*
      */!][!VAR "CRCLength"="$CRCLength + 1"!][!/*
    */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC16')"!][!/*
      */!][!VAR "CRCLength"="$CRCLength + 2"!][!/*
      */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC32')"!][!/*
      */!][!VAR "CRCLength"="$CRCLength + 4"!][!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!][!/*
    */!]0xFFFFU[!/*
    */!][!ENDIF!], /* ramBlockCrcIndex */[!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCRCCompMechanism))]) != 0"!][!/*
    */!][!IF "(node:exists(NvMBlockUseCRCCompMechanism)) and (node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndTrue(NvMBlockUseCRCCompMechanism))"!]
    [!"num:i($NvCRCLength)"!]U[!/*
    */!][!IF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC8')"!][!/*
      */!][!VAR "NvCRCLength"="$NvCRCLength + 1"!][!/*
    */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC16')"!][!/*
      */!][!VAR "NvCRCLength"="$NvCRCLength + 2"!][!/*
      */!][!ELSEIF "(node:exists(NvMBlockCrcType)) and (NvMBlockCrcType = 'NVM_CRC32')"!][!/*
      */!][!VAR "NvCRCLength"="$NvCRCLength + 4"!][!/*
    */!][!ENDIF!][!/*
    */!][!ELSE!]
    0xFFFFU[!/*
    */!][!ENDIF!], /* nvBlockCrcIndex */[!/*
    */!][!ELSE!][!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMWriteVerification))]) != 0"!][!/*
    */!][!IF "node:exists(NvMWriteVerificationDataSize)"!]
    [!"num:i(NvMWriteVerificationDataSize)"!]U,  /* verifyDataSize */[!/*
    */!][!ELSE!]
    1U,  /* verifyDataSize */[!/*
    */!][!ENDIF!][!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMPreWriteDataComp))]) != 0"!][!/*
    */!][!IF "node:exists(NvMPreWriteDataCompDataSize)"!]
    [!"num:i(NvMPreWriteDataCompDataSize)"!]U,  /* preWriteDataCompDataSize */[!//
    [!ELSE!]
    1U,  /* preWriteDataCompDataSize */[!/*
    */!][!ENDIF!][!/*
    */!][!ENDIF!][!/*]
    */!][!IF "(count(../../NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMEnBlockCheck))]) != 0)"!][!/*]
    */!][!IF "node:existsAndTrue(NvMEnBlockCheck)"!]
    [!"num:i($BcBlkIdx)"!]U, /* bcBlockIdx */[!/*
    */!][!VAR "BcBlkIdx"="$BcBlkIdx + 1"!][!/*
    */!][!ELSE!]
    [!IF "(count(../../NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMEnBlockCheck))]) < 256)"!]0xFFU,[!ELSE!]0xFFFFU,[!ENDIF!] /* bcBlockIdx */[!/*
    */!][!ENDIF!][!/*]
    */!][!ENDIF!][!//]
    [!"num:i(NvMNvBlockNum)"!]U, /* nvBlockNum */
    [!"num:i(NvMRomBlockNum)"!]U, /* romBlockNum */
    [!IF "node:existsAndTrue(../../NvMCommon/NvMJobPrioritization)"!][!/*
    */!][!"num:i(NvMBlockJobPriority)"!]U, /* blockJobPriority */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[(NvMMaxNumOfWriteRetries > 0)]) != 0"!]
    [!"num:i(NvMMaxNumOfWriteRetries)"!]U,  /* writeRetryLimit */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "count(../../NvMBlockDescriptor/eb-list::*[(NvMMaxNumOfReadRetries > 0)]) != 0"!]
    [!"NvMMaxNumOfReadRetries"!]U,  /* readRetryLimit */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "node:existsAndTrue(../../NvMCommon/NvMCommonCryptoSecurityParameters/NvMEnableCryptoSecurityHooks)"!]
    [!"NvMCryptoExtraInfoSize"!]U  /* CryptoExtraInfoSize */[!/*
    */!][!ENDIF!][!/*
    */!][!IF "$OsAppSymbolicName != ''"!]
    (uint8)[!"$OsAppSymbolicName"!]  /* OsApplication symbolic name */[!/*
    */!][!ENDIF!]
  }[!/*
*/!][!ENDLOOP!]
}; /* NvM_BlockDescriptorTable */

[!IF "$BswDistributionEnabled = 'true'"!]

CONST(NvM_SchMInterPartitionCallsType,NVM_CONST) NvM_SchMInterPartitionCalls[NVM_NUMBER_OF_SATELLITE_PARTITIONS]=
{[!/*
*/!][!LOOP "as:modconf('NvM')[1]/NvMCommon/NvMEcucPartitionRef/eb-list::*"!][!/*
         */!][!IF "as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef != (.)"!][!/*
         */!][!VAR "SatellitePartition" = "(.)"!][!/*
         */!][!VAR "SatellitePartitionName" = "substring-after($SatellitePartition,'EcucPartitionCollection/')"!]
  /* [!"$SatellitePartitionName"!] */[!/*
   */!]
  {[!/*
    */!]
    &NvM_1_[!"$SatellitePartitionName"!]_SchMJobCalls, /* schMJobCalls */
    [!IF "count(as:modconf('NvM')[1]/NvMBlockDescriptor/eb-list::*[(NvMBlockEcucPartitionRef = node:current()) and (node:existsAndTrue(NvMProvideRteJobFinishedPort) or ((node:exists(NvMSingleBlockCallback)) and (NvMSingleBlockCallback != '')))]) != 0"!][!/*
      */!]
    /* Deviation MISRAC2012-1 */
    (NvM_SchMJobEndCallbackFctPtr)[!/*
    */!]&SchM_Call_NvM_RequiredCSEntry_NvM_1_[!"$SatellitePartitionName"!]_JobFinished[!/*
    */!][!ELSE!][!/*
    */!]NULL_PTR[!/*
    */!][!ENDIF!], /* singleBlockCallback */
    (uint8)[!"name(as:modconf('Os')[1]/OsApplication/eb-list::*[string(OsAppEcucPartitionRef) = $SatellitePartition])"!]  /* OsApplication symbolic name */
  },[!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!]
}; /* NvM_SchMInterPartitionCalls */
[!/*
*/!][!VAR "MasterPartition" = "as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef"!][!/*
*/!][!VAR "MasterPartitionName" = "substring-after($MasterPartition,'EcucPartitionCollection/')"!][!/*
*/!][!IF "($InitCallbackArraySize > 0)"!]

/* Deviation MISRAC2012-1 */
STATIC CONST(NvM_CallbackFctPtr,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_InitBlockCallbacks[[!"$InitCallbackArraySize"!]]=
{[!/*
  */!]
[!FOR "i" = "1" TO "$InitCallbackArraySize"!][!/*
  */!]  [!"text:split($InitCallbackArray, ';')[position() = $i]"!]
[!/*
*/!][!ENDFOR!][!/*
*/!]}; /* NvM_1_[!"$MasterPartitionName"!]_InitBlockCallbacks */
[!ENDIF!][!/*
*/!][!IF "($SingleCallbackArraySize > 0)"!]

/* Deviation MISRAC2012-1 */
STATIC CONST(NvM_CallbackFctPtr,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_SingleBlockCallbacks[[!"$SingleCallbackArraySize"!]]=
{[!/*
  */!]
[!FOR "i" = "1" TO "$SingleCallbackArraySize"!][!/*
  */!]  [!"text:split($SingleCallbackArray, ';')[position() = $i]"!]
[!/*
*/!][!ENDFOR!][!/*
*/!]}; /* NvM_1_[!"$MasterPartitionName"!]_SingleBlockCallbacks */
[!ENDIF!][!/*
*/!][!IF "($ReadCallbackArraySize > 0)"!]

STATIC CONST(NvM_NvToRamCopyCallbackType,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_ReadBlockCallbacks[[!"$ReadCallbackArraySize"!]]=
{[!/*
  */!]
[!FOR "i" = "1" TO "$ReadCallbackArraySize"!][!/*
  */!]  [!"text:split($ReadCallbackArray, ';')[position() = $i]"!]
[!/*
*/!][!ENDFOR!][!/*
*/!]}; /* NvM_1_[!"$MasterPartitionName"!]_ReadBlockCallbacks */
[!ENDIF!][!/*
*/!][!IF "($WriteCallbackArraySize > 0)"!]

STATIC CONST(NvM_RamToNvCopyCallbackType,NVM_CONST) NvM_1_[!"$MasterPartitionName"!]_WriteBlockCallbacks[[!"$WriteCallbackArraySize"!]]=
{[!/*
  */!]
[!FOR "i" = "1" TO "$WriteCallbackArraySize"!][!/*
  */!]  [!"text:split($WriteCallbackArray, ';')[position() = $i]"!]
[!/*
*/!][!ENDFOR!][!/*
*/!]}; /* NvM_1_[!"$MasterPartitionName"!]_WriteBlockCallbacks */
[!ENDIF!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "(count(NvMBlockDescriptor/eb-list::*[node:existsAndTrue(NvMEnBlockCheck)]) != 0)"!][!/*]
*/!]CONST(NvM_BcCfgDataType,NVM_CONST) NvM_BcCfgData[NVM_BC_NR_OF_BLOCKS]=
{[!/*
*/!][!VAR "BcBlockIndex"="0"!][!/*
*/!][!LOOP "util:distinct(node:order(NvMBlockDescriptor/eb-list::*, 'NvMNvramBlockIdentifier'))"!][!/*
*/!][!VAR "BcBlockIndex"="$BcBlockIndex + 1"!][!/*
*/!][!IF "node:existsAndTrue(NvMEnBlockCheck)"!]
  {
  [!"num:i($BcBlockIndex)"!]U,  /* Block descriptor index */
  [!"num:i(NvMBcDelayCounter)"!]U,  /* delayCounter */
  [!VAR "BcBlockDesc"="0"!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnAutoStart)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 1"!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnCrcComp)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 2"!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnRamComp)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 4"!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnReddCopiesComp)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 8"!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnAutoRepair)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 16"!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMBcEnSetAPI)"!][!VAR "BcBlockDesc"="$BcBlockDesc + 32"!][!ENDIF!][!/*
  */!][!"num:inttohex($BcBlockDesc,2)"!]U,  /* BcBlockDesc */
  },[!ENDIF!][!/*
*/!][!ENDLOOP!]
};[!/*
*/!][!ENDIF!]
#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_STOP_SEC_CONFIG_DATA_MC_SHARED_UNSPECIFIED
#include <NvM_MemMap.h>
#else
#define NVM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/

[!VAR "BlockIdIndex"="0"!][!/*
*/!][!IF "(count(NvMBlockDescriptor/eb-list::*) != num:max(NvMBlockDescriptor/eb-list::*/NvMNvramBlockIdentifier)) and (num:max(NvMBlockDescriptor/eb-list::*/NvMNvramBlockIdentifier) div (count(NvMBlockDescriptor/eb-list::*) + 1) <= 10)"!]
#define NVM_START_SEC_CONFIG_DATA_16
#include <NvM_MemMap.h>
CONST(uint16, NVM_CONST) NvM_RedirBlockId[[!"num:i((num:max(NvMBlockDescriptor/eb-list::*/NvMNvramBlockIdentifier)) + 1)"!]U]=
{[!/*
*/!]
  0U, /* Position of block with Id 0 in the Configuration structure */
[!/*
  */!][!FOR "i" = "1" TO "(num:max(NvMBlockDescriptor/eb-list::*/NvMNvramBlockIdentifier))"!][!/*
    */!][!VAR "BlockFound"="'FALSE'"!][!/*
    */!][!LOOP "util:distinct(node:order(NvMBlockDescriptor/eb-list::*, 'NvMNvramBlockIdentifier'))"!][!/*
      */!][!IF "number($i) = NvMNvramBlockIdentifier"!][!/*
        */!][!VAR "BlockFound"="'TRUE'"!][!/*
      */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
    */!][!IF "$BlockFound = 'TRUE'"!][!/*
      */!][!VAR "BlockIdIndex"="$BlockIdIndex + 1"!][!/*

            */!]  [!"num:i($BlockIdIndex)"!]U, /* Position of block with Id [!"num:i($i)"!] in the Configuration structure */
[!/*
        */!][!ELSE!][!/*

            */!]  [!"num:i((count(NvMBlockDescriptor/eb-list::*)) + 1)"!]U, /* NO block with Id [!"num:i($i)"!] in the Configuration structure */
[!/*
        */!][!ENDIF!][!/*
  */!][!ENDFOR!][!/*
*/!]};
#define NVM_STOP_SEC_CONFIG_DATA_16
#include <NvM_MemMap.h>
[!ENDIF!]

#define NVM_START_SEC_CONFIG_DATA_8
#include <NvM_MemMap.h>

#if (NVM_CANCEL_INTERNAL_JOB == STD_ON)
CONST(uint8,NVM_CONST) NvM_UsedDeviceIds[NVM_NUM_USED_DEVICES]=
{[!/*
*/!][!LOOP "text:split($NVM_DeviceIdList,';')"!]
[!"."!]U,[!//
[!ENDLOOP!][!//

};/*NvM_UsedDeviceIds*/
#endif /* NVM_CANCEL_INTERNAL_JOB == STD_ON */

#define NVM_STOP_SEC_CONFIG_DATA_8
#include <NvM_MemMap.h>
[!/*
 */!]
[!IF "$maxCrcSize=1"!]
#define NVM_START_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
 [!/*
 */!]
VAR(uint8,NVM_APPL_DATA) NvM_CalcCrc_CalcBuffer = (uint8)0U;
[!/*
 */!]
#define NVM_STOP_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
[!ELSEIF "$maxCrcSize=2"!]
#define NVM_START_SEC_VAR_INIT_16
#include <NvM_MemMap.h>
 [!/*
 */!]
VAR(uint16,NVM_APPL_DATA) NvM_CalcCrc_CalcBuffer = (uint16)0U;
[!/*
 */!]
#define NVM_STOP_SEC_VAR_INIT_16
#include <NvM_MemMap.h>
[!ELSE!]
#define NVM_START_SEC_VAR_INIT_32
#include <NvM_MemMap.h>
 [!/*
 */!]
VAR(uint32,NVM_APPL_DATA) NvM_CalcCrc_CalcBuffer = (uint32)0U;
[!/*
 */!]
#define NVM_STOP_SEC_VAR_INIT_32
#include <NvM_MemMap.h>
[!ENDIF!][!/*
 */!]
[!IF "not(node:exists(NvMCommon/NvMSoftwareChangeCallout)) and (NvMCommon/NvMSoftwareChangeCallout != '')"!]
[!IF "$Block1Size != 2"!][!//
[!/* NvMCompiledConfigId is converted into hex and separated on hex Bytes and put them in the array in the reversed order */!]
[!VAR "hexConfigId" = "num:inttohex(as:modconf('NvM')[1]/NvMCommon/NvMCompiledConfigId)"!][!/*
*/!][!VAR "hexPrefix" = "substring( $hexConfigId, 1, 2)"!][!/*
*/!][!VAR "hexString" = "substring-after( $hexConfigId,'0x')"!][!/*
*/!][!IF "string-length( $hexString ) mod 2 != 0"!][!/*
    */!][!VAR "hexString" = "concat( '0',$hexString)"!][!/*
*/!][!ENDIF!][!/*
*/!]/* !LINKSTO NvM.SWS_NvM_00034,1 */
#define NVM_START_SEC_CONFIG_DATA_8
#include <NvM_MemMap.h>
CONST(uint8,NVM_CONST) NvM_CompiledConfigurationId[NVM_CONFIGURATIONID_SIZE] = {[!//
[!IF "number($Block1Size) < (string-length($hexString) div 2)"!][!/*
    */!][!WARNING!]The size of the block 1 has to be at least [!"string-length($hexString) div 2"!] [!ENDWARNING!][!/*
    */!]};[!/*
*/!][!ELSE!][!/*
  */!][!FOR "i" = "1" TO "$Block1Size"!][!/*
  */!][!IF "number($i) <= (string-length($hexString) div 2)"!][!/*
        */!]0x[!"substring( $hexString, string-length($hexString) - ((2*$i)-1), 2)"!],[!/*
    */!][!ELSE!][!/*
        */!]0x00,[!/*
    */!][!ENDIF!][!/*
  */!][!ENDFOR!]};[!/*
*/!][!ENDIF!]
#define NVM_STOP_SEC_CONFIG_DATA_8
#include <NvM_MemMap.h>
[!ELSE!]
#define NVM_START_SEC_CONFIG_DATA_16
#include <NvM_MemMap.h>
/* !LINKSTO NvM.SWS_NvM_00034,1 */
CONST(uint16,NVM_CONST) NvM_CompiledConfigurationId = [!"num:inttohex(NvMCommon/NvMCompiledConfigId)"!]U;
#define NVM_STOP_SEC_CONFIG_DATA_16
#include <NvM_MemMap.h>
[!ENDIF!][!/*
*/!]
[!ELSE!]
#define NVM_START_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
/** \brief Stores the address of the new Configuration Id
 **/
VAR( uint8,NVM_VAR ) NvM_CompiledConfigurationId[NVM_CONFIGURATIONID_SIZE] = {0U};

#define NVM_STOP_SEC_VAR_INIT_8
#include <NvM_MemMap.h>
[!ENDIF!]

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
