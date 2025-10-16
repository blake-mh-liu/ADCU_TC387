%===========$Update Time :  2025-09-11 12:53:03 $=========
disp('Loading $Id: eop_var.m  2025-09-11 12:53:03    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('AEOP_nRrOilTempSpdMod_X_degC', 	'degC',    -500,    500,    'single',    '');
a2l_par('AEOP_nRrOilTempSpdMod_Y_KW', 	'kW',    -100,    100,    'single',    '');
a2l_par('MEOP_nRrOilTempSpdMod_Z_M', 	'M',    -10000,    10000,    'single',    '');
a2l_par('MEOP_nRrOilTempMotOptMod_Z_M', 	'M',    -10000,    10000,    'single',    '');
a2l_par('MEOP_nRrOilTempDetOptMod_Z_M', 	'M',    -10000,    10000,    'single',    '');
a2l_par('AEOP_nRrTMTempSpdMod_X_degC', 	'degC',    -500,    500,    'single',    '');
a2l_par('MEOP_nRrTMTempSpdMod_Y_T', 	'T',    -10000,    10000,    'single',    '');
a2l_par('MEOP_nRrTMTempMotOptMod_Y_T', 	'T',    -10000,    10000,    'single',    '');
a2l_par('MEOP_nRrOilTempDetOptMod_Y_T', 	'T',    -10000,    10000,    'single',    '');
a2l_par('EopC_rSpdRampUp_C', 	'rpm',    0,    50000,    'single',    '');
a2l_par('EopC_rSpdRampDown_C', 	'rpm',    -50000,    0,    'single',    '');
a2l_par('AEOP_nReqMotSpdMax_X_A', 	'degC',    -500,    500,    'single',    '');
a2l_par('MEOP_nReqMotSpdMax_Y_T', 	'rpm',    -10000,    10000,    'single',    '');
a2l_par('EopC_nReqMotSpdMin_C', 	'rpm',    -10000,    10000,    'single',    '');
a2l_par('EopC_nReqMotSpdTrig_C', 	'flg',    0,    1,    'boolean',    '');
a2l_par('EopC_nReqMotSpdMan_C', 	'rpm',    -10000,    10000,    'single',    '');
a2l_par('EopC_bMotEnaManTrig_C', 	'flg',    0,    1,    'boolean',    '');
a2l_par('EopC_bMotEnaMan_C', 	'flg',    0,    1,    'boolean',    '');

%% Monitored Signals
% Internal Signals %

%% Outputs Signals
% Outputs Signals %
a2l_mon('VEOP_bMotEnaReq_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VEOP_nEOPSpdReq_rpm', 	'rpm',    -100000,    100000,    'single',    '');
