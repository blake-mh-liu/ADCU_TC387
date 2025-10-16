/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==[Includes]================================================================*/

#include <Cal_Trace.h>
#include <Cal_Cfg.h>
#include <Cal_Version.h>


/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/



/*==[Declaration of functions with internal linkage]==========================*/



/*==[Constants with internal linkage]=========================================*/



/*==[Variables with internal linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Constants with external linkage]=========================================*/



/*==[Definition of functions with external linkage]===========================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

[!IF "'true' = node:value(as:modconf('Cal')/CalGeneral/CalVersionInfoApi)"!][!//


FUNC(void, CAL_CODE) Cal_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CAL_APPL_DATA) versionInfo
)
{
  DBG_CAL_GETVERSIONINFO_ENTRY(versionInfo);

  if (NULL_PTR != versionInfo)
  {
    /* !LINKSTO CAL0706, 1
     */
    versionInfo->vendorID         = CAL_VENDOR_ID;
    versionInfo->moduleID         = CAL_MODULE_ID;
    versionInfo->sw_major_version = CAL_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = CAL_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = CAL_SW_PATCH_VERSION;
  }

  DBG_CAL_GETVERSIONINFO_EXIT(versionInfo);
}
[!ENDIF!][!//

#define CAL_STOP_SEC_CODE
#include <MemMap.h>



/*==[Definition of functions with internal linkage]===========================*/

