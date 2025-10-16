/*
 * File: HCU_LIB.h
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

#ifndef HCU_LIB_h_
#define HCU_LIB_h_
#ifndef SWC_APP_type_COMMON_INCLUDES_
#define SWC_APP_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_APP_type.h"
#endif                                 /* SWC_APP_type_COMMON_INCLUDES_ */

/* PublicStructure Variables for Internal Data, for system '<S355>/signal validity checking' */
typedef struct {
  boolean UnitDelay_DSTATE;            /* '<S358>/UnitDelay' */
} ARID_DEF_sig_valid_check_T;

/* PublicStructure Variables for Internal Data, for system '<S363>/signal validity checking' */
typedef struct {
  float32 UnitDelay_DSTATE;            /* '<S366>/UnitDelay' */
} ARID_DEF_sig_valid_check_j_T;

/* PublicStructure Variables for Internal Data, for system '<S385>/signal validity checking' */
typedef struct {
  uint8 UnitDelay_DSTATE;              /* '<S388>/UnitDelay' */
} ARID_DEF_sig_valid_check_k_T;

extern boolean SWC_APP_type_override_signal_m2(boolean rtu_signal_raw, boolean
  rtu_cal_ovrdflg, boolean rtu_cal_ovrdval);
extern boolean sig_valid_check(boolean rtu_new_signal, boolean
  rtu_new_signal_valid_flg, boolean rtu_def_value, ARID_DEF_sig_valid_check_T
  *SWC_APP_type__ARID_DEF_arg);
extern float32 SWC_APP_ty_override_signal_m2_m(float32 rtu_signal_raw, boolean
  rtu_cal_ovrdflg, float32 rtu_cal_ovrdval);
extern float32 SWC_APP_type_sig_valid_check(float32 rtu_new_signal, boolean
  rtu_new_signal_valid_flg, float32 rtu_def_value, ARID_DEF_sig_valid_check_j_T *
  SWC_APP_type__ARID_DEF_arg);
extern uint8 SWC_APP_ty_override_signal_m2_p(uint8 rtu_signal_raw, boolean
  rtu_cal_ovrdflg, uint8 rtu_cal_ovrdval);
extern uint8 SWC_APP_type_sig_valid_check_i(uint8 rtu_new_signal, boolean
  rtu_new_signal_valid_flg, uint8 rtu_def_value, ARID_DEF_sig_valid_check_k_T
  *SWC_APP_type__ARID_DEF_arg);

#endif                                 /* HCU_LIB_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
