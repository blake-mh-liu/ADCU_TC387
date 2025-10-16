[!/**
 * \file
 *
 * \brief AUTOSAR CanNm
 *
 * This file contains the implementation of the AUTOSAR
 * module CanNm.
 *
 * \version 6.20.6
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//

[!/* These checks were originally present as INVALID checks in CanNm.xdm.
   * Since these inter-module checks involve parameters from different
   * configuration classes, it's no more possible to keep them in CanNm.xdm.
   * Refer ASCCANNM-443 for more details.
   */!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('CANNM_CHECKS_M'))"!]
[!VAR "CANNM_CHECKS_M" = "'true'"!]

[!NOCODE!][!//

[!/* === Inter-module checks between CanNm and CanIf, EcuC or PduR === */!]

[!/* === General checks === */!]

[!/* Ensure that the routing path of the EIRA Rx NSdu is configured in PduR */!]
[!/* === This check has been moved from CanNmPnEiraRxNSduRef in CanNm.xdm.m4 === */!]
[!SELECT "CanNmGlobalConfig/eb-list::*[1]"!]
  [!IF "((node:existsAndTrue(as:modconf('CanNm')/CanNmGlobalConfig/eb-list::*/CanNmPnEiraCalcEnabled))) and
         (not(node:exists(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/
          PduRRoutingPath/eb-list::*/PduRSrcPdu[PduRSrcPduRef =
          node:current()/CanNmPnEiraRxNSduRef]/PduRSourcePduHandleId)))"!]
    [!ERROR!]"The routing path for CanNm EIRA PDU (CanNmPnEiraRxNSduRef) is not configured in the PduR module."
    [!ENDERROR!]
  [!ENDIF!]
[!ENDSELECT!]

[!/* Ensure that CanNmMaxPn is not smaller than the number of bits set to 1 in CanNmPnFilterMaskByteValue entries. */!]
[!IF "node:exists(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMaxPn)"!]
  [!VAR "BitsSetTo1" = "0"!]
  [!LOOP "util:distinct(node:order(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnFilterMaskByte/eb-list::*,'CanNmPnFilterMaskByteIndex'))"!]
    [!FOR "BitPos" = "0" TO "7"!]
      [!IF "node:existsAndTrue(bit:getbit(CanNmPnFilterMaskByteValue, $BitPos))"!]
        [!VAR "BitsSetTo1" = "$BitsSetTo1 + 1"!]
      [!ENDIF!]
    [!ENDFOR!]
  [!ENDLOOP!]
  [!IF "as:modconf('CanNm')[1]/CanNmGeneral/CanNmMaxPn < number($BitsSetTo1)"!]
    [!ERROR!]"Length of CanNmMaxPn cannot be smaller than the number of bits set to 1 in CanNmPnFilterMaskByteValue entries."
    [!ENDERROR!]
  [!ENDIF!]
[!ENDIF!]

[!/* Perform the following checks for each channel configured */!]
[!LOOP "CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*"!]

  [!SELECT "CanNmUserDataRxPdu"!]


    [!/* Ensure that the length of User Data Rx Pdu
       * matches with User Data Length parameter
       */!]
    [!/* === This check has been moved from CanNmUserDataRxPdu in CanNm.xdm.m4 === */!]
    [!/* !LINKSTO CanNm.SWS_CanNm_00332,1 */!]
    [!IF "(num:i(node:ref(CanNmRxUserDataPduRef)/PduLength) !=
           num:i(../CanNmUserDataLength))"!]
      [!ERROR!]Length of Rx User Data Pdu (CanNmRxUserDataPduRef) for channel '[!"as:name(..)"!]' doesn't match with User Data Length parameter (CanNmUserDataLength).
      [!ENDERROR!]
    [!ENDIF!]

    [!/* Ensure that routing path of User Data Rx Pdu is configured in PduR */!]
    [!/* !LINKSTO CanNm.EB.ComUserDataSupport.PduR_CanNmUserDataRxId,1 */!]
    [!/* === This check has been moved from CanNmUserDataRxPdu in CanNm.xdm.m4 === */!]
    [!IF "(not(node:exists(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/
           PduRRoutingPath/eb-list::*/PduRSrcPdu[PduRSrcPduRef = node:current()/CanNmRxUserDataPduRef]/PduRSourcePduHandleId)))"!]
      [!ERROR!]Routing path for the CanNm UserData Rx PDU (CanNmRxUserDataPduRef) in channel '[!"as:name(..)"!]' is not configured in PduR module.
      [!ENDERROR!]
    [!ENDIF!]

  [!ENDSELECT!]

  [!SELECT "CanNmUserDataTxPdu"!]


    [!/* Ensure that the length of User Data Tx Pdu
       * matches with User Data Length parameter
       */!]
    [!/* === This check has been moved from CanNmTxUserDataPduRef in CanNm.xdm.m4 === */!]
    [!/* !LINKSTO CanNm.SWS_CanNm_00332,1 */!]
    [!IF "(num:i(node:ref(CanNmTxUserDataPduRef)/PduLength) != num:i(../CanNmUserDataLength))"!]
      [!ERROR!]Length of Tx User Data Pdu (CanNmTxUserDataPduRef) for channel '[!"as:name(..)"!]' doesn't match with User Data Length parameter (CanNmUserDataLength).
      [!ENDERROR!]
    [!ENDIF!]

    [!/* Ensure that routing path of User Data Tx Pdu is configured in PduR */!]
    [!/* For more information please refer to ticket ASCCANNM-743  */!]
    [!IF "(not(node:exists(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/
           PduRRoutingPath/eb-list::*/PduRDestPdu/eb-list::*[PduRDestPduRef =
           node:current()/CanNmTxUserDataPduRef]/PduRDestPduHandleId)))"!]
      [!ERROR!]Routing path for the CanNm UserData Tx PDU (CanNmTxUserDataPduRef) in channel '[!"as:name(..)"!]' is not configured or PduRDestPduHandleId is disabled in PduR module.
      [!ENDERROR!]
    [!ENDIF!]

  [!ENDSELECT!]

  [!IF "(node:refvalid(CanNmTxPdu/CanNmTxPduRef))"!]

    [!/* Ensure that the length of User Data Tx Pdu and User Data Rx Pdu are equal */!]
    [!/* === This check has been moved from CanNmTxPduRef in CanNm.xdm.m4 === */!]
    [!IF "((node:refvalid(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)) and
           (num:i(node:ref(CanNmTxPdu/CanNmTxPduRef)/PduLength) !=
            num:i(node:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength)))"!]
      [!ERROR!]The length of Tx Pdu (CanNmTxPduRef) for channel '[!"as:name(.)"!]' is not equal to the length of the Rx Pdu (CanNmRxPduRef).
      [!ENDERROR!]
    [!ENDIF!]

  [!ENDIF!]

  [!/* === Checks for Rx Pdu === */!]

    [!/* Ensure that Rx Pdu length is not 0 */!]
    [!IF "(num:i(node:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength) = 0)"!]
      [!ERROR!]The length of Rx Pdu (CanNmRxPduRef) for channel '[!"as:name(.)"!]' is 0!
      [!ENDERROR!]
    [!ENDIF!]

    [!/* Ensure that Rx Pdu is large enough to hold PN Info */!]
    [!/* === This check has been moved from CanNmRxPduRef in CanNm.xdm.m4 === */!]
    [!IF "((node:existsAndTrue(CanNmPnEnabled)) and
          (node:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength <
           (../../CanNmPnInfo/CanNmPnInfoLength + ../../CanNmPnInfo/CanNmPnInfoOffset)))"!]
        [!ERROR!]Partial networking is enabled for channel '[!"node:name(.)"!]', but length of Rx Pdu (CanNmRxPduRef) is less than (CanNmPnInfoLength + CanNmPnInfoOffset).
      [!ENDERROR!]
    [!ENDIF!]

    [!/* Ensure that Rx Pdu is large enough to hold CBV and Node Id */!]
    [!/* === This check has been moved from CanNmUserDataLength in CanNm.xdm.m4 === */!]
    [!IF "(CanNmUserDataLength > (as:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength -
            count(( util:union(CanNmPduNidPosition,CanNmPduCbvPosition) )[. != 'CANNM_PDU_OFF'])))"!]
      [!ERROR!]The size of the user data is greater than the length of the PDU subtracted by length of the Control Bit Vector or the Node Id.
      [!ENDERROR!]
    [!ENDIF!]

    [!IF "node:exists(CanNmCarWakeUpBytePosition)"!]
      [!IF "(node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoLength)) and
            (node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoOffset)) and
            (node:existsAndTrue(CanNmPnEnabled)) and
            (as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoLength > 0) and
            (CanNmCarWakeUpBytePosition >= as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoOffset) and
            (CanNmCarWakeUpBytePosition <= (as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoOffset +
            ((as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoLength) - 1)))"!]
        [!ERROR!]For Channel '[!"node:name(.)"!]' CanNmCarWakeUpBytePosition overlaps with partial network bytes (CanNmPnInfoOffset, CanNmPnInfoLength)
        [!ENDERROR!]
      [!ENDIF!]
      [!IF "(node:refvalid(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)) and (CanNmCarWakeUpBytePosition >= as:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength)"!]
        [!ERROR!]For Channel '[!"node:name(.)"!]' CanNmCarWakeUpBytePosition is greater or equal than the RxPduLength
        [!ENDERROR!]
      [!ENDIF!]
   [!ENDIF!]

[!ENDLOOP!]

[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmPnSupported)"!]
  [!LOOP "as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*"!]
    [!IF "(node:existsAndTrue(CanNmPnEraCalcEnabled))"!]
      [!IF "count(as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*/PduRSrcPdu[PduRSrcPduRef=node:current()/CanNmPnEraRxNSduRef]/PduRSourcePduHandleId) = 0"!]
       [!ERROR!] In CanNm for channel: [!"node:name(.)"!], the pdu referenced by CanNmPnEraRxNSduRef is not configured in PduR
       [!ENDERROR!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]

[!/* !LINKSTO CanNm.EB.PostBuildRamSize.2,1 */!]
[!VAR "CalculatedPbRamSize" = "0"!][!//
[!LOOP "util:distinct(node:order(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*,'CanNmRxPdu/eb-list::*[1]/CanNmRxPduId'))"!]
[!VAR "CalculatedPbRamSize" = "$CalculatedPbRamSize + num:i(node:ref(CanNmRxPdu/eb-list::*[1]/CanNmRxPduRef)/PduLength)"!]
[!ENDLOOP!]

[!IF "node:existsAndFalse(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPassiveModeEnabled)"!]
[!VAR "CalculatedPbRamSize" = "$CalculatedPbRamSize * 2"!]
[!ENDIF!]

[!IF "($CalculatedPbRamSize) > as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPostBuildRamSize"!]
  [!ERROR!] Space needed for TX, RX pdus are less then configurred CanNmPostBuildRamSize
  [!ENDERROR!]
[!ENDIF!]

[!/* !LINKSTO CanNm.EB.ComUserDataSupport.CanNmUserDataTxPdu,1 */!]
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmComUserDataSupport))"!]
  [!IF "(node:existsAndFalse(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPassiveModeEnabled))"!]
    [!LOOP "util:distinct(node:order(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*,'CanNmRxPdu/eb-list::*[1]/CanNmRxPduId'))"!]
      [!IF "(CanNmUserDataLength != 0) and (not(node:exists(CanNmUserDataTxPdu)))"!]
          [!ERROR!] "CanNmUserDataTxPdu should be configured for '[!"node:name(.)"!]' since CanNmUserDataLength is not zero"
          [!ENDERROR!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDIF!]

[!IF "(node:existsAndFalse(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreSupport)) and
      (node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef)]))"!]
  [!SELECT "as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*"!]
    [!IF "not(node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef))"!]
      [!ERROR!] "All channels ComMChannelPartitionRef refrences from ComM must be either set or unset if CanNmMultiCoreSupport is false"
      [!ENDERROR!]
    [!ENDIF!]
    [!IF "count(as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (node:value(OsAppEcucPartitionRef) = node:value(node:ref(node:current()/CanNmComMNetworkHandleRef)/ComMChannelPartitionRef))]) = 0"!]
      [!ERROR!] "If reference ComMChannelPartitionRef from ComM is set, then same reference must exist in OsAppEcucPartitionRef for an os application"
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDSELECT!]
[!ENDIF!]

[!IF "(node:existsAndFalse(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreSupport)) and
      (node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef)])) and
      (node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnEiraCalcEnabled)) and 
      (node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnEiraCalcEnabled)) and
      not(node:refvalid(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef))
      "!]
  [!ERROR!] "If multicore per channel conditions are set and CanNmPnEiraCalcEnabled is true, then in ComM the reference ComMMasterPNCEcuCPartitionRef must be set"
  [!ENDERROR!]
[!ENDIF!]

[!/* Check that in case CanNmSynchronizedPncShutdownEnabled is set to true CanNmPnEnabled is set to true */!]
[!LOOP "as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*"!]
  [!IF "node:exists(CanNmSynchronizedPncShutdownEnabled) and 
        (node:existsAndTrue(CanNmSynchronizedPncShutdownEnabled)) and
        ((node:existsAndFalse(CanNmPnEnabled)) or not(node:exists(CanNmPnEnabled)))
       "!]
    [!ERROR!]"For channel [!"node:name(.)"!] CanNmSynchronizedPncShutdownEnabled is set to true but CanNmPnEnabled is set to false"  
    [!ENDERROR!]        
  [!ENDIF!]
[!ENDLOOP!]

[!ENDNOCODE!][!//

[!ENDIF!]
