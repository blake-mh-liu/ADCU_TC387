
#ifndef ERU_IRQ_H
#define ERU_IRQ_H

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

/******************SCUERUSR0 IRQ ********************************/

#ifdef SCUERUSR0_ISR
#define IRQ_SCUERUSR0_EXIST  STD_ON
#define IRQ_SCU_ERU_SR0_PRIO    SCUERUSR0_ISR_ISR_LEVEL
#define IRQ_SCU_ERU_SR0_CAT     SCUERUSR0_ISR_ISR_CATEGORY
#else
#define IRQ_SCUERUSR0_EXIST  STD_OFF
#endif

/******************SCUERUSR1 IRQ ********************************/

#ifdef SCUERUSR1_ISR
#define IRQ_SCUERUSR1_EXIST  STD_ON
#define IRQ_SCU_ERU_SR1_PRIO    SCUERUSR1_ISR_ISR_LEVEL
#define IRQ_SCU_ERU_SR1_CAT     SCUERUSR1_ISR_ISR_CATEGORY
#else
#define IRQ_SCUERUSR1_EXIST  STD_OFF
#endif

/******************SCUERUSR2 IRQ ********************************/

#ifdef SCUERUSR2_ISR
#define IRQ_SCUERUSR2_EXIST  STD_ON
#define IRQ_SCU_ERU_SR2_PRIO    SCUERUSR2_ISR_ISR_LEVEL
#define IRQ_SCU_ERU_SR2_CAT     SCUERUSR2_ISR_ISR_CATEGORY
#else
#define IRQ_SCUERUSR2_EXIST  STD_OFF
#endif

/******************SCUERUSR3 IRQ ********************************/

#ifdef SCUERUSR3_ISR
#define IRQ_SCUERUSR3_EXIST  STD_ON
#define IRQ_SCU_ERU_SR3_PRIO    SCUERUSR3_ISR_ISR_LEVEL
#define IRQ_SCU_ERU_SR3_CAT     SCUERUSR3_ISR_ISR_CATEGORY
#else
#define IRQ_SCUERUSR3_EXIST  STD_OFF
#endif
#endif /* #ifndef ERU_IRQ_H */
