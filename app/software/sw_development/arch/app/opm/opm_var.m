%===========$Update Time :  2025-09-10 11:57:45 $=========
disp('Loading $Id: opm_var.m  2025-09-10 11:57:45    foxtron $      FVT_export_businfo_v2.0 2021-11-02')
%% Calibration Name, Units, Min, Max, Data Type, Comment
a2l_par('OpMod_bDcha2AfterRunMor_C', 	'flag',    0,    1,    'boolean',    '');
a2l_par('OpMod_nRot2AfterRun_C', 	'cnt',    0,    100000,    'single',    '');
a2l_par('OpMod_uDCSide2AfterRun_C', 	'cnt',    0,    100000,    'single',    '');
a2l_par('OpMod_tiDcha2AfterRun_C', 	'cnt',    0,    100000,    'single',    '');
a2l_par('OpMod_bService_C', 	'flag',    0,    1,    'boolean',    '');
a2l_par('OpMod_ResolverEnt_C', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_MotMod_enum_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_MotMod_enum_ovrdval', 	'enum',    0,    15,    'uint8',    '');
a2l_par('KOPM_PsvDischrgEna_flg_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_PsvDischrgEna_flg_ovrdval', 	'flag',    0,    1,    'boolean',    '');
a2l_par('OpMod_nRotASCEna_C', 	'cnt',    0,    100000,    'single',    '');
a2l_par('OpMod_nRotASCDi_C', 	'cnt',    0,    100000,    'single',    '');
a2l_par('KOPM_IVTROpMode_enum_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_IVTROpMode_enum_ovrdval', 	'enum',    0,    6,    'uint8',    '');
a2l_par('KOPM_FakeCtrlModCmd_enum', 	'enum',    0,    6,    'uint8',    '');
a2l_par('KOPM_FakeGearPosn_enum', 	'enum',    0,    10,    'uint8',    '');
a2l_par('KOPM_FakeBMSContrClosed_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_FakeKL15_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_FakeMCUEna_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_FakeActDmpReq_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_FakeActvDchaReq_flg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_MCUSysSta_enum_ovrdflg', 	'flag',    0,    1,    'boolean',    '');
a2l_par('KOPM_MCUSysSta_enum_ovrdval', 	'enum',    0,    15,    'uint8',    '');

%% Monitored Signals
% Internal Signals %
a2l_mon('VOPM_PsvDischrgEna_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VOPM_CurLoopEna_flg', 	'flg',    0,    1,    'boolean',    '');

%% Outputs Signals
% Outputs Signals %
a2l_mon('VOPM_MotMod_enum', 	'enum',    0,    255,    'uint8',    '');
a2l_mon('VOPM_IVTROpMode_enum', 	'enum',    0,    255,    'uint8',    '');
a2l_mon('VOPM_MCUEna_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VOPM_TMReady_flg', 	'flg',    0,    1,    'boolean',    '');
a2l_mon('VOPM_BoostOPSta_flg', 	'flg',    0,    1,    'boolean',    '');
