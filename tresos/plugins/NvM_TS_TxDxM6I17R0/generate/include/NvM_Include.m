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
[!/* !LINKSTO NvM.SWS_NvM_00544,1 */!]
[!/*
=== define maximum space needed for CRC ===
*/!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCrc)) and (NvMBlockCrcType='NVM_CRC32')]) > 0"!][!/*
   */!][!VAR "maxCrcSize"="4"!][!/*
*/!][!ELSEIF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCrc)) and (NvMBlockCrcType='NVM_CRC16')]) > 0"!][!/*
   */!][!VAR "maxCrcSize"="2"!][!/*
*/!][!ELSE!][!/*
   */!][!VAR "maxCrcSize"="1"!][!/*   
*/!][!ENDIF!][!/*

=== calculate the maximum space needed for internal buffer ===
  */!][!VAR "crcSize" = "0"!][!/*
  */!][!VAR "ExtraCryptoSize" = "0"!][!/*
  */!][!VAR "blockIdSize" = "0"!][!/*
  */!][!VAR "maxBlockSize"="0"!][!/* 
  */!][!LOOP "NvMBlockDescriptor/eb-list::*[((node:existsAndTrue(../../NvMCommon/NvMMemAccUsage)) and (../../NvMCommon/NvMBufferAlignmentValue != 'NVM_ALIGN_8_BITS')) or
                                    ((node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndFalse(NvMUserProvidesSpaceForBlockAndCrc))) or
                                    (node:existsAndTrue(NvMWriteVerification)) or 
                                    (node:existsAndTrue(NvMPreWriteDataComp)) or 
                                    (node:existsAndTrue(NvMEnBlockCheck)) or 
                                    (node:existsAndTrue(NvMStaticBlockIDCheck)) or 
                                    ((node:existsAndTrue(NvMEnableBlockCryptoSecurityHandling)) and
                                    (node:existsAndTrue(../../NvMCommon/NvMCommonCryptoSecurityParameters/NvMEnableCryptoSecurityHooks))) or 
                                    (node:existsAndTrue(NvMBlockUseSyncMechanism)) or 
                                    (NvMBlockManagementType = 'NVM_BLOCK_REDUNDANT') or 
                                    (NvMBlockManagementType = 'NVM_BLOCK_DATASET')]"!][!/*
  */!][!IF "node:existsAndTrue(NvMBlockUseCrc)"!][!/*
    */!][!IF "NvMBlockCrcType = 'NVM_CRC32'"!][!/*
      */!][!VAR "crcSize"="4"!][!/* 
      */!][!ELSEIF "NvMBlockCrcType = 'NVM_CRC16'"!][!/*
      */!][!VAR "crcSize"="2"!][!/* 
    */!][!ELSE!][!/*
      */!][!VAR "crcSize"="1"!][!/* 
    */!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(../../NvMCommon/NvMCommonCryptoSecurityParameters/NvMEnableCryptoSecurityHooks)"!][!/*
  */!][!IF "node:existsAndTrue(NvMEnableBlockCryptoSecurityHandling)"!][!VAR "ExtraCryptoSize"="NvMCryptoExtraInfoSize"!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMStaticBlockIDCheck)"!][!VAR "blockIdSize"="2"!][!ENDIF!][!/*
  */!][!VAR "blockSize"="NvMNvBlockLength + $blockIdSize + $crcSize + $ExtraCryptoSize"!][!/*
  */!][!IF "$blockSize > $maxBlockSize"!][!/*
     */!][!VAR "maxBlockSize"="$blockSize"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

=== calculate the space needed for RAM CRC buffer ===
*/!][!VAR "CrcBufSize" = "0"!][!/*
*/!][!LOOP "NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCrc)) and (node:existsAndTrue(NvMCalcRamBlockCrc))]"!][!/*
   */!][!IF "NvMBlockCrcType = 'NVM_CRC8'"!][!/*
      */!][!VAR "CrcBufSize" = "$CrcBufSize + 1"!][!/*
      */!][!ELSEIF "NvMBlockCrcType = 'NVM_CRC16'"!][!/*
      */!][!VAR "CrcBufSize" = "$CrcBufSize + 2"!][!/*
   */!][!ELSE!][!/*
      */!][!VAR "CrcBufSize" = "$CrcBufSize + 4"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

=== calculate the space needed for NV CRC buffer ===
*/!][!VAR "NvCrcBufSize" = "0"!][!/*
*/!][!LOOP "NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseCRCCompMechanism)) and (node:existsAndTrue(NvMBlockUseCrc))]"!][!/*
   */!][!IF "NvMBlockCrcType = 'NVM_CRC8'"!][!/*
      */!][!VAR "NvCrcBufSize" = "$NvCrcBufSize + 1"!][!/*
      */!][!ELSEIF "NvMBlockCrcType = 'NVM_CRC16'"!][!/*
      */!][!VAR "NvCrcBufSize" = "$NvCrcBufSize + 2"!][!/*
   */!][!ELSE!][!/*
      */!][!VAR "NvCrcBufSize" = "$NvCrcBufSize + 4"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

=== calculate the space needed for RAM Write verification buffer ===
*/!][!VAR "writeVerificationBufferSize"="0"!][!/*
*/!][!VAR "preWriteDataCompBufferSize"="0"!][!/*
*/!][!VAR "maxVerificationSize"="0"!][!/*
*/!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMWriteVerification))])>0"!][!/* 
  */!][!LOOP "NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMWriteVerification))]"!][!/*
  */!][!VAR "writeVerificationBufferSize"="NvMWriteVerificationDataSize"!][!/*
  */!][!IF "$writeVerificationBufferSize > $maxVerificationSize"!][!/*
     */!][!VAR "maxVerificationSize"="$writeVerificationBufferSize"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!ENDIF!]
[!VAR "NVM_DeviceIdList"="''"!][!/*
*/!][!VAR "NVM_NrOfDevices"="0"!][!/*
*/!][!LOOP "as:modconf('NvM')[1]/NvMBlockDescriptor/eb-list::*"!][!/*
  */!][!VAR "Found"="'false'"!][!/*
  */!][!VAR "DeviceId"="node:value(NvMNvramDeviceId)"!][!/*
  */!][!LOOP "text:split($NVM_DeviceIdList,';')"!][!/*
    */!][!IF "((.) = number($DeviceId))"!][!/*
     */!][!VAR "Found"="'true'"!][!/*
  */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!IF "($Found = 'false')"!][!/*
    */!][!VAR "NVM_DeviceIdList"!][!"$NVM_DeviceIdList"!][!"NvMNvramDeviceId"!];[!ENDVAR!][!/*
    */!][!VAR "NVM_NrOfDevices"="$NVM_NrOfDevices + 1"!][!/*
    */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMPreWriteDataComp))])>0"!][!/* 
  */!][!LOOP "NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMPreWriteDataComp))]"!][!/*
  */!][!VAR "preWriteDataCompBufferSize"="NvMPreWriteDataCompDataSize"!][!/*
  */!][!IF "$preWriteDataCompBufferSize > $maxVerificationSize"!][!/*
     */!][!VAR "maxVerificationSize"="$preWriteDataCompBufferSize"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*
*/!][!ENDIF!][!/*

=== calculate the maximum space needed for intermediate buffer ===
  */!][!VAR "intcrcSize" = "0"!][!/*
  */!][!VAR "intblockIdSize" = "0"!][!/*
  */!][!LOOP "NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMEnBlockCheck))]"!][!/*
  */!][!IF "node:existsAndTrue(NvMBlockUseCrc)"!][!/*
    */!][!IF "NvMBlockCrcType = 'NVM_CRC32'"!][!/*
      */!][!VAR "intcrcSize"="4"!][!/* 
      */!][!ELSEIF "NvMBlockCrcType = 'NVM_CRC16'"!][!/*
      */!][!VAR "intcrcSize"="2"!][!/* 
    */!][!ELSE!][!/*
      */!][!VAR "intcrcSize"="1"!][!/* 
    */!][!ENDIF!][!/*
  */!][!ENDIF!][!/*
  */!][!IF "node:existsAndTrue(NvMStaticBlockIDCheck)"!][!VAR "intblockIdSize"="2"!][!ENDIF!][!/*
  */!][!VAR "intblockSize"="NvMNvBlockLength + $intblockIdSize + $intcrcSize"!][!/*
  */!][!IF "$intblockSize > $maxVerificationSize"!][!/*
     */!][!VAR "maxVerificationSize"="$intblockSize"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

=== make the Bsw distribution callbacks arrays on Master ===
*/!][!IF "(count(as:modconf('NvM')[1]/NvMCommon/NvMEcucPartitionRef/eb-list::*) > 1)"!][!/*
  */!][!VAR "InitCallbackArray"="''"!][!/*
  */!][!VAR "InitCallbackArraySize"="0"!][!/*
  */!][!VAR "SingleCallbackArray"="''"!][!/*
  */!][!VAR "SingleCallbackArraySize"="0"!][!/*
  */!][!VAR "ReadCallbackArray"="''"!][!/*
  */!][!VAR "ReadCallbackArraySize"="0"!][!/*
  */!][!VAR "WriteCallbackArray"="''"!][!/*
  */!][!VAR "WriteCallbackArraySize"="0"!][!/*
  */!][!LOOP "util:distinct(node:order(NvMBlockDescriptor/eb-list::*, 'NvMNvramBlockIdentifier'))"!][!/*
   */!][!IF "NvMBlockEcucPartitionRef = as:modconf('NvM')[1]/NvMCommon/NvMMasterEcucPartitionRef"!][!/*
    */!][!IF "(node:existsAndTrue(NvMProvideRteInitBlockPort) and (node:exists(../../NvMCommon/NvMServiceAPI)) and (node:exists(NvMRPortInterfacesASRVersion)))"!][!/*
      */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'(NvM_CallbackFctPtr)')"!][!/*
        */!][!IF "node:existsAndTrue(ASR2011CallbackEnabled)"!][!/*
          */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'&Rte_Call_NvM_PNInitBlock_ASR2011_',as:name(.),'_InitBlock')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
          */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'&Rte_Call_PNInitBlock_',as:name(.),'_InitBlock')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
          */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'&Rte_Call_NvM_PNInitBlock_ASR32_',as:name(.),'_InitBlock')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
          */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'&Rte_Call_NvM_PNInitBlock_ASR40_',as:name(.),'_InitBlock')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
          */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'&Rte_Call_NvM_PNInitBlock_ASR42_',as:name(.),'_InitBlock')"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,', /* ',as:name(.),' */;')"!][!/*
        */!][!VAR "InitCallbackArraySize"="$InitCallbackArraySize + 1"!][!/*
    */!][!ELSEIF "(node:exists(NvMInitBlockCallback)) and (NvMInitBlockCallback != '')"!][!/*
      */!][!VAR "InitCallbackArray"="concat($InitCallbackArray,'(NvM_CallbackFctPtr)&',NvMInitBlockCallback,', /* ',as:name(.),' */;')"!][!/*
      */!][!VAR "InitCallbackArraySize"="$InitCallbackArraySize + 1"!][!/*
    */!][!ENDIF!][!/*
      */!][!IF "(node:existsAndTrue(NvMProvideRteJobFinishedPort) and (node:exists(../../NvMCommon/NvMServiceAPI)) and (node:exists(NvMRPortInterfacesASRVersion)))"!][!/*
        */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'(NvM_CallbackFctPtr)')"!][!/*
        */!][!IF "node:existsAndTrue(ASR2011CallbackEnabled)"!][!/*
          */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'&Rte_Call_NvM_PNJobFinished_ASR2011_',as:name(.),'_JobFinished')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
          */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'&Rte_Call_PNJobFinished_',as:name(.),'_JobFinished')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
          */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'&Rte_Call_NvM_PNJobFinished_ASR32_',as:name(.),'_JobFinished')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
          */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'&Rte_Call_NvM_PNJobFinished_ASR40_',as:name(.),'_JobFinished')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
          */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'&Rte_Call_NvM_PNJobFinished_ASR42_',as:name(.),'_JobFinished')"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,', /* ',as:name(.),' */;')"!][!/*
        */!][!VAR "SingleCallbackArraySize"="$SingleCallbackArraySize + 1"!][!/*
    */!][!ELSEIF "(node:exists(NvMSingleBlockCallback)) and (NvMSingleBlockCallback != '')"!][!/*
      */!][!VAR "SingleCallbackArray"="concat($SingleCallbackArray,'(NvM_CallbackFctPtr)&',NvMSingleBlockCallback,', /* ',as:name(.),' */;')"!][!/*
      */!][!VAR "SingleCallbackArraySize"="$SingleCallbackArraySize + 1"!][!/*
    */!][!ENDIF!][!/*
      */!][!IF "(node:existsAndTrue(NvMProvideRteMirrorPort) and (node:exists(../../NvMCommon/NvMServiceAPI)) and (node:exists(NvMRPortInterfacesASRVersion)))"!][!/*
        */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'(NvM_NvToRamCopyCallbackType)')"!][!/*
        */!][!IF "node:existsAndTrue(ASR2011CallbackEnabled)"!][!/*
          */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'&Rte_Call_NvM_PMirror_ASR2011_',as:name(.),'_ReadRamBlockFromNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
          */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'&Rte_Call_PMirror_',as:name(.),'_ReadRamBlockFromNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
          */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'&Rte_Call_NvM_PMirror_ASR32_',as:name(.),'_ReadRamBlockFromNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
          */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'&Rte_Call_NvM_PMirror_ASR40_',as:name(.),'_ReadRamBlockFromNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
          */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'&Rte_Call_NvM_PMirror_ASR42_',as:name(.),'_ReadRamBlockFromNvm')"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,', /* ',as:name(.),' */;')"!][!/*
        */!][!VAR "ReadCallbackArraySize"="$ReadCallbackArraySize + 1"!][!/*
    */!][!ELSEIF "node:existsAndTrue(NvMBlockUseSyncMechanism) and not(node:empty(NvMReadRamBlockFromNvCallback))"!][!/*
      */!][!VAR "ReadCallbackArray"="concat($ReadCallbackArray,'(NvM_NvToRamCopyCallbackType)&',NvMReadRamBlockFromNvCallback,', /* ',as:name(.),' */;')"!][!/*
      */!][!VAR "ReadCallbackArraySize"="$ReadCallbackArraySize + 1"!][!/*
    */!][!ENDIF!][!/*
      */!][!IF "(node:existsAndTrue(NvMProvideRteMirrorPort) and (node:exists(../../NvMCommon/NvMServiceAPI)) and (node:exists(NvMRPortInterfacesASRVersion)))"!][!/*
        */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'(NvM_RamToNvCopyCallbackType)')"!][!/*
        */!][!IF "node:existsAndTrue(ASR2011CallbackEnabled)"!][!/*
          */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'&Rte_Call_NvM_PMirror_ASR2011_',as:name(.),'_WriteRamBlockToNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'DEFAULT')"!][!/*
          */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'&Rte_Call_PMirror_',as:name(.),'_WriteRamBlockToNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_32')"!][!/*
          */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'&Rte_Call_NvM_PMirror_ASR32_',as:name(.),'_WriteRamBlockToNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_40')"!][!/*
          */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'&Rte_Call_NvM_PMirror_ASR40_',as:name(.),'_WriteRamBlockToNvm')"!][!/*
        */!][!ELSEIF "(NvMRPortInterfacesASRVersion = 'AUTOSAR_42')"!][!/*
          */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'&Rte_Call_NvM_PMirror_ASR42_',as:name(.),'_WriteRamBlockToNvm')"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,', /* ',as:name(.),' */;')"!][!/*
        */!][!VAR "WriteCallbackArraySize"="$WriteCallbackArraySize + 1"!][!/*
    */!][!ELSEIF "node:existsAndTrue(NvMBlockUseSyncMechanism) and not(node:empty(NvMWriteRamBlockToNvCallback))"!][!/*
      */!][!VAR "WriteCallbackArray"="concat($WriteCallbackArray,'(NvM_RamToNvCopyCallbackType)&',NvMWriteRamBlockToNvCallback,', /* ',as:name(.),' */;')"!][!/*
      */!][!VAR "WriteCallbackArraySize"="$WriteCallbackArraySize + 1"!][!/*
    */!][!ENDIF!][!/*
   */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!VAR "InitCallbackArraySize" = "num:i($InitCallbackArraySize)"!][!/*
  */!][!VAR "SingleCallbackArraySize" = "num:i($SingleCallbackArraySize)"!][!/*
  */!][!VAR "ReadCallbackArraySize" = "num:i($ReadCallbackArraySize)"!][!/*
  */!][!VAR "WriteCallbackArraySize" = "num:i($WriteCallbackArraySize)"!][!/*
*/!][!ENDIF!]
