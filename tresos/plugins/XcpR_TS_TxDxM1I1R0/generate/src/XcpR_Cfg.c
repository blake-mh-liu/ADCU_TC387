/**
 * \file
 *
 * \brief AUTOSAR XcpR
 *
 * This file contains the implementation of the AUTOSAR
 * module XcpR.
 *
 * \version 1.1.8
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!INCLUDE "include/XcpR_Vars.m"!][!//

/*==[Includes]================================================================*/

#include <XcpR.h>
#include <XcpR_Int.h>

#if ((XCPR_DEST_ON_CAN_LOWER_LAYER_ENABLED == STD_ON) || (XCPR_DEST_ON_CANFD_LOWER_LAYER_ENABLED == STD_ON))
#include <CanIf.h> /* CAN interface APIs */
#endif

#if (XCPR_DEST_ON_FLEXRAY_LOWER_LAYER_ENABLED == STD_ON)
#include <FrIf.h> /* FlexRay interface APIs */
#endif

#if (XCPR_DEST_ON_ETHERNET_LOWER_LAYER_ENABLED == STD_ON)
#include <SoAd.h> /* Socket Adapter interface APIs */
#endif

#if (XCPR_DEST_ON_CDD_LOWER_LAYER_ENABLED == STD_ON)
[!LOOP "text:split($CddHeaderFileList, ' ')"!][!//
#include <[!"."!]> /* [!"."!] CDD header */
[!ENDLOOP!][!//
#endif

#if ((XCPR_DEST_ON_CDD_UPPER_LAYER_ENABLED == STD_ON) || (XCPR_DEST_ON_CDD_LOWER_LAYER_ENABLED == STD_ON))
#include <[!"$CddULHeaderFile"!]> /* AUTOSAR [!"$CddULShortName"!] on CDD callback header; */
#endif

[!AUTOSPACING!][!//
/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define XCPR_START_SEC_CONST_UNSPECIFIED
#include <XcpR_MemMap.h>

/** \brief List of configured Reception PDUs */
CONST(XcpR_SrcPduType, XCPR_CONST) XcpR_SrcConf[XCPR_NO_OF_SOURCE_PDUS] =
{
[!VAR "PduStartPosInRx" = "0"!][!//
[!VAR "IntPduBufId" = "0"!][!//
  [!LOOP "util:distinct(node:order(XcpRGeneral/XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRRxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduId'))"!][!//
    [!VAR "FlxMaxMsgLengthInit"="0"!][!//
    [!VAR "EthMaxMsgLengthInit"="0"!][!//
    [!VAR "FlxPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "EthPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "FlxHeaderAlignment"="''"!][!//
    [!VAR "SequenceCorrection"="'false'"!][!//
    [!VAR "XcpRMaxDataLength" = "num:max(text:split(concat(num:i(node:when(node:exists(XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm), XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm, 0)), ' ', num:i(XcpRSourcePDUAttributes/XcpRSrcMaxCto), ' ', num:i(XcpRSourcePDUAttributes/XcpRSrcMaxDto))))"!][!//
    [!CALL "GetSourceConnectionType","InterfaceType"="XcpRSourceInterfaceType"!][!//
    [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_FLEXRAY'"!][!//
      [!VAR "SequenceCorrection"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceSequenceCorrectionEnabled"!][!//
      [!VAR "FlxHeaderAlignment"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceFlxHeaderAlignment"!][!//
      [!VAR "FlxPackMultiMsgInOneFrame"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneFlexRayFrame"!][!//
      [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneFlexRayFrame)"!][!//
        [!VAR "FlxMaxMsgLengthInit"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceMaxFlexMsgLength"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_ETHERNET'"!][!//
      [!VAR "EthPackMultiMsgInOneFrame"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneEthernetFrame"!][!//
      [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneEthernetFrame)"!][!//
        [!VAR "EthMaxMsgLengthInit"="XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceMaxEthernetMsgLength"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!CALL "GetPackagePduSize","FlxPackMultiMsgInOneFrame"="$FlxPackMultiMsgInOneFrame","EthPackMultiMsgInOneFrame"="$EthPackMultiMsgInOneFrame","FlxMaxMsgLengthInit"="$FlxMaxMsgLengthInit","EthMaxMsgLengthInit"="$EthMaxMsgLengthInit","XcpRConnectionType"="XcpRSourceInterfaceType","FlxHeaderAlignment"="$FlxHeaderAlignment","SequenceCorrection"="$SequenceCorrection","XcpRMaxDataLength"="$XcpRMaxDataLength"!][!//
    [!VAR "RxSrcEcuCPathName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduReference))"!][!//
  {
    [!INDENT "4"!][!//
    /* XcpR Rx Source PDU: [!"as:name(.)"!] */
    [!"text:toupper(XcpRIsSrcMasterConnection)"!], /* IsMasterConnection */
    [!"num:i($IntPduBufId)"!]U, /* map PDU to internal buffer Id */
    [!"num:i(XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduId)"!]U, /* Pdu Id used by LowerLayer for XcpR_RxIndication */
    [!IF "count(../../XcpRSourcePDUConfiguration/eb-list::*[XcpRSourceInterfaceType = 'XcpRSourceConnectionOverEthernet']) > 0"!]
      [!IF "node:existsAndTrue(./XcpRIsSrcMasterConnection)"!]
        [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_ETHERNET'"!][!//
          [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdSocketRoute/eb-list::*/SoAdRxSocketConnOrSocketConnBundleRef)"!]
            [!VAR "EcuCFound" = "'false'"!]
            [!LOOP "node:ref(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*"!]
              [!IF "as:name(node:ref(./SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName"!]
                [!VAR "EcuCFound" = "'true'"!]
              [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$EcuCFound"!][!//
              [!SELECT "node:ref(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*[(count(SoAdSocketRouteDest/eb-list::*) > 0) and node:refvalid(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef) and (as:name(node:ref(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName)][1]"!]
              [!IF "not(node:refvalid(SoAdRxSocketConnOrSocketConnBundleRef))"!]
                [!ERROR "Invalid value for node SoAdRxSocketConnOrSocketConnBundleRef: Invalid reference."!]
              [!ENDIF!]
              [!VAR "SoAdConnectionName" = "as:name(node:ref(SoAdRxSocketConnOrSocketConnBundleRef))"!]
              [!VAR "SoAdConnectionGroupName" = "as:name(node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../..)"!]
              [!"node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/SoAdSocketId"!]U, /* SoAd Rx socket connection Id([!"$SoAdConnectionGroupName"!]_[!"$SoAdConnectionName"!]) */
              [!IF "(node:refvalid(node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../../SoAdSocketLocalAddressRef) and node:ref(node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../../SoAdSocketLocalAddressRef)/TcpIpDomainType  = 'TCPIP_AF_INET6')"!]
                [!"'TRUE'"!], /* flag if SoAd connection is IP V6*/
              [!ELSE!]
               [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
              [!ENDIF!]
              [!ENDSELECT!]
            [!ELSE!]
              [!ERROR "The XcpR configuration contains an Ethernet source which does not share a similar RxPdu EcuC reference with an EcuC Pdu configured as an entry in the SoAdSocketRouteDest list. As a consequence, the SoAd Rx socket connection Id cannot be derived."!]
            [!ENDIF!]
          [!ENDIF!]
        [!ELSE!]
          (SoAd_SoConIdType)XCPR_IGNORED_SOCON_ID, /* Unused SoAd Rx socket connection Id */
          [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
        [!ENDIF!]
      [!ELSE!]
        (SoAd_SoConIdType)XCPR_IGNORED_SOCON_ID, /* Unused SoAd Rx socket connection Id */
        [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
      [!ENDIF!]
    [!ENDIF!]
    XCPR_RX_PDU_DIRECTION, /* PDU Type */
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRSrcPduSupportRxFromRxIndication)"!][!//
      XCPR_RECEPTION_ON_RX_INDICATION, /* the type of processing */
    [!ELSE!][!//
      XCPR_RECEPTION_ON_MAINFUNCTION, /* the type of processing */
    [!ENDIF!][!//
    [!"num:i($PduStartPosInRx)"!]U, /* Pdu data start position into Rx buffer data */
    [!ENDINDENT!][!//
    {
    [!INDENT "6"!][!//
      /* PDU Attributes per source */
      [!"$XcpRMaxDataLength"!]U, /* MaxPackageSize */
      [!"XcpRSourcePDUAttributes/XcpRSrcMaxCto"!]U, /* MaxCTO */
      [!"XcpRSourcePDUAttributes/XcpRSrcMaxDto"!]U, /* MaxDTO */
    [!IF "node:exists(XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm)"!][!//
      [!"XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm"!]U, /* XcpRSrcMaxCtoPgm */
    [!ELSE!][!//
      0U, /* XcpRSrcMaxCtoPgm */
    [!ENDIF!][!//
      [!"num:i($XcpRPackagePduSize)"!]U, /* PDU Length Max - Maximum size for a PDU */
      [!"num:i($XcpRPackageHeaderSize)"!]U /* PDU header size */
    [!VAR "IntPduBufId" = "$IntPduBufId + 1"!][!//
    [!ENDINDENT!][!//
    },
    {
    [!INDENT "6"!][!//
    /* Bus Attributes per source */
    [!IF "$ConnectionType != 'XCPR_CONNECTION_OVER_ETHERNET'"!]
      [!"$ConnectionType"!], /* XcpR connection type */
    [!ELSE!]
      [!VAR "RxSrcEcuCPathName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduReference))"!][!//
      [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdSocketRoute/eb-list::*/SoAdRxSocketConnOrSocketConnBundleRef)"!]
        [!VAR "EcuCFound" = "'false'"!]
        [!LOOP "node:ref(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*"!]
          [!IF "as:name(node:ref(./SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName"!]
            [!VAR "EcuCFound" = "'true'"!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$EcuCFound"!][!//
          [!SELECT "node:ref(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*[(count(SoAdSocketRouteDest/eb-list::*) > 0) and node:refvalid(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef) and (as:name(node:ref(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName)]"!]
          [!IF "not(node:refvalid(SoAdRxSocketConnOrSocketConnBundleRef))"!]
            [!ERROR "Invalid value for node SoAdRxSocketConnOrSocketConnBundleRef: Invalid reference."!]
          [!ENDIF!]
          [!IF "node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketTcp'"!]
            [!"'XCPR_CONNECTION_OVER_TCPIP'"!], /* XcpR connection type */
          [!ELSEIF "node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketUdp'"!]
            [!"'XCPR_CONNECTION_OVER_UDPIP'"!], /* XcpR connection type */
          [!ENDIF!]
          [!ENDSELECT!]
        [!ELSE!]
          [!ERROR "The XcpR configuration contains an Ethernet source which does not share a similar RxPdu EcuC reference with an EcuC Pdu configured as an entry in the SoAdSocketRouteDest list. As a consequence, the type of Ethernet connection (TCP/UDP) cannot be derived."!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "($NoOfSrcCanFDPdus > 0) or ($NoOfDestCanFDPdus > 0)"!][!//
      [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_CANFD'"!]
        [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceCanFdMaxDlcRequired)"!][!//
          [!"num:integer(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceCanFdMaxDlc)"!]U, /* CanFD MAX_DLC value */
        [!ELSE!]
          0U, /* CanFD MAX_DLC value (XcpRSourceCanFdMaxDlcRequired disabled) */
        [!ENDIF!]
          0U, /* CanFD Fill byte value (not used) */
      [!ELSE!]
        0U, /* CanFD MAX_DLC value   (not used) */
        0U, /* CanFD Fill byte value (not used) */
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "($NoOfSrcFlexRayPdus > 0) or ($NoOfDestFlexRayPdus > 0)"!][!//
      [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_FLEXRAY'"!][!//
        [!"num:integer(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceFlxNodeAddress)"!]U,  /* FlexRay network address */
        [!CALL "GetFlxHeaderAlignment","FlxHeaderAlignment"="$FlxHeaderAlignment"!][!//
        [!"num:integer($XcpRPackageAlignment)"!]U, /* FlexRay package alignment */
      [!ELSE!][!//
        0U, /* FlexRay network address   (not used) */
        0U, /* FlexRay package alignment (not used) */
      [!ENDIF!][!//
    [!ENDIF!][!//
      XCPR_IGNORED_CNT_ID /* Id of internal package counter */
    [!ENDINDENT!][!//
    },
    [!INDENT "4"!][!//
    [!VAR "RxSrcConnectionFlags"="''"!]
    [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneFlexRayFrame)"!][!//
      [!VAR "RxSrcConnectionFlags"="concat($RxSrcConnectionFlags,'XCPR_RECEPTION_MULTIPLE_PACKING',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourcePackMultiMsgInOneEthernetFrame)"!][!//
      [!VAR "RxSrcConnectionFlags"="concat($RxSrcConnectionFlags,'XCPR_RECEPTION_MULTIPLE_PACKING',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRRxSrcPduSupportTxFromRxIndication)"!][!//
      [!VAR "RxSrcConnectionFlags"="concat($RxSrcConnectionFlags,'XCPR_TRANSMISSION_FROM_RXINDICATION',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceOpenSoCon)"!][!//
      [!VAR "RxSrcConnectionFlags"="concat($RxSrcConnectionFlags,'XCPR_RECEPTION_OPEN_SOCON_FLAG',' ')"!]
    [!ENDIF!]
    [!CALL "PrintPropertyFlags","PropertyList"="$RxSrcConnectionFlags","CommentString"="'Properties and supported types for this PDU'","Indentation"="4"!]
    [!ENDINDENT!][!//
    [!VAR "SrcName" = "as:name(.)"!][!//
    {
    [!INDENT "6"!][!//
    [!VAR "NoOfDest" = "0"!][!//
    [!LOOP "(../../XcpRRoutingPaths/eb-list::*[as:name(node:ref(XcpRSourcePduRef)) = $SrcName])"!][!//
      [!VAR "DestName" = "as:name(node:ref(XcpRDestinationPduRef))"!][!//
      [!VAR "DestIdx" = "0"!][!//
      [!LOOP "util:distinct(node:order(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId'))"!][!//
        [!IF "$DestName = as:name(.)"!][!//
          &XcpR_DestConf[[!"num:i($DestIdx)"!]],/* Link to Tx destination */[!//

          [!VAR "NoOfDest" = "$NoOfDest + 1"!][!//
        [!ENDIF!][!//
        [!VAR "DestIdx" = "$DestIdx + 1"!][!//
      [!ENDLOOP!][!//
      [!LOOP "(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRRxPdu'])"!][!//
        [!IF "$DestName = as:name(.)"!][!//
          &XcpR_DestConf[[!"num:i($DestIdx)"!]],/* Link to Rx destination */[!//

          [!VAR "NoOfDest" = "$NoOfDest + 1"!][!//
        [!ENDIF!][!//
        [!VAR "DestIdx" = "$DestIdx + 1"!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!FOR "Idx" = "num:i($NoOfDest)+1" TO "2"!][!//
      NULL_PTR,
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
    }
    [!VAR "PduStartPosInRx" = "$PduStartPosInRx + $XcpRPackagePduSize"!][!//
  },
  [!ENDLOOP!][!//
[!IF "num:integer(count(XcpRGeneral/XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'])) > 0"!][!//
  [!LOOP "util:distinct(node:order(XcpRGeneral/XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxSourcePduId'))"!]
    [!INDENT "0"!]
    [!VAR "FlxMaxMsgLengthInit"="0"!][!//
    [!VAR "EthMaxMsgLengthInit"="0"!][!//
    [!VAR "FlxPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "EthPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "FlxHeaderAlignment"="''"!][!//
    [!VAR "SequenceCorrection"="'false'"!][!//
    [!VAR "XcpRMaxDataLength" = "num:max(text:split(concat(num:i(node:when(node:exists(XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm), XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm, 0)), ' ', num:i(XcpRSourcePDUAttributes/XcpRSrcMaxCto), ' ', num:i(XcpRSourcePDUAttributes/XcpRSrcMaxDto))))"!][!//
    [!CALL "GetSourceConnectionType","InterfaceType"="XcpRSourceInterfaceType"!][!//
    [!ENDINDENT!]
    [!CALL "GetPackagePduSize","FlxPackMultiMsgInOneFrame"="$FlxPackMultiMsgInOneFrame","EthPackMultiMsgInOneFrame"="$EthPackMultiMsgInOneFrame","FlxMaxMsgLengthInit"="$FlxMaxMsgLengthInit","EthMaxMsgLengthInit"="$EthMaxMsgLengthInit","XcpRConnectionType"="XcpRSourceInterfaceType","FlxHeaderAlignment"="$FlxHeaderAlignment","SequenceCorrection"="$SequenceCorrection","XcpRMaxDataLength"="$XcpRMaxDataLength"!]
  {
    [!INDENT "4"!][!//
    /* XcpR Tx Source PDU: [!"as:name(.)"!] */
    FALSE, /* IsMasterConnection */
    [!"num:i($IntPduBufId)"!]U, /* map PDU to internal buffer Id */
    [!"num:i(XcpRPdu/eb-choice::*[1]/XcpRTxSourcePduId)"!]U, /* Pdu Id used by UpperLayer for XcpR_Transmit */
    [!IF "count(../../XcpRSourcePDUConfiguration/eb-list::*[XcpRSourceInterfaceType = 'XcpRSourceConnectionOverEthernet']) > 0"!]
    (SoAd_SoConIdType)XCPR_IGNORED_SOCON_ID, /* Unused SoAd Rx socket connection Id */
    [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
    [!ENDIF!]
    XCPR_TX_PDU_DIRECTION, /* PDU type - Rx or Tx */
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRSrcPduSupportRxFromXcpRTransmit)"!]
      XCPR_RECEPTION_ON_RX_INDICATION, /* the type of processing */
    [!ELSE!]
      XCPR_RECEPTION_ON_MAINFUNCTION, /* the type of processing */
    [!ENDIF!]
    [!"num:i($PduStartPosInRx)"!]U, /* Pdu data start position into Rx buffer data */
    [!ENDINDENT!]
    {
    [!INDENT "6"!][!//
      /* PDU Attributes per source */
      [!"$XcpRMaxDataLength"!]U, /* MaxPackageSize */
      [!"num:integer(XcpRSourcePDUAttributes/XcpRSrcMaxCto)"!]U, /* MaxCTO */
      [!"num:integer(XcpRSourcePDUAttributes/XcpRSrcMaxDto)"!]U, /* MaxDTO */
    [!IF "node:exists(XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm)"!]
      [!"num:integer(XcpRSourcePDUAttributes/XcpRSrcMaxCtoPgm)"!]U, /* XcpRSrcMaxCtoPgm */
    [!ELSE!]
      0U, /* XcpRSrcMaxCtoPgm */
    [!ENDIF!][!//
      [!"num:i($XcpRPackagePduSize)"!]U, /* PDU Length Max - Maximum size for a PDU */
      [!"num:i($XcpRPackageHeaderSize)"!]U /* PDU header size */
    [!ENDINDENT!]
    },
    {
    [!INDENT "6"!][!//
    /* Bus Attributes per source */
    [!"$ConnectionType"!],
    [!IF "($NoOfSrcCanFDPdus > 0) or ($NoOfDestCanFDPdus > 0)"!][!//
      0U, /* not used for a Tx source */
      0U, /* not used for a Tx source */
    [!ENDIF!][!//
    [!IF "($NoOfSrcFlexRayPdus > 0) or ($NoOfDestFlexRayPdus > 0)"!][!//
      0U, /* not used for a Tx source */
      0U, /* not used for a Tx source */
    [!ENDIF!]
      XCPR_IGNORED_CNT_ID /* Id of internal package counter */
    [!ENDINDENT!]
    },
    [!INDENT "4"!][!//
    [!VAR "TxSrcConnectionFlags"="''"!]
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRTxSrcPduSupportTxFromXcpRTransmit)"!][!//
      [!VAR "TxSrcConnectionFlags"="concat($TxSrcConnectionFlags,'XCPR_TRANSMISSION_FROM_RXINDICATION',' ')"!]
    [!ENDIF!]
    [!CALL "PrintPropertyFlags","PropertyList"="$TxSrcConnectionFlags","CommentString"="'Properties and supported types for this PDU'","Indentation"="4"!]
    [!ENDINDENT!][!//
    [!VAR "SrcName" = "as:name(.)"!][!//
    {
    [!INDENT "6"!]
    [!VAR "NoOfDest" = "0"!][!//
    [!LOOP "(../../XcpRRoutingPaths/eb-list::*[as:name(node:ref(XcpRSourcePduRef)) = $SrcName])"!][!//
      [!VAR "DestName" = "as:name(node:ref(XcpRDestinationPduRef))"!][!//
      [!VAR "DestIdx" = "0"!][!//
      [!LOOP "util:distinct(node:order(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId'))"!][!//
        [!IF "$DestName = as:name(.)"!][!//
          &XcpR_DestConf[[!"num:i($DestIdx)"!]],/* Link to Tx destination */[!//

          [!VAR "NoOfDest" = "$NoOfDest + 1"!][!//
        [!ENDIF!][!//
        [!VAR "DestIdx" = "$DestIdx + 1"!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!FOR "Idx" = "num:i($NoOfDest)+1" TO "2"!][!//
      NULL_PTR,
    [!ENDFOR!][!//
    [!ENDINDENT!]
    }
    [!VAR "PduStartPosInRx" = "$PduStartPosInRx + $XcpRPackagePduSize"!]
  },
    [!VAR "IntPduBufId" = "$IntPduBufId + 1"!]
  [!ENDLOOP!]
[!ENDIF!]
};

/** \brief List of configured Transmission PDUs */
CONST(XcpR_DestPduType, XCPR_CONST) XcpR_DestConf[XCPR_NO_OF_DESTINATION_PDUS] =
{
[!VAR "PduStartPosInRx" = "0"!][!//
[!VAR "IntPduBufId" = "0"!][!//
[!VAR "IdPackageCnt" = "0"!][!//
[!VAR "XcpRTcpIpConns" = "0"!]
[!VAR "SoAdSoConModeChgEnabled" = "'false'"!]
  [!LOOP "util:distinct(node:order(XcpRGeneral/XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId'))"!]
    [!VAR "DestinationHasCounter" = "'false'"!][!//
    [!VAR "FlxMaxMsgLengthInit"="0"!][!//
    [!VAR "EthMaxMsgLengthInit"="0"!][!//
    [!VAR "FlxPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "EthPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "FlxHeaderAlignment"="''"!][!//
    [!VAR "SequenceCorrection"="'false'"!][!//
    [!VAR "XcpRMaxDataLength" = "num:max(text:split(concat(num:i(node:when(node:exists(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm), XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm, 0)), ' ', num:i(XcpRDestinationPDUAttributes/XcpRDestMaxCto), ' ', num:i(XcpRDestinationPDUAttributes/XcpRDestMaxDto))))"!][!//
    [!CALL "GetDestinationConnectionType","InterfaceType"="XcpRDestinationInterfaceType"!]
    [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_FLEXRAY'"!][!//
      [!VAR "SequenceCorrection"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationSequenceCorrectionEnabled"!]
      [!VAR "FlxHeaderAlignment"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationFlxHeaderAlignment"!]
      [!VAR "FlxPackMultiMsgInOneFrame"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneFlexRayFrame"!]
      [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneFlexRayFrame)"!]
        [!VAR "FlxMaxMsgLengthInit"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationMaxFlexMsgLength"!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_ETHERNET'"!][!//
      [!VAR "EthPackMultiMsgInOneFrame"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneEthernetFrame"!]
      [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneEthernetFrame)"!]
        [!VAR "EthMaxMsgLengthInit"="XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationMaxEthernetMsgLength"!]
      [!ENDIF!]
    [!ENDIF!]
    [!CALL "GetPackagePduSize","FlxPackMultiMsgInOneFrame"="$FlxPackMultiMsgInOneFrame","EthPackMultiMsgInOneFrame"="$EthPackMultiMsgInOneFrame","FlxMaxMsgLengthInit"="$FlxMaxMsgLengthInit","EthMaxMsgLengthInit"="$EthMaxMsgLengthInit","XcpRConnectionType"="XcpRDestinationInterfaceType","FlxHeaderAlignment"="$FlxHeaderAlignment","SequenceCorrection"="$SequenceCorrection","XcpRMaxDataLength"="$XcpRMaxDataLength"!]
    [!VAR "TxDestName" = "as:name(.)"!][!//
    [!VAR "TxDestEcuCPathName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduReference))"!][!//
  {
    [!INDENT "4"!][!//
    /* XcpR Tx Destination PDU: [!"as:name(.)"!] */
    [!"text:toupper(XcpRIsDestMasterConnection)"!], /* IsMasterConnection */
    [!"num:i($IntPduBufId)"!]U, /* map PDU to internal buffer Id */
    [!"num:i(XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId)"!]U, /* Pdu Id used by LowerLayer for XcpR_TxConfirmation */
    [!"num:i(XcpRPdu/eb-choice::*[1]/XcpRLowerLayerDestinationPduId)"!]U, /* Lower Layer Destination Pdu ID */
    [!IF "num:integer(count(../../XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'])) > 0"!]
      [!VAR "ValidRefFound" = "'false'"!][!//
      [!VAR "TxPduId"="'255'"!]
      [!LOOP "(../../XcpRRoutingPaths/eb-list::*[as:name(node:ref(XcpRDestinationPduRef)) = $TxDestName])"!][!//
        [!VAR "LinkedSrcName" = "as:name(node:ref(XcpRSourcePduRef))"!][!//
        [!LOOP "util:distinct(node:order(../../XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxSourcePduId'))"!][!//
          [!IF "$LinkedSrcName = as:name(.)"!][!//
            [!VAR "TxSourceEcuCPathName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRTxSourcePduReference))"!]
            [!LOOP "util:distinct(node:order(as:modconf('Xcp')[1]/XcpConfig/eb-list::*[1]/XcpPdu/eb-list::*[.='XcpTxPdu'], 'XcpTxPduId'))"!]
              [!IF "as:name(node:ref(XcpTxPduRef)) = $TxSourceEcuCPathName"!]
                [!VAR "TxPduId"="num:i(XcpTxPduId)"!]
                [!VAR "ValidRefFound" = "'true'"!][!//
              [!ENDIF!]
            [!ENDLOOP!]
            [!IF "$ValidRefFound = 'false'"!]
              [!ERROR "The XcpR configuration contains a TxSource which does not share a similar TxPduId EcuC reference as a TxPdu from the Xcp configuration. As a consequence, the XcpTxPduId for TxConfirmation cannot be derived"!]
            [!ENDIF!]
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
      [!IF "$ValidRefFound"!]
        /* !LINKSTO XcpR.Impl.UpperLayerTxConfirmationPduId, 1 */
        [!"$TxPduId"!]U, /* PduId used for UL TxConfirmation/TriggerTransmit */
      [!ELSE!]
        0xFFU, /* UL TxConfirmation/TriggerTransmit PduId - invalid value */
      [!ENDIF!]
      [!VAR "NrTxSources"="num:integer(count(../../XcpRSourcePDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu']))"!]
    [!ELSE!]
      0xFFU, /* UL TxConfirmation/TriggerTransmit PduId - invalid value */
      [!VAR "NrTxSources"="0"!]
    [!ENDIF!]
    [!IF "count(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet']) > 0"!]
      [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_ETHERNET'"!][!//
        [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdPduRoute/eb-list::*/SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)"!]
          [!SELECT "node:ref(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/SoAdPduRoute/eb-list::*[node:refvalid(SoAdTxPduRef) and (as:name(node:ref(SoAdTxPduRef)) = $TxDestEcuCPathName) and (count(SoAdPduRouteDest/eb-list::*) > 0)]"!]
            [!IF "not(node:refvalid(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef))"!]
              [!ERROR "Invalid value for node SoAdTxSocketConnOrSocketConnBundleRef: Invalid reference."!]
            [!ENDIF!]
            [!VAR "SoAdConnectionName" = "as:name(node:ref(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef))"!]
            [!VAR "SoAdConnectionGroupName" = "as:name(node:ref(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef)/../..)"!]
            [!"node:ref(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef)/SoAdSocketId"!]U, /* SoAd Tx socket connection Id([!"$SoAdConnectionGroupName"!]_[!"$SoAdConnectionName"!]) */
            [!IF "(node:refvalid(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef) and node:refvalid(node:ref(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketLocalAddressRef) and node:ref(node:ref(SoAdPduRouteDest/*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketLocalAddressRef)/TcpIpDomainType  = 'TCPIP_AF_INET6')"!]
                [!"'TRUE'"!], /* flag if SoAd connection is IP V6*/
            [!ELSE!]
               [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
            [!ENDIF!]
          [!ENDSELECT!]
        [!ENDIF!]
      [!ELSE!]
        (SoAd_SoConIdType)XCPR_IGNORED_SOCON_ID, /* Unused SoAd Tx socket connection Id */
        [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
      [!ENDIF!]
    [!ENDIF!]
    XCPR_TX_PDU_DIRECTION, /* PDU type - Rx or Tx */
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRDestPduSupportTxFromTxConfirmation)"!]
      XCPR_TRANSMISSION_ON_TX_CONFIRMATION, /* the type of processing */
    [!ELSE!]
      XCPR_TRANSMISSION_ON_MAINFUNCTION, /* the type of processing */
    [!ENDIF!]
    [!"num:i($PduStartPosInRx)"!]U, /* Pdu data start position into Tx buffer data */
    [!CALL "GetCallbackFunction", "Connection"="$ConnectionType", "PDUType"="'Tx'", "NrOfTxSources"="$NrTxSources"!]
    [!"$RxIndicationFunc"!], /* RxIndication */
    [!"$TxConfirmationFunc"!], /* TxConfirmation */
    [!"$TriggerTransmitFunc"!], /* TriggerTransmit */
    [!"$TransmitFunc"!], /* Transmit */
    [!ENDINDENT!][!//
    {
    [!INDENT "6"!][!//
      /* PDU Attributes per destination */
      [!"$XcpRMaxDataLength"!]U, /* Max Package Size */
      [!"num:integer(XcpRDestinationPDUAttributes/XcpRDestMaxCto)"!]U, /* MaxCTO */
      [!"num:integer(XcpRDestinationPDUAttributes/XcpRDestMaxDto)"!]U, /* MaxDTO */
    [!IF "node:exists(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm)"!]
      [!"num:integer(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm)"!]U, /* XcpRDestMaxCtoPgm */
    [!ELSE!]
      0U, /* XcpRDestMaxCtoPgm */
    [!ENDIF!]
      [!"num:i($XcpRPackagePduSize)"!]U, /* PDU Length Max - Maximum size for a PDU */
      [!"num:i($XcpRPackageHeaderSize)"!]U /* PDU header size */
    [!VAR "IntPduBufId" = "$IntPduBufId + 1"!]
    [!ENDINDENT!][!//
    },
    {
    [!INDENT "6"!][!//
      /* Bus Attributes per destination */
    [!IF "$ConnectionType != 'XCPR_CONNECTION_OVER_ETHERNET'"!]
      [!"$ConnectionType"!], /* XcpR connection type */
    [!ELSE!]
        [!VAR "DestEcuCPduName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduReference))"!][!//
        [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdPduRoute/eb-list::*/SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)"!]
          [!IF "count(node:ref(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/SoAdPduRoute/eb-list::*[node:refvalid(SoAdTxPduRef) and (as:name(node:ref(SoAdTxPduRef)) = $DestEcuCPduName) and node:refvalid(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef) and (node:ref(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketTcp')]) > 0"!]
            [!VAR "XcpRTcpIpConns" = "$XcpRTcpIpConns + 1"!]
          [!ENDIF!]
          [!IF "node:refvalid(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)"!]
            [!IF "(node:existsAndTrue(node:ref(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/../../SoAdBswModules/eb-list::*[as:name(.) = 'XcpR']/SoAdSoConModeChg))"!]
              [!VAR "SoAdSoConModeChgEnabled" = "'true'"!]
            [!ENDIF!]
          [!ENDIF!]
          [!IF "count(node:ref(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/SoAdPduRoute/eb-list::*[node:refvalid(SoAdTxPduRef) and (as:name(node:ref(SoAdTxPduRef)) = $DestEcuCPduName) and node:refvalid(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef) and (node:ref(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketTcp')]) > 0"!]
            [!"'XCPR_CONNECTION_OVER_TCPIP'"!], /* XcpR connection type */
          [!ELSEIF "count(node:ref(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/SoAdPduRoute/eb-list::*[node:refvalid(SoAdTxPduRef) and (as:name(node:ref(SoAdTxPduRef)) = $DestEcuCPduName) and node:refvalid(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef) and (node:ref(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketUdp')]) > 0"!]
            [!"'XCPR_CONNECTION_OVER_UDPIP'"!], /* XcpR connection type */
          [!ELSE!]
            [!ERROR "The XcpR configuration contains an Ethernet destination which does not share a similar TxPdu EcuC reference with an EcuC Pdu configured as an entry in the SoAdPduRoute list. As a consequence, the type of Ethernet connection (TCP/UDP) cannot be derived"!]
          [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
    [!IF "($NoOfDestCanFDPdus > 0) or ($NoOfSrcCanFDPdus > 0)"!]
      [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_CANFD'"!]
        [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationCanFdMaxDlcRequired)"!][!//
          [!"num:integer(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationCanFdMaxDlc)"!]U, /* CanFD MAX_DLC value */
        [!ELSE!]
          0U, /* CanFD MAX_DLC value (XcpRDestinationCanFdMaxDlcRequired disabled) */
        [!ENDIF!]
        [!"num:integer(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationCanFdFillValue)"!]U, /* CanFD Fill byte value */
      [!ELSE!]
        0U,  /* CanFD MAX_DLC value   (not used) */
        0U,  /* CanFD Fill byte value (not used) */
      [!ENDIF!]
    [!ENDIF!]
    [!IF "($NoOfDestFlexRayPdus > 0) or ($NoOfSrcFlexRayPdus > 0)"!]
      [!IF "$ConnectionType = 'XCPR_CONNECTION_OVER_FLEXRAY'"!]
        [!"num:integer(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationFlxNodeAddress)"!]U,  /* FlexRay network address */
        [!CALL "GetFlxHeaderAlignment","FlxHeaderAlignment"="$FlxHeaderAlignment"!]
        [!"num:integer($XcpRPackageAlignment)"!]U, /* FlexRay package alignment */
      [!ELSE!]
        0U, /* FlexRay network address   (not used) */
        0U, /* FlexRay package alignment (not used) */
      [!ENDIF!]
    [!ENDIF!]
    [!IF "num:integer(count(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverFlexRay'])) > 0"!]
      [!IF "(XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverFlexRay') and ($SequenceCorrection = 'true')"!]
        [!VAR "DestinationHasCounter" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "num:integer(count(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet'])) > 0"!]
      [!IF "(XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet')"!]
        [!VAR "DestinationHasCounter" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "$DestinationHasCounter"!]
      [!"num:i($IdPackageCnt)"!]U /* Id of the packet counter */
      [!VAR "IdPackageCnt" = "$IdPackageCnt + 1"!]
    [!ELSE!]
      XCPR_IGNORED_CNT_ID /* Id of the packet counter */
    [!ENDIF!]
    [!ENDINDENT!][!//
    },
    [!INDENT "4"!][!//
    [!VAR "TxDestConnectionFlags"="''"!]
    [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationCanFdMaxDlcRequired)"!]
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_TRANSMISSION_MAX_DLC_ENABLED',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneFlexRayFrame)"!][!//
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_TRANSMISSION_MULTIPLE_PACKING',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationPackMultiMsgInOneEthernetFrame)"!][!//
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_TRANSMISSION_MULTIPLE_PACKING',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduSupportForCddTriggerTransmit) or node:existsAndTrue(XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduSupportForFrTriggerTransmit)"!]
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_SUPPORT_FOR_TRIGGER_TRANSMIT',' ')"!]
    [!ENDIF!]
    [!IF "$SequenceCorrection = 'true'"!]
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_TRANSMISSION_SEQUENCE_CORRECTION',' ')"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationOpenSoCon)"!]
      [!VAR "TxDestConnectionFlags"="concat($TxDestConnectionFlags,'XCPR_TRANSMISSION_OPEN_SOCON_FLAG',' ')"!]
    [!ENDIF!]
    [!CALL "PrintPropertyFlags","PropertyList"="$TxDestConnectionFlags","CommentString"="'Properties and supported types for this PDU'","Indentation"="4"!]
    [!ENDINDENT!][!//
    [!VAR "PduStartPosInRx" = "$PduStartPosInRx + $XcpRPackagePduSize"!]
  },
  [!ENDLOOP!]
[!IF "($XcpRTcpIpConns = 0) and ($SoAdSoConModeChgEnabled = 'true')"!][!//
  [!ERROR "SoAdSoConModeChg has to be disabled, for the dedicated XcpR configuration entry into 'SoAdBswModules' container, in case there is no XcpR connection over TCP/IP, configured ('SoAdSocketProtocol' = 'SoAdSocketTcp')"!]
[!ENDIF!]
[!IF "num:integer(count(XcpRGeneral/XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRRxPdu'])) > 0"!][!//
  [!LOOP "XcpRGeneral/XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRRxPdu']"!]
    [!VAR "FlxMaxMsgLengthInit"="0"!][!//
    [!VAR "EthMaxMsgLengthInit"="0"!][!//
    [!VAR "FlxPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "EthPackMultiMsgInOneFrame"="'false'"!][!//
    [!VAR "FlxHeaderAlignment"="''"!][!//
    [!VAR "SequenceCorrection"="'false'"!][!//
    [!VAR "XcpRMaxDataLength" = "num:max(text:split(concat(num:i(node:when(node:exists(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm), XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm, 0)), ' ', num:i(XcpRDestinationPDUAttributes/XcpRDestMaxCto), ' ', num:i(XcpRDestinationPDUAttributes/XcpRDestMaxDto))))"!][!//
    [!CALL "GetDestinationConnectionType","InterfaceType"="XcpRDestinationInterfaceType"!]
    [!CALL "GetPackagePduSize","FlxPackMultiMsgInOneFrame"="$FlxPackMultiMsgInOneFrame","EthPackMultiMsgInOneFrame"="$EthPackMultiMsgInOneFrame","FlxMaxMsgLengthInit"="$FlxMaxMsgLengthInit","EthMaxMsgLengthInit"="$EthMaxMsgLengthInit","XcpRConnectionType"="XcpRDestinationInterfaceType","FlxHeaderAlignment"="$FlxHeaderAlignment","SequenceCorrection"="$SequenceCorrection","XcpRMaxDataLength"="$XcpRMaxDataLength"!]
  {
    [!INDENT "4"!][!//
    /* XcpR Rx Destination PDU: [!"as:name(.)"!] */
    FALSE, /* IsMasterConnection */
    [!"num:i($IntPduBufId)"!]U, /* map PDU to internal buffer Id */
    0xFF, /* invalid value (Pdu Id used by LowerLayer for XcpR_TxConfirmation) */
    [!VAR "ULPdu"="as:name(node:ref(XcpRPdu/eb-choice::*[1]/XcpRRxDestinationPduReference))"!]
    [!VAR "ULValidRefFound" = "'false'"!][!//
    [!LOOP "util:distinct(node:order(as:modconf('Xcp')[1]/XcpConfig/eb-list::*[1]/XcpPdu/eb-list::*[node:name(.)='XcpRxPdu'], 'XcpRxPduId'))"!]
      [!IF "as:name(node:ref(XcpRxPduRef)) = $ULPdu"!]
        /* !LINKSTO XcpR.Impl.UpperLayerRxIndicationPduId, 1 */
        [!"num:i(XcpRxPduId)"!]U, /* Upper layer PDU ID */
        [!VAR "ULValidRefFound" = "'true'"!][!//
      [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$ULValidRefFound = 'false'"!]
      [!ERROR "The XcpR configuration contains a RxDestination which does not share a similar RxPduId EcuC reference as a RxPdu from the Xcp configuration. As a consequence, the XcpRxPduId for Xcp_RxIndication() cannot be derived"!]
    [!ENDIF!]
    0xFFU, /* Tx Confirmation PduId - invalid value */
    [!IF "count(../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet']) > 0"!]
      (SoAd_SoConIdType)XCPR_IGNORED_SOCON_ID, /* Unused SoAd Tx socket connection Id */
      [!"'FALSE'"!], /* flag if SoAd connection is IP V6*/
    [!ENDIF!]
    XCPR_RX_PDU_DIRECTION, /* PDU type - Rx or Tx */
    XCPR_PROCESSING_OF_RX_DEST_NOT_POSSIBLE, /* the type of processing */
    [!"num:i($PduStartPosInRx)"!]U, /* Pdu data start position into Tx buffer data */
    [!CALL "GetCallbackFunction", "Connection"="$ConnectionType", "PDUType"="'Rx'", "NrOfTxSources"="0"!]
    [!"$RxIndicationFunc"!], /* RxIndication */
    [!"$TxConfirmationFunc"!], /* TxConfirmation */
    [!"$TriggerTransmitFunc"!], /* TriggerTransmit */
    [!"$TransmitFunc"!], /* Transmit */
    [!ENDINDENT!][!//
    {
    [!INDENT "6"!][!//
      /* PDU Attributes per destination */
      [!"$XcpRMaxDataLength"!]U, /* Max Package Size */
      [!"num:i(XcpRDestinationPDUAttributes/XcpRDestMaxCto)"!]U, /* MaxCTO */
      [!"num:i(XcpRDestinationPDUAttributes/XcpRDestMaxDto)"!]U, /* MaxDTO */
    [!IF "node:exists(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm)"!]
      [!"num:i(XcpRDestinationPDUAttributes/XcpRDestMaxCtoPgm)"!]U, /* XcpRDestMaxCtoPgm */
    [!ELSE!]
      0U, /* XcpRDestMaxCtoPgm */
    [!ENDIF!]
      [!"num:i($XcpRPackagePduSize)"!]U, /* PDU Length Max - Maximum size for a PDU */
      [!"num:i($XcpRPackageHeaderSize)"!]U /* PDU header size */
    [!ENDINDENT!][!//
    },
    {
    [!INDENT "6"!][!//
      /* Bus Attributes per destination */
      [!"$ConnectionType"!],
    [!IF "($NoOfDestCanFDPdus > 0) or ($NoOfSrcCanFDPdus > 0)"!]
      0U, /* not used for Rx destination */
      0U, /* not used for Rx destination */
    [!ENDIF!]
    [!IF "($NoOfDestFlexRayPdus > 0) or ($NoOfSrcFlexRayPdus > 0)"!]
      0U, /* not used for Rx destination */
      0U, /* not used for Rx destination */
    [!ENDIF!]
      XCPR_IGNORED_CNT_ID /* Id of the packet counter */
    [!ENDINDENT!][!//
    },
    0U /* Properties and supported types for this PDU */
    [!VAR "PduStartPosInRx" = "$PduStartPosInRx + $XcpRPackagePduSize"!]
  },
    [!VAR "IntPduBufId" = "$IntPduBufId + 1"!][!//
  [!ENDLOOP!]
[!ENDIF!]
};


[!IF "num:integer(count(XcpRGeneral/XcpRRoutingToConnectionMapping/eb-list::*)) > 0"!][!//

[!VAR "XcpRMaxRoutingPaths" = "num:i(0)"!][!//
[!LOOP "(XcpRGeneral/XcpRRoutingToConnectionMapping/eb-list::*)"!][!//
  [!VAR "XcpRCurrentNrOfRoutingPaths" = "num:integer(count(./eb-list::*/eb-list::*))"!][!//
  [!IF "$XcpRCurrentNrOfRoutingPaths > $XcpRMaxRoutingPaths"!][!//
    [!VAR "XcpRMaxRoutingPaths" = "$XcpRCurrentNrOfRoutingPaths"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

/* !LINKSTO XcpR.Impl.ConnectionGroups.ActiveGroupInformation, 1 */
/** \brief List of configured Connection Groups */
CONST(XcpR_ConnectionGroupType, XCPR_CONST) XcpR_ConnectionGroups[XCPR_NO_OF_CONNECTION_GROUPS] =
{
  [!LOOP "XcpRGeneral/XcpRRoutingToConnectionMapping/eb-list::*"!][!//
  { /* Connection Group: [!"node:name(.)"!] */
    {
      [!VAR "NoOfDest" = "0"!][!//
      [!LOOP "./eb-list::*/*"!]
      {
        [!INDENT "8"!]
        [!IF "node:ref(node:ref(./XcpRRoutingPathRef)/XcpRDestinationPduRef)/XcpRPdu = 'XcpRTxPdu'"!]
          /* Tx Dest: "[!"as:name(node:ref(node:ref(./XcpRRoutingPathRef)/XcpRDestinationPduRef))"!]" from "[!"as:name(node:ref(./XcpRRoutingPathRef))"!]" */
        [!ELSE!]
          /* Rx Dest: "[!"as:name(node:ref(node:ref(./XcpRRoutingPathRef)/XcpRDestinationPduRef))"!]" from "[!"as:name(node:ref(./XcpRRoutingPathRef))"!]" */
        [!ENDIF!]
        [!VAR "DestName" = "as:name(node:ref(node:ref(./XcpRRoutingPathRef)/XcpRDestinationPduRef))"!][!//
        [!VAR "DestIdx" = "0"!][!//
        [!LOOP "util:distinct(node:order(../../../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId'))"!][!//
          [!IF "$DestName = as:name(.)"!][!//
            &XcpR_DestConf[[!"num:i($DestIdx)"!]],
            [!VAR "NoOfDest" = "$NoOfDest + 1"!][!//
          [!ENDIF!][!//
          [!VAR "DestIdx" = "$DestIdx + 1"!][!//
        [!ENDLOOP!][!//
        [!LOOP "(../../../../XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRRxPdu'])"!][!//
          [!IF "$DestName = as:name(.)"!][!//
            &XcpR_DestConf[[!"num:i($DestIdx)"!]],
            [!VAR "NoOfDest" = "$NoOfDest + 1"!][!//
          [!ENDIF!][!//
          [!VAR "DestIdx" = "$DestIdx + 1"!][!//
        [!ENDLOOP!][!//
        [!IF "node:ref(node:ref(./XcpRRoutingPathRef)/XcpRSourcePduRef)/XcpRPdu = 'XcpRRxPdu'"!]
          [!"num:i(node:ref(node:ref(./XcpRRoutingPathRef)/XcpRSourcePduRef)/XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduId)"!]U, /* Rx Source PduId */
        [!ELSE!]
          [!"num:i(node:ref(node:ref(./XcpRRoutingPathRef)/XcpRSourcePduRef)/XcpRPdu/eb-choice::*[1]/XcpRTxSourcePduId)"!]U, /* Tx Source PduId */
        [!ENDIF!]
        [!ENDINDENT!]
      },
      [!ENDLOOP!]
      [!FOR "Idx" = "num:i($NoOfDest)+1" TO "num:i($XcpRMaxRoutingPaths)"!][!//
      {
        NULL_PTR,
        (PduIdType) XCPR_INVALID_PDU_ID
      },
      [!ENDFOR!][!//
    }
  },
  [!ENDLOOP!][!//
};

[!ENDIF!][!//


[!IF "count(XcpRGeneral/XcpRDestinationPDUConfiguration/eb-list::*[XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet']) > 0"!]
  [!IF "$XcpRSupportForSoAdSocketProtocolTcp"!]
/** \brief List used to map TCP/IP socket connections towards an XcpR destination Id. */
CONST(XcpR_TcpIpSocketDestMapType, XCPR_CONST) XcpR_TcpIpSocketDestMapCfg[XCPR_NO_OF_TCPIP_SOCKET_CON] =
{
  [!LOOP "util:distinct(node:order(XcpRGeneral/XcpRDestinationPDUConfiguration/eb-list::*[XcpRPdu ='XcpRTxPdu'], 'XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId'))"!]
    [!VAR "SelectedDestinationId" = "XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId"!]
    [!VAR "SelectedDestinationName"="as:name(.)"!]
    [!VAR "DestEcuCPduName" = "as:name(node:ref(./XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduReference))"!][!//
    [!IF "node:exists(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef) and node:refvalid(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)"!]
      [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdPduRoute/eb-list::*/SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)"!]
        [!SELECT "node:ref(./XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationConnectionSoAdConfigRef)/SoAdPduRoute/eb-list::*[node:refvalid(SoAdTxPduRef) and (as:name(node:ref(SoAdTxPduRef)) = $DestEcuCPduName) and node:refvalid(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef) and (node:ref(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketTcp')]"!]
          [!SELECT "node:ref(SoAdPduRouteDest/eb-list::*/SoAdTxSocketConnOrSocketConnBundleRef)"!]
            [!VAR "SoAdConnectionName" = "concat(as:name(../..),'_',as:name(.))"!]
  {
    [!"SoAdSocketId"!]U, /* Id of the TcpIp socket connection ([!"$SoAdConnectionName"!]). */
    [!"$SelectedDestinationId"!]U, /* XcpR internal Destination Id ([!"$SelectedDestinationName"!]) */
  },
         [!ENDSELECT!]
       [!ENDSELECT!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
};
  [!ENDIF!]
[!ENDIF!]

#define XCPR_STOP_SEC_CONST_UNSPECIFIED
#include <XcpR_MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#define XCPR_START_SEC_CODE
#include <XcpR_MemMap.h>

#if (XCPR_OPEN_SO_CON == STD_ON)
/*-----------------------------[XcpR_InitSoAdConnections]------------------------*/

FUNC(Std_ReturnType, XCPR_CODE) XcpR_InitSoAdConnections(void)
{
  Std_ReturnType RetVal = E_OK;
[!VAR "SrcPresent" = "'false'"!]
[!IF "$XcpRSupportForSoAdSocketProtocolUdp = 'true'"!]
[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection) and (node:existsAndTrue(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection)))"!]
    [!IF "(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType = 'XcpRSourceConnectionOverEthernet')"!]
      [!IF "node:existsAndTrue(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceOpenSoCon)"!][!//
        [!VAR "SrcPresent" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]

[!VAR "DestPresent" = "'false'"!]
[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection))"!]
    [!IF "(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet')"!]
      [!IF "(node:existsAndTrue(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationOpenSoCon))"!]
        [!VAR "DestPresent" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

[!IF "$SrcPresent = 'true'"!]
  uint8 SrcIndex = 0xFF;
[!ENDIF!]

[!IF "$DestPresent = 'true'"!]
  uint8 DestIndex = 0xFF;
[!ENDIF!]

[!VAR "SoAdConnectionsFound" = "'false'"!]
[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "((node:exists(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection)) and (node:existsAndTrue(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection)) and (node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet'))"!]
    [!VAR "SoAdConnectionsFound" = "'true'"!]
  [!ENDIF!]
[!ENDLOOP!]

[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "((node:exists(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection)) and (node:existsAndTrue(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection)) and (node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType = 'XcpRSourceConnectionOverEthernet'))"!]
    [!VAR "SoAdConnectionsFound" = "'true'"!]
  [!ENDIF!]
[!ENDLOOP!]

[!IF "($XcpRSupportForSoAdSocketProtocolUdp = 'true') and ($SoAdConnectionsFound = 'true')"!]
  /* Open SoAd sockets related to XcpR Ethernet connections to the master Xcp */
  boolean DestSocketsOpened = TRUE;
[!ENDIF!]

[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection) and (node:existsAndTrue(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection)))"!]
    [!IF "(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet')"!]
      [!IF "(node:existsAndTrue(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationOpenSoCon))"!]
  DestIndex = [!"node:ref(./XcpRDestinationPduRef)/XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId"!]U;
  /* Open SoAd socket connection for XcpR destination: [!"as:name(node:ref(./XcpRDestinationPduRef))"!] */
  if (SoAd_OpenSoCon(XcpR_DestConf[DestIndex].SoAdTxConId) != E_OK)
  {
    /* the socket connection cannot be opened. */
    RetVal = E_NOT_OK;
      [!IF "$XcpRSupportForSoAdSocketProtocolUdp"!]
    DestSocketsOpened = FALSE;
      [!ENDIF!]
  }
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

[!IF "$XcpRSupportForSoAdSocketProtocolUdp"!]
[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection) and (node:existsAndTrue(node:ref(./XcpRSourcePduRef)/XcpRIsSrcMasterConnection)))"!]
    [!IF "(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType = 'XcpRSourceConnectionOverEthernet')"!]
      [!IF "node:existsAndTrue(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceOpenSoCon)"!][!//
  SrcIndex = [!"node:ref(./XcpRSourcePduRef)/XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduId"!]U;
  /* Open a SoAd socket connection for XcpR source: [!"as:name(node:ref(./XcpRSourcePduRef))"!] */
        [!VAR "RxSrcEcuCPathName" = "as:name(node:ref(node:ref(./XcpRSourcePduRef)/XcpRPdu/eb-choice::*[1]/XcpRRxSourcePduReference))"!][!//
        [!IF "node:exists(as:modconf('SoAd')/SoAdConfig/eb-list::*/SoAdSocketRoute/eb-list::*/SoAdRxSocketConnOrSocketConnBundleRef)"!]
          [!VAR "EcuCFound" = "'false'"!]
          [!LOOP "node:ref(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*"!]
            [!IF "as:name(node:ref(./SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName"!]
              [!VAR "EcuCFound" = "'true'"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!IF "$EcuCFound = 'true'"!][!//
            [!SELECT "node:ref(node:ref(./XcpRSourcePduRef)/XcpRSourceInterfaceType/eb-choice::*[1]/XcpRSourceConnectionSoAdConfigRef)/SoAdSocketRoute/eb-list::*[(count(SoAdSocketRouteDest/eb-list::*) > 0) and node:refvalid(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef) and (as:name(node:ref(SoAdSocketRouteDest/eb-list::*/SoAdRxPduRef)) = $RxSrcEcuCPathName)]"!]
            [!IF "node:ref(SoAdRxSocketConnOrSocketConnBundleRef)/../../SoAdSocketProtocol = 'SoAdSocketUdp'"!]
  if (DestSocketsOpened == TRUE)
  {
    if (SoAd_OpenSoCon(XcpR_SrcConf[SrcIndex].SoAdRxConId) != E_OK)
    {
      /* the socket connection cannot be open. */
      RetVal = E_NOT_OK;
    }
  }
              [!ENDIF!]
            [!ENDSELECT!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]

[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection) and node:existsAndFalse(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection))"!]
    [!IF "(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet')"!]
  /* Open SoAd sockets related to XcpR Ethernet connections on the internal bus */
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]
[!LOOP "(XcpRGeneral/XcpRRoutingPaths/eb-list::*)"!]
  [!IF "(node:exists(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection) and node:existsAndFalse(node:ref(./XcpRDestinationPduRef)/XcpRIsDestMasterConnection))"!]
    [!IF "(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType = 'XcpRDestinationConnectionOverEthernet')"!]
      [!IF "(node:existsAndTrue(node:ref(./XcpRDestinationPduRef)/XcpRDestinationInterfaceType/eb-choice::*[1]/XcpRDestinationOpenSoCon))"!]
  /* Open SoAd socket connection for XcpR destination: [!"as:name(node:ref(./XcpRDestinationPduRef))"!] */
  DestIndex = [!"node:ref(./XcpRDestinationPduRef)/XcpRPdu/eb-choice::*[1]/XcpRTxDestinationPduId"!]U;
  if (SoAd_OpenSoCon(XcpR_DestConf[DestIndex].SoAdTxConId) != E_OK)
  {
    /* the socket connection cannot be open. */
    RetVal = E_NOT_OK;
  }
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

  return RetVal;
}
#endif

#define XCPR_STOP_SEC_CODE
#include <XcpR_MemMap.h>
