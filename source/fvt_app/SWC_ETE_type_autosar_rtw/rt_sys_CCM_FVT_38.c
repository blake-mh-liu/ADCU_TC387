/*
 * File: rt_sys_CCM_FVT_38.c
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
#include "rt_sys_CCM_FVT_38.h"
#include "rt_sys_rt_sys_CCM_FVT_38_36.h"

/*
 * Output and update for atomic system:
 *    '<S47>/ER_FF'
 *    '<S47>/ER_FF1'
 *    '<S58>/ER_FF'
 *    '<S115>/ER_FF1'
 *    '<S6>/ER_FF1'
 *    '<S6>/ER_FF2'
 *    '<S6>/ER_FF3'
 *    '<S6>/ER_FF4'
 *    '<S6>/ER_FF5'
 */
void SWC_ETE_type_ER_FF(boolean rtu_E1_T, boolean rtu_R2_F, boolean *rty_y,
  ARID_DEF_ER_FF_SWC_ETE_type_T *SWC_ETE_type__ARID_DEF_arg)
{
  boolean rtb_UnitDelay_j;

  /* Outputs for Atomic SubSystem: '<S56>/Delay' */
  SWC_ETE_type_Delay_l(&rtb_UnitDelay_j,
                       &SWC_ETE_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S56>/Delay' */

  /* Switch: '<S62>/SWT' incorporates:
   *  Constant: '<S56>/true'
   *  Switch: '<S61>/SWT'
   */
  if (rtu_E1_T) {
    *rty_y = true_MatlabRTW;
  } else {
    *rty_y = ((!rtu_R2_F) && rtb_UnitDelay_j);
  }

  /* End of Switch: '<S62>/SWT' */

  /* Update for Atomic SubSystem: '<S56>/Delay' */
  SWC_ETE_type_Delay_l_Update(*rty_y,
    &SWC_ETE_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Update for SubSystem: '<S56>/Delay' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
