/**
 * \file
 *
 * \brief AUTOSAR Xcp
 *
 * This file contains the implementation of the AUTOSAR
 * module Xcp.
 *
 * \version 2.13.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to object
 *
 * Reason:
 * The MTA address for write purposes is needed.
 */

/*==[Includes]================================================================*/

#include <Xcp_MemoryProxy.h>
#include <Xcp.h>
#include <Xcp_Int.h>
#if (XCP_RAM_CALLOUT_PROXY_ENABLED == STD_ON)
#include <Xcp_UserCallouts.h>
#endif

#if(XCP_BSW_DISTRIBUTION_MEMORY_ACCESS_AREAS == STD_ON)

#include <TSMem.h>

/*==[Variables with external linkage]=========================================*/

#define XCP_START_SEC_VAR_CLEARED_MEMORY_PROXY_8
#include <Xcp_MemMap.h>

VAR(uint8, XCP_VAR_CLEARED) Xcp_MemoryProxyBuffer[XCP_MAX_MEMORY_WRITE_BYTES];

#define XCP_STOP_SEC_VAR_CLEARED_MEMORY_PROXY_8
#include <Xcp_MemMap.h>

#define XCP_START_SEC_VAR_CLEARED_MEMORY_PROXY_16
#include <Xcp_MemMap.h>

VAR(uint16, XCP_VAR_CLEARED) Xcp_MemoryProxyResponseLength;

#define XCP_STOP_SEC_VAR_CLEARED_MEMORY_PROXY_16
#include <Xcp_MemMap.h>

#define XCP_START_SEC_VAR_INIT_MEMORY_PROXY_UNSPECIFIED
#include <Xcp_MemMap.h>

VAR(Atomic_t, XCP_VAR) Xcp_MemoryProxyState = ATOMICS_OBJECT_INITIALIZER(XCP_MEMORY_PROXY_AVAILABLE);

#define XCP_STOP_SEC_VAR_INIT_MEMORY_PROXY_UNSPECIFIED
#include <Xcp_MemMap.h>

/*==[Definition of functions with external linkage]===========================*/

#define XCP_START_SEC_CODE
#include <Xcp_MemMap.h>

FUNC(void, XCP_CODE) Xcp_MemoryProxyHandler(Xcp_MemoryProxyDataType* data)
{
  switch(data->type)
  {
#if (XCP_BSW_DISTRIBUTION_CALIBRATION_MEMORY_ACCESS_AREAS == STD_ON)
    case XCP_MEMORYPROXYDATA_UPLOAD:
    case XCP_MEMORYPROXYDATA_DOWNLOAD:
    case XCP_XCP_MEMORYPROXYDATA_CRC:
    {
      Xcp_MemoryRequestType type = XCP_MEMORY_REQUEST_READ;
      Xcp_ErrorType ret;
      switch (data->type)
      {
        case XCP_MEMORYPROXYDATA_DOWNLOAD:
          type = XCP_MEMORY_REQUEST_WRITE;
          break;
        case XCP_MEMORYPROXYDATA_UPLOAD:
          type = XCP_MEMORY_REQUEST_READ;
          break;
        case XCP_XCP_MEMORYPROXYDATA_CRC:
          type = XCP_MEMORY_REQUEST_CRC;
          break;
        /* CHECK: NOPARSE */
        default:
          /* No action required */
          break;
        /* CHECK: PARSE */
      }
      ret = Xcp_BswDistributionMemoryAccess(
              data->address,
              &Xcp_MemoryProxyResponseLength,
              (Xcp_MemoryRequestSizeType)data->size,
              type,
#if (XCP_RAM_CALLOUT_PROXY_ENABLED == STD_ON)
              data->MemoryAreaIdx
#else
              /* dummy value */
              0U
#endif
              ,data->sessionState
            );
      if (ret != XCP_E_BUSY)
      {
        Xcp_MemoryProxySetReadyIfSameSession(data->sessionState);
      }
      break;
    }
#endif
#if (XCP_BSW_DISTRIBUTION_DAQSTIM_MEMORY_ACCESS_AREAS == STD_ON)
    case XCP_MEMORYPROXYDATA_EVENT_PROCESSOR:
    {
      uint16 Idx = 0U;
      uint16 ReadIdx = data->IdxRequestBuffer;
      /* !LINKSTO Xcp.dsn.BSWDistribution.MemProxy.Atomics,1 */
      Atomic_value_t partition = Atomics_Load(&Xcp_PartitionOfActiveConnection);
      uint8 CurrentApplicationId = (uint8)GetApplicationID();

      for (Idx = 0U; Idx < data->size; Idx++)
      {
        if (data->RequestBuffer[ReadIdx].appId == CurrentApplicationId)
        {
          if (data->RequestBuffer[ReadIdx].type == XCP_MEMORYPROXYDATA_STIMULATION)
          {
            TS_MemCpy(data->RequestBuffer[ReadIdx].address1, data->RequestBuffer[ReadIdx].address2, data->RequestBuffer[ReadIdx].size);
          }
          else if (data->RequestBuffer[ReadIdx].type == XCP_MEMORYPROXYDATA_SAMPLE_0)
          {
            /* !LINKSTO Xcp.dsn.BSWDistribution.EventProcessing.MemProxy.CopyDataIntoMirror,2 */
            *(uint8 *)data->RequestBuffer[ReadIdx].address2 = 0U;
          }
          else if (data->RequestBuffer[ReadIdx].type == XCP_MEMORYPROXYDATA_SAMPLE_1)
          {
            /* !LINKSTO Xcp.dsn.BSWDistribution.EventProcessing.MemProxy.CopyDataIntoMirror,2 */
            *(uint8 *)data->RequestBuffer[ReadIdx].address2 = 1U;
          }
          else if (data->RequestBuffer[ReadIdx].type == XCP_MEMORYPROXYDATA_STIMULATION_0)
          {
            /* Deviation MISRAC2012-1 */
            *(uint8 *)data->RequestBuffer[ReadIdx].address2 =
                 *(uint8 *)data->RequestBuffer[ReadIdx].address1 | (uint8)(data->RequestBuffer[ReadIdx].bitMask);
            TS_MemCpy(data->RequestBuffer[ReadIdx].address1,
                 data->RequestBuffer[ReadIdx].address2, data->RequestBuffer[ReadIdx].size);
          }
          else if (data->RequestBuffer[ReadIdx].type == XCP_MEMORYPROXYDATA_STIMULATION_1)
          {
            /* Deviation MISRAC2012-1 */
            *(uint8 *)data->RequestBuffer[ReadIdx].address2 =
               *(uint8 *)data->RequestBuffer[ReadIdx].address1 & (uint8)(~data->RequestBuffer[ReadIdx].bitMask);
            TS_MemCpy(data->RequestBuffer[ReadIdx].address1,
                 data->RequestBuffer[ReadIdx].address2, data->RequestBuffer[ReadIdx].size);
          }
          else
          {
            /* !LINKSTO Xcp.dsn.BSWDistribution.EventProcessing.MemProxy.CopyDataIntoMirror,2 */
            /* copy data into the mirror */
            TS_MemCpy(data->RequestBuffer[ReadIdx].address2, data->RequestBuffer[ReadIdx].address1, data->RequestBuffer[ReadIdx].size);
          }
        }
        ReadIdx++;
        if (ReadIdx == XCP_MAX_SIZE_OF_REQUEST_BUFFER)
        {
          ReadIdx = 0U;
        }
      }

      if (CurrentApplicationId != partition)
      {
        (void) Xcp_SendMemoryProxyNotification[CurrentApplicationId][partition](data->EventId);
      }

      break;
    }
#endif
    /* CHECK: NOPARSE */
    default:
      /* all possible cases have been explicitly covered in 'case's above, the 'default'
       * cannot be reached */
       XCP_UNREACHABLE_CODE_ASSERT(XCP_SID_MAIN_FUNCTION);
      break;
    /* CHECK: PARSE */
  }
}

#if (XCP_RAM_CALLOUT_PROXY_ENABLED == STD_ON)

FUNC(void, XCP_CODE) Xcp_ApplReadDataFromRAMFinished
(
  uint8 result,
  P2VAR(void, AUTOMATIC, XCP_VAR) AddressPtr,
  P2CONST(uint8, AUTOMATIC, XCP_CONST) DataPtr,
  uint8 DataLength,
  uint16 SessionState
)
{
  TS_PARAM_UNUSED(result);
  TS_PARAM_UNUSED(AddressPtr);
  TS_PARAM_UNUSED(DataPtr);
  TS_PARAM_UNUSED(DataLength);
  Xcp_MemoryProxySetReadyIfSameSession(SessionState);
}

FUNC(void, XCP_CODE) Xcp_ApplWriteDataToRAMFinished
(
  uint8 result,
  P2VAR(void, AUTOMATIC, XCP_VAR) AddressPtr,
  P2CONST(uint8, AUTOMATIC, XCP_CONST) DataPtr,
  uint8 DataLength,
  uint16 SessionState
)
{
  TS_PARAM_UNUSED(result);
  TS_PARAM_UNUSED(AddressPtr);
  TS_PARAM_UNUSED(DataPtr);
  TS_PARAM_UNUSED(DataLength);
  Xcp_MemoryProxySetReadyIfSameSession(SessionState);
}

#endif

FUNC(void, XCP_CODE) Xcp_MemoryProxySetNewState(uint8 newState)
{
  Atomic_value_t localProxyState;
  Atomic_value_t newProxyState;
  localProxyState = Atomics_Load(&Xcp_MemoryProxyState);
  newProxyState = (localProxyState / XCP_MEMORY_PROXY_STATES_COUNT) * XCP_MEMORY_PROXY_STATES_COUNT + newState;
  Atomics_Store(&Xcp_MemoryProxyState, newProxyState);
}

FUNC(void, XCP_CODE) Xcp_MemoryProxySetAvailableNewSession(void)
{
  Atomic_value_t localProxyState;
  Atomic_value_t newProxyState;
  /* CHECK: NOPARSE */
  do
  {
    localProxyState = Atomics_Load(&Xcp_MemoryProxyState);
    newProxyState = ((localProxyState / XCP_MEMORY_PROXY_STATES_COUNT) + 1U) * XCP_MEMORY_PROXY_STATES_COUNT;
  }while(!Atomics_CompareExchange(&Xcp_MemoryProxyState, &localProxyState, newProxyState));
  /* CHECK: PARSE */
}

FUNC(void, XCP_CODE) Xcp_MemoryProxySetReadyIfSameSession(uint16 original)
{
  Atomic_value_t localProxyState;
  Atomic_value_t newProxyState;
  /* CHECK: NOPARSE */
  do
  {
    localProxyState = Atomics_Load(&Xcp_MemoryProxyState);
    if ((uint16) localProxyState == original)
    {
      newProxyState = (localProxyState / XCP_MEMORY_PROXY_STATES_COUNT) * XCP_MEMORY_PROXY_STATES_COUNT + XCP_MEMORY_PROXY_READY;
    }
    else
    {
      break;
    }
  }while(!Atomics_CompareExchange(&Xcp_MemoryProxyState, &localProxyState, newProxyState));
  /* CHECK: PARSE */
}

#define XCP_STOP_SEC_CODE
#include <Xcp_MemMap.h>

#endif /* XCP_BSW_DISTRIBUTION_MEMORY_ACCESS_AREAS == STD_ON */
