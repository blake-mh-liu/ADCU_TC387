[!/**
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
 */!][!//
[!VAR "FEE_CHECKS.M" = "'true'"!][!//
[!//
[!//
[!VAR "Margin" = "num:integer(4)"!][!//number of block infos (block stamp + written marker) between data and block info
[!//
[!//
[!MACRO "GetAlignedSize", "DataSize", "Alignment"!][!//
[!INDENT "0"!][!//
  [!"num:integer($DataSize + (($Alignment - ($DataSize mod $Alignment)) mod $Alignment))"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!//
[!VAR "ConfigBlocksTotalSizeAl" = "num:integer(0)"!][!//size used for all config blocks(data aligned to virtual page + block info)
[!VAR "NotConfigBlocksTotalSizeAl" = "num:integer(0)"!][!//size used for all notconfig blocks(data aligned to virtual page + block info)
[!VAR "BlocksTotalSizeAl" = "num:integer(0)"!][!//size used for all blocks(config+notconfig) aligned to virtual page
[!VAR "BufferSize" = "num:integer(0)"!][!//
[!VAR "InitBufferSize" = "num:integer(0)"!][!//
[!VAR "VirPageSize" = "FeeGeneral/FeeVirtualPageSize"!][!//
[!VAR "WrittenMarkerSize" = "$VirPageSize"!][!//
[!//
[!//
[!IF "node:exists(FeeGeneral/FeeNumberOfNotConfigBlocks)"!][!//
  [!VAR "NumberOfNotConfigBlocks" = "num:integer(FeeGeneral/FeeNumberOfNotConfigBlocks)"!][!//
  [!VAR "NotConfigBlocksDataSize" = "num:integer(FeeGeneral/FeeDataSizeNotConfiguredBlocks)"!][!//
[!ELSE!][!//
  [!VAR "NumberOfNotConfigBlocks" = "num:integer(0)"!][!//
  [!VAR "NotConfigBlocksDataSize" = "num:integer(0)"!][!//
[!ENDIF!][!//
[!//
[!//
[!IF "node:exists(FeeGeneral/FeeCriticalBlock)"!][!//
  [!VAR "CriticalBlockNumber" = "num:integer(node:ref(FeeGeneral/FeeCriticalBlock)/FeeBlockNumber)"!][!//
  [!VAR "CriticalBlockSize" = "num:integer(node:ref(FeeGeneral/FeeCriticalBlock)/FeeBlockSize)"!][!//
  [!VAR "CriticalBlockSizeAl"!][!INDENT "0"!][!//
     [!CALL "GetAlignedSize", "DataSize" = "$CriticalBlockSize", "Alignment" = "$VirPageSize"!][!//
  [!ENDINDENT!][!ENDVAR!][!//
[!ELSE!][!//
  [!VAR "CriticalBlockNumber" = "num:integer(0)"!][!//
[!ENDIF!][!//
[!//
[!//
[!IF "$VirPageSize > 2"!][!//
  [!VAR "HeaderStatusFieldSize" = "num:integer($VirPageSize)"!][!//
[!ELSE!][!//
  [!VAR "HeaderStatusFieldSize" = "num:integer(2)"!][!//
[!ENDIF!][!//
[!VAR "ECounterCrc" = "num:integer(1)"!][!//
[!VAR "CidCrc" = "num:integer(1)"!][!//
[!VAR "HeaderConfigId" = "num:integer(1)"!][!//
[!VAR "HeaderCounter" = "num:integer(1)"!][!//
[!VAR "HeaderEraseCounter" = "num:integer(4)"!][!//
[!VAR "SectionManagementObjectSize" = "num:integer($ECounterCrc + $HeaderConfigId + $HeaderEraseCounter + $HeaderCounter + $CidCrc)"!][!//
[!VAR "SectionManagementObjectSizeAl"!][!INDENT "0"!][!//
  [!CALL "GetAlignedSize", "DataSize" = "$SectionManagementObjectSize", "Alignment"= "$VirPageSize"!][!//
[!ENDINDENT!][!ENDVAR!][!//
[!VAR "HeaderSize" = "num:integer(2 * $HeaderStatusFieldSize + $SectionManagementObjectSizeAl)"!][!//
[!//
[!//
[!IF "((node:existsAndTrue(FeeGeneral/FeeUseBlankCheck)) and (node:existsAndTrue(FeeGeneral/FeeConsistencyPattern)))"!][!//
  [!VAR "EndPatternSize" = "$VirPageSize"!][!//
[!ELSE!][!//
  [!VAR "EndPatternSize" = "num:integer(0)"!][!//
[!ENDIF!][!//
[!//
[!//
[!VAR "BlockStampSizeAl"!][!INDENT "0"!][!//
  [!CALL "GetAlignedSize", "DataSize" = "10", "Alignment" = "$VirPageSize"!][!//
[!ENDINDENT!][!ENDVAR!][!//
[!//
[!//
[!VAR "SectionManagementOverhead" = "$HeaderSize + $EndPatternSize"!][!//
[!//
[!//
[!VAR "BlockInfoSize" = "num:integer($BlockStampSizeAl + $WrittenMarkerSize)"!][!//
[!VAR "MarginSize" = "$Margin * $BlockInfoSize"!][!//
[!//
[!//
[!MACRO "GetBlockTotalSizeInSection", "BlockDataSize", "LocalVarDoNotSet" = "0"!][!//
[!INDENT "0"!][!//
  [!VAR "LocalVarDoNotSet"!][!//
    [!CALL "GetAlignedSize", "DataSize" = "$BlockDataSize", "Alignment" = "$VirPageSize"!] [!//
  [!ENDVAR!][!//
  [!"num:integer($LocalVarDoNotSet + $BlockInfoSize)"!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!//
[!//
[!//
[!VAR "TotalFlashSize" = "0"!][!//
[!VAR "Section0StartAddress" = "0"!][!//
[!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!][!//
[!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector)"!][!//
[!VAR "NumberOfDataSectors" = "num:integer(count(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*[((node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR'))]))"!][!//
[!VAR "ConsecutiveDataFlashSectors" = "0"!][!//
[!VAR "TotalNumberOfConsecutiveSectors" = "0"!][!//
[!/* In case of other Fls driver implementations, take into consideration all flash sectors */!][!//
[!LOOP "as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*"!][!//
  [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*/FlsSectorOption)"!][!//
    [!IF "FlsSectorOption = 'FLS_DF_SECTOR'"!][!//
      [!IF "$ConsecutiveDataFlashSectors = 0"!][!//
        [!VAR "Section0StartAddress" = "FlsSectorStartaddress"!][!//
      [!ENDIF!][!//
      [!VAR "TotalFlashSize" = "$TotalFlashSize + (FlsNumberOfSectors * FlsSectorSize)"!][!//
      [!VAR "ConsecutiveDataFlashSectors" = "$ConsecutiveDataFlashSectors + 1"!][!//
      [!VAR "TotalNumberOfConsecutiveSectors" = "$TotalNumberOfConsecutiveSectors + FlsNumberOfSectors"!][!//
    [!ELSE!][!//
      [!ASSERT "(($ConsecutiveDataFlashSectors = 0) or ($ConsecutiveDataFlashSectors >= $NumberOfDataSectors))", "Configured data flash sectors are not consecutive! Please check your configuration."!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "TotalFlashSize" = "$TotalFlashSize + (FlsNumberOfSectors * FlsSectorSize)"!][!//
    [!VAR "TotalNumberOfConsecutiveSectors" = "sum(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*/FlsNumberOfSectors)"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!//
[!/********************** Calculation of section 0 and section 1 size ***************************/!][!//
[!VAR "Section0size" = "0"!][!//
[!VAR "Flag" = "0"!][!//
[!VAR "SectorIndex" = "0"!][!//
[!LOOP "as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*"!][!//
  [!/* Check if FlsSectorOption parameter exists and if the current sector is a data flash sector OR use all configured flash sectors */!][!//
  [!IF "((($NumberOfDataSectors > 0) and (node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR')) or ((not(node:exists(FlsSectorOption))) and ($NumberOfDataSectors = 0)))"!][!//
    [!FOR "i" = "1" TO "FlsNumberOfSectors"!][!//
      [!VAR "SectorIndex" = "$SectorIndex + 1"!][!//
      [!IF "($SectorIndex = $TotalNumberOfConsecutiveSectors) or ($Section0size >= ($TotalFlashSize div 2))"!][!//
        [!VAR "Flag" = "1"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "Section0size" = "$Section0size + FlsSectorSize"!][!//
    [!ENDFOR!][!//
    [!IF "$Flag = 1"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ELSEIF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector)"!][!//
[!VAR "NumberOfDataSectors" = "num:integer(count(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*[((node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR'))]))"!][!//
[!VAR "ConsecutiveDataFlashSectors" = "0"!][!//
[!VAR "TotalNumberOfConsecutiveSectors" = "0"!][!//
[!/* In case of other Fls driver implementations, take into consideration all flash sectors */!][!//
[!LOOP "as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*"!][!//
  [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*/FlsSectorOption)"!][!//
    [!IF "FlsSectorOption = 'FLS_DF_SECTOR'"!][!//
      [!IF "$ConsecutiveDataFlashSectors = 0"!][!//
        [!VAR "Section0StartAddress" = "FlsSectorStartaddress"!][!//
      [!ENDIF!][!//
      [!VAR "TotalFlashSize" = "$TotalFlashSize + (FlsNumberOfSectors * FlsSectorSize)"!][!//
      [!VAR "ConsecutiveDataFlashSectors" = "$ConsecutiveDataFlashSectors + 1"!][!//
      [!VAR "TotalNumberOfConsecutiveSectors" = "$TotalNumberOfConsecutiveSectors + FlsNumberOfSectors"!][!//
    [!ELSE!][!//
      [!ASSERT "(($ConsecutiveDataFlashSectors = 0) or ($ConsecutiveDataFlashSectors >= $NumberOfDataSectors))", "Configured data flash sectors are not consecutive! Please check your configuration."!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "TotalFlashSize" = "$TotalFlashSize + (FlsNumberOfSectors * FlsSectorSize)"!][!//
    [!VAR "TotalNumberOfConsecutiveSectors" = "sum(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*/FlsNumberOfSectors)"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!/********************** Calculation of section 0 and section 1 size ***************************/!][!//
[!VAR "Section0size" = "0"!][!//
[!VAR "Flag" = "0"!][!//
[!VAR "SectorIndex" = "0"!][!//
[!LOOP "as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*"!][!//
  [!/* Check if FlsSectorOption parameter exists and if the current sector is a data flash sector OR use all configured flash sectors */!][!//
  [!IF "((($NumberOfDataSectors > 0) and (node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR')) or ((not(node:exists(FlsSectorOption))) and ($NumberOfDataSectors = 0)))"!][!//
    [!FOR "i" = "1" TO "FlsNumberOfSectors"!][!//
      [!VAR "SectorIndex" = "$SectorIndex + 1"!][!//
      [!IF "($SectorIndex = $TotalNumberOfConsecutiveSectors) or ($Section0size >= ($TotalFlashSize div 2))"!][!//
        [!VAR "Flag" = "1"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
      [!VAR "Section0size" = "$Section0size + FlsSectorSize"!][!//
    [!ENDFOR!][!//
    [!IF "$Flag = 1"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
[!ERROR!][!//
/* FlsSector not configured or incompatible Fee/Fls implementation */[!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!VAR "Section1size" = "$TotalFlashSize - $Section0size"!][!//
[!VAR "Section1StartAddress" = "$Section0StartAddress + $Section0size"!][!//
[!//
[!/***********************Calculate Section Size For AutoGeneration ********************/!][!//
[!VAR "GenericSectionSize" = "0"!][!//
  [!IF "node:existsAndTrue(as:modconf('Fee')[1]/FeeGeneral/EnableAutoSectionGeneration)"!][!//
    [!IF "TotalFlashSize mod as:modconf('Fee')[1]/FeeGeneral/FeeNumberOfSections != 0"!][!//
      [!/* !LINKSTO Fee.Sections.NumberOfSections.Validate,1 */!][!//
      [!ERROR "Available FLS Flash could not be split into equal sections. Please disable EnableAutoSectionGeneration and configure the FEE sections manually! A"!][!//
    [!ELSE!][!//
      [!VAR "GenericSectionSize" = "$TotalFlashSize div as:modconf('Fee')[1]/FeeGeneral/FeeNumberOfSections"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!//
[!/***********************Endif for MemAcc ussage ********************/!][!//
[!ENDIF!][!//
[!/***********************Config ID calculation ********************/!][!//
[!VAR "ConfigId" = "0"!][!//
[!MACRO "ConfigIdCalculus", "Parameter"!][!//
  [!VAR "ParameterInInt" = "$Parameter"!][!//
  [!VAR "ParameterInHex" = "num:inttohex($ParameterInInt,8)"!][!//
  [!FOR "i" = "0" TO "3"!][!//
    [!VAR "ConfigId" = "bit:and($ConfigId * 37 + num:hextoint(substring( $ParameterInHex, 2*$i+3, 2 )),255)"!][!//
  [!ENDFOR!][!//
[!ENDMACRO!][!//
[!//
[!IF "node:existsAndTrue(as:modconf('Fee')[1]/FeeGeneral/EnableAutoSectionGeneration)"!][!//
[!CALL "ConfigIdCalculus", "Parameter" = "$TotalFlashSize"!][!//
[!ELSE!][!//
  [!LOOP "as:modconf('Fee')[1]/FeeGeneral/FeeSectionConfiguration/eb-list::*"!][!//
    [!CALL "ConfigIdCalculus", "Parameter" = "FeeSectionStartAddress"!][!//
    [!CALL "ConfigIdCalculus", "Parameter" = "FeeSectionSize"!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//
[!CALL "ConfigIdCalculus", "Parameter" = "FeeGeneral/FeeVirtualPageSize"!][!//
[!CALL "ConfigIdCalculus", "Parameter" = "FeeGeneral/FeeNumberOfSections"!][!//
[!//
[!VAR "ConfigId_Legacy" = "$ConfigId"!][!//
[!VAR "ConfigId" = "0"!][!//
[!IF "node:existsAndTrue(as:modconf('Fee')[1]/FeeGeneral/EnableAutoSectionGeneration)"!][!//
  [!VAR "SectionSize" = "0"!][!//
  [!VAR "SectionStartAddress" = "0"!][!//
  [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector)"!][!//
    [!LOOP "as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector/eb-list::*"!][!//
       [!IF "((($NumberOfDataSectors > 0) and (node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR')) or ((not(node:exists(FlsSectorOption))) and ($NumberOfDataSectors = 0)))"!][!//
         [!FOR "i" = "1" TO "FlsNumberOfSectors"!][!//
           [!VAR "SectionSize" = "$SectionSize + FlsSectorSize"!][!//
           [!IF "$SectionSize = $GenericSectionSize"!][!//
             [!CALL "ConfigIdCalculus", "Parameter" = "num:integer($SectionStartAddress)"!][!//
             [!CALL "ConfigIdCalculus", "Parameter" = "num:integer($SectionSize)"!][!//
             [!VAR "SectionStartAddress" = "$SectionStartAddress + $SectionSize"!][!//
             [!VAR "SectionSize" = "0"!][!//
           [!ENDIF!][!//
         [!ENDFOR!][!//
       [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ELSE!][!//
    [!LOOP "as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/eb-list::*"!][!//
       [!IF "((($NumberOfDataSectors > 0) and (node:exists(FlsSectorOption)) and (FlsSectorOption = 'FLS_DF_SECTOR')) or ((not(node:exists(FlsSectorOption))) and ($NumberOfDataSectors = 0)))"!][!//
         [!FOR "i" = "1" TO "FlsNumberOfSectors"!][!//
           [!VAR "SectionSize" = "$SectionSize + FlsSectorSize"!][!//
           [!IF "$SectionSize = $GenericSectionSize"!][!//
             [!CALL "ConfigIdCalculus", "Parameter" = "num:integer($SectionStartAddress)"!][!//
             [!CALL "ConfigIdCalculus", "Parameter" = "num:integer($SectionSize)"!][!//
             [!VAR "SectionStartAddress" = "$SectionStartAddress + $SectionSize"!][!//
             [!VAR "SectionSize" = "0"!][!//
           [!ENDIF!][!//
         [!ENDFOR!][!//
       [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!LOOP "as:modconf('Fee')[1]/FeeGeneral/FeeSectionConfiguration/eb-list::*"!][!//
    [!CALL "ConfigIdCalculus", "Parameter" = "FeeSectionStartAddress"!][!//
    [!CALL "ConfigIdCalculus", "Parameter" = "FeeSectionSize"!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//
[!CALL "ConfigIdCalculus", "Parameter" = "FeeGeneral/FeeVirtualPageSize"!][!//
[!CALL "ConfigIdCalculus", "Parameter" = "FeeGeneral/FeeNumberOfSections"!][!//
[!//
[!/***********************Calculation of Space required for switch operation ********************/!][!//
[!/* !LINKSTO Fee.Configuration.TotalBlocksSize,1, Fee.Configuration.TotalBlocksSize.SwitchNotConfiguredBlocks,1 */!][!//
[!LOOP "FeeBlockConfiguration/eb-list::*"!][!//
  [!VAR "BlockTotalSizeAl"!][!INDENT "0"!][!//
    [!CALL "GetBlockTotalSizeInSection", "BlockDataSize" = "FeeBlockSize"!][!//
  [!ENDINDENT!][!ENDVAR!][!//
  [!VAR "ConfigBlocksTotalSizeAl" = "$ConfigBlocksTotalSizeAl + $BlockTotalSizeAl"!][!//
[!ENDLOOP!][!//
[!IF "(node:exists(FeeGeneral/FeeImmediateSpaceReserved))"!][!//
  [!IF "(FeeGeneral/FeeImmediateSpaceReserved = 0)"!][!//
    [!VAR "ImmediateSpaceReserved" = "num:integer(0)"!]
    [!LOOP "FeeBlockConfiguration/eb-list::*"!][!//
      [!IF "node:existsAndTrue(FeeImmediateData)"!][!//
        [!VAR "ImmediateBlockSpace"!][!INDENT "0"!][!//
          [!CALL "GetBlockTotalSizeInSection", "BlockDataSize" = "FeeBlockSize"!][!//
        [!ENDINDENT!][!ENDVAR!][!//
        [!VAR "ImmediateSpaceReserved" = "num:integer($ImmediateSpaceReserved + $ImmediateBlockSpace)"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ELSE!][!//
      [!VAR "ImmediateSpaceReserved" = "FeeGeneral/FeeImmediateSpaceReserved"!]
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "ImmediateSpaceReserved" = "num:integer(0)"!]
[!ENDIF!][!//
[!//
[!//
[!IF "node:exists(FeeGeneral/FeeNumberOfNotConfigBlocks)"!][!//
  [!/* worst case: each not cfg block is a multiple of VirtPage + 1 byte
       DataSize = Sum{i=0->NumberOfNotConfigBlocks | FullPagesBlock(i) + 1 }
       if (Data Size - number_of_blocks) is not aligned => one page we assumed full, has some unused bytes
       in which one byte will be put
   */!][!//
  [!VAR "NotConfigBlocksDataSizeMoreBytesPagesAl"!][!INDENT "0"!][!//
    [!CALL "GetAlignedSize", "DataSize" = "($NotConfigBlocksDataSize - $NumberOfNotConfigBlocks)", "Alignment"= "$VirPageSize"!][!//
  [!ENDINDENT!][!ENDVAR!][!//
  [!IF "$NotConfigBlocksDataSizeMoreBytesPagesAl + $NumberOfNotConfigBlocks = $NotConfigBlocksDataSize"!][!//
    [!VAR "Max1BytePages" = "$NumberOfNotConfigBlocks"!][!//
  [!ELSE!][!//
    [!VAR "Max1BytePages" = "$NumberOfNotConfigBlocks - 1"!][!//
  [!ENDIF!][!//
  [!VAR "NotConfigBlocksTotalSizeAl" = "$NotConfigBlocksDataSizeMoreBytesPagesAl + $Max1BytePages * $VirPageSize"!][!//
  [!VAR "NotConfigBlocksTotalSizeAl" = "num:integer($NotConfigBlocksTotalSizeAl + $NumberOfNotConfigBlocks * ($BlockInfoSize))"!][!//
[!ENDIF!][!//
[!//
[!VAR "BlocksTotalSizeAl" = "num:integer($ConfigBlocksTotalSizeAl + $NotConfigBlocksTotalSizeAl)"!][!//
[!//
[!IF "count(FeeBlockConfiguration/eb-list::*) > 0"!][!//
  [!VAR "LargestBlockSize" = "num:max(FeeBlockConfiguration/eb-list::*/FeeBlockSize)"!][!//
[!ELSE!][!//
  [!VAR "LargestBlockSize" = "0"!][!//
[!ENDIF!][!//
[!//
[!VAR "LargestBlockSizeInSection"!][!INDENT "0"!][!//
  [!CALL "GetBlockTotalSizeInSection", "BlockDataSize" = "$LargestBlockSize"!][!//
[!ENDINDENT!][!ENDVAR!][!//
[!//
[!//
[!VAR "SmallestBufferSize" = "num:i(num:max(text:split(concat(($SectionManagementOverhead),' ',$BlockInfoSize))))"!][!//
[!/* !LINKSTO Fee.Configuration.FeeBuffer,1 */!][!//
[!IF "node:exists(FeeGeneral/FeeBufferSize) and (not(node:exists(FeeGeneral/FeeUseBufferForJobs)) or (node:existsAndFalse(FeeGeneral/FeeUseBufferForJobs)))"!][!//
  [!IF "FeeGeneral/FeeBufferSize < number($SmallestBufferSize)"!][!//
    [!ERROR!] Configured buffer size is smaller than the minimum size needed. It should be at least [!"$SmallestBufferSize"!].[!ENDERROR!][!//
  [!ENDIF!][!//
  [!IF "FeeGeneral/FeeBufferSize mod FeeGeneral/FeeVirtualPageSize != 0"!][!//
    [!ERROR!] Buffer Size must be multiple of VirtualPage.[!ENDERROR!][!//
  [!ENDIF!][!//
  [!VAR "BufferSize" = "FeeGeneral/FeeBufferSize"!][!//
  [!VAR "TruncBufferSize" = "num:i($BufferSize div $BlockInfoSize) * num:i($BlockInfoSize)"!][!//
[!ELSE!][!//
  [!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!][!//
    [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector)"!][!//
      [!VAR "FlsMaxReadNormalMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsMaxReadNormalMode)"!][!//
    [!ELSE!][!//
      [!VAR "FlsMaxReadNormalMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/FlsMaxReadNormalMode)"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "FlsMaxReadNormalMode" = "0"!][!//
  [!ENDIF!][!//
  [!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!][!//
    [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector)"!][!//
      [!VAR "FlsMaxWriteNormalMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsMaxWriteNormalMode)"!][!//
    [!ELSE!][!//
      [!VAR "FlsMaxWriteNormalMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/FlsMaxWriteNormalMode)"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "FlsMaxWriteNormalMode" = "0"!][!//
  [!ENDIF!][!//
  [!/* !LINKSTO Fee.FeeBufferCalculation.DefaultBuffer,1 */!][!//
  [!IF "not($FlsMaxReadNormalMode = 0) and not($FlsMaxWriteNormalMode = 0)"!][!//
    [!VAR "BufferSize" = "num:i(num:min(text:split(concat(num:max(text:split(concat($FlsMaxReadNormalMode,' ',$FlsMaxWriteNormalMode))),' ',$LargestBlockSize))))"!][!//
  [!ELSEIF "($FlsMaxReadNormalMode = 0) and not($FlsMaxWriteNormalMode = 0)"!][!//
    [!VAR "BufferSize" = "num:i(num:min(text:split(concat($FlsMaxWriteNormalMode,' ',$LargestBlockSize))))"!][!//
  [!ELSEIF "($FlsMaxWriteNormalMode = 0) and not($FlsMaxReadNormalMode = 0)"!][!//
    [!VAR "BufferSize" = "num:i(num:min(text:split(concat($FlsMaxReadNormalMode,' ',$LargestBlockSize))))"!][!//
  [!ELSE!][!//
    [!VAR "BufferSize" = "$LargestBlockSize"!][!//
  [!ENDIF!][!//
  [!VAR "BufferSize"!][!INDENT "0"!][!//
    [!CALL "GetAlignedSize", "DataSize" = "$BufferSize", "Alignment" = "$VirPageSize"!][!//
  [!ENDINDENT!][!ENDVAR!][!//
  [!IF "$BufferSize < $SmallestBufferSize"!][!//
    [!VAR "BufferSize" = "$SmallestBufferSize"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:existsAndFalse(FeeGeneral/FeeMemAccUsage)"!][!//
  [!IF "node:exists(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsSectorList/FlsSector)"!][!//
    [!VAR "FlsMaxReadFastMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/eb-list::*[1]/FlsMaxReadFastMode)"!][!//
  [!ELSE!][!//
    [!VAR "FlsMaxReadFastMode" = "num:i(as:modconf('Fls')[1]/FlsConfigSet/FlsMaxReadFastMode)"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "FlsMaxReadFastMode" = "0"!][!//
[!ENDIF!][!//
[!VAR "SmallestBufferSize"!][!INDENT "0"!][!//
  [!CALL "GetAlignedSize", "DataSize" = "$SmallestBufferSize", "Alignment"= "$BlockInfoSize"!][!//
[!ENDINDENT!][!ENDVAR!][!//
[!IF "node:existsAndFalse(FeeGeneral/FeeInitializeInLoop)"!][!//
  [!VAR "FlsMaxReadFastModeAl" = "num:integer($FlsMaxReadFastMode div $BlockInfoSize) * num:i($BlockInfoSize)"!][!//
  [!VAR "TruncBufferSize" = "num:integer($BufferSize div $BlockInfoSize) * num:i($BlockInfoSize)"!][!//
  [!/* !LINKSTO Fee.FeeBufferCalculation.InitBuffer,1 */!][!//
  [!VAR "InitBufferSize" = "num:i(num:min(text:split(concat(num:max(text:split(concat($FlsMaxReadFastModeAl,' ',$SmallestBufferSize))),' ',$TruncBufferSize))))"!][!//
[!ELSE!][!//
  [!/* !LINKSTO Fee.FeeBufferCalculation.SmallestBuffer,1 */!][!//
  [!VAR "InitBufferSize" = "$SmallestBufferSize"!][!//
[!ENDIF!][!//
[!IF "node:exists(FeeGeneral/FeeInitializationReadSize)"!][!//
  [!/* !LINKSTO Fee.FeeBufferCalculation.ConfiguredInitBuffer,1 */!][!//
  [!VAR "InitBufferSize" = "FeeGeneral/FeeInitializationReadSize"!][!//
  [!VAR "InitBufferSize" = "num:integer(num:integer($InitBufferSize div $BlockInfoSize) * num:i($BlockInfoSize))"!][!//
[!ENDIF!][!//
[!IF "node:exists(FeeGeneral/FeeBufferSize) and (not(node:exists(FeeGeneral/FeeUseBufferForJobs)) or (node:existsAndFalse(FeeGeneral/FeeUseBufferForJobs)))"!][!//
  [!IF "$BufferSize != $InitBufferSize"!][!//
    [!INFO!] The buffer size used for startup is [!"$InitBufferSize"!] bytes.[!ENDINFO!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!/***********************Section Configuration Validation ********************/!][!//
  [!IF "node:existsAndFalse(as:modconf('Fee')[1]/FeeGeneral/EnableAutoSectionGeneration)"!][!//
    [!VAR "PreviousSectionStartAddress" = "-1"!][!//
    [!VAR "PreviousSectionSize" = "0"!][!//
    [!LOOP "util:distinct(node:order(FeeGeneral/FeeSectionConfiguration/eb-list::*,'node:value(FeeSectionNumber)'))"!][!//
      [!IF "(FeeSectionStartAddress >= $PreviousSectionStartAddress + $PreviousSectionSize)"!][!//
        [!VAR "PreviousSectionStartAddress" = "FeeSectionStartAddress"!][!//
        [!VAR "PreviousSectionSize" = "FeeSectionSize"!][!//
      [!ELSE!][!//
        [!ERROR!] Sections configuration is not consistent.[!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!//
