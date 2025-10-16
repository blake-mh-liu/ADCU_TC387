/*
 * File: rt_sys_CCM_FVT_38.h
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

#ifndef rt_sys_CCM_FVT_38_h_
#define rt_sys_CCM_FVT_38_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

#include "rt_sys_rt_sys_CCM_FVT_38_36.h"

/* PublicStructure Variables for Internal Data, for system '<S47>/ER_FF' */
typedef struct {
  ARID_DEF_Delay_SWC_ETE_type_n_T ARID_DEF_Delay;/* '<S56>/Delay' */
} ARID_DEF_ER_FF_SWC_ETE_type_T;

extern void SWC_ETE_type_ER_FF(boolean rtu_E1_T, boolean rtu_R2_F, boolean
  *rty_y, ARID_DEF_ER_FF_SWC_ETE_type_T *SWC_ETE_type__ARID_DEF_arg);

#endif                                 /* rt_sys_CCM_FVT_38_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
