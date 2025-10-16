/*==================================================================================================
 * Copyright 2025 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "cdd_adc_cfg.h"
#include "Adc_Cfg.h"
#include "cdd_adc_lookup_table.h"

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ADC_VOLTAGE_REFERENCE      (5.0f)
#define DC_VOLTAGE_DIVIDER_RATIO   (2.0f + 1200.0f)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define CDD_ADC_START_SEC_GLOBAL
#include "cdd_adc_memmap.h"

Adc_ValueGroupType group0_1msBuffer[GROUP0_1MS_COUNT] = { 0 };
Adc_ValueGroupType group1_1msBuffer[GROUP1_1MS_COUNT] = { 0 };
Adc_ValueGroupType group2_1msBuffer[GROUP2_1MS_COUNT] = { 0 };

#define CDD_ADC_STOP_SEC_GLOBAL
#include "cdd_adc_memmap.h"

Adc_ValueGroupType group3_1msBuffer[GROUP3_1MS_COUNT] = { 0 };
Adc_ValueGroupType group8_1msBuffer[GROUP8_1MS_COUNT] = { 0 };
Adc_ValueGroupType group9_1msBuffer[GROUP9_1MS_COUNT] = { 0 };
Adc_ValueGroupType group10_1msBuffer[GROUP10_1MS_COUNT] = { 0 };
Adc_ValueGroupType group11_1msBuffer[GROUP11_1MS_COUNT] = { 0 };

EvAdc_SignalDataType PMIC_5V8_SignalData;
EvAdc_SignalDataType KL15_SignalData;
EvAdc_SignalDataType KL30_SignalData;
EvAdc_SignalDataType HV_LV_13V5_SignalData;
EvAdc_SignalDataType QUC_1V25_SignalData;
EvAdc_SignalDataType QUC_3V3_SignalData;
EvAdc_SignalDataType QUC_5V0_SignalData;
EvAdc_SignalDataType QVR_5V0_SignalData;
EvAdc_SignalDataType QT1_5V0_SignalData;
EvAdc_SignalDataType QT2_SignalData;
EvAdc_SignalDataType QCO_5V0_SignalData;
EvAdc_SignalDataType BOOST_LDO_12V0_SignalData;
EvAdc_SignalDataType BOOST_21V5_SignalData;
EvAdc_SignalDataType HV_U_SignalData;
EvAdc_SignalDataType HV_V_SignalData;
EvAdc_SignalDataType CURRENT_U_IO_SignalData;
EvAdc_SignalDataType CURRENT_V_IO_SignalData;
EvAdc_SignalDataType CURRENT_W_IO_SignalData;
EvAdc_SignalDataType SIN_P_SignalData;
EvAdc_SignalDataType SIN_N_SignalData;
EvAdc_SignalDataType COS_P_SignalData;
EvAdc_SignalDataType COS_N_SignalData;
EvAdc_SignalDataType EXC_P_SignalData;
EvAdc_SignalDataType EXC_N_SignalData;
EvAdc_SignalDataType TEMP_MCU_SignalData;
EvAdc_SignalDataType TEMP_FLYBACK_SignalData;
EvAdc_SignalDataType TEMP_OIL_SignalData;
EvAdc_SignalDataType TEMP_M_U_SignalData;
EvAdc_SignalDataType TEMP_M_V_SignalData;
EvAdc_SignalDataType TEMP_M_W_SignalData;
EvAdc_SignalDataType Temp_SIC_U_SignalData;
EvAdc_SignalDataType Temp_SIC_V_SignalData;
EvAdc_SignalDataType Temp_SIC_W_SignalData;

const EvAdc_SignalCfgType PMIC_5V8_SignalCfg = {
    group11_1msBuffer,
    PMIC_5V8_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType KL15_SignalCfg = {
    group11_1msBuffer,
    KL15_GROUPINDEX,
    calculate_divider_voltage_0V_to_35V,
};

const EvAdc_SignalCfgType KL30_SignalCfg = {
    group11_1msBuffer,
    KL30_GROUPINDEX,
    calculate_divider_voltage_0V_to_35V,
};

const EvAdc_SignalCfgType HV_LV_13V5_SignalCfg = {
    group2_1msBuffer,
    HV_LV_13V5_GROUPINDEX,
    calculate_divider_voltage_0V_to_25V,
};

const EvAdc_SignalCfgType QUC_1V25_SignalCfg = {
    group0_1msBuffer,
    QUC_1V25_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType QUC_3V3_SignalCfg = {
    group8_1msBuffer,
    QUC_3V3_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType QUC_5V0_SignalCfg = {
    group11_1msBuffer,
    QUC_5V0_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType QVR_5V0_SignalCfg = {
    group11_1msBuffer,
    QVR_5V0_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType QT1_5V0_SignalCfg = {
    group1_1msBuffer,
    QT1_5V0_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType QT2_SignalCfg = {
    group1_1msBuffer,
    QT2_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType QCO_5V0_SignalCfg = {
    group8_1msBuffer,
    QCO_5V0_GROUPINDEX,
    calculate_divider_voltage_0V_to_10V,
};

const EvAdc_SignalCfgType BOOST_LDO_12V0_SignalCfg = {
    group8_1msBuffer,
    BOOST_LDO_12V0_GROUPINDEX,
    calculate_divider_voltage_0V_to_25V,
};

const EvAdc_SignalCfgType BOOST_21V5_SignalCfg = {
    group8_1msBuffer,
    BOOST_21V5_GROUPINDEX,
    calculate_divider_voltage_0V_to_35V,
};

const EvAdc_SignalCfgType HV_U_SignalCfg = {
    group3_1msBuffer,
    HV_U_GROUPINDEX,
    calculate_dc_bus_voltage,
};

const EvAdc_SignalCfgType HV_V_SignalCfg = {
    group11_1msBuffer,
    HV_V_GROUPINDEX,
    calculate_dc_bus_voltage,
};

const EvAdc_SignalCfgType CURRENT_U_IO_SignalCfg = {
    group9_1msBuffer,
    CURRENT_U_IO_GROUPINDEX,
    calculate_current,
};

const EvAdc_SignalCfgType CURRENT_V_IO_SignalCfg = {
    group8_1msBuffer,
    CURRENT_V_IO_GROUPINDEX,
    calculate_current,
};

const EvAdc_SignalCfgType CURRENT_W_IO_SignalCfg = {
    group10_1msBuffer,
    CURRENT_W_IO_GROUPINDEX,
    calculate_current,
};

const EvAdc_SignalCfgType SIN_P_SignalCfg = {
    group0_1msBuffer,
    SIN_P_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType SIN_N_SignalCfg = {
    group0_1msBuffer,
    SIN_N_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType COS_P_SignalCfg = {
    group3_1msBuffer,
    COS_P_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType COS_N_SignalCfg = {
    group2_1msBuffer,
    COS_N_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType EXC_P_SignalCfg = {
    group9_1msBuffer,
    EXC_P_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType EXC_N_SignalCfg = {
    group9_1msBuffer,
    EXC_N_GROUPINDEX,
    calculate_divider_voltage_0V_to_5V,
};

const EvAdc_SignalCfgType TEMP_MCU_SignalCfg = {
    group3_1msBuffer,
    TEMP_MCU_GROUPINDEX,
    calculate_pcb_temp,
};

const EvAdc_SignalCfgType TEMP_FLYBACK_SignalCfg = {
    group11_1msBuffer,
    TEMP_FLYBACK_GROUPINDEX,
    calculate_pcb_temp,
};

const EvAdc_SignalCfgType TEMP_OIL_SignalCfg = {
    group8_1msBuffer,
    TEMP_OIL_GROUPINDEX,
    calculate_oil_temp,
};
const EvAdc_SignalCfgType TEMP_M_U_SignalCfg = {
    group3_1msBuffer,
    TEMP_M_U_GROUPINDEX,
    calculate_motor_temp,
};

const EvAdc_SignalCfgType TEMP_M_V_SignalCfg = {
    group2_1msBuffer,
    TEMP_M_V_GROUPINDEX,
    calculate_motor_temp,
};

const EvAdc_SignalCfgType TEMP_M_W_SignalCfg = {
    group3_1msBuffer,
    TEMP_M_W_GROUPINDEX,
    calculate_motor_temp,
};

const EvAdc_SignalCfgType Temp_SIC_U_SignalCfg = {
    group3_1msBuffer,
    TEMP_SIC_U_GROUPINDEX,
    calculate_sic_temp,
};

const EvAdc_SignalCfgType Temp_SIC_V_SignalCfg = {
    group3_1msBuffer,
    TEMP_SIC_V_GROUPINDEX,
    calculate_sic_temp,
};

const EvAdc_SignalCfgType Temp_SIC_W_SignalCfg = {
    group8_1msBuffer,
    TEMP_SIC_W_GROUPINDEX,
    calculate_sic_temp,
};

const EvAdc_SignalCfgType* const g_EvAdc_SignalCfgList[SYSTEM_ADC_SIGNAL_COUNT] = 
{
    /*PMIC_5V8_SIGNAL         = */&PMIC_5V8_SignalCfg,
    /*KL15_SIGNAL             = */&KL15_SignalCfg,
    /*KL30_SIGNAL             = */&KL30_SignalCfg,
    /*HV_LV_13V5_SIGNAL       = */&HV_LV_13V5_SignalCfg,
    /*QUC_1V25_SIGNAL         = */&QUC_1V25_SignalCfg,
    /*QUC_3V3_SIGNAL          = */&QUC_3V3_SignalCfg,
    /*QUC_5V0_SIGNAL          = */&QUC_5V0_SignalCfg,
    /*QVR_5V0_SIGNAL          = */&QVR_5V0_SignalCfg,
    /*QT1_5V0_SIGNAL          = */&QT1_5V0_SignalCfg,
    /*QT2_SIGNAL              = */&QT2_SignalCfg,
    /*QCO_5V0_SIGNAL          = */&QCO_5V0_SignalCfg,
    /*BOOST_LDO_12V0_SIGNAL   = */&BOOST_LDO_12V0_SignalCfg,
    /*BOOST_21V5_SIGNAL       = */&BOOST_21V5_SignalCfg, 
    /*HV_U_SIGNAL             = */&HV_U_SignalCfg,
    /*HV_V_SIGNAL             = */&HV_V_SignalCfg,
    /*CURRENT_U_IO_SIGNAL     = */&CURRENT_U_IO_SignalCfg,
    /*CURRENT_V_IO_SIGNAL     = */&CURRENT_V_IO_SignalCfg,
    /*CURRENT_W_IO_SIGNAL     = */&CURRENT_W_IO_SignalCfg,
    /*SIN_P_ADC_SIGNAL        = */&SIN_P_SignalCfg,
    /*SIN_N_ADC_SIGNAL        = */&SIN_N_SignalCfg,
    /*COS_P_ADC_SIGNAL        = */&COS_P_SignalCfg,   // COS_P_ADC uses the same configuration as HV_U_SIGNAL    
    /*COS_N_ADC_SIGNAL        = */&COS_N_SignalCfg,
    /*EXC_P_ADC_SIGNAL        = */&EXC_P_SignalCfg,
    /*EXC_N_ADC_SIGNAL        = */&EXC_N_SignalCfg,  
    /*TEMP_MCU_SIGNAL         = */&TEMP_MCU_SignalCfg,
    /*TEMP_FLYBACK_SIGNAL     = */&TEMP_FLYBACK_SignalCfg,
    /*Temp_OIL_SIGNAL         = */&TEMP_OIL_SignalCfg,
    /*Temp_M_U_SIGNAL         = */&TEMP_M_U_SignalCfg,
    /*Temp_M_V_SIGNAL         = */&TEMP_M_V_SignalCfg,
    /*Temp_M_W_SIGNAL         = */&TEMP_M_W_SignalCfg,
    /*Temp_SIC_U_SIGNAL       = */&Temp_SIC_U_SignalCfg,
    /*Temp_SIC_V_SIGNAL       = */&Temp_SIC_V_SignalCfg,
    /*Temp_SIC_W_SIGNAL       = */&Temp_SIC_W_SignalCfg,
};

EvAdc_SignalDataType* const g_EvAdc_SignalDataList[SYSTEM_ADC_SIGNAL_COUNT] =
{
    /*PMIC_5V8_DATA         = */&PMIC_5V8_SignalData,
    /*KL15_DATA             = */&KL15_SignalData,
    /*KL30_DATA             = */&KL30_SignalData,
    /*HV_LV_13V5_DATA       = */&HV_LV_13V5_SignalData,
    /*QUC_1V25_DATA         = */&QUC_1V25_SignalData,
    /*QUC_3V3_DATA          = */&QUC_3V3_SignalData,//
    /*QUC_5V0_DATA          = */&QUC_5V0_SignalData,
    /*QVR_5V0_DATA          = */&QVR_5V0_SignalData,
    /*QT1_5V0_DATA          = */&QT1_5V0_SignalData,
    /*QT2_DATA              = */&QT2_SignalData,
    /*QCO_5V0_DATA          = */&QCO_5V0_SignalData,
    /*BOOST_LDO_12V0_DATA   = */&BOOST_LDO_12V0_SignalData,
    /*BOOST_21V5_DATA       = */&BOOST_21V5_SignalData,
    /*HV_U_DATA             = */&HV_U_SignalData,
    /*HV_V_DATA             = */&HV_V_SignalData,
    /*CURRENT_U_IO_DATA     = */&CURRENT_U_IO_SignalData,
    /*CURRENT_V_IO_DATA     = */&CURRENT_V_IO_SignalData,
    /*CURRENT_W_IO_DATA     = */&CURRENT_W_IO_SignalData,
    /*SIN_P_ADC_DATA        = */&SIN_P_SignalData,    
    /*SIN_N_ADC_DATA        = */&SIN_N_SignalData,  
    /*COS_P_ADC_DATA        = */&COS_P_SignalData,  
    /*COS_N_ADC_DATA        = */&COS_N_SignalData,  
    /*EXC_P_ADC_DATA        = */&EXC_P_SignalData,  
    /*EXC_N_ADC_DATA        = */&EXC_N_SignalData,    
    /*TEMP_MCU_DATA         = */&TEMP_MCU_SignalData,
    /*TEMP_FLYBACK_DATA     = */&TEMP_FLYBACK_SignalData,
    /*Temp_OIL_DATA         = */&TEMP_OIL_SignalData,
    /*Temp_M_U_DATA         = */&TEMP_M_U_SignalData,
    /*Temp_M_V_DATA         = */&TEMP_M_V_SignalData,
    /*Temp_M_W_DATA         = */&TEMP_M_W_SignalData,
    /*Temp_SIC_U_DATA       = */&Temp_SIC_U_SignalData,
    /*Temp_SIC_V_DATA       = */&Temp_SIC_V_SignalData,
    /*Temp_SIC_W_DATA       = */&Temp_SIC_W_SignalData,
};

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
static float EvAdc_GetTempByVoltage(float voltage, const EvAdc_stTempVoltPairType* table, uint32 tableSize)
{
    float32 frettemp = 0.0f;

    if (voltage >= table[0].volt)
    {
        return table[0].temp;
    }
    if (voltage <= table[tableSize - 1].volt)
    {
        return table[tableSize - 1].temp;
    }
    for (uint16 i = 0; i < tableSize - 1; i++)
    {
        float v_high = table[i].volt;
        float v_low  = table[i + 1].volt;
        if ((voltage <= v_high) && (voltage >= v_low))
        {
            float t_high = table[i].temp;
            float t_low  = table[i + 1].temp;
            frettemp =  t_high + (t_low - t_high) * (voltage - v_high) / (v_low - v_high);
            break;
        }
    }
    return frettemp;
}


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void calculate_dc_bus_voltage(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = CONV_MV_TO_V(p_signalData->u32_Mv) * DC_VOLTAGE_DIVIDER_RATIO / ADC_VOLTAGE_REFERENCE;
}

void calculate_motor_temp(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = EvAdc_GetTempByVoltage(CONV_MV_TO_V(p_signalData->u32_Mv), c_stMotorTempVoltageTable, MOTOR_TEMP_TABLE_SIZE) ;
}

void calculate_oil_temp(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = EvAdc_GetTempByVoltage(CONV_MV_TO_V(p_signalData->u32_Mv), c_stOilTempVoltageTable, OIL_TEMP_TABLE_SIZE) ;
}

void calculate_pcb_temp(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = EvAdc_GetTempByVoltage(CONV_MV_TO_V(p_signalData->u32_Mv), c_stPCBTempVoltageTable, PCB_TEMP_TABLE_SIZE) ;
}

void calculate_sic_temp(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = EvAdc_GetTempByVoltage(CONV_MV_TO_V(p_signalData->u32_Mv), c_stSICTempVoltageTable, SIC_TEMP_TABLE_SIZE) ;
}

void calculate_current(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = (CONV_MV_TO_V(p_signalData->u32_Mv) -2.5f) / 2.5f;
}

void calculate_divider_voltage_0V_to_5V(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = CONV_MV_TO_V(p_signalData->u32_Mv);
}

void calculate_divider_voltage_0V_to_10V(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = CONV_MV_TO_V(p_signalData->u32_Mv) * 20.0f / 10.0f;
}

void calculate_divider_voltage_0V_to_25V(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = CONV_MV_TO_V(p_signalData->u32_Mv) *(5.1f + 20.0f) / 5.1f;
}

void calculate_divider_voltage_0V_to_35V(EvAdc_SignalDataType* p_signalData)
{
    p_signalData->f32_Phy = CONV_MV_TO_V(p_signalData->u32_Mv) *(3.3f + 20.0f) / 3.3f;
}
