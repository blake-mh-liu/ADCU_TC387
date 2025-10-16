/**
 * \file
 *
 * \brief AUTOSAR CanTrcv
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTrcv.
 *
 * \version 1.0.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


#if (!defined CANTRCV_CFG_H)
#define CANTRCV_CFG_H


/*==================[inclusions]=============================================*/


#include <Std_Types.h>            /* Standard types */

/*==================[macros]=================================================*/

/** \brief CanIf callback API support
 **
 ** This configuration parameter defines if the CanTrcv uses CanIf PN callbacks
 */
[!IF "VendorSpecific/CanTrcvPnCanIfCallbackSupport = 'true'"!][!//
#define CANTRCV_CANIF_PN_CALLBACK_SUPPORT STD_ON
[!ELSE!][!//
#define CANTRCV_CANIF_PN_CALLBACK_SUPPORT STD_OFF
[!ENDIF!][!//

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* #if (!defined CANTRCV_CFG_H) */

/*==================[end of file]============================================*/
