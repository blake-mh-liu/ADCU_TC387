/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \version 5.21.4
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef COMM_TYPES_H
#define COMM_TYPES_H

/*==================[inclusions]============================================*/
[!INCLUDE "../../generate_macros/ComM_Functions.m"!]

#include <ComM_BSW_Types.h>/* Types required in own module's implementation */
[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true'"!]
  [!CALL "GetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
  [!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]
    [!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0 "!]
      [!CALL "GetUsedUserOsApplications"!]
      [!FOR "Idx" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]
        [!VAR "CurrentOsApplication" = "string(text:split($FoundUserOsApplications,' ')[position() = $Idx])"!]
#include <Rte_ComM_User_[!"$CurrentOsApplication"!]_Type.h>
      [!ENDFOR!] [!/*[!FOR "Idx" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]*/!]
    [!ENDIF!] [!/*[!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0 "!]*/!]
  [!ELSE!] [!/*[!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]
#include <Rte_ComM_Type.h>       /* Include Symbols defined by RTE */  
  [!ENDIF!] [!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]
[!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true'"!]*/!]

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))

/* Provide the typedef for ComM_InhibitionStatusType only if it
 *  was not provided by RTE */
#ifndef RTE_TYPE_ComM_InhibitionStatusType
#define RTE_TYPE_ComM_InhibitionStatusType
/** \brief Inhibition Status Type
 *
 * Provide AUTOSAR 4.0 InhibitionStatusType as default to other BSW modules
 */
/* !LINKSTO ComM.SWS_ComM_00669,1 */
typedef ComM_ASR40_InhibitionStatusType ComM_InhibitionStatusType;
#endif
#endif /* COMM_MODE_LIMITATION_ENABLED ... */

/* Provide the typedef for ComM_UserHandleType only if it
 *  was not provided by RTE */
#ifndef RTE_TYPE_ComM_UserHandleType
#define RTE_TYPE_ComM_UserHandleType
/** \brief User Handle Type
 *
 * Provide AUTOSAR 4.0 UserHandleType as default to other BSW modules
 */
/* !LINKSTO ComM.SWS_ComM_00670,1 */
typedef ComM_ASR40_UserHandleType ComM_UserHandleType;
#endif

/* Provide the typedef for ComM_ModeType only if it
 *  was not provided by RTE */
#ifndef RTE_TYPE_ComM_ModeType
#define RTE_TYPE_ComM_ModeType
/** \brief Mode Type
 *
 * Provide AUTOSAR 4.0 ComM_ModeType as default to other BSW modules
 */
/* !LINKSTO ComM.SWS_ComM_00672,1 */
typedef ComM_ASR40_ModeType ComM_ModeType;
#endif

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef COMM_TYPES_H */
/*==================[end of file]===========================================*/
