
#ifndef SENT_IRQ_H
#define SENT_IRQ_H

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

/******************SENTSR0 IRQ ********************************/

#ifdef SENTSR0_ISR
#define IRQ_SENTSR0_EXIST  STD_ON
#define IRQ_SENT_SR0_PRIO    SENTSR0_ISR_ISR_LEVEL
#define IRQ_SENT_SR0_CAT     SENTSR0_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR0_EXIST  STD_OFF
#endif

/******************SENTSR1 IRQ ********************************/

#ifdef SENTSR1_ISR
#define IRQ_SENTSR1_EXIST  STD_ON
#define IRQ_SENT_SR1_PRIO    SENTSR1_ISR_ISR_LEVEL
#define IRQ_SENT_SR1_CAT     SENTSR1_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR1_EXIST  STD_OFF
#endif

/******************SENTSR2 IRQ ********************************/

#ifdef SENTSR2_ISR
#define IRQ_SENTSR2_EXIST  STD_ON
#define IRQ_SENT_SR2_PRIO    SENTSR2_ISR_ISR_LEVEL
#define IRQ_SENT_SR2_CAT     SENTSR2_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR2_EXIST  STD_OFF
#endif

/******************SENTSR3 IRQ ********************************/

#ifdef SENTSR3_ISR
#define IRQ_SENTSR3_EXIST  STD_ON
#define IRQ_SENT_SR3_PRIO    SENTSR3_ISR_ISR_LEVEL
#define IRQ_SENT_SR3_CAT     SENTSR3_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR3_EXIST  STD_OFF
#endif

/******************SENTSR4 IRQ ********************************/

#ifdef SENTSR4_ISR
#define IRQ_SENTSR4_EXIST  STD_ON
#define IRQ_SENT_SR4_PRIO    SENTSR4_ISR_ISR_LEVEL
#define IRQ_SENT_SR4_CAT     SENTSR4_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR4_EXIST  STD_OFF
#endif

/******************SENTSR5 IRQ ********************************/

#ifdef SENTSR5_ISR
#define IRQ_SENTSR5_EXIST  STD_ON
#define IRQ_SENT_SR5_PRIO    SENTSR5_ISR_ISR_LEVEL
#define IRQ_SENT_SR5_CAT     SENTSR5_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR5_EXIST  STD_OFF
#endif

/******************SENTSR6 IRQ ********************************/

#ifdef SENTSR6_ISR
#define IRQ_SENTSR6_EXIST  STD_ON
#define IRQ_SENT_SR6_PRIO    SENTSR6_ISR_ISR_LEVEL
#define IRQ_SENT_SR6_CAT     SENTSR6_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR6_EXIST  STD_OFF
#endif

/******************SENTSR7 IRQ ********************************/

#ifdef SENTSR7_ISR
#define IRQ_SENTSR7_EXIST  STD_ON
#define IRQ_SENT_SR7_PRIO    SENTSR7_ISR_ISR_LEVEL
#define IRQ_SENT_SR7_CAT     SENTSR7_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR7_EXIST  STD_OFF
#endif

/******************SENTSR8 IRQ ********************************/

#ifdef SENTSR8_ISR
#define IRQ_SENTSR8_EXIST  STD_ON
#define IRQ_SENT_SR8_PRIO    SENTSR8_ISR_ISR_LEVEL
#define IRQ_SENT_SR8_CAT     SENTSR8_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR8_EXIST  STD_OFF
#endif

/******************SENTSR9 IRQ ********************************/

#ifdef SENTSR9_ISR
#define IRQ_SENTSR9_EXIST  STD_ON
#define IRQ_SENT_SR9_PRIO    SENTSR9_ISR_ISR_LEVEL
#define IRQ_SENT_SR9_CAT     SENTSR9_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR9_EXIST  STD_OFF
#endif
#endif /* #ifndef SENT_IRQ_H */
