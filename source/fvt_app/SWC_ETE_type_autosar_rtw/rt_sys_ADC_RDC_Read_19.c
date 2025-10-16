/*
 * File: rt_sys_ADC_RDC_Read_19.c
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
#include "rt_sys_ADC_RDC_Read_19.h"

/*
 * Output and update for atomic system:
 *    '<S20>/DIV2'
 *    '<S50>/DIV2'
 *    '<S170>/DIV5'
 *    '<S173>/DIV'
 *    '<S173>/DIV1'
 *    '<S173>/DIV2'
 *    '<S173>/DIV5'
 */
void SWC_ETE_type_DIV2(float32 rtu_In1, float32 rtu_In2, float32 *rty_Out)
{
  float64 tmp;

  /* Switch: '<S38>/SWT' incorporates:
   *  Constant: '<S29>/Constant1'
   *  Constant: '<S29>/Constant3'
   *  RelationalOperator: '<S35>/Relational Operator'
   *  RelationalOperator: '<S41>/Relational Operator'
   *  Switch: '<S42>/SWT'
   */
  if (rtu_In2 >= 0.0F) {
    /* Outputs for Atomic SubSystem: '<S29>/MAX' */
    /* Switch: '<S39>/SWT' incorporates:
     *  Constant: '<S29>/Constant2'
     *  RelationalOperator: '<S40>/Relational Operator'
     */
    if (rtu_In2 < 1.0E-15) {
      tmp = 1.0E-15;
    } else {
      tmp = rtu_In2;
    }

    /* End of Switch: '<S39>/SWT' */
    /* End of Outputs for SubSystem: '<S29>/MAX' */

    /* Outputs for Atomic SubSystem: '<S29>/MIN' */
  } else if (rtu_In2 > -1.0E-15) {
    /* Switch: '<S42>/SWT' incorporates:
     *  Constant: '<S29>/Constant3'
     */
    tmp = -1.0E-15;
  } else {
    tmp = rtu_In2;

    /* End of Outputs for SubSystem: '<S29>/MIN' */
  }

  /* Product: '<S29>/Divide' incorporates:
   *  Switch: '<S38>/SWT'
   */
  *rty_Out = (float32)(rtu_In1 / tmp);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
