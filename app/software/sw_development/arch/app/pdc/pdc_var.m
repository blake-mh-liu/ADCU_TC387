%===========$Update Time :  2025-08-28 20:35:16 $=========
disp('Loading $Id: pdc_var.m  2025-08-28 20:35:16    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KPDC_nPosnErrMaxSpd_C', 	'rpm',    0,    30000,    'single',    '');
a2l_par('KDSM_bIvtrTarHiDebug_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KDSM_DiagSpdH_rpm', 	'rpm',    0,    30000,    'single',    '');
a2l_par('KDSM_DiagSpdL_rpm', 	'rpm',    0,    30000,    'single',    '');
a2l_par('KPDC_FWCnt_C', 	'cnt',    0,    255,    'uint8',    '');
a2l_par('KPDC_facScalePWM_C', 	'factor',    0,    100,    'single',    '');
a2l_par('KeSVMR_PWMPrd_cnt', 	'cnt',    0,    60000,    'uint16',    '');
a2l_par('KeSVMR_FullDTCCurr_A', 	'A',    0,    10000,    'single',    '');
a2l_par('KeSVMR_t_DeadTime', 	's',    0,    1,    'single',    '');
a2l_par('KeSVMR_b_UseStrictClamp', 	'tbd',    0,    100,    'single',    '');
a2l_par('KeSVMR_StrClampMinDuty_pct', 	'factor',    0,    1,    'single',    '');
a2l_par('KeSVMR_StrClampMaxDuty_pct', 	'factor',    0,    1,    'single',    '');
a2l_par('KeSVMR_t_MinPulseWidth', 	's',    0,    1,    'single',    '');
a2l_par('KeMCCR_b_UseMeasCrntDTC', 	'cnt',    0,    255,    'uint8',    '');
a2l_par('KOSP_IvtrTarMor_enum_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOSP_IvtrTarMor_enum_ovrdval', 	'enum',    0,    10,    'uint8',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VPDC_bASCFlgRaw_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPDC_Ivtr1ModCmd_enum', 	'enum',    0,    10,    'uint8',    '');
a2l_mon('VPDC_DutyA_raw', 	'raw',    0,    1,    'single',    '');
a2l_mon('VPDC_DutyB_raw', 	'raw',    0,    1,    'single',    '');
a2l_mon('VPDC_DutyC_raw', 	'raw',    0,    1,    'single',    '');

%% Outputs Signals
% Outputs Signals %
