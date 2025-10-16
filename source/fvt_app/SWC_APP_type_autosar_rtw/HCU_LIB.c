/*
 * File: HCU_LIB.c
 *
 * Code generated for Simulink model 'SWC_APP_type'.
 *
 * Model version                  : 1.119
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Sep 24 14:15:55 2025
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtwtypes.h"
#include "HCU_LIB.h"

/*
 * Output and update for atomic system:
 *    '<S324>/override_signal_m2 '
 *    '<S327>/override_signal_m2 '
 *    '<S330>/override_signal_m2 '
 *    '<S333>/override_signal_m2 '
 *    '<S336>/override_signal_m2 '
 *    '<S339>/override_signal_m2 '
 *    '<S342>/override_signal_m2 '
 *    '<S355>/override_signal_m2 '
 *    '<S359>/override_signal_m2 '
 *    '<S370>/override_signal_m2 '
 *    ...
 */
boolean SWC_APP_type_override_signal_m2(boolean rtu_signal_raw, boolean
  rtu_cal_ovrdflg, boolean rtu_cal_ovrdval)
{
  boolean rty_signal_0;

  /* Switch: '<S326>/Switch1' */
  if (rtu_cal_ovrdflg) {
    rty_signal_0 = rtu_cal_ovrdval;
  } else {
    rty_signal_0 = rtu_signal_raw;
  }

  /* End of Switch: '<S326>/Switch1' */
  return rty_signal_0;
}

/*
 * Output and update for atomic system:
 *    '<S355>/signal validity checking'
 *    '<S359>/signal validity checking'
 *    '<S370>/signal validity checking'
 *    '<S374>/signal validity checking'
 *    '<S378>/signal validity checking'
 *    '<S402>/signal validity checking'
 *    '<S434>/signal validity checking'
 *    '<S438>/signal validity checking'
 *    '<S534>/signal validity checking'
 *    '<S538>/signal validity checking'
 *    ...
 */
boolean sig_valid_check(boolean rtu_new_signal, boolean rtu_new_signal_valid_flg,
  boolean rtu_def_value, ARID_DEF_sig_valid_check_T *SWC_APP_type__ARID_DEF_arg)
{
  boolean rty_valid_signal_0;

  /* Switch: '<S358>/Switch' incorporates:
   *  Logic: '<S358>/Logical Operator1'
   *  Switch: '<S358>/Switch1'
   */
  if (!rtu_new_signal_valid_flg) {
    rty_valid_signal_0 = rtu_def_value;
  } else {
    rty_valid_signal_0 = rtu_new_signal;
  }

  /* End of Switch: '<S358>/Switch' */

  /* Update for UnitDelay: '<S358>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rty_valid_signal_0;
  return rty_valid_signal_0;
}

/*
 * Output and update for atomic system:
 *    '<S363>/override_signal_m2 '
 *    '<S389>/override_signal_m2 '
 *    '<S393>/override_signal_m2 '
 *    '<S449>/override_signal_m2 '
 *    '<S453>/override_signal_m2 '
 *    '<S461>/override_signal_m2 '
 *    '<S465>/override_signal_m2 '
 *    '<S469>/override_signal_m2 '
 *    '<S473>/override_signal_m2 '
 *    '<S483>/override_signal_m2 '
 *    ...
 */
float32 SWC_APP_ty_override_signal_m2_m(float32 rtu_signal_raw, boolean
  rtu_cal_ovrdflg, float32 rtu_cal_ovrdval)
{
  float32 rty_signal_0;

  /* Switch: '<S365>/Switch1' */
  if (rtu_cal_ovrdflg) {
    rty_signal_0 = rtu_cal_ovrdval;
  } else {
    rty_signal_0 = rtu_signal_raw;
  }

  /* End of Switch: '<S365>/Switch1' */
  return rty_signal_0;
}

/*
 * Output and update for atomic system:
 *    '<S363>/signal validity checking'
 *    '<S389>/signal validity checking'
 *    '<S393>/signal validity checking'
 *    '<S449>/signal validity checking'
 *    '<S453>/signal validity checking'
 *    '<S461>/signal validity checking'
 *    '<S465>/signal validity checking'
 *    '<S469>/signal validity checking'
 *    '<S473>/signal validity checking'
 *    '<S483>/signal validity checking'
 *    ...
 */
float32 SWC_APP_type_sig_valid_check(float32 rtu_new_signal, boolean
  rtu_new_signal_valid_flg, float32 rtu_def_value, ARID_DEF_sig_valid_check_j_T *
  SWC_APP_type__ARID_DEF_arg)
{
  float32 rty_valid_signal_0;

  /* Switch: '<S366>/Switch' incorporates:
   *  Logic: '<S366>/Logical Operator1'
   *  Switch: '<S366>/Switch1'
   */
  if (!rtu_new_signal_valid_flg) {
    rty_valid_signal_0 = rtu_def_value;
  } else {
    rty_valid_signal_0 = rtu_new_signal;
  }

  /* End of Switch: '<S366>/Switch' */

  /* Update for UnitDelay: '<S366>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rty_valid_signal_0;
  return rty_valid_signal_0;
}

/*
 * Output and update for atomic system:
 *    '<S385>/override_signal_m2 '
 *    '<S406>/override_signal_m2 '
 *    '<S410>/override_signal_m2 '
 *    '<S414>/override_signal_m2 '
 *    '<S418>/override_signal_m2 '
 *    '<S426>/override_signal_m2 '
 *    '<S430>/override_signal_m2 '
 *    '<S457>/override_signal_m2 '
 *    '<S550>/override_signal_m2 '
 *    '<S554>/override_signal_m2 '
 *    ...
 */
uint8 SWC_APP_ty_override_signal_m2_p(uint8 rtu_signal_raw, boolean
  rtu_cal_ovrdflg, uint8 rtu_cal_ovrdval)
{
  uint8 rty_signal_0;

  /* Switch: '<S387>/Switch1' */
  if (rtu_cal_ovrdflg) {
    rty_signal_0 = rtu_cal_ovrdval;
  } else {
    rty_signal_0 = rtu_signal_raw;
  }

  /* End of Switch: '<S387>/Switch1' */
  return rty_signal_0;
}

/*
 * Output and update for atomic system:
 *    '<S385>/signal validity checking'
 *    '<S406>/signal validity checking'
 *    '<S410>/signal validity checking'
 *    '<S414>/signal validity checking'
 *    '<S418>/signal validity checking'
 *    '<S426>/signal validity checking'
 *    '<S430>/signal validity checking'
 *    '<S457>/signal validity checking'
 *    '<S550>/signal validity checking'
 *    '<S554>/signal validity checking'
 *    ...
 */
uint8 SWC_APP_type_sig_valid_check_i(uint8 rtu_new_signal, boolean
  rtu_new_signal_valid_flg, uint8 rtu_def_value, ARID_DEF_sig_valid_check_k_T
  *SWC_APP_type__ARID_DEF_arg)
{
  uint8 rty_valid_signal_0;

  /* Switch: '<S388>/Switch' incorporates:
   *  Logic: '<S388>/Logical Operator1'
   *  Switch: '<S388>/Switch1'
   */
  if (!rtu_new_signal_valid_flg) {
    rty_valid_signal_0 = rtu_def_value;
  } else {
    rty_valid_signal_0 = rtu_new_signal;
  }

  /* End of Switch: '<S388>/Switch' */

  /* Update for UnitDelay: '<S388>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rty_valid_signal_0;
  return rty_valid_signal_0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
