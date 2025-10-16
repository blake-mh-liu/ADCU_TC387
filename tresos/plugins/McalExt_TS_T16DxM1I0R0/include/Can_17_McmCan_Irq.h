
#ifndef CAN_17_MCMCAN_IRQ_H
#define CAN_17_MCMCAN_IRQ_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "Std_Types.h"                                                        

#ifdef MCALEXT_IRQ_USE_OS                                                           
#include <Os.h>        /* OS interrupt services */                              
#endif


/*******************************************************************************
**                      Public Macro Definitions                              **
*******************************************************************************/

/************************* interrupt CATEGORY *********************************/

#ifdef IRQ_CAT1
#if (IRQ_CAT1 != 1)
#error IRQ_CAT1 already defined with a wrong value
#endif
#else
#define IRQ_CAT1                    (1)
#endif

#ifdef IRQ_CAT2
#if (IRQ_CAT2 != 2)
#error IRQ_CAT2 already defined with a wrong value
#endif
#else
#define IRQ_CAT2                    (2)
#endif



/* The name of the ISRs shall be the same name than the ISR       *
 * functions provided by Infineon                                 */

/**********************************************************/          

/******************CAN0SR0 IRQ ********************************/

#ifdef CAN0SR0_ISR
#define IRQ_CAN0SR0_EXIST  STD_ON
#define IRQ_CAN0_SR0_PRIO    CAN0SR0_ISR_ISR_LEVEL
#define IRQ_CAN0_SR0_CAT     CAN0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR0_EXIST  STD_OFF
#endif

/******************CAN0SR1 IRQ ********************************/

#ifdef CAN0SR1_ISR
#define IRQ_CAN0SR1_EXIST  STD_ON
#define IRQ_CAN0_SR1_PRIO    CAN0SR1_ISR_ISR_LEVEL
#define IRQ_CAN0_SR1_CAT     CAN0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR1_EXIST  STD_OFF
#endif

/******************CAN0SR10 IRQ ********************************/

#ifdef CAN0SR10_ISR
#define IRQ_CAN0SR10_EXIST  STD_ON
#define IRQ_CAN0_SR10_PRIO    CAN0SR10_ISR_ISR_LEVEL
#define IRQ_CAN0_SR10_CAT     CAN0SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR10_EXIST  STD_OFF
#endif

/******************CAN0SR11 IRQ ********************************/

#ifdef CAN0SR11_ISR
#define IRQ_CAN0SR11_EXIST  STD_ON
#define IRQ_CAN0_SR11_PRIO    CAN0SR11_ISR_ISR_LEVEL
#define IRQ_CAN0_SR11_CAT     CAN0SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR11_EXIST  STD_OFF
#endif

/******************CAN0SR12 IRQ ********************************/

#ifdef CAN0SR12_ISR
#define IRQ_CAN0SR12_EXIST  STD_ON
#define IRQ_CAN0_SR12_PRIO    CAN0SR12_ISR_ISR_LEVEL
#define IRQ_CAN0_SR12_CAT     CAN0SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR12_EXIST  STD_OFF
#endif

/******************CAN0SR13 IRQ ********************************/

#ifdef CAN0SR13_ISR
#define IRQ_CAN0SR13_EXIST  STD_ON
#define IRQ_CAN0_SR13_PRIO    CAN0SR13_ISR_ISR_LEVEL
#define IRQ_CAN0_SR13_CAT     CAN0SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR13_EXIST  STD_OFF
#endif

/******************CAN0SR14 IRQ ********************************/

#ifdef CAN0SR14_ISR
#define IRQ_CAN0SR14_EXIST  STD_ON
#define IRQ_CAN0_SR14_PRIO    CAN0SR14_ISR_ISR_LEVEL
#define IRQ_CAN0_SR14_CAT     CAN0SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR14_EXIST  STD_OFF
#endif

/******************CAN0SR15 IRQ ********************************/

#ifdef CAN0SR15_ISR
#define IRQ_CAN0SR15_EXIST  STD_ON
#define IRQ_CAN0_SR15_PRIO    CAN0SR15_ISR_ISR_LEVEL
#define IRQ_CAN0_SR15_CAT     CAN0SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR15_EXIST  STD_OFF
#endif

/******************CAN0SR2 IRQ ********************************/

#ifdef CAN0SR2_ISR
#define IRQ_CAN0SR2_EXIST  STD_ON
#define IRQ_CAN0_SR2_PRIO    CAN0SR2_ISR_ISR_LEVEL
#define IRQ_CAN0_SR2_CAT     CAN0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR2_EXIST  STD_OFF
#endif

/******************CAN0SR3 IRQ ********************************/

#ifdef CAN0SR3_ISR
#define IRQ_CAN0SR3_EXIST  STD_ON
#define IRQ_CAN0_SR3_PRIO    CAN0SR3_ISR_ISR_LEVEL
#define IRQ_CAN0_SR3_CAT     CAN0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR3_EXIST  STD_OFF
#endif

/******************CAN0SR4 IRQ ********************************/

#ifdef CAN0SR4_ISR
#define IRQ_CAN0SR4_EXIST  STD_ON
#define IRQ_CAN0_SR4_PRIO    CAN0SR4_ISR_ISR_LEVEL
#define IRQ_CAN0_SR4_CAT     CAN0SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR4_EXIST  STD_OFF
#endif

/******************CAN0SR5 IRQ ********************************/

#ifdef CAN0SR5_ISR
#define IRQ_CAN0SR5_EXIST  STD_ON
#define IRQ_CAN0_SR5_PRIO    CAN0SR5_ISR_ISR_LEVEL
#define IRQ_CAN0_SR5_CAT     CAN0SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR5_EXIST  STD_OFF
#endif

/******************CAN0SR6 IRQ ********************************/

#ifdef CAN0SR6_ISR
#define IRQ_CAN0SR6_EXIST  STD_ON
#define IRQ_CAN0_SR6_PRIO    CAN0SR6_ISR_ISR_LEVEL
#define IRQ_CAN0_SR6_CAT     CAN0SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR6_EXIST  STD_OFF
#endif

/******************CAN0SR7 IRQ ********************************/

#ifdef CAN0SR7_ISR
#define IRQ_CAN0SR7_EXIST  STD_ON
#define IRQ_CAN0_SR7_PRIO    CAN0SR7_ISR_ISR_LEVEL
#define IRQ_CAN0_SR7_CAT     CAN0SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR7_EXIST  STD_OFF
#endif

/******************CAN0SR8 IRQ ********************************/

#ifdef CAN0SR8_ISR
#define IRQ_CAN0SR8_EXIST  STD_ON
#define IRQ_CAN0_SR8_PRIO    CAN0SR8_ISR_ISR_LEVEL
#define IRQ_CAN0_SR8_CAT     CAN0SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR8_EXIST  STD_OFF
#endif

/******************CAN0SR9 IRQ ********************************/

#ifdef CAN0SR9_ISR
#define IRQ_CAN0SR9_EXIST  STD_ON
#define IRQ_CAN0_SR9_PRIO    CAN0SR9_ISR_ISR_LEVEL
#define IRQ_CAN0_SR9_CAT     CAN0SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR9_EXIST  STD_OFF
#endif

/******************CAN1SR0 IRQ ********************************/

#ifdef CAN1SR0_ISR
#define IRQ_CAN1SR0_EXIST  STD_ON
#define IRQ_CAN1_SR0_PRIO    CAN1SR0_ISR_ISR_LEVEL
#define IRQ_CAN1_SR0_CAT     CAN1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR0_EXIST  STD_OFF
#endif

/******************CAN1SR1 IRQ ********************************/

#ifdef CAN1SR1_ISR
#define IRQ_CAN1SR1_EXIST  STD_ON
#define IRQ_CAN1_SR1_PRIO    CAN1SR1_ISR_ISR_LEVEL
#define IRQ_CAN1_SR1_CAT     CAN1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR1_EXIST  STD_OFF
#endif

/******************CAN1SR10 IRQ ********************************/

#ifdef CAN1SR10_ISR
#define IRQ_CAN1SR10_EXIST  STD_ON
#define IRQ_CAN1_SR10_PRIO    CAN1SR10_ISR_ISR_LEVEL
#define IRQ_CAN1_SR10_CAT     CAN1SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR10_EXIST  STD_OFF
#endif

/******************CAN1SR11 IRQ ********************************/

#ifdef CAN1SR11_ISR
#define IRQ_CAN1SR11_EXIST  STD_ON
#define IRQ_CAN1_SR11_PRIO    CAN1SR11_ISR_ISR_LEVEL
#define IRQ_CAN1_SR11_CAT     CAN1SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR11_EXIST  STD_OFF
#endif

/******************CAN1SR12 IRQ ********************************/

#ifdef CAN1SR12_ISR
#define IRQ_CAN1SR12_EXIST  STD_ON
#define IRQ_CAN1_SR12_PRIO    CAN1SR12_ISR_ISR_LEVEL
#define IRQ_CAN1_SR12_CAT     CAN1SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR12_EXIST  STD_OFF
#endif

/******************CAN1SR13 IRQ ********************************/

#ifdef CAN1SR13_ISR
#define IRQ_CAN1SR13_EXIST  STD_ON
#define IRQ_CAN1_SR13_PRIO    CAN1SR13_ISR_ISR_LEVEL
#define IRQ_CAN1_SR13_CAT     CAN1SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR13_EXIST  STD_OFF
#endif

/******************CAN1SR14 IRQ ********************************/

#ifdef CAN1SR14_ISR
#define IRQ_CAN1SR14_EXIST  STD_ON
#define IRQ_CAN1_SR14_PRIO    CAN1SR14_ISR_ISR_LEVEL
#define IRQ_CAN1_SR14_CAT     CAN1SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR14_EXIST  STD_OFF
#endif

/******************CAN1SR15 IRQ ********************************/

#ifdef CAN1SR15_ISR
#define IRQ_CAN1SR15_EXIST  STD_ON
#define IRQ_CAN1_SR15_PRIO    CAN1SR15_ISR_ISR_LEVEL
#define IRQ_CAN1_SR15_CAT     CAN1SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR15_EXIST  STD_OFF
#endif

/******************CAN1SR2 IRQ ********************************/

#ifdef CAN1SR2_ISR
#define IRQ_CAN1SR2_EXIST  STD_ON
#define IRQ_CAN1_SR2_PRIO    CAN1SR2_ISR_ISR_LEVEL
#define IRQ_CAN1_SR2_CAT     CAN1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR2_EXIST  STD_OFF
#endif

/******************CAN1SR3 IRQ ********************************/

#ifdef CAN1SR3_ISR
#define IRQ_CAN1SR3_EXIST  STD_ON
#define IRQ_CAN1_SR3_PRIO    CAN1SR3_ISR_ISR_LEVEL
#define IRQ_CAN1_SR3_CAT     CAN1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR3_EXIST  STD_OFF
#endif

/******************CAN1SR4 IRQ ********************************/

#ifdef CAN1SR4_ISR
#define IRQ_CAN1SR4_EXIST  STD_ON
#define IRQ_CAN1_SR4_PRIO    CAN1SR4_ISR_ISR_LEVEL
#define IRQ_CAN1_SR4_CAT     CAN1SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR4_EXIST  STD_OFF
#endif

/******************CAN1SR5 IRQ ********************************/

#ifdef CAN1SR5_ISR
#define IRQ_CAN1SR5_EXIST  STD_ON
#define IRQ_CAN1_SR5_PRIO    CAN1SR5_ISR_ISR_LEVEL
#define IRQ_CAN1_SR5_CAT     CAN1SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR5_EXIST  STD_OFF
#endif

/******************CAN1SR6 IRQ ********************************/

#ifdef CAN1SR6_ISR
#define IRQ_CAN1SR6_EXIST  STD_ON
#define IRQ_CAN1_SR6_PRIO    CAN1SR6_ISR_ISR_LEVEL
#define IRQ_CAN1_SR6_CAT     CAN1SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR6_EXIST  STD_OFF
#endif

/******************CAN1SR7 IRQ ********************************/

#ifdef CAN1SR7_ISR
#define IRQ_CAN1SR7_EXIST  STD_ON
#define IRQ_CAN1_SR7_PRIO    CAN1SR7_ISR_ISR_LEVEL
#define IRQ_CAN1_SR7_CAT     CAN1SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR7_EXIST  STD_OFF
#endif

/******************CAN1SR8 IRQ ********************************/

#ifdef CAN1SR8_ISR
#define IRQ_CAN1SR8_EXIST  STD_ON
#define IRQ_CAN1_SR8_PRIO    CAN1SR8_ISR_ISR_LEVEL
#define IRQ_CAN1_SR8_CAT     CAN1SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR8_EXIST  STD_OFF
#endif

/******************CAN1SR9 IRQ ********************************/

#ifdef CAN1SR9_ISR
#define IRQ_CAN1SR9_EXIST  STD_ON
#define IRQ_CAN1_SR9_PRIO    CAN1SR9_ISR_ISR_LEVEL
#define IRQ_CAN1_SR9_CAT     CAN1SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR9_EXIST  STD_OFF
#endif

/******************CAN2SR0 IRQ ********************************/

#ifdef CAN2SR0_ISR
#define IRQ_CAN2SR0_EXIST  STD_ON
#define IRQ_CAN2_SR0_PRIO    CAN2SR0_ISR_ISR_LEVEL
#define IRQ_CAN2_SR0_CAT     CAN2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR0_EXIST  STD_OFF
#endif

/******************CAN2SR1 IRQ ********************************/

#ifdef CAN2SR1_ISR
#define IRQ_CAN2SR1_EXIST  STD_ON
#define IRQ_CAN2_SR1_PRIO    CAN2SR1_ISR_ISR_LEVEL
#define IRQ_CAN2_SR1_CAT     CAN2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR1_EXIST  STD_OFF
#endif

/******************CAN2SR10 IRQ ********************************/

#ifdef CAN2SR10_ISR
#define IRQ_CAN2SR10_EXIST  STD_ON
#define IRQ_CAN2_SR10_PRIO    CAN2SR10_ISR_ISR_LEVEL
#define IRQ_CAN2_SR10_CAT     CAN2SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR10_EXIST  STD_OFF
#endif

/******************CAN2SR11 IRQ ********************************/

#ifdef CAN2SR11_ISR
#define IRQ_CAN2SR11_EXIST  STD_ON
#define IRQ_CAN2_SR11_PRIO    CAN2SR11_ISR_ISR_LEVEL
#define IRQ_CAN2_SR11_CAT     CAN2SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR11_EXIST  STD_OFF
#endif

/******************CAN2SR12 IRQ ********************************/

#ifdef CAN2SR12_ISR
#define IRQ_CAN2SR12_EXIST  STD_ON
#define IRQ_CAN2_SR12_PRIO    CAN2SR12_ISR_ISR_LEVEL
#define IRQ_CAN2_SR12_CAT     CAN2SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR12_EXIST  STD_OFF
#endif

/******************CAN2SR13 IRQ ********************************/

#ifdef CAN2SR13_ISR
#define IRQ_CAN2SR13_EXIST  STD_ON
#define IRQ_CAN2_SR13_PRIO    CAN2SR13_ISR_ISR_LEVEL
#define IRQ_CAN2_SR13_CAT     CAN2SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR13_EXIST  STD_OFF
#endif

/******************CAN2SR14 IRQ ********************************/

#ifdef CAN2SR14_ISR
#define IRQ_CAN2SR14_EXIST  STD_ON
#define IRQ_CAN2_SR14_PRIO    CAN2SR14_ISR_ISR_LEVEL
#define IRQ_CAN2_SR14_CAT     CAN2SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR14_EXIST  STD_OFF
#endif

/******************CAN2SR15 IRQ ********************************/

#ifdef CAN2SR15_ISR
#define IRQ_CAN2SR15_EXIST  STD_ON
#define IRQ_CAN2_SR15_PRIO    CAN2SR15_ISR_ISR_LEVEL
#define IRQ_CAN2_SR15_CAT     CAN2SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR15_EXIST  STD_OFF
#endif

/******************CAN2SR2 IRQ ********************************/

#ifdef CAN2SR2_ISR
#define IRQ_CAN2SR2_EXIST  STD_ON
#define IRQ_CAN2_SR2_PRIO    CAN2SR2_ISR_ISR_LEVEL
#define IRQ_CAN2_SR2_CAT     CAN2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR2_EXIST  STD_OFF
#endif

/******************CAN2SR3 IRQ ********************************/

#ifdef CAN2SR3_ISR
#define IRQ_CAN2SR3_EXIST  STD_ON
#define IRQ_CAN2_SR3_PRIO    CAN2SR3_ISR_ISR_LEVEL
#define IRQ_CAN2_SR3_CAT     CAN2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR3_EXIST  STD_OFF
#endif

/******************CAN2SR4 IRQ ********************************/

#ifdef CAN2SR4_ISR
#define IRQ_CAN2SR4_EXIST  STD_ON
#define IRQ_CAN2_SR4_PRIO    CAN2SR4_ISR_ISR_LEVEL
#define IRQ_CAN2_SR4_CAT     CAN2SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR4_EXIST  STD_OFF
#endif

/******************CAN2SR5 IRQ ********************************/

#ifdef CAN2SR5_ISR
#define IRQ_CAN2SR5_EXIST  STD_ON
#define IRQ_CAN2_SR5_PRIO    CAN2SR5_ISR_ISR_LEVEL
#define IRQ_CAN2_SR5_CAT     CAN2SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR5_EXIST  STD_OFF
#endif

/******************CAN2SR6 IRQ ********************************/

#ifdef CAN2SR6_ISR
#define IRQ_CAN2SR6_EXIST  STD_ON
#define IRQ_CAN2_SR6_PRIO    CAN2SR6_ISR_ISR_LEVEL
#define IRQ_CAN2_SR6_CAT     CAN2SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR6_EXIST  STD_OFF
#endif

/******************CAN2SR7 IRQ ********************************/

#ifdef CAN2SR7_ISR
#define IRQ_CAN2SR7_EXIST  STD_ON
#define IRQ_CAN2_SR7_PRIO    CAN2SR7_ISR_ISR_LEVEL
#define IRQ_CAN2_SR7_CAT     CAN2SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR7_EXIST  STD_OFF
#endif

/******************CAN2SR8 IRQ ********************************/

#ifdef CAN2SR8_ISR
#define IRQ_CAN2SR8_EXIST  STD_ON
#define IRQ_CAN2_SR8_PRIO    CAN2SR8_ISR_ISR_LEVEL
#define IRQ_CAN2_SR8_CAT     CAN2SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR8_EXIST  STD_OFF
#endif

/******************CAN2SR9 IRQ ********************************/

#ifdef CAN2SR9_ISR
#define IRQ_CAN2SR9_EXIST  STD_ON
#define IRQ_CAN2_SR9_PRIO    CAN2SR9_ISR_ISR_LEVEL
#define IRQ_CAN2_SR9_CAT     CAN2SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR9_EXIST  STD_OFF
#endif

/******************CAN3SR0 IRQ ********************************/

#ifdef CAN3SR0_ISR
#define IRQ_CAN3SR0_EXIST  STD_ON
#define IRQ_CAN3_SR0_PRIO    CAN3SR0_ISR_ISR_LEVEL
#define IRQ_CAN3_SR0_CAT     CAN3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR0_EXIST  STD_OFF
#endif

/******************CAN3SR1 IRQ ********************************/

#ifdef CAN3SR1_ISR
#define IRQ_CAN3SR1_EXIST  STD_ON
#define IRQ_CAN3_SR1_PRIO    CAN3SR1_ISR_ISR_LEVEL
#define IRQ_CAN3_SR1_CAT     CAN3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR1_EXIST  STD_OFF
#endif

/******************CAN3SR10 IRQ ********************************/

#ifdef CAN3SR10_ISR
#define IRQ_CAN3SR10_EXIST  STD_ON
#define IRQ_CAN3_SR10_PRIO    CAN3SR10_ISR_ISR_LEVEL
#define IRQ_CAN3_SR10_CAT     CAN3SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR10_EXIST  STD_OFF
#endif

/******************CAN3SR11 IRQ ********************************/

#ifdef CAN3SR11_ISR
#define IRQ_CAN3SR11_EXIST  STD_ON
#define IRQ_CAN3_SR11_PRIO    CAN3SR11_ISR_ISR_LEVEL
#define IRQ_CAN3_SR11_CAT     CAN3SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR11_EXIST  STD_OFF
#endif

/******************CAN3SR12 IRQ ********************************/

#ifdef CAN3SR12_ISR
#define IRQ_CAN3SR12_EXIST  STD_ON
#define IRQ_CAN3_SR12_PRIO    CAN3SR12_ISR_ISR_LEVEL
#define IRQ_CAN3_SR12_CAT     CAN3SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR12_EXIST  STD_OFF
#endif

/******************CAN3SR13 IRQ ********************************/

#ifdef CAN3SR13_ISR
#define IRQ_CAN3SR13_EXIST  STD_ON
#define IRQ_CAN3_SR13_PRIO    CAN3SR13_ISR_ISR_LEVEL
#define IRQ_CAN3_SR13_CAT     CAN3SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR13_EXIST  STD_OFF
#endif

/******************CAN3SR14 IRQ ********************************/

#ifdef CAN3SR14_ISR
#define IRQ_CAN3SR14_EXIST  STD_ON
#define IRQ_CAN3_SR14_PRIO    CAN3SR14_ISR_ISR_LEVEL
#define IRQ_CAN3_SR14_CAT     CAN3SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR14_EXIST  STD_OFF
#endif

/******************CAN3SR15 IRQ ********************************/

#ifdef CAN3SR15_ISR
#define IRQ_CAN3SR15_EXIST  STD_ON
#define IRQ_CAN3_SR15_PRIO    CAN3SR15_ISR_ISR_LEVEL
#define IRQ_CAN3_SR15_CAT     CAN3SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR15_EXIST  STD_OFF
#endif

/******************CAN3SR2 IRQ ********************************/

#ifdef CAN3SR2_ISR
#define IRQ_CAN3SR2_EXIST  STD_ON
#define IRQ_CAN3_SR2_PRIO    CAN3SR2_ISR_ISR_LEVEL
#define IRQ_CAN3_SR2_CAT     CAN3SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR2_EXIST  STD_OFF
#endif

/******************CAN3SR3 IRQ ********************************/

#ifdef CAN3SR3_ISR
#define IRQ_CAN3SR3_EXIST  STD_ON
#define IRQ_CAN3_SR3_PRIO    CAN3SR3_ISR_ISR_LEVEL
#define IRQ_CAN3_SR3_CAT     CAN3SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR3_EXIST  STD_OFF
#endif

/******************CAN3SR4 IRQ ********************************/

#ifdef CAN3SR4_ISR
#define IRQ_CAN3SR4_EXIST  STD_ON
#define IRQ_CAN3_SR4_PRIO    CAN3SR4_ISR_ISR_LEVEL
#define IRQ_CAN3_SR4_CAT     CAN3SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR4_EXIST  STD_OFF
#endif

/******************CAN3SR5 IRQ ********************************/

#ifdef CAN3SR5_ISR
#define IRQ_CAN3SR5_EXIST  STD_ON
#define IRQ_CAN3_SR5_PRIO    CAN3SR5_ISR_ISR_LEVEL
#define IRQ_CAN3_SR5_CAT     CAN3SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR5_EXIST  STD_OFF
#endif

/******************CAN3SR6 IRQ ********************************/

#ifdef CAN3SR6_ISR
#define IRQ_CAN3SR6_EXIST  STD_ON
#define IRQ_CAN3_SR6_PRIO    CAN3SR6_ISR_ISR_LEVEL
#define IRQ_CAN3_SR6_CAT     CAN3SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR6_EXIST  STD_OFF
#endif

/******************CAN3SR7 IRQ ********************************/

#ifdef CAN3SR7_ISR
#define IRQ_CAN3SR7_EXIST  STD_ON
#define IRQ_CAN3_SR7_PRIO    CAN3SR7_ISR_ISR_LEVEL
#define IRQ_CAN3_SR7_CAT     CAN3SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR7_EXIST  STD_OFF
#endif

/******************CAN3SR8 IRQ ********************************/

#ifdef CAN3SR8_ISR
#define IRQ_CAN3SR8_EXIST  STD_ON
#define IRQ_CAN3_SR8_PRIO    CAN3SR8_ISR_ISR_LEVEL
#define IRQ_CAN3_SR8_CAT     CAN3SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR8_EXIST  STD_OFF
#endif

/******************CAN3SR9 IRQ ********************************/

#ifdef CAN3SR9_ISR
#define IRQ_CAN3SR9_EXIST  STD_ON
#define IRQ_CAN3_SR9_PRIO    CAN3SR9_ISR_ISR_LEVEL
#define IRQ_CAN3_SR9_CAT     CAN3SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN3SR9_EXIST  STD_OFF
#endif

/******************CAN4SR0 IRQ ********************************/

#ifdef CAN4SR0_ISR
#define IRQ_CAN4SR0_EXIST  STD_ON
#define IRQ_CAN4_SR0_PRIO    CAN4SR0_ISR_ISR_LEVEL
#define IRQ_CAN4_SR0_CAT     CAN4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR0_EXIST  STD_OFF
#endif

/******************CAN4SR1 IRQ ********************************/

#ifdef CAN4SR1_ISR
#define IRQ_CAN4SR1_EXIST  STD_ON
#define IRQ_CAN4_SR1_PRIO    CAN4SR1_ISR_ISR_LEVEL
#define IRQ_CAN4_SR1_CAT     CAN4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR1_EXIST  STD_OFF
#endif

/******************CAN4SR10 IRQ ********************************/

#ifdef CAN4SR10_ISR
#define IRQ_CAN4SR10_EXIST  STD_ON
#define IRQ_CAN4_SR10_PRIO    CAN4SR10_ISR_ISR_LEVEL
#define IRQ_CAN4_SR10_CAT     CAN4SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR10_EXIST  STD_OFF
#endif

/******************CAN4SR11 IRQ ********************************/

#ifdef CAN4SR11_ISR
#define IRQ_CAN4SR11_EXIST  STD_ON
#define IRQ_CAN4_SR11_PRIO    CAN4SR11_ISR_ISR_LEVEL
#define IRQ_CAN4_SR11_CAT     CAN4SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR11_EXIST  STD_OFF
#endif

/******************CAN4SR12 IRQ ********************************/

#ifdef CAN4SR12_ISR
#define IRQ_CAN4SR12_EXIST  STD_ON
#define IRQ_CAN4_SR12_PRIO    CAN4SR12_ISR_ISR_LEVEL
#define IRQ_CAN4_SR12_CAT     CAN4SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR12_EXIST  STD_OFF
#endif

/******************CAN4SR13 IRQ ********************************/

#ifdef CAN4SR13_ISR
#define IRQ_CAN4SR13_EXIST  STD_ON
#define IRQ_CAN4_SR13_PRIO    CAN4SR13_ISR_ISR_LEVEL
#define IRQ_CAN4_SR13_CAT     CAN4SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR13_EXIST  STD_OFF
#endif

/******************CAN4SR14 IRQ ********************************/

#ifdef CAN4SR14_ISR
#define IRQ_CAN4SR14_EXIST  STD_ON
#define IRQ_CAN4_SR14_PRIO    CAN4SR14_ISR_ISR_LEVEL
#define IRQ_CAN4_SR14_CAT     CAN4SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR14_EXIST  STD_OFF
#endif

/******************CAN4SR15 IRQ ********************************/

#ifdef CAN4SR15_ISR
#define IRQ_CAN4SR15_EXIST  STD_ON
#define IRQ_CAN4_SR15_PRIO    CAN4SR15_ISR_ISR_LEVEL
#define IRQ_CAN4_SR15_CAT     CAN4SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR15_EXIST  STD_OFF
#endif

/******************CAN4SR2 IRQ ********************************/

#ifdef CAN4SR2_ISR
#define IRQ_CAN4SR2_EXIST  STD_ON
#define IRQ_CAN4_SR2_PRIO    CAN4SR2_ISR_ISR_LEVEL
#define IRQ_CAN4_SR2_CAT     CAN4SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR2_EXIST  STD_OFF
#endif

/******************CAN4SR3 IRQ ********************************/

#ifdef CAN4SR3_ISR
#define IRQ_CAN4SR3_EXIST  STD_ON
#define IRQ_CAN4_SR3_PRIO    CAN4SR3_ISR_ISR_LEVEL
#define IRQ_CAN4_SR3_CAT     CAN4SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR3_EXIST  STD_OFF
#endif

/******************CAN4SR4 IRQ ********************************/

#ifdef CAN4SR4_ISR
#define IRQ_CAN4SR4_EXIST  STD_ON
#define IRQ_CAN4_SR4_PRIO    CAN4SR4_ISR_ISR_LEVEL
#define IRQ_CAN4_SR4_CAT     CAN4SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR4_EXIST  STD_OFF
#endif

/******************CAN4SR5 IRQ ********************************/

#ifdef CAN4SR5_ISR
#define IRQ_CAN4SR5_EXIST  STD_ON
#define IRQ_CAN4_SR5_PRIO    CAN4SR5_ISR_ISR_LEVEL
#define IRQ_CAN4_SR5_CAT     CAN4SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR5_EXIST  STD_OFF
#endif

/******************CAN4SR6 IRQ ********************************/

#ifdef CAN4SR6_ISR
#define IRQ_CAN4SR6_EXIST  STD_ON
#define IRQ_CAN4_SR6_PRIO    CAN4SR6_ISR_ISR_LEVEL
#define IRQ_CAN4_SR6_CAT     CAN4SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR6_EXIST  STD_OFF
#endif

/******************CAN4SR7 IRQ ********************************/

#ifdef CAN4SR7_ISR
#define IRQ_CAN4SR7_EXIST  STD_ON
#define IRQ_CAN4_SR7_PRIO    CAN4SR7_ISR_ISR_LEVEL
#define IRQ_CAN4_SR7_CAT     CAN4SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR7_EXIST  STD_OFF
#endif

/******************CAN4SR8 IRQ ********************************/

#ifdef CAN4SR8_ISR
#define IRQ_CAN4SR8_EXIST  STD_ON
#define IRQ_CAN4_SR8_PRIO    CAN4SR8_ISR_ISR_LEVEL
#define IRQ_CAN4_SR8_CAT     CAN4SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR8_EXIST  STD_OFF
#endif

/******************CAN4SR9 IRQ ********************************/

#ifdef CAN4SR9_ISR
#define IRQ_CAN4SR9_EXIST  STD_ON
#define IRQ_CAN4_SR9_PRIO    CAN4SR9_ISR_ISR_LEVEL
#define IRQ_CAN4_SR9_CAT     CAN4SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN4SR9_EXIST  STD_OFF
#endif
#endif /* #ifndef CAN_17_MCMCAN_IRQ_H */
