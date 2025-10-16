%===========$Update Time :  2025-09-09 16:55:01 $=========
disp('Loading $Id: dgh_var.m  2025-09-09 16:55:01    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KDGH_bRstRteFault_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_FaultLevel2_flg_ovrdflg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_FaultLevel2_flg_ovrdval', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_OverCurrent_A', 	'A',    0,    1000,    'single',    '');
a2l_par('KDGH_OverCurrentHeal_C', 	'cnt',    -1000,    0,    'int16',    '');
a2l_par('KDGH_OverCurrentErr_C', 	'cnt',    0,    1000,    'int16',    '');
a2l_par('KDGH_RstPhaCurrOver_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_PhaCurrOverU_A', 	'A',    0,    5000,    'single',    '');
a2l_par('KDGH_PhaCurrOverV_A', 	'A',    0,    5000,    'single',    '');
a2l_par('KDGH_PhaCurrOverW_A', 	'A',    0,    5000,    'single',    '');
a2l_par('KDGH_OverCurrent_flg_ovrdflg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_OverCurrent_flg_ovrdval', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_SumErr_A', 	'A',    0,    1000,    'single',    '');
a2l_par('KDGH_SumErrHeal_C', 	'cnt',    -1000,    0,    'int16',    '');
a2l_par('KDGH_SumErrErr_C', 	'cnt',    0,    1000,    'int16',    '');
a2l_par('KDGH_RstSumErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_SumErr_flg_ovrdflg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KDGH_SumErr_flg_ovrdval', 	'flg',    0,    1,    'boolean',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VDGH_CurrFaultLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_PosSenrFaultLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_HWHsideFltLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_HWLsideFltLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_HWOverVoltFltLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_RteFault_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_100usFaultLevel2_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_FaultLevel2_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_PhaCurrOverDQ_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_PhaCurrOverU_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_PhaCurrOverV_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_PhaCurrOverW_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_OverCurrent_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_SumErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_CurOffsErrLat_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VDGH_SumErrPhCurU_A', 	'A',    -100000,    100000,    'single',    '');
a2l_mon('VDGH_SumErrPhCurV_A', 	'A',    -100000,    100000,    'single',    '');
a2l_mon('VDGH_SumErrPhCurW_A', 	'A',    -100000,    100000,    'single',    '');

%% Outputs Signals
% Outputs Signals %
