/** \file        Cpl_RLECompress.c
 **
 ** \brief       Cpl RLE compression interface.
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

/* !LINKSTO EB_CPL_0801_021, 1
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

/* !LINKSTO EB_CPL_0801_023, 1
 */
#include <Cal_Types.h>
#include <Cal_Compress.h>

#include <Cpl_RLECompress_Cfg.h>
#include <Cpl_RLECompress.h>



#if (CPL_RLECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

#if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)

#define  CPL_RLECOMPRESS_8BIT_CNTR_HI     0x00FFU  /* 255U */
#define  CPL_RLECOMPRESS_8BIT_CNTR_POS    0x0000U  /*   0U */
#define  CPL_RLECOMPRESS_8BIT_VALU_POS    0x0001U  /*   1U */
#define  CPL_RLECOMPRESS_8BIT_RUNLEN      0x0002U  /*   2U */

#endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */



#if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)

#define  CPL_RLECOMPRESS_CTRLBIT_CNTR_LO    0x007FU  /*   127U */
#define  CPL_RLECOMPRESS_CTRLBIT_CNTR_HI    0x7FFFU  /* 32767U */
#define  CPL_RLECOMPRESS_CTRLBIT_FLAGPOS    0x0080U  /*   128U */

#define  CPL_RLECOMPRESS_CTRLBIT_V1_CP      0x0000U  /*     0U */
#define  CPL_RLECOMPRESS_CTRLBIT_V1_VP      0x0001U  /*     1U */
#define  CPL_RLECOMPRESS_CTRLBIT_V1_RUNLEN  0x0002U  /*     2U */

#define  CPL_RLECOMPRESS_CTRLBIT_V2_CPH     0x0000U  /*     0U */
#define  CPL_RLECOMPRESS_CTRLBIT_V2_CPL     0x0001U  /*     1U */
#define  CPL_RLECOMPRESS_CTRLBIT_V2_VP      0x0002U  /*     2U */
#define  CPL_RLECOMPRESS_CTRLBIT_V2_RUNLEN  0x0003U  /*     3U */

#endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the internal states of the RLECompress.
 **/
typedef enum
{
  CPL_RLECOMPRESS_S_IDLE,
  CPL_RLECOMPRESS_S_ILLEGAL,
  CPL_RLECOMPRESS_S_INITIALIZED
}
Cpl_RLECompressStateType;



/* Declaration of structure name to avoid circular dependencies.
 * Structure is defined below.
 */
struct Cpl_RLECompressCtxBufStruct;



/** \brief  Function pointer that holds specific run function for RLE type.
 **/
typedef P2FUNC(Cal_ReturnType, CPL_CODE, Cpl_RLECompressRunFunctionType)
(
    /* Deviation MISRAC2012-2 */
    P2VAR(struct Cpl_RLECompressCtxBufStruct, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2CONST(uint8,                              AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                             AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                              AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                             AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Function pointer that holds specific end function for RLE type.
 **/
typedef P2FUNC(Cal_ReturnType, CPL_CODE, Cpl_RLECompressEndFunctionType)
(
    /* Deviation MISRAC2012-2 */
    P2VAR(struct Cpl_RLECompressCtxBufStruct, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                              AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                             AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);



/** \brief  Structure which contains the context of the RLECompress.
 **/
/* NOTE: - if this structure is changed, the "invalid" test expression for
 *         "CplRleCompressVariant" in Cpl.xdm.m4 has to be adjusted, too
 *       - actual size is ( 2*uint32 + 1*uint8 + 4*? )= ~13 bytes
 */
struct Cpl_RLECompressCtxBufStruct
{
  /** \brief  pointer to the corresponding RLE compression primitive configuration
   **/
  P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) cfgPtr;

  /** \brief  the internal state machine state
   **/
      Cpl_RLECompressStateType                                 State;

  /** \brief  specific run function for type of RLE
   **/
      Cpl_RLECompressRunFunctionType                                   Cpl_RLERunFunction;

  /** \brief  specific end function for type of RLE
   **/
      Cpl_RLECompressEndFunctionType                                   Cpl_RLEEndFunction;

  /** \brief  the current value
   **/
      uint8                                                    curValu;

  /** \brief  the value counter
   **/
      uint32                                                   curCntr;

  /** \brief  flag for RLECompress process start up indication
   **/
      boolean                                                  flgBeg;
};



/** \brief  Type of structure which contains the context of the RLECompress.
 **/
typedef struct Cpl_RLECompressCtxBufStruct Cpl_RLECompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/** \brief  Initialize RLE compression computation context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
 ** \param[in]      argCfg              Pointer to RLECompress module configuration which has to
 **                                     be used during the RLE compression computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK                  Request successful.
 ** \retval   CAL_E_NOT_OK              Request failed.
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressBeg
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
);

/** \brief  Execute RLE compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete RLE compression computation and reset parts of the context.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressEnd
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);



#if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)

/** \brief  Execute specific RLE 8Bit compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete specific RLE 8Bit compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITEnd
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Write RLE 8Bit compressed data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITWrite
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

#endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */



#if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)

/** \brief  Execute specific RLE CtrlBit compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Complete specific RLE CtrlBit compression computation.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITEnd
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

/** \brief  Write RLE CtrlBit compressed data into output buffer.
 **
 ** \param[in,out]  argCtx              Holds a pointer to the buffer in which the context of the
 **                                     service that calls the RLE compression is stored.
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
 **/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITWrite
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
);

#endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressStart]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressStart
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_031, 1
   */
  if ( (sizeof(Cal_CompressCtxBufType) >= sizeof(Cpl_RLECompressCtxBufType)) &&
       (locCtxPtr                      != NULL_PTR                         ) &&
       (locCfgPtr                      != NULL_PTR                         )
     )
  {
    locRetVal = Cpl_RLECompressBeg( locCtxPtr, locCfgPtr );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressUpdate]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressUpdate
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

  CONSTP2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_036, 1
   */
  if ( (locCtxPtr        != NULL_PTR                     ) &&
       (locCtxPtr->State == CPL_RLECOMPRESS_S_INITIALIZED) &&
       (locCfgPtr        != NULL_PTR                     ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr            ) &&
       (iputBuf          != NULL_PTR                     ) &&
       (iputBufLen       != NULL_PTR                     ) &&
       (oputBuf          != NULL_PTR                     ) &&
       (oputBufLen       != NULL_PTR                     )
     )
  {
    locRetVal = Cpl_RLECompressRun( locCtxPtr, iputBuf, iputBufLen, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_037, 1
   */
  if ( (locRetVal        != CAL_E_OK                     ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER           ) &&
       (locCtxPtr        != NULL_PTR                     ) &&
       (locCfgPtr        != NULL_PTR                     ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr            )
     )
  {
    (void) Cpl_RLECompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressFinish]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressFinish
(
  P2CONST(void,                   AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                  AUTOMATIC, CPL_APPL_DATA) oputBuf,
    P2VAR(uint32,                 AUTOMATIC, CPL_APPL_DATA) oputBufLen
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLenDummy;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locLenDummy = 0U;
  locRetVal   = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* !LINKSTO EB_CPL_0804_041, 1
   */
  if ( ( locCtxPtr        != NULL_PTR              ) &&
       ( locCtxPtr->State != CPL_RLECOMPRESS_S_IDLE) &&
       ( locCfgPtr        != NULL_PTR              ) &&
       ( locCfgPtr        == locCtxPtr->cfgPtr     ) &&
       ( oputBuf          != NULL_PTR              ) &&
       ( oputBufLen       != NULL_PTR              )
     )
  {
    locRetVal = Cpl_RLECompressEnd( locCtxPtr, oputBuf, oputBufLen );
  }

  /* !LINKSTO EB_CPL_0804_042, 1
   */
  if ( (locRetVal        != CAL_E_OK               ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER     ) &&
       (locCtxPtr        != NULL_PTR               ) &&
       (locCfgPtr        != NULL_PTR               ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr      )
     )
  {
    (void) Cpl_RLECompressEnd( locCtxPtr, NULL_PTR, &locLenDummy );
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
/*----[Cpl_RLECompressBeg]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressBeg
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(Cpl_RLECompressConfigType, AUTOMATIC, CPL_APPL_DATA) argCfg
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  argCtx->cfgPtr  = argCfg;
  argCtx->State   = CPL_RLECOMPRESS_S_INITIALIZED;

  switch ( argCfg->Variant )
  {
    #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)
      case CPL_RLE_VARIANT_8BIT:
        argCtx->Cpl_RLERunFunction = &Cpl_RLECompressType8BITRun;
        argCtx->Cpl_RLEEndFunction = &Cpl_RLECompressType8BITEnd;
        locRetVal                  = CAL_E_OK;
      break;
    #endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */

    #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)
      case CPL_RLE_VARIANT_CTRLBIT:
        argCtx->Cpl_RLERunFunction = &Cpl_RLECompressTypeCTRLBITRun;
        argCtx->Cpl_RLEEndFunction = &Cpl_RLECompressTypeCTRLBITEnd;
        locRetVal                  = CAL_E_OK;
      break;
    #endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

    default:
      argCtx->Cpl_RLERunFunction = NULL_PTR;
      argCtx->Cpl_RLEEndFunction = NULL_PTR;
    break;
  }

  argCtx->curValu = 0U;
  argCtx->curCntr = 0U;
  argCtx->flgBeg  = TRUE;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressRun]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
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
/*----[Cpl_RLECompressEnd]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressEnd
(
  P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
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

  argCtx->State = CPL_RLECOMPRESS_S_IDLE;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressType8BITRun]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
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

  if ( argCtx->flgBeg == TRUE )
  {
    argCtx->curValu = argIputBuf[locIputBufPos];
    argCtx->curCntr = 1U;
    argCtx->flgBeg  = FALSE;

    locIputBufPos++;
  }

  while ( locIputBufPos < locIputBufLen )
  {
    if ( (argCtx->curValu != argIputBuf[locIputBufPos]   ) ||
         (argCtx->curCntr >= CPL_RLECOMPRESS_8BIT_CNTR_HI)
       )
    {
      locRetVal        = Cpl_RLECompressType8BITWrite
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
      locOputBufLen    = *argOputBufLen - locOputBufLen;

      argCtx->curValu  = argIputBuf[locIputBufPos];
      argCtx->curCntr  = 1U;
    }
    else
    {
      argCtx->curCntr++;
    }

    locIputBufPos++;
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

#endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressType8BITEnd]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITEnd
(
  P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = Cpl_RLECompressType8BITWrite
              (
                argCtx,
                argOputBuf,
                argOputBufLen
              );

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressType8BITWrite]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressType8BITWrite
(
  P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locOputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argCtx->curCntr != 0U )
  {
    if ( CPL_RLECOMPRESS_8BIT_VALU_POS < locOputBufLen )
    {
      argOputBuf[CPL_RLECOMPRESS_8BIT_CNTR_POS]  = (uint8)(argCtx->curCntr);
      argOputBuf[CPL_RLECOMPRESS_8BIT_VALU_POS]  = (uint8)(argCtx->curValu);

      locOputBufPos                             += CPL_RLECOMPRESS_8BIT_RUNLEN;

      locRetVal                                  = CAL_E_OK;
    }
    else
    {
      locRetVal = CAL_E_SMALL_BUFFER;
    }
  }
  else
  {
    locRetVal = CAL_E_OK;
  }

  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLECOMPRESS_VARIANT_8BIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressTypeCTRLBITRun]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITRun
(
    P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                     AUTOMATIC, CPL_APPL_DATA) argIputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argIputBufLen,
    P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
    P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
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

  if ( argCtx->flgBeg == TRUE )
  {
    argCtx->curValu = argIputBuf[locIputBufPos];
    argCtx->curCntr = 1U;
    argCtx->flgBeg  = FALSE;

    locIputBufPos++;
  }

  while ( locIputBufPos < locIputBufLen )
  {
    if ( (argCtx->curValu != argIputBuf[locIputBufPos]      ) ||
         (argCtx->curCntr >= CPL_RLECOMPRESS_CTRLBIT_CNTR_HI)
       )
    {
      locRetVal        = Cpl_RLECompressTypeCTRLBITWrite
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
      locOputBufLen    = *argOputBufLen - locOputBufLen;

      argCtx->curValu  = argIputBuf[locIputBufPos];
      argCtx->curCntr  = 1U;
    }
    else
    {
      argCtx->curCntr++;
    }

    locIputBufPos++;
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

#endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressTypeCTRLBITEnd]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITEnd
(
  P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = Cpl_RLECompressTypeCTRLBITWrite
              (
                argCtx,
                argOputBuf,
                argOputBufLen
              );

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_RLECompressTypeCTRLBITWrite]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON)

STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_RLECompressTypeCTRLBITWrite
(
  P2VAR(Cpl_RLECompressCtxBufType, AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                     AUTOMATIC, CPL_APPL_DATA) argOputBuf,
  P2VAR(uint32,                    AUTOMATIC, CPL_APPL_DATA) argOputBufLen
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locOputBufPos;
  VAR(uint32,         AUTOMATIC) locOputBufLen;
  VAR(Cal_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locOputBufPos =  0U;
  locOputBufLen = *argOputBufLen;
  locRetVal     =  CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( argCtx->curCntr != 0U )
  {
    if ( argCtx->curCntr <= CPL_RLECOMPRESS_CTRLBIT_CNTR_LO )
    {
      if ( CPL_RLECOMPRESS_CTRLBIT_V1_VP < locOputBufLen )
      {
        argOputBuf[CPL_RLECOMPRESS_CTRLBIT_V1_CP]  = (uint8)(argCtx->curCntr);
        argOputBuf[CPL_RLECOMPRESS_CTRLBIT_V1_VP]  = (uint8)(argCtx->curValu);

        locOputBufPos                             += CPL_RLECOMPRESS_CTRLBIT_V1_RUNLEN;

        locRetVal                                  = CAL_E_OK;
      }
      else
      {
        locRetVal = CAL_E_SMALL_BUFFER;
      }
    }
    else
    {
      if ( CPL_RLECOMPRESS_CTRLBIT_V2_VP < locOputBufLen )
      {
        argOputBuf[CPL_RLECOMPRESS_CTRLBIT_V2_CPH]  = (uint8)(argCtx->curCntr >> 8U) |
                                                                    CPL_RLECOMPRESS_CTRLBIT_FLAGPOS;
        argOputBuf[CPL_RLECOMPRESS_CTRLBIT_V2_CPL]  = (uint8)(argCtx->curCntr);
        argOputBuf[CPL_RLECOMPRESS_CTRLBIT_V2_VP ]  = (uint8)(argCtx->curValu);

        locOputBufPos                              += CPL_RLECOMPRESS_CTRLBIT_V2_RUNLEN;

        locRetVal                                   = CAL_E_OK;
      }
      else
      {
        locRetVal = CAL_E_SMALL_BUFFER;
      }
    }
  }
  else
  {
    locRetVal = CAL_E_OK;
  }

  *argOputBufLen = locOputBufPos;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

#endif /* #if (CPL_RLECOMPRESS_VARIANT_CTRLBIT == STD_ON) */

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/

#else /* #if (CPL_RLECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_RleCompress_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_RLECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
