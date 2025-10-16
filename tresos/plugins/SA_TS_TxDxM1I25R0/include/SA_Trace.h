
#ifndef SA_TRACE_H
#define SA_TRACE_H
/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Trace.h                      */
/*%%  |                             |  %%  \brief SA trace debug mode            */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.25.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*==================[inclusions]============================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include "EB_Prj.h"
/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_INIT_ENTRY
/** \brief Entry point of function SA_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_INIT_EXIT
/** \brief Exit point of function SA_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_MANAGE_ENTRY
/** \brief Entry point of function SA_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_MANAGE_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_MANAGE_EXIT
/** \brief Exit point of function SA_Manage()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_MANAGE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GETSEED_ENTRY
/** \brief Entry point of function SA_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_GETSEED_ENTRY(aubSeed)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GETSEED_EXIT
/** \brief Exit point of function SA_GetSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_GETSEED_EXIT(eSaStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_COMPAREKEY_ENTRY
/** \brief Entry point of function SA_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_COMPAREKEY_ENTRY(aubReceivedKey)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_COMPAREKEY_EXIT
/** \brief Exit point of function SA_CompareKey()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_COMPAREKEY_EXIT(eSaStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_INITCRYPTO_ENTRY
/** \brief Entry point of function SA_InitCrypto()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_INITCRYPTO_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_INITCRYPTO_EXIT
/** \brief Exit point of function SA_InitCrypto()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_INITCRYPTO_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GENERATERANDOMNUMBER_ENTRY
/** \brief Entry point of function SA_GenerateRandomNumber()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_GENERATERANDOMNUMBER_ENTRY(aubRandomNumber)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GENERATERANDOMNUMBER_EXIT
/** \brief Exit point of function SA_GenerateRandomNumber()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_GENERATERANDOMNUMBER_EXIT(m_eSaStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GENERATERANDOMCALLBACK_ENTRY
/** \brief Entry point of function SA_GenerateRandomCallback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_GENERATERANDOMCALLBACK_ENTRY(eCsmResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GENERATERANDOMCALLBACK_EXIT
/** \brief Exit point of function SA_GenerateRandomCallback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_GENERATERANDOMCALLBACK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_ENTRY
/** \brief Entry point of function SA_SignatureVerifAndHashCallback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_ENTRY(eCsmResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_EXIT
/** \brief Exit point of function SA_SignatureVerifAndHashCallback()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_VERIFYSIGNATURE_ENTRY
/** \brief Entry point of function SA_VerifySignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_VERIFYSIGNATURE_ENTRY(pstAsymPublicKey)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_VERIFYSIGNATURE_EXIT
/** \brief Exit point of function SA_VerifySignature()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_VERIFYSIGNATURE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_VERIFYSIGNATUREUPDATE_ENTRY
/** \brief Entry point of function SA_VerifySignatureUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_VERIFYSIGNATUREUPDATE_ENTRY(pubSignature)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_VERIFYSIGNATUREUPDATE_EXIT
/** \brief Exit point of function SA_VerifySignatureUpdate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_VERIFYSIGNATUREUPDATE_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_CSMNOTIFICATION_ENTRY
/** \brief Entry point of function SA_CsmNotification()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_CSMNOTIFICATION_ENTRY(eCsmResult)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_CSMNOTIFICATION_EXIT
/** \brief Exit point of function SA_CsmNotification()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_CSMNOTIFICATION_EXIT(E_OK)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GETSTATUS_ENTRY
/** \brief Entry point of function SA_GetStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_GETSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_GETSTATUS_EXIT
/** \brief Exit point of function SA_GetStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_GETSTATUS_EXIT(m_eSaStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_ANTISCANNING_ENTRY
/** \brief Entry point of function SA_Antiscanning()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SA_ANTISCANNING_ENTRY(ubKeyMatch)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SA_ANTISCANNING_EXIT
/** \brief Exit point of function SA_Antiscanning()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SA_ANTISCANNING_EXIT(eSaStatus)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif      /* SA_TRACE_H */
/*==================[end of file]===========================================*/

