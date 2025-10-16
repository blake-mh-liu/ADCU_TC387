/*==================================================================================================
 * Copyright 2024 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/
#ifndef __ADC_API_H__
#define __ADC_API_H__

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <adc.h>
#include "cdd_adc_cfg.h"


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef enum 
{
    ADC_PHASE_U = 0u,
    ADC_PHASE_V,
    ADC_PHASE_W,
    ADC_PHASE_COUNT,
 } Adc_Phase_Current_Num;


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern EvAdc_SignalDataType* const g_EvAdc_SignalDataList[SYSTEM_ADC_SIGNAL_COUNT];

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
Std_ReturnType read_phase_current_sync_result(EvAdc_SignalDataType phCurrent[ADC_PHASE_COUNT]);
void start_core0_system_adc_hw_trigger(void);
void stop_core0_system_adc_hw_trigger(void);
void start_core1_system_adc_hw_trigger(void);
void stop_core1_system_adc_hw_trigger(void);
void start_core1_phase_current_adc_hw_trigger(void);
void stop_core1_phase_current_adc_hw_trigger(void);
void calculate_adc_system_signal(System_Adc_Signal eSignal);
void calculate_all_adc_system_signal(void);
EvAdc_SignalDataType read_adc_system_value(System_Adc_Signal eSignal);

#endif