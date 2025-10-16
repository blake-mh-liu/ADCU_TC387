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
#ifndef MEMEACC_QUEUE_H
#define MEMEACC_QUEUE_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types             */
#include <MemAcc_Cfg.h>           /* Contains generated configuration       */
#include <MemAcc_Int_Types.h>
/*==================[macros]================================================*/

#define MEMACC_JOB_QUEUE_SIZE MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS /* Place Holder */
#define MEMACC_QUEUE_INVALID_AREA_INDEX 65535u

/*==================[external data]=========================================*/
#define MEMACC_START_SEC_VAR_CLEARED_16
#include <MemAcc_MemMap.h>

extern VAR(MemAcc_AddressAreaIdType, MEMACC_VAR_CLEARED) MemAcc_QueueElementsNo;

#define MEMACC_STOP_SEC_VAR_CLEARED_16
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_VAR_CLEARED_32
#include <MemAcc_MemMap.h>

extern VAR(MemAcc_AddressAreaIdType, MEMACC_VAR ) MemAcc_AreaIdQueue[MEMACC_JOB_QUEUE_SIZE];

#define MEMACC_STOP_SEC_VAR_CLEARED_32
#include <MemAcc_MemMap.h>

/*==================[external function declarations]=========================*/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/** \brief Service for initialization of the Devices internal queue
 **
 ** This function initializes the internal queue of the module.
 ** It is called during the MemAcc module initialization.
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_Queue_Init(void);

/** \brief Insert an AreaId job in queue
 **
 ** \param[in]      AddressAreaCfgIdx  -Index in the configuration data for area to be inserted in queue
 **
 **
 ** \return void
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_InsertInQueue(MemAcc_AddressAreaIdType AddressAreaCfgIdx);

/** \brief Remove a AreaId element from queue after finish.
 **
 ** \param[in]      AddressAreaCfgIdx  -Index in the configuration data for area to be removed from queue
 **
 ** \return void
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_DequeueFromIndex(MemAcc_AddressAreaIdType ElementIdx);


#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

#endif /* ifndef MEMEACC_QUEUE_H */
/*==================[end of file]===========================================*/
