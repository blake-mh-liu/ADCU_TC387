/**
 * \file
 *
 * \brief AUTOSAR ReProgMemM
 *
 * This file contains the implementation of the AUTOSAR
 * module ReProgMemM.
 *
 * \version 1.13.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 21.2 (required)
 * A reserved identifier or macro name shall not be declared.
 *
 * Reason:
 * Macros are defined inside the linker script.
 *
 */
#ifndef REPROGMEMM_CFG_H
#define REPROGMEMM_CFG_H


[!AUTOSPACING!]
/*==[Includes]================================================================*/
#include "ReProgMemM_Types.h"

/*==[Macros]==================================================================*/
[!IF "General/ReProgMemMServiceAPI/ReProgMemMVersionInfoApi = 'true'"!][!//
#define REPROGMEMM_VERSION_INFO_API      STD_ON
[!ELSE!][!//
#define REPROGMEMM_VERSION_INFO_API      STD_OFF
[!ENDIF!][!//
[!IF "General/ReProgMemMServiceAPI/ReProgMemMDevErrorDetect = 'true'"!][!//
#define REPROGMEMM_DEV_ERROR_DETECT      STD_ON
[!ELSE!][!//
#define REPROGMEMM_DEV_ERROR_DETECT      STD_OFF
[!ENDIF!][!//

[!VAR "MEMORY_MAX"="num:dectoint(count(MemoryConfig/Memory/*))"!][!//
#define REPROGMEMM_MEMORY_NB [!"$MEMORY_MAX"!]U


[!VAR "FLASH_USE" = "0"!]
[!VAR "FLASH_EXT_USE" = "0"!]
[!VAR "RAM_USE" = "0"!]
[!VAR "CUSTOM_MEMORY_USE" = "0"!]

[!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!][!//
      [!VAR "MEMORY_TYPE"="text:toupper(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Memory_Type)"!][!//
      [!IF "$MEMORY_TYPE = 'FLASH'"!]
          [!VAR "FLASH_USE" = "1"!]
      [!ELSEIF "$MEMORY_TYPE = 'FLASH_EXT'"!]
            [!VAR "FLASH_EXT_USE" = "1"!]
      [!ELSEIF "$MEMORY_TYPE = 'RAM'"!]
            [!VAR "RAM_USE" = "1"!]
     [!ELSE!]
            [!VAR "CUSTOM_MEMORY_USE" = "1"!]
      [!ENDIF!][!//
[!ENDFOR!]


[!IF "$FLASH_USE = 1"!]
#define REPROGMEMM_TOPO_FLASH_ENABLED                         STD_ON
[!ELSE!]
#define REPROGMEMM_TOPO_FLASH_ENABLED                         STD_OFF
[!ENDIF!]

[!IF "$FLASH_EXT_USE = 1"!]
#define REPROGMEMM_TOPO_FLASHEXT_ENABLED                      STD_ON
[!ELSE!]
#define REPROGMEMM_TOPO_FLASHEXT_ENABLED                      STD_OFF
[!ENDIF!]

[!IF "$RAM_USE = 1"!]
#define REPROGMEMM_RAM_MEMORY_USE                             STD_ON
[!ELSE!]
#define REPROGMEMM_RAM_MEMORY_USE                             STD_OFF
[!ENDIF!]

[!IF "$CUSTOM_MEMORY_USE = 1"!]
#define REPROGMEMM_CUSTOM_MEMORY_USE                          STD_ON
[!ELSE!]
#define REPROGMEMM_CUSTOM_MEMORY_USE                          STD_OFF
[!ENDIF!]


[!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
[!VAR "MEMORY_NAME"="text:toupper(name(MemoryConfig/Memory/*[number($MEMORY_IDX)]))"!]
[!VAR "MEMORY_ID"="num:inttohex(($MEMORY_IDX)-1)"!]
#define REPROGMEMM_MEMORY_[!"$MEMORY_NAME"!]                  [!"$MEMORY_ID"!]
[!ENDFOR!]

 /* Dual Memory bank feature */
[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
#define REPROGMEMM_DUALBANK_ENABLED                          STD_ON
[!ELSE!]
#define REPROGMEMM_DUALBANK_ENABLED                          STD_OFF
[!ENDIF!]

 /* Copy Flash routines from ROM to RAM */
[!IF "General/Copy_ROM_To_RAM = 'true'"!]
#define REPROGMEMM_COPY_ROM_TO_RAM_ENABLE                    STD_ON


#define REPROGMEMM_START_SEC_VAR_INIT_8
#include <ReProgMemM_MemMap.h>
/* These macros are used to define the address of the Flash routine in RAM memory */
/* __Flash_API_ROM_SECTION_START_ADDR shall be set to the start address of ROM section/group for Flash driver in the linker file */
/* __Flash_API_ROM_SECTION_END_ADDR shall be set to the end address of ROM section/group for Flash driver in the linker file */
/* __Flash_API_RAM_SECTION_START_ADDR shall be set to the start address of RAM section/group for Flash driver in the linker file */
/* __Flash_API_RAM_SECTION_END_ADDR shall be set to the end address of RAM section/group for Flash driver in the linker file */

/* ROM */
/* Deviation MISRAC2012-1 */
extern uint8 __Flash_API_ROM_SECTION_START_ADDR;
extern uint8 __Flash_API_ROM_SECTION_END_ADDR;

/* RAM */
/* Deviation MISRAC2012-1 */
extern uint8 __Flash_API_RAM_SECTION_START_ADDR;
extern uint8 __Flash_API_RAM_SECTION_END_ADDR;

#define REPROGMEMM_STOP_SEC_VAR_INIT_8
#include <ReProgMemM_MemMap.h>

#define REPROGMEMM_COPY_FLASH_ROUTINES                       STD_ON
#define REPROGMEMM_FLASH_ROUTINES_RAM_ADDR_START             &__Flash_API_RAM_SECTION_START_ADDR
#define REPROGMEMM_FLASH_ROUTINES_RAM_ADDR_END               &__Flash_API_RAM_SECTION_END_ADDR
#define REPROGMEMM_FLASH_ROUTINES_ROM_ADDR_START             &__Flash_API_ROM_SECTION_START_ADDR
#define REPROGMEMM_FLASH_ROUTINES_ROM_ADDR_END               &__Flash_API_ROM_SECTION_END_ADDR

[!ELSE!]
#define REPROGMEMM_COPY_ROM_TO_RAM_ENABLE                    STD_OFF
#define REPROGMEMM_COPY_FLASH_ROUTINES                       STD_OFF
[!ENDIF!]

/* Flash memory configurations */
#define REPROGMEMM_FLASH_PAGE_SIZE                           [!"General/FlashPageSize"!]U
#define REPROGMEMM_FLASH_PAGE_PADDING_VALUE                  [!"General/FlashPagePaddingValue"!]U

[!VAR "FLASH_SECTORS_DESCRIPTION_MAX"="num:dectoint(count(FlashSectors/FlashSectorsTable/*))"!][!//
#define REPROGMEMM_FLASH_SECTORS_DESCRIPT_NB                 [!"$FLASH_SECTORS_DESCRIPTION_MAX"!]U
#define REPROGMEMM_FLASH_SECTORS_ELEMENTS                    [!"$FLASH_SECTORS_DESCRIPTION_MAX"!]U

 /* Number of PFLASH configurations */
[!IF "node:exists(as:modconf('FlsLoader'))"!]
#define REPROGMEMM_PFLASH_PASSWORD_PW00                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW0_0),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW01                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW0_1),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW10                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW1_0),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW11                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW1_1),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW20                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW2_0),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW21                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW2_1),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW30                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW3_0),8)"!]U
#define REPROGMEMM_PFLASH_PASSWORD_PW31                      [!"num:inttohex(num:i(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW3_1),8)"!]U

[!VAR "NB_PFLASH_CONFIG"="num:dectoint(count(as:modconf('FlsLoader')[1]/FlsLoaderPFLASHConfig/*))"!]
[!IF "$NB_PFLASH_CONFIG = 0"!]
[!ERROR "At least one range sector address must be configured!!!"!]
[!ELSE!]
#define REPROGMEMM_PFLASH_CONFIG                   [!"$NB_PFLASH_CONFIG"!]U
[!ENDIF!]
[!ELSE!]
#define REPROGMEMM_PFLASH_CONFIG                   1U

#define REPROGMEMM_PFLASH_PASSWORD_PW00            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW01            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW10            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW11            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW20            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW21            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW30            0x00000000U
#define REPROGMEMM_PFLASH_PASSWORD_PW31            0x00000000U
[!ENDIF!]

 /* Address offset */
[!IF "General/Custom_Address_Offset_Used = 'true'"!]
#define REPROGMEMM_CUSTOM_OFFSET_ENABLE            STD_ON
[!ELSE!]
#define REPROGMEMM_CUSTOM_OFFSET_ENABLE            STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('MemAcc'))"!]
#define REPROGMEMM_USE_MEMACC_ENABLE               STD_ON
[!ELSE!]
#define REPROGMEMM_USE_MEMACC_ENABLE               STD_OFF
[!ENDIF!]

/* Number of sectors to erase at each turn */
#define REPROGMEMM_SIZE_PER_TURN                   [!"General/SectorsToErasePerTurn"!]U
/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/
#define REPROGMEMM_START_SEC_CONST_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

extern CONST(REPROGMEMM_CfgMemory_t,            ReProgMemM_CONST) m_astReProgMemMMemoryCfg[REPROGMEMM_MEMORY_NB];
extern CONST(REPROGMEMM_CfgMemorySectorsProt_t, ReProgMemM_CONST) m_astReProgMemMMemorySecProtCfg[REPROGMEMM_FLASH_SECTORS_ELEMENTS];

#define REPROGMEMM_STOP_SEC_CONST_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

/*==[Variables with external linkage]=========================================*/



/*==[Definition of functions with external linkage]===========================*/

#endif /* #ifndef REPROGMEMM_CFG_H */

/*==================[end of file]=============================================*/

