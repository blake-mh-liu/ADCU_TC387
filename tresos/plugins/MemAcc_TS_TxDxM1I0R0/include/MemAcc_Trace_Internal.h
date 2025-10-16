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
#ifndef MEMACC_TRACE_INTERNAL_H
#define MEMACC_TRACE_INTERNAL_H
/*==================[inclusions]============================================*/

/*==================[macros]================================================*/
/* Place internal debug instrumentation macros in this file, i.e. all
   macros that are not generated for the public api instrumentation.
*/

#ifndef DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_ENTRY
/** \brief Entry point of function MemAcc_ValidateGetMemoryInfoParams() */
#define DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_ENTRY(a,b,c)
#endif

#ifndef DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_EXIT
/** \brief Exit point of function MemAcc_ValidateGetMemoryInfoParams() */
#define DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_EXIT(a,b,c,d)
#endif
#ifndef DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_ENTRY
/** \brief Entry point of function MemAcc_ValidateGetJobInfoParams() */
#define DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_ENTRY(a,b)
#endif

#ifndef DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_EXIT
/** \brief Exit point of function MemAcc_ValidateGetJobInfoParams() */
#define DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_EXIT(a,b,c)
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

#endif /* ifndef MEMACC_TRACE_INTERNAL_H */
/*==================[end of file]===========================================*/
