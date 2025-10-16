/*
 * File: EOP.c
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

#include "EOP.h"
#include <math.h>
#include "rtwtypes.h"
#include "look2_iflf_binlcapw.h"
#include "look1_iflf_binlcapw.h"

/* Includes for objects with custom storage classes */
#include "SWC_APP_type.h"

/* Output and update for atomic system: '<S2>/EOP' */
void SWC_APP_type_EOP(void)
{
  float32 rtb_MultiportSwitch1;
  float32 rtb_deltafalllimit;

  /* Outputs for Atomic SubSystem: '<S4>/EOP' */
  /* Switch: '<S125>/Switch1' incorporates:
   *  Constant: '<S125>/Constant12'
   */
  if (EopC_bMotEnaManTrig_C) {
    /* Switch: '<S125>/Switch1' incorporates:
     *  Constant: '<S125>/Constant11'
     */
    VEOP_bMotEnaReq_flg = EopC_bMotEnaMan_C;
  } else {
    /* MultiPortSwitch: '<S125>/Multiport Switch' */
    switch (SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRRunStatusSta_enum) {
     case 0:
      /* Switch: '<S125>/Switch1' incorporates:
       *  Constant: '<S131>/MPS_ReqMotSpdMor5'
       *  MultiPortSwitch: '<S125>/Multiport Switch'
       */
      VEOP_bMotEnaReq_flg = true_MatlabRTW;
      break;

     case 1:
      /* Switch: '<S125>/Switch1' incorporates:
       *  Constant: '<S128>/MPS_ReqMotSpdMor5'
       *  MultiPortSwitch: '<S125>/Multiport Switch'
       */
      VEOP_bMotEnaReq_flg = true_MatlabRTW;
      break;

     case 2:
      /* Switch: '<S125>/Switch1' incorporates:
       *  Constant: '<S126>/MPS_ReqMotSpdMor5'
       *  MultiPortSwitch: '<S125>/Multiport Switch'
       */
      VEOP_bMotEnaReq_flg = true_MatlabRTW;
      break;

     case 3:
      /* Switch: '<S125>/Switch1' incorporates:
       *  Constant: '<S127>/MPS_ReqMotSpdMor5'
       *  MultiPortSwitch: '<S125>/Multiport Switch'
       */
      VEOP_bMotEnaReq_flg = false_MatlabRTW;
      break;

     default:
      /* Switch: '<S125>/Switch1' incorporates:
       *  Constant: '<S127>/MPS_ReqMotSpdMor5'
       *  MultiPortSwitch: '<S125>/Multiport Switch'
       */
      VEOP_bMotEnaReq_flg = false_MatlabRTW;
      break;
    }

    /* End of MultiPortSwitch: '<S125>/Multiport Switch' */
  }

  /* End of Switch: '<S125>/Switch1' */

  /* MultiPortSwitch: '<S125>/Multiport Switch1' */
  switch (SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRRunStatusSta_enum) {
   case 0:
    /* MultiPortSwitch: '<S125>/Multiport Switch1' incorporates:
     *  Constant: '<S131>/MPS_ReqMotSpdMor11'
     *  Lookup_n-D: '<S131>/EopC_nRrOilTemp_M'
     *  Lookup_n-D: '<S131>/EopC_nRrTMTemp_T'
     *  MinMax: '<S125>/Max1'
     *  Product: '<S131>/Divide'
     *  Product: '<S131>/Product'
     *  Sum: '<S131>/Add'
     *  Switch: '<S125>/Switch2'
     *  Switch: '<S125>/Switch3'
     *  Switch: '<S125>/Switch5'
     *  Switch: '<S125>/Switch6'
     */
    rtb_MultiportSwitch1 = look2_iflf_binlcapw
      (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VMCM_TqAct_Nm *
       SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot /
       9550.0F, VFOC_ADCOilTemp_degC, &AEOP_nRrOilTempSpdMod_Y_KW[0],
       &AEOP_nRrOilTempSpdMod_X_degC[0], &MEOP_nRrOilTempSpdMod_Z_M[0],
       SWC_APP_type_ConstP.pooled26, 10U) + look1_iflf_binlcapw(fmaxf(fmaxf(0.0F,
      VFOC_ADCMotorVTemp_degC), VFOC_ADCMotorWTemp_degC),
      &AEOP_nRrTMTempSpdMod_X_degC[0], &MEOP_nRrTMTempSpdMod_Y_T[0], 9U);
    break;

   case 1:
    /* MultiPortSwitch: '<S125>/Multiport Switch1' incorporates:
     *  Constant: '<S128>/MPS_ReqMotSpdMor11'
     *  Lookup_n-D: '<S128>/EopC_nRrOilTempMotOptMod_M'
     *  Lookup_n-D: '<S128>/EopC_nRrTMTempMotOptMod_T'
     *  MinMax: '<S125>/Max1'
     *  Product: '<S128>/Divide'
     *  Product: '<S128>/Product'
     *  Sum: '<S128>/Add'
     *  Switch: '<S125>/Switch2'
     *  Switch: '<S125>/Switch3'
     *  Switch: '<S125>/Switch5'
     *  Switch: '<S125>/Switch6'
     */
    rtb_MultiportSwitch1 = look2_iflf_binlcapw
      (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VMCM_TqAct_Nm *
       SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot /
       9550.0F, VFOC_ADCOilTemp_degC, &AEOP_nRrOilTempSpdMod_Y_KW[0],
       &AEOP_nRrOilTempSpdMod_X_degC[0], &MEOP_nRrOilTempMotOptMod_Z_M[0],
       SWC_APP_type_ConstP.pooled26, 10U) + look1_iflf_binlcapw(fmaxf(fmaxf(0.0F,
      VFOC_ADCMotorVTemp_degC), VFOC_ADCMotorWTemp_degC),
      &AEOP_nRrTMTempSpdMod_X_degC[0], &MEOP_nRrTMTempMotOptMod_Y_T[0], 9U);
    break;

   case 2:
    /* MultiPortSwitch: '<S125>/Multiport Switch1' incorporates:
     *  Constant: '<S126>/MPS_ReqMotSpdMor11'
     *  Lookup_n-D: '<S126>/EopC_nRrOilTempDetOptMod_M'
     *  Lookup_n-D: '<S126>/EopC_nRrTMTempDetOptMod_T'
     *  MinMax: '<S125>/Max1'
     *  Product: '<S126>/Divide'
     *  Product: '<S126>/Product'
     *  Sum: '<S126>/Add'
     *  Switch: '<S125>/Switch2'
     *  Switch: '<S125>/Switch3'
     *  Switch: '<S125>/Switch5'
     *  Switch: '<S125>/Switch6'
     */
    rtb_MultiportSwitch1 = look2_iflf_binlcapw
      (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VMCM_TqAct_Nm *
       SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot /
       9550.0F, VFOC_ADCOilTemp_degC, &AEOP_nRrOilTempSpdMod_Y_KW[0],
       &AEOP_nRrOilTempSpdMod_X_degC[0], &MEOP_nRrOilTempDetOptMod_Z_M[0],
       SWC_APP_type_ConstP.pooled26, 10U) + look1_iflf_binlcapw(fmaxf(fmaxf(0.0F,
      VFOC_ADCMotorVTemp_degC), VFOC_ADCMotorWTemp_degC),
      &AEOP_nRrTMTempSpdMod_X_degC[0], &MEOP_nRrOilTempDetOptMod_Y_T[0], 9U);
    break;

   case 3:
    /* MultiPortSwitch: '<S125>/Multiport Switch1' incorporates:
     *  Constant: '<S127>/MPS_ReqMotSpdMor1'
     */
    rtb_MultiportSwitch1 = 0.0F;
    break;

   default:
    /* MultiPortSwitch: '<S125>/Multiport Switch1' incorporates:
     *  Constant: '<S127>/MPS_ReqMotSpdMor1'
     */
    rtb_MultiportSwitch1 = 0.0F;
    break;
  }

  /* End of MultiPortSwitch: '<S125>/Multiport Switch1' */

  /* Sum: '<S129>/Difference Inputs1' incorporates:
   *  UnitDelay: '<S129>/Delay Input2'
   *
   * Block description for '<S129>/Difference Inputs1':
   *
   *  Add in CPU
   *
   * Block description for '<S129>/Delay Input2':
   *
   *  Store in Global RAM
   */
  rtb_MultiportSwitch1 -= SWC_APP_type_ARID_DEF.DelayInput2_DSTATE_g;

  /* Switch: '<S132>/Switch2' incorporates:
   *  Constant: '<S125>/MPS_ReqMotSpdMor6'
   *  Product: '<S129>/delta rise limit'
   *  SampleTimeMath: '<S129>/sample time'
   *
   * About '<S129>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit = EopC_rSpdRampUp_C * 0.001F;

  /* Switch: '<S132>/Switch2' incorporates:
   *  RelationalOperator: '<S132>/LowerRelop1'
   */
  if (rtb_MultiportSwitch1 <= rtb_deltafalllimit) {
    /* Product: '<S129>/delta fall limit' incorporates:
     *  Constant: '<S125>/MPS_ReqMotSpdMor9'
     *  SampleTimeMath: '<S129>/sample time'
     *
     * About '<S129>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit = EopC_rSpdRampDown_C * 0.001F;

    /* Switch: '<S132>/Switch' incorporates:
     *  RelationalOperator: '<S132>/UpperRelop'
     */
    if (rtb_MultiportSwitch1 >= rtb_deltafalllimit) {
      /* Switch: '<S132>/Switch2' */
      rtb_deltafalllimit = rtb_MultiportSwitch1;
    }

    /* End of Switch: '<S132>/Switch' */
  }

  /* End of Switch: '<S132>/Switch2' */

  /* Sum: '<S129>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S129>/Delay Input2'
   *
   * Block description for '<S129>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S129>/Delay Input2':
   *
   *  Store in Global RAM
   */
  SWC_APP_type_ARID_DEF.DelayInput2_DSTATE_g += rtb_deltafalllimit;

  /* Switch: '<S125>/Switch4' incorporates:
   *  Constant: '<S125>/MPS_ReqMotSpdMorFlg1'
   */
  if (EopC_nReqMotSpdTrig_C) {
    /* Switch: '<S125>/Switch4' incorporates:
     *  Constant: '<S125>/MPS_ReqMotSpdMor10'
     */
    VEOP_nEOPSpdReq_rpm = EopC_nReqMotSpdMan_C;
  } else {
    /* Lookup_n-D: '<S125>/EopC_nReqMotSpdMax_T' incorporates:
     *  Switch: '<S125>/Switch6'
     */
    VEOP_nEOPSpdReq_rpm = look1_iflf_binlcapw(VFOC_ADCOilTemp_degC,
      &AEOP_nReqMotSpdMax_X_A[0], &MEOP_nReqMotSpdMax_Y_T[0], 4U);

    /* Switch: '<S130>/Switch2' incorporates:
     *  RelationalOperator: '<S130>/LowerRelop1'
     */
    if (SWC_APP_type_ARID_DEF.DelayInput2_DSTATE_g <= VEOP_nEOPSpdReq_rpm) {
      /* Switch: '<S130>/Switch' incorporates:
       *  Constant: '<S125>/MPS_ReqMotSpdMor5'
       *  RelationalOperator: '<S130>/UpperRelop'
       */
      if (SWC_APP_type_ARID_DEF.DelayInput2_DSTATE_g < EopC_nReqMotSpdMin_C) {
        /* Switch: '<S125>/Switch4' incorporates:
         *  Switch: '<S130>/Switch2'
         */
        VEOP_nEOPSpdReq_rpm = EopC_nReqMotSpdMin_C;
      } else {
        /* Switch: '<S125>/Switch4' incorporates:
         *  Switch: '<S130>/Switch2'
         */
        VEOP_nEOPSpdReq_rpm = SWC_APP_type_ARID_DEF.DelayInput2_DSTATE_g;
      }

      /* End of Switch: '<S130>/Switch' */
    }

    /* End of Switch: '<S130>/Switch2' */
  }

  /* End of Switch: '<S125>/Switch4' */

  /* Update for UnitDelay: '<S125>/Unit Delay' incorporates:
   *  Switch: '<S125>/Switch6'
   */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_d = VFOC_ADCOilTemp_degC;

  /* Update for UnitDelay: '<S125>/Unit Delay2' incorporates:
   *  Switch: '<S125>/Switch2'
   */
  SWC_APP_type_ARID_DEF.UnitDelay2_DSTATE_n = VFOC_ADCMotorVTemp_degC;

  /* Update for UnitDelay: '<S125>/Unit Delay3' incorporates:
   *  Switch: '<S125>/Switch5'
   */
  SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_m = VFOC_ADCMotorWTemp_degC;

  /* End of Outputs for SubSystem: '<S4>/EOP' */

  /* BusCreator: '<S4>/Bus Creator' */
  SWC_APP_type_ARID_DEF.BusCreator_c.VEOP_bMotEnaReq_flg = VEOP_bMotEnaReq_flg;
  SWC_APP_type_ARID_DEF.BusCreator_c.VEOP_nEOPSpdReq_rpm = VEOP_nEOPSpdReq_rpm;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
