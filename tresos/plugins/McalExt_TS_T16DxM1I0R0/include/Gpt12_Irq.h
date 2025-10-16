
#ifndef GPT12_IRQ_H
#define GPT12_IRQ_H

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

/******************GPT12_T2 IRQ ********************************/

#ifdef GPT12_T2_ISR
#define IRQ_GPT12_T2_EXIST  STD_ON
#define IRQ_GPT120_T2_PRIO    GPT12_T2_ISR_ISR_LEVEL
#define IRQ_GPT120_T2_CAT     GPT12_T2_ISR_ISR_CATEGORY
#else
#define IRQ_GPT12_T2_EXIST  STD_OFF
#endif

/******************GPT12_T3 IRQ ********************************/

#ifdef GPT12_T3_ISR
#define IRQ_GPT12_T3_EXIST  STD_ON
#define IRQ_GPT120_T3_PRIO    GPT12_T3_ISR_ISR_LEVEL
#define IRQ_GPT120_T3_CAT     GPT12_T3_ISR_ISR_CATEGORY
#else
#define IRQ_GPT12_T3_EXIST  STD_OFF
#endif

/******************GPT12_T4 IRQ ********************************/

#ifdef GPT12_T4_ISR
#define IRQ_GPT12_T4_EXIST  STD_ON
#define IRQ_GPT120_T4_PRIO    GPT12_T4_ISR_ISR_LEVEL
#define IRQ_GPT120_T4_CAT     GPT12_T4_ISR_ISR_CATEGORY
#else
#define IRQ_GPT12_T4_EXIST  STD_OFF
#endif

/******************GPT12_T5 IRQ ********************************/

#ifdef GPT12_T5_ISR
#define IRQ_GPT12_T5_EXIST  STD_ON
#define IRQ_GPT120_T5_PRIO    GPT12_T5_ISR_ISR_LEVEL
#define IRQ_GPT120_T5_CAT     GPT12_T5_ISR_ISR_CATEGORY
#else
#define IRQ_GPT12_T5_EXIST  STD_OFF
#endif

/******************GPT12_T6 IRQ ********************************/

#ifdef GPT12_T6_ISR
#define IRQ_GPT12_T6_EXIST  STD_ON
#define IRQ_GPT120_T6_PRIO    GPT12_T6_ISR_ISR_LEVEL
#define IRQ_GPT120_T6_CAT     GPT12_T6_ISR_ISR_CATEGORY
#else
#define IRQ_GPT12_T6_EXIST  STD_OFF
#endif
#endif /* #ifndef GPT12_IRQ_H */
