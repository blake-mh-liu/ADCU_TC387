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
**  FILENAME     : Eru_Irq.c                                                  **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains the interrupt frames for the ERU.       **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
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

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */

#include "McalLib.h"
#include "MCAL_Compiler.h"
#include "Mcu_17_TimerIp.h"
#include "IFX_Os.h"
#include "Eru_Irq.h"

/* MCAL driver utility functions for setting interrupt priority initialization
  and interrupt category */
#include "Irq.h"

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
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

/*******************************************************************************
** Syntax:           void ERU_ISR_SRN00(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request nodes 1 for the  ERU.  **
*******************************************************************************/
#if (IRQ_SCUERUSR0_EXIST == STD_ON)
#if((IRQ_SCU_ERU_SR0_PRIO > 0) || (IRQ_SCU_ERU_SR0_CAT == IRQ_CAT2))
#if((IRQ_SCU_ERU_SR0_PRIO > 0) && (IRQ_SCU_ERU_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(SCUERUSR0_ISR, 0, IRQ_SCU_ERU_SR0_PRIO)
#elif IRQ_SCU_ERU_SR0_CAT == IRQ_CAT2
ISR(SCUERUSR0_ISR)
#endif
{
  /* Enable Global Interrupts */
	 /* ENABLE(); */
  /* Call Mcu Interrupt funtion */
  Mcu_17_Eru_GatingIsr(0);

}
#endif
#endif

#if (IRQ_SCUERUSR1_EXIST == STD_ON)
#if((IRQ_SCU_ERU_SR1_PRIO > 0) || (IRQ_SCU_ERU_SR1_CAT == IRQ_CAT2))
#if((IRQ_SCU_ERU_SR1_PRIO > 0) && (IRQ_SCU_ERU_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(SCUERUSR1_ISR, 0, IRQ_SCU_ERU_SR1_PRIO)
#elif IRQ_SCU_ERU_SR1_CAT == IRQ_CAT2
ISR(SCUERUSR1_ISR)
#endif
{
  /* Enable Global Interrupts */
	/* ENABLE(); */
  /* Call Mcu Interrupt funtion */
  Mcu_17_Eru_GatingIsr(1);
}
#endif
#endif

#if (IRQ_SCUERUSR2_EXIST == STD_ON)
#if((IRQ_SCU_ERU_SR2_PRIO > 0) || (IRQ_SCU_ERU_SR2_CAT == IRQ_CAT2))
#if((IRQ_SCU_ERU_SR2_PRIO > 0) && (IRQ_SCU_ERU_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(SCUERUSR2_ISR, 0, IRQ_SCU_ERU_SR2_PRIO)
#elif IRQ_SCU_ERU_SR2_CAT == IRQ_CAT2
ISR(SCUERUSR2_ISR)
#endif
{
  /* Enable Global Interrupts */
	/* ENABLE(); */
  /* Call Mcu Interrupt funtion */
  Mcu_17_Eru_GatingIsr(2);
}
#endif
#endif

#if (IRQ_SCUERUSR3_EXIST == STD_ON)
#if((IRQ_SCU_ERU_SR3_PRIO > 0) || (IRQ_SCU_ERU_SR3_CAT == IRQ_CAT2))
#if((IRQ_SCU_ERU_SR3_PRIO > 0) && (IRQ_SCU_ERU_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(SCUERUSR3_ISR, 0, IRQ_SCU_ERU_SR3_PRIO)
#elif IRQ_SCU_ERU_SR3_CAT == IRQ_CAT2
ISR(SCUERUSR3_ISR)
#endif
{
  /* Enable Global Interrupts */
	/* ENABLE(); */
  /* Call Mcu Interrupt funtion */
  Mcu_17_Eru_GatingIsr(3);
}
#endif
#endif
