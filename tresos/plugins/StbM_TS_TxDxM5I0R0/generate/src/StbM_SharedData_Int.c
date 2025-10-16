/**
 * \file
 *
 * \brief AUTOSAR StbM
 *
 * This file contains the implementation of the AUTOSAR
 * module StbM.
 *
 * \version 5.0.9
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!AUTOSPACING!]
[!INCLUDE "../include/StbM_Vars.m"!]

/** \addtogroup Synchronized Time Base Manager
 ** @{ */

/*==[Includes]================================================================*/

#include <StbM_Int_Cfg.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

[!IF "($StbMShareDataTimeBasesNumber > 0)"!]

#define STBM_START_SEC_VAR_CLEARED_TIME_DATA_UNSPECIFIED
#include <StbM_MemMap.h>

[!IF "($StbMSharedDataVersion = '1')"!]
/** \brief Variable that holds the Memory Shared Data of the Time Bases - version 1 */
VAR(StbM_SharedEthOffsetType, STBM_VAR_CLEARED) StbM_SharedEthOffsetData;
[!ELSE!]
/** \brief Variable that holds the Memory Shared Data of the Time Bases - version 2 */
VAR(uint8, STBM_VAR_CLEARED) StbM_SharedData[STBM_NUMBER_OF_INDEXES_FOR_VERSION_AND_TIMEBASENUMBER + (STBM_NUMBER_TIME_BASES_THAT_SHARE_DATA_MODULES*STBM_NUMBER_OF_SHAREDDATA_BYTES_PER_TIMEBASE)];
[!ENDIF!]

#define STBM_STOP_SEC_VAR_CLEARED_TIME_DATA_UNSPECIFIED
#include <StbM_MemMap.h>

[!ENDIF!]

/*==[Definition of functions with internal linkage]===========================*/

/** @} doxygen end group definition */
/*==================[end of file]===========================================*/

