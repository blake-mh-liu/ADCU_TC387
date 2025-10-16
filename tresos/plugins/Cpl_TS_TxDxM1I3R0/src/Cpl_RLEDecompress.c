/** \file        Cpl_RLEDecompress.c
 **
 ** \brief       Cpl RLE decompression interface.
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

/* !LINKSTO EB_CPL_0801_031, 1
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
 *  MISRAC2012-2) Deviated Rule: 20.7 (required)
 *   "Expressions resulting from the expansion of macro parameters shall be
 *    enclosed in parentheses."
 *
 *    Reason:
 *    The AUTOSAR compiler abstraction requires these definitions in this way
 *    and the arguments cannot be enclosed in parentheses due to C syntax.
 */


/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_033, 1
 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_RLEDecompress_Cfg.h>
#include <Cpl_RLEDecompress.h>



#if (CPL_RLEDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

#if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)

#define  CPL_RLEDECOMPRESS_CTRLBIT_FLAGPOS  0x0080U  /*   128U */
#define  CPL_RLEDECOMPRESS_CTRLBIT_CNTR_LO  0x007FU  /*   127U */

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*==================[type definitions]============================================================*/


/** \brief  Enumeration of the internal states of the RLEDecompress.
 **/
typedef enum
{
  CPL_RLEDECOMPRESS_S_IDLE,
  CPL_RLEDECOMPRESS_S_ILLEGAL,
  CPL_RLEDECOMPRESS_S_INITIALIZED
}
Cpl_RLEDecompressStateType;



/* Declaration of structure name to avoid circular dependencies.
 * Structure is defined below.
 */
struct Cpl_RLEDecompressCtxBufStruct;



/** \brief  Function pointer that holds specific run function for RLE type.
 **/
typedef P2FUNC(Cal_ReturnType, CPL_CODE, Cpl_RLEDecompressRunFunctionType)
(
    /* Deviation MISRAC2012-2 */
    P2VAR(struct Cpl_RLEDecompressCtxBufStruct, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2CONST(uint8,                                AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                               AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                                AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                               AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Function pointer that holds specific end function for RLE type.
 **/
typedef P2FUNC(Cal_ReturnType, CPL_CODE, Cpl_RLEDecompressEndFunctionType)
(
    /* Deviation MISRAC2012-2 */
    P2VAR(struct Cpl_RLEDecompressCtxBufStruct, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                                AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                               AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);



/** \brief  Structure which contains the context of the RLEDecompress.
 **/
/* NOTE: - if this structure is changed, the "invalid" test expression for
 *         "CplRleDecompressVariant" in Cpl.xdm.m4 have to be adjusted, too
 *       - actual size is ( 2*uint32 + 1*uint8 + 5*? ) = ~14 bytes
 */
struct Cpl_RLEDecompressCtxBufStruct
{
  /** \brief  pointer to the corresponding RLE decompression primitive configuration
   **/
  P2CONST(Cpl_RLEDecompressConfigType, TYPEDEF, CPL_APPL_DATA) cfgPtr;

  /** \brief  the internal state machine state
   **/
          Cpl_RLEDecompressStateType                           State;

  /** \brief  specific run function for type of RLE
   **/
          Cpl_RLEDecompressRunFunctionType                               Cpl_RLERunFunction;

  /** \brief  specific end function for type of RLE
   **/
          Cpl_RLEDecompressEndFunctionType                               Cpl_RLEEndFunction;

  /** \brief  the current value
   **/
          uint8                                                curValu;

  /** \brief  the value counter
   **/
          uint16                                               curCntr;

  /** \brief  the counter of bytes of a run
   **/
          uint8                                                bytCntr;

  /** \brief  were all bytes of the current run read successfully?
   **/
          boolean                                              encIncomplete;
};



/** \brief  Type of structure which contains the context of the RLEDecompress.
 **/
typedef struct Cpl_RLEDecompressCtxBufStruct Cpl_RLEDecompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/** \brief  Initialize RLE decompression computation context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
 ** \param[in]      argCfg              Pointer to RLEDecompress module configuration which has to
 **                                     be used during the RLE decompression computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressBeg
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
);

/** \brief  Execute RLE decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete RLE decompression computation and reset parts of the context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressEnd
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);



#if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON)

/** \brief  Execute specific RLE 8Bit decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressType8BITRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete specific RLE 8Bit decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressType8BITEnd
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON) */



#if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)

/** \brief  Execute specific RLE CtrlBit decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressTypeCTRLBITRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete specific RLE CtrlBit decompression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressTypeCTRLBITEnd
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON) */



#if ( (CPL_RLEDECOMPRESS_VARIANT_8BIT    == STD_ON) || \
      (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)    \
    )

/** \brief  Write RLE decompressed data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE decompression is stored.
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
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLETypeCMMNWrite
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

#endif /* #if ( (CPL_RLEDECOMPRESS_VARIANT_8BIT    == STD_ON) || \
                (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)    \
              )                                                  */

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_046, 1
   */
  if ( (sizeof(Cal_DecompressCtxBufType) >= sizeof(Cpl_RLEDecompressCtxBufType)) &&
       (locCtxPtr                        != NULL_PTR                           ) &&
       (locCfgPtr                        != NULL_PTR                           )
     )
  {
    locRetVal = Cpl_RLEDecompressBeg( locCtxPtr, locCfgPtr );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressUpdate
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

  CONSTP2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_051, 1
   */
  if ( (locCtxPtr        != NULL_PTR                       ) &&
       (locCtxPtr->State == CPL_RLEDECOMPRESS_S_INITIALIZED) &&
       (locCfgPtr        != NULL_PTR                       ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr              ) &&
       (iputBuf          != NULL_PTR                       ) &&
       (iputBufLen       != NULL_PTR                       ) &&
       (oputBuf          != NULL_PTR                       ) &&
       (oputBufLen       != NULL_PTR                       )
     )
  {
    locRetVal = Cpl_RLEDecompressRun( locCtxPtr, iputBuf, iputBufLen, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_052, 1
   */
  if ( (locRetVal        != CAL_E_OK                       ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER             ) &&
       (locCtxPtr        != NULL_PTR                       ) &&
       (locCfgPtr        != NULL_PTR                       ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr              )
     )
  {
    (void) Cpl_RLEDecompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_056, 1
   */
  if ( ( locCtxPtr        != NULL_PTR                ) &&
       ( locCtxPtr->State != CPL_RLEDECOMPRESS_S_IDLE) &&
       ( locCfgPtr        != NULL_PTR                ) &&
       ( locCfgPtr        == locCtxPtr->cfgPtr       ) &&
       ( oputBuf          != NULL_PTR                ) &&
       ( oputBufLen       != NULL_PTR                )
     )
  {
    locRetVal = Cpl_RLEDecompressEnd( locCtxPtr, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_057, 1
   */
  if ( (locRetVal        != CAL_E_OK                 ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER       ) &&
       (locCtxPtr        != NULL_PTR                 ) &&
       (locCfgPtr        != NULL_PTR                 ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr        )
     )
  {
    (void) Cpl_RLEDecompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
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
/*----[Cpl_RLEDecompressBeg]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressBeg
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_RLEDecompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  argCtx->cfgPtr  = argCfg;
  argCtx->State   = CPL_RLEDECOMPRESS_S_INITIALIZED;

  switch ( argCfg->Variant )
  {
    #if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON)
      case CPL_RLE_VARIANT_8BIT:
        argCtx->Cpl_RLERunFunction = &Cpl_RLEDecompressType8BITRun;
        argCtx->Cpl_RLEEndFunction = &Cpl_RLEDecompressType8BITEnd;
        locRetVal                  = CAL_E_OK;
      break;
    #endif /* #if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON) */

    #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)
      case CPL_RLE_VARIANT_CTRLBIT:
        argCtx->Cpl_RLERunFunction = &Cpl_RLEDecompressTypeCTRLBITRun;
        argCtx->Cpl_RLEEndFunction = &Cpl_RLEDecompressTypeCTRLBITEnd;
        locRetVal                  = CAL_E_OK;
      break;
    #endif /* #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

    default:
      argCtx->Cpl_RLERunFunction = NULL_PTR;
      argCtx->Cpl_RLEEndFunction = NULL_PTR;
    break;
  }

  argCtx->curValu       = 0U;
  argCtx->curCntr       = 0U;

  argCtx->bytCntr       = 0U;
  argCtx->encIncomplete = FALSE;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressRun]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( *argIputBufLen == 0U )
  {
    locRetVal = CAL_E_OK;
  }
  else
  {
    if ( argCtx->Cpl_RLERunFunction != NULL_PTR )
    {
      locRetVal = argCtx->Cpl_RLERunFunction
                  (
                    argCtx,
                    argIputBuf,
                    argIputBufLen,
                    argOputBuf,
                    argOputBufLen
                  );
    }
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressEnd]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressEnd
(
  P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argOputBuf != NULL_PTR )
  {
    if ( argCtx->Cpl_RLEEndFunction != NULL_PTR )
    {
      locRetVal = argCtx->Cpl_RLEEndFunction
                  (
                    argCtx,
                    argOputBuf,
                    argOputBufLen
                  );
    }
  }
  else
  {
    locRetVal = CAL_E_OK;
  }

  argCtx->State = CPL_RLEDECOMPRESS_S_IDLE;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressType8BITRun]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressType8BITRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locIputBufPos;
  VAR(uint32,         AUTOMATIC) locIputBufLen;
  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locIputBufPos =  0U;
  locIputBufLen = *argIputBufLen;
  locOputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  while ( locIputBufPos < locIputBufLen )
  {
    if ( (locIputBufPos   <  locIputBufLen) &&
         (argCtx->bytCntr == 0U           )
       )
    {
      argCtx->curCntr       = argIputBuf[locIputBufPos];
      argCtx->encIncomplete = TRUE;
      argCtx->bytCntr++;
      locIputBufPos++;
    }

    if ( (locIputBufPos   <  locIputBufLen) &&
         (argCtx->bytCntr == 1U           )
       )
    {
      argCtx->curValu = argIputBuf[locIputBufPos];
      argCtx->encIncomplete = FALSE;
      argCtx->bytCntr++;
      locIputBufPos++;
    }

    if ( argCtx->encIncomplete == FALSE )
    {
      locRetVal        = Cpl_RLETypeCMMNWrite
                         (
                            argCtx,
                           &argOputBuf[locOputBufPos],
                           &locOputBufLen
                         );

      if ( locRetVal != CAL_E_OK )
      {
        break;
      }

      locOputBufPos   +=  locOputBufLen;
      locOputBufLen    = *argOputBufLen - locOputBufPos;

      argCtx->bytCntr  = 0U;
    }
  }

  if ( locIputBufPos >= locIputBufLen )
  {
    locRetVal = CAL_E_OK;
  }

  *argIputBufLen = locIputBufPos;
  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressType8BITEnd]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressType8BITEnd
(
  P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = Cpl_RLETypeCMMNWrite
              (
                argCtx,
                argOputBuf,
                argOputBufLen
              );

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_8BIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressTypeCTRLBITRun]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressTypeCTRLBITRun
(
    P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                       AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locIputBufPos;
  VAR(uint32,         AUTOMATIC) locIputBufLen;
  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locIputBufPos =  0U;
  locIputBufLen = *argIputBufLen;
  locOputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  while ( locIputBufPos < locIputBufLen )
  {
    if ( (locIputBufPos   <  locIputBufLen) &&
         (argCtx->bytCntr == 0U           )
       )
    {
      argCtx->curCntr       = argIputBuf[locIputBufPos];
      argCtx->encIncomplete = TRUE;
      argCtx->bytCntr++;
      locIputBufPos++;
    }

    if ( ((argCtx->curCntr & CPL_RLEDECOMPRESS_CTRLBIT_FLAGPOS)
                                                            == 0U                               ) &&
         ( argCtx->curCntr                                  <= CPL_RLEDECOMPRESS_CTRLBIT_CNTR_LO)
       )
    {
      if ( (locIputBufPos   <  locIputBufLen) &&
           (argCtx->bytCntr == 1U           )
         )
      {
        argCtx->curValu       = argIputBuf[locIputBufPos];
        argCtx->encIncomplete = FALSE;
        argCtx->bytCntr++;
        locIputBufPos++;
      }
    }
    else
    {
      if ( (locIputBufPos   <  locIputBufLen) &&
           (argCtx->bytCntr == 1U           )
         )
      {
        argCtx->curCntr        &= CPL_RLEDECOMPRESS_CTRLBIT_CNTR_LO;
        argCtx->curCntr       <<= 8U;
        argCtx->curCntr        += argIputBuf[locIputBufPos];
        argCtx->encIncomplete   = TRUE;
        argCtx->bytCntr++;
        locIputBufPos++;
      }

      if ( (locIputBufPos   <  locIputBufLen) &&
           (argCtx->bytCntr == 2U           )
         )
      {
        argCtx->curValu       = argIputBuf[locIputBufPos];
        argCtx->encIncomplete = FALSE;
        argCtx->bytCntr++;
        locIputBufPos++;
      }
    }

    if ( argCtx->encIncomplete == FALSE )
    {
      locRetVal        = Cpl_RLETypeCMMNWrite
                         (
                            argCtx,
                           &argOputBuf[locOputBufPos],
                           &locOputBufLen
                         );

      if ( locRetVal != CAL_E_OK )
      {
        break;
      }

      locOputBufPos   +=  locOputBufLen;
      locOputBufLen    = *argOputBufLen - locOputBufPos;

      argCtx->bytCntr  = 0U;
    }
  }

  if ( locIputBufPos >= locIputBufLen )
  {
    locRetVal = CAL_E_OK;
  }

  *argIputBufLen = locIputBufPos;
  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLEDecompressTypeCTRLBITEnd]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLEDecompressTypeCTRLBITEnd
(
  P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = Cpl_RLETypeCMMNWrite
              (
                argCtx,
                argOputBuf,
                argOputBufLen
              );

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLETypeCMMNWrite]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if ( (CPL_RLEDECOMPRESS_VARIANT_8BIT    == STD_ON) || \
      (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)    \
    )

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLETypeCMMNWrite
(
  P2VAR(Cpl_RLEDecompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                       AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                      AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  VAR(uint16,         AUTOMATIC) locCntr;  /* to avoid pointer dereferencing in for loop */
  VAR(uint8,          AUTOMATIC) locValu;  /* to avoid pointer dereferencing in for loop */

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locOputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  locCntr       = argCtx->curCntr;         /* to avoid pointer dereferencing in for loop */
  locValu       = argCtx->curValu;         /* to avoid pointer dereferencing in for loop */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argCtx->curCntr < locOputBufLen )
  {
    if ( (argCtx->encIncomplete == FALSE) &&
         (argCtx->curCntr       != 0U   )
       )
    {
      for ( locOputBufPos = 0U; locOputBufPos < locCntr; locOputBufPos++ )
      {
        argOputBuf[locOputBufPos] = locValu;
      }

      argCtx->curCntr = 0U;
      argCtx->curValu = 0U;
    }

    locRetVal = CAL_E_OK;
  }
  else
  {
    locRetVal = CAL_E_SMALL_BUFFER;
  }

  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if ( (CPL_RLEDECOMPRESS_VARIANT_8BIT    == STD_ON) || \
                (CPL_RLEDECOMPRESS_VARIANT_CTRLBIT == STD_ON)    \
              )                                                    */

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/

#else /* #if (CPL_RLEDECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_RleDecompress_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_RLEDECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
