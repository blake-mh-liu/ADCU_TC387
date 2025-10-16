%% Header defining EBUS constants

% =========== $Id: vcu_local_hdr.m 1295 2014-07-10 03:09:34Z fenix $  =========
disp('Loading $Id: vcu_local_hdr.m 1295 2021-01-12 03:09:34Z foxtron $')

%-----------------------------
% General global constants
%-----------------------------

TRUE                 = boolean( 1 );
FALSE                = boolean( 0 );

ZERO_FLOAT          = single(0);
ZERO_INT            = uint8(0);
ONE_INT             = uint8(1);

ONE_PERCENT         = single( 0.01 );
HUNDRED             = single( 100 );
PI                  = single( pi );
GRAVITY_G           = single( 9.8 );
HALF_PI             = single( pi/2 );
TWO_PI              = single( 2*pi);
MINUSONE_PI         = single( -pi);

MINUSONE_FLOAT      = single(-1);
ONE_FLOAT           = single(1);
TWO_FLOAT           = single(2);

OPENLOOP_VD_CMD     = single(0);
OPENLOOP_VQ_CMD     = single(24*0.9);

% global VFOC_VQcmd_V;
% VFOC_VQcmd_V = Simulink.Signal;
% VFOC_VQcmd_V.CoderInfo.StorageClass = 'ExportedGlobal';
% VFOC_VQcmd_V.DataType = 'single';
% 
% global VFOC_VDcmd_V;
% VFOC_VDcmd_V = Simulink.Signal;
% VFOC_VDcmd_V.CoderInfo.StorageClass = 'ExportedGlobal';
% VFOC_VDcmd_V.DataType = 'single';
% 
% global VFOC_DCbusVolt_V;
% VFOC_DCbusVolt_V = Simulink.Signal;
% VFOC_DCbusVolt_V.CoderInfo.StorageClass = 'ExportedGlobal';
% VFOC_DCbusVolt_V.DataType = 'single';
% 
% global VFOC_FakeSpd_rpm;
% VFOC_FakeSpd_rpm = Simulink.Signal;
% VFOC_FakeSpd_rpm.CoderInfo.StorageClass = 'ExportedGlobal';
% VFOC_FakeSpd_rpm.DataType = 'single';



%-----------------------------
% Vehicle Parameters
%-----------------------------


%-----------------------------
% Unit conversion constants
%-----------------------------

KPH2MPS             = single( 1000/3600 );
%KPH2RPM             = single( 100/(12*pi*TIRE_RADIUS));
MPH2KPH             = single( 1.6093    );
MPS2KPH             = single( 1/KPH2MPS );
KPH2MPH             = single( 1/MPH2KPH );
RPM2RADPS           = single( 2*pi/60   );
RADPS2RPM           = single( 1/RPM2RADPS);
DEG2RAD             = single( pi/180    );
RAD2DEG             = single( 180/pi    );
W2KW                = single( 1/1000    ); % Will remove after later software review
XX2KXX              = single( 1e-3      );
KXX2XX              = single( 1000      );


EPSILON             = single( 1e-6      );
HOUR2SEC            = single( 3600      );
MIN2SEC             = single( 60	   );

Hr2min              = single( 60	   );
Hr2sec              = single( 3600	   );
W2Wh                = single(0.005/3600);
W2kW                = single(0.001);
pct                 = single(100);

INCH2MM             = single(25.4);
MM2METER            = single(0.001);
RADIUS2DIAMETER     = single(2);
DIAMETER2RADIUS     = single(0.5);
TimeoutOccurred     = uint8(64);

%-----------------------------
% CAN API constants
%-----------------------------
CANFDArray = zeros(1,64);

%-----------------------------
% PWM API constants
%-----------------------------
PWM_DutyCmd_Array = uint32(zeros(1,3));
PWM_Period_inTick = uint32(5000);

%-----------------------------
% ADC API constants
%-----------------------------
ADC_Vdc = uint16(0);
ADC_PhCurrent_Array = int16(zeros(1,3));

%-----------------------------
% RDC API constants
%-----------------------------
RDC_sin_fbk = int16(0);
RDC_cos_fbk = int16(0);
RDC_TimeStamp = uint32(0);

%#########################################################################
% Model execution period
%#########################################################################

C_TICK_TIME_S                    = single(0.001);
C_TASK_5MS_S                     = (	C_TICK_TIME_S      	)	;
C_TASK_10MS_S                    = (	C_TICK_TIME_S * 2  	)	;
C_TASK_100MS_S                   = (	C_TICK_TIME_S * 20 	)	;
C_TASK_1000MS_S                  = (	C_TICK_TIME_S * 200	)	;
C_TASK_30000MS_S                  = (	C_TICK_TIME_S * 6000	)	;
C_TASK_31000MS_S                  = (	C_TICK_TIME_S * 6200	)	;
C_FOC_SAMPLE_TIME                 = single(0.0001);
SPD_GAIN                          = single(2*pi/60);

GRC_FAKE_SAMPLE_TIME              = single(1);
%#########################################################################
% Model ENUMs
%#########################################################################

%% -------------------------FOC---------------------------------------
% VFOC_SensorMode_enum
ENUM_SENSORMODE_RDC                         = uint8(  0  );
ENUM_SENSORFOCMODE_FAKERDC                  = uint8(  1  );
ENUM_SENSORFOCMODE_CURRENTRDCTEMP           = uint8(  2  );
ENUM_SENSORFOCMODE_RDCALIGN                 = uint8(  3  );

% VFOC_RDCMode_enum
ENUM_RDCMODE_RAWRDC                         = uint8(  0  );
ENUM_RDCMODE_ANGLETRACK                     = uint8(  1  );

% VFOC_RUNMode_enum
ENUM_RUNMODE_OPENLOOP                       = uint8(  0  );
ENUM_RUNMODE_TQ                             = uint8(  1  );
ENUM_RUNMODE_TQSPD                          = uint8(  2  );

% VFOC_CurFilterType_enum
ENUM_CURFILTERTYPE_NOFILTER                 = uint8(  0  );  
ENUM_CURFILTERTYPE_LOWPASS                  = uint8(  1  );
ENUM_CURFILTERTYPE_IIR                      = uint8(  2  );

%% -------------------------OPM---------------------------------------
% VOPM_MotMod_enum
ENUM_MOTMOD_INIT                           = uint8(  0  );
ENUM_MOTMOD_STANDBY                        = uint8(  1  );
ENUM_MOTMOD_READY                          = uint8(  2  );
ENUM_MOTMOD_TQCTROL                        = uint8(  3  );
ENUM_MOTMOD_SPDCTRL                        = uint8(  4  );
ENUM_MOTMOD_FAILURE                        = uint8(  5  );
ENUM_MOTMOD_AFTERRUN                       = uint8(  6  );
ENUM_MOTMOD_DISCHARGE                      = uint8(  7  );
ENUM_MOTMOD_RESOLVERADJUST                 = uint8(  8  );
ENUM_MOTMOD_DIAGSERV                       = uint8(  9  );
ENUM_MOTMOD_EMERPWRDOWN                    = uint8(  10  );
ENUM_MOTMOD_HEATING                        = uint8(  11  );
ENUM_MOTMOD_BOOSTCHRG                      = uint8(  12  );
ENUM_MOTMOD_RESD0D                         = uint8(  13  );
ENUM_MOTMOD_RESD0E                         = uint8(  14  );
ENUM_MOTMOD_INVALID                        = uint8(  15  );

% VOPM_IVTROpMode_enum
ENUM_IVTROPMODE_FW                              = uint8(  0  );
ENUM_IVTROPMODE_DTCYCTRL                        = uint8(  1  );
ENUM_IVTROPMODE_ASCLO                           = uint8(  2  );
ENUM_IVTROPMODE_ASCHI                           = uint8(  3  );
ENUM_IVTROPMODE_FLTMOD                          = uint8(  4  );
ENUM_IVTROPMODE_IVTROFF                         = uint8(  5  );
ENUM_IVTROPMODE_ASC                             = uint8(  6  );

%% -------------------------VCU---------------------------------------
% VVCU_GearPosn_enum
ENUM_GEARPOSN_PARK                              = uint8(  0  );
ENUM_GEARPOSN_INVALID                           = uint8(  1  );
ENUM_GEARPOSN_NOUSE02                           = uint8(  2  );
ENUM_GEARPOSN_NOUSE03                           = uint8(  3  );
ENUM_GEARPOSN_NEUT                              = uint8(  4  );
ENUM_GEARPOSN_DRIVE                             = uint8(  5  );
ENUM_GEARPOSN_FAILR                             = uint8(  6  );
ENUM_GEARPOSN_RVS                               = uint8(  7  );

% VVCU_CtrlMode_enum
ENUM_CTRLMODE_TQMODE                            = uint8(  0  );
ENUM_CTRLMODE_SPDMODE                           = uint8(  1  );
ENUM_CTRLMODE_RESD02                            = uint8(  2  );
ENUM_CTRLMODE_RESD03                            = uint8(  3  );
ENUM_CTRLMODE_EMGYPWRDOWN                       = uint8(  4  );
ENUM_CTRLMODE_HEATGMOD                          = uint8(  5  );
ENUM_CTRLMODE_BOOSTMOD                          = uint8(  6  );
ENUM_CTRLMODE_INVLD                             = uint8(  7  );