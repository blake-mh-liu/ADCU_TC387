/*
 * File: ADC_RDC_Read.c
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
#include "ADC_RDC_Read.h"
#include <math.h>
#include "rt_sys_ADC_RDC_Read_0.h"
#include "rt_sys_ADC_RDC_Read_19.h"
#include "FVTMC_API.h"
#include "look1_iflf_binlcapw.h"

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/* Output and update for atomic system: '<S20>/First_Order_Filter' */
void First_Order_Filter(float32 rtu_InputSignal, float32 rtu_cutoff_freq,
  float32 rtu_sample_freq, float32 *rty_OutputSignal,
  ARID_DEF_First_Order_Filter_T *SWC_ETE_type__ARID_DEF_arg)
{
  float32 rtb_alpha;

  /* Product: '<S30>/Divide' incorporates:
   *  Gain: '<S30>/Gain'
   *  Sum: '<S30>/Add1'
   */
  rtb_alpha = 6.28318548F * rtu_cutoff_freq;
  rtb_alpha /= rtb_alpha + rtu_sample_freq;

  /* Sum: '<S30>/Add2' incorporates:
   *  Constant: '<S30>/Constant'
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   *  Sum: '<S30>/Add'
   *  UnitDelay: '<S30>/Unit Delay'
   */
  *rty_OutputSignal = (1.0F - rtb_alpha) *
    SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE + rtu_InputSignal * rtb_alpha;

  /* Update for UnitDelay: '<S30>/Unit Delay' */
  SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE = *rty_OutputSignal;
}

/* System initialize for atomic system: '<S3>/ADC_RDC_Read' */
void SWC_ETE_type_ADC_RDC_Read_Init(void)
{
  /* SystemInitialize for Atomic SubSystem: '<S4>/ROT1' */
  /* InitializeConditions for DataTypeConversion: '<S32>/Data Type Conversion' incorporates:
   *  UnitDelay: '<S20>/Unit Delay'
   */
  SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_j = 5000.0F;

  /* End of SystemInitialize for SubSystem: '<S4>/ROT1' */
}

/* Output and update for atomic system: '<S3>/ADC_RDC_Read' */
void SWC_ETE_type_ADC_RDC_Read(void)
{
  EvAdc_SignalDataType_Fake rtb_CCaller_o2[3];
  EvAdc_SignalDataType_Fake expl_temp;
  float32 rtb_Abs;
  float32 rtb_Abs1;
  float32 rtb_Abs2;
  float32 tmp;
  float32 tmp_0;
  float32 tmp_1;
  uint16 rtb_Add_g;
  boolean rtb_Ena_flg;

  /* CCaller: '<S4>/C Caller' incorporates:
   *  SignalConversion generated from: '<S4>/C Caller'
   */
  rtb_CCaller_o2[0] = SWC_ETE_type_ConstB.TmpSignalConversionAtCCalle[0];
  rtb_CCaller_o2[1] = SWC_ETE_type_ConstB.TmpSignalConversionAtCCalle[1];
  rtb_CCaller_o2[2] = SWC_ETE_type_ConstB.TmpSignalConversionAtCCalle[2];

  /* CCaller: '<S4>/C Caller' */
  read_phase_current_sync_result(&rtb_CCaller_o2[0]);

  /* DataTypeConversion: '<S4>/Data Type Conversion1' */
  VFOC_iARaw_raw = rtb_CCaller_o2[0].f32_Phy;

  /* DataTypeConversion: '<S4>/Data Type Conversion2' */
  VFOC_iBRaw_raw = rtb_CCaller_o2[1].f32_Phy;

  /* DataTypeConversion: '<S4>/Data Type Conversion3' */
  VFOC_iCRaw_raw = rtb_CCaller_o2[2].f32_Phy;

  /* Sum: '<S27>/Add' incorporates:
   *  UnitDelay: '<S27>/Unit Delay'
   *  UnitDelay: '<S27>/Unit Delay1'
   */
  rtb_Add_g = (uint16)((uint32)SWC_ETE_type_ARID_DEF.UnitDelay1_DSTATE_k +
                       SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mq);

  /* RelationalOperator: '<S27>/Relational Operator' incorporates:
   *  Constant: '<S27>/Constant1'
   */
  rtb_Ena_flg = (rtb_Add_g <= KPCS_OffsFilTi_cnt);

  /* Switch: '<S27>/Switch1' incorporates:
   *  Constant: '<S27>/Constant3'
   */
  if (KPCS_EnaSnsrSelfLrn_flg_ovrdflg) {
    /* Switch: '<S27>/Switch1' incorporates:
     *  Constant: '<S27>/Constant'
     */
    VPCS_EnaSnsrSelfLrn_flg = KPCS_EnaSnsrSelfLrn_flg_ovrdval;
  } else {
    /* Switch: '<S27>/Switch1' */
    VPCS_EnaSnsrSelfLrn_flg = rtb_Ena_flg;
  }

  /* End of Switch: '<S27>/Switch1' */

  /* Outputs for Enabled SubSystem: '<S19>/CalcSelfLrnOffsVal' incorporates:
   *  EnablePort: '<S25>/Enable'
   */
  if (VPCS_EnaSnsrSelfLrn_flg) {
    /* Sum: '<S25>/Subtract' incorporates:
     *  UnitDelay: '<S25>/Unit Delay'
     */
    rtb_Abs1 = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[0];

    /* Sum: '<S25>/Add' incorporates:
     *  UnitDelay: '<S25>/Unit Delay'
     */
    rtb_Abs = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[0];

    /* Sum: '<S25>/Subtract' incorporates:
     *  UnitDelay: '<S25>/Unit Delay'
     */
    rtb_Abs2 = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[1];

    /* Sum: '<S25>/Add' incorporates:
     *  Sum: '<S25>/Subtract'
     *  UnitDelay: '<S25>/Unit Delay'
     */
    tmp = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[1];

    /* Sum: '<S25>/Subtract' incorporates:
     *  UnitDelay: '<S25>/Unit Delay'
     */
    tmp_0 = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[2];

    /* Sum: '<S25>/Add' incorporates:
     *  Sum: '<S25>/Subtract'
     *  UnitDelay: '<S25>/Unit Delay'
     */
    tmp_1 = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[2];

    /* Sum: '<S25>/Add' incorporates:
     *  Constant: '<S25>/Constant'
     *  Product: '<S25>/Product'
     *  Sum: '<S25>/Subtract'
     *  UnitDelay: '<S25>/Unit Delay'
     */
    SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[0] = (VFOC_iCRaw_raw - rtb_Abs1) *
      KPCS_OffsFilCoeff_fac + rtb_Abs;
    SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[1] = (VFOC_iBRaw_raw - rtb_Abs2) *
      KPCS_OffsFilCoeff_fac + tmp;
    SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[2] = (VFOC_iARaw_raw - tmp_0) *
      KPCS_OffsFilCoeff_fac + tmp_1;

    /* DataTypeConversion: '<S25>/Data Type Conversion' */
    VPCS_WCurOffsRaw_V = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[0];

    /* DataTypeConversion: '<S25>/Data Type Conversion1' */
    VPCS_VCurOffsRaw_V = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[1];

    /* DataTypeConversion: '<S25>/Data Type Conversion3' */
    VPCS_UCurOffsRaw_V = SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mh[2];
  }

  /* End of Outputs for SubSystem: '<S19>/CalcSelfLrnOffsVal' */

  /* Logic: '<S19>/Logical Operator' */
  VPCS_SnsrSelfLrnCompl_flg = !VPCS_EnaSnsrSelfLrn_flg;

  /* Outputs for Enabled SubSystem: '<S19>/SnsrOffsDiag' incorporates:
   *  EnablePort: '<S28>/Enable'
   */
  if (VPCS_SnsrSelfLrnCompl_flg) {
    /* Logic: '<S28>/Logical Operator' incorporates:
     *  Constant: '<S28>/Constant'
     *  Constant: '<S28>/Constant1'
     *  RelationalOperator: '<S28>/Relational Operator'
     *  RelationalOperator: '<S28>/Relational Operator1'
     */
    VPCS_WCurOffsVolVld_flg = ((VPCS_WCurOffsRaw_V <=
      KPCS_PhaseCurSnsrVolVldMax_V) && (VPCS_WCurOffsRaw_V >=
      KPCS_PhaseCurSnsrVolVldMin_V));
    VPCS_VCurOffsVolVld_flg = ((VPCS_VCurOffsRaw_V <=
      KPCS_PhaseCurSnsrVolVldMax_V) && (VPCS_VCurOffsRaw_V >=
      KPCS_PhaseCurSnsrVolVldMin_V));
    VPCS_UCurOffsVolVld_flg = ((VPCS_UCurOffsRaw_V <=
      KPCS_PhaseCurSnsrVolVldMax_V) && (VPCS_UCurOffsRaw_V >=
      KPCS_PhaseCurSnsrVolVldMin_V));

    /* Switch: '<S28>/PCS_bCurOffsVolVld_flgswt' incorporates:
     *  Constant: '<S28>/PCS_bCurOffsVolVld_flgTrig_C'
     */
    if (KPCS_bCurOffsVolVld_flg_ovrdflg) {
      /* Switch: '<S28>/PCS_bCurOffsVolVld_flgswt' incorporates:
       *  Constant: '<S28>/PCS_bCurOffsVolVld_flgMor_C'
       */
      VPCS_bCurOffsVolVld_flg = KPCS_bCurOffsVolVld_flg_ovrdval;
    } else {
      /* Switch: '<S28>/PCS_bCurOffsVolVld_flgswt' incorporates:
       *  Logic: '<S28>/Logical Operator1'
       */
      VPCS_bCurOffsVolVld_flg = (VPCS_WCurOffsVolVld_flg &&
        VPCS_VCurOffsVolVld_flg && VPCS_UCurOffsVolVld_flg);
    }

    /* End of Switch: '<S28>/PCS_bCurOffsVolVld_flgswt' */

    /* Switch: '<S28>/Switch' */
    if (VPCS_WCurOffsVolVld_flg) {
      /* Switch: '<S28>/Switch' */
      VPCS_WCurOffsFil_V = VPCS_WCurOffsRaw_V;
    } else {
      /* Switch: '<S28>/Switch' incorporates:
       *  Constant: '<S28>/Constant4'
       */
      VPCS_WCurOffsFil_V = KPCS_PhaseCurSnsrVolDft_V;
    }

    /* End of Switch: '<S28>/Switch' */

    /* Switch: '<S28>/Switch1' */
    if (VPCS_VCurOffsVolVld_flg) {
      /* Switch: '<S28>/Switch1' */
      VPCS_VCurOffsFil_V = VPCS_VCurOffsRaw_V;
    } else {
      /* Switch: '<S28>/Switch1' incorporates:
       *  Constant: '<S28>/Constant4'
       */
      VPCS_VCurOffsFil_V = KPCS_PhaseCurSnsrVolDft_V;
    }

    /* End of Switch: '<S28>/Switch1' */

    /* Switch: '<S28>/Switch2' */
    if (VPCS_UCurOffsVolVld_flg) {
      /* Switch: '<S28>/Switch2' */
      VPCS_UCurOffsFil_V = VPCS_UCurOffsRaw_V;
    } else {
      /* Switch: '<S28>/Switch2' incorporates:
       *  Constant: '<S28>/Constant4'
       */
      VPCS_UCurOffsFil_V = KPCS_PhaseCurSnsrVolDft_V;
    }

    /* End of Switch: '<S28>/Switch2' */
  }

  /* End of Outputs for SubSystem: '<S19>/SnsrOffsDiag' */

  /* Product: '<S19>/Product' incorporates:
   *  Constant: '<S19>/Constant'
   *  Sum: '<S19>/Subtract'
   */
  VPCS_PhaWCur_A = (VFOC_iCRaw_raw - VPCS_WCurOffsFil_V) * KPCS_WCurSnsr_Gain;

  /* Product: '<S19>/Product1' incorporates:
   *  Constant: '<S19>/Constant1'
   *  Sum: '<S19>/Subtract1'
   */
  VPCS_PhaVCur_A = (VFOC_iBRaw_raw - VPCS_VCurOffsFil_V) * KPCS_VCurSnsr_Gain;

  /* Product: '<S19>/Product3' incorporates:
   *  Constant: '<S19>/Constant3'
   *  Sum: '<S19>/Subtract3'
   */
  VPCS_PhaUCur_A = (VFOC_iARaw_raw - VPCS_UCurOffsFil_V) * KPCS_UCurSnsr_Gain;

  /* Abs: '<S26>/Abs' */
  rtb_Abs = fabsf(VFOC_iCRaw_raw);

  /* Abs: '<S26>/Abs2' */
  rtb_Abs2 = fabsf(VFOC_iARaw_raw);

  /* Switch: '<S26>/Switch7' incorporates:
   *  Constant: '<S26>/Constant'
   *  RelationalOperator: '<S26>/Relational Operator3'
   *  Switch: '<S26>/Switch6'
   *  UnitDelay: '<S26>/Unit Delay3'
   */
  if (KPCS_MaxCurrReset_flg) {
    /* Switch: '<S26>/Switch7' incorporates:
     *  Constant: '<S26>/Constant4'
     */
    VPCS_MaxPhaCurW_A = 0.0F;
  } else if (rtb_Abs > VPCS_MaxPhaCurW_A) {
    /* Switch: '<S26>/Switch6' incorporates:
     *  Switch: '<S26>/Switch7'
     */
    VPCS_MaxPhaCurW_A = rtb_Abs;
  }

  /* End of Switch: '<S26>/Switch7' */

  /* Abs: '<S26>/Abs1' */
  rtb_Abs1 = fabsf(VFOC_iBRaw_raw);

  /* Switch: '<S26>/Switch3' incorporates:
   *  Constant: '<S26>/Constant'
   *  RelationalOperator: '<S26>/Relational Operator1'
   *  Switch: '<S26>/Switch1'
   *  Switch: '<S26>/Switch2'
   *  Switch: '<S26>/Switch5'
   *  UnitDelay: '<S26>/Unit Delay1'
   */
  if (KPCS_MaxCurrReset_flg) {
    /* Switch: '<S26>/Switch3' incorporates:
     *  Constant: '<S26>/Constant2'
     */
    VPCS_MaxPhaCurU_A = 0.0F;

    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant1'
     */
    VPCS_MaxPhaCur_A = 0.0F;

    /* Switch: '<S26>/Switch5' incorporates:
     *  Constant: '<S26>/Constant3'
     */
    VPCS_MaxPhaCurV_A = 0.0F;
  } else {
    if (rtb_Abs2 > VPCS_MaxPhaCurU_A) {
      /* Switch: '<S26>/Switch2' incorporates:
       *  Switch: '<S26>/Switch3'
       */
      VPCS_MaxPhaCurU_A = rtb_Abs2;
    }

    /* MinMax: '<S26>/MinMax1' */
    rtb_Abs = fmaxf(fmaxf(rtb_Abs2, rtb_Abs1), rtb_Abs);

    /* Switch: '<S26>/Switch' incorporates:
     *  RelationalOperator: '<S26>/Relational Operator'
     *  UnitDelay: '<S26>/Unit Delay'
     */
    if (rtb_Abs > VPCS_MaxPhaCur_A) {
      /* Switch: '<S26>/Switch1' */
      VPCS_MaxPhaCur_A = rtb_Abs;
    }

    /* End of Switch: '<S26>/Switch' */

    /* Switch: '<S26>/Switch4' incorporates:
     *  RelationalOperator: '<S26>/Relational Operator2'
     *  UnitDelay: '<S26>/Unit Delay2'
     */
    if (rtb_Abs1 > VPCS_MaxPhaCurV_A) {
      /* Switch: '<S26>/Switch5' */
      VPCS_MaxPhaCurV_A = rtb_Abs1;
    }

    /* End of Switch: '<S26>/Switch4' */
  }

  /* End of Switch: '<S26>/Switch3' */

  /* CCaller: '<S4>/C Caller15' incorporates:
   *  Constant: '<S4>/Constant14'
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  DataTypeConversion: '<S4>/Data Type Conversion4'
   */
  expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
    KFOC_ADCReadEnum_enum);

  /* DataTypeConversion: '<S4>/Data Type Conversion5' incorporates:
   *  CCaller: '<S4>/C Caller15'
   */
  VFOC_DCBusRAW_V = expl_temp.f32_Phy;

  /* Outputs for Atomic SubSystem: '<S18>/Delay' */
  SWC_ETE_type_Delay(&rtb_Abs1, &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_g);

  /* End of Outputs for SubSystem: '<S18>/Delay' */

  /* Sum: '<S24>/Sum1' incorporates:
   *  Constant: '<S4>/Constant13'
   *  Product: '<S22>/Mul1'
   *  Sum: '<S23>/Sub1'
   */
  SWC_ETE_type_ARID_DEF.Sum1 = (VFOC_DCBusRAW_V - rtb_Abs1) * KFOC_DCBusLPF_c +
    rtb_Abs1;

  /* Switch: '<S4>/Switch3' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant2'
   *  Switch: '<S4>/Switch1'
   */
  if (KFOC_DCBusVoltage_V_ovrdflg) {
    /* Switch: '<S4>/Switch3' incorporates:
     *  Constant: '<S4>/Constant1'
     */
    VFOC_DCBusVoltage_V = KFOC_DCBusVoltage_V_ovrdval;
  } else if (KFOC_DCBusUseRaw_flg) {
    /* Switch: '<S4>/Switch1' incorporates:
     *  Switch: '<S4>/Switch3'
     */
    VFOC_DCBusVoltage_V = VFOC_DCBusRAW_V;
  } else {
    /* Switch: '<S4>/Switch3' incorporates:
     *  Switch: '<S4>/Switch1'
     */
    VFOC_DCBusVoltage_V = SWC_ETE_type_ARID_DEF.Sum1;
  }

  /* End of Switch: '<S4>/Switch3' */

  /* CCaller: '<S4>/C Caller1' */

  /* DataTypeConversion: '<S20>/Data Type Conversion2' incorporates:
   *  CCaller: '<S4>/C Caller2'
   */

  /* Outputs for Atomic SubSystem: '<S4>/ROT1' */
  /* Switch: '<S20>/RotS_nRotswt' incorporates:
   *  Constant: '<S20>/Constant4'
   *  Constant: '<S20>/RotS_nRotTrig_C'
   */
  if (KROT_RotSpdMRaw_rpm_ovrdflg) {
    /* Switch: '<S20>/RotS_nRotswt' incorporates:
     *  Constant: '<S20>/RotS_nRotMor_C'
     */
    rtb_Abs1 = KROT_RotSpdMRaw_rpm_ovrdval;
  } else {
    /* Outputs for Atomic SubSystem: '<S20>/DIV2' */
    SWC_ETE_type_DIV2(VROT_RotSpdERaw_rads, KFOC_PolePairs_p, &rtb_Abs1);

    /* End of Outputs for SubSystem: '<S20>/DIV2' */

    /* Switch: '<S20>/RotS_nRotswt' incorporates:
     *  Constant: '<S20>/Constant4'
     *  Gain: '<S20>/rad//s2rpm'
     */
    rtb_Abs1 *= 9.54929638F;
  }

  /* End of Switch: '<S20>/RotS_nRotswt' */

  /* Outputs for Atomic SubSystem: '<S20>/First_Order_Filter' */
  /* SignalConversion generated from: '<S20>/First_Order_Filter' incorporates:
   *  Constant: '<S20>/RotS_nRotMor_C1'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  First_Order_Filter(rtb_Abs1, KROT_SpdCutoffFreq_Hz,
                     SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_j, &VROT_RotSpdM_rpm,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_First_Order_Filter);

  /* End of Outputs for SubSystem: '<S20>/First_Order_Filter' */

  /* Switch: '<S20>/Switch' incorporates:
   *  Constant: '<S20>/RotS_agRotRawMor_C2'
   *  Constant: '<S20>/RotS_agRotRawMor_C3'
   *  Constant: '<S32>/RotS_nRotMor_C1'
   *  Lookup_n-D: '<S20>/1-D Lookup Table'
   *  RelationalOperator: '<S20>/GreaterThan'
   *  SignalConversion generated from: '<S20>/First_Order_Filter'
   */
  if (VROT_RotSpdM_rpm < 1000.0F) {
    rtb_Abs2 = 0.0F;
  } else {
    rtb_Abs2 = look1_iflf_binlcapw(VROT_RotSpdM_rpm, &AROT_ParkCompAngle_X_rpm[0],
      &MROT_ParkCompAngle_Y_rad[0], 19U);
  }

  /* End of Switch: '<S20>/Switch' */

  /* Sum: '<S20>/Add1' */
  VROT_RotAgECompL_rad = rtb_Abs2 + VFOC_RotorPosnOffset_rad;

  /* DataTypeConversion: '<S20>/Data Type Conversion1' */
  VROT_RotAngleERaw_rad = rtb_Abs;

  /* Switch: '<S20>/RotS_agRotRawswt' incorporates:
   *  Constant: '<S20>/Constant2'
   *  Constant: '<S20>/RotS_agRotRawTrig_C'
   *  Constant: '<S3>/Constant13'
   *  RelationalOperator: '<S20>/Equal'
   *  Switch: '<S20>/Switch1'
   */
  if (KROT_RotAngleE_rad_ovrdflg) {
    /* Switch: '<S20>/RotS_agRotRawswt' incorporates:
     *  Constant: '<S20>/RotS_agRotRawMor_C'
     */
    VROT_RotAngleE_rad = KROT_RotAngleE_rad_ovrdval;
  } else if (KFOC_SensorMode_enum == 3) {
    /* Switch: '<S20>/Switch1' incorporates:
     *  Constant: '<S20>/RotS_agRotRawMor_C4'
     *  Switch: '<S20>/RotS_agRotRawswt'
     */
    VROT_RotAngleE_rad = 0.0F;
  } else {
    /* Switch: '<S20>/RotS_agRotRawswt' incorporates:
     *  Sum: '<S20>/Add'
     *  Switch: '<S20>/Switch1'
     */
    VROT_RotAngleE_rad = VROT_RotAgECompL_rad + VROT_RotAngleERaw_rad;
  }

  /* End of Switch: '<S20>/RotS_agRotRawswt' */

  /* Switch: '<S34>/Switch1' incorporates:
   *  Bias: '<S34>/Bias1'
   */
  if (VROT_RotAngleE_rad + 6.28318548F > 6.28318548F) {
    /* Switch: '<S34>/Switch' */
    if (VROT_RotAngleE_rad > 6.28318548F) {
      /* Switch: '<S34>/Switch1' incorporates:
       *  Bias: '<S34>/Bias'
       *  Switch: '<S34>/Switch'
       */
      VROT_RotAngleE_rad -= 6.28318548F;
    }

    /* End of Switch: '<S34>/Switch' */
  } else {
    /* Switch: '<S34>/Switch1' */
    VROT_RotAngleE_rad += 6.28318548F;
  }

  /* End of Switch: '<S34>/Switch1' */

  /* SignalConversion: '<S20>/Signal Conversion' */
  VROT_RotSpdE_rads = VROT_RotSpdERaw_rads;

  /* Product: '<S20>/Product1' incorporates:
   *  Constant: '<S20>/TM_Prd'
   *  Lookup_n-D: '<S20>/1-D Lookup Table2'
   *  Product: '<S20>/Product2'
   *  SignalConversion generated from: '<S20>/First_Order_Filter'
   */
  VROT_RotAgECompV_rad = KROT_CurLoopPrd_t * VROT_RotSpdE_rads *
    look1_iflf_binlcapw(VROT_RotSpdM_rpm, &AROT_ParkCompAngle_X_rpm[0],
                        &MROT_VolPosnOffsWiSpd_Y_deg[0], 19U);

  /* Sum: '<S20>/Add3' */
  VROT_RotAngleV_rad = VROT_RotAgECompV_rad + VROT_RotAngleE_rad;

  /* Switch: '<S33>/Switch1' incorporates:
   *  Bias: '<S33>/Bias1'
   */
  if (VROT_RotAngleV_rad + 6.28318548F > 6.28318548F) {
    /* Switch: '<S33>/Switch' */
    if (VROT_RotAngleV_rad > 6.28318548F) {
      /* Switch: '<S33>/Switch1' incorporates:
       *  Bias: '<S33>/Bias'
       *  Switch: '<S33>/Switch'
       */
      VROT_RotAngleV_rad -= 6.28318548F;
    }

    /* End of Switch: '<S33>/Switch' */
  } else {
    /* Switch: '<S33>/Switch1' */
    VROT_RotAngleV_rad += 6.28318548F;
  }

  /* End of Switch: '<S33>/Switch1' */

  /* Switch: '<S32>/Switch3' incorporates:
   *  Constant: '<S32>/RotS_nRotMor_C1'
   */
  if (KROT_bUseVariableFc_flg) {
    /* Abs: '<S32>/Abs' incorporates:
     *  UnitDelay: '<S32>/Unit Delay'
     */
    rtb_Abs = fabsf(SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_p0);

    /* Switch: '<S32>/Switch' incorporates:
     *  Switch: '<S32>/Switch1'
     */
    if (rtb_Abs >= 5000.0F) {
      /* Switch: '<S32>/Switch3' incorporates:
       *  Constant: '<S32>/Constant1'
       *  Switch: '<S32>/Switch'
       */
      rtb_Abs = 10000.0F;
    } else if (rtb_Abs >= 3000.0F) {
      /* Switch: '<S32>/Switch1' incorporates:
       *  Fcn: '<S32>/Fcn'
       *  Switch: '<S32>/Switch3'
       */
      rtb_Abs = (rtb_Abs - 3000.0F) * 2.5F + 5000.0F;
    } else {
      /* Switch: '<S32>/Switch3' incorporates:
       *  Constant: '<S32>/Constant3'
       *  Switch: '<S32>/Switch1'
       */
      rtb_Abs = 5000.0F;
    }

    /* End of Switch: '<S32>/Switch' */
  } else {
    /* Switch: '<S32>/Switch3' incorporates:
     *  Constant: '<S32>/Constant2'
     */
    rtb_Abs = 10000.0F;
  }

  /* End of Switch: '<S32>/Switch3' */

  /* DataTypeConversion: '<S32>/Data Type Conversion' */
  SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_j = fmodf(floorf(rtb_Abs), 65536.0F);

  /* DataTypeConversion: '<S31>/Data Type Conversion' incorporates:
   *  Constant: '<S31>/Constant'
   *  DataTypeConversion: '<S32>/Data Type Conversion'
   *  Sum: '<S31>/Subtract'
   */
  VROT_FreqPWM_Tick = (uint32)(15000 - (sint32)
    SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_j);

  /* Update for UnitDelay: '<S32>/Unit Delay' */
  SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_p0 = rtb_Abs1;

  /* End of Outputs for SubSystem: '<S4>/ROT1' */

  /* Update for UnitDelay: '<S27>/Unit Delay1' */
  SWC_ETE_type_ARID_DEF.UnitDelay1_DSTATE_k = rtb_Ena_flg;

  /* Update for UnitDelay: '<S27>/Unit Delay' */
  SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_mq = rtb_Add_g;

  /* Update for Atomic SubSystem: '<S18>/Delay' */
  SWC_ETE_type_Delay_Update(SWC_ETE_type_ARID_DEF.Sum1,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_g);

  /* End of Update for SubSystem: '<S18>/Delay' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
