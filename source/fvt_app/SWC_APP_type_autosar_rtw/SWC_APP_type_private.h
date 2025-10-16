/*
 * File: SWC_APP_type_private.h
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

#ifndef SWC_APP_type_private_h_
#define SWC_APP_type_private_h_
#include "rtwtypes.h"
#include "SWC_APP_type.h"
#include "Rte_Type.h"
#include "SWC_APP_type_types.h"

extern void SWC_APP_type_Delay_Update(boolean rtu_u,
  ARID_DEF_Delay_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg);
extern boolean SWC_APP_type_Delay(ARID_DEF_Delay_SWC_APP_type_T
  *SWC_APP_type__ARID_DEF_arg);
extern void SWC_APP_type_ER_FF(boolean rtu_E1_T, boolean rtu_R2_F, boolean
  *rty_y, ARID_DEF_ER_FF_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg);
extern void SWC_APP_type_Delay_p_Update(float32 rtu_u,
  ARID_DEF_Delay_SWC_APP_type_f_T *SWC_APP_type__ARID_DEF_arg);
extern float32 SWC_APP_type_Delay_m(ARID_DEF_Delay_SWC_APP_type_f_T
  *SWC_APP_type__ARID_DEF_arg);
extern boolean SWC_APP_type_Delay_d(boolean rtu_u,
  ARID_DEF_Delay_SWC_APP_type_h_T *SWC_APP_type__ARID_DEF_arg);
extern boolean SWC_APP_type_Falling(boolean rtu_In1,
  ARID_DEF_Falling_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg);
extern boolean SWC_APP_type_Rising(boolean rtu_In1,
  ARID_DEF_Rising_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg);
extern void SWC_APP_type_Subsystem(boolean rtu_Enable, uint8 rtu_RC, uint8
  rtu_RC_delay, boolean *rty_RCErr);
extern void SWC_APP_type_CAN_MCU_R1(boolean rtu_BOUTP_outputs, float32
  rtu_BOUTP_outputs_h, DT_CAN_MCU_R1_SG_MCU_FVT_R_Local1
  *rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_);
extern void SWC_APP_type_CAN3(float32 rtu_BOUTP_outputs, float32
  rtu_BOUTP_outputs_f, float32 rtu_BOUTP_outputs_g, boolean rtu_BOUTP_outputs_fu,
  boolean rtu_BOUTP_outputs_p, float32 rtu_BOUTP_outputs_m, float32
  rtu_BOUTP_outputs_k, float32 rtu_BOUTP_outputs_i, float32 rtu_BOUTP_outputs_i4,
  uint8 rtu_BOUTP_outputs_i0, float32 rtu_BOUTP_outputs_c, boolean
  rtu_BOUTP_outputs_j, float32 rtu_BOUTP_outputs_f2, float32
  rtu_BOUTP_outputs_cs, float32 rtu_BOUTP_outputs_ke, uint8 rtu_BOUTP_outputs_g1,
  DT_CAN3_SG_MCU_B_R1 *rty_DT_CAN3_SG_MCU_B_R1, DT_CAN3_SG_MCU_B_R2
  *rty_DT_CAN3_SG_MCU_B_R2, DT_CAN3_SG_MCU_FVT_R1 *rty_DT_CAN3_SG_MCU_FVT_R1,
  const ConstB_CAN3_SWC_APP_type_T *localC);
extern void SWC_APP_type_RE_FF(boolean rtu_R1_F, boolean rtu_E2_T, boolean
  *rty_y, ARID_DEF_RE_FF_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg);
extern void SWC_APP_type_Chart_Init(sint16 *rty_Count, boolean *rty_Status);
extern void SWC_APP_type_Chart(sint16 rtu_Count_Pre, boolean rtu_State, sint16
  rtu_Heal_Max, sint16 rtu_Error_Max, boolean rtu_Status_Pre, sint16 *rty_Count,
  boolean *rty_Status);
extern void SWC_APP_type_debounce_Init(boolean *rty_Status);
extern void SWC_APP_type_debounce(boolean rtu_error_state, sint16 rtu_heal_max,
  sint16 rtu_error_max, boolean *rty_Status, ARID_DEF_debounce_SWC_APP_typ_T
  *SWC_APP_type__ARID_DEF_arg);
extern void CoefSmooth_Init(float32 *rty_OutputCoef);
extern void CoefSmooth(float32 rtu_InputCoef, float32 rtu_DepStep, float32
  rtu_AddStep, float32 *rty_OutputCoef);
extern float32 Derating_Forward(float32 rtu_InputVal, float32 rtu_StartVal,
  float32 rtu_Width, float32 rtu_EndVal, ARID_DEF_Derating_Forward_T
  *SWC_APP_type__ARID_DEF_arg);
extern void Derating_Reverse_Init(float32 *rty_Coef);
extern void Derating_Reverse(float32 rtu_f32_Input_T, float32 rtu_f32_StartP,
  float32 rtu_f32_Delta, float32 rtu_f32_EndP, float32 *rty_Coef,
  ARID_DEF_Derating_Reverse_T *SWC_APP_type__ARID_DEF_arg);
extern void SWC_APP_type_debounce_m_Init(boolean *rty_Status);
extern boolean SWC_APP_type_debounce_c(boolean rtu_error_state, sint16
  rtu_heal_max, sint16 rtu_error_max, ARID_DEF_debounce_SWC_APP_t_j_T
  *SWC_APP_type__ARID_DEF_arg);
extern float32 Abs(float32 rtu_In1);
extern void Coef_Decrease_Increase_Init(float32 *rty_OutputCoef,
  ARID_DEF_Coef_Decrease_Increa_T *SWC_APP_type__ARID_DEF_arg);
extern float32 Coef_Decrease_Increase(boolean rtu_Input_Flg, float32 rtu_AddStep,
  float32 rtu_SubStep, ARID_DEF_Coef_Decrease_Increa_T
  *SWC_APP_type__ARID_DEF_arg);
extern void Hysteresis_Ctrl_Forward_Init(boolean *rty_enable);
extern void Hysteresis_Ctrl_Forward(float32 rtu_Input, float32 rtu_EnterPoint,
  float32 rtu_Hys_Band, boolean *rty_enable);

#endif                                 /* SWC_APP_type_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
