/**
 * \file
 *
 * \brief AUTOSAR Dlt
 *
 * This file contains the implementation of the AUTOSAR
 * module Dlt.
 *
 * \version 1.9.2
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef DLT_DET_H
#define DLT_DET_H

/*==[Includes]================================================================*/

#include <Dlt_Cfg.h>

/*==[Macros definitions]======================================================*/

/*--[API Service IDs]---------------------------------------------------------*/
#if (defined DLT_SID_DetForwardErrorTrace)
#error DLT_SID_DetForwardErrorTrace already defined
#endif
/** \brief Service Id for Dlt_DetForwardErrorTrace() */
#define DLT_SID_DetForwardErrorTrace 0x07U

/*==[Types declarations]======================================================*/
/*==[Declaration of constants with external linkage]==========================*/
/*==[Declaration of variables with external linkage]==========================*/
/*==[Declaration of functions with external linkage]==========================*/

#if (DLT_DET_FORWARDERRORTRACE == STD_ON)

#define DLT_START_SEC_CODE
#include <Dlt_MemMap.h>

/* !LINKSTO Dlt.SWS_Dlt_00430, 1, Dlt.SWS_Dlt_00432, 1 */
extern FUNC(void, DLT_CODE) Dlt_DetForwardErrorTrace(uint16 ModuleId,
                                                     uint8  InstanceId,
                                                     uint8  ApiId,
                                                     uint8  ErrorId);

#define DLT_STOP_SEC_CODE
#include <Dlt_MemMap.h>

#endif

#endif /* ifndef DLT_DET_H */
