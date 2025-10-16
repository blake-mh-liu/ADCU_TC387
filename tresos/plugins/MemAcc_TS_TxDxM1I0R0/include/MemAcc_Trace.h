/**
 * \file
 *
 * \brief AUTOSAR MemAcc
 *
 * This file contains the implementation of the AUTOSAR
 * module MemAcc.
 *
 * \version 1.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef MEMACC_TRACE_H
#define MEMACC_TRACE_H
/*==================[inclusions]============================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include <MemAcc_Trace_Internal.h>

/*==================[macros]================================================*/

#ifndef DBG_MEMACC_GETJOBINFO_ENTRY
/** \brief Entry point of function MemAcc_GetJobInfo() */
#define DBG_MEMACC_GETJOBINFO_ENTRY(a, b)
#endif

#ifndef DBG_MEMACC_GETJOBINFO_EXIT
/** \brief Exit point of function MemAcc_GetJobInfo() */
#define DBG_MEMACC_GETJOBINFO_EXIT(a,b)
#endif

#ifndef DBG_MEMACC_GETPROCESSEDLENGTH_ENTRY
/** \brief Entry point of function MemAcc_GetProcessedLength() */
#define DBG_MEMACC_GETPROCESSEDLENGTH_ENTRY(a)
#endif

#ifndef DBG_MEMACC_GETPROCESSEDLENGTH_EXIT
/** \brief Exit point of function MemAcc_GetProcessedLength() */
#define DBG_MEMACC_GETPROCESSEDLENGTH_EXIT(a, b)
#endif

#ifndef DBG_MEMACC_INIT_ENTRY
/** \brief Entry point of function MEMACC_Init() */
#define DBG_MEMACC_INIT_ENTRY()
#endif

#ifndef DBG_MEMACC_INIT_EXIT
/** \brief Exit point of function MEMACC_Init() */
#define DBG_MEMACC_INIT_EXIT()
#endif

#ifndef DBG_MEMACC_MAINFUNCTION_ENTRY
/** \brief Entry point of function MEMACC_MainFunction() */
#define DBG_MEMACC_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_MEMACC_MAINFUNCTION_EXIT
/** \brief Exit point of function MEMACC_MainFunction() */
#define DBG_MEMACC_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_MEMACC_GETVERSIONINFO_ENTRY
/** \brief Entry point of function MEMACC_GetVersionInfo() */
#define DBG_MEMACC_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_MEMACC_GETVERSIONINFO_EXIT
/** \brief Exit point of function MEMACC_GetVersionInfo() */
#define DBG_MEMACC_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_MEMACC_GETMEMORYINFO_ENTRY
/** \brief Entry point of function MemAcc_GetMemoryInfo() */
#define DBG_MEMACC_GETMEMORYINFO_ENTRY(a, b, c)
#endif

#ifndef DBG_MEMACC_GETMEMORYINFO_EXIT
/** \brief Exit point of function MemAcc_GetMemoryInfo() */
#define DBG_MEMACC_GETMEMORYINFO_EXIT(a, b, c, d)
#endif

#ifndef DBG_MEMACC_GETJOBRESULT_ENTRY
/** \brief Entry point of function MemAcc_GetJobResult() */
#define DBG_MEMACC_GETJOBRESULT_ENTRY(a)
#endif

#ifndef DBG_MEMACC_GETJOBRESULT_EXIT
/** \brief Exit point of function MemAcc_GetJobResult() */
#define DBG_MEMACC_GETJOBRESULT_EXIT(a,b)
#endif

#ifndef DBG_MEMACC_GETJOBSTATUS_ENTRY
/** \brief Entry point of function MemAcc_GetJobStatus() */
#define DBG_MEMACC_GETJOBSTATUS_ENTRY(a)
#endif

#ifndef DBG_MEMACC_GETJOBSTATUS_EXIT
/** \brief Exit point of function MemAcc_GetJobStatus() */
#define DBG_MEMACC_GETJOBSTATUS_EXIT(a,b)
#endif

#ifndef DBG_MEMACC_BLANKCHECK_ENTRY
/** \brief Entry point of function MemAcc_BlankCheck() */
#define DBG_MEMACC_BLANKCHECK_ENTRY(a, b, c)
#endif

#ifndef DBG_MEMACC_BLANKCHECK_EXIT
/** \brief Exit point of function MemAcc_BlankCheck() */
#define DBG_MEMACC_BLANKCHECK_EXIT(a,b,c,d)
#endif

#ifndef DBG_MEMACC_READ_ENTRY
/** \brief Entry point of function MemAcc_Read() */
#define DBG_MEMACC_READ_ENTRY(a, b, c, d)
#endif

#ifndef DBG_MEMACC_READ_EXIT
/** \brief Exit point of function MemAcc_Read() */
#define DBG_MEMACC_READ_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_MEMACC_WRITE_ENTRY
/** \brief Entry point of function MemAcc_Write() */
#define DBG_MEMACC_WRITE_ENTRY(a, b, c, d)
#endif

#ifndef DBG_MEMACC_WRITE_EXIT
/** \brief Exit point of function MemAcc_Write() */
#define DBG_MEMACC_WRITE_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_MEMACC_ERASE_ENTRY
/** \brief Entry point of function MemAcc_Erase() */
#define DBG_MEMACC_ERASE_ENTRY(a, b, c)
#endif

#ifndef DBG_MEMACC_ERASE_EXIT
/** \brief Exit point of function MemAcc_Erase() */
#define DBG_MEMACC_ERASE_EXIT(a, b, c, d)
#endif

#ifndef DBG_MEMACC_COMPARE_ENTRY
/** \brief Entry point of function MemAcc_Compare() */
#define DBG_MEMACC_COMPARE_ENTRY(a, b, c, d)
#endif

#ifndef DBG_MEMACC_COMPARE_EXIT
/** \brief Exit point of function MemAcc_Compare() */
#define DBG_MEMACC_COMPARE_EXIT(a,b,c,d, e)
#endif

#ifndef DBG_MEMACC_CANCEL_ENTRY
/** \brief Entry point of function MemAcc_Cancel() */
#define DBG_MEMACC_CANCEL_ENTRY(a)
#endif

#ifndef DBG_MEMACC_CANCEL_EXIT
/** \brief Exit point of function MemAcc_Cancel() */
#define DBG_MEMACC_CANCEL_EXIT(a)
#endif

#ifndef DBG_MEMACC_REQUESTLOCK_ENTRY
/** \brief Entry point of function MemAcc_RequestLock() */
#define DBG_MEMACC_REQUESTLOCK_ENTRY(a, b, c, d)
#endif

#ifndef DBG_MEMACC_REQUESTLOCK_EXIT
/** \brief Exit point of function MemAcc_RequestLock() */
#define DBG_MEMACC_REQUESTLOCK_EXIT(a,b,c,d, e)
#endif

#ifndef DBG_MEMACC_RELEASELOCK_ENTRY
/** \brief Entry point of function MemAcc_ReleaseLock() */
#define DBG_MEMACC_RELEASELOCK_ENTRY(a, b, c)
#endif

#ifndef DBG_MEMACC_RELEASELOCK_EXIT
/** \brief Exit point of function MemAcc_ReleaseLock() */
#define DBG_MEMACC_RELEASELOCK_EXIT(a,b,c,d)
#endif
/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef MEMACC_TRACE_H */
/*==================[end of file]===========================================*/
