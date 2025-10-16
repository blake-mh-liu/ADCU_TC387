/*
 * File: FOC_Mode_Judge.c
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

#include "FOC_Mode_Judge.h"
#include <math.h>
#include "rtwtypes.h"

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/* Output and update for atomic system: '<S3>/FOC_Mode_Judge' */
void SWC_ETE_type_FOC_Mode_Judge(void)
{
  float32 rtb_Switch2_h_idx_0;
  float32 rtb_Switch2_h_idx_1;
  float32 rtb_Switch2_h_idx_2;
  float32 rtb_Switch7_tmp;

  /* Switch: '<S12>/Switch7' incorporates:
   *  Constant: '<S12>/Constant10'
   *  Constant: '<S12>/Constant11'
   *  Constant: '<S12>/Constant17'
   *  Constant: '<S12>/Constant2'
   *  Constant: '<S3>/Constant13'
   *  Logic: '<S12>/Logical Operator'
   *  RelationalOperator: '<S12>/Equal'
   *  RelationalOperator: '<S12>/Equal1'
   *  RelationalOperator: '<S12>/Equal2'
   *  RelationalOperator: '<S12>/Equal4'
   *  Switch: '<S12>/Switch2'
   *  Switch: '<S12>/Switch3'
   */
  if ((KFOC_SensorMode_enum == 2) || (KFOC_SensorMode_enum == 3)) {
    /* DataTypeConversion: '<S12>/Data Type Conversion' incorporates:
     *  Switch: '<S12>/Switch7'
     */
    VFOC_VcmdAlpha_V = VCCM_uAlphaVoltTar_V;

    /* DataTypeConversion: '<S12>/Data Type Conversion1' incorporates:
     *  Switch: '<S12>/Switch7'
     */
    VFOC_VcmdBeta_V = VCCM_uBetaVoltTar_V;
  } else {
    if (KFOC_SensorMode_enum == 0) {
      /* Saturate: '<S12>/Saturation1' incorporates:
       *  Constant: '<S12>/Constant18'
       *  Switch: '<S12>/Switch2'
       */
      if (KFOC_VdCmd_V > 57.0F) {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_0 = 57.0F;
      } else if (KFOC_VdCmd_V < -57.0F) {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_0 = -57.0F;
      } else {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_0 = KFOC_VdCmd_V;
      }

      /* End of Saturate: '<S12>/Saturation1' */

      /* Saturate: '<S12>/Saturaton2' incorporates:
       *  Constant: '<S12>/Constant19'
       *  Switch: '<S12>/Switch2'
       */
      if (KFOC_VqCmd_V > 57.0F) {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_1 = 57.0F;
      } else if (KFOC_VqCmd_V < -57.0F) {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_1 = -57.0F;
      } else {
        /* Switch: '<S12>/Switch2' */
        rtb_Switch2_h_idx_1 = KFOC_VqCmd_V;
      }

      /* End of Saturate: '<S12>/Saturaton2' */

      /* Switch: '<S12>/Switch2' */
      rtb_Switch2_h_idx_2 = VROT_RotAngleE_rad;
    } else if (KFOC_SensorMode_enum == 1) {
      /* Saturate: '<S12>/Saturation' incorporates:
       *  Constant: '<S12>/Constant20'
       *  Switch: '<S12>/Switch2'
       *  Switch: '<S12>/Switch3'
       */
      if (KFOC_VdCmd_V > 57.0F) {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_0 = 57.0F;
      } else if (KFOC_VdCmd_V < -57.0F) {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_0 = -57.0F;
      } else {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_0 = KFOC_VdCmd_V;
      }

      /* End of Saturate: '<S12>/Saturation' */

      /* Saturate: '<S12>/Saturaton1' incorporates:
       *  Constant: '<S12>/Constant21'
       *  Switch: '<S12>/Switch2'
       *  Switch: '<S12>/Switch3'
       */
      if (KFOC_VqCmd_V > 57.0F) {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_1 = 57.0F;
      } else if (KFOC_VqCmd_V < -57.0F) {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_1 = -57.0F;
      } else {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Switch: '<S12>/Switch3'
         */
        rtb_Switch2_h_idx_1 = KFOC_VqCmd_V;
      }

      /* End of Saturate: '<S12>/Saturaton1' */

      /* Switch: '<S12>/Switch2' incorporates:
       *  Switch: '<S12>/Switch3'
       */
      rtb_Switch2_h_idx_2 = VFOC_FakeRotorPosn_rad;
    } else {
      /* Switch: '<S12>/Switch2' incorporates:
       *  Constant: '<S12>/Constant4'
       *  Constant: '<S12>/Constant5'
       *  Switch: '<S12>/Switch3'
       */
      rtb_Switch2_h_idx_0 = 0.0F;
      rtb_Switch2_h_idx_1 = 0.0F;
      rtb_Switch2_h_idx_2 = VROT_RotAngleE_rad;
    }

    /* Fcn: '<S169>/Fcn' incorporates:
     *  Constant: '<S12>/Constant11'
     *  Fcn: '<S169>/Fcn1'
     *  RelationalOperator: '<S12>/Equal1'
     *  Switch: '<S12>/Switch2'
     *  Switch: '<S12>/Switch3'
     */
    rtb_Switch7_tmp = sinf(rtb_Switch2_h_idx_2);
    rtb_Switch2_h_idx_2 = cosf(rtb_Switch2_h_idx_2);

    /* DataTypeConversion: '<S12>/Data Type Conversion' incorporates:
     *  Fcn: '<S169>/Fcn'
     *  Switch: '<S12>/Switch7'
     */
    VFOC_VcmdAlpha_V = rtb_Switch2_h_idx_2 * rtb_Switch2_h_idx_0 -
      rtb_Switch7_tmp * rtb_Switch2_h_idx_1;

    /* DataTypeConversion: '<S12>/Data Type Conversion1' incorporates:
     *  Fcn: '<S169>/Fcn1'
     *  Switch: '<S12>/Switch7'
     */
    VFOC_VcmdBeta_V = rtb_Switch7_tmp * rtb_Switch2_h_idx_0 +
      rtb_Switch2_h_idx_2 * rtb_Switch2_h_idx_1;
  }

  /* End of Switch: '<S12>/Switch7' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
