/*
 * File: SWC_APP_type_types.h
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

#ifndef SWC_APP_type_types_h_
#define SWC_APP_type_types_h_
#include "Rte_Type.h"
#include "rtwtypes.h"
#include "FVTMC_API.h"
#ifndef DEFINED_TYPEDEF_FOR_BEOP_outputs_
#define DEFINED_TYPEDEF_FOR_BEOP_outputs_

typedef struct {
  boolean VEOP_bMotEnaReq_flg;
  float32 VEOP_nEOPSpdReq_rpm;
} BEOP_outputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BHAL_CAN3_outputs_
#define DEFINED_TYPEDEF_FOR_BHAL_CAN3_outputs_

typedef struct {
  boolean VHAL_CANMsgInvalidBMS1_flg;
  boolean VHAL_BMS1CSErr_flg;
  boolean VHAL_BMS1RCErr_flg;
  float32 VHAL_HVBattVolt_V;
  boolean VHAL_CANMsgInvalidBMS6_flg;
  boolean VHAL_BMS6CSErr_flg;
  boolean VHAL_BMS6RCErr_flg;
  boolean VHAL_HVBContactorSta_flg;
  boolean VHAL_CANMsgInvalidFD3C1000_flg;
  uint8 VHAL_BatteryMode_enum;
  float32 VHAL_RrCoolantflow_Lpmin;
  float32 VHAL_RrCoolanttemp_C;
  boolean VHAL_CANMsgInvalidFD3VCU1_flg;
  boolean VHAL_ActiveDischReq_flg;
  uint8 VHAL_CSVCU1_enum;
  uint8 VHAL_PwrSta_enum;
  uint8 VHAL_RCVCU1_enum;
  uint8 VHAL_ShiftGearPosn_enum;
  boolean VHAL_CANMsgInvalidFD3VCU2_flg;
  uint8 VHAL_CSVCU2CAN1_enum;
  uint8 VHAL_RCVCU2CAN1_enum;
  boolean VHAL_RrActvDmpDisabReq_flg;
  boolean VHAL_RrMCUEnaReq_flg;
  boolean VHAL_CANMsgInvalidFD3VCU5_flg;
  float32 VHAL_FDCVCURrSpdMaxReq_rpm;
  float32 VHAL_FDCVCURrSpdMinReq_rpm;
  uint8 VHAL_FDCVCURrTMCtrlModeReq_enum;
  float32 VHAL_FDCVCURrTMSpdReq_rpm;
  float32 VHAL_FDCVCURrTMTqReq_Nm;
  float32 VHAL_FDCVCURrTqMaxReq_Nm;
  float32 VHAL_FDCVCURrTqMinReq_Nm;
  boolean VHAL_CANMsgInvalidGW3CE1000_flg;
  float32 VHAL_IVITimeDay_DAY;
  float32 VHAL_IVITimeHour_hr;
  float32 VHAL_IVITimeMinute_min;
  float32 VHAL_IVITimeMonth_MONTH;
  float32 VHAL_IVITimeSecond_s;
  float32 VHAL_VehSpeed_kph;
} BHAL_CAN3_outputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BHAL_CAN_MCU_R1_outputs_
#define DEFINED_TYPEDEF_FOR_BHAL_CAN_MCU_R1_outputs_

typedef struct {
  boolean VHAL_CANMsgInvalidEOPFVTRLocal1_flg;
  float32 VHAL_EOPFVTRActualSpdSta_rpm;
  boolean VHAL_EOPFVTRCSInvalidSta_flg;
  boolean VHAL_EOPFVTRCanLossSta_flg;
  boolean VHAL_EOPFVTREnableOffSta_flg;
  boolean VHAL_EOPFVTRHallSigErrSta_flg;
  uint8 VHAL_EOPFVTRLocal1CSSta_enum;
  uint8 VHAL_EOPFVTRLocal1RCSta_enum;
  uint8 VHAL_EOPFVTROverTempBCKSta_enum;
  boolean VHAL_EOPFVTROverTempSta_flg;
  uint8 VHAL_EOPFVTROverVolSta_enum;
  boolean VHAL_EOPFVTRPumpReadySta_flg;
  boolean VHAL_EOPFVTRRCInvalidSta_flg;
  uint8 VHAL_EOPFVTRRunStatusSta_enum;
  boolean VHAL_EOPFVTRStartFailureSta_flg;
  uint8 VHAL_EOPFVTRUnderVolSta_enum;
} BHAL_CAN_MCU_R1_outputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BINP_CAN3_outputs_
#define DEFINED_TYPEDEF_FOR_BINP_CAN3_outputs_

typedef struct {
  boolean VINP_CANMsgValidBMS1_flg;
  boolean VINP_CANMsgValidBMS6_flg;
  boolean VINP_CANMsgValidFD3C1000_flg;
  boolean VINP_CANMsgValidFD3VCU1_flg;
  boolean VINP_CANMsgValidFD3VCU2_flg;
  boolean VINP_CANMsgValidFD3VCU5_flg;
  boolean VINP_CANMsgValidGW3CE1000_flg;
  boolean VINP_BMS1CSErr_flg;
  boolean VINP_BMS1RCErr_flg;
  float32 VINP_HVBattVolt_V;
  boolean VINP_BMS6CSErr_flg;
  boolean VINP_BMS6RCErr_flg;
  boolean VINP_HVBContactorSta_flg;
  uint8 VINP_BatteryMode_enum;
  float32 VINP_RrCoolantflow_Lpmin;
  float32 VINP_RrCoolanttemp_C;
  boolean VINP_ActiveDischReq_flg;
  uint8 VINP_CSVCU1_enum;
  uint8 VINP_PwrSta_enum;
  uint8 VINP_RCVCU1_enum;
  uint8 VINP_ShiftGearPosn_enum;
  uint8 VINP_CSVCU2CAN1_enum;
  uint8 VINP_RCVCU2CAN1_enum;
  boolean VINP_RrActvDmpDisabReq_flg;
  boolean VINP_RrMCUEnaReq_flg;
  float32 VINP_FDCVCURrSpdMaxReq_rpm;
  float32 VINP_FDCVCURrSpdMinReq_rpm;
  uint8 VINP_FDCVCURrTMCtrlModeReq_enum;
  float32 VINP_FDCVCURrTMSpdReq_rpm;
  float32 VINP_FDCVCURrTMTqReq_Nm;
  float32 VINP_FDCVCURrTqMaxReq_Nm;
  float32 VINP_FDCVCURrTqMinReq_Nm;
  float32 VINP_IVITimeDay_DAY;
  float32 VINP_IVITimeHour_hr;
  float32 VINP_IVITimeMinute_min;
  float32 VINP_IVITimeMonth_MONTH;
  float32 VINP_IVITimeSecond_s;
  float32 VINP_VehSpeed_kph;
} BINP_CAN3_outputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BINP_CAN_MCU_R1_outputs_
#define DEFINED_TYPEDEF_FOR_BINP_CAN_MCU_R1_outputs_

typedef struct {
  boolean VINP_CANMsgValidEOPFVTRLocal1_flg;
  float32 VINP_EOPFVTRActualSpdSta_rpm;
  boolean VINP_EOPFVTRCSInvalidSta_flg;
  boolean VINP_EOPFVTRCanLossSta_flg;
  boolean VINP_EOPFVTREnableOffSta_flg;
  boolean VINP_EOPFVTRHallSigErrSta_flg;
  uint8 VINP_EOPFVTRLocal1CSSta_enum;
  uint8 VINP_EOPFVTRLocal1RCSta_enum;
  uint8 VINP_EOPFVTROverTempBCKSta_enum;
  boolean VINP_EOPFVTROverTempSta_flg;
  uint8 VINP_EOPFVTROverVolSta_enum;
  boolean VINP_EOPFVTRPumpReadySta_flg;
  boolean VINP_EOPFVTRRCInvalidSta_flg;
  uint8 VINP_EOPFVTRRunStatusSta_enum;
  boolean VINP_EOPFVTRStartFailureSta_flg;
  uint8 VINP_EOPFVTRUnderVolSta_enum;
} BINP_CAN_MCU_R1_outputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BLLC_outputs_
#define DEFINED_TYPEDEF_FOR_BLLC_outputs_

typedef struct {
  float32 VLLC_volfCooltFlowTar_C;
} BLLC_outputs;

#endif
#endif                                 /* SWC_APP_type_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
