
#ifndef DSADC_IRQ_H
#define DSADC_IRQ_H

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

/******************DSADC0SRGA IRQ ********************************/

#ifdef DSADC0SRGA_ISR
#define IRQ_DSADC0SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA0_PRIO    DSADC0SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA0_CAT     DSADC0SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC0SRGA_EXIST  STD_OFF
#endif

/******************DSADC0SRGM IRQ ********************************/

#ifdef DSADC0SRGM_ISR
#define IRQ_DSADC0SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM0_PRIO    DSADC0SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM0_CAT     DSADC0SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC0SRGM_EXIST  STD_OFF
#endif

/******************DSADC10SRGA IRQ ********************************/

#ifdef DSADC10SRGA_ISR
#define IRQ_DSADC10SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA10_PRIO    DSADC10SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA10_CAT     DSADC10SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC10SRGA_EXIST  STD_OFF
#endif

/******************DSADC10SRGM IRQ ********************************/

#ifdef DSADC10SRGM_ISR
#define IRQ_DSADC10SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM10_PRIO    DSADC10SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM10_CAT     DSADC10SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC10SRGM_EXIST  STD_OFF
#endif

/******************DSADC11SRGA IRQ ********************************/

#ifdef DSADC11SRGA_ISR
#define IRQ_DSADC11SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA11_PRIO    DSADC11SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA11_CAT     DSADC11SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC11SRGA_EXIST  STD_OFF
#endif

/******************DSADC11SRGM IRQ ********************************/

#ifdef DSADC11SRGM_ISR
#define IRQ_DSADC11SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM11_PRIO    DSADC11SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM11_CAT     DSADC11SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC11SRGM_EXIST  STD_OFF
#endif

/******************DSADC12SRGA IRQ ********************************/

#ifdef DSADC12SRGA_ISR
#define IRQ_DSADC12SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA12_PRIO    DSADC12SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA12_CAT     DSADC12SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC12SRGA_EXIST  STD_OFF
#endif

/******************DSADC12SRGM IRQ ********************************/

#ifdef DSADC12SRGM_ISR
#define IRQ_DSADC12SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM12_PRIO    DSADC12SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM12_CAT     DSADC12SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC12SRGM_EXIST  STD_OFF
#endif

/******************DSADC13SRGA IRQ ********************************/

#ifdef DSADC13SRGA_ISR
#define IRQ_DSADC13SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA13_PRIO    DSADC13SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA13_CAT     DSADC13SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC13SRGA_EXIST  STD_OFF
#endif

/******************DSADC13SRGM IRQ ********************************/

#ifdef DSADC13SRGM_ISR
#define IRQ_DSADC13SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM13_PRIO    DSADC13SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM13_CAT     DSADC13SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC13SRGM_EXIST  STD_OFF
#endif

/******************DSADC1SRGA IRQ ********************************/

#ifdef DSADC1SRGA_ISR
#define IRQ_DSADC1SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA1_PRIO    DSADC1SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA1_CAT     DSADC1SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC1SRGA_EXIST  STD_OFF
#endif

/******************DSADC1SRGM IRQ ********************************/

#ifdef DSADC1SRGM_ISR
#define IRQ_DSADC1SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM1_PRIO    DSADC1SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM1_CAT     DSADC1SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC1SRGM_EXIST  STD_OFF
#endif

/******************DSADC2SRGA IRQ ********************************/

#ifdef DSADC2SRGA_ISR
#define IRQ_DSADC2SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA2_PRIO    DSADC2SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA2_CAT     DSADC2SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC2SRGA_EXIST  STD_OFF
#endif

/******************DSADC2SRGM IRQ ********************************/

#ifdef DSADC2SRGM_ISR
#define IRQ_DSADC2SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM2_PRIO    DSADC2SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM2_CAT     DSADC2SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC2SRGM_EXIST  STD_OFF
#endif

/******************DSADC3SRGA IRQ ********************************/

#ifdef DSADC3SRGA_ISR
#define IRQ_DSADC3SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA3_PRIO    DSADC3SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA3_CAT     DSADC3SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC3SRGA_EXIST  STD_OFF
#endif

/******************DSADC3SRGM IRQ ********************************/

#ifdef DSADC3SRGM_ISR
#define IRQ_DSADC3SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM3_PRIO    DSADC3SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM3_CAT     DSADC3SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC3SRGM_EXIST  STD_OFF
#endif

/******************DSADC4SRGA IRQ ********************************/

#ifdef DSADC4SRGA_ISR
#define IRQ_DSADC4SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA4_PRIO    DSADC4SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA4_CAT     DSADC4SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC4SRGA_EXIST  STD_OFF
#endif

/******************DSADC4SRGM IRQ ********************************/

#ifdef DSADC4SRGM_ISR
#define IRQ_DSADC4SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM4_PRIO    DSADC4SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM4_CAT     DSADC4SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC4SRGM_EXIST  STD_OFF
#endif

/******************DSADC5SRGA IRQ ********************************/

#ifdef DSADC5SRGA_ISR
#define IRQ_DSADC5SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA5_PRIO    DSADC5SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA5_CAT     DSADC5SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC5SRGA_EXIST  STD_OFF
#endif

/******************DSADC5SRGM IRQ ********************************/

#ifdef DSADC5SRGM_ISR
#define IRQ_DSADC5SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM5_PRIO    DSADC5SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM5_CAT     DSADC5SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC5SRGM_EXIST  STD_OFF
#endif

/******************DSADC6SRGA IRQ ********************************/

#ifdef DSADC6SRGA_ISR
#define IRQ_DSADC6SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA6_PRIO    DSADC6SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA6_CAT     DSADC6SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC6SRGA_EXIST  STD_OFF
#endif

/******************DSADC6SRGM IRQ ********************************/

#ifdef DSADC6SRGM_ISR
#define IRQ_DSADC6SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM6_PRIO    DSADC6SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM6_CAT     DSADC6SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC6SRGM_EXIST  STD_OFF
#endif

/******************DSADC7SRGA IRQ ********************************/

#ifdef DSADC7SRGA_ISR
#define IRQ_DSADC7SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA7_PRIO    DSADC7SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA7_CAT     DSADC7SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC7SRGA_EXIST  STD_OFF
#endif

/******************DSADC7SRGM IRQ ********************************/

#ifdef DSADC7SRGM_ISR
#define IRQ_DSADC7SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM7_PRIO    DSADC7SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM7_CAT     DSADC7SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC7SRGM_EXIST  STD_OFF
#endif

/******************DSADC8SRGA IRQ ********************************/

#ifdef DSADC8SRGA_ISR
#define IRQ_DSADC8SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA8_PRIO    DSADC8SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA8_CAT     DSADC8SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC8SRGA_EXIST  STD_OFF
#endif

/******************DSADC8SRGM IRQ ********************************/

#ifdef DSADC8SRGM_ISR
#define IRQ_DSADC8SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM8_PRIO    DSADC8SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM8_CAT     DSADC8SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC8SRGM_EXIST  STD_OFF
#endif

/******************DSADC9SRGA IRQ ********************************/

#ifdef DSADC9SRGA_ISR
#define IRQ_DSADC9SRGA_EXIST  STD_ON
#define IRQ_DSADC_SRA9_PRIO    DSADC9SRGA_ISR_ISR_LEVEL
#define IRQ_DSADC_SRA9_CAT     DSADC9SRGA_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC9SRGA_EXIST  STD_OFF
#endif

/******************DSADC9SRGM IRQ ********************************/

#ifdef DSADC9SRGM_ISR
#define IRQ_DSADC9SRGM_EXIST  STD_ON
#define IRQ_DSADC_SRM9_PRIO    DSADC9SRGM_ISR_ISR_LEVEL
#define IRQ_DSADC_SRM9_CAT     DSADC9SRGM_ISR_ISR_CATEGORY
#else
#define IRQ_DSADC9SRGM_EXIST  STD_OFF
#endif
#endif /* #ifndef DSADC_IRQ_H */
