/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CANTSYN_INT_H
#define CANTSYN_INT_H

/*==================[inclusions]============================================*/
#include <CanTSyn_Int_Cfg.h> /* Module Multi MainFunction declarations */

/* if DET is switched on, include Det.h*/
#if((CANTSYN_DEV_ERROR_DETECT == STD_ON) || (CANTSYN_DET_RUNTIME_CHECK == STD_ON))
/* include Det header for the DET calls. */
#include <Det.h>
#endif /* (CANTSYN_DEV_ERROR_DETECT == STD_ON) || (CANTSYN_DET_RUNTIME_CHECK == STD_ON) */
/*==================[macros]================================================*/

#if(CANTSYN_DEV_ERROR_DETECT == STD_ON)

#if (defined CANTSYN_DET_REPORT_ERROR)
#error CANTSYN_DET_REPORT_ERROR is already defined
#endif /* if (defined CANTSYN_DET_REPORT_ERROR) */

/** \brief Abstracts the Det_ReportError
**
** Det_ReportError is a service function and requires to have a return
** value which is always E_OK (see DET009). It is therefore o.k. to cast
** the value to void.
**
** \param[in] ApiId The ID of the calling function
** \param[in] ErrorId The error code reported by the calling function
**
*/
#define CANTSYN_DET_REPORT_ERROR(ApiId, ErrorId) \
  (void) Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId), (ErrorId))

#endif /* CANTSYN_DEV_ERROR_DETECT == STD_ON */

/* -----------------[defensive programming macros]------------------------ */




/*------------------------[Defensive programming]----------------------------*/

#if (defined CANTSYN_PRECONDITION_ASSERT)
#error CANTSYN_PRECONDITION_ASSERT is already defined
#endif

#if (defined CANTSYN_PRECONDITION_ASSERT_NO_EVAL)
#error CANTSYN_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (CANTSYN_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))
#else
#define CANTSYN_PRECONDITION_ASSERT(Condition, ApiId)
#define CANTSYN_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined CANTSYN_POSTCONDITION_ASSERT)
#error CANTSYN_POSTCONDITION_ASSERT is already defined
#endif

#if (defined CANTSYN_POSTCONDITION_ASSERT_NO_EVAL)
#error CANTSYN_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (CANTSYN_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))
#else
#define CANTSYN_POSTCONDITION_ASSERT(Condition, ApiId)
#define CANTSYN_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined CANTSYN_INVARIANT_ASSERT)
#error CANTSYN_INVARIANT_ASSERT is already defined
#endif

#if (defined CANTSYN_INVARIANT_ASSERT_NO_EVAL)
#error CANTSYN_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (CANTSYN_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define CANTSYN_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))
#else
#define CANTSYN_INVARIANT_ASSERT(Condition, ApiId)
#define CANTSYN_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined CANTSYN_STATIC_ASSERT)
# error CANTSYN_STATIC_ASSERT is already defined
#endif
#if (CANTSYN_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define CANTSYN_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define CANTSYN_STATIC_ASSERT(expr)
#endif

#if (defined CANTSYN_UNREACHABLE_CODE_ASSERT)
#error CANTSYN_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (CANTSYN_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **

 ** \param[in] ApiId Service ID of the API function */
#define CANTSYN_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID, (ApiId))
#else
#define CANTSYN_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined CANTSYN_INTERNAL_API_ID)
#error CANTSYN_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define CANTSYN_INTERNAL_API_ID DET_INTERNAL_API_ID



/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef CANTSYN_INT_H */
/*==================[end of file]============================================*/

