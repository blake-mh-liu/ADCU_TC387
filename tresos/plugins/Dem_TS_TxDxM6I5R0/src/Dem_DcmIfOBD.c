/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \version 6.5.8
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* this file contains definitions of OBD related APIs provided by Dem to the
 * Dcm. */

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
 * W549: condition is always false
 *
 * Reason:
 * The 'if' condition will always be 'FALSE' in tests where OBD is enabled and all the events
 * belong to the DEM_OBD_RDY_NONE and DemCalibrationSupport is enabled.
 */

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 2.1 (required)
 *    "A project shall not contain unreachable code."
 *
 *    Reason:
 *    Run time check for the active OBD variant is always DEM_OBD_VARIANT_OBDONUDS
 *    when switching/selection of the OBD variant is not supported.
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                        /* EB specific standard types */
#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <TSMem.h>                          /* EB specific memory functions */

#include <Dem_Int.h>             /* module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

/*==================[macros]================================================*/
#if (defined DEM_PID01PID41_SIZE)
#error DEM_PID01PID41_SIZE already defined
#endif
/** \brief Size of PID $01/$41 as per SAE J1979 */
#define DEM_PID01PID41_SIZE 0x04U

#if (defined DEM_PIDF501_SIZE)
#error DEM_PIDF501_SIZE already defined
#endif
/** \brief Size of PID $F501 as per SAE J1979-2 */
#define DEM_PIDF501_SIZE 0x06U

#if (defined DEM_ENGINETYPE_MASK)
#error DEM_ENGINETYPE_MASK already defined
#endif
/** \brief Bitmask to identify DemOBDEngineType in PID $01/$41 */
#define DEM_ENGINETYPE_MASK 0x08U

#if (defined DEM_CMPRCMPT_MASK)
#error DEM_CMPRCMPT_MASK already defined
#endif
/** \brief Bitmask to identify CMPRCMPT in PID $01/$41 */
#define DEM_CMPRCMPT_MASK 0x04U

#if (defined DEM_RGP_UNUSED_FILTER_ATTRIBUTE)
#error DEM_RGP_UNUSED_FILTER_ATTRIBUTE already defined
#endif
/** \brief Value for unused filter specific attribute */
#define DEM_RGP_UNUSED_FILTER_ATTRIBUTE 0x00U

#if (defined DEM_RGP_RESET_READINESS_IN_PROGRESS)
#error DEM_RGP_RESET_READINESS_IN_PROGRESS already defined
#endif
/** \brief Macro indicating bit position of ResetReadinessInProgress bit */
#define DEM_RGP_RESET_READINESS_IN_PROGRESS  0x10000000U

#if (defined DEM_RGP_CLEAR_IN_PROGRESS)
#error DEM_RGP_CLEAR_IN_PROGRESS already defined
#endif
/** \brief Macro indicating bit position of ClearDTCInProgress bit */
#define DEM_RGP_CLEAR_IN_PROGRESS  0x20000000U

#if (defined DEM_RGP_CLEARED_ON_RETRIEVAL)
#error DEM_RGP_CLEARED_ON_RETRIEVAL already defined
#endif
/** \brief Macro indicating bit position of ReadinessClearedOnRetrieval bit */
#define DEM_RGP_CLEARED_ON_RETRIEVAL  0x40000000U

#if (defined DEM_RGP_CLEARED_ON_DYC_START)
#error DEM_RGP_CLEARED_ON_DYC_START already defined
#endif
/** \brief Macro indicating bit position of ReadinessClearedOnDCYStart bit */
#define DEM_RGP_CLEARED_ON_DYC_START  0x80000000U

#if (defined DEM_RGP_RESET_READINESS_IN_PROGRESS_MASK)
#error DEM_RGP_RESET_READINESS_IN_PROGRESS_MASK already defined
#endif
/** \brief Macro holds mask value indicating readiness status bits set to "not
 *         complete" along with ReadinessClearedOnRetrieval,
 *         ReadinessClearedOnDCYStart and
 *         ResetReadinessInProgress bits set to 1 */
#define DEM_RGP_RESET_READINESS_IN_PROGRESS_MASK \
  (DEM_RGP_RESET_READINESS_IN_PROGRESS | \
   DEM_RGP_CLEARED_ON_RETRIEVAL | \
   DEM_RGP_CLEARED_ON_DYC_START)

#if (defined DEM_RGP_CLEAR_IN_PROGRESS_MASK)
#error DEM_RGP_CLEAR_IN_PROGRESS_MASK already defined
#endif
/** \brief Macro holds mask value indicating readiness status bits set to "not
 *         complete" along with ReadinessClearedOnRetrieval,
 *         ReadinessClearedOnDCYStart and ClearDTCInProgress bits set to 1 */
#define DEM_RGP_CLEAR_IN_PROGRESS_MASK \
  (DEM_RGP_CLEAR_IN_PROGRESS | \
   DEM_RGP_CLEARED_ON_RETRIEVAL | \
   DEM_RGP_CLEARED_ON_DYC_START)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#if (DEM_OBD_Support == STD_ON)

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if (defined DEM_MIL_ID)
/** \brief Function to update MIL status in byte A of PID $01, $F401 and $F501
 **
 ** This function shall update the status of MIL derived from the event
 ** status into byte A, bit 7 of PID $01, $F401 and $F501
 **
 ** \param[inout] PIDByteA  Buffer pointing to byte A of a PID $01, $F401 and
 **                         $F501.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateMILStatusInPID(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PIDByteA);
#endif /* (defined DEM_MIL_ID) */

/** \brief Function to calculate the number of confirmed DTCs in byte A of
 ** PID $01, $F401 and $F501
 **
 ** This function calculates and updates the number of confirmed
 ** emission-related DTCs stored into byte A, bits 0 - 6 of a PID $01, $F401
 ** and $F501.
 **
 ** \param[inout] PIDByteA  Buffer pointing to byte A of PID $01, $F401 and
 **                         $F501.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateDTCCntInPID(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PIDByteA);

#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
/** \brief Function to check if the readiness group is forced to complete
 **
 ** This function evaluates if the status of a given readiness group is forced
 ** to complete.
 **
 ** \param[in] RgId         Identifier of the readiness group which needs to
 **                         be evaluated if it is forced to complete.
 **
 ** \return Boolean value indicating whether the readiness group is forced to
 **         complete.
 ** \retval TRUE  Readiness group is forced to complete
 ** \retval FALSE Readiness group is not forced to complete
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_IsRGForcedComplete(
  Dem_OBDReadinessGroupType RgId);

/** \brief Function to initialize the readiness calculation status
 **
 ** This function initializes the calculation status for the given readiness
 ** group based on the RG complete status.
 **
 ** \param[in]  RgId          Identifier of the readiness group which needs to
 **                           be evaluated if it is forced to complete.
 ** \param[in]  RGReady       Positional bit mask containing the complete status
 **                           of the readiness group.
 ** \param[out] RGCalcStatus  Status indicating if the calculation of the readiness
 **                           group is required or not.
 **                           DEM_RG_CALC_NOT_STARTED: calculation is required.
 **                           DEM_RG_CALC_FORCE_COMPLETE: calculation not required.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitRGCalcStatus(
  Dem_OBDReadinessGroupType                         RgId,
  uint32                                            RGReady,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus);

/** \brief Function to calculate readiness information of each event
 **
 ** The function checks the readiness of the given event and in sequence
 ** re-calculates the status (support and ready) of the corresponding
 ** readiness group for PID $01 and PID $F501.
 **
 ** \param[in]    RgId          Id of the calculated readiness group to which
 **                             the event belongs.
 ** \param[in]    EventId       Identifies the Dem event.
 ** \param[in]    UnusedFilterAttribute  Filter specific attribute which is
 **                             currently used only for J1939Readiness1.
 ** \param[inout] Supported     Prior (IN) and new (OUT) support status of the
 **                             readiness group.
 ** \param[inout] Ready         Prior (IN) and new (OUT) ready status of the
 **                             readiness group.
 ** \param[inout] RGCalcStatus  The current calculation status for this RG.
 **                             DEM_RG_CALC_NOT_STARTED: Readiness calculation
 **                             for a given readiness group has not yet
 **                             started.
 **                             DEM_RG_CALC_ONGOING: Readiness calculation is
 **                             on going for all associated events.
 **                             DEM_RG_CALC_FINISHED: Readiness calculation for
 **                             given group is successful and fully finished.
 **                             DEM_RG_CALC_FORCE_COMPLETE: Readiness is forced
 **                             to complete.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RGCalcPerEventPIDFx01(
  Dem_OBDReadinessGroupType                         RgId,
  Dem_EventIdType                                   EventId,
  uint8                                             Filter,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Supported,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Ready,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus);

/** \brief Function to calculate readiness information of each event
 **
 ** The function checks the readiness of the given event and in sequence
 ** re-calculates the status (support and ready) of the corresponding
 ** readiness group for PID $41.
 **
 ** \param[in]    RgId          Id of the calculated readiness group to which
 **                             the event belongs.
 ** \param[in]    EventId       Identifies the Dem event.
 ** \param[in]    UnusedFilterAttribute  Filter specific attribute which is
 **                             currently used only for J1939Readiness1.
 ** \param[inout] Supported     Prior (IN) and new (OUT) support status of the
 **                             readiness group.
 ** \param[inout] Ready         Prior (IN) and new (OUT) ready status of the
 **                             readiness group.
 ** \param[inout] RGCalcStatus  The current calculation status for this RG.
 **                             DEM_RG_CALC_NOT_STARTED: Readiness calculation
 **                             for a given readiness group has not yet
 **                             started.
 **                             DEM_RG_CALC_ONGOING: Readiness calculation is
 **                             on going for all associated events.
 **                             DEM_RG_CALC_FINISHED: Readiness calculation for
 **                             given group is successful and fully finished.
 **                             DEM_RG_CALC_FORCE_COMPLETE: Readiness is forced
 **                             to complete.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RGCalcPerEventPID41(
  Dem_OBDReadinessGroupType                         RgId,
  Dem_EventIdType                                   EventId,
  uint8                                             Filter,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Supported,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Ready,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus);

/** \brief Function to select a specific readiness type
 **
 ** The function initialize the variables used by Dem_RgpCalcSelectedReadiness()
 ** based on the selected readiness type.
 **
 ** \param[in]  ReadinessId       Internal readiness API Id.
 ** \param[in]  Node              Node specific attribute which is
 **                               currently used only for J1939Readiness1.
 ** \param[out] NeededGroupsMask  Mask indicating which readiness groups are
 **                               required for calculation.
 ** \param[out] CalcRGPerEventFnc Pointer to the PerEvent calculation
 **                               function that shall be used.
 ** \param[out] NvDataReadyStatus Pointer to the NvData.ReadinessStatus
 **                               array element used.
 ** \param[out] DTCFormat         Pointer to the relevant format.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_SelectReadiness(
  Dem_ReadinessType                                    ReadinessId,
  uint8                                                Node,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)                  NeededGroupsMask,
  P2VAR(Dem_RGProcessEvPtrType, AUTOMATIC, AUTOMATIC)  CalcRGPerEventFnc,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC)                  NvDataReadyStatusIdx,
  P2VAR(Dem_DTCFormatType, AUTOMATIC, AUTOMATIC)       DTCFormat);

/** \brief Internal function to calculate the readiness information
 **
 ** This function calculates the readiness information in two scenarios.
    Scenario 1: When readiness calibration support is disabled
      The algorithm loops over all events to check if the event needs to be
      considered for the readiness calculation. If it needs to be considered,
      the PID specific readiness status calculation function is called for the
      event. The readiness group specific RGCalcStatus, the calculated
      Supported and Ready bits are temporarily stored in arrays (indexed with
      RgId) until all events/all RGs are processed.
    Scenario 2: When readiness calibration support is enabled
      The algorithm loops over all readiness groups, starting from readiness
      group at index 1 to check if this group needs to be considered for
      calculation. If it needs to be considered, PID specific readiness status
      calculation is called for each event until all events that belong to
      this group are processed, or the readiness calculation for this
      readiness group is finished.
 **
 ** \param[in]   DTCFormat         Readiness calculation relevant DTC format.
 ** \param[in]   Node              Node specific attribute which is
 **                                currently used only for J1939Readiness1.
 ** \param[in]   NeededGroupsMask  Mask indicating which readiness groups are
 **                                required for calculation.
 ** \param[in]   CalcRGPerEventFnc Pointer to the PerEvent calculation
 **                                function that shall be used.
 ** \param[out]  LocalRGSupported  Positional bit mask containing the support
 **                                status of the readiness group.
 ** \param[out]  LocalRGReady      Positional bit mask containing the complete
 **                                status of the readiness group.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_CalcReadiness(
  boolean                              DTCFormat,
  uint8                                Node,
  uint32                               NeededGroupsMask,
  Dem_RGProcessEvPtrType               CalcRGPerEventFnc,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGSupported,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGReady);

/** \brief Function to get a positional bit mask of the forced ready groups
 **
 ** This function returns a positional bit mask of the forced readiness groups.
 **
 ** \return uint32 Ready status positional bit mask with the bits corresponding
 **                to the forced ready groups set.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_GetForceReadyBitMask(void);
#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */
/** \brief Function to get the readiness calculation relevant DTC format
 **
 ** This functions gets the DTC format of the DTC that needs to be considered
 ** for PID $01/$41/$F501 readiness calculation. The relevant DTC depends on
 ** the active OBD variant and UDS/OBD DTC separation.
 **
 ** \return Dem_DTCFormatType DTC format to be considered in readiness calculation.
 ** \retval DEM_DTC_FORMAT_OBD        OBD Classic
 ** \retval DEM_DTC_FORMAT_UDS        OBDonUDS
 ** \retval DEM_DTC_FORMAT_OBD_3BYTE  OBDonUDS with OBD/UDS DTC separation
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_DTCFormatType, DEM_CODE) Dem_GetRelevantDTCFormat(void);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
#endif /* (DEM_OBD_Support == STD_ON) */

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*------------------[Dem_RGBitPosPID01PID41 array]--------------------------*/
#if (DEM_OBD_Support == STD_ON)
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

/* !LINKSTO dsn.Dem.RGP.BufferBitPositionMap,1 */
/** \brief Array containing the bit position information for the supported and
 ** ready status for all the readiness groups required by PID $01 and PID $41 */
STATIC CONST(Dem_RGStatusMappingType, DEM_CONST)
  Dem_RGBitPosPID01PID41[DEM_RGP_MAX_NUM_READINESS_GROUPS] =
{
  {/* RgId 0 - NONE */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 1 - CAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_0)
  },
  {/* RgId 2 - HTCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_1)
  },
  {/* RgId 3 - MISF */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_4)
  },
  {/* RgId 4 - EVAP */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_2)
  },
  {/* RgId 5 - SECAIR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_3)
  },
  {/* RgId 6 - FLSYS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_5)
  },
  {/* RgId 7 - EGSENS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_5),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_5)
  },
  {/* RgId 8 - EGR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_7),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_7)
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
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
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
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_0)
  },
  {/* RgId 17 - NOXCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_1)
  },
  {/* RgId 18 - BOOSTPR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_3)
  },
  {/* RgId 19 - NOXADSORB */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 20 - PMFLT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_6),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_6)
  },
  {/* RgId 21 - GPF */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_4),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_4)
  },
  {/* RgId 22 - O2SENS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_5),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_5)
  },
  {/* RgId 23 - O2SENSHT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_6),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_6)
  },
  {/* RgId 24 - AC */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
};

/*------------------[Dem_RGBitPosPIDF501 array]-----------------------------*/

#if (DEM_OBDONUDS_SUPPORT)
/* !LINKSTO dsn.Dem.RGP.BufferBitPositionMap,1 */
/** \brief Array containing the bit position information for the supported and
 ** ready status for all the readiness groups required by PID $F501 */
STATIC CONST(Dem_RGStatusMappingType, DEM_CONST)
  Dem_RGBitPosPIDF501[DEM_RGP_MAX_NUM_READINESS_GROUPS] =
{
  {/* RgId 0 - NONE */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 1 - CAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_4)
  },
  {/* RgId 2 - HTCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_6)
  },
  {/* RgId 3 - MISF */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_4)
  },
  {/* RgId 4 - EVAP */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_4)
  },
  {/* RgId 5 - SECAIR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_5)
  },
  {/* RgId 6 - FLSYS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_5)
  },
  {/* RgId 7 - EGSENS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_4)
  },
  {/* RgId 8 - EGR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_6)
  },
  {/* RgId 9 - PCV */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_5)
  },
  {/* RgId 10 - ECS */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_7)
  },
  {/* RgId 11 - CSER */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_5)
  },
  {/* RgId 12 - VVT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_3,DEM_BITPOS_7)
  },
  {/* RgId 13 - DOR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_0),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_4)
  },
  {/* RgId 14 - CMPRCMPT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_0,DEM_BITPOS_6)
  },
  {/* RgId 15 - OTHER */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_7)
  },
  {/* RgId 16 - HCCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_1),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_5)
  },
  {/* RgId 17 - NOXCAT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_1,DEM_BITPOS_7)
  },
  {/* RgId 18 - BOOSTPR */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_6)
  },
  {/* RgId 19 - NOXADSORB */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_2),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_4,DEM_BITPOS_6)
  },
  {/* RgId 20 - PMFLT */
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_3),
    DEM_BIT_POS_IN_ARRAY(DEM_READINESS_DATABYTE_2,DEM_BITPOS_7)
  },
  {/* RgId 21 - GPF */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 22 - O2SENS */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 23 - O2SENSHT */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
  {/* RgId 24 - AC */
    DEM_RGID_NOTSUPPORTED,
    DEM_RGID_NOTSUPPORTED
  },
};
#endif /* DEM_OBDONUDS_SUPPORT */

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */
#endif /* (DEM_OBD_Support == STD_ON) */
/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#if (DEM_INCLUDE_RTE == STD_ON)
#define Dem_START_SEC_CODE
#include <Dem_MemMap.h>
#else
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
#endif

#if (DEM_OBD_Support == STD_ON)

/*------------------[Dem_SetEventDisabled]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventDisabled(Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
  Dem_OBDReadinessGroupType RgId;
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
  uint16 EvOffset;
  uint16 NumOfEventsInRdyGrp;
  uint16 ArrayIndex;
#endif
#endif

  DBG_DEM_SETEVENTDISABLED_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if ( (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF) && \
      (DEM_EVENT_DISABLING_SUPPORT == STD_OFF) )
    TS_PARAM_UNUSED(EventId);
#endif
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(EventId) == FALSE)
    {
      /* event is disabled/not available so the disabling
      * of event shall be skipped */
      /* E_NOT_OK return value remains */
    }
    else
#endif
    {
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
      for (RgId = 1U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
      {
        /* check the positional readiness bit mask to ensure if the readiness
        * group is valid */
        if (DEM_IS_ANY_BIT_SET(DEM_RGP_RGMASK_PID01_PID41, (uint32) 1U << (RgId)))
        {
          /* find number of event slots that can be calibrated within the
          * readiness group segment */
#if ((DEM_OBD_CLASSIC_SUPPORT) && (DEM_OBD_CLASSIC_FIXED_SLOTS_SUPPORT == STD_ON))
          NumOfEventsInRdyGrp = DEM_MAX_EVENTS_PER_READINESS_GROUP;
          ArrayIndex = Dem_OBDReadinessGroupOffset[RgId] - NumOfEventsInRdyGrp;
#else
          NumOfEventsInRdyGrp = Dem_OBDReadinessGroupOffset[RgId] -
            Dem_OBDReadinessGroupOffset[RgId - 1U];
          ArrayIndex = Dem_OBDReadinessGroupOffset[RgId - 1U];
#endif

          /* Deviation TASKING-1 */
          for (EvOffset = 0U; EvOffset < NumOfEventsInRdyGrp; EvOffset++)
          {
            if (EventId == Dem_OBDReadinessGroup[ArrayIndex + EvOffset])
            {
              /* !LINKSTO dsn.Dem.ReadinessEnableStatus.CriticalSection,1 */
              /*
              * ENTER critical section to protect ReadinessEnableStatus
              *       call-context: SWC / CDD
              */
              DEM_ENTER_EXCLUSIVE_AREA();

              /* !LINKSTO Dem.ASR40.SWS_Dem_00348,1 */
              /* !LINKSTO dsn.Dem.OBDPidSupport.Dem_ReadinessEnableStatus_01,1 */
              /* set the readiness group of the event disabled */
              DEM_SET_READINESS_GROUP_DISABLED(RgId, Dem_NvData.ReadinessEnableStatus);

              /*
              * LEAVE critical section
              */
              DEM_EXIT_EXCLUSIVE_AREA();

              /* Move to the next readiness group */
              /* !LINKSTO Dem.DemEventOBDReadinessGroup.DisableReadinessGroup,1 */
              break;
            }
          }
        }
      }
#else
      /* Get the readiness group of the event */
      RgId = Dem_GbiOBDReadinessGroup(EventId);

      if ((DEM_IS_ANY_BIT_SET(DEM_RGP_RGMASK_PID01_PID41, (uint32) 1U << (RgId))))
      {
        /* !LINKSTO dsn.Dem.ReadinessEnableStatus.CriticalSection,1 */
        /*
        * ENTER critical section to protect ReadinessEnableStatus
        *       call-context: SWC / CDD
        */
        DEM_ENTER_EXCLUSIVE_AREA();

        /* !LINKSTO Dem.ASR40.SWS_Dem_00348,1, dsn.Dem.OBDPidSupport.Dem_ReadinessEnableStatus_01,1 */
        /* Set the readiness group of the event disabled */
        DEM_SET_READINESS_GROUP_DISABLED(RgId, Dem_NvData.ReadinessEnableStatus);

        /*
        * LEAVE critical section
        */
        DEM_EXIT_EXCLUSIVE_AREA();
      }
#endif /* #if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON) */
#endif /* #if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */
      Result = E_OK;
    }
  }
  DBG_DEM_SETEVENTDISABLED_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_OBD_Support == STD_ON) */


/*------------------[Dem_SetPtoStatus]--------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetPtoStatus(boolean PtoStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETPTOSTATUS_ENTRY(PtoStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetPtoStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetPtoStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ( (PtoStatus != TRUE) && (PtoStatus != FALSE) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetPtoStatus, DEM_E_PARAM_DATA);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PtoStatus);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
  }

  DBG_DEM_SETPTOSTATUS_EXIT(Result, PtoStatus);
  return Result;
}

/* !LINKSTO Dem_OBD_0001,2 */
#if (DEM_OBD_Support == STD_ON)
/*------------------[Dem_SetPfcCycleQualified]------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetPfcCycleQualified(void)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_SETPFCCYCLEQUALIFIED_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetPfcCycleQualified, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetPfcCycleQualified, DEM_E_WRONG_CONTEXT);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* set permanent fault status */
    /* !LINKSTO Dem_OBD_0028,1 */
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
    DEM_PFC_STATUS = TRUE;
#endif
  }

  DBG_DEM_SETPFCCYCLEQUALIFIED_EXIT(Result);
  return Result;
}

/*------------------[Dem_GetPfcCycleQualified]------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetPfcCycleQualified(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) isqualified)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_GETPFCCYCLEQUALIFIED_ENTRY(isqualified);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetPfcCycleQualified, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetPfcCycleQualified, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (isqualified == NULL_PTR)
  {
    /* !LINKSTO Dem_OBD_0079,1 */
    DEM_REPORT_ERROR(DEM_SID_GetPfcCycleQualified, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* get permanent fault status */
    /* !LINKSTO Dem_OBD_0078,1 */
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
    *isqualified = DEM_PFC_STATUS;
#else
    *isqualified = FALSE;
#endif
  }

  DBG_DEM_GETPFCCYCLEQUALIFIED_EXIT(Result, isqualified);
  return Result;
}

/*------------------[Dem_InitReadinessGroupProcessor]-----------------------*/

FUNC(void, DEM_CODE) Dem_InitReadinessGroupProcessor(void)
{
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
  uint8 NodeIdx;
#endif

  DBG_DEM_INITREADINESSGROUPPROCESSOR_ENTRY();

#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
  /* Deviation TASKING-1 */
  for(NodeIdx = 0; NodeIdx < DEM_RGP_NUM_J1939_READINESS_NODES; NodeIdx++)
  {
    /* Clear in progress bits */
    Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_BASE_IDX_J1939READINESS1 + NodeIdx] &=
      (~(DEM_RGP_CLEAR_IN_PROGRESS | DEM_RGP_RESET_READINESS_IN_PROGRESS));
  }
#endif
  /* Clear in progress bits */
  Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] &=
    (~(DEM_RGP_CLEAR_IN_PROGRESS | DEM_RGP_RESET_READINESS_IN_PROGRESS));

#if (DEM_OBDONUDS_SUPPORT)
  /* Clear in progress bits */
  Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] &=
    (~(DEM_RGP_CLEAR_IN_PROGRESS | DEM_RGP_RESET_READINESS_IN_PROGRESS));

#endif

  DBG_DEM_INITREADINESSGROUPPROCESSOR_EXIT();
}

FUNC(void, DEM_CODE) Dem_ResetReadiness(void)
{
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
  Dem_OBDReadinessGroupType RgId;
  uint16 EvOffset;
  uint16 NumOfEventsInRdyGrp;
  uint16 ArrayIndex;
#endif
  Dem_EventIdType EventId;
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_VARIANT_SELECTABLE == STD_OFF))
  uint32 RGConfigMask = DEM_RGP_RGMASK_PIDF501;
#else
  uint32 RGConfigMask = DEM_RGP_RGMASK_PID01_PID41;
#endif
#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */

  DBG_DEM_RESETREADINESS_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO dsn.Dem.OBDPidSupport.Dem_ResetReadiness_01,1 */
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetReadiness, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_ResetReadiness, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)

    /*
     * ENTER critical section to protect Dem_NvData.<PID>ReadyStatus
     *       call-context: Dem (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* Notify RGP with the start of reset readiness */
    Dem_RgpNotifyClearReadiness(DEM_SID_ResetReadiness,
                                DEM_CLEAR_START,
                                DEM_RGP_UNUSED_FILTER_ATTRIBUTE);

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
    /* run time check for the active OBD variant */
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
    {
      RGConfigMask = DEM_RGP_RGMASK_PIDF501;
    }
#endif

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
    for (RgId = 1U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
    {
      /* Deviation TASKING-1 */
      if (DEM_IS_ANY_BIT_SET(RGConfigMask, (uint32) 1U << (RgId)))
      {
#if ((DEM_OBD_CLASSIC_SUPPORT) && (DEM_OBD_CLASSIC_FIXED_SLOTS_SUPPORT == STD_ON))
        NumOfEventsInRdyGrp = DEM_MAX_EVENTS_PER_READINESS_GROUP;
        ArrayIndex = Dem_OBDReadinessGroupOffset[RgId] - NumOfEventsInRdyGrp;
#else
        /* find number of event slots that can be calibrated within the
         * readiness group segment */
        NumOfEventsInRdyGrp = Dem_OBDReadinessGroupOffset[RgId] -
          Dem_OBDReadinessGroupOffset[RgId - 1U];
        ArrayIndex = Dem_OBDReadinessGroupOffset[RgId - 1U];
#endif
        /* loop through all the assigned events within readiness group segment */
        for (EvOffset = 0U; EvOffset < NumOfEventsInRdyGrp; EvOffset++)
        {
          /* calculate Status Mask place outside the critical section */
          EventId = Dem_OBDReadinessGroup[ArrayIndex + EvOffset];

          if (DEM_EVENT_ID_INVALID != EventId)
          {
            P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_VAR) EventDTCStatusPtr;
            Dem_DTCStatusMaskType OldDTCStatusMask;
            Dem_DTCStatusMaskType NewDTCStatusMask;
#if (DEM_NUM_CMB_DTCS > 0U)
            if(EventId == DEM_GET_MASTER_EVID(EventId))
            {
              Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
              /* !LINKSTO Dem.OBD.ResetReadiness.CombinedEvents,1 */
              if (DEM_IS_DTC_COMBINED(DTCConfIdx))
              {
                Dem_EventIdType CmbEventId;
                Dem_CmbDTCEvLnkType CmbEvIdx;
                Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
                /* loop through all the events and calculate the combined status */
                for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
                {
                  Dem_EventStatusExtendedType OldCombinedStatus = 0U;
                  Dem_EventStatusExtendedType NewCombinedStatus = 0U;

                  CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];


                  EventDTCStatusPtr = &DEM_DTC_STATUS_MASKS[CmbEventId];

                  /*
                   * ENTER critical section to protect consistency of UDS Status Byte
                   */
                  DEM_ENTER_EXCLUSIVE_AREA();

                  OldDTCStatusMask = *EventDTCStatusPtr;
                  NewDTCStatusMask = OldDTCStatusMask;

                  if ( (!DEM_IS_ST_BIT_CDTC_SET(OldDTCStatusMask)) &&
                       (!DEM_IS_ST_BIT_PDTC_SET(OldDTCStatusMask)) )
                  {
                    DEM_SET_MASK(NewDTCStatusMask, DEM_UDS_STATUS_TNCSLC);
                    *EventDTCStatusPtr = NewDTCStatusMask;
                  }

                  OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
                  NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);

                  /*
                   * LEAVE critical section
                   */
                  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
                  if (OldDTCStatusMask != NewDTCStatusMask)
                  {
                    /* notify application if event status has changed */
                    Dem_CbTriggerOnEventStatus(CmbEventId, OldDTCStatusMask, NewDTCStatusMask);
                  }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */

                  if (OldCombinedStatus != NewCombinedStatus)
                  {
                    Dem_InternalCheckOnCmbDTCStatusChange(CmbEventId, OldCombinedStatus, NewCombinedStatus);
                  }
                }
              }
              else
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
              {
                EventDTCStatusPtr = &DEM_DTC_STATUS_MASKS[EventId];

                /*
                 * ENTER critical section to protect consistency of UDS Status Byte
                 */
                DEM_ENTER_EXCLUSIVE_AREA();

                OldDTCStatusMask = *EventDTCStatusPtr;
                NewDTCStatusMask = OldDTCStatusMask;

                if ( (!DEM_IS_ST_BIT_CDTC_SET(OldDTCStatusMask)) &&
                     (!DEM_IS_ST_BIT_PDTC_SET(OldDTCStatusMask)) )
                {
                  DEM_SET_MASK(NewDTCStatusMask, DEM_UDS_STATUS_TNCSLC);
                  *EventDTCStatusPtr = NewDTCStatusMask;
                }

                /*
                 * LEAVE critical section
                 */
                DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
                if (OldDTCStatusMask != NewDTCStatusMask)
                {
                  /* notify application if event status has changed */
                  Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
                }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */
              }
#if (DEM_NUM_CMB_DTCS > 0U)
            }
#endif
          }
        }
      }
    }
#else
    /* Deviation TASKING-1 */
    for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
    {
      /* Deviation TASKING-2 */
      if (DEM_IS_ANY_BIT_SET(RGConfigMask, (uint32) 1U <<
          Dem_GbiOBDReadinessGroup(EventId)))
      {
        Dem_DTCStatusMaskType OldDTCStatusMask;
        Dem_DTCStatusMaskType NewDTCStatusMask;

        P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_VAR) EventDTCStatusPtr;

#if (DEM_NUM_CMB_DTCS > 0U)
        if(EventId == DEM_GET_MASTER_EVID(EventId))
        {
          Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
          /* !LINKSTO Dem.OBD.ResetReadiness.CombinedEvents,1 */
          if (DEM_IS_DTC_COMBINED(DTCConfIdx))
          {
            Dem_EventIdType CmbEventId;
            Dem_CmbDTCEvLnkType CmbEvIdx;
            Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
            /* loop through all the events and calculate the combined status */
            for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
            {
              Dem_EventStatusExtendedType OldCombinedStatus = 0U;
              Dem_EventStatusExtendedType NewCombinedStatus = 0U;

              CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];


              EventDTCStatusPtr = &DEM_DTC_STATUS_MASKS[CmbEventId];

              /*
               * ENTER critical section to protect consistency of UDS Status Byte
               */
              DEM_ENTER_EXCLUSIVE_AREA();

              OldDTCStatusMask = *EventDTCStatusPtr;
              NewDTCStatusMask = OldDTCStatusMask;

              if ( (!DEM_IS_ST_BIT_CDTC_SET(OldDTCStatusMask)) &&
                   (!DEM_IS_ST_BIT_PDTC_SET(OldDTCStatusMask)) )
              {
                DEM_SET_MASK(NewDTCStatusMask, DEM_UDS_STATUS_TNCSLC);
                *EventDTCStatusPtr = NewDTCStatusMask;
              }

              OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
              NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);

              /*
               * LEAVE critical section
               */
              DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
              if (OldDTCStatusMask != NewDTCStatusMask)
              {
                /* notify application if event status has changed */
                Dem_CbTriggerOnEventStatus(CmbEventId, OldDTCStatusMask, NewDTCStatusMask);
              }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */

              if (OldCombinedStatus != NewCombinedStatus)
              {
                Dem_InternalCheckOnCmbDTCStatusChange(CmbEventId, OldCombinedStatus, NewCombinedStatus);
              }
            }
          }
          else
#endif
          {

            /* calculate Status Mask place outside the critical section */
            EventDTCStatusPtr = &DEM_DTC_STATUS_MASKS[EventId];

            /*
             * ENTER critical section to protect consistency of UDS Status Byte
             */
            DEM_ENTER_EXCLUSIVE_AREA();

            OldDTCStatusMask = *EventDTCStatusPtr;
            NewDTCStatusMask = OldDTCStatusMask;

            if ( (!DEM_IS_ST_BIT_CDTC_SET(OldDTCStatusMask)) &&
                 (!DEM_IS_ST_BIT_PDTC_SET(OldDTCStatusMask)) )
            {
              DEM_SET_MASK(NewDTCStatusMask, DEM_UDS_STATUS_TNCSLC);
              *EventDTCStatusPtr = NewDTCStatusMask;
            }

            /*
             * LEAVE critical section
             */
            DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            if (OldDTCStatusMask != NewDTCStatusMask)
            {
              /* notify application if event status has changed */
              Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
            }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */
          }
#if (DEM_NUM_CMB_DTCS > 0U)
        }
#endif
      }
    }
#endif /* (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON) */

    /*
     * ENTER critical section to protect Dem_NvData.<PID>ReadyStatus
     *       call-context: Dem (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* Notify RGP with the finish of reset readiness */
    Dem_RgpNotifyClearReadiness(DEM_SID_ResetReadiness,
                                DEM_CLEAR_FINISH,
                                DEM_RGP_UNUSED_FILTER_ATTRIBUTE);

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */
  }

  DBG_DEM_RESETREADINESS_EXIT();
}

#endif /* (DEM_OBD_Support == STD_ON) */

#if (DEM_INCLUDE_RTE == STD_ON)
#define Dem_STOP_SEC_CODE
#include <Dem_MemMap.h>
#else
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
#endif

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ((DEM_IUMPR_FUNCTIONS_ENABLED == STD_ON) && (DEM_OBD_Support == STD_ON))
/*------------------[Dem_RepIUMPRFaultDetect]-------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRFaultDetect(
  Dem_RatioIdType RatioID)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_REPIUMPRFAULTDETECT_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRFaultDetect, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRFaultDetect, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
  }

  DBG_DEM_REPIUMPRFAULTDETECT_EXIT(Result, RatioID);
  return Result;
}

/*------------------[Dem_RepIUMPRDenLock]-----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenLock(Dem_RatioIdType RatioID)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_REPIUMPRDENLOCK_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenLock, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenLock, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
  }

  DBG_DEM_REPIUMPRDENLOCK_EXIT(Result, RatioID);
  return Result;
}

/*------------------[Dem_RepIUMPRDenRelease]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(Dem_RatioIdType RatioID)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_REPIUMPRDENRELEASE_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenRelease, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenRelease, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
   }

  DBG_DEM_REPIUMPRDENRELEASE_EXIT(Result, RatioID);
  return Result;
}

#endif /* (DEM_IUMPR_FUNCTIONS_ENABLED == STD_ON) && (DEM_OBD_Support == STD_ON) */

#if ((DEM_DCM_ENABLED == STD_ON) && (DEM_OBD_Support == STD_ON))
/*------------------[Dem_DcmGetInfoTypeValue08]-----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue08(
  Dcm_OpStatusType                       OpStatus,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08BufferSize)
{
  /* the API is implemented only as stub with return value always E_NOT_OK */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETINFOTYPEVALUE08_ENTRY(OpStatus, Iumprdata08,
                                      Iumprdata08BufferSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue08, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue08, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DCM_INITIAL != OpStatus)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue08, DEM_E_PARAM_DATA);
  }
  else if ((Iumprdata08 == NULL_PTR) || (Iumprdata08BufferSize == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue08, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(Iumprdata08);
  TS_PARAM_UNUSED(Iumprdata08BufferSize);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(OpStatus);
  }

  DBG_DEM_DCMGETINFOTYPEVALUE08_EXIT(Result, OpStatus, Iumprdata08,
                                     Iumprdata08BufferSize);
  return Result;
}

/*------------------[Dem_DcmGetInfoTypeValue0B]-----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue0B(
  Dcm_OpStatusType                       OpStatus,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0B,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0BBufferSize)
{
  /* the API is implemented only as stub with return value always E_NOT_OK */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETINFOTYPEVALUE0B_ENTRY(OpStatus, Iumprdata0B,
                                      Iumprdata0BBufferSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue0B, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue0B, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DCM_INITIAL != OpStatus)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue0B, DEM_E_PARAM_DATA);
  }
  else if ((Iumprdata0B == NULL_PTR) || (Iumprdata0BBufferSize == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue0B, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(Iumprdata0B);
  TS_PARAM_UNUSED(Iumprdata0BBufferSize);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(OpStatus);
  }

  DBG_DEM_DCMGETINFOTYPEVALUE0B_EXIT(Result, OpStatus, Iumprdata0B,
                                     Iumprdata0BBufferSize);
  return Result;
}
#endif /* (DEM_DCM_ENABLED == STD_ON) && (DEM_OBD_Support == STD_ON) */

#if ((DEM_DCM_ENABLED == STD_ON) && (DEM_OBDONUDS_SUPPORT))
/*----------------[Dem_DcmGetInfoTypeValue79]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue79(
  Dcm_OpStatusType                       OpStatus,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBufferSize)
{
  /* the API always returns E_OK */
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMGETINFOTYPEVALUE79_ENTRY(OpStatus,
                                      DataValueBuffer,
                                      DataValueBufferSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue79, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue79, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (DCM_INITIAL != OpStatus)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue79, DEM_E_PARAM_DATA);
  }
  else if ((DataValueBuffer == NULL_PTR) || (DataValueBufferSize == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetInfoTypeValue79, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(OpStatus);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if (*DataValueBufferSize >= DEM_MAR_ELEMENT_SIZE)
    {
#if (DEM_MAR_SUPPORT == STD_ON)
      /* the size of the mini-denominator data is 1 byte */
      *DataValueBufferSize = DEM_MAR_ELEMENT_SIZE;
      /* !LINKSTO Dem.ASR21-11.SWS_Dem_01369,1 */
      *DataValueBuffer = Dem_NvData.MARData.Denominator;
#else
      /* if there is no MAR support, the buffer size is changed to 0,
       * to indicate that the buffer value is not valid */
      *DataValueBufferSize = DEM_INVALID_BUFFER_SIZE;
      TS_PARAM_UNUSED(DataValueBuffer);
#endif
    }
  }

  DBG_DEM_DCMGETINFOTYPEVALUE79_EXIT(Result,
                                     OpStatus,
                                     DataValueBuffer,
                                     DataValueBufferSize);
  return Result;
}
#endif /* (DEM_DCM_ENABLED == STD_ON) && (DEM_OBDONUDS_SUPPORT) */

#if (DEM_OBD_Support == STD_ON)
/*------------------[Dem_DcmReadDataOfPID01]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01value)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMREADDATAOFPID01_ENTRY(PID01value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID01, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID01, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID01value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID01, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    uint8 PID01[DEM_PID01PID41_SIZE] = {0x00U, 0x00U, 0x00U, 0x00U};

#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
    uint32 RGReady;
    uint32 RGSupported;
#endif

#if (defined DEM_MIL_ID)
    /* !LINKSTO Dem.ASR40.SWS_Dem_00352,1 */
    /* write the MIL Status to Byte A, bit 7 */
    Dem_UpdateMILStatusInPID(&PID01[DEM_PID_DATABYTE_A]);
#endif
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
    /* !LINKSTO Dem.ASR40.SWS_Dem_00355_Implicit1,1 */
    /* !LINKSTO dsn.Dem.ReadinessStatus.ComputationOnRetrieval,1 */
    /* compute readiness support and status of all the applicable groups */
    Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_PID01,
                                 DEM_RGP_UNUSED_FILTER_ATTRIBUTE,
                                 &RGSupported,
                                 &RGReady);

    /* Update ready and support status in the output buffer */
    Dem_RgpMapOutputData(RGSupported,
                         RGReady,
                         DEM_RGP_RGMASK_PID01_PID41,
                         Dem_RGBitPosPID01PID41,
                         &PID01[DEM_READINESS_DATABYTE_STARTPOS]);
#endif
    /* !LINKSTO Dem.ASR40.SWS_Dem_00351,1 */
    /* compute and write the number of confirmed faults to byte A, bits 0-6 */
    Dem_UpdateDTCCntInPID(&PID01[DEM_PID_DATABYTE_A]);

    /* update the OBDEngineType bit based on configuration/calibration */
    PID01[DEM_PID_DATABYTE_B] |= (Dem_ObdReadinessForceCompleteMask & DEM_ENGINETYPE_MASK);

    /* copy content of the PID into the destination buffer */
    TS_MemCpy(PID01value, PID01, DEM_PID01PID41_SIZE);
  }

  DBG_DEM_DCMREADDATAOFPID01_EXIT(Result, PID01value);
  return Result;
}
#endif /* (DEM_OBD_Support == STD_ON) */

/*------------------[Dem_DcmReadDataOfPID21]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID21(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value)
{

  DBG_DEM_DCMREADDATAOFPID21_ENTRY(PID21value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID21, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID21, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID21value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID21, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT == STD_ON */
  {
#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
    uint32 TicksTraveled;

    /*
     * ENTER critical section to protect
     *       Dem_NvData.TicksTraveledWhileMILIsActivated -- 32 bit read
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    TicksTraveled = Dem_NvData.TicksTraveledWhileMILIsActivated;

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    /* !LINKSTO DemChap7.8.3_Implicit1,1 */
    /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.DataAvailability,1 */
    /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.Scaling,1 */
    /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.Measurement,1 */
    /* !LINKSTO Dem.ASR42.SWS_Dem_01098,1 */
    PID21value[0] = (uint8)(DEM_CONVERT_TICKS_TO_KILOMETERS(TicksTraveled) >> 8);
    PID21value[1] = (uint8) DEM_CONVERT_TICKS_TO_KILOMETERS(TicksTraveled);
#else
    /* !LINKSTO Dem.SWS_Dem_01096,1 */
    /* !LINKSTO Dem.OBD.DistanceTraveled.InternalPID21Calculation.NotAvailable,1 */
    PID21value[0] = 0U;
    PID21value[1] = 0U;
#endif /* (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF) */
  }

  DBG_DEM_DCMREADDATAOFPID21_EXIT(E_OK, PID21value);
  return E_OK;
}
/*------------------[Dem_DcmReadDataOfPID30]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID30(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID30value)
{
  /* !LINKSTO Dem.ASR40.SWS_Dem_00320,2, Dem.Pid.SupportedPid_5,1 */
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMREADDATAOFPID30_ENTRY(PID30value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID30, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID30, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID30value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID30, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (defined DEM_OPCYC_WARMUP_ID)
    PID30value[0] = Dem_NvData.OBDWarmupCycleCtr;
#else
    /* !LINKSTO Dem.EB.OBD.PID30,1 */
    PID30value[0] = 0U;
#endif
  }

  DBG_DEM_DCMREADDATAOFPID30_EXIT(Result, PID30value);
  return Result;
}

/*------------------[Dem_DcmReadDataOfPID31]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID31(
  /* !LINKSTO Dem.ASR40.SWS_Dem_00321,2, Dem.Pid.SupportedPid_6,1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID31value)
{

  DBG_DEM_DCMREADDATAOFPID31_ENTRY(PID31value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID31, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID31, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID31value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID31, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_OBD_CENTRALIZED_PID31_HANDLING == STD_OFF)
    uint32 TicksTraveled;

    /*
     * ENTER critical section to protect
     *       Dem_NvData.TicksTraveledSinceDTCsCleared -- 32 bit read
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    TicksTraveled = Dem_NvData.TicksTraveledSinceDTCsCleared;

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    PID31value[0] = (uint8)(DEM_CONVERT_TICKS_TO_KILOMETERS(TicksTraveled) >> 8);
    PID31value[1] = (uint8) DEM_CONVERT_TICKS_TO_KILOMETERS(TicksTraveled);
#else
    /* !LINKSTO Dem.OBD.PID31,1 */
    PID31value[0] = 0U;
    PID31value[1] = 0U;
#endif /* (DEM_OBD_CENTRALIZED_PID31_HANDLING == STD_OFF) */
  }

  DBG_DEM_DCMREADDATAOFPID31_EXIT(E_OK, PID31value);
  return E_OK;
}

#if (DEM_OBD_Support == STD_ON)
/*------------------[Dem_DcmReadDataOfPID41]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID41(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41value)
{
  /* !LINKSTO Dem.ASR40.SWS_Dem_00322,2, dsn.Dem.OBDPid41.DemReadDataOfPID41,1 */
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMREADDATAOFPID41_ENTRY(PID41value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID41, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID41, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID41value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID41, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    uint8 PID41[DEM_PID01PID41_SIZE] = {0x00U, 0x00U, 0x00U, 0x00U};
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
    uint32 RGReady;
    uint32 RGSupported;


    /* !LINKSTO dsn.Dem.ReadinessStatus.ComputationOnRetrieval,1 */
    /* compute readiness support and status of all the applicable groups */
    Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_PID41,
                                 DEM_RGP_UNUSED_FILTER_ATTRIBUTE,
                                 &RGSupported,
                                 &RGReady);

    Dem_RgpMapOutputData(RGSupported,
                         RGReady,
                         DEM_RGP_RGMASK_PID01_PID41,
                         Dem_RGBitPosPID01PID41,
                         &PID41[DEM_READINESS_DATABYTE_STARTPOS]);
#endif

    /* update the OBDEngineType bit based on configuration/calibration */
    PID41[DEM_PID_DATABYTE_B] |= (Dem_ObdReadinessPID41ByteB & DEM_CMPRCMPT_MASK);
    PID41[DEM_PID_DATABYTE_B] |= (Dem_ObdReadinessForceCompleteMask & DEM_ENGINETYPE_MASK);

    /* copy content of the PID into the destination buffer */
    TS_MemCpy(PID41value, PID41, DEM_PID01PID41_SIZE);
  }

  DBG_DEM_DCMREADDATAOFPID41_EXIT(Result, PID41value);
  return Result;
}
#endif /* (DEM_OBD_Support == STD_ON) */

/*------------------[Dem_DcmReadDataOfPID4D]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Dvalue)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID4D_ENTRY(PID4Dvalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4D, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4D, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID4Dvalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4D, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID4Dvalue);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID4D_EXIT(Result, PID4Dvalue);
  return Result;
}

/*------------------[Dem_DcmReadDataOfPID4E]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Evalue)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID4E_ENTRY(PID4Evalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4E, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4E, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID4Evalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4E, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID4Evalue);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function NOT fully implemented yet.
     * implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID4E_EXIT(Result, PID4Evalue);
  return Result;
}

/*------------------[Dem_DcmReadDataOfPID1C]--------------------------------*/

#if (DEM_OBD_COMPLIANCY_ENABLED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID1Cvalue)
{
  /* !LINKSTO Dem.ASR40.SWS_Dem_00325,3, Dem.Pid.SupportedPid_3,2 */
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMREADDATAOFPID1C_ENTRY(PID1Cvalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID1C, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID1C, DEM_E_WRONG_CONTEXT);
  }
#endif/* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID1Cvalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID1C, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    PID1Cvalue[0] = Dem_ObdCompliancyPID1CByte;
  }

  DBG_DEM_DCMREADDATAOFPID1C_EXIT(Result, PID1Cvalue);
  return Result;
}
#endif /* (DEM_OBD_COMPLIANCY_ENABLED == STD_ON) */

/* !LINKSTO Dem_OBD_0001,2 */
#if (DEM_OBD_Support == STD_ON)
/*------------------[Dem_DcmReadDataOfPID91]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID91(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID91value)
{
  /* the API is implemented only as stub with return value always E_NOT_OK */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID91_ENTRY(PID91value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID91, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID91, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PID91value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID91, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID91value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function existing only as stub. */
  }

  DBG_DEM_DCMREADDATAOFPID91_EXIT(Result, PID91value);
  return Result;
}

/*------------------[Dem_DcmReadDataOfOBDFreezeFrame]-----------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfOBDFreezeFrame(
  uint8                                   PID,
  uint8                                   DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFOBDFREEZEFRAME_ENTRY(
    PID, DataElementIndexOfPID, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfOBDFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfOBDFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
#if (DEM_OBDONUDS_SUPPORT)
    /* Deviation MISRAC2012-1 */
  else if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
  {
    /* !LINKSTO Dem.OBDonUDS.Dem_DcmReadDataOfOBDFreezeFrame.ReturnValue,1 */
    /* if OBDonUDS functionality is active, the API will return E_NOT_OK */
    /* !LINKSTO Dem.OBDonUDS.Dem_DcmReadDataOfOBDFreezeFrame.DetError,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfOBDFreezeFrame, DEM_E_WRONG_CONDITION);
  }
#endif
#if (DEM_OBD_CLASSIC_SUPPORT)
  else if ( ((DestBuffer == NULL_PTR) || (BufSize == NULL_PTR)) &&
            (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBD_CLASSIC) )
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfOBDFreezeFrame, DEM_E_PARAM_POINTER);
  }
#endif
  /* Deviation MISRAC2012-1 */
  else
#endif /* DEM_DEV_ERROR_DETECT  */
  {
#if (DEM_OBD_CLASSIC_SUPPORT)
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
    /* local variable to protect concurrent read access to stored event Id */
    Dem_EventIdType StoredOBDFFEventId = DEM_EVENT_ID_INVALID;
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    /* local variable to hold the event entry index from multiple OBD FF */
    Dem_SizeEvMemEntryType SelectedEntryIndex = 0U;
    boolean                EntryFound = FALSE;
#endif

    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)

    StoredOBDFFEventId = DEM_OBDFF_STORED_EVENT_ID;
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)

    EntryFound = Dem_SelectEntryOfOBDFreezeFrameEvent(&SelectedEntryIndex, TRUE);
#endif

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();


#if ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE) && \
      ((DEM_EVENT_DISABLING_SUPPORT == STD_ON) || \
      (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)) )
    /* check whether any OBD freeze frame is stored */
    if ( (StoredOBDFFEventId != DEM_EVENT_ID_INVALID) &&
         (Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_OBD, StoredOBDFFEventId) != DEM_NO_DTC) )
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
    /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.EventId,1 */
    /* check whether any OBD freeze frame is stored */
    if (StoredOBDFFEventId != DEM_EVENT_ID_INVALID)
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    if (EntryFound == TRUE)
#endif
    {
      uint8_least PidClassIterator;
      Dem_SizeEntryDataType StartByte = 0U;

      /* find dedicated PID in OBD freeze frame */
      /* Deviation TASKING-1 */
      for (PidClassIterator = 0U;
           PidClassIterator < DEM_NUM_OF_PIDS_IN_OBDFF;
           PidClassIterator++)
      {
        if ( (Dem_PidClass[PidClassIterator].ParameterId == PID) &&
             (Dem_PidClass[PidClassIterator].ParameterId != DEM_PID_UNUSED) )
        {
          /* if PID is found in PID class, check whether parameter
           * DataElementIndexOfPID is valid
           */
          if (DataElementIndexOfPID < Dem_PidClass[PidClassIterator]
                                            .NumSegDataElements)
          {
            break;
          }
        }

        /* calculate start position index of the PID */
        StartByte += (Dem_SizeEntryDataType)Dem_PidClass[PidClassIterator].Size;
      }

      /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.Pid,1 */
      /* only perform further actions if PID was found and parameter
       * DataElementIndexOfPID is valid. Otherwise return E_NOT_OK */
      if (PidClassIterator < DEM_NUM_OF_PIDS_IN_OBDFF)
      {
        /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.BufSize,1 */
        /* check whether given BufSize has the right size,
         * otherwise return E_NOT_OK */
        if (*BufSize >= Dem_PidClass[PidClassIterator]
                              .ObdFFPidDataElementSize[DataElementIndexOfPID])
        {
          P2VAR(Dem_EntryDataType, AUTOMATIC, DEM_VAR_CLEARED) OBDFFStoredData;
          /* calculate index of OBDFFData[]
           * --> pos. of PID in FF + index of data element in PID */
          /* !LINKSTO Dem.SWS_Dem_00597,1 */
          const Dem_SizeEntryDataType ObdFFDataIdx = StartByte + Dem_PidClass[
            PidClassIterator].ObdFFPidDataElementOffset[DataElementIndexOfPID];

          /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.CriticalSection,1 */
          /*
           * ENTER critical section to protect the event memory
           *       call-context: Dem (Task)
           */
          DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
          OBDFFStoredData = DEM_OBDFF_ENTRY_FFDATA_LINK(SelectedEntryIndex);
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
          OBDFFStoredData = DEM_OBDFF_STORED_DATA;
#endif
          /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.DestBuffer,1
           */
          /* !LINKSTO Dem.ASR43.SWS_Dem_00596,1 */
          /* write dedicated data element into destination buffer */
          TS_MemCpy(DestBuffer,
            &OBDFFStoredData[ObdFFDataIdx],
            Dem_PidClass[PidClassIterator].ObdFFPidDataElementSize[DataElementIndexOfPID]);

          /*
           * LEAVE critical section
           */
          DEM_EXIT_EXCLUSIVE_AREA();

          /* !LINKSTO dsn.Dem.OBD.ReadDataOfOBDFreezeFrame.BufsizeOut,1 */
          /* return size of data written into DestBuffer */
          *BufSize = Dem_PidClass[PidClassIterator]
                              .ObdFFPidDataElementSize[DataElementIndexOfPID];

          Result = E_OK;
        }
      } /* return E_NOT_OK, if no OBD freeze frame stored,
         * or PID not found in OBD freeze frame
         * or provided BufSize is to small
         * or PID is DEM_PID_UNUSED */
    }
#endif /* (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) */
#endif /* DEM_OBD_CLASSIC_SUPPORT */
#if (DEM_NUM_OF_PIDS_IN_OBDFF == 0U)
    TS_PARAM_UNUSED(PID);
    TS_PARAM_UNUSED(DataElementIndexOfPID);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
#endif
  }

  DBG_DEM_DCMREADDATAOFOBDFREEZEFRAME_EXIT(
    Result, PID, DataElementIndexOfPID, DestBuffer, BufSize);
  return Result;
}

/*------------------[Dem_DcmGetDTCOfOBDFreezeFrame]-------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8                                   FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  Dem_DTCFormatType                       DTCFormat)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETDTCOFOBDFREEZEFRAME_ENTRY(FrameNumber, DTC, DTCFormat);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetDTCOfOBDFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetDTCOfOBDFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
#if (DEM_OBDONUDS_SUPPORT)
  /* Deviation MISRAC2012-1 */
  else if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
  {
    /* !LINKSTO Dem.OBDonUDS.Dem_DcmGetDTCOfOBDFreezeFrame.ReturnValue,1 */
    /* if OBDonUDS functionality is active, the API will always return E_NOT_OK */
    /* !LINKSTO Dem.OBDonUDS.Dem_DcmGetDTCOfOBDFreezeFrame.DetError,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetDTCOfOBDFreezeFrame, DEM_E_WRONG_CONDITION);
  }
#endif
#if (DEM_OBD_CLASSIC_SUPPORT)
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetDTCOfOBDFreezeFrame, DEM_E_PARAM_POINTER);
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS) &&
            (DTCFormat != DEM_DTC_FORMAT_J1939) )
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetDTCOfOBDFreezeFrame, DEM_E_PARAM_DATA);
  }
#endif
  /* Deviation MISRAC2012-1 */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_OBD_CLASSIC_SUPPORT)
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
    /* !LINKSTO dsn.Dem.OBD.GetDTCOfOBDFreezeFrame.FrameNumber,1 */
    /* check whether provided FrameNumber == '0', otherwise return E_NOT_OK */
    if (FrameNumber == DEM_OBD_FF_RECORD_NUM_FIRST)
    {
      if ( (DTCFormat == DEM_DTC_FORMAT_OBD) || (DTCFormat == DEM_DTC_FORMAT_UDS) )
      {
        /* local variable to protect concurrent read access to stored event Id */
        Dem_EventIdType StoredOBDFFEventId = DEM_EVENT_ID_INVALID;
        boolean         EntryFound = FALSE;

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)

        /*
         * ENTER critical section
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        StoredOBDFFEventId = DEM_OBDFF_STORED_EVENT_ID;

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

        /* !LINKSTO dsn.Dem.OBD.GetDTCOfOBDFreezeFrame.EventId,1 */
        /* check whether any OBD freeze frame is stored */
        if (StoredOBDFFEventId != DEM_EVENT_ID_INVALID)
        {
          EntryFound = TRUE;
        }
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
        Dem_SizeEvMemEntryType SelectedEntryIndex = 0U;

        /*
         * ENTER critical section
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        EntryFound = Dem_SelectEntryOfOBDFreezeFrameEvent(&SelectedEntryIndex, TRUE);

        if (EntryFound == TRUE)
        {
          /* get selected entry event Id from primary memory */
          StoredOBDFFEventId =
          Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][SelectedEntryIndex].EventId;
        }

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE) */
        if (EntryFound == TRUE)
        {
          /* For storing temporarily DTC value */
          uint32 DtcTempValue = DEM_NO_DTC;

          /* !LINKSTO dsn.Dem.OBD.GetDTCOfOBDFreezeFrame.GetVisibleCmbDTC,1 */
          /* !LINKSTO dsn.Dem.OBD.GetDTCOfOBDFreezeFrame.Dtc,1 */
          /* !LINKSTO dsn.Dem.OBD.GetDTCOfOBDFreezeFrame.NonExistingDTCFormat,1 */
          /* !LINKSTO Dem.ASR43.SWS_Dem_00623,1 */
          /* !LINKSTO Dem.Pid.SupportedPid_2,1 */
          /* OBD freeze frames will only be stored if the event has an OBD DTC
           * configured (see: Dem_ProcessEventEntry()), otherwise it's no OBD event.
           * Nevertheless the result needs to be checked because the DTC might not be
           * visible (suppressed) or the event might be unavailable or the UDS format is
           * requested but the event is not assigned with a UDS DTC. */
          DtcTempValue = Dem_GetVisibleCmbDTC(DTCFormat, StoredOBDFFEventId);

          if (DtcTempValue != DEM_NO_DTC)
          {
            *DTC = DtcTempValue;
            Result = E_OK;
          }
        }
      }
      else
      {
        /* J1939 format is not supported, the function will exit with E_NOT_OK */
      }
    }
#endif /* (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) */
#endif /* DEM_OBD_CLASSIC_SUPPORT */
#if (DEM_NUM_OF_PIDS_IN_OBDFF == 0U)
    TS_PARAM_UNUSED(FrameNumber);
    TS_PARAM_UNUSED(DTC);
    TS_PARAM_UNUSED(DTCFormat);
#endif
  }
  DBG_DEM_DCMGETDTCOFOBDFREEZEFRAME_EXIT(Result, FrameNumber, DTC, DTCFormat);
  return Result;
}

/*------------------[Dem_DcmGetAvailableOBDMIDs]----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetAvailableOBDMIDs(
  uint8                                   Obdmid,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) Obdmidvalue)
{
  /* function NOT fully implemented yet and will always return E_NOT_OK.
   * implementation is scheduled for future releases. */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETAVAILABLEOBDIDS_ENTRY(Obdmid, Obdmidvalue);
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetAvailableOBDMIDs, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetAvailableOBDMIDs, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (Obdmidvalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetAvailableOBDMIDs, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT  */
  {
    TS_PARAM_UNUSED(Obdmid);
    TS_PARAM_UNUSED(Obdmidvalue);
  }
  DBG_DEM_DCMGETAVAILABLEOBDIDS_EXIT(Result, Obdmid, Obdmidvalue);

  return Result;
}

/*------------------[Dem_DcmGetNumTIDsOfOBDMID]-----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetNumTIDsOfOBDMID(
  uint8                                   Obdmid,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  numberOfTIDs)
{
  /* function NOT fully implemented yet and will always return E_NOT_OK.
   * implementation is scheduled for future releases. */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETNUMTIDSOFOBDMID_ENTRY(Obdmid, numberOfTIDs);
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetNumTIDsOfOBDMID, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmGetNumTIDsOfOBDMID, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (numberOfTIDs == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmGetNumTIDsOfOBDMID, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT  */
  {
    TS_PARAM_UNUSED(Obdmid);
    TS_PARAM_UNUSED(numberOfTIDs);
  }
  DBG_DEM_DCMGETNUMTIDSOFOBDMID_EXIT(Result, Obdmid, numberOfTIDs);

  return Result;
}

/*------------------[Dem_DcmGetDTRData]-------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetDTRData(
  uint8                                   Obdmid,
  uint8                                   TIDindex,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  TIDvalue,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  UaSID,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Testvalue,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Lowlimvalue,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Upplimvalue)
{
  /* function NOT fully implemented yet and will always return E_NOT_OK.
   * implementation is scheduled for future releases. */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_DCMGETDTRDATA_ENTRY(
    Obdmid, TIDindex, TIDvalue, UaSID, Testvalue, Lowlimvalue, Upplimvalue);
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR( DEM_SID_DcmGetDTRData, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR( DEM_SID_DcmGetDTRData, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ( (TIDvalue    == NULL_PTR) ||
            (UaSID       == NULL_PTR) ||
            (Testvalue   == NULL_PTR) ||
            (Lowlimvalue == NULL_PTR) ||
            (Upplimvalue == NULL_PTR) )
  {
    DEM_REPORT_ERROR( DEM_SID_DcmGetDTRData, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT  */
  {
    TS_PARAM_UNUSED(Obdmid);
    TS_PARAM_UNUSED(TIDindex);
    TS_PARAM_UNUSED(TIDvalue);
    TS_PARAM_UNUSED(UaSID);
    TS_PARAM_UNUSED(Testvalue);
    TS_PARAM_UNUSED(Lowlimvalue);
    TS_PARAM_UNUSED(Upplimvalue);
  }
  DBG_DEM_DCMGETDTRDATA_EXIT(Result,
    Obdmid, TIDindex, TIDvalue, UaSID, Testvalue, Lowlimvalue, Upplimvalue);

  return Result;
}

#if (DEM_OBDONUDS_SUPPORT)
/*------------------[Dem_DcmReadDataOfPIDF501]------------------------------*/

/* !LINKSTO dsn.Dem.OBDPidF501.DemReadDataOfPIDF501,1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPIDF501(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDF501value)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_DCMREADDATAOFPIDF501_ENTRY(PIDF501value);
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPIDF501, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPIDF501, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (PIDF501value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPIDF501, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    uint8 PIDF501[DEM_PIDF501_SIZE] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
    uint32 RGReady;
    uint32 RGSupported;
#endif

    /* !LINKSTO Dem.OBD.PID$F501.Computation.J1979DACompliant,1 */
    /* run time check for the active OBD variant */
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
    {
#if (defined DEM_MIL_ID)
      /* write the MIL Status to Byte A, bit 7 */
      Dem_UpdateMILStatusInPID(&PIDF501[DEM_PID_DATABYTE_A]);
#endif
#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
      /* compute readiness support and status of all the applicable groups */
      /* !LINKSTO dsn.Dem.ReadinessStatus.ComputationOnRetrieval,1 */
      Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_PIDF501,
                                   DEM_RGP_UNUSED_FILTER_ATTRIBUTE,
                                   &RGSupported,
                                   &RGReady);

      /* Update supported and ready status in the output buffer */
      Dem_RgpMapOutputData(RGSupported,
                           RGReady,
                           DEM_RGP_RGMASK_PIDF501,
                           Dem_RGBitPosPIDF501,
                           &PIDF501[DEM_READINESS_DATABYTE_STARTPOS]);
#endif

      /* compute and write the number of confirmed faults to byte A, bits 0-6 */
      Dem_UpdateDTCCntInPID(&PIDF501[DEM_PID_DATABYTE_A]);

    }

    /* copy content of the PID into the destination buffer */
    TS_MemCpy(PIDF501value, PIDF501, DEM_PIDF501_SIZE);
  }

  DBG_DEM_DCMREADDATAOFPIDF501_EXIT(Result, PIDF501value);
  return Result;
}
#endif /* DEM_OBDONUDS_SUPPORT */

#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_RgpMapOutputData(
  uint32                                                 RGSupported,
  uint32                                                 RGReady,
  uint32                                                 NeededGroupsMask,
  P2CONST(Dem_RGStatusMappingType, AUTOMATIC, DEM_CONST) RGBitPosMap,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                     Buffer)
{
  Dem_OBDReadinessGroupType RgId;
  uint32 RgMsk = 1U;
  uint32 RGNotReady = (~RGReady) & NeededGroupsMask;
  DBG_DEM_RGPMAPOUTPUTDATA_ENTRY(RGSupported, NeededGroupsMask, RGReady, RGBitPosMap, Buffer);

  for(RgId = 1U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
  {
    RgMsk <<= (uint32) 1U;

    /* Unsupported bits are skipped since ready bits are inverted in the output buffer */
    if (DEM_IS_ANY_BIT_SET(RGSupported, RgMsk))
    {
      /* set supported bit of the readiness group */
      DEM_SET_BIT_IN_ARRAY(Buffer, RGBitPosMap[RgId].SupportedPosition);
    }
    if (DEM_IS_ANY_BIT_SET(RGNotReady, RgMsk))
    {
      /* update status bit of the readiness group */
      DEM_SET_BIT_IN_ARRAY(Buffer, RGBitPosMap[RgId].ReadyPosition);
    }
  }

  DBG_DEM_RGPMAPOUTPUTDATA_EXIT(RGSupported, RGReady, NeededGroupsMask, RGBitPosMap, Buffer);
}

FUNC(void, DEM_CODE) Dem_RgpCalcSelectedReadiness(
  Dem_ReadinessType                    ReadinessId,
  uint8                                Node,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  RGSupported,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  RGReady)
{
  uint32 LocalRGSupported = 0U;
  uint32 LocalRGReady = 0U;
  uint32 NeededGroupsMask = 0U;
  Dem_RGProcessEvPtrType CalcRGPerEventFnc = NULL_PTR;
  P2VAR(uint32, AUTOMATIC, DEM_VAR) NvDataReadyStatus = NULL_PTR;
  uint16 NvDataReadyStatusIdx = 0U;
  boolean DTCFormat = DEM_DTC_FORMAT_OBD;
  boolean ClearResetInProgress = FALSE;
  boolean AllLatchedRGReady = FALSE;
  uint32 ResetClearedMask = 0U;

  DBG_DEM_RGPCALCSELECTEDREADINESS_ENTRY(ReadinessId, Node, RGSupported, RGReady);

#if (DEM_J1939_READINESS1_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(Node);
#endif

  Dem_SelectReadiness(ReadinessId,
                      Node,
                      &NeededGroupsMask,
                      &CalcRGPerEventFnc,
                      &NvDataReadyStatusIdx,
                      &DTCFormat);

  /*
   * ENTER critical section to protect Dem_NvData.<PID>ReadyStatus
   *       call-context: Dem (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  if (RGReady == NULL_PTR)
  {
    ResetClearedMask = DEM_RGP_CLEARED_ON_DYC_START;
    if (ReadinessId == DEM_RGP_READINESS_PID01)
    {
      /* !LINKSTO dsn.Dem.ReadinessEnableStatus.CriticalSection,1 */
      /* Reset the enabled readiness groups for PID $41 */
      DEM_RESET_READINESS_GROUP_ENABLED(Dem_NvData.ReadinessEnableStatus);
    }
  }
  else
  {
    ResetClearedMask = DEM_RGP_CLEARED_ON_RETRIEVAL;
  }

  /* If PID selected is not PID $41 */
  if (NvDataReadyStatusIdx < DEM_READINESS_STATUS_ARRAY_SIZE)
  {
    NvDataReadyStatus = &Dem_NvData.ReadinessStatus[NvDataReadyStatusIdx];

    /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency.ClearDTC_1,1 */
    /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency.ResetReadiness_1,1 */
    if (((*NvDataReadyStatus) &
          (DEM_RGP_RESET_READINESS_IN_PROGRESS |
           DEM_RGP_CLEAR_IN_PROGRESS)) == 0U)
    {
      /* Reset the clear bit */
      *NvDataReadyStatus &= (~ResetClearedMask);
    }
    else
    {
      /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency,1 */
      ClearResetInProgress = TRUE;
    }
    LocalRGReady = *NvDataReadyStatus;
    if (NeededGroupsMask == (NeededGroupsMask & LocalRGReady))
    {
      /* status of all applicable readiness groups is complete */
      AllLatchedRGReady = TRUE;
    }
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  if ( ((ClearResetInProgress == FALSE) && (AllLatchedRGReady == FALSE)) ||
       (RGReady != NULL_PTR) )
  {
    Dem_CalcReadiness(DTCFormat,
                      Node,
                      NeededGroupsMask,
                      CalcRGPerEventFnc,
                      &LocalRGSupported,
                      &LocalRGReady);
  }

  /*
   * ENTER critical section to protect Dem_NvData.<PID>ReadyStatus
   *       call-context: Dem (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  if (NvDataReadyStatus != NULL_PTR)
  {
    /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency.ClearDTC_2,1 */
    /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency.ClearDTC_3,1 */
    /* !LINKSTO dsn.Dem.ReadinessStatus.Clear.Concurrency.ResetReadiness_2,1 */
    if( (ClearResetInProgress == TRUE) ||
        (((*NvDataReadyStatus) & ResetClearedMask) != 0U) )
    {
      /* Get the forced groups mask */
      uint32 ForcedReadyMask = Dem_GetForceReadyBitMask();

      /* Get the Clear in progress bits and rest readiness in progress bits
       * from the NvData variable to cover the case that a clear was started
       * after Calculation was started and to keep it reset if the clear has finished
       * while the calculation was on going */
      uint32 ResetMask = (*NvDataReadyStatus) & (DEM_RGP_RESET_READINESS_IN_PROGRESS |
                                         DEM_RGP_CLEAR_IN_PROGRESS);

      /* Set the bits of any supported forced readiness groups */
      LocalRGReady = (ForcedReadyMask & LocalRGSupported) | ResetMask;
    }

    /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.PID$01,1 */
    /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.PID$F501,1 */
    /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.ReadDiagnosticReadiness1,1 */
    /* Set ready bits */
    *NvDataReadyStatus = LocalRGReady;
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  if (RGReady != NULL_PTR)
  {
    *RGReady = LocalRGReady;
  }

  if (RGSupported != NULL_PTR)
  {
    *RGSupported = LocalRGSupported;
  }

  DBG_DEM_RGPCALCSELECTEDREADINESS_EXIT(ReadinessId, Filter, RGSupported, RGReady);
}

FUNC(void, DEM_CODE) Dem_RgpNotifyDCYStart(void)
{
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
  uint8 NodeIdx;
#endif

  DBG_DEM_RGPNOTIFYDCYSTART_ENTRY();

  /* compute readiness for PID $01 */
  Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_PID01,
                               DEM_RGP_UNUSED_FILTER_ATTRIBUTE,
                               NULL_PTR,
                               NULL_PTR);

#if (DEM_OBDONUDS_SUPPORT)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
    /* run time check for the active OBD variant */
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
    {
      /* compute readiness for PID $F501 */
      Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_PIDF501,
                                   DEM_RGP_UNUSED_FILTER_ATTRIBUTE,
                                   NULL_PTR,
                                   NULL_PTR);
    }
#endif

#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
  /* compute readiness for J1939 Readiness1 */
  /* Deviation TASKING-1 */
  for(NodeIdx = 0; NodeIdx < DEM_RGP_NUM_J1939_READINESS_NODES; NodeIdx++)
  {
    Dem_RgpCalcSelectedReadiness(DEM_RGP_READINESS_J1939READINESS1,
                                 Dem_RGP_J1939NmNodes[NodeIdx],
                                 NULL_PTR,
                                 NULL_PTR);
  }
#endif

  DBG_DEM_RGPNOTIFYDCYSTART_EXIT();
}

FUNC(void, DEM_CODE) Dem_RgpNotifyClearReadiness(
  uint8                     ServiceID,
  Dem_ClearStatusType       ClearStatus,
  uint8                     J1939Node)
{
  DBG_DEM_RGPNOTIFYCLEARREADINESS_ENTRY(ServiceID, ClearStatus, J1939Node);

#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(J1939Node);
#endif

  switch (ServiceID)
  {
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
    case DEM_SID_J1939DcmClearDTC:
    {
      uint8 NodeIdx = Dem_GetJ1939RGPNodeIdx(J1939Node);

      /* If clear is triggered for a readiness relevant node */
      if (NodeIdx != DEM_J1939_INVALID_NODE_IDX)
      {
        if(ClearStatus == DEM_CLEAR_START)
        {
          /* !LINKSTO Dem.ReadinessStatus.Clear.ReadDiagnosticReadiness1,1 */
          /* Clear latched readiness groups and set the clear all bit */
          Dem_NvData.ReadinessStatus[
            DEM_READINESS_STATUS_BASE_IDX_J1939READINESS1 + NodeIdx] =
            DEM_RGP_CLEAR_IN_PROGRESS_MASK;
        }
        else
        {
          /* Clear latched readiness groups and set the clear all bit */
          Dem_NvData.ReadinessStatus[
            DEM_READINESS_STATUS_BASE_IDX_J1939READINESS1 + NodeIdx] &=
            ~DEM_RGP_CLEAR_IN_PROGRESS;
        }
      }
      break;
    }
#endif
    case DEM_SID_ClearDTC:
    {
      /* !LINKSTO Dem.OBDonUDS.ClearResetEmissionRelatedDiagInfo.EmissionsGroup.StatusOfSystemMonitoringTests,1 */
      /* !LINKSTO Dem.OBDonUDS.ClearResetEmissionRelatedDiagInfo.AllDTCs.StatusOfSystemMonitoringTests,1 */

      if(ClearStatus == DEM_CLEAR_START)
      {
        /* !LINKSTO Dem.ReadinessStatus.Clear.PID$01,1 */
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] =
        /* retain the ResetReadinessInProgress bit */
          (Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] &
          DEM_RGP_RESET_READINESS_IN_PROGRESS) |
        /* Clear latched readiness groups and set the clear all bit */
          DEM_RGP_CLEAR_IN_PROGRESS_MASK;
#if (DEM_OBDONUDS_SUPPORT)
        /* !LINKSTO Dem.ReadinessStatus.Clear.PID$F501,1 */
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] =
        /* retain the ResetReadinessInProgress bit */
          (Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] &
          DEM_RGP_RESET_READINESS_IN_PROGRESS) |
        /* Clear latched readiness groups and set the clear all bit */
          DEM_RGP_CLEAR_IN_PROGRESS_MASK;
#endif
      }
      else
      {
        /* Clear latched readiness groups and set the clear all bit */
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] &=
          ~DEM_RGP_CLEAR_IN_PROGRESS;
#if (DEM_OBDONUDS_SUPPORT)
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] &=
          ~DEM_RGP_CLEAR_IN_PROGRESS;
#endif
      }
      break;
    }
    case DEM_SID_ResetReadiness:
    {
      if(ClearStatus == DEM_CLEAR_START)
      {
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] =
        /* retain the ClearDTCInProgress bit */
          (Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] &
          DEM_RGP_CLEAR_IN_PROGRESS) |
        /* Clear latched readiness groups and set the reset readiness all bit */
          DEM_RGP_RESET_READINESS_IN_PROGRESS_MASK;
#if (DEM_OBDONUDS_SUPPORT)
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] =
        /* retain the ClearDTCInProgress bit */
          (Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] &
          DEM_RGP_CLEAR_IN_PROGRESS) |
        /* Clear latched readiness groups and set the reset readiness all bit */
          DEM_RGP_RESET_READINESS_IN_PROGRESS_MASK;
#endif
      }
      else
      {
        /* Clear latched readiness groups and set the rest readiness all bit */
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PID01] &=
          ~DEM_RGP_RESET_READINESS_IN_PROGRESS;
#if (DEM_OBDONUDS_SUPPORT)
        Dem_NvData.ReadinessStatus[DEM_READINESS_STATUS_IDX_PIDF501] &=
          ~DEM_RGP_RESET_READINESS_IN_PROGRESS;
#endif
      }
      break;
    }
    /* CHECK: NOPARSE */
    default:
    {
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    }
    /* CHECK: PARSE */
  }

  DBG_DEM_RGPNOTIFYCLEARREADINESS_EXIT(ServiceID, ClearStatus, Filter);
}
#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */

#if (DEM_OBDONUDS_SUPPORT)
/*------------------[Dem_RgpGetNumDTCForRG]---------------------------------*/

FUNC(uint16, DEM_CODE) Dem_RgpGetNumDTCForRG(
  Dem_EventOBDReadinessGroupType  ReadinessGroupNumber,
  Dem_DTCFormatType               DTCFormat)
{
  uint16 CountedDTCs = 0U;

  DBG_DEM_RGPGETNUMDTCFORRG_ENTRY(ReadinessGroupNumber, DTCFormat);

  /* filter only for OBD readiness groups that correspond to a
   * valid ReadinessGroupNumber */
  if (ReadinessGroupNumber <= DEM_RGP_MAX_READINESS_GROUP_ID_J1979)
  {
    uint16 Iterator, IteratorStartValue, IteratorMaxValue;

    /* in the non-calibration case, the function loops through all the
     * configured events */
    IteratorStartValue = 1U;
    IteratorMaxValue = DEM_MAX_EVENTID + 1U;

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
    /* when filtering for ReadinessGroupNumber 0x00, the function loops through
     * all configured events, also in the calibration case */
    if (ReadinessGroupNumber != DEM_OBD_RDY_NONE)
    {
      /* if calibration is enabled, the function iterates through the elements of
       * Dem_OBDonUDSReadinessGroup[] array containing the events assigned to the
       * filtered readiness group, using the Dem_OBDReadinessGroupOffset[] array */
      IteratorStartValue = Dem_OBDReadinessGroupOffset[ReadinessGroupNumber - 1U];
      IteratorMaxValue = Dem_OBDReadinessGroupOffset[ReadinessGroupNumber];
    }
#endif

    /* Deviation TASKING-1 */
    for (Iterator = IteratorStartValue; Iterator < IteratorMaxValue; Iterator++)
    {
      Dem_EventIdType EventId = (Dem_EventIdType) Iterator;

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
      if (ReadinessGroupNumber != DEM_OBD_RDY_NONE)
      {
        /* EventId is assigned to the OBD readiness group with ID equal with
         * ReadinessGroupNumber */
        EventId = Dem_OBDReadinessGroup[Iterator];
      }
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
      /* the DTC assigned to events in combination is counted only once */
      if (DEM_GET_MASTER_EVID(EventId) == EventId)
#endif
      {
        const uint32 DTC = Dem_GetVisibleCmbDTC(DTCFormat, EventId);

        /* !LINKSTO Dem.ASR21-11.SWS_Dem_01101,1 */
        /* check if the DTC is emission relevant and if it is not suppressed
         * or disabled */
        if ( (DTC != DEM_NO_DTC) &&
             (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS) )
        {
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF)
          /* check into configuration if EventId is assigned to the OBD readiness
           * group with ID equal to ReadinessGroupNumber
           * check into configuration, for the special scenario in which
           * calibration is enabled, and there are no event slots reserved via
           * calibration for any of the OBD readiness groups */
          if (Dem_GbiOBDReadinessGroup(EventId) == ReadinessGroupNumber)
#else
          /* if filtering is done for other readiness group than DEM_OBD_RDY_NONE,
           * the current event should be counted */
          /* when filtering is done for DEM_OBD_RDY_NONE, check whether the current
           * event is present in Dem_OBDReadinessGroup[] array or not, indicated
           * by the corresponding flag from the bit-arrray Dem_RGEvents[] */
          /* !LINKSTO Dem.SetDTCFilterByReadinessGroup.ReadinessGroupNone,1 */
          if ( (ReadinessGroupNumber != DEM_OBD_RDY_NONE) ||
               (!DEM_IS_BIT_SET_IN_ARRAY(Dem_RGEvents, EventId)) )
#endif
          {
            CountedDTCs++;
          }
        }
      }
    }
  }

  DBG_DEM_RGPGETNUMDTCFORRG_EXIT(CountedDTCs, ReadinessGroupNumber, DTCFormat);
  return CountedDTCs;
}

/*------------------[Dem_RgpGetNextDTCForRG]--------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RgpGetNextDTCForRG(
  Dem_EventOBDReadinessGroupType                     ReadinessGroupNumber,
  Dem_DTCFormatType                                  DTCFormat,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC)                NextItem,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, AUTOMATIC) DTCStatus,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)                DTC)
{
  Std_ReturnType Result = DEM_NO_SUCH_ELEMENT;
  uint16 Iterator = 0U;

  DBG_DEM_RGPGETNEXTDTCFORRG_ENTRY(
    ReadinessGroupNumber, DTCFormat, NextItem, DTCStatus, DTC);

  /* filter only for OBD readiness groups that correspond to a
   * valid ReadinessGroupNumber */
  if (ReadinessGroupNumber <= DEM_RGP_MAX_READINESS_GROUP_ID_J1979)
  {
    /* in the non-calibration case, the function loops through all the
     * configured events */
    uint16 IteratorMaxValue = DEM_MAX_EVENTID;

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
    /* when filtering for ReadinessGroupNumber 0x00, the function loops through
     * all configured events, also in the calibration case */
    if (ReadinessGroupNumber != DEM_OBD_RDY_NONE)
    {
      /* if calibration is enabled, the function iterates through the elements of
       * Dem_OBDonUDSReadinessGroup[] array containing the events assigned to the
       * filtered readiness group, using the Dem_OBDReadinessGroupOffset[] array */
      IteratorMaxValue = Dem_OBDReadinessGroupOffset[ReadinessGroupNumber] -
                         Dem_OBDReadinessGroupOffset[ReadinessGroupNumber - 1U];
    }
#endif

    /* Deviation TASKING-1 */
    for (Iterator = *NextItem; Iterator <= IteratorMaxValue; Iterator++)
    {
      Dem_EventIdType EventId = (Dem_EventIdType) Iterator;

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON)
      if (ReadinessGroupNumber != DEM_OBD_RDY_NONE)
      {
        /* get the Dem_OBDReadinessGroup[]'s index where is located the next
         * event corresponding to the OBD readiness group whose ID is equal with
         * ReadinessGroupNumber */
        uint16 NextEventIndex =
          Dem_OBDReadinessGroupOffset[ReadinessGroupNumber - 1U] + Iterator - 1U;

        /* retrieve the next event's id assigned to the selected readiness group */
        EventId = Dem_OBDReadinessGroup[NextEventIndex];
      }
      if (EventId != DEM_EVENT_ID_INVALID)
#endif
      {
#if (DEM_NUM_CMB_DTCS > 0U)
        /* for events in combination the combined DTC is retrieved
         * from the master event */
        if (DEM_GET_MASTER_EVID(EventId) == EventId)
#endif
        {
          *DTC = Dem_GetVisibleCmbDTC(DTCFormat, EventId);

          /* !LINKSTO Dem.ASR21-11.SWS_Dem_01101,1 */
          /* check if the DTC is emission relevant and if it is not suppressed
           * or disabled */
          if ( (*DTC != DEM_NO_DTC) &&
               (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS) )
          {
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF)
            /* check into configuration if EventId is assigned to the OBD readiness
            * with ID equal to ReadinessGroupNumber */
            if (Dem_GbiOBDReadinessGroup(EventId) == ReadinessGroupNumber)
#else
            /* if filtering is done for other readiness group than DEM_OBD_RDY_NONE,
             * the current DTC should be returned */
            /* when filtering is done for DEM_OBD_RDY_NONE, check whether the current
             * event is present in Dem_OBDReadinessGroup[] array or not, indicated
             * by the corresponding flag from the bit-arrray Dem_RGEvents[] */
            /* !LINKSTO Dem.SetDTCFilterByReadinessGroup.ReadinessGroupNone,1 */
            if ( (ReadinessGroupNumber != DEM_OBD_RDY_NONE) ||
                 (!DEM_IS_BIT_SET_IN_ARRAY(Dem_RGEvents, EventId)) )
#endif
            {
#if (DEM_NUM_CMB_DTCS > 0U)
              Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
              if (DEM_IS_DTC_COMBINED(DTCConfIdx))
              {
                *DTCStatus = Dem_CmbDTCStatus[DTCConfIdx];
              }
              else
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
              {
                *DTCStatus = DEM_DTC_STATUS_MASKS[EventId];
              }

              /* mask out unsupported bits in DTC status */
              *DTCStatus &= DEM_DTC_STATUS_AVAILABILITY_MASK;

              /* next matching DTC found */
              Result = E_OK;
              /* end search for the current call */
              break;
            }
          }
        }
      }
    }
  }

  /* update NextItem for next call in filter */
  *NextItem = ++Iterator;

  DBG_DEM_RGPGETNEXTDTCFORRG_EXIT(
    Result, ReadinessGroupNumber, DTCFormat, NextItem, DTCStatus, DTC);
  return Result;
}
#endif /* (DEM_OBDONUDS_SUPPORT) */
#endif /* (DEM_OBD_Support) */

/*==================[internal function definitions]=========================*/
#if (DEM_OBD_Support == STD_ON)
#if (defined DEM_MIL_ID)
STATIC FUNC(void, DEM_CODE) Dem_UpdateMILStatusInPID(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PIDByteA)
{

  DBG_DEM_UPDATEMILSTATUSINPID_ENTRY(PIDByteA);

  if (Dem_InternalGetIndicatorStatus(DEM_MIL_ID, TRUE) != DEM_INDICATOR_OFF)
  {
    /* write the MIL Status corresponding bit of PID $01/$F401/$F501 */
    DEM_SET_BIT_8(*PIDByteA, DEM_BITPOS_7);
  }

  DBG_DEM_UPDATEMILSTATUSINPID_EXIT(PIDByteA);
}
#endif

STATIC FUNC(void, DEM_CODE) Dem_UpdateDTCCntInPID(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PIDByteA)
{
  Dem_EventIdType EventId;
  Dem_DTCFormatType DTCFormat;
  uint16 DTCCnt = 0U;

  DBG_DEM_UPDATEDTCCNTINPID_ENTRY(PIDByteA);

  DTCFormat = Dem_GetRelevantDTCFormat();

  /* count number of confirmed OBD DTCs by searching through _all_ events.
   * If event combination is enabled, a particular DTC is counted only once
   * per all associated combined events that refer to DTC Class, because
   * only one event can have CDTC bit set within the group of events */
  /* Deviation TASKING-1 */
  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      if ( (DEM_GET_MASTER_EVID(EventId) == EventId) &&
            DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_CDTC) )
      {
        if (Dem_GetVisibleCmbDTC(DTCFormat, EventId) != DEM_NO_DTC)
        {
#if ((DEM_OBDONUDS_SUPPORT) && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))
          if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
#endif
          {
            DTCCnt++;
          }
        }
      }
    }
    else
#endif
    {
      if (DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
      {
        if (Dem_GetVisibleCmbDTC(DTCFormat, EventId) != DEM_NO_DTC)
        {
#if ((DEM_OBDONUDS_SUPPORT) && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))
          if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
#endif
          {
            DTCCnt++;
          }
        }
      }
    }
  }
  *PIDByteA |= (DTCCnt > DEM_MAX_NUM_DTC_IN_PID) ?
    DEM_MAX_NUM_DTC_IN_PID : (uint8)DTCCnt;

  DBG_DEM_UPDATEDTCCNTINPID_EXIT(PIDByteA);
}

#if (DEM_READINESS_CALCULATION_SUPPORT == STD_ON)
STATIC FUNC(boolean, DEM_CODE) Dem_IsRGForcedComplete(
  Dem_OBDReadinessGroupType                              RgId)
{
  boolean Result = FALSE;
  uint8 CheckMask = 0;

  DBG_DEM_ISRGFORCEDCOMPLETE_ENTRY(RgId);

  /* !LINKSTO Dem.DemOBDForceMisfireMonitoringReady.Config,1 */
  /* !LINKSTO Dem.DemOBDForceFuelSysMonitoringReady.Config,1 */
  /* !LINKSTO Dem.DemOBDForceCCMonitoringReady.Config,1 */
  /* check if the readiness group is one of the readiness groups that
   * can be forced to complete */
  if ( (RgId == DEM_OBD_RDY_MISF) || (RgId == DEM_OBD_RDY_FLSYS) ||
       (RgId == DEM_OBD_RDY_CMPRCMPT) )
  {
    /* initialize the check mask by setting the bit corresponding
     * to the ready bit of the current RG */
    DEM_SET_BIT_8(CheckMask, Dem_RGBitPosPID01PID41[RgId].ReadyPosition);

    /* check if the current readiness group is forced to ready */
    if (((~Dem_ObdReadinessForceCompleteMask) & CheckMask) != 0U)
    {
      Result = TRUE;
    }
  }

  DBG_DEM_ISRGFORCEDCOMPLETE_EXIT(Result, RgId);

  return Result;
}

STATIC FUNC(void, DEM_CODE) Dem_InitRGCalcStatus(
  Dem_OBDReadinessGroupType                              RgId,
  uint32                                                 RGReady,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC)      RGCalcStatus)
{

  DBG_DEM_INITRGCALCSTATUS_ENTRY(RgId, RGReady, RGCalcStatus);

  *RGCalcStatus = DEM_RG_CALC_NOT_STARTED;

  if (DEM_IS_ANY_BIT_SET(RGReady, (uint32) 1U << (RgId)))
  {
    *RGCalcStatus = DEM_RG_CALC_FORCE_COMPLETE;
  }
  /* check if the readiness group is one of the readiness groups that
   * can be forced to complete */
  else
  {
    if (Dem_IsRGForcedComplete(RgId) == TRUE)
    {
      *RGCalcStatus = DEM_RG_CALC_FORCE_COMPLETE;
    }
  }

  DBG_DEM_INITRGCALCSTATUS_EXIT(RgId, RGReady, RGCalcStatus);
}

STATIC FUNC(void, DEM_CODE) Dem_RGCalcPerEventPIDFx01(
  Dem_OBDReadinessGroupType                         RgId,
  Dem_EventIdType                                   EventId,
  uint8                                             Filter,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Supported,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Ready,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus)
{
  DBG_DEM_RGCALCPEREVENTPIDFX01_ENTRY(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);
  TS_PARAM_UNUSED(Filter);
  TS_PARAM_UNUSED(RgId);

  if (*RGCalcStatus == DEM_RG_CALC_FORCE_COMPLETE)
  {
    *Supported = TRUE;
    *Ready = TRUE;
    *RGCalcStatus = DEM_RG_CALC_FINISHED;
  }
  else
  {
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
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
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.TestedSinceLastClear,1 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.TestedSinceLastClear,1 */
      /* check if the monitor was not completed since last clear or if the event
       * has a pending status */
      if (DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_TNCSLC |
                                         DEM_UDS_STATUS_PDTC))
      {
         /* set readiness status to not complete */
         *Ready = FALSE;
      }
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.MIL,1 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.MIL,1 */
      /* check if event is confirmed (CDTC bit is set) */
      if (DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_CDTC))
      {
        /* event has caused MIL on, set readiness status to complete */
        *Ready = TRUE;
        /* if at least one event in this readiness group is confirmed, set the
         * state of readiness group calculation to finished so that readiness
         * status is not calculated for subsequent events */
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
        /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.ExcludedEvents,2 */
        if (Dem_GbiEvAvailable(CmbEventId) == TRUE)
#endif
        {
          /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.TestedSinceLastClear,2 */
          /* check if the monitor was not completed since last clear or if the event
           * has a pending status */
          if (DEM_IS_ANY_EV_ST_BIT_SET(CmbEventId,
                                       DEM_UDS_STATUS_TNCSLC |
                                       DEM_UDS_STATUS_PDTC))
          {
             /* set readiness status to not complete */
             *Ready = FALSE;
          }
          /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.MIL,2 */
          /* check if event is confirmed (CDTC bit is set) */
          if (DEM_IS_EV_ST_BIT_CDTC_SET(CmbEventId))
          {
            /* event has caused MIL on, set readiness status to complete */
            *Ready = TRUE;
            /* if at least one event in this readiness group is confirmed, set the
             * state of readiness group calculation to finished so that readiness
             * status is not calculated for subsequent events */
            *RGCalcStatus = DEM_RG_CALC_FINISHED;
            break;
          }
        }
      }
#endif /* (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) */
    }
    else
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
    {
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.TestedSinceLastClear,1 */
      /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.TestedSinceLastClear,2 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.TestedSinceLastClear,1 */
      /* check if the monitor was not completed since last clear or if the event
       * has a pending status */
      if (DEM_IS_ANY_EV_ST_BIT_SET(EventId,
                                   DEM_UDS_STATUS_TNCSLC |
                                   DEM_UDS_STATUS_PDTC))
      {
        /* set readiness status to not complete */
        *Ready = FALSE;
      }
      /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.MIL,2 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.MIL,1 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.MIL,1 */
      /* check if event is confirmed (CDTC bit is set) */
      if (DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
      {
        /* event has caused MIL on, set readiness status to complete */
        *Ready = TRUE;
        /* if at least one event in this readiness group is confirmed, set the
         * state of readiness group calculation to finished so that readiness
         * status is not calculated for subsequent events */
        *RGCalcStatus = DEM_RG_CALC_FINISHED;
      }
    }
  }

  DBG_DEM_RGCALCPEREVENTPIDFX01_EXIT(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);
}

STATIC FUNC(void, DEM_CODE) Dem_RGCalcPerEventPID41(
  Dem_OBDReadinessGroupType                         RgId,
  Dem_EventIdType                                   EventId,
  uint8                                             Filter,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Supported,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)              Ready,
  P2VAR(Dem_RGCalcStatusType, AUTOMATIC, AUTOMATIC) RGCalcStatus)
{
  DBG_DEM_RGCALCPEREVENTPID41_ENTRY(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);
  TS_PARAM_UNUSED(Filter);

  if (DEM_MONITOR_IS_ENABLED(RgId, Dem_NvData.ReadinessEnableStatus))
  {
    /* !LINKSTO Dem.ASR40.SWS_Dem_00356,1 */
    *Supported = TRUE;
  }

  if (*RGCalcStatus == DEM_RG_CALC_FORCE_COMPLETE)
  {
    *Ready = TRUE;
    *RGCalcStatus = DEM_RG_CALC_FINISHED;
  }
  else
  {
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
    if (*RGCalcStatus == DEM_RG_CALC_NOT_STARTED)
    {
      *Ready = TRUE;
      *RGCalcStatus = DEM_RG_CALC_ONGOING;
    }

#if (DEM_NUM_CMB_DTCS > 0U)
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      Dem_EventIdType CmbEventId;
      Dem_CmbDTCEvLnkType CmbEvIdx;
      Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
      /* loop through all the events and calculate the combined status */
      for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
      {
        CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if (Dem_GbiEvAvailable(CmbEventId) == TRUE)
#endif
        {
          /* !LINKSTO Dem.ASR40.SWS_Dem_00355,1 */
          /* !LINKSTO dsn.Dem.ReadinessStatus.Computation.PID$41.DisabledReadinessGroup,1 */
          /* check if event was not completed monitoring cycle - independent
           * of the disable status of the group */
          if (DEM_IS_EV_ST_BIT_TNCTOC_SET(CmbEventId))
          {
            /* set readiness status to not complete */
            *Ready = FALSE;
          }
        }
      }
    }
    else
#endif
    {
      /* !LINKSTO Dem.ASR40.SWS_Dem_00355,1 */
      /* !LINKSTO dsn.Dem.ReadinessStatus.Computation.PID$41.DisabledReadinessGroup,1 */
      /* check if event was not completed monitoring cycle - independent
       * of the disable status of the group */
      if (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId))
      {
        /* set readiness status to not complete */
        *Ready = FALSE;
      }
    }
  }

  DBG_DEM_RGCALCPEREVENTPID41_EXIT(
    RgId, EventId, Filter, Supported, Ready, RGCalcStatus);
}

STATIC FUNC(void, DEM_CODE) Dem_SelectReadiness(
  Dem_ReadinessType                                    ReadinessId,
  uint8                                                Node,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)                  NeededGroupsMask,
  P2VAR(Dem_RGProcessEvPtrType, AUTOMATIC, AUTOMATIC)  CalcRGPerEventFnc,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC)                  NvDataReadyStatusIdx,
  P2VAR(Dem_DTCFormatType, AUTOMATIC, AUTOMATIC)       DTCFormat)
{
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
  uint8 NodeIdx;
#else
  TS_PARAM_UNUSED(Node);
#endif

  DBG_DEM_SELECTREADINESS_ENTRY
    (ReadinessId, Node, NeededGroupsMask, CalcRGPerEventFnc, NvDataReadyStatus, DTCFormat);

  switch(ReadinessId)
  {
    case DEM_RGP_READINESS_PID01:
    {
      *CalcRGPerEventFnc = Dem_RGCalcPerEventPIDFx01;
      *NeededGroupsMask = DEM_RGP_RGMASK_PID01_PID41;
      /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.PID$01,1 */
      *NvDataReadyStatusIdx = DEM_READINESS_STATUS_IDX_PID01;
      *DTCFormat = Dem_GetRelevantDTCFormat();
      break;
    }
#if (DEM_OBDONUDS_SUPPORT)
    case DEM_RGP_READINESS_PIDF501:
    {
      *CalcRGPerEventFnc = Dem_RGCalcPerEventPIDFx01;
      *NeededGroupsMask = DEM_RGP_RGMASK_PIDF501;
      /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.PID$F501,1 */
      *NvDataReadyStatusIdx = DEM_READINESS_STATUS_IDX_PIDF501;
      *DTCFormat = Dem_GetRelevantDTCFormat();
      break;
    }
#endif /* DEM_OBDONUDS_SUPPORT */
    /* !LINKSTO VCC_DEM_006_Req141v1,1 */
    case DEM_RGP_READINESS_PID41:
    {
      *CalcRGPerEventFnc = Dem_RGCalcPerEventPID41;
      *NeededGroupsMask = DEM_RGP_RGMASK_PID01_PID41;
      *NvDataReadyStatusIdx = DEM_READINESS_STATUS_ARRAY_SIZE;
      *DTCFormat = Dem_GetRelevantDTCFormat();
      break;
    }
#if (DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON)
    case DEM_RGP_READINESS_J1939READINESS1:
    {
      *CalcRGPerEventFnc = Dem_RGCalcPerEventJ1939Readiness1;
      *NeededGroupsMask = DEM_RGP_RGMASK_J1939READINESS1;
      NodeIdx = Dem_GetJ1939RGPNodeIdx(Node);

      /* If Readiness1 is triggered for a readiness relevant node */
      if (NodeIdx != DEM_J1939_INVALID_NODE_IDX)
      {
        /* !LINKSTO Dem.ReadinessStatus.NonVolatileStorage.ReadDiagnosticReadiness1,1 */
        *NvDataReadyStatusIdx =
          (uint16) ((uint16) DEM_READINESS_STATUS_BASE_IDX_J1939READINESS1 +
                    (uint16) NodeIdx);
      }
      else
      {
        *NvDataReadyStatusIdx = DEM_READINESS_STATUS_ARRAY_SIZE;
      }

      *DTCFormat = DEM_DTC_FORMAT_J1939;
      break;
    }
#endif /* DEM_J1939_READINESS1_CALCULATION_SUPPORT == STD_ON */
    /* CHECK: NOPARSE */
    default:
    {
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    }
    /* CHECK: PARSE */
  }

  DBG_DEM_SELECTREADINESS_EXIT
    (ReadinessId, Node, NeededGroupsMask, CalcRGPerEventFnc, NvDataReadyStatus, DTCFormat);
}

#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF)
/* The readiness calculation when calibration is disabled/enabled is performed
   in Dem_CalcReadiness(). However the definition of the Dem_CalcReadiness()
   is different for the case calibration disabled/enabled. */
STATIC FUNC(void, DEM_CODE) Dem_CalcReadiness(
  boolean                              DTCFormat,
  uint8                                Node,
  uint32                               NeededGroupsMask,
  Dem_RGProcessEvPtrType               CalcRGPerEventFnc,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGSupported,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGReady)
{
  Dem_EventIdType EventId;
  Dem_OBDReadinessGroupType RgId;
  Dem_RGCalcStatusType RGCalcStatus[DEM_RGP_MAX_NUM_READINESS_GROUPS];
  boolean Supported[DEM_RGP_MAX_NUM_READINESS_GROUPS];
  boolean Ready[DEM_RGP_MAX_NUM_READINESS_GROUPS];

  DBG_DEM_CALCREADINESS_ENTRY(DTCFormat, Node, NeededGroupsMask,
    CalcRGPerEventFnc, LocalRGSupported, LocalRGReady);

  for (RgId = 0U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
  {
    /* initialize all the readiness groups to not supported and complete */
    Supported[RgId] = FALSE;
    Ready[RgId] = TRUE;

    /* initialize the readiness calculation status to DEM_RG_CALC_FORCE_COMPLETE
     * if the readiness is forced to complete or if it is latched to complete and to
     * DEM_RG_CALC_NOT_STARTED otherwise */
    Dem_InitRGCalcStatus(RgId, *LocalRGReady, &RGCalcStatus[RgId]);
  }
  /* Deviation TASKING-1 */
  for (EventId = 1u; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
#if (DEM_NUM_CMB_DTCS > 0U)
    /* Check if the current event is a master event */
    if(EventId == DEM_GET_MASTER_EVID(EventId))
#endif
    {
      /* get the readiness group of the event */
      Dem_OBDReadinessGroupType ReadinessGroupNumber =
        Dem_GbiOBDReadinessGroup(EventId);

      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.ExcludedEvents,1 */
      /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.ExcludedEvents,2 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.ExcludedEvents,1 */
      /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$41.ExcludedEvents,1 */
      /* check if the readiness calculation is not fully finished for the
       * respective readiness group, if the positional readiness bit mask
       * which ensures the readiness group is valid, supported for the
       * configured engine type */
      if ( (ReadinessGroupNumber < DEM_RGP_MAX_NUM_READINESS_GROUPS) &&
           (RGCalcStatus[ReadinessGroupNumber] != DEM_RG_CALC_FINISHED) &&
           (Dem_GetVisibleCmbDTC(DTCFormat, EventId) != DEM_NO_DTC) &&
           (DEM_IS_ANY_BIT_SET(NeededGroupsMask, (uint32) 1U << (ReadinessGroupNumber))) )
      {
        /* invoke the specific readiness calculation function */
        CalcRGPerEventFnc(ReadinessGroupNumber,
                          EventId,
                          Node,
                          &Supported[ReadinessGroupNumber],
                          &Ready[ReadinessGroupNumber],
                          &RGCalcStatus[ReadinessGroupNumber]);
      }
    }
  }
  for (RgId = 1U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
  {
    /* update readiness data in the output bit masks */
    if (DEM_IS_ANY_BIT_SET(NeededGroupsMask, (uint32) 1U << (RgId)))
    {
      /* update readiness data based on the bit mask */
      if(Supported[RgId] == TRUE)
      {
        DEM_SET_BIT_32(*LocalRGSupported, RgId);
      }

      if(Ready[RgId] == TRUE)
      {
        DEM_SET_BIT_32(*LocalRGReady, RgId);
      }
    }
  }

  DBG_DEM_CALCREADINESS_EXIT(DTCFormat, Node, NeededGroupsMask,
    CalcRGPerEventFnc, LocalRGSupported, LocalRGReady);
}
#else
STATIC FUNC(void, DEM_CODE) Dem_CalcReadiness(
  boolean                              DTCFormat,
  uint8                                Node,
  uint32                               NeededGroupsMask,
  Dem_RGProcessEvPtrType               CalcRGPerEventFnc,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGSupported,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  LocalRGReady)
{
  Dem_RGCalcStatusType RGCalcStatus;
  boolean Supported;
  boolean Ready;
  Dem_EventIdType EventId;
  Dem_OBDReadinessGroupType RgId;

  DBG_DEM_CALCREADINESS_ENTRY(DTCFormat, Node, NeededGroupsMask,
    CalcRGPerEventFnc, LocalRGSupported, LocalRGReady);

  for (RgId = 1U; RgId < DEM_RGP_MAX_NUM_READINESS_GROUPS; RgId++)
  {
    /* check the positional readiness bit mask to ensure if the readiness
     * group is valid */
    if (DEM_IS_ANY_BIT_SET(NeededGroupsMask, (uint32) 1U << (RgId)))
    {
      uint16 EvOffset;
      uint16 NumOfEventsInRdyGrp;
      uint16 ArrayIndex;
      /* initialize the readiness group to not supported and complete */
      Supported = FALSE;
      Ready = TRUE;

      /* initialize the readiness calculation status to DEM_RG_CALC_FORCE_COMPLETE
       * if the readiness is forced to complete or if it is latched to complete and to
       * DEM_RG_CALC_NOT_STARTED otherwise */
       Dem_InitRGCalcStatus(RgId, *LocalRGReady, &RGCalcStatus);

#if ((DEM_OBD_CLASSIC_SUPPORT) && (DEM_OBD_CLASSIC_FIXED_SLOTS_SUPPORT == STD_ON))
      NumOfEventsInRdyGrp = DEM_MAX_EVENTS_PER_READINESS_GROUP;
      ArrayIndex = Dem_OBDReadinessGroupOffset[RgId] - NumOfEventsInRdyGrp;
#else
      /* find number of event slots that can be calibrated within the
       * readiness group segment */
      NumOfEventsInRdyGrp = Dem_OBDReadinessGroupOffset[RgId] -
        Dem_OBDReadinessGroupOffset[RgId - 1U];
      ArrayIndex = Dem_OBDReadinessGroupOffset[RgId - 1U];
#endif
      /* loop through all the assigned events within readiness group segment */
      for (EvOffset = 0U; EvOffset < NumOfEventsInRdyGrp; EvOffset++)
      {
        EventId = Dem_OBDReadinessGroup[ArrayIndex + EvOffset];

        if (RGCalcStatus == DEM_RG_CALC_FINISHED)
        {
          /* Skip to the next readiness group segment if the status
           * of readiness calculation is finished */
          break;
        }
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$01.ExcludedEvents,1 */
        /* !LINKSTO Dem.ReadinessStatus.Computation.PID$01.ExcludedEvents,2 */
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$F501.ExcludedEvents,1 */
        /* !LINKSTO Dem.OBDonUDS.ReadinessStatus.Computation.PID$41.ExcludedEvents,1 */
        /* Check if the current event is visible, valid and master event */
#if (DEM_NUM_CMB_DTCS > 0U)
        if((EventId != DEM_EVENT_ID_INVALID) &&
           (EventId == DEM_GET_MASTER_EVID(EventId) &&
           (Dem_GetVisibleCmbDTC(DTCFormat, EventId) != DEM_NO_DTC)))
#else
        if((EventId != DEM_EVENT_ID_INVALID) &&
           (Dem_GetVisibleCmbDTC(DTCFormat, EventId) != DEM_NO_DTC))
#endif
        {
          /* invoke the specific readiness calculation function */
          CalcRGPerEventFnc(RgId,
                            EventId,
                            Node,
                            &Supported,
                            &Ready,
                            &RGCalcStatus);
        }
      }
      /* update readiness data based on the bit mask */
      if(Supported == TRUE)
      {
        DEM_SET_BIT_32(*LocalRGSupported, RgId);
      }
      if(Ready == TRUE)
      {
        DEM_SET_BIT_32(*LocalRGReady, RgId);
      }
    }
  }
  DBG_DEM_CALCREADINESS_EXIT(DTCFormat, Node, NeededGroupsMask,
    CalcRGPerEventFnc, LocalRGSupported, LocalRGReady);
}
#endif /* (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF) */

STATIC FUNC(uint32, DEM_CODE) Dem_GetForceReadyBitMask(void)
{
  uint32 RGReady = 0;
  DBG_DEM_GETFORCEREADYBITMASK_ENTRY();

  if (Dem_IsRGForcedComplete(DEM_OBD_RDY_MISF) == TRUE)
  {
    DEM_SET_BIT_32(RGReady, DEM_OBD_RDY_MISF);
  }

  if (Dem_IsRGForcedComplete(DEM_OBD_RDY_FLSYS) == TRUE)
  {
    DEM_SET_BIT_32(RGReady, DEM_OBD_RDY_FLSYS);
  }

  if (Dem_IsRGForcedComplete(DEM_OBD_RDY_CMPRCMPT) == TRUE)
  {
    DEM_SET_BIT_32(RGReady, DEM_OBD_RDY_CMPRCMPT);
  }

  DBG_DEM_GETFORCEREADYBITMASK_EXIT(RGReady);

  return RGReady;
}
#endif /* (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) */

STATIC FUNC(Dem_DTCFormatType, DEM_CODE) Dem_GetRelevantDTCFormat(void)
{
  Dem_DTCFormatType DTCFormat;

  DBG_DEM_GETRELEVANTDTCFORMAT_ENTRY();

#if (DEM_OBDONUDS_SUPPORT)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
  if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif /* (DEM_OBD_VARIANT_SELECTABLE == STD_ON) */
  {
#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
    DTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
#else
    DTCFormat = DEM_DTC_FORMAT_UDS;
#endif /* (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON) */
  }
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
  else
#endif /* (DEM_OBD_VARIANT_SELECTABLE == STD_ON) */
#endif /* DEM_OBDONUDS_SUPPORT */

#if (DEM_OBD_CLASSIC_SUPPORT)
  {
    DTCFormat = DEM_DTC_FORMAT_OBD;
  }
#endif /* DEM_OBD_CLASSIC_SUPPORT */

  DBG_DEM_GETRELEVANTDTCFORMAT_EXIT(DTCFormat);

  return DTCFormat;
}
#endif /* (DEM_OBD_Support == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[end of file]===========================================*/
