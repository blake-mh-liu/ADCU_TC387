/*
 * File: PDC.h
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

#ifndef PDC_h_
#define PDC_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

/* Invariant block signals for system '<S190>/SetSVMR_SmartClamps_PhsA' */
typedef struct {
  const boolean RelationalOperator1;   /* '<S197>/Relational Operator1' */
} ConstB_SetSVMR_SmartClamps_Ph_T;

extern void SetSVMR_DeadTimeCompensation_Ph(float32 rtu_LeSVMC_I_Lis, float32
  rtu_LeSVMC_Pct_p_Duty_in, float32 rtu_VaSVMR_K_DeadTimeCmp_Slope, float32
  rtu_VaSVMR_Pct_DeadTimeCmp, float32 *rty_LeSVMC_Pct_p_Duty);
extern void SWC_ET_SetSVMR_SmartClamps_PhsA(float32 rtu_LeSVMC_Pct_DC_Duty_in,
  float32 rtu_VeSVMR_Pct_DC_FixedDutyOffs, float32 rtu_VaSVMR_Pct_DCMaxDuty_nom,
  float32 rtu_VaSVMR_Pct_DCMinDuty_nom, float32 rtu_VaSVMR_Pct_DCMaxDutyRound,
  float32 rtu_VaSVMR_Pct_DCMinDutyRound, float32 *rty_LeSVMC_Pct_DC_Duty, const
  ConstB_SetSVMR_SmartClamps_Ph_T *localC);
extern void SWC_ETE_type_PDC_Init(void);
extern void SWC_ETE_type_PDC(void);

#endif                                 /* PDC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
