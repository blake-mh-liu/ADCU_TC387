
#ifndef ETH_17_GETHMACV2_IRQ_H
#define ETH_17_GETHMACV2_IRQ_H

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

/******************ETHSR12 IRQ ********************************/

#ifdef ETHSR12_ISR
#define IRQ_ETHSR12_EXIST  STD_ON
#define IRQ_GETH1_SR2_PRIO    ETHSR12_ISR_ISR_LEVEL
#define IRQ_GETH1_SR2_CAT     ETHSR12_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR12_EXIST  STD_OFF
#endif

/******************ETHSR13 IRQ ********************************/

#ifdef ETHSR13_ISR
#define IRQ_ETHSR13_EXIST  STD_ON
#define IRQ_GETH1_SR3_PRIO    ETHSR13_ISR_ISR_LEVEL
#define IRQ_GETH1_SR3_CAT     ETHSR13_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR13_EXIST  STD_OFF
#endif

/******************ETHSR14 IRQ ********************************/

#ifdef ETHSR14_ISR
#define IRQ_ETHSR14_EXIST  STD_ON
#define IRQ_GETH1_SR4_PRIO    ETHSR14_ISR_ISR_LEVEL
#define IRQ_GETH1_SR4_CAT     ETHSR14_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR14_EXIST  STD_OFF
#endif

/******************ETHSR15 IRQ ********************************/

#ifdef ETHSR15_ISR
#define IRQ_ETHSR15_EXIST  STD_ON
#define IRQ_GETH1_SR5_PRIO    ETHSR15_ISR_ISR_LEVEL
#define IRQ_GETH1_SR5_CAT     ETHSR15_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR15_EXIST  STD_OFF
#endif

/******************ETHSR16 IRQ ********************************/

#ifdef ETHSR16_ISR
#define IRQ_ETHSR16_EXIST  STD_ON
#define IRQ_GETH1_SR6_PRIO    ETHSR16_ISR_ISR_LEVEL
#define IRQ_GETH1_SR6_CAT     ETHSR16_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR16_EXIST  STD_OFF
#endif

/******************ETHSR17 IRQ ********************************/

#ifdef ETHSR17_ISR
#define IRQ_ETHSR17_EXIST  STD_ON
#define IRQ_GETH1_SR7_PRIO    ETHSR17_ISR_ISR_LEVEL
#define IRQ_GETH1_SR7_CAT     ETHSR17_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR17_EXIST  STD_OFF
#endif

/******************ETHSR18 IRQ ********************************/

#ifdef ETHSR18_ISR
#define IRQ_ETHSR18_EXIST  STD_ON
#define IRQ_GETH1_SR8_PRIO    ETHSR18_ISR_ISR_LEVEL
#define IRQ_GETH1_SR8_CAT     ETHSR18_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR18_EXIST  STD_OFF
#endif

/******************ETHSR19 IRQ ********************************/

#ifdef ETHSR19_ISR
#define IRQ_ETHSR19_EXIST  STD_ON
#define IRQ_GETH1_SR9_PRIO    ETHSR19_ISR_ISR_LEVEL
#define IRQ_GETH1_SR9_CAT     ETHSR19_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR19_EXIST  STD_OFF
#endif

/******************ETHSR2 IRQ ********************************/

#ifdef ETHSR2_ISR
#define IRQ_ETHSR2_EXIST  STD_ON
#define IRQ_GETH_SR2_PRIO    ETHSR2_ISR_ISR_LEVEL
#define IRQ_GETH_SR2_CAT     ETHSR2_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR2_EXIST  STD_OFF
#endif

/******************ETHSR3 IRQ ********************************/

#ifdef ETHSR3_ISR
#define IRQ_ETHSR3_EXIST  STD_ON
#define IRQ_GETH_SR3_PRIO    ETHSR3_ISR_ISR_LEVEL
#define IRQ_GETH_SR3_CAT     ETHSR3_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR3_EXIST  STD_OFF
#endif

/******************ETHSR4 IRQ ********************************/

#ifdef ETHSR4_ISR
#define IRQ_ETHSR4_EXIST  STD_ON
#define IRQ_GETH_SR4_PRIO    ETHSR4_ISR_ISR_LEVEL
#define IRQ_GETH_SR4_CAT     ETHSR4_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR4_EXIST  STD_OFF
#endif

/******************ETHSR5 IRQ ********************************/

#ifdef ETHSR5_ISR
#define IRQ_ETHSR5_EXIST  STD_ON
#define IRQ_GETH_SR5_PRIO    ETHSR5_ISR_ISR_LEVEL
#define IRQ_GETH_SR5_CAT     ETHSR5_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR5_EXIST  STD_OFF
#endif

/******************ETHSR6 IRQ ********************************/

#ifdef ETHSR6_ISR
#define IRQ_ETHSR6_EXIST  STD_ON
#define IRQ_GETH_SR6_PRIO    ETHSR6_ISR_ISR_LEVEL
#define IRQ_GETH_SR6_CAT     ETHSR6_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR6_EXIST  STD_OFF
#endif

/******************ETHSR7 IRQ ********************************/

#ifdef ETHSR7_ISR
#define IRQ_ETHSR7_EXIST  STD_ON
#define IRQ_GETH_SR7_PRIO    ETHSR7_ISR_ISR_LEVEL
#define IRQ_GETH_SR7_CAT     ETHSR7_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR7_EXIST  STD_OFF
#endif

/******************ETHSR8 IRQ ********************************/

#ifdef ETHSR8_ISR
#define IRQ_ETHSR8_EXIST  STD_ON
#define IRQ_GETH_SR8_PRIO    ETHSR8_ISR_ISR_LEVEL
#define IRQ_GETH_SR8_CAT     ETHSR8_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR8_EXIST  STD_OFF
#endif

/******************ETHSR9 IRQ ********************************/

#ifdef ETHSR9_ISR
#define IRQ_ETHSR9_EXIST  STD_ON
#define IRQ_GETH_SR9_PRIO    ETHSR9_ISR_ISR_LEVEL
#define IRQ_GETH_SR9_CAT     ETHSR9_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR9_EXIST  STD_OFF
#endif
#endif /* #ifndef ETH_17_GETHMACV2_IRQ_H */
