
#ifndef I2C_IRQ_H
#define I2C_IRQ_H

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

/******************I2C0DTR IRQ ********************************/

#ifdef I2C0DTR_ISR
#define IRQ_I2C0DTR_EXIST  STD_ON
#define IRQ_I2C_DTR_SR0_PRIO    I2C0DTR_ISR_ISR_LEVEL
#define IRQ_I2C_DTR_SR0_CAT     I2C0DTR_ISR_ISR_CATEGORY
#else
#define IRQ_I2C0DTR_EXIST  STD_OFF
#endif

/******************I2C0E IRQ ********************************/

#ifdef I2C0E_ISR
#define IRQ_I2C0E_EXIST  STD_ON
#define IRQ_I2C_ERR_SR0_PRIO    I2C0E_ISR_ISR_LEVEL
#define IRQ_I2C_ERR_SR0_CAT     I2C0E_ISR_ISR_CATEGORY
#else
#define IRQ_I2C0E_EXIST  STD_OFF
#endif

/******************I2C0P IRQ ********************************/

#ifdef I2C0P_ISR
#define IRQ_I2C0P_EXIST  STD_ON
#define IRQ_I2C_P_SR0_PRIO    I2C0P_ISR_ISR_LEVEL
#define IRQ_I2C_P_SR0_CAT     I2C0P_ISR_ISR_CATEGORY
#else
#define IRQ_I2C0P_EXIST  STD_OFF
#endif

/******************I2C1DTR IRQ ********************************/

#ifdef I2C1DTR_ISR
#define IRQ_I2C1DTR_EXIST  STD_ON
#define IRQ_I2C_DTR_SR1_PRIO    I2C1DTR_ISR_ISR_LEVEL
#define IRQ_I2C_DTR_SR1_CAT     I2C1DTR_ISR_ISR_CATEGORY
#else
#define IRQ_I2C1DTR_EXIST  STD_OFF
#endif

/******************I2C1E IRQ ********************************/

#ifdef I2C1E_ISR
#define IRQ_I2C1E_EXIST  STD_ON
#define IRQ_I2C_ERR_SR1_PRIO    I2C1E_ISR_ISR_LEVEL
#define IRQ_I2C_ERR_SR1_CAT     I2C1E_ISR_ISR_CATEGORY
#else
#define IRQ_I2C1E_EXIST  STD_OFF
#endif

/******************I2C1P IRQ ********************************/

#ifdef I2C1P_ISR
#define IRQ_I2C1P_EXIST  STD_ON
#define IRQ_I2C_P_SR1_PRIO    I2C1P_ISR_ISR_LEVEL
#define IRQ_I2C_P_SR1_CAT     I2C1P_ISR_ISR_CATEGORY
#else
#define IRQ_I2C1P_EXIST  STD_OFF
#endif
#endif /* #ifndef I2C_IRQ_H */
