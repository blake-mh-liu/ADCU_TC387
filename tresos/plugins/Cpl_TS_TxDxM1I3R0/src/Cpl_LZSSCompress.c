/** \file        Cpl_LZSSCompress.c
 **
 ** \brief       Cpl LZSS compression interface.
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

/* !LINKSTO EB_CPL_0801_001, 1
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
 */

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_003, 1
 */
#include <Cal_Types.h>
#include <Cal_Compress.h>

#include <Cpl_LZSSCompress_Cfg.h>
#include <Cpl_LZSSCompress.h>



#if (CPL_LZSSCOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/** \brief  The flag bit value of an uncompressed character in compressed data
 **/
#define  CPL_LZSSCOMPRESS_FLAG_CHR        0U

/** \brief  The flag bit value of a compressed sequence of characters in compressed data
 **/
#define  CPL_LZSSCOMPRESS_FLAG_REF        1U

/** \brief  The minimum size of the prefix of the look ahead buffer that matches a substring in
 **         the look back buffer
 **/
#define  CPL_LZSSCOMPRESS_MATCH_MIN_SIZE  3U

/** \brief  Macro to determine the minimum of two given values.
 **/
#define  CPL_LZSSCOMPRESS_MINIMUM(a,b)    ( ((a)<=(b)) ? (a) : (b) )

/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the internal states of the LZSSCompress.
 **/
typedef enum
{
  CPL_LZSSCOMPRESS_S_IDLE,
  CPL_LZSSCOMPRESS_S_INITIALIZED
}
Cpl_LZSSCompressStateType;

/** \brief  Enumeration of the internal states of the sub function Cpl_LZSSFindMatch.
 **/
typedef enum
{
  CPL_LZSSCOMPRESS_S_SFFMIDLE,
  CPL_LZSSCOMPRESS_S_SFFMBUSY
}
Cpl_LZSSCompressSfFmStateType;

/** \brief  Structure which contains the context of the LZSSCompress.
 **/
/* NOTE: - if this structure is changed, the "invalid" test expression for
 *         "CplLzssCompressLengthBitsPerBlock" in Cpl.xdm.m4 has to be adjusted, too
 *       - actual size is ( 11*uint32 + 1*uint8 + 3*? ) = ~48 bytes
 */
typedef struct
{
  /** \brief  pointer to the LZSS compression primitive configuration
   **/
  P2CONST(Cpl_LZSSCompressConfigType,    TYPEDEF, CPL_APPL_DATA) cfgPtr;

  /** \brief  the internal state machine state
   **/
          Cpl_LZSSCompressStateType                              State;

  /** \brief  counter which counts the number of loop iterations during the compression
   **/
          uint32                                                 loopCntr;

  /** \brief  the compression indicator that (counts from 0 to 8)
   **/
          uint8                                                  stepCntr;

  /** \brief  the position in the input stream
   **/
          uint32                                                 iputBuffPos;

  /** \brief  the position in the output stream
   **/
          uint32                                                 oputBuffPos;

  /** \brief  the offset of the longest string match
   **/
          uint32                                                 infoBestOff;

  /** \brief  the length of the longest string match
   **/
          uint32                                                 infoBestLen;

  /** \brief  byte which stores whether a block contains an uncompressed character or a
   **         two byte block with length and offset information
   **/
          uint8                                                  flagByte;

  /** \brief  the position of the current flagByte in the output stream
   **/
          uint32                                                 flagBytePos;

  /** \brief  Cpl_LZSSFindMatch sub function internal state machine state
   **/
          Cpl_LZSSCompressSfFmStateType                          sffmState;

  /** \brief  Cpl_LZSSFindMatch sub function best index result
   **/
          uint32                                                 sffmBestIdx;

  /** \brief  Cpl_LZSSFindMatch sub function best length result
   **/
          uint32                                                 sffmBestLen;

  /** \brief  Cpl_LZSSFindMatch sub function temporary index value
   **/
          uint32                                                 sffmTempIdx;

  /** \brief  Cpl_LZSSFindMatch sub function temporary length value
   **/
          uint32                                                 sffmTempLen;
}
Cpl_LZSSCompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/** \brief  Initialize LZSS compression computation context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in]      argCfg              Pointer to LZSSCompress module configuration which has to
 **                                     be used during the LZSS compression computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressBeg
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
);

/** \brief  Execute LZSS compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the data that shall be processed.
 ** \param[in,out]  argIputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     compressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer argOputBuf is too small to store the
 **                                     complete result.
 ** \retval   CAL_E_BUSY                Request was interrupted because "Cpl_LZSSCompressCtxBufType/
 **                                     Cpl_LZSSCompressConfigType/iterBeforeInterruption"
 **                                     iterations were reached.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressRun
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete LZSS compression computation and reset parts of the context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     compressed data shall be stored.
 ** \param[in,out]  argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressEnd
(
  P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Write context value 'flagByte' to output and reset related context variables.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     compressed data shall be stored.
 **
 ** \returns  Nothing.
 **/
STATIC FUNC(void, CPL_CODE) Cpl_LZSSHandleFlags
(
  P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf
);

/** \brief  Write data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in]      argIputBuf          Holds a pointer to the data that shall be processed.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     compressed data shall be stored.
 ** \param[in]      argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_SMALL_BUFFER        The provided buffer argOputBuf is too small to store the
 **                                     result.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSWriteBytes
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
      VAR(uint32,                     AUTOMATIC               ) argOputBufLen
);

/** \brief  Find the longest match of a prefix of the look ahead buffer in the look back buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the LZSS compression is stored.
 ** \param[in]      argIputBufLb        Holds a pointer to the look back buffer.
 ** \param[in]      argIputBufLbLen     Contains the length of the look back buffer in bytes.
 ** \param[in]      argIputBufLa        Holds a pointer to the look ahead buffer.
 ** \param[in]      argIputBufLaLen     Contains the length of the look ahead buffer in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 ** \retval   CAL_E_BUSY                Request was interrupted because "Cpl_LZSSCompressCtxBufType/
 **                                     Cpl_LZSSCompressConfigType/iterBeforeInterruption"
 **                                     iterations were reached.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSFindMatch
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLb,
      VAR(uint32,                     AUTOMATIC               ) argIputBufLbLen,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLa,
      VAR(uint32,                     AUTOMATIC               ) argIputBufLaLen
);

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCompressStart]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressStart
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_001, 1
   */
  if ( (sizeof(Cal_CompressCtxBufType) >= sizeof(Cpl_LZSSCompressCtxBufType)) &&
       (locCtxPtr                      != NULL_PTR                          ) &&
       (locCfgPtr                      != NULL_PTR                          )
     )
  {
    locRetVal = Cpl_LZSSCompressBeg( locCtxPtr, locCfgPtr );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCompressUpdate]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressUpdate
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                  AUTOMATIC, CPL_APPL_DATA) iputBuf,
    P2VAR(uint32,                 AUTOMATIC, CPL_APPL_DATA) iputBufLen,
    P2VAR(uint8,                  AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                 AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_006, 1
   */
  if ( (locCtxPtr        != NULL_PTR                      ) &&
       (locCtxPtr->State == CPL_LZSSCOMPRESS_S_INITIALIZED) &&
       (locCfgPtr        != NULL_PTR                      ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr             ) &&
       (iputBuf          != NULL_PTR                      ) &&
       (iputBufLen       != NULL_PTR                      ) &&
       (oputBuf          != NULL_PTR                      ) &&
       (oputBufLen       != NULL_PTR                      )
     )
  {
    locRetVal = Cpl_LZSSCompressRun( locCtxPtr, iputBuf, iputBufLen, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_007, 1
   */
  if ( (locRetVal        != CAL_E_OK                      ) &&
       (locRetVal        != CAL_E_BUSY                    ) &&
       (locCtxPtr        != NULL_PTR                      ) &&
       (locCfgPtr        != NULL_PTR                      ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr             )
     )
  {
    (void) Cpl_LZSSCompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCompressFinish]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressFinish
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                  AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                 AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_011, 1
   */
  if ( ( locCtxPtr        != NULL_PTR               ) &&
       ( locCtxPtr->State != CPL_LZSSCOMPRESS_S_IDLE) &&
       ( locCfgPtr        != NULL_PTR               ) &&
       ( locCfgPtr        == locCtxPtr->cfgPtr      ) &&
       ( oputBuf          != NULL_PTR               ) &&
       ( oputBufLen       != NULL_PTR               )
     )
  {
    locRetVal = Cpl_LZSSCompressEnd( locCtxPtr, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_012, 1
   */
  if ( (locRetVal        != CAL_E_OK                ) &&
       (locCtxPtr        != NULL_PTR                ) &&
       (locCfgPtr        != NULL_PTR                ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr       )
     )
  {
    (void) Cpl_LZSSCompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
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
/*----[Cpl_LZSSCompressBeg]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressBeg
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( (argCfg->sizeBufLookBack  <= CPL_LZSSCOMPRESS_BUF_LB_MAX_SIZE) &&
       (argCfg->sizeBufLookAhead <= CPL_LZSSCOMPRESS_BUF_LA_MAX_SIZE)
     )
  {
    argCtx->cfgPtr       = argCfg;
    argCtx->State        = CPL_LZSSCOMPRESS_S_INITIALIZED;
    argCtx->loopCntr     = 0U;
    argCtx->stepCntr     = 0U;

    argCtx->iputBuffPos  = 0U;
    argCtx->oputBuffPos  = 1U;

    argCtx->infoBestOff  = 0U;
    argCtx->infoBestLen  = 0U;

    argCtx->flagByte     = 0U;
    argCtx->flagBytePos  = 0U;

    argCtx->sffmState    = CPL_LZSSCOMPRESS_S_SFFMIDLE;

    argCtx->sffmBestIdx  = 0U;
    argCtx->sffmBestLen  = 0U;

    argCtx->sffmTempIdx  = 0U;
    argCtx->sffmTempLen  = 0U;

    locRetVal            = CAL_E_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCompressRun]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressRun
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr;

      VAR(uint32,                     AUTOMATIC               ) locBufLbIdx;
      VAR(uint32,                     AUTOMATIC               ) locBufLbLen;
      VAR(uint32,                     AUTOMATIC               ) locBufLaLen;

      VAR(uint32,                     AUTOMATIC               ) locIputBufLen; /* to avoid pointer
                                                                                  dereferencing in
                                                                                  function
                                                                                */
      VAR(uint32,                     AUTOMATIC               ) locOputBufLen; /* to avoid pointer
                                                                                  dereferencing in
                                                                                  function
                                                                                */

      VAR(Cal_ReturnType,             AUTOMATIC               ) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr     =  argCtx->cfgPtr;
  locIputBufLen = *argIputBufLen;
  locOputBufLen = *argOputBufLen;

  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( locOputBufLen == 0U )
  {
    locRetVal = CAL_E_SMALL_BUFFER;
  }
  else
  if ( locIputBufLen == 0U )
  {
    locRetVal = CAL_E_OK;
  }
  else
  {

    do
    {
      if ( ( argCtx->iputBuffPos                  < CPL_LZSSCOMPRESS_MATCH_MIN_SIZE) ||
           ((locIputBufLen - argCtx->iputBuffPos) < CPL_LZSSCOMPRESS_MATCH_MIN_SIZE)
         )
      {
        argCtx->infoBestOff = 0U;
        argCtx->infoBestLen = 0U;

        locRetVal           = Cpl_LZSSWriteBytes
                              (
                                argCtx,
                                argIputBuf,
                                argOputBuf,
                                locOputBufLen
                              );
      }
      else
      {
        locBufLbIdx = (argCtx->iputBuffPos < locCfgPtr->sizeBufLookBack)
                      ? ((uint32)0U)
                      : (argCtx->iputBuffPos - locCfgPtr->sizeBufLookBack);

        locBufLbLen = CPL_LZSSCOMPRESS_MINIMUM
                      (
                        argCtx->iputBuffPos, locCfgPtr->sizeBufLookBack
                      );

        locBufLaLen = CPL_LZSSCOMPRESS_MINIMUM
                      (
                        (locIputBufLen - argCtx->iputBuffPos), locCfgPtr->sizeBufLookAhead
                      );

        locRetVal   = Cpl_LZSSFindMatch
                      (
                         argCtx,
                        &(argIputBuf[locBufLbIdx        ]), locBufLbLen,
                        &(argIputBuf[argCtx->iputBuffPos]), locBufLaLen
                      );

        if ( locRetVal == CAL_E_OK )
        {
          /* convert found 'bestIdx' to 'bestOff' */
          argCtx->infoBestOff = argCtx->iputBuffPos - locBufLbIdx - argCtx->sffmBestIdx;

          /* ensure that found 'bestLen' is less than or equal to 'bestOff' */
          argCtx->infoBestLen = CPL_LZSSCOMPRESS_MINIMUM
                                (
                                  argCtx->sffmBestLen, argCtx->infoBestOff
                                );

          locRetVal           = Cpl_LZSSWriteBytes
                                (
                                  argCtx,
                                  argIputBuf,
                                  argOputBuf,
                                  locOputBufLen
                                );

          if ( ( argCtx->iputBuffPos                                   <  locIputBufLen) &&
               ((argCtx->loopCntr % locCfgPtr->iterBeforeInterruption) == 0U           )
             )
          {
            locRetVal = CAL_E_BUSY;
          }
        }
      }
    }
    while ( (locRetVal           == CAL_E_OK     ) &&
            (argCtx->iputBuffPos <  locIputBufLen)
          );

  }

  if ( locRetVal == CAL_E_OK )
  {
    if ( locIputBufLen > 0U )
    {
      if ( argCtx->stepCntr != 0U )
      {
        /* The FALSE branch cannot be covered as (argCtx->stepCntr != 0U) is TRUE only when all the
         * data was written in the output buffer succesfully.
         * Nevertheless, for completness sake this check needs to be kept. */
        /* CHECK: NOPARSE */
        if ( locOputBufLen >= (argCtx->flagBytePos + 1U) )
        {
          argOputBuf[argCtx->flagBytePos] = argCtx->flagByte;
        }
        else
        {
          locRetVal = CAL_E_SMALL_BUFFER;
        }
        /* CHECK: PARSE */
      }
      else
      {
        argCtx->oputBuffPos--;
      }

      *argIputBufLen = argCtx->iputBuffPos;
      *argOputBufLen = argCtx->oputBuffPos;
    }
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSCompressEnd]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSCompressEnd
(
  P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                     AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)

{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

   CPL_PARAM_UNUSED(argOputBuf);

   argCtx->State     = CPL_LZSSCOMPRESS_S_IDLE;
   argCtx->sffmState = CPL_LZSSCOMPRESS_S_SFFMIDLE;

  *argOputBufLen     = 0U;

   locRetVal         = CAL_E_OK;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSHandleFlags]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CPL_CODE) Cpl_LZSSHandleFlags
(
  P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  argCtx->stepCntr++;

  if ( argCtx->stepCntr >= 8U )
  {
    argOputBuf[argCtx->flagBytePos] = argCtx->flagByte;
    argCtx->stepCntr                = 0U;
    argCtx->flagByte                = 0U;
    argCtx->flagBytePos             = argCtx->oputBuffPos;
    argCtx->oputBuffPos++;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSWriteBytes]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSWriteBytes
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint8,                      AUTOMATIC, CPL_APPL_DATA) argOputBuf,
      VAR(uint32,                     AUTOMATIC               ) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr;
      VAR(uint16,                     AUTOMATIC               ) locEncoding;
      VAR(Cal_ReturnType,             AUTOMATIC               ) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr   = argCtx->cfgPtr;
  locEncoding = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( (argCtx->infoBestOff >= CPL_LZSSCOMPRESS_MATCH_MIN_SIZE) &&
       (argCtx->infoBestLen >= CPL_LZSSCOMPRESS_MATCH_MIN_SIZE)
     )
  {
    /* Compress a sequence of consecutive bytes */
    if ( (argCtx->oputBuffPos + 1U) < argOputBufLen )
    {
      locEncoding =
        (uint16)( (argCtx->infoBestLen & locCfgPtr->maskLength) << locCfgPtr->shftLength) |
        (uint16)( (argCtx->infoBestOff & locCfgPtr->maskOffset)                         );

      argOputBuf[argCtx->oputBuffPos     ]  = (uint8)(locEncoding >> 8U);
      argOputBuf[argCtx->oputBuffPos + 1U]  = (uint8)(locEncoding      );

      argCtx->flagByte                     |= (uint8)( CPL_LZSSCOMPRESS_FLAG_REF <<
                                                       (7U - argCtx->stepCntr)
                                                     );

      argCtx->oputBuffPos                  += 2U;
      argCtx->iputBuffPos                  += argCtx->infoBestLen;

      (void) Cpl_LZSSHandleFlags( argCtx, argOputBuf );

      locRetVal                             = CAL_E_OK;
    }
    else
    {
      locRetVal                             = CAL_E_SMALL_BUFFER;
    }
  }
  else
  {
    /* Compress single byte. */
    if ( argCtx->oputBuffPos < argOputBufLen )
    {
      argOputBuf[argCtx->oputBuffPos]       = argIputBuf[argCtx->iputBuffPos];

      argCtx->oputBuffPos++;
      argCtx->iputBuffPos++;

      (void) Cpl_LZSSHandleFlags( argCtx, argOputBuf );

      locRetVal                             = CAL_E_OK;
    }
    else
    {
      locRetVal                             = CAL_E_SMALL_BUFFER;
    }
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZSSFindMatch]-------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZSSFindMatch
(
    P2VAR(Cpl_LZSSCompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLb,
      VAR(uint32,                     AUTOMATIC               ) argIputBufLbLen,
  P2CONST(uint8,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLa,
      VAR(uint32,                     AUTOMATIC               ) argIputBufLaLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cpl_LZSSCompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr;
      VAR(Cal_ReturnType,             AUTOMATIC               ) locRetVal;
      VAR(boolean,                    AUTOMATIC               ) locDoBreak;
      VAR(boolean,                    AUTOMATIC               ) finishedMatchLoop;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr         = argCtx->cfgPtr;
  locRetVal         = CAL_E_NOT_OK;
  locDoBreak        = FALSE;
  finishedMatchLoop = FALSE;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argCtx->sffmState == CPL_LZSSCOMPRESS_S_SFFMIDLE )
  {
    argCtx->sffmBestIdx = 0U;
    argCtx->sffmBestLen = 0U;

    argCtx->sffmState   = CPL_LZSSCOMPRESS_S_SFFMBUSY;
    argCtx->sffmTempIdx = 0U;
  }

  /* Main search loop */
  while ( (argCtx->sffmState   == CPL_LZSSCOMPRESS_S_SFFMBUSY                        ) &&
          (argCtx->sffmTempIdx <= (argIputBufLbLen - CPL_LZSSCOMPRESS_MATCH_MIN_SIZE)) &&
          (finishedMatchLoop   == FALSE                                              )
        )
  {
    /* Search for 3 element minimum match.
     */
    if ( (argIputBufLb[argCtx->sffmTempIdx+0] == argIputBufLa[0]) &&
         (argIputBufLb[argCtx->sffmTempIdx+1] == argIputBufLa[1]) &&
         (argIputBufLb[argCtx->sffmTempIdx+2] == argIputBufLa[2])
       )
    {
      argCtx->sffmTempLen = CPL_LZSSCOMPRESS_MATCH_MIN_SIZE;

      /* Search for maybe longer match.
       */
      while ( ((argCtx->sffmTempIdx + argCtx->sffmTempLen) < argIputBufLbLen                 ) &&
              (argCtx->sffmTempLen                         < argIputBufLaLen                 ) &&
              (argCtx->sffmBestLen                         < argIputBufLbLen                 ) &&
              (argCtx->sffmBestLen                         < argIputBufLaLen                 ) &&
              (argCtx->sffmBestLen                         < locCfgPtr->sizeBufLookAhead     ) &&
              (argIputBufLb[argCtx->sffmTempIdx + argCtx->sffmTempLen] ==
                                                            argIputBufLa[argCtx->sffmTempLen])
            )
      {
        argCtx->sffmTempLen++;
      }

      argCtx->sffmBestIdx  = (argCtx->sffmTempLen > argCtx->sffmBestLen)
                           ?  argCtx->sffmTempIdx
                           :  argCtx->sffmBestIdx;

      argCtx->sffmBestLen  = (argCtx->sffmTempLen > argCtx->sffmBestLen)
                           ?  argCtx->sffmTempLen
                           :  argCtx->sffmBestLen;
    }

    argCtx->sffmTempIdx++;
    argCtx->loopCntr++;

    if ( (argCtx->sffmBestLen                                 >= argIputBufLbLen            ) ||
         (argCtx->sffmBestLen                                 >= argIputBufLaLen            ) ||
         ((argIputBufLbLen - CPL_LZSSCOMPRESS_MATCH_MIN_SIZE) <  argCtx->sffmTempIdx        )
       )
    {
      argCtx->sffmState = CPL_LZSSCOMPRESS_S_SFFMIDLE;
      locDoBreak = TRUE;
    }

    /* Interrupt */
    if ( (argCtx->loopCntr % locCfgPtr->iterBeforeInterruption) == 0U )
    {
      locDoBreak = TRUE;
    }

    if (locDoBreak != FALSE)
    {
      locDoBreak        = FALSE;
      finishedMatchLoop = TRUE;
    }
  }

  if ( argCtx->sffmState == CPL_LZSSCOMPRESS_S_SFFMBUSY )
  {
    locRetVal = CAL_E_BUSY;
  }
  else
  {
    argCtx->sffmState = CPL_LZSSCOMPRESS_S_SFFMIDLE;
    locRetVal         = CAL_E_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/

#else /* #if (CPL_LZSSCOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_LzssCompress_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_LZSSCOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
