/*
 * File: SWC_ETE_type.c
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

#include "SWC_ETE_type.h"
#include "MTPA_FOC.h"

/* Exported block signals */
uint32 VROT_FreqPWM_Tick;              /* '<S31>/Data Type Conversion' */
float32 VFOC_RotorPosnOffset_rad;      /* '<S15>/Switch' */
float32 VFOC_FakeRotorPosn_rad;        /* '<S262>/Switch' */
float32 VPDC_DutyA_raw;                /* '<S171>/Data Type Conversion1' */
float32 VPDC_DutyB_raw;                /* '<S171>/Data Type Conversion2' */
float32 VPDC_DutyC_raw;                /* '<S171>/Data Type Conversion4' */
float32 VFOC_VcmdAlpha_V;              /* '<S12>/Data Type Conversion' */
float32 VFOC_VcmdBeta_V;               /* '<S12>/Data Type Conversion1' */
float32 VDGH_SumErrPhCurU_A;           /* '<S115>/Switch2' */
float32 VDGH_SumErrPhCurW_A;           /* '<S115>/Switch4' */
float32 VDGH_SumErrPhCurV_A;           /* '<S115>/Switch6' */
float32 VCCM_iDCurrAct_A;              /* '<S54>/Add' */
float32 VMCM_VdFwd_V;                  /* '<S48>/Gain3' */
float32 VCCM_VdRef_V;                  /* '<S94>/Add5' */
float32 VCCM_iQCurrAct_A;              /* '<S55>/Add' */
float32 VMCM_VqFwd_V;                  /* '<S48>/Gain2' */
float32 VCCM_VqRef_V;                  /* '<S95>/Add5' */
float32 VCCM_DcHiBatLim_V;             /* '<S50>/Saturation1' */
float32 VCCM_VdCmd_V;                  /* '<S50>/Switch' */
float32 VCCM_VqCmd_V;                  /* '<S50>/Switch1' */
float32 VCCM_uASCVd_V;                 /* '<S44>/Merge' */
float32 VCCM_uASCVq_V;                 /* '<S44>/Merge1' */
float32 VCCM_uAlphaVoltTar_V;          /* '<S46>/Fcn' */
float32 VCCM_uBetaVoltTar_V;           /* '<S46>/Fcn1' */
float32 VMCM_TqAct_Nm;                 /* '<S48>/Product10' */
float32 VMCM_TqEst_Nm;                 /* '<S48>/Product7' */
float32 VCCM_VcmdBfLim_V;              /* '<S97>/Add' */
float32 VCCM_BattVolCirRadius_V;       /* '<S98>/Add' */
float32 VCCM_VoltUtilize_pu;           /* '<S50>/Product6' */
float32 VFOC_iARaw_raw;                /* '<S4>/Data Type Conversion1' */
float32 VFOC_iBRaw_raw;                /* '<S4>/Data Type Conversion2' */
float32 VFOC_iCRaw_raw;                /* '<S4>/Data Type Conversion3' */
float32 VPCS_PhaWCur_A;                /* '<S19>/Product' */
float32 VPCS_PhaVCur_A;                /* '<S19>/Product1' */
float32 VPCS_PhaUCur_A;                /* '<S19>/Product3' */
float32 VPCS_MaxPhaCurW_A;             /* '<S26>/Switch7' */
float32 VPCS_MaxPhaCurU_A;             /* '<S26>/Switch3' */
float32 VPCS_MaxPhaCur_A;              /* '<S26>/Switch1' */
float32 VPCS_MaxPhaCurV_A;             /* '<S26>/Switch5' */
float32 VFOC_DCBusRAW_V;               /* '<S4>/Data Type Conversion5' */
float32 VFOC_DCBusVoltage_V;           /* '<S4>/Switch3' */
float32 VROT_RotSpdERaw_rads;          /* '<S20>/Data Type Conversion2' */
float32 VROT_RotSpdM_rpm;              /* '<S20>/First_Order_Filter' */
float32 VROT_RotAgECompL_rad;          /* '<S20>/Add1' */
float32 VROT_RotAngleERaw_rad;         /* '<S20>/Data Type Conversion1' */
float32 VROT_RotAngleE_rad;            /* '<S34>/Switch1' */
float32 VROT_RotSpdE_rads;             /* '<S20>/Signal Conversion' */
float32 VROT_RotAgECompV_rad;          /* '<S20>/Product1' */
float32 VROT_RotAngleV_rad;            /* '<S33>/Switch1' */
float32 VPCS_WCurOffsFil_V;            /* '<S28>/Switch' */
float32 VPCS_VCurOffsFil_V;            /* '<S28>/Switch1' */
float32 VPCS_UCurOffsFil_V;            /* '<S28>/Switch2' */
float32 VPCS_WCurOffsRaw_V;            /* '<S25>/Data Type Conversion' */
float32 VPCS_VCurOffsRaw_V;            /* '<S25>/Data Type Conversion1' */
float32 VPCS_UCurOffsRaw_V;            /* '<S25>/Data Type Conversion3' */
uint8 VPDC_Ivtr1ModCmd_enum;           /* '<S185>/Merge2' */
boolean VDGH_RteFault_flg;             /* '<S6>/Logical Operator1' */
boolean VDGH_100usFaultLevel2_flg;     /* '<S6>/bsw_bPosSenrFaultswt' */
boolean VDGH_FaultLevel2_flg;          /* '<S6>/Logical Operator2' */
boolean VDGH_CurOffsErrLat_flg;        /* '<S6>/Logical Operator9' */
boolean VPDC_bASCFlgRaw_flg;           /* '<S171>/Logical Operator' */
boolean VDGH_OverCurrent_flg;          /* '<S113>/ESM_bMcuShtDwnAllwdswt' */
boolean VDGH_PhaCurrOverDQ_flg;        /* '<S167>/SWT' */
boolean VDGH_PhaCurrOverW_flg;         /* '<S163>/SWT' */
boolean VDGH_PhaCurrOverV_flg;         /* '<S159>/SWT' */
boolean VDGH_PhaCurrOverU_flg;         /* '<S155>/SWT' */
boolean VDGH_HWOverVoltFltLat_flg;     /* '<S146>/SWT' */
boolean VDGH_HWLsideFltLat_flg;        /* '<S142>/SWT' */
boolean VDGH_HWHsideFltLat_flg;        /* '<S138>/SWT' */
boolean VDGH_PosSenrFaultLat_flg;      /* '<S134>/SWT' */
boolean VDGH_CurrFaultLat_flg;         /* '<S130>/SWT' */
boolean VDGH_SumErr_flg;               /* '<S115>/SumErr_Outswt' */
boolean VCCM_bASCEna_flg;              /* '<S44>/Merge2' */
boolean VCCM_CurErrorOverThd2_flg;     /* '<S66>/SWT' */
boolean VCCM_CurErrorOverThd_flg;      /* '<S62>/SWT' */
boolean VPCS_EnaSnsrSelfLrn_flg;       /* '<S27>/Switch1' */
boolean VPCS_SnsrSelfLrnCompl_flg;     /* '<S19>/Logical Operator' */
boolean VPCS_WCurOffsVolVld_flg;       /* '<S28>/Signal Conversion2' */
boolean VPCS_VCurOffsVolVld_flg;       /* '<S28>/Signal Conversion' */
boolean VPCS_UCurOffsVolVld_flg;       /* '<S28>/Signal Conversion1' */
boolean VPCS_bCurOffsVolVld_flg;       /* '<S28>/PCS_bCurOffsVolVld_flgswt' */

/* Exported data definition */
#define SWC_ETE_type_START_SEC_CAL
#include "SWC_ETE_type_MemMap.h"

/* Definition for custom storage class: Global */
float32 ACCM_IdKp_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F, 5000.0F,
  6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F, 13000.0F,
  14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F } ;/* Referenced by:
                                                                      * '<S92>/MCCM_IdKp_value'
                                                                      * '<S93>/MCCM_IqKp_value'
                                                                      */

float32 ACCM_facCCMLq_X_A[36] = { 0.0F, 18.5714302F, 37.1428604F, 55.7142906F,
  74.2857132F, 92.8571396F, 111.428596F, 130.0F, 148.571396F, 167.142899F,
  185.714294F, 204.285706F, 222.857101F, 241.428604F, 260.0F, 278.571411F,
  297.142914F, 315.714294F, 334.285706F, 352.857086F, 371.428589F, 390.0F,
  408.571411F, 427.142914F, 445.714294F, 464.285706F, 482.857086F, 501.428589F,
  520.0F, 538.571411F, 557.142883F, 575.714294F, 594.285706F, 612.857117F,
  631.428589F, 650.0F } ;              /* Referenced by:
                                        * '<S48>/LdMapp'
                                        * '<S48>/LqMapp'
                                        */

float32 ACCM_facCCMLq_Y_A[36] = { -650.0F, -631.428589F, -612.857117F,
  -594.285706F, -575.714294F, -557.142883F, -538.571411F, -520.0F, -501.428589F,
  -482.857086F, -464.285706F, -445.714294F, -427.142914F, -408.571411F, -390.0F,
  -371.428589F, -352.857086F, -334.285706F, -315.714294F, -297.142914F,
  -278.571411F, -260.0F, -241.428604F, -222.857101F, -204.285706F, -185.714294F,
  -167.142899F, -148.571396F, -130.0F, -111.428596F, -92.8571396F, -74.2857132F,
  -55.7142906F, -37.1428604F, -18.5714302F, 0.0F } ;/* Referenced by:
                                                     * '<S48>/LdMapp'
                                                     * '<S48>/LqMapp'
                                                     */

float32 ACCM_facLPFiDAct_X_rpm[11] = { 100.0F, 200.0F, 300.0F, 400.0F, 500.0F,
  600.0F, 700.0F, 800.0F, 900.0F, 1000.0F, 2000.0F } ;/* Referenced by:
                                                       * '<S45>/CCM_facLPFiDAct_T1'
                                                       * '<S45>/CCM_facLPFiQAct_T1'
                                                       */

float32 AROT_ParkCompAngle_X_rpm[20] = { 1000.0F, 2000.0F, 3000.0F, 4000.0F,
  5000.0F, 6000.0F, 7000.0F, 8000.0F, 9000.0F, 10000.0F, 11000.0F, 12000.0F,
  13000.0F, 14000.0F, 15000.0F, 16000.0F, 17000.0F, 18000.0F, 19000.0F, 20000.0F
} ;                                    /* Referenced by:
                                        * '<S20>/1-D Lookup Table'
                                        * '<S20>/1-D Lookup Table2'
                                        */

float32 KCCM_BattVolFilTi_fac = 0.06F; /* Referenced by:
                                        * '<S97>/Constant'
                                        * '<S98>/Constant'
                                        */
float32 KCCM_CurLoopPrd_t = 0.0001F;   /* Referenced by:
                                        * '<S92>/TM_Prd'
                                        * '<S93>/TM_Prd'
                                        */
float32 KCCM_FwdMask_c = 1.0F;         /* Referenced by:
                                        * '<S92>/Constant2'
                                        * '<S93>/Constant2'
                                        */
float32 KCCM_IdKi_null = 40.0F;        /* Referenced by: '<S92>/TM_Id_Ki' */
float32 KCCM_IdKt_null = 800.0F;       /* Referenced by: '<S92>/TM_Id_Kt' */
float32 KCCM_IqKi_null = 40.0F;        /* Referenced by: '<S93>/TM_Id_Ki' */
float32 KCCM_IqKt_null = 800.0F;       /* Referenced by: '<S93>/TM_Id_Kt' */
boolean KCCM_UdqASCEna_C = true_MatlabRTW;/* Referenced by: '<S44>/Constant2' */
float32 KCCM_UdqASCTagValue_C = 0.0F;  /* Referenced by: '<S52>/Constant3' */
float32 KCCM_UdqASCTimesValue_C = 0.01F;/* Referenced by: '<S52>/Constant1' */
boolean KCCM_VdSpSwEna_flg = false_MatlabRTW;/* Referenced by: '<S50>/ReciSqrt3M3' */
float32 KCCM_VdSp_V = 0.0F;            /* Referenced by: '<S50>/ReciSqrt3M1' */
float32 KCCM_VolMod_perc = 0.57F;      /* Referenced by: '<S50>/ReciSqrt3M' */
float32 KCCM_VqSp_V = 0.0F;            /* Referenced by: '<S50>/ReciSqrt3M2' */
boolean KCCM_bRstCurErrorOverThd_C = false_MatlabRTW;/* Referenced by: '<S47>/Constant7' */
float32 KCCM_tiCurErrOvr_C = 100.0F;   /* Referenced by: '<S47>/Constant2' */
boolean KDGH_FaultLevel2_flg_ovrdflg = false_MatlabRTW;
                             /* Referenced by: '<S6>/bsw_bPosSenrFaultTrig_C' */
boolean KDGH_FaultLevel2_flg_ovrdval = false_MatlabRTW;
                              /* Referenced by: '<S6>/bsw_bPosSenrFaultMor_C' */
sint16 KDGH_OverCurrentErr_C = 20;     /* Referenced by: '<S113>/Constant2' */
sint16 KDGH_OverCurrentHeal_C = -20;   /* Referenced by: '<S113>/Constant1' */
float32 KDGH_OverCurrent_A = 707.0F;   /* Referenced by: '<S113>/Constant' */
boolean KDGH_OverCurrent_flg_ovrdflg = false_MatlabRTW;
                         /* Referenced by: '<S113>/ESM_bMcuShtDwnAllwdTrig_C' */
boolean KDGH_OverCurrent_flg_ovrdval = false_MatlabRTW;
                          /* Referenced by: '<S113>/ESM_bMcuShtDwnAllwdMor_C' */
float32 KDGH_PhaCurrOverU_A = 700.0F;  /* Referenced by: '<S113>/Constant3' */
float32 KDGH_PhaCurrOverV_A = 700.0F;  /* Referenced by: '<S113>/Constant4' */
float32 KDGH_PhaCurrOverW_A = 700.0F;  /* Referenced by: '<S113>/Constant5' */
boolean KDGH_RstPhaCurrOver_flg = false_MatlabRTW;/* Referenced by:
                                                   * '<S113>/Constant12'
                                                   * '<S113>/Constant13'
                                                   * '<S113>/Constant7'
                                                   * '<S113>/Constant8'
                                                   */
boolean KDGH_RstSumErr_flg = false_MatlabRTW;/* Referenced by: '<S115>/Constant8' */
sint16 KDGH_SumErrErr_C = 20;          /* Referenced by: '<S115>/Constant2' */
sint16 KDGH_SumErrHeal_C = -20;        /* Referenced by: '<S115>/Constant1' */
float32 KDGH_SumErr_A = 50.0F;         /* Referenced by: '<S115>/Constant' */
boolean KDGH_SumErr_flg_ovrdflg = false_MatlabRTW;
                                  /* Referenced by: '<S115>/SumErr_OutTrig_C' */
boolean KDGH_SumErr_flg_ovrdval = false_MatlabRTW;
                                   /* Referenced by: '<S115>/SumErr_OutMor_C' */
boolean KDGH_bRstRteFault_flg = false_MatlabRTW;/* Referenced by: '<S6>/Constant8' */
float32 KDSM_CurErrorThd2_value = 100.0F;/* Referenced by: '<S47>/Constant1' */
float32 KDSM_CurErrorThd_value = 30.0F;/* Referenced by: '<S47>/Constant6' */
float32 KDSM_DiagSpdH_rpm = 11000.0F;  /* Referenced by: '<S184>/Constant2' */
float32 KDSM_DiagSpdL_rpm = 10500.0F;  /* Referenced by: '<S184>/Constant4' */
boolean KDSM_bIvtrTarHiDebug_flg = false_MatlabRTW;/* Referenced by: '<S184>/Constant7' */
uint8 KFOC_ADCReadEnum_enum = 13U;     /* Referenced by: '<S4>/Constant14' */
float32 KFOC_DCBusLPF_c = 0.44F;       /* Referenced by: '<S4>/Constant13' */
boolean KFOC_DCBusUseRaw_flg = false_MatlabRTW;/* Referenced by: '<S4>/Constant2' */
boolean KFOC_DCBusVoltage_V_ovrdflg = false_MatlabRTW;/* Referenced by: '<S4>/Constant' */
float32 KFOC_DCBusVoltage_V_ovrdval = 0.0F;/* Referenced by: '<S4>/Constant1' */
boolean KFOC_FltActn_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S3>/Constant12' */
boolean KFOC_FltActn_flg_ovrdfval = false_MatlabRTW;/* Referenced by: '<S3>/Constant14' */
boolean KFOC_GateICDisable_flg = false_MatlabRTW;/* Referenced by: '<S3>/Constant1' */
boolean KFOC_GateICEnable_flg = false_MatlabRTW;/* Referenced by: '<S3>/Constant3' */
boolean KFOC_IdCmd_A_ovrdflg = false_MatlabRTW;/* Referenced by: '<S3>/Constant5' */
float32 KFOC_IdCmd_A_ovrdfval = 0.0F;  /* Referenced by: '<S3>/Constant6' */
boolean KFOC_IqCmd_A_ovrdflg = false_MatlabRTW;/* Referenced by: '<S3>/Constant8' */
float32 KFOC_IqCmd_A_ovrdfval = 0.0F;  /* Referenced by: '<S3>/Constant9' */
float32 KFOC_MagFluxLinkage_C = 0.138F;/* Referenced by:
                                        * '<S48>/Constant1'
                                        * '<S48>/Constant2'
                                        * '<S48>/Constant4'
                                        */
boolean KFOC_OpMod_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S3>/Constant10' */
uint8 KFOC_OpMod_enum_ovrdval = 0U;    /* Referenced by: '<S3>/Constant11' */
boolean KFOC_PWMidle_flg = false_MatlabRTW;/* Referenced by: '<S14>/Constant' */
float32 KFOC_PolePairs_p = 3.0F;       /* Referenced by:
                                        * '<S20>/Constant4'
                                        * '<S48>/Constant3'
                                        * '<S48>/Constant5'
                                        */
boolean KFOC_RotPosnOffset_rad_ovrdflg = false_MatlabRTW;/* Referenced by: '<S15>/Constant' */
float32 KFOC_RotPosnOffset_rad_ovrdval = 0.0F;/* Referenced by: '<S15>/Constant1' */
uint8 KFOC_SensorMode_enum = 0U;       /* Referenced by: '<S3>/Constant13' */
float32 KFOC_SpdCmd_RPM = 10.0F;       /* Referenced by: '<S3>/Constant2' */
float32 KFOC_VdCmd_V = 0.0F;           /* Referenced by:
                                        * '<S12>/Constant18'
                                        * '<S12>/Constant20'
                                        */
float32 KFOC_VqCmd_V = 0.0F;           /* Referenced by:
                                        * '<S12>/Constant19'
                                        * '<S12>/Constant21'
                                        */
float32 KMCM_DFwdCoef_null = 1.0F;     /* Referenced by: '<S48>/Gain3' */
float32 KMCM_QFwdCoef_null = 1.0F;     /* Referenced by: '<S48>/Gain2' */
boolean KOSP_IvtrTarMor_enum_ovrdflg = false_MatlabRTW;/* Referenced by: '<S184>/Constant9' */
uint8 KOSP_IvtrTarMor_enum_ovrdval = 5U;/* Referenced by: '<S184>/Constant12' */
boolean KPCS_EnaSnsrSelfLrn_flg_ovrdflg = false_MatlabRTW;/* Referenced by: '<S27>/Constant3' */
boolean KPCS_EnaSnsrSelfLrn_flg_ovrdval = false_MatlabRTW;/* Referenced by: '<S27>/Constant' */
boolean KPCS_MaxCurrReset_flg = false_MatlabRTW;/* Referenced by: '<S26>/Constant' */
float32 KPCS_OffsFilCoeff_fac = 0.1F;  /* Referenced by: '<S25>/Constant' */
uint16 KPCS_OffsFilTi_cnt = 250U;      /* Referenced by: '<S27>/Constant1' */
float32 KPCS_PhaseCurSnsrVolDft_V = 0.0F;/* Referenced by: '<S28>/Constant4' */
float32 KPCS_PhaseCurSnsrVolVldMax_V = 40.0F;/* Referenced by: '<S28>/Constant' */
float32 KPCS_PhaseCurSnsrVolVldMin_V = -40.0F;/* Referenced by: '<S28>/Constant1' */
float32 KPCS_UCurSnsr_Gain = 1.0F;     /* Referenced by: '<S19>/Constant3' */
float32 KPCS_VCurSnsr_Gain = 1.0F;     /* Referenced by: '<S19>/Constant1' */
float32 KPCS_WCurSnsr_Gain = 1.0F;     /* Referenced by: '<S19>/Constant' */
boolean KPCS_bCurOffsVolVld_flg_ovrdflg = false_MatlabRTW;
                       /* Referenced by: '<S28>/PCS_bCurOffsVolVld_flgTrig_C' */
boolean KPCS_bCurOffsVolVld_flg_ovrdval = false_MatlabRTW;
                        /* Referenced by: '<S28>/PCS_bCurOffsVolVld_flgMor_C' */
uint8 KPDC_FWCnt_C = 0U;               /* Referenced by: '<S220>/Constant2' */
float32 KPDC_facScalePWM_C = 2.0F;     /* Referenced by: '<S171>/Constant4' */
float32 KPDC_nPosnErrMaxSpd_C = 2000.0F;/* Referenced by: '<S184>/Constant1' */
float32 KRCM_IdCmd_A = 0.0F;           /* Referenced by: '<S43>/Constant2' */
float32 KRCM_IqCmd_A = 0.0F;           /* Referenced by: '<S43>/Constant4' */
float32 KROT_CurLoopPrd_t = 0.0001F;   /* Referenced by: '<S20>/TM_Prd' */
boolean KROT_RotAngleE_rad_ovrdflg = false_MatlabRTW;
                                /* Referenced by: '<S20>/RotS_agRotRawTrig_C' */
float32 KROT_RotAngleE_rad_ovrdval = 0.0F;
                                 /* Referenced by: '<S20>/RotS_agRotRawMor_C' */
boolean KROT_RotSpdMRaw_rpm_ovrdflg = false_MatlabRTW;
                                    /* Referenced by: '<S20>/RotS_nRotTrig_C' */
float32 KROT_RotSpdMRaw_rpm_ovrdval = 0.0F;
                                     /* Referenced by: '<S20>/RotS_nRotMor_C' */
float32 KROT_SpdCutoffFreq_Hz = 100.0F;
                                    /* Referenced by: '<S20>/RotS_nRotMor_C1' */
boolean KROT_bUseVariableFc_flg = false_MatlabRTW;
                                    /* Referenced by: '<S32>/RotS_nRotMor_C1' */
uint8 KeMCCR_b_UseMeasCrntDTC = 0U;    /* Referenced by: '<S183>/ReciSqrt3M1' */
float32 KeSVMR_FullDTCCurr_A = 6.0F;   /* Referenced by: '<S188>/Constant3' */
uint16 KeSVMR_PWMPrd_cnt = 10000U;     /* Referenced by:
                                        * '<S188>/Constant2'
                                        * '<S189>/Constant2'
                                        */
float32 KeSVMR_StrClampMaxDuty_pct = 1.0F;/* Referenced by: '<S213>/Constant1' */
float32 KeSVMR_StrClampMinDuty_pct = 0.0F;/* Referenced by: '<S213>/Constant3' */
float32 KeSVMR_b_UseStrictClamp = 1.0F;/* Referenced by:
                                        * '<S189>/Constant5'
                                        * '<S197>/Constant'
                                        * '<S198>/Constant'
                                        * '<S199>/Constant'
                                        */
float32 KeSVMR_t_DeadTime = 3.0E-6F;   /* Referenced by:
                                        * '<S188>/Constant'
                                        * '<S212>/Constant5'
                                        */
float32 KeSVMR_t_MinPulseWidth = 2.0E-6F;/* Referenced by: '<S212>/Constant1' */
float32 MCCM_IdKp_Y_value[20] = { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
  1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F } ;
                                    /* Referenced by: '<S92>/MCCM_IdKp_value' */

float32 MCCM_IqKp_Y_value[20] = { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
  1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F } ;
                                    /* Referenced by: '<S93>/MCCM_IqKp_value' */

float32 MCCM_facCCMLd_Z_T[1296] = { 0.00029299F, 0.0002931F, 0.00029321F,
  0.00029332F, 0.00029346F, 0.00029364F, 0.00029388F, 0.0002942F, 0.00029463F,
  0.00029518F, 0.00029584F, 0.00029659F, 0.00029742F, 0.00029827F, 0.00029911F,
  0.00029994F, 0.00030075F, 0.00030153F, 0.00030229F, 0.00030302F, 0.0003037F,
  0.00030434F, 0.00030498F, 0.00030565F, 0.00030657F, 0.00030758F, 0.00030857F,
  0.00030956F, 0.00031055F, 0.00031154F, 0.00031253F, 0.00031353F, 0.00031452F,
  0.00031547F, 0.00031695F, 0.00031577F, 0.00029049F, 0.00029068F, 0.00029087F,
  0.00029106F, 0.00029126F, 0.00029149F, 0.00029178F, 0.00029214F, 0.00029261F,
  0.0002932F, 0.00029391F, 0.0002947F, 0.00029553F, 0.00029637F, 0.0002972F,
  0.000298F, 0.00029877F, 0.00029955F, 0.00030035F, 0.00030114F, 0.00030189F,
  0.00030264F, 0.00030348F, 0.00030437F, 0.00030532F, 0.00030624F, 0.00030717F,
  0.00030809F, 0.00030902F, 0.00030996F, 0.00031088F, 0.00031181F, 0.00031269F,
  0.00031387F, 0.00031371F, 0.00031604F, 0.000288F, 0.00028826F, 0.00028852F,
  0.00028878F, 0.00028905F, 0.00028935F, 0.00028969F, 0.00029009F, 0.00029059F,
  0.00029124F, 0.00029199F, 0.00029281F, 0.00029363F, 0.00029446F, 0.00029527F,
  0.00029605F, 0.00029681F, 0.00029758F, 0.00029841F, 0.00029925F, 0.00030007F,
  0.00030091F, 0.00030179F, 0.00030266F, 0.00030352F, 0.00030438F, 0.00030525F,
  0.0003061F, 0.00030697F, 0.00030783F, 0.00030869F, 0.00030955F, 0.00031043F,
  0.00031119F, 0.00031245F, 0.00031276F, 0.00028551F, 0.00028583F, 0.00028615F,
  0.00028649F, 0.00028684F, 0.0002872F, 0.0002876F, 0.00028806F, 0.00028862F,
  0.00028933F, 0.00029011F, 0.00029092F, 0.00029171F, 0.0002925F, 0.00029329F,
  0.00029408F, 0.00029486F, 0.00029566F, 0.00029646F, 0.00029726F, 0.00029807F,
  0.00029887F, 0.00029967F, 0.00030046F, 0.00030126F, 0.00030206F, 0.00030286F,
  0.00030366F, 0.00030445F, 0.00030525F, 0.00030605F, 0.00030685F, 0.00030764F,
  0.00030848F, 0.00030924F, 0.00030974F, 0.00028301F, 0.00028337F, 0.00028375F,
  0.00028415F, 0.00028459F, 0.00028504F, 0.00028551F, 0.00028607F, 0.00028682F,
  0.00028753F, 0.00028829F, 0.00028902F, 0.00028975F, 0.00029049F, 0.00029122F,
  0.00029197F, 0.0002927F, 0.00029344F, 0.00029417F, 0.0002949F, 0.00029563F,
  0.00029637F, 0.0002971F, 0.00029784F, 0.00029857F, 0.0002993F, 0.00030004F,
  0.00030077F, 0.00030151F, 0.00030224F, 0.00030297F, 0.00030372F, 0.00030445F,
  0.00030516F, 0.00030591F, 0.00030656F, 0.00028049F, 0.00028089F, 0.0002813F,
  0.00028175F, 0.00028228F, 0.00028284F, 0.00028342F, 0.00028408F, 0.00028477F,
  0.00028542F, 0.0002861F, 0.00028677F, 0.00028744F, 0.0002881F, 0.00028878F,
  0.00028945F, 0.00029011F, 0.00029079F, 0.00029146F, 0.00029213F, 0.0002928F,
  0.00029347F, 0.00029414F, 0.00029481F, 0.00029548F, 0.00029615F, 0.00029682F,
  0.00029749F, 0.00029817F, 0.00029883F, 0.00029952F, 0.00030016F, 0.00030082F,
  0.00030151F, 0.00030235F, 0.00030305F, 0.00027794F, 0.00027837F, 0.00027881F,
  0.00027927F, 0.00027989F, 0.00028051F, 0.00028109F, 0.00028172F, 0.0002823F,
  0.00028291F, 0.00028352F, 0.00028413F, 0.00028474F, 0.00028535F, 0.00028595F,
  0.00028656F, 0.00028717F, 0.00028777F, 0.00028838F, 0.00028899F, 0.00028959F,
  0.00029021F, 0.00029081F, 0.00029143F, 0.00029202F, 0.00029265F, 0.00029323F,
  0.00029386F, 0.00029445F, 0.00029506F, 0.00029567F, 0.00029628F, 0.00029687F,
  0.00029758F, 0.00029837F, 0.00029915F, 0.00027531F, 0.00027578F, 0.00027626F,
  0.00027679F, 0.00027732F, 0.00027789F, 0.00027844F, 0.00027898F, 0.00027953F,
  0.00028007F, 0.00028061F, 0.00028116F, 0.0002817F, 0.00028225F, 0.0002828F,
  0.00028334F, 0.00028388F, 0.00028443F, 0.00028498F, 0.00028551F, 0.00028606F,
  0.00028662F, 0.00028714F, 0.00028769F, 0.00028826F, 0.00028877F, 0.00028934F,
  0.00028989F, 0.0002904F, 0.00029099F, 0.00029152F, 0.00029203F, 0.00029265F,
  0.00029336F, 0.00029413F, 0.00029493F, 0.00027259F, 0.00027305F, 0.00027354F,
  0.00027403F, 0.00027448F, 0.00027499F, 0.00027547F, 0.00027595F, 0.00027643F,
  0.00027691F, 0.00027739F, 0.00027788F, 0.00027837F, 0.00027886F, 0.00027934F,
  0.00027982F, 0.00028029F, 0.00028077F, 0.00028127F, 0.00028176F, 0.00028223F,
  0.0002827F, 0.0002832F, 0.00028369F, 0.00028414F, 0.00028464F, 0.00028514F,
  0.0002856F, 0.00028607F, 0.00028659F, 0.00028703F, 0.00028758F, 0.00028819F,
  0.00028892F, 0.00028969F, 0.00029049F, 0.00026972F, 0.00027013F, 0.00027056F,
  0.00027099F, 0.00027141F, 0.00027182F, 0.00027224F, 0.00027267F, 0.00027309F,
  0.00027351F, 0.00027394F, 0.00027436F, 0.00027477F, 0.00027518F, 0.00027559F,
  0.00027602F, 0.00027646F, 0.00027688F, 0.0002773F, 0.0002777F, 0.00027812F,
  0.00027856F, 0.00027898F, 0.00027939F, 0.0002798F, 0.00028024F, 0.00028067F,
  0.0002811F, 0.00028149F, 0.00028189F, 0.00028238F, 0.00028292F, 0.00028359F,
  0.00028433F, 0.0002851F, 0.00028589F, 0.00026663F, 0.00026698F, 0.00026734F,
  0.0002677F, 0.00026806F, 0.00026842F, 0.00026878F, 0.00026914F, 0.00026949F,
  0.00026985F, 0.0002702F, 0.00027056F, 0.00027091F, 0.00027128F, 0.00027165F,
  0.00027202F, 0.00027238F, 0.00027273F, 0.00027308F, 0.00027343F, 0.0002738F,
  0.00027417F, 0.00027453F, 0.00027489F, 0.00027523F, 0.00027559F, 0.00027597F,
  0.00027631F, 0.00027665F, 0.00027708F, 0.00027759F, 0.0002782F, 0.00027889F,
  0.00027963F, 0.00028039F, 0.00028117F, 0.00026332F, 0.00026361F, 0.00026391F,
  0.00026421F, 0.00026451F, 0.0002648F, 0.0002651F, 0.0002654F, 0.0002657F,
  0.00026599F, 0.00026629F, 0.00026658F, 0.00026688F, 0.00026719F, 0.00026749F,
  0.00026779F, 0.00026809F, 0.00026839F, 0.00026869F, 0.00026898F, 0.00026927F,
  0.00026958F, 0.00026988F, 0.00027018F, 0.00027049F, 0.00027079F, 0.00027106F,
  0.00027134F, 0.00027172F, 0.00027221F, 0.00027277F, 0.00027341F, 0.00027411F,
  0.00027484F, 0.0002756F, 0.00027636F, 0.00025983F, 0.00026007F, 0.00026031F,
  0.00026055F, 0.00026079F, 0.00026102F, 0.00026126F, 0.0002615F, 0.00026174F,
  0.00026198F, 0.00026221F, 0.00026245F, 0.00026268F, 0.00026292F, 0.00026315F,
  0.0002634F, 0.00026364F, 0.00026388F, 0.00026412F, 0.00026436F, 0.00026459F,
  0.00026483F, 0.00026506F, 0.0002653F, 0.00026555F, 0.00026577F, 0.00026601F,
  0.00026632F, 0.00026677F, 0.0002673F, 0.00026791F, 0.00026857F, 0.00026927F,
  0.00027F, 0.00027074F, 0.00027149F, 0.00025621F, 0.00025638F, 0.00025656F,
  0.00025674F, 0.00025692F, 0.0002571F, 0.00025728F, 0.00025746F, 0.00025764F,
  0.00025782F, 0.000258F, 0.00025817F, 0.00025835F, 0.00025853F, 0.00025871F,
  0.00025889F, 0.00025906F, 0.00025923F, 0.00025942F, 0.0002596F, 0.00025979F,
  0.00025996F, 0.00026014F, 0.00026033F, 0.00026048F, 0.00026066F, 0.00026091F,
  0.00026131F, 0.00026181F, 0.00026239F, 0.00026303F, 0.0002637F, 0.0002644F,
  0.00026511F, 0.00026583F, 0.00026656F, 0.00025249F, 0.00025261F, 0.00025273F,
  0.00025285F, 0.00025297F, 0.00025309F, 0.0002532F, 0.00025332F, 0.00025344F,
  0.00025356F, 0.00025367F, 0.0002538F, 0.00025392F, 0.00025404F, 0.00025416F,
  0.00025427F, 0.00025439F, 0.0002545F, 0.00025463F, 0.00025476F, 0.00025488F,
  0.00025499F, 0.0002551F, 0.00025521F, 0.00025535F, 0.00025552F, 0.00025588F,
  0.00025634F, 0.00025689F, 0.00025749F, 0.00025813F, 0.0002588F, 0.00025949F,
  0.00026019F, 0.00026089F, 0.00026159F, 0.00024874F, 0.00024877F, 0.00024882F,
  0.00024888F, 0.00024894F, 0.000249F, 0.00024906F, 0.00024912F, 0.00024918F,
  0.00024924F, 0.0002493F, 0.00024936F, 0.00024942F, 0.00024948F, 0.00024954F,
  0.0002496F, 0.00024966F, 0.00024972F, 0.00024978F, 0.00024984F, 0.00024988F,
  0.00024993F, 0.00025001F, 0.00025009F, 0.00025026F, 0.00025055F, 0.00025095F,
  0.00025145F, 0.00025201F, 0.00025261F, 0.00025325F, 0.0002539F, 0.00025457F,
  0.00025524F, 0.00025591F, 0.00025659F, 0.00024497F, 0.00024492F, 0.00024488F,
  0.00024488F, 0.00024488F, 0.00024489F, 0.00024489F, 0.00024489F, 0.00024489F,
  0.00024489F, 0.00024489F, 0.00024489F, 0.00024489F, 0.00024489F, 0.0002449F,
  0.0002449F, 0.00024491F, 0.00024491F, 0.00024489F, 0.00024488F, 0.00024486F,
  0.0002449F, 0.00024494F, 0.0002451F, 0.00024535F, 0.00024569F, 0.00024612F,
  0.00024662F, 0.00024717F, 0.00024776F, 0.00024837F, 0.000249F, 0.00024964F,
  0.00025028F, 0.00025092F, 0.00025156F, 0.00024121F, 0.00024109F, 0.00024096F,
  0.00024088F, 0.00024082F, 0.00024076F, 0.0002407F, 0.00024065F, 0.00024059F,
  0.00024054F, 0.00024049F, 0.00024043F, 0.00024038F, 0.00024032F, 0.00024026F,
  0.00024021F, 0.00024016F, 0.0002401F, 0.00024001F, 0.00023996F, 0.00023993F,
  0.00023994F, 0.00024006F, 0.00024028F, 0.00024057F, 0.00024094F, 0.00024137F,
  0.00024186F, 0.00024239F, 0.00024295F, 0.00024352F, 0.00024411F, 0.00024471F,
  0.00024531F, 0.0002459F, 0.0002465F, 0.00023749F, 0.00023729F, 0.00023711F,
  0.00023695F, 0.0002368F, 0.00023667F, 0.00023655F, 0.00023643F, 0.00023633F,
  0.00023622F, 0.00023612F, 0.00023601F, 0.00023589F, 0.00023578F, 0.00023566F,
  0.00023554F, 0.00023543F, 0.0002353F, 0.0002352F, 0.00023509F, 0.0002351F,
  0.00023519F, 0.00023536F, 0.00023561F, 0.00023592F, 0.00023629F, 0.00023671F,
  0.00023717F, 0.00023766F, 0.00023817F, 0.0002387F, 0.00023924F, 0.00023978F,
  0.00024033F, 0.00024088F, 0.00024142F, 0.00023379F, 0.00023355F, 0.00023332F,
  0.00023309F, 0.00023286F, 0.00023265F, 0.00023248F, 0.00023231F, 0.00023215F,
  0.00023199F, 0.00023182F, 0.00023164F, 0.00023147F, 0.00023128F, 0.00023111F,
  0.00023095F, 0.00023078F, 0.00023062F, 0.00023045F, 0.00023043F, 0.0002305F,
  0.00023063F, 0.00023083F, 0.00023108F, 0.00023138F, 0.00023173F, 0.00023212F,
  0.00023254F, 0.00023297F, 0.00023343F, 0.0002339F, 0.00023438F, 0.00023487F,
  0.00023535F, 0.00023584F, 0.00023633F, 0.00023012F, 0.00022985F, 0.00022958F,
  0.00022931F, 0.00022903F, 0.00022877F, 0.00022855F, 0.00022833F, 0.0002281F,
  0.00022787F, 0.00022763F, 0.00022738F, 0.00022714F, 0.0002269F, 0.00022665F,
  0.00022649F, 0.00022624F, 0.0002261F, 0.00022601F, 0.00022602F, 0.0002261F,
  0.00022624F, 0.00022644F, 0.00022668F, 0.00022695F, 0.00022726F, 0.0002276F,
  0.00022796F, 0.00022834F, 0.00022873F, 0.00022913F, 0.00022955F, 0.00022996F,
  0.00023038F, 0.0002308F, 0.00023122F, 0.00022648F, 0.00022619F, 0.00022591F,
  0.00022562F, 0.00022533F, 0.00022506F, 0.0002248F, 0.00022452F, 0.00022422F,
  0.0002239F, 0.00022357F, 0.00022325F, 0.00022297F, 0.00022271F, 0.00022245F,
  0.00022217F, 0.00022198F, 0.00022186F, 0.00022181F, 0.00022182F, 0.00022189F,
  0.00022202F, 0.00022218F, 0.00022238F, 0.00022261F, 0.00022287F, 0.00022314F,
  0.00022344F, 0.00022374F, 0.00022406F, 0.00022439F, 0.00022473F, 0.00022507F,
  0.00022541F, 0.00022576F, 0.0002261F, 0.00022287F, 0.00022258F, 0.00022229F,
  0.000222F, 0.00022172F, 0.00022145F, 0.00022117F, 0.00022086F, 0.00022049F,
  0.00022008F, 0.00021969F, 0.00021932F, 0.00021902F, 0.00021866F, 0.00021839F,
  0.00021815F, 0.00021797F, 0.00021785F, 0.0002178F, 0.00021779F, 0.00021784F,
  0.00021793F, 0.00021804F, 0.00021819F, 0.00021836F, 0.00021854F, 0.00021874F,
  0.00021896F, 0.00021919F, 0.00021943F, 0.00021968F, 0.00021993F, 0.00022019F,
  0.00022045F, 0.00022071F, 0.00022098F, 0.00021928F, 0.00021899F, 0.00021871F,
  0.00021843F, 0.00021816F, 0.00021789F, 0.00021762F, 0.00021732F, 0.00021694F,
  0.00021644F, 0.00021604F, 0.00021563F, 0.00021523F, 0.00021487F, 0.00021457F,
  0.00021433F, 0.00021415F, 0.00021402F, 0.00021395F, 0.00021392F, 0.00021392F,
  0.00021395F, 0.00021401F, 0.00021408F, 0.00021417F, 0.00021428F, 0.0002144F,
  0.00021453F, 0.00021467F, 0.00021482F, 0.00021499F, 0.00021515F, 0.00021532F,
  0.0002155F, 0.00021567F, 0.00021585F, 0.00021572F, 0.00021544F, 0.00021517F,
  0.0002149F, 0.00021463F, 0.00021437F, 0.0002141F, 0.00021382F, 0.0002135F,
  0.00021303F, 0.0002125F, 0.00021208F, 0.00021163F, 0.00021124F, 0.00021092F,
  0.00021067F, 0.00021048F, 0.00021034F, 0.00021024F, 0.00021017F, 0.00021012F,
  0.00021008F, 0.00021005F, 0.00021004F, 0.00021004F, 0.00021006F, 0.00021009F,
  0.00021013F, 0.00021018F, 0.00021025F, 0.00021032F, 0.00021039F, 0.00021047F,
  0.00021056F, 0.00021064F, 0.00021073F, 0.00021219F, 0.00021192F, 0.00021165F,
  0.00021138F, 0.00021112F, 0.00021086F, 0.00021059F, 0.00021029F, 0.00020995F,
  0.00020952F, 0.00020903F, 0.00020856F, 0.00020812F, 0.00020772F, 0.00020739F,
  0.00020713F, 0.00020692F, 0.00020677F, 0.00020663F, 0.00020651F, 0.00020639F,
  0.00020628F, 0.00020616F, 0.00020606F, 0.00020596F, 0.00020588F, 0.00020582F,
  0.00020577F, 0.00020573F, 0.00020569F, 0.00020567F, 0.00020565F, 0.00020563F,
  0.00020562F, 0.00020561F, 0.0002056F, 0.00020868F, 0.00020842F, 0.00020815F,
  0.00020788F, 0.00020762F, 0.00020735F, 0.00020706F, 0.00020675F, 0.00020639F,
  0.00020599F, 0.00020554F, 0.00020508F, 0.00020465F, 0.00020426F, 0.00020393F,
  0.00020366F, 0.00020344F, 0.00020326F, 0.0002031F, 0.00020292F, 0.00020273F,
  0.00020252F, 0.00020231F, 0.00020211F, 0.00020192F, 0.00020174F, 0.00020158F,
  0.00020143F, 0.00020129F, 0.00020116F, 0.00020104F, 0.00020092F, 0.00020081F,
  0.0002007F, 0.00020059F, 0.00020048F, 0.0002052F, 0.00020493F, 0.00020466F,
  0.00020439F, 0.00020412F, 0.00020384F, 0.00020354F, 0.00020321F, 0.00020285F,
  0.00020246F, 0.00020204F, 0.00020162F, 0.00020121F, 0.00020083F, 0.0002005F,
  0.00020022F, 0.00019999F, 0.00019978F, 0.00019959F, 0.00019937F, 0.00019908F,
  0.00019878F, 0.00019848F, 0.00019818F, 0.0001979F, 0.00019762F, 0.00019736F,
  0.00019712F, 0.00019688F, 0.00019665F, 0.00019643F, 0.00019621F, 0.00019599F,
  0.00019578F, 0.00019557F, 0.00019536F, 0.00020172F, 0.00020145F, 0.00020118F,
  0.0002009F, 0.00020062F, 0.00020033F, 0.00020002F, 0.00019968F, 0.00019933F,
  0.00019895F, 0.00019856F, 0.00019817F, 0.00019778F, 0.00019742F, 0.00019709F,
  0.0001968F, 0.00019654F, 0.0001963F, 0.00019606F, 0.00019578F, 0.00019542F,
  0.00019504F, 0.00019465F, 0.00019426F, 0.00019389F, 0.00019352F, 0.00019317F,
  0.00019282F, 0.00019248F, 0.00019215F, 0.00019183F, 0.00019151F, 0.00019119F,
  0.00019088F, 0.00019056F, 0.00019025F, 0.00019825F, 0.00019797F, 0.0001977F,
  0.00019741F, 0.00019713F, 0.00019682F, 0.00019651F, 0.00019617F, 0.00019583F,
  0.00019547F, 0.0001951F, 0.00019473F, 0.00019436F, 0.00019401F, 0.00019368F,
  0.00019336F, 0.00019307F, 0.00019278F, 0.00019247F, 0.00019212F, 0.00019172F,
  0.00019127F, 0.00019082F, 0.00019035F, 0.00018989F, 0.00018943F, 0.00018898F,
  0.00018854F, 0.0001881F, 0.00018767F, 0.00018724F, 0.00018682F, 0.0001864F,
  0.00018598F, 0.00018556F, 0.00018514F, 0.00019478F, 0.0001945F, 0.00019422F,
  0.00019393F, 0.00019363F, 0.00019333F, 0.00019301F, 0.00019268F, 0.00019234F,
  0.000192F, 0.00019165F, 0.00019129F, 0.00019094F, 0.00019059F, 0.00019025F,
  0.00018991F, 0.00018958F, 0.00018923F, 0.00018886F, 0.00018844F, 0.00018799F,
  0.00018749F, 0.00018697F, 0.00018644F, 0.00018589F, 0.00018535F, 0.00018481F,
  0.00018427F, 0.00018373F, 0.0001832F, 0.00018267F, 0.00018214F, 0.00018161F,
  0.00018109F, 0.00018056F, 0.00018004F, 0.00019132F, 0.00019103F, 0.00019074F,
  0.00019045F, 0.00019015F, 0.00018984F, 0.00018953F, 0.0001892F, 0.00018888F,
  0.00018854F, 0.0001882F, 0.00018786F, 0.00018751F, 0.00018716F, 0.00018681F,
  0.00018644F, 0.00018606F, 0.00018566F, 0.00018523F, 0.00018476F, 0.00018424F,
  0.0001837F, 0.00018312F, 0.00018251F, 0.0001819F, 0.00018127F, 0.00018064F,
  0.00018F, 0.00017937F, 0.00017874F, 0.0001781F, 0.00017747F, 0.00017684F,
  0.0001762F, 0.00017557F, 0.00017494F, 0.00018785F, 0.00018755F, 0.00018726F,
  0.00018696F, 0.00018666F, 0.00018636F, 0.00018605F, 0.00018574F, 0.00018542F,
  0.0001851F, 0.00018477F, 0.00018443F, 0.00018408F, 0.00018373F, 0.00018335F,
  0.00018296F, 0.00018254F, 0.00018208F, 0.00018159F, 0.00018106F, 0.0001805F,
  0.00017989F, 0.00017925F, 0.00017859F, 0.0001779F, 0.00017719F, 0.00017647F,
  0.00017575F, 0.00017501F, 0.00017428F, 0.00017354F, 0.0001728F, 0.00017206F,
  0.00017132F, 0.00017058F, 0.00016985F, 0.00018437F, 0.00018408F, 0.00018378F,
  0.00018349F, 0.00018319F, 0.00018289F, 0.00018258F, 0.00018228F, 0.00018197F,
  0.00018166F, 0.00018133F, 0.000181F, 0.00018065F, 0.00018028F, 0.00017989F,
  0.00017946F, 0.000179F, 0.0001785F, 0.00017796F, 0.00017737F, 0.00017675F,
  0.00017609F, 0.00017539F, 0.00017465F, 0.00017389F, 0.00017311F, 0.0001723F,
  0.00017149F, 0.00017066F, 0.00016982F, 0.00016898F, 0.00016814F, 0.00016729F,
  0.00016645F, 0.0001656F, 0.00016475F, 0.0001809F, 0.0001806F, 0.0001803F,
  0.00018001F, 0.00017971F, 0.00017942F, 0.00017912F, 0.00017882F, 0.00017852F,
  0.00017822F, 0.0001779F, 0.00017757F, 0.00017722F, 0.00017683F, 0.00017642F,
  0.00017596F, 0.00017546F, 0.00017491F, 0.00017432F, 0.00017368F, 0.000173F,
  0.00017228F, 0.00017152F, 0.00017072F, 0.00016989F, 0.00016902F, 0.00016814F,
  0.00016723F, 0.00016631F, 0.00016537F, 0.00016443F, 0.00016348F, 0.00016253F,
  0.00016157F, 0.00016062F, 0.00015966F, 0.00017743F, 0.00017713F, 0.00017683F,
  0.00017653F, 0.00017624F, 0.00017595F, 0.00017566F, 0.00017537F, 0.00017508F,
  0.00017478F, 0.00017447F, 0.00017414F, 0.00017378F, 0.00017338F, 0.00017294F,
  0.00017245F, 0.00017191F, 0.00017132F, 0.00017068F, 0.00016999F, 0.00016925F,
  0.00016847F, 0.00016765F, 0.00016678F, 0.00016588F, 0.00016494F, 0.00016397F,
  0.00016297F, 0.00016196F, 0.00016092F, 0.00015988F, 0.00015882F, 0.00015776F,
  0.0001567F, 0.00015563F, 0.00015457F } ;/* Referenced by: '<S48>/LdMapp' */

float32 MCCM_facCCMLq_Z_T[1296] = { 0.00095308F, 0.00096545F, 0.0009778F,
  0.00099011F, 0.0010023F, 0.0010144F, 0.0010261F, 0.0010375F, 0.0010484F,
  0.0010587F, 0.0010685F, 0.0010777F, 0.0010865F, 0.0010949F, 0.0011031F,
  0.0011113F, 0.0011196F, 0.0011281F, 0.0011368F, 0.0011455F, 0.0011532F,
  0.0011582F, 0.0011559F, 0.0011381F, 0.001095F, 0.0011054F, 0.0011119F,
  0.0011182F, 0.0011271F, 0.0011386F, 0.001147F, 0.0011611F, 0.0011717F,
  0.0011834F, 0.0011964F, 0.0011961F, 0.00092829F, 0.00093994F, 0.00095159F,
  0.0009632F, 0.00097473F, 0.0009861F, 0.00099721F, 0.0010079F, 0.0010182F,
  0.0010278F, 0.0010368F, 0.0010454F, 0.0010535F, 0.0010613F, 0.0010689F,
  0.0010764F, 0.0010838F, 0.001091F, 0.001098F, 0.0011047F, 0.0011105F,
  0.0011143F, 0.0011171F, 0.0011244F, 0.0011449F, 0.0011472F, 0.0011503F,
  0.0011516F, 0.0011535F, 0.0011561F, 0.0011553F, 0.0011559F, 0.0011551F,
  0.0011567F, 0.0011496F, 0.0011577F, 0.00090351F, 0.00091446F, 0.0009254F,
  0.00093631F, 0.00094715F, 0.00095784F, 0.00096829F, 0.00097838F, 0.00098795F,
  0.00099682F, 0.0010051F, 0.001013F, 0.0010205F, 0.0010277F, 0.0010347F,
  0.0010414F, 0.001048F, 0.0010541F, 0.0010597F, 0.001065F, 0.0010701F,
  0.0010747F, 0.0010795F, 0.0010828F, 0.001082F, 0.0010861F, 0.0010895F,
  0.0010935F, 0.0010963F, 0.0010988F, 0.0011017F, 0.0011041F, 0.0011061F,
  0.001107F, 0.0011106F, 0.0011081F, 0.00087875F, 0.00088904F, 0.0008993F,
  0.00090951F, 0.00091963F, 0.00092962F, 0.00093936F, 0.00094872F, 0.00095756F,
  0.00096563F, 0.00097321F, 0.00098046F, 0.00098743F, 0.00099412F, 0.0010005F,
  0.0010066F, 0.0010124F, 0.0010179F, 0.001023F, 0.0010279F, 0.0010325F,
  0.0010368F, 0.0010407F, 0.0010447F, 0.0010493F, 0.0010523F, 0.0010551F,
  0.0010572F, 0.0010594F, 0.0010613F, 0.0010627F, 0.0010638F, 0.0010648F,
  0.0010653F, 0.0010659F, 0.0010637F, 0.00085405F, 0.00086371F, 0.00087334F,
  0.00088286F, 0.00089224F, 0.00090146F, 0.00091045F, 0.00091895F, 0.00092659F,
  0.00093409F, 0.00094106F, 0.00094789F, 0.00095441F, 0.00096062F, 0.00096656F,
  0.0009722F, 0.00097754F, 0.00098261F, 0.00098738F, 0.00099187F, 0.00099606F,
  0.00099994F, 0.0010036F, 0.0010068F, 0.0010095F, 0.0010123F, 0.0010147F,
  0.001017F, 0.0010189F, 0.0010205F, 0.0010218F, 0.0010228F, 0.0010235F,
  0.0010242F, 0.0010239F, 0.0010222F, 0.00082947F, 0.00083855F, 0.00084759F,
  0.00085648F, 0.00086509F, 0.00087348F, 0.00088157F, 0.00088912F, 0.00089631F,
  0.00090332F, 0.00090996F, 0.00091633F, 0.00092244F, 0.00092825F, 0.00093375F,
  0.000939F, 0.00094396F, 0.0009486F, 0.00095299F, 0.00095708F, 0.00096087F,
  0.00096441F, 0.00096761F, 0.00097061F, 0.00097333F, 0.00097571F, 0.00097778F,
  0.00097957F, 0.00098105F, 0.00098231F, 0.00098316F, 0.0009839F, 0.00098438F,
  0.00098429F, 0.00098325F, 0.00098244F, 0.00080509F, 0.00081361F, 0.00082211F,
  0.00083047F, 0.00083833F, 0.00084597F, 0.00085341F, 0.00086043F, 0.00086731F,
  0.0008738F, 0.00088003F, 0.00088598F, 0.00089166F, 0.00089705F, 0.00090221F,
  0.00090702F, 0.00091155F, 0.00091588F, 0.00091984F, 0.00092355F, 0.00092702F,
  0.00093015F, 0.00093305F, 0.00093559F, 0.00093797F, 0.00093989F, 0.00094177F,
  0.00094316F, 0.00094441F, 0.00094534F, 0.00094595F, 0.00094628F, 0.00094643F,
  0.00094588F, 0.00094515F, 0.00094453F, 0.00078104F, 0.00078906F, 0.00079699F,
  0.0008047F, 0.00081225F, 0.00081934F, 0.00082627F, 0.00083292F, 0.00083928F,
  0.00084538F, 0.00085122F, 0.0008568F, 0.00086209F, 0.00086704F, 0.0008718F,
  0.00087623F, 0.00088047F, 0.00088432F, 0.00088796F, 0.00089137F, 0.00089441F,
  0.00089718F, 0.00089981F, 0.00090205F, 0.00090395F, 0.00090583F, 0.00090714F,
  0.0009083F, 0.00090932F, 0.00090977F, 0.00091015F, 0.00091033F, 0.00090996F,
  0.00090951F, 0.00090898F, 0.00090843F, 0.00075747F, 0.00076511F, 0.0007726F,
  0.00077986F, 0.00078701F, 0.00079368F, 0.0008002F, 0.00080644F, 0.00081241F,
  0.00081812F, 0.00082358F, 0.00082872F, 0.00083359F, 0.00083818F, 0.00084254F,
  0.00084664F, 0.00085052F, 0.00085409F, 0.00085731F, 0.00086028F, 0.00086312F,
  0.00086566F, 0.00086776F, 0.00086968F, 0.0008715F, 0.00087286F, 0.00087391F,
  0.00087488F, 0.00087555F, 0.00087576F, 0.00087593F, 0.0008756F, 0.00087544F,
  0.000875F, 0.00087449F, 0.00087398F, 0.00073464F, 0.00074201F, 0.00074915F,
  0.00075605F, 0.00076264F, 0.00076903F, 0.00077513F, 0.00078096F, 0.00078651F,
  0.0007918F, 0.00079687F, 0.00080164F, 0.00080622F, 0.00081052F, 0.00081458F,
  0.00081828F, 0.00082169F, 0.00082487F, 0.00082786F, 0.00083067F, 0.0008331F,
  0.00083515F, 0.00083705F, 0.00083877F, 0.00084024F, 0.00084126F, 0.00084207F,
  0.00084265F, 0.00084313F, 0.00084324F, 0.00084288F, 0.00084278F, 0.00084246F,
  0.00084202F, 0.00084154F, 0.00084105F, 0.00071294F, 0.00071995F, 0.00072668F,
  0.00073317F, 0.00073937F, 0.00074533F, 0.00075105F, 0.00075651F, 0.0007617F,
  0.00076666F, 0.00077137F, 0.00077584F, 0.00078003F, 0.00078392F, 0.00078752F,
  0.00079089F, 0.00079405F, 0.00079698F, 0.00079967F, 0.00080211F, 0.00080419F,
  0.00080601F, 0.00080761F, 0.00080898F, 0.0008102F, 0.00081107F, 0.00081157F,
  0.00081199F, 0.00081216F, 0.00081172F, 0.00081153F, 0.00081127F, 0.0008109F,
  0.00081046F, 0.00080998F, 0.00080949F, 0.0006923F, 0.0006988F, 0.00070512F,
  0.0007112F, 0.00071702F, 0.00072261F, 0.00072793F, 0.00073304F, 0.00073787F,
  0.00074248F, 0.00074683F, 0.00075096F, 0.00075481F, 0.00075834F, 0.00076165F,
  0.00076473F, 0.00076756F, 0.00077013F, 0.0007725F, 0.00077466F, 0.00077657F,
  0.0007781F, 0.00077939F, 0.0007805F, 0.00078139F, 0.00078198F, 0.00078242F,
  0.00078259F, 0.00078207F, 0.00078171F, 0.00078143F, 0.0007811F, 0.00078069F,
  0.00078022F, 0.00077972F, 0.0007792F, 0.00067248F, 0.00067848F, 0.00068441F,
  0.00069012F, 0.00069558F, 0.00070079F, 0.00070573F, 0.00071048F, 0.00071495F,
  0.0007192F, 0.00072321F, 0.00072698F, 0.00073054F, 0.00073387F, 0.0007369F,
  0.00073964F, 0.00074215F, 0.00074445F, 0.00074651F, 0.00074834F, 0.00074991F,
  0.00075127F, 0.00075245F, 0.00075327F, 0.00075377F, 0.00075405F, 0.00075443F,
  0.00075388F, 0.00075342F, 0.00075305F, 0.00075267F, 0.00075224F, 0.00075174F,
  0.00075121F, 0.00075064F, 0.00075007F, 0.00065341F, 0.00065899F, 0.00066455F,
  0.00066988F, 0.00067499F, 0.00067986F, 0.00068445F, 0.00068885F, 0.00069299F,
  0.00069693F, 0.00070061F, 0.00070406F, 0.00070729F, 0.00071027F, 0.00071301F,
  0.00071551F, 0.00071781F, 0.00071991F, 0.00072166F, 0.00072316F, 0.00072445F,
  0.00072559F, 0.00072651F, 0.00072705F, 0.00072729F, 0.0007277F, 0.00072735F,
  0.00072681F, 0.00072627F, 0.00072574F, 0.0007252F, 0.00072462F, 0.000724F,
  0.00072334F, 0.00072267F, 0.00072199F, 0.0006351F, 0.00064024F, 0.00064541F,
  0.00065041F, 0.00065516F, 0.00065971F, 0.00066399F, 0.00066809F, 0.00067196F,
  0.00067561F, 0.000679F, 0.00068211F, 0.000685F, 0.00068766F, 0.00069012F,
  0.00069238F, 0.00069445F, 0.00069629F, 0.00069779F, 0.00069907F, 0.00070014F,
  0.00070101F, 0.00070177F, 0.0007021F, 0.00070231F, 0.0007023F, 0.00070176F,
  0.00070109F, 0.00070038F, 0.00069966F, 0.00069892F, 0.00069816F, 0.00069736F,
  0.00069655F, 0.00069572F, 0.00069489F, 0.00061756F, 0.00062227F, 0.00062704F,
  0.00063171F, 0.00063613F, 0.00064037F, 0.00064436F, 0.00064815F, 0.00065172F,
  0.00065507F, 0.00065819F, 0.00066104F, 0.00066365F, 0.00066605F, 0.00066824F,
  0.00067025F, 0.00067206F, 0.00067367F, 0.00067491F, 0.00067596F, 0.00067681F,
  0.00067755F, 0.00067806F, 0.00067804F, 0.00067809F, 0.00067785F, 0.00067727F,
  0.0006765F, 0.00067563F, 0.0006747F, 0.00067374F, 0.00067276F, 0.00067176F,
  0.00067074F, 0.00066972F, 0.00066869F, 0.0006008F, 0.00060512F, 0.00060945F,
  0.00061376F, 0.00061789F, 0.00062182F, 0.00062551F, 0.00062899F, 0.00063227F,
  0.00063534F, 0.00063823F, 0.00064081F, 0.00064317F, 0.00064533F, 0.00064729F,
  0.00064906F, 0.00065065F, 0.00065199F, 0.00065304F, 0.00065387F, 0.0006544F,
  0.0006551F, 0.00065496F, 0.000655F, 0.00065488F, 0.00065448F, 0.0006538F,
  0.00065291F, 0.00065188F, 0.00065075F, 0.00064956F, 0.00064834F, 0.00064709F,
  0.00064584F, 0.00064458F, 0.00064332F, 0.00058474F, 0.00058867F, 0.0005926F,
  0.00059655F, 0.00060036F, 0.00060399F, 0.00060739F, 0.00061059F, 0.00061361F,
  0.00061643F, 0.00061903F, 0.00062139F, 0.00062353F, 0.00062547F, 0.0006272F,
  0.00062875F, 0.00063015F, 0.00063125F, 0.00063207F, 0.00063281F, 0.00063332F,
  0.00063369F, 0.00063346F, 0.00063318F, 0.00063278F, 0.00063216F, 0.00063132F,
  0.00063027F, 0.00062904F, 0.00062769F, 0.00062626F, 0.00062478F, 0.00062328F,
  0.00062176F, 0.00062023F, 0.00061871F, 0.00056928F, 0.00057287F, 0.00057646F,
  0.00058003F, 0.00058351F, 0.00058684F, 0.00058998F, 0.00059293F, 0.00059571F,
  0.00059829F, 0.00060065F, 0.00060277F, 0.00060469F, 0.00060643F, 0.00060794F,
  0.00060927F, 0.00061051F, 0.00061127F, 0.00061212F, 0.00061244F, 0.00061294F,
  0.00061311F, 0.00061289F, 0.00061241F, 0.00061173F, 0.00061085F, 0.00060977F,
  0.00060849F, 0.00060704F, 0.00060544F, 0.00060376F, 0.00060201F, 0.00060022F,
  0.00059842F, 0.00059661F, 0.00059479F, 0.00055434F, 0.00055763F, 0.00056091F,
  0.00056415F, 0.00056732F, 0.00057038F, 0.00057327F, 0.00057598F, 0.00057852F,
  0.00058088F, 0.00058303F, 0.00058492F, 0.00058662F, 0.00058812F, 0.00058946F,
  0.00059077F, 0.00059165F, 0.00059236F, 0.00059278F, 0.00059322F, 0.00059352F,
  0.00059352F, 0.00059319F, 0.00059254F, 0.00059161F, 0.00059045F, 0.00058908F,
  0.00058752F, 0.00058579F, 0.00058393F, 0.00058196F, 0.00057992F, 0.00057784F,
  0.00057574F, 0.00057363F, 0.00057152F, 0.00053984F, 0.00054286F, 0.00054587F,
  0.00054883F, 0.00055174F, 0.00055455F, 0.00055723F, 0.00055973F, 0.00056205F,
  0.00056417F, 0.00056609F, 0.00056779F, 0.0005693F, 0.00057059F, 0.00057165F,
  0.00057285F, 0.00057345F, 0.00057422F, 0.0005747F, 0.00057502F, 0.00057511F,
  0.0005749F, 0.00057436F, 0.00057348F, 0.00057229F, 0.00057083F, 0.00056915F,
  0.00056727F, 0.00056523F, 0.00056306F, 0.00056079F, 0.00055845F, 0.00055607F,
  0.00055366F, 0.00055123F, 0.00054881F, 0.0005257F, 0.00052849F, 0.00053126F,
  0.00053401F, 0.0005367F, 0.00053932F, 0.00054181F, 0.00054412F, 0.00054624F,
  0.00054814F, 0.00054982F, 0.00055132F, 0.00055272F, 0.0005539F, 0.00055495F,
  0.00055576F, 0.0005565F, 0.00055715F, 0.00055759F, 0.00055777F, 0.00055763F,
  0.00055717F, 0.00055636F, 0.00055519F, 0.00055369F, 0.0005519F, 0.00054988F,
  0.00054766F, 0.00054528F, 0.00054278F, 0.00054019F, 0.00053753F, 0.00053483F,
  0.0005321F, 0.00052936F, 0.00052662F, 0.00051188F, 0.00051446F, 0.00051703F,
  0.00051959F, 0.00052211F, 0.00052457F, 0.00052692F, 0.00052909F, 0.00053102F,
  0.00053271F, 0.00053421F, 0.00053548F, 0.00053682F, 0.00053772F, 0.00053884F,
  0.00053975F, 0.0005405F, 0.00054106F, 0.00054137F, 0.00054136F, 0.00054098F,
  0.00054022F, 0.00053908F, 0.00053757F, 0.00053571F, 0.00053356F, 0.00053117F,
  0.00052859F, 0.00052586F, 0.00052301F, 0.00052008F, 0.00051709F, 0.00051407F,
  0.00051101F, 0.00050795F, 0.00050488F, 0.00049831F, 0.00050072F, 0.00050312F,
  0.00050552F, 0.00050788F, 0.0005102F, 0.00051243F, 0.00051451F, 0.00051634F,
  0.00051781F, 0.00051922F, 0.0005204F, 0.00052152F, 0.00052254F, 0.00052358F,
  0.00052453F, 0.00052528F, 0.00052576F, 0.00052592F, 0.00052569F, 0.00052503F,
  0.00052394F, 0.00052243F, 0.00052051F, 0.00051826F, 0.00051571F, 0.00051294F,
  0.00050998F, 0.00050688F, 0.00050368F, 0.00050041F, 0.00049708F, 0.00049372F,
  0.00049034F, 0.00048695F, 0.00048356F, 0.00048497F, 0.00048723F, 0.00048948F,
  0.00049172F, 0.00049394F, 0.00049613F, 0.00049824F, 0.00050025F, 0.00050206F,
  0.00050343F, 0.00050453F, 0.00050573F, 0.00050685F, 0.00050794F, 0.00050898F,
  0.00050992F, 0.00051066F, 0.00051108F, 0.00051109F, 0.00051063F, 0.00050967F,
  0.0005082F, 0.00050626F, 0.00050391F, 0.00050122F, 0.00049826F, 0.00049509F,
  0.00049175F, 0.00048829F, 0.00048473F, 0.00048111F, 0.00047745F, 0.00047375F,
  0.00047004F, 0.00046631F, 0.00046259F, 0.00047182F, 0.00047393F, 0.00047605F,
  0.00047815F, 0.00048024F, 0.00048229F, 0.00048427F, 0.00048613F, 0.0004878F,
  0.00048917F, 0.00049033F, 0.00049148F, 0.00049262F, 0.00049374F, 0.00049479F,
  0.00049574F, 0.00049646F, 0.00049684F, 0.00049673F, 0.00049604F, 0.00049474F,
  0.00049284F, 0.00049044F, 0.00048763F, 0.0004845F, 0.00048112F, 0.00047756F,
  0.00047384F, 0.00047001F, 0.0004661F, 0.00046214F, 0.00045813F, 0.00045409F,
  0.00045005F, 0.00044599F, 0.00044193F, 0.00045882F, 0.00046081F, 0.00046279F,
  0.00046477F, 0.00046672F, 0.00046863F, 0.00047047F, 0.00047219F, 0.00047375F,
  0.00047513F, 0.00047637F, 0.00047754F, 0.00047869F, 0.0004798F, 0.00048085F,
  0.00048178F, 0.00048248F, 0.00048284F, 0.00048265F, 0.00048174F, 0.00048004F,
  0.00047768F, 0.0004748F, 0.00047154F, 0.00046799F, 0.00046422F, 0.00046027F,
  0.00045619F, 0.000452F, 0.00044774F, 0.00044343F, 0.00043908F, 0.00043471F,
  0.00043033F, 0.00042594F, 0.00042155F, 0.00044595F, 0.00044781F, 0.00044968F,
  0.00045153F, 0.00045335F, 0.00045513F, 0.00045684F, 0.00045845F, 0.00045994F,
  0.00046131F, 0.00046259F, 0.00046379F, 0.00046493F, 0.00046602F, 0.00046702F,
  0.00046789F, 0.00046853F, 0.00046883F, 0.00046859F, 0.00046748F, 0.00046534F,
  0.00046251F, 0.00045921F, 0.00045555F, 0.00045162F, 0.00044747F, 0.00044317F,
  0.00043874F, 0.00043421F, 0.00042961F, 0.00042496F, 0.00042027F, 0.00041556F,
  0.00041085F, 0.00040612F, 0.00040139F, 0.00043317F, 0.00043492F, 0.00043667F,
  0.0004384F, 0.00044011F, 0.00044178F, 0.00044337F, 0.00044489F, 0.00044633F,
  0.00044769F, 0.00044896F, 0.00045016F, 0.00045127F, 0.0004523F, 0.00045321F,
  0.00045395F, 0.00045444F, 0.00045457F, 0.00045416F, 0.00045284F, 0.00045035F,
  0.00044719F, 0.00044355F, 0.00043957F, 0.00043531F, 0.00043084F, 0.0004262F,
  0.00042144F, 0.00041658F, 0.00041165F, 0.00040667F, 0.00040165F, 0.00039661F,
  0.00039156F, 0.0003865F, 0.00038144F, 0.00042045F, 0.0004221F, 0.00042375F,
  0.00042538F, 0.00042699F, 0.00042855F, 0.00043006F, 0.00043151F, 0.0004329F,
  0.00043421F, 0.00043545F, 0.00043661F, 0.00043766F, 0.00043858F, 0.00043935F,
  0.00043989F, 0.00044013F, 0.00043995F, 0.00043914F, 0.0004375F, 0.00043492F,
  0.00043161F, 0.00042777F, 0.00042354F, 0.00041901F, 0.00041426F, 0.00040933F,
  0.00040426F, 0.00039908F, 0.00039383F, 0.00038852F, 0.00038318F, 0.00037781F,
  0.00037243F, 0.00036703F, 0.00036164F, 0.00040778F, 0.00040934F, 0.00041089F,
  0.00041244F, 0.00041395F, 0.00041544F, 0.00041687F, 0.00041826F, 0.00041959F,
  0.00042085F, 0.00042203F, 0.0004231F, 0.00042404F, 0.00042482F, 0.00042539F,
  0.00042568F, 0.0004256F, 0.00042503F, 0.00042383F, 0.00042189F, 0.00041919F,
  0.00041579F, 0.00041183F, 0.00040743F, 0.0004027F, 0.0003977F, 0.0003925F,
  0.00038715F, 0.00038168F, 0.00037612F, 0.0003705F, 0.00036483F, 0.00035913F,
  0.00035342F, 0.00034769F, 0.00034197F, 0.00039513F, 0.00039661F, 0.00039809F,
  0.00039955F, 0.000401F, 0.00040241F, 0.00040379F, 0.00040511F, 0.00040638F,
  0.00040757F, 0.00040866F, 0.00040962F, 0.00041041F, 0.000411F, 0.00041132F,
  0.00041131F, 0.00041088F, 0.00040993F, 0.00040838F, 0.00040617F, 0.00040331F,
  0.00039981F, 0.00039576F, 0.00039123F, 0.00038633F, 0.00038113F, 0.0003757F,
  0.00037009F, 0.00036434F, 0.00035849F, 0.00035256F, 0.00034657F, 0.00034055F,
  0.00033451F, 0.00032845F, 0.00032239F, 0.0003825F, 0.00038391F, 0.00038532F,
  0.00038672F, 0.0003881F, 0.00038946F, 0.00039077F, 0.00039204F, 0.00039323F,
  0.00039433F, 0.00039531F, 0.00039613F, 0.00039675F, 0.00039711F, 0.00039716F,
  0.00039683F, 0.00039604F, 0.00039474F, 0.00039288F, 0.00039042F, 0.00038737F,
  0.00038374F, 0.00037958F, 0.00037494F, 0.0003699F, 0.00036453F, 0.0003589F,
  0.00035305F, 0.00034704F, 0.0003409F, 0.00033467F, 0.00032837F, 0.00032203F,
  0.00031566F, 0.00030927F, 0.00030288F, 0.00036988F, 0.00037123F, 0.00037258F,
  0.00037392F, 0.00037524F, 0.00037654F, 0.0003778F, 0.00037901F, 0.00038013F,
  0.00038113F, 0.00038198F, 0.00038264F, 0.00038305F, 0.00038317F, 0.00038292F,
  0.00038227F, 0.00038115F, 0.00037952F, 0.00037735F, 0.00037465F, 0.0003714F,
  0.00036763F, 0.00036335F, 0.0003586F, 0.00035343F, 0.00034791F, 0.00034209F,
  0.00033603F, 0.00032977F, 0.00032335F, 0.00031682F, 0.00031021F, 0.00030355F,
  0.00029685F, 0.00029014F, 0.00028342F, 0.00035726F, 0.00035855F, 0.00035984F,
  0.00036113F, 0.0003624F, 0.00036365F, 0.00036486F, 0.000366F, 0.00036704F,
  0.00036794F, 0.00036866F, 0.00036914F, 0.00036934F, 0.00036919F, 0.00036865F,
  0.00036767F, 0.00036622F, 0.00036427F, 0.00036183F, 0.00035888F, 0.00035544F,
  0.0003515F, 0.00034709F, 0.00034222F, 0.00033693F, 0.00033127F, 0.00032527F,
  0.000319F, 0.0003125F, 0.00030582F, 0.000299F, 0.00029208F, 0.00028509F,
  0.00027807F, 0.00027102F, 0.00026397F, 0.00034464F, 0.00034588F, 0.00034711F,
  0.00034835F, 0.00034957F, 0.00035077F, 0.00035192F, 0.000353F, 0.00035396F,
  0.00035475F, 0.00035533F, 0.00035564F, 0.00035561F, 0.0003552F, 0.00035436F,
  0.00035306F, 0.00035128F, 0.00034903F, 0.0003463F, 0.00034311F, 0.00033947F,
  0.00033537F, 0.00033082F, 0.00032583F, 0.00032042F, 0.00031462F, 0.00030845F,
  0.00030197F, 0.00029523F, 0.00028828F, 0.00028117F, 0.00027395F, 0.00026664F,
  0.00025929F, 0.00025192F, 0.00024454F } ;/* Referenced by: '<S48>/LqMapp' */

float32 MCCM_facLPFiDAct_Y_T[11] = { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
  1.0F, 1.0F, 1.0F, 1.0F } ;     /* Referenced by: '<S45>/CCM_facLPFiDAct_T1' */

float32 MCCM_facLPFiQAct_Y_T[11] = { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
  1.0F, 1.0F, 1.0F, 1.0F } ;     /* Referenced by: '<S45>/CCM_facLPFiQAct_T1' */

float32 MROT_ParkCompAngle_Y_rad[20] = { 0.035F, 0.017F, 0.0035F, -0.011F,
  -0.025F, -0.0395F, -0.0535F, -0.0675F, -0.0815F, -0.0955F, -0.1095F, -0.1245F,
  -0.1388F, -0.153F, -0.1673F, -0.1815F, -0.1958F, -0.2101F, -0.225F, -0.2386F }
;                                  /* Referenced by: '<S20>/1-D Lookup Table' */

float32 MROT_VolPosnOffsWiSpd_Y_deg[20] = { 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F,
  1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F,
  1.5F } ;                        /* Referenced by: '<S20>/1-D Lookup Table2' */

float32 SampleTimeFOC = 0.1F;          /* Referenced by: '<S47>/Constant10' */

#define SWC_ETE_type_STOP_SEC_CAL
#include "SWC_ETE_type_MemMap.h"

/* PublicStructure Variables for Internal Data */
ARID_DEF_SWC_ETE_type_T SWC_ETE_type_ARID_DEF;

/* Model step function */
void run_FOC(void)
{
  /* RootInportFunctionCallGenerator generated from: '<Root>/run_FOC' incorporates:
   *  SubSystem: '<Root>/run_FOC_sys'
   */
  /* Outputs for Atomic SubSystem: '<S2>/MTPA_FOC' */
  SWC_ETE_type_MTPA_FOC();

  /* End of Outputs for SubSystem: '<S2>/MTPA_FOC' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/run_FOC' */

  /* Outport: '<Root>/P_HiRateTxLoRateRx_HiRateTxLoRateRx' */
  SWC_ETE_type_ARID_DEF.P_HiRateTxLoRateRx_HiRateTxLoRa =
    SWC_ETE_type_ARID_DEF.BusCreator;
  (void)Rte_Write_P_HiRateTxLoRateRx_HiRateTxLoRateRx
    (&SWC_ETE_type_ARID_DEF.P_HiRateTxLoRateRx_HiRateTxLoRa);
}

/* Model initialize function */
void SWC_ETE_type_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/run_FOC' incorporates:
   *  SubSystem: '<Root>/run_FOC_sys'
   */
  /* SystemInitialize for Atomic SubSystem: '<S2>/MTPA_FOC' */
  SWC_ETE_type_MTPA_FOC_Init();

  /* End of SystemInitialize for SubSystem: '<S2>/MTPA_FOC' */
  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/run_FOC' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
