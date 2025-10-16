/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA1.h>
#include <Cry_SHA2.h>
#include <Cry_SHA_Common.h>
#include <Cry_Common.h>

#if ((CRY_SHA1_ENABLED == STD_ON) || (CRY_SHA2_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

#if (defined CRY_SHACOMPRESSSTART)
#error CRY_SHACOMPRESSSTART is already defined
#endif
/** \brief  Initialize compress functions
 **
 **  This macro initializes the compression states of the context variable so
 **  that the compress functions can be used
 **
 **/
#define CRY_SHACOMPRESSSTART(CtxPtr) \
  (CtxPtr)->SHACompressState = CRY_SHA_S_COMPRESS;

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Processes the given input data
 **
 **  This function processes the input data stored in the context of the
 **  algorithm
 **
 ** \param[in] CtxPtr A pointer to the context of the algoritm
 **
 ** \param[in] CompressFct A pointer to the SHA-1/SHA-2 specific compression function
 **
 ** \returns  If process input has been finsihed or not
 **
 ** \retval TRUE Finished
 **
 ** \retval FALSE Not finished
 **
 **/
static FUNC(boolean, CRY_CODE) Cry_SHAProcessInput
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  Cry_SHACompressFctType                          CompressFct
);

/** \brief  Converts an unsigned 32-bit number into an array of unsigned byte values
 **
 **  This function converts an unsigned 32-bit number into an array of unsigned
 **  byte values as needed by the padding function of the SHA algorithms
 **
 ** \param[in] Count A number in an unsigned 32-bit variable which must be
 ** converted to an array of bytes
 **
 ** \param[out] Convert A pointer to an array of 8-bit unsigned values which
 ** will hold the converted number after this function has finished
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHACountConvert
(
  uint32                                 Count,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) Convert
);

/** \brief  Copies the digest to the output area
 **
 **  The internal state of the SHA algorithm after the input has been
 **  processed completely is the digest. This function copies the digest from
 **  the internal state to the output array.
 **
 ** \param[in] CtxPtr A pointer to the context of the algoritm
 **
 ** \returns  If the user-provided buffer is large enough to store the entire computed hash
 **
 ** \retval CSM_E_OK           The user-provided buffer is equal or larger than the hash length
 **
 ** \retval CSM_E_SMALL_BUFFER The user provided buffer is smaller than the hash length
 **/
static FUNC(Csm_ReturnType, CRY_CODE) Cry_SHAExport
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(void, CRY_CODE) Cry_SHAMainFunction
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  Cry_SHAInitFctType                              InitFct,
  Cry_SHACompressFctType                          CompressFct
)
{
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
  boolean finished = FALSE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */


  if (CtxPtr->RestartFlag == TRUE)
  {
    CtxPtr->State = CRY_SHA_S_INIT;
    CtxPtr->RestartFlag = FALSE;
  }

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
  /* If the "FAST" code variant is used, process as much data
   * as possible in a single Cry_SHAMainFunction() function call
   */
  while (finished == FALSE)
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */
  {
    switch(CtxPtr->State)
    {
      case CRY_SHA_S_INIT:
        /* 1. Init the number of processed bytes */
        CtxPtr->Count = (uint32)0U;

        /* 2. Initialize the internal state of the hash function */
        (InitFct)();

        CtxPtr->State = CRY_SHA_S_INITIALIZED;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
        /* Nothing else to process until input data is provided, exit the loop */
        finished = TRUE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */

        /* !LINKSTO CSM0454, 1
         */
        Csm_HashCallbackNotification(CSM_E_OK);
        break;

      case CRY_SHA_S_UPDATE:
        if(Cry_SHAProcessInput(CtxPtr, CompressFct) == TRUE)
        {
          CtxPtr->State = CRY_SHA_S_INITIALIZED;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
          /* Nothing else to process until the Update/Finish APIs are called, exit the loop */
          finished = TRUE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */

          /* !LINKSTO CSM0454, 1
           */
          Csm_HashCallbackNotification(CSM_E_OK);
        }
        break;

      case CRY_SHA_S_FINISH:
        /* Pad the buffer */

        /* initialize the Pad block */
        CtxPtr->SHAPad[0] = (uint8)0x80U;
        CtxPtr->length[0] = (uint8)1U;
        do
        {
          CtxPtr->SHAPad[CtxPtr->length[0]] = (uint8)0U;
          ++CtxPtr->length[0];
        } while (CtxPtr->length[0] < (uint8)CRY_SHA_BLOCK_LEN_BYTES);

        /* 1. convert length information */
        Cry_SHACountConvert(CtxPtr->Count, CtxPtr->length);

        /* 2. append padding to CtxPtr->Common.result_context */
        CtxPtr->Data = CtxPtr->SHAPad;

#if (CRY_SHA2_WORD_SIZE == 32U)
        CtxPtr->DataLength =
            (
                ((CRY_SHA_BLOCK_LEN_BYTES - 9U) - (CtxPtr->Count)) &
                ((uint32)0x3fUL)
            ) +
            (uint32)1U;
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
        CtxPtr->DataLength =
            (
                ((CRY_SHA_BLOCK_LEN_BYTES - 17U) - (CtxPtr->Count)) &
                ((uint32)0x7fUL)
            ) +
            (uint32)1U;
#endif

        CtxPtr->State = CRY_SHA_S_FINISH_UPDATE1;
        break;

      case CRY_SHA_S_FINISH_UPDATE1:
        if(Cry_SHAProcessInput(CtxPtr, CompressFct) == TRUE)
        {
          CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS;

          /* 3. append length information and complete last block */
          CtxPtr->Data       = CtxPtr->length;
#if (CRY_SHA2_WORD_SIZE == 32U)
          CtxPtr->DataLength =  8U;
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
          CtxPtr->DataLength =  16U;
#endif

          CtxPtr->State = CRY_SHA_S_FINISH_UPDATE2;
        }
        break;

      case CRY_SHA_S_FINISH_UPDATE2:
        if(Cry_SHAProcessInput(CtxPtr, CompressFct) == TRUE)
        {
          CtxPtr->State = CRY_SHA_S_FINISH_EXPORT;
        }
        break;

      case CRY_SHA_S_FINISH_EXPORT:
      {
        Csm_ReturnType exportResult;


        /* 4. export CtxPtr->Internalstate to user */
        exportResult = Cry_SHAExport(CtxPtr);

        CtxPtr->State = CRY_SHA_S_IDLE;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
        finished = TRUE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */

        /* !LINKSTO CSM0454, 1
         */
        Csm_HashCallbackNotification(exportResult);

        Csm_HashServiceFinishNotification();
      }
      break;

      case CRY_SHA_S_INITIALIZED:
      default:
      {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
        finished = TRUE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */
        break;
      }
    }
  }
}
/*==[Definition of functions with internal linkage]===========================*/

static FUNC(boolean, CRY_CODE) Cry_SHAProcessInput
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  Cry_SHACompressFctType                          CompressFct
)
{
  boolean Finished = FALSE;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST)
  /* If the "FAST" code variant is used, process as much data
   * as possible in a single Cry_SHAProcessInput() function call
   */
  while (Finished == FALSE)
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_FAST) */
  {
    switch(CtxPtr->ProcessInputState)
    {
      case CRY_SHA_S_PROCESS:
        if (CtxPtr->DataLength != (uint32) 0U)
        {
          /* initialize temporal data */
          CtxPtr->p    = CtxPtr->Data;
          CtxPtr->left = CtxPtr->DataLength;
          CtxPtr->copy = (uint8) 0U;

          /* 1. get unprocessed bytes from last block and update the counter */
#if (CRY_SHA2_WORD_SIZE == 32U)
          CtxPtr->offset = (uint8) ((CtxPtr->Count) & (uint32) 0x3fU);
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
          CtxPtr->offset = (uint8) ((CtxPtr->Count) & (uint32) 0x7fU);
#endif

          /* Ignore a possible overflow here */
          CtxPtr->Count += CtxPtr->DataLength;

          CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COPY1;
        }
        else
        {
          /* if there is no data, there is no work to do */
          Finished = TRUE;
        }
        break;

      case CRY_SHA_S_PROCESS_COPY1:
        /* 2. if existent, process incomplete blocks */
        if (CtxPtr->offset > (uint8) 0U)
        {
          /* find out how much data we need to copy */
          if
          (
              (uint32)((uint32)CtxPtr->offset + CtxPtr->DataLength) >
              (uint32)CRY_SHA_BLOCK_LEN_BYTES
          )
          {
            CtxPtr->copy = (uint8)CRY_SHA_BLOCK_LEN_BYTES - CtxPtr->offset;
          }
          else
          {
            /* cast is ok here: we tested dataBytes "< 64" above */
            CtxPtr->copy = (uint8) CtxPtr->DataLength;
          }

          /* fill up the temporary buffer with as much data as possible */
          Cry_CommonCopy
          (
              &CtxPtr->Partial[CtxPtr->offset],
              CtxPtr->p,
              (uint16)CtxPtr->copy
          );

          /* look if we have one block to compress */
          if
          (
              (uint8)(CtxPtr->offset + CtxPtr->copy) <
              (uint8)CRY_SHA_BLOCK_LEN_BYTES
          )
          {
            Finished = TRUE;
          }
          else
          {
            /* we have one complete block, so compress it */
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
            CRY_SHACOMPRESSSTART(CtxPtr);
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

            CtxPtr->p = &CtxPtr->p[CtxPtr->copy];
            CtxPtr->left -= (uint32)CtxPtr->copy;

            CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COMPRESS1;
          }
        }
        else
        {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
          CRY_SHACOMPRESSSTART(CtxPtr);
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

          CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COMPRESS2;
        }
        break;

      case CRY_SHA_S_PROCESS_COMPRESS1:
        if(CompressFct(CtxPtr->Partial) == TRUE)
        {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
          CRY_SHACOMPRESSSTART(CtxPtr);
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
          CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COMPRESS2;
        }
        break;

      case CRY_SHA_S_PROCESS_COMPRESS2:
        /* 3. process complete blocks */
#if (CRY_SHA2_WORD_SIZE == 32U)
        if ((CtxPtr->left & (uint32)0xffffffc0UL) != (uint32) 0U)
        {
          if(CompressFct(CtxPtr->p) == TRUE)
          {
            CtxPtr->p = &CtxPtr->p[CRY_SHA_BLOCK_LEN_BYTES];
            CtxPtr->left -= (uint32)CRY_SHA_BLOCK_LEN_BYTES;

            /* If there is data for another block, start processing. */
            if ((CtxPtr->left & (uint32)0xffffffc0UL) != (uint32) 0U)
            {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
              CRY_SHACOMPRESSSTART(CtxPtr);
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
            }
            else
            {
              CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COPY2;
            }
          }
        }
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
        if ((CtxPtr->left & (uint32)0xffffff80UL) != (uint32) 0U)
        {
          if(CompressFct(CtxPtr->p) == TRUE)
          {
            CtxPtr->p     = &CtxPtr->p[CRY_SHA_BLOCK_LEN_BYTES];
            CtxPtr->left -= (uint32)CRY_SHA_BLOCK_LEN_BYTES;

            /* If there is data for another block, start processing. */
            if ((CtxPtr->left & (uint32)0xffffff80UL) != (uint32) 0U)
            {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
              CRY_SHACOMPRESSSTART(CtxPtr);
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
            }
          }
        }
#endif
        else
        {
          CtxPtr->ProcessInputState = CRY_SHA_S_PROCESS_COPY2;
        }
        break;

      case CRY_SHA_S_PROCESS_COPY2:
        /* 4. Check if there is still data */
        if (CtxPtr->left > (uint32) 0U)
        {
          /* Copy data into partial buffer */
          Cry_CommonCopy
          (
              CtxPtr->Partial,
              CtxPtr->p,
              (uint16)CtxPtr->left
          );
        }

        Finished = TRUE;
        break;
      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
      default:
        {
          Finished = TRUE;
          break;
        }
      /* CHECK: PARSE */
    }
  }

  return Finished;
}

static FUNC(void, CRY_CODE) Cry_SHACountConvert
(
  uint32                                 Count,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) Convert
)
{
  /* convert into bits */
  Count <<= 3U;

  /* Copy the result. We only have the lower 32 bits, so the upper 32/96 bits
   * are zero.
   */
#if (CRY_SHA2_WORD_SIZE == 32U)
  Convert[0U] = (uint8)0U;
  Convert[1U] = (uint8)0U;
  Convert[2U] = (uint8)0U;
  Convert[3U] = (uint8)0U;
  Convert[4U] = (uint8)(Count >> 24U);
  Convert[5U] = (uint8)(Count >> 16U);
  Convert[6U] = (uint8)(Count >>  8U);
  Convert[7U] = (uint8)(Count       );
#endif

#if (CRY_SHA2_WORD_SIZE == 64U)
  Convert[0U ] = (uint8)0U;
  Convert[1U ] = (uint8)0U;
  Convert[2U ] = (uint8)0U;
  Convert[3U ] = (uint8)0U;
  Convert[4U ] = (uint8)0U;
  Convert[5U ] = (uint8)0U;
  Convert[6U ] = (uint8)0U;
  Convert[7U ] = (uint8)0U;
  Convert[8U ] = (uint8)0U;
  Convert[9U ] = (uint8)0U;
  Convert[10U] = (uint8)0U;
  Convert[11U] = (uint8)0U;
  Convert[12U] = (uint8)(Count >> 24U);
  Convert[13U] = (uint8)(Count >> 16U);
  Convert[14U] = (uint8)(Count >>  8U);
  Convert[15U] = (uint8)(Count       );
#endif
}

static FUNC(Csm_ReturnType, CRY_CODE) Cry_SHAExport
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr
)
{
  uint8_least index; /* loop variable */
  uint32 HashLength;
  Csm_ReturnType ErrorCode = CSM_E_OK;

  HashLength = CtxPtr->CfgPtr->HashLength;

  if(HashLength <= *(CtxPtr->ResultLengthPtr))
  {
    *(CtxPtr->ResultLengthPtr) = HashLength;
  }
  else
  {
    if (FALSE == CtxPtr->TruncationAllowed)
    {
      /* !LINKSTO CSM0661,1 */
      ErrorCode = CSM_E_SMALL_BUFFER;
    }
  }

#if (CRY_SHA2_WORD_SIZE == 32U)
  index = (uint8_least)0U;
   do
   {
     uint8_least tmpIndex; /* tmp space to save loop results */

     tmpIndex = index;
     tmpIndex <<= 2U;
     if(tmpIndex < *(CtxPtr->ResultLengthPtr))
     {
       CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >> 24U);
       tmpIndex++;
     }

     if(tmpIndex < *(CtxPtr->ResultLengthPtr))
     {
       CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >> 16U);
       tmpIndex++;
     }

     if(tmpIndex < *(CtxPtr->ResultLengthPtr))
     {
       CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >>  8U);
       tmpIndex++;
     }

     if(tmpIndex < *(CtxPtr->ResultLengthPtr))
     {
       CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index]       );
     }

     index++;
   } while (index <= (uint8_least)(*(CtxPtr->ResultLengthPtr) >> 2U));
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
    index = (uint8_least)0U;
    do
    {
      uint8_least tmpIndex; /* tmp space to save loop results */

      tmpIndex = index;
      tmpIndex <<= 2U;

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index + 1U] >> 24U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index + 1U] >> 16U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index + 1U] >>  8U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index + 1U]);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >> 24U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >> 16U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index] >>  8U);
        tmpIndex++;
      }

      if(tmpIndex < *(CtxPtr->ResultLengthPtr))
      {
        CtxPtr->Result[tmpIndex] = (uint8)(CtxPtr->Internalstate[index]);
      }

      index += 2U;
    } while (index <= (uint8_least)(*(CtxPtr->ResultLengthPtr) >> 2U));
#endif

  return ErrorCode;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if ((CRY_SHA1_ENABLED == STD_ON) || (CRY_SHA2_ENABLED == STD_ON)) */

typedef uint8 Cry_SHA_PrvtEmptyTranslationUnitType;

#endif /* #if ((CRY_SHA1_ENABLED == STD_ON) || (CRY_SHA2_ENABLED == STD_ON)) #else */
