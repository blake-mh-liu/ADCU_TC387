/* --------{ EB Automotive C Source File }-------- */

/* This file contains definitions for interface functions provided by Dem to
 * the J1939Dcm and the general internal functions needed for the J1939Dcm
 * interface and J1939 extension core functionalities. */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The compiler optimizes the 'for' loop (which has only 1 iteration) in the following way:
 * - it prepares in advance the index for the next iteration
 * - if the index is equal to '0' it goes back to check the 'for' loop conditions, otherwise it just moves on
 * - since the index is already equal to '1', it never jumps back to check the exit condition
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The "Dem_J1939FreezeFrameFilter.IsFilterValid" is set to FALSE when unsupported
 * FreezeFrameKind is requested. In other configurations, the code coverage reaches
 * sections where the value is different.
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The "Dem_J1939DTCFilter.IsFilterValid" is set to FALSE when wrong filter is requested.
 * In other configurations, the code coverage reaches sections where the value is different.
 */

/*==================[inclusions]============================================*/
#include <TSAutosar.h>                        /* EB specific standard types */
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */
/*==================[macros]================================================*/
#if (defined DEM_DM5_READINESS_SIZE)
#error DEM_DM5_READINESS_SIZE already defined
#endif
/** \brief Size of DM5 as per SAE_J1939 */
#define DEM_DM5_READINESS_SIZE 0x05U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if (DEM_J1939_SUPPORT == STD_ON)
/** \brief Function to return the node of the DTC referenced by a specific event
 **
 ** \pre This function shall be called only for a valid J1939Dtc.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return uint8 value, the value of the Node
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint8, DEM_CODE) Dem_InternalGetJ1939Node(Dem_EventIdType EventId);

#if ((DEM_J1939_READING_DTC_SUPPORT == STD_ON) || \
     (DEM_J1939_READINESS1_SUPPORT == STD_ON) || \
     (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON))
/** \brief Function to apply the DTC filter with the given event
 **
 ** Note: For filter setting DEM_J1939DTC_PERMANENT always FALSE is returned.
 ** This filter must be handled by the calling function itself.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] J1939Filter
 **
 ** \return Boolean value, if the filter matches the event configuration
 ** \retval TRUE  the filters match
 ** \retval FALSE the filters don't match
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_ApplyJ1939DTCFilter(
  Dem_EventIdType                                                EventId,
  Dem_J1939DcmDTCStatusFilterType                               J1939Filter
 );
#endif /* (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ||
          (DEM_J1939_READINESS1_SUPPORT == STD_ON)  ||
          (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON) */

#if ((DEM_J1939_READING_DTC_SUPPORT == STD_ON) || \
     (DEM_J1939_READINESS1_SUPPORT == STD_ON))
/** \brief Gets the count of  J1939 DTCs.
 *
 * \param[in] DTCStatusFilter      set the filter type
 * \param[in] DTCKind  Defines the functional group of DTCs to be counted
 * \param[in] Node     J1939Nm node Id
 *
 * \return uint8 Returns DTC counts that match the input parameters
 */
STATIC FUNC(uint8, DEM_CODE) Dem_GetNumberJ1939DTCs(
  Dem_J1939DcmDTCStatusFilterType  DTCStatusFilter,
  Dem_DTCKindType                  DTCKind,
  uint8                            Node);
#endif

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
#if ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
     (defined DEM_PIL_ID) || (defined DEM_MIL_ID))
/** \brief Internal function for reading the status of Lamp indicators.
 **
 ** This function shall be used to read the Lamp indicator-status derived from the
 ** event status as a summary of all assigned events.
 **
 ** \param[in] IndicatorId ID of indicator
 **
 ** \return Status of the indicator, like on, off, blinking.
 ** \retval DEM_INDICATOR_OFF         Indicator off mode
 ** \retval DEM_INDICATOR_CONTINUOUS  Indicator continuously on mode
 ** \retval DEM_INDICATOR_SLOW_FLASH  Indicator slow flash mode
 ** \retval DEM_INDICATOR_FAST_FLASH  Indicator fast flash mode
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_IndicatorStatusType, DEM_CODE) Dem_J1939InternalGetLampStatus(
  Dem_IndicatorIdType IndicatorId);
#endif /* ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) ||
           (defined DEM_PIL_ID) || (defined DEM_MIL_ID)) */

/** \brief Internal function for setting the bytes of the indicator lamps.
 **
 ** This function shall be used to retrieve the status of the configured
 ** indicator lamps.
 **
 ** \param[out] LampStatus  The status of the four lamps.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_J1939GetInternalLampStatusBytes(
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA)  LampStatus);

#if ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
     (defined DEM_PIL_ID) || (defined DEM_MIL_ID))
/** \brief Internal function for reading lamp command and lamp flash bits.
 **
 ** This function shall be used to retrieve the lamp commanded
 ** condition based on the status of requested indicator.
 **
 ** \param[in]    IndicatorStatus The status of requested indicator.
 **
 ** \return Dem_J1939DcmLampStatusType Result. Return the status of the
 **         requested indicator in the 2 lower most bits of each bytes
 **         (lower byte and upper byte) containing the command and flash
 **         status respectively.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_J1939DcmLampStatusType, DEM_CODE) Dem_J1939GetLampBits(
  Dem_IndicatorStatusType     IndicatorStatus);
#endif /* ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
           (defined DEM_PIL_ID) || (defined DEM_MIL_ID)) */
#endif /* (DEM_J1939_READING_DTC_SUPPORT == STD_ON) */

#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
/** \brief Start clearing process of all events matching the node and filter
 **
 ** \param[in]  DTCTypeFilter
 ** \param[in]  Node
 **
 ** \return Updated result of clear event process
 */
STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_J1939DcmStartClearDTC(
  Dem_J1939DcmSetClearFilterType   DTCTypeFilter,
  uint8                                     Node);

#endif /* DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*------------------[Dem_RGBitPosJ1939Readiness1 array]---------------------*/
#if ( (DEM_J1939_READINESS1_SUPPORT == STD_ON) && \
      (DEM_OBD_Support == STD_ON) && \
      (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) )
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

/* !LINKSTO dsn.Dem.RGP.BufferBitPositionMap,1 */
/** \brief Array containing the bit position information for the supported and
 ** ready status for all the readiness groups required by J1939Rediness1 */
STATIC CONST(Dem_RGStatusMappingType, DEM_CONST)
  Dem_RGBitPosJ1939Readiness1[DEM_RGP_MAX_NUM_READINESS_GROUPS] =
{
  {/* RgId 0 - NONE */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 1 - CAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_0)
  },
  {/* RgId 2 - HTCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_1)
  },
  {/* RgId 3 - MISF */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_4)
  },
  {/* RgId 4 - EVAP */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_2)
  },
  {/* RgId 5 - SECAIR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_3)
  },
  {/* RgId 6 - FLSYS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_5)
  },
  {/* RgId 7 - EGSENS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_5),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_5)
  },
  {/* RgId 8 - EGR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_7),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_7)
  },
  {/* RgId 9 - PCV */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 10 - ECS */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 11 - CSER */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_0)
  },
  {/* RgId 12 - VVT */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 13 - DOR */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 14 - CMPRCMPT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_6)
  },
  {/* RgId 15 - OTHER */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 16 - HCCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_4),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_4)
  },
  {/* RgId 17 - NOXCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_3)
  },
  {/* RgId 18 - BOOSTPR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_1)
  },
  {/* RgId 19 - NOXADSORB */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 20 - PMFLT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_2)
  },
  {/* RgId 21 - GPF */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 22 - O2SENS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_5),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_5)
  },
  {/* RgId 23 - O2SENSHT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_6),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_6)
  },
  {/* RgId 24 - AC */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_4),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_4)
  },
};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
#endif /* #if ( (DEM_J1939_READINESS1_SUPPORT == STD_ON) && \
                (DEM_OBD_Support == STD_ON) && \
                (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) ) */

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/
#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <Dem_MemMap.h>
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)

/** \brief Status of DTC-filter */
STATIC VAR(Dem_J1939DTCFilterType, DEM_VAR) Dem_J1939DTCFilter =
{
  1U,                            /* index of event to read next */
  DEM_J1939DTC_ACTIVE,           /* J1939 DTC status filter */
  DEM_DTC_KIND_ALL_DTCS,         /* DTC kind */
  0U,                            /* J1939 NM Node */
  FALSE,                         /* Initial value for validity */
};
#endif

#if (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)

/** \brief Status of J1939 Freeze Frame Filter */
STATIC VAR(Dem_J1939FreezeFrameFilterType, DEM_VAR) Dem_J1939FreezeFrameFilter =
{
  1U,                            /* index of event to read next */
  DEM_J1939DCM_FREEZEFRAME,      /* Kind of J1939 Freeze Frame */
  0U,                            /* J1939 NM Node */
  FALSE,                         /* Initial value for validity */
};

#endif
#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[external function definitions]=========================*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
/*------------------------[Dem_J1939DcmSetDTCFilter]------------------------*/

FUNC(Dem_ReturnSetFilterType, DEM_CODE) Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType                             DTCStatusFilter,
  Dem_DTCKindType                                             DTCKind,
  uint8                                                       node,
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA) LampStatus)
{
  Dem_ReturnSetFilterType Result = DEM_WRONG_FILTER;

  DBG_DEM_J1939DCMSETDTCFILTER_ENTER(
    DTCStatusFilter, DTCKind, node, LampStatus);
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_WRONG_CONTEXT);
  }
#endif
  else if ( (DTCStatusFilter != DEM_J1939DTC_ACTIVE) &&
            (DTCStatusFilter != DEM_J1939DTC_PREVIOUSLY_ACTIVE) &&
            (DTCStatusFilter != DEM_J1939DTC_PENDING) &&
            (DTCStatusFilter != DEM_J1939DTC_CURRENTLY_ACTIVE) &&
            (DTCStatusFilter != DEM_J1939DTC_PERMANENT) )
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
            (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS) )
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter,
                     DEM_E_WRONG_CONFIGURATION);
  }
  else if (LampStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if ( ( (DTCKind == DEM_DTC_KIND_ALL_DTCS) &&
           (DTCStatusFilter == DEM_J1939DTC_PERMANENT) ) ||
         ( (DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
           (DTCStatusFilter == DEM_J1939DTC_CURRENTLY_ACTIVE) ) )
    {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.DetInvalidParameterCombination,1 */
      DEM_REPORT_ERROR(DEM_SID_J1939DcmSetDTCFilter, DEM_E_PARAM_DATA);
#endif
      /* Resetting the filter criteria when the wrong filter is requested */
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.ResetFilter,1 */
      Dem_J1939DTCFilter.NextItem = 0U;
      Dem_J1939DTCFilter.DTCKind = DEM_J1939DTC_ACTIVE;
      Dem_J1939DTCFilter.Node = 0U;
      Dem_J1939DTCFilter.IsFilterValid = FALSE;

      Result = DEM_WRONG_FILTER;
    }
    else
    {
      /* !LINKSTO Dem.SWS_Dem_00855,1 */
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.ResetFilter,1 */
      Dem_J1939DTCFilter.J1939DTCStatusFilter = DTCStatusFilter;
      Dem_J1939DTCFilter.DTCKind = DTCKind;
      Dem_J1939DTCFilter.Node = node;
#if (DEM_OBD_Support == STD_OFF)
      if ( (DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS) ||
           (DTCStatusFilter == DEM_J1939DTC_PERMANENT) )
      {
        /* if OBD support is disabled these filters do not return any element;
        * setting NextItem to DEM_NUMBER_OF_EVENTS avoids unnecessary event looping
        * in subsequent API calls */
        /* !LINKSTO dsn.Dem.J1939.J1939DTCFilter.J1939DcmSetDTCFilter.NoOBDSupport,1 */
        Dem_J1939DTCFilter.NextItem = DEM_NUMBER_OF_EVENTS;
      }
      else
#endif
      {
        Dem_J1939DTCFilter.NextItem = 0U;
      }

      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.ReturnLampStatus,1 */
      Dem_J1939GetInternalLampStatusBytes(LampStatus);
      Dem_J1939DTCFilter.IsFilterValid = TRUE;

      Result = DEM_FILTER_ACCEPTED;
    }
  }

  DBG_DEM_J1939DCMSETDTCFILTER_EXIT(
    Result, DTCStatusFilter, DTCKind ,node, LampStatus);
  return Result;
}

/*-------------------[Dem_J1939DcmGetNumberOfFilteredDTC]-------------------*/

FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE) Dem_J1939DcmGetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredDTC)
{
  Dem_ReturnGetNumberOfFilteredDTCType Result = DEM_NUMBER_FAILED;

  DBG_DEM_J1939DCMGETNUMBEROFFILTEREDDTC_ENTER(NumberOfFilteredDTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNumberOfFilteredDTC, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNumberOfFilteredDTC,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (NumberOfFilteredDTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNumberOfFilteredDTC,
                     DEM_E_PARAM_POINTER);
  }
  /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.DetInvalidFilter,1 */
  else if (Dem_J1939DTCFilter.IsFilterValid == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNumberOfFilteredDTC, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.InvalidFilterCriteria,1 */
    /* Deviation TASKING-3 */
    if (Dem_J1939DTCFilter.IsFilterValid != FALSE)
    {
      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNumberOfFilteredDTC.NumberFiltered,2 */
      *NumberOfFilteredDTC = Dem_GetNumberJ1939DTCs(
                               Dem_J1939DTCFilter.J1939DTCStatusFilter,
                               Dem_J1939DTCFilter.DTCKind,
                               Dem_J1939DTCFilter.Node);
      Result = DEM_NUMBER_OK;
    }
  }

  DBG_DEM_J1939DCMGETNUMBEROFFILTEREDDTC_EXIT(Result, NumberOfFilteredDTC);

  return Result;
}

/*---------------------[Dem_J1939DcmGetNextFilteredDTC]---------------------*/

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) Dem_J1939DcmGetNextFilteredDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) OccurenceCounter)
{
  /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.NoMatchingRet,2 */
  Dem_ReturnGetNextFilteredElementType Result = DEM_FILTERED_NO_MATCHING_ELEMENT;

  DBG_DEM_J1939DCMGETNEXTFILTEREDDTC_ENTER(J1939DTC, OccurenceCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredDTC, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredDTC, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((J1939DTC == NULL_PTR) || (OccurenceCounter == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredDTC, DEM_E_PARAM_POINTER);
  }
  /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.DetInvalidFilter,1 */
  else if (Dem_J1939DTCFilter.IsFilterValid == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredDTC, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.InvalidFilterCriteria,1 */
    /* Deviation TASKING-3 */
    if (Dem_J1939DTCFilter.IsFilterValid != FALSE)
    {
      uint16 MaxIdx = DEM_MAX_EVENTID;
      boolean FilterResult = FALSE;
      *J1939DTC = (uint32)DEM_NO_DTC;
      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.NoOccCnt,1 */
      *OccurenceCounter = (uint8)127U;

      if (DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilter.J1939DTCStatusFilter)
      {
#if ((DEM_OBD_Support == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
        /* only permanent memory entries are checked */
        MaxIdx = DEM_MAX_NUMBER_EVENT_ENTRY_PER - 1U;
#else
        /* skip the loop, if permanent memory is not configured (there is no matching element) */
        Dem_J1939DTCFilter.NextItem = DEM_NUMBER_OF_EVENTS;
#endif
      }
      else if (Dem_J1939DTCFilter.NextItem == 0U)
      {
        /* NextItem == 0 indicates that this is the first execution after
         * Dem_J1939DcmSetDTCFilter(), but the first valid EventID is 1 */
        Dem_J1939DTCFilter.NextItem = 1U;
      }
      else
      {
        /* do nothing */
      }
      /* search for first DTC fulfilling the filter criterion */
      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.FilteredDTCs,1 */
      while ( (Dem_J1939DTCFilter.NextItem <= MaxIdx) &&
              (FilterResult == FALSE) )
      {
        Dem_EventIdType NextEventId = DEM_EVENT_ID_INVALID;
        uint32 GetFilter_J1939Dtc = DEM_NO_DTC;
        boolean StatusFilterMatches = FALSE;
        /* !LINKSTO Dem_OBD_0001,2 */
#if ((DEM_OBD_Support == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
        if(DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilter.J1939DTCStatusFilter)
        {
          /* Only events stored in the permanent memory are relevant. Therefore only
           * permanent entries are checked to reduce runtime. */
          const Dem_PermanentMemoryEntryType Entry =
            Dem_EventMemoryPermanent[Dem_J1939DTCFilter.NextItem];

          NextEventId = DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry);
          /* !LINKSTO Dem.J1939.PermanentDTC.NonVolatileStorage,1 */
          if ( (NextEventId != DEM_EVENT_ID_INVALID) &&
               (Dem_EventMemoryPermanentNonVolatileStored[Dem_J1939DTCFilter.NextItem] !=
                 DEM_PERMANENT_MEMORY_NV_STORED) )
          {
            /* event not taken into account, because it is not yet stored non-volatile */
            NextEventId = DEM_EVENT_ID_INVALID;
          }
          StatusFilterMatches = TRUE;
        }
        else
#endif
        {
          /* all configured events are checked */
          NextEventId = (Dem_EventIdType)Dem_J1939DTCFilter.NextItem;
        }

        if (NextEventId != DEM_EVENT_ID_INVALID)
        {
#if (DEM_NUM_CMB_DTCS > 0U)
          Dem_EventIdType MasterEventId = DEM_GET_MASTER_EVID(NextEventId);
          if (NextEventId == MasterEventId)
#endif
          {
            GetFilter_J1939Dtc = Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_J1939,
                                                      NextEventId);
          }
        }


        if (GetFilter_J1939Dtc != DEM_NO_DTC)
        {
#if (DEM_OBD_Support == STD_ON)
          const Dem_DTCKindType DTCKind = Dem_GbiDTCKind(NextEventId);
#endif
          Dem_EventMemoryEntryPtrType EvMemEntryPtr;
          /* check if no DTC kind was filtered (DEM_DTC_KIND_ALL_DTCS)
           * or if kind filter matches */
#if (DEM_OBD_Support == STD_ON)
          if ((Dem_J1939DTCFilter.DTCKind == DEM_DTC_KIND_ALL_DTCS) ||
             (Dem_J1939DTCFilter.DTCKind == DTCKind) )
#endif
          {
            uint8 Node = Dem_InternalGetJ1939Node(NextEventId);
            if (Node == Dem_J1939DTCFilter.Node)
            {
#if ((DEM_OBD_Support == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
              if(FALSE == StatusFilterMatches)
#endif
              {
                /* in case of "DEM_J1939DTC_PERMANENT" the filter applies always because the
                 * EventID was taken from the permanent memory itself and there are no further
                 * filter criteria */
                StatusFilterMatches = Dem_ApplyJ1939DTCFilter(NextEventId,
                                        Dem_J1939DTCFilter.J1939DTCStatusFilter);
              }
              if (TRUE == StatusFilterMatches)
              {
                FilterResult = TRUE;
                /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.FilterRetOk,1 */
                Result = DEM_FILTERED_OK;
                /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.FilterOk,1 */
                *J1939DTC = GetFilter_J1939Dtc;
                /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFilteredDTC.OccCnt,1 */

                /*
                 * ENTER critical section to protect the event memory entry
                 *       call-context: any
                 */
                DEM_ENTER_EXCLUSIVE_AREA();

                if (TRUE == Dem_SearchForEntry(
                              NextEventId, &EvMemEntryPtr, NULL_PTR))
                {
                  *OccurenceCounter = (EvMemEntryPtr->OccCtr >= 126U) ?
                                        126U : EvMemEntryPtr->OccCtr;
                }

                /*
                 * LEAVE critical section
                 */
                DEM_EXIT_EXCLUSIVE_AREA();

              }
            }
          }
        }

        /* update NextItem for next call in filter */
        Dem_J1939DTCFilter.NextItem++;
      }
    }
  }

  DBG_DEM_J1939DCMGETNEXTFILTEREDDTC_EXIT(Result, J1939DTC, OccurenceCounter);
  return Result;
}

#endif /* (DEM_J1939_READING_DTC_SUPPORT == STD_ON) */

#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
/*--------------------------[Dem_J1939DcmClearDTC]--------------------------*/

FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  uint8                          node)
{
  Dem_ReturnClearDTCType Result = DEM_ASR42_CLEAR_FAILED;

  DBG_DEM_J1939DCMCLEARDTC_ENTRY(DTCTypeFilter, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmClearDTC, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmClearDTC, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((DTCTypeFilter != DEM_J1939DTC_CLEAR_ALL) &&
           (DTCTypeFilter != DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmClearDTC, DEM_E_PARAM_DATA);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmClearDTC, DEM_E_WRONG_CONFIGURATION);
    Result = DEM_CLEAR_WRONG_DTC;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean IsNewClearing = TRUE;

    DEM_ENTER_EXCLUSIVE_AREA();
    if (Dem_ClearDTCResult[DEM_VIRTUAL_CLIENT_J1939] != DEM_CLEAR_NO_RESULT)
    {
      /* there is a valid Dem_ClearDTCResult of a running or finished clearing process */
      /* possible values: DEM_PENDING, E_OK, DEM_WRONG_DTC, DEM_CLEAR_MEMORY_ERROR */

      /* we need to additionally check for node and filter */
      if((Dem_ClearDtcAsyncStatus.Dem_J1939Node == node) &&
         (Dem_ClearDtcAsyncStatus.Dem_J1939DTCTypeFilter == DTCTypeFilter))
      {
        /* This is an identical call to the Dem_J1939DcmClearDTC that resulted in
         * Dem_ClearDTCResult[DEM_VIRTUAL_CLIENT_J1939] value, handle normally */
        /* !LINKSTO Dem.ASR41.SWS_Dem_00663,1 */
        Result = Dem_ClearDTCResult[DEM_VIRTUAL_CLIENT_J1939];
        if (Result != DEM_PENDING)
        {
          /* clearing operation done, reset result */
          Dem_ClearDTCResult[DEM_VIRTUAL_CLIENT_J1939] = DEM_CLEAR_NO_RESULT;
        }
      }
      else
      {
        /* different node or filter, Dem_ClearDTCResult not modified */
        /* !LINKSTO Dem.ASR41.SWS_Dem_00662,1 */
        Result = DEM_CLEAR_BUSY;
      }

      IsNewClearing = FALSE;
    }
    DEM_EXIT_EXCLUSIVE_AREA();

    /* check if an async ClearDTC was started */
    if (TRUE == IsNewClearing)
    {
      /* no pending Dem_ClearDTCResult -> this is a new clearing process for
       * DEM_VIRTUAL_CLIENT_J1939 */
      Result = Dem_J1939DcmStartClearDTC(DTCTypeFilter, node);
    }
  }

  DBG_DEM_J1939DCMCLEARDTC_EXIT(Result, DTCTypeFilter, node);
  return Result;
}

#endif /*(DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON) */

#if ((DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
     (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON))
/*-------------------[Dem_J1939DcmSetFreezeFrameFilter]---------------------*/

FUNC(Dem_ReturnSetFilterType, DEM_CODE) Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind,
  uint8                                node)
{
  Dem_ReturnSetFilterType Result = DEM_WRONG_FILTER;

  DBG_DEM_J1939DCMSETFREEZEFRAMEFILTER_ENTRY(FreezeFrameKind, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetFreezeFrameFilter, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetFreezeFrameFilter,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetFreezeFrameFilter,
                     DEM_E_WRONG_CONFIGURATION);
  }
  else if (FreezeFrameKind > DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetFreezeFrameFilter, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.DemJ1939DcmFF,1 */
    if (FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME)
    {
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.MaskAttributes,1 */
      /* DM04 Freeze Frame Kind */
      Dem_J1939FreezeFrameFilter.NextItem = 1U;
      Dem_J1939FreezeFrameFilter.FreezeFrameKind = FreezeFrameKind;
      Dem_J1939FreezeFrameFilter.Node = node;
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.FilterAccepted_J1939DcmSetFreezeFrameFilter,1 */
      Dem_J1939FreezeFrameFilter.IsFilterValid = TRUE;
      Result = DEM_FILTER_ACCEPTED;
    }
    else
    {
      /* Resetting the filter criteria when unsupported FreezeFrameKind is requested */
      Dem_J1939FreezeFrameFilter.NextItem = 1U;
      Dem_J1939FreezeFrameFilter.FreezeFrameKind = DEM_J1939DCM_FREEZEFRAME;
      Dem_J1939FreezeFrameFilter.Node = 0U;
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.FilterAccepted_J1939DcmSetFreezeFrameFilter,1 */
      Dem_J1939FreezeFrameFilter.IsFilterValid = FALSE;

      /* DM24 and DM25 are not implemented yet */
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.DemJ1939DcmExpFF.WrongFilter,1 */
      Result = DEM_WRONG_FILTER;
    }
  }

  DBG_DEM_J1939DCMSETFREEZEFRAMEFILTER_EXIT(Result, FreezeFrameKind, node);
  return Result;
}

/*---------------------[Dem_J1939DcmGetNextFreezeFrame]---------------------*/

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) Dem_J1939DcmGetNextFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  OccurenceCounter,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.NoMatchedFreezeFrame,2 */
  Dem_ReturnGetNextFilteredElementType Result =
    DEM_FILTERED_NO_MATCHING_ELEMENT;

  DBG_DEM_J1939DCMGETNEXTFREEZEFRAME_ENTRY(
    J1939DTC, OccurenceCounter, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((J1939DTC == NULL_PTR) || (OccurenceCounter == NULL_PTR) ||
           (DestBuffer == NULL_PTR) || (BufSize == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFreezeFrame, DEM_E_PARAM_POINTER);
  }
  else if (Dem_J1939FreezeFrameFilter.IsFilterValid == FALSE)
  {
    /* !LINKSTO Dem.DetReport.WrongConditionJ1939DcmGetNextFreezeFrame,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFreezeFrame,
                     DEM_E_WRONG_CONDITION);
  }
  else
#endif
  {
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.FilterAccepted_J1939DcmSetFreezeFrameFilter,1 */
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.FilterAccepted_DemInit,1 */
    /* Deviation TASKING-2 */
    if (Dem_J1939FreezeFrameFilter.IsFilterValid != FALSE)
    {
      *J1939DTC = (uint32)DEM_NO_DTC;
      *OccurenceCounter = (uint8)127U;

      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.FilteredFreezeFrame,1 */
      /* search for first DTC fulfilling the filter criterion */
#if ( DEM_NUM_J1939FFSPNS > 0U )
      while ( (Dem_J1939FreezeFrameFilter.NextItem <= DEM_MAX_EVENTID) &&
              (Result == DEM_FILTERED_NO_MATCHING_ELEMENT) )
      {
        Dem_EventIdType NextEventId;
#if (DEM_NUM_CMB_DTCS > 0U)
        Dem_EventIdType MasterEventId;
#endif
        uint32 CurrJ1939Dtc = DEM_NO_DTC;
        NextEventId = (Dem_EventIdType)Dem_J1939FreezeFrameFilter.NextItem;
#if (DEM_NUM_CMB_DTCS > 0U)
        MasterEventId = DEM_GET_MASTER_EVID(NextEventId);
        if (NextEventId == MasterEventId)
#endif
        {
          CurrJ1939Dtc = Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_J1939,
                                              NextEventId);
        }
        /* check if current event has a configured J1939 DTC and, it is a master in case of combined DTC */
#if (DEM_NUM_CMB_DTCS > 0U)
        if ((CurrJ1939Dtc != DEM_NO_DTC) && (NextEventId == MasterEventId))
#else
        if (CurrJ1939Dtc != DEM_NO_DTC)
#endif
        {
          uint8 Node = Dem_InternalGetJ1939Node(NextEventId);
          /* check if current event belong to requested node, and J1939 Freeze frame requested */
          if ((Node == Dem_J1939FreezeFrameFilter.Node) &&
              (Dem_J1939FreezeFrameFilter.FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME) )
          {
            Dem_EventMemoryEntryPtrType EvMemEntryPtr;

            /*
            * ENTER critical section to protect the event memory entry
            *       call-context: any
            */
            DEM_ENTER_EXCLUSIVE_AREA();

            /* retrieve J1939 FF data */
            Result = Dem_CollectJ1939FFInfo(
                       NextEventId, &EvMemEntryPtr,BufSize, DestBuffer);

            if ( Result == DEM_FILTERED_OK)
            { /* data retrieved successfully */
              /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.MatchingDTC,1 */
              *J1939DTC = CurrJ1939Dtc;
              /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.MatchingOC,1 */
              if ((EvMemEntryPtr->OccCtr) >= 126U)
              {
                /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.OCCNotVal,2 */
                *OccurenceCounter = 126U;
              }
              else
              {
                /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.MatchingDTC,1 */
                *OccurenceCounter = EvMemEntryPtr->OccCtr;
              }
            }
            /* DEM_FILTERED_PENDING case not implemented as function call is synchronous,
             * and J1939Dcm handle one request at a time */

            /*
             * LEAVE critical section
             */
            DEM_EXIT_EXCLUSIVE_AREA();

          }
        }

        /* update NextItem for next call in filter */
        Dem_J1939FreezeFrameFilter.NextItem++;
      }
#endif /* DEM_NUM_J1939FFSPNS > 0U */
    }
    /* Result remains DEM_FILTERED_NO_MATCHING_ELEMENT because
     * FreezeFrameKind not valid */
  }
#if ((DEM_NUM_J1939FFSPNS == 0U) && (DEM_DEV_ERROR_DETECT == STD_OFF))
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
#endif

  DBG_DEM_J1939DCMGETNEXTFREEZEFRAME_EXIT(
    Result, J1939DTC, OccurenceCounter, DestBuffer, BufSize);
  return Result;
}

#if (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON)
/*--------------------[Dem_J1939DcmGetNextSPNInFreezeFrame]-----------------*/

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) Dem_J1939DcmGetNextSPNInFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) SPNSupported,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  SPNDataLength)
{
  Dem_ReturnGetNextFilteredElementType Result = DEM_FILTERED_NO_MATCHING_ELEMENT;

  DBG_DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_ENTRY(SPNSupported, SPNDataLength);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextSPNInFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextSPNInFreezeFrame,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((SPNSupported == NULL_PTR) || (SPNDataLength == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextSPNInFreezeFrame,
                     DEM_E_PARAM_POINTER);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(SPNSupported);
    TS_PARAM_UNUSED(SPNDataLength);
  }

  DBG_DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_EXIT(Result,
    SPNSupported, SPNDataLength);

  return Result;
}
#endif /* (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON)*/
#endif/* ((DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
          (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON)) */


#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
/*-----------------------[Dem_J1939DcmSetRatioFilter]-----------------------*/

FUNC(Dem_ReturnSetFilterType, DEM_CODE) Dem_J1939DcmSetRatioFilter(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) IgnitionCycleCounter,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) OBDMonitoringConditionsEncountered,
  uint8 node)
{
  Dem_ReturnSetFilterType Result = DEM_WRONG_FILTER;

  DBG_DEM_J1939DCMSETRATIOFILTER_ENTRY(
    IgnitionCycleCounter, OBDMonitoringConditionsEncountered, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetRatioFilter, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetRatioFilter, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((IgnitionCycleCounter == NULL_PTR) ||
           (OBDMonitoringConditionsEncountered == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetRatioFilter, DEM_E_PARAM_POINTER);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmSetRatioFilter,
                     DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(IgnitionCycleCounter);
    TS_PARAM_UNUSED(OBDMonitoringConditionsEncountered);
    TS_PARAM_UNUSED(node);
  }

  DBG_DEM_J1939DCMSETRATIOFILTER_EXIT(
    Result, IgnitionCycleCounter, OBDMonitoringConditionsEncountered, node);

  return Result;
}

/*--------------------[Dem_J1939DcmGetNextFilteredRatio]--------------------*/

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) Dem_J1939DcmGetNextFilteredRatio(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SPN,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Numerator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Denominator)
{
  Dem_ReturnGetNextFilteredElementType Result = DEM_FILTERED_NO_MATCHING_ELEMENT;

  DBG_DEM_J1939DCMGETNEXTFILTEREDRATIO_ENTRY(SPN, Numerator, Denominator);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredRatio, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredRatio,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((SPN == NULL_PTR) ||
           (Numerator == NULL_PTR) ||
           (Denominator == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextFilteredRatio,
                     DEM_E_PARAM_POINTER);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(SPN);
    TS_PARAM_UNUSED(Numerator);
    TS_PARAM_UNUSED(Denominator);
  }

  DBG_DEM_J1939DCMGETNEXTFILTEREDRATIO_EXIT(
    Result, SPN, Numerator, Denominator);

  return Result;
}
#endif /* (DEM_J1939_RATIO_SUPPORT == STD_ON) */

#if (DEM_J1939_READINESS1_SUPPORT == STD_ON)
/*------------------[Dem_J1939DcmReadDiagnosticReadiness1]------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness1(
  P2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, AUTOMATIC) DataValue,
  uint8 node)
{
  Std_ReturnType Result = E_NOT_OK;
#if ( (DEM_OBD_Support == STD_ON) && \
      (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) )
  /* initialize internal variable used for calculating support and status bytes
   * for continuously and non-continuously monitored systems */
  uint8 DM5[DEM_DM5_READINESS_SIZE] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
  uint32 RGSupported;
  uint32 RGReady;
#endif

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS1_ENTRY(DataValue, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness1, DEM_E_UNINIT);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness1,
                     DEM_E_WRONG_CONFIGURATION);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness1,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DataValue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness1,
                     DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.ActiveTroubleCodes,1 */
    DataValue->ActiveTroubleCodes = Dem_GetNumberJ1939DTCs(
                                      DEM_J1939DTC_ACTIVE,
                                      DEM_DTC_KIND_ALL_DTCS,
                                      node);
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.PreviouslyActiveTroubleCodes,1 */
    DataValue->PreviouslyActiveDiagnosticTroubleCodes =
       Dem_GetNumberJ1939DTCs(
        DEM_J1939DTC_PREVIOUSLY_ACTIVE,
        DEM_DTC_KIND_ALL_DTCS,
        node);
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.OBDCompliance,2 */
    DataValue->OBDCompliance = Dem_ObdCompliancyPID1CByte;
    /* mark all ReadinessGroups as not checked */
#if ( (DEM_OBD_Support == STD_ON) && \
      (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) )
    /* !LINKSTO dsn.Dem.ReadinessStatus.ComputationOnRetrieval,1 */
    /* compute readiness support and status of all the applicable groups */
    Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_J1939READINESS1,
                                 node,
                                 &RGSupported,
                                 &RGReady);

    Dem_RgpMapOutputData(RGSupported, RGReady, DEM_RGP_RGMASK_J1939READINESS1, Dem_RGBitPosJ1939Readiness1, &DM5[DEM_READINESS_DATABYTE_0]);

    /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.SupportBit,1 */
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.NoncontMonitoredSystems.Support,1 */
    DataValue->NonContinuouslyMonitoredSystemsSupport = (uint16)DM5[DEM_READINESS_DATABYTE_1] |
                                                        ((uint16)DM5[DEM_READINESS_DATABYTE_2] << 8);
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.NoncontMonitoredSystems.Status,1 */
    DataValue->NonContinuouslyMonitoredSystemsStatus = (uint16)DM5[DEM_READINESS_DATABYTE_3] |
                                                       ((uint16)DM5[DEM_READINESS_DATABYTE_4] << 8);
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.ContMonitoredSystems.SupportAndStatus,1 */
    DataValue->ContinuouslyMonitoredSystemsSupport_Status = DM5[DEM_READINESS_DATABYTE_0];
    /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.StatusBitNotSupported,1 */
#else
    /* Setting the values to zero if DEM_OBD_SUPPORT is OFF */
    /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.OBDComplianceNonOBDECU,1 */
    /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.NonOBDDevice,1 */
    /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.StatusBitNotSupported,1 */
    DataValue->NonContinuouslyMonitoredSystemsSupport = 0U;
    DataValue->NonContinuouslyMonitoredSystemsStatus = 0U;
    DataValue->ContinuouslyMonitoredSystemsSupport_Status = 0U;
#endif /* ( (DEM_OBD_Support == STD_ON) && \
            (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) ) */

    Result = E_OK;
  }

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS1_EXIT(Result, DataValue, node);

  return Result;
}
#endif /* (DEM_J1939_READINESS1_SUPPORT == 0U) */

#if (DEM_J1939_READINESS2_SUPPORT == STD_ON)
/*------------------[Dem_J1939DcmReadDiagnosticReadiness2]------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness2(
  P2VAR(Dem_J1939DcmDiagnosticReadiness2Type, AUTOMATIC, DEM_APPL_DATA) DataValue,
  uint8 node)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS2_ENTRY(DataValue, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness2, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness2,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DataValue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness2,
                     DEM_E_PARAM_POINTER);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness2,
                     DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(DataValue);
    TS_PARAM_UNUSED(node);
  }

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS2_EXIT(Result, DataValue, node);

  return Result;
}
#endif /* (DEM_J1939_READINESS2_SUPPORT == STD_ON) */

#if (DEM_J1939_READINESS3_SUPPORT == STD_ON)
/*------------------[Dem_J1939DcmReadDiagnosticReadiness3]------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness3(
  P2VAR(Dem_J1939DcmDiagnosticReadiness3Type, AUTOMATIC, DEM_APPL_DATA) DataValue,
  uint8 node)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS3_ENTRY(DataValue, node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness3, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness3,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DataValue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness3,
                     DEM_E_PARAM_POINTER);
  }
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmReadDiagnosticReadiness3,
                     DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(DataValue);
    TS_PARAM_UNUSED(node);
  }

  DBG_DEM_J1939DCMREADDIAGNOSTICREADINESS3_EXIT(Result, DataValue, node);

  return Result;
}
#endif /* (DEM_J1939_READINESS3_SUPPORT == STD_ON) */

#if (DEM_J1939_DM31_SUPPORT == STD_ON)
/*--------------------[Dem_J1939DcmFirstDTCwithLampStatus]------------------*/

FUNC(void, DEM_CODE) Dem_J1939DcmFirstDTCwithLampStatus(uint8 node)
{
  DBG_DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_ENTRY(node);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmFirstDTCwithLampStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmFirstDTCwithLampStatus,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (FALSE == DEM_J1939_NODE_EXIST(node))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmFirstDTCwithLampStatus, DEM_E_PARAM_DATA);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(node);
  }

  DBG_DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_EXIT(node);
}

/*--------------------[Dem_J1939DcmGetNextDTCwithLampStatus]----------------*/

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) Dem_J1939DcmGetNextDTCwithLampStatus(
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, AUTOMATIC) LampStatus,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)                 J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)                  OccurenceCounter)
{
  Dem_ReturnGetNextFilteredElementType Result = DEM_FILTERED_NO_MATCHING_ELEMENT;

  DBG_DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_ENTRY(
    LampStatus, J1939DTC, OccurenceCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextDTCwithLampStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextDTCwithLampStatus,
                     DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ((LampStatus == NULL_PTR) ||
           (J1939DTC == NULL_PTR) ||
           (OccurenceCounter == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_J1939DcmGetNextDTCwithLampStatus,
                     DEM_E_PARAM_POINTER);
  }
  else
#endif
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(LampStatus);
    TS_PARAM_UNUSED(J1939DTC);
    TS_PARAM_UNUSED(OccurenceCounter);
  }

  DBG_DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_EXIT(Result,
    LampStatus, J1939DTC, OccurenceCounter);

  return Result;
}
#endif /* (DEM_J1939_DM31_SUPPORT == STD_ON)*/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[internal function definitions]=========================*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)

#if ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
     (defined DEM_PIL_ID) || (defined DEM_MIL_ID))
/*---------------------[Dem_J1939InternalGetLampStatus]---------------------*/

STATIC FUNC(Dem_IndicatorStatusType, DEM_CODE) Dem_J1939InternalGetLampStatus(
  Dem_IndicatorIdType IndicatorId)
{
  Dem_IndicatorStatusType Status = DEM_INDICATOR_OFF;
  DBG_DEM_J1939INTERNALGETLAMPSTATUS_ENTER(IndicatorId);

  switch (IndicatorId)
  {
#ifdef DEM_AWIL_ID
    case DEM_AWIL_ID:
#endif
#ifdef DEM_RSIL_ID
    case DEM_RSIL_ID:
#endif
#ifdef DEM_PIL_ID
    case DEM_PIL_ID:
#endif
#ifdef DEM_MIL_ID
    case DEM_MIL_ID:
#endif

    {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
      Dem_EventIdType EventId;

      for (EventId = 1U; EventId <= DEM_MAX_EVENTID; EventId++)
      {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if (Dem_GbiEvAvailable(EventId) == FALSE)
        {
          /* event is disabled so the getting of status shall be skipped */
        }
        else
#endif
        {
          const Dem_IndicatorGrpIdxType IndicatorClassIdx =
            Dem_GbiIndicatorClassIndex(EventId);

          /* check for valid indicator index and prevent calibration error */
          if (IndicatorClassIdx < DEM_INDICATOR_UNUSED)
          {
            const Dem_IndicatorIdxType IndicatorClassIdxStart =
              Dem_IndicatorGroups[IndicatorClassIdx];
            const Dem_IndicatorIdxType IndicatorClassIdxEnd =
              Dem_IndicatorGroups[IndicatorClassIdx + 1U];
            Dem_IndicatorIdxType Idx;

            for (Idx = IndicatorClassIdxStart; Idx < IndicatorClassIdxEnd; Idx++)
            {
              CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
                &Dem_IndicatorClasses[Idx];
              if ((IndicatorClass->IndicatorId == IndicatorId) &&
                  (IndicatorClass->Enabled == TRUE) )
              {
                if ( DEM_IS_BIT_SET_IN_ARRAY(
                       DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorClass->IndicatorId],
                       EventId) )
                {
                  /* !LINKSTO dsn.Dem.J1939.IndicatorBehaviorMapping,1 */
                  Dem_IndicatorStatusType Status_Temp = IndicatorClass->Behaviour;
#ifdef DEM_MIL_ID
                  switch(IndicatorClass->Behaviour)
                  {
                    case DEM_INDICATOR_BLINK_CONT:
                    {
                      Status_Temp = DEM_INDICATOR_FAST_FLASH;
                      break;
                    }
                    case DEM_INDICATOR_BLINKING:
                    {
                      Status_Temp = DEM_INDICATOR_SLOW_FLASH;
                      break;
                    }
                    default:
                    {
                      Status_Temp = IndicatorClass->Behaviour;
                      break;
                    }
                  }
#endif /* #ifdef DEM_MIL_ID */
                  if (Status == DEM_INDICATOR_OFF)
                  {
                    /* set initial behaviour */
                    Status = Status_Temp;
                  }
                  else
                  {
                    /* !LINKSTO Dem.SWS_Dem_00859,1 */
                    /* !LINKSTO Dem.SWS_Dem_00860,1 */
                    /* !LINKSTO Dem.SWS_Dem_00861,1 */
                    /* !LINKSTO Dem.SWS_Dem_00863,1 */
                    /* !LINKSTO Dem.SWS_Dem_00864,1 */
                    /* !LINKSTO Dem.SWS_Dem_00865,1 */
                    /* !LINKSTO Dem.SWS_Dem_00867,1 */
                    /* !LINKSTO Dem.SWS_Dem_00868,1 */
                    /* !LINKSTO Dem.SWS_Dem_00869,1 */
                    /* !LINKSTO Dem.SWS_Dem_00871,1 */
                    /* !LINKSTO Dem.SWS_Dem_00872,1 */
                    /* !LINKSTO Dem.SWS_Dem_00873,1 */
                    if (Status_Temp > Status)
                    {
                      /* as different behaviours are requested, SW-C is responsible
                       * for behaviour selection */
                      Status = Status_Temp;
                    }
                  }
                }
                /* else: no linked event requests its warning indicator
                 * -> status remains same */
                /* !LINKSTO Dem.SWS_Dem_00862,1 */
                /* !LINKSTO Dem.SWS_Dem_00866,1 */
                /* !LINKSTO Dem.SWS_Dem_00870,1 */
                /* !LINKSTO Dem.SWS_Dem_00858,1 */
              }
            }
          }
        }
      }
      /* calibration is disabled and event availability is not considered */
#else
      {
        P2CONST(Dem_IndicatorLinkType, AUTOMATIC, DEM_CONST) IndicatorLink;
        Dem_IndicatorIdxType LinkIdx;

        /* point to first indicator link of according data structures */
        IndicatorLink = &Dem_IndicatorLink[Dem_IndicatorDesc[IndicatorId].StartIdx];

        for (LinkIdx = 0U; LinkIdx < Dem_IndicatorDesc[IndicatorId].Number; ++LinkIdx)
        {
          const Dem_CounterDataIdxType CounterDataIdx =
            LinkIdx + Dem_IndicatorDesc[IndicatorId].StartIdx;

          if (DEM_IS_BIT_SET_IN_ARRAY(
                DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_INDICATOR_DEFAULT_COUNTER],
                CounterDataIdx))
            {
              Dem_IndicatorStatusType Status_Temp = IndicatorLink[LinkIdx].Behaviour;
#ifdef DEM_MIL_ID
              switch(IndicatorLink[LinkIdx].Behaviour)
              {
                case DEM_INDICATOR_BLINK_CONT:
                {
                  Status_Temp = DEM_INDICATOR_FAST_FLASH;
                  break;
                }
                case DEM_INDICATOR_BLINKING:
                {
                  Status_Temp = DEM_INDICATOR_SLOW_FLASH;
                  break;
                }
                default:
                {
                  Status_Temp = IndicatorLink[LinkIdx].Behaviour;
                  break;
                }
              }
#endif /* #ifdef DEM_MIL_ID */
              if (Status == DEM_INDICATOR_OFF)
              {
                /* set initial behaviour */
                Status = Status_Temp;
              }
              else
              {
                /* !LINKSTO Dem.SWS_Dem_00859,1 */
                /* !LINKSTO Dem.SWS_Dem_00860,1 */
                /* !LINKSTO Dem.SWS_Dem_00861,1 */
                /* !LINKSTO Dem.SWS_Dem_00863,1 */
                /* !LINKSTO Dem.SWS_Dem_00864,1 */
                /* !LINKSTO Dem.SWS_Dem_00865,1 */
                /* !LINKSTO Dem.SWS_Dem_00867,1 */
                /* !LINKSTO Dem.SWS_Dem_00868,1 */
                /* !LINKSTO Dem.SWS_Dem_00869,1 */
                /* !LINKSTO Dem.SWS_Dem_00871,1 */
                /* !LINKSTO Dem.SWS_Dem_00872,1 */
                /* !LINKSTO Dem.SWS_Dem_00873,1 */
                if (Status_Temp > Status)
                {
                  /* Check current indicator status behavior */
                  Status = Status_Temp;
                }
              }
            }
            /* else: no linked event requests its warning indicator
             * -> status remains same */
            /* !LINKSTO Dem.SWS_Dem_00858,1 */
            /* !LINKSTO Dem.SWS_Dem_00862,1 */
            /* !LINKSTO Dem.SWS_Dem_00866,1 */
            /* !LINKSTO Dem.SWS_Dem_00870,1 */
          }
        }
#endif
      break;
    }
    /* CHECK: NOPARSE */
    default:
      DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_J1939DcmSetDTCFilter);
      break;
    /* CHECK: PARSE */
  }

  DBG_DEM_J1939INTERNALGETLAMPSTATUS_EXIT(Status, IndicatorId);
  /* return lamp status value */
  return Status;
}
#endif /* ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) ||
           (defined DEM_PIL_ID) || (defined DEM_MIL_ID)) */

/*-------------------[Dem_J1939GetInternalLampStatusBytes]------------------*/

STATIC FUNC(void, DEM_CODE) Dem_J1939GetInternalLampStatusBytes(
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA)  LampStatus)
{
#if ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
     (defined DEM_PIL_ID) || (defined DEM_MIL_ID))
  Dem_IndicatorStatusType IndicatorStatus = 0U;
  Dem_J1939DcmLampStatusType SingleLampStatus = 0U;
#endif

  Dem_J1939DcmLampStatusType InternalLampStatus = 0U;

  DBG_DEM_J1939DCMGETINTERNALLAMPSTATUSBYTES_ENTRY(LampStatus);

#if (defined DEM_MIL_ID)
  IndicatorStatus = Dem_J1939InternalGetLampStatus(DEM_MIL_ID);
  SingleLampStatus = Dem_J1939GetLampBits(IndicatorStatus);
  InternalLampStatus |= (SingleLampStatus << DEM_MIL_OFFSET);
#else
  /* !LINKSTO Dem.J1939.LampStatus.Unavailable,1 */
  InternalLampStatus |= (Dem_J1939DcmLampStatusType)(DEM_J1939_INDICATOR_CONT_UNAVAILABLE << DEM_MIL_OFFSET);
#endif /* (defined DEM_MIL_ID) */

#if (defined DEM_AWIL_ID)
  IndicatorStatus = Dem_J1939InternalGetLampStatus(DEM_AWIL_ID);
  SingleLampStatus = Dem_J1939GetLampBits(IndicatorStatus);
  InternalLampStatus |= (SingleLampStatus << DEM_AWIL_OFFSET);
#else
  /* !LINKSTO Dem.J1939.LampStatus.Unavailable,1 */
  InternalLampStatus |= (Dem_J1939DcmLampStatusType)(DEM_J1939_INDICATOR_CONT_UNAVAILABLE << DEM_AWIL_OFFSET);
#endif /* (defined DEM_AWIL_ID) */

#if (defined DEM_RSIL_ID)
  IndicatorStatus = Dem_J1939InternalGetLampStatus(DEM_RSIL_ID);
  SingleLampStatus = Dem_J1939GetLampBits(IndicatorStatus);
  InternalLampStatus |= (SingleLampStatus << DEM_RSIL_OFFSET);
#else
  /* !LINKSTO Dem.J1939.LampStatus.Unavailable,1 */
  InternalLampStatus |= (Dem_J1939DcmLampStatusType)(DEM_J1939_INDICATOR_CONT_UNAVAILABLE << DEM_RSIL_OFFSET);
#endif /* (defined DEM_RSIL_ID) */

#if (defined DEM_PIL_ID)
  /* PIL offset not required since it is placed in the lower most bits */
  IndicatorStatus = Dem_J1939InternalGetLampStatus(DEM_PIL_ID);
  SingleLampStatus = Dem_J1939GetLampBits(IndicatorStatus);
  InternalLampStatus |= SingleLampStatus;
#else
  /* !LINKSTO Dem.J1939.LampStatus.Unavailable,1 */
  InternalLampStatus |= (Dem_J1939DcmLampStatusType)DEM_J1939_INDICATOR_CONT_UNAVAILABLE;
#endif /* (defined DEM_PIL_ID) */

  *LampStatus = InternalLampStatus;

  DBG_DEM_J1939DCMGETINTERNALLAMPSTATUSBYTES_EXIT(LampStatus);
}

#if ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
     (defined DEM_PIL_ID) || (defined DEM_MIL_ID))
STATIC FUNC(Dem_J1939DcmLampStatusType, DEM_CODE) Dem_J1939GetLampBits(
  Dem_IndicatorStatusType     IndicatorStatus)
{
  Dem_J1939DcmLampStatusType Result = 0U;

  DBG_DEM_J1939GETLAMPBITS_ENTRY(IndicatorStatus);

  switch (IndicatorStatus)
  {
    case DEM_INDICATOR_OFF:
      /* !LINKSTO Dem.SWS_Dem_00859,1 */
      /* !LINKSTO Dem.SWS_Dem_00867,1 */
      /* !LINKSTO Dem.SWS_Dem_00863,1 */
      /* !LINKSTO Dem.SWS_Dem_00871,1 */
      /* The indicator is off */
      Result = (Dem_J1939DcmLampStatusType)DEM_J1939_INDICATOR_CONT_UNAVAILABLE;
      break;
    case DEM_INDICATOR_CONTINUOUS:
      /* The indicator is continuously on */
      Result = (Dem_J1939DcmLampStatusType)(DEM_J1939_INDICATOR_ACTIVE | DEM_J1939_INDICATOR_CONT_UNAVAILABLE);
      break;
    case DEM_INDICATOR_SLOW_FLASH:
      /* The indicator is slow flashing */
      /* The slow flash status is represented by zeros so no need for any operation. */
      Result = (Dem_J1939DcmLampStatusType)DEM_J1939_INDICATOR_ACTIVE;
      break;
    case DEM_INDICATOR_FAST_FLASH:
      /* The indicator is fast flashing */
      Result = (Dem_J1939DcmLampStatusType)(DEM_J1939_INDICATOR_ACTIVE | DEM_J1939_INDICATOR_FAST_FLASH);
      break;
    /* CHECK: NOPARSE */
    default:
      /* unreachable state. */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_J1939DcmSetDTCFilter);
      break;
    /* CHECK: PARSE */
  }

  DBG_DEM_J1939GETLAMPBITS_EXIT(IndicatorStatus, Result);

  return Result;
}
#endif /* ((defined DEM_AWIL_ID) || (defined DEM_RSIL_ID) || \
           (defined DEM_PIL_ID) || (defined DEM_MIL_ID)) */
#endif /* (DEM_J1939_READING_DTC_SUPPORT == STD_ON) */

#if ((DEM_J1939_READING_DTC_SUPPORT == STD_ON) || \
     (DEM_J1939_READINESS1_SUPPORT == STD_ON) || \
     (DEM_J1939_CLEAR_DTC_SUPPORT==STD_ON))
/*-------------------------[Dem_ApplyJ1939DTCFilter]------------------------*/

STATIC FUNC(boolean, DEM_CODE) Dem_ApplyJ1939DTCFilter(
  Dem_EventIdType                                                EventId,
  Dem_J1939DcmDTCStatusFilterType                                J1939Filter)
{
  boolean Result = FALSE;
  Dem_DTCStatusMaskType DTCStatus;

  DBG_DEM_APPLYJ1939DTCFILTER_ENTRY(EventId, J1939Filter);

  DTCStatus = DEM_GET_DTC_STATUS(EventId);
#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_GET_MASTER_EVID(EventId) == EventId)
#endif
  {
    /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.FilterCriteria,1 */
    switch(J1939Filter)
    {
      case DEM_J1939DTC_ACTIVE:
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
        if ((Dem_IsEventsMILIndicatorActive(EventId) == TRUE) ||
            DEM_IS_EACH_BIT_SET(DTCStatus, DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF))
#else
        if (DEM_IS_EACH_BIT_SET(DTCStatus, DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF))
#endif

        {
          Result = TRUE;
        }
        break;
      case DEM_J1939DTC_PREVIOUSLY_ACTIVE:
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
        if ((Dem_IsEventsMILIndicatorActive(EventId) == FALSE) &&
            DEM_IS_EACH_BIT_MATCH(DTCStatus,
                                  DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF,
                                  DEM_UDS_STATUS_CDTC))
#else
        if (DEM_IS_EACH_BIT_MATCH(DTCStatus,
                                  DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF,
                                  DEM_UDS_STATUS_CDTC))
#endif


        {
          Result = TRUE;
        }
        break;
      case DEM_J1939DTC_PENDING:
        if (DEM_IS_ST_BIT_PDTC_SET(DTCStatus))
        {
          Result = TRUE;
        }
        break;
      case DEM_J1939DTC_CURRENTLY_ACTIVE:
        if (DEM_IS_ST_BIT_TF_SET(DTCStatus))
        {
          Result = TRUE;
        }
        break;
      /* CHECK: NOPARSE */
      default:
        /* Unreachable state */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_J1939DcmGetNextFilteredDTC);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DEM_APPLYJ1939DTCFILTER_EXIT(Result, EventId, J1939Filter);

  return Result;
}
#endif /* (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ||
          (DEM_J1939_READINESS1_SUPPORT == STD_ON)  ||
          (DEM_J1939_CLEAR_DTC_SUPPORT==STD_ON) */

#if ((DEM_J1939_READING_DTC_SUPPORT == STD_ON) || \
     (DEM_J1939_READINESS1_SUPPORT == STD_ON))
/*-------------------------[Dem_GetNumberJ1939DTCs]-------------------------*/

STATIC FUNC(uint8, DEM_CODE) Dem_GetNumberJ1939DTCs(
  Dem_J1939DcmDTCStatusFilterType  DTCStatusFilter,
  Dem_DTCKindType                  DTCKind,
  uint8                            Node)
{
  Dem_EventIdType EventId = DEM_EVENT_ID_INVALID;
  uint16 ItemIdx = 1U;
  uint16 MaxIdx = DEM_MAX_EVENTID;
  uint8 EventCnt = 0U;
  uint8 MaxDTCCount = DEM_J1939_MAX_DTC_COUNT_VALUE;
  uint32 J1939Dtc = DEM_NO_DTC;
#if (DEM_OBD_Support == STD_ON)
  Dem_DTCKindType DTCKindVar;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
  Dem_EventIdType MasterEventId;
#endif

  DBG_DEM_GETNUMBERJ1939DTCS_ENTRY(DTCStatusFilter, DTCKind, Node);

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
  if(DEM_J1939DTC_PERMANENT == DTCStatusFilter)
  {
#if ((DEM_OBD_Support == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
    /* loop through the permanent entries */
    MaxIdx = DEM_MAX_NUMBER_EVENT_ENTRY_PER - 1U;
    ItemIdx = 0U;
#else
    /* do not enter the loop, if permanent memory is not configured */
    MaxIdx = 0U;
#endif
  }
#endif

  /* check that the number of reported DTCs does not exceed the maximum allowed value */
  /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNumberOfFilteredDTC.MaxValue,1 */
  /* !LINKSTO Dem.J1939.ReadDiagnosticReadiness1.ReportedTroubleCodesMaxValue,1 */
  while ((ItemIdx <= MaxIdx) && (EventCnt < MaxDTCCount))
  {
    boolean AllowCntIncrement = FALSE;
    /* !LINKSTO Dem_OBD_0001,2 */
#if ((DEM_OBD_Support == STD_ON) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) && \
     (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
    if(DEM_J1939DTC_PERMANENT == DTCStatusFilter)
    {
      /* Only events stored in the permanent memory are relevant. Therefore only
       * permanent entries are checked to reduce runtime. */
      const Dem_PermanentMemoryEntryType Entry =
      Dem_EventMemoryPermanent[ItemIdx];

      EventId = DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry);

      /* !LINKSTO Dem.J1939.PermanentDTC.NonVolatileStorage,1 */
      if ( (EventId != DEM_EVENT_ID_INVALID) &&
           (Dem_EventMemoryPermanentNonVolatileStored[ItemIdx] !=
              DEM_PERMANENT_MEMORY_NV_STORED) )
      {
        /* event not taken into account, because it is not yet stored non-volatile */
        EventId = DEM_EVENT_ID_INVALID;
      }
      AllowCntIncrement = TRUE;
    }
    else
#endif
    {
      /* loop through all events */
      EventId = ItemIdx;
    }
    if (EventId != DEM_EVENT_ID_INVALID)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      MasterEventId = DEM_GET_MASTER_EVID(EventId);
      if (EventId == MasterEventId)
#endif
      {
        J1939Dtc = Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_J1939,
                                        EventId);
      }
#if (DEM_NUM_CMB_DTCS > 0U)
      if ((J1939Dtc != DEM_NO_DTC) && (EventId == MasterEventId))
#else
      if (J1939Dtc != DEM_NO_DTC)
#endif
      {
#if (DEM_OBD_Support == STD_ON)
        DTCKindVar = Dem_GbiDTCKind(EventId);
        /* check if no DTC kind was filtered (DEM_DTC_KIND_ALL_DTCS)
         * or if kind filter matches */
        if ((DTCKind == DEM_DTC_KIND_ALL_DTCS) ||
            (DTCKind == DTCKindVar))
#else
        TS_PARAM_UNUSED(DTCKind);
#endif
        {
          if (Node == Dem_InternalGetJ1939Node(EventId))
          {
#if ((DEM_OBD_Support == STD_ON) && \
     (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) && \
     (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
            if (FALSE == AllowCntIncrement)
#endif
            {
              AllowCntIncrement = Dem_ApplyJ1939DTCFilter(EventId,
                                                          DTCStatusFilter);
            }
            if (TRUE == AllowCntIncrement)
            {
              EventCnt++;
            }
          }
        }
      }
    }
    /* update EventId for next check */
    ItemIdx++;
  }
  DBG_DEM_GETNUMBERJ1939DTCS_EXIT(EventCnt, DTCStatusFilter, DTCKind, Node);

  return EventCnt;
}

#endif /* ((DEM_J1939_READING_DTC_SUPPORT == STD_ON) ||
           (DEM_J1939_READINESS1_SUPPORT == STD_ON) */


#if ( ( DEM_J1939_READINESS1_SUPPORT == STD_ON) && (DEM_OBD_Support == STD_ON) && \
      (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) )
/*---------------------[Dem_RGCalcPerEventJ1939Readiness1]------------------*/
FUNC(void, DEM_CODE) Dem_RGCalcPerEventJ1939Readiness1(
  Dem_OBDReadinessGroupType                         RgId,
  Dem_EventIdType                                   EventId,
  uint8                                             Filter,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Supported,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Ready,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus)
{
  uint8 EventNode;

  DBG_DEM_RGCALCPEREVENTJ1939READINESS1_ENTRY(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);

  TS_PARAM_UNUSED(RgId);

  EventNode = Dem_InternalGetJ1939Node(EventId);
  /* Check if the node is the requested node */
  /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.Calculation,1 */
  if (EventNode == Filter)
  {
#if (DEM_NUM_CMB_DTCS > 0U)
      Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
    if (*RGCalcStatus == DEM_RG_CALC_FORCE_COMPLETE)
    {
      *Supported = TRUE;
      *Ready = TRUE;
      *RGCalcStatus = DEM_RG_CALC_FINISHED;
    }
    else
    {
      if (*RGCalcStatus == DEM_RG_CALC_NOT_STARTED)
      {
        *Supported = TRUE;
        *Ready = TRUE;
        *RGCalcStatus = DEM_RG_CALC_ONGOING;
      }
#if (DEM_NUM_CMB_DTCS > 0U)
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.J1939Readiness1.TestedSinceLastClear,1 */
        /* check if the monitor was not completed since last clear or if the event
         * has a pending status */
        if (DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_TNCSLC |
                                           DEM_UDS_STATUS_PDTC))
        {
           /* set readiness status to not complete */
           *Ready = FALSE;
        }
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.J1939Readiness1.MIL,1 */
        /* check if event is confirmed (CDTC bit is set) */
        if (DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_CDTC))
        {
          /* event has caused MIL on, set readiness status to complete */
          *Ready = TRUE;
          /* if at least one event in this readiness group is confirmed, set the
           * state of readiness group calculation to finished so that readiness
           * status is not calculated for consecutive events */
          *RGCalcStatus = DEM_RG_CALC_FINISHED;
        }

#else

        Dem_EventIdType CmbEventId;
        Dem_CmbDTCEvLnkType CmbEvIdx;
        Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
        /* loop through all the events and calculate the combined status */
        for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
        {
          CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
          /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.ExcludedEvents,2 */
          if (Dem_GbiEvAvailable(CmbEventId) == TRUE)
#endif
          {
            /* !LINKSTO Dem.ReadinessStatus.Computation.ReadDiagnosticReadiness1.MonitoringStatusBit,1 */
            /* !LINKSTO Dem.ReadinessStatus.Computation.J1939Readiness1.TestedSinceLastClear,1 */
            /* check if the monitor was not completed since last clear or if the event
             * has a pending status */
            if (DEM_IS_ANY_EV_ST_BIT_SET(CmbEventId,
                                         DEM_UDS_STATUS_TNCSLC |
                                         DEM_UDS_STATUS_PDTC))
            {
              /* set readiness status to not complete */
              *Ready = FALSE;
            }
            /* !LINKSTO Dem.ReadinessStatus.Computation.J1939Readiness1.MIL,1 */
            /* check if event is confirmed (CDTC bit is set) */
            if (DEM_IS_EV_ST_BIT_CDTC_SET(CmbEventId))
            {
              /* event has caused MIL on, set readiness status to complete */
              *Ready = TRUE;
              /* if at least one event in this readiness group is confirmed, set the
               * state of readiness group calculation to finished so that readiness
               * status is not calculated for consecutive events */
              *RGCalcStatus = DEM_RG_CALC_FINISHED;
              break;
            }
          }
        }
#endif /* (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) */
      }
      else
#endif
      {
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.J1939Readiness1.TestedSinceLastClear,1 */
        /* !LINKSTO Dem.ReadinessStatus.Computation.J1939Readiness1.TestedSinceLastClear,1 */
        /* check if the monitor was not completed since last clear or if the event
         * has a pending status */
        if (DEM_IS_ANY_EV_ST_BIT_SET(EventId,
                                     DEM_UDS_STATUS_TNCSLC |
                                     DEM_UDS_STATUS_PDTC))
        {
          /* set readiness status to not complete */
          *Ready = FALSE;
        }
        /* !LINKSTO Dem.ReadinessStatus.Computation.J1939Readiness1.MIL,1 */
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.J1939Readiness1.MIL,1 */
        /* check if event is confirmed (CDTC bit is set) */
        if (DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
        {
          /* event has caused MIL on, set readiness status to complete */
          *Ready = TRUE;
          /* if at least one event in this readiness group is confirmed, set the
           * state of readiness group calculation to finished so that readiness
           * status is not calculated for consecutive events */
          *RGCalcStatus = DEM_RG_CALC_FINISHED;
        }
      }
    }
  }

  DBG_DEM_RGCALCPEREVENTJ1939READINESS1_EXIT(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);
}

#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
FUNC(uint8, DEM_CODE) Dem_GetJ1939RGPNodeIdx(uint8 Node)
{
  uint8 NodeIdx;
  uint8 Result = DEM_J1939_INVALID_NODE_IDX;

  DBG_DEM_GETJ1939RGPNODEIDX_ENTRY(Node);

  /* Deviation TASKING-1 */
  for(NodeIdx = 0; NodeIdx < DEM_RGP_NUM_J1939_READINESS_NODES; NodeIdx++)
  {
    if(Dem_RGP_J1939NmNodes[NodeIdx] == Node)
    {
      Result = NodeIdx;
      break;
    }
  }

  DBG_DEM_GETJ1939RGPNODEIDX_EXIT(Node, NodeIdx);

  return Result;
}
#endif /* (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON) */
#endif /* ( ( DEM_J1939_READINESS1_SUPPORT == STD_ON) && (DEM_OBD_Support == STD_ON) &&
            (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) ) */

#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
/*------------------------[Dem_J1939DcmStartClearDTC]-----------------------*/

STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_J1939DcmStartClearDTC(
  Dem_J1939DcmSetClearFilterType   DTCTypeFilter,
  uint8                                     Node)
{
  Dem_ReturnClearDTCType Result = DEM_CLEAR_PENDING;

  DBG_DEM_J1939DCMSTARTCLEARDTC_ENTRY(DTCTypeFilter, Node);

  /*
   * ENTER critical section to protect RunState RMW (service lock)
   *       call-context: Dcm (Task), Rte (Task)
  */
  DEM_ENTER_EXCLUSIVE_AREA();

  if (DEM_CLEARDTC_STATE_IDLE == Dem_ClearDtcAsyncStatus.RunState)
  {
    /* set the Result to be reported by Dem_J1939DcmClearDTC() */
    Dem_ClearDTCResult[DEM_VIRTUAL_CLIENT_J1939] = Result;
    /* initialize ClearDTCAsyncStatus */
    Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_STARTED;
    /* keep service Id to know which function started the clearing process (lock) */
    Dem_ClearDtcAsyncStatus.ClientId = DEM_VIRTUAL_CLIENT_J1939;
    Dem_ClearDtcAsyncStatus.Dem_J1939DTCTypeFilter = DTCTypeFilter;
    Dem_ClearDtcAsyncStatus.Dem_J1939Node = Node;
    /* event clearing is suspended, store current context */
    Dem_ClearDtcAsyncStatus.NextEventId = 1U;
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_ClearDtcAsyncStatus.NextCmbEvIdx = 0U;
#endif
    /* status modified flag is always present */
    Dem_ClearDtcAsyncStatus.AnyEventModified.EvSt = FALSE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* data modified flag is only present for NONVOLATILE_FINISH */
    Dem_ClearDtcAsyncStatus.AnyEventModified.EvMemEntry = FALSE;

#endif
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
    if (DTCTypeFilter == DEM_J1939DTC_CLEAR_ALL)
    {
      Dem_RgpNotifyClearReadiness(DEM_SID_J1939DcmClearDTC,
                            DEM_CLEAR_START,
                            Dem_ClearDtcAsyncStatus.Dem_J1939Node);
    }
#endif
  }
  else
  {
    /* report Result BUSY */
    /* !LINKSTO Dem.ASR41.SWS_Dem_00662,1 */
    Result = DEM_CLEAR_BUSY;
  }

  /*
   * LEAVE critical section
  */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_J1939DCMSTARTCLEARDTC_EXIT(Result, DTCTypeFilter, Node);
  return Result;
}

/*----------------------[Dem_J1939DcmClearFilterCheck]----------------------*/

FUNC(boolean, DEM_CODE) Dem_J1939DcmClearFilterCheck(
  Dem_J1939DcmSetClearFilterType   DTCTypeFilter,
  uint8                                     Node,
  Dem_EventIdType                        EventId)
{
  boolean Result = FALSE;
  uint32 J1939Dtc;

  DBG_DEM_J1939DCMCLEARFILTERCHECK_ENTRY(DTCTypeFilter, Node, EventId);

    J1939Dtc = Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_J1939,
                                    EventId);

  if (J1939Dtc != DEM_NO_DTC)
  {
    Dem_J1939DcmDTCStatusFilterType DTCStatusFilter = DEM_J1939DTC_ACTIVE;
    uint8 EventNode;
    boolean FilterResult = FALSE;

    switch (DTCTypeFilter)
    {
      case DEM_J1939DTC_CLEAR_ALL:
        DTCStatusFilter = DEM_J1939DTC_ACTIVE;
      break;
      case DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE:
        DTCStatusFilter = DEM_J1939DTC_PREVIOUSLY_ACTIVE;
      break;
      /* CHECK: NOPARSE */
      default:
        /* unreachable state. */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_J1939DcmClearDTC);
      break;
      /* CHECK: PARSE */
    }

    EventNode = Dem_InternalGetJ1939Node(EventId);
    FilterResult = Dem_ApplyJ1939DTCFilter(EventId, DTCStatusFilter);

    if ((TRUE == FilterResult) && (EventNode == Node))
    {
      Result = TRUE;
    }
  }

  DBG_DEM_J1939DCMCLEARFILTERCHECK_EXIT(Result, DTCTypeFilter, Node, EventId);

  return Result;
}
#endif /* DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON */

/*-------------------------[Dem_InternalGetJ1939DTC]------------------------*/

FUNC(uint32, DEM_CODE) Dem_InternalGetJ1939DTC(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_INTERNALGETJ1939DTC_ENTRY(EventId);

  DTC = (uint32)((Dem_EventJ1939DtcAndNode[DEM_DESC_J1939_IDX(EventId)]) & DEM_J1939_DTC_MASK);

  DBG_DEM_INTERNALGETJ1939DTC_EXIT(DTC, EventId);

  return DTC;
}

/*------------------------[Dem_InternalGetJ1939Node]------------------------*/

STATIC FUNC(uint8, DEM_CODE) Dem_InternalGetJ1939Node(Dem_EventIdType EventId)
{
  uint8 Node;
  uint8 NodeIdx;

  DBG_DEM_INTERNALGETJ1939NODE_ENTRY(EventId);

  NodeIdx = (uint8)((uint32)Dem_EventJ1939DtcAndNode[DEM_DESC_J1939_IDX(EventId)] >> DEM_J1939_NODE_IDX_OFFSET);
  Node = Dem_J1939NmNodeIds[NodeIdx];

  DBG_DEM_INTERNALGETJ1939NODE_EXIT(Node, EventId);
  return Node;
}

#if (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)
/*------------------[Dem_InitJ1939FreezeFrameFilter]------------------------*/

FUNC(void, DEM_CODE) Dem_InitJ1939FreezeFrameFilter(void)
{
  /* This function is called from Dem_Init always (after Dem is
   * pre-initialized as well as after post-initialized) */
  DBG_DEM_INITJ1939FREEZEFRAMEFILTER_ENTRY();

  Dem_J1939FreezeFrameFilter.IsFilterValid = FALSE;

  DBG_INITJ1939FREEZEFRAMEFILTER_EXIT();
}
#endif

/*------------------[Dem_InitJ1939DtcFilter]---------------------------*/

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_InitJ1939DtcFilter(void)
{
  /* This function is called from Dem_Init always (after Dem is
   * pre-initialized as well as after post-initialized) */
  DBG_DEM_INITJ1939DTCFILTER_ENTRY();

  Dem_J1939DTCFilter.IsFilterValid = FALSE;

  DBG_INITJ1939DTCFILTER_EXIT();
}
#endif

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* (DEM_J1939_SUPPORT == STD_ON) */
