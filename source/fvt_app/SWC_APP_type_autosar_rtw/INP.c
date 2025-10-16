/*
 * File: INP.c
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

#include "INP.h"
#include "HCU_LIB.h"
#include "rtwtypes.h"

/* Includes for objects with custom storage classes */
#include "SWC_APP_type.h"

/* Output and update for atomic system: '<S2>/INP' */
void SWC_APP_type_INP(void)
{
  float32 rtb_Switch1;
  float32 rtb_valid_signal;
  float32 rtb_valid_signal_b;
  float32 rtb_valid_signal_d;
  float32 rtb_valid_signal_i;
  float32 rtb_valid_signal_j3;
  float32 rtb_valid_signal_jp2;
  float32 rtb_valid_signal_k;
  float32 rtb_valid_signal_km;
  float32 rtb_valid_signal_kr;
  float32 rtb_valid_signal_krk;
  float32 rtb_valid_signal_kx;
  float32 rtb_valid_signal_nx;
  float32 rtb_valid_signal_o;
  float32 rtb_valid_signal_oy;
  float32 rtb_valid_signal_p;
  float32 rtb_valid_signal_p3;
  uint8 rtb_Switch1_ft;
  uint8 rtb_valid_signal_b2;
  uint8 rtb_valid_signal_bh;
  uint8 rtb_valid_signal_ch;
  uint8 rtb_valid_signal_cs;
  uint8 rtb_valid_signal_ej;
  uint8 rtb_valid_signal_fk;
  uint8 rtb_valid_signal_i3;
  uint8 rtb_valid_signal_l1;
  uint8 rtb_valid_signal_n;
  uint8 rtb_valid_signal_n4;
  uint8 rtb_valid_signal_ot;
  uint8 rtb_valid_signal_ov;
  uint8 rtb_valid_signal_pqq;
  uint8 rtb_valid_signal_ptu;
  boolean rtb_Switch1_gv;
  boolean rtb_valid_signal_bk;
  boolean rtb_valid_signal_ce;
  boolean rtb_valid_signal_ck;
  boolean rtb_valid_signal_cr;
  boolean rtb_valid_signal_d0;
  boolean rtb_valid_signal_eyl;
  boolean rtb_valid_signal_hi;
  boolean rtb_valid_signal_if;
  boolean rtb_valid_signal_jq;
  boolean rtb_valid_signal_l;
  boolean rtb_valid_signal_ob;
  boolean rtb_valid_signal_ow;
  boolean rtb_valid_signal_p1;
  boolean rtb_valid_signal_pg;
  boolean rtb_valid_signal_ps;
  boolean rtb_valid_signal_pw;

  /* Outputs for Atomic SubSystem: '<S511>/override_signal_m2 ' */

  /* Constant: '<S510>/ovrdflg' incorporates:
   *  Constant: '<S510>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_CANMsgInvalidEOPFVTRLocal1_flg,
     KINP_CANMsgInvalidEOPFVTRLocal1_flg_ovrdflg,
     KINP_CANMsgInvalidEOPFVTRLocal1_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S511>/override_signal_m2 ' */

  /* Logic: '<S507>/not1' */
  VINP_CANMsgValidEOPFVTRLocal1_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S562>/signal validity checking' */

  /* Logic: '<S562>/Logical Operator2' incorporates:
   *  Constant: '<S523>/defval'
   */
  rtb_valid_signal_cr = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverTempSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTROverTempSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_nv);

  /* End of Outputs for SubSystem: '<S562>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S562>/override_signal_m2 ' */

  /* Constant: '<S523>/ovrdflg' incorporates:
   *  Constant: '<S523>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_cr,
    KINP_EOPFVTROverTempSta_flg_ovrdflg, KINP_EOPFVTROverTempSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S562>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_10' */
  VINP_EOPFVTROverTempSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S566>/signal validity checking' */

  /* Logic: '<S566>/Logical Operator2' incorporates:
   *  Constant: '<S524>/defval'
   */
  rtb_valid_signal_ptu = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverVolSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTROverVolSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_oy);

  /* End of Outputs for SubSystem: '<S566>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S566>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_11' incorporates:
   *  Constant: '<S524>/ovrdflg'
   *  Constant: '<S524>/ovrdval'
   */
  VINP_EOPFVTROverVolSta_enum = SWC_APP_ty_override_signal_m2_p
    (rtb_valid_signal_ptu, KINP_EOPFVTROverVolSta_enum_ovrdflg,
     KINP_EOPFVTROverVolSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S566>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S570>/signal validity checking' */

  /* Logic: '<S570>/Logical Operator2' incorporates:
   *  Constant: '<S525>/defval'
   */
  rtb_valid_signal_hi = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRPumpReadySta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRPumpReadySta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_i);

  /* End of Outputs for SubSystem: '<S570>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S570>/override_signal_m2 ' */

  /* Constant: '<S525>/ovrdflg' incorporates:
   *  Constant: '<S525>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_hi,
    KINP_EOPFVTRPumpReadySta_flg_ovrdflg, KINP_EOPFVTRPumpReadySta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S570>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_12' */
  VINP_EOPFVTRPumpReadySta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S574>/signal validity checking' */

  /* Logic: '<S574>/Logical Operator2' incorporates:
   *  Constant: '<S526>/defval'
   */
  rtb_valid_signal_bk = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRRCInvalidSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRRCInvalidSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_n);

  /* End of Outputs for SubSystem: '<S574>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S574>/override_signal_m2 ' */

  /* Constant: '<S526>/ovrdflg' incorporates:
   *  Constant: '<S526>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_bk,
    KINP_EOPFVTRRCInvalidSta_flg_ovrdflg, KINP_EOPFVTRRCInvalidSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S574>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_13' */
  VINP_EOPFVTRRCInvalidSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S578>/signal validity checking' */

  /* Logic: '<S578>/Logical Operator2' incorporates:
   *  Constant: '<S527>/defval'
   */
  rtb_valid_signal_ov = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRRunStatusSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRRunStatusSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_o);

  /* End of Outputs for SubSystem: '<S578>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S578>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_14' incorporates:
   *  Constant: '<S527>/ovrdflg'
   *  Constant: '<S527>/ovrdval'
   */
  VINP_EOPFVTRRunStatusSta_enum = SWC_APP_ty_override_signal_m2_p
    (rtb_valid_signal_ov, KINP_EOPFVTRRunStatusSta_enum_ovrdflg,
     KINP_EOPFVTRRunStatusSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S578>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S582>/signal validity checking' */

  /* Logic: '<S582>/Logical Operator2' incorporates:
   *  Constant: '<S528>/defval'
   */
  rtb_valid_signal_if = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRStartFailureSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRStartFailureSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_j);

  /* End of Outputs for SubSystem: '<S582>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S582>/override_signal_m2 ' */

  /* Constant: '<S528>/ovrdflg' incorporates:
   *  Constant: '<S528>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_if,
    KINP_EOPFVTRStartFailureSta_flg_ovrdflg,
    KINP_EOPFVTRStartFailureSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S582>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_15' */
  VINP_EOPFVTRStartFailureSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S586>/signal validity checking' */

  /* Logic: '<S586>/Logical Operator2' incorporates:
   *  Constant: '<S529>/defval'
   */
  rtb_valid_signal_cs = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRUnderVolSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRUnderVolSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheckin);

  /* End of Outputs for SubSystem: '<S586>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S586>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_16' incorporates:
   *  Constant: '<S529>/ovrdflg'
   *  Constant: '<S529>/ovrdval'
   */
  VINP_EOPFVTRUnderVolSta_enum = SWC_APP_ty_override_signal_m2_p
    (rtb_valid_signal_cs, KINP_EOPFVTRUnderVolSta_enum_ovrdflg,
     KINP_EOPFVTRUnderVolSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S586>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S530>/signal validity checking' */

  /* Logic: '<S530>/Logical Operator2' incorporates:
   *  Constant: '<S515>/defval'
   */
  rtb_valid_signal = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRActualSpdSta_rpm,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRActualSpdSta_rpm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_ct);

  /* End of Outputs for SubSystem: '<S530>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S530>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_2' incorporates:
   *  Constant: '<S515>/ovrdflg'
   *  Constant: '<S515>/ovrdval'
   */
  VINP_EOPFVTRActualSpdSta_rpm = SWC_APP_ty_override_signal_m2_m
    (rtb_valid_signal, KINP_EOPFVTRActualSpdSta_rpm_ovrdflg,
     KINP_EOPFVTRActualSpdSta_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S530>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S534>/signal validity checking' */

  /* Logic: '<S534>/Logical Operator2' incorporates:
   *  Constant: '<S516>/defval'
   */
  rtb_valid_signal_eyl = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRCSInvalidSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRCSInvalidSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_c0);

  /* End of Outputs for SubSystem: '<S534>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S534>/override_signal_m2 ' */

  /* Constant: '<S516>/ovrdflg' incorporates:
   *  Constant: '<S516>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_eyl,
    KINP_EOPFVTRCSInvalidSta_flg_ovrdflg, KINP_EOPFVTRCSInvalidSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S534>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_3' */
  VINP_EOPFVTRCSInvalidSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S538>/signal validity checking' */

  /* Logic: '<S538>/Logical Operator2' incorporates:
   *  Constant: '<S517>/defval'
   */
  rtb_valid_signal_jq = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRCanLossSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRCanLossSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_h);

  /* End of Outputs for SubSystem: '<S538>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S538>/override_signal_m2 ' */

  /* Constant: '<S517>/ovrdflg' incorporates:
   *  Constant: '<S517>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_jq,
    KINP_EOPFVTRCanLossSta_flg_ovrdflg, KINP_EOPFVTRCanLossSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S538>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_4' */
  VINP_EOPFVTRCanLossSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S542>/signal validity checking' */

  /* Logic: '<S542>/Logical Operator2' incorporates:
   *  Constant: '<S518>/defval'
   */
  rtb_valid_signal_d0 = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTREnableOffSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTREnableOffSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_ja);

  /* End of Outputs for SubSystem: '<S542>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S542>/override_signal_m2 ' */

  /* Constant: '<S518>/ovrdflg' incorporates:
   *  Constant: '<S518>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_d0,
    KINP_EOPFVTREnableOffSta_flg_ovrdflg, KINP_EOPFVTREnableOffSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S542>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_5' */
  VINP_EOPFVTREnableOffSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S546>/signal validity checking' */

  /* Logic: '<S546>/Logical Operator2' incorporates:
   *  Constant: '<S519>/defval'
   */
  rtb_valid_signal_ow = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRHallSigErrSta_flg,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRHallSigErrSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_m3);

  /* End of Outputs for SubSystem: '<S546>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S546>/override_signal_m2 ' */

  /* Constant: '<S519>/ovrdflg' incorporates:
   *  Constant: '<S519>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_ow,
    KINP_EOPFVTRHallSigErrSta_flg_ovrdflg, KINP_EOPFVTRHallSigErrSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S546>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_6' */
  VINP_EOPFVTRHallSigErrSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S550>/signal validity checking' */

  /* Logic: '<S550>/Logical Operator2' incorporates:
   *  Constant: '<S520>/defval'
   */
  rtb_valid_signal_l1 = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRLocal1CSSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRLocal1CSSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_md);

  /* End of Outputs for SubSystem: '<S550>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S550>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_7' incorporates:
   *  Constant: '<S520>/ovrdflg'
   *  Constant: '<S520>/ovrdval'
   */
  VINP_EOPFVTRLocal1CSSta_enum = SWC_APP_ty_override_signal_m2_p
    (rtb_valid_signal_l1, KINP_EOPFVTRLocal1CSSta_enum_ovrdflg,
     KINP_EOPFVTRLocal1CSSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S550>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S554>/signal validity checking' */

  /* Logic: '<S554>/Logical Operator2' incorporates:
   *  Constant: '<S521>/defval'
   */
  rtb_valid_signal_fk = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRLocal1RCSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTRLocal1RCSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_c);

  /* End of Outputs for SubSystem: '<S554>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S554>/override_signal_m2 ' */

  /* Constant: '<S521>/ovrdflg' incorporates:
   *  Constant: '<S521>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_fk,
    KINP_EOPFVTRLocal1RCSta_enum_ovrdflg, KINP_EOPFVTRLocal1RCSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S554>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_8' */
  VINP_EOPFVTRLocal1RCSta_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S558>/signal validity checking' */

  /* Logic: '<S558>/Logical Operator2' incorporates:
   *  Constant: '<S522>/defval'
   */
  rtb_valid_signal_pqq = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverTempBCKSta_enum,
     VINP_CANMsgValidEOPFVTRLocal1_flg, KINP_EOPFVTROverTempBCKSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_m);

  /* End of Outputs for SubSystem: '<S558>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S558>/override_signal_m2 ' */

  /* Constant: '<S522>/ovrdflg' incorporates:
   *  Constant: '<S522>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_pqq,
    KINP_EOPFVTROverTempBCKSta_enum_ovrdflg,
    KINP_EOPFVTROverTempBCKSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S558>/override_signal_m2 ' */

  /* DataTypeConversion: '<S508>/UnitConverter_9' */
  VINP_EOPFVTROverTempBCKSta_enum = rtb_Switch1_ft;

  /* BusCreator: '<S508>/bus_creator' */
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_CANMsgValidEOPFVTRLocal1_flg =
    VINP_CANMsgValidEOPFVTRLocal1_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRActualSpdSta_rpm =
    VINP_EOPFVTRActualSpdSta_rpm;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRCSInvalidSta_flg =
    VINP_EOPFVTRCSInvalidSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRCanLossSta_flg =
    VINP_EOPFVTRCanLossSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTREnableOffSta_flg =
    VINP_EOPFVTREnableOffSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRHallSigErrSta_flg =
    VINP_EOPFVTRHallSigErrSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRLocal1CSSta_enum =
    VINP_EOPFVTRLocal1CSSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRLocal1RCSta_enum =
    VINP_EOPFVTRLocal1RCSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTROverTempBCKSta_enum =
    VINP_EOPFVTROverTempBCKSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTROverTempSta_flg =
    VINP_EOPFVTROverTempSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTROverVolSta_enum =
    VINP_EOPFVTROverVolSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRPumpReadySta_flg =
    VINP_EOPFVTRPumpReadySta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRRCInvalidSta_flg =
    VINP_EOPFVTRRCInvalidSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRRunStatusSta_enum =
    VINP_EOPFVTRRunStatusSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRStartFailureSta_flg =
    VINP_EOPFVTRStartFailureSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_b.VINP_EOPFVTRUnderVolSta_enum =
    VINP_EOPFVTRUnderVolSta_enum;

  /* Outputs for Atomic SubSystem: '<S324>/override_signal_m2 ' */

  /* Constant: '<S317>/ovrdflg' incorporates:
   *  Constant: '<S317>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidBMS1_flg,
     KINP_CANMsgInvalidBMS1_flg_ovrdflg, KINP_CANMsgInvalidBMS1_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S324>/override_signal_m2 ' */

  /* Logic: '<S314>/not1' */
  VINP_CANMsgValidBMS1_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S355>/signal validity checking' */

  /* Logic: '<S355>/Logical Operator2' incorporates:
   *  Constant: '<S352>/defval'
   */
  rtb_valid_signal_ob = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS1CSErr_flg,
     VINP_CANMsgValidBMS1_flg, KINP_BMS1CSErr_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_h3);

  /* End of Outputs for SubSystem: '<S355>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S355>/override_signal_m2 ' */

  /* Constant: '<S352>/ovrdflg' incorporates:
   *  Constant: '<S352>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_ob,
    KINP_BMS1CSErr_flg_ovrdflg, KINP_BMS1CSErr_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S355>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_8' */
  VINP_BMS1CSErr_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S327>/override_signal_m2 ' */

  /* Constant: '<S318>/ovrdflg' incorporates:
   *  Constant: '<S318>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidBMS6_flg,
     KINP_CANMsgInvalidBMS6_flg_ovrdflg, KINP_CANMsgInvalidBMS6_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S327>/override_signal_m2 ' */

  /* Logic: '<S314>/not2' */
  VINP_CANMsgValidBMS6_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S330>/override_signal_m2 ' */

  /* Constant: '<S319>/ovrdflg' incorporates:
   *  Constant: '<S319>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3C1000_flg,
     KINP_CANMsgInvalidFD3C1000_flg_ovrdflg,
     KINP_CANMsgInvalidFD3C1000_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S330>/override_signal_m2 ' */

  /* Logic: '<S314>/not3' */
  VINP_CANMsgValidFD3C1000_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S333>/override_signal_m2 ' */

  /* Constant: '<S320>/ovrdflg' incorporates:
   *  Constant: '<S320>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU1_flg,
     KINP_CANMsgInvalidFD3VCU1_flg_ovrdflg,
     KINP_CANMsgInvalidFD3VCU1_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S333>/override_signal_m2 ' */

  /* Logic: '<S314>/not4' */
  VINP_CANMsgValidFD3VCU1_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S336>/override_signal_m2 ' */

  /* Constant: '<S321>/ovrdflg' incorporates:
   *  Constant: '<S321>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU2_flg,
     KINP_CANMsgInvalidFD3VCU2_flg_ovrdflg,
     KINP_CANMsgInvalidFD3VCU2_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S336>/override_signal_m2 ' */

  /* Logic: '<S314>/not5' */
  VINP_CANMsgValidFD3VCU2_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S339>/override_signal_m2 ' */

  /* Constant: '<S322>/ovrdflg' incorporates:
   *  Constant: '<S322>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU5_flg,
     KINP_CANMsgInvalidFD3VCU5_flg_ovrdflg,
     KINP_CANMsgInvalidFD3VCU5_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S339>/override_signal_m2 ' */

  /* Logic: '<S314>/not6' */
  VINP_CANMsgValidFD3VCU5_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S342>/override_signal_m2 ' */

  /* Constant: '<S323>/ovrdflg' incorporates:
   *  Constant: '<S323>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidGW3CE1000_flg,
     KINP_CANMsgInvalidGW3CE1000_flg_ovrdflg,
     KINP_CANMsgInvalidGW3CE1000_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S342>/override_signal_m2 ' */

  /* Logic: '<S314>/not7' */
  VINP_CANMsgValidGW3CE1000_flg = !rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S363>/signal validity checking' */

  /* Logic: '<S363>/Logical Operator2' incorporates:
   *  Constant: '<S354>/defval'
   */
  rtb_valid_signal_b = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_HVBattVolt_V,
     VINP_CANMsgValidBMS1_flg, KINP_HVBattVolt_V_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_me);

  /* End of Outputs for SubSystem: '<S363>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S363>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_10' incorporates:
   *  Constant: '<S354>/ovrdflg'
   *  Constant: '<S354>/ovrdval'
   */
  VINP_HVBattVolt_V = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_b,
    KINP_HVBattVolt_V_ovrdflg, KINP_HVBattVolt_V_ovrdval);

  /* End of Outputs for SubSystem: '<S363>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S370>/signal validity checking' */

  /* Logic: '<S370>/Logical Operator2' incorporates:
   *  Constant: '<S367>/defval'
   */
  rtb_valid_signal_p1 = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS6CSErr_flg,
     VINP_CANMsgValidBMS6_flg, KINP_BMS6CSErr_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_h2);

  /* End of Outputs for SubSystem: '<S370>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S370>/override_signal_m2 ' */

  /* Constant: '<S367>/ovrdflg' incorporates:
   *  Constant: '<S367>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_p1,
    KINP_BMS6CSErr_flg_ovrdflg, KINP_BMS6CSErr_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S370>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_11' */
  VINP_BMS6CSErr_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S374>/signal validity checking' */

  /* Logic: '<S374>/Logical Operator2' incorporates:
   *  Constant: '<S368>/defval'
   */
  rtb_valid_signal_pg = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS6RCErr_flg,
     VINP_CANMsgValidBMS6_flg, KINP_BMS6RCErr_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_l5);

  /* End of Outputs for SubSystem: '<S374>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S374>/override_signal_m2 ' */

  /* Constant: '<S368>/ovrdflg' incorporates:
   *  Constant: '<S368>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_pg,
    KINP_BMS6RCErr_flg_ovrdflg, KINP_BMS6RCErr_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S374>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_12' */
  VINP_BMS6RCErr_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S378>/signal validity checking' */

  /* Logic: '<S378>/Logical Operator2' incorporates:
   *  Constant: '<S369>/defval'
   */
  rtb_valid_signal_ck = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_HVBContactorSta_flg,
     VINP_CANMsgValidBMS6_flg, KINP_HVBContactorSta_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_hh);

  /* End of Outputs for SubSystem: '<S378>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S378>/override_signal_m2 ' */

  /* Constant: '<S369>/ovrdflg' incorporates:
   *  Constant: '<S369>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_ck,
    KINP_HVBContactorSta_flg_ovrdflg, KINP_HVBContactorSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S378>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_13' */
  VINP_HVBContactorSta_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S385>/signal validity checking' */

  /* Logic: '<S385>/Logical Operator2' incorporates:
   *  Constant: '<S382>/defval'
   */
  rtb_valid_signal_bh = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BatteryMode_enum,
     VINP_CANMsgValidFD3C1000_flg, KINP_BatteryMode_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_o4);

  /* End of Outputs for SubSystem: '<S385>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S385>/override_signal_m2 ' */

  /* Constant: '<S382>/ovrdflg' incorporates:
   *  Constant: '<S382>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_bh,
    KINP_BatteryMode_enum_ovrdflg, KINP_BatteryMode_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S385>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_14' */
  VINP_BatteryMode_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S389>/signal validity checking' */

  /* Logic: '<S389>/Logical Operator2' incorporates:
   *  Constant: '<S383>/defval'
   */
  rtb_valid_signal_jp2 = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrCoolantflow_Lpmin,
     VINP_CANMsgValidFD3C1000_flg, KINP_RrCoolantflow_Lpmin_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_e1);

  /* End of Outputs for SubSystem: '<S389>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S389>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_15' incorporates:
   *  Constant: '<S383>/ovrdflg'
   *  Constant: '<S383>/ovrdval'
   */
  VINP_RrCoolantflow_Lpmin = SWC_APP_ty_override_signal_m2_m
    (rtb_valid_signal_jp2, KINP_RrCoolantflow_Lpmin_ovrdflg,
     KINP_RrCoolantflow_Lpmin_ovrdval);

  /* End of Outputs for SubSystem: '<S389>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S393>/signal validity checking' */

  /* Logic: '<S393>/Logical Operator2' incorporates:
   *  Constant: '<S384>/defval'
   */
  rtb_valid_signal_p3 = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrCoolanttemp_C,
     VINP_CANMsgValidFD3C1000_flg, KINP_RrCoolanttemp_C_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_p4);

  /* End of Outputs for SubSystem: '<S393>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S393>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_16' incorporates:
   *  Constant: '<S384>/ovrdflg'
   *  Constant: '<S384>/ovrdval'
   */
  VINP_RrCoolanttemp_C = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_p3,
    KINP_RrCoolanttemp_C_ovrdflg, KINP_RrCoolanttemp_C_ovrdval);

  /* End of Outputs for SubSystem: '<S393>/override_signal_m2 ' */

  /* Outputs for Atomic SubSystem: '<S402>/signal validity checking' */

  /* Logic: '<S402>/Logical Operator2' incorporates:
   *  Constant: '<S397>/defval'
   */
  rtb_valid_signal_ce = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_ActiveDischReq_flg,
     VINP_CANMsgValidFD3VCU1_flg, KINP_ActiveDischReq_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_fm);

  /* End of Outputs for SubSystem: '<S402>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S402>/override_signal_m2 ' */

  /* Constant: '<S397>/ovrdflg' incorporates:
   *  Constant: '<S397>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_ce,
    KINP_ActiveDischReq_flg_ovrdflg, KINP_ActiveDischReq_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S402>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_17' */
  VINP_ActiveDischReq_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S406>/signal validity checking' */

  /* Logic: '<S406>/Logical Operator2' incorporates:
   *  Constant: '<S398>/defval'
   */
  rtb_valid_signal_n4 = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CSVCU1_enum,
     VINP_CANMsgValidFD3VCU1_flg, KINP_CSVCU1_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_cn);

  /* End of Outputs for SubSystem: '<S406>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S406>/override_signal_m2 ' */

  /* Constant: '<S398>/ovrdflg' incorporates:
   *  Constant: '<S398>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_n4,
    KINP_CSVCU1_enum_ovrdflg, KINP_CSVCU1_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S406>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_18' */
  VINP_CSVCU1_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S410>/signal validity checking' */

  /* Logic: '<S410>/Logical Operator2' incorporates:
   *  Constant: '<S399>/defval'
   */
  rtb_valid_signal_b2 = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_PwrSta_enum,
     VINP_CANMsgValidFD3VCU1_flg, KINP_PwrSta_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_mj);

  /* End of Outputs for SubSystem: '<S410>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S410>/override_signal_m2 ' */

  /* Constant: '<S399>/ovrdflg' incorporates:
   *  Constant: '<S399>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_b2,
    KINP_PwrSta_enum_ovrdflg, KINP_PwrSta_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S410>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_19' */
  VINP_PwrSta_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S414>/signal validity checking' */

  /* Logic: '<S414>/Logical Operator2' incorporates:
   *  Constant: '<S400>/defval'
   */
  rtb_valid_signal_ot = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RCVCU1_enum,
     VINP_CANMsgValidFD3VCU1_flg, KINP_RCVCU1_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_mv);

  /* End of Outputs for SubSystem: '<S414>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S414>/override_signal_m2 ' */

  /* Constant: '<S400>/ovrdflg' incorporates:
   *  Constant: '<S400>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_ot,
    KINP_RCVCU1_enum_ovrdflg, KINP_RCVCU1_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S414>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_20' */
  VINP_RCVCU1_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S418>/signal validity checking' */

  /* Logic: '<S418>/Logical Operator2' incorporates:
   *  Constant: '<S401>/defval'
   */
  rtb_valid_signal_i3 = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_ShiftGearPosn_enum,
     VINP_CANMsgValidFD3VCU1_flg, KINP_ShiftGearPosn_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_lm);

  /* End of Outputs for SubSystem: '<S418>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S418>/override_signal_m2 ' */

  /* Constant: '<S401>/ovrdflg' incorporates:
   *  Constant: '<S401>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_i3,
    KINP_ShiftGearPosn_enum_ovrdflg, KINP_ShiftGearPosn_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S418>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_21' */
  VINP_ShiftGearPosn_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S426>/signal validity checking' */

  /* Logic: '<S426>/Logical Operator2' incorporates:
   *  Constant: '<S422>/defval'
   */
  rtb_valid_signal_ch = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CSVCU2CAN1_enum,
     VINP_CANMsgValidFD3VCU2_flg, KINP_CSVCU2CAN1_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_o3);

  /* End of Outputs for SubSystem: '<S426>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S426>/override_signal_m2 ' */

  /* Constant: '<S422>/ovrdflg' incorporates:
   *  Constant: '<S422>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_ch,
    KINP_CSVCU2CAN1_enum_ovrdflg, KINP_CSVCU2CAN1_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S426>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_22' */
  VINP_CSVCU2CAN1_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S430>/signal validity checking' */

  /* Logic: '<S430>/Logical Operator2' incorporates:
   *  Constant: '<S423>/defval'
   */
  rtb_valid_signal_n = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RCVCU2CAN1_enum,
     VINP_CANMsgValidFD3VCU2_flg, KINP_RCVCU2CAN1_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_co);

  /* End of Outputs for SubSystem: '<S430>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S430>/override_signal_m2 ' */

  /* Constant: '<S423>/ovrdflg' incorporates:
   *  Constant: '<S423>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_n,
    KINP_RCVCU2CAN1_enum_ovrdflg, KINP_RCVCU2CAN1_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S430>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_23' */
  VINP_RCVCU2CAN1_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S434>/signal validity checking' */

  /* Logic: '<S434>/Logical Operator2' incorporates:
   *  Constant: '<S424>/defval'
   */
  rtb_valid_signal_pw = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrActvDmpDisabReq_flg,
     VINP_CANMsgValidFD3VCU2_flg, KINP_RrActvDmpDisabReq_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_g);

  /* End of Outputs for SubSystem: '<S434>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S434>/override_signal_m2 ' */

  /* Constant: '<S424>/ovrdflg' incorporates:
   *  Constant: '<S424>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_pw,
    KINP_RrActvDmpDisabReq_flg_ovrdflg, KINP_RrActvDmpDisabReq_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S434>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_24' */
  VINP_RrActvDmpDisabReq_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S438>/signal validity checking' */

  /* Logic: '<S438>/Logical Operator2' incorporates:
   *  Constant: '<S425>/defval'
   */
  rtb_valid_signal_ps = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrMCUEnaReq_flg,
     VINP_CANMsgValidFD3VCU2_flg, KINP_RrMCUEnaReq_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_ff);

  /* End of Outputs for SubSystem: '<S438>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S438>/override_signal_m2 ' */

  /* Constant: '<S425>/ovrdflg' incorporates:
   *  Constant: '<S425>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_ps,
    KINP_RrMCUEnaReq_flg_ovrdflg, KINP_RrMCUEnaReq_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S438>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_25' */
  VINP_RrMCUEnaReq_flg = rtb_Switch1_gv;

  /* Outputs for Atomic SubSystem: '<S449>/signal validity checking' */

  /* Logic: '<S449>/Logical Operator2' incorporates:
   *  Constant: '<S442>/defval'
   */
  rtb_valid_signal_kx = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrSpdMaxReq_rpm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrSpdMaxReq_rpm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_iz);

  /* End of Outputs for SubSystem: '<S449>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S449>/override_signal_m2 ' */

  /* Constant: '<S442>/ovrdflg' incorporates:
   *  Constant: '<S442>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_kx,
    KINP_FDCVCURrSpdMaxReq_rpm_ovrdflg, KINP_FDCVCURrSpdMaxReq_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S449>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_26' */
  VINP_FDCVCURrSpdMaxReq_rpm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S453>/signal validity checking' */

  /* Logic: '<S453>/Logical Operator2' incorporates:
   *  Constant: '<S443>/defval'
   */
  rtb_valid_signal_j3 = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrSpdMinReq_rpm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrSpdMinReq_rpm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_f);

  /* End of Outputs for SubSystem: '<S453>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S453>/override_signal_m2 ' */

  /* Constant: '<S443>/ovrdflg' incorporates:
   *  Constant: '<S443>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_j3,
    KINP_FDCVCURrSpdMinReq_rpm_ovrdflg, KINP_FDCVCURrSpdMinReq_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S453>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_27' */
  VINP_FDCVCURrSpdMinReq_rpm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S457>/signal validity checking' */

  /* Logic: '<S457>/Logical Operator2' incorporates:
   *  Constant: '<S444>/defval'
   */
  rtb_valid_signal_ej = SWC_APP_type_sig_valid_check_i
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMCtrlModeReq_enum,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrTMCtrlModeReq_enum_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_ip);

  /* End of Outputs for SubSystem: '<S457>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S457>/override_signal_m2 ' */

  /* Constant: '<S444>/ovrdflg' incorporates:
   *  Constant: '<S444>/ovrdval'
   */
  rtb_Switch1_ft = SWC_APP_ty_override_signal_m2_p(rtb_valid_signal_ej,
    KINP_FDCVCURrTMCtrlModeReq_enum_ovrdflg,
    KINP_FDCVCURrTMCtrlModeReq_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S457>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_28' */
  VINP_FDCVCURrTMCtrlModeReq_enum = rtb_Switch1_ft;

  /* Outputs for Atomic SubSystem: '<S461>/signal validity checking' */

  /* Logic: '<S461>/Logical Operator2' incorporates:
   *  Constant: '<S445>/defval'
   */
  rtb_valid_signal_krk = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMSpdReq_rpm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrTMSpdReq_rpm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_o2);

  /* End of Outputs for SubSystem: '<S461>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S461>/override_signal_m2 ' */

  /* Constant: '<S445>/ovrdflg' incorporates:
   *  Constant: '<S445>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_krk,
    KINP_FDCVCURrTMSpdReq_rpm_ovrdflg, KINP_FDCVCURrTMSpdReq_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S461>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_29' */
  VINP_FDCVCURrTMSpdReq_rpm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S465>/signal validity checking' */

  /* Logic: '<S465>/Logical Operator2' incorporates:
   *  Constant: '<S446>/defval'
   */
  rtb_valid_signal_nx = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMTqReq_Nm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrTMTqReq_Nm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_oj);

  /* End of Outputs for SubSystem: '<S465>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S465>/override_signal_m2 ' */

  /* Constant: '<S446>/ovrdflg' incorporates:
   *  Constant: '<S446>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_nx,
    KINP_FDCVCURrTMTqReq_Nm_ovrdflg, KINP_FDCVCURrTMTqReq_Nm_ovrdval);

  /* End of Outputs for SubSystem: '<S465>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_30' */
  VINP_FDCVCURrTMTqReq_Nm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S469>/signal validity checking' */

  /* Logic: '<S469>/Logical Operator2' incorporates:
   *  Constant: '<S447>/defval'
   */
  rtb_valid_signal_d = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTqMaxReq_Nm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrTqMaxReq_Nm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_l);

  /* End of Outputs for SubSystem: '<S469>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S469>/override_signal_m2 ' */

  /* Constant: '<S447>/ovrdflg' incorporates:
   *  Constant: '<S447>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_d,
    KINP_FDCVCURrTqMaxReq_Nm_ovrdflg, KINP_FDCVCURrTqMaxReq_Nm_ovrdval);

  /* End of Outputs for SubSystem: '<S469>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_31' */
  VINP_FDCVCURrTqMaxReq_Nm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S473>/signal validity checking' */

  /* Logic: '<S473>/Logical Operator2' incorporates:
   *  Constant: '<S448>/defval'
   */
  rtb_valid_signal_kr = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTqMinReq_Nm,
     VINP_CANMsgValidFD3VCU5_flg, KINP_FDCVCURrTqMinReq_Nm_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_if);

  /* End of Outputs for SubSystem: '<S473>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S473>/override_signal_m2 ' */

  /* Constant: '<S448>/ovrdflg' incorporates:
   *  Constant: '<S448>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_kr,
    KINP_FDCVCURrTqMinReq_Nm_ovrdflg, KINP_FDCVCURrTqMinReq_Nm_ovrdval);

  /* End of Outputs for SubSystem: '<S473>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_32' */
  VINP_FDCVCURrTqMinReq_Nm = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S483>/signal validity checking' */

  /* Logic: '<S483>/Logical Operator2' incorporates:
   *  Constant: '<S477>/defval'
   */
  rtb_valid_signal_i = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeDay_DAY,
     VINP_CANMsgValidGW3CE1000_flg, KINP_IVITimeDay_DAY_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_as);

  /* End of Outputs for SubSystem: '<S483>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S483>/override_signal_m2 ' */

  /* Constant: '<S477>/ovrdflg' incorporates:
   *  Constant: '<S477>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_i,
    KINP_IVITimeDay_DAY_ovrdflg, KINP_IVITimeDay_DAY_ovrdval);

  /* End of Outputs for SubSystem: '<S483>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_33' */
  VINP_IVITimeDay_DAY = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S487>/signal validity checking' */

  /* Logic: '<S487>/Logical Operator2' incorporates:
   *  Constant: '<S478>/defval'
   */
  rtb_valid_signal_o = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeHour_hr,
     VINP_CANMsgValidGW3CE1000_flg, KINP_IVITimeHour_hr_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_ax);

  /* End of Outputs for SubSystem: '<S487>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S487>/override_signal_m2 ' */

  /* Constant: '<S478>/ovrdflg' incorporates:
   *  Constant: '<S478>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_o,
    KINP_IVITimeHour_hr_ovrdflg, KINP_IVITimeHour_hr_ovrdval);

  /* End of Outputs for SubSystem: '<S487>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_34' */
  VINP_IVITimeHour_hr = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S491>/signal validity checking' */

  /* Logic: '<S491>/Logical Operator2' incorporates:
   *  Constant: '<S479>/defval'
   */
  rtb_valid_signal_oy = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeMinute_min,
     VINP_CANMsgValidGW3CE1000_flg, KINP_IVITimeMinute_min_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_e);

  /* End of Outputs for SubSystem: '<S491>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S491>/override_signal_m2 ' */

  /* Constant: '<S479>/ovrdflg' incorporates:
   *  Constant: '<S479>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_oy,
    KINP_IVITimeMinute_min_ovrdflg, KINP_IVITimeMinute_min_ovrdval);

  /* End of Outputs for SubSystem: '<S491>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_35' */
  VINP_IVITimeMinute_min = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S495>/signal validity checking' */

  /* Logic: '<S495>/Logical Operator2' incorporates:
   *  Constant: '<S480>/defval'
   */
  rtb_valid_signal_p = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeMonth_MONTH,
     VINP_CANMsgValidGW3CE1000_flg, KINP_IVITimeMonth_MONTH_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_a);

  /* End of Outputs for SubSystem: '<S495>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S495>/override_signal_m2 ' */

  /* Constant: '<S480>/ovrdflg' incorporates:
   *  Constant: '<S480>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_p,
    KINP_IVITimeMonth_MONTH_ovrdflg, KINP_IVITimeMonth_MONTH_ovrdval);

  /* End of Outputs for SubSystem: '<S495>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_36' */
  VINP_IVITimeMonth_MONTH = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S499>/signal validity checking' */

  /* Logic: '<S499>/Logical Operator2' incorporates:
   *  Constant: '<S481>/defval'
   */
  rtb_valid_signal_k = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeSecond_s,
     VINP_CANMsgValidGW3CE1000_flg, KINP_IVITimeSecond_s_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_p5);

  /* End of Outputs for SubSystem: '<S499>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S499>/override_signal_m2 ' */

  /* Constant: '<S481>/ovrdflg' incorporates:
   *  Constant: '<S481>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_k,
    KINP_IVITimeSecond_s_ovrdflg, KINP_IVITimeSecond_s_ovrdval);

  /* End of Outputs for SubSystem: '<S499>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_37' */
  VINP_IVITimeSecond_s = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S503>/signal validity checking' */

  /* Logic: '<S503>/Logical Operator2' incorporates:
   *  Constant: '<S482>/defval'
   */
  rtb_valid_signal_km = SWC_APP_type_sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_VehSpeed_kph,
     VINP_CANMsgValidGW3CE1000_flg, KINP_VehSpeed_kph_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditychecki_p);

  /* End of Outputs for SubSystem: '<S503>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S503>/override_signal_m2 ' */

  /* Constant: '<S482>/ovrdflg' incorporates:
   *  Constant: '<S482>/ovrdval'
   */
  rtb_Switch1 = SWC_APP_ty_override_signal_m2_m(rtb_valid_signal_km,
    KINP_VehSpeed_kph_ovrdflg, KINP_VehSpeed_kph_ovrdval);

  /* End of Outputs for SubSystem: '<S503>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_38' */
  VINP_VehSpeed_kph = rtb_Switch1;

  /* Outputs for Atomic SubSystem: '<S359>/signal validity checking' */

  /* Logic: '<S359>/Logical Operator2' incorporates:
   *  Constant: '<S353>/defval'
   */
  rtb_valid_signal_l = sig_valid_check
    (SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS1RCErr_flg,
     VINP_CANMsgValidBMS1_flg, KINP_BMS1RCErr_flg_defval,
     &SWC_APP_type_ARID_DEF.ARID_DEF_signalvaliditycheck_mc);

  /* End of Outputs for SubSystem: '<S359>/signal validity checking' */

  /* Outputs for Atomic SubSystem: '<S359>/override_signal_m2 ' */

  /* Constant: '<S353>/ovrdflg' incorporates:
   *  Constant: '<S353>/ovrdval'
   */
  rtb_Switch1_gv = SWC_APP_type_override_signal_m2(rtb_valid_signal_l,
    KINP_BMS1RCErr_flg_ovrdflg, KINP_BMS1RCErr_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S359>/override_signal_m2 ' */

  /* DataTypeConversion: '<S315>/UnitConverter_9' */
  VINP_BMS1RCErr_flg = rtb_Switch1_gv;

  /* BusCreator: '<S315>/bus_creator' */
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidBMS1_flg =
    VINP_CANMsgValidBMS1_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidBMS6_flg =
    VINP_CANMsgValidBMS6_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidFD3C1000_flg =
    VINP_CANMsgValidFD3C1000_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidFD3VCU1_flg =
    VINP_CANMsgValidFD3VCU1_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidFD3VCU2_flg =
    VINP_CANMsgValidFD3VCU2_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidFD3VCU5_flg =
    VINP_CANMsgValidFD3VCU5_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CANMsgValidGW3CE1000_flg =
    VINP_CANMsgValidGW3CE1000_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_BMS1CSErr_flg = VINP_BMS1CSErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_BMS1RCErr_flg = VINP_BMS1RCErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_HVBattVolt_V = VINP_HVBattVolt_V;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_BMS6CSErr_flg = VINP_BMS6CSErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_BMS6RCErr_flg = VINP_BMS6RCErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_HVBContactorSta_flg =
    VINP_HVBContactorSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_BatteryMode_enum =
    VINP_BatteryMode_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RrCoolantflow_Lpmin =
    VINP_RrCoolantflow_Lpmin;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RrCoolanttemp_C = VINP_RrCoolanttemp_C;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_ActiveDischReq_flg =
    VINP_ActiveDischReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CSVCU1_enum = VINP_CSVCU1_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_PwrSta_enum = VINP_PwrSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RCVCU1_enum = VINP_RCVCU1_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum =
    VINP_ShiftGearPosn_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_CSVCU2CAN1_enum = VINP_CSVCU2CAN1_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RCVCU2CAN1_enum = VINP_RCVCU2CAN1_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RrActvDmpDisabReq_flg =
    VINP_RrActvDmpDisabReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg = VINP_RrMCUEnaReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrSpdMaxReq_rpm =
    VINP_FDCVCURrSpdMaxReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrSpdMinReq_rpm =
    VINP_FDCVCURrSpdMinReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum =
    VINP_FDCVCURrTMCtrlModeReq_enum;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMSpdReq_rpm =
    VINP_FDCVCURrTMSpdReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMTqReq_Nm =
    VINP_FDCVCURrTMTqReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTqMaxReq_Nm =
    VINP_FDCVCURrTqMaxReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTqMinReq_Nm =
    VINP_FDCVCURrTqMinReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_IVITimeDay_DAY = VINP_IVITimeDay_DAY;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_IVITimeHour_hr = VINP_IVITimeHour_hr;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_IVITimeMinute_min =
    VINP_IVITimeMinute_min;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_IVITimeMonth_MONTH =
    VINP_IVITimeMonth_MONTH;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_IVITimeSecond_s = VINP_IVITimeSecond_s;
  SWC_APP_type_ARID_DEF.bus_creator.VINP_VehSpeed_kph = VINP_VehSpeed_kph;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
