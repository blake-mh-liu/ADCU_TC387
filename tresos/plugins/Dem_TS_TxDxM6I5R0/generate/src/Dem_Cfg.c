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

/* This file contains all definitions of the configuration of the AUTOSAR
 * module Dem that are target independent. */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *     Conversions shall not be performed between a pointer to a function and
 *     any other type.
 *
 *     Reason:
 *     In order to save memory, the function pointers necessary for Read Callbacks are generated
 *     as an array of unions (union type which contains all such possible function pointers),
 *     instead of an array of structures containing all possible pointer types.
 *     The array containing the function pointers is initialized using brace-enclosed initializer
 *     list and C90 standard allow only the initialization of the first union member.
 *     The solution is to use a "generic function pointer" and use that type to define the array,
 *     and use explicit casts for each initialized member.
 *     Casting one function pointer type to the general type at initialization and then back again
 *     to the original type is guaranteed to preserve the correct data.
 *
 *
 * MISRAC2012-2) Deviated Rule: 20.7 (required)
 *     Expressions resulting from the expansion of macro parameters shall be enclosed in
 *     parentheses.
 *
 *     Reason:
 *     The macro DEM_CONST_CALIBRATION is used to modify the read-only attribute of a memory section
 *     to which a constant is assigned via the compiler abstraction macro, in order for the compiler
 *     to allow the simulation of the constant calibration. The syntax of the compiler abstraction
 *     macro definition requires that DEM_CONST_CALIBRATION macro's definition to not be enclosed in
 *     parentheses.
 */

[!AUTOSPACING!]
[!INCLUDE "../../generate_common/Dem_Include.m"!]
[!//
/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                    /* EB specific standard types */
#include <Std_Types.h>                    /* AUTOSAR standard types */
#include <Dem_Int.h>                      /* API and internal declarations,
                                           * dependent and static part */
[!CALL "CALCULATE_MULTICORE_SETTINGS"!][!//
[!//
[!INDENT "0"!]
  [!IF "$DemBSWDistributionOfEventReports = 'true'"!]
    [!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
      [!VAR "SatelliteCoreId" = "num:i(./DemSatelliteCoreId)"!]
      #include <SchM_Dem_1_Core_[!"$SatelliteCoreId"!].h> /* BSW distribution datatypes and API definitions */
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDINDENT!]
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

CONST(Dem_ConfigType, DEM_CONST) [!"as:name(DemConfigSet/eb-list::*[1])"!] = {0U};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
[!//
[!INDENT "0"!]

[!IF "(as:modconf('Dem')[1]/DemGeneral/DemExtendedDataCapture = 'DEM_TRIGGER_ON_FDC_THRESHOLD') and
      (as:modconf('Dem')[1]/DemGeneral/DemEventDisplacementStrategy = 'DEM_DISPLACEMENT_FULL') and
      (node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemEventDisplacementSupport))"!]
  /*------------------[Passive event reference configuration]------------------*/
  #define DEM_START_SEC_CALIB_16
  #include <Dem_MemMap.h>

  [!VAR "NumOfLines" = "0"!]
  [!LOOP "DemConfigSet/eb-list::*/DemAdvDisplacementPassiveTableLine/eb-list::*"!]
     [!/* !LINKSTO dsn.Dem.Displacement.AdvDisplPassiveEventIds,1 */!][!//
     /** \brief event IDs of passive events, referenced by [!"as:name(.)"!] */
     /* Deviation MISRAC2012-2 */
     CONST(Dem_EventIdType, DEM_CONST_CALIBRATION)
       [!WS "2"!]Dem_AdvDisplPassiveEventIdsLine[!"num:integer($NumOfLines)"!][DEM_NUM_OF_PASSIVE_EVENT_REFS_LINE[!"num:integer($NumOfLines)"!]] =
       [!VAR "NumOfLines" = "$NumOfLines + 1"!]
     {
       [!LOOP "./DemPassiveEventRefs/eb-list::*/DemPassiveEventRef"!]
         [!VAR "NameInSegment" = "as:name(as:ref(.))"!]
         [!WS "2"!][!"as:ref(.)/DemEventId"!]U, /* event ID of passive event: [!"$NameInSegment"!] */
       [!ENDLOOP!]
     };
  [!ENDLOOP!]

  [!IF "node:exists(DemConfigSet/eb-list::*/DemAdvDisplacementPassiveTableLine/eb-list::*)"!]
    [!VAR "NumOfLines" = "0"!]
    [!/* !LINKSTO dsn.Dem.Displacement.DemAdvDisplReportedEventIds,1 */!][!//
    /** \brief advanced displacement reported events */
    /* Deviation MISRAC2012-2 */
    CONST(Dem_EventIdType, DEM_CONST_CALIBRATION)
    [!WS "2"!]Dem_AdvDisplPassiveTableLineReportedEventIds[DEM_NUM_OF_PASSIVE_TABLE_LINES] =
    {
    [!LOOP "DemConfigSet/eb-list::*/DemAdvDisplacementPassiveTableLine/eb-list::*"!]
      [!VAR "NameInSegment" = "as:name(as:ref(./DemReportedEventRef))"!]
      [!WS "2"!][!"as:ref(./DemReportedEventRef)/DemEventId"!]U, /* event ID of reported event: [!"$NameInSegment"!] */
      [!VAR "NumOfLines" = "$NumOfLines + 1"!]
    [!ENDLOOP!]
    };
  [!ENDIF!]

  #define DEM_STOP_SEC_CALIB_16
  #include <Dem_MemMap.h>

  [!IF "node:exists(DemConfigSet/eb-list::*/DemAdvDisplacementPassiveTableLine/eb-list::*)"!]
    #define DEM_START_SEC_CALIB_UNSPECIFIED
    #include <Dem_MemMap.h>

    [!VAR "NumOfLines" = "0"!]
    [!/* !LINKSTO dsn.Dem.Displacement.DemAdvDisplPassiveEvents,1 */!][!//
    /** \brief advanced displacement passive events */
    /* Deviation MISRAC2012-2 */
    CONST(Dem_AdvDisplPassiveTableLinePassiveEventsType, DEM_CONST_CALIBRATION)
    [!WS "2"!]Dem_AdvDisplPassiveTableLinePassiveEvents[DEM_NUM_OF_PASSIVE_TABLE_LINES] =
    {
    [!LOOP "DemConfigSet/eb-list::*/DemAdvDisplacementPassiveTableLine/eb-list::*"!]
      [!VAR "NameInSegment" = "as:name(as:ref(./DemReportedEventRef))"!]
      [!WS "2"!]/* [!"as:name(.)"!] */
      [!WS "2"!]{
      [!WS "4"!]Dem_AdvDisplPassiveEventIdsLine[!"num:integer($NumOfLines)"!], /* array of passive event refs */
      [!WS "4"!]DEM_NUM_OF_PASSIVE_EVENT_REFS_LINE[!"num:integer($NumOfLines)"!], /* number of passive event refs */
      [!WS "2"!]},
      [!VAR "NumOfLines" = "$NumOfLines + 1"!]
    [!ENDLOOP!]
    };

    #define DEM_STOP_SEC_CALIB_UNSPECIFIED
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDIF!]

  [!IF "node:existsAndTrue(DemGeneral/DemOBDSupport)"!]
/*------------------[PID class configuration]---------------------------------*/
    [!LOOP "DemConfigSet/eb-list::*/DemPidClass/eb-list::*"!]
      [!VAR "NumPidElement" = "count(DemPidDataElement/eb-list::*/DemPidDataElementClassRef)"!]
      #define DEM_START_SEC_CONST_16
      #include <Dem_MemMap.h>

      /* !LINKSTO dsn.Dem.OBD.DemPidDataElementIdxOf,1 */
      /** \brief Indexes of data elements contained in [!"as:name(.)"!] */
      STATIC CONST(Dem_OBDFFDataElementIdxType, DEM_CONST)
        [!/* !LINKSTO dsn.Dem.OBD.DemPidDataElementIdxOf.Size,1 */!][!//
        [!WS "2"!]Dem_PidDataElementIdxOf_[!"as:name(.)"!][[!"num:integer($NumPidElement)"!]] =
      {
        [!LOOP "DemPidDataElement/eb-list::*/DemPidDataElementClassRef"!]
          [!VAR "NameInSegment" = "as:name(as:ref(.))"!]
          [!VAR "IdxCtr" = "0"!]
          [!LOOP "as:modconf('Dem')[1]/DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!/* !LINKSTO dsn.Dem.OBD.DemPidDataElementIdxOf.Content,1 */!][!//
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!LOOP "as:modconf('Dem')[1]/DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!/* !LINKSTO dsn.Dem.OBD.DemPidDataElementIdxOf.Order,1 */!][!//
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      };

      /* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementOffsetOf,1 */
      /** \brief Start-bytes of data elements in PIDs [!"as:name(.)"!] */
      STATIC CONST(Dem_OBDFFDataElementOffsetType, DEM_CONST)
        [!/* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementOffsetOf.Size,1 */!][!//
        [!WS "2"!]Dem_PidDataElementOffsetOf_[!"as:name(.)"!][[!"num:integer($NumPidElement)"!]] =
      {
        [!VAR "Offset" = "0"!]
        [!LOOP "DemPidDataElement/eb-list::*/DemPidDataElementClassRef"!]
          [!/* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementOffsetOf.Content,1 */!][!//
          [!WS "2"!][!"num:integer($Offset)"!]U,[!//
          /* [!"as:name(as:ref(.))"!] */
          [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
          [!VAR "Offset" = "$Offset + $SizeOfDataElement"!]
        [!ENDLOOP!]
      };

      #define DEM_STOP_SEC_CONST_16
      #include <Dem_MemMap.h>

      #define DEM_START_SEC_CONST_8
      #include <Dem_MemMap.h>

      /* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementSizesOf,1 */
      /** \brief Size of data elements in PIDs [!"as:name(.)"!] */
      STATIC CONST(uint8, DEM_CONST)
        [!/* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementSizesOf.Size,1 */!][!//
        [!WS "2"!]Dem_PidDataElementSizesOf_[!"as:name(.)"!][[!"num:integer($NumPidElement)"!]] =
      {
        [!LOOP "DemPidDataElement/eb-list::*/DemPidDataElementClassRef"!]
          [!VAR "NameInSegment" = "as:name(as:ref(.))"!]
          [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
          [!/* !LINKSTO dsn.Dem.OBD.Dem_PidDataElementSizesOf.Content,1 */!][!//
          [!WS "2"!][!"$SizeOfDataElement"!]U, /* [!"$NameInSegment"!] */
        [!ENDLOOP!]
      };

      #define DEM_STOP_SEC_CONST_8
      #include <Dem_MemMap.h>
    [!ENDLOOP!]

    [!IF "node:exists(DemConfigSet/eb-list::*/DemPidClass/eb-list::*)"!]
    #define DEM_START_SEC_CALIB_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief OBD freeze frame segments (PIDs) */
     /* !LINKSTO dsn.Dem.OBD.PidClass,1 */
     /* !LINKSTO Dem.SWS_Dem_00597,1 */
     /* !LINKSTO Dem.ECUC_Dem_00733,1 */
     /* Deviation MISRAC2012-2 */
    CONST(Dem_PidClassType, DEM_CONST_CALIBRATION) Dem_PidClass[DEM_NUM_OF_PIDS_IN_OBDFF] =
    {
      [!LOOP "DemConfigSet/eb-list::*/DemPidClass/eb-list::*"!]
        [!WS "2"!]/* [!"as:name(.)"!] */
        [!WS "2"!]{
          [!VAR "PidSize" = "0"!]
          [!LOOP "DemPidDataElement/eb-list::*/DemPidDataElementClassRef"!]
            [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
            [!VAR "PidSize" = "$PidSize + $SizeOfDataElement"!]
          [!ENDLOOP!]
          [!WS "4"!]Dem_PidDataElementOffsetOf_[!"as:name(.)"!],
          [!WS "4"!]Dem_PidDataElementSizesOf_[!"as:name(.)"!],
          [!WS "4"!]Dem_PidDataElementIdxOf_[!"as:name(.)"!],
          [!WS "4"!][!"num:integer($PidSize)"!]U,  /* Size of PID in OBD FF in byte */
          [!WS "4"!][!"num:integer(count(DemPidDataElement/eb-list::*))"!]U,  /* Number of data elements in PID */
          [!WS "4"!]DEM_OBDFF_PID_[!"as:name(.)"!],  /* PID */
        [!WS "2"!]},
      [!ENDLOOP!]
    };

    #define DEM_STOP_SEC_CALIB_UNSPECIFIED
    #include <Dem_MemMap.h>
    [!ENDIF!]
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[Freeze frame classes configuration]--------------------*/
[!//
[!INDENT "0"!]
  [!IF "node:exists(DemGeneral/DemDidClass/eb-list::*)"!]
    #define DEM_START_SEC_CONST_16
    #include <Dem_MemMap.h>
    [!LOOP "DemGeneral/DemDidClass/eb-list::*"!]
      [!VAR "NumFFElement" = "count(DemDidDataElementClassRef/eb-list::*)"!]

      /** \brief Indexes of element on freeze frame data segment
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
        [!WS "2"!]Dem_DataElementIdx[!"as:name(.)"!][[!"num:integer($NumFFElement)"!]] =
      {
        [!LOOP "DemDidDataElementClassRef/eb-list::*"!]
          [!VAR "NameInSegment" = "as:name(as:ref(.))"!]
          [!VAR "IdxCtr" = "0"!]
          [!LOOP "../../../../DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!/* !LINKSTO dsn.Dem.OBD.DemPidDataElementIdxOf.Order,1 */!][!//
          [!LOOP "../../../../DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      };

      /** \brief Start-bytes of element on freeze frame data segment
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
        [!WS "2"!]Dem_DataElementOffset[!"as:name(.)"!][[!"num:integer($NumFFElement)"!]] =
      {
        [!VAR "Offset" = "0"!]
        [!LOOP "DemDidDataElementClassRef/eb-list::*"!]
          [!WS "2"!][!"num:integer($Offset)"!]U, [!//
          [!IF "node:name(as:ref(.)) = 'DemInternalDataElementClass'"!]
            /* [!"as:ref(.)/DemInternalDataElement"!] */
          [!ELSE!][!//
            /* [!"as:name(as:ref(.))"!] */
            [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
            [!VAR "Offset" = "$Offset + $SizeOfDataElement"!]
          [!ENDIF!]
        [!ENDLOOP!]
      };
    [!ENDLOOP!]

    #define DEM_STOP_SEC_CONST_16
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief Freeze frame segments (DIDs) */
    CONST(Dem_FFSegmentType, DEM_CONST)
    Dem_FFSegment[DEM_NUM_FFSEGS] =
    {
      [!LOOP "DemGeneral/DemDidClass/eb-list::*"!]
        [!WS "2"!]/* [!"as:name(.)"!] */
        [!WS "2"!]{
          [!WS "4"!]Dem_DataElementIdx[!"as:name(.)"!],
          [!WS "4"!]Dem_DataElementOffset[!"as:name(.)"!],
          [!WS "4"!]DEM_FFS_DID_[!"as:name(.)"!],
          [!WS "4"!][!"num:integer(count(DemDidDataElementClassRef/eb-list::*))"!]U
        [!WS "2"!]},
      [!ENDLOOP!]
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CALIB_16
    #include <Dem_MemMap.h>

    /* !LINKSTO Dem.Dem_FFSegId.Access,1 */
    [!LOOP "DemGeneral/DemFreezeFrameClass/eb-list::*"!]

      /*---[Freeze frame class [!"as:name(.)"!]]---*/
      [!VAR "NumFFSegs" = "count(DemDidClassRef/eb-list::*)"!]

      /** \brief Indexes of segments on freeze frame class
       ** [!"as:name(.)"!] to ::Dem_FFSegment[]
       **/
       /* Deviation MISRAC2012-2 */
      DEM_STATIC CONST(Dem_FFSegIdxType, DEM_CONST_CALIBRATION)
      Dem_FFSegIdx[!"as:name(.)"!][[!"num:integer($NumFFSegs)"!]] =
      {
        [!LOOP "DemDidClassRef/eb-list::*"!]
          [!WS "2"!][!"node:pos(as:ref(.))"!]U, /* [!"as:name(as:ref(.))"!] */
        [!ENDLOOP!]
      };
    [!ENDLOOP!]

    #define DEM_STOP_SEC_CALIB_16
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief Array containing all freeze frame classes */
    CONST(Dem_FFClassType, DEM_CONST)
    Dem_FFClass[DEM_NUM_FFCLS] =
    {
      [!INDENT "2"!]
        [!LOOP "DemGeneral/DemFreezeFrameClass/eb-list::*"!]
          {
            [!VAR "NumFFSegs" = "count(DemDidClassRef/eb-list::*)"!]
            [!WS "2"!]Dem_FFSegIdx[!"as:name(.)"!],
            [!WS "2"!][!"num:integer($NumFFSegs)"!]U /* number of segments */
          },
        [!ENDLOOP!]
          {
            [!WS "2"!]NULL_PTR,
            [!WS "2"!]0U
          }
      [!ENDINDENT!]
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>
    [!ENDIF!]
[!ENDINDENT!]

/*------------------[Freeze frame record number classes configuration]------*/
[!//
[!INDENT "0"!]
  [!IF "DemGeneral/DemTypeOfFreezeFrameRecordNumeration = 'DEM_FF_RECNUM_CONFIGURED' and node:exists(DemGeneral/DemFreezeFrameRecNumClass/eb-list::*)"!]
    #define DEM_START_SEC_CONST_8
    #include <Dem_MemMap.h>
    [!LOOP "DemGeneral/DemFreezeFrameRecNumClass/eb-list::*"!]
      [!VAR "NumFFRecords" = "count(DemFreezeFrameRecordNumber/eb-list::*)"!]

      /** \brief Freeze frame record numbers for
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_FFIdxType, DEM_CONST)
        [!WS "2"!]Dem_FFRecNumClass[!"as:name(.)"!][[!"num:integer($NumFFRecords)"!]] =
      {
        [!LOOP "DemFreezeFrameRecordNumber/eb-list::*"!]
          [!WS "2"!][!"translate(num:inttohex(., 2), 'abcdef', 'ABCDEF')"!]U,
        [!ENDLOOP!]
      };
    [!ENDLOOP!]

    #define DEM_STOP_SEC_CONST_8
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief Array containing all freeze frame record number classes */
    CONST(Dem_FFRecNumerationClassType, DEM_CONST)
      [!WS "2"!]Dem_FFRecNumerationClass[DEM_NUM_FFRECNUMCLS] =
    {
      [!LOOP "DemGeneral/DemFreezeFrameRecNumClass/eb-list::*"!]
        [!WS "2"!]{
          [!WS "4"!]Dem_FFRecNumClass[!"as:name(.)"!],
          /* number of freeze frame records */
          [!WS "4"!][!"num:integer(count(DemFreezeFrameRecordNumber/eb-list::*))"!]U
        [!WS "2"!]},
      [!ENDLOOP!]
        [!WS "2"!]{
          [!WS "4"!]NULL_PTR,
          [!WS "4"!]0U /* number of freeze frame records */
       [!WS "2"!]}
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[Extended data classes configuration]-------------------*/
[!//
[!INDENT "0"!]
  [!IF "node:exists(DemGeneral/DemExtendedDataRecordClass/eb-list::*)"!]
    #define DEM_START_SEC_CONST_16
    #include <Dem_MemMap.h>
    [!LOOP "DemGeneral/DemExtendedDataRecordClass/eb-list::*"!]
      [!VAR "NumEDElement" = "count(DemDataElementClassRef/eb-list::*)"!]

      /** \brief Indexes of element on extended data segment
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
        [!WS "2"!]Dem_DataElementIdx[!"as:name(.)"!][[!"num:integer($NumEDElement)"!]] =
      {
        [!LOOP "DemDataElementClassRef/eb-list::*"!]
          [!IF "node:name(as:ref(.)) = 'DemInternalDataElementClass'"!]
            [!/* !LINKSTO Dem.SWS_Dem_00472,1 */!][!//
            [!IF "(as:ref(.)/DemInternalDataElement = 'DEM_AGINGCTR_UPCNT') or
                  (as:ref(.)/DemInternalDataElement = 'DEM_AGINGCTR')"!]
              [!WS "2"!]DEM_INT_VAL_IDX_AGECTRUP,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_AGINGCTR_DOWNCNT'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_AGECTRDWN,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCCCTR'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCCCTR,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OVFLIND'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OVFIND,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_SIGNIFICANCE'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_EVSIGNIF,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_SI30'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_SI30,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_CURRENT_FDC'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_CURRENT_FDC,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_FDC12'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_FDC12,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC1'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC1,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC2'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC2,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC3'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC3,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC4'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC4,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC5'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC5,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC6'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC6,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_OCC7'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_OCC7,
            [!/* !LINKSTO Dem.InternalDataElement.Priority.Mapping,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_PRIORITY'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_PRIO,
            [!/* !LINKSTO Dem.InternalDataElement.EventId.Mapping,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_EVENT_ID'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_EVENT_ID,
            [!/* !LINKSTO Dem.MultiEventTriggering.InternalDataElement.RootId.Mapping,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_ROOT_EVENT_ID'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_ROOT_ID,
            [!/* !LINKSTO Dem.SWS_Dem_00984,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_CYCLES_SINCE_FIRST_FAILED'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_CSFF,
            [!/* !LINKSTO Dem.SWS_Dem_00775,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_CYCLES_SINCE_LAST_FAILED'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_CSLF,
            [!/* !LINKSTO Dem.SWS_Dem_00779,1 */!][!//
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_FAILED_CYCLES'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_FAILEDCYCLES,
            [!ELSEIF "as:ref(.)/DemInternalDataElement = 'DEM_MONITOR_ACTIVITY_DATA'"!]
              [!WS "2"!]DEM_INT_VAL_IDX_MAD,
            [!ENDIF!]
          [!ENDIF!]
          [!VAR "NameInSegment" = "as:name(as:ref(.))"!]
          [!VAR "IdxCtr" = "0"!]
          [!LOOP "../../../../DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!LOOP "../../../../DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass']"!]
            [!IF "$NameInSegment = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$NameInSegment"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      };

      /** \brief Start-bytes of element on extended data segment
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
        [!WS "2"!]Dem_DataElementOffset[!"as:name(.)"!][[!"num:integer($NumEDElement)"!]] =
      {
        [!VAR "Offset" = "0"!]
        [!LOOP "DemDataElementClassRef/eb-list::*"!]
          [!WS "2"!][!"num:integer($Offset)"!]U, [!//
          [!IF "node:name(as:ref(.)) = 'DemInternalDataElementClass' or (node:name(as:ref(.)) = 'DemExternalCSDataElementClass' and node:existsAndTrue(as:ref(.)/DemDataElementCaptureOnRetrieval))"!]
            [!IF "node:name(as:ref(.)) = 'DemInternalDataElementClass'"!]
              /* [!"as:ref(.)/DemInternalDataElement"!] */
            [!ELSE!]
              /* [!"as:name(as:ref(.))"!] with DemDataElementCaptureOnRetrieval=true */
            [!ENDIF!]
          [!ELSE!][!//
            /* [!"as:name(as:ref(.))"!] */
            [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
            [!VAR "Offset" = "$Offset + $SizeOfDataElement"!]
          [!ENDIF!]
        [!ENDLOOP!]
      };
    [!ENDLOOP!]

    #define DEM_STOP_SEC_CONST_16
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief Extended data segments (Records) */
    CONST(Dem_EDSegmentType, DEM_CONST) Dem_EDSegment[DEM_NUM_EDSEGS] =
    {
      [!INDENT "2"!]
      [!LOOP "DemGeneral/DemExtendedDataRecordClass/eb-list::*"!]
        /* [!"as:name(.)"!] */
        {
          [!INDENT "4"!]
          Dem_DataElementIdx[!"as:name(.)"!],
          Dem_DataElementOffset[!"as:name(.)"!],
          [!"num:integer(count(DemDataElementClassRef/eb-list::*))"!]U,
          DEM_EDS_NUM_[!"as:name(.)"!],
          [!IF "not(node:exists(DemExtendedDataRecordUpdate))"!]
            TRUE,
          [!ELSE!]
            [!IF "DemExtendedDataRecordUpdate = 'DEM_UPDATE_RECORD_YES'"!]
              TRUE,
            [!ELSE!]
              FALSE,
            [!ENDIF!]
          [!ENDIF!]
          [!IF "node:existsAndTrue(DemExtendedDataRecordAlwaysAvailable)"!]
            TRUE, /* always available */
          [!ELSE!]
            FALSE, /* always available */
          [!ENDIF!]
          [!ENDINDENT!]
        },
      [!ENDLOOP!]
      [!ENDINDENT!]
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>
    [!LOOP "DemGeneral/DemExtendedDataClass/eb-list::*"!]

      #define DEM_START_SEC_CONST_8
      #include <Dem_MemMap.h>

      /*---[Extended data class [!"as:name(.)"!]]---*/
      [!VAR "NumEDSegs" = "count(DemExtendedDataRecordClassRef/eb-list::*)"!]

      /** \brief Indexes of segments on extended data class
       ** [!"as:name(.)"!] to ::Dem_EDSegment[]
       **/
      STATIC CONST(Dem_EDSegIdxType, DEM_CONST)
      Dem_EDSegIdx[!"as:name(.)"!][[!"num:integer($NumEDSegs)"!]] =
      {
        [!LOOP "DemExtendedDataRecordClassRef/eb-list::*"!]
          [!WS "2"!][!"node:pos(as:ref(.))"!]U, /* [!"as:name(as:ref(.))"!] */
        [!ENDLOOP!]
      };

      #define DEM_STOP_SEC_CONST_8
      #include <Dem_MemMap.h>

      #define DEM_START_SEC_CONST_16
      #include <Dem_MemMap.h>

      /** \brief Start-bytes of segments on extended data class
       ** [!"as:name(.)"!]
       **/
      STATIC CONST(Dem_EDStartByteType, DEM_CONST)
        [!WS "2"!]Dem_EDStartByte[!"as:name(.)"!][[!"num:integer($NumEDSegs)"!]] =
      {
        [!VAR "StartByte" = "0"!]
        [!LOOP "DemExtendedDataRecordClassRef/eb-list::*"!]
          [!WS "2"!][!"num:integer($StartByte)"!]U, /* [!"as:name(as:ref(.))"!] */
          [!LOOP "(as:ref(.)/DemDataElementClassRef/eb-list::*)"!]
            [!IF "node:name(as:ref(.)) != 'DemInternalDataElementClass' and (node:name(as:ref(.)) != 'DemExternalCSDataElementClass' or node:existsAndFalse(as:ref(.)/DemDataElementCaptureOnRetrieval))"!]
              [!CALL "GET_SIZE_OF_DATA_ELEMENT"!]
              [!VAR "StartByte" = "$StartByte + $SizeOfDataElement"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      };

      #define DEM_STOP_SEC_CONST_16
      #include <Dem_MemMap.h>
    [!ENDLOOP!]

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /** \brief Array containing all extended data classes */
    CONST(Dem_EDClassType, DEM_CONST)
    Dem_EDClass[DEM_NUM_EDCLS] =
    {
      [!INDENT "2"!]
        [!LOOP "DemGeneral/DemExtendedDataClass/eb-list::*"!]
          {
            [!VAR "NumEDSegs" = "count(DemExtendedDataRecordClassRef/eb-list::*)"!]
            [!WS "2"!]Dem_EDSegIdx[!"as:name(.)"!],
            [!WS "2"!]Dem_EDStartByte[!"as:name(.)"!],
            [!WS "2"!][!"num:integer($NumEDSegs)"!]U /* number of segments */
          },
        [!ENDLOOP!]
          {
            [!WS "2"!]NULL_PTR,
            [!WS "2"!]NULL_PTR,
            [!WS "2"!]0U
          }
      [!ENDINDENT!]
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[Data element classes configuration]--------------------*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>
[!//
[!IF "node:exists(DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass' or node:name(.) = 'DemExternalSRDataElementClass'])"!]
  [!VAR "SRSupport" = "(node:existsAndTrue(DemGeneral/DemRteUsage)) and node:exists(DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass'])"!]
  [!VAR "CaptureOnRetrievalSupport" = "node:exists(DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[(node:name(.) = 'DemExternalCSDataElementClass') and node:existsAndTrue(./DemDataElementCaptureOnRetrieval)])"!]
  [!VAR "EventIdSupport" = "node:exists(DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[(node:name(.) = 'DemExternalCSDataElementClass') and (node:existsAndTrue(./DemDataElementInterfaceWithEventParameter))])"!]
  [!INDENT "0"!]

    /** \brief Array containing all external data elements */
    CONST(Dem_DataElementType, DEM_CONST)
      Dem_DataElement[DEM_NUM_EXT_DATAELEMENTS] =
    {
      [!WS "2"!]/* elements are sorted for optimization reasons presented in design */
      [!LOOP "DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass']"!]
        [!WS "2"!]/* [!"as:name(.)"!] */
        [!WS "2"!]{
          [!IF "node:exists(./DemDataElementReadFnc)"!]
            [!VAR "CallbackName" = "./DemDataElementReadFnc"!]
          [!ELSE!][!//
            [!VAR "CallbackName" = "concat('Rte_Call_CBReadData_', as:name(.), '_ReadData')"!]
          [!ENDIF!]
          [!WS "4"!]/* Deviation MISRAC2012-1 */
          [!WS "4"!]{(Dem_GeneralFuncType)&[!"$CallbackName"!]},
          [!VAR "SizeOfDataElement" = "0"!][!//
          [!IF "node:existsAndTrue(./DemDataElementDataSize)"!][!//
            [!VAR "SizeOfDataElement" = "./DemDataElementDataSize"!][!//
          [!ELSEIF "node:existsAndTrue(./DemDataElementArraySize)"!][!//
            [!VAR "DataTypes" = "substring-before(./DemDataElementDataType, '_N')"!][!//
            [!IF "($DataTypes ='UINT16') or ($DataTypes ='SINT16')"!][!//
              [!VAR "SizeOfDataElement" = "num:integer((./DemDataElementArraySize) * 2)"!][!//
            [!ELSEIF "($DataTypes ='UINT32') or ($DataTypes ='SINT32') or ($DataTypes ='FLOAT32')"!][!//
              [!VAR "SizeOfDataElement" = "num:integer((./DemDataElementArraySize) * 4)"!][!//
            [!ELSE!][!//
              [!VAR "SizeOfDataElement" = "num:integer(./DemDataElementArraySize)"!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!IF "node:exists(./DemDataElementDataType)"!][!//
              [!VAR "DataTypes" = "(./DemDataElementDataType)"!][!//
              [!IF "($DataTypes ='UINT16') or ($DataTypes ='SINT16')"!][!//
                [!VAR "SizeOfDataElement" = "num:integer(2)"!][!//
              [!ELSEIF "($DataTypes ='UINT32') or ($DataTypes ='SINT32') or ($DataTypes ='FLOAT32')"!][!//
                [!VAR "SizeOfDataElement" = "num:integer(4)"!][!//
              [!ELSE!][!//
                [!VAR "SizeOfDataElement" = "num:integer(1)"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
          [!WS "4"!][!"$SizeOfDataElement"!]U,
          [!IF "(./DemDataElementCaptureTrigger = 'DEM_TRIGGER_ON_DEQUALIFICATION')"!]
            [!WS "4"!](DEM_TRIGGER_ON_DEQUALIFICATION << DEM_DATA_ELEMENT_TRIGGER_OFFSET) |
          [!ELSE!][!//
            [!WS "4"!]/* DEM_TRIGGER_ON_QUALIFICATION */
          [!ENDIF!]
          [!IF "node:exists(./DemDataElementDataType)"!][!//
              [!WS "4"!]DEM_READ_DATA_DATA_TYPE_[!"./DemDataElementDataType"!],
          [!ELSE!][!//
              [!WS "4"!]DEM_READ_DATA_DATA_TYPE_UINT8,
          [!ENDIF!]
          [!IF "$EventIdSupport = 'true'"!]
            [!IF "node:existsAndTrue(./DemDataElementInterfaceWithEventParameter)"!]
              [!WS "4"!]TRUE,   /* Event ID support is true */
            [!ELSE!][!//
              [!WS "4"!]FALSE,  /* Event ID support is false */
            [!ENDIF!]
          [!ENDIF!]
          [!IF "$SRSupport = 'true'"!]
            [!WS "4"!]DEM_OPAQUE,  /* default value not used for CS Data Elements */
          [!ENDIF!]
          [!IF "$CaptureOnRetrievalSupport = 'true'"!]
            [!IF "node:existsAndTrue(./DemDataElementCaptureOnRetrieval)"!]
              [!WS "4"!]TRUE  /* CaptureOnRetrieval is true */
            [!ELSE!][!//
              [!WS "4"!]FALSE  /* CaptureOnRetrieval is false */
            [!ENDIF!]
          [!ENDIF!]
        [!WS "2"!]},
      [!ENDLOOP!]
      [!IF "$SRSupport = 'true'"!]
        [!LOOP "DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass']"!]
          [!WS "2"!]/* [!"as:name(.)"!] */
          [!WS "2"!]{
            [!VAR "ReadFunction" = "concat('Rte_Read_Dem_SRDataServices_', as:name(.),'_data')"!]
            [!WS "4"!]/* Deviation MISRAC2012-1 */
            [!WS "4"!]{(Dem_GeneralFuncType)&[!"$ReadFunction"!]},
            [!WS "4"!][!"./DemDataElementDataSize"!]U,
            [!IF "(./DemDataElementCaptureTrigger = 'DEM_TRIGGER_ON_DEQUALIFICATION')"!]
              [!WS "4"!](DEM_TRIGGER_ON_DEQUALIFICATION << DEM_DATA_ELEMENT_TRIGGER_OFFSET) |
            [!ELSE!][!//
              [!WS "4"!]/* DEM_TRIGGER_ON_QUALIFICATION */
            [!ENDIF!]
            [!WS "4"!]DEM_READ_DATA_DATA_TYPE_[!"./DemDataElementDataType"!],
            [!IF "$EventIdSupport = 'true'"!]
              [!WS "4"!]FALSE,  /* Event ID support is false */
            [!ENDIF!]
            [!IF "(node:exists(./DemDataElementEndianness))"!]
              [!WS "4"!]DEM_[!"./DemDataElementEndianness"!],
            [!ELSE!][!//
              [!WS "4"!]DEM_[!"as:modconf('Dem')[1]/DemGeneral/DemDataElementDefaultEndianness"!],
            [!ENDIF!]
            [!IF "$CaptureOnRetrievalSupport = 'true'"!]
              [!WS "4"!]FALSE  /* CaptureOnRetrieval, not used for SR */
            [!ENDIF!]
          [!WS "2"!]},
        [!ENDLOOP!]
      [!ENDIF!]
    };
  [!ENDINDENT!]
[!ENDIF!]

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*------------------[DTC groups configuration]------------------------------*/

[!IF "(node:exists(DemGeneral/DemGroupOfDTC/eb-list::*[as:name(.) != 'DEM_DTC_GROUP_EMISSION_REL_DTCS']))"!]
#define DEM_START_SEC_CONST_32
#include <Dem_MemMap.h>
/** \brief Array containing the DTC group values */
CONST(Dem_DTCGroupType, DEM_CONST) Dem_DTCGroups[DEM_NUM_DTC_GROUPS] =
{
  [!/* sort DTC group values in ascending order, to support search-algorithm */!][!//
  [!LOOP "util:distinct(node:order(DemGeneral/DemGroupOfDTC/eb-list::*[as:name(.) != 'DEM_DTC_GROUP_EMISSION_REL_DTCS'], './DemGroupDTCs'))"!]
    [!WS "2"!]DemConf_DemGroupOfDTC_[!"as:name(.)"!],
  [!ENDLOOP!]
};

#define DEM_STOP_SEC_CONST_32
#include <Dem_MemMap.h>
[!ENDIF!]

/*------------------[Events Class configuration]----------------------------*/

#define DEM_START_SEC_CALIB_UNSPECIFIED
#include <Dem_MemMap.h>

[!VAR "OBDSupport" = "node:value('DemGeneral/DemOBDSupport')"!]
[!VAR "FreezeFrameRecordCapture" = "node:value('DemGeneral/DemFreezeFrameCapture')"!]
[!VAR "EnableConditionGroupNumber" = "num:integer(count(DemGeneral/DemEnableConditionGroup/eb-list::*))"!]
[!IF "$CalibrationWithoutEvCombSupport = 'true'"!]
[!CALL "GET_VCC_OCC5_USED"!][!//
[!CALL "CREATE_EVENT_CLASS_LIST"!]
[!CALL "CREATE_PRIORITY_VALUE_LIST"!][!//
/** \brief EventClass configuration description table */
/* Deviation MISRAC2012-2 */
CONST(Dem_EventClassDescType, DEM_CONST_CALIBRATION) Dem_EventClassDesc[DEM_NUMBER_OF_EVENT_CLASSES] =
{
  [!INDENT "2"!]
  [!VAR "EventClassIdx" = "0"!]
  [!LOOP "text:split($EventClassList, '#')"!]
  [!VAR "EventClassString" = "."!]
   /* Event Class [!"num:i($EventClassIdx)"!] */
  [!VAR "EventClassIdx" = "$EventClassIdx + 1"!]
  {
    [!INDENT "4"!]
    [!IF "$NumMultiEventTriggering > 0"!]
      /* Multi-event triggering index */
      [!VAR "MultiEventTriggeringClassIdx" = "substring-before($EventClassString,'T')"!]
      [!IF "$MultiEventTriggeringClassIdx = '-'"!]
        DEM_MULTIEVENTTRIGGERINGIDX_UNUSED,
      [!ELSE!][!//
        [!"substring-before($EventClassString,'T')"!]U,
      [!ENDIF!]
    [!ENDIF!]
    [!VAR "EventClassString" = "substring-after($EventClassString, 'T')"!]
    [!IF "$CalibrationSupport = 'true'"!]
      [!VAR "IndicatorClassIdx" = "substring-before($EventClassString,'I')"!]
      [!IF "$IndicatorClassIdx = '-'"!]
        DEM_INDICATOR_UNUSED,
      [!ELSE!][!//
        [!"$IndicatorClassIdx"!]U,
      [!ENDIF!]
    [!ENDIF!]
    [!VAR "EventClassString" = "substring-after($EventClassString, 'I')"!]
    /* DemAgingCycleCounterThreshold (if 0 DemAgingAllowed == 'false')*/
    [!"substring-before($EventClassString,'A')"!]U,
    [!VAR "EventClassString" = "substring-after($EventClassString, 'A')"!]
    [!IF "$VccOcc5Used = 1"!]
      /* DemOBDAgingCycleCounterThreshold */
      [!"substring-before($EventClassString,'O')"!]U,
    [!ENDIF!]
    [!VAR "EventClassString" = "substring-after($EventClassString, 'O')"!]
    /* DemEventFailureCycleCounterThreshold (0 if disabled')*/
    [!"substring-before($EventClassString,'F')"!]U,
    [!VAR "EventClassString" = "substring-after($EventClassString, 'F')"!]
    /* Event priority (0 = most important) */
    [!CALL "GET_INTERNAL_PRIORITY_IDX", "Prio" = "num:i(substring-before($EventClassString,'P'))"!]
    [!"num:i($PriorityValueIdx)"!]U,
    [!VAR "EventClassString" = "substring-after($EventClassString, 'P')"!]
    [!/* !LINKSTO dsn.Dem.CommonOperationCycle.Dem_EventClassDesc,1 */!][!//
    [!IF "$CommonOperationCycleEnabled = 'true'"!]
      /* Operation cycle*/
      [!"substring-before($EventClassString,'!')"!],
      [!VAR "EventClassString" = "substring-after($EventClassString, '!')"!]
    [!ENDIF!]
    [!IF "$AgingAllowedSeperateFlag = 'true'"!]
      /* DemAgingAllowed */
      [!"substring-before($EventClassString,'?')"!],
      [!VAR "EventClassString" = "substring-after($EventClassString, '?')"!]
    [!ENDIF!]
    [!IF "($OBDSupport = 'true') or ($FreezeFrameRecordCapture = 'DEM_TRIGGER_ON_FDC_THRESHOLD')"!][!//
      /* Bitfield for boolean values
      [!WS!]*   bit 0: DemMinRatio
      [!WS!]*   bit 1: DemFreezeFrameUpdate (always true, for calibration use only)
      [!WS!]*/
      ((uint8)[!"substring-before($EventClassString,'M')"!]U)
      [!/* !LINKSTO Dem.EB.EventClass.FreezeFrameUpdate.Default,1 */!][!//
      | ((uint8)(DEM_FFUPDATEEVENTCLASS_MASK & 1U) << DEM_FFUPDATEEVENTCLASS_OFFSET),
    [!ENDIF!]
    [!VAR "EventClassString" = "substring-after($EventClassString, 'M')"!]
    [!IF "$EnableConditionGroupNumber > 0"!]
      /* enable condition group */
      [!VAR "EnCondGrpIdx" = "substring-before($EventClassString,'&')"!]
      [!IF "$EnCondGrpIdx = '-'"!]
        DEM_ENCONDITIONGROUP_UNUSED
      [!ELSE!][!//
        [!"substring-before($EventClassString,'&')"!]U
      [!ENDIF!]
      [!VAR "EventClassString" = "substring-after($EventClassString, '&')"!]
    [!ENDIF!]
    [!ENDINDENT!]
  },
  [!ENDLOOP!]
  [!ENDINDENT!]
};
[!ENDIF!]

#define DEM_STOP_SEC_CALIB_UNSPECIFIED
#include <Dem_MemMap.h>

/*------------------[Events configuration]----------------------------------*/
[!CALL "CREATE_DTCCLASS_LIST_FROM_EVENTS"!][!//
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_TYPE1'"!][!//
  [!CALL "CALC_DESCRIPTION", "Array" = "$DTCDescStr"!][!//
[!ENDIF!][!//
[!CALL "CALC_MULTI_EVENT_CLASSES"!][!//
[!CALL "CALC_DESCRIPTION", "Array" = "$EventDescStr"!][!//

[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_TYPE1'"!][!//
[!IF "$CalDtcConfigIdxOffset = 0"!][!//
#define DEM_START_SEC_CONST_[!"$CalDtcConfigIdxWidth"!]
#include <Dem_MemMap.h>

CONST(Dem_DTCConfIdxType, DEM_CONST) Dem_EventDTCConfIdx[DEM_NUMBER_OF_EVENTS] =
{
    ( 0U ),                                 /* invalid event id entry */
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
      [!CALL "BUILD_DESCRIPTION", "Array" = "$DTCConfIdxStr"!][!//
    [!ENDLOOP!]
};

#define DEM_STOP_SEC_CONST_[!"$CalDtcConfigIdxWidth"!]
#include <Dem_MemMap.h>
[!ENDIF!]
[!ENDIF!]

#define DEM_START_SEC_CALIB_32
#include <Dem_MemMap.h>

/** \brief Event configuration description table (uses 'bit packing scheme) */
/* Deviation MISRAC2012-2 */
CONST(Dem_EventDescType, DEM_CONST_CALIBRATION) Dem_EventDesc[DEM_NUMBER_OF_EVENTS] =
{
[!CALL "CREATE_PRIORITY_VALUE_LIST"!][!//
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
  [!CALL "DEBOUNCE_COUNTER_CLASS_CALC"!][!//
[!ENDIF!][!//
  [!"$EventDescEmptyStr"!]
[!/* generate event descriptions */!][!//
[!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
  [!WS "2"!]{ /* event: [!"as:name(.)"!] */
  [!CALL "BUILD_DESCRIPTION", "Array" = "$EventDescStr"!][!//
  [!WS "2"!]},
[!ENDLOOP!][!//
};

#define DEM_STOP_SEC_CALIB_32
#include <Dem_MemMap.h>

[!CALL "CALC_OBD_MEMSEC_VARS"!][!//
[!CALL "CALC_DESCRIPTION", "Array" = "$OBDConfigStr"!][!//
[!IF "not(DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED')"!][!//
#define DEM_START_SEC_[!"$ObdDTCDataSection"!]_32
#include <Dem_MemMap.h>

/** \brief DTC configuration description table (uses 'bit packing scheme)
 ** contains DTC related configuration data for
 **   - events without event combination
 **   - the master configuration event in case of event combination
 **   - events without DTC class (referred to by Dem_EventDesc[] entry)
 **/
/* Deviation MISRAC2012-2 */
CONST(Dem_DTCDescType, [!"$ObdDTCMemSection"!]) Dem_DTCDesc[DEM_NUMBER_OF_DTCS] =
{
[!/* creation of 'PriorityValueList' (unique list of all configured
   * priority values ordered in ascending order) was done via CREATE_PRIORITY_VALUE_LIST */!][!//
[!//
  [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
    [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
[!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
    [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
[!//
      [!IF "node:exists(DemDTCClassRef)"!][!//
[!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
   * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
        [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
      [!ELSE!][!/* No DTC class or no UDS-DTC configured */!][!//
        [!VAR "EventDTCClassName" = "node:name(.)"!][!//
      [!ENDIF!][!//
      [!IF "$DTCClassName = $EventDTCClassName"!][!//
[!/* output is generated for events without DTC class, events without event combination and for
   * the master configuration event of event combinations */!][!//
        [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
          [!IF "(node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
            [!WS "2"!]/* UDS-DTC of Master Configuration Event: [!"as:name(.)"!] */
          [!ELSE!][!//
            [!WS "2"!]/* UDS-DTC of Event: [!"as:name(.)"!] */
          [!ENDIF!][!//
          [!WS "2"!]{
          [!/* !LINKSTO Dem.DemInternalDataElementRange.EventSignificance,1 */!][!//
          [!/* !LINKSTO Dem.DemInternalDataElementRange.EventSignificance,1 */!][!//
          [!CALL "BUILD_DESCRIPTION", "Array" = "$DTCDescStr"!][!//
        [!WS "2"!]},
[!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
   * only one event is mapped to an UDS-DTC (the Master Configuration Event in case of event combination) */!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
};

#define DEM_STOP_SEC_[!"$ObdDTCDataSection"!]_32
#include <Dem_MemMap.h>
[!ENDIF!][!//



[!IF "not(DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED')"!][!//
[!IF "$DemNbOfCmbDTCs > 0"!][!//
#define DEM_START_SEC_CONST_16
#include <Dem_MemMap.h>
CONST(Dem_CmbDTCEvLnkType, DEM_CONST) Dem_CmbDTCEvLnk[DEM_NUM_CMB_DTCS + 1U] =
{
  [!LOOP "text:split($DemCmbDTCEvLnkList, '#')"!][!//
    [!WS "2"!][!"num:integer(.)"!]U,
  [!ENDLOOP!][!//
};

CONST(Dem_EventIdType, DEM_CONST) Dem_CmbDTCEvents[DEM_NUM_CMB_EVENTS] =
{
  [!VAR "DTCClassName" = "''"!]
  [!FOR "EventCtr" = "1" TO "$DemNbOfCmbEvents"!]
    [!VAR "EventId" = "text:split($DemCmbDTCEventsList, '#')[position() = $EventCtr]"!]
    [!IF "not($DTCClassName = as:name(as:ref(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemDTCClassRef)))"!]
      [!VAR "DTCClassName" = "as:name(as:ref(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId]/DemDTCClassRef))"!]
      [!WS "2"!]/* Next group of combined events assigned to DemDTCClassRef = [!"$DTCClassName"!] */
    [!ENDIF!]
    [!WS "2"!]DemConf_DemEventParameter_[!"node:name(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[number(DemEventId) = $EventId])"!],
  [!ENDFOR!]
};
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!ENDIF!]

[!IF "node:existsAndTrue(DemGeneral/DemEventDisplacementSupport)"!]
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

CONST(Dem_PriorityType, DEM_CONST) Dem_ExternalPrioValue[DEM_NUM_EVENT_PRIORITIES] =
{
[!LOOP "text:split($PriorityValueList, '#')"!]
  [!WS "2"!](uint8)[!"."!]U,
[!ENDLOOP!]
};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>

[!ENDIF!]

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
[!VAR "BitIndex" = "1"!][!// Skip pos 0 which is allocated for invalid event
[!VAR "ByteVal" = "0"!][!//
#if (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)
/** \brief Generate the const array Dem_StatusBitStorageTF[],
 ** only if not all configured events do have the same
 ** DemStatusBitStorageTestFailedPerEvent value. */
CONST(uint8, DEM_CONST) Dem_StatusBitStorageTF[DEM_STATUS_BIT_STORAGE_TF_ARRAY_SIZE] =
{
  [!INDENT "2"!]
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    [!IF "node:existsAndTrue(DemStatusBitStorageTestFailedPerEvent)"!][!//
      [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
    [!ENDIF!]
    [!VAR "BitIndex" = "$BitIndex + 1"!]
    [!IF "($BitIndex = 8)"!]
      [!"num:inttohex($ByteVal, 2)"!]U,
      [!VAR "ByteVal" = "0"!]
      [!VAR "BitIndex" = "0"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "($BitIndex != 0)"!]
    [!"num:inttohex($ByteVal, 2)"!]U
  [!ENDIF!]
  [!ENDINDENT!]
};
#endif

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>

[!IF "node:existsAndTrue(DemGeneral/DemJ1939Support)"!]
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

  [!INDENT "0"!]
    [!CALL "CREATE_J1939_NODE_LIST"!][!//
    [!IF "$NumJ1939Nodes > 0"!][!//
      CONST(uint8, DEM_CONST) Dem_J1939NmNodeIds[DEM_MAX_NUM_J1939_NODES] =
      {
        [!LOOP "text:split($J1939NodeList, '#')"!][!//
          [!WS "2"!]/* [!"text:split(., ':')[position() = 2]"!] */
          [!WS "2"!][!"text:split(., ':')[position() = 1]"!],
        [!ENDLOOP!][!//
      };
      [!IF "$ReadinessJ1939Support = 'true'"!][!//

        CONST(uint8, DEM_CONST) Dem_RGP_J1939NmNodes[DEM_RGP_NUM_J1939_READINESS_NODES] =
        {
          [!LOOP "text:split($J1939NodeListWithReadiness, '#')"!][!//
            [!WS "2"!]/* [!"text:split(., ':')[position() = 2]"!] */
            [!WS "2"!][!"text:split(., ':')[position() = 1]"!],
          [!ENDLOOP!][!//
        };
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDINDENT!]

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

[!VAR "NodeName" = "''"!][!//
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
/** \brief J1939 specific event configuration description table
 ** containing Node Idx and J1939 DTC value */
CONST(Dem_J1939DtcAndNodeBitfieldType, DEM_CONST) Dem_EventJ1939DtcAndNode[DEM_NUMBER_OF_EVENTS] =
{
  [!INDENT "2"!][!//
    ((uint32)(DEM_J1939_INVALID_NODE_IDX) << DEM_J1939_NODE_IDX_OFFSET), /* invalid event id and node entry */
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
      /* [!"as:name(.)"!] */
      [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemJ1939DTCValue)"!][!//
        [!VAR "NodeIdx" = "0"!][!//
        [!VAR "NodeName" = "text:split(node:value(as:ref(./DemDTCClassRef)/DemJ1939NodeRef),'/')[last()]"!][!//
        [!LOOP "text:split($J1939NodeList, '#')"!][!//
          [!IF "text:contains(text:split(., ":")[position() = '2'], $NodeName)"!][!//
            /* Index of [!"$NodeName"!] */
            ((uint32)([!"translate(num:inttohex($NodeIdx, 2), 'abcdef', 'ABCDEF')"!]U) << DEM_J1939_NODE_IDX_OFFSET) |
            [!BREAK!][!//
          [!ENDIF!][!//
          [!VAR "NodeIdx" = "$NodeIdx + 1"!][!//
        [!ENDLOOP!][!//
        /* J1939-DTC value */
        [!"translate(num:inttohex(as:ref(DemDTCClassRef)/DemJ1939DTCValue, 6), 'abcdef', 'ABCDEF')"!]U,
      [!ELSE!][!/* No DTC class configured and no node index is referenced */!][!//
        /* No J1939-DTC value and no Node Idx referenced */
        (Dem_J1939DtcAndNodeBitfieldType)(((uint32)(DEM_J1939_INVALID_NODE_IDX) << DEM_J1939_NODE_IDX_OFFSET) |
        (uint32)(DEM_NO_DTC)),
      [!ENDIF!][!//
    [!//
    [!ENDLOOP!][!//
  [!ENDINDENT!]
};
[!ELSE!][!// "DemGeneral/DemEventCombinationSupport != 'DEM_EVCOMB_DISABLED'
/** \brief J1939 specific event configuration description table
 ** containing Node Idx and J1939 DTC value */
CONST(Dem_J1939DtcAndNodeBitfieldType, DEM_CONST) Dem_EventJ1939DtcAndNode[DEM_NUMBER_OF_DTCS] =
{
  [!INDENT "2"!]
    [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
      [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
      [!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
      [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
        [!IF "node:exists(DemDTCClassRef)"!][!//
          [!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
             * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
          [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
        [!ELSE!][!/* No DTC class */!][!//
          [!VAR "EventDTCClassName" = "node:name(.)"!][!//
        [!ENDIF!][!//
        [!IF "$DTCClassName = $EventDTCClassName"!][!//
          [!/* output is generated for events without DTC class, events without event combination and for
             * the master configuration event of event combinations */!][!//
          [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
            [!IF "(node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
              /* J1939-DTC of Master Configuration Event: [!"as:name(.)"!] */
            [!ELSE!][!//
              /* J1939-DTC of Event: [!"as:name(.)"!] */
            [!ENDIF!][!//
            [!IF "node:exists(DemDTCClassRef) and node:exists(as:ref(DemDTCClassRef)/DemJ1939DTCValue)"!][!//
              [!VAR "NodeIdx" = "0"!][!//
              [!VAR "NodeName" = "text:split(node:value(as:ref(./DemDTCClassRef)/DemJ1939NodeRef),'/')[last()]"!][!//
              [!LOOP "text:split($J1939NodeList, '#')"!][!//
                [!IF "text:contains(text:split(., ":")[position() = '2'], $NodeName)"!][!//
                  /* Index of [!"$NodeName"!] */
                  ((uint32)([!"translate(num:inttohex($NodeIdx, 2), 'abcdef', 'ABCDEF')"!]U) << DEM_J1939_NODE_IDX_OFFSET) |
                  [!BREAK!][!//
                [!ENDIF!][!//
                [!VAR "NodeIdx" = "$NodeIdx + 1"!][!//
              [!ENDLOOP!][!//
              /* J1939-DTC value */
              [!"translate(num:inttohex(as:ref(DemDTCClassRef)/DemJ1939DTCValue, 6), 'abcdef', 'ABCDEF')"!]U,
            [!ELSE!][!/* No DTC class configured and no node referenced */!][!//
              /* No J1939-DTC Value and no node index referenced */
              (Dem_J1939DtcAndNodeBitfieldType)(((uint32)(DEM_J1939_INVALID_NODE_IDX) << DEM_J1939_NODE_IDX_OFFSET) |
              (uint32)(DEM_NO_DTC)),
            [!ENDIF!][!//
            [!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
               * only one event is mapped to an J1939-DTC (the Master Configuration Event in case of event combination) */!][!//
            [!BREAK!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
  [!ENDINDENT!][!//
};
[!ENDIF!][!//

[!IF "node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemGeneralJ1939/DemJ1939FreezeFrameSupport) "!]
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
/** \brief J1939 event specific J1939 freeze frame class index */
CONST(Dem_J1939FFClassIdxType, DEM_CONST) Dem_EventJ1939FFClassIdx[(DEM_NUMBER_OF_EVENTS)] =
{
  [!INDENT "2"!][!//
    DEM_J1939FFCLS_NULL_IDX,            /* invalid event id entry */
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!][!//
      /* [!"as:name(.)"!] */
      [!INDENT "2"!][!//
        [!IF "((node:exists(DemDTCClassRef)) and (node:exists(as:ref(DemDTCClassRef)/DemJ1939DTCValue)) and (node:refvalid(./DemJ1939FreezeFrameClassRef)))"!][!//
          [!/*  -----[DemJ1939FreezeFrameClassRef]----- */!][!//
          [!"node:pos(as:ref(./DemJ1939FreezeFrameClassRef))"!]U, /* J1939 Freeze Frame Class Index - [!"as:name(as:ref(./DemJ1939FreezeFrameClassRef))"!] */
        [!ELSE!][!/* No Freeze Frame is referenced */!][!//
          (Dem_J1939FFClassIdxType)(DEM_J1939FFCLS_NULL_IDX), /* No Configured J1939Freeze Frame */
        [!ENDIF!][!//
      [!ENDINDENT!][!//
      [!//
    [!ENDLOOP!][!//
  [!ENDINDENT!]
};
[!ELSE!][!// "DemGeneral/DemEventCombinationSupport != 'DEM_EVCOMB_DISABLED'
/** \brief J1939 event specific J1939 freeze frame class index */
CONST(Dem_J1939FFClassIdxType, DEM_CONST) Dem_EventJ1939FFClassIdx[(DEM_NUMBER_OF_DTCS)] =
{
  [!INDENT "0"!]
    [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
      [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
      [!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
      [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
        [!IF "node:exists(DemDTCClassRef)"!][!//
          [!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
             * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
          [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
        [!ELSE!][!/* No DTC class */!][!//
          [!VAR "EventDTCClassName" = "node:name(.)"!][!//
        [!ENDIF!][!//
        [!IF "$DTCClassName = $EventDTCClassName"!][!//
          [!/* output is generated for events without DTC class, events without event combination and for
             * the master configuration event of event combinations */!][!//
          [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
            [!IF "(node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
              /* J1939-DTC of Master Configuration Event: [!"as:name(.)"!] */
            [!ELSE!][!//
              /* J1939-DTC of Event: [!"as:name(.)"!] */
            [!ENDIF!][!//
            [!WS "2"!]
            [!IF "((node:exists(DemDTCClassRef)) and (node:exists(as:ref(DemDTCClassRef)/DemJ1939DTCValue)) and (node:refvalid(./DemJ1939FreezeFrameClassRef)))"!][!//
              [!/*  -----[DemJ1939FreezeFrameClassRef]----- */!][!//
              [!"node:pos(as:ref(./DemJ1939FreezeFrameClassRef))"!]U, /* J1939 Freeze Frame Class Index - [!"as:name(as:ref(./DemJ1939FreezeFrameClassRef))"!] */
            [!ELSE!][!/* No J1939Freeze is referenced */!][!//
              (Dem_J1939FFClassIdxType)(DEM_J1939FFCLS_NULL_IDX), /* No Configured J1939Freeze Frame Class */
            [!ENDIF!][!//
            [!WS "2"!]
            [!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
               * only one event is mapped to an J1939-DTC (the Master Configuration Event in case of event combination) */!][!//
            [!BREAK!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
  [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDIF!][!//
/*------------------[J1939 Freeze Frame configuration]----------------------------------*/
[!IF "node:existsAndTrue(as:modconf('Dem')[1]/DemGeneral/DemGeneralJ1939/DemJ1939FreezeFrameSupport) "!]
[!//
[!INDENT "0"!]
  [!IF "node:exists(DemGeneral/DemSPNClass/eb-list::*)"!]

    [!LOOP "DemGeneral/DemJ1939FreezeFrameClass/eb-list::*"!]
      /*---[J1939 Freeze frame class [!"as:name(.)"!]]---*/
      [!VAR "NumJ1939FFSegs" = "count(DemSPNClassRef/eb-list::*)"!]
      /** \brief J1939 Freeze frame data element class indexes linked
       ** to the configured SPNs */
      STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
      Dem_J1939FFDataElementClassIdx[!"as:name(.)"!][[!"num:integer($NumJ1939FFSegs)"!]] =
      {
        [!LOOP "DemSPNClassRef/eb-list::*"!]
          [!WS "2"!]/* [!"as:name(as:ref(.))"!] */
          [!VAR "DEClassName" = "as:name(as:ref(as:ref(.)/DemSPNDataElementClassRef))"!]
          [!VAR "IdxCtr" = "0"!]
          [!LOOP "as:modconf('Dem')[1]/DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalCSDataElementClass']"!]
            [!IF "$DEClassName = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$DEClassName"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!LOOP "as:modconf('Dem')[1]/DemGeneral/DemDataElementClass/eb-choice::*[1]/eb-list::*[node:name(.) = 'DemExternalSRDataElementClass']"!]
            [!IF "$DEClassName = as:name(.)"!]
              [!WS "2"!][!"num:integer($IdxCtr)"!]U, /* [!"$DEClassName"!] */
              [!BREAK!]
            [!ELSE!][!//
              [!VAR "IdxCtr" = "$IdxCtr + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      };
    [!ENDLOOP!]


    /** \brief Array containing all J1939 freeze frame classes */
    CONST(Dem_J1939FFClassType, DEM_CONST)
    Dem_J1939FFClass[DEM_NUM_J1939FFCLS] =
    {
      [!INDENT "2"!]
        [!LOOP "DemGeneral/DemJ1939FreezeFrameClass/eb-list::*"!]
          {
            [!VAR "NumJ1939FFSegs" = "count(DemSPNClassRef/eb-list::*)"!]
            [!WS "2"!]Dem_J1939FFDataElementClassIdx[!"as:name(.)"!],
            [!WS "2"!][!"num:integer($NumJ1939FFSegs)"!]U /* number of SPNs */
          },
        [!ENDLOOP!]
          {
            [!WS "2"!]NULL_PTR,
            [!WS "2"!]0U
          }
      [!ENDINDENT!]
    };

  [!ENDIF!]
[!ENDINDENT!]
[!ENDIF!]
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "(node:existsAndTrue(DemGeneral/DemOBDSupport))"!]
[!IF "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"!][!//
/* !LINKSTO dsn.Dem_OBD_0018,3 */
/* !LINKSTO dsn.Dem.OBD.config.0001,3 */
[!CALL "GET_VCC_OCC5_USED"!][!//
[!IF " ($VccOcc5Used = 1) and ($CalibrationWithoutEvCombSupport = 'false')"!]
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
/** \brief Array containing all OBD Aging Cycle Counter Threshold */
CONST(uint8, DEM_CONST) Dem_OBDAgingCycleThreshold[DEM_NUMBER_OF_EVENTS] =
{
  0U,  /* invalid event id entry */
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    /* [!"as:name(.)"!] */
    [!INDENT "2"!]
      [!IF "node:existsAndTrue(DemEventClass/DemAgingAllowed)"!][!//
         [!"DemEventClass/DemOBDAgingCycleCounterThreshold"!]U,
      [!ELSE!][!//
         DEM_AGING_CYC_CNT_DISABLED,
      [!ENDIF!]
    [!ENDINDENT!]
  [!ENDLOOP!]
};
#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "$DemObdDTCSupport = 'true'"!][!//
[!CALL "CALC_DESCRIPTION", "Array" = "$OBDDTCStr"!][!//
#define DEM_START_SEC_[!"$ObdDTCDataSection"!]_16
#include <Dem_MemMap.h>
/** \brief Array containing all OBD DTCs */
/* Deviation MISRAC2012-2 */
CONST(uint16, [!"$ObdDTCMemSection"!]) Dem_OBDDTC[DEM_NUMBER_OF_EVENTS] =
{
  0U,  /* invalid event id entry */
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    /* [!"as:name(.)"!] */
    [!CALL "BUILD_DESCRIPTION", "Array" = "$OBDDTCStr"!][!//
  [!ENDLOOP!]
};
#define DEM_STOP_SEC_[!"$ObdDTCDataSection"!]_16
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "not(($ObdUdsDtcSeparationSupport = 'false') and ($DTCClassAvailable = 'false') and ($CalibrationWithoutEvCombSupport = 'true'))"!]
#define DEM_START_SEC_[!"$ObdConfigDataSection"!]_[!"$ObdTypeWidth"!]
#include <Dem_MemMap.h>
/** \brief Array containing bit packed three byte OBD DTCs, WWHOBD DTC Class and Readiness value
 ** (depending on configuration) */
/* !LINKSTO dsn.Dem.OBD.config.DtcValue3Byte.0001,2 */
/* !LINKSTO dsn.Dem.OBD.config.DemWWHOBDDTCClass.001,1 */
/* !LINKSTO dsn.Dem.OBD.config.DemEventOBDReadinessGroup.0001,2 */
 /* Deviation MISRAC2012-2 */
CONST(uint[!"$ObdTypeWidth"!], [!"$ObdConfigMemSection"!]) Dem_OBDConfig[DEM_NUMBER_OF_EVENTS] =
{
  0U,  /* invalid event id entry */
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    [!WS "2"!]
    /* [!"as:name(.)"!] */
    [!CALL "BUILD_DESCRIPTION", "Array" = "$OBDConfigStr"!][!//
  [!ENDLOOP!]
};
#define DEM_STOP_SEC_[!"$ObdConfigDataSection"!]_[!"$ObdTypeWidth"!]
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!ELSE!][!// "DemGeneral/DemEventCombinationSupport != 'DEM_EVCOMB_DISABLED'"
[!//
[!CALL "GET_VCC_OCC5_USED"!][!//
[!IF "($VccOcc5Used = 1)"!]
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
/** \brief Array containing all OBD Aging Cycle Counter Threshold */
CONST(uint8, DEM_CONST) Dem_OBDAgingCycleThreshold[DEM_NUMBER_OF_DTCS] =
{
[!INDENT "0"!]
  [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
    [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
[!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
    [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
      [!IF "node:exists(DemDTCClassRef)"!][!//
[!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
   * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
        [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
      [!ELSE!][!/* No DTC class or no OBD-DTC configured */!][!//
        [!VAR "EventDTCClassName" = "node:name(.)"!][!//
      [!ENDIF!][!//
      [!IF "$DTCClassName = $EventDTCClassName"!][!//
[!/* output is generated for events without DTC class, events without event combination and for
   * the master configuration event of event combinations */!][!//
        [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
          [!IF "(node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
            [!WS "2"!]/* OBD-DTC of Master Configuration Event: [!"as:name(.)"!] */
          [!ELSE!][!//
            [!WS "2"!]/* OBD-DTC of Event: [!"as:name(.)"!] */
          [!ENDIF!][!//
          [!WS "2"!]{
            [!IF "node:existsAndTrue(DemEventClass/DemAgingAllowed)"!][!//
              [!"DemEventClass/DemOBDAgingCycleCounterThreshold"!]U
            [!ELSE!][!//
              DEM_AGING_CYC_CNT_DISABLED
            [!ENDIF!]
          [!WS "2"!]},
[!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
   * only one event is mapped to an UDS-DTC (the Master Configuration Event in case of event combination) */!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
};
#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "$DemObdDTCSupport = 'true'"!][!//
[!CALL "CALC_DESCRIPTION", "Array" = "$OBDDTCStr"!][!//
#define DEM_START_SEC_[!"$ObdDTCDataSection"!]_16
#include <Dem_MemMap.h>
/** \brief Array containing all OBD DTCs */
/* Deviation MISRAC2012-2 */
CONST(uint16, [!"$ObdDTCMemSection"!]) Dem_OBDDTC[DEM_NUMBER_OF_DTCS] =
{
[!INDENT "0"!]
  [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
    [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
[!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
    [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
      [!IF "node:exists(DemDTCClassRef)"!][!//
[!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
   * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
        [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
      [!ELSE!][!/* No DTC class or no OBD-DTC configured */!][!//
        [!VAR "EventDTCClassName" = "node:name(.)"!][!//
      [!ENDIF!][!//
      [!IF "$DTCClassName = $EventDTCClassName"!][!//
[!/* output is generated for events without DTC class, events without event combination and for
   * the master configuration event of event combinations */!][!//
        [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
          [!IF "(DemEvtCmbCommonParamMaster = 'true')"!][!//
            [!WS "2"!]/* OBD-DTC of Master Configuration Event: [!"as:name(.)"!] */
          [!ELSE!][!//
            [!WS "2"!]/* OBD-DTC of Event: [!"as:name(.)"!] */
          [!ENDIF!][!//
          [!WS "2"!]
          [!CALL "BUILD_DESCRIPTION", "Array" = "$OBDDTCStr"!][!//
          [!WS "2"!]
[!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
   * only one event is mapped to an UDS-DTC (the Master Configuration Event in case of event combination) */!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
};
#define DEM_STOP_SEC_[!"$ObdDTCDataSection"!]_16
#include <Dem_MemMap.h>
[!ENDIF!][!// ($DemObdDTCSupport = 'true')
[!//
/* !LINKSTO dsn.Dem_OBD_0019,2 */
/* !LINKSTO dsn.Dem.OBD.config.0002,2 */
[!IF "not(($ObdUdsDtcSeparationSupport = 'false') and ($DTCClassAvailable = 'false') and ($CalibrationWithoutEvCombSupport = 'true'))"!]
#define DEM_START_SEC_[!"$ObdConfigDataSection"!]_[!"$ObdTypeWidth"!]
#include <Dem_MemMap.h>
/** \brief Array containing bit packed three byte OBD DTCs, WWHOBD DTC Class and Readiness value
 ** (depending on configuration) */
/* !LINKSTO dsn.Dem.OBD.config.DtcValue3Byte.0001,2 */
/* !LINKSTO dsn.Dem.OBD.config.DemWWHOBDDTCClass.001,1 */
/* !LINKSTO dsn.Dem.OBD.config.DemEventOBDReadinessGroup.0001,2 */
 /* Deviation MISRAC2012-2 */
CONST(uint[!"$ObdTypeWidth"!], [!"$ObdConfigMemSection"!]) Dem_OBDConfig[DEM_NUMBER_OF_DTCS] =
{
[!INDENT "0"!]
  [!FOR "DTCCtr" = "0" TO "num:integer($DemNbOfDTCClasses) - 1"!][!//
    [!VAR "DTCClassName" = "text:split($DemDTCClassList, '#')[position() = $DTCCtr+1]"!][!//
[!/* for performance reasons, looping is not performed in DemEventId order (not needed) */!][!//
    [!LOOP "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!][!//
      [!IF "node:exists(DemDTCClassRef)"!][!//
[!/* for performance reasons, the name (always unique) is extracted from the SHORT-NAME-path string
   * instead of using the node function "as:name(as:ref(DemDTCClassRef))" */!][!//
        [!VAR "EventDTCClassName" = "text:split(DemDTCClassRef, '/')[last()]"!][!//
      [!ELSE!][!/* No DTC class or no OBD-DTC configured */!][!//
        [!VAR "EventDTCClassName" = "node:name(.)"!][!//
      [!ENDIF!][!//
      [!IF "$DTCClassName = $EventDTCClassName"!][!//
[!/* output is generated for events without DTC class, events without event combination and for
   * the master configuration event of event combinations */!][!//
        [!IF "not(node:exists(DemDTCClassRef)) or not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))"!][!//
          [!WS "2"!]/* [!"as:name(.)"!] */
          [!VAR "Operator" = "''"!][!//
          [!CALL "BUILD_DESCRIPTION", "Array" = "$OBDConfigStr"!][!//
[!/* If output was generated, stop searching for matching EventDTCClassname for the current DTCClassname since
   * only one event is mapped to an UDS-DTC (the Master Configuration Event in case of event combination) */!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
};
#define DEM_STOP_SEC_[!"$ObdConfigDataSection"!]_[!"$ObdTypeWidth"!]
#include <Dem_MemMap.h>
[!ENDIF!][!// "DemGeneral/DemEventCombinationSupport = 'DEM_EVCOMB_DISABLED'"
[!ENDIF!][!//
[!//
[!IF "($OBDSupport = 'true') and ($CalibrationWithoutEvCombSupport = 'false')"!]
#define DEM_START_SEC_[!"$ObdDTCDataSection"!]_8
#include <Dem_MemMap.h>

[!INDENT "0"!]
  [!VAR "BitIndex" = "1"!][!//
  [!VAR "ByteVal" = "0"!][!//
    /** \brief Calibratable bit-field array that holds minimum ratio event status
    [!WS!]**        (enabled/disabled) of all events */
    /* !LINKSTO dsn.Dem.OBD.config.MinRatioEvent.0001,3 */
    /* Deviation MISRAC2012-2 */
    CONST(uint8, [!"$ObdDTCMemSection"!]) Dem_MinRatioEvent[DEM_MIN_RATIO_EVENT_ARRAY_SIZE] =
  {
    [!INDENT "2"!]
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
        [!IF "node:existsAndTrue(DemEventClass/DemMinRatioEvent)"!]
          [!VAR "ByteVal" = "bit:or($ByteVal, bit:shl(1 ,$BitIndex))"!]
        [!ENDIF!]
        [!VAR "BitIndex" = "$BitIndex + 1"!]
        [!IF "($BitIndex mod 8) = 0"!]
          [!"translate(num:inttohex($ByteVal, 2), 'abcdef', 'ABCDEF')"!]U,
          [!VAR "ByteVal" = "0"!]
          [!VAR "BitIndex" = "0"!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "($BitIndex mod 8) != 0"!]
        [!"translate(num:inttohex($ByteVal, 2), 'abcdef', 'ABCDEF')"!]U
      [!ENDIF!]
    [!ENDINDENT!]
  };
[!ENDINDENT!]

#define DEM_STOP_SEC_[!"$ObdDTCDataSection"!]_8
#include <Dem_MemMap.h>
[!ENDIF!][!//
[!//
[!IF "$CalibrationSupport = 'true'"!][!//
    [!CALL "CREATE_READINESSGROUPS_EVENT_LIST"!][!//
    [!CALL "CREATE_READINESSGROUPS_CONFIG_LIST"!][!//
    [!CALL "GET_NUMBER_RG_EVENTS"!][!//
    [!IF "$EventIdSlots > 0"!][!//

[!/* Readiness group offset is added to ReadinessGroupsConfigList */!][!//
      [!VAR "ListWithOffset" = "''"!][!//
      [!VAR "ReadinessGroupsConfigWithOffsetList" = "''"!][!//
      [!VAR "Offset" = "num:i(0)"!][!//
      [!LOOP "text:split($ReadinessGroupsConfigList, '#')"!][!//
        [!VAR "RG" = "text:split(., ":")[position() = '2']"!][!//
        [!VAR "MaxNumEventsInRG" = "text:split(., ':')[position() = 3]"!][!//
        [!VAR "Offset" = "$Offset + $MaxNumEventsInRG"!][!//
        [!VAR "ListWithOffset" = "concat(., ':', num:i($Offset), '#')"!][!//
        [!VAR "ReadinessGroupsConfigWithOffsetList" = "concat($ReadinessGroupsConfigWithOffsetList, $ListWithOffset)"!][!//
      [!ENDLOOP!][!//

#define DEM_START_SEC_CALIB_16
#include <Dem_MemMap.h>

      [!INDENT "0"!]
      /* Deviation MISRAC2012-2 */
      CONST(Dem_EventIdType, DEM_CONST_CALIBRATION)
        [!WS "2"!]Dem_OBDReadinessGroup[DEM_RGP_MAX_NUM_READINESS_EVENTS] =
      {
        [!LOOP "text:split($ReadinessGroupsConfigList,'#')"!][!//
          [!VAR "RGID" = "text:split(.,":")[position() = '1']"!][!//
          [!VAR "RG" = "text:split(.,":")[position() = '2']"!][!//
          [!VAR "MaxNumEventsInRG" = "text:split(.,":")[position() = '3']"!][!//
          [!IF "($MaxNumEventsInRG != '0')"!][!//
            [!WS "2"!]/* [!"concat('DEM_OBD_RDY_',$RG, ' (', $RGID, ')')"!] */
            [!FOR "NumEventsInRG" = "'1'" TO "$MaxNumEventsInRG"!][!//
              [!VAR "EventRGID" = "substring-before($ReadinessGroupsEventList,':')"!][!//
              [!IF "($RGID = $EventRGID)"!][!//
                [!VAR "ReadinessGroupsEventList" = "substring-after($ReadinessGroupsEventList,':')"!][!//
                [!VAR "Event" = "concat('DemConf_DemEventParameter_',substring-before($ReadinessGroupsEventList,'#'))"!][!//
                [!VAR "ReadinessGroupsEventList" = "substring-after($ReadinessGroupsEventList,'#')"!][!//
                [!WS "2"!][!"$Event"!],
              [!ELSE!][!//
                [!WS "2"!] DEM_EVENT_ID_INVALID,
              [!ENDIF!][!//
            [!ENDFOR!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      };

#define DEM_STOP_SEC_CALIB_16
#include <Dem_MemMap.h>


#define DEM_START_SEC_CONST_16
#include <Dem_MemMap.h>
      CONST(uint16, DEM_CONST)
        Dem_OBDReadinessGroupOffset[DEM_RGP_MAX_NUM_READINESS_GROUPS] =
        {
          [!VAR "Offset" = "num:i(0)"!][!//
          [!LOOP "text:split($ReadinessInfoList, '#')"!][!//
            [!VAR "RG" = "text:split(., ':')[position() = 1]"!][!//
            [!VAR "RGID" = "substring-before(substring-after($ReadinessInfoList, concat($RG,':')), ':')"!][!//
            [!VAR "CalculatedOffset" = "0"!]
            [!LOOP "text:split($ReadinessGroupsConfigWithOffsetList, '#')"!][!//
              [!IF "contains(., $RGID)"!]
                [!VAR "CalculatedOffset" = "text:split(., ':')[position() = 4]"!][!//
                [!VAR "Offset" = "num:i($CalculatedOffset)"!][!//
                [!BREAK!]
              [!ENDIF!]
            [!ENDLOOP!]
            [!WS "2"!][!"$Offset"!], /* [!"$RG"!] */
          [!ENDLOOP!][!//
        };
      [!ENDINDENT!][!//

#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>

    [!ENDIF!][!// "$MaxRGEvt != 0"

[!ENDIF!][!// "$CalibrationSupport"
[!ENDIF!][!// "node:existsAndTrue(DemGeneral/DemOBDSupport)"

[!IF "node:existsAndTrue(DemGeneral/DemDevFreezeFrameSupport)"!]
#define DEM_START_SEC_CALIB_16
#include <Dem_MemMap.h>

/** \brief The array contains Development Freeze Frame classes
 *   for Freeze Frame A and Freeze Frame B and associated
 *   record number */
/* !LINKSTO dsn.Dem.DevFF.EventDescDevFF,1 */
/* Deviation MISRAC2012-2 */
CONST(Dem_EventDescDevFFType, DEM_CONST_CALIBRATION)
  Dem_EventDescDevFF[DEM_NUMBER_OF_EVENTS][DEM_NUM_OF_DEVFF_KIND] =
{
  { {0U, 0U}, {0U, 0U} },                             /* invalid event id entry */
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    [!WS "2"!]{ /* event: [!"as:name(.)"!] */
      [!WS "4"!]{ /* Freeze Frame A */
        [!IF "(node:exists(DemDevFreezeFrameAClassRef))"!]
          [!WS "6"!]DEM_FFCLS_IDX_[!"as:name(as:ref(./DemDevFreezeFrameAClassRef))"!],
        [!ELSE!][!//
          [!WS "6"!]DEM_FFCLS_NULL_IDX,
        [!ENDIF!]
        [!IF "(node:exists(DemDevFreezeFrameAClassRef)) or (node:exists(DemDevFreezeFrameARecNum))"!]
          [!WS "6"!][!"translate(num:inttohex(./DemDevFreezeFrameARecNum, 2), 'abcdef', 'ABCDEF')"!]U
        [!ELSE!][!//
          [!WS "6"!]0x00U
        [!ENDIF!]
      [!WS "4"!]},
      [!WS "4"!]{ /* Freeze Frame B */
        [!IF "(node:exists(DemDevFreezeFrameBClassRef))"!]
          [!WS "6"!]DEM_FFCLS_IDX_[!"as:name(as:ref(./DemDevFreezeFrameBClassRef))"!],
        [!ELSE!][!//
          [!WS "6"!]DEM_FFCLS_NULL_IDX,
        [!ENDIF!]
        [!IF "(node:exists(DemDevFreezeFrameBClassRef))"!]
          [!WS "6"!][!"translate(num:inttohex(./DemDevFreezeFrameBRecNum, 2), 'abcdef', 'ABCDEF')"!]U
        [!ELSE!][!//
          [!WS "6"!]0x00U
        [!ENDIF!]
      [!WS "4"!]}
    [!WS "2"!]},
  [!ENDLOOP!]
};
#define DEM_STOP_SEC_CALIB_16
#include <Dem_MemMap.h>
[!ENDIF!]

[!IF "$MARSupport = 'true'"!][!//
/*------------------[MAR events configuration]------------------------------*/
  [!CALL "CREATE_MAR_EVENTS_LIST"!][!//

#define DEM_START_SEC_CONST_16
#include <Dem_MemMap.h>

CONST(Dem_EventIdType, DEM_CONST) Dem_MAREvents[DEM_NUM_MAR_EVENTS] =
{
  [!INDENT "2"!]
    [!LOOP "text:split($MARNonCmbEventList, '#')"!][!//
      [!VAR "EventId" = "text:split(., ':')[position() = 1]"!][!//
      [!VAR "EventName" = "text:split(., ':')[position() = 2]"!][!//
      [!"num:i($EventId)"!]U, /* [!"$EventName"!] */
    [!ENDLOOP!][!//
    [!IF "$MARCmbEventsNum > 0"!][!//
      [!LOOP "text:split($MARCmbEventList, '#')"!][!//
        [!VAR "DTCClassName" = "text:split(., '&')[position() = 1]"!][!//
        [!VAR "CmbEventsList" = "text:split(., '&')[position() = 3]"!][!//
        /* combined events with DTCClass [!"$DTCClassName"!] */
        [!LOOP "text:split($CmbEventsList, '?')"!][!//
          [!VAR "EventId" = "text:split(., ':')[position() = 1]"!][!//
          [!VAR "EventName" = "text:split(., ':')[position() = 2]"!][!//
          [!"num:i($EventId)"!]U, /* [!"$EventName"!] */
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ENDINDENT!]
};

[!IF "$MARCmbEventsNum > 0"!][!//
[!IF "$MAREventsNum <= 255"!][!//
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!][!//

CONST(Dem_MAREventIndexType, DEM_CONST)
  Dem_MAREventCombinationIdx[DEM_NUM_MAR_CMB_DTCS + 1U] =
{
  [!INDENT "2"!]
    [!VAR "StartIndexForCmb" = "$MARNonCmbEventsNum"!][!//
    [!LOOP "text:split($MARCmbEventList, '#')"!][!//
      [!VAR "DTCClassName" = "text:split(., '&')[position() = 1]"!][!//
      [!"num:i($StartIndexForCmb)"!]U, /* start index for MAR combination [!"$DTCClassName"!] */
      [!VAR "NumEventsInCmb" = "text:split(., '&')[position() = 2]"!][!//
      [!VAR "StartIndexForCmb" = "$StartIndexForCmb + $NumEventsInCmb"!][!//
    [!ENDLOOP!][!//
    [!"num:i($StartIndexForCmb)"!]U, /* dummy entry for internal processing */
  [!ENDINDENT!]
};
[!ENDIF!][!//

[!IF "($MAREventsNum > 255) or ($MARCmbEventsNum = 0)"!][!//
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>
[!ELSE!][!//
#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!]
[!ENDIF!][!//

[!IF "$NumberOfMILGroups > 0"!]
/*------------------[MIL groups configuration]------------------------------*/

#define DEM_START_SEC_CONST_16
#include <Dem_MemMap.h>

CONST(Dem_EventIdType, DEM_CONST) Dem_MILGroupEventId[DEM_MILGROUP_NUM_EVENTS] =
{
  [!INDENT "2"!]
    [!FOR "GroupIdx" = "0" TO "num:i($NumberOfMILGroups - 1)"!]
      /* MIL group [!"$GroupIdx"!] */
      [!LOOP "text:split($MILGroupEventList, '#')"!][!//
        [!IF "contains(., concat(':', num:i($GroupIdx)))"!][!//
          [!VAR "FoundEventId" = "text:split(., ':')[position() = 1]"!][!//
          [!"$FoundEventId"!]U,
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
  [!ENDINDENT!]
};

[!IF "$NumberOfEventsInMILGroups <= 255"!][!//
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!][!//

CONST(Dem_MILGroupEventIndexType, DEM_CONST) Dem_MILGroupStartIndex[DEM_MILGROUP_NUM_GROUP + 1U] =
{
  [!INDENT "2"!]
    [!VAR "StartIndexCounter" = "0"!][!//
    [!FOR "GroupIdx" = "0" TO "num:i($NumberOfMILGroups - 1)"!]
      [!"num:integer($StartIndexCounter)"!]U,
      [!LOOP "text:split($MILGroupEventList, '#')"!][!//
        [!IF "contains(., concat(':', num:i($GroupIdx)))"!][!//
          [!VAR "StartIndexCounter" = "num:integer($StartIndexCounter + 1)"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!"$StartIndexCounter"!]U /* dummy value used for internal processing */
  [!ENDINDENT!]
};

[!IF "($NumberOfEventsInMILGroups > 255) and ($NumberOfMILGroups <= 255)"!][!//
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!][!//

CONST(Dem_MILGroupIndexType, DEM_CONST) Dem_MILGroupIndexPerEvent[DEM_NUMBER_OF_EVENTS] =
{
  [!WS "2"!]DEM_MILGROUP_GROUP_IDX_INVALID, /* corresponds to DEM_EVENT_ID_INVALID */
  [!LOOP "text:split($MILGroupEventList, '#')"!][!//
    [!IF "contains(., '-')"!][!//
      [!WS "2"!]DEM_MILGROUP_GROUP_IDX_INVALID,
    [!ELSE!]
      [!VAR "GroupIdx" = "text:split(., ':')[position() = 2]"!][!//
      [!WS "2"!][!"$GroupIdx"!]U,
    [!ENDIF!][!//
  [!ENDLOOP!][!//
};

[!IF "$NumberOfMILGroups > 255"!][!//
#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>
[!ELSE!][!//
#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
[!ENDIF!]
[!ENDIF!]

/*------------------[Enable conditions configuration]-----------------------*/

[!INDENT "0"!]
  #define DEM_START_SEC_VAR_INIT_8
  #include <Dem_MemMap.h>

  [!IF "node:exists(DemGeneral/DemEnableCondition/eb-list::*)"!]
    /** \brief Enable condition status */
    VAR(boolean, DEM_VAR) Dem_EnCondStatus[DEM_NUM_ENABLECONDITIONS] =
    {
      [!VAR "MaxEnableConditionId" = "count(DemGeneral/DemEnableCondition/eb-list::*) - 1"!]
      [!FOR "EnableConditionId" = "0" TO "$MaxEnableConditionId"!]
        [!SELECT "DemGeneral/DemEnableCondition/eb-list::*[number(DemEnableConditionId) = $EnableConditionId]"!]
          [!IF "node:existsAndTrue(DemEnableConditionStatus)"!]
            [!WS "2"!]TRUE,  [!//
          [!ELSE!]
            [!WS "2"!]FALSE, [!//
          [!ENDIF!]
          /* condition name: [!"as:name(.)"!] */
        [!ENDSELECT!]
      [!ENDFOR!]
    };
  [!ENDIF!]

  [!IF "node:exists(DemGeneral/DemEnableConditionGroup/eb-list::*)"!]
    /** \brief Enable condition group status counter array,
    [!WS!]**   holds the status counters per enable condition group, that counts how
    [!WS!]**   many enable conditions, that are linked to the dedicated condition
    [!WS!]**   group are enabled/disabled. (max. 256 conditions per group) */
    VAR(Dem_EnCondGrpStatusCounterType, DEM_VAR)
      [!WS "2"!]Dem_EnCondGrpStatusCounter[DEM_NUM_ENCONDGROUPS + 1U] =
    {
      [!INDENT "2"!]
        [!VAR "GrpCntInitVal" = "0"!]
        [!LOOP "DemGeneral/DemEnableConditionGroup/eb-list::*"!]
          [!LOOP "DemEnableConditionRef/eb-list::*"!]
            [!/* calculate initial counter value according initial EnCond. status */!][!//
            [!IF "node:existsAndFalse(as:ref(.)/DemEnableConditionStatus)"!]
              [!VAR "GrpCntInitVal" = "$GrpCntInitVal + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!"num:i($GrpCntInitVal)"!]U, /* group counter: [!"as:name(.)"!] */
          [!VAR "GrpCntInitVal" = "0"!]
        [!ENDLOOP!]
        0U  /* Dummy entry for internal processing */
      [!ENDINDENT!]
    };
  [!ENDIF!]
  #define DEM_STOP_SEC_VAR_INIT_8
  #include <Dem_MemMap.h>

  [!IF "node:exists(DemGeneral/DemEnableConditionGroup/eb-list::*)"!]
    #define DEM_START_SEC_CONST_16
    #include <Dem_MemMap.h>

    /** \brief Enable condition link array,
    [!WS!]** holds the start indexes of Dem_EnCondGrpLink[] */
    CONST(Dem_EnCondLnkType, DEM_CONST) Dem_EnCondToEvIdLink[DEM_NUM_ENABLECONDITIONS + 1U] =
    {
      [!INDENT "2"!]
        [!VAR "EnCondCnt" = "0"!]
        [!/* number of condition groups, referencing enable conditions */!][!//
        [!VAR "NrOfGrpRefEnCond" = "0"!]
        [!VAR "EnCondId" = "0"!]
        [!VAR "EnCondName" = "''"!]
        [!LOOP "util:distinct(node:order(DemGeneral/DemEnableCondition/eb-list::*, 'DemEnableConditionId'))"!]
          [!VAR "EnCondName" = "as:name(.)"!]
          [!VAR "EnCondId" = "num:i(DemEnableConditionId)"!]
          [!"num:i($NrOfGrpRefEnCond)"!]U, /* start index, [!"$EnCondName"!] */
          [!LOOP "../../DemEnableConditionGroup/eb-list::*/DemEnableConditionRef/eb-list::*"!]
            [!IF "number(as:ref(.)/DemEnableConditionId) = $EnCondId"!]
              [!/* incrementing nr of groups, that are referencing this condition */!][!//
              [!VAR "NrOfGrpRefEnCond" = "$NrOfGrpRefEnCond + 1"!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
        [!"num:i($NrOfGrpRefEnCond)"!]U, /* dummy entry, for internal processing */
      [!ENDINDENT!]
    };

    #define DEM_STOP_SEC_CONST_16
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_8
    #include <Dem_MemMap.h>

    /** \brief Enable condition group status counter link array,
    [!WS!]** holds the indexes of Dem_EnCondGrpStatusCounter[]. One enable condition
    [!WS!]** can refer to several condition group status counters. */
    CONST(Dem_EnCondGrpType, DEM_CONST)
      [!WS "2"!]Dem_EnCondGrpLink[DEM_NUM_ENCONDGRP_LINKS] =
    {
      [!INDENT "2"!]
        [!VAR "EnCondCnt" = "0"!]
        [!VAR "CurrentGrpIdx" = "0"!]
        [!VAR "EnCondName" = "''"!]
        [!VAR "EnCondId" = "0"!]
        [!VAR "EnCondGrpName" = "''"!]
        [!LOOP "util:distinct(node:order(DemGeneral/DemEnableCondition/eb-list::*,'DemEnableConditionId'))"!]
          [!VAR "EnCondName" = "as:name(.)"!]
          [!VAR "EnCondId" = "num:i(DemEnableConditionId)"!]
          [!LOOP "../../DemEnableConditionGroup/eb-list::*/DemEnableConditionRef/eb-list::*"!]
            [!IF "number(as:ref(.)/DemEnableConditionId) = $EnCondId"!]
              [!/* incrementing nr of groups, that are referencing this condition */!][!//
              [!VAR "CurrentGrpIdx" = "node:pos(../../.)"!]
              [!VAR "EnCondGrpName" = "as:name(../../.)"!]
              [!"num:i($CurrentGrpIdx)"!]U, /* group: [!"$EnCondGrpName"!], condition: [!"$EnCondName"!] */
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
      [!ENDINDENT!]
    };

    #define DEM_STOP_SEC_CONST_8
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[Multi event triggering configuration]------------------*/

[!INDENT "0"!]
  [!IF "$NumMultiEventTriggering > 0"!]
    #define DEM_START_SEC_CONST_16
    #include <Dem_MemMap.h>

    /** \brief Multi event triggering classes array,
    [!WS!]**   holds data per each multi event triggering class configuration. */
    CONST(Dem_MultiEventTriggeringType, DEM_CONST)
      [!WS "2"!]Dem_MultiEventTriggeringClasses[DEM_MULTI_EVENT_TRIGGERING_CLASS_COUNT] =
    {
      [!LOOP "text:split($MultiEventTriggeringClassList, '#')"!][!//
      [!WS "2"!]{
        [!INDENT "4"!]
          [!VAR "SlaveStartIdx" = "text:split(.)[position() = 1]"!]
          [!VAR "SlaveNextIdx" = "text:split(.)[position() = 2]"!]
          [!VAR "Behavior" = "text:split(.)[position() = 3]"!]
          [!"$SlaveStartIdx"!]U,
          [!"$SlaveNextIdx"!]U,
          [!"$Behavior"!]
        [!ENDINDENT!]
      [!WS "2"!]},
      [!ENDLOOP!][!//
    };

    /** \brief Slave event configurations array,
    [!WS!]**   holds EventId of slave events referenced in
    [!WS!]**   multi event triggering classes */
    CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_MultiEventTriggeringSlaveEventId[DEM_MULTI_EVENT_TRIGGERING_SLAVE_COUNT] =
    {
    [!LOOP "text:split($MultiEventTriggeringSlaveGroupList, '#')"!][!//
      [!INDENT "2"!]
        [!VAR "SlaveEventIds" = "text:split(., ';')[position() = 2]"!]
        [!LOOP "text:split($SlaveEventIds)"!]
          [!"."!]U,
        [!ENDLOOP!]
      [!ENDINDENT!]
    [!ENDLOOP!][!//
    };

    /** \brief Master events configurations array,
    [!WS!]**   holds sorted EventId of master events referenced in
    [!WS!]**   multi event triggering configurations */
    CONST(Dem_EventIdType, DEM_CONST)
      [!WS "2"!]Dem_MultiEventTriggeringMasterEventId[DEM_MULTI_EVENT_TRIGGERING_COUNT] =
    {
      [!LOOP "text:split($MultiEventTriggeringClassIndexList, '#')"!][!//
        [!INDENT "2"!]
          [!"text:split(.,':')[position() = 1]"!]U,
        [!ENDINDENT!]
      [!ENDLOOP!][!//
    };

    #define DEM_STOP_SEC_CONST_16
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[Warning indicators configuration]----------------------*/

[!INDENT "0"!]
  [!IF "$CalibrationSupport = 'true'"!]
    [!CALL "CALC_INDICATOR_CLASSES"!]
    [!CALL "GET_NUMBER_OF_INDICATOR_CLASSES"!]
    [!IF "$NumberOfIndicatorClasses != 0"!]
      /* Indicator class index:
        [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
          [!CALL "GET_INDICATOR_CLASS_INDEX", "EVENT_ID" = "DemEventId"!]
          [!WS "1"!]* [!"as:name(.)"!]: [!"$IndicatorClassIndex"!]
        [!ENDLOOP!]
       [!WS "1"!]*/
      #if (DEM_NUM_INDICATOR_LINKS > 0U)
      #define DEM_START_SEC_CALIB_8
      #include <Dem_MemMap.h>

      /* Deviation MISRAC2012-2 */
      CONST(Dem_IndicatorClassType, DEM_CONST_CALIBRATION) Dem_IndicatorClasses[DEM_NUM_INDICATOR_LINKS] =
      {
        [!VAR "ClassIndex" = "0"!]
        [!LOOP "text:split($IndicatorClassList, '#')"!]
          [!WS "2"!]/* Class [!"num:i($ClassIndex)"!] */
          [!VAR "ClassIndex" = "$ClassIndex + 1"!]
          [!LOOP "text:split(., '+')"!]
            [!VAR "IndicatorId" = "text:split(., ' ')[position() = 1]"!]
            [!VAR "IndicatorBehaviour" = "text:split(., ' ')[position() = 2]"!]
            [!VAR "FailureThreshold" = "text:split(., ' ')[position() = 3]"!]
            [!VAR "HealingThreshold" = "text:split(., ' ')[position() = 4]"!]
            [!VAR "IsIndFailureCycleSrcEvent" = "text:split(., ' ')[position() = 5]"!]
            [!IF "$CommonOperationCycleEnabled = 'false'"!]
              [!VAR "FailureCycle" = "text:split(., ' ')[position() = 6]"!]
              [!VAR "HealingCycle" = "text:split(., ' ')[position() = 7]"!]
            [!ENDIF!]
            [!WS "2"!]{
              [!INDENT "4"!]
                TRUE, /* Enabled */
                DemConf_DemIndicator_[!"$IndicatorId"!], /* Indicator Id */
                [!"$IndicatorBehaviour"!],
                [!"$HealingThreshold"!]U, /* Indicator Healing Cycle Counter Threshold */
                [!"$FailureThreshold"!]U, /* Indicator Failure Cycle Counter Threshold */
                [!IF "$CommonOperationCycleEnabled = 'false'"!]
                  [!"$HealingCycle"!], /* Indicator Healing Cycle */
                  [!"$FailureCycle"!], /* Indicator Failure Cycle */
                [!ENDIF!]
                /* Flag indicates, whether DemIndicatorFailureCycleSource == DEM_FAILURE_CYCLE_EVENT */
                [!"$IsIndFailureCycleSrcEvent"!],
              [!ENDINDENT!]
            [!WS "2"!]},
          [!ENDLOOP!]
        [!ENDLOOP!]

        [!FOR "IndicatorClass" = "$NumberOfIndicatorClasses" TO "DemGeneral/DemMaxNumberIndicatorClasses - 1"!]
          [!WS "2"!]{
            [!INDENT "4"!]
              FALSE, /* Enabled */
              DemConf_DemIndicator_[!"as:name(as:modconf('Dem')[1]/DemGeneral/DemIndicator/eb-list::*[1])"!], /* Indicator id */
              DEM_INDICATOR_CONTINUOUS,
              0U, /* Indicator Healing Cycle Counter Threshold */
              0U, /* Indicator Failure Cycle Counter Threshold */
              [!IF "$CommonOperationCycleEnabled = 'false'"!]
                [!"$HealingCycle"!], /* Indicator Healing Cycle */
                [!"$FailureCycle"!], /* Indicator Failure Cycle */
              [!ENDIF!]
              /* Flag indicates, whether DemIndicatorFailureCycleSource == DEM_FAILURE_CYCLE_EVENT */
              TRUE,
            [!ENDINDENT!]
          [!WS "2"!]},
        [!ENDFOR!]
      };
      #define DEM_STOP_SEC_CALIB_8
      #include <Dem_MemMap.h>
      #endif

      [!IF "(count(DemGeneral/DemMaxNumberIndicatorClasses) + 1) > 0"!]
      #define DEM_START_SEC_CONST_UNSPECIFIED
      #include <Dem_MemMap.h>
      CONST(Dem_IndicatorIdxType, DEM_CONST) Dem_IndicatorGroups[DEM_NUM_INDICATOR_GROUPS] =
      {
        [!WS "2"!]0U,
        [!VAR "IndicatorClassIndex" = "0"!]
        [!LOOP "text:split($IndicatorClassList, '#')"!]
          [!VAR "IndicatorClassIndex" = "$IndicatorClassIndex + count(text:split(., '+'))"!]
          [!WS "2"!][!"num:i($IndicatorClassIndex)"!]U,
        [!ENDLOOP!]
        /* !LINKSTO VCC_DEM_006_Req115v1,1 */
        [!FOR "IndicatorClass" = "$ClassIndex" TO "DemGeneral/DemMaxNumberIndicatorClasses - 1"!]
          [!VAR "IndicatorClassIndex" = "$IndicatorClassIndex + 1"!]
          [!WS "2"!][!"num:i($IndicatorClassIndex)"!]U,
        [!ENDFOR!]
      };
      #define DEM_STOP_SEC_CONST_UNSPECIFIED
      #include <Dem_MemMap.h>

      [!IF "($CalibrationWithoutEvCombSupport = 'false')"!]
      #define DEM_START_SEC_CALIB_UNSPECIFIED
      #include <Dem_MemMap.h>
      /* Deviation MISRAC2012-2 */
      CONST(Dem_IndicatorGrpIdxType, DEM_CONST_CALIBRATION)
        Dem_EventIndicatorClassIdx[DEM_NUMBER_OF_EVENTS] =
      {
        [!WS "2"!]DEM_INDICATOR_UNUSED, /* invalid event id entry */
        [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
          [!CALL "GET_INDICATOR_CLASS_INDEX", "EVENT_ID" = "DemEventId"!]
          [!IF "$IndicatorClassIndex = '-'"!]
            [!WS "2"!]DEM_INDICATOR_UNUSED, /* [!"as:name(.)"!] */
          [!ELSE!]
            [!WS "2"!][!"$IndicatorClassIndex"!]U, /* [!"as:name(.)"!] */
          [!ENDIF!]
        [!ENDLOOP!]
      };
      #define DEM_STOP_SEC_CALIB_UNSPECIFIED
      #include <Dem_MemMap.h>
      [!ENDIF!]
      [!ENDIF!]

    [!ENDIF!]
  [!ELSE!][!//
    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    [!IF "$NumIndicator > 0"!]
      /** \brief Warning indicator configuration description table */
      CONST(Dem_IndicatorDescType, DEM_CONST)
        [!WS "2"!]Dem_IndicatorDesc[DEM_NUMBER_OF_INDICATORS] =
      {
        [!VAR "IndicatorLnkIdx" = "0"!]
        [!VAR "MaxIndicatorId" = "$NumIndicator - 1"!]
        [!CALL "GET_OBDONUDS_MIL_ID"!][!//
        [!FOR "IndicatorId" = "0" TO "$MaxIndicatorId"!]
          [!VAR "MILSlaveEventsNum" = "0"!][!//
          [!IF "($OBDonUDSMILId = $IndicatorId)"!]
            [!/* count the number of slave events for which the MIL is configured only for the master, but generated for all events in combination */!][!//
            [!CALL "GET_NUMBER_OF_MIL_SLAVE_EVENTS"!][!//
          [!ENDIF!][!//
          [!VAR "IndicatorLnkNum" = "$MILSlaveEventsNum + count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemIndicatorAttribute/eb-list::*[number(as:ref(DemIndicatorRef)/DemIndicatorID) = $IndicatorId])"!]
          [!INDENT "2"!]
            { /* warning indicator: [!"node:name(DemGeneral/DemIndicator/eb-list::*[number(DemIndicatorID) = $IndicatorId])"!] (= ID [!"num:i($IndicatorId)"!]) */
              [!WS "2"!]/* number: */ [!"num:i($IndicatorLnkNum)"!]U, /* index: */ [!"num:i($IndicatorLnkIdx)"!]U
            }[!//
            ,
          [!ENDINDENT!]
          [!VAR "IndicatorLnkIdx" = "$IndicatorLnkIdx + $IndicatorLnkNum"!]
        [!ENDFOR!]
      };
    [!ENDIF!]

    [!/* Generate healing and failure lists containing all unique combinations of cycles and thresholds */!][!//
    [!IF "$NumIndicator > 0"!]
      [!VAR "HealList" = "'#'"!][!/* List of all unique healing cycle and threshold pairs */!][!//
      [!VAR "FailList" = "'#'"!][!/* List of all unique failure cycle and threshold pairs */!][!//
      [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*"!]
        [!LOOP "./DemEventClass/DemIndicatorAttribute/eb-list::*"!]
          [!IF "$CommonOperationCycleEnabled = 'false'"!]
            [!VAR "HealingCycle" = "as:name(as:ref(./DemIndicatorHealingCycleRef))"!]
          [!ELSE!]
            [!VAR "HealingCycle" = "as:name(as:ref(../../DemOperationCycleRef))"!]
          [!ENDIF!]
          [!IF "not(contains($HealList, concat('#', $HealingCycle,'*',node:value(./DemIndicatorHealingCycleCounterThreshold), '#')))"!]
            [!VAR "HealList" = "concat($HealList, $HealingCycle,'*',node:value(./DemIndicatorHealingCycleCounterThreshold), '#')"!]
          [!ENDIF!]
          [!IF "./DemIndicatorFailureCycleSource = 'DEM_FAILURE_CYCLE_INDICATOR'"!]
            [!IF "$CommonOperationCycleEnabled = 'false'"!]
              [!VAR "FailCycle" = "as:name(as:ref(./DemIndicatorFailureCycleRef))"!]
            [!ENDIF!]
            [!VAR "FailThrsld" = "node:value(./DemIndicatorFailureCycleCounterThreshold)"!]
          [!ELSE!]
            [!IF "$CommonOperationCycleEnabled = 'false'"!]
              [!/* check if event is combined */!][!//
              [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
                [!VAR "FailCycle" = "as:name(as:ref(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleRef))"!][!//
              [!ELSE!][!//
                [!VAR "FailCycle" = "as:name(as:ref(../../DemEventFailureCycleRef))"!]
              [!ENDIF!][!//
            [!ENDIF!]
            [!/* check if event is combined */!][!//
            [!IF "node:exists(../../../DemEvtCmbCommonParamMaster)"!][!//
              [!VAR "FailThrsld" = "node:value(../../../../eb-list::*[(DemDTCClassRef=node:current()/../../../DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemEventFailureCycleCounterThreshold)"!][!//
            [!ELSE!][!//
              [!VAR "FailThrsld" = "node:value(../../DemEventFailureCycleCounterThreshold)"!]
            [!ENDIF!][!//
          [!ENDIF!]
          [!IF "$CommonOperationCycleEnabled = 'true'"!]
            [!VAR "FailCycle" = "as:name(as:ref(../../DemOperationCycleRef))"!]
          [!ENDIF!]
          [!IF "not(contains($FailList, concat('#', $FailCycle,'*', $FailThrsld, '#')))"!]
            [!VAR "FailList" = "concat($FailList, $FailCycle,'*',$FailThrsld, '#')"!]
          [!ENDIF!]
        [!ENDLOOP!]
      [!ENDLOOP!]
    [!ENDIF!]

    [!IF "$NumIndicator > 0"!]
      #if (DEM_NUM_INDICATOR_LINKS != 0)
      /** \brief Warning indicator-link configuration link table */
      CONST(Dem_IndicatorLinkType, DEM_CONST)
        [!WS "2"!]Dem_IndicatorLink[DEM_NUM_INDICATOR_LINKS] =
      {
        [!INDENT "2"!]
        [!CALL "GET_OBDONUDS_MIL_ID"!][!//
          [!VAR "MaxIndicatorId" = "$NumIndicator - 1"!]
          [!FOR "IndicatorId" = "0" TO "$MaxIndicatorId"!]
            [!IF "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemIndicatorAttribute/eb-list::*[number(as:ref(DemIndicatorRef)/DemIndicatorID) = $IndicatorId]) = 0"!]
              [!WS "2"!]/* no links */
            [!ENDIF!]
            [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
              [!VAR "EventName" = "node:name(.)"!][!//
              [!IF "($OBDonUDSMILId = $IndicatorId) and node:existsAndFalse(DemEvtCmbCommonParamMaster)"!][!//
                [!/* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.CommonMILConfiguration,1 */!][!//
                [!/* If OBDonUDS combination is enabled and the current event is a slave event, then the MIL of the master event is processed (if exists) */!][!//
                [!LOOP "(../eb-list::*[(DemDTCClassRef = node:current()/DemDTCClassRef) and (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemEventClass/DemIndicatorAttribute/eb-list::*[number(as:ref(./DemIndicatorRef)/DemIndicatorID) = $IndicatorId])"!]
                  {
                    [!CALL "CREATE_INDICATOR_LINK"!][!//
                  }[!//
                ,
                [!ENDLOOP!]
              [!ELSE!]
                [!LOOP "./DemEventClass/DemIndicatorAttribute/eb-list::*[number(as:ref(./DemIndicatorRef)/DemIndicatorID) = $IndicatorId]"!]
                  {
                    [!CALL "CREATE_INDICATOR_LINK"!][!//
                  }[!//
                ,
                [!ENDLOOP!]
              [!ENDIF!]
            [!ENDLOOP!]
          [!ENDFOR!]
        [!ENDINDENT!]
      };
      #endif
    [!ENDIF!]

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    #define DEM_START_SEC_CONST_8
    #include <Dem_MemMap.h>

    [!IF "$NumIndicator > 0"!]
      #if (DEM_NUM_HEALINGCYC_COUNTER_INFO_ELEMENTS != 0U)
      /** \brief Warning indicator configuration healing cycle-counter information table */
      CONST(Dem_CounterInfoType, DEM_CONST)
        [!WS "2"!]Dem_HealingCycleCounterInfo[DEM_NUM_HEALINGCYC_COUNTER_INFO_ELEMENTS] =
      {
        [!/* list of all unique healing cycle and threshold pair */!][!//
        [!LOOP "text:split($HealList, '#')"!]
          [!VAR "HealingCycle" = "text:split(., '*')[position()=1]"!]
          [!VAR "HealingThreshold" = "text:split(., '*')[position()=2]"!]
          [!INDENT "2"!]
          {
            [!WS "2"!][!"$HealingCycle"!],
            [!WS "2"!][!"$HealingThreshold"!]U /* Healing threshold */
          },
          [!ENDINDENT!]
        [!ENDLOOP!]
      };
      #endif
    [!ENDIF!]

    [!IF "$NumIndicator > 0"!]
      #if (DEM_NUM_FAILURECYC_COUNTER_INFO_ELEMENTS != 0U)
      /** \brief Warning indicator configuration failure cycle-counter information table */
      CONST(Dem_CounterInfoType, DEM_CONST)
        [!WS "2"!]Dem_FailureCycleCounterInfo[DEM_NUM_FAILURECYC_COUNTER_INFO_ELEMENTS] =
      {
        [!/* list of all unique failure cycle and threshold pair */!][!//
        [!LOOP "text:split($FailList, '#')"!]
          [!VAR "FailCycle" = "text:split(., '*')[position()=1]"!]
          [!VAR "FailThreshold" = "text:split(., '*')[position()=2]"!]
          [!INDENT "2"!]
          {
            [!WS "2"!][!"$FailCycle"!],
            [!WS "2"!][!"$FailThreshold"!]U /* Failure threshold */
          },
          [!ENDINDENT!]
        [!ENDLOOP!]
      };
      #endif
    [!ENDIF!]

    #define DEM_STOP_SEC_CONST_8
    #include <Dem_MemMap.h>
  [!ENDIF!]

[!ENDINDENT!]

/*------------------[Debouncing configuration]------------------------------*/

[!INDENT "0"!]
  /** \brief Counter based debouncing configuration description table */
  [!IF "(node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceCounterBased'])) or (node:exists(DemGeneral/DemMaxNumberDebCounterClasses) and (DemGeneral/DemMaxNumberDebCounterClasses > 0))"!]
  #define DEM_START_SEC_CALIB_16
  #include <Dem_MemMap.h>

    [!VAR "UnconfirmedThresholdEnabled" = "'false'"!]
    [!IF "(DemGeneral/DemFreezeFrameCapture = 'DEM_TRIGGER_ON_FDC_THRESHOLD') or (DemGeneral/DemExtendedDataCapture = 'DEM_TRIGGER_ON_FDC_THRESHOLD')"!]
      [!VAR "UnconfirmedThresholdEnabled" = "'true'"!]
    [!ENDIF!]
    [!CALL "DEBOUNCE_COUNTER_CLASS_CALC"!]
    /* Deviation MISRAC2012-2 */
    CONST(Dem_DebounceCounterClassType, DEM_CONST_CALIBRATION)
      [!WS "2"!]Dem_DebounceCounterClass[DEM_NUM_DEBOUNCE_COUNTER_CLASSES] =
    {
      [!INDENT "2"!]
      [!VAR "DebounceClassIdx" = "0"!]
      [!LOOP "text:split($DebounceClasses, '#')"!]
        [!VAR "DebounceCounterDecrementStepSize" = "text:split(., ':')[position() = 1]"!]
        [!VAR "DebounceCounterIncrementStepSize" = "text:split(., ':')[position() = 2]"!]
        [!VAR "DebounceCounterPassedThreshold" = "text:split(., ':')[position() = 3]"!]
        [!VAR "DebounceCounterFailedThreshold" = "text:split(., ':')[position() = 4]"!]
        [!VAR "DebounceCounterUnconfirmedThreshold" = "text:split(., ':')[position() = 5]"!]
        [!VAR "DebounceCounterJumpDownValue" = "text:split(., ':')[position() = 6]"!]
        [!VAR "DebounceCounterJumpUpValue" = "text:split(., ':')[position() = 7]"!]
        [!VAR "DebounceCounterBehavior" = "text:split(., ':')[position() = 8]"!]
        [!VAR "DebounceCounterJumpDown" = "text:split(., ':')[position() = 9]"!]
        [!VAR "DebounceCounterJumpUp" = "text:split(., ':')[position() = 10]"!]
        [!VAR "DebounceCounterStorage" = "text:split(., ':')[position() = 11]"!]
        { /* [!"num:i($DebounceClassIdx)"!] */
          [!INDENT "4"!]
          [!"$DebounceCounterDecrementStepSize"!]U, /* DemDebounceCounterDecrementStepSize */
          [!"$DebounceCounterIncrementStepSize"!]U, /* DemDebounceCounterIncrementStepSize */
          [!"$DebounceCounterPassedThreshold"!], /* DemDebounceCounterPassedThreshold */
          [!"$DebounceCounterFailedThreshold"!], /* DemDebounceCounterFailedThreshold */
          [!IF "$UnconfirmedThresholdEnabled = 'true'"!]
            [!"$DebounceCounterUnconfirmedThreshold"!], /* DemDebounceCounterUnconfirmedThreshold */
          [!ENDIF!]
          [!"$DebounceCounterJumpDownValue"!], /* DemDebounceCounterJumpDownValue */
          [!"$DebounceCounterJumpUpValue"!], /* DemDebounceCounterJumpUpValue */
          [!IF "$DebounceCounterBehavior = 'DEM_DEBOUNCE_FREEZE'"!]
            DEM_DEBOUNCE_FREEZE, /* DemDebounceBehavior */
          [!ELSE!]
            DEM_DEBOUNCE_RESET, /* DemDebounceBehavior */
          [!ENDIF!]
          [!IF "$DebounceCounterJumpDown = 'true'"!]
            TRUE, /* DemDebounceCounterJumpDown */
          [!ELSE!]
            FALSE, /* DemDebounceCounterJumpDown */
          [!ENDIF!]
          [!IF "$DebounceCounterJumpUp = 'true'"!]
            TRUE, /* DemDebounceCounterJumpUp */
          [!ELSE!]
            FALSE, /* DemDebounceCounterJumpUp */
          [!ENDIF!]
          [!ENDINDENT!]
        },
        [!VAR "DebounceClassIdx" = "$DebounceClassIdx + 1"!]
      [!ENDLOOP!]
      [!VAR "DebounceCtr" = "num:integer(count(text:split($DebounceClasses, '#')))"!]
      [!IF "node:exists(DemGeneral/DemMaxNumberDebCounterClasses)"!]
        [!VAR "MaxNumberDebCounter" = "num:integer(DemGeneral/DemMaxNumberDebCounterClasses)"!]
        [!IF "$DebounceCtr < $MaxNumberDebCounter"!]
          /* Unused debounce classes */
          [!FOR "DebounceCtrIdx" = "$DebounceCtr" TO "$MaxNumberDebCounter - 1"!]
            {
              [!INDENT "4"!]
              1U, /* DemDebounceCounterDecrementStepSize */
              1U, /* DemDebounceCounterIncrementStepSize */
              -128, /* DemDebounceCounterPassedThreshold */
              127, /* DemDebounceCounterFailedThreshold */
              [!IF "$UnconfirmedThresholdEnabled = 'true'"!]
                127, /* DemDebounceCounterUnconfirmedThreshold */
              [!ENDIF!]
              0, /* DemDebounceCounterJumpDownValue */
              0, /* DemDebounceCounterJumpUpValue */
              DEM_DEBOUNCE_FREEZE, /* DemDebounceBehavior */
              FALSE, /* DemDebounceCounterJumpDown */
              FALSE, /* DemDebounceCounterJumpUp */
              [!ENDINDENT!]
            },
          [!ENDFOR!]
        [!ENDIF!]
      [!ENDIF!]
      [!ENDINDENT!]
    };

      /** \brief Counter based debouncing class index table */
      /* Deviation MISRAC2012-2 */
      CONST(Dem_DebounceCounterClassIdxType, DEM_CONST_CALIBRATION)
        [!WS "2"!]Dem_DebounceCounterClassIdx[DEM_NUM_DEBOUNCE_COUNTER] =
      {
        [!CALL "DEBOUNCE_COUNTER_CLASS_CALC"!]
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceCounterBased'], 'DemEventId'))"!]
        [!VAR "DebounceStorage" = "node:value(./DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceCounterStorage)"!]
          [!CALL "DEBOUNCE_COUNTER_GET_CLASS_INDEX", "EventId" = "DemEventId"!]
          [!IF "$DebounceStorage = 'true'"!]
            [!IF "num:integer($DebounceCounterClassIndex) != 0"!]
              [!WS "2"!][!"$DebounceCounterClassIndex"!] | DEM_DEBOUNCE_COUNTER_NVSTORAGE_MASK, /* [!"DemEventId"!] */
            [!ELSE!][!//
              [!WS "2"!]DEM_DEBOUNCE_COUNTER_NVSTORAGE_MASK, /* [!"DemEventId"!] */
            [!ENDIF!]
          [!ELSE!][!//
            [!WS "2"!][!"$DebounceCounterClassIndex"!], /* [!"DemEventId"!] */
          [!ENDIF!]
        [!ENDLOOP!]
      };

  #define DEM_STOP_SEC_CALIB_16
  #include <Dem_MemMap.h>
  [!ELSE!]
    /* none */
  [!ENDIF!]

  /** \brief Time based debouncing configuration description table */
   /* !LINKSTO Dem.Calibration.DemTimeBasedDebounceClassConcept,1 */
  [!IF "(count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase']) > 0) or (node:exists(DemGeneral/DemMaxNumberDebTimeClasses) and (DemGeneral/DemMaxNumberDebTimeClasses > 0))"!][!//
  #define DEM_START_SEC_CALIB_32
  #include <Dem_MemMap.h>

    /* Deviation MISRAC2012-2 */
    CONST(Dem_DebounceTimeClassType, DEM_CONST_CALIBRATION)
      [!WS "2"!]Dem_DebounceTimeClass[DEM_NUM_DEBOUNCE_TIME_CLASSES] =
    {
      [!CALL "DEBOUNCE_TIME_CLASS_CALC"!][!//
      [!INDENT "2"!]
      [!VAR "TimeDebounceClassIdx" = "0"!]
      [!LOOP "text:split($TimeDebounceClasses, '#')"!]
      [!VAR "DemDebounceTimeFailedThreshold" = "text:split(., ':')[position() = 1]"!]
      [!VAR "DemDebounceTimePassedThreshold" = "text:split(., ':')[position() = 2]"!]
      [!VAR "DebounceTimeBehavior" = "text:split(., ':')[position() = 3]"!]
      { /* [!"num:i($TimeDebounceClassIdx)"!] */
      [!/* TimeFailedThreshold and TimePassedThreshold are stored in main
              * function "ticks", not in ms! */!][!//
        [!INDENT "4"!]
        [!"num:i(ceiling(($DemDebounceTimeFailedThreshold * 1000) div ($DemTaskTime* 1000)))"!]U, /* DemDebounceTimeFailedThreshold */
        [!"num:i(ceiling(($DemDebounceTimePassedThreshold * 1000) div ($DemTaskTime * 1000)))"!]U, /* DemDebounceTimePassedThreshold */
        [!IF "$DebounceTimeBehavior = 'DEM_DEBOUNCE_FREEZE'"!]
          DEM_DEBOUNCE_FREEZE, /* DemDebounceBehavior */
        [!ELSEIF "$DebounceTimeBehavior = 'DEM_DEBOUNCE_RESET'"!]
          DEM_DEBOUNCE_RESET, /* DemDebounceBehavior */
        [!ELSE!][!//
          DEM_DEBOUNCE_CONTINUE, /* DemDebounceBehavior */
        [!ENDIF!]
        [!ENDINDENT!]
      },
        [!VAR "TimeDebounceClassIdx" = "$TimeDebounceClassIdx + 1"!]
      [!ENDLOOP!]
      [!VAR "TimeDebounceCtr" = "num:integer(count(text:split($TimeDebounceClasses, '#')))"!]
      [!IF "node:exists(DemGeneral/DemMaxNumberDebTimeClasses)"!]
        [!VAR "MaxNumberTimeDebCounter" = "num:integer(DemGeneral/DemMaxNumberDebTimeClasses)"!]
        [!IF "$TimeDebounceCtr < $MaxNumberTimeDebCounter"!]
          /* Unused debounce classes */
          [!FOR "DebounceTimeIdx" = "$TimeDebounceCtr" TO "$MaxNumberTimeDebCounter - 1"!]
            {
               [!INDENT "4"!]
                /* [!"num:i($DebounceTimeIdx)"!] */
               1U, /* DemDebounceTimeFailedThreshold */
               1U, /* DemDebounceTimePassedThreshold */
               DEM_DEBOUNCE_CONTINUE, /* DemDebounceBehavior */
               [!ENDINDENT!]
             },
          [!ENDFOR!]
        [!ENDIF!]
      [!ENDIF!]
      [!ENDINDENT!]
       };

  #define DEM_STOP_SEC_CALIB_32
  #include <Dem_MemMap.h>

  #define DEM_START_SEC_CALIB_16
  #include <Dem_MemMap.h>

      /** \brief Time based debouncing class index table */
      /* Deviation MISRAC2012-2 */
      CONST(Dem_DebounceTimeClassIdxType, DEM_CONST_CALIBRATION)
        [!WS "2"!]Dem_DebounceTimeClassIdx[DEM_NUM_DEBOUNCE_TIME] =
      {
        [!CALL "DEBOUNCE_TIME_CLASS_CALC"!][!//
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'], 'DemEventId'))"!][!//
        [!CALL "DEBOUNCE_TIME_GET_CLASS_INDEX", "EventId" = "DemEventId"!][!//
          [!WS "2"!][!"$DebounceTimeClassIndex"!], /* EventName: [!"as:name(.)"!] */
        [!ENDLOOP!][!//
      };

  #define DEM_STOP_SEC_CALIB_16
  #include <Dem_MemMap.h>
  [!ELSE!]
    /* none */
  [!ENDIF!]

  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief Time based debouncing configuration description table */
  [!IF "node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'])"!]
    CONST(Dem_EventIdType, DEM_CONST)
      [!WS "2"!]Dem_DebounceTimeCfg[DEM_NUM_DEBOUNCE_TIME] =
    {
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceTimeBase'], 'DemEventId'))"!]
        [!SELECT "DemEventClass"!]
          [!WS "2"!] /* event: [!"as:name(..)"!] */
           [!WS "2"!] DemConf_DemEventParameter_[!"as:name(..)"!],
        [!ENDSELECT!]
      [!ENDLOOP!]
    };
  [!ELSE!]
    /* none */
  [!ENDIF!]

#define DEM_STOP_SEC_CONST_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_32
#include <Dem_MemMap.h>

  /** \brief Frequency based debouncing configuration description table */
  [!IF "node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceFrequencyBased'])"!]
    CONST(Dem_DebounceFrequencyCfgType, DEM_CONST)
      [!WS "2"!]Dem_DebounceFrequencyCfg[DEM_NUM_DEBOUNCE_FREQUENCY] =
    {
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*[1]/DemEventParameter/eb-list::*[DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceFrequencyBased'], 'DemEventId'))"!]
        [!SELECT "DemEventClass"!]
          [!WS "2"!]{ /* event: [!"as:name(..)"!] */
            [!/* DurationOfTimeWindow is stored in main function "ticks", not in ms! */!][!//
            [!WS "4"!][!//
            [!"num:i(ceiling((DemDebounceAlgorithmClass/eb-choice::*[1]/DemDurationOfTimeWindow * 1000) div (as:modconf('Dem')[1]/DemGeneral/DemTaskTime * 1000)))"!]U,
            [!WS "4"!][!//
            [!"num:i(DemDebounceAlgorithmClass/eb-choice::*[1]/DemThresholdForEventTestedFailed - 1)"!]U,
            [!WS "4"!][!//
            [!"num:i(DemDebounceAlgorithmClass/eb-choice::*[1]/DemThresholdForEventTestedPassed - 1)"!]U,
            [!WS "4"!][!//
            DemConf_DemEventParameter_[!"as:name(..)"!],
            [!WS "4"!][!//
            [!IF "DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceBehavior = 'DEM_DEBOUNCE_FREEZE'"!]
              DEM_DEBOUNCE_FREEZE, /* DemDebounceBehavior */
            [!ELSEIF "DemDebounceAlgorithmClass/eb-choice::*[1]/DemDebounceBehavior = 'DEM_DEBOUNCE_RESET'"!]
              DEM_DEBOUNCE_RESET, /* DemDebounceBehavior */
            [!ELSE!][!//
              DEM_DEBOUNCE_CONTINUE, /* DemDebounceBehavior */
            [!ENDIF!]
          [!WS "2"!]},
        [!ENDSELECT!]
      [!ENDLOOP!]
    };
  [!ELSE!]
    /* none */
  [!ENDIF!]

  #define DEM_STOP_SEC_CONST_32
  #include <Dem_MemMap.h>
[!ENDINDENT!]

/*------------------[Fault confirmation configuration]----------------------*/

[!INDENT "0"!]
  [!IF "node:exists(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:exists(DemEventClass/DemEventFailureCycleRef)])"!]
    [!IF "($CommonOperationCycleEnabled = 'false') or ($CalibrationWithoutEvCombSupport = 'false')"!]
      #define DEM_START_SEC_CALIB_8
      #include <Dem_MemMap.h>

      /** \brief Failure cycle and failure counter threshold configuration */
      /* Deviation MISRAC2012-2 */
      CONST(Dem_EventFailureCycleCfgType, DEM_CONST_CALIBRATION)
        [!WS "2"!]Dem_EventFailureCycleCfg[DEM_NUM_FAILURECYCLES] =
      {
        [!LOOP "text:split($FailureCycleCfgList, '#')"!]
          [!VAR "EventFailureCycle" = "text:split(., '*')[position() = 1]"!]
          [!VAR "EventFailureThreshold" = "text:split(., '*')[position() = 2]"!]
          [!WS "2"!]{
            [!IF "$CommonOperationCycleEnabled = 'false'"!]
              [!WS "4"!][!"$EventFailureCycle"!],
            [!ENDIF!]
            [!IF "$CalibrationWithoutEvCombSupport = 'false'"!]
              [!WS "4"!][!"num:i($EventFailureThreshold)"!]U
            [!ENDIF!]
          [!WS "2"!]},
        [!ENDLOOP!]
      };

      #define DEM_STOP_SEC_CALIB_8
      #include <Dem_MemMap.h>
    [!ELSE!]
      /* stored in event class */
    [!ENDIF!]
  [!ELSE!]
    /* none */
  [!ENDIF!]
[!ENDINDENT!]

[!INDENT "0"!]
  [!VAR "NumberEventsWithFaultConfirmation" = "count((DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[node:exists(DemEventClass/DemEventFailureCycleCounterThreshold)]))"!]
  [!IF "(node:existsAndFalse(DemGeneral/DemResetConfirmedBitOnOverflow)) and ($NumberEventsWithFaultConfirmation > 0)"!]
    #define DEM_START_SEC_CONST_16
    #include <Dem_MemMap.h>

    /** \brief Indexes for status counter for events array in ::Dem_NvData */
    CONST(Dem_StatusCounterIndexType, DEM_CONST)
      [!WS "2"!]Dem_StatusCounterIndex[DEM_STATUS_COUNTER_INDEX_SIZE] =
    {
      [!/* ConstGroupSize must be equal to DEM_STATUS_COUNTER_GROUP_SIZE */!][!//
      [!VAR "ConstGroupSize" = "4"!]
      [!VAR "StatusCounterIndex" = "0"!]
      [!WS "2"!]0U, /* base index of first event group always points to first data element */
      [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
        [!IF "(node:value(DemEventId) mod $ConstGroupSize) = 0"!]
          [!/* print base index of group calculated over all previous groups */!][!//
          [!WS "2"!][!"num:i($StatusCounterIndex)"!]U, /* base index of event group [[!"num:i(DemEventId)"!]..[!"num:i(DemEventId + ($ConstGroupSize - 1))"!]] */
        [!ENDIF!]
        [!IF "not(node:exists(DemEvtCmbCommonParamMaster)) and node:exists(DemEventClass/DemEventFailureCycleCounterThreshold)"!]
          [!VAR "StatusCounterIndex" = "$StatusCounterIndex + 1"!]
        [!ENDIF!]
      [!ENDLOOP!]
    };

    #define DEM_STOP_SEC_CONST_16
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[ Event Availability ]------------------------*/

#define DEM_START_SEC_CALIB_8
#include <Dem_MemMap.h>

[!INDENT "0"!]
  [!IF "($CalibrationSupport = 'true') or ($AvailabilitySupport = 'true')"!]
    [!VAR "BitIndex" = "1"!][!//
    [!VAR "ByteVal" = "0"!][!//
      /** \brief Calibratable bit-field array that holds availability status (enabled/disabled)
      [!WS!]**        of all events
      [!WS!]** Note: If an event is available, the corresponding bit is set to one. */
      /* Deviation MISRAC2012-2 */
      CONST(uint8, DEM_CONST_CALIBRATION) Dem_EventEnabled[DEM_EVENT_ENABLED_ARRAY_SIZE] =
    {
      [!INDENT "2"!]
        [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
          [!IF "node:existsAndTrue(DemEventClass/DemEventAvailable)"!]
            [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
          [!ENDIF!]
          [!VAR "BitIndex" = "$BitIndex + 1"!]
          [!IF "($BitIndex mod 8) = 0"!]
            [!"num:inttohex($ByteVal, 2)"!]U,
            [!VAR "ByteVal" = "0"!]
            [!VAR "BitIndex" = "0"!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!IF "($BitIndex mod 8) != 0"!]
          [!"num:inttohex($ByteVal, 2)"!]U
        [!ENDIF!]
      [!ENDINDENT!]
    };
  [!ENDIF!]
[!ENDINDENT!]

#define DEM_STOP_SEC_CALIB_8
#include <Dem_MemMap.h>

/*------------------[RTE / C-callback notifications]------------------------*/

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

[!INDENT "0"!]
  /** \brief Event callback property table */
  CONST(Dem_CbPropertyType, DEM_CONST) Dem_CbProperty[DEM_NUMBER_OF_EVENTS] =
  {
    [!WS "2"!]0U,
    [!WS "2"!]/* invalid event id entry */
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
      [!WS "2"!]/* event: [!"as:name(.)"!] */
      [!IF "node:exists(DemCallbackInitMForE)"!]
        DEM_GEN_CB_INIT_MONITOR |
        [!//
      [!ELSE!]
       [!WS "2"!]/* no init monitor callback */
     [!//
      [!ENDIF!]
      [!IF "node:exists(DemCallbackEventStatusChanged/eb-list::*)"!]
        [!IF "node:exists(DemCallbackEventStatusChanged/eb-list::*[not(node:exists(DemCallbackEventStatusChangedFnc))])"!]
          DEM_RTE_CB_TRIG_ON_EVST | [!//
        [!ENDIF!]
        [!IF "node:exists(DemCallbackEventStatusChanged/eb-list::*/DemCallbackEventStatusChangedFnc)"!]
          DEM_C_CB_TRIG_ON_EVST | [!//
        [!ENDIF!]
      [!ELSE!]
         [!WS "2"!]/* no trigger on event status callback(s) */
        [!//
      [!ENDIF!]
      [!IF "node:exists(DemCallbackEventDataChanged)"!]
        [!IF "not(node:exists(DemCallbackEventDataChanged/DemCallbackEventDataChangedFnc))"!]
          DEM_RTE_CB_TRIG_ON_EVDAT | [!//
        [!ELSE!]
          DEM_C_CB_TRIG_ON_EVDAT | [!//
        [!ENDIF!]
      [!ELSE!]
         [!WS "2"!]/* no trigger on event data changed callback */
        [!//
      [!ENDIF!]
      [!IF "(not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))) and node:exists(DemCallbackClearEventAllowed)"!]
        [!IF "not(node:exists(DemCallbackClearEventAllowed/DemCallbackClearEventAllowedFnc))"!]
          DEM_RTE_CB_CLEAR_EVENT_ALLOWED | [!//
        [!ELSE!]
          DEM_C_CB_CLEAR_EVENT_ALLOWED | [!//
        [!ENDIF!]
      [!ELSE!]
         [!WS "2"!]/* no clearEventAllowed callback */
        [!//
      [!ENDIF!]
      [!IF "DemEventClass/DemDebounceAlgorithmClass = 'DemDebounceMonitorInternal'"!]
        [!IF "node:exists(DemEventClass/DemDebounceAlgorithmClass/eb-choice::*[1]/DemCallbackGetFDC)"!]
          DEM_GEN_CB_FAULT_DETECTION_CTR | [!//
        [!ELSE!]
          [!WS "2"!]/* no fault detection counter callback */
          [!//
        [!ENDIF!]
      [!ELSE!]
         [!WS "2"!]/* DEM-internal fault detection counter */
        [!//
      [!ENDIF!]
       [!WS "2"!]DEM_ZERO_END,
    [!ENDLOOP!]
  };
  [!//
  /*---------------[Operation cycle automatic end enabled masks]-------------*/
  [!INDENT "0"!]
   [!/* vars for calculation of AutomaticEndEnabled bitmask */!]
    [!VAR "isAutoEndEnabled" = "0"!]
    [!VAR "maskCnt" = "1"!]
    [!VAR "autEndEnabledMask" = "0"!]
    [!VAR "autEndEnabledOpCycFrom" = "0"!]
    [!VAR "opCycCount" = "0"!]
    [!IF "node:exists(DemGeneral/DemOperationCycle/eb-list::*[node:existsAndTrue(DemOperationCycleAutomaticEnd)])"!]
      [!VAR "isAutoEndEnabled" = "1"!]
    [!ENDIF!]
    [!IF "$isAutoEndEnabled = 1"!]
      /* Array contains masks for automatic ending of operation cycles. */
      /* One mask groups 8 operation cycles to keep the numerical value of */
      /* the masks small. Every mask is a bitfield, containing the auto end */
      /* enabled information of 8 consecutive operation cycles. */
      CONST(uint8, DEM_CONST)
      [!WS "2"!]Dem_OpCycAutoEndEnabledMasks[DEM_OPCYC_NUM_OF_AUTO_END_ENABLED_MASKS] =
      {
        [!LOOP "DemGeneral/DemOperationCycle/eb-list::*"!]
          [!VAR "opCycCount" = "$opCycCount + 1"!]
          [!IF "node:existsAndTrue(DemOperationCycleAutomaticEnd)"!]
            [!VAR "autEndEnabledMask" = "$autEndEnabledMask + $maskCnt"!]
          [!ENDIF!]
          [!VAR "maskCnt" = "$maskCnt * 2"!]
          [!IF "(node:pos(.) + 1) mod 8 = 0 or node:islast(.)"!]
            [!WS "2"!]/* Automatic end enabled mask for operation cycles [!"num:integer($autEndEnabledOpCycFrom)"!] .. [!"num:integer($opCycCount - 1)"!] */
            [!WS "2"!][!"num:inttohex($autEndEnabledMask)"!]U,
            [!VAR "autEndEnabledMask" = "0"!]
            [!VAR "maskCnt" = "1"!]
            [!VAR "autEndEnabledOpCycFrom" = "$opCycCount"!]
          [!ENDIF!]
        [!ENDLOOP!]
      };
    [!ENDIF!]
  [!ENDINDENT!]
  [!//
  #define DEM_STOP_SEC_CONST_8
  #include <Dem_MemMap.h>

  /*---[INIT_MONITOR]---*/

  [!IF "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackInitMForE) != 0"!]
  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  /** \brief Generic callback function pointer table for InitMonitor */
  CONST(Dem_CbFuncPtrInitMonitorType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrInitMonitor[DEM_CB_TABLE_INIT_MONITOR_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackInitMForE"!]
      [!IF "node:exists(DemCallbackInitMForEFnc)"!]
        [!VAR "CallbackName" = "DemCallbackInitMForEFnc"!]
        [!WS "2"!]/* event: [!"as:name(../.)"!] */
      [!ELSE!]
        [!VAR "CallbackName" = "concat('Rte_Call_CBInitEvt_', as:name(../.), '_InitMonitorForEvent')"!]
      [!ENDIF!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>
  [!ENDIF!]

  [!IF "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackInitMForE) != 0"!]
  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief Generic lookup table for InitMonitor */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_CbLookupTableInitMonitor[DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackInitMForE"!]
      [!WS "2"!]DemConf_DemEventParameter_[!"as:name(../.)"!], [!//
      [!IF "node:exists(DemCallbackInitMForEFnc)"!]
        /* -> [!"DemCallbackInitMForEFnc"!]() */
      [!ELSE!]
        /* -> Rte_Call */
      [!ENDIF!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>
  [!ENDIF!]

  /*---[TRIGGER_ON_EVENT_STATUS]---*/

  #if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE != 0U)
  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  /** \brief C-Callback function pointer table for TriggerOnEventStatus */
  CONST(Dem_CbFuncPtrTrigOnEvStType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrTrigOnEvSt[DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE] =
  {
    [!VAR "CbNameList" = "'#'"!]  [!/* list of all unique callbacks */!][!//
    [!VAR "CCbCtr" = "0"!]        [!/* number of unique callbacks */!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventStatusChanged/eb-list::*[node:exists(DemCallbackEventStatusChangedFnc)]"!]
      [!IF "not(contains($CbNameList, concat('#', DemCallbackEventStatusChangedFnc, '#')))"!]
        [!VAR "CallbackName" = "DemCallbackEventStatusChangedFnc"!]
        [!WS "2"!]&[!"$CallbackName"!],
        [!VAR "CbNameList" = "concat($CbNameList, $CallbackName, '#')"!]
        [!VAR "CCbCtr" = "$CCbCtr + 1"!]
      [!ENDIF!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>
  #endif

  #if (DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE != 0U)
  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief C-Lookup table for TriggerOnEventStatus */
  CONST(Dem_CbLookupTableType, DEM_CONST)
    [!WS "2"!]Dem_CbLookupTableTrigOnEvSt[DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventStatusChanged/eb-list::*[node:exists(DemCallbackEventStatusChangedFnc)]"!]
      [!VAR "CallbackName" = "DemCallbackEventStatusChangedFnc"!]
      [!VAR "SearchStr" = "substring-after($CbNameList, '#')"!]
      [!/* finding the index of the callback in array Dem_CbFuncPtrTrigOnEvSt[] */!][!//
      [!FOR "FuncPtrTableIdx" = "0" TO "$CCbCtr"!]
        [!VAR "FuncNameStr" = "substring-before($SearchStr, '#')"!]
        [!VAR "SearchStr" = "substring-after($SearchStr, '#')"!][!//
        [!IF "$FuncNameStr = $CallbackName"!]
          [!/* current event-name and index to the array Dem_CbFuncPtrTrigOnEvSt[] */!][!//
          [!WS "2"!]{ DemConf_DemEventParameter_[!"as:name(../../.)"!], [!"num:integer($FuncPtrTableIdx)"!]U }, [!//
          /* -> [!"$CallbackName"!]() */
          [!BREAK!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>
  #endif

  #if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE != 0U)
  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  /** \brief RTE-Callback function pointer table
   ** for TriggerOnEventStatus
   **/
  CONST(Dem_RteFuncPtrTrigOnEvStType, DEM_CONST)
    [!WS "2"!]Dem_RteFuncPtrTrigOnEvSt[DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE] =
  {
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
      [!VAR "RunningNr" = "0"!]
      [!LOOP "DemCallbackEventStatusChanged/eb-list::*[not(node:exists(DemCallbackEventStatusChangedFnc))]"!]
        [!VAR "RunningNr" = "num:integer($RunningNr + 1)"!]
        [!IF "as:modconf('Dem')[1]/DemGeneral/DemServiceAPI/DemDefaultASRServiceAPI = 'AUTOSAR_2011'"!]
          [!VAR "CallbackName" = "concat('Rte_Call_CBEventUdsStatusChanged_', as:name(../../.), '_', as:name(.), '_CallbackEventUdsStatusChanged')"!]
        [!ELSE!]
          [!VAR "CallbackName" = "concat('Rte_Call_CBStatusEvt_', as:name(../../.), '_', $RunningNr, '_EventStatusChanged')"!]
        [!ENDIF!]
        [!WS "2"!]&[!"$CallbackName"!],
      [!ENDLOOP!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>
  #endif

  #if (DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE != 0U)
  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief RTE-Lookup table for TriggerOnEventStatus */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_RteLookupTableTrigOnEvSt[DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE] =
  {
    [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
      [!LOOP "DemCallbackEventStatusChanged/eb-list::*[not(node:exists(DemCallbackEventStatusChangedFnc))]"!]
        [!WS "2"!]DemConf_DemEventParameter_[!"as:name(../../.)"!],
      [!ENDLOOP!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>
  #endif

  /*---[TRIGGER_ON_DTC_STATUS]---*/

  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  [!IF "count(DemGeneral/DemCallbackDTCStatusChanged/eb-list::*) != 0"!]
  /** \brief Generic callback function pointer table for TriggerOnDTCStatus */
  CONST(Dem_CbFuncPtrTrigOnDTCStType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrTrigOnDTCSt[DEM_CB_TABLE_TRIG_ON_DTCST_SIZE] =
  {
    [!VAR "RunningNr" = "0"!]
    [!LOOP "DemGeneral/DemCallbackDTCStatusChanged/eb-list::*"!]
      [!IF "node:exists(DemCallbackDTCStatusChangedFnc)"!]
        [!VAR "CallbackName" = "DemCallbackDTCStatusChangedFnc"!]
      [!ELSE!]
        [!IF "as:modconf('Dem')[1]/DemGeneral/DemServiceAPI/DemDefaultASRServiceAPI = 'AUTOSAR_2011'"!]
          [!VAR "CallbackName" = "concat('Rte_Call_CBStatusDTC_', as:name(.), '_DTCStatusChanged')"!]
        [!ELSE!]
          [!VAR "RunningNr" = "num:integer($RunningNr + 1)"!]
          [!VAR "CallbackName" = "concat('Rte_Call_CBStatusDTC_', $RunningNr, '_DTCStatusChanged')"!]
        [!ENDIF!]
      [!ENDIF!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  [!ENDIF!]

  [!IF "count(DemGeneral/DemClearDTCNotification/eb-list::*[./DemClearDtcNotificationTime = 'START']) != 0"!]
  /** \brief Generic callback function pointer table for DemClearDTCNotification,
   ** with DemClearDtcNotificationTime set to START
   **/
  /* !LINKSTO Dem.ClearDTC.DemClearDtcNotificationFnc,1 */
  CONST(Dem_CbFuncPtrClearDTCNotifType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrStartClearDTCNotif[DEM_START_CLEAR_DTC_NOTIFICATION_SIZE] =
  {
    [!LOOP "DemGeneral/DemClearDTCNotification/eb-list::*[./DemClearDtcNotificationTime = 'START']"!]
      [!IF "node:exists(DemClearDtcNotificationFnc)"!]
        [!VAR "CallbackName" = "DemClearDtcNotificationFnc"!]
      [!ELSE!]
        [!VAR "CallbackName" = "concat('Rte_Call_ClearDtcNotification_', as:name(.), '_ClearDtcNotification')"!]
      [!ENDIF!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  [!ENDIF!]

  [!IF "count(DemGeneral/DemClearDTCNotification/eb-list::*[./DemClearDtcNotificationTime = 'FINISH']) != 0"!]
  /** \brief Generic callback function pointer table for DemClearDTCNotification,
   ** with DemClearDtcNotificationTime set to FINISH
   **/
  /* !LINKSTO Dem.ClearDTC.DemClearDtcNotificationFnc,1 */
  CONST(Dem_CbFuncPtrClearDTCNotifType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrFinishClearDTCNotif[DEM_FINISH_CLEAR_DTC_NOTIFICATION_SIZE] =
  {
    [!LOOP "DemGeneral/DemClearDTCNotification/eb-list::*[./DemClearDtcNotificationTime = 'FINISH']"!]
      [!IF "node:exists(DemClearDtcNotificationFnc)"!]
        [!VAR "CallbackName" = "DemClearDtcNotificationFnc"!]
      [!ELSE!]
        [!VAR "CallbackName" = "concat('Rte_Call_ClearDtcNotification_', as:name(.), '_ClearDtcNotification')"!]
      [!ENDIF!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  [!ENDIF!]

  /*---[TRIGGER_ON_EVENT_DATA_CHANGED]---*/

  #if (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
  /** \brief C-Callback function pointer table for TriggerOnEventDataChanged */
  CONST(Dem_CbFuncPtrTrigOnEvDatType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrTrigOnEvDat[DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE] =
  {
    [!VAR "CbNameList" = "'#'"!]  [!/* list of all unique callbacks */!][!//
    [!VAR "CCbCtr" = "0"!]        [!/* number of unique callbacks */!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventDataChanged[node:exists(DemCallbackEventDataChangedFnc)]"!]
      [!IF "not(contains($CbNameList, concat('#', DemCallbackEventDataChangedFnc, '#')))"!]
        [!VAR "CallbackName" = "DemCallbackEventDataChangedFnc"!]
        [!WS "2"!]&[!"$CallbackName"!],
        [!VAR "CbNameList" = "concat($CbNameList, $CallbackName, '#')"!]
        [!VAR "CCbCtr" = "$CCbCtr + 1"!]
      [!ENDIF!]
    [!ENDLOOP!]
  };
  #endif

  #if (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
  /** \brief RTE-Callback function pointer table for TriggerOnEventDataChanged */
  CONST(Dem_RteFuncPtrTrigOnEvDatType, DEM_CONST)
    [!WS "2"!]Dem_RteFuncPtrTrigOnEvDat[DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventDataChanged[not(node:exists(DemCallbackEventDataChangedFnc))]"!]
      [!VAR "CallbackName" = "concat('Rte_Call_CBDataEvt_', as:name(../.), '_EventDataChanged')"!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  #endif

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  #if (DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
  /** \brief C-Lookup table for TriggerOnEventDataChanged */
  CONST(Dem_CbLookupTableType, DEM_CONST)
    [!WS "2"!]Dem_CbLookupTableTrigOnEvDat[DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventDataChanged[node:exists(DemCallbackEventDataChangedFnc)]"!]
      [!VAR "CallbackName" = "DemCallbackEventDataChangedFnc"!]
      [!VAR "SearchStr" = "substring-after($CbNameList, '#')"!]
      [!/* finding the index of the callback in array Dem_CbFuncPtrTrigOnEvDat[] */!][!//
      [!FOR "FuncPtrTableIdx" = "0" TO "$CCbCtr"!]
        [!VAR "FuncNameStr" = "substring-before($SearchStr, '#')"!]
        [!VAR "SearchStr" = "substring-after($SearchStr, '#')"!]
        [!IF "$FuncNameStr = $CallbackName"!]
          [!/* current event-name and index to the array Dem_CbFuncPtrTrigOnEvDat[] */!][!//
          [!WS "2"!]{ DemConf_DemEventParameter_[!"as:name(../.)"!], [!"num:integer($FuncPtrTableIdx)"!]U }, [!//
          /* -> [!"$CallbackName"!]() */
          [!BREAK!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDLOOP!]
  };
  #endif

  #if (DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
  /** \brief RTE-Lookup table for TriggerOnEventDataChanged */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_RteLookupTableTrigOnEvDat[DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemCallbackEventDataChanged[not(node:exists(DemCallbackEventDataChangedFnc))]"!]
      [!WS "2"!]DemConf_DemEventParameter_[!"as:name(../.)"!],
    [!ENDLOOP!]
  };
  #endif

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>

  [!CALL "CREATE_SEM_CONFIG_LISTS"!][!//

  [!IF "$NumSev> 0"!]
  #define DEM_START_SEC_CONST_8
  #include <Dem_MemMap.h>

  /*-------------[Arrays for DemEventKind DEM_EVENT_KIND_SEV]-------------*/
  /** \brief Bit array, that holds the information for every configured event,
   **  if DemEventKind is set to DEM_EVENT_KIND_SEV (bit set to 1).
   */
  CONST(uint8, DEM_CONST)
      [!WS "2"!]Dem_SevConfigArray[DEM_SEV_CONFIG_ARRAY_SIZE] =
    {
      [!INDENT "2"!]
        [!LOOP "text:split($DemSevConfList, '#')"!]
          [!"."!]U,
        [!ENDLOOP!][!//
      [!ENDINDENT!]
    };

  #define DEM_STOP_SEC_CONST_8
  #include <Dem_MemMap.h>
  [!ENDIF!]

  [!IF "$NumSevWithCb> 0"!]
  /*---[Configuration for EventSyncStorageProcessed C-callback ]---*/

  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief Array for EventId with configured
  [!WS!]** callback for EventSyncStorageProcessed */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_SevWithSyncStoreProcCb[DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB] =
  {
    [!INDENT "2"!]
      [!LOOP "text:split($DemSevWithCbList, '#')"!]
        [!"substring-before(.,'?')"!]U, /* event: [!"substring-after(.,'?')"!] */
      [!ENDLOOP!][!//
    [!ENDINDENT!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>

  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  /* !LINKSTO dsn.Dem.Sem.ConfigSyncStoreProcCB,1 */
  /** \brief C-Callback function pointer table for EventSyncStorageProcessed */
  CONST(Dem_CbFuncPtrSevSyncStoreProcType, DEM_CONST)
    [!WS "2"!]Dem_CbFncPtrSevSyncStoreProc[DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB] =
  {
    [!INDENT "2"!]
      [!LOOP "text:split($DemSevCbNameList, '#')"!]
        &[!"."!],
      [!ENDLOOP!][!//
    [!ENDINDENT!]
  };

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>
  [!ENDIF!]

  /*---[CLEAR_EVENT_ALLOWED]---*/

  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  #if (DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
  /** \brief C-Callback function pointer table for ClearEventAllowed */
  CONST(Dem_CbFuncPtrClearEventAllowedType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrClearEventAllowed[DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
  {
    [!VAR "CbNameList" = "'#'"!]  [!/* list of all unique callbacks */!][!//
    [!VAR "CCbCtr" = "0"!]        [!/* number of unique callbacks */!][!//
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemCallbackClearEventAllowed[node:exists(DemCallbackClearEventAllowedFnc)]"!]
      [!IF "not(contains($CbNameList, concat('#', DemCallbackClearEventAllowedFnc, '#')))"!]
        [!VAR "CallbackName" = "DemCallbackClearEventAllowedFnc"!]
        [!WS "2"!]&[!"$CallbackName"!],
        [!VAR "CbNameList" = "concat($CbNameList, $CallbackName, '#')"!]
        [!VAR "CCbCtr" = "$CCbCtr + 1"!]
      [!ENDIF!]
    [!ENDLOOP!]
  };
  #endif

  #if (DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
  /** \brief C-Lookup table for ClearEventAllowed
  [!WS!]** also Clear Event Behavior info is packed in EventId */
  CONST(Dem_CbLookupTableType, DEM_CONST)
    [!WS "2"!]Dem_CbLookupTableClearEventAllowed
      [!WS "4"!][DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemCallbackClearEventAllowed[node:exists(DemCallbackClearEventAllowedFnc)]"!]
      [!VAR "CallbackName" = "DemCallbackClearEventAllowedFnc"!]
      [!VAR "ClEvBehavior" = "DemClearEventAllowedBehavior"!]
      [!VAR "SearchStr" = "substring-after($CbNameList, '#')"!][!//
      [!/* finding the index of the callback in array Dem_CbFuncPtrClearEventAllowed[] */!][!//
      [!FOR "FuncPtrTableIdx" = "0" TO "$CCbCtr"!]
        [!VAR "FuncNameStr" = "substring-before($SearchStr, '#')"!]
        [!VAR "SearchStr" = "substring-after($SearchStr, '#')"!]
        [!IF "$FuncNameStr = $CallbackName"!][!//
          [!/* current event-name and index to the array Dem_CbFuncPtrClearEventAllowed[] */!][!//
          [!WS "2"!]{ [!"$ClEvBehavior"!] | DemConf_DemEventParameter_[!"as:name(../.)"!], [!"num:integer($FuncPtrTableIdx)"!]U }, [!//
          /* -> [!"$CallbackName"!]() */
          [!BREAK!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDLOOP!]
  };
  #endif

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

  #if (DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief RTE-Lookup table for ClearEventAllowed
  [!WS!]** also Clear Event Behavior info is packed in EventId */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_RteLookupTableClearEventAllowed
      [!WS "4"!][DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemCallbackClearEventAllowed[not(node:exists(DemCallbackClearEventAllowedFnc))]"!]
      [!VAR "ClEvBehavior" = "DemClearEventAllowedBehavior"!]
      [!WS "2"!][!"$ClEvBehavior"!] | DemConf_DemEventParameter_[!"as:name(../.)"!],
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>
  #endif

  #define DEM_START_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>

   #if (DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
  /** \brief RTE-Callback function pointer table for ClearEventAllowed */
  CONST(Dem_CbFuncPtrClearEventAllowedType, DEM_CONST)
    [!WS "2"!]Dem_RteFuncPtrClearEventAllowed[DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[not(node:exists(DemEvtCmbCommonParamMaster)) or (node:existsAndTrue(DemEvtCmbCommonParamMaster))]/DemCallbackClearEventAllowed[not(node:exists(DemCallbackClearEventAllowedFnc))]"!]
      [!VAR "CallbackName" = "concat('Rte_Call_CBClrEvt_', as:name(../.), '_ClearEventAllowed')"!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  #endif

  /*---[GET_FDC]---*/

  [!IF "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemDebounceAlgorithmClass[node:name(.) = 'DemDebounceMonitorInternal']/DemCallbackGetFDC) != 0"!]
  /** \brief Generic callback function pointer table for
   ** GetFaultDetectionCounter
   **/
  CONST(Dem_CbFuncPtrGetFDCType, DEM_CONST)
    [!WS "2"!]Dem_CbFuncPtrGetFDC[DEM_CB_TABLE_GET_FDC_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemDebounceAlgorithmClass[node:name(.) = 'DemDebounceMonitorInternal']/DemCallbackGetFDC"!]
      [!IF "node:exists(DemCallbackGetFDCFnc)"!]
        [!VAR "CallbackName" = "DemCallbackGetFDCFnc"!]
        [!WS "2"!]/* event: [!"as:name(../../../.)"!] */
      [!ELSE!]
        [!VAR "CallbackName" = "concat('Rte_Call_CBFaultDetectCtr_', as:name(../../../.), '_GetFaultDetectionCounter')"!]
      [!ENDIF!]
      [!WS "2"!]&[!"$CallbackName"!],
    [!ENDLOOP!]
  };
  [!ENDIF!]

  #define DEM_STOP_SEC_CONST_UNSPECIFIED
  #include <Dem_MemMap.h>
  [!IF "count(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemDebounceAlgorithmClass[node:name(.) = 'DemDebounceMonitorInternal']/DemCallbackGetFDC) != 0"!]

  #define DEM_START_SEC_CONST_16
  #include <Dem_MemMap.h>

  /** \brief Generic lookup table for GetFaultDetectionCounter */
  CONST(Dem_EventIdType, DEM_CONST)
    [!WS "2"!]Dem_CbLookupTableGetFDC[DEM_LOOKUP_TABLE_GET_FDC_SIZE] =
  {
    [!LOOP "DemConfigSet/eb-list::*/DemEventParameter/eb-list::*/DemEventClass/DemDebounceAlgorithmClass[node:name(.) = 'DemDebounceMonitorInternal']/DemCallbackGetFDC"!]
      [!WS "2"!]DemConf_DemEventParameter_[!"as:name(../../../.)"!], [!//
      [!IF "node:exists(DemCallbackGetFDCFnc)"!]
        /* -> [!"DemCallbackGetFDCFnc"!]() */
      [!ELSE!]
        /* -> Rte_Call */
      [!ENDIF!]
    [!ENDLOOP!]
  };

  #define DEM_STOP_SEC_CONST_16
  #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*------------------[OBD Readiness Groups force complete]-------------------*/

/* !LINKSTO dsn.Dem.OBDPidSupport.Dem_ReadinessForceStatus_01,1 */
[!VAR "DemOBDForceReady" = "num:hextoint('0xFF')"!]
[!IF "node:exists(DemGeneral/DemGeneralOBD/DemOBDEngineType) and (DemGeneral/DemGeneralOBD/DemOBDEngineType = 'DEM_IGNITION_SPARK')"!]
[!VAR "DemOBDForceReady" = "bit:xor($DemOBDForceReady,num:hextoint('0x08'))"!]
[!ENDIF!]
[!IF "node:existsAndTrue(DemGeneral/DemOBDForceMisfireMonitoringReady)"!]
[!VAR "DemOBDForceReady" = "bit:xor($DemOBDForceReady,num:hextoint('0x10'))"!]
[!ENDIF!]
[!IF "node:existsAndTrue(DemGeneral/DemOBDForceFuelSysMonitoringReady)"!]
[!VAR "DemOBDForceReady" = "bit:xor($DemOBDForceReady,num:hextoint('0x20'))"!]
[!ENDIF!]
[!IF "node:existsAndTrue(DemGeneral/DemOBDForceCCMonitoringReady)"!]
[!VAR "DemOBDForceReady" = "bit:xor($DemOBDForceReady,num:hextoint('0x40'))"!]
[!ENDIF!]
#define DEM_START_SEC_CALIB_8
#include <Dem_MemMap.h>

[!IF "((node:existsAndTrue(DemGeneral/DemOBDSupport)) or (node:existsAndTrue(DemGeneral/DemGeneralJ1939/DemJ1939Readiness1Support)))"!]
/* Deviation MISRAC2012-2 */
CONST(uint8, DEM_CONST_CALIBRATION) Dem_ObdReadinessForceCompleteMask = [!"translate(num:inttohex($DemOBDForceReady, 2), 'abcdef', 'ABCDEF')"!]U;
[!IF "node:exists(DemGeneral/DemGeneralOBD/DemOBDCompliancy)"!]
/* Deviation MISRAC2012-2 */
CONST(uint8, DEM_CONST_CALIBRATION) Dem_ObdCompliancyPID1CByte = [!"num:integer(DemGeneral/DemGeneralOBD/DemOBDCompliancy)"!];
[!ELSE!]
/* Deviation MISRAC2012-2 */
CONST(uint8, DEM_CONST_CALIBRATION) Dem_ObdCompliancyPID1CByte = 0x5U; /* default value for non-OBD ECU */
[!ENDIF!]
[!ENDIF!]

/*------------------[OBD Readiness Groups PID41 ByteB Pre-set value]---------*/
[!IF "node:existsAndTrue(DemGeneral/DemOBDSupport)"!]
/* Deviation MISRAC2012-2 */
CONST(uint8, DEM_CONST_CALIBRATION) Dem_ObdReadinessPID41ByteB = 0x0CU;
[!ENDIF!]

#define DEM_STOP_SEC_CALIB_8
#include <Dem_MemMap.h>

#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

CONST(uint8, DEM_CONST) Dem_ConfirmThresholdAdaptable[DEM_CONFIG_EVENT_BIT_ARRAY_SIZE] =
{
  [!INDENT "2"!][!//
  [!VAR "ByteVal" = "0"!][!//
  [!VAR "BitIndex" = "1"!][!/* To override non-existing event 0 */!][!//
  [!LOOP "util:distinct(node:order(DemConfigSet/eb-list::*/DemEventParameter/eb-list::*, 'DemEventId'))"!]
    [!IF "node:existsAndFalse(DemEvtCmbCommonParamMaster)"!][!//
      [!/* Select the Masters config */!][!//
      [!SELECT "as:modconf('Dem')[1]/DemConfigSet/eb-list::*/DemEventParameter/eb-list::*[(node:existsAndTrue(DemEvtCmbCommonParamMaster)) and (DemDTCClassRef = node:current()/DemDTCClassRef)]"!]
        [!IF "node:existsAndTrue(DemEventClass/DemEventConfirmationThresholdCounterAdaptable)"!][!//
          [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ELSE!][!//
      [!IF "node:existsAndTrue(DemEventClass/DemEventConfirmationThresholdCounterAdaptable)"!][!//
        [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!VAR "BitIndex" = "$BitIndex + 1"!][!//
    [!IF "($BitIndex = 8)"!][!//
      [!"num:inttohex($ByteVal, 2)"!]U,
      [!VAR "ByteVal" = "0"!][!//
      [!VAR "BitIndex" = "0"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "($BitIndex != 0)"!][!//
    [!"num:inttohex($ByteVal, 2)"!]U
  [!ENDIF!][!//
  [!ENDINDENT!][!//
};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>
#endif /* (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON) */

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
[!//
[!INDENT "0"!]
  [!IF "$DemBSWDistributionOfEventReports = 'true'"!]
    [!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
      [!VAR "SatelliteCoreId" = "num:i(DemSatelliteCoreId)"!]

      #define DEM_1_Core_[!"$SatelliteCoreId"!]_START_SEC_VAR_CLEARED_8
      #include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>

      /** \brief Index of the next entry in the FIFO queue belonging to the satellite instance [!"$SatelliteCoreId"!] to write into */
      VAR(uint8, DEM_VAR) Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx;
      /** \brief Index of the next entry in the FIFO queue belonging to the satellite instance [!"$SatelliteCoreId"!] to read from */
      VAR(uint8, DEM_VAR) Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueReadIdx;

      #define DEM_1_Core_[!"$SatelliteCoreId"!]_STOP_SEC_VAR_CLEARED_8
      #include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>
    [!ENDLOOP!]

    #define DEM_START_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>

    /* !LINKSTO dsn.Dem.BSWDistribution.SatelliteContext,1 */
    /** \brief Function pointer array for easy access to SchM functions */
    CONST(Dem_SatelliteFncPtrType, DEM_CONST) Dem_SatelliteFncPtr[DEM_NUMBER_OF_CORES] =
    {
      [!FOR "SatelliteCoreId" = "0" TO "$NumberOfSatteliteCores"!]
        [!IF "$SatelliteCoreId != $MasterCoreId"!]
          [!WS "2"!]/* core Id [!"($SatelliteCoreId)"!] */
          [!WS "2"!]{
            [!WS "4"!]SchM_Enter_Dem_1_Core_[!"$SatelliteCoreId"!]_SCHM_DEM_EXCLUSIVE_AREA_SatelliteCore[!"$SatelliteCoreId"!],
            [!WS "4"!]SchM_Exit_Dem_1_Core_[!"$SatelliteCoreId"!]_SCHM_DEM_EXCLUSIVE_AREA_SatelliteCore[!"$SatelliteCoreId"!],
            [!WS "4"!]SchM_Send_Dem_1_Core_[!"$SatelliteCoreId"!]_ReportErrorStatusProvide
          [!WS "2"!]},
        [!ELSE!][!//
          [!WS "2"!]/* master core [!"$MasterCoreId"!] member --> must never be accessed */
          [!WS "2"!]{
            [!WS "4"!]NULL_PTR,
            [!WS "4"!]NULL_PTR,
            [!WS "4"!]NULL_PTR
          [!WS "2"!]},
        [!ENDIF!]
      [!ENDFOR!]
    };

    #define DEM_STOP_SEC_CONST_UNSPECIFIED
    #include <Dem_MemMap.h>
  [!ENDIF!]
[!ENDINDENT!]

/*==================[internal data]=========================================*/
[!//
[!INDENT "0"!]
  [!IF "$DemBSWDistributionOfEventReports = 'true'"!]
    [!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
      [!VAR "SatelliteCoreId" = "num:i(DemSatelliteCoreId)"!]

      #define DEM_1_Core_[!"$SatelliteCoreId"!]_START_SEC_VAR_CLEARED_16
      #include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>
      /** \brief Local queue on satellite instance of Core [!"$SatelliteCoreId"!] used for the multi-core functionality,
      [!WS!]** to store BSW event reports when the Dem is not yet fully initialized, i.e. pre-initialized */
      STATIC VAR(Dem_LocalBswEventQueueType, DEM_VAR)
      [!WS "2"!]Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueue[DEM_SATELLITE_[!"$SatelliteCoreId"!]_LOCAL_BSW_EVENT_QUEUE_SIZE];
      #define DEM_1_Core_[!"$SatelliteCoreId"!]_STOP_SEC_VAR_CLEARED_16
      #include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDINDENT!]

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
[!//
[!IF "$DemBSWDistributionOfEventReports = 'true'"!]

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC(boolean, DEM_CODE) Dem_QueueBswEventReportOnSatellite(
  CoreIdType          CoreId,
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  Dem_LocalBswEventQueueType QueueEntry;
  boolean QueueOperationStatus = FALSE;

  QueueEntry.EventId = EventId;
  QueueEntry.EventStatus = EventStatus;

  switch (CoreId)
  {
[!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
  [!VAR "SatelliteCoreId" = "num:i(DemSatelliteCoreId)"!]
    case DEM_SATELLITE_[!"$SatelliteCoreId"!]_CORE_ID:
    {
      /* queue overflow handling */
      if (Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx <
          DEM_SATELLITE_[!"$SatelliteCoreId"!]_LOCAL_BSW_EVENT_QUEUE_SIZE)
      {
        /* write request into the queue */
        Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueue[
          Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx] = QueueEntry;
        ++Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx;

        QueueOperationStatus = TRUE;
      }
      break;
    }
[!ENDLOOP!]
    /* CHECK: NOPARSE */
    default:
    {
      /* never reached, since it must not be called from the master instance core */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    }
    /* CHECK: PARSE */
  }

  return QueueOperationStatus;
}

FUNC(boolean, DEM_CODE) Dem_IsSatelliteQueueEmpty(CoreIdType CoreId)
{
  boolean Result = FALSE;

  switch (CoreId)
  {
[!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
  [!VAR "SatelliteCoreId" = "num:i(DemSatelliteCoreId)"!]
    case DEM_SATELLITE_[!"$SatelliteCoreId"!]_CORE_ID:
    {
      if (Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx ==
          Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueReadIdx)
      {
        Result = TRUE;
      }
      break;
    }
[!ENDLOOP!]
    /* CHECK: NOPARSE */
    default:
    {
      /* never reached, since it must not be called from the master instance core */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    }
    /* CHECK: PARSE */
  }

  return Result;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
[!//
[!VAR "DevErrorDetect" = "'false'"!]
[!IF "node:existsAndTrue(DemGeneral/DemDevErrorDetect)"!]
  [!VAR "DevErrorDetect" = "'true'"!]
[!ENDIF!]
[!//
[!LOOP "(DemGeneral/DemBSWDistribution/DemSatelliteInstanceConfig/eb-list::*)"!]
  [!VAR "SatelliteCoreId" = "num:i(DemSatelliteCoreId)"!]

#define DEM_1_Core_[!"$SatelliteCoreId"!]_START_SEC_CODE
#include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>
FUNC(void, DEM_1_Core_[!"$SatelliteCoreId"!]_CODE)
  Dem_1_Core_[!"$SatelliteCoreId"!]_SendQueuedBswEventReports(void)
{
  const CoreIdType CoreId = GetCoreID();

[!IF "$DevErrorDetect = 'true'"!]
  if (CoreId != [!"$SatelliteCoreId"!]U)
  {
    /* !LINKSTO Dem.BSWDistribution.BSWReportBufferSendingOnSatellites.WrongContext,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
  }
  else
[!ENDIF!]
  {
    uint8 QueueIdx;

    if (Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx > 0U)
    {
      for (QueueIdx = 0U;
           QueueIdx < Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueWriteIdx;
           QueueIdx++)
      {
        Dem_EventReportInfoType LocalBswEventInfo;

        LocalBswEventInfo.EventId = Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueue[QueueIdx].EventId;
        LocalBswEventInfo.EventStatus = Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueue[QueueIdx].EventStatus;
        LocalBswEventInfo.QueuedInPreinitPhase = TRUE;

        /* send the information to the master one by one
         * cast away the return value since it cannot be handled */
        (void)Dem_SatelliteFncPtr[CoreId].SchMSendReportErrorStatusToMaster(
          &LocalBswEventInfo);

        /* update read index of FIFO queue:
         * it's essential to update the ReadIdx after sending the information via Rte
         * to protect the reporting order in case of interruption by Dem_ReportErrorStatus() */
        ++Dem_Core[!"$SatelliteCoreId"!]_LocalBswEventQueueReadIdx;
      }
    }
  }
}
#define DEM_1_Core_[!"$SatelliteCoreId"!]_STOP_SEC_CODE
#include <Dem_1_Core_[!"$SatelliteCoreId"!]_MemMap.h>
[!ENDLOOP!]
[!ENDIF!]

/*==================[end of file]===========================================*/
