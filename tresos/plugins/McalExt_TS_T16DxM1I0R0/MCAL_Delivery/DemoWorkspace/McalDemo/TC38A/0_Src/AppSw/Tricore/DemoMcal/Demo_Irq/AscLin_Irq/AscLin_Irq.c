/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : AscLin_Irq.c                                                  **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-08                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the ISR handlers for the                 **
**                Lin_17_AscLin/UART Module.                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of LIN Driver,AUTOSAR Release 4.2.2/4.4.0**
**                     and UART driver.                                       **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
/* 
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

*/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Platforms_Macros.h"
#include "Irq.h"

#if (((defined IRQ_ASCLIN_CHANNEL0_USED) && (IRQ_ASCLIN_CHANNEL0_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL1_USED) && (IRQ_ASCLIN_CHANNEL1_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL2_USED) && (IRQ_ASCLIN_CHANNEL2_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL3_USED) && (IRQ_ASCLIN_CHANNEL3_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL4_USED) && (IRQ_ASCLIN_CHANNEL4_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL5_USED) && (IRQ_ASCLIN_CHANNEL5_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL6_USED) && (IRQ_ASCLIN_CHANNEL6_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL7_USED) && (IRQ_ASCLIN_CHANNEL7_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL8_USED) && (IRQ_ASCLIN_CHANNEL8_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL9_USED) && (IRQ_ASCLIN_CHANNEL9_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL10_USED) && (IRQ_ASCLIN_CHANNEL10_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL11_USED) && (IRQ_ASCLIN_CHANNEL11_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL12_USED) && (IRQ_ASCLIN_CHANNEL12_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL13_USED) && (IRQ_ASCLIN_CHANNEL13_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL14_USED) && (IRQ_ASCLIN_CHANNEL14_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL15_USED) && (IRQ_ASCLIN_CHANNEL15_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL16_USED) && (IRQ_ASCLIN_CHANNEL16_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL17_USED) && (IRQ_ASCLIN_CHANNEL17_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL18_USED) && (IRQ_ASCLIN_CHANNEL18_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL19_USED) && (IRQ_ASCLIN_CHANNEL19_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL20_USED) && (IRQ_ASCLIN_CHANNEL20_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL21_USED) && (IRQ_ASCLIN_CHANNEL21_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL22_USED) && (IRQ_ASCLIN_CHANNEL22_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL23_USED) && (IRQ_ASCLIN_CHANNEL23_USED == IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER)))
#include "Lin_17_AscLin.h"
#endif

#if (((defined IRQ_ASCLIN_CHANNEL0_USED) && (IRQ_ASCLIN_CHANNEL0_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL1_USED) && (IRQ_ASCLIN_CHANNEL1_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL2_USED) && (IRQ_ASCLIN_CHANNEL2_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL3_USED) && (IRQ_ASCLIN_CHANNEL3_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL4_USED) && (IRQ_ASCLIN_CHANNEL4_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL5_USED) && (IRQ_ASCLIN_CHANNEL5_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL6_USED) && (IRQ_ASCLIN_CHANNEL6_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL7_USED) && (IRQ_ASCLIN_CHANNEL7_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL8_USED) && (IRQ_ASCLIN_CHANNEL8_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL9_USED) && (IRQ_ASCLIN_CHANNEL9_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL10_USED) && (IRQ_ASCLIN_CHANNEL10_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL11_USED) && (IRQ_ASCLIN_CHANNEL11_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL12_USED) && (IRQ_ASCLIN_CHANNEL12_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL13_USED) && (IRQ_ASCLIN_CHANNEL13_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL14_USED) && (IRQ_ASCLIN_CHANNEL14_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL15_USED) && (IRQ_ASCLIN_CHANNEL15_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL16_USED) && (IRQ_ASCLIN_CHANNEL16_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL17_USED) && (IRQ_ASCLIN_CHANNEL17_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL18_USED) && (IRQ_ASCLIN_CHANNEL18_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL19_USED) && (IRQ_ASCLIN_CHANNEL19_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL20_USED) && (IRQ_ASCLIN_CHANNEL20_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL21_USED) && (IRQ_ASCLIN_CHANNEL21_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL22_USED) && (IRQ_ASCLIN_CHANNEL22_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)) || \
((defined IRQ_ASCLIN_CHANNEL23_USED) && (IRQ_ASCLIN_CHANNEL23_USED == IRQ_ASCLIN_CH_USED_BY_UART_DRIVER)))
#include "Uart.h"
#endif


#include "IFX_Os.h"
#include "AscLin_Irq.h"
/*******************************************************************************
**                      Private Macros Definitions                            **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

#if (IRQ_ASCLIN0TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN0TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN0_TX_PRIO > 0) || (IRQ_ASCLIN0_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN0_TX_PRIO > 0) && (IRQ_ASCLIN0_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN0TX_ISR, 0, IRQ_ASCLIN0_TX_PRIO)
#elif IRQ_ASCLIN0_TX_CAT == IRQ_CAT2
ISR(ASCLIN0TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(0U);
  #elif((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(0U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN0RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN0RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN0_RX_PRIO > 0) || (IRQ_ASCLIN0_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN0_RX_PRIO > 0) && (IRQ_ASCLIN0_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN0RX_ISR, 0, IRQ_ASCLIN0_RX_PRIO)
#elif IRQ_ASCLIN0_RX_CAT == IRQ_CAT2
ISR(ASCLIN0RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(0U);
  #elif((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(0U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN0ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN0ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN0_ERR_PRIO > 0) || (IRQ_ASCLIN0_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN0_ERR_PRIO > 0) && (IRQ_ASCLIN0_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN0ERR_ISR, 0, IRQ_ASCLIN0_ERR_PRIO)
#elif IRQ_ASCLIN0_ERR_CAT == IRQ_CAT2
ISR(ASCLIN0ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(0U);
  #elif((IRQ_ASCLIN_CHANNEL0_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(0U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN1TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN1TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_ASCLIN1_TX_PRIO > 0) || (IRQ_ASCLIN1_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN1_TX_PRIO > 0) && (IRQ_ASCLIN1_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN1TX_ISR, 0, IRQ_ASCLIN1_TX_PRIO)
#elif IRQ_ASCLIN1_TX_CAT == IRQ_CAT2
ISR(ASCLIN1TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #ifdef IRQ_ASCLIN_CHANNEL1_USED
  #if((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(1U);
  #elif((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(1U);
  #endif
  #else
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(1U);
  #endif /*#ifdef IRQ_ASCLIN_CHANNEL1_USED*/
}
#endif
#endif

#if (IRQ_ASCLIN1RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN1RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_ASCLIN1_RX_PRIO > 0) || (IRQ_ASCLIN1_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN1_RX_PRIO > 0) && (IRQ_ASCLIN1_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN1RX_ISR, 0, IRQ_ASCLIN1_RX_PRIO)
#elif IRQ_ASCLIN1_RX_CAT == IRQ_CAT2
ISR(ASCLIN1RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #ifdef IRQ_ASCLIN_CHANNEL1_USED
  #if((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(1U);
  #elif((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(1U);
  #endif
  #else
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(1U);
  #endif /*#ifdef IRQ_ASCLIN_CHANNEL1_USED*/
}
#endif
#endif
#if (IRQ_ASCLIN1ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN1ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if((IRQ_ASCLIN1_ERR_PRIO > 0) || (IRQ_ASCLIN1_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN1_ERR_PRIO > 0) && (IRQ_ASCLIN1_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN1ERR_ISR, 0, IRQ_ASCLIN1_ERR_PRIO)
#elif IRQ_ASCLIN1_ERR_CAT == IRQ_CAT2
ISR(ASCLIN1ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #ifdef IRQ_ASCLIN_CHANNEL1_USED
  #if((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(1U);
  #elif((IRQ_ASCLIN_CHANNEL1_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(1U);
  #endif
  #else
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(1U);
  #endif /*#ifdef IRQ_ASCLIN_CHANNEL1_USED*/
}
#endif
#endif

#if (IRQ_ASCLIN2TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN2TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN2_TX_PRIO > 0) || (IRQ_ASCLIN2_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN2_TX_PRIO > 0) && (IRQ_ASCLIN2_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN2TX_ISR, 0, IRQ_ASCLIN2_TX_PRIO)
#elif IRQ_ASCLIN2_TX_CAT == IRQ_CAT2
ISR(ASCLIN2TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(2U);
  #elif((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(2U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN2RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN2RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN2_RX_PRIO > 0) || (IRQ_ASCLIN2_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN2_RX_PRIO > 0) && (IRQ_ASCLIN2_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN2RX_ISR, 0, IRQ_ASCLIN2_RX_PRIO)
#elif IRQ_ASCLIN2_RX_CAT == IRQ_CAT2
ISR(ASCLIN2RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(2U);
  #elif((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(2U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN2ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN2ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN2_ERR_PRIO > 0) || (IRQ_ASCLIN2_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN2_ERR_PRIO > 0) && (IRQ_ASCLIN2_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN2ERR_ISR, 0, IRQ_ASCLIN2_ERR_PRIO)
#elif IRQ_ASCLIN2_ERR_CAT == IRQ_CAT2
ISR(ASCLIN2ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(2U);
  #elif((IRQ_ASCLIN_CHANNEL2_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(2U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN3TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN3TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN3_TX_PRIO > 0) || (IRQ_ASCLIN3_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN3_TX_PRIO > 0) && (IRQ_ASCLIN3_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN3TX_ISR, 0, IRQ_ASCLIN3_TX_PRIO)
#elif IRQ_ASCLIN3_TX_CAT == IRQ_CAT2
ISR(ASCLIN3TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(3U);
  #elif((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(3U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN3RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN3RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN3_RX_PRIO > 0) || (IRQ_ASCLIN3_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN3_RX_PRIO > 0) && (IRQ_ASCLIN3_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN3RX_ISR, 0, IRQ_ASCLIN3_RX_PRIO)
#elif IRQ_ASCLIN3_RX_CAT == IRQ_CAT2
ISR(ASCLIN3RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(3U);
  #elif((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(3U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN3ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN3ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmissiov or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN3_ERR_PRIO > 0) || (IRQ_ASCLIN3_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN3_ERR_PRIO > 0) && (IRQ_ASCLIN3_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN3ERR_ISR, 0, IRQ_ASCLIN3_ERR_PRIO)
#elif IRQ_ASCLIN3_ERR_CAT == IRQ_CAT2
ISR(ASCLIN3ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(3U);
  #elif((IRQ_ASCLIN_CHANNEL3_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(3U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN4TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN4TX_EXIST == STD_ON)
#if((IRQ_ASCLIN4_TX_PRIO > 0) || (IRQ_ASCLIN4_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN4_TX_PRIO > 0) && (IRQ_ASCLIN4_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN4TX_ISR, 0, IRQ_ASCLIN4_TX_PRIO)
#elif IRQ_ASCLIN4_TX_CAT == IRQ_CAT2
ISR(ASCLIN4TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(4U);
  #elif((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(4U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN4RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN4RX_EXIST == STD_ON)
#if((IRQ_ASCLIN4_RX_PRIO > 0) || (IRQ_ASCLIN4_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN4_RX_PRIO > 0) && (IRQ_ASCLIN4_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN4RX_ISR, 0, IRQ_ASCLIN4_RX_PRIO)
#elif IRQ_ASCLIN4_RX_CAT == IRQ_CAT2
ISR(ASCLIN4RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(4U);
  #elif((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(4U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN4ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN4ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN4_ERR_PRIO > 0) || (IRQ_ASCLIN4_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN4_ERR_PRIO > 0) && (IRQ_ASCLIN4_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN4ERR_ISR, 0, IRQ_ASCLIN4_ERR_PRIO)
#elif IRQ_ASCLIN4_ERR_CAT == IRQ_CAT2
ISR(ASCLIN4ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(4U);
  #elif((IRQ_ASCLIN_CHANNEL4_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(4U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN5TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN5TX_EXIST == STD_ON)
#if((IRQ_ASCLIN5_TX_PRIO > 0) || (IRQ_ASCLIN5_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN5_TX_PRIO > 0) && (IRQ_ASCLIN5_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN5TX_ISR, 0, IRQ_ASCLIN5_TX_PRIO)
#elif IRQ_ASCLIN5_TX_CAT == IRQ_CAT2
ISR(ASCLIN5TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(5U);
  #elif((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(5U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN5RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN5RX_EXIST == STD_ON)
#if((IRQ_ASCLIN5_RX_PRIO > 0) || (IRQ_ASCLIN5_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN5_RX_PRIO > 0) && (IRQ_ASCLIN5_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN5RX_ISR, 0, IRQ_ASCLIN5_RX_PRIO)
#elif IRQ_ASCLIN5_RX_CAT == IRQ_CAT2
ISR(ASCLIN5RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(5U);
  #elif((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(5U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN5ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN5ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN5_ERR_PRIO > 0) || (IRQ_ASCLIN5_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN5_ERR_PRIO > 0) && (IRQ_ASCLIN5_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN5ERR_ISR, 0, IRQ_ASCLIN5_ERR_PRIO)
#elif IRQ_ASCLIN5_ERR_CAT == IRQ_CAT2
ISR(ASCLIN5ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(5U);
  #elif((IRQ_ASCLIN_CHANNEL5_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(5U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN6TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN6TX_EXIST == STD_ON)
#if((IRQ_ASCLIN6_TX_PRIO > 0) || (IRQ_ASCLIN6_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN6_TX_PRIO > 0) && (IRQ_ASCLIN6_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN6TX_ISR, 0, IRQ_ASCLIN6_TX_PRIO)
#elif IRQ_ASCLIN6_TX_CAT == IRQ_CAT2
ISR(ASCLIN6TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(6U);
  #elif((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(6U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN6RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN6RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN6_RX_PRIO > 0) || (IRQ_ASCLIN6_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN6_RX_PRIO > 0) && (IRQ_ASCLIN6_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN6RX_ISR, 0, IRQ_ASCLIN6_RX_PRIO)
#elif IRQ_ASCLIN6_RX_CAT == IRQ_CAT2
ISR(ASCLIN6RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(6U);
  #elif((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(6U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN6ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN6ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN6_ERR_PRIO > 0) || (IRQ_ASCLIN6_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN6_ERR_PRIO > 0) && (IRQ_ASCLIN6_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN6ERR_ISR, 0, IRQ_ASCLIN6_ERR_PRIO)
#elif IRQ_ASCLIN6_ERR_CAT == IRQ_CAT2
ISR(ASCLIN6ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(6U);
  #elif((IRQ_ASCLIN_CHANNEL6_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(6U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN7TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN7TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN7_TX_PRIO > 0) || (IRQ_ASCLIN7_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN7_TX_PRIO > 0) && (IRQ_ASCLIN7_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN7TX_ISR, 0, IRQ_ASCLIN7_TX_PRIO)
#elif IRQ_ASCLIN7_TX_CAT == IRQ_CAT2
ISR(ASCLIN7TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(7U);
  #elif((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(7U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN7RX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN7RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN7_RX_PRIO > 0) || (IRQ_ASCLIN7_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN7_RX_PRIO > 0) && (IRQ_ASCLIN7_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN7RX_ISR, 0, IRQ_ASCLIN7_RX_PRIO)
#elif IRQ_ASCLIN7_RX_CAT == IRQ_CAT2
ISR(ASCLIN7RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(7U);
  #elif((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(7U);
  #endif
}
#endif
#endif
#if (IRQ_ASCLIN7ERR_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN7ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN7_ERR_PRIO > 0) || (IRQ_ASCLIN7_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN7_ERR_PRIO > 0) && (IRQ_ASCLIN7_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN7ERR_ISR, 0, IRQ_ASCLIN7_ERR_PRIO)
#elif IRQ_ASCLIN7_ERR_CAT == IRQ_CAT2
ISR(ASCLIN7ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(7U);
  #elif((IRQ_ASCLIN_CHANNEL7_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(7U);
  #endif
}
#endif
#endif

#if (IRQ_ASCLIN8TX_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ASCLIN8TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_ASCLIN8_TX_PRIO > 0) || (IRQ_ASCLIN8_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN8_TX_PRIO > 0) && (IRQ_ASCLIN8_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN8TX_ISR, 0, IRQ_ASCLIN8_TX_PRIO)
#elif IRQ_ASCLIN8_TX_CAT == IRQ_CAT2
ISR(ASCLIN8TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(8U);
  #elif((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(8U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN8RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN8RX_EXIST == STD_ON)
#if((IRQ_ASCLIN8_RX_PRIO > 0) || (IRQ_ASCLIN8_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN8_RX_PRIO > 0) && (IRQ_ASCLIN8_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN8RX_ISR, 0, IRQ_ASCLIN8_RX_PRIO)
#elif IRQ_ASCLIN8_RX_CAT == IRQ_CAT2
ISR(ASCLIN8RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(8U);
  #elif((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(8U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN8ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN8ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN8_ERR_PRIO > 0) || (IRQ_ASCLIN8_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN8_ERR_PRIO > 0) && (IRQ_ASCLIN8_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN8ERR_ISR, 0, IRQ_ASCLIN8_ERR_PRIO)
#elif IRQ_ASCLIN8_ERR_CAT == IRQ_CAT2
ISR(ASCLIN8ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(8U);
  #elif((IRQ_ASCLIN_CHANNEL8_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(8U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN9TX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN9TX_EXIST == STD_ON)
#if((IRQ_ASCLIN9_TX_PRIO > 0) || (IRQ_ASCLIN9_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN9_TX_PRIO > 0) && (IRQ_ASCLIN9_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN9TX_ISR, 0, IRQ_ASCLIN9_TX_PRIO)
#elif IRQ_ASCLIN9_TX_CAT == IRQ_CAT2
ISR(ASCLIN9TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(9U);
  #elif((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(9U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN9RX_ISR(void)                                **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN9RX_EXIST == STD_ON)
#if((IRQ_ASCLIN9_RX_PRIO > 0) || (IRQ_ASCLIN9_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN9_RX_PRIO > 0) && (IRQ_ASCLIN9_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN9RX_ISR, 0, IRQ_ASCLIN9_RX_PRIO)
#elif IRQ_ASCLIN9_RX_CAT == IRQ_CAT2
ISR(ASCLIN9RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(9U);
  #elif((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(9U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN9ERR_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN9ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN9_ERR_PRIO > 0) || (IRQ_ASCLIN9_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN9_ERR_PRIO > 0) && (IRQ_ASCLIN9_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN9ERR_ISR, 0, IRQ_ASCLIN9_ERR_PRIO)
#elif IRQ_ASCLIN9_ERR_CAT == IRQ_CAT2
ISR(ASCLIN9ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(9U);
  #elif((IRQ_ASCLIN_CHANNEL9_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(9U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN10TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN10TX_EXIST == STD_ON)
#if((IRQ_ASCLIN10_TX_PRIO > 0) || (IRQ_ASCLIN10_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN10_TX_PRIO > 0) && (IRQ_ASCLIN10_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN10TX_ISR, 0, IRQ_ASCLIN10_TX_PRIO)
#elif IRQ_ASCLIN10_TX_CAT == IRQ_CAT2
ISR(ASCLIN10TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(10U);
  #elif((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(10U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN10RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN10RX_EXIST == STD_ON)
#if((IRQ_ASCLIN10_RX_PRIO > 0) || (IRQ_ASCLIN10_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN10_RX_PRIO > 0) && (IRQ_ASCLIN10_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN10RX_ISR, 0, IRQ_ASCLIN10_RX_PRIO)
#elif IRQ_ASCLIN10_RX_CAT == IRQ_CAT2
ISR(ASCLIN10RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(10U);
  #elif((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(10U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN10ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN10ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN10_ERR_PRIO > 0) || (IRQ_ASCLIN10_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN10_ERR_PRIO > 0) && (IRQ_ASCLIN10_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN10ERR_ISR, 0, IRQ_ASCLIN10_ERR_PRIO)
#elif IRQ_ASCLIN10_ERR_CAT == IRQ_CAT2
ISR(ASCLIN10ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(10U);
  #elif((IRQ_ASCLIN_CHANNEL10_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(10U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN11TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN11TX_EXIST == STD_ON)
#if((IRQ_ASCLIN11_TX_PRIO > 0) || (IRQ_ASCLIN11_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN11_TX_PRIO > 0) && (IRQ_ASCLIN11_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN11TX_ISR, 0, IRQ_ASCLIN11_TX_PRIO)
#elif IRQ_ASCLIN11_TX_CAT == IRQ_CAT2
ISR(ASCLIN11TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(11U);
  #elif((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(11U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN11RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN11RX_EXIST == STD_ON)
#if((IRQ_ASCLIN11_RX_PRIO > 0) || (IRQ_ASCLIN11_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN11_RX_PRIO > 0) && (IRQ_ASCLIN11_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN11RX_ISR, 0, IRQ_ASCLIN11_RX_PRIO)
#elif IRQ_ASCLIN11_RX_CAT == IRQ_CAT2
ISR(ASCLIN11RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(11U);
  #elif((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(11U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN11ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN11ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN11_ERR_PRIO > 0) || (IRQ_ASCLIN11_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN11_ERR_PRIO > 0) && (IRQ_ASCLIN11_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN11ERR_ISR, 0, IRQ_ASCLIN11_ERR_PRIO)
#elif IRQ_ASCLIN11_ERR_CAT == IRQ_CAT2
ISR(ASCLIN11ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(11U);
  #elif((IRQ_ASCLIN_CHANNEL11_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(11U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN12TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN12TX_EXIST == STD_ON)
#if((IRQ_ASCLIN12_TX_PRIO > 0) || (IRQ_ASCLIN12_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN12_TX_PRIO > 0) && (IRQ_ASCLIN12_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN12TX_ISR, 0, IRQ_ASCLIN12_TX_PRIO)
#elif IRQ_ASCLIN12_TX_CAT == IRQ_CAT2
ISR(ASCLIN12TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(12U);
  #elif((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(12U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN12RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN12RX_EXIST == STD_ON)
#if((IRQ_ASCLIN12_RX_PRIO > 0) || (IRQ_ASCLIN12_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN12_RX_PRIO > 0) && (IRQ_ASCLIN12_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN12RX_ISR, 0, IRQ_ASCLIN12_RX_PRIO)
#elif IRQ_ASCLIN12_RX_CAT == IRQ_CAT2
ISR(ASCLIN12RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(12U);
  #elif((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(12U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN12ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN12ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN12_ERR_PRIO > 0) || (IRQ_ASCLIN12_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN12_ERR_PRIO > 0) && (IRQ_ASCLIN12_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN12ERR_ISR, 0, IRQ_ASCLIN12_ERR_PRIO)
#elif IRQ_ASCLIN12_ERR_CAT == IRQ_CAT2
ISR(ASCLIN12ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(12U);
  #elif((IRQ_ASCLIN_CHANNEL12_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(12U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN13TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN13TX_EXIST == STD_ON)
#if((IRQ_ASCLIN13_TX_PRIO > 0) || (IRQ_ASCLIN13_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN13_TX_PRIO > 0) && (IRQ_ASCLIN13_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN13TX_ISR, 0, IRQ_ASCLIN13_TX_PRIO)
#elif IRQ_ASCLIN13_TX_CAT == IRQ_CAT2
ISR(ASCLIN13TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(13U);
  #elif((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(13U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN13RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN13RX_EXIST == STD_ON)
#if((IRQ_ASCLIN13_RX_PRIO > 0) || (IRQ_ASCLIN13_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN13_RX_PRIO > 0) && (IRQ_ASCLIN13_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN13RX_ISR, 0, IRQ_ASCLIN13_RX_PRIO)
#elif IRQ_ASCLIN13_RX_CAT == IRQ_CAT2
ISR(ASCLIN13RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(13U);
  #elif((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(13U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN13ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN13ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN13_ERR_PRIO > 0) || (IRQ_ASCLIN13_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN13_ERR_PRIO > 0) && (IRQ_ASCLIN13_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN13ERR_ISR, 0, IRQ_ASCLIN13_ERR_PRIO)
#elif IRQ_ASCLIN13_ERR_CAT == IRQ_CAT2
ISR(ASCLIN13ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(13U);
  #elif((IRQ_ASCLIN_CHANNEL13_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(13U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN14TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN14TX_EXIST == STD_ON)
#if((IRQ_ASCLIN14_TX_PRIO > 0) || (IRQ_ASCLIN14_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN14_TX_PRIO > 0) && (IRQ_ASCLIN14_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN14TX_ISR, 0, IRQ_ASCLIN14_TX_PRIO)
#elif IRQ_ASCLIN14_TX_CAT == IRQ_CAT2
ISR(ASCLIN14TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(14U);
  #elif((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(14U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN14RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN14RX_EXIST == STD_ON)
#if((IRQ_ASCLIN14_RX_PRIO > 0) || (IRQ_ASCLIN14_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN14_RX_PRIO > 0) && (IRQ_ASCLIN14_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN14RX_ISR, 0, IRQ_ASCLIN14_RX_PRIO)
#elif IRQ_ASCLIN14_RX_CAT == IRQ_CAT2
ISR(ASCLIN14RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(14U);
  #elif((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(14U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN14ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN14ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN14_ERR_PRIO > 0) || (IRQ_ASCLIN14_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN14_ERR_PRIO > 0) && (IRQ_ASCLIN14_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN14ERR_ISR, 0, IRQ_ASCLIN14_ERR_PRIO)
#elif IRQ_ASCLIN14_ERR_CAT == IRQ_CAT2
ISR(ASCLIN14ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(14U);
  #elif((IRQ_ASCLIN_CHANNEL14_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(14U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN15TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN15TX_EXIST == STD_ON)
#if((IRQ_ASCLIN15_TX_PRIO > 0) || (IRQ_ASCLIN15_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN15_TX_PRIO > 0) && (IRQ_ASCLIN15_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN15TX_ISR, 0, IRQ_ASCLIN15_TX_PRIO)
#elif IRQ_ASCLIN15_TX_CAT == IRQ_CAT2
ISR(ASCLIN15TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(15U);
  #elif((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(15U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN15RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN15RX_EXIST == STD_ON)
#if((IRQ_ASCLIN15_RX_PRIO > 0) || (IRQ_ASCLIN15_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN15_RX_PRIO > 0) && (IRQ_ASCLIN15_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN15RX_ISR, 0, IRQ_ASCLIN15_RX_PRIO)
#elif IRQ_ASCLIN15_RX_CAT == IRQ_CAT2
ISR(ASCLIN15RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(15U);
  #elif((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(15U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN15ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN15ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN15_ERR_PRIO > 0) || (IRQ_ASCLIN15_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN15_ERR_PRIO > 0) && (IRQ_ASCLIN15_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN15ERR_ISR, 0, IRQ_ASCLIN15_ERR_PRIO)
#elif IRQ_ASCLIN15_ERR_CAT == IRQ_CAT2
ISR(ASCLIN15ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(15U);
  #elif((IRQ_ASCLIN_CHANNEL15_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(15U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN16TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN16TX_EXIST == STD_ON)
#if((IRQ_ASCLIN16_TX_PRIO > 0) || (IRQ_ASCLIN16_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN16_TX_PRIO > 0) && (IRQ_ASCLIN16_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN16TX_ISR, 0, IRQ_ASCLIN16_TX_PRIO)
#elif IRQ_ASCLIN16_TX_CAT == IRQ_CAT2
ISR(ASCLIN16TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(16U);
  #elif((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(16U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN16RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN16RX_EXIST == STD_ON)
#if((IRQ_ASCLIN16_RX_PRIO > 0) || (IRQ_ASCLIN16_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN16_RX_PRIO > 0) && (IRQ_ASCLIN16_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN16RX_ISR, 0, IRQ_ASCLIN16_RX_PRIO)
#elif IRQ_ASCLIN16_RX_CAT == IRQ_CAT2
ISR(ASCLIN16RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(16U);
  #elif((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(16U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN16ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN16ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN16_ERR_PRIO > 0) || (IRQ_ASCLIN16_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN16_ERR_PRIO > 0) && (IRQ_ASCLIN16_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN16ERR_ISR, 0, IRQ_ASCLIN16_ERR_PRIO)
#elif IRQ_ASCLIN16_ERR_CAT == IRQ_CAT2
ISR(ASCLIN16ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(16U);
  #elif((IRQ_ASCLIN_CHANNEL16_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(16U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN17TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN17TX_EXIST == STD_ON)
#if((IRQ_ASCLIN17_TX_PRIO > 0) || (IRQ_ASCLIN17_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN17_TX_PRIO > 0) && (IRQ_ASCLIN17_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN17TX_ISR, 0, IRQ_ASCLIN17_TX_PRIO)
#elif IRQ_ASCLIN17_TX_CAT == IRQ_CAT2
ISR(ASCLIN17TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(17U);
  #elif((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(17U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN17RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN17RX_EXIST == STD_ON)
#if((IRQ_ASCLIN17_RX_PRIO > 0) || (IRQ_ASCLIN17_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN17_RX_PRIO > 0) && (IRQ_ASCLIN17_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN17RX_ISR, 0, IRQ_ASCLIN17_RX_PRIO)
#elif IRQ_ASCLIN17_RX_CAT == IRQ_CAT2
ISR(ASCLIN17RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(17U);
  #elif((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(17U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN17ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN17ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN17_ERR_PRIO > 0) || (IRQ_ASCLIN17_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN17_ERR_PRIO > 0) && (IRQ_ASCLIN17_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN17ERR_ISR, 0, IRQ_ASCLIN17_ERR_PRIO)
#elif IRQ_ASCLIN17_ERR_CAT == IRQ_CAT2
ISR(ASCLIN17ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(17U);
  #elif((IRQ_ASCLIN_CHANNEL17_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(17U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN18TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN18TX_EXIST == STD_ON)
#if((IRQ_ASCLIN18_TX_PRIO > 0) || (IRQ_ASCLIN18_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN18_TX_PRIO > 0) && (IRQ_ASCLIN18_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN18TX_ISR, 0, IRQ_ASCLIN18_TX_PRIO)
#elif IRQ_ASCLIN18_TX_CAT == IRQ_CAT2
ISR(ASCLIN18TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(18U);
  #elif((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(18U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN18RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN18RX_EXIST == STD_ON)
#if((IRQ_ASCLIN18_RX_PRIO > 0) || (IRQ_ASCLIN18_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN18_RX_PRIO > 0) && (IRQ_ASCLIN18_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN18RX_ISR, 0, IRQ_ASCLIN18_RX_PRIO)
#elif IRQ_ASCLIN18_RX_CAT == IRQ_CAT2
ISR(ASCLIN18RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(18U);
  #elif((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(18U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN18ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN18ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN18_ERR_PRIO > 0) || (IRQ_ASCLIN18_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN18_ERR_PRIO > 0) && (IRQ_ASCLIN18_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN18ERR_ISR, 0, IRQ_ASCLIN18_ERR_PRIO)
#elif IRQ_ASCLIN18_ERR_CAT == IRQ_CAT2
ISR(ASCLIN18ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(18U);
  #elif((IRQ_ASCLIN_CHANNEL18_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(18U);
  #endif
}
#endif
#endif


/******************************************************************************
** Syntax :          void ASCLIN19TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN19TX_EXIST == STD_ON)
#if((IRQ_ASCLIN19_TX_PRIO > 0) || (IRQ_ASCLIN19_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN19_TX_PRIO > 0) && (IRQ_ASCLIN19_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN19TX_ISR, 0, IRQ_ASCLIN19_TX_PRIO)
#elif IRQ_ASCLIN19_TX_CAT == IRQ_CAT2
ISR(ASCLIN19TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(19U);
  #elif((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(19U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN19RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN19RX_EXIST == STD_ON)
#if((IRQ_ASCLIN19_RX_PRIO > 0) || (IRQ_ASCLIN19_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN19_RX_PRIO > 0) && (IRQ_ASCLIN19_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN19RX_ISR, 0, IRQ_ASCLIN19_RX_PRIO)
#elif IRQ_ASCLIN19_RX_CAT == IRQ_CAT2
ISR(ASCLIN19RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(19U);
  #elif((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(19U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN19ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN19ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN19_ERR_PRIO > 0) || (IRQ_ASCLIN19_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN19_ERR_PRIO > 0) && (IRQ_ASCLIN19_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN19ERR_ISR, 0, IRQ_ASCLIN19_ERR_PRIO)
#elif IRQ_ASCLIN19_ERR_CAT == IRQ_CAT2
ISR(ASCLIN19ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(19U);
  #elif((IRQ_ASCLIN_CHANNEL19_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(19U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN20TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN20TX_EXIST == STD_ON)
#if((IRQ_ASCLIN20_TX_PRIO > 0) || (IRQ_ASCLIN20_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN20_TX_PRIO > 0) && (IRQ_ASCLIN20_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN20TX_ISR, 0, IRQ_ASCLIN20_TX_PRIO)
#elif IRQ_ASCLIN20_TX_CAT == IRQ_CAT2
ISR(ASCLIN20TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(20U);
  #elif((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(20U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN20RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN20RX_EXIST == STD_ON)
#if((IRQ_ASCLIN20_RX_PRIO > 0) || (IRQ_ASCLIN20_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN20_RX_PRIO > 0) && (IRQ_ASCLIN20_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN20RX_ISR, 0, IRQ_ASCLIN20_RX_PRIO)
#elif IRQ_ASCLIN20_RX_CAT == IRQ_CAT2
ISR(ASCLIN20RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(20U);
  #elif((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(20U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN20ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN20ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN20_ERR_PRIO > 0) || (IRQ_ASCLIN20_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN20_ERR_PRIO > 0) && (IRQ_ASCLIN20_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN20ERR_ISR, 0, IRQ_ASCLIN20_ERR_PRIO)
#elif IRQ_ASCLIN20_ERR_CAT == IRQ_CAT2
ISR(ASCLIN20ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(20U);
  #elif((IRQ_ASCLIN_CHANNEL20_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(20U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN21TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN21TX_EXIST == STD_ON)
#if((IRQ_ASCLIN21_TX_PRIO > 0) || (IRQ_ASCLIN21_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN21_TX_PRIO > 0) && (IRQ_ASCLIN21_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN21TX_ISR, 0, IRQ_ASCLIN21_TX_PRIO)
#elif IRQ_ASCLIN21_TX_CAT == IRQ_CAT2
ISR(ASCLIN21TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(21U);
  #elif((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(21U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN21RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN21RX_EXIST == STD_ON)
#if((IRQ_ASCLIN21_RX_PRIO > 0) || (IRQ_ASCLIN21_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN21_RX_PRIO > 0) && (IRQ_ASCLIN21_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN21RX_ISR, 0, IRQ_ASCLIN21_RX_PRIO)
#elif IRQ_ASCLIN21_RX_CAT == IRQ_CAT2
ISR(ASCLIN21RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(21U);
  #elif((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(21U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ASCLIN21ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN21ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN21_ERR_PRIO > 0) || (IRQ_ASCLIN21_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN21_ERR_PRIO > 0) && (IRQ_ASCLIN21_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN21ERR_ISR, 0, IRQ_ASCLIN21_ERR_PRIO)
#elif IRQ_ASCLIN21_ERR_CAT == IRQ_CAT2
ISR(ASCLIN21ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(21U);
  #elif((IRQ_ASCLIN_CHANNEL21_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(21U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN22TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN22TX_EXIST == STD_ON)
#if((IRQ_ASCLIN22_TX_PRIO > 0) || (IRQ_ASCLIN22_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN22_TX_PRIO > 0) && (IRQ_ASCLIN22_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN22TX_ISR, 0, IRQ_ASCLIN22_TX_PRIO)
#elif IRQ_ASCLIN22_TX_CAT == IRQ_CAT2
ISR(ASCLIN22TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(22U);
  #elif((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(22U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN22RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN22RX_EXIST == STD_ON)
#if((IRQ_ASCLIN22_RX_PRIO > 0) || (IRQ_ASCLIN22_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN22_RX_PRIO > 0) && (IRQ_ASCLIN22_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN22RX_ISR, 0, IRQ_ASCLIN22_RX_PRIO)
#elif IRQ_ASCLIN22_RX_CAT == IRQ_CAT2
ISR(ASCLIN22RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(22U);
  #elif((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(22U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN22ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN22ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN22_ERR_PRIO > 0) || (IRQ_ASCLIN22_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN22_ERR_PRIO > 0) && (IRQ_ASCLIN22_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN22ERR_ISR, 0, IRQ_ASCLIN22_ERR_PRIO)
#elif IRQ_ASCLIN22_ERR_CAT == IRQ_CAT2
ISR(ASCLIN22ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(22U);
  #elif((IRQ_ASCLIN_CHANNEL22_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(22U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN23TX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission complete                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN23TX_EXIST == STD_ON)
#if((IRQ_ASCLIN23_TX_PRIO > 0) || (IRQ_ASCLIN23_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN23_TX_PRIO > 0) && (IRQ_ASCLIN23_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN23TX_ISR, 0, IRQ_ASCLIN23_TX_PRIO)
#elif IRQ_ASCLIN23_TX_CAT == IRQ_CAT2
ISR(ASCLIN23TX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_TX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrTransmit(23U);
  #elif((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrTransmit(23U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN23RX_ISR(void)                               **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN reception complete                    **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN23RX_EXIST == STD_ON)
#if((IRQ_ASCLIN23_RX_PRIO > 0) || (IRQ_ASCLIN23_RX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN23_RX_PRIO > 0) && (IRQ_ASCLIN23_RX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN23RX_ISR, 0, IRQ_ASCLIN23_RX_PRIO)
#elif IRQ_ASCLIN23_RX_CAT == IRQ_CAT2
ISR(ASCLIN23RX_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && (UART_RX_MODE != UART_POLLING_MODE))
  /* Call Uart Interrupt function*/
  Uart_IsrReceive(23U);
  #elif((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrReceive(23U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ASCLIN23ERR_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on ASCLIN transmission or reception error       **
**                   and wake up interrupt service request                   **
**                                                                           **
******************************************************************************/
#if (IRQ_ASCLIN23ERR_EXIST == STD_ON)
#if((IRQ_ASCLIN23_ERR_PRIO > 0) || (IRQ_ASCLIN23_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN23_ERR_PRIO > 0) && (IRQ_ASCLIN23_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN23ERR_ISR, 0, IRQ_ASCLIN23_ERR_PRIO)
#elif IRQ_ASCLIN23_ERR_CAT == IRQ_CAT2
ISR(ASCLIN23ERR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  #if((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_UART_DRIVER) && ((UART_TX_MODE != UART_POLLING_MODE) || (UART_RX_MODE != UART_POLLING_MODE)))
  /* Call Uart Interrupt function*/
  Uart_IsrError(23U);
  #elif((IRQ_ASCLIN_CHANNEL23_USED==IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER) && (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON))
  /* Call Lin Interrupt function*/
  Lin_17_AscLin_IsrError(23U);
  #endif
}
#endif
#endif
