/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \version 6.8.63
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!][!//
/*==================[inclusions]=============================================*/
[!INCLUDE "../../generate_macros/CanTp_PostBuild.m"!][!//
#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <TSAtomic_Assign.h>   /* atomic assign macros */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Api.h>         /* CanTp API declarations */
#include <CanTp_Internal.h>    /* internal macros and variables */
#include <CanTp_MultiMainFunction.h>
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

[!IF "CanTpGeneral/CanTpDedicatedChannelProcessingSupport = 'true'"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpGeneral/CanTpChannelProcessing/*"!][!//
[!VAR "ChannelProcessingName" = "as:name(.)"!][!//

[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_START_SEC_CODE
#include <CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MemMap.h>
#endif
[!ELSE!]
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]

[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
FUNC(void, CANTP_CODE) CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MainFunction_[!"$ChannelProcessingName"!](void)
[!ELSE!][!//
FUNC(void, CANTP_CODE) CanTp_MainFunction_[!"$ChannelProcessingName"!](void)
[!ENDIF!]
{
  CanTp_ConfChannelType index;

#if((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U)
  uint16 NonIdleChannel;
#else
  uint8 NonIdleChannel;
#endif

  DBG_CANTP_MAINFUNCTION_ENTRY();

  CANTP_ENTER_CRITICAL_SECTION();
  NonIdleChannel = CanTp_NonIdleChannelArray[CANTP_PARTITION_[!"num:i(node:pos(.))"!]];
  CANTP_LEAVE_CRITICAL_SECTION();

  /* !LINKSTO CanTp.EB.IdleChannels,1 */
  /* only do something in state CANTP_ON and if at least one channel is not idle */
  if((CanTp_InitVars.State == CANTP_ON) && (0U != NonIdleChannel))
  {
    /*for loop on configured channels*/
    for(index = 0; index < CANTP_NUMBER_CONFIGURED_CHANNELS; index++)
    {
      uint8 partition = CANTP_CFG_GET_CONFIGURED_PARTITION(index);
      CanTp_RxChannelType rx_channel = CANTP_CFG_GET_RXTPCHANNEL_FOR_PARTITION(index);
      CanTp_TxChannelType tx_channel = CANTP_CFG_GET_TXTPCHANNEL_FOR_PARTITION(index);

      /*check if the partition that refers this channel should be handled on this MainFunction*/
      if(partition == CANTP_PARTITION_[!"num:i(node:pos(.))"!])
      {
        /*check if a tx channel should be handled*/
        if(tx_channel != INVALID_TX_CHANNEL_ID)
        {
          CanTp_Decoupled_MainFunction_Tx(tx_channel);
        }
        else
        {
          /*do nothing*/
        }
        
        /*check if a rx channel should be handled
        if channel is half duplex, it has been already bandled by CanTp_Decoupled_MainFunction_Tx*/
        if((rx_channel != INVALID_RX_CHANNEL_ID) && (rx_channel != tx_channel))
        {
          CanTp_Decoupled_MainFunction_Rx(rx_channel);
        }
        else
        {
          /*do nothing*/
        }
      }
      else
      {
        /*nothing to do*/
      }
    }
  }
  
  DBG_CANTP_MAINFUNCTION_EXIT();
}

[!IF "as:modconf('CanTp')[1]/CanTpGeneral/CanTpMultiCoreSupport = 'true'"!][!//
[!VAR "PartitionsRefs" = "as:name(as:ref(CanTpEcucPartitionRef))"!][!//
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_STOP_SEC_CODE
#include <CanTp_[!"$MulticoreVendorID"!]_[!"$PartitionsRefs"!]_MemMap.h>
#endif
[!ELSE!]
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]

[!ENDLOOP!]

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif

FUNC(void, CANTP_CODE) CanTp_Decoupled_MainFunction_Rx(uint8 rx_channel)
{
  CanTp_ChannelHandling(rx_channel);
}

FUNC(void, CANTP_CODE) CanTp_Decoupled_MainFunction_Tx(uint8 tx_channel)
{
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;

  uint32 MfCounterTicks;

  ChannelPtr = &CanTp_Channel[tx_channel];
  TS_AtomicAssign32(MfCounterTicks, ChannelPtr->MfCounterTicks);

  if(MfCounterTicks > 0U)
  {
    /* decrease STmin counter and call notification function if 0 */
    /* No need to protect the decrement since MfCounterTicks is set upon */
    /* a TX confirmation of a CF to ensure STmin => MfCounterTicks is only */
    /* decremented here when a TX confirmation of a CF cannot happen */
    MfCounterTicks--;

    TS_AtomicAssign32(ChannelPtr->MfCounterTicks, MfCounterTicks);

    if(MfCounterTicks == 0U)
    {
      /* call callback routine */
      CanTp_STminCallback(tx_channel);
    }
  }

  CanTp_ChannelHandling(tx_channel);
}
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif
[!ENDIF!]

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
[!ENDCODE!]

