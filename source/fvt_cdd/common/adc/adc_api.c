/*==================================================================================================
 * Copyright 2024 (c) Foxtron Inc - All Rights Reserved
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
#include "adc_api.h"
#include "IfxEvadc_reg.h"
#include "Adc_Cfg.h"
#include "cdd_adc_cfg.h"


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ADC_MAX_SAMPLE_COUNT        (10u)

#define ADC_CUR_U_GROUP             (0u)
#define ADC_CUR_V_GROUP             (1u)
#define ADC_CUR_W_GROUP             (2u)

#define ZERODRIFT_COUNT             (5u)
#define CUR_SNNSOR_GAIN             (500.0f)
#define CUR_SENSOR_OFFSET           (2.5f)
#define CUR_SENSOR_OFFSET_THRESHOLD (0.5f)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
#define CDD_ADC_START_SEC_CORE1
#include "cdd_adc_memmap.h"

static uint8 g_u8CurSnsr_ZeroDrift_Count[ADC_PHASE_COUNT] = { 0u };
static float32 g_f32CurSnsrCmpSum[ADC_PHASE_COUNT] = { 0.0f };

#define CDD_ADC_STOP_SEC_CORE1
#include "cdd_adc_memmap.h"

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define CDD_ADC_START_SEC_CODE_CORE1
#include "cdd_adc_memmap.h"

static Std_ReturnType get_adc_channel_value(uint8 group, uint8 channel, uint16* adcValue)
{
    uint32 retry_count = 0;
    Ifx_EVADC_G* evadcGroup = &MODULE_EVADC.G[group];

    while (evadcGroup->RES[channel].B.VF == 0)
    {
        if (++retry_count > ADC_MAX_SAMPLE_COUNT)
        {
            *adcValue = 0;
            return E_NOT_OK;
        }
    }

    *adcValue = evadcGroup->RES[channel].B.RESULT;
    return E_OK;
}

static Std_ReturnType read_adc_phase_current_raw(uint16 u16Array3_phCurrent[ADC_PHASE_COUNT])
{
    Std_ReturnType result = E_OK;
    uint16 uAout, vAout, wAout;

    result |= get_adc_channel_value(ADC_CUR_U_GROUP, AdcConf_AdcChannel_CURRENT_U_AN0, &uAout);
    result |= get_adc_channel_value(ADC_CUR_V_GROUP, AdcConf_AdcChannel_CURRENT_V_AN8, &vAout);
    result |= get_adc_channel_value(ADC_CUR_W_GROUP, AdcConf_AdcChannel_CURRENT_W_AN16, &wAout);

    u16Array3_phCurrent[ADC_PHASE_U] = uAout;
    u16Array3_phCurrent[ADC_PHASE_V] = vAout;
    u16Array3_phCurrent[ADC_PHASE_W] = wAout;

    return result;
}

static float32 calculate_adc_phase_with_zero_drift(uint8 phase, float32 phaseVoltage)
{
    float32 adcPhasePhy;

    if (g_u8CurSnsr_ZeroDrift_Count[phase] < ZERODRIFT_COUNT)
    {
        if (phaseVoltage > (CUR_SENSOR_OFFSET - CUR_SENSOR_OFFSET_THRESHOLD) && phaseVoltage < (CUR_SENSOR_OFFSET + CUR_SENSOR_OFFSET_THRESHOLD))
        {
            /* If the value is in the range of zero drift, then accumulate it */
            g_f32CurSnsrCmpSum[phase] += (phaseVoltage - CUR_SENSOR_OFFSET);
            g_u8CurSnsr_ZeroDrift_Count[phase]++;
        }
        if (ZERODRIFT_COUNT == g_u8CurSnsr_ZeroDrift_Count[phase])
        {
            g_f32CurSnsrCmpSum[phase] /= ZERODRIFT_COUNT;/* Get the average value of zero drift */
        }
        adcPhasePhy = (phaseVoltage - CUR_SENSOR_OFFSET) * CUR_SNNSOR_GAIN;
    }
    else
    {
        adcPhasePhy = (phaseVoltage - CUR_SENSOR_OFFSET - g_f32CurSnsrCmpSum[phase]) * CUR_SNNSOR_GAIN;
    }

    return adcPhasePhy;
}

#define CDD_ADC_STOP_SEC_CODE_CORE1
#include "cdd_adc_memmap.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#include "Eth_17_GEthMacV2.h"

sint32 RTL8211F_IsPhyIdValid(void)
{
  uint16 phy_id1=0;
  uint16 phy_id2=0;
  /* Read PHY device Identification ID1. */
  if(Eth_17_GEthMacV2_ReadMii(0, 1, 0x02, &phy_id1)!= 0)
  {
      return -2;
  }
   /* Read PHY Device Identification ID2. */
  if(Eth_17_GEthMacV2_ReadMii(0, 1, 0x03, &phy_id2)!= 0)
  {
      return -2;
  }
  /* Verify PHY Device ID1 & ID2. */
  if((phy_id1 == 0x001cU) && (phy_id2 == 0xc916U))
  {
      return 0x00;
  }

  return 0x01;
}

sint32 RTL8211F_PhyReset(void)
{
  uint16 reg_bmcr;
  /* Reset PHY*/
  if(Eth_17_GEthMacV2_ReadMii(0, 1, 0x00, &reg_bmcr)!= 0)
  {
     return -2; 
  }
    
  reg_bmcr |= 0x8000;
  if(Eth_17_GEthMacV2_WriteMii(0, 1, 0x00, reg_bmcr)!= 0)
  {
     return -2;  
  }

  return 0;
}

sint32 RTL8211F_PhyResetCheck(void)
{
  uint16 reg_bmcr;
  /*Check PHY reset status*/
  if(Eth_17_GEthMacV2_ReadMii(0, 1, 0x00, &reg_bmcr)!= 0)
  {
      return -2; 
  }
  if((reg_bmcr & 0x8000) == 0x00)
  {
      return 0x00;
  }

  return 0x01;
}

sint32 RTL8211F_PhyInit(void)
{
  uint16 reg_value = 0;
  uint16 reg_bmcr = 0;
  uint32 retries = 0xffffffff;

  while ((RTL8211F_IsPhyIdValid() != 0x00) && (--retries)){}

  if (retries == 0)
  {
    return -3;
  }

  /*Enable CLKOUT @125MHz */
  /*Select the PHY page for the register PHY_CR2_ADDRESS*/
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x1f, 0xa43);
  Eth_17_GEthMacV2_ReadMii(0, 1, 0x19, &reg_value);
  reg_value |= 0x1;
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x19, reg_value);

  /* restore to default page 0 */
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x1f, 0x0);

  /* A PHY reset should be issued after setting this bits in PHY_CR2_ADDRESS */
  RTL8211F_PhyReset();

  /*Veirfy the phy reset is ok or not*/
  while (RTL8211F_PhyResetCheck() != 0x00){}

  /*RTL8211F_TX_DELAY delay to be added*/
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x1f, 0xd08);
  Eth_17_GEthMacV2_ReadMii(0, 1, 0x11, &reg_value);
  reg_value |= 0x100;  
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x11, reg_value);	

  /*restore to default page 0 */
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x1f, 0x0);

  /*Reading the value of Basic mode control register*/
  Eth_17_GEthMacV2_ReadMii(0, 1, 0x00, &reg_bmcr);
 
  reg_value |= 0x2000;
  
  reg_value |= 0x0100;
  
  /*Setting the value to Basic mode control register*/
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x00, reg_value);

  /*Enable Auto Negotiation*/
  reg_bmcr |= 0x1000;
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x00, reg_bmcr);

  /*Software reset is asserted, Restart AN or power mode transition*/
  reg_bmcr |= 0x0200;
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x00, reg_bmcr);
  
  return 0;
}

sint32 RTL8211F_GetPhyLinkStatus(void)
{
  uint16 reg_value = 0;
   Eth_17_GEthMacV2_WriteMii(0, 1, 0x1F, 0xa43);
   Eth_17_GEthMacV2_ReadMii(0, 1, 0x1a, &reg_value);
  
   /* restore to default page 0 */
   Eth_17_GEthMacV2_WriteMii(0, 1, 0x1f, 0);
  return ((reg_value & 0x0004) ? 0x01 : 0x00);
}

uint8 initStatus = 0xFF, sysStatus = 0xFF;

void start_core0_system_adc_hw_trigger(void)
{
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP3_1MS, &group3_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP8_1MS, &group8_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP9_1MS, &group9_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP10_1MS, &group10_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP11_1MS, &group11_1msBuffer[0]);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP3_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP8_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP9_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP10_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP11_1MS);
    RTL8211F_PhyInit();
    Eth_17_GEthMacV2_SetControllerMode(0, ETH_MODE_ACTIVE);
}

void stop_core0_system_adc_hw_trigger(void)
{
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP0_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP3_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP8_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP9_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP10_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP11_1MS);
}

void start_core1_system_adc_hw_trigger(void)
{
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP0_1MS, &group0_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP1_1MS, &group1_1msBuffer[0]);
    Adc_SetupResultBuffer(AdcConf_AdcGroup_ADCGROUP2_1MS, &group2_1msBuffer[0]);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP0_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP1_1MS);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP2_1MS);
}

void stop_core1_system_adc_hw_trigger(void)
{
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP0_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP1_1MS);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_ADCGROUP2_1MS);
}

void start_core1_phase_current_adc_hw_trigger(void)
{
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_CUR_U);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_CUR_V);
    Adc_EnableHardwareTrigger(AdcConf_AdcGroup_CUR_W);
}

void stop_core1_phase_current_adc_hw_trigger(void)
{
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_CUR_U);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_CUR_V);
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_CUR_W);
}

EvAdc_SignalDataType read_adc_system_value(System_Adc_Signal eSignal)
{
    if (eSignal < SYSTEM_ADC_SIGNAL_COUNT)
    {
        return *g_EvAdc_SignalDataList[eSignal];
    }
    else
    {
        EvAdc_SignalDataType invalidData = {
            .u32_Reg = 0u,
            .u32_Mv = 0u,
            .f32_Phy = 0.0f
        };
        return invalidData;
    }
}

#define CDD_ADC_START_SEC_CODE_CORE0
#include "cdd_adc_memmap.h"

void calculate_adc_system_signal(System_Adc_Signal eSignal)
{
    const EvAdc_SignalCfgType* p_Sign;
    EvAdc_SignalDataType* signalDataType;

    if (eSignal >= SYSTEM_ADC_SIGNAL_COUNT)
    {
        return;
    }
    p_Sign = g_EvAdc_SignalCfgList[eSignal];
    signalDataType = g_EvAdc_SignalDataList[eSignal];

    signalDataType->u32_Reg = p_Sign->dataBuffer[p_Sign->dataBufferIndex];
    signalDataType->u32_Mv = EVADC_CONV_MV_DATA(signalDataType->u32_Reg);
    p_Sign->p_CalculateFunction(signalDataType);
}

void calculate_all_adc_system_signal(void)
{
    for (System_Adc_Signal signal = PMIC_5V8_SIGNAL; signal < SYSTEM_ADC_SIGNAL_COUNT; signal++)
    {
        calculate_adc_system_signal(signal);
    }
}

#define CDD_ADC_STOP_SEC_CODE_CORE0
#include "cdd_adc_memmap.h"

#define CDD_ADC_START_SEC_CODE_CORE1
#include "cdd_adc_memmap.h"

Std_ReturnType read_phase_current_sync_result(EvAdc_SignalDataType phCurrent[ADC_PHASE_COUNT])
{
    Std_ReturnType result;
    uint16 u16Array3_phCurrent[ADC_PHASE_COUNT];

    result = read_adc_phase_current_raw(&u16Array3_phCurrent[ADC_PHASE_U]);

    if (result != E_OK)
    {
        return result;
    }

    for (uint8 phase = ADC_PHASE_U; phase < ADC_PHASE_COUNT; phase++)
    {
        phCurrent[phase].u32_Reg = u16Array3_phCurrent[phase];
        phCurrent[phase].u32_Mv = EVADC_CONV_MV_DATA(u16Array3_phCurrent[phase]);
        phCurrent[phase].f32_Phy = calculate_adc_phase_with_zero_drift(phase, CONV_MV_TO_V(phCurrent[phase].u32_Mv));
    }

    return result;
}

#define CDD_ADC_STOP_SEC_CODE_CORE1
#include "cdd_adc_memmap.h"