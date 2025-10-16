/**
 * \file
 *
 * \brief AUTOSAR ApplTemplates
 *
 * This file contains the implementation of the AUTOSAR
 * module ApplTemplates.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef PLATFORMS_MODULES_H
#define PLATFORMS_MODULES_H


/*==================[includes]==============================================*/

/*==================[macros]================================================*/

/*
 * Here you can define platform-specific names for init functions
 * and configuration pointer names when modules require other init function
 * names or configuration pointer names than defined in BswM_Modules.h
 * or Base_Modules.h.
 */

/* EcuM basicTempalte cfg is using following defines to keep them common */
#define BASE_MCU_CONFIG_PTR &Mcu_ConfigRoot[0]

#define SPI_INIT_FUNC         Spi_Init
#define BASE_SPI_CONFIG_PTR   &Spi_ConfigRoot[0]

#define FLS_INIT_FUNC         Fls_17_Pmu_Init
#define BASE_FLS_CONFIG_PTR   &Fls_17_Pmu_ConfigRoot[0]

#define FEE_INIT_FUNC         Fee_Init
#define BASE_FEE_CONFIG_PTR

#define CAN_INIT_FUNC         Can_17_MCanP_Init
#define BASE_CAN_CONFIG_PTR   &Can_17_MCanP_ConfigRoot[0]

#define LIN_INIT_FUNC       Lin_17_AscLin_Init
#define BASE_LIN_CONFIG_PTR &Lin_ConfigRoot[0]

/* For Infineon FlexRay driver comment next line in */
 #define FR_INIT_FUNC          Fr_17_Eray_Init
 #define BASE_FR_CONFIG_PTR    &Fr_17_Eray_ConfigRoot[0]
/* For EB FlexRay driver comment next line in */
/*#define FR_INIT_FUNC          Fr_Init*/
/*#define BASE_FR_CONFIG_PTR    &FrMultipleConfiguration*/

#define ETH_INIT_FUNC       Eth_17_EthMac_Init
#define BASE_ETH_CONFIG_PTR &Eth_ConfigRoot[0]

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef PLATFORMS_MODULES_H */

/*==================[end of file]===========================================*/
