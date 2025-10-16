#ifndef ETH_GENERAL_TYPES
#define ETH_GENERAL_TYPES

/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* !LINKSTO Base.ASR430.SWS_Eth_00149,1 */

/*==================[inclusions]=============================================*/

#include <ComStack_Types.h> /* basic AUTOSAR type definitions */
#include <Eth_GeneralTypes_Cfg.h>

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/* === Ethernet Driver Types === */

/** \brief Constant for value OK of Eth_ReturnType */
#define ETH_OK 0U
/** \brief Constant for value NOT_OK of Eth_ReturnType */
#define ETH_E_NOT_OK 1U
#ifndef ETH_E_NO_ACCESS
/** \brief Constant for value NO_ACCESS of Eth_ReturnType */
#define ETH_E_NO_ACCESS 2U
#endif
/** \brief Definition Eth_ReturnType */
typedef uint8 Eth_ReturnType;

/** \brief Constant for value DOWN of Eth_ModeType */
#define ETH_MODE_DOWN 0U
/** \brief Constant for value ACTIVE of Eth_ModeType */
#define ETH_MODE_ACTIVE 1U
/** \brief Constant for value ACTIVE_WITH_WAKEUP_REQUEST of Eth_ModeType */
#define ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST 2U
/** \brief Definition of Eth_ModeType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00158,1 */
typedef uint8 Eth_ModeType;

/** \brief Constant for value UNINIT of Eth_StateType */
#define ETH_STATE_UNINIT 0U
/** \brief Constant for value INIT of Eth_StateType */
#define ETH_STATE_INIT 1U
/** \brief Constant for value ACTIVE of Eth_StateType */
#define ETH_STATE_ACTIVE 2U
/** \brief Definition of Eth_StateType */
/* !LINKSTO Base.SWS_Eth_00159,1 */
typedef uint8 Eth_StateType;

/** \brief Definition of Eth_FrameType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00160,1 */
typedef uint16 Eth_FrameType;

/** \brief Definition of Eth_DataType
 *
 * \note This type is defined as 8 bit wide unsigned integer because
 *       this definition is available on all CPU types.
 */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00161,1 */
typedef uint8 Eth_DataType;

/** \brief Constant for value RECEIVED of Eth_FilterActionType */
#define ETH_RECEIVED 0U
/** \brief Constant for value NOT_RECEIVED of Eth_FilterActionType */
#define ETH_NOT_RECEIVED 1U
/** \brief Constant for value RECEIVED_MORE_DATA_AVAILABLE of Eth_FilterActionType */
#define ETH_RECEIVED_MORE_DATA_AVAILABLE 2U
/** \brief Constant for value RECEIVED_FRAMES_LOST of Eth_FilterActionType */
#define ETH_RECEIVED_FRAMES_LOST 3U
/** \brief Definition of Eth_FilterActionType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00162,1 */
typedef uint8 Eth_RxStatusType;

/** \brief Constant for value ADD_TO_FILTER of Eth_FilterActionType */
#define ETH_ADD_TO_FILTER 0U
/** \brief Constant for value ADD_TO_FILTER of Eth_FilterActionType (Compatibility with AUTOSAR 4.1.0) */
#define ADD_TO_FILTER 0U
/** \brief Constant for value REMOVE_FROM_FILTER of Eth_FilterActionType */
#define ETH_REMOVE_FROM_FILTER 1U
/** \brief Constant for value REMOVE_FROM_FILTER of Eth_FilterActionType (Compatibility with AUTOSAR 4.1.0) */
#define REMOVE_FROM_FILTER 1U
/** \brief Definition of Eth_FilterActionType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00163,1 */
typedef uint8 Eth_FilterActionType;

/** \brief Constant for value VALID of Eth_TimeStampQualType */
#define ETH_VALID 0U
/** \brief Constant for value INVALID of Eth_TimeStampQualType */
#define ETH_INVALID 1U
/** \brief Constant for value UNCERTAIN of Eth_TimeStampQualType */
#define ETH_UNCERTAIN 2U
/** \brief Definition of Eth_TimeStampQualType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00177,1 */
typedef uint8 Eth_TimeStampQualType;

/** \brief Definition of Eth_TimeStampType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00178,1 */
typedef struct
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} Eth_TimeStampType;

/** \brief Definition of Eth_TimeIntDiffType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00179,1 */
typedef struct
{
  Eth_TimeStampType diff;
  boolean sign;
} Eth_TimeIntDiffType;

/** \brief Definition of Eth_RateRatioType */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00180,1 */
typedef struct
{
  Eth_TimeIntDiffType IngressTimeStampDelta;
  Eth_TimeIntDiffType OriginTimeStampDelta;
} Eth_RateRatioType;

/** \brief Definition of Eth_MacVlanType */
/* !LINKSTO Base.SWS_Eth_91001,1 */
typedef struct
{
  uint8 MacAddr[6];
  uint16 VlanId;
  uint32 SwitchPort;
} Eth_MacVlanType;

/** \brief Definition of Eth_CounterType
 *   Statistic counter for diagnostics.
 *
 * 1.)  dropped packets due to buffer overrun
 * 2.)  dropped packets due to CRC errors
 * 3.)  number of undersize packets which were less than 64 octets long (excluding framing bits,
 *      but including FCS octets) and were otherwise will formed. (see IETF RFC 1757) 4.) number
 *      of oversize packets which are longer than 1518 octets (excluding framing bits, but
 *      including FCS octets) and were otherwise well formed. (see IETF RFC 1757)
 * 5.)  number of alignment errors, i.e. packets which are received and are not an integral number
 *      of octets in length and do not pass the CRC.
 * 6.)  SQE test error according to IETF RFC1643 dot3StatsSQETestErrors
 * 7.)  The number of inbound packets which were chosen to be discarded even though no errors had
 *      been detected to prevent their being deliverable to a higher-layer protocol. One possible
 *      reason for discarding such a packet could be to free up buffer space. (see IETF RFC 2233
 *      ifInDiscards)
 * 8.)  total number of erroneous inbound packets
 * 9.)  The number of outbound packets which were chosen to be discarded even though no errors had
 *      been detected to prevent their being transmitted. One possible reason for discarding such a
 *      packet could be to free up buffer space. (see IETF RFC 2233 ifOutDiscards)
 * 10.) total number of erroneous outbound packets
 * 11.) Single collision frames: A count of successfully transmitted frames on a particular
 *      interface for which transmission is inhibited by exactly one collision. (see IETF RFC1643
 *      dot3StatsSingleCollisionFrames)
 * 12.) Multiple collision frames: A count of successfully transmitted frames on a particular
 *      interface for which transmission is inhibited by more than one collision. (see IETF RFC1643
 *      dot3StatsMultipleCollisionFrames)
 * 13.) Number of deferred transmission: A count of frames for which the first transmission attempt
 *      on a particular interface is delayed because the medium is busy. (see IETF RFC1643
 *      dot3StatsDeferredTransmissions)
 * 14.) Number of late collisions: The number of times that a collision is detected on a particular
 *      interface later than 512 bit-times into the transmission of a packet. (see IETF RFC1643
 *      dot3StatsLateCollisions)
 * 15-18 .) hardware dependent counter values
 */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_91007,1 */
typedef struct
{
  uint32 DropPktBufOverrun;
  uint32 DropPktCrc;
  uint32 UndersizePkt;
  uint32 OversizePkt;
  uint32 AlgnmtErr;
  uint32 SqeTestErr;
  uint32 DiscInbdPkt;
  uint32 ErrInbdPkt;
  uint32 DiscOtbdPkt;
  uint32 ErrOtbdPkt;
  uint32 SnglCollPkt;
  uint32 MultCollPkt;
  uint32 DfrdPkt;
  uint32 LatCollPkt;
  uint32 HwDepCtr0;
  uint32 HwDepCtr1;
  uint32 HwDepCtr2;
  uint32 HwDepCtr3;
} Eth_CounterType;

/** \brief Definition of Eth_RxStatsType
 *   Reception statistic counter for diagnostics.
 */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_91002,1 */
typedef struct
{
  uint32 RxStatsDropEvents;
  uint32 RxStatsOctets;
  uint32 RxStatsPkts;
  uint32 RxStatsBroadcastPkts;
  uint32 RxStatsMulticastPkts;
  uint32 RxStatsCrcAlignErrors;
  uint32 RxStatsUndersizePkts;
  uint32 RxStatsOversizePkts;
  uint32 RxStatsFragments;
  uint32 RxStatsJabbers;
  uint32 RxStatsCollisions;
  uint32 RxStatsPkts64Octets;
  uint32 RxStatsPkts65to127Octets;
  uint32 RxStatsPkts128to255Octets;
  uint32 RxStatsPkts256to511Octets;
  uint32 RxStatsPkts512to1023Octets;
  uint32 RxStatsPkts1024to1518Octets;
  uint32 RxUnicastFrames;
} Eth_RxStatsType;

/** \brief Eth_RxStatsType was included in Eth_GeneralTypes.h file by Elektrobit long
 *   before it was specified in Autosar. The according RfC includes this typo and we
 *   used it as it was defined there.
 *   This define is used to prevent compile errors in modules which already used
 *   Eth_RxStatsType with this typo */
#define RxdStatsCrcAlignErrors RxStatsCrcAlignErrors

/** \brief Definition of Eth_TxStatsType
 *   Transmission statistic counter for diagnostics.
 */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_91003,1 */
typedef struct
{
  uint32 TxNumberOfOctets;
  uint32 TxNUcastPkts;
  uint32 TxUniCastPkts;
} Eth_TxStatsType;

/** \brief Definition of Eth_TxStatsType
 *   Transmission error statistic counter for diagnostics.
 */
/* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_91004,1 */
typedef struct
{
  uint32 TxDroppedNoErrorPkts;
  uint32 TxDroppedErrorPkts;
  uint32 TxDeferredTrans;
  uint32 TxSingleCollision;
  uint32 TxMultipleCollision;
  uint32 TxLateCollision;
  uint32 TxExcessiveCollison;
} Eth_TxErrorCounterValuesType;


/** \brief Retransmit info type (used for API Eth_Retransmit()) */
typedef struct {
  uint8 Priority;
  boolean TxConfirmation;
  P2VAR(uint8, TYPEDEF, ETH_APPL_DATA) PhysAddrPtr;
} Eth_RetransmitInfoType;
/** \brief Retransmit info type macro to prevent double definition in Eth
 *   (backward compatibility, to prevent double definition in Eth_Types.h) */
#define ETH_RETRANSMITINFOTYPE_DEF


/** \brief Buffer list type (used for API Eth_TransmitBufList()) */
typedef struct
{
  P2VAR(Eth_DataType, TYPEDEF, ETH_APPL_DATA) BufPtr;
  uint16 LenByte;
} Eth_BufListType;
/** \brief Buffer list type macro to prevent double definition in Eth
 *   (backward compatibility, to prevent double definition in Eth_Types.h) */
#define ETH_BUFLISTTYPE_DEF


/* === Ethernet Transceiver Types === */

/** \brief Constant for value DOWN of EthTrcv_ModeType */
#define ETHTRCV_MODE_DOWN 0U
/** \brief Constant for value ACTIVE of EthTrcv_ModeType */
#define ETHTRCV_MODE_ACTIVE 1U
/** \brief Constant for value ACTIVE_WITH_WAKEUP_REQUEST of EthTrcv_ModeType */
#define ETHTRCV_MODE_ACTIVE_WITH_WAKEUP_REQUEST 2U
/** \brief Definition of EthTrcv_ModeType */
typedef uint8 EthTrcv_ModeType;

/** \brief Constant for value DOWN of EthTrcv_LinkStateType */
#define ETHTRCV_LINK_STATE_DOWN 0U
/** \brief Constant for value ACTIVE of EthTrcv_LinkStateType */
#define ETHTRCV_LINK_STATE_ACTIVE 1U
/** \brief Definition of EthTrcv_LinkStateType */
typedef uint8 EthTrcv_LinkStateType;

/** \brief Constant for value UNINIT of EthTrcv_StateType */
#define ETHTRCV_STATE_UNINIT 0U
/** \brief Constant for value INIT of EthTrcv_StateType */
#define ETHTRCV_STATE_INIT 1U
/** \brief Constant for value ACTIVE of EthTrcv_StateType */
#define ETHTRCV_STATE_ACTIVE 2U
/** \brief Definition of EthTrcv_StateType */
typedef uint8 EthTrcv_StateType;

/** \brief Constant for value 10MBIT of EthTrcv_BaudRateType */
#define ETHTRCV_BAUD_RATE_10MBIT 0U
/** \brief Constant for value 100MBIT of EthTrcv_BaudRateType */
#define ETHTRCV_BAUD_RATE_100MBIT 1U
/** \brief Constant for value 1000MBIT of EthTrcv_BaudRateType */
#define ETHTRCV_BAUD_RATE_1000MBIT 2U
/** \brief Definition of EthTrcv_BaudRateType */
typedef uint8 EthTrcv_BaudRateType;

/** \brief Constant for value HALF of EthTrcv_DuplexModeType */
#define ETHTRCV_DUPLEX_MODE_HALF 0U
/** \brief Constant for value FULL of EthTrcv_DuplexModeType */
#define ETHTRCV_DUPLEX_MODE_FULL 1U
/** \brief Definition of EthTrcv_DuplexModeType */
typedef uint8 EthTrcv_DuplexModeType;

/** \brief Constant for value transceiver wake up mode disabled of EthTrcv_ WakeupModeType */
#define ETHTRCV_WUM_DISABLE 0U
/** \brief Constant for value Transceiver wake up mode enabled of EthTrcv_ WakeupModeType */
#define ETHTRCV_WUM_ENABLE  1U
/** \brief Constant for value transceiver wake up reason cleared of EthTrcv_ WakeupModeType */
#define ETHTRCV_WUM_CLEAR   2U
/** \brief Definition of EthTrcv_DuplexModeType */
typedef uint8 EthTrcv_WakeupModeType;

/** \brief Constant for value transceiver wake up reason - no wake up reason detected */
#define ETHTRCV_WUR_NONE 0U
/** \brief Constant for value Transceiver wake up reason - no distinct reason supported by hardware */
#define ETHTRCV_WUR_GENERAL 1U
/** \brief Constant for value transceiver wake up reason - Bus wake up detected */
#define ETHTRCV_WUR_BUS 2U
/** \brief Constant for value transceiver wake up reason - Internal wake up detected */
#define ETHTRCV_WUR_INTERNAL 3U
/** \brief Constant for value Transceiver wake up reason - Reset wake up detected */
#define ETHTRCV_WUR_RESET 4U
/** \brief Constant for value transceiver wake up reason - Power on wake up detected */
#define ETHTRCV_WUR_POWER_ON 5U
/** \brief Constant for value transceiver wake up reason - Pin wake up detected */
#define ETHTRCV_WUR_PIN 6U
/** \brief Constant for value Transceiver wake up reason - System error wake up detected */
#define ETHTRCV_WUR_SYSERR 7U
/** \brief Definition of EthTrcv_WakeupReasonType */
typedef uint8 EthTrcv_WakeupReasonType;

/** \brief Constant for value NORMAL OPERATION of EthTrcv_PhyLoopbackModeType */
#define ETHTRCV_PHYLOOPBACK_NONE 0U
/** \brief Constant for value INTERNAL LOOPBACK of EthTrcv_PhyLoopbackModeType */
#define ETHTRCV_PHYLOOPBACK_INTERNAL 1U
/** \brief Constant for value EXTERNAL LOOPBACK of EthTrcv_PhyLoopbackModeType */
#define ETHTRCV_PHYLOOPBACK_EXTERNAL 2U
/** \brief Constant for value REMOTE LOOPBACK of EthTrcv_PhyLoopbackModeType */
#define ETHTRCV_PHYLOOPBACK_REMOTE 3U
/** \brief Definition of EthTrcv_PhyLoopbackModeType */
typedef uint8 EthTrcv_PhyLoopbackModeType;

/** \brief Constant for value NORMAL OPERATION of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_NONE 0U
/** \brief Constant for value TEST TRANSMITTER DROOP of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_1 1U
/** \brief Constant for value TEST MASTER TIMING JITTER of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_2 2U
/** \brief Constant for value TEST SLAVE TIMING JITTER of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_3 3U
/** \brief Constant for value TEST TRANSMITTER DISTORTION of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_4 4U
/** \brief Constant for value TEST POWER SPECTRAL DENSITY (PSD) MASK of EthTrcv_PhyTestModeType */
#define ETHTRCV_PHYTESTMODE_5 5U
/** \brief Definition of EthTrcv_PhyTestModeType */
typedef uint8 EthTrcv_PhyTestModeType;

/** \brief Constant for value NORMAL OPERATION of EthTrcv_PhyTxModeType */
#define ETHTRCV_PHYTXMODE_NORMAL 0U
/** \brief Constant for value TRANSMITTER DISABLED of EthTrcv_PhyTxModeType */
#define ETHTRCV_PHYTXMODE_TX_OFF 1U
/** \brief Constant for value SCRAMBLER DISABLED of EthTrcv_PhyTxModeType */
#define ETHTRCV_PHYTXMODE_SCRAMBLER_OFF 2U
/** \brief Definition of EthTrcv_PhyTxModeType */
typedef uint8 EthTrcv_PhyTxModeType;

/** \brief Constant for value CABLE DIAGNOSTIC OK of EthTrcv_CableDiagResultType */
#define ETHTRCV_CABLEDIAG_OK 0U
/** \brief Constant for value CABLE DIAGNOSTIC FAILED of EthTrcv_CableDiagResultType */
#define ETHTRCV_CABLEDIAG_ERROR 1U
/** \brief Constant for value SHORT CIRCUIT DETECTED of EthTrcv_CableDiagResultType */
#define ETHTRCV_CABLEDIAG_SHORT 2U
/** \brief Constant for value OPEN CIRCUIT DETECTED of EthTrcv_CableDiagResultType */
#define ETHTRCV_CABLEDIAG_OPEN 3U
/** \brief Constant for value CABLE DIAGNOSTIC PENDING of EthTrcv_CableDiagResultType */
/* This element is introduced with RFC 77675 */
#define ETHTRCV_CABLEDIAG_PENDING 0x04U
/** \brief Constant for value CABLE DIAGNOSTIC WRONG POLARITY of EthTrcv_CableDiagResultType */
/* This element is introduced with RFC 77675 */
#define ETHTRCV_CABLEDIAG_WRONG_POLARITY 0x05U

/** \brief Definition of EthTrcv_CableDiagResultType */
typedef uint8 EthTrcv_CableDiagResultType;

/* === Ethernet Switch Types === */

/** \brief Constant for value UNINIT of EthSwt_StateType */
#define ETHSWT_STATE_UNINIT 0U
/** \brief Constant for value INIT of EthSwt_StateType */
#define ETHSWT_STATE_INIT   1U
/** \brief Constant for value ACTIVE of EthSwt_StateType */
#define ETHSWT_STATE_ACTIVE 2U
/** \brief Definition of EthSwt_StateType */
typedef uint8 EthSwt_StateType;

/** \brief Constant for value HWDISABLED of EthSwt_MacLearningType */
#define ETHSWT_MACLEARNING_HWDISABLED 0U
/** \brief Constant for value HWENABLED of EthSwt_MacLearningType */
#define ETHSWT_MACLEARNING_HWENABLED  1U
/** \brief Constant for value SWENABLED of EthSwt_MacLearningType */
#define ETHSWT_MACLEARNING_SWENABLED  2U
/** \brief Definition of EthSwt_MacLearningType */
typedef uint8 EthSwt_MacLearningType;

/** \brief Definition of EthSwt_MgmtInfoType
 *   Type for holding the management information received/transmitted on Switches (ports).
 */
typedef struct
{
  uint8 SwitchIdx;
  uint8 SwitchPortIdx;
} EthSwt_MgmtInfoType;

/** \brief Definition of EthSwt_PortMirrorCfgType
 *   Type for holding the information of port mirror configuration.
 */
typedef struct
{
  /** \brief specifies the type selection
   *         0x00== free configuration,
   *         0x01 - 0x0FF == set number
  */
  uint8 SetSelection;
  /** \brief specifies whether direction is Ingress or Egress
   *         0 : Ingress
   *         1 : Egress
  */
  uint8 TrafficDirection;
  /** \brief Specifies the source MAC address that should be mirrored */
  uint8  srcMacAddrFilter[6U];
  /** \brief Specifies the destination MAC address that should be mirrored */
  uint8  dstMacAddrFilter[6U];
  /** \brief VLAN address [0..65535] that should be mirrored */
  uint16  VlanIdFilter;
  /** \brief Divider if only a subset of received frames should be mirrored.*/
  uint8 MirroringPacketDivider;
  /** \brief specifies the mode how the mirrored traffic should be tagged .
   *         0x00 == No VLAN retagging;
   *         0x01 == VLAN retagging;
   *         0x03 == VLAN Double tagging
   * */
  uint8 MirroringMode;
  /** \brief specifies a time constant in seconds after the mirroring
   *         configuration should be resumed.*/
  uint16 MirroringTimeout;
} EthSwt_PortMirrorCfgType;

/** \brief Constant for value port mirroring disabled of EthSwt_PortMirrorStateType */
#define PORT_MIRROR_DISABLED 0U
/** \brief Constant for value port mirroring enabled of EthSwt_PortMirrorStateType */
#define PORT_MIRROR_ENABLED  1U
/** \brief Definition of EthSwt_PortMirrorStateType */
typedef uint8 EthSwt_PortMirrorStateType;

/* === Ethernet Interface Types === */

/** \brief Signal quality structure type */
typedef struct
{
  /* the highest signal quality of a link since last clear */
  uint32 HighestSignalQuality;
  /* the lowest signal quality of a link since last clear */
  uint32 LowestSignalQuality;
  /* the actual signal quality */
  uint32 ActualSignalQuality;
} EthIf_SignalQualityResultType;

/** \brief Data Type that represents the Ethernet interface switch port group index.
 * The index is zero based and unique for every configured switch port group. */
typedef uint8 EthIf_SwitchPortGroupIdxType;

/* !LINKSTO Base.EB_Ref.SWS_EthIf_91010.AvailableVia,1 */
/** \brief Constant for the value of Measurement index for dropped datagrams caused by invalid
 *         CrtlIdx/VLAN */
#if (defined ETHIF_MEAS_DROP_CRTLIDX)
#error ETHIF_MEAS_DROP_CRTLIDX is already defined
#endif
#define ETHIF_MEAS_DROP_CRTLIDX 1U

/** \brief Constant for the value of Measurement index for dropped datagrams caused by unknown
 *         Ethertype */
#if (defined ETHIF_MEAS_DROP_UNKNOWN_ETHERTYPE)
#error ETHIF_MEAS_DROP_UNKNOWN_ETHERTYPE is already defined
#endif
#define ETHIF_MEAS_DROP_UNKNOWN_ETHERTYPE   0x80U

/** \brief Constant for the value of Measurement index for dropped datagrams caused by double
 *         VLAN tag */
#if (defined ETHIF_MEAS_DROP_DOUBLE_VLANTAG)
#error ETHIF_MEAS_DROP_DOUBLE_VLANTAG is already defined
#endif
#define ETHIF_MEAS_DROP_DOUBLE_VLANTAG      0x81U

/** \brief Constant for the value of Measurement index for datagrams dropped because local MAC was
 *         same as source MAC in an incoming frame */
#if (defined ETHIF_MEAS_DROP_ETH_MAC_COLLISION)
#error ETHIF_MEAS_DROP_ETH_MAC_COLLISION is already defined
#endif
#define ETHIF_MEAS_DROP_ETH_MAC_COLLISION   0x82U

/* !LINKSTO Base.EB_Ref.SWS_EthIf_91010.AvailableVia,1 */
/** \brief Constant for the value of Measurement index that represents all measurement indexes */
#if (defined ETHIF_MEAS_ALL)
#error ETHIF_MEAS_ALL is already defined
#endif
#define ETHIF_MEAS_ALL 0xFFU

/* !LINKSTO Base.EB_Ref.SWS_EthIf_91010.AvailableVia,1 */
/** \brief Definition of EthIf_MeasurementIdxType - index to select specific measurement data */
typedef uint8 EthIf_MeasurementIdxType;

/* === SoAd Interface Types for MeasurementIdx === */
/* !LINKSTO Base.EB_Ref.SWS_SoAd_91010.AvailableVia,1 */
/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         destination TCP-Port */
#if (defined SOAD_MEAS_DROP_TCP)
#error SOAD_MEAS_DROP_TCP is already defined
#endif
#define SOAD_MEAS_DROP_TCP 1U

/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         destination UDP-Port */
#if (defined SOAD_MEAS_DROP_UDP)
#error SOAD_MEAS_DROP_UDP is already defined
#endif
#define SOAD_MEAS_DROP_UDP 2U

/** \brief Constant for the value of Measurement index that represents all measurement indexes */
#if (defined SOAD_MEAS_ALL)
#error SOAD_MEAS_ALL is already defined
#endif
#define SOAD_MEAS_ALL 0xFFU

/* !LINKSTO Base.EB_Ref.SWS_SoAd_91010.AvailableVia,1 */
/** \brief Definition of SoAd_MeasurementIdxType - index to select specific measurement data */
typedef uint8 SoAd_MeasurementIdxType;

/* === TcpIp Interface Types for MeasurementIdx === */
/* !LINKSTO Base.EB_Ref.SWS_TcpIp_91010.AvailableVia,1 */
/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         destination TCP-Port */
#if (defined TCPIP_MEAS_DROP_TCP)
#error TCPIP_MEAS_DROP_TCP is already defined
#endif
#define TCPIP_MEAS_DROP_TCP 1U

/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         destination UDP-Port */
#if (defined TCPIP_MEAS_DROP_UDP)
#error TCPIP_MEAS_DROP_UDP is already defined
#endif
#define TCPIP_MEAS_DROP_UDP 2U

/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         IPv4 address */
#if (defined TCPIP_MEAS_DROP_IPV4)
#error TCPIP_MEAS_DROP_IPV4 is already defined
#endif
#define TCPIP_MEAS_DROP_IPV4 3U

/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         IPv6 address */
#if (defined TCPIP_MEAS_DROP_IPV6)
#error TCPIP_MEAS_DROP_IPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_IPV6 4U

/** \brief Constant for the value of Measurement index for dropped PDUs caused by invalid
 *         ICMPv6 packets */
#if (defined TCPIP_MEAS_DROP_ICMPV6)
#error TCPIP_MEAS_DROP_ICMPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_ICMPV6 0x80U

/** \brief Constant for the value of Measurement index for replaced ARP entries */
#if (defined TCPIP_MEAS_REPLACED_ARP)
#error TCPIP_MEAS_REPLACED_ARP is already defined
#endif
#define TCPIP_MEAS_REPLACED_ARP 0x81U

/** \brief Constant for the value of Measurement index for dropped ARP entry add requests */
#if (defined TCPIP_MEAS_DROP_ARP)
#error TCPIP_MEAS_DROP_ARP is already defined
#endif
#define TCPIP_MEAS_DROP_ARP 0x82U

/** \brief Constant for the value of Measurement index for accepted Ip datagrams,
           allowed by a matched security policy */
#if (defined TCPIP_MEAS_PASS_VALID_POLICY)
#error TCPIP_MEAS_PASS_VALID_POLICY is already defined
#endif
#define TCPIP_MEAS_PASS_VALID_POLICY 0x83U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies addresses */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_ADDRESSES)
#error TCPIP_MEAS_DROP_INVALID_POLICY_ADDRESSES is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_ADDRESSES 0x84U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid codes for ICMPv6 packets */
#if (defined TCPIP_MEAS_DROP_INVALID_CODE_ICMPV6)
#error TCPIP_MEAS_DROP_INVALID_CODE_ICMPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_CODE_ICMPV6 0x85U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid packet format for IpV6 packets */
#if (defined TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_IPV6)
#error TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_IPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_IPV6 0x86U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid extension header for IpV6 packets */
#if (defined TCPIP_MEAS_DROP_INVALID_EXTENSION_HEADER_IPV6)
#error TCPIP_MEAS_DROP_INVALID_EXTENSION_HEADER_IPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_EXTENSION_HEADER_IPV6 0x87U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid packet format for UDP packets */
#if (defined TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_UDP)
#error TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_UDP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_UDP 0x88U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid checksum for UDP packets */
#if (defined TCPIP_MEAS_DROP_INVALID_CHECKSUM_UDP)
#error TCPIP_MEAS_DROP_INVALID_CHECKSUM_UDP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_CHECKSUM_UDP 0x89U

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid packet format for TCP packets */
#if (defined TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_TCP)
#error TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_TCP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_PACKET_FORMAT_TCP 0x8AU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by invalid checksum for TCP packets */
#if (defined TCPIP_MEAS_DROP_INVALID_CHECKSUM_TCP)
#error TCPIP_MEAS_DROP_INVALID_CHECKSUM_TCP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_CHECKSUM_TCP 0x8BU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies for UDP packet */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_UDP)
#error TCPIP_MEAS_DROP_INVALID_POLICY_UDP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_UDP 0x8CU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies for TCP packet */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_TCP)
#error TCPIP_MEAS_DROP_INVALID_POLICY_TCP is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_TCP 0x8DU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies for ICMPV4 packet */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV4)
#error TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV4 is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV4 0x8EU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies for ICMPV6 packet */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV6)
#error TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV6 is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_ICMPV6 0x8FU

/** \brief Constant for the value of Measurement index for dropped Ip datagrams,
           caused by unmatched security policies for unspecified protocol layer */
#if (defined TCPIP_MEAS_DROP_INVALID_POLICY_UNSPECIFIED_PROTOCOL_LAYER)
#error TCPIP_MEAS_DROP_INVALID_POLICY_UNSPECIFIED_PROTOCOL_LAYER is already defined
#endif
#define TCPIP_MEAS_DROP_INVALID_POLICY_UNSPECIFIED_PROTOCOL_LAYER 0x90U

/** \brief Constant for the value of Measurement index that represents all measurement indexes */
#if (defined TCPIP_MEAS_ALL)
#error TCPIP_MEAS_ALL is already defined
#endif
#define TCPIP_MEAS_ALL 0xFFU

/* !LINKSTO Base.EB_Ref.SWS_TcpIp_91010.AvailableVia,1 */
/** \brief Definition of TcpIp_MeasurementIdxType - index to select specific measurement data */
typedef uint8 TcpIp_MeasurementIdxType;

/*==================[end of file]============================================*/
#endif /* ETH_GENERAL_TYPES */
