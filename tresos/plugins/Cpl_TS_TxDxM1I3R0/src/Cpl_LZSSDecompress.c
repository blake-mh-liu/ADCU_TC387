/** \file        Cpl_LZSSDecompress.c
 **
 ** \brief       Cpl LZSS decompression interface.
 **
 ** \project     Crypto Primitive Library
 ** \author      Danny Block <Danny.Block@elektrobit.com>
 ** \author      EB Automotive GmbH, 91058 Erlangen, Germany
 **
 ** \controller  independent
 ** \compiler    independent
 ** \hardware    independent
 **
 ** Copyright 2012 by EB Automotive GmbH
 ** All rights exclusively reserved for EB Automotive GmbH,
 ** unless expressly agreed to otherwise
 **/

/* !LINKSTO EB_CPL_0801_011, 1
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
 *
 *  MISRAC2012-2) Deviated Rule: 13.5 (required)
 *    "The right-hand operand of a logical && or || operator shall not contain side effects."
 *
 *    Reason:
 *    The MISRA rule is not violated. This is a constraint of the MISRA checker: When a function
 *    is called on the right hand side of a logical operator, the checker always raises this error
 *    because it does not know whether the function has side effects or not. In our case, none of
 *    the functions have side effects.
 *
 */

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_013, 1
 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_LZSSDecompress_Cfg.h>
#include <Cpl_LZSSDecompress.h>



#if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/** \brief  Macro encodes the maximum necessary buffer size of all configurations;
 **         a buffer of that size in a individual configuration context holds the LZSS decompression
 **         ring buffer
 **/
#define  CPL_LZSSDECOMPRESS_BUF_MAX_SIZE  (CPL_LZSSDECOMPRESS_BUF_LB_MAX_SIZE)

/** \brief  A byte with its most significant bit set
 **/
#define  CPL_LZSSDECOMPRESS_SET_BYTE_MSB  ((uint8)0x80U)

/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the internal states of the LZSSDecompress.
 **/
typedef enum
{
  CPL_LZSSDECOMPRESS_S_IDLE,
  CPL_LZSSDECOMPRESS_S_ILLEGAL,
  CPL_LZSSDECOMPRESS_S_INITIALIZED
}
Cpl_LZSSDecompressStateType;

/** \brief  Enumeration of internal LZSSDecompress return values.
 **/
typedef enum
{
  CPL_LZSSDECOMPRESS_E_NOT_OK,
  CPL_LZSSDECOMPRESS_E_BLOCK_NOT_FINISHED,
  CPL_LZSSDECOMPRESS_E_BLOCK_FINISHED
}
Cpl_LZSSDecompressReturnType;

/** \brief  structure which contains the context of the LZSSDecompress.
 **/
/* NOTE: - if this structure is changed, the "invalid" test expression for
 *        "CplLzssDecompressLengthBitsPerBlock" in Cpl.xdm.m4 have to be adjusted, too
 *       - actual size is ( 3*uint32 + 2*uint8 + CPL_LZSSDECOMPRESS_BUF_MAX_SIZE*uint8 + 2*? +
 *                          (3*uint32 + 1*?) ) = ~29 bytes + CPL_LZSSDECOMPRESS_BUF_MAX_SIZE*uint8
 */
typedef struct
{
  /** \brief  pointer to the corresponding LZSS decompression primitive configuration
   **/
  P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) cfgPtr;

  /** \brief  the internal state machine state
   **/
          Cpl_LZSSDecompressStateType                             State;

  /** \brief  the LZSS decompression buffer
   **/
          uint8                                          rawBuffer[CPL_LZSSDECOMPRESS_BUF_MAX_SIZE];

  /** \brief  the LZSS decompression ring buffer where to search offset/length pairs and
   **         that is located in 'Buffer'
   **/
          Cpl_RingBufferType                                      rngBuffer;

  /** \brief  the offset of the current offset/length pair
   **/
          uint32                                                  curOffset;

  /** \brief  The length of the current offset/length pair
   **/
          uint32                                                  curLength;

  /** \brief  byte byte which indicates whether the next encodings  are literal bytes or
   **         offset/length pairs
   **/
          uint8                                                   flgByte;

  /** \brief  the current index in the 'flagByte'
   **/
          uint32                                                  flgByteMask;

  /** \brief  the first byte of an incomplete encoding.
   **/
          uint8                                                   encByte;

  /** \brief  do we have an incomplete encoding left over from the last call of
   **         'Cpl_LZSSDecompressUpdate()'?
   **/
          boolean                                                 encIncomplete;
}
Cpl_LZSSDecompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/** \brief  Initialize LZSS decompression computation context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS decompression is stored.
 ** \param[in]      argCfg              Pointer to LZSSDecompress module configuration which has to
 **                                     be used during the LZSS decompression computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressBeg
(
    P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
);

/** \brief  Execute LZSS decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS decompression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the data that shall be processed.
 ** \param[in,out]  argIputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer argOputBuf is too small to store the
 **                                     complete result.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressRun
(
    P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                        AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete LZSS decompression computation and reset parts of the context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS decompression is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressEnd
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Interprets a two byte block of compressed data as tuple of offset and length and
 **         calls Cpl_LZSSCopyBytesFromLookBack.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS decompression is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      argOputBufPos       The current position in argOputBuf where to insert
 **                                     decompressed data.
 ** \param[in]      argEncoding         The current two byte block of compressed data.
 **
 ** \returns  The new position in argOputBuf where to insert further decompressed data.
 **/
STATIC FUNC(uint32, CPL_CODE) Cpl_LZSSDecodeEncoding
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    VAR(uint32,                       AUTOMATIC               ) argOputBufLen,
    VAR(uint32,                       AUTOMATIC               ) argOputBufPos,
    VAR(uint16,                       AUTOMATIC               ) argEncoding
);

/** \brief  Write out decompressed data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS decompression is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      argOputBufPos       The current position in argOputBuf where to insert
 **                                     decompressed data.
 **
 ** \returns  The new position in argOputBuf where to insert further decompressed data.
 **/
STATIC FUNC(uint32, CPL_CODE) Cpl_LZSSCopyBytesFromLookBack
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    VAR(uint32,                       AUTOMATIC               ) argOputBufLen,
    VAR(uint32,                       AUTOMATIC               ) argOputBufPos
);

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressStart]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_016, 1
   */
  if ( (sizeof(Cal_DecompressCtxBufType) >= sizeof(Cpl_LZSSDecompressCtxBufType)) &&
       (locCtxPtr                        != NULL_PTR                            ) &&
       (locCfgPtr                        != NULL_PTR                            )
     )
  {
    locRetVal = Cpl_LZSSDecompressBeg( locCtxPtr, locCfgPtr );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressUpdate]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressUpdate
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                    AUTOMATIC, CPL_APPL_DATA) iputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) iputBufLen,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_021, 1
   */
  if ( (locCtxPtr        != NULL_PTR                        ) &&
       (locCtxPtr->State == CPL_LZSSDECOMPRESS_S_INITIALIZED) &&
       (locCfgPtr        != NULL_PTR                        ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr               ) &&
       (iputBuf          != NULL_PTR                        ) &&
       (iputBufLen       != NULL_PTR                        ) &&
       (oputBuf          != NULL_PTR                        ) &&
       (oputBufLen       != NULL_PTR                        )
     )
  {
    locRetVal = Cpl_LZSSDecompressRun(locCtxPtr, iputBuf, iputBufLen, oputBuf, oputBufLen);
  }

  /* !LINKSTO EB_CPL_0804_022, 1
   */
  if ( (locRetVal        != CAL_E_OK                        ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER              ) &&
       (locCtxPtr        != NULL_PTR                        ) &&
       (locCfgPtr        != NULL_PTR                        ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr               )
     )
  {

    (void) Cpl_LZSSDecompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressFinish]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_026, 1
   */
  if ( ( locCtxPtr        != NULL_PTR                 ) &&
       ( locCtxPtr->State != CPL_LZSSDECOMPRESS_S_IDLE) &&
       ( locCfgPtr        != NULL_PTR                 ) &&
       ( locCfgPtr        == locCtxPtr->cfgPtr        ) &&
       ( oputBuf          != NULL_PTR                 ) &&
       ( oputBufLen       != NULL_PTR                 ) &&
       (*oputBufLen       >= locCtxPtr->curLength     )
     )
  {
    locRetVal = Cpl_LZSSDecompressEnd(locCtxPtr, oputBuf, oputBufLen);
  }

  /* !LINKSTO EB_CPL_0804_029, 1
   */
  if ( (locRetVal        != CAL_E_OK                  ) &&
       (locCtxPtr        != NULL_PTR                  ) &&
       (locCfgPtr        != NULL_PTR                  ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr         )
     )
  {
    (void) Cpl_LZSSDecompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*==================[internal function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressBeg]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressBeg
(
    P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_LZSSDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argCfg->sizeBufLookBack <= CPL_LZSSDECOMPRESS_BUF_MAX_SIZE )
  {
    argCtx->cfgPtr        = argCfg;
    argCtx->State         = CPL_LZSSDECOMPRESS_S_INITIALIZED;
    (void) Cpl_CommonRingBufferInit
           (
               argCtx->rawBuffer,
               CPL_LZSSDECOMPRESS_BUF_MAX_SIZE,
             &(argCtx->rngBuffer),
               argCfg->sizeBufLookBack
           );
    argCtx->curOffset     = 0x00U;
    argCtx->curLength     = 0x00U;
    argCtx->flgByte       = 0x00U;
    argCtx->flgByteMask   = 0x00U;
    argCtx->encByte       = 0x00U;
    argCtx->encIncomplete = FALSE;

    locRetVal = CAL_E_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressRun]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressRun
(
    P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                        AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locIputBufLen;
  VAR(uint32,         AUTOMATIC) locOputBufLen;

  VAR(uint32,         AUTOMATIC) locIputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufPos;

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locIputBufLen = *argIputBufLen;
  locOputBufLen = *argOputBufLen;

  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* We start at the beginning of input and output buffers. */
  locIputBufPos = 0U;
  locOputBufPos = 0U;

  /* Determine if a incomplete encoding was detected the last run. */
  if ( argCtx->encIncomplete == TRUE )
  {
    /* Combine the byte stored in the last run and the first byte of the
     * input buffer to create a complete encoding and decode that encoding.
     */
    locOputBufPos = Cpl_LZSSDecodeEncoding
                    (
                      argCtx,
                      argOputBuf,
                      locOputBufLen,
                      locOputBufPos,
                      ( (uint16)((uint16)argCtx->encByte << 8U) | (uint16)argIputBuf[0U] )
                    );

    argCtx->encIncomplete = FALSE;

    locIputBufPos = 1U;
  }
  else
  if ( argCtx->curLength > 0U )
  {
    /* Some bytes still need to be written before the decoding
     * process can start again.
     */
    locOputBufPos = Cpl_LZSSCopyBytesFromLookBack
                    (
                      argCtx,
                      argOputBuf,
                      locOputBufLen,
                      locOputBufPos
                    );
  }
  else
  {
    /* Nothing to do. */
  }

  /* Main decompression loop */
  while ( (locIputBufPos < locIputBufLen) &&
          (locOputBufPos < locOputBufLen)
        )
  {
    /* Is the indicator byte fully processed? */
    if ( argCtx->flgByteMask == 0U )
    {
       /* Get the next indicator byte from the input and reset the bit mask. */
       argCtx->flgByteMask = CPL_LZSSDECOMPRESS_SET_BYTE_MSB;
       argCtx->flgByte     = argIputBuf[locIputBufPos];
       locIputBufPos++;
    }
    else
    {
      /* Check the current bit of the indicator byte. */
      if ( (argCtx->flgByte & argCtx->flgByteMask) == 0U )
      {
        /* The indicator byte tells us that there is a single byte at the
         * current position in the input buffer.
         */

        /* Simply copy the current byte to the end of the dictionary. */
        Cpl_CommonRingBufferPush( &(argCtx->rngBuffer), argIputBuf[locIputBufPos] );

        /* Simply copy the current byte to the end of the output buffer. */
        argOputBuf[locOputBufPos] = argIputBuf[locIputBufPos];
        locOputBufPos++;

        /* The current byte is processed, move one byte on. */
        locIputBufPos++;
      }
      else
      {
        /* The indicator byte tells us that we have a two-byte encoding at
         * the current input buffer position.
         */

        if ( (locIputBufPos + 1U) < locIputBufLen )
        {
          /* We still have two bytes left in the input buffer. Decode those two bytes. */
          locOputBufPos = Cpl_LZSSDecodeEncoding
                          (
                             argCtx,
                             argOputBuf,
                             locOputBufLen,
                             locOputBufPos,
                             (
                               (uint16)((uint16)argIputBuf[locIputBufPos     ] << 8) |
                               (uint16)         argIputBuf[locIputBufPos + 1U]
                             )
                          );

          /* Two bytes were processed. */
          locIputBufPos += 2U;
        }
        else
        {
          /* We only have one byte left in the input buffer. Store that
           * byte for the next call of this function.
           */
          argCtx->encByte        = argIputBuf[locIputBufPos];
          argCtx->encIncomplete  = TRUE;
          locIputBufPos++;
        }
      }

      /* Go on to the next bit in the indicator byte which indicates an
       * encoding or a single byte.
       */
      argCtx->flgByteMask >>= 1;
    }
  } /* end of main decompression loop */

  if ( argCtx->State == CPL_LZSSDECOMPRESS_S_ILLEGAL )
  {
    /* An error occurred during decompression. */
    locRetVal = CAL_E_NOT_OK;
  }
  else
  if ( (locIputBufPos     >= locIputBufLen) &&
       (argCtx->curLength == 0U           )
     )
  {
    /* We have processed the whole input buffer and we have written all
     * decoded bytes to the output buffer.
     */
    locRetVal = CAL_E_OK;
  }
  else
  {
    locRetVal = CAL_E_SMALL_BUFFER;
  }

  /* Return the length of data from buffer iputBuf that was already processed/compressed. */
  *argIputBufLen = locIputBufPos;

  /* Return the size of compressed data (the result) which was written to the buffer oputBuf. */
  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecompressEnd]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSDecompressEnd
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                       AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locOputBufLen = *argOputBufLen;
  locOputBufPos =  0U;
  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argOputBuf != NULL_PTR )
  {
    if ( argCtx->encIncomplete == TRUE )
    {
      /* !LINKSTO EB_CPL_0804_027, 1
       */
      locRetVal= CAL_E_NOT_OK;
    }
    else
    if ( argCtx->curLength == 0U )
    {
      locRetVal= CAL_E_OK;
    }
    else
    {
      /* !LINKSTO EB_CPL_0804_028, 1
       */

      /* Some bytes still need to be written. */
      locOputBufPos = Cpl_LZSSCopyBytesFromLookBack
                      (
                        argCtx,
                        argOputBuf,
                        locOputBufLen,
                        locOputBufPos
                      );

      locRetVal     = CAL_E_OK;
    }
  }

  *argOputBufLen = locOputBufPos;
   argCtx->State = CPL_LZSSDECOMPRESS_S_IDLE;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSDecodeEncoding]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(uint32, CPL_CODE) Cpl_LZSSDecodeEncoding
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    VAR(uint32,                       AUTOMATIC               ) argOputBufLen,
    VAR(uint32,                       AUTOMATIC               ) argOputBufPos,
    VAR(uint16,                       AUTOMATIC               ) argEncoding
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32, AUTOMATIC) locOputBufPos;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locOputBufPos = 0U;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* Extract the length from the encoding. */
  argCtx->curLength = ((uint32)argEncoding >> argCtx->cfgPtr->shftLength)
                        & argCtx->cfgPtr->maskLength;

  /* Extract the offset from the encoding. */
  argCtx->curOffset = ((uint32)argEncoding                              )
                        & argCtx->cfgPtr->maskOffset;

  /* Was the decoding correct? */
  /* Deviation MISRAC2012-2 <START> */
  if ( (argCtx->curLength <= argCtx->curOffset                                 ) &&
       (argCtx->curOffset <= Cpl_CommonRingBufferGetLevel(&(argCtx->rngBuffer)))
     )
  /* Deviation MISRAC2012-2 <STOP> */
  {
    locOputBufPos = Cpl_LZSSCopyBytesFromLookBack
                    (
                      argCtx,
                      argOputBuf,
                      argOputBufLen,
                      argOputBufPos
                    );
  }
  else
  {
    /* The string length is greater than the offset or the offset is greater
     * than the actual ring buffer size. This is an error. The data seems to be corrupt.
     * The decompression has failed.
     */
    argCtx->State = CPL_LZSSDECOMPRESS_S_ILLEGAL;
    locOputBufPos = argOputBufLen;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locOputBufPos;
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCopyBytesFromLookBack]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(uint32, CPL_CODE) Cpl_LZSSCopyBytesFromLookBack
(
  P2VAR(Cpl_LZSSDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                        AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    VAR(uint32,                       AUTOMATIC               ) argOputBufLen,
    VAR(uint32,                       AUTOMATIC               ) argOputBufPos
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32, AUTOMATIC) locLength;
  VAR(uint32, AUTOMATIC) locOputBufPos;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLength     = argCtx->curLength;
  locOputBufPos = argOputBufPos;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  while ( (locLength     > 0U           ) &&
          (locOputBufPos < argOputBufLen)
        )
  {
    argOputBuf[locOputBufPos] = Cpl_CommonRingBufferReadFromEnd
                                (
                                  &(argCtx->rngBuffer),
                                    argCtx->curOffset - 1U,
                                    CPL_D_NEGATIVE
                                );
                                Cpl_CommonRingBufferPush
                                (
                                  &(argCtx->rngBuffer),
                                    argOputBuf[locOputBufPos]
                                );
    locLength--;
    locOputBufPos++;
  }

  argCtx->curLength = locLength;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locOputBufPos;
}

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/

#else /* #if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_LzssDecompress_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
