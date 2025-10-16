/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CANTSYN_INT_STC_H
#define CANTSYN_INT_STC_H

/*==================[inclusions]============================================*/

#include <ComStack_Types.h> /* typedefs for AUTOSAR com stack */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/** \brief Partition config
 **
 ** This type contains the number of time domains and the time domains
 ** which are connected to a a certain partition.
 */
typedef struct
{
  CONST(uint8, TYPEDEF) partitionIndex;  /**< Partition index */
  CONST(uint8, TYPEDEF) numberOfTimeDomains;  /**< Number of connected time domains per partition */
  CONSTP2CONST(uint16, TYPEDEF, CANTSYN_APPL_CONST) partitionTimeDomainsList; /**< Pointer to the structure which contains all the time domains connected to a certain partition */
} CanTSyn_PartitionCfgType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef CANTSYN_INT_STC_H */
/*==================[end of file]============================================*/

