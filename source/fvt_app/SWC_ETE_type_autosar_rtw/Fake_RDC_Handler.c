/*
 * File: Fake_RDC_Handler.c
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

#include "Fake_RDC_Handler.h"
#include "rtwtypes.h"

/* Includes for objects with custom storage classes */
#include "SWC_ETE_type.h"

/* Output and update for enable system: '<S15>/Fake_RDC_Handler' */
void SWC_ETE_type_Fake_RDC_Handler(void)
{
  /* Outputs for Enabled SubSystem: '<S15>/Fake_RDC_Handler' incorporates:
   *  EnablePort: '<S262>/Enable'
   */
  if (SWC_ETE_type_ARID_DEF.Equal3) {
    /* Sum: '<S262>/Add' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Gain: '<S262>/Gain'
     *  Gain: '<S262>/Gain1'
     *  UnitDelay: '<S262>/Unit Delay1'
     */
    VFOC_FakeRotorPosn_rad += 0.104719758F * KFOC_SpdCmd_RPM * 0.0001F;

    /* Switch: '<S262>/Switch' incorporates:
     *  Constant: '<S262>/Constant2'
     */
    if (VFOC_FakeRotorPosn_rad > 6.28318548F) {
      VFOC_FakeRotorPosn_rad = 0.0F;
    }

    /* End of Switch: '<S262>/Switch' */
  }

  /* End of Outputs for SubSystem: '<S15>/Fake_RDC_Handler' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
