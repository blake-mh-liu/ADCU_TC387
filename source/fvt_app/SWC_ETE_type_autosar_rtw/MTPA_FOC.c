/*
 * File: MTPA_FOC.c
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
#include "MTPA_FOC.h"
#include "rt_sys_CCM_FVT_38.h"
#include "ADC_RDC_Read.h"
#include "PDC.h"
#include "CCM_FVT.h"
#include "Fake_RDC_Handler.h"
#include "FOC_Mode_Judge.h"
#include "rt_sys_rt_sys_CCM_FVT_38_36.h"
#include <math.h>
#include "Rte_Type.h"

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/*
 * System initialize for atomic system:
 *    '<S115>/debounce'
 *    '<S113>/debounce'
 */
void SWC_ETE_type_debounce_Init(boolean *rty_Status)
{
  /* SystemInitialize for Chart: '<S121>/Chart' */
  *rty_Status = false_MatlabRTW;
}

/*
 * Output and update for atomic system:
 *    '<S115>/debounce'
 *    '<S113>/debounce'
 */
void SWC_ETE_type_debounce(boolean rtu_error_state, sint16 rtu_heal_max, sint16
  rtu_error_max, boolean *rty_Status, ARID_DEF_debounce_SWC_ETE_typ_T
  *SWC_ETE_type__ARID_DEF_arg)
{
  /* Chart: '<S121>/Chart' incorporates:
   *  UnitDelay: '<S121>/Unit Delay'
   *  UnitDelay: '<S121>/Unit Delay1'
   */
  if (rtu_error_state) {
    if (SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE <= 0) {
      SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE = 2;
    } else if (SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE >= rtu_error_max) {
      SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE = rtu_error_max;
    } else {
      sint32 tmp;
      tmp = SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE + 2;
      if (SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE + 2 > 32767) {
        tmp = 32767;
      }

      SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE = (sint16)tmp;
    }
  } else if (SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE <= rtu_heal_max) {
    SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE = rtu_heal_max;
  } else {
    SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE--;
  }

  *rty_Status = ((SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE > rtu_heal_max) &&
                 (SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE || (rtu_heal_max >=
    SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE) ||
                  (SWC_ETE_type__ARID_DEF_arg->UnitDelay1_DSTATE >=
                   rtu_error_max)));

  /* End of Chart: '<S121>/Chart' */

  /* Update for UnitDelay: '<S121>/Unit Delay' */
  SWC_ETE_type__ARID_DEF_arg->UnitDelay_DSTATE = *rty_Status;
}

/* System initialize for atomic system: '<S6>/CurrentSensor' */
void CurrentSensor_Init(void)
{
  /* local block i/o variables */
  boolean rtb_Status;

  /* SystemInitialize for IfAction SubSystem: '<S114>/Sum_Err' */
  /* SystemInitialize for Atomic SubSystem: '<S115>/debounce' */
  SWC_ETE_type_debounce_Init(&rtb_Status);

  /* End of SystemInitialize for SubSystem: '<S115>/debounce' */
  /* End of SystemInitialize for SubSystem: '<S114>/Sum_Err' */
}

/* Output and update for atomic system: '<S6>/CurrentSensor' */
void CurrentSensor(void)
{
  /* local block i/o variables */
  boolean rtb_Status;
  float32 rtb_Subtract2_i;

  /* If: '<S114>/If' incorporates:
   *  Constant: '<S115>/Constant'
   *  Constant: '<S115>/Constant1'
   *  Constant: '<S115>/Constant2'
   *  Constant: '<S115>/Constant8'
   *  RelationalOperator: '<S115>/Relational Operator2'
   *  Switch: '<S115>/Switch'
   */
  if (VPCS_SnsrSelfLrnCompl_flg) {
    /* Outputs for IfAction SubSystem: '<S114>/Sum_Err' incorporates:
     *  ActionPort: '<S115>/Action Port'
     */
    /* Sum: '<S115>/Subtract2' incorporates:
     *  Sum: '<S115>/Add'
     */
    rtb_Subtract2_i = (VPCS_PhaUCur_A + VPCS_PhaVCur_A) + VPCS_PhaWCur_A;

    /* Switch: '<S115>/Switch' incorporates:
     *  Constant: '<S116>/Constant'
     *  Gain: '<S115>/Gain'
     *  RelationalOperator: '<S116>/Compare'
     */
    if (rtb_Subtract2_i < 0.0F) {
      rtb_Subtract2_i = -rtb_Subtract2_i;
    }

    /* Outputs for Atomic SubSystem: '<S115>/debounce' */
    SWC_ETE_type_debounce((rtb_Subtract2_i >= KDGH_SumErr_A), KDGH_SumErrHeal_C,
                          KDGH_SumErrErr_C, &rtb_Status,
                          &SWC_ETE_type_ARID_DEF.ARID_DEF_debounce_c);

    /* End of Outputs for SubSystem: '<S115>/debounce' */

    /* Outputs for Atomic SubSystem: '<S115>/ER_FF1' */
    SWC_ETE_type_ER_FF(rtb_Status, KDGH_RstSumErr_flg,
                       &SWC_ETE_type_ARID_DEF.SWT_d,
                       &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF1_b);

    /* End of Outputs for SubSystem: '<S115>/ER_FF1' */

    /* Switch: '<S115>/SumErr_Outswt' incorporates:
     *  Constant: '<S115>/Constant'
     *  Constant: '<S115>/Constant1'
     *  Constant: '<S115>/Constant2'
     *  Constant: '<S115>/Constant8'
     *  Constant: '<S115>/SumErr_OutTrig_C'
     *  RelationalOperator: '<S115>/Relational Operator2'
     *  Switch: '<S115>/Switch'
     */
    if (KDGH_SumErr_flg_ovrdflg) {
      /* Switch: '<S115>/SumErr_Outswt' incorporates:
       *  Constant: '<S115>/SumErr_OutMor_C'
       */
      VDGH_SumErr_flg = KDGH_SumErr_flg_ovrdval;
    } else {
      /* Switch: '<S115>/SumErr_Outswt' */
      VDGH_SumErr_flg = SWC_ETE_type_ARID_DEF.SWT_d;
    }

    /* End of Switch: '<S115>/SumErr_Outswt' */

    /* Switch: '<S115>/Switch2' incorporates:
     *  Constant: '<S115>/Constant8'
     *  RelationalOperator: '<S117>/FixPt Relational Operator'
     *  Switch: '<S115>/Switch1'
     *  Switch: '<S115>/Switch4'
     *  Switch: '<S115>/Switch6'
     *  UnitDelay: '<S117>/Delay Input1'
     *
     * Block description for '<S117>/Delay Input1':
     *
     *  Store in Global RAM
     */
    if (KDGH_RstSumErr_flg) {
      /* Switch: '<S115>/Switch2' incorporates:
       *  Constant: '<S115>/Constant4'
       */
      VDGH_SumErrPhCurU_A = 0.0F;

      /* Switch: '<S115>/Switch4' incorporates:
       *  Constant: '<S115>/Constant5'
       */
      VDGH_SumErrPhCurW_A = 0.0F;

      /* Switch: '<S115>/Switch6' incorporates:
       *  Constant: '<S115>/Constant6'
       */
      VDGH_SumErrPhCurV_A = 0.0F;
    } else {
      if ((sint32)VDGH_SumErr_flg > (sint32)
          SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_f) {
        /* Switch: '<S115>/Switch1' incorporates:
         *  Switch: '<S115>/Switch2'
         */
        VDGH_SumErrPhCurU_A = VPCS_PhaUCur_A;
      }

      /* Switch: '<S115>/Switch3' incorporates:
       *  RelationalOperator: '<S118>/FixPt Relational Operator'
       *  UnitDelay: '<S118>/Delay Input1'
       *
       * Block description for '<S118>/Delay Input1':
       *
       *  Store in Global RAM
       */
      if ((sint32)VDGH_SumErr_flg > (sint32)
          SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_n) {
        /* Switch: '<S115>/Switch4' */
        VDGH_SumErrPhCurW_A = VPCS_PhaVCur_A;
      }

      /* End of Switch: '<S115>/Switch3' */

      /* Switch: '<S115>/Switch5' incorporates:
       *  RelationalOperator: '<S119>/FixPt Relational Operator'
       *  UnitDelay: '<S119>/Delay Input1'
       *
       * Block description for '<S119>/Delay Input1':
       *
       *  Store in Global RAM
       */
      if ((sint32)VDGH_SumErr_flg > (sint32)
          SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_m) {
        /* Switch: '<S115>/Switch6' */
        VDGH_SumErrPhCurV_A = VPCS_PhaWCur_A;
      }

      /* End of Switch: '<S115>/Switch5' */
    }

    /* End of Switch: '<S115>/Switch2' */

    /* Update for UnitDelay: '<S117>/Delay Input1'
     *
     * Block description for '<S117>/Delay Input1':
     *
     *  Store in Global RAM
     */
    SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_f = VDGH_SumErr_flg;

    /* Update for UnitDelay: '<S118>/Delay Input1'
     *
     * Block description for '<S118>/Delay Input1':
     *
     *  Store in Global RAM
     */
    SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_n = VDGH_SumErr_flg;

    /* Update for UnitDelay: '<S119>/Delay Input1'
     *
     * Block description for '<S119>/Delay Input1':
     *
     *  Store in Global RAM
     */
    SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_m = VDGH_SumErr_flg;

    /* End of Outputs for SubSystem: '<S114>/Sum_Err' */
  }

  /* End of If: '<S114>/If' */
}

/*
 * Output and update for enable system:
 *    '<S3>/Enable_GateIC'
 *    '<S3>/Subsystem1'
 */
void SWC_ETE_type_Enable_GateIC(boolean rtu_Enable)
{
  /* Outputs for Enabled SubSystem: '<S3>/Enable_GateIC' incorporates:
   *  EnablePort: '<S11>/Enable'
   */

  /* End of Outputs for SubSystem: '<S3>/Enable_GateIC' */
}

/* System initialize for atomic system: '<S2>/MTPA_FOC' */
void SWC_ETE_type_MTPA_FOC_Init(void)
{
  /* local block i/o variables */
  boolean rtb_Status_p;

  /* SystemInitialize for Atomic SubSystem: '<S3>/ADC_RDC_Read' */
  SWC_ETE_type_ADC_RDC_Read_Init();

  /* End of SystemInitialize for SubSystem: '<S3>/ADC_RDC_Read' */

  /* SystemInitialize for Atomic SubSystem: '<S6>/CurrentSensor' */
  CurrentSensor_Init();

  /* End of SystemInitialize for SubSystem: '<S6>/CurrentSensor' */

  /* SystemInitialize for Atomic SubSystem: '<S6>/OverCurrent' */
  /* SystemInitialize for Atomic SubSystem: '<S113>/debounce' */
  SWC_ETE_type_debounce_Init(&rtb_Status_p);

  /* End of SystemInitialize for SubSystem: '<S113>/debounce' */
  /* End of SystemInitialize for SubSystem: '<S6>/OverCurrent' */

  /* SystemInitialize for Atomic SubSystem: '<S3>/PDC' */
  SWC_ETE_type_PDC_Init();

  /* End of SystemInitialize for SubSystem: '<S3>/PDC' */
}

/* Output and update for atomic system: '<S2>/MTPA_FOC' */
void SWC_ETE_type_MTPA_FOC(void)
{
  /* local block i/o variables */
  boolean rtb_Status_p;
  DT_LoRateTxHiRateRx tmpRead;
  float32 tmp;
  uint32 rtb_CCaller1_g[3];
  boolean rtb_FixPtRelationalOperator_g;
  boolean rtb_UnitDelay_gi;

  /* Inport: '<Root>/R_LoRateTxHiRateRx_LoRateTxHiRateRx' */
  (void)Rte_Read_R_LoRateTxHiRateRx_LoRateTxHiRateRx(&tmpRead);

  /* Outputs for Atomic SubSystem: '<S3>/ADC_RDC_Read' */
  SWC_ETE_type_ADC_RDC_Read();

  /* End of Outputs for SubSystem: '<S3>/ADC_RDC_Read' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S3>/Constant10'
   *  Constant: '<S3>/Constant11'
   */
  if (KFOC_OpMod_enum_ovrdflg) {
    SWC_ETE_type_ARID_DEF.Switch2_o = KFOC_OpMod_enum_ovrdval;
  } else {
    SWC_ETE_type_ARID_DEF.Switch2_o = tmpRead.u8_OpMod_stIvtrTar;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/Constant5'
   *  Constant: '<S3>/Constant6'
   */
  if (KFOC_IdCmd_A_ovrdflg) {
    SWC_ETE_type_ARID_DEF.CCM_IdCmd = KFOC_IdCmd_A_ovrdfval;
  } else {
    SWC_ETE_type_ARID_DEF.CCM_IdCmd = tmpRead.f32_VMCM_IdCmd_A;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Switch: '<S3>/Switch1' incorporates:
   *  Constant: '<S3>/Constant8'
   *  Constant: '<S3>/Constant9'
   */
  if (KFOC_IqCmd_A_ovrdflg) {
    SWC_ETE_type_ARID_DEF.Switch1 = KFOC_IqCmd_A_ovrdfval;
  } else {
    SWC_ETE_type_ARID_DEF.Switch1 = tmpRead.f32_VMCM_IqCmd_A;
  }

  /* End of Switch: '<S3>/Switch1' */

  /* Outputs for Atomic SubSystem: '<S3>/CCM_FVT' */
  SWC_ETE_type_CCM_FVT();

  /* End of Outputs for SubSystem: '<S3>/CCM_FVT' */

  /* Outputs for Atomic SubSystem: '<S6>/ER_FF2' */
  /* Logic: '<S6>/Logical Operator4' incorporates:
   *  Constant: '<S6>/Constant8'
   */
  SWC_ETE_type_ER_FF(false_MatlabRTW, KDGH_bRstRteFault_flg,
                     &VDGH_PosSenrFaultLat_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF2);

  /* End of Outputs for SubSystem: '<S6>/ER_FF2' */

  /* RelationalOperator: '<S15>/Equal3' incorporates:
   *  Constant: '<S15>/Constant4'
   *  Constant: '<S3>/Constant13'
   */
  SWC_ETE_type_ARID_DEF.Equal3 = (KFOC_SensorMode_enum == 1);

  /* Outputs for Enabled SubSystem: '<S15>/Fake_RDC_Handler' */
  SWC_ETE_type_Fake_RDC_Handler();

  /* End of Outputs for SubSystem: '<S15>/Fake_RDC_Handler' */

  /* Outputs for Atomic SubSystem: '<S3>/FOC_Mode_Judge' */
  SWC_ETE_type_FOC_Mode_Judge();

  /* End of Outputs for SubSystem: '<S3>/FOC_Mode_Judge' */

  /* Outputs for Atomic SubSystem: '<S6>/OverCurrent' */
  /* Outputs for Atomic SubSystem: '<S113>/ER_FF' */
  /* Outputs for Atomic SubSystem: '<S147>/Delay' */
  SWC_ETE_type_Delay_l(&rtb_UnitDelay_gi,
                       &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_k);

  /* End of Outputs for SubSystem: '<S147>/Delay' */

  /* Switch: '<S155>/SWT' incorporates:
   *  Abs: '<S113>/Abs'
   *  Constant: '<S113>/Constant3'
   *  RelationalOperator: '<S113>/Relational Operator'
   */
  if (fabsf(VPCS_PhaUCur_A) >= KDGH_PhaCurrOverU_A) {
    /* Switch: '<S155>/SWT' incorporates:
     *  Constant: '<S147>/true'
     */
    VDGH_PhaCurrOverU_flg = true_MatlabRTW;
  } else {
    /* Switch: '<S155>/SWT' incorporates:
     *  Constant: '<S113>/Constant7'
     *  Switch: '<S154>/SWT'
     */
    VDGH_PhaCurrOverU_flg = ((!KDGH_RstPhaCurrOver_flg) && rtb_UnitDelay_gi);
  }

  /* End of Switch: '<S155>/SWT' */

  /* Update for Atomic SubSystem: '<S147>/Delay' */
  SWC_ETE_type_Delay_l_Update(VDGH_PhaCurrOverU_flg,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_k);

  /* End of Update for SubSystem: '<S147>/Delay' */
  /* End of Outputs for SubSystem: '<S113>/ER_FF' */

  /* Outputs for Atomic SubSystem: '<S113>/ER_FF1' */
  /* Outputs for Atomic SubSystem: '<S148>/Delay' */
  SWC_ETE_type_Delay_l(&rtb_UnitDelay_gi,
                       &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_c);

  /* End of Outputs for SubSystem: '<S148>/Delay' */

  /* Switch: '<S159>/SWT' incorporates:
   *  Abs: '<S113>/Abs1'
   *  Constant: '<S113>/Constant4'
   *  RelationalOperator: '<S113>/Relational Operator1'
   */
  if (fabsf(VPCS_PhaVCur_A) >= KDGH_PhaCurrOverV_A) {
    /* Switch: '<S159>/SWT' incorporates:
     *  Constant: '<S148>/true'
     */
    VDGH_PhaCurrOverV_flg = true_MatlabRTW;
  } else {
    /* Switch: '<S159>/SWT' incorporates:
     *  Constant: '<S113>/Constant8'
     *  Switch: '<S158>/SWT'
     */
    VDGH_PhaCurrOverV_flg = ((!KDGH_RstPhaCurrOver_flg) && rtb_UnitDelay_gi);
  }

  /* End of Switch: '<S159>/SWT' */

  /* Update for Atomic SubSystem: '<S148>/Delay' */
  SWC_ETE_type_Delay_l_Update(VDGH_PhaCurrOverV_flg,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_c);

  /* End of Update for SubSystem: '<S148>/Delay' */
  /* End of Outputs for SubSystem: '<S113>/ER_FF1' */

  /* Outputs for Atomic SubSystem: '<S113>/ER_FF2' */
  /* Outputs for Atomic SubSystem: '<S149>/Delay' */
  SWC_ETE_type_Delay_l(&rtb_UnitDelay_gi,
                       &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_m);

  /* End of Outputs for SubSystem: '<S149>/Delay' */

  /* Switch: '<S163>/SWT' incorporates:
   *  Abs: '<S113>/Abs2'
   *  Constant: '<S113>/Constant5'
   *  RelationalOperator: '<S113>/Relational Operator3'
   */
  if (fabsf(VPCS_PhaWCur_A) >= KDGH_PhaCurrOverW_A) {
    /* Switch: '<S163>/SWT' incorporates:
     *  Constant: '<S149>/true'
     */
    VDGH_PhaCurrOverW_flg = true_MatlabRTW;
  } else {
    /* Switch: '<S163>/SWT' incorporates:
     *  Constant: '<S113>/Constant12'
     *  Switch: '<S162>/SWT'
     */
    VDGH_PhaCurrOverW_flg = ((!KDGH_RstPhaCurrOver_flg) && rtb_UnitDelay_gi);
  }

  /* End of Switch: '<S163>/SWT' */

  /* Update for Atomic SubSystem: '<S149>/Delay' */
  SWC_ETE_type_Delay_l_Update(VDGH_PhaCurrOverW_flg,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay_m);

  /* End of Update for SubSystem: '<S149>/Delay' */
  /* End of Outputs for SubSystem: '<S113>/ER_FF2' */

  /* Outputs for Atomic SubSystem: '<S113>/debounce' */
  /* RelationalOperator: '<S113>/Relational Operator2' incorporates:
   *  Constant: '<S113>/Constant'
   *  Constant: '<S113>/Constant1'
   *  Constant: '<S113>/Constant2'
   *  Fcn: '<S113>/Fcn'
   *  Sqrt: '<S113>/Sqrt'
   */
  SWC_ETE_type_debounce((sqrtf(VCCM_iDCurrAct_A * VCCM_iDCurrAct_A +
    VCCM_iQCurrAct_A * VCCM_iQCurrAct_A) >= KDGH_OverCurrent_A),
                        KDGH_OverCurrentHeal_C, KDGH_OverCurrentErr_C,
                        &rtb_Status_p, &SWC_ETE_type_ARID_DEF.ARID_DEF_debounce);

  /* End of Outputs for SubSystem: '<S113>/debounce' */

  /* Outputs for Atomic SubSystem: '<S113>/ER_FF3' */
  /* Outputs for Atomic SubSystem: '<S150>/Delay' */
  SWC_ETE_type_Delay_l(&rtb_UnitDelay_gi, &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S150>/Delay' */

  /* Switch: '<S167>/SWT' */
  if (rtb_Status_p) {
    /* Switch: '<S167>/SWT' incorporates:
     *  Constant: '<S150>/true'
     */
    VDGH_PhaCurrOverDQ_flg = true_MatlabRTW;
  } else {
    /* Switch: '<S167>/SWT' incorporates:
     *  Constant: '<S113>/Constant13'
     *  Switch: '<S166>/SWT'
     */
    VDGH_PhaCurrOverDQ_flg = ((!KDGH_RstPhaCurrOver_flg) && rtb_UnitDelay_gi);
  }

  /* End of Switch: '<S167>/SWT' */

  /* Update for Atomic SubSystem: '<S150>/Delay' */
  SWC_ETE_type_Delay_l_Update(VDGH_PhaCurrOverDQ_flg,
    &SWC_ETE_type_ARID_DEF.ARID_DEF_Delay);

  /* End of Update for SubSystem: '<S150>/Delay' */
  /* End of Outputs for SubSystem: '<S113>/ER_FF3' */

  /* Switch: '<S113>/ESM_bMcuShtDwnAllwdswt' incorporates:
   *  Constant: '<S113>/ESM_bMcuShtDwnAllwdTrig_C'
   */
  if (KDGH_OverCurrent_flg_ovrdflg) {
    /* Switch: '<S113>/ESM_bMcuShtDwnAllwdswt' incorporates:
     *  Constant: '<S113>/ESM_bMcuShtDwnAllwdMor_C'
     */
    VDGH_OverCurrent_flg = KDGH_OverCurrent_flg_ovrdval;
  } else {
    /* Switch: '<S113>/ESM_bMcuShtDwnAllwdswt' incorporates:
     *  Logic: '<S113>/Logical Operator'
     */
    VDGH_OverCurrent_flg = (VDGH_PhaCurrOverDQ_flg || VDGH_PhaCurrOverU_flg ||
      VDGH_PhaCurrOverV_flg || VDGH_PhaCurrOverW_flg);
  }

  /* End of Switch: '<S113>/ESM_bMcuShtDwnAllwdswt' */
  /* End of Outputs for SubSystem: '<S6>/OverCurrent' */

  /* Outputs for Atomic SubSystem: '<S6>/CurrentSensor' */
  CurrentSensor();

  /* End of Outputs for SubSystem: '<S6>/CurrentSensor' */

  /* Outputs for Atomic SubSystem: '<S6>/ER_FF1' */
  /* Logic: '<S6>/Logical Operator3' incorporates:
   *  Constant: '<S6>/Constant8'
   */
  SWC_ETE_type_ER_FF(false_MatlabRTW, KDGH_bRstRteFault_flg,
                     &VDGH_CurrFaultLat_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF1);

  /* End of Outputs for SubSystem: '<S6>/ER_FF1' */

  /* Outputs for Atomic SubSystem: '<S6>/ER_FF3' */
  /* Logic: '<S6>/Logical Operator5' incorporates:
   *  Constant: '<S6>/Constant8'
   */
  SWC_ETE_type_ER_FF(false_MatlabRTW, KDGH_bRstRteFault_flg,
                     &VDGH_HWHsideFltLat_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF3);

  /* End of Outputs for SubSystem: '<S6>/ER_FF3' */

  /* Outputs for Atomic SubSystem: '<S6>/ER_FF4' */
  /* Logic: '<S6>/Logical Operator6' incorporates:
   *  Constant: '<S6>/Constant8'
   */
  SWC_ETE_type_ER_FF(false_MatlabRTW, KDGH_bRstRteFault_flg,
                     &VDGH_HWLsideFltLat_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF4);

  /* End of Outputs for SubSystem: '<S6>/ER_FF4' */

  /* Outputs for Atomic SubSystem: '<S6>/ER_FF5' */
  /* Logic: '<S6>/Logical Operator10' incorporates:
   *  Constant: '<S6>/Constant8'
   */
  SWC_ETE_type_ER_FF(false_MatlabRTW, KDGH_bRstRteFault_flg,
                     &VDGH_HWOverVoltFltLat_flg,
                     &SWC_ETE_type_ARID_DEF.ARID_DEF_ER_FF5);

  /* End of Outputs for SubSystem: '<S6>/ER_FF5' */

  /* Logic: '<S6>/Logical Operator1' */
  VDGH_RteFault_flg = (VDGH_CurrFaultLat_flg || VDGH_PosSenrFaultLat_flg ||
                       VDGH_HWHsideFltLat_flg || VDGH_HWLsideFltLat_flg ||
                       VDGH_HWOverVoltFltLat_flg);

  /* Logic: '<S6>/Logical Operator8' incorporates:
   *  Logic: '<S6>/Logical Operator7'
   */
  rtb_UnitDelay_gi = ((!VPCS_bCurOffsVolVld_flg) && VPCS_SnsrSelfLrnCompl_flg);

  /* Switch: '<S6>/bsw_bPosSenrFaultswt' incorporates:
   *  Constant: '<S6>/bsw_bPosSenrFaultTrig_C'
   */
  if (KDGH_FaultLevel2_flg_ovrdflg) {
    /* Switch: '<S6>/bsw_bPosSenrFaultswt' incorporates:
     *  Constant: '<S6>/bsw_bPosSenrFaultMor_C'
     */
    VDGH_100usFaultLevel2_flg = KDGH_FaultLevel2_flg_ovrdval;
  } else {
    /* Switch: '<S6>/bsw_bPosSenrFaultswt' incorporates:
     *  Logic: '<S6>/Logical Operator'
     */
    VDGH_100usFaultLevel2_flg = (VDGH_OverCurrent_flg || VDGH_SumErr_flg ||
      VCCM_CurErrorOverThd2_flg || VDGH_RteFault_flg || rtb_UnitDelay_gi);
  }

  /* End of Switch: '<S6>/bsw_bPosSenrFaultswt' */

  /* Switch: '<S3>/Switch3' incorporates:
   *  Constant: '<S3>/Constant12'
   *  Constant: '<S3>/Constant14'
   *  DataTypeConversion: '<S3>/Cast To Boolean'
   */
  if (KFOC_FltActn_flg_ovrdflg) {
    rtb_FixPtRelationalOperator_g = KFOC_FltActn_flg_ovrdfval;
  } else {
    rtb_FixPtRelationalOperator_g = (tmpRead.u8_VDSM_FltActn22_flg != 0);
  }

  /* Logic: '<S6>/Logical Operator2' incorporates:
   *  Switch: '<S3>/Switch3'
   */
  VDGH_FaultLevel2_flg = (VDGH_100usFaultLevel2_flg ||
    rtb_FixPtRelationalOperator_g);

  /* Outputs for Atomic SubSystem: '<S3>/PDC' */
  SWC_ETE_type_PDC();

  /* End of Outputs for SubSystem: '<S3>/PDC' */

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Product: '<S3>/Product'
   *  Switch: '<S186>/Switch2'
   */
  tmp = fmodf(floorf(SWC_ETE_type_ARID_DEF.Switch2[0] * (float32)
                     VROT_FreqPWM_Tick), 4.2949673E+9F);

  /* CCaller: '<S3>/C Caller1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   */
  rtb_CCaller1_g[0] = tmp < 0.0F ? (uint32)-(sint32)(uint32)-tmp : (uint32)tmp;

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Product: '<S3>/Product'
   *  Switch: '<S186>/Switch2'
   */
  tmp = fmodf(floorf(SWC_ETE_type_ARID_DEF.Switch2[1] * (float32)
                     VROT_FreqPWM_Tick), 4.2949673E+9F);

  /* CCaller: '<S3>/C Caller1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   */
  rtb_CCaller1_g[1] = tmp < 0.0F ? (uint32)-(sint32)(uint32)-tmp : (uint32)tmp;

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Product: '<S3>/Product'
   *  Switch: '<S186>/Switch2'
   */
  tmp = fmodf(floorf(SWC_ETE_type_ARID_DEF.Switch2[2] * (float32)
                     VROT_FreqPWM_Tick), 4.2949673E+9F);

  /* CCaller: '<S3>/C Caller1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   */
  rtb_CCaller1_g[2] = tmp < 0.0F ? (uint32)-(sint32)(uint32)-tmp : (uint32)tmp;

  /* CCaller: '<S3>/C Caller1' */

  /* DataTypeConversion: '<S3>/Data Type Conversion10' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_VDSM_FltActn12_flg =
    VDGH_100usFaultLevel2_flg;

  /* DataTypeConversion: '<S3>/Data Type Conversion2' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_PCS_bOverCurr = VDGH_OverCurrent_flg;

  /* DataTypeConversion: '<S3>/Data Type Conversion3' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_Diag_bPhaCurrOverU = VDGH_PhaCurrOverU_flg;

  /* DataTypeConversion: '<S3>/Data Type Conversion4' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_Diag_bPhaCurrOverV = VDGH_PhaCurrOverV_flg;

  /* DataTypeConversion: '<S3>/Data Type Conversion5' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_Diag_bPhaCurrOverW = VDGH_PhaCurrOverW_flg;

  /* DataTypeConversion: '<S3>/Data Type Conversion9' */
  SWC_ETE_type_ARID_DEF.BusCreator.u8_Diag1_b1_SumErr_null = VDGH_SumErr_flg;

  /* BusCreator: '<S3>/Bus Creator' */
  SWC_ETE_type_ARID_DEF.BusCreator.f32_DSS_uDCSide = VFOC_DCBusVoltage_V;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_RotS_nRot = VROT_RotSpdM_rpm;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_RotS_agRot = VROT_RotAngleE_rad;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_PCS_iPaCS = VPCS_PhaUCur_A;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_PCS_iPbCS = VPCS_PhaVCur_A;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_PCS_iPcCS = VPCS_PhaWCur_A;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_TorqEst_tqMotEst = VMCM_TqEst_Nm;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_CCM_uDVoltTar = VCCM_VdCmd_V;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_CCM_uQVoltTar = VCCM_VqCmd_V;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_CCM_iDCurrAct = VCCM_iDCurrAct_A;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_CCM_iQCurrAct = VCCM_iQCurrAct_A;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_VCCM_BattVolCirRadius_V =
    VCCM_BattVolCirRadius_V;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_VCCM_VcmdBfLim_V = VCCM_VcmdBfLim_V;
  SWC_ETE_type_ARID_DEF.BusCreator.f32_VMCM_TqAct_Nm = VMCM_TqAct_Nm;

  /* Logic: '<S6>/Logical Operator9' incorporates:
   *  UnitDelay: '<S6>/Unit Delay'
   */
  VDGH_CurOffsErrLat_flg = (rtb_UnitDelay_gi || VDGH_CurOffsErrLat_flg);

  /* Outputs for Enabled SubSystem: '<S15>/Subsystem' incorporates:
   *  EnablePort: '<S263>/Enable'
   */
  /* RelationalOperator: '<S15>/Equal2' incorporates:
   *  Constant: '<S15>/Constant3'
   *  Constant: '<S3>/Constant13'
   */
  if (KFOC_SensorMode_enum == 3) {
    /* Abs: '<S263>/Abs' incorporates:
     *  Constant: '<S263>/Constant'
     *  Sum: '<S263>/Subtract'
     */
    SWC_ETE_type_ARID_DEF.VFOC_PosnOffset_rad = fabsf(VROT_RotAngleERaw_rad -
      3.14159274F);
  }

  /* End of RelationalOperator: '<S15>/Equal2' */
  /* End of Outputs for SubSystem: '<S15>/Subsystem' */

  /* Switch: '<S15>/Switch' incorporates:
   *  Constant: '<S15>/Constant'
   *  Constant: '<S15>/Constant1'
   */
  if (KFOC_RotPosnOffset_rad_ovrdflg) {
    VFOC_RotorPosnOffset_rad = KFOC_RotPosnOffset_rad_ovrdval;
  } else {
    VFOC_RotorPosnOffset_rad = SWC_ETE_type_ARID_DEF.VFOC_PosnOffset_rad;
  }

  /* End of Switch: '<S15>/Switch' */

  /* Switch: '<S14>/Switch6' incorporates:
   *  Constant: '<S14>/Constant'
   */
  rtb_UnitDelay_gi = KFOC_PWMidle_flg;

  /* Outputs for Enabled SubSystem: '<S14>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S261>/Enable'
   */
  /* RelationalOperator: '<S260>/FixPt Relational Operator' incorporates:
   *  Constant: '<S14>/Constant'
   *  Switch: '<S14>/Switch6'
   *  UnitDelay: '<S260>/Delay Input1'
   *
   * Block description for '<S260>/Delay Input1':
   *
   *  Store in Global RAM
   */

  /* End of RelationalOperator: '<S260>/FixPt Relational Operator' */
  /* End of Outputs for SubSystem: '<S14>/Enabled Subsystem' */

  /* Outputs for Enabled SubSystem: '<S3>/Disable_GateIC' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  /* RelationalOperator: '<S8>/FixPt Relational Operator' incorporates:
   *  Constant: '<S3>/Constant1'
   *  UnitDelay: '<S8>/Delay Input1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
 

  /* End of RelationalOperator: '<S8>/FixPt Relational Operator' */
  /* End of Outputs for SubSystem: '<S3>/Disable_GateIC' */

  /* Outputs for Enabled SubSystem: '<S3>/Enable_GateIC' */
  /* RelationalOperator: '<S9>/FixPt Relational Operator' incorporates:
   *  Constant: '<S3>/Constant3'
   *  UnitDelay: '<S9>/Delay Input1'
   *
   * Block description for '<S9>/Delay Input1':
   *
   *  Store in Global RAM
   */
  SWC_ETE_type_Enable_GateIC(((sint32)KFOC_GateICEnable_flg > (sint32)
    SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_j));

  /* End of Outputs for SubSystem: '<S3>/Enable_GateIC' */

  /* Outputs for Enabled SubSystem: '<S3>/Subsystem1' */
  /* UnitDelay: '<S3>/Unit Delay' */
  SWC_ETE_type_Enable_GateIC(SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_c);

  /* End of Outputs for SubSystem: '<S3>/Subsystem1' */

  /* RelationalOperator: '<S7>/FixPt Relational Operator' incorporates:
   *  Constant: '<S3>/Constant7'
   *  UnitDelay: '<S7>/Delay Input1'
   *
   * Block description for '<S7>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator_g = !SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_i;

  /* Outputs for Enabled SubSystem: '<S3>/Subsystem' incorporates:
   *  EnablePort: '<S16>/Enable'
   */
  if (rtb_FixPtRelationalOperator_g) {
    /* CCaller: '<S16>/C Caller' */
    Ifx_SvmF32_init();
  }

  /* End of Outputs for SubSystem: '<S3>/Subsystem' */

  /* Update for UnitDelay: '<S260>/Delay Input1'
   *
   * Block description for '<S260>/Delay Input1':
   *
   *  Store in Global RAM
   */
  SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE = rtb_UnitDelay_gi;

  /* Update for UnitDelay: '<S8>/Delay Input1' incorporates:
   *  Constant: '<S3>/Constant1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_h = KFOC_GateICDisable_flg;

  /* Update for UnitDelay: '<S9>/Delay Input1' incorporates:
   *  Constant: '<S3>/Constant3'
   *
   * Block description for '<S9>/Delay Input1':
   *
   *  Store in Global RAM
   */
  SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_j = KFOC_GateICEnable_flg;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  SWC_ETE_type_ARID_DEF.UnitDelay_DSTATE_c = rtb_FixPtRelationalOperator_g;

  /* Update for UnitDelay: '<S7>/Delay Input1' incorporates:
   *  Constant: '<S3>/Constant7'
   *
   * Block description for '<S7>/Delay Input1':
   *
   *  Store in Global RAM
   */
  SWC_ETE_type_ARID_DEF.DelayInput1_DSTATE_i = true_MatlabRTW;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
