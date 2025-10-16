#ifndef J1939TP_VERSION_H
#define J1939TP_VERSION_H
/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined J1939TP_VENDOR_ID)
#error J1939TP_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define J1939TP_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined J1939TP_MODULE_ID)
#error J1939TP_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define J1939TP_MODULE_ID         37U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined J1939TP_AR_RELEASE_MAJOR_VERSION)
#error J1939TP_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define J1939TP_AR_RELEASE_MAJOR_VERSION     4U

#if (defined J1939TP_AR_RELEASE_MINOR_VERSION)
#error J1939TP_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define J1939TP_AR_RELEASE_MINOR_VERSION     2U

#if (defined J1939TP_AR_RELEASE_REVISION_VERSION)
#error J1939TP_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define J1939TP_AR_RELEASE_REVISION_VERSION  2U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined J1939TP_SW_MAJOR_VERSION)
#error J1939TP_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define J1939TP_SW_MAJOR_VERSION             1U

#if (defined J1939TP_SW_MINOR_VERSION)
#error J1939TP_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define J1939TP_SW_MINOR_VERSION             2U

#if (defined J1939TP_SW_PATCH_VERSION)
#error J1939TP_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define J1939TP_SW_PATCH_VERSION             14U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef J1939TP_VERSION_H */
/*==================[end of file]============================================*/
