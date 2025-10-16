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
**  FILENAME  : Eth_17_GEthMacV2_Irq.c                                        **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-09                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames for the ETH Module. **
**                                                                            **
**  SPECIFICATION(S) : Specification of ETH Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                             **
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
/* Include Eth header file Eth.h */
#include "Eth_17_GEthMacV2.h"
/*Include Irq Module*/
#include "Irq.h"
#include "Eth_17_GEthMacV2_Irq.h"

#include "IFX_Os.h"

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
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
#if (IRQ_ETHSR2_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR2_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 0 Channel-0 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR2_PRIO > 0) || (IRQ_GETH_SR2_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR2_PRIO > 0) && (IRQ_GETH_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR2_ISR, 0, IRQ_GETH_SR2_PRIO)
#elif IRQ_GETH_SR2_CAT == IRQ_CAT2
ISR(ETHSR2_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(0,0);
}
#endif
#endif

#if (IRQ_ETHSR3_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR3_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 0 Channel-1 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR3_PRIO > 0) || (IRQ_GETH_SR3_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR3_PRIO > 0) && (IRQ_GETH_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR3_ISR, 0, IRQ_GETH_SR3_PRIO)
#elif IRQ_GETH_SR3_CAT == IRQ_CAT2
ISR(ETHSR3_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(0,1);
}
#endif
#endif

#if (IRQ_ETHSR4_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR4_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 0 Channel-2 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR4_PRIO > 0) || (IRQ_GETH_SR4_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR4_PRIO > 0) && (IRQ_GETH_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR4_ISR, 0, IRQ_GETH_SR4_PRIO)
#elif IRQ_GETH_SR4_CAT == IRQ_CAT2
ISR(ETHSR4_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(0,2);
}
#endif
#endif

#if (IRQ_ETHSR5_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR5_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 0 Channel-1 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR5_PRIO > 0) || (IRQ_GETH_SR5_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR5_PRIO > 0) && (IRQ_GETH_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR5_ISR, 0, IRQ_GETH_SR5_PRIO)
#elif IRQ_GETH_SR5_CAT == IRQ_CAT2
ISR(ETHSR5_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(0,3);
}
#endif
#endif

#if (IRQ_ETHSR6_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR6_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 0 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR6_PRIO > 0) || (IRQ_GETH_SR6_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR6_PRIO > 0) && (IRQ_GETH_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR6_ISR, 0, IRQ_GETH_SR6_PRIO)
#elif IRQ_GETH_SR6_CAT == IRQ_CAT2
ISR(ETHSR6_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(0,0);
}
#endif
#endif

#if (IRQ_ETHSR7_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR7_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 0 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR7_PRIO > 0) || (IRQ_GETH_SR7_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR7_PRIO > 0) && (IRQ_GETH_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR7_ISR, 0, IRQ_GETH_SR7_PRIO)
#elif IRQ_GETH_SR7_CAT == IRQ_CAT2
ISR(ETHSR7_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(0,1);
}
#endif
#endif

#if (IRQ_ETHSR8_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR8_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 0 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR8_PRIO > 0) || (IRQ_GETH_SR8_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR8_PRIO > 0) && (IRQ_GETH_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR8_ISR, 0, IRQ_GETH_SR8_PRIO)
#elif IRQ_GETH_SR8_CAT == IRQ_CAT2
ISR(ETHSR8_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(0,2);
}
#endif
#endif

#if (IRQ_ETHSR9_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR9_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 0 Channel-3 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR9_PRIO > 0) || (IRQ_GETH_SR9_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR9_PRIO > 0) && (IRQ_GETH_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR9_ISR, 0, IRQ_GETH_SR9_PRIO)
#elif IRQ_GETH_SR9_CAT == IRQ_CAT2
ISR(ETHSR9_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(0,3);
}
#endif
#endif

#if (IRQ_ETHSR12_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR2_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 1 Channel-0 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR2_PRIO > 0) || (IRQ_GETH1_SR2_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR2_PRIO > 0) && (IRQ_GETH1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR12_ISR, 0, IRQ_GETH1_SR2_PRIO)
#elif IRQ_GETH1_SR2_CAT == IRQ_CAT2
ISR(ETHSR12_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(1,0);
}
#endif
#endif 

#if (IRQ_ETHSR13_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR3_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 1 Channel-1 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR3_PRIO > 0) || (IRQ_GETH1_SR3_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR3_PRIO > 0) && (IRQ_GETH1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR13_ISR, 0, IRQ_GETH1_SR3_PRIO)
#elif IRQ_GETH1_SR3_CAT == IRQ_CAT2
ISR(ETHSR13_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(1,1);
}
#endif
#endif 

#if (IRQ_ETHSR14_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR4_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 1 Channel-0 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR4_PRIO > 0) || (IRQ_GETH1_SR4_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR4_PRIO > 0) && (IRQ_GETH1_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR14_ISR, 0, IRQ_GETH1_SR4_PRIO)
#elif IRQ_GETH1_SR4_CAT == IRQ_CAT2
ISR(ETHSR14_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(1,2);
}
#endif
#endif

#if (IRQ_ETHSR15_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR5_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 1 Channel-3 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR5_PRIO > 0) || (IRQ_GETH1_SR5_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR5_PRIO > 0) && (IRQ_GETH1_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR15_ISR, 0, IRQ_GETH1_SR5_PRIO)
#elif IRQ_GETH1_SR5_CAT == IRQ_CAT2
ISR(ETHSR15_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_TxDmaIrqHdlr(1,3);
}
#endif
#endif

#if (IRQ_ETHSR16_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR6_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 1 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR6_PRIO > 0) || (IRQ_GETH1_SR6_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR6_PRIO > 0) && (IRQ_GETH1_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR16_ISR, 0, IRQ_GETH1_SR6_PRIO)
#elif IRQ_GETH1_SR6_CAT == IRQ_CAT2
ISR(ETHSR16_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(1,0);
}
#endif
#endif

#if (IRQ_ETHSR17_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR7_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 1 Channel-1 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR7_PRIO > 0) || (IRQ_GETH1_SR7_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR7_PRIO > 0) && (IRQ_GETH1_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR17_ISR, 0, IRQ_GETH1_SR7_PRIO)
#elif IRQ_GETH1_SR7_CAT == IRQ_CAT2
ISR(ETHSR17_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(1,1);
}
#endif
#endif

#if (IRQ_ETHSR18_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR8_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 1 Channel-2 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR8_PRIO > 0) || (IRQ_GETH1_SR8_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR8_PRIO > 0) && (IRQ_GETH1_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR18_ISR, 0, IRQ_GETH1_SR8_PRIO)
#elif IRQ_GETH1_SR8_CAT == IRQ_CAT2
ISR(ETHSR18_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(1,2);
}
#endif
#endif

#if (IRQ_ETHSR19_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR9_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 1 Channel-3 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR9_PRIO > 0) || (IRQ_GETH1_SR9_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR9_PRIO > 0) && (IRQ_GETH1_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR19_ISR, 0, IRQ_GETH1_SR9_PRIO)
#elif IRQ_GETH1_SR9_CAT == IRQ_CAT2
ISR(ETHSR19_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE();*/
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMacV2_RxDmaIrqHdlr(1,3);
}
#endif
#endif
