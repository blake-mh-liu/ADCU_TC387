/* 
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

*/

#ifndef SPI_USERCODE_H
#define SPI_USERCODE_H

/**
 * \file Spi_UserCode.h
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
#include <Std_Types.h>	/* AUTOSAR standard types */

/*==================[macros]================================================*/
#ifdef QSPI_SCR_CLR_MASK
#error QSPI_SCR_CLR_MASK already defined
#endif
/** \brief Set CLRR to clear SRR bit and disable SRE bit */
#define QSPI_SCR_CLR_MASK (0x02000000u)

#ifdef QSPI_SCR_DMA_MODE
#error QSPI_SCR_DMA_MODE already defined
#endif
/** \brief Set ToS to DMA */
#define QSPI_SCR_DMA_MODE (1u)

#ifdef QSPI_SCR_EN_SRE
#error QSPI_SCR_EN_SRE already defined
#endif
/** \brief Bit to enable service request */
#define QSPI_SCR_EN_SRE   (1u)

/*-------------------------[Application specific]----------------------------*/
/* User: Please change to your needs */

#ifdef QSPI_SCR_RX_PRIO
#error QSPI_SCR_RX_PRIO already defined
#endif
/** \brief QSPI2RX to DMA channel mapping */
#define QSPI_SCR_RX_PRIO  (4u)

#ifdef QSPI_SCR_TX_PRIO
#error QSPI_SCR_TX_PRIO already defined
#endif
/** \brief QSPI2TX to DMA channel mapping */
#define QSPI_SCR_TX_PRIO  (5u)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/** \brief User function to initialize DMA in SPI
 **
 ** \return No return value. */
extern FUNC(void, SPI_APPL_CODE) Spi_InitDMAUsr(void);

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* #ifndef SPI_USERCODE_H */
