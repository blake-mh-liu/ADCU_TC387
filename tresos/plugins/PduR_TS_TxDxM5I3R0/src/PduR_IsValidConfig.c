/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \version 5.3.55
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <PduR_Cfg.h>            /* Compile time configuration */
#if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF)
#include <TSAutosar.h>            /* EB specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part for service ID) */
#include <PduR_Api_Depend.h>      /* Public API (dependent part) */
#include <PduR_Lcfg.h>            /* Link time configuration */
#include <TSPBConfig_Signature.h> /* Post build signature check */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#define PDUR_START_SEC_CODE_CC_BLOCK
#include <PduR_MemMap.h>

FUNC(Std_ReturnType, PDUR_CODE) PduR_IsValidConfig
(
   P2CONST(void, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
)
{
    /* Assume an invalid configuration */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_PDUR_ISVALIDCONFIG_ENTRY(ConfigPtr);

    if (ConfigPtr != NULL_PTR)
    {
        CONSTP2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_APPL_CONST) PBConfigPtr =
                (P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_APPL_CONST)) ConfigPtr;

        /* Check if the configuration fits to the platform */
        if (TS_PlatformSigIsValid(PBConfigPtr->PduR_PlatformSignature) == TRUE)
        {
            /* Validate the post build configuration against the compile time configuration */
            if (PDUR_CFG_SIGNATURE == PBConfigPtr->PduR_CfgSignature)
            {
                /* Validate the post build configuration against the link time configuration */
                if (PduRLcfgSignature == PBConfigPtr->PduR_LcfgSignature)
                {
                   /* Validate the post build configuration against the published information
                      configuration */
                   if (PDUR_PUBLIC_INFO_SIGNATURE == PBConfigPtr->PduR_PublicInfoSignature)
                   {
                      /* Indicate that the configuration is valid */
                      RetVal = E_OK;
                   }
                }
            }
        }
    }

    DBG_PDUR_ISVALIDCONFIG_EXIT(RetVal, ConfigPtr);
    return RetVal;
}

/* AUTOSAR Memory Mapping - end section for code */
#define PDUR_STOP_SEC_CODE_CC_BLOCK
#include <PduR_MemMap.h>

/*==================[internal function definitions]=========================*/

#else /* if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_IsValidConfigType;


#endif /* if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF) */

/*==================[end of file]===========================================*/
