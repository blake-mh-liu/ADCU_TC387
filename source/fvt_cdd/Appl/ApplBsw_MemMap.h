/*********************************************************************************************************************
* FILENAME    | ApplBsw_MemMap_Template.h
*-------------+-------------------------------------------------------------------------------------------------------
* PROJECT     | GEELY BMS project 
*-------------+-------------------------------------------------------------------------------------------------------
* DESCRIPTION | this file for generate memory map file for GEELY BMS project 
*             | how to layout data into memory map
*-------------+-------------------------------------------------------------------------------------------------------
* USAGE       | #define BSW_START_SEC_VAR_QM_CONST
*             | #include "ApplBsw_MemMap.h"
*             |   const unit16 g_u16Data = 0;
*             | #define BSW_STOP_SEC_VAR_QM_CONST
*             | #include "ApplBsw_MemMap.h"
*-------------+-------------------------------------------------------------------------------------------------------
* NOTES       | 
*-------------+-------------------------------------------------------------------------------------------------------
* COPYRIGHT   | Copyright (c)  Automotive Technology (Zhejiang) Co. Ltd. 2019.
*             | All rights reserved.
*-------------+-------------------------------------------------------------------------------------------------------
* AUTHORS     | Name                  | Init | Company
*             |-----------------------+------+------------------------------------------------------------------------
*             | Hu Hongli             | Hlhu |  Automotive Technology (Zhejiang) Co. Ltd
*             |                       |      |
*-------------+-----------------------+-------------------------------------------------------------------------------
* REVISIONS   | Version  | yyyy-mm-dd | Init |  Ref  | Description
*             |----------+------------+------+-------+----------------------------------------------------------------
*             | 00.01.00 | 2019-11-23 | huhl |   -   | Initial version
*             |          |            |      |       | 
*====================================================================================================================*/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#define MEMMAP_ERROR
/**********************************************************************************************************************
 * CDD MemMap for code section 
 *********************************************************************************************************************/
#ifdef BSW_START_SEC_APP_HEADER_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_APP_HEADER_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "APP_HEADER" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "APP_HEADER" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_APP_HEADER_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_APP_HEADER_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_APP_HEADER_CONST_UNSPECIFIED_OPEN
#error Section BSW_START_SEC_APP_HEADER_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_APP_HEADER_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_APP_HEADER_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef BSW_START_SEC_CPU0QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU0QM_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU0QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_CODE_OPEN
#error Section BSW_CPU0QM_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU0QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU1QM_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU1QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_CODE_OPEN
#error Section BSW_CPU1QM_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU1QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU2QM_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU2QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_CODE_OPEN
#error Section BSW_CPU2QM_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU2QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU3QM_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU3QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_CODE_OPEN
#error Section BSW_CPU3QM_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU3QM_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU0ASIL_CODE"  /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU0ASIL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_CODE_OPEN
#error Section BSW_CPU0ASIL_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU0ASIL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_CODE_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code "BSW_CPU1ASIL_CODE"  /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_START_SEC_CPU1ASIL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_CODE_OPEN
#error Section BSW_CPU1ASIL_CODE is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
#undef BSW_STOP_SEC_CPU1ASIL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU0QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU0QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU0QM_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU1QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU1QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU1QM_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU2QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU2QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU2QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU2QM_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU2QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU3QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU3QM_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU3QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU3QM_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU3QM_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU0ASIL_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU0ASIL_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0ASIL_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CPU1ASIL_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CPU1ASIL_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1ASIL_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_CONST_UNSPECIFIED_OPEN
#error Section BSW_CPU1ASIL_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1ASIL_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CALDATA_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma protect on
#pragma section farrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CALDATA_CONST_UNSPECIFIED_OPEN
#error Section BSW_CALDATA_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CALDATA_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma protect off
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_VBOB_CALDATA_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_VBOB_CALDATA_CONST_UNSPECIFIED_OPEN
#error Section BSW_VBOB_CALDATA_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_VBOB_CALDATA_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CALDATA_VBOB_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "BSW_CALDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CALDATA_VBOB_CONST_UNSPECIFIED_OPEN
#error Section BSW_CALDATA_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CALDATA_VBOB_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_VBOB_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_VBOB_CRC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CALDATA_VBOB_CRC_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "VBOB_CRCDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "VBOB_CRCDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_VBOB_CRC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_VBOB_CRC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CALDATA_VBOB_CRC_CONST_UNSPECIFIED_OPEN
#error Section BSW_CALDATA_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CALDATA_VBOB_CRC_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_VBOB_CRC_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_VBOB_VER_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CALDATA_VBOB_VER_CONST_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom "VBOB_VERDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom "VBOB_VERDATA_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_VBOB_VER_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_VBOB_VER_CALDATA_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CALDATA_VBOB_VER_CONST_UNSPECIFIED_OPEN
#error Section BSW_CALDATA_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CALDATA_VBOB_VER_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_VBOB_VER_CALDATA_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef BSW_START_SEC_CPU0ASIL_SHARE_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_SHARE_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_LMU0_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_CPU0ASIL_SHARE_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_SHARE_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_SHARE_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_SHARE_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_SHARE_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_LMU0_NONE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_NONE_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_SHARE_NONE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef BSW_START_SEC_CPU0QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU0QM_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU1QM_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU2QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU2QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU2QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU2QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU2QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU2QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU2QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU2QM_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU2QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU3QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU3QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU3QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU3QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU3QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU3QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU3QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU3QM_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU3QM_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0ASIL_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0ASIL_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0ASIL_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1ASIL_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1ASIL_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1ASIL_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_VAR_UNSPECIFIED_OPEN
#error Section BSW_CPU1ASIL_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1ASIL_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_GLBDATA_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_GLBDATA_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_GLBDATA_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_GLBDATA_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_GLBDATA_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_GLBDATA_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_GLBDATA_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_GLBDATA_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_GLBDATA_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_GLBDATA_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_GLBDATA_VAR_UNSPECIFIED_OPEN
#error Section BSW_GLBDATA_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_GLBDATA_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_GLBDATA_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_GLBDATA_SAVE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_GLBDATA_VAR_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_GLBDATA_SAVE_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_GLBDATA_SAVE_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_GLBDATA_SAVE_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_GLBDATA_SAVE_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_GLBDATA_SAVE_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_GLBDATA_SAVE_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_GLBDATA_SAVE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_GLBDATA_SAVE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_GLBDATA_VAR_UNSPECIFIED_OPEN
#error Section BSW_GLBDATA_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_GLBDATA_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_GLBDATA_SAVE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU0QM_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU1QM_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU2QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU2QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU2QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU2QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU2QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU2QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU2QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU2QM_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU2QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU3QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU3QM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU3QM_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU3QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU3QM_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU3QM_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU3QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU3QM_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU3QM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0ASIL_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0ASIL_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1ASIL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1ASIL_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1ASIL_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1ASIL_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU1ASIL_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1ASIL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_GLBDATA_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_GLBDATA_VAR_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_GLBDATA_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_GLBDATA_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_GLBDATA_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_GLBDATA_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_GLBDATA_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_GLBDATA_VAR_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_GLBDATA_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_GLBDATA_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_GLBDATA_VAR_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_GLBDATA_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_GLBDATA_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_GLBDATA_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0QM_VAR_NOCACHE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0QM_VAR_NOCACHE_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0QM_VAR_NOCACHE_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0QM_VAR_NOCACHE_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU0QM_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1QM_VAR_NOCACHE_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1QM_VAR_NOCACHE_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1QM_VAR_NOCACHE_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1QM_VAR_NOCACHE_FAST_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU1QM_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU2QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU2QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU2QM_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU2QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU3QM_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU3QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU3QM_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU3QM_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1ASIL_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1ASIL_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_GLBDATA_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_GLBDATA_VAR_NOCACHE_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_GLBDATA_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_GLBDATA_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_GLBDATA_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_GLBDATA_VAR_NOCACHE_UNSPECIFIED_OPEN
#error Section BSW_GLBDATA_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_GLBDATA_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_GLBDATA_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU2QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU2QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU3QM_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU3QM_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU0ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU0ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_CPU1ASIL_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

#undef BSW_START_SEC_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_CPU1ASIL_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_START_SEC_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifdef BSW_MEMMAP_SECTION_OPEN
#error A MemMap section is already open. Nesting is not supported.
#endif
#define BSW_MEMMAP_SECTION_OPEN
#define BSW_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#ifndef MEMMAP_ERROR
#error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
#endif
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata "BSW_GLBDATA_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_START_SEC_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef BSW_STOP_SEC_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
#ifndef BSW_MEMMAP_SECTION_OPEN
#error No MemMap section is currently opened.
#endif
#undef BSW_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#ifndef BSW_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#error Section BSW_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
#endif
#undef BSW_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
#undef BSW_STOP_SEC_GLBDATA_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

