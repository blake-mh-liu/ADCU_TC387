

/**
 * \file
 *
 * \brief AUTOSAR ReProgMemM
 *
 * This file contains the implementation of the AUTOSAR
 * module ReProgMemM.
 *
 * \version 1.13.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef REPROGMEMM_TRACE_H
#define REPROGMEMM_TRACE_H


/*==================[inclusions]============================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETACTIVEBANK_ENTRY
/** \brief Entry point of function ReProgMemM_GetActiveBank()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_GETACTIVEBANK_ENTRY(UbActiveBank)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETACTIVEBANK_EXIT
/** \brief Exit point of function ReProgMemM_GetActiveBank()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_GETACTIVEBANK_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_ENTRY
/** \brief Entry point of function ReProgMemM_GetInactiveBankAddrOffset()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_EXIT
/** \brief Exit point of function ReProgMemM_GetInactiveBankAddrOffset()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_INIT_ENTRY
/** \brief Entry point of function ReProgMemM_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_INIT_EXIT
/** \brief Exit point of function ReProgMemM_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_MAINFUNCTION_ENTRY
/** \brief Entry point of function ReProgMemM_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_MAINFUNCTION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_MAINFUNCTION_EXIT
/** \brief Exit point of function ReProgMemM_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_MAINFUNCTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETJOBSTATUS_ENTRY
/** \brief Entry point of function ReProgMemM_GetJobStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_GETJOBSTATUS_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETJOBSTATUS_EXIT
/** \brief Exit point of function ReProgMemM_GetJobStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_GETJOBSTATUS_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_ERASE_ENTRY
/** \brief Entry point of function ReProgMemM_Erase()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_ERASE_ENTRY(ulAddress,ulLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_ERASE_EXIT
/** \brief Exit point of function ReProgMemM_Erase()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_ERASE_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_READ_ENTRY
/** \brief Entry point of function ReProgMemM_Read()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_READ_ENTRY(ulAddress,ulLength,pubDataPtr,ubBankType)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_READ_EXIT
/** \brief Exit point of function ReProgMemM_Read()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_READ_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_WRITE_ENTRY
/** \brief Entry point of function ReProgMemM_Write()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_WRITE_ENTRY(ulAddress,ulLength,pubDataPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_WRITE_EXIT
/** \brief Exit point of function ReProgMemM_Write()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_REPROGMEMM_WRITE_EXIT(RetVal)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function ReProgMemM_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_GETVERSIONINFO_ENTRY(versioninfo)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_REPROGMEMM_GETVERSIONINFO_EXIT
/** \brief Exit point of function ReProgMemM_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_REPROGMEMM_GETVERSIONINFO_EXIT()
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

#endif      /* REPROGMEMM_TRACE_H */

/*==================[end of file]===========================================*/

