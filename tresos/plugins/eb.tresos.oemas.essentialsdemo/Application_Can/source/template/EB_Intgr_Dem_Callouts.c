/**
 * \file
 *
 * \brief AUTOSAR GenericDemo
 *
 * This file contains the implementation of the AUTOSAR
 * module GenericDemo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <TSAutosar.h>     /* EB specific standard types, TS_PARAM_UNUSED() */

#include <Dem_Cfg.h>                             /* declaration of callouts */

#include <NvM.h>                                  /* NvM */
#include <Fee.h>                                  /* Fee */
#include <Fls.h>                                  /* Fls */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/


#define DEM_START_SEC_CODE
#include <MemMap.h>

/*------------------[Main callouts]-----------------------------------------*/


FUNC(void, DEM_APPL_CODE) Appl_TriggerMemoryStack(const NvM_BlockIdType BlockId)
{
   NvM_RequestResultType Result;

   do
   {
    NvM_MainFunction();
    Fee_MainFunction();
    Fls_MainFunction();
    NvM_GetErrorStatus(BlockId, &Result);
   }
   while (Result == NVM_REQ_PENDING);

}



#define DEM_STOP_SEC_CODE
#include <MemMap.h>


/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/

