/**
 * \file
 *
 * \brief AUTOSAR MemIf
 *
 * This file contains the implementation of the AUTOSAR
 * module MemIf.
 *
 * \version 5.11.20
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef MEMIF_CFG_H
#define MEMIF_CFG_H
[!VAR "MemIf_InternalCfg" = "'false'"!][!//
[!INCLUDE "MemIf_CommonCfg.m"!][!//

/*==================[includes]==============================================*/
/* !LINKSTO MemIf.SWS_MemIf_00037,1 */
#include <Std_Types.h>                            /* AUTOSAR standard types     */
#include <TSAutosar.h>                            /* EB specific standard types */

/*==================[macros]================================================*/
#if (defined MEMIF_MEMACC_USAGE)
#error MEMIF_MEMACC_USAGE is already defined
#endif
/** \brief Macro switch for MemAcc usage */
#define MEMIF_MEMACC_USAGE                [!//
[!IF "node:existsAndTrue(MemIfGeneral/MemIfMemAccUsage)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined MEMIF_DEV_ERROR_DETECT)
#error MEMIF_DEV_ERROR_DETECT is already defined
#endif /* if (defined MEMIF_DEV_ERROR_DETECT) */
/** \brief En-/disable development error tracer checks */
#define MEMIF_DEV_ERROR_DETECT   [!//
[!IF "node:existsAndTrue(MemIfGeneral/MemIfDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined MEMIF_MAXIMUM_NUMBER_OF_DEVICES)
#error MEMIF_MAXIMUM_NUMBER_OF_DEVICES is already defined
#endif /* if (defined MEMIF_MAXIMUM_NUMBER_OF_DEVICES) */
/** \brief Maximum number of the underlying memory abstraction modules
 **
 ** Largest Driver Index or 1 if only one abstraction module is present */
[!IF "$NumDevices > 1"!][!//
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!]
#define MEMIF_MAXIMUM_NUMBER_OF_DEVICES  [!"num:i($OldDeviceIndex+1)"!]U
[!ELSE!]
#define MEMIF_MAXIMUM_NUMBER_OF_DEVICES  [!"num:i($OldMemAccAddressAreaId+1)"!]U
[!ENDIF!]
[!ELSE!][!//
#define MEMIF_MAXIMUM_NUMBER_OF_DEVICES 1U
[!ENDIF!][!//
#if (defined MEMIF_VERSION_INFO_API)
#error MEMIF_VERSION_INFO_API is already defined
#endif /* if (defined MEMIF_VERSION_INFO_API) */
/** \brief En-/disable API version information */
#define MEMIF_VERSION_INFO_API   [!//
[!IF "node:existsAndTrue(MemIfGeneral/MemIfVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*==================[type definitions]======================================*/

/*==================[external data]=========================================*/

#endif /* ifndef MEMIF_CFG_H */
/*==================[end of file]===========================================*/
