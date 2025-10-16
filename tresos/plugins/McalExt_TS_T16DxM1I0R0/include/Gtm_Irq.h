
#ifndef GTM_IRQ_H
#define GTM_IRQ_H

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

/******************GTMATOM0SR0 IRQ ********************************/

#ifdef GTMATOM0SR0_ISR
#define IRQ_GTMATOM0SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM0_SR0_PRIO    GTMATOM0SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM0_SR0_CAT     GTMATOM0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM0SR0_EXIST  STD_OFF
#endif

/******************GTMATOM0SR1 IRQ ********************************/

#ifdef GTMATOM0SR1_ISR
#define IRQ_GTMATOM0SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM0_SR1_PRIO    GTMATOM0SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM0_SR1_CAT     GTMATOM0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM0SR1_EXIST  STD_OFF
#endif

/******************GTMATOM0SR2 IRQ ********************************/

#ifdef GTMATOM0SR2_ISR
#define IRQ_GTMATOM0SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM0_SR2_PRIO    GTMATOM0SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM0_SR2_CAT     GTMATOM0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM0SR2_EXIST  STD_OFF
#endif

/******************GTMATOM0SR3 IRQ ********************************/

#ifdef GTMATOM0SR3_ISR
#define IRQ_GTMATOM0SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM0_SR3_PRIO    GTMATOM0SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM0_SR3_CAT     GTMATOM0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM0SR3_EXIST  STD_OFF
#endif

/******************GTMATOM10SR0 IRQ ********************************/

#ifdef GTMATOM10SR0_ISR
#define IRQ_GTMATOM10SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM10_SR0_PRIO    GTMATOM10SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM10_SR0_CAT     GTMATOM10SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM10SR0_EXIST  STD_OFF
#endif

/******************GTMATOM10SR1 IRQ ********************************/

#ifdef GTMATOM10SR1_ISR
#define IRQ_GTMATOM10SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM10_SR1_PRIO    GTMATOM10SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM10_SR1_CAT     GTMATOM10SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM10SR1_EXIST  STD_OFF
#endif

/******************GTMATOM10SR2 IRQ ********************************/

#ifdef GTMATOM10SR2_ISR
#define IRQ_GTMATOM10SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM10_SR2_PRIO    GTMATOM10SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM10_SR2_CAT     GTMATOM10SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM10SR2_EXIST  STD_OFF
#endif

/******************GTMATOM10SR3 IRQ ********************************/

#ifdef GTMATOM10SR3_ISR
#define IRQ_GTMATOM10SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM10_SR3_PRIO    GTMATOM10SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM10_SR3_CAT     GTMATOM10SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM10SR3_EXIST  STD_OFF
#endif

/******************GTMATOM11SR0 IRQ ********************************/

#ifdef GTMATOM11SR0_ISR
#define IRQ_GTMATOM11SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM11_SR0_PRIO    GTMATOM11SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM11_SR0_CAT     GTMATOM11SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM11SR0_EXIST  STD_OFF
#endif

/******************GTMATOM11SR1 IRQ ********************************/

#ifdef GTMATOM11SR1_ISR
#define IRQ_GTMATOM11SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM11_SR1_PRIO    GTMATOM11SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM11_SR1_CAT     GTMATOM11SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM11SR1_EXIST  STD_OFF
#endif

/******************GTMATOM11SR2 IRQ ********************************/

#ifdef GTMATOM11SR2_ISR
#define IRQ_GTMATOM11SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM11_SR2_PRIO    GTMATOM11SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM11_SR2_CAT     GTMATOM11SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM11SR2_EXIST  STD_OFF
#endif

/******************GTMATOM11SR3 IRQ ********************************/

#ifdef GTMATOM11SR3_ISR
#define IRQ_GTMATOM11SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM11_SR3_PRIO    GTMATOM11SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM11_SR3_CAT     GTMATOM11SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM11SR3_EXIST  STD_OFF
#endif

/******************GTMATOM1SR0 IRQ ********************************/

#ifdef GTMATOM1SR0_ISR
#define IRQ_GTMATOM1SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM1_SR0_PRIO    GTMATOM1SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM1_SR0_CAT     GTMATOM1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM1SR0_EXIST  STD_OFF
#endif

/******************GTMATOM1SR1 IRQ ********************************/

#ifdef GTMATOM1SR1_ISR
#define IRQ_GTMATOM1SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM1_SR1_PRIO    GTMATOM1SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM1_SR1_CAT     GTMATOM1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM1SR1_EXIST  STD_OFF
#endif

/******************GTMATOM1SR2 IRQ ********************************/

#ifdef GTMATOM1SR2_ISR
#define IRQ_GTMATOM1SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM1_SR2_PRIO    GTMATOM1SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM1_SR2_CAT     GTMATOM1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM1SR2_EXIST  STD_OFF
#endif

/******************GTMATOM1SR3 IRQ ********************************/

#ifdef GTMATOM1SR3_ISR
#define IRQ_GTMATOM1SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM1_SR3_PRIO    GTMATOM1SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM1_SR3_CAT     GTMATOM1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM1SR3_EXIST  STD_OFF
#endif

/******************GTMATOM2SR0 IRQ ********************************/

#ifdef GTMATOM2SR0_ISR
#define IRQ_GTMATOM2SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM2_SR0_PRIO    GTMATOM2SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM2_SR0_CAT     GTMATOM2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM2SR0_EXIST  STD_OFF
#endif

/******************GTMATOM2SR1 IRQ ********************************/

#ifdef GTMATOM2SR1_ISR
#define IRQ_GTMATOM2SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM2_SR1_PRIO    GTMATOM2SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM2_SR1_CAT     GTMATOM2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM2SR1_EXIST  STD_OFF
#endif

/******************GTMATOM2SR2 IRQ ********************************/

#ifdef GTMATOM2SR2_ISR
#define IRQ_GTMATOM2SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM2_SR2_PRIO    GTMATOM2SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM2_SR2_CAT     GTMATOM2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM2SR2_EXIST  STD_OFF
#endif

/******************GTMATOM2SR3 IRQ ********************************/

#ifdef GTMATOM2SR3_ISR
#define IRQ_GTMATOM2SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM2_SR3_PRIO    GTMATOM2SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM2_SR3_CAT     GTMATOM2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM2SR3_EXIST  STD_OFF
#endif

/******************GTMATOM3SR0 IRQ ********************************/

#ifdef GTMATOM3SR0_ISR
#define IRQ_GTMATOM3SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM3_SR0_PRIO    GTMATOM3SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM3_SR0_CAT     GTMATOM3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM3SR0_EXIST  STD_OFF
#endif

/******************GTMATOM3SR1 IRQ ********************************/

#ifdef GTMATOM3SR1_ISR
#define IRQ_GTMATOM3SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM3_SR1_PRIO    GTMATOM3SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM3_SR1_CAT     GTMATOM3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM3SR1_EXIST  STD_OFF
#endif

/******************GTMATOM3SR2 IRQ ********************************/

#ifdef GTMATOM3SR2_ISR
#define IRQ_GTMATOM3SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM3_SR2_PRIO    GTMATOM3SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM3_SR2_CAT     GTMATOM3SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM3SR2_EXIST  STD_OFF
#endif

/******************GTMATOM3SR3 IRQ ********************************/

#ifdef GTMATOM3SR3_ISR
#define IRQ_GTMATOM3SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM3_SR3_PRIO    GTMATOM3SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM3_SR3_CAT     GTMATOM3SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM3SR3_EXIST  STD_OFF
#endif

/******************GTMATOM4SR0 IRQ ********************************/

#ifdef GTMATOM4SR0_ISR
#define IRQ_GTMATOM4SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM4_SR0_PRIO    GTMATOM4SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM4_SR0_CAT     GTMATOM4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM4SR0_EXIST  STD_OFF
#endif

/******************GTMATOM4SR1 IRQ ********************************/

#ifdef GTMATOM4SR1_ISR
#define IRQ_GTMATOM4SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM4_SR1_PRIO    GTMATOM4SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM4_SR1_CAT     GTMATOM4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM4SR1_EXIST  STD_OFF
#endif

/******************GTMATOM4SR2 IRQ ********************************/

#ifdef GTMATOM4SR2_ISR
#define IRQ_GTMATOM4SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM4_SR2_PRIO    GTMATOM4SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM4_SR2_CAT     GTMATOM4SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM4SR2_EXIST  STD_OFF
#endif

/******************GTMATOM4SR3 IRQ ********************************/

#ifdef GTMATOM4SR3_ISR
#define IRQ_GTMATOM4SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM4_SR3_PRIO    GTMATOM4SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM4_SR3_CAT     GTMATOM4SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM4SR3_EXIST  STD_OFF
#endif

/******************GTMATOM5SR0 IRQ ********************************/

#ifdef GTMATOM5SR0_ISR
#define IRQ_GTMATOM5SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM5_SR0_PRIO    GTMATOM5SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM5_SR0_CAT     GTMATOM5SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM5SR0_EXIST  STD_OFF
#endif

/******************GTMATOM5SR1 IRQ ********************************/

#ifdef GTMATOM5SR1_ISR
#define IRQ_GTMATOM5SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM5_SR1_PRIO    GTMATOM5SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM5_SR1_CAT     GTMATOM5SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM5SR1_EXIST  STD_OFF
#endif

/******************GTMATOM5SR2 IRQ ********************************/

#ifdef GTMATOM5SR2_ISR
#define IRQ_GTMATOM5SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM5_SR2_PRIO    GTMATOM5SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM5_SR2_CAT     GTMATOM5SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM5SR2_EXIST  STD_OFF
#endif

/******************GTMATOM5SR3 IRQ ********************************/

#ifdef GTMATOM5SR3_ISR
#define IRQ_GTMATOM5SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM5_SR3_PRIO    GTMATOM5SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM5_SR3_CAT     GTMATOM5SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM5SR3_EXIST  STD_OFF
#endif

/******************GTMATOM6SR0 IRQ ********************************/

#ifdef GTMATOM6SR0_ISR
#define IRQ_GTMATOM6SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM6_SR0_PRIO    GTMATOM6SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM6_SR0_CAT     GTMATOM6SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM6SR0_EXIST  STD_OFF
#endif

/******************GTMATOM6SR1 IRQ ********************************/

#ifdef GTMATOM6SR1_ISR
#define IRQ_GTMATOM6SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM6_SR1_PRIO    GTMATOM6SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM6_SR1_CAT     GTMATOM6SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM6SR1_EXIST  STD_OFF
#endif

/******************GTMATOM6SR2 IRQ ********************************/

#ifdef GTMATOM6SR2_ISR
#define IRQ_GTMATOM6SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM6_SR2_PRIO    GTMATOM6SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM6_SR2_CAT     GTMATOM6SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM6SR2_EXIST  STD_OFF
#endif

/******************GTMATOM6SR3 IRQ ********************************/

#ifdef GTMATOM6SR3_ISR
#define IRQ_GTMATOM6SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM6_SR3_PRIO    GTMATOM6SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM6_SR3_CAT     GTMATOM6SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM6SR3_EXIST  STD_OFF
#endif

/******************GTMATOM7SR0 IRQ ********************************/

#ifdef GTMATOM7SR0_ISR
#define IRQ_GTMATOM7SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM7_SR0_PRIO    GTMATOM7SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM7_SR0_CAT     GTMATOM7SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM7SR0_EXIST  STD_OFF
#endif

/******************GTMATOM7SR1 IRQ ********************************/

#ifdef GTMATOM7SR1_ISR
#define IRQ_GTMATOM7SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM7_SR1_PRIO    GTMATOM7SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM7_SR1_CAT     GTMATOM7SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM7SR1_EXIST  STD_OFF
#endif

/******************GTMATOM7SR2 IRQ ********************************/

#ifdef GTMATOM7SR2_ISR
#define IRQ_GTMATOM7SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM7_SR2_PRIO    GTMATOM7SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM7_SR2_CAT     GTMATOM7SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM7SR2_EXIST  STD_OFF
#endif

/******************GTMATOM7SR3 IRQ ********************************/

#ifdef GTMATOM7SR3_ISR
#define IRQ_GTMATOM7SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM7_SR3_PRIO    GTMATOM7SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM7_SR3_CAT     GTMATOM7SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM7SR3_EXIST  STD_OFF
#endif

/******************GTMATOM8SR0 IRQ ********************************/

#ifdef GTMATOM8SR0_ISR
#define IRQ_GTMATOM8SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM8_SR0_PRIO    GTMATOM8SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM8_SR0_CAT     GTMATOM8SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM8SR0_EXIST  STD_OFF
#endif

/******************GTMATOM8SR1 IRQ ********************************/

#ifdef GTMATOM8SR1_ISR
#define IRQ_GTMATOM8SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM8_SR1_PRIO    GTMATOM8SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM8_SR1_CAT     GTMATOM8SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM8SR1_EXIST  STD_OFF
#endif

/******************GTMATOM8SR2 IRQ ********************************/

#ifdef GTMATOM8SR2_ISR
#define IRQ_GTMATOM8SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM8_SR2_PRIO    GTMATOM8SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM8_SR2_CAT     GTMATOM8SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM8SR2_EXIST  STD_OFF
#endif

/******************GTMATOM8SR3 IRQ ********************************/

#ifdef GTMATOM8SR3_ISR
#define IRQ_GTMATOM8SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM8_SR3_PRIO    GTMATOM8SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM8_SR3_CAT     GTMATOM8SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM8SR3_EXIST  STD_OFF
#endif

/******************GTMATOM9SR0 IRQ ********************************/

#ifdef GTMATOM9SR0_ISR
#define IRQ_GTMATOM9SR0_EXIST  STD_ON
#define IRQ_GTM_ATOM9_SR0_PRIO    GTMATOM9SR0_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM9_SR0_CAT     GTMATOM9SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM9SR0_EXIST  STD_OFF
#endif

/******************GTMATOM9SR1 IRQ ********************************/

#ifdef GTMATOM9SR1_ISR
#define IRQ_GTMATOM9SR1_EXIST  STD_ON
#define IRQ_GTM_ATOM9_SR1_PRIO    GTMATOM9SR1_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM9_SR1_CAT     GTMATOM9SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM9SR1_EXIST  STD_OFF
#endif

/******************GTMATOM9SR2 IRQ ********************************/

#ifdef GTMATOM9SR2_ISR
#define IRQ_GTMATOM9SR2_EXIST  STD_ON
#define IRQ_GTM_ATOM9_SR2_PRIO    GTMATOM9SR2_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM9_SR2_CAT     GTMATOM9SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM9SR2_EXIST  STD_OFF
#endif

/******************GTMATOM9SR3 IRQ ********************************/

#ifdef GTMATOM9SR3_ISR
#define IRQ_GTMATOM9SR3_EXIST  STD_ON
#define IRQ_GTM_ATOM9_SR3_PRIO    GTMATOM9SR3_ISR_ISR_LEVEL
#define IRQ_GTM_ATOM9_SR3_CAT     GTMATOM9SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMATOM9SR3_EXIST  STD_OFF
#endif

/******************GTMTIM0SR0 IRQ ********************************/

#ifdef GTMTIM0SR0_ISR
#define IRQ_GTMTIM0SR0_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR0_PRIO    GTMTIM0SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR0_CAT     GTMTIM0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR0_EXIST  STD_OFF
#endif

/******************GTMTIM0SR1 IRQ ********************************/

#ifdef GTMTIM0SR1_ISR
#define IRQ_GTMTIM0SR1_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR1_PRIO    GTMTIM0SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR1_CAT     GTMTIM0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR1_EXIST  STD_OFF
#endif

/******************GTMTIM0SR2 IRQ ********************************/

#ifdef GTMTIM0SR2_ISR
#define IRQ_GTMTIM0SR2_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR2_PRIO    GTMTIM0SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR2_CAT     GTMTIM0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR2_EXIST  STD_OFF
#endif

/******************GTMTIM0SR3 IRQ ********************************/

#ifdef GTMTIM0SR3_ISR
#define IRQ_GTMTIM0SR3_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR3_PRIO    GTMTIM0SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR3_CAT     GTMTIM0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR3_EXIST  STD_OFF
#endif

/******************GTMTIM0SR4 IRQ ********************************/

#ifdef GTMTIM0SR4_ISR
#define IRQ_GTMTIM0SR4_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR4_PRIO    GTMTIM0SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR4_CAT     GTMTIM0SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR4_EXIST  STD_OFF
#endif

/******************GTMTIM0SR5 IRQ ********************************/

#ifdef GTMTIM0SR5_ISR
#define IRQ_GTMTIM0SR5_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR5_PRIO    GTMTIM0SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR5_CAT     GTMTIM0SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR5_EXIST  STD_OFF
#endif

/******************GTMTIM0SR6 IRQ ********************************/

#ifdef GTMTIM0SR6_ISR
#define IRQ_GTMTIM0SR6_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR6_PRIO    GTMTIM0SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR6_CAT     GTMTIM0SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR6_EXIST  STD_OFF
#endif

/******************GTMTIM0SR7 IRQ ********************************/

#ifdef GTMTIM0SR7_ISR
#define IRQ_GTMTIM0SR7_EXIST  STD_ON
#define IRQ_GTM_TIM0_SR7_PRIO    GTMTIM0SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM0_SR7_CAT     GTMTIM0SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM0SR7_EXIST  STD_OFF
#endif

/******************GTMTIM1SR0 IRQ ********************************/

#ifdef GTMTIM1SR0_ISR
#define IRQ_GTMTIM1SR0_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR0_PRIO    GTMTIM1SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR0_CAT     GTMTIM1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR0_EXIST  STD_OFF
#endif

/******************GTMTIM1SR1 IRQ ********************************/

#ifdef GTMTIM1SR1_ISR
#define IRQ_GTMTIM1SR1_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR1_PRIO    GTMTIM1SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR1_CAT     GTMTIM1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR1_EXIST  STD_OFF
#endif

/******************GTMTIM1SR2 IRQ ********************************/

#ifdef GTMTIM1SR2_ISR
#define IRQ_GTMTIM1SR2_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR2_PRIO    GTMTIM1SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR2_CAT     GTMTIM1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR2_EXIST  STD_OFF
#endif

/******************GTMTIM1SR3 IRQ ********************************/

#ifdef GTMTIM1SR3_ISR
#define IRQ_GTMTIM1SR3_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR3_PRIO    GTMTIM1SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR3_CAT     GTMTIM1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR3_EXIST  STD_OFF
#endif

/******************GTMTIM1SR4 IRQ ********************************/

#ifdef GTMTIM1SR4_ISR
#define IRQ_GTMTIM1SR4_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR4_PRIO    GTMTIM1SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR4_CAT     GTMTIM1SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR4_EXIST  STD_OFF
#endif

/******************GTMTIM1SR5 IRQ ********************************/

#ifdef GTMTIM1SR5_ISR
#define IRQ_GTMTIM1SR5_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR5_PRIO    GTMTIM1SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR5_CAT     GTMTIM1SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR5_EXIST  STD_OFF
#endif

/******************GTMTIM1SR6 IRQ ********************************/

#ifdef GTMTIM1SR6_ISR
#define IRQ_GTMTIM1SR6_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR6_PRIO    GTMTIM1SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR6_CAT     GTMTIM1SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR6_EXIST  STD_OFF
#endif

/******************GTMTIM1SR7 IRQ ********************************/

#ifdef GTMTIM1SR7_ISR
#define IRQ_GTMTIM1SR7_EXIST  STD_ON
#define IRQ_GTM_TIM1_SR7_PRIO    GTMTIM1SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM1_SR7_CAT     GTMTIM1SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM1SR7_EXIST  STD_OFF
#endif

/******************GTMTIM2SR0 IRQ ********************************/

#ifdef GTMTIM2SR0_ISR
#define IRQ_GTMTIM2SR0_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR0_PRIO    GTMTIM2SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR0_CAT     GTMTIM2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR0_EXIST  STD_OFF
#endif

/******************GTMTIM2SR1 IRQ ********************************/

#ifdef GTMTIM2SR1_ISR
#define IRQ_GTMTIM2SR1_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR1_PRIO    GTMTIM2SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR1_CAT     GTMTIM2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR1_EXIST  STD_OFF
#endif

/******************GTMTIM2SR2 IRQ ********************************/

#ifdef GTMTIM2SR2_ISR
#define IRQ_GTMTIM2SR2_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR2_PRIO    GTMTIM2SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR2_CAT     GTMTIM2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR2_EXIST  STD_OFF
#endif

/******************GTMTIM2SR3 IRQ ********************************/

#ifdef GTMTIM2SR3_ISR
#define IRQ_GTMTIM2SR3_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR3_PRIO    GTMTIM2SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR3_CAT     GTMTIM2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR3_EXIST  STD_OFF
#endif

/******************GTMTIM2SR4 IRQ ********************************/

#ifdef GTMTIM2SR4_ISR
#define IRQ_GTMTIM2SR4_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR4_PRIO    GTMTIM2SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR4_CAT     GTMTIM2SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR4_EXIST  STD_OFF
#endif

/******************GTMTIM2SR5 IRQ ********************************/

#ifdef GTMTIM2SR5_ISR
#define IRQ_GTMTIM2SR5_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR5_PRIO    GTMTIM2SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR5_CAT     GTMTIM2SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR5_EXIST  STD_OFF
#endif

/******************GTMTIM2SR6 IRQ ********************************/

#ifdef GTMTIM2SR6_ISR
#define IRQ_GTMTIM2SR6_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR6_PRIO    GTMTIM2SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR6_CAT     GTMTIM2SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR6_EXIST  STD_OFF
#endif

/******************GTMTIM2SR7 IRQ ********************************/

#ifdef GTMTIM2SR7_ISR
#define IRQ_GTMTIM2SR7_EXIST  STD_ON
#define IRQ_GTM_TIM2_SR7_PRIO    GTMTIM2SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM2_SR7_CAT     GTMTIM2SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM2SR7_EXIST  STD_OFF
#endif

/******************GTMTIM3SR0 IRQ ********************************/

#ifdef GTMTIM3SR0_ISR
#define IRQ_GTMTIM3SR0_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR0_PRIO    GTMTIM3SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR0_CAT     GTMTIM3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR0_EXIST  STD_OFF
#endif

/******************GTMTIM3SR1 IRQ ********************************/

#ifdef GTMTIM3SR1_ISR
#define IRQ_GTMTIM3SR1_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR1_PRIO    GTMTIM3SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR1_CAT     GTMTIM3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR1_EXIST  STD_OFF
#endif

/******************GTMTIM3SR2 IRQ ********************************/

#ifdef GTMTIM3SR2_ISR
#define IRQ_GTMTIM3SR2_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR2_PRIO    GTMTIM3SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR2_CAT     GTMTIM3SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR2_EXIST  STD_OFF
#endif

/******************GTMTIM3SR3 IRQ ********************************/

#ifdef GTMTIM3SR3_ISR
#define IRQ_GTMTIM3SR3_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR3_PRIO    GTMTIM3SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR3_CAT     GTMTIM3SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR3_EXIST  STD_OFF
#endif

/******************GTMTIM3SR4 IRQ ********************************/

#ifdef GTMTIM3SR4_ISR
#define IRQ_GTMTIM3SR4_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR4_PRIO    GTMTIM3SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR4_CAT     GTMTIM3SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR4_EXIST  STD_OFF
#endif

/******************GTMTIM3SR5 IRQ ********************************/

#ifdef GTMTIM3SR5_ISR
#define IRQ_GTMTIM3SR5_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR5_PRIO    GTMTIM3SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR5_CAT     GTMTIM3SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR5_EXIST  STD_OFF
#endif

/******************GTMTIM3SR6 IRQ ********************************/

#ifdef GTMTIM3SR6_ISR
#define IRQ_GTMTIM3SR6_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR6_PRIO    GTMTIM3SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR6_CAT     GTMTIM3SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR6_EXIST  STD_OFF
#endif

/******************GTMTIM3SR7 IRQ ********************************/

#ifdef GTMTIM3SR7_ISR
#define IRQ_GTMTIM3SR7_EXIST  STD_ON
#define IRQ_GTM_TIM3_SR7_PRIO    GTMTIM3SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM3_SR7_CAT     GTMTIM3SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM3SR7_EXIST  STD_OFF
#endif

/******************GTMTIM4SR0 IRQ ********************************/

#ifdef GTMTIM4SR0_ISR
#define IRQ_GTMTIM4SR0_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR0_PRIO    GTMTIM4SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR0_CAT     GTMTIM4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR0_EXIST  STD_OFF
#endif

/******************GTMTIM4SR1 IRQ ********************************/

#ifdef GTMTIM4SR1_ISR
#define IRQ_GTMTIM4SR1_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR1_PRIO    GTMTIM4SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR1_CAT     GTMTIM4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR1_EXIST  STD_OFF
#endif

/******************GTMTIM4SR2 IRQ ********************************/

#ifdef GTMTIM4SR2_ISR
#define IRQ_GTMTIM4SR2_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR2_PRIO    GTMTIM4SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR2_CAT     GTMTIM4SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR2_EXIST  STD_OFF
#endif

/******************GTMTIM4SR3 IRQ ********************************/

#ifdef GTMTIM4SR3_ISR
#define IRQ_GTMTIM4SR3_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR3_PRIO    GTMTIM4SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR3_CAT     GTMTIM4SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR3_EXIST  STD_OFF
#endif

/******************GTMTIM4SR4 IRQ ********************************/

#ifdef GTMTIM4SR4_ISR
#define IRQ_GTMTIM4SR4_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR4_PRIO    GTMTIM4SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR4_CAT     GTMTIM4SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR4_EXIST  STD_OFF
#endif

/******************GTMTIM4SR5 IRQ ********************************/

#ifdef GTMTIM4SR5_ISR
#define IRQ_GTMTIM4SR5_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR5_PRIO    GTMTIM4SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR5_CAT     GTMTIM4SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR5_EXIST  STD_OFF
#endif

/******************GTMTIM4SR6 IRQ ********************************/

#ifdef GTMTIM4SR6_ISR
#define IRQ_GTMTIM4SR6_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR6_PRIO    GTMTIM4SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR6_CAT     GTMTIM4SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR6_EXIST  STD_OFF
#endif

/******************GTMTIM4SR7 IRQ ********************************/

#ifdef GTMTIM4SR7_ISR
#define IRQ_GTMTIM4SR7_EXIST  STD_ON
#define IRQ_GTM_TIM4_SR7_PRIO    GTMTIM4SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM4_SR7_CAT     GTMTIM4SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM4SR7_EXIST  STD_OFF
#endif

/******************GTMTIM5SR0 IRQ ********************************/

#ifdef GTMTIM5SR0_ISR
#define IRQ_GTMTIM5SR0_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR0_PRIO    GTMTIM5SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR0_CAT     GTMTIM5SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR0_EXIST  STD_OFF
#endif

/******************GTMTIM5SR1 IRQ ********************************/

#ifdef GTMTIM5SR1_ISR
#define IRQ_GTMTIM5SR1_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR1_PRIO    GTMTIM5SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR1_CAT     GTMTIM5SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR1_EXIST  STD_OFF
#endif

/******************GTMTIM5SR2 IRQ ********************************/

#ifdef GTMTIM5SR2_ISR
#define IRQ_GTMTIM5SR2_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR2_PRIO    GTMTIM5SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR2_CAT     GTMTIM5SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR2_EXIST  STD_OFF
#endif

/******************GTMTIM5SR3 IRQ ********************************/

#ifdef GTMTIM5SR3_ISR
#define IRQ_GTMTIM5SR3_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR3_PRIO    GTMTIM5SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR3_CAT     GTMTIM5SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR3_EXIST  STD_OFF
#endif

/******************GTMTIM5SR4 IRQ ********************************/

#ifdef GTMTIM5SR4_ISR
#define IRQ_GTMTIM5SR4_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR4_PRIO    GTMTIM5SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR4_CAT     GTMTIM5SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR4_EXIST  STD_OFF
#endif

/******************GTMTIM5SR5 IRQ ********************************/

#ifdef GTMTIM5SR5_ISR
#define IRQ_GTMTIM5SR5_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR5_PRIO    GTMTIM5SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR5_CAT     GTMTIM5SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR5_EXIST  STD_OFF
#endif

/******************GTMTIM5SR6 IRQ ********************************/

#ifdef GTMTIM5SR6_ISR
#define IRQ_GTMTIM5SR6_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR6_PRIO    GTMTIM5SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR6_CAT     GTMTIM5SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR6_EXIST  STD_OFF
#endif

/******************GTMTIM5SR7 IRQ ********************************/

#ifdef GTMTIM5SR7_ISR
#define IRQ_GTMTIM5SR7_EXIST  STD_ON
#define IRQ_GTM_TIM5_SR7_PRIO    GTMTIM5SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM5_SR7_CAT     GTMTIM5SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM5SR7_EXIST  STD_OFF
#endif

/******************GTMTIM6SR0 IRQ ********************************/

#ifdef GTMTIM6SR0_ISR
#define IRQ_GTMTIM6SR0_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR0_PRIO    GTMTIM6SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR0_CAT     GTMTIM6SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR0_EXIST  STD_OFF
#endif

/******************GTMTIM6SR1 IRQ ********************************/

#ifdef GTMTIM6SR1_ISR
#define IRQ_GTMTIM6SR1_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR1_PRIO    GTMTIM6SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR1_CAT     GTMTIM6SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR1_EXIST  STD_OFF
#endif

/******************GTMTIM6SR2 IRQ ********************************/

#ifdef GTMTIM6SR2_ISR
#define IRQ_GTMTIM6SR2_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR2_PRIO    GTMTIM6SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR2_CAT     GTMTIM6SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR2_EXIST  STD_OFF
#endif

/******************GTMTIM6SR3 IRQ ********************************/

#ifdef GTMTIM6SR3_ISR
#define IRQ_GTMTIM6SR3_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR3_PRIO    GTMTIM6SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR3_CAT     GTMTIM6SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR3_EXIST  STD_OFF
#endif

/******************GTMTIM6SR4 IRQ ********************************/

#ifdef GTMTIM6SR4_ISR
#define IRQ_GTMTIM6SR4_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR4_PRIO    GTMTIM6SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR4_CAT     GTMTIM6SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR4_EXIST  STD_OFF
#endif

/******************GTMTIM6SR5 IRQ ********************************/

#ifdef GTMTIM6SR5_ISR
#define IRQ_GTMTIM6SR5_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR5_PRIO    GTMTIM6SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR5_CAT     GTMTIM6SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR5_EXIST  STD_OFF
#endif

/******************GTMTIM6SR6 IRQ ********************************/

#ifdef GTMTIM6SR6_ISR
#define IRQ_GTMTIM6SR6_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR6_PRIO    GTMTIM6SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR6_CAT     GTMTIM6SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR6_EXIST  STD_OFF
#endif

/******************GTMTIM6SR7 IRQ ********************************/

#ifdef GTMTIM6SR7_ISR
#define IRQ_GTMTIM6SR7_EXIST  STD_ON
#define IRQ_GTM_TIM6_SR7_PRIO    GTMTIM6SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM6_SR7_CAT     GTMTIM6SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM6SR7_EXIST  STD_OFF
#endif

/******************GTMTIM7SR0 IRQ ********************************/

#ifdef GTMTIM7SR0_ISR
#define IRQ_GTMTIM7SR0_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR0_PRIO    GTMTIM7SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR0_CAT     GTMTIM7SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR0_EXIST  STD_OFF
#endif

/******************GTMTIM7SR1 IRQ ********************************/

#ifdef GTMTIM7SR1_ISR
#define IRQ_GTMTIM7SR1_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR1_PRIO    GTMTIM7SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR1_CAT     GTMTIM7SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR1_EXIST  STD_OFF
#endif

/******************GTMTIM7SR2 IRQ ********************************/

#ifdef GTMTIM7SR2_ISR
#define IRQ_GTMTIM7SR2_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR2_PRIO    GTMTIM7SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR2_CAT     GTMTIM7SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR2_EXIST  STD_OFF
#endif

/******************GTMTIM7SR3 IRQ ********************************/

#ifdef GTMTIM7SR3_ISR
#define IRQ_GTMTIM7SR3_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR3_PRIO    GTMTIM7SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR3_CAT     GTMTIM7SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR3_EXIST  STD_OFF
#endif

/******************GTMTIM7SR4 IRQ ********************************/

#ifdef GTMTIM7SR4_ISR
#define IRQ_GTMTIM7SR4_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR4_PRIO    GTMTIM7SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR4_CAT     GTMTIM7SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR4_EXIST  STD_OFF
#endif

/******************GTMTIM7SR5 IRQ ********************************/

#ifdef GTMTIM7SR5_ISR
#define IRQ_GTMTIM7SR5_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR5_PRIO    GTMTIM7SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR5_CAT     GTMTIM7SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR5_EXIST  STD_OFF
#endif

/******************GTMTIM7SR6 IRQ ********************************/

#ifdef GTMTIM7SR6_ISR
#define IRQ_GTMTIM7SR6_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR6_PRIO    GTMTIM7SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR6_CAT     GTMTIM7SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR6_EXIST  STD_OFF
#endif

/******************GTMTIM7SR7 IRQ ********************************/

#ifdef GTMTIM7SR7_ISR
#define IRQ_GTMTIM7SR7_EXIST  STD_ON
#define IRQ_GTM_TIM7_SR7_PRIO    GTMTIM7SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TIM7_SR7_CAT     GTMTIM7SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTIM7SR7_EXIST  STD_OFF
#endif

/******************GTMTOM0SR0 IRQ ********************************/

#ifdef GTMTOM0SR0_ISR
#define IRQ_GTMTOM0SR0_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR0_PRIO    GTMTOM0SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR0_CAT     GTMTOM0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR0_EXIST  STD_OFF
#endif

/******************GTMTOM0SR1 IRQ ********************************/

#ifdef GTMTOM0SR1_ISR
#define IRQ_GTMTOM0SR1_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR1_PRIO    GTMTOM0SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR1_CAT     GTMTOM0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR1_EXIST  STD_OFF
#endif

/******************GTMTOM0SR2 IRQ ********************************/

#ifdef GTMTOM0SR2_ISR
#define IRQ_GTMTOM0SR2_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR2_PRIO    GTMTOM0SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR2_CAT     GTMTOM0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR2_EXIST  STD_OFF
#endif

/******************GTMTOM0SR3 IRQ ********************************/

#ifdef GTMTOM0SR3_ISR
#define IRQ_GTMTOM0SR3_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR3_PRIO    GTMTOM0SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR3_CAT     GTMTOM0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR3_EXIST  STD_OFF
#endif

/******************GTMTOM0SR4 IRQ ********************************/

#ifdef GTMTOM0SR4_ISR
#define IRQ_GTMTOM0SR4_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR4_PRIO    GTMTOM0SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR4_CAT     GTMTOM0SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR4_EXIST  STD_OFF
#endif

/******************GTMTOM0SR5 IRQ ********************************/

#ifdef GTMTOM0SR5_ISR
#define IRQ_GTMTOM0SR5_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR5_PRIO    GTMTOM0SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR5_CAT     GTMTOM0SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR5_EXIST  STD_OFF
#endif

/******************GTMTOM0SR6 IRQ ********************************/

#ifdef GTMTOM0SR6_ISR
#define IRQ_GTMTOM0SR6_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR6_PRIO    GTMTOM0SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR6_CAT     GTMTOM0SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR6_EXIST  STD_OFF
#endif

/******************GTMTOM0SR7 IRQ ********************************/

#ifdef GTMTOM0SR7_ISR
#define IRQ_GTMTOM0SR7_EXIST  STD_ON
#define IRQ_GTM_TOM0_SR7_PRIO    GTMTOM0SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM0_SR7_CAT     GTMTOM0SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM0SR7_EXIST  STD_OFF
#endif

/******************GTMTOM1SR0 IRQ ********************************/

#ifdef GTMTOM1SR0_ISR
#define IRQ_GTMTOM1SR0_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR0_PRIO    GTMTOM1SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR0_CAT     GTMTOM1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR0_EXIST  STD_OFF
#endif

/******************GTMTOM1SR1 IRQ ********************************/

#ifdef GTMTOM1SR1_ISR
#define IRQ_GTMTOM1SR1_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR1_PRIO    GTMTOM1SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR1_CAT     GTMTOM1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR1_EXIST  STD_OFF
#endif

/******************GTMTOM1SR2 IRQ ********************************/

#ifdef GTMTOM1SR2_ISR
#define IRQ_GTMTOM1SR2_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR2_PRIO    GTMTOM1SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR2_CAT     GTMTOM1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR2_EXIST  STD_OFF
#endif

/******************GTMTOM1SR3 IRQ ********************************/

#ifdef GTMTOM1SR3_ISR
#define IRQ_GTMTOM1SR3_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR3_PRIO    GTMTOM1SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR3_CAT     GTMTOM1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR3_EXIST  STD_OFF
#endif

/******************GTMTOM1SR4 IRQ ********************************/

#ifdef GTMTOM1SR4_ISR
#define IRQ_GTMTOM1SR4_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR4_PRIO    GTMTOM1SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR4_CAT     GTMTOM1SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR4_EXIST  STD_OFF
#endif

/******************GTMTOM1SR5 IRQ ********************************/

#ifdef GTMTOM1SR5_ISR
#define IRQ_GTMTOM1SR5_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR5_PRIO    GTMTOM1SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR5_CAT     GTMTOM1SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR5_EXIST  STD_OFF
#endif

/******************GTMTOM1SR6 IRQ ********************************/

#ifdef GTMTOM1SR6_ISR
#define IRQ_GTMTOM1SR6_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR6_PRIO    GTMTOM1SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR6_CAT     GTMTOM1SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR6_EXIST  STD_OFF
#endif

/******************GTMTOM1SR7 IRQ ********************************/

#ifdef GTMTOM1SR7_ISR
#define IRQ_GTMTOM1SR7_EXIST  STD_ON
#define IRQ_GTM_TOM1_SR7_PRIO    GTMTOM1SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM1_SR7_CAT     GTMTOM1SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM1SR7_EXIST  STD_OFF
#endif

/******************GTMTOM2SR0 IRQ ********************************/

#ifdef GTMTOM2SR0_ISR
#define IRQ_GTMTOM2SR0_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR0_PRIO    GTMTOM2SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR0_CAT     GTMTOM2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR0_EXIST  STD_OFF
#endif

/******************GTMTOM2SR1 IRQ ********************************/

#ifdef GTMTOM2SR1_ISR
#define IRQ_GTMTOM2SR1_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR1_PRIO    GTMTOM2SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR1_CAT     GTMTOM2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR1_EXIST  STD_OFF
#endif

/******************GTMTOM2SR2 IRQ ********************************/

#ifdef GTMTOM2SR2_ISR
#define IRQ_GTMTOM2SR2_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR2_PRIO    GTMTOM2SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR2_CAT     GTMTOM2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR2_EXIST  STD_OFF
#endif

/******************GTMTOM2SR3 IRQ ********************************/

#ifdef GTMTOM2SR3_ISR
#define IRQ_GTMTOM2SR3_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR3_PRIO    GTMTOM2SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR3_CAT     GTMTOM2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR3_EXIST  STD_OFF
#endif

/******************GTMTOM2SR4 IRQ ********************************/

#ifdef GTMTOM2SR4_ISR
#define IRQ_GTMTOM2SR4_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR4_PRIO    GTMTOM2SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR4_CAT     GTMTOM2SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR4_EXIST  STD_OFF
#endif

/******************GTMTOM2SR5 IRQ ********************************/

#ifdef GTMTOM2SR5_ISR
#define IRQ_GTMTOM2SR5_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR5_PRIO    GTMTOM2SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR5_CAT     GTMTOM2SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR5_EXIST  STD_OFF
#endif

/******************GTMTOM2SR6 IRQ ********************************/

#ifdef GTMTOM2SR6_ISR
#define IRQ_GTMTOM2SR6_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR6_PRIO    GTMTOM2SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR6_CAT     GTMTOM2SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR6_EXIST  STD_OFF
#endif

/******************GTMTOM2SR7 IRQ ********************************/

#ifdef GTMTOM2SR7_ISR
#define IRQ_GTMTOM2SR7_EXIST  STD_ON
#define IRQ_GTM_TOM2_SR7_PRIO    GTMTOM2SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM2_SR7_CAT     GTMTOM2SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM2SR7_EXIST  STD_OFF
#endif

/******************GTMTOM3SR0 IRQ ********************************/

#ifdef GTMTOM3SR0_ISR
#define IRQ_GTMTOM3SR0_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR0_PRIO    GTMTOM3SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR0_CAT     GTMTOM3SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR0_EXIST  STD_OFF
#endif

/******************GTMTOM3SR1 IRQ ********************************/

#ifdef GTMTOM3SR1_ISR
#define IRQ_GTMTOM3SR1_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR1_PRIO    GTMTOM3SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR1_CAT     GTMTOM3SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR1_EXIST  STD_OFF
#endif

/******************GTMTOM3SR2 IRQ ********************************/

#ifdef GTMTOM3SR2_ISR
#define IRQ_GTMTOM3SR2_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR2_PRIO    GTMTOM3SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR2_CAT     GTMTOM3SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR2_EXIST  STD_OFF
#endif

/******************GTMTOM3SR3 IRQ ********************************/

#ifdef GTMTOM3SR3_ISR
#define IRQ_GTMTOM3SR3_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR3_PRIO    GTMTOM3SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR3_CAT     GTMTOM3SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR3_EXIST  STD_OFF
#endif

/******************GTMTOM3SR4 IRQ ********************************/

#ifdef GTMTOM3SR4_ISR
#define IRQ_GTMTOM3SR4_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR4_PRIO    GTMTOM3SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR4_CAT     GTMTOM3SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR4_EXIST  STD_OFF
#endif

/******************GTMTOM3SR5 IRQ ********************************/

#ifdef GTMTOM3SR5_ISR
#define IRQ_GTMTOM3SR5_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR5_PRIO    GTMTOM3SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR5_CAT     GTMTOM3SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR5_EXIST  STD_OFF
#endif

/******************GTMTOM3SR6 IRQ ********************************/

#ifdef GTMTOM3SR6_ISR
#define IRQ_GTMTOM3SR6_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR6_PRIO    GTMTOM3SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR6_CAT     GTMTOM3SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR6_EXIST  STD_OFF
#endif

/******************GTMTOM3SR7 IRQ ********************************/

#ifdef GTMTOM3SR7_ISR
#define IRQ_GTMTOM3SR7_EXIST  STD_ON
#define IRQ_GTM_TOM3_SR7_PRIO    GTMTOM3SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM3_SR7_CAT     GTMTOM3SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM3SR7_EXIST  STD_OFF
#endif

/******************GTMTOM4SR0 IRQ ********************************/

#ifdef GTMTOM4SR0_ISR
#define IRQ_GTMTOM4SR0_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR0_PRIO    GTMTOM4SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR0_CAT     GTMTOM4SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR0_EXIST  STD_OFF
#endif

/******************GTMTOM4SR1 IRQ ********************************/

#ifdef GTMTOM4SR1_ISR
#define IRQ_GTMTOM4SR1_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR1_PRIO    GTMTOM4SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR1_CAT     GTMTOM4SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR1_EXIST  STD_OFF
#endif

/******************GTMTOM4SR2 IRQ ********************************/

#ifdef GTMTOM4SR2_ISR
#define IRQ_GTMTOM4SR2_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR2_PRIO    GTMTOM4SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR2_CAT     GTMTOM4SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR2_EXIST  STD_OFF
#endif

/******************GTMTOM4SR3 IRQ ********************************/

#ifdef GTMTOM4SR3_ISR
#define IRQ_GTMTOM4SR3_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR3_PRIO    GTMTOM4SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR3_CAT     GTMTOM4SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR3_EXIST  STD_OFF
#endif

/******************GTMTOM4SR4 IRQ ********************************/

#ifdef GTMTOM4SR4_ISR
#define IRQ_GTMTOM4SR4_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR4_PRIO    GTMTOM4SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR4_CAT     GTMTOM4SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR4_EXIST  STD_OFF
#endif

/******************GTMTOM4SR5 IRQ ********************************/

#ifdef GTMTOM4SR5_ISR
#define IRQ_GTMTOM4SR5_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR5_PRIO    GTMTOM4SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR5_CAT     GTMTOM4SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR5_EXIST  STD_OFF
#endif

/******************GTMTOM4SR6 IRQ ********************************/

#ifdef GTMTOM4SR6_ISR
#define IRQ_GTMTOM4SR6_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR6_PRIO    GTMTOM4SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR6_CAT     GTMTOM4SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR6_EXIST  STD_OFF
#endif

/******************GTMTOM4SR7 IRQ ********************************/

#ifdef GTMTOM4SR7_ISR
#define IRQ_GTMTOM4SR7_EXIST  STD_ON
#define IRQ_GTM_TOM4_SR7_PRIO    GTMTOM4SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM4_SR7_CAT     GTMTOM4SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM4SR7_EXIST  STD_OFF
#endif

/******************GTMTOM5SR0 IRQ ********************************/

#ifdef GTMTOM5SR0_ISR
#define IRQ_GTMTOM5SR0_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR0_PRIO    GTMTOM5SR0_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR0_CAT     GTMTOM5SR0_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR0_EXIST  STD_OFF
#endif

/******************GTMTOM5SR1 IRQ ********************************/

#ifdef GTMTOM5SR1_ISR
#define IRQ_GTMTOM5SR1_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR1_PRIO    GTMTOM5SR1_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR1_CAT     GTMTOM5SR1_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR1_EXIST  STD_OFF
#endif

/******************GTMTOM5SR2 IRQ ********************************/

#ifdef GTMTOM5SR2_ISR
#define IRQ_GTMTOM5SR2_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR2_PRIO    GTMTOM5SR2_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR2_CAT     GTMTOM5SR2_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR2_EXIST  STD_OFF
#endif

/******************GTMTOM5SR3 IRQ ********************************/

#ifdef GTMTOM5SR3_ISR
#define IRQ_GTMTOM5SR3_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR3_PRIO    GTMTOM5SR3_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR3_CAT     GTMTOM5SR3_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR3_EXIST  STD_OFF
#endif

/******************GTMTOM5SR4 IRQ ********************************/

#ifdef GTMTOM5SR4_ISR
#define IRQ_GTMTOM5SR4_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR4_PRIO    GTMTOM5SR4_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR4_CAT     GTMTOM5SR4_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR4_EXIST  STD_OFF
#endif

/******************GTMTOM5SR5 IRQ ********************************/

#ifdef GTMTOM5SR5_ISR
#define IRQ_GTMTOM5SR5_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR5_PRIO    GTMTOM5SR5_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR5_CAT     GTMTOM5SR5_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR5_EXIST  STD_OFF
#endif

/******************GTMTOM5SR6 IRQ ********************************/

#ifdef GTMTOM5SR6_ISR
#define IRQ_GTMTOM5SR6_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR6_PRIO    GTMTOM5SR6_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR6_CAT     GTMTOM5SR6_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR6_EXIST  STD_OFF
#endif

/******************GTMTOM5SR7 IRQ ********************************/

#ifdef GTMTOM5SR7_ISR
#define IRQ_GTMTOM5SR7_EXIST  STD_ON
#define IRQ_GTM_TOM5_SR7_PRIO    GTMTOM5SR7_ISR_ISR_LEVEL
#define IRQ_GTM_TOM5_SR7_CAT     GTMTOM5SR7_ISR_ISR_CATEGORY
#else
#define IRQ_GTMTOM5SR7_EXIST  STD_OFF
#endif
#endif /* #ifndef GTM_IRQ_H */
