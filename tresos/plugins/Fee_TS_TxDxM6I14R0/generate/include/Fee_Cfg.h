#ifndef FEE_CFG_H
#define FEE_CFG_H
/**
 * \file
 *
 * \brief AUTOSAR Fee
 *
 * This file contains the implementation of the AUTOSAR
 * module Fee.
 *
 * \version 6.14.31
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!AUTOSPACING!]
[!VAR "VendorApiInfix" = "'EB'"!]
[!VAR "VendorId" = "1"!]
/*==================[inclusions]============================================*/
/* !LINKSTO Fee.SWS_Fee_00084,2, Fee.ASR40.SWS_Fee_00002,1 */
#include <MemIf_Types.h>
[!IF "(node:existsAndTrue(FeeGeneral/FeeMemAccUsage))"!][!//
#include <MemAcc.h>
[!ELSE!][!//
/* !LINKSTO Fee.SWS_Fee_00084,2, Fee.ASR40.SWS_Fee_00002,1 */
[!IF "(node:exists(as:modconf('Fls')[1]/CommonPublishedInformation/VendorApiInfix)) and (not(as:modconf('Fls')[1]/CommonPublishedInformation/VendorApiInfix = ''))"!][!//
[!VAR "VendorApiInfix" = "as:modconf('Fls')[1]/CommonPublishedInformation/VendorApiInfix"!][!//
[!VAR "VendorId" = "as:modconf('Fls')[1]/CommonPublishedInformation/VendorId"!][!//
#include <Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!].h>
[!ELSE!]
#include <Fls.h>
[!ENDIF!]
[!ENDIF!]
/* !LINKSTO Fee.ASR40.SWS_Fee_00002,1 */
#include <NvM_Cbk.h>  /* NvM callback interface */
[!IF "((node:exists(FeeGeneral/FeeNvmJobEndNotification)) and
(FeeGeneral/FeeNvmJobEndNotification != '') and (FeeGeneral/FeeNvmJobEndNotification != 'NULL_PTR'))
or ((node:exists(FeeGeneral/FeeNvmJobErrorNotification)) and
(FeeGeneral/FeeNvmJobErrorNotification != '') and (FeeGeneral/FeeNvmJobErrorNotification != 'NULL_PTR'))"!]
#include <NvM_Cbk.h>  /* NvM callback interface */
[!ENDIF!]
[!INCLUDE "Fee_Checks.m"!]

/*==================[macros]================================================*/

/** \brief The total flash size
 **
 ** This parameter defines the total flash size. */
#if (defined FEE_TOTAL_FLASH_SIZE)
#error FEE_TOTAL_FLASH_SIZE is already defined
#endif
#define FEE_TOTAL_FLASH_SIZE                       [!"num:inttohex($TotalFlashSize)"!]U
 
/** \brief Represents the number of blocks configured by the user */
#if (defined FEE_NO_OF_CONFIGURED_BLOCKS)
#error FEE_NO_OF_CONFIGURED_BLOCKS is already defined
#endif
#define FEE_NO_OF_CONFIGURED_BLOCKS                [!"num:integer(count(FeeBlockConfiguration/eb-list::*))"!]U

/** \brief Represents the size of the biggest block */
#if (defined FEE_BIGGEST_BLOCK_SIZE)
#error FEE_BIGGEST_BLOCK_SIZE is already defined
#endif
#define FEE_BIGGEST_BLOCK_SIZE                     [!"num:inttohex($LargestBlockSizeInSection)"!]U

#if (defined FEE_NUMBER_NOT_CONFIGURED_BLOCKS)
#error FEE_NUMBER_NOT_CONFIGURED_BLOCKS is already defined
#endif
/** \brief Represents the number of not-configured blocks that Fee can handle */
#define FEE_NUMBER_NOT_CONFIGURED_BLOCKS           [!"$NumberOfNotConfigBlocks"!]U

#if (defined FEE_IMMEDIATE_SPACE_RESERVED)
#error FEE_IMMEDIATE_SPACE_RESERVED is already defined
#endif
/** \brief Represents the space to reserve for immediate blocks in the last available section */
#define FEE_IMMEDIATE_SPACE_RESERVED           [!"$ImmediateSpaceReserved"!]U

#if (defined FEE_NOT_CONFIGURED_BLOCKS_DATA_SIZE)
#error FEE_NOT_CONFIGURED_BLOCKS_DATA_SIZE is already defined
#endif
/** \brief Represents the upper layer data size for not-configured blocks that Fee can handle */
#define FEE_NOT_CONFIGURED_BLOCKS_DATA_SIZE        [!"$NotConfigBlocksDataSize"!]U

#if (defined FEE_NOT_CONFIGURED_BLOCKS_TOTAL_SIZE)
#error FEE_NOT_CONFIGURED_BLOCKS_TOTAL_SIZE is already defined
#endif
/** \brief Represents the total size reserved for the not-configured blocks that Fee can handle */
#define FEE_NOT_CONFIGURED_BLOCKS_TOTAL_SIZE       [!"$NotConfigBlocksTotalSizeAl"!]U

#if (defined FEE_TOTAL_NUMBER_OF_BLOCKS)
#error FEE_TOTAL_NUMBER_OF_BLOCKS is already defined
#endif
/** \brief Total number of blocks (configured and not configured) to be used by Fee */
#define FEE_TOTAL_NUMBER_OF_BLOCKS                 [!"num:integer(count(FeeBlockConfiguration/eb-list::*) + $NumberOfNotConfigBlocks)"!]U

[!SELECT "FeeGeneral"!]

/** \brief Precompiler switch to support new ASR21-11 module MemAcc
 **
 ** Precompiler switch to support new ASR21-11 module MemAcc. */
#if (defined FEE_USE_MEMACC)
#error FEE_USE_MEMACC is already defined
#endif
[!IF "(node:existsAndTrue(FeeMemAccUsage))"!][!//
#define FEE_USE_MEMACC                    STD_ON
[!ELSE!]
#define FEE_USE_MEMACC                    STD_OFF
[!ENDIF!]

/** \brief Number of sections
 **
 ** This parameter defines the total number of sections. */
#if (defined FEE_NUMBER_OF_SECTIONS)
#error FEE_NUMBER_OF_SECTIONS is already defined
#endif
#define FEE_NUMBER_OF_SECTIONS                     [!"FeeNumberOfSections"!]U


/** \brief Represents the size of internal buffer for writing block data and
 ** reading block infos */
#if (defined FEE_BUFFER_SIZE)
#error FEE_BUFFER_SIZE is already defined
#endif
#define FEE_BUFFER_SIZE                            [!"$BufferSize"!]U

/** \brief Represents the size of internal buffer used at init to cache blocks */
#if (defined FEE_INIT_BUFFER_SIZE)
#error FEE_INIT_BUFFER_SIZE is already defined
#endif
#define FEE_INIT_BUFFER_SIZE                       [!"$InitBufferSize"!]U

/** \brief Virtual page size */
#if (defined FEE_VIRTUAL_PAGE_SIZE)
#error FEE_VIRTUAL_PAGE_SIZE is already defined
#endif
#define FEE_VIRTUAL_PAGE_SIZE                      [!"FeeVirtualPageSize"!]U

/** \brief ConfigId computed over Virtual Page, Number of sections, Sections addresses and sizes  */
#if (defined FEE_CONFIG_ID)
#error FEE_CONFIG_ID is already defined
#endif
#define FEE_CONFIG_ID                              [!"$ConfigId"!]U

/** \brief LegacyConfigId computed over Virtual Page, Number of sections, Total flash data size */
#if (defined FEE_LEGACY_CONFIG_ID)
#error FEE_LEGACY_CONFIG_ID is already defined
#endif
#define FEE_LEGACY_CONFIG_ID                       [!"$ConfigId_Legacy"!]U

/** \brief The size of consistency pattern markers */
#define FEE_CONSISTENCY_PATTERN_SIZE               [!"$EndPatternSize"!]U

/** \brief Number of bytes used by header fields when aligned to virtual page */
#if (defined FEE_SECTION_MARKER_SIZE_AL)
#error FEE_SECTION_MARKER_SIZE_AL is already defined
#endif
#define FEE_SECTION_MARKER_SIZE_AL            [!"$HeaderStatusFieldSize"!]U

/** \brief Number of bytes used by the Erase Counter field */
#if (defined FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL)
#error FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL is already defined
#endif
#define FEE_SECTION_MANAGEMENT_OBJ_SIZE_AL         [!"$SectionManagementObjectSizeAl"!]U

/** \brief Size of the 5 fields of the section header (Erase Counter Field, Active Field,
 *         Erasable Field, Crc, ConfigId, SectionCounter and its inverted)
 */
#if (defined FEE_HEADER_SIZE)
#error FEE_HEADER_SIZE is already defined
#endif
#define FEE_HEADER_SIZE                            [!"$HeaderSize"!]U

/** \brief Offset of erasable field from header start address */
#if (defined FEE_HEADER_ERASABLE_MARKER_OFFSET)
#error FEE_HEADER_ERASABLE_MARKER_OFFSET is already defined
#endif
#define FEE_HEADER_ERASABLE_MARKER_OFFSET          0U

/** \brief Offset of erase counter field from header start address */
#if (defined FEE_SECTION_MANAGEMENT_OFFSET)
#error FEE_SECTION_MANAGEMENT_OFFSET is already defined
#endif
#define FEE_SECTION_MANAGEMENT_OFFSET              [!"num:integer($HeaderStatusFieldSize)"!]U

/** \brief Offset of header Crc */
#if (defined FEE_ECRCFIELD_OFFSET)
#error FEE_ECRCFIELD_OFFSET is already defined
#endif
#define FEE_ECRCFIELD_OFFSET                       [!"num:integer($HeaderStatusFieldSize + $HeaderEraseCounter)"!]U

/** \brief Offset of configId and section counter Crc */
#if (defined FEE_CRCFIELD_OFFSET)
#error FEE_CRCFIELD_OFFSET is already defined
#endif
#define FEE_CRCFIELD_OFFSET                        [!"num:integer($HeaderStatusFieldSize + $HeaderEraseCounter + $ECounterCrc)"!]U

/** \brief Offset of header Config Id */
#if (defined FEE_CIDFIELD_OFFSET)
#error FEE_CIDFIELD_OFFSET is already defined
#endif
#define FEE_CIDFIELD_OFFSET                        [!"num:integer($HeaderStatusFieldSize + $HeaderEraseCounter + $ECounterCrc + $CidCrc)"!]U

 /** \brief Offset of SectionCounter */
#if (defined FEE_SECTIONCOUNTERFIELD_OFFSET)
#error FEE_SECTIONCOUNTERFIELD_OFFSET is already defined
#endif
#define FEE_SECTIONCOUNTERFIELD_OFFSET             [!"num:integer($HeaderStatusFieldSize + $HeaderEraseCounter + $ECounterCrc + $CidCrc + $HeaderConfigId)"!]U

/** \brief Offset of active field from header start address */
#if (defined FEE_HEADER_ACTIVE_MARKER_OFFSET)
#error FEE_HEADER_ACTIVE_MARKER_OFFSET is already defined
#endif
#define FEE_HEADER_ACTIVE_MARKER_OFFSET            [!"num:integer($SectionManagementObjectSizeAl + $HeaderStatusFieldSize + $EndPatternSize)"!]U

[!IF "((node:existsAndTrue(FeeUseBlankCheck)) and (node:existsAndTrue(FeeConsistencyPattern)))"!][!//
/** \brief Offset of section management end pattern field from header start address */
#if (defined FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET)
#error FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET is already defined
#endif
#define FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET    [!"num:integer($SectionManagementObjectSizeAl + $HeaderStatusFieldSize)"!]U
[!ELSE!]
 /** \brief Offset of section management end pattern field from header start address */
#if (defined FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET)
#error FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET is already defined
#endif
#define FEE_SECTION_MANAGEMENT_END_PATTERN_OFFSET    0U
[!ENDIF!]

/** \brief Erase counter API on\off compiler switch */
#if (defined FEE_ERASE_COUNTER_API)
#error FEE_ERASE_COUNTER_API is already defined
#endif
#define FEE_ERASE_COUNTER_API                        [!//
[!IF "node:existsAndTrue(FeeEraseCounterApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief FreezeActivities API on\off compiler switch */
#if (defined FEE_FREEZE_ACTIVITIES_API)
#error FEE_FREEZE_ACTIVITIES_API is already defined
#endif
[!IF "(node:existsAndTrue(FeeFreezeActivitiesApi))"!][!//
#define FEE_FREEZE_ACTIVITIES_API                    STD_ON
[!ELSE!]
#define FEE_FREEZE_ACTIVITIES_API                    STD_OFF
[!ENDIF!]

/** \brief DynamicBlockLength on\off compiler switch */
#if (defined FEE_DYNAMIC_BLOCK_LENGTH)
#error FEE_DYNAMIC_BLOCK_LENGTH is already defined
#endif
[!IF "(node:existsAndTrue(FeeDynamicBlockLength))"!][!//
#define FEE_DYNAMIC_BLOCK_LENGTH                      STD_ON
[!ELSE!]
#define FEE_DYNAMIC_BLOCK_LENGTH                      STD_OFF
[!ENDIF!]

/** \brief FeeEnableSmallSectionSize on\off compiler switch */
#if (defined FEE_SMALL_SECTION_ENABLED)
#error FEE_SMALL_SECTION_ENABLED is already defined
#endif
[!IF "node:existsAndTrue(FeeEnableSmallSectionSize)"!][!//
#define FEE_SMALL_SECTION_ENABLED                      STD_ON
[!ELSE!]
#define FEE_SMALL_SECTION_ENABLED                      STD_OFF
[!ENDIF!]

/** \brief WriteCustom API on\off compiler switch */
#if (defined FEE_WRITE_CUSTOM_API)
#error FEE_WRITE_CUSTOM_API is already defined
#endif
[!IF "(node:existsAndTrue(FeeWriteCustomApi))"!][!//
#define FEE_WRITE_CUSTOM_API                         STD_ON
[!ELSE!]
#define FEE_WRITE_CUSTOM_API                         STD_OFF
[!ENDIF!]

/** \brief Fee_ReadCustom API on\off compiler switch */
#if (defined FEE_READ_CUSTOM_API)
#error FEE_READ_CUSTOM_API is already defined
#endif
[!IF "(node:existsAndTrue(FeeReadCustomApi))"!][!//
#define FEE_READ_CUSTOM_API                          STD_ON
[!ELSE!]
#define FEE_READ_CUSTOM_API                          STD_OFF
[!ENDIF!]

#if (defined FEE_CANCEL_SECTION_ERASE)
#error FEE_CANCEL_SECTION_ERASE is already defined
#endif
/** \brief CancelSectionErase API on\off compiler switch */
#define FEE_CANCEL_SECTION_ERASE                     [!//
[!IF "(node:existsAndTrue(FeeCancelSectionEraseApi))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_CRITICAL_BLOCK_NUMBER)
#error FEE_CRITICAL_BLOCK_NUMBER is already defined
#endif
/** \brief Critical block number */
#define FEE_CRITICAL_BLOCK_NUMBER                    [!"$CriticalBlockNumber"!]U

[!IF "(node:exists(FeeCriticalBlock))"!][!//
/** \brief Critical block size. */
#define FEE_CRITICAL_BLOCK_SIZE                      [!"$CriticalBlockSizeAl"!]U
[!ENDIF!]

#if (defined FEE_USE_BLANKCHECK)
#error FEE_USE_BLANKCHECK is already defined
#endif
/** \brief Blank Check usage on\off compiler switch */
#define FEE_USE_BLANKCHECK                     [!//
[!IF "(node:existsAndTrue(FeeUseBlankCheck))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Pattern for data consistency on\off compiler switch */
#if (defined FEE_CONSISTENCY_PATTERN_ENABLED)
#error FEE_CONSISTENCY_PATTERN_ENABLED is already defined
#endif
#define FEE_CONSISTENCY_PATTERN_ENABLED              [!//
[!IF "((node:existsAndTrue(FeeUseBlankCheck)) and (node:existsAndTrue(FeeConsistencyPattern)))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Size of management information for a block aligned to virtual page*/
#if (defined FEE_BLOCKSTAMP_SIZE_AL)
#error FEE_BLOCKSTAMP_SIZE_AL is already defined
#endif
#define FEE_BLOCKSTAMP_SIZE_AL         [!"num:integer($BlockStampSizeAl)"!]U

/** \brief Size of total management overhead info for a block (including the written marker)*/
#if (defined FEE_BLOCKINFO_SIZE)
#error FEE_BLOCKINFO_SIZE is already defined
#endif
#define FEE_BLOCKINFO_SIZE         [!"num:integer($BlockInfoSize)"!]U

/** \brief Number of reserved block info + written marker */
#if (defined FEE_MARGIN)
#error FEE_MARGIN is already defined
#endif
#define FEE_MARGIN                                      [!"num:integer($Margin)"!]U

/** \brief Nvm Job end notification function */
#if (defined FEE_NVM_JOB_END_NOTIFICATION)
#error FEE_NVM_JOB_END_NOTIFICATION is already defined
#endif
#define FEE_NVM_JOB_END_NOTIFICATION() [!//
[!IF "node:exists(FeeNvmJobEndNotification) and (FeeNvmJobEndNotification != '') and (FeeNvmJobEndNotification != 'NULL_PTR')"!]
  [!"FeeNvmJobEndNotification"!]()[!ELSE!] do {} while (0)
[!ENDIF!]

/** \brief Nvm Job error notification function */
#if (defined FEE_NVM_JOB_ERROR_NOTIFICATION)
#error FEE_NVM_JOB_ERROR_NOTIFICATION is already defined
#endif
#define FEE_NVM_JOB_ERROR_NOTIFICATION() [!//
[!IF "node:exists(FeeNvmJobErrorNotification) and (FeeNvmJobErrorNotification != '') and (FeeNvmJobErrorNotification != 'NULL_PTR')"!]
  [!"FeeNvmJobErrorNotification"!]()[!ELSE!] do {} while (0)
[!ENDIF!]

/** \brief Version info on\off compiler switch */
#if (defined FEE_VERSION_INFO_API)
#error FEE_VERSION_INFO_API is already defined
#endif
#define FEE_VERSION_INFO_API               [!//
[!IF "node:existsAndTrue(FeeVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Polling Mode on\off compiler switch */
#if (defined FEE_POLLING_MODE)
#error FEE_POLLING_MODE is already defined
#endif
#define FEE_POLLING_MODE                   [!//
[!IF "node:existsAndTrue(FeePollingMode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Development error detect on\off compiler switch */
#if (defined FEE_DEV_ERROR_DETECT)
#error FEE_DEV_ERROR_DETECT is already defined
#endif
#define FEE_DEV_ERROR_DETECT               [!//
[!IF "node:existsAndTrue(FeeDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Initialization production error detect on\off compiler switch */
#if (defined FEE_PROD_ERROR_DETECT)
#error FEE_PROD_ERROR_DETECT is already defined
#endif
#define FEE_PROD_ERROR_DETECT              [!//
[!IF "node:existsAndTrue(FeeProdErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Set mode on\off compiler switch */
#if (defined FEE_SET_MODE_SUPPORTED)
#error FEE_SET_MODE_SUPPORTED is already defined
#endif
#define FEE_SET_MODE_SUPPORTED             [!//
[!IF "node:existsAndTrue(FeeSetModeSupported)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief InstanceId of this module instance */
#if (defined FEE_INSTANCE_ID)
#error FEE_INSTANCE_ID is already defined
#endif
#define FEE_INSTANCE_ID                    [!"FeeIndex"!]U

/** \brief Compatibility with LowerLayer alignment */
#if (defined FEE_LOWERLAYER_ALIGNED)
#error FEE_LOWERLAYER_ALIGNED is already defined
#endif
#define FEE_LOWERLAYER_ALIGNED [!//
[!IF "(node:existsAndTrue(FeeUseBufferForJobs))"!]
  STD_ON[!ELSE!]STD_OFF
[!ENDIF!]

[!//
[!IF "(node:existsAndTrue(FeeUseBufferForJobs)) "!][!//
[!IF "(node:existsAndTrue(FeeMemAccUsage))"!][!//
#define FEE_ALIGNMENT_VALUE [!"node:value(node:ref(FeeBufferAlignmentValue)/MemAccBufferAlignmentValue)"!]U
[!ELSE!]

#define FEE_ALIGNMENT_VALUE 4U
[!ENDIF!]
[!ELSE!]

#define FEE_ALIGNMENT_VALUE 1U
[!ENDIF!]
/** \brief Macro to show if Enable Abort Erase functionality is available */
#if (defined FEE_ENABLE_ABORT_ERASE)
#error FEE_ENABLE_ABORT_ERASE is already defined
#endif
#define FEE_ENABLE_ABORT_ERASE             [!//
[!IF "node:existsAndTrue(FeeEnableAbortErase)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!]

/** \brief Macro to show if Fls_Cancel API is available */
#if (defined FEE_FLS_CANCEL_API)
#error FEE_FLS_CANCEL_API is already defined
#endif
#define FEE_FLS_CANCEL_API                 [!//
[!IF "(node:existsAndTrue(as:modconf('Fls')[1]/FlsGeneral/FlsCancelApi)) or (node:existsAndTrue(FeeGeneral/FeeMemAccUsage))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "node:exists(as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_FLASH_ACCESSIBLE) and (as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_FLASH_ACCESSIBLE != '') and (as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_FLASH_ACCESSIBLE != 'NULL_PTR')"!][!//
/** \brief Flash accessible Dem event Id */
#if (defined FEE_E_FLASH_ACCESSIBLE_DEM_EVENT_ID)
#error FEE_E_FLASH_ACCESSIBLE_DEM_EVENT_ID is already defined
#endif
#define FEE_E_FLASH_ACCESSIBLE_DEM_EVENT_ID    [!//
[!"num:i(node:ref(as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_FLASH_ACCESSIBLE)/DemEventId)"!]U
[!ENDIF!]

[!IF "node:exists(as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_DATA_RECOVERED) and (as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_DATA_RECOVERED != '') and (as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_DATA_RECOVERED != 'NULL_PTR')"!][!//
/** \brief Flash Data Recovered Dem event Id */
#if (defined FEE_E_DATA_RECOVERED_DEM_EVENT_ID)
#error FEE_E_DATA_RECOVERED_DEM_EVENT_ID is already defined
#endif
#define FEE_E_DATA_RECOVERED_DEM_EVENT_ID      [!//
[!"num:i(node:ref(as:modconf('Fee')[1]/FeeDemEventParameterRefs/FEE_E_DATA_RECOVERED)/DemEventId)"!]U
[!ENDIF!]

[!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!]
[!SELECT "as:modconf('Fls')[1]/FlsPublishedInformation"!]
/** \brief Erase value of flash */
#if (defined FEE_FLASH_ERASE_VALUE)
#error FEE_FLASH_ERASE_VALUE is already defined
#endif
#define FEE_FLASH_ERASE_VALUE                  [!"num:inttohex(FlsErasedValue, 2)"!]U

/** \brief Value to fill unused bytes */
#if (defined FEE_PAD_BYTE)
#error FEE_PAD_BYTE is already defined
#endif
#define FEE_PAD_BYTE                           (uint8)(~FEE_FLASH_ERASE_VALUE)

/** \brief Value to indicate Erased section */
#if (defined FEE_SECTION_STATUS_ERASED)
#error FEE_SECTION_STATUS_ERASED is already defined
#endif
#define FEE_SECTION_STATUS_ERASED              [!"num:inttohex(FlsErasedValue, 2)"!][!"substring-after(num:inttohex(FlsErasedValue, 2),'0x')"!]U

/** \brief Value to indicate Erased section */
#if (defined FEE_SECTION_STATUS_ERASED_COUNTER)
#error FEE_SECTION_STATUS_ERASED_COUNTER is already defined
#endif
#define FEE_SECTION_STATUS_ERASED_COUNTER      [!"num:inttohex(FlsErasedValue, 2)"!][!"substring-after(num:inttohex(FlsErasedValue, 2),'0x')"!][!/*
*/!][!"substring-after(num:inttohex(FlsErasedValue, 2),'0x')"!][!"substring-after(num:inttohex(FlsErasedValue, 2),'0x')"!]U
[!ENDSELECT!]
[!ELSE!][!//
/** \brief Erase value of flash */
#if (defined FEE_FLASH_ERASE_VALUE)
#error FEE_FLASH_ERASE_VALUE is already defined
#endif
#define FEE_FLASH_ERASE_VALUE                  (uint8)[!"FeeGeneral/FeeDriverErasedValue"!]U

/** \brief Value to fill unused bytes */
#if (defined FEE_PAD_BYTE)
#error FEE_PAD_BYTE is already defined
#endif
#define FEE_PAD_BYTE                           (uint8)(~FEE_FLASH_ERASE_VALUE)

/** \brief Value to indicate Erased section */
#if (defined FEE_SECTION_STATUS_ERASED)
#error FEE_SECTION_STATUS_ERASED is already defined
#endif
#define FEE_SECTION_STATUS_ERASED              (uint8)0xFFU

/** \brief Value to indicate Erased section */
#if (defined FEE_SECTION_STATUS_ERASED_COUNTER)
#error FEE_SECTION_STATUS_ERASED_COUNTER is already defined
#endif
#define FEE_SECTION_STATUS_ERASED_COUNTER      (uint8)0xFFU
[!ENDIF!]


/* -----------[Symbolic names for the Fee blocks]--------------------------- */

[!LOOP "FeeBlockConfiguration/eb-list::*"!][!//
/** \brief Symbolic name for the FEE Block number [!"FeeBlockNumber"!]" */
#define FeeConf_FeeBlockConfiguration_[!"as:name(.)"!]   [!"FeeBlockNumber"!]U

#ifndef FEE_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define [!"as:name(.)"!]   [!"FeeBlockNumber"!]U
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Fee_[!"as:name(.)"!] [!"FeeBlockNumber"!]U
#endif /* ifndef FEE_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

[!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!]
/* !LINKSTO Fee.VendorInfixDriver.Support,1 */
[!IF "(node:exists(as:modconf('Fls')[1]/CommonPublishedInformation/VendorApiInfix)) and (not(as:modconf('Fls')[1]/CommonPublishedInformation/VendorApiInfix = ''))"!][!//
/*------------------------[Driver Vendor APIs]------------------------------*/
#define Fee_LowerLayer_Write Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_Write
[!IF "((node:exists(FeeGeneral/FeeFlsReadApiType)) and (FeeGeneral/FeeFlsReadApiType = 'Fls_ReadImmediate'))"!]
#define Fee_LowerLayer_Read Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_ReadImmediate
[!ELSE!][!//
#define Fee_LowerLayer_Read Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_Read
[!ENDIF!]
[!IF "node:existsAndTrue(as:modconf('Fls')[1]/FlsGeneral/FlsCancelApi)"!]
#define Fee_LowerLayer_Cancel Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_Cancel
[!ENDIF!]
#define Fee_LowerLayer_GetJobResult Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_GetJobResult
#define Fee_LowerLayer_GetStatus Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_GetStatus
[!IF "node:existsAndTrue(FeeGeneral/FeeSetModeSupported)"!]
#define Fee_LowerLayer_SetMode Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_SetMode
[!ENDIF!]
#define Fee_LowerLayer_Erase Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_Erase
#define Fee_LowerLayer_BlankCheck Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_BlankCheck

/*data types*/
typedef Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_AddressType Fee_LowerLayer_AddressType;
typedef Fls_[!"$VendorId"!]_[!"$VendorApiInfix"!]_LengthType Fee_LowerLayer_LengthType;
[!ELSE!][!//

[!IF "node:existsAndTrue(FeeGeneral/FeeSetModeSupported)"!]
/** \brief Macro to call Fls_SetMode API, if available */
#if (defined Fee_LowerLayer_SetMode)
#error Fee_LowerLayer_SetMode is already defined
#endif
#define Fee_LowerLayer_SetMode(Mode) (Fls_SetMode((Mode)))
[!ENDIF!]
[!IF "node:existsAndTrue(as:modconf('Fls')[1]/FlsGeneral/FlsCancelApi)"!]
#define Fee_LowerLayer_Cancel Fls_Cancel
[!ENDIF!]
#define Fee_LowerLayer_Write Fls_Write
[!IF "((node:exists(FeeGeneral/FeeFlsReadApiType)) and (FeeGeneral/FeeFlsReadApiType = 'Fls_ReadImmediate'))"!]
#define Fee_LowerLayer_Read Fls_ReadImmediate
[!ELSE!][!//
#define Fee_LowerLayer_Read Fls_Read
[!ENDIF!]
#define Fee_LowerLayer_GetJobResult Fls_GetJobResult
#define Fee_LowerLayer_GetStatus Fls_GetStatus
#define Fee_LowerLayer_Erase Fls_Erase
#define Fee_LowerLayer_BlankCheck Fls_BlankCheck
/*data types*/
typedef Fls_AddressType Fee_LowerLayer_AddressType;
typedef Fls_LengthType Fee_LowerLayer_LengthType;
[!ENDIF!][!//
[!ELSE!][!//
/* !LINKSTO Fee.FeeMemAccUsage.ApiCompliance,1 */
#define FEE_MEMACC_AREA_ID [!"node:value(node:ref(FeeGeneral/FeeBufferAlignmentValue)/MemAccAddressAreaId)"!]U

#define Fee_LowerLayer_Write(a,b,c) MemAcc_Write(FEE_MEMACC_AREA_ID, (a), (b), (c))
#define Fee_LowerLayer_Read(a,b,c) MemAcc_Read(FEE_MEMACC_AREA_ID, (a), (b), (c))
#define Fee_LowerLayer_GetJobResult() Fee_MemAcc_GetConsolidatedJobResult()
#define Fee_LowerLayer_GetStatus() MemAcc_GetJobStatus(FEE_MEMACC_AREA_ID)
#define Fee_LowerLayer_Cancel() MemAcc_Cancel(FEE_MEMACC_AREA_ID)
#define Fee_LowerLayer_Erase(a,b) MemAcc_Erase(FEE_MEMACC_AREA_ID, (a), (b))
#define Fee_LowerLayer_BlankCheck(a,b) MemAcc_BlankCheck(FEE_MEMACC_AREA_ID, (a), (b))
/*data types*/
typedef MemAcc_AddressType Fee_LowerLayer_AddressType;
typedef MemAcc_LengthType Fee_LowerLayer_LengthType;
[!ENDIF!][!//
/** \brief Macro to call Fee_LowerLayer_Cancel API, if available */
#if (defined FEE_CANCEL_FLASHJOB)
#error FEE_CANCEL_FLASHJOB is already defined
#endif
#define FEE_CANCEL_FLASHJOB() \
  do\
  {\
[!IF "((node:existsAndTrue(as:modconf('Fls')[1]/FlsGeneral/FlsCancelApi)) or (node:existsAndTrue(FeeGeneral/FeeMemAccUsage)))"!]
    Fee_Gv.FeeFlashJobResult = MEMIF_JOB_CANCELED;\
    Fee_LowerLayer_Cancel();\
[!ENDIF!]
  }while(0)
/*------------------[Defensive programming]---------------------------------*/
[!SELECT "FeeDefensiveProgramming"!][!//

#if (defined FEE_DEFENSIVE_PROGRAMMING_ENABLED)
#error FEE_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define FEE_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_PRECONDITION_ASSERT_ENABLED)
#error FEE_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define FEE_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled)) and (node:existsAndTrue(FeePrecondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_POSTCONDITION_ASSERT_ENABLED)
#error FEE_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define FEE_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled)) and (node:existsAndTrue(FeePostcondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_UNREACHABLE_CODE_ASSERT_ENABLED)
#error FEE_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define FEE_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled)) and (node:existsAndTrue(FeeUnreachAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_INVARIANT_ASSERT_ENABLED)
#error FEE_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define FEE_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled)) and (node:existsAndTrue(FeeInvariantAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined FEE_STATIC_ASSERT_ENABLED)
#error FEE_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define FEE_STATIC_ASSERT_ENABLED           [!//
[!IF "(node:existsAndTrue(../FeeGeneral/FeeDevErrorDetect)) and (node:existsAndTrue(FeeDefProgEnabled)) and (node:existsAndTrue(FeeStaticAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


/*==================[type definitions]======================================*/

/** \brief This type represents the current state of the FEE module */
typedef uint8 Fee_State_t;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/** \brief This type represents the current state of the FEE module */
#define  FEE_STATE_INVALID                             (Fee_State_t)255               /**< Invalid state */
#define  FEE_UNINIT                                    (Fee_State_t)0                 /**< unitialized state state */
#define  FEE_IDLE                                      (Fee_State_t)1                 /**< Idle state */
#define  FEE_INIT_READ_HEADER                          (Fee_State_t)2                 /**< Read Section Header state */
#define  FEE_INIT_READ_FOOTER                          (Fee_State_t)3                 /**< Read Section Footer state */
#define  FEE_READ_BLOCKDATA                            (Fee_State_t)4                 /**< Read block data state */
#define  FEE_WRITE_BLOCK_INFO                          (Fee_State_t)5                 /**< write block info state */
#define  FEE_WRITE_BLOCK_DATA                          (Fee_State_t)6                 /**< write block data state */
#define  FEE_WRITTEN_MARKER                            (Fee_State_t)7                 /**< write written marker state */
#define  FEE_SS_WRITTEN_MARKER                         (Fee_State_t)8                /**< write written marker during a swtich operation state */
#define  FEE_MARK_HEADER_ACTIVE                        (Fee_State_t)9                /**< Write Active marker in header state */
#define  FEE_MARK_FOOTER_ACTIVE                        (Fee_State_t)10                /**< Write Activer marker in footer state */
#define  FEE_MARK_HEADER_ERASABLE                      (Fee_State_t)11                /**< Write Erasable marker in header state */
#define  FEE_MARK_FOOTER_ERASABLE                      (Fee_State_t)12                /**< Write Erasable marker in footer state */
#define  FEE_WRITE_SECTION_HEADER                      (Fee_State_t)13                /**< Write section information in header state */
#define  FEE_WRITE_SECTION_FOOTER                      (Fee_State_t)14                /**< Write section information in footer state */
#define  FEE_SS_COPY_INFO                              (Fee_State_t)15                /**< Copy block info during switch state */
#define  FEE_SS_READ_DATA                              (Fee_State_t)16                /**< Read data during switch state */
#define  FEE_SS_COPY_DATA                              (Fee_State_t)17                /**< Copy block data during switch state */
#define  FEE_ERASE_SECTION                             (Fee_State_t)18                /**< Erase a section state */
#define  FEE_STATE_WAIT_A_CYCLE                        (Fee_State_t)19                /**< Retry state */
#define  FEE_TRIGGER_JOB_OR_INTERNAL                   (Fee_State_t)20                /**< Trigger a job or an internal operation state */
[!SELECT "FeeGeneral"!]
[!VAR "StateNumber" = "20"!][!//
[!IF "(node:existsAndTrue(FeeUseBlankCheck))"!]
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_HEADER                        (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check header state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_FOOTER                        (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check footer state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_HEADER_ACTIVE                 (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check header's Active marker state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_FOOTER_ACTIVE                 (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check footer's Active marker state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_HEADER_ERASABLE               (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check header's Erasable marker state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_FOOTER_ERASABLE               (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check footer's Erasable marker state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_W_MARKER                      (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check written marker state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_BLANK_CHECK_BLOCK_STAMP                   (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Blank-check block stamp state */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_READ_BLOCK_STAMP                          (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Read block stamp state */
[!IF "(node:existsAndTrue(FeeConsistencyPattern))"!]
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_WRITE_HEADER_ERASE_COUNTER_END_PATTERN    (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Write header erase counter end patter */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_WRITE_FOOTER_ERASE_COUNTER_END_PATTERN    (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Write footer erase counter end patter */
[!ENDIF!]
[!ELSE!]
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_INIT_FILL_CACHE                           (Fee_State_t)[!"num:integer($StateNumber)"!]                 /**< Fills the cashe during init */
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_INIT_BLOCK_BY_BLOCK                       (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Initialize the cashe reading block by block info */
[!ENDIF!]
[!IF "$CriticalBlockNumber > 0"!][!//
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_CRITICAL_FROZEN                           (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Frozen state */
[!ENDIF!]
[!IF "(node:existsAndTrue(FeeMemAccUsage))"!][!//
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_CANCEL_ONGOING                           (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< Frozen state */
[!ENDIF!]
  [!VAR "StateNumber" = "$StateNumber + 1"!][!//
#define  FEE_NUM_STATES                                (Fee_State_t)[!"num:integer($StateNumber)"!]                /**< number of states */
[!ENDSELECT!][!//
/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* #ifndef FEE_CFG_H */
