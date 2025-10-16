/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \version 5.3.55
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 5.5 (required)
 *  Identifiers shall be distinct from macro names.
 *
 *  Reason:
 *  The rule requires that an identifier used as an external identifier shall
 *  not be used for any other purpose in any name space or translation unit,
 *  even if it denotes an object with no linkage. Here, a pre-compile macro
 *  excludes its usage as an external identifier when defined as a macro.
 *
 *  MISRAC2012-2) Deviated Rule: 5.8 (required)
 *  Identifiers that define objects or functions with external linkage shall
 *  be unique.
 *
 *  Reason:
 *  The rule requires that an identifier used as an external identifier shall
 *  not be used for any other purpose in any name space or translation unit,
 *  even if it denotes an object with no linkage. Here, a pre-compile macro
 *  excludes its usage as an external identifier when defined as a macro.
 */


/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Version.h>         /* Version info */
#include <PduR_Api_Depend.h>      /* PDU Router API functions (PduR_GConfigPtr) */

#if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF)
/*==================[macros]================================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef PDUR_VENDOR_ID /* configuration check */
#error PDUR_VENDOR_ID must be defined
#endif

#if (PDUR_VENDOR_ID != 1U) /* vendor check */
#error PDUR_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef PDUR_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error PDUR_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (PDUR_AR_RELEASE_MAJOR_VERSION != 4U)
#error PDUR_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef PDUR_AR_RELEASE_MINOR_VERSION /* configuration check */
#error PDUR_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (PDUR_AR_RELEASE_MINOR_VERSION != 0U )
#error PDUR_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#ifndef PDUR_AR_RELEASE_REVISION_VERSION /* configuration check */
#error PDUR_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (PDUR_AR_RELEASE_REVISION_VERSION != 3U )
#error PDUR_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef PDUR_SW_MAJOR_VERSION /* configuration check */
#error PDUR_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (PDUR_SW_MAJOR_VERSION != 5U)
#error PDUR_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#ifndef PDUR_SW_MINOR_VERSION /* configuration check */
#error PDUR_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (PDUR_SW_MINOR_VERSION < 3U)
#error PDUR_SW_MINOR_VERSION wrong (< 3U)
#endif

#ifndef PDUR_SW_PATCH_VERSION /* configuration check */
#error PDUR_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (PDUR_SW_PATCH_VERSION < 55U)
#error PDUR_SW_PATCH_VERSION wrong (< 55U)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/



/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/* AUTOSAR Memory Mapping - start section for code */
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include <PduR_MemMap.h>

VAR(PduR_StateType, PDUR_VAR) PduR_State = PDUR_UNINIT;

/* AUTOSAR Memory Mapping - end section for code */
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <PduR_MemMap.h>

/*
 * if not a constant configuration address is used - define pointer variable
 */
#if (PDUR_CONST_CFG_ADDRESS_ENABLE == STD_OFF)


#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <PduR_MemMap.h>

/**
 * \brief global variable for the pointer to the config of PduR
 */
/* Deviation MISRAC2012-1, MISRAC2012-2 */
P2CONST(PduR_PBConfigType, PDUR_VAR_CLEARED, PDUR_APPL_CONST) PduR_GConfigPtr;


#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <PduR_MemMap.h>

#endif /* PDUR_CONST_CFG_ADDRESS_ENABLE == STD_OFF */

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#else /* if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_PduRType;


#endif /* if (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF) */
/*==================[end of file]===========================================*/
