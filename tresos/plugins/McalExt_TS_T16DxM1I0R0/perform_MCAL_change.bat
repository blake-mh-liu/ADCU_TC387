@echo off
:: --------{ EB Automotive Batch File }--------
::
:: script to update MCAL module with EB content
:: or reset it to vendor content

if [%1]==[EB_update] goto usage
if [%1]==[origin] goto usage
echo Usage: %0 [OPTION]
echo(
echo   EB_update
echo		Update files of the plug-in with content of Elektrobit Automotive GmbH.
echo   origin
echo		Reset the files of the plug-in with vendor content.
echo(
goto copy_end

:usage
cd %~d0 >NUL
cd %~p0
:: if exist an *.origin_version delete the current file:
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h (
echo delete %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h (
echo delete %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h )
if exist .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h (
echo delete %~d0%~p0MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h
del .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h )
if exist .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c
del .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c )
if exist .\MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c (
echo delete %~d0%~p0MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c
del .\MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c )
:: if exist an *.EB_update file delete the current file:
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h (
echo 	remove %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h
del .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c
del .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h (
echo 	remove %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h
del .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h )
if exist .\templates\Spi_UserCode.c (
echo 	remove %~d0%~p0templates\Spi_UserCode.c
del .\templates\Spi_UserCode.c )
if exist .\templates\Spi_UserCode.h (
echo 	remove %~d0%~p0templates\Spi_UserCode.h
del .\templates\Spi_UserCode.h )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.origin_version 
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.origin_version .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.origin_version 
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.origin_version .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.origin_version 
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.origin_version .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.origin_version 
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.origin_version .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.origin_version 
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.origin_version .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h >NUL )
if exist .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h.origin_version 
copy .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h.origin_version .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_Cfg.h >NUL )
if exist .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c.origin_version 
copy .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c.origin_version .\MCAL_Delivery\Original_Files\Fr\Fr_17_Eray_PBcfg.c >NUL )
if exist .\MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c.origin_version (
echo 	use %~d0%~p0MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c.origin_version 
copy .\MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c.origin_version .\MCAL_Delivery\Original_Files\Gpt\Gpt_PBcfg.c >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Adc_Irq\Adc_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\AscLin_Irq\AscLin_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Can_Irq\Can_17_McmCan_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Ccu6_Irq\Ccu6_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dma_Irq\Dma_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Dsadc_Irq\Dsadc_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Eru_Irq\Eru_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\EthV2_Irq\Eth_17_GEthMacV2_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Fls_Irq\Fls_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gpt12_Irq\Gpt12_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Gtm_Irq\Gtm_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Hssl_Irq\Hssl_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\I2c_Irq\I2c_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Sent_Irq\Sent_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Spi_Irq\Spi_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\AppSw\Tricore\DemoMcal\Demo_Irq\Stm_Irq\Stm_Irq.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Autosar_Srv\Mcal_SafetyError.c >NUL )
if exist .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.EB_update
copy .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h.EB_update .\MCAL_Delivery\DemoWorkspace\McalDemo\TC38A\0_Src\BaseSw\Infra\Irq\ssc\inc\Irq.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\inc\Adc_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Adc_Aurix2G\generate\template\src\Adc_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\config\AS440\CanTrcv_17_W9255.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\inc\CanTrcv_17_W9255_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\CanTrcv_17_W9255_Aurix2G\generate\template\src\CanTrcv_17_W9255_Cfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\config\AS440\Can_17_McmCan.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\inc\Can_17_McmCan_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Can_17_McmCan_Aurix2G\generate\template\src\Can_17_McmCan_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\inc\Dma_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dma_Aurix2G\generate\template\src\Dma_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\inc\Dsadc_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Dsadc_Aurix2G\generate\template\src\Dsadc_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\config\AS440\Eth_17_GEthMacV2.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\inc\Eth_17_GEthMacV2_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Eth_17_GEthMacV2_Aurix2G\generate\template\src\Eth_17_GEthMacV2_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\inc\Fee_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fee_Aurix2G\generate\template\src\Fee_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\inc\Fls_17_Dmu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fls_17_Dmu_Aurix2G\generate\template\src\Fls_17_Dmu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\config\AS440\Fr_17_Eray.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_Cfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\inc\Fr_17_Eray_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Fr_17_Eray_Aurix2G\generate\template\src\Fr_17_Eray_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\config\AS440\Gpt.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\inc\Gpt_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Gpt_Aurix2G\generate\template\src\Gpt_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\inc\I2c_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\I2c_Aurix2G\generate\template\src\I2c_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\inc\Icu_17_TimerIp_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Icu_17_TimerIp_Aurix2G\generate\template\src\Icu_17_TimerIp_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\inc\Iom_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Iom_Aurix2G\generate\template\src\Iom_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\inc\Lin_17_AscLin_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Lin_17_AscLin_Aurix2G\generate\template\src\Lin_17_AscLin_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\inc\Mcu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Mcu_Aurix2G\generate\template\src\Mcu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\inc\Ocu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Ocu_Aurix2G\generate\template\src\Ocu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\inc\Port_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Port_Aurix2G\generate\template\src\Port_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\inc\Pwm_17_GtmCcu6_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Pwm_17_GtmCcu6_Aurix2G\generate\template\src\Pwm_17_GtmCcu6_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\inc\Sent_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Sent_Aurix2G\generate\template\src\Sent_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\inc\Smu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Smu_Aurix2G\generate\template\src\Smu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\Spi_checks.m >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\inc\Spi_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Spi_Aurix2G\generate\template\src\Spi_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\inc\Uart_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Uart_Aurix2G\generate\template\src\Uart_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\config\AS440\Wdg_17_Scu.xdm >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\inc\Wdg_17_Scu_PBcfg.h >NUL )
if exist .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.EB_update
copy .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c.EB_update .\MCAL_Delivery\McIsar\PluginsTresos\eclipse\plugins\Wdg_17_Scu_Aurix2G\generate\template\src\Wdg_17_Scu_PBcfg.c >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.EB_update
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h.EB_update .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx.h >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.EB_update
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h.EB_update .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\Bfx\ssc\inc\Bfx_Local.h >NUL )
if exist .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.EB_update (
echo 	use %~d0%~p0MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.EB_update
copy .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h.EB_update .\MCAL_Delivery\McIsar\Src\Mcal\Tricore\McalLib\ssc\inc\Mcal_Compiler.h >NUL )
if exist .\templates\Spi_UserCode.c.EB_update (
echo 	use %~d0%~p0templates\Spi_UserCode.c.EB_update
copy .\templates\Spi_UserCode.c.EB_update .\templates\Spi_UserCode.c >NUL )
if exist .\templates\Spi_UserCode.h.EB_update (
echo 	use %~d0%~p0templates\Spi_UserCode.h.EB_update
copy .\templates\Spi_UserCode.h.EB_update .\templates\Spi_UserCode.h >NUL )
:copy_end
