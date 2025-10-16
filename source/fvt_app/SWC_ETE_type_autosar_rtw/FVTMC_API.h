#ifndef __FVTMC_API_H_
#define __FVTMC_API_H_

/*#include <stdint.h>*/
#include <Platform_Types.h>
#include <stdbool.h>

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* Define quantity of Rx message and channel*/
#define APP_MAJOR 1
#define APP_MINOR 0
#define APP_PATCH 0 

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*typedef float float32;
typedef uint32 uint32;*/
typedef struct
{
    float32 real;               /**< \brief Real part */
    float32 imag;               /**< \brief Imaginary part */
} cfloat32;

typedef enum
{
    GateDriverPos_uHS = 0,
    GateDriverPos_uLS,
    GateDriverPos_vHS,
    GateDriverPos_vLS,
    GateDriverPos_wHS,
    GateDriverPos_wLS,
    GateDriverPos_Count,
} GateDriver_Position_Fake;

typedef enum 
{
    ADC_PHASE_U = 0u,
    ADC_PHASE_V,
    ADC_PHASE_W,
    ADC_PHASE_COUNT,
 } Adc_Phase_Current_Num_Fake;

typedef struct
{
    uint32  u32_Reg;
    uint32  u32_Mv;
    float32 f32_Phy;
} EvAdc_SignalDataType_Fake;

typedef enum
{
    PMIC_5V8_SIGNAL = 0u,
    KL15_SIGNAL,
    KL30_SIGNAL,
    HV_LV_13V5_SIGNAL,
    QUC_1V25_SIGNAL,
    QUC_3V3_SIGNAL,
    QUC_5V0_SIGNAL,
    QVR_5V0_SIGNAL,
    QT1_5V0_SIGNAL,
    QT2_SIGNAL,
    QCO_5V0_SIGNAL,
    BOOST_LDO_12V0_SIGNAL,
    BOOST_21V5_SIGNAL,
    HV_U_SIGNAL,
    HV_V_SIGNAL,
    CURRENT_U_IO_SIGNAL,
    CURRENT_V_IO_SIGNAL,
    CURRENT_W_IO_SIGNAL,
    SIN_P_SIGNAL,
    SIN_N_SIGNAL,
    COS_P_SIGNAL,
    COS_N_SIGNAL,
    EXC_P_SIGNAL,
    EXC_N_SIGNAL,
    TEMP_MCU_SIGNAL,
    TEMP_FLYBACK_SIGNAL,
    TEMP_OIL_SIGNAL,
    TEMP_M_U_SIGNAL,
    TEMP_M_V_SIGNAL,
    TEMP_M_W_SIGNAL,
    TEMP_SIC_U_SIGNAL,
    TEMP_SIC_V_SIGNAL,
    TEMP_SIC_W_SIGNAL,
    SYSTEM_ADC_SIGNAL_COUNT,
} System_Adc_Signal_Fake;


/*==================================================================================================
*                                    Infenion API
==================================================================================================*/
extern void Ifx_SvmF32_init(void);
extern void Ifx_SvmF32_do(cfloat32 m, uint32 period, uint32* timerValues);

/*==================================================================================================
*                                    PWM API
==================================================================================================*/

/*==================================================================================================
*                                    ADC API
==================================================================================================*/
extern uint8 read_phase_current_sync_result(EvAdc_SignalDataType_Fake phCurrent[ADC_PHASE_COUNT]);
extern void calculate_all_adc_system_signal(void);
extern EvAdc_SignalDataType_Fake read_adc_system_value(System_Adc_Signal_Fake eSignal);

/*==================================================================================================
*                                    Resolver API
==================================================================================================*/
extern uint8 start_resolver_excitation_signal(void);
extern uint8 stop_resolver_excitation_signal(void);
extern uint8 resolver_feedback_dsadc_calibration(void);
extern void dsadc_read_resolver_feedback(sint16* s16sinfbk, sint16* s16cosfbk, uint32* u32rdcTimestamp);
extern float32 EdsadcRdc_Atan2(float32 f32X_Data, float32 f32Y_Data);

/*==================================================================================================
*                                    Gatedriver API
==================================================================================================*/


/*extern float32  Ifx_SvmF32_getVoltage(float32 m, float32 vdc);*/
/*extern cfloat32 Ifx_SvmF32_getVoltages(cfloat32 m, float32 vdc);*/
/*extern cfloat32 Ifx_SvmF32_getModIndex(cfloat32 v, float32 vdc);*/


#endif
