[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fr_17_Eray.m                                                  **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2019-06-28                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Fr_17_Eray.bmd                                   **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={9988512D-3AA7-4b66-88DE-2869368CAF4E}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Fr Driver                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]
[!INDENT "0"!][!//
  [!/* *** multiple inclusion protection*** */!][!//
  [!IF "not(var:defined('FR_M'))"!][!//
    [!VAR "FR_M"="'true'"!][!//

    [!/*
    MACRO: Fr_17_Eray_CG_ConfigSwitch 
    Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
    true/false
    */!]
    [!MACRO "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = ""!][!//
    [!//
      [!IF "$nodeval = 'true'"!][!//
        (STD_ON)[!//
      [!ELSE!][!//
        (STD_OFF)[!//
      [!ENDIF!]
    [!ENDMACRO!]

    [!/*
    MACRO: Fr_17_Eray_CG_ConfigSwitch2 
    Macro to generate configuration switch values (0,1) based on configuration
    true/false
    */!]
    [!MACRO "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = ""!][!//
    [!//
      [!INDENT "4"!][!//
        [!IF "$nodeval = 'true'"!][!//
          1[!//
        [!ELSE!][!//
          0[!//
        [!ENDIF!][!//
      [!ENDINDENT!][!//
    [!ENDMACRO!]

    [!/*
    MACRO: Fr_17_Eray_CG_HeaderCRC 
    Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
    true/false
    Input Parameters:
    Sync : 1 if it is sync frame, 0 other wise
    Sfi  : 1 if it is start frame, 0 otherwise 
    Fid  : Frame ID / Slot ID
    Plc  : Payload length in terms of 16bit words
            Note: For static segment frames it is equal to PayloadLengthStatic

    Output Parameters:
    vCrcReg : 11 bit Header CRC value
    */!]
    [!MACRO "Fr_17_Eray_CG_HeaderCRC", "Sync" = "", "Sfi" = "", "Fid" = "", "Plc" = ""!][!//
      [!//
      [!VAR "Header1" = "num:i(bit:or((bit:shl(num:i($Sync), 19)), (bit:shl(num:i($Sfi), 18))))"!][!//
      [!/* Input PLC in terms of bytes, so divide by 2 to make it 16bit word length */!][!//
      [!VAR "Header2" = "num:i(bit:or((bit:shl(num:i($Fid), 7)), num:i($Plc)))"!][!//
      [!VAR "Header" = "num:i(bit:or($Header1, $Header2))"!][!//
      [!//
      [!// Initial value for Header CRC */ [!//
      [!VAR "vCrcReg" = "num:i(26)"!][!//
      [!VAR "vCrcPoly" = "num:i(901)"!][!//
      [!VAR "length" = "num:i(20)"!][!//
      [!//
      [!VAR "Header" = "bit:shl($Header, 12)"!][!//
      [!VAR "vCrcReg" = "bit:shl($vCrcReg, 21)"!][!//
      [!VAR "vCrcPoly" = "bit:shl($vCrcPoly, 21)"!][!//
      [!VAR "mask" = "num:hextoint('0x80000000')"!][!//
      [!VAR "mask32bit" = "num:hextoint('0xffffffff')"!][!//
      [!//
      [!FOR "cg_i" = "0" TO "19"!][!//
        [!VAR "vNextBitHeader" = "bit:and($Header, $mask)"!][!//
        [!VAR "vNextBitCrcReg" = "bit:and($vCrcReg, $mask)"!][!//

        [!VAR "vCrcNext" = "bit:xor($vNextBitHeader, $vNextBitCrcReg)"!][!//

        [!VAR "Header" = "bit:shl($Header, 1)"!][!//
        [!VAR "vCrcReg" = "bit:shl($vCrcReg, 1)"!][!//

        [!VAR "Header" = "bit:and($Header,$mask32bit )"!][!//
        [!VAR "vCrcReg" = "bit:and($vCrcReg, $mask32bit)"!][!//

        [!IF "$vCrcNext > 0"!][!//
          [!VAR "vCrcReg" = "bit:xor($vCrcReg, $vCrcPoly)"!][!//
        [!ENDIF!][!//

      [!ENDFOR!][!//

      [!VAR "vCrcReg" = "bit:shr($vCrcReg, 21)"!][!//
      [!VAR "vCrcReg" = "num:inttohex($vCrcReg)"!][!//
    [!ENDMACRO!][!//
    [!//
    [!//
    [!/*
    MACRO: Fr_17_Eray_CG_GetLPduIdxPath 
    Macro to manipulate LPduIdxPath to make it suitable for comparison with 
    FrIfLPduIdxRef
    */!]
    [!MACRO "Fr_17_Eray_CG_GetLPduIdxPath", "LPduIdxPath" = ""!][!//
      LPduIdxPath = [!"$LPduIdxPath"!]
      [!VAR "LPduIdxPath" = "substring-after($LPduIdxPath, 'FrIfConfig/')"!][!//
      [!//
      [!VAR "TempString1" = "substring-before($LPduIdxPath, 'FrIfCluster/')"!][!//
      [!VAR "TempString2" = "substring-after($LPduIdxPath, 'FrIfCluster/')"!][!//
      [!VAR "LPduIdxPath" = "concat($TempString1, $TempString2)"!][!//
      [!//
      [!VAR "TempString1" = "substring-before($LPduIdxPath, 'FrIfController/')"!][!//
      [!VAR "TempString2" = "substring-after($LPduIdxPath, 'FrIfController/')"!][!//
      [!VAR "LPduIdxPath" = "concat($TempString1, $TempString2)"!][!//
      [!//
      [!VAR "TempString1" = "substring-before($LPduIdxPath, 'FrIfLPdu/')"!][!//
      [!VAR "TempString2" = "substring-after($LPduIdxPath, 'FrIfLPdu/')"!][!//
      [!VAR "LPduIdxPath" = "concat($TempString1, $TempString2)"!][!//
      [!//
      $LPduIdxPath Modified = [!"$LPduIdxPath"!]
    [!ENDMACRO!][!//

    [!/*
    MACRO: Fr_17_Eray_CG_MsBufDir 
    Macro to find direction of message buffer
    */!]
    [!MACRO "Fr_17_Eray_CG_MsBufDir", "CurrentCluster" = "", "LPduIdxPath" = ""!][!//
      [!/* Append '/' to avoid matches like Lpdu_1 being contained by Lpdu_11, Lpdu_12, Lpdu_110 etc */!]
      [!VAR "LPduIdxPath_Slash" = "concat($LPduIdxPath,'/')"!][!//
      [!VAR "LPduTxStatus" = "num:i(0)"!][!//
      [!VAR "LPduRxStatus" = "num:i(0)"!][!//
      [!VAR "LPduTxStatusTrueFor" = "''"!][!//[!//
      [!VAR "LPduRxStatusTrueFor" = "''"!][!//[!//
      [!//
      [!VAR "Jobs" = "(concat($CurrentCluster, '/FrIfJobList/FrIfJob'))"!][!//
      [!LOOP "node:ref($Jobs)/*"!][!//
        [!LOOP "FrIfCommunicationOperation/*"!][!//
          [!IF "node:empty(FrIfLPduIdxRef)"!][!//
            [!ERROR!][!//
              Missing reference to LPdu index for the communication operation [!"node:name(.)"!] within the FrIf Job [!"node:name(../..)"!]
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!//FrIfCommunicationAction = [!"FrIfCommunicationAction"!][!//
          [!/* Append '/' to avoid matches like Lpdu_1 being contained by Lpdu_11, Lpdu_12, Lpdu_110 etc */!]
          [!VAR "FrIfLPduIdxRef_Slash" = "concat(FrIfLPduIdxRef,'/')"!][!//
          [!/* ---------  Config Rule ---------*/!][!//
          [!IF "not(contains($FrIfLPduIdxRef_Slash, substring-before($LPduIdxPath_Slash, '/')))"!][!//
            [!ERROR!][!//
              Error: Mixing of configurations from different post-build configurations
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!/* ------------------------------------------*/!][!//
          --> $FrIfLPduIdxRef_Slash [!"$FrIfLPduIdxRef_Slash"!]
          --> LPduIdxPath_Slash [!"$LPduIdxPath_Slash"!]
          [!IF "contains($FrIfLPduIdxRef_Slash, $LPduIdxPath_Slash) and (contains(FrIfCommunicationAction,'RECEIVE') or (FrIfCommunicationAction = 'RX_INDICATION'))"!][!//
            [!VAR "LPduRxStatus" = "num:i(1)"!][!//[!//
            [!VAR "LPduRxStatusTrueFor" = "node:path(.)"!][!//[!//
          [!ENDIF!][!//
          [!IF "contains($FrIfLPduIdxRef_Slash, $LPduIdxPath_Slash) and (contains(FrIfCommunicationAction,'TRANSMISSION') or (FrIfCommunicationAction = 'TX_CONFIRMATION'))"!][!//
            [!VAR "LPduTxStatus" = "num:i(1)"!][!//
            [!VAR "LPduTxStatusTrueFor" = "node:path(.)"!][!//[!//
          [!ENDIF!][!//
          [!//
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
      [!//
      [!/* ---------  Config Rule FR_CR_205 ---------*/!][!//
      [!IF "(($LPduRxStatus = num:i(1)) and ($LPduTxStatus = num:i(1)))"!][!//
        [!ERROR!][!//
          Error: [!"$LPduIdxPath_Slash"!] is configured for transmission as well as reception.
          Transmission in job: [!"$LPduTxStatusTrueFor"!]
          Reception in job: [!"$LPduRxStatusTrueFor"!]
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!/* ------------------------------------------*/!][!//
      LPduRxStatus = [!"$LPduRxStatus"!][!//
      LPduTxStatus = [!"$LPduTxStatus"!][!//
    [!ENDMACRO!][!//

  [!ENDIF!][!// IF "not(var:defined('FR_M'))

[!ENDINDENT!][!//
