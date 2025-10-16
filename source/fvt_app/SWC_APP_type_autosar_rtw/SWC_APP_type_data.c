/*
 * File: SWC_APP_type_data.c
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

#include "SWC_APP_type.h"

/* Invariant block signals (default storage) */
const ConstB_SWC_APP_type_T SWC_APP_type_ConstB = {
  1.0,                                 /* '<S148>/Saturation' */
  1.0,                                 /* '<S166>/Saturation' */
  0.0F,                                /* '<S27>/Abs1' */
  0.0F,                                /* '<S28>/Abs1' */
  0.0100000007F,                       /* '<S143>/Gain1' */
  0.0150000006F,                       /* '<S143>/Gain' */
  0.1F,                                /* '<S161>/Gain1' */
  0.15F,                               /* '<S161>/Gain' */
  0.5F,                                /* '<S913>/Gain1' */
  0.5F,                                /* '<S882>/Gain1' */
  0.5F,                                /* '<S854>/Gain1' */
  0.5F,                                /* '<S749>/Gain1' */
  0.5F,                                /* '<S721>/Gain1' */
  0.5F,                                /* '<S105>/Gain1' */
  0.5F,                                /* '<S80>/Gain1' */
  0.5F,                                /* '<S55>/Gain1' */
  3,                                   /* '<S5>/Data Type Conversion20' */
  5,                                   /* '<S5>/Data Type Conversion22' */
  2,                                   /* '<S5>/Data Type Conversion12' */
  4,                                   /* '<S5>/Data Type Conversion13' */
  1,                                   /* '<S5>/Data Type Conversion15' */
  0,                                   /* '<S5>/Data Type Conversion9' */
  2,                                   /* '<S5>/Data Type Conversion10' */
  4,                                   /* '<S5>/Data Type Conversion11' */
  3,                                   /* '<S5>/Data Type Conversion16' */
  5,                                   /* '<S5>/Data Type Conversion24' */
  0,                                   /* '<S5>/Data Type Conversion29' */
  1,                                   /* '<S5>/Data Type Conversion19' */
  GateDriverPos_vLS,                   /* '<S5>/Data Type Conversion21' */
  GateDriverPos_wLS,                   /* '<S5>/Data Type Conversion23' */
  GateDriverPos_vHS,                   /* '<S5>/Data Type Conversion27' */
  GateDriverPos_wHS,                   /* '<S5>/Data Type Conversion28' */
  GateDriverPos_uLS,                   /* '<S5>/Data Type Conversion14' */
  GateDriverPos_uHS,                   /* '<S5>/Data Type Conversion6' */
  GateDriverPos_vHS,                   /* '<S5>/Data Type Conversion7' */
  GateDriverPos_wHS,                   /* '<S5>/Data Type Conversion8' */
  GateDriverPos_vLS,                   /* '<S5>/Data Type Conversion17' */
  GateDriverPos_wLS,                   /* '<S5>/Data Type Conversion25' */
  GateDriverPos_uHS,                   /* '<S5>/Data Type Conversion26' */
  GateDriverPos_uLS,                   /* '<S5>/Data Type Conversion18' */
  1U,                                  /* '<S145>/Data Type Conversion' */
  5U,                                  /* '<S145>/Max' */
  2U,                                  /* '<S145>/Divide' */
  1U,                                  /* '<S163>/Data Type Conversion' */
  5U,                                  /* '<S163>/Max' */
  20U,                                 /* '<S163>/Divide' */
  true_MatlabRTW,                      /* '<S27>/Relational Operator' */
  false_MatlabRTW,                     /* '<S27>/Logical Operator5' */
  true_MatlabRTW,                      /* '<S28>/Relational Operator' */
  false_MatlabRTW,                     /* '<S28>/Logical Operator5' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator1' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator12' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator14' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator16' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator17' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator19' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator21' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator23' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator25' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator27' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator29' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator3' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator31' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator33' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator5' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator7' */
  false_MatlabRTW,                     /* '<S706>/Logical Operator9' */

  /* Start of '<S7>/CAN3' */
  {
    40.0F,                             /* '<S262>/Add' */
    1.0F,                              /* '<S262>/MinMax' */
    40.0F,                             /* '<S262>/Divide' */
    0.1F,                              /* '<S263>/MinMax' */
    1022.0F,                           /* '<S264>/Add' */
    0.1F,                              /* '<S264>/MinMax' */
    10220.0F,                          /* '<S264>/Divide' */
    1022.0F,                           /* '<S265>/Add' */
    1.0F,                              /* '<S265>/MinMax' */
    1022.0F,                           /* '<S265>/Divide' */
    0.0F,                              /* '<S266>/Add' */
    0.1F,                              /* '<S266>/MinMax' */
    0.0F,                              /* '<S266>/Divide' */
    0.1F,                              /* '<S267>/MinMax' */
    0.1F,                              /* '<S268>/MinMax' */
    40.0F,                             /* '<S269>/Add' */
    1.0F,                              /* '<S269>/MinMax' */
    40.0F,                             /* '<S269>/Divide' */
    1.0F,                              /* '<S270>/MinMax' */
    18000.0F,                          /* '<S271>/Add' */
    1.0F,                              /* '<S271>/MinMax' */
    18000.0F,                          /* '<S271>/Divide' */
    40.0F,                             /* '<S272>/Add' */
    1.0F,                              /* '<S272>/MinMax' */
    40.0F,                             /* '<S272>/Divide' */
    0.1F,                              /* '<S273>/MinMax' */
    0.1F,                              /* '<S274>/MinMax' */
    40.0F,                             /* '<S291>/Add' */
    1.0F,                              /* '<S291>/MinMax' */
    40.0F,                             /* '<S291>/Divide' */
    40.0F,                             /* '<S292>/Add' */
    1.0F,                              /* '<S292>/MinMax' */
    40.0F,                             /* '<S292>/Divide' */
    0.25F,                             /* '<S293>/MinMax' */
    1022.0F,                           /* '<S303>/Add' */
    0.1F,                              /* '<S303>/MinMax' */
    10220.0F,                          /* '<S303>/Divide' */
    0.2F,                              /* '<S304>/MinMax' */
    1.0F,                              /* '<S305>/MinMax' */
    1.0F,                              /* '<S306>/MinMax' */
    40U,                               /* '<S233>/Data Type Conversion' */
    10220U,                            /* '<S239>/Data Type Conversion' */
    1022U,                             /* '<S241>/Data Type Conversion' */
    40U,                               /* '<S254>/Data Type Conversion' */
    18000U,                            /* '<S258>/Data Type Conversion' */
    40U,                               /* '<S259>/Data Type Conversion' */
    40U,                               /* '<S278>/Data Type Conversion' */
    40U,                               /* '<S283>/Data Type Conversion' */
    2U,                                /* '<S287>/Data Type Conversion' */
    2U,                                /* '<S288>/Data Type Conversion' */
    10220U,                            /* '<S295>/Data Type Conversion' */
    0U                                 /* '<S244>/Data Type Conversion' */
  }
  /* End of '<S7>/CAN3' */
};

/* Constant parameters (default storage) */
const ConstP_SWC_APP_type_T SWC_APP_type_ConstP = {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S27>/696MTPAIdGen'
   *   '<S27>/696MTPAIdMot'
   *   '<S28>/530MTPAIdGen'
   *   '<S28>/530MTPAIdMot'
   */
  { 50U, 19U },

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S126>/EopC_nRrOilTempDetOptMod_M'
   *   '<S128>/EopC_nRrOilTempMotOptMod_M'
   *   '<S131>/EopC_nRrOilTemp_M'
   */
  { 9U, 8U },

  /* Computed Parameter: LLCM_volCoolFlowWater_M_maxInde
   * Referenced by: '<S590>/LLCM_volCoolFlowWater_M'
   */
  { 3U, 3U },

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S702>/TrqMax'
   *   '<S702>/TrqMin'
   */
  { 20U, 4U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
