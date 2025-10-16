/**
 * \file
 *
 * \brief AUTOSAR MemAcc
 *
 * This file contains the implementation of the AUTOSAR
 * module MemAcc.
 *
 * \version 1.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef MemAcc_INT_H
#define MemAcc_INT_H
/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

/*------------------[the MemAcc Instance Id]---------------------------------*/

#if(defined MEMACC_INSTANCE_ID)
#error MEMACC_INSTANCE_ID is already defined
#endif
/** \brief Defines the instance number of this Memory Access.
 **        Since multiple instances of a Memory Access are not supported
 **        the Instance Id is always zero.
 **/
#define MEMACC_INSTANCE_ID     0x00U

#if(defined MEMACC_INVALID_ADDRESSAREA)
#error MEMACC_INVALID_ADDRESSAREA is already defined
#endif
/** \brief Defines the Invalid address.
 **/
#define MEMACC_INVALID_ADDRESSAREA     0xFFFFU

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef MemAcc_INT_H */
/*==================[end of file]===========================================*/
