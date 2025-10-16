/*
 * File: intrp2d_fu32fl_pw.c
 *
 * Code generated for Simulink model 'SWC_APP_type'.
 *
 * Model version                  : 1.119
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Sep 24 14:15:55 2025
 */

#include "intrp2d_fu32fl_pw.h"
#include "rtwtypes.h"

float32 intrp2d_fu32fl_pw(const uint32 bpIndex[], const float32 frac[], const
  float32 table[], const uint32 stride)
{
  float32 yL_0d0;
  float32 yL_0d1;
  uint32 offset_1d;

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  offset_1d = bpIndex[1U] * stride + bpIndex[0U];
  yL_0d0 = table[offset_1d];
  yL_0d0 += (table[offset_1d + 1U] - yL_0d0) * frac[0U];
  offset_1d += stride;
  yL_0d1 = table[offset_1d];
  return (((table[offset_1d + 1U] - yL_0d1) * frac[0U] + yL_0d1) - yL_0d0) *
    frac[1U] + yL_0d0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
