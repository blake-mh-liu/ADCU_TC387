
#ifndef STM_IRQ_H
#define STM_IRQ_H

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

/******************STM0SR0 IRQ ********************************/

#ifdef STM0SR0_ISR
#define IRQ_STM0SR0_EXIST  STD_ON
#define IRQ_STM0_SR0_PRIO    STM0SR0_ISR_ISR_LEVEL
#define IRQ_STM0_SR0_CAT     STM0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM0SR0_EXIST  STD_OFF
#endif

/******************STM0SR1 IRQ ********************************/

#ifdef STM0SR1_ISR
#define IRQ_STM0SR1_EXIST  STD_ON
#define IRQ_STM0_SR1_PRIO    STM0SR1_ISR_ISR_LEVEL
#define IRQ_STM0_SR1_CAT     STM0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM0SR1_EXIST  STD_OFF
#endif

/******************STM1SR0 IRQ ********************************/

#ifdef STM1SR0_ISR
#define IRQ_STM1SR0_EXIST  STD_ON
#define IRQ_STM1_SR0_PRIO    STM1SR0_ISR_ISR_LEVEL
#define IRQ_STM1_SR0_CAT     STM1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM1SR0_EXIST  STD_OFF
#endif

/******************STM1SR1 IRQ ********************************/

#ifdef STM1SR1_ISR
#define IRQ_STM1SR1_EXIST  STD_ON
#define IRQ_STM1_SR1_PRIO    STM1SR1_ISR_ISR_LEVEL
#define IRQ_STM1_SR1_CAT     STM1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM1SR1_EXIST  STD_OFF
#endif

/******************STM2SR0 IRQ ********************************/

#ifdef STM2SR0_ISR
#define IRQ_STM2SR0_EXIST  STD_ON
#define IRQ_STM2_SR0_PRIO    STM2SR0_ISR_ISR_LEVEL
#define IRQ_STM2_SR0_CAT     STM2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM2SR0_EXIST  STD_OFF
#endif

/******************STM2SR1 IRQ ********************************/

#ifdef STM2SR1_ISR
#define IRQ_STM2SR1_EXIST  STD_ON
#define IRQ_STM2_SR1_PRIO    STM2SR1_ISR_ISR_LEVEL
#define IRQ_STM2_SR1_CAT     STM2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM2SR1_EXIST  STD_OFF
#endif

/******************STM3SR0 IRQ ********************************/

#ifdef STM3SR0_ISR
#define IRQ_STM3SR0_EXIST  STD_ON
#define IRQ_STM3_SR0_PRIO    STM3SR0_ISR_ISR_LEVEL
#define IRQ_STM3_SR0_CAT     STM3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM3SR0_EXIST  STD_OFF
#endif

/******************STM3SR1 IRQ ********************************/

#ifdef STM3SR1_ISR
#define IRQ_STM3SR1_EXIST  STD_ON
#define IRQ_STM3_SR1_PRIO    STM3SR1_ISR_ISR_LEVEL
#define IRQ_STM3_SR1_CAT     STM3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM3SR1_EXIST  STD_OFF
#endif

/******************STM4SR0 IRQ ********************************/

#ifdef STM4SR0_ISR
#define IRQ_STM4SR0_EXIST  STD_ON
#define IRQ_STM4_SR0_PRIO    STM4SR0_ISR_ISR_LEVEL
#define IRQ_STM4_SR0_CAT     STM4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM4SR0_EXIST  STD_OFF
#endif

/******************STM4SR1 IRQ ********************************/

#ifdef STM4SR1_ISR
#define IRQ_STM4SR1_EXIST  STD_ON
#define IRQ_STM4_SR1_PRIO    STM4SR1_ISR_ISR_LEVEL
#define IRQ_STM4_SR1_CAT     STM4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM4SR1_EXIST  STD_OFF
#endif

/******************STM5SR0 IRQ ********************************/

#ifdef STM5SR0_ISR
#define IRQ_STM5SR0_EXIST  STD_ON
#define IRQ_STM5_SR0_PRIO    STM5SR0_ISR_ISR_LEVEL
#define IRQ_STM5_SR0_CAT     STM5SR0_ISR_ISR_CATEGORY
#else
#define IRQ_STM5SR0_EXIST  STD_OFF
#endif

/******************STM5SR1 IRQ ********************************/

#ifdef STM5SR1_ISR
#define IRQ_STM5SR1_EXIST  STD_ON
#define IRQ_STM5_SR1_PRIO    STM5SR1_ISR_ISR_LEVEL
#define IRQ_STM5_SR1_CAT     STM5SR1_ISR_ISR_CATEGORY
#else
#define IRQ_STM5SR1_EXIST  STD_OFF
#endif
#endif /* #ifndef STM_IRQ_H */
