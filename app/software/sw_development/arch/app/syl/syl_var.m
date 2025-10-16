%===========$Update Time :  2025-09-11 10:26:33 $=========
disp('Loading $Id: syl_var.m  2025-09-11 10:26:33    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KSYL_nTMSpdMin_RPM', 	'rpm',    -20000,    0,    'single',    '');
a2l_par('KSYL_nTMSpdMax_RPM', 	'rpm',    0,    20000,    'single',    '');
a2l_par('KSYL_frqSwitchMax_Hz', 	'Hz',    0,    10000,    'single',    '');
a2l_par('ASYL_TrqMax_X_V', 	'V',    0,    700,    'single',    '');
a2l_par('ASYL_TrqMax_Y_rpm', 	'rpm',    0,    20000,    'single',    '');
a2l_par('MSYL_TrqMax_Z_Nm', 	'Nm',    0,    500,    'single',    '');
a2l_par('ASYL_TrqMin_X_V', 	'V',    0,    700,    'single',    '');
a2l_par('ASYL_TrqMin_Y_rpm', 	'rpm',    0,    20000,    'single',    '');
a2l_par('MSYL_TrqMin_Z_Nm', 	'Nm',    -500,    0,    'single',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VSYL_nTMSpdMin_RPM', 	'RPM',    -100000,    100000,    'single',    '');
a2l_mon('VSYL_nTMSpdMax_RPM', 	'RPM',    -100000,    100000,    'single',    '');
a2l_mon('VSYL_frqSwitchMax_Hz', 	'Hz',    -100000,    100000,    'single',    '');
a2l_mon('VSYL_facTorqueCoef_null', 	'null',    0,    1,    'single',    '');

%% Outputs Signals
% Outputs Signals %
a2l_mon('VSYL_tqTMTqMax_Nm', 	'Nm',    -100000,    100000,    'single',    '');
a2l_mon('VSYL_tqTMTqMin_Nm', 	'Nm',    -100000,    100000,    'single',    '');
