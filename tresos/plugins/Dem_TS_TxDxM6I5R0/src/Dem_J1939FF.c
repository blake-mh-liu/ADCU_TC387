/* --------{ EB Automotive C Source File }-------- */

/* This file contains definitions for internal functions provided to
 * get the needed information for the J1939 freeze frame data. */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr, 1 */

#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <TSAutosar.h>                        /* EB specific standard types */
#include <TSMem.h>                          /* EB specific memory functions */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( (DEM_J1939_FREEZEFRAME_SUPPORT==STD_ON) && ( DEM_NUM_J1939FFSPNS > 0U ) )

/*==================[internal function declarations]========================*/

/** \brief Function to get the size of an SPN which is part of a
 **        J1939 freeze frame
 **
 ** \param[in] SPN Idx
 **
 ** \return Size of the J1939 freeze frame SPN
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_SizeJ1939FFType, DEM_CODE) Dem_SizeOfJ1939FFSPN(
  Dem_DataElementIdxType J1939FFSPN);

/** \brief Function to get a pointer to the specified J1939 FF-record entry data of
 ** an event memory entry
 **
 ** J1939FF class must not be the ::Dem_NullJ1939FFClass for this event.
 **
 ** \param[in] EvMemEntry
 **
 ** \return Pointer to the J1939 FF-record entry data
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE) Dem_J1939FFEntryData(
  Dem_EventMemoryEntryPtrConstType               EvMemEntry);

/*==================[external function definitions]=========================*/

FUNC(Dem_J1939FFClassIdxType, DEM_CODE) Dem_GbiJ1939FFClassIdx(Dem_EventIdType EventId)
{
  Dem_J1939FFClassIdxType Result = (Dem_J1939FFClassIdxType)DEM_J1939FFCLS_NULL_IDX;

  DBG_DEM_GBIJ1939FFCLASSIDX_ENTRY(EventId);

  Result = Dem_EventJ1939FFClassIdx[DEM_DESC_J1939_IDX(EventId)];

  DBG_DEM_GBIJ1939FFCLASSIDX_EXIT(Result, EventId);
  return Result;
}

FUNC(void, DEM_CODE) Dem_StoreJ1939FF(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_SizeEntryDataType                       CapturedDataSize,
  Dem_EventMemoryEntryPtrType                 EvMemEntryPtr,
  Dem_EventIdType                             EventId,
  Dem_EventNotificationDataPtrType            Notification)
{
  /* pointer to J1939FF data - for writing */
  const Dem_EntryDataPtrType J1939FFEntryData = Dem_J1939FFEntryData(EvMemEntryPtr);

  if (CapturedDataSize > 0U)
  {
    TS_MemCpy(J1939FFEntryData, CapturedDataBuf, CapturedDataSize);

#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
    Notification->TriggerOnEventData = EventId;
#else
    TS_PARAM_UNUSED(Notification);
    TS_PARAM_UNUSED(EventId);
#endif
  }
}

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_CollectJ1939FFInfo(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntry,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)                  BufSize,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)                   DestBuffer)
{
  /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.NoMatchedFreezeFrame, 2 */
  Dem_ReturnGetNextFilteredElementType Result = DEM_FILTERED_NO_MATCHING_ELEMENT;
  /* find event memory entry */
  const boolean EntryExists = Dem_SearchForEntry(EventId, EvMemEntry, NULL_PTR);
  /* J1939 freeze frame class index */
  Dem_J1939FFClassIdxType J1939FFClassIdx = Dem_GbiJ1939FFClassIdx(EventId);

  DBG_DEM_COLLECTJ1939FFINFO_ENTRY(EventId, EvMemEntry, BufSize, DestBuffer);

  /* check if event exist and has a configured J1939 Freeze frame */
  if ((EntryExists == TRUE) && (J1939FFClassIdx != DEM_J1939FFCLS_NULL_IDX))
  {
    /* pointer to J1939FF data - for reading */
    const Dem_EntryDataPtrConstType J1939FFEntryData =
      Dem_J1939FFEntryData(*EvMemEntry);

    /* J1939 freeze frame class */
    CONSTP2CONST(Dem_J1939FFClassType, AUTOMATIC, DEM_CONST) J1939FFClass =
      &Dem_J1939FFClass[J1939FFClassIdx];

    /* J1939 freeze frame class size */
    Dem_SizeJ1939FFType J1939FFSize = Dem_SizeOfJ1939FF(J1939FFClass);

    /* check if buffer size is sufficient */
    if (J1939FFSize <= (*BufSize))
    {
      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.MatchingOut, 2 */
      /* copy J1939 FF from it's memory to the buffer */
      TS_MemCpy(&DestBuffer[0], &J1939FFEntryData[0], J1939FFSize);

      /* update buffer size with J1939 freeze frame class size */
      *BufSize = J1939FFSize;

      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.FilterOK, 1 */
      Result = DEM_FILTERED_OK;
    }
    else
    {
      /* !LINKSTO Dem.J1939.Dem_J1939DcmGetNextFreezeFrame.SmallBufferSize, 2 */
      /* destination buffer is too small */
      Result = DEM_FILTERED_BUFFER_TOO_SMALL;
    }
  }

  DBG_DEM_COLLECTJ1939FFINFO_EXIT(EventId, EvMemEntry, BufSize, DestBuffer, Result);
  return Result;
}

FUNC(Dem_SizeJ1939FFType, DEM_CODE) Dem_SizeOfJ1939FF(
  P2CONST(Dem_J1939FFClassType, AUTOMATIC, DEM_CONST) J1939FFClass)
{
  Dem_SizeJ1939FFType Result = 0U;
  /* number of SPNs in J1939 FF */
  Dem_NumFFSPNsType NumJ1939FFSPNs = J1939FFClass->NumJ1939FFSPNs;

  /* pointer to SPNs/data element indexes array */
  CONSTP2CONST(Dem_DataElementIdxType, AUTOMATIC, DEM_CONST) DataElementIdxArray =
    J1939FFClass->J1939FFSPNDataElementIdx;

  Dem_NumFFSPNsType IndexSPNDataElem = 0U;

  DBG_DEM_SIZEOFJ1939FF_ENTRY(J1939FFClass);

  /* loop through all SPNs/data elements and calculate their size */
  for(IndexSPNDataElem = 0U; IndexSPNDataElem < NumJ1939FFSPNs; IndexSPNDataElem++)
  {
    /* calculate size of single SPN */
    Result += Dem_SizeOfJ1939FFSPN(DataElementIdxArray[IndexSPNDataElem]);
  }

  DBG_DEM_SIZEOFJ1939FF_EXIT(J1939FFClass, Result);
  return Result;
}

/*==================[internal function definitions]=========================*/

FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureJ1939FF(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)           CaptureBuffer,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)       J1939FFSize)
{
  Std_ReturnType Result = E_OK;
  /* J1939 Freeze frame class index */
  Dem_J1939FFClassIdxType J1939FFClassIdx = Dem_GbiJ1939FFClassIdx(EventId);
  /* check if event has a configured J1939 Freeze frame */
  P2CONST(Dem_J1939FFClassType, AUTOMATIC, DEM_CONST) J1939FFClass =
    &Dem_J1939FFClass[J1939FFClassIdx];
  /* pointer to SPNs/data element indexes array */
  CONSTP2CONST(Dem_DataElementIdxType, AUTOMATIC, DEM_CONST) DataElementIdxArray =
    J1939FFClass->J1939FFSPNDataElementIdx;

  Dem_NumFFSPNsType IndexSPNDataElem = 0U;
  Dem_DataElementIdxType DataElementIdx = 0U;
  Dem_SizeEntryDataType FFStartByte = 0U;
  /* number of SPNs in J1939 FF */
  Dem_NumFFSPNsType NumJ1939FFSPNs = J1939FFClass->NumJ1939FFSPNs;

  DBG_DEM_CAPTUREJ1939FF_ENTRY(EventId, CaptureBuffer, J1939FFSize);

  /* loop through all SPNs/data elements and read the related data */
  /* !LINKSTO dsn.Dem.J1939.FreezeFrame.J1939SPNuserDefined, 1 */
  for(IndexSPNDataElem = 0U; IndexSPNDataElem < NumJ1939FFSPNs; IndexSPNDataElem++)
  {
    Std_ReturnType DataPresent = E_NOT_OK;
    Dem_SizeEntryDataType DataElementSize = 0U;

    /* data element index */
    DataElementIdx = DataElementIdxArray[IndexSPNDataElem];
    /* data element size */
    DataElementSize = DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);

    /* read data related to SPN's data element */
    DataPresent = Dem_ReadExternalDataElement(&CaptureBuffer[FFStartByte],
                                              DataElementIdx,
                                              EventId);

    /* check if data wasn't stored successfully
     * and then fill buffer with padding according to data element size */
    if (DataPresent != E_OK)
    {
      const Dem_SizeEntryDataType StartIndex = FFStartByte;
      Dem_SizeEntryDataType StopIndex;
      Dem_SizeEntryDataType Index;

      StopIndex = StartIndex + DataElementSize;

      /* fill FF segment with padding values */
      for (Index = StartIndex; Index < StopIndex; ++Index)
      {
        CaptureBuffer[Index] = DEM_DATA_PADDING_VALUE;
      }

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
      /* data for J1939 FFs cannot be read, return DEM_E_NODATAAVAILABLE;
       * this return value is used to report a DET error outside the
       * exclusive area opened in Dem_ProcessEvent() */
      Result = DEM_E_NODATAAVAILABLE;
#endif
    }

    /* add element size -> start byte for the next element */
     FFStartByte += DataElementSize;
  }

  *J1939FFSize = FFStartByte;

  DBG_DEM_CAPTUREJ1939FF_EXIT(Result, EventId, CaptureBuffer, J1939FFSize);
  return Result;
}


STATIC FUNC(Dem_SizeJ1939FFType, DEM_CODE) Dem_SizeOfJ1939FFSPN(
  Dem_DataElementIdxType J1939FFSPN)
{
  Dem_SizeJ1939FFType Result = 0U;

  DBG_DEM_SIZEOFJ1939FFSPN_ENTRY(J1939FFSPN);

#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
  /* get size of SPN's data element */
  Result = DEM_EXTERNAL_DATA_ELEMENT_SIZE(J1939FFSPN);
#else
  TS_PARAM_UNUSED(J1939FFSPN);
#endif

  DBG_DEM_SIZEOFJ1939FFSPN_EXIT(Result, J1939FFSPN);
  return Result;
}

STATIC FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE) Dem_J1939FFEntryData(
  Dem_EventMemoryEntryPtrConstType EvMemEntry)
{
  const Dem_EventIdType EventId = EvMemEntry->EventId;
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
  Dem_EntryDataPtrType Result;

#if ( (DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U) )
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];
#endif

#if (DEM_NUM_FFSEGS > 0U)
  /* get freeze frame class layout */
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
    &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];
  const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);
#endif

  /* calculate start position of the needed FF */
  Dem_SizeEntryDataType StartPos = EvMemEntry->EntryDataPos;
#if (DEM_USE_INT_VAL_AREA == STD_ON)
  /* calculate size of internal values area */
  StartPos = StartPos + Dem_SizeOfIntValArea(EventId);
#endif

#if (DEM_NUM_EDSEGS > 0U)
  /* calculate size of Extended freeze frame */
  StartPos = StartPos + Dem_SizeOfED(EDClass);
#endif

#if (DEM_NUM_FFSEGS > 0U)
  /* calculate size of freeze frame */
  StartPos = StartPos + ((Dem_SizeEntryDataType)Dem_SizeOfFF(DEM_REGULAR_FF, FFClass) *
    MaxNumFF);
#endif /* DEM_NUM_FFSEGS > 0U */

  DBG_DEM_J1939FFENTRYDATA_ENTRY(EvMemEntry);

  Result = &Dem_EntryData[OriginIdx][StartPos];

  DBG_DEM_J1939FFENTRYDATA_EXIT(EvMemEntry, Result);
  return Result;
}
#endif /* (DEM_J1939_FREEZEFRAME_SUPPORT==STD_ON) && ( DEM_NUM_J1939FFSPNS > 0U ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*==================[end of file]===========================================*/
