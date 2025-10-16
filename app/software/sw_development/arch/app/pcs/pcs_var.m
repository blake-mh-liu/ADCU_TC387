%===========$Update Time :  2025-09-09 15:51:32 $=========
disp('Loading $Id: pcs_var.m  2025-09-09 15:51:32    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KPCS_EnaSnsrSelfLrn_flg_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KPCS_EnaSnsrSelfLrn_flg_ovrdval', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KPCS_OffsFilTi_cnt', 	'cnt',    0,    60000,    'uint16',    '');
a2l_par('KPCS_OffsFilCoeff_fac', 	'factor',    0,    1,    'single',    '');
a2l_par('KPCS_PhaseCurSnsrVolVldMax_V', 	'V',    0,    100,    'single',    '');
a2l_par('KPCS_PhaseCurSnsrVolVldMin_V', 	'V',    -100,    0,    'single',    '');
a2l_par('KPCS_PhaseCurSnsrVolDft_V', 	'V',    -100,    100,    'single',    '');
a2l_par('KPCS_bCurOffsVolVld_flg_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KPCS_bCurOffsVolVld_flg_ovrdval', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KPCS_WCurSnsr_Gain', 	'gain',    0,    10,    'single',    '');
a2l_par('KPCS_VCurSnsr_Gain', 	'gain',    0,    10,    'single',    '');
a2l_par('KPCS_UCurSnsr_Gain', 	'gain',    0,    10,    'single',    '');
a2l_par('KPCS_MaxCurrReset_flg', 	'flag',    0,    1,    'boolean',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VPCS_EnaSnsrSelfLrn_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_SnsrSelfLrnCompl_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_UCurOffsRaw_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_VCurOffsRaw_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_WCurOffsRaw_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_bCurOffsVolVld_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_UCurOffsFil_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_VCurOffsFil_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_WCurOffsFil_V', 	'V',    -100,    100,    'single',    '');
a2l_mon('VPCS_PhaUCur_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_PhaVCur_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_PhaWCur_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_UCurOffsVolVld_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_VCurOffsVolVld_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_WCurOffsVolVld_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VPCS_MaxPhaCur_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_MaxPhaCurU_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_MaxPhaCurV_A', 	'A',    -10000000,    10000000,    'single',    '');
a2l_mon('VPCS_MaxPhaCurW_A', 	'A',    -10000000,    10000000,    'single',    '');

%% Outputs Signals
% Outputs Signals %
