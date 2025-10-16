[!/**
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
 */!][!//
[!NOCODE!] 
[!/********************** Checking of Fee/Ea-Blocksizes vs. NvM-Blocksizes **********************************************/!][!//
  [!LOOP "NvMBlockDescriptor/eb-list::*"!]
    [!VAR "crcSize" = "0"!]
    [!VAR "blockIdSize" = "0"!]
    [!VAR "ExtraCryptoInfoSize" = "0"!]
    [!IF "node:existsAndTrue(NvMBlockUseCrc) and node:exists(NvMBlockCrcType)"!]
       [!IF "NvMBlockCrcType = 'NVM_CRC32'"!]
        [!VAR "crcSize"="4"!]
       [!ELSEIF "NvMBlockCrcType = 'NVM_CRC16'"!]
        [!VAR "crcSize"="2"!]
       [!ELSE!]
        [!VAR "crcSize"="1"!]
       [!ENDIF!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(NvMStaticBlockIDCheck)"!][!VAR "blockIdSize"="2"!][!ENDIF!]
    [!IF "node:existsAndTrue(../../NvMCommon/NvMCommonCryptoSecurityParameters/NvMEnableCryptoSecurityHooks)"!]
    [!IF "node:existsAndTrue(NvMEnableBlockCryptoSecurityHandling)"!][!VAR "ExtraCryptoInfoSize"="NvMCryptoExtraInfoSize"!][!ENDIF!]
    [!ENDIF!]
    [!VAR "reqBlkSize"="num:i(NvMNvBlockLength + $blockIdSize + $crcSize + $ExtraCryptoInfoSize)"!]

    [!IF "node:refvalid(NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfFeeBlock) and (NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfFeeBlock)!="""!]
      [!VAR "BlockNumber"="as:ref(./NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfFeeBlock)/FeeBlockNumber"!]
      [!VAR "NumberOfCopies"="./NvMNvBlockNum"!]
      [!LOOP "as:modconf('Fee')"!]
        [!LOOP "FeeBlockConfiguration/eb-list::*"!]
          [!IF "((FeeBlockNumber >= number($BlockNumber)) and (FeeBlockNumber < ($BlockNumber + $NumberOfCopies)))"!]
             [!IF "FeeBlockSize < number($reqBlkSize)"!]
                [!ERROR!] Configured Block size of Fee Block Number:[!"FeeBlockNumber"!] is not valid. It should be [!"$reqBlkSize"!].[!ENDERROR!]
             [!ENDIF!]
          [!ENDIF!]
        [!ENDLOOP!]
      [!ENDLOOP!]
    [!ELSEIF "node:refvalid(NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfEaBlock) and (NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfEaBlock)!="""!]
      [!VAR "BlockNumber"="as:ref(NvMTargetBlockReference/eb-choice::*[1]/NvMNameOfEaBlock)/EaBlockNumber"!]
      [!VAR "NumberOfCopies"="./NvMNvBlockNum"!]
      [!LOOP "as:modconf('Ea')"!]
        [!LOOP "EaBlockConfiguration/eb-list::*"!]
            [!IF "((EaBlockNumber >= number($BlockNumber)) and (EaBlockNumber < ($BlockNumber + $NumberOfCopies)))"!]
               [!IF "EaBlockSize < number($reqBlkSize)"!]
                  [!ERROR!] Configured Block size of Ea Block Number:[!"EaBlockNumber"!] is not valid. It should be [!"$reqBlkSize"!].[!ENDERROR!]
               [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
      [!ENDLOOP!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!]