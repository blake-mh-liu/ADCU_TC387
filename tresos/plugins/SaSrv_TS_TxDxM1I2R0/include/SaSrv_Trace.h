
/**
 * \file
 *
 * \brief AUTOSAR SaSrv
 *
 * This file contains the implementation of the AUTOSAR
 * module SaSrv.
 *
 * \version 1.2.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef SASRV_TRACE_H
#define SASRV_TRACE_H

/*==================[inclusions]============================================*/


#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include <SaSrv_DSD_Cfg.h>

/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_INIT_ENTRY
/** \brief Entry point of function SaSrv_DSD_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_INIT_EXIT
/** \brief Exit point of function SaSrv_DSD_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_INIT_ENTRY
/** \brief Entry point of function SaSrv_DSP_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_INIT_EXIT
/** \brief Exit point of function SaSrv_DSP_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_DEINIT_ENTRY
/** \brief Entry point of function SaSrv_DSD_DeInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_DEINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_DEINIT_EXIT
/** \brief Exit point of function SaSrv_DSD_DeInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_DEINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_DEINIT_ENTRY
/** \brief Entry point of function SaSrv_DSP_DeInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_DEINIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_DEINIT_EXIT
/** \brief Exit point of function SaSrv_DSP_DeInit()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_DEINIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_MAINFUNCTION_ENTRY
/** \brief Entry point of function SaSrv_DSP_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_MAINFUNCTION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_MAINFUNCTION_EXIT
/** \brief Exit point of function SaSrv_DSP_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_MAINFUNCTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_MAINFUNCTION_ENTRY
/** \brief Entry point of function SaSrv_DSD_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_MAINFUNCTION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_MAINFUNCTION_EXIT
/** \brief Exit point of function SaSrv_DSD_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_MAINFUNCTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_GETSEED_ENTRY
/** \brief Entry point of function SaSrv_DSD_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_GETSEED_ENTRY(OpStatus,Seed,ErrorCode,Level)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_GETSEED_EXIT
/** \brief Exit point of function SaSrv_DSD_GetSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSD_GETSEED_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_GETSEED_ENTRY
/** \brief Entry point of function SaSrv_DSP_GetSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_GETSEED_ENTRY(OpStatus,Seed,ErrorCode,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_GETSEED_EXIT
/** \brief Exit point of function SaSrv_DSP_GetSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_GETSEED_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_COMPAREKEY_ENTRY
/** \brief Entry point of function SaSrv_DSD_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_COMPAREKEY_ENTRY(Key,OpStatus,ErrorCode,Level)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_COMPAREKEY_EXIT
/** \brief Exit point of function SaSrv_DSD_CompareKey()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSD_COMPAREKEY_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_COMPAREKEY_ENTRY
/** \brief Entry point of function SaSrv_DSP_CompareKey()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_COMPAREKEY_ENTRY(Key,OpStatus,ErrorCode,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_COMPAREKEY_EXIT
/** \brief Exit point of function SaSrv_DSP_CompareKey()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_COMPAREKEY_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_ENTRY
/** \brief Entry point of function SaSrv_DSD_SetSecurityAttemptCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_ENTRY(OpStatus,AttemptCounter,Level)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_EXIT
/** \brief Exit point of function SaSrv_DSD_SetSecurityAttemptCounter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSD_SETSECURITYATTEMPTCOUNTER_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_ENTRY
/** \brief Entry point of function SaSrv_DSP_SetSecurityAttemptCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_ENTRY(OpStatus,AttemptCounter,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_EXIT
/** \brief Exit point of function SaSrv_DSP_SetSecurityAttemptCounter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_SETSECURITYATTEMPTCOUNTER_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_ENTRY
/** \brief Entry point of function SaSrv_DSD_GetSecurityAttemptCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_ENTRY(OpStatus,AttemptCounter,Level)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_EXIT
/** \brief Exit point of function SaSrv_DSD_GetSecurityAttemptCounter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSD_GETSECURITYATTEMPTCOUNTER_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_ENTRY
/** \brief Entry point of function SaSrv_DSP_GetSecurityAttemptCounter()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_ENTRY(OpStatus,AttemptCounter,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_EXIT
/** \brief Exit point of function SaSrv_DSP_GetSecurityAttemptCounter()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_GETSECURITYATTEMPTCOUNTER_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_COTS_MACGENERATESERVICE_ENTRY
/** \brief Entry point of function SaSrv_DSP_COTS_MACGenerateService()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_COTS_MACGENERATESERVICE_ENTRY(DataPtr,DataLength,MacPtr,MacLengthPtr,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_COTS_MACGENERATESERVICE_EXIT
/** \brief Exit point of function SaSrv_DSP_COTS_MACGenerateService()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_COTS_MACGENERATESERVICE_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_ENTRY
/** \brief Entry point of function SaSrv_DSP_NvMService_GetErrorStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_ENTRY(ResultPtr,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_EXIT
/** \brief Exit point of function SaSrv_DSP_NvMService_GetErrorStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_NVMSERVICE_GETERRORSTATUS_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_ENTRY
/** \brief Entry point of function SaSrv_DSP_NvMService_WriteBlock()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_ENTRY(DataPtr,CfgId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */
/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_EXIT
/** \brief Exit point of function SaSrv_DSP_NvMService_WriteBlock()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_SASRV_DSP_NVMSERVICE_WRITEBLOCK_EXIT(RetVal)
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

#endif /* SASRV_TRACE_H */
/*==================[end of file]===========================================*/

