%===========$Update Time :  2025-08-22 18:10:19 $=========
disp('Loading $Id: rot_var.m  2025-08-22 18:10:19    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KROT_SpdCutoffFreq_Hz', 	'Hz',    0,    100000,    'single',    '');
a2l_par('KROT_RotSpdMRaw_rpm_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KROT_RotSpdMRaw_rpm_ovrdval', 	'rpm',    0,    100000,    'single',    '');
a2l_par('AROT_ParkCompAngle_X_rpm', 	'rpm',    0,    100000,    'single',    '');
a2l_par('MROT_ParkCompAngle_Y_rad', 	'rad',    -7,    7,    'single',    '');
a2l_par('MROT_VolPosnOffsWiSpd_Y_deg', 	'deg',    0,    1000,    'single',    '');
a2l_par('KROT_RotAngleE_rad_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KROT_RotAngleE_rad_ovrdval', 	'rad',    -20,    20,    'single',    '');
a2l_par('KROT_agOffset_C', 	'rad',    -20,    20,    'single',    '');
a2l_par('KROT_bUseVariableFc_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KROT_CurLoopPrd_t', 	's',    0,    1,    'single',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VROT_RotAngleERaw_rad', 	'rad',    -10,    10,    'single',    '');
a2l_mon('VROT_RotSpdERaw_rads', 	'rads',    -100000,    100000,    'single',    '');
a2l_mon('VROT_RotSpdM_rpm', 	'rpm',    -100000,    100000,    'single',    '');
a2l_mon('VROT_RotSpdE_rads', 	'rads',    -100000,    100000,    'single',    '');
a2l_mon('VROT_RotAngleE_rad', 	'rad',    -10,    10,    'single',    '');
a2l_mon('VROT_RotAngleV_rad', 	'rad',    -10,    10,    'single',    '');
a2l_mon('VROT_FreqPWM_Tick', 	'Tick',    0,    100000,    'uint32',    '');
a2l_mon('VROT_FreqPWM_Hz', 	'Hz',    0,    10000,    'uint16',    '');
a2l_mon('VROT_RotAgECompV_rad', 	'rad',    -10,    10,    'single',    '');
a2l_mon('VROT_RotAgECompL_rad', 	'rad',    -10,    10,    'single',    '');

%% Outputs Signals
% Outputs Signals %
