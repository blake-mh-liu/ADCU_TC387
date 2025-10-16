/**
 * \file
 *
 * \brief AUTOSAR E2E
 *
 * This file contains the implementation of the AUTOSAR
 * module E2E.
 *
 * \version 2.0.22
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 *  A project should not contain unused type declarations.
 *
 * Reason:
 * E2E_PCheckStatusType will be used by E2E_PXXMapStatusToSM in each profile.
 */

#ifndef E2E_H
#define E2E_H

/*==================[inclusions]=============================================*/

#include <Std_Types.h>          /* AUTOSAR standard types             */

/*==================[macros]=================================================*/

#if (defined E2E_EB_SOURCEID_MAXVALUE) /* to prevent double declaration */
#error E2E_EB_SOURCEID_MAXVALUE is already defined
#endif /* #if (defined E2E_EB_SOURCEID_MAXVALUE) */

/** \brief Maximum value for E2E for method SourceID */
#define E2E_EB_SOURCEID_MAXVALUE 0xFFFFFFFUL

/*------------------[E2E Error Classification]-------------------------------*/

#if (defined E2E_E_INPUTERR_NULL) /* to prevent double declaration */
#error E2E_E_INPUTERR_NULL is already defined
#endif

/** \brief At least one pointer parameter is a NULL pointer. */
#define E2E_E_INPUTERR_NULL 0x13U

#if (defined E2E_E_INPUTERR_WRONG) /* to prevent double declaration */
#error E2E_E_INPUTERR_WRONG is already defined
#endif

/** \brief At least one input parameter is erroneous (e.g. out of range) */
#define E2E_E_INPUTERR_WRONG 0x17U

#if (defined E2E_E_INTERR) /* to prevent double declaration */
#error E2E_E_INTERR is already defined
#endif

/**
 * \brief An internal library error has occurred.
 *
 * An internal library error has occurred. (e.g. error detected by program flow monitoring,
 * violated invariant or postcondition)
 */
#define E2E_E_INTERR 0x19U

#if (defined E2E_E_OK) /* to prevent double declaration */
#error E2E_E_OK is already defined
#endif

/** \brief Function completed successfully. */
#define E2E_E_OK 0U

#if (defined E2E_E_INVALID) /* to prevent double declaration */
#error E2E_E_INVALID is already defined
#endif

/** \brief Invalid value passed to function. */
#define E2E_E_INVALID 0xFFU

#if (defined E2E_E_WRONGSTATE) /* to prevent double declaration */
#error E2E_E_WRONGSTATE is already defined
#endif

/** \brief Function executed in wrong state. */
#define E2E_E_WRONGSTATE 0x1AU

#if (defined E2E_P_OK) /* to prevent double declaration */
#error E2E_P_OK is already defined
#endif

/**
 * \brief The checks of the Data in this cycle were successful (including counter check).
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_OK 0x00U

#if (defined E2E_P_REPEATED) /* to prevent double declaration */
#error E2E_P_REPEATED is already defined
#endif

/**
 * \brief Either no new data is available, or the new data has a repeated counter.
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_REPEATED 0x01U

#if (defined E2E_P_WRONGSEQUENCE) /* to prevent double declaration */
#error E2E_P_WRONGSEQUENCE is already defined
#endif

/**
 * \brief The checks of the Data in this cycle were successful, with the exception of
 *        counter jump, which changed more than allowed delta.
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_WRONGSEQUENCE 0x02U

#if (defined E2E_P_ERROR) /* to prevent double declaration */
#error E2E_P_ERROR is already defined
#endif

/**
 * \brief Error not related to counters occurred (e.g. wrong crc, wrong length, wrong DataID)
 *        or the return of the check function was not OK.
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_ERROR 0x03U

#if (defined E2E_P_NOTAVAILABLE) /* to prevent double declaration */
#error E2E_P_NOTAVAILABLE is already defined
#endif

/**
 * \brief No value has been received yet. This is used as the initialization value
 *        for the buffer, it is not returned by any E2E profile.
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_NOTAVAILABLE 0x04U

#if (defined E2E_P_NONEWDATA) /* to prevent double declaration */
#error E2E_P_NONEWDATA is already defined
#endif

/**
 * \brief No new Data is available since the last call of the check function.
 *
 * Note: related to E2E_PCheckStatusType
 */
#define E2E_P_NONEWDATA 0x05U

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined E2E_VENDOR_ID) /* to prevent double declaration */
#error E2E_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define E2E_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined E2E_MODULE_ID) /* to prevent double declaration */
#error E2E_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define E2E_MODULE_ID         207U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined E2E_AR_RELEASE_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define E2E_AR_RELEASE_MAJOR_VERSION  4U

#if (defined E2E_AR_RELEASE_MINOR_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define E2E_AR_RELEASE_MINOR_VERSION  2U

#if (defined E2E_AR_RELEASE_REVISION_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define E2E_AR_RELEASE_REVISION_VERSION  1U

/*------------------[AUTOSAR specification version identification]----------*/

#if (defined E2E_AR_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_AR_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR specification major version */
#define E2E_AR_MAJOR_VERSION  4U

#if (defined E2E_AR_MINOR_VERSION) /* to prevent double declaration */
#error E2E_AR_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR specification minor version */
#define E2E_AR_MINOR_VERSION  2U

#if (defined E2E_AR_PATCH_VERSION) /* to prevent double declaration */
#error E2E_AR_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR specification patch version */
#define E2E_AR_PATCH_VERSION  1U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined E2E_SW_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define E2E_SW_MAJOR_VERSION  2U

#if (defined E2E_SW_MINOR_VERSION) /* to prevent double declaration */
#error E2E_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define E2E_SW_MINOR_VERSION  0U

#if (defined E2E_SW_PATCH_VERSION) /* to prevent double declaration */
#error E2E_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define E2E_SW_PATCH_VERSION  22U


/*==================[type definitions]=======================================*/

/**
 * \brief Status type for E2E State Machine return values.
 */
 /* Deviation MISRAC2012-1 */
typedef uint8 E2E_PCheckStatusType;


/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/


#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>

/** \brief Return the modules version information
 *
 * This service returns the version information of this module. The version
 * information includes:
 * - Module Id
 * - Vendor Id
 * - Vendor specific version numbers
 *
 * \param[out] VersionInfo Pointer where to store the version information of this module
 *
 * \ServiceID{0x14}
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
);

/**
 * \brief Checks the method specific input information using the E2E Profiles for method.
 *
 * Checks SourceID, MessageType and MessageResult for using the E2E Profiles for method.
 *
 * \param[in]     SourceID       A system-unique identifier of the Data Source.
 * \param[in]     MessageType    Type of the message (request/response).
 * \param[in]     MessageResult  Result of the message (OK/ERROR).
 *
 * \return Function execution success status
 * \retval E2E_E_INPUTERR_WRONG At least one input parameter is erroneous.
 * \retval E2E_E_OK Function completed successfully.
 */
extern FUNC(Std_ReturnType, E2E_CODE) E2E_EB_MethodCheck
(
   uint32 SourceID,
   Std_MessageTypeType MessageType,
   Std_MessageResultType MessageResult
);

/**
 * \brief Checks the method specific message input information using the E2E Profiles for method.
 *
 * Checks MessageType and MessageResult for using the E2E Profiles for method.
 *
 * \param[in]     MessageType    Type of the message (request/response).
 * \param[in]     MessageResult  Result of the message (OK/ERROR).
 *
 * \return Function execution success status
 * \retval E2E_E_INPUTERR_WRONG At least one input parameter is erroneous.
 * \retval E2E_E_OK Function completed successfully.
 */
extern FUNC(Std_ReturnType, E2E_CODE) E2E_EB_MethodMessageCheck
(
  Std_MessageTypeType MessageType,
  Std_MessageResultType MessageResult
);

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>

#endif /* ifndef E2E_H */
/*==================[end of file]============================================*/
