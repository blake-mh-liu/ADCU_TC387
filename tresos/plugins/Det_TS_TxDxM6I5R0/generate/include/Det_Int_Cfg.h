/**
 * \file
 *
 * \brief AUTOSAR Det
 *
 * This file contains the implementation of the AUTOSAR
 * module Det.
 *
 * \version 6.5.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef DET_INT_CFG_H
#define DET_INT_CFG_H

/*==[Includes]================================================================*/

[!IF "node:exists(DetNotification)"!][!//
[!LOOP "DetNotification/DetHeaderFile/eb-list::*"!][!//
/* Include declaration of user defined callback function */
#include <[!"."!]>
[!ENDLOOP!][!//
[!ENDIF!][!//

/*==[Macros]==================================================================*/

/* !LINKSTO Det.EB_Ref.SWS_Det_00180.Signature,1 */
/* !LINKSTO Det.EB_Ref.SWS_Det_00180.ID,1 */

#if (defined DET_NOTIFICATIONS_DEVELOPMENT_ERROR)
#error DET_NOTIFICATIONS_DEVELOPMENT_ERROR is already defined
#endif

/* !LINKSTO Det.SWS_Det_00018,1 */
/* !LINKSTO Det.SWS_Det_00181,1 */
/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_DEVELOPMENT_ERROR(a,b,c,d)              \
          do                                    \
          {                                     \
[!IF "node:exists(DetNotification)"!][!//
[!LOOP "DetNotification/DetErrorHook/eb-list::*"!][!//
            [!"."!](a,b,c,d); \
[!ENDLOOP!][!//
[!ENDIF!][!//
          } while (0)

/* !LINKSTO Det.SWS_Det_00184,1 */
#if (defined DET_NOTIFICATIONS_RUNTIME_ERROR)
#error DET_NOTIFICATIONS_RUNTIME_ERROR is already defined
#endif

/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_RUNTIME_ERROR(a,b,c,d)              \
          do                                    \
          {                                     \
[!IF "node:exists(DetNotification)"!][!//
[!LOOP "DetNotification/DetReportRuntimeErrorCallout/eb-list::*"!][!//
            [!"."!](a,b,c,d); \
[!ENDLOOP!][!//
[!ENDIF!][!//
          } while (0)

/* !LINKSTO Det.SWS_Det_00187,1 */
#if (defined DET_NOTIFICATIONS_TRANSIENT_FAULT)
#error DET_NOTIFICATIONS_TRANSIENT_FAULT is already defined
#endif

/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_TRANSIENT_FAULT(a,b,c,d)              \
          do                                    \
          {                                     \
[!IF "node:exists(DetNotification)"!][!//
[!LOOP "DetNotification/DetReportTransientFaultCallout/eb-list::*"!][!//
            transientFaultRetVal |= [!"."!](a,b,c,d); \
[!ENDLOOP!][!//
[!ENDIF!][!//
          } while (0)

/** \brief Set the function parameters as unused if no error hook function is configured and the Breakpoint mode is used */
#define DET_REPORT_ERROR_STATUS_PARAMETERS \
          do                               \
          {                                \
[!IF "(as:modconf('Det')/DetGeneral/LoggingMode = 'Breakpoint') and
      (num:i(count(as:modconf('Det')/DetNotification/DetErrorHook/eb-list::*)) = 0) and
      (num:i(count(as:modconf('Det')/DetNotification/DetReportRuntimeErrorCallout/eb-list::*)) = 0) and
      (num:i(count(as:modconf('Det')/DetNotification/DetReportTransientFaultCallout/eb-list::*)) = 0)"!][!//
  TS_PARAM_UNUSED(ModuleId);               \
  TS_PARAM_UNUSED(InstanceId);             \
  TS_PARAM_UNUSED(ApiId);                  \
  TS_PARAM_UNUSED(ErrorId);                \
[!ENDIF!][!//
          } while (0)

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Functions with external linkage]=========================================*/

#endif /* ifndef DET_INT_CFG_H */

