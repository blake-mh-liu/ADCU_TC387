
#ifndef DMA_IRQ_H
#define DMA_IRQ_H

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

/******************DMACH0SR IRQ ********************************/

#ifdef DMACH0SR_ISR
#define IRQ_DMACH0SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL0_SR_PRIO    DMACH0SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL0_SR_CAT     DMACH0SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH0SR_EXIST  STD_OFF
#endif

/******************DMACH100SR IRQ ********************************/

#ifdef DMACH100SR_ISR
#define IRQ_DMACH100SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL100_SR_PRIO    DMACH100SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL100_SR_CAT     DMACH100SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH100SR_EXIST  STD_OFF
#endif

/******************DMACH101SR IRQ ********************************/

#ifdef DMACH101SR_ISR
#define IRQ_DMACH101SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL101_SR_PRIO    DMACH101SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL101_SR_CAT     DMACH101SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH101SR_EXIST  STD_OFF
#endif

/******************DMACH102SR IRQ ********************************/

#ifdef DMACH102SR_ISR
#define IRQ_DMACH102SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL102_SR_PRIO    DMACH102SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL102_SR_CAT     DMACH102SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH102SR_EXIST  STD_OFF
#endif

/******************DMACH103SR IRQ ********************************/

#ifdef DMACH103SR_ISR
#define IRQ_DMACH103SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL103_SR_PRIO    DMACH103SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL103_SR_CAT     DMACH103SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH103SR_EXIST  STD_OFF
#endif

/******************DMACH104SR IRQ ********************************/

#ifdef DMACH104SR_ISR
#define IRQ_DMACH104SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL104_SR_PRIO    DMACH104SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL104_SR_CAT     DMACH104SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH104SR_EXIST  STD_OFF
#endif

/******************DMACH105SR IRQ ********************************/

#ifdef DMACH105SR_ISR
#define IRQ_DMACH105SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL105_SR_PRIO    DMACH105SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL105_SR_CAT     DMACH105SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH105SR_EXIST  STD_OFF
#endif

/******************DMACH106SR IRQ ********************************/

#ifdef DMACH106SR_ISR
#define IRQ_DMACH106SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL106_SR_PRIO    DMACH106SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL106_SR_CAT     DMACH106SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH106SR_EXIST  STD_OFF
#endif

/******************DMACH107SR IRQ ********************************/

#ifdef DMACH107SR_ISR
#define IRQ_DMACH107SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL107_SR_PRIO    DMACH107SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL107_SR_CAT     DMACH107SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH107SR_EXIST  STD_OFF
#endif

/******************DMACH108SR IRQ ********************************/

#ifdef DMACH108SR_ISR
#define IRQ_DMACH108SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL108_SR_PRIO    DMACH108SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL108_SR_CAT     DMACH108SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH108SR_EXIST  STD_OFF
#endif

/******************DMACH109SR IRQ ********************************/

#ifdef DMACH109SR_ISR
#define IRQ_DMACH109SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL109_SR_PRIO    DMACH109SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL109_SR_CAT     DMACH109SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH109SR_EXIST  STD_OFF
#endif

/******************DMACH10SR IRQ ********************************/

#ifdef DMACH10SR_ISR
#define IRQ_DMACH10SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL10_SR_PRIO    DMACH10SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL10_SR_CAT     DMACH10SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH10SR_EXIST  STD_OFF
#endif

/******************DMACH110SR IRQ ********************************/

#ifdef DMACH110SR_ISR
#define IRQ_DMACH110SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL110_SR_PRIO    DMACH110SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL110_SR_CAT     DMACH110SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH110SR_EXIST  STD_OFF
#endif

/******************DMACH111SR IRQ ********************************/

#ifdef DMACH111SR_ISR
#define IRQ_DMACH111SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL111_SR_PRIO    DMACH111SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL111_SR_CAT     DMACH111SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH111SR_EXIST  STD_OFF
#endif

/******************DMACH112SR IRQ ********************************/

#ifdef DMACH112SR_ISR
#define IRQ_DMACH112SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL112_SR_PRIO    DMACH112SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL112_SR_CAT     DMACH112SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH112SR_EXIST  STD_OFF
#endif

/******************DMACH113SR IRQ ********************************/

#ifdef DMACH113SR_ISR
#define IRQ_DMACH113SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL113_SR_PRIO    DMACH113SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL113_SR_CAT     DMACH113SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH113SR_EXIST  STD_OFF
#endif

/******************DMACH114SR IRQ ********************************/

#ifdef DMACH114SR_ISR
#define IRQ_DMACH114SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL114_SR_PRIO    DMACH114SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL114_SR_CAT     DMACH114SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH114SR_EXIST  STD_OFF
#endif

/******************DMACH115SR IRQ ********************************/

#ifdef DMACH115SR_ISR
#define IRQ_DMACH115SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL115_SR_PRIO    DMACH115SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL115_SR_CAT     DMACH115SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH115SR_EXIST  STD_OFF
#endif

/******************DMACH116SR IRQ ********************************/

#ifdef DMACH116SR_ISR
#define IRQ_DMACH116SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL116_SR_PRIO    DMACH116SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL116_SR_CAT     DMACH116SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH116SR_EXIST  STD_OFF
#endif

/******************DMACH117SR IRQ ********************************/

#ifdef DMACH117SR_ISR
#define IRQ_DMACH117SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL117_SR_PRIO    DMACH117SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL117_SR_CAT     DMACH117SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH117SR_EXIST  STD_OFF
#endif

/******************DMACH118SR IRQ ********************************/

#ifdef DMACH118SR_ISR
#define IRQ_DMACH118SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL118_SR_PRIO    DMACH118SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL118_SR_CAT     DMACH118SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH118SR_EXIST  STD_OFF
#endif

/******************DMACH119SR IRQ ********************************/

#ifdef DMACH119SR_ISR
#define IRQ_DMACH119SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL119_SR_PRIO    DMACH119SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL119_SR_CAT     DMACH119SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH119SR_EXIST  STD_OFF
#endif

/******************DMACH11SR IRQ ********************************/

#ifdef DMACH11SR_ISR
#define IRQ_DMACH11SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL11_SR_PRIO    DMACH11SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL11_SR_CAT     DMACH11SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH11SR_EXIST  STD_OFF
#endif

/******************DMACH120SR IRQ ********************************/

#ifdef DMACH120SR_ISR
#define IRQ_DMACH120SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL120_SR_PRIO    DMACH120SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL120_SR_CAT     DMACH120SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH120SR_EXIST  STD_OFF
#endif

/******************DMACH121SR IRQ ********************************/

#ifdef DMACH121SR_ISR
#define IRQ_DMACH121SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL121_SR_PRIO    DMACH121SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL121_SR_CAT     DMACH121SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH121SR_EXIST  STD_OFF
#endif

/******************DMACH122SR IRQ ********************************/

#ifdef DMACH122SR_ISR
#define IRQ_DMACH122SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL122_SR_PRIO    DMACH122SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL122_SR_CAT     DMACH122SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH122SR_EXIST  STD_OFF
#endif

/******************DMACH123SR IRQ ********************************/

#ifdef DMACH123SR_ISR
#define IRQ_DMACH123SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL123_SR_PRIO    DMACH123SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL123_SR_CAT     DMACH123SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH123SR_EXIST  STD_OFF
#endif

/******************DMACH124SR IRQ ********************************/

#ifdef DMACH124SR_ISR
#define IRQ_DMACH124SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL124_SR_PRIO    DMACH124SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL124_SR_CAT     DMACH124SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH124SR_EXIST  STD_OFF
#endif

/******************DMACH125SR IRQ ********************************/

#ifdef DMACH125SR_ISR
#define IRQ_DMACH125SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL125_SR_PRIO    DMACH125SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL125_SR_CAT     DMACH125SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH125SR_EXIST  STD_OFF
#endif

/******************DMACH126SR IRQ ********************************/

#ifdef DMACH126SR_ISR
#define IRQ_DMACH126SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL126_SR_PRIO    DMACH126SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL126_SR_CAT     DMACH126SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH126SR_EXIST  STD_OFF
#endif

/******************DMACH127SR IRQ ********************************/

#ifdef DMACH127SR_ISR
#define IRQ_DMACH127SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL127_SR_PRIO    DMACH127SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL127_SR_CAT     DMACH127SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH127SR_EXIST  STD_OFF
#endif

/******************DMACH12SR IRQ ********************************/

#ifdef DMACH12SR_ISR
#define IRQ_DMACH12SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL12_SR_PRIO    DMACH12SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL12_SR_CAT     DMACH12SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH12SR_EXIST  STD_OFF
#endif

/******************DMACH13SR IRQ ********************************/

#ifdef DMACH13SR_ISR
#define IRQ_DMACH13SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL13_SR_PRIO    DMACH13SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL13_SR_CAT     DMACH13SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH13SR_EXIST  STD_OFF
#endif

/******************DMACH14SR IRQ ********************************/

#ifdef DMACH14SR_ISR
#define IRQ_DMACH14SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL14_SR_PRIO    DMACH14SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL14_SR_CAT     DMACH14SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH14SR_EXIST  STD_OFF
#endif

/******************DMACH15SR IRQ ********************************/

#ifdef DMACH15SR_ISR
#define IRQ_DMACH15SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL15_SR_PRIO    DMACH15SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL15_SR_CAT     DMACH15SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH15SR_EXIST  STD_OFF
#endif

/******************DMACH16SR IRQ ********************************/

#ifdef DMACH16SR_ISR
#define IRQ_DMACH16SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL16_SR_PRIO    DMACH16SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL16_SR_CAT     DMACH16SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH16SR_EXIST  STD_OFF
#endif

/******************DMACH17SR IRQ ********************************/

#ifdef DMACH17SR_ISR
#define IRQ_DMACH17SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL17_SR_PRIO    DMACH17SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL17_SR_CAT     DMACH17SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH17SR_EXIST  STD_OFF
#endif

/******************DMACH18SR IRQ ********************************/

#ifdef DMACH18SR_ISR
#define IRQ_DMACH18SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL18_SR_PRIO    DMACH18SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL18_SR_CAT     DMACH18SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH18SR_EXIST  STD_OFF
#endif

/******************DMACH19SR IRQ ********************************/

#ifdef DMACH19SR_ISR
#define IRQ_DMACH19SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL19_SR_PRIO    DMACH19SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL19_SR_CAT     DMACH19SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH19SR_EXIST  STD_OFF
#endif

/******************DMACH1SR IRQ ********************************/

#ifdef DMACH1SR_ISR
#define IRQ_DMACH1SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL1_SR_PRIO    DMACH1SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL1_SR_CAT     DMACH1SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH1SR_EXIST  STD_OFF
#endif

/******************DMACH20SR IRQ ********************************/

#ifdef DMACH20SR_ISR
#define IRQ_DMACH20SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL20_SR_PRIO    DMACH20SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL20_SR_CAT     DMACH20SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH20SR_EXIST  STD_OFF
#endif

/******************DMACH21SR IRQ ********************************/

#ifdef DMACH21SR_ISR
#define IRQ_DMACH21SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL21_SR_PRIO    DMACH21SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL21_SR_CAT     DMACH21SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH21SR_EXIST  STD_OFF
#endif

/******************DMACH22SR IRQ ********************************/

#ifdef DMACH22SR_ISR
#define IRQ_DMACH22SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL22_SR_PRIO    DMACH22SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL22_SR_CAT     DMACH22SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH22SR_EXIST  STD_OFF
#endif

/******************DMACH23SR IRQ ********************************/

#ifdef DMACH23SR_ISR
#define IRQ_DMACH23SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL23_SR_PRIO    DMACH23SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL23_SR_CAT     DMACH23SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH23SR_EXIST  STD_OFF
#endif

/******************DMACH24SR IRQ ********************************/

#ifdef DMACH24SR_ISR
#define IRQ_DMACH24SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL24_SR_PRIO    DMACH24SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL24_SR_CAT     DMACH24SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH24SR_EXIST  STD_OFF
#endif

/******************DMACH25SR IRQ ********************************/

#ifdef DMACH25SR_ISR
#define IRQ_DMACH25SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL25_SR_PRIO    DMACH25SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL25_SR_CAT     DMACH25SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH25SR_EXIST  STD_OFF
#endif

/******************DMACH26SR IRQ ********************************/

#ifdef DMACH26SR_ISR
#define IRQ_DMACH26SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL26_SR_PRIO    DMACH26SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL26_SR_CAT     DMACH26SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH26SR_EXIST  STD_OFF
#endif

/******************DMACH27SR IRQ ********************************/

#ifdef DMACH27SR_ISR
#define IRQ_DMACH27SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL27_SR_PRIO    DMACH27SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL27_SR_CAT     DMACH27SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH27SR_EXIST  STD_OFF
#endif

/******************DMACH28SR IRQ ********************************/

#ifdef DMACH28SR_ISR
#define IRQ_DMACH28SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL28_SR_PRIO    DMACH28SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL28_SR_CAT     DMACH28SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH28SR_EXIST  STD_OFF
#endif

/******************DMACH29SR IRQ ********************************/

#ifdef DMACH29SR_ISR
#define IRQ_DMACH29SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL29_SR_PRIO    DMACH29SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL29_SR_CAT     DMACH29SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH29SR_EXIST  STD_OFF
#endif

/******************DMACH2SR IRQ ********************************/

#ifdef DMACH2SR_ISR
#define IRQ_DMACH2SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL2_SR_PRIO    DMACH2SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL2_SR_CAT     DMACH2SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH2SR_EXIST  STD_OFF
#endif

/******************DMACH30SR IRQ ********************************/

#ifdef DMACH30SR_ISR
#define IRQ_DMACH30SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL30_SR_PRIO    DMACH30SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL30_SR_CAT     DMACH30SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH30SR_EXIST  STD_OFF
#endif

/******************DMACH31SR IRQ ********************************/

#ifdef DMACH31SR_ISR
#define IRQ_DMACH31SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL31_SR_PRIO    DMACH31SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL31_SR_CAT     DMACH31SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH31SR_EXIST  STD_OFF
#endif

/******************DMACH32SR IRQ ********************************/

#ifdef DMACH32SR_ISR
#define IRQ_DMACH32SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL32_SR_PRIO    DMACH32SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL32_SR_CAT     DMACH32SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH32SR_EXIST  STD_OFF
#endif

/******************DMACH33SR IRQ ********************************/

#ifdef DMACH33SR_ISR
#define IRQ_DMACH33SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL33_SR_PRIO    DMACH33SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL33_SR_CAT     DMACH33SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH33SR_EXIST  STD_OFF
#endif

/******************DMACH34SR IRQ ********************************/

#ifdef DMACH34SR_ISR
#define IRQ_DMACH34SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL34_SR_PRIO    DMACH34SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL34_SR_CAT     DMACH34SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH34SR_EXIST  STD_OFF
#endif

/******************DMACH35SR IRQ ********************************/

#ifdef DMACH35SR_ISR
#define IRQ_DMACH35SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL35_SR_PRIO    DMACH35SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL35_SR_CAT     DMACH35SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH35SR_EXIST  STD_OFF
#endif

/******************DMACH36SR IRQ ********************************/

#ifdef DMACH36SR_ISR
#define IRQ_DMACH36SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL36_SR_PRIO    DMACH36SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL36_SR_CAT     DMACH36SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH36SR_EXIST  STD_OFF
#endif

/******************DMACH37SR IRQ ********************************/

#ifdef DMACH37SR_ISR
#define IRQ_DMACH37SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL37_SR_PRIO    DMACH37SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL37_SR_CAT     DMACH37SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH37SR_EXIST  STD_OFF
#endif

/******************DMACH38SR IRQ ********************************/

#ifdef DMACH38SR_ISR
#define IRQ_DMACH38SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL38_SR_PRIO    DMACH38SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL38_SR_CAT     DMACH38SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH38SR_EXIST  STD_OFF
#endif

/******************DMACH39SR IRQ ********************************/

#ifdef DMACH39SR_ISR
#define IRQ_DMACH39SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL39_SR_PRIO    DMACH39SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL39_SR_CAT     DMACH39SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH39SR_EXIST  STD_OFF
#endif

/******************DMACH3SR IRQ ********************************/

#ifdef DMACH3SR_ISR
#define IRQ_DMACH3SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL3_SR_PRIO    DMACH3SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL3_SR_CAT     DMACH3SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH3SR_EXIST  STD_OFF
#endif

/******************DMACH40SR IRQ ********************************/

#ifdef DMACH40SR_ISR
#define IRQ_DMACH40SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL40_SR_PRIO    DMACH40SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL40_SR_CAT     DMACH40SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH40SR_EXIST  STD_OFF
#endif

/******************DMACH41SR IRQ ********************************/

#ifdef DMACH41SR_ISR
#define IRQ_DMACH41SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL41_SR_PRIO    DMACH41SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL41_SR_CAT     DMACH41SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH41SR_EXIST  STD_OFF
#endif

/******************DMACH42SR IRQ ********************************/

#ifdef DMACH42SR_ISR
#define IRQ_DMACH42SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL42_SR_PRIO    DMACH42SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL42_SR_CAT     DMACH42SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH42SR_EXIST  STD_OFF
#endif

/******************DMACH43SR IRQ ********************************/

#ifdef DMACH43SR_ISR
#define IRQ_DMACH43SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL43_SR_PRIO    DMACH43SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL43_SR_CAT     DMACH43SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH43SR_EXIST  STD_OFF
#endif

/******************DMACH44SR IRQ ********************************/

#ifdef DMACH44SR_ISR
#define IRQ_DMACH44SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL44_SR_PRIO    DMACH44SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL44_SR_CAT     DMACH44SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH44SR_EXIST  STD_OFF
#endif

/******************DMACH45SR IRQ ********************************/

#ifdef DMACH45SR_ISR
#define IRQ_DMACH45SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL45_SR_PRIO    DMACH45SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL45_SR_CAT     DMACH45SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH45SR_EXIST  STD_OFF
#endif

/******************DMACH46SR IRQ ********************************/

#ifdef DMACH46SR_ISR
#define IRQ_DMACH46SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL46_SR_PRIO    DMACH46SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL46_SR_CAT     DMACH46SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH46SR_EXIST  STD_OFF
#endif

/******************DMACH47SR IRQ ********************************/

#ifdef DMACH47SR_ISR
#define IRQ_DMACH47SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL47_SR_PRIO    DMACH47SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL47_SR_CAT     DMACH47SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH47SR_EXIST  STD_OFF
#endif

/******************DMACH48SR IRQ ********************************/

#ifdef DMACH48SR_ISR
#define IRQ_DMACH48SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL48_SR_PRIO    DMACH48SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL48_SR_CAT     DMACH48SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH48SR_EXIST  STD_OFF
#endif

/******************DMACH49SR IRQ ********************************/

#ifdef DMACH49SR_ISR
#define IRQ_DMACH49SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL49_SR_PRIO    DMACH49SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL49_SR_CAT     DMACH49SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH49SR_EXIST  STD_OFF
#endif

/******************DMACH4SR IRQ ********************************/

#ifdef DMACH4SR_ISR
#define IRQ_DMACH4SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL4_SR_PRIO    DMACH4SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL4_SR_CAT     DMACH4SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH4SR_EXIST  STD_OFF
#endif

/******************DMACH50SR IRQ ********************************/

#ifdef DMACH50SR_ISR
#define IRQ_DMACH50SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL50_SR_PRIO    DMACH50SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL50_SR_CAT     DMACH50SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH50SR_EXIST  STD_OFF
#endif

/******************DMACH51SR IRQ ********************************/

#ifdef DMACH51SR_ISR
#define IRQ_DMACH51SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL51_SR_PRIO    DMACH51SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL51_SR_CAT     DMACH51SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH51SR_EXIST  STD_OFF
#endif

/******************DMACH52SR IRQ ********************************/

#ifdef DMACH52SR_ISR
#define IRQ_DMACH52SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL52_SR_PRIO    DMACH52SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL52_SR_CAT     DMACH52SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH52SR_EXIST  STD_OFF
#endif

/******************DMACH53SR IRQ ********************************/

#ifdef DMACH53SR_ISR
#define IRQ_DMACH53SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL53_SR_PRIO    DMACH53SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL53_SR_CAT     DMACH53SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH53SR_EXIST  STD_OFF
#endif

/******************DMACH54SR IRQ ********************************/

#ifdef DMACH54SR_ISR
#define IRQ_DMACH54SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL54_SR_PRIO    DMACH54SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL54_SR_CAT     DMACH54SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH54SR_EXIST  STD_OFF
#endif

/******************DMACH55SR IRQ ********************************/

#ifdef DMACH55SR_ISR
#define IRQ_DMACH55SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL55_SR_PRIO    DMACH55SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL55_SR_CAT     DMACH55SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH55SR_EXIST  STD_OFF
#endif

/******************DMACH56SR IRQ ********************************/

#ifdef DMACH56SR_ISR
#define IRQ_DMACH56SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL56_SR_PRIO    DMACH56SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL56_SR_CAT     DMACH56SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH56SR_EXIST  STD_OFF
#endif

/******************DMACH57SR IRQ ********************************/

#ifdef DMACH57SR_ISR
#define IRQ_DMACH57SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL57_SR_PRIO    DMACH57SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL57_SR_CAT     DMACH57SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH57SR_EXIST  STD_OFF
#endif

/******************DMACH58SR IRQ ********************************/

#ifdef DMACH58SR_ISR
#define IRQ_DMACH58SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL58_SR_PRIO    DMACH58SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL58_SR_CAT     DMACH58SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH58SR_EXIST  STD_OFF
#endif

/******************DMACH59SR IRQ ********************************/

#ifdef DMACH59SR_ISR
#define IRQ_DMACH59SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL59_SR_PRIO    DMACH59SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL59_SR_CAT     DMACH59SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH59SR_EXIST  STD_OFF
#endif

/******************DMACH5SR IRQ ********************************/

#ifdef DMACH5SR_ISR
#define IRQ_DMACH5SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL5_SR_PRIO    DMACH5SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL5_SR_CAT     DMACH5SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH5SR_EXIST  STD_OFF
#endif

/******************DMACH60SR IRQ ********************************/

#ifdef DMACH60SR_ISR
#define IRQ_DMACH60SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL60_SR_PRIO    DMACH60SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL60_SR_CAT     DMACH60SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH60SR_EXIST  STD_OFF
#endif

/******************DMACH61SR IRQ ********************************/

#ifdef DMACH61SR_ISR
#define IRQ_DMACH61SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL61_SR_PRIO    DMACH61SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL61_SR_CAT     DMACH61SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH61SR_EXIST  STD_OFF
#endif

/******************DMACH62SR IRQ ********************************/

#ifdef DMACH62SR_ISR
#define IRQ_DMACH62SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL62_SR_PRIO    DMACH62SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL62_SR_CAT     DMACH62SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH62SR_EXIST  STD_OFF
#endif

/******************DMACH63SR IRQ ********************************/

#ifdef DMACH63SR_ISR
#define IRQ_DMACH63SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL63_SR_PRIO    DMACH63SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL63_SR_CAT     DMACH63SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH63SR_EXIST  STD_OFF
#endif

/******************DMACH64SR IRQ ********************************/

#ifdef DMACH64SR_ISR
#define IRQ_DMACH64SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL64_SR_PRIO    DMACH64SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL64_SR_CAT     DMACH64SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH64SR_EXIST  STD_OFF
#endif

/******************DMACH65SR IRQ ********************************/

#ifdef DMACH65SR_ISR
#define IRQ_DMACH65SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL65_SR_PRIO    DMACH65SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL65_SR_CAT     DMACH65SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH65SR_EXIST  STD_OFF
#endif

/******************DMACH66SR IRQ ********************************/

#ifdef DMACH66SR_ISR
#define IRQ_DMACH66SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL66_SR_PRIO    DMACH66SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL66_SR_CAT     DMACH66SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH66SR_EXIST  STD_OFF
#endif

/******************DMACH67SR IRQ ********************************/

#ifdef DMACH67SR_ISR
#define IRQ_DMACH67SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL67_SR_PRIO    DMACH67SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL67_SR_CAT     DMACH67SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH67SR_EXIST  STD_OFF
#endif

/******************DMACH68SR IRQ ********************************/

#ifdef DMACH68SR_ISR
#define IRQ_DMACH68SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL68_SR_PRIO    DMACH68SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL68_SR_CAT     DMACH68SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH68SR_EXIST  STD_OFF
#endif

/******************DMACH69SR IRQ ********************************/

#ifdef DMACH69SR_ISR
#define IRQ_DMACH69SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL69_SR_PRIO    DMACH69SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL69_SR_CAT     DMACH69SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH69SR_EXIST  STD_OFF
#endif

/******************DMACH6SR IRQ ********************************/

#ifdef DMACH6SR_ISR
#define IRQ_DMACH6SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL6_SR_PRIO    DMACH6SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL6_SR_CAT     DMACH6SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH6SR_EXIST  STD_OFF
#endif

/******************DMACH70SR IRQ ********************************/

#ifdef DMACH70SR_ISR
#define IRQ_DMACH70SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL70_SR_PRIO    DMACH70SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL70_SR_CAT     DMACH70SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH70SR_EXIST  STD_OFF
#endif

/******************DMACH71SR IRQ ********************************/

#ifdef DMACH71SR_ISR
#define IRQ_DMACH71SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL71_SR_PRIO    DMACH71SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL71_SR_CAT     DMACH71SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH71SR_EXIST  STD_OFF
#endif

/******************DMACH72SR IRQ ********************************/

#ifdef DMACH72SR_ISR
#define IRQ_DMACH72SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL72_SR_PRIO    DMACH72SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL72_SR_CAT     DMACH72SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH72SR_EXIST  STD_OFF
#endif

/******************DMACH73SR IRQ ********************************/

#ifdef DMACH73SR_ISR
#define IRQ_DMACH73SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL73_SR_PRIO    DMACH73SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL73_SR_CAT     DMACH73SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH73SR_EXIST  STD_OFF
#endif

/******************DMACH74SR IRQ ********************************/

#ifdef DMACH74SR_ISR
#define IRQ_DMACH74SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL74_SR_PRIO    DMACH74SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL74_SR_CAT     DMACH74SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH74SR_EXIST  STD_OFF
#endif

/******************DMACH75SR IRQ ********************************/

#ifdef DMACH75SR_ISR
#define IRQ_DMACH75SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL75_SR_PRIO    DMACH75SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL75_SR_CAT     DMACH75SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH75SR_EXIST  STD_OFF
#endif

/******************DMACH76SR IRQ ********************************/

#ifdef DMACH76SR_ISR
#define IRQ_DMACH76SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL76_SR_PRIO    DMACH76SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL76_SR_CAT     DMACH76SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH76SR_EXIST  STD_OFF
#endif

/******************DMACH77SR IRQ ********************************/

#ifdef DMACH77SR_ISR
#define IRQ_DMACH77SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL77_SR_PRIO    DMACH77SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL77_SR_CAT     DMACH77SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH77SR_EXIST  STD_OFF
#endif

/******************DMACH78SR IRQ ********************************/

#ifdef DMACH78SR_ISR
#define IRQ_DMACH78SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL78_SR_PRIO    DMACH78SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL78_SR_CAT     DMACH78SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH78SR_EXIST  STD_OFF
#endif

/******************DMACH79SR IRQ ********************************/

#ifdef DMACH79SR_ISR
#define IRQ_DMACH79SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL79_SR_PRIO    DMACH79SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL79_SR_CAT     DMACH79SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH79SR_EXIST  STD_OFF
#endif

/******************DMACH7SR IRQ ********************************/

#ifdef DMACH7SR_ISR
#define IRQ_DMACH7SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL7_SR_PRIO    DMACH7SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL7_SR_CAT     DMACH7SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH7SR_EXIST  STD_OFF
#endif

/******************DMACH80SR IRQ ********************************/

#ifdef DMACH80SR_ISR
#define IRQ_DMACH80SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL80_SR_PRIO    DMACH80SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL80_SR_CAT     DMACH80SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH80SR_EXIST  STD_OFF
#endif

/******************DMACH81SR IRQ ********************************/

#ifdef DMACH81SR_ISR
#define IRQ_DMACH81SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL81_SR_PRIO    DMACH81SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL81_SR_CAT     DMACH81SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH81SR_EXIST  STD_OFF
#endif

/******************DMACH82SR IRQ ********************************/

#ifdef DMACH82SR_ISR
#define IRQ_DMACH82SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL82_SR_PRIO    DMACH82SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL82_SR_CAT     DMACH82SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH82SR_EXIST  STD_OFF
#endif

/******************DMACH83SR IRQ ********************************/

#ifdef DMACH83SR_ISR
#define IRQ_DMACH83SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL83_SR_PRIO    DMACH83SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL83_SR_CAT     DMACH83SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH83SR_EXIST  STD_OFF
#endif

/******************DMACH84SR IRQ ********************************/

#ifdef DMACH84SR_ISR
#define IRQ_DMACH84SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL84_SR_PRIO    DMACH84SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL84_SR_CAT     DMACH84SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH84SR_EXIST  STD_OFF
#endif

/******************DMACH85SR IRQ ********************************/

#ifdef DMACH85SR_ISR
#define IRQ_DMACH85SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL85_SR_PRIO    DMACH85SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL85_SR_CAT     DMACH85SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH85SR_EXIST  STD_OFF
#endif

/******************DMACH86SR IRQ ********************************/

#ifdef DMACH86SR_ISR
#define IRQ_DMACH86SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL86_SR_PRIO    DMACH86SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL86_SR_CAT     DMACH86SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH86SR_EXIST  STD_OFF
#endif

/******************DMACH87SR IRQ ********************************/

#ifdef DMACH87SR_ISR
#define IRQ_DMACH87SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL87_SR_PRIO    DMACH87SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL87_SR_CAT     DMACH87SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH87SR_EXIST  STD_OFF
#endif

/******************DMACH88SR IRQ ********************************/

#ifdef DMACH88SR_ISR
#define IRQ_DMACH88SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL88_SR_PRIO    DMACH88SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL88_SR_CAT     DMACH88SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH88SR_EXIST  STD_OFF
#endif

/******************DMACH89SR IRQ ********************************/

#ifdef DMACH89SR_ISR
#define IRQ_DMACH89SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL89_SR_PRIO    DMACH89SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL89_SR_CAT     DMACH89SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH89SR_EXIST  STD_OFF
#endif

/******************DMACH8SR IRQ ********************************/

#ifdef DMACH8SR_ISR
#define IRQ_DMACH8SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL8_SR_PRIO    DMACH8SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL8_SR_CAT     DMACH8SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH8SR_EXIST  STD_OFF
#endif

/******************DMACH90SR IRQ ********************************/

#ifdef DMACH90SR_ISR
#define IRQ_DMACH90SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL90_SR_PRIO    DMACH90SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL90_SR_CAT     DMACH90SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH90SR_EXIST  STD_OFF
#endif

/******************DMACH91SR IRQ ********************************/

#ifdef DMACH91SR_ISR
#define IRQ_DMACH91SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL91_SR_PRIO    DMACH91SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL91_SR_CAT     DMACH91SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH91SR_EXIST  STD_OFF
#endif

/******************DMACH92SR IRQ ********************************/

#ifdef DMACH92SR_ISR
#define IRQ_DMACH92SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL92_SR_PRIO    DMACH92SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL92_SR_CAT     DMACH92SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH92SR_EXIST  STD_OFF
#endif

/******************DMACH93SR IRQ ********************************/

#ifdef DMACH93SR_ISR
#define IRQ_DMACH93SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL93_SR_PRIO    DMACH93SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL93_SR_CAT     DMACH93SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH93SR_EXIST  STD_OFF
#endif

/******************DMACH94SR IRQ ********************************/

#ifdef DMACH94SR_ISR
#define IRQ_DMACH94SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL94_SR_PRIO    DMACH94SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL94_SR_CAT     DMACH94SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH94SR_EXIST  STD_OFF
#endif

/******************DMACH95SR IRQ ********************************/

#ifdef DMACH95SR_ISR
#define IRQ_DMACH95SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL95_SR_PRIO    DMACH95SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL95_SR_CAT     DMACH95SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH95SR_EXIST  STD_OFF
#endif

/******************DMACH96SR IRQ ********************************/

#ifdef DMACH96SR_ISR
#define IRQ_DMACH96SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL96_SR_PRIO    DMACH96SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL96_SR_CAT     DMACH96SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH96SR_EXIST  STD_OFF
#endif

/******************DMACH97SR IRQ ********************************/

#ifdef DMACH97SR_ISR
#define IRQ_DMACH97SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL97_SR_PRIO    DMACH97SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL97_SR_CAT     DMACH97SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH97SR_EXIST  STD_OFF
#endif

/******************DMACH98SR IRQ ********************************/

#ifdef DMACH98SR_ISR
#define IRQ_DMACH98SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL98_SR_PRIO    DMACH98SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL98_SR_CAT     DMACH98SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH98SR_EXIST  STD_OFF
#endif

/******************DMACH99SR IRQ ********************************/

#ifdef DMACH99SR_ISR
#define IRQ_DMACH99SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL99_SR_PRIO    DMACH99SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL99_SR_CAT     DMACH99SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH99SR_EXIST  STD_OFF
#endif

/******************DMACH9SR IRQ ********************************/

#ifdef DMACH9SR_ISR
#define IRQ_DMACH9SR_EXIST  STD_ON
#define IRQ_DMA_CHANNEL9_SR_PRIO    DMACH9SR_ISR_ISR_LEVEL
#define IRQ_DMA_CHANNEL9_SR_CAT     DMACH9SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMACH9SR_EXIST  STD_OFF
#endif

/******************DMAERR0SR IRQ ********************************/

#ifdef DMAERR0SR_ISR
#define IRQ_DMAERR0SR_EXIST  STD_ON
#define IRQ_DMA_ERR0_SR_PRIO    DMAERR0SR_ISR_ISR_LEVEL
#define IRQ_DMA_ERR0_SR_CAT     DMAERR0SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMAERR0SR_EXIST  STD_OFF
#endif

/******************DMAERR1SR IRQ ********************************/

#ifdef DMAERR1SR_ISR
#define IRQ_DMAERR1SR_EXIST  STD_ON
#define IRQ_DMA_ERR1_SR_PRIO    DMAERR1SR_ISR_ISR_LEVEL
#define IRQ_DMA_ERR1_SR_CAT     DMAERR1SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMAERR1SR_EXIST  STD_OFF
#endif

/******************DMAERR2SR IRQ ********************************/

#ifdef DMAERR2SR_ISR
#define IRQ_DMAERR2SR_EXIST  STD_ON
#define IRQ_DMA_ERR2_SR_PRIO    DMAERR2SR_ISR_ISR_LEVEL
#define IRQ_DMA_ERR2_SR_CAT     DMAERR2SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMAERR2SR_EXIST  STD_OFF
#endif

/******************DMAERR3SR IRQ ********************************/

#ifdef DMAERR3SR_ISR
#define IRQ_DMAERR3SR_EXIST  STD_ON
#define IRQ_DMA_ERR3_SR_PRIO    DMAERR3SR_ISR_ISR_LEVEL
#define IRQ_DMA_ERR3_SR_CAT     DMAERR3SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMAERR3SR_EXIST  STD_OFF
#endif

/******************DMAGPSR00SR IRQ ********************************/

#ifdef DMAGPSR00SR_ISR
#define IRQ_DMAGPSR00SR_EXIST  STD_ON
#define IRQ_GPSRGROUP0_SR0_PRIO    DMAGPSR00SR_ISR_ISR_LEVEL
#define IRQ_GPSRGROUP0_SR0_CAT     DMAGPSR00SR_ISR_ISR_CATEGORY
#else
#define IRQ_DMAGPSR00SR_EXIST  STD_OFF
#endif
#endif /* #ifndef DMA_IRQ_H */
