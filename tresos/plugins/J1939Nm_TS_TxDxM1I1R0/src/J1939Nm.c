/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 9.3 (required)
 *  Arrays shall not be partially initialized.
 *
 *  Reason: False positive, The initialization is done according to misra guidelines.
 */

/*  tasking Deviation List
 *
 *  TASKING-1) Deviated Rule: W549
 *  W549: condition is always true
 *
 *  Reason: False-positive from the Tasking v5.0r2 compiler (TCVX-41885)
 */

/*==================[inclusions]============================================*/
#include <J1939Nm.h>
#include <TSAutosar.h>        /* Specific standard types */
#include <J1939Nm_Cbk.h>
#include <NmStack_Types.h>
#include <Nm_Cbk.h>
#include <CanIf.h>
#include <J1939Nm_Trace.h>                        /* Dbg related macros for J1939Nm */
#include <BswM_J1939Nm.h>

#include <SchM_J1939Nm.h>      /* For exclusive area protection */

#if ( J1939NM_DEV_ERROR_DETECT == STD_ON )
/* For DET error detection */
#include <Det.h>
#endif

#if(J1939NM_DEM_ENABLED == STD_ON)
 #include <Dem.h> /* For Dem implementation */
#endif

/* Version check */

/*for MemCopy_MemCopy */
#include <TSMem.h>

#if (J1939NM_USER_CALLOUT == STD_ON )
/* For J1939NmUserCallout Indication */
#include <J1939Nm_Externals.h>
#endif
/*======================================================*/
/* Definition of ROM constants                          */
/*======================================================*/
#define J1939NM_PGN_BYTE0            (0x00u)
#define J1939NM_PGN_BYTE1            (0xEEu)
#define J1939NM_PGN_BYTE2            (0x00u)
#define FlagArray_SIZE               (0x02u)   /*to store the calling of J1939Nm_NetworkRelease and  the corresponding nmChannelHandle */
#define NMCHANNELHANDLE              (0x01u)   /*to store the the corresponding nmChannelHandle */
#define NetworkRelease_Channel       (0x00u)   /*to store the calling of J1939Nm_NetworkRelease */
#define NetworkRelease_Called        (0x01u)
#define NetworkRelease_NotCalled     (0x00u)


/*  Size of the Node Name **/
#define J1939NM_NODE_NAME_SIZE            (8u)

/*  Fixed size (in bytes) of the Node Preferred Address **/
#define J1939NM_NODE_PREF_ADDRESS_SIZE    (1u)

/*  Fixed size (in bytes) of a PGN **/
#define J1939NM_PGN_SIZE                  (3u)

/*  Fixed size (in bytes) of the MetaData **/
#define J1939NM_METADATA_LENGTH           (uint8)(J1939NM_NODE_PREF_ADDRESS_SIZE + J1939NM_PGN_SIZE)   /* For J1939Nm, MetaData = Node Preferred Address + PGN */

/*indexes of meta data in the MetaData_Information*/
#define SOURCE_ADD_INDEX    0U


/*  NULL Source address **/
#define J1939NM_NULL_ADDRESS              (0xFE)

/*  PGN for J1939Nm **/
#define J1939NM_PGN                       (0x00EE00)

#define J1939NM_START_SEC_CONST_8
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_CONST_8
#include <J1939Nm_MemMap.h>

/*  Structure position for delay seed (MSB of Name)**/
#define NAME_POS                        (7u)

/*  Structure position for preffered address **/
#define ADDRESS_POS                     (8u)
/*======================================================*/
/* Definition of RAM variables                          */
/*======================================================*/
#define J1939NM_START_SEC_VAR_CLEARED_16
#include <J1939Nm_MemMap.h>
/* global counter for the delay timer */
static VAR(uint16,J1939NM_VAR) J1939Nm_DelayCtr[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
#define J1939NM_STOP_SEC_VAR_CLEARED_16
#include <J1939Nm_MemMap.h>


/*---------------------------------------*/
/* initialized and cleared RAM (default) */
/*---------------------------------------*/

#define J1939NM_START_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>
VAR(uint8, J1939NM_VAR) J1939Nm_PendingNode;
VAR(uint8, J1939NM_VAR) J1939Nm_PendingChannel;
static VAR(uint8, J1939NM_VAR) J1939Nm_NetworkRelease_FlagArray[J1939NM_NUMBER_OF_CHANNELS_MAX][FlagArray_SIZE]; /*for each J1939Nm channel,this flag is set if J1939Nm_NetworkRelease function is called and the corresponding nmChannelHandle is stored*/
static VAR(uint8, J1939NM_VAR) J1939Nm_NmChannelState[J1939NM_NUMBER_OF_CHANNELS_MAX];
/* Frame which will be transmitted after a no transmission pending. */
/* !LINKSTO J1939Nm.SWS_J1939Nm_00018,1 */
static VAR(uint8, J1939NM_VAR) Txbuffer[(uint8)J1939NM_NUMBER_OF_NODES_MAX][(uint8)J1939NM_NODE_NAME_SIZE];
static VAR(uint8, J1939NM_VAR) MetaData_Information[(uint8)J1939NM_NUMBER_OF_NODES_MAX];

static VAR(uint8, J1939NM_VAR) BusoffRandomDelay[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];

static VAR(uint8, J1939NM_VAR) J1939Nm_TransmissionPending = {J1939NM_NO_TRANSMISSION_PENDING};
#define J1939NM_STOP_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Nm_MemMap.h>

static P2CONST( J1939Nm_ConfigType, J1939NM_VAR, J1939NM_APPL_CONST )
  J1939Nm_ConfigPtr ;

#define J1939NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>
#define J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>

VAR(boolean, J1939NM_VAR) J1939Nm_ProcessPendingRequestFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
VAR(boolean, J1939NM_VAR) J1939Nm_StartDelayFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
VAR(boolean, J1939NM_VAR) J1939Nm_ACLostFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];

#define J1939NM_STOP_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>

/*---------------------------------------*/
/* non initialized RAM                   */
/*---------------------------------------*/

/* UNKNOWN SIZE */
#define J1939NM_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>
static J1939Nm_ChannelNodeInfoType J1939NmChannelNodeInfoArr [J1939NM_NUMBER_OF_CHANNELS_MAX] ;
VAR(J1939Nm_StateType, J1939NM_VAR) J1939Nm_InitState = { J1939NM_UNINIT };
#define J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>


/*======================================================*/
/* close variable declaration sections                  */
/*======================================================*/

#define J1939NM_START_SEC_CODE
#include <J1939Nm_MemMap.h>
/* Private functions prototypes */
static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkHandleValidator(VAR(NetworkHandleType, AUTOMATIC)
 NetworkHandle, P2VAR(NetworkHandleType, AUTOMATIC, J1939NM_APPL_DATA) InternalNmChannelID);

static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_AddressClaimed_Transmit(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels
);

static FUNC(void, J1939NM_CODE) J1939Nm_RequestIndication_BroadCast(
  VAR(NetworkHandleType, AUTOMATIC) internalChannelID,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr
);

static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_DelayStart(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr
);


static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_NormalOp(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels
);

static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_ACLost(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_SleepCnt
);

static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_DetValidityCheck(
  VAR(Std_ReturnType, AUTOMATIC) validRxPduID,
  VAR(Std_ReturnType, AUTOMATIC) validPrefAddress,
  VAR(Std_ReturnType, AUTOMATIC) validNodeId
);

static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NodeId_PrefAddress_ValidityCheck(
  VAR(uint8, AUTOMATIC) SA,
  P2VAR(Std_ReturnType, AUTOMATIC, J1939NM_APPL_DATA) validPrefAddress,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_Node,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_NodeID,
  VAR(uint8, AUTOMATIC) lub_Channel,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_NodeChannel
);

static FUNC(void, J1939NM_CODE) J1939Nm_HandlePendingTransmission(uint8 Node,uint8 Chid);

/* ************************************************************
 *  Name                 :  J1939Nm_SetCanId
 *  Description          :  Each BSW Module needs to initialize internal
 *  variables and hardware resources in a separate initialization function
 *  Parameters           :  [Input: uint8 SA] [Input: EcuC_PduIdType PduId)] [Input: uint8 ApiId_DET)]
 *  Return               :  Std_ReturnType
 *  Critical/explanation :  [No]
 **************************************************************/
static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetCanId(
  VAR(uint8, AUTOMATIC) SA,
  VAR(EcuC_PduIdType, AUTOMATIC) PduId,
  P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_CONST) PduInfoPtr,
  VAR(uint8, AUTOMATIC) ApiId_DET)
{
  uint32 CanId32;
  Std_ReturnType SetMetaDataResult_Local;
  static VAR(PduInfoType, J1939NM_VAR) Dummy_PduInfo;
  static P2VAR(PduInfoType, AUTOMATIC, J1939NM_VAR) Dummy_PduInfoPtr = &Dummy_PduInfo;
  TS_PARAM_UNUSED(PduInfoPtr);

    /* !LINKSTO J1939Nm.SWS_J1939Nm_00073,1*/
    CanId32 = ((uint32)J1939NM_PGN_BYTE2 << 24);
    CanId32 |= ((uint32)J1939NM_PGN_BYTE1 << 16);
    CanId32 |= ((uint32)J1939NM_PGN_BYTE0 << 8);
    CanId32 |= ((uint32)SA);

  SetMetaDataResult_Local = EcuC_SetMetaDataCanId(PduId, Dummy_PduInfoPtr ,CanId32);
  if(SetMetaDataResult_Local != E_OK)
  {
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.EB.Invalid_MetaData,1 */
      (void)Det_ReportError( (uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, (uint8)ApiId_DET, (uint8)J1939NM_E_INVALID_METADATA_HANDLE);
#endif
  }

return SetMetaDataResult_Local;
}

/* ---------------------------- */
/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */

FUNC( Std_ReturnType, J1939NM_CODE) J1939Nm_IsValidConfig
(
  P2CONST(void,AUTOMATIC,J1939NM_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(J1939Nm_ConfigType,AUTOMATIC,J1939NM_APPL_CONST) ConfigPtr = voidConfigPtr;

    /* Check if the configuration fits to the platform */
    if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
    {
      /* Validate the post build configuration against the compile time configuration */
      if (J1939NM_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if (J1939Nm_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the post build configuration against the compile time published information
             configuration */
          if (J1939NM_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
          {
            /* Indicate that the configuration is valid */
            RetVal = E_OK;
          }
        }
      }
    }

  return RetVal;
}

/* Exported functions */
/* ------------------ */

/* ************************************************************
 *  Name                 :  J1939Nm_Init
 *  Description          :  Each BSW Module needs to initialize internal
 *  variables and hardware resources in a separate initialization function
 *  Parameters           :  [Input: pointer to config struct]
 *  Return               :  void
 *  Critical/explanation :  [No]
 **************************************************************/
/* !LINKSTO J1939Nm.SWS_J1939Nm_00031,1 */
FUNC(void, J1939NM_CODE) J1939Nm_Init(P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_APPL_CONST) configPtr)
{
  /*to loop on each Node */
  VAR(uint8, AUTOMATIC) lub_Node;
  /*to loop on each Channel */
  VAR(uint8, AUTOMATIC) lub_Channel;
  VAR(uint8, AUTOMATIC) lub_NodeChannel;
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lps_CanIfTransmissionState;

  P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_APPL_CONST) LocalConfigPtr = configPtr;

  /* Save the configuration pointer */
#if (J1939NM_PBCFGM_SUPPORT_ENABLED == STD_ON)
  /* If the initialization function is called with an null pointer get the configuration from the
   * post build configuration manager */
  if (LocalConfigPtr == NULL_PTR)
  {
    PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
    if (E_OK == PbcfgM_GetConfig( J1939NM_MODULE_ID,
                                  J1939NM_INSTANCE_ID,
                                  &ModuleConfig)
                                )
    {
      LocalConfigPtr = (P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_APPL_CONST)) ModuleConfig;
    }
  }
#endif /* J1939NM_PBCFGM_SUPPORT_ENABLED == STD_ON */

#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* check whether parameter LocalConfigPtr is a NULL_PTR or invalid*/
  if (LocalConfigPtr == NULL_PTR)
  {
    /* found a NULL_PTR, report to DET */
    (void) Det_ReportError( J1939NM_MODULE_ID,
                            J1939NM_INSTANCE_ID,
                            J1939NM_API_ID_INIT,
                            J1939NM_E_INIT_FAILED
                          );
  }
  else
#endif /* J1939NM_DEV_ERROR_DETECT */
  {
    if ( E_OK != J1939Nm_IsValidConfig(LocalConfigPtr))
    {
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* check that configuration pointer is valid */
      (void) Det_ReportError( J1939NM_MODULE_ID,
                              J1939NM_INSTANCE_ID,
                              J1939NM_API_ID_INIT,
                              J1939NM_E_PARAM_POINTER
                            );
#endif /* J1939NM_DEV_ERROR_DETECT */
    }
    else
    {
      /*Set Global Initialize Post build Configuration pointer */
      J1939Nm_ConfigPtr = LocalConfigPtr;

      /*if the J1939Nm module is already initialized */
      if (J1939Nm_InitState == J1939NM_INIT)
      {
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO J1939Nm.SWS_J1939Nm_00005,1*/
            /* !LINKSTO J1939Nm.SWS_J1939Nm_00041,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.2,1 */
            (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_INIT, J1939NM_E_REINIT);
#endif
      }
      else
      {
        /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.Init,1 */
        lps_CanIfTransmissionState = &J1939Nm_TransmissionPending;
        *lps_CanIfTransmissionState = J1939NM_NO_TRANSMISSION_PENDING;

        /* !LINKSTO EB_Ref.SWS_J1939Nm_00002.1,1 */
        for (lub_Channel = 0u; lub_Channel < (uint8) J1939NM_NUMBER_OF_CHANNELS; lub_Channel++)
        {
          J1939Nm_NetworkRelease_FlagArray[lub_Channel][NetworkRelease_Channel] = NetworkRelease_NotCalled;
          J1939Nm_NetworkRelease_FlagArray[lub_Channel][NMCHANNELHANDLE] = 0;
          J1939Nm_NmChannelState[lub_Channel] = DEFAULT_CHANGE_STATE;

          /* !LINKSTO J1939Nm.SWS_J1939Nm_00007,1 */
          for (lub_NodeChannel = 0u; lub_NodeChannel < J1939Nm_GetNumbOfNodeInChannel(lub_Channel); lub_NodeChannel++)
          {
            J1939NmChannelNodeInfoArr[lub_Channel].NodeChannel[lub_NodeChannel].NodeChannelMode = NM_MODE_BUS_SLEEP;
            J1939NmChannelNodeInfoArr[lub_Channel].NodeChannel[lub_NodeChannel].NodeChannelNetworkModeState = NM_STATE_BUS_SLEEP;
            J1939NmChannelNodeInfoArr[lub_Channel].NodeChannel[lub_NodeChannel].NodeChannelOfflineSubState = J1939NM_OFFLINE_CLAIMING;
          }

          for (lub_Node = 0u; lub_Node < (uint8) J1939NM_NUMBER_OF_NODES; lub_Node++)
          {
            J1939Nm_DelayCtr[lub_Channel][lub_Node] = DEFAULT_CHANGE_STATE;
            BusoffRandomDelay[lub_Channel][lub_Node] = DEFAULT_CHANGE_STATE;
            J1939Nm_ProcessPendingRequestFlag[lub_Channel][lub_Node] = DEFAULT_CHANGE_STATE;
            J1939Nm_StartDelayFlag[lub_Channel][lub_Node] = DEFAULT_CHANGE_STATE;
            J1939Nm_ACLostFlag[lub_Channel][lub_Node] = DEFAULT_CHANGE_STATE;
          }
        }

        J1939Nm_PendingNode = 0u;
        J1939Nm_PendingChannel = 0u;

        /* !LINKSTO EB_Ref.SWS_J1939Nm_00002.2,1 */
        J1939Nm_InitState = J1939NM_INIT;
      }
    }
  }
}


/* ************************************************************
 *  Name                 :  J1939Nm_DeInit
 *  Description          :  This function resets the J1939 Network Management
 *              module to the uninitialized state.
 *  Parameters           :  void
 *  Return               :  void
 *  Critical/explanation :  [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00032,1 */
FUNC(void, J1939NM_CODE) J1939Nm_DeInit(void)
{
  /* if the J1939Nm module is not initialized */
  if(J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.EB.DET.DEINIT,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_DEINIT, J1939NM_E_UNINIT);
    #endif
  }
  else
  {
    /* !LINKSTO J1939Nm.SWS_J1939Nm_00003,1 */
    J1939Nm_InitState = J1939NM_UNINIT;
  }
}

#if ( J1939NM_VERSION_INFO_API == STD_ON ) /*API enabled */
/* ************************************************************
 *  Name                 : J1939Nm_GetVersionInfo
 *  Description          : Each BSW module shall provide a function
 *  to read out the version information of the dedicated module implementation
 *  Parameters           : Input / output: Std_VersionInfoType *versioninfo
 *  Return               : void
 *  Critical/explanation : [yes / No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00033,1 */
FUNC(void, J1939NM_CODE) J1939Nm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939NM_APPL_DATA) versioninfo)
{
  if(versioninfo == NULL_PTR)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.4,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETVERSIONINFO, J1939NM_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* Copy Vendor ID */
    versioninfo->vendorID = J1939NM_VENDOR_ID;
    /* Copy Module identifier */
    versioninfo->moduleID = J1939NM_MODULE_ID;
    /* Copy Vendor SW major version number */
    versioninfo->sw_major_version = (uint8)J1939NM_SW_MAJOR_VERSION;
    /* Copy Vendor SW minor version number */
    versioninfo->sw_minor_version = (uint8)J1939NM_SW_MINOR_VERSION;
    /* Copy Vendor SW patch level version number */
    versioninfo->sw_patch_version = (uint8)J1939NM_SW_PATCH_VERSION;
  }
}
#endif

/* ************************************************************
 *  Name                 : J1939Nm_NetworkRequest
 *  Description          : Requests the network, since ECU needs
 *               to communicate on the bus
 *  Parameters           : Input: NetworkHandleType nmChannelHandle
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00044,1 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRequest(VAR(NetworkHandleType, AUTOMATIC) nmChannelHandle)
{
  /*The return value */
  VAR(uint8, AUTOMATIC) ret_val = (Std_ReturnType) E_OK;
  /*to loop on each node */
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr;
  /*to loop on each node */
  VAR(uint8, AUTOMATIC) lub_Nodes;
  /*Index used for Arrays */
  VAR(uint8, AUTOMATIC) lub_IndexTmp;
  /*The return value of Address Claimed Transmit*/
  VAR(uint8, AUTOMATIC) ret_val_AddrClaimed = (Std_ReturnType) E_NOT_OK;
#if(J1939NM_DEM_ENABLED == STD_ON)
  /*Index used for Dem Events */
  VAR(uint8, AUTOMATIC) lub_DemEventIndex;
#endif
  /*To obtain channel */
  VAR(NetworkHandleType, AUTOMATIC) internalChannelID;
  P2VAR(J1939Nm_ChannelNodeInfoType, AUTOMATIC, J1939NM_APPL_DATA) lps_ChannelConfig;
  CONST(Std_ReturnType, J1939NM_CONST) validNetworkHandleId = J1939Nm_NetworkHandleValidator(nmChannelHandle, &internalChannelID);

  /*if the J1939Nm module is not initialized */
  if (J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.EB.DET.NETWORK_REQUEST,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_NETWORKREQUEST, J1939NM_E_UNINIT);
    #endif
    /*return an error code */
    ret_val = (Std_ReturnType) E_NOT_OK;
  }

  /*if the NetworkHandle parameter is invalid */
  else if (validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.6,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_NETWORKREQUEST, J1939NM_E_INVALID_NETWORK_ID);
    /*return an error code */
    #endif
    ret_val = (Std_ReturnType) E_NOT_OK;
  }
  else
  {
    /*clear the flag of J1939Nm_NetworkRelease in case J1939Nm_NetworkRequest was called before main function*/
    J1939Nm_NetworkRelease_FlagArray[internalChannelID][NetworkRelease_Channel] = NetworkRelease_NotCalled;

    lps_ChannelConfig = &J1939NmChannelNodeInfoArr[internalChannelID];
    for (lub_NodeChannelCtr = 0u; lub_NodeChannelCtr < J1939Nm_GetNumbOfNodeInChannel(internalChannelID); lub_NodeChannelCtr++)
    {
      boolean flag = FALSE;
      SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

      /* !LINKSTO EB_Ref.SWS_J1939Nm_00009.1,1 */
      lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelMode = NM_MODE_NETWORK;

      SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
      lub_Nodes = 0;
      /* Deviation TASKING-1 */
      while(FALSE == flag)
      {
        if (J1939NM_GetNodeID(lub_Nodes) == J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr))
        {
          /* !LINKSTO EB_Ref.SWS_J1939Nm_00009.3,1 */
          /*Trigger a transmission of an address calimed PG for each node channel */
          if (TRUE == J1939Nm_GetAddressArbitration(internalChannelID))
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            /*Name */
            for (lub_IndexTmp = 0u; lub_IndexTmp < (uint8) J1939NM_NODE_NAME_SIZE; lub_IndexTmp++)
            {
              Txbuffer[lub_Nodes][lub_IndexTmp] = J1939Nm_GetNodeName(lub_Nodes)[lub_IndexTmp];
            }

            /*Node Preferred Address */
            MetaData_Information[lub_Nodes] = J1939Nm_GetNodePreferedAddress(lub_Nodes);

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            /* !LINKSTO J1939Nm.SWS_J1939Nm_00016,1 */
            if (J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
            {
              ret_val_AddrClaimed = J1939Nm_AddressClaimed_Transmit(lub_Nodes,internalChannelID);
              if(E_OK == ret_val_AddrClaimed)
              {
                SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
                /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.TxPending,1 */
                J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
                SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
              }
              else
              {
                SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
                /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.TxAbort,1 */
                J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
                SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
              }
              /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
              SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
              J1939Nm_PendingChannel = internalChannelID;
              /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
              J1939Nm_PendingNode = lub_Nodes;
              SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
            }
            else
            {
              /* !LINKSTO J1939Nm.SWS_J1939Nm_00017,1 */
              /*Due not yet called "J1939Nm_TxConfirmation" to set "J1939Nm_TransmissionPending = J1939NM_NO_TRANSMISSION_PENDING" */
              /*Due J1939Nm_TxConfirmation needs this pdu for its own call, and there won't be the indexes of "internalChannelID" nor "lub_NodeChannelCtr", an extra buffer with this specific value should be assigned. */
              SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

              J1939Nm_ProcessPendingRequestFlag[internalChannelID][lub_Nodes] = (boolean) TRUE;

              SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
            }
          }


          if (J1939Nm_GetNodeStartupDelay(lub_Nodes) == (boolean) TRUE)
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            /* !LINKSTO EB_Ref.SWS_J1939Nm_00010.1,1 */
            /* Deviation TASKING-1 <1> */
            lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState = NM_STATE_OFFLINE;
            lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState = J1939NM_OFFLINE_CLAIMING;

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.1,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Nm_00010.2,1 */
            /* Deviation TASKING-1 <1> */
            BswM_J1939Nm_StateChangeNotification(nmChannelHandle, J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr), NM_STATE_OFFLINE);

          }
          else /*J1939Nm_PsConfig->J1939Nm_NodeDescriptor[lub_Nodes].StartUpDelay == FALSE */
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            /* !LINKSTO EB_Ref.SWS_J1939Nm_00011.1,1 */
            lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState = NM_STATE_NORMAL_OPERATION;

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

            if (J1939Nm_NmChannelState[internalChannelID] == FALSE)
            {
              /* !LINKSTO J1939Nm.SWS_J1939Nm_00064,1*/
              /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.6,1*/
              /*SWS_Nm_00165,1*/
              /* Deviation TASKING-1 <1> */
              Nm_StateChangeNotification(nmChannelHandle, NM_STATE_OFFLINE, NM_STATE_NORMAL_OPERATION);

              SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();

              J1939Nm_NmChannelState[internalChannelID] = TRUE;

              SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_REQUEST();
            }

            /* !LINKSTO EB_Ref.SWS_J1939Nm_00011.2,1 */
            BswM_J1939Nm_StateChangeNotification(nmChannelHandle, J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr), NM_STATE_NORMAL_OPERATION);
#if(J1939NM_DEM_ENABLED == STD_ON)
            if(J1939Nm_GetNumbOfDemEvent(internalChannelID) > 0U)
            {
              for(lub_DemEventIndex=0; lub_DemEventIndex < J1939Nm_GetNumbOfDemEvent(internalChannelID); lub_DemEventIndex++)
              {
                if(J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr) == J1939Nm_GetNodeIdInDemEvent(internalChannelID,lub_DemEventIndex))
                {
                  /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.ASR_42.Dem_Reporting,1 */
                  (void)Dem_ReportErrorStatus((Dem_EventIdType)J1939Nm_GetDemEventId(internalChannelID,lub_DemEventIndex), (Dem_EventStatusType)DEM_EVENT_STATUS_PREPASSED);
                }
              }
            }
#endif
          }

          flag = TRUE;
        }
        lub_Nodes++;
      }
    }

    /* !LINKSTO EB_Ref.SWS_J1939Nm_00009.2,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.4,1 */
    Nm_NetworkMode(nmChannelHandle);

    if (J1939Nm_NmChannelState[internalChannelID] == FALSE)
    {
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00066,1*/
      /*If the last NodeChannel has changed its state to "Offline"*/
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00063,1 */
      /*SWS_Nm_00165,1*/
      /* Deviation TASKING-1 <1> */
      Nm_StateChangeNotification(nmChannelHandle, NM_STATE_NORMAL_OPERATION, NM_STATE_OFFLINE);
    }
  }

  /*return */
  return ret_val;
}

/* ************************************************************
 *  Name                 : J1939Nm_NetworkRelease
 *  Description          : Releases the network, since ECU doesn't
 *               have to communicate on the bus
 *  Parameters           : Input: NetworkHandleType nmChannelHandle
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Sync/Async           : Asynchronous
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00045,1 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRelease(VAR(NetworkHandleType, AUTOMATIC) nmChannelHandle)
{
  /* The return value */
  VAR(uint8, AUTOMATIC) ret_val = (Std_ReturnType) E_OK;

  VAR(Std_ReturnType, AUTOMATIC) validNetworkHandleId = (Std_ReturnType) E_NOT_OK;
  /* To obtain channel */
  VAR(NetworkHandleType, AUTOMATIC) internalChannelID;


  validNetworkHandleId = J1939Nm_NetworkHandleValidator(nmChannelHandle, &internalChannelID);

    /* if the J1939Nm module is not initialized */
    if(J1939Nm_InitState == J1939NM_UNINIT)
    {
        #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Nm.EB.DET.NETWORK_RELEASE,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
        (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_NETWORKRELEASE,
          J1939NM_E_UNINIT);
        #endif
        /* return an error code */
        ret_val = (Std_ReturnType)E_NOT_OK;
    }
    /* if the NetworkHandle parameter is invalid */
    else if(validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
    {
        #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.6,1 */
        (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_NETWORKRELEASE,
          J1939NM_E_INVALID_NETWORK_ID);
        #endif
        /* return an error code */
        ret_val = (Std_ReturnType) E_NOT_OK;
    }
    else
    {
        J1939Nm_NetworkRelease_FlagArray[internalChannelID][NetworkRelease_Channel] = NetworkRelease_Called;
        J1939Nm_NetworkRelease_FlagArray[internalChannelID][NMCHANNELHANDLE] = nmChannelHandle;


    }

    /* return */
    return ret_val;
}

/* ************************************************************
 *  Name                 : J1939Nm_GetState
 *  Description          : Returns the state and the mode of the network management.
 *  Parameters           : Input:  NetworkHandleType NetworkHandle
 *             : Output: Nm_StateType* const nmStatePtr
 *             : Output: Nm_ModeType* const nmModePtr
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00052,1 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetState(
  VAR(NetworkHandleType, J1939NM_VAR) NetworkHandle,
  P2VAR(Nm_StateType, AUTOMATIC, J1939NM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, J1939NM_APPL_DATA) nmModePtr
)
{
  /* The return value */
  VAR(uint8, AUTOMATIC) ret_val = (Std_ReturnType)E_OK;
  /* Internal ID reference for Nm channels */
  VAR(NetworkHandleType, AUTOMATIC) ChannelID_internal = 0u;

  VAR(Std_ReturnType, AUTOMATIC) validNetworkHandleId = (Std_ReturnType) E_NOT_OK;
  validNetworkHandleId = J1939Nm_NetworkHandleValidator(NetworkHandle, &ChannelID_internal);

  /* if the J1939Nm module is not initialized */
  if(J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.EB.DET.GET_STATE,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETSTATE, J1939NM_E_UNINIT);
    #endif
    /* return an error code */
    ret_val = (Std_ReturnType)E_NOT_OK;
  }
  /* if the NetworkHandle parameter is invalid */
  else if(validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.6,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETSTATE, J1939NM_E_INVALID_NETWORK_ID);
    #endif
    /* return an error code */
    ret_val = (Std_ReturnType)E_NOT_OK;
  }
  else if((nmStatePtr == NULL_PTR) || (nmModePtr == NULL_PTR))
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.4,1 */
    /* reporting DET error(J1939NM_E_PARAM_POINTER) for when a NULL pointer is provided (4.2.2 in the section 7.8) */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETSTATE, J1939NM_E_PARAM_POINTER);
    #endif
    /* return an error code */
    ret_val = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* Obtains the first nodechannel, due it has the same mode and state for all the nodechannels in the channel */
    *nmStatePtr = ((Nm_StateType)(J1939NmChannelNodeInfoArr[ChannelID_internal].NodeChannel[0].NodeChannelNetworkModeState));
    *nmModePtr = ((Nm_ModeType)(J1939NmChannelNodeInfoArr[ChannelID_internal].NodeChannel[0].NodeChannelMode));
  }
  /* return */
  return ret_val;
}

/* ************************************************************
 *  Name                 : J1939Nm_GetBusOffDelay
 *  Description          : This callout function returns the number of CanSM base
 *               cycles to wait additionally to L1/L2 after a BusOff occurred.
 *  Parameters           : Input: const NetworkHandleType network
 *             : Output: uint8* const delayCyclesPtr
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00070,1 */
FUNC(void, J1939NM_CODE) J1939Nm_GetBusOffDelay(VAR(NetworkHandleType, AUTOMATIC) network,
                         P2VAR(uint8, AUTOMATIC,J1939NM_APPL_DATA) delayCyclesPtr)
{
  /* Generic counter variable */
  VAR(uint8, AUTOMATIC) lub_Ctr_i;
  /* Generic counter variable */
  VAR(uint8, AUTOMATIC) lub_Ctr_j;
  /* Internal ID reference for Nm channels */
  VAR(NetworkHandleType, AUTOMATIC) ChannelID_internal = 0u;

  VAR(Std_ReturnType, AUTOMATIC) validNetworkHandleId = (Std_ReturnType) E_NOT_OK;

  validNetworkHandleId = J1939Nm_NetworkHandleValidator(network, &ChannelID_internal);

  /* if the J1939Nm module is not initialized */
  if(J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.EB.DET.BUS_OFF_DELAY,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETBUSOFFDELAY, J1939NM_E_UNINIT);
    #endif
  }
  /* if the NetworkHandle parameter is invalid */
  else if(validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.6,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETBUSOFFDELAY, J1939NM_E_INVALID_NETWORK_ID);
    #endif
  }
  else if(delayCyclesPtr == NULL_PTR)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.4,1 */
    /* reporting DET error(J1939NM_E_PARAM_POINTER) for when a NULL pointer is provided (4.2.2 in the section 7.8) */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_GETBUSOFFDELAY, J1939NM_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* EB_Ref.SWS_J1939Nm_00068.1,1 */
    /* J1939Nm.SWS_J1939Nm_00069,1 */
    for (lub_Ctr_i = 0u; lub_Ctr_i < J1939Nm_GetNumbOfNodeInChannel(ChannelID_internal); lub_Ctr_i++)
    {
      boolean flag = FALSE;
      lub_Ctr_j = 0;
      /* Deviation TASKING-1 */
      while(FALSE == flag)
      {
        if(J1939NM_GetNodeID(lub_Ctr_j) == J1939NM_GetNodeIDInChannel(ChannelID_internal,lub_Ctr_i))
        {
          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_GETBUSOFF_DELAY();

          /* EB_Ref.SWS_J1939Nm_00068.3,1 */
          *delayCyclesPtr = ((uint8) J1939Nm_GetNodeName(lub_Ctr_j)[NAME_POS])*((uint8) J1939NM_DELAY_TICK_PERIOD);

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_GETBUSOFF_DELAY();
          flag = TRUE;
        }
        lub_Ctr_j++;
      }
    }
  }
}

/* ************************************************************
 *  Name                 : J1939Nm_PassiveStartUp
 *  Description          : Passive startup of the NM. It triggers the
 *                         transition from Bus-Sleep Mode to the Network
 *                         Mode without requesting the network.
 *  Parameters           : Input: NetworkHandleType nmChannelHandle
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00054,1 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_PassiveStartUp(VAR(NetworkHandleType, J1939NM_VAR) nmChannelHandle)
{
    /* The return value */
    VAR(uint8, AUTOMATIC) ret_val = (Std_ReturnType)E_OK;
    VAR(Std_ReturnType, AUTOMATIC) validNetworkHandleId = (Std_ReturnType) E_NOT_OK;
    /* To obtain channel */
    VAR(NetworkHandleType, AUTOMATIC) internalChannelID;
    validNetworkHandleId = J1939Nm_NetworkHandleValidator(nmChannelHandle, &internalChannelID);
    /* if the J1939Nm module is not initialized */
    if(J1939Nm_InitState == J1939NM_UNINIT)
    {
        #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Nm.EB.DET.PASSIVE_STARTUP,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
        (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_PASSIVESTARTUP, J1939NM_E_UNINIT);
        #endif
        /* return an error code */
        ret_val = (Std_ReturnType)E_NOT_OK;
    }
    /* if the NetworkHandle parameter is invalid */
    else if(validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
    {
        #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
        (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_PASSIVESTARTUP,
          J1939NM_E_INVALID_NETWORK_ID);
        #endif
        /* return an error code */
        ret_val = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        ret_val = (Std_ReturnType)E_NOT_OK;
    }
    /* return */
    return ret_val;
}
/* ************************************************************
 *  Name                 : J1939Nm_RxIndication
 *  Description          : Indication of a received I-PDU from a lower
 *                         layer communication interface module.
 *  Parameters           : Input: PduIdType RxPduId
 *                       : Input: PduInfoType* PduInfoPtr
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
/* J1939Nm_SWS_J1939Nm_00036,1 */
FUNC(void, J1939NM_CODE) J1939Nm_RxIndication(
     VAR(PduIdType, AUTOMATIC) RxPduId,
     P2VAR(PduInfoType, AUTOMATIC,  J1939NM_APPL_DATA) PduInfoPtr)
{
  VAR(uint8, AUTOMATIC) lub_Channel = 0u;
  VAR(uint8, AUTOMATIC) lub_Node = 0u;
  VAR(uint8, AUTOMATIC) lub_NodeChannel = 0u;
  VAR(uint8, AUTOMATIC) lub_Ctr;
  VAR(uint8, AUTOMATIC) lub_NodeID = 0u;
  VAR(boolean, AUTOMATIC) lub_Arbitration = (boolean) FALSE;
  VAR(Std_ReturnType, AUTOMATIC) getMetaDataResult = (Std_ReturnType)0;
  VAR(uint8, AUTOMATIC) SA;
  VAR(uint32, AUTOMATIC) CanId;

  /*The return value of Address Claimed Transmit*/
  VAR(uint8, AUTOMATIC) ret_val_AddrClaimed = (Std_ReturnType) E_NOT_OK;
  VAR(Std_ReturnType, AUTOMATIC) validRxPduID = (Std_ReturnType)E_NOT_OK;
  VAR(Std_ReturnType, AUTOMATIC) validPrefAddress = (Std_ReturnType)E_NOT_OK;
  VAR(Std_ReturnType, AUTOMATIC) validNodeId = (Std_ReturnType)E_NOT_OK;

  VAR(uint8, AUTOMATIC) RandomDelay = 0;    /* Variable that gets the node ID value */

  /* reference to the Channel config structure */
  P2VAR(J1939Nm_ChannelNodeInfoType, AUTOMATIC, J1939NM_APPL_DATA) lps_ChannelConfig;

  P2VAR(uint32, AUTOMATIC, J1939NM_APPL_DATA) CanId_Ptr;
  CanId_Ptr = &CanId;

  if(J1939Nm_InitState == J1939NM_INIT)
  {
    if(PduInfoPtr != NULL_PTR)
    {
      for(lub_Ctr=0u; lub_Ctr < (uint8) J1939NM_NUMBER_OF_CHANNELS;lub_Ctr++)
      {
        if(RxPduId == J1939Nm_J1939RxPduIDs[lub_Ctr])
        {
          validRxPduID = (Std_ReturnType) E_OK;
          lub_Channel = lub_Ctr;
          break;
        }
      }
      getMetaDataResult = EcuC_GetMetaDataCanId( J1939Nm_GetRxEcucPduId(lub_Channel), PduInfoPtr , CanId_Ptr );

      /* !LINKSTO J1939Nm.SWS_J1939Nm_00074,1 */
      SA = (uint8)(CanId);

      if(getMetaDataResult != E_OK)
      {

#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO J1939Nm.EB.Invalid_MetaData,1 */
            (void)Det_ReportError( J1939NM_MODULE_ID, (uint8)0, J1939NM_API_ID_RXINDICATION, J1939NM_E_INVALID_METADATA_HANDLE);
#endif
      }

      validNodeId = J1939Nm_NodeId_PrefAddress_ValidityCheck(SA, &validPrefAddress ,&lub_Node, &lub_NodeID, lub_Channel, &lub_NodeChannel);

      /* !LINKSTO J1939Nm.SWS_J1939Nm_00059,1 */
#if (J1939NM_USER_CALLOUT == STD_ON)
      if( (validRxPduID == (Std_ReturnType) E_OK) && (PduInfoPtr->SduLength >= 8U) )
      {
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00060,1 */
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00028,1 */
        (*J1939NmCalloutFunctionPtr)( lub_Channel, SA, PduInfoPtr->SduDataPtr);
      }
#endif
    }
  }

  /* ------------------------------- */
  /* if the J1939Nm module is not initialized */
  if(J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.EB.DET.RX_INDICATION,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION, J1939NM_E_UNINIT);
    #endif
  }
  else if(PduInfoPtr == NULL_PTR)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.4,1 */
    /* reporting DET error(J1939NM_E_PARAM_POINTER) for when a NULL pointer is provided (4.2.2 in the section 7.8) */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION, J1939NM_E_PARAM_POINTER);
    #endif
  }
  else if(PduInfoPtr->SduLength < 8U)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* invalid pdu sdu length*/
    /* !LINKSTO J1939Nm.EB.Invalid_PduSduLength,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION, J1939NM_E_INVALID_PDU_SDULENGTH);
    #endif
  }
  else if(J1939Nm_DetValidityCheck(validRxPduID, validPrefAddress, validNodeId) == E_NOT_OK)
  {
    /*Drop the Frame. No action required */
  }
  else
  {

    if (TRUE == J1939Nm_GetAddressArbitration(lub_Channel))
    {
      /* If payload has a bigger value than the NAME of the Node, and the srcAddress is a valid one: */
      for(lub_Ctr=8u;((lub_Ctr>(uint8)0u) && (lub_Arbitration != (boolean) TRUE));)
      {
        lub_Ctr--;
        if(PduInfoPtr->SduDataPtr[lub_Ctr] > J1939Nm_GetNodeName(lub_Node)[lub_Ctr])
        {
          /* !LINKSTO J1939Nm.SWS_J1939Nm_00020,1 */
          /* ---------------- TRIGGER A TRANSMISSION OF AN ADDRESS CLAIMED PG FOR EACH NODECHANNEL ---------------------- */

          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
          /* Node Preferred Address */
          MetaData_Information[lub_Node] = J1939Nm_GetNodePreferedAddress(lub_Node);

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();

          /* !LINKSTO J1939Nm.SWS_J1939Nm_00016,1 */
          if(J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
          {
            ret_val_AddrClaimed = J1939Nm_AddressClaimed_Transmit(lub_Node, lub_Channel);
            if(E_OK == ret_val_AddrClaimed)
            {
              SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
              J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
              SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
            }
            else
            {
              SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
              J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
              SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
            }
            /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
            J1939Nm_PendingChannel = lub_Channel;
            /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
            J1939Nm_PendingNode = lub_Node;
            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
          }
          else
          {

            /* !LINKSTO J1939Nm.SWS_J1939Nm_00017,1 */
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();

            J1939Nm_ProcessPendingRequestFlag[lub_Channel][lub_Node] = (boolean) TRUE;

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();
          }

          lub_Arbitration = (boolean) TRUE;
        }
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00021,1 */
        /* If payload has a lower value than the MSB of the NAME of the Node, and the srcAddress is a valid one: */
        else if(PduInfoPtr->SduDataPtr[lub_Ctr]  < J1939Nm_GetNodeName(lub_Node)[lub_Ctr])
        {
          lps_ChannelConfig = J1939NmChannelNodeInfoArr;

          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();

          /* !LINKSTO EB_Ref.SWS_J1939Nm_00014.1,1 */
          /* Deviation TASKING-1 <1> */
          lps_ChannelConfig[lub_Channel].NodeChannel[lub_NodeChannel].NodeChannelNetworkModeState = NM_STATE_OFFLINE;
          lps_ChannelConfig[lub_Channel].NodeChannel[lub_NodeChannel].NodeChannelOfflineSubState = J1939NM_OFFLINE_ACLOST;

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();


          /* EB_Ref.SWS_J1939Nm_00068.1,1 */
          J1939Nm_GetBusOffDelay(lub_Channel, &RandomDelay);

          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();

          BusoffRandomDelay[lub_Channel][lub_Node] = RandomDelay;

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_RX_INDICATION();

          lub_Arbitration = (boolean) TRUE;
        }
        else
        {
          /* To Avoid MISRA Warning */
          /*No action taken care if its equal*/
        }
      }
    }
  }
}

/* ************************************************************
 *  Name                 : J1939Nm_TxConfirmation
 *  Description          : The lower layer communication interface module confirms
 *                         the transmission of a PDU, or the failure to transmit a PDU.
 *  Parameters           : Input: PduIdType TxPduID
 *  Parameters           : Input: Std_ReturnType result
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00037,1 */
FUNC(void, J1939NM_CODE) J1939Nm_TxConfirmation(VAR(PduIdType, AUTOMATIC) TxPduId, VAR(Std_ReturnType, AUTOMATIC) result)
{
  /*reference to the Scheduler manager descriptor structure */
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lps_CanIfTransmissionState;

  /*------------------------------- */
  VAR(uint8, AUTOMATIC) lub_ChannelCtr; /*Generic counter variable */
  VAR(Std_ReturnType, AUTOMATIC) validTxPduID = (Std_ReturnType) E_NOT_OK;

  /* ------------------------------- */
  /*if the J1939Nm module is not initialized */
  if (J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.EB.DET.TX_CONFIRMATION,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_TXCONFIRMATION, J1939NM_E_UNINIT);
    #endif
  }
  else
  {
    for (lub_ChannelCtr = 0u; lub_ChannelCtr < (uint8) J1939NM_NUMBER_OF_CHANNELS; lub_ChannelCtr++)
    {
      if (TxPduId == J1939Nm_J1939TxPduIDs[lub_ChannelCtr])
      {
        validTxPduID = (Std_ReturnType) E_OK;
        break;
      }
      else
      {
        /*Nothing to do due invalid TxPduID */
      }
    }

      /*if the PduIdType parameter is invalid */
    if (validTxPduID == (Std_ReturnType) E_NOT_OK)
    {
      #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00025,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.5,1 */
        (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_TXCONFIRMATION, J1939NM_E_INVALID_PDU_SDU_ID);
      #endif
    }
    else
    {
      lps_CanIfTransmissionState = &J1939Nm_TransmissionPending;

      if((J1939NM_TRANSMISSION_PENDING == *lps_CanIfTransmissionState) && (result == E_OK))
      {
        if (J1939Nm_GetNodeStartupDelay(J1939Nm_PendingNode) == (boolean) TRUE)
        {
          /*START THE DELAY TIMER: */
          /* !LINKSTO J1939Nm.SWS_J1939Nm_00061,1 */
          J1939Nm_StartDelayFlag[lub_ChannelCtr][J1939Nm_PendingNode] = (boolean) TRUE;
        }
        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00019,1 */
        /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.NoTxPending,1 */
        *lps_CanIfTransmissionState = J1939NM_NO_TRANSMISSION_PENDING;
        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
      }
      else if ((J1939NM_TRANSMISSION_PENDING == *lps_CanIfTransmissionState) && (result == E_NOT_OK))
      {
          /* !LINKSTO EB_Ref.SWS_J1939Nm_00062.2,1 */
          if(E_OK == J1939Nm_AddressClaimed_Transmit(J1939Nm_PendingNode, J1939Nm_PendingChannel))
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
            *lps_CanIfTransmissionState = J1939NM_TRANSMISSION_PENDING;
            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
          }
          else
          { /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.TxPendingAbort,1*/
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
            *lps_CanIfTransmissionState = J1939NM_TRANSMISSION_ABORT;
            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_TX_CONFIRMATION();
          }
      } /*For the retransmission if J1939Nm_TxConfirmation returns E_NOT_OK*/
      else
      {
        /* Nothing to be done when J1939Nm_TxConfirmation() is received in a
           state different than J1939NM_TRANSMISSION_PENDING */
      }
    }
  }
}

static FUNC(void, J1939NM_CODE) J1939Nm_HandlePendingTransmission(uint8 Node,uint8 Chid)
{
    /*The return value of Address Claimed Transmit*/
    VAR(uint8, AUTOMATIC) ret_val_AddrClaimed = (Std_ReturnType) E_NOT_OK;

    DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_ENTRY(Node,Chid);

    if (J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
    {
      ret_val_AddrClaimed = J1939Nm_AddressClaimed_Transmit(Node, Chid);
      if(E_OK == ret_val_AddrClaimed)
      {
        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
        J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
      }
      else
      {
        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
        J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
      }
      SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
      /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
      J1939Nm_PendingChannel = Chid;
      /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
      J1939Nm_PendingNode = Node;
      SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
    }
    else
    {
      /*Due not yet called "J1939Nm_TxConfirmation" to set "J1939Nm_TransmissionPending = J1939NM_NO_TRANSMISSION_PENDING"*/
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00017,1 */
      SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

      J1939Nm_ProcessPendingRequestFlag[Chid][Node] = (boolean) TRUE;

      SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
    }

    DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_EXIT(Node,Chid);
}

/* ************************************************************
 *  Name                 : J1939Nm_RequestIndication
 *  Description          : Indicates reception of a Request PG.
 *
 *  Parameters           : Input: uint8 node
 *                       : Input: NetworkHandleType channel
 *                       : Input: uint32 requestedPgn
 *                       : Input: uint8 sourceAddress
 *                       : Input: uint8 destAddress
 *                       : Input: uint8 priority
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
 /* !LINKSTO J1939Nm.SWS_J1939Nm_00043,1 */
FUNC(void, J1939NM_CODE) J1939Nm_RequestIndication(
  VAR(uint8, AUTOMATIC) node,
  VAR(NetworkHandleType, AUTOMATIC) channel,
  VAR(uint32, AUTOMATIC) requestedPgn,
  VAR(uint8, AUTOMATIC) sourceAddress,
  VAR(uint8, AUTOMATIC) destAddress,
  VAR(uint8, AUTOMATIC) priority
)
{
  VAR(Std_ReturnType, AUTOMATIC) validNetworkHandleId = (Std_ReturnType) E_NOT_OK;

  /*Generic counter variable */
  VAR(uint8, AUTOMATIC) lub_Ctr;
  VAR(uint8, AUTOMATIC) lub_Node = 0u;
  /*to loop on each node in the channel*/
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr;
  VAR(boolean, AUTOMATIC) validNodeID = (boolean) FALSE;
  VAR(boolean, AUTOMATIC) validdestAddress = (boolean) FALSE;

  /*To obtain Random delay */
  VAR(uint8, AUTOMATIC) RandomDelay;
  /*To obtain channel */
  VAR(NetworkHandleType, AUTOMATIC) internalChannelID;

  validNetworkHandleId = J1939Nm_NetworkHandleValidator(channel, &internalChannelID);

  if (J1939Nm_InitState == J1939NM_INIT)
  {
    if (destAddress == (uint8) 0xFF)
    {
      validdestAddress = (boolean) TRUE;
    }

    for (lub_Ctr = 0u; lub_Ctr < (uint8) J1939NM_NUMBER_OF_NODES; lub_Ctr++)
    {
      if (node == J1939NM_GetNodeID(lub_Ctr))
      {
        validNodeID = (boolean) TRUE;
        lub_Node = lub_Ctr;

        if (destAddress == J1939Nm_GetNodePreferedAddress(lub_Ctr))
        {
          validdestAddress = (boolean) TRUE;
        }

        break;
      }
    }
  }

  /*if the J1939Nm module is not initialized */
  if (J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.EB.DET.REQUEST_INDICATION,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_UNINIT);
    #endif
  }

  /*if the NetworkHandle parameter is invalid */
  else if (validNetworkHandleId == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00026,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_INVALID_NETWORK_ID);
    #endif
  }
  else if (validNodeID == (boolean) FALSE)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.5,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.6,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_INVALID_NODE);
    #endif
  }
  else if (requestedPgn != (uint32) J1939NM_PGN)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.8,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.7,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.7,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_INVALID_PGN);
    #endif
  }
  else if ((sourceAddress == (uint8) 0xFF) || (validdestAddress == (boolean) FALSE))
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.1,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.2,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.9,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.10,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_INVALID_ADDRESS);
    #endif
  }

  /*If priority has a different value than the according ones to it's size */
  else if ((uint8)(priority) > (uint8) 7u)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.3,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.8,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00067.4,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_REQUESTINDICATION, J1939NM_E_INVALID_PRIO);
    #endif
  }
  else
  {
    for (lub_NodeChannelCtr = 0u; lub_NodeChannelCtr < J1939Nm_GetNumbOfNodeInChannel(internalChannelID); lub_NodeChannelCtr++)
    {
      if (destAddress != (uint8) 0xFF)
      {
        if (node == J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr))
        {
          /* Deviation TASKING-1 <1> */
          if ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_NORMAL_OPERATION) ||
            ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_OFFLINE) &&
            (J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_CLAIMING)))
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

            /* !LINKSTO EB_Ref.SWS_J1939Nm_00022.1,1 */
            /* !LINKSTO EB_Ref.SWS_J1939Nm_00022.2,1 */
            /*---------------- TRIGGER A TRANSMISSION OF AN ADDRESS CLAIMED PG FOR THE NODECHANNEL ---------------------- */
            /*Preferred Address */
            MetaData_Information[lub_Node] = (uint8) J1939Nm_GetNodePreferedAddress(lub_Node);

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

            /* !LINKSTO J1939Nm.SWS_J1939Nm_00016,1 */
            J1939Nm_HandlePendingTransmission(lub_Node,internalChannelID);
          }
          else if ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_OFFLINE) &&
              (J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_ACLOST))
          {
            /* !LINKSTO EB_Ref.SWS_J1939Nm_00068.2,1 */
            /* !LINKSTO J1939Nm.SWS_J1939Nm_00023,1 */
            J1939Nm_GetBusOffDelay(internalChannelID, &RandomDelay);

            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

            BusoffRandomDelay[internalChannelID][lub_Node] = RandomDelay;

            /*------------- TRIGGER A CANNOT CLAIM ADDRESS PG FOR EACH NODECHANNEL AFTER THE DELAY CALCULATED ------------ */

            /*Preferred Address */
            MetaData_Information[lub_Node] = (uint8) J1939NM_NULL_ADDRESS;

            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
            /*------------------------------------------------------------------------------------------------------------ */
          }
          else
          {
            /*To Avoid MISRA Warning */
          }
          break;
        }
      }
      else
      {
        /* !LINKSTO J1939Nm.EB.BroadcastRequestIndication,1 */
        J1939Nm_RequestIndication_BroadCast(internalChannelID, lub_NodeChannelCtr);
      }
    }
  }
}


/* ************************************************************
 *  Name                 : J1939Nm_RequestIndication_BroadCast
 *  Description          : Used for processing the actions required
 *                         when the request indication was broadcasted
 *  Parameters           : Input: uint8 internalChannelID
 *  Parameters           : Input: uint8 lub_NodeChannelCtr
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(void, J1939NM_CODE) J1939Nm_RequestIndication_BroadCast(
  VAR(NetworkHandleType, AUTOMATIC) internalChannelID,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr
)
{
  boolean flag = FALSE;
  uint8 lub_Node = 0u;
  uint8 RandomDelay;
  /*The return value of Address Claimed Transmit*/
  VAR(uint8, AUTOMATIC) ret_val_AddrClaimed = (Std_ReturnType) E_NOT_OK;
  /* Deviation TASKING-1 */
  while(FALSE == flag)
  {
    if (J1939NM_GetNodeID(lub_Node) == J1939NM_GetNodeIDInChannel(internalChannelID,lub_NodeChannelCtr))
    {
      /* Deviation TASKING-1 <1> */
      if ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_NORMAL_OPERATION) ||
            ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_OFFLINE) &&
            (J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_CLAIMING)))
      {
        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

        /* !LINKSTO EB_Ref.SWS_J1939Nm_00022.1,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00022.2,1 */
        /*---------------- TRIGGER A TRANSMISSION OF AN ADDRESS CLAIMED PG FOR THE NODECHANNEL ---------------------- */

        /*Preferred Address */
        MetaData_Information[lub_Node] = (uint8) J1939Nm_GetNodePreferedAddress(lub_Node);

        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

        /* !LINKSTO J1939Nm.SWS_J1939Nm_00016,1 */
        if (J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
        {
          ret_val_AddrClaimed = J1939Nm_AddressClaimed_Transmit(lub_Node, internalChannelID);
          if(E_OK == ret_val_AddrClaimed)
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
            J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
          }
          else
          {
            SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
            J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
            SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
          }
          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
          /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
          J1939Nm_PendingChannel = internalChannelID;
          /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
          J1939Nm_PendingNode = lub_Node;
          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
        }
        else
        {
          /*Due not yet called "J1939Nm_TxConfirmation" to set "J1939Nm_TransmissionPending = J1939NM_NO_TRANSMISSION_PENDING"*/
          /* !LINKSTO J1939Nm.SWS_J1939Nm_00017,1 */
          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

          J1939Nm_ProcessPendingRequestFlag[internalChannelID][lub_Node] = (boolean) TRUE;

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
        }


      }
      else if ((J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState == NM_STATE_OFFLINE) &&
              (J1939NmChannelNodeInfoArr[internalChannelID].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_ACLOST))
      {

        /* !LINKSTO EB_Ref.SWS_J1939Nm_00068.2,1 */
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00023,1 */
        J1939Nm_GetBusOffDelay(internalChannelID, &RandomDelay);

        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();

        BusoffRandomDelay[internalChannelID][lub_Node] = RandomDelay;

        /*------------- TRIGGER A CANNOT CLAIM ADDRESS PG FOR EACH NODECHANNEL AFTER THE DELAY CALCULATED ------------ */

        /*Preferred Address */
        MetaData_Information[lub_Node] = (uint8) J1939NM_NULL_ADDRESS;

        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_REQ_INDICATION();
        /*------------------------------------------------------------------------------------------------------------ */
      }
      else
      {
        /*To Avoid MISRA Warning */
      }
      flag = TRUE;
    }
    lub_Node++;
  }
}

/* ************************************************************
*  Name                 : J1939Nm_MainFunction
*  Description          : Main function of the J1939 Network Management module.
*              Used for scheduling purposes and timeout supervision.
*  Parameters           : none
*  Return               : none
*  Critical/explanation : [No]
**************************************************************/
/* !LINKSTO J1939Nm.SWS_J1939Nm_00006,1 */
/* !LINKSTO J1939Nm.SWS_J1939Nm_00038,1 */
FUNC(void, J1939NM_CODE) J1939Nm_MainFunction(void)
{
  /*to loop on each channel*/
  VAR(uint8, AUTOMATIC) lub_Channels;
  /*to loop on each node in the channel*/
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr;
  /*To go through all nodes */
  VAR(uint8, AUTOMATIC) lub_Nodes;

  /*reference to the Channel config structure */
  P2VAR(J1939Nm_ChannelNodeInfoType, AUTOMATIC, J1939NM_APPL_DATA) lps_ChannelConfig;

  /*To sleep count of NodeChannel of a particular channel*/
  /* Deviation MISRAC2012-1 <1> */
  VAR(uint8, AUTOMATIC) lub_SleepCnt[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX]={{0U}};

  /*if the J1939Nm module is not initialized */
  if (J1939Nm_InitState == J1939NM_UNINIT)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO J1939Nm.EB.DET.MAINFUNCTION,1 */
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.1,1 */
      (void) Det_ReportError((uint16) J1939NM_MODULE_ID, (uint8) J1939NM_INSTANCE_ID, J1939NM_API_ID_MAINFUNCTION, J1939NM_E_UNINIT);
    #endif
  }
  else
  {
    /*Loop for all the Channels*/
    for (lub_Channels = 0u; lub_Channels < (uint8) J1939NM_NUMBER_OF_CHANNELS; lub_Channels++)
    {
      /*check if J1939Nm_NetworkRelease was called for any channel*/
      if (J1939Nm_NetworkRelease_FlagArray[lub_Channels][NetworkRelease_Channel] == NetworkRelease_Called)
      {

        lps_ChannelConfig = &J1939NmChannelNodeInfoArr[lub_Channels];

        for (lub_NodeChannelCtr = 0u; lub_NodeChannelCtr < J1939Nm_GetNumbOfNodeInChannel(lub_Channels); lub_NodeChannelCtr++)
        {
          SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_RELEASE();

          /* !LINKSTO EB_Ref.SWS_J1939Nm_00015.1,1 */
          lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelMode = NM_MODE_BUS_SLEEP;
          lps_ChannelConfig->NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState = NM_STATE_BUS_SLEEP;

          SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_RELEASE();
          /* !LINKSTO EB_Ref.SWS_J1939Nm_00015.4,1 */
          BswM_J1939Nm_StateChangeNotification(J1939Nm_NetworkRelease_FlagArray[lub_Channels][NMCHANNELHANDLE], J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr), NM_STATE_BUS_SLEEP);

        }

        /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.5,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00015.2,1 */
        Nm_BusSleepMode(J1939Nm_NetworkRelease_FlagArray[lub_Channels][NMCHANNELHANDLE]);

        /*SWS_Nm_00165,1 */
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00015.3,1 */
        /* Deviation TASKING-1 <1> */
        Nm_StateChangeNotification(J1939Nm_NetworkRelease_FlagArray[lub_Channels][NMCHANNELHANDLE], NM_STATE_OFFLINE, NM_STATE_BUS_SLEEP);

        SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_RELEASE();

        J1939Nm_NmChannelState[lub_Channels] = FALSE;

        SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_RELEASE();

        J1939Nm_NetworkRelease_FlagArray[lub_Channels][NetworkRelease_Channel] = NetworkRelease_NotCalled;
      }

      /*Loop for the NodeChannel present in the current Channel*/
      for (lub_NodeChannelCtr = 0u; (lub_NodeChannelCtr < J1939Nm_GetNumbOfNodeInChannel(lub_Channels)); lub_NodeChannelCtr++)
      {
        /*Verify the NodeChannel is in Sleep Mode or Network Mode*/
        switch (J1939NmChannelNodeInfoArr[lub_Channels].NodeChannel[lub_NodeChannelCtr].NodeChannelMode)
        {
          case NM_MODE_BUS_SLEEP:
            {
              break;
            }

            /*case NM mode network*/
          case NM_MODE_NETWORK:
            {
              /*Loop for the Node to operate on particular Node */
              boolean flag = FALSE;
              lub_Nodes = 0;
              /* Deviation TASKING-1 */
              while(FALSE == flag)
              {
                /*node id check */
                if (J1939NM_GetNodeID(lub_Nodes) == J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr))
                {
                  if (J1939NmChannelNodeInfoArr[lub_Channels].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_CLAIMING)
                  {
                    J1939Nm_MainFunction_DelayStart(lub_Nodes, lub_Channels, lub_NodeChannelCtr);
                  }

                  if (J1939Nm_ACLostFlag[lub_Channels][lub_NodeChannelCtr] == (boolean) FALSE)
                  {
                    /*check for off-line AC_LOST */
                    J1939Nm_MainFunction_ACLost(lub_Nodes, lub_Channels, lub_NodeChannelCtr, (lub_SleepCnt[lub_Channels]));
                  }

                  /*If NodeChannelNetworkModeState is in NM_STATE_NORMAL_OPERATION*/
                  J1939Nm_MainFunction_NormalOp(lub_Nodes, lub_Channels);
                  flag = TRUE;
                } /*node id check */
                lub_Nodes++;
              } /*Loop for the Node to operate on particular Node */
              break;
            } /*case NM mode network*/
          /* CHECK: NOPARSE */
          default:
            {
              /*Nothing to do*/
              break;
            }
          /* CHECK: PARSE */
        } /*Verify the NodeChannel is in Sleep Mode or Network Mode*/
      } /*Loop for the NodeChannel present in the current Channel*/
    } /*Loop for all the Channels*/

    /*For the retransmission if CanIf_Transmit() returns E_NOT_OK */
    if (J1939Nm_TransmissionPending == J1939NM_TRANSMISSION_ABORT)
    {
        /* !LINKSTO EB_Ref.SWS_J1939Nm_00062.1,1 */
        if(E_OK == J1939Nm_AddressClaimed_Transmit(J1939Nm_PendingNode, J1939Nm_PendingChannel))
        {
          /* !LINKSTO J1939Nm.EB.Dsn.CanIfTransmissionState.AbortTxPending,1 */
          J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
        }
    }
  } /*if the J1939Nm module is not initialized */
} /*FUNCTION ENDS */


/* ************************************************************
 *  Name                 : J1939Nm_AddressClaimed_Transmit
 *  Description          : Used for Triggering Address Claimed message
 *  Parameters           : Input: uint8 lub_Nodes
 *  Parameters           : Input: uint8 lub_Channels
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_AddressClaimed_Transmit(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels
)
{
  /*pdu info structure for PduRouter and CAN Interface */
  PduInfoType pdu_info_canif;

  pdu_info_canif.SduLength = (uint32) J1939NM_NODE_NAME_SIZE;
  pdu_info_canif.SduDataPtr = &Txbuffer[lub_Nodes][0];

  (void)J1939Nm_SetCanId(MetaData_Information[lub_Nodes], J1939Nm_GetTxEcucPduId(lub_Channels), &pdu_info_canif, J1939NM_API_ID_MAINFUNCTION);

  /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.2,1 */
  /*Transmit the information. */
  return ((Std_ReturnType)CanIf_Transmit(J1939Nm_GetTxCanIfPduId(lub_Channels), &pdu_info_canif));
}

/* ************************************************************
 *  Name                 : J1939Nm_MainFunction_ACLost
 *  Description          : Used for processing the actions required For Ack Lost
 *  Parameters           : Input: uint8 lub_Nodes
 *  Parameters           : Input: uint8 lub_Channels
 *  Parameters           : Input: uint8 lub_NodeChannelCtr
 *  Parameters           : Input: uint8* lub_SleepCnt
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_ACLost(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_SleepCnt
)
{
#if (J1939NM_DEM_ENABLED == STD_ON)
  /*Index used for Dem Events */
  VAR(uint8, AUTOMATIC) lub_DemEventIndex;
#endif
  if (J1939NmChannelNodeInfoArr[lub_Channels].NodeChannel[lub_NodeChannelCtr].NodeChannelOfflineSubState == J1939NM_OFFLINE_ACLOST)
  {
    J1939Nm_DelayCtr[lub_Channels][lub_Nodes] = J1939Nm_DelayCtr[lub_Channels][lub_Nodes] + (uint16) J1939NM_MAIN_FUNC_PERIOD;

    /* !LINKSTO EB_Ref.SWS_J1939Nm_00014.2,1 */
    /*------------- TRIGGER A CANNOT CLAIM ADDRESS PG FOR EACH NODECHANNEL AFTER THE DELAY CALCULATED ------------ */
    if (J1939Nm_DelayCtr[lub_Channels][lub_Nodes] >= BusoffRandomDelay[lub_Channels][lub_Nodes])
    {
      /*Processed the AC_LOST for this NodeChannel of the respective channel*/
      J1939Nm_ACLostFlag[lub_Channels][lub_NodeChannelCtr] = (uint8) TRUE;

      /*Node Preferred Address */
      MetaData_Information[lub_Nodes] = (uint8) J1939NM_NULL_ADDRESS;

      /* !LINKSTO J1939Nm.SWS_J1939Nm_00016,1 */
      if (J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
      {
        if(E_OK == J1939Nm_AddressClaimed_Transmit(lub_Nodes, lub_Channels))
        {
          J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
        }
        else
        {
          J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
        }
        /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
        J1939Nm_PendingChannel = lub_Channels;
        /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
        J1939Nm_PendingNode = lub_Nodes;
      }
      else
      {
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00017,1 */
        J1939Nm_ProcessPendingRequestFlag[lub_Channels][lub_Nodes] = (boolean) TRUE;
      }

      /* ------------------------------------------------------------------------------------------------------------ */
      /* !LINKSTO J1939Nm.SWS_J1939Nm_00065,1*/
      /* Deviation TASKING-1 <1> */
      BswM_J1939Nm_StateChangeNotification(J1939Nm_ComMChannelIDs[lub_Channels], J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr), NM_STATE_OFFLINE);

      /*Don't make whole network to sleep instead of make only NodeChannel from Network_Mode to Sleep_Mode */
#if (J1939NM_DEM_ENABLED == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00012.1,1 */
      if(J1939Nm_GetNumbOfDemEvent(lub_Channels) > 0U)
      {
        for(lub_DemEventIndex=0; lub_DemEventIndex < J1939Nm_GetNumbOfDemEvent(lub_Channels); lub_DemEventIndex++)
        {
          if(J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr) == J1939Nm_GetNodeIdInDemEvent(lub_Channels,lub_DemEventIndex))
          {
            /* !LINKSTO EB_Ref.SWS_J1939Nm_00040.ASR_42.Dem_Reporting,1 */
            (void)Dem_ReportErrorStatus((Dem_EventIdType)J1939Nm_GetDemEventId(lub_Channels,lub_DemEventIndex), (Dem_EventStatusType)DEM_EVENT_STATUS_PREFAILED);
          }
        }
      }
#endif

      lub_SleepCnt[lub_NodeChannelCtr]++;

      if (J1939Nm_GetNumbOfNodeInChannel(lub_Channels) == lub_SleepCnt[lub_NodeChannelCtr])
      {
        /* Deviation TASKING-1 <1> */
        Nm_StateChangeNotification(J1939Nm_ComMChannelIDs[lub_Channels], NM_STATE_NORMAL_OPERATION, NM_STATE_OFFLINE);

        J1939NmChannelNodeInfoArr[lub_Channels].NodeChannel[lub_NodeChannelCtr].NodeChannelMode = NM_MODE_BUS_SLEEP;

        lub_SleepCnt[lub_NodeChannelCtr] = 0u;
      }
    } /*------------- TRIGGER A CANNOT CLAIM ADDRESS PG FOR EACH NODECHANNEL AFTER THE DELAY CALCULATED ------------ */
  }
}

/* ************************************************************
 *  Name                 : J1939Nm_MainFunction_NormalOp
 *  Description          : Used for processing the actions required For Normal Operation
 *  Parameters           : Input: uint8 lub_Nodes
 *  Parameters           : Input: uint8 lub_Channels
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_NormalOp(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels
)
{
  /*If NodeChannelNetworkModeState is in NM_STATE_NORMAL_OPERATION*/
  if (J1939Nm_ProcessPendingRequestFlag[lub_Channels][lub_Nodes] == (boolean) TRUE)
  {

    /*Process pending requests*/
    if (J1939Nm_TransmissionPending == J1939NM_NO_TRANSMISSION_PENDING)
    {
      J1939Nm_ProcessPendingRequestFlag[lub_Channels][lub_Nodes] = (boolean) FALSE;

      if(E_OK == J1939Nm_AddressClaimed_Transmit(lub_Nodes, lub_Channels))
      {
        J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_PENDING;
      }
      else
      {
        J1939Nm_TransmissionPending = J1939NM_TRANSMISSION_ABORT;
      }
      /* Update these variables for retransmission, if J1939Nm_TxConfirmation() or CanIf_Transmit() is received with E_NOT_OK */
      J1939Nm_PendingChannel = lub_Channels;
      /* Variable to verify the startupDelay in J1939Nm_TxConfirmation() function */
      J1939Nm_PendingNode = lub_Nodes;
    }
    else
    {
      /*No Operation */
    }
  }
}

/* ************************************************************
 *  Name                 : J1939Nm_MainFunction_DelayStart
 *  Description          : Used for processing the actions required when the Delay counter used to calculate
                           the 250ms delay before the nodeChannel move from the claiming state to normal operation state.
 *  Parameters           : Input: uint8 lub_Nodes
 *  Parameters           : Input: uint8 lub_Channels
 *  Parameters           : Input: uint8 lub_NodeChannelCtr
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(void, J1939NM_CODE) J1939Nm_MainFunction_DelayStart(
  VAR(uint8, AUTOMATIC) lub_Nodes,
  VAR(uint8, AUTOMATIC) lub_Channels,
  VAR(uint8, AUTOMATIC) lub_NodeChannelCtr
)
{
#if (J1939NM_DEM_ENABLED == STD_ON)
  /*Index used for Dem Events */
  VAR(uint8, AUTOMATIC) lub_DemEventIndex;
#endif
  if (J1939Nm_StartDelayFlag[lub_Channels][lub_Nodes] == (boolean) TRUE)
  {
    /*Start delay counter for 250ms to confirm address in the network */
    J1939Nm_DelayCtr[lub_Channels][lub_Nodes] = J1939Nm_DelayCtr[lub_Channels][lub_Nodes] + (uint16) J1939NM_MAIN_FUNC_PERIOD;

    /*If the NodeChannel has stayed for 250ms in state "Claiming", after transmission of the initial AddressClaiming PG, it will switch to state "NormalOperation" */
    if (J1939Nm_DelayCtr[lub_Channels][lub_Nodes] >= (uint16) J1939NM_CLAIMING_PERIOD)
    {
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00013.1,1 */
      J1939NmChannelNodeInfoArr[lub_Channels].NodeChannel[lub_NodeChannelCtr].NodeChannelNetworkModeState = NM_STATE_NORMAL_OPERATION;

      /*Reset global counter and disable it*/
      J1939Nm_DelayCtr[lub_Channels][lub_Nodes] = (uint16) 0x00;

      J1939Nm_StartDelayFlag[lub_Channels][lub_Nodes] = (boolean) FALSE;

      /* !LINKSTO EB_Ref.SWS_J1939Nm_00013.2,1 */
      BswM_J1939Nm_StateChangeNotification(J1939Nm_ComMChannelIDs[lub_Channels],  J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr), NM_STATE_NORMAL_OPERATION);

#if (J1939NM_DEM_ENABLED == STD_ON)
      /* !LINKSTO EB_Ref.SWS_J1939Nm_00012.2,1 */
      if(J1939Nm_GetNumbOfDemEvent(lub_Channels) > 0U)
      {
        for(lub_DemEventIndex=0; lub_DemEventIndex < J1939Nm_GetNumbOfDemEvent(lub_Channels); lub_DemEventIndex++)
        {
          if(J1939NM_GetNodeIDInChannel(lub_Channels,lub_NodeChannelCtr) == J1939Nm_GetNodeIdInDemEvent(lub_Channels,lub_DemEventIndex))
          {
            (void)Dem_ReportErrorStatus((Dem_EventIdType)J1939Nm_GetDemEventId(lub_Channels,lub_DemEventIndex), (Dem_EventStatusType)DEM_EVENT_STATUS_PREPASSED);
          }
        }
      }
#endif

      if (J1939Nm_NmChannelState[lub_Channels] == FALSE)
      {
        /* !LINKSTO J1939Nm.SWS_J1939Nm_00066,1*/
        /*If the last NodeChannel has changed its state to "Offline"*/
        /*SWS_Nm_00165,1*/
        /* Deviation TASKING-1 <1> */
        Nm_StateChangeNotification(J1939Nm_ComMChannelIDs[lub_Channels], NM_STATE_OFFLINE, NM_STATE_NORMAL_OPERATION);

        J1939Nm_NmChannelState[lub_Channels] = TRUE;
      }
    }
  }
}

/* ************************************************************
 *  Name                 : J1939Nm_NetworkHandleValidator
 *  Description          : Used for validating the NetworkHandle
 *                       : received as a parameter in the API functions.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/

static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkHandleValidator(VAR(NetworkHandleType, AUTOMATIC) NetworkHandle, P2VAR(NetworkHandleType, AUTOMATIC, J1939NM_APPL_DATA) InternalNmChannelID)
{
  /* The return value */
  VAR(Std_ReturnType, AUTOMATIC) ret_val = (Std_ReturnType) E_NOT_OK;
  VAR(uint8, AUTOMATIC) lub_Ctr;  /* Generic counter variable */

  DBG_J1939NM_NULL_POINTER_VALIDATION_ENTRY(InternalNmChannelID);

  /* to avoid compiler warnings*/
  *InternalNmChannelID = (NetworkHandleType) 0;

  for(lub_Ctr=0u; lub_Ctr < (uint8) J1939NM_NUMBER_OF_COMM_CHANNELS;lub_Ctr++)
  {
    if(NetworkHandle == J1939Nm_ComMChannelIDs[lub_Ctr])
    {
      ret_val = (Std_ReturnType) E_OK;

      SchM_Enter_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_VALIDATOR();


      *InternalNmChannelID = (NetworkHandleType) lub_Ctr;

      SchM_Exit_J1939Nm_SCHM_J1939NM_EXCLUSIVE_NW_VALIDATOR();
      break;
    }
    else
    {
        /* Nothing to do due invalid NetworkHandle */
    }
  }

  DBG_J1939NM_NULL_POINTER_VALIDATION_EXIT(InternalNmChannelID);
  return ret_val;
}

/* ************************************************************
 *  Name                 : J1939Nm_DetValidityCheck
 *  Description          : Used to log the DET errors for invalid RxPduID,PrefAddress,NodeId.
 *  Parameters           : Input: Std_ReturnType validRxPduID
 *  Parameters           : Input: Std_ReturnType validPrefAddress
 *  Parameters           : Input: Std_ReturnType validNodeId
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/

static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_DetValidityCheck(
  VAR(Std_ReturnType, AUTOMATIC) validRxPduID,
  VAR(Std_ReturnType, AUTOMATIC) validPrefAddress,
  VAR(Std_ReturnType, AUTOMATIC) validNodeId
)
{
  VAR(Std_ReturnType, AUTOMATIC) status = (Std_ReturnType)E_OK;

  /* if the PduIdType parameter is invalid */
  if(validRxPduID == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO J1939Nm.SWS_J1939Nm_00025,1 */
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.5,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION,
      J1939NM_E_INVALID_PDU_SDU_ID);
    status = E_NOT_OK;
    #endif
  }
  else if(validPrefAddress == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.9,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION, J1939NM_E_INVALID_ADDRESS);
    status = E_NOT_OK;
    #endif
  }
  else if(validNodeId == (Std_ReturnType) E_NOT_OK)
  {
    #if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO EB_Ref.SWS_J1939Nm_00024.10,1 */
    (void)Det_ReportError((uint16)J1939NM_MODULE_ID, (uint8)J1939NM_INSTANCE_ID, J1939NM_API_ID_RXINDICATION, J1939NM_E_INVALID_NODE);
    status = E_NOT_OK;
    #endif
  }
  else
  {
    /* Do Nothing */
  }
  return status;

}

/* ************************************************************
 *  Name                 : J1939Nm_NodeId_PrefAddress_ValidityCheck
 *  Description          : Used to check the validity of NodeId and Preferred address.
 *  Parameters           : Input: uint8 SA
 *  Parameters           : Input / output: Std_VersionInfoType *validPrefAddress
 *  Parameters           : Input / output: uint8 *lub_Node
 *  Parameters           : Input / output: uint8 *lub_NodeID
 *  Parameters           : Input: uint8 lub_Channel
 *  Parameters           : Input / output: uint8 *lub_NodeChannel
 *  Return               : Std_ReturnType E_OK, E_NOT_OK
 *  Critical/explanation : [No]
 **************************************************************/
static FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NodeId_PrefAddress_ValidityCheck(
  VAR(uint8, AUTOMATIC) SA,
  P2VAR(Std_ReturnType, AUTOMATIC, J1939NM_APPL_DATA) validPrefAddress,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_Node,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_NodeID,
  VAR(uint8, AUTOMATIC) lub_Channel,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) lub_NodeChannel
)
{
  VAR(Std_ReturnType, AUTOMATIC) validNodeId = (Std_ReturnType)E_NOT_OK;
  VAR(uint8, AUTOMATIC) lub_Ctr;

  for (lub_Ctr=0u; lub_Ctr < (uint8) J1939NM_NUMBER_OF_NODES ; lub_Ctr++)
  {
    if(SA == (J1939Nm_GetNodePreferedAddress(lub_Ctr)))
    {
      *validPrefAddress = (Std_ReturnType) E_OK;
      *lub_NodeID = J1939NM_GetNodeID(lub_Ctr);
      *lub_Node = lub_Ctr;
      break;
    }
  }

  for (lub_Ctr=0u; lub_Ctr < J1939Nm_GetNumbOfNodeInChannel(lub_Channel); lub_Ctr++)
  {
    if(*(lub_NodeID) == J1939NM_GetNodeIDInChannel(lub_Channel,lub_Ctr))
    {
      /* Obtained NodeChannel */
      validNodeId = (Std_ReturnType) E_OK;
      *lub_NodeChannel = lub_Ctr;
      break;
    }
  }
  return validNodeId;

}
/*==================[Dummy functions]=========================*/

FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetUserData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) nmUserDataPtr
)
{
  TS_PARAM_UNUSED(NetworkHandle);
  TS_PARAM_UNUSED(nmUserDataPtr);

#if(J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Nm.EB.Invalid_Call,1 */
  (void)Det_ReportError(J1939NM_MODULE_ID, J1939NM_INSTANCE_ID,J1939NM_SETUSERDATA, J1939NM_E_INVALID_CALL);
#endif /* J1939NM_DEV_ERROR_DETECT == STD_ON */

  return E_NOT_OK;
}

FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetUserData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmUserDataPtr
)
{
  TS_PARAM_UNUSED(NetworkHandle);
  TS_PARAM_UNUSED(nmUserDataPtr);

#if(J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Nm.EB.Invalid_Call,1 */
  (void)Det_ReportError(J1939NM_MODULE_ID, J1939NM_INSTANCE_ID,J1939NM_GETUSERDATA, J1939NM_E_INVALID_CALL);
#endif /* J1939NM_DEV_ERROR_DETECT == STD_ON */

  return E_NOT_OK;
}


FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetPduData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmPduData
)
{
  TS_PARAM_UNUSED(NetworkHandle);
  TS_PARAM_UNUSED(nmPduData);

#if(J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Nm.EB.Invalid_Call,1 */
  (void)Det_ReportError(J1939NM_MODULE_ID, J1939NM_INSTANCE_ID,J1939NM_GETPDUDATA, J1939NM_E_INVALID_CALL);
#endif /* J1939NM_DEV_ERROR_DETECT == STD_ON */

  return E_NOT_OK;
}


FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_CheckRemoteSleepIndication
(
  VAR(NetworkHandleType, AUTOMATIC) nmNetworkHandle,
  P2VAR(boolean, AUTOMATIC, J1939NM_APPL_DATA) nmRemoteSleepIndPtr
)
{
  TS_PARAM_UNUSED(nmNetworkHandle);
  TS_PARAM_UNUSED(nmRemoteSleepIndPtr);

#if(J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO J1939Nm.EB.Invalid_Call,1 */
  (void)Det_ReportError(J1939NM_MODULE_ID, J1939NM_INSTANCE_ID,J1939NM_CHECKREMOTESLEEPINDICATION, J1939NM_E_INVALID_CALL);
#endif /* J1939NM_DEV_ERROR_DETECT == STD_ON */

  return E_NOT_OK;
}

#define J1939NM_STOP_SEC_CODE
#include <J1939Nm_MemMap.h>

