/*
 * File: MTPA_FOC.h
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

#ifndef MTPA_FOC_h_
#define MTPA_FOC_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

/* PublicStructure Variables for Internal Data, for system '<S115>/debounce' */
typedef struct {
  sint16 UnitDelay1_DSTATE;            /* '<S121>/Unit Delay1' */
  boolean UnitDelay_DSTATE;            /* '<S121>/Unit Delay' */
} ARID_DEF_debounce_SWC_ETE_typ_T;

extern void SWC_ETE_type_debounce_Init(boolean *rty_Status);
extern void SWC_ETE_type_debounce(boolean rtu_error_state, sint16 rtu_heal_max,
  sint16 rtu_error_max, boolean *rty_Status, ARID_DEF_debounce_SWC_ETE_typ_T
  *SWC_ETE_type__ARID_DEF_arg);
extern void SWC_ETE_type_Enable_GateIC(boolean rtu_Enable);
extern void CurrentSensor_Init(void);
extern void CurrentSensor(void);
extern void SWC_ETE_type_MTPA_FOC_Init(void);
extern void SWC_ETE_type_MTPA_FOC(void);

#endif                                 /* MTPA_FOC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
