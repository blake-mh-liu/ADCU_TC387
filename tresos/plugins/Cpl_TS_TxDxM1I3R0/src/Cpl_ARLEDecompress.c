/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_075, 1
 */

/*==================[misra deviations]============================================================*/

/* MISRA-C:2012 Deviation List:
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast shall not be performed between a pointer to object type and a
 *    pointer to a different object type."
 *
 *    Reason:
 *    This type cast is specified in AUTOSAR_SWS_CryptoAbstractionLibrary.pdf.
 *    It is ensured by a requirement, that this type cast does not violate
 *    memory bounds.
 */

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_077, 1
 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_ARLEDecompress_Cfg.h>
#include <Cpl_ARLEDecompress.h>

#include <Cpl_ARLECommon.h>

#include <TSMem.h>

#if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/


/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the internal states of the ARLEDecompress.
 **/
typedef enum
{
  CPL_ARLEDECOMPRESS_S_IDLE,
  CPL_ARLEDECOMPRESS_S_ILLEGAL,
  CPL_ARLEDECOMPRESS_S_INITIALIZED
}
Cpl_ARLEDecompressStateType;

/** \brief  Enumeration of the internal algorithm states of the ARLEDecompress.
 **/
typedef enum
{
  CPL_ARLEDECOMPRESS_ALGO_S_READING,
  CPL_ARLEDECOMPRESS_ALGO_S_WRITING
}
Cpl_ARLEDecompressAlgoStateType;

/** \brief  Structure which contains the context of the ARLEDecompress.
 **/
/* NOTE: - if this structure is changed, the "invalid" test expression for
 *         "CplArleDecompressConfig" in Cpl.xdm.m4 have to be adjusted, too
 *       - current size is ( 1*uint32 + 1*uint8 + 7*uint8 ) = ~12 bytes
 */
typedef struct
{

  /** \brief  the internal state machine state
   **/
          Cpl_ARLEDecompressStateType                           State;

  /** \brief  the current value
   **/
          uint8                                                curPattern[4];
  /** \brief  the pattern length (0 = uncompressed)
   **/
          uint8                                                curPatLength;
  /** \brief  number of patterns remaining to be written in the current run
   **/
          uint8                                                 curNoPatRemainingOput;

  /** \brief  which byte of the current run is currently read
   **/
          uint8                                                 curPosInRun;

  /** \brief  current algorithm state (reading or writing)
   **/
          Cpl_ARLEDecompressAlgoStateType                       decompState;
} Cpl_ARLEDecompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/** \brief  Execute ARLE decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the data that shall be processed.
 ** \param[in,out]  argIputBufLen       Holds a pointer to a memory location which stores:
 **                                     - on entry: the length of the input buffer
 **                                     - on exit: the amount of data read from the buffer
 ** \param[out]     argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location which stores:
 **                                     - on entry: the length of the output buffer
 **                                     - on exit: the amount of data written to the buffer
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer argOputBuf is too small to store the
 **                                     complete result.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Write ARLE decompressed data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the memory location where the
 **                                     compressed data is stored.
 ** \param[in,out]  argIputBufLen       Holds a pointer to a memory location which stores:
 **                                     - on entry: the length of the input buffer
 **                                     - on exit: the amount of data read from the buffer
 ** \param[out]     argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location which stores:
 **                                     - on entry: the length of the output buffer
 **                                     - on exit: the amount of data written to the buffer
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer argOputBuf is too small to store the
 **                                     complete result.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEWriteRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Read ARLE decompressed data from input buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the ARLE decompression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the memory location where the
 **                                     compressed data is stored.
 ** \param[in,out]  argIputBufLen       Holds a pointer to a memory location which stores:
 **                                     - on entry: the length of the input buffer
 **                                     - on exit: the amount of data read from the buffer
 **
 **/
STATIC FUNC(void, CPL_CODE) Cpl_ARLEReadRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen
);

/** \brief  Convert the encoded type into a pattern length
 **
 ** \param[in]      ctrlByte            The control byte from the input data stream
 **
 ** \returns  Length of the pattern.
 **
 ** \retval   0x00                      The type described by the control byte is
 **                                     CPL_ARLE_TYPE_UNCOMP, hence no pattern
 **                                     length can be calculated.
 **
 **/
STATIC FUNC(uint8, CPL_CODE) Cpl_ARLEType2Length
(
  uint8 ctrlByte
);
/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_ARLEDecompressStart]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
  VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  Cal_ReturnType locRetVal;

  locRetVal = CAL_E_NOT_OK;

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_CFG_IGNORE, 1 */
  CPL_PARAM_UNUSED(cfgPtr);

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_START_ERROR, 1 */
  if ( (sizeof(Cal_DecompressCtxBufType) >= sizeof(Cpl_ARLEDecompressCtxBufType)) &&
       (locCtxPtr                        != NULL_PTR                           )
     )
  {
    locCtxPtr->State   = CPL_ARLEDECOMPRESS_S_INITIALIZED;

    locCtxPtr->curNoPatRemainingOput = 0U;
    locCtxPtr->curPatLength = 0U;

    locCtxPtr->curPosInRun = 0U;
    locCtxPtr->decompState = CPL_ARLEDECOMPRESS_ALGO_S_READING;

    locRetVal = CAL_E_OK;
  }

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_ARLEDecompressUpdate]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressUpdate
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
  VAR(Cal_DecompressCtxBufType,   AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                  AUTOMATIC, CPL_APPL_DATA) iputBuf,
  P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) iputBufLen,
  P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
  P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  Cal_ReturnType locRetVal;

  locRetVal   = CAL_E_NOT_OK;

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_CFG_IGNORE, 1 */
  CPL_PARAM_UNUSED(cfgPtr);

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_UPDATE_ERROR, 1 */
  if ( (locCtxPtr        != NULL_PTR                       ) &&
       (locCtxPtr->State == CPL_ARLEDECOMPRESS_S_INITIALIZED) &&
       (iputBuf          != NULL_PTR                       ) &&
       (iputBufLen       != NULL_PTR                       ) &&
       (oputBuf          != NULL_PTR                       ) &&
       (oputBufLen       != NULL_PTR                       )
     )
  {
    locRetVal = Cpl_ARLEDecompressRun( locCtxPtr, iputBuf, iputBufLen, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_UPDATE_ERROR_RESET, 1
   */
  if ( (locRetVal        != CAL_E_OK                       ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER             ) &&
       (locCtxPtr        != NULL_PTR                       )
     )
  {
    locCtxPtr->State = CPL_ARLEDECOMPRESS_S_IDLE;
  }

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_ARLEDecompressFinish]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
  VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
  P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  Cal_ReturnType locRetVal;

  locRetVal   = CAL_E_NOT_OK;

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_CFG_IGNORE, 1 */
  CPL_PARAM_UNUSED(cfgPtr);

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_FINISH_ERROR, 1
   */
  if ( ( locCtxPtr        != NULL_PTR                ) &&
       ( locCtxPtr->State != CPL_ARLEDECOMPRESS_S_IDLE) &&
       ( oputBuf          != NULL_PTR                ) &&
       ( oputBufLen       != NULL_PTR                )
     )
  {
    locRetVal = Cpl_ARLEWriteRun
                (
                  locCtxPtr,
                  NULL_PTR,
                  NULL_PTR,
                  oputBuf,
                  oputBufLen
                );
    locCtxPtr->State = CPL_ARLEDECOMPRESS_S_IDLE;
  }

  /* !LINKSTO EB_CPL_ARLE_DSN_DECOMP_FINISH_ERROR_RESET, 1
   */
  if ( (locRetVal        != CAL_E_OK                 ) &&
       (locCtxPtr        != NULL_PTR                 )
     )
  {
    locCtxPtr->State = CPL_ARLEDECOMPRESS_S_IDLE;
  }

  return locRetVal;
}

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*==================[internal function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_ARLEDecompressRun]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEDecompressRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
  P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  Cal_ReturnType locRetVal          = CAL_E_NOT_OK;
  const uint32 locInitialIputBufLen = *argIputBufLen;
  uint32 locIputBufLen              = *argIputBufLen;
  const uint32 locInitialOputBufLen = *argOputBufLen;
  uint32 locOputBufLen              = *argOputBufLen;
  uint32 locOputBufPos              = 0U;
  uint32 locIputBufPos              = 0U;

  if ( locInitialIputBufLen == 0U )
  {
    locRetVal = CAL_E_OK;
  }
  else
  {
    /* !LINKSTO BL-30022_10223, 1
       !LINKSTO BL-30022_10586, 1
    */
    while ( (locIputBufPos < locInitialIputBufLen) &&
            (locRetVal != CAL_E_SMALL_BUFFER)
          )
    {
      /* the last call to the update function might not have completed the last run */
      if ( argCtx->decompState == CPL_ARLEDECOMPRESS_ALGO_S_READING )
      {
        Cpl_ARLEReadRun(argCtx,
                        &argIputBuf[locIputBufPos],
                        &locIputBufLen
                       );
        locIputBufPos += locIputBufLen;
        locIputBufLen =  locInitialIputBufLen - locIputBufPos;
      }

      if ( argCtx->decompState == CPL_ARLEDECOMPRESS_ALGO_S_READING )
      {
        /* nothing can be decoded any more - more input data needed */
        break;
      }
      else
      {
        locRetVal = Cpl_ARLEWriteRun( argCtx,
                                      &argIputBuf[locIputBufPos],
                                      &locIputBufLen,
                                      &argOputBuf[locOputBufPos],
                                      &locOputBufLen
                                      );
        locIputBufPos += locIputBufLen;
        locIputBufLen =  locInitialIputBufLen - locIputBufPos;
        locOputBufPos += locOputBufLen;
        locOputBufLen =  locInitialOputBufLen - locOputBufPos;
      }
    }
    if ( locIputBufPos >= locIputBufLen )
    {
      locRetVal = CAL_E_OK;
    }
  }

  *argIputBufLen = locIputBufPos;
  *argOputBufLen = locOputBufPos;

  return locRetVal;
}

STATIC FUNC(void, CPL_CODE) Cpl_ARLEReadRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen
)
{
    uint32 locIputBufPos;
    uint32 locIputBufLen;

    locIputBufPos = 0U;
    locIputBufLen = *argIputBufLen;

    while ( (locIputBufPos < locIputBufLen) &&
            (argCtx->decompState == CPL_ARLEDECOMPRESS_ALGO_S_READING)
          )
    {
      /* Read Control Byte - Type and length */
      if ( argCtx->curPosInRun == 0U )
      {
        argCtx->curNoPatRemainingOput  = argIputBuf[locIputBufPos] & CPL_ARLE_CNTR;
        argCtx->curPatLength      = Cpl_ARLEType2Length(argIputBuf[locIputBufPos]);
        if ( argCtx->curPatLength == 0U )
        {
          /* Uncompressed data */
          argCtx->decompState = CPL_ARLEDECOMPRESS_ALGO_S_WRITING;
        }
        else
        {
          argCtx->curPosInRun++;
        }
      }
      else
      {
        /* curPosInRun is at least 1 here */
        argCtx->curPattern[argCtx->curPosInRun - 1U] = argIputBuf[locIputBufPos];
        if (argCtx->curPosInRun >= argCtx->curPatLength)
        {
          argCtx->decompState = CPL_ARLEDECOMPRESS_ALGO_S_WRITING;
          argCtx->curPosInRun = 0U;
        }
        else
        {
          argCtx->curPosInRun++;
        }
      }
      locIputBufPos++;
    }

    *argIputBufLen = locIputBufPos;
}

/*------------------------------------------------------------------------------------------------*/
/*----------------[Cpl_ARLEWriteRun]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_ARLEWriteRun
(
  P2VAR(Cpl_ARLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  uint32 locOputBufPos;
  uint32 locOputBufLen;
  uint32 locIputBufPos;
  uint32 locIputBufLen;
  Cal_ReturnType locRetVal;
  /* the following variables are used to avoid pointer dereferencing in for loop */
  uint32 locCntr;
  uint8 locPatLength;
  uint8 locPattern[4];

  locOputBufPos =  0U;
  locIputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  if (argCtx->decompState == CPL_ARLEDECOMPRESS_ALGO_S_WRITING)
  {
    if (argCtx->curNoPatRemainingOput == 0U)
    {
      /* No output remaining - could happen if e.g. a run has a length of 0
       * (which does not make sense, but nevertheless the algorithm should be robust against it) */
      argCtx->decompState = CPL_ARLEDECOMPRESS_ALGO_S_READING;
      locRetVal     =  CAL_E_OK;
    }
    else if ( argCtx->curPatLength == 0U )
    {
      /* Write uncompressed data */
      if ( (argIputBuf != NULL_PTR) && (argIputBufLen != NULL_PTR) )
      {
        locIputBufLen = *argIputBufLen;

        if ( (locOputBufLen >= argCtx->curNoPatRemainingOput) &&
             (locIputBufLen >= argCtx->curNoPatRemainingOput)
           )
        {
          /* Complete pattern can be written this turn */
          locCntr = argCtx->curNoPatRemainingOput;
          argCtx->decompState = CPL_ARLEDECOMPRESS_ALGO_S_READING;
          locRetVal = CAL_E_OK;
        }
        else if (locOputBufLen < locIputBufLen)
        {
          /* Output limited by output buffer size */
          locCntr = locOputBufLen;
          locRetVal = CAL_E_SMALL_BUFFER;
        }
        else
        {
          /* Output limited by input buffer size */
          locCntr = locIputBufLen;
          locRetVal = CAL_E_OK;
        }
        TS_MemCpy(argOputBuf, argIputBuf, locCntr);
        locOputBufPos += locCntr;
        locIputBufPos += locCntr;

       /* the cast is legal because locCntr can never exceed 255 here,
        * because it's limited to the value range of
        * curNoPatRemainingOput. For the same reason, the difference
        * never gets smaller than 0. */
        argCtx->curNoPatRemainingOput -= (uint8)locCntr;
      }
      else
      {
        if (argCtx->curNoPatRemainingOput > locOputBufLen)
        {
          /* Cpl_ARLEDecompressFinish was called after a small buffer
           * was passed to Cpl_ARLEDecompressRun */
          locRetVal = CAL_E_SMALL_BUFFER;
        }
        else
        {
          /* This happens if this function is called from Cpl_ARLEDecompressFinish.
           * It means that there is an incomplete uncompressed data section in the input stream.
           */
        }
      }
    }
    else
    {
      /* Write compressed pattern */
      locPatLength = argCtx->curPatLength;

      for ( locCntr = 0u; locCntr < locPatLength; locCntr++ )
      {
        locPattern[locCntr] = argCtx->curPattern[locCntr];
      }

      locCntr = ((uint32)argCtx->curNoPatRemainingOput) * ((uint32)locPatLength);

      /* Limit to length of available buffer */
      if (locOputBufLen < locCntr)
      {
        /* Yields a number that is divisible by locPatLength */
        locCntr = locOputBufLen / ((uint32)locPatLength);
        argCtx->curNoPatRemainingOput -= (uint8)locCntr;
        locCntr *= locPatLength;
        locRetVal = CAL_E_SMALL_BUFFER;
      }
      else
      {
        argCtx->curNoPatRemainingOput = 0U;
        argCtx->decompState = CPL_ARLEDECOMPRESS_ALGO_S_READING;
        locRetVal = CAL_E_OK;
      }

      /* Write to the output buffer */
      for ( locOputBufPos = 0U; locOputBufPos < locCntr; locOputBufPos++ )
      {
        argOputBuf[locOputBufPos] = locPattern[locOputBufPos % locPatLength];
      }
    }
  }
  else if (argCtx->curPosInRun == 0U)
  {
    /* Last run was completely decoded and written to output buffer - everything OK */
    locRetVal = CAL_E_OK;
  }
  else
  {
    /* Function has been called with an incomplete pattern.
     * This could happen if the input stream is corrupted and
     * Cpl_ARLEDecompressFinish is called */
  }
  *argOputBufLen = locOputBufPos;
  if (argIputBufLen != NULL_PTR)
  {
    *argIputBufLen = locIputBufPos;
  }

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----------------[Cpl_ARLEType2Length]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(uint8, CPL_CODE) Cpl_ARLEType2Length
(
  uint8 ctrlByte
)
{
  uint8 retLength = 0xFFU;
  switch (ctrlByte & CPL_ARLE_TYPE)
  {
  case CPL_ARLE_TYPE_UNCOMP:
    retLength = 0U;
    break;
  case CPL_ARLE_TYPE_BYTE:
    retLength = 1U;
    break;
  case CPL_ARLE_TYPE_WORD:
    retLength = 2U;
    break;
  case CPL_ARLE_TYPE_LONG:
    retLength = 4U;
    break;
  /*CHECK: NOPARSE */
  default:
    {
      break;
    }
  /*CHECK: PARSE */
  }
  return retLength;
}
#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/

#else /* #if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_ARLEDECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
