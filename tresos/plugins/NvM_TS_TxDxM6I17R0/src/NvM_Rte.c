/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \version 6.17.36
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.3 (required)
 * All declarations of an object or function shall use the same names and type qualifiers.
 *
 * Reason:
 * Declaration is generated through Rte and uses the same underlaying type.
 * The underlaying type is (void*) in case of read and (const void *) in case of write.
 */
/*==================[inclusions]============================================*/

#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>                                             /* EB specific standard types */

#if (defined NVM_INTERNAL_USE)
#error NVM_INTERNAL_USE is already defined
#endif
#define NVM_INTERNAL_USE
#include <NvM_BSW.h>                                              /* Declaration of Nvm BSW APIs */

#if (NVM_INCLUDE_RTE == STD_ON)
#include <Rte_NvM.h>         /* Declaration of Nvm APIs visible to RTE - consistency enforcement */
#endif

#if (( defined(NVM_MC_CALLOUTS_ENABLED) ) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON))
#include <NvM_Wrapper.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

#if (NVM_INCLUDE_RTE == STD_ON)
#if (NVM_DEFAULT_ASR_SERVICE_API == NVM_SERVICE_API_ASR32)
#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC(void, NVM_CODE) NvM_Rte_GetErrorStatus
(
  NvM_BlockIdType BlockId,
  P2VAR( NvM_RequestResultType,AUTOMATIC,NVM_APPL_DATA ) RequestResultPtr
)
{

  NvM_ASR32_GetErrorStatus( BlockId, RequestResultPtr );

}

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC(void, NVM_CODE) NvM_Rte_SetDataIndex
(
  NvM_BlockIdType BlockId, uint8 DataIndex
)
{
  NvM_ASR32_SetDataIndex(BlockId, DataIndex);
}

FUNC(void, NVM_CODE) NvM_Rte_GetDataIndex
(
  NvM_BlockIdType                        BlockId,
  P2VAR( uint8,AUTOMATIC,NVM_APPL_DATA ) DataIndex
)
{
  NvM_ASR32_GetDataIndex(BlockId, DataIndex);
}
#endif  /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
FUNC(void, NVM_CODE) NvM_Rte_SetRamBlockStatus
(
  NvM_BlockIdType BlockId,
  boolean         BlockChanged
)
{

  NvM_ASR32_SetRamBlockStatus(BlockId, BlockChanged);

}
#endif  /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC( Std_ReturnType, NVM_CODE ) NvM_Rte_ReadBlock
(
  NvM_BlockIdType                        BlockId,
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA)  NvM_DstPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR32_ReadBlock(BlockId, NvM_DstPtr);
  return ret;
}

FUNC( Std_ReturnType, NVM_CODE ) NvM_Rte_WriteBlock
(
  NvM_BlockIdType                         BlockId,
  P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR32_WriteBlock(BlockId, NvM_SrcPtr);
  return ret;
}

FUNC( Std_ReturnType, NVM_CODE ) NvM_Rte_RestoreBlockDefaults
(
  NvM_BlockIdType                       BlockId,
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR32_RestoreBlockDefaults(BlockId,  NvM_DestPtr);
  return ret;
}
#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

#if (NVM_SERVICE_PORT_USED == STD_ON)

FUNC( Std_ReturnType, NVM_CODE ) NvM_Rte_EraseNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR32_EraseNvBlock(BlockId);
  return ret;
}

FUNC( Std_ReturnType, NVM_CODE ) NvM_Rte_InvalidateNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR32_InvalidateNvBlock(BlockId);
  return ret;
}

#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_ADMIN_PORT_USED == STD_ON)
FUNC(void, NVM_CODE) NvM_Rte_SetBlockProtection
(
  NvM_BlockIdType BlockId,
  boolean         ProtectionEnabled
)
{
  NvM_ASR32_SetBlockProtection(BlockId, ProtectionEnabled);
}
#endif/* #if (NVM_ADMIN_PORT_USED == STD_ON) */
#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#elif  (NVM_DEFAULT_ASR_SERVICE_API == NVM_SERVICE_API_ASR40)

#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_GetErrorStatus
(
  NvM_BlockIdType BlockId,
  P2VAR( NvM_RequestResultType,AUTOMATIC,NVM_APPL_DATA ) RequestResultPtr
)
{
  Std_ReturnType ret = E_NOT_OK;


  ret = NvM_ASR40_GetErrorStatus( BlockId, RequestResultPtr );


  return ret;
}

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetDataIndex
(
  NvM_BlockIdType BlockId, uint8 DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetDataIndex(BlockId, DataIndex);
  return ret;
}

FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_GetDataIndex
(
  NvM_BlockIdType                        BlockId,
  P2VAR( uint8,AUTOMATIC,NVM_APPL_DATA ) DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_GetDataIndex(BlockId, DataIndex);
  return ret;
}
#endif  /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetRamBlockStatus
(
  NvM_BlockIdType BlockId,
  boolean         BlockChanged
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetRamBlockStatus(BlockId, BlockChanged);
  return ret;
}
#endif  /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

/* Deviation MISRAC2012-1 */
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_ReadBlock
(
  NvM_BlockIdType                        BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA)  NvM_DstPtr
)
{
  Std_ReturnType Result;

#if (defined NVM_READBLOCK_CALLOUT) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Result = NvM_Wrapper_ReadBlock(BlockId, NvM_DstPtr);
#else
  Result = NvM_ASR40_ReadBlock(BlockId, NvM_DstPtr);
#endif

  return Result;
}

/* Deviation MISRAC2012-1 */
FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_WriteBlock
(
  NvM_BlockIdType                         BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType Result = E_NOT_OK;

#if (defined NVM_WRITEBLOCK_CALLOUT) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Result = NvM_Wrapper_WriteBlock(BlockId, NvM_SrcPtr);
#else
  Result = NvM_ASR40_WriteBlock(BlockId, NvM_SrcPtr);
#endif

  return Result;
}

/* Deviation MISRAC2012-1 */
FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_RestoreBlockDefaults
(
  NvM_BlockIdType                       BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType Result;

#if (defined NVM_RESTOREBLOCKDEFAULTS_CALLOUT) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Result = NvM_Wrapper_RestoreBlockDefaults(BlockId, NvM_DestPtr);
#else
  Result = NvM_ASR40_RestoreBlockDefaults(BlockId,  NvM_DestPtr);
#endif

  return Result;
}

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_EraseNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType Result;

#if (defined NVM_ERASENVBLOCK_CALLOUT) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Result = NvM_Wrapper_EraseNvBlock(BlockId);
#else
  Result = NvM_ASR40_EraseNvBlock(BlockId);
#endif

  return Result;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_InvalidateNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType Result;

#if (defined NVM_INVALIDATENVBLOCK_CALLOUT) || (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Result = NvM_Wrapper_InvalidateNvBlock(BlockId);
#else
  Result = NvM_ASR40_InvalidateNvBlock(BlockId);
#endif

  return Result;
}
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_ADMIN_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetBlockProtection
(
  NvM_BlockIdType BlockId,
  boolean         ProtectionEnabled
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetBlockProtection(BlockId, ProtectionEnabled);
  return ret;
}
#endif /* #if (NVM_ADMIN_PORT_USED == STD_ON) */

#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#elif  (NVM_DEFAULT_ASR_SERVICE_API == NVM_SERVICE_API_ASR42)

#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_GetErrorStatus
(
  NvM_BlockIdType BlockId,
  P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_GetErrorStatus(BlockId, RequestResultPtr);

  return ret;
}

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetDataIndex
(
  NvM_BlockIdType BlockId,
  uint8 DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_SetDataIndex(BlockId, DataIndex);

  return ret;
}

FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_GetDataIndex
(
  NvM_BlockIdType BlockId,
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_GetDataIndex(BlockId, DataIndex);

  return ret;
}
#endif  /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetRamBlockStatus
(
  NvM_BlockIdType BlockId,
  boolean BlockChanged
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_SetRamBlockStatus(BlockId, BlockChanged);

  return ret;
}
#endif  /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

/* Deviation MISRAC2012-1 */
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_ReadBlock
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_ReadBlock(BlockId, NvM_DstPtr);

  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_ReadPRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR42_ReadPRAMBlock(BlockId);
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_WriteBlock
(
  NvM_BlockIdType BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_WriteBlock(BlockId, NvM_SrcPtr);

  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_WritePRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR42_WritePRAMBlock(BlockId);
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_RestoreBlockDefaults
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_RestoreBlockDefaults(BlockId, NvM_DestPtr);

  return ret;
}


FUNC( Std_ReturnType,NVM_CODE ) NvM_Rte_RestorePRAMBlockDefaults
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR42_RestorePRAMBlockDefaults(BlockId);
  return ret;
}

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_EraseNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_EraseNvBlock(BlockId);

  return ret;
}

FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_InvalidateNvBlock
(
  NvM_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_InvalidateNvBlock(BlockId);

  return ret;
}
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_ADMIN_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_Rte_SetBlockProtection
(
  NvM_BlockIdType BlockId,
  boolean ProtectionEnabled
)
{
  Std_ReturnType ret = E_NOT_OK;

  ret = NvM_ASR42_SetBlockProtection(BlockId, ProtectionEnabled);

  return ret;
}
#endif /* #if (NVM_ADMIN_PORT_USED == STD_ON) */

#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */
#endif /* #if (NVM_DEFAULT_ASR_SERVICE_API == NVM_SERVICE_API_ASR32) */
#endif /* #if (NVM_INCLUDE_RTE == STD_ON) */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#if ((NVM_INCLUDE_RTE == STD_OFF) &&\
     (NVM_ENABLE_ASR32_SERVICE_API == STD_OFF) &&\
     (NVM_ENABLE_ASR40_SERVICE_API == STD_OFF) &&\
     (NVM_ENABLE_ASR42_SERVICE_API == STD_OFF) \
    )

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

#endif /* ((NVM_INCLUDE_RTE == STD_OFF) && (NVM_ENABLE_ASR32_SERVICE_API == STD_OFF)) */
/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
