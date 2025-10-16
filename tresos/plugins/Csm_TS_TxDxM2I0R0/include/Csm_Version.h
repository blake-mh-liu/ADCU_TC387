/* !LINKSTO CSM001_PI, 1
 */
#if (!defined CSM_VERSION_H)
#define CSM_VERSION_H
/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined CSM_VENDOR_ID)
#error CSM_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define CSM_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined CSM_MODULE_ID)
#error CSM_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define CSM_MODULE_ID         110U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined CSM_AR_RELEASE_MAJOR_VERSION)
#error CSM_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define CSM_AR_RELEASE_MAJOR_VERSION     4U

#if (defined CSM_AR_RELEASE_MINOR_VERSION)
#error CSM_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define CSM_AR_RELEASE_MINOR_VERSION     0U

#if (defined CSM_AR_RELEASE_REVISION_VERSION)
#error CSM_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define CSM_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined CSM_SW_MAJOR_VERSION)
#error CSM_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define CSM_SW_MAJOR_VERSION             2U

#if (defined CSM_SW_MINOR_VERSION)
#error CSM_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define CSM_SW_MINOR_VERSION             0U

#if (defined CSM_SW_PATCH_VERSION)
#error CSM_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define CSM_SW_PATCH_VERSION             9U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CSM_VERSION_H ) */
/*==================[end of file]============================================*/

