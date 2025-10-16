/**
 * \file
 *
 * \brief AUTOSAR Crc
 *
 * This file contains the implementation of the AUTOSAR
 * module Crc.
 *
 * \version 6.11.20
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef CRC_CFG_H
#define CRC_CFG_H

/* !LINKSTO Crc.ASR40.SWS_Crc_00024,1 */

/* This file contains the generated Crc module configuration. */

/*==================[includes]===============================================*/

/*==================[macros]=================================================*/

#if (defined CRC_DEV_ERROR_DETECT)
# error CRC_DEV_ERROR_DETECT already defined
#endif
/** \brief Macro switch for DET usage */
#define CRC_DEV_ERROR_DETECT             [!//
[!IF "node:existsAndTrue(CrcGeneral/CrcDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*------------------[CRC calculation method options]-------------------------*/

#if (defined CRC_8_ENABLED)
# error CRC_8_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC8 routine */
#define CRC_8_ENABLED         [!//
[!IF "node:exists(CrcGeneral/Crc8Mode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_8_TABLE_SIZE)
# error CRC_8_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC8 lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_8_TABLE_SIZE      [!//
[!IF "node:exists(CrcGeneral/Crc8Mode) and (CrcGeneral/Crc8Mode != 'CRC_8_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc8TableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_8H2F_ENABLED)
# error CRC_8H2F_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC8H2F routine */
#define CRC_8H2F_ENABLED      [!//
[!IF "node:exists(CrcGeneral/Crc8H2FMode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_8H2F_TABLE_SIZE)
# error CRC_8H2F_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC8H2F lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_8H2F_TABLE_SIZE   [!//
[!IF "node:exists(CrcGeneral/Crc8H2FMode) and (CrcGeneral/Crc8H2FMode != 'CRC_8H2F_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc8H2FTableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_16_ENABLED)
# error CRC_16_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC16 routine */
#define CRC_16_ENABLED        [!//
[!IF "node:exists(CrcGeneral/Crc16Mode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_16_TABLE_SIZE)
# error CRC_16_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC16 lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_16_TABLE_SIZE     [!//
[!IF "node:exists(CrcGeneral/Crc16Mode) and (CrcGeneral/Crc16Mode != 'CRC_16_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc16TableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_16ARC_ENABLED)
# error CRC_16ARC_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC16ARC routine */
#define CRC_16ARC_ENABLED        [!//
[!IF "node:exists(CrcGeneral/Crc16ARCMode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_16_ARC_TABLE_SIZE)
# error CRC_16_ARC_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC16ARC lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_16_ARC_TABLE_SIZE     [!//
[!IF "node:exists(CrcGeneral/Crc16ARCMode) and (CrcGeneral/Crc16ARCMode != 'CRC_16_ARC_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc16ARCTableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_32_ENABLED)
# error CRC_32_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC32 routine */
#define CRC_32_ENABLED        [!//
[!IF "node:exists(CrcGeneral/Crc32Mode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_32_TABLE_SIZE)
# error CRC_32_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC32 lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_32_TABLE_SIZE     [!//
[!IF "node:exists(CrcGeneral/Crc32Mode) and (CrcGeneral/Crc32Mode != 'CRC_32_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc32TableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_32P4_ENABLED)
# error CRC_32P4_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC32P4 routine */
#define CRC_32P4_ENABLED        [!//
[!IF "node:exists(CrcGeneral/Crc32P4Mode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_32P4_TABLE_SIZE)
# error CRC_32P4_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC32P4 lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_32P4_TABLE_SIZE     [!//
[!IF "node:exists(CrcGeneral/Crc32P4Mode) and (CrcGeneral/Crc32P4Mode != 'CRC_32P4_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc32P4TableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

#if (defined CRC_64_ENABLED)
# error CRC_64_ENABLED already defined
#endif
/** \brief Switch to en/disable the CRC64 routine */
#define CRC_64_ENABLED        [!//
[!IF "node:exists(CrcGeneral/Crc64Mode)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRC_64_TABLE_SIZE)
# error CRC_64_TABLE_SIZE already defined
#endif
/** \brief Number of elements in CRC64 lookup table
 *
 * If size is 0 table based calculation is deactivated. */
#define CRC_64_TABLE_SIZE     [!//
[!IF "node:exists(CrcGeneral/Crc64Mode) and (CrcGeneral/Crc64Mode != 'CRC_64_RUNTIME')"!][!//
[!IF "(CrcGeneral/Crc64TableSize = 'CRC_TABLE_16_ELEMENTS')"!][!//
16U[!ELSE!]256U[!ENDIF!]
[!ELSE!]0U[!ENDIF!]

/*------------------[API configuration options]------------------------------*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef CRC_CFG_H */
/*==================[end of file]============================================*/
