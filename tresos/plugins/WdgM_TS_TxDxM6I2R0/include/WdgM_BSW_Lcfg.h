/**
 * \file
 *
 * \brief AUTOSAR WdgM
 *
 * This file contains the implementation of the AUTOSAR
 * module WdgM.
 *
 * \version 6.2.7
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*
 * Misra-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (Required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The Autosar macro P2CONST shall have ptrtype as the reference type
 * whitch in our case is struct <typename>. If parantheses are used then
 * type definition will be wrong.
 */

#ifndef WDGM_BSW_LCFG_H
#define WDGM_BSW_LCFG_H
/*==================[inclusions]=================================================================*/
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure06,1 */
#include <WdgM_Int.h>                                            /* WdgM Internal Data and Types */
/* !LINKSTO WDGM.EB.Design.IncludeFileStructure07,1 */
#include <WdgIf.h>                                                             /* WdgIf_ModeType */

/*==================[macros]=====================================================================*/
#if (defined WDGM_EB_DUMMY_SEID)
#error WDGM_EB_DUMMY_SEID is already defined
#endif

/** \brief dummy SEID in case some SE/CP has no predecessor */
#define WDGM_EB_DUMMY_SEID 255U

#if (defined WDGM_EB_DUMMY_CPID)
#error WDGM_EB_DUMMY_CPID is already defined
#endif

/** \brief dummy CPID in case some SE/CP has no predecessor */
#define WDGM_EB_DUMMY_CPID 255U

#if (defined WDGM_EB_DUMMY_FAILEDREFCYCLETOL)
#error WDGM_EB_DUMMY_FAILEDREFCYCLETOL is already defined
#endif

/** \brief dummy failed reference cycle tolerance in case a SE is not configured in some mode */
#define WDGM_EB_DUMMY_FAILEDREFCYCLETOL 0U

#if (defined WDGM_EB_FALSE)
#error WDGM_EB_FALSE is already defined
#endif
#if (defined WDGM_EB_TRUE)
#error WDGM_EB_TRUE is already defined
#endif
#if (WDGM_MIXED_CRITICALITY == STD_ON)
#define WDGM_EB_FALSE 0xFF00U
#define WDGM_EB_TRUE 0xFE01U
#else /* (WDGM_MIXED_CRITICALITY == STD_ON) */
#define WDGM_EB_FALSE FALSE
#define WDGM_EB_TRUE TRUE
#endif

/*==================[type definitions]===========================================================*/

/*------------------[basic type definitions]-----------------------------------------------------*/

#if (WDGM_MIXED_CRITICALITY == STD_ON)
/** \brief contains the local statuses of all SE from core */
typedef uint16 WdgM_EB_LocalStatusType;
/** \brief used by the WdgM master instance to notify WdgM satellite instances that the mode switch has been performed */
typedef uint16 WdgM_EB_ModeType;
#if (WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED == STD_ON)
/** \brief used to detect Watchdog Satellite failure */
typedef uint16 WdgM_EB_SatelliteWdgIfSetModeFailedType;
#endif
#else
/** \brief contains the local statuses of all SE from core */
typedef uint8 WdgM_EB_LocalStatusType;

#if (WDGM_EB_MULTICORE_ENABLED == STD_ON)
/** \brief used by the WdgM master instance to notify WdgM satellite instances that the mode switch has been performed */
typedef uint8 WdgM_EB_ModeType;
#endif

#if (WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED == STD_ON)
/** \brief used to detect Watchdog Satellite failure */
typedef uint8 WdgM_EB_SatelliteWdgIfSetModeFailedType;
#endif
#endif

/** \brief result type of a checkpoint */
typedef uint8 WdgM_EB_ResultType;

#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
/** \brief identifier of a logical supervision graph */
typedef uint16 WdgM_EB_GraphIdType;
#endif

#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
/** \brief identifier of a deadline supervision entity */
typedef uint16 WdgM_EB_DMIdType;
#endif

/** \brief identifier of a supervised entity
 *
 * This is a deviation from AUTOSAR and is fixed to uint8 in order to use atomic assignments */
typedef uint8 WdgM_EB_SEIdType;

/** \brief identifier of a checkpoint
 *
 * This is a deviation from AUTOSAR and is fixed to uint8 in order to use atomic assignments */
typedef uint8 WdgM_EB_CPIdType;

/** \brief alive counter data */
typedef uint16 WdgM_EB_AliveCounterType;

/** \brief the value of a trigger condition */
typedef uint16 WdgM_EB_TriggerConditionType;

/** \brief the id of a trigger */
typedef uint8 WdgM_EB_TriggerIdType;

/** \brief the id of a watchdog */
typedef uint8 WdgM_EB_WatchdogIdType;

/** \brief the first expired SEId
 *
 * Holding the SEId and the bit-inverse value */
typedef uint16 WdgM_EB_ExpiredSEIDType;

#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
/** \brief a timestamp for deadline monitoring */
typedef uint32 WdgM_EB_TimestampType;
#endif

#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
/** \brief holding a checkpoint */
typedef struct
{
  WdgM_EB_SEIdType SEId;
  WdgM_EB_CPIdType CPId;
} WdgM_EB_CPType;
#endif

#if (WDGM_PARTITION_RESET == STD_ON)
/** \brief Holding information of SEs mapped to an Os Application */
typedef struct
{
  CONSTP2VAR(WdgM_EB_SEIdType, AUTOMATIC, AUTOMATIC) WdgM_EB_SE;
  CONST(uint8, WDGM_CONST) WdgM_EB_Size;
} WdgM_EB_SE_Type;
#endif

/*------------------[data type definitions]------------------------------------------------------*/

#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable4,1 */
/** \brief data for a deadline supervision graph */
typedef struct
{
  WdgM_EB_TimestampType StartTimestampData;
  /**< time-stamp when the start Checkpoint was called */
  WdgM_EB_TimestampType StartTimestampDataInv;
  /**< bit-inverse time-stamp when the start Checkpoint was called */
  uint32 MaxCyclesData;
  /**<  maximum allowed main function cycles until deadline violation */
  uint16 IsActiveData;
  /**< active flag of the Deadline Monitoring including bit-inverse data */
} WdgM_EB_DMDataType;
#endif

/** \brief runtime data of a CP */
typedef struct
{
  /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable3,1 */
  uint32 AliveCounterData; /**< alive counter and bit-inverse of it */
#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
  /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable5,1 */
  uint16 DeadlineData; /**< deadline result and bit-inverse of it */
#endif
#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
  /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable8,1 */
  uint16 LogicalData; /**< logical result and bit-inverse of it */
#endif
} WdgM_EB_CPDataType;

#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable6,2,
            WDGM.EB.DesignDecision.InternalVariable7,2 */
/** \brief data for a logical supervision graph */
typedef struct
{
  uint32 LastCPData; /**< last checkpoint including bit-inverse data */
  /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable7,2 */
  uint16 IsActiveData; /**< active flag of the graph including bit-inverse data */
} WdgM_EB_GraphDataType;
#endif

#if (WDGM_EB_EXTERNAL_GRAPH_NUM > 0U)
/** \brief the sequence counter for all CP in one graph
 *
 * Holding the counter to determine concurrent call of ChecpointReached function including bit-inverse data */
typedef uint16 WdgM_EB_ExtGraphDataSeqArrayType;
#endif

/*------------------[configuration type definitions]---------------------------------------------*/

#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
/** \brief configuration data for logical supervision of a CP */
typedef struct
{
  P2CONST(WdgM_EB_CPType,TYPEDEF,WDGM_CONST) PredCPs;
  /**< pointer to an array of allowed predecessor CPs. NULL_PTR if no predecessors are allowed. */
  WdgM_EB_GraphIdType GraphId; /**< id of the graph the CP belongs to */
  uint8 SESequenceIdx; /**< index in the Sequence Graph Array for the SE which contains this CP.
  All CPs, belonging to the graph, which are part of the same SE have the same index in the Array. */
  uint8 NumOfPredCPs; /**< number of allowed predecessor CPs. If 0, then this is an initial CP. */
  boolean IsFinal; /**< flag for being a final CP */
#if (WDGM_EB_OPTIMIZED_EXTERNAL_GRAPH_ENABLED == STD_ON)
  boolean IsOptimized; /**< flag for external graph optimization. */
#endif
} WdgM_EB_CPLogicalCfgType;
#endif

/** \brief configuration data for alive supervision of a CP */
typedef struct
{
  uint16 ExpectedAliveIndication; /**< amount of expected alive indications */
  uint16 SupervisionReferenceCycle;
  /**< amount of supervision cycles needed until checking is performed */

  uint8 MaxMargin; /**< maximum number of additional indications */
  uint8 MinMargin; /**< maximum number of fewer indications */
} WdgM_EB_CPAliveCfgType;

#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
/** \brief configuration data for deadline monitoring of a CP */
typedef struct WdgM_EB_CPDeadlineCfgStructType
{
  WdgM_EB_TimestampType WdgMDeadlineMax; /**< maximum Deadline time */
  WdgM_EB_TimestampType WdgMDeadlineMin; /**< minimum Deadline time */
  uint16 DMMaxMainfunctionCycles; /**< maximum main function calls until deadline violation */
  /* Deviation MISRAC2012-1 */
  P2CONST(struct WdgM_EB_CPDeadlineCfgStructType,TYPEDEF,WDGM_CONST) PrevCPDeadlineCfg;
  /**< pointer to deadline configuration in case a start checkpoint is a stop checkpoint
   * of a previous deadline supervision configuration */
  WdgM_EB_DMIdType DMId;
  /**< id of the Deadline Monitoring this CP belongs to in case of a Start CP,
   * in case of a Stop CP, this variable is retrieved via \a PrevCPDeadlineCfg. */
  WdgM_EB_CPIdType StartCPId; /**< Internal Checkpoint id of start checkpoint */
  WdgM_EB_CPIdType StopCPId; /**< Internal Checkpoint id of stop checkpoint */
} WdgM_EB_CPDeadlineCfgType;
#endif

/** \brief configuration data of a CP */
typedef struct
{
  P2CONST(WdgM_EB_CPAliveCfgType,TYPEDEF,WDGM_CONST) AliveCfgPtr[WDGM_EB_MODE_NUM];
  /**< array of pointers to alive supervision configuration */
#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
  P2CONST(WdgM_EB_CPDeadlineCfgType,TYPEDEF,WDGM_CONST) DeadlineCfgPtr[WDGM_EB_MODE_NUM];
  /**< array of pointers to deadline monitoring configuration */
#endif
#if (WDGM_EB_LOGICAL_SUPERVISION_ENABLED == STD_ON)
  P2CONST(WdgM_EB_CPLogicalCfgType,TYPEDEF,WDGM_CONST) IntLogicalCfgPtr[WDGM_EB_MODE_NUM];
  /**< array of pointers to internal logical supervision configuration */
  P2CONST(WdgM_EB_CPLogicalCfgType,TYPEDEF,WDGM_CONST) ExtLogicalCfgPtr[WDGM_EB_MODE_NUM];
  /**< array of pointers to external logical supervision configuration */
#endif
} WdgM_EB_CPCfgType;

/** \brief configuration data of a SE */
typedef struct
{
  P2CONST(WdgM_EB_CPCfgType,TYPEDEF,WDGM_CONST) CPCfg;
  /**< pointer to an array of length NumOfCPs of CP configurations */
  P2VAR(WdgM_EB_CPDataType,TYPEDEF,WDGM_VAR) CPData;
  /**< pointer to an array of length NumOfCPs of CP runtime data */
  WdgM_EB_SEIdType SEId;
  /**< identifier of the external SE */
  WdgM_EB_CPIdType NumOfCPs;
  /**< number of CPs in this SE */
  boolean ErrorRecoveryEnabled;
  /**< True, if Supervised Entity shall never enter state Expired for sake of error recovery */
#if (WDGM_PARTITION_RESET == STD_ON)
  boolean OsPartitionRefEnabled;
  /**< True, if the Supervised Entity is mapped to an Os Application */
  ApplicationType OsPartitionRef;
  /**< identifier of a referenced Os Application. */
  P2VAR(uint8,TYPEDEF,WDGM_VAR) PartitionStatus;
  /**< Status of the WdgM partition. */
#endif
  uint8 FailedAliveSupervisionRefCycleTol[WDGM_EB_MODE_NUM];
  /**< amount of reference cycles that are tolerable to fail in the given mode */
#if (WDGM_EB_MULTICORE_ENABLED == STD_ON)
  WdgM_EB_CoreIdType CoreID;
  /**< Core ID where the SE is executed */
#endif
} WdgM_EB_SECfgType;

/** \brief configuration data for a watchdog trigger */
typedef struct
{
  WdgIf_ModeType WatchdogMode; /**< watchdog mode to use for triggering */
  WdgM_EB_TriggerConditionType TriggerCondition; /**< the value that is used for triggering */
  WdgM_EB_WatchdogIdType WatchdogId; /**< the id of the watchdog to trigger */
#if(WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED == STD_ON)
  boolean TriggerFromAllCores; /* watchdog is core aware and must be triggered from all cores */
  WdgM_EB_CoreIdType WdgCoreId; /* watchdog is core aware and must be triggered from a specific core */
#endif
} WdgM_EB_TriggerCfgType;

/** \brief configuration data for each mode */
typedef struct
{
  uint32 MaxSupervisionCycleCounter;
  /**< least common multiple of all reference cycle values */
  P2CONST(WdgM_EB_TriggerCfgType, TYPEDEF, WDGM_CONST) TriggerCfg;
  /**< pointer to an array of trigger configurations */
  uint16 ExpiredSupervisionCycleTol;
  /**< amount of supervision cycles to wait in state EXPIRED */
  WdgM_EB_TriggerIdType NumTriggers;
  /**< number of triggers configured for this mode */
} WdgM_EB_ModeCfgType;

/** \brief internal runtime data of a CP (only accessed from MainFunction) */
typedef struct
{
  WdgM_EB_AliveCounterType AliveCounterData; /**< alive counter */
} WdgM_EB_CPInternalDataType;

#if (WDGM_EB_EXTERNAL_GRAPH_NUM > 0U)
/** \brief Externals Graph run-time data
 *
 * This type is used to represent the pointer to the run-time data for each
 * external graph to store the sequence number of checkpoint for each
 * supervised entity and the number of SE of the runtime-data
 */
typedef struct
{
  P2VAR(WdgM_EB_ExtGraphDataSeqArrayType, TYPEDEF, WDGM_VAR) GraphDataPtr; /**< pointer to an array of length NumOfSEperGraphId
  which contains the greatest sequence number for each SE in the external graph */
  uint8 NumOfSEperGraphId; /**< length of the array pointed above */
} WdgM_EB_ExtGraphDataSeqType;
#endif

/** \brief core instance data */
typedef struct
{
  CONSTP2VAR(WdgM_EB_LocalStatusType, AUTOMATIC, AUTOMATIC) WdgM_EB_SELocalStatus; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable1,4 */
  /**< local statuses of SE from a specific core */
#if (WDGM_TRIGGER_WDG_DRIVER_MULTICORE_ENABLED == STD_ON)
  CONSTP2VAR(WdgM_EB_SatelliteWdgIfSetModeFailedType, AUTOMATIC, AUTOMATIC) WdgM_EB_SatelliteWdgIfSetModeFailed;
  /**<local status for the SatelliteWdgIfSetMode for a specific core*/
#endif
#if(WDGM_EB_MULTICORE_ENABLED == STD_ON)
#if(WDGM_EB_EXT_SATELLITE_ALIVENESS_ENABLED == STD_ON)
  CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) WdgM_EB_Satellite_AliveCounter;
  /**<local status for the SatelliteAliveCounter for a specific core*/
#endif
#endif
#if (WDGM_EB_GET_ALL_EXPIRED_SE == STD_ON)
  P2VAR(WdgM_EB_ExpiredSEIDType, AUTOMATIC, AUTOMATIC) WdgM_EB_ExpiredSEIDs; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable27,1 */
  /**< holds the all the expired SEs */
  CONST(uint8, WDGM_CONST) WdgM_EB_ExpiredSEIDArraySize;
  /**< holds the maximum size of expired SEs */
  P2VAR(WdgM_EB_ExpiredSEIDType, AUTOMATIC, AUTOMATIC) WdgM_EB_ExpiredSEIDsCounter; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable28,1 */
  /**< holds the number of expired SEs */
#endif
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) WdgM_EB_FailedAliveSupervisionRefCycleCnt; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable10,3 */
  /**< failed reference cycle counter for the SE */
  CONSTP2VAR(WdgM_EB_CPInternalDataType, AUTOMATIC, AUTOMATIC) WdgM_EB_IntRAMData; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable25,1 */
  /**< Internal RAM data holding a copy of the alive counter values for each checkpoint */
  CONSTP2VAR(WdgM_EB_InitStatusType, AUTOMATIC, AUTOMATIC) WdgM_EB_InitStatus; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable15,3 */
  /**< initialization status for each core */
#if (WDGM_EB_MULTICORE_ENABLED == STD_ON)
  CONSTP2VAR(WdgM_EB_ModeType, AUTOMATIC, AUTOMATIC) WdgM_EB_CoreSwitchMode; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable14,1 */
  /**< used to have a synchronous switch mode for all cores */
#endif
  VAR(uint32, WDGM_VAR) WdgM_EB_SupervisionCycleCnt;   /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable31,1 */
  /**< WdgM internal counter for supervision cycles */
  WdgM_ModeType WdgM_EB_CurrentModeId; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable21,1 */
  /**< WdgM_EB_CurrentModeId represents current mode id set by WdgM_SetMode */
  boolean WdgM_EB_MainFunctionActive; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable22,1 */
  /**< WdgM internal flag for indicating an active MainFunction execution */
#if (WDGM_EB_CHECK_MAINFUNCTION_TIMING == STD_ON)
  VAR(WdgM_EB_TimestampType, WDGM_VAR) WdgM_EB_MainFunctionTimeStamp; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable23,1 */
  /**< TimeStamp of the last WdgM MainFunction call */
#endif
  CONST(WdgM_EB_CoreIdType, WDGM_VAR) CoreID;
  /**< Core ID where the CoreInstance belongs to */
#if (WDGM_PARTITION_RESET == STD_ON)
  CONST(ApplicationType, WDGM_VAR) NumOsPartitions;
  /**< Number of Os Partitions mapped to this Core ID */
  CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) WdgM_EB_PartitionSupervisionCycleCntPtr; /* !LINKSTO WDGM.EB.DesignDecision.InternalVariable30,1 */
  /**< WdgM internal counter for supervision cycles mapped to WdgM partitions */
#endif
}WdgM_EB_CoreContextType;

/*==================[external function declarations]=============================================*/

/*==================[external constants]=========================================================*/

#define WDGM_START_SEC_CONST_ASIL_D_8
#include <WdgM_MemMap.h>

/** \brief configured initial mode id */
extern CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_InitialModeId;

#if (WDGM_EB_DEINIT_MODE_ENABLED == STD_ON)
/** \brief configured de-init mode id */
extern CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_DeInitModeId;
#endif

/** \brief array size of configuration data for a WdgMMode */
extern CONST(WdgM_ModeType,WDGM_CONST) WdgM_EB_ModeCfgSize;

/** \brief array of mapping SEId to SE internal ID */
extern CONST(WdgM_EB_SEIdType, WDGM_CONST) WdgM_EB_SEIntSEId[WDGM_EB_SE_NUM];

/** \brief array of mapping SE internal ID to local Core Idx*/
extern CONST(WdgM_EB_SEIdType, WDGM_CONST) WdgM_EB_SELocalCoreIdx[WDGM_EB_SE_NUM];

#define WDGM_STOP_SEC_CONST_ASIL_D_8
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

/** \brief array of configuration data for a SE */
extern CONST(WdgM_EB_SECfgType,WDGM_CONST) WdgM_EB_SECfg[WDGM_EB_SE_NUM];

/** \brief array of configuration data for a WdgMMode */
extern CONST(WdgM_EB_ModeCfgType,WDGM_CONST) WdgM_EB_ModeCfg[WDGM_EB_MODE_NUM];

#define WDGM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include <WdgM_MemMap.h>

#define WDGM_START_SEC_CONST_ASIL_D_16
#include <WdgM_MemMap.h>

#if (WDGM_EB_CALLERIDS_ENABLED == STD_ON)
/** \brief List of configured caller IDs */
extern CONST(uint16, WDGM_CONST) WdgM_EB_CallerIds[WDGM_EB_CALLERIDS_NUM];
#endif

#define WDGM_STOP_SEC_CONST_ASIL_D_16
#include <WdgM_MemMap.h>

/*==================[external data]==============================================================*/

/* !LINKSTO WDGM.EB.TIMEPM.WDGM020304,2 */
#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
#define WDGM_START_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#else
#define WDGM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif


/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable4,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable11,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable9,1 */
/* !LINKSTO WDGM.EB.DesignDecision.InternalVariable24,1 */
#if (WDGM_EB_DEADLINE_SUPERVISION_ENABLED == STD_ON)
#if (WDGM_EB_DM_NUM > 0)
extern VAR(WdgM_EB_DMDataType,WDGM_VAR) WdgM_EB_DMData[WDGM_EB_DM_NUM];
#else
extern VAR(WdgM_EB_DMDataType,WDGM_VAR) WdgM_EB_DMData[1];
#endif
#endif

#if (WDGM_EB_PARTITIONING_ENABLED == STD_ON)
#define WDGM_STOP_SEC_VAR_CLEARED_SHARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#else
#define WDGM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <WdgM_MemMap.h>
#endif

#endif /* ifndef WDGM_BSW_LCFG_H */
/*==================[end of file]================================================================*/
