#EB_Automotive_Makefile

McalExt_CORE_PATH      ?= $(PLUGINS_BASE)/McalExt_$(McalExt_VARIANT)
McalExt_OUTPUT_PATH    := $(AUTOSAR_BASE_OUTPUT_PATH)

McalExt_GEN_FILES      += $(McalExt_OUTPUT_PATH)/include/Platforms_Modules.h

ifeq ($(McalExt_Adc_USED),true)
ifeq ($(Adc_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Adc/Adc_defs.mak
endif
endif

ifeq ($(McalExt_Bfx_USED),true)
ifeq ($(Bfx_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Bfx/Bfx_defs.mak
endif
endif

ifeq ($(McalExt_Can_USED),true)
ifeq ($(Can_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Can/Can_defs.mak
endif
endif

ifeq ($(McalExt_CanTrcv1_17_V9251_USED),true)
ifeq ($(CanTrcv1_VARIANT),17_V9251_Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_CanTrcv1/CanTrcv1_defs.mak
endif
endif

ifeq ($(McalExt_CanTrcv2_17_W9255_USED),true)
ifeq ($(CanTrcv2_VARIANT),17_W9255_Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_CanTrcv2/CanTrcv2_defs.mak
endif
endif

ifeq ($(McalExt_Crc_USED),true)
ifeq ($(Crc_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Crc/Crc_defs.mak
endif
endif

ifeq ($(McalExt_Dio_USED),true)
ifeq ($(Dio_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Dio/Dio_defs.mak
endif
endif

ifeq ($(McalExt_Dma_USED),true)
ifeq ($(Dma_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Dma/Dma_defs.mak
endif
endif

ifeq ($(McalExt_Dsadc_USED),true)
ifeq ($(Dsadc_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Dsadc/Dsadc_defs.mak
endif
endif

ifeq ($(McalExt_Eth_USED),true)
ifeq ($(Eth_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Eth/Eth_defs.mak
endif
endif

ifeq ($(McalExt_Fee_USED),true)
ifeq ($(Fee_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Fee/Fee_defs.mak
endif
endif

ifeq ($(McalExt_Fls_USED),true)
ifeq ($(Fls_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Fls/Fls_defs.mak
endif
endif

ifeq ($(McalExt_FlsLoader_USED),true)
ifeq ($(FlsLoader_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_FlsLoader/FlsLoader_defs.mak
endif
endif

ifeq ($(McalExt_Fr_USED),true)
ifeq ($(Fr_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Fr/Fr_defs.mak
endif
endif

ifeq ($(McalExt_Gpt_USED),true)
ifeq ($(Gpt_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Gpt/Gpt_defs.mak
endif
endif

ifeq ($(McalExt_Hssl_USED),true)
ifeq ($(Hssl_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Hssl/Hssl_defs.mak
endif
endif

ifeq ($(McalExt_I2c_USED),true)
ifeq ($(I2c_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_I2c/I2c_defs.mak
endif
endif

ifeq ($(McalExt_Icu_USED),true)
ifeq ($(Icu_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Icu/Icu_defs.mak
endif
endif

ifeq ($(McalExt_Iom_USED),true)
ifeq ($(Iom_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Iom/Iom_defs.mak
endif
endif

ifeq ($(McalExt_Lin_USED),true)
ifeq ($(Lin_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Lin/Lin_defs.mak
endif
endif

ifeq ($(McalExt_McalLib_USED),true)
ifeq ($(McalLib_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_McalLib/McalLib_defs.mak
endif
endif

ifeq ($(McalExt_Mcu_USED),true)
ifeq ($(Mcu_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Mcu/Mcu_defs.mak
endif
endif

ifeq ($(McalExt_Ocu_USED),true)
ifeq ($(Ocu_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Ocu/Ocu_defs.mak
endif
endif

ifeq ($(McalExt_Port_USED),true)
ifeq ($(Port_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Port/Port_defs.mak
endif
endif

ifeq ($(McalExt_Pwm_USED),true)
ifeq ($(Pwm_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Pwm/Pwm_defs.mak
endif
endif

ifeq ($(McalExt_Sent_USED),true)
ifeq ($(Sent_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Sent/Sent_defs.mak
endif
endif

ifeq ($(McalExt_Smu_USED),true)
ifeq ($(Smu_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Smu/Smu_defs.mak
endif
endif

ifeq ($(McalExt_Spi_USED),true)
ifeq ($(Spi_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Spi/Spi_defs.mak
endif
endif

ifeq ($(McalExt_Stm_USED),true)
ifeq ($(Stm_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Stm/Stm_defs.mak
endif
endif

ifeq ($(McalExt_Uart_USED),true)
ifeq ($(Uart_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Uart/Uart_defs.mak
endif
endif

ifeq ($(McalExt_Wdg_USED),true)
ifeq ($(Wdg_VARIANT),Aurix2GAS440)
include  $(McalExt_CORE_PATH)/make/make_Wdg/Wdg_defs.mak
endif
endif

TRESOS_GEN_FILES   += $(McalExt_GEN_FILES)

CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/include
CC_INCLUDE_PATH    += $(McalExt_OUTPUT_PATH)/include
CC_INCLUDE_PATH    += $(McalExt_OUTPUT_PATH)/inc
CC_INCLUDE_PATH    += $(McalExt_CORE_PATH)/MCAL_Delivery/DemoWorkspace/McalDemo/TC38A/0_Src/BaseSw/Infra/Irq/ssc/inc
