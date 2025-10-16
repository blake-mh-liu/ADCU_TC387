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
**  FILENAME     : Eth_17_GEthMacV2.c                                         **
**                                                                            **
**  VERSION      : 10.0.0                                                     **
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
**  DESCRIPTION  : Eth Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Ethernet Driver,AUTOSAR Release 4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={BF94A146-7C19-46b2-818B-589D20D77A53}]
[/cover] */
/* [cover parentID={BD607180-6DDB-4175-9E75-6DCCAEBFBD5C}]
[/cover] */
/* [cover parentID={70671113-E91A-48e6-973A-C3667508093F}]
[/cover] */
/* [cover parentID={6EE6E933-ABA0-4c6e-9AF0-4A1BB260FF63}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={EA392A13-FCA8-42f7-B9BC-0967C60FE9AB}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
MemMap
[/cover] */
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in ETH driver
[/cover]*/
/*******************************************************************************
**                      Includes                                             **
*******************************************************************************/
/* Inclusion of ETH header file, this includes ETH configuration file also */
#include "Eth_17_GEthMacV2.h"

/* Inclusion of GETH MAC Register file */
#include "IfxGeth_reg.h"
#include "IfxGeth_bf.h"

/* Inclusion of SchM header file */
#include "SchM_Eth_17_GEthMacV2.h"

/* Inclusion of Mcal Specific Global Header File */
#include "McalLib.h"

#if((ETH_17_GETHMACV2_INIT_API_MODE != ETH_17_GETHMACV2_MCAL_SUPERVISOR)||\
    (ETH_17_GETHMACV2_RUNTIME_API_MODE != ETH_17_GETHMACV2_MCAL_SUPERVISOR))
#include "McalLib_OsStub.h"
#endif

/* Conditional Inclusion of Development Error Tracer File */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON) */

/* Inclusion of EthIf and EthTrcv header file */
#include "EthIf.h"
#include "EthTrcv.h"

/* Conditional Inclusion of EthSwt driver header file */
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Eth.h"
#endif /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/* [cover parentID={9ABF9C4B-71FA-447d-9E7F-2055169B63C7}]
[/cover] */
/* AUTOSAR Specification File Version Check */
#ifndef ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION
  #error "ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION is not defined."
#endif
  /* [cover parentID={3906CF90-17F8-4e45-8E49-1DCA068DA702}]
  Version check across files of Ethernet module
  [/cover] */
#if (ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#ifndef ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION
  #error "ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#if (ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION does not match."
#endif

#ifndef ETH_17_GETHMACV2_AR_RELEASE_REVISION_VERSION
  #error "ETH_17_GETHMACV2_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if (ETH_17_GETHMACV2_AR_RELEASE_REVISION_VERSION != \
                          MCAL_AR_RELEASE_REVISION_VERSION)
  #error "ETH_17_GETHMACV2_AR_RELEASE_REVISION_VERSION does not match."
#endif

/* ETH Header File Version Check */
#ifndef ETH_17_GETHMACV2_SW_MAJOR_VERSION
  #error "ETH_17_GETHMACV2_SW_MAJOR_VERSION is not defined."
#endif

#ifndef ETH_17_GETHMACV2_SW_MINOR_VERSION
  #error "ETH_17_GETHMACV2_SW_MINOR_VERSION is not defined."
#endif

#ifndef ETH_17_GETHMACV2_SW_PATCH_VERSION
  #error "ETH_17_GETHMACV2_SW_PATCH_VERSION is not defined."
#endif

#if (ETH_17_GETHMACV2_SW_MAJOR_VERSION != 20U)
  #error "ETH_17_GETHMACV2_SW_MAJOR_VERSION does not match."
#endif

#if (ETH_17_GETHMACV2_SW_MINOR_VERSION != 25U)
  #error "ETH_17_GETHMACV2_SW_MINOR_VERSION does not match."
#endif

#if (ETH_17_GETHMACV2_SW_PATCH_VERSION != 0U)
  #error "ETH_17_GETHMACV2_SW_PATCH_VERSION does not match."
#endif

/* [cover parentID={71DE244B-7A02-4769-9FE0-7A4D5BD79FFD}]
Inter module consistency checks
[/cover] */
/*
  VERSION CHECK FOR DET MODULE INCLUSION
  */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif/* End Of ETH_17_GETHMACV2_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*Used to enable ETH module, GETH_CLC.B.DISR = ETH_17_GETHMACV2_MOD_ENABLE */
#define ETH_17_GETHMACV2_MOD_ENABLE            (0U)

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
/* To check if the time stamp value provided by hardware is corrupted. */
#define ETH_17_GETHMACV2_INGRESS_TS_CORRUPT    (0xFFFFFFFFU)

/* Number of microseconds increments per clock or overflow */
#define ETH_17_GETHMACV2_SUB_SEC_INCREMENT_VAL (20U)

/* Enable timestamp for Tx and Rx  */
#define ETH_17_GETHMACV2_TS_ENABLE             (0x01U)

/* Macro used to check for Invalid FIFO index */
#define ETH_17_GETHMACV2_INV_FIFO_IDX          (0xFFU)

/* DMA descriptor index - invalid value */
#define ETH_17_GETHMACV2_DMADESC_INVALID       (0xFFFFU)
#endif

/* Ethernet frame's Header field length. */
#define ETH_17_GETHMACV2_FRAMEHEADER_LENGTH    (14U)
/* Ethernet frame's checksum field length. */
#define ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH    (4U)

/* Macros to Mask Interrupts which are enabled in default. */
#define ETH_17_GETHMACV2_DISABLE_MMC_TX_INTPT      (0x0FFFFFFFU)
#define ETH_17_GETHMACV2_DISABLE_MMC_RX_INTPT      (0x0FFFFFFFU)
#define ETH_17_GETHMACV2_DISABLE_MMC_IPC_RX_INTPT  (0x3FFF3FFFU)

/* Macro to Enable Address filtering in Mac Address register. */
#define ETH_17_GETHMACV2_MACADDRRESS_ENABLE        (0x80000000U)

#define ETH_17_GETHMACV2_BUFFER_NOTUSED            (0U)
#define ETH_17_GETHMACV2_BUFFER_USED               (1U)
#define ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED   (2U)

/* Macro for MAC address length. */
#define ETH_17_GETHMACV2_MACADDRESS_LEN            (6U)

#if ((ETH_17_GETHMACV2_RX_IRQHDLR == STD_ON) || \
     (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON))
/* Macro to check for set bit value */
#define ETH_17_GETHMACV2_SET                       (1U)
#endif

/* Macro for default value to load in MAC Address register 0 to 31. */
#define ETH_17_GETHMACV2_FILT0_DEF_HIGH_VAL        (0x8000FFFFU)
#define ETH_17_GETHMACV2_FILT0_DEF_LOW_VAL         (0xFFFFFFFFU)
#define ETH_17_GETHMACV2_FILT_HIGH_1_31_DEF_VAL    (0x0000FFFFU)
#define ETH_17_GETHMACV2_FILT_LOW_1_31_DEF_VAL     (0xFFFFFFFFU)

/* Number of Hardware MAC address filter registers available. */
#define ETH_17_GETHMACV2_NO_OF_FILTER_REGISTERS    (32U)

#define ETH_17_GETHMACV2_INVALID_FILTER_VALUE      (0xFFU)

/* Macros for Ethernet Frame fields. */
#define ETH_17_GETHMACV2_FRAME_DESTADDR_POS        (0U)
#define ETH_17_GETHMACV2_FRAME_SRCADDR_POS         (6U)
#define ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS        (12U)
#define ETH_17_GETHMACV2_FRAME_TYPE_LSB_POS        (13U)
#define ETH_17_GETHMACV2_FRAME_PAYLOAD_POS         (14U)

#if ((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON) || \
     (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON))
#define ETH_17_GETHMACV2_IPV4_ICMP_PROTOCOL        (0x01U)
#define ETH_17_GETHMACV2_IPV4_FRAMETYPE            (0x0800U)
#define ETH_17_GETHMACV2_FRAME_ICMP_CRC_POS        (36U)
#define ETH_17_GETHMACV2_FRAME_IPV4TYPE_POS        (23U)
#endif

/* Macro to Mask Buffer 1 Length field in Tx-Descriptor-TDES2(Bit 0 to 13) */
#define ETH_17_GETHMACV2_MASK_TDES2_BUF1LENGTH     (0xFFFFC000U)

/* Macros used for number of bits shifts and Byte Mask. */
#define ETH_17_GETHMACV2_SHIFT_4BIT                (4U)
#define ETH_17_GETHMACV2_SHIFT_8BIT                (8U)
#define ETH_17_GETHMACV2_SHIFT_12BIT               (12U)
#define ETH_17_GETHMACV2_SHIFT_16BIT               (16U)
#define ETH_17_GETHMACV2_SHIFT_24BIT               (24U)
#define ETH_17_GETHMACV2_BYTE0_MASK                (0x000000FFU)
#define ETH_17_GETHMACV2_BYTE_MASK                 (0xFFU)

#define ETH_17_GETHMACV2_MASK_LSB                  (0x00FFU)

/* Macro to represent duplex modes */
#define ETH_17_GETHMACV2_FULL_DUPLEX               (1U)
#define ETH_17_GETHMACV2_HALF_DUPLEX               (0U)

/* Macro for kernel reset not executed */
#define ETH_17_GETHMACV2_RST_NOT_EXEC              (0U)

/* Macro for queue flushing operation in progress */
#define ETH_17_GETHMACV2_QFLUSH_IN_PROG            (1U)

/* Macro to check for descriptor released by DMA */
#define ETH_17_GETHMACV2_DESC_RELEASED             (0U)

/* Macro for indicating no error */
#define ETH_17_GETHMACV2_NO_ERROR                  (0U)

#if ((ETH_17_GETHMACV2_ENA_MII_API == STD_ON) || \
     (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON))
/* Macro to check for busy state */
#define ETH_17_GETHMACV2_BUSY_ST                   (1U)
#endif

/* Macro for RGMII Mode */
#define ETH_17_GETHMACV2_RGMII                     (1U)

/* Macro for Frame received status */
#define ETH_17_GETHMACV2_FRM_NOTRECEIVED           (0U)
#define ETH_17_GETHMACV2_FRM_RECEIVED              (1U)

/* Macros for the position and mask of controller parameters within the
 * EthCtrlProperties structure element */
#define ETH_17_GETHMACV2_GPTCL_PHY_POS             (22U)
#define ETH_17_GETHMACV2_PHYINTF_POS               (2U)
#define ETH_17_GETHMACV2_PHYINTF_MSK               (7U)
#define ETH_17_GETHMACV2_OPMODE_POS                (5U)
#define ETH_17_GETHMACV2_OPMODE_MSK                (1U)
#define ETH_17_GETHMACV2_TXINT_POS                 (6U)
#define ETH_17_GETHMACV2_TXINT_MSK                 (1U)
#define ETH_17_GETHMACV2_TXRXINT_POS               (6U)
#define ETH_17_GETHMACV2_TXRXINT_MSK               (3U)
#define ETH_17_GETHMACV2_RXINT_POS                 (7U)
#define ETH_17_GETHMACV2_RXINT_MSK                 (1U)
#define ETH_17_GETHMACV2_CRCS_POS                  (8U)
#define ETH_17_GETHMACV2_CRCS_MSK                  (1U)
#define ETH_17_GETHMACV2_TXSKEW_MASK               (0x0FU)
#define ETH_17_GETHMACV2_RXSKEW_MASK               (0xF0U)
#define ETH_17_GETHMACV2_RXSKEW_OFF                (4U)
#define ETH_17_GETHMACV2_PS_MSK                    (1U)
#define ETH_17_GETHMACV2_FES_POS                   (1U)
#define ETH_17_GETHMACV2_FES_MSK                   (1U)

/* Tx interrupt enabled */
#define ETH_17_GETHMACV2_TXINT_ENABLED             (1U)

/* Rx interrupt enabled */
#define ETH_17_GETHMACV2_RXINT_ENABLED             (2U)

/* Macro for Maximum STM tick for overflow to happen. */
#define ETH_17_GETHMACV2_STM_TICK_OVERFLOW         (0xFFFFFFFFU)

/* Macro for RBSZ_13_y bit-field that indicates the buffer size*/
#define ETH_17_GETHMACV2_RBSZ_13_Y                 (2U)

/* Maximum channels/ FIFOs supported in this device */
#define ETH_17_GETHMACV2_MAXCHLS_SUPPORTED         (4U)

#if ((ETH_17_GETHMACV2_GETTXERRCNTRVAL_API == STD_ON) || \
     (ETH_17_GETHMACV2_GETRXSTATS_API == STD_ON) || \
     (ETH_17_GETHMACV2_GETCNTRVALUES_API == STD_ON))
/* Macros used for unsupported counter statistic */
#define ETH_17_GETHMACV2_UNSUPPORTED_CNTR        (0xFFFFFFFFU)
#endif

/* Macro to disable the MAC Transmission and Reception */
#define ETH_17_GETHMACV2_MAC_TXRX_DISABLEMASK    (0xFFFFFFFCU)
/* Macro to enable the MAC Transmission and Reception */
#define ETH_17_GETHMACV2_MAC_TXRX_ENABLEMASK     (0x00000003U)

/* Macro to enable the RX Queue */
#define ETH_17_GETHMACV2_MTL_RXQ_ENABLE          (0x2U)

/* Macro to get the index of the buffer */
#define ETH_17_GETHMACV2_BUFIDX_MASK             (0x00001FFFU)

#if ((ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON) || \
     (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON))
/* Macro to get the index of the channel */
#define ETH_17_GETHMACV2_CHNLIDX_MASK            (0xFFFFE000U)
#endif

/* Macro to get the valid index of the channel */
#define ETH_17_GETHMACV2_VLDCHNLIDX_MASK         (0x0000E000U)

/* Macro to shift the FIFO reference index in the designated position
 * within buffer Index */
#define ETH_17_GETHMACV2_FIFOIDX_POS             (13U)

#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
/* Maximum Priority that can be assigned to a FIFO */
#define ETH_17_GETHMACV2_MAX_PRIORITY            (0x7U)

/* Macro used to check for non-configured priority */
#define ETH_17_GETHMACV2_NONCFG_PRIORITY         (0xFFU)

#endif /* (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON) */

/* Enable CBS algorithm and credit not be reset to 0 when no packet to Tx */
#define ETH_17_GETHMACV2_ETS_AVALG_CC            (0x0000000CU)

/* The offset address of the MTL TXQ operation mode register */
#define ETH_17_GETHMACV2_MTL_REG_OFFSETADDR      (0x10U)

/* Transmit Queue in AVB mode */
#define ETH_17_GETHMACV2_TXQ_AVBMODE             (0x01U)

/* Buffer index queue - Reset value */
#define ETH_17_GETHMACV2_QRST_VAL                (0x1FFFU)

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
/* Length of EtherType field */
#define ETH_17_GETHMACV2_ETHERTYPE_LEN             (2U)
#endif

/* Macros for core init / deinit state */
#define ETH_17_GETHMACV2_CORE_UNINIT             (0x0U)
#define ETH_17_GETHMACV2_CORE_INIT               (0x1U)

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
[/cover] */
/* User and Supervisory mode related macros for Initialization API */
#if ETH_17_GETHMACV2_INIT_API_MODE  == ETH_17_GETHMACV2_MCAL_SUPERVISOR
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ETH_17_GETHMACV2_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data)\
                                    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_SFR_INIT_DEINIT_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  ETH_17_GETHMACV2_SFR_INIT_DEINIT_WRITE32(reg,value) \
                                                 ((*(reg)) = (uint32)(value))
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ETH_17_GETHMACV2_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data)\
                                MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_SFR_INIT_DEINIT_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  ETH_17_GETHMACV2_SFR_INIT_DEINIT_WRITE32(reg,value) \
                  MCAL_SFR_OS_WRITE32(ETH_17_GETHMACV2_MODULE_ID,reg,value)
#endif

/* To configure TX/RX Clock delay for skew timing, in RGMII mode,*/
/*User and Supervisory mode related macros for Run time APIs */
#if ETH_17_GETHMACV2_RUNTIME_API_MODE  == ETH_17_GETHMACV2_MCAL_SUPERVISOR

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for supervisor/ User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WritePeripEndInitProtReg(RegAdd,Data)

/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(reg,value) \
                                  ((*(reg)) = (uint32)(value))
#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for supervisor/ User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                              MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(reg,value) \
                   MCAL_SFR_OS_WRITE32(ETH_17_GETHMACV2_MODULE_ID,reg,value)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* Data Type for Controller Initialization Status */
/* [cover parentID={AD4706E2-D662-4672-8C5A-76B6E0AA9DFF}] */
typedef enum
{
  ETH_17_GETHMACV2_CTRL_NOT_INITIALIZED  = 0x0U,
  ETH_17_GETHMACV2_CTRL_INITIALIZED      = 0x1U
}Eth_17_GEthMacV2_CtrlConfigStatusType;
/*  [/cover] */

/* Structure for Transmit buffer table, contains the Tx status of each
 * Tx buffer index. */
/* [cover parentID={F95C6330-2081-4830-B62F-8BFF8FA21536}] */
typedef struct
{
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  /* Pointer to the Tx Data address used during invocation of EthSwt APIs */
  uint8 *SwtTxDataPtr;
  /* To store the Tx Length used during invocation of EthSwt APIs */
  uint16 SwtTxLength;
#endif
  uint16 BuffLengthReqstd;
  uint8 BuffStatus;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  uint8 TimeStampEnable;
#endif
}Eth_17_GEthMacV2_TxBuffTableType;
/*  [/cover] */

/* Structure for Transmit Descriptor*/
/*** Read Format  - Read by DMA and Written by software  ***/
/* Tx Descriptor 0 - Buffer 1 address */
/* Tx Descriptor 1 - Buffer 2 Address */
/* Tx Descriptor 2 - IOC, TTSE, Buffer 1 and Buffer 2 Length*/
/* Tx Descriptor 3 - OWN, CTXT, FD, LD, CPC, CIC, TPL */

/*** Write Format - Written by DMA controller and Read by software ***/
/* Tx Descriptor 0 - Transmit Packet's Timestamp Low */
/* Tx Descriptor 1 - Transmit Packet's Timestamp High */
/* Tx Descriptor 2 - Reserved */
/* Tx Descriptor 3 - OWN, CTXT, FD, LD, Tx Timestamp Status */
/* [cover parentID={25937530-31AD-42c9-930D-B752B846396E}] */
typedef volatile struct
{
  uint32 TDES0;
  uint32 TDES1;
  uint32 TDES2;
  uint32 TDES3;
}Eth_17_GEthMacV2_DmaTxDescType;
/*  [/cover] */

/* Structure for Receive Descriptor*/
/*** Read Format  - Read by DMA and Written by software  ***/
/* Rx Descriptor 0 - Buffer 1 address */
/* Rx Descriptor 1 - Reserved */
/* Rx Descriptor 2 - Buffer 2 address */
/* Rx Descriptor 3 - OWN, IOC, Buffer1 valid and Buffer2 valid */

/*** Write Format - Written by DMA controller and Read by software ***/
/* Rx Descriptor 0 - IVT, OVT (VLAN)*/
/* Rx Descriptor 1 - Timestamp Dropped, Timestamp Available etc.*/
/* Rx Descriptor 2 - L3L4FM, L4FM etc. */
/* Rx Descriptor 3 - OWN, CTXT, FD, LD, Length/Type, Packet Length(PL)*/

/*** Context Descriptor - Written by DMA controller and Read by software ***/
/* Rx Descriptor 0 - Receive Packet's Timestamp Low */
/* Rx Descriptor 1 - Receive Packet's Timestamp High */
/* Rx Descriptor 2 - Reserved */
/* Rx Descriptor 3 - OWN,CTXT */
/* [cover parentID={90FED407-400E-47f6-A492-C47C82962CA9}] */
typedef volatile struct
{
  uint32 RDES0;
  uint32 RDES1;
  uint32 RDES2;
  uint32 RDES3;
}Eth_17_GEthMacV2_DmaRxDescType;
/*  [/cover] */

/* Structure for MAC Address registers 1 to 31, HIGH and LOW */
/* [cover parentID={CDFCE8EE-238C-4b9b-A4DE-1CA5B77F7DAD}] */
typedef volatile struct
{
  Ifx_GETH_MAC_ADDRESS_HIGH AddrHigh;
  Ifx_GETH_MAC_ADDRESS_LOW  AddrLow;
}Eth_17_GEthMacV2_MacAddr_1_31Type;
/*  [/cover] */

/* Structure to hold run-time operational data of ETH Controller*/
/* [cover parentID={E0229786-4927-4c9e-B335-EE0B3F16CE85}] */
typedef struct
{
  /* To store current Controller mode */
  Eth_ModeType EthControllerMode;
  /* To store previous controller mode */
  Eth_ModeType PrevEthControllerMode;
  /* Controller Initialization status */
  Eth_17_GEthMacV2_CtrlConfigStatusType CtrlConfigStatus;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Array of pointers to store the current DataPtr values for Ingress
   * timestamping */
  Eth_DataType* RxTmStmpDataPtr[ETH_17_GETHMACV2_MAXCHLS_SUPPORTED];
#endif
  /* To store controller's unique unicast MAC address */
  uint8 EthUnicastMacAddress[6];
  /* To store status of Address filter, is open or not*/
  boolean AddressFilterOpenStat;
}Eth_17_GEthMacV2_RunTimeOpertnDataType;
/*  [/cover] */

/* Structure to hold run-time operational data of Tx channels */
/* [cover parentID={74A3BE97-32DA-4964-B3F8-37E1654279F1}] */
typedef struct
{
  /* Index of the Tx DMA descriptor table */
  uint16 CurrTxDmaDescIdx;
  /* Index of the confirmed Tx DMA descriptor table */
  uint16 CnfrmTxDmaDescIdx;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Tx-DMA descriptor index where egress time-stamp has to be read */
  uint16 TxDmaDescIdxTmStmp;
#endif
  /* Current queue front index used to get the element from the queue */
  uint16 CurrQFront;
  /* Current queue rear index used to store the element into the queue */
  uint16 CurrQRear;
}Eth_17_GEthMacV2_RunTmTxChnlDataType;
/*  [/cover] */

/* Structure to hold run-time operational data of Rx channels */
/* [cover parentID={494B8035-7FD3-49e8-B69C-549EC0A64E77}] */
typedef struct
{
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  /* Pointer to the Rx Data address used during invocation of EthSwt APIs */
  uint8 *SwtRxDataPtr;
  /* To store the Rx Length used during invocation of EthSwt APIs */
  uint16 SwtRxLength;
#endif
  /* Rx index used for storing currently scanning Rx-DMA descriptor. */
  uint16 CurrRxDmaDescIdx;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Rx-DMA descriptor index where Ingress Timestamp has to be read. */
  uint16 RxDmaDescIdxTmStmp;
#endif
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  /* Flag to indicate type of frame used during invocation of EthSwt APIs */
  boolean SwtMgmtFrameOnly;
#endif
}Eth_17_GEthMacV2_RunTmRxChnlDataType;
/*  [/cover] */

/* Structure to hold transmit descriptor related runtime data */
/* [cover parentID={86F326CA-37ED-49f5-8F89-78F1BE4B5C2D}] */
typedef struct
{
  /* Mapping of the Tx descriptor index to buffer index */
  uint16 TxDescBufMapIdx;
  /* Indicates that Tx is initiated */
  uint8 FrameTxInitiated;
  /* Indicates whether the Tx confirmation is requested or not */
  uint8 TxConfirmReq;
}Eth_17_GEthMacV2_TxDescBufMapStType;
/*  [/cover] */

/* Structure for DemReportedCount */
/* [cover parentID={9630E2F7-DB0B-409e-AC40-E57A485CBB21}] */
typedef struct
{
  uint32 Count;
  uint32 DemReportedCount;
}Eth_17_GEthMacV2_StatsCntrDemReportStatType;
/*  [/cover] */

/* Structure to record statistics count on undersize, oversize, CRC, alignment
 * failures, Rx frames lost and collision errors */
/* [cover parentID={6F7A007A-DAF6-4851-9528-45C615D1E384}] */
typedef struct
{
  Eth_17_GEthMacV2_StatsCntrDemReportStatType RxFramesLostCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType CRCErrorFrameCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType UnderSizeFrameCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType OverSizeFrameCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType AlignmentErrorFrameCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType SingleCollisionCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType MultipleCollisionCounter;
  Eth_17_GEthMacV2_StatsCntrDemReportStatType LateCollisionCounter;
}Eth_17_GEthMacV2_StatsCntrType;
/*  [/cover] */

/* [cover parentID={6092FCC1-816B-4c2a-97EB-6DA24F80F2BD}] */
typedef struct
{
  /* Pointer to Ethernet Tx Buffer table contains Tx status of each Tx buffer */
  Eth_17_GEthMacV2_TxBuffTableType **EthTxBuffTablePtr;
  /* Pointer to Transmit Descriptors list. One descriptor for each Tx Buffer. */
  Eth_17_GEthMacV2_DmaTxDescType **EthDmaTxDescPtr;
  /* Pointer to receive Descriptors list. One descriptor for each Rx Buffer. */
  Eth_17_GEthMacV2_DmaRxDescType **EthDmaRxDescPtr;
  /* Pointer to structure which holds the run-time data of Tx Channels */
  Eth_17_GEthMacV2_RunTmTxChnlDataType *EthRunTmTxChnlDataPtr;
  /* Pointer to structure which holds the run-time data of Rx Channels */
  Eth_17_GEthMacV2_RunTmRxChnlDataType *EthRunTmRxChnlDataPtr;
  /* Pointer to transmit descriptor related runtime data */
  Eth_17_GEthMacV2_TxDescBufMapStType **EthTxDescBufMapStPtr;
  /* Pointer to Queue which contains the available Tx buffer indices */
  uint16 **EthTxBuffQueuePtr;
  /* Pointer to Rx Buffer*/
  volatile uint8 **EthRxBufferPtr;
  /* Pointer to Tx Buffer*/
  volatile uint8 **EthTxBufferPtr;
}Eth_17_GEthMacV2_BuffDescType;
/*  [/cover] */

/* [cover parentID={F6623EE0-ABE2-4de1-9ADB-E6F29C5BC454}] */
typedef struct
{
  /* Variable to hold run-time operational data of ETH driver*/
  Eth_17_GEthMacV2_RunTimeOpertnDataType EthRunTimeOpertnData;
  /* Data structure to store statistics counter values. */
  Eth_17_GEthMacV2_StatsCntrType EthStatisticsCounters;
  /* Pointer to Buffers and Descriptors for the current controller */
  Eth_17_GEthMacV2_BuffDescType* EthBuffDescPtr;
}Eth_17_GEthMacV2_CtrlStatusType;
/*  [/cover] */

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core0*/
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore0[ETH_17_GETHMACV2_MAX_CTRL_CORE0];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core0*/
static uint32 Eth_17_GEthMacV2_InitStCore0;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core1 */
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore1[ETH_17_GETHMACV2_MAX_CTRL_CORE1];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core1 */
static uint32 Eth_17_GEthMacV2_InitStCore1;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core2 */
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore2[ETH_17_GETHMACV2_MAX_CTRL_CORE2];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core2 */
static uint32 Eth_17_GEthMacV2_InitStCore2;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core3 */
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore3[ETH_17_GETHMACV2_MAX_CTRL_CORE3];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core3 */
static uint32 Eth_17_GEthMacV2_InitStCore3;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core4 */
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore4[ETH_17_GETHMACV2_MAX_CTRL_CORE4];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core4 */
static uint32 Eth_17_GEthMacV2_InitStCore4;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif


#if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0xFFU)
#if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store status of the controller(s) allocated to core5 */
static Eth_17_GEthMacV2_CtrlStatusType
          Eth_17_GEthMacV2_CtrlStCore5[ETH_17_GETHMACV2_MAX_CTRL_CORE5];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store initialization status of core5 */
static uint32 Eth_17_GEthMacV2_InitStCore5;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif
#endif

/* [cover parentID={0176B556-D35A-4cc2-A3B7-95F77AF9C8E6}]
[/cover] */
#ifdef ETH_17_GETHMACV2_CTRL0_CONFIGURED
#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
/* Global variable to store Tx buffer status for ctrl-0 FIFO-0 */
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-0 FIFO-0 */
static Eth_17_GEthMacV2_TxDescBufMapStType
                                Eth_17_GEthMacV2_TxMapStFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-0 FIFO-1 */
static Eth_17_GEthMacV2_TxDescBufMapStType
                                Eth_17_GEthMacV2_TxMapStFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-0 FIFO-2 */
static Eth_17_GEthMacV2_TxDescBufMapStType
                                Eth_17_GEthMacV2_TxMapStFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT];
#endif  /* (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-0 FIFO-3 */
static Eth_17_GEthMacV2_TxDescBufMapStType
                                Eth_17_GEthMacV2_TxMapStFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT];
#endif

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={F9C5C167-6106-46b4-BFE5-AE724C8E3597}]
[/cover] */
/* [cover parentID={0176B556-D35A-4cc2-A3B7-95F77AF9C8E6}]
[/cover] */
#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={05EE3492-395F-4f56-8504-C3AEA6A2E9F3}]
[/cover] */
#if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
/* Transmit buffer for ctrl-0 FIFO-0 */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_SIZE];
#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
/* Transmit buffer for ctrl-0 FIFO-1 */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_SIZE];
#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
/* Transmit buffer for ctrl-0 FIFO-2 */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_SIZE];
#endif  /* (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
/* Transmit buffer for ctrl-0 FIFO-3 */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_SIZE];
#endif

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={F9C5C167-6106-46b4-BFE5-AE724C8E3597}]
[/cover] */
/* [cover parentID={0176B556-D35A-4cc2-A3B7-95F77AF9C8E6}]
[/cover] */
#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/*[cover parentID={E5A73625-895E-4f51-9B32-0C04C416FD96}]
[/cover]*/

#if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
/* Global variable to store Tx Descriptor status for ctrl-0 FIFO-0 */
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT];

#endif  /* (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT];
#endif

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_16
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-0 FIFO-0 */
static uint16 Eth_17_GEthMacV2_TxQBufFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-0 FIFO-1 */
static uint16 Eth_17_GEthMacV2_TxQBufFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-0 FIFO-2 */
static uint16 Eth_17_GEthMacV2_TxQBufFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT];
#endif  /* (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-0 FIFO-3 */
static uint16 Eth_17_GEthMacV2_TxQBufFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U) */

/* Structure to hold the run-time data of Tx channels for ctrl 0 */
#if (ETH_17_GETHMACV2_CTRL0_TXFIFO_CFGD != 0U)
static Eth_17_GEthMacV2_RunTmTxChnlDataType
      Eth_17_GEthMacV2_TxChnlDataCtrl0[ETH_17_GETHMACV2_CTRL0_TXFIFO_CFGD];
#endif

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_16
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_16
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

static Eth_17_GEthMacV2_TxBuffTableType *Eth_17_GEthMacV2_TxBufTblCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

/* Global variable to store Tx Descriptor status for controller 0 */
static Eth_17_GEthMacV2_DmaTxDescType *Eth_17_GEthMacV2_DmaTxDescCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

/* Transmit buffer for controller 0 */
static volatile uint8 *Eth_17_GEthMacV2_TxBufCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

/* Transmit descriptor table data for controller 0 */
static Eth_17_GEthMacV2_TxDescBufMapStType *Eth_17_GEthMacV2_TxMapStCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

static uint16 *Eth_17_GEthMacV2_TxQBufCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_CTRL0_RXFIFO_CFGD != 0U)
/* Structure to hold the run-time data of Rx channels for ctrl 0 */
static Eth_17_GEthMacV2_RunTmRxChnlDataType
      Eth_17_GEthMacV2_RxChnlDataCtrl0[ETH_17_GETHMACV2_CTRL0_RXFIFO_CFGD];
#endif

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={F9C5C167-6106-46b4-BFE5-AE724C8E3597}]
[/cover] */
#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U)
/* Receive buffer for controller 0 channel 0 */
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U)
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U)
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U)
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U) */

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={F9C5C167-6106-46b4-BFE5-AE724C8E3597}]
[/cover] */
#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Global variable to store Rx Descriptor status for controller 0 */
#if (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo0Ctrl0
                                  [ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo1Ctrl0
                                  [ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo2Ctrl0
                                  [ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U)
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo3Ctrl0
                                  [ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U) */

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={5737A944-6EC4-49b0-A840-0B70D1E81046}]
[/cover] */
static Eth_17_GEthMacV2_DmaRxDescType *Eth_17_GEthMacV2_DmaRxDescCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

/* [cover parentID={C7DF8D34-8E0E-41a2-81ED-E5A96407E974}]
[/cover] */
/* Receive buffer for controller 0 */
static volatile uint8 *Eth_17_GEthMacV2_RxBufCtrl0Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo0Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo1Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo2Ctrl0,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL0_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo3Ctrl0
  #else
  NULL_PTR
  #endif
};

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* Variable to store starting address of Buffertable, Tx/Rx descriptors and
   Tx/Rx Buffers. (Controller0) */
static Eth_17_GEthMacV2_BuffDescType Eth_17_GEthMacV2_BuffDescCtrl0 =
{
  Eth_17_GEthMacV2_TxBufTblCtrl0Ptr,
  Eth_17_GEthMacV2_DmaTxDescCtrl0Ptr,
  Eth_17_GEthMacV2_DmaRxDescCtrl0Ptr,
#if (ETH_17_GETHMACV2_CTRL0_TXFIFO_CFGD != 0U)
  Eth_17_GEthMacV2_TxChnlDataCtrl0,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_CTRL0_RXFIFO_CFGD != 0U)
  Eth_17_GEthMacV2_RxChnlDataCtrl0,
#else
  NULL_PTR,
#endif
  Eth_17_GEthMacV2_TxMapStCtrl0Ptr,
  Eth_17_GEthMacV2_TxQBufCtrl0Ptr,
  Eth_17_GEthMacV2_RxBufCtrl0Ptr,
  Eth_17_GEthMacV2_TxBufCtrl0Ptr
};

#if defined ETH_17_GETHMACV2_CTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif /*ETH_17_GETHMACV2_CTRL0_CONFIGURED*/


#ifdef ETH_17_GETHMACV2_CTRL1_CONFIGURED
#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Global variable to store Tx buffer status for controller 1 */
/*[cover parentID={97064F03-3879-453c-A415-346D5524BDE5}]
[/cover]*/

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-1 FIFO-0 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxDescBufMapStType Eth_17_GEthMacV2_TxMapStFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-1 FIFO-1 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxDescBufMapStType Eth_17_GEthMacV2_TxMapStFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-1 FIFO-2 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxDescBufMapStType Eth_17_GEthMacV2_TxMapStFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxBuffTableType Eth_17_GEthMacV2_TxBufTblFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT];

/* Mapping of Tx DMA index to buffer index for ctrl-1 FIFO-3 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_TxDescBufMapStType Eth_17_GEthMacV2_TxMapStFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U) */

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Global variable to store Tx buffer status for controller 1 */
/* [cover parentID={05EE3492-395F-4f56-8504-C3AEA6A2E9F3}]
[/cover] */

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_TxBufFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_SIZE];

#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U) */

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Global variable to store Tx buffer status for controller 1 */
/*[cover parentID={E5A73625-895E-4f51-9B32-0C04C416FD96}]
[/cover]*/

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaTxDescType Eth_17_GEthMacV2_DmaTxDescFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT];

#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U) */

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_TXDESC_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_16
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-1 FIFO-0 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static uint16 Eth_17_GEthMacV2_TxQBufFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-1 FIFO-1 */
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
  characters due to MIP added as per AUTOSAR requirement. Since compiler
  supports more than 32 characters, no side effects seen. */
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
  characters due to MIP added as per AUTOSAR requirement. Since compiler
  supports more than 32 characters, no side effects seen. */
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
  characters due to MIP added as per AUTOSAR requirement. Since compiler
  supports more than 32 characters, no side effects seen. */
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
  characters due to MIP added as per AUTOSAR requirement. Since compiler
  supports more than 32 characters, no side effects seen. */
static uint16 Eth_17_GEthMacV2_TxQBufFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-1 FIFO-2 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static uint16 Eth_17_GEthMacV2_TxQBufFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT];
#endif  /* (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U) */

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
/* Queue for transmit buffer indices for ctrl-1 FIFO-3 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static uint16 Eth_17_GEthMacV2_TxQBufFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT];
#endif /* (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U) */

/* Structure to hold the run-time data of Tx channels for ctrl 1 */
#if (ETH_17_GETHMACV2_CTRL1_TXFIFO_CFGD != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_RunTmTxChnlDataType\
      Eth_17_GEthMacV2_TxChnlDataCtrl1[ETH_17_GETHMACV2_CTRL1_TXFIFO_CFGD];
#endif

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_16
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_16
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

static Eth_17_GEthMacV2_TxBuffTableType *Eth_17_GEthMacV2_TxBufTblCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufTblFifo3Ctrl1
#else
  NULL_PTR
#endif
};

/* Global variable to store Tx Descriptor status for controller 1 */
static Eth_17_GEthMacV2_DmaTxDescType *Eth_17_GEthMacV2_DmaTxDescCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaTxDescFifo3Ctrl1
#else
  NULL_PTR
#endif
};

/* Transmit buffer for controller 1 */
static volatile uint8 *Eth_17_GEthMacV2_TxBufCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED]=
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxBufFifo3Ctrl1
#else
  NULL_PTR
#endif
};

/* Mapping of Tx DMA index to buffer index for ctrl-1 */
static Eth_17_GEthMacV2_TxDescBufMapStType *Eth_17_GEthMacV2_TxMapStCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED]=
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxMapStFifo3Ctrl1
#else
  NULL_PTR
#endif
};

static uint16 *Eth_17_GEthMacV2_TxQBufCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
  #if (ETH_17_GETHMACV2_FIFO0_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo0Ctrl1,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO1_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo1Ctrl1,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO2_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo2Ctrl1,
  #else
  NULL_PTR,
  #endif
  #if (ETH_17_GETHMACV2_FIFO3_CTRL1_TXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_TxQBufFifo3Ctrl1
  #else
  NULL_PTR
  #endif
};

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#if (ETH_17_GETHMACV2_CTRL1_RXFIFO_CFGD != 0U)
/* Structure to hold the run-time data of Rx channels for ctrl 1 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_RunTmRxChnlDataType\
      Eth_17_GEthMacV2_RxChnlDataCtrl1[ETH_17_GETHMACV2_CTRL1_RXFIFO_CFGD];
#endif

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Global variable to store Rx Descriptor status for controller 1 */

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_SIZE];
#endif

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_SIZE];
#endif

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_SIZE];
#endif

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static volatile uint8 Eth_17_GEthMacV2_RxBufFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_SIZE];
#endif

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXBUFFER_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_START_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Global variable to store Rx Descriptor status for controller 1 */

#if (ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo0Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_COUNT];
#endif

#if (ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo1Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_COUNT];
#endif

#if (ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo2Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_COUNT];
#endif

#if (ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_COUNT != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
characters due to MIP added as per AUTOSAR requirement. Since compiler
supports more than 32 characters, no side effects seen. */
static Eth_17_GEthMacV2_DmaRxDescType Eth_17_GEthMacV2_DmaRxDescFifo3Ctrl1\
                                  [ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_COUNT];
#endif

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_RXDESC_STOP_SEC_VAR_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/* [cover parentID={5737A944-6EC4-49b0-A840-0B70D1E81046}]
[/cover] */
static Eth_17_GEthMacV2_DmaRxDescType *Eth_17_GEthMacV2_DmaRxDescCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_DmaRxDescFifo3Ctrl1
#else
  NULL_PTR
#endif
};

/* [cover parentID={C7DF8D34-8E0E-41a2-81ED-E5A96407E974}]
[/cover] */
/* Receive buffer for controller 1 */
static volatile uint8 *Eth_17_GEthMacV2_RxBufCtrl1Ptr
                                  [ETH_17_GETHMACV2_MAXCHLS_SUPPORTED] =
{
#if (ETH_17_GETHMACV2_FIFO0_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo0Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO1_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo1Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO2_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo2Ctrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_FIFO3_CTRL1_RXBUF_COUNT != 0U)
  Eth_17_GEthMacV2_RxBufFifo3Ctrl1
#else
  NULL_PTR
#endif
};

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_32
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"


#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Variable to store starting address of Buffertable, Tx/Rx descriptors and
   Tx/Rx Buffers. (Controller1) */

static Eth_17_GEthMacV2_BuffDescType Eth_17_GEthMacV2_BuffDescCtrl1 =
{
  Eth_17_GEthMacV2_TxBufTblCtrl1Ptr,
  Eth_17_GEthMacV2_DmaTxDescCtrl1Ptr,
  Eth_17_GEthMacV2_DmaRxDescCtrl1Ptr,
#if (ETH_17_GETHMACV2_CTRL1_TXFIFO_CFGD != 0U)
  Eth_17_GEthMacV2_TxChnlDataCtrl1,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_CTRL1_RXFIFO_CFGD != 0U)
  Eth_17_GEthMacV2_RxChnlDataCtrl1,
#else
  NULL_PTR,
#endif
  Eth_17_GEthMacV2_TxMapStCtrl1Ptr,
  Eth_17_GEthMacV2_TxQBufCtrl1Ptr,
  Eth_17_GEthMacV2_RxBufCtrl1Ptr,
  Eth_17_GEthMacV2_TxBufCtrl1Ptr
};

#if defined ETH_17_GETHMACV2_CTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMACV2_CTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

#endif /* ETH_17_GETHMACV2_CTRL1_CONFIGURED */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* Array contains pointers to core initialization status */
static const Eth_17_GEthMacV2_ConfigType* Eth_17_GEthMacV2_ConfigPtr;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

static uint32* const Eth_17_GEthMacV2_CoreInitStatusPtr
                                  [ETH_17_GETHMACV2_MAX_CORES] =
{
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0U)
  &Eth_17_GEthMacV2_InitStCore0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0U)
  &Eth_17_GEthMacV2_InitStCore1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0U)
  &Eth_17_GEthMacV2_InitStCore2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0U)
  &Eth_17_GEthMacV2_InitStCore3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0U)
  &Eth_17_GEthMacV2_InitStCore4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0U)
  &Eth_17_GEthMacV2_InitStCore5,
  #else
  NULL_PTR,
  #endif
  #endif
};

/* Array contains pointers to Controller status of the core */
static Eth_17_GEthMacV2_CtrlStatusType* const
                  Eth_17_GEthMacV2_CtrlStatusPtr[ETH_17_GETHMACV2_MAX_CORES]=
{
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE0 != 0U)
  Eth_17_GEthMacV2_CtrlStCore0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE1 != 0U)
  Eth_17_GEthMacV2_CtrlStCore1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE2 != 0U)
  Eth_17_GEthMacV2_CtrlStCore2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE3 != 0U)
  Eth_17_GEthMacV2_CtrlStCore3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE4 != 0U)
  Eth_17_GEthMacV2_CtrlStCore4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0xFFU)
  #if (ETH_17_GETHMACV2_MAX_CTRL_CORE5 != 0U)
  Eth_17_GEthMacV2_CtrlStCore5,
  #else
  NULL_PTR,
  #endif
  #endif
};
/* Stores the base address of the ethernet controllers */
static Ifx_GETH* const Eth_17_GEthMacV2_CtrlBaseAddrPtr
                                  [ETH_17_GETHMACV2_MAX_CONTROLLERS] =
{
  &MODULE_GETH,
  #if (ETH_17_GETHMACV2_MAX_CONTROLLERS > 1U)
  &MODULE_GETH1
  #endif
};
/* Array contains pointers to controller buffers/descriptors */
/* MISRA2012_RULE_8_9_JUSTIFICATION: Eth_17_GEthMacV2_BuffDescAddrPtr is
  initialized(copy table) with the value generated from the configuration.
  Later the global status variable is initialized with this value in init
  function, Hence the variable cannot be defined in the local scope. No side
  effects foreseen by violating this MISRA rule */
static Eth_17_GEthMacV2_BuffDescType * const\
        Eth_17_GEthMacV2_BuffDescAddrPtr[ETH_17_GETHMACV2_MAX_CONTROLLERS] =
{
#ifdef ETH_17_GETHMACV2_CTRL0_CONFIGURED
  &Eth_17_GEthMacV2_BuffDescCtrl0,
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_MAX_CONTROLLERS > 1U)
#ifdef ETH_17_GETHMACV2_CTRL1_CONFIGURED
  &Eth_17_GEthMacV2_BuffDescCtrl1
#else
  NULL_PTR
#endif
#endif
};

/*Array to hold the base of the HIGH and low registers for Dual controllers*/
static volatile Ifx_GETH_MAC_ADDRESS_HIGH* const
          Eth_17_GEthMacV2_HighBaseAddrPtr[ETH_17_GETHMACV2_MAX_CONTROLLERS]=
{
#ifdef ETH_17_GETHMACV2_CTRL0_CONFIGURED
/*Base Address for MAC address register 1- High and Low for GETH*/
&(GETH_MAC_ADDRESS1_HIGH),
#else
  NULL_PTR,
#endif
#if (ETH_17_GETHMACV2_MAX_CONTROLLERS > 1U)
#ifdef ETH_17_GETHMACV2_CTRL1_CONFIGURED
/*Base Address for MAC address register 1- High and Low for GETH*/
&(GETH1_MAC_ADDRESS1_HIGH)
#else
NULL_PTR
#endif
#endif
/* MISRA2012_RULE_19_2_JUSTIFICATION:Union used for register type definition.
   No side effects foreseen by violating this MISRA rule*/
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMacV2_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* Memory Map of the Eth Code */
#define ETH_17_GETHMACV2_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMacV2_MemMap.h"

static uint8 Eth_17_GEthMacV2_lDetCheckMode(const uint8 ServiceId,
            const Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr);

#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
static uint8 Eth_17_GEthMacV2_lDetChkNoInit(const uint8 CtrlIdx,
                                            const uint8 ServiceId);

static uint8 Eth_17_GEthMacV2_lInitDetCheck(
                        const Eth_17_GEthMacV2_ConfigType * const DetConfigPtr,
                        const uint32 CoreId);

static uint8 Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(const uint8 CtrlIdx,
                                                    const uint8 ServiceId);

static uint8 Eth_17_GEthMacV2_lDetChkPointerInvalid(const void * const Ptr,
                                                    const uint8 ServiceId);

static uint8 Eth_17_GEthMacV2_lDetChkNoInitStage1(const uint8 ServiceId);

static uint8 Eth_17_GEthMacV2_lDetChkModeInvalid(const Eth_ModeType CtrlMode);

LOCAL_INLINE uint8 Eth_17_GEthMacV2_lDetChkProvideTxBuffer(
                                        const uint8 CtrlIdx,
                                        const uint8 Priority,
                                        const Eth_BufIdxType* const BufIdxPtr,
                                        uint8* const * const BufPtr,
                                        const uint16* const LenBytePtr);

static uint8 Eth_17_GEthMacV2_lDetChkSetCtrlMode(const uint8 CtrlIdx,
                                                 const Eth_ModeType CtrlMode);

#endif /*ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON*/

static void Eth_17_GEthMacV2_lDemtimeout(const boolean Timeout,
                                         const Dem_EventIdType EthDemAccess);

static void Eth_17_GEthMacV2_lDemReportStatisticsCounterValues(void);

static void Eth_17_GEthMacV2_lDemReportHalfDuplStatCountValues(
             const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr,
             Eth_17_GEthMacV2_CtrlStatusType * const EthLocalCoreStatusPtr);

static void Eth_17_GEthMacV2_lUpdateEthStatisticsCounterValues(void);

static void Eth_17_GEthMacV2_lDemReportAllErrorPass(const
               Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lInitGethController(const
            Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static Std_ReturnType Eth_17_GEthMacV2_lResetGethCore(const
                 Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lDisableGethInterrupt(const
              Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lEnableGethInterrupt(const
             Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lGethCoreInit(
            const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lInitGlobalVar(
                  Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr);

LOCAL_INLINE void Eth_17_GEthMacV2_lPhyIfModeSkewCfg(const
                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static Std_ReturnType Eth_17_GEthMacV2_lResetDma(const uint8 CtrlIdx);

static void Eth_17_GEthMacV2_lResetTxRxStatus(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lMacCoreInit(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lClearAllAddressFilters(const uint8 CtrlIdx);

static void Eth_17_GEthMacV2_lMtlCoreInit(
            const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lDmaCoreInit(
             const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lDmaTxDescriptorInit(const
                   Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lDmaRxDescriptorInit(const
                   Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lStartTxRx(
             const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static Std_ReturnType Eth_17_GEthMacV2_lStopTxRx(
             const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static Std_ReturnType Eth_17_GEthMacV2_lTransmit(
                   const uint8 CtrlIdx,
                   const Eth_BufIdxType BufIdx, const Eth_FrameType FrameType,
                   const boolean TxConfirmation, const uint16 LenByte,
                   const uint8* const PhysAddrPtr);

static void Eth_17_GEthMacV2_lConfirmTxFrames (const uint8 CtrlIdx);

#if (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON)
static void Eth_17_GEthMacV2_lIntConfirmTxFrames(const uint8 CtrlIdx,
                                                 const uint8 Channel);
#endif

static uint8 Eth_17_GEthMacV2_lReceiveFrames(const uint8 CtrlIdx,
                                             const uint8 FifoIdx);

LOCAL_INLINE void Eth_17_GEthMacV2_lSetPhysAddr(const uint8 CtrlIdx,
                                                const uint8* const MacAddrPtr);

LOCAL_INLINE void Eth_17_GEthMacV2_lGetPhysAddr(const uint8 CtrlIdx,
                                                uint8* const MacAddrPtr);

LOCAL_INLINE boolean Eth_17_GEthMacV2_lIsBroadcastAddress(
                                                const uint8* const MacAddrPtr);

LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrTxBufIdx(const uint16 TxBufIdx,
                                                   const uint16 EthTxBufTotal);

LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrRxBufIdx(const uint16 RxBufIdx,
                                                   const uint16 EthRxBufTotal);

static void Eth_17_GEthMacV2_lCheckForCtrlModeChange(const uint8 CtrlIdx,
                Eth_17_GEthMacV2_CtrlStatusType * const EthLocalCoreStatusPtr);

LOCAL_INLINE boolean Eth_17_GEthMacV2_lIsAllZeroAddress(
                                            const uint8* const MacAddrPtr);

static Std_ReturnType Eth_17_GEthMacV2_lAddToFilter(const uint8 CtrlIdx,
                                       const uint8* const MacAddrPtr);

static Std_ReturnType Eth_17_GEthMacV2_lRemoveFromFilter(const uint8 CtrlIdx,
                                            const uint8* const MacAddrPtr);

static uint16 Eth_17_GEthMacV2_lCheckFilterPresent(const uint8 CtrlIdx,
                                            const uint8* const MacAddrPtr);

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
static Std_ReturnType Eth_17_GEthMacV2_lTimerInit(
            const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static boolean Eth_17_GEthMacV2_lTsAdRegTimeout(const uint8 CtrlIdx,
                                                const uint32 WaitTicks);

static boolean Eth_17_GEthMacV2_lTsInitTimeout(const uint8 CtrlIdx,
                                               const uint32 WaitTicks);

#endif /*end of ETH_17_GETHMACV2_GLOBALTIMESUPPORT */

#if((ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON) &&\
    (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON))
static uint8 Eth_17_GEthMacV2_lDetCheckBufIdx(const uint8 CtrlIdx,
                                              const uint8 ServiceId,
                                              const uint16 FifoIdxMap,
                                              const uint16 BufferIdx);
#endif


#if ((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON  ) || \
     (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON  ))
static void Eth_17_GEthMacV2_lCheckForICMPV4Frame(uint8 * const BufferAddrPtr,
                                                const Eth_FrameType FrameType);
#endif

static void Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(const uint32
                                                  EthDelayWaitTime);

static boolean Eth_17_GEthMacV2_lIsNextFrameAvailable(const uint8 CtrlIdx,
                                                      const uint8 FifoIdx);

static Eth_17_GEthMacV2_CtrlStatusType* Eth_17_GEthMacV2_lGetCtrlStatusPtr
                                                        (const uint8 CtrlIdx);

static Eth_17_GEthMacV2_CoreCtrlConfigType* Eth_17_GEthMacV2_lGetCtrlConfigPtr(
                                                         const uint8 CtrlIdx);

static void Eth_17_GEthMacV2_lCfgTxQueue(const
                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

static void Eth_17_GEthMacV2_lCfgRxQueue(const
                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
LOCAL_INLINE Std_ReturnType Eth_17_GEthMacV2_lChkSwtRxFrmParam(
            const uint16 RxActualLen, const uint16 RxModifiedLen,
            const uint8* const EthTypeAddrPtr, const uint8* const BufferPtr);

static BufReq_ReturnType Eth_17_GEthMacV2_lSwtAdaptPrepFrame(
                                             const uint8 CtrlIdx,
                                             const uint8 PrioMapIdx,
                                             Eth_BufIdxType* const BufIdxPtr,
                                             uint8** const BufPtr,
                                             uint16* const LenBytePtr);
#endif /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */

static uint16 Eth_17_GEthMacV2_lReadQElem(const uint16* const QueuePtr,
      uint16* const QFrontPtr, uint16* const QRearPtr, const uint16 QueueSize);

static void Eth_17_GEthMacV2_lAddQElem(const uint16 Element,
                              uint16* const QueuePtr, uint16 * const QFrontPtr,
                              uint16* const QRearPtr, const uint16 QueueSize);

static boolean Eth_17_GEthMacV2_lQEmptySt(const uint16 QFront);

static Std_ReturnType Eth_17_GEthMacV2_lTxQFlush(const
                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr);

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID={F2D87119-724B-457f-A9D4-58E27B080C0C}] **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_Init                              **
**                       (const Eth_17_GEthMacV2_ConfigType* const CfgPtr)    **
**                                                                            **
** Description      : The function initializes the Ethernet Driver and        **
**                    store the access to the configuration                   **
**                    parameters for subsequent API calls.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CfgPtr - Pointer to the implementation specific         **
**                              structure                                     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Eth_17_GEthMacV2_Init(const Eth_17_GEthMacV2_ConfigType* const CfgPtr)
{
  uint32 RegVal;
  uint32 CoreId;
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
  #if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
  #endif
  uint8 ControllerIdx;

  CoreId = Mcal_GetCpuIndex();
  RetValue = E_OK;

  /* [cover parentID={672A41B8-74C5-4f40-BF63-15D813AE17CC}]
  DET is Enabled
  [/cover] */
  #if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  DevError = Eth_17_GEthMacV2_lInitDetCheck(CfgPtr, CoreId);

  /* [cover parentID={1659F0E8-B09E-402b-B722-AB220495EA23}]
  Is error detected?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  #endif /* ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON */
  {
    /* [cover parentID={E28655AF-5A14-4372-B2D6-0AC23F059811}]
     Retrieve the core, controller configuration data and
     controller status of the current core.
     Store Ethernet config set pointer for later use
     [/cover] */
    Eth_17_GEthMacV2_ConfigPtr = CfgPtr;

    /* Get pointer to Core Configuration data */
    EthLocalCoreCfgPtr = Eth_17_GEthMacV2_ConfigPtr->EthCoreAdd[CoreId];

    /* Get pointer to controller Configuration data */
    EthLocalCtrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCtrlPtr;

    /* Get pointer to controller status of current core */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_CtrlStatusPtr[CoreId];

    /* Core Init status is reset to UNINIT state */
    *(Eth_17_GEthMacV2_CoreInitStatusPtr[CoreId]) =
                                      (uint32)ETH_17_GETHMACV2_CORE_UNINIT;

    /* Loop through all controllers allocated to current core.*/
    for(ControllerIdx = 0; ControllerIdx < (EthLocalCoreCfgPtr->
                                  EthMaxControllers); ControllerIdx++)
    {
      /* Initialize Buffer Descriptor pointer for the current controller */
      EthLocalCoreStatusPtr->EthBuffDescPtr = Eth_17_GEthMacV2_BuffDescAddrPtr
                                            [EthLocalCtrlCfgPtr->EthCtrlIdx];

      /* Initialize global variables for current controller */
      Eth_17_GEthMacV2_lInitGlobalVar(EthLocalCoreStatusPtr);

      /* get base address of the controller */
      EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthLocalCtrlCfgPtr->
                                                            EthCtrlIdx];

      /* Enable the clock */
      /* [cover parentID={43F027CA-7D2C-4120-ADD3-80A39BDA4F0C}]
       Enable the GETH MAC Module
       [/cover] */
      ETH_17_GETHMACV2_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG
                    (&(EthCtrlAddPtr->CLC),(uint32)ETH_17_GETHMACV2_MOD_ENABLE);

      RegVal = (uint32)EthCtrlAddPtr->CLC.B.DISS;

      /* [cover parentID={4E2C6F25-8A49-4134-8FA6-01D0FF113A80}]
      GETH MAC Enabled
      [/cover] */
      /* Check if GETH is enabled, if not, report DEM_E_ACCESS error. */
      if(RegVal != (uint32) ETH_17_GETHMACV2_MOD_ENABLE)
      {
        /* [cover parentID={C066D310-87B7-4394-AA1E-D5F9D36E1DD1}]
        Production Error is Enabled
        [/cover] */
        if(EthLocalCtrlCfgPtr->EthDemAccess !=
                                          ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
        {
          /* [cover parentID={E37D759D-8EA1-4f68-9229-46FA567142A7}]
          Report Production Error (Hardware Access failure) as
          DEM_EVENT_STATUS_PREFAILED
          [/cover] */
          /*Production Error should be reported only if Production Error has
          been enabled  */
          (void)Mcal_Wrapper_Dem_SetEventStatus(
                EthLocalCtrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREFAILED);
        }

        RetValue = E_NOT_OK;
        break;
      }
      else
      {
        /* [cover parentID={3276B0AA-7B81-46c3-84A4-C6DBCD83CB66}]
        Select the external PHY interface according to the configured mode and
        also select the alternate inputs to be used in the GPCTL register
        [/cover] */
        ETH_17_GETHMACV2_SFR_INIT_DEINIT_WRITE32(&EthCtrlAddPtr->GPCTL.U,
         (uint32)(((((uint32)EthLocalCtrlCfgPtr->EthCtrlProperties >>
            (uint32)ETH_17_GETHMACV2_PHYINTF_POS) &
            (uint32)ETH_17_GETHMACV2_PHYINTF_MSK)
            << (uint32)ETH_17_GETHMACV2_GPTCL_PHY_POS) |
            (uint32)EthLocalCtrlCfgPtr->EthGpctlRegVal));

        /*Production Error should be reported only if Production Error has
        been enabled  */
        /* [cover parentID={3A5F3BC9-6AEA-4dfe-82D2-A5A133B4FFB8}]
        Production Error is Enabled
        [/cover] */
        if(EthLocalCtrlCfgPtr->EthDemAccess !=
                                          ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
        {
          /* [cover parentID={35DC2344-842F-41cc-B9F4-E7A05B8EA7C6}]
             Report Production Error (Hardware Access failure) as
             DEM_EVENT_STATUS_PREPASSED
             [/cover] */
          (void)Mcal_Wrapper_Dem_SetEventStatus(
                EthLocalCtrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
        }
      }

      EthLocalCtrlCfgPtr++;
      EthLocalCoreStatusPtr++;
    }

    /* Set Core status to INITIALIZED if no Production Error is reported */
    /* [cover parentID={6B843A8B-CE4E-4ea9-B5AC-412BCF3FAB8F}]
    Any Production error reported?
    [/cover] */
    if(RetValue == E_OK)
    {
      /* [cover parentID={BBC89145-A067-48ff-9669-7CF002E4C94E}]
      Set Core status to ETH_STATE_INIT
      [/cover] */
      *(Eth_17_GEthMacV2_CoreInitStatusPtr[CoreId]) =
                                      (uint32)ETH_17_GETHMACV2_CORE_INIT;
    }
  }
}

/*******************************************************************************
** Traceability    : [cover parentID={3833FED9-F472-4f61-BE24-AA1A9AC22116}]  **
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
** Return value     : E_OK     - Successfully set the requested mode          **
**                    E_NOT_OK - Controller mode could not be changed         **
**                                                                            **
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_SetControllerMode(const uint8 CtrlIdx,
                                                  const Eth_ModeType CtrlMode)
{
  Eth_ModeType CurrentMode;
  uint32 RegVal;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;

  /* [cover parentID={6ADEA943-F87D-476e-8312-910F21AC11C2}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  RetValue = E_OK;

  /* Check for presence of any development error */
  DevError = Eth_17_GEthMacV2_lDetChkSetCtrlMode(CtrlIdx, CtrlMode);

  /* [cover parentID={EA534940-530A-49f6-B4C2-B1A7706CA5B3}]
  Any DET error occurred ?
  [/cover] */
  if(DevError != ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={7841D471-DB71-4e04-B0E6-6891EA8C2A65}]
    [/cover] */
    RetValue = E_NOT_OK;
  }
  else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* Get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthLocalCtrlCfgPtr->
                                                          EthCtrlIdx];

    /*Check if GETH IP is enabled*/
    RegVal = (uint32) EthCtrlAddPtr->CLC.B.DISS;

    /* [cover parentID={800129CE-FC1A-4cc7-AF7C-EA867A5F17EC}]
    GETH MAC is enabled
    [/cover] */
    /* DEM_E_ACCESS error detection */
    if(RegVal != (uint32) ETH_17_GETHMACV2_MOD_ENABLE)
    {
      /* [cover parentID={ACB60798-0B0D-4aa8-A189-3BB2EC309160}]
      [/cover] */
      /* Production error should be reported only if Production error has been
      enabled. */
      if(EthLocalCtrlCfgPtr->EthDemAccess !=
                             ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={A6EEDF4F-AE25-4b70-A689-CBFE52F412B4}]
        Report Production error (Hardware Access failure) as
        DEM_EVENT_STATUS_PREFAILED
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(EthLocalCtrlCfgPtr->EthDemAccess,
                                      DEM_EVENT_STATUS_PREFAILED);
      }
      RetValue = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={8ED062B5-7D57-43d2-BCD5-9081A55525E4}]
      Init Stage-1 is done and MII interface Configuration status is NOT
      INITIALIZED (If Controller specific initialization not done)
      [/cover] */
      if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CtrlConfigStatus
                                 == ETH_17_GETHMACV2_CTRL_NOT_INITIALIZED)
      {
        /*Complete controller Initialization (Stage-2) */
        /*Info: If controller Initialization(Init Stage-2) completed
        successfully, then CtrlConfigStatus will be set as
        ETH_17_GETHMACV2_CTRL_INITIALIZED from called function*/
        /*Info:Any error during Init Stage-2, will cause to raise
         Hardware Access failure Production error from called function*/
        /* [cover parentID={F2000315-3626-48c4-8E8F-3F3DDCEE2458}]
        [/cover] */
        Eth_17_GEthMacV2_lInitGethController(EthLocalCtrlCfgPtr);
      }
      /* [cover parentID={9D9F13F7-8825-4193-8C2C-34604EE908EB}]
      If Controller is initialized
      [/cover] */
      /* Try operating to change controller mode( ACTIVE/DOWN) only if
      CtrlConfigStatus is ETH_17_GETHMACV2_CTRL_INITIALIZED*/
      if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CtrlConfigStatus ==
                                        ETH_17_GETHMACV2_CTRL_INITIALIZED)
      {
        /* [cover parentID={42FBEA70-8F90-4680-B301-EB1A69F932F3}]
        Requested Controller Mode
        [/cover] */
        /* If Requested mode is to Set to ACTIVE. */
        if(CtrlMode == ETH_MODE_ACTIVE)
        {
          /* Get current mode, ACTIVE or DOWN */
          CurrentMode = EthLocalCoreStatusPtr->
                          EthRunTimeOpertnData.EthControllerMode;

          /* If current mode is DOWN. */
          /* [cover parentID={DB220DBB-C417-42c2-817F-EF93D17884D1}]
          Check Current Mode
          [/cover] */
          if(CurrentMode == ETH_MODE_DOWN)
          {
            /* Enable interrupt before setting controller to Active mode */
            Eth_17_GEthMacV2_lEnableGethInterrupt(EthLocalCtrlCfgPtr);

            /* [cover parentID={03548C88-DF44-4501-BE93-BF81B9C380A4}]
            Start Tx and Rx in MAC and DMA core
            [/cover] */
            Eth_17_GEthMacV2_lStartTxRx(EthLocalCtrlCfgPtr);

            EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode =
                                                               ETH_MODE_ACTIVE;

            /* [cover parentID={ED0C49EF-D03E-4a82-8410-BF0E705D6994}]
            [/cover] */
            /* Production error should be reported only if Production error
            has been enabled. */
            if(EthLocalCtrlCfgPtr->EthDemAccess !=
                                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
            {
              /* [cover parentID={8AB1809C-B3EF-4cfa-98F8-8827BCE80087}]
              Report Production Error (Hardware Access failure) as
              DEM_EVENT_STATUS_PREPASSED
              [/cover] */
              (void)Mcal_Wrapper_Dem_SetEventStatus(
                  EthLocalCtrlCfgPtr->EthDemAccess,DEM_EVENT_STATUS_PREPASSED);
            }
            /* [cover parentID={F4CF564B-C3F9-44cd-B80D-E8896E5E7334}]
            Set RetValue = E_OK
            [/cover] */
            RetValue = E_OK;
          }
          else
          {
            /* Controller is already in ACTIVE State */
            if (EthLocalCtrlCfgPtr->EthDemAccess !=
                                   ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
            {
              /* [cover parentID={8AB1809C-B3EF-4cfa-98F8-8827BCE80087}]
              Report Production error (Hardware Access failure) as
              DEM_EVENT_STATUS_PREPASSED
              [/cover] */
              /* Production error should be reported only if Production error
              has been enabled. */
              (void)Mcal_Wrapper_Dem_SetEventStatus(
                EthLocalCtrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
            }
            /* [cover parentID={147BCB88-BC5C-40e0-8778-380EDAEF81F8}]
            Set RetValue = E_OK ( controller is already ACTIVE)
            [/cover] */
            RetValue = E_OK;
          }
        }
        else if(CtrlMode == ETH_MODE_DOWN)
        {
          /* Requested mode is set to DOWN. */
          /* [cover parentID={8A669E8F-A98E-4f33-9445-BC0B62528E29}]
          Stop Tx and Rx in MAC and DMA
          [/cover] */
          RetValue = Eth_17_GEthMacV2_lStopTxRx(EthLocalCtrlCfgPtr);

          /* [cover parentID={F50FF70F-062B-4d79-993D-AAECAC8B4150}]
          Any error while stopping Tx and Rx operation?
          [/cover] */
          if (RetValue == E_OK)
          {
            /* [cover parentID={B19ABB25-4541-4608-9AB5-44BAB98FA185}]
            RetValue is E_OK, when control reaches here
            [/cover] */
            /* Set the controller Mode to DOWN */
            EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode =
                                                                ETH_MODE_DOWN;

            /* [cover parentID={2A9A06E2-2392-4f7a-9149-D3291DB7E5DE}]
            Reset all Tx and Rx status and Buffers
            [/cover] */
            /* Reset Tx/ Rx status and Buffers */
            Eth_17_GEthMacV2_lResetTxRxStatus(EthLocalCtrlCfgPtr);

            /* Production Error should be reported only if Production error
            has been enabled. */
            /* [cover parentID={A6F8968B-AE5B-487b-A6AC-A9426BFB01CB}]
            [/cover] */
            if(EthLocalCtrlCfgPtr->EthDemAccess !=
                                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
            {
              /* [cover parentID={7123FD12-0107-428f-8D5D-380DCECDC6C4}]
              Report Production error (Hardware Access failure) as
              DEM_EVENT_STATUS_PREPASSED
              [/cover] */
              (void)Mcal_Wrapper_Dem_SetEventStatus(
                 EthLocalCtrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
            }
          }
        }
        else
        {
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_OFF)
          /* Requested mode is unknown (in parameter CtrlMode) */
          /* [cover parentID={7841D471-DB71-4e04-B0E6-6891EA8C2A65}]
          [/cover] */
          RetValue = E_NOT_OK;
#endif /*ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_OFF*/
        }

        /* [cover parentID={A2B784D3-7732-4e8a-91D7-72EA88D73F6C}]
        Check Controller mode and if so, indicate the same
        (Inform application about State change)
        [/cover] */
        Eth_17_GEthMacV2_lCheckForCtrlModeChange(CtrlIdx,
                                                 EthLocalCoreStatusPtr);
      }
      else
      {
        /* Controller is not initialized */
        /* [cover parentID={7841D471-DB71-4e04-B0E6-6891EA8C2A65}]
        [/cover] */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={19277E1C-6BDB-4d80-985B-15D64C4D111C}]  **
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
BufReq_ReturnType Eth_17_GEthMacV2_ProvideTxBuffer(const uint8 CtrlIdx,
                                             const uint8 Priority,
                                             Eth_BufIdxType* const BufIdxPtr,
                                             uint8** const BufPtr,
                                             uint16* const LenBytePtr)
{
  /* [cover parentID={67C9F5C4-7083-4ab8-854B-D962CCDBC802}]
  In Default, Set BufferStatus to BUFREQ_E_BUSY(To Return)
  [/cover] */
  BufReq_ReturnType BufferStatus = BUFREQ_E_BUSY;
  Eth_17_GEthMacV2_TxBuffTableType *TxBuffTablePtr;
  Eth_17_GEthMacV2_TxDescBufMapStType *CnfrmTxDescTablePtr;
  uint32 DescStatus;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_BuffDescType *EthLocalBuffDescPtr;
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_OFF)
  const volatile uint8 *TxBuffBasePtr;
  uint16 TxBufLengthAligned;
  uint16 CurrTxBufferIdx;
#endif
  uint16 TxBufLengthConfig;
  uint16 TxDescCnfrmIdx;
  uint16 BufMapIdx;
  uint8 PrioMapIdx;
  uint8 FifoIdx;
  boolean EmptyQSt;

  /* [cover parentID={511554D3-78A1-4d69-A89B-C54E7D272FE2}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={939180DA-BCED-4612-A1A7-7775EC995C53}]
  Check for presence of any development error
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkProvideTxBuffer(CtrlIdx, Priority,
                                            BufIdxPtr, BufPtr, LenBytePtr);

  /* [cover parentID={ACFC4575-6C19-4d00-8F2D-FFA481038422}]
  Any DET error occurred ?
  [/cover] */
  if(DevError != ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={42F19141-DFD4-4e9e-81DA-18E4BC185C95}]
    [/cover] */
    BufferStatus = BUFREQ_E_NOT_OK;
  }
  else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    EthLocalBuffDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr;

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Extract the priority related values from configuration */
    PrioMapIdx = EthLocalCtrlCfgPtr->EthTxPrioFifoMapPtr[Priority];

    FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioMapIdx].TxFifoIdx;

    /* [cover parentID={685D99A7-831D-4f54-AFC0-E712F97A6B4D}]
    [/cover] */
    /* [cover parentID={A7328EBC-2A5C-4724-98B5-0CF006718B04}]
    [/cover] */
    /* [cover parentID={49B7D4EC-38A5-492a-8B3E-9E237C75B6C6}]
    Enter the critical section
    [/cover] */
    SchM_Enter_Eth_17_GEthMacV2_TxDescData();

    TxDescCnfrmIdx = EthLocalBuffDescPtr->
                      EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx;

    CnfrmTxDescTablePtr= &(EthLocalBuffDescPtr->EthTxDescBufMapStPtr[FifoIdx]
                                                          [TxDescCnfrmIdx]);

    /* [cover parentID={FA38E9C2-23CD-441f-852E-CA1D90350375}]
    If frame transmission was initiated and Tx confirmation was not
    requested
    [/cover] */
    if ((CnfrmTxDescTablePtr->TxConfirmReq == ETH_17_GETHMACV2_DISABLE) &&
        (CnfrmTxDescTablePtr->FrameTxInitiated == ETH_17_GETHMACV2_ENABLE))
    {
      BufMapIdx = EthLocalBuffDescPtr->EthTxDescBufMapStPtr[FifoIdx]
                                    [TxDescCnfrmIdx].TxDescBufMapIdx;

      /* Get TxBuffTable index that is mapped to the current Tx Desc index */
      TxBuffTablePtr = &(EthLocalBuffDescPtr->EthTxBuffTablePtr
                                               [FifoIdx][BufMapIdx]);

      /* [cover parentID={51DB1F58-BB1E-45c5-BDE6-48497461CE93}]
      Check if buffer status is USED_TXINITIATED
      [/cover] */
      if(TxBuffTablePtr->BuffStatus == ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED)
      {
        DescStatus = EthLocalBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
                                            [TxDescCnfrmIdx].TDES3;

        /* [cover parentID={227952C7-1B89-49f8-AD6A-2AAB167C4B99}]
        Check if Buffer is released by DMA by checking OWN bit
        [/cover] */
        if((DescStatus & ((uint32)ETH_17_GETHMACV2_DMA_TX_DESC_OWN_SET))
                                            == ETH_17_GETHMACV2_DESC_RELEASED)
        {
          /* buffer has been transmitted, release buffer now. */
          /* [cover parentID={232F9EC7-B8B8-4168-BC1E-9F75E6312A2D}]
          Corresponding to current "TxBufferTable" pointer, Mark Buffer
          status as NOT USED and Frame transmission initiated as NO
          [/cover] */
          CnfrmTxDescTablePtr->FrameTxInitiated = ETH_17_GETHMACV2_DISABLE;

          TxBuffTablePtr->BuffStatus = ETH_17_GETHMACV2_BUFFER_NOTUSED;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
          TxBuffTablePtr->TimeStampEnable = ETH_17_GETHMACV2_DISABLE;
#endif

          /* [cover parentID={A6886311-A7AC-4ab7-9F80-76B2508FFAC2}]
          Add the buffer index into the queue indicating availability
          [/cover] */
          Eth_17_GEthMacV2_lAddQElem(BufMapIdx, EthLocalBuffDescPtr->
            EthTxBuffQueuePtr[FifoIdx], &(EthLocalBuffDescPtr->
            EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront), &(EthLocalBuffDescPtr->
            EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear), EthLocalCtrlCfgPtr->
            EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers);

          /* Implicitly confirmed, therefore move to next buffer */
          /* [cover parentID={18B33928-0FC9-4d01-9A3C-C208ED20E3C7}]
          [/cover] */
          EthLocalBuffDescPtr->EthRunTmTxChnlDataPtr
              [FifoIdx].CnfrmTxDmaDescIdx =
              Eth_17_GEthMacV2_lIncrTxBufIdx(EthLocalBuffDescPtr->
              EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx,
              EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers);
        }
      }
    }

    /* [cover parentID={6562D6B9-1C5C-40a8-A72C-4444A7809203}]
    Exit the critical section
    [/cover] */
    SchM_Exit_Eth_17_GEthMacV2_TxDescData();

    /* Get configured buffer length */
    TxBufLengthConfig = EthLocalCtrlCfgPtr->
                         EthTxFifoCfgPtr[PrioMapIdx].TxBufferSize;

    /* [cover parentID={F2F0AE60-8ABB-4019-8C6B-10989CD9C71D}]
    Requested Length of Buffer Size is <= Allocated Tx Buffer
    Size - Frame Header and  CRC
    [/cover] */
    /* The requested buffer size should not exceed Configured
    Tx Buffer - ETH total Frame Header.
    ETH total Frame Header = Header(14) + Frame CRC(4)
    That is reserved size (header and frame CRC) is 18 bytes */
    if ((uint16)(*LenBytePtr) > (TxBufLengthConfig -
                    ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                                 ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH))))
    {
      /* [cover parentID={3B6828B3-9250-4fbe-96F6-0CBDDD361B91}]
      Fill output parameter 'LenBytePtr' as
      Allocated Tx Buffer Size - Frame Header and  CRC)
      [/cover] */
      *LenBytePtr = TxBufLengthConfig -
                      ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                        ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH));

      /* [cover parentID={BF6B42BC-8298-4a25-8422-4AA87F547ADD}]
      BufferStatus = BUFREQ_E_OVFL ( To Return)- That is, requested buffer
      too large
      [/cover] */
      BufferStatus = BUFREQ_E_OVFL;
    }
    else
    {
      /* [cover parentID={892531F4-B781-47b7-92C7-4E2CF5FEFAE7}]
      [/cover] */
      /* [cover parentID={E2FA4513-13EE-4270-861B-BC817BD87EC9}]
      [/cover] */
      /* [cover parentID={58F69729-1B7C-4d60-8BFA-940AD25E4465}]
      Enter the critical section
      [/cover] */
      SchM_Enter_Eth_17_GEthMacV2_TxBufIdx();

      /* [cover parentID={4F57C011-005E-4ae9-A603-DF5521D45E47}]
      Check whether the Queue is not empty
      [/cover] */
      EmptyQSt = Eth_17_GEthMacV2_lQEmptySt(EthLocalBuffDescPtr->
                          EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront);

      if (FALSE == EmptyQSt)
      {
        /* [cover parentID={6DF1CC18-4661-4dfc-85FB-546DAC276BFB}]
        Switch Management support is enabled
        [/cover] */
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
        /* Invoke and process the EthSwt APIs for management support*/
        /* [cover parentID={05FC5C09-E574-4221-9715-1C73E1F7A3E5}]
        Switch driver frame preparation
        [/cover] */
        BufferStatus = Eth_17_GEthMacV2_lSwtAdaptPrepFrame(CtrlIdx, PrioMapIdx,
                                                BufIdxPtr, BufPtr, LenBytePtr);

        /* [cover parentID={E7AA6355-A5C9-4df4-A4A9-0D3954F0358D}]
        Exit the critical section
        [/cover] */
        SchM_Exit_Eth_17_GEthMacV2_TxBufIdx();
#else
        /* [cover parentID={63F70CB4-A51F-4799-949D-0503E7EFAB72}]
        Get the buffer index from the queue
        [/cover] */
        CurrTxBufferIdx = Eth_17_GEthMacV2_lReadQElem(EthLocalBuffDescPtr->
            EthTxBuffQueuePtr[FifoIdx], &EthLocalBuffDescPtr->
            EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront, &EthLocalBuffDescPtr->
            EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear, EthLocalCtrlCfgPtr->
                EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers);

        /* [cover parentID={7AD8D02A-6BFE-4e27-BDC5-A9808AFE16E0}]
        Exit the critical Section
        [/cover] */
        SchM_Exit_Eth_17_GEthMacV2_TxBufIdx();

        /* Provide Buffer index and buffer pointer to application
           Set buffer used, TimeStamp not enabled, store the length requested */
        *BufIdxPtr = ((uint32)PrioMapIdx << ETH_17_GETHMACV2_FIFOIDX_POS) |
                                                  (CurrTxBufferIdx);

        /* [cover parentID={D84E0EE8-073A-4ea8-B987-0D811CF67A78}]
        Corresponding to current "TxBufferTable" pointer, Mark Buffer status as
        USED, Frame transmission initiated as NO and Tx confirmation requested
        as NO. Store requested buffer length to check during Transmit API
        [/cover] */
        /* Get current TxBuffTable index to check buffer status */
        TxBuffTablePtr= &(EthLocalBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                                                          [CurrTxBufferIdx]);

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        TxBuffTablePtr->TimeStampEnable = ETH_17_GETHMACV2_DISABLE;
#endif

        TxBuffTablePtr->BuffLengthReqstd = *LenBytePtr;

        TxBuffBasePtr = &(EthLocalBuffDescPtr->EthTxBufferPtr[FifoIdx][0U]);

        TxBufLengthAligned = EthLocalCtrlCfgPtr->
                                EthTxFifoCfgPtr[PrioMapIdx].TxBufferAlignSize;

        /* [cover parentID={6BF63977-6277-4c30-AE82-0B03D1300EC2}]
        Provide Buffer Index and Buffer Pointer to Application
        (Fill output parameters BufIdxPtr with Current Tx index and BufPtr with
        buffer address from Current Tx Descriptor )
        [/cover] */
        /* Ethernet Packet format is,
        MAC Destination Address(6) + MAC Source Address(6) + Type/Length(2)+
        Payload/Data(46-1500) + FCS(4)*/
        /* Upper layer only fills the data(Payload),Frame Header has to be
        filled by Eth_Transmit function so BufPtr points Payload Pointer*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
        pointer type is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
        expression is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
        is performed to access the buffer address from DMA descriptor.
        This is the intended design and valid as per DMA hardware design.
        There are no side effects seen by violating this rule.*/
        *BufPtr = (uint8*)((uint32)TxBuffBasePtr +\
                          ((uint32)CurrTxBufferIdx * TxBufLengthAligned)\
                          + (uint32)ETH_17_GETHMACV2_FRAMEHEADER_LENGTH);

        TxBuffTablePtr->BuffStatus = ETH_17_GETHMACV2_BUFFER_USED;

        /* [cover parentID={F424B08D-5EDB-45be-A3CF-B7F83FB1E9A7}]
        BufferStatus = BUFREQ_OK ( To Return)
        [/cover] */
        BufferStatus = BUFREQ_OK;
#endif
      }
      else
      {
        /* Exit the critical section */
        SchM_Exit_Eth_17_GEthMacV2_TxBufIdx();
      }
    }
  }

  return BufferStatus;
}

/*******************************************************************************
** Traceability    : [cover parentID={5DD9C705-ADCC-4268-AFD1-DBC07170B32C}]  **
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
Std_ReturnType Eth_17_GEthMacV2_GetControllerMode(const uint8 CtrlIdx,
                                               Eth_ModeType* const CtrlModePtr)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Std_ReturnType RetValue;

  /* [cover parentID={597AA864-3BA0-41b1-BA01-D33E9117481F}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={DB32F9FF-BA7C-4d74-9521-C0DFE5189B38}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                    ETH_17_GETHMACV2_SID_GETCONTROLLERMODE);

  /* [cover parentID={6D9DB562-C863-4a0a-BFE7-5A5158D9CC99}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMACV2_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={E2882417-E554-40b4-B22E-6143CB42F0F1}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                            CtrlIdx, ETH_17_GETHMACV2_SID_GETCONTROLLERMODE);
  }
  /* ETH_17_GETHMACV2_E_UNINIT */
  /* [cover parentID={CE02486C-054B-44a6-BD43-A760CEC58BE9}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={F7EA1D91-4712-441a-8C47-5FD49104B72D}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                            ETH_17_GETHMACV2_SID_GETCONTROLLERMODE);
  }
  /* [cover parentID={0A63029F-BD93-4aeb-9381-2DA6A9536F70}]
  Is controller initialized ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={CE6DD9E2-A832-47ad-AD9A-D720443194B5}]
    Validate Controller Mode Pointer
    [/cover] */
    /*  ETH_17_GETHMACV2_E_PARAM_POINTER */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(
                          CtrlModePtr, ETH_17_GETHMACV2_SID_GETCONTROLLERMODE);
  }
  /* [cover parentID={1773F3E3-3592-4404-ABE8-3DCE334FA099}]
  Valid Controller Mode Pointer
  [/cover] */
  if(DevError != ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={9C156E09-4247-4d88-9A3D-0CF100D9BFEA}]
    Set Return Value = E_NOT_OK
    [/cover] */
    RetValue = E_NOT_OK;
  }
  else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={FF5725FE-DE43-4d66-862D-43AB3AAB97F4}]
    Get current controller mode and store it in Controller Mode pointer
    parameter
    [/cover] */
    *CtrlModePtr = EthLocalCoreStatusPtr->
                        EthRunTimeOpertnData.EthControllerMode;

    /* [cover parentID={8946DFC5-E80F-4491-BB0F-40F41C9BC48B}]
    Set Return Value = E_OK
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={E66B1573-F50C-4eb2-9F90-504A0D16C4E4}]  **
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
** Reentrancy       : Non -Reentrant                                          **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (out) : Physical source address (MAC address) in network byte   **
**                    order.                                                  **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Eth_17_GEthMacV2_GetPhysAddr(const uint8 CtrlIdx, uint8* const PhysAddrPtr)
{
  /* [cover parentID={00D52A11-9D4D-4a27-BD5B-C6B9A33FEC0A}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={39D90178-4700-4dfd-B047-102862E3ED6D}]
  Validate Physical Address Pointer parameter
  [/cover] */
  /* ETH_17_GETHMACV2_E_PARAM_POINTER */
  DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(
                            PhysAddrPtr, ETH_17_GETHMACV2_SID_GETPHYADDRESS);

  /* [cover parentID={798830FB-B09B-4b2f-8D1C-38E645CA26C8}]
  Valid Physical Address Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if Eth_17_GEthMacV2_Init is successful */
    /* [cover parentID={981D6214-E9E3-4482-817C-1C98D99E072E}]
    Check Driver is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                    ETH_17_GETHMACV2_SID_GETPHYADDRESS);
  }
  /* [cover parentID={8E4098CD-641D-47f3-B3AB-6001E13C46CA}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMACV2_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={D3665E14-66A7-4583-AB5B-6FC616FD1F11}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                CtrlIdx, ETH_17_GETHMACV2_SID_GETPHYADDRESS);
  }
  /* [cover parentID={74340F2C-F2BE-46a8-98B3-4340F1B03D76}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={C9505D57-62A2-4481-AFB1-70868DCD961C}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETPHYADDRESS);
  }
  /* [cover parentID={8F0A5F63-1045-4cad-B395-13C3DDA8E55F}]
  If controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* [cover parentID={EB764153-0DBF-4d07-9C58-C4068D7C44A3}]
    Get the Controller Physical source Address (MAC address) and fill
    in physical address pointer parameter
    [/cover] */
    Eth_17_GEthMacV2_lGetPhysAddr(CtrlIdx, PhysAddrPtr);
  }
}

#if (ETH_17_GETHMACV2_ENA_MII_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={2D03C5C6-9FD4-48f2-B9D4-08E39A5B8B0B}]  **
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
** Return value     : E_OK     - Service Accepted                             **
**                    E_NOT_OK - Service denied / error detected              **
**                                                                            **
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_WriteMii(const uint8 CtrlIdx,
                const uint8 TrcvIdx, const uint8 RegIdx, const uint16 RegVal)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint32 AddressRegVal;
  uint32 GmiiBusyBitVal;
  uint32 GmiiBusyBitWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif
  boolean IsTimeExpired;

  /* [cover parentID={A60A34CA-299A-4a8e-87D9-0FFF55F64F09}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* [cover parentID={73002AE2-C32B-4a3f-A05E-D8DCCDEBD569}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={CE3ED190-6EA7-4382-838C-B4971D1DD86C}]
  Check Eth_Init is successfully executed before
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                              (ETH_17_GETHMACV2_SID_WRITEMII);

  /* [cover parentID={E1D1EF14-7341-4f26-A3B1-699E36C8F2F3}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={A64DC749-CC81-499c-9C6F-B0595C3346A7}]
    Validate Controller Index
    [/cover] */
    /*  ETH_17_GETHMACV2_E_INV_CTRL_IDX */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(CtrlIdx,
                          ETH_17_GETHMACV2_SID_WRITEMII);
  }
  /* [cover parentID={14F34BC2-D95E-486e-A05B-FC094CA35502}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Update 16-bit data value which is to be written to the PHY
       in upcoming write operation */
    EthCtrlAddPtr->MAC_MDIO_DATA.U = (uint32)RegVal;

    /* [cover parentID={A7516CEA-6F20-48ff-AD86-D30A3BCF1D52}]
    Update MDIO Address Register for Write Operation ( Update MDIO address
    register-with Transceiver Index, with Register Index and as WRITE COMMAND)
    [/cover] */
    AddressRegVal = (uint32)
     ((((uint32)TrcvIdx & (uint32)IFX_GETH_MAC_MDIO_ADDRESS_PA_MSK) <<
                               (uint32)IFX_GETH_MAC_MDIO_ADDRESS_PA_OFF) |
     (((uint32)RegIdx & (uint32)IFX_GETH_MAC_MDIO_ADDRESS_RDA_MSK) <<
                             (uint32)IFX_GETH_MAC_MDIO_ADDRESS_RDA_OFF) |
     ((uint32)((uint32)(EthLocalCtrlCfgPtr->EthMdcRegVal) <<
                                     IFX_GETH_MAC_MDIO_ADDRESS_CR_OFF)) |
     (uint32)ETH_17_GETHMACV2_WRITECOMMAND |
     (uint32) ETH_17_GETHMACV2_GMIIBUSYSET);

    EthCtrlAddPtr->MAC_MDIO_ADDRESS.U = AddressRegVal;

    /* Wait until Write is completed */
    /* Get STM timer current resolution and calculate number of ticks to wait*/
    DelayTickResolution = Mcal_DelayTickResolution();

    GmiiBusyBitWaitTicks  =
                     (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT / DelayTickResolution);

    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    if(GmiiBusyBitWaitTicks == 0U)
    {
      GmiiBusyBitWaitTicks++;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    IsTimeExpired = FALSE;

    do
    {
      GmiiBusyBitVal = (uint32)EthCtrlAddPtr->MAC_MDIO_ADDRESS.B.GB;

      /* Check wait time is reached at maximum timeout configured*/
      if((((uint32)((CurrSTMTick - BaseSTMTick) &
             ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= GmiiBusyBitWaitTicks) &&
           (GmiiBusyBitVal == (uint32)ETH_17_GETHMACV2_BUSY_ST))
      {
        /*Timeout Happened and write is not completed yet*/
        IsTimeExpired = TRUE;
      }

      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();

    }while((GmiiBusyBitVal == (uint32)ETH_17_GETHMACV2_BUSY_ST) &&
           (IsTimeExpired == FALSE));

    /*Check Timeout error in case of Hardware issue*/
    /* [cover parentID={02FE1D08-24C2-4ef9-A3BA-436E05B88D5F}]
    Timeout Elapsed
    [/cover] */
    if(IsTimeExpired == FALSE)
    {
      /* [cover parentID={247F4197-E9D3-4adc-9114-9E9203DBD8E7}]
      Indicate Write confirmation to Ethernet transceiver driver
      [/cover] */
      EthTrcv_WriteMiiIndication(CtrlIdx, TrcvIdx, RegIdx);

      /* [cover parentID={BF4D56F2-9876-40b3-9DE0-9817573729D0}]
      [/cover] */
      RetValue = E_OK;
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={FB6399A9-548D-4b52-96C7-B2D3D98435CC}]  **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_ReadMii(                **
**                                   const uint8 CtrlIdx,                     **
**                                   const uint8 TrcvIdx, const uint8 RegIdx, **
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
** Parameters (out) : *RegVal - Filled with the register content of the       **
**                              indexed register                              **
**                                                                            **
** Return value     : E_OK     - Service Accepted                             **
**                    E_NOT_OK - Service denied / error detected              **
**                                                                            **
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_ReadMii(const uint8 CtrlIdx,
                                        const uint8 TrcvIdx,
                                        const uint8 RegIdx,
                                        uint16* const RegValPtr)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint32 AddressRegVal;
  uint32 GmiiBusyBitVal;
  uint32 GmiiBusyBitWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif
  boolean IsTimeExpired;

  /* [cover parentID={7DD107BE-724B-48a2-AE24-01B8F318D383}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* [cover parentID={FB55010C-7123-4f53-99BD-7A5A6F40D1A9}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={75B15877-A179-43c3-9600-9A235DFC171A}]
  Check if driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                   ETH_17_GETHMACV2_SID_READMII);

  /* [cover parentID={53CB3E9D-F5D7-451e-A1F5-271ED55CB33E}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={5954E3C2-DA5B-4b78-ABEE-B1FFDA454B7C}]
    Validate Controller Index
    [/cover] */
    /*  ETH_17_GETHMACV2_E_INV_CTRL_IDX */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(CtrlIdx,
                                              ETH_17_GETHMACV2_SID_READMII);
  }
  /* [cover parentID={14FEBB7F-102B-4943-80B1-D18CABEC4CDE}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={EE0524AC-FF4E-4385-953F-C8FF914E24BC}]
    Validate Register Value Pointer
    [/cover] */
    /* ETH_17_GETHMACV2_E_PARAM_POINTER. */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(RegValPtr,
                                              ETH_17_GETHMACV2_SID_READMII);
  }
  /* [cover parentID={C2FD8170-F068-4f08-A62E-82A92A5695DD}]
  Valid Register Value Pointer
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Update MDIO Address register for read operation */
    AddressRegVal = (uint32)
      ((((uint32)TrcvIdx & (uint32)IFX_GETH_MAC_MDIO_ADDRESS_PA_MSK) <<
                               (uint32)IFX_GETH_MAC_MDIO_ADDRESS_PA_OFF) |
      (((uint32)RegIdx & (uint32)IFX_GETH_MAC_MDIO_ADDRESS_RDA_MSK) <<
                               (uint32)IFX_GETH_MAC_MDIO_ADDRESS_RDA_OFF) |
      ((uint32)((uint32)(EthLocalCtrlCfgPtr->EthMdcRegVal) <<
                                       IFX_GETH_MAC_MDIO_ADDRESS_CR_OFF)) |
      (uint32)ETH_17_GETHMACV2_READCOMMAND |
      (uint32)ETH_17_GETHMACV2_GMIIBUSYSET);

    EthCtrlAddPtr->MAC_MDIO_ADDRESS.U = (uint32)AddressRegVal;

    /* [cover parentID={8B62223D-4349-41b3-9B3F-E9899608CDA0}]
    Wait until Read Operation Completed (By polling GMII Busy bit)
    or Timeout elapsed
    [/cover] */
    /* Get STM timer current resolution and calculate number of ticks to wait*/
    DelayTickResolution = Mcal_DelayTickResolution();
    GmiiBusyBitWaitTicks  =
                   (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT / DelayTickResolution);

    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    if(GmiiBusyBitWaitTicks == 0U)
    {
      GmiiBusyBitWaitTicks++;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    IsTimeExpired = FALSE;

    do
    {
      GmiiBusyBitVal = (uint32)EthCtrlAddPtr->MAC_MDIO_ADDRESS.B.GB;

      /* Check wait time is reached at maximum timeout configured */
      if((((uint32)((CurrSTMTick - BaseSTMTick) &
             ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= GmiiBusyBitWaitTicks) &&
         (GmiiBusyBitVal == (uint32)ETH_17_GETHMACV2_BUSY_ST))
      {
        /* Timeout Happened and read is not completed yet */
        IsTimeExpired = TRUE;
      }

      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();

    }while((GmiiBusyBitVal == (uint32)ETH_17_GETHMACV2_BUSY_ST) &&
           (IsTimeExpired == FALSE));

    /*Check if Timeout error happened in case of Hardware issue*/
    /* [cover parentID={FA527014-CBBC-43d3-80E9-32E156CABED4}]
    Timeout Elapsed
    [/cover] */
    if(IsTimeExpired == FALSE)
    {
      /* [cover parentID={80894A67-BC13-4a95-B123-C327B41CAC98}]
      Read data from MDIO Data Register to and copy to Register Value Pointer
      (function output parameter)
      [/cover] */
      /*Read is successful. Read register value and store to out parameter */
      /* After Successful read from PHY, Data available at WORD Register*/
      *RegValPtr = (uint16)(EthCtrlAddPtr->MAC_MDIO_DATA.B.GD);

      /* [cover parentID={84F6D221-DD96-47c6-85CF-F78F904598EE}]
      Indicate/Provide read register value to Ethernet transceiver driver
      [/cover] */
      EthTrcv_ReadMiiIndication(CtrlIdx,TrcvIdx, RegIdx,(uint8)*RegValPtr);

      /* [cover parentID={B7D11C7B-2C0A-414d-B8C7-F31B72792242}]
      [/cover] */
      RetValue = E_OK;
    }
  }
  return RetValue;
}

#endif /* End of ETH_17_GETHMACV2_ENA_MII_API */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B3AB992E-0BB0-4e76-A673-560FCEBD27E7}]  **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_TxConfirmation(                   **
**                                                      const uint8 CtrlIdx)  **
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
void Eth_17_GEthMacV2_TxConfirmation(const uint8 CtrlIdx)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint8 DevError;
#endif
  uint8 IntEnabled;

  /* [cover parentID={F9C5C255-5EAF-41b7-97C1-ADC9986F8220}]
  DET is Enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={B177661E-7195-4804-BF23-EE1F56849CD3}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                   (ETH_17_GETHMACV2_SID_TXCONFIRMATION);

  /* [cover parentID={94ECD966-EC85-4bf1-B9B7-D82D867D1A2D}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={225FBFDD-F764-42b1-9808-F4BDA66C226D}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                CtrlIdx, ETH_17_GETHMACV2_SID_TXCONFIRMATION);
  }

  /* [cover parentID={2EED28B3-3971-4808-BF88-435DA5FCA0D2}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={27ADBA64-7BDD-49cf-9921-5C648B272CD5}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                            ETH_17_GETHMACV2_SID_TXCONFIRMATION);
  }

  /* [cover parentID={91CC90A8-C801-4374-A025-FEEE69A992D9}]
  If controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={FD9294C7-DD92-492b-B0B6-CEAB3C40CCB9}]
    Validate Controller Mode
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetCheckMode(
                  ETH_17_GETHMACV2_SID_TXCONFIRMATION, EthLocalCoreStatusPtr);
  }
  /* [cover parentID={806299A9-A8E5-4772-AA10-3770D20F2475}]
  Valid Controller Mode
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* If Tx Isr is enabled then confirmation is done in ISR */
    IntEnabled = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties >>
          ETH_17_GETHMACV2_TXINT_POS) & ETH_17_GETHMACV2_TXINT_MSK);

    /* [cover parentID={7BF2533F-632E-4999-B57B-F032763BCB35}]
    If Tx Interrupt is enabled
    [/cover] */
    if(IntEnabled == ETH_17_GETHMACV2_DISABLE)
    {
      /* Local function to confirm all successfully transmitted frames */
      /* [cover parentID={F7F37F01-BAB6-453f-9EF7-5639A92E4892}]
      [/cover] */
      Eth_17_GEthMacV2_lConfirmTxFrames(CtrlIdx);
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0A70B1F3-74DC-4e84-B56C-90A1AC70475F}]  **
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
/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_Transmit(
             const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,
             const Eth_FrameType FrameType, const boolean TxConfirmation,
             const uint16 LenByte, const uint8* const PhysAddrPtr)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint16 BufferIdx;
  uint16 PrioVal;
  uint16 TxBufTotal;
  uint8 FifoIdx;
#endif
  uint8 DevError;
  Std_ReturnType RetVal;

  /* [cover parentID={107F63AC-83C0-43c3-B0D8-F84AEAC9DBE0}]
  DET is Enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)

  BufferIdx = (uint16)(BufIdx & (uint32)ETH_17_GETHMACV2_BUFIDX_MASK);

  PrioVal = (uint16)((BufIdx & (uint32)ETH_17_GETHMACV2_CHNLIDX_MASK) >>
                                        (uint8)ETH_17_GETHMACV2_FIFOIDX_POS);

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={8512B9FD-9AA6-4498-AF33-9B41512C2E7C}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                        ETH_17_GETHMACV2_SID_TRANSMIT);

  /* [cover parentID={5ADB4E5D-4280-4b14-A41E-E16D1AD5205F}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={F2C0443B-28D8-4e1d-9FBD-09DB8B0F228A}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(CtrlIdx,
                                 ETH_17_GETHMACV2_SID_TRANSMIT);
  }
  /* [cover parentID={03D775C8-2E71-4de1-96BD-71E59350FC0A}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
     Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={AFF6F650-5B7B-4803-A728-3AD8FB2AC28B}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_TRANSMIT);
  }
  /* [cover parentID={F1E5C27B-AC68-415f-8F37-AEC0F380C50C}]
  Is controller initialized ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={8A3925B0-2520-4766-9F82-9ABB8B84A028}]
    Is the index to FIFO reference within valid range ?
    [/cover] */
    if (PrioVal >= (uint16)(EthLocalCtrlCfgPtr->EthNumTxChnls))
    {
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                  ETH_17_GETHMACV2_INSTANCE_ID,
                  ETH_17_GETHMACV2_SID_TRANSMIT, ETH_17_GETHMACV2_E_INV_PARAM);

      DevError = ETH_17_GETHMACV2_E_INV_PARAM;
    }
    else
    {
      TxBufTotal = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioVal].NumOfTxBuffers;

      FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioVal].TxFifoIdx;

      /* [cover parentID={3E40572C-F888-4dc1-B3D8-BE79ADA7B52D}]
      BufIdx(Input parameter) less than Total Tx buffer allocated
      [/cover] */
      if(BufferIdx >= TxBufTotal)
      {
        /* [cover parentID={CB09140D-A671-48ab-9797-074ED5BD5FF2}]
        Report DET error ( Invalid Parameter)
        [/cover] */
        (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                  ETH_17_GETHMACV2_INSTANCE_ID,
                  ETH_17_GETHMACV2_SID_TRANSMIT,ETH_17_GETHMACV2_E_INV_PARAM);

        DevError = ETH_17_GETHMACV2_E_INV_PARAM;
      }
      /* [cover parentID={222E0AC2-A8FB-48f9-8907-7C618CDFA9CB}]
      BufIdx(Input parameter) is the one allocated to application
      ( Buffer status is USED)
      [/cover] */
      else if(EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthTxBuffTablePtr[FifoIdx][BufferIdx].BuffStatus !=
              ETH_17_GETHMACV2_BUFFER_USED)
      {
        /* Report DET error ( Invalid Parameter) */
        (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                    ETH_17_GETHMACV2_INSTANCE_ID,
                    ETH_17_GETHMACV2_SID_TRANSMIT,ETH_17_GETHMACV2_E_INV_PARAM);

        DevError = ETH_17_GETHMACV2_E_INV_PARAM;
      }
      /* [cover parentID={7E9FD58D-E74A-4a99-8415-F8678F597ADC}]
      LenByte parameter values is greater than buffer length allocated
      (allocated from ProvideTxBuffer API)
      [/cover] */
      else if(LenByte > EthLocalCoreStatusPtr->EthBuffDescPtr->
                EthTxBuffTablePtr[FifoIdx][BufferIdx].BuffLengthReqstd)
      {
        /* Report DET error (Invalid Parameter) */
        (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                    ETH_17_GETHMACV2_INSTANCE_ID,
                    ETH_17_GETHMACV2_SID_TRANSMIT,ETH_17_GETHMACV2_E_INV_PARAM);

        DevError = ETH_17_GETHMACV2_E_INV_PARAM;
      }
      else
      {
        /*Do nothing. No actions required*/
      }
    }
  }
  /* [cover parentID={6E002E03-818E-4236-9698-C8D297C1E53E}]
  Any parameter error detected ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={AB30BD45-3C7B-4850-BF96-602184BBFEA5}]
    Validate PhysAddrPtr Pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(PhysAddrPtr,
                                               ETH_17_GETHMACV2_SID_TRANSMIT);
  }

  /* [cover parentID={9FCAC9BD-A09B-44f6-9268-5A469019FCB7}]
  Valid PhysAddrPtr Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={B0C4D9A0-89ED-409d-B57E-4DB97BC69301}]
    Validate Controller Mode
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetCheckMode(ETH_17_GETHMACV2_SID_TRANSMIT,
                                              EthLocalCoreStatusPtr);
  }
  /* [cover parentID={26D9553D-47A4-48c1-AE89-BFE14E6CF662}]
  Valid Controller Mode
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={DA527C3D-E473-4bfe-9D73-263D9DC78F1F}]
    Trigger Transmission
    [/cover] */
    /* [cover parentID={4D8D6356-811D-4736-A113-E61D7A2B4F12}]
    [/cover] */
    RetVal = Eth_17_GEthMacV2_lTransmit(CtrlIdx, BufIdx, FrameType,
                                  TxConfirmation, LenByte, PhysAddrPtr);
  }
  else
  {
    /* [cover parentID={46F221A5-7184-4bd9-ADCF-8D172863B879}]
    [/cover] */
    RetVal = E_NOT_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F275FCBA-2CBA-446b-80D6-37A1DF3A435D}]  **
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

/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
void Eth_17_GEthMacV2_Receive(const uint8 CtrlIdx,
                              const uint8 FifoIdx,
                              Eth_RxStatusType* const RxStatusPtr)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Ifx_GETH *EthCtrlAddPtr;
  uint8 FrameNofityStatus;
  uint8 IntEnabled;
  uint8 ChnlIdx;
  boolean NxtFrmAvlbl;

  /* [cover parentID={A654D63A-C105-474e-A778-0352BD01F0CD}]
  DET is Enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={45977132-58CF-4eff-A9A9-F43E1CA6397B}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                       ETH_17_GETHMACV2_SID_RECEIVE);

  /* [cover parentID={2BF23B09-A88B-442a-A33A-27EC187B07B5}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={58FEF484-EC66-4ea6-BB6D-3E5AE763511B}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                  CtrlIdx, ETH_17_GETHMACV2_SID_RECEIVE);
  }
  /* [cover parentID={85936845-E262-4416-A81F-5833F1BDE71E}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
            Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={787C1CE9-AE6D-4004-B210-DE3BA29B368F}]
    Check if controller init is Successful
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_RECEIVE);
  }

  /* [cover parentID={C6D19BD6-B533-4365-9346-BC62EF207173}]
  If controller init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={FC8BF1D5-CB19-48f3-8282-5727E1696D2C}]
    Validate Controller Mode
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetCheckMode(ETH_17_GETHMACV2_SID_RECEIVE,
                                              EthLocalCoreStatusPtr);
  }

  /* [cover parentID={546F0714-A8A1-4a17-B465-05C5678B6FF0}]
  Valid Controller Mode
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={8B678F20-DD80-4fb3-A460-8942507F3C24}]
    Validate RxStatusPtr Pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(RxStatusPtr,
                                              ETH_17_GETHMACV2_SID_RECEIVE);
  }

  /* [cover parentID={BD264A5C-959B-4a6f-87D0-26ADF884053D}]
  Valid RxStatusPtr Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* [cover parentID={D9500834-0A7E-478c-8910-F3E6D932194D}]
    Is FifoIdx parameter valid ?
    [/cover] */
    if (FifoIdx >= EthLocalCtrlCfgPtr->EthNumRxChnls)
    {
      /* [cover parentID={A96D3370-6C82-4bf5-A8E9-6790B547060C}]
      Report Invalid Param dev error
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                ETH_17_GETHMACV2_INSTANCE_ID,
                ETH_17_GETHMACV2_SID_RECEIVE, ETH_17_GETHMACV2_E_INV_PARAM);

      DevError = ETH_17_GETHMACV2_E_INV_PARAM;
    }
  }

  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif/* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /*initialize the RxStatusPtr to ETH_NOT_RECEIVED*/
    *RxStatusPtr = ETH_NOT_RECEIVED;

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    ChnlIdx = EthLocalCtrlCfgPtr->EthRxFifoChnlMapPtr[FifoIdx];

    IntEnabled = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties >>
                    ETH_17_GETHMACV2_RXINT_POS) & ETH_17_GETHMACV2_RXINT_MSK);

    /* If Rx ISR is enabled then Polling mode disabled */
    /* [cover parentID={67562F8F-5FF6-41e1-A69B-3F8574FA921D}]
    If Rx Interrupt is enabled
    [/cover] */
    if(IntEnabled == ETH_17_GETHMACV2_DISABLE)
    {
      /* [cover parentID={12C08275-12A1-42e7-9414-CDE68FC942BD}]
      Check if New frame received and indicate to EthIf driver
      [/cover] */
      FrameNofityStatus = Eth_17_GEthMacV2_lReceiveFrames(CtrlIdx, FifoIdx);

      /* [cover parentID={84940EDC-817E-425b-B8AF-A41DE94E73FC}]
      New Frame received
      [/cover] */
      if(ETH_17_GETHMACV2_FRM_RECEIVED == FrameNofityStatus)
      {
        /* [cover parentID={8AB21BE5-F3CD-4acb-A4D0-DE6973B48322}]
        Check if more frames are received
        [/cover] */
        /* [cover parentID={0C0CF230-8009-4be7-8F2A-96010E9F4617}]
        Any more frames available ?
        [/cover] */
        NxtFrmAvlbl = Eth_17_GEthMacV2_lIsNextFrameAvailable(CtrlIdx, FifoIdx);

        if(NxtFrmAvlbl == TRUE)
        {
          /* [cover parentID={2D8277C8-51DF-49aa-8056-84D6859D37A9}]
          Fill output parameter RxStatusPtr as MORE_DATA_AVAILABLE
          [/cover] */
          *RxStatusPtr = ETH_RECEIVED_MORE_DATA_AVAILABLE;
        }
        else
        {
          /* [cover parentID={2200944B-BFC7-4e8e-8CF6-A11F8F6D2D38}]
          Fill output parameter RxStatusPtr as RECEIVED (But more
          frames not available)
          [/cover] */
          *RxStatusPtr = ETH_RECEIVED;
        }
      }
      else
      {
        /* [cover parentID={1F72C40D-ED54-4848-BC7B-78821C7E525D}]
        Fill output parameter RxStatusPtr as NOT_RECEIVED
        [/cover] */
        *RxStatusPtr = ETH_NOT_RECEIVED;
      }

      /* [cover parentID={F6317D93-87A5-46b6-8466-C99C1C72D692}]
      Issue poll demand command for Rx- DMA channel
      [/cover] */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
       integer type is performed to assign last buffer address to tail pointer
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
        is performed to to assign last buffer address to tail pointer
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
      EthCtrlAddPtr->DMA_CH[ChnlIdx].RXDESC_TAIL_POINTER.U =\
       (uint32)(&(EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaRxDescPtr\
       [FifoIdx][EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].NumOfRxBuffers]));
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={58480FFA-F0B1-40e1-8B5A-948214A22141}]  **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMacV2_UpdatePhysAddrFilter(   **
**                      const uint8 CtrlIdx,const uint8* const PhysAddrPtr,   **
**                      const Eth_FilterActionType Action)                    **
**                                                                            **
** Description      : Adds or removes the MAC address from filter             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Rentrant                                            **
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
Std_ReturnType Eth_17_GEthMacV2_UpdatePhysAddrFilter(const uint8 CtrlIdx,
                             const uint8* const PhysAddrPtr,
                             const Eth_FilterActionType Action)
{
  Ifx_GETH *EthCtrlAddPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Std_ReturnType RetVal;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif

  RetVal = E_OK;

  /* [cover parentID={4AB71F49-5C25-4267-9794-06B4EFA806FB}]
  DET is Enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={7ACA0ACC-952D-40a0-B6E6-B702FB4E147A}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                    ETH_17_GETHMACV2_SID_UPDATEFILTER);

  /* [cover parentID={A734F80D-060E-4a13-B42C-BD1D1CC32152}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMACV2_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={540B208E-C9C8-4d10-9E58-20001314AEC2}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(CtrlIdx,
                                   ETH_17_GETHMACV2_SID_UPDATEFILTER);
  }

  /* [cover parentID={4A7493C2-E608-4a0a-8890-DA615BA6CCA4}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
     /* Check if controller init is Successful in
     Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={880F81B9-08BB-4795-95FC-1ACF88CEAE1E}]
    Check if controller init is Sucessful
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_UPDATEFILTER);
  }
  /* [cover parentID={C6806241-B15E-45af-AB82-3C54EC14F6F6}]
  If controller init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={674ED8B4-2A55-4a9a-A8EA-800B76FA2747}]
    Validate Physical Address Pointer
    [/cover] */
    /*  ETH_17_GETHMACV2_E_PARAM_POINTER. */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(PhysAddrPtr,
                                     ETH_17_GETHMACV2_SID_UPDATEFILTER);
  }
  /* [cover parentID={07DC3153-EF61-4132-9CB6-71D9AE756E3F}]
  Valid Physical Address Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check the parameter Action is valid */
    /* [cover parentID={F8A97338-71E8-4151-B390-3E759B7CDA32}]
    Is the input parameter Action valid ?
    [/cover] */
    if((Action != ETH_ADD_TO_FILTER) && (Action != ETH_REMOVE_FROM_FILTER))
    {
      /* [cover parentID={9FD841E8-0B30-4bf4-B61F-ADEFEF507123}]
      Invalid Parameter DET
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                ETH_17_GETHMACV2_INSTANCE_ID,
                ETH_17_GETHMACV2_SID_UPDATEFILTER,ETH_17_GETHMACV2_E_INV_PARAM);

      DevError = ETH_17_GETHMACV2_E_INV_PARAM;
    }
  }

  if(DevError != ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    RetVal = E_NOT_OK;
  }
  else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* get base address of the controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthLocalCtrlCfgPtr->
                                                          EthCtrlIdx];

    /* [cover parentID={53BDBCDB-EA2B-4004-897A-9C31B6150881}]
    Check if Physical address is Broadcast address
    [/cover] */
    /* [cover parentID={48A5BF89-5282-43a1-BAF2-C97808FFD2FE}]
    Physical Address is broadcast address
    [/cover] */
    if(Eth_17_GEthMacV2_lIsBroadcastAddress(PhysAddrPtr) == TRUE)
    {
      /* [cover parentID={FF0904AB-5FD3-4dd0-BC9C-57823928FB5D}]
      Open filter completely to receive all frames
      [/cover] */
      EthCtrlAddPtr->MAC_PACKET_FILTER.U =
                         (uint32)(ETH_17_GETHMACV2_MAC_FILT_OPEN_CONF);

      Eth_17_GEthMacV2_lClearAllAddressFilters(CtrlIdx);

      /* Set FilterOpenStatus as TRUE*/
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat = TRUE;
    }
    /* [cover parentID={0E84BDD5-C638-487f-B491-5A6CC5374560}]
    Check if Physical address is all Zeros
    [/cover] */
    /* [cover parentID={576605D3-C881-41d7-AABF-328D04B176F3}]
    Physical Address is all Zeros
    [/cover] */
    else if(Eth_17_GEthMacV2_lIsAllZeroAddress(PhysAddrPtr) == TRUE)
    {
      /* [cover parentID={436A0384-2BD6-4af5-A67E-D65DD208B440}]
      Limit MAC filter to the controllers unique unicast MAC address and Set
      FilterOpenStatus as FALSE
      [/cover] */
      EthCtrlAddPtr->MAC_PACKET_FILTER.U =
                          (uint32)ETH_17_GETHMACV2_MAC_FILT_INIT_CONF;

      Eth_17_GEthMacV2_lClearAllAddressFilters(CtrlIdx);

      /* Insert delay for back to back register writes */
      Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(
                                    EthLocalCtrlCfgPtr->EthBkRegWrWaitTime);

      /* Set the configured MAC address in MAC Address register 0 */
      Eth_17_GEthMacV2_lSetPhysAddr(EthLocalCtrlCfgPtr->EthCtrlIdx,
                              (uint8*)EthLocalCoreStatusPtr->
                                EthRunTimeOpertnData.EthUnicastMacAddress);

      /* Set FilterOpenStatus as FALSE*/
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat =
                                                                      FALSE;
    }
    /* [cover parentID={9D88C40A-3E7B-418e-A65C-790D95613D4E}]
    FilterOpenStatus is TRUE
    [/cover] */
    else if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat
                                                                      == TRUE)
    {
      /* Filter is in Open state and hence it is error case*/
      /* [cover parentID={6E6EBF27-712F-43a2-8BBB-3B3E79B4B375}]
      [/cover] */
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={87E9AE78-1092-42a6-BBC5-078F583A432D}]
    Action Is "Add to Filter"
    [/cover] */
    else if(ETH_ADD_TO_FILTER == Action)
    {
      /* [cover parentID={447204A3-BF6E-4467-96BB-F83A0C5FEFA5}]
      Add the address to the filter
      [/cover] */
      RetVal = Eth_17_GEthMacV2_lAddToFilter(CtrlIdx, PhysAddrPtr);

      /* [cover parentID={DAEB6C10-F484-46e2-BECD-6888070EBA55}]
      [/cover] */
      if(RetVal == E_OK)
      {
        /* [cover parentID={34AD4EF6-66A3-4d2e-A49C-17483792C8F2}]
        Address added to filter successfully
        [/cover] */
        /* Configure Mac filter register */
        EthCtrlAddPtr->MAC_PACKET_FILTER.U =
                                   ETH_17_GETHMACV2_MAC_FILT_INIT_CONF;
      }
    }
    /* [cover parentID={676C76E7-34D2-4da9-A66E-E5367B1828E1}]
    Action Is "Remove from Filter"
    [/cover] */
    else if(ETH_REMOVE_FROM_FILTER == Action)
    {
      /* [cover parentID={F000340E-2E31-4638-8548-57206F9F60F6}]
      Remove the address from filter
      [/cover] */
      RetVal = Eth_17_GEthMacV2_lRemoveFromFilter(CtrlIdx, PhysAddrPtr);
    }
    else
    {
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_OFF)
      /* Requested Action is unknown */
      /* [cover parentID={3F41C5EF-13CC-4515-95FF-4A5CD3449208}]
      [/cover] */
      RetVal = E_NOT_OK;
#endif /*ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_OFF*/
    }
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A6F4B467-28CF-42a2-A902-1135139C9A1A}]  **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_SetPhysAddr( const uint8 CtrlIdx, **
**                                         const uint8* const PhysAddrPtr )   **
**                                                                            **
** Description      : Sets the controllers MAC address                        **
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
void Eth_17_GEthMacV2_SetPhysAddr(const uint8 CtrlIdx,
                                  const uint8* const PhysAddrPtr)
{
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint8 LoopCount;

  /* [cover parentID={3F4CF2AD-4941-4a31-BD5C-C20F3622F626}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={5F90EC19-10B6-4328-AA1C-D606F9B487E8}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                   ETH_17_GETHMACV2_SID_SETPHYSADDRESS);

  /* [cover parentID={B354534C-700E-4459-8C7B-72EEE02393E7}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMACV2_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={D2CE302D-9CFC-4a12-ACCD-2A0D64BD1BEC}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                          CtrlIdx, ETH_17_GETHMACV2_SID_SETPHYSADDRESS);
  }

  /* [cover parentID={00323F6A-E437-4725-8B36-92D4BA606DF8}]
  If controller Index is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={22563A91-DDFF-4428-9EE0-201ECD1B279D}]
    Check controller initialization
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_SETPHYSADDRESS);
  }

  /* [cover parentID={73D1A3E5-D5B8-4705-A610-F797F7DCBCA5}]
  if controller initialization is successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={A34F8149-CDD1-4e23-8321-A950847C49CB}]
    Validate Physical Address Pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(PhysAddrPtr,
                                    ETH_17_GETHMACV2_SID_SETPHYSADDRESS);
  }
  /* [cover parentID={D9C3FDD5-ACFB-428b-889A-1D66FC480817}]
  Valid Physical Address Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* Copy the MAC address, which will be used to restore controllers
    unique unicast MAC address while ending promiscuous mode, using API
    Eth_UpdatePhysAddrFilter().*/
    for(LoopCount = 0U; LoopCount < ETH_17_GETHMACV2_MACADDRESS_LEN;
                                                          LoopCount++)
    {
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.
                      EthUnicastMacAddress[LoopCount] = PhysAddrPtr[LoopCount];
    }
    /* [cover parentID={A87523B1-6AD9-4473-BF91-EC8B42C79BDF}]
    Set the Controller Physical source Address( MAC address)
    [/cover] */
    Eth_17_GEthMacV2_lSetPhysAddr(CtrlIdx, PhysAddrPtr);
  }
}


#if (ETH_17_GETHMACV2_GETTXSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={A7FF1D07-FE38-4efc-8A0A-E1B4FD1CE6E9}] **
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
Std_ReturnType Eth_17_GEthMacV2_GetTxStats (const uint8 CtrlIdx,
                                            Eth_TxStatsType* const TxStats)
{
  const Ifx_GETH *EthCtrlAddPtr;
  uint32 TxNUcastPktsCnt;
  Std_ReturnType RetValue;

  /* [cover parentID={AB3E0DB2-DBFE-4fb0-BF90-6B619F37E7E8}]
  Development Error Detection is Enabled
  [/cover] */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={45C08185-8127-43c9-9FEB-43399F0E037F}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={FAC8E101-5EFF-4e08-A728-0677AE5CEEA0}]
  Check for driver initialization
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                 (ETH_17_GETHMACV2_SID_GETTXSTATS);

  /* [cover parentID={60361C2C-83C8-42b0-995E-75E40194939D}]
  Is driver initialized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={52511BDE-1C53-45fe-9FA0-2E1C2BAE107E}]
    Validate the controller index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                  CtrlIdx, ETH_17_GETHMACV2_SID_GETTXSTATS);
  }

  /* [cover parentID={0FC3B676-FAA3-4683-95BC-8E4585D4A31B}]
  Is controller index valid?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
       Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={DF9313AC-C413-4800-A23F-F02C001169DF}]
    Check for controller initialization
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETTXSTATS);
  }

  /* [cover parentID={10F539EE-B560-44a6-899D-C171E4B80AE8}]
  Is controller initalized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={E98F883C-F3CE-45e7-9D3C-FF70B7506FDF}]
    Validate the TxStats pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(TxStats,
                                         ETH_17_GETHMACV2_SID_GETTXSTATS);
  }

  /* [cover parentID={0BE8D6D3-29E2-4f11-80A5-00E9E89F4975}]
  Is the TxStats pointer valid ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON */
  {
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* [cover parentID={7A44024F-F672-4313-B5DE-065EA71028B6}]
    [/cover] */
    /* TxNumberOfOctets - number of octets transmitted */
    TxStats->TxNumberOfOctets = EthCtrlAddPtr->TX_OCTET_COUNT_GOOD_BAD.U;

    /* TxNUcastPkts - Total number of non-unicast packets transmitted */
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    TxNUcastPktsCnt = EthCtrlAddPtr->TX_MULTICAST_PACKETS_GOOD_BAD.U;

    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler supports
    more than 32 characters, no side effects seen. */
    TxStats->TxNUcastPkts = TxNUcastPktsCnt +\
                              EthCtrlAddPtr->TX_BROADCAST_PACKETS_GOOD_BAD.U;

    /* TxUniCastPkts - Total number of unicast packets transmitted */
    TxStats->TxUniCastPkts = EthCtrlAddPtr->TX_UNICAST_PACKETS_GOOD_BAD.U;

    /* [cover parentID={3238BB20-3245-43fd-BF6C-DDA47A905D29}]
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}
#endif  /* ETH_17_GETHMACV2_GETTXSTATS_API == STD_ON */


#if (ETH_17_GETHMACV2_GETTXERRCNTRVAL_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={7F7F2D5B-A28F-4a26-8580-555F7DFF472F}] **
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
Std_ReturnType Eth_17_GEthMacV2_GetTxErrorCounterValues (const uint8 CtrlIdx,
                    Eth_TxErrorCounterValuesType* const TxErrorCounterValues)
{
  const Ifx_GETH *EthCtrlAddPtr;
  uint32 TxDroppedErrPktsCnt;
  Std_ReturnType RetValue;

  /* [cover parentID={DD4F59AA-9143-4e4c-914F-ABF4A2A57352}]
  Development error detection is enabled
  [/cover] */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={F7DE5CE2-3BCB-4035-9995-257287A3F6BD}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={E108BA15-9DA4-4891-A324-6C12D98820EF}]
  Check for driver initialization
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                 (ETH_17_GETHMACV2_SID_GETTXERRCNTRVAL);

  /* [cover parentID={D76F2C5C-23EC-4d23-84E3-2DB0E8DBA1B3}]
  Is driver initialized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={33ECC0C4-8CB1-49ea-A191-132CBBABC136}]
    Validate the controller index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                              CtrlIdx, ETH_17_GETHMACV2_SID_GETTXERRCNTRVAL);
  }

  /* [cover parentID={31CA4C6D-FDA9-4f25-B547-A77BE8233370}]
  Is controller index valid?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
       Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={16BB8231-D98F-45eb-A8EF-39FB2F4E0F23}]
    Check for controller initialization
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETTXERRCNTRVAL);
  }

  /* [cover parentID={BFCB4576-32A4-4341-A6FD-B81900227818}]
  Is controller initialized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={FAECE81B-27C1-422d-89DC-078F9EF3E79D}]
    Validate the TxErrorCounterValues pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(TxErrorCounterValues,
                                      ETH_17_GETHMACV2_SID_GETTXERRCNTRVAL);
  }

  /* [cover parentID={562C2BEE-C17A-4a30-B34F-E5DB917F1E9F}]
  Is the TxErrorCounterValues pointer valid?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON */
  {
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* [cover parentID={3E575D10-10F3-4d2c-B2C4-E6E24ACECED9}]
    [/cover] */
    /* TxDroppedNoErrorPkts - Not supported */
    TxErrorCounterValues->TxDroppedNoErrorPkts =
                             (uint32)ETH_17_GETHMACV2_UNSUPPORTED_CNTR;

    TxDroppedErrPktsCnt = EthCtrlAddPtr->TX_UNDERFLOW_ERROR_PACKETS.U;
    TxDroppedErrPktsCnt += EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.U;
    TxDroppedErrPktsCnt += EthCtrlAddPtr->TX_EXCESSIVE_COLLISION_PACKETS.U;
    TxDroppedErrPktsCnt += EthCtrlAddPtr->TX_CARRIER_ERROR_PACKETS.U;

    /* TxDroppedErrorPkts - Total number of outbound packets that could not be
       transmitted because of errors */
    TxErrorCounterValues->TxDroppedErrorPkts = TxDroppedErrPktsCnt +\
                            EthCtrlAddPtr->TX_EXCESSIVE_DEFERRAL_ERROR.U;

    /* TxDeferredTrans - Count of frames for which the first Tx attempt is
       delayed because the medium is busy */
    TxErrorCounterValues->TxDeferredTrans =
                            EthCtrlAddPtr->TX_DEFERRED_PACKETS.U;

    /* TxSingleCollision - Count of frames for which Tx is inhibited by exactly
       one collision */
    TxErrorCounterValues->TxSingleCollision =
                            EthCtrlAddPtr->TX_SINGLE_COLLISION_GOOD_PACKETS.U;

    /* TxMultipleCollision - Count of frames for which Tx is inhibited by more
       than one collision */
    TxErrorCounterValues->TxMultipleCollision =
                            EthCtrlAddPtr->TX_MULTIPLE_COLLISION_GOOD_PACKETS.U;

    /* TxLateCollision - Count of packets aborted because of late collision */
    TxErrorCounterValues->TxLateCollision =
                            EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.U;

    /* TxExcessiveCollison - Count of packets aborted due of excessive
       collisions */
    TxErrorCounterValues->TxExcessiveCollison =
                            EthCtrlAddPtr->TX_EXCESSIVE_COLLISION_PACKETS.U;

    /* [cover parentID={9E30AC23-1F18-4273-8A8B-7577481DFF11}]
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}
#endif  /* ETH_17_GETHMACV2_GETTXERRCNTRVAL_API == STD_ON */


#if (ETH_17_GETHMACV2_GETRXSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={7AA512EA-F3CE-46ee-86A7-85C6BA72825C}] **
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
**                                                                            **
** Parameters (out) : RxStats - List of receive statistic counter values      **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : success                       **
**                                   -  E_NOT_OK : Rx error statistics could  **
**                                                 not be obtained            **
**                                                                            **
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_GetRxStats (const uint8 CtrlIdx,
                                            Eth_RxStatsType* const RxStats)
{
  const Ifx_GETH *EthCtrlAddPtr;
  uint32 RxStatsCrcAlignErrCnt;
  Std_ReturnType RetValue;

  /* [cover parentID={5C36C7C0-078B-4e33-A3C5-D2E1535F28E9}]
  Development error detection is enabled
  [/cover] */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={8840077C-675C-4deb-80C4-801B78F198A3}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={9594CD30-52A6-4ed5-943E-95ED9F1E4B83}]
  Check for driver initialization
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                 (ETH_17_GETHMACV2_SID_GETRXSTATS);

  /* [cover parentID={26C406A4-BB2A-499b-ADA0-ADA2E1DD805E}]
  Is driver initialized?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={44A871D1-84E1-4184-A72F-ADC642EE57CD}]
    Validate the controller index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                  CtrlIdx, ETH_17_GETHMACV2_SID_GETRXSTATS);
  }

  /* [cover parentID={AE6F9BD4-5033-4c04-BD5E-FE4001664FE3}]
  Is controller index valid?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
       Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={4100C3D9-78C1-492a-8114-21EF1E157894}]
    Check for controller initialization
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETRXSTATS);
  }

  /* [cover parentID={41D9174C-966E-442d-9DA1-64633644E21C}]
  Is controller initialized?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={6FA6D068-E8CD-40fa-984C-C7480AA03DFE}]
    Validate the RxStats pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(RxStats,
                                           ETH_17_GETHMACV2_SID_GETRXSTATS);
  }

  /* [cover parentID={0D971057-F4E6-4d9b-B182-094F6A8F80C6}]
  Is the RxStats pointer valid ?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON */
  {
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* [cover parentID={547B945E-42B3-4a50-9935-B5D55F28B0EB}]
    [/cover] */
    /* RxStatsDropEvents - Packets dropped due to lack of resources */
    RxStats->RxStatsDropEvents =
                             (uint32)EthCtrlAddPtr->RX_FIFO_OVERFLOW_PACKETS.U;

    /* RxStatsOctets - Total number of octets of data received */
    RxStats->RxStatsOctets =
                             (uint32)EthCtrlAddPtr->RX_OCTET_COUNT_GOOD_BAD.U;

    /* RxStatsPkts - Total number of packets received */
    RxStats->RxStatsPkts = (uint32)EthCtrlAddPtr->RX_PACKETS_COUNT_GOOD_BAD.U;

    /* RxStatsBroadcastPkts - Total good broadcast packets received */
    RxStats->RxStatsBroadcastPkts =
                             (uint32)EthCtrlAddPtr->RX_BROADCAST_PACKETS_GOOD.U;

    /* RxStatsMulticastPkts - Total good multicast packets received */
    RxStats->RxStatsMulticastPkts =
                             (uint32)EthCtrlAddPtr->RX_MULTICAST_PACKETS_GOOD.U;

    RxStatsCrcAlignErrCnt = EthCtrlAddPtr->RX_CRC_ERROR_PACKETS.U;

    /* RxStatsCrcAlignErrors - Total packets received with FCS error or
       alignment error */
    RxStats->RxStatsCrcAlignErrors = RxStatsCrcAlignErrCnt +
                          (uint32)EthCtrlAddPtr->RX_ALIGNMENT_ERROR_PACKETS.U;

    /* RxStatsUndersizePkts - Total packets received that were less than
       64 octets long */
    RxStats->RxStatsUndersizePkts =
                          (uint32)EthCtrlAddPtr->RX_UNDERSIZE_PACKETS_GOOD.U;

    /* RxStatsOversizePkts - Total packets received that were longer than
       1518 octets */
    RxStats->RxStatsOversizePkts =
                             (uint32)EthCtrlAddPtr->RX_OVERSIZE_PACKETS_GOOD.U;

    /* RxStatsFragments - Total packets received that were less than 64 octets
       in length with either FCS error or alignment error */
    RxStats->RxStatsFragments =
                             (uint32)EthCtrlAddPtr->RX_RUNT_ERROR_PACKETS.U;

    /* RxStatsJabbers - Total packets received that were longer than 1518
       octets with either FCS error or alignment error */
    RxStats->RxStatsJabbers =
                             (uint32)EthCtrlAddPtr->RX_JABBER_ERROR_PACKETS.U;

    /* RxStatsCollisions - Best estimate of the total number of collisions -
       This counter is not supported by the HW */
    RxStats->RxStatsCollisions =
                             (uint32)ETH_17_GETHMACV2_UNSUPPORTED_CNTR;

    /* RxStatsPkts64Octets - Total packets received that were 64 octets in
       length */
    RxStats->RxStatsPkts64Octets =
                         (uint32)EthCtrlAddPtr->RX_64OCTETS_PACKETS_GOOD_BAD.U;

    /* RxStatsPkts65to127Octets - Total packets received that were between
       65 and 127 octets in length */
    RxStats->RxStatsPkts65to127Octets =
                     (uint32)EthCtrlAddPtr->RX_65TO127OCTETS_PACKETS_GOOD_BAD.U;

    /* RxStatsPkts128to255Octets - Total packets received that were between
       128 and 255 octets in length */
    RxStats->RxStatsPkts128to255Octets =
                  (uint32)EthCtrlAddPtr->RX_128TO255OCTETS_PACKETS_GOOD_BAD.U;

    /* RxStatsPkts256to511Octets - Total packets received that were between
       256 and 511 octets in length */
    RxStats->RxStatsPkts256to511Octets =
                  (uint32)EthCtrlAddPtr->RX_256TO511OCTETS_PACKETS_GOOD_BAD.U;

    /* RxStatsPkts512to1023Octets - Total packets received that were between
       512 and 1023 octets in length */
    RxStats->RxStatsPkts512to1023Octets =
                  (uint32)EthCtrlAddPtr->RX_512TO1023OCTETS_PACKETS_GOOD_BAD.U;

    /* RxStatsPkts1024to1518Octets - Total packets received that were between
       1024 and 1518 octets in length */
    RxStats->RxStatsPkts1024to1518Octets =
                  (uint32)EthCtrlAddPtr->RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD.U;

    /* RxUnicastFrames - Total unicast packets received */
    RxStats->RxUnicastFrames =
                     (uint32)EthCtrlAddPtr->RX_UNICAST_PACKETS_GOOD.U;

    /* [cover parentID={FB36F028-90CA-4cb0-8D75-3AA4ED169C6F}]
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}
#endif  /* ETH_17_GETHMACV2_GETRXSTATS_API == STD_ON */

#if (ETH_17_GETHMACV2_GETCNTRVALUES_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1E177B77-6459-4c06-AD91-8E2F2312C0FC}]  **
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
Std_ReturnType Eth_17_GEthMacV2_GetCounterValues (const uint8 CtrlIdx,
                                     Eth_CounterType* const CounterPtr)
{
  uint32 TotalErronInbPkts;
  uint32 TotalErronOutbPkts;
  const Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;

  /* [cover parentID={09481E87-6125-4874-A886-F4B60352449D}]
  Development error detection is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={C8D96519-95D2-4786-B3E5-19CE2F5394B0}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* [cover parentID={4832D5BE-0A21-469b-BED0-696350D7C3CF}]
  Check for driver initialization
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                      (ETH_17_GETHMACV2_SID_GETCOUNTERVALUES);

  /* [cover parentID={FE58DF14-B965-4c58-9AB5-7181AFE12648}]
  Is driver initialized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={AF04EB77-F9DF-4729-B676-13628FC857D7}]
    Validate the controller index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                              CtrlIdx, ETH_17_GETHMACV2_SID_GETCOUNTERVALUES);
  }

  /* [cover parentID={839BA654-D2FF-422c-8638-6922C339C9D1}]
  Is controller index valid?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
     /* Check if controller init is successful in
        Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={233B78FB-A316-4eda-97E3-6077DEE01C9E}]
    Check for controller initialization
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETCOUNTERVALUES);
  }

  /* [cover parentID={CEFC2FF3-1F70-4661-8709-74CCF2635C20}]
  Is controller initialized?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={0D5DB752-5F6C-4a01-9377-8E0C16A3BCA6}]
    Validate the CounterPtr pointer
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(CounterPtr,
                                       ETH_17_GETHMACV2_SID_GETCOUNTERVALUES);
  }

  /* [cover parentID={5EA98F34-D396-4093-8987-64BBEB5A5CDB}]
  CounterPtr pointer is valid
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* [cover parentID={7EB1AAD1-7D0A-48f5-B5EC-AAB405D6F059}]
    [/cover] */
    /* DropPktBufOverrun - Dropped packets due to buffer overrun. That is, the
       packets discarded because of Receive FIFO overflow */
    CounterPtr->DropPktBufOverrun =
                        EthCtrlAddPtr->RX_FIFO_OVERFLOW_PACKETS.U;

    /* DropPktCrc -- Dropped packets due to CRC errors */
    CounterPtr->DropPktCrc =
                  (uint32)EthCtrlAddPtr->RX_CRC_ERROR_PACKETS.B.RXCRCERR;

    /* UndersizePkt -- Number of undersize packets which were less than 64
       octets long without any errors */
    CounterPtr->UndersizePkt =
                 (uint32)EthCtrlAddPtr->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG;

    /* OversizePkt -- Number of oversize packets which are longer than 1518
       octets without any errors */
    CounterPtr->OversizePkt =
                    (uint32)EthCtrlAddPtr->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG;

    /* AlgnmtErr -- Number of alignment errors, i.e. packets which are received
       and are not an integral number of octets in length and do not pass the
       CRC. */
    CounterPtr->AlgnmtErr =
                  (uint32)EthCtrlAddPtr->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR;

    /* SqeTestErr - Signal Quality Error test error. This error counter is not
       supported by hardware */
    CounterPtr->SqeTestErr = (uint32)ETH_17_GETHMACV2_UNSUPPORTED_CNTR;

    /* DiscInbdPkt --Number of inbound packets which were chosen to be
       discarded even though no errors had been detected. One possible reason
       for discarding such a packet could be to free up buffer space.
       Info: There are no specific packets which are chosen to be discarded by
       the SW/ HW. Hence this counter is not supported */
    CounterPtr->DiscInbdPkt = (uint32)ETH_17_GETHMACV2_UNSUPPORTED_CNTR;

    /* ErrInbdPkt - Total number of erroneous inbound packets.
       Info: This item is filled with counters that is addition of all receive
       error counters available from hardware */
    TotalErronInbPkts =
                      (uint32)(EthCtrlAddPtr->RX_CRC_ERROR_PACKETS.B.RXCRCERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                      EthCtrlAddPtr->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                           EthCtrlAddPtr->RX_RUNT_ERROR_PACKETS.B.RXRUNTERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                          EthCtrlAddPtr->RX_JABBER_ERROR_PACKETS.B.RXJABERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                          EthCtrlAddPtr->RX_LENGTH_ERROR_PACKETS.B.RXLENERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                   EthCtrlAddPtr->RX_OUT_OF_RANGE_TYPE_PACKETS.B.RXOUTOFRNG);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts +
                        EthCtrlAddPtr->RX_RECEIVE_ERROR_PACKETS.B.RXRCVERR);
    CounterPtr->ErrInbdPkt = TotalErronInbPkts;

    /* DiscOtbdPkt - The number of outbound packets which were chosen to be
       discarded even though no errors had been detected.
       Info: There are no specific packets which are chosen to be discarded by
       the SW/ HW. Hence this counter is not supported */
    CounterPtr->DiscOtbdPkt = (uint32)ETH_17_GETHMACV2_UNSUPPORTED_CNTR;

    /* ErrOtbdPkt - Total number of erroneous outbound packets */
    TotalErronOutbPkts = (uint32)(EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.B.
                                                                    TXLATECOL);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts +
                    EthCtrlAddPtr->TX_EXCESSIVE_COLLISION_PACKETS.B.TXEXSCOL);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts +
                            EthCtrlAddPtr->TX_CARRIER_ERROR_PACKETS.B.TXCARR);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts +
                      EthCtrlAddPtr->TX_EXCESSIVE_DEFERRAL_ERROR.B.TXEXSDEF);
    CounterPtr->ErrOtbdPkt = TotalErronOutbPkts;

    /* SnglCollPkt -Single collision frames. The number of successfully
       transmitted packets after a single collision */
    CounterPtr->SnglCollPkt =
          (uint32)EthCtrlAddPtr->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG;

    /* MultCollPkt - Multiple collision frames. The number of successfully
       transmitted packets after multiple collisions. */
    CounterPtr->MultCollPkt =
         (uint32)EthCtrlAddPtr->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG;

    /* DfrdPkt - Number of deferred transmission: A count of frames for which
       the first transmission attempt on a particular interface is delayed
       because the medium is busy */
    CounterPtr->DfrdPkt = (uint32)EthCtrlAddPtr->TX_DEFERRED_PACKETS.B.TXDEFRD;

    /* LatCollPkt - Number of late collisions. The number of packets aborted
       because of late collision error. */
    CounterPtr->LatCollPkt =
                   (uint32)EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.B.TXLATECOL;

    /* [cover parentID={8FE3C969-3852-431e-AFA2-DBAF82DE3C9D}]
    [/cover] */
    /* HwDepCtr0 - This counter provides the number of good VLAN packets
       transmitted */
    CounterPtr->HwDepCtr0 =
                          (uint32)EthCtrlAddPtr->TX_VLAN_PACKETS_GOOD.B.TXVLANG;

    /* HwDepCtr1 - This counter provides the number of good IPv4 packets
       received */
    CounterPtr->HwDepCtr1 =
                       (uint32)EthCtrlAddPtr->RXIPV4_GOOD_PACKETS.B.RXIPV4GDPKT;

    /* HwDepCtr2 - This counter provides the number of good IP datagrams
       received with a good TCP payload */
    CounterPtr->HwDepCtr2 =
                       (uint32)EthCtrlAddPtr->RXTCP_GOOD_PACKETS.B.RXTCPGDPKT;

    /* HwDepCtr3 - This counter provides the number of good IP datagrams
       received with a good UDP payload (without checksum disabled) */
    CounterPtr->HwDepCtr3 =
                       (uint32)EthCtrlAddPtr->RXUDP_GOOD_PACKETS.B.RXUDPGDPKT;

    /* [cover parentID={DD83ACE3-8CB9-48d5-A7CE-467500546BBD}]
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}
#endif/* End for ETH_17_GETHMACV2_GETCNTRVALUES_API */


#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={FA03859F-C0CE-4cee-8BFD-F7B0F2727E54}]  **
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
Std_ReturnType Eth_17_GEthMacV2_GetCurrentTime(const uint8 CtrlIdx,
                                Eth_TimeStampQualType* const timeQualPtr,
                                Eth_TimeStampType* const timeStampPtr)
{
  const Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
  /* [cover parentID={4B886995-9A79-4913-A739-4A86CBC646F9}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={D4ED6D93-5477-4fea-8142-B60300FB6FCF}]
  In default, Set RetValue = E_NOT_OK
  [/cover] */
  RetValue = E_NOT_OK;

  /* [cover parentID={CB4C91F9-D09B-42d5-A0D5-D0EA07779951}]
   Validate Time stamp Quality pointer (Output parameter)
   [/cover] */
  /* ETH_17_GETHMACV2_E_PARAM_POINTER */
  DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeQualPtr,
                                         ETH_17_GETHMACV2_SID_GETCURRENTTIME);

  /* [cover parentID={13272AEA-4806-4bc3-BA53-7DA36911641A}]
  Valid Timestamp Quality Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    *timeQualPtr = ETH_INVALID;

    /* [cover parentID={431B20D6-0182-4406-B1CA-3DC237A35DED}]
     Validate Time stamp pointer( Output parameter)
     [/cover] */
    /* ETH_17_GETHMACV2_E_PARAM_POINTER */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeStampPtr,
                                         ETH_17_GETHMACV2_SID_GETCURRENTTIME);
  }
  /* [cover parentID={1EC342E0-09C4-4c65-A241-63DE4F7F028E}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={66367C24-6997-4a47-BEFE-44CFB1771944}]
    Check Driver is initialized
    [/cover] */
    /* Check if Eth_17_GEthMacV2_Init is successful */
    DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                        ETH_17_GETHMACV2_SID_GETCURRENTTIME);
  }
  /* [cover parentID={BCAE38DA-9DD6-4e7e-B977-4AD306629F64}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={AF9421C5-463A-4772-B9D9-B2C69BB05C78}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                             CtrlIdx, ETH_17_GETHMACV2_SID_GETCURRENTTIME);
  }
  /* [cover parentID={A0485F07-A6A5-47f2-86C3-38CDCE46F95F}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
                                        Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={9E1E6189-3397-404b-8628-3A3D67971418}]
    Check if controller initialization was successful
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETCURRENTTIME);
  }

  /* [cover parentID={B306CE4E-C916-4e7c-AADB-0FD555FE8B14}]
  If controller init successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* get base address of the controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

    /* [cover parentID={60FB580B-9148-4fe9-BE4C-08A260076D88}]
     Set Time stamp Quality as VALID
     [/cover] */
    *timeQualPtr = ETH_VALID;

    /* [cover parentID={04AC8FCF-64CA-4755-8B61-2D10E5ADE970}]
    Read Time from Timer(Hardware Timer in GETH) and fill in
    timeStampPtr (output parameter)
    [/cover] */
    /* Return Higher word second, second and nano second value */
    timeStampPtr->seconds = EthCtrlAddPtr->MAC_SYSTEM_TIME_SECONDS.U;
    timeStampPtr->secondsHi =
                  EthCtrlAddPtr->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
    timeStampPtr->nanoseconds =
                  EthCtrlAddPtr->MAC_SYSTEM_TIME_NANOSECONDS.B.TSSS;

    /* [cover parentID={982EAD3C-2AD8-41d2-852D-712DCC7EE509}]
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={839F657F-9BDF-4c59-A76B-DFA595BD6DFE}]  **
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
void Eth_17_GEthMacV2_EnableEgressTimeStamp(const uint8 CtrlIdx,
                                            const Eth_BufIdxType BufIdx)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint16 BufferIdx;
  uint16 PrioMapIdx;
  uint16 FifoIdx;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif

  /* Get the buffer index */
  BufferIdx = (uint16)(BufIdx & (uint32)ETH_17_GETHMACV2_BUFIDX_MASK);

  /* Get the channel index */
  PrioMapIdx = (uint16)((BufIdx & (uint32)ETH_17_GETHMACV2_CHNLIDX_MASK) >>
                                   (uint8)ETH_17_GETHMACV2_FIFOIDX_POS);

  /* [cover parentID={C8987F3E-AA36-4356-93DE-AEA3791D4035}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={7691697A-AA58-456a-9CB2-6C49E6C37BF9}]
  Check Driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                               (ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP);

  /* [cover parentID={2C10EF7E-13A2-4d06-ACCF-FD40318F0488}]
   Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={8A796113-8C72-40ed-B3E7-6A23BD7889A9}]
    Check Controller Index is Valid
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                          CtrlIdx, ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP);
  }
  /* [cover parentID={E581AB6E-694F-432c-89F4-72E51723D15E}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={8EDC0D4E-14E7-4d1e-B3A9-FDDDA8C5DF34}]
    Check controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP);
  }

  /* [cover parentID={4F8D61B8-CC58-423d-A970-068770F77025}]
  If controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={2F4B7B06-5C78-468e-A29E-AAEBA82BBD06}]
    Check Buffer index is valid
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetCheckBufIdx(CtrlIdx,
            ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP,PrioMapIdx, BufferIdx);
  }

  /* [cover parentID={5A1E2CDF-DBBB-47ac-AA57-DFD92BE20C05}]
  Check if any DET error occured due to previous check
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioMapIdx].TxFifoIdx;

    /* [cover parentID={2DBAB784-704E-43bc-ACE8-97D59425F9F0}]
    BufIdx(Input parameter) is the one allocated to application
    (Buffer status is USED)
    [/cover] */
    if(EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                 [BufferIdx].BuffStatus == ETH_17_GETHMACV2_BUFFER_USED)
    {
      /* [cover parentID={9A0C294C-AB8D-46b9-9559-BCD25076A758}]
      Enable Transmit Time stamp
      [/cover] */
      EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
          [BufferIdx].TimeStampEnable = ETH_17_GETHMACV2_ENABLE;
    }
    else
    {
      /* [cover parentID={DE6CF3E7-33CF-4bb2-88A0-6708593AA7B2}]
      DET is enabled
      [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={44231FCB-57FB-4cd1-857B-1E96C6BA43E2}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID,
                            ETH_17_GETHMACV2_SID_ENABLEEGRESSTIMESTAMP,
                            ETH_17_GETHMACV2_E_INV_PARAM);
#endif
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DD8EB5AE-3044-4a59-A50E-B4FE6B4A6086}]  **
**                                                                            **
** Syntax           : Std_ReturnType  Eth_17_GEthMacV2_GetEgressTimeStamp     **
**                        (const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,  **
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
Std_ReturnType Eth_17_GEthMacV2_GetEgressTimeStamp(const uint8 CtrlIdx,
       const Eth_BufIdxType BufIdx, Eth_TimeStampQualType* const timeQualPtr,
                                    Eth_TimeStampType* const timeStampPtr)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_DmaTxDescType *EthLocalDmaTxDescPtr;
  const Ifx_GETH *EthCtrlAddPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint16 BufferIdx;
  uint16 PrioIdx;
  uint16 FifoIdx;
  uint16 TxDescIdx;
  Std_ReturnType RetVal;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif

  /* [cover parentID={8D87CBBE-4836-4ec1-AE12-3B75D539FF8C}]
  [/cover] */
  RetVal = E_NOT_OK;

  BufferIdx = (uint16)(BufIdx & (uint32)ETH_17_GETHMACV2_BUFIDX_MASK);

  PrioIdx = (uint16)((BufIdx & (uint32)ETH_17_GETHMACV2_CHNLIDX_MASK) >>
                                      (uint8)ETH_17_GETHMACV2_FIFOIDX_POS);

  /* [cover parentID={9369442C-C518-472c-A3DC-3BB2AF57EDA5}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={B9DD02CC-E726-46c5-B12E-686AEC5184C5}]
  Validate Time stamp Quality pointer (Output parameter)
  [/cover] */
  /* ETH_17_GETHMACV2_E_PARAM_POINTER */
  DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeQualPtr,
                                      ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP);

  /* [cover parentID={2D2BC311-6D20-4d99-BD73-C90AF522F8E9}]
  Valid Timestamp Quality Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    *timeQualPtr = ETH_INVALID;

    /* [cover parentID={B6DA85F0-E06B-43de-B491-988E2E629FD8}]
    Validate Time stamp pointer( Output parameter)
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeStampPtr,
                                    ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={B04EAB6C-90C7-4063-A5B0-BB7BE279B515}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={1B1A029C-DEA4-48a7-A33F-0333785FD911}]
     Check Driver is initialized
     [/cover] */
    /* Check if Eth_17_GEthMacV2_Init is successfully */
    DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                  ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={A59A7844-B2BC-46fb-B01B-C14CBB64EB48}]
  If driver is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={92E9415D-B457-4eee-8C24-C2CDDA480B13}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                           CtrlIdx, ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={DA57FB4A-1F9D-4798-A6D1-9AF3534BF5F8}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is Successfully done in
       Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={81188A1D-7973-4db9-BDD8-DD50C9D78CB9}]
    Check controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={0AFA0190-1F9F-479e-AE9D-B3E32FD09DD3}]
  If Controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={F22C4ACA-4BBB-4ad7-8B20-BC5238ADDCE9}]
    Check for buffer index is valid
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetCheckBufIdx(CtrlIdx,
               ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP, PrioIdx, BufferIdx);
  }

  /* [cover parentID={57C4C8BF-33F4-47f1-9EC7-4DD642EAC35C}]
  Any DET error due to previous check?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* [cover parentID={144E9B60-5D36-47a4-BDFD-EAD3FF3B2812}]
    Set Time stamp Quality as INVALID
    [/cover] */
    *timeQualPtr = ETH_INVALID;

    /* get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

     /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* Get controller configuration data */
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioIdx].TxFifoIdx;

    EthLocalDmaTxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                              EthDmaTxDescPtr[FifoIdx];

    TxDescIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
                      EthRunTmTxChnlDataPtr[FifoIdx].TxDmaDescIdxTmStmp;

    /* [cover parentID={07C039BA-BEF3-460b-B86E-43BA48654429}]
    BufIdx(Input parameter) is the one allocated to application( Buffer status
    is Used_TxInitiated) and Check Tx time stamp descriptor index is valid and
    Check if Time stamp for buffer is enabled
    [/cover] */
    if((EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
        [BufferIdx].BuffStatus == ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED) &&
       (EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                    [BufferIdx].TimeStampEnable == ETH_17_GETHMACV2_ENABLE) &&
       (TxDescIdx != ETH_17_GETHMACV2_DMADESC_INVALID))
    {
      /* Check if the requested descriptor's LD bit(Last Descriptor) is set */
      /* [cover parentID={6B0FF6E9-961A-4fb4-AE27-65BBC635336C}]
      Requested frame's ( Buffer Index's) end of packet is received
      [/cover] */
      if((EthLocalDmaTxDescPtr[TxDescIdx].TDES3 &
         ((uint32)ETH_17_GETHMACV2_DMA_TX_DESC_LD_SET)) ==
             (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_LD_SET)
      {
        /* [cover parentID={E3E48C39-B044-4662-A57D-053D513AC9A8}]
        Timestamp has been captured by hardware for the requested frame
        (Buffer Index)
        [/cover] */
        if((EthLocalDmaTxDescPtr[TxDescIdx].TDES3 &
                   ((uint32)ETH_17_GETHMACV2_DMA_TX_DESC_TTSS_SET)) ==
                   (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_TTSS_SET)
        {
          /* [cover parentID={25A41911-2BBD-46b6-8354-E7CB4CFEB9F5}]
          Set Time stamp Quality as VALID
          [/cover] */
          *timeQualPtr = ETH_VALID;

          /* [cover parentID={5DAF230C-DC53-4994-8A51-6EA1A49827C0}]
          Read Time stamp form Tx descriptor of Buffer Index and HIGHER WORD
          SECONDS register and copy to time StampPointer (output parameter)
          [/cover] */
          /* Copy packet time stamp to timeStampPtr.*/
          /* Info: Overflow of MAC_SYSTEM_TIME_SECONDS register will happen
           * only once in 130 years. Hence MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS
           * directly coped to SecondHi value */
          timeStampPtr->secondsHi =
                (uint16)EthCtrlAddPtr->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U;
          timeStampPtr->seconds =
                         (EthLocalDmaTxDescPtr[TxDescIdx].TDES1);
          timeStampPtr->nanoseconds =
                         (EthLocalDmaTxDescPtr[TxDescIdx].TDES0);

          /* [cover parentID={3C19AC5E-3E43-46c2-968B-299DE765536F}]
          [/cover] */
          RetVal = E_OK;
        }
      }
    }
    else
    {
      /* [cover parentID={03BDCA05-DAB6-45ff-933F-F2BCA96817D0}]
      DET is enabled
      [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={3CCA808C-E4A7-4a17-A058-2119115EA4C1}]
      Report DET error (Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID,
                            ETH_17_GETHMACV2_SID_GETEGRESSTIMESTAMP,
                            ETH_17_GETHMACV2_E_INV_PARAM);
#endif
    }
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={EAAB4E73-D3E6-4cba-B6B9-58AE81F8AAD7}]  **
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
**                                     This parameter is not used in ETH      **
**                                     driver design                          **
**                                                                            **
** Parameters (out) : timeQualPtr  -  quality of HW time stamp, e.g.          **
**                                    based on current drift                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Success                          **
**                                   - E_NOT_OK: Failed to read time stamp    **
**                                                                            **
*******************************************************************************/
Std_ReturnType Eth_17_GEthMacV2_GetIngressTimeStamp(const uint8 CtrlIdx,
                                 const Eth_DataType* const DataPtr,
                                 Eth_TimeStampQualType* const timeQualPtr,
                                 Eth_TimeStampType* const timeStampPtr)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_DmaRxDescType *EthLocalDmaRxDescPtr;
  const Ifx_GETH *EthCtrlAddPtr;
  uint16 DmaDescIdx;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif
  uint8 FifoIdx;
  uint8 LoopCnt;
  Std_ReturnType RetVal;

  /* [cover parentID={7BB5CE6B-980C-4b84-8299-EAF990A8886C}]
  [/cover] */
  RetVal = E_NOT_OK;

  FifoIdx = ETH_17_GETHMACV2_INV_FIFO_IDX;

  /* [cover parentID={081E5D3F-27E4-46c4-902A-192D98AB0DEA}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={24D084BE-4013-4157-ACC4-6759B264AFC9}]
  Validate Time stamp Quality pointer (Output parameter)
  [/cover] */
  /* ETH_17_GETHMACV2_E_PARAM_POINTER */
  DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeQualPtr,
                                  ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);

  /* [cover parentID={D76FFC81-6BC2-4725-8668-98C53D8652A5}]
  Is Timestamp Quality Pointer valid ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    *timeQualPtr = ETH_INVALID;

    /* [cover parentID={2A8BDB55-4DAA-413f-810B-6EC5003A94CD}]
    Validate Time stamp pointer( Output parameter)
    [/cover] */
     DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(timeStampPtr,
                                    ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={14309505-620F-418f-8EE8-D362D68F7C2B}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if Eth_17_GEthMacV2_Init is successful */
    /* [cover parentID={03F06D82-2742-4528-B9EA-5769726C5652}]
    Check Driver is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                   ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={B587D97E-2350-4fc9-98AA-0B8B671A9525}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={C5712B54-2732-46b2-87FF-CDBF0E9A2BF5}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                         CtrlIdx, ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={6B07CD86-9978-4bef-A5E4-75A8CC1ECA9F}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
     /* Check if controller init is Successful in
          Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={9777147C-AA96-4460-9A23-16F85D78A88D}]
     Check if controller init is successful
     [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={3135CCE7-3714-4768-B34D-BA987984223D}]
  If controller init was successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={0953FBE0-B97E-46c1-B24A-10F2EBD0441F}]
    Validate DataPtr pointer
    [/cover] */
     DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(DataPtr,
                                  ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={3A90AA25-96BE-4eb0-B4C6-6D4E38AD2ABB}]
  Valid DataPtr
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

    /* [cover parentID={5963EFD7-B192-4c36-AA5C-00A649AA89CA}]
    Set the time stamp quality as INVALID
    [/cover] */
    *timeQualPtr = ETH_INVALID;

    /* Check if valid DataPtr is passed to this API during invocation */
    /* [cover parentID={D93A1C8F-E4D9-4ae2-882A-948589DC57E0}]
    Is the DataPtr value valid as expected by the calling sequence?
    [/cover] */
    for (LoopCnt = 0U; LoopCnt < ETH_17_GETHMACV2_MAXCHLS_SUPPORTED; LoopCnt++)
    {
      if (EthLocalCoreStatusPtr->EthRunTimeOpertnData.RxTmStmpDataPtr[LoopCnt]
            == DataPtr)
      {
        FifoIdx = LoopCnt;
        break;
      }
    }

    /* If FIFO index is valid */
    if (FifoIdx != ETH_17_GETHMACV2_INV_FIFO_IDX)
    {
      /* get base address of the indexed controller */
      EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

      /* [cover parentID={5A2B1F7B-E251-4f7a-843C-C6294C397D4F}]
      Is valid Time stamp is available for Requested DataPtr ?
      [/cover] */
      if (EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmRxChnlDataPtr[FifoIdx].
                       RxDmaDescIdxTmStmp != ETH_17_GETHMACV2_DMADESC_INVALID)
      {
        DmaDescIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
                      EthRunTmRxChnlDataPtr[FifoIdx].RxDmaDescIdxTmStmp;

        /* [cover parentID={29461D63-521E-4f2e-9F3B-FDC65CF34699}]
        Read Time stamp from Rx descriptor with corresponding index and
        HIGHER WORD SECONDS register and copy to timeStampPtr (output parameter)
        [/cover] */
        /* Info: Overflow of MAC_SYSTEM_TIME_SECONDS register will happen
        only once in 130 years. Hence MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS
        directly coped to SecondHi value */
        EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                                  EthDmaRxDescPtr[FifoIdx];

        timeStampPtr->secondsHi =
                  (uint16)EthCtrlAddPtr->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U;

        timeStampPtr->seconds = (EthLocalDmaRxDescPtr[DmaDescIdx].RDES1);

        timeStampPtr->nanoseconds = (EthLocalDmaRxDescPtr[DmaDescIdx].RDES0);

        /* Check time stamp quality by checking is it corrupted. */
        /* [cover parentID={82652832-0238-4d61-87CF-718A6E951AA3}]
        [/cover] */
        if((timeStampPtr->seconds != ETH_17_GETHMACV2_INGRESS_TS_CORRUPT) ||
           (timeStampPtr->nanoseconds != ETH_17_GETHMACV2_INGRESS_TS_CORRUPT))
        {
          /* [cover parentID={D0B7912D-B646-401d-87BA-D3AFCF18DA3A}]
          Set Time stamp Quality as VALID
          [/cover] */
          *timeQualPtr = ETH_VALID;

          /* [cover parentID={05B17B45-648B-4d4e-BA73-93126F7F18BB}]
          [/cover] */
          RetVal = E_OK;
        }
      }
    }
    /* [cover parentID={6AADCD31-7073-47ed-AF45-CE04BFC9F84D}]
    DET is enabled
    [/cover] */
#if (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* [cover parentID={8058E9B0-131C-46d5-8D7A-8A7EEB47DD56}]
      Report Dev error for invalid DataPtr
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID,
                            ETH_17_GETHMACV2_SID_GETINGRESSTIMESTAMP,
                            ETH_17_GETHMACV2_E_PARAM_POINTER);
    }
#endif /* (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON) */
  }

  return RetVal;
}

#endif  /* (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C8AE4ACE-712F-471c-904A-F5DA375B1A11}]  **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_MainFunction (void)               **
**                                                                            **
** Description      : The function checks for controller errors  and          **
**                    lost frames.                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x20                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Eth_17_GEthMacV2_MainFunction(void)
{
  uint32 CoreId;
  CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={B1FAC4DC-28B4-42ee-97CD-434E8A406CB6}]
  Check Ethernet Driver is initialized for the current core
  [/cover] */
  /* [cover parentID={25FC213C-5F08-444a-8F0B-F02DA93FFE2B}]
  Driver Initialized for current core?
  [/cover] */
  /* If ETH driver is not initialized, return immediately without performing
  any functionality and without raising any errors.*/
  if(*(Eth_17_GEthMacV2_CoreInitStatusPtr[CoreId]) ==
                                      (uint32)ETH_17_GETHMACV2_CORE_INIT)
  {
    /* [cover parentID={0B2FD07C-21B3-46ab-86CB-B32A739034CC}]
    Updates Statistics counter values
    [/cover] */
    Eth_17_GEthMacV2_lUpdateEthStatisticsCounterValues();

    /* [cover parentID={91E25E78-6F7C-4ce2-AA47-2C27AD2C7DCA}]
    Report to Production error for Statistics Counter values
    [/cover] */
    Eth_17_GEthMacV2_lDemReportStatisticsCounterValues();
  }
}

#if(ETH_17_GETHMACV2_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D054828C-C86D-4f79-A9EC-80A0805067CB}]  **
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
void Eth_17_GEthMacV2_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr)
{
  /* [cover parentID={995956B0-43C6-4fbb-B807-B4B00DD17651}]
  Development error detection is enabled
  [/cover] */
  #if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;

  /* [cover parentID={DD778126-2F51-4831-8812-444FA2675978}]
  Validate the VersionInfoPtr pointer
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(VersionInfoPtr,
                                         ETH_17_GETHMACV2_SID_GETVERSIONINFO);

  /* [cover parentID={E76DA896-B128-4f7c-A6E6-4B03ED9E3EB8}]
  VersionInfoPtr pointer is valid
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  #endif /* End for ETH_17_GETHMACV2_DEV_ERROR_DETECT */
  {
    /* [cover parentID={C6303C16-7CFB-4c6a-A897-00F47730CE82}]
    Write the values of Module ID, Vendor ID, SW Major, Minor and Patch
    version to the Version Info Pointer
    [/cover] */
    VersionInfoPtr->vendorID         = (uint16)ETH_17_GETHMACV2_VENDOR_ID;
    VersionInfoPtr->moduleID         = (uint16)ETH_17_GETHMACV2_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)ETH_17_GETHMACV2_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)ETH_17_GETHMACV2_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)ETH_17_GETHMACV2_SW_PATCH_VERSION;
  }
}
#endif  /* ETH_17_GETHMACV2_VERSION_INFO_API == STD_ON */

#if (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A185ADAD-9EC9-4e88-830C-7D407536C2D3}]  **
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
void Eth_17_GEthMacV2_TxDmaIrqHdlr(const uint8 CtrlIdx, const uint8 DmaChnlIdx)
{
  Ifx_GETH *EthCtrlAddPtr;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint8 DevError;
#endif

  /* [cover parentID={E66C8B31-3D09-4b98-AA79-C5B70F1CF4FF}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={4AC8B90C-2F7C-4f7f-B192-58A7D72552D1}]
  Check if Eth_17_GEthMacV2_Init is successful
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                          ETH_17_GETHMACV2_SID_TXHANDLER);

  /* [cover parentID={81149938-E08C-4f9c-B699-36A5998CDF07}]
  If init was successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={FA1C5A2E-B0BE-44e0-8B75-006455EB610D}]
    Check If Control Index is valid
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                  CtrlIdx, ETH_17_GETHMACV2_SID_TXHANDLER);
  }
  /* [cover parentID={DFAE27C7-8C2F-47a4-BC52-0C0D24A6C8CF}]
  If Ctrl Index is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={EB37FD48-D912-4522-87F3-1F0E3BCB9D72}]
    Check controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_TXHANDLER);
  }

  /* [cover parentID={8C41E1A6-5BEE-4e72-9C00-77756DA559FD}]
  Is Ctrl Init done ?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* if the DMA channel number is more than the supported channels or
     * if the DMA channel is not used */
    /* [cover parentID={6D22B009-A407-413c-8036-ED34717BDC48}]
    Is DmaChnl input parameter valid?
    [/cover] */
    if ((DmaChnlIdx >= ETH_17_GETHMACV2_MAXCHLS_SUPPORTED) ||
        (ETH_17_GETHMACV2_NONCFG_PRIORITY ==
          EthLocalCtrlCfgPtr->EthTxChnlFifoMapPtr[DmaChnlIdx]))
    {
      /* [cover parentID={8A619114-41CD-4a6e-8207-12E2602D3CCE}]
      Report Invalid Param dev error
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                ETH_17_GETHMACV2_INSTANCE_ID,
                ETH_17_GETHMACV2_SID_TXHANDLER, ETH_17_GETHMACV2_E_INV_PARAM);
    }
    else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
    {
      EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

      /* [cover parentID={0E6B6386-9DBA-4b81-9061-CEA91681EFC8}]
      Read DMA_CH[ChnlIdx]_STATUS register to check Tx Interrupt(TI) bit
      [/cover] */
      /* [cover parentID={7419A90A-CAD7-4ef9-9B93-ADA81437562C}]
      Is Tx Interrupt(TI) bit set in DMA_CH[ChnlIdx]_STATUS register ?
      [/cover] */
      if (EthCtrlAddPtr->DMA_CH[DmaChnlIdx].STATUS.B.TI ==
                                              ETH_17_GETHMACV2_SET)
      {
        /* [cover parentID={B5A2B412-DF6D-4832-B3B1-F2B8A9047368}]
        Clear Tx Interrupt(TI) bit in DMA_CH[ChnlIdx]_STATUS register
        [/cover] */
        EthCtrlAddPtr->DMA_CH[DmaChnlIdx].STATUS.U = (uint32)
                         ((uint32)ETH_17_GETHMACV2_DMA_CH_STAT_TI_RESET |
                          (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_NIS_RESET);

        /* [cover parentID={9A776059-5C83-43f5-9F8E-FB4EEE40FF73}]
        Confirm all successfully transmitted frames to application
        [/cover] */
        /* Local function to confirm all successfully transmitted frames */
        Eth_17_GEthMacV2_lIntConfirmTxFrames(CtrlIdx, DmaChnlIdx);
      }
    }
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  }
#endif
}
#endif  /* (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON) */

#if (ETH_17_GETHMACV2_RX_IRQHDLR == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A867CD67-787E-4746-BC08-18737DCF772E}]  **
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
void Eth_17_GEthMacV2_RxDmaIrqHdlr(const uint8 CtrlIdx, const uint8 DmaChnlIdx)
{
  Ifx_GETH *EthCtrlAddPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint8 FifoIdx;
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError;
#endif

  /* [cover parentID={9A64490D-B684-49dc-9077-B8F48A2828D4}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={BC90DF65-8312-482f-934E-9AC6088A8457}]
  Check if Eth_17_GEthMacV2_Init is successful
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                        ETH_17_GETHMACV2_SID_RXHANDLER);

  /* [cover parentID={4FF91EA3-DCBE-41aa-8A5E-263180C83DDE}]
  If Init was successful ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={ED1AF082-921F-4260-B764-21AED2675891}]
    Check If Control Index is valid
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                                  CtrlIdx, ETH_17_GETHMACV2_SID_RXHANDLER);
  }
  /* [cover parentID={FA3D9A60-2D4F-4bdd-948E-0BF6BDAF7118}]
  Is Ctrl Index Valid ?
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={BBC90998-28F3-4eaa-B0A6-4234D383642D}]
    Check controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_RXHANDLER);
  }

  /* [cover parentID={BCAC096A-264D-4fb4-B361-AFE14F11CBF5}]
  Is Ctrl Init done ?
  [/cover] */
  if (DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

    /* if the DMA channel number is more than the supported channels or
     * if the DMA channel is not used */
    /* [cover parentID={3D176D4E-4EFA-4652-A5C5-FA4280539E07}]
    Is DmaChnl input parameter valid?
    [/cover] */
    if ((DmaChnlIdx >= ETH_17_GETHMACV2_MAXCHLS_SUPPORTED) ||
        (ETH_17_GETHMACV2_NONCFG_PRIORITY ==
          EthLocalCtrlCfgPtr->EthRxChnlFifoMapPtr[DmaChnlIdx]))
    {
      /* [cover parentID={40A3748B-B863-4d6f-83DD-277FC683F42F}]
      Report Invalid Param dev error
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                ETH_17_GETHMACV2_INSTANCE_ID,
                ETH_17_GETHMACV2_SID_RXHANDLER, ETH_17_GETHMACV2_E_INV_PARAM);
    }
    else
#endif /* End of ETH_17_GETHMACV2_DEV_ERROR_DETECT */
    {
      EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

      /* Get controller status */
      EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

      /* Get controller configuration data */
      EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

      FifoIdx = EthLocalCtrlCfgPtr->EthRxChnlFifoMapPtr[DmaChnlIdx];

      /* [cover parentID={0E9315C7-C885-4a38-9ED6-3D6C42BA50FF}]
      Read DMA_CH[ChnlIdx]_STATUS register to check Rx Interrupt(RI) bit
      [/cover] */
      /* [cover parentID={87B6F3E5-093C-43da-AAB8-006E9EA20BC4}]
      Is Rx Interrupt(RI) bit or Receive buffer unavailable(RBU) bit set in
      DMA_CH[ChnlIdx]_STATUS register ?
      [/cover] */
      /* Read DMA channel Status to check Receive Interrupt bit */
      /* MISRA2012_RULE_13_5_JUSTIFICATION: Or operator required to check the RI
      and RBU bits of the SFR. This warning is due to the volatile
      qualifier in the SFRs and no side-affect foreseen by violation.*/
      if ((EthCtrlAddPtr->DMA_CH[DmaChnlIdx].STATUS.B.RI ==\
              ETH_17_GETHMACV2_SET) || (EthCtrlAddPtr->\
              DMA_CH[DmaChnlIdx].STATUS.B.RBU == ETH_17_GETHMACV2_SET))
      {
        /* [cover parentID={E26125DF-E650-4b44-BA72-409A7447AD6B}]
        Clear Rx Interrupt(RI) bit  or the RBU bit in DMA_CH[ChnlIdx]_STATUS register
        [/cover] */
        EthCtrlAddPtr->DMA_CH[DmaChnlIdx].STATUS.U = (uint32)
                    ((uint32)ETH_17_GETHMACV2_DMA_CH_STAT_RI_RESET |
                     (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_NIS_RESET |
                     (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_RBU_ERI_AIE_RESET);

        /* [cover parentID={8D066E91-D1F9-44a1-AF6F-B30404052AC7}]
        Process the received frame and notify the application
        [/cover] */
        /* Local function to notify received frames */
        (void)Eth_17_GEthMacV2_lReceiveFrames(CtrlIdx, FifoIdx);

        /* [cover parentID={81B11D15-31FD-4502-BA68-913D18403E83}]
        Issue Poll demand command for the indexed channel of Receive DMA
        [/cover] */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
        integer type is performed to align last buffer address to tail pointer
        register. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
        is performed to to assign last buffer address to tail pointer
        register. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        EthCtrlAddPtr->DMA_CH[DmaChnlIdx].RXDESC_TAIL_POINTER.U =\
         (uint32)(&EthLocalCoreStatusPtr->EthBuffDescPtr->\
           EthDmaRxDescPtr[FifoIdx]\
            [EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].NumOfRxBuffers]);
      }
    }
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
  }
#endif
}
#endif /* (ETH_17_GETHMACV2_RX_IRQHDLR == STD_ON) */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={8C596208-63DA-4d86-9AF5-B625FCB35996}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lStartTxRx(const           **
**                   Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)**
**                                                                            **
** Description      : Function to start Tx and Rx in MAC and DMA core         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lStartTxRx(const
                     Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint8 ChnlsUsed;
  uint8 LoopCnt;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  ChnlsUsed = EthCtrlCfgPtr->EthNumRxChnls;

  /* Start Reception on required Rx-DMA channels */
  /* [cover parentID={B830DBB2-5BC9-4f57-A5B1-1726CE235F4A}]
  Loop for the number of required Rx channels
  [/cover] */
  for (LoopCnt = 0; LoopCnt < ChnlsUsed; LoopCnt++)
  {
    /* [cover parentID={8652AE3A-9391-428f-9395-F130C9F73BFA}]
    Start Reception on selected Rx-DMA channel
    [/cover] */
    EthCtrlAddPtr->DMA_CH[LoopCnt].RX_CONTROL.B.SR = ETH_17_GETHMACV2_ENABLE;

    /* Insert delay for back to back register writes */
    Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(EthCtrlCfgPtr->EthBkRegWrWaitTime);

    /* [cover parentID={55865F50-8A66-4f1d-BD6D-DA7B93E72CFC}]
    Disable the queue packet flush after starting the receive process
    [/cover] */
    EthCtrlAddPtr->DMA_CH[LoopCnt].RX_CONTROL.B.RPF = ETH_17_GETHMACV2_DISABLE;
  }

  ChnlsUsed = EthCtrlCfgPtr->EthNumTxChnls;

  /* Start Transmission on required Tx-DMA channels */
  /* [cover parentID={22C22201-FA16-4a45-9D26-DF75F7F81B10}]
  Loop for the number of required Tx channels
  [/cover] */
  for (LoopCnt = 0; LoopCnt < ChnlsUsed; LoopCnt++)
  {
    /* [cover parentID={6CD46448-D3B3-465f-BA55-C06D40DDBBC6}]
    Start Transmission on selected Tx-DMA channel
    [/cover] */
    EthCtrlAddPtr->DMA_CH[LoopCnt].TX_CONTROL.B.ST = ETH_17_GETHMACV2_ENABLE;
  }

  /* [cover parentID={2AD9E8E1-12A0-4e81-9E69-BF270C189579}]
  Enable MAC Transmitter and Receiver
  [/cover] */
  EthCtrlAddPtr->MAC_CONFIGURATION.U = (EthCtrlAddPtr->MAC_CONFIGURATION.U |
                               (uint32)ETH_17_GETHMACV2_MAC_TXRX_ENABLEMASK);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C39ECB20-511B-4fdf-8EB4-65471D02D7B9}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lStopTxRx(const  **
**                   Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)**
**                                                                            **
** Description      : Function to stop Tx and Rx in MAC and DMA core          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: Tx and Rx stopped in MAC and DMA **
**                                   - E_NOT_OK: Timeout error during Tx queue**
**                                                 flush operation            **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lStopTxRx(const
               Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetVal;
  uint8 ChnlsUsd;
  uint8 LoopCnt;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  ChnlsUsd = EthCtrlCfgPtr->EthNumTxChnls;

  /* Stop Transmission on the required DMA Channels */
  /* [cover parentID={E2786CE1-A6DC-42e4-88C3-B4774B4B5B0F}]
  Loop for the number of required Tx channels
  [/cover] */
  for (LoopCnt = 0; LoopCnt < ChnlsUsd; LoopCnt++)
  {
    /* [cover parentID={871E4EC4-DB6F-4254-8BC2-8ECC448A710C}]
    Stop Transmission on the selected DMA Channel
    [/cover] */
    EthCtrlAddPtr->DMA_CH[LoopCnt].TX_CONTROL.B.ST = ETH_17_GETHMACV2_DISABLE;
  }

  /* [cover parentID={6A121458-AC96-43ad-B9DE-AEE7AE020E57}]
  Flush the transmit queues
  [/cover] */
  RetVal = Eth_17_GEthMacV2_lTxQFlush(EthCtrlCfgPtr);

  /* [cover parentID={F8A4747F-290D-4851-A1E0-941B45CB29B4}]
  Any error during Tx queue flush operation?
  [/cover] */
  if (RetVal == E_OK)
  {
    /* [cover parentID={2DF7B663-BE3B-432d-A896-C7A266445D98}]
    Disable MAC Transmitter and Receiver
    [/cover] */
    EthCtrlAddPtr->MAC_CONFIGURATION.U = (EthCtrlAddPtr->MAC_CONFIGURATION.U &
                               (uint32)ETH_17_GETHMACV2_MAC_TXRX_DISABLEMASK);

    ChnlsUsd = EthCtrlCfgPtr->EthNumRxChnls;

    /* Stop Reception on required DMA Channels */
    /* [cover parentID={1FD59159-0F89-4a19-8DDA-495C69EAC0D0}]
    Loop for the number of required Rx channels
    [/cover] */
    for (LoopCnt = 0; LoopCnt < ChnlsUsd; LoopCnt++)
    {
      /* [cover parentID={4A66B379-C58A-42ba-B19D-28F0CEC24339}]
      Enable the receive queue packet flush operation
      [/cover] */
      /* This packet flush operation flushes the packet from the Rx queues
      destined to the DMA Rx channel when it is stopped. Also, the packets in
      the Rx Queues that were received when this Rx DMA was stopped,
      get flushed out when the Rx DMA is re-started */
      EthCtrlAddPtr->DMA_CH[LoopCnt].RX_CONTROL.B.RPF = ETH_17_GETHMACV2_ENABLE;

      /* Insert delay for back to back register writes */
      Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(EthCtrlCfgPtr->EthBkRegWrWaitTime);

      /* [cover parentID={4525490E-FF2C-4ea0-8EE8-6171ED2B8AB7}]
      Stop Reception on the selected DMA Channel
      [/cover] */
      EthCtrlAddPtr->DMA_CH[LoopCnt].RX_CONTROL.B.SR = ETH_17_GETHMACV2_DISABLE;
    }
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C4BD64FB-86EC-4265-9321-A31B3243AE75}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lCheckForCtrlModeChange (  **
**                    const uint8 CtrlIdx, Eth_17_GEthMacV2_CtrlStatusType    **
**                                          * const EthLocalCoreStatusPtr)    **
**                                                                            **
** Description      : The function checks polling state changes.              **
**                    Calls EthIf_CtrlModeIndication when the                 **
**                    controller mode changed.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    EthLocalCoreStatusPtr - Pointer to controller status    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lCheckForCtrlModeChange(const uint8 CtrlIdx,
              Eth_17_GEthMacV2_CtrlStatusType* const EthLocalCoreStatusPtr)
{
  /* [cover parentID={E15C6CFC-6ADE-4d8a-8FD8-9E04156CE23A}]
  Current Controller mode Not Equal to Previous Controller mode
  [/cover] */
  if (EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode !=
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode)
  {
    /* [cover parentID={F5AD7421-9727-4e1a-8AE1-DA211AF759A9}]
    Indicate Controller mode change status to EthIf
    [/cover] */
    EthIf_CtrlModeIndication(CtrlIdx, EthLocalCoreStatusPtr->
                                      EthRunTimeOpertnData.EthControllerMode);

    EthLocalCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode =
        EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={57697DBC-1079-4fa3-BAB3-A863A99BDCA0}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lConfirmTxFrames(          **
**                                                 const uint8 CtrlIdx)       **
**                                                                            **
** Description      : check transmit buffers and confirm transmitted frames   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lConfirmTxFrames(const uint8 CtrlIdx)
{
  Eth_17_GEthMacV2_TxBuffTableType *TxBuffTablePtr;
  Eth_17_GEthMacV2_TxDescBufMapStType *TxDescTablePtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint32 DescStatus;
  uint16 TxBufTotal;
  uint16 Count;
  uint16 TxBufIdx;
  uint16 TxDescCnfrmIdx;
  uint8 LoopCnt;
  uint8 FifoIdx;
  uint8 ChnlsUsd;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  /* Get the number of Tx channels used */
  ChnlsUsd = EthLocalCtrlCfgPtr->EthNumTxChnls;

  /* [cover parentID={080CF434-4A3A-4da8-B464-C9FCE03142DA}]
  Loop for the number of configured FIFOs
  [/cover] */
  for (LoopCnt = 0U; LoopCnt < ChnlsUsd; LoopCnt++)
  {
    TxBufTotal = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[LoopCnt].NumOfTxBuffers;

    FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[LoopCnt].TxFifoIdx;

    /* Start scanning all Tx Buffers within a FIFO */
    /* [cover parentID={31CBC514-3A35-4246-B516-BE3AC64A7B8C}]
    [/cover] */
    for (Count = 0U; Count < TxBufTotal; Count++)
    {
      /* [cover parentID={685D99A7-831D-4f54-AFC0-E712F97A6B4D}]
      [/cover] */
      /* [cover parentID={1F52B6BB-B569-4b44-8094-A54CBD09A05B}]
      [/cover] */
      /* [cover parentID={6F1200D7-8752-4f1b-9862-8F0CC9D58FED}]
      Enter the critical section
      [/cover] */
      SchM_Enter_Eth_17_GEthMacV2_TxDescData();

      TxDescCnfrmIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
                          EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx;

      TxDescTablePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                            EthTxDescBufMapStPtr[FifoIdx][TxDescCnfrmIdx]);

      DescStatus = EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr
                    [FifoIdx][TxDescCnfrmIdx].TDES3;

      TxBufIdx = TxDescTablePtr->TxDescBufMapIdx;

      TxBuffTablePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                             EthTxBuffTablePtr[FifoIdx][TxBufIdx]);

      /* [cover parentID={6F4F9201-745D-4d4d-BC71-533B54961BD4}]
      Buffer Status is USED_TXINITIATED and Transmission is INITIATED and
      Buffer is RELEASED by DMA
      [/cover] */
      if((TxBuffTablePtr->BuffStatus ==
                          ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED) &&
         (TxDescTablePtr->FrameTxInitiated == ETH_17_GETHMACV2_ENABLE) &&
         ((DescStatus & (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_OWN_SET) ==
                                              ETH_17_GETHMACV2_DESC_RELEASED))
      {
        /* [cover parentID={EE56A66C-4266-4767-B136-8530F6591A3A}]
        Tx confirmation requested status in buffer table is REQUESTED
        [/cover] */
        /* Check if confirmation requested before in Eth_Transmit() API.*/
        if (TxDescTablePtr->TxConfirmReq == ETH_17_GETHMACV2_ENABLE)
        {
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
          /* store the descriptor index where the time stamp can be checked */
          EthLocalCoreStatusPtr->EthBuffDescPtr->
           EthRunTmTxChnlDataPtr[FifoIdx].TxDmaDescIdxTmStmp = TxDescCnfrmIdx;
#endif

          /* Check for presence of any error during transmit operation */
          /* [cover parentID={1921C492-DBAB-497b-99EB-7BF2AA65D82A}]
          [/cover] */
          if ((DescStatus & (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_ERROR_MASK) ==
                                                    ETH_17_GETHMACV2_NO_ERROR)
          {
            /* [cover parentID={8ECD2F1E-56F8-421f-81C9-0D79E823A54C}]
            Call EthIf Tx Confirmation function with E_OK for
            ConfirmTx Buffer Index
            [/cover] */
            EthIf_TxConfirmation(CtrlIdx,
             (Eth_BufIdxType)(((uint32)LoopCnt << ETH_17_GETHMACV2_FIFOIDX_POS)
                                                      | TxBufIdx), E_OK);
          }
          else
          {
            /* [cover parentID={E5B491BD-4F61-496c-A6E2-A005AF141968}]
            Call EthIf Tx Confirmation function with E_NOT_OK for
            ConfirmTx Buffer Index
            [/cover] */
            EthIf_TxConfirmation(CtrlIdx,
             (Eth_BufIdxType)(((uint32)LoopCnt << ETH_17_GETHMACV2_FIFOIDX_POS)
                                                      | TxBufIdx), E_NOT_OK);
          }

          /* Reset Tx confirmation request. */
          TxDescTablePtr->TxConfirmReq = ETH_17_GETHMACV2_DISABLE;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
          /* Reset the descriptor index to invalid value, as it is invalid for
           * the next TxConfirmation */
          EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].
                          TxDmaDescIdxTmStmp = ETH_17_GETHMACV2_DMADESC_INVALID;
#endif
        }
        /* [cover parentID={15204064-EE39-4157-AF42-166FE5E0C88E}]
        Reset Frame Tx Request status as Transmission NOT INITIATED and Set
        Buffer status as FREE
        [/cover] */
        /*Clear Frame Tx Request Indication */
        TxDescTablePtr->FrameTxInitiated = ETH_17_GETHMACV2_DISABLE;

        /* Release the buffer to application use */
        TxBuffTablePtr->BuffStatus = ETH_17_GETHMACV2_BUFFER_NOTUSED;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        /* Reset the timestamp enable flag */
        TxBuffTablePtr->TimeStampEnable = ETH_17_GETHMACV2_DISABLE;
#endif

        /* [cover parentID={757C7AFE-0529-475e-ADBE-7F821E889F76}]
        Add the buffer index into the queue indicating availability
        [/cover] */
        Eth_17_GEthMacV2_lAddQElem(TxBufIdx, EthLocalCoreStatusPtr->
          EthBuffDescPtr->EthTxBuffQueuePtr[FifoIdx], &(EthLocalCoreStatusPtr->
          EthBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront),
          &(EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear), EthLocalCtrlCfgPtr->
          EthTxFifoCfgPtr[LoopCnt].NumOfTxBuffers);

        /* Point to next buffer in the buffer ring */
        EthLocalCoreStatusPtr->EthBuffDescPtr->
            EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx =
        Eth_17_GEthMacV2_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthBuffDescPtr->
                EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx, TxBufTotal);

        /* [cover parentID={A832A070-2C5A-4510-B690-F8CA2CB73B18}]
        Exit the critical section
        [/cover] */
        SchM_Exit_Eth_17_GEthMacV2_TxDescData();
      }
      else
      {
        /* [cover parentID={A832A070-2C5A-4510-B690-F8CA2CB73B18}]
        Exit the critical section
        [/cover] */
        SchM_Exit_Eth_17_GEthMacV2_TxDescData();

        /* Buffer unused or not released by DMA, break for Loop */
        break;
      }
    }
  }
}

#if (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3F4A6028-5904-4d21-AC4B-FD576596E692}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lIntConfirmTxFrames(       **
**                               const uint8 CtrlIdx, const uint8 Channel)    **
**                                                                            **
** Description      : check transmit buffers and confirm transmitted frames   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    Channel - The channel on which the interrupt is         **
**                                generated                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lIntConfirmTxFrames(const uint8 CtrlIdx,
                                                 const uint8 Channel)
{
  Eth_17_GEthMacV2_TxBuffTableType *TxBuffTablePtr;
  Eth_17_GEthMacV2_TxDescBufMapStType *TxDescTablePtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint32 DescStatus;
  uint16 Count;
  uint16 TxBufTotal;
  uint16 TxBufIdx;
  uint16 TxDescCnfrmIdx;
  uint8 FifoIdx;
  uint8 PrioMapIdx;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  PrioMapIdx = EthLocalCtrlCfgPtr->EthTxChnlFifoMapPtr[Channel];

  TxBufTotal = EthLocalCtrlCfgPtr->
                    EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers;

  FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioMapIdx].TxFifoIdx;

  /* [cover parentID={B4CB6143-62F9-42e9-A1E3-9719DE911914}]
  Start scanning all Tx Buffers
  [/cover] */
  for (Count = 0U; Count < TxBufTotal; Count++)
  {
    /* [cover parentID={E5C8A42C-3EB4-40ed-B681-338E6AA79118}]
    [/cover] */
    /* [cover parentID={74E18F58-93EC-4d85-96E7-E0C67A02871C}]
    [/cover] */
    /* [cover parentID={250A1A88-7940-454f-BEEA-ED3B6BB851EA}]
    Enter the critical section
    [/cover] */
    SchM_Enter_Eth_17_GEthMacV2_TxDescDataISR();

    TxDescCnfrmIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
                      EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx;

    TxDescTablePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                            EthTxDescBufMapStPtr[FifoIdx][TxDescCnfrmIdx]);

    DescStatus = EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr
                   [FifoIdx][TxDescCnfrmIdx].TDES3;

    TxBufIdx = TxDescTablePtr->TxDescBufMapIdx;

    TxBuffTablePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                            EthTxBuffTablePtr[FifoIdx][TxBufIdx]);

    /* [cover parentID={BB4E45E3-82AF-4804-BB29-F6B7787C8666}]
    Buffer Status is USED_TXINITIATED and Transmission is INITIATED and Buffer
    is RELEASED by DMA
    [/cover] */
    if((TxBuffTablePtr->BuffStatus ==
                        ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED) &&
       (TxDescTablePtr->FrameTxInitiated == ETH_17_GETHMACV2_ENABLE) &&
       ((DescStatus & (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_OWN_SET) ==
                                              ETH_17_GETHMACV2_DESC_RELEASED))
    {
      /* [cover parentID={1E3A3E83-448B-48f3-820C-B2131FDEF86A}]
      Tx confirmation requested status in buffer table is REQUESTED
      [/cover] */
      /* Check if confirmation requested before in Eth_Transmit() API.*/
      if (TxDescTablePtr->TxConfirmReq == ETH_17_GETHMACV2_ENABLE)
      {
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        /* store the descriptor index where the time stamp can be checked */
        EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].TxDmaDescIdxTmStmp = TxDescCnfrmIdx;
#endif
        /* [cover parentID={6A34269F-BFB9-433e-8B9E-4E02FF2F437E}]
        Any error detected during transmission?
        [/cover] */
        /* Check for presence of any error during transmit operation */
        if ((DescStatus & (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_ERROR_MASK) ==
                                                    ETH_17_GETHMACV2_NO_ERROR)
        {
          /* [cover parentID={E4990C68-6A55-471b-AFD7-64355EB60D49}]
          Call EthIf Tx Confirmation function with E_OK for
          ConfirmTx Buffer Index
          [/cover] */
          EthIf_TxConfirmation(CtrlIdx,
           (Eth_BufIdxType)(((uint32)PrioMapIdx << ETH_17_GETHMACV2_FIFOIDX_POS)
                                                    | TxBufIdx), E_OK);
        }
        else
        {
          /* [cover parentID={095A128C-5835-4e6e-8981-4C18AD6672A9}]
          Call EthIf Tx Confirmation function with E_NOT_OK for
          ConfirmTx Buffer Index
          [/cover] */
          EthIf_TxConfirmation(CtrlIdx,
           (Eth_BufIdxType)(((uint32)PrioMapIdx << ETH_17_GETHMACV2_FIFOIDX_POS)
                                                    | TxBufIdx), E_NOT_OK);
        }

        /* Reset Tx confirmation request. */
        TxDescTablePtr->TxConfirmReq = ETH_17_GETHMACV2_DISABLE;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        /* Reset the descriptor index to invalid value, as it is invalid for
         * the next TxConfirmation */
        EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].
                        TxDmaDescIdxTmStmp = ETH_17_GETHMACV2_DMADESC_INVALID;
#endif
      }

      /* [cover parentID={9BD65109-7B85-4fb8-8425-1EE1F2277DD5}]
      Clear Frame Tx Request Indication, Release the buffer to application use.
      [/cover] */
      /*Clear Frame Tx Request Indication */
      TxDescTablePtr->FrameTxInitiated = ETH_17_GETHMACV2_DISABLE;

      /* Release the buffer to application use */
      TxBuffTablePtr->BuffStatus = ETH_17_GETHMACV2_BUFFER_NOTUSED;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
      /* Reset the timestamp enable flag */
      TxBuffTablePtr->TimeStampEnable = ETH_17_GETHMACV2_DISABLE;
#endif

      /* [cover parentID={6981CA29-3ACC-44d2-B95F-1C97E1ED4586}]
      Add the buffer index into the queue indicating availability and
      Point to next buffer in the buffer ring
      [/cover] */
      /* Add the buffer index into the queue indicating availability */
      Eth_17_GEthMacV2_lAddQElem(TxBufIdx, EthLocalCoreStatusPtr->
        EthBuffDescPtr->EthTxBuffQueuePtr[FifoIdx], &(EthLocalCoreStatusPtr->
        EthBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront),
        &(EthLocalCoreStatusPtr->EthBuffDescPtr->
        EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear), EthLocalCtrlCfgPtr->
        EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers);

      EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx =
        Eth_17_GEthMacV2_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthBuffDescPtr->
              EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx, TxBufTotal);

      /* [cover parentID={8B770D30-582E-45d8-9595-F9E9779C5023}]
      Exit the critical section
      [/cover] */
      SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR();
    }
    else
    {
      /* [cover parentID={8B770D30-582E-45d8-9595-F9E9779C5023}]
      Exit the critical section
      [/cover] */
      SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR();

      /* Buffer unused or not released by DMA, break for Loop */
      break;
    }
  }
}
#endif  /* (ETH_17_GETHMACV2_TX_IRQHDLR == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B268F0FB-2C56-4445-B3CF-827B5EB216F1}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lReceiveFrames(           **
**                                                  const uint8 CtrlIdx,      **
**                                                  const uint8 FifoIdx)      **
**                                                                            **
** Description      : Function to scan all Rx Buffers within a FIFO for       **
**                      new Frames                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    FifoIdx - FIFO Index                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint8 :                                                 **
**                    ETH_17_GETHMACV2_FRM_RECEIVED: New frame received       **
**                    ETH_17_GETHMACV2_FRM_NOTRECEIVED: Frame not received    **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lReceiveFrames(const uint8 CtrlIdx,
                                             const uint8 FifoIdx)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
#else
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
#endif
  Eth_17_GEthMacV2_DmaRxDescType *EthLocalDmaRxDescPtr;
  const volatile uint8 *RxBuffBasePtr;
  uint8 *CurrentBufferPtr;
  const uint8 *EthSourceAddr;
#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  uint32 DescStatRDES1;
  uint32 ConxtDescRDES3;
  uint16 ConxtDescPosition;
#endif
  uint32 DescStatRDES3;
  uint16 RxLength;
  uint16 FrameType;
  uint16 RxBufLengthAligned;
  uint16 RxBufTotal;
  uint16 RxBufClrStrtIdx;
  uint16 BufferCount;
  uint8 TempVar;
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  Std_ReturnType RetVal;
#endif
  uint8 IntEnabled;
  uint8 CrcStripEnabled;
  uint8 BufferClearCount;
  uint8 ApplIndication;
  boolean BroadcastState;

  /*ApplIndication is set to zero*/
  ApplIndication = (uint8)ETH_17_GETHMACV2_FRM_NOTRECEIVED;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                                EthDmaRxDescPtr[FifoIdx];

  /* Get the number of Rx buffers configured for the FIFO */
  RxBufTotal = EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].NumOfRxBuffers;

  IntEnabled = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties >>
                    ETH_17_GETHMACV2_RXINT_POS) & ETH_17_GETHMACV2_RXINT_MSK);

  RxBufLengthAligned = EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].
                                                   RxBufferAlignSize;

  RxBuffBasePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                      EthRxBufferPtr[FifoIdx][0U]);

  /* Info: For receive operation descriptors are configured to store exactly
     one ethernet frame.
     i.e received frames are not spread across multiple descriptors, If length
     of the received frame is greater than length of the descriptor then these
     frames are not received. */
  /* [cover parentID={07BA9E36-D632-48d8-B33F-76D03E09B240}]
  Loop to scan all Rx buffers
  [/cover] */
  /* [cover parentID={CF2B0862-7009-4f80-95AC-659695E9548B}]
  [/cover] */
  for(BufferCount = 0U; BufferCount < RxBufTotal; BufferCount++)
  {
    /* Read DMA Rx Descriptor status from RDES3 of Eth_CurrRxDmaDescIdx. */
    DescStatRDES3 = EthLocalDmaRxDescPtr[EthLocalCoreStatusPtr->EthBuffDescPtr->
             EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx].RDES3;

    /* Check if Rx buffer of current Eth_CurrRxDmaDescIdx is released by DMA.
    Info: In polling mode, only one Rx notification is given per call of
    Eth_Receive.
    Note: In interrupt mode, Rx notification is given for all received packet
    currently */
    /* BufferClearCount variable counts number of buffers to be released.
    Initialized to zero here */
    BufferClearCount = 0U;

    /* [cover parentID={B1EB9AA7-8455-459a-99FD-48DBE138C4DF}]
    Rx buffer is released by DMA and No Rx notification is called ( in polling
    mode, only one Rx notification is given per call of Eth_Receive API)
    or Rx interrupt is enabled
    [/cover] */
    if (((DescStatRDES3 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET) ==
          ETH_17_GETHMACV2_DESC_RELEASED) &&
          (((IntEnabled == ETH_17_GETHMACV2_DISABLE) &&
          (ApplIndication == ETH_17_GETHMACV2_FRM_NOTRECEIVED)) ||
          (IntEnabled == ETH_17_GETHMACV2_ENABLE)))
    {
      /* BufferClearCount incremented to release one descriptor */
      BufferClearCount++;

      RxBufClrStrtIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
              EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx;

      /* Check if first Descriptor bit (FD) and Last Descriptor bit (LD)
                                           is set for Eth_CurrRxDmaDescIdx.*/
      /* [cover parentID={661AD280-7C14-4d70-B753-6C74C4229D29}]
      [/cover] */
      if (((DescStatRDES3 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_FD_LD_SET) ==
           (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_FD_LD_SET))
      {
        /* [cover parentID={7AC6724D-89C7-42b3-B8B9-658E85A39F60}]
        [/cover] */
        /* Get length of the received frame */
        RxLength = (uint16)(DescStatRDES3 &
                              (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_PL_MASK);

        /* get pointer to the received data buffer */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
        pointer type is performed to fetch buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
        is performed to access the buffer address from DMA descriptor.
        This is the intended design and valid as per DMA hardware design.
        There are no side effects seen by violating this rule.*/
        /* [cover parentID={6350953D-5EBD-40ef-8512-26CDCD433E64}]
        Extract packet length, frame type, broadcast state
        and time stamp availability status
        [/cover] */
        CurrentBufferPtr = (uint8*)EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES0;

        /* [cover parentID={81873DC9-26D1-4c39-8092-A302BF6CD553}]
        Check if frame received is broadcast
        [/cover] */
        BroadcastState = Eth_17_GEthMacV2_lIsBroadcastAddress(
                     &(CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_DESTADDR_POS]));

        EthSourceAddr = &(CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_SRCADDR_POS]);

        /* [cover parentID={30456F2D-20CF-482d-BEC0-BE0F81CB7D50}]
        Switch management support Enabled
        [/cover] */
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
        EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmRxChnlDataPtr[FifoIdx].SwtRxDataPtr =
              &(CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS]);

        EthLocalCoreStatusPtr->EthBuffDescPtr->
                  EthRunTmRxChnlDataPtr[FifoIdx].SwtRxLength = RxLength;

        /* [cover parentID={7EFB5D68-B7D9-44d2-BC85-079661CC3CEB}]
        Call EthSwt_EthRxProcessFrame API to process Rx frame
        [/cover] */
        RetVal = EthSwt_EthRxProcessFrame(CtrlIdx,
                  (((uint32)FifoIdx << ETH_17_GETHMACV2_FIFOIDX_POS) |
                   RxBufClrStrtIdx), &EthLocalCoreStatusPtr->EthBuffDescPtr->
                   EthRunTmRxChnlDataPtr[FifoIdx].SwtRxDataPtr,
                   &EthLocalCoreStatusPtr->EthBuffDescPtr->
                 EthRunTmRxChnlDataPtr[FifoIdx].SwtRxLength,
                   &EthLocalCoreStatusPtr->EthBuffDescPtr->
                 EthRunTmRxChnlDataPtr[FifoIdx].SwtMgmtFrameOnly);

        /* [cover parentID={866CCDCF-A569-45eb-B586-E477EB10A6A6}]
        Is previous API call executed successfully?
        [/cover] */
        if (RetVal == E_OK)
        {
          /* [cover parentID={359B1376-F916-48e7-A646-3AF877895376}]
          Check the validity of the parameters modified by the EthSwt driver API
          [/cover] */
          RetVal = Eth_17_GEthMacV2_lChkSwtRxFrmParam(RxLength,
                    EthLocalCoreStatusPtr->EthBuffDescPtr->
                     EthRunTmRxChnlDataPtr[FifoIdx].SwtRxLength,
                    EthLocalCoreStatusPtr->EthBuffDescPtr->
                     EthRunTmRxChnlDataPtr[FifoIdx].SwtRxDataPtr,
                    CurrentBufferPtr);
        }

        /* [cover parentID={3C0F0B8A-7E40-4b01-AFBE-36B86C1730EF}]
        Is any error occured due to previous check?
        [/cover] */
        if (RetVal == E_OK)
        {
          /* Mark one indication to application done - used in polling mode*/
          ApplIndication = ETH_17_GETHMACV2_FRM_RECEIVED;

        /* if the frame is for only Management purpose, do not invoke the
           Rx indication function */
        /* [cover parentID={155C2609-1028-4bc2-AE5D-0BCE50CA2927}]
        if the received frame is for only Management purpose
        [/cover] */
        if (EthLocalCoreStatusPtr->EthBuffDescPtr->
               EthRunTmRxChnlDataPtr[FifoIdx].SwtMgmtFrameOnly == FALSE)
#endif /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */
        {
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
          /* Adjust the address offset with the management info length */
          /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
          pointer type is performed to adjust the address offset with the
          management info length that is extracted by the EthSwt API. There are
          no side effects seen by violating this rule.*/
          /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
          expression is performed to adjust the address offset with the
          management info length that is extracted by the EthSwt API. There are
          no side effects seen by violating this rule.*/
          /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to
          pointer is performed to adjust the address offset with the
          management info length that is extracted by the EthSwt API. There are
          no side effects seen by violating this rule.*/
          CurrentBufferPtr = (uint8*)((uint32)CurrentBufferPtr +\
                (uint32)(RxLength - EthLocalCoreStatusPtr->EthBuffDescPtr->\
                          EthRunTmRxChnlDataPtr[FifoIdx].SwtRxLength));

          RxLength = EthLocalCoreStatusPtr->EthBuffDescPtr->
                       EthRunTmRxChnlDataPtr[FifoIdx].SwtRxLength;
#else
          /* Mark one indication to application done - used in polling mode*/
          ApplIndication = ETH_17_GETHMACV2_FRM_RECEIVED;
#endif /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)

          /* Reset time stamp availability as Not Available*/
          /* [cover parentID={4F4CACFD-7AF8-4a7e-936D-880DDDE98093}]
          Reset time stamp availability as Not Available
          [/cover] */
          EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmRxChnlDataPtr[FifoIdx].
                          RxDmaDescIdxTmStmp = ETH_17_GETHMACV2_DMADESC_INVALID;

        /* Read RDES1 to get time stamp availability status */
        DescStatRDES1 = EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES1;

        /* Check if the time stamp is available for the current frame.*/
        /* [cover parentID={7655BB80-CCB4-43d9-8C7D-2F61C1395DDC}]
        Time stamp is available for this current received frame
        [/cover] */
        if((DescStatRDES1 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_TSA_SET) ==
                                 (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_TSA_SET)
        {
          /* Increment Eth_CurrRxDmaDescIdx,next is a context descriptor
          Info :Context descriptor is used only for time stamp storage,
          Buffer assigned to this descriptor will not be used. Next packet
          will be stored to buffer of descriptor after this context
          descriptor. Hence,increment Current Rx Dma descriptor index */
          ConxtDescPosition =
            Eth_17_GEthMacV2_lIncrRxBufIdx(RxBufClrStrtIdx, RxBufTotal);

          EthLocalCoreStatusPtr->EthBuffDescPtr->
                        EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx =
                                                            ConxtDescPosition;

          /* BufferClearCount incremented to release context descriptor */
          BufferClearCount++;

          ConxtDescRDES3 = EthLocalDmaRxDescPtr[ConxtDescPosition].RDES3;

          /* [cover parentID={887BAC49-3A82-42fe-A16C-BB040D5633C9}]
          Check if timestamp is available in the context descriptor
          [/cover] */
          if((ConxtDescRDES3 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_CTXT_SET)
                            == (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_CTXT_SET)
          {
            /* [cover parentID={16EC9881-8EE6-4743-8A1C-C3EFE5F24A28}]
            For time stamp retrieval, mark the Rx Descriptor index
            [/cover] */
            EthLocalCoreStatusPtr->EthBuffDescPtr->
                  EthRunTmRxChnlDataPtr[FifoIdx].RxDmaDescIdxTmStmp =
                                                        ConxtDescPosition;
          }
        }

        /* store the DataPtr address at the corresponding array position to be
         * used for comparison while reading ingress time stamp */
        EthLocalCoreStatusPtr->EthRunTimeOpertnData.RxTmStmpDataPtr[FifoIdx] =
                  (Eth_DataType *)
                  &(CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_PAYLOAD_POS]);

#endif /*(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)*/

        CrcStripEnabled = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties >>
                      ETH_17_GETHMACV2_CRCS_POS) & ETH_17_GETHMACV2_CRCS_MSK);

        /* update the Rx frame length */
        RxLength = RxLength - (uint16)ETH_17_GETHMACV2_FRAMEHEADER_LENGTH;

        /* [cover parentID={99A1D506-153F-4284-AF35-8667D77F5503}]
        If CRC stripping is enabled
        [/cover] */
        if(CrcStripEnabled == ETH_17_GETHMACV2_ENABLE)
        {
          /* [cover parentID={D487A116-DFE7-47f7-82CF-629F8E021EE0}]
          Update the length of the Rx frame (subtract the frame checksum length)
          [/cover] */
          RxLength = RxLength - (uint16)ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH;
        }

        /* Get Frame Type of the received frame */
        FrameType = (uint16)(((uint16)(((uint16)CurrentBufferPtr
         [ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS]) << ETH_17_GETHMACV2_SHIFT_8BIT))
           | ((uint16)CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_TYPE_LSB_POS]));

        /* [cover parentID={F4DEB375-3DB0-4706-9B22-38AAD9B9F5D3}]
        Indicate Application about Rx frame
        [/cover] */
        EthIf_RxIndication (CtrlIdx, FrameType, BroadcastState,
          EthSourceAddr, (Eth_DataType *)&
        (CurrentBufferPtr[ETH_17_GETHMACV2_FRAME_PAYLOAD_POS]), RxLength);

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        /* Reset time stamp availability as Not Available*/
        EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmRxChnlDataPtr[FifoIdx].
                        RxDmaDescIdxTmStmp = ETH_17_GETHMACV2_DMADESC_INVALID;

        /* Reset the DataPtr for timestamp to NULL */
        EthLocalCoreStatusPtr->EthRunTimeOpertnData.RxTmStmpDataPtr[FifoIdx] =
                                                                    NULL_PTR;
#endif /*(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)*/
        }

      /* [cover parentID={E2EDB0D3-2E87-4dcd-A502-84B7DD1F2A3B}]
      Switch management support Enabled
      [/cover] */
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
      /* [cover parentID={33E27EA0-4458-4f6d-9A48-572566226122}]
      Invoke switch driver Rx indication API call
      [/cover] */
      (void)EthSwt_EthRxFinishedIndication(CtrlIdx, (((uint32)FifoIdx <<
                          ETH_17_GETHMACV2_FIFOIDX_POS) | RxBufClrStrtIdx));
      }
#endif
      }

      /* [cover parentID={87C89501-85FF-48bf-A1F8-A8C10220A961}]
      Free all Descriptors holding the Ethernet frame to DMA
      [/cover] */
      for(TempVar = 0U; TempVar < BufferClearCount; TempVar++)
      {
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
          pointer type is performed to access the buffer address from DMA
          descriptor. This is the intended design and valid as per DMA hardware
          design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
          is performed to access the buffer address from DMA descriptor.
          This is the intended design and valid as per DMA hardware design.
          There are no side effects seen by violating this rule.*/
        EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES0 =\
          ((uint32)RxBuffBasePtr +\
          ((uint32)RxBufClrStrtIdx * RxBufLengthAligned));

        EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES1 = 0U;

        /* Descriptor Buffer2 pointer not used */
        EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES2 = 0U;

        /* Info :While releasing each time, Buffer 1 valid to be set*/
        EthLocalDmaRxDescPtr[RxBufClrStrtIdx].RDES3 = (uint32)
                        (((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_BF1_VALID) |
                        ((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_IOC_ENABLE) |
                        ((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET));

        RxBufClrStrtIdx = Eth_17_GEthMacV2_lIncrRxBufIdx(
                                     RxBufClrStrtIdx, RxBufTotal);
      }

      /* Increment Current Rx Dma descriptor index */
      EthLocalCoreStatusPtr->EthBuffDescPtr->
                 EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx =
         Eth_17_GEthMacV2_lIncrRxBufIdx(EthLocalCoreStatusPtr->EthBuffDescPtr->
                EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx, RxBufTotal);
    }
    else
    {
      /* [cover parentID={3CFE02EE-5D3E-463c-91BF-40557F094055}]
      Descriptor still owned by DMA or One application indication
      done, break the loop
      [/cover] */
      break;
    }
  }

  return ApplIndication;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={2EDCFFDB-3A9C-4f05-A65A-3DCA1C970224}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_GEthMacV2_lSetPhysAddr(        **
**                        const uint8 CtrlIdx, const uint8* const MacAddrPtr) **
**                                                                            **
** Description      : Sets the physical source address for the controller     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : MacAddrPtr  - Physical source address (MAC address) in  **
**                    network byte order.                                     **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_GEthMacV2_lSetPhysAddr(const uint8 CtrlIdx,
                                                const uint8* const MacAddrPtr)
{
  uint32 DataVal;
  Ifx_GETH *EthCtrlAddPtr;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* Extract Byte 5 and Byte 6. */
  DataVal = ((((uint32)MacAddrPtr[5])<<ETH_17_GETHMACV2_SHIFT_8BIT) |
             ((uint32)MacAddrPtr[4]) | (ETH_17_GETHMACV2_MACADDRRESS_ENABLE));

  /* Write upper 16 bit of Physical address to MAC Address0 High Register */
  EthCtrlAddPtr->MAC_ADDRESS_HIGH0.U = (uint32)DataVal;

  /* Extract Byte 1,2,3 and 4. */
  DataVal = (uint32)((((uint32)MacAddrPtr[3]) << ETH_17_GETHMACV2_SHIFT_24BIT) |
                     (((uint32)MacAddrPtr[2]) << ETH_17_GETHMACV2_SHIFT_16BIT) |
                     (((uint32)MacAddrPtr[1]) << ETH_17_GETHMACV2_SHIFT_8BIT)  |
                       MacAddrPtr[0]);

  /*Write lower 4 bytes of Physical address to MAC Address0 low Register*/
  EthCtrlAddPtr->MAC_ADDRESS_LOW0.U = (uint32)DataVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={AA266371-78BD-47fc-893E-25AA4133A974}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_GEthMacV2_lGetPhysAddr         **
**                             (const uint8 CtrlIdx, uint8* const MacAddrPtr) **
**                                                                            **
** Description      : Obtains the physical source address used by the         **
**                    controller                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddrPtr - Physical source address (MAC address) in   **
**                    network byte order.                                     **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_GEthMacV2_lGetPhysAddr(const uint8 CtrlIdx,
                                                uint8* const MacAddrPtr)
{
  uint32 DataVal;
  const Ifx_GETH *EthCtrlAddPtr;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* [cover parentID={022F5577-40C6-49df-B027-E3CF42177176}]
  Read Physical Source Address from MAC Address Register 0 and write into
  Physical Address Pointer
  [/cover] */
  DataVal = (uint32)(EthCtrlAddPtr->MAC_ADDRESS_HIGH0.U);

  /* Extract Byte 5 and Byte 6. */
  MacAddrPtr[5] = (uint8)((DataVal >> ETH_17_GETHMACV2_SHIFT_8BIT) &
                                       ETH_17_GETHMACV2_BYTE0_MASK);
  MacAddrPtr[4] = (uint8)(DataVal & ETH_17_GETHMACV2_BYTE0_MASK);

  /* Extract Byte 1,2,3 and 4. */
  DataVal = (uint32)(EthCtrlAddPtr->MAC_ADDRESS_LOW0.U);

  MacAddrPtr[3] =(uint8)((DataVal >> ETH_17_GETHMACV2_SHIFT_24BIT) &
                                       ETH_17_GETHMACV2_BYTE0_MASK);
  MacAddrPtr[2] =(uint8)((DataVal >> ETH_17_GETHMACV2_SHIFT_16BIT) &
                                       ETH_17_GETHMACV2_BYTE0_MASK);
  MacAddrPtr[1] =(uint8)((DataVal >> ETH_17_GETHMACV2_SHIFT_8BIT) &
                                       ETH_17_GETHMACV2_BYTE0_MASK);
  MacAddrPtr[0] =(uint8)(DataVal & ETH_17_GETHMACV2_BYTE0_MASK);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9F0E836E-FF92-4f68-8A68-8329F5928B26}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrRxBufIdx      **
**                                              (const uint16 RxBufIdx,       **
**                                               const uint16 EthRxBufTotal)  **
**                                                                            **
** Description      : Move RX buffer index to next index in ring buffer       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : RxBufIdx - Current Rx Buffer Index                      **
**                    EthRxBufTotal - Rx Buffer Length Total                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Next Rx index in ring buffer                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrRxBufIdx (const uint16 RxBufIdx,
                                                   const uint16 EthRxBufTotal)
{
  return ((RxBufIdx+1U) % (EthRxBufTotal));
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E629C357-CFC2-4b42-BE97-92FDD978654A}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrTxBufIdx      **
**                        (const uint16 TxBufIdx, const uint16 EthTxBufTotal) **
**                                                                            **
** Description      : Move TX buffer index to next index in ring buffer       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : TxBufIdx - Current Tx Buffer Index                      **
**                    EthTxBufTotal - Tx Buffer Length Total                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Next Tx index in ring buffer                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 Eth_17_GEthMacV2_lIncrTxBufIdx(const uint16 TxBufIdx,
                                                  const uint16 EthTxBufTotal)
{
  return ((TxBufIdx+1U) % (EthTxBufTotal));
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={6E5BC49F-8746-464a-89BF-F6D732220EC6}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE boolean                                    **
**                     Eth_17_GEthMacV2_lIsBroadcastAddress(                  **
**                                            const uint8* const MacAddrPtr)  **
**                                                                            **
** Description      : This function returns TRUE if the MAC address is a      **
**                    broadcast address                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : MacAddrPtr - Pointer to the MAC address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - MAC address is a broadcast address               **
**                    FALSE - MAC address is not a broadcast address          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Eth_17_GEthMacV2_lIsBroadcastAddress(
                                             const uint8* const MacAddrPtr)
{
  boolean RetVal;

  if((MacAddrPtr[0] == 0xFFU) && (MacAddrPtr[1] == 0xFFU) &&
     (MacAddrPtr[2] == 0xFFU) && (MacAddrPtr[3] == 0xFFU) &&
     (MacAddrPtr[4] == 0xFFU) && (MacAddrPtr[5] == 0xFFU))
  {
    /* MAC address is a broadcast address. */
    RetVal = TRUE;
  }
  else
  {
    /*If any byte of MAC address is not FF return false */
    RetVal = FALSE;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C223786B-718D-473d-8EFC-79C3E3C7BBB3}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_GEthMacV2_lIsNextFrameAvailable(  **
**                                  const uint8 CtrlIdx, const uint8 FifoIdx) **
**                                                                            **
** Description      : This function returns TRUE if next frame is availabe    **
**                    in buffers.                                             **
**                    This local API is required only in polling mode of Rx   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    FifoIdx - Specifies the related FIFO                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - Next frame available                             **
**                    FALSE - Next frame not available                        **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_GEthMacV2_lIsNextFrameAvailable(const uint8 CtrlIdx,
                                                      const uint8 FifoIdx)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMacV2_DmaRxDescType *EthLocalDmaRxDescPtr;
  const volatile uint8 *RxBuffBasePtr;
  uint32 DescStatRDES3;
  uint16 RxBufLengthAligned;
  uint16 RxBufTotal;
  uint16 RxBufferClearStartIdx;
  uint16 BufferCount;
  uint16 BufferClearCount;
  boolean NextFrameAvlbl;

  NextFrameAvlbl = FALSE;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                                EthDmaRxDescPtr[FifoIdx];

  /* Get the number of Rx buffers configured for the FIFO */
  RxBufTotal = EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].NumOfRxBuffers;

  RxBufLengthAligned = EthLocalCtrlCfgPtr->EthRxFifoCfgPtr[FifoIdx].
                                                   RxBufferAlignSize;

  RxBuffBasePtr = &(EthLocalCoreStatusPtr->EthBuffDescPtr->
                                              EthRxBufferPtr[FifoIdx][0U]);


  /* Check if Rx buffer of current Eth_CurrRxDmaDescIdx is released by DMA */
  /* BufferClearCount variable counts number of buffers to be released.
  Initialized to zero here */
  BufferClearCount = 0U;

  RxBufferClearStartIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx;

  /* Info: For receive operation descriptors are configured to store exactly
     one ethernet frame.
     i.e received frames are not spread across multiple descriptors, If length
     of the received frame is greater than length of the descriptor then these
     frames are not received. */
  /* [cover parentID={1EB12FC9-30E1-4000-8014-6A376C3E7D7A}]
  Loop till the total Rx buffers within the FIFO
  [/cover] */
  for(BufferCount = 0U; BufferCount < RxBufTotal; BufferCount++)
  {
    /* Read DMA Rx Descriptor status from RDES3 of Eth_CurrRxDmaDescIdx. */
    DescStatRDES3 = EthLocalDmaRxDescPtr[EthLocalCoreStatusPtr->EthBuffDescPtr->
             EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx].RDES3;

    /* [cover parentID={33EEB1A8-AA29-497d-8C13-EC56F75CB377}]
    Is Rx Descriptor released by DMA and NextFrameAvailable is false ?
    [/cover] */
    if (((DescStatRDES3 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET) ==
       ETH_17_GETHMACV2_DESC_RELEASED) && (NextFrameAvlbl == FALSE))
    {
      /* [cover parentID={C7A7E4F9-55D8-499a-8725-CDD7E2F352B0}]
      Check if first Descriptor bit (FD) and Last Descriptor bit (LD) is set
      for Eth_CurrRxDmaDescIdx
      [/cover] */
      if (((DescStatRDES3 & (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_FD_LD_SET) ==
           (uint32)ETH_17_GETHMACV2_DMA_RX_DESC_FD_LD_SET))
      {
        /* [cover parentID={6A0EE416-C0CD-4489-A17E-2935ED979DC9}]
        Set NextFrameAvailable variable TRUE
        [/cover] */
        NextFrameAvlbl = TRUE;
      }
      else
      {
        /* BufferClearCount incremented to release one descriptor */
        BufferClearCount++;

        /* Increment Current Rx Dma descriptor index */
        EthLocalCoreStatusPtr->EthBuffDescPtr->
                   EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx =
        Eth_17_GEthMacV2_lIncrRxBufIdx(EthLocalCoreStatusPtr->EthBuffDescPtr->
                EthRunTmRxChnlDataPtr[FifoIdx].CurrRxDmaDescIdx, RxBufTotal);
      }
    }
    else
    {
      /* Descriptor still owned by DMA - break the loop */
      break;
    }
  }

  /* [cover parentID={0D5E3358-4A87-432f-A673-9D5D80B0D0ED}]
  Free all descriptors released by DMA that do not have the first and last
  descriptor bit set
  [/cover] */
  /* [cover parentID={3E9140A8-8332-42f8-BF2F-635B503347F4}]
  Is buffer count less than total buffer clear count ?
  [/cover] */
  for (BufferCount = 0U; BufferCount < BufferClearCount; BufferCount++)
  {
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
      pointer type is performed to access the buffer address from DMA
      descriptor. This is the intended design and valid as per DMA hardware
      design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
      is performed to access the buffer address from DMA descriptor.
      This is the intended design and valid as per DMA hardware design.
      There are no side effects seen by violating this rule.*/
    EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES0 =\
              ((uint32)RxBuffBasePtr +\
              ((uint32)RxBufferClearStartIdx * RxBufLengthAligned));

    EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES1 = 0U;

    /* Descriptor Buffer2 pointer not used */
    EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES2 = 0U;

    /* Info :While releasing each time, Buffer 1 valid to be set*/
    EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES3 = (uint32)
                  (((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_BF1_VALID) |
                  ((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_IOC_ENABLE) |
                  ((uint32)ETH_17_GETHMACV2_DMA_RX_DESC_OWN_SET));

    RxBufferClearStartIdx = Eth_17_GEthMacV2_lIncrRxBufIdx(
                               RxBufferClearStartIdx, RxBufTotal);
  }

  return NextFrameAvlbl;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1980E926-ACDF-421c-8219-FE35A47D665D}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lClearAllAddressFilters(   **
**                                                     const uint8 CtrlIdx)   **
**                                                                            **
** Description      : This function clears all MAC filters register           **
**                    from 0 to 31                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lClearAllAddressFilters(const uint8 CtrlIdx)
{
  uint32 Count;
  uint32 NumberOfFilters;
  Ifx_GETH *EthCtrlAddPtr;
  Eth_17_GEthMacV2_MacAddr_1_31Type *EthMacFilterAddPtr;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
     different object types is performed for SFR access. There are no side
     effects seen by violating this rule. */
  EthMacFilterAddPtr = ((Eth_17_GEthMacV2_MacAddr_1_31Type*)\
                            Eth_17_GEthMacV2_HighBaseAddrPtr[CtrlIdx]);

  /* Set default value to Address register 0. */
  /* Info: Address register 0 is always enabled. */
  /* [cover parentID={9F99B369-C2F5-4cf9-82DE-1DD16F308A3E}]
  Clear MAC Address filter register 0 with Reset value
  [/cover] */
  EthCtrlAddPtr->MAC_ADDRESS_HIGH0.U = ETH_17_GETHMACV2_FILT0_DEF_HIGH_VAL;
  EthCtrlAddPtr->MAC_ADDRESS_LOW0.U = ETH_17_GETHMACV2_FILT0_DEF_LOW_VAL;

  /* First MAC address filter register is already initialized.
     Hence reduce 1.*/
  NumberOfFilters = ETH_17_GETHMACV2_NO_OF_FILTER_REGISTERS - 1U;

  /* Clear all Filter registers from 1 to 31 and disable the register */
  /* [cover parentID={C7E90E8B-25A7-4995-926F-9286045E88FE}]
  [/cover] */
  for(Count = 0U; Count < NumberOfFilters; Count++)
  {
    EthMacFilterAddPtr[Count].AddrHigh.U =
                          (uint32)ETH_17_GETHMACV2_FILT_HIGH_1_31_DEF_VAL;

    EthMacFilterAddPtr[Count].AddrLow.U =
                          (uint32)ETH_17_GETHMACV2_FILT_LOW_1_31_DEF_VAL;
  }
}

/* Local API's for Update PHY Filters */
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={96F3E157-0BB6-49c4-BE0F-F013B4CA5A3E}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE boolean Eth_17_GEthMacV2_lIsAllZeroAddress **
**                                            (const uint8* const MacAddrPtr) **
**                                                                            **
** Description      : This function returns TRUE if the MAC address is        **
**                    all Zeros                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddrPtr - Pointer to the MAC address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - MAC address consists of all Zeros                **
**                    FALSE - MAC address does not consist of all Zeros       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Eth_17_GEthMacV2_lIsAllZeroAddress(
                                      const uint8* const MacAddrPtr)
{
  boolean RetVal;

  if((MacAddrPtr[0] == 0U) && (MacAddrPtr[1] == 0U) && (MacAddrPtr[2] == 0U) &&
     (MacAddrPtr[3] == 0U) && (MacAddrPtr[4] == 0U) && (MacAddrPtr[5] == 0U))
  {
    /* If any byte of MAC address is non-zero return false*/
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C5060F6B-E474-4a2b-9605-0A3D9315E9E4}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lAddToFilter(    **
**                    const uint8 CtrlIdx, const uint8* const MacAddrPtr)     **
**                                                                            **
** Description      : This function adds a MAC address to filter              **
**                    This local API is required only if filters are supported**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    MacAddrPtr - MAC Address to be added to filter          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Address is successfully added to filter          **
**                    E_NOT_OK - Address could not be added to filter         **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lAddToFilter(const uint8 CtrlIdx,
                                       const uint8* const MacAddrPtr)
{
  Eth_17_GEthMacV2_MacAddr_1_31Type *EthMacFilterAddPtr;
  uint32 MacAdrressLow;
  uint32 MacAddressHigh;
  uint16 FilterPresenceStatus;
  uint8 IsAddPresent;
  uint8 FreeFilterIdx;
  Std_ReturnType RetVal;

  RetVal = E_NOT_OK;

  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
    different object types is performed for SFR access. There are no side
    effects seen by violating this rule. */
  EthMacFilterAddPtr = (Eth_17_GEthMacV2_MacAddr_1_31Type*)\
                        Eth_17_GEthMacV2_HighBaseAddrPtr[CtrlIdx];

  /* Check filter is present already, if not,get free filter register index. */
  FilterPresenceStatus = Eth_17_GEthMacV2_lCheckFilterPresent(CtrlIdx,
                                                              MacAddrPtr);

  IsAddPresent = (uint8)(FilterPresenceStatus &
                          ((uint16)ETH_17_GETHMACV2_MASK_LSB));

  /* [cover parentID={B7989288-03BC-45c0-9122-18B2E7FD2BFD}]
  Filter address is already present
  [/cover] */
  /* Check if same address is not already present in the filter */
  if(IsAddPresent == (uint8)ETH_17_GETHMACV2_INVALID_FILTER_VALUE)
  {
    /* Extract free filter register index from FilterPresenceStatus. */
    FreeFilterIdx = (uint8)(FilterPresenceStatus >>
                                     ETH_17_GETHMACV2_SHIFT_8BIT);

    /* [cover parentID={31053182-10CB-4cab-B9EC-642BB356DBE9}]
    Free filter register index is valid
    [/cover] */
    /* If free filter register index is valid, update filter address.
    0 to 30 is valid index. */
    if(FreeFilterIdx != ETH_17_GETHMACV2_INVALID_FILTER_VALUE)
    {
      MacAdrressLow = (uint32)
                   ((((uint32)MacAddrPtr[3]) << ETH_17_GETHMACV2_SHIFT_24BIT) |
                    (((uint32)MacAddrPtr[2]) << ETH_17_GETHMACV2_SHIFT_16BIT) |
                    (((uint32)MacAddrPtr[1]) << ETH_17_GETHMACV2_SHIFT_8BIT)  |
                      (uint32)MacAddrPtr[0]);

      MacAddressHigh = (uint32)(((uint32)MacAddrPtr[5] <<
                        ETH_17_GETHMACV2_SHIFT_8BIT) | (uint32)MacAddrPtr[4]);

      /* [cover parentID={9D4394A4-7D8F-4acb-836A-FF44284A3DA9}]
      Write Physical address in free MAC address filter register
      [/cover] */
      EthMacFilterAddPtr[FreeFilterIdx].AddrHigh.U =
             (uint32)(MacAddressHigh | ETH_17_GETHMACV2_MACADDRRESS_ENABLE);

      EthMacFilterAddPtr[FreeFilterIdx].AddrLow.U = (uint32)MacAdrressLow;

      RetVal = E_OK;
    }
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0B548C5C-3137-4f6a-ABE1-644DA1972988}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lRemoveFromFilter**
**                       (const uint8 CtrlIdx, const uint8* const MacAddrPtr) **
**                                                                            **
** Description      : This function removes a MAC address from filter         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddrPtr - Pointer to the MAC Address                 **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Address is successfully removed from filter      **
**                    E_NOT_OK - Address could not be removed from filter     **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lRemoveFromFilter(const uint8 CtrlIdx,
                                            const uint8* const MacAddrPtr)
{
  Eth_17_GEthMacV2_MacAddr_1_31Type *EthMacFilterAddPtr;
  uint16 FilterPresenceStatus;
  uint8 FilterPresentIdx;
  Std_ReturnType RetVal;

  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
   different object types is performed for SFR access. There are no side
   effects seen by violating this rule. */
  EthMacFilterAddPtr = (Eth_17_GEthMacV2_MacAddr_1_31Type*)\
                        Eth_17_GEthMacV2_HighBaseAddrPtr[CtrlIdx];

  /* [cover parentID={313FBAD5-D005-4c49-9562-2178226153B8}]
  Check if the MAC physical address exists in the filter set
  (The function return filter present status with as filter register index,
  where the filter is present)
  [/cover] */
  FilterPresenceStatus = Eth_17_GEthMacV2_lCheckFilterPresent(CtrlIdx,
                                                              MacAddrPtr);

  FilterPresentIdx = (uint8)(FilterPresenceStatus &
                                         ((uint16)ETH_17_GETHMACV2_MASK_LSB));

  /* [cover parentID={CF77F423-9540-4aff-AA92-5D145013AFEC}]
  Address present in filter set
  [/cover] */
  /* If FilterPresentIdx is valid, update that address register with default.
     0 to 30 is valid index. */
  if(FilterPresentIdx != ETH_17_GETHMACV2_INVALID_FILTER_VALUE)
  {
    /* [cover parentID={704FF88C-D3DB-479f-A710-9E716EC2346A}]
    Remove address from filter register ( where address is present) and
    fill the address register with reset value
    [/cover] */
    EthMacFilterAddPtr[FilterPresentIdx].AddrHigh.U =
                        (uint32)ETH_17_GETHMACV2_FILT_HIGH_1_31_DEF_VAL;

    EthMacFilterAddPtr[FilterPresentIdx].AddrLow.U =
                        (uint32)ETH_17_GETHMACV2_FILT_LOW_1_31_DEF_VAL;
    RetVal = E_OK;
  }
  else
  {
    /*FilterPresentIdx value is invalid or out of range */
    RetVal = E_NOT_OK;
  }

  return RetVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3958F01D-9461-4200-93FB-7A2D2962CB57}]  **
**                                                                            **
** Syntax           : static uint16 Eth_17_GEthMacV2_lCheckFilterPresent(     **
**                    const uint8 CtrlIdx, const uint8* const MacAddrPtr)     **
**                                                                            **
** Description      : This function returns the filter index where the address**
**                    is present.If address is not present,it return free     **
**                    filter register index, where new filter value can be    **
**                    programmed.                                             **
**                    This local API is required only if filters are supported**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                    MacAddrPtr - Pointer to the MAC Address                 **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Byte 0 - If address already present,index of it.        **
**                    Byte 1 - If address already not present,index of free   **
**                             filter register index.                         **
**                    If Byte 0 is 0xFF means - address not already present   **
**                    If Byte 1 is 0xFF means - no free free filter register  **
**                                                                            **
*******************************************************************************/
static uint16 Eth_17_GEthMacV2_lCheckFilterPresent(const uint8 CtrlIdx,
                                      const uint8* const MacAddrPtr)
{
  const Eth_17_GEthMacV2_MacAddr_1_31Type *EthMacFilterAddPtr;
  uint32 DataValHigh;
  uint32 DataValLow;
  uint32 DataValLowReg;
  uint32 DataValHighReg;
  uint16 RetVal;
  uint8 Count;
  uint8 FreeFilterIdx;
  uint8 IsAddPresent;
  uint8 NumberOfFilters;

  FreeFilterIdx = ETH_17_GETHMACV2_INVALID_FILTER_VALUE;
  IsAddPresent = ETH_17_GETHMACV2_INVALID_FILTER_VALUE;

  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
    different object types is performed for SFR access. There are no side
    effects seen by violating this rule. */
  EthMacFilterAddPtr = (Eth_17_GEthMacV2_MacAddr_1_31Type*)\
                        Eth_17_GEthMacV2_HighBaseAddrPtr[CtrlIdx];

  /* Exclude first MAC address filter register.*/
  NumberOfFilters = (uint8)(ETH_17_GETHMACV2_NO_OF_FILTER_REGISTERS - 1U);

  DataValHigh = (uint32)(ETH_17_GETHMACV2_MACADDRRESS_ENABLE |
                      ((uint32)MacAddrPtr[5] << ETH_17_GETHMACV2_SHIFT_8BIT) |
                       (uint32)MacAddrPtr[4]);

  DataValLow = ((((uint32)MacAddrPtr[3]) << ETH_17_GETHMACV2_SHIFT_24BIT) |
                (((uint32)MacAddrPtr[2]) << ETH_17_GETHMACV2_SHIFT_16BIT) |
                (((uint32)MacAddrPtr[1]) << ETH_17_GETHMACV2_SHIFT_8BIT)  |
                (uint32)MacAddrPtr[0]);

  /* [cover parentID={C073D36C-7A43-4fd0-B8AF-EC794A66BE26}]
  Loop to scan MAC filter address registers 1 to 31
  [/cover] */
  /* Scan address filter registers from 1 to 31. */
  for(Count = 0U; Count < NumberOfFilters; Count++)
  {
    /* [cover parentID={B53FF789-23D3-40d3-98A0-1E424C891516}]
    MAC filter address register is enabled
    [/cover] */
    if (EthMacFilterAddPtr[Count].AddrHigh.B.AE == ETH_17_GETHMACV2_ENABLE)
    {
      /* [cover parentID={256CAC27-5779-43da-AF54-47A883D88F96}]
      Is address in filter register equal to physical address to be added
      [/cover] */
      /* If Filter register is enabled, check address is already programmed.*/
      DataValHighReg = (uint32)EthMacFilterAddPtr[Count].AddrHigh.U;

      DataValLowReg = (uint32)EthMacFilterAddPtr[Count].AddrLow.U;

      if((DataValHighReg == DataValHigh) && (DataValLowReg == DataValLow))
      {
        /* Filter already applied */
        IsAddPresent = Count;
        break;
      }
    }
    else
    {
      /* [cover parentID={D5901874-11F0-4e22-BAD9-BF3139D04D01}]
      Is Free filter index value INVALID
      [/cover] */
      /* Filter is free. Now  assign FreeFilterIdx only if not done already.*/
      if(FreeFilterIdx == ETH_17_GETHMACV2_INVALID_FILTER_VALUE)
      {
        FreeFilterIdx = Count;
      }
    }
  }

  RetVal = (uint16)((uint16)FreeFilterIdx << ETH_17_GETHMACV2_SHIFT_8BIT);
  RetVal |= (uint16)IsAddPresent;

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7B844AAC-3F37-4395-B8A3-855C4097DB3D}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDisableGethInterrupt(const**
**                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr) **
**                                                                            **
** Description      : Clear interrupt status and mask interrupts which are    **
**                    enabled in default                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDisableGethInterrupt(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint8 IntEnabled;
  uint8 LoopCount;
  uint8 MaxUsedChannels;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Mask all interrupts which are enabled in default */
  EthCtrlAddPtr->MMC_RX_INTERRUPT_MASK.U =
                                (uint32)ETH_17_GETHMACV2_DISABLE_MMC_RX_INTPT;

  EthCtrlAddPtr->MMC_TX_INTERRUPT_MASK.U =
                                (uint32)ETH_17_GETHMACV2_DISABLE_MMC_TX_INTPT;

  EthCtrlAddPtr->MMC_IPC_RX_INTERRUPT_MASK.U =
                            (uint32)ETH_17_GETHMACV2_DISABLE_MMC_IPC_RX_INTPT;

  /* If Transmit or Receive interrupt is enabled in configuration then
     disable it*/
  IntEnabled = (uint8)((EthCtrlCfgPtr->EthCtrlProperties >>
                ETH_17_GETHMACV2_TXRXINT_POS) & ETH_17_GETHMACV2_TXRXINT_MSK);

  /* [cover parentID={9F94A7F9-4FA4-4fd4-9757-323B70C27E5B}]
  [/cover] */
  /* Determine the max channels among Tx and Rx channels */
  if (EthCtrlCfgPtr->EthNumTxChnls >= EthCtrlCfgPtr->EthNumRxChnls)
  {
    MaxUsedChannels = EthCtrlCfgPtr->EthNumTxChnls;
  }
  else
  {
    MaxUsedChannels = EthCtrlCfgPtr->EthNumRxChnls;
  }

  /* [cover parentID={9A1F7E2C-0C48-435e-95B3-62E0F8D486E7}]
  If Tx or Rx interrupt in enabled
  [/cover] */
  if(IntEnabled != ETH_17_GETHMACV2_DISABLE)
  {
    for (LoopCount = 0; LoopCount < MaxUsedChannels; LoopCount++)
    {
      /* [cover parentID={A47E7A45-F36F-4e7c-B8E6-999C513437C0}]
      Clear DMA channel interrupt status bits
      [/cover] */
      EthCtrlAddPtr->DMA_CH[LoopCount].STATUS.U =
                              (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_CLR_ALL;

      /* [cover parentID={6F35FCAD-5990-4ef3-A88C-C4C4217E78A5}]
      Disable the DMA channel interrupt
      [/cover] */
      EthCtrlAddPtr->DMA_CH[LoopCount].INTERRUPT_ENABLE.U =
                                     (uint32)ETH_17_GETHMACV2_DISABLE;
    }
  }
  else
  {
    for (LoopCount = 0; LoopCount < MaxUsedChannels; LoopCount++)
    {
      /* [cover parentID={3B8AB047-F975-456a-99AA-08B40945E0DA}]
      Clear DMA channel interrupt status bits
      [/cover] */
      EthCtrlAddPtr->DMA_CH[LoopCount].STATUS.U =
                               (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_CLR_ALL;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={43BC7EB9-7529-40fb-A4D8-E4B250E3AF24}] **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lEnableGethInterrupt(const **
**                 Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)  **
**                                                                            **
** Description      : Enable DMA Channel-0 Tx and Rx Interrupt                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lEnableGethInterrupt(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint8 IntEnabled;
  uint8 ChnlCnt;
  uint8 MaxChnlsUsd;
  uint8 TxChnlsUsd;
  uint8 RxChnlsUsd;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  IntEnabled = (uint8)((EthCtrlCfgPtr->EthCtrlProperties >>
                ETH_17_GETHMACV2_TXRXINT_POS) & ETH_17_GETHMACV2_TXRXINT_MSK);

  /* Get the number of Tx channels */
  TxChnlsUsd = EthCtrlCfgPtr->EthNumTxChnls;

  /* Get the number of Rx channels */
  RxChnlsUsd = EthCtrlCfgPtr->EthNumRxChnls;

  /* Determine the Max channels among Tx and Rx */
  MaxChnlsUsd = RxChnlsUsd;

  /* [cover parentID={5DC8EBF3-3C03-4041-8FE8-B38D126A6ACC}]
  Are number of Tx channels greater than Rx channels ?
  [/cover] */
  if (TxChnlsUsd > RxChnlsUsd)
  {
    MaxChnlsUsd = TxChnlsUsd;
  }

  /* [cover parentID={8810915B-8F10-4d9a-97F0-8DEBC7B37FAF}]
  If either Tx or Rx Interrupt is enabled?
  [/cover] */
  if (IntEnabled != ETH_17_GETHMACV2_DISABLE)
  {
    /* [cover parentID={B9491C9A-62FC-4acb-81F4-1738CCB36715}]
    Loop until Max channels used
    [/cover] */
    for (ChnlCnt = 0U; ChnlCnt < MaxChnlsUsd; ChnlCnt++)
    {
      /* Clear interrupt status bits of DMA channels */
      EthCtrlAddPtr->DMA_CH[ChnlCnt].STATUS.U =
                        (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_CLR_ALL;

      EthCtrlAddPtr->DMA_CH[ChnlCnt].INTERRUPT_ENABLE.B.NIE =
                                            (uint8)ETH_17_GETHMACV2_ENABLE;
    }

    /* [cover parentID={EB0D6456-1088-4392-B2FE-15E2F526720F}]
    If Tx interrupt is enabled
    [/cover] */
    if ((IntEnabled & ETH_17_GETHMACV2_TXINT_ENABLED) ==
                                      ETH_17_GETHMACV2_TXINT_ENABLED)
    {
      /* [cover parentID={ED1DEB14-200B-49b3-8A3A-4EF0F9645B52}]
      Loop for number of Tx channels
      [/cover] */
      for (ChnlCnt = 0U; ChnlCnt < TxChnlsUsd; ChnlCnt++)
      {
        /* [cover parentID={074449E3-1DBA-48f4-B45C-4268DE913E30}]
        Enable Transmit Interrupt for the selected DMA channel
        [/cover] */
        EthCtrlAddPtr->DMA_CH[ChnlCnt].INTERRUPT_ENABLE.B.TIE =
                                          (uint8)ETH_17_GETHMACV2_ENABLE;
      }
    }

    /* [cover parentID={B292E4AE-52F8-48f7-AB72-B5B556277148}]
    If Rx Interrupt is enabled
    [/cover] */
    if ((IntEnabled & ETH_17_GETHMACV2_RXINT_ENABLED) ==
                                      ETH_17_GETHMACV2_RXINT_ENABLED)
    {
      /* [cover parentID={F00E76AB-E311-4983-8606-C01E4B64BACA}]
      Loop for number of Rx channels
      [/cover] */
      for (ChnlCnt = 0U; ChnlCnt < RxChnlsUsd; ChnlCnt++)
      {
        /* Enable DMA Channel RIE, RBUE and AIE bits. */
        /* [cover parentID={68469DDA-DCE2-47b4-A4E0-19036709F66C}]
        Enable receive interrupt, buffer unavailable and abnormal interrupt
        bits for the selected DMA channel
        [/cover] */
        EthCtrlAddPtr->DMA_CH[ChnlCnt].INTERRUPT_ENABLE.B.RIE =
                                          (uint8)ETH_17_GETHMACV2_ENABLE;
        EthCtrlAddPtr->DMA_CH[ChnlCnt].INTERRUPT_ENABLE.B.RBUE =
                                          (uint8)ETH_17_GETHMACV2_ENABLE;
        EthCtrlAddPtr->DMA_CH[ChnlCnt].INTERRUPT_ENABLE.B.AIE =
                                          (uint8)ETH_17_GETHMACV2_ENABLE;
      }
    }
  }
  else
  {
    /* Clear interrupt status bits of DMA channels */
    /* [cover parentID={FAACBA8E-7AB6-47df-A466-C9C3C5D18E71}]
    Loop until Max channels used
    [/cover] */
    for (ChnlCnt = 0U; ChnlCnt < MaxChnlsUsd; ChnlCnt++)
    {
      EthCtrlAddPtr->DMA_CH[ChnlCnt].STATUS.U =
                               (uint32)ETH_17_GETHMACV2_DMA_CH_STAT_CLR_ALL;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0EA58AA9-6E3B-45b6-9F07-03EDE8D66FF2}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lResetGethCore(  **
**                     const Eth_17_GEthMacV2_CoreCtrlConfigType*             **
**                                            const EthCtrlCfgPtr)            **
**                                                                            **
** Description      : Reset the GETH Core                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Kernel reset successful                      **
**                    E_NOT_OK - Kernel reset failed                          **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lResetGethCore(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  uint32 ResetStatus;
  uint32 NumberWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
  boolean IsTimeExpired;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Issue command to reset the GETH Core(GETH Kernel). */
  /* Reset End Init Protection to access registers */
  ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
                    (&(EthCtrlAddPtr->KRST0),(uint32)ETH_17_GETHMACV2_ENABLE);

  ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
                    (&(EthCtrlAddPtr->KRST1),(uint32)ETH_17_GETHMACV2_ENABLE);

  /* Check whether a GETH reset was executed or not, wait only until timeout.*/
  /* Get STM timer current resolution and calculate number of ticks to wait*/
  DelayTickResolution = Mcal_DelayTickResolution();
  NumberWaitTicks  = (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={FA84133F-080F-49ab-9A4E-0217120B3C1E}]
  [/cover] */
  if(NumberWaitTicks == 0U)
  {
    /* [cover parentID={FA84133F-080F-49ab-9A4E-0217120B3C1E}]
    Increment the ticks
    [/cover] */
    NumberWaitTicks++;
  }

  /*Get current STM tick*/
  CurrSTMTick   = Mcal_DelayGetTick();
  BaseSTMTick   = CurrSTMTick;
  IsTimeExpired = FALSE;

  /* [cover parentID={FA84133F-080F-49ab-9A4E-0217120B3C1E}]
  wait until Kernel reset is done or time has elapsed
  [/cover] */
  do
  {
    ResetStatus = (uint32)EthCtrlAddPtr->KRST0.B.RSTSTAT;

    /* Check wait time is reached at maximum timeout configured */
    if((((uint32)((CurrSTMTick - BaseSTMTick) &
          ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >=
          NumberWaitTicks) && (ResetStatus == ETH_17_GETHMACV2_RST_NOT_EXEC))
    {
      /* Timeout happened and reset is not completed yet*/
      IsTimeExpired = TRUE;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while((ResetStatus == ETH_17_GETHMACV2_RST_NOT_EXEC) &&
                                  (IsTimeExpired == FALSE));

  /* If timeout has occurred, report Production error for timeout */
  /* [cover parentID={9D198E84-2A82-4e94-BCD4-C2C8FA5C5212}]
  Report Production error if timeout has elasped
  [/cover] */
  Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired, EthCtrlCfgPtr->EthDemAccess);

  /* [cover parentID={0DC778D8-21B6-4184-B6CC-DC248CF48277}]
  Timeout elapsed
  [/cover] */
  if (IsTimeExpired == FALSE)
  {
    /* [cover parentID={E45B2DCD-302A-4d8b-94EA-83175C153857}]
    Check whether RGMII mode is configured
    [/cover] */
    if(((EthCtrlCfgPtr->EthCtrlProperties >> ETH_17_GETHMACV2_PHYINTF_POS)
                    & ETH_17_GETHMACV2_PHYINTF_MSK) == ETH_17_GETHMACV2_RGMII)
    {
      /* Calculate number of ticks to wait for RGMII mode */
      NumberWaitTicks = (ETH_17_GETHMACV2_KRNLRST_RGMII_WAITCNT/
                                                        DelayTickResolution);
    }
    else
    {
      /* Calculate number of ticks to wait for MII/ RMII mode */
      NumberWaitTicks = (ETH_17_GETHMACV2_KRNLRST_MII_WAITCNT/
                                                        DelayTickResolution);
    }

    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    if (NumberWaitTicks == 0U)
    {
      /* Increment the ticks */
      NumberWaitTicks++;
    }

    /*Get current STM tick*/
    CurrSTMTick   = Mcal_DelayGetTick();
    BaseSTMTick   = CurrSTMTick;
    IsTimeExpired = FALSE;

    /* Wait until necessary time has elapsed */
    do
    {
      /* Check wait time has reached maximum timeout configured */
      if(((uint32)((CurrSTMTick - BaseSTMTick) &
           ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= NumberWaitTicks)
      {
        /* Necessary time has elapsed */
        IsTimeExpired = TRUE;
      }

      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();
    }while(IsTimeExpired == FALSE);

    /* [cover parentID={E10B0BAE-873D-4810-A3D4-BA199B02915C}]
    Clear GETH Reset Status
    [/cover] */
    ETH_17_GETHMACV2_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
                  (&(EthCtrlAddPtr->KRSTCLR),(uint32)ETH_17_GETHMACV2_ENABLE);

    RetValue = E_OK;
  }
  else
  {
     /* [cover parentID={323A6A10-92A5-4812-82DD-5492496A7001}]
     Set return value E_NOT_OK
     [/cover] */
     RetValue = E_NOT_OK;
  }

  return (RetValue);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={4A55E3C7-6DEC-4384-B619-439D061926D1}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lInitGethController(const  **
**                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Apply reset to DMA to select MII  and complete          **
**                    Ethernet controller initialization process              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lInitGethController(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
  uint8 LoopCount;
  uint8 RxChnlsUsed;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* [cover parentID={042CD745-8F35-48c5-A4FB-9ACB8F079B92}]
  Flush the required transmit queues
  [/cover] */
  RetValue = Eth_17_GEthMacV2_lTxQFlush(EthCtrlCfgPtr);

  /* Check if the Tx flush operation is successful */
  /* Note: If Tx flush operation is not successful, Hardware Access failure
     Production error will be reported from called function. Hence, no action
     needed here. */
  /* [cover parentID={72B2C414-8A62-4ec6-8F00-3EA97C12C578}]
  [/cover] */
  if (RetValue == E_OK)
  {
    /* Get the number of Rx Channels */
    RxChnlsUsed = EthCtrlCfgPtr->EthNumRxChnls;

    /* [cover parentID={83A0D256-FDD9-40a7-B771-E9940BA8BDFB}]
    Flush the required receive Queues
    [/cover] */
    for(LoopCount = 0U; LoopCount < RxChnlsUsed; LoopCount++)
    {
      EthCtrlAddPtr->DMA_CH[LoopCount].RX_CONTROL.B.RPF = 1U;
    }

    /* Reset interrupt status and mask the interrupts */
    Eth_17_GEthMacV2_lDisableGethInterrupt(EthCtrlCfgPtr);

    /* [cover parentID={BBB2A1D8-24B2-46e8-BB7E-E33C898EE631}]
    Check whether RGMII mode is configured
    [/cover] */
    if (((EthCtrlCfgPtr->EthCtrlProperties>>ETH_17_GETHMACV2_PHYINTF_POS)
                    & ETH_17_GETHMACV2_PHYINTF_MSK) == ETH_17_GETHMACV2_RGMII)
    {
      /* [cover parentID={AEE234BC-7CA1-4178-9B52-155CBC2147D9}]
      Set the PHY interface to MII mode and retain the alternate input values
      Configure the TX and RX timing skew to zero
      [/cover] */
      ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(&EthCtrlAddPtr->GPCTL.U,
                                (uint32)EthCtrlCfgPtr->EthGpctlRegVal);

      /* In RGMII mode, initialize the timing skew to zero */
      ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(&(EthCtrlAddPtr->SKEWCTL.U), 0U);
    }

    /* [cover parentID={BD364B04-B2DC-48f4-B0B7-E1DB0F23FC8F}]
    Apply GETH MAC Kernel Reset
    [/cover] */
    RetValue = Eth_17_GEthMacV2_lResetGethCore(EthCtrlCfgPtr);

    /* If Kernel Reset is failed due to hardware access failure, RetValue
      will be E_NOT_OK and Hardware Access failure Production error will be
      reported from called function */
    /* [cover parentID={4E7FC9D5-5B70-414a-A392-9A878420621E}]
    Is Kernel Reset Successful ?
    [/cover] */
    if (RetValue == E_OK)
    {
      /* [cover parentID={98FEC4FE-3AF8-4ada-895D-17BD6095C0FB}]
      Configure selected PHY interface in GPCTL.
      In RGMII mode, also configure timing skew.
      [/cover] */
      /*Info: In Init function, only MDIO/MII pins preparation is done.
      Rest of Init part will be done in SetController mode, when the API is
      called for first time */
      Eth_17_GEthMacV2_lPhyIfModeSkewCfg(EthCtrlCfgPtr);

      /* Apply software reset to DMA.*/
      /* PHY interface is selected by DMA_reset.*/
      /*Info: It is assumed, that PHY is already configured by Ethernet
      Transceiver  driver and input clock from PHY is available*/
      RetValue = Eth_17_GEthMacV2_lResetDma(EthCtrlCfgPtr->EthCtrlIdx);

      /* [cover parentID={E72AFB73-C3BD-4bfe-A307-54CF5EDA3FF7}]
      DMA Reset is successful
      [/cover] */
      /* If DMA Reset is not successful, it means PHY interface could not be
      configured.Function will return E_NOT_OK and also Hardware Access failure
      Production error will be reported from called function */
      if(RetValue == E_OK)
      {
        /* [cover parentID={F7EEE0E6-CAD9-4f06-8A68-3CE6DB36732A}]
        Initialize the GETH Core- MAC,MTL and DMA initialization
        [/cover] */
        Eth_17_GEthMacV2_lGethCoreInit(EthCtrlCfgPtr);
      }
      /* [cover parentID={1FAFCF37-65FF-4919-9E06-F748373213CA}]
      If DMA Reset is failed due to any hardware access failure,
      Hardware Access failure Production error will be reported from called
      function. Hence no action needed here.
      [/cover] */
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E6F865F3-A144-4919-B160-E68F6C278509}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lGethCoreInit              **
**                           (const Eth_17_GEthMacV2_CoreCtrlConfigType*      **
**                                                     const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Configure MAC,MTL and DMA as per config root            **
**                    parameters                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lGethCoreInit(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
#if (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  Std_ReturnType RetValue = E_NOT_OK;
#endif
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(
                                       EthCtrlCfgPtr->EthCtrlIdx);

  /* Stop MAC and DMA transmission and reception */
  Eth_17_GEthMacV2_CtrlBaseAddrPtr
    [EthCtrlCfgPtr->EthCtrlIdx]->MAC_CONFIGURATION.U =
    (uint32)(Eth_17_GEthMacV2_CtrlBaseAddrPtr
              [EthCtrlCfgPtr->EthCtrlIdx]->MAC_CONFIGURATION.U
                        & (uint32)ETH_17_GETHMACV2_MAC_TXRX_DISABLEMASK);

  /* Do DMA (Sub block of GETH IP)configuration.*/
  Eth_17_GEthMacV2_lDmaCoreInit(EthCtrlCfgPtr);

  /* Do MTL core (Sub block of GETH IP)configuration.*/
  Eth_17_GEthMacV2_lMtlCoreInit(EthCtrlCfgPtr);

  /* Do MAC core(Sub block of GETH IP) configuration.*/
  Eth_17_GEthMacV2_lMacCoreInit(EthCtrlCfgPtr);


#if (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Initialize timer for MAC Timestamp feature for clock synchronization
  as per IEEE 1588-2008 PTP.*/
  /* If Timer Init is not successful,the function will return E_NOT_OK and
  also Hardware Access failure Production error will be reported from called
  function */
  RetValue = Eth_17_GEthMacV2_lTimerInit(EthCtrlCfgPtr);

  /* [cover parentID={78CA4680-476E-4077-B189-EC9F69A1B17A}]
  If Timer initialzation is successful
  [/cover] */
  if(RetValue == E_OK)
#endif
  {
    /* [cover parentID={AF420BBF-EE14-4ee4-9A06-3B9A8F12654B}]
    Set Controller Status to Initialized
    [/cover] */
    EthLocalCoreStatusPtr->EthRunTimeOpertnData.CtrlConfigStatus =
                                          ETH_17_GETHMACV2_CTRL_INITIALIZED;

    /* Ethernet controller is successfully initialized Report Pass to
    Mcal_Wrapper*/
    /* [cover parentID={C10E9C74-E6CC-4133-A63F-3AAFCAB3177D}]
    Report Pre Passed to Mcal_Wrapper module for all Production Errors
    [/cover] */
    /* Report all Production errors as prepass (except ETH_E_ACCESS)*/
    Eth_17_GEthMacV2_lDemReportAllErrorPass(EthCtrlCfgPtr);
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DA969C70-4A03-4e08-970F-E25B2F5A17CF}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lInitGlobalVar (           **
**                    Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr)**
**                                                                            **
** Description      : Initialize global variables                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : EthCoreStatusPtr- Pointer to Ethernet controller status,**
**                     used to access the global variables for initialization **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lInitGlobalVar(
                    Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr)
{
  uint8 LoopCount;

  /*Initialize Statistics Counter structure*/
  EthCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.Count = 0U;

  EthCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.
                                   DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.
                                   DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.
                                   DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.
                                   DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.
                                   DemReportedCount = 0U;

  EthCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.Count = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.Count = 0U;

  EthCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.
                               DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.
                               DemReportedCount = 0U;
  EthCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.
                               DemReportedCount = 0U;

    /* Initialize stored MAC address as 0 */
  for(LoopCount = 0U; LoopCount < ETH_17_GETHMACV2_MACADDRESS_LEN; LoopCount++)
  {
    EthCoreStatusPtr->EthRunTimeOpertnData.EthUnicastMacAddress[LoopCount] = 0U;
  }

  /* Set Controller Mode as DOWN in default. */
  EthCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode = ETH_MODE_DOWN;

  /* Set Previous Controller Mode as DOWN in default. */
  EthCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode = ETH_MODE_DOWN;

  /* Set the MII interface configuration status as Not configured. */
  EthCoreStatusPtr->EthRunTimeOpertnData.CtrlConfigStatus =
                                      ETH_17_GETHMACV2_CTRL_NOT_INITIALIZED;

  /* Set FilterOpenStatus as FALSE*/
  EthCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat = FALSE;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Set the Rx Timestamp DataPtr for all FIFOs to NULL */
  for (LoopCount = 0U;
       LoopCount < ETH_17_GETHMACV2_MAXCHLS_SUPPORTED; LoopCount++)
  {
    EthCoreStatusPtr->EthRunTimeOpertnData.RxTmStmpDataPtr[LoopCount] =
                                                                NULL_PTR;
  }
#endif
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={084292ED-DAEE-4b33-AD04-7D1AF3FA6716}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_GEthMacV2_lPhyIfModeSkewCfg(   **
**                       const Eth_17_GEthMacV2_CoreCtrlConfigType *          **
**                       const EthCtrlCfgPtr)                                 **
**                                                                            **
** Description      : This function configures GPCTL register to choose the   **
**                    selected PHY interface and the alternate inputs.        **
**                    Also configures the timing skew in RGMII mode.          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_GEthMacV2_lPhyIfModeSkewCfg(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint32 GptclValue;

  /*Before starting this function, all Port/Pin configuration should completed*/
  /* Info: Port Configuration is done by Port driver. */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* [cover parentID={0ADB901B-425C-4c4c-A703-4023F851F264}]
  Configure GPCTL register to choose selected PHY interface and alternate inputs
  [/cover] */
  GptclValue = (((((uint32)EthCtrlCfgPtr->
      EthCtrlProperties >> (uint32)ETH_17_GETHMACV2_PHYINTF_POS) &
      (uint32)ETH_17_GETHMACV2_PHYINTF_MSK) <<
      (uint32)ETH_17_GETHMACV2_GPTCL_PHY_POS) |
      (uint32) EthCtrlCfgPtr->EthGpctlRegVal);

  ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(&EthCtrlAddPtr->GPCTL.U, GptclValue);

  /* In RGMII mode, configure TX/RX Clock delay for skew timing */
  /* [cover parentID={F981B1D2-3B15-4771-9949-5012F18E2351}]
  Check whether RGMII mode is configured
  [/cover] */
  if(((EthCtrlCfgPtr->EthCtrlProperties >> ETH_17_GETHMACV2_PHYINTF_POS) &
                      ETH_17_GETHMACV2_PHYINTF_MSK) == ETH_17_GETHMACV2_RGMII)
  {
    /* [cover parentID={E7F3F821-3EEB-469c-8F58-3613727F9531}]
    Configure skew control register to the specified Tx and Rx skew timing
    [/cover] */
    ETH_17_GETHMACV2_SFR_RUNTIME_WRITE32(&(EthCtrlAddPtr->SKEWCTL.U),
    (((uint32)((uint32)(EthCtrlCfgPtr->EthSkewDelay &
    ETH_17_GETHMACV2_TXSKEW_MASK) << (uint32) IFX_GETH_SKEWCTL_TXCFG_OFF)) |
    ((uint32)((uint32)((EthCtrlCfgPtr->EthSkewDelay &
            ETH_17_GETHMACV2_RXSKEW_MASK) << ETH_17_GETHMACV2_RXSKEW_OFF)))));
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3929C939-A285-49aa-AE6A-91F9843DAA4E}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lResetDma        **
**                      (const uint8 CtrlIdx)                                 **
**                                                                            **
* Description      : Apply software reset to DMA                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - DMA Reset finished successfully              **
**                    E_NOT_OK - DMA Reset is not successful                  **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lResetDma(const uint8 CtrlIdx)
{
  uint32 NoOfSpbCyclesToWait;
  uint32 DmaResetFinished;
  uint32 DmaResetWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  Ifx_GETH *EthCtrlAddPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  Std_ReturnType RetValue;
  boolean IsTimeExpired;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /*In default set RetVal is E_NOT_OK */
  /* [cover parentID={7DCDEAAE-EF3E-4301-B2EE-4C302BAB9DA6}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* Hardware Errata/Application Hint - GETH_AI.H001( Preparation
  for Software Reset) is implemented below.
  That is, after applying DMA reset, wait for Wait 4 fSPB cycles,
  then check if DMA_MODE.SWR = 0B*/
  /* Get STM timer current resolution*/
  DelayTickResolution = Mcal_DelayTickResolution();

  /* Calculate SPB cycles in nanosecond to wait after DMA reset */
  NoOfSpbCyclesToWait = (uint32)(ETH_17_GETHMACV2_DMA_RESET_WAITCYCLE *
                                    ETH_17_GETHMACV2_FSPB_PERIOD_IN_NANOSEC);

  /* Calculate number of ticks to wait .That is 4 fSPB cycles*/
  DmaResetWaitTicks = (NoOfSpbCyclesToWait / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={6B33E6B9-12BD-4c25-9DFE-DFB6D0AD086E}]
  If Stm resolution is zero
  [/cover] */
  if(DmaResetWaitTicks == 0U)
  {
    /* [cover parentID={6D7B633D-5534-4c49-AF4F-8164AD20F65B}]
    Increment the ticks.
    [/cover] */
    DmaResetWaitTicks++;
  }

  /* [cover parentID={32C3D305-ABC8-45a0-8320-059930048A07}]
  Apply Software Reset to DMA
  [/cover] */
  EthCtrlAddPtr->DMA_MODE.B.SWR = (uint8)ETH_17_GETHMACV2_DMA_SWR;

  /*Get current STM tick*/
  CurrSTMTick   = Mcal_DelayGetTick();
  BaseSTMTick   = CurrSTMTick;
  IsTimeExpired = FALSE;

  /* [cover parentID={2E044AE0-F075-4d5e-B53E-A637F0B3C9DB}]
  Wait for the configured number of CSR clock cycles to check for reset
  completion
  [/cover] */
  do
  {
    /* Check wait time is reached at DMA reset wait time*/
    if(((uint32)((CurrSTMTick - BaseSTMTick) &
         ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= DmaResetWaitTicks)
    {
      /* Required cycles have elapsed */
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while(IsTimeExpired == FALSE);

  /* Calculate number of ticks to wait,until DMA reset is finished*/
  DmaResetWaitTicks  = (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT /DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  if(DmaResetWaitTicks == 0U)
  {
    /* Increment the ticks */
    DmaResetWaitTicks++;
  }

  /*Get current STM tick*/
  CurrSTMTick   = Mcal_DelayGetTick();
  BaseSTMTick   = CurrSTMTick;
  IsTimeExpired = FALSE;

  /* Checking in a time out loop if DMA reset if completed. */
  /* [cover parentID={62684A9D-72F2-4ccb-8ED0-8785A47E8431}]
  Wait until DMA reset completed or Timeout is elapsed
  [/cover] */
  do
  {
    /* If DMA reset is finished, zero should be read in the SWR bit. */
    DmaResetFinished = (uint32)(EthCtrlAddPtr->DMA_MODE.B.SWR);

    /* Check wait time is reached at maximum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) &
                  ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= DmaResetWaitTicks) &&
                 (DmaResetFinished == (uint32)ETH_17_GETHMACV2_DMA_SWR))
    {
      /*Timeout Happened and DMA reset is not finished yet*/
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while((DmaResetFinished == (uint32)ETH_17_GETHMACV2_DMA_SWR) &&
                                   (IsTimeExpired == FALSE));

  /* [cover parentID={E6422B66-37C0-4e88-85C5-7EC8A610C3EC}]
  Check if Timeout is elapsed
  [/cover] */
  /* If timeout has occurred, report Production error for timeout */
  Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired,EthLocalCtrlCfgPtr->EthDemAccess);

  /* [cover parentID={C101A226-4D8A-45e2-8B56-02695C92AFC7}]
  Timeout elapsed
  [/cover] */
  if (IsTimeExpired == FALSE)
  {
    /* [cover parentID={A4885C88-0923-4ecf-8AD4-36BB0E52229D}]
    set return value E_OK
    [/cover] */
    RetValue = E_OK;
  }

  return (RetValue);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={ED9E9EB3-0CBE-4b6e-88BC-ED2DD2525C3A}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lMacCoreInit               **
**                   (const Eth_17_GEthMacV2_ConfigType* const EthCtrlCfgPtr) **
**                                                                            **
** Description      : Configure MAC core as per configuration                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lMacCoreInit(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint32 MacConfigVal;
  uint8 LoopCount;
  uint8 EthOpMode;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(
                                         EthCtrlCfgPtr->EthCtrlIdx);

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* [cover parentID={AF6035B7-C361-4447-939D-85332B6AC1F1}]
  Configure Ethernet speed (10 or 100 or 1000 Mbps)
  [/cover] */
  MacConfigVal = ((uint32)EthCtrlCfgPtr->EthCtrlProperties &
                    ETH_17_GETHMACV2_PS_MSK) << (uint32)15U;

  MacConfigVal |= (((uint32)EthCtrlCfgPtr->EthCtrlProperties >>
                  ETH_17_GETHMACV2_FES_POS) & ETH_17_GETHMACV2_FES_MSK) << 14U;

  EthOpMode = (uint8)((EthCtrlCfgPtr->EthCtrlProperties) >>
                    ETH_17_GETHMACV2_OPMODE_POS) & ETH_17_GETHMACV2_OPMODE_MSK;

  /* Initialize MAC config and Tx/Rx flow control registers. */
  /* [cover parentID={5474C8E3-4618-46f1-B815-5C45B03FF738}]
  If OpMode is FULL DUPLEX
  [/cover] */
  if(EthOpMode == ETH_17_GETHMACV2_FULL_DUPLEX)
  {
    /* [cover parentID={CA918CCF-E84E-414e-AA57-B525C3D1092D}]
    Write MAC config register for Full Duplex mode
    [/cover] */
    MacConfigVal |= (uint32)(ETH_17_GETHMACV2_MAC_INIT_FDX_CONF);
  }
  else
  {
    /* [cover parentID={91EAB22F-E95A-4cf3-8AA4-0187C518F05D}]
    Write MAC config register for Half Duplex mode
    [/cover] */
    MacConfigVal |= (uint32)(ETH_17_GETHMACV2_MAC_INIT_HDX_CONF);
  }

  /* [cover parentID={5C93BDE6-1D7F-46c2-9BC2-FA6885FC6475}]
  Configure MAC Packet Filter register
  [/cover] */
  EthCtrlAddPtr->MAC_PACKET_FILTER.U = ETH_17_GETHMACV2_MAC_FILT_INIT_CONF;

  /* Clear MAC Address filter Registers 0 to 31 */
  Eth_17_GEthMacV2_lClearAllAddressFilters(EthCtrlCfgPtr->EthCtrlIdx);

  /* [cover parentID={7E8F45A4-8277-4796-92C5-AAD52B2D3BA4}]
  Set the configured unicast MAC address in MAC Address register 0
  [/cover] */
  Eth_17_GEthMacV2_lSetPhysAddr(EthCtrlCfgPtr->EthCtrlIdx,
                                EthCtrlCfgPtr->EthMacAddress);

  /* Copy configured MAC address, which will be used to restore controllers
     unique unicast MAC address while ending promiscuous mode, using API
     Eth_UpdatePhysAddrFilter().*/
  /* [cover parentID={A0E1B862-5E67-480e-9A9A-AFC6C82474C9}]
  Store configured MAC address in a global variable
  [/cover] */
  for(LoopCount = 0U;
      LoopCount < ETH_17_GETHMACV2_MACADDRESS_LEN; LoopCount++)
  {
    EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthUnicastMacAddress
                        [LoopCount] = EthCtrlCfgPtr->EthMacAddress[LoopCount];
  }

  /* [cover parentID={FDA19FDA-7511-47cb-BDB8-8D5DEA2F4913}]
  Checksum Offload  Enabled
  [/cover] */
#if((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON ) ||\
    (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) ||\
    (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) ||\
    (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON ))

  /* [cover parentID={27734502-1B37-4dae-BF8F-B64830E58237}]
  Enable Checksum Offload for IPv4 header checksum and IPv4 or IPv6, TCP, UDP,
  or ICMP payload checksum
  [/cover] */
  MacConfigVal |= ETH_17_GETHMACV2_MAC_CHKSM_OFFLD_ENBL;
#endif

  EthCtrlAddPtr->MAC_CONFIGURATION.U = MacConfigVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={6C156822-DC5B-4e8d-BC68-E982BA6D9C52}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lMtlCoreInit( const        **
**                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr) **
**                                                                            **
** Description      : Configure MTL core (MAC Transaction Layer)              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet Controller           **
**                                     Configuration.                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lMtlCoreInit(
          const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Configure MTL Operation mode(Common for Tx and Rx) and the MTL
       transmit scheduling algorithm */
  /* [cover parentID={835A0487-1641-4982-9A00-40796EC4F1EC}]
  [/cover] */
  EthCtrlAddPtr->MTL_OPERATION_MODE.U = ETH_17_GETHMACV2_MTL_OPERTN_MODE_INIT |
       ((uint32)EthCtrlCfgPtr->EthMtlTxSchAlg <<
                   (uint8)IFX_GETH_MTL_OPERATION_MODE_SCHALG_OFF);

  /* [cover parentID={D0B727E2-0FF2-418b-A78D-926EF6023517}]
  Configure the transmit queues
  [/cover] */
  Eth_17_GEthMacV2_lCfgTxQueue(EthCtrlCfgPtr);

  /* [cover parentID={1D550C3F-0587-4038-9CBB-91E31C2FB27E}]
  Configure the Receive queues
  [/cover] */
  Eth_17_GEthMacV2_lCfgRxQueue(EthCtrlCfgPtr);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1658B198-2C2A-4804-809C-D75C869D8453}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDmaCoreInit(const         **
**                 Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)  **
**                                                                            **
** Description      : Configure DMA channels                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDmaCoreInit(
               const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint8 LoopCount;
  uint8 MaxChannelsCfgd;

  /* Get controller status */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  MaxChannelsCfgd = EthCtrlCfgPtr->EthNumRxChnls;

  /* Configure DMA Bus mode register. */
  /* [cover parentID={547DBC3B-C084-46a6-86E6-983BF3C2A291}]
  [/cover] */
  EthCtrlAddPtr->DMA_MODE.U = ETH_17_GETHMACV2_DMA_BUS_MODE_INIT_CONF |
   ((uint32)EthCtrlCfgPtr->EthDmaTxArbAlg << (uint8)IFX_GETH_DMA_MODE_TAA_OFF);

  /* Configure DMA system bus mode register */
  EthCtrlAddPtr->DMA_SYSBUS_MODE.U = ETH_17_GETHMACV2_DMA_SYSBUS_MODE_INIT_CONF;

  /* [cover parentID={0BA9F546-D305-4c5e-87BB-80F00D8B8C0E}]
  Configure Tx burst, beat length and the channel weights for the required
  Tx DMA channels
  [/cover] */
  for (LoopCount = 0U; LoopCount < EthCtrlCfgPtr->EthNumTxChnls; LoopCount++)
  {
    /* Configure the burst length and weights */
    EthCtrlAddPtr->DMA_CH[LoopCount].TX_CONTROL.U =
        ((uint32)ETH_17_GETHMACV2_DMA_CH_TXCTRL_CONF |
        ((uint32)EthCtrlCfgPtr->EthTxFifoCfgPtr[EthCtrlCfgPtr->
                 EthTxChnlFifoMapPtr[LoopCount]].TxDmaChnlWght <<
                               IFX_GETH_DMA_CH_TX_CONTROL_TCW_OFF));
  }

  for (LoopCount = 0U; LoopCount < EthCtrlCfgPtr->EthNumRxChnls; LoopCount++)
  {
    /* Configure Rx PBL (Receive burst length).*/
    EthCtrlAddPtr->DMA_CH[LoopCount].RX_CONTROL.B.RXPBL =
                                    (uint8)ETH_17_GETHMACV2_DMA_CH_RXPBL;
  }

  /* get the max of Tx and Rx channels configured */
  if (EthCtrlCfgPtr->EthNumTxChnls > EthCtrlCfgPtr->EthNumRxChnls)
  {
    MaxChannelsCfgd = EthCtrlCfgPtr->EthNumTxChnls;
  }

  for (LoopCount = 0U; LoopCount < MaxChannelsCfgd; LoopCount++)
  {
    /* Configure Tx and Rx Transfer burst and beat length */
    EthCtrlAddPtr->DMA_CH[LoopCount].CONTROL.B.PBLX8 =
                             (uint8)ETH_17_GETHMACV2_DMA_8X_BURST_LENGTH_MODE;
  }

  /* Configure Tx Descriptors */
  Eth_17_GEthMacV2_lDmaTxDescriptorInit(EthCtrlCfgPtr);

  /* Configure Rx Descriptors */
  Eth_17_GEthMacV2_lDmaRxDescriptorInit(EthCtrlCfgPtr);

  /* [cover parentID={1C34B05D-4FC9-4824-BF64-CB1874B1255A}]
  Enable DMA Tx and Rx Interrupt
  [/cover] */
  Eth_17_GEthMacV2_lEnableGethInterrupt(EthCtrlCfgPtr);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9D738E73-F321-432b-87A4-A544198515D0}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDmaTxDescriptorInit(const **
**                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Configure DMA Transmit Descriptors list                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDmaTxDescriptorInit(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMacV2_TxBuffTableType *EthLocalTxBuffTablePtr;
  Eth_17_GEthMacV2_TxDescBufMapStType *EthLocalTxDescTablePtr;
  Eth_17_GEthMacV2_DmaTxDescType *EthLocalDmaTxDescPtr;
  Ifx_GETH *EthCtrlAddPtr;
  uint16 QElemLpCnt;
  uint16 TxBufPerChnl;
  uint8 TxChnlsUsd;
  uint8 ChnlMap;
  uint8 FifoIdx;
  uint8 FifoLpCnt;
  uint8 BufLpCnt;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(
                                       EthCtrlCfgPtr->EthCtrlIdx);

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Get the number of Tx channels */
  TxChnlsUsd = EthCtrlCfgPtr->EthNumTxChnls;

  /* Initialize the necessary parameters/ values for all the Tx channels */
  /* [cover parentID={C3533C98-F5B4-471c-B68B-4827E4548B1E}]
  Loop till the required total number of Tx DMA channels
  [/cover] */
  for (FifoLpCnt = 0U; FifoLpCnt < TxChnlsUsd; FifoLpCnt++)
  {
    /* Get the number Tx buffers configured within a FIFO */
    TxBufPerChnl = EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoLpCnt].NumOfTxBuffers;

    /* Get the channel mapped to the Tx FIFO */
    ChnlMap = EthCtrlCfgPtr->EthTxFifoChnlMapPtr[FifoLpCnt];

    /* Get the Tx FIFO index */
    FifoIdx = EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoLpCnt].TxFifoIdx;

    EthLocalTxBuffTablePtr = EthLocalCoreStatusPtr->
                          EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx];

    EthLocalDmaTxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                           EthDmaTxDescPtr[FifoIdx];

    EthLocalTxDescTablePtr = EthLocalCoreStatusPtr->
                          EthBuffDescPtr->EthTxDescBufMapStPtr[FifoIdx];

    /* [cover parentID={3C5A32B9-2DFE-4c57-8DC3-A3A4FA1854C6}]
    Loop until the last buffer index within the FIFO
    [/cover] */
    for (BufLpCnt = 0U; BufLpCnt < TxBufPerChnl; BufLpCnt++)
    {
      /* Clear Buffer Table Parameters */
      EthLocalTxBuffTablePtr[BufLpCnt].BuffStatus =
                                          ETH_17_GETHMACV2_BUFFER_NOTUSED;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
      EthLocalTxBuffTablePtr[BufLpCnt].TimeStampEnable =
                                          ETH_17_GETHMACV2_DISABLE;
#endif

      EthLocalTxDescTablePtr[BufLpCnt].TxConfirmReq = ETH_17_GETHMACV2_DISABLE;

      EthLocalTxDescTablePtr[BufLpCnt].FrameTxInitiated =
                                          ETH_17_GETHMACV2_DISABLE;

      EthLocalTxDescTablePtr[BufLpCnt].TxDescBufMapIdx = 0U;

      /* Start Initializing the common fields of Tx Descriptors */
      /* Descriptor Buffer2 pointer not used */
      EthLocalDmaTxDescPtr[BufLpCnt].TDES1 = (uint32)0U;

      /* Enable Interrupt on transmission completion.Buffer length/Packet length
         in TDES2 and TDES3 will be updated during Transmit request*/
      EthLocalDmaTxDescPtr[BufLpCnt].TDES2 =
                                  (uint32)ETH_17_GETHMACV2_DMA_TDES2_INIT;
    }

    /* Configure TX-DMA-CH Descriptor tail pointer with start of DmaTxDesc
    array address. During each transmission request, descriptor tail pointer
    will be advanced */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long is
     performed to assign last buffer address to tail pointer register. This is
     the intended design and valid as per DMA hardware design. There are no
     side effects seen by violating this rule.*/
    EthCtrlAddPtr->DMA_CH[ChnlMap].TXDESC_TAIL_POINTER.U =\
                            (uint32)(&EthLocalDmaTxDescPtr[0U]);

    /* Configure TX-DMA-CH Descriptor list address with start
       of DmaTxDesc array address.*/
     /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
       integer type is performed to assign last buffer address to list address
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
     /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
        is performed to to assign last buffer address to list address
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
    EthCtrlAddPtr->DMA_CH[ChnlMap].TXDESC_LIST_ADDRESS.U =\
                            (uint32)(&EthLocalDmaTxDescPtr[0U]);

    /* Configure TX-DMA-CH Descriptor ring length with total number
       of Tx descriptor minus 1 */
    EthCtrlAddPtr->DMA_CH[ChnlMap].TXDESC_RING_LENGTH.U =
                       ((uint32)TxBufPerChnl - (uint32)1U);

    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmTxChnlDataPtr[FifoIdx].CurrTxDmaDescIdx = 0U;

    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmTxChnlDataPtr[FifoIdx].CnfrmTxDmaDescIdx = 0U;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
    EthLocalCoreStatusPtr->EthBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].
                      TxDmaDescIdxTmStmp = ETH_17_GETHMACV2_DMADESC_INVALID;
#endif

    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront = 0U;

    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear = (TxBufPerChnl - 1U);

    /* Pre-fill the buffer index queue with initial values */
    for (QElemLpCnt = 0U; QElemLpCnt < TxBufPerChnl; QElemLpCnt++)
    {
      EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffQueuePtr[FifoIdx]
                              [QElemLpCnt] = QElemLpCnt;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7EC2052E-1FBD-4831-91A3-275A3D114D29}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDmaRxDescriptorInit(const **
**                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Configure DMA Receive Descriptors list                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDmaRxDescriptorInit(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  uint32 LoopCount;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMacV2_DmaRxDescType *EthLocalDmaRxDescPtr;
  Ifx_GETH *EthCtrlAddPtr;
  const volatile uint8 *RxBuffBasePtr;
  uint16 RxBufLengthAligned;
  uint16 RxBufPerChnl;
  uint16 ChnlCnt;
  uint8 RxChnlsUsd;
  uint8 ChnlMap;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(
                                          EthCtrlCfgPtr->EthCtrlIdx);

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Get the number of Rx channels */
  RxChnlsUsd = EthCtrlCfgPtr->EthNumRxChnls;

  /* Initialize the necessary parameters/ values for all the Rx channels */
  /* [cover parentID={2526F622-67E6-486b-80A8-553EEBF95A5A}]
  Loop till the required total number of Rx DMA channels
  [/cover] */
  for (LoopCount = 0U; LoopCount < RxChnlsUsd; LoopCount++)
  {
    /* Get the number of buffers configured with the Rx FIFO */
    RxBufPerChnl = EthCtrlCfgPtr->EthRxFifoCfgPtr[LoopCount].NumOfRxBuffers;

    /* Get the Rx buffer aligned size */
    RxBufLengthAligned = EthCtrlCfgPtr->
                EthRxFifoCfgPtr[LoopCount].RxBufferAlignSize;

    /* Get the channel number assigned to the FIFO */
    ChnlMap = EthCtrlCfgPtr->EthRxFifoChnlMapPtr[LoopCount];

    /* Get Start Address of Rx Buffer*/
    RxBuffBasePtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                       EthRxBufferPtr[LoopCount];

    /* Get the base address of the Rx descriptor for the FIFO */
    EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr->
                                         EthDmaRxDescPtr[LoopCount];

    /* [cover parentID={A8DF995C-7EDA-4ebd-91A5-6267C1BC0B69}]
    Loop until the last buffer index within the FIFO
    [/cover] */
    for (ChnlCnt = 0U; ChnlCnt < RxBufPerChnl; ChnlCnt++)
    {
      /* Start Initializing Rx Descriptors */
      /* [cover parentID={42D4A560-4518-40cd-ACB8-7BD679273378}]
      [/cover] */
      /* Assign the Receive Buffer pointer to the Descriptor buffer pointer */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
      pointer type is performed to access the buffer address from DMA
      descriptor. This is the intended design and valid as per DMA hardware
      design. There are no side effects seen by violating this rule.*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
      is performed to access the buffer address from DMA descriptor.
      This is the intended design and valid as per DMA hardware design.
      There are no side effects seen by violating this rule.*/
      EthLocalDmaRxDescPtr[ChnlCnt].RDES0 = ((uint32)RxBuffBasePtr +
                        ((uint32)ChnlCnt * RxBufLengthAligned));

      /* Descriptor Buffer2 pointer not used */
      EthLocalDmaRxDescPtr[ChnlCnt].RDES2 = 0U;

      /* Set OWN bit, Enable Interrupt on completion, Set Buffer1 valid */
      EthLocalDmaRxDescPtr[ChnlCnt].RDES3 =
                                    (uint32)ETH_17_GETHMACV2_DMA_RDES3_INIT;
    }

    /* Configure Size of one Rx buffer (which is RxBufLenByteAligned)*/
    EthCtrlAddPtr->DMA_CH[ChnlMap].RX_CONTROL.B.RBSZ_13_Y =
                 (uint16)(RxBufLengthAligned >> ETH_17_GETHMACV2_RBSZ_13_Y);

    /*Configure RX- DMA-CH0 Descriptor list address with start
      of DmaRxDesc array address.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
    integer type is performed to assign last buffer address to list address
    register. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
    to assign last buffer address to list address register. This is the
    intended design and valid as per DMA hardware design. There are no side
    effects seen by violating this rule.*/
    EthCtrlAddPtr->DMA_CH[ChnlMap].RXDESC_LIST_ADDRESS.U =\
                            (uint32)(&EthLocalDmaRxDescPtr[0U]);

    /* Configure Rx-DMA-CH Descriptor tail pointer with last Rx descriptor
      address plus 1*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
       integer type is performed to assign last buffer address to tail pointer
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       to assign last buffer address to list address
       register. This is the intended design and valid as per DMA hardware
       design. There are no side effects seen by violating this rule.*/
    EthCtrlAddPtr->DMA_CH[ChnlMap].RXDESC_TAIL_POINTER.U =\
                            (uint32)(&EthLocalDmaRxDescPtr[RxBufPerChnl]);

    /* Configure Rx-DMA-CH Descriptor ring length with total number
      of Rx descriptor minus 1 */
    EthCtrlAddPtr->DMA_CH[ChnlMap].RXDESC_RING_LENGTH.U =
                 (uint32)((uint32)RxBufPerChnl - (uint32)1U);

    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmRxChnlDataPtr[LoopCount].CurrRxDmaDescIdx = 0U;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
    EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmRxChnlDataPtr[LoopCount].RxDmaDescIdxTmStmp =
                                        ETH_17_GETHMACV2_DMADESC_INVALID;
#endif
  }
}

#if (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={BF7F6745-83EB-4ba6-B25C-D5A9176A58F7}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lTimerInit (     **
**                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : The function initializes Timer Registers for            **
**                                 IEEE 1588 Timestamp support                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Timer Init finished successfully             **
**                    E_NOT_OK - Timer Init is not successful                 **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lTimerInit(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  uint32 TimerInitWaitTicks;
  uint32 DelayTickResolution;
  Ifx_GETH *EthCtrlAddPtr;
  Std_ReturnType RetValue;
  boolean IsTimeExpired;

  RetValue = E_NOT_OK;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Get STM timer current resolution and calculate maximum number of ticks
  to wait before expected hardware behaviour has occurred- That timer init*/
  DelayTickResolution = Mcal_DelayTickResolution();

  TimerInitWaitTicks = (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT /
                                            DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={F453757C-57C6-47af-96B4-52A7B5E6C129}]
  If STM resolution is zero
  [/cover] */
  if(TimerInitWaitTicks == 0U)
  {
    /* Increment the ticks */
    TimerInitWaitTicks++;
  }

  /* Timestamp Enable */
  /* Disable Processing of PTP frames Sent over IPv4-UDP.
     In default, it is enabled.*/
  EthCtrlAddPtr->MAC_TIMESTAMP_CONTROL.U = ETH_17_GETHMACV2_TS_ENABLE;

  /* Insert delay for back to back register writes */
  Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(EthCtrlCfgPtr->EthBkRegWrWaitTime);

  /* Initialize system time higher word second with ZERO.*/
  EthCtrlAddPtr->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = 0U;

  /* Initialize system time(Second and Nanosecond part) with  ZERO.*/
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  EthCtrlAddPtr->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = 0U;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
   characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  EthCtrlAddPtr->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.U = 0U;

  /*      ------------------------------------------------------------
   *                       TIME - COARSE UPDATE
   *      ------------------------------------------------------------
   *                (Not used currently in this function,
   *                described here just for information )
   *
   *   Consider for 50 Mhz Peripheral Bus frequency ,
   *                   ptp clock frequency = 50 Mhz.
   *
   *   Time period = 1/(50 * 10^6) seconds = 20 ns.
   *
   *   Value loaded in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register is
   *   added to nano second on every PTP clock cycle.
   *
   *   Hence Min resolution = 20 ns. That is, 20 counts should be loaded in
   *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register.
   *
   *   General formula for value to be
   *   loaded in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC = 1000/ EthOpetnFreq,
   *   where EthOpetnFreq is Ethernet Peripheral operation frequency in MHz. ;
   *
   *     ------------------------------------------------------------
   *                        TIME - FINE UPDATE
   *     ------------------------------------------------------------
   *                   (Used currently in this function )
   *
   *   System Time Update logic requires a 50-MHz clock frequency to
   *   achieve 20-ns accuracy, 50MHz clock is internal to GETH-IP.
   *
   *   Here on every PTP clock cycle(which is Ethernet Peripheral
   *   Bus frequency) Accumulator register( which is internal to GETH IP) is
   *   added with the contents of MAC_TIMESTAMP_ADDEND register.
   *   The arithmetic carry(Due to overflow of Accumulator ) that the
   *   Accumulator generates is used as a pulse to increment the system time
   *   counter. Every time pulse is generated, it represents 20 ns as per below
   *   calculated addend value ,so always value to  be initialized to
   *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC is 20
   *
   *   Value to be loaded to MAC_TIMESTAMP_ADDEND register =
   *                                              2^32/FreqDivisionRatio
   *
   *   where FreqDivisionRatio = PTP clock frequency/ 50 = EthOpetnFreq/50
   *
   *   The MAC_TIMESTAMP_ADDEND register value is directly generated and used
   *
   * */

  /*Update SSINC value.*/
  EthCtrlAddPtr->MAC_SUB_SECOND_INCREMENT.B.SSINC =
                                    ETH_17_GETHMACV2_SUB_SEC_INCREMENT_VAL;

  /*Update ADDEND register */
  EthCtrlAddPtr->MAC_TIMESTAMP_ADDEND.U =
                        (uint32)ETH_17_GETHMACV2_TIMESTAMP_ADDEND_VAL;

  /* Wait until Update Addend Register bit is Reset.*/
  IsTimeExpired = Eth_17_GEthMacV2_lTsAdRegTimeout(EthCtrlCfgPtr->EthCtrlIdx,
                                                   TimerInitWaitTicks);

  /* If timeout has occurred, report Production error for timeout */
  Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired,EthCtrlCfgPtr->EthDemAccess);

  /* [cover parentID={E095781D-93F4-4c82-B880-08B131839625}]
  Did Timeout occur ?
  [/cover] */
  if (IsTimeExpired == FALSE)
  {
    /* Set Update Addend Register bit to update content of the
    Timestamp Addend register.*/
    /* Time stamp Fine update */
    /* Timestamp digital roll over control for 1 nanosecond accuracy
       That is, each value in nanosecond register represent 1ns */
    EthCtrlAddPtr->MAC_TIMESTAMP_CONTROL.U |= (((uint32)ETH_17_GETHMACV2_ENABLE
        << IFX_GETH_MAC_TIMESTAMP_CONTROL_TSCFUPDT_OFF) |
        ((uint32)ETH_17_GETHMACV2_ENABLE <<
         IFX_GETH_MAC_TIMESTAMP_CONTROL_TSADDREG_OFF) |
        ((uint32)ETH_17_GETHMACV2_ENABLE <<
         IFX_GETH_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_OFF));

    /* Insert delay for back to back register writes */
    Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(EthCtrlCfgPtr->EthBkRegWrWaitTime);

    /* The Update Addend Register bit is cleared when the update is
    completed.Wait until Update Addend Register bit is cleared*/
    IsTimeExpired = Eth_17_GEthMacV2_lTsAdRegTimeout(EthCtrlCfgPtr->EthCtrlIdx,
                                                     TimerInitWaitTicks);

    /* If timeout has occurred, report Production error for timeout */
    Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired, EthCtrlCfgPtr->EthDemAccess);

    /* [cover parentID={993E2B27-29EB-45a0-B4F0-D30110784B52}]
    Did Timeout occur ?
    [/cover] */
    if (IsTimeExpired == FALSE)
    {
      /* Wait for TSINIT bit is Reset to start Timestamp Initialization*/
      IsTimeExpired = Eth_17_GEthMacV2_lTsInitTimeout(EthCtrlCfgPtr->EthCtrlIdx,
                                                      TimerInitWaitTicks);

      /* If timeout has occurred, report Production error for timeout */
      Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired, EthCtrlCfgPtr->EthDemAccess);

      /* [cover parentID={F75528F5-95FD-4e62-8B65-7FED7E508DAF}]
      Did Timeout occur ?
      [/cover] */
      if (IsTimeExpired == FALSE)
      {
        /* Initialize Time stamp.*/
        /*Add time stamp for all frames */
        EthCtrlAddPtr->MAC_TIMESTAMP_CONTROL.U |=
          (((uint32)ETH_17_GETHMACV2_ENABLE <<
            IFX_GETH_MAC_TIMESTAMP_CONTROL_TSINIT_OFF) |
              ((uint32)ETH_17_GETHMACV2_ENABLE <<
               IFX_GETH_MAC_TIMESTAMP_CONTROL_TSENALL_OFF));

        /* The TSINIT Register bit is cleared when when the initialization is
        completed. Wait until TSINIT Register bit is cleared */
        IsTimeExpired = Eth_17_GEthMacV2_lTsInitTimeout(
                                EthCtrlCfgPtr->EthCtrlIdx, TimerInitWaitTicks);

        /* If timeout has occurred, report Production error for timeout */
        Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired,EthCtrlCfgPtr->EthDemAccess);

        /* [cover parentID={E80234FC-7577-4983-A5C2-E975E042A432}]
        Did Timeout occur ?
        [/cover] */
        if (IsTimeExpired == FALSE)
        {
          RetValue = E_OK;
        }
      }
    }
  }

  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1EC857EF-E045-46ab-87C9-590802B2DB42}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_GEthMacV2_lTsAdRegTimeout(        **
**                                         const uint8 CtrlIdx,               **
**                                         const uint32 WaitTicks)            **
**                                                                            **
** Description      : Function to check that MAC_TIMESTAMP_CONTROL.TSADDREG   **
**                    bit is cleared before timeout happens                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : WaitTicks - Number of ticks to wait for timeout         **
**                    CtrlIdx - Controller Index.                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE - Register Bit cleared and no timeout detected    **
**                    TRUE -  Register Bit not cleared and timeout detected   **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_GEthMacV2_lTsAdRegTimeout(const uint8 CtrlIdx,
                                                const uint32 WaitTicks)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 RegVal;
  const Ifx_GETH *EthCtrlAddPtr;
  boolean IsTimeExpired;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* Wait until Update Addend Register bit is cleared.*/
  /* Get current STM tick */
  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  IsTimeExpired = FALSE;

  do
  {
    RegVal = (uint32)EthCtrlAddPtr->MAC_TIMESTAMP_CONTROL.B.TSADDREG;

    /* [cover parentID={CEAF3B07-FDA8-4bc6-8E49-BF2EEB3F56A6}]
    (current tick - first time tick) < Maximum time to wait for
    Hardware time out error
    [/cover] */
    /* Check wait time is reached at maximum timeout configured */
    if((((uint32)((CurrSTMTick - BaseSTMTick) &
          ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >=
          WaitTicks) && (RegVal == (uint32)ETH_17_GETHMACV2_BUSY_ST))
    {
      /* Timeout occurred and Update Addend Register bit is not cleared yet */
      IsTimeExpired = TRUE;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();

    /* [cover parentID={EC42C226-79BC-4c98-959B-495694A600D4}]
    Update Addend Register bit is cleared
    [/cover] */
  }while((RegVal == (uint32)ETH_17_GETHMACV2_BUSY_ST) &&
                                  (IsTimeExpired == FALSE));

  return IsTimeExpired;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={BB021551-7B56-42fb-8FE0-2AF294FCC3F4}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_GEthMacV2_lTsInitTimeout(         **
**                                         const uint8 CtrlIdx,               **
**                                         const uint32 WaitTicks)            **
**                                                                            **
** Description      : Function to check that MAC_TIMESTAMP_CONTROL.TSINIT     **
**                    bit is cleared before timeout happens                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : WaitTicks - Number of ticks to wait for timeout         **
**                    CtrlIdx - Controller Index.                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE - Register Bit cleared and no timeout detected    **
**                    TRUE -  Register Bit not cleared and timeout detected   **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_GEthMacV2_lTsInitTimeout(const uint8 CtrlIdx,
                                               const uint32 WaitTicks)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 RegVal;
  const Ifx_GETH *EthCtrlAddPtr;
  boolean IsTimeExpired;

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* Wait for TSINIT bit is cleared */
  /*Get current STM tick*/
  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  IsTimeExpired = FALSE;

  do
  {
    RegVal = (uint32)EthCtrlAddPtr->MAC_TIMESTAMP_CONTROL.B.TSINIT;

    /* [cover parentID={90B72758-80C0-4a0b-AAEC-236933972D5C}]
    (current tick - first time tick) < Maximum time to wait for
    Hardware time out error
    [/cover] */
    /* Check wait time is reached at maximum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) &
          ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= WaitTicks) &&
          (RegVal == (uint32)ETH_17_GETHMACV2_BUSY_ST))
    {
      /*Timeout occurred and TSINIT bit is not cleared yet*/
      IsTimeExpired = TRUE;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();

    /* [cover parentID={88DBFEEB-A72E-4d9e-8303-33270C375F6A}]
    TSINIT Register bit is cleared
    [/cover] */
  }while((RegVal == (uint32)ETH_17_GETHMACV2_BUSY_ST) &&
                                  (IsTimeExpired == FALSE));

  return IsTimeExpired;
}
#endif /*end of ETH_17_GETHMACV2_GLOBALTIMESUPPORT */

#if((ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON) &&\
    (ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F9F460D5-C4EE-4cf9-BC6B-1950BAB1BAAA}]  **
**                                                                            **
** Syntax           : uint8 Eth_17_GEthMacV2_lDetCheckBufIdx (                **
**                      const uint8 CtrlIdx, const uint8 ServiceId,           **
**                      const uint16 FifoIdxMap, const uint16 BufferIdx)      **
**                                                                            **
** Description      : Development error check for the buffer index parameter  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller Mode                  **
**                    ServiceId - Service ID of the API                       **
**                    FifoIdxMap - Internal FIFO index reference              **
**                    BufferIdx - Index of the buffer                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR - Parameter is valid      **
**                    ETH_17_GETHMACV2_E_INV_PARAM - Parameter is invalid     **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetCheckBufIdx(const uint8 CtrlIdx,
                                              const uint8 ServiceId,
                                              const uint16 FifoIdxMap,
                                              const uint16 BufferIdx)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint16 TxBufTotal;
  uint8 DevError;

  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* [cover parentID={A7AE00B2-AD80-4858-9E2A-E125C1DC9AA7}]
  If channel index is within the range of configured channels
  [/cover] */
  if (FifoIdxMap >= EthLocalCtrlCfgPtr->EthNumTxChnls)
  {
    /* [cover parentID={FA55E5E9-5244-4d66-9DFA-A9CB1789180A}]
    Report DET error ( Invalid Parameter)
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                          ETH_17_GETHMACV2_E_INV_PARAM);

    DevError = ETH_17_GETHMACV2_E_INV_PARAM;
  }
  else
  {
    /* Get the total number of buffers configured */
    TxBufTotal = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr
                                        [FifoIdxMap].NumOfTxBuffers;

    /* [cover parentID={511F653E-A1C3-4147-9125-83F0F12AE2F9}]
    BufIdx(Input parameter) less than Total Tx buffer allocated
    [/cover] */
    if(BufferIdx >= TxBufTotal)
    {
      /* [cover parentID={FA55E5E9-5244-4d66-9DFA-A9CB1789180A}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                            ETH_17_GETHMACV2_E_INV_PARAM);

      DevError = ETH_17_GETHMACV2_E_INV_PARAM;
    }
    else
    {
      /* Do nothing. No action required */
    }
  }

  return DevError;
}
#endif /* end of GLOBALTIMESUPPORT && DEV_ERROR_DETECT == STD_ON */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D7BD2459-9B01-4442-BFD5-DE969B219D10}]  **
**                                                                            **
** Syntax          : void Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly (const        **
**                                             uint32 EthDelayWaitTime)       **
**                                                                            **
** Description     : Inserts the required delay for back to back register     **
**                    write operations                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  None                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  EthDelayWaitTime - Wait time in ns to be inserted for   **
**                      back to back register writes                          **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lBkToBkRegWrInsrtDly(const uint32 EthDelayWaitTime)
{
  uint32 NumberWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;

  /* Get STM timer current resolution and calculate number of ticks to wait*/
  DelayTickResolution = Mcal_DelayTickResolution();

  NumberWaitTicks = (EthDelayWaitTime / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={0D4B6B80-ED07-4987-B086-C68E2B4AD5C1}]
  If the number of ticks is zero
  [/cover] */
  if(NumberWaitTicks == 0U)
  {
    /* Increment the tick */
    NumberWaitTicks++;
  }

  /*Get current STM tick*/
  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  IsTimeExpired = FALSE;

  /* Wait until necessary time has elapsed */
  do
  {
    /* Check wait time has reached maximum timeout configured */
    /* [cover parentID={D34510BE-0A97-4254-9CA9-3C833855FDC4}]
    Has the necessary time elapsed?
    [/cover] */
    if(((uint32)((CurrSTMTick - BaseSTMTick) &
         ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >= NumberWaitTicks)
    {
      /* Necessary time has elapsed */
      IsTimeExpired = TRUE;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while(IsTimeExpired == FALSE);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={6FB62E43-277B-416a-9E6C-07D8467F843F}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lTransmit(       **
**                       const uint8 CtrlIdx,                                 **
**                       const Eth_BufIdxType BufIdx,                         **
**                       const Eth_FrameType FrameType,                       **
**                       const boolean TxConfirmation,                        **
**                       const uint16 LenByte, const uint8* const PhysAddrPtr)**
**                                                                            **
** Description      : Triggers transmission of a previously                   **
**                     filled transmit buffer                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index.                             **
**                    BufIdx - Index of the buffer resource                   **
**                    FrameType- Ethernet frame type                          **
**                    TxConfirmation - Activates transmission confirmation    **
**                    LenByte - Data length in byte                           **
**                    PhysAddrPtr - Physical target address                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK- Transmission request is successfully placed       **
**                    E_NOT_OK: Transmission failed                           **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lTransmit(
             const uint8 CtrlIdx,
             const Eth_BufIdxType BufIdx, const Eth_FrameType FrameType,
             const boolean TxConfirmation, const uint16 LenByte,
             const uint8* const PhysAddrPtr)
{
  uint8* TxBufAddrPtr;
  uint32 TxLength;
  uint32 LoopCount;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  Ifx_GETH *EthCtrlAddPtr;
#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  /* uint8* EthBufPtr; */
  /* uint16 EthLenByte; */
  uint16 TxBufLengthConfig;
#endif
  uint16 TxBufLengthAligned;
  uint16 BufferIdx;
  uint16 FifoIdx;
  uint16 TxDescIdx;
  uint8 PrioVal;
  Std_ReturnType RetVal;

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_OFF)
  RetVal = E_OK;
#endif

  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  /* Get base address of the indexed controller */
  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[CtrlIdx];

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  /* Get the required indices of the buffers/ FIFOs */
  BufferIdx = (uint16)(BufIdx & (uint32)ETH_17_GETHMACV2_BUFIDX_MASK);

  PrioVal = (uint8)((BufIdx & (uint32)ETH_17_GETHMACV2_VLDCHNLIDX_MASK) >>
                                      (uint8)ETH_17_GETHMACV2_FIFOIDX_POS);

  FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioVal].TxFifoIdx;

  TxBufLengthAligned = EthLocalCtrlCfgPtr->
                          EthTxFifoCfgPtr[PrioVal].TxBufferAlignSize;

  /* Load the start address of the current Tx Buffer */
  /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
  expression is performed to access the buffer address from DMA
  descriptor. This is the intended design and valid as per DMA hardware
  design. There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
  is performed to access the buffer address from DMA descriptor.
  This is the intended design and valid as per DMA hardware design.
  There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a pointer
  type is performed to access the buffer address from DMA descriptor. This is
  the intended design and valid as per DMA hardware design. There are no side
  effects seen by violating this rule.*/
  TxBufAddrPtr = (uint8*)(((uint32)&(EthLocalCoreStatusPtr->EthBuffDescPtr->\
                     EthTxBufferPtr[FifoIdx][0U])) +\
                    ((uint32)BufferIdx * TxBufLengthAligned));

  /* [cover parentID={3E1D4710-3036-4e40-95B1-081A95193AF0}]
  Fill the Destination MAC Address in Tx Buffer
  [/cover] */
  for(LoopCount = 0U;
      LoopCount < (uint32)ETH_17_GETHMACV2_MACADDRESS_LEN; LoopCount++)
  {
    TxBufAddrPtr[LoopCount] = (uint8)PhysAddrPtr[LoopCount];
  }

  /* [cover parentID={FDB450FF-3812-4087-8FDA-80AE25A6D3DD}]
  Fill the Source MAC address in Tx  buffer
  [/cover] */
  /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
  expression is performed to access the buffer address from DMA
  descriptor. This is the intended design and valid as per DMA hardware
  design. There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
  is performed to access the buffer address from DMA descriptor.
  This is the intended design and valid as per DMA hardware design.
  There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a pointer
  type is performed to access the buffer address from DMA descriptor. This is
  the intended design and valid as per DMA hardware design. There are no side
  effects seen by violating this rule.*/
  Eth_17_GEthMacV2_lGetPhysAddr(CtrlIdx, (uint8 *)((uint32)TxBufAddrPtr +\
                                (uint32)ETH_17_GETHMACV2_FRAME_SRCADDR_POS));

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
    [BufferIdx].SwtTxDataPtr = (uint8*)(&TxBufAddrPtr
                                    [ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS]);

  EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                                  [BufferIdx].SwtTxLength = LenByte;

  /* [cover parentID={B0F44ED5-FAC3-44cf-A527-6EBE345F2DA2}]
  Invoke the switch driver API is to insert management information
  [/cover] */
  RetVal = EthSwt_EthTxProcessFrame(CtrlIdx, BufIdx, &EthLocalCoreStatusPtr->
            EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxDataPtr,
            &EthLocalCoreStatusPtr->EthBuffDescPtr->
                EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength);

  /* Management info inserted into the frame by the switch driver */
  /* [cover parentID={01772BFC-9D89-4cd2-A2D4-6CD28F3F630A}]
  Is E_OK returned by the EthSwt_EthTxProcessFrame API ?
  [/cover] */
  if (RetVal == E_OK)
  {
    /* Get the configured Tx buffer size */
    TxBufLengthConfig = EthLocalCtrlCfgPtr->
                            EthTxFifoCfgPtr[PrioVal].TxBufferSize;

    /* [cover parentID={C7707DF3-A878-4ad6-BFF8-90850BC5C2B6}]
    If the modified length exceeds the configured buffer size or
    if the modified length is reduced from the actual requested length
    [/cover] */
    if ((EthLocalCoreStatusPtr->EthBuffDescPtr->
         EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength > (TxBufLengthConfig
          - ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
              ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH)))) ||
        (EthLocalCoreStatusPtr->EthBuffDescPtr->
           EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength < LenByte))
    {
      /* Error - incorrect length modification by the switch driver */
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={E8E96AB3-A30E-4d6c-BCB2-9B254783FB32}]
    Is data pointer modified by the switch driver correct?
    [/cover] */
    else if (EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
        [BufferIdx].SwtTxDataPtr != (uint8*)(&TxBufAddrPtr
        [(ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS + (EthLocalCoreStatusPtr->
        EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength -
                                                                LenByte))]))
    {
      /* Error due to incorrect data pointer modification by the
         switch driver */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* Increment the buffer address by the number of bytes of
         management information needed */
      TxBufAddrPtr = (uint8 *)(&TxBufAddrPtr[EthLocalCoreStatusPtr->
              EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength
                        - LenByte]);
    }
  }

  /* [cover parentID={BE829930-6E29-4fed-82B2-B8D0DB95E308}]
  Is return value E_OK ?
  [/cover] */
  if (RetVal == E_OK)
#endif  /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */
  {
  /* [cover parentID={03687AE0-F00F-4945-ABC6-403EBD2560F6}]
  Fill the Frame Type in Tx Buffer
  [/cover] */
  /* Fill the Frame Type in TX Buffer */
  TxBufAddrPtr[ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS] = (uint8)((FrameType >>
                ETH_17_GETHMACV2_SHIFT_8BIT) & ETH_17_GETHMACV2_BYTE_MASK);

  TxBufAddrPtr[ETH_17_GETHMACV2_FRAME_TYPE_LSB_POS] =
                   (uint8)(FrameType & ETH_17_GETHMACV2_BYTE_MASK);

#if ((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON  ) || \
     (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON  ))

    Eth_17_GEthMacV2_lCheckForICMPV4Frame(&TxBufAddrPtr[0U], FrameType);
#endif

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_OFF)
  /*Buffer2 size would be zero, single buffer and single frame at the time.
  Here Header length(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH) is added because
  provideTxbuffer API only provides the Payload buffer.*/
  TxLength = (uint32)(((uint32)LenByte + ETH_17_GETHMACV2_FRAMEHEADER_LENGTH) &
                  (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_PAC_LEN_MASK);
#else
  /*Buffer2 size would be zero, single buffer and single frame at the time.
  Here Header length(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH) is added because
  provideTxbuffer API only provides the Payload buffer.*/
  TxLength = (uint32)(((uint32)EthLocalCoreStatusPtr->
            EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx][BufferIdx].SwtTxLength +
                  ETH_17_GETHMACV2_FRAMEHEADER_LENGTH) &
                  (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_PAC_LEN_MASK);
#endif

  /* [cover parentID={DC8B3F8D-8431-4add-A675-1DD5AE104C79}]
  Critical section to protect the transmit descriptor to buffer mapping
  and status data
  [/cover] */
  /* [cover parentID={685D99A7-831D-4f54-AFC0-E712F97A6B4D}]
  [/cover] */
  /* [cover parentID={F3796E26-6D5A-4cd2-B773-EEE3F31E016E}]
  Enter Critical Section
  [/cover] */
  SchM_Enter_Eth_17_GEthMacV2_TxDescData();

  TxDescIdx = EthLocalCoreStatusPtr->EthBuffDescPtr->
                    EthRunTmTxChnlDataPtr[FifoIdx].CurrTxDmaDescIdx;

  /* [cover parentID={2D939499-1ADF-4a03-98E9-3B916B1F6E46}]
  Tx Confirmation Needed
  [/cover] */
  if(TxConfirmation == (boolean)TRUE)
  {
    /* [cover parentID={182EFBE2-D8B1-4083-8490-20E9EA18DE71}]
    Set Tx Confirmation as NEEDED in Tx Mapping and status Table
    (at BufIdx location)
    [/cover] */
    EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxDescBufMapStPtr
            [FifoIdx][TxDescIdx].TxConfirmReq = ETH_17_GETHMACV2_ENABLE;
  }
  else
  {
    /* Set Tx Confirmation as NOT NEEDED in Tx Buffer Table
    (at BufIdx location) */
    EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxDescBufMapStPtr
            [FifoIdx][TxDescIdx].TxConfirmReq = ETH_17_GETHMACV2_DISABLE;
  }

  /*Assign the TDES0 to the current buffer pointer*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
  pointer type is performed to access the buffer address from DMA
  descriptor. This is the intended design and valid as per DMA hardware
  design. There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
  is performed to access the buffer address from DMA descriptor.
  This is the intended design and valid as per DMA hardware design.
  There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_18_4_JUSTIFICATION: pointer arithmetic is performed
  using '+' operator to configure the RAM address in DMA descriptors.
  This is the intended design and valid as per DMA hardware
  design. There are no side effects seen by violating this rule.*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]\
                          [TxDescIdx].TDES0 = (((uint32)\
        &(EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBufferPtr[FifoIdx][0U]))\
                                  + ((uint32)BufferIdx * TxBufLengthAligned));

  /* If timestamp is enabled, the Tx Descriptor will be overwritten by
  the HW to capture the timestamp. Hence, re-initialize Tx Descriptor if
  timestamp is enabled. */
  #if (ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
  /* Re-initialize TDES1 to zero */
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
                     [TxDescIdx].TDES1 = (uint32)0U;

  if (EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                  [BufferIdx].TimeStampEnable == ETH_17_GETHMACV2_DISABLE)
  {
    /* Enable Interrupt on transmission completion.
    Buffer length/Packet length in TDES2 and TDES3 will be updated
    during Transmit request. Previously enabled TTSE bit is disabled */
    EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
                 [TxDescIdx].TDES2 = (uint32)ETH_17_GETHMACV2_DMA_TDES2_INIT;
  }
  else
  {
    /* Enable Interrupt on transmission completion and enable time stamp */
    EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
                 [TxDescIdx].TDES2 =
          (uint32)(ETH_17_GETHMACV2_DMA_TX_DESC_IOC_ENABLE |
                   ETH_17_GETHMACV2_DMA_TX_DESC_TS_ENABLE);
  }
  #endif /* ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON */

  /*Update Tx descriptor - TDES3, with packet length.*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
                                      [TxDescIdx].TDES3 = TxLength;

/* [cover parentID={51C0F326-7A55-4ff1-9281-E25200530855}]
Checksum Insertion Enabled
[/cover] */
#if ((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON ) || \
     (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) || \
     (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) || \
     (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON ))
  /* [cover parentID={875072AD-4CEC-4081-91D9-FFDD942EF18F}]
  Enable Checksum Insertion in Tx descriptor
  (at BufIdx location of Tx descriptor)
  [/cover] */
  /* Enable Checksum Insertion in Tx descriptor.*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]
       [TxDescIdx].TDES3 |= (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_CIC_PSDO;
#endif

  /* [cover parentID={17D252D4-F6EB-41aa-9A10-280813CEBFE9}]
  Update Tx descriptor for fields, packet length, Buffer1 Length
  (as packet length),FD as set, LD as set and OWN bit as set
  [/cover] */
  /*Update Tx descriptor - TDES3, with first descriptor (FD) bit set.*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx][TxDescIdx].
                  TDES3 |= (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_FD_SET;

  /*Update Tx descriptor - TDES2.Buffer 1 Length, with Packet length to be
  transmitted*/
  /*Info: Both buffer length in TDES2 and and packet length in TDES3 should
  be same*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx][TxDescIdx].
    TDES2 = ((uint32)(EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr
     [FifoIdx][TxDescIdx].TDES2 &
    ((uint32)ETH_17_GETHMACV2_MASK_TDES2_BUF1LENGTH))) | ((uint32)TxLength);

  /*Update Tx descriptor - TDES3, with last descriptor (LD) bit set.*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx][TxDescIdx].
     TDES3 |= (uint32)ETH_17_GETHMACV2_DMA_TX_DESC_LD_SET;

  /* Assign the buffer index at the corresponding Tx descriptor index */
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxDescBufMapStPtr
                   [FifoIdx][TxDescIdx].TxDescBufMapIdx = BufferIdx;

  /* Frame Transmit Request is done*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxDescBufMapStPtr
                [FifoIdx][TxDescIdx].FrameTxInitiated = ETH_17_GETHMACV2_ENABLE;

  EthLocalCoreStatusPtr->EthBuffDescPtr->EthTxBuffTablePtr[FifoIdx][BufferIdx].
                        BuffStatus = ETH_17_GETHMACV2_BUFFER_USED_TXINITIATED;

  /* Release buffer to DMA by setting OWN bit*/
  EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx][TxDescIdx].
     TDES3 |= (uint32)(ETH_17_GETHMACV2_DMA_TX_DESC_OWN_SET);

  /* Point to next buffer in the buffer ring */
  EthLocalCoreStatusPtr->EthBuffDescPtr->
      EthRunTmTxChnlDataPtr[FifoIdx].CurrTxDmaDescIdx =
  Eth_17_GEthMacV2_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].CurrTxDmaDescIdx,
           (EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioVal].NumOfTxBuffers));

  /* [cover parentID={6AB3912D-31FF-4cbd-83C9-7C7728D67369}]
  Issue poll demand command for the corresponding Tx- DMA channel
  [/cover] */
  /*Update Tx- DMA-CH0 Descriptor tail pointer to issue poll demand command*/
   /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
   /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long to
     assign last buffer address to tail pointer register. This is the intended
     design and valid as per DMA hardware design. There are no side effects
     seen by violating this rule.*/
  EthCtrlAddPtr->DMA_CH[EthLocalCtrlCfgPtr->EthTxFifoChnlMapPtr[PrioVal]]\
            .TXDESC_TAIL_POINTER.U =\
    (uint32)(&EthLocalCoreStatusPtr->EthBuffDescPtr->EthDmaTxDescPtr[FifoIdx]\
           [EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioVal].NumOfTxBuffers]);

  /* [cover parentID={5C2CC647-5015-4aba-903D-BA737D3571E8}]
  Exit the critical section
  [/cover] */
  SchM_Exit_Eth_17_GEthMacV2_TxDescData();

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
  /* [cover parentID={346C9062-A8C1-4f0a-8F00-2F7FF1EA5AD2}]
  Tx finished indication to Switch
  [/cover] */
  RetVal = EthSwt_EthTxFinishedIndication(CtrlIdx, BufIdx);
#endif
  }

  return RetVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F7543953-FF6D-4527-9349-8695284C9047}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lResetTxRxStatus(const     **
**                Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Function to Reset all Tx and Rx status                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lResetTxRxStatus(
              const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  /* Reset interrupt status and mask the interrupt which are
  enabled in default.*/
  Eth_17_GEthMacV2_lDisableGethInterrupt(EthCtrlCfgPtr);

  /* Keep Tx DMA Descriptors in Init state, hence buffers are released.*/
  Eth_17_GEthMacV2_lDmaTxDescriptorInit(EthCtrlCfgPtr);

  /* Keep Rx DMA Descriptors in Init state, hence buffers are released.*/
  Eth_17_GEthMacV2_lDmaRxDescriptorInit(EthCtrlCfgPtr);
}


#if ((ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON) || \
     (ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={12056F04-4F8C-4a3e-9C41-2B13BBEA14AA}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lCheckForICMPV4Frame(      **
**                                uint8 * const BufferAddrPtr,                **
**                                const Eth_FrameType FrameType)              **
**                                                                            **
** Description      : This function checks for ICMP V4 frame type, and        **
**                    replaces the ICMP checksum field of the payload to      **
**                    0x00.Since for ICMP-over-IPv4 packets ETHMAC requires   **
**                    the Checksum field in the ICMP packet to be always      **
**                    16'h0000.If it is not equal to 16'h0000 ,               **
**                    an incorrect checksum may be inserted into the packet.  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : FrameType- Ethernet frame type                          **
**                                                                            **
** Parameters (inout) : BufferAddrPtr - Pointer to the address of the         **
**                                      buffer resource                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lCheckForICMPV4Frame(uint8 * const BufferAddrPtr,
                                            const Eth_FrameType FrameType)
{
  if(FrameType == ETH_17_GETHMACV2_IPV4_FRAMETYPE)
  {
    if(BufferAddrPtr[ETH_17_GETHMACV2_FRAME_IPV4TYPE_POS] ==
                  ETH_17_GETHMACV2_IPV4_ICMP_PROTOCOL)
    {
      BufferAddrPtr[ETH_17_GETHMACV2_FRAME_ICMP_CRC_POS] = 0U;

      BufferAddrPtr[ETH_17_GETHMACV2_FRAME_ICMP_CRC_POS + 1U] = 0U;
    }
  }
}
#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F21CECBB-E2BF-4a81-838A-4147F4C3CC1B}]  **
**                                                                            **
** Syntax           : static void                                             **
**                       Eth_17_GEthMacV2_lUpdateEthStatisticsCounterValues   **
**                                                                 ( void )   **
**                                                                            **
** Description      : Updates statistics counter values                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lUpdateEthStatisticsCounterValues(void)
{
  const Ifx_GETH *EthCtrlAddPtr;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint32 CoreId;
  uint8 ControllerIdx;
  uint8 EthOpMode;

  CoreId = Mcal_GetCpuIndex();

  EthLocalCoreCfgPtr = Eth_17_GEthMacV2_ConfigPtr->EthCoreAdd[CoreId];
  EthLocalCtrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCtrlPtr;
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_CtrlStatusPtr[CoreId];

  /* [cover parentID={DE634AEB-7D27-4044-9643-6DE909CDD5CB}]
  Loop till Controller index is less than available controllers
  [/cover] */
  for(ControllerIdx = 0; ControllerIdx < EthLocalCoreCfgPtr->EthMaxControllers;
                                                               ControllerIdx++)
  {
    /* Get base address of the indexed controller */
    EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthLocalCtrlCfgPtr->
                                                          EthCtrlIdx];

    EthOpMode = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties) >>
                    ETH_17_GETHMACV2_OPMODE_POS) & ETH_17_GETHMACV2_OPMODE_MSK;

    /* [cover parentID={57E16FD9-75F2-4990-9A34-81BBA8CDABAE}]
    CRC error is greater than zero
    [/cover] */
    /*Check if number of packets received with CRC error is greater than zero*/
    if((uint32)EthCtrlAddPtr->RX_CRC_ERROR_PACKETS.B.RXCRCERR > 0U)
    {
      /* Update CRC error Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.
        Count = (uint32)EthCtrlAddPtr->RX_CRC_ERROR_PACKETS.B.RXCRCERR -
        EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.
        DemReportedCount;
    }

    /* [cover parentID={4D1E6867-A2BB-4a5d-A588-30E5EE3B6B74}]
    Undersize packets greater than zero
    [/cover] */
    /*Check if number of packets received with length less than 64 bytes,without
    any errors, is greater than zero*/
    if((uint32)EthCtrlAddPtr->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG > 0U)
    {
      /* Update undersize good packets Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.
        Count = (uint32)EthCtrlAddPtr->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG -
        EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.
        DemReportedCount;
    }

    /* [cover parentID={722DDAE2-7EF9-4cff-9881-F5C2D27D447C}]
    Oversize packets greater than zero
    [/cover] */
    /*Check if number of packets received without errors, with length greater
      than the maxsize,is greater than zero*/
     if((uint32)EthCtrlAddPtr->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG > 0U)
    {
      /* Update oversize good packets Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.Count
        = (uint32)EthCtrlAddPtr->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG -
        EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.
        DemReportedCount;
    }

    /* [cover parentID={46716838-541D-44cf-B3A3-B636AD4FBC2F}]
    Alignment error is greater than zero
    [/cover] */
    /*Check if number of packets received with alignment (dribble) error is
    greater than zero
    Info: It is valid only in 10/100 mode */
    if((uint32)EthCtrlAddPtr->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR > 0U)
    {
      /*Update Alignment Error Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.
        Count = (uint32)EthCtrlAddPtr->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR -
        EthLocalCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.
        DemReportedCount;
    }

    /* Check if the number of missed received packets due to FIFO overflow
     * is greater than zero */
    /* [cover parentID={8B9A13F9-2E9D-49e9-BC9C-B42EAFA9BF5C}]
    [/cover] */
    if((uint32)EthCtrlAddPtr->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL > 0U)
    {
      /* Update Rx frames lost count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.
        Count = (uint32)EthCtrlAddPtr->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL -
        EthLocalCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.
        DemReportedCount;
    }

    /* [cover parentID={A191AAC4-057E-47d5-A266-57D86F09B6F6}]
     If OpMode is HALF DUPLEX
    [/cover] */
    if (EthOpMode == ETH_17_GETHMACV2_HALF_DUPLEX)
    {
      /*Check if number of successfully transmitted packets after a single
        collision is greater than zero
        Info: It is valid only half-duplex mode*/
      /* [cover parentID={657EA7A8-A062-4fed-946E-C27A13A9C099}]
      [/cover] */
      if((uint32)EthCtrlAddPtr->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG
                                                                          > 0U)
      {
        /*Update Single Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.
          Count = (uint32)EthCtrlAddPtr->TX_SINGLE_COLLISION_GOOD_PACKETS.B.
          TXSNGLCOLG - EthLocalCoreStatusPtr->EthStatisticsCounters.
          SingleCollisionCounter.DemReportedCount;
      }

      /*Check if number of successfully transmitted packets after multiple
        collision is greater than zero
        Info: It is valid only half-duplex mode*/
      /* [cover parentID={55FBF353-2EF1-4eb0-B00D-4BCB753B1702}]
      [/cover] */
      if((uint32)EthCtrlAddPtr->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG
                                                                          > 0U)
      {
        /*Update Multiple Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.
          Count = (uint32)EthCtrlAddPtr->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.
          TXMULTCOLG - EthLocalCoreStatusPtr->EthStatisticsCounters.
          MultipleCollisionCounter.DemReportedCount;
      }

      /* Check if number of packets aborted because of late collision error
        is greater than zero
        Info: It is valid only half-duplex mode */
      /* [cover parentID={1A3065C5-26AA-4615-A41B-3031197228D6}]
      [/cover] */
      if((uint32)EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.B.TXLATECOL > 0U)
      {
        /*Update Late Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.
          Count = (uint32)EthCtrlAddPtr->TX_LATE_COLLISION_PACKETS.B.TXLATECOL -
          EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.
          DemReportedCount;
      }
    }
    /* [cover parentID={5308C7AE-394A-4880-A29F-E21EC2D39B67}]
    Increment the pointers to check for the next controller
    [/cover] */
    EthLocalCtrlCfgPtr++;
    EthLocalCoreStatusPtr++;
  }
}

/*******************************************************************************
**                        Functions for Production Error Report               **
*******************************************************************************/

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={119B7ADD-2E3E-44e7-B3F0-8892E2139583}] **
**                                                                            **
** Syntax           : static void                                             **
**                         Eth_17_GEthMacV2_lDemReportStatisticsCounterValues **
**                                                                   (void)   **
**                                                                            **
** Description      : Raise Production Error for Statistics Counter values    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDemReportStatisticsCounterValues(void)
{
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint32 CoreId;
  uint8 ControllerIdx;
  uint8 EthOpMode;

  CoreId = Mcal_GetCpuIndex();

  EthLocalCoreCfgPtr = Eth_17_GEthMacV2_ConfigPtr->EthCoreAdd[CoreId];
  EthLocalCtrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCtrlPtr;
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_CtrlStatusPtr[CoreId];

  /* [cover parentID={414FD94E-AD6E-499e-8813-3CB35CB3EF6C}]
  Loop until Controller index is less than available controllers
  [/cover] */
  for(ControllerIdx = 0; ControllerIdx < EthLocalCoreCfgPtr->EthMaxControllers;
                                                               ControllerIdx++)
  {
    EthOpMode = (uint8)((EthLocalCtrlCfgPtr->EthCtrlProperties) >>
                    ETH_17_GETHMACV2_OPMODE_POS) & ETH_17_GETHMACV2_OPMODE_MSK;

    /* [cover parentID={28B9A82C-9260-4e1b-A9FA-A0F8F6C27D31}]
    If total Frames lost is greater than zero and Production error is enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.Count
                                                                        > 0U)
    {
      if(EthLocalCtrlCfgPtr->EthDemFramesLost !=
                                      ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={3DF4EA22-2545-4d57-9FDF-600277FD57F7}]
        Report ETH_E_RX_FRAMES_LOST
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(
             EthLocalCtrlCfgPtr->EthDemFramesLost, DEM_EVENT_STATUS_PREFAILED);

        EthLocalCoreStatusPtr->EthStatisticsCounters.RxFramesLostCounter.
          DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
          RxFramesLostCounter.DemReportedCount +
          EthLocalCoreStatusPtr->EthStatisticsCounters.
          RxFramesLostCounter.Count;
      }
    }

    /* [cover parentID={8F65A935-D793-4472-8829-BF0F2F058604}]
    If total CRC errors is greater than zero and Production error is enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.
                          CRCErrorFrameCounter.Count > 0U)
    {
      if(EthLocalCtrlCfgPtr->EthDemCRC != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={8AF31CF3-F54E-4583-BA3E-01B681DF3AF3}]
        Report ETH_E_CRC
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(EthLocalCtrlCfgPtr->EthDemCRC,
                                           DEM_EVENT_STATUS_PREFAILED);

        EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.
          DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
          CRCErrorFrameCounter.DemReportedCount +
          EthLocalCoreStatusPtr->EthStatisticsCounters.
          CRCErrorFrameCounter.Count;
      }
    }

    /* [cover parentID={D2DCC1A9-1CFC-4246-911B-617F15FF665C}]
    If total undersize counter is greater than zero and Production error is
    enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.
                         UnderSizeFrameCounter.Count > 0U)
    {
      if(EthLocalCtrlCfgPtr->EthDemUndersize !=
                                         ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={7DB9C2CA-814C-42b2-8B92-4130778AA2BB}]
        Report ETH_E_UNDERSIZEFRAME
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(
              EthLocalCtrlCfgPtr->EthDemUndersize, DEM_EVENT_STATUS_PREFAILED);

        EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.
          DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
          UnderSizeFrameCounter.DemReportedCount + EthLocalCoreStatusPtr->
          EthStatisticsCounters.UnderSizeFrameCounter.Count;
      }
    }

    /* [cover parentID={12B3843A-EC96-4179-AE09-749E01DE1D92}]
    If total oversize counter is greater than zero and Production error is
    enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.
                                            Count > 0U)
    {
      if(EthLocalCtrlCfgPtr->EthDemOversize !=
                                      ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={4ADE4E62-A981-40e9-B056-25E35DD1B3A1}]
        Report ETH_E_OVERSIZEFRAME
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(
              EthLocalCtrlCfgPtr->EthDemOversize, DEM_EVENT_STATUS_PREFAILED);

        EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.
          DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
          OverSizeFrameCounter.DemReportedCount + EthLocalCoreStatusPtr->
          EthStatisticsCounters.OverSizeFrameCounter.Count;
      }
    }

    /* [cover parentID={96E50E77-39BB-4ccf-BF9D-756BBE793CCD}]
    If total alignment errors is greater than zero and Production error is
    enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.
                   AlignmentErrorFrameCounter.Count > 0U)
    {
      if(EthLocalCtrlCfgPtr->EthDemAlignment !=
                                        ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={96AF6844-C810-45a5-9040-0BDC4846A2B7}]
        Report ETH_E_ALIGNMENT
        [/cover] */
        (void)Mcal_Wrapper_Dem_SetEventStatus(
              EthLocalCtrlCfgPtr->EthDemAlignment, DEM_EVENT_STATUS_PREFAILED);

        EthLocalCoreStatusPtr->EthStatisticsCounters.
          AlignmentErrorFrameCounter.DemReportedCount = EthLocalCoreStatusPtr->
          EthStatisticsCounters.AlignmentErrorFrameCounter.DemReportedCount +
          EthLocalCoreStatusPtr->EthStatisticsCounters.
          AlignmentErrorFrameCounter.Count;
      }
    }

    /* [cover parentID={76262A11-7765-4c1f-B463-847B61823AC6}]
    If Mode is HALF DUPLEX
    [/cover] */
    if(EthOpMode == ETH_17_GETHMACV2_HALF_DUPLEX)
    {
      /* [cover parentID={A0DF3BEE-32EA-4c4e-BB2A-C6A8701F2686}]
      [/cover] */
      Eth_17_GEthMacV2_lDemReportHalfDuplStatCountValues(EthLocalCtrlCfgPtr,
                                                        EthLocalCoreStatusPtr);
    }

    EthLocalCtrlCfgPtr++;
    EthLocalCoreStatusPtr++;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={B6891B44-18C5-4fed-B054-5730A76B88F4}] **
**                                                                            **
** Syntax           : static void                                             **
**                      Eth_17_GEthMacV2_lDemReportHalfDuplStatCountValues    **
**                    (const Eth_17_GEthMacV2_CoreCtrlConfigType              **
**                     *const EthCtrlCfgPtr, Eth_17_GEthMacV2_CtrlStatusType  **
**                     *const EthLocalCoreStatusPtr)                          **
**                                                                            **
** Description      : Raise Production error for Half Duplex Statistics       **
**                    Counter values                                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr -Pointer to controller configuration data **
**                                                                            **
** Parameters (inout) : EthLocalCoreStatusPtr - Pointer to controller status  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDemReportHalfDuplStatCountValues(const
                 Eth_17_GEthMacV2_CoreCtrlConfigType *const EthCtrlCfgPtr,
                 Eth_17_GEthMacV2_CtrlStatusType *const EthLocalCoreStatusPtr)
{
  /* [cover parentID={295AA83B-D1A7-408a-A4E3-4ABF1EDB2BEB}]
  Is Single collision count > 0 and Production error is enabled ?
  [/cover] */
  if(EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.
                                                              Count > 0U)
  {
    if(EthCtrlCfgPtr->EthDemSingleCollision !=
                                      ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
    {
      /* [cover parentID={1117A9F8-F984-459b-9129-FFA8CE783230}]
      Report ETH_E_SINGLECOLLISION
      [/cover] */
      (void)Mcal_Wrapper_Dem_SetEventStatus(
            EthCtrlCfgPtr->EthDemSingleCollision, DEM_EVENT_STATUS_PREFAILED);

      EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.
      DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
      SingleCollisionCounter.DemReportedCount +
      EthLocalCoreStatusPtr->EthStatisticsCounters.
      SingleCollisionCounter.Count;
    }
  }

  /* [cover parentID={74E27369-094F-481d-BBE8-294FA7B939DA}]
  Is Multiple collision count > 0 and Production error is enabled ?
  [/cover] */
  if(EthLocalCoreStatusPtr->EthStatisticsCounters.
                     MultipleCollisionCounter.Count > 0U)
  {
    if(EthCtrlCfgPtr->EthDemMultipleCollision !=
                                       ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
    {
      /* [cover parentID={7CCD5CE9-2A46-4867-A98E-92009AF5C2E7}]
      Report ETH_E_MULTIPLECOLLISION
      [/cover] */
      (void)Mcal_Wrapper_Dem_SetEventStatus(
          EthCtrlCfgPtr->EthDemMultipleCollision, DEM_EVENT_STATUS_PREFAILED);

      EthLocalCoreStatusPtr->EthStatisticsCounters.
        MultipleCollisionCounter.DemReportedCount =
        EthLocalCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.
        DemReportedCount + EthLocalCoreStatusPtr->EthStatisticsCounters.
        MultipleCollisionCounter.Count;
    }
  }

  /* [cover parentID={3269B9DE-C87C-4315-A583-20F4DFDFF47D}]
  Is late collision count > 0 and Production error is enabled?
  [/cover] */
  if(EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.
                                                            Count > 0U)
  {
    if(EthCtrlCfgPtr->EthDemLateCollision !=
                                    ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
    {
      /* [cover parentID={5A466F91-35CF-4bc2-8189-DC8FF6AE8BA7}]
      Report ETH_E_LATECOLLISION
      [/cover] */
      (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemLateCollision,
                                            DEM_EVENT_STATUS_PREFAILED);

      EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.
        LateCollisionCounter.DemReportedCount + EthLocalCoreStatusPtr->
        EthStatisticsCounters.LateCollisionCounter.Count;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={028200D0-B5DF-4141-93C8-2367C9B0F7B6}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDemReportAllErrorPass(    **
**          const Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)   **
**                                                                            **
** Description      : Report all Production errors as Pass to Mcal_Wrapper    **
**                    module                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to ethernet Controller           **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDemReportAllErrorPass(const
                    Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  /* [cover parentID={7686FDCF-7A21-4a5d-A519-A0C3665D5C8A}]
  If DEM id for corresponding Production error is enabled
  [/cover] */
  /* [cover parentID={59826ECD-D6BA-46a6-B2F5-111133E62C5A}]
  Report Production error as DEM_EVENT_STATUS_PREPASSED (except for
  ETH_E_ACCESS)
  [/cover] */
  if(EthCtrlCfgPtr->EthDemFramesLost != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemFramesLost,
                                             DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemCRC != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemCRC,
                                            DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemUndersize != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemUndersize,
                                            DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemOversize != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemOversize,
                                           DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemAlignment != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemAlignment,
                                         DEM_EVENT_STATUS_PREPASSED);
  }
  /* [cover parentID={D3150895-1007-4aae-AD2E-D2452D567F24}]
  If DEM id for corresponding Production error of Half Duplex is enabled
  [/cover] */
  /* [cover parentID={D8B2F089-A046-4ae9-992A-1C00C68664EA}]
  Report corresponding Production error as DEM_EVENT_STATUS_PREPASSED
  [/cover] */
  if(EthCtrlCfgPtr->EthDemSingleCollision != \
                                         ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(
          EthCtrlCfgPtr->EthDemSingleCollision, DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemMultipleCollision != \
                                         ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(
          EthCtrlCfgPtr->EthDemMultipleCollision, DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCtrlCfgPtr->EthDemLateCollision != \
                                         ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
  {
    (void)Mcal_Wrapper_Dem_SetEventStatus(EthCtrlCfgPtr->EthDemLateCollision,
          DEM_EVENT_STATUS_PREPASSED);
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7036B58F-7C72-47dc-B97C-11F360E4FAF1}]  **
**                                                                            **
** Syntax           : static void Eth_17_GEthMacV2_lDemtimeout                **
**                    (const uint32 Timeout, ,const Dem_EventIdType           **
**                                                          EthDemAccess)     **
**                                                                            **
** Description      : Report Hardware Access Production error if timeout      **
**                    happened                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : Timeout - Timeout occurred status                       **
**                    EthDemAccess - Production Error Enable/Disable Status   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lDemtimeout(const boolean Timeout,
                                      const Dem_EventIdType EthDemAccess)
{
  /* [cover parentID={FF37D69C-100B-4b4d-9768-8397BE6AFFA4}]
  Check if timeout occurred
  [/cover] */
  if(Timeout == TRUE)
  {
    /* If Production error is enabled */
    if(EthDemAccess != ETH_17_GETHMACV2_DISABLE_DEM_REPORT)
    {
      /* [cover parentID={AF52A3C1-4A3B-4023-8B29-AE70A1F293FC}]
      Report error DEM_E_ACCESS
      [/cover] */
      (void)Mcal_Wrapper_Dem_SetEventStatus(EthDemAccess,
            DEM_EVENT_STATUS_PREFAILED);
    }
  }
}

/*******************************************************************************
**                        Functions for DET checks                            **
*******************************************************************************/

#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7F6BA151-2C1C-4c45-A489-49C15C8820B9}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkPointerInvalid     **
**                             (const void * const Ptr,const uint8 ServiceId) **
**                                                                            **
** Description      : DET check for ETH_17_GETHMACV2_E_PARAM_POINTER          **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Ptr- Pointer to be checked                              **
**                    ServiceId- ServiceId of API                             **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR     - Valid pointer       **
**                    ETH_17_GETHMACV2_E_PARAM_POINTER  - NULL pointer        **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkPointerInvalid(const void* const Ptr,
                                                    const uint8 ServiceId)
{
  uint8 DevError;
  /* [cover parentID={E4B09346-8C6B-426a-94AA-C488E4D213CD}][/cover] */
  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* [cover parentID={1CCA81E8-C7B5-46c3-913A-3D169416C946}]
  Input Parameter 'Ptr' is Null
  [/cover] */
  if(Ptr == NULL_PTR)
  {
    DevError = ETH_17_GETHMACV2_E_PARAM_POINTER;

    /* [cover parentID={8089A224-E086-473f-B7BF-80B45AD5CF61}]
    Report DET as Invalid Pointer with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId, DevError);
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={ECC06C73-D505-4217-AE28-80F2A4BE2550}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid     **
**                                     (const uint8 CtrlIdx,                  **
**                                      const uint8 ServiceId)                **
**                                                                            **
** Description      : DET check for ETH_17_GETHMACV2_E_INV_CTRL_IDX           **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : CtrlIdx- Controller Index to be checked                 **
**                    ServiceId- Service Id of API                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR  - Valid ctrl index       **
**                    ETH_17_GETHMACV2_E_INV_CTRL_IDX - Invalid ctrl index    **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(const uint8 CtrlIdx,
                                                    const uint8 ServiceId)
{
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint32 CoreId;
  uint8 DevError;
  uint8 CoreCtrlIdx;

  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* [cover parentID={C7427779-7393-422d-98B3-221D9808C745}]
  If Controller Index is greater or equal to max controllers
  [/cover] */
  if (CtrlIdx >= ETH_17_GETHMACV2_MAX_CONTROLLERS)
  {
    /* [cover parentID={6725C55B-8B11-4aaf-9E40-B355F17B30AC}]
    Report DET as Invalid Controller Index with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                          ETH_17_GETHMACV2_E_INV_CTRL_IDX);

    DevError = ETH_17_GETHMACV2_E_INV_CTRL_IDX;
  }

  /* [cover parentID={3A9CA646-1959-447b-B7CE-F085EC600593}]
  If no error (Ctrl Idx is Valid)
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    CoreId = Mcal_GetCpuIndex();

    EthLocalCoreCfgPtr = Eth_17_GEthMacV2_ConfigPtr->EthCoreAdd[CoreId];

    CoreCtrlIdx = Eth_17_GEthMacV2_ConfigPtr->EthNodeIdxMapPtr[CtrlIdx];

    /* [cover parentID={ACB46966-95C8-4030-8405-DCBE354BB3D5}]
    If the controller index is greater than max allocated controllers to
    current core
    [/cover] */
    if (CoreCtrlIdx >= EthLocalCoreCfgPtr->EthMaxControllers)
    {
      /* [cover parentID={0DA56957-565B-4d9d-A08E-8C7D2C4638D9}]
      Report DET as Controller Index is not allocated to current core
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                            ETH_17_GETHMACV2_E_INV_CTRL_IDX);

      DevError = ETH_17_GETHMACV2_E_INV_CTRL_IDX;
    }
    /* [cover parentID={C72E2A80-F725-4119-B92A-551B23B9D603}]
    If NO DET
    [/cover] */
    if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
    {
      EthLocalCtrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCtrlPtr;
      EthLocalCtrlCfgPtr = &(EthLocalCtrlCfgPtr[CoreCtrlIdx]);

      /* [cover parentID={DFD7CE5B-74EF-420a-AFE9-42A3BB08DE4A}]
      If the controller index is valid but not allocated to the current core
      [/cover] */
      if(EthLocalCtrlCfgPtr->EthCtrlIdx != CtrlIdx)
      {
        /* [cover parentID={8640A59E-531F-4986-A08F-4B3631B89205}]
        Report DET as Controller Index is not allocated to current core
        [/cover] */
        (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                              ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                              ETH_17_GETHMACV2_E_INV_CTRL_IDX);

        DevError = ETH_17_GETHMACV2_E_INV_CTRL_IDX;
      }
    }
  }

  return DevError ;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={656C1B91-9FF5-448b-9F4B-B15331454105}]  **
**                                                                            **
** Syntax : static uint8 Eth_17_GEthMacV2_lInitDetCheck                       **
**                            (const Eth_17_GEthMacV2_ConfigType * const      **
**                            DetConfigPtr, const uint32 CoreId)              **
** [/cover]                                                                   **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   DetConfigPtr - Pointer to configuration set             **
**                    CoreId : Core Number                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      ErrorFlag (uint32)                                      **
**                                                                            **
** Description :      Local function :Service for DET check in Ethernet Init  **
**                                    function                                **
**                                                                            **
******************************************************************************/
static uint8 Eth_17_GEthMacV2_lInitDetCheck(
                     const Eth_17_GEthMacV2_ConfigType * const DetConfigPtr,
                     const uint32 CoreId)
{
  #if (ETH_17_GETHMACV2_MULTICORE_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  #endif
  uint8 DevError;

  /* [cover parentID={A5560539-0AEF-4b1f-801F-F2E52F44CBD7}]
  No DET reported
  [/cover] */
  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* [cover parentID={01C3C2CC-A054-449f-87EB-082BE289954F}]
  If Config Ptr is NULL
  [/cover] */
  if(DetConfigPtr == NULL_PTR)
  {
    DevError = ETH_17_GETHMACV2_E_INIT_FAILED;
    /* [cover parentID={29EA6389-14B0-4dad-9C26-EA967AF3BDFC}]
    Report ETH_17_GETHMACV2_E_INIT_FAILED
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID,
                          ETH_17_GETHMACV2_SID_INIT, DevError);
  }
  #if (ETH_17_GETHMACV2_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={A6C1170C-E55D-45de-B44C-03211004EE8B}]
  If no DET and current core configured with controller
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    EthLocalCoreCfgPtr = DetConfigPtr->EthCoreAdd[CoreId];

    if(EthLocalCoreCfgPtr == NULL_PTR)
    {
      /* Report DET - Init failed as No controller is configured to
          current core */
      DevError = ETH_17_GETHMACV2_E_CORE_NOT_CONFIGURED;
      /* [cover parentID={EC9B2732-1ABA-42eb-A486-72219E7E27A8}]
      Report ETH_17_GETHMACV2_E_CORE_NOT_CONFIGURED
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID,
                            ETH_17_GETHMACV2_SID_INIT, DevError);
    }
  }
  #else
    UNUSED_PARAMETER(CoreId);
  #endif

  return DevError;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={AB26B62F-BAD7-43a8-B7E4-9EFEC5495CCB}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkNoInit             **
**                               (const uint8 CtrlIdx, const uint8 ServiceId) **
**                                                                            **
** Description      : DET check for ETH_17_GETHMACV2_E_UNINIT                 **
**                    This local API is required only if DET is enabled       **
**                    This local API is verifies if the controller init       **
**                      is successful                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx- Controller Index                               **
**                    ServiceId- ServiceId of API                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR - Init is sucsessful      **
**                    ETH_17_GETHMACV2_E_UNINIT  - Init is failed             **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkNoInit(const uint8 CtrlIdx,
                                            const uint8 ServiceId)
{
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint8 DevError;

  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  /* [cover parentID={970B6388-544D-4252-AE06-4587356FA480}]
  If controller initialization was successful
  [/cover] */
  /* Check if Eth_17_GEthMacV2_SetControllerMode API is called and controller
  initialization was successful. */
  if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CtrlConfigStatus ==
                                      ETH_17_GETHMACV2_CTRL_NOT_INITIALIZED)
  {
    DevError = ETH_17_GETHMACV2_E_UNINIT;

    /* [cover parentID={F03AD3BC-0F21-4b89-AC2C-CCD33F217793}]
    Report DET as Uninitialized with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                          ETH_17_GETHMACV2_E_UNINIT);
  }

  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={40633E95-C691-46c3-9927-7DE736E782FB}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkNoInitStage1       **
**                    (const uint8 ServiceId)                                 **
**                                                                            **
** Description      : DET check for Eth_Init is successfully executed         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : ServiceId - Service ID of API                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR  - Init Stage1 is success **
**                    ETH_17_GETHMACV2_E_UNINIT - No Init Stage1 Error        **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkNoInitStage1(const uint8 ServiceId)
{
  uint32 CoreId;
  uint8 DevError;

  CoreId = Mcal_GetCpuIndex();
  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* [cover parentID={E66707CD-B4DB-4e11-8C66-B59F2B95B933}]
  Check if the controller is configured to the core
  [/cover] */
  if(Eth_17_GEthMacV2_CoreInitStatusPtr[CoreId]!= NULL_PTR)
  {
    /* [cover parentID={31E93064-396C-4d11-9472-DC16AA579CE9}]
    Eth_Init is not successfully executed before
    [/cover] */
    /* Check if Eth_Init is successfully executed before */
    if(*(Eth_17_GEthMacV2_CoreInitStatusPtr[CoreId]) !=
                                      (uint32)ETH_17_GETHMACV2_CORE_INIT)
    {
      DevError = ETH_17_GETHMACV2_E_UNINIT;

      /* [cover parentID={3ED693A0-D03A-4a7f-9279-9A884F7FDA62}]
      Report DET as Uninitialized with Service ID
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                            ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                            ETH_17_GETHMACV2_E_UNINIT);
    }
  }
  else
  {
    DevError = ETH_17_GETHMACV2_E_UNINIT;

    /* [cover parentID={DE19604E-55F2-41f9-88FC-2138FA732972}]
    Report DET as Uninitialized with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                          ETH_17_GETHMACV2_E_UNINIT);
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={44843BE9-2FF1-43b3-801D-589AFE6A07AA}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkModeInvalid        **
**                                             (const Eth_ModeType CtrlMode)  **
**                                                                            **
** Description      : DET check for the parameter CtrlMode is valid           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlMode - Controller Mode                              **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR - CtrlMode param is valid **
**                    ETH_17_GETHMACV2_E_INV_PARAM -CtrlMode param is invalid **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkModeInvalid(const Eth_ModeType CtrlMode)
{
  uint8 DevError;

  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* [cover parentID={C2B68B41-7F45-472b-BFE8-A84B51CDA08D}]
  Parameter CtrlMode is valid.
  That is CtrlMode != ETH_MODE_ACTIVE  &&  CtrlMode != ETH_MODE_DOWN
  [/cover] */
  /* Check whether parameter CtrlMode is valid */
  if((CtrlMode != ETH_MODE_ACTIVE) && (CtrlMode != ETH_MODE_DOWN))
  {
    DevError = ETH_17_GETHMACV2_E_INV_PARAM;

    /* [cover parentID={913FD193-3DCB-4513-9BB3-3BDDADAFD8B2}]
    Report DET as Invalid Parameter with Service ID of SetControllerMode API
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID,
                          ETH_17_GETHMACV2_SID_SETCONTROLLERMODE,
                          ETH_17_GETHMACV2_E_INV_PARAM);
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={326011E7-B632-4ff3-934A-376CB60590E2}]  **
**                                                                            **
** Syntax           : uint8 Eth_17_GEthMacV2_lDetChkProvideTxBuffer (         **
**                      const uint8 CtrlIdx, const uint8 Priority,            **
**                      const Eth_BufIdxType* const BufIdxPtr,                **
**                      uint8** const BufPtr, const uint16* const LenBytePtr) **
**                                                                            **
** Description      : Development error checks to be done for                 **
**                          Eth_17_GEthMacV2_ProvideTxBuffer API              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller Mode                  **
**                    Priority - Priority for transmit buffer FIFO selection  **
**                    BufIdxPtr - Pointer to the buffer index resource        **
**                    BufPtr - Pointer to the granted buffer                  **
**                    LenBytePtr - Pointer to the desired length              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint8 - Value of the development error                  **
**                     Zero value indicates - Parameters are valid, No Error  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Eth_17_GEthMacV2_lDetChkProvideTxBuffer(
                                        const uint8 CtrlIdx,
                                        const uint8 Priority,
                                        const Eth_BufIdxType* const BufIdxPtr,
                                        uint8* const * const BufPtr,
                                        const uint16* const LenBytePtr)
{
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint8 DevError;

  /* Check if Eth_17_GEthMacV2_Init is successful */
  /* [cover parentID={A7ADA3B2-7952-4d99-8CED-A16B3081CBFF}]
  Check if driver is initialized
  [/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1(
                                 ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);

  /* [cover parentID={FA4B421D-307F-4cfa-BC87-729BABD810BB}]
  If driver is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={89939D4D-3DCD-480e-84EE-7930330C0ED6}]
    Validate CtrlIdx
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(CtrlIdx,
                                ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);
  }

  /* [cover parentID={6321AED1-B654-47e7-96E0-52F203901A5A}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
       Eth_17_GEthMacV2_SetControllerMode */
    /* [cover parentID={D9205202-6A5C-4dc0-8139-81D5846FBB91}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkNoInit(CtrlIdx,
                              ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={C08C4E35-2EF9-4e1f-A662-2E1D3552E26B}]
  Controller Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={F936F36B-7996-42b8-81C0-BA776810843B}]
    Validate BufIdxPtr (Output parameter)
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(BufIdxPtr,
                               ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={41723148-21AA-46b5-BFC9-5BE0515368D7}]
  Valid BufIdxPtr
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={5429B4C7-78B4-4979-B3CD-887CCCB30F19}]
    Validate BufPtr (Output parameter)
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(BufPtr,
                               ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={60918362-2657-453f-AC75-1F04B5658354}]
  Valid BufPtr
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={932C06DD-B9DB-4fb7-B81F-05A303B69984}]
    Validate LenBytePtr(In/Out parameter)
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkPointerInvalid(LenBytePtr,
                                ETH_17_GETHMACV2_SID_PROVIDETXBUFFER);
  }

  /* [cover parentID={91DCFAC2-FAC1-4f16-BBBC-051F49F78E4E}]
  Valid LenBytePtr
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Validate the priority parameter */
    /* [cover parentID={68E2DD87-BE8F-438a-8456-F428938EB1B8}]
    Check if the priority parameter is greater than max value
    [/cover] */
    if (Priority > (uint8)ETH_17_GETHMACV2_MAX_PRIORITY)
    {
      /* [cover parentID={9D8FD1E8-7838-49f0-979D-8B4A6C690737}]
      Report development error - ETH_E_INV_PARAM
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
          ETH_17_GETHMACV2_INSTANCE_ID,
          ETH_17_GETHMACV2_SID_PROVIDETXBUFFER, ETH_17_GETHMACV2_E_INV_PARAM);

      DevError = ETH_17_GETHMACV2_E_INV_PARAM;
    }
    else
    {
      /* Get controller configuration data */
      EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

      /* [cover parentID={18C4C6B7-C503-4a1c-A67B-E84B8C6F293A}]
      [/cover] */
      /* if the priority does not match the configured priorities */
      if (EthLocalCtrlCfgPtr->EthTxPrioFifoMapPtr[Priority] ==
                                  (uint8)ETH_17_GETHMACV2_NONCFG_PRIORITY)
      {
        /* [cover parentID={9D8FD1E8-7838-49f0-979D-8B4A6C690737}]
        Report development error - ETH_E_INV_PARAM
        [/cover] */
        (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
            ETH_17_GETHMACV2_INSTANCE_ID,
            ETH_17_GETHMACV2_SID_PROVIDETXBUFFER, ETH_17_GETHMACV2_E_INV_PARAM);

        DevError = ETH_17_GETHMACV2_E_INV_PARAM;
      }
    }
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={0E1D1587-3F80-4425-82F1-895FCB8D197E}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetChkSetCtrlMode(       **
**                                    const uint8 CtrlIdx,                    **
**                                    const Eth_ModeType CtrlMode)            **
**                                                                            **
** Description      : Development error checks to be done for                 **
**                          Eth_17_GEthMacV2_SetControllerMode API            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                    CtrlMode  - Controller Mode DOWN/ACTIVE                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint8 - Value of the development error                  **
**                     Zero value indicates - Parameters are valid, No Error  **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetChkSetCtrlMode(const uint8 CtrlIdx,
                                                 const Eth_ModeType CtrlMode)
{
  uint8 DevError;

  /* Check if Eth_Init is successful */
  /* [cover parentID={6FCAB36D-2A43-4558-84B5-5AB441731B27}][/cover] */
  DevError = Eth_17_GEthMacV2_lDetChkNoInitStage1
                                  (ETH_17_GETHMACV2_SID_SETCONTROLLERMODE);

  /* [cover parentID={56F74F5D-D3DD-4ed6-A568-32C147CF0946}]
  Eth_Init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* [cover parentID={D21ED4ED-5BE2-4575-BAFD-2F940F1E4DD5}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_GEthMacV2_lDetChkCtrlIdxInvalid(
                              CtrlIdx, ETH_17_GETHMACV2_SID_SETCONTROLLERMODE);
  }
  /* [cover parentID={0EE64A27-0549-43f3-9355-40A863D273AB}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMACV2_E_DET_NO_ERR)
  {
    /* Check the parameter CtrlMode is valid  */
    /* [cover parentID={6A866ABC-064A-4131-99A2-915C3DB6E0BF}]
     Validate CtrlMode
     [/cover] */
    DevError =  Eth_17_GEthMacV2_lDetChkModeInvalid(CtrlMode);
  }

  return DevError;
}

#endif /*ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON*/

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={8D9BE2CE-CCC0-4f9d-8D11-CDD33DCF1BDC}]  **
**                                                                            **
** Syntax           : static uint8 Eth_17_GEthMacV2_lDetCheckMode             **
**                    (const uint8 ServiceId, const                           **
**                    Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr)**
**                                                                            **
** Description      : DET check for ETH_17_GETHMACV2_E_INV_MODE               **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : ServiceId - ServiceId of API                            **
**                    EthCoreStatusPtr - Pointer to Ethernet controller status**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMACV2_E_DET_NO_ERR   - Valid Controller mode **
**                    ETH_17_GETHMACV2_E_INV_MODE   - Invalid Controller mode **
**                                                                            **
*******************************************************************************/
static uint8 Eth_17_GEthMacV2_lDetCheckMode(const uint8 ServiceId,
              const Eth_17_GEthMacV2_CtrlStatusType* const EthCoreStatusPtr)
{
  Eth_ModeType CtrlMode;
  uint8 DevError;

  DevError = ETH_17_GETHMACV2_E_DET_NO_ERR;

  /* Read the current controller mode */
  CtrlMode = EthCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode;

  /* [cover parentID={AA894DB2-54D7-4082-8BD3-CC68756F2D59}]
  Is the current controller mode not in ACTIVE state
  [/cover] */
  if(CtrlMode != ETH_MODE_ACTIVE)
  {
    DevError = ETH_17_GETHMACV2_E_INV_MODE;

    /* [cover parentID={3B0B2C39-A151-46d7-A3CD-828969F8A3AC}]
    DET is Enabled
    [/cover] */
#if(ETH_17_GETHMACV2_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={9FB23D3E-F5A8-420f-8374-1591157A7716}]
    Report DET as Invalid Mode with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMACV2_MODULE_ID,
                          ETH_17_GETHMACV2_INSTANCE_ID, ServiceId,
                          ETH_17_GETHMACV2_E_INV_MODE);
#else
    UNUSED_PARAMETER(ServiceId);
#endif
  }

  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={97AAE249-BAC3-4f84-B466-510220270514}]  **
**                                                                            **
** Syntax          :  static Eth_17_GEthMacV2_CoreCtrlConfigType*             **
**                   Eth_17_GEthMacV2_lGetCtrlConfigPtr(const uint8 CtrlIdx)  **
**                                                                            **
** Description :      Get pointer to controller config data                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in):   CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      CtrlCfgPtr- Pointer to controller configuration         **
**                                                                            **
*******************************************************************************/
static Eth_17_GEthMacV2_CoreCtrlConfigType* Eth_17_GEthMacV2_lGetCtrlConfigPtr
                                                         (const uint8 CtrlIdx)
{
  uint32 CoreId;
  const Eth_17_GEthMacV2_CoreConfigType *EthLocalCoreCfgPtr;
  Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  uint8 CoreCtrlIdx;

  /*Get the current core Id*/
  CoreId = Mcal_GetCpuIndex();

  EthLocalCoreCfgPtr = Eth_17_GEthMacV2_ConfigPtr->EthCoreAdd[CoreId];
  CoreCtrlIdx = Eth_17_GEthMacV2_ConfigPtr->EthNodeIdxMapPtr[CtrlIdx];

  /* Obtain the pointer to controller configuration for the current core*/
  EthLocalCtrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCtrlPtr;
  EthLocalCtrlCfgPtr = &(EthLocalCtrlCfgPtr[CoreCtrlIdx]);

  return EthLocalCtrlCfgPtr;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9CF2CA34-7844-4cd9-A34F-18D9ED43C752}]  **
**                                                                            **
** Syntax          : Eth_17_GEthMacV2_CtrlStatusType*                         **
**                    Eth_17_GEthMacV2_lGetCtrlStatusPtr(                     **
**                                                    const uint8 CtrlIdx)    **
**                                                                            **
** Description :      Get pointer to controller status                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in):   CtrlIdx - Controller Id                                 **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      Pointer to controller Status                            **
**                                                                            **
*******************************************************************************/
static Eth_17_GEthMacV2_CtrlStatusType* Eth_17_GEthMacV2_lGetCtrlStatusPtr
                                                         (const uint8 CtrlIdx)
{
  uint32 CoreId;
  Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  uint8 CoreCtrlIdx;

  /* Get the current core Id */
  CoreId = Mcal_GetCpuIndex();

  CoreCtrlIdx = Eth_17_GEthMacV2_ConfigPtr->EthNodeIdxMapPtr[CtrlIdx];

  /* Obtain the pointer to controller status for the current core */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_CtrlStatusPtr[CoreId];
  EthLocalCoreStatusPtr = &(EthLocalCoreStatusPtr[CoreCtrlIdx]);

  return EthLocalCoreStatusPtr;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9D3D4251-28E0-4c82-9146-33E2B5C22B83}]  **
**                                                                            **
** Syntax          : void Eth_17_GEthMacV2_lCfgTxQueue (const                 **
**                          Eth_17_GEthMacV2_CoreCtrlConfigType* const        **
**                                                       EthCtrlCfgPtr)       **
**                                                                            **
** Description     : Configures the MTL transmit queues                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  None                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                                   configuration.                           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lCfgTxQueue(const
                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint8 FifoMapIdx;
  uint8 TxChnlsUsd;
  uint8 ChnlCnt;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Get the number of Tx channels */
  TxChnlsUsd = EthCtrlCfgPtr->EthNumTxChnls;

  /* [cover parentID={3EE37C4B-09F7-4f48-8642-5810438276F7}]
  If any FIFO is configured for transmission
  [/cover] */
  if (TxChnlsUsd > 0U)
  {
    /* Configure transmit queues - Operation Mode, Weights, parameters related
        to CBS */
    FifoMapIdx = EthCtrlCfgPtr->EthTxChnlFifoMapPtr[0];

    /* Configure MTL Operation mode for TX Queue-0 */
    /* [cover parentID={22981F96-075C-449d-8883-AC93DAB36EE9}]
    Configure MTL Operation mode for Tx Queue 0 - Enable Tx in store and
    forward, set the queue size and enable the queue for Tx
    [/cover] */
    EthCtrlAddPtr->MTL_TXQ0.OPERATION_MODE.U =
      ((uint32)ETH_17_GETHMACV2_MTL_TXQ0_OPERTN_MODE_INIT |
      ((uint32)EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoMapIdx].TxQueueSize << 16U));

    /* Configure the weights */
    EthCtrlAddPtr->MTL_TXQ0.QUANTUM_WEIGHT.U = EthCtrlCfgPtr->
              EthTxFifoCfgPtr[FifoMapIdx].IdleSlopeCredit;

    /* [cover parentID={5C8E9F0F-7989-4798-8018-1AD98E81D47C}]
    Loop until the number of queues required for transmission
    [/cover] */
    for(ChnlCnt = 1U; ChnlCnt < TxChnlsUsd; ChnlCnt++)
    {
      FifoMapIdx = EthCtrlCfgPtr->EthTxChnlFifoMapPtr[ChnlCnt];

      /* [cover parentID={EEDD1850-91E1-47c7-8BA8-DC883404F507}]
      Configure MTL Operation mode for selected Tx Queue - Enable Tx in store
      and forward, set the queue size and the queue mode based on the mapped
      FIFO configuration
      [/cover] */
      (&EthCtrlAddPtr->MTL_TXQ1.OPERATION_MODE)[(ChnlCnt - 1U)
          * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U =
       ((uint32)ETH_17_GETHMACV2_MTL_TSF |
       ((uint32)EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoMapIdx].TxQueueMode << 2U) |
       ((uint32)EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoMapIdx].TxQueueSize << 16U));

      /* Configure the weights */
      (&EthCtrlAddPtr->MTL_TXQ1.QUANTUM_WEIGHT)[(ChnlCnt - 1U)
          * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U = EthCtrlCfgPtr->
                EthTxFifoCfgPtr[FifoMapIdx].IdleSlopeCredit;

      /* [cover parentID={6E982EBC-2E2F-496f-A3BE-943951E5C221}]
      If the configured mode of the mapped FIFO is AV mode ?
      [/cover] */
      if (EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoMapIdx].TxQueueMode ==
                                              ETH_17_GETHMACV2_TXQ_AVBMODE)
      {
        /* [cover parentID={E124D2F3-E9E9-4846-9384-B08282CC2356}]
        Configure the send slope credit value, High credit and Low credit
        values for the Tx Queue based on the configured values for the FIFO
        [/cover] */
        (&EthCtrlAddPtr->MTL_TXQ1.ETS_CONTROL)[(ChnlCnt - 1U)
          * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U =
                    (uint32)ETH_17_GETHMACV2_ETS_AVALG_CC;

        (&EthCtrlAddPtr->MTL_TXQ1.SENDSLOPECREDIT)
          [(ChnlCnt- 1U) * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U =
              EthCtrlCfgPtr->EthTxFifoCfgPtr[FifoMapIdx].SendSlopeCredit;

        (&EthCtrlAddPtr->MTL_TXQ1.HICREDIT)[(ChnlCnt - 1U)
          * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U = EthCtrlCfgPtr->
                    EthTxFifoCfgPtr[FifoMapIdx].HiCredit;

        (&EthCtrlAddPtr->MTL_TXQ1.LOCREDIT)[(ChnlCnt - 1U)
          * ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U = EthCtrlCfgPtr->
                    EthTxFifoCfgPtr[FifoMapIdx].LoCredit;
      }
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={265C0A07-5CB2-4818-B039-3090272E844B}]  **
**                                                                            **
** Syntax          : void Eth_17_GEthMacV2_lCfgRxQueue (const                 **
**                          Eth_17_GEthMacV2_CoreCtrlConfigType* const        **
**                                                       EthCtrlCfgPtr)       **
**                                                                            **
** Description     : Configures the MTL receive queues                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  None                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                                   configuration.                           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lCfgRxQueue(const
                  Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint32 QueueOpVal;
  uint32 QueuePrioVal;
  uint32 QueueDmaMap;
  uint8 RxChnlsUsd;
  uint8 FifoMapIdx;
  uint8 ChnlCnt;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Get the number of receive channels */
  RxChnlsUsd = EthCtrlCfgPtr->EthNumRxChnls;

  QueueDmaMap = 0U;
  QueueOpVal = 0U;
  QueuePrioVal = 0U;

  /* [cover parentID={9BB8A676-64F8-4847-B8AC-932BA4A624E0}]
  Loop for the number of configured Rx channels
  [/cover] */
  for(ChnlCnt = 0U; ChnlCnt < RxChnlsUsd; ChnlCnt++)
  {
    FifoMapIdx = EthCtrlCfgPtr->EthRxChnlFifoMapPtr[ChnlCnt];

    /* Configure MTL Operation mode for RX Queue */
    (&EthCtrlAddPtr->MTL_RXQ0.OPERATION_MODE)[ChnlCnt *
            ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].U =
      ((uint32)ETH_17_GETHMACV2_MTL_RSF | ETH_17_GETHMACV2_MTL_FUP |
      ((uint32)EthCtrlCfgPtr->EthRxFifoCfgPtr[FifoMapIdx].RxQueueSize << 20U));

    /*Map RX Queue to DMA channel */
    QueueDmaMap |= (uint32)ChnlCnt << (ChnlCnt * 8U);

    QueueOpVal |= (uint32)ETH_17_GETHMACV2_MTL_RXQ_ENABLE << (ChnlCnt * 2U);

    QueuePrioVal |= (uint32)EthCtrlCfgPtr->EthRxFifoCfgPtr[FifoMapIdx].
                               RxFifoPriority << (ChnlCnt * 8U);
  }

  if (RxChnlsUsd > 0U)
  {
    /* Configure the RX Queues to DMA channel */
    EthCtrlAddPtr->MTL_RXQ_DMA_MAP0.U = QueueDmaMap;

    /* Configure the priorities of the queues */
    EthCtrlAddPtr->MAC_RXQ_CTRL2.U = QueuePrioVal;

    /* [cover parentID={C3E90A5D-FF0C-4a97-977E-CCA4E6C224C1}]
    Configure the routing of the untagged packets
    [/cover] */
    EthCtrlAddPtr->MAC_RXQ_CTRL1.U = ((uint32)EthCtrlCfgPtr->EthUntagRxQueue) |
      ((uint32)EthCtrlCfgPtr->EthUntagRxQueue << ETH_17_GETHMACV2_SHIFT_4BIT) |
      ((uint32)EthCtrlCfgPtr->EthUntagRxQueue << ETH_17_GETHMACV2_SHIFT_12BIT);

    /* [cover parentID={35525923-664E-4120-BEC7-C2F6E6ABCD65}]
    Enable the required queues for Rx operation
    [/cover] */
    EthCtrlAddPtr->MAC_RXQ_CTRL0.U = QueueOpVal;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B833D61C-1C4E-4428-98A4-CF036C9D9AEF}]  **
**                                                                            **
** Syntax          : boolean Eth_17_GEthMacV2_lQEmptySt (                     **
**                                                  const uint16 QFront)      **
**                                                                            **
** Description     : Checks whether the queue is empty based on the value of  **
**                    front index                                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : QFront - Front index of the queue                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : TRUE - Queue is empty                                    **
**                   FALSE - Queue is non-empty                               **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_GEthMacV2_lQEmptySt(const uint16 QFront)
{
  boolean QStatus;

  QStatus = FALSE;

  /* [cover parentID={1F5AAC68-1783-4afa-BBAE-BD24F78CCAC4}]
  Is queue front index same as queue reset value?
  [/cover] */
  if (QFront == ETH_17_GETHMACV2_QRST_VAL)
  {
    QStatus = TRUE;
  }

  return QStatus;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={6CDA273B-5AFE-4b51-BBEF-9E3D3A92B679}]  **
**                                                                            **
** Syntax          : void Eth_17_GEthMacV2_lAddQElem (                        **
**                          const uint16 Element, uint16* const QueuePtr,     **
**                          uint16 * const QFrontPtr, uint16* const QRearPtr, **
**                          const uint16 QueueSize)                           **
**                                                                            **
** Description     : Function to add an element into the queue                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Element - Element value to be added to the queue         **
**                   QueueSize - Total size of the queue                      **
**                                                                            **
** Parameters (inout): QFrontPtr - Pointer to the front index of queue, used  **
**                                 to check if queue is empty. If empty,      **
**                                 front index is set to 0                    **
**                                                                            **
** Parameters (out): QueuePtr - Pointer to the start of queue memory, accessed**
**                              to add the element to the queue               **
**                   QRearPtr - Pointer to the rear index of queue, this rear **
**                              index is incremented and element is added to  **
**                              the queue                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
static void Eth_17_GEthMacV2_lAddQElem(const uint16 Element,
                              uint16* const QueuePtr, uint16 * const QFrontPtr,
                              uint16* const QRearPtr, const uint16 QueueSize)
{
  /* [cover parentID={410B33EF-7E3F-4fb6-AE07-F8A6210712EE}]
  Is queue empty?
  [/cover] */
  if (*QFrontPtr == ETH_17_GETHMACV2_QRST_VAL)
  {
    *QFrontPtr = 0U;
    *QRearPtr = 0U;
  }
  else
  {
    *QRearPtr = (*QRearPtr + 1U) % QueueSize;
  }

  QueuePtr[*QRearPtr] = Element;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F6DBB9FF-AC7E-4f5f-B0C7-7875C6798BF3}]  **
**                                                                            **
** Syntax          : uint16 Eth_17_GEthMacV2_lReadQElem (                     **
**                     const uint16* const QueuePtr, uint16* const QFrontPtr, **
**                     uint16* const QRearPtr, const uint16 QueueSize)        **
**                                                                            **
** Description     : To read an element from the queue                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : QueuePtr - Pointer to the start of queue memory,         **
**                               accessed to read the element from queue      **
**                   QueueSize - Total size of the queue                      **
**                                                                            **
** Parameters (inout): QFrontPtr - Pointer to the front index of queue, used  **
**                                 to check if queue has only one element.    **
**                                 If yes, front index is set to reset value  **
**                     QRearPtr - Pointer to the rear index of queue, used    **
**                                 to check if queue has only one element.    **
**                                 If yes, rear index is set to reset value   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint16 - The element value read out from the queue       **
**                                                                            **
*******************************************************************************/
static uint16 Eth_17_GEthMacV2_lReadQElem(const uint16* const QueuePtr,
        uint16* const QFrontPtr, uint16* const QRearPtr, const uint16 QueueSize)
{
  uint16 Element;

  /* [cover parentID={F77271C7-A128-48cc-9714-9A1AEC40EA5B}]
  Read out the value from the rear index of the queue
  [/cover] */
  Element = QueuePtr[*QFrontPtr];

  /* [cover parentID={B27D1036-89FB-4f88-873C-2A650056CD67}]
  Is queue front index = rear index ?
  [/cover] */
  /* Only one element in Queue, reset it */
  if (*QFrontPtr == *QRearPtr)
  {
    *QFrontPtr = ETH_17_GETHMACV2_QRST_VAL;
    *QRearPtr = ETH_17_GETHMACV2_QRST_VAL;
  }
  else
  {
    *QFrontPtr = (*QFrontPtr + 1U) % QueueSize;
  }

  return Element;
}

#if (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={486188AD-FF7D-4115-AC69-D4808C0D1C99}]  **
**                                                                            **
** Syntax          : Std_ReturnType Eth_17_GEthMacV2_lChkSwtRxFrmParam (      **
**                     const uint16 RxActualLen, const uint16 RxModifiedLen,  **
**                                       const uint8* const EthTypeAddrPtr,   **
**                                             const uint8* const BufferPtr)  **
**                                                                            **
** Description     : Checks the validity of modified parameters by the switch **
**                    API EthSwt_EthRxProcessFrame                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : RxActualLen - Actual length of the received frame        **
**                   RxModifiedLen - Length modified by                       **
**                                    EthSwt_EthRxProcessFrame API            **
**                   EthTypeAddrPtr - Pointer to the address of EthType field **
**                   BufferPtr - Address of the receive buffer                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Std_ReturnType - E_OK: Valid parameter modification      **
**                                E_NOT_OK: Invalid parameter modification    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Eth_17_GEthMacV2_lChkSwtRxFrmParam(
            const uint16 RxActualLen, const uint16 RxModifiedLen,
            const uint8* const EthTypeAddrPtr, const uint8* const BufferPtr)
{
  Std_ReturnType RetVal;

  /* if length is incremented from the actual received length or
   * length is modified below the minimum length */
  /* [cover parentID={49FB5A86-FF30-4fb5-B039-1977168D3E41}]
  [/cover] */
  if ((RxModifiedLen > RxActualLen) || (RxModifiedLen < 18U))
  {
    RetVal = E_NOT_OK;
  }
  /* Address is not updated correctly by the EthSwt driver */
  /* [cover parentID={D40A628C-645D-40dc-96D4-96240A840CD9}]
  [/cover] */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
    pointer type is performed to check for the correct address modification
    by the EthSwt driver API. This is validity check for the modified address.
    There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is performed to check for the correct address modification
    by the EthSwt driver API. This is validity check for the modified address.
    There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
    expression is performed to check for the correct address modification
    by the EthSwt driver API. This is validity check for the modified address.
    There are no side effects seen by violating this rule.*/
  else if (EthTypeAddrPtr != (uint8*)((uint32)&(BufferPtr\
              [ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS]) +\
              (uint32)(RxActualLen - RxModifiedLen)))
  {
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={108BA321-DCBE-4373-8A1B-B15DD893E9C5}]  **
**                                                                            **
** Syntax          : BufReq_ReturnType Eth_17_GEthMacV2_lSwtAdaptPrepFrame (  **
**                     const uint8 CtrlIdx, const uint8 PrioMapIdx,           **
**                     Eth_BufIdxType* const BufIdxPtr, uint8** const BufPtr, **
**                                             uint16* const LenBytePtr)      **
**                                                                            **
** Description     : Function to provide the switch management support        **
**                    functionality in Eth_17_GEthMacV2_ProvideTxBuffer API   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : CtrlIdx - Index of the controller                        **
**                   PrioMapIdx - Internal FIFO reference index               **
**                                                                            **
** Parameters (inout): BufPtr - Pointer to the granted buffer. In case of     **
**                      invalid parameter modification of EthSwt API, the     **
**                      existing value is restored.                           **
**                     LenBytePtr - Pointer to the length in bytes. In case   **
**                      of invalid parameter modification of EthSwt API, the  **
**                      existing value at the address is restored.            **
**                                                                            **
** Parameters (out): BufIdxPtr - Address where the granted buffer index is    **
**                               stored                                       **
**                                                                            **
** Return value     : BUFREQ_OK       - Successfully granted buffer           **
**                    BUFREQ_E_NOT_OK - Error detected                        **
**                    BUFREQ_E_OVFL - Requested additional size by EthSwt     **
**                                    driver too large                        **
**                                                                            **
*******************************************************************************/
static BufReq_ReturnType Eth_17_GEthMacV2_lSwtAdaptPrepFrame(
                                             const uint8 CtrlIdx,
                                             const uint8 PrioMapIdx,
                                             Eth_BufIdxType* const BufIdxPtr,
                                             uint8** const BufPtr,
                                             uint16* const LenBytePtr)
{
  Eth_17_GEthMacV2_TxBuffTableType *TxBuffTablePtr;
  const Eth_17_GEthMacV2_CoreCtrlConfigType *EthLocalCtrlCfgPtr;
  const Eth_17_GEthMacV2_CtrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMacV2_BuffDescType *EthLocalBuffDescPtr;
  const volatile uint8 *TxBuffBasePtr;
  uint8 *EthBufPtr;
  uint8 *ModEthBufPtr;
  BufReq_ReturnType BufferStatus;
  Eth_BufIdxType EthBufIdx;
  uint16 TxBufLengthAligned;
  uint16 TxBufLengthConfig;
  uint16 CurrTxBufIdx;
  uint16 LenBytes;
  uint16 ModLenBytes;
  Std_ReturnType SwtRetVal;
  uint8 FifoIdx;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_GEthMacV2_lGetCtrlStatusPtr(CtrlIdx);

  EthLocalBuffDescPtr = EthLocalCoreStatusPtr->EthBuffDescPtr;

  /* Get controller configuration data */
  EthLocalCtrlCfgPtr = Eth_17_GEthMacV2_lGetCtrlConfigPtr(CtrlIdx);

  FifoIdx = EthLocalCtrlCfgPtr->EthTxFifoCfgPtr[PrioMapIdx].TxFifoIdx;

  /* Get configured buffer length */
  TxBufLengthConfig = EthLocalCtrlCfgPtr->
                       EthTxFifoCfgPtr[PrioMapIdx].TxBufferSize;

  LenBytes = *LenBytePtr;

  /* [cover parentID={51C179D7-6F9A-4fb5-BBBF-25791BE70C0A}]
  Invoke EthSwt_EthTxAdaptBufferLength API
  [/cover] */
  EthSwt_EthTxAdaptBufferLength(LenBytePtr);

  /* Make a copy and restore the requested length to LenBytePtr */
  ModLenBytes = *LenBytePtr;
  *LenBytePtr = LenBytes;

  /* [cover parentID={842E35D5-EEFB-444f-998C-B9BE2DDE0A5C}]
  If the modified length exceeds the configured buffer size
  [/cover] */
  if (ModLenBytes > (TxBufLengthConfig -
          ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                       ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH))))
  {
    /* Fill output parameter 'LenBytePtr' as
       Allocated Tx Buffer Size - Frame Header and CRC) */
    *LenBytePtr = TxBufLengthConfig -
                    ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                      ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH));

    /* BufferStatus - modified buffer size too large */
    BufferStatus = BUFREQ_E_OVFL;
  }
  /* [cover parentID={CA4732EA-ECCC-485b-83E7-021FBB84BD7B}]
  if the modified length is reduced from the actual requested length
  [/cover] */
  else if (ModLenBytes < LenBytes)
  {
    /* BufferStatus - Error detected due to incorrect length
       modification by the switch driver */
    BufferStatus = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* Read the buffer index from the queue (Queue front should not move here
     * as the validation of the modified parameters from Switch API is not
     * yet done */
    CurrTxBufIdx = EthLocalBuffDescPtr->EthTxBuffQueuePtr[FifoIdx]
      [EthLocalBuffDescPtr->EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront];

    /* Provide Buffer index and buffer pointer to application
       Set buffer used, Transmission not yet requested, no confirmation. */
    EthBufIdx = ((uint32)PrioMapIdx << ETH_17_GETHMACV2_FIFOIDX_POS) |
                                                        (CurrTxBufIdx);

    TxBuffBasePtr = &(EthLocalBuffDescPtr->EthTxBufferPtr[FifoIdx][0U]);

    TxBufLengthAligned = EthLocalCtrlCfgPtr->
                            EthTxFifoCfgPtr[PrioMapIdx].TxBufferAlignSize;

    /* Make a copy of the existing address to restore in error scenario */
    EthBufPtr = *BufPtr;

    /* [cover parentID={C8A3E370-6088-460d-BCE6-0DA24BB92C8E}]
    Store requested buffer length to check after invocation of Tx Prepare
    Frame API
    [/cover] */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
    pointer type is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
    expression is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is performed to access the buffer address from DMA descriptor.
    This is the intended design and valid as per DMA hardware design.
    There are no side effects seen by violating this rule.*/
    *BufPtr = (uint8*)(((uint32)TxBuffBasePtr +\
                         ((uint32)CurrTxBufIdx * TxBufLengthAligned)) +\
                          (uint32)ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS);

    /* [cover parentID={63394BF9-B5F5-41fe-B455-7AE5CF9D1A7E}]
    Invoke the EthSwt_EthTxPrepareFrame API for Tx frame preparation
    [/cover] */
    SwtRetVal = EthSwt_EthTxPrepareFrame(CtrlIdx, EthBufIdx,
                                         BufPtr, LenBytePtr);

    /* Make a copy and restore the requested length to LenBytePtr and
     * address to the initial value */
    ModLenBytes = *LenBytePtr;
    *LenBytePtr = LenBytes;
    ModEthBufPtr = *BufPtr;
    *BufPtr = EthBufPtr;

    /* [cover parentID={4C98FF3C-1E19-41d1-9C4C-E96A868DF7CB}]
    Is Frame successfully prepared by the switch driver (return value - E_OK)
    [/cover] */
    if (SwtRetVal == E_OK)
    {
      /* [cover parentID={088F5901-C890-4186-9858-8A9AB36A6D5D}]
      If the modified length exceeds the configured buffer size
      [/cover] */
      if (ModLenBytes > (TxBufLengthConfig -
              ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                           ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH))))
      {
        /* Fill output parameter 'LenBytePtr' as
           Allocated Tx Buffer Size - Frame Header and CRC) */
        *LenBytePtr = TxBufLengthConfig -
                        ((uint16)(ETH_17_GETHMACV2_FRAMEHEADER_LENGTH +
                          ETH_17_GETHMACV2_FRAMECHKSUM_LENGTH));

        /* BufferStatus - modified buffer size too large */
        BufferStatus = BUFREQ_E_OVFL;
      }
      /* [cover parentID={F2A60DDC-22D7-4132-B861-F5F45CBEFDF6}]
      if the modified length is reduced from the actual requested length
      [/cover] */
      else if (ModLenBytes < LenBytes)
      {
        /* BufferStatus - Error detected due to incorrect length
           modification by the switch driver */
        BufferStatus = BUFREQ_E_NOT_OK;
      }
      /* [cover parentID={E3B07092-5E79-4fc6-AE4A-6CEB42D9A684}]
      Is Buffer pointer modified by the TxPrep frame API correct ?
      [/cover] */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
      pointer type is performed to access the buffer address and compare it
      with the modified address by the EthSwt API. There are no side effects
      seen by violating this rule.*/
      /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
      expression is performed to access the buffer address and compare it
      with the modified address by the EthSwt API. There are no side effects
      seen by violating this rule.*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
      is performed to access the buffer address and compare it with the
      modified address by the EthSwt API. There are no side effects seen by
      violating this rule.*/
      else if (ModEthBufPtr != (uint8*)(((uint32)TxBuffBasePtr +\
              ((uint32)CurrTxBufIdx * TxBufLengthAligned) +\
               (uint32)ETH_17_GETHMACV2_FRAME_TYPE_MSB_POS) +\
               (uint32)(ModLenBytes - LenBytes)))
      {
        /* BufferStatus - Error detected due to incorrect data pointer
           modification by the switch driver */
        BufferStatus = BUFREQ_E_NOT_OK;
      }
      else
      {
        /* All conditions are met for providing the buffer index */
        /* [cover parentID={44922A77-7315-47ad-BCF2-0403D98ABE0A}]
        Get the buffer index from the queue
        [/cover] */
        CurrTxBufIdx = Eth_17_GEthMacV2_lReadQElem(EthLocalBuffDescPtr->
          EthTxBuffQueuePtr[FifoIdx], &EthLocalBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].CurrQFront, &EthLocalBuffDescPtr->
          EthRunTmTxChnlDataPtr[FifoIdx].CurrQRear, EthLocalCtrlCfgPtr->
              EthTxFifoCfgPtr[PrioMapIdx].NumOfTxBuffers);

        /* [cover parentID={CF130415-6C2C-44b3-BC47-A044438EDDD6}]
        Get current TxBuffTable index and set the buffer status to USED.
        Store the modified length (actual length + length requested by
        EthSwt driver API).
        [/cover] */
        /* Get current TxBuffTable index to check buffer status */
        TxBuffTablePtr= &(EthLocalBuffDescPtr->EthTxBuffTablePtr[FifoIdx]
                                                          [CurrTxBufIdx]);

        TxBuffTablePtr->BuffStatus = ETH_17_GETHMACV2_BUFFER_USED;

#if(ETH_17_GETHMACV2_GLOBALTIMESUPPORT == STD_ON)
        TxBuffTablePtr->TimeStampEnable = ETH_17_GETHMACV2_DISABLE;
#endif

        /* Store the length which is modified by the switch driver */
        TxBuffTablePtr->BuffLengthReqstd = ModLenBytes;

        /* [cover parentID={1E510508-AC74-4b9a-8719-88750EF85BFF}]
        Provide the buffer index, address of the granted buffer as the
        output parameters
        [/cover] */
        *BufIdxPtr = EthBufIdx;

        *BufPtr = (uint8*)(&ModEthBufPtr[ETH_17_GETHMACV2_ETHERTYPE_LEN]);

        /* [cover parentID={2EF93CC4-CC06-4d2d-8D06-E0721DD9FD8C}]
        Update Buffer status as BUFREQ_OK
        [/cover] */
        BufferStatus = BUFREQ_OK;
      }
    }
    else
    {
      /* Frame preparation failed in the Swt driver */
      /* [cover parentID={663724E4-E4A9-4f92-995C-DE092A0864E6}]
      Update buffer status as BUFREQ_E_NOT_OK
      [/cover] */
      BufferStatus = BUFREQ_E_NOT_OK;
    }
  }

  return BufferStatus;
}

#endif /* (ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={683EED20-CB2F-46a2-B65B-A458937326D3}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_GEthMacV2_lTxQFlush(const  **
**                   Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)**
**                                                                            **
** Description      : Function to perform the flush operation of the transmit **
**                      queues                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthCtrlCfgPtr- Pointer to Ethernet controller           **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType- E_OK: Tx queue flush operation complete **
**                                    E_NOT_OK: Timeout error occurred        **
**                                     waiting for flush operation to complete**
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_GEthMacV2_lTxQFlush(const
               Eth_17_GEthMacV2_CoreCtrlConfigType* const EthCtrlCfgPtr)
{
  Ifx_GETH *EthCtrlAddPtr;
  uint32 DelayTickResolution;
  uint32 NumberWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 TxFlushSt;
  uint8 ChnlsUsd;
  uint8 LoopCnt;
  Std_ReturnType RetVal;
  boolean IsTimeExpired;

  RetVal = E_OK;

  EthCtrlAddPtr = Eth_17_GEthMacV2_CtrlBaseAddrPtr[EthCtrlCfgPtr->EthCtrlIdx];

  /* Check whether Tx flushing operation is complete, wait only until timeout */
  /* Get STM timer current resolution and calculate number of ticks to wait*/
  DelayTickResolution = Mcal_DelayTickResolution();
  NumberWaitTicks  = (ETH_17_GETHMACV2_MAXTIMEOUT_COUNT / DelayTickResolution);

  /* Do not allow wait ticks to be zero, if STM timer resolution is lower */
  if(NumberWaitTicks == 0U)
  {
    /* Increment the ticks */
    NumberWaitTicks++;
  }

  ChnlsUsd = EthCtrlCfgPtr->EthNumTxChnls;

  /* Stop Transmission on the required DMA Channels */
  for (LoopCnt = 0; LoopCnt < ChnlsUsd; LoopCnt++)
  {
    /* [cover parentID={E74B37B5-1292-4e20-8736-516D0C0E98D3}]
    Initiate the transmit queue flush operation
    [/cover] */
    (&EthCtrlAddPtr->MTL_TXQ0.OPERATION_MODE)[LoopCnt *
                          ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].B.FTQ = 1U;

    /* Wait until the Tx flush operation is complete before writing to the
       OPERATION_MODE register of next queue */
    /*Get current STM tick*/
    CurrSTMTick   = Mcal_DelayGetTick();
    BaseSTMTick   = CurrSTMTick;
    IsTimeExpired = FALSE;

    /* wait until Tx queue flushing is done or time has elapsed */
    do
    {
      TxFlushSt = (&EthCtrlAddPtr->MTL_TXQ0.OPERATION_MODE)[LoopCnt *
                          ETH_17_GETHMACV2_MTL_REG_OFFSETADDR].B.FTQ;

      /* Check if wait time has reached maximum timeout configured */
      if((((uint32)((CurrSTMTick - BaseSTMTick) &
          ETH_17_GETHMACV2_STM_TICK_OVERFLOW)) >=
          NumberWaitTicks) && (TxFlushSt == ETH_17_GETHMACV2_QFLUSH_IN_PROG))
      {
        /* Timeout happened and reset is not completed yet*/
        IsTimeExpired = TRUE;
      }

      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();
    }while((TxFlushSt == ETH_17_GETHMACV2_QFLUSH_IN_PROG) &&
                                    (IsTimeExpired == FALSE));

    /* [cover parentID={AA1D27EF-F84F-48a3-9FF3-F6607F9D054B}]
    Timeout elapsed ?
    [/cover] */
    if (IsTimeExpired == TRUE)
    {
      /* If timeout has occurred, report Production error for timeout */
      /* [cover parentID={2D10DBFB-1EA2-46bc-A35E-758F51FE2372}]
      [/cover] */
      Eth_17_GEthMacV2_lDemtimeout(IsTimeExpired, EthCtrlCfgPtr->EthDemAccess);

      RetVal = E_NOT_OK;

      /* Break the loop when timeout condition has occurred */
      break;
    }
  }

  return RetVal;
}

#define ETH_17_GETHMACV2_STOP_SEC_CODE_QM_GLOBAL
 /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMacV2_MemMap.h"

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
