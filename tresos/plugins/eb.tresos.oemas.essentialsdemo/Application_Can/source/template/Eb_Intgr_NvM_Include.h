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
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef NVM_INCLUDE_H
#define NVM_INCLUDE_H


/*==================[includes]==============================================*/

#include <Base_Modules.h>               /* Module enable defines */

#if defined(BASE_DEM_ENABLED) && (BASE_DEM_ENABLED==STD_ON)
#include <Dem.h>    /* Dem has an RAM block */
#include <Dem_NvMCbk.h>
#endif

#if defined(BASE_COMM_ENABLED)
#if (BASE_COMM_ENABLED==STD_ON)
#include <ComM.h>                       /* ComM has an RAM block */
#endif
#endif

#include <Dcm_Dsl_RoeServices.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define NVM_START_SEC_CONFIG_DATA_APPL_CONST
#include <MemMap.h>
extern CONST(uint8, NVM_APPL_CONST) DidF190_DefaultData[];
#define NVM_STOP_SEC_CONFIG_DATA_APPL_CONST
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef NVM_INCLUDE_H */

/*==================[end of file]===========================================*/
