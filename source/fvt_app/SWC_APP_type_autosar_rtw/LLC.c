/*
 * File: LLC.c
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

#include "LLC.h"
#include <math.h>
#include "rtwtypes.h"
#include "look1_iflf_binlcapw.h"
#include "look2_iflf_binlcapw.h"

/* Includes for objects with custom storage classes */
#include "SWC_APP_type.h"

/* Output and update for atomic system: '<S2>/LLC' */
void SWC_APP_type_LLC(void)
{
  float32 rtb_Add1;
  float32 rtb_deltafalllimit;

  /* Sum: '<S590>/Add1' incorporates:
   *  DataTypeConversion: '<S933>/Data Type Conversion20'
   *  Lookup_n-D: '<S590>/LLCM_volCoolFlowOil_M'
   *  Lookup_n-D: '<S590>/LLCM_volCoolFlowWater_M'
   *  Lookup_n-D: '<S590>/LLCM_volfCooltFlow_M'
   *  MinMax: '<S590>/MinMax'
   *  Product: '<S17>/Product2'
   *  Sum: '<S590>/Add2'
   *  Switch: '<S592>/SWT'
   *  Switch: '<S593>/SWT'
   *  Switch: '<S594>/SWT'
   */
  rtb_Add1 = ((look1_iflf_binlcapw(fmaxf(fmaxf(VFOC_ADCSicUTemp_degC,
    VFOC_ADCSicVTemp_degC), VFOC_ADCSicWTemp_degC), &ALLC_volfCooltFlow_X_degC[0],
    &MLLC_volfCooltFlow_Y_T[0], 3U) + look2_iflf_binlcapw
               (SWC_APP_type_ARID_DEF.bus_creator.VINP_RrCoolanttemp_C,
                VCRM_PwrEleAct_W, &ALLC_volCoolFlowWater_Y_degC[0],
                &ALLC_volCoolFlowWater_X_kW[0], &MLLC_volCoolFlowWater_Z_M[0],
                SWC_APP_type_ConstP.LLCM_volCoolFlowWater_M_maxInde, 4U)) +
              look1_iflf_binlcapw(VFOC_ADCOilTemp_degC,
    &ALLC_volCoolFlowOil_X_degC[0], &MLLC_volCoolFlowOil_Y_T[0], 3U)) +
    SWC_APP_type_ARID_DEF.bus_creator.VINP_RrCoolantflow_Lpmin;

  /* Switch: '<S595>/Switch2' incorporates:
   *  Constant: '<S590>/Constant4'
   *  Constant: '<S590>/Constant5'
   *  RelationalOperator: '<S595>/LowerRelop1'
   *  RelationalOperator: '<S595>/UpperRelop'
   *  Switch: '<S595>/Switch'
   */
  if (rtb_Add1 > LLCM_volfcooltFlowMax_C) {
    rtb_Add1 = LLCM_volfcooltFlowMax_C;
  } else if (rtb_Add1 < LLCM_volfcooltFlowMin_C) {
    /* Switch: '<S595>/Switch' incorporates:
     *  Constant: '<S590>/Constant5'
     */
    rtb_Add1 = LLCM_volfcooltFlowMin_C;
  }

  /* Sum: '<S591>/Difference Inputs1' incorporates:
   *  Switch: '<S595>/Switch2'
   *  UnitDelay: '<S591>/Delay Input2'
   *
   * Block description for '<S591>/Difference Inputs1':
   *
   *  Add in CPU
   *
   * Block description for '<S591>/Delay Input2':
   *
   *  Store in Global RAM
   */
  rtb_Add1 -= SWC_APP_type_ARID_DEF.DelayInput2_DSTATE;

  /* Switch: '<S596>/Switch2' incorporates:
   *  Constant: '<S590>/MPS_ReqMotSpdMor6'
   *  Product: '<S591>/delta rise limit'
   *  SampleTimeMath: '<S591>/sample time'
   *
   * About '<S591>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_deltafalllimit = LLCM_volfcooltFlowRampUp_C * 0.001F;

  /* Switch: '<S596>/Switch2' incorporates:
   *  RelationalOperator: '<S596>/LowerRelop1'
   */
  if (rtb_Add1 <= rtb_deltafalllimit) {
    /* Product: '<S591>/delta fall limit' incorporates:
     *  Constant: '<S590>/MPS_ReqMotSpdMor9'
     *  SampleTimeMath: '<S591>/sample time'
     *
     * About '<S591>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_deltafalllimit = LLCM_volfcooltFlowRampDown_C * 0.001F;

    /* Switch: '<S596>/Switch' incorporates:
     *  RelationalOperator: '<S596>/UpperRelop'
     */
    if (rtb_Add1 >= rtb_deltafalllimit) {
      /* Switch: '<S596>/Switch2' */
      rtb_deltafalllimit = rtb_Add1;
    }

    /* End of Switch: '<S596>/Switch' */
  }

  /* End of Switch: '<S596>/Switch2' */

  /* Sum: '<S591>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S591>/Delay Input2'
   *
   * Block description for '<S591>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S591>/Delay Input2':
   *
   *  Store in Global RAM
   */
  SWC_APP_type_ARID_DEF.DelayInput2_DSTATE += rtb_deltafalllimit;

  /* Switch: '<S590>/Switch4' incorporates:
   *  Constant: '<S590>/MPS_ReqMotSpdMor1'
   */
  if (LLCM_bTcooltFlowTrig_C) {
    /* Switch: '<S590>/Switch4' incorporates:
     *  Constant: '<S590>/MPS_ReqMotSpdMor2'
     */
    VLLC_volfCooltFlowTar_C = LLCM_volfcooltFlowMor_C;
  } else {
    /* Switch: '<S590>/Switch4' */
    VLLC_volfCooltFlowTar_C = SWC_APP_type_ARID_DEF.DelayInput2_DSTATE;
  }

  /* End of Switch: '<S590>/Switch4' */

  /* BusCreator: '<S9>/Bus Creator' */
  SWC_APP_type_ARID_DEF.BusCreator.VLLC_volfCooltFlowTar_C =
    VLLC_volfCooltFlowTar_C;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
