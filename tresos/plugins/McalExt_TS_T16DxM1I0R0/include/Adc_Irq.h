
#ifndef ADC_IRQ_H
#define ADC_IRQ_H

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

/******************ADC0SR0 IRQ ********************************/

#ifdef ADC0SR0_ISR
#define IRQ_ADC0SR0_EXIST  STD_ON
#define IRQ_ADC0_SR0_PRIO    ADC0SR0_ISR_ISR_LEVEL
#define IRQ_ADC0_SR0_CAT     ADC0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC0SR0_EXIST  STD_OFF
#endif

/******************ADC0SR1 IRQ ********************************/

#ifdef ADC0SR1_ISR
#define IRQ_ADC0SR1_EXIST  STD_ON
#define IRQ_ADC0_SR1_PRIO    ADC0SR1_ISR_ISR_LEVEL
#define IRQ_ADC0_SR1_CAT     ADC0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC0SR1_EXIST  STD_OFF
#endif

/******************ADC0SR2 IRQ ********************************/

#ifdef ADC0SR2_ISR
#define IRQ_ADC0SR2_EXIST  STD_ON
#define IRQ_ADC0_SR2_PRIO    ADC0SR2_ISR_ISR_LEVEL
#define IRQ_ADC0_SR2_CAT     ADC0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC0SR2_EXIST  STD_OFF
#endif

/******************ADC0SR3 IRQ ********************************/

#ifdef ADC0SR3_ISR
#define IRQ_ADC0SR3_EXIST  STD_ON
#define IRQ_ADC0_SR3_PRIO    ADC0SR3_ISR_ISR_LEVEL
#define IRQ_ADC0_SR3_CAT     ADC0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC0SR3_EXIST  STD_OFF
#endif

/******************ADC10SR0 IRQ ********************************/

#ifdef ADC10SR0_ISR
#define IRQ_ADC10SR0_EXIST  STD_ON
#define IRQ_ADC10_SR0_PRIO    ADC10SR0_ISR_ISR_LEVEL
#define IRQ_ADC10_SR0_CAT     ADC10SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC10SR0_EXIST  STD_OFF
#endif

/******************ADC10SR1 IRQ ********************************/

#ifdef ADC10SR1_ISR
#define IRQ_ADC10SR1_EXIST  STD_ON
#define IRQ_ADC10_SR1_PRIO    ADC10SR1_ISR_ISR_LEVEL
#define IRQ_ADC10_SR1_CAT     ADC10SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC10SR1_EXIST  STD_OFF
#endif

/******************ADC10SR2 IRQ ********************************/

#ifdef ADC10SR2_ISR
#define IRQ_ADC10SR2_EXIST  STD_ON
#define IRQ_ADC10_SR2_PRIO    ADC10SR2_ISR_ISR_LEVEL
#define IRQ_ADC10_SR2_CAT     ADC10SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC10SR2_EXIST  STD_OFF
#endif

/******************ADC10SR3 IRQ ********************************/

#ifdef ADC10SR3_ISR
#define IRQ_ADC10SR3_EXIST  STD_ON
#define IRQ_ADC10_SR3_PRIO    ADC10SR3_ISR_ISR_LEVEL
#define IRQ_ADC10_SR3_CAT     ADC10SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC10SR3_EXIST  STD_OFF
#endif

/******************ADC11SR0 IRQ ********************************/

#ifdef ADC11SR0_ISR
#define IRQ_ADC11SR0_EXIST  STD_ON
#define IRQ_ADC11_SR0_PRIO    ADC11SR0_ISR_ISR_LEVEL
#define IRQ_ADC11_SR0_CAT     ADC11SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC11SR0_EXIST  STD_OFF
#endif

/******************ADC11SR1 IRQ ********************************/

#ifdef ADC11SR1_ISR
#define IRQ_ADC11SR1_EXIST  STD_ON
#define IRQ_ADC11_SR1_PRIO    ADC11SR1_ISR_ISR_LEVEL
#define IRQ_ADC11_SR1_CAT     ADC11SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC11SR1_EXIST  STD_OFF
#endif

/******************ADC11SR2 IRQ ********************************/

#ifdef ADC11SR2_ISR
#define IRQ_ADC11SR2_EXIST  STD_ON
#define IRQ_ADC11_SR2_PRIO    ADC11SR2_ISR_ISR_LEVEL
#define IRQ_ADC11_SR2_CAT     ADC11SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC11SR2_EXIST  STD_OFF
#endif

/******************ADC11SR3 IRQ ********************************/

#ifdef ADC11SR3_ISR
#define IRQ_ADC11SR3_EXIST  STD_ON
#define IRQ_ADC11_SR3_PRIO    ADC11SR3_ISR_ISR_LEVEL
#define IRQ_ADC11_SR3_CAT     ADC11SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC11SR3_EXIST  STD_OFF
#endif

/******************ADC1SR0 IRQ ********************************/

#ifdef ADC1SR0_ISR
#define IRQ_ADC1SR0_EXIST  STD_ON
#define IRQ_ADC1_SR0_PRIO    ADC1SR0_ISR_ISR_LEVEL
#define IRQ_ADC1_SR0_CAT     ADC1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC1SR0_EXIST  STD_OFF
#endif

/******************ADC1SR1 IRQ ********************************/

#ifdef ADC1SR1_ISR
#define IRQ_ADC1SR1_EXIST  STD_ON
#define IRQ_ADC1_SR1_PRIO    ADC1SR1_ISR_ISR_LEVEL
#define IRQ_ADC1_SR1_CAT     ADC1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC1SR1_EXIST  STD_OFF
#endif

/******************ADC1SR2 IRQ ********************************/

#ifdef ADC1SR2_ISR
#define IRQ_ADC1SR2_EXIST  STD_ON
#define IRQ_ADC1_SR2_PRIO    ADC1SR2_ISR_ISR_LEVEL
#define IRQ_ADC1_SR2_CAT     ADC1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC1SR2_EXIST  STD_OFF
#endif

/******************ADC1SR3 IRQ ********************************/

#ifdef ADC1SR3_ISR
#define IRQ_ADC1SR3_EXIST  STD_ON
#define IRQ_ADC1_SR3_PRIO    ADC1SR3_ISR_ISR_LEVEL
#define IRQ_ADC1_SR3_CAT     ADC1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC1SR3_EXIST  STD_OFF
#endif

/******************ADC2SR0 IRQ ********************************/

#ifdef ADC2SR0_ISR
#define IRQ_ADC2SR0_EXIST  STD_ON
#define IRQ_ADC2_SR0_PRIO    ADC2SR0_ISR_ISR_LEVEL
#define IRQ_ADC2_SR0_CAT     ADC2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC2SR0_EXIST  STD_OFF
#endif

/******************ADC2SR1 IRQ ********************************/

#ifdef ADC2SR1_ISR
#define IRQ_ADC2SR1_EXIST  STD_ON
#define IRQ_ADC2_SR1_PRIO    ADC2SR1_ISR_ISR_LEVEL
#define IRQ_ADC2_SR1_CAT     ADC2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC2SR1_EXIST  STD_OFF
#endif

/******************ADC2SR2 IRQ ********************************/

#ifdef ADC2SR2_ISR
#define IRQ_ADC2SR2_EXIST  STD_ON
#define IRQ_ADC2_SR2_PRIO    ADC2SR2_ISR_ISR_LEVEL
#define IRQ_ADC2_SR2_CAT     ADC2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC2SR2_EXIST  STD_OFF
#endif

/******************ADC2SR3 IRQ ********************************/

#ifdef ADC2SR3_ISR
#define IRQ_ADC2SR3_EXIST  STD_ON
#define IRQ_ADC2_SR3_PRIO    ADC2SR3_ISR_ISR_LEVEL
#define IRQ_ADC2_SR3_CAT     ADC2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC2SR3_EXIST  STD_OFF
#endif

/******************ADC3SR0 IRQ ********************************/

#ifdef ADC3SR0_ISR
#define IRQ_ADC3SR0_EXIST  STD_ON
#define IRQ_ADC3_SR0_PRIO    ADC3SR0_ISR_ISR_LEVEL
#define IRQ_ADC3_SR0_CAT     ADC3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC3SR0_EXIST  STD_OFF
#endif

/******************ADC3SR1 IRQ ********************************/

#ifdef ADC3SR1_ISR
#define IRQ_ADC3SR1_EXIST  STD_ON
#define IRQ_ADC3_SR1_PRIO    ADC3SR1_ISR_ISR_LEVEL
#define IRQ_ADC3_SR1_CAT     ADC3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC3SR1_EXIST  STD_OFF
#endif

/******************ADC3SR2 IRQ ********************************/

#ifdef ADC3SR2_ISR
#define IRQ_ADC3SR2_EXIST  STD_ON
#define IRQ_ADC3_SR2_PRIO    ADC3SR2_ISR_ISR_LEVEL
#define IRQ_ADC3_SR2_CAT     ADC3SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC3SR2_EXIST  STD_OFF
#endif

/******************ADC3SR3 IRQ ********************************/

#ifdef ADC3SR3_ISR
#define IRQ_ADC3SR3_EXIST  STD_ON
#define IRQ_ADC3_SR3_PRIO    ADC3SR3_ISR_ISR_LEVEL
#define IRQ_ADC3_SR3_CAT     ADC3SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC3SR3_EXIST  STD_OFF
#endif

/******************ADC4SR0 IRQ ********************************/

#ifdef ADC4SR0_ISR
#define IRQ_ADC4SR0_EXIST  STD_ON
#define IRQ_ADC4_SR0_PRIO    ADC4SR0_ISR_ISR_LEVEL
#define IRQ_ADC4_SR0_CAT     ADC4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC4SR0_EXIST  STD_OFF
#endif

/******************ADC4SR1 IRQ ********************************/

#ifdef ADC4SR1_ISR
#define IRQ_ADC4SR1_EXIST  STD_ON
#define IRQ_ADC4_SR1_PRIO    ADC4SR1_ISR_ISR_LEVEL
#define IRQ_ADC4_SR1_CAT     ADC4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC4SR1_EXIST  STD_OFF
#endif

/******************ADC4SR2 IRQ ********************************/

#ifdef ADC4SR2_ISR
#define IRQ_ADC4SR2_EXIST  STD_ON
#define IRQ_ADC4_SR2_PRIO    ADC4SR2_ISR_ISR_LEVEL
#define IRQ_ADC4_SR2_CAT     ADC4SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC4SR2_EXIST  STD_OFF
#endif

/******************ADC4SR3 IRQ ********************************/

#ifdef ADC4SR3_ISR
#define IRQ_ADC4SR3_EXIST  STD_ON
#define IRQ_ADC4_SR3_PRIO    ADC4SR3_ISR_ISR_LEVEL
#define IRQ_ADC4_SR3_CAT     ADC4SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC4SR3_EXIST  STD_OFF
#endif

/******************ADC5SR0 IRQ ********************************/

#ifdef ADC5SR0_ISR
#define IRQ_ADC5SR0_EXIST  STD_ON
#define IRQ_ADC5_SR0_PRIO    ADC5SR0_ISR_ISR_LEVEL
#define IRQ_ADC5_SR0_CAT     ADC5SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC5SR0_EXIST  STD_OFF
#endif

/******************ADC5SR1 IRQ ********************************/

#ifdef ADC5SR1_ISR
#define IRQ_ADC5SR1_EXIST  STD_ON
#define IRQ_ADC5_SR1_PRIO    ADC5SR1_ISR_ISR_LEVEL
#define IRQ_ADC5_SR1_CAT     ADC5SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC5SR1_EXIST  STD_OFF
#endif

/******************ADC5SR2 IRQ ********************************/

#ifdef ADC5SR2_ISR
#define IRQ_ADC5SR2_EXIST  STD_ON
#define IRQ_ADC5_SR2_PRIO    ADC5SR2_ISR_ISR_LEVEL
#define IRQ_ADC5_SR2_CAT     ADC5SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC5SR2_EXIST  STD_OFF
#endif

/******************ADC5SR3 IRQ ********************************/

#ifdef ADC5SR3_ISR
#define IRQ_ADC5SR3_EXIST  STD_ON
#define IRQ_ADC5_SR3_PRIO    ADC5SR3_ISR_ISR_LEVEL
#define IRQ_ADC5_SR3_CAT     ADC5SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC5SR3_EXIST  STD_OFF
#endif

/******************ADC6SR0 IRQ ********************************/

#ifdef ADC6SR0_ISR
#define IRQ_ADC6SR0_EXIST  STD_ON
#define IRQ_ADC6_SR0_PRIO    ADC6SR0_ISR_ISR_LEVEL
#define IRQ_ADC6_SR0_CAT     ADC6SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC6SR0_EXIST  STD_OFF
#endif

/******************ADC6SR1 IRQ ********************************/

#ifdef ADC6SR1_ISR
#define IRQ_ADC6SR1_EXIST  STD_ON
#define IRQ_ADC6_SR1_PRIO    ADC6SR1_ISR_ISR_LEVEL
#define IRQ_ADC6_SR1_CAT     ADC6SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC6SR1_EXIST  STD_OFF
#endif

/******************ADC6SR2 IRQ ********************************/

#ifdef ADC6SR2_ISR
#define IRQ_ADC6SR2_EXIST  STD_ON
#define IRQ_ADC6_SR2_PRIO    ADC6SR2_ISR_ISR_LEVEL
#define IRQ_ADC6_SR2_CAT     ADC6SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC6SR2_EXIST  STD_OFF
#endif

/******************ADC6SR3 IRQ ********************************/

#ifdef ADC6SR3_ISR
#define IRQ_ADC6SR3_EXIST  STD_ON
#define IRQ_ADC6_SR3_PRIO    ADC6SR3_ISR_ISR_LEVEL
#define IRQ_ADC6_SR3_CAT     ADC6SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC6SR3_EXIST  STD_OFF
#endif

/******************ADC7SR0 IRQ ********************************/

#ifdef ADC7SR0_ISR
#define IRQ_ADC7SR0_EXIST  STD_ON
#define IRQ_ADC7_SR0_PRIO    ADC7SR0_ISR_ISR_LEVEL
#define IRQ_ADC7_SR0_CAT     ADC7SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC7SR0_EXIST  STD_OFF
#endif

/******************ADC7SR1 IRQ ********************************/

#ifdef ADC7SR1_ISR
#define IRQ_ADC7SR1_EXIST  STD_ON
#define IRQ_ADC7_SR1_PRIO    ADC7SR1_ISR_ISR_LEVEL
#define IRQ_ADC7_SR1_CAT     ADC7SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC7SR1_EXIST  STD_OFF
#endif

/******************ADC7SR2 IRQ ********************************/

#ifdef ADC7SR2_ISR
#define IRQ_ADC7SR2_EXIST  STD_ON
#define IRQ_ADC7_SR2_PRIO    ADC7SR2_ISR_ISR_LEVEL
#define IRQ_ADC7_SR2_CAT     ADC7SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC7SR2_EXIST  STD_OFF
#endif

/******************ADC7SR3 IRQ ********************************/

#ifdef ADC7SR3_ISR
#define IRQ_ADC7SR3_EXIST  STD_ON
#define IRQ_ADC7_SR3_PRIO    ADC7SR3_ISR_ISR_LEVEL
#define IRQ_ADC7_SR3_CAT     ADC7SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC7SR3_EXIST  STD_OFF
#endif

/******************ADC8SR0 IRQ ********************************/

#ifdef ADC8SR0_ISR
#define IRQ_ADC8SR0_EXIST  STD_ON
#define IRQ_ADC8_SR0_PRIO    ADC8SR0_ISR_ISR_LEVEL
#define IRQ_ADC8_SR0_CAT     ADC8SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC8SR0_EXIST  STD_OFF
#endif

/******************ADC8SR1 IRQ ********************************/

#ifdef ADC8SR1_ISR
#define IRQ_ADC8SR1_EXIST  STD_ON
#define IRQ_ADC8_SR1_PRIO    ADC8SR1_ISR_ISR_LEVEL
#define IRQ_ADC8_SR1_CAT     ADC8SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC8SR1_EXIST  STD_OFF
#endif

/******************ADC8SR2 IRQ ********************************/

#ifdef ADC8SR2_ISR
#define IRQ_ADC8SR2_EXIST  STD_ON
#define IRQ_ADC8_SR2_PRIO    ADC8SR2_ISR_ISR_LEVEL
#define IRQ_ADC8_SR2_CAT     ADC8SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC8SR2_EXIST  STD_OFF
#endif

/******************ADC8SR3 IRQ ********************************/

#ifdef ADC8SR3_ISR
#define IRQ_ADC8SR3_EXIST  STD_ON
#define IRQ_ADC8_SR3_PRIO    ADC8SR3_ISR_ISR_LEVEL
#define IRQ_ADC8_SR3_CAT     ADC8SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC8SR3_EXIST  STD_OFF
#endif

/******************ADC9SR0 IRQ ********************************/

#ifdef ADC9SR0_ISR
#define IRQ_ADC9SR0_EXIST  STD_ON
#define IRQ_ADC9_SR0_PRIO    ADC9SR0_ISR_ISR_LEVEL
#define IRQ_ADC9_SR0_CAT     ADC9SR0_ISR_ISR_CATEGORY
#else
#define IRQ_ADC9SR0_EXIST  STD_OFF
#endif

/******************ADC9SR1 IRQ ********************************/

#ifdef ADC9SR1_ISR
#define IRQ_ADC9SR1_EXIST  STD_ON
#define IRQ_ADC9_SR1_PRIO    ADC9SR1_ISR_ISR_LEVEL
#define IRQ_ADC9_SR1_CAT     ADC9SR1_ISR_ISR_CATEGORY
#else
#define IRQ_ADC9SR1_EXIST  STD_OFF
#endif

/******************ADC9SR2 IRQ ********************************/

#ifdef ADC9SR2_ISR
#define IRQ_ADC9SR2_EXIST  STD_ON
#define IRQ_ADC9_SR2_PRIO    ADC9SR2_ISR_ISR_LEVEL
#define IRQ_ADC9_SR2_CAT     ADC9SR2_ISR_ISR_CATEGORY
#else
#define IRQ_ADC9SR2_EXIST  STD_OFF
#endif

/******************ADC9SR3 IRQ ********************************/

#ifdef ADC9SR3_ISR
#define IRQ_ADC9SR3_EXIST  STD_ON
#define IRQ_ADC9_SR3_PRIO    ADC9SR3_ISR_ISR_LEVEL
#define IRQ_ADC9_SR3_CAT     ADC9SR3_ISR_ISR_CATEGORY
#else
#define IRQ_ADC9SR3_EXIST  STD_OFF
#endif
#endif /* #ifndef ADC_IRQ_H */
