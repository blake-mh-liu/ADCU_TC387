[!INCLUDE "../../generate_macros/Base_Vars.m"!][!//
#ifndef FR_GENERALTYPES_CFG_H
#define FR_GENERALTYPES_CFG_H
[!AUTOSPACING!][!//
/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[type definitions]=======================================*/

/*==================[macros]=================================================*/
#if (defined FRCHANNELAVALUE)
#error FrChannelAValue already defined
#endif
#define FRCHANNELAVALUE [!"$FrChannelAValue"!]
#endif /* ifndef ETH_GENERALTYPES_CFG_H */