//===========$Update Time :  2022-04-06 10:28:19 $=========
#include "FVTMC_API.h"
#include <string.h>

/*==================================================================================================
*                                    Infenion API
==================================================================================================*/
/* System related APIs */
void  Ifx_SvmF32_init(void)
{}
void Ifx_SvmF32_do(cfloat32 m, uint32 period, uint32* timerValues)
{}

/*==================================================================================================
*                                    PWM API
==================================================================================================*/


/*==================================================================================================
*                                    ADC API
==================================================================================================*/
uint8 read_phase_current_sync_result(EvAdc_SignalDataType_Fake phCurrent[ADC_PHASE_COUNT])
{}
void calculate_all_adc_system_signal(void)
{}
EvAdc_SignalDataType_Fake read_adc_system_value(System_Adc_Signal_Fake eSignal)
{}

/*==================================================================================================
*                                    Resolver API
==================================================================================================*/
uint8 start_resolver_excitation_signal(void)
{}
uint8 stop_resolver_excitation_signal(void)
{}
uint8 resolver_feedback_dsadc_calibration(void)
{}
void dsadc_read_resolver_feedback(sint16* s16sinfbk, sint16* s16cosfbk, uint32* u32rdcTimestamp)
{}
float32 EdsadcRdc_Atan2(float32 f32X_Data, float32 f32Y_Data) 
{}

/*==================================================================================================
*                                    Gatedriver API
==================================================================================================*/
void gatedriver_enable(void)
{}
void gatedriver_disable(void)
{}
void update_gatedriver_data_duty(void)
{}
float32 get_gatedriver_data_adc(GateDriver_Position_Fake position)
{}
float32 get_gatedriver_data_diagnostic2(GateDriver_Position_Fake position)
{}








