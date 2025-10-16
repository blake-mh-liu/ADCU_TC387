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
#ifndef NVM_TYPES_H
#define NVM_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types      */
#include <Std_Types.h>            /* AUTOSAR standard types*/
[!/*
   If RTE Usage is enabled, Include Rte_NvM_Type.h to get the
   NvM type definitions.
*/!]
[!IF "node:existsAndTrue(NvMCommon/NvMRteUsage)"!][!//
#include <Rte_NvM_Type.h>    /* Rte type definitions. */
[!ENDIF!][!//

/* ==================[macros]================================================= */

/* These types are also defined by RTE if R-ports are used */
[!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(ASR2011CallbackEnabled))]) != 0"!][!//
/* !LINKSTO NvM.SWS_NvM_91123,1 */
#ifndef NVM_INIT_READ_BLOCK
/** \brief input value for the init callback function when AR20-11 is enabled
 ** and NvM_ReadBlock is requested */
#define NVM_INIT_READ_BLOCK               0U
#endif

#ifndef NVM_INIT_RESTORE_BLOCK_DEFAULTS
/** \brief input value for the init callback function when AR20-11 is enabled
 ** and NvM_RestoreBlockDefaults is requested */
#define NVM_INIT_RESTORE_BLOCK_DEFAULTS   1U
#endif

#ifndef NVM_INIT_READ_ALL_BLOCK
/** \brief input value for the init callback function when AR20-11 is enabled
 ** and NvM_ReadAll is requested */
#define NVM_INIT_READ_ALL_BLOCK           2U
#endif

#ifndef NVM_INIT_FIRST_INIT_ALL
/** \brief input value for the init callback function when AR20-11 is enabled
 ** and NvM_RestoreBlockDefaults is requested */
#define NVM_INIT_FIRST_INIT_ALL           3U
#endif

/* !LINKSTO NvM.SWS_NvM_91002,1 */
/* NvM_BlockRequestType: */
#ifndef NVM_READ_BLOCK
/** \brief input value for the single callback function after finishing the job of
 ** NvM_ReadBlock / NvM_ReadPRAMBlock */
#define NVM_READ_BLOCK                0U
#endif

#ifndef NVM_WRITE_BLOCK
/** \brief input value for the single callback function after finishing the job of
 ** NvM_WriteBlock / NvM_WritePRAMBlock */
#define NVM_WRITE_BLOCK               1U
#endif

#ifndef NVM_RESTORE_BLOCK_DEFAULTS
/** \brief input value for the single callback function after finishing the job of
 ** NvM_RestoreBlockDefaults / NvM_RestorePRAMBlockDefaults */
#define NVM_RESTORE_BLOCK_DEFAULTS    2U
#endif

#ifndef NVM_ERASE_NV_BLOCK
/** \brief input value for the single callback function after finishing the job of
 ** NvM_EraseNvBlock */
#define NVM_ERASE_NV_BLOCK            3U
#endif

#ifndef NVM_INVALIDATE_NV_BLOCK
/** \brief input value for the single callback function after finishing the job of
 ** NvM_InvalidateNvBlock */
#define NVM_INVALIDATE_NV_BLOCK       4U
#endif

#ifndef NVM_READ_ALL_BLOCK
/** \brief input value for the single callback function after finishing the job of
 ** NvM_ReadAll */
#define NVM_READ_ALL_BLOCK            5U
#endif
[!ENDIF!][!//

/*==================[type definitions]======================================*/

#ifndef RTE_TYPE_NvM_ASR32_BlockIdType
#define RTE_TYPE_NvM_ASR32_BlockIdType
/**  \brief Defines the NvM block ID which is equal to the
 **  number of the block in the configuration table.
 **  In case the Rte is available this type is defined in Rte_Type.h.
 **/
typedef uint16 NvM_ASR32_BlockIdType;
#endif

#ifndef RTE_TYPE_NvM_ASR32_RequestResultType
#define RTE_TYPE_NvM_ASR32_RequestResultType
/**  \brief Defines the NvM error status e.g. NVM_REQ_OK.
 **  In case the Rte is available, this type is defined in Rte_Type.h.
 **/
typedef uint8 NvM_ASR32_RequestResultType;
#endif

#ifndef RTE_TYPE_NvM_ASR40_BlockIdType
#define RTE_TYPE_NvM_ASR40_BlockIdType
/**  \brief Defines the NvM block ID which is equal to the
 **  number of the block in the configuration table.
 **  In case the Rte is available this type is defined in Rte_Type.h.
 **/
/* !LINKSTO NvM.SWS_NvM_00471,1 */
typedef uint16 NvM_ASR40_BlockIdType;
#endif

#ifndef RTE_TYPE_NvM_ASR40_RequestResultType
#define RTE_TYPE_NvM_ASR40_RequestResultType
/**  \brief Defines the NvM error status e.g. NVM_REQ_OK.
 **  In case the Rte is available, this type is defined in Rte_Type.h.
 **/
/* !LINKSTO NvM.SWS_NvM_00470,3 */
typedef uint8 NvM_ASR40_RequestResultType;
#endif

#ifndef RTE_TYPE_NvM_ASR42_BlockIdType
#define RTE_TYPE_NvM_ASR42_BlockIdType
/**  \brief Defines the NvM block ID which is equal to the
 **  number of the block in the configuration table.
 **  In case the Rte is available this type is defined in Rte_Type.h.
 **/
/* !LINKSTO NvM.SWS_NvM_00471,1 */
typedef uint16 NvM_ASR42_BlockIdType;
#endif

#ifndef RTE_TYPE_NvM_ASR42_RequestResultType
#define RTE_TYPE_NvM_ASR42_RequestResultType
/**  \brief Defines the NvM error status e.g. NVM_REQ_OK.
 **  In case the Rte is available, this type is defined in Rte_Type.h.
 **/
/* !LINKSTO NvM.SWS_NvM_00470,3 */
typedef uint8 NvM_ASR42_RequestResultType;
#endif

[!IF "(node:existsAndFalse(NvMCommon/NvMRteUsage)) or (NvMCommon/NvMServiceAPI/NvMDefaultASRServiceAPI = 'NONE')"!][!//
/** \brief Provides AUTOSAR 4.0 NvM_RequestResultType as default to other
 ** BSW modules */
/* !LINKSTO NvM.SWS_NvM_00471,1 */
typedef NvM_ASR40_BlockIdType NvM_BlockIdType;
/** \brief Provides AUTOSAR 4.0 NvM_RequestResultType as default to other
 ** BSW modules */
/* !LINKSTO NvM.SWS_NvM_00470,3 */
typedef NvM_ASR40_RequestResultType NvM_RequestResultType;
[!ENDIF!][!//

[!IF "(node:existsAndFalse(NvMCommon/NvMRteUsage))"!][!//
[!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(ASR2011CallbackEnabled))]) != 0"!][!//
/** \brief Provides AUTOSAR 2011 NvM_InitBlockRequestType as default to other
 ** BSW modules */
/* !LINKSTO NvM.SWS_NvM_91123,1 */
typedef uint8 NvM_InitBlockRequestType;
/** \brief Provides AUTOSAR 2011 NvM_BlockRequestType as default to other
 ** BSW modules */
/* !LINKSTO NvM.SWS_NvM_91002,1 */
typedef uint8 NvM_BlockRequestType;
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "(count(NvMCommon/NvMEcucPartitionRef/eb-list::*) > 1)"!][!//
[!IF "count(NvMBlockDescriptor/eb-list::*[node:existsAndTrue(NvMProvideRteJobFinishedPort) or ((node:exists(NvMSingleBlockCallback)) and (NvMSingleBlockCallback != ''))]) != 0"!][!//
/**  \brief Defines the NVRAM block error status callback function.
 **         It is called if a asynchronous NvM API request has finished.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobEndCallbackFctPtr )
              ( uint16 BlockId, uint8 ServiceId, uint8 ErrorStatus);
[!ENDIF!][!//
[!IF "NvMCommon/NvMApiConfigClass = 'NVM_API_CONFIG_CLASS_3'"!][!//
/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for EraseNvBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobEraseNvBlockFctPtr )
              ( NvM_ASR40_BlockIdType BlockId );

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for InvalidateNvBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobInvalidateNvBlockFctPtr )
              ( NvM_ASR40_BlockIdType BlockId );
[!ENDIF!][!//
[!IF "(NvMCommon/NvMApiConfigClass = 'NVM_API_CONFIG_CLASS_3') or (NvMCommon/NvMApiConfigClass = 'NVM_API_CONFIG_CLASS_2')"!][!//
/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for ReadBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobReadBlockFctPtr )
              ( NvM_ASR40_BlockIdType BlockId , NvM_SchM_DstPtrType  NvM_DstPtr);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for ReadPRAMBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobReadPRAMBlockFctPtr )
              ( NvM_ASR42_BlockIdType BlockId);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for RestoreBlockDefaults job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobRestoreBlockDefaultsFctPtr )
              ( NvM_ASR40_BlockIdType BlockId , NvM_SchM_DstPtrType  NvM_DstPtr);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for RestorePRAMBlockDefaults job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobRestorePRAMBlockDefaultsFctPtr )
              ( NvM_ASR42_BlockIdType BlockId);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for WriteBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobWriteBlockFctPtr )
              ( NvM_ASR40_BlockIdType BlockId , NvM_SchM_SrcPtrType  NvM_SrcPtr);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for WritePRAMBlock job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobWritePRAMBlockFctPtr )
              ( NvM_ASR42_BlockIdType BlockId);

/**  \brief Defines the SchM NvMSatellite -> NvMMaster call type for CancelJobs job.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SchMJobCancelJobsFctPtr )
              ( NvM_ASR40_BlockIdType BlockId );
[!ENDIF!][!//
[!ENDIF!][!//

/**  \brief Generic function pointer used for callbacks
 **/
typedef P2FUNC( void,NVM_CODE,NvM_CallbackFctPtr )( void );

[!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(ASR2011CallbackEnabled))]) != 0"!][!//
/* !LINKSTO NvM.SWS_NvM_00469,2 */
/**  \brief Defines the NVRAM block initialization call back function.
 **         It is called if data from NVRAM is not readable.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_InitBlockCallbackTypeAR2011 )( NvM_InitBlockRequestType InitBlockRequest );

/* !LINKSTO NvM.SWS_NvM_00467,2 */
/**  \brief Defines the NVRAM block error status callback function.
 **         It is called if a asynchronous NvM API request has finished.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SingleBlockCallbackTypeAR2011 )
              ( NvM_BlockRequestType BlockRequest, NvM_RequestResultType JobResult );
[!ENDIF!][!//

/**  \brief Defines the NVRAM block initialization call back function.
 **         It is called if data from NVRAM is not readable.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_InitBlockCallbackType )( void );

/**  \brief Defines the NVRAM block error status callback function.
 **         It is called if a asynchronous NvM API request has finished.
 **/
typedef P2FUNC( Std_ReturnType,NVM_CODE,NvM_SingleBlockCallbackType )
              ( uint8 ServiceId, NvM_RequestResultType JobResult );

/**  \brief Defines the NVRAM multi request callback function.
 **         It is called if the NvM multiblock requests
 **         NvM_WriteAll() or NvM_ReadAll() or NvM_ValidateAll() is finished.
 **/
typedef P2FUNC( void,NVM_CODE,NvM_MultiBlockCallbackType )
              ( uint8 ServiceId, NvM_RequestResultType JobResult );

[!IF "count(NvMBlockDescriptor/eb-list::*[(node:existsAndTrue(NvMBlockUseSyncMechanism))]) != 0"!][!//
/**  \brief Defines the RAM to NvM copy callback function.
 **         It is called in order to let the application copy data from
 **         RAM block to NvM module's mirror.
 **/

typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_RamToNvCopyCallbackType)
              (P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvMBuffer);

/**  \brief Defines the NvM to RAM copy callback function.
 **         It is called in order to let the application copy data from
 **         NvM module's mirror to RAM block.
 **/
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_NvToRamCopyCallbackType)
              (P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvMBuffer);
[!ENDIF!]

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* NVM_TYPES_H */

/*=========================[end of file NvM_Types.h]========================*/
