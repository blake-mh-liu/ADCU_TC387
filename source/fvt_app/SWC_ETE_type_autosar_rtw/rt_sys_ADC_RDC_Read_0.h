/*
 * File: rt_sys_ADC_RDC_Read_0.h
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

#ifndef rt_sys_ADC_RDC_Read_0_h_
#define rt_sys_ADC_RDC_Read_0_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

/* PublicStructure Variables for Internal Data, for system '<S18>/Delay' */
typedef struct {
  float32 UnitDelay_DSTATE;            /* '<S21>/UnitDelay' */
} ARID_DEF_Delay_SWC_ETE_type_T;

extern void SWC_ETE_type_Delay_Update(float32 rtu_u,
  ARID_DEF_Delay_SWC_ETE_type_T *SWC_ETE_type__ARID_DEF_arg);
extern void SWC_ETE_type_Delay(float32 *rty_y, ARID_DEF_Delay_SWC_ETE_type_T
  *SWC_ETE_type__ARID_DEF_arg);

#endif                                 /* rt_sys_ADC_RDC_Read_0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
