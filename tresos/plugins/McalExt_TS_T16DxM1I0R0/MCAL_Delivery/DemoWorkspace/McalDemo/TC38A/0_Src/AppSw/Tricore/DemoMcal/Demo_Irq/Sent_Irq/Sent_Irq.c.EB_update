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
**  FILENAME     : Sent_Irq.c                                                 **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames for the SENT. This  **
**                file is given for evaluation purpose only.                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
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

/* Inclusion of Tasking sfr file */

/*Include Irq Module*/
#include "Irq.h"

/* Include Mcal.h to import the library functions */
/*#include "Mcal.h"*/
#include "IFX_Os.h"
/* Include SENT header file  */
#include "Sent.h"

/* Include SENT IRQ header file  */
#include "Sent_Irq.h"
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



/******************************************************************************
** Syntax : void SENTSR0_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 0                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR0_EXIST == STD_ON)
#if((IRQ_SENT_SR0_PRIO > 0) || (IRQ_SENT_SR0_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR0_PRIO > 0) && (IRQ_SENT_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR0_ISR, 0, IRQ_SENT_SR0_PRIO)
#elif IRQ_SENT_SR0_CAT == IRQ_CAT2
ISR(SENTSR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(0);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR1_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 1                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR1_EXIST == STD_ON)
#if((IRQ_SENT_SR1_PRIO > 0) || (IRQ_SENT_SR1_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR1_PRIO > 0) && (IRQ_SENT_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR1_ISR, 0, IRQ_SENT_SR1_PRIO)
#elif IRQ_SENT_SR1_CAT == IRQ_CAT2
ISR(SENTSR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(1);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR2_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 2                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR2_EXIST == STD_ON)
#if((IRQ_SENT_SR2_PRIO > 0) || (IRQ_SENT_SR2_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR2_PRIO > 0) && (IRQ_SENT_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR2_ISR, 0, IRQ_SENT_SR2_PRIO)
#elif IRQ_SENT_SR2_CAT == IRQ_CAT2
ISR(SENTSR2_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(2);
}
#endif
#endif
/******************************************************************************
** Syntax : void SENTSR3_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 3                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR3_EXIST == STD_ON)
#if((IRQ_SENT_SR3_PRIO > 0) || (IRQ_SENT_SR3_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR3_PRIO > 0) && (IRQ_SENT_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR3_ISR, 0, IRQ_SENT_SR3_PRIO)
#elif IRQ_SENT_SR3_CAT == IRQ_CAT2
ISR(SENTSR3_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(3);
}
#endif
#endif
/******************************************************************************
** Syntax : void SENTSR4_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 4                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR4_EXIST == STD_ON)
#if((IRQ_SENT_SR4_PRIO > 0) || (IRQ_SENT_SR4_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR4_PRIO > 0) && (IRQ_SENT_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR4_ISR, 0, IRQ_SENT_SR4_PRIO)
#elif IRQ_SENT_SR4_CAT == IRQ_CAT2
ISR(SENTSR4_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(4);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR5_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 5                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR5_EXIST == STD_ON)
#if((IRQ_SENT_SR5_PRIO > 0) || (IRQ_SENT_SR5_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR5_PRIO > 0) && (IRQ_SENT_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR5_ISR, 0, IRQ_SENT_SR5_PRIO)
#elif IRQ_SENT_SR5_CAT == IRQ_CAT2
ISR(SENTSR5_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(5);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR6_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 6                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR6_EXIST == STD_ON)
#if((IRQ_SENT_SR6_PRIO > 0) || (IRQ_SENT_SR6_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR6_PRIO > 0) && (IRQ_SENT_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR6_ISR, 0, IRQ_SENT_SR6_PRIO)
#elif IRQ_SENT_SR6_CAT == IRQ_CAT2
ISR(SENTSR6_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(6);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR7_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 7                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR7_EXIST == STD_ON)
#if((IRQ_SENT_SR7_PRIO > 0) || (IRQ_SENT_SR7_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR7_PRIO > 0) && (IRQ_SENT_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR7_ISR, 0, IRQ_SENT_SR7_PRIO)
#elif IRQ_SENT_SR7_CAT == IRQ_CAT2
ISR(SENTSR7_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(7);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR8_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 8                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR8_EXIST == STD_ON)
#if((IRQ_SENT_SR8_PRIO > 0) || (IRQ_SENT_SR8_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR8_PRIO > 0) && (IRQ_SENT_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR8_ISR, 0, IRQ_SENT_SR8_PRIO)
#elif IRQ_SENT_SR8_CAT == IRQ_CAT2
ISR(SENTSR8_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(8);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR9_ISR(void)                                           **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 9                           **
**                                                                           **
******************************************************************************/
#if(IRQ_SENTSR9_EXIST == STD_ON)
#if((IRQ_SENT_SR9_PRIO > 0) || (IRQ_SENT_SR9_CAT == IRQ_CAT2))
#if((IRQ_SENT_SR9_PRIO > 0) && (IRQ_SENT_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR9_ISR, 0, IRQ_SENT_SR9_PRIO)
#elif IRQ_SENT_SR9_CAT == IRQ_CAT2
ISR(SENTSR9_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Sent_Isr(9);
}
#endif
#endif
