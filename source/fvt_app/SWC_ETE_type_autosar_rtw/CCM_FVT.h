/*
 * File: CCM_FVT.h
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

#ifndef CCM_FVT_h_
#define CCM_FVT_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

/* PublicStructure Variables for Internal Data, for system '<S71>/Delay' */
typedef struct {
  boolean UnitDelay_DSTATE;            /* '<S84>/UnitDelay' */
} ARID_DEF_Delay_SWC_ETE_type_c_T;

/* PublicStructure Variables for Internal Data, for system '<S58>/Rising' */
typedef struct {
  ARID_DEF_Delay_SWC_ETE_type_c_T ARID_DEF_Delay;/* '<S73>/Delay' */
} ARID_DEF_Rising_SWC_ETE_type_T;

extern void SWC_ETE_type_Delay_c(boolean rtu_u, boolean *rty_y,
  ARID_DEF_Delay_SWC_ETE_type_c_T *SWC_ETE_type__ARID_DEF_arg);
extern void SWC_ETE_type_Rising(boolean rtu_In1, boolean *rty_Out1,
  ARID_DEF_Rising_SWC_ETE_type_T *SWC_ETE_type__ARID_DEF_arg);
extern void SWC_ETE_type_CCM_FVT(void);

#endif                                 /* CCM_FVT_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
