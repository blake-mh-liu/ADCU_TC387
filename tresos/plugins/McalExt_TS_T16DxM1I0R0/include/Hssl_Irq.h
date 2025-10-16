
#ifndef HSSL_IRQ_H
#define HSSL_IRQ_H

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

/******************HSSL0_COK0 IRQ ********************************/

#ifdef HSSL0_COK0_ISR
#define IRQ_HSSL0_COK0_EXIST  STD_ON
#define IRQ_HSSL0_COK0_PRIO    HSSL0_COK0_ISR_ISR_LEVEL
#define IRQ_HSSL0_COK0_CAT     HSSL0_COK0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_COK0_EXIST  STD_OFF
#endif

/******************HSSL0_COK1 IRQ ********************************/

#ifdef HSSL0_COK1_ISR
#define IRQ_HSSL0_COK1_EXIST  STD_ON
#define IRQ_HSSL0_COK1_PRIO    HSSL0_COK1_ISR_ISR_LEVEL
#define IRQ_HSSL0_COK1_CAT     HSSL0_COK1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_COK1_EXIST  STD_OFF
#endif

/******************HSSL0_COK2 IRQ ********************************/

#ifdef HSSL0_COK2_ISR
#define IRQ_HSSL0_COK2_EXIST  STD_ON
#define IRQ_HSSL0_COK2_PRIO    HSSL0_COK2_ISR_ISR_LEVEL
#define IRQ_HSSL0_COK2_CAT     HSSL0_COK2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_COK2_EXIST  STD_OFF
#endif

/******************HSSL0_COK3 IRQ ********************************/

#ifdef HSSL0_COK3_ISR
#define IRQ_HSSL0_COK3_EXIST  STD_ON
#define IRQ_HSSL0_COK3_PRIO    HSSL0_COK3_ISR_ISR_LEVEL
#define IRQ_HSSL0_COK3_CAT     HSSL0_COK3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_COK3_EXIST  STD_OFF
#endif

/******************HSSL0_ERR0 IRQ ********************************/

#ifdef HSSL0_ERR0_ISR
#define IRQ_HSSL0_ERR0_EXIST  STD_ON
#define IRQ_HSSL0_ERR0_PRIO    HSSL0_ERR0_ISR_ISR_LEVEL
#define IRQ_HSSL0_ERR0_CAT     HSSL0_ERR0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_ERR0_EXIST  STD_OFF
#endif

/******************HSSL0_ERR1 IRQ ********************************/

#ifdef HSSL0_ERR1_ISR
#define IRQ_HSSL0_ERR1_EXIST  STD_ON
#define IRQ_HSSL0_ERR1_PRIO    HSSL0_ERR1_ISR_ISR_LEVEL
#define IRQ_HSSL0_ERR1_CAT     HSSL0_ERR1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_ERR1_EXIST  STD_OFF
#endif

/******************HSSL0_ERR2 IRQ ********************************/

#ifdef HSSL0_ERR2_ISR
#define IRQ_HSSL0_ERR2_EXIST  STD_ON
#define IRQ_HSSL0_ERR2_PRIO    HSSL0_ERR2_ISR_ISR_LEVEL
#define IRQ_HSSL0_ERR2_CAT     HSSL0_ERR2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_ERR2_EXIST  STD_OFF
#endif

/******************HSSL0_ERR3 IRQ ********************************/

#ifdef HSSL0_ERR3_ISR
#define IRQ_HSSL0_ERR3_EXIST  STD_ON
#define IRQ_HSSL0_ERR3_PRIO    HSSL0_ERR3_ISR_ISR_LEVEL
#define IRQ_HSSL0_ERR3_CAT     HSSL0_ERR3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_ERR3_EXIST  STD_OFF
#endif

/******************HSSL0_EXI0 IRQ ********************************/

#ifdef HSSL0_EXI0_ISR
#define IRQ_HSSL0_EXI0_EXIST  STD_ON
#define IRQ_HSSL0_EXI0_PRIO    HSSL0_EXI0_ISR_ISR_LEVEL
#define IRQ_HSSL0_EXI0_CAT     HSSL0_EXI0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_EXI0_EXIST  STD_OFF
#endif

/******************HSSL0_RDI0 IRQ ********************************/

#ifdef HSSL0_RDI0_ISR
#define IRQ_HSSL0_RDI0_EXIST  STD_ON
#define IRQ_HSSL0_RDI0_PRIO    HSSL0_RDI0_ISR_ISR_LEVEL
#define IRQ_HSSL0_RDI0_CAT     HSSL0_RDI0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_RDI0_EXIST  STD_OFF
#endif

/******************HSSL0_RDI1 IRQ ********************************/

#ifdef HSSL0_RDI1_ISR
#define IRQ_HSSL0_RDI1_EXIST  STD_ON
#define IRQ_HSSL0_RDI1_PRIO    HSSL0_RDI1_ISR_ISR_LEVEL
#define IRQ_HSSL0_RDI1_CAT     HSSL0_RDI1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_RDI1_EXIST  STD_OFF
#endif

/******************HSSL0_RDI2 IRQ ********************************/

#ifdef HSSL0_RDI2_ISR
#define IRQ_HSSL0_RDI2_EXIST  STD_ON
#define IRQ_HSSL0_RDI2_PRIO    HSSL0_RDI2_ISR_ISR_LEVEL
#define IRQ_HSSL0_RDI2_CAT     HSSL0_RDI2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_RDI2_EXIST  STD_OFF
#endif

/******************HSSL0_RDI3 IRQ ********************************/

#ifdef HSSL0_RDI3_ISR
#define IRQ_HSSL0_RDI3_EXIST  STD_ON
#define IRQ_HSSL0_RDI3_PRIO    HSSL0_RDI3_ISR_ISR_LEVEL
#define IRQ_HSSL0_RDI3_CAT     HSSL0_RDI3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_RDI3_EXIST  STD_OFF
#endif

/******************HSSL0_TRG0 IRQ ********************************/

#ifdef HSSL0_TRG0_ISR
#define IRQ_HSSL0_TRG0_EXIST  STD_ON
#define IRQ_HSSL0_TRG0_PRIO    HSSL0_TRG0_ISR_ISR_LEVEL
#define IRQ_HSSL0_TRG0_CAT     HSSL0_TRG0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_TRG0_EXIST  STD_OFF
#endif

/******************HSSL0_TRG1 IRQ ********************************/

#ifdef HSSL0_TRG1_ISR
#define IRQ_HSSL0_TRG1_EXIST  STD_ON
#define IRQ_HSSL0_TRG1_PRIO    HSSL0_TRG1_ISR_ISR_LEVEL
#define IRQ_HSSL0_TRG1_CAT     HSSL0_TRG1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_TRG1_EXIST  STD_OFF
#endif

/******************HSSL0_TRG2 IRQ ********************************/

#ifdef HSSL0_TRG2_ISR
#define IRQ_HSSL0_TRG2_EXIST  STD_ON
#define IRQ_HSSL0_TRG2_PRIO    HSSL0_TRG2_ISR_ISR_LEVEL
#define IRQ_HSSL0_TRG2_CAT     HSSL0_TRG2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_TRG2_EXIST  STD_OFF
#endif

/******************HSSL0_TRG3 IRQ ********************************/

#ifdef HSSL0_TRG3_ISR
#define IRQ_HSSL0_TRG3_EXIST  STD_ON
#define IRQ_HSSL0_TRG3_PRIO    HSSL0_TRG3_ISR_ISR_LEVEL
#define IRQ_HSSL0_TRG3_CAT     HSSL0_TRG3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL0_TRG3_EXIST  STD_OFF
#endif

/******************HSSL1_COK0 IRQ ********************************/

#ifdef HSSL1_COK0_ISR
#define IRQ_HSSL1_COK0_EXIST  STD_ON
#define IRQ_HSSL1_COK0_PRIO    HSSL1_COK0_ISR_ISR_LEVEL
#define IRQ_HSSL1_COK0_CAT     HSSL1_COK0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_COK0_EXIST  STD_OFF
#endif

/******************HSSL1_COK1 IRQ ********************************/

#ifdef HSSL1_COK1_ISR
#define IRQ_HSSL1_COK1_EXIST  STD_ON
#define IRQ_HSSL1_COK1_PRIO    HSSL1_COK1_ISR_ISR_LEVEL
#define IRQ_HSSL1_COK1_CAT     HSSL1_COK1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_COK1_EXIST  STD_OFF
#endif

/******************HSSL1_COK2 IRQ ********************************/

#ifdef HSSL1_COK2_ISR
#define IRQ_HSSL1_COK2_EXIST  STD_ON
#define IRQ_HSSL1_COK2_PRIO    HSSL1_COK2_ISR_ISR_LEVEL
#define IRQ_HSSL1_COK2_CAT     HSSL1_COK2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_COK2_EXIST  STD_OFF
#endif

/******************HSSL1_COK3 IRQ ********************************/

#ifdef HSSL1_COK3_ISR
#define IRQ_HSSL1_COK3_EXIST  STD_ON
#define IRQ_HSSL1_COK3_PRIO    HSSL1_COK3_ISR_ISR_LEVEL
#define IRQ_HSSL1_COK3_CAT     HSSL1_COK3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_COK3_EXIST  STD_OFF
#endif

/******************HSSL1_ERR0 IRQ ********************************/

#ifdef HSSL1_ERR0_ISR
#define IRQ_HSSL1_ERR0_EXIST  STD_ON
#define IRQ_HSSL1_ERR0_PRIO    HSSL1_ERR0_ISR_ISR_LEVEL
#define IRQ_HSSL1_ERR0_CAT     HSSL1_ERR0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_ERR0_EXIST  STD_OFF
#endif

/******************HSSL1_ERR1 IRQ ********************************/

#ifdef HSSL1_ERR1_ISR
#define IRQ_HSSL1_ERR1_EXIST  STD_ON
#define IRQ_HSSL1_ERR1_PRIO    HSSL1_ERR1_ISR_ISR_LEVEL
#define IRQ_HSSL1_ERR1_CAT     HSSL1_ERR1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_ERR1_EXIST  STD_OFF
#endif

/******************HSSL1_ERR2 IRQ ********************************/

#ifdef HSSL1_ERR2_ISR
#define IRQ_HSSL1_ERR2_EXIST  STD_ON
#define IRQ_HSSL1_ERR2_PRIO    HSSL1_ERR2_ISR_ISR_LEVEL
#define IRQ_HSSL1_ERR2_CAT     HSSL1_ERR2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_ERR2_EXIST  STD_OFF
#endif

/******************HSSL1_ERR3 IRQ ********************************/

#ifdef HSSL1_ERR3_ISR
#define IRQ_HSSL1_ERR3_EXIST  STD_ON
#define IRQ_HSSL1_ERR3_PRIO    HSSL1_ERR3_ISR_ISR_LEVEL
#define IRQ_HSSL1_ERR3_CAT     HSSL1_ERR3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_ERR3_EXIST  STD_OFF
#endif

/******************HSSL1_EXI0 IRQ ********************************/

#ifdef HSSL1_EXI0_ISR
#define IRQ_HSSL1_EXI0_EXIST  STD_ON
#define IRQ_HSSL1_EXI0_PRIO    HSSL1_EXI0_ISR_ISR_LEVEL
#define IRQ_HSSL1_EXI0_CAT     HSSL1_EXI0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_EXI0_EXIST  STD_OFF
#endif

/******************HSSL1_RDI0 IRQ ********************************/

#ifdef HSSL1_RDI0_ISR
#define IRQ_HSSL1_RDI0_EXIST  STD_ON
#define IRQ_HSSL1_RDI0_PRIO    HSSL1_RDI0_ISR_ISR_LEVEL
#define IRQ_HSSL1_RDI0_CAT     HSSL1_RDI0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_RDI0_EXIST  STD_OFF
#endif

/******************HSSL1_RDI1 IRQ ********************************/

#ifdef HSSL1_RDI1_ISR
#define IRQ_HSSL1_RDI1_EXIST  STD_ON
#define IRQ_HSSL1_RDI1_PRIO    HSSL1_RDI1_ISR_ISR_LEVEL
#define IRQ_HSSL1_RDI1_CAT     HSSL1_RDI1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_RDI1_EXIST  STD_OFF
#endif

/******************HSSL1_RDI2 IRQ ********************************/

#ifdef HSSL1_RDI2_ISR
#define IRQ_HSSL1_RDI2_EXIST  STD_ON
#define IRQ_HSSL1_RDI2_PRIO    HSSL1_RDI2_ISR_ISR_LEVEL
#define IRQ_HSSL1_RDI2_CAT     HSSL1_RDI2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_RDI2_EXIST  STD_OFF
#endif

/******************HSSL1_RDI3 IRQ ********************************/

#ifdef HSSL1_RDI3_ISR
#define IRQ_HSSL1_RDI3_EXIST  STD_ON
#define IRQ_HSSL1_RDI3_PRIO    HSSL1_RDI3_ISR_ISR_LEVEL
#define IRQ_HSSL1_RDI3_CAT     HSSL1_RDI3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_RDI3_EXIST  STD_OFF
#endif

/******************HSSL1_TRG0 IRQ ********************************/

#ifdef HSSL1_TRG0_ISR
#define IRQ_HSSL1_TRG0_EXIST  STD_ON
#define IRQ_HSSL1_TRG0_PRIO    HSSL1_TRG0_ISR_ISR_LEVEL
#define IRQ_HSSL1_TRG0_CAT     HSSL1_TRG0_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_TRG0_EXIST  STD_OFF
#endif

/******************HSSL1_TRG1 IRQ ********************************/

#ifdef HSSL1_TRG1_ISR
#define IRQ_HSSL1_TRG1_EXIST  STD_ON
#define IRQ_HSSL1_TRG1_PRIO    HSSL1_TRG1_ISR_ISR_LEVEL
#define IRQ_HSSL1_TRG1_CAT     HSSL1_TRG1_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_TRG1_EXIST  STD_OFF
#endif

/******************HSSL1_TRG2 IRQ ********************************/

#ifdef HSSL1_TRG2_ISR
#define IRQ_HSSL1_TRG2_EXIST  STD_ON
#define IRQ_HSSL1_TRG2_PRIO    HSSL1_TRG2_ISR_ISR_LEVEL
#define IRQ_HSSL1_TRG2_CAT     HSSL1_TRG2_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_TRG2_EXIST  STD_OFF
#endif

/******************HSSL1_TRG3 IRQ ********************************/

#ifdef HSSL1_TRG3_ISR
#define IRQ_HSSL1_TRG3_EXIST  STD_ON
#define IRQ_HSSL1_TRG3_PRIO    HSSL1_TRG3_ISR_ISR_LEVEL
#define IRQ_HSSL1_TRG3_CAT     HSSL1_TRG3_ISR_ISR_CATEGORY
#else
#define IRQ_HSSL1_TRG3_EXIST  STD_OFF
#endif
#endif /* #ifndef HSSL_IRQ_H */
