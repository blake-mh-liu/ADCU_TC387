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

#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>         /* EB AUTOSAR standard types */
#include <ComStack_Types.h>    /* AUTOSAR ComStack types */
#include <CanTp_Cfg.h> /* CanTp precompile time config */

/*==================[macros]================================================*/


#if (defined CANTP_NPDU_LENGTH_8) /* to prevent double declaration */
#error CANTP_NPDU_LENGTH_8 is already defined
#endif /* if (defined CANTP_NPDU_LENGTH_8) */
/** \brief Maximum N-PDU length of normal CAN frame in bytes */
#define CANTP_NPDU_LENGTH_8 8U

/** \brief CAN FD possible N-PDU lengths */
#if(CANTP_CANFD_ENABLED == STD_ON)

#if (defined CANTP_FD_NPDU_LENGTH_12) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_12 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_12) */
#define CANTP_FD_NPDU_LENGTH_12 12U

#if (defined CANTP_FD_NPDU_LENGTH_16) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_16 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_16) */
#define CANTP_FD_NPDU_LENGTH_16 16U

#if (defined CANTP_FD_NPDU_LENGTH_20) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_20 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_20) */
#define CANTP_FD_NPDU_LENGTH_20 20U

#if (defined CANTP_FD_NPDU_LENGTH_24) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_24 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_24) */
#define CANTP_FD_NPDU_LENGTH_24 24U

#if (defined CANTP_FD_NPDU_LENGTH_32) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_32 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_32) */
#define CANTP_FD_NPDU_LENGTH_32 32U

#if (defined CANTP_FD_NPDU_LENGTH_48) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_48 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_48) */
#define CANTP_FD_NPDU_LENGTH_48 48U

#if (defined CANTP_FD_NPDU_LENGTH_64) /* to prevent double declaration */
#error CANTP_FD_NPDU_LENGTH_64 is already defined
#endif /* if (defined CANTP_FD_NPDU_LENGTH_64) */
#define CANTP_FD_NPDU_LENGTH_64 64U

#if (defined CANTP_SF_STARTPOS_NPCI_STD) /* to prevent double declaration */
#error CANTP_SF_STARTPOS_NPCI_STD is already defined
#endif /* if (defined CANTP_SF_STARTPOS_NPCI_STD) */
#define CANTP_SF_STARTPOS_NPCI_STD 0U

#if (defined CANTP_SF_STARTPOS_NPCI_EXTMIX) /* to prevent double declaration */
#error CANTP_SF_STARTPOS_NPCI_EXTMIX is already defined
#endif /* if (defined CANTP_SF_STARTPOS_NPCI_EXTMIX) */
#define CANTP_SF_STARTPOS_NPCI_EXTMIX 1U

#if (defined SF_DL_7) /* to prevent double declaration */
#error SF_DL_7 is already defined
#endif /* if (defined SF_DL_7) */
#define SF_DL_7 7U

#if (defined SF_DL_8) /* to prevent double declaration */
#error SF_DL_8 is already defined
#endif /* if (defined SF_DL_8) */
#define SF_DL_8 8U

#if (defined SF_DL_9) /* to prevent double declaration */
#error SF_DL_9 is already defined
#endif /* if (defined SF_DL_9) */
#define SF_DL_9 9U

#if (defined SF_DL_10) /* to prevent double declaration */
#error SF_DL_10 is already defined
#endif /* if (defined SF_DL_10) */
#define SF_DL_10 10U

#if (defined SF_DL_11) /* to prevent double declaration */
#error SF_DL_11 is already defined
#endif /* if (defined SF_DL_11) */
#define SF_DL_11 11U

#if (defined SF_DL_13) /* to prevent double declaration */
#error SF_DL_13 is already defined
#endif /* if (defined SF_DL_13) */
#define SF_DL_13 13U

#if (defined SF_DL_14) /* to prevent double declaration */
#error SF_DL_14 is already defined
#endif /* if (defined SF_DL_14) */
#define SF_DL_14 14U

#if (defined SF_DL_15) /* to prevent double declaration */
#error SF_DL_15 is already defined
#endif /* if (defined SF_DL_15) */
#define SF_DL_15 15U

#if (defined SF_DL_17) /* to prevent double declaration */
#error SF_DL_17 is already defined
#endif /* if (defined SF_DL_17) */
#define SF_DL_17 17U

#if (defined SF_DL_18) /* to prevent double declaration */
#error SF_DL_18 is already defined
#endif /* if (defined SF_DL_18) */
#define SF_DL_18 18U

#if (defined SF_DL_19) /* to prevent double declaration */
#error SF_DL_19 is already defined
#endif /* if (defined SF_DL_19) */
#define SF_DL_19 19U

#if (defined SF_DL_21) /* to prevent double declaration */
#error SF_DL_21 is already defined
#endif /* if (defined SF_DL_21) */
#define SF_DL_21 21U

#if (defined SF_DL_22) /* to prevent double declaration */
#error SF_DL_22 is already defined
#endif /* if (defined SF_DL_22) */
#define SF_DL_22 22U

#if (defined SF_DL_23) /* to prevent double declaration */
#error SF_DL_23 is already defined
#endif /* if (defined SF_DL_23) */
#define SF_DL_23 23U

#if (defined SF_DL_29) /* to prevent double declaration */
#error SF_DL_29 is already defined
#endif /* if (defined SF_DL_29) */
#define SF_DL_29 29U

#if (defined SF_DL_30) /* to prevent double declaration */
#error SF_DL_30 is already defined
#endif /* if (defined SF_DL_30) */
#define SF_DL_30 30U

#if (defined SF_DL_31) /* to prevent double declaration */
#error SF_DL_31 is already defined
#endif /* if (defined SF_DL_31) */
#define SF_DL_31 31U

#if (defined SF_DL_45) /* to prevent double declaration */
#error SF_DL_45 is already defined
#endif /* if (defined SF_DL_45) */
#define SF_DL_45 45U

#if (defined SF_DL_46) /* to prevent double declaration */
#error SF_DL_46 is already defined
#endif /* if (defined SF_DL_46) */
#define SF_DL_46 46U

#if (defined SF_DL_47) /* to prevent double declaration */
#error SF_DL_47 is already defined
#endif /* if (defined SF_DL_47) */
#define SF_DL_47 47U

#if (defined SF_DL_61) /* to prevent double declaration */
#error SF_DL_61 is already defined
#endif /* if (defined SF_DL_61) */
#define SF_DL_61 61U

#if (defined SF_DL_62) /* to prevent double declaration */
#error SF_DL_62 is already defined
#endif /* if (defined SF_DL_62) */
#define SF_DL_62 62U
#endif


#if (defined CANTP_NPDU_LENGTH_MAX) /* to prevent double declaration */
#error CANTP_NPDU_LENGTH_MAX is already defined
#endif /* if (defined CANTP_NPDU_LENGTH_MAX) */

/** \brief Maximum length of N-PDU in bytes */
#if(CANTP_CANFD_ENABLED == STD_ON)
#define CANTP_NPDU_LENGTH_MAX CANTP_FD_NPDU_LENGTH_64
#else
#define CANTP_NPDU_LENGTH_MAX CANTP_NPDU_LENGTH_8
#endif


#if (defined CANTP_NPDU_LENGTH_MIN) /* to prevent double declaration */
#error CANTP_NPDU_LENGTH_MIN is already defined
#endif /* if (defined CANTP_NPDU_LENGTH_MIN) */

/** \brief Minimum length of N-PDU in bytes
 **
 ** The smallest N-PDU must at least have 1 byte header and 1 byte data (SF, CF).
 ** FC frames will have at least a header of 3 bytes.
 */
#define CANTP_NPDU_LENGTH_MIN     2U

#if (defined CANTP_STANDARD_FC_MIN_LENGTH) /* to prevent double declaration */
#error CANTP_STANDARD_FC_MIN_LENGTH is already defined
#endif /* if (defined CANTP_STANDARD_FC_MIN_LENGTH) */

/** \brief Minimum length of a flow control in bytes
 **
 ** The smallest length of a FC must be 3 bytes for standard addressing format.
 ** FC frames will have at least a header of 3 bytes.
 */
#define CANTP_STANDARD_FC_MIN_LENGTH     3U

#if (defined CANTP_EXT_MIX_FC_MIN_LENGTH) /* to prevent double declaration */
#error CANTP_EXT_MIX_FC_MIN_LENGTH is already defined
#endif /* if (defined CANTP_EXT_MIX_FC_MIN_LENGTH) */

/** \brief Minimum length of a flow control in bytes
 **
 ** The smallest length of a FC must be 4 bytes for extended and mixed addressing format.
 ** FC frames will have at least a header of 4 bytes.
 */
#define CANTP_EXT_MIX_FC_MIN_LENGTH     4U

#if (defined CANTP_EXT_MIX_FF_MIN_LENGTH) /* to prevent double declaration */
#error CANTP_EXT_MIX_FF_MIN_LENGTH is already defined
#endif /* if (defined CANTP_EXT_MIX_FF_MIN_LENGTH) */

/** \brief Minimum length of a flow control in bytes
 **
 ** The smallest length of a FF must be 3 bytes for extended and mixed addressing format.
 ** FF frames will have at least a header of 3 bytes.
 */
#define CANTP_EXT_MIX_FF_MIN_LENGTH     3U


#if (defined CANTP_CAN20_SINGLEFRAME_MIN_SDULENGTH_EXTENDED_MIXED) /* to prevent double declaration */
#error CANTP_CAN20_SINGLEFRAME_MIN_SDULENGTH_EXTENDED_MIXED is already defined
#endif /* if (defined CANTP_CAN20_SINGLEFRAME_MIN_SDULENGTH_EXTENDED_MIXED) */

/** \brief Minimum SduLength(CAN_DL) for extended/mixed CAN 2.0 SFs, in order that payload to exist
 **
 ** The smallest SduLength(CAN_DL) permitted for extended/mixed CAN 2.0 SFs
 ** An extended/mixed CAN 2.0 SF will have at least a header of 2 bytes and in order that payload to exist, SduLength(CAN_DL) needs to be at least 3 bytes (payload 1 byte)
 */
#define CANTP_CAN20_SINGLEFRAME_MIN_SDULENGTH_EXTENDED_MIXED     3U


#if (defined CANTP_NSDU_SF_LENGTH_MAX) /* to prevent double declaration */
#error CANTP_NSDU_SF_LENGTH_MAX is already defined
#endif /* if (defined CANTP_NSDU_SF_LENGTH_MAX) */

/** \brief Maximum N-SDU size of a single frame
 **
 ** CanTp needs to store received FF and SF in a temporary buffer in case no upper layer buffer is
 ** available. The maximum N-SDU size of a single frame describes the maximum size of this temporary
 ** buffer.
 */
#if(CANTP_CANFD_ENABLED == STD_ON)
#define CANTP_NSDU_SF_LENGTH_MAX 62U
#else
#define CANTP_NSDU_SF_LENGTH_MAX 7U
#endif

/** \brief Channel mode types */

#if (defined CANTP_MODE_FULL_DUPLEX) /* to prevent double declaration */
#error CANTP_MODE_FULL_DUPLEX is already defined
#endif /* if (defined CANTP_MODE_FULL_DUPLEX) */
#define CANTP_MODE_FULL_DUPLEX  0U

#if (defined CANTP_MODE_HALF_DUPLEX) /* to prevent double declaration */
#error CANTP_MODE_HALF_DUPLEX is already defined
#endif /* if (defined CANTP_MODE_HALF_DUPLEX) */
#define CANTP_MODE_HALF_DUPLEX  1U

/** \brief Type of Gpt callback type. */

#if (defined CANTP_GPT_CALLBACK) /* to prevent double declaration */
#error CANTP_GPT_CALLBACK is already defined
#endif /* if (defined CANTP_GPT_CALLBACK) */
#define CANTP_GPT_CALLBACK           0U

#if (defined CANTP_MAINFUNCTION_CALLBACK) /* to prevent double declaration */
#error CANTP_MAINFUNCTION_CALLBACK is already defined
#endif /* if (defined CANTP_MAINFUNCTION_CALLBACK) */
#define CANTP_MAINFUNCTION_CALLBACK  1U

/*==================[type definitions]======================================*/

/** \brief Type to define indication for upper layer status. */
typedef enum
{
  CANTP_ULIND_NONE,
  CANTP_ULIND_STATUS
} CanTp_ULIndicationType;

/** \brief Type to hold channel state information. */
typedef VAR(uint8, TYPEDEF) CanTp_ChStateType;


/** \brief Type of TxChannelIndex, dependent only of CanTpMaxTxChannels configured (see channelLUT)
 */
#if ((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U)
typedef VAR(uint16, TYPEDEF) CanTp_TxChannelType;
#else /* ((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U) */
typedef VAR(uint8, TYPEDEF) CanTp_TxChannelType;
#endif /* ((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U) */


/** \brief Type of Channel, dependent of CanTpMaxTxChannels and CanTpMaxRxChannels configured (see channelLUT)
 */
#if((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U)
typedef VAR(uint16, TYPEDEF) CanTp_ChType;
#else /* (CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS <= 255U)*/
typedef VAR(uint8, TYPEDEF) CanTp_ChType;
#endif /* (CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS > 255U) */


/** \brief Type of RxChannelIndex, dependent of CanTpMaxTxChannels and CanTpMaxRxChannels configured (see channelLUT)
 */
#if((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U)
typedef VAR(uint16, TYPEDEF) CanTp_RxChannelType;
#else /* ((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U) */
typedef VAR(uint8, TYPEDEF) CanTp_RxChannelType;
#endif /* ((CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS) > 255U) */

/** \brief Type of configured CanTp channels. */
#if(CANTP_NUMBER_CONFIGURED_CHANNELS > 255U)
typedef VAR(uint16, TYPEDEF) CanTp_ConfChannelType;
#else /* (CANTP_NUMBER_CONFIGURED_CHANNELS > 255U) */
typedef VAR(uint8, TYPEDEF) CanTp_ConfChannelType;
#endif /* (CANTP_NUMBER_CONFIGURED_CHANNELS > 255U) */


/** \brief Type of CanTp Channel administration. */
typedef struct
{
  /* STmin counter for MainFunction callback */
  VAR(uint32, TYPEDEF) MfCounterTicks;
  /* total message length */
  VAR(PduLengthType, TYPEDEF) TotalLength;
  /* Actual buffer size provided by upper layer.
     RX: Buffer available for receiving data.
     TX: Amount of bytes ready to transmit.
   */
  VAR(PduLengthType, TYPEDEF) ActualBufferSize;
  /* transmitted/received length */
  VAR(PduLengthType, TYPEDEF) ProcessedLength;
  /* handled N-Sdu */
  VAR(PduIdType, TYPEDEF) NSduId;
  /* Id of Tx Confirmation handled on channel release */
  VAR(PduIdType, TYPEDEF) PostTxConfNPduId;
  /* Id of Rx Indication handled on channel release */
  VAR(PduIdType, TYPEDEF) PostRxIndNSduId;
  /* timeout counter */
  VAR(uint32, TYPEDEF) Ticks;
  /* ticks to countdown before channel release */
  VAR(uint16, TYPEDEF) PostTicks;
  /* address information of ongoing Rx N-PDU */
  VAR(PduIdType, TYPEDEF) RxNAILock;
  /* Incoming RX N-PDU length while channel was locked */
  VAR(uint8, TYPEDEF) PostRxIndLength;
  /* Incoming RX N-PDU while channel was locked */
  VAR(uint8, TYPEDEF) PostRxIndData[CANTP_NPDU_LENGTH_MAX];
  /* Stores the frame type of the postponed frame. */
  VAR(uint8, TYPEDEF) PostRxIndFrameType;
  /* ind. flag for upper layer */
  VAR(uint8, TYPEDEF) ChannelLockFlag;
  /* Contains:
  * bit 0: flag indicating Rx indication handling on channel release
  * bit 1: flag indicating Tx confirmation handling on channel release
  * bit 2: flag indicating STmin timeout handling on channel release
  */
  VAR(uint8, TYPEDEF) PostFlag;
  /* channel state */
  VAR(CanTp_ChStateType, TYPEDEF) State;
  /* current Transmit block size */
  VAR(uint8, TYPEDEF) BlockSize;
  /* counter of transmitted/received frames within a block */
  VAR(uint8, TYPEDEF) ProcessedBlockFrames;
  /* counter for wait frames */
  VAR(uint8, TYPEDEF) WftCounter;
  /* sequence number for CF */
  VAR(uint8, TYPEDEF) SequenceNumber;
  /* for Tx Channels only */
  VAR(uint8, TYPEDEF) StMin;
#if(CANTP_CHANGE_TX_PARAMETER_REQ_API == STD_ON)
  /* The STmin value received from the last FC,for Tx Channels only */
  VAR(uint8, TYPEDEF) LastStMinFC;
#endif /* (CANTP_CHANGE_TX_PARAMETER_REQ_API == STD_ON) */
  /* Temporary buffer
     RX: Incoming FF and SF will be stored until processed by upper layer.
   */
  VAR(uint8, TYPEDEF) TempBuffer[CANTP_NSDU_SF_LENGTH_MAX];
  /* Temporary buffer length indicates the amount of bytes in the buffer. */
  VAR(uint8, TYPEDEF) TempLength;
  /* length of data to transmit */
  VAR(uint8, TYPEDEF) CanIfDLC;
  /* Transmit buffer for CanIf
     TX Channel: Stores the frame which will be transmitted next.
     Rx Channel: Stores the FC frame which will be transmitted next.
   */
  VAR(uint8, TYPEDEF) CanIfData[CANTP_NPDU_LENGTH_MAX];
#if(CANTP_CANFD_ENABLED == STD_ON)
  /* SduLength of the received FF */
  VAR(uint8, TYPEDEF) ReceivedSduLength;
#endif /* (CANTP_CANFD_ENABLED == STD_ON) */
  /* Contains:
  * bit 0: flag for rounding up with +1 the STmin
  * bit 1: flag indicating if channel is locked for ongoing reception for a N_AI on current channel
  * bit 2: flag indicating the last CF of ongoing multiframe reception for a N_AI on current channel
  * bit 3: flag indicating the previous sent FC was with WAIT status
  * bit 4: flag indicating the reception of a flow control
  */
  VAR(uint8, TYPEDEF) ConnectionFlags;

#if (CANTP_METADATA_CHANNELS == STD_ON)
  VAR(uint32, TYPEDEF) MetadataFc;
  VAR(PduIdType, TYPEDEF) FcPduId;
  VAR(PduIdType, TYPEDEF) MetadataLLFcPduId;
#endif

#if(CANTP_DISTRIBUTED_CHANNEL_SUPPORT == STD_ON)
  /* Partition to which the channel is linked. */
  VAR(uint8, TYPEDEF) Partition;
#endif
} CanTp_ChannelType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/



/*==================[end of file]===========================================*/

#endif /* ifndef CANTP_TYPES_H */
