/* 
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

*/

/**
 * \file Spi_UserCode.c
 *
 * \brief AUTOSAR MCAL templates
 *
 * This file contains a template implementation of an initialization
 * function to configure the Spi DMA transfer in asynchronous mode.
 *
 * \par To be changed by user: yes
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 *
 * \remarks Please read ImportantNotes_DMATemplate.txt
 */

/*==================[inclusions]============================================*/

#include <Spi.h>          /* AUTOSAR SPI driver to include Ifx_SRC_SRCR */
#include <Spi_UserCode.h> /* Own header file for macro definitions */
#include "IfxSrc_regdef.h"
#include "IfxSrc_reg.h"

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

FUNC(void, SPI_APPL_CODE) Spi_InitDMAUsr(void)
{
  /* Note: If template matches to your need please change '#if 1' to #if 0' */
#if 1
  /* QSPI RX and TX have to be mapped to DMA - not to interrupts. Infineon IRQ
   * module is capable to map interrupt nodes to CPU0/CPU1/CPU2 interrupts or
   * to DMA.
   * This functionality have to be implemented in the user application as part
   * of integration code with EB's Autocore OS or Safety OS and with AutoCore
   * Generic.
   *
   *  Implementation hint:
   *  Please adapt macros "QSPI_SCR_RX_PRIO" and "QSPI_SCR_TX_PRIO" to match
   *  the configuration in your application.
   *
   *  FUNC(void, SPI_APPL_CODE) Spi_InitDMAUsr(void)
   *  {
   *    Ifx_SRC_SRCR txDMA, rxDMA;
   *    txDMA.U = 0U;
   *    rxDMA.U = 0U;
   *
   *    SRC_QSPI_QSPI2_TX.U = QSPI_SCR_CLR_MASK;
   *    SRC_QSPI_QSPI2_RX.U = QSPI_SCR_CLR_MASK;
   *
   *    txDMA.B.TOS = QSPI_SCR_DMA_MODE;
   *    rxDMA.B.TOS = QSPI_SCR_DMA_MODE;
   *
   *    txDMA.B.SRPN = QSPI_SCR_TX_PRIO;
   *    rxDMA.B.SRPN = QSPI_SCR_RX_PRIO;
   *
   *    txDMA.B.SRE = QSPI_SCR_EN_SRE;
   *    rxDMA.B.SRE = QSPI_SCR_EN_SRE;
   *  
   *    SRC_QSPI_QSPI2_TX.U = txDMA.U;
   *    SRC_QSPI_QSPI2_RX.U = rxDMA.U;
   *  }
   */
#else
  Ifx_SRC_SRCR txDMA, rxDMA;
  txDMA.U = 0U;
  rxDMA.U = 0U;

  /* Clear pending requests before DMA configuration */
  SRC_QSPI_QSPI2_TX.U = QSPI_SCR_CLR_MASK;
  SRC_QSPI_QSPI2_RX.U = QSPI_SCR_CLR_MASK;

  /* Set Type of Service to 'DMA' */
  txDMA.B.TOS = QSPI_SCR_DMA_MODE;
  rxDMA.B.TOS = QSPI_SCR_DMA_MODE;
  /* Set Service Request Priority Number aka 'DMA channel' */
  txDMA.B.SRPN = QSPI_SCR_TX_PRIO;
  rxDMA.B.SRPN = QSPI_SCR_RX_PRIO;
  /* Service Request Enable bit */
  txDMA.B.SRE = QSPI_SCR_EN_SRE;
  rxDMA.B.SRE = QSPI_SCR_EN_SRE;
  
  /* Write to QSPI2 Service Request registers */
  SRC_QSPI_QSPI2_TX.U = txDMA.U;
  SRC_QSPI_QSPI2_RX.U = rxDMA.U;
#endif
}
