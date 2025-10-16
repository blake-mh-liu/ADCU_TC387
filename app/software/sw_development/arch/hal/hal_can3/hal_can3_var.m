%===========$Update Time :  2025-09-12 09:32:07 $=========
disp('Loading $Id: hal_can3_var.m  2025-09-12 09:32:07    foxtron $      FVT_export_businfo_v3.0 2022-09-06')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('KHAL_CAN3BMS1E2E_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_par('KHAL_CAN3BMS6E2E_flg', 	'flg',    0,    1,    'boolean',    '');

%% Monitored Signals
% Internal Signals %

%% Outputs Signals
% Outputs Signals %
a2l_mon('VHAL_CANMsgInvalidBMS1_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_BMS1CSErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_BMS1RCErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_HVBattVolt_V', 	'V',    0,    819,    'single',    '');
a2l_mon('VHAL_CANMsgInvalidBMS6_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_BMS6CSErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_BMS6RCErr_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_HVBContactorSta_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_CANMsgInvalidFD3C1000_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_BatteryMode_enum', 	'enum',    0,    5,    'uint8',    '');
a2l_mon('VHAL_RrCoolantflow_Lpmin', 	'Lpmin',    0,    15.75,    'single',    '');
a2l_mon('VHAL_RrCoolanttemp_C', 	'C',    -40,    214,    'single',    '');
a2l_mon('VHAL_CANMsgInvalidFD3VCU1_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_ActiveDischReq_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_CSVCU1_enum', 	'enum',    0,    255,    'uint8',    '');
a2l_mon('VHAL_PwrSta_enum', 	'enum',    0,    7,    'uint8',    '');
a2l_mon('VHAL_RCVCU1_enum', 	'enum',    0,    14,    'uint8',    '');
a2l_mon('VHAL_ShiftGearPosn_enum', 	'enum',    0,    7,    'uint8',    '');
a2l_mon('VHAL_CANMsgInvalidFD3VCU2_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_CSVCU2CAN1_enum', 	'enum',    0,    255,    'uint8',    '');
a2l_mon('VHAL_RCVCU2CAN1_enum', 	'enum',    0,    14,    'uint8',    '');
a2l_mon('VHAL_RrActvDmpDisabReq_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_RrMCUEnaReq_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_CANMsgInvalidFD3VCU5_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_FDCVCURrSpdMaxReq_rpm', 	'rpm',    0,    65535,    'single',    '');
a2l_mon('VHAL_FDCVCURrSpdMinReq_rpm', 	'rpm',    -22000,    43535,    'single',    '');
a2l_mon('VHAL_FDCVCURrTMCtrlModeReq_enum', 	'enum',    0,    7,    'uint8',    '');
a2l_mon('VHAL_FDCVCURrTMSpdReq_rpm', 	'rpm',    -22000,    43535,    'single',    '');
a2l_mon('VHAL_FDCVCURrTMTqReq_Nm', 	'Nm',    -1000,    5553.5,    'single',    '');
a2l_mon('VHAL_FDCVCURrTqMaxReq_Nm', 	'Nm',    0,    4095,    'single',    '');
a2l_mon('VHAL_FDCVCURrTqMinReq_Nm', 	'Nm',    -1022,    3073,    'single',    '');
a2l_mon('VHAL_CANMsgInvalidGW3CE1000_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VHAL_IVITimeDay_DAY', 	'DAY',    0,    31,    'single',    '');
a2l_mon('VHAL_IVITimeHour_hr', 	'hr',    0,    31,    'single',    '');
a2l_mon('VHAL_IVITimeMinute_min', 	'min',    0,    63,    'single',    '');
a2l_mon('VHAL_IVITimeMonth_MONTH', 	'MONTH',    0,    12,    'single',    '');
a2l_mon('VHAL_IVITimeSecond_s', 	's',    0,    63,    'single',    '');
a2l_mon('VHAL_VehSpeed_kph', 	'kph',    0,    255.875,    'single',    '');
