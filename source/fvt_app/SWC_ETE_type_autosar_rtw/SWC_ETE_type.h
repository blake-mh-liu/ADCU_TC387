/*
 * File: SWC_ETE_type.h
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

#ifndef SWC_ETE_type_h_
#define SWC_ETE_type_h_
#ifndef SWC_ETE_type_COMMON_INCLUDES_
#define SWC_ETE_type_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_SWC_ETE_type.h"
#endif                                 /* SWC_ETE_type_COMMON_INCLUDES_ */

#include "SWC_ETE_type_types.h"
#include "FVTMC_API.h"
#include "PDC.h"
#include "Rte_Type.h"
#include "MTPA_FOC.h"
#include "rt_sys_rt_sys_CCM_FVT_38_36.h"
#include "rt_sys_CCM_FVT_38.h"
#include "CCM_FVT.h"
#include "rt_sys_ADC_RDC_Read_0.h"
#include "ADC_RDC_Read.h"

/* PublicStructure Variables for Internal Data, for system '<Root>' */
typedef struct {
  ARID_DEF_debounce_SWC_ETE_typ_T ARID_DEF_debounce;/* '<S113>/debounce' */
  ARID_DEF_Delay_SWC_ETE_type_n_T ARID_DEF_Delay;/* '<S150>/Delay' */
  ARID_DEF_Delay_SWC_ETE_type_n_T ARID_DEF_Delay_m;/* '<S149>/Delay' */
  ARID_DEF_Delay_SWC_ETE_type_n_T ARID_DEF_Delay_c;/* '<S148>/Delay' */
  ARID_DEF_Delay_SWC_ETE_type_n_T ARID_DEF_Delay_k;/* '<S147>/Delay' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF5;/* '<S6>/ER_FF5' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF4;/* '<S6>/ER_FF4' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF3;/* '<S6>/ER_FF3' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF2;/* '<S6>/ER_FF2' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF1;/* '<S6>/ER_FF1' */
  ARID_DEF_debounce_SWC_ETE_typ_T ARID_DEF_debounce_c;/* '<S115>/debounce' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF1_b;/* '<S115>/ER_FF1' */
  ARID_DEF_Rising_SWC_ETE_type_T ARID_DEF_Rising1;/* '<S58>/Rising1' */
  ARID_DEF_Rising_SWC_ETE_type_T ARID_DEF_Rising;/* '<S58>/Rising' */
  ARID_DEF_Delay_SWC_ETE_type_c_T ARID_DEF_Delay_p;/* '<S71>/Delay' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF;/* '<S58>/ER_FF' */
  ARID_DEF_Delay_SWC_ETE_type_T ARID_DEF_Delay_cv;/* '<S58>/Delay' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF1_f;/* '<S47>/ER_FF1' */
  ARID_DEF_ER_FF_SWC_ETE_type_T ARID_DEF_ER_FF_g;/* '<S47>/ER_FF' */
  ARID_DEF_First_Order_Filter_T ARID_DEF_First_Order_Filter;/* '<S20>/First_Order_Filter' */
  ARID_DEF_Delay_SWC_ETE_type_T ARID_DEF_Delay_g;/* '<S18>/Delay' */
  DT_HiRateTxLoRateRx BusCreator;      /* '<S3>/Bus Creator' */
  DT_HiRateTxLoRateRx P_HiRateTxLoRateRx_HiRateTxLoRa;
                              /* '<Root>/P_HiRateTxLoRateRx_HiRateTxLoRateRx' */
  float32 Switch2[3];                  /* '<S186>/Switch2' */
  float32 ActDuty[3];                  /* '<S220>/ASC2' */
  float32 UnitDelay_DSTATE_mh[3];      /* '<S25>/Unit Delay' */
  float32 Switch1;                     /* '<S3>/Switch1' */
  float32 VFOC_PosnOffset_rad;         /* '<S263>/Abs' */
  float32 Product1;                    /* '<S212>/Product1' */
  float32 Product2;                    /* '<S212>/Product2' */
  float32 CCM_IqCmd;                   /* '<S43>/Switch1' */
  float32 SWT;                         /* '<S78>/SWT' */
  float32 intVd;                       /* '<S52>/Ramp' */
  float32 intVq;                       /* '<S52>/Ramp' */
  float32 Sum1;                        /* '<S24>/Sum1' */
  float32 CCM_IdCmd;                   /* '<S43>/Switch3' */
  float32 Integraldelay3_DSTATE;       /* '<S94>/Integral delay3' */
  float32 Integraldelay3_DSTATE_b;     /* '<S95>/Integral delay3' */
  float32 UnitDelay_DSTATE_j;          /* '<S20>/Unit Delay' */
  float32 UnitDelay_DSTATE_p0;         /* '<S32>/Unit Delay' */
  float32 deltaVq;                     /* '<S52>/Ramp' */
  float32 deltaVd;                     /* '<S52>/Ramp' */
  uint16 UnitDelay_DSTATE_mq;          /* '<S27>/Unit Delay' */
  sint8 If_ActiveSubsystem;            /* '<S185>/If' */
  uint8 Switch2_o;                     /* '<S3>/Switch2' */
  uint8 Counter;                       /* '<S220>/ASC2' */
  uint8 is_active_c1_pdc_grc;          /* '<S184>/SS_SafetyShutdown_Ctrl' */
  uint8 is_c1_pdc_grc;                 /* '<S184>/SS_SafetyShutdown_Ctrl' */
  boolean Equal3;                      /* '<S15>/Equal3' */
  boolean SWT_d;                       /* '<S125>/SWT' */
  boolean SWT_dw;                      /* '<S82>/SWT' */
  boolean enASC_flg;                   /* '<S52>/Ramp' */
  boolean DelayInput1_DSTATE;          /* '<S260>/Delay Input1' */
  boolean DelayInput1_DSTATE_h;        /* '<S8>/Delay Input1' */
  boolean DelayInput1_DSTATE_j;        /* '<S9>/Delay Input1' */
  boolean UnitDelay_DSTATE_c;          /* '<S3>/Unit Delay' */
  boolean DelayInput1_DSTATE_i;        /* '<S7>/Delay Input1' */
  boolean DelayInput1_DSTATE_f;        /* '<S117>/Delay Input1' */
  boolean DelayInput1_DSTATE_n;        /* '<S118>/Delay Input1' */
  boolean DelayInput1_DSTATE_m;        /* '<S119>/Delay Input1' */
  boolean UnitDelay1_DSTATE_k;         /* '<S27>/Unit Delay1' */
} ARID_DEF_SWC_ETE_type_T;

/* Invariant block signals (default storage) */
typedef struct {
  const EvAdc_SignalDataType_Fake TmpSignalConversionAtCCalle[3];
  const float32 DataTypeConversion;    /* '<S3>/Data Type Conversion' */
  const float32 Gain1;                 /* '<S190>/Gain1' */
  const boolean RelationalOperator;    /* '<S187>/Relational Operator' */
  const boolean RelationalOperator1;   /* '<S187>/Relational Operator1' */
  const boolean LogicalOperator;       /* '<S187>/Logical Operator' */
  const boolean RelationalOperator1_h; /* '<S189>/Relational Operator1' */
  ConstB_SetSVMR_SmartClamps_Ph_T SetSVMR_SmartClamps_PhsC;/* '<S190>/SetSVMR_SmartClamps_PhsC' */
  ConstB_SetSVMR_SmartClamps_Ph_T SetSVMR_SmartClamps_PhsB;/* '<S190>/SetSVMR_SmartClamps_PhsB' */
  ConstB_SetSVMR_SmartClamps_Ph_T SetSVMR_SmartClamps_PhsA;/* '<S190>/SetSVMR_SmartClamps_PhsA' */
} ConstB_SWC_ETE_type_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S48>/LdMapp'
   *   '<S48>/LqMapp'
   */
  uint32 pooled20[2];
} ConstP_SWC_ETE_type_T;

/* PublicStructure Variables for Internal Data */
extern ARID_DEF_SWC_ETE_type_T SWC_ETE_type_ARID_DEF;
extern const ConstB_SWC_ETE_type_T SWC_ETE_type_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_SWC_ETE_type_T SWC_ETE_type_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint32 VROT_FreqPWM_Tick;       /* '<S31>/Data Type Conversion' */
extern float32 VFOC_RotorPosnOffset_rad;/* '<S15>/Switch' */
extern float32 VFOC_FakeRotorPosn_rad; /* '<S262>/Switch' */
extern float32 VPDC_DutyA_raw;         /* '<S171>/Data Type Conversion1' */
extern float32 VPDC_DutyB_raw;         /* '<S171>/Data Type Conversion2' */
extern float32 VPDC_DutyC_raw;         /* '<S171>/Data Type Conversion4' */
extern float32 VFOC_VcmdAlpha_V;       /* '<S12>/Data Type Conversion' */
extern float32 VFOC_VcmdBeta_V;        /* '<S12>/Data Type Conversion1' */
extern float32 VDGH_SumErrPhCurU_A;    /* '<S115>/Switch2' */
extern float32 VDGH_SumErrPhCurW_A;    /* '<S115>/Switch4' */
extern float32 VDGH_SumErrPhCurV_A;    /* '<S115>/Switch6' */
extern float32 VCCM_iDCurrAct_A;       /* '<S54>/Add' */
extern float32 VMCM_VdFwd_V;           /* '<S48>/Gain3' */
extern float32 VCCM_VdRef_V;           /* '<S94>/Add5' */
extern float32 VCCM_iQCurrAct_A;       /* '<S55>/Add' */
extern float32 VMCM_VqFwd_V;           /* '<S48>/Gain2' */
extern float32 VCCM_VqRef_V;           /* '<S95>/Add5' */
extern float32 VCCM_DcHiBatLim_V;      /* '<S50>/Saturation1' */
extern float32 VCCM_VdCmd_V;           /* '<S50>/Switch' */
extern float32 VCCM_VqCmd_V;           /* '<S50>/Switch1' */
extern float32 VCCM_uASCVd_V;          /* '<S44>/Merge' */
extern float32 VCCM_uASCVq_V;          /* '<S44>/Merge1' */
extern float32 VCCM_uAlphaVoltTar_V;   /* '<S46>/Fcn' */
extern float32 VCCM_uBetaVoltTar_V;    /* '<S46>/Fcn1' */
extern float32 VMCM_TqAct_Nm;          /* '<S48>/Product10' */
extern float32 VMCM_TqEst_Nm;          /* '<S48>/Product7' */
extern float32 VCCM_VcmdBfLim_V;       /* '<S97>/Add' */
extern float32 VCCM_BattVolCirRadius_V;/* '<S98>/Add' */
extern float32 VCCM_VoltUtilize_pu;    /* '<S50>/Product6' */
extern float32 VFOC_iARaw_raw;         /* '<S4>/Data Type Conversion1' */
extern float32 VFOC_iBRaw_raw;         /* '<S4>/Data Type Conversion2' */
extern float32 VFOC_iCRaw_raw;         /* '<S4>/Data Type Conversion3' */
extern float32 VPCS_PhaWCur_A;         /* '<S19>/Product' */
extern float32 VPCS_PhaVCur_A;         /* '<S19>/Product1' */
extern float32 VPCS_PhaUCur_A;         /* '<S19>/Product3' */
extern float32 VPCS_MaxPhaCurW_A;      /* '<S26>/Switch7' */
extern float32 VPCS_MaxPhaCurU_A;      /* '<S26>/Switch3' */
extern float32 VPCS_MaxPhaCur_A;       /* '<S26>/Switch1' */
extern float32 VPCS_MaxPhaCurV_A;      /* '<S26>/Switch5' */
extern float32 VFOC_DCBusRAW_V;        /* '<S4>/Data Type Conversion5' */
extern float32 VFOC_DCBusVoltage_V;    /* '<S4>/Switch3' */
extern float32 VROT_RotSpdERaw_rads;   /* '<S20>/Data Type Conversion2' */
extern float32 VROT_RotSpdM_rpm;       /* '<S20>/First_Order_Filter' */
extern float32 VROT_RotAgECompL_rad;   /* '<S20>/Add1' */
extern float32 VROT_RotAngleERaw_rad;  /* '<S20>/Data Type Conversion1' */
extern float32 VROT_RotAngleE_rad;     /* '<S34>/Switch1' */
extern float32 VROT_RotSpdE_rads;      /* '<S20>/Signal Conversion' */
extern float32 VROT_RotAgECompV_rad;   /* '<S20>/Product1' */
extern float32 VROT_RotAngleV_rad;     /* '<S33>/Switch1' */
extern float32 VPCS_WCurOffsFil_V;     /* '<S28>/Switch' */
extern float32 VPCS_VCurOffsFil_V;     /* '<S28>/Switch1' */
extern float32 VPCS_UCurOffsFil_V;     /* '<S28>/Switch2' */
extern float32 VPCS_WCurOffsRaw_V;     /* '<S25>/Data Type Conversion' */
extern float32 VPCS_VCurOffsRaw_V;     /* '<S25>/Data Type Conversion1' */
extern float32 VPCS_UCurOffsRaw_V;     /* '<S25>/Data Type Conversion3' */
extern uint8 VPDC_Ivtr1ModCmd_enum;    /* '<S185>/Merge2' */
extern boolean VDGH_RteFault_flg;      /* '<S6>/Logical Operator1' */
extern boolean VDGH_100usFaultLevel2_flg;/* '<S6>/bsw_bPosSenrFaultswt' */
extern boolean VDGH_FaultLevel2_flg;   /* '<S6>/Logical Operator2' */
extern boolean VDGH_CurOffsErrLat_flg; /* '<S6>/Logical Operator9' */
extern boolean VPDC_bASCFlgRaw_flg;    /* '<S171>/Logical Operator' */
extern boolean VDGH_OverCurrent_flg;   /* '<S113>/ESM_bMcuShtDwnAllwdswt' */
extern boolean VDGH_PhaCurrOverDQ_flg; /* '<S167>/SWT' */
extern boolean VDGH_PhaCurrOverW_flg;  /* '<S163>/SWT' */
extern boolean VDGH_PhaCurrOverV_flg;  /* '<S159>/SWT' */
extern boolean VDGH_PhaCurrOverU_flg;  /* '<S155>/SWT' */
extern boolean VDGH_HWOverVoltFltLat_flg;/* '<S146>/SWT' */
extern boolean VDGH_HWLsideFltLat_flg; /* '<S142>/SWT' */
extern boolean VDGH_HWHsideFltLat_flg; /* '<S138>/SWT' */
extern boolean VDGH_PosSenrFaultLat_flg;/* '<S134>/SWT' */
extern boolean VDGH_CurrFaultLat_flg;  /* '<S130>/SWT' */
extern boolean VDGH_SumErr_flg;        /* '<S115>/SumErr_Outswt' */
extern boolean VCCM_bASCEna_flg;       /* '<S44>/Merge2' */
extern boolean VCCM_CurErrorOverThd2_flg;/* '<S66>/SWT' */
extern boolean VCCM_CurErrorOverThd_flg;/* '<S62>/SWT' */
extern boolean VPCS_EnaSnsrSelfLrn_flg;/* '<S27>/Switch1' */
extern boolean VPCS_SnsrSelfLrnCompl_flg;/* '<S19>/Logical Operator' */
extern boolean VPCS_WCurOffsVolVld_flg;/* '<S28>/Signal Conversion2' */
extern boolean VPCS_VCurOffsVolVld_flg;/* '<S28>/Signal Conversion' */
extern boolean VPCS_UCurOffsVolVld_flg;/* '<S28>/Signal Conversion1' */
extern boolean VPCS_bCurOffsVolVld_flg;/* '<S28>/PCS_bCurOffsVolVld_flgswt' */

/* Exported data declaration */
#define SWC_ETE_type_START_SEC_CAL
#include "SWC_ETE_type_MemMap.h"

/* Declaration for custom storage class: Global */
extern float32 ACCM_IdKp_X_rpm[20];    /* Referenced by:
                                        * '<S92>/MCCM_IdKp_value'
                                        * '<S93>/MCCM_IqKp_value'
                                        */
extern float32 ACCM_facCCMLq_X_A[36];  /* Referenced by:
                                        * '<S48>/LdMapp'
                                        * '<S48>/LqMapp'
                                        */
extern float32 ACCM_facCCMLq_Y_A[36];  /* Referenced by:
                                        * '<S48>/LdMapp'
                                        * '<S48>/LqMapp'
                                        */
extern float32 ACCM_facLPFiDAct_X_rpm[11];/* Referenced by:
                                           * '<S45>/CCM_facLPFiDAct_T1'
                                           * '<S45>/CCM_facLPFiQAct_T1'
                                           */
extern float32 AROT_ParkCompAngle_X_rpm[20];/* Referenced by:
                                             * '<S20>/1-D Lookup Table'
                                             * '<S20>/1-D Lookup Table2'
                                             */
extern float32 KCCM_BattVolFilTi_fac;  /* Referenced by:
                                        * '<S97>/Constant'
                                        * '<S98>/Constant'
                                        */
extern float32 KCCM_CurLoopPrd_t;      /* Referenced by:
                                        * '<S92>/TM_Prd'
                                        * '<S93>/TM_Prd'
                                        */
extern float32 KCCM_FwdMask_c;         /* Referenced by:
                                        * '<S92>/Constant2'
                                        * '<S93>/Constant2'
                                        */
extern float32 KCCM_IdKi_null;         /* Referenced by: '<S92>/TM_Id_Ki' */
extern float32 KCCM_IdKt_null;         /* Referenced by: '<S92>/TM_Id_Kt' */
extern float32 KCCM_IqKi_null;         /* Referenced by: '<S93>/TM_Id_Ki' */
extern float32 KCCM_IqKt_null;         /* Referenced by: '<S93>/TM_Id_Kt' */
extern boolean KCCM_UdqASCEna_C;       /* Referenced by: '<S44>/Constant2' */
extern float32 KCCM_UdqASCTagValue_C;  /* Referenced by: '<S52>/Constant3' */
extern float32 KCCM_UdqASCTimesValue_C;/* Referenced by: '<S52>/Constant1' */
extern boolean KCCM_VdSpSwEna_flg;     /* Referenced by: '<S50>/ReciSqrt3M3' */
extern float32 KCCM_VdSp_V;            /* Referenced by: '<S50>/ReciSqrt3M1' */
extern float32 KCCM_VolMod_perc;       /* Referenced by: '<S50>/ReciSqrt3M' */
extern float32 KCCM_VqSp_V;            /* Referenced by: '<S50>/ReciSqrt3M2' */
extern boolean KCCM_bRstCurErrorOverThd_C;/* Referenced by: '<S47>/Constant7' */
extern float32 KCCM_tiCurErrOvr_C;     /* Referenced by: '<S47>/Constant2' */
extern boolean KDGH_FaultLevel2_flg_ovrdflg;
                             /* Referenced by: '<S6>/bsw_bPosSenrFaultTrig_C' */
extern boolean KDGH_FaultLevel2_flg_ovrdval;
                              /* Referenced by: '<S6>/bsw_bPosSenrFaultMor_C' */
extern sint16 KDGH_OverCurrentErr_C;   /* Referenced by: '<S113>/Constant2' */
extern sint16 KDGH_OverCurrentHeal_C;  /* Referenced by: '<S113>/Constant1' */
extern float32 KDGH_OverCurrent_A;     /* Referenced by: '<S113>/Constant' */
extern boolean KDGH_OverCurrent_flg_ovrdflg;
                         /* Referenced by: '<S113>/ESM_bMcuShtDwnAllwdTrig_C' */
extern boolean KDGH_OverCurrent_flg_ovrdval;
                          /* Referenced by: '<S113>/ESM_bMcuShtDwnAllwdMor_C' */
extern float32 KDGH_PhaCurrOverU_A;    /* Referenced by: '<S113>/Constant3' */
extern float32 KDGH_PhaCurrOverV_A;    /* Referenced by: '<S113>/Constant4' */
extern float32 KDGH_PhaCurrOverW_A;    /* Referenced by: '<S113>/Constant5' */
extern boolean KDGH_RstPhaCurrOver_flg;/* Referenced by:
                                        * '<S113>/Constant12'
                                        * '<S113>/Constant13'
                                        * '<S113>/Constant7'
                                        * '<S113>/Constant8'
                                        */
extern boolean KDGH_RstSumErr_flg;     /* Referenced by: '<S115>/Constant8' */
extern sint16 KDGH_SumErrErr_C;        /* Referenced by: '<S115>/Constant2' */
extern sint16 KDGH_SumErrHeal_C;       /* Referenced by: '<S115>/Constant1' */
extern float32 KDGH_SumErr_A;          /* Referenced by: '<S115>/Constant' */
extern boolean KDGH_SumErr_flg_ovrdflg;
                                  /* Referenced by: '<S115>/SumErr_OutTrig_C' */
extern boolean KDGH_SumErr_flg_ovrdval;
                                   /* Referenced by: '<S115>/SumErr_OutMor_C' */
extern boolean KDGH_bRstRteFault_flg;  /* Referenced by: '<S6>/Constant8' */
extern float32 KDSM_CurErrorThd2_value;/* Referenced by: '<S47>/Constant1' */
extern float32 KDSM_CurErrorThd_value; /* Referenced by: '<S47>/Constant6' */
extern float32 KDSM_DiagSpdH_rpm;      /* Referenced by: '<S184>/Constant2' */
extern float32 KDSM_DiagSpdL_rpm;      /* Referenced by: '<S184>/Constant4' */
extern boolean KDSM_bIvtrTarHiDebug_flg;/* Referenced by: '<S184>/Constant7' */
extern uint8 KFOC_ADCReadEnum_enum;    /* Referenced by: '<S4>/Constant14' */
extern float32 KFOC_DCBusLPF_c;        /* Referenced by: '<S4>/Constant13' */
extern boolean KFOC_DCBusUseRaw_flg;   /* Referenced by: '<S4>/Constant2' */
extern boolean KFOC_DCBusVoltage_V_ovrdflg;/* Referenced by: '<S4>/Constant' */
extern float32 KFOC_DCBusVoltage_V_ovrdval;/* Referenced by: '<S4>/Constant1' */
extern boolean KFOC_FltActn_flg_ovrdflg;/* Referenced by: '<S3>/Constant12' */
extern boolean KFOC_FltActn_flg_ovrdfval;/* Referenced by: '<S3>/Constant14' */
extern boolean KFOC_GateICDisable_flg; /* Referenced by: '<S3>/Constant1' */
extern boolean KFOC_GateICEnable_flg;  /* Referenced by: '<S3>/Constant3' */
extern boolean KFOC_IdCmd_A_ovrdflg;   /* Referenced by: '<S3>/Constant5' */
extern float32 KFOC_IdCmd_A_ovrdfval;  /* Referenced by: '<S3>/Constant6' */
extern boolean KFOC_IqCmd_A_ovrdflg;   /* Referenced by: '<S3>/Constant8' */
extern float32 KFOC_IqCmd_A_ovrdfval;  /* Referenced by: '<S3>/Constant9' */
extern float32 KFOC_MagFluxLinkage_C;  /* Referenced by:
                                        * '<S48>/Constant1'
                                        * '<S48>/Constant2'
                                        * '<S48>/Constant4'
                                        */
extern boolean KFOC_OpMod_enum_ovrdflg;/* Referenced by: '<S3>/Constant10' */
extern uint8 KFOC_OpMod_enum_ovrdval;  /* Referenced by: '<S3>/Constant11' */
extern boolean KFOC_PWMidle_flg;       /* Referenced by: '<S14>/Constant' */
extern float32 KFOC_PolePairs_p;       /* Referenced by:
                                        * '<S20>/Constant4'
                                        * '<S48>/Constant3'
                                        * '<S48>/Constant5'
                                        */
extern boolean KFOC_RotPosnOffset_rad_ovrdflg;/* Referenced by: '<S15>/Constant' */
extern float32 KFOC_RotPosnOffset_rad_ovrdval;/* Referenced by: '<S15>/Constant1' */
extern uint8 KFOC_SensorMode_enum;     /* Referenced by: '<S3>/Constant13' */
extern float32 KFOC_SpdCmd_RPM;        /* Referenced by: '<S3>/Constant2' */
extern float32 KFOC_VdCmd_V;           /* Referenced by:
                                        * '<S12>/Constant18'
                                        * '<S12>/Constant20'
                                        */
extern float32 KFOC_VqCmd_V;           /* Referenced by:
                                        * '<S12>/Constant19'
                                        * '<S12>/Constant21'
                                        */
extern float32 KMCM_DFwdCoef_null;     /* Referenced by: '<S48>/Gain3' */
extern float32 KMCM_QFwdCoef_null;     /* Referenced by: '<S48>/Gain2' */
extern boolean KOSP_IvtrTarMor_enum_ovrdflg;/* Referenced by: '<S184>/Constant9' */
extern uint8 KOSP_IvtrTarMor_enum_ovrdval;/* Referenced by: '<S184>/Constant12' */
extern boolean KPCS_EnaSnsrSelfLrn_flg_ovrdflg;/* Referenced by: '<S27>/Constant3' */
extern boolean KPCS_EnaSnsrSelfLrn_flg_ovrdval;/* Referenced by: '<S27>/Constant' */
extern boolean KPCS_MaxCurrReset_flg;  /* Referenced by: '<S26>/Constant' */
extern float32 KPCS_OffsFilCoeff_fac;  /* Referenced by: '<S25>/Constant' */
extern uint16 KPCS_OffsFilTi_cnt;      /* Referenced by: '<S27>/Constant1' */
extern float32 KPCS_PhaseCurSnsrVolDft_V;/* Referenced by: '<S28>/Constant4' */
extern float32 KPCS_PhaseCurSnsrVolVldMax_V;/* Referenced by: '<S28>/Constant' */
extern float32 KPCS_PhaseCurSnsrVolVldMin_V;/* Referenced by: '<S28>/Constant1' */
extern float32 KPCS_UCurSnsr_Gain;     /* Referenced by: '<S19>/Constant3' */
extern float32 KPCS_VCurSnsr_Gain;     /* Referenced by: '<S19>/Constant1' */
extern float32 KPCS_WCurSnsr_Gain;     /* Referenced by: '<S19>/Constant' */
extern boolean KPCS_bCurOffsVolVld_flg_ovrdflg;
                       /* Referenced by: '<S28>/PCS_bCurOffsVolVld_flgTrig_C' */
extern boolean KPCS_bCurOffsVolVld_flg_ovrdval;
                        /* Referenced by: '<S28>/PCS_bCurOffsVolVld_flgMor_C' */
extern uint8 KPDC_FWCnt_C;             /* Referenced by: '<S220>/Constant2' */
extern float32 KPDC_facScalePWM_C;     /* Referenced by: '<S171>/Constant4' */
extern float32 KPDC_nPosnErrMaxSpd_C;  /* Referenced by: '<S184>/Constant1' */
extern float32 KRCM_IdCmd_A;           /* Referenced by: '<S43>/Constant2' */
extern float32 KRCM_IqCmd_A;           /* Referenced by: '<S43>/Constant4' */
extern float32 KROT_CurLoopPrd_t;      /* Referenced by: '<S20>/TM_Prd' */
extern boolean KROT_RotAngleE_rad_ovrdflg;
                                /* Referenced by: '<S20>/RotS_agRotRawTrig_C' */
extern float32 KROT_RotAngleE_rad_ovrdval;
                                 /* Referenced by: '<S20>/RotS_agRotRawMor_C' */
extern boolean KROT_RotSpdMRaw_rpm_ovrdflg;
                                    /* Referenced by: '<S20>/RotS_nRotTrig_C' */
extern float32 KROT_RotSpdMRaw_rpm_ovrdval;
                                     /* Referenced by: '<S20>/RotS_nRotMor_C' */
extern float32 KROT_SpdCutoffFreq_Hz;
                                    /* Referenced by: '<S20>/RotS_nRotMor_C1' */
extern boolean KROT_bUseVariableFc_flg;
                                    /* Referenced by: '<S32>/RotS_nRotMor_C1' */
extern uint8 KeMCCR_b_UseMeasCrntDTC;  /* Referenced by: '<S183>/ReciSqrt3M1' */
extern float32 KeSVMR_FullDTCCurr_A;   /* Referenced by: '<S188>/Constant3' */
extern uint16 KeSVMR_PWMPrd_cnt;       /* Referenced by:
                                        * '<S188>/Constant2'
                                        * '<S189>/Constant2'
                                        */
extern float32 KeSVMR_StrClampMaxDuty_pct;/* Referenced by: '<S213>/Constant1' */
extern float32 KeSVMR_StrClampMinDuty_pct;/* Referenced by: '<S213>/Constant3' */
extern float32 KeSVMR_b_UseStrictClamp;/* Referenced by:
                                        * '<S189>/Constant5'
                                        * '<S197>/Constant'
                                        * '<S198>/Constant'
                                        * '<S199>/Constant'
                                        */
extern float32 KeSVMR_t_DeadTime;      /* Referenced by:
                                        * '<S188>/Constant'
                                        * '<S212>/Constant5'
                                        */
extern float32 KeSVMR_t_MinPulseWidth; /* Referenced by: '<S212>/Constant1' */
extern float32 MCCM_IdKp_Y_value[20];
                                    /* Referenced by: '<S92>/MCCM_IdKp_value' */
extern float32 MCCM_IqKp_Y_value[20];
                                    /* Referenced by: '<S93>/MCCM_IqKp_value' */
extern float32 MCCM_facCCMLd_Z_T[1296];/* Referenced by: '<S48>/LdMapp' */
extern float32 MCCM_facCCMLq_Z_T[1296];/* Referenced by: '<S48>/LqMapp' */
extern float32 MCCM_facLPFiDAct_Y_T[11];
                                 /* Referenced by: '<S45>/CCM_facLPFiDAct_T1' */
extern float32 MCCM_facLPFiQAct_Y_T[11];
                                 /* Referenced by: '<S45>/CCM_facLPFiQAct_T1' */
extern float32 MROT_ParkCompAngle_Y_rad[20];
                                   /* Referenced by: '<S20>/1-D Lookup Table' */
extern float32 MROT_VolPosnOffsWiSpd_Y_deg[20];
                                  /* Referenced by: '<S20>/1-D Lookup Table2' */
extern float32 SampleTimeFOC;          /* Referenced by: '<S47>/Constant10' */

#define SWC_ETE_type_STOP_SEC_CAL
#include "SWC_ETE_type_MemMap.h"

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S26>/Display' : Unused code path elimination
 * Block '<S26>/Display1' : Unused code path elimination
 * Block '<S26>/Display2' : Unused code path elimination
 * Block '<S26>/Display3' : Unused code path elimination
 * Block '<S60>/NOT1' : Unused code path elimination
 * Block '<S64>/NOT1' : Unused code path elimination
 * Block '<S80>/NOT1' : Unused code path elimination
 * Block '<S115>/Display' : Unused code path elimination
 * Block '<S115>/Display1' : Unused code path elimination
 * Block '<S115>/Display2' : Unused code path elimination
 * Block '<S123>/NOT1' : Unused code path elimination
 * Block '<S128>/NOT1' : Unused code path elimination
 * Block '<S132>/NOT1' : Unused code path elimination
 * Block '<S136>/NOT1' : Unused code path elimination
 * Block '<S140>/NOT1' : Unused code path elimination
 * Block '<S144>/NOT1' : Unused code path elimination
 * Block '<S153>/NOT1' : Unused code path elimination
 * Block '<S157>/NOT1' : Unused code path elimination
 * Block '<S161>/NOT1' : Unused code path elimination
 * Block '<S165>/NOT1' : Unused code path elimination
 * Block '<S171>/Display' : Unused code path elimination
 * Block '<S171>/Display1' : Unused code path elimination
 * Block '<S171>/Display2' : Unused code path elimination
 * Block '<S216>/Data Type Duplicate' : Unused code path elimination
 * Block '<S216>/Data Type Propagation' : Unused code path elimination
 * Block '<S186>/Data Type Duplicate' : Unused code path elimination
 * Block '<S186>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S44>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S115>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S113>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S171>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S194>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S194>/Signal Conversion2' : Eliminate redundant signal conversion block
 * Block '<S195>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S195>/Signal Conversion2' : Eliminate redundant signal conversion block
 * Block '<S196>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S196>/Signal Conversion2' : Eliminate redundant signal conversion block
 * Block '<S197>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S198>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S199>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion2' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion7' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion8' : Eliminate redundant signal conversion block
 * Block '<S190>/Signal Conversion9' : Eliminate redundant signal conversion block
 * Block '<S187>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S188>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S188>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S15>/Data Type Conversion5' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SWC_ETE_type'
 * '<S1>'   : 'SWC_ETE_type/SWC_ETE_type_Init'
 * '<S2>'   : 'SWC_ETE_type/run_FOC_sys'
 * '<S3>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC'
 * '<S4>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read'
 * '<S5>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT'
 * '<S6>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH'
 * '<S7>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Detect Increase'
 * '<S8>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Detect Increase1'
 * '<S9>'   : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Detect Increase2'
 * '<S10>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Disable_GateIC'
 * '<S11>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Enable_GateIC'
 * '<S12>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/FOC_Mode_Judge'
 * '<S13>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC'
 * '<S14>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PWM_idle_Mode'
 * '<S15>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/RotorPositionHandle'
 * '<S16>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Subsystem'
 * '<S17>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/Subsystem1'
 * '<S18>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/LowPass_NoTrigger1'
 * '<S19>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/PCS'
 * '<S20>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1'
 * '<S21>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/LowPass_NoTrigger1/Delay'
 * '<S22>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/LowPass_NoTrigger1/MUL'
 * '<S23>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/LowPass_NoTrigger1/SUB'
 * '<S24>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/LowPass_NoTrigger1/SUM'
 * '<S25>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/PCS/CalcSelfLrnOffsVal'
 * '<S26>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/PCS/MaxPha'
 * '<S27>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/PCS/SelfLrnEna'
 * '<S28>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/PCS/SnsrOffsDiag'
 * '<S29>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2'
 * '<S30>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/First_Order_Filter'
 * '<S31>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/Subsystem'
 * '<S32>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/Variable_Fc'
 * '<S33>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/Wrapp '
 * '<S34>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/Wrapp 1'
 * '<S35>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/BigEqual'
 * '<S36>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MAX'
 * '<S37>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MIN'
 * '<S38>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/SWT2'
 * '<S39>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MAX/SWT2'
 * '<S40>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MAX/Small'
 * '<S41>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MIN/Big'
 * '<S42>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/ADC_RDC_Read/ROT1/DIV2/MIN/SWT2'
 * '<S43>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop'
 * '<S44>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ASCCal'
 * '<S45>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ActCurrDQ'
 * '<S46>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/Anti Park'
 * '<S47>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd'
 * '<S48>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/FwTqEsti'
 * '<S49>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/PI'
 * '<S50>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim'
 * '<S51>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ASCCal/If Action Subsystem'
 * '<S52>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ASCCal/Subsystem1'
 * '<S53>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ASCCal/Subsystem1/Ramp'
 * '<S54>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ActCurrDQ/LowPass_Filter'
 * '<S55>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/ActCurrDQ/LowPass_Filter1'
 * '<S56>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF'
 * '<S57>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF1'
 * '<S58>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2'
 * '<S59>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF/Delay'
 * '<S60>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF/NOT'
 * '<S61>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF/SWT1'
 * '<S62>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF/SWT2'
 * '<S63>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF1/Delay'
 * '<S64>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF1/NOT'
 * '<S65>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF1/SWT1'
 * '<S66>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/ER_FF1/SWT2'
 * '<S67>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/AND'
 * '<S68>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/BigEqual'
 * '<S69>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Delay'
 * '<S70>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/ER_FF'
 * '<S71>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Falling'
 * '<S72>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/GAIN'
 * '<S73>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising'
 * '<S74>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising1'
 * '<S75>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/SUB'
 * '<S76>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/SUM'
 * '<S77>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/SWT1'
 * '<S78>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/SWT2'
 * '<S79>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/ER_FF/Delay'
 * '<S80>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/ER_FF/NOT'
 * '<S81>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/ER_FF/SWT1'
 * '<S82>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/ER_FF/SWT2'
 * '<S83>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Falling/AND'
 * '<S84>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Falling/Delay'
 * '<S85>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Falling/NOT'
 * '<S86>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising/AND'
 * '<S87>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising/Delay'
 * '<S88>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising/NOT'
 * '<S89>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising1/AND'
 * '<S90>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising1/Delay'
 * '<S91>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/CurErrorOverThd/TurnOnDelay_Dyn2/Rising1/NOT'
 * '<S92>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/PI/IdPI'
 * '<S93>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/PI/IqPI'
 * '<S94>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/PI/IdPI/Id_Regulator'
 * '<S95>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/PI/IqPI/Iq_Regulator'
 * '<S96>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2'
 * '<S97>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/VdFilter'
 * '<S98>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/VdFilter1'
 * '<S99>'  : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/BigEqual'
 * '<S100>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MAX'
 * '<S101>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MIN'
 * '<S102>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/SWT2'
 * '<S103>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MAX/SWT2'
 * '<S104>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MAX/Small'
 * '<S105>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MIN/Big'
 * '<S106>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/CCM_FVT/CurrLoop/VdqLim/DIV2/MIN/SWT2'
 * '<S107>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor'
 * '<S108>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF1'
 * '<S109>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF2'
 * '<S110>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF3'
 * '<S111>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF4'
 * '<S112>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF5'
 * '<S113>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent'
 * '<S114>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem'
 * '<S115>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err'
 * '<S116>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/Compare To Zero'
 * '<S117>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/Detect Increase'
 * '<S118>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/Detect Increase1'
 * '<S119>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/Detect Increase2'
 * '<S120>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/ER_FF1'
 * '<S121>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/debounce'
 * '<S122>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/ER_FF1/Delay'
 * '<S123>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/ER_FF1/NOT'
 * '<S124>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/ER_FF1/SWT1'
 * '<S125>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/ER_FF1/SWT2'
 * '<S126>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/CurrentSensor/Subsystem/Sum_Err/debounce/Chart'
 * '<S127>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF1/Delay'
 * '<S128>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF1/NOT'
 * '<S129>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF1/SWT1'
 * '<S130>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF1/SWT2'
 * '<S131>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF2/Delay'
 * '<S132>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF2/NOT'
 * '<S133>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF2/SWT1'
 * '<S134>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF2/SWT2'
 * '<S135>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF3/Delay'
 * '<S136>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF3/NOT'
 * '<S137>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF3/SWT1'
 * '<S138>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF3/SWT2'
 * '<S139>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF4/Delay'
 * '<S140>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF4/NOT'
 * '<S141>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF4/SWT1'
 * '<S142>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF4/SWT2'
 * '<S143>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF5/Delay'
 * '<S144>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF5/NOT'
 * '<S145>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF5/SWT1'
 * '<S146>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/ER_FF5/SWT2'
 * '<S147>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF'
 * '<S148>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF1'
 * '<S149>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF2'
 * '<S150>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF3'
 * '<S151>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/debounce'
 * '<S152>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF/Delay'
 * '<S153>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF/NOT'
 * '<S154>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF/SWT1'
 * '<S155>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF/SWT2'
 * '<S156>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF1/Delay'
 * '<S157>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF1/NOT'
 * '<S158>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF1/SWT1'
 * '<S159>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF1/SWT2'
 * '<S160>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF2/Delay'
 * '<S161>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF2/NOT'
 * '<S162>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF2/SWT1'
 * '<S163>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF2/SWT2'
 * '<S164>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF3/Delay'
 * '<S165>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF3/NOT'
 * '<S166>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF3/SWT1'
 * '<S167>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/ER_FF3/SWT2'
 * '<S168>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/DGH/OverCurrent/debounce/Chart'
 * '<S169>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/FOC_Mode_Judge/Inverse Park Transform (GRC)'
 * '<S170>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation'
 * '<S171>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation'
 * '<S172>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/SectorDetermine'
 * '<S173>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation'
 * '<S174>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5'
 * '<S175>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/BigEqual'
 * '<S176>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MAX'
 * '<S177>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MIN'
 * '<S178>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/SWT2'
 * '<S179>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MAX/SWT2'
 * '<S180>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MAX/Small'
 * '<S181>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MIN/Big'
 * '<S182>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/ChangeTimeCalculation/DIV5/MIN/SWT2'
 * '<S183>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation'
 * '<S184>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/Inverter Control '
 * '<S185>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable'
 * '<S186>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/Saturation Dynamic'
 * '<S187>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO'
 * '<S188>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/ReInitSVMR_DeadTimeCompensation'
 * '<S189>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/ReInitSVMR_PWM_Modulation'
 * '<S190>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem'
 * '<S191>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem1'
 * '<S192>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem5'
 * '<S193>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem6'
 * '<S194>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsA'
 * '<S195>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsB'
 * '<S196>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsC'
 * '<S197>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsA'
 * '<S198>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsB'
 * '<S199>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsC'
 * '<S200>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsA/compensate'
 * '<S201>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsA/no_compensate'
 * '<S202>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsB/compensate'
 * '<S203>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsB/no_compensate'
 * '<S204>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsC/compensate'
 * '<S205>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_DeadTimeCompensation_PhsC/no_compensate'
 * '<S206>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsA/SmartClamping'
 * '<S207>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsA/StrictClamping'
 * '<S208>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsB/SmartClamping'
 * '<S209>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsB/StrictClamping'
 * '<S210>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsC/SmartClamping'
 * '<S211>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/MngSVMR_Base_MtrCntrl0_ProcessDCsForHWIO/If Action Subsystem/SetSVMR_SmartClamps_PhsC/StrictClamping'
 * '<S212>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/ReInitSVMR_PWM_Modulation/Not_SVPWM_StrictClamp'
 * '<S213>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/DeadTimeCompensation/ReInitSVMR_PWM_Modulation/SVPWM_StrictClamp'
 * '<S214>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/Inverter Control /Compare To Zero'
 * '<S215>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/Inverter Control /SS_SafetyShutdown_Ctrl'
 * '<S216>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/Inverter Control /Saturation Dynamic'
 * '<S217>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable/NormalPWM'
 * '<S218>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable/PWMFW'
 * '<S219>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable/PWMGOFF'
 * '<S220>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable/ThreePhaseSC'
 * '<S221>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/PWMCalculation/PWMCmdCtrlEnable/ThreePhaseSC/ASC2'
 * '<S222>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV'
 * '<S223>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1'
 * '<S224>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2'
 * '<S225>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5'
 * '<S226>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/Overmodulation'
 * '<S227>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/BigEqual'
 * '<S228>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MAX'
 * '<S229>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MIN'
 * '<S230>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/SWT2'
 * '<S231>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MAX/SWT2'
 * '<S232>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MAX/Small'
 * '<S233>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MIN/Big'
 * '<S234>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV/MIN/SWT2'
 * '<S235>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/BigEqual'
 * '<S236>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MAX'
 * '<S237>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MIN'
 * '<S238>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/SWT2'
 * '<S239>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MAX/SWT2'
 * '<S240>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MAX/Small'
 * '<S241>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MIN/Big'
 * '<S242>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV1/MIN/SWT2'
 * '<S243>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/BigEqual'
 * '<S244>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MAX'
 * '<S245>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MIN'
 * '<S246>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/SWT2'
 * '<S247>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MAX/SWT2'
 * '<S248>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MAX/Small'
 * '<S249>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MIN/Big'
 * '<S250>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV2/MIN/SWT2'
 * '<S251>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/BigEqual'
 * '<S252>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MAX'
 * '<S253>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MIN'
 * '<S254>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/SWT2'
 * '<S255>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MAX/SWT2'
 * '<S256>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MAX/Small'
 * '<S257>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MIN/Big'
 * '<S258>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/DIV5/MIN/SWT2'
 * '<S259>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PDC/WorkTimeCalculation/Overmodulation/Overmodulation'
 * '<S260>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PWM_idle_Mode/Detect Increase'
 * '<S261>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/PWM_idle_Mode/Enabled Subsystem'
 * '<S262>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/RotorPositionHandle/Fake_RDC_Handler'
 * '<S263>' : 'SWC_ETE_type/run_FOC_sys/MTPA_FOC/RotorPositionHandle/Subsystem'
 */
#endif                                 /* SWC_ETE_type_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
