/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined CAL_VERSION_H)
#define CAL_VERSION_H

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined CAL_VENDOR_ID)
#error CAL_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define CAL_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined CAL_MODULE_ID)
#error CAL_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define CAL_MODULE_ID         206U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined CAL_AR_RELEASE_MAJOR_VERSION)
#error CAL_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define CAL_AR_RELEASE_MAJOR_VERSION     4U

#if (defined CAL_AR_RELEASE_MINOR_VERSION)
#error CAL_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define CAL_AR_RELEASE_MINOR_VERSION     0U

#if (defined CAL_AR_RELEASE_REVISION_VERSION)
#error CAL_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define CAL_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined CAL_SW_MAJOR_VERSION)
#error CAL_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define CAL_SW_MAJOR_VERSION             1U

#if (defined CAL_SW_MINOR_VERSION)
#error CAL_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define CAL_SW_MINOR_VERSION             2U

#if (defined CAL_SW_PATCH_VERSION)
#error CAL_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define CAL_SW_PATCH_VERSION             2U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CAL_VERSION_H ) */
/*==================[end of file]============================================*/

