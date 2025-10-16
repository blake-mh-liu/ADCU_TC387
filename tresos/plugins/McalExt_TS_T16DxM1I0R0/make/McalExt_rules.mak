#EB_Automotive_Makefile

LIBRARIES_TO_BUILD     += McalExt_src

ifeq ($(McalExt_Adc_USED),true)
ifeq ($(Adc_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Adc_src
include  $(McalExt_CORE_PATH)/make/make_Adc/Adc_rules.mak
endif
endif

ifeq ($(McalExt_Bfx_USED),true)
ifeq ($(Bfx_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Bfx_src
include  $(McalExt_CORE_PATH)/make/make_Bfx/Bfx_rules.mak
endif
endif

ifeq ($(McalExt_Can_USED),true)
ifeq ($(Can_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Can_src
include  $(McalExt_CORE_PATH)/make/make_Can/Can_rules.mak
endif
endif

ifeq ($(McalExt_CanTrcv1_17_V9251_USED),true)
ifeq ($(CanTrcv1_VARIANT),17_V9251_Aurix2GAS440)
LIBRARIES_TO_BUILD     += CanTrcv1_src
include  $(McalExt_CORE_PATH)/make/make_CanTrcv1/CanTrcv1_rules.mak
endif
endif

ifeq ($(McalExt_CanTrcv2_17_W9255_USED),true)
ifeq ($(CanTrcv2_VARIANT),17_W9255_Aurix2GAS440)
LIBRARIES_TO_BUILD     += CanTrcv2_src
include  $(McalExt_CORE_PATH)/make/make_CanTrcv2/CanTrcv2_rules.mak
endif
endif

ifeq ($(McalExt_Crc_USED),true)
ifeq ($(Crc_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Crc_src
include  $(McalExt_CORE_PATH)/make/make_Crc/Crc_rules.mak
endif
endif

ifeq ($(McalExt_Dio_USED),true)
ifeq ($(Dio_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Dio_src
include  $(McalExt_CORE_PATH)/make/make_Dio/Dio_rules.mak
endif
endif

ifeq ($(McalExt_Dma_USED),true)
ifeq ($(Dma_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Dma_src
include  $(McalExt_CORE_PATH)/make/make_Dma/Dma_rules.mak
endif
endif

ifeq ($(McalExt_Dsadc_USED),true)
ifeq ($(Dsadc_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Dsadc_src
include  $(McalExt_CORE_PATH)/make/make_Dsadc/Dsadc_rules.mak
endif
endif

ifeq ($(McalExt_Eth_USED),true)
ifeq ($(Eth_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Eth_src
include  $(McalExt_CORE_PATH)/make/make_Eth/Eth_rules.mak
endif
endif

ifeq ($(McalExt_Fee_USED),true)
ifeq ($(Fee_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Fee_src
include  $(McalExt_CORE_PATH)/make/make_Fee/Fee_rules.mak
endif
endif

ifeq ($(McalExt_Fls_USED),true)
ifeq ($(Fls_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Fls_src
include  $(McalExt_CORE_PATH)/make/make_Fls/Fls_rules.mak
endif
endif

ifeq ($(McalExt_FlsLoader_USED),true)
ifeq ($(FlsLoader_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += FlsLoader_src
include  $(McalExt_CORE_PATH)/make/make_FlsLoader/FlsLoader_rules.mak
endif
endif

ifeq ($(McalExt_Fr_USED),true)
ifeq ($(Fr_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Fr_src
include  $(McalExt_CORE_PATH)/make/make_Fr/Fr_rules.mak
endif
endif

ifeq ($(McalExt_Gpt_USED),true)
ifeq ($(Gpt_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Gpt_src
include  $(McalExt_CORE_PATH)/make/make_Gpt/Gpt_rules.mak
endif
endif

ifeq ($(McalExt_Hssl_USED),true)
ifeq ($(Hssl_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Hssl_src
include  $(McalExt_CORE_PATH)/make/make_Hssl/Hssl_rules.mak
endif
endif

ifeq ($(McalExt_I2c_USED),true)
ifeq ($(I2c_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += I2c_src
include  $(McalExt_CORE_PATH)/make/make_I2c/I2c_rules.mak
endif
endif

ifeq ($(McalExt_Icu_USED),true)
ifeq ($(Icu_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Icu_src
include  $(McalExt_CORE_PATH)/make/make_Icu/Icu_rules.mak
endif
endif

ifeq ($(McalExt_Iom_USED),true)
ifeq ($(Iom_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Iom_src
include  $(McalExt_CORE_PATH)/make/make_Iom/Iom_rules.mak
endif
endif

ifeq ($(McalExt_Lin_USED),true)
ifeq ($(Lin_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Lin_src
include  $(McalExt_CORE_PATH)/make/make_Lin/Lin_rules.mak
endif
endif

ifeq ($(McalExt_McalLib_USED),true)
ifeq ($(McalLib_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += McalLib_src
include  $(McalExt_CORE_PATH)/make/make_McalLib/McalLib_rules.mak
endif
endif

ifeq ($(McalExt_Mcu_USED),true)
ifeq ($(Mcu_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Mcu_src
include  $(McalExt_CORE_PATH)/make/make_Mcu/Mcu_rules.mak
endif
endif

ifeq ($(McalExt_Ocu_USED),true)
ifeq ($(Ocu_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Ocu_src
include  $(McalExt_CORE_PATH)/make/make_Ocu/Ocu_rules.mak
endif
endif

ifeq ($(McalExt_Port_USED),true)
ifeq ($(Port_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Port_src
include  $(McalExt_CORE_PATH)/make/make_Port/Port_rules.mak
endif
endif

ifeq ($(McalExt_Pwm_USED),true)
ifeq ($(Pwm_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Pwm_src
include  $(McalExt_CORE_PATH)/make/make_Pwm/Pwm_rules.mak
endif
endif

ifeq ($(McalExt_Sent_USED),true)
ifeq ($(Sent_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Sent_src
include  $(McalExt_CORE_PATH)/make/make_Sent/Sent_rules.mak
endif
endif

ifeq ($(McalExt_Smu_USED),true)
ifeq ($(Smu_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Smu_src
include  $(McalExt_CORE_PATH)/make/make_Smu/Smu_rules.mak
endif
endif

ifeq ($(McalExt_Spi_USED),true)
ifeq ($(Spi_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Spi_src
include  $(McalExt_CORE_PATH)/make/make_Spi/Spi_rules.mak
endif
endif

ifeq ($(McalExt_Stm_USED),true)
ifeq ($(Stm_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Stm_src
include  $(McalExt_CORE_PATH)/make/make_Stm/Stm_rules.mak
endif
endif

ifeq ($(McalExt_Uart_USED),true)
ifeq ($(Uart_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Uart_src
include  $(McalExt_CORE_PATH)/make/make_Uart/Uart_rules.mak
endif
endif

ifeq ($(McalExt_Wdg_USED),true)
ifeq ($(Wdg_VARIANT),Aurix2GAS440)
LIBRARIES_TO_BUILD     += Wdg_src
include  $(McalExt_CORE_PATH)/make/make_Wdg/Wdg_rules.mak
endif
endif

McalExt_src_FILES += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/BaseSw/Infra/Autosar_Srv/Mcal_SafetyError.c