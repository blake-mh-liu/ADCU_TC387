/*
 * File: ADC_RDC_Read.h
 *
 * Code generated for Simulink model 'SWC_ETE_type'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Sep 24 14:18:28 2025
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ADC_RDC_Read_h_
#define ADC_RDC_Read_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

/* PublicStructure Variables for Internal Data, for system '<S20>/First_Order_Filter' */
typedef struct {
  float32 UnitDelay_DSTATE;            /* '<S30>/Unit Delay' */
} ARID_DEF_First_Order_Filter_T;

extern void First_Order_Filter(float32 rtu_InputSignal, float32 rtu_cutoff_freq,
  float32 rtu_sample_freq, float32 *rty_OutputSignal,
  ARID_DEF_First_Order_Filter_T *SWC_ETE_type__ARID_DEF_arg);
extern void SWC_ETE_type_ADC_RDC_Read_Init(void);
extern void SWC_ETE_type_ADC_RDC_Read(void);

#endif                                 /* ADC_RDC_Read_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
