#if (!defined CPL_VERSION_H)
#define CPL_VERSION_H
/**
 * \file
 *
 * \brief AUTOSAR Cpl
 *
 * This file contains the implementation of the AUTOSAR
 * module Cpl.
 *
 * \version 1.3.3
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2020 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined CPL_VENDOR_ID)
#error CPL_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define CPL_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined CPL_MODULE_ID)
#error CPL_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define CPL_MODULE_ID         206U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined CPL_AR_RELEASE_MAJOR_VERSION)
#error CPL_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define CPL_AR_RELEASE_MAJOR_VERSION     4U

#if (defined CPL_AR_RELEASE_MINOR_VERSION)
#error CPL_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define CPL_AR_RELEASE_MINOR_VERSION     0U

#if (defined CPL_AR_RELEASE_REVISION_VERSION)
#error CPL_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define CPL_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined CPL_SW_MAJOR_VERSION)
#error CPL_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define CPL_SW_MAJOR_VERSION             1U

#if (defined CPL_SW_MINOR_VERSION)
#error CPL_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define CPL_SW_MINOR_VERSION             3U

#if (defined CPL_SW_PATCH_VERSION)
#error CPL_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define CPL_SW_PATCH_VERSION             3U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CPL_VERSION_H ) */
/*==================[end of file]============================================*/
