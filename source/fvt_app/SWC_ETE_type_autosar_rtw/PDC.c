/*
 * File: PDC.c
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
#include "PDC.h"
#include "rt_sys_ADC_RDC_Read_19.h"
#include <math.h>

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/* Named constants for Chart: '<S184>/SS_SafetyShutdown_Ctrl' */
#define SWC_ETE_type_IN_ASC_Dwn        ((uint8)1U)
#define SWC_ETE_type_IN_ASC_Up         ((uint8)2U)
#define SWC_ETE_type_IN_FWL            ((uint8)3U)
#define SWC_ETE_type_IN_Normal         ((uint8)4U)

/*
 * Output and update for atomic system:
 *    '<S190>/SetSVMR_DeadTimeCompensation_PhsA'
 *    '<S190>/SetSVMR_DeadTimeCompensation_PhsB'
 *    '<S190>/SetSVMR_DeadTimeCompensation_PhsC'
 */
void SetSVMR_DeadTimeCompensation_Ph(float32 rtu_LeSVMC_I_Lis, float32
  rtu_LeSVMC_Pct_p_Duty_in, float32 rtu_VaSVMR_K_DeadTimeCmp_Slope, float32
  rtu_VaSVMR_Pct_DeadTimeCmp, float32 *rty_LeSVMC_Pct_p_Duty)
{
  /* If: '<S194>/If' incorporates:
   *  Constant: '<S194>/Constant'
   *  Constant: '<S194>/Constant1'
   *  Logic: '<S194>/Logical Operator'
   *  RelationalOperator: '<S194>/Relational Operator'
   *  RelationalOperator: '<S194>/Relational Operator1'
   */
  if ((rtu_LeSVMC_Pct_p_Duty_in > 0.0F) && (rtu_LeSVMC_Pct_p_Duty_in < 1.0F)) {
    float32 rtb_Product_a;

    /* Outputs for IfAction SubSystem: '<S194>/compensate' incorporates:
     *  ActionPort: '<S200>/Action Port'
     */
    /* Product: '<S200>/Product' */
    rtb_Product_a = rtu_VaSVMR_K_DeadTimeCmp_Slope * rtu_LeSVMC_I_Lis;

    /* Switch: '<S200>/Switch' incorporates:
     *  Gain: '<S200>/Gain'
     *  RelationalOperator: '<S200>/Relational Operator'
     *  RelationalOperator: '<S200>/Relational Operator1'
     *  Switch: '<S200>/Switch1'
     */
    if (rtb_Product_a > rtu_VaSVMR_Pct_DeadTimeCmp) {
      /* Switch: '<S200>/Switch' */
      rtb_Product_a = rtu_VaSVMR_Pct_DeadTimeCmp;
    } else if (rtb_Product_a < -rtu_VaSVMR_Pct_DeadTimeCmp) {
      /* Switch: '<S200>/Switch1' incorporates:
       *  Gain: '<S200>/Gain'
       *  Switch: '<S200>/Switch'
       */
      rtb_Product_a = -rtu_VaSVMR_Pct_DeadTimeCmp;
    }

    /* End of Switch: '<S200>/Switch' */

    /* Sum: '<S200>/Add' */
    *rty_LeSVMC_Pct_p_Duty = rtu_LeSVMC_Pct_p_Duty_in + rtb_Product_a;

    /* End of Outputs for SubSystem: '<S194>/compensate' */
  } else {
    /* Outputs for IfAction SubSystem: '<S194>/no_compensate' incorporates:
     *  ActionPort: '<S201>/Action Port'
     */
    /* SignalConversion: '<S201>/Signal Conversion' */
    *rty_LeSVMC_Pct_p_Duty = rtu_LeSVMC_Pct_p_Duty_in;

    /* End of Outputs for SubSystem: '<S194>/no_compensate' */
  }

  /* End of If: '<S194>/If' */
}

/*
 * Output and update for atomic system:
 *    '<S190>/SetSVMR_SmartClamps_PhsA'
 *    '<S190>/SetSVMR_SmartClamps_PhsB'
 *    '<S190>/SetSVMR_SmartClamps_PhsC'
 */
void SWC_ET_SetSVMR_SmartClamps_PhsA(float32 rtu_LeSVMC_Pct_DC_Duty_in, float32
  rtu_VeSVMR_Pct_DC_FixedDutyOffs, float32 rtu_VaSVMR_Pct_DCMaxDuty_nom, float32
  rtu_VaSVMR_Pct_DCMinDuty_nom, float32 rtu_VaSVMR_Pct_DCMaxDutyRound, float32
  rtu_VaSVMR_Pct_DCMinDutyRound, float32 *rty_LeSVMC_Pct_DC_Duty, const
  ConstB_SetSVMR_SmartClamps_Ph_T *localC)
{
  float32 rtb_Add_h;

  /* If: '<S197>/If' incorporates:
   *  Constant: '<S197>/Constant'
   *  Constant: '<S197>/Constant1'
   *  Logic: '<S197>/Logical Operator'
   *  RelationalOperator: '<S197>/Relational Operator'
   *  RelationalOperator: '<S206>/Relational Operator'
   *  RelationalOperator: '<S206>/Relational Operator2'
   *  Switch: '<S206>/Switch'
   *  Switch: '<S206>/Switch2'
   */
  if ((KeSVMR_b_UseStrictClamp == 1.0F) && localC->RelationalOperator1) {
    /* Outputs for IfAction SubSystem: '<S197>/StrictClamping' incorporates:
     *  ActionPort: '<S207>/Action Port'
     */
    /* Sum: '<S207>/Add' */
    rtb_Add_h = rtu_VeSVMR_Pct_DC_FixedDutyOffs + rtu_LeSVMC_Pct_DC_Duty_in;

    /* Switch: '<S207>/Switch' incorporates:
     *  RelationalOperator: '<S207>/Relational Operator'
     *  RelationalOperator: '<S207>/Relational Operator1'
     *  Switch: '<S207>/Switch2'
     */
    if (rtb_Add_h > rtu_VaSVMR_Pct_DCMaxDuty_nom) {
      *rty_LeSVMC_Pct_DC_Duty = rtu_VaSVMR_Pct_DCMaxDuty_nom;
    } else if (rtb_Add_h < rtu_VaSVMR_Pct_DCMinDuty_nom) {
      /* Switch: '<S207>/Switch2' */
      *rty_LeSVMC_Pct_DC_Duty = rtu_VaSVMR_Pct_DCMinDuty_nom;
    } else {
      *rty_LeSVMC_Pct_DC_Duty = rtb_Add_h;
    }

    /* End of Switch: '<S207>/Switch' */
    /* End of Outputs for SubSystem: '<S197>/StrictClamping' */

    /* Outputs for IfAction SubSystem: '<S197>/SmartClamping' incorporates:
     *  ActionPort: '<S206>/Action Port'
     */
  } else if (rtu_LeSVMC_Pct_DC_Duty_in > rtu_VaSVMR_Pct_DCMaxDuty_nom) {
    /* Switch: '<S206>/Switch1' incorporates:
     *  Constant: '<S206>/Constant1'
     *  RelationalOperator: '<S206>/Relational Operator1'
     *  Switch: '<S206>/Switch'
     */
    if (rtu_LeSVMC_Pct_DC_Duty_in > rtu_VaSVMR_Pct_DCMaxDutyRound) {
      *rty_LeSVMC_Pct_DC_Duty = 1.0F;
    } else {
      *rty_LeSVMC_Pct_DC_Duty = rtu_VaSVMR_Pct_DCMaxDuty_nom;
    }
  } else if (rtu_LeSVMC_Pct_DC_Duty_in < rtu_VaSVMR_Pct_DCMinDuty_nom) {
    /* Switch: '<S206>/Switch3' incorporates:
     *  RelationalOperator: '<S206>/Relational Operator3'
     *  Switch: '<S206>/Switch'
     *  Switch: '<S206>/Switch2'
     */
    if (rtu_LeSVMC_Pct_DC_Duty_in < rtu_VaSVMR_Pct_DCMinDutyRound) {
      /* Switch: '<S206>/Switch2' incorporates:
       *  Constant: '<S206>/Constant2'
       *  Switch: '<S206>/Switch1'
       */
      *rty_LeSVMC_Pct_DC_Duty = 0.0F;
    } else {
      /* Switch: '<S206>/Switch2' incorporates:
       *  Switch: '<S206>/Switch1'
       */
      *rty_LeSVMC_Pct_DC_Duty = rtu_VaSVMR_Pct_DCMinDuty_nom;
    }

    /* End of Switch: '<S206>/Switch3' */
  } else {
    /* Switch: '<S206>/Switch' incorporates:
     *  Switch: '<S206>/Switch1'
     *  Switch: '<S206>/Switch2'
     */
    *rty_LeSVMC_Pct_DC_Duty = rtu_LeSVMC_Pct_DC_Duty_in;

    /* End of Outputs for SubSystem: '<S197>/SmartClamping' */
  }

  /* End of If: '<S197>/If' */
}

/* System initialize for atomic system: '<S3>/PDC' */
void SWC_ETE_type_PDC_Init(void)
{
  /* Start for If: '<S185>/If' */
  SWC_ETE_type_ARID_DEF.If_ActiveSubsystem = -1;
}

/* Output and update for atomic system: '<S3>/PDC' */
void SWC_ETE_type_PDC(void)
{
  float32 rtb_Constant2_f;
  float32 rtb_Cos;
  float32 rtb_Divide_ed;
  float32 rtb_Divide_ey;
  float32 rtb_Divide_p;
  float32 rtb_Merge_i;
  float32 rtb_PDC_tiChange2;
  float32 rtb_PDC_tiChange3;
  float32 rtb_Product1_jb;
  float32 rtb_Product_pm;
  float32 rtb_Sin;
  float32 rtb_VeMCCR_I_Idx;
  float32 rtb_VeMCCR_I_Iqx;
  sint32 rtb_PDC_noSector;
  sint8 rtPrevAction;
  uint8 rtb_SS_u8_SafetySts_null;

  /* Outputs for Atomic SubSystem: '<S170>/DIV5' */
  /* Constant: '<S170>/Constant3' */
  SWC_ETE_type_DIV2(1.0F, SWC_ETE_type_ConstB.DataTypeConversion, &rtb_Divide_ey);

  /* End of Outputs for SubSystem: '<S170>/DIV5' */

  /* Outputs for Atomic SubSystem: '<S173>/DIV5' */
  /* Constant: '<S173>/Constant3' */
  SWC_ETE_type_DIV2(1.0F, SWC_ETE_type_ConstB.DataTypeConversion, &rtb_Divide_p);

  /* End of Outputs for SubSystem: '<S173>/DIV5' */

  /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
   *  Constant: '<S172>/Constant'
   *  Product: '<S172>/Product'
   */
  rtb_PDC_tiChange3 = VFOC_VcmdAlpha_V * 0.866F;

  /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
   *  Constant: '<S172>/Constant1'
   *  Product: '<S172>/Product1'
   */
  rtb_PDC_tiChange2 = VFOC_VcmdBeta_V * 0.5F;

  /* Sum: '<S172>/Add' incorporates:
   *  Constant: '<S172>/Constant3'
   *  Constant: '<S172>/Constant4'
   *  Constant: '<S172>/Constant5'
   *  Product: '<S172>/Product2'
   *  Product: '<S172>/Product3'
   *  Product: '<S172>/Product4'
   *  RelationalOperator: '<S172>/Relational Operator'
   *  RelationalOperator: '<S172>/Relational Operator1'
   *  RelationalOperator: '<S172>/Relational Operator2'
   */
  rtb_PDC_noSector = ((rtb_PDC_tiChange3 >= rtb_PDC_tiChange2 ? 2 : 0) +
                      (-rtb_PDC_tiChange3 >= rtb_PDC_tiChange2 ? 4 : 0)) +
    (VFOC_VcmdBeta_V >= 0.0F);

  /* Product: '<S173>/Product' incorporates:
   *  Constant: '<S173>/Constant'
   *  Constant: '<S188>/Constant2'
   */
  rtb_Constant2_f = VFOC_VcmdAlpha_V * 1.732F;

  /* Product: '<S173>/Product1' incorporates:
   *  Constant: '<S173>/Constant1'
   */
  rtb_PDC_tiChange3 = VFOC_DCBusVoltage_V * 2.0F;

  /* Outputs for Atomic SubSystem: '<S173>/DIV' */
  /* Sum: '<S173>/Add1' */
  SWC_ETE_type_DIV2(VFOC_VcmdBeta_V - rtb_Constant2_f, rtb_PDC_tiChange3,
                    &rtb_PDC_tiChange2);

  /* End of Outputs for SubSystem: '<S173>/DIV' */

  /* Outputs for Atomic SubSystem: '<S173>/DIV1' */
  /* Sum: '<S173>/Add' */
  SWC_ETE_type_DIV2(rtb_Constant2_f + VFOC_VcmdBeta_V, rtb_PDC_tiChange3,
                    &rtb_Divide_ed);

  /* End of Outputs for SubSystem: '<S173>/DIV1' */

  /* Outputs for Atomic SubSystem: '<S173>/DIV2' */
  SWC_ETE_type_DIV2(VFOC_VcmdBeta_V, VFOC_DCBusVoltage_V, &rtb_Constant2_f);

  /* End of Outputs for SubSystem: '<S173>/DIV2' */

  /* MultiPortSwitch: '<S173>/Multiport Switch' */
  switch (rtb_PDC_noSector) {
   case 1:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant5'
     *  Product: '<S173>/Product2'
     */
    rtb_PDC_tiChange3 = rtb_PDC_tiChange2 * rtb_Divide_p * 1.732F;

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant2'
     *  Product: '<S173>/Product3'
     */
    rtb_Divide_ed = rtb_Divide_ed * rtb_Divide_p * 1.732F;
    break;

   case 2:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant2'
     *  Product: '<S173>/Product3'
     */
    rtb_PDC_tiChange3 = rtb_Divide_ed * rtb_Divide_p * 1.732F;

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant4'
     *  Gain: '<S173>/Gain3'
     *  Product: '<S173>/Product4'
     */
    rtb_Divide_ed = -(rtb_Constant2_f * rtb_Divide_p * 1.732F);
    break;

   case 3:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant5'
     *  Gain: '<S173>/Gain'
     *  Product: '<S173>/Product2'
     */
    rtb_PDC_tiChange3 = -(rtb_PDC_tiChange2 * rtb_Divide_p * 1.732F);

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant4'
     *  Product: '<S173>/Product4'
     */
    rtb_Divide_ed = rtb_Constant2_f * rtb_Divide_p * 1.732F;
    break;

   case 4:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant4'
     *  Gain: '<S173>/Gain1'
     *  Product: '<S173>/Product4'
     */
    rtb_PDC_tiChange3 = -(rtb_Constant2_f * rtb_Divide_p * 1.732F);

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant5'
     *  Product: '<S173>/Product2'
     */
    rtb_Divide_ed = rtb_PDC_tiChange2 * rtb_Divide_p * 1.732F;
    break;

   case 5:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant4'
     *  Product: '<S173>/Product4'
     */
    rtb_PDC_tiChange3 = rtb_Constant2_f * rtb_Divide_p * 1.732F;

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant2'
     *  Gain: '<S173>/Gain4'
     *  Product: '<S173>/Product3'
     */
    rtb_Divide_ed = -(rtb_Divide_ed * rtb_Divide_p * 1.732F);
    break;

   default:
    /* MultiPortSwitch: '<S173>/Multiport Switch' incorporates:
     *  Constant: '<S173>/Constant2'
     *  Gain: '<S173>/Gain2'
     *  Product: '<S173>/Product3'
     */
    rtb_PDC_tiChange3 = -(rtb_Divide_ed * rtb_Divide_p * 1.732F);

    /* MultiPortSwitch: '<S173>/Multiport Switch1' incorporates:
     *  Constant: '<S173>/Constant5'
     *  Gain: '<S173>/Gain5'
     *  Product: '<S173>/Product2'
     */
    rtb_Divide_ed = -(rtb_PDC_tiChange2 * rtb_Divide_p * 1.732F);
    break;
  }

  /* End of MultiPortSwitch: '<S173>/Multiport Switch' */

  /* Chart: '<S226>/Overmodulation'
   *
   * Block description for '<S226>/Overmodulation':
   *  The duty limitation, which limit to peak duty.
   *  T1 = T1 * Duty_max / ( T1 + T2 );
   *  T2 = T2 * Duty_max / ( T1 + T2 );
   */
  rtb_Constant2_f = rtb_PDC_tiChange3 + rtb_Divide_ed;
  if (rtb_Constant2_f > rtb_Divide_p) {
    if ((rtb_PDC_tiChange3 <= rtb_Divide_p) && (rtb_Divide_ed <= rtb_Divide_p))
    {
      rtb_Constant2_f = rtb_Divide_p / rtb_Constant2_f;
      rtb_PDC_tiChange3 *= rtb_Constant2_f;
      rtb_Divide_ed *= rtb_Constant2_f;
    } else if ((rtb_PDC_tiChange3 > rtb_Divide_p) && (rtb_PDC_tiChange3 >
                rtb_Divide_ed)) {
      rtb_PDC_tiChange3 = rtb_Divide_p;
      rtb_Divide_ed = 0.0F;
    } else if ((rtb_Divide_ed > rtb_Divide_p) && (rtb_Divide_ed >
                rtb_PDC_tiChange3)) {
      rtb_PDC_tiChange3 = 0.0F;
      rtb_Divide_ed = rtb_Divide_p;
    } else {
      rtb_PDC_tiChange3 = rtb_Divide_p / 2.0F;
      rtb_Divide_ed = rtb_PDC_tiChange3;
    }
  }

  /* End of Chart: '<S226>/Overmodulation' */

  /* MultiPortSwitch: '<S170>/Multiport Switch' incorporates:
   *  Constant: '<S170>/Constant'
   *  Constant: '<S170>/Constant1'
   *  Constant: '<S170>/Constant2'
   *  Constant: '<S188>/Constant2'
   *  Product: '<S170>/Product'
   *  Product: '<S170>/Product1'
   *  Product: '<S170>/Product2'
   *  Sum: '<S170>/Add'
   *  Sum: '<S170>/Add1'
   *  Sum: '<S170>/Add2'
   */
  switch (rtb_PDC_noSector) {
   case 1:
    /* Sum: '<S170>/Add2' incorporates:
     *  Sum: '<S170>/Add'
     */
    rtb_Divide_p = rtb_Divide_ey + rtb_PDC_tiChange3;
    rtb_Constant2_f = (rtb_Divide_p - rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant'
     *  Constant: '<S170>/Constant1'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product'
     *  Product: '<S170>/Product1'
     *  Sum: '<S170>/Add1'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange2 = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant2'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     */
    rtb_PDC_tiChange3 = (rtb_Divide_p + rtb_Divide_ed) * 0.25F;
    break;

   case 2:
    rtb_Constant2_f = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;

    /* Sum: '<S170>/Add' incorporates:
     *  Constant: '<S170>/Constant'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product'
     *  Sum: '<S170>/Add1'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange3 += rtb_Divide_ey;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant2'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     */
    rtb_PDC_tiChange2 = (rtb_PDC_tiChange3 + rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant1'
     *  Product: '<S170>/Product1'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange3 = (rtb_PDC_tiChange3 - rtb_Divide_ed) * 0.25F;
    break;

   case 3:
    rtb_Constant2_f = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;

    /* Sum: '<S170>/Add2' incorporates:
     *  Constant: '<S170>/Constant'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product'
     *  Sum: '<S170>/Add'
     *  Sum: '<S170>/Add1'
     */
    rtb_PDC_tiChange3 += rtb_Divide_ey;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant1'
     *  Product: '<S170>/Product1'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange2 = (rtb_PDC_tiChange3 - rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant2'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     */
    rtb_PDC_tiChange3 = (rtb_PDC_tiChange3 + rtb_Divide_ed) * 0.25F;
    break;

   case 4:
    /* Sum: '<S170>/Add' incorporates:
     *  Sum: '<S170>/Add2'
     */
    rtb_Divide_p = rtb_Divide_ey + rtb_PDC_tiChange3;
    rtb_Constant2_f = (rtb_Divide_p + rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant1'
     *  Constant: '<S170>/Constant2'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product1'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange2 = (rtb_Divide_p - rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant'
     *  Product: '<S170>/Product'
     *  Sum: '<S170>/Add1'
     */
    rtb_PDC_tiChange3 = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;
    break;

   case 5:
    /* Sum: '<S170>/Add' incorporates:
     *  Sum: '<S170>/Add2'
     */
    rtb_Divide_p = rtb_Divide_ey + rtb_PDC_tiChange3;
    rtb_Constant2_f = (rtb_Divide_p + rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant'
     *  Constant: '<S170>/Constant2'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     *  Sum: '<S170>/Add1'
     */
    rtb_PDC_tiChange2 = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant1'
     *  Product: '<S170>/Product1'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange3 = (rtb_Divide_p - rtb_Divide_ed) * 0.25F;
    break;

   default:
    /* Sum: '<S170>/Add2' incorporates:
     *  Sum: '<S170>/Add'
     */
    rtb_Divide_p = rtb_Divide_ey + rtb_PDC_tiChange3;
    rtb_Constant2_f = (rtb_Divide_p - rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch1' incorporates:
     *  Constant: '<S170>/Constant1'
     *  Constant: '<S170>/Constant2'
     *  Constant: '<S188>/Constant2'
     *  Product: '<S170>/Product1'
     *  Product: '<S170>/Product2'
     *  Sum: '<S170>/Add'
     *  Sum: '<S170>/Add2'
     */
    rtb_PDC_tiChange2 = (rtb_Divide_p + rtb_Divide_ed) * 0.25F;

    /* MultiPortSwitch: '<S170>/Multiport Switch2' incorporates:
     *  Constant: '<S170>/Constant'
     *  Product: '<S170>/Product'
     *  Sum: '<S170>/Add1'
     */
    rtb_PDC_tiChange3 = ((rtb_Divide_ey - rtb_PDC_tiChange3) - rtb_Divide_ed) *
      0.25F;
    break;
  }

  /* End of MultiPortSwitch: '<S170>/Multiport Switch' */

  /* Trigonometry: '<S171>/Cos' */
  rtb_Cos = cosf(VROT_RotAngleV_rad);

  /* Switch: '<S184>/Switch' incorporates:
   *  Constant: '<S214>/Constant'
   *  RelationalOperator: '<S214>/Compare'
   */
  if (VROT_RotSpdM_rpm >= 0.0F) {
    /* Switch: '<S184>/Switch' */
    rtb_Divide_ey = VROT_RotSpdM_rpm;
  } else {
    /* Switch: '<S184>/Switch' incorporates:
     *  Gain: '<S184>/Gain'
     */
    rtb_Divide_ey = -VROT_RotSpdM_rpm;
  }

  /* End of Switch: '<S184>/Switch' */

  /* Switch: '<S184>/Switch1' */
  if (VDGH_PosSenrFaultLat_flg) {
    /* Switch: '<S216>/Switch2' incorporates:
     *  Constant: '<S184>/Constant1'
     *  Constant: '<S184>/Constant3'
     *  RelationalOperator: '<S216>/LowerRelop1'
     *  RelationalOperator: '<S216>/UpperRelop'
     *  Switch: '<S216>/Switch'
     */
    if (rtb_Divide_ey > KPDC_nPosnErrMaxSpd_C) {
      /* Switch: '<S184>/Switch1' incorporates:
       *  Switch: '<S216>/Switch2'
       */
      rtb_Divide_ey = KPDC_nPosnErrMaxSpd_C;
    } else if (rtb_Divide_ey < 0.0F) {
      /* Switch: '<S216>/Switch' incorporates:
       *  Constant: '<S184>/Constant3'
       *  Switch: '<S184>/Switch1'
       *  Switch: '<S216>/Switch2'
       */
      rtb_Divide_ey = 0.0F;
    }

    /* End of Switch: '<S216>/Switch2' */
  }

  /* End of Switch: '<S184>/Switch1' */

  /* Chart: '<S184>/SS_SafetyShutdown_Ctrl' incorporates:
   *  Constant: '<S184>/Constant2'
   *  Constant: '<S184>/Constant4'
   *  Constant: '<S184>/Constant7'
   */
  if (SWC_ETE_type_ARID_DEF.is_active_c1_pdc_grc == 0U) {
    SWC_ETE_type_ARID_DEF.is_active_c1_pdc_grc = 1U;
    SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_Normal;

    /* MCU is in normal state. */
    rtb_SS_u8_SafetySts_null = 1U;
  } else {
    switch (SWC_ETE_type_ARID_DEF.is_c1_pdc_grc) {
     case SWC_ETE_type_IN_ASC_Dwn:
      rtb_SS_u8_SafetySts_null = 2U;
      if (rtb_Divide_ey <= KDSM_DiagSpdL_rpm) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_FWL;

        /* The IGBT bridge is off */
        rtb_SS_u8_SafetySts_null = 0U;
      }
      break;

     case SWC_ETE_type_IN_ASC_Up:
      rtb_SS_u8_SafetySts_null = 3U;
      if (rtb_Divide_ey <= KDSM_DiagSpdL_rpm) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_FWL;

        /* The IGBT bridge is off */
        rtb_SS_u8_SafetySts_null = 0U;
      }
      break;

     case SWC_ETE_type_IN_FWL:
      rtb_SS_u8_SafetySts_null = 0U;
      if (rtb_Divide_ey >= KDSM_DiagSpdH_rpm) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_ASC_Dwn;

        /* The down bridge is short circuit */
        rtb_SS_u8_SafetySts_null = 2U;
      } else if (KDSM_bIvtrTarHiDebug_flg) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_Normal;

        /* MCU is in normal state. */
        rtb_SS_u8_SafetySts_null = 1U;
      }
      break;

     default:
      /* case IN_Normal: */
      rtb_SS_u8_SafetySts_null = 1U;
      if (VDGH_FaultLevel2_flg && (rtb_Divide_ey >= KDSM_DiagSpdH_rpm)) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_ASC_Dwn;

        /* The down bridge is short circuit */
        rtb_SS_u8_SafetySts_null = 2U;
      } else if (VDGH_FaultLevel2_flg) {
        SWC_ETE_type_ARID_DEF.is_c1_pdc_grc = SWC_ETE_type_IN_FWL;

        /* The IGBT bridge is off */
        rtb_SS_u8_SafetySts_null = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<S184>/SS_SafetyShutdown_Ctrl' */

  /* Switch: '<S184>/Switch2' incorporates:
   *  Constant: '<S184>/Constant'
   *  Constant: '<S184>/Constant9'
   *  RelationalOperator: '<S184>/Relational Operator2'
   *  Switch: '<S184>/Switch3'
   *  Switch: '<S184>/Switch5'
   */
  if (KOSP_IvtrTarMor_enum_ovrdflg) {
    /* Switch: '<S184>/Switch2' incorporates:
     *  Constant: '<S184>/Constant12'
     */
    rtb_SS_u8_SafetySts_null = KOSP_IvtrTarMor_enum_ovrdval;
  } else if (SWC_ETE_type_ARID_DEF.Switch2_o == 5) {
    /* Switch: '<S184>/Switch5' incorporates:
     *  Constant: '<S184>/Constant5'
     *  Switch: '<S184>/Switch2'
     */
    rtb_SS_u8_SafetySts_null = 5U;
  } else if (!VDGH_FaultLevel2_flg) {
    /* Switch: '<S184>/Switch2' incorporates:
     *  Switch: '<S184>/Switch3'
     *  Switch: '<S184>/Switch5'
     */
    rtb_SS_u8_SafetySts_null = SWC_ETE_type_ARID_DEF.Switch2_o;
  }

  /* End of Switch: '<S184>/Switch2' */

  /* Trigonometry: '<S171>/Sin' */
  rtb_Sin = sinf(VROT_RotAngleV_rad);

  /* Outputs for Atomic SubSystem: '<S183>/ReInitSVMR_DeadTimeCompensation' */
  /* Product: '<S188>/Product' incorporates:
   *  Constant: '<S188>/Constant'
   *  Constant: '<S188>/Constant2'
   */
  rtb_Product_pm = KeSVMR_t_DeadTime * (float32)KeSVMR_PWMPrd_cnt;

  /* Product: '<S188>/Product1' incorporates:
   *  Constant: '<S188>/Constant3'
   *  Constant: '<S188>/Constant4'
   *  Product: '<S188>/Divide1'
   */
  rtb_Product1_jb = 1.0F / KeSVMR_FullDTCCurr_A * rtb_Product_pm;

  /* End of Outputs for SubSystem: '<S183>/ReInitSVMR_DeadTimeCompensation' */

  /* Outputs for Atomic SubSystem: '<S183>/ReInitSVMR_PWM_Modulation' */
  /* If: '<S189>/If' incorporates:
   *  Constant: '<S189>/Constant5'
   *  Constant: '<S189>/Constant6'
   *  Logic: '<S189>/Logical Operator'
   *  RelationalOperator: '<S189>/Relational Operator2'
   */
  if ((KeSVMR_b_UseStrictClamp == 1.0F) &&
      SWC_ETE_type_ConstB.RelationalOperator1_h) {
    /* Outputs for IfAction SubSystem: '<S189>/SVPWM_StrictClamp' incorporates:
     *  ActionPort: '<S213>/Action Port'
     */
    /* Merge: '<S189>/Merge2' incorporates:
     *  Constant: '<S213>/Constant'
     *  Constant: '<S213>/Constant1'
     *  Constant: '<S213>/Constant2'
     *  Constant: '<S213>/Constant3'
     *  Product: '<S213>/Product'
     *  Sum: '<S213>/Add'
     */
    rtb_Divide_ed = ((KeSVMR_StrClampMinDuty_pct + KeSVMR_StrClampMaxDuty_pct) -
                     1.0F) * 0.5F;

    /* Merge: '<S189>/Merge1' incorporates:
     *  Constant: '<S213>/Constant1'
     *  SignalConversion: '<S213>/Signal Conversion1'
     */
    rtb_Divide_p = KeSVMR_StrClampMaxDuty_pct;

    /* Merge: '<S189>/Merge' incorporates:
     *  Constant: '<S213>/Constant3'
     *  SignalConversion: '<S213>/Signal Conversion'
     */
    rtb_Divide_ey = KeSVMR_StrClampMinDuty_pct;

    /* End of Outputs for SubSystem: '<S189>/SVPWM_StrictClamp' */
  } else {
    /* Outputs for IfAction SubSystem: '<S189>/Not_SVPWM_StrictClamp' incorporates:
     *  ActionPort: '<S212>/Action Port'
     */
    /* Product: '<S212>/Product' incorporates:
     *  Constant: '<S189>/Constant2'
     *  Constant: '<S212>/Constant1'
     *  Constant: '<S212>/Constant5'
     *  Sum: '<S212>/Add'
     */
    rtb_Divide_ey = (KeSVMR_t_DeadTime + KeSVMR_t_MinPulseWidth) * (float32)
      KeSVMR_PWMPrd_cnt;

    /* Product: '<S212>/Product1' incorporates:
     *  Constant: '<S212>/Constant'
     *  Constant: '<S212>/Constant2'
     *  Constant: '<S212>/Constant3'
     *  Sum: '<S212>/Add1'
     *  Sum: '<S212>/Subtract'
     */
    SWC_ETE_type_ARID_DEF.Product1 = ((1.0F - rtb_Divide_ey) + 1.0F) * 0.5F;

    /* Merge: '<S189>/Merge1' incorporates:
     *  Constant: '<S212>/Constant'
     *  SignalConversion: '<S212>/Signal Conversion1'
     *  Sum: '<S212>/Subtract'
     */
    rtb_Divide_p = 1.0F - rtb_Divide_ey;

    /* Product: '<S212>/Product2' incorporates:
     *  Constant: '<S212>/Constant4'
     */
    SWC_ETE_type_ARID_DEF.Product2 = 0.5F * rtb_Divide_ey;

    /* Merge: '<S189>/Merge2' incorporates:
     *  Constant: '<S212>/Constant6'
     *  SignalConversion generated from: '<S212>/VeSVMR_Pct_DC_FixedDutyOffset'
     */
    rtb_Divide_ed = 0.0F;

    /* End of Outputs for SubSystem: '<S189>/Not_SVPWM_StrictClamp' */
  }

  /* End of If: '<S189>/If' */
  /* End of Outputs for SubSystem: '<S183>/ReInitSVMR_PWM_Modulation' */

  /* If: '<S187>/If2' incorporates:
   *  Constant: '<S183>/ReciSqrt3M1'
   *  RelationalOperator: '<S187>/Comparison3'
   */
  if (KeMCCR_b_UseMeasCrntDTC == 1) {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem5' incorporates:
     *  ActionPort: '<S192>/Action Port'
     */
    /* Merge: '<S187>/Merge3' incorporates:
     *  SignalConversion generated from: '<S192>/LeMCCR_I_TmpIq'
     */
    rtb_VeMCCR_I_Iqx = VCCM_iQCurrAct_A;

    /* Merge: '<S187>/Merge7' incorporates:
     *  SignalConversion generated from: '<S192>/LeMCCR_I_TmpId'
     */
    rtb_VeMCCR_I_Idx = VCCM_iDCurrAct_A;

    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem5' */
  } else {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem6' incorporates:
     *  ActionPort: '<S193>/Action Port'
     */
    /* Merge: '<S187>/Merge3' incorporates:
     *  SignalConversion generated from: '<S193>/VeMCDR_I_IsqCmd'
     */
    rtb_VeMCCR_I_Iqx = SWC_ETE_type_ARID_DEF.CCM_IqCmd;

    /* Merge: '<S187>/Merge7' incorporates:
     *  SignalConversion generated from: '<S193>/VeMCDR_I_IsdCmd'
     */
    rtb_VeMCCR_I_Idx = SWC_ETE_type_ARID_DEF.CCM_IdCmd;

    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem6' */
  }

  /* End of If: '<S187>/If2' */

  /* If: '<S187>/If' incorporates:
   *  Constant: '<S171>/Constant'
   *  Constant: '<S171>/Constant4'
   *  Constant: '<S190>/Constant'
   *  Gain: '<S190>/Gain12'
   *  Gain: '<S190>/Gain7'
   *  Product: '<S171>/Product3'
   *  Product: '<S171>/Product4'
   *  Product: '<S190>/Product4'
   *  Product: '<S190>/Product5'
   *  Sum: '<S171>/Subtract'
   *  Sum: '<S190>/Add2'
   *  Sum: '<S190>/Add3'
   */
  if (SWC_ETE_type_ConstB.LogicalOperator) {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem' incorporates:
     *  ActionPort: '<S190>/Action Port'
     */
    /* Merge: '<S196>/Merge' incorporates:
     *  Product: '<S190>/Product'
     *  Product: '<S190>/Product1'
     *  Sum: '<S190>/Add'
     */
    rtb_Merge_i = rtb_VeMCCR_I_Idx * rtb_Sin + rtb_VeMCCR_I_Iqx * rtb_Cos;

    /* Sum: '<S190>/Add1' incorporates:
     *  Product: '<S190>/Product2'
     *  Product: '<S190>/Product3'
     */
    rtb_Cos = rtb_VeMCCR_I_Idx * rtb_Cos - rtb_VeMCCR_I_Iqx * rtb_Sin;

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsB' */
    SetSVMR_DeadTimeCompensation_Ph(-0.5F * rtb_Cos + rtb_Merge_i * 0.86603F,
      1.0F - rtb_PDC_tiChange2 * SWC_ETE_type_ConstB.DataTypeConversion *
      KPDC_facScalePWM_C, rtb_Product1_jb, rtb_Product_pm, &rtb_Sin);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsB' */

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_SmartClamps_PhsB' */
    SWC_ET_SetSVMR_SmartClamps_PhsA(rtb_Sin, rtb_Divide_ed, rtb_Divide_p,
      rtb_Divide_ey, SWC_ETE_type_ARID_DEF.Product1,
      SWC_ETE_type_ARID_DEF.Product2, &rtb_PDC_tiChange2,
      &SWC_ETE_type_ConstB.SetSVMR_SmartClamps_PhsB);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_SmartClamps_PhsB' */

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsC' */
    SetSVMR_DeadTimeCompensation_Ph(-0.5F * rtb_Cos + rtb_Merge_i *
      SWC_ETE_type_ConstB.Gain1, 1.0F - rtb_PDC_tiChange3 *
      SWC_ETE_type_ConstB.DataTypeConversion * KPDC_facScalePWM_C,
      rtb_Product1_jb, rtb_Product_pm, &rtb_Merge_i);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsC' */

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_SmartClamps_PhsC' */
    SWC_ET_SetSVMR_SmartClamps_PhsA(rtb_Merge_i, rtb_Divide_ed, rtb_Divide_p,
      rtb_Divide_ey, SWC_ETE_type_ARID_DEF.Product1,
      SWC_ETE_type_ARID_DEF.Product2, &rtb_PDC_tiChange3,
      &SWC_ETE_type_ConstB.SetSVMR_SmartClamps_PhsC);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_SmartClamps_PhsC' */

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsA' */
    SetSVMR_DeadTimeCompensation_Ph(rtb_Cos, 1.0F - rtb_Constant2_f *
      SWC_ETE_type_ConstB.DataTypeConversion * KPDC_facScalePWM_C,
      rtb_Product1_jb, rtb_Product_pm, &rtb_Merge_i);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_DeadTimeCompensation_PhsA' */

    /* Outputs for Atomic SubSystem: '<S190>/SetSVMR_SmartClamps_PhsA' */
    SWC_ET_SetSVMR_SmartClamps_PhsA(rtb_Merge_i, rtb_Divide_ed, rtb_Divide_p,
      rtb_Divide_ey, SWC_ETE_type_ARID_DEF.Product1,
      SWC_ETE_type_ARID_DEF.Product2, &rtb_Constant2_f,
      &SWC_ETE_type_ConstB.SetSVMR_SmartClamps_PhsA);

    /* End of Outputs for SubSystem: '<S190>/SetSVMR_SmartClamps_PhsA' */
    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S191>/Action Port'
     */
    /* Merge: '<S187>/Merge' incorporates:
     *  Constant: '<S191>/Constant4'
     *  SignalConversion generated from: '<S191>/LeSVMC_Pct_DC_DutyA'
     */
    rtb_Constant2_f = 0.0F;

    /* Merge: '<S187>/Merge1' incorporates:
     *  Constant: '<S191>/Constant5'
     *  SignalConversion generated from: '<S191>/LeSVMC_Pct_DC_DutyB'
     */
    rtb_PDC_tiChange2 = 0.0F;

    /* Merge: '<S187>/Merge2' incorporates:
     *  Constant: '<S191>/Constant6'
     *  SignalConversion generated from: '<S191>/LeSVMC_Pct_DC_DutyC'
     */
    rtb_PDC_tiChange3 = 0.0F;

    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem1' */
  }

  /* End of If: '<S187>/If' */

  /* If: '<S185>/If' incorporates:
   *  Constant: '<S185>/C1'
   *  Constant: '<S185>/C2'
   *  Constant: '<S185>/C3'
   *  Constant: '<S185>/C4'
   */
  rtPrevAction = SWC_ETE_type_ARID_DEF.If_ActiveSubsystem;
  if (rtb_SS_u8_SafetySts_null == 1) {
    SWC_ETE_type_ARID_DEF.If_ActiveSubsystem = 0;
  } else if ((rtb_SS_u8_SafetySts_null == 2) || (rtb_SS_u8_SafetySts_null == 3))
  {
    SWC_ETE_type_ARID_DEF.If_ActiveSubsystem = 1;
  } else if (rtb_SS_u8_SafetySts_null == 0) {
    SWC_ETE_type_ARID_DEF.If_ActiveSubsystem = 2;
  } else {
    SWC_ETE_type_ARID_DEF.If_ActiveSubsystem = 3;
  }

  switch (SWC_ETE_type_ARID_DEF.If_ActiveSubsystem) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S185>/NormalPWM' incorporates:
     *  ActionPort: '<S217>/Action Port'
     */
    /* Merge: '<S185>/Merge2' incorporates:
     *  Constant: '<S217>/Constant'
     *  SignalConversion generated from: '<S217>/PDC_Ivtr1ModCmd'
     */
    VPDC_Ivtr1ModCmd_enum = 1U;

    /* End of Outputs for SubSystem: '<S185>/NormalPWM' */
    break;

   case 1:
    if (SWC_ETE_type_ARID_DEF.If_ActiveSubsystem != rtPrevAction) {
      /* SystemReset for IfAction SubSystem: '<S185>/ThreePhaseSC' incorporates:
       *  ActionPort: '<S220>/Action Port'
       */
      /* SystemReset for If: '<S185>/If' incorporates:
       *  Chart: '<S220>/ASC2'
       */
      SWC_ETE_type_ARID_DEF.Counter = 0U;

      /* End of SystemReset for SubSystem: '<S185>/ThreePhaseSC' */
    }

    /* Outputs for IfAction SubSystem: '<S185>/ThreePhaseSC' incorporates:
     *  ActionPort: '<S220>/Action Port'
     */
    /* Chart: '<S220>/ASC2' incorporates:
     *  Constant: '<S220>/Constant2'
     *  SignalConversion generated from: '<S221>/ SFunction '
     */
    if (!VCCM_bASCEna_flg) {
      SWC_ETE_type_ARID_DEF.ActDuty[0] = rtb_Constant2_f;
      SWC_ETE_type_ARID_DEF.ActDuty[1] = rtb_PDC_tiChange2;
      SWC_ETE_type_ARID_DEF.ActDuty[2] = rtb_PDC_tiChange3;

      /* Merge: '<S185>/Merge2' incorporates:
       *  SignalConversion generated from: '<S221>/ SFunction '
       */
      VPDC_Ivtr1ModCmd_enum = 1U;
    } else if (SWC_ETE_type_ARID_DEF.Counter < KPDC_FWCnt_C) {
      SWC_ETE_type_ARID_DEF.Counter++;

      /* Merge: '<S185>/Merge2' */
      VPDC_Ivtr1ModCmd_enum = 0U;
      SWC_ETE_type_ARID_DEF.ActDuty[0] = 0.5F;
      SWC_ETE_type_ARID_DEF.ActDuty[1] = 0.5F;
      SWC_ETE_type_ARID_DEF.ActDuty[2] = 0.5F;
    } else if (rtb_SS_u8_SafetySts_null == 2) {
      /* Merge: '<S185>/Merge2' */
      VPDC_Ivtr1ModCmd_enum = 2U;
      SWC_ETE_type_ARID_DEF.ActDuty[0] = 0.0F;
      SWC_ETE_type_ARID_DEF.ActDuty[1] = 0.0F;
      SWC_ETE_type_ARID_DEF.ActDuty[2] = 0.0F;
    } else {
      /* Merge: '<S185>/Merge2' */
      VPDC_Ivtr1ModCmd_enum = 3U;
      SWC_ETE_type_ARID_DEF.ActDuty[0] = 1.0F;
      SWC_ETE_type_ARID_DEF.ActDuty[1] = 1.0F;
      SWC_ETE_type_ARID_DEF.ActDuty[2] = 1.0F;
    }

    /* End of Chart: '<S220>/ASC2' */

    /* Switch: '<S186>/Switch' incorporates:
     *  SignalConversion generated from: '<S220>/PWM_Duty'
     */
    rtb_Constant2_f = SWC_ETE_type_ARID_DEF.ActDuty[0];
    rtb_PDC_tiChange2 = SWC_ETE_type_ARID_DEF.ActDuty[1];
    rtb_PDC_tiChange3 = SWC_ETE_type_ARID_DEF.ActDuty[2];

    /* End of Outputs for SubSystem: '<S185>/ThreePhaseSC' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S185>/PWMFW' incorporates:
     *  ActionPort: '<S218>/Action Port'
     */
    /* Switch: '<S186>/Switch' incorporates:
     *  Constant: '<S218>/0%'
     *  Constant: '<S218>/0%1'
     *  Constant: '<S218>/0%2'
     *  SignalConversion generated from: '<S218>/PWM_Duty'
     */
    rtb_Constant2_f = 0.5F;
    rtb_PDC_tiChange2 = 0.5F;
    rtb_PDC_tiChange3 = 0.5F;

    /* Merge: '<S185>/Merge2' incorporates:
     *  Constant: '<S218>/Constant'
     *  SignalConversion generated from: '<S218>/PDC_Ivtr1ModCmd'
     */
    VPDC_Ivtr1ModCmd_enum = 0U;


    /* End of Outputs for SubSystem: '<S185>/PWMFW' */
    break;

   default:
    /* Outputs for IfAction SubSystem: '<S185>/PWMGOFF' incorporates:
     *  ActionPort: '<S219>/Action Port'
     */
    /* Switch: '<S186>/Switch' incorporates:
     *  Constant: '<S219>/0%'
     *  Constant: '<S219>/0%1'
     *  Constant: '<S219>/0%2'
     *  SignalConversion generated from: '<S219>/PWM_Duty'
     */
    rtb_Constant2_f = 0.0F;
    rtb_PDC_tiChange2 = 0.0F;
    rtb_PDC_tiChange3 = 0.0F;

    /* Merge: '<S185>/Merge2' incorporates:
     *  SignalConversion generated from: '<S219>/PWMType'
     */
    VPDC_Ivtr1ModCmd_enum = rtb_SS_u8_SafetySts_null;

    /* End of Outputs for SubSystem: '<S185>/PWMGOFF' */
    break;
  }

  /* End of If: '<S185>/If' */

  /* Switch: '<S186>/Switch2' incorporates:
   *  Constant: '<S171>/PDC_rIvtrSaMor_C1'
   *  Constant: '<S171>/PDC_rIvtrSaMor_C2'
   *  RelationalOperator: '<S186>/LowerRelop1'
   *  RelationalOperator: '<S186>/UpperRelop'
   *  Switch: '<S186>/Switch'
   */
  if (rtb_Constant2_f > 1.0F) {
    /* Switch: '<S186>/Switch2' */
    SWC_ETE_type_ARID_DEF.Switch2[0] = 1.0F;
  } else if (rtb_Constant2_f < 0.0F) {
    /* Switch: '<S186>/Switch' incorporates:
     *  Constant: '<S171>/PDC_rIvtrSaMor_C2'
     *  Switch: '<S186>/Switch2'
     */
    SWC_ETE_type_ARID_DEF.Switch2[0] = 0.0F;
  } else {
    /* Switch: '<S186>/Switch2' incorporates:
     *  Switch: '<S186>/Switch'
     */
    SWC_ETE_type_ARID_DEF.Switch2[0] = rtb_Constant2_f;
  }

  if (rtb_PDC_tiChange2 > 1.0F) {
    /* Switch: '<S186>/Switch2' */
    SWC_ETE_type_ARID_DEF.Switch2[1] = 1.0F;
  } else if (rtb_PDC_tiChange2 < 0.0F) {
    /* Switch: '<S186>/Switch' incorporates:
     *  Constant: '<S171>/PDC_rIvtrSaMor_C2'
     *  Switch: '<S186>/Switch2'
     */
    SWC_ETE_type_ARID_DEF.Switch2[1] = 0.0F;
  } else {
    /* Switch: '<S186>/Switch2' incorporates:
     *  Switch: '<S186>/Switch'
     */
    SWC_ETE_type_ARID_DEF.Switch2[1] = rtb_PDC_tiChange2;
  }

  if (rtb_PDC_tiChange3 > 1.0F) {
    /* Switch: '<S186>/Switch2' */
    SWC_ETE_type_ARID_DEF.Switch2[2] = 1.0F;
  } else if (rtb_PDC_tiChange3 < 0.0F) {
    /* Switch: '<S186>/Switch' incorporates:
     *  Constant: '<S171>/PDC_rIvtrSaMor_C2'
     *  Switch: '<S186>/Switch2'
     */
    SWC_ETE_type_ARID_DEF.Switch2[2] = 0.0F;
  } else {
    /* Switch: '<S186>/Switch2' incorporates:
     *  Switch: '<S186>/Switch'
     */
    SWC_ETE_type_ARID_DEF.Switch2[2] = rtb_PDC_tiChange3;
  }

  /* End of Switch: '<S186>/Switch2' */

  /* DataTypeConversion: '<S171>/Data Type Conversion1' */
  VPDC_DutyA_raw = SWC_ETE_type_ARID_DEF.Switch2[0];

  /* DataTypeConversion: '<S171>/Data Type Conversion2' */
  VPDC_DutyB_raw = SWC_ETE_type_ARID_DEF.Switch2[1];

  /* DataTypeConversion: '<S171>/Data Type Conversion4' */
  VPDC_DutyC_raw = SWC_ETE_type_ARID_DEF.Switch2[2];

  /* Logic: '<S171>/Logical Operator' incorporates:
   *  Constant: '<S171>/C2'
   *  Constant: '<S171>/C3'
   *  RelationalOperator: '<S171>/Relational Operator1'
   *  RelationalOperator: '<S171>/Relational Operator2'
   */
  VPDC_bASCFlgRaw_flg = ((rtb_SS_u8_SafetySts_null == 3) ||
    (rtb_SS_u8_SafetySts_null == 2));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
