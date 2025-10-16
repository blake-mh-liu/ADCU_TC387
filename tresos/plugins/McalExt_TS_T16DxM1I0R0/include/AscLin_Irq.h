
#ifndef ASCLIN_IRQ_H
#define ASCLIN_IRQ_H

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

/******************ASCLIN0ERR IRQ ********************************/

#ifdef ASCLIN0ERR_ISR
#define IRQ_ASCLIN0ERR_EXIST  STD_ON
#define IRQ_ASCLIN0_ERR_PRIO    ASCLIN0ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN0_ERR_CAT     ASCLIN0ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN0ERR_EXIST  STD_OFF
#endif

/******************ASCLIN0RX IRQ ********************************/

#ifdef ASCLIN0RX_ISR
#define IRQ_ASCLIN0RX_EXIST  STD_ON
#define IRQ_ASCLIN0_RX_PRIO    ASCLIN0RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN0_RX_CAT     ASCLIN0RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN0RX_EXIST  STD_OFF
#endif

/******************ASCLIN0TX IRQ ********************************/

#ifdef ASCLIN0TX_ISR
#define IRQ_ASCLIN0TX_EXIST  STD_ON
#define IRQ_ASCLIN0_TX_PRIO    ASCLIN0TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN0_TX_CAT     ASCLIN0TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN0TX_EXIST  STD_OFF
#endif

/******************ASCLIN10ERR IRQ ********************************/

#ifdef ASCLIN10ERR_ISR
#define IRQ_ASCLIN10ERR_EXIST  STD_ON
#define IRQ_ASCLIN10_ERR_PRIO    ASCLIN10ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN10_ERR_CAT     ASCLIN10ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN10ERR_EXIST  STD_OFF
#endif

/******************ASCLIN10RX IRQ ********************************/

#ifdef ASCLIN10RX_ISR
#define IRQ_ASCLIN10RX_EXIST  STD_ON
#define IRQ_ASCLIN10_RX_PRIO    ASCLIN10RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN10_RX_CAT     ASCLIN10RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN10RX_EXIST  STD_OFF
#endif

/******************ASCLIN10TX IRQ ********************************/

#ifdef ASCLIN10TX_ISR
#define IRQ_ASCLIN10TX_EXIST  STD_ON
#define IRQ_ASCLIN10_TX_PRIO    ASCLIN10TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN10_TX_CAT     ASCLIN10TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN10TX_EXIST  STD_OFF
#endif

/******************ASCLIN11ERR IRQ ********************************/

#ifdef ASCLIN11ERR_ISR
#define IRQ_ASCLIN11ERR_EXIST  STD_ON
#define IRQ_ASCLIN11_ERR_PRIO    ASCLIN11ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN11_ERR_CAT     ASCLIN11ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN11ERR_EXIST  STD_OFF
#endif

/******************ASCLIN11RX IRQ ********************************/

#ifdef ASCLIN11RX_ISR
#define IRQ_ASCLIN11RX_EXIST  STD_ON
#define IRQ_ASCLIN11_RX_PRIO    ASCLIN11RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN11_RX_CAT     ASCLIN11RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN11RX_EXIST  STD_OFF
#endif

/******************ASCLIN11TX IRQ ********************************/

#ifdef ASCLIN11TX_ISR
#define IRQ_ASCLIN11TX_EXIST  STD_ON
#define IRQ_ASCLIN11_TX_PRIO    ASCLIN11TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN11_TX_CAT     ASCLIN11TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN11TX_EXIST  STD_OFF
#endif

/******************ASCLIN12ERR IRQ ********************************/

#ifdef ASCLIN12ERR_ISR
#define IRQ_ASCLIN12ERR_EXIST  STD_ON
#define IRQ_ASCLIN12_ERR_PRIO    ASCLIN12ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN12_ERR_CAT     ASCLIN12ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN12ERR_EXIST  STD_OFF
#endif

/******************ASCLIN12RX IRQ ********************************/

#ifdef ASCLIN12RX_ISR
#define IRQ_ASCLIN12RX_EXIST  STD_ON
#define IRQ_ASCLIN12_RX_PRIO    ASCLIN12RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN12_RX_CAT     ASCLIN12RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN12RX_EXIST  STD_OFF
#endif

/******************ASCLIN12TX IRQ ********************************/

#ifdef ASCLIN12TX_ISR
#define IRQ_ASCLIN12TX_EXIST  STD_ON
#define IRQ_ASCLIN12_TX_PRIO    ASCLIN12TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN12_TX_CAT     ASCLIN12TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN12TX_EXIST  STD_OFF
#endif

/******************ASCLIN13ERR IRQ ********************************/

#ifdef ASCLIN13ERR_ISR
#define IRQ_ASCLIN13ERR_EXIST  STD_ON
#define IRQ_ASCLIN13_ERR_PRIO    ASCLIN13ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN13_ERR_CAT     ASCLIN13ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN13ERR_EXIST  STD_OFF
#endif

/******************ASCLIN13RX IRQ ********************************/

#ifdef ASCLIN13RX_ISR
#define IRQ_ASCLIN13RX_EXIST  STD_ON
#define IRQ_ASCLIN13_RX_PRIO    ASCLIN13RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN13_RX_CAT     ASCLIN13RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN13RX_EXIST  STD_OFF
#endif

/******************ASCLIN13TX IRQ ********************************/

#ifdef ASCLIN13TX_ISR
#define IRQ_ASCLIN13TX_EXIST  STD_ON
#define IRQ_ASCLIN13_TX_PRIO    ASCLIN13TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN13_TX_CAT     ASCLIN13TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN13TX_EXIST  STD_OFF
#endif

/******************ASCLIN14ERR IRQ ********************************/

#ifdef ASCLIN14ERR_ISR
#define IRQ_ASCLIN14ERR_EXIST  STD_ON
#define IRQ_ASCLIN14_ERR_PRIO    ASCLIN14ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN14_ERR_CAT     ASCLIN14ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN14ERR_EXIST  STD_OFF
#endif

/******************ASCLIN14RX IRQ ********************************/

#ifdef ASCLIN14RX_ISR
#define IRQ_ASCLIN14RX_EXIST  STD_ON
#define IRQ_ASCLIN14_RX_PRIO    ASCLIN14RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN14_RX_CAT     ASCLIN14RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN14RX_EXIST  STD_OFF
#endif

/******************ASCLIN14TX IRQ ********************************/

#ifdef ASCLIN14TX_ISR
#define IRQ_ASCLIN14TX_EXIST  STD_ON
#define IRQ_ASCLIN14_TX_PRIO    ASCLIN14TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN14_TX_CAT     ASCLIN14TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN14TX_EXIST  STD_OFF
#endif

/******************ASCLIN15ERR IRQ ********************************/

#ifdef ASCLIN15ERR_ISR
#define IRQ_ASCLIN15ERR_EXIST  STD_ON
#define IRQ_ASCLIN15_ERR_PRIO    ASCLIN15ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN15_ERR_CAT     ASCLIN15ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN15ERR_EXIST  STD_OFF
#endif

/******************ASCLIN15RX IRQ ********************************/

#ifdef ASCLIN15RX_ISR
#define IRQ_ASCLIN15RX_EXIST  STD_ON
#define IRQ_ASCLIN15_RX_PRIO    ASCLIN15RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN15_RX_CAT     ASCLIN15RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN15RX_EXIST  STD_OFF
#endif

/******************ASCLIN15TX IRQ ********************************/

#ifdef ASCLIN15TX_ISR
#define IRQ_ASCLIN15TX_EXIST  STD_ON
#define IRQ_ASCLIN15_TX_PRIO    ASCLIN15TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN15_TX_CAT     ASCLIN15TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN15TX_EXIST  STD_OFF
#endif

/******************ASCLIN16ERR IRQ ********************************/

#ifdef ASCLIN16ERR_ISR
#define IRQ_ASCLIN16ERR_EXIST  STD_ON
#define IRQ_ASCLIN16_ERR_PRIO    ASCLIN16ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN16_ERR_CAT     ASCLIN16ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN16ERR_EXIST  STD_OFF
#endif

/******************ASCLIN16RX IRQ ********************************/

#ifdef ASCLIN16RX_ISR
#define IRQ_ASCLIN16RX_EXIST  STD_ON
#define IRQ_ASCLIN16_RX_PRIO    ASCLIN16RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN16_RX_CAT     ASCLIN16RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN16RX_EXIST  STD_OFF
#endif

/******************ASCLIN16TX IRQ ********************************/

#ifdef ASCLIN16TX_ISR
#define IRQ_ASCLIN16TX_EXIST  STD_ON
#define IRQ_ASCLIN16_TX_PRIO    ASCLIN16TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN16_TX_CAT     ASCLIN16TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN16TX_EXIST  STD_OFF
#endif

/******************ASCLIN17ERR IRQ ********************************/

#ifdef ASCLIN17ERR_ISR
#define IRQ_ASCLIN17ERR_EXIST  STD_ON
#define IRQ_ASCLIN17_ERR_PRIO    ASCLIN17ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN17_ERR_CAT     ASCLIN17ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN17ERR_EXIST  STD_OFF
#endif

/******************ASCLIN17RX IRQ ********************************/

#ifdef ASCLIN17RX_ISR
#define IRQ_ASCLIN17RX_EXIST  STD_ON
#define IRQ_ASCLIN17_RX_PRIO    ASCLIN17RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN17_RX_CAT     ASCLIN17RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN17RX_EXIST  STD_OFF
#endif

/******************ASCLIN17TX IRQ ********************************/

#ifdef ASCLIN17TX_ISR
#define IRQ_ASCLIN17TX_EXIST  STD_ON
#define IRQ_ASCLIN17_TX_PRIO    ASCLIN17TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN17_TX_CAT     ASCLIN17TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN17TX_EXIST  STD_OFF
#endif

/******************ASCLIN18ERR IRQ ********************************/

#ifdef ASCLIN18ERR_ISR
#define IRQ_ASCLIN18ERR_EXIST  STD_ON
#define IRQ_ASCLIN18_ERR_PRIO    ASCLIN18ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN18_ERR_CAT     ASCLIN18ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN18ERR_EXIST  STD_OFF
#endif

/******************ASCLIN18RX IRQ ********************************/

#ifdef ASCLIN18RX_ISR
#define IRQ_ASCLIN18RX_EXIST  STD_ON
#define IRQ_ASCLIN18_RX_PRIO    ASCLIN18RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN18_RX_CAT     ASCLIN18RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN18RX_EXIST  STD_OFF
#endif

/******************ASCLIN18TX IRQ ********************************/

#ifdef ASCLIN18TX_ISR
#define IRQ_ASCLIN18TX_EXIST  STD_ON
#define IRQ_ASCLIN18_TX_PRIO    ASCLIN18TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN18_TX_CAT     ASCLIN18TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN18TX_EXIST  STD_OFF
#endif

/******************ASCLIN19ERR IRQ ********************************/

#ifdef ASCLIN19ERR_ISR
#define IRQ_ASCLIN19ERR_EXIST  STD_ON
#define IRQ_ASCLIN19_ERR_PRIO    ASCLIN19ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN19_ERR_CAT     ASCLIN19ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN19ERR_EXIST  STD_OFF
#endif

/******************ASCLIN19RX IRQ ********************************/

#ifdef ASCLIN19RX_ISR
#define IRQ_ASCLIN19RX_EXIST  STD_ON
#define IRQ_ASCLIN19_RX_PRIO    ASCLIN19RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN19_RX_CAT     ASCLIN19RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN19RX_EXIST  STD_OFF
#endif

/******************ASCLIN19TX IRQ ********************************/

#ifdef ASCLIN19TX_ISR
#define IRQ_ASCLIN19TX_EXIST  STD_ON
#define IRQ_ASCLIN19_TX_PRIO    ASCLIN19TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN19_TX_CAT     ASCLIN19TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN19TX_EXIST  STD_OFF
#endif

/******************ASCLIN1ERR IRQ ********************************/

#ifdef ASCLIN1ERR_ISR
#define IRQ_ASCLIN1ERR_EXIST  STD_ON
#define IRQ_ASCLIN1_ERR_PRIO    ASCLIN1ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN1_ERR_CAT     ASCLIN1ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN1ERR_EXIST  STD_OFF
#endif

/******************ASCLIN1RX IRQ ********************************/

#ifdef ASCLIN1RX_ISR
#define IRQ_ASCLIN1RX_EXIST  STD_ON
#define IRQ_ASCLIN1_RX_PRIO    ASCLIN1RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN1_RX_CAT     ASCLIN1RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN1RX_EXIST  STD_OFF
#endif

/******************ASCLIN1TX IRQ ********************************/

#ifdef ASCLIN1TX_ISR
#define IRQ_ASCLIN1TX_EXIST  STD_ON
#define IRQ_ASCLIN1_TX_PRIO    ASCLIN1TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN1_TX_CAT     ASCLIN1TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN1TX_EXIST  STD_OFF
#endif

/******************ASCLIN20ERR IRQ ********************************/

#ifdef ASCLIN20ERR_ISR
#define IRQ_ASCLIN20ERR_EXIST  STD_ON
#define IRQ_ASCLIN20_ERR_PRIO    ASCLIN20ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN20_ERR_CAT     ASCLIN20ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN20ERR_EXIST  STD_OFF
#endif

/******************ASCLIN20RX IRQ ********************************/

#ifdef ASCLIN20RX_ISR
#define IRQ_ASCLIN20RX_EXIST  STD_ON
#define IRQ_ASCLIN20_RX_PRIO    ASCLIN20RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN20_RX_CAT     ASCLIN20RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN20RX_EXIST  STD_OFF
#endif

/******************ASCLIN20TX IRQ ********************************/

#ifdef ASCLIN20TX_ISR
#define IRQ_ASCLIN20TX_EXIST  STD_ON
#define IRQ_ASCLIN20_TX_PRIO    ASCLIN20TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN20_TX_CAT     ASCLIN20TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN20TX_EXIST  STD_OFF
#endif

/******************ASCLIN21ERR IRQ ********************************/

#ifdef ASCLIN21ERR_ISR
#define IRQ_ASCLIN21ERR_EXIST  STD_ON
#define IRQ_ASCLIN21_ERR_PRIO    ASCLIN21ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN21_ERR_CAT     ASCLIN21ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN21ERR_EXIST  STD_OFF
#endif

/******************ASCLIN21RX IRQ ********************************/

#ifdef ASCLIN21RX_ISR
#define IRQ_ASCLIN21RX_EXIST  STD_ON
#define IRQ_ASCLIN21_RX_PRIO    ASCLIN21RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN21_RX_CAT     ASCLIN21RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN21RX_EXIST  STD_OFF
#endif

/******************ASCLIN21TX IRQ ********************************/

#ifdef ASCLIN21TX_ISR
#define IRQ_ASCLIN21TX_EXIST  STD_ON
#define IRQ_ASCLIN21_TX_PRIO    ASCLIN21TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN21_TX_CAT     ASCLIN21TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN21TX_EXIST  STD_OFF
#endif

/******************ASCLIN22ERR IRQ ********************************/

#ifdef ASCLIN22ERR_ISR
#define IRQ_ASCLIN22ERR_EXIST  STD_ON
#define IRQ_ASCLIN22_ERR_PRIO    ASCLIN22ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN22_ERR_CAT     ASCLIN22ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN22ERR_EXIST  STD_OFF
#endif

/******************ASCLIN22RX IRQ ********************************/

#ifdef ASCLIN22RX_ISR
#define IRQ_ASCLIN22RX_EXIST  STD_ON
#define IRQ_ASCLIN22_RX_PRIO    ASCLIN22RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN22_RX_CAT     ASCLIN22RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN22RX_EXIST  STD_OFF
#endif

/******************ASCLIN22TX IRQ ********************************/

#ifdef ASCLIN22TX_ISR
#define IRQ_ASCLIN22TX_EXIST  STD_ON
#define IRQ_ASCLIN22_TX_PRIO    ASCLIN22TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN22_TX_CAT     ASCLIN22TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN22TX_EXIST  STD_OFF
#endif

/******************ASCLIN23ERR IRQ ********************************/

#ifdef ASCLIN23ERR_ISR
#define IRQ_ASCLIN23ERR_EXIST  STD_ON
#define IRQ_ASCLIN23_ERR_PRIO    ASCLIN23ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN23_ERR_CAT     ASCLIN23ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN23ERR_EXIST  STD_OFF
#endif

/******************ASCLIN23RX IRQ ********************************/

#ifdef ASCLIN23RX_ISR
#define IRQ_ASCLIN23RX_EXIST  STD_ON
#define IRQ_ASCLIN23_RX_PRIO    ASCLIN23RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN23_RX_CAT     ASCLIN23RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN23RX_EXIST  STD_OFF
#endif

/******************ASCLIN23TX IRQ ********************************/

#ifdef ASCLIN23TX_ISR
#define IRQ_ASCLIN23TX_EXIST  STD_ON
#define IRQ_ASCLIN23_TX_PRIO    ASCLIN23TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN23_TX_CAT     ASCLIN23TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN23TX_EXIST  STD_OFF
#endif

/******************ASCLIN2ERR IRQ ********************************/

#ifdef ASCLIN2ERR_ISR
#define IRQ_ASCLIN2ERR_EXIST  STD_ON
#define IRQ_ASCLIN2_ERR_PRIO    ASCLIN2ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN2_ERR_CAT     ASCLIN2ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN2ERR_EXIST  STD_OFF
#endif

/******************ASCLIN2RX IRQ ********************************/

#ifdef ASCLIN2RX_ISR
#define IRQ_ASCLIN2RX_EXIST  STD_ON
#define IRQ_ASCLIN2_RX_PRIO    ASCLIN2RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN2_RX_CAT     ASCLIN2RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN2RX_EXIST  STD_OFF
#endif

/******************ASCLIN2TX IRQ ********************************/

#ifdef ASCLIN2TX_ISR
#define IRQ_ASCLIN2TX_EXIST  STD_ON
#define IRQ_ASCLIN2_TX_PRIO    ASCLIN2TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN2_TX_CAT     ASCLIN2TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN2TX_EXIST  STD_OFF
#endif

/******************ASCLIN3ERR IRQ ********************************/

#ifdef ASCLIN3ERR_ISR
#define IRQ_ASCLIN3ERR_EXIST  STD_ON
#define IRQ_ASCLIN3_ERR_PRIO    ASCLIN3ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN3_ERR_CAT     ASCLIN3ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN3ERR_EXIST  STD_OFF
#endif

/******************ASCLIN3RX IRQ ********************************/

#ifdef ASCLIN3RX_ISR
#define IRQ_ASCLIN3RX_EXIST  STD_ON
#define IRQ_ASCLIN3_RX_PRIO    ASCLIN3RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN3_RX_CAT     ASCLIN3RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN3RX_EXIST  STD_OFF
#endif

/******************ASCLIN3TX IRQ ********************************/

#ifdef ASCLIN3TX_ISR
#define IRQ_ASCLIN3TX_EXIST  STD_ON
#define IRQ_ASCLIN3_TX_PRIO    ASCLIN3TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN3_TX_CAT     ASCLIN3TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN3TX_EXIST  STD_OFF
#endif

/******************ASCLIN4ERR IRQ ********************************/

#ifdef ASCLIN4ERR_ISR
#define IRQ_ASCLIN4ERR_EXIST  STD_ON
#define IRQ_ASCLIN4_ERR_PRIO    ASCLIN4ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN4_ERR_CAT     ASCLIN4ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN4ERR_EXIST  STD_OFF
#endif

/******************ASCLIN4RX IRQ ********************************/

#ifdef ASCLIN4RX_ISR
#define IRQ_ASCLIN4RX_EXIST  STD_ON
#define IRQ_ASCLIN4_RX_PRIO    ASCLIN4RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN4_RX_CAT     ASCLIN4RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN4RX_EXIST  STD_OFF
#endif

/******************ASCLIN4TX IRQ ********************************/

#ifdef ASCLIN4TX_ISR
#define IRQ_ASCLIN4TX_EXIST  STD_ON
#define IRQ_ASCLIN4_TX_PRIO    ASCLIN4TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN4_TX_CAT     ASCLIN4TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN4TX_EXIST  STD_OFF
#endif

/******************ASCLIN5ERR IRQ ********************************/

#ifdef ASCLIN5ERR_ISR
#define IRQ_ASCLIN5ERR_EXIST  STD_ON
#define IRQ_ASCLIN5_ERR_PRIO    ASCLIN5ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN5_ERR_CAT     ASCLIN5ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN5ERR_EXIST  STD_OFF
#endif

/******************ASCLIN5RX IRQ ********************************/

#ifdef ASCLIN5RX_ISR
#define IRQ_ASCLIN5RX_EXIST  STD_ON
#define IRQ_ASCLIN5_RX_PRIO    ASCLIN5RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN5_RX_CAT     ASCLIN5RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN5RX_EXIST  STD_OFF
#endif

/******************ASCLIN5TX IRQ ********************************/

#ifdef ASCLIN5TX_ISR
#define IRQ_ASCLIN5TX_EXIST  STD_ON
#define IRQ_ASCLIN5_TX_PRIO    ASCLIN5TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN5_TX_CAT     ASCLIN5TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN5TX_EXIST  STD_OFF
#endif

/******************ASCLIN6ERR IRQ ********************************/

#ifdef ASCLIN6ERR_ISR
#define IRQ_ASCLIN6ERR_EXIST  STD_ON
#define IRQ_ASCLIN6_ERR_PRIO    ASCLIN6ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN6_ERR_CAT     ASCLIN6ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN6ERR_EXIST  STD_OFF
#endif

/******************ASCLIN6RX IRQ ********************************/

#ifdef ASCLIN6RX_ISR
#define IRQ_ASCLIN6RX_EXIST  STD_ON
#define IRQ_ASCLIN6_RX_PRIO    ASCLIN6RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN6_RX_CAT     ASCLIN6RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN6RX_EXIST  STD_OFF
#endif

/******************ASCLIN6TX IRQ ********************************/

#ifdef ASCLIN6TX_ISR
#define IRQ_ASCLIN6TX_EXIST  STD_ON
#define IRQ_ASCLIN6_TX_PRIO    ASCLIN6TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN6_TX_CAT     ASCLIN6TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN6TX_EXIST  STD_OFF
#endif

/******************ASCLIN7ERR IRQ ********************************/

#ifdef ASCLIN7ERR_ISR
#define IRQ_ASCLIN7ERR_EXIST  STD_ON
#define IRQ_ASCLIN7_ERR_PRIO    ASCLIN7ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN7_ERR_CAT     ASCLIN7ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN7ERR_EXIST  STD_OFF
#endif

/******************ASCLIN7RX IRQ ********************************/

#ifdef ASCLIN7RX_ISR
#define IRQ_ASCLIN7RX_EXIST  STD_ON
#define IRQ_ASCLIN7_RX_PRIO    ASCLIN7RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN7_RX_CAT     ASCLIN7RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN7RX_EXIST  STD_OFF
#endif

/******************ASCLIN7TX IRQ ********************************/

#ifdef ASCLIN7TX_ISR
#define IRQ_ASCLIN7TX_EXIST  STD_ON
#define IRQ_ASCLIN7_TX_PRIO    ASCLIN7TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN7_TX_CAT     ASCLIN7TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN7TX_EXIST  STD_OFF
#endif

/******************ASCLIN8ERR IRQ ********************************/

#ifdef ASCLIN8ERR_ISR
#define IRQ_ASCLIN8ERR_EXIST  STD_ON
#define IRQ_ASCLIN8_ERR_PRIO    ASCLIN8ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN8_ERR_CAT     ASCLIN8ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN8ERR_EXIST  STD_OFF
#endif

/******************ASCLIN8RX IRQ ********************************/

#ifdef ASCLIN8RX_ISR
#define IRQ_ASCLIN8RX_EXIST  STD_ON
#define IRQ_ASCLIN8_RX_PRIO    ASCLIN8RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN8_RX_CAT     ASCLIN8RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN8RX_EXIST  STD_OFF
#endif

/******************ASCLIN8TX IRQ ********************************/

#ifdef ASCLIN8TX_ISR
#define IRQ_ASCLIN8TX_EXIST  STD_ON
#define IRQ_ASCLIN8_TX_PRIO    ASCLIN8TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN8_TX_CAT     ASCLIN8TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN8TX_EXIST  STD_OFF
#endif

/******************ASCLIN9ERR IRQ ********************************/

#ifdef ASCLIN9ERR_ISR
#define IRQ_ASCLIN9ERR_EXIST  STD_ON
#define IRQ_ASCLIN9_ERR_PRIO    ASCLIN9ERR_ISR_ISR_LEVEL
#define IRQ_ASCLIN9_ERR_CAT     ASCLIN9ERR_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN9ERR_EXIST  STD_OFF
#endif

/******************ASCLIN9RX IRQ ********************************/

#ifdef ASCLIN9RX_ISR
#define IRQ_ASCLIN9RX_EXIST  STD_ON
#define IRQ_ASCLIN9_RX_PRIO    ASCLIN9RX_ISR_ISR_LEVEL
#define IRQ_ASCLIN9_RX_CAT     ASCLIN9RX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN9RX_EXIST  STD_OFF
#endif

/******************ASCLIN9TX IRQ ********************************/

#ifdef ASCLIN9TX_ISR
#define IRQ_ASCLIN9TX_EXIST  STD_ON
#define IRQ_ASCLIN9_TX_PRIO    ASCLIN9TX_ISR_ISR_LEVEL
#define IRQ_ASCLIN9_TX_CAT     ASCLIN9TX_ISR_ISR_CATEGORY
#else
#define IRQ_ASCLIN9TX_EXIST  STD_OFF
#endif
#endif /* #ifndef ASCLIN_IRQ_H */
