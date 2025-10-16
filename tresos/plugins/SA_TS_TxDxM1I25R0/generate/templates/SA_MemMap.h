/**
 * \file
 *
 * \brief AUTOSAR Demo_SA
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo_SA.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA deviation report:
 *  - This file violates MISRA-C:2004, Rule 19.6:
 *       "#undef shall not be used"
 *    Reason:
 *       The specification document explicitely describes this mechanism.
 *  - This file violates MISRA-C:2004, Rule 19.15:
 *       "Precautions shall be taken in order to prevent the contents
 *        of a header file being included twice."
 *    Reason:
 *       This file needs to be included more than once in a compilation unit
 */
/* CHECK: NOPARSE */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 3.4 (required)
 *   "All uses of the #pragma directive shall be documented and explained."
 *
 *   Reason:
 *   lib.
 *
 */
/* Deviation MISRA-1 <START> */
#if 0
/*------------------[Start of a module]--------------------------------------*/
#elif defined (SA_AM0001_START_SEC_VAR_INIT_16)
    #undef  SA_AM0001_START_SEC_VAR_INIT_16
    #undef  MEMMAP_ERROR
#elif defined (SA_AM0001_STOP_SEC_VAR_INIT_16)
    #undef  SA_AM0001_STOP_SEC_VAR_INIT_16
    #undef  MEMMAP_ERROR
#endif
