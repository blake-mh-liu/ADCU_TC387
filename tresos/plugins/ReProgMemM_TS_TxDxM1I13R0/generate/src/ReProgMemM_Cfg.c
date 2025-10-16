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

/*==[Includes]================================================================*/
#include "Std_Types.h"               /* AUTOSAR standard types */
#include "ReProgMemM_Cfg.h"
#include "ReProgMemM.h"
/*==[Macros]==================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/
[!AUTOSPACING!]
[!VAR "MEMORY_MAX"="num:dectoint(count(MemoryConfig/Memory/*))"!][!//
[!VAR "FLASH_SECTORS_DESCRIPTION_MAX"="num:dectoint(count(FlashSectors/FlashSectorsTable/*))"!][!//

#define REPROGMEMM_START_SEC_CONST_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

CONST(REPROGMEMM_CfgMemory_t, ReProgMemM_CONST) m_astReProgMemMMemoryCfg[REPROGMEMM_MEMORY_NB] =
{
[!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!][!//
    [!VAR "MEMORY_TYPE"="text:toupper(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Memory_Type)"!][!//
    [!VAR "MEMORY_MIN_VALUE_TO_WRITE"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Min_Value_To_Write)"!][!//
    [!VAR "MEMORY_BLOCK_LEN"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/BlockLength)"!][!//
    [!VAR "MEMORY_ADDRESS_OFFSET"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Addr_Offset)"!][!//
    [!VAR "MEMORY_ERASE_VALUE"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Erase_Value)"!][!//
    [!VAR "MEMORY_START_ADDRESS"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Memory_Start_address)"!][!//
    [!VAR "MEMORY_LENGTH"="num:inttohex(MemoryConfig/Memory/*[number($MEMORY_IDX)]/Memory_Length)"!][!//
    {
        [!WS "8"!]REPROGMEMM_MEM_TYPE_[!"$MEMORY_TYPE"!], /*selected Memory Type */
        [!WS "8"!][!"$MEMORY_MIN_VALUE_TO_WRITE"!]U, /* memory minimum value to write */
        [!WS "8"!][!"$MEMORY_BLOCK_LEN"!]U, /* block length value to be provided in RequestDownload response */
        [!WS "8"!][!"$MEMORY_ADDRESS_OFFSET"!]U, /* start address offset for the memory */
        [!WS "8"!][!"$MEMORY_ERASE_VALUE"!]U, /* value to set for each byte when the memory is erased */
        [!WS "8"!][!"$MEMORY_START_ADDRESS"!]U, /* selected memory start address */
        [!WS "8"!][!"$MEMORY_LENGTH"!]U, /* selected memory length */
    },
[!ENDFOR!][!//
};

CONST(REPROGMEMM_CfgMemorySectorsProt_t, ReProgMemM_CONST) m_astReProgMemMMemorySecProtCfg[REPROGMEMM_FLASH_SECTORS_ELEMENTS] =
{
[!VAR "NB_RANGE_SECTOR_DECLARATION"="num:dectoint(count(FlashSectors/FlashSectorsTable/*))"!]
[!IF "$NB_RANGE_SECTOR_DECLARATION = 0"!]
[!ERROR "At least one range sector address must be configured!!!"!]
[!ENDIF!]
[!FOR "FLASH_SECTORS_DESCRIPTION_IDX" = "1" TO "$FLASH_SECTORS_DESCRIPTION_MAX"!]
[!IF "(FlashSectors/FlashSectorsTable/*[number($FLASH_SECTORS_DESCRIPTION_IDX)]/Programmable = 'true')"!]
[!VAR "FLASH_PROTECTION_TYPE"= "'REPROGMEMM_SECTOR_NOT_PROTECTED' "!]
[!ELSE!]
[!VAR "FLASH_PROTECTION_TYPE"= "'REPROGMEMM_SECTOR_WRITE_PROTECTED' "!]
[!ENDIF!]
    {
        {
            /* PFLASH PROTECTION PASSWORD from FLSLOADER */
            REPROGMEMM_PFLASH_PASSWORD_PW00,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 00 */
            REPROGMEMM_PFLASH_PASSWORD_PW01,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 01 */
            REPROGMEMM_PFLASH_PASSWORD_PW10,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 10 */
            REPROGMEMM_PFLASH_PASSWORD_PW11,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 11 */
            REPROGMEMM_PFLASH_PASSWORD_PW20,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 20 */
            REPROGMEMM_PFLASH_PASSWORD_PW21,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 21 */
            REPROGMEMM_PFLASH_PASSWORD_PW30,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 30 */
            REPROGMEMM_PFLASH_PASSWORD_PW31,[!WS "10"!]/* PFLASH PROTECTION PASSWORD WORD 31 */
        },
        /*Start_Address     Length                Sector_Size           Protection */
        [!"num:inttohex(FlashSectors/FlashSectorsTable/*[number($FLASH_SECTORS_DESCRIPTION_IDX)]/Start_Address,8)"!]U,[!WS "8"!][!"num:inttohex(FlashSectors/FlashSectorsTable/*[number($FLASH_SECTORS_DESCRIPTION_IDX)]/Length,8)"!]U,[!WS "10"!][!"num:inttohex(FlashSectors/FlashSectorsTable/*[number($FLASH_SECTORS_DESCRIPTION_IDX)]/Sector_Size,8)"!]U,[!WS "10"!][!"$FLASH_PROTECTION_TYPE"!]
    },
[!ENDFOR!]
};
#define REPROGMEMM_STOP_SEC_CONST_UNSPECIFIED
#include <ReProgMemM_MemMap.h>
/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/


/*==[Definition of functions with internal linkage]===========================*/


/** @} doxygen end group definition */
/*==================[end of file]===========================================*/
