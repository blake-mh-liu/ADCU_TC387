/**
 * \file
 *
 * \brief AUTOSAR ApplTemplates
 *
 * This file contains the implementation of the AUTOSAR
 * module ApplTemplates.
 *
 * \version 6.8.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
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

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[Autosar vendor identification]--------------------------*/

#if (!defined MEM_VENDOR_ID)
/** \brief Autosar module vendor identification
 **
 ** Vendor ID of the dedicated implementation of this module according
 ** to the AUTOSAR vendor list. */
#define MEM_VENDOR_ID 1U /* Elektrobit Automotive GmbH */
#endif

/*------------------[AUTOSAR release version identification]-----------------*/

#if (!defined MEM_AR_RELEASE_MAJOR_VERSION)
/** \brief definition of the AUTOSAR release major version of the specification */
#define MEM_AR_RELEASE_MAJOR_VERSION 1U
#endif

#if (!defined MEM_AR_RELEASE_MINOR_VERSION)
/** \brief definition of a AUTOSAR release minor version of the specification */
#define MEM_AR_RELEASE_MINOR_VERSION 1U
#endif

#if (!defined MEM_AR_RELEASE_PATCH_VERSION)
/** \brief definition of a AUTOSAR release patch version of the specification */
#define MEM_AR_RELEASE_PATCH_VERSION 0U
#endif

/*------------------[Autosar software version]-------------------------------*/

#if (!defined MEM_SW_MAJOR_VERSION)
/** \brief definition of the major version of this implementation */
#define MEM_SW_MAJOR_VERSION 1U
#endif

#if (!defined MEM_SW_MINOR_VERSION)
/** \brief definition of a minor version of this implementation */
#define MEM_SW_MINOR_VERSION 1U
#endif

#if (!defined MEM_SW_PATCH_VERSION)
/** \brief definition of a patch version of this implementation */
#define MEM_SW_PATCH_VERSION 0U
#endif

/*------------------[MemMap error checking]----------------------------------*/

#if 0 /* to be able to use #elif for every module */


/*------------------[Start of a module]--------------------------------------*/
/* following macors are needed for BasicTemplate application code            */

#elif (defined MCU_START_SEC_APPL_CODE || defined MCU_START_SEC_CALLOUT_CODE)
  #undef MCU_START_SEC_APPL_CODE
  #undef MCU_START_SEC_CALLOUT_CODE
  #undef MEMMAP_ERROR

#elif (defined MCU_STOP_SEC_APPL_CODE || defined MCU_STOP_SEC_CALLOUT_CODE)
  #undef MCU_STOP_SEC_APPL_CODE
  #undef MCU_STOP_SEC_CALLOUT_CODE
  #undef MEMMAP_ERROR
  
#elif (defined IRQ_START_SEC_CODE_QM_GLOBAL)
  #undef IRQ_START_SEC_CODE_QM_GLOBAL
  #undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CODE_QM_GLOBAL)
  #undef IRQ_STOP_SEC_CODE_QM_GLOBAL
  #undef MEMMAP_ERROR 

#elif (defined IRQ_START_SEC_CODE)
  #undef IRQ_START_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CODE)
  #undef IRQ_STOP_SEC_CODE
  #undef MEMMAP_ERROR    
/*------------------[Start of a module]--------------------------------------*/
/* TC2XX specific
*/
#elif (defined MCAL_START_SEC_CODE)
   #pragma section code "rom_code_testing"
   #undef MCAL_TCLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif (defined MCAL_STOP_SEC_CODE)
   #pragma section code restore
   #undef MCAL_TCLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_CODE)
   #pragma section code "rom_code_testing"
   #undef MCAL_TCLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif (defined MCAL_TCLIB_STOP_SEC_CODE)
   #pragma section code restore
   #undef MCAL_TCLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_VAR_32BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_TCLIB_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_TCLIB_STOP_SEC_VAR_32BIT)
   #pragma section fardata restore
   #undef MCAL_TCLIB_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_VAR_INIT_32BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_TCLIB_START_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT)
   #pragma section fardata restore
   #undef MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_CONST_32BIT)
   #pragma section farrom "rom_const_testing"
   #undef MCAL_TCLIB_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_TCLIB_STOP_SEC_CONST_32BIT)
   #pragma section farrom restore
   #undef MCAL_TCLIB_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_VAR_8BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_TCLIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_TCLIB_STOP_SEC_VAR_8BIT)
   #pragma section fardata restore
   #undef MCAL_TCLIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_CODE)
   #pragma section code "rom_code_testing"
   #undef MCAL_WDGLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif (defined MCAL_WDGLIB_STOP_SEC_CODE)
   #pragma section code restore
   #undef MCAL_WDGLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_VAR_32BIT)
   #pragma section farbss "ram_testing"
   #undef MCAL_WDGLIB_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_WDGLIB_STOP_SEC_VAR_32BIT)
   #pragma section farbss restore
   #undef MCAL_WDGLIB_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT)
   #pragma section fardata restore
   #undef MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_VAR_8BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_WDGLIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_WDGLIB_STOP_SEC_VAR_8BIT)
   #pragma section fardata restore
   #undef MCAL_WDGLIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_CONST_32BIT)
   #pragma section farrom "rom_const_testing"
   #undef MCAL_WDGLIB_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_WDGLIB_STOP_SEC_CONST_32BIT)
   #pragma section farrom restore
   #undef MCAL_WDGLIB_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_DMALIB_START_SEC_CODE)
   #pragma section code "rom_code_testing"
   #undef MCAL_DMALIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif (defined MCAL_DMALIB_STOP_SEC_CODE)
   #pragma section code restore
   #undef MCAL_DMALIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif (defined MCAL_DMALIB_START_SEC_VAR_32BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_DMALIB_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_DMALIB_STOP_SEC_VAR_32BIT)
   #pragma section fardata restore
   #undef MCAL_DMALIB_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

#elif (defined MCAL_DMALIB_START_SEC_VAR_8BIT)
   #pragma section fardata "raminit_testing"
   #undef MCAL_DMALIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif (defined MCAL_DMALIB_STOP_SEC_VAR_8BIT)
   #pragma section fardata restore
   #undef MCAL_DMALIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

/*------------------[Start of a module]--------------------------------------*/
/* TC3XX specific
*/
#elif (defined MCALLIB_START_SEC_CODE_QM_GLOBAL)
  #undef MCALLIB_START_SEC_CODE_QM_GLOBAL 
  #undef MEMMAP_ERROR
#elif (defined MCALLIB_SEC_STOP_CODE_QM_GLOBAL)
  #undef MCALLIB_STOP_SEC_CODE_QM_GLOBAL
  #undef MEMMAP_ERROR

#elif (defined MCALLIB_START_SEC_CONST_QM_8)
  #undef MCALLIB_START_SEC_CONST_QM_8
  #undef MEMMAP_ERROR
#elif (defined MCALLIB_STOP_SEC_CONST_QM_8)
  #undef MCALLIB_STOP_SEC_CONST_QM_8
  #undef MEMMAP_ERROR  

#elif (defined MCALLIB_START_SEC_CONST_QM_UNSPECIFIED)
  #undef MCALLIB_START_SEC_CONST_QM_UNSPECIFIED
  #undef MEMMAP_ERROR
#elif (defined MCALLIB_STOP_SEC_CONST_QM_UNSPECIFIED)
  #undef MCALLIB_STOP_SEC_CONST_QM_UNSPECIFIED
  #undef MEMMAP_ERROR   

#elif (defined MCALLIB_START_SEC_VAR_CLEARED_QM_LOCAL_32)
  #undef MCALLIB_START_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef MEMMAP_ERROR
#elif (defined MCALLIB_STOP_SEC_VAR_CLEARED_QM_LOCAL_32)
  #undef MCALLIB_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef MEMMAP_ERROR   

#elif (defined MCALLIB_START_SEC_VAR_INIT_QM_LOCAL_32)
  #undef MCALLIB_START_SEC_VAR_INIT_QM_LOCAL_32
  #undef MEMMAP_ERROR
#elif (defined MCALLIB_STOP_SEC_VAR_INIT_QM_LOCAL_32)
  #undef MCALLIB_STOP_SEC_VAR_INIT_QM_LOCAL_32
  #undef MEMMAP_ERROR 

#endif

/*------------------[MemMap error checking]----------------------------------*/

/*==================[end of file]============================================*/

