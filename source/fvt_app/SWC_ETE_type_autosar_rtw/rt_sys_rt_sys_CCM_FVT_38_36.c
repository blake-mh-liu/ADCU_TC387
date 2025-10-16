/*
 * File: rt_sys_rt_sys_CCM_FVT_38_36.c
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

#include "rtwtypes.h"
#include "rt_sys_rt_sys_CCM_FVT_38_36.h"

void SWC_ETE_type_Delay_l(boolean *rty_y, ARID_DEF_Delay_SWC_ETE_type_n_T
  *SWC_ETE_type__ARID_DEF_arg)
{
  /* UnitDelay: '<S59>/UnitDelay' */
  *rty_y = SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE;
}

/*
 * Update for atomic system:
 *    '<S56>/Delay'
 *    '<S57>/Delay'
 *    '<S70>/Delay'
 *    '<S120>/Delay'
 *    '<S108>/Delay'
 *    '<S109>/Delay'
 *    '<S110>/Delay'
 *    '<S111>/Delay'
 *    '<S112>/Delay'
 *    '<S147>/Delay'
 *    ...
 */
void SWC_ETE_type_Delay_l_Update(boolean rtu_u, ARID_DEF_Delay_SWC_ETE_type_n_T *
  SWC_ETE_type__ARID_DEF_arg)
{
  /* Update for UnitDelay: '<S59>/UnitDelay' */
  SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE = rtu_u;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
