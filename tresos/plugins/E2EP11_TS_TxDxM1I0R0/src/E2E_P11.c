/**
 * \file
 *
 * \brief AUTOSAR E2EP11
 *
 * This file contains the implementation of the AUTOSAR
 * module E2EP11.
 *
 * \version 1.0.3
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <E2E_P11.h>      /* E2E Profile 11      */
#include <SCrc_CRC8.h>    /* SCrc routine CRC8  */

/*==================[macros]=================================================*/

#if (defined E2EP11_CRC_STARTVALUE) /* to prevent double declaration */
#error E2EP11_CRC_STARTVALUE is already defined
#endif /* #if (defined E2EP11_CRC_STARTVALUE) */

/** \brief Start value for Crc calculation
 *
 * Note: The CalculateCRC8() API is XORing this start value with 0xFF
 * resulting with actual internal start value equal to 0x00.
 */
#define E2EP11_CRC_STARTVALUE 0xFFU

#if (defined E2EP11_CRC_FINALXORVALUE) /* to prevent double declaration */
#error E2EP11_CRC_FINALXORVALUE is already defined
#endif /* #if (defined E2EP11_CRC_FINALXORVALUE) */

/** \brief XOR value which is applied on the result before returned by the Crc routine */
#define E2EP11_CRC_FINALXORVALUE 0xFFU

#if (defined E2EP11_COUNTER_MAX) /* to prevent double declaration */
#error E2EP11_COUNTER_MAX is already defined
#endif /* #if (defined E2EP11_COUNTER_MAX) */

/** \brief Maximum allowed counter value for E2E Profile 11 */
#define E2EP11_COUNTER_MAX 14U

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>

/**
 * \brief Perform null pointer checks of the input parameters of the Protect function
 *
 * \param[in] ConfigPtr Pointer to static configuration.
 * \param[in] StatePtr  Pointer to port/data communication state.
 * \param[in] DataPtr   Pointer to Data to be protected.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ProtectNullPtrChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2CONST(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);

/**
 * \brief Perform input parameter checks of the State parameter of the Protect function
 *
 * \param[in] StatePtr  Pointer to port/data communication state.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ProtectStateParamChecks
(
   P2CONST(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);

/**
 * \brief Perform null pointer checks of the input parameters of the Check function
 *
 * \param[in] ConfigPtr Pointer to static configuration.
 * \param[in] StatePtr  Pointer to port/data communication state.
 * \param[in] DataPtr   Pointer to Data to be protected.
 * \param[in] Length    Length of data in Bytes.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11CheckNullPtrChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2CONST(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
   uint16 Length
);

/**
 * \brief Perform input parameter checks of the ConfigPtr parameter
 *
 * \param[in] ConfigPtr Pointer to static configuration.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ConfigParamChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr
);

/**
 * \brief Perform input parameter checks of the State parameter of the Check function
 *
 * \param[in] StatePtr  Pointer to port/data communication state.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11CheckStateParamChecks
(
   P2CONST(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);

/**
 * \brief Calculate the Crc value
 *
 * \param[in] DataPtr        Pointer to Data to be protected.
 * \param[in] Counter        Port/data communication state counter value
 * \param[in] CrcByteOffset  Offset of CRC value in bytes containing the most significant
 *                           byte of the CRC value (i.e. CrcByteOffset+3 contains the least
 *                           significant byte of the 4-byte CRC value).
 * \param[in] Length         Length of Data.
 * \param[in] DataID         DataID used in CRC calculation.
 * \param[in] DataIDMode     Inclusion mode of ID in CRC computation.
 *
 * \pre All input parameters are valid
 *
 * \return Crc value
 */
static FUNC(uint8, E2E_CODE) E2E_EB_CalculateCrc
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Counter,
    uint16 CrcByteOffset,
    uint16 Length,
    uint16 DataID,
    E2E_P11DataIDMode DataIDMode
);

/**
 * \brief Protects the array/buffer to be transmitted using the E2E Profile P11.
 *
 * \param[in]     ConfigPtr Pointer to static configuration.
 * \param[in,out] CounterPtr  Pointer to port/data communication state.
 * \param[in,out] DataPtr   Pointer to Data to be protected.
 *
 * \pre All input parameters are valid
 *
 * \return Function execution success status
 * \retval E2E_E_INPUTERR_NULL At least one pointer parameter is a NULL pointer.
 * \retval E2E_E_INPUTERR_WRONG At least one input parameter is erroneous.
 * \retval E2E_E_OK Function completed successfully.
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11Protect
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) CounterPtr,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);

/**
 * \brief Check the received Data using the E2E Profile P11.
 *
 * \param[in]     ConfigPtr Pointer to static configuration.
 * \param[in,out] StatePtr  Pointer to port/data communication state.
 * \param[in,out] DataPtr   Pointer to Data to be protected.
 *
 * \pre All input parameters are valid
 *
 */
static FUNC(void, E2E_CODE) E2E_EB_P11Check
(
  P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);

/*==================[internal constants]=====================================*/

/*==================[internal data]==========================================*/

/*==================[external function definition]=========================*/

FUNC(Std_ReturnType, E2E_CODE) E2E_P11Protect
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
   uint16 Length
)
{
   Std_ReturnType RetVal;

   if (E2E_EB_P11ProtectNullPtrChecks(ConfigPtr, StatePtr, DataPtr) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (E2E_EB_P11ConfigParamChecks(ConfigPtr) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2E_EB_P11ProtectStateParamChecks(StatePtr) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if ((uint16)(ConfigPtr->DataLength / 8U) != Length)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      /* input ok => execute protect function */
      RetVal = E2E_EB_P11Protect(ConfigPtr, &(StatePtr->Counter), DataPtr);
   }

   return RetVal;
}

FUNC(Std_ReturnType, E2E_CODE) E2E_P11Check
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
   uint16 Length
)
{
   Std_ReturnType RetVal = E2E_E_OK;

   /* Note: Null pointer is allowed for DataPtr.
    *       This may happen if queued communication is used and no data is available. */
   if (E2E_EB_P11CheckNullPtrChecks(ConfigPtr, StatePtr, DataPtr, Length) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (E2E_EB_P11ConfigParamChecks(ConfigPtr) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2E_EB_P11CheckStateParamChecks(StatePtr) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if ((NULL_PTR != DataPtr) && (Length == 0U))
   {
        RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if ((Length != 0U) && (((uint16)(ConfigPtr->DataLength / 8U)) != Length))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      /* input ok => execute check function */
      E2E_EB_P11Check(ConfigPtr, StatePtr, DataPtr);
   }

   return RetVal;
}

FUNC(Std_ReturnType, E2E_CODE) E2E_P11ProtectInit
(
   P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
   Std_ReturnType RetVal;

   if (NULL_PTR != StatePtr)
   {
      StatePtr->Counter = 0U;
      RetVal = E2E_E_OK;
   }
   else
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }

   return RetVal;
}

FUNC(Std_ReturnType, E2E_CODE) E2E_P11CheckInit
(
   P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
   Std_ReturnType RetVal;

   if (NULL_PTR != StatePtr)
   {
      StatePtr->Counter = E2EP11_COUNTER_MAX;
      StatePtr->Status = E2E_P11STATUS_ERROR;
      RetVal = E2E_E_OK;
   }
   else
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }

   return RetVal;
}

FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P11MapStatusToSM
(
   Std_ReturnType CheckReturn,
   E2E_P11CheckStatusType Status
)
{
   E2E_PCheckStatusType RetVal;

   if (CheckReturn == E2E_E_OK)
   {
      switch (Status)
      {
          case E2E_P11STATUS_OK: /* fall through */
          case E2E_P11STATUS_OKSOMELOST:
          {
              RetVal = E2E_P_OK;
          }
          break;
          case E2E_P11STATUS_ERROR:
          {
              RetVal = E2E_P_ERROR;
          }
          break;
          case E2E_P11STATUS_REPEATED:
          {
              RetVal = E2E_P_REPEATED;
          }
          break;
          case E2E_P11STATUS_NONEWDATA:
          {
              RetVal = E2E_P_NONEWDATA;
          }
          break;
          case E2E_P11STATUS_WRONGSEQUENCE:
          {
              RetVal = E2E_P_WRONGSEQUENCE;
          }
          break;
          default:
          {
              RetVal = E2E_P_ERROR;
          }
          break;
      }
   }
   else
   {
      RetVal = E2E_P_ERROR;
   }

   return RetVal;
}

/*==================[internal function definition]===========================*/

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ProtectNullPtrChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2CONST(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
   Std_ReturnType RetVal;

   /* null pointer checks */
   if (NULL_PTR == ConfigPtr)
   {
      RetVal = E_NOT_OK;
   }
   else if (NULL_PTR == StatePtr)
   {
      RetVal = E_NOT_OK;
   }
   else if (NULL_PTR == DataPtr)
   {
      RetVal = E_NOT_OK;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ProtectStateParamChecks
(
   P2CONST(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P11ProtectStateType */
   if (E2EP11_COUNTER_MAX < StatePtr->Counter)
   {
      RetVal = E_NOT_OK;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11CheckNullPtrChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2CONST(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
   P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
   uint16 Length
)
{
   Std_ReturnType RetVal;

   /* null pointer checks */
   if (NULL_PTR == ConfigPtr)
   {
      RetVal = E_NOT_OK;
   }
   else if (NULL_PTR == StatePtr)
   {
      RetVal = E_NOT_OK;
   }
   else if ((NULL_PTR == DataPtr) && (0U != Length))
   {
    RetVal = E2E_E_INPUTERR_NULL;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11ConfigParamChecks
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr
)
{
  Std_ReturnType RetVal;

  /* sanity and input checks: E2E_P11ConfigType */
  /* ConfigPtr->MaxDeltaCounter requires no check since all values are valid */
  if (0U != (ConfigPtr->CRCOffset % 8U))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if ((ConfigPtr->CRCOffset + 8U) > ConfigPtr->DataLength)
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if (0U != (ConfigPtr->DataLength % 8U))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if (((E2E_P11_DATAID_BOTH != ConfigPtr->DataIDMode) &&
           (E2E_P11_DATAID_ALT != ConfigPtr->DataIDMode)) &&
           (E2E_P11_DATAID_NIBBLE != ConfigPtr->DataIDMode))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if ((E2E_P11_DATAID_NIBBLE == ConfigPtr->DataIDMode) &&
          (0x0FFFU < ConfigPtr->DataID))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if (0U != (ConfigPtr->CounterOffset % 4U))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if ((ConfigPtr->CounterOffset + 4U) > ConfigPtr->DataLength)
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if ((E2E_P11_DATAID_NIBBLE == ConfigPtr->DataIDMode) &&
    (0U != (ConfigPtr->DataIDNibbleOffset % 4U)))
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else if ((ConfigPtr->DataIDNibbleOffset + 4U) > ConfigPtr->DataLength)
  {
     RetVal = E2E_E_INPUTERR_WRONG;
  }
  else
  {
     RetVal = E_OK;
  }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11CheckStateParamChecks
(
   P2CONST(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P11CheckStateType */
   /* StatePtr->Status requires no check since it is not read (only written) */
   if (E2EP11_COUNTER_MAX < StatePtr->Counter)
   {
      RetVal = E_NOT_OK;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(uint8, E2E_CODE) E2E_EB_CalculateCrc
(
  P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  uint16 Counter,
  uint16 CrcByteOffset,
  uint16 Length,
  uint16 DataID,
  E2E_P11DataIDMode DataIDMode
)
{
   uint8 Crc;
   const uint8 DataIdLow  = (uint8)(DataID & 0x00FFU);
   const uint8 DataIdHigh = (E2E_P11_DATAID_NIBBLE == DataIDMode) ?
       (uint8)0U : (uint8)(DataID >> 8U);

   /* CRC over DataId
    * This step only applies for mode: E2E_P11_DATAID_ALT
    */
   if (E2E_P11_DATAID_ALT == DataIDMode)
   {
     if ((Counter % 2U) == 0U)
     {
         /* For Even counter values the CRC over DataId (low byte) */
         Crc = SCrc_CalculateCRC8(&DataIdLow, 1U, E2EP11_CRC_STARTVALUE, FALSE);
     }
     else
     {
         /* For Odd counter values the CRC over DataId (high byte) */
         Crc = SCrc_CalculateCRC8(&DataIdHigh, 1U, E2EP11_CRC_STARTVALUE, FALSE);
     }
   }
   else
   {
       /* CRC over DataId (low byte)
        * This step is equal for modes: E2E_P11_DATAID_BOTH
        * and E2E_P11_DATAID_NIBBLE
        */
       Crc = SCrc_CalculateCRC8(&DataIdLow, 1U, E2EP11_CRC_STARTVALUE, FALSE);

       /* CRC over DataId (high byte)
        * This step only applies for mode: E2E_P11_DATAID_BOTH
        * and E2E_P11_DATAID_NIBBLE
        */
       Crc = SCrc_CalculateCRC8(&DataIdHigh, 1U, Crc, FALSE);
   }

   /* CRC over Data. */
   if (0U < CrcByteOffset)
   {
      Crc = SCrc_CalculateCRC8(&DataPtr[0], CrcByteOffset, Crc, FALSE);

      if (CrcByteOffset < ((uint16)Length - (uint16)1U))
      {
         Crc = SCrc_CalculateCRC8(&DataPtr[CrcByteOffset + 1U],
                     (((uint32)Length - CrcByteOffset) - 1U), Crc, FALSE);
      }
   }
   else
   {
      Crc = SCrc_CalculateCRC8(&DataPtr[1U], ((uint32)Length - 1U), Crc, FALSE);
   }

  Crc = Crc ^ E2EP11_CRC_FINALXORVALUE;

  return Crc;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P11Protect
(
   P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) CounterPtr,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
  E2E_P11DataIDMode DataIDMode = ConfigPtr->DataIDMode;
  uint16 Length = (ConfigPtr->DataLength / 8U);
  uint16 DataID = ConfigPtr->DataID;
  uint16 CRCOffset = ConfigPtr->CRCOffset;
  uint16 CounterOffset = ConfigPtr->CounterOffset;
  uint16 CounterByteOffset = (uint16)(ConfigPtr->CounterOffset / 8U);
  uint16 DataIDNibbleOffset = ConfigPtr->DataIDNibbleOffset;
  uint16 DataIDNibbleByteOffset = (uint16)(ConfigPtr->DataIDNibbleOffset / 8U);

  /* Compute values written into data */
  const uint8 Counter = *CounterPtr;

  /* 1) Write DataIDNibble */
  if(E2E_P11_DATAID_NIBBLE == DataIDMode)
  {
    const uint8 DataIDNibble = (uint8)((DataID & (uint16)0x0F00U) >> 8U);

    if ( 0U == (DataIDNibbleOffset % 8U) )
    {
      /* DataIDNibble is written to low nibble */
      DataPtr[DataIDNibbleByteOffset] = (uint8)(DataPtr[DataIDNibbleByteOffset] & 0xF0U);
      DataPtr[DataIDNibbleByteOffset] = (uint8)(DataPtr[DataIDNibbleByteOffset] | DataIDNibble);
    }
    else
    {
      /* DataIDNibble is written to high nibble */
      DataPtr[DataIDNibbleByteOffset] = (uint8)(DataPtr[DataIDNibbleByteOffset] & 0x0FU);
      DataPtr[DataIDNibbleByteOffset] = (uint8)((DataPtr[DataIDNibbleByteOffset] | (DataIDNibble << 4U)) & 0xFFU);
    }
  }

  /* 2) Write Counter */
  if ( 0U == (CounterOffset % 8U) )
  {
    /* Counter is written to low nibble */
    DataPtr[CounterByteOffset] = (uint8)(DataPtr[CounterByteOffset] & 0xF0U);
    DataPtr[CounterByteOffset] = (uint8)(DataPtr[CounterByteOffset] | Counter);
  }
  else
  {
    /* Counter is written to high nibble */
    DataPtr[CounterByteOffset] = (uint8)(DataPtr[CounterByteOffset] & 0x0FU);
    DataPtr[CounterByteOffset] = (uint8)((DataPtr[CounterByteOffset] | (Counter << 4U)) & 0xFFU);
  }

  {
      const uint16 CrcByteOffset = (uint16)(CRCOffset / 8U);

      /* 3) Compute CRC */
      const uint8 ComputedCRC = E2E_EB_CalculateCrc(DataPtr, Counter, CrcByteOffset, Length, DataID, DataIDMode);

      /* 4) Write CRC */
      DataPtr[CrcByteOffset] = ComputedCRC;
  }

  /* 5) Increment Counter */
  /* update sequence counter modulo 14 */
  (*CounterPtr) = (((*CounterPtr) + 1U) % 15U);

   return E2E_E_OK;
}

static FUNC(void, E2E_CODE) E2E_EB_P11Check
(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    /* If DataPtr equals NULL, then no data was received in this cycle. */
    const boolean NewDataAvailable = (DataPtr != NULL_PTR) ? TRUE : FALSE;

    if (TRUE == NewDataAvailable)
    {
        E2E_P11DataIDMode DataIDMode = ConfigPtr->DataIDMode;
        uint16 Length = (ConfigPtr->DataLength / 8U);
        uint16 DataID = ConfigPtr->DataID;
        uint16 CRCOffset = ConfigPtr->CRCOffset;
        uint16 CounterOffset = ConfigPtr->CounterOffset;
        uint16 DataIDNibbleOffset = ConfigPtr->DataIDNibbleOffset;

        uint8 MaxDeltaCounter = ConfigPtr->MaxDeltaCounter;
        const uint8 LastStateCounter = StatePtr->Counter;

       /* Read DataIDNibble value which is placed at different positions depending on tx of Length */
        const uint8 DataIDNibbleByte = DataPtr[(uint16)(DataIDNibbleOffset / 8U)];
        const uint8 ReceivedNibble = (0U == (DataIDNibbleOffset % 8U)) ?
                                     (uint8)(DataIDNibbleByte & 0x0FU) : (uint8)((DataIDNibbleByte & 0xF0U) >> 4U);

        /* Read Counter value which is placed at different positions depending on tx of Length */
        const uint8 CounterNibbleByte = DataPtr[(uint16)(CounterOffset / 8U)];
        const uint8 ReceivedCounter = (0U == (CounterOffset % 8U)) ?
                                     (uint8)(CounterNibbleByte & 0x0FU) : (uint8)((CounterNibbleByte & 0xF0U) >> 4U);

        /* Read CRC */
        const uint16 CrcByteOffset = (uint16)(CRCOffset / 8U);
        const uint8 ReceivedCRC = DataPtr[CrcByteOffset];

        /* Compute CRC */
        const uint8 ComputedCRC = E2E_EB_CalculateCrc(DataPtr, ReceivedCounter, CrcByteOffset, Length, DataID, DataIDMode);

        /* Do checks */
        if (ReceivedCRC != ComputedCRC)
        {
            StatePtr->Status = E2E_P11STATUS_ERROR;
        }
        else if ( (E2E_P11_DATAID_NIBBLE == DataIDMode) && (ReceivedNibble != ((uint8)((DataID >> 8U) & (uint16)0x0FU))) )
        {
            StatePtr->Status = E2E_P11STATUS_ERROR;
        }
        else
        {
            /* correct CRC and E2E header content => check sequence counter */
            const uint8 DeltaCounter = (ReceivedCounter >= LastStateCounter) ?
                  (uint8)(ReceivedCounter - LastStateCounter) :
                  (uint8)((E2EP11_COUNTER_MAX +  ReceivedCounter + 1U ) - LastStateCounter);

            if (DeltaCounter > MaxDeltaCounter)
            {
                /* counter too big, i.e. too many data in the sequence
                 * have been probably lost since the last reception. */
                StatePtr->Status = E2E_P11STATUS_WRONGSEQUENCE;
            }
            else if (1U < DeltaCounter)
            {
                /* the Counter is incremented by DeltaCounter
                 * (1 <= DeltaCounter <= MaxDeltaCounter), i.e.
                 * some Data in the sequence have been probably lost since
                 * the last correct reception, but this is within
                 * the configured tolerance range. */
                StatePtr->Status = E2E_P11STATUS_OKSOMELOST;
            }
            else if (1U == DeltaCounter)
            {
                /* the Counter is incremented by 1, i.e. no Data has
                 * been lost since the last correct data reception. */
                StatePtr->Status = E2E_P11STATUS_OK;
            }
            else /* DeltaCounter == 0U */
            {
                /* the counter is identical, i.e. data has already been
                 * received (repeated message) */
                StatePtr->Status = E2E_P11STATUS_REPEATED;
            }

            /* Store counter value for next received message. */
            StatePtr->Counter = ReceivedCounter;
        }
    }
    else
    {
        /* no new data available since the last call */
        StatePtr->Status = E2E_P11STATUS_NONEWDATA;
    }
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>

/*==================[end of file]============================================*/
