%===========$Update Time :  2025-09-11 12:53:10 $=========
disp('Loading $Id: llc_var.m  2025-09-11 12:53:10    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('LLCM_tlvtrATemp_C', 	'degC',    -500,    500,    'single',    '');
a2l_par('LLCM_tlvtrBTemp_C', 	'degC',    -500,    500,    'single',    '');
a2l_par('LLCM_tlvtrCTemp_C', 	'degC',    -500,    500,    'single',    '');
a2l_par('LLCM_volfcooltFlowMax_C', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('LLCM_volfcooltFlowMin_C', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('LLCM_volfcooltFlowRampUp_C', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('LLCM_volfcooltFlowRampDown_C', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('LLCM_bTcooltFlowTrig_C', 	'flg',    0,    1,    'boolean',    '');
a2l_par('LLCM_volfcooltFlowMor_C', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('ALLC_volCoolFlowWater_X_kW', 	'kW',    -100,    100,    'single',    '');
a2l_par('ALLC_volCoolFlowWater_Y_degC', 	'degC',    -500,    500,    'single',    '');
a2l_par('MLLC_volCoolFlowWater_Z_M', 	'M',    -100,    100,    'single',    '');
a2l_par('ALLC_volCoolFlowOil_X_degC', 	'degC',    -500,    500,    'single',    '');
a2l_par('MLLC_volCoolFlowOil_Y_T', 	'flow',    -1000,    1000,    'single',    '');
a2l_par('ALLC_volfCooltFlow_X_degC', 	'degC',    -500,    500,    'single',    '');
a2l_par('MLLC_volfCooltFlow_Y_T', 	'flow',    -1000,    1000,    'single',    '');

%% Monitored Signals
% Internal Signals %

%% Outputs Signals
% Outputs Signals %
a2l_mon('VLLC_volfCooltFlowTar_C', 	'C',    -1000,    1000,    'single',    '');
