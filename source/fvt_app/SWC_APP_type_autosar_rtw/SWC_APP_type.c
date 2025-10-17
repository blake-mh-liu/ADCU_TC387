/*
 * File: SWC_APP_type.c
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
#include "rtwtypes.h"
#include "Rte_Type.h"
#include "SWC_APP_type_private.h"
#include "rt_roundf.h"
#include <math.h>
#include "INP.h"
#include "EOP.h"
#include "HCU_LIB.h"
#include "LLC.h"
#include "GateDirver_Temp_Read.h"
#include "FVTMC_API.h"
#include "plook_u32ff_binx.h"
#include "look2_iflf_binlxpw.h"
#include "intrp2d_fu32fl_pw.h"
#include "look1_iflf_binlcapw.h"

/* Named constants for Chart: '<S790>/Chart1' */
#define SWC_APP_type_IN_Initial        ((uint8)1U)
#define SWC_APP_type_IN_Judge          ((uint8)2U)

/* Named constants for Chart: '<S597>/MotorMode' */
#define SWC_APP_t_IN_PowerDownProcedure ((uint8)2U)
#define SWC_APP_typ_IN_PowerUpProcedure ((uint8)2U)
#define SWC_APP_type_IN_AfterRunMode   ((uint8)1U)
#define SWC_APP_type_IN_Boosting       ((uint8)1U)
#define SWC_APP_type_IN_DiagService    ((uint8)2U)
#define SWC_APP_type_IN_DischargeMode  ((uint8)1U)
#define SWC_APP_type_IN_FailureMode    ((uint8)1U)
#define SWC_APP_type_IN_Heating        ((uint8)3U)
#define SWC_APP_type_IN_Initial_i      ((uint8)4U)
#define SWC_APP_type_IN_MotStM         ((uint8)2U)
#define SWC_APP_type_IN_Ready          ((uint8)5U)
#define SWC_APP_type_IN_ResolverAdjust ((uint8)6U)
#define SWC_APP_type_IN_Speed          ((uint8)7U)
#define SWC_APP_type_IN_StandBy        ((uint8)8U)
#define SWC_APP_type_IN_Torque         ((uint8)9U)

/* Exported block signals */
float32 VHAL_EOPFVTRActualSpdSta_rpm;  /* '<S134>/UnitConverter' */
float32 VHAL_HVBattVolt_V;             /* '<S158>/Add' */
float32 VHAL_RrCoolantflow_Lpmin;      /* '<S181>/Add' */
float32 VHAL_RrCoolanttemp_C;          /* '<S182>/Add' */
float32 VHAL_FDCVCURrSpdMaxReq_rpm;    /* '<S133>/UnitConverter18' */
float32 VHAL_FDCVCURrSpdMinReq_rpm;    /* '<S199>/Add' */
float32 VHAL_FDCVCURrTMSpdReq_rpm;     /* '<S200>/Add' */
float32 VHAL_FDCVCURrTMTqReq_Nm;       /* '<S201>/Add' */
float32 VHAL_FDCVCURrTqMaxReq_Nm;      /* '<S133>/UnitConverter23' */
float32 VHAL_FDCVCURrTqMinReq_Nm;      /* '<S202>/Add' */
float32 VHAL_IVITimeDay_DAY;           /* '<S133>/UnitConverter25' */
float32 VHAL_IVITimeHour_hr;           /* '<S133>/UnitConverter26' */
float32 VHAL_IVITimeMinute_min;        /* '<S133>/UnitConverter27' */
float32 VHAL_IVITimeMonth_MONTH;       /* '<S133>/UnitConverter28' */
float32 VHAL_IVITimeSecond_s;          /* '<S133>/UnitConverter29' */
float32 VHAL_VehSpeed_kph;             /* '<S209>/Add' */
float32 VCRM_IdSp_A;                   /* '<S33>/Switch' */
float32 VCRM_IqSp_A;                   /* '<S33>/Switch1' */
float32 VCRM_PIOut_value;              /* '<S47>/Switch2' */
float32 VCRM_IdCmdFWC_A;               /* '<S23>/Add' */
float32 VCRM_IdCmd_A;                  /* '<S25>/Add' */
float32 VCRM_IqCmdFWC_A;               /* '<S23>/Switch' */
float32 VDGL_OverSpdDerateCoef_gain;   /* '<S712>/Coef_Decrease_Increase' */
float32 VDGL_IGBTDerateCoef_gain;      /* '<S807>/CoefSmooth' */
float32 VDGL_MotDerateCoef_gain;       /* '<S810>/CoefSmooth' */
float32 VDGL_PCBDerateCoef_gain;       /* '<S809>/CoefSmooth' */
float32 VDGL_OilDerateCoef_gain;       /* '<S808>/CoefSmooth' */
float32 VDGL_UdcOverDerateCoef_gain;   /* '<S778>/CoefSmooth' */
float32 VDGL_UdcLowDerateCoef_gain;    /* '<S777>/CoefSmooth' */
float32 VSYL_facTorqueCoef_null;       /* '<S702>/MinMax' */
float32 VSYL_tqTMTqMax_Nm;             /* '<S702>/Product' */
float32 VSYL_tqTMTqMin_Nm;             /* '<S702>/Product1' */
float32 VCRM_IqCmd_A;                  /* '<S30>/Add' */
float32 VCRM_PwrEleAct_W;              /* '<S17>/Product2' */
float32 VCRM_BusCurr_A;                /* '<S19>/Add' */
float32 VOUTP_tqTMTqMin_Nm;            /* '<S700>/MinMax10' */
float32 VOUTP_tqTMTqMax_Nm;            /* '<S696>/MinMax10' */
float32 VOUTP_volfCooltFlowTar_C;      /* '<S672>/MinMax10' */
float32 VOUTP_nEOPSpdReq_rpm;          /* '<S668>/MinMax10' */
float32 VOUTP_PwrEleAct_W;             /* '<S660>/MinMax10' */
float32 VOUTP_BusCurr_A;               /* '<S656>/MinMax10' */
float32 VAPP_iDCurrAct_A;              /* '<S15>/Data Type Conversion' */
float32 VAPP_iQCurrAct_A;              /* '<S15>/Data Type Conversion1' */
float32 VAPP_ADCKL30_V;                /* '<S15>/Data Type Conversion2' */
float32 VAPP_ADCKL15_V;                /* '<S15>/Data Type Conversion3' */
float32 VAPP_uDC_V;                    /* '<S15>/Data Type Conversion4' */
float32 VAPP_RotSpd_rpm;               /* '<S15>/Data Type Conversion5' */
float32 VAPP_OilTemp_degC;             /* '<S15>/Data Type Conversion6' */
float32 VOUTP_OilTemp_degC;            /* '<S636>/MinMax10' */
float32 VOUTP_RotSpd_rpm;              /* '<S640>/MinMax10' */
float32 VOUTP_uDC_V;                   /* '<S652>/MinMax10' */
float32 VOUTP_ADCKL15_V;               /* '<S628>/MinMax10' */
float32 VOUTP_ADCKL30_V;               /* '<S632>/MinMax10' */
float32 VOUTP_iQCurrAct_A;             /* '<S648>/MinMax10' */
float32 VOUTP_iDCurrAct_A;             /* '<S644>/MinMax10' */
float32 VSYL_nTMSpdMin_RPM;            /* '<S12>/Constant' */
float32 VSYL_nTMSpdMax_RPM;            /* '<S12>/Constant1' */
float32 VSYL_frqSwitchMax_Hz;          /* '<S12>/Constant2' */
float32 VFOC_ADCMCUTemp_degC;          /* '<S933>/Data Type Conversion18' */
float32 VFOC_ADCFlyBackTemp_degC;      /* '<S933>/Data Type Conversion19' */
float32 VFOC_ADCOilTemp_degC;          /* '<S933>/Data Type Conversion20' */
float32 VFOC_ADCMotorUTemp_degC;       /* '<S933>/Data Type Conversion21' */
float32 VFOC_ADCMotorVTemp_degC;       /* '<S933>/Data Type Conversion22' */
float32 VFOC_ADCMotorWTemp_degC;       /* '<S933>/Data Type Conversion23' */
float32 VFOC_ADCSicUTemp_degC;         /* '<S933>/Data Type Conversion24' */
float32 VFOC_ADCSicVTemp_degC;         /* '<S933>/Data Type Conversion25' */
float32 VFOC_ADCSicWTemp_degC;         /* '<S933>/Data Type Conversion26' */
float32 VLLC_volfCooltFlowTar_C;       /* '<S590>/Switch4' */
float32 VINP_EOPFVTRActualSpdSta_rpm;  /* '<S508>/UnitConverter_2' */
float32 VINP_HVBattVolt_V;             /* '<S315>/UnitConverter_10' */
float32 VINP_RrCoolantflow_Lpmin;      /* '<S315>/UnitConverter_15' */
float32 VINP_RrCoolanttemp_C;          /* '<S315>/UnitConverter_16' */
float32 VINP_FDCVCURrSpdMaxReq_rpm;    /* '<S315>/UnitConverter_26' */
float32 VINP_FDCVCURrSpdMinReq_rpm;    /* '<S315>/UnitConverter_27' */
float32 VINP_FDCVCURrTMSpdReq_rpm;     /* '<S315>/UnitConverter_29' */
float32 VINP_FDCVCURrTMTqReq_Nm;       /* '<S315>/UnitConverter_30' */
float32 VINP_FDCVCURrTqMaxReq_Nm;      /* '<S315>/UnitConverter_31' */
float32 VINP_FDCVCURrTqMinReq_Nm;      /* '<S315>/UnitConverter_32' */
float32 VINP_IVITimeDay_DAY;           /* '<S315>/UnitConverter_33' */
float32 VINP_IVITimeHour_hr;           /* '<S315>/UnitConverter_34' */
float32 VINP_IVITimeMinute_min;        /* '<S315>/UnitConverter_35' */
float32 VINP_IVITimeMonth_MONTH;       /* '<S315>/UnitConverter_36' */
float32 VINP_IVITimeSecond_s;          /* '<S315>/UnitConverter_37' */
float32 VINP_VehSpeed_kph;             /* '<S315>/UnitConverter_38' */
float32 VFOC_GateICFrame0Vl_pct;       /* '<S5>/C Caller10' */
float32 VFOC_GateICFrame0Wl_pct;       /* '<S5>/C Caller11' */
float32 VFOC_GateICFrame1Vh_pct;       /* '<S5>/C Caller12' */
float32 VFOC_GateICFrame1Wh_pct;       /* '<S5>/C Caller13' */
float32 VFOC_GateICFrame1Ul_pct;       /* '<S5>/C Caller14' */
float32 VFOC_GateICFrame0Uh_pct;       /* '<S5>/C Caller3' */
float32 VFOC_GateICFrame0Vh_pct;       /* '<S5>/C Caller4' */
float32 VFOC_GateICFrame0Wh_pct;       /* '<S5>/C Caller5' */
float32 VFOC_GateICFrame1Vl_pct;       /* '<S5>/C Caller6' */
float32 VFOC_GateICFrame1Wl_pct;       /* '<S5>/C Caller7' */
float32 VFOC_GateICFrame1Uh_pct;       /* '<S5>/C Caller8' */
float32 VFOC_GateICFrame0Ul_pct;       /* '<S5>/C Caller9' */
float32 VEOP_nEOPSpdReq_rpm;           /* '<S125>/Switch4' */
float32 VCRM_IdCmdinit_A;              /* '<S18>/IArb' */
float32 VCRM_IqCmdinit_A;              /* '<S18>/IArb' */
uint8 VHAL_EOPFVTRLocal1CSSta_enum;    /* '<S134>/UnitConverter5' */
uint8 VHAL_EOPFVTRLocal1RCSta_enum;    /* '<S134>/UnitConverter6' */
uint8 VHAL_EOPFVTROverTempBCKSta_enum; /* '<S134>/UnitConverter7' */
uint8 VHAL_EOPFVTROverVolSta_enum;     /* '<S134>/UnitConverter9' */
uint8 VHAL_EOPFVTRRunStatusSta_enum;   /* '<S134>/UnitConverter12' */
uint8 VHAL_EOPFVTRUnderVolSta_enum;    /* '<S134>/UnitConverter14' */
uint8 VHAL_BatteryMode_enum;           /* '<S133>/UnitConverter6' */
uint8 VHAL_CSVCU1_enum;                /* '<S133>/UnitConverter10' */
uint8 VHAL_PwrSta_enum;                /* '<S133>/UnitConverter11' */
uint8 VHAL_RCVCU1_enum;                /* '<S133>/UnitConverter12' */
uint8 VHAL_ShiftGearPosn_enum;         /* '<S133>/UnitConverter13' */
uint8 VHAL_CSVCU2CAN1_enum;            /* '<S133>/UnitConverter14' */
uint8 VHAL_RCVCU2CAN1_enum;            /* '<S133>/UnitConverter15' */
uint8 VHAL_FDCVCURrTMCtrlModeReq_enum; /* '<S133>/UnitConverter20' */
uint8 VOUTP_IVTROpMode_enum;           /* '<S680>/MinMax10' */
uint8 VOUTP_MotMod_enum;               /* '<S688>/MinMax10' */
uint8 VOPM_MotMod_enum;                /* '<S597>/OpMod_stMotActswt' */
uint8 VOPM_IVTROpMode_enum;            /* '<S597>/OpMod_stIvtrTarswt' */
uint8 VINP_EOPFVTROverVolSta_enum;     /* '<S508>/UnitConverter_11' */
uint8 VINP_EOPFVTRRunStatusSta_enum;   /* '<S508>/UnitConverter_14' */
uint8 VINP_EOPFVTRUnderVolSta_enum;    /* '<S508>/UnitConverter_16' */
uint8 VINP_EOPFVTRLocal1CSSta_enum;    /* '<S508>/UnitConverter_7' */
uint8 VINP_EOPFVTRLocal1RCSta_enum;    /* '<S508>/UnitConverter_8' */
uint8 VINP_EOPFVTROverTempBCKSta_enum; /* '<S508>/UnitConverter_9' */
uint8 VINP_BatteryMode_enum;           /* '<S315>/UnitConverter_14' */
uint8 VINP_CSVCU1_enum;                /* '<S315>/UnitConverter_18' */
uint8 VINP_PwrSta_enum;                /* '<S315>/UnitConverter_19' */
uint8 VINP_RCVCU1_enum;                /* '<S315>/UnitConverter_20' */
uint8 VINP_ShiftGearPosn_enum;         /* '<S315>/UnitConverter_21' */
uint8 VINP_CSVCU2CAN1_enum;            /* '<S315>/UnitConverter_22' */
uint8 VINP_RCVCU2CAN1_enum;            /* '<S315>/UnitConverter_23' */
uint8 VINP_FDCVCURrTMCtrlModeReq_enum; /* '<S315>/UnitConverter_28' */
boolean VDGL_OverSpdErr_flg;           /* '<S712>/Logical Operator2' */
boolean VHAL_EOPFVTRCSInvalidSta_flg;  /* '<S134>/UnitConverter1' */
boolean VHAL_EOPFVTRCanLossSta_flg;    /* '<S134>/UnitConverter2' */
boolean VHAL_EOPFVTREnableOffSta_flg;  /* '<S134>/UnitConverter3' */
boolean VHAL_EOPFVTRHallSigErrSta_flg; /* '<S134>/UnitConverter4' */
boolean VHAL_EOPFVTROverTempSta_flg;   /* '<S134>/UnitConverter8' */
boolean VHAL_EOPFVTRPumpReadySta_flg;  /* '<S134>/UnitConverter10' */
boolean VHAL_EOPFVTRRCInvalidSta_flg;  /* '<S134>/UnitConverter11' */
boolean VHAL_EOPFVTRStartFailureSta_flg;/* '<S134>/UnitConverter13' */
boolean VHAL_BMS1CSErr_flg;            /* '<S146>/Equal' */
boolean VHAL_BMS1RCErr_flg;            /* '<S146>/Logical Operator4' */
boolean VHAL_BMS6CSErr_flg;            /* '<S164>/Equal' */
boolean VHAL_BMS6RCErr_flg;            /* '<S164>/Logical Operator4' */
boolean VHAL_HVBContactorSta_flg;      /* '<S133>/UnitConverter5' */
boolean VHAL_ActiveDischReq_flg;       /* '<S133>/UnitConverter9' */
boolean VHAL_RrActvDmpDisabReq_flg;    /* '<S133>/UnitConverter16' */
boolean VHAL_RrMCUEnaReq_flg;          /* '<S133>/UnitConverter17' */
boolean VDGL_DiagOverTrq_flg;          /* '<S714>/DiagM_bOverTorqueswt' */
boolean VOPM_MCUEna_flg;               /* '<S10>/Data Type Conversion' */
boolean VOPM_TMReady_flg;              /* '<S10>/Data Type Conversion1' */
boolean VOPM_BoostOPSta_flg;           /* '<S10>/Data Type Conversion2' */
boolean VOUTP_BoostOPSta_flg;          /* '<S676>/MinMax10' */
boolean VOUTP_TMReady_flg;             /* '<S692>/MinMax10' */
boolean VOUTP_MCUEna_flg;              /* '<S684>/MinMax10' */
boolean VOUTP_bMotEnaReq_flg;          /* '<S664>/MinMax10' */
boolean VHAL_CANMsgInvalidEOPFVTRLocal1_flg;/* '<S210>/Equal' */
boolean VHAL_CANMsgInvalidBMS1_flg;    /* '<S137>/Equal' */
boolean VHAL_CANMsgInvalidBMS6_flg;    /* '<S137>/Equal1' */
boolean VHAL_CANMsgInvalidFD3C1000_flg;/* '<S137>/Equal2' */
boolean VHAL_CANMsgInvalidFD3VCU1_flg; /* '<S137>/Equal3' */
boolean VHAL_CANMsgInvalidFD3VCU2_flg; /* '<S137>/Equal4' */
boolean VHAL_CANMsgInvalidFD3VCU5_flg; /* '<S137>/Equal5' */
boolean VHAL_CANMsgInvalidGW3CE1000_flg;/* '<S137>/Equal6' */
boolean VDGL_DiagStall_flg;            /* '<S907>/SWT' */
boolean VDGL_TempMotWarning_flg;       /* '<S841>/Signal Conversion' */
boolean VDGL_TempMotFault_flg;         /* '<S841>/Signal Conversion1' */
boolean VDGL_TempPCBWarning_flg;       /* '<S833>/Signal Conversion' */
boolean VDGL_TempPCBFault_flg;         /* '<S833>/Signal Conversion1' */
boolean VDGL_TempOilWarning_flg;       /* '<S824>/Signal Conversion' */
boolean VDGL_TempOilFault_flg;         /* '<S824>/Signal Conversion1' */
boolean VDGL_TempIGBTFault_flg;        /* '<S816>/Signal Conversion' */
boolean VDGL_TempIGBTWarning_flg;      /* '<S817>/Signal Conversion' */
boolean VDGL_HVOverErr_flg;            /* '<S791>/Signal Conversion' */
boolean VDGL_HVOverWarn_flg;           /* '<S791>/Signal Conversion1' */
boolean VDGL_HVLowErr_flg;             /* '<S782>/Signal Conversion' */
boolean VDGL_HVLowWarn_flg;            /* '<S782>/Signal Conversion1' */
boolean VDGL_DiagEOPSpdDiff_flg;       /* '<S739>/SWT' */
boolean VOPM_CurLoopEna_flg;           /* '<S597>/Logical Operator' */
boolean VOPM_PsvDischrgEna_flg;        /* '<S597>/OpMod_stMotActswt1' */
boolean VINP_CANMsgValidEOPFVTRLocal1_flg;/* '<S507>/not1' */
boolean VINP_EOPFVTROverTempSta_flg;   /* '<S508>/UnitConverter_10' */
boolean VINP_EOPFVTRPumpReadySta_flg;  /* '<S508>/UnitConverter_12' */
boolean VINP_EOPFVTRRCInvalidSta_flg;  /* '<S508>/UnitConverter_13' */
boolean VINP_EOPFVTRStartFailureSta_flg;/* '<S508>/UnitConverter_15' */
boolean VINP_EOPFVTRCSInvalidSta_flg;  /* '<S508>/UnitConverter_3' */
boolean VINP_EOPFVTRCanLossSta_flg;    /* '<S508>/UnitConverter_4' */
boolean VINP_EOPFVTREnableOffSta_flg;  /* '<S508>/UnitConverter_5' */
boolean VINP_EOPFVTRHallSigErrSta_flg; /* '<S508>/UnitConverter_6' */
boolean VINP_CANMsgValidBMS1_flg;      /* '<S314>/not1' */
boolean VINP_BMS1CSErr_flg;            /* '<S315>/UnitConverter_8' */
boolean VINP_CANMsgValidBMS6_flg;      /* '<S314>/not2' */
boolean VINP_CANMsgValidFD3C1000_flg;  /* '<S314>/not3' */
boolean VINP_CANMsgValidFD3VCU1_flg;   /* '<S314>/not4' */
boolean VINP_CANMsgValidFD3VCU2_flg;   /* '<S314>/not5' */
boolean VINP_CANMsgValidFD3VCU5_flg;   /* '<S314>/not6' */
boolean VINP_CANMsgValidGW3CE1000_flg; /* '<S314>/not7' */
boolean VINP_BMS6CSErr_flg;            /* '<S315>/UnitConverter_11' */
boolean VINP_BMS6RCErr_flg;            /* '<S315>/UnitConverter_12' */
boolean VINP_HVBContactorSta_flg;      /* '<S315>/UnitConverter_13' */
boolean VINP_ActiveDischReq_flg;       /* '<S315>/UnitConverter_17' */
boolean VINP_RrActvDmpDisabReq_flg;    /* '<S315>/UnitConverter_24' */
boolean VINP_RrMCUEnaReq_flg;          /* '<S315>/UnitConverter_25' */
boolean VINP_BMS1RCErr_flg;            /* '<S315>/UnitConverter_9' */
boolean VEOP_bMotEnaReq_flg;           /* '<S125>/Switch1' */

/* Exported data definition */
#define SWC_APP_type_START_SEC_CAL
#include "SWC_APP_type_MemMap.h"

/* Definition for custom storage class: Global */
float32 ACRM_Eta_X_rpm[4] = { 5000.0F, 10000.0F, 15000.0F, 20000.0F } ;
                                    /* Referenced by: '<S17>/MPEM_EtaY_value' */

float32 ACRM_MTPAIdGenMin_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F,
  5000.0F, 6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F,
  13000.0F, 14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F
} ;                                    /* Referenced by: '<S28>/530MTPAIdGen' */

float32 ACRM_MTPAIdGenMin_Y_Nm[51] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F,
  60.0F, 70.0F, 80.0F, 90.0F, 100.0F, 110.0F, 120.0F, 130.0F, 140.0F, 150.0F,
  160.0F, 170.0F, 180.0F, 190.0F, 200.0F, 210.0F, 220.0F, 230.0F, 240.0F, 250.0F,
  260.0F, 270.0F, 280.0F, 290.0F, 300.0F, 310.0F, 320.0F, 330.0F, 340.0F, 350.0F,
  360.0F, 370.0F, 380.0F, 390.0F, 400.0F, 410.0F, 420.0F, 430.0F, 440.0F, 450.0F,
  460.0F, 470.0F, 480.0F, 490.0F, 500.0F } ;/* Referenced by: '<S28>/530MTPAIdGen' */

float32 ACRM_MTPAIdGen_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F, 5000.0F,
  6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F, 13000.0F,
  14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F } ;/* Referenced by: '<S27>/696MTPAIdGen' */

float32 ACRM_MTPAIdGen_Y_Nm[51] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F,
  60.0F, 70.0F, 80.0F, 90.0F, 100.0F, 110.0F, 120.0F, 130.0F, 140.0F, 150.0F,
  160.0F, 170.0F, 180.0F, 190.0F, 200.0F, 210.0F, 220.0F, 230.0F, 240.0F, 250.0F,
  260.0F, 270.0F, 280.0F, 290.0F, 300.0F, 310.0F, 320.0F, 330.0F, 340.0F, 350.0F,
  360.0F, 370.0F, 380.0F, 390.0F, 400.0F, 410.0F, 420.0F, 430.0F, 440.0F, 450.0F,
  460.0F, 470.0F, 480.0F, 490.0F, 500.0F } ;/* Referenced by: '<S27>/696MTPAIdGen' */

float32 ACRM_MTPAIdMotMin_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F,
  5000.0F, 6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F,
  13000.0F, 14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F
} ;                                    /* Referenced by:
                                        * '<S28>/530MTPAIdMot'
                                        * '<S28>/Prelookup1'
                                        */

float32 ACRM_MTPAIdMotMin_Y_Nm[51] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F,
  60.0F, 70.0F, 80.0F, 90.0F, 100.0F, 110.0F, 120.0F, 130.0F, 140.0F, 150.0F,
  160.0F, 170.0F, 180.0F, 190.0F, 200.0F, 210.0F, 220.0F, 230.0F, 240.0F, 250.0F,
  260.0F, 270.0F, 280.0F, 290.0F, 300.0F, 310.0F, 320.0F, 330.0F, 340.0F, 350.0F,
  360.0F, 370.0F, 380.0F, 390.0F, 400.0F, 410.0F, 420.0F, 430.0F, 440.0F, 450.0F,
  460.0F, 470.0F, 480.0F, 490.0F, 500.0F } ;/* Referenced by:
                                             * '<S28>/530MTPAIdMot'
                                             * '<S28>/Prelookup'
                                             */

float32 ACRM_MTPAIdMot_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F, 5000.0F,
  6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F, 13000.0F,
  14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F } ;/* Referenced by:
                                                                      * '<S27>/696MTPAIdMot'
                                                                      * '<S27>/Prelookup1'
                                                                      */

float32 ACRM_MTPAIdMot_Y_Nm[51] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F,
  60.0F, 70.0F, 80.0F, 90.0F, 100.0F, 110.0F, 120.0F, 130.0F, 140.0F, 150.0F,
  160.0F, 170.0F, 180.0F, 190.0F, 200.0F, 210.0F, 220.0F, 230.0F, 240.0F, 250.0F,
  260.0F, 270.0F, 280.0F, 290.0F, 300.0F, 310.0F, 320.0F, 330.0F, 340.0F, 350.0F,
  360.0F, 370.0F, 380.0F, 390.0F, 400.0F, 410.0F, 420.0F, 430.0F, 440.0F, 450.0F,
  460.0F, 470.0F, 480.0F, 490.0F, 500.0F } ;/* Referenced by:
                                             * '<S27>/696MTPAIdMot'
                                             * '<S27>/Prelookup'
                                             */

float32 ACRM_MTPVIdLimt_X_rpm[18] = { 11500.0F, 12000.0F, 12500.0F, 13000.0F,
  13500.0F, 14000.0F, 14500.0F, 15000.0F, 15500.0F, 16000.0F, 16500.0F, 17000.0F,
  17500.0F, 18000.0F, 18500.0F, 19000.0F, 19500.0F, 20000.0F } ;
                                   /* Referenced by: '<S26>/1-D Lookup Table' */

float32 AEOP_nReqMotSpdMax_X_A[5] = { -21.0F, -10.0F, 0.0F, 10.0F, 80.0F } ;
                              /* Referenced by: '<S125>/EopC_nReqMotSpdMax_T' */

float32 AEOP_nRrOilTempSpdMod_X_degC[9] = { -40.0F, -30.0F, -10.0F, 0.0F, 10.0F,
  20.0F, 50.0F, 80.0F, 100.0F } ;      /* Referenced by:
                                        * '<S126>/EopC_nRrOilTempDetOptMod_M'
                                        * '<S128>/EopC_nRrOilTempMotOptMod_M'
                                        * '<S131>/EopC_nRrOilTemp_M'
                                        */

float32 AEOP_nRrOilTempSpdMod_Y_KW[10] = { 4.5F, 5.5F, 6.5F, 7.5F, 8.5F, 10.0F,
  12.0F, 14.0F, 16.0F, 18.0F } ;       /* Referenced by:
                                        * '<S126>/EopC_nRrOilTempDetOptMod_M'
                                        * '<S128>/EopC_nRrOilTempMotOptMod_M'
                                        * '<S131>/EopC_nRrOilTemp_M'
                                        */

float32 AEOP_nRrTMTempSpdMod_X_degC[10] = { -40.0F, -30.0F, -20.0F, -10.0F, 0.0F,
  10.0F, 20.0F, 40.0F, 80.0F, 120.0F } ;/* Referenced by:
                                         * '<S126>/EopC_nRrTMTempDetOptMod_T'
                                         * '<S128>/EopC_nRrTMTempMotOptMod_T'
                                         * '<S131>/EopC_nRrTMTemp_T'
                                         */

float32 ALLC_volCoolFlowOil_X_degC[4] = { -40.0F, -20.0F, 0.0F, 20.0F } ;
                             /* Referenced by: '<S590>/LLCM_volCoolFlowOil_M' */

float32 ALLC_volCoolFlowWater_X_kW[4] = { 1.0F, 2.0F, 3.0F, 4.0F } ;
                           /* Referenced by: '<S590>/LLCM_volCoolFlowWater_M' */

float32 ALLC_volCoolFlowWater_Y_degC[4] = { -40.0F, -20.0F, 0.0F, 20.0F } ;
                           /* Referenced by: '<S590>/LLCM_volCoolFlowWater_M' */

float32 ALLC_volfCooltFlow_X_degC[4] = { -40.0F, -20.0F, 0.0F, 20.0F } ;
                              /* Referenced by: '<S590>/LLCM_volfCooltFlow_M' */

float32 ASYL_TrqMax_X_V[5] = { 100.0F, 200.0F, 300.0F, 400.0F, 500.0F } ;/* Referenced by: '<S702>/TrqMax' */

float32 ASYL_TrqMax_Y_rpm[21] = { 0.0F, 1000.0F, 2000.0F, 3000.0F, 4000.0F,
  5000.0F, 6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F,
  13000.0F, 14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F
} ;                                    /* Referenced by: '<S702>/TrqMax' */

float32 ASYL_TrqMin_X_V[5] = { 100.0F, 200.0F, 300.0F, 400.0F, 500.0F } ;/* Referenced by: '<S702>/TrqMin' */

float32 ASYL_TrqMin_Y_rpm[21] = { 0.0F, 1000.0F, 2000.0F, 3000.0F, 4000.0F,
  5000.0F, 6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F,
  13000.0F, 14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F
} ;                                    /* Referenced by: '<S702>/TrqMin' */

boolean Diag2_bRstFault_C = false_MatlabRTW;/* Referenced by:
                                             * '<S13>/Constant2'
                                             * '<S13>/Constant7'
                                             */
float32 Diag2_f32_UdcLowCoefAddStep_C = 0.005F;/* Referenced by: '<S777>/T4' */
float32 Diag2_f32_UdcLowCoefDepStep_C = 0.005F;/* Referenced by: '<S777>/T3' */
float32 Diag2_f32_UdcLowHysBand_C = 10.0F;/* Referenced by: '<S777>/dT2' */
float32 Diag2_f32_UdcLowStartDerat_C = 510.0F;/* Referenced by:
                                               * '<S777>/T1'
                                               * '<S782>/T1'
                                               */
float32 Diag2_f32_UdcLowStopDerat_C = 480.0F;/* Referenced by:
                                              * '<S777>/T2'
                                              * '<S782>/T2'
                                              */
float32 Diag2_f32_UdcOverCoefAddStep_C = 0.005F;/* Referenced by: '<S778>/T4' */
float32 Diag2_f32_UdcOverCoefDepStep_C = 0.005F;/* Referenced by: '<S778>/T3' */
float32 Diag2_f32_UdcOverHysBand_C = 20.0F;/* Referenced by: '<S778>/dT2' */
float32 Diag2_f32_UdcOverStartDerat_C = 750.0F;/* Referenced by:
                                                * '<S778>/T1'
                                                * '<S791>/T1'
                                                */
float32 Diag2_f32_UdcOverStopDerat_C = 880.0F;/* Referenced by:
                                               * '<S778>/T2'
                                               * '<S791>/T2'
                                               */
sint16 Diag2_int16_HvLowErrErr_C = 20; /* Referenced by: '<S782>/Constant2' */
sint16 Diag2_int16_HvLowErrHeal_C = -20;/* Referenced by: '<S782>/Constant1' */
sint16 Diag2_int16_HvLowWarnErr_C = 20;/* Referenced by: '<S782>/Constant5' */
sint16 Diag2_int16_HvLowWarnHeal_C = -20;/* Referenced by: '<S782>/Constant4' */
sint16 Diag2_int16_HvOverErrErr_C = 20;/* Referenced by: '<S791>/Constant2' */
sint16 Diag2_int16_HvOverErrHeal_C = -20;/* Referenced by: '<S791>/Constant1' */
sint16 Diag2_int16_HvOverWarnErr_C = 20;/* Referenced by: '<S791>/Constant5' */
sint16 Diag2_int16_HvOverWarnHeal_C = -20;/* Referenced by: '<S791>/Constant4' */
boolean DiagM_Fault2LevelMor_C = false_MatlabRTW;
                             /* Referenced by: '<S13>/Diag3_Fault2LevelMor_C' */
boolean DiagM_Fault2LevelTrig_C = false_MatlabRTW;
                            /* Referenced by: '<S13>/Diag3_Fault2LevelTrig_C' */
boolean DiagM_bZeroCurrMor_C = false_MatlabRTW;
                               /* Referenced by: '<S13>/DiagM_bZeroCurrMor_C' */
boolean DiagM_bZeroCurrTrig_C = false_MatlabRTW;
                              /* Referenced by: '<S13>/DiagM_bZeroCurrTrig_C' */
boolean EopC_bMotEnaManTrig_C = false_MatlabRTW;/* Referenced by: '<S125>/Constant12' */
boolean EopC_bMotEnaMan_C = false_MatlabRTW;/* Referenced by: '<S125>/Constant11' */
float32 EopC_nReqMotSpdMan_C = 0.0F;
                                /* Referenced by: '<S125>/MPS_ReqMotSpdMor10' */
float32 EopC_nReqMotSpdMin_C = 0.0F;
                                 /* Referenced by: '<S125>/MPS_ReqMotSpdMor5' */
boolean EopC_nReqMotSpdTrig_C = false_MatlabRTW;
                              /* Referenced by: '<S125>/MPS_ReqMotSpdMorFlg1' */
float32 EopC_rSpdRampDown_C = -7000.0F;
                                 /* Referenced by: '<S125>/MPS_ReqMotSpdMor9' */
float32 EopC_rSpdRampUp_C = 20000.0F;
                                 /* Referenced by: '<S125>/MPS_ReqMotSpdMor6' */
uint8 KAPP_ADCKL15_enum = 1U;          /* Referenced by: '<S933>/Constant10' */
uint8 KAPP_ADCKL30_enum = 2U;          /* Referenced by: '<S933>/Constant9' */
boolean KCRM_AtSweep_deg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S33>/Constant9' */
float32 KCRM_AtSweep_deg_ovrdval = 90.0F;/* Referenced by: '<S33>/Constant4' */
float32 KCRM_BusCurFil_null = 0.01F;   /* Referenced by: '<S17>/Constant1' */
boolean KCRM_CurDebugSwt_null = true_MatlabRTW;/* Referenced by: '<S18>/Constant5' */
float32 KCRM_CurTqCmdHi_Nm = 80.0F;    /* Referenced by: '<S23>/Constant6' */
float32 KCRM_CurTqCmdLo_Nm = 50.0F;    /* Referenced by: '<S23>/Constant5' */
float32 KCRM_DynoDeratingFiltFac_null = 0.01F;/* Referenced by: '<S20>/Constant' */
float32 KCRM_FWCEnable_null = 0.0F;    /* Referenced by: '<S23>/Gain1' */
float32 KCRM_FWCKi_null = 40.0F;       /* Referenced by: '<S23>/Constant1' */
float32 KCRM_FWCKp_null = 1.0F;        /* Referenced by: '<S23>/Constant' */
float32 KCRM_IdCmdFilCoeff_null = 0.05F;/* Referenced by: '<S25>/Constant' */
float32 KCRM_IdCmdMaxLimt_A = -600.0F; /* Referenced by: '<S26>/Constant3' */
float32 KCRM_IdSpForActvDisc_null = -40.0F;/* Referenced by: '<S18>/Constant2' */
float32 KCRM_IdSp_A_ovrdval = 0.0F;    /* Referenced by: '<S33>/Constant6' */
float32 KCRM_IdqMapVolHi_V = 696.0F;   /* Referenced by: '<S31>/Constant' */
float32 KCRM_IdqMapVolLo_V = 530.0F;   /* Referenced by: '<S31>/Constant1' */
float32 KCRM_IqCmdFilCoeff_null = 0.05F;/* Referenced by: '<S30>/Constant' */
float32 KCRM_IqDeratingFac_null = 0.4F;/* Referenced by:
                                        * '<S18>/Constant6'
                                        * '<S18>/Constant7'
                                        */
float32 KCRM_IqDeratingRecoverTi_ms = 30000.0F;/* Referenced by: '<S18>/Constant8' */
float32 KCRM_IqDeratingTi_ms = 30000.0F;/* Referenced by: '<S18>/Constant4' */
float32 KCRM_IqSp_A_ovrdval = 0.0F;    /* Referenced by: '<S33>/Constant7' */
float32 KCRM_IsSp_A = 0.0F;            /* Referenced by: '<S33>/Constant3' */
boolean KCRM_MTPAGenSwitch_flg = false_MatlabRTW;/* Referenced by:
                                                  * '<S27>/Constant3'
                                                  * '<S28>/Constant3'
                                                  */
boolean KCRM_MTPAMotSwitch_flg = false_MatlabRTW;/* Referenced by:
                                                  * '<S27>/Constant'
                                                  * '<S28>/Constant'
                                                  */
float32 KCRM_MTPVSpdThd_rpm = 11500.0F;/* Referenced by: '<S26>/Constant' */
float32 KCRM_MinVolOfst4FW_V = 30.0F;  /* Referenced by: '<S29>/Constant19' */
float32 KCRM_PILowerLimit_null = -500.0F;/* Referenced by: '<S23>/Constant2' */
float32 KCRM_SpdCtlPrd_s = 0.001F;     /* Referenced by: '<S23>/Gain' */
boolean KCRM_UsingIsSp_A_ovrdflg = true_MatlabRTW;/* Referenced by:
                                                   * '<S33>/Constant1'
                                                   * '<S33>/Constant2'
                                                   */
float32 KCRM_VolModINV_perc = 1.7544F; /* Referenced by: '<S31>/Gain' */
float32 KCRM_VolOfstVsBattVol4FW_V = 0.0F;/* Referenced by: '<S29>/Constant10' */
boolean KCRM_bRstDebugOverSpd_null = false_MatlabRTW;/* Referenced by: '<S18>/Constant15' */
float32 KCRM_grdIsThetaRampDown_C = -0.1F;/* Referenced by: '<S33>/Constant10' */
float32 KCRM_grdIsThetaRampUp_C = 0.1F;/* Referenced by: '<S33>/Constant11' */
float32 KCRM_nDebugOverSpd_rpm = 6000.0F;/* Referenced by: '<S18>/Constant12' */
float32 KCRM_tiDebugOverSpdDlyon_ms = 500.0F;/* Referenced by: '<S18>/Constant11' */
float32 KDGL_IGBTCoefAddStep_C = 0.005F;/* Referenced by: '<S807>/T4' */
float32 KDGL_IGBTCoefDepStep_C = 0.005F;/* Referenced by: '<S807>/T3' */
float32 KDGL_IGBTHysBand_C = 3.0F;     /* Referenced by: '<S807>/dT2' */
float32 KDGL_IGBTStartDerat_C = 85.0F; /* Referenced by:
                                        * '<S807>/T1'
                                        * '<S817>/T1'
                                        */
float32 KDGL_IGBTStopDerat_C = 90.0F;  /* Referenced by:
                                        * '<S807>/T2'
                                        * '<S816>/T2'
                                        */
float32 KDGL_MotCoefAddStep_C = 0.005F;/* Referenced by: '<S810>/T6' */
float32 KDGL_MotCoefDepStep_C = 0.005F;/* Referenced by: '<S810>/T5' */
float32 KDGL_MotHysBand_C = 10.0F;     /* Referenced by: '<S810>/dT1' */
float32 KDGL_MotStartDerat_C = 110.0F; /* Referenced by:
                                        * '<S810>/T3'
                                        * '<S841>/T3'
                                        */
float32 KDGL_MotStopDerat_C = 120.0F;  /* Referenced by:
                                        * '<S810>/T4'
                                        * '<S841>/T4'
                                        */
float32 KDGL_OilCoefAddStep_C = 0.005F;/* Referenced by: '<S808>/T4' */
float32 KDGL_OilCoefDepStep_C = 0.005F;/* Referenced by: '<S808>/T3' */
float32 KDGL_OilHysBand_C = 3.0F;      /* Referenced by: '<S808>/dT2' */
float32 KDGL_OilStartDerat_C = 110.0F; /* Referenced by:
                                        * '<S808>/T1'
                                        * '<S824>/T1'
                                        */
float32 KDGL_OilStopDerat_C = 120.0F;  /* Referenced by:
                                        * '<S808>/T2'
                                        * '<S824>/T2'
                                        */
sint16 KDGL_OverSpdErr_cnt = 20;       /* Referenced by: '<S800>/Constant2' */
sint16 KDGL_OverSpdHeal_cnt = -20;     /* Referenced by: '<S800>/Constant1' */
float32 KDGL_OverSpdHysBand_rpm = 1000.0F;/* Referenced by: '<S800>/Constant3' */
float32 KDGL_OverSpdNotEna_rpm = 2800.0F;/* Referenced by: '<S712>/Constant' */
float32 KDGL_OverSpd_rpm = 10000.0F;   /* Referenced by: '<S800>/Constant' */
boolean KDGL_OverTorque_flg_ovrdflg = true_MatlabRTW;
                           /* Referenced by: '<S714>/DiagM_bOverTorqueTrig_C' */
boolean KDGL_OverTorque_flg_ovrdval = false_MatlabRTW;
                            /* Referenced by: '<S714>/DiagM_bOverTorqueMor_C' */
float32 KDGL_PCBCoefAddStep_C = 0.005F;/* Referenced by: '<S809>/T4' */
float32 KDGL_PCBCoefDepStep_C = 0.005F;/* Referenced by: '<S809>/T3' */
float32 KDGL_PCBHysBand_C = 3.0F;      /* Referenced by: '<S809>/dT2' */
float32 KDGL_PCBStartDerat_C = 85.0F;  /* Referenced by:
                                        * '<S809>/T1'
                                        * '<S833>/T1'
                                        */
float32 KDGL_PCBStopDerat_C = 90.0F;   /* Referenced by:
                                        * '<S809>/T2'
                                        * '<S833>/T2'
                                        */
float32 KDGL_SpdOverCoefAddStep_C = 0.005F;/* Referenced by: '<S712>/T4' */
float32 KDGL_SpdOverCoefSubStep_C = 0.005F;/* Referenced by: '<S712>/T3' */
sint16 KDGL_TempIGBTFaultErr_C = 20;   /* Referenced by: '<S816>/Constant2' */
sint16 KDGL_TempIGBTFaultHeal_C = -20; /* Referenced by: '<S816>/Constant1' */
sint16 KDGL_TempIGBTWarningErr_C = 20; /* Referenced by: '<S817>/Constant2' */
sint16 KDGL_TempIGBTWarningHeal_C = -20;/* Referenced by: '<S817>/Constant1' */
sint16 KDGL_TempMotFaultErr_C = 20;    /* Referenced by: '<S841>/Constant5' */
sint16 KDGL_TempMotFaultHeal_C = -20;  /* Referenced by: '<S841>/Constant4' */
sint16 KDGL_TempMotWarningErr_C = 20;  /* Referenced by: '<S841>/Constant2' */
sint16 KDGL_TempMotWarningHeal_C = -20;/* Referenced by: '<S841>/Constant1' */
sint16 KDGL_TempOilFaultErr_C = 20;    /* Referenced by: '<S824>/Constant5' */
sint16 KDGL_TempOilFaultHeal_C = -20;  /* Referenced by: '<S824>/Constant4' */
sint16 KDGL_TempOilWarningErr_C = 20;  /* Referenced by: '<S824>/Constant2' */
sint16 KDGL_TempOilWarningHeal_C = -20;/* Referenced by: '<S824>/Constant1' */
sint16 KDGL_TempPCBFaultErr_C = 20;    /* Referenced by: '<S833>/Constant5' */
sint16 KDGL_TempPCBFaultHeal_C = -20;  /* Referenced by: '<S833>/Constant4' */
sint16 KDGL_TempPCBWarningErr_C = 20;  /* Referenced by: '<S833>/Constant2' */
sint16 KDGL_TempPCBWarningHeal_C = -20;/* Referenced by: '<S833>/Constant1' */
boolean KDGL_bBusOffEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT2' */
boolean KDGL_bComInvaildVcuEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT3' */
boolean KDGL_bComLostVcuEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT1' */
boolean KDGL_bCurrFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT6' */
boolean KDGL_bEOPFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT10' */
boolean KDGL_bEnaBenchShutDwn_C = true_MatlabRTW;/* Referenced by: '<S13>/Constant1' */
boolean KDGL_bHvDcVoltFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT9' */
boolean KDGL_bIGNVoltFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT15' */
boolean KDGL_bOilTempFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT12' */
boolean KDGL_bPCBTempFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT11' */
boolean KDGL_bPREREGFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT16' */
boolean KDGL_bPosSenrFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT4' */
boolean KDGL_bRstStallPort_flg = false_MatlabRTW;/* Referenced by: '<S715>/Constant7' */
boolean KDGL_bSicFltFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT8' */
boolean KDGL_bSicTempFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT7' */
boolean KDGL_bTempSensrFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT5' */
boolean KDGL_bVCC5VFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT17' */
boolean KDGL_bVREF5VFaultEna_C = false_MatlabRTW;/* Referenced by: '<S706>/dT18' */
boolean KDGL_bWaterTempFaultEna_C = false_MatlabRTW;/* Referenced by:
                                                     * '<S706>/dT13'
                                                     * '<S706>/dT14'
                                                     */
float32 KDGL_iMotStallProtEna_A = 150.0F;/* Referenced by: '<S715>/Constant2' */
float32 KDGL_nEOPSpdDiff_rpm = 300.0F; /* Referenced by: '<S708>/Constant35' */
float32 KDGL_nRotStallProtEna_rpm = 150.0F;/* Referenced by: '<S715>/Constant31' */
float32 KDGL_tiDlyOffEOP_C = 500.0F;   /* Referenced by: '<S708>/Constant20' */
float32 KDGL_tiDlyOffOverTqProt_C = 500.0F;/* Referenced by: '<S714>/Constant20' */
float32 KDGL_tiDlyOnEOP_C = 500.0F;    /* Referenced by: '<S708>/Constant1' */
float32 KDGL_tiDlyOnOverTqProt_C = 500.0F;/* Referenced by: '<S714>/Constant1' */
float32 KDGL_tiDlyOnStallProt_C = 1000.0F;/* Referenced by: '<S715>/Constant1' */
float32 KDGL_tqMotStallProtEna_Nm = 400.0F;/* Referenced by: '<S715>/Constant35' */
uint8 KFOC_ADCFlyBackTemp_enum = 25U;  /* Referenced by: '<S933>/Constant7' */
uint8 KFOC_ADCMCUTemp_enum = 24U;      /* Referenced by: '<S933>/Constant8' */
uint8 KFOC_ADCMotorUTemp_enum = 27U;   /* Referenced by: '<S933>/Constant1' */
uint8 KFOC_ADCMotorVTemp_enum = 28U;   /* Referenced by: '<S933>/Constant2' */
uint8 KFOC_ADCMotorWTemp_enum = 29U;   /* Referenced by: '<S933>/Constant3' */
uint8 KFOC_ADCOilTemp_enum = 26U;      /* Referenced by: '<S933>/Constant14' */
uint8 KFOC_ADCSicUTemp_enum = 30U;     /* Referenced by: '<S933>/Constant4' */
uint8 KFOC_ADCSicVTemp_enum = 31U;     /* Referenced by: '<S933>/Constant5' */
uint8 KFOC_ADCSicWTemp_enum = 32U;     /* Referenced by: '<S933>/Constant6' */
boolean KHAL_CAN3BMS1E2E_flg = true_MatlabRTW;
                              /* Referenced by: '<S135>/KHAL_CAN3BMS1E2E_flg' */
boolean KHAL_CAN3BMS6E2E_flg = true_MatlabRTW;
                              /* Referenced by: '<S136>/KHAL_CAN3BMS6E2E_flg' */
boolean KHAL_CAN3TxReq_flg = true_MatlabRTW;/* Referenced by: '<S7>/Constant2' */
boolean KHAL_CAN_MCU_R1TxReq_flg = true_MatlabRTW;/* Referenced by: '<S7>/Constant' */
boolean KINP_ActiveDischReq_flg_defval = false_MatlabRTW;/* Referenced by: '<S397>/defval' */
boolean KINP_ActiveDischReq_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S397>/ovrdflg' */
boolean KINP_ActiveDischReq_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S397>/ovrdval' */
boolean KINP_BMS1CSErr_flg_defval = false_MatlabRTW;/* Referenced by: '<S352>/defval' */
boolean KINP_BMS1CSErr_flg_ovrdflg = true_MatlabRTW;/* Referenced by: '<S352>/ovrdflg' */
boolean KINP_BMS1CSErr_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S352>/ovrdval' */
boolean KINP_BMS1RCErr_flg_defval = false_MatlabRTW;/* Referenced by: '<S353>/defval' */
boolean KINP_BMS1RCErr_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S353>/ovrdflg' */
boolean KINP_BMS1RCErr_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S353>/ovrdval' */
boolean KINP_BMS6CSErr_flg_defval = false_MatlabRTW;/* Referenced by: '<S367>/defval' */
boolean KINP_BMS6CSErr_flg_ovrdflg = true_MatlabRTW;/* Referenced by: '<S367>/ovrdflg' */
boolean KINP_BMS6CSErr_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S367>/ovrdval' */
boolean KINP_BMS6RCErr_flg_defval = false_MatlabRTW;/* Referenced by: '<S368>/defval' */
boolean KINP_BMS6RCErr_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S368>/ovrdflg' */
boolean KINP_BMS6RCErr_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S368>/ovrdval' */
uint8 KINP_BatteryMode_enum_defval = 0U;/* Referenced by: '<S382>/defval' */
boolean KINP_BatteryMode_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S382>/ovrdflg' */
uint8 KINP_BatteryMode_enum_ovrdval = 0U;/* Referenced by: '<S382>/ovrdval' */
boolean KINP_CANMsgInvalidBMS1_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S317>/ovrdflg' */
boolean KINP_CANMsgInvalidBMS1_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S317>/ovrdval' */
boolean KINP_CANMsgInvalidBMS6_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S318>/ovrdflg' */
boolean KINP_CANMsgInvalidBMS6_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S318>/ovrdval' */
boolean KINP_CANMsgInvalidEOPFVTRLocal1_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S510>/ovrdflg' */
boolean KINP_CANMsgInvalidEOPFVTRLocal1_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S510>/ovrdval' */
boolean KINP_CANMsgInvalidFD3C1000_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S319>/ovrdflg' */
boolean KINP_CANMsgInvalidFD3C1000_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S319>/ovrdval' */
boolean KINP_CANMsgInvalidFD3VCU1_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S320>/ovrdflg' */
boolean KINP_CANMsgInvalidFD3VCU1_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S320>/ovrdval' */
boolean KINP_CANMsgInvalidFD3VCU2_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S321>/ovrdflg' */
boolean KINP_CANMsgInvalidFD3VCU2_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S321>/ovrdval' */
boolean KINP_CANMsgInvalidFD3VCU5_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S322>/ovrdflg' */
boolean KINP_CANMsgInvalidFD3VCU5_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S322>/ovrdval' */
boolean KINP_CANMsgInvalidGW3CE1000_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S323>/ovrdflg' */
boolean KINP_CANMsgInvalidGW3CE1000_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S323>/ovrdval' */
uint8 KINP_CSVCU1_enum_defval = 0U;    /* Referenced by: '<S398>/defval' */
boolean KINP_CSVCU1_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S398>/ovrdflg' */
uint8 KINP_CSVCU1_enum_ovrdval = 0U;   /* Referenced by: '<S398>/ovrdval' */
uint8 KINP_CSVCU2CAN1_enum_defval = 0U;/* Referenced by: '<S422>/defval' */
boolean KINP_CSVCU2CAN1_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S422>/ovrdflg' */
uint8 KINP_CSVCU2CAN1_enum_ovrdval = 0U;/* Referenced by: '<S422>/ovrdval' */
float32 KINP_EOPFVTRActualSpdSta_rpm_defval = 0.0F;/* Referenced by: '<S515>/defval' */
boolean KINP_EOPFVTRActualSpdSta_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S515>/ovrdflg' */
float32 KINP_EOPFVTRActualSpdSta_rpm_ovrdval = 0.0F;/* Referenced by: '<S515>/ovrdval' */
boolean KINP_EOPFVTRCSInvalidSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S516>/defval' */
boolean KINP_EOPFVTRCSInvalidSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S516>/ovrdflg' */
boolean KINP_EOPFVTRCSInvalidSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S516>/ovrdval' */
boolean KINP_EOPFVTRCanLossSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S517>/defval' */
boolean KINP_EOPFVTRCanLossSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S517>/ovrdflg' */
boolean KINP_EOPFVTRCanLossSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S517>/ovrdval' */
boolean KINP_EOPFVTREnableOffSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S518>/defval' */
boolean KINP_EOPFVTREnableOffSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S518>/ovrdflg' */
boolean KINP_EOPFVTREnableOffSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S518>/ovrdval' */
boolean KINP_EOPFVTRHallSigErrSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S519>/defval' */
boolean KINP_EOPFVTRHallSigErrSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S519>/ovrdflg' */
boolean KINP_EOPFVTRHallSigErrSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S519>/ovrdval' */
uint8 KINP_EOPFVTRLocal1CSSta_enum_defval = 0U;/* Referenced by: '<S520>/defval' */
boolean KINP_EOPFVTRLocal1CSSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S520>/ovrdflg' */
uint8 KINP_EOPFVTRLocal1CSSta_enum_ovrdval = 0U;/* Referenced by: '<S520>/ovrdval' */
uint8 KINP_EOPFVTRLocal1RCSta_enum_defval = 0U;/* Referenced by: '<S521>/defval' */
boolean KINP_EOPFVTRLocal1RCSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S521>/ovrdflg' */
uint8 KINP_EOPFVTRLocal1RCSta_enum_ovrdval = 0U;/* Referenced by: '<S521>/ovrdval' */
uint8 KINP_EOPFVTROverTempBCKSta_enum_defval = 0U;/* Referenced by: '<S522>/defval' */
boolean KINP_EOPFVTROverTempBCKSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S522>/ovrdflg' */
uint8 KINP_EOPFVTROverTempBCKSta_enum_ovrdval = 0U;/* Referenced by: '<S522>/ovrdval' */
boolean KINP_EOPFVTROverTempSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S523>/defval' */
boolean KINP_EOPFVTROverTempSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S523>/ovrdflg' */
boolean KINP_EOPFVTROverTempSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S523>/ovrdval' */
uint8 KINP_EOPFVTROverVolSta_enum_defval = 0U;/* Referenced by: '<S524>/defval' */
boolean KINP_EOPFVTROverVolSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S524>/ovrdflg' */
uint8 KINP_EOPFVTROverVolSta_enum_ovrdval = 0U;/* Referenced by: '<S524>/ovrdval' */
boolean KINP_EOPFVTRPumpReadySta_flg_defval = false_MatlabRTW;/* Referenced by: '<S525>/defval' */
boolean KINP_EOPFVTRPumpReadySta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S525>/ovrdflg' */
boolean KINP_EOPFVTRPumpReadySta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S525>/ovrdval' */
boolean KINP_EOPFVTRRCInvalidSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S526>/defval' */
boolean KINP_EOPFVTRRCInvalidSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S526>/ovrdflg' */
boolean KINP_EOPFVTRRCInvalidSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S526>/ovrdval' */
uint8 KINP_EOPFVTRRunStatusSta_enum_defval = 0U;/* Referenced by: '<S527>/defval' */
boolean KINP_EOPFVTRRunStatusSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S527>/ovrdflg' */
uint8 KINP_EOPFVTRRunStatusSta_enum_ovrdval = 0U;/* Referenced by: '<S527>/ovrdval' */
boolean KINP_EOPFVTRStartFailureSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S528>/defval' */
boolean KINP_EOPFVTRStartFailureSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S528>/ovrdflg' */
boolean KINP_EOPFVTRStartFailureSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S528>/ovrdval' */
uint8 KINP_EOPFVTRUnderVolSta_enum_defval = 0U;/* Referenced by: '<S529>/defval' */
boolean KINP_EOPFVTRUnderVolSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S529>/ovrdflg' */
uint8 KINP_EOPFVTRUnderVolSta_enum_ovrdval = 0U;/* Referenced by: '<S529>/ovrdval' */
float32 KINP_FDCVCURrSpdMaxReq_rpm_defval = 0.0F;/* Referenced by: '<S442>/defval' */
boolean KINP_FDCVCURrSpdMaxReq_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S442>/ovrdflg' */
float32 KINP_FDCVCURrSpdMaxReq_rpm_ovrdval = 0.0F;/* Referenced by: '<S442>/ovrdval' */
float32 KINP_FDCVCURrSpdMinReq_rpm_defval = 0.0F;/* Referenced by: '<S443>/defval' */
boolean KINP_FDCVCURrSpdMinReq_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S443>/ovrdflg' */
float32 KINP_FDCVCURrSpdMinReq_rpm_ovrdval = 0.0F;/* Referenced by: '<S443>/ovrdval' */
uint8 KINP_FDCVCURrTMCtrlModeReq_enum_defval = 0U;/* Referenced by: '<S444>/defval' */
boolean KINP_FDCVCURrTMCtrlModeReq_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S444>/ovrdflg' */
uint8 KINP_FDCVCURrTMCtrlModeReq_enum_ovrdval = 0U;/* Referenced by: '<S444>/ovrdval' */
float32 KINP_FDCVCURrTMSpdReq_rpm_defval = 0.0F;/* Referenced by: '<S445>/defval' */
boolean KINP_FDCVCURrTMSpdReq_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S445>/ovrdflg' */
float32 KINP_FDCVCURrTMSpdReq_rpm_ovrdval = 0.0F;/* Referenced by: '<S445>/ovrdval' */
float32 KINP_FDCVCURrTMTqReq_Nm_defval = 0.0F;/* Referenced by: '<S446>/defval' */
boolean KINP_FDCVCURrTMTqReq_Nm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S446>/ovrdflg' */
float32 KINP_FDCVCURrTMTqReq_Nm_ovrdval = 0.0F;/* Referenced by: '<S446>/ovrdval' */
float32 KINP_FDCVCURrTqMaxReq_Nm_defval = 0.0F;/* Referenced by: '<S447>/defval' */
boolean KINP_FDCVCURrTqMaxReq_Nm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S447>/ovrdflg' */
float32 KINP_FDCVCURrTqMaxReq_Nm_ovrdval = 0.0F;/* Referenced by: '<S447>/ovrdval' */
float32 KINP_FDCVCURrTqMinReq_Nm_defval = 0.0F;/* Referenced by: '<S448>/defval' */
boolean KINP_FDCVCURrTqMinReq_Nm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S448>/ovrdflg' */
float32 KINP_FDCVCURrTqMinReq_Nm_ovrdval = 0.0F;/* Referenced by: '<S448>/ovrdval' */
boolean KINP_HVBContactorSta_flg_defval = false_MatlabRTW;/* Referenced by: '<S369>/defval' */
boolean KINP_HVBContactorSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S369>/ovrdflg' */
boolean KINP_HVBContactorSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S369>/ovrdval' */
float32 KINP_HVBattVolt_V_defval = 0.0F;/* Referenced by: '<S354>/defval' */
boolean KINP_HVBattVolt_V_ovrdflg = false_MatlabRTW;/* Referenced by: '<S354>/ovrdflg' */
float32 KINP_HVBattVolt_V_ovrdval = 0.0F;/* Referenced by: '<S354>/ovrdval' */
float32 KINP_IVITimeDay_DAY_defval = 0.0F;/* Referenced by: '<S477>/defval' */
boolean KINP_IVITimeDay_DAY_ovrdflg = false_MatlabRTW;/* Referenced by: '<S477>/ovrdflg' */
float32 KINP_IVITimeDay_DAY_ovrdval = 0.0F;/* Referenced by: '<S477>/ovrdval' */
float32 KINP_IVITimeHour_hr_defval = 0.0F;/* Referenced by: '<S478>/defval' */
boolean KINP_IVITimeHour_hr_ovrdflg = false_MatlabRTW;/* Referenced by: '<S478>/ovrdflg' */
float32 KINP_IVITimeHour_hr_ovrdval = 0.0F;/* Referenced by: '<S478>/ovrdval' */
float32 KINP_IVITimeMinute_min_defval = 0.0F;/* Referenced by: '<S479>/defval' */
boolean KINP_IVITimeMinute_min_ovrdflg = false_MatlabRTW;/* Referenced by: '<S479>/ovrdflg' */
float32 KINP_IVITimeMinute_min_ovrdval = 0.0F;/* Referenced by: '<S479>/ovrdval' */
float32 KINP_IVITimeMonth_MONTH_defval = 0.0F;/* Referenced by: '<S480>/defval' */
boolean KINP_IVITimeMonth_MONTH_ovrdflg = false_MatlabRTW;/* Referenced by: '<S480>/ovrdflg' */
float32 KINP_IVITimeMonth_MONTH_ovrdval = 0.0F;/* Referenced by: '<S480>/ovrdval' */
float32 KINP_IVITimeSecond_s_defval = 0.0F;/* Referenced by: '<S481>/defval' */
boolean KINP_IVITimeSecond_s_ovrdflg = false_MatlabRTW;/* Referenced by: '<S481>/ovrdflg' */
float32 KINP_IVITimeSecond_s_ovrdval = 0.0F;/* Referenced by: '<S481>/ovrdval' */
uint8 KINP_PwrSta_enum_defval = 0U;    /* Referenced by: '<S399>/defval' */
boolean KINP_PwrSta_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S399>/ovrdflg' */
uint8 KINP_PwrSta_enum_ovrdval = 0U;   /* Referenced by: '<S399>/ovrdval' */
uint8 KINP_RCVCU1_enum_defval = 0U;    /* Referenced by: '<S400>/defval' */
boolean KINP_RCVCU1_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S400>/ovrdflg' */
uint8 KINP_RCVCU1_enum_ovrdval = 0U;   /* Referenced by: '<S400>/ovrdval' */
uint8 KINP_RCVCU2CAN1_enum_defval = 0U;/* Referenced by: '<S423>/defval' */
boolean KINP_RCVCU2CAN1_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S423>/ovrdflg' */
uint8 KINP_RCVCU2CAN1_enum_ovrdval = 0U;/* Referenced by: '<S423>/ovrdval' */
boolean KINP_RrActvDmpDisabReq_flg_defval = false_MatlabRTW;/* Referenced by: '<S424>/defval' */
boolean KINP_RrActvDmpDisabReq_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S424>/ovrdflg' */
boolean KINP_RrActvDmpDisabReq_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S424>/ovrdval' */
float32 KINP_RrCoolantflow_Lpmin_defval = 0.0F;/* Referenced by: '<S383>/defval' */
boolean KINP_RrCoolantflow_Lpmin_ovrdflg = false_MatlabRTW;/* Referenced by: '<S383>/ovrdflg' */
float32 KINP_RrCoolantflow_Lpmin_ovrdval = 0.0F;/* Referenced by: '<S383>/ovrdval' */
float32 KINP_RrCoolanttemp_C_defval = 0.0F;/* Referenced by: '<S384>/defval' */
boolean KINP_RrCoolanttemp_C_ovrdflg = false_MatlabRTW;/* Referenced by: '<S384>/ovrdflg' */
float32 KINP_RrCoolanttemp_C_ovrdval = 0.0F;/* Referenced by: '<S384>/ovrdval' */
boolean KINP_RrMCUEnaReq_flg_defval = false_MatlabRTW;/* Referenced by: '<S425>/defval' */
boolean KINP_RrMCUEnaReq_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S425>/ovrdflg' */
boolean KINP_RrMCUEnaReq_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S425>/ovrdval' */
uint8 KINP_ShiftGearPosn_enum_defval = 0U;/* Referenced by: '<S401>/defval' */
boolean KINP_ShiftGearPosn_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S401>/ovrdflg' */
uint8 KINP_ShiftGearPosn_enum_ovrdval = 0U;/* Referenced by: '<S401>/ovrdval' */
float32 KINP_VehSpeed_kph_defval = 0.0F;/* Referenced by: '<S482>/defval' */
boolean KINP_VehSpeed_kph_ovrdflg = false_MatlabRTW;/* Referenced by: '<S482>/ovrdflg' */
float32 KINP_VehSpeed_kph_ovrdval = 0.0F;/* Referenced by: '<S482>/ovrdval' */
boolean KOPM_FakeKL15_flg = false_MatlabRTW;/* Referenced by: '<S2>/Constant3' */
boolean KOPM_IVTROpMode_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S597>/Constant3' */
uint8 KOPM_IVTROpMode_enum_ovrdval = 0U;/* Referenced by: '<S597>/Constant4' */
boolean KOPM_MotMod_enum_ovrdflg = false_MatlabRTW;
                              /* Referenced by: '<S597>/OpMod_stMotActTrig_C' */
uint8 KOPM_MotMod_enum_ovrdval = 1U;
                               /* Referenced by: '<S597>/OpMod_stMotActMor_C' */
boolean KOPM_PsvDischrgEna_flg_ovrdflg = true_MatlabRTW;
                             /* Referenced by: '<S597>/OpMod_stMotActTrig_C1' */
boolean KOPM_PsvDischrgEna_flg_ovrdval = false_MatlabRTW;
                             /* Referenced by: '<S597>/OpMod_stMotActTrig_C2' */
float32 KOUTP_ADCKL15_V_maxval = 100000.0F;/* Referenced by: '<S626>/_maxval' */
float32 KOUTP_ADCKL15_V_minval = -100000.0F;/* Referenced by: '<S626>/_minval' */
boolean KOUTP_ADCKL15_V_ovrdflg = false_MatlabRTW;/* Referenced by: '<S627>/_ovrdflg' */
float32 KOUTP_ADCKL15_V_ovrdval = 0.0F;/* Referenced by: '<S627>/_ovrdval' */
float32 KOUTP_ADCKL30_V_maxval = 100000.0F;/* Referenced by: '<S630>/_maxval' */
float32 KOUTP_ADCKL30_V_minval = -100000.0F;/* Referenced by: '<S630>/_minval' */
boolean KOUTP_ADCKL30_V_ovrdflg = false_MatlabRTW;/* Referenced by: '<S631>/_ovrdflg' */
float32 KOUTP_ADCKL30_V_ovrdval = 0.0F;/* Referenced by: '<S631>/_ovrdval' */
boolean KOUTP_BoostOPSta_flg_maxval = true_MatlabRTW;/* Referenced by: '<S674>/_maxval' */
boolean KOUTP_BoostOPSta_flg_minval = false_MatlabRTW;/* Referenced by: '<S674>/_minval' */
boolean KOUTP_BoostOPSta_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S675>/_ovrdflg' */
boolean KOUTP_BoostOPSta_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S675>/_ovrdval' */
float32 KOUTP_BusCurr_A_maxval = 100000.0F;/* Referenced by: '<S654>/_maxval' */
float32 KOUTP_BusCurr_A_minval = -100000.0F;/* Referenced by: '<S654>/_minval' */
boolean KOUTP_BusCurr_A_ovrdflg = false_MatlabRTW;/* Referenced by: '<S655>/_ovrdflg' */
float32 KOUTP_BusCurr_A_ovrdval = 0.0F;/* Referenced by: '<S655>/_ovrdval' */
uint8 KOUTP_IVTROpMode_enum_maxval = 255U;/* Referenced by: '<S678>/_maxval' */
uint8 KOUTP_IVTROpMode_enum_minval = 0U;/* Referenced by: '<S678>/_minval' */
boolean KOUTP_IVTROpMode_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S679>/_ovrdflg' */
uint8 KOUTP_IVTROpMode_enum_ovrdval = 0U;/* Referenced by: '<S679>/_ovrdval' */
boolean KOUTP_MCUEna_flg_maxval = true_MatlabRTW;/* Referenced by: '<S682>/_maxval' */
boolean KOUTP_MCUEna_flg_minval = false_MatlabRTW;/* Referenced by: '<S682>/_minval' */
boolean KOUTP_MCUEna_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S683>/_ovrdflg' */
boolean KOUTP_MCUEna_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S683>/_ovrdval' */
uint8 KOUTP_MotMod_enum_maxval = 255U; /* Referenced by: '<S686>/_maxval' */
uint8 KOUTP_MotMod_enum_minval = 0U;   /* Referenced by: '<S686>/_minval' */
boolean KOUTP_MotMod_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S687>/_ovrdflg' */
uint8 KOUTP_MotMod_enum_ovrdval = 0U;  /* Referenced by: '<S687>/_ovrdval' */
float32 KOUTP_OilTemp_degC_maxval = 100000.0F;/* Referenced by: '<S634>/_maxval' */
float32 KOUTP_OilTemp_degC_minval = -100000.0F;/* Referenced by: '<S634>/_minval' */
boolean KOUTP_OilTemp_degC_ovrdflg = false_MatlabRTW;/* Referenced by: '<S635>/_ovrdflg' */
float32 KOUTP_OilTemp_degC_ovrdval = 0.0F;/* Referenced by: '<S635>/_ovrdval' */
float32 KOUTP_PwrEleAct_W_maxval = 100000.0F;/* Referenced by: '<S658>/_maxval' */
float32 KOUTP_PwrEleAct_W_minval = -100000.0F;/* Referenced by: '<S658>/_minval' */
boolean KOUTP_PwrEleAct_W_ovrdflg = false_MatlabRTW;/* Referenced by: '<S659>/_ovrdflg' */
float32 KOUTP_PwrEleAct_W_ovrdval = 0.0F;/* Referenced by: '<S659>/_ovrdval' */
float32 KOUTP_RotSpd_rpm_maxval = 100000.0F;/* Referenced by: '<S638>/_maxval' */
float32 KOUTP_RotSpd_rpm_minval = -100000.0F;/* Referenced by: '<S638>/_minval' */
boolean KOUTP_RotSpd_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S639>/_ovrdflg' */
float32 KOUTP_RotSpd_rpm_ovrdval = 0.0F;/* Referenced by: '<S639>/_ovrdval' */
boolean KOUTP_TMReady_flg_maxval = true_MatlabRTW;/* Referenced by: '<S690>/_maxval' */
boolean KOUTP_TMReady_flg_minval = false_MatlabRTW;/* Referenced by: '<S690>/_minval' */
boolean KOUTP_TMReady_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S691>/_ovrdflg' */
boolean KOUTP_TMReady_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S691>/_ovrdval' */
boolean KOUTP_bMotEnaReq_flg_maxval = true_MatlabRTW;/* Referenced by: '<S662>/_maxval' */
boolean KOUTP_bMotEnaReq_flg_minval = false_MatlabRTW;/* Referenced by: '<S662>/_minval' */
boolean KOUTP_bMotEnaReq_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S663>/_ovrdflg' */
boolean KOUTP_bMotEnaReq_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S663>/_ovrdval' */
float32 KOUTP_iDCurrAct_A_maxval = 100000.0F;/* Referenced by: '<S642>/_maxval' */
float32 KOUTP_iDCurrAct_A_minval = -100000.0F;/* Referenced by: '<S642>/_minval' */
boolean KOUTP_iDCurrAct_A_ovrdflg = false_MatlabRTW;/* Referenced by: '<S643>/_ovrdflg' */
float32 KOUTP_iDCurrAct_A_ovrdval = 0.0F;/* Referenced by: '<S643>/_ovrdval' */
float32 KOUTP_iQCurrAct_A_maxval = 100000.0F;/* Referenced by: '<S646>/_maxval' */
float32 KOUTP_iQCurrAct_A_minval = -100000.0F;/* Referenced by: '<S646>/_minval' */
boolean KOUTP_iQCurrAct_A_ovrdflg = false_MatlabRTW;/* Referenced by: '<S647>/_ovrdflg' */
float32 KOUTP_iQCurrAct_A_ovrdval = 0.0F;/* Referenced by: '<S647>/_ovrdval' */
float32 KOUTP_nEOPSpdReq_rpm_maxval = 100000.0F;/* Referenced by: '<S666>/_maxval' */
float32 KOUTP_nEOPSpdReq_rpm_minval = -100000.0F;/* Referenced by: '<S666>/_minval' */
boolean KOUTP_nEOPSpdReq_rpm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S667>/_ovrdflg' */
float32 KOUTP_nEOPSpdReq_rpm_ovrdval = 0.0F;/* Referenced by: '<S667>/_ovrdval' */
float32 KOUTP_tqTMTqMax_Nm_maxval = 100000.0F;/* Referenced by: '<S694>/_maxval' */
float32 KOUTP_tqTMTqMax_Nm_minval = -100000.0F;/* Referenced by: '<S694>/_minval' */
boolean KOUTP_tqTMTqMax_Nm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S695>/_ovrdflg' */
float32 KOUTP_tqTMTqMax_Nm_ovrdval = 0.0F;/* Referenced by: '<S695>/_ovrdval' */
float32 KOUTP_tqTMTqMin_Nm_maxval = 100000.0F;/* Referenced by: '<S698>/_maxval' */
float32 KOUTP_tqTMTqMin_Nm_minval = -100000.0F;/* Referenced by: '<S698>/_minval' */
boolean KOUTP_tqTMTqMin_Nm_ovrdflg = false_MatlabRTW;/* Referenced by: '<S699>/_ovrdflg' */
float32 KOUTP_tqTMTqMin_Nm_ovrdval = 0.0F;/* Referenced by: '<S699>/_ovrdval' */
float32 KOUTP_uDC_V_maxval = 100000.0F;/* Referenced by: '<S650>/_maxval' */
float32 KOUTP_uDC_V_minval = -100000.0F;/* Referenced by: '<S650>/_minval' */
boolean KOUTP_uDC_V_ovrdflg = false_MatlabRTW;/* Referenced by: '<S651>/_ovrdflg' */
float32 KOUTP_uDC_V_ovrdval = 0.0F;    /* Referenced by: '<S651>/_ovrdval' */
float32 KOUTP_volfCooltFlowTar_C_maxval = 1000.0F;/* Referenced by: '<S670>/_maxval' */
float32 KOUTP_volfCooltFlowTar_C_minval = -1000.0F;/* Referenced by: '<S670>/_minval' */
boolean KOUTP_volfCooltFlowTar_C_ovrdflg = false_MatlabRTW;/* Referenced by: '<S671>/_ovrdflg' */
float32 KOUTP_volfCooltFlowTar_C_ovrdval = 0.0F;/* Referenced by: '<S671>/_ovrdval' */
float32 KSYL_frqSwitchMax_Hz = 10000.0F;/* Referenced by: '<S12>/Constant2' */
float32 KSYL_nTMSpdMax_RPM = 20000.0F; /* Referenced by: '<S12>/Constant1' */
float32 KSYL_nTMSpdMin_RPM = -20000.0F;/* Referenced by: '<S12>/Constant' */
boolean LLCM_bTcooltFlowTrig_C = false_MatlabRTW;
                                 /* Referenced by: '<S590>/MPS_ReqMotSpdMor1' */
float32 LLCM_tlvtrATemp_C = 60.0F;     /* Referenced by: '<S590>/Constant1' */
float32 LLCM_tlvtrBTemp_C = 60.0F;     /* Referenced by: '<S590>/Constant2' */
float32 LLCM_tlvtrCTemp_C = 60.0F;     /* Referenced by: '<S590>/Constant3' */
float32 LLCM_volfcooltFlowMax_C = 10.0F;/* Referenced by: '<S590>/Constant4' */
float32 LLCM_volfcooltFlowMin_C = 10.0F;/* Referenced by: '<S590>/Constant5' */
float32 LLCM_volfcooltFlowMor_C = 10.0F;
                                 /* Referenced by: '<S590>/MPS_ReqMotSpdMor2' */
float32 LLCM_volfcooltFlowRampDown_C = 10.0F;
                                 /* Referenced by: '<S590>/MPS_ReqMotSpdMor9' */
float32 LLCM_volfcooltFlowRampUp_C = 10.0F;
                                 /* Referenced by: '<S590>/MPS_ReqMotSpdMor6' */
float32 MCRM_Eta_Y_null[4] = { 1.2F, 1.18F, 1.15F, 1.0F } ;
                                    /* Referenced by: '<S17>/MPEM_EtaY_value' */

float32 MCRM_MTPAIdGenMin_Z_A[1020] = { 1.30362904F, -1.92809796F, -5.1598258F,
  -8.39155293F, -14.3588104F, -20.9387207F, -28.9770794F, -37.1886902F,
  -45.7220612F, -54.2423706F, -62.7431107F, -71.5497894F, -80.8774F, -90.02845F,
  -98.7472534F, -107.574402F, -116.930298F, -126.319099F, -136.332306F,
  -146.345505F, -155.290604F, -164.167603F, -175.158905F, -186.523193F,
  -197.661606F, -208.743393F, -219.223404F, -229.543396F, -239.461F,
  -249.258408F, -259.229187F, -269.235504F, -282.265106F, -295.525513F,
  -305.383209F, -315.240814F, -326.297607F, -337.868286F, -351.956696F,
  -365.457214F, -376.537109F, -387.251801F, -397.224915F, -408.094788F,
  -423.343597F, -439.184296F, -455.098907F, -470.252899F, -482.097107F,
  -492.311188F, -497.928894F, 1.268484F, -1.98344195F, -5.23536682F,
  -8.48729324F, -13.8836F, -20.3557205F, -29.9713F, -38.8533211F, -46.588F,
  -54.1644211F, -61.5473785F, -69.7013397F, -78.8773F, -88.3486786F, -98.36866F,
  -108.608F, -119.542099F, -130.162292F, -138.682098F, -147.268799F,
  -158.019104F, -168.769394F, -178.338501F, -187.845398F, -197.95F, -208.121F,
  -218.361694F, -228.630905F, -238.5793F, -248.376694F, -259.268188F,
  -270.544189F, -282.049F, -293.611115F, -305.571503F, -317.596802F,
  -328.550507F, -339.521698F, -351.650208F, -363.621094F, -373.998505F,
  -384.486115F, -397.621399F, -410.954F, -424.582611F, -438.20459F, -451.948792F,
  -466.256592F, -480.331512F, -494.263885F, -494.263885F, 3.46865F, -1.35633397F,
  -6.18131924F, -11.0063F, -15.80972F, -21.6553307F, -30.6309395F, -39.0853615F,
  -46.8200493F, -54.9426308F, -63.4854507F, -72.41F, -81.7826691F, -90.9491425F,
  -99.7930908F, -108.803902F, -118.204201F, -127.73F, -137.790894F, -147.7491F,
  -156.668701F, -165.611694F, -176.866302F, -188.120804F, -199.758408F,
  -211.377197F, -221.596F, -231.814804F, -241.3255F, -250.828903F, -261.806702F,
  -272.799286F, -284.2435F, -295.715912F, -307.868408F, -319.832611F, -330.73F,
  -342.063599F, -354.638885F, -366.965698F, -378.850311F, -390.820404F,
  -402.854889F, -415.626587F, -428.606201F, -441.585693F, -454.9534F,
  -468.903503F, -482.636688F, -494.263885F, -494.263885F, 1.17092597F,
  -2.0809989F, -5.33292484F, -8.58485126F, -14.0811596F, -20.51334F,
  -29.2881298F, -37.9760513F, -46.5534F, -55.1134911F, -63.656311F, -73.2325F,
  -83.9281693F, -93.2721863F, -100.749603F, -108.803902F, -118.204201F, -127.73F,
  -137.790894F, -148.081802F, -160.698593F, -173.256F, -182.901505F,
  -192.546906F, -201.062897F, -209.544F, -219.533F, -229.853F, -239.519806F,
  -249.0233F, -259.674103F, -270.611786F, -282.049F, -293.611115F, -305.464386F,
  -317.365F, -329.879395F, -342.360199F, -353.590607F, -364.908F, -376.596802F,
  -388.438507F, -400.54071F, -412.345795F, -423.944611F, -436.919495F,
  -450.423798F, -463.553192F, -476.89151F, -490.570496F, -494.263885F, 1.93375F,
  -1.87827599F, -5.69030285F, -9.50233F, -14.5508404F, -21.1885891F, -31.6867F,
  -41.0435486F, -49.0055313F, -56.0593796F, -62.2749481F, -70.3334274F,
  -80.7374115F, -90.56604F, -99.3261566F, -108.229301F, -117.585197F,
  -126.822701F, -135.192093F, -143.642105F, -156.040497F, -168.439F,
  -180.086395F, -191.6772F, -207.653702F, -224.117599F, -236.561096F,
  -248.557907F, -264.994904F, -281.904907F, -299.346802F, -316.504303F,
  -333.109894F, -349.54F, -365.862305F, -386.249512F, -406.323F, -426.138306F,
  -447.281097F, -471.995911F, -500.669708F, -535.574524F, -564.22467F,
  -593.804504F, -593.804504F, -593.804504F, -593.804504F, -593.804504F,
  -593.804504F, -593.804504F, -593.804504F, 1.07740796F, -2.15431905F,
  -5.38604689F, -8.61777401F, -16.2733803F, -23.4875603F, -29.2641602F,
  -36.5683784F, -45.8976F, -57.0804787F, -70.3536606F, -85.0391312F,
  -101.254601F, -117.188797F, -132.935394F, -149.093796F, -165.333694F,
  -180.915497F, -197.241302F, -215.148102F, -231.717804F, -247.610306F,
  -261.953796F, -277.292786F, -295.465393F, -313.841492F, -331.57431F,
  -347.795898F, -368.11911F, -390.974F, -417.454803F, -444.84079F, -469.723511F,
  -498.125702F, -531.61377F, -579.112488F, -616.4104F, -616.4104F, -616.4104F,
  -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F,
  -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F,
  1.10588801F, -2.14603806F, -5.397964F, -8.64989F, -21.5423F, -35.7406197F,
  -52.6289215F, -69.4885712F, -86.3143234F, -103.020599F, -120.152397F,
  -137.508499F, -154.263596F, -171.271103F, -188.464294F, -205.264099F,
  -223.291107F, -242.146301F, -259.637085F, -274.705292F, -288.735291F,
  -309.862396F, -329.721588F, -352.022095F, -377.193695F, -400.839111F,
  -428.5672F, -460.270294F, -499.304688F, -591.635315F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -12.1928701F, -23.5958195F, -34.9987717F, -48.3635406F, -61.9133606F,
  -74.6562881F, -88.845253F, -103.931099F, -120.337601F, -136.755707F,
  -153.473907F, -170.769302F, -189.326797F, -207.492599F, -225.493393F,
  -245.077499F, -264.740906F, -286.367F, -308.722595F, -330.301788F,
  -353.757385F, -379.171295F, -409.204315F, -441.812F, -478.511597F,
  -541.161377F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -42.4754105F, -54.5544891F, -66.6335678F, -78.7126465F,
  -91.2031326F, -106.220901F, -121.7892F, -137.996201F, -155.377106F,
  -172.528702F, -189.947906F, -208.048294F, -228.886093F, -249.641098F,
  -270.406799F, -291.021698F, -312.215302F, -336.198914F, -363.003815F,
  -392.084106F, -424.231598F, -466.136597F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -55.2997513F, -71.3277F, -87.3556366F,
  -103.383598F, -119.411499F, -135.439499F, -151.467407F, -167.859497F,
  -185.404495F, -203.459106F, -222.812F, -243.431107F, -264.831696F,
  -287.359497F, -310.799F, -332.931091F, -361.361389F, -397.771515F,
  -438.020691F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -55.2997513F, -71.3277F,
  -87.3556366F, -103.383598F, -119.411499F, -135.439499F, -151.467407F,
  -167.859497F, -185.404495F, -203.459106F, -222.812F, -243.431107F,
  -264.831696F, -287.359497F, -310.799F, -332.931091F, -361.361389F,
  -397.771515F, -438.020691F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -55.2997513F,
  -71.3277F, -87.3556366F, -103.383598F, -119.411499F, -135.439499F,
  -151.467407F, -167.859497F, -185.404495F, -203.459106F, -222.812F,
  -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F } ;/* Referenced by:
                                                                      * '<S28>/Id_Gen_Map'
                                                                      * '<S28>/530MTPAIdGen'
                                                                      */

float32 MCRM_MTPAIdGen_Z_A[1020] = { 3.56961799F, -1.22558296F, -6.0207839F,
  -10.81598F, -14.8963299F, -20.1387806F, -30.6368904F, -39.5245209F,
  -45.4212685F, -51.8819695F, -59.1214485F, -68.1219101F, -79.6564865F,
  -90.3165894F, -99.1184235F, -108.748901F, -121.3172F, -133.152802F,
  -140.084198F, -147.054306F, -157.856598F, -168.658798F, -178.157104F,
  -187.572205F, -198.1129F, -208.821701F, -219.223404F, -229.543396F, -239.461F,
  -249.258408F, -259.229187F, -269.235504F, -282.265106F, -295.525513F,
  -305.383209F, -315.240814F, -326.297607F, -337.868286F, -351.956696F,
  -365.457214F, -376.537109F, -387.251801F, -397.224915F, -408.094788F,
  -423.343597F, -439.184296F, -455.098907F, -470.252899F, -482.097107F,
  -492.311188F, -497.928894F, 1.05379403F, -3.25764489F, -7.56908417F,
  -11.8805199F, -18.9816494F, -25.2891293F, -28.7752F, -34.8897781F,
  -45.1156082F, -54.6009216F, -63.1437416F, -72.0351F, -81.4077682F, -90.61026F,
  -99.496727F, -108.133499F, -116.095F, -124.741203F, -136.306305F, -147.814697F,
  -158.669296F, -169.496094F, -178.956894F, -188.417694F, -198.299896F,
  -208.199707F, -218.361694F, -228.630905F, -238.5793F, -248.376694F,
  -259.268188F, -270.544189F, -282.049F, -293.611115F, -305.571503F,
  -317.596802F, -328.550507F, -339.521698F, -351.650208F, -363.621094F,
  -373.998505F, -384.486115F, -397.621399F, -410.954F, -424.582611F, -438.20459F,
  -451.948792F, -466.256592F, -480.331512F, -494.263885F, -494.263885F,
  1.20344603F, -2.04848F, -5.30040598F, -8.55233192F, -13.3341F, -18.9527607F,
  -26.6617508F, -35.9875298F, -47.2893791F, -56.7020912F, -64.2997513F,
  -72.1624374F, -80.2901611F, -89.2926712F, -99.4085388F, -109.289597F,
  -118.734596F, -128.345703F, -138.454697F, -148.691498F, -159.599106F,
  -170.347595F, -179.808395F, -189.347504F, -200.374405F, -211.377197F,
  -221.596F, -231.814804F, -241.3255F, -250.828903F, -261.806702F, -272.799286F,
  -284.2435F, -295.715912F, -307.868408F, -319.832611F, -330.73F, -342.063599F,
  -354.638885F, -366.965698F, -378.850311F, -390.820404F, -402.854889F,
  -415.626587F, -428.606201F, -441.585693F, -454.9534F, -468.903503F,
  -482.636688F, -494.263885F, -494.263885F, 1.16745F, -2.10492897F, -5.37730694F,
  -8.64968491F, -14.1924801F, -20.9121399F, -30.4569607F, -38.2527695F,
  -45.5552711F, -53.4928207F, -61.9499588F, -70.826828F, -80.0471268F,
  -89.0338211F, -97.7674408F, -107.394302F, -118.361F, -129.037903F,
  -139.098801F, -149.369598F, -160.384705F, -171.104507F, -180.565201F,
  -190.083099F, -199.982895F, -209.882599F, -220.197403F, -230.568695F,
  -240.2686F, -249.868F, -261.225098F, -272.799286F, -284.2435F, -295.708313F,
  -307.670898F, -319.713409F, -332.341614F, -344.622F, -355.912689F,
  -367.362701F, -379.051392F, -390.902F, -402.869598F, -415.810699F,
  -429.068115F, -442.605F, -456.137085F, -469.664398F, -483.463287F,
  -494.263885F, -494.263885F, 2.21323F, -1.54388702F, -5.30100393F, -9.21396732F,
  -14.5295496F, -20.9675F, -29.7905102F, -38.0143509F, -45.6390305F,
  -54.3981895F, -63.9788818F, -73.5195618F, -83.0300598F, -92.1649704F,
  -100.966797F, -110.064598F, -119.554901F, -129.239105F, -139.3F, -149.097397F,
  -158.060104F, -167.459793F, -178.992905F, -190.350204F, -200.710403F,
  -211.070602F, -222.633194F, -234.195694F, -244.9189F, -255.642197F,
  -266.806396F, -277.967102F, -288.341797F, -298.737213F, -309.37149F,
  -320.288605F, -332.586212F, -344.59079F, -355.761414F, -367.228699F,
  -379.180115F, -391.062408F, -402.89859F, -415.277496F, -427.84F, -441.132202F,
  -454.917F, -469.505188F, -483.463287F, -494.263885F, -494.263885F, 1.71738803F,
  -2.36105394F, -6.43949604F, -10.5339499F, -15.1461897F, -20.5975208F,
  -27.6071701F, -35.8281403F, -45.1233215F, -53.8904305F, -62.3055F,
  -70.4532928F, -78.4153519F, -86.6392822F, -95.0954285F, -104.487396F,
  -115.1716F, -125.508698F, -135.073105F, -144.809692F, -155.698898F,
  -165.845093F, -169.305F, -175.282593F, -191.331F, -207.379501F, -219.017F,
  -229.337F, -240.244507F, -251.347702F, -262.643402F, -273.981293F,
  -285.568207F, -297.189209F, -307.677704F, -318.093903F, -330.69989F,
  -343.599792F, -358.31781F, -373.80069F, -390.048401F, -396.222504F,
  -396.222504F, -396.222504F, -396.222504F, -396.222504F, -396.222504F,
  -396.222504F, -396.222504F, -396.222504F, -396.222504F, 0.299312413F,
  -2.16101599F, -4.62134314F, -7.32277107F, -14.6050901F, -22.1745F, -30.3012F,
  -38.63937F, -47.1727295F, -57.0772896F, -68.0162506F, -81.7146606F,
  -97.4947586F, -111.747498F, -125.213501F, -140.194504F, -155.680603F,
  -171.359207F, -188.585495F, -207.619202F, -222.786F, -236.133102F, -237.7715F,
  -239.171F, -240.570404F, -246.302902F, -261.243103F, -276.866913F, -293.07309F,
  -309.473206F, -326.061096F, -343.591888F, -363.217194F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, 2.31303811F, -2.00962305F, -6.33228397F,
  -10.6227598F, -14.4089603F, -21.6977196F, -35.4912F, -52.2639618F,
  -71.8991776F, -88.6528168F, -105.535698F, -123.348602F, -139.295303F,
  -154.778503F, -172.2061F, -188.926605F, -205.136795F, -222.479095F,
  -240.459106F, -257.552094F, -261.573395F, -265.594696F, -269.616F,
  -279.411285F, -297.180206F, -315.199402F, -333.942505F, -353.789398F,
  -376.415192F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, 0.842858493F, -2.94112897F,
  -6.72511721F, -10.50986F, -14.3191204F, -22.2139606F, -38.403759F,
  -54.8450089F, -71.5183792F, -87.7648926F, -104.142097F, -121.6642F,
  -138.655807F, -155.263107F, -172.418594F, -189.304199F, -205.839F,
  -224.103302F, -242.566696F, -260.958313F, -279.52951F, -298.633087F,
  -318.554688F, -339.865387F, -360.983398F, -381.721497F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  11.3967505F, -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F,
  -71.8025589F, -89.2560806F, -105.9105F, -122.375702F, -139.072098F,
  -156.162292F, -173.628693F, -191.698196F, -208.409103F, -225.664505F,
  -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  11.3967505F, -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F,
  -71.8025589F, -89.2560806F, -105.9105F, -122.375702F, -139.072098F,
  -156.162292F, -173.628693F, -191.698196F, -208.409103F, -225.664505F,
  -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F }
;                                      /* Referenced by:
                                        * '<S27>/696Id_Gen_Map'
                                        * '<S27>/696MTPAIdGen'
                                        */

float32 MCRM_MTPAIdMotMin_Z_A[1020] = { 1.30362904F, -1.92809796F, -5.1598258F,
  -8.39155293F, -14.3588104F, -20.9387207F, -28.9770794F, -37.1886902F,
  -45.7220612F, -54.2423706F, -62.7431107F, -71.5497894F, -80.8774F, -90.02845F,
  -98.7472534F, -107.574402F, -116.930298F, -126.319099F, -136.332306F,
  -146.345505F, -155.290604F, -164.167603F, -175.158905F, -186.523193F,
  -197.661606F, -208.743393F, -219.223404F, -229.543396F, -239.461F,
  -249.258408F, -259.229187F, -269.235504F, -282.265106F, -295.525513F,
  -305.383209F, -315.240814F, -326.297607F, -337.868286F, -351.956696F,
  -365.457214F, -376.537109F, -387.251801F, -397.224915F, -408.094788F,
  -423.343597F, -439.184296F, -455.098907F, -470.252899F, -482.097107F,
  -492.311188F, -497.928894F, 1.268484F, -1.98344195F, -5.23536682F,
  -8.48729324F, -13.8836F, -20.3557205F, -29.9713F, -38.8533211F, -46.588F,
  -54.1644211F, -61.5473785F, -69.7013397F, -78.8773F, -88.3486786F, -98.36866F,
  -108.608F, -119.542099F, -130.162292F, -138.682098F, -147.268799F,
  -158.019104F, -168.769394F, -178.338501F, -187.845398F, -197.95F, -208.121F,
  -218.361694F, -228.630905F, -238.5793F, -248.376694F, -259.268188F,
  -270.544189F, -282.049F, -293.611115F, -305.571503F, -317.596802F,
  -328.550507F, -339.521698F, -351.650208F, -363.621094F, -373.998505F,
  -384.486115F, -397.621399F, -410.954F, -424.582611F, -438.20459F, -451.948792F,
  -466.256592F, -480.331512F, -494.263885F, -494.263885F, 3.46865F, -1.35633397F,
  -6.18131924F, -11.0063F, -15.80972F, -21.6553307F, -30.6309395F, -39.0853615F,
  -46.8200493F, -54.9426308F, -63.4854507F, -72.41F, -81.7826691F, -90.9491425F,
  -99.7930908F, -108.803902F, -118.204201F, -127.73F, -137.790894F, -147.7491F,
  -156.668701F, -165.611694F, -176.866302F, -188.120804F, -199.758408F,
  -211.377197F, -221.596F, -231.814804F, -241.3255F, -250.828903F, -261.806702F,
  -272.799286F, -284.2435F, -295.715912F, -307.868408F, -319.832611F, -330.73F,
  -342.063599F, -354.638885F, -366.965698F, -378.850311F, -390.820404F,
  -402.854889F, -415.626587F, -428.606201F, -441.585693F, -454.9534F,
  -468.903503F, -482.636688F, -494.263885F, -494.263885F, 1.17092597F,
  -2.0809989F, -5.33292484F, -8.58485126F, -14.0811596F, -20.51334F,
  -29.2881298F, -37.9760513F, -46.5534F, -55.1134911F, -63.656311F, -73.2325F,
  -83.9281693F, -93.2721863F, -100.749603F, -108.803902F, -118.204201F, -127.73F,
  -137.790894F, -148.081802F, -160.698593F, -173.256F, -182.901505F,
  -192.546906F, -201.062897F, -209.544F, -219.533F, -229.853F, -239.519806F,
  -249.0233F, -259.674103F, -270.611786F, -282.049F, -293.611115F, -305.464386F,
  -317.365F, -329.879395F, -342.360199F, -353.590607F, -364.908F, -376.596802F,
  -388.438507F, -400.54071F, -412.345795F, -423.944611F, -436.919495F,
  -450.423798F, -463.553192F, -476.89151F, -490.570496F, -494.263885F, 1.93375F,
  -1.87827599F, -5.69030285F, -9.50233F, -14.5508404F, -21.1885891F, -31.6867F,
  -41.0435486F, -49.0055313F, -56.0593796F, -62.2749481F, -70.3334274F,
  -80.7374115F, -90.56604F, -99.3261566F, -108.229301F, -117.585197F,
  -126.822701F, -135.192093F, -143.642105F, -156.040497F, -168.439F,
  -180.086395F, -191.6772F, -207.653702F, -224.117599F, -236.561096F,
  -248.557907F, -264.994904F, -281.904907F, -299.346802F, -316.504303F,
  -333.109894F, -349.54F, -365.862305F, -386.249512F, -406.323F, -426.138306F,
  -447.281097F, -471.995911F, -500.669708F, -535.574524F, -564.22467F,
  -593.804504F, -593.804504F, -593.804504F, -593.804504F, -593.804504F,
  -593.804504F, -593.804504F, -593.804504F, 1.07740796F, -2.15431905F,
  -5.38604689F, -8.61777401F, -16.2733803F, -23.4875603F, -29.2641602F,
  -36.5683784F, -45.8976F, -57.0804787F, -70.3536606F, -85.0391312F,
  -101.254601F, -117.188797F, -132.935394F, -149.093796F, -165.333694F,
  -180.915497F, -197.241302F, -215.148102F, -231.717804F, -247.610306F,
  -261.953796F, -277.292786F, -295.465393F, -313.841492F, -331.57431F,
  -347.795898F, -368.11911F, -390.974F, -417.454803F, -444.84079F, -469.723511F,
  -498.125702F, -531.61377F, -579.112488F, -616.4104F, -616.4104F, -616.4104F,
  -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F,
  -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F, -616.4104F,
  1.10588801F, -2.14603806F, -5.397964F, -8.64989F, -21.5423F, -35.7406197F,
  -52.6289215F, -69.4885712F, -86.3143234F, -103.020599F, -120.152397F,
  -137.508499F, -154.263596F, -171.271103F, -188.464294F, -205.264099F,
  -223.291107F, -242.146301F, -259.637085F, -274.705292F, -288.735291F,
  -309.862396F, -329.721588F, -352.022095F, -377.193695F, -400.839111F,
  -428.5672F, -460.270294F, -499.304688F, -591.635315F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -578.178284F, -578.178284F, -578.178284F, -578.178284F, -578.178284F,
  -12.1928701F, -23.5958195F, -34.9987717F, -48.3635406F, -61.9133606F,
  -74.6562881F, -88.845253F, -103.931099F, -120.337601F, -136.755707F,
  -153.473907F, -170.769302F, -189.326797F, -207.492599F, -225.493393F,
  -245.077499F, -264.740906F, -286.367F, -308.722595F, -330.301788F,
  -353.757385F, -379.171295F, -409.204315F, -441.812F, -478.511597F,
  -541.161377F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -558.521729F, -558.521729F, -558.521729F, -558.521729F,
  -558.521729F, -42.4754105F, -54.5544891F, -66.6335678F, -78.7126465F,
  -91.2031326F, -106.220901F, -121.7892F, -137.996201F, -155.377106F,
  -172.528702F, -189.947906F, -208.048294F, -228.886093F, -249.641098F,
  -270.406799F, -291.021698F, -312.215302F, -336.198914F, -363.003815F,
  -392.084106F, -424.231598F, -466.136597F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F, -536.96283F,
  -536.96283F, -536.96283F, -536.96283F, -55.2997513F, -71.3277F, -87.3556366F,
  -103.383598F, -119.411499F, -135.439499F, -151.467407F, -167.859497F,
  -185.404495F, -203.459106F, -222.812F, -243.431107F, -264.831696F,
  -287.359497F, -310.799F, -332.931091F, -361.361389F, -397.771515F,
  -438.020691F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -55.2997513F, -71.3277F,
  -87.3556366F, -103.383598F, -119.411499F, -135.439499F, -151.467407F,
  -167.859497F, -185.404495F, -203.459106F, -222.812F, -243.431107F,
  -264.831696F, -287.359497F, -310.799F, -332.931091F, -361.361389F,
  -397.771515F, -438.020691F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -55.2997513F,
  -71.3277F, -87.3556366F, -103.383598F, -119.411499F, -135.439499F,
  -151.467407F, -167.859497F, -185.404495F, -203.459106F, -222.812F,
  -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -55.2997513F, -71.3277F, -87.3556366F, -103.383598F, -119.411499F,
  -135.439499F, -151.467407F, -167.859497F, -185.404495F, -203.459106F,
  -222.812F, -243.431107F, -264.831696F, -287.359497F, -310.799F, -332.931091F,
  -361.361389F, -397.771515F, -438.020691F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F,
  -514.912292F, -514.912292F, -514.912292F, -514.912292F, -514.912292F } ;/* Referenced by:
                                                                      * '<S28>/Id_Mot_Map'
                                                                      * '<S28>/530MTPAIdMot'
                                                                      */

float32 MCRM_MTPAIdMot_Z_A[1020] = { 3.56961799F, -1.22558296F, -6.0207839F,
  -10.81598F, -14.8963299F, -20.1387806F, -30.6368904F, -39.5245209F,
  -45.4212685F, -51.8819695F, -59.1214485F, -68.1219101F, -79.6564865F,
  -90.3165894F, -99.1184235F, -108.748901F, -121.3172F, -133.152802F,
  -140.084198F, -147.054306F, -157.856598F, -168.658798F, -178.157104F,
  -187.572205F, -198.1129F, -208.821701F, -219.223404F, -229.543396F, -239.461F,
  -249.258408F, -259.229187F, -269.235504F, -282.265106F, -295.525513F,
  -305.383209F, -315.240814F, -326.297607F, -337.868286F, -351.956696F,
  -365.457214F, -376.537109F, -387.251801F, -397.224915F, -408.094788F,
  -423.343597F, -439.184296F, -455.098907F, -470.252899F, -482.097107F,
  -492.311188F, -497.928894F, 1.05379403F, -3.25764489F, -7.56908417F,
  -11.8805199F, -18.9816494F, -25.2891293F, -28.7752F, -34.8897781F,
  -45.1156082F, -54.6009216F, -63.1437416F, -72.0351F, -81.4077682F, -90.61026F,
  -99.496727F, -108.133499F, -116.095F, -124.741203F, -136.306305F, -147.814697F,
  -158.669296F, -169.496094F, -178.956894F, -188.417694F, -198.299896F,
  -208.199707F, -218.361694F, -228.630905F, -238.5793F, -248.376694F,
  -259.268188F, -270.544189F, -282.049F, -293.611115F, -305.571503F,
  -317.596802F, -328.550507F, -339.521698F, -351.650208F, -363.621094F,
  -373.998505F, -384.486115F, -397.621399F, -410.954F, -424.582611F, -438.20459F,
  -451.948792F, -466.256592F, -480.331512F, -494.263885F, -494.263885F,
  1.20344603F, -2.04848F, -5.30040598F, -8.55233192F, -13.3341F, -18.9527607F,
  -26.6617508F, -35.9875298F, -47.2893791F, -56.7020912F, -64.2997513F,
  -72.1624374F, -80.2901611F, -89.2926712F, -99.4085388F, -109.289597F,
  -118.734596F, -128.345703F, -138.454697F, -148.691498F, -159.599106F,
  -170.347595F, -179.808395F, -189.347504F, -200.374405F, -211.377197F,
  -221.596F, -231.814804F, -241.3255F, -250.828903F, -261.806702F, -272.799286F,
  -284.2435F, -295.715912F, -307.868408F, -319.832611F, -330.73F, -342.063599F,
  -354.638885F, -366.965698F, -378.850311F, -390.820404F, -402.854889F,
  -415.626587F, -428.606201F, -441.585693F, -454.9534F, -468.903503F,
  -482.636688F, -494.263885F, -494.263885F, 1.16745F, -2.10492897F, -5.37730694F,
  -8.64968491F, -14.1924801F, -20.9121399F, -30.4569607F, -38.2527695F,
  -45.5552711F, -53.4928207F, -61.9499588F, -70.826828F, -80.0471268F,
  -89.0338211F, -97.7674408F, -107.394302F, -118.361F, -129.037903F,
  -139.098801F, -149.369598F, -160.384705F, -171.104507F, -180.565201F,
  -190.083099F, -199.982895F, -209.882599F, -220.197403F, -230.568695F,
  -240.2686F, -249.868F, -261.225098F, -272.799286F, -284.2435F, -295.708313F,
  -307.670898F, -319.713409F, -332.341614F, -344.622F, -355.912689F,
  -367.362701F, -379.051392F, -390.902F, -402.869598F, -415.810699F,
  -429.068115F, -442.605F, -456.137085F, -469.664398F, -483.463287F,
  -494.263885F, -494.263885F, 2.21323F, -1.54388702F, -5.30100393F, -9.21396732F,
  -14.5295496F, -20.9675F, -29.7905102F, -38.0143509F, -45.6390305F,
  -54.3981895F, -63.9788818F, -73.5195618F, -83.0300598F, -92.1649704F,
  -100.966797F, -110.064598F, -119.554901F, -129.239105F, -139.3F, -149.097397F,
  -158.060104F, -167.459793F, -178.992905F, -190.350204F, -200.710403F,
  -211.070602F, -222.633194F, -234.195694F, -244.9189F, -255.642197F,
  -266.806396F, -277.967102F, -288.341797F, -298.737213F, -309.37149F,
  -320.288605F, -332.586212F, -344.59079F, -355.761414F, -367.228699F,
  -379.180115F, -391.062408F, -402.89859F, -415.277496F, -427.84F, -441.132202F,
  -454.917F, -469.505188F, -483.463287F, -494.263885F, -494.263885F, 1.71738803F,
  -2.36105394F, -6.43949604F, -10.5339499F, -15.1461897F, -20.5975208F,
  -27.6071701F, -35.8281403F, -45.1233215F, -53.8904305F, -62.3055F,
  -70.4532928F, -78.4153519F, -86.6392822F, -95.0954285F, -104.487396F,
  -115.1716F, -125.508698F, -135.073105F, -144.809692F, -155.698898F,
  -165.845093F, -169.305F, -175.282593F, -191.331F, -207.379501F, -219.017F,
  -229.337F, -240.244507F, -251.347702F, -262.643402F, -273.981293F,
  -285.568207F, -297.189209F, -307.677704F, -318.093903F, -330.69989F,
  -343.599792F, -358.31781F, -373.80069F, -390.048401F, -396.222504F,
  -396.222504F, -396.222504F, -396.222504F, -396.222504F, -396.222504F,
  -396.222504F, -396.222504F, -396.222504F, -396.222504F, 0.299312413F,
  -2.16101599F, -4.62134314F, -7.32277107F, -14.6050901F, -22.1745F, -30.3012F,
  -38.63937F, -47.1727295F, -57.0772896F, -68.0162506F, -81.7146606F,
  -97.4947586F, -111.747498F, -125.213501F, -140.194504F, -155.680603F,
  -171.359207F, -188.585495F, -207.619202F, -222.786F, -236.133102F, -237.7715F,
  -239.171F, -240.570404F, -246.302902F, -261.243103F, -276.866913F, -293.07309F,
  -309.473206F, -326.061096F, -343.591888F, -363.217194F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, -379.526215F, -379.526215F, -379.526215F,
  -379.526215F, -379.526215F, 2.31303811F, -2.00962305F, -6.33228397F,
  -10.6227598F, -14.4089603F, -21.6977196F, -35.4912F, -52.2639618F,
  -71.8991776F, -88.6528168F, -105.535698F, -123.348602F, -139.295303F,
  -154.778503F, -172.2061F, -188.926605F, -205.136795F, -222.479095F,
  -240.459106F, -257.552094F, -261.573395F, -265.594696F, -269.616F,
  -279.411285F, -297.180206F, -315.199402F, -333.942505F, -353.789398F,
  -376.415192F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, -378.677795F, -378.677795F,
  -378.677795F, -378.677795F, -378.677795F, 0.842858493F, -2.94112897F,
  -6.72511721F, -10.50986F, -14.3191204F, -22.2139606F, -38.403759F,
  -54.8450089F, -71.5183792F, -87.7648926F, -104.142097F, -121.6642F,
  -138.655807F, -155.263107F, -172.418594F, -189.304199F, -205.839F,
  -224.103302F, -242.566696F, -260.958313F, -279.52951F, -298.633087F,
  -318.554688F, -339.865387F, -360.983398F, -381.721497F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F,
  -391.2146F, -391.2146F, -391.2146F, -391.2146F, -391.2146F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  11.3967505F, -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F,
  -71.8025589F, -89.2560806F, -105.9105F, -122.375702F, -139.072098F,
  -156.162292F, -173.628693F, -191.698196F, -208.409103F, -225.664505F,
  -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  11.3967505F, -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F,
  -71.8025589F, -89.2560806F, -105.9105F, -122.375702F, -139.072098F,
  -156.162292F, -173.628693F, -191.698196F, -208.409103F, -225.664505F,
  -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F,
  -1.06381905F, -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F,
  -89.2560806F, -105.9105F, -122.375702F, -139.072098F, -156.162292F,
  -173.628693F, -191.698196F, -208.409103F, -225.664505F, -244.110794F,
  -263.876F, -284.646F, -305.271F, -325.812103F, -349.377808F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, 11.3967505F, -1.06381905F,
  -13.5243902F, -26.34375F, -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F,
  -105.9105F, -122.375702F, -139.072098F, -156.162292F, -173.628693F,
  -191.698196F, -208.409103F, -225.664505F, -244.110794F, -263.876F, -284.646F,
  -305.271F, -325.812103F, -349.377808F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, 11.3967505F, -1.06381905F, -13.5243902F, -26.34375F,
  -41.3671303F, -56.3795F, -71.8025589F, -89.2560806F, -105.9105F, -122.375702F,
  -139.072098F, -156.162292F, -173.628693F, -191.698196F, -208.409103F,
  -225.664505F, -244.110794F, -263.876F, -284.646F, -305.271F, -325.812103F,
  -349.377808F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F,
  -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F, -373.43219F }
;                                      /* Referenced by:
                                        * '<S27>/696Id_Mot_Map'
                                        * '<S27>/696MTPAIdMot'
                                        */

float32 MCRM_MTPVIdLimt_Y_A[18] = { -565.0F, -536.0F, -536.0F, -531.0F, -519.0F,
  -503.0F, -503.0F, -493.0F, -493.0F, -493.0F, -472.0F, -472.0F, -469.0F,
  -464.0F, -458.0F, -451.0F, -442.0F, -434.0F } ;
                                   /* Referenced by: '<S26>/1-D Lookup Table' */

float32 MEOP_nReqMotSpdMax_Y_T[5] = { 3000.0F, 3000.0F, 3000.0F, 3000.0F,
  3000.0F } ;                 /* Referenced by: '<S125>/EopC_nReqMotSpdMax_T' */

float32 MEOP_nRrOilTempDetOptMod_Y_T[10] = { 100.0F, 100.0F, 100.0F, 200.0F,
  200.0F, 200.0F, 300.0F, 300.0F, 300.0F, 350.0F } ;
                         /* Referenced by: '<S126>/EopC_nRrTMTempDetOptMod_T' */

float32 MEOP_nRrOilTempDetOptMod_Z_M[90] = { 1800.0F, 1700.0F, 1600.0F, 1500.0F,
  1400.0F, 1200.0F, 1000.0F, 800.0F, 700.0F, 600.0F, 2000.0F, 1900.0F, 1800.0F,
  1700.0F, 1600.0F, 1500.0F, 1200.0F, 1000.0F, 900.0F, 800.0F, 2500.0F, 2400.0F,
  2300.0F, 2200.0F, 2100.0F, 2000.0F, 1900.0F, 1600.0F, 1300.0F, 1000.0F,
  2850.0F, 2850.0F, 2850.0F, 2700.0F, 2600.0F, 2400.0F, 2200.0F, 2000.0F,
  1600.0F, 1200.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2500.0F, 2200.0F, 1800.0F, 1300.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2500.0F, 2000.0F, 1400.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2750.0F, 2250.0F, 1500.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2250.0F, 1500.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2250.0F, 1500.0F } ;
                        /* Referenced by: '<S126>/EopC_nRrOilTempDetOptMod_M' */

float32 MEOP_nRrOilTempMotOptMod_Z_M[90] = { 1800.0F, 1700.0F, 1600.0F, 1500.0F,
  1400.0F, 1200.0F, 1000.0F, 800.0F, 700.0F, 600.0F, 2000.0F, 1900.0F, 1800.0F,
  1700.0F, 1600.0F, 1500.0F, 1200.0F, 1000.0F, 900.0F, 800.0F, 2500.0F, 2400.0F,
  2300.0F, 2200.0F, 2100.0F, 2000.0F, 1900.0F, 1600.0F, 1300.0F, 1000.0F,
  2850.0F, 2850.0F, 2850.0F, 2700.0F, 2600.0F, 2400.0F, 2200.0F, 2000.0F,
  1600.0F, 1200.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2500.0F, 2200.0F, 1800.0F, 1300.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2500.0F, 2000.0F, 1400.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2750.0F, 2250.0F, 1500.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2250.0F, 1500.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2250.0F, 1500.0F } ;
                        /* Referenced by: '<S128>/EopC_nRrOilTempMotOptMod_M' */

float32 MEOP_nRrOilTempSpdMod_Z_M[90] = { 1800.0F, 1700.0F, 1600.0F, 1500.0F,
  1400.0F, 1200.0F, 1000.0F, 800.0F, 700.0F, 600.0F, 2000.0F, 1900.0F, 1800.0F,
  1700.0F, 1600.0F, 1500.0F, 1200.0F, 1000.0F, 900.0F, 800.0F, 2500.0F, 2400.0F,
  2300.0F, 2200.0F, 2100.0F, 2000.0F, 1900.0F, 1600.0F, 1300.0F, 1000.0F,
  2850.0F, 2850.0F, 2850.0F, 2700.0F, 2600.0F, 2400.0F, 2200.0F, 2000.0F,
  1600.0F, 1200.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2500.0F, 2200.0F, 1800.0F, 1300.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2500.0F, 2000.0F, 1400.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2750.0F, 2250.0F, 1500.0F,
  2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2250.0F, 1500.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F, 2850.0F,
  2850.0F, 2850.0F, 2250.0F, 1500.0F } ;
                                 /* Referenced by: '<S131>/EopC_nRrOilTemp_M' */

float32 MEOP_nRrTMTempMotOptMod_Y_T[10] = { 100.0F, 100.0F, 100.0F, 200.0F,
  200.0F, 200.0F, 300.0F, 300.0F, 300.0F, 350.0F } ;
                         /* Referenced by: '<S128>/EopC_nRrTMTempMotOptMod_T' */

float32 MEOP_nRrTMTempSpdMod_Y_T[10] = { 100.0F, 100.0F, 100.0F, 200.0F, 200.0F,
  200.0F, 300.0F, 300.0F, 300.0F, 350.0F } ;
                                  /* Referenced by: '<S131>/EopC_nRrTMTemp_T' */

float32 MLLC_volCoolFlowOil_Y_T[4] = { 14.0F, 14.0F, 14.0F, 14.0F } ;
                             /* Referenced by: '<S590>/LLCM_volCoolFlowOil_M' */

float32 MLLC_volCoolFlowWater_Z_M[16] = { 1.0F, 1.0F, 1.0F, 1.0F, 2.0F, 2.0F,
  2.0F, 2.0F, 3.0F, 3.0F, 3.0F, 3.0F, 4.0F, 4.0F, 4.0F, 4.0F } ;
                           /* Referenced by: '<S590>/LLCM_volCoolFlowWater_M' */

float32 MLLC_volfCooltFlow_Y_T[4] = { 1.0F, 2.0F, 3.0F, 4.0F } ;
                              /* Referenced by: '<S590>/LLCM_volfCooltFlow_M' */

float32 MSYL_TrqMax_Z_Nm[105] = { 500.0F, 500.0F, 500.0F, 500.0F, 500.0F, 500.0F,
  446.97F, 383.28F, 335.81F, 298.14F, 268.44F, 240.66F, 213.24F, 191.15F,
  173.05F, 157.58F, 144.81F, 133.99F, 124.32F, 115.57F, 108.1F, 500.0F, 500.0F,
  500.0F, 500.0F, 500.0F, 500.0F, 446.97F, 383.28F, 335.81F, 298.14F, 268.44F,
  240.66F, 213.24F, 191.15F, 173.05F, 157.58F, 144.81F, 133.99F, 124.32F,
  115.57F, 108.1F, 500.0F, 500.0F, 500.0F, 500.0F, 500.0F, 500.0F, 446.97F,
  383.28F, 335.81F, 298.14F, 268.44F, 240.66F, 213.24F, 191.15F, 173.05F,
  157.58F, 144.81F, 133.99F, 124.32F, 115.57F, 108.1F, 500.0F, 500.0F, 500.0F,
  500.0F, 500.0F, 500.0F, 446.97F, 383.28F, 335.81F, 298.14F, 268.44F, 240.66F,
  213.24F, 191.15F, 173.05F, 157.58F, 144.81F, 133.99F, 124.32F, 115.57F, 108.1F,
  500.0F, 500.0F, 500.0F, 500.0F, 500.0F, 500.0F, 446.97F, 383.28F, 335.81F,
  298.14F, 268.44F, 240.66F, 213.24F, 191.15F, 173.05F, 157.58F, 144.81F,
  133.99F, 124.32F, 115.57F, 108.1F } ;/* Referenced by: '<S702>/TrqMax' */

float32 MSYL_TrqMin_Z_Nm[105] = { -500.0F, -500.0F, -500.0F, -500.0F, -500.0F,
  -500.0F, -446.97F, -383.28F, -335.81F, -298.14F, -268.44F, -240.66F, -213.24F,
  -191.15F, -173.05F, -157.58F, -144.81F, -133.99F, -124.32F, -115.57F, -108.1F,
  -500.0F, -500.0F, -500.0F, -500.0F, -500.0F, -500.0F, -446.97F, -383.28F,
  -335.81F, -298.14F, -268.44F, -240.66F, -213.24F, -191.15F, -173.05F, -157.58F,
  -144.81F, -133.99F, -124.32F, -115.57F, -108.1F, -500.0F, -500.0F, -500.0F,
  -500.0F, -500.0F, -500.0F, -446.97F, -383.28F, -335.81F, -298.14F, -268.44F,
  -240.66F, -213.24F, -191.15F, -173.05F, -157.58F, -144.81F, -133.99F, -124.32F,
  -115.57F, -108.1F, -500.0F, -500.0F, -500.0F, -500.0F, -500.0F, -500.0F,
  -446.97F, -383.28F, -335.81F, -298.14F, -268.44F, -240.66F, -213.24F, -191.15F,
  -173.05F, -157.58F, -144.81F, -133.99F, -124.32F, -115.57F, -108.1F, -500.0F,
  -500.0F, -500.0F, -500.0F, -500.0F, -500.0F, -446.97F, -383.28F, -335.81F,
  -298.14F, -268.44F, -240.66F, -213.24F, -191.15F, -173.05F, -157.58F, -144.81F,
  -133.99F, -124.32F, -115.57F, -108.1F } ;/* Referenced by: '<S702>/TrqMin' */

boolean OpMod_ResolverEnt_C = false_MatlabRTW;
                               /* Referenced by: '<S597>/OpMod_ResolverEnt_C' */
boolean OpMod_bDcha2AfterRunMor_C = false_MatlabRTW;
                         /* Referenced by: '<S597>/OpMod_bDcha2AfterRunMor_C' */
boolean OpMod_bService_C = false_MatlabRTW;/* Referenced by: '<S597>/Constant1' */
float32 OpMod_nRot2AfterRun_C = 1000.0F;
                             /* Referenced by: '<S597>/OpMod_nRot2AfterRun_C' */
float32 OpMod_nRotASCDi_C = 10500.0F;  /* Referenced by: '<S598>/Constant2' */
float32 OpMod_nRotASCEna_C = 11000.0F; /* Referenced by: '<S598>/Constant3' */
float32 OpMod_tiDcha2AfterRun_C = 300.0F;
                           /* Referenced by: '<S597>/OpMod_tiDcha2AfterRun_C' */
float32 OpMod_uDCSide2AfterRun_C = 24.0F;
                          /* Referenced by: '<S597>/OpMod_uDCSide2AfterRun_C' */

#define SWC_APP_type_STOP_SEC_CAL
#include "SWC_APP_type_MemMap.h"

/* PublicStructure Variables for Internal Data */
ARID_DEF_SWC_APP_type_T SWC_APP_type_ARID_DEF;

/* Forward declaration for local functions */
static float32 SWC_APP_type_funmaxrun_SWC_APP(float32 b_m, float32 n);
static float32 SWC_APP_type_funminrun_SWC_APP(float32 b_m, float32 n);

/* Forward declaration for local functions */
static void inner_default_Judgerun_SWC_APP(const float32 *Divide, const float32 *
  Divide1, const float32 *Divide2, float32 rtu_f32_Input_T, float32
  rtu_f32_StartP, float32 rtu_f32_Delta, float32 rtu_f32_EndP, float32 *rty_Coef,
  ARID_DEF_Derating_Reverse_T *SWC_APP_type__ARID_DEF_arg);

/* Forward declaration for local functions */
static float32 SWC_APP_typ_funminrun_SWC_APP_e(float32 b_m, float32 n);
static float32 SWC_APP_typ_funmaxrun_SWC_APP_m(float32 b_m, float32 n);

/* Forward declaration for local functions */
static void exit_internal_PowerDownProcedur(void);

/*
 * Outputs for atomic system:
 *    '<S21>/Delay'
 *    '<S22>/Delay'
 *    '<S53>/Delay'
 *    '<S78>/Delay'
 *    '<S103>/Delay'
 *    '<S600>/Delay'
 *    '<S724>/Delay'
 *    '<S747>/Delay'
 *    '<S709>/Delay'
 *    '<S710>/Delay'
 *    ...
 */
boolean SWC_APP_type_Delay(ARID_DEF_Delay_SWC_APP_type_T
  *SWC_APP_type__ARID_DEF_arg)
{
  /* UnitDelay: '<S37>/UnitDelay' */
  return SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE;
}

/*
 * Update for atomic system:
 *    '<S21>/Delay'
 *    '<S22>/Delay'
 *    '<S53>/Delay'
 *    '<S78>/Delay'
 *    '<S103>/Delay'
 *    '<S600>/Delay'
 *    '<S724>/Delay'
 *    '<S747>/Delay'
 *    '<S709>/Delay'
 *    '<S710>/Delay'
 *    ...
 */
void SWC_APP_type_Delay_Update(boolean rtu_u, ARID_DEF_Delay_SWC_APP_type_T
  *SWC_APP_type__ARID_DEF_arg)
{
  /* Update for UnitDelay: '<S37>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rtu_u;
}

/*
 * Output and update for atomic system:
 *    '<S18>/ER_FF'
 *    '<S34>/ER_FF'
 *    '<S35>/ER_FF'
 *    '<S36>/ER_FF'
 *    '<S717>/ER_FF'
 *    '<S850>/ER_FF'
 *    '<S903>/ER_FF'
 */
void SWC_APP_type_ER_FF(boolean rtu_E1_T, boolean rtu_R2_F, boolean *rty_y,
  ARID_DEF_ER_FF_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg)
{
  boolean rtb_UnitDelay_c;

  /* Outputs for Atomic SubSystem: '<S21>/Delay' */
  rtb_UnitDelay_c = SWC_APP_type_Delay
    (&SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S21>/Delay' */

  /* Switch: '<S40>/SWT' incorporates:
   *  Constant: '<S21>/true'
   *  Switch: '<S39>/SWT'
   */
  if (rtu_E1_T) {
    *rty_y = true_MatlabRTW;
  } else {
    *rty_y = ((!rtu_R2_F) && rtb_UnitDelay_c);
  }

  /* End of Switch: '<S40>/SWT' */

  /* Update for Atomic SubSystem: '<S21>/Delay' */
  SWC_APP_type_Delay_Update(*rty_y, &SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Update for SubSystem: '<S21>/Delay' */
}

/*
 * Outputs for atomic system:
 *    '<S34>/Delay'
 *    '<S35>/Delay'
 *    '<S36>/Delay'
 *    '<S716>/Delay1'
 *    '<S717>/Delay'
 *    '<S849>/Delay1'
 *    '<S850>/Delay'
 *    '<S903>/Delay'
 */
float32 SWC_APP_type_Delay_m(ARID_DEF_Delay_SWC_APP_type_f_T
  *SWC_APP_type__ARID_DEF_arg)
{
  /* UnitDelay: '<S52>/UnitDelay' */
  return SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE;
}

/*
 * Update for atomic system:
 *    '<S34>/Delay'
 *    '<S35>/Delay'
 *    '<S36>/Delay'
 *    '<S716>/Delay1'
 *    '<S717>/Delay'
 *    '<S849>/Delay1'
 *    '<S850>/Delay'
 *    '<S903>/Delay'
 */
void SWC_APP_type_Delay_p_Update(float32 rtu_u, ARID_DEF_Delay_SWC_APP_type_f_T *
  SWC_APP_type__ARID_DEF_arg)
{
  /* Update for UnitDelay: '<S52>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rtu_u;
}

/*
 * Output and update for atomic system:
 *    '<S54>/Delay'
 *    '<S56>/Delay'
 *    '<S57>/Delay'
 *    '<S79>/Delay'
 *    '<S81>/Delay'
 *    '<S82>/Delay'
 *    '<S104>/Delay'
 *    '<S106>/Delay'
 *    '<S107>/Delay'
 *    '<S719>/Delay'
 *    ...
 */
boolean SWC_APP_type_Delay_d(boolean rtu_u, ARID_DEF_Delay_SWC_APP_type_h_T
  *SWC_APP_type__ARID_DEF_arg)
{
  boolean rty_y_0;

  /* UnitDelay: '<S67>/UnitDelay' */
  rty_y_0 = SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S67>/UnitDelay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rtu_u;
  return rty_y_0;
}

/*
 * Output and update for atomic system:
 *    '<S34>/Falling'
 *    '<S35>/Falling'
 *    '<S36>/Falling'
 *    '<S716>/Falling'
 *    '<S716>/Falling1'
 *    '<S717>/Falling'
 *    '<S849>/Falling'
 *    '<S849>/Falling1'
 *    '<S850>/Falling'
 *    '<S903>/Falling'
 */
boolean SWC_APP_type_Falling(boolean rtu_In1, ARID_DEF_Falling_SWC_APP_type_T
  *SWC_APP_type__ARID_DEF_arg)
{
  boolean rty_Out1_0;
  boolean rtb_UnitDelay_o0;

  /* Outputs for Atomic SubSystem: '<S54>/Delay' */
  rtb_UnitDelay_o0 = SWC_APP_type_Delay_d(rtu_In1,
    &SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S54>/Delay' */

  /* Logic: '<S66>/AND1' incorporates:
   *  Logic: '<S68>/NOT1'
   */
  rty_Out1_0 = ((!rtu_In1) && rtb_UnitDelay_o0);
  return rty_Out1_0;
}

/*
 * Output and update for atomic system:
 *    '<S34>/Rising'
 *    '<S34>/Rising1'
 *    '<S35>/Rising'
 *    '<S35>/Rising1'
 *    '<S36>/Rising'
 *    '<S36>/Rising1'
 *    '<S716>/Rising1'
 *    '<S717>/Rising'
 *    '<S717>/Rising1'
 *    '<S849>/Rising1'
 *    ...
 */
boolean SWC_APP_type_Rising(boolean rtu_In1, ARID_DEF_Rising_SWC_APP_type_T
  *SWC_APP_type__ARID_DEF_arg)
{
  boolean rty_Out1_0;
  boolean rtb_UnitDelay_i;

  /* Outputs for Atomic SubSystem: '<S56>/Delay' */
  rtb_UnitDelay_i = SWC_APP_type_Delay_d(rtu_In1,
    &SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S56>/Delay' */

  /* Logic: '<S69>/AND1' incorporates:
   *  Logic: '<S71>/NOT1'
   */
  rty_Out1_0 = (rtu_In1 && (!rtb_UnitDelay_i));
  return rty_Out1_0;
}

/*
 * Output and update for enable system:
 *    '<S146>/Subsystem'
 *    '<S164>/Subsystem'
 */
void SWC_APP_type_Subsystem(boolean rtu_Enable, uint8 rtu_RC, uint8 rtu_RC_delay,
  boolean *rty_RCErr)
{
  /* Outputs for Enabled SubSystem: '<S146>/Subsystem' incorporates:
   *  EnablePort: '<S150>/Enable'
   */
  if (rtu_Enable) {
    /* RelationalOperator: '<S150>/Equal1' */
    *rty_RCErr = (rtu_RC == rtu_RC_delay);
  }

  /* End of Outputs for SubSystem: '<S146>/Subsystem' */
}

/* Output and update for function-call system: '<S7>/CAN_MCU_R1' */
void SWC_APP_type_CAN_MCU_R1(boolean rtu_BOUTP_outputs, float32
  rtu_BOUTP_outputs_h, DT_CAN_MCU_R1_SG_MCU_FVT_R_Local1
  *rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_)
{
  float32 tmp;

  /* BusCreator: '<S307>/bus_creator' incorporates:
   *  DataTypeConversion: '<S310>/Data Type Conversion'
   */
  rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_->CAN_MCU_R1_MCU_FVT_R_Local1_CS_Sta = 0U;
  rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_->CAN_MCU_R1_MCU_FVT_R_Local1_RC_Sta = 0U;
  rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_->CAN_MCU_R1_MCU_FVT_R_OPCStartOn_Req =
    rtu_BOUTP_outputs;

  /* DataTypeConversion: '<S311>/Data Type Conversion' */
  tmp = fmodf(rt_roundf(rtu_BOUTP_outputs_h), 65536.0F);

  /* BusCreator: '<S307>/bus_creator' incorporates:
   *  DataTypeConversion: '<S311>/Data Type Conversion'
   */
  rty_DT_CAN_MCU_R1_SG_MCU_FVT_R_->CAN_MCU_R1_MCU_FVT_R_OilPmpTarSpd_Req =
    (uint16)(tmp < 0.0F ? (sint32)(uint16)-(sint16)(uint16)-tmp : (sint32)
             (uint16)tmp);
}

/* Output and update for function-call system: '<S7>/CAN3' */
void SWC_APP_type_CAN3(float32 rtu_BOUTP_outputs, float32 rtu_BOUTP_outputs_f,
  float32 rtu_BOUTP_outputs_g, boolean rtu_BOUTP_outputs_fu, boolean
  rtu_BOUTP_outputs_p, float32 rtu_BOUTP_outputs_m, float32 rtu_BOUTP_outputs_k,
  float32 rtu_BOUTP_outputs_i, float32 rtu_BOUTP_outputs_i4, uint8
  rtu_BOUTP_outputs_i0, float32 rtu_BOUTP_outputs_c, boolean rtu_BOUTP_outputs_j,
  float32 rtu_BOUTP_outputs_f2, float32 rtu_BOUTP_outputs_cs, float32
  rtu_BOUTP_outputs_ke, uint8 rtu_BOUTP_outputs_g1, DT_CAN3_SG_MCU_B_R1
  *rty_DT_CAN3_SG_MCU_B_R1, DT_CAN3_SG_MCU_B_R2 *rty_DT_CAN3_SG_MCU_B_R2,
  DT_CAN3_SG_MCU_FVT_R1 *rty_DT_CAN3_SG_MCU_FVT_R1, const
  ConstB_CAN3_SWC_APP_type_T *localC)
{
  float32 tmp;

  /* BusCreator: '<S230>/bus_creator' */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_MCUWarn_R = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_MCU_B_R_IGBTDdeTemp_Sta =
    localC->DataTypeConversion;

  /* DataTypeConversion: '<S234>/Data Type Conversion' incorporates:
   *  Constant: '<S263>/offset'
   *  Product: '<S263>/Divide'
   *  Sum: '<S263>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs - -530.0F) / localC->MinMax_a),
              65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S234>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_MCU_B_R_RealPwrKw_Sta = (uint16)(tmp < 0.0F ?
    (sint32)(uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_ActvDmpDisabSta = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_EDUDrtSta = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_EDUOpratingSta = rtu_BOUTP_outputs_i0;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_EDURealTMTq = localC->DataTypeConversion_p;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_EDURotateDirction = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_EDUTqReqFbk = localC->DataTypeConversion_px;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCU1Chksum = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCU1RolCnt = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUBAT = localC->DataTypeConversion_m;

  /* DataTypeConversion: '<S245>/Data Type Conversion' incorporates:
   *  Constant: '<S267>/offset'
   *  Product: '<S267>/Divide'
   *  Sum: '<S267>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_f - -1500.0F) / localC->MinMax_o),
              65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S245>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUDCBusCurr = (uint16)(tmp < 0.0F ? (sint32)
    (uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);

  /* DataTypeConversion: '<S246>/Data Type Conversion' incorporates:
   *  Product: '<S268>/Divide'
   *  Sum: '<S268>/Add'
   */
  tmp = fmodf(rt_roundf(rtu_BOUTP_outputs_g / localC->MinMax_b), 65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S246>/Data Type Conversion'
   *  DataTypeConversion: '<S248>/Data Type Conversion'
   *  DataTypeConversion: '<S251>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUDCBusVolt = (uint16)(tmp < 0.0F ? (sint32)
    (uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUDischrgSta = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUEnaSta = rtu_BOUTP_outputs_fu;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUErr = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUIGN_sta = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUReady = rtu_BOUTP_outputs_p;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUReady4Pre = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUSysSta = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MCUTemp = localC->DataTypeConversion_b;

  /* DataTypeConversion: '<S255>/Data Type Conversion' */
  tmp = fmodf(rt_roundf(rtu_BOUTP_outputs_m), 65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S255>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_MotorAvailTq = (uint16)(tmp < 0.0F ? (sint32)
    (uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);

  /* DataTypeConversion: '<S256>/Data Type Conversion' incorporates:
   *  Constant: '<S270>/offset'
   *  Product: '<S270>/Divide'
   *  Sum: '<S270>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_k - -1022.0F) / localC->MinMax_jv),
              65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S256>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_RegenAvailTq = (uint16)(tmp < 0.0F ? (sint32)
    (uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_Reserved_bits = 0U;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_TMSpd = localC->DataTypeConversion_f;
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_TMTemp = localC->DataTypeConversion_g;

  /* DataTypeConversion: '<S260>/Data Type Conversion' incorporates:
   *  Constant: '<S273>/offset'
   *  Product: '<S273>/Divide'
   *  Sum: '<S273>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_i - -1500.0F) / localC->MinMax_d),
              65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S260>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_TMid = (uint16)(tmp < 0.0F ? (sint32)(uint16)
    -(sint16)(uint16)-tmp : (sint32)(uint16)tmp);

  /* DataTypeConversion: '<S261>/Data Type Conversion' incorporates:
   *  Constant: '<S274>/offset'
   *  Product: '<S274>/Divide'
   *  Sum: '<S274>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_i4 - -1500.0F) / localC->MinMax_my),
              65536.0F);

  /* BusCreator: '<S230>/bus_creator' incorporates:
   *  DataTypeConversion: '<S261>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R1->CAN3_Rr_TMiq = (uint16)(tmp < 0.0F ? (sint32)(uint16)
    -(sint16)(uint16)-tmp : (sint32)(uint16)tmp);

  /* BusCreator: '<S231>/bus_creator' */
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_MCU_B_R_FailLv_Sta = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_MCU_B_R_KL302TqCnt_Sta = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_MCU_B_R_LLCTempWarn_Sta = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_CoolanttempReq =
    localC->DataTypeConversion_bl;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_Failcode1 = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_Failcode2 = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_Failcodehistory1 = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_Failcodehistory2 = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_LLCTemp = localC->DataTypeConversion_fo;

  /* DataTypeConversion: '<S284>/Data Type Conversion' incorporates:
   *  Product: '<S293>/Divide'
   *  Sum: '<S293>/Add'
   */
  tmp = fmodf(rt_roundf(rtu_BOUTP_outputs_c / localC->MinMax_oi), 256.0F);

  /* BusCreator: '<S231>/bus_creator' incorporates:
   *  DataTypeConversion: '<S284>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_LLCflowReq = (uint8)(tmp < 0.0F ? (sint32)
    (uint8)-(sint8)(uint8)-tmp : (sint32)(uint8)tmp);
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_MCU2Chksum = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_MCU2RolCnt = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_MCU3_HW_Ver = localC->DataTypeConversion_ga;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_MCU3_SW_Ver = localC->DataTypeConversion_h;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_MCUTempWarn = 0U;
  rty_DT_CAN3_SG_MCU_B_R2->CAN3_Rr_TMTempWarn = 0U;

  /* BusCreator: '<S232>/bus_creator' incorporates:
   *  DataTypeConversion: '<S294>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_BoostOP_Sta = rtu_BOUTP_outputs_j;
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_EDUTqReq_Fbk =
    localC->DataTypeConversion_j;
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_Failcode3_Sta = 0U;
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_HeatingOP_Sta = 0U;

  /* DataTypeConversion: '<S298>/Data Type Conversion' incorporates:
   *  Product: '<S304>/Divide'
   *  Sum: '<S304>/Add'
   */
  tmp = fmodf(rt_roundf(rtu_BOUTP_outputs_f2 / localC->MinMax_g), 65536.0F);

  /* BusCreator: '<S232>/bus_creator' incorporates:
   *  DataTypeConversion: '<S298>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_MCUBAT_Sta = (uint16)(tmp < 0.0F ?
    (sint32)(uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_MCUErr_Sta = 0U;
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_MCUSys_Sta = rtu_BOUTP_outputs_g1;

  /* DataTypeConversion: '<S301>/Data Type Conversion' incorporates:
   *  Constant: '<S305>/offset'
   *  Product: '<S305>/Divide'
   *  Sum: '<S305>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_cs - -40.0F) / localC->MinMax_aq),
              65536.0F);

  /* BusCreator: '<S232>/bus_creator' incorporates:
   *  DataTypeConversion: '<S301>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_OilTemp_Sta = (uint16)(tmp < 0.0F ?
    (sint32)(uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);

  /* DataTypeConversion: '<S302>/Data Type Conversion' incorporates:
   *  Constant: '<S306>/offset'
   *  Product: '<S306>/Divide'
   *  Sum: '<S306>/Add'
   */
  tmp = fmodf(rt_roundf((rtu_BOUTP_outputs_ke - -22000.0F) / localC->MinMax_c),
              65536.0F);

  /* BusCreator: '<S232>/bus_creator' incorporates:
   *  DataTypeConversion: '<S302>/Data Type Conversion'
   */
  rty_DT_CAN3_SG_MCU_FVT_R1->CAN3_MCU_FVT_R_TMSpd_Sta = (uint16)(tmp < 0.0F ?
    (sint32)(uint16)-(sint16)(uint16)-tmp : (sint32)(uint16)tmp);
}

/*
 * Output and update for atomic system:
 *    '<S716>/RE_FF'
 *    '<S849>/RE_FF'
 */
void SWC_APP_type_RE_FF(boolean rtu_R1_F, boolean rtu_E2_T, boolean *rty_y,
  ARID_DEF_RE_FF_SWC_APP_type_T *SWC_APP_type__ARID_DEF_arg)
{
  boolean rtb_UnitDelay_h;

  /* Outputs for Atomic SubSystem: '<S724>/Delay' */
  rtb_UnitDelay_h = SWC_APP_type_Delay
    (&SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S724>/Delay' */

  /* Switch: '<S739>/SWT' incorporates:
   *  Constant: '<S724>/false'
   *  Switch: '<S740>/SWT'
   */
  if (rtu_R1_F) {
    *rty_y = false_MatlabRTW;
  } else {
    *rty_y = (rtu_E2_T || rtb_UnitDelay_h);
  }

  /* End of Switch: '<S739>/SWT' */

  /* Update for Atomic SubSystem: '<S724>/Delay' */
  SWC_APP_type_Delay_Update(*rty_y, &SWC_APP_type__ARID_DEF_arg->ARID_DEF_Delay);

  /* End of Update for SubSystem: '<S724>/Delay' */
}

/*
 * System initialize for atomic system:
 *    '<S785>/Chart'
 *    '<S786>/Chart'
 *    '<S794>/Chart'
 *    '<S795>/Chart'
 *    '<S804>/Chart'
 *    '<S818>/Chart'
 *    '<S820>/Chart'
 *    '<S827>/Chart'
 *    '<S828>/Chart'
 *    '<S836>/Chart'
 *    ...
 */
void SWC_APP_type_Chart_Init(sint16 *rty_Count, boolean *rty_Status)
{
  *rty_Count = 0;
  *rty_Status = false_MatlabRTW;
}

/*
 * Output and update for atomic system:
 *    '<S785>/Chart'
 *    '<S786>/Chart'
 *    '<S794>/Chart'
 *    '<S795>/Chart'
 *    '<S804>/Chart'
 *    '<S818>/Chart'
 *    '<S820>/Chart'
 *    '<S827>/Chart'
 *    '<S828>/Chart'
 *    '<S836>/Chart'
 *    ...
 */
void SWC_APP_type_Chart(sint16 rtu_Count_Pre, boolean rtu_State, sint16
  rtu_Heal_Max, sint16 rtu_Error_Max, boolean rtu_Status_Pre, sint16 *rty_Count,
  boolean *rty_Status)
{
  /* Chart: '<S785>/Chart' */
  if (rtu_State) {
    if (rtu_Count_Pre <= 0) {
      *rty_Count = 2;
    } else if (rtu_Count_Pre >= rtu_Error_Max) {
      *rty_Count = rtu_Error_Max;
    } else {
      sint32 tmp;
      tmp = rtu_Count_Pre + 2;
      if (rtu_Count_Pre + 2 > 32767) {
        tmp = 32767;
      }

      *rty_Count = (sint16)tmp;
    }
  } else if (rtu_Count_Pre <= rtu_Heal_Max) {
    *rty_Count = rtu_Heal_Max;
  } else {
    *rty_Count = (sint16)(rtu_Count_Pre - 1);
  }

  *rty_Status = ((*rty_Count > rtu_Heal_Max) && (rtu_Status_Pre || (rtu_Heal_Max
    >= *rty_Count) || (*rty_Count >= rtu_Error_Max)));

  /* End of Chart: '<S785>/Chart' */
}

/*
 * System initialize for atomic system:
 *    '<S782>/debounce'
 *    '<S782>/debounce1'
 */
void SWC_APP_type_debounce_Init(boolean *rty_Status)
{
  sint16 rtb_Count;

  /* SystemInitialize for Chart: '<S785>/Chart' */
  SWC_APP_type_Chart_Init(&rtb_Count, rty_Status);
}

/*
 * Output and update for atomic system:
 *    '<S782>/debounce'
 *    '<S782>/debounce1'
 */
void SWC_APP_type_debounce(boolean rtu_error_state, sint16 rtu_heal_max, sint16
  rtu_error_max, boolean *rty_Status, ARID_DEF_debounce_SWC_APP_typ_T
  *SWC_APP_type__ARID_DEF_arg)
{
  /* Chart: '<S785>/Chart' incorporates:
   *  UnitDelay: '<S785>/Unit Delay'
   *  UnitDelay: '<S785>/Unit Delay1'
   */
  SWC_APP_type_Chart(SWC_APP_type__ARID_DEF_arg->UnitDelay1_DSTATE,
                     rtu_error_state, rtu_heal_max, rtu_error_max,
                     SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE,
                     &SWC_APP_type__ARID_DEF_arg->UnitDelay1_DSTATE, rty_Status);

  /* Update for UnitDelay: '<S785>/Unit Delay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = *rty_Status;
}

/* Function for Chart: '<S780>/Chart' */
static float32 SWC_APP_type_funmaxrun_SWC_APP(float32 b_m, float32 n)
{
  return fmaxf(b_m, n);
}

/* Function for Chart: '<S780>/Chart' */
static float32 SWC_APP_type_funminrun_SWC_APP(float32 b_m, float32 n)
{
  float32 y;
  if (b_m > n) {
    y = n;
  } else {
    y = b_m;
  }

  return y;
}

/*
 * System initialize for atomic system:
 *    '<S777>/CoefSmooth'
 *    '<S778>/CoefSmooth'
 *    '<S807>/CoefSmooth'
 *    '<S808>/CoefSmooth'
 *    '<S809>/CoefSmooth'
 *    '<S810>/CoefSmooth'
 */
void CoefSmooth_Init(float32 *rty_OutputCoef)
{
  /* SystemInitialize for Chart: '<S780>/Chart' */
  *rty_OutputCoef = 1.0F;
}

/*
 * Output and update for atomic system:
 *    '<S777>/CoefSmooth'
 *    '<S778>/CoefSmooth'
 *    '<S807>/CoefSmooth'
 *    '<S808>/CoefSmooth'
 *    '<S809>/CoefSmooth'
 *    '<S810>/CoefSmooth'
 */
void CoefSmooth(float32 rtu_InputCoef, float32 rtu_DepStep, float32 rtu_AddStep,
                float32 *rty_OutputCoef)
{
  /* Chart: '<S780>/Chart' */
  if (rtu_InputCoef > *rty_OutputCoef) {
    *rty_OutputCoef += rtu_AddStep;
    *rty_OutputCoef = SWC_APP_type_funminrun_SWC_APP(*rty_OutputCoef,
      rtu_InputCoef);
  } else {
    *rty_OutputCoef -= rtu_DepStep;
    *rty_OutputCoef = SWC_APP_type_funmaxrun_SWC_APP(*rty_OutputCoef,
      rtu_InputCoef);
  }

  /* End of Chart: '<S780>/Chart' */
}

/* Output and update for atomic system: '<S777>/Derating_Forward' */
float32 Derating_Forward(float32 rtu_InputVal, float32 rtu_StartVal, float32
  rtu_Width, float32 rtu_EndVal, ARID_DEF_Derating_Forward_T
  *SWC_APP_type__ARID_DEF_arg)
{
  float32 rty_Coef_0;

  /* Chart: '<S781>/Chart' */
  if (!SWC_APP_type__ARID_DEF_arg->FirstFlag) {
    SWC_APP_type__ARID_DEF_arg->DownVal = rtu_StartVal;
    SWC_APP_type__ARID_DEF_arg->UpVal = rtu_StartVal + rtu_Width;
    SWC_APP_type__ARID_DEF_arg->FirstFlag = true_MatlabRTW;
  }

  if (rtu_InputVal <= rtu_EndVal) {
    SWC_APP_type__ARID_DEF_arg->DownVal = rtu_EndVal;
    SWC_APP_type__ARID_DEF_arg->UpVal = rtu_EndVal + rtu_Width;
  } else {
    float32 tmp;
    tmp = rtu_StartVal + rtu_Width;
    if (rtu_InputVal >= tmp) {
      SWC_APP_type__ARID_DEF_arg->UpVal = tmp;
      SWC_APP_type__ARID_DEF_arg->DownVal = rtu_StartVal;
    } else if (rtu_InputVal > SWC_APP_type__ARID_DEF_arg->UpVal) {
      SWC_APP_type__ARID_DEF_arg->UpVal = rtu_InputVal;
      SWC_APP_type__ARID_DEF_arg->DownVal = SWC_APP_type__ARID_DEF_arg->UpVal -
        rtu_Width;
    } else if (rtu_InputVal < SWC_APP_type__ARID_DEF_arg->DownVal) {
      SWC_APP_type__ARID_DEF_arg->DownVal = rtu_InputVal;
      SWC_APP_type__ARID_DEF_arg->UpVal = SWC_APP_type__ARID_DEF_arg->DownVal +
        rtu_Width;
    }
  }

  rty_Coef_0 = (SWC_APP_type__ARID_DEF_arg->DownVal - rtu_EndVal) /
    (rtu_StartVal - rtu_EndVal);

  /* End of Chart: '<S781>/Chart' */

  /* Saturate: '<S781>/Saturation' */
  if (rty_Coef_0 > 1.0F) {
    rty_Coef_0 = 1.0F;
  } else if (rty_Coef_0 < 0.0F) {
    rty_Coef_0 = 0.0F;
  }

  /* End of Saturate: '<S781>/Saturation' */
  return rty_Coef_0;
}

/* Function for Chart: '<S790>/Chart1' */
static void inner_default_Judgerun_SWC_APP(const float32 *Divide, const float32 *
  Divide1, const float32 *Divide2, float32 rtu_f32_Input_T, float32
  rtu_f32_StartP, float32 rtu_f32_Delta, float32 rtu_f32_EndP, float32 *rty_Coef,
  ARID_DEF_Derating_Reverse_T *SWC_APP_type__ARID_DEF_arg)
{
  float32 tmp;

  /* Chart: '<S790>/Chart1' */
  tmp = rtu_f32_StartP - rtu_f32_Delta;
  if (rtu_f32_Input_T < tmp) {
    *rty_Coef = 1.0F;

    /* Current_Coef=1; */
    SWC_APP_type__ARID_DEF_arg->Up_point = tmp;
    SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_StartP;
  } else if (rtu_f32_Input_T > rtu_f32_EndP) {
    *rty_Coef = 0.0F;

    /* Current_Coef=a*T+b1; */
    SWC_APP_type__ARID_DEF_arg->Up_point = rtu_f32_EndP - rtu_f32_Delta;
    SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_EndP;
  } else if (rtu_f32_Input_T >= SWC_APP_type__ARID_DEF_arg->Down_point) {
    *rty_Coef = *Divide * rtu_f32_Input_T + *Divide1;

    /* Current_Coef=a*T+b1; */
    SWC_APP_type__ARID_DEF_arg->Up_point = rtu_f32_Input_T - rtu_f32_Delta;
    SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_Input_T;
  } else if (rtu_f32_Input_T <= SWC_APP_type__ARID_DEF_arg->Up_point) {
    *rty_Coef = *Divide * rtu_f32_Input_T + *Divide2;

    /* Current_Coef=a*T+b2; */
    SWC_APP_type__ARID_DEF_arg->Up_point = rtu_f32_Input_T;
    SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_Input_T + rtu_f32_Delta;
  } else {
    /* Coef=Current_Coef; */
  }

  /* End of Chart: '<S790>/Chart1' */
}

/*
 * System initialize for atomic system:
 *    '<S778>/Derating_Reverse'
 *    '<S807>/Derating_Reverse'
 *    '<S808>/Derating_Reverse'
 *    '<S809>/Derating_Reverse'
 *    '<S810>/Temp_Derating_Reverse'
 */
void Derating_Reverse_Init(float32 *rty_Coef)
{
  /* SystemInitialize for Chart: '<S790>/Chart1' */
  *rty_Coef = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S778>/Derating_Reverse'
 *    '<S807>/Derating_Reverse'
 *    '<S808>/Derating_Reverse'
 *    '<S809>/Derating_Reverse'
 *    '<S810>/Temp_Derating_Reverse'
 */
void Derating_Reverse(float32 rtu_f32_Input_T, float32 rtu_f32_StartP, float32
                      rtu_f32_Delta, float32 rtu_f32_EndP, float32 *rty_Coef,
                      ARID_DEF_Derating_Reverse_T *SWC_APP_type__ARID_DEF_arg)
{
  float32 Divide;
  float32 Divide1;
  float32 Divide2_tmp;
  float32 rtb_Subtract_l;

  /* Sum: '<S790>/Subtract' */
  rtb_Subtract_l = rtu_f32_EndP - rtu_f32_StartP;

  /* Product: '<S790>/Divide' incorporates:
   *  Constant: '<S790>/Constant'
   */
  Divide = -1.0F / rtb_Subtract_l;

  /* Product: '<S790>/Divide1' */
  Divide1 = rtu_f32_EndP / rtb_Subtract_l;

  /* Sum: '<S790>/Subtract1' incorporates:
   *  Chart: '<S790>/Chart1'
   */
  Divide2_tmp = rtu_f32_EndP - rtu_f32_Delta;

  /* Product: '<S790>/Divide2' incorporates:
   *  Sum: '<S790>/Subtract1'
   */
  rtb_Subtract_l = Divide2_tmp / rtb_Subtract_l;

  /* Chart: '<S790>/Chart1' */
  if (SWC_APP_type__ARID_DEF_arg->is_active_c6_Library == 0U) {
    SWC_APP_type__ARID_DEF_arg->is_active_c6_Library = 1U;
    SWC_APP_type__ARID_DEF_arg->is_c6_Library = SWC_APP_type_IN_Initial;
    if (rtu_f32_Input_T > rtu_f32_EndP) {
      *rty_Coef = 0.0F;

      /* Current_Coef=1; */
      SWC_APP_type__ARID_DEF_arg->Up_point = Divide2_tmp;
      SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_EndP;
    } else if (rtu_f32_Input_T < rtu_f32_StartP) {
      *rty_Coef = 1.0F;

      /* Current_Coef=1; */
      SWC_APP_type__ARID_DEF_arg->Up_point = rtu_f32_StartP - rtu_f32_Delta;
      SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_StartP;
    } else {
      *rty_Coef = Divide * rtu_f32_Input_T + Divide1;

      /* Current_Coef=a*T+b1; */
      SWC_APP_type__ARID_DEF_arg->Up_point = rtu_f32_Input_T - rtu_f32_Delta;
      SWC_APP_type__ARID_DEF_arg->Down_point = rtu_f32_Input_T;
    }
  } else if (SWC_APP_type__ARID_DEF_arg->is_c6_Library ==
             SWC_APP_type_IN_Initial) {
    SWC_APP_type__ARID_DEF_arg->is_c6_Library = SWC_APP_type_IN_Judge;
    inner_default_Judgerun_SWC_APP(&Divide, &Divide1, &rtb_Subtract_l,
      rtu_f32_Input_T, rtu_f32_StartP, rtu_f32_Delta, rtu_f32_EndP, rty_Coef,
      SWC_APP_type__ARID_DEF_arg);
  } else {
    /* case IN_Judge: */
    inner_default_Judgerun_SWC_APP(&Divide, &Divide1, &rtb_Subtract_l,
      rtu_f32_Input_T, rtu_f32_StartP, rtu_f32_Delta, rtu_f32_EndP, rty_Coef,
      SWC_APP_type__ARID_DEF_arg);
  }
}

/*
 * System initialize for atomic system:
 *    '<S791>/debounce'
 *    '<S791>/debounce1'
 *    '<S800>/debounce'
 *    '<S816>/debounce'
 *    '<S817>/debounce'
 *    '<S824>/debounce'
 *    '<S824>/debounce1'
 *    '<S833>/debounce'
 *    '<S833>/debounce1'
 *    '<S841>/debounce'
 *    '<S841>/debounce1'
 */
void SWC_APP_type_debounce_m_Init(boolean *rty_Status)
{
  sint16 rtb_Count;

  /* SystemInitialize for Chart: '<S794>/Chart' */
  SWC_APP_type_Chart_Init(&rtb_Count, rty_Status);
}

/*
 * Output and update for atomic system:
 *    '<S791>/debounce'
 *    '<S791>/debounce1'
 *    '<S800>/debounce'
 *    '<S816>/debounce'
 *    '<S817>/debounce'
 *    '<S824>/debounce'
 *    '<S824>/debounce1'
 *    '<S833>/debounce'
 *    '<S833>/debounce1'
 *    '<S841>/debounce'
 *    '<S841>/debounce1'
 */
boolean SWC_APP_type_debounce_c(boolean rtu_error_state, sint16 rtu_heal_max,
  sint16 rtu_error_max, ARID_DEF_debounce_SWC_APP_t_j_T
  *SWC_APP_type__ARID_DEF_arg)
{
  boolean rty_Status_0;

  /* Chart: '<S794>/Chart' incorporates:
   *  UnitDelay: '<S794>/Unit Delay'
   *  UnitDelay: '<S794>/Unit Delay1'
   */
  SWC_APP_type_Chart(SWC_APP_type__ARID_DEF_arg->UnitDelay1_DSTATE,
                     rtu_error_state, rtu_heal_max, rtu_error_max,
                     SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE,
                     &SWC_APP_type__ARID_DEF_arg->UnitDelay1_DSTATE,
                     &rty_Status_0);

  /* Update for UnitDelay: '<S794>/Unit Delay' */
  SWC_APP_type__ARID_DEF_arg->UnitDelay_DSTATE = rty_Status_0;
  return rty_Status_0;
}

/* Output and update for atomic system: '<S712>/Abs1' */
float32 Abs(float32 rtu_In1)
{
  float32 rty_Out1_0;

  /* Switch: '<S798>/Switch' incorporates:
   *  Constant: '<S801>/Constant'
   *  Gain: '<S798>/Gain'
   *  RelationalOperator: '<S801>/Compare'
   */
  if (rtu_In1 >= 0.0F) {
    rty_Out1_0 = rtu_In1;
  } else {
    rty_Out1_0 = -rtu_In1;
  }

  /* End of Switch: '<S798>/Switch' */
  return rty_Out1_0;
}

/* Function for Chart: '<S799>/Chart' */
static float32 SWC_APP_typ_funminrun_SWC_APP_e(float32 b_m, float32 n)
{
  float32 y;
  if (b_m > n) {
    y = n;
  } else {
    y = b_m;
  }

  return y;
}

/* Function for Chart: '<S799>/Chart' */
static float32 SWC_APP_typ_funmaxrun_SWC_APP_m(float32 b_m, float32 n)
{
  return fmaxf(b_m, n);
}

/* System initialize for atomic system: '<S712>/Coef_Decrease_Increase' */
void Coef_Decrease_Increase_Init(float32 *rty_OutputCoef,
  ARID_DEF_Coef_Decrease_Increa_T *SWC_APP_type__ARID_DEF_arg)
{
  /* SystemInitialize for Chart: '<S799>/Chart' */
  *rty_OutputCoef = 0.0F;
  SWC_APP_type__ARID_DEF_arg->Coef_Local = 1.0F;
}

/* Output and update for atomic system: '<S712>/Coef_Decrease_Increase' */
float32 Coef_Decrease_Increase(boolean rtu_Input_Flg, float32 rtu_AddStep,
  float32 rtu_SubStep, ARID_DEF_Coef_Decrease_Increa_T
  *SWC_APP_type__ARID_DEF_arg)
{
  float32 rty_OutputCoef_0;

  /* Chart: '<S799>/Chart' */
  if (rtu_Input_Flg) {
    SWC_APP_type__ARID_DEF_arg->Coef_Local -= rtu_SubStep;
    SWC_APP_type__ARID_DEF_arg->Coef_Local = SWC_APP_typ_funmaxrun_SWC_APP_m
      (SWC_APP_type__ARID_DEF_arg->Coef_Local, 0.0F);
  } else {
    SWC_APP_type__ARID_DEF_arg->Coef_Local += rtu_AddStep;
    SWC_APP_type__ARID_DEF_arg->Coef_Local = SWC_APP_typ_funminrun_SWC_APP_e
      (SWC_APP_type__ARID_DEF_arg->Coef_Local, 1.0F);
  }

  rty_OutputCoef_0 = SWC_APP_type__ARID_DEF_arg->Coef_Local;

  /* End of Chart: '<S799>/Chart' */
  return rty_OutputCoef_0;
}

/* System initialize for atomic system: '<S800>/Hysteresis_Ctrl_Forward' */
void Hysteresis_Ctrl_Forward_Init(boolean *rty_enable)
{
  /* SystemInitialize for Chart: '<S803>/Hysteresis_Control' */
  *rty_enable = false_MatlabRTW;
}

/* Output and update for atomic system: '<S800>/Hysteresis_Ctrl_Forward' */
void Hysteresis_Ctrl_Forward(float32 rtu_Input, float32 rtu_EnterPoint, float32
  rtu_Hys_Band, boolean *rty_enable)
{
  /* Chart: '<S803>/Hysteresis_Control' incorporates:
   *  Sum: '<S803>/Add'
   */
  *rty_enable = ((rtu_Input >= rtu_EnterPoint) || ((rtu_Input > rtu_EnterPoint -
    rtu_Hys_Band) && (*rty_enable)));
}

/* Function for Chart: '<S597>/MotorMode' */
static void exit_internal_PowerDownProcedur(void)
{
  SWC_APP_type_ARID_DEF.is_PowerUpProcedure = 0;
  SWC_APP_type_ARID_DEF.is_PowerDownProcedure = 0;
}

#include "logging.h"
uint32 uart_count = 0;
/* Model step function for TID1 */
void run_SWC_APP(void)                 /* Explicit Task: run_SWC_APP */
{
  /* local block i/o variables */
  float32 rtb_OutputCoef;
  boolean rtb_Status;
  boolean rtb_Status_l;
  boolean rtb_Status_j;
  boolean rtb_Status_b;
  boolean rtb_Status_b2;
  boolean rtb_Status_d;
  boolean rtb_Status_k;
  boolean rtb_Status_f;
  boolean rtb_Status_c;
  boolean rtb_Status_h;
  boolean rtb_Status_ci;
  boolean rtb_Status_la;
  boolean rtb_Status_g;
  DT_CAN3_SG_BMS1 rtb_TmpSignalConversionAtR_CA_l;
  DT_CAN3_SG_BMS6 rtb_TmpSignalConversionAtR_CA_k;
  DT_CAN3_SG_FD3_C100_0 rtb_TmpSignalConversionAtR_CA_d;
  DT_CAN3_SG_FD3_VCU1 rtb_TmpSignalConversionAtR_CA_g;
  DT_CAN3_SG_FD3_VCU2 rtb_TmpSignalConversionAtR_CAN3;
  DT_CAN3_SG_FD3_VCU5 rtb_TmpSignalConversionAtR_CA_m;
  DT_CAN3_SG_GW3_CE100_0 rtb_TmpSignalConversionAtR_CA_c;
  DT_CAN_MCU_R1_SG_EOP_FVT_R_Local1 rtb_TmpSignalConversionAtR_CAN_;
  EvAdc_SignalDataType_Fake expl_temp;
  float64 tmp_0;
  float32 frac[2];
  float32 frac_0[2];
  float32 rtb_Prelookup1_o2;
  float32 rtb_Prelookup1_o2_n;
  float32 rtb_Prelookup_o2;
  float32 rtb_SWT;
  float32 rtb_TrqMax;
  float32 rtb_UnitDelay_bs;
  float32 rtb_UnitDelay_cg;
  float32 rtb_UnitDelay_d;
  float32 rtb_UnitDelay_di;
  float32 rtb_UnitDelay_e;
  float32 rtb_UnitDelay_jc;
  float32 rtb_UnitDelay_n2;
  float32 rtb_UnitDelay_plq;
  float32 tmp_2;
  sint32 i;
  sint32 rtb_MinMax;
  uint32 bpIndex[2];
  uint32 bpIndex_0[2];
  uint32 rtb_Prelookup1_o1;
  uint32 rtb_Prelookup_o1;
  uint16 tmp_1;
  sint8 tmp;
  sint8 tmp_3;
  uint8 rtb_DataTypeConversion3_h[17];
  uint8 rtb_DataTypeConversion3_p[15];
  uint8 rtb_DataTypeConversion3_j[13];
  uint8 rtb_DataTypeConversion3[11];
  uint8 message;
  uint8 rtb_BitwiseOR;
  uint8 rtb_BitwiseOR1;
  uint8 rtb_MinMax5;
  uint8 u0;
  boolean rtb_LogicalOperator[15];
  boolean rtb_LogicalOperator_e0[11];
  boolean DiagM_bOver2Stop;
  boolean rtb_AND1_c;
  boolean rtb_AND1_g2;
  boolean rtb_AND1_gb;
  boolean rtb_AND1_h;
  boolean rtb_AND1_h1;
  boolean rtb_AND1_ig;
  boolean rtb_AND1_j;
  boolean rtb_AND1_l;
  boolean rtb_AND1_pg;
  boolean rtb_LogicalOperator5;
  boolean rtb_UnitDelay_a;
  boolean rtb_UnitDelay_bk;
  boolean rtb_UnitDelay_ch;
  boolean rtb_UnitDelay_f3;
  boolean rtb_UnitDelay_nm;

  if(uart_count == 1000)
  {
    Logging_Printf("hellow world!\n");
    uart_count = 0;
  }
  else
  {
    uart_count++;
  }

  /* RootInportFunctionCallGenerator generated from: '<Root>/run_SWC_APP' incorporates:
   *  SubSystem: '<Root>/run_SWC_APP_sys'
   */
  /* SignalConversion generated from: '<S2>/R_HiRateTxLoRateRx_HiRateTxLoRateRx' incorporates:
   *  Inport: '<Root>/R_HiRateTxLoRateRx_HiRateTxLoRateRx'
   */
  (void)Rte_Read_R_HiRateTxLoRateRx_HiRateTxLoRateRx
    (&SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx);

  /* Outputs for Atomic SubSystem: '<S712>/Abs1' */
  rtb_SWT = Abs
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot);

  /* End of Outputs for SubSystem: '<S712>/Abs1' */

  /* Outputs for Atomic SubSystem: '<S712>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S800>/Hysteresis_Ctrl_Forward' */
  /* Constant: '<S800>/Constant' incorporates:
   *  Constant: '<S800>/Constant3'
   */
  Hysteresis_Ctrl_Forward(rtb_SWT, KDGL_OverSpd_rpm, KDGL_OverSpdHysBand_rpm,
    &SWC_APP_type_ARID_DEF.enable);

  /* End of Outputs for SubSystem: '<S800>/Hysteresis_Ctrl_Forward' */

  /* Outputs for Atomic SubSystem: '<S800>/debounce' */
  /* Constant: '<S800>/Constant1' incorporates:
   *  Constant: '<S800>/Constant2'
   */
  rtb_Status_c = SWC_APP_type_debounce_c(SWC_APP_type_ARID_DEF.enable,
    KDGL_OverSpdHeal_cnt, KDGL_OverSpdErr_cnt,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_gu);

  /* End of Outputs for SubSystem: '<S800>/debounce' */
  /* End of Outputs for SubSystem: '<S712>/Function-Call Subsystem' */

  /* Logic: '<S712>/Logical Operator2' incorporates:
   *  Constant: '<S712>/Constant'
   *  Logic: '<S712>/Logical Operator1'
   *  Logic: '<S712>/Logical Operator3'
   *  RelationalOperator: '<S712>/Relational Operator'
   */
  VDGL_OverSpdErr_flg = (((!VOPM_CurLoopEna_flg) && (rtb_SWT >=
    KDGL_OverSpdNotEna_rpm)) || rtb_Status_c);

  /* Outputs for Atomic SubSystem: '<S778>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S791>/debounce' */
  /* RelationalOperator: '<S791>/Relational Operator' incorporates:
   *  Constant: '<S791>/Constant1'
   *  Constant: '<S791>/Constant2'
   *  Constant: '<S791>/T2'
   */
  rtb_Status_ci = SWC_APP_type_debounce_c
    ((SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >=
      Diag2_f32_UdcOverStopDerat_C), Diag2_int16_HvOverErrHeal_C,
     Diag2_int16_HvOverErrErr_C, &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_d);

  /* End of Outputs for SubSystem: '<S791>/debounce' */

  /* SignalConversion: '<S791>/Signal Conversion' */
  VDGL_HVOverErr_flg = rtb_Status_ci;

  /* Outputs for Atomic SubSystem: '<S791>/debounce1' */
  /* RelationalOperator: '<S791>/Relational Operator1' incorporates:
   *  Constant: '<S791>/Constant4'
   *  Constant: '<S791>/Constant5'
   *  Constant: '<S791>/T1'
   */
  rtb_Status_h = SWC_APP_type_debounce_c
    ((SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >=
      Diag2_f32_UdcOverStartDerat_C), Diag2_int16_HvOverWarnHeal_C,
     Diag2_int16_HvOverWarnErr_C, &SWC_APP_type_ARID_DEF.ARID_DEF_debounce1_l);

  /* End of Outputs for SubSystem: '<S791>/debounce1' */

  /* SignalConversion: '<S791>/Signal Conversion1' */
  VDGL_HVOverWarn_flg = rtb_Status_h;

  /* End of Outputs for SubSystem: '<S778>/Function-Call Subsystem' */

  /* SignalConversion generated from: '<S2>/R_CAN_MCU_R1_EOP_FVT_R_Local1_CAN_MCU_R1_SG_EOP_FVT_R_Local1' incorporates:
   *  Inport: '<Root>/R_CAN_MCU_R1_EOP_FVT_R_Local1_CAN_MCU_R1_SG_EOP_FVT_R_Local1'
   */
  (void)Rte_Read_R_CAN_MCU_R1_EOP_FVT_R_Local1_CAN_MCU_R1_SG_EOP_FVT_R_Local1
    (&rtb_TmpSignalConversionAtR_CAN_);

  /* DataTypeConversion: '<S134>/UnitConverter' */
  VHAL_EOPFVTRActualSpdSta_rpm =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_ActualSpd_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter1' */
  VHAL_EOPFVTRCSInvalidSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_CSInvalid_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter2' */
  VHAL_EOPFVTRCanLossSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_CanLoss_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter3' */
  VHAL_EOPFVTREnableOffSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_EnableOff_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter4' */
  VHAL_EOPFVTRHallSigErrSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_HallSigErr_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter5' */
  VHAL_EOPFVTRLocal1CSSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_Local1_CS_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter6' */
  VHAL_EOPFVTRLocal1RCSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_Local1_RC_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter7' */
  VHAL_EOPFVTROverTempBCKSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_OverTempBCK_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter8' */
  VHAL_EOPFVTROverTempSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_OverTemp_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter9' */
  VHAL_EOPFVTROverVolSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_OverVol_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter10' */
  VHAL_EOPFVTRPumpReadySta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_PumpReady_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter11' */
  VHAL_EOPFVTRRCInvalidSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_RCInvalid_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter12' */
  VHAL_EOPFVTRRunStatusSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_RunStatus_Sta;

  /* DataTypeConversion: '<S134>/UnitConverter13' */
  VHAL_EOPFVTRStartFailureSta_flg =
    (rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_StartFailure_Sta != 0);

  /* DataTypeConversion: '<S134>/UnitConverter14' */
  VHAL_EOPFVTRUnderVolSta_enum =
    rtb_TmpSignalConversionAtR_CAN_.CAN_MCU_R1_EOP_FVT_R_UnderVol_Sta;

  /* BusCreator: '<S134>/bus_creator' */
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_CANMsgInvalidEOPFVTRLocal1_flg =
    VHAL_CANMsgInvalidEOPFVTRLocal1_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRActualSpdSta_rpm =
    VHAL_EOPFVTRActualSpdSta_rpm;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRCSInvalidSta_flg =
    VHAL_EOPFVTRCSInvalidSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRCanLossSta_flg =
    VHAL_EOPFVTRCanLossSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTREnableOffSta_flg =
    VHAL_EOPFVTREnableOffSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRHallSigErrSta_flg =
    VHAL_EOPFVTRHallSigErrSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRLocal1CSSta_enum =
    VHAL_EOPFVTRLocal1CSSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRLocal1RCSta_enum =
    VHAL_EOPFVTRLocal1RCSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverTempBCKSta_enum =
    VHAL_EOPFVTROverTempBCKSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverTempSta_flg =
    VHAL_EOPFVTROverTempSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTROverVolSta_enum =
    VHAL_EOPFVTROverVolSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRPumpReadySta_flg =
    VHAL_EOPFVTRPumpReadySta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRRCInvalidSta_flg =
    VHAL_EOPFVTRRCInvalidSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRRunStatusSta_enum =
    VHAL_EOPFVTRRunStatusSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRStartFailureSta_flg =
    VHAL_EOPFVTRStartFailureSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_nq.VHAL_EOPFVTRUnderVolSta_enum =
    VHAL_EOPFVTRUnderVolSta_enum;

  /* SignalConversion generated from: '<S2>/R_CAN3_BMS1_CAN3_SG_BMS1' incorporates:
   *  Inport: '<Root>/R_CAN3_BMS1_CAN3_SG_BMS1'
   */
  (void)Rte_Read_R_CAN3_BMS1_CAN3_SG_BMS1(&rtb_TmpSignalConversionAtR_CA_l);

  /* S-Function (sfix_bitop): '<S135>/BitwiseOR1' incorporates:
   *  S-Function (sfix_bitop): '<S135>/BitwiseAND1'
   */
  rtb_BitwiseOR1 = (uint8)(rtb_TmpSignalConversionAtR_CA_l.CAN3_HVBattVolt & 255);

  /* MinMax: '<S688>/MinMax5' incorporates:
   *  ArithShift: '<S135>/RightShift'
   *  DataTypeConversion: '<S135>/Data Type Conversion'
   */
  rtb_MinMax5 = (uint8)(rtb_TmpSignalConversionAtR_CA_l.CAN3_HVBattVolt >> 8);

  /* S-Function (sfix_bitop): '<S135>/BitwiseOR' */
  rtb_BitwiseOR = rtb_MinMax5;

  /* If: '<S147>/If' incorporates:
   *  Constant: '<S135>/KHAL_CAN3BMS1E2E_flg'
   *  DataTypeConversion: '<S147>/Data Type Conversion'
   */
  if (KHAL_CAN3BMS1E2E_flg) {
    /* Outputs for IfAction SubSystem: '<S147>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S153>/Action Port'
     */
    /* DataTypeConversion: '<S156>/Data Type Conversion3' incorporates:
     *  Constant: '<S135>/0x3C'
     *  Constant: '<S135>/0xDC'
     *  Constant: '<S135>/constant1'
     *  Constant: '<S135>/constant10'
     *  Constant: '<S135>/constant11'
     *  Constant: '<S135>/constant12'
     *  Constant: '<S135>/constant13'
     *  Constant: '<S135>/constant2'
     *  Constant: '<S135>/constant3'
     *  Constant: '<S135>/constant4'
     *  Constant: '<S135>/constant5'
     *  Constant: '<S135>/constant6'
     *  Constant: '<S135>/constant7'
     *  Constant: '<S135>/constant8'
     *  Constant: '<S135>/constant9'
     *  S-Function (sfix_bitop): '<S135>/BitwiseOR'
     */
    rtb_DataTypeConversion3_h[0] = 60U;
    rtb_DataTypeConversion3_h[1] = 220U;
    rtb_DataTypeConversion3_h[2] = 0U;
    rtb_DataTypeConversion3_h[3] = 0U;
    rtb_DataTypeConversion3_h[4] = rtb_MinMax5;
    rtb_DataTypeConversion3_h[5] = rtb_BitwiseOR1;
    rtb_DataTypeConversion3_h[6] = 0U;
    rtb_DataTypeConversion3_h[7] = 0U;
    rtb_DataTypeConversion3_h[8] = 0U;
    rtb_DataTypeConversion3_h[9] = 0U;
    rtb_DataTypeConversion3_h[10] = 0U;
    rtb_DataTypeConversion3_h[11] = 0U;
    rtb_DataTypeConversion3_h[12] = 0U;
    rtb_DataTypeConversion3_h[13] = 0U;
    rtb_DataTypeConversion3_h[14] = 0U;
    rtb_DataTypeConversion3_h[15] = 0U;
    rtb_DataTypeConversion3_h[16] = 0U;

    /* MATLAB Function: '<S156>/MATLAB Function' */
    message = 0U;
    for (i = 0; i < 17; i++) {
      message ^= rtb_DataTypeConversion3_h[i];
      for (rtb_MinMax = 0; rtb_MinMax < 8; rtb_MinMax++) {
        if ((message & 128U) != 0U) {
          message = (uint8)((uint8)(message << 1) ^ 29);
        } else {
          message <<= 1;
        }
      }
    }

    /* MinMax: '<S688>/MinMax5' incorporates:
     *  DataTypeConversion: '<S156>/Data Type Conversion4'
     *  MATLAB Function: '<S156>/MATLAB Function'
     */
    rtb_MinMax5 = message;

    /* End of Outputs for SubSystem: '<S147>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S147>/If Action Subsystem' incorporates:
     *  ActionPort: '<S152>/Action Port'
     */
    /* DataTypeConversion: '<S154>/Data Type Conversion3' incorporates:
     *  Constant: '<S135>/constant1'
     *  Constant: '<S135>/constant10'
     *  Constant: '<S135>/constant11'
     *  Constant: '<S135>/constant12'
     *  Constant: '<S135>/constant13'
     *  Constant: '<S135>/constant2'
     *  Constant: '<S135>/constant3'
     *  Constant: '<S135>/constant4'
     *  Constant: '<S135>/constant5'
     *  Constant: '<S135>/constant6'
     *  Constant: '<S135>/constant7'
     *  Constant: '<S135>/constant8'
     *  Constant: '<S135>/constant9'
     *  S-Function (sfix_bitop): '<S135>/BitwiseOR'
     */
    rtb_DataTypeConversion3_p[0] = 0U;
    rtb_DataTypeConversion3_p[1] = 0U;
    rtb_DataTypeConversion3_p[2] = rtb_MinMax5;
    rtb_DataTypeConversion3_p[3] = rtb_BitwiseOR1;
    rtb_DataTypeConversion3_p[4] = 0U;
    rtb_DataTypeConversion3_p[5] = 0U;
    rtb_DataTypeConversion3_p[6] = 0U;
    rtb_DataTypeConversion3_p[7] = 0U;
    rtb_DataTypeConversion3_p[8] = 0U;
    rtb_DataTypeConversion3_p[9] = 0U;
    rtb_DataTypeConversion3_p[10] = 0U;
    rtb_DataTypeConversion3_p[11] = 0U;
    rtb_DataTypeConversion3_p[12] = 0U;
    rtb_DataTypeConversion3_p[13] = 0U;
    rtb_DataTypeConversion3_p[14] = 0U;

    /* MATLAB Function: '<S154>/MATLAB Function' */
    message = MAX_uint8_T;
    for (i = 0; i < 15; i++) {
      message ^= rtb_DataTypeConversion3_p[i];
      for (rtb_MinMax = 0; rtb_MinMax < 8; rtb_MinMax++) {
        if ((message & 128U) != 0U) {
          message = (uint8)((uint8)(message << 1) ^ 29);
        } else {
          message <<= 1;
        }
      }
    }

    /* MinMax: '<S688>/MinMax5' incorporates:
     *  DataTypeConversion: '<S154>/Data Type Conversion4'
     *  MATLAB Function: '<S154>/MATLAB Function'
     */
    rtb_MinMax5 = (uint8)(message ^ 255);

    /* End of Outputs for SubSystem: '<S147>/If Action Subsystem' */
  }

  /* End of If: '<S147>/If' */

  /* RelationalOperator: '<S146>/Equal' incorporates:
   *  Constant: '<S135>/constant'
   */
  VHAL_BMS1CSErr_flg = (rtb_MinMax5 != 0);

  /* Switch: '<S146>/Switch' incorporates:
   *  Constant: '<S135>/KHAL_CAN3BMS1E2E_flg'
   *  RelationalOperator: '<S146>/Relational Operator2'
   *  Switch: '<S146>/Switch1'
   *  UnitDelay: '<S146>/Unit Delay'
   */
  if (SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_n <= 0) {
    /* MinMax: '<S166>/MinMax' */
    rtb_MinMax = 0;
  } else {
    if (KHAL_CAN3BMS1E2E_flg) {
      /* Switch: '<S146>/Switch1' incorporates:
       *  Constant: '<S146>/Constant65'
       */
      i = 14;
    } else {
      /* Switch: '<S146>/Switch1' incorporates:
       *  Constant: '<S146>/Constant3'
       */
      i = 15;
    }

    /* MinMax: '<S166>/MinMax' incorporates:
     *  Constant: '<S146>/Constant2'
     *  Sum: '<S146>/Add1'
     *  Switch: '<S146>/Switch1'
     */
    rtb_MinMax = i + 1;
  }

  /* End of Switch: '<S146>/Switch' */

  /* SignalConversion generated from: '<S149>/Delay' incorporates:
   *  Constant: '<S135>/constant1'
   *  Constant: '<S135>/constant10'
   *  Constant: '<S135>/constant11'
   *  Constant: '<S135>/constant12'
   *  Constant: '<S135>/constant13'
   *  Constant: '<S135>/constant2'
   *  Constant: '<S135>/constant3'
   *  Constant: '<S135>/constant4'
   *  Constant: '<S135>/constant5'
   *  Constant: '<S135>/constant6'
   *  Constant: '<S135>/constant7'
   *  Constant: '<S135>/constant8'
   *  Constant: '<S135>/constant9'
   */
  rtb_DataTypeConversion3_p[0] = 0U;
  rtb_DataTypeConversion3_p[1] = 0U;
  rtb_DataTypeConversion3_p[2] = rtb_BitwiseOR;
  rtb_DataTypeConversion3_p[3] = rtb_BitwiseOR1;
  rtb_DataTypeConversion3_p[4] = 0U;
  rtb_DataTypeConversion3_p[5] = 0U;
  rtb_DataTypeConversion3_p[6] = 0U;
  rtb_DataTypeConversion3_p[7] = 0U;
  rtb_DataTypeConversion3_p[8] = 0U;
  rtb_DataTypeConversion3_p[9] = 0U;
  rtb_DataTypeConversion3_p[10] = 0U;
  rtb_DataTypeConversion3_p[11] = 0U;
  rtb_DataTypeConversion3_p[12] = 0U;
  rtb_DataTypeConversion3_p[13] = 0U;
  rtb_DataTypeConversion3_p[14] = 0U;
  for (i = 0; i < 15; i++) {
    /* Logic: '<S149>/Logical Operator' incorporates:
     *  Delay: '<S149>/Delay'
     *  Delay: '<S149>/Delay1'
     *  RelationalOperator: '<S149>/Relational Operator'
     */
    rtb_LogicalOperator[i] = ((rtb_DataTypeConversion3_p[i] !=
      SWC_APP_type_ARID_DEF.Delay_DSTATE[i]) &&
      SWC_APP_type_ARID_DEF.Delay1_DSTATE);
  }

  /* Logic: '<S146>/Logical Operator1' incorporates:
   *  UnitDelay: '<S146>/Unit Delay'
   */
  rtb_LogicalOperator5 = rtb_LogicalOperator[0];
  for (i = 0; i < 14; i++) {
    rtb_LogicalOperator5 = (rtb_LogicalOperator5 || rtb_LogicalOperator[i + 1]);
  }

  /* Outputs for Enabled SubSystem: '<S146>/Subsystem' */
  SWC_APP_type_Subsystem(rtb_LogicalOperator5, 0U,
    SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_n, &SWC_APP_type_ARID_DEF.Equal1_h);

  /* End of Logic: '<S146>/Logical Operator1' */
  /* End of Outputs for SubSystem: '<S146>/Subsystem' */

  /* Switch: '<S148>/Switch2' incorporates:
   *  Constant: '<S148>/Constant1'
   *  Constant: '<S148>/Constant2'
   *  Logic: '<S146>/Logical Operator'
   *  Sum: '<S148>/Subtract2'
   *  Switch: '<S148>/Switch1'
   *  UnitDelay: '<S148>/Unit Delay1'
   */
  if (!SWC_APP_type_ARID_DEF.Equal1_h) {
    tmp_1 = 0U;
  } else {
    tmp_1 = (uint16)(SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_b + 1U);
  }

  /* DataTypeConversion: '<S148>/Data Type Conversion' incorporates:
   *  MinMax: '<S148>/MinMax'
   *  Switch: '<S148>/Switch1'
   *  Switch: '<S148>/Switch2'
   *  UnitDelay: '<S148>/Unit Delay1'
   */
  tmp_0 = fmod(floor(fmin(SWC_APP_type_ConstB.Saturation, tmp_1)), 65536.0);
  SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_b = (uint16)(tmp_0 < 0.0 ? (sint32)
    (uint16)-(sint16)(uint16)-tmp_0 : (sint32)(uint16)tmp_0);

  /* Switch: '<S151>/Switch2' incorporates:
   *  RelationalOperator: '<S146>/Equal1'
   *  UnitDelay: '<S146>/Unit Delay'
   */
  if (SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_n == 0) {
    /* Switch: '<S18>/Switch2' incorporates:
     *  Constant: '<S146>/Constant8'
     *  Sum: '<S151>/Subtract2'
     *  UnitDelay: '<S151>/Unit Delay1'
     */
    rtb_Prelookup1_o2_n = SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE + 0.001F;
  } else {
    /* Switch: '<S151>/Switch1' incorporates:
     *  Constant: '<S151>/Constant1'
     *  Switch: '<S18>/Switch2'
     */
    rtb_Prelookup1_o2_n = 0.0F;
  }

  /* End of Switch: '<S151>/Switch2' */

  /* Switch: '<S151>/Switch' incorporates:
   *  RelationalOperator: '<S151>/GreaterThan'
   *  UnitDelay: '<S151>/Unit Delay1'
   */
  if (SWC_APP_type_ConstB.Gain <= rtb_Prelookup1_o2_n) {
    SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE = SWC_APP_type_ConstB.Gain;
  } else {
    SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE = rtb_Prelookup1_o2_n;
  }

  /* End of Switch: '<S151>/Switch' */

  /* Logic: '<S146>/Logical Operator4' incorporates:
   *  Constant: '<S146>/Constant'
   *  Logic: '<S146>/Logical Operator2'
   *  RelationalOperator: '<S146>/Relational Operator'
   *  RelationalOperator: '<S146>/Relational Operator1'
   *  RelationalOperator: '<S146>/Relational Operator3'
   *  Sum: '<S146>/Add3'
   *  UnitDelay: '<S146>/Unit Delay'
   *  UnitDelay: '<S146>/Unit Delay3'
   *  UnitDelay: '<S148>/Unit Delay1'
   *  UnitDelay: '<S151>/Unit Delay1'
   */
  VHAL_BMS1RCErr_flg = (((rtb_MinMax - SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_n >=
    2) || (SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_b >= 1) ||
    (SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE >= SWC_APP_type_ConstB.Gain)) &&
                        SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_j);

  /* Sum: '<S158>/Add' incorporates:
   *  Constant: '<S158>/gain'
   *  DataTypeConversion: '<S158>/Data Type Conversion'
   *  Product: '<S158>/Product'
   */
  VHAL_HVBattVolt_V = (float32)rtb_TmpSignalConversionAtR_CA_l.CAN3_HVBattVolt *
    0.1F;

  /* SignalConversion generated from: '<S2>/R_CAN3_BMS6_CAN3_SG_BMS6' incorporates:
   *  Inport: '<Root>/R_CAN3_BMS6_CAN3_SG_BMS6'
   */
  (void)Rte_Read_R_CAN3_BMS6_CAN3_SG_BMS6(&rtb_TmpSignalConversionAtR_CA_k);

  /* S-Function (sfix_bitop): '<S136>/BitwiseAND' incorporates:
   *  ArithShift: '<S136>/LeftShift'
   */
  rtb_BitwiseOR1 = (uint8)(rtb_TmpSignalConversionAtR_CA_k.CAN3_HVBContactorSta <<
    2);

  /* If: '<S165>/If' incorporates:
   *  Constant: '<S136>/KHAL_CAN3BMS6E2E_flg'
   *  DataTypeConversion: '<S165>/Data Type Conversion'
   */
  if (KHAL_CAN3BMS6E2E_flg) {
    /* Outputs for IfAction SubSystem: '<S165>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S171>/Action Port'
     */
    /* DataTypeConversion: '<S174>/Data Type Conversion3' incorporates:
     *  Constant: '<S136>/0x3B'
     *  Constant: '<S136>/0xDB'
     *  Constant: '<S136>/constant1'
     *  Constant: '<S136>/constant10'
     *  Constant: '<S136>/constant2'
     *  Constant: '<S136>/constant3'
     *  Constant: '<S136>/constant4'
     *  Constant: '<S136>/constant5'
     *  Constant: '<S136>/constant6'
     *  Constant: '<S136>/constant7'
     *  Constant: '<S136>/constant8'
     *  Constant: '<S136>/constant9'
     *  S-Function (sfix_bitop): '<S136>/BitwiseOR'
     */
    rtb_DataTypeConversion3_j[0] = 59U;
    rtb_DataTypeConversion3_j[1] = 219U;
    rtb_DataTypeConversion3_j[2] = 0U;
    rtb_DataTypeConversion3_j[3] = 0U;
    rtb_DataTypeConversion3_j[4] = 0U;
    rtb_DataTypeConversion3_j[5] = 0U;
    rtb_DataTypeConversion3_j[6] = 0U;
    rtb_DataTypeConversion3_j[7] = 0U;
    rtb_DataTypeConversion3_j[8] = 0U;
    rtb_DataTypeConversion3_j[9] = rtb_BitwiseOR1;
    rtb_DataTypeConversion3_j[10] = 0U;
    rtb_DataTypeConversion3_j[11] = 0U;
    rtb_DataTypeConversion3_j[12] = 0U;

    /* MATLAB Function: '<S174>/MATLAB Function' */
    message = 0U;
    for (i = 0; i < 13; i++) {
      message ^= rtb_DataTypeConversion3_j[i];
      for (rtb_MinMax = 0; rtb_MinMax < 8; rtb_MinMax++) {
        if ((message & 128U) != 0U) {
          message = (uint8)((uint8)(message << 1) ^ 29);
        } else {
          message <<= 1;
        }
      }
    }

    /* MinMax: '<S688>/MinMax5' incorporates:
     *  DataTypeConversion: '<S174>/Data Type Conversion4'
     *  MATLAB Function: '<S174>/MATLAB Function'
     */
    rtb_MinMax5 = message;

    /* End of Outputs for SubSystem: '<S165>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S165>/If Action Subsystem' incorporates:
     *  ActionPort: '<S170>/Action Port'
     */
    /* DataTypeConversion: '<S172>/Data Type Conversion3' incorporates:
     *  Constant: '<S136>/constant1'
     *  Constant: '<S136>/constant10'
     *  Constant: '<S136>/constant2'
     *  Constant: '<S136>/constant3'
     *  Constant: '<S136>/constant4'
     *  Constant: '<S136>/constant5'
     *  Constant: '<S136>/constant6'
     *  Constant: '<S136>/constant7'
     *  Constant: '<S136>/constant8'
     *  Constant: '<S136>/constant9'
     *  S-Function (sfix_bitop): '<S136>/BitwiseOR'
     */
    rtb_DataTypeConversion3[0] = 0U;
    rtb_DataTypeConversion3[1] = 0U;
    rtb_DataTypeConversion3[2] = 0U;
    rtb_DataTypeConversion3[3] = 0U;
    rtb_DataTypeConversion3[4] = 0U;
    rtb_DataTypeConversion3[5] = 0U;
    rtb_DataTypeConversion3[6] = 0U;
    rtb_DataTypeConversion3[7] = rtb_BitwiseOR1;
    rtb_DataTypeConversion3[8] = 0U;
    rtb_DataTypeConversion3[9] = 0U;
    rtb_DataTypeConversion3[10] = 0U;

    /* MATLAB Function: '<S172>/MATLAB Function' */
    message = MAX_uint8_T;
    for (i = 0; i < 11; i++) {
      message ^= rtb_DataTypeConversion3[i];
      for (rtb_MinMax = 0; rtb_MinMax < 8; rtb_MinMax++) {
        if ((message & 128U) != 0U) {
          message = (uint8)((uint8)(message << 1) ^ 29);
        } else {
          message <<= 1;
        }
      }
    }

    /* MinMax: '<S688>/MinMax5' incorporates:
     *  DataTypeConversion: '<S172>/Data Type Conversion4'
     *  MATLAB Function: '<S172>/MATLAB Function'
     */
    rtb_MinMax5 = (uint8)(message ^ 255);

    /* End of Outputs for SubSystem: '<S165>/If Action Subsystem' */
  }

  /* End of If: '<S165>/If' */

  /* RelationalOperator: '<S164>/Equal' incorporates:
   *  Constant: '<S136>/constant'
   */
  VHAL_BMS6CSErr_flg = (rtb_MinMax5 != 0);

  /* Switch: '<S164>/Switch' incorporates:
   *  Constant: '<S136>/KHAL_CAN3BMS6E2E_flg'
   *  RelationalOperator: '<S164>/Relational Operator2'
   *  Switch: '<S164>/Switch1'
   *  UnitDelay: '<S164>/Unit Delay'
   */
  if (SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_h <= 0) {
    /* MinMax: '<S166>/MinMax' */
    rtb_MinMax = 0;
  } else {
    if (KHAL_CAN3BMS6E2E_flg) {
      /* Switch: '<S164>/Switch1' incorporates:
       *  Constant: '<S164>/Constant65'
       */
      i = 14;
    } else {
      /* Switch: '<S164>/Switch1' incorporates:
       *  Constant: '<S164>/Constant3'
       */
      i = 15;
    }

    /* MinMax: '<S166>/MinMax' incorporates:
     *  Constant: '<S164>/Constant2'
     *  Sum: '<S164>/Add1'
     *  Switch: '<S164>/Switch1'
     */
    rtb_MinMax = i + 1;
  }

  /* End of Switch: '<S164>/Switch' */

  /* SignalConversion generated from: '<S167>/Delay' incorporates:
   *  Constant: '<S136>/constant1'
   *  Constant: '<S136>/constant10'
   *  Constant: '<S136>/constant2'
   *  Constant: '<S136>/constant3'
   *  Constant: '<S136>/constant4'
   *  Constant: '<S136>/constant5'
   *  Constant: '<S136>/constant6'
   *  Constant: '<S136>/constant7'
   *  Constant: '<S136>/constant8'
   *  Constant: '<S136>/constant9'
   *  S-Function (sfix_bitop): '<S136>/BitwiseOR'
   */
  rtb_DataTypeConversion3[0] = 0U;
  rtb_DataTypeConversion3[1] = 0U;
  rtb_DataTypeConversion3[2] = 0U;
  rtb_DataTypeConversion3[3] = 0U;
  rtb_DataTypeConversion3[4] = 0U;
  rtb_DataTypeConversion3[5] = 0U;
  rtb_DataTypeConversion3[6] = 0U;
  rtb_DataTypeConversion3[7] = rtb_BitwiseOR1;
  rtb_DataTypeConversion3[8] = 0U;
  rtb_DataTypeConversion3[9] = 0U;
  rtb_DataTypeConversion3[10] = 0U;
  for (i = 0; i < 11; i++) {
    /* Logic: '<S167>/Logical Operator' incorporates:
     *  Delay: '<S167>/Delay'
     *  Delay: '<S167>/Delay1'
     *  RelationalOperator: '<S167>/Relational Operator'
     */
    rtb_LogicalOperator_e0[i] = ((rtb_DataTypeConversion3[i] !=
      SWC_APP_type_ARID_DEF.Delay_DSTATE_o[i]) &&
      SWC_APP_type_ARID_DEF.Delay1_DSTATE_o);
  }

  /* Logic: '<S164>/Logical Operator1' incorporates:
   *  UnitDelay: '<S164>/Unit Delay'
   */
  rtb_LogicalOperator5 = rtb_LogicalOperator_e0[0];
  for (i = 0; i < 10; i++) {
    rtb_LogicalOperator5 = (rtb_LogicalOperator5 || rtb_LogicalOperator_e0[i + 1]);
  }

  /* Outputs for Enabled SubSystem: '<S164>/Subsystem' */
  SWC_APP_type_Subsystem(rtb_LogicalOperator5, 0U,
    SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_h, &SWC_APP_type_ARID_DEF.Equal1);

  /* End of Logic: '<S164>/Logical Operator1' */
  /* End of Outputs for SubSystem: '<S164>/Subsystem' */

  /* Switch: '<S166>/Switch2' incorporates:
   *  Constant: '<S166>/Constant1'
   *  Constant: '<S166>/Constant2'
   *  Logic: '<S164>/Logical Operator'
   *  Sum: '<S166>/Subtract2'
   *  Switch: '<S166>/Switch1'
   *  UnitDelay: '<S166>/Unit Delay1'
   */
  if (!SWC_APP_type_ARID_DEF.Equal1) {
    tmp_1 = 0U;
  } else {
    tmp_1 = (uint16)(SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_j + 1U);
  }

  /* DataTypeConversion: '<S166>/Data Type Conversion' incorporates:
   *  MinMax: '<S166>/MinMax'
   *  Switch: '<S166>/Switch1'
   *  Switch: '<S166>/Switch2'
   *  UnitDelay: '<S166>/Unit Delay1'
   */
  tmp_0 = fmod(floor(fmin(SWC_APP_type_ConstB.Saturation_e, tmp_1)), 65536.0);
  SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_j = (uint16)(tmp_0 < 0.0 ? (sint32)
    (uint16)-(sint16)(uint16)-tmp_0 : (sint32)(uint16)tmp_0);

  /* Switch: '<S169>/Switch2' incorporates:
   *  RelationalOperator: '<S164>/Equal1'
   *  UnitDelay: '<S164>/Unit Delay'
   */
  if (SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_h == 0) {
    /* Switch: '<S18>/Switch2' incorporates:
     *  Constant: '<S164>/Constant8'
     *  Sum: '<S169>/Subtract2'
     *  UnitDelay: '<S169>/Unit Delay1'
     */
    rtb_Prelookup1_o2_n = SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_f + 0.001F;
  } else {
    /* Switch: '<S169>/Switch1' incorporates:
     *  Constant: '<S169>/Constant1'
     *  Switch: '<S18>/Switch2'
     */
    rtb_Prelookup1_o2_n = 0.0F;
  }

  /* End of Switch: '<S169>/Switch2' */

  /* Switch: '<S169>/Switch' incorporates:
   *  RelationalOperator: '<S169>/GreaterThan'
   *  UnitDelay: '<S169>/Unit Delay1'
   */
  if (SWC_APP_type_ConstB.Gain_l <= rtb_Prelookup1_o2_n) {
    SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_f = SWC_APP_type_ConstB.Gain_l;
  } else {
    SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_f = rtb_Prelookup1_o2_n;
  }

  /* End of Switch: '<S169>/Switch' */

  /* Logic: '<S164>/Logical Operator4' incorporates:
   *  Constant: '<S164>/Constant'
   *  Logic: '<S164>/Logical Operator2'
   *  RelationalOperator: '<S164>/Relational Operator'
   *  RelationalOperator: '<S164>/Relational Operator1'
   *  RelationalOperator: '<S164>/Relational Operator3'
   *  Sum: '<S164>/Add3'
   *  UnitDelay: '<S164>/Unit Delay'
   *  UnitDelay: '<S164>/Unit Delay3'
   *  UnitDelay: '<S166>/Unit Delay1'
   *  UnitDelay: '<S169>/Unit Delay1'
   */
  VHAL_BMS6RCErr_flg = (((rtb_MinMax - SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_h >=
    2) || (SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_j >= 1) ||
    (SWC_APP_type_ARID_DEF.UnitDelay1_DSTATE_f >= SWC_APP_type_ConstB.Gain_l)) &&
                        SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_a);

  /* DataTypeConversion: '<S133>/UnitConverter5' */
  VHAL_HVBContactorSta_flg =
    (rtb_TmpSignalConversionAtR_CA_k.CAN3_HVBContactorSta != 0);

  /* SignalConversion generated from: '<S2>/R_CAN3_FD3_C100_0_CAN3_SG_FD3_C100_0' incorporates:
   *  Inport: '<Root>/R_CAN3_FD3_C100_0_CAN3_SG_FD3_C100_0'
   */
  (void)Rte_Read_R_CAN3_FD3_C100_0_CAN3_SG_FD3_C100_0
    (&rtb_TmpSignalConversionAtR_CA_d);

  /* DataTypeConversion: '<S133>/UnitConverter6' */
  VHAL_BatteryMode_enum = rtb_TmpSignalConversionAtR_CA_d.CAN3_BatteryMode;

  /* Sum: '<S181>/Add' incorporates:
   *  Constant: '<S181>/gain'
   *  DataTypeConversion: '<S181>/Data Type Conversion'
   *  Product: '<S181>/Product'
   */
  VHAL_RrCoolantflow_Lpmin = (float32)
    rtb_TmpSignalConversionAtR_CA_d.CAN3_Rr_Coolantflow * 0.25F;

  /* Sum: '<S182>/Add' incorporates:
   *  DataTypeConversion: '<S182>/Data Type Conversion'
   */
  VHAL_RrCoolanttemp_C = (float32)
    rtb_TmpSignalConversionAtR_CA_d.CAN3_Rr_Coolanttemp - 40.0F;

  /* SignalConversion generated from: '<S2>/R_CAN3_FD3_VCU1_CAN3_SG_FD3_VCU1' incorporates:
   *  Inport: '<Root>/R_CAN3_FD3_VCU1_CAN3_SG_FD3_VCU1'
   */
  (void)Rte_Read_R_CAN3_FD3_VCU1_CAN3_SG_FD3_VCU1
    (&rtb_TmpSignalConversionAtR_CA_g);

  /* DataTypeConversion: '<S133>/UnitConverter9' */
  VHAL_ActiveDischReq_flg = (rtb_TmpSignalConversionAtR_CA_g.CAN3_ActiveDischReq
    != 0);

  /* DataTypeConversion: '<S133>/UnitConverter10' */
  VHAL_CSVCU1_enum = rtb_TmpSignalConversionAtR_CA_g.CAN3_CS_VCU1;

  /* DataTypeConversion: '<S133>/UnitConverter11' */
  VHAL_PwrSta_enum = rtb_TmpSignalConversionAtR_CA_g.CAN3_PwrSta;

  /* DataTypeConversion: '<S133>/UnitConverter12' */
  VHAL_RCVCU1_enum = rtb_TmpSignalConversionAtR_CA_g.CAN3_RC_VCU1;

  /* DataTypeConversion: '<S133>/UnitConverter13' */
  VHAL_ShiftGearPosn_enum = rtb_TmpSignalConversionAtR_CA_g.CAN3_ShiftGearPosn;

  /* SignalConversion generated from: '<S2>/R_CAN3_FD3_VCU2_CAN3_SG_FD3_VCU2' incorporates:
   *  Inport: '<Root>/R_CAN3_FD3_VCU2_CAN3_SG_FD3_VCU2'
   */
  (void)Rte_Read_R_CAN3_FD3_VCU2_CAN3_SG_FD3_VCU2
    (&rtb_TmpSignalConversionAtR_CAN3);

  /* DataTypeConversion: '<S133>/UnitConverter14' */
  VHAL_CSVCU2CAN1_enum = rtb_TmpSignalConversionAtR_CAN3.CAN3_CS_VCU2_CAN1;

  /* DataTypeConversion: '<S133>/UnitConverter15' */
  VHAL_RCVCU2CAN1_enum = rtb_TmpSignalConversionAtR_CAN3.CAN3_RC_VCU2_CAN1;

  /* DataTypeConversion: '<S133>/UnitConverter16' */
  VHAL_RrActvDmpDisabReq_flg =
    (rtb_TmpSignalConversionAtR_CAN3.CAN3_Rr_ActvDmpDisabReq != 0);

  /* DataTypeConversion: '<S133>/UnitConverter17' */
  VHAL_RrMCUEnaReq_flg = (rtb_TmpSignalConversionAtR_CAN3.CAN3_Rr_MCUEnaReq != 0);

  /* SignalConversion generated from: '<S2>/R_CAN3_FD3_VCU5_CAN3_SG_FD3_VCU5' incorporates:
   *  Inport: '<Root>/R_CAN3_FD3_VCU5_CAN3_SG_FD3_VCU5'
   */
  (void)Rte_Read_R_CAN3_FD3_VCU5_CAN3_SG_FD3_VCU5
    (&rtb_TmpSignalConversionAtR_CA_m);

  /* DataTypeConversion: '<S133>/UnitConverter18' */
  VHAL_FDCVCURrSpdMaxReq_rpm =
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrSpdMax_Req;

  /* Sum: '<S199>/Add' incorporates:
   *  DataTypeConversion: '<S199>/Data Type Conversion'
   */
  VHAL_FDCVCURrSpdMinReq_rpm = (float32)
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrSpdMin_Req - 22000.0F;

  /* DataTypeConversion: '<S133>/UnitConverter20' */
  VHAL_FDCVCURrTMCtrlModeReq_enum =
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrTMCtrlMode_Req;

  /* Sum: '<S200>/Add' incorporates:
   *  DataTypeConversion: '<S200>/Data Type Conversion'
   */
  VHAL_FDCVCURrTMSpdReq_rpm = (float32)
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrTMSpd_Req - 22000.0F;

  /* Sum: '<S201>/Add' incorporates:
   *  Constant: '<S201>/gain'
   *  DataTypeConversion: '<S201>/Data Type Conversion'
   *  Product: '<S201>/Product'
   */
  VHAL_FDCVCURrTMTqReq_Nm = (float32)
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrTMTq_Req * 0.1F - 1000.0F;

  /* DataTypeConversion: '<S133>/UnitConverter23' */
  VHAL_FDCVCURrTqMaxReq_Nm =
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrTqMax_Req;

  /* Sum: '<S202>/Add' incorporates:
   *  DataTypeConversion: '<S202>/Data Type Conversion'
   */
  VHAL_FDCVCURrTqMinReq_Nm = (float32)
    rtb_TmpSignalConversionAtR_CA_m.CAN3_FDC_VCU_RrTqMin_Req - 1022.0F;

  /* SignalConversion generated from: '<S2>/R_CAN3_GW3_CE100_0_CAN3_SG_GW3_CE100_0' incorporates:
   *  Inport: '<Root>/R_CAN3_GW3_CE100_0_CAN3_SG_GW3_CE100_0'
   */
  (void)Rte_Read_R_CAN3_GW3_CE100_0_CAN3_SG_GW3_CE100_0
    (&rtb_TmpSignalConversionAtR_CA_c);

  /* DataTypeConversion: '<S133>/UnitConverter25' */
  VHAL_IVITimeDay_DAY = rtb_TmpSignalConversionAtR_CA_c.CAN3_IVI_Time_Day;

  /* DataTypeConversion: '<S133>/UnitConverter26' */
  VHAL_IVITimeHour_hr = rtb_TmpSignalConversionAtR_CA_c.CAN3_IVI_Time_Hour;

  /* DataTypeConversion: '<S133>/UnitConverter27' */
  VHAL_IVITimeMinute_min = rtb_TmpSignalConversionAtR_CA_c.CAN3_IVI_Time_Minute;

  /* DataTypeConversion: '<S133>/UnitConverter28' */
  VHAL_IVITimeMonth_MONTH = rtb_TmpSignalConversionAtR_CA_c.CAN3_IVI_Time_Month;

  /* DataTypeConversion: '<S133>/UnitConverter29' */
  VHAL_IVITimeSecond_s = rtb_TmpSignalConversionAtR_CA_c.CAN3_IVI_Time_Second;

  /* Sum: '<S209>/Add' incorporates:
   *  Constant: '<S209>/gain'
   *  DataTypeConversion: '<S209>/Data Type Conversion'
   *  Product: '<S209>/Product'
   */
  VHAL_VehSpeed_kph = (float32)rtb_TmpSignalConversionAtR_CA_c.CAN3_VehSpeed *
    0.125F;

  /* BusCreator: '<S133>/bus_creator' */
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidBMS1_flg =
    VHAL_CANMsgInvalidBMS1_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS1CSErr_flg = VHAL_BMS1CSErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS1RCErr_flg = VHAL_BMS1RCErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_HVBattVolt_V = VHAL_HVBattVolt_V;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidBMS6_flg =
    VHAL_CANMsgInvalidBMS6_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS6CSErr_flg = VHAL_BMS6CSErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BMS6RCErr_flg = VHAL_BMS6RCErr_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_HVBContactorSta_flg =
    VHAL_HVBContactorSta_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3C1000_flg =
    VHAL_CANMsgInvalidFD3C1000_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_BatteryMode_enum =
    VHAL_BatteryMode_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrCoolantflow_Lpmin =
    VHAL_RrCoolantflow_Lpmin;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrCoolanttemp_C =
    VHAL_RrCoolanttemp_C;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU1_flg =
    VHAL_CANMsgInvalidFD3VCU1_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_ActiveDischReq_flg =
    VHAL_ActiveDischReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CSVCU1_enum = VHAL_CSVCU1_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_PwrSta_enum = VHAL_PwrSta_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RCVCU1_enum = VHAL_RCVCU1_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_ShiftGearPosn_enum =
    VHAL_ShiftGearPosn_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU2_flg =
    VHAL_CANMsgInvalidFD3VCU2_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CSVCU2CAN1_enum =
    VHAL_CSVCU2CAN1_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RCVCU2CAN1_enum =
    VHAL_RCVCU2CAN1_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrActvDmpDisabReq_flg =
    VHAL_RrActvDmpDisabReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_RrMCUEnaReq_flg =
    VHAL_RrMCUEnaReq_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidFD3VCU5_flg =
    VHAL_CANMsgInvalidFD3VCU5_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrSpdMaxReq_rpm =
    VHAL_FDCVCURrSpdMaxReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrSpdMinReq_rpm =
    VHAL_FDCVCURrSpdMinReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMCtrlModeReq_enum =
    VHAL_FDCVCURrTMCtrlModeReq_enum;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMSpdReq_rpm =
    VHAL_FDCVCURrTMSpdReq_rpm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTMTqReq_Nm =
    VHAL_FDCVCURrTMTqReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTqMaxReq_Nm =
    VHAL_FDCVCURrTqMaxReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_FDCVCURrTqMinReq_Nm =
    VHAL_FDCVCURrTqMinReq_Nm;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_CANMsgInvalidGW3CE1000_flg =
    VHAL_CANMsgInvalidGW3CE1000_flg;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeDay_DAY = VHAL_IVITimeDay_DAY;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeHour_hr = VHAL_IVITimeHour_hr;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeMinute_min =
    VHAL_IVITimeMinute_min;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeMonth_MONTH =
    VHAL_IVITimeMonth_MONTH;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_IVITimeSecond_s =
    VHAL_IVITimeSecond_s;
  SWC_APP_type_ARID_DEF.bus_creator_e.VHAL_VehSpeed_kph = VHAL_VehSpeed_kph;

  /* Outputs for Atomic SubSystem: '<S2>/INP' */
  SWC_APP_type_INP();

  /* End of Outputs for SubSystem: '<S2>/INP' */

  /* Chart: '<S777>/Chart' incorporates:
   *  Constant: '<S782>/Constant1'
   *  Constant: '<S782>/Constant2'
   *  Constant: '<S782>/Constant4'
   *  Constant: '<S782>/Constant5'
   *  Constant: '<S782>/T1'
   *  Constant: '<S782>/T2'
   *  RelationalOperator: '<S782>/Relational Operator'
   *  RelationalOperator: '<S782>/Relational Operator1'
   */
  if (SWC_APP_type_ARID_DEF.bus_creator.VINP_HVBContactorSta_flg &&
      (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum != 6))
  {
    /* Outputs for Function Call SubSystem: '<S777>/Function-Call Subsystem' */
    /* Outputs for Atomic SubSystem: '<S782>/debounce' */
    SWC_APP_type_debounce
      ((SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide <=
        Diag2_f32_UdcLowStopDerat_C), Diag2_int16_HvLowErrHeal_C,
       Diag2_int16_HvLowErrErr_C, &rtb_Status_g,
       &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_o);

    /* End of Outputs for SubSystem: '<S782>/debounce' */

    /* SignalConversion: '<S782>/Signal Conversion' incorporates:
     *  Constant: '<S782>/Constant1'
     *  Constant: '<S782>/Constant2'
     *  Constant: '<S782>/T2'
     *  RelationalOperator: '<S782>/Relational Operator'
     */
    VDGL_HVLowErr_flg = rtb_Status_g;

    /* Outputs for Atomic SubSystem: '<S782>/debounce1' */
    SWC_APP_type_debounce
      ((SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide <=
        Diag2_f32_UdcLowStartDerat_C), Diag2_int16_HvLowWarnHeal_C,
       Diag2_int16_HvLowWarnErr_C, &rtb_Status_la,
       &SWC_APP_type_ARID_DEF.ARID_DEF_debounce1_lx);

    /* End of Outputs for SubSystem: '<S782>/debounce1' */

    /* SignalConversion: '<S782>/Signal Conversion1' incorporates:
     *  Constant: '<S782>/Constant4'
     *  Constant: '<S782>/Constant5'
     *  Constant: '<S782>/T1'
     *  RelationalOperator: '<S782>/Relational Operator1'
     */
    VDGL_HVLowWarn_flg = rtb_Status_la;

    /* End of Outputs for SubSystem: '<S777>/Function-Call Subsystem' */
  }

  /* End of Chart: '<S777>/Chart' */

  /* Outputs for Atomic SubSystem: '<S13>/ER_FF' */
  /* Outputs for Atomic SubSystem: '<S709>/Delay' */
  rtb_UnitDelay_bk = SWC_APP_type_Delay(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_n);

  /* End of Outputs for SubSystem: '<S709>/Delay' */

  /* Switch: '<S772>/SWT' incorporates:
   *  Constant: '<S706>/dT1'
   *  Constant: '<S706>/dT10'
   *  Constant: '<S706>/dT11'
   *  Constant: '<S706>/dT12'
   *  Constant: '<S706>/dT13'
   *  Constant: '<S706>/dT14'
   *  Constant: '<S706>/dT15'
   *  Constant: '<S706>/dT16'
   *  Constant: '<S706>/dT17'
   *  Constant: '<S706>/dT18'
   *  Constant: '<S706>/dT3'
   *  Constant: '<S706>/dT4'
   *  Constant: '<S706>/dT5'
   *  Constant: '<S706>/dT6'
   *  Constant: '<S706>/dT7'
   *  Constant: '<S706>/dT8'
   *  Constant: '<S706>/dT9'
   *  Logic: '<S13>/Logical Operator'
   *  Logic: '<S706>/Logical Operator10'
   *  Logic: '<S706>/Logical Operator11'
   *  Logic: '<S706>/Logical Operator13'
   *  Logic: '<S706>/Logical Operator15'
   *  Logic: '<S706>/Logical Operator18'
   *  Logic: '<S706>/Logical Operator2'
   *  Logic: '<S706>/Logical Operator20'
   *  Logic: '<S706>/Logical Operator22'
   *  Logic: '<S706>/Logical Operator24'
   *  Logic: '<S706>/Logical Operator26'
   *  Logic: '<S706>/Logical Operator28'
   *  Logic: '<S706>/Logical Operator30'
   *  Logic: '<S706>/Logical Operator32'
   *  Logic: '<S706>/Logical Operator34'
   *  Logic: '<S706>/Logical Operator4'
   *  Logic: '<S706>/Logical Operator6'
   *  Logic: '<S706>/Logical Operator8'
   */
  if (VDGL_OverSpdErr_flg || VDGL_HVOverErr_flg || VDGL_HVLowErr_flg ||
      (SWC_APP_type_ConstB.LogicalOperator1 && KDGL_bComLostVcuEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator3 && KDGL_bComInvaildVcuEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator5_m && KDGL_bPosSenrFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator7 && KDGL_bTempSensrFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator9 && KDGL_bCurrFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator12 && KDGL_bSicTempFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator14 && KDGL_bSicFltFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator16 && KDGL_bHvDcVoltFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator17 && KDGL_bEOPFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator19 && KDGL_bPCBTempFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator21 && KDGL_bOilTempFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator23 && KDGL_bWaterTempFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator25 && KDGL_bWaterTempFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator27 && KDGL_bIGNVoltFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator29 && KDGL_bPREREGFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator31 && KDGL_bVCC5VFaultEna_C) ||
      (SWC_APP_type_ConstB.LogicalOperator33 && KDGL_bVREF5VFaultEna_C)) {
    /* Switch: '<S772>/SWT' incorporates:
     *  Constant: '<S709>/true'
     */
    SWC_APP_type_ARID_DEF.SWT_h = true_MatlabRTW;
  } else {
    /* Switch: '<S772>/SWT' incorporates:
     *  Constant: '<S13>/Constant7'
     *  Switch: '<S771>/SWT'
     */
    SWC_APP_type_ARID_DEF.SWT_h = ((!Diag2_bRstFault_C) && rtb_UnitDelay_bk);
  }

  /* End of Switch: '<S772>/SWT' */

  /* Update for Atomic SubSystem: '<S709>/Delay' */
  SWC_APP_type_Delay_Update(SWC_APP_type_ARID_DEF.SWT_h,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_n);

  /* End of Update for SubSystem: '<S709>/Delay' */
  /* End of Outputs for SubSystem: '<S13>/ER_FF' */

  /* Switch: '<S13>/Diag3_Fault2Levelswt' incorporates:
   *  Constant: '<S13>/Diag3_Fault2LevelTrig_C'
   */
  if (DiagM_Fault2LevelTrig_C) {
    /* MinMax: '<S688>/MinMax5' incorporates:
     *  Constant: '<S13>/Diag3_Fault2LevelMor_C'
     */
    rtb_MinMax5 = DiagM_Fault2LevelMor_C;
  } else {
    /* MinMax: '<S688>/MinMax5' */
    rtb_MinMax5 = SWC_APP_type_ARID_DEF.SWT_h;
  }

  /* End of Switch: '<S13>/Diag3_Fault2Levelswt' */

  /* Logic: '<S13>/Logical Operator1' */
  DiagM_bOver2Stop = ((rtb_MinMax5 != 0) ||
                      (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.u8_VDSM_FltActn12_flg
                       != 0));

  /* Outputs for Atomic SubSystem: '<S10>/OpMod' */
  /* Chart: '<S597>/MotorMode' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S597>/Constant'
   *  Constant: '<S597>/Constant1'
   *  Constant: '<S597>/OpMod_ResolverEnt_C'
   *  Constant: '<S597>/OpMod_nRot2AfterRun_C'
   *  Constant: '<S597>/OpMod_tiDcha2AfterRun_C'
   *  Constant: '<S597>/OpMod_uDCSide2AfterRun_C'
   */
  if (SWC_APP_type_ARID_DEF.is_active_c9_opm_grc == 0U) {
    SWC_APP_type_ARID_DEF.is_active_c9_opm_grc = 1U;
    SWC_APP_type_ARID_DEF.is_c9_opm_grc = SWC_APP_type_IN_MotStM;
    SWC_APP_type_ARID_DEF.is_MotStM = SWC_APP_t_IN_PowerDownProcedure;
    SWC_APP_type_ARID_DEF.is_PowerDownProcedure =
      SWC_APP_typ_IN_PowerUpProcedure;
    SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Initial_i;
    VOPM_MotMod_enum = 0U;
  } else if (SWC_APP_type_ARID_DEF.is_c9_opm_grc == SWC_APP_type_IN_AfterRunMode)
  {
    VOPM_MotMod_enum = 6U;
    if (KOPM_FakeKL15_flg && (!DiagM_bOver2Stop)) {
      SWC_APP_type_ARID_DEF.is_c9_opm_grc = SWC_APP_type_IN_MotStM;
      SWC_APP_type_ARID_DEF.is_MotStM = SWC_APP_t_IN_PowerDownProcedure;
      SWC_APP_type_ARID_DEF.is_PowerDownProcedure =
        SWC_APP_typ_IN_PowerUpProcedure;
      SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_StandBy;
      VOPM_MotMod_enum = 1U;
    }
  } else {
    /* case IN_MotStM: */
    rtb_LogicalOperator5 = !KOPM_FakeKL15_flg;
    if ((rtb_LogicalOperator5 && (SWC_APP_type_ARID_DEF.OpMod_DchaTmr >
          OpMod_tiDcha2AfterRun_C) &&
         (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot <
          OpMod_nRot2AfterRun_C)) || (rtb_LogicalOperator5 &&
         (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide <
          OpMod_uDCSide2AfterRun_C) &&
         (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot <
          OpMod_nRot2AfterRun_C))) {
      exit_internal_PowerDownProcedur();
      SWC_APP_type_ARID_DEF.is_MotStM = 0;
      SWC_APP_type_ARID_DEF.is_c9_opm_grc = SWC_APP_type_IN_AfterRunMode;
      SWC_APP_type_ARID_DEF.OpMod_bPasDchaEna = false_MatlabRTW;
      VOPM_MotMod_enum = 6U;
    } else if (SWC_APP_type_ARID_DEF.is_MotStM == SWC_APP_type_IN_DischargeMode)
    {
      VOPM_MotMod_enum = 7U;
      if (DiagM_bOver2Stop) {
        SWC_APP_type_ARID_DEF.OpMod_bPasDchaEna = true_MatlabRTW;
        SWC_APP_type_ARID_DEF.is_MotStM = SWC_APP_t_IN_PowerDownProcedure;
        SWC_APP_type_ARID_DEF.is_PowerDownProcedure =
          SWC_APP_type_IN_FailureMode;
        VOPM_MotMod_enum = 5U;
      } else {
        SWC_APP_type_ARID_DEF.OpMod_DchaTmr++;
      }

      /* case IN_PowerDownProcedure: */
    } else if (SWC_APP_type_ARID_DEF.bus_creator.VINP_ActiveDischReq_flg &&
               (!SWC_APP_type_ARID_DEF.bus_creator.VINP_HVBContactorSta_flg) &&
               (!DiagM_bOver2Stop)) {
      exit_internal_PowerDownProcedur();
      SWC_APP_type_ARID_DEF.is_MotStM = SWC_APP_type_IN_DischargeMode;
      VOPM_MotMod_enum = 7U;
      SWC_APP_type_ARID_DEF.OpMod_DchaTmr = 0.0F;
    } else if (SWC_APP_type_ARID_DEF.is_PowerDownProcedure ==
               SWC_APP_type_IN_FailureMode) {
      VOPM_MotMod_enum = 5U;

      /* case IN_PowerUpProcedure: */
    } else if (DiagM_bOver2Stop) {
      SWC_APP_type_ARID_DEF.is_PowerUpProcedure = 0;
      SWC_APP_type_ARID_DEF.is_PowerDownProcedure = SWC_APP_type_IN_FailureMode;
      VOPM_MotMod_enum = 5U;
    } else {
      switch (SWC_APP_type_ARID_DEF.is_PowerUpProcedure) {
       case SWC_APP_type_IN_Boosting:
        VOPM_MotMod_enum = 12U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg ||
            (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum
             != 6) || (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum
                       != 0)) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       case SWC_APP_type_IN_DiagService:
        VOPM_MotMod_enum = 9U;
        if (!OpMod_bService_C) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       case SWC_APP_type_IN_Heating:
        VOPM_MotMod_enum = 11U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg ||
            (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum
             != 5) || (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum
                       != 0)) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       case SWC_APP_type_IN_Initial_i:
        VOPM_MotMod_enum = 0U;
        if (KOPM_FakeKL15_flg) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_StandBy;
          VOPM_MotMod_enum = 1U;
        }
        break;

       case SWC_APP_type_IN_Ready:
        VOPM_MotMod_enum = 2U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg &&
            (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum ==
             0) && (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum !=
                    0) &&
            SWC_APP_type_ARID_DEF.bus_creator.VINP_RrActvDmpDisabReq_flg) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Torque;
          VOPM_MotMod_enum = 3U;
          SWC_APP_type_ARID_DEF.OpMod_bMCUEna = true_MatlabRTW;
        } else if (SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg &&
                   (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum
                    == 1) &&
                   (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum !=
                    0) &&
                   SWC_APP_type_ARID_DEF.bus_creator.VINP_RrActvDmpDisabReq_flg)
        {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Speed;
          VOPM_MotMod_enum = 4U;
          SWC_APP_type_ARID_DEF.OpMod_bMCUEna = true_MatlabRTW;
        } else {
          rtb_LogicalOperator5 =
            !SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg;
          if (rtb_LogicalOperator5 &&
              (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum
               == 5) &&
              (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum == 0))
          {
            SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Heating;
            VOPM_MotMod_enum = 11U;
          } else if (rtb_LogicalOperator5 &&
                     (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum
                      == 6) &&
                     (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum ==
                      0)) {
            SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Boosting;
            VOPM_MotMod_enum = 12U;
            SWC_APP_type_ARID_DEF.OpMod_bBoostOPSta = true_MatlabRTW;
          } else if (OpMod_ResolverEnt_C) {
            SWC_APP_type_ARID_DEF.is_PowerUpProcedure =
              SWC_APP_type_IN_ResolverAdjust;
            VOPM_MotMod_enum = 8U;
          } else if (OpMod_bService_C) {
            SWC_APP_type_ARID_DEF.is_PowerUpProcedure =
              SWC_APP_type_IN_DiagService;
            VOPM_MotMod_enum = 9U;
          }
        }
        break;

       case SWC_APP_type_IN_ResolverAdjust:
        VOPM_MotMod_enum = 8U;
        if (!OpMod_ResolverEnt_C) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       case SWC_APP_type_IN_Speed:
        VOPM_MotMod_enum = 4U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum ==
            0) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Torque;
          VOPM_MotMod_enum = 3U;
          SWC_APP_type_ARID_DEF.OpMod_bMCUEna = true_MatlabRTW;
        } else if ((!SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg) ||
                   (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum ==
                    0) ||
                   (!SWC_APP_type_ARID_DEF.bus_creator.VINP_RrActvDmpDisabReq_flg))
        {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       case SWC_APP_type_IN_StandBy:
        VOPM_MotMod_enum = 1U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_HVBContactorSta_flg &&
            (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide
             > OpMod_uDCSide2AfterRun_C)) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;

       default:
        /* case IN_Torque: */
        VOPM_MotMod_enum = 3U;
        if (SWC_APP_type_ARID_DEF.bus_creator.VINP_FDCVCURrTMCtrlModeReq_enum ==
            1) {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Speed;
          VOPM_MotMod_enum = 4U;
          SWC_APP_type_ARID_DEF.OpMod_bMCUEna = true_MatlabRTW;
        } else if ((!SWC_APP_type_ARID_DEF.bus_creator.VINP_RrMCUEnaReq_flg) ||
                   (SWC_APP_type_ARID_DEF.bus_creator.VINP_ShiftGearPosn_enum ==
                    0) ||
                   (!SWC_APP_type_ARID_DEF.bus_creator.VINP_RrActvDmpDisabReq_flg))
        {
          SWC_APP_type_ARID_DEF.is_PowerUpProcedure = SWC_APP_type_IN_Ready;
          VOPM_MotMod_enum = 2U;
          SWC_APP_type_ARID_DEF.OpMod_bTMReady = true_MatlabRTW;
        }
        break;
      }
    }
  }

  /* End of Chart: '<S597>/MotorMode' */

  /* Switch: '<S597>/OpMod_stMotActswt' incorporates:
   *  Constant: '<S597>/OpMod_stMotActTrig_C'
   */
  if (KOPM_MotMod_enum_ovrdflg) {
    /* Switch: '<S597>/OpMod_stMotActswt' incorporates:
     *  Constant: '<S597>/OpMod_stMotActMor_C'
     */
    VOPM_MotMod_enum = KOPM_MotMod_enum_ovrdval;
  }

  /* End of Switch: '<S597>/OpMod_stMotActswt' */

  /* Abs: '<S598>/Abs' incorporates:
   *  Abs: '<S715>/Abs7'
   */
  rtb_TrqMax = fabsf
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot);

  /* Outputs for Atomic SubSystem: '<S598>/Hysterisis_NoRst1' */
  /* Logic: '<S731>/AND1' incorporates:
   *  Abs: '<S598>/Abs'
   *  Constant: '<S598>/Constant3'
   *  RelationalOperator: '<S601>/Relational Operator'
   */
  rtb_AND1_g2 = (rtb_TrqMax > OpMod_nRotASCEna_C);

  /* Outputs for Atomic SubSystem: '<S600>/Delay' */
  rtb_UnitDelay_ch = SWC_APP_type_Delay(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_j);

  /* End of Outputs for SubSystem: '<S600>/Delay' */

  /* Switch: '<S604>/SWT' incorporates:
   *  Abs: '<S598>/Abs'
   *  Constant: '<S598>/Constant2'
   *  Logic: '<S603>/OR1'
   *  RelationalOperator: '<S605>/Relational Operator'
   */
  if ((rtb_TrqMax < OpMod_nRotASCDi_C) || rtb_AND1_g2) {
    /* Switch: '<S604>/SWT' */
    SWC_APP_type_ARID_DEF.SWT_cf = rtb_AND1_g2;
  } else {
    /* Switch: '<S604>/SWT' */
    SWC_APP_type_ARID_DEF.SWT_cf = rtb_UnitDelay_ch;
  }

  /* End of Switch: '<S604>/SWT' */

  /* Update for Atomic SubSystem: '<S600>/Delay' */
  SWC_APP_type_Delay_Update(SWC_APP_type_ARID_DEF.SWT_cf,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_j);

  /* End of Update for SubSystem: '<S600>/Delay' */
  /* End of Outputs for SubSystem: '<S598>/Hysterisis_NoRst1' */

  /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
   *  Constant: '<S597>/Constant3'
   *  Constant: '<S598>/Constant9'
   *  Logic: '<S598>/Logical Operator4'
   *  RelationalOperator: '<S598>/Relational Operator7'
   *  Switch: '<S598>/OpMod_stMotActswt1'
   *  Switch: '<S598>/OpMod_stMotActswt2'
   */
  if (KOPM_IVTROpMode_enum_ovrdflg) {
    /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
     *  Constant: '<S597>/Constant4'
     */
    VOPM_IVTROpMode_enum = KOPM_IVTROpMode_enum_ovrdval;
  } else if (VOPM_MotMod_enum != 5) {
    /* Switch: '<S598>/OpMod_stMotActswt5' incorporates:
     *  Constant: '<S598>/Constant8'
     *  Logic: '<S598>/Logical Operator3'
     *  RelationalOperator: '<S598>/Relational Operator6'
     *  Switch: '<S598>/OpMod_stMotActswt1'
     */
    if (VOPM_MotMod_enum != 6) {
      /* Switch: '<S598>/OpMod_stMotActswt7' incorporates:
       *  Constant: '<S598>/Constant5'
       *  Constant: '<S598>/Constant6'
       *  Constant: '<S598>/Constant7'
       *  Logic: '<S598>/Logical Operator'
       *  Logic: '<S598>/Logical Operator1'
       *  RelationalOperator: '<S598>/Relational Operator'
       *  RelationalOperator: '<S598>/Relational Operator1'
       *  RelationalOperator: '<S598>/Relational Operator2'
       */
      if ((VOPM_MotMod_enum != 4) && (VOPM_MotMod_enum != 7) &&
          (VOPM_MotMod_enum != 3)) {
        /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
         *  Constant: '<S598>/Constant10'
         *  Switch: '<S598>/OpMod_stMotActswt4'
         *  Switch: '<S598>/OpMod_stMotActswt5'
         *  Switch: '<S598>/OpMod_stMotActswt7'
         */
        VOPM_IVTROpMode_enum = 0U;
      } else {
        /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
         *  Constant: '<S598>/Constant12'
         *  Switch: '<S598>/OpMod_stMotActswt5'
         *  Switch: '<S598>/OpMod_stMotActswt7'
         */
        VOPM_IVTROpMode_enum = 1U;
      }

      /* End of Switch: '<S598>/OpMod_stMotActswt7' */
    } else {
      /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
       *  Constant: '<S598>/Constant13'
       *  Switch: '<S598>/OpMod_stMotActswt5'
       */
      VOPM_IVTROpMode_enum = 5U;
    }

    /* End of Switch: '<S598>/OpMod_stMotActswt5' */
  } else if (SWC_APP_type_ARID_DEF.SWT_cf) {
    /* Switch: '<S598>/OpMod_stMotActswt2' incorporates:
     *  Constant: '<S598>/Constant14'
     *  Switch: '<S597>/OpMod_stIvtrTarswt'
     *  Switch: '<S598>/OpMod_stMotActswt1'
     */
    VOPM_IVTROpMode_enum = 2U;
  } else {
    /* Switch: '<S597>/OpMod_stIvtrTarswt' incorporates:
     *  Constant: '<S598>/Constant15'
     *  Switch: '<S598>/OpMod_stMotActswt1'
     *  Switch: '<S598>/OpMod_stMotActswt2'
     */
    VOPM_IVTROpMode_enum = 0U;
  }

  /* End of Switch: '<S597>/OpMod_stIvtrTarswt' */

  /* Logic: '<S597>/Logical Operator' incorporates:
   *  Constant: '<S597>/Constant2'
   *  Logic: '<S597>/Logical Operator1'
   *  RelationalOperator: '<S597>/Relational Operator1'
   */
  VOPM_CurLoopEna_flg = ((VOPM_IVTROpMode_enum == 1) && (!DiagM_bOver2Stop));

  /* Switch: '<S597>/OpMod_stMotActswt1' incorporates:
   *  Constant: '<S597>/OpMod_stMotActTrig_C1'
   */
  if (KOPM_PsvDischrgEna_flg_ovrdflg) {
    /* Switch: '<S597>/OpMod_stMotActswt1' incorporates:
     *  Constant: '<S597>/OpMod_stMotActTrig_C2'
     */
    VOPM_PsvDischrgEna_flg = KOPM_PsvDischrgEna_flg_ovrdval;
  } else {
    /* Switch: '<S597>/OpMod_stMotActswt1' */
    VOPM_PsvDischrgEna_flg = SWC_APP_type_ARID_DEF.OpMod_bPasDchaEna;
  }

  /* End of Switch: '<S597>/OpMod_stMotActswt1' */
  /* End of Outputs for SubSystem: '<S10>/OpMod' */

  /* PreLookup: '<S27>/Prelookup' */
  rtb_Prelookup_o1 = plook_u32ff_binx(SWC_APP_type_ConstB.Abs1_p,
    &ACRM_MTPAIdMot_Y_Nm[0], 50U, &rtb_Prelookup_o2);

  /* PreLookup: '<S27>/Prelookup1' incorporates:
   *  Abs: '<S27>/Abs'
   */
  rtb_Prelookup1_o1 = plook_u32ff_binx(fabsf
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide),
    &ACRM_MTPAIdMot_X_rpm[0], 19U, &rtb_Prelookup1_o2);

  /* Logic: '<S741>/AND1' incorporates:
   *  RelationalOperator: '<S27>/Relational Operator1'
   */
  rtb_AND1_h =
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >=
     0.0F);

  /* Switch: '<S27>/Switch1' incorporates:
   *  Constant: '<S27>/Constant3'
   *  Logic: '<S27>/Logical Operator'
   *  Logic: '<S27>/Logical Operator3'
   *  Logic: '<S27>/Logical Operator6'
   *  Logic: '<S27>/Logical Operator8'
   *  Switch: '<S27>/Switch5'
   */
  if ((SWC_APP_type_ConstB.RelationalOperator && rtb_AND1_h) ||
      (SWC_APP_type_ConstB.LogicalOperator5 && (!rtb_AND1_h))) {
    /* Switch: '<S27>/Switch4' incorporates:
     *  Constant: '<S27>/Constant'
     */
    if (KCRM_MTPAMotSwitch_flg) {
      /* Switch: '<S18>/Switch2' incorporates:
       *  Lookup_n-D: '<S27>/696MTPAIdMot'
       *  Switch: '<S27>/Switch4'
       */
      rtb_Prelookup1_o2_n = look2_iflf_binlxpw(0.0F,
        SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
        &ACRM_MTPAIdMot_Y_Nm[0], &ACRM_MTPAIdMot_X_rpm[0], &MCRM_MTPAIdMot_Z_A[0],
        SWC_APP_type_ConstP.pooled25, 51U);
    } else {
      /* Interpolation_n-D: '<S27>/696Id_Mot_Map' */
      frac[0] = rtb_Prelookup_o2;
      frac[1] = rtb_Prelookup1_o2;
      bpIndex[0] = rtb_Prelookup_o1;
      bpIndex[1] = rtb_Prelookup1_o1;

      /* Switch: '<S18>/Switch2' incorporates:
       *  Interpolation_n-D: '<S27>/696Id_Mot_Map'
       *  Switch: '<S27>/Switch4'
       */
      rtb_Prelookup1_o2_n = intrp2d_fu32fl_pw(bpIndex, frac,
        &MCRM_MTPAIdMot_Z_A[0], 51U);
    }

    /* End of Switch: '<S27>/Switch4' */
  } else if (KCRM_MTPAGenSwitch_flg) {
    /* Switch: '<S18>/Switch2' incorporates:
     *  Lookup_n-D: '<S27>/696MTPAIdGen'
     *  Switch: '<S27>/Switch5'
     */
    rtb_Prelookup1_o2_n = look2_iflf_binlxpw(0.0F,
      SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
      &ACRM_MTPAIdGen_Y_Nm[0], &ACRM_MTPAIdGen_X_rpm[0], &MCRM_MTPAIdGen_Z_A[0],
      SWC_APP_type_ConstP.pooled25, 51U);
  } else {
    /* Interpolation_n-D: '<S27>/696Id_Gen_Map' incorporates:
     *  Switch: '<S27>/Switch5'
     */
    frac[0] = rtb_Prelookup_o2;
    frac[1] = rtb_Prelookup1_o2;
    bpIndex[0] = rtb_Prelookup_o1;
    bpIndex[1] = rtb_Prelookup1_o1;

    /* Switch: '<S18>/Switch2' incorporates:
     *  Interpolation_n-D: '<S27>/696Id_Gen_Map'
     *  Switch: '<S27>/Switch5'
     */
    rtb_Prelookup1_o2_n = intrp2d_fu32fl_pw(bpIndex, frac, &MCRM_MTPAIdGen_Z_A[0],
      51U);
  }

  /* End of Switch: '<S27>/Switch1' */

  /* Saturate: '<S27>/Saturation' */
  if (rtb_Prelookup1_o2_n > 0.0F) {
    /* Saturate: '<S27>/Saturation' */
    VCRM_IdCmdinit_A = 0.0F;
  } else if (rtb_Prelookup1_o2_n < -500.0F) {
    /* Saturate: '<S27>/Saturation' */
    VCRM_IdCmdinit_A = -500.0F;
  } else {
    /* Saturate: '<S27>/Saturation' */
    VCRM_IdCmdinit_A = rtb_Prelookup1_o2_n;
  }

  /* End of Saturate: '<S27>/Saturation' */

  /* Gain: '<S31>/Gain' */
  rtb_Prelookup_o2 = KCRM_VolModINV_perc *
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VCCM_BattVolCirRadius_V;

  /* PreLookup: '<S28>/Prelookup' */
  rtb_Prelookup_o1 = plook_u32ff_binx(SWC_APP_type_ConstB.Abs1_f,
    &ACRM_MTPAIdMotMin_Y_Nm[0], 50U, &rtb_Prelookup1_o2);

  /* PreLookup: '<S28>/Prelookup1' incorporates:
   *  Abs: '<S28>/Abs'
   */
  rtb_Prelookup1_o1 = plook_u32ff_binx(fabsf
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide),
    &ACRM_MTPAIdMotMin_X_rpm[0], 19U, &rtb_Prelookup1_o2_n);

  /* Logic: '<S741>/AND1' incorporates:
   *  RelationalOperator: '<S28>/Relational Operator1'
   */
  rtb_AND1_h =
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >=
     0.0F);

  /* Switch: '<S28>/Switch1' incorporates:
   *  Constant: '<S28>/Constant3'
   *  Logic: '<S28>/Logical Operator'
   *  Logic: '<S28>/Logical Operator3'
   *  Logic: '<S28>/Logical Operator6'
   *  Logic: '<S28>/Logical Operator8'
   *  Switch: '<S28>/Switch5'
   */
  if ((SWC_APP_type_ConstB.RelationalOperator_e && rtb_AND1_h) ||
      (SWC_APP_type_ConstB.LogicalOperator5_g && (!rtb_AND1_h))) {
    /* Switch: '<S28>/Switch4' incorporates:
     *  Constant: '<S28>/Constant'
     */
    if (KCRM_MTPAMotSwitch_flg) {
      /* Switch: '<S18>/Switch2' incorporates:
       *  Lookup_n-D: '<S28>/530MTPAIdMot'
       *  Switch: '<S28>/Switch4'
       */
      rtb_Prelookup1_o2_n = look2_iflf_binlxpw(0.0F,
        SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
        &ACRM_MTPAIdMotMin_Y_Nm[0], &ACRM_MTPAIdMotMin_X_rpm[0],
        &MCRM_MTPAIdMotMin_Z_A[0], SWC_APP_type_ConstP.pooled25, 51U);
    } else {
      /* Interpolation_n-D: '<S28>/Id_Mot_Map' */
      frac_0[0] = rtb_Prelookup1_o2;
      frac_0[1] = rtb_Prelookup1_o2_n;
      bpIndex_0[0] = rtb_Prelookup_o1;
      bpIndex_0[1] = rtb_Prelookup1_o1;

      /* Switch: '<S18>/Switch2' incorporates:
       *  Interpolation_n-D: '<S28>/Id_Mot_Map'
       *  Switch: '<S28>/Switch4'
       */
      rtb_Prelookup1_o2_n = intrp2d_fu32fl_pw(bpIndex_0, frac_0,
        &MCRM_MTPAIdMotMin_Z_A[0], 51U);
    }

    /* End of Switch: '<S28>/Switch4' */
  } else if (KCRM_MTPAGenSwitch_flg) {
    /* Switch: '<S18>/Switch2' incorporates:
     *  Lookup_n-D: '<S28>/530MTPAIdGen'
     *  Switch: '<S28>/Switch5'
     */
    rtb_Prelookup1_o2_n = look2_iflf_binlxpw(0.0F,
      SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
      &ACRM_MTPAIdGenMin_Y_Nm[0], &ACRM_MTPAIdGenMin_X_rpm[0],
      &MCRM_MTPAIdGenMin_Z_A[0], SWC_APP_type_ConstP.pooled25, 51U);
  } else {
    /* Interpolation_n-D: '<S28>/Id_Gen_Map' incorporates:
     *  Switch: '<S28>/Switch5'
     */
    frac_0[0] = rtb_Prelookup1_o2;
    frac_0[1] = rtb_Prelookup1_o2_n;
    bpIndex_0[0] = rtb_Prelookup_o1;
    bpIndex_0[1] = rtb_Prelookup1_o1;

    /* Switch: '<S18>/Switch2' incorporates:
     *  Interpolation_n-D: '<S28>/Id_Gen_Map'
     *  Switch: '<S28>/Switch5'
     */
    rtb_Prelookup1_o2_n = intrp2d_fu32fl_pw(bpIndex_0, frac_0,
      &MCRM_MTPAIdGenMin_Z_A[0], 51U);
  }

  /* End of Switch: '<S28>/Switch1' */

  /* Saturate: '<S28>/Saturation' */
  if (rtb_Prelookup1_o2_n > 0.0F) {
    /* Saturate: '<S28>/Saturation' */
    rtb_Prelookup1_o2_n = 0.0F;
  } else if (rtb_Prelookup1_o2_n < -500.0F) {
    /* Saturate: '<S28>/Saturation' */
    rtb_Prelookup1_o2_n = -500.0F;
  }

  /* End of Saturate: '<S28>/Saturation' */

  /* Switch: '<S31>/Switch1' incorporates:
   *  Constant: '<S31>/Constant'
   *  RelationalOperator: '<S31>/Relational Operator1'
   */
  if (rtb_Prelookup_o2 < KCRM_IdqMapVolHi_V) {
    /* Switch: '<S31>/Switch2' incorporates:
     *  Constant: '<S31>/Constant1'
     *  RelationalOperator: '<S31>/Relational Operator'
     */
    if (rtb_Prelookup_o2 <= KCRM_IdqMapVolLo_V) {
      /* Switch: '<S31>/Switch1' incorporates:
       *  Switch: '<S31>/Switch2'
       */
      VCRM_IdCmdinit_A = rtb_Prelookup1_o2_n;
    } else {
      /* Switch: '<S31>/Switch1' incorporates:
       *  Product: '<S31>/Divide'
       *  Product: '<S31>/Divide1'
       *  Saturate: '<S31>/Saturation'
       *  Sum: '<S31>/Subtract'
       *  Sum: '<S31>/Subtract1'
       *  Sum: '<S31>/Subtract2'
       *  Sum: '<S31>/Subtract3'
       *  Switch: '<S31>/Switch2'
       */
      VCRM_IdCmdinit_A = 1.0F / (KCRM_IdqMapVolHi_V - KCRM_IdqMapVolLo_V) *
        fmaxf(rtb_Prelookup_o2 - KCRM_IdqMapVolLo_V, 0.5F) * (VCRM_IdCmdinit_A -
        rtb_Prelookup1_o2_n) + rtb_Prelookup1_o2_n;
    }

    /* End of Switch: '<S31>/Switch2' */
  }

  /* End of Switch: '<S31>/Switch1' */

  /* Switch: '<S18>/Switch2' incorporates:
   *  Constant: '<S33>/Constant11'
   *  Sum: '<S33>/Add'
   *  UnitDelay: '<S33>/Unit Delay3'
   */
  rtb_Prelookup1_o2_n = SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE +
    KCRM_grdIsThetaRampUp_C;

  /* Switch: '<S33>/Switch2' incorporates:
   *  Constant: '<S33>/Constant9'
   */
  if (KCRM_AtSweep_deg_ovrdflg) {
    /* Switch: '<S33>/Switch2' */
    rtb_Prelookup_o2 = 0.0F;
  } else {
    /* Switch: '<S33>/Switch2' incorporates:
     *  Constant: '<S33>/Constant4'
     */
    rtb_Prelookup_o2 = KCRM_AtSweep_deg_ovrdval;
  }

  /* End of Switch: '<S33>/Switch2' */

  /* Switch: '<S49>/Switch2' incorporates:
   *  RelationalOperator: '<S49>/LowerRelop1'
   *  UnitDelay: '<S33>/Unit Delay4'
   */
  if (rtb_Prelookup_o2 > rtb_Prelookup1_o2_n) {
    SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE = rtb_Prelookup1_o2_n;
  } else {
    /* Sum: '<S33>/Add1' incorporates:
     *  Constant: '<S33>/Constant10'
     *  UnitDelay: '<S33>/Unit Delay4'
     */
    SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE += KCRM_grdIsThetaRampDown_C;

    /* Switch: '<S49>/Switch' incorporates:
     *  RelationalOperator: '<S49>/UpperRelop'
     *  UnitDelay: '<S33>/Unit Delay4'
     */
    if (rtb_Prelookup_o2 >= SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE) {
      SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE = rtb_Prelookup_o2;
    }

    /* End of Switch: '<S49>/Switch' */
  }

  /* End of Switch: '<S49>/Switch2' */

  /* Gain: '<S33>/Gain' incorporates:
   *  UnitDelay: '<S33>/Unit Delay4'
   */
  rtb_Prelookup_o2 = 0.0174532924F * SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE;

  /* Switch: '<S33>/Switch' incorporates:
   *  Constant: '<S33>/Constant1'
   *  Switch: '<S33>/Switch1'
   */
  if (KCRM_UsingIsSp_A_ovrdflg) {
    /* Switch: '<S33>/Switch' incorporates:
     *  Constant: '<S33>/Constant3'
     *  Gain: '<S33>/Gain1'
     *  Product: '<S33>/Product'
     *  Trigonometry: '<S33>/Trigonometric Function'
     */
    VCRM_IdSp_A = KCRM_IsSp_A * -sinf(rtb_Prelookup_o2);

    /* Switch: '<S33>/Switch1' incorporates:
     *  Constant: '<S33>/Constant3'
     *  Product: '<S33>/Product1'
     *  Trigonometry: '<S33>/Trigonometric Function1'
     */
    VCRM_IqSp_A = KCRM_IsSp_A * cosf(rtb_Prelookup_o2);
  } else {
    /* Switch: '<S33>/Switch' incorporates:
     *  Constant: '<S33>/Constant6'
     */
    VCRM_IdSp_A = KCRM_IdSp_A_ovrdval;

    /* Switch: '<S33>/Switch1' incorporates:
     *  Constant: '<S33>/Constant7'
     */
    VCRM_IqSp_A = KCRM_IqSp_A_ovrdval;
  }

  /* End of Switch: '<S33>/Switch' */

  /* RelationalOperator: '<S18>/Relational Operator' incorporates:
   *  Constant: '<S18>/Constant18'
   */
  DiagM_bOver2Stop = (VOPM_MotMod_enum == 7);

  /* Chart: '<S18>/IArb' incorporates:
   *  Constant: '<S18>/Constant2'
   *  Constant: '<S18>/Constant5'
   */
  /* $TL$ stepfunctionclass=GlobalFunctionClasses/INLINE_FCN; $TL$ */
  if (DiagM_bOver2Stop) {
    VCRM_IdCmdinit_A = KCRM_IdSpForActvDisc_null;
    VCRM_IqCmdinit_A = 0.0F;
  } else if (KCRM_CurDebugSwt_null) {
    VCRM_IdCmdinit_A = VCRM_IdSp_A;
    VCRM_IqCmdinit_A = VCRM_IqSp_A;
  } else if (VOPM_CurLoopEna_flg) {
    VCRM_IqCmdinit_A = 0.0F;
  } else {
    VCRM_IdCmdinit_A = 0.0F;
    VCRM_IqCmdinit_A = 0.0F;
  }

  /* End of Chart: '<S18>/IArb' */

  /* Logic: '<S741>/AND1' incorporates:
   *  Logic: '<S18>/Logical Operator'
   *  Logic: '<S18>/Logical Operator1'
   */
  rtb_AND1_h = (VOPM_CurLoopEna_flg && (!DiagM_bOver2Stop));

  /* Switch: '<S23>/Switch3' */
  if (rtb_AND1_h) {
    /* Product: '<S45>/Product' incorporates:
     *  Constant: '<S29>/Constant10'
     *  Constant: '<S29>/Constant19'
     *  Constant: '<S29>/Constant20'
     *  Gain: '<S23>/Gain1'
     *  MinMax: '<S29>/MinMax1'
     *  Product: '<S29>/Divide1'
     *  Sum: '<S29>/Add1'
     *  Sum: '<S29>/Add11'
     */
    rtb_Prelookup_o2 =
      ((SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VCCM_BattVolCirRadius_V
        - SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VCCM_VcmdBfLim_V)
       - fmaxf(fmaxf
               (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_VCCM_BattVolCirRadius_V
                * KCRM_VolOfstVsBattVol4FW_V, KCRM_MinVolOfst4FW_V), 0.0F)) *
      KCRM_FWCEnable_null;
  } else {
    /* Product: '<S45>/Product' incorporates:
     *  Constant: '<S23>/Constant9'
     */
    rtb_Prelookup_o2 = 0.0F;
  }

  /* End of Switch: '<S23>/Switch3' */

  /* Logic: '<S23>/Logical Operator' */
  DiagM_bOver2Stop = !rtb_AND1_h;

  /* DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
  if (DiagM_bOver2Stop || (SWC_APP_type_ARID_DEF.DiscreteTimeIntegrator_PrevRese
       != 0)) {
    SWC_APP_type_ARID_DEF.DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  /* Sum: '<S45>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
   *  Product: '<S45>/Product1'
   */
  rtb_Prelookup1_o2 = KCRM_FWCKp_null * rtb_Prelookup_o2 +
    SWC_APP_type_ARID_DEF.DiscreteTimeIntegrator_DSTATE;

  /* Switch: '<S47>/Switch2' incorporates:
   *  Constant: '<S23>/Constant2'
   *  Constant: '<S45>/Constant'
   *  RelationalOperator: '<S47>/LowerRelop1'
   *  RelationalOperator: '<S47>/UpperRelop'
   *  Switch: '<S47>/Switch'
   */
  if (rtb_Prelookup1_o2 > 0.0F) {
    /* Switch: '<S47>/Switch2' */
    VCRM_PIOut_value = 0.0F;
  } else if (rtb_Prelookup1_o2 < KCRM_PILowerLimit_null) {
    /* Switch: '<S47>/Switch' incorporates:
     *  Constant: '<S23>/Constant2'
     *  Switch: '<S47>/Switch2'
     */
    VCRM_PIOut_value = KCRM_PILowerLimit_null;
  } else {
    /* Switch: '<S47>/Switch2' incorporates:
     *  Switch: '<S47>/Switch'
     */
    VCRM_PIOut_value = rtb_Prelookup1_o2;
  }

  /* End of Switch: '<S47>/Switch2' */

  /* Switch: '<S23>/Switch1' incorporates:
   *  Constant: '<S23>/Constant5'
   *  Constant: '<S23>/Constant6'
   *  RelationalOperator: '<S23>/Relational Operator'
   *  RelationalOperator: '<S23>/Relational Operator1'
   *  Switch: '<S23>/Switch2'
   */
  if (KCRM_CurTqCmdLo_Nm >= 0.0F) {
    /* Switch: '<S23>/Switch1' incorporates:
     *  Constant: '<S23>/Constant3'
     */
    frac[0] = VCRM_PIOut_value;
    frac[1] = 0.0F;
  } else if (KCRM_CurTqCmdHi_Nm <= 0.0F) {
    /* Switch: '<S23>/Switch1' incorporates:
     *  Constant: '<S23>/Constant4'
     *  Switch: '<S23>/Switch2'
     */
    frac[0] = 0.0F;
    frac[1] = VCRM_PIOut_value;
  } else {
    /* Gain: '<S23>/Gain2' incorporates:
     *  Constant: '<S23>/Constant6'
     *  Product: '<S23>/Divide'
     *  Sum: '<S23>/Add2'
     *  Sum: '<S23>/Add3'
     *  Switch: '<S23>/Switch2'
     */
    rtb_Prelookup1_o2_n = (0.0F - KCRM_CurTqCmdLo_Nm) / (KCRM_CurTqCmdHi_Nm -
      KCRM_CurTqCmdLo_Nm) * 1.57079637F;

    /* Switch: '<S23>/Switch1' incorporates:
     *  Product: '<S23>/Product'
     *  Product: '<S23>/Product1'
     *  Switch: '<S23>/Switch2'
     *  Trigonometry: '<S23>/Sin'
     *  Trigonometry: '<S23>/Sin1'
     */
    frac[0] = cosf(rtb_Prelookup1_o2_n) * VCRM_PIOut_value;
    frac[1] = sinf(rtb_Prelookup1_o2_n) * VCRM_PIOut_value;
  }

  /* End of Switch: '<S23>/Switch1' */

  /* Sum: '<S23>/Add' */
  VCRM_IdCmdFWC_A = VCRM_IdCmdinit_A + frac[0];

  /* Switch: '<S32>/Switch2' incorporates:
   *  Constant: '<S18>/Constant'
   *  Constant: '<S26>/Constant'
   *  RelationalOperator: '<S26>/Relational Operator'
   *  RelationalOperator: '<S32>/LowerRelop1'
   *  Switch: '<S26>/Switch'
   */
  if (VCRM_IdCmdFWC_A > 0.0F) {
    /* Switch: '<S18>/Switch2' */
    rtb_Prelookup1_o2_n = 0.0F;
  } else {
    if (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >
        KCRM_MTPVSpdThd_rpm) {
      /* Switch: '<S26>/Switch' incorporates:
       *  Lookup_n-D: '<S26>/1-D Lookup Table'
       */
      rtb_Prelookup1_o2_n = look1_iflf_binlcapw
        (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
         &ACRM_MTPVIdLimt_X_rpm[0], &MCRM_MTPVIdLimt_Y_A[0], 17U);
    } else {
      /* Switch: '<S26>/Switch' incorporates:
       *  Constant: '<S26>/Constant3'
       */
      rtb_Prelookup1_o2_n = KCRM_IdCmdMaxLimt_A;
    }

    /* Switch: '<S32>/Switch' incorporates:
     *  RelationalOperator: '<S32>/UpperRelop'
     */
    if (VCRM_IdCmdFWC_A >= rtb_Prelookup1_o2_n) {
      /* Switch: '<S18>/Switch2' */
      rtb_Prelookup1_o2_n = VCRM_IdCmdFWC_A;
    }

    /* End of Switch: '<S32>/Switch' */
  }

  /* End of Switch: '<S32>/Switch2' */

  /* Sum: '<S25>/Add' incorporates:
   *  Constant: '<S25>/Constant'
   *  Product: '<S25>/Product'
   *  Sum: '<S25>/Subtract'
   */
  VCRM_IdCmd_A += (rtb_Prelookup1_o2_n - VCRM_IdCmd_A) * KCRM_IdCmdFilCoeff_null;

  /* Switch: '<S23>/Switch' incorporates:
   *  Constant: '<S23>/Constant8'
   *  Logic: '<S23>/Logical Operator1'
   *  Logic: '<S23>/Logical Operator2'
   *  RelationalOperator: '<S23>/Relational Operator2'
   *  RelationalOperator: '<S23>/Relational Operator5'
   *  RelationalOperator: '<S23>/Relational Operator6'
   */
  if ((VCRM_IqCmdinit_A < 0.0F) || ((VCRM_IqCmdinit_A == 0.0F) &&
       (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide <
        0.0F))) {
    /* Switch: '<S23>/Switch' incorporates:
     *  Abs: '<S23>/Abs'
     *  Constant: '<S23>/Constant7'
     *  Gain: '<S23>/Gain3'
     *  MinMax: '<S23>/Max'
     *  Sum: '<S23>/Add1'
     */
    VCRM_IqCmdFWC_A = -fmaxf(frac[1] + fabsf(VCRM_IqCmdinit_A), 0.0F);
  } else {
    /* Switch: '<S23>/Switch' incorporates:
     *  Abs: '<S23>/Abs'
     *  Constant: '<S23>/Constant7'
     *  MinMax: '<S23>/Max'
     *  Sum: '<S23>/Add1'
     */
    VCRM_IqCmdFWC_A = fmaxf(frac[1] + fabsf(VCRM_IqCmdinit_A), 0.0F);
  }

  /* End of Switch: '<S23>/Switch' */

  /* Logic: '<S741>/AND1' incorporates:
   *  Constant: '<S715>/Constant35'
   *  RelationalOperator: '<S715>/Relational Operator1'
   */
  rtb_AND1_h = (KDGL_tqMotStallProtEna_Nm <= 0.0F);

  /* Logic: '<S715>/Logical Operator5' incorporates:
   *  Abs: '<S715>/Abs'
   *  Abs: '<S715>/Abs1'
   *  Constant: '<S715>/Constant2'
   *  Constant: '<S715>/Constant31'
   *  Logic: '<S715>/Logical Operator'
   *  MinMax: '<S715>/Max'
   *  RelationalOperator: '<S715>/Relational Operator'
   *  RelationalOperator: '<S715>/Relational Operator2'
   *  UnitDelay: '<S2>/Unit Delay1'
   *  UnitDelay: '<S2>/Unit Delay2'
   */
  rtb_LogicalOperator5 = ((rtb_TrqMax <= KDGL_nRotStallProtEna_rpm) &&
    (rtb_AND1_h || (fmaxf(fabsf(SWC_APP_type_ARID_DEF.UnitDelay2_DSTATE), fabsf
    (VCRM_IqCmd_A)) >= KDGL_iMotStallProtEna_A)));

  /* Outputs for Atomic SubSystem: '<S715>/TurnOnDelay_Dyn2' */
  /* Outputs for Atomic SubSystem: '<S903>/Rising' */
  rtb_AND1_h = SWC_APP_type_Rising(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising);

  /* End of Outputs for SubSystem: '<S903>/Rising' */

  /* Outputs for Atomic SubSystem: '<S903>/Delay' */
  rtb_UnitDelay_cg = SWC_APP_type_Delay_m(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay);

  /* End of Outputs for SubSystem: '<S903>/Delay' */

  /* Switch: '<S919>/SWT' */
  if (rtb_AND1_h) {
    /* Switch: '<S919>/SWT' incorporates:
     *  Constant: '<S903>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT = 0.0F;
  } else {
    /* Switch: '<S919>/SWT' incorporates:
     *  Constant: '<S715>/Constant38'
     *  Sum: '<S917>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT = rtb_UnitDelay_cg + 1.0F;
  }

  /* End of Switch: '<S919>/SWT' */

  /* Switch: '<S918>/SWT' */
  if (rtb_LogicalOperator5) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S715>/Constant1'
     *  Sum: '<S916>/Sub1'
     */
    rtb_SWT = KDGL_tiDlyOnStallProt_C - SWC_APP_type_ConstB.Gain1_e;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S903>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S918>/SWT' */

  /* Outputs for Atomic SubSystem: '<S903>/Rising1' */
  /* Logic: '<S908>/AND1' incorporates:
   *  RelationalOperator: '<S909>/Relational Operator'
   */
  rtb_AND1_h = SWC_APP_type_Rising((rtb_LogicalOperator5 &&
    (SWC_APP_type_ARID_DEF.SWT >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1);

  /* End of Outputs for SubSystem: '<S903>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S903>/Falling' */
  rtb_AND1_pg = SWC_APP_type_Falling(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling);

  /* End of Outputs for SubSystem: '<S903>/Falling' */

  /* Outputs for Atomic SubSystem: '<S903>/ER_FF' */
  SWC_APP_type_ER_FF(rtb_AND1_h, rtb_AND1_pg, &SWC_APP_type_ARID_DEF.SWT_c,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF);

  /* End of Outputs for SubSystem: '<S903>/ER_FF' */

  /* Update for Atomic SubSystem: '<S903>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay);

  /* End of Update for SubSystem: '<S903>/Delay' */
  /* End of Outputs for SubSystem: '<S715>/TurnOnDelay_Dyn2' */

  /* Outputs for Atomic SubSystem: '<S715>/ER_FF' */
  /* Outputs for Atomic SubSystem: '<S902>/Delay' */
  rtb_UnitDelay_a = SWC_APP_type_Delay(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_m);

  /* End of Outputs for SubSystem: '<S902>/Delay' */

  /* Switch: '<S907>/SWT' */
  if (SWC_APP_type_ARID_DEF.SWT_c) {
    /* Switch: '<S907>/SWT' incorporates:
     *  Constant: '<S902>/true'
     */
    VDGL_DiagStall_flg = true_MatlabRTW;
  } else {
    /* Switch: '<S907>/SWT' incorporates:
     *  Constant: '<S715>/Constant7'
     *  Switch: '<S906>/SWT'
     */
    VDGL_DiagStall_flg = ((!KDGL_bRstStallPort_flg) && rtb_UnitDelay_a);
  }

  /* End of Switch: '<S907>/SWT' */

  /* Update for Atomic SubSystem: '<S902>/Delay' */
  SWC_APP_type_Delay_Update(VDGL_DiagStall_flg,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_m);

  /* End of Update for SubSystem: '<S902>/Delay' */
  /* End of Outputs for SubSystem: '<S715>/ER_FF' */

  /* Logic: '<S741>/AND1' incorporates:
   *  RelationalOperator: '<S714>/Relational Operator1'
   *  UnitDelay: '<S2>/Unit Delay4'
   */
  rtb_AND1_h = (SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE_h <= 0.0F);

  /* Logic: '<S714>/Logical Operator' incorporates:
   *  RelationalOperator: '<S714>/Relational Operator2'
   *  UnitDelay: '<S2>/Unit Delay3'
   */
  rtb_LogicalOperator5 = (rtb_AND1_h ||
    (SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_d >= 0.0F));

  /* Outputs for Atomic SubSystem: '<S714>/TurnOnDelay_Dyn2' */
  /* Outputs for Atomic SubSystem: '<S850>/Rising' */
  rtb_AND1_h = SWC_APP_type_Rising(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising_k);

  /* End of Outputs for SubSystem: '<S850>/Rising' */

  /* Outputs for Atomic SubSystem: '<S850>/Delay' */
  rtb_UnitDelay_bs = SWC_APP_type_Delay_m
    (&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_p);

  /* End of Outputs for SubSystem: '<S850>/Delay' */

  /* Switch: '<S888>/SWT' */
  if (rtb_AND1_h) {
    /* Switch: '<S888>/SWT' incorporates:
     *  Constant: '<S850>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_m = 0.0F;
  } else {
    /* Switch: '<S888>/SWT' incorporates:
     *  Constant: '<S714>/Constant38'
     *  Sum: '<S886>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_m = rtb_UnitDelay_bs + 1.0F;
  }

  /* End of Switch: '<S888>/SWT' */

  /* Switch: '<S887>/SWT' */
  if (rtb_LogicalOperator5) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S714>/Constant1'
     *  Sum: '<S885>/Sub1'
     */
    rtb_SWT = KDGL_tiDlyOnOverTqProt_C - SWC_APP_type_ConstB.Gain1_a;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S850>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S887>/SWT' */

  /* Outputs for Atomic SubSystem: '<S850>/Rising1' */
  /* Logic: '<S877>/AND1' incorporates:
   *  RelationalOperator: '<S878>/Relational Operator'
   */
  rtb_AND1_h = SWC_APP_type_Rising((rtb_LogicalOperator5 &&
    (SWC_APP_type_ARID_DEF.SWT_m >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_c);

  /* End of Outputs for SubSystem: '<S850>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S850>/Falling' */
  rtb_AND1_c = SWC_APP_type_Falling(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_c);

  /* End of Outputs for SubSystem: '<S850>/Falling' */

  /* Outputs for Atomic SubSystem: '<S850>/ER_FF' */
  SWC_APP_type_ER_FF(rtb_AND1_h, rtb_AND1_c, &SWC_APP_type_ARID_DEF.SWT_a,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_b);

  /* End of Outputs for SubSystem: '<S850>/ER_FF' */

  /* Update for Atomic SubSystem: '<S850>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_m,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_p);

  /* End of Update for SubSystem: '<S850>/Delay' */
  /* End of Outputs for SubSystem: '<S714>/TurnOnDelay_Dyn2' */

  /* Outputs for Atomic SubSystem: '<S714>/TurnOffDelay_Dyn1' */
  /* Outputs for Atomic SubSystem: '<S849>/Falling1' */
  rtb_AND1_j = SWC_APP_type_Falling(SWC_APP_type_ARID_DEF.SWT_a,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling1);

  /* End of Outputs for SubSystem: '<S849>/Falling1' */

  /* Outputs for Atomic SubSystem: '<S849>/Delay1' */
  rtb_UnitDelay_jc = SWC_APP_type_Delay_m(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay1);

  /* End of Outputs for SubSystem: '<S849>/Delay1' */

  /* Switch: '<S861>/SWT' */
  if (rtb_AND1_j) {
    /* Switch: '<S861>/SWT' incorporates:
     *  Constant: '<S849>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_mq = 0.0F;
  } else {
    /* Switch: '<S861>/SWT' incorporates:
     *  Constant: '<S714>/Constant18'
     *  Sum: '<S860>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_mq = rtb_UnitDelay_jc + 1.0F;
  }

  /* End of Switch: '<S861>/SWT' */

  /* Switch: '<S862>/SWT' incorporates:
   *  Logic: '<S855>/NOT1'
   */
  if (!SWC_APP_type_ARID_DEF.SWT_a) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S714>/Constant20'
     *  Sum: '<S859>/Sub1'
     */
    rtb_SWT = KDGL_tiDlyOffOverTqProt_C - SWC_APP_type_ConstB.Gain1_d;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S849>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S862>/SWT' */

  /* Outputs for Atomic SubSystem: '<S849>/Falling' */
  /* Logic: '<S856>/OR1' incorporates:
   *  RelationalOperator: '<S863>/Relational Operator'
   */
  rtb_AND1_h = SWC_APP_type_Falling((SWC_APP_type_ARID_DEF.SWT_a ||
    (SWC_APP_type_ARID_DEF.SWT_mq < rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_f);

  /* End of Outputs for SubSystem: '<S849>/Falling' */

  /* Outputs for Atomic SubSystem: '<S849>/Rising1' */
  rtb_AND1_j = SWC_APP_type_Rising(SWC_APP_type_ARID_DEF.SWT_a,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_cv);

  /* End of Outputs for SubSystem: '<S849>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S849>/RE_FF' */
  SWC_APP_type_RE_FF(rtb_AND1_h, rtb_AND1_j, &SWC_APP_type_ARID_DEF.SWT_l,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_RE_FF);

  /* End of Outputs for SubSystem: '<S849>/RE_FF' */

  /* Update for Atomic SubSystem: '<S849>/Delay1' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_mq,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay1);

  /* End of Update for SubSystem: '<S849>/Delay1' */
  /* End of Outputs for SubSystem: '<S714>/TurnOffDelay_Dyn1' */

  /* Switch: '<S714>/DiagM_bOverTorqueswt' incorporates:
   *  Constant: '<S714>/DiagM_bOverTorqueTrig_C'
   */
  if (KDGL_OverTorque_flg_ovrdflg) {
    /* Switch: '<S714>/DiagM_bOverTorqueswt' incorporates:
     *  Constant: '<S714>/DiagM_bOverTorqueMor_C'
     */
    VDGL_DiagOverTrq_flg = KDGL_OverTorque_flg_ovrdval;
  } else {
    /* Switch: '<S714>/DiagM_bOverTorqueswt' */
    VDGL_DiagOverTrq_flg = SWC_APP_type_ARID_DEF.SWT_l;
  }

  /* End of Switch: '<S714>/DiagM_bOverTorqueswt' */

  /* Outputs for Atomic SubSystem: '<S712>/Coef_Decrease_Increase' */
  /* Logic: '<S712>/Logical Operator' incorporates:
   *  Constant: '<S712>/T3'
   *  Constant: '<S712>/T4'
   */
  rtb_OutputCoef = Coef_Decrease_Increase((VDGL_OverSpdErr_flg ||
    VDGL_DiagStall_flg || VDGL_DiagOverTrq_flg), KDGL_SpdOverCoefAddStep_C,
    KDGL_SpdOverCoefSubStep_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Coef_Decrease_Increas);

  /* End of Outputs for SubSystem: '<S712>/Coef_Decrease_Increase' */

  /* SignalConversion generated from: '<S712>/Coef_Decrease_Increase' */
  VDGL_OverSpdDerateCoef_gain = rtb_OutputCoef;

  /* Outputs for Enabled SubSystem: '<S14>/Subsystem' incorporates:
   *  EnablePort: '<S933>/Enable'
   */
  /* UnitDelay: '<S14>/Unit Delay' */
  if (SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_p) {
    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller9'
     *  Constant: '<S933>/Constant8'
     *  DataTypeConversion: '<S933>/Data Type Conversion16'
     *  DataTypeConversion: '<S933>/Data Type Conversion17'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCMCUTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion18' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller9'
     */
    VFOC_ADCMCUTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller8'
     *  Constant: '<S933>/Constant7'
     *  DataTypeConversion: '<S933>/Data Type Conversion14'
     *  DataTypeConversion: '<S933>/Data Type Conversion15'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCFlyBackTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion19' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller8'
     */
    VFOC_ADCFlyBackTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller1'
     *  Constant: '<S933>/Constant14'
     *  DataTypeConversion: '<S933>/Data Type Conversion'
     *  DataTypeConversion: '<S933>/Data Type Conversion4'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCOilTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion20' incorporates:
     *  CCaller: '<S933>/C Caller1'
     *  CCaller: '<S933>/C Caller11'
     */
    VFOC_ADCOilTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller2'
     *  Constant: '<S933>/Constant1'
     *  DataTypeConversion: '<S933>/Data Type Conversion1'
     *  DataTypeConversion: '<S933>/Data Type Conversion2'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCMotorUTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion21' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller2'
     */
    VFOC_ADCMotorUTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller3'
     *  Constant: '<S933>/Constant2'
     *  DataTypeConversion: '<S933>/Data Type Conversion3'
     *  DataTypeConversion: '<S933>/Data Type Conversion5'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCMotorVTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion22' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller3'
     */
    VFOC_ADCMotorVTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller4'
     *  Constant: '<S933>/Constant3'
     *  DataTypeConversion: '<S933>/Data Type Conversion6'
     *  DataTypeConversion: '<S933>/Data Type Conversion7'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCMotorWTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion23' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller4'
     */
    VFOC_ADCMotorWTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller5'
     *  Constant: '<S933>/Constant4'
     *  DataTypeConversion: '<S933>/Data Type Conversion8'
     *  DataTypeConversion: '<S933>/Data Type Conversion9'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCSicUTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion24' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller5'
     */
    VFOC_ADCSicUTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller6'
     *  Constant: '<S933>/Constant5'
     *  DataTypeConversion: '<S933>/Data Type Conversion10'
     *  DataTypeConversion: '<S933>/Data Type Conversion11'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCSicVTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion25' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller6'
     */
    VFOC_ADCSicVTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller7'
     *  Constant: '<S933>/Constant6'
     *  DataTypeConversion: '<S933>/Data Type Conversion12'
     *  DataTypeConversion: '<S933>/Data Type Conversion13'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)
      KFOC_ADCSicWTemp_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion26' incorporates:
     *  CCaller: '<S933>/C Caller11'
     *  CCaller: '<S933>/C Caller7'
     */
    VFOC_ADCSicWTemp_degC = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  CCaller: '<S933>/C Caller10'
     *  Constant: '<S933>/Constant9'
     *  DataTypeConversion: '<S933>/Data Type Conversion27'
     *  DataTypeConversion: '<S933>/Data Type Conversion28'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)KAPP_ADCKL30_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion29' incorporates:
     *  CCaller: '<S933>/C Caller10'
     *  CCaller: '<S933>/C Caller11'
     */
    SWC_APP_type_ARID_DEF.DataTypeConversion29 = expl_temp.f32_Phy;

    /* CCaller: '<S933>/C Caller11' incorporates:
     *  Constant: '<S933>/Constant10'
     *  DataTypeConversion: '<S933>/Data Type Conversion30'
     *  DataTypeConversion: '<S933>/Data Type Conversion31'
     */
    expl_temp = read_adc_system_value((System_Adc_Signal_Fake)KAPP_ADCKL15_enum);

    /* DataTypeConversion: '<S933>/Data Type Conversion32' incorporates:
     *  CCaller: '<S933>/C Caller11'
     */
    SWC_APP_type_ARID_DEF.DataTypeConversion32 = expl_temp.f32_Phy;
  }

  /* End of UnitDelay: '<S14>/Unit Delay' */
  /* End of Outputs for SubSystem: '<S14>/Subsystem' */

  /* MinMax: '<S807>/Max' */
  SWC_APP_type_ARID_DEF.TempIGBTMax = fmaxf(fmaxf(VFOC_ADCSicUTemp_degC,
    VFOC_ADCSicVTemp_degC), VFOC_ADCSicWTemp_degC);

  /* Outputs for Atomic SubSystem: '<S807>/Derating_Reverse' */
  /* Constant: '<S807>/T1' incorporates:
   *  Constant: '<S807>/T2'
   *  Constant: '<S807>/dT2'
   */
  Derating_Reverse(SWC_APP_type_ARID_DEF.TempIGBTMax, KDGL_IGBTStartDerat_C,
                   KDGL_IGBTHysBand_C, KDGL_IGBTStopDerat_C,
                   &SWC_APP_type_ARID_DEF.Coef_i,
                   &SWC_APP_type_ARID_DEF.ARID_DEF_Derating_Reverse_d);

  /* End of Outputs for SubSystem: '<S807>/Derating_Reverse' */

  /* Outputs for Atomic SubSystem: '<S807>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S816>/debounce' */
  /* Logic: '<S816>/Logical Operator' incorporates:
   *  Constant: '<S816>/Constant1'
   *  Constant: '<S816>/Constant2'
   *  Constant: '<S816>/T2'
   *  RelationalOperator: '<S816>/Relational Operator'
   *  RelationalOperator: '<S816>/Relational Operator1'
   *  RelationalOperator: '<S816>/Relational Operator2'
   */
  rtb_Status_f = SWC_APP_type_debounce_c(((VFOC_ADCSicUTemp_degC >=
    KDGL_IGBTStopDerat_C) || (VFOC_ADCSicVTemp_degC >= KDGL_IGBTStopDerat_C) ||
    (VFOC_ADCSicWTemp_degC >= KDGL_IGBTStopDerat_C)), KDGL_TempIGBTFaultHeal_C,
    KDGL_TempIGBTFaultErr_C, &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_j);

  /* End of Outputs for SubSystem: '<S816>/debounce' */

  /* SignalConversion: '<S816>/Signal Conversion' */
  VDGL_TempIGBTFault_flg = rtb_Status_f;

  /* Outputs for Atomic SubSystem: '<S817>/debounce' */
  /* Logic: '<S817>/Logical Operator' incorporates:
   *  Constant: '<S817>/Constant1'
   *  Constant: '<S817>/Constant2'
   *  Constant: '<S817>/T1'
   *  RelationalOperator: '<S817>/Relational Operator'
   *  RelationalOperator: '<S817>/Relational Operator1'
   *  RelationalOperator: '<S817>/Relational Operator2'
   */
  rtb_Status_k = SWC_APP_type_debounce_c(((VFOC_ADCSicUTemp_degC >=
    KDGL_IGBTStartDerat_C) || (VFOC_ADCSicVTemp_degC >= KDGL_IGBTStartDerat_C) ||
    (VFOC_ADCSicWTemp_degC >= KDGL_IGBTStartDerat_C)),
    KDGL_TempIGBTWarningHeal_C, KDGL_TempIGBTWarningErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_l);

  /* End of Outputs for SubSystem: '<S817>/debounce' */

  /* SignalConversion: '<S817>/Signal Conversion' */
  VDGL_TempIGBTWarning_flg = rtb_Status_k;

  /* End of Outputs for SubSystem: '<S807>/Function-Call Subsystem' */

  /* Switch: '<S807>/Switch' incorporates:
   *  Constant: '<S807>/Constant'
   *  Constant: '<S807>/T3'
   *  Constant: '<S807>/T4'
   */
  if (VDGL_TempIGBTWarning_flg) {
    tmp_2 = SWC_APP_type_ARID_DEF.Coef_i;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S807>/CoefSmooth' */
  CoefSmooth(tmp_2, KDGL_IGBTCoefDepStep_C, KDGL_IGBTCoefAddStep_C,
             &SWC_APP_type_ARID_DEF.OutputCoef_n);

  /* End of Switch: '<S807>/Switch' */
  /* End of Outputs for SubSystem: '<S807>/CoefSmooth' */

  /* SignalConversion generated from: '<S807>/CoefSmooth' */
  VDGL_IGBTDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef_n;

  /* MinMax: '<S713>/MinMax1' */
  SWC_APP_type_ARID_DEF.MinMax1 = fmaxf(fmaxf(VFOC_ADCMotorUTemp_degC,
    VFOC_ADCMotorVTemp_degC), VFOC_ADCMotorWTemp_degC);

  /* Outputs for Atomic SubSystem: '<S810>/Temp_Derating_Reverse' */
  /* Constant: '<S810>/T3' incorporates:
   *  Constant: '<S810>/T4'
   *  Constant: '<S810>/dT1'
   */
  Derating_Reverse(SWC_APP_type_ARID_DEF.MinMax1, KDGL_MotStartDerat_C,
                   KDGL_MotHysBand_C, KDGL_MotStopDerat_C,
                   &SWC_APP_type_ARID_DEF.Coef,
                   &SWC_APP_type_ARID_DEF.ARID_DEF_Temp_Derating_Reverse);

  /* End of Outputs for SubSystem: '<S810>/Temp_Derating_Reverse' */

  /* Outputs for Atomic SubSystem: '<S810>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S841>/debounce' */
  /* RelationalOperator: '<S841>/Relational Operator' incorporates:
   *  Constant: '<S841>/Constant1'
   *  Constant: '<S841>/Constant2'
   *  Constant: '<S841>/T3'
   */
  rtb_Status_l = SWC_APP_type_debounce_c((SWC_APP_type_ARID_DEF.MinMax1 >=
    KDGL_MotStartDerat_C), KDGL_TempMotWarningHeal_C, KDGL_TempMotWarningErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce);

  /* End of Outputs for SubSystem: '<S841>/debounce' */

  /* SignalConversion: '<S841>/Signal Conversion' */
  VDGL_TempMotWarning_flg = rtb_Status_l;

  /* Outputs for Atomic SubSystem: '<S841>/debounce1' */
  /* RelationalOperator: '<S841>/Relational Operator1' incorporates:
   *  Constant: '<S841>/Constant4'
   *  Constant: '<S841>/Constant5'
   *  Constant: '<S841>/T4'
   */
  rtb_Status = SWC_APP_type_debounce_c((SWC_APP_type_ARID_DEF.MinMax1 >=
    KDGL_MotStopDerat_C), KDGL_TempMotFaultHeal_C, KDGL_TempMotFaultErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce1);

  /* End of Outputs for SubSystem: '<S841>/debounce1' */

  /* SignalConversion: '<S841>/Signal Conversion1' */
  VDGL_TempMotFault_flg = rtb_Status;

  /* End of Outputs for SubSystem: '<S810>/Function-Call Subsystem' */

  /* Switch: '<S810>/Switch' incorporates:
   *  Constant: '<S810>/Constant'
   *  Constant: '<S810>/T5'
   *  Constant: '<S810>/T6'
   */
  if (VDGL_TempMotWarning_flg) {
    tmp_2 = SWC_APP_type_ARID_DEF.Coef;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S810>/CoefSmooth' */
  CoefSmooth(tmp_2, KDGL_MotCoefDepStep_C, KDGL_MotCoefAddStep_C,
             &SWC_APP_type_ARID_DEF.OutputCoef);

  /* End of Switch: '<S810>/Switch' */
  /* End of Outputs for SubSystem: '<S810>/CoefSmooth' */

  /* SignalConversion generated from: '<S810>/CoefSmooth' */
  VDGL_MotDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef;

  /* Outputs for Atomic SubSystem: '<S809>/Derating_Reverse' */
  /* Constant: '<S809>/T1' incorporates:
   *  Constant: '<S809>/T2'
   *  Constant: '<S809>/dT2'
   */
  Derating_Reverse(VFOC_ADCMCUTemp_degC, KDGL_PCBStartDerat_C, KDGL_PCBHysBand_C,
                   KDGL_PCBStopDerat_C, &SWC_APP_type_ARID_DEF.Coef_k,
                   &SWC_APP_type_ARID_DEF.ARID_DEF_Derating_Reverse);

  /* End of Outputs for SubSystem: '<S809>/Derating_Reverse' */

  /* Outputs for Atomic SubSystem: '<S809>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S833>/debounce' */
  /* RelationalOperator: '<S833>/Relational Operator' incorporates:
   *  Constant: '<S833>/Constant1'
   *  Constant: '<S833>/Constant2'
   *  Constant: '<S833>/T1'
   */
  rtb_Status_b = SWC_APP_type_debounce_c((VFOC_ADCMCUTemp_degC >=
    KDGL_PCBStartDerat_C), KDGL_TempPCBWarningHeal_C, KDGL_TempPCBWarningErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_g);

  /* End of Outputs for SubSystem: '<S833>/debounce' */

  /* SignalConversion: '<S833>/Signal Conversion' */
  VDGL_TempPCBWarning_flg = rtb_Status_b;

  /* Outputs for Atomic SubSystem: '<S833>/debounce1' */
  /* RelationalOperator: '<S833>/Relational Operator1' incorporates:
   *  Constant: '<S833>/Constant4'
   *  Constant: '<S833>/Constant5'
   *  Constant: '<S833>/T2'
   */
  rtb_Status_j = SWC_APP_type_debounce_c((VFOC_ADCMCUTemp_degC >=
    KDGL_PCBStopDerat_C), KDGL_TempPCBFaultHeal_C, KDGL_TempPCBFaultErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce1_g);

  /* End of Outputs for SubSystem: '<S833>/debounce1' */

  /* SignalConversion: '<S833>/Signal Conversion1' */
  VDGL_TempPCBFault_flg = rtb_Status_j;

  /* End of Outputs for SubSystem: '<S809>/Function-Call Subsystem' */

  /* Switch: '<S809>/Switch' incorporates:
   *  Constant: '<S809>/Constant'
   *  Constant: '<S809>/T3'
   *  Constant: '<S809>/T4'
   */
  if (VDGL_TempPCBWarning_flg) {
    tmp_2 = SWC_APP_type_ARID_DEF.Coef_k;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S809>/CoefSmooth' */
  CoefSmooth(tmp_2, KDGL_PCBCoefDepStep_C, KDGL_PCBCoefAddStep_C,
             &SWC_APP_type_ARID_DEF.OutputCoef_l);

  /* End of Switch: '<S809>/Switch' */
  /* End of Outputs for SubSystem: '<S809>/CoefSmooth' */

  /* SignalConversion generated from: '<S809>/CoefSmooth' */
  VDGL_PCBDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef_l;

  /* Outputs for Atomic SubSystem: '<S808>/Derating_Reverse' */
  /* Constant: '<S808>/T1' incorporates:
   *  Constant: '<S808>/T2'
   *  Constant: '<S808>/dT2'
   */
  Derating_Reverse(VFOC_ADCOilTemp_degC, KDGL_OilStartDerat_C, KDGL_OilHysBand_C,
                   KDGL_OilStopDerat_C, &SWC_APP_type_ARID_DEF.Coef_l,
                   &SWC_APP_type_ARID_DEF.ARID_DEF_Derating_Reverse_p);

  /* End of Outputs for SubSystem: '<S808>/Derating_Reverse' */

  /* Outputs for Atomic SubSystem: '<S808>/Function-Call Subsystem' */
  /* Outputs for Atomic SubSystem: '<S824>/debounce' */
  /* RelationalOperator: '<S824>/Relational Operator' incorporates:
   *  Constant: '<S824>/Constant1'
   *  Constant: '<S824>/Constant2'
   *  Constant: '<S824>/T1'
   */
  rtb_Status_d = SWC_APP_type_debounce_c((VFOC_ADCOilTemp_degC >=
    KDGL_OilStartDerat_C), KDGL_TempOilWarningHeal_C, KDGL_TempOilWarningErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce_n);

  /* End of Outputs for SubSystem: '<S824>/debounce' */

  /* SignalConversion: '<S824>/Signal Conversion' */
  VDGL_TempOilWarning_flg = rtb_Status_d;

  /* Outputs for Atomic SubSystem: '<S824>/debounce1' */
  /* RelationalOperator: '<S824>/Relational Operator1' incorporates:
   *  Constant: '<S824>/Constant4'
   *  Constant: '<S824>/Constant5'
   *  Constant: '<S824>/T2'
   */
  rtb_Status_b2 = SWC_APP_type_debounce_c((VFOC_ADCOilTemp_degC >=
    KDGL_OilStopDerat_C), KDGL_TempOilFaultHeal_C, KDGL_TempOilFaultErr_C,
    &SWC_APP_type_ARID_DEF.ARID_DEF_debounce1_m);

  /* End of Outputs for SubSystem: '<S824>/debounce1' */

  /* SignalConversion: '<S824>/Signal Conversion1' */
  VDGL_TempOilFault_flg = rtb_Status_b2;

  /* End of Outputs for SubSystem: '<S808>/Function-Call Subsystem' */

  /* Switch: '<S808>/Switch' incorporates:
   *  Constant: '<S808>/Constant'
   *  Constant: '<S808>/T3'
   *  Constant: '<S808>/T4'
   */
  if (VDGL_TempOilWarning_flg) {
    tmp_2 = SWC_APP_type_ARID_DEF.Coef_l;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S808>/CoefSmooth' */
  CoefSmooth(tmp_2, KDGL_OilCoefDepStep_C, KDGL_OilCoefAddStep_C,
             &SWC_APP_type_ARID_DEF.OutputCoef_f);

  /* End of Switch: '<S808>/Switch' */
  /* End of Outputs for SubSystem: '<S808>/CoefSmooth' */

  /* SignalConversion generated from: '<S808>/CoefSmooth' */
  VDGL_OilDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef_f;

  /* Outputs for Atomic SubSystem: '<S778>/Derating_Reverse' */
  /* Constant: '<S778>/T1' incorporates:
   *  Constant: '<S778>/T2'
   *  Constant: '<S778>/dT2'
   */
  Derating_Reverse
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
     Diag2_f32_UdcOverStartDerat_C, Diag2_f32_UdcOverHysBand_C,
     Diag2_f32_UdcOverStopDerat_C, &SWC_APP_type_ARID_DEF.Coef_d,
     &SWC_APP_type_ARID_DEF.ARID_DEF_Derating_Reverse_dy);

  /* End of Outputs for SubSystem: '<S778>/Derating_Reverse' */

  /* Switch: '<S778>/Switch' incorporates:
   *  Constant: '<S778>/Constant'
   *  Constant: '<S778>/T3'
   *  Constant: '<S778>/T4'
   */
  if (VDGL_HVOverWarn_flg) {
    tmp_2 = SWC_APP_type_ARID_DEF.Coef_d;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S778>/CoefSmooth' */
  CoefSmooth(tmp_2, Diag2_f32_UdcOverCoefDepStep_C,
             Diag2_f32_UdcOverCoefAddStep_C, &SWC_APP_type_ARID_DEF.OutputCoef_m);

  /* End of Switch: '<S778>/Switch' */
  /* End of Outputs for SubSystem: '<S778>/CoefSmooth' */

  /* SignalConversion generated from: '<S778>/CoefSmooth' */
  VDGL_UdcOverDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef_m;

  /* Outputs for Atomic SubSystem: '<S777>/Derating_Forward' */
  /* Constant: '<S777>/T1' incorporates:
   *  Constant: '<S777>/T2'
   *  Constant: '<S777>/dT2'
   */
  rtb_SWT = Derating_Forward
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
     Diag2_f32_UdcLowStartDerat_C, Diag2_f32_UdcLowHysBand_C,
     Diag2_f32_UdcLowStopDerat_C,
     &SWC_APP_type_ARID_DEF.ARID_DEF_Derating_Forward);

  /* End of Outputs for SubSystem: '<S777>/Derating_Forward' */

  /* Switch: '<S777>/Switch' incorporates:
   *  Constant: '<S777>/Constant'
   *  Constant: '<S777>/T3'
   *  Constant: '<S777>/T4'
   */
  if (VDGL_HVLowWarn_flg) {
    tmp_2 = rtb_SWT;
  } else {
    tmp_2 = 1.0F;
  }

  /* Outputs for Atomic SubSystem: '<S777>/CoefSmooth' */
  CoefSmooth(tmp_2, Diag2_f32_UdcLowCoefDepStep_C, Diag2_f32_UdcLowCoefAddStep_C,
             &SWC_APP_type_ARID_DEF.OutputCoef_p);

  /* End of Switch: '<S777>/Switch' */
  /* End of Outputs for SubSystem: '<S777>/CoefSmooth' */

  /* SignalConversion generated from: '<S777>/CoefSmooth' */
  VDGL_UdcLowDerateCoef_gain = SWC_APP_type_ARID_DEF.OutputCoef_p;

  /* MinMax: '<S702>/MinMax' */
  VSYL_facTorqueCoef_null = fminf(fminf(fminf(fminf(fminf(fminf
    (VDGL_OverSpdDerateCoef_gain, VDGL_IGBTDerateCoef_gain),
    VDGL_MotDerateCoef_gain), VDGL_PCBDerateCoef_gain), VDGL_OilDerateCoef_gain),
    VDGL_UdcOverDerateCoef_gain), VDGL_UdcLowDerateCoef_gain);

  /* Switch: '<S702>/Switch2' incorporates:
   *  Constant: '<S705>/Constant'
   *  RelationalOperator: '<S705>/Compare'
   */
  if (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot >=
      0.0F) {
    /* Product: '<S17>/Product1' */
    rtb_Prelookup1_o2_n =
      SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot;
  } else {
    /* Product: '<S17>/Product1' incorporates:
     *  Gain: '<S702>/Gain2'
     */
    rtb_Prelookup1_o2_n =
      -SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot;
  }

  /* End of Switch: '<S702>/Switch2' */

  /* Lookup_n-D: '<S702>/TrqMax' incorporates:
   *  Product: '<S17>/Product1'
   */
  rtb_TrqMax = look2_iflf_binlxpw(rtb_Prelookup1_o2_n,
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
    &ASYL_TrqMax_Y_rpm[0], &ASYL_TrqMax_X_V[0], &MSYL_TrqMax_Z_Nm[0],
    SWC_APP_type_ConstP.pooled27, 21U);

  /* Lookup_n-D: '<S702>/TrqMin' incorporates:
   *  Product: '<S17>/Product1'
   */
  rtb_Prelookup1_o2_n = look2_iflf_binlxpw(rtb_Prelookup1_o2_n,
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
    &ASYL_TrqMin_Y_rpm[0], &ASYL_TrqMin_X_V[0], &MSYL_TrqMin_Z_Nm[0],
    SWC_APP_type_ConstP.pooled27, 21U);

  /* Switch: '<S702>/Switch' incorporates:
   *  Constant: '<S703>/Constant'
   *  Gain: '<S702>/Gain'
   *  Gain: '<S702>/Gain1'
   *  RelationalOperator: '<S703>/Compare'
   *  Switch: '<S702>/Switch1'
   */
  if (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot >=
      0.0F) {
    tmp_2 = rtb_TrqMax;
  } else {
    tmp_2 = -rtb_Prelookup1_o2_n;
    rtb_Prelookup1_o2_n = -rtb_TrqMax;
  }

  /* Product: '<S702>/Product' incorporates:
   *  Switch: '<S702>/Switch'
   */
  VSYL_tqTMTqMax_Nm = VSYL_facTorqueCoef_null * tmp_2;

  /* Product: '<S702>/Product1' incorporates:
   *  Switch: '<S702>/Switch1'
   */
  VSYL_tqTMTqMin_Nm = VSYL_facTorqueCoef_null * rtb_Prelookup1_o2_n;

  /* Logic: '<S760>/AND1' incorporates:
   *  Abs: '<S18>/Abs1'
   *  Constant: '<S18>/Constant6'
   *  Gain: '<S18>/Gain'
   *  Product: '<S18>/Divide1'
   *  RelationalOperator: '<S18>/Relational Operator3'
   */
  rtb_AND1_l = (KCRM_IqDeratingFac_null * -fabsf(VSYL_tqTMTqMin_Nm) >= 0.0F);

  /* Logic: '<S18>/Logical Operator3' incorporates:
   *  Constant: '<S18>/Constant6'
   *  Product: '<S18>/Divide'
   *  RelationalOperator: '<S18>/Relational Operator2'
   */
  rtb_LogicalOperator5 = ((KCRM_IqDeratingFac_null * VSYL_tqTMTqMax_Nm <= 0.0F) ||
    rtb_AND1_l);

  /* Outputs for Atomic SubSystem: '<S18>/TurnOnDelay_Dyn2' */
  /* Outputs for Atomic SubSystem: '<S35>/Rising' */
  rtb_AND1_h1 = SWC_APP_type_Rising(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising_j);

  /* End of Outputs for SubSystem: '<S35>/Rising' */

  /* Outputs for Atomic SubSystem: '<S35>/Delay' */
  rtb_UnitDelay_d = SWC_APP_type_Delay_m
    (&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_bb);

  /* End of Outputs for SubSystem: '<S35>/Delay' */

  /* Switch: '<S86>/SWT' */
  if (rtb_AND1_h1) {
    /* Switch: '<S86>/SWT' incorporates:
     *  Constant: '<S35>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_iv = 0.0F;
  } else {
    /* Switch: '<S86>/SWT' incorporates:
     *  Constant: '<S18>/Constant38'
     *  Sum: '<S84>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_iv = rtb_UnitDelay_d + 1.0F;
  }

  /* End of Switch: '<S86>/SWT' */

  /* Switch: '<S85>/SWT' */
  if (rtb_LogicalOperator5) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S18>/Constant4'
     *  Sum: '<S83>/Sub1'
     */
    rtb_SWT = KCRM_IqDeratingTi_ms - SWC_APP_type_ConstB.Gain1_c;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S35>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S85>/SWT' */

  /* Outputs for Atomic SubSystem: '<S35>/Rising1' */
  /* Logic: '<S75>/AND1' incorporates:
   *  RelationalOperator: '<S76>/Relational Operator'
   */
  rtb_AND1_h1 = SWC_APP_type_Rising((rtb_LogicalOperator5 &&
    (SWC_APP_type_ARID_DEF.SWT_iv >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_a);

  /* End of Outputs for SubSystem: '<S35>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S35>/Falling' */
  rtb_AND1_ig = SWC_APP_type_Falling(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_e);

  /* End of Outputs for SubSystem: '<S35>/Falling' */

  /* Outputs for Atomic SubSystem: '<S35>/ER_FF' */
  SWC_APP_type_ER_FF(rtb_AND1_h1, rtb_AND1_ig, &SWC_APP_type_ARID_DEF.SWT_g,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_o);

  /* End of Outputs for SubSystem: '<S35>/ER_FF' */

  /* Update for Atomic SubSystem: '<S35>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_iv,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_bb);

  /* End of Update for SubSystem: '<S35>/Delay' */
  /* End of Outputs for SubSystem: '<S18>/TurnOnDelay_Dyn2' */

  /* Outputs for Atomic SubSystem: '<S18>/ER_FF' */
  /* UnitDelay: '<S18>/Unit Delay' */
  SWC_APP_type_ER_FF(SWC_APP_type_ARID_DEF.SWT_g,
                     SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_hc,
                     &SWC_APP_type_ARID_DEF.SWT_c1,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_c);

  /* End of Outputs for SubSystem: '<S18>/ER_FF' */

  /* RelationalOperator: '<S18>/Relational Operator4' incorporates:
   *  Constant: '<S18>/Constant12'
   */
  rtb_LogicalOperator5 =
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide >=
     KCRM_nDebugOverSpd_rpm);

  /* Outputs for Atomic SubSystem: '<S18>/TurnOnDelay_Dyn3' */
  /* Outputs for Atomic SubSystem: '<S36>/Rising' */
  rtb_AND1_g2 = SWC_APP_type_Rising(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising_kl);

  /* End of Outputs for SubSystem: '<S36>/Rising' */

  /* Outputs for Atomic SubSystem: '<S36>/Delay' */
  rtb_UnitDelay_plq = SWC_APP_type_Delay_m
    (&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_p4);

  /* End of Outputs for SubSystem: '<S36>/Delay' */

  /* Switch: '<S111>/SWT' */
  if (rtb_AND1_g2) {
    /* Switch: '<S111>/SWT' incorporates:
     *  Constant: '<S36>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_i = 0.0F;
  } else {
    /* Switch: '<S111>/SWT' incorporates:
     *  Constant: '<S18>/Constant3'
     *  Sum: '<S109>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_i = rtb_UnitDelay_plq + 1.0F;
  }

  /* End of Switch: '<S111>/SWT' */

  /* Switch: '<S110>/SWT' */
  if (rtb_LogicalOperator5) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S18>/Constant11'
     *  Sum: '<S108>/Sub1'
     */
    rtb_SWT = KCRM_tiDebugOverSpdDlyon_ms - SWC_APP_type_ConstB.Gain1_g;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S36>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S110>/SWT' */

  /* Outputs for Atomic SubSystem: '<S36>/Rising1' */
  /* Logic: '<S100>/AND1' incorporates:
   *  RelationalOperator: '<S101>/Relational Operator'
   */
  rtb_AND1_g2 = SWC_APP_type_Rising((rtb_LogicalOperator5 &&
    (SWC_APP_type_ARID_DEF.SWT_i >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_cs);

  /* End of Outputs for SubSystem: '<S36>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S36>/Falling' */
  rtb_AND1_h1 = SWC_APP_type_Falling(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_p);

  /* End of Outputs for SubSystem: '<S36>/Falling' */

  /* Outputs for Atomic SubSystem: '<S36>/ER_FF' */
  SWC_APP_type_ER_FF(rtb_AND1_g2, rtb_AND1_h1, &SWC_APP_type_ARID_DEF.SWT_b,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_p);

  /* End of Outputs for SubSystem: '<S36>/ER_FF' */

  /* Update for Atomic SubSystem: '<S36>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_i,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_p4);

  /* End of Update for SubSystem: '<S36>/Delay' */
  /* End of Outputs for SubSystem: '<S18>/TurnOnDelay_Dyn3' */

  /* Outputs for Atomic SubSystem: '<S18>/ER_FF1' */
  /* Outputs for Atomic SubSystem: '<S22>/Delay' */
  rtb_UnitDelay_nm = SWC_APP_type_Delay(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_e);

  /* End of Outputs for SubSystem: '<S22>/Delay' */

  /* Switch: '<S44>/SWT' */
  if (SWC_APP_type_ARID_DEF.SWT_b) {
    /* Switch: '<S44>/SWT' incorporates:
     *  Constant: '<S22>/true'
     */
    SWC_APP_type_ARID_DEF.SWT_he = true_MatlabRTW;
  } else {
    /* Switch: '<S44>/SWT' incorporates:
     *  Constant: '<S18>/Constant15'
     *  Switch: '<S43>/SWT'
     */
    SWC_APP_type_ARID_DEF.SWT_he = ((!KCRM_bRstDebugOverSpd_null) &&
      rtb_UnitDelay_nm);
  }

  /* End of Switch: '<S44>/SWT' */

  /* Update for Atomic SubSystem: '<S22>/Delay' */
  SWC_APP_type_Delay_Update(SWC_APP_type_ARID_DEF.SWT_he,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_e);

  /* End of Update for SubSystem: '<S22>/Delay' */
  /* End of Outputs for SubSystem: '<S18>/ER_FF1' */

  /* Outputs for Atomic SubSystem: '<S13>/ER_FF1' */
  /* Outputs for Atomic SubSystem: '<S710>/Delay' */
  rtb_UnitDelay_f3 = SWC_APP_type_Delay(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_b);

  /* End of Outputs for SubSystem: '<S710>/Delay' */

  /* Switch: '<S776>/SWT' incorporates:
   *  Logic: '<S13>/Logical Operator3'
   */
  if (VDGL_TempIGBTFault_flg || VDGL_TempMotFault_flg || VDGL_TempPCBFault_flg ||
      VDGL_TempOilFault_flg || VDGL_DiagStall_flg) {
    /* Switch: '<S776>/SWT' incorporates:
     *  Constant: '<S710>/true'
     */
    SWC_APP_type_ARID_DEF.SWT_f = true_MatlabRTW;
  } else {
    /* Switch: '<S776>/SWT' incorporates:
     *  Constant: '<S13>/Constant2'
     *  Switch: '<S775>/SWT'
     */
    SWC_APP_type_ARID_DEF.SWT_f = ((!Diag2_bRstFault_C) && rtb_UnitDelay_f3);
  }

  /* End of Switch: '<S776>/SWT' */

  /* Update for Atomic SubSystem: '<S710>/Delay' */
  SWC_APP_type_Delay_Update(SWC_APP_type_ARID_DEF.SWT_f,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_b);

  /* End of Update for SubSystem: '<S710>/Delay' */
  /* End of Outputs for SubSystem: '<S13>/ER_FF1' */

  /* Switch: '<S18>/Switch' incorporates:
   *  Constant: '<S18>/Constant7'
   *  Constant: '<S18>/Constant9'
   */
  if (SWC_APP_type_ARID_DEF.SWT_c1) {
    tmp_2 = KCRM_IqDeratingFac_null;
  } else {
    tmp_2 = 1.0F;
  }

  /* Switch: '<S13>/DiagM_bZeroCurrswt' incorporates:
   *  Constant: '<S13>/DiagM_bZeroCurrMor_C'
   *  Constant: '<S13>/DiagM_bZeroCurrTrig_C'
   */
  if (DiagM_bZeroCurrTrig_C) {
    rtb_LogicalOperator5 = DiagM_bZeroCurrMor_C;
  } else {
    rtb_LogicalOperator5 = SWC_APP_type_ARID_DEF.SWT_f;
  }

  /* Sum: '<S20>/Add' incorporates:
   *  Constant: '<S20>/Constant'
   *  MinMax: '<S18>/MinMax'
   *  Product: '<S20>/Product'
   *  Sum: '<S20>/Subtract'
   *  Switch: '<S13>/DiagM_bZeroCurrswt'
   *  Switch: '<S18>/Switch'
   *  Switch: '<S18>/Switch2'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_j += (fminf(fminf(tmp_2, (float32)
    !SWC_APP_type_ARID_DEF.SWT_he), (float32)!rtb_LogicalOperator5) -
    SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_j) * KCRM_DynoDeratingFiltFac_null;

  /* Sum: '<S30>/Add' incorporates:
   *  Constant: '<S30>/Constant'
   *  Product: '<S18>/Divide2'
   *  Product: '<S30>/Product'
   *  Sum: '<S30>/Subtract'
   *  UnitDelay: '<S20>/Unit Delay'
   *  UnitDelay: '<S30>/Unit Delay'
   */
  VCRM_IqCmd_A = (VCRM_IqCmdFWC_A * SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_j -
                  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_i) *
    KCRM_IqCmdFilCoeff_null + SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_i;

  /* BusCreator: '<S2>/Bus Creator' */
  message = VOPM_MotMod_enum;
  rtb_BitwiseOR1 = VOPM_IVTROpMode_enum;
  rtb_TrqMax = VCRM_IdCmd_A;
  rtb_Prelookup1_o2_n = VCRM_IqCmd_A;
  rtb_BitwiseOR = rtb_MinMax5;

  /* Product: '<S17>/Product2' incorporates:
   *  Gain: '<S17>/Gain1'
   *  Lookup_n-D: '<S17>/MPEM_EtaY_value'
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Sum: '<S17>/Add2'
   */
  VCRM_PwrEleAct_W =
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_uDVoltTar *
     SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_iDCurrAct +
     SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_uQVoltTar *
     SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_iQCurrAct) *
    1.5F * look1_iflf_binlcapw
    (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide,
     &ACRM_Eta_X_rpm[0], &MCRM_Eta_Y_null[0], 3U);

  /* Switch: '<S17>/Switch' incorporates:
   *  Constant: '<S17>/Constant2'
   */
  if (SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot > 0.1F)
  {
    tmp_2 = SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot;
  } else {
    tmp_2 = 1.0F;
  }

  /* Sum: '<S19>/Add' incorporates:
   *  Constant: '<S17>/Constant1'
   *  Product: '<S17>/Divide'
   *  Product: '<S19>/Product'
   *  Sum: '<S19>/Subtract'
   *  Switch: '<S17>/Switch'
   */
  VCRM_BusCurr_A += (VCRM_PwrEleAct_W / tmp_2 - VCRM_BusCurr_A) *
    KCRM_BusCurFil_null;

  /* Switch: '<S48>/Switch' incorporates:
   *  Constant: '<S23>/Constant2'
   *  Constant: '<S45>/Constant'
   *  RelationalOperator: '<S48>/u_GTE_up'
   *  RelationalOperator: '<S48>/u_GT_lo'
   *  Switch: '<S48>/Switch1'
   */
  if (rtb_Prelookup1_o2 >= 0.0F) {
    /* Switch: '<S729>/SWT' */
    rtb_SWT = 0.0F;
  } else if (rtb_Prelookup1_o2 > KCRM_PILowerLimit_null) {
    /* Switch: '<S48>/Switch1' incorporates:
     *  Switch: '<S729>/SWT'
     */
    rtb_SWT = rtb_Prelookup1_o2;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S23>/Constant2'
     *  Switch: '<S48>/Switch1'
     */
    rtb_SWT = KCRM_PILowerLimit_null;
  }

  /* End of Switch: '<S48>/Switch' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Sum: '<S48>/Diff'
   */
  rtb_SWT = rtb_Prelookup1_o2 - rtb_SWT;

  /* Product: '<S45>/Product' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S23>/Gain'
   */
  rtb_Prelookup_o2 *= KCRM_SpdCtlPrd_s * KCRM_FWCKi_null;

  /* Switch: '<S46>/Switch1' incorporates:
   *  Constant: '<S46>/Constant'
   *  Constant: '<S46>/Constant2'
   *  Constant: '<S46>/Constant5'
   *  RelationalOperator: '<S46>/Relational Operator1'
   */
  if (rtb_SWT > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S46>/Switch2' incorporates:
   *  Constant: '<S46>/Constant3'
   *  Constant: '<S46>/Constant4'
   *  Constant: '<S46>/Constant5'
   *  RelationalOperator: '<S46>/Relational Operator2'
   */
  if (rtb_Prelookup_o2 > 0.0F) {
    tmp_3 = 1;
  } else {
    tmp_3 = -1;
  }

  /* Switch: '<S46>/Switch3' incorporates:
   *  Constant: '<S46>/Constant5'
   *  Logic: '<S46>/AND3'
   *  RelationalOperator: '<S46>/Equal1'
   *  RelationalOperator: '<S46>/Relational Operator'
   *  Switch: '<S46>/Switch1'
   *  Switch: '<S46>/Switch2'
   */
  if ((rtb_SWT != 0.0F) && (tmp == tmp_3)) {
    /* Switch: '<S46>/Switch3' incorporates:
     *  Constant: '<S46>/Constant1'
     */
    rtb_Prelookup_o2 = 0.0F;
  }

  /* End of Switch: '<S46>/Switch3' */

  /* Outputs for Atomic SubSystem: '<S18>/TurnOnDelay_Dyn1' */
  /* Outputs for Atomic SubSystem: '<S34>/Rising' */
  rtb_AND1_g2 = SWC_APP_type_Rising(SWC_APP_type_ARID_DEF.SWT_c1,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising_g);

  /* End of Outputs for SubSystem: '<S34>/Rising' */

  /* Outputs for Atomic SubSystem: '<S34>/Delay' */
  rtb_UnitDelay_e = SWC_APP_type_Delay_m(&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_h);

  /* End of Outputs for SubSystem: '<S34>/Delay' */

  /* Switch: '<S61>/SWT' */
  if (rtb_AND1_g2) {
    /* Switch: '<S61>/SWT' incorporates:
     *  Constant: '<S34>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_k = 0.0F;
  } else {
    /* Switch: '<S61>/SWT' incorporates:
     *  Constant: '<S18>/Constant10'
     *  Sum: '<S59>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_k = rtb_UnitDelay_e + 1.0F;
  }

  /* End of Switch: '<S61>/SWT' */

  /* Switch: '<S60>/SWT' */
  if (SWC_APP_type_ARID_DEF.SWT_c1) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S18>/Constant8'
     *  Sum: '<S58>/Sub1'
     */
    rtb_SWT = KCRM_IqDeratingRecoverTi_ms - SWC_APP_type_ConstB.Gain1_gq;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S34>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S60>/SWT' */

  /* Outputs for Atomic SubSystem: '<S34>/Rising1' */
  /* Logic: '<S50>/AND1' incorporates:
   *  RelationalOperator: '<S51>/Relational Operator'
   */
  rtb_AND1_g2 = SWC_APP_type_Rising((SWC_APP_type_ARID_DEF.SWT_c1 &&
    (SWC_APP_type_ARID_DEF.SWT_k >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_ao);

  /* End of Outputs for SubSystem: '<S34>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S34>/Falling' */
  rtb_AND1_gb = SWC_APP_type_Falling(SWC_APP_type_ARID_DEF.SWT_c1,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_ex);

  /* End of Outputs for SubSystem: '<S34>/Falling' */

  /* Outputs for Atomic SubSystem: '<S34>/ER_FF' */
  /* UnitDelay: '<S18>/Unit Delay' */
  SWC_APP_type_ER_FF(rtb_AND1_g2, rtb_AND1_gb,
                     &SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_hc,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_f);

  /* End of Outputs for SubSystem: '<S34>/ER_FF' */

  /* Update for Atomic SubSystem: '<S34>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_k,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_h);

  /* End of Update for SubSystem: '<S34>/Delay' */
  /* End of Outputs for SubSystem: '<S18>/TurnOnDelay_Dyn1' */

  /* Outputs for Atomic SubSystem: '<S2>/EOP' */
  SWC_APP_type_EOP();

  /* End of Outputs for SubSystem: '<S2>/EOP' */

  /* Outputs for Atomic SubSystem: '<S699>/override_signal_m2 ' */
  /* BusCreator: '<S12>/Bus Creator' incorporates:
   *  Constant: '<S699>/_ovrdflg'
   *  Constant: '<S699>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VSYL_tqTMTqMin_Nm,
    KOUTP_tqTMTqMin_Nm_ovrdflg, KOUTP_tqTMTqMin_Nm_ovrdval);

  /* End of Outputs for SubSystem: '<S699>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S698>/_maxval'
   *  MinMax: '<S700>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_tqTMTqMin_Nm_maxval);

  /* MinMax: '<S700>/MinMax10' incorporates:
   *  Constant: '<S698>/_minval'
   */
  VOUTP_tqTMTqMin_Nm = fmaxf(rtb_SWT, KOUTP_tqTMTqMin_Nm_minval);

  /* Outputs for Atomic SubSystem: '<S695>/override_signal_m2 ' */
  /* BusCreator: '<S12>/Bus Creator' incorporates:
   *  Constant: '<S695>/_ovrdflg'
   *  Constant: '<S695>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VSYL_tqTMTqMax_Nm,
    KOUTP_tqTMTqMax_Nm_ovrdflg, KOUTP_tqTMTqMax_Nm_ovrdval);

  /* End of Outputs for SubSystem: '<S695>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S694>/_maxval'
   *  MinMax: '<S696>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_tqTMTqMax_Nm_maxval);

  /* MinMax: '<S696>/MinMax10' incorporates:
   *  Constant: '<S694>/_minval'
   */
  VOUTP_tqTMTqMax_Nm = fmaxf(rtb_SWT, KOUTP_tqTMTqMax_Nm_minval);

  /* DataTypeConversion: '<S10>/Data Type Conversion' */
  VOPM_MCUEna_flg = SWC_APP_type_ARID_DEF.OpMod_bMCUEna;

  /* DataTypeConversion: '<S10>/Data Type Conversion1' */
  VOPM_TMReady_flg = SWC_APP_type_ARID_DEF.OpMod_bTMReady;

  /* DataTypeConversion: '<S10>/Data Type Conversion2' */
  VOPM_BoostOPSta_flg = SWC_APP_type_ARID_DEF.OpMod_bBoostOPSta;

  /* Outputs for Atomic SubSystem: '<S675>/override_signal_m2 ' */
  /* BusCreator: '<S10>/Bus Creator' incorporates:
   *  Constant: '<S675>/_ovrdflg'
   *  Constant: '<S675>/_ovrdval'
   */
  rtb_AND1_g2 = SWC_APP_type_override_signal_m2(VOPM_BoostOPSta_flg,
    KOUTP_BoostOPSta_flg_ovrdflg, KOUTP_BoostOPSta_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S675>/override_signal_m2 ' */

  /* MinMax: '<S676>/MinMax10' incorporates:
   *  Constant: '<S674>/_maxval'
   *  Constant: '<S674>/_minval'
   *  MinMax: '<S676>/MinMax5'
   */
  VOUTP_BoostOPSta_flg = ((rtb_AND1_g2 && KOUTP_BoostOPSta_flg_maxval) ||
    KOUTP_BoostOPSta_flg_minval);

  /* Outputs for Atomic SubSystem: '<S691>/override_signal_m2 ' */
  /* BusCreator: '<S10>/Bus Creator' incorporates:
   *  Constant: '<S691>/_ovrdflg'
   *  Constant: '<S691>/_ovrdval'
   */
  rtb_AND1_g2 = SWC_APP_type_override_signal_m2(VOPM_TMReady_flg,
    KOUTP_TMReady_flg_ovrdflg, KOUTP_TMReady_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S691>/override_signal_m2 ' */

  /* MinMax: '<S692>/MinMax10' incorporates:
   *  Constant: '<S690>/_maxval'
   *  Constant: '<S690>/_minval'
   *  MinMax: '<S692>/MinMax5'
   */
  VOUTP_TMReady_flg = ((rtb_AND1_g2 && KOUTP_TMReady_flg_maxval) ||
                       KOUTP_TMReady_flg_minval);

  /* Outputs for Atomic SubSystem: '<S683>/override_signal_m2 ' */
  /* BusCreator: '<S10>/Bus Creator' incorporates:
   *  Constant: '<S683>/_ovrdflg'
   *  Constant: '<S683>/_ovrdval'
   */
  rtb_AND1_g2 = SWC_APP_type_override_signal_m2(VOPM_MCUEna_flg,
    KOUTP_MCUEna_flg_ovrdflg, KOUTP_MCUEna_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S683>/override_signal_m2 ' */

  /* MinMax: '<S684>/MinMax10' incorporates:
   *  Constant: '<S682>/_maxval'
   *  Constant: '<S682>/_minval'
   *  MinMax: '<S684>/MinMax5'
   */
  VOUTP_MCUEna_flg = ((rtb_AND1_g2 && KOUTP_MCUEna_flg_maxval) ||
                      KOUTP_MCUEna_flg_minval);

  /* Outputs for Atomic SubSystem: '<S679>/override_signal_m2 ' */
  /* BusCreator: '<S10>/Bus Creator' incorporates:
   *  Constant: '<S679>/_ovrdflg'
   *  Constant: '<S679>/_ovrdval'
   */
  rtb_MinMax5 = SWC_APP_ty_override_signal_m2_p(VOPM_IVTROpMode_enum,
    KOUTP_IVTROpMode_enum_ovrdflg, KOUTP_IVTROpMode_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S679>/override_signal_m2 ' */

  /* MinMax: '<S680>/MinMax5' incorporates:
   *  Constant: '<S678>/_maxval'
   */
  u0 = rtb_MinMax5;
  if (u0 <= KOUTP_IVTROpMode_enum_maxval) {
    /* MinMax: '<S688>/MinMax5' */
    rtb_MinMax5 = u0;
  } else {
    /* MinMax: '<S688>/MinMax5' */
    rtb_MinMax5 = KOUTP_IVTROpMode_enum_maxval;
  }

  /* End of MinMax: '<S680>/MinMax5' */

  /* MinMax: '<S680>/MinMax10' incorporates:
   *  Constant: '<S678>/_minval'
   */
  VOUTP_IVTROpMode_enum = rtb_MinMax5;
  if (VOUTP_IVTROpMode_enum < KOUTP_IVTROpMode_enum_minval) {
    /* MinMax: '<S680>/MinMax10' */
    VOUTP_IVTROpMode_enum = KOUTP_IVTROpMode_enum_minval;
  }

  /* End of MinMax: '<S680>/MinMax10' */

  /* Outputs for Atomic SubSystem: '<S687>/override_signal_m2 ' */
  /* BusCreator: '<S10>/Bus Creator' incorporates:
   *  Constant: '<S687>/_ovrdflg'
   *  Constant: '<S687>/_ovrdval'
   */
  rtb_MinMax5 = SWC_APP_ty_override_signal_m2_p(VOPM_MotMod_enum,
    KOUTP_MotMod_enum_ovrdflg, KOUTP_MotMod_enum_ovrdval);

  /* End of Outputs for SubSystem: '<S687>/override_signal_m2 ' */

  /* MinMax: '<S688>/MinMax5' incorporates:
   *  Constant: '<S686>/_maxval'
   */
  VOUTP_MotMod_enum = rtb_MinMax5;
  if (VOUTP_MotMod_enum > KOUTP_MotMod_enum_maxval) {
    VOUTP_MotMod_enum = KOUTP_MotMod_enum_maxval;
  }

  /* MinMax: '<S688>/MinMax10' incorporates:
   *  Constant: '<S686>/_minval'
   */
  if (VOUTP_MotMod_enum < KOUTP_MotMod_enum_minval) {
    /* MinMax: '<S688>/MinMax5' incorporates:
     *  MinMax: '<S688>/MinMax10'
     */
    VOUTP_MotMod_enum = KOUTP_MotMod_enum_minval;
  }

  /* End of MinMax: '<S688>/MinMax10' */

  /* Outputs for Atomic SubSystem: '<S2>/LLC' */
  SWC_APP_type_LLC();

  /* End of Outputs for SubSystem: '<S2>/LLC' */

  /* Outputs for Atomic SubSystem: '<S671>/override_signal_m2 ' */
  /* Constant: '<S671>/_ovrdflg' incorporates:
   *  Constant: '<S671>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m
    (SWC_APP_type_ARID_DEF.BusCreator.VLLC_volfCooltFlowTar_C,
     KOUTP_volfCooltFlowTar_C_ovrdflg, KOUTP_volfCooltFlowTar_C_ovrdval);

  /* End of Outputs for SubSystem: '<S671>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S670>/_maxval'
   *  MinMax: '<S672>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_volfCooltFlowTar_C_maxval);

  /* MinMax: '<S672>/MinMax10' incorporates:
   *  Constant: '<S670>/_minval'
   */
  VOUTP_volfCooltFlowTar_C = fmaxf(rtb_SWT, KOUTP_volfCooltFlowTar_C_minval);

  /* Outputs for Atomic SubSystem: '<S667>/override_signal_m2 ' */
  /* Constant: '<S667>/_ovrdflg' incorporates:
   *  Constant: '<S667>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m
    (SWC_APP_type_ARID_DEF.BusCreator_c.VEOP_nEOPSpdReq_rpm,
     KOUTP_nEOPSpdReq_rpm_ovrdflg, KOUTP_nEOPSpdReq_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S667>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S666>/_maxval'
   *  MinMax: '<S668>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_nEOPSpdReq_rpm_maxval);

  /* MinMax: '<S668>/MinMax10' incorporates:
   *  Constant: '<S666>/_minval'
   */
  VOUTP_nEOPSpdReq_rpm = fmaxf(rtb_SWT, KOUTP_nEOPSpdReq_rpm_minval);

  /* Outputs for Atomic SubSystem: '<S663>/override_signal_m2 ' */
  /* Constant: '<S663>/_ovrdflg' incorporates:
   *  Constant: '<S663>/_ovrdval'
   */
  rtb_AND1_g2 = SWC_APP_type_override_signal_m2
    (SWC_APP_type_ARID_DEF.BusCreator_c.VEOP_bMotEnaReq_flg,
     KOUTP_bMotEnaReq_flg_ovrdflg, KOUTP_bMotEnaReq_flg_ovrdval);

  /* End of Outputs for SubSystem: '<S663>/override_signal_m2 ' */

  /* Logic: '<S741>/AND1' incorporates:
   *  Constant: '<S662>/_maxval'
   *  MinMax: '<S664>/MinMax5'
   */
  rtb_AND1_h = (rtb_AND1_g2 && KOUTP_bMotEnaReq_flg_maxval);

  /* MinMax: '<S664>/MinMax10' incorporates:
   *  Constant: '<S662>/_minval'
   */
  VOUTP_bMotEnaReq_flg = (rtb_AND1_h || KOUTP_bMotEnaReq_flg_minval);

  /* Outputs for Atomic SubSystem: '<S659>/override_signal_m2 ' */
  /* BusCreator: '<S3>/Bus Creator' incorporates:
   *  Constant: '<S659>/_ovrdflg'
   *  Constant: '<S659>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VCRM_PwrEleAct_W,
    KOUTP_PwrEleAct_W_ovrdflg, KOUTP_PwrEleAct_W_ovrdval);

  /* End of Outputs for SubSystem: '<S659>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S658>/_maxval'
   *  MinMax: '<S660>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_PwrEleAct_W_maxval);

  /* MinMax: '<S660>/MinMax10' incorporates:
   *  Constant: '<S658>/_minval'
   */
  VOUTP_PwrEleAct_W = fmaxf(rtb_SWT, KOUTP_PwrEleAct_W_minval);

  /* Outputs for Atomic SubSystem: '<S655>/override_signal_m2 ' */
  /* BusCreator: '<S3>/Bus Creator' incorporates:
   *  Constant: '<S655>/_ovrdflg'
   *  Constant: '<S655>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VCRM_BusCurr_A,
    KOUTP_BusCurr_A_ovrdflg, KOUTP_BusCurr_A_ovrdval);

  /* End of Outputs for SubSystem: '<S655>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S654>/_maxval'
   *  MinMax: '<S656>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_BusCurr_A_maxval);

  /* MinMax: '<S656>/MinMax10' incorporates:
   *  Constant: '<S654>/_minval'
   */
  VOUTP_BusCurr_A = fmaxf(rtb_SWT, KOUTP_BusCurr_A_minval);

  /* DataTypeConversion: '<S15>/Data Type Conversion' */
  VAPP_iDCurrAct_A =
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_iDCurrAct;

  /* DataTypeConversion: '<S15>/Data Type Conversion1' */
  VAPP_iQCurrAct_A =
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_CCM_iQCurrAct;

  /* DataTypeConversion: '<S15>/Data Type Conversion2' */
  VAPP_ADCKL30_V = SWC_APP_type_ARID_DEF.DataTypeConversion29;

  /* DataTypeConversion: '<S15>/Data Type Conversion3' */
  VAPP_ADCKL15_V = SWC_APP_type_ARID_DEF.DataTypeConversion32;

  /* DataTypeConversion: '<S15>/Data Type Conversion4' */
  VAPP_uDC_V =
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_DSS_uDCSide;

  /* DataTypeConversion: '<S15>/Data Type Conversion5' */
  VAPP_RotSpd_rpm =
    SWC_APP_type_ARID_DEF.TmpSignalConversionAtR_HiRateTx.f32_RotS_nRot;

  /* DataTypeConversion: '<S15>/Data Type Conversion6' */
  VAPP_OilTemp_degC = VFOC_ADCOilTemp_degC;

  /* Outputs for Atomic SubSystem: '<S635>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S635>/_ovrdflg'
   *  Constant: '<S635>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_OilTemp_degC,
    KOUTP_OilTemp_degC_ovrdflg, KOUTP_OilTemp_degC_ovrdval);

  /* End of Outputs for SubSystem: '<S635>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S634>/_maxval'
   *  MinMax: '<S636>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_OilTemp_degC_maxval);

  /* MinMax: '<S636>/MinMax10' incorporates:
   *  Constant: '<S634>/_minval'
   */
  VOUTP_OilTemp_degC = fmaxf(rtb_SWT, KOUTP_OilTemp_degC_minval);

  /* Outputs for Atomic SubSystem: '<S639>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S639>/_ovrdflg'
   *  Constant: '<S639>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_RotSpd_rpm,
    KOUTP_RotSpd_rpm_ovrdflg, KOUTP_RotSpd_rpm_ovrdval);

  /* End of Outputs for SubSystem: '<S639>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S638>/_maxval'
   *  MinMax: '<S640>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_RotSpd_rpm_maxval);

  /* MinMax: '<S640>/MinMax10' incorporates:
   *  Constant: '<S638>/_minval'
   */
  VOUTP_RotSpd_rpm = fmaxf(rtb_SWT, KOUTP_RotSpd_rpm_minval);

  /* Outputs for Atomic SubSystem: '<S651>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S651>/_ovrdflg'
   *  Constant: '<S651>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_uDC_V, KOUTP_uDC_V_ovrdflg,
    KOUTP_uDC_V_ovrdval);

  /* End of Outputs for SubSystem: '<S651>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S650>/_maxval'
   *  MinMax: '<S652>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_uDC_V_maxval);

  /* MinMax: '<S652>/MinMax10' incorporates:
   *  Constant: '<S650>/_minval'
   */
  VOUTP_uDC_V = fmaxf(rtb_SWT, KOUTP_uDC_V_minval);

  /* Outputs for Atomic SubSystem: '<S627>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S627>/_ovrdflg'
   *  Constant: '<S627>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_ADCKL15_V,
    KOUTP_ADCKL15_V_ovrdflg, KOUTP_ADCKL15_V_ovrdval);

  /* End of Outputs for SubSystem: '<S627>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S626>/_maxval'
   *  MinMax: '<S628>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_ADCKL15_V_maxval);

  /* MinMax: '<S628>/MinMax10' incorporates:
   *  Constant: '<S626>/_minval'
   */
  VOUTP_ADCKL15_V = fmaxf(rtb_SWT, KOUTP_ADCKL15_V_minval);

  /* Outputs for Atomic SubSystem: '<S631>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S631>/_ovrdflg'
   *  Constant: '<S631>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_ADCKL30_V,
    KOUTP_ADCKL30_V_ovrdflg, KOUTP_ADCKL30_V_ovrdval);

  /* End of Outputs for SubSystem: '<S631>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S630>/_maxval'
   *  MinMax: '<S632>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_ADCKL30_V_maxval);

  /* MinMax: '<S632>/MinMax10' incorporates:
   *  Constant: '<S630>/_minval'
   */
  VOUTP_ADCKL30_V = fmaxf(rtb_SWT, KOUTP_ADCKL30_V_minval);

  /* Outputs for Atomic SubSystem: '<S647>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S647>/_ovrdflg'
   *  Constant: '<S647>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_iQCurrAct_A,
    KOUTP_iQCurrAct_A_ovrdflg, KOUTP_iQCurrAct_A_ovrdval);

  /* End of Outputs for SubSystem: '<S647>/override_signal_m2 ' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Constant: '<S646>/_maxval'
   *  MinMax: '<S648>/MinMax5'
   */
  rtb_SWT = fminf(rtb_SWT, KOUTP_iQCurrAct_A_maxval);

  /* MinMax: '<S648>/MinMax10' incorporates:
   *  Constant: '<S646>/_minval'
   */
  VOUTP_iQCurrAct_A = fmaxf(rtb_SWT, KOUTP_iQCurrAct_A_minval);

  /* Outputs for Atomic SubSystem: '<S643>/override_signal_m2 ' */
  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  Constant: '<S643>/_ovrdflg'
   *  Constant: '<S643>/_ovrdval'
   */
  rtb_SWT = SWC_APP_ty_override_signal_m2_m(VAPP_iDCurrAct_A,
    KOUTP_iDCurrAct_A_ovrdflg, KOUTP_iDCurrAct_A_ovrdval);

  /* End of Outputs for SubSystem: '<S643>/override_signal_m2 ' */

  /* MinMax: '<S644>/MinMax10' incorporates:
   *  Constant: '<S642>/_maxval'
   *  Constant: '<S642>/_minval'
   *  MinMax: '<S644>/MinMax5'
   */
  VOUTP_iDCurrAct_A = fmaxf(fminf(rtb_SWT, KOUTP_iDCurrAct_A_maxval),
    KOUTP_iDCurrAct_A_minval);

  /* Chart: '<S7>/CAN_Scheduler' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/Constant2'
   */
  if (SWC_APP_type_ARID_DEF.is_active_c225_halout == 0U) {
    SWC_APP_type_ARID_DEF.is_active_c225_halout = 1U;
    if (KHAL_CAN_MCU_R1TxReq_flg) {
      /* Outputs for Function Call SubSystem: '<S7>/CAN_MCU_R1' */
      SWC_APP_type_CAN_MCU_R1(VOUTP_bMotEnaReq_flg, VOUTP_nEOPSpdReq_rpm,
        &SWC_APP_type_ARID_DEF.bus_creator_f);

      /* End of Outputs for SubSystem: '<S7>/CAN_MCU_R1' */
    }

    if (KHAL_CAN3TxReq_flg) {
      /* Outputs for Function Call SubSystem: '<S7>/CAN3' */
      SWC_APP_type_CAN3(VOUTP_PwrEleAct_W, VOUTP_BusCurr_A, VOUTP_uDC_V,
                        VOUTP_MCUEna_flg, VOUTP_TMReady_flg, VOUTP_tqTMTqMax_Nm,
                        VOUTP_tqTMTqMin_Nm, VOUTP_iDCurrAct_A, VOUTP_iQCurrAct_A,
                        VOUTP_MotMod_enum, VOUTP_volfCooltFlowTar_C,
                        VOUTP_BoostOPSta_flg, VOUTP_ADCKL30_V,
                        VOUTP_OilTemp_degC, VOUTP_RotSpd_rpm,
                        VOUTP_IVTROpMode_enum,
                        &SWC_APP_type_ARID_DEF.bus_creator_n,
                        &SWC_APP_type_ARID_DEF.bus_creator_j,
                        &SWC_APP_type_ARID_DEF.bus_creator_d,
                        &SWC_APP_type_ConstB.CAN3);

      /* End of Outputs for SubSystem: '<S7>/CAN3' */
    }
  } else {
    if (KHAL_CAN_MCU_R1TxReq_flg) {
      /* Outputs for Function Call SubSystem: '<S7>/CAN_MCU_R1' */
      SWC_APP_type_CAN_MCU_R1(VOUTP_bMotEnaReq_flg, VOUTP_nEOPSpdReq_rpm,
        &SWC_APP_type_ARID_DEF.bus_creator_f);

      /* End of Outputs for SubSystem: '<S7>/CAN_MCU_R1' */
    }

    if (KHAL_CAN3TxReq_flg) {
      /* Outputs for Function Call SubSystem: '<S7>/CAN3' */
      SWC_APP_type_CAN3(VOUTP_PwrEleAct_W, VOUTP_BusCurr_A, VOUTP_uDC_V,
                        VOUTP_MCUEna_flg, VOUTP_TMReady_flg, VOUTP_tqTMTqMax_Nm,
                        VOUTP_tqTMTqMin_Nm, VOUTP_iDCurrAct_A, VOUTP_iQCurrAct_A,
                        VOUTP_MotMod_enum, VOUTP_volfCooltFlowTar_C,
                        VOUTP_BoostOPSta_flg, VOUTP_ADCKL30_V,
                        VOUTP_OilTemp_degC, VOUTP_RotSpd_rpm,
                        VOUTP_IVTROpMode_enum,
                        &SWC_APP_type_ARID_DEF.bus_creator_n,
                        &SWC_APP_type_ARID_DEF.bus_creator_j,
                        &SWC_APP_type_ARID_DEF.bus_creator_d,
                        &SWC_APP_type_ConstB.CAN3);

      /* End of Outputs for SubSystem: '<S7>/CAN3' */
    }
  }

  /* End of Chart: '<S7>/CAN_Scheduler' */

  /* Constant: '<S12>/Constant' */
  VSYL_nTMSpdMin_RPM = KSYL_nTMSpdMin_RPM;

  /* Constant: '<S12>/Constant1' */
  VSYL_nTMSpdMax_RPM = KSYL_nTMSpdMax_RPM;

  /* Constant: '<S12>/Constant2' */
  VSYL_frqSwitchMax_Hz = KSYL_frqSwitchMax_Hz;

  /* RelationalOperator: '<S708>/Relational Operator1' incorporates:
   *  Abs: '<S708>/Abs'
   *  Constant: '<S708>/Constant35'
   *  UnitDelay: '<S2>/Unit Delay5'
   */
  rtb_LogicalOperator5 = (fabsf(SWC_APP_type_ARID_DEF.UnitDelay5_DSTATE) >=
    KDGL_nEOPSpdDiff_rpm);

  /* Outputs for Atomic SubSystem: '<S708>/TurnOnDelay_Dyn2' */
  /* Outputs for Atomic SubSystem: '<S717>/Rising' */
  rtb_AND1_h = SWC_APP_type_Rising(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising_l);

  /* End of Outputs for SubSystem: '<S717>/Rising' */

  /* Outputs for Atomic SubSystem: '<S717>/Delay' */
  rtb_UnitDelay_di = SWC_APP_type_Delay_m
    (&SWC_APP_type_ARID_DEF.ARID_DEF_Delay_d);

  /* End of Outputs for SubSystem: '<S717>/Delay' */

  /* Switch: '<S755>/SWT' */
  if (rtb_AND1_h) {
    /* Switch: '<S755>/SWT' incorporates:
     *  Constant: '<S717>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_e = 0.0F;
  } else {
    /* Switch: '<S755>/SWT' incorporates:
     *  Constant: '<S708>/Constant38'
     *  Sum: '<S753>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_e = rtb_UnitDelay_di + 1.0F;
  }

  /* End of Switch: '<S755>/SWT' */

  /* Switch: '<S754>/SWT' */
  if (rtb_LogicalOperator5) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S708>/Constant1'
     *  Sum: '<S752>/Sub1'
     */
    rtb_SWT = KDGL_tiDlyOnEOP_C - SWC_APP_type_ConstB.Gain1_ax;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S717>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S754>/SWT' */

  /* Outputs for Atomic SubSystem: '<S717>/Rising1' */
  /* Logic: '<S744>/AND1' incorporates:
   *  RelationalOperator: '<S745>/Relational Operator'
   */
  rtb_AND1_h = SWC_APP_type_Rising((rtb_LogicalOperator5 &&
    (SWC_APP_type_ARID_DEF.SWT_e >= rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_b);

  /* End of Outputs for SubSystem: '<S717>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S717>/Falling' */
  rtb_AND1_l = SWC_APP_type_Falling(rtb_LogicalOperator5,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_h);

  /* End of Outputs for SubSystem: '<S717>/Falling' */

  /* Outputs for Atomic SubSystem: '<S717>/ER_FF' */
  SWC_APP_type_ER_FF(rtb_AND1_h, rtb_AND1_l, &SWC_APP_type_ARID_DEF.SWT_fm,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_ER_FF_bn);

  /* End of Outputs for SubSystem: '<S717>/ER_FF' */

  /* Update for Atomic SubSystem: '<S717>/Delay' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_e,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay_d);

  /* End of Update for SubSystem: '<S717>/Delay' */
  /* End of Outputs for SubSystem: '<S708>/TurnOnDelay_Dyn2' */

  /* Outputs for Atomic SubSystem: '<S708>/TurnOffDelay_Dyn1' */
  /* Outputs for Atomic SubSystem: '<S716>/Falling1' */
  rtb_AND1_h = SWC_APP_type_Falling(SWC_APP_type_ARID_DEF.SWT_fm,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling1_j);

  /* End of Outputs for SubSystem: '<S716>/Falling1' */

  /* Outputs for Atomic SubSystem: '<S716>/Delay1' */
  rtb_UnitDelay_n2 = SWC_APP_type_Delay_m
    (&SWC_APP_type_ARID_DEF.ARID_DEF_Delay1_a);

  /* End of Outputs for SubSystem: '<S716>/Delay1' */

  /* Switch: '<S728>/SWT' */
  if (rtb_AND1_h) {
    /* Switch: '<S728>/SWT' incorporates:
     *  Constant: '<S716>/Constant1'
     */
    SWC_APP_type_ARID_DEF.SWT_es = 0.0F;
  } else {
    /* Switch: '<S728>/SWT' incorporates:
     *  Constant: '<S708>/Constant18'
     *  Sum: '<S727>/Sum1'
     */
    SWC_APP_type_ARID_DEF.SWT_es = rtb_UnitDelay_n2 + 1.0F;
  }

  /* End of Switch: '<S728>/SWT' */

  /* Switch: '<S729>/SWT' incorporates:
   *  Logic: '<S722>/NOT1'
   */
  if (!SWC_APP_type_ARID_DEF.SWT_fm) {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S708>/Constant20'
     *  Sum: '<S726>/Sub1'
     */
    rtb_SWT = KDGL_tiDlyOffEOP_C - SWC_APP_type_ConstB.Gain1_dw;
  } else {
    /* Switch: '<S729>/SWT' incorporates:
     *  Constant: '<S716>/Constant2'
     */
    rtb_SWT = 0.0F;
  }

  /* End of Switch: '<S729>/SWT' */

  /* Outputs for Atomic SubSystem: '<S716>/Falling' */
  /* Logic: '<S723>/OR1' incorporates:
   *  RelationalOperator: '<S730>/Relational Operator'
   */
  rtb_AND1_g2 = SWC_APP_type_Falling((SWC_APP_type_ARID_DEF.SWT_fm ||
    (SWC_APP_type_ARID_DEF.SWT_es < rtb_SWT)),
    &SWC_APP_type_ARID_DEF.ARID_DEF_Falling_fd);

  /* End of Outputs for SubSystem: '<S716>/Falling' */

  /* Outputs for Atomic SubSystem: '<S716>/Rising1' */
  rtb_AND1_h = SWC_APP_type_Rising(SWC_APP_type_ARID_DEF.SWT_fm,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Rising1_e);

  /* End of Outputs for SubSystem: '<S716>/Rising1' */

  /* Outputs for Atomic SubSystem: '<S716>/RE_FF' */
  SWC_APP_type_RE_FF(rtb_AND1_g2, rtb_AND1_h, &VDGL_DiagEOPSpdDiff_flg,
                     &SWC_APP_type_ARID_DEF.ARID_DEF_RE_FF_b);

  /* End of Outputs for SubSystem: '<S716>/RE_FF' */

  /* Update for Atomic SubSystem: '<S716>/Delay1' */
  SWC_APP_type_Delay_p_Update(SWC_APP_type_ARID_DEF.SWT_es,
    &SWC_APP_type_ARID_DEF.ARID_DEF_Delay1_a);

  /* End of Update for SubSystem: '<S716>/Delay1' */
  /* End of Outputs for SubSystem: '<S708>/TurnOffDelay_Dyn1' */

  /* CCaller: '<S14>/C Caller15' */
  calculate_all_adc_system_signal();

  /* Outputs for Atomic SubSystem: '<S2>/GateDirver_Temp_Read' */
  // SWC_APP_ty_GateDirver_Temp_Read();

  /* End of Outputs for SubSystem: '<S2>/GateDirver_Temp_Read' */

  /* Update for UnitDelay: '<S146>/Unit Delay' */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_n = 0U;

  /* Update for Delay: '<S149>/Delay' */
  for (i = 0; i < 15; i++) {
    SWC_APP_type_ARID_DEF.Delay_DSTATE[i] = rtb_DataTypeConversion3_p[i];
  }

  /* End of Update for Delay: '<S149>/Delay' */

  /* Update for Delay: '<S149>/Delay1' incorporates:
   *  Constant: '<S149>/Constant'
   */
  SWC_APP_type_ARID_DEF.Delay1_DSTATE = true_MatlabRTW;

  /* Update for UnitDelay: '<S146>/Unit Delay3' incorporates:
   *  Constant: '<S146>/Constant7'
   */
  SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_j = true_MatlabRTW;

  /* Update for UnitDelay: '<S164>/Unit Delay' */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_h = 0U;

  /* Update for Delay: '<S167>/Delay' */
  for (i = 0; i < 11; i++) {
    SWC_APP_type_ARID_DEF.Delay_DSTATE_o[i] = rtb_DataTypeConversion3[i];
  }

  /* End of Update for Delay: '<S167>/Delay' */

  /* Update for Delay: '<S167>/Delay1' incorporates:
   *  Constant: '<S167>/Constant'
   */
  SWC_APP_type_ARID_DEF.Delay1_DSTATE_o = true_MatlabRTW;

  /* Update for UnitDelay: '<S164>/Unit Delay3' incorporates:
   *  Constant: '<S164>/Constant7'
   */
  SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_a = true_MatlabRTW;

  /* Update for UnitDelay: '<S33>/Unit Delay3' incorporates:
   *  UnitDelay: '<S33>/Unit Delay4'
   */
  SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE =
    SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE;

  /* Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
  SWC_APP_type_ARID_DEF.DiscreteTimeIntegrator_DSTATE += rtb_Prelookup_o2;
  SWC_APP_type_ARID_DEF.DiscreteTimeIntegrator_PrevRese = (sint8)
    DiagM_bOver2Stop;

  /* Update for UnitDelay: '<S2>/Unit Delay2' */
  SWC_APP_type_ARID_DEF.UnitDelay2_DSTATE = VCRM_IdCmd_A;

  /* Update for UnitDelay: '<S2>/Unit Delay4' */
  SWC_APP_type_ARID_DEF.UnitDelay4_DSTATE_h = VSYL_tqTMTqMax_Nm;

  /* Update for UnitDelay: '<S2>/Unit Delay3' */
  SWC_APP_type_ARID_DEF.UnitDelay3_DSTATE_d = VSYL_tqTMTqMin_Nm;

  /* Update for UnitDelay: '<S14>/Unit Delay' incorporates:
   *  Constant: '<S14>/Constant'
   */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_p = true_MatlabRTW;

  /* Update for UnitDelay: '<S30>/Unit Delay' */
  SWC_APP_type_ARID_DEF.UnitDelay_DSTATE_i = VCRM_IqCmd_A;

  /* Update for UnitDelay: '<S2>/Unit Delay5' */
  SWC_APP_type_ARID_DEF.UnitDelay5_DSTATE = 0.0F;

  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/run_SWC_APP' */

  /* Outport: '<Root>/P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R1' */
  SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R =
    SWC_APP_type_ARID_DEF.bus_creator_n;

  /* Outport: '<Root>/P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R2' */
  SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R =
    SWC_APP_type_ARID_DEF.bus_creator_j;

  /* Outport: '<Root>/P_LoRateTxHiRateRx_LoRateTxHiRateRx' */
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.u8_OpMod_stMotAct =
    message;
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.u8_OpMod_stIvtrTar =
    rtb_BitwiseOR1;
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.f32_SysLim_frqSwitchMax =
    0.0F;
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.f32_VMCM_IdCmd_A =
    rtb_TrqMax;
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.f32_VMCM_IqCmd_A =
    rtb_Prelookup1_o2_n;
  SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa.u8_VDSM_FltActn22_flg =
    rtb_BitwiseOR;

  /* Outport: '<Root>/P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_FVT_R1' */
  SWC_APP_type_ARID_DEF.P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_F =
    SWC_APP_type_ARID_DEF.bus_creator_d;

  /* Outport: '<Root>/P_CAN_MCU_R1_MCU_FVT_R_Local1_CAN_MCU_R1_SG_MCU_FVT_R_Local1' */
  SWC_APP_type_ARID_DEF.P_CAN_MCU_R1_MCU_FVT_R_Local1_C =
    SWC_APP_type_ARID_DEF.bus_creator_f;
  (void)Rte_Write_P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R1
    (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R);
  (void)Rte_Write_P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R2
    (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R);
  (void)Rte_Write_P_LoRateTxHiRateRx_LoRateTxHiRateRx
    (&SWC_APP_type_ARID_DEF.P_LoRateTxHiRateRx_LoRateTxHiRa);
  (void)Rte_Write_P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_FVT_R1
    (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_F);
  (void)Rte_Write_P_CAN_MCU_R1_MCU_FVT_R_Local1_CAN_MCU_R1_SG_MCU_FVT_R_Local1
    (&SWC_APP_type_ARID_DEF.P_CAN_MCU_R1_MCU_FVT_R_Local1_C);
}

/* Model initialize function */
void SWC_APP_type_Init(void)
{
  {
    /* local block i/o variables */
    float32 rtb_OutputCoef;
    boolean rtb_Status;
    boolean rtb_Status_l;
    boolean rtb_Status_j;
    boolean rtb_Status_b;
    boolean rtb_Status_b2;
    boolean rtb_Status_d;
    boolean rtb_Status_k;
    boolean rtb_Status_f;
    boolean rtb_Status_c;
    boolean rtb_Status_h;
    boolean rtb_Status_ci;
    boolean rtb_Status_la;
    boolean rtb_Status_g;

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/run_SWC_APP' incorporates:
     *  SubSystem: '<Root>/run_SWC_APP_sys'
     */
    /* SystemInitialize for Chart: '<S777>/Chart' incorporates:
     *  SubSystem: '<S777>/Function-Call Subsystem'
     */
    /* SystemInitialize for Atomic SubSystem: '<S782>/debounce' */
    SWC_APP_type_debounce_Init(&rtb_Status_g);

    /* End of SystemInitialize for SubSystem: '<S782>/debounce' */

    /* SystemInitialize for SignalConversion: '<S782>/Signal Conversion' */
    VDGL_HVLowErr_flg = rtb_Status_g;

    /* SystemInitialize for Atomic SubSystem: '<S782>/debounce1' */
    SWC_APP_type_debounce_Init(&rtb_Status_la);

    /* End of SystemInitialize for SubSystem: '<S782>/debounce1' */

    /* SystemInitialize for SignalConversion: '<S782>/Signal Conversion1' */
    VDGL_HVLowWarn_flg = rtb_Status_la;

    /* SystemInitialize for Atomic SubSystem: '<S777>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef_p);

    /* End of SystemInitialize for SubSystem: '<S777>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S778>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef_m);

    /* End of SystemInitialize for SubSystem: '<S778>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S778>/Derating_Reverse' */
    Derating_Reverse_Init(&SWC_APP_type_ARID_DEF.Coef_d);

    /* End of SystemInitialize for SubSystem: '<S778>/Derating_Reverse' */

    /* SystemInitialize for Atomic SubSystem: '<S778>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S791>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_ci);

    /* End of SystemInitialize for SubSystem: '<S791>/debounce' */

    /* SystemInitialize for Atomic SubSystem: '<S791>/debounce1' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_h);

    /* End of SystemInitialize for SubSystem: '<S791>/debounce1' */
    /* End of SystemInitialize for SubSystem: '<S778>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S712>/Coef_Decrease_Increase' */
    Coef_Decrease_Increase_Init(&rtb_OutputCoef,
      &SWC_APP_type_ARID_DEF.ARID_DEF_Coef_Decrease_Increas);

    /* End of SystemInitialize for SubSystem: '<S712>/Coef_Decrease_Increase' */

    /* SystemInitialize for Atomic SubSystem: '<S712>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S800>/Hysteresis_Ctrl_Forward' */
    Hysteresis_Ctrl_Forward_Init(&SWC_APP_type_ARID_DEF.enable);

    /* End of SystemInitialize for SubSystem: '<S800>/Hysteresis_Ctrl_Forward' */

    /* SystemInitialize for Atomic SubSystem: '<S800>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_c);

    /* End of SystemInitialize for SubSystem: '<S800>/debounce' */
    /* End of SystemInitialize for SubSystem: '<S712>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S807>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef_n);

    /* End of SystemInitialize for SubSystem: '<S807>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S807>/Derating_Reverse' */
    Derating_Reverse_Init(&SWC_APP_type_ARID_DEF.Coef_i);

    /* End of SystemInitialize for SubSystem: '<S807>/Derating_Reverse' */

    /* SystemInitialize for Atomic SubSystem: '<S807>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S816>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_f);

    /* End of SystemInitialize for SubSystem: '<S816>/debounce' */

    /* SystemInitialize for Atomic SubSystem: '<S817>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_k);

    /* End of SystemInitialize for SubSystem: '<S817>/debounce' */
    /* End of SystemInitialize for SubSystem: '<S807>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S808>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef_f);

    /* End of SystemInitialize for SubSystem: '<S808>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S808>/Derating_Reverse' */
    Derating_Reverse_Init(&SWC_APP_type_ARID_DEF.Coef_l);

    /* End of SystemInitialize for SubSystem: '<S808>/Derating_Reverse' */

    /* SystemInitialize for Atomic SubSystem: '<S808>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S824>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_d);

    /* End of SystemInitialize for SubSystem: '<S824>/debounce' */

    /* SystemInitialize for Atomic SubSystem: '<S824>/debounce1' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_b2);

    /* End of SystemInitialize for SubSystem: '<S824>/debounce1' */
    /* End of SystemInitialize for SubSystem: '<S808>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S809>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef_l);

    /* End of SystemInitialize for SubSystem: '<S809>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S809>/Derating_Reverse' */
    Derating_Reverse_Init(&SWC_APP_type_ARID_DEF.Coef_k);

    /* End of SystemInitialize for SubSystem: '<S809>/Derating_Reverse' */

    /* SystemInitialize for Atomic SubSystem: '<S809>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S833>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_b);

    /* End of SystemInitialize for SubSystem: '<S833>/debounce' */

    /* SystemInitialize for Atomic SubSystem: '<S833>/debounce1' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_j);

    /* End of SystemInitialize for SubSystem: '<S833>/debounce1' */
    /* End of SystemInitialize for SubSystem: '<S809>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S810>/CoefSmooth' */
    CoefSmooth_Init(&SWC_APP_type_ARID_DEF.OutputCoef);

    /* End of SystemInitialize for SubSystem: '<S810>/CoefSmooth' */

    /* SystemInitialize for Atomic SubSystem: '<S810>/Function-Call Subsystem' */
    /* SystemInitialize for Atomic SubSystem: '<S841>/debounce' */
    SWC_APP_type_debounce_m_Init(&rtb_Status_l);

    /* End of SystemInitialize for SubSystem: '<S841>/debounce' */

    /* SystemInitialize for Atomic SubSystem: '<S841>/debounce1' */
    SWC_APP_type_debounce_m_Init(&rtb_Status);

    /* End of SystemInitialize for SubSystem: '<S841>/debounce1' */
    /* End of SystemInitialize for SubSystem: '<S810>/Function-Call Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S810>/Temp_Derating_Reverse' */
    Derating_Reverse_Init(&SWC_APP_type_ARID_DEF.Coef);

    /* End of SystemInitialize for SubSystem: '<S810>/Temp_Derating_Reverse' */
    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/run_SWC_APP' */

    /* SystemInitialize for Outport: '<Root>/P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R1' incorporates:
     *  BusCreator: '<S230>/bus_creator'
     */
    SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R =
      SWC_APP_type_ARID_DEF.bus_creator_n;

    /* SystemInitialize for Outport: '<Root>/P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R2' incorporates:
     *  BusCreator: '<S231>/bus_creator'
     */
    SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R =
      SWC_APP_type_ARID_DEF.bus_creator_j;

    /* SystemInitialize for Outport: '<Root>/P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_FVT_R1' incorporates:
     *  BusCreator: '<S232>/bus_creator'
     */
    SWC_APP_type_ARID_DEF.P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_F =
      SWC_APP_type_ARID_DEF.bus_creator_d;

    /* SystemInitialize for Outport: '<Root>/P_CAN_MCU_R1_MCU_FVT_R_Local1_CAN_MCU_R1_SG_MCU_FVT_R_Local1' incorporates:
     *  BusCreator: '<S307>/bus_creator'
     */
    SWC_APP_type_ARID_DEF.P_CAN_MCU_R1_MCU_FVT_R_Local1_C =
      SWC_APP_type_ARID_DEF.bus_creator_f;
    (void)Rte_Write_P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R1
      (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R1_CAN3_SG_MCU_B_R);
    (void)Rte_Write_P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R2
      (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_B_R2_CAN3_SG_MCU_B_R);
    (void)Rte_Write_P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_FVT_R1
      (&SWC_APP_type_ARID_DEF.P_CAN3_MCU_FVT_R1_CAN3_SG_MCU_F);
    (void)Rte_Write_P_CAN_MCU_R1_MCU_FVT_R_Local1_CAN_MCU_R1_SG_MCU_FVT_R_Local1
      (&SWC_APP_type_ARID_DEF.P_CAN_MCU_R1_MCU_FVT_R_Local1_C);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
