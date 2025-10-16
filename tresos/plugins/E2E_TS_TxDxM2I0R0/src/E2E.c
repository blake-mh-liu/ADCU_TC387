/**
 * \file
 *
 * \brief AUTOSAR E2E
 *
 * This file contains the implementation of the AUTOSAR
 * module E2E.
 *
 * \version 2.0.22
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
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer
 * to void into pointer to object.
 *
 * Reason:
 * The uint8 pointer cast is used for byte wise
 * initialization of the complete VersionInfo
 * struct with zeros in order to ensure
 * compatibility with ASR 3.2.
 *
 */

/*==================[inclusions]=============================================*/

#include <E2E.h>          /* E2E library */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

/*==================[internal constants]=====================================*/

/*==================[internal data]==========================================*/

/*==================[external function definition]===========================*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>

FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
)
{
   if (NULL_PTR != VersionInfo)
   {
      uint32 i;

      /* Initialize complete struct with zeros.
       * This ensures compatibility with ASR 3.2 which additionally
       * contains the parameter instanceId which must be set to 0.
       */
      for (i=0U; i<(uint32)(sizeof(Std_VersionInfoType)); i++)
      {
         /* Deviation MISRAC2012-1 */
         ((P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA))
               ((P2VAR(void, AUTOMATIC, E2E_APPL_DATA)) VersionInfo))[i] = 0U;
      }

      VersionInfo->vendorID         = E2E_VENDOR_ID;
      VersionInfo->moduleID         = E2E_MODULE_ID;
      VersionInfo->sw_major_version = E2E_SW_MAJOR_VERSION;
      VersionInfo->sw_minor_version = E2E_SW_MINOR_VERSION;
      VersionInfo->sw_patch_version = E2E_SW_PATCH_VERSION;
   }
}

FUNC(Std_ReturnType, E2E_CODE) E2E_EB_MethodCheck
(
   uint32 SourceID,
   Std_MessageTypeType MessageType,
   Std_MessageResultType MessageResult
)
{
    Std_ReturnType RetVal;

    if (SourceID > E2E_EB_SOURCEID_MAXVALUE)
    {
        RetVal = E2E_E_INPUTERR_WRONG;
    }
    else if (E2E_EB_MethodMessageCheck(MessageType, MessageResult) != E2E_E_OK)
    {
        RetVal = E2E_E_INPUTERR_WRONG;
    }
    else
    {
        RetVal = E2E_E_OK;
    }

    return RetVal;
}

FUNC(Std_ReturnType, E2E_CODE) E2E_EB_MethodMessageCheck
(
   Std_MessageTypeType MessageType,
   Std_MessageResultType MessageResult
)
{
    Std_ReturnType RetVal;

    if((MessageType != STD_MESSAGETYPE_REQUEST) &&
        (MessageType != STD_MESSAGETYPE_RESPONSE))
    {
        RetVal = E2E_E_INPUTERR_WRONG;
    }
    else if ((MessageResult != STD_MESSAGERESULT_OK) &&
        (MessageResult != STD_MESSAGERESULT_ERROR))
    {
        RetVal = E2E_E_INPUTERR_WRONG;
    }
    else
    {
        RetVal = E2E_E_OK;
    }

    return RetVal;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>

/*==================[internal function definition]===========================*/

/*==================[end of file]============================================*/
