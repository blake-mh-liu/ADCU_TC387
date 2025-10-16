/*==================================================================================================
 * Copyright 2025 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/
#ifndef __CDD_ADC_CFG_H__
#define __CDD_ADC_CFG_H__

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc.h"

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define EVADC_CONV_MV_DATA(u32_RegData) ((5000u * (u32_RegData)) / 4095u)
#define CONV_MV_TO_V(Mv)                ((float32)Mv / 1000.0f)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    uint32  u32_Reg;
    uint32  u32_Mv;
    float32 f32_Phy;
} EvAdc_SignalDataType;

enum Adc_Group0_1ms
{
    QUC_1V25_GROUPINDEX = 0u,
    SIN_P_GROUPINDEX,
    SIN_N_GROUPINDEX,
    GROUP0_1MS_COUNT,
};

enum Adc_Group1_1ms
{
    QT1_5V0_GROUPINDEX = 0u,
    QT2_GROUPINDEX,
    GROUP1_1MS_COUNT,
};

enum Adc_Group2_1ms
{
    COS_N_GROUPINDEX = 0u,
    HV_LV_13V5_GROUPINDEX,
    TEMP_M_V_GROUPINDEX,
    GROUP2_1MS_COUNT,
};

enum Adc_Group3_1ms
{
    HV_U_GROUPINDEX = 0u,
    COS_P_GROUPINDEX,
    TEMP_SIC_U_GROUPINDEX,
    TEMP_SIC_V_GROUPINDEX,
    TEMP_MCU_GROUPINDEX,
    TEMP_M_U_GROUPINDEX,
    TEMP_M_W_GROUPINDEX,
    GROUP3_1MS_COUNT,
};

enum Adc_Group8_1ms
{
    BOOST_21V5_GROUPINDEX = 0u,
    BOOST_LDO_12V0_GROUPINDEX,
    QCO_5V0_GROUPINDEX,
    QUC_3V3_GROUPINDEX,
    TEMP_OIL_GROUPINDEX,
    TEMP_SIC_W_GROUPINDEX,
    CURRENT_V_IO_GROUPINDEX,
    GROUP8_1MS_COUNT,
};

enum Adc_Group9_1ms
{
    CURRENT_U_IO_GROUPINDEX = 0u,
    EXC_N_GROUPINDEX,
    EXC_P_GROUPINDEX,
    GROUP9_1MS_COUNT,
};

enum Adc_Group10_1ms
{
    CURRENT_W_IO_GROUPINDEX = 0u,
    GROUP10_1MS_COUNT,
};

enum Adc_Group11_1ms
{
    KL30_GROUPINDEX = 0u,
    HV_V_GROUPINDEX,
    PMIC_5V8_GROUPINDEX,
    QVR_5V0_GROUPINDEX,
    KL15_GROUPINDEX,
    QUC_5V0_GROUPINDEX,
    TEMP_FLYBACK_GROUPINDEX,
    GROUP11_1MS_COUNT,
};

typedef void (*calculateSystemAdcDataFn)(EvAdc_SignalDataType*);

typedef struct
{
    Adc_ValueGroupType*      dataBuffer;
    uint32                   dataBufferIndex;
    calculateSystemAdcDataFn p_CalculateFunction;
} EvAdc_SignalCfgType;

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
} System_Adc_Signal;


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern Adc_ValueGroupType group0_1msBuffer[GROUP0_1MS_COUNT];
extern Adc_ValueGroupType group1_1msBuffer[GROUP1_1MS_COUNT];
extern Adc_ValueGroupType group2_1msBuffer[GROUP2_1MS_COUNT];
extern Adc_ValueGroupType group3_1msBuffer[GROUP3_1MS_COUNT];
extern Adc_ValueGroupType group8_1msBuffer[GROUP8_1MS_COUNT];
extern Adc_ValueGroupType group9_1msBuffer[GROUP9_1MS_COUNT];
extern Adc_ValueGroupType group10_1msBuffer[GROUP10_1MS_COUNT];
extern Adc_ValueGroupType group11_1msBuffer[GROUP11_1MS_COUNT];
extern const EvAdc_SignalCfgType* const g_EvAdc_SignalCfgList[SYSTEM_ADC_SIGNAL_COUNT];
extern EvAdc_SignalDataType* const g_EvAdc_SignalDataList[SYSTEM_ADC_SIGNAL_COUNT];

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void calculate_dc_bus_voltage(EvAdc_SignalDataType* p_signalData);
void calculate_motor_temp(EvAdc_SignalDataType* p_signalData);
void calculate_oil_temp(EvAdc_SignalDataType* p_signalData);
void calculate_pcb_temp(EvAdc_SignalDataType* p_signalData);
void calculate_sic_temp(EvAdc_SignalDataType* p_signalData);
void calculate_current(EvAdc_SignalDataType* p_signalData);
void calculate_divider_voltage_0V_to_5V(EvAdc_SignalDataType* p_signalData);
void calculate_divider_voltage_0V_to_10V(EvAdc_SignalDataType* p_signalData);
void calculate_divider_voltage_0V_to_25V(EvAdc_SignalDataType* p_signalData);
void calculate_divider_voltage_0V_to_35V(EvAdc_SignalDataType* p_signalData);

#endif