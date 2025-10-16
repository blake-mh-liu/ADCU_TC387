/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Eth_17_GEthMacV2.h                                         **
**                                                                            **
**  VERSION      : 5.0.0                                                      **
**                                                                            **
**  DATE         : 2023-05-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Eth Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) :Specification of Ethernet Driver, AUTOSAR Release 4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9A1A9210-1D23-4417-8786-B7D12DD7EF6E}]
[/cover] */
#ifndef ETH_17_GETHMACV2_H
#define ETH_17_GETHMACV2_H

/*******************************************************************************
**                              Includes                                      **
*******************************************************************************/
/* [cover parentID={6DFF13F1-1E81-45ba-A1BA-AB4165C9633B}]
[/cover] */
/* Inclusion of Platform_Types.h and Compiler.h */
/* [cover parentID={6D6DF488-3E3D-49db-BFD5-3B10C9A719D9}]
[/cover] */
/* [cover parentID={EA392A13-FCA8-42f7-B9BC-0967C60FE9AB}]
[/cover] */
#include "Eth_17_GEthMacV2_Types.h"

/* Mcal_Wrapper header file */
#include "Mcal_Wrapper.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Service IDs which are used while reporting development errors. */
#define ETH_17_GETHMACV2_SID_INIT                   ((uint8)0x01)
#define ETH_17_GETHMACV2_SID_SETCONTROLLERMODE      ((uint8)0x03)
#define ETH_17_GETHMACV2_SID_GETCONTROLLERMODE      ((uint8)0x04)
#define ETH_17_GETHMACV2_SID_WRITEMII               ((uint8)0x05)
#define ETH_17_GETHMACV2_SID_READMII                ((uint8)0x06)
#define ETH_17_GETHMACV2_SID_GETPHYADDRESS          ((uint8)0x08)
#define ETH_17_GETHMACV2_SID_PROVIDETXBUFFER        ((uint8)0x09)
#define ETH_17_GETHMACV2_SID_TRANSMIT               ((uint8)0x0A)
#define ETH_17_GETHMACV2_SID_RECEIVE                ((uint8)0x0B)
#define ETH_17_GETHMACV2_SID_TXCONFIRMATION         ((uint8)0x0C)
#define ETH_17_GETHMACV2_SID_GETVERSIONINFO         ((uint8)0x0D)
#define ETH_17_GETHMACV2_SID_RXHANDLER              ((uint8)0x10)
#define ETH_17_GETHMACV2_SID_TXHANDLER              ((uint8)0x11)
#define ETH_17_GETHMACV2_SID_UPDATEFILTER           ((uint8)0x12)
#define ETH_17_GETHMACV2_SID_SETPHYSADDRESS         ((uint8)0x13)
#define ETH_17_GETHMACV2_SID_GETCOUNTERVALUES       ((uint8)0x14)
#define ETH_17_GETHMACV2_SID_GETRXSTATS             ((uint8)0x15)
#define ETH_17_GETHMACV2_SID_GETCURRENTTIME         ((uint8)0x16)
#define ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP  ((uint8)0x17)
#define ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP     ((uint8)0x18)
#define ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP    ((uint8)0x19)
#define ETH_17_GETHMACV2_SID_SETCORRECTIONTIME      ((uint8)0x1A)
#define ETH_17_GETHMACV2_SID_SETGLOBALTIME          ((uint8)0x1B)
#define ETH_17_GETHMACV2_SID_GETTXSTATS             ((uint8)0x1C)
#define ETH_17_GETHMACV2_SID_GETTXERRCNTRVAL        ((uint8)0x1D)


/* Published parameters */
/* [cover parentID={3DDE6C59-919F-4734-85A7-785C9163F45B}]
[/cover] */
/* ETH Vendor ID - Vendor ID of the dedicated implementation of this
   module according to the AUTOSAR vendor list */
#define ETH_17_GETHMACV2_VENDOR_ID       ((uint16)17)
/*ETH Module ID - Module ID of this module from Module List */
#define ETH_17_GETHMACV2_MODULE_ID       ((uint16)88)
/* ETH Instance ID */
#define ETH_17_GETHMACV2_INSTANCE_ID     ((uint8)ETH_17_GETHMACV2_INDEX)

/* Error code for Development errors */
#define ETH_17_GETHMACV2_E_DET_NO_ERR           ((uint8)0x00)
/* [cover parentID={2E45B5CC-1FCE-4513-A390-35C3EB7CA5D9}][/cover] */
#define ETH_17_GETHMACV2_E_INV_CTRL_IDX         ((uint8)0x01)

/* [cover parentID={222BC33D-4C86-4dc2-961B-C27F5B67EB8E}][/cover] */
#define ETH_17_GETHMACV2_E_UNINIT               ((uint8)0x02)

/* [cover parentID={5F0300EE-9D57-42fd-90C1-323B57047509}][/cover] */
#define ETH_17_GETHMACV2_E_PARAM_POINTER        ((uint8)0x03)

/* [cover parentID={8B48D7DF-1252-4abf-9EAB-CC2A2B9F856C}][/cover] */
#define ETH_17_GETHMACV2_E_INV_PARAM            ((uint8)0x04)

/* [cover parentID={94056AEB-BC5A-43cc-B7DE-CB4847B7EC7A}][/cover] */
#define ETH_17_GETHMACV2_E_INV_MODE             ((uint8)0x05)

/* [cover parentID={59A9A5FA-051E-49d1-8F22-22EB372B048D}][/cover] */
#define ETH_17_GETHMACV2_E_INIT_FAILED          ((uint8)0x20)

/* [cover parentID={FC3957EB-2354-48d0-8E70-5C0AFEA88807}][/cover] */
#define ETH_17_GETHMACV2_E_CORE_NOT_CONFIGURED  ((uint8)0x64)

/* Production error report Disable/Enable. */
#define ETH_17_GETHMACV2_DISABLE_DEM_REPORT (0U)
#define ETH_17_GETHMACV2_ENABLE_DEM_REPORT  (1U)

/* Enable/Disable Macro. */
#define ETH_17_GETHMACV2_ENABLE             (1U)
#define ETH_17_GETHMACV2_DISABLE            (0U)

#define ETH_17_GETHMACV2_MCAL_SUPERVISOR    (0U)
#define ETH_17_GETHMACV2_MCAL_USER1         (1U)

/* Macros for MAC Configuration Register - MAC_CONFIGURATION*/
#define ETH_17_GETHMACV2_MAC_RX               (0x00000001U)
#define ETH_17_GETHMACV2_RXENABLE             (0x00000001U)
#define ETH_17_GETHMACV2_RXDISABLE            (0x00000000U)
#define ETH_17_GETHMACV2_MAC_TX               (0x00000002U)
#define ETH_17_GETHMACV2_TXENABLE             (0x00000002U)
#define ETH_17_GETHMACV2_TXDISABLE            (0x00000000U)
#define ETH_17_GETHMACV2_MACPREAMBLENGTH7     (0x00000000U)
#define ETH_17_GETHMACV2_DEFERRALCHECKENABLE  (0x00000010U)
#define ETH_17_GETHMACV2_DEFERRALCHECKDISABLE (0x00000000U)
#define ETH_17_GETHMACV2_BACKOFFLIMIT         (0x00000060U)
#define ETH_17_GETHMACV2_BACKOFFLIMIT3        (0x00000060U)
#define ETH_17_GETHMACV2_BACKOFFLIMIT2        (0x00000040U)
#define ETH_17_GETHMACV2_BACKOFFLIMIT1        (0x00000020U)
#define ETH_17_GETHMACV2_BACKOFFLIMIT0        (0x00000000U)
#define ETH_17_GETHMACV2_RETRYDISABLE         (0x00000100U)
#define ETH_17_GETHMACV2_RETRYENABLE          (0x00000000U)
#define ETH_17_GETHMACV2_DISABLERXOWN         (0x00000400U)
#define ETH_17_GETHMACV2_ENABLERXOWN          (0x00000000U)
#define ETH_17_GETHMACV2_LOOPBACKON           (0x00001000U)
#define ETH_17_GETHMACV2_LOOPBACKOFF          (0x00000000U)
#define ETH_17_GETHMACV2_FULLDUPLEX           (0x00002000U)
#define ETH_17_GETHMACV2_HALFDUPLEX           (0x00000000U)
#define ETH_17_GETHMACV2_JUMBOFRAMEENABLE     (0x00010000U)
#define ETH_17_GETHMACV2_JUMBOFRAMEDISABLE    (0x00000000U)
#define ETH_17_GETHMACV2_JABBERDISABLE        (0x00020000U)
#define ETH_17_GETHMACV2_JABBERENABLE         (0x00000000U)
#define ETH_17_GETHMACV2_PACKETBURSTENABLE    (0x00040000U)
#define ETH_17_GETHMACV2_PACKETBURSTDISABLE   (0x00000000U)
#define ETH_17_GETHMACV2_WATCHDOGDISABLE      (0x00080000U)
#define ETH_17_GETHMACV2_WATCHDOGENABLE       (0x00000000U)
#define ETH_17_GETHMACV2_PADCRCSTRIPENABLE    (0x00100000U)
#define ETH_17_GETHMACV2_PADCRCSTRIPDISABLE   (0x00000000U)
#define ETH_17_GETHMACV2_CRCSTRTPKTENABLE     (0x00200000U)
#define ETH_17_GETHMACV2_CRCSTRTPKTDISABLE    (0x00000000U)
#define ETH_17_GETHMACV2_INTERPACKGAP96BIT    (0x00000000U)
#define ETH_17_GETHMACV2_INTERPACKGAP88BIT    (0x01000000U)
#define ETH_17_GETHMACV2_INTERPACKGAP80BIT    (0x02000000U)
#define ETH_17_GETHMACV2_INTERPACKGAP40BIT    (0x07000000U)

#define ETH_17_GETHMACV2_PROMISC_ON           (0x00000001U)
#define ETH_17_GETHMACV2_PROMISC_OFF          (0x00000000U)
#define ETH_17_GETHMACV2_MULTICASTENABLE      (0x00000010U)
#define ETH_17_GETHMACV2_MULTICASTDISABLE     (0x00000000U)
#define ETH_17_GETHMACV2_BROADCASTDISABLE     (0x00000020U)
#define ETH_17_GETHMACV2_BROADCASTENABLE      (0x00000000U)
#define ETH_17_GETHMACV2_PASSCONTROL          (0x000000C0U)
#define ETH_17_GETHMACV2_PASSCONTROL0         (0x00000000U)
#define ETH_17_GETHMACV2_PASSCONTROL1         (0x00000040U)
#define ETH_17_GETHMACV2_PASSCONTROL2         (0x00000080U)
#define ETH_17_GETHMACV2_PASSCONTROL3         (0x000000C0U)
#define ETH_17_GETHMACV2_RECEIVEALLOFF        (0x00000000U)
#define ETH_17_GETHMACV2_RECEIVEALLON         (0x80000000U)

/* Macros for MAC MDIO Address Register - MAC_MDIO_ADDRESS*/
#define ETH_17_GETHMACV2_GMIIBUSYSET          (0x00000001U)
#define ETH_17_GETHMACV2_GMIIBUSYCLEAR        (0x00000000U)
#define ETH_17_GETHMACV2_C45EENABLE           (0x00000002U)
#define ETH_17_GETHMACV2_C45EDISABLE          (0x00000000U)
#define ETH_17_GETHMACV2_WRITECOMMAND         (0x00000004U)
#define ETH_17_GETHMACV2_POSTREADINCRC45      (0x00000008U)
#define ETH_17_GETHMACV2_READCOMMAND          (0x0000000CU)

/* Macros for MTL Operation Mode Register - MTL_OPERATION_MODE*/
#define ETH_17_GETHMACV2_MTL_DTXTS_DISABLE    (0x00000000U)
#define ETH_17_GETHMACV2_MTL_DTXTS_ENABLE     (0x00000002U)
#define ETH_17_GETHMACV2_MTL_RAA_SP           (0x00000000U)
#define ETH_17_GETHMACV2_MTL_RAA_WSP          (0x00000004U)
#define ETH_17_GETHMACV2_MTL_SCHALG_WRR       (0x00000000U)
#define ETH_17_GETHMACV2_MTL_SCHALG_SP        (0x00000060U)

/* Macros, MTL Queue0 Transmit Operation Mode Register-MTL_TXQ0_OPERATION_MODE*/
#define ETH_17_GETHMACV2_MTL_FTQ              (0x00000001U)
#define ETH_17_GETHMACV2_MTL_TSF              (0x00000002U)
#define ETH_17_GETHMACV2_MTL_TXQEN            (0x00000008U)
#define ETH_17_GETHMACV2_MTL_TXQS_256BYTES    (0x00000000U)
#define ETH_17_GETHMACV2_MTL_TXQS_2048BYTES   (0x00070000U)
#define ETH_17_GETHMACV2_MTL_TXQS_4096BYTES   (0x000F0000U)

/* Macros, MTL Queue 0 Receive Operation Mode Register-MTL_RXQ0_OPERATION_MODE*/
#define ETH_17_GETHMACV2_MTL_FUP              (0x00000008U)
#define ETH_17_GETHMACV2_MTL_FEP              (0x00000010U)
#define ETH_17_GETHMACV2_MTL_RSF              (0x00000020U)
#define ETH_17_GETHMACV2_MTL_DIS_TCP_EF       (0x00000040U)
#define ETH_17_GETHMACV2_MTL_RQS_256BYTES     (0x00000000U)
#define ETH_17_GETHMACV2_MTL_RQS_2048BYTES    (0x00700000U)
#define ETH_17_GETHMACV2_MTL_RQS_4096BYTES    (0x00F00000U)
#define ETH_17_GETHMACV2_MTL_RQS_8192BYTES    (0x01F00000U)

/* Macros for DMA Bus Mode Register - DMA_MODE*/
#define ETH_17_GETHMACV2_DMA_SWR              (0x00000001U)
#define ETH_17_GETHMACV2_DMA_TX_RX_ARB_FP     (0x00000002U)
#define ETH_17_GETHMACV2_DMA_TAA_FP           (0x00000000U)
#define ETH_17_GETHMACV2_DMA_TAA_WSP          (0x00000004U)
#define ETH_17_GETHMACV2_DMA_TAA_WRB          (0x00000008U)
#define ETH_17_GETHMACV2_DMA_TXPR_DISABLE     (0x00000000U)
#define ETH_17_GETHMACV2_DMA_TXPR_ENABLE      (0x00000800U)
#define ETH_17_GETHMACV2_DMA_INTM_ZERO        (0x00000000U)
#define ETH_17_GETHMACV2_DMA_INTM_ONE         (0x00010000U)
#define ETH_17_GETHMACV2_DMA_INTM_TWO         (0x00020000U)
#define ETH_17_GETHMACV2_DMA_INTM_THREE       (0x00030000U)

/* Macros for DMA System Bus Mode Register - DMA_SYSBUS_MODE*/
#define ETH_17_GETHMACV2_DMA_FB_DISABLE       (0x00000000U)
#define ETH_17_GETHMACV2_DMA_FB_ENABLE        (0x00000001U)
#define ETH_17_GETHMACV2_DMA_AAL_DISABLE      (0x00000000U)
#define ETH_17_GETHMACV2_DMA_AAL_ENABLE       (0x00001000U)
#define ETH_17_GETHMACV2_DMA_MB_DISABLE       (0x00000000U)
#define ETH_17_GETHMACV2_DMA_MB_ENABLE        (0x00004000U)

/* Macros for DMA Channel i Transmit Control Register - DMA_CHi_TX_CONTROL*/
#define ETH_17_GETHMACV2_DMA_TX_CH_STOP       (0x00000000U)
#define ETH_17_GETHMACV2_DMA_TX_CH_START      (0x00000001U)

/* Macros for DMA Channel i Receive Control Register - DMA_CHi_RX_CONTROL*/
#define ETH_17_GETHMACV2_DMA_RX_CH_STOP       (0x00000000U)
#define ETH_17_GETHMACV2_DMA_RX_CH_START      (0x00000001U)

/* Macros for DMA Channel i Status Register - DMA_CHi_STATUS*/
#define ETH_17_GETHMACV2_DMA_CH_STAT_TI_RESET           (0x00000001U)
#define ETH_17_GETHMACV2_DMA_CH_STAT_RI_RESET           (0x00000040U)
#define ETH_17_GETHMACV2_DMA_CH_STAT_RBU_ERI_AIE_RESET  (0x00004880U)
#define ETH_17_GETHMACV2_DMA_CH_STAT_NIS_RESET          (0x00008000U)
#define ETH_17_GETHMACV2_DMA_CH_STAT_CLR_ALL            (0x0000FFC7U)

/* Macros for DMA Transmit Descriptor */
#define ETH_17_GETHMACV2_DMA_TX_DESC_TS_ENABLE    (0x40000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_TTSS_SET     (0x00020000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_CTXT_SET     (0x40000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_FD_SET       (0x20000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_LD_SET       (0x10000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_CPC_ENABLE   (0x00000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_CIC_PSDO     (0x00030000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_PAC_LEN_MASK (0x00007FFFU)
#define ETH_17_GETHMACV2_DMA_TX_DESC_IOC_ENABLE   (0x80000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_OWN_SET      (0x80000000U)
#define ETH_17_GETHMACV2_DMA_TX_DESC_ERROR_MASK   (0x00808000U)

/* Macros for DMA Receive Descriptor */
#define ETH_17_GETHMACV2_DMA_RX_DESC_IOC_ENABLE   (0x40000000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_BF1_VALID    (0x01000000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_TSA_SET      (0x00004000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_CTXT_SET     (0x40000000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_LD_SET       (0x10000000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_PL_MASK      (0x00007FFFU)
#define ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET      (0x80000000U)
#define ETH_17_GETHMACV2_DMA_RX_DESC_FD_LD_SET    (0x30000000U)

/* Macros used for list of Ethernet statistics items to be returned from
Eth_GetEtherStats() APIs */
#define ETH_17_GETHMACV2_STAT_DROP_EVENTS           (0U)
#define ETH_17_GETHMACV2_STAT_OCTETS                (1U)
#define ETH_17_GETHMACV2_STAT_PKTS                  (2U)
#define ETH_17_GETHMACV2_STAT_BROADCAST_PKTS        (3U)
#define ETH_17_GETHMACV2_STAT_MULTICAST_PKTS        (4U)
#define ETH_17_GETHMACV2_STAT_CRC_ALIGN_ERRORS      (5U)
#define ETH_17_GETHMACV2_STAT_UNDERSIZE_PKTS        (6U)
#define ETH_17_GETHMACV2_STAT_OVERSIZE_PKTS         (7U)
#define ETH_17_GETHMACV2_STAT_FRAGMENTS             (8U)
#define ETH_17_GETHMACV2_STAT_JABBERS               (9U)
#define ETH_17_GETHMACV2_STAT_COLLISIONS            (10U)
#define ETH_17_GETHMACV2_STAT_PKTS_64_OCTETS        (11U)
#define ETH_17_GETHMACV2_STAT_PKTS_65_127_OCTETS    (12U)
#define ETH_17_GETHMACV2_STAT_PKTS_128_255_OCTETS   (13U)
#define ETH_17_GETHMACV2_STAT_PKTS_256_511_OCTETS   (14U)
#define ETH_17_GETHMACV2_STAT_PKTS_512_1023_OCTETS  (15U)
#define ETH_17_GETHMACV2_STAT_PKTS_1024_1518_OCTETS (16U)

/* Macros used for list of Ethernet drop count items to be returned from
Eth_GetDropCount() APIs */
#define ETH_17_GETHMACV2_DROP_PKTS_BUFOVERRUN       (0U)
#define ETH_17_GETHMACV2_DROP_PKTS_CRCERROR         (1U)
#define ETH_17_GETHMACV2_DROP_PKTS_UNDERSIZE        (2U)
#define ETH_17_GETHMACV2_DROP_PKTS_OVERSIZE         (3U)
#define ETH_17_GETHMACV2_DROP_PKTS_ALIGNERROR       (4U)
#define ETH_17_GETHMACV2_DROP_PKTS_SQETESTERROR     (5U)
#define ETH_17_GETHMACV2_DROP_PKTS_RECV_Q_OVERFLOW  (6U)
#define ETH_17_GETHMACV2_DROP_ERRONEOUS_INB_PKTS    (7U)
#define ETH_17_GETHMACV2_DROP_OUTB_PKTS             (8U)
#define ETH_17_GETHMACV2_SINGLE_COLLISION_PKTS      (10U)
#define ETH_17_GETHMACV2_MULTIPLE_COLLISION_PKTS    (11U)
#define ETH_17_GETHMACV2_DEFERRED_TRANSMISSION_PKTS (12U)
#define ETH_17_GETHMACV2_LATE_COLLISION_PKTS        (13U)

#define ETH_17_GETHMACV2_DMA_FP           (0x0U)
#define ETH_17_GETHMACV2_DMA_WSP          (0x1U)
#define ETH_17_GETHMACV2_DMA_WRB          (0x2U)

/*******************************************************************************
**          Macros for Configuration Register Initial values                  **
*******************************************************************************/
/* Alternate input for Receive Clock for RGMII (RGMII can use ALT0 only).*/
#define ETH_17_GETHMACV2_RXCLK_ALT0_INPUT    (0x00000000U)
/* Alternate input for Receive Data 0 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMACV2_RXDATA0_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 1 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMACV2_RXDATA1_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 2 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMACV2_RXDATA2_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 3 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMACV2_RXDATA3_ALT0_INPUT  (0x00000000U)

/**** FULL DUPLEX MODE ****/
/* Init value for MAC configuration Register in Full-duplex mode. */
#define ETH_17_GETHMACV2_MAC_INIT_FDX_CONF (\
  (ETH_17_GETHMACV2_MACPREAMBLENGTH7     |\
   ETH_17_GETHMACV2_DEFERRALCHECKDISABLE | ETH_17_GETHMACV2_BACKOFFLIMIT2     |\
   ETH_17_GETHMACV2_RETRYENABLE          | ETH_17_GETHMACV2_ENABLERXOWN       |\
   ETH_17_GETHMACV2_LOOPBACKOFF          | ETH_17_GETHMACV2_JUMBOFRAMEDISABLE |\
   ETH_17_GETHMACV2_JABBERDISABLE        |\
   ETH_17_GETHMACV2_PACKETBURSTDISABLE   | ETH_17_GETHMACV2_WATCHDOGENABLE    |\
   ETH_17_GETHMACV2_PADCRCSTRIPDISABLE   |\
   ETH_17_GETHMACV2_CRCSTRTPKTDISABLE    | ETH_17_GETHMACV2_INTERPACKGAP96BIT |\
   ETH_17_GETHMACV2_TXDISABLE            | ETH_17_GETHMACV2_RXDISABLE         |\
   ETH_17_GETHMACV2_FULLDUPLEX))

#define ETH_17_GETHMACV2_MAC_CHKSM_OFFLD_ENBL  (0x08000000U)

/**** HALF DUPLEX MODE   ****/
/* Init value for MAC configuration Register in Half-duplex mode. */
#define ETH_17_GETHMACV2_MAC_INIT_HDX_CONF (\
  (ETH_17_GETHMACV2_MACPREAMBLENGTH7     |\
   ETH_17_GETHMACV2_DEFERRALCHECKDISABLE | ETH_17_GETHMACV2_BACKOFFLIMIT2     |\
   ETH_17_GETHMACV2_RETRYENABLE          | ETH_17_GETHMACV2_ENABLERXOWN       |\
   ETH_17_GETHMACV2_LOOPBACKOFF          | ETH_17_GETHMACV2_JUMBOFRAMEDISABLE |\
   ETH_17_GETHMACV2_JABBERDISABLE        |\
   ETH_17_GETHMACV2_PACKETBURSTDISABLE   | ETH_17_GETHMACV2_WATCHDOGENABLE    |\
   ETH_17_GETHMACV2_PADCRCSTRIPDISABLE   |\
   ETH_17_GETHMACV2_CRCSTRTPKTDISABLE    | ETH_17_GETHMACV2_INTERPACKGAP96BIT |\
   ETH_17_GETHMACV2_TXDISABLE            | ETH_17_GETHMACV2_RXDISABLE         |\
   ETH_17_GETHMACV2_HALFDUPLEX))

/**** MAC Registers   ****/
/* Init value for MAC Packet Filter Register. */
#define ETH_17_GETHMACV2_MAC_FILT_INIT_CONF (\
                                        (ETH_17_GETHMACV2_PROMISC_OFF       |\
                                         ETH_17_GETHMACV2_BROADCASTENABLE   |\
                                         ETH_17_GETHMACV2_RECEIVEALLOFF     |\
                                         ETH_17_GETHMACV2_PASSCONTROL0))

/*MAC Packet Filter Register value to completly open filter.*/

#define ETH_17_GETHMACV2_MAC_FILT_OPEN_CONF (\
                                        (ETH_17_GETHMACV2_PROMISC_ON       |\
                                         ETH_17_GETHMACV2_MULTICASTENABLE  |\
                                         ETH_17_GETHMACV2_RECEIVEALLON))

/**** MTL Registers   ****/
/* Init value for MTL Operation Mode Register - Common for Tx and Rx. */
#define ETH_17_GETHMACV2_MTL_OPERTN_MODE_INIT  (\
                                        (ETH_17_GETHMACV2_MTL_DTXTS_DISABLE|\
                                         ETH_17_GETHMACV2_MTL_RAA_SP))

/* Init value for MTL TX-Q Operation Mode Register. */
#define ETH_17_GETHMACV2_MTL_TXQ0_OPERTN_MODE_INIT  (\
                                        (ETH_17_GETHMACV2_MTL_TSF          |\
                                         ETH_17_GETHMACV2_MTL_TXQEN))

/* Init value for MTL RX-Q Operation Mode Register. */
#define ETH_17_GETHMACV2_MTL_RX_Q0_OPERTN_MODE_INIT (\
                                        (ETH_17_GETHMACV2_MTL_RSF          |\
                                         ETH_17_GETHMACV2_MTL_RQS_2048BYTES))

/* Macro for RX-Q0 to DMA-channel-0 mapping. */
#define ETH_17_GETHMACV2_MTL_RX_Q0_T0_DMA_MAP       (0x00U)

/* Macro to enable RX-Q0. */
#define ETH_17_GETHMACV2_MTL_ENABLE_RX_Q            (0x02U)

/**** DMA Registers   ****/
/* Init value for DMA Bus Mode Register. Interrupt Mode(INTM) - 01
 * DMA Tx or Rx Arbitration Scheme - Fixed Priority - 1
 * Tx DMA has higher priority than Rx Transmit Priority - 1  */
#define ETH_17_GETHMACV2_DMA_BUS_MODE_INIT_CONF    (0x00010802U)

/* Init value for DMA System Bus Mode Register. */
#define ETH_17_GETHMACV2_DMA_SYSBUS_MODE_INIT_CONF (\
                                          ETH_17_GETHMACV2_DMA_FB_DISABLE  |\
                                          ETH_17_GETHMACV2_DMA_AAL_DISABLE |\
                                          ETH_17_GETHMACV2_DMA_MB_DISABLE)

/* Macro to configure DMA 8xPBL( 8x burst length) mode. */
#define ETH_17_GETHMACV2_DMA_8X_BURST_LENGTH_MODE   (ETH_17_GETHMACV2_DISABLE)

/*Macro to configure DMA PBL( burst length) for Tx-DMA Channel */
#define ETH_17_GETHMACV2_DMA_CH_TXCTRL_CONF        (0x00080010U)

/*Macro to configure DMA PBL( burst length) for Rx-DMA Channel */
#define ETH_17_GETHMACV2_DMA_CH_RXPBL              (0x08U)

/**** DMA-Tx Descriptor ****/
/* Init value for TX- Descriptor TDES2. */
#define ETH_17_GETHMACV2_DMA_TDES2_INIT  ETH_17_GETHMACV2_DMA_TX_DESC_IOC_ENABLE

/**** DMA-Tx Descriptor ****/
/* Init value for RX- Descriptor RDES3. */
#define ETH_17_GETHMACV2_DMA_RDES3_INIT    (\
                                  (ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET     |\
                                   ETH_17_GETHMACV2_DMA_RX_DESC_IOC_ENABLE  |\
                                   ETH_17_GETHMACV2_DMA_RX_DESC_BF1_VALID))

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={438563B0-88A4-470d-AE54-A54DB8504B40}] */
typedef struct
{
  uint32 HiCredit;
  uint32 LoCredit;
  uint16 NumOfTxBuffers;
  uint16 TxBufferSize;
  uint16 TxBufferAlignSize;
  uint16 IdleSlopeCredit;
  uint16 SendSlopeCredit;
  uint8 TxFifoIdx;
  uint8 TxDmaChnlWght;
  uint8 TxQueueMode;
  uint8 TxQueueSize;
}Eth_17_GEthMacV2_TxFifoCfgType;
/*  [/cover] */

/* [cover parentID={FCC934B3-5007-4db6-8CC4-E73D4F2EBCE6}] */
typedef struct
{
  uint16 NumOfRxBuffers;
  uint16 RxBufferSize;
  uint16 RxBufferAlignSize;
  uint8 RxFifoIdx;
  uint8 RxFifoPriority;
  uint8 RxQueueSize;
}Eth_17_GEthMacV2_RxFifoCfgType;
/*  [/cover] */

/*Structure to store controller configuration data */
/* [cover parentID={793D4E0F-E2A1-432a-9C77-F9076BD21EC0}]
[/cover] */
typedef struct
{
  /*Specifies the Tx[0:3]/Rx[4:7] clock delay in RGMII mode for transmit
    skew timing*/
  uint32 EthSkewDelay;
  /* Element to store GETH_GPCTL register value for the controller */
  uint32 EthGpctlRegVal;
  /* Recommended time to wait for back to back register write */
  uint32 EthBkRegWrWaitTime;
  /* Pointer to the Tx FIFO parameters */
  const Eth_17_GEthMacV2_TxFifoCfgType *EthTxFifoCfgPtr;
  /* Pointer to the mapping of Tx FIFO to Channels */
  const uint8 *EthTxFifoChnlMapPtr;
  /* Pointer to the mapping of Tx Channels to FifoIdx */
  const uint8 *EthTxChnlFifoMapPtr;
  /* Pointer to the mapping of configured Priority to FifoIdx */
  const uint8 *EthTxPrioFifoMapPtr;
  /* Pointer to the Rx FIFO details */
  const Eth_17_GEthMacV2_RxFifoCfgType *EthRxFifoCfgPtr;
  /* Pointer to the mapping of Rx FIFO to Channels */
  const uint8 *EthRxFifoChnlMapPtr;
  /* Pointer to the mapping of channels to Rx Fifo */
  const uint8 *EthRxChnlFifoMapPtr;
  /* Propertes of Ethernet Controller
     Bit[0] - Port Select(PS)
       0 for 1000Mbps
       1 for 10 or 100 Mbps
     Bit[1] - Speed(FES)
       0 for 10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0.
       1 for 100 Mbps when PS bit is 1.
     Bit[2:4] - PhyInterface (000-MII, 100-RMII, 001-RGMII).
     Bit[5] - Mode of the Controller. [0 - HALFDUPLEX, 1- FULLDUPLEX].
     Bit[6] - Tx Interrupt Enable/Disable [0 - Disabled, 1- Enabled].
     Bit[7] - Rx Interrupt Enable/Disable [0 - Disabled, 1- Enabled].
     Bit[8] - CRC Stripping Enable/Disable [0 - Disabled, 1- Enabled].
  */
  uint16 EthCtrlProperties;
  /*DEM Id for ETH_E_ACCESS Failure.*/
  /* [cover parentID={1089BE26-1282-4b98-9216-4B0B8DF061C8}][/cover] */
  Dem_EventIdType EthDemAccess;
  /*DEM Id for ETH_E_RX_FRAMES_LOST Failure.*/
  /* [cover parentID={10E0143C-34CB-4122-81E6-4774332D7707}][/cover] */
  Dem_EventIdType EthDemFramesLost;
  /*DEM Id for ETH_E_ALIGNMENT Failure.*/
  /* [cover parentID={13AF5510-94E3-4801-ADFE-0FA118CD7025}][/cover] */
  Dem_EventIdType EthDemAlignment;
  /*DEM Id for ETH_E_CRC Failure.*/
  /* [cover parentID={31521667-F597-4497-AD39-607754604CF4}][/cover] */
  Dem_EventIdType EthDemCRC;
  /*DEM Id for ETH_E_UNDERSIZEFRAME Failure.*/
  /* [cover parentID={97349837-0874-47d9-9D48-F662E0631EFD}][/cover] */
  Dem_EventIdType EthDemUndersize;
  /*DEM Id for ETH_E_OVERSIZEFRAME Failure.*/
  /* [cover parentID={C9887F9D-F5AF-4ff8-AF36-D43549114184}][/cover] */
  Dem_EventIdType EthDemOversize;
  /*DEM Id for ETH_E_SINGLE_COLLISION Failure.*/
  /* [cover parentID={72001674-E7D8-4515-BFF8-CB7142CEB865}][/cover] */
  Dem_EventIdType EthDemSingleCollision;
  /*DEM Id for ETH_E_MULTIPLE_COLLISION Failure.*/
  /* [cover parentID={A33AD4B3-C211-447e-AAE5-6A9A6D3C9674}][/cover] */
  Dem_EventIdType EthDemMultipleCollision;
  /*DEM Id for ETH_E_LATE_COLLISION Failure.*/
  /* [cover parentID={D20EBE7A-EFE0-4493-BF0E-F1FBFD414CC0}][/cover] */
  Dem_EventIdType EthDemLateCollision;
  /* Default PHY MAC address in Network Byte order */
  uint8  EthMacAddress[6];
    /* Ethernet Controller Index */
  uint8  EthCtrlIdx;
  /* Number of Tx channels used in the controller */
  uint8  EthNumTxChnls;
  /* DMA transmit arbitration algorithm */
  uint8  EthDmaTxArbAlg;
  /* MTL transmit scheduling algorithm */
  uint8  EthMtlTxSchAlg;
  /* Number of Rx Channels used in the controller */
  uint8 EthNumRxChnls;
  /* Queue where the untagged Rx frames are routed */
  uint8 EthUntagRxQueue;
  /* CSR clock divider register field value for generation of MDC clock */
  uint8 EthMdcRegVal;
}Eth_17_GEthMacV2_CoreCtrlConfigType;


/* Structure to store core configuration data */
/* [cover parentID={664D5607-C54D-40d0-874F-FFB12B15AF69}] `
[/cover] */
typedef struct
{
  /* Element to store address of controller configuration for the current
     core */
  Eth_17_GEthMacV2_CoreCtrlConfigType* EthCoreCtrlPtr;
  /* Element to store maximum controllers allocated to current core */
  uint8                         EthMaxControllers;
}Eth_17_GEthMacV2_CoreConfigType;

/*Structure for Ethernet Post-Build configuration(for initialization) */
/* [cover parentID={81140149-9D26-470b-ACD6-D9259AE1C55C}]
[/cover] */
typedef struct
{
  /* Array to store starting addresses of Core Configuration data*/
  Eth_17_GEthMacV2_CoreConfigType* EthCoreAdd[ETH_17_GETHMACV2_MAX_CORES];
  /* Pointer to the array, Array value represents the index of the controller
     in the current core.*/
  uint8*                         EthNodeIdxMapPtr;
}Eth_17_GEthMacV2_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define ETH_17_GETHMACV2_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_TxDmaIrqHdlr(const uint8 CtrlIdx, **
**                                                    const uint8 DmaChnlIdx) **
**                                                                            **
** Description      : IRQ handler for frame transmission completion           **
**                    interrupt from Transmit DMA channel.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x11                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different DMA channel indexes and         **
**                      Ctrl indexes                                          **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    DmaChnlIdx - Transmit DMA channel index                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_TxDmaIrqHdlr(const uint8 CtrlIdx,
                                          const uint8 DmaChnlIdx);
#endif  /* (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON) */

#if (ETH_17_GETHMACV2_RX_IRQHDLR == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_RxDmaIrqHdlr(const uint8 CtrlIdx, **
**                                                    const uint8 DmaChnlIdx) **
**                                                                            **
** Description      : IRQ handler for frame reception completion              **
**                    interrupts from Receive DMA channel.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different DMA channel indexes and         **
**                      Ctrl indexes                                          **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    DmaChnlIdx - Receive DMA channel index                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_RxDmaIrqHdlr(const uint8 CtrlIdx,
                                          const uint8 DmaChnlIdx);
#endif /* (ETH_17_GETHMACV2_RX_IRQHDLR == STD_ON) */


#if ( ETH_17_GETHMACV2_ENA_MII_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_ReadMii(                **
**                                   const uint8 CtrlIdx,                     **
**                                   const uint8 TrcvIdx,const uint8 RegIdx,  **
**                                   uint16 *const RegValPtr)                 **
**                                                                            **
** Description      : Reads a transceiver register                            **
**                                                                            **
*** [/cover]                                                                  **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller                       **
**                    TrcvIdx - Index of the transceiver on the MII           **
**                    RegIdx  - Index of the transceiver register on the MII  **
**                                                                            **
** Parameters (out) : RegValPtr - Filled with the register content of the     **
**                              indexed register                              **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Service accepted                 **
**                                     E_NOT_OK: Service denied               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_ReadMii(const uint8 CtrlIdx,
                                               const uint8 TrcvIdx,
                                               const uint8 RegIdx,
                                               uint16* const RegValPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_WriteMii(               **
**                                        const uint8 CtrlIdx,                **
**                                        const uint8 TrcvIdx,                **
**                                        const uint8 RegIdx,                 **
**                                        const uint16 RegVal)                **
**                                                                            **
** Description      : Configures a transceiver register or triggers a function**
**                    offered by the transceiver                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller                       **
**                    TrcvIdx - Index of the transceiver on the MII           **
**                    RegIdx  - Index of the transceiver register on the MII  **
**                    RegVal  - Value to be written into the indexed register **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Service accepted                 **
**                                     E_NOT_OK: Service denied               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_WriteMii(const uint8 CtrlIdx,
                                                const uint8 TrcvIdx,
                                                const uint8 RegIdx,
                                                const uint16 RegVal);
#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_ReadMii(CtrlIdx,TrcvIdx,RegIdx,RegValPtr) \
                        (ERROR_Eth_17_GEthMacV2_ReadMii_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_WriteMii(CtrlIdx,TrcvIdx,RegIdx,RegVal) \
                        (ERROR_Eth_17_GEthMacV2_WriteMii_API_IS_NOT_SELECTED)

#endif /* End of ETH_17_GETHMACV2_ENA_MII_API */

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_Init                              **
**                       (const Eth_17_GEthMacV2_ConfigType* const CfgPtr )   **
**                                                                            **
** Description      : The function Initializes the Ethernet Driver and        **
**                    store the access to the configuration                   **
**                    parameters for subsequent API calls.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : CfgPtr - Pointer to configuration set                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_Init(const Eth_17_GEthMacV2_ConfigType*
                                                       const CfgPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : BufReq_ReturnType Eth_17_GEthMacV2_ProvideTxBuffer(     **
**                         const uint8 CtrlIdx, const uint8 Priority,         **
**                         Eth_BufIdxType* const BufIdxPtr,                   **
**                         uint8** const BufPtr, uint16* const LenBytePtr)    **
**                                                                            **
** Description      : Provides access to a transmit buffer of the FIFO        **
**                      related to the specified priority                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    Priority - Frame priority for transmit buffer FIFO      **
**                                selection                                   **
**                                                                            **
** Parameters (inout): LenBytePtr -In: desired length in bytes,               **
**                                 out: granted length in bytes               **
**                                                                            **
** Parameters (out) : BufIdxPtr - Index to the granted buffer resource        **
**                    BufPtr    - Pointer to the granted buffer               **
**                                                                            **
** Return value     : BUFREQ_OK       - Successfully granted buffer           **
**                    BUFREQ_E_NOT_OK - Development error detected            **
**                    BUFREQ_E_BUSY   - All Buffers are in USE                **
**                    BUFREQ_E_OVFL   - Requested buffer too large            **
**                                                                            **
*******************************************************************************/
extern BufReq_ReturnType Eth_17_GEthMacV2_ProvideTxBuffer(const uint8 CtrlIdx,
                        const uint8 Priority, Eth_BufIdxType* const BufIdxPtr,
                        uint8** const BufPtr, uint16* const LenBytePtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_Transmit(               **
**                    const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,       **
**                    const Eth_FrameType FrameType,                          **
**                    boolean TxConfirmation, const uint16 LenByte,           **
**                    const uint8* const PhysAddrPtr)                         **
**                                                                            **
** Description      : Triggers transmission of a previously                   **
**                    filled transmit buffer                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    BufIdx - Index of the buffer resource                   **
**                    FrameType- Ethernet frame type                          **
**                    TxConfirmation - Activates transmission confirmation    **
**                    LenByte - Data length in byte                           **
**                    PhysAddrPtr - Physical target address                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Success                                      **
**                    E_NOT_OK - Transmission failed                          **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_Transmit(
              const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,
              const Eth_FrameType FrameType, const boolean TxConfirmation,
              const uint16 LenByte, const uint8* const PhysAddrPtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_Receive( const uint8 CtrlIdx,     **
**                                   const uint8 FifoIdx,                     **
**                                   Eth_RxStatusType* const RxStatusPtr )    **
**                                                                            **
** Description      : Triggers frame reception                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    FifoIdx - Specifies the related FIFO                    **
**                                                                            **
** Parameters (out) : RxStatusPtr -  Indicates whether a frame has been       **
**                                   received and if so, whether more frames  **
**                                   are available or frames got lost.        **
**                                                                            **
*** Return value     : None                                                   **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_Receive(const uint8 CtrlIdx,
                                     const uint8 FifoIdx,
                                     Eth_RxStatusType* const RxStatusPtr);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_GetPhysAddr( const uint8 CtrlIdx, **
**                                             uint8* const PhysAddrPtr )     **
**                                                                            **
** Description      : Obtains the physical source address used by the         **
**                    indexed controller                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (out) : PhysAddrPtr - Physical source address (MAC address) in  **
**                      network byte order.                                   **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_GetPhysAddr(const uint8 CtrlIdx,
                                         uint8* const PhysAddrPtr);

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_TxConfirmation(                   **
**                                               const uint8 CtrlIdx)         **
**                                                                            **
** Description      : Triggers frame transmission confirmation                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_TxConfirmation( const uint8 CtrlIdx);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_SetControllerMode(      **
**                                    const uint8 CtrlIdx,                    **
**                                    const Eth_ModeType CtrlMode )           **
**                                                                            **
** Description      : Enables / Disables the indexed controller               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                    CtrlMode  - Controller Mode DOWN/ACTIVE                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Successfully Set the requested mode          **
**                    E_NOT_OK - Controller mode could not be changed         **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_SetControllerMode(const uint8 CtrlIdx,
                                                const Eth_ModeType CtrlMode);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetControllerMode(      **
**                        const uint8 CtrlIdx,Eth_ModeType* const CtrlModePtr)**
**                                                                            **
** Description      : Obtains the state of the indexed controller             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (out) : CtrlModePtr  -Controller Mode DOWN/ACTIVE               **
**                                                                            **
** Return value     : E_OK     - Success                                      **
**                    E_NOT_OK - Controller mode could not be obtained        **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetControllerMode(const uint8 CtrlIdx,
                                             Eth_ModeType* const CtrlModePtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_SetPhysAddr( const uint8 CtrlIdx, **
**                                         const uint8* const PhysAddrPtr )   **
**                                                                            **
** Description      : Sets the MAC address used by the indexed controller     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x13                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    PhysAddrPtr - MAC address in network byte order         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_SetPhysAddr(const uint8 CtrlIdx,
                                         const uint8* const PhysAddrPtr);

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_UpdatePhysAddrFilter(   **
**                      const uint8 CtrlIdx,const uint8* const PhysAddrPtr,   **
**                      const Eth_FilterActionType Action )                   **
**                                                                            **
** Description      : Adds or removes the MAC address from filter             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    PhysAddrPtr - MAC address in network byte order         **
**                    Action - Add or remove the MAC address from filter      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Filter was successfully changed                  **
**                    E_NOT_OK - Filter could not be changed                  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_UpdatePhysAddrFilter(
                       const uint8 CtrlIdx, const uint8* const PhysAddrPtr,
                       const Eth_FilterActionType Action);

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetCurrentTime(         **
**                              const uint8 CtrlIdx,                          **
**                              Eth_TimeStampQualType* const timeQualPtr,     **
**                              Eth_TimeStampType* const timeStampPtr)        **
**                                                                            **
** Description      : Returns a time value out of the HW registers.           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx      -  Index of Eth Controller within the      **
**                                    context of the Ethernet driver.         **
**                                                                            **
** Parameters (out) : timeQualPtr  -  Quality of HW time stamp, e.g.          **
**                    based on current drift                                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : Success                       **
**                                   -  E_NOT_OK : Failed                     **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetCurrentTime(const uint8 CtrlIdx,
              Eth_TimeStampQualType* const timeQualPtr, Eth_TimeStampType*
                                                      const timeStampPtr);

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_EnableEgressTimeStamp             **
**                      (const uint8 CtrlIdx, const Eth_BufIdxType BufIdx)    **
**                                                                            **
** Description      : The function activates timestamp for the specific       **
**                    transmit frame                                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x17                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    BufIdx        -  Index of the message buffer, where     **
**                                     application expects egress             **
**                                     time stamping                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_EnableEgressTimeStamp(const uint8 CtrlIdx,
                                                 const Eth_BufIdxType BufIdx);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetEgressTimeStamp      **
**                                 (const uint8 CtrlIdx, const uint8 BufIdx,  **
**                                  Eth_TimeStampQualType* const timeQualPtr, **
**                                  Eth_TimeStampType* const timeStampPtr)    **
**                                                                            **
** Description      : Reads back the egress time stamp on a dedicated message **
**                    object. It must be called within the TxConfirmation()   **
**                    function.                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x18                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    BufIdx        -  Index of the message buffer, where     **
**                                     Application expects egress             **
**                                     time stamping                          **
**                                                                            **
** Parameters (out) : timeQualPtr  -  quality of HW time stamp, e.g.          **
**                                    based on current drift                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Success                          **
**                                   - E_NOT_OK: Failed to read time stamp    **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType  Eth_17_GEthMacV2_GetEgressTimeStamp(const uint8 CtrlIdx,
        const Eth_BufIdxType BufIdx, Eth_TimeStampQualType* const timeQualPtr,
        Eth_TimeStampType* const timeStampPtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetIngressTimeStamp     **
**                                (const uint8 CtrlIdx,                       **
**                                 const Eth_DataType* const DataPtr,         **
**                                 Eth_TimeStampQualType* const timeQualPtr   **
**                                 Eth_TimeStampType* const timeStampPtr)     **
**                                                                            **
** Description      : Reads back the ingress time stamp on a dedicated        **
**                    message object. It must be called within the            **
**                    RxIndication() function.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x18                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    DataPtr       -  Index of the message buffer, where     **
**                                     Application expects Ingress            **
**                                     time stamping.                         **
**                                                                            **
** Parameters (out) : timeQualPtr  -  quality of HW time stamp, e.g.          **
**                                    based on current drift                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Success                          **
**                                   - E_NOT_OK: Failed to read time stamp    **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetIngressTimeStamp(const uint8 CtrlIdx,
                                   const Eth_DataType* const DataPtr,
                                   Eth_TimeStampQualType* const timeQualPtr,
                                   Eth_TimeStampType* const timeStampPtr);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetCurrentTime(CtrlIdx,timeQualPtr,timeStampPtr) \
              (ERROR_Eth_17_GEthMacV2_GetCurrentTime_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_EnableEgressTimeStamp(CtrlIdx,BufIdx) \
              (ERROR_Eth_17_GEthMacV2_EnableEgressTimeStamp_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetEgressTimeStamp(CtrlIdx,BufIdx,timeQualPtr, \
                                                        timeStampPtr) \
              (ERROR_Eth_17_GEthMacV2_GetEgressTimeStamp_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetIngressTimeStamp(CtrlIdx,DataPtr,timeQualPtr, \
                                                        timeStampPtr)\
              (ERROR_Eth_17_GEthMacV2_GetIngressTimeStamp_API_IS_NOT_SELECTED)

#endif/* End for ETH_17_GETHMACV2_GLOBALTIMESUPPORT */

#if(ETH_17_GETHMACV2_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax :          void Eth_17_GEthMacV2_GetVersionInfo                     **
**                             (Std_VersionInfoType * const VersionInfoPtr)   **
**                                                                            **
** Description :     This service will return the version info of ETH driver  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0D                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out): VersionInfoPtr : Pointer to hold the version values      **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_GetVersionInfo(Std_VersionInfoType*
                                            const VersionInfoPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetVersionInfo(VersionInfoPtr) \
                (ERROR_Eth_17_GEthMacV2_GetVersionInfo_API_IS_NOT_SELECTED)
#endif /* End for ETH_17_GETHMACV2_VERSION_INFO_API */

#if (ETH_17_GETHMACV2_GETCNTRVALUES_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetCounterValues(       **
**                                        const uint8 CtrlIdx,                **
**                                        Eth_CounterType* const CounterPtr)  **
**                                                                            **
** Description      : Reads a list of statistic counter values of the         **
**                    corresponding controller.  The meaning of these counter **
**                    values is described at Eth_CounterType.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x14                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx     - Index of Eth Controller within the        **
**                                  context of the Ethernet driver.           **
**                                                                            **
** Parameters (out) : CounterPtr - List of counter values according to IETF   **
**                     RFC 1757, RFC 1643 and RFC 2233                        **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK: success                         **
**                                      E_NOT_OK: Counter values could        **
**                                                not be obtained.            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetCounterValues(const uint8 CtrlIdx,
                                           Eth_CounterType* const CounterPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetCounterValues(CtrlIdx,CounterPtr) \
                (ERROR_Eth_17_GEthMacV2_GetCounterValues_API_IS_NOT_SELECTED)

#endif/* End for ETH_17_GETHMACV2_GETCNTRVALUES_API */

#if (ETH_17_GETHMACV2_GETRXSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetRxStats              **
**                        (const uint8 CtrlIdx,                               **
**                         Eth_RxStatsType* const RxStats)                    **
**                                                                            **
** Description      : Returns the receive statistic counter values            **
**                    (according to IETF RFC2819), where the maximal possible **
**                    value denotes an invalid value, for example, if this    **
**                    counter is not available.                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x15                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of Eth controller within the            **
**                              context of the Ethernet driver.               **
**                                                                            **
** Parameters (out) : RxStats - List of receive statistic counter values      **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : success                       **
**                                   -  E_NOT_OK : Rx error statistics could  **
**                                                 not be obtained            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetRxStats (const uint8 CtrlIdx,
                                        Eth_RxStatsType* const RxStats);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetRxStats(CtrlIdx,RxStats) \
                    (ERROR_Eth_17_GEthMacV2_GetRxStats_API_IS_NOT_SELECTED)
#endif/* End for ETH_17_GETHMACV2_GETRXSTATS_API */

#if (ETH_17_GETHMACV2_GETTXSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetTxStats              **
**                                          (const uint8 CtrlIdx,             **
**                                           Eth_TxStatsType* const TxStats)  **
**                                                                            **
** Description      : Returns the list of transmission statistics (described  **
**                    in IETF RFC1213) defined with Eth_TxStatsType, where    **
**                    the maximal possible value denotes an invalid value,    **
**                    for example, if this counter is not available.          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of Eth Controller within the            **
**                              context of the Ethernet driver.               **
**                                                                            **
**                                                                            **
** Parameters (out) : TxStats - List of statistic values for transmission.    **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : success                       **
**                                   -  E_NOT_OK : Tx statistics could not be **
**                                                 obtained                   **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetTxStats (const uint8 CtrlIdx,
                                            Eth_TxStatsType* const TxStats);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetTxStats(CtrlIdx,TxStats) \
                    (ERROR_Eth_17_GEthMacV2_GetTxStats_API_IS_NOT_SELECTED)
#endif/* End for ETH_17_GETHMACV2_GETTXSTATS_API */

#if (ETH_17_GETHMACV2_GETTXERRCNTRVAL_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_GetTxErrorCounterValues **
**                        (const uint8 CtrlIdx,                               **
**                         Eth_TxErrorCounterValuesType* const                **
**                             TxErrorCounterValues)                          **
**                                                                            **
** Description      : Returns the list of transmission error counters         **
**                    (described in IETF RFC1213 and RFC1643) defined with    **
**                    Eth_TxErrorCounterValuesType, where the maximal         **
**                    possible value shall denote an invalid value, for       **
**                    example, if this counter is not available.              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of Eth controller within the            **
**                              context of the Ethernet driver.               **
**                                                                            **
**                                                                            **
** Parameters (out) : TxErrorCounterValues - List of statistic error counter  **
**                                           values for transmission.         **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : success                       **
**                                   -  E_NOT_OK : Tx error statistics could  **
**                                                 not be obtained            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMacV2_GetTxErrorCounterValues (
                    const uint8 CtrlIdx,
                    Eth_TxErrorCounterValuesType* const TxErrorCounterValues);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMacV2_GetTxErrorCounterValues(CtrlIdx,TxErrorCounterValues) \
          (ERROR_Eth_17_GEthMacV2_GetTxErrorCounterValues_API_IS_NOT_SELECTED)
#endif/* End for ETH_17_GETHMACV2_GETTXERRCNTRVAL_API */

#define ETH_17_GETHMACV2_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMacV2_MemMap.h"

#include "Eth_17_GEthMacV2_PBcfg.h"

#endif /* ETH_17_GETHMACV2_H */
