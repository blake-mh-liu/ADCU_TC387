/**
 * \file
 *
 * \brief AUTOSAR SaSrv
 *
 * This file contains the implementation of the AUTOSAR
 * module SaSrv.
 *
 * \version 1.2.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef SASRV_DSP_COTS_CFG_H
#define SASRV_DSP_COTS_CFG_H

/*==================[includes]====================================================================*/

#include <Rte_SaSrv_Type.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/**
 *  \brief The MAC Generate Service.
 *
 * Uses the given data to perform a MAC generation and stores the MAC in the memory location pointed to by the MAC pointer.
 *
 * \param[in]    DataPtr       Input data.
 * \param[in]    DataLength    Input data length.
 * \param[out]   MacPtr        Output data (MAC).
 * \param[inout] MacLengthPtr  MAC length.
 * \param[in]    CfgId         Configuration identifier.
 * \return Standard Return Code.
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Mac generation failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_COTS_MACGenerateService
(
  P2CONST(uint8,  AUTOMATIC, SaSrv_CONST    ) DataPtr,
          uint32                              DataLength,
    P2VAR(uint8,  AUTOMATIC, SaSrv_APPL_DATA) MacPtr,
    P2VAR(uint32, AUTOMATIC, SaSrv_APPL_DATA) MacLengthPtr,
          uint8                               CfgId
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#endif /* SASRV_DSP_COTS_CFG_H */

/*==================[end of file]=================================================================*/
