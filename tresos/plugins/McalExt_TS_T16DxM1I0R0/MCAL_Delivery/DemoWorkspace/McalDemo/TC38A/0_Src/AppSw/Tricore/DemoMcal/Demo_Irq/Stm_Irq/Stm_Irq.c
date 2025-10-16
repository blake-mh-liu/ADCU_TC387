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
**  FILENAME  : Stm_Irq.c                                                     **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-12                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames                     **
*                 for the WDG/STM Module.                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Watchdog Driver, AUTOSAR Release 4.2.2**
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
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
#include "Mcu_17_TimerIp.h"

/*Module configuration */
#include "Wdg_17_Scu.h"
#include "Wdg_17_Scu_Cbk.h"

/* Global functions like Enable/Disable interrupts */
#include "McalLib.h"
#include "Irq.h"
#include "IFX_Os.h"

/* Inclusion of controller sfr file */
#include "IfxStm_reg.h"
#include "IfxSrc_reg.h"


/* Include STM IRQ header file  */
#include "Stm_Irq.h"
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


/******************************************************************************
** Syntax :          void STM0SR0_ISR(void)                                  **
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
** Description :     Service on STM0 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM0SR0_EXIST == STD_ON)
#if((IRQ_STM0_SR0_PRIO > 0) || (IRQ_STM0_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM0_SR0_PRIO > 0) && (IRQ_STM0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM0SR0_ISR, 0, IRQ_STM0_SR0_PRIO)
#elif (IRQ_STM0_SR0_CAT == IRQ_CAT2)
ISR(STM0SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) 
    /* Call Wdg periodic processing function */
    Mcu_17_Stm_CompareMatchIsr(0U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void STM0SR1_ISR(void)                                  **
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
** Description :     Service on STM0 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM0SR1_EXIST == STD_ON)
#if((IRQ_STM0_SR1_PRIO > 0) || (IRQ_STM0_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM0_SR1_PRIO > 0) && (IRQ_STM0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM0SR1_ISR, 0, IRQ_STM0_SR1_PRIO)
#elif (IRQ_STM0_SR1_CAT == IRQ_CAT2)
ISR(STM0SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
 
  Mcu_17_Stm_CompareMatchIsr(0U, 1U);

}
#endif
#endif



/******************************************************************************
** Syntax :          void STM1SR0_ISR(void)                                  **
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
** Description :     Service on STM1 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM1SR0_EXIST == STD_ON)
#if((IRQ_STM1_SR0_PRIO > 0) || (IRQ_STM1_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM1_SR0_PRIO > 0) && (IRQ_STM1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM1SR0_ISR, 0, IRQ_STM1_SR0_PRIO)
#elif (IRQ_STM1_SR0_CAT == IRQ_CAT2)
ISR(STM1SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER))
    Mcu_17_Stm_CompareMatchIsr(1U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM1SR1_ISR(void)                                  **
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
** Description :     Service on STM1 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM1SR1_EXIST == STD_ON)
#if((IRQ_STM1_SR1_PRIO > 0) || (IRQ_STM1_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM1_SR1_PRIO > 0) && (IRQ_STM1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM1SR1_ISR, 0, IRQ_STM1_SR1_PRIO)
#elif (IRQ_STM1_SR1_CAT == IRQ_CAT2)
ISR(STM1SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Mcu_17_Stm_CompareMatchIsr(1U, 1U);

}
#endif
#endif



/******************************************************************************
** Syntax :          void STM2SR0_ISR(void)                                  **
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
** Description :     Service on STM2 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM2SR0_EXIST == STD_ON)
#if((IRQ_STM2_SR0_PRIO > 0) || (IRQ_STM2_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM2_SR0_PRIO > 0) && (IRQ_STM2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM2SR0_ISR, 0, IRQ_STM2_SR0_PRIO)
#elif (IRQ_STM2_SR0_CAT == IRQ_CAT2)
ISR(STM2SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER))  
    Mcu_17_Stm_CompareMatchIsr(2U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM2SR1_ISR(void)                                  **
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
** Description :     Service on STM2 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM2SR1_EXIST == STD_ON)
#if((IRQ_STM2_SR1_PRIO > 0) || (IRQ_STM2_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM2_SR1_PRIO > 0) && (IRQ_STM2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM2SR1_ISR, 0, IRQ_STM2_SR1_PRIO)
#elif (IRQ_STM2_SR1_CAT == IRQ_CAT2)
ISR(STM2SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  Mcu_17_Stm_CompareMatchIsr(2U, 1U);

}
#endif
#endif



/******************************************************************************
** Syntax :          void STM3SR0_ISR(void)                                  **
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
** Description :     Service on STM3 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM3SR0_EXIST == STD_ON)
#if((IRQ_STM3_SR0_PRIO > 0) || (IRQ_STM3_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM3_SR0_PRIO > 0) && (IRQ_STM3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM3SR0_ISR, 0, IRQ_STM3_SR0_PRIO)
#elif (IRQ_STM3_SR0_CAT == IRQ_CAT2)
ISR(STM3SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER))
    Mcu_17_Stm_CompareMatchIsr(3U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM3SR1_ISR(void)                                  **
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
** Description :     Service on STM3 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM3SR1_EXIST == STD_ON)
#if((IRQ_STM3_SR1_PRIO > 0) || (IRQ_STM3_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM3_SR1_PRIO > 0) && (IRQ_STM3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM3SR1_ISR, 0, IRQ_STM3_SR1_PRIO)
#elif (IRQ_STM3_SR1_CAT == IRQ_CAT2)
ISR(STM3SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
 
  Mcu_17_Stm_CompareMatchIsr(3U, 1U);

}
#endif
#endif



/******************************************************************************
** Syntax :          void STM4SR0_ISR(void)                                  **
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
** Description :     Service on STM4 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM4SR0_EXIST == STD_ON)
#if((IRQ_STM4_SR0_PRIO > 0) || (IRQ_STM4_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM4_SR0_PRIO > 0) && (IRQ_STM4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM4SR0_ISR, 0, IRQ_STM4_SR0_PRIO)
#elif (IRQ_STM4_SR0_CAT == IRQ_CAT2)
ISR(STM4SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER))
    Mcu_17_Stm_CompareMatchIsr(4U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM4SR1_ISR(void)                                  **
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
** Description :     Service on STM4 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM4SR1_EXIST == STD_ON)
#if((IRQ_STM4_SR1_PRIO > 0) || (IRQ_STM4_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM4_SR1_PRIO > 0) && (IRQ_STM4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM4SR1_ISR, 0, IRQ_STM4_SR1_PRIO)
#elif (IRQ_STM4_SR1_CAT == IRQ_CAT2)
ISR(STM4SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  Mcu_17_Stm_CompareMatchIsr(4U, 1U);
}
#endif
#endif



/******************************************************************************
** Syntax :          void STM5SR0_ISR(void)                                  **
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
** Description :     Service on STM5 match interrupt                         **
**                                                                           **
******************************************************************************/
#if(IRQ_STM5SR0_EXIST == STD_ON)
#if((IRQ_STM5_SR0_PRIO > 0) || (IRQ_STM5_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM5_SR0_PRIO > 0) && (IRQ_STM5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM5SR0_ISR, 0, IRQ_STM5_SR0_PRIO)
#elif (IRQ_STM5_SR0_CAT == IRQ_CAT2)
ISR(STM5SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER))&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER))
    Mcu_17_Stm_CompareMatchIsr(5U, 0U);
    *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM5SR1_ISR(void)                                  **
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
** Description :     Service on STM5 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if(IRQ_STM5SR1_EXIST == STD_ON)
#if((IRQ_STM5_SR1_PRIO > 0) || (IRQ_STM5_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM5_SR1_PRIO > 0) && (IRQ_STM5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM5SR1_ISR, 0, IRQ_STM5_SR1_PRIO)
#elif (IRQ_STM5_SR1_CAT == IRQ_CAT2)
ISR(STM5SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* ENABLE(); */
  Mcu_17_Stm_CompareMatchIsr(5U, 1U);
}
#endif
#endif
