/**
 * \file
 *
 * \brief AUTOSAR IpduM
 *
 * This file contains the implementation of the AUTOSAR
 * module IpduM.
 *
 * \version 3.3.57
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

[!INCLUDE "../../generate_macros/IpduM_Macros.m"!]

[!IF "var:defined('postBuildVariant')"!]
[!VAR "IPDUM_VARIANT_SUFFIX"="concat('_',$postBuildVariant)"!]
[!VAR "inclGuard" = "concat('IPDUM_SYMBOLICNAMES',$postBuildVariant,'_PBCFG_H')"!]
[!ELSE!]
[!VAR "IPDUM_VARIANT_SUFFIX"="''"!]
[!VAR "inclGuard" = "'IPDUM_SYMBOLICNAMES_PBCFG_H'"!]
[!ENDIF!]
#ifndef [!"$inclGuard"!]
#define [!"$inclGuard"!]

/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

/************************/
/* Symbolic name values */
/************************/
[!INDENT "0"!][!//
[!SELECT "IpduMConfig/*[1]"!][!//
  [!IF "node:exists(IpduMRxPathway/*)"!][!//
    [!LOOP "IpduMRxPathway/*"!]
      /*################################################################################################*/
      /* Rx pathway: [!"as:name(.)"!] */
      [!CALL "GetSymbolName",
        "ShortNameRef"="'./IpduMRxIndication'",
        "OldName"="as:name(.)"!][!//
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMRxIndication_'",
        "SymbolicName"="$SymbolName",
        "SymbolicIdName"="'IpduMRxHandleId'",
        "SymbolicValue"="node:path(./IpduMRxIndication/IpduMRxHandleId)",
        "PduName"="as:name(node:ref(./IpduMRxIndication/IpduMRxIndicationPduRef))",
        "VariantSuffix"="$IPDUM_VARIANT_SUFFIX"!][!//
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMTxPathway/*)"!][!//
    [!LOOP "IpduMTxPathway/*"!][!//
      /*################################################################################################*/
      /* Tx pathway: [!"as:name(.)"!] */
      [!IF "node:exists(./IpduMTxRequest/IpduMTxStaticPart)"!][!//
        [!CALL "GetSymbolName",
          "ShortNameRef"="'./IpduMTxRequest/IpduMTxStaticPart'",
          "OldName"="as:name(.)"!][!//
        [!CALL "GenSymbols",
          "SymbolicPrefix"="'IpduMConf_IpduMTxStaticPart_'",
          "SymbolicName"="$SymbolName",
          "SymbolicIdName"="'IpduMTxStaticHandleId'",
          "SymbolicValue"="node:path(./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticHandleId)",
          "PduName"="as:name(node:ref(./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))",
          "VariantSuffix"="$IPDUM_VARIANT_SUFFIX"!][!//
      [!ENDIF!][!//
      [!LOOP "IpduMTxRequest/IpduMTxDynamicPart/*"!][!//
        [!CALL "GenSymbols",
          "SymbolicPrefix"="'IpduMConf_IpduMTxDynamicPart_'",
          "SymbolicName"="as:name(.)",
          "SymbolicIdName"="'IpduMTxDynamicHandleId'",
          "SymbolicValue"="node:path(./IpduMTxDynamicHandleId)",
          "PduName"="as:name(node:ref(./IpduMTxDynamicPduRef))",
          "VariantSuffix"="$IPDUM_VARIANT_SUFFIX"!][!//
      [!ENDLOOP!][!//
      [!CALL "GetSymbolName",
        "ShortNameRef"="'./IpduMTxRequest'",
        "OldName"="as:name(.)"!][!//
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMTxRequest_'",
        "SymbolicName"="$SymbolName",
        "SymbolicIdName"="'IpduMTxConfirmationPduId'",
        "SymbolicValue"="node:path(./IpduMTxRequest/IpduMTxConfirmationPduId)",
        "PduName"="as:name(node:ref(./IpduMTxRequest/IpduMOutgoingPduRef))",
        "VariantSuffix"="$IPDUM_VARIANT_SUFFIX",
        "Legacy"="false()"!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainerRxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainerRxPdu/*"!]
      /* IpduMContainerRxPdu: [!"as:name(.)"!] */
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMContainerRxPdu_'",
        "SymbolicName"="as:name(.)",
        "SymbolicIdName"="'IpduMContainerRxHandleId'",
        "SymbolicValue"="node:path(./IpduMContainerRxHandleId)",
        "PduName"="as:name(node:ref(./IpduMContainerRxPduRef))",
        "VariantSuffix"="$IPDUM_VARIANT_SUFFIX",
        "Legacy"="false()"!][!//
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainedTxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainedTxPdu/*"!]
      /* IpduMContainedTxPdu: [!"as:name(.)"!] */
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMContainedTxPdu_'",
        "SymbolicName"="as:name(.)",
        "SymbolicIdName"="'IpduMContainedTxPduHandleId'",
        "SymbolicValue"="node:path(./IpduMContainedTxPduHandleId)",
        "PduName"="as:name(node:ref(./IpduMContainedTxPduRef))",
        "VariantSuffix"="$IPDUM_VARIANT_SUFFIX",
        "Legacy"="false()"!][!//
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainerTxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      [!IF "node:exists(./IpduMContainerTxHandleId)"!][!//
      /* IpduMContainerTxPdu: [!"as:name(.)"!] */
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMContainerTxPdu_'",
        "SymbolicName"="as:name(.)",
        "SymbolicIdName"="'IpduMContainerTxHandleId'",
        "SymbolicValue"="node:path(./IpduMContainerTxHandleId)",
        "PduName"="as:name(node:ref(./IpduMContainerTxPduRef))",
        "VariantSuffix"="$IPDUM_VARIANT_SUFFIX",
        "Legacy"="false()"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/*****************************************************/
/* Vendor specific outgoing and confirmation PDU IDs */
/*****************************************************/
#if (defined IPDUM_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES)
[!INDENT "0"!][!//
[!SELECT "IpduMConfig/*[1]"!][!//
  [!IF "node:exists(IpduMRxPathway/*)"!][!//
    [!LOOP "IpduMRxPathway/*"!]
     /*################################################################################################*/
      /* Rx pathway: [!"as:name(.)"!] */
      [!IF "node:exists(./IpduMRxIndication/IpduMRxStaticPart)"!][!/*
        */!][!CALL "GetOutputPduId","IpduMOutgoingPduRef"="IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef"!]
        /* [!"node:path(IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef)"!] */
[!VAR "SymbolName" = "concat('IPDUM_RX_OUTGOING_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
        #define [!"$SymbolName"!] [!"num:i($PduID)"!]U /* [!"as:name(node:ref(IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef))"!] Static Rx */
      [!ENDIF!][!//
      [!LOOP "IpduMRxIndication/IpduMRxDynamicPart/*"!]
        [!CALL "GetOutputPduId","IpduMOutgoingPduRef"="IpduMOutgoingDynamicPduRef"!][!/*
        */!]/* [!"node:path(IpduMOutgoingDynamicPduRef)"!] */
[!VAR "SymbolName" = "concat('IPDUM_RX_OUTGOING_ID_', as:name(./../../..), '_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
        #define [!"$SymbolName"!] [!"num:i($PduID)"!]U /* [!"as:name(node:ref(IpduMOutgoingDynamicPduRef))"!] Dynamic Rx */
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainedRxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainedRxPdu/*"!]
      /* IpduMContainedRxPdu: [!"as:name(.)"!] */
      [!CALL "GetOutputPduId","IpduMOutgoingPduRef"="./IpduMContainedRxPduRef"!][!/*
      */!]
[!VAR "SymbolName" = "concat('IPDUM_RX_OUTGOING_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
        #define [!"$SymbolName"!] [!"num:i($PduID)"!]U
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainerTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      /* IpduMContainerTxPdu: [!"as:name(.)"!] */
      [!CALL "GetOutputPduId", "IpduMOutgoingPduRef"="./IpduMContainerTxPduRef"!][!//
[!VAR "SymbolName" = "concat('IPDUM_TX_OUTGOING_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
      #define [!"$SymbolName"!] [!"num:i($PduID)"!]U  /* [!"as:name(node:ref(./IpduMContainerTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainedTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainedTxPdu/*"!]
      /* IpduMContainedTxPdu: [!"as:name(.)"!] */
      [!CALL "GetResponsePduId", "IpduMPduRef"="./IpduMContainedTxPduRef"!][!//
[!VAR "SymbolName" = "concat('IPDUM_TX_CONFIRM_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
      #define [!"$SymbolName"!] [!"num:i($ResponsePduID)"!]U  /* [!"as:name(node:ref(./IpduMContainedTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainerTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      /* IpduMContainerTxPdu: [!"as:name(.)"!] */
      [!CALL "GetResponsePduId", "IpduMPduRef"="./IpduMContainerTxPduRef"!][!//
[!VAR "SymbolName" = "concat('IPDUM_TX_CONFIRM_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
      #define [!"$SymbolName"!] [!"num:i($ResponsePduID)"!]U  /* [!"as:name(node:ref(./IpduMContainerTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMTxPathway/*)"!][!//
    [!LOOP "IpduMTxPathway/*"!]
     /*################################################################################################*/
      /* Tx pathway: [!"as:name(.)"!] */
      [!IF "node:exists(./IpduMTxRequest/IpduMTxStaticPart)"!][!/*
        */!][!IF "./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticConfirmation = 'true'"!][!/*
          */!][!CALL "GetResponsePduId","IpduMPduRef"="IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef"!]
              /* [!"node:path(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef)"!] */
[!VAR "SymbolName" = "concat('IPDUM_TX_CONFIRM_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
              #define [!"$SymbolName"!] [!"num:i($ResponsePduID)"!]U /* [!"as:name(node:ref(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))"!] Static Tx */
            [!ELSE!][!//
              /* [!"as:name(node:ref(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))"!] Disabled static TxConfirmation */
            [!ENDIF!][!//
      [!ENDIF!][!//
      [!LOOP "IpduMTxRequest/IpduMTxDynamicPart/*"!][!/*
        */!][!IF "./IpduMTxDynamicConfirmation = 'true'"!][!/*
          */!][!CALL "GetResponsePduId","IpduMPduRef"="./IpduMTxDynamicPduRef"!]
              /* [!"node:path(IpduMTxDynamicPduRef)"!] */
[!VAR "SymbolName" = "concat('IPDUM_TX_CONFIRM_ID_', as:name(./../../..), '_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
              #define [!"$SymbolName"!] [!"num:i($ResponsePduID)"!]U /* [!"as:name(node:ref(IpduMTxDynamicPduRef))"!] Dynamic Tx */
            [!ELSE!][!//
                 /* [!"as:name(node:ref(IpduMTxDynamicPduRef))"!]  Disabled dynamic TxConfirmation */
            [!ENDIF!][!//
      [!ENDLOOP!][!/*
        */!][!CALL "GetOutputPduId","IpduMOutgoingPduRef"="./IpduMTxRequest/IpduMOutgoingPduRef"!]
        /* [!"node:path(./IpduMTxRequest/IpduMOutgoingPduRef)"!] */
[!VAR "SymbolName" = "concat('IPDUM_TX_OUTGOING_ID_', as:name(.), $IPDUM_VARIANT_SUFFIX)"!][!//
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined!
#endif /* #if (defined [!"$SymbolName"!])*/
        #define [!"$SymbolName"!] [!"num:i($PduID)"!]U  /* [!"as:name(node:ref(./IpduMTxRequest/IpduMOutgoingPduRef))"!] Tx */
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef [!"$inclGuard"!] */
/*==================[end of file]===========================================*/
