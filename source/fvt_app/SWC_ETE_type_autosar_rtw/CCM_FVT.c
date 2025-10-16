/*
 * File: CCM_FVT.c
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
#include "CCM_FVT.h"
#include <math.h>
#include "rt_sys_ADC_RDC_Read_19.h"
#include "rt_sys_ADC_RDC_Read_0.h"
#include "rt_sys_CCM_FVT_38.h"
#include "look1_iflf_binlcapw.h"
#include "look2_iflf_binlcapw.h"

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/*
 * Output and update for atomic system:
 *    '<S71>/Delay'
 *    '<S73>/Delay'
 *    '<S74>/Delay'
 */
void SWC_ETE_type_Delay_c(boolean rtu_u, boolean *rty_y,
  ARID_DEF_Delay_SWC_ETE_type_c_T *SWC_ETE_type__ARID_DEF_arg)
{
  /* UnitDelay: '<S84>/UnitDelay' */
  *rty_y = SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S84>/UnitDelay' */
  SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE = rtu_u;
}

/*
 * Output and update for atomic system:
 *    '<S58>/Rising'
 *    '<S58>/Rising1'
 */
void SWC_ETE_type_Rising(boolean rtu_In1, boolean *rty_Out1,
  ARID_DEF_Rising_SWC_ETE_type_T *SWC_ETE_type__ARID_DEF_arg)
{
  boolean rtb_UnitDelay_an;

  /* Outputs for Atomic SubSystem: '<S73>/Delay' */
  SWC_ETE_type_Delay_c(rtu_In1, &rtb_UnitDelay_an,
                       &SWC_ETE_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S73>/Delay' */

  /* Logic: '<S86>/AND1' incorporates:
   *  Logic: '<S88>/NOT1'
   */
  *rty_Out1 = (rtu_In1 && (!rtb_UnitDelay_an));
}

/* Output and update for atomic system: '<S3>/CCM_FVT' */
void SWC_ETE_type_CCM_FVT(void)
{
  float32 VCCM_iDCurrAct_A_tmp;
  float32 rtb_BattVolCirRadius;
  float32 rtb_CCM_facLPFiQAct_T1;
  float32 rtb_Divide_c;
  float32 rtb_LqMapp;
  float32 rtb_Max;
  float32 rtb_SWT;
  boolean rtb_AND1_i;
  boolean rtb_LogicalOperator_ct;
  boolean rtb_UnitDelay_gs;

  /* Lookup_n-D: '<S45>/CCM_facLPFiQAct_T1' incorporates:
   *  Abs: '<S45>/Abs1'
   */
  rtb_CCM_facLPFiQAct_T1 = fabsf(VROT_RotSpdM_rpm);

  /* Product: '<S96>/Divide' incorporates:
   *  Constant: '<S45>/Constant45'
   *  Constant: '<S45>/Constant46'
   *  Product: '<S45>/Product14'
   *  Product: '<S45>/Product15'
   *  Sum: '<S45>/Add12'
   *  Sum: '<S45>/Add13'
   */
  rtb_Divide_c = (VPCS_PhaUCur_A - (VPCS_PhaWCur_A + VPCS_PhaVCur_A) * 0.5F) *
    0.6667F;

  /* MinMax: '<S47>/Max' incorporates:
   *  Constant: '<S45>/Constant47'
   *  Product: '<S45>/Product16'
   *  Sum: '<S45>/Add14'
   */
  rtb_Max = (VPCS_PhaVCur_A - VPCS_PhaWCur_A) * 0.5773F;

  /* Fcn: '<S45>/Fcn4' incorporates:
   *  Fcn: '<S45>/Fcn5'
   */
  rtb_BattVolCirRadius = sinf(VROT_RotAngleE_rad);
  VCCM_iDCurrAct_A_tmp = cosf(VROT_RotAngleE_rad);

  /* Sum: '<S54>/Add' incorporates:
   *  Fcn: '<S45>/Fcn4'
   *  Lookup_n-D: '<S45>/CCM_facLPFiDAct_T1'
   *  Lookup_n-D: '<S45>/CCM_facLPFiQAct_T1'
   *  Product: '<S54>/Product'
   *  Sum: '<S54>/Subtract'
   *  UnitDelay: '<S54>/Unit Delay'
   */
  VCCM_iDCurrAct_A += ((rtb_Divide_c * VCCM_iDCurrAct_A_tmp + rtb_Max *
                        rtb_BattVolCirRadius) - VCCM_iDCurrAct_A) *
    look1_iflf_binlcapw(rtb_CCM_facLPFiQAct_T1, &ACCM_facLPFiDAct_X_rpm[0],
                        &MCCM_facLPFiDAct_Y_T[0], 10U);

  /* Logic: '<S43>/Logical Operator' incorporates:
   *  Constant: '<S43>/Constant'
   *  Logic: '<S43>/Logical Operator1'
   *  RelationalOperator: '<S43>/Relational Operator2'
   */
  rtb_LogicalOperator_ct = ((SWC_ETE_type_ARID_DEF.Switch2_o == 1) &&
    (!VDGH_FaultLevel2_flg));

  /* Switch: '<S77>/SWT' incorporates:
   *  Product: '<S94>/Product2'
   *  Sum: '<S94>/Subtract1'
   */
  rtb_SWT = rtb_LogicalOperator_ct ? SWC_ETE_type_ARID_DEF.CCM_IdCmd -
    VCCM_iDCurrAct_A : 0.0F;

  /* Switch: '<S43>/Switch2' incorporates:
   *  Switch: '<S43>/Switch1'
   *  UnitDelay: '<S43>/Unit Delay2'
   */
  if (VCCM_CurErrorOverThd_flg) {
    /* Switch: '<S43>/Switch1' incorporates:
     *  Constant: '<S43>/Constant3'
     */
    SWC_ETE_type_ARID_DEF.CCM_IqCmd = 0.0F;
  } else {
    /* Switch: '<S43>/Switch1' */
    SWC_ETE_type_ARID_DEF.CCM_IqCmd = SWC_ETE_type_ARID_DEF.Switch1;
  }

  /* End of Switch: '<S43>/Switch2' */

  /* Lookup_n-D: '<S48>/LqMapp' incorporates:
   *  Switch: '<S43>/Switch1'
   *  Switch: '<S43>/Switch3'
   */
  rtb_LqMapp = look2_iflf_binlcapw(SWC_ETE_type_ARID_DEF.CCM_IdCmd,
    SWC_ETE_type_ARID_DEF.CCM_IqCmd, &ACCM_facCCMLq_Y_A[0], &ACCM_facCCMLq_X_A[0],
    &MCCM_facCCMLq_Z_T[0], SWC_ETE_type_ConstP.pooled20, 36U);

  /* Gain: '<S48>/Gain3' incorporates:
   *  Gain: '<S48>/Gain'
   *  Product: '<S48>/Product4'
   *  Product: '<S48>/Product5'
   */
  VMCM_VdFwd_V = -(SWC_ETE_type_ARID_DEF.CCM_IqCmd * rtb_LqMapp *
                   VROT_RotSpdE_rads) * KMCM_DFwdCoef_null;

  /* Product: '<S94>/Product9' incorporates:
   *  Constant: '<S92>/TM_Id_Ki'
   *  Constant: '<S92>/TM_Id_Kt'
   *  Constant: '<S92>/TM_Prd'
   *  Product: '<S94>/Product1'
   *  Product: '<S94>/Product5'
   *  Product: '<S94>/Product6'
   *  Product: '<S94>/Product7'
   *  Sum: '<S94>/Add2'
   *  Sum: '<S94>/Subtract2'
   *  UnitDelay: '<S43>/Unit Delay'
   *  UnitDelay: '<S94>/Integral delay2'
   *  UnitDelay: '<S94>/Integral delay3'
   */
  SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE = rtb_LogicalOperator_ct ?
    (rtb_SWT * KCCM_IdKi_null * KCCM_CurLoopPrd_t +
     SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE) + KCCM_CurLoopPrd_t *
    KCCM_IdKt_null * (VCCM_VdCmd_V - VCCM_VdRef_V) : 0.0F;

  /* Sum: '<S94>/Add5' incorporates:
   *  Constant: '<S92>/Constant2'
   *  Lookup_n-D: '<S92>/MCCM_IdKp_value'
   *  Product: '<S92>/Product3'
   *  Product: '<S94>/Product'
   *  SignalConversion generated from: '<S20>/First_Order_Filter'
   */
  VCCM_VdRef_V = (rtb_SWT * look1_iflf_binlcapw(VROT_RotSpdM_rpm,
    &ACCM_IdKp_X_rpm[0], &MCCM_IdKp_Y_value[0], 19U) + VMCM_VdFwd_V *
                  KCCM_FwdMask_c) + SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE;

  /* Sum: '<S55>/Add' incorporates:
   *  Fcn: '<S45>/Fcn5'
   *  Lookup_n-D: '<S45>/CCM_facLPFiQAct_T1'
   *  Product: '<S55>/Product'
   *  Sum: '<S55>/Subtract'
   *  UnitDelay: '<S55>/Unit Delay'
   */
  VCCM_iQCurrAct_A += ((-rtb_Divide_c * rtb_BattVolCirRadius + rtb_Max *
                        VCCM_iDCurrAct_A_tmp) - VCCM_iQCurrAct_A) *
    look1_iflf_binlcapw(rtb_CCM_facLPFiQAct_T1, &ACCM_facLPFiDAct_X_rpm[0],
                        &MCCM_facLPFiQAct_Y_T[0], 10U);

  /* Switch: '<S77>/SWT' incorporates:
   *  Product: '<S95>/Product2'
   *  Sum: '<S95>/Subtract1'
   */
  rtb_SWT = rtb_LogicalOperator_ct ? SWC_ETE_type_ARID_DEF.CCM_IqCmd -
    VCCM_iQCurrAct_A : 0.0F;

  /* UnitDelay: '<S98>/Unit Delay' incorporates:
   *  Lookup_n-D: '<S48>/LdMapp'
   *  Switch: '<S43>/Switch1'
   *  Switch: '<S43>/Switch3'
   */
  rtb_CCM_facLPFiQAct_T1 = look2_iflf_binlcapw(SWC_ETE_type_ARID_DEF.CCM_IdCmd,
    SWC_ETE_type_ARID_DEF.CCM_IqCmd, &ACCM_facCCMLq_Y_A[0], &ACCM_facCCMLq_X_A[0],
    &MCCM_facCCMLd_Z_T[0], SWC_ETE_type_ConstP.pooled20, 36U);

  /* Gain: '<S48>/Gain2' incorporates:
   *  Constant: '<S48>/Constant2'
   *  Product: '<S48>/Product1'
   *  Product: '<S48>/Product2'
   *  Sum: '<S48>/Add'
   */
  VMCM_VqFwd_V = (SWC_ETE_type_ARID_DEF.CCM_IdCmd * rtb_CCM_facLPFiQAct_T1 +
                  KFOC_MagFluxLinkage_C) * VROT_RotSpdE_rads *
    KMCM_QFwdCoef_null;

  /* Product: '<S96>/Divide' incorporates:
   *  UnitDelay: '<S95>/Integral delay2'
   */
  rtb_Divide_c = VCCM_VqRef_V;

  /* Product: '<S95>/Product9' incorporates:
   *  Constant: '<S93>/TM_Id_Ki'
   *  Constant: '<S93>/TM_Id_Kt'
   *  Constant: '<S93>/TM_Prd'
   *  Product: '<S95>/Product1'
   *  Product: '<S95>/Product5'
   *  Product: '<S95>/Product6'
   *  Product: '<S95>/Product7'
   *  Sum: '<S95>/Add2'
   *  Sum: '<S95>/Subtract2'
   *  UnitDelay: '<S43>/Unit Delay1'
   *  UnitDelay: '<S95>/Integral delay2'
   *  UnitDelay: '<S95>/Integral delay3'
   */
  SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE_b = rtb_LogicalOperator_ct ?
    (rtb_SWT * KCCM_IqKi_null * KCCM_CurLoopPrd_t +
     SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE_b) + KCCM_CurLoopPrd_t *
    KCCM_IqKt_null * (VCCM_VqCmd_V - VCCM_VqRef_V) : 0.0F;

  /* Sum: '<S95>/Add5' incorporates:
   *  Constant: '<S93>/Constant2'
   *  Lookup_n-D: '<S93>/MCCM_IqKp_value'
   *  Product: '<S93>/Product3'
   *  Product: '<S95>/Product'
   *  SignalConversion generated from: '<S20>/First_Order_Filter'
   */
  VCCM_VqRef_V = (rtb_SWT * look1_iflf_binlcapw(VROT_RotSpdM_rpm,
    &ACCM_IdKp_X_rpm[0], &MCCM_IqKp_Y_value[0], 19U) + VMCM_VqFwd_V *
                  KCCM_FwdMask_c) +
    SWC_ETE_type_ARID_DEF.Integraldelay3_DSTATE_b;

  /* Switch: '<S50>/Switch2' incorporates:
   *  Constant: '<S50>/ReciSqrt3M3'
   *  Logic: '<S50>/Logical Operator'
   *  Switch: '<S50>/Switch3'
   */
  if (!KCCM_VdSpSwEna_flg) {
    /* Switch: '<S50>/Switch2' */
    VCCM_VdCmd_V = VCCM_VdRef_V;

    /* Switch: '<S50>/Switch3' */
    VCCM_VqCmd_V = VCCM_VqRef_V;
  } else {
    /* Switch: '<S50>/Switch2' incorporates:
     *  Constant: '<S50>/ReciSqrt3M1'
     */
    VCCM_VdCmd_V = KCCM_VdSp_V;

    /* Switch: '<S50>/Switch3' incorporates:
     *  Constant: '<S50>/ReciSqrt3M2'
     */
    VCCM_VqCmd_V = KCCM_VqSp_V;
  }

  /* End of Switch: '<S50>/Switch2' */

  /* Switch: '<S77>/SWT' incorporates:
   *  Math: '<S50>/Math'
   *  Math: '<S50>/Math1'
   *  Sum: '<S50>/Add'
   */
  rtb_SWT = VCCM_VdCmd_V * VCCM_VdCmd_V + VCCM_VqCmd_V * VCCM_VqCmd_V;

  /* Math: '<S50>/Math2'
   *
   * About '<S50>/Math2':
   *  Operator: sqrt
   */
  if (rtb_SWT < 0.0F) {
    rtb_SWT = -sqrtf(fabsf(rtb_SWT));
  } else {
    rtb_SWT = sqrtf(rtb_SWT);
  }

  /* Saturate: '<S50>/Saturation2' incorporates:
   *  Math: '<S50>/Math2'
   *
   * About '<S50>/Math2':
   *  Operator: sqrt
   */
  if (rtb_SWT > 1023.0F) {
    /* Saturate: '<S50>/Saturation2' */
    rtb_SWT = 1023.0F;
  } else if (rtb_SWT < 1.0F) {
    /* Saturate: '<S50>/Saturation2' */
    rtb_SWT = 1.0F;
  }

  /* End of Saturate: '<S50>/Saturation2' */

  /* Saturate: '<S50>/Saturation1' */
  if (VFOC_DCBusVoltage_V > 1023.0F) {
    /* Saturate: '<S50>/Saturation1' */
    VCCM_DcHiBatLim_V = 1023.0F;
  } else if (VFOC_DCBusVoltage_V < 1.0F) {
    /* Saturate: '<S50>/Saturation1' */
    VCCM_DcHiBatLim_V = 1.0F;
  } else {
    /* Saturate: '<S50>/Saturation1' */
    VCCM_DcHiBatLim_V = VFOC_DCBusVoltage_V;
  }

  /* End of Saturate: '<S50>/Saturation1' */

  /* Product: '<S50>/Product' incorporates:
   *  Constant: '<S50>/ReciSqrt3M'
   */
  rtb_BattVolCirRadius = VCCM_DcHiBatLim_V * KCCM_VolMod_perc;

  /* Logic: '<S89>/AND1' incorporates:
   *  RelationalOperator: '<S50>/Relational Operator2'
   */
  rtb_AND1_i = (rtb_SWT <= rtb_BattVolCirRadius);

  /* Outputs for Atomic SubSystem: '<S50>/DIV2' */
  SWC_ETE_type_DIV2(rtb_BattVolCirRadius, rtb_SWT, &rtb_Divide_c);

  /* End of Outputs for SubSystem: '<S50>/DIV2' */

  /* Switch: '<S50>/Switch' incorporates:
   *  Switch: '<S50>/Switch1'
   */
  if (!rtb_AND1_i) {
    /* Switch: '<S50>/Switch' incorporates:
     *  Product: '<S50>/Product1'
     */
    VCCM_VdCmd_V *= rtb_Divide_c;

    /* Switch: '<S50>/Switch1' incorporates:
     *  Product: '<S50>/Product2'
     */
    VCCM_VqCmd_V *= rtb_Divide_c;
  }

  /* End of Switch: '<S50>/Switch' */

  /* If: '<S44>/If' incorporates:
   *  Constant: '<S44>/Constant2'
   */
  if (KCCM_UdqASCEna_C) {
    /* Outputs for IfAction SubSystem: '<S44>/Subsystem1' incorporates:
     *  ActionPort: '<S52>/Action Port'
     */
    /* Chart: '<S52>/Ramp' incorporates:
     *  Constant: '<S52>/Constant1'
     *  Constant: '<S52>/Constant3'
     */
    if (!VPDC_bASCFlgRaw_flg) {
      SWC_ETE_type_ARID_DEF.intVd = VCCM_VdCmd_V;
      SWC_ETE_type_ARID_DEF.intVq = VCCM_VqCmd_V;
      SWC_ETE_type_ARID_DEF.deltaVd = (float32)((KCCM_UdqASCTagValue_C -
        VCCM_VdCmd_V) / KCCM_UdqASCTimesValue_C * 0.0001);
      SWC_ETE_type_ARID_DEF.deltaVq = (float32)((KCCM_UdqASCTagValue_C -
        VCCM_VqCmd_V) / KCCM_UdqASCTimesValue_C * 0.0001);
    } else if ((fabsf(SWC_ETE_type_ARID_DEF.intVd - KCCM_UdqASCTagValue_C) >
                fabsf(SWC_ETE_type_ARID_DEF.deltaVd)) || (fabsf
                (SWC_ETE_type_ARID_DEF.intVq - KCCM_UdqASCTagValue_C) > fabsf
                (SWC_ETE_type_ARID_DEF.deltaVq))) {
      SWC_ETE_type_ARID_DEF.intVd += SWC_ETE_type_ARID_DEF.deltaVd;
      SWC_ETE_type_ARID_DEF.intVq += SWC_ETE_type_ARID_DEF.deltaVq;
    } else {
      SWC_ETE_type_ARID_DEF.intVd = KCCM_UdqASCTagValue_C;
      SWC_ETE_type_ARID_DEF.intVq = KCCM_UdqASCTagValue_C;
      SWC_ETE_type_ARID_DEF.enASC_flg = true_MatlabRTW;
    }

    /* End of Chart: '<S52>/Ramp' */

    /* Merge: '<S44>/Merge' incorporates:
     *  SignalConversion generated from: '<S52>/Vd'
     */
    VCCM_uASCVd_V = SWC_ETE_type_ARID_DEF.intVd;

    /* Merge: '<S44>/Merge1' incorporates:
     *  SignalConversion generated from: '<S52>/Vq'
     */
    VCCM_uASCVq_V = SWC_ETE_type_ARID_DEF.intVq;

    /* Merge: '<S44>/Merge2' incorporates:
     *  SignalConversion generated from: '<S52>/enASC_flg'
     */
    VCCM_bASCEna_flg = SWC_ETE_type_ARID_DEF.enASC_flg;

    /* End of Outputs for SubSystem: '<S44>/Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S44>/If Action Subsystem' incorporates:
     *  ActionPort: '<S51>/Action Port'
     */
    /* Merge: '<S44>/Merge' incorporates:
     *  SignalConversion generated from: '<S51>/VdRef'
     */
    VCCM_uASCVd_V = VCCM_VdCmd_V;

    /* Merge: '<S44>/Merge1' incorporates:
     *  SignalConversion generated from: '<S51>/VqRef'
     */
    VCCM_uASCVq_V = VCCM_VqCmd_V;

    /* Merge: '<S44>/Merge2' incorporates:
     *  SignalConversion generated from: '<S51>/ASCFlag'
     */
    VCCM_bASCEna_flg = VPDC_bASCFlgRaw_flg;

    /* End of Outputs for SubSystem: '<S44>/If Action Subsystem' */
  }

  /* End of If: '<S44>/If' */

  /* Fcn: '<S46>/Fcn' incorporates:
   *  Fcn: '<S46>/Fcn1'
   */
  rtb_Max = sinf(VROT_RotAngleV_rad);
  rtb_Divide_c = cosf(VROT_RotAngleV_rad);

  /* Fcn: '<S46>/Fcn' */
  VCCM_uAlphaVoltTar_V = rtb_Divide_c * VCCM_uASCVd_V - rtb_Max * VCCM_uASCVq_V;

  /* Fcn: '<S46>/Fcn1' */
  VCCM_uBetaVoltTar_V = rtb_Max * VCCM_uASCVd_V + rtb_Divide_c * VCCM_uASCVq_V;

  /* MinMax: '<S47>/Max' incorporates:
   *  Abs: '<S47>/Abs'
   *  Abs: '<S47>/Abs1'
   *  Sum: '<S47>/Add'
   *  Sum: '<S47>/Add1'
   */
  rtb_Max = fmaxf(fabsf(SWC_ETE_type_ARID_DEF.CCM_IdCmd - VCCM_iDCurrAct_A),
                  fabsf(SWC_ETE_type_ARID_DEF.CCM_IqCmd - VCCM_iQCurrAct_A));

  /* Logic: '<S47>/Logical Operator1' incorporates:
   *  Constant: '<S47>/Constant6'
   *  RelationalOperator: '<S47>/Relational Operator2'
   */
  rtb_LogicalOperator_ct = (rtb_LogicalOperator_ct && (rtb_Max >
    KDSM_CurErrorThd_value));

  /* Outputs for Atomic SubSystem: '<S47>/TurnOnDelay_Dyn2' */
  /* Outputs for Atomic SubSystem: '<S58>/Rising' */
  SWC_ETE_type_Rising(rtb_LogicalOperator_ct, &rtb_AND1_i,
                      &SWC_ETE_type_ARID_DEF.ARID_DEF_Rising);

  /* End of Outputs for SubSystem: '<S58>/Rising' */

  /* Outputs for Atomic SubSystem: '<S58>/Delay' */
  SWC_ETE_type_Delay(&rtb_Divide_c, &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_cv);

  /* End of Outputs for SubSystem: '<S58>/Delay' */

  /* Switch: '<S78>/SWT' */
  if (rtb_AND1_i) {
    /* Switch: '<S78>/SWT' incorporates:
     *  Constant: '<S58>/Constant1'
     */
    SWC_ETE_type_ARID_DEF.SWT = 0.0F;
  } else {
    /* Switch: '<S78>/SWT' incorporates:
     *  Constant: '<S47>/Constant10'
     *  Sum: '<S76>/Sum1'
     */
    SWC_ETE_type_ARID_DEF.SWT = SampleTimeFOC + rtb_Divide_c;
  }

  /* End of Switch: '<S78>/SWT' */

  /* Switch: '<S77>/SWT' incorporates:
   *  Constant: '<S47>/Constant10'
   *  Constant: '<S47>/Constant2'
   *  Constant: '<S58>/Constant2'
   *  Gain: '<S72>/Gain1'
   *  Sum: '<S75>/Sub1'
   */
  if (rtb_LogicalOperator_ct) {
    rtb_Divide_c = KCCM_tiCurErrOvr_C - 0.5F * SampleTimeFOC;
  } else {
    rtb_Divide_c = 0.0F;
  }

  /* Outputs for Atomic SubSystem: '<S58>/Rising1' */
  /* Logic: '<S67>/AND1' incorporates:
   *  RelationalOperator: '<S68>/Relational Operator'
   *  Switch: '<S77>/SWT'
   */
  SWC_ETE_type_Rising((rtb_LogicalOperator_ct && (SWC_ETE_type_ARID_DEF.SWT >=
    rtb_Divide_c)), &rtb_AND1_i, &SWC_ETE_type_ARID_DEF.ARID_DEF_Rising1);

  /* End of Outputs for SubSystem: '<S58>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S58>/Falling' */
  /* Outputs for Atomic SubSystem: '<S71>/Delay' */
  SWC_ETE_type_Delay_c(rtb_LogicalOperator_ct, &rtb_UnitDelay_gs,
                       &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_p);

  /* End of Outputs for SubSystem: '<S71>/Delay' */

  /* Outputs for Atomic SubSystem: '<S58>/ER_FF' */
  /* Logic: '<S83>/AND1' incorporates:
   *  Logic: '<S85>/NOT1'
   */
  SWC_ETE_type_ER_FF(rtb_AND1_i, ((!rtb_LogicalOperator_ct) && rtb_UnitDelay_gs),
                     &SWC_ETE_type_ARID_DEF.SWT_dw,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF);

  /* End of Outputs for SubSystem: '<S58>/ER_FF' */
  /* End of Outputs for SubSystem: '<S58>/Falling' */

  /* Update for Atomic SubSystem: '<S58>/Delay' */
  SWC_ETE_type_Delay_Update(SWC_ETE_type_ARID_DEF.SWT,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_cv);

  /* End of Update for SubSystem: '<S58>/Delay' */
  /* End of Outputs for SubSystem: '<S47>/TurnOnDelay_Dyn2' */

  /* Outputs for Atomic SubSystem: '<S47>/ER_FF' */
  /* Constant: '<S47>/Constant7' */
  SWC_ETE_type_ER_FF(SWC_ETE_type_ARID_DEF.SWT_dw, KCCM_bRstCurErrorOverThd_C,
                     &VCCM_CurErrorOverThd_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF_g);

  /* End of Outputs for SubSystem: '<S47>/ER_FF' */

  /* Outputs for Atomic SubSystem: '<S47>/ER_FF1' */
  /* RelationalOperator: '<S47>/Relational Operator1' incorporates:
   *  Constant: '<S47>/Constant1'
   *  Constant: '<S47>/Constant7'
   */
  SWC_ETE_type_ER_FF((rtb_Max > KDSM_CurErrorThd2_value),
                     KCCM_bRstCurErrorOverThd_C, &VCCM_CurErrorOverThd2_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF1_f);

  /* End of Outputs for SubSystem: '<S47>/ER_FF1' */

  /* UnitDelay: '<S98>/Unit Delay' incorporates:
   *  Sum: '<S48>/Add2'
   */
  rtb_CCM_facLPFiQAct_T1 -= rtb_LqMapp;

  /* Product: '<S48>/Product10' incorporates:
   *  Constant: '<S48>/Constant4'
   *  Constant: '<S48>/Constant5'
   *  Gain: '<S48>/Gain4'
   *  Product: '<S48>/Product8'
   *  Product: '<S48>/Product9'
   *  Sum: '<S48>/Add3'
   */
  VMCM_TqAct_Nm = (rtb_CCM_facLPFiQAct_T1 * SWC_ETE_type_ARID_DEF.CCM_IdCmd +
                   KFOC_MagFluxLinkage_C) * (1.5F * KFOC_PolePairs_p *
    SWC_ETE_type_ARID_DEF.CCM_IqCmd);

  /* Product: '<S48>/Product7' incorporates:
   *  Constant: '<S48>/Constant1'
   *  Constant: '<S48>/Constant3'
   *  Gain: '<S48>/Gain1'
   *  Product: '<S48>/Product3'
   *  Product: '<S48>/Product6'
   *  Sum: '<S48>/Add1'
   */
  VMCM_TqEst_Nm = (rtb_CCM_facLPFiQAct_T1 * VCCM_iDCurrAct_A +
                   KFOC_MagFluxLinkage_C) * (1.5F * KFOC_PolePairs_p *
    VCCM_iQCurrAct_A);

  /* Sum: '<S97>/Add' incorporates:
   *  Constant: '<S97>/Constant'
   *  Product: '<S97>/Product'
   *  Sum: '<S97>/Subtract'
   *  UnitDelay: '<S97>/Unit Delay'
   */
  VCCM_VcmdBfLim_V += (rtb_SWT - VCCM_VcmdBfLim_V) * KCCM_BattVolFilTi_fac;

  /* Sum: '<S98>/Add' incorporates:
   *  Constant: '<S98>/Constant'
   *  Product: '<S98>/Product'
   *  Sum: '<S98>/Subtract'
   *  UnitDelay: '<S98>/Unit Delay'
   */
  VCCM_BattVolCirRadius_V += (rtb_BattVolCirRadius - VCCM_BattVolCirRadius_V) *
    KCCM_BattVolFilTi_fac;

  /* Product: '<S50>/Product6' */
  VCCM_VoltUtilize_pu = VCCM_VcmdBfLim_V / VCCM_BattVolCirRadius_V;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
