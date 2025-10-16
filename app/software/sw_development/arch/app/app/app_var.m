%===========$Update Time :  2025-09-11 10:09:05 $=========
disp('Loading $Id: app_var.m  2025-09-11 10:09:05    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KAPP_ADCKL30_enum', 	'enum',    0,    32,    'uint8',    '');
a2l_par('KAPP_ADCKL15_enum', 	'enum',    0,    32,    'uint8',    '');

%% Monitored Signals
% Internal Signals %

%% Outputs Signals
% Outputs Signals %
a2l_mon('VAPP_iDCurrAct_A', 	'A',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_iQCurrAct_A', 	'A',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_ADCKL30_V', 	'V',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_ADCKL15_V', 	'V',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_uDC_V', 	'V',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_RotSpd_rpm', 	'rpm',    -100000,    100000,    'single',    '');
a2l_mon('VAPP_OilTemp_degC', 	'degC',    -100000,    100000,    'single',    '');
