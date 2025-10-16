/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_H
#define CRYPTO_XVIX_XAIX_INT_H

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.
 *
 */

/*==================[includes]====================================================================*/

#include <SchM_Crypto_xVIx_xAIx.h>       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0004,1 */

#include <Crypto_xVIx_xAIx_Int_Types.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0005,1 */
#include <Crypto_xVIx_xAIx_Int_Cfg.h>    /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0002,1 */
#include <Crypto_xVIx_xAIx_Cfg.h>        /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0006,1 */
#include <Crypto_xVIx_xAIx_Trace.h>

/* !LINKSTO Crypto.Asr.SWS_Crypto_00126,1 */
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) || (CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON))
#include <Det.h>                         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.h/0003,1 */
#endif

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32)
#error CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32 already defined
#endif
/** \brief  Converts a byte array of four bytes into a uint32 value. **/
#define CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(src) \
((uint32) (  ((uint32) ((src)[0U]) << 24U)                \
           | ((uint32) ((src)[1U]) << 16U)                \
           | ((uint32) ((src)[2U]) <<  8U)                \
           | ((uint32) ((src)[3U])       )                \
          )                                               \
)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY)
#error CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY already defined
#endif
/** \brief Converts a uint32 value into a byte array of four bytes. **/
#define CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(dst, src) \
do                                                             \
{                                                              \
  (dst)[0U] = (uint8) ((src) >> 24U);                          \
  (dst)[1U] = (uint8) ((src) >> 16U);                          \
  (dst)[2U] = (uint8) ((src) >>  8U);                          \
  (dst)[3U] = (uint8) ((src)       );                          \
}                                                              \
while (0U)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SHL32,2 */
#if (defined CRYPTO_XVIX_XAIX_SHL32)
#error CRYPTO_XVIX_XAIX_SHL32 is already defined
#endif
/** \brief  This macro performs shifting of a uint32 type v by w bits to the left. **/
#define CRYPTO_XVIX_XAIX_SHL32(v, w) (((uint32)(w) < 32U) ? ((uint32) (v) << (w)) : ((uint32) 0U))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SHR32,2 */
#if (defined CRYPTO_XVIX_XAIX_SHR32)
#error CRYPTO_XVIX_XAIX_SHR32 is already defined
#endif
/** \brief  This macro performs shifting of a uint32 type v by w bits to the right. **/
#define CRYPTO_XVIX_XAIX_SHR32(v, w) (((uint32)(w) < 32U) ? ((uint32) (v) >> (w)) : ((uint32) 0U))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ROL32,1 */
#if (defined CRYPTO_XVIX_XAIX_ROL32)
#error CRYPTO_XVIX_XAIX_ROL32 is already defined
#endif
/** \brief  Rotate a 32-bit word v by a given amount of w bits to the left **/
#define CRYPTO_XVIX_XAIX_ROL32(v, w) ((((uint32) (v)) << ((w) % 32U)) | (((uint32) (v)) >> (32U - ((w) % 32U))))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ROR32,1 */
#if (defined CRYPTO_XVIX_XAIX_ROR32)
#error CRYPTO_XVIX_XAIX_ROR32 is already defined
#endif
/** \brief  Rotate a 32-bit word v by a given amount of w bits to the right **/
#define CRYPTO_XVIX_XAIX_ROR32(v, w) ((((uint32) (v)) >> ((w) % 32U)) | (((uint32) (v)) << (32U - ((w) % 32U))))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_NOT32,1 */
#if (defined CRYPTO_XVIX_XAIX_NOT32)
#error CRYPTO_XVIX_XAIX_NOT32 is already defined
#endif
/** \brief  This macro performs a logical NOT operation of a given uint32 variable. **/
#define CRYPTO_XVIX_XAIX_NOT32(a) (~((uint32) (a)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_AND32,1 */
#if (defined CRYPTO_XVIX_XAIX_AND32)
#error CRYPTO_XVIX_XAIX_AND32 is already defined
#endif
/** \brief  This macro performs a logical AND operation of two uint32 variables. **/
#define CRYPTO_XVIX_XAIX_AND32(a, b) (((uint32) (a)) & ((uint32) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_OR32,1 */
#if (defined CRYPTO_XVIX_XAIX_OR32)
#error CRYPTO_XVIX_XAIX_OR32 is already defined
#endif
/** \brief  This macro performs a logical OR operation of two uint32 variables. **/
#define CRYPTO_XVIX_XAIX_OR32(a, b) (((uint32) (a)) | ((uint32) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_XOR32,1 */
#if (defined CRYPTO_XVIX_XAIX_XOR32)
#error CRYPTO_XVIX_XAIX_XOR32 is already defined
#endif
/** \brief  This macro performs a logical XOR operation of two uint32 variables. **/
#define CRYPTO_XVIX_XAIX_XOR32(a, b) (((uint32) (a)) ^ ((uint32) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ADD32,1 */
#if (defined CRYPTO_XVIX_XAIX_ADD32)
#error CRYPTO_XVIX_XAIX_ADD32 is already defined
#endif
/** \brief  This macro performs the addition of two uint32 variables. **/
#define CRYPTO_XVIX_XAIX_ADD32(a, b) (((uint32) (a)) + ((uint32) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SHL64,2 */
#if (defined CRYPTO_XVIX_XAIX_SHL64)
#error CRYPTO_XVIX_XAIX_SHL64 is already defined
#endif
/** \brief  This macro performs shifting of a uint64 type v by w bits to the left. **/
#define CRYPTO_XVIX_XAIX_SHL64(v, w) (((uint64)(w) < 64U) ? ((uint64) (v) << (w)) : ((uint64) 0U))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SHR64,2 */
#if (defined CRYPTO_XVIX_XAIX_SHR64)
#error CRYPTO_XVIX_XAIX_SHR64 is already defined
#endif
/** \brief  This macro performs shifting of a uint64 type v by w bits to the right. **/
#define CRYPTO_XVIX_XAIX_SHR64(v, w) (((uint64)(w) < 64U) ? ((uint64) (v) >> (w)) : ((uint64) 0U))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ROL64,1 */
#if (defined CRYPTO_XVIX_XAIX_ROL64)
#error CRYPTO_XVIX_XAIX_ROL64 is already defined
#endif
/** \brief  Rotate a 64-bit type v by a given amount of w bits to the left **/
#define CRYPTO_XVIX_XAIX_ROL64(v, w) ((((uint64) (v)) << ((w) % 64U)) | (((uint64) (v)) >> (64U - ((w) % 64U))))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ROR64,1 */
#if (defined CRYPTO_XVIX_XAIX_ROR64)
#error CRYPTO_XVIX_XAIX_ROR64 is already defined
#endif
/** \brief  Rotate a 64-bit type v by a given amount of w bits to the right **/
#define CRYPTO_XVIX_XAIX_ROR64(v, w) ((((uint64) (v)) >> ((w) % 64U)) | (((uint64) (v)) << (64U - ((w) % 64U))))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_NOT64,1 */
#if (defined CRYPTO_XVIX_XAIX_NOT64)
#error CRYPTO_XVIX_XAIX_NOT64 is already defined
#endif
/** \brief  This macro performs a logical NOT operation of a given uint64 variable. **/
#define CRYPTO_XVIX_XAIX_NOT64(a) (~((uint64) (a)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_AND64,1 */
#if (defined CRYPTO_XVIX_XAIX_AND64)
#error CRYPTO_XVIX_XAIX_AND64 is already defined
#endif
/** \brief  This macro performs a logical AND operation of two uint64 variables. **/
#define CRYPTO_XVIX_XAIX_AND64(a, b) (((uint64) (a)) & ((uint64) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_OR64,1 */
#if (defined CRYPTO_XVIX_XAIX_OR64)
#error CRYPTO_XVIX_XAIX_OR64 is already defined
#endif
/** \brief  This macro performs a logical OR operation of two uint64 variables. **/
#define CRYPTO_XVIX_XAIX_OR64(a, b) (((uint64) (a)) | ((uint64) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_XOR64,1 */
#if (defined CRYPTO_XVIX_XAIX_XOR64)
#error CRYPTO_XVIX_XAIX_XOR64 is already defined
#endif
/** \brief  This macro performs a logical XOR operation of two uint64 variables. **/
#define CRYPTO_XVIX_XAIX_XOR64(a, b) (((uint64) (a)) ^ ((uint64) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_ADD64,1 */
#if (defined CRYPTO_XVIX_XAIX_ADD64)
#error CRYPTO_XVIX_XAIX_ADD64 is already defined
#endif
/** \brief  This macro performs the addition of two uint64 variables. **/
#define CRYPTO_XVIX_XAIX_ADD64(a, b) (((uint64) (a)) + ((uint64) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_MUL64,1 */
#if (defined CRYPTO_XVIX_XAIX_MUL64)
#error CRYPTO_XVIX_XAIX_MUL64 is already defined
#endif
/** \brief  This macro performs the multiplication of two uint64 variables. **/
#define CRYPTO_XVIX_XAIX_MUL64(a, b) (((uint64) (a)) * ((uint64) (b)))

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE,1 */
#if (defined CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE)
#error CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE is already defined
#endif
/** \brief  Conversion of 8 x 8 bit values to a 64 bit word in little endian format. **/
#define CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE(a) \
(  ((uint64) ((a)[0U])       )                        \
 | ((uint64) ((a)[1U]) <<  8U)                        \
 | ((uint64) ((a)[2U]) << 16U)                        \
 | ((uint64) ((a)[3U]) << 24U)                        \
 | ((uint64) ((a)[4U]) << 32U)                        \
 | ((uint64) ((a)[5U]) << 40U)                        \
 | ((uint64) ((a)[6U]) << 48U)                        \
 | ((uint64) ((a)[7U]) << 56U)                        \
)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE,1 */
#if (defined CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE)
#error CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE is already defined
#endif
/** \brief  Conversion of 8 x 8 bit values to a 64 bit word in big endian format. **/
#define CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(a) \
(  ((uint64) ((a)[0U]) << 56U)                        \
 | ((uint64) ((a)[1U]) << 48U)                        \
 | ((uint64) ((a)[2U]) << 40U)                        \
 | ((uint64) ((a)[3U]) << 32U)                        \
 | ((uint64) ((a)[4U]) << 24U)                        \
 | ((uint64) ((a)[5U]) << 16U)                        \
 | ((uint64) ((a)[6U]) <<  8U)                        \
 | ((uint64) ((a)[7U])       )                        \
)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_LE,1 */
#if (defined CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_LE)
#error CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_LE is already defined
#endif
/** \brief  Conversion of a 64 bit word in little endian format to 8 x 8 bit values. **/
#define CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_LE(a, b) \
do                                                       \
{                                                        \
  (b)[0U] = (uint8) ((a)       );                        \
  (b)[1U] = (uint8) ((a) >>  8U);                        \
  (b)[2U] = (uint8) ((a) >> 16U);                        \
  (b)[3U] = (uint8) ((a) >> 24U);                        \
  (b)[4U] = (uint8) ((a) >> 32U);                        \
  (b)[5U] = (uint8) ((a) >> 40U);                        \
  (b)[6U] = (uint8) ((a) >> 48U);                        \
  (b)[7U] = (uint8) ((a) >> 56U);                        \
}                                                        \
while (0U)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE,1 */
#if (defined CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE)
#error CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE is already defined
#endif
/** \brief  Conversion of a 64 bit word in big endian format to 8 x 8 bit values. **/
#define CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE(a, b) \
do                                                       \
{                                                        \
  (b)[0U] = (uint8) ((a) >> 56U);                        \
  (b)[1U] = (uint8) ((a) >> 48U);                        \
  (b)[2U] = (uint8) ((a) >> 40U);                        \
  (b)[3U] = (uint8) ((a) >> 32U);                        \
  (b)[4U] = (uint8) ((a) >> 24U);                        \
  (b)[5U] = (uint8) ((a) >> 16U);                        \
  (b)[6U] = (uint8) ((a) >>  8U);                        \
  (b)[7U] = (uint8) ((a)       );                        \
}                                                        \
while (0U)

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_UINT64_GET_LOW_BYTE,1 */
#if (defined CRYPTO_XVIX_XAIX_UINT64_GET_LOW_BYTE)
#error CRYPTO_XVIX_XAIX_UINT64_GET_LOW_BYTE is already defined
#endif
/** \brief  Conversion of a 64 bit word in little endian format to 8 x 8 bit values. **/
#define CRYPTO_XVIX_XAIX_UINT64_GET_LOW_BYTE(a) ((uint8) (a))

#if (defined CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE)
#error CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE is already defined
#endif
/** \brief  This macro performs the cast of a primitive's workspace to the given data type. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE,1 */
#define CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(type)  \
P2VAR(type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace \
= (P2VAR(type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) primitive->cnfg->workspace

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT is already defined
#endif
/** \brief  This macro completes the processing of a job's operation mode. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT(retval, opmode, cbktype)                 \
do                                                                             \
{                                                                              \
  workspace->smResult         = (retval);                                      \
  workspace->smOperationDone |= (opmode);                                      \
  if (E_OK == (retval))                                                        \
  {                                                                            \
    (void) Crypto_xVIx_xAIx_Procedure_NotifyCaller(job, workspace, (cbktype)); \
  }                                                                            \
}                                                                              \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_START)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_START is already defined
#endif
/** \brief  This macro completes the processing of a job's START operation mode. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_START,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_START(retval, wssize)                        \
do                                                                                 \
{                                                                                  \
  workspace->smResult         = (retval);                                          \
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;                        \
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_2,1 */                                   \
  if (   (E_OK                          == (retval)          )                     \
      && (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)                     \
     )                                                                             \
  {                                                                                \
    (void) Crypto_xVIx_xAIx_CallbackNotification_Start(workspace->paObjectId,      \
                                                       job,                        \
                                                       workspace->paPrimitive,     \
                                                       workspace->smOperationDone, \
                                                       workspace->smResult,        \
                                                       wssize                      \
                                                      );                           \
  }                                                                                \
}                                                                                  \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE is already defined
#endif
/** \brief  The macro completes the processing of a job's UPDATE operation mode. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(retval, wssize)                        \
do                                                                                  \
{                                                                                   \
  workspace->smResult         = (retval);                                           \
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_UPDATE;                        \
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_2,1 */                                    \
  if (   (E_OK                          == (retval)          )                      \
      && (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)                      \
     )                                                                              \
  {                                                                                 \
    (void) Crypto_xVIx_xAIx_CallbackNotification_Update(workspace->paObjectId,      \
                                                        job,                        \
                                                        workspace->paPrimitive,     \
                                                        workspace->smOperationDone, \
                                                        workspace->smResult,        \
                                                        wssize                      \
                                                        );                          \
  }                                                                                 \
}                                                                                   \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH is already defined
#endif
/** \brief  This macro completes the processing of a job's FINISH operation mode. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(retval, wssize)                          \
do                                                                                    \
{                                                                                     \
  workspace->smResult         = (retval);                                             \
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;                          \
  if (E_OK == (retval))                                                               \
  {                                                                                   \
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_2,1 */                                    \
    if (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)                          \
    {                                                                                 \
      (void) Crypto_xVIx_xAIx_CallbackNotification_Finish(workspace->paObjectId,      \
                                                          job,                        \
                                                          workspace->paPrimitive,     \
                                                          workspace->smOperationDone, \
                                                          workspace->smResult,        \
                                                          wssize                      \
                                                         );                           \
    }                                                                                 \
  }                                                                                   \
}                                                                                     \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL is already defined
#endif
/** \brief  This macro completes the processing of a job's SINGLECALL operation mode. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(retval, wssize)                      \
do                                                                                    \
{                                                                                     \
  workspace->smResult         = (retval);                                             \
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_SINGLECALL;                      \
  if (E_OK == (retval))                                                               \
  {                                                                                   \
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_2,1 */                                    \
    if (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)                          \
    {                                                                                 \
      (void) Crypto_xVIx_xAIx_CallbackNotification_Finish(workspace->paObjectId,      \
                                                          job,                        \
                                                          workspace->paPrimitive,     \
                                                          workspace->smOperationDone, \
                                                          workspace->smResult,        \
                                                          wssize                      \
                                                         );                           \
    }                                                                                 \
  }                                                                                   \
}                                                                                     \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL is already defined
#endif
/** \brief  This macro completes the processing of a job's cancelling. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(retval, wssize)                      \
do                                                                                \
{                                                                                 \
  if (NULL_PTR == workspace->paPrimitive)                                         \
  {                                                                               \
    workspace->paPrimitive = primitive;                                           \
  }                                                                               \
  workspace->smResult = (retval);                                                 \
  (void) Crypto_xVIx_xAIx_CallbackNotification_Cancel(workspace->paObjectId,      \
                                                      job,                        \
                                                      workspace->paPrimitive,     \
                                                      workspace->smOperationDone, \
                                                      workspace->smResult,        \
                                                      wssize                      \
                                                     );                           \
}                                                                                 \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET is already defined
#endif
/** \brief  This macro completes the processing of a job's reset. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(retval, wssize)                      \
do                                                                               \
{                                                                                \
  if (NULL_PTR == workspace->paPrimitive)                                        \
  {                                                                              \
    workspace->paPrimitive = primitive;                                          \
  }                                                                              \
  (void) Crypto_xVIx_xAIx_CallbackNotification_Reset(workspace->paObjectId,      \
                                                     job,                        \
                                                     workspace->paPrimitive,     \
                                                     workspace->smOperationDone, \
                                                     workspace->smResult,        \
                                                     wssize                      \
                                                    );                           \
}                                                                                \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART)
#error CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART is already defined
#endif
/** \brief  This macro completes the processing of a job's restart. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART,1 */
#define CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(retval, wssize)                      \
do                                                                                 \
{                                                                                  \
  if (NULL_PTR == workspace->paPrimitive)                                          \
  {                                                                                \
    workspace->paPrimitive = primitive;                                            \
  }                                                                                \
  (void) Crypto_xVIx_xAIx_CallbackNotification_Restart(workspace->paObjectId,      \
                                                       job,                        \
                                                       workspace->paPrimitive,     \
                                                       workspace->smOperationDone, \
                                                       workspace->smResult,        \
                                                       wssize                      \
                                                      );                           \
}                                                                                  \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_RESET_CALLBACK)
#error CRYPTO_XVIX_XAIX_RESET_CALLBACK is already defined
#endif
/** \brief  This macro resets callback handling before processing a job. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_RESET_CALLBACK,1 */
#define CRYPTO_XVIX_XAIX_RESET_CALLBACK()                   \
do                                                          \
{                                                           \
  workspace->notifyType   = CRYPTO_XVIX_XAIX_CALLBACK_NONE; \
  workspace->notifyResult = CRYPTO_E_BUSY;                  \
}                                                           \
while (0)

/* Crypto_xVIx_xAIx_KeyStateType */

#if (defined CRYPTO_XVIX_XAIX_KEYSTATE_INVALID)
#error CRYPTO_XVIX_XAIX_KEYSTATE_INVALID is already defined
#endif
/** \brief  Key is invalid. **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyStateType/0001,1 */
#define CRYPTO_XVIX_XAIX_KEYSTATE_INVALID 0x00U

#if (defined CRYPTO_XVIX_XAIX_KEYSTATE_VALID)
#error CRYPTO_XVIX_XAIX_KEYSTATE_VALID is already defined
#endif
/** \brief  Key is valid. **/
/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_KeyStateType/0001,1 */
#define CRYPTO_XVIX_XAIX_KEYSTATE_VALID 0x01U

/* Crypto_xVIx_xAIx_ReadAccessType */

#if (defined CRYPTO_XVIX_XAIX_RA_DENIED)
#error CRYPTO_XVIX_XAIX_RA_DENIED is already defined
#endif
/** \brief  The key element can not be read from outside the crypto driver. **/
#define CRYPTO_XVIX_XAIX_RA_DENIED 0x01U

#if (defined CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY)
#error CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY is already defined
#endif
/** \brief  Key element can be copied within the same crypto driver. **/
#define CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY 0x02U

#if (defined CRYPTO_XVIX_XAIX_RA_ALLOWED)
#error CRYPTO_XVIX_XAIX_RA_ALLOWED is already defined
#endif
/** \brief  Key element can be read in plaintext. **/
#define CRYPTO_XVIX_XAIX_RA_ALLOWED 0x03U

#if (defined CRYPTO_XVIX_XAIX_RA_ENCRYPTED)
#error CRYPTO_XVIX_XAIX_RA_ENCRYPTED is already defined
#endif
/** \brief  Key element can be read encrypted. **/
#define CRYPTO_XVIX_XAIX_RA_ENCRYPTED 0x04U

/* Crypto_xVIx_xAIx_WriteAccessType */

#if (defined CRYPTO_XVIX_XAIX_WA_DENIED)
#error CRYPTO_XVIX_XAIX_WA_DENIED is already defined
#endif
/** \brief  The key element can not be written from outside the crypto driver. **/
#define CRYPTO_XVIX_XAIX_WA_DENIED 0x01U

#if (defined CRYPTO_XVIX_XAIX_WA_INTERNAL_COPY)
#error CRYPTO_XVIX_XAIX_WA_INTERNAL_COPY is already defined
#endif
/** \brief  Key element within the same crypto driver can be copied to the key element. **/
#define CRYPTO_XVIX_XAIX_WA_INTERNAL_COPY 0x02U

#if (defined CRYPTO_XVIX_XAIX_WA_ALLOWED)
#error CRYPTO_XVIX_XAIX_WA_ALLOWED is already defined
#endif
/** \brief  Key element can be written in plaintext. **/
#define CRYPTO_XVIX_XAIX_WA_ALLOWED 0x03U

#if (defined CRYPTO_XVIX_XAIX_WA_ENCRYPTED)
#error CRYPTO_XVIX_XAIX_WA_ENCRYPTED is already defined
#endif
/** \brief  Key element can be written encrypted. **/
#define CRYPTO_XVIX_XAIX_WA_ENCRYPTED 0x04U

/* Crypto_xVIx_xAIx_KeyElementFormat */

#if (defined CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_OCTET)
#error CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_OCTET is already defined
#endif
/** \brief  Key provided as octet value in binary form. **/
#define CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_OCTET 0x01U

#if (defined CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY)
#error CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY is already defined
#endif
/** \brief  Private key material in ASN.1 coded form (DER coding). The key material
 **         is provided in binary form, not, e.g. as a BASE64 string.
 **/
#define CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY 0x05U

#if (defined CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PUBLICKEY)
#error CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PUBLICKEY is already defined
#endif
/** \brief  Public key material in ASN.1 coded form (DER coding). The key material
 **         is provided in binary form, not, e.g. as a BASE64 string.
 **/
#define CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PUBLICKEY 0x06U

#if (defined CRYPTO_XVIX_XAIX_CDOCJ)
#error CRYPTO_XVIX_XAIX_CDOCJ is already defined
#endif
/** \brief  Get the current job pointer of a Crypto Driver Object. **/
#define CRYPTO_XVIX_XAIX_CDOCJ(objectId) (Crypto_xVIx_xAIx_CDOs[(objectId)].data->jobCurrent)

#if (defined CRYPTO_XVIX_XAIX_CDOCJIP)
#error CRYPTO_XVIX_XAIX_CDOCJIP is already defined
#endif
/** \brief  Return if the current job is processed or not. **/
#define CRYPTO_XVIX_XAIX_CDOCJIP(objectId) (Crypto_xVIx_xAIx_CDOs[(objectId)].data->jobCurrentIsProcessed)

#if (defined CRYPTO_XVIX_XAIX_CDOCP)
#error CRYPTO_XVIX_XAIX_CDOCP is already defined
#endif
/** \brief  Get the current primitive pointer of a Crypto Driver Object. **/
#define CRYPTO_XVIX_XAIX_CDOCP(objectId) (Crypto_xVIx_xAIx_CDOs[(objectId)].data->primitiveCurrent)

#if (defined CRYPTO_XVIX_XAIX_CDOCS)
#error CRYPTO_XVIX_XAIX_CDOCS is already defined
#endif
/** \brief  Get the current state of a Crypto Driver Object. **/
#define CRYPTO_XVIX_XAIX_CDOCS(objectId) (Crypto_xVIx_xAIx_CDOs[(objectId)].data->state)

#if (defined CRYPTO_XVIX_XAIX_CDOPL)
#error CRYPTO_XVIX_XAIX_CDOPL is already defined
#endif
/** \brief  Get an entry of the primitive list of a Crypto Driver Object. **/
#define CRYPTO_XVIX_XAIX_CDOPL(objectId, listId) (Crypto_xVIx_xAIx_CDOs[(objectId)].cnfg->primitiveList[(listId)])

#if (defined CRYPTO_XVIX_XAIX_JOBPI)
#error CRYPTO_XVIX_XAIX_JOBPI is already defined
#endif
/** \brief  Get the primitive info of a job. **/
#define CRYPTO_XVIX_XAIX_JOBPI(job) ((job)->jobPrimitiveInfo->primitiveInfo)

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SHA1_HASHSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_SHA1_HASHSIZE is already defined
#endif
/** \brief  Hash size for SHA1. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SHA1_HASHSIZE 20U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SHA224_HASHSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_SHA224_HASHSIZE is already defined
#endif
/** \brief  Hash size for SHA224. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SHA224_HASHSIZE 28U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SHA256_HASHSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_SHA256_HASHSIZE is already defined
#endif
/** \brief  Hash size for SHA256. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SHA256_HASHSIZE 32U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SHA384_HASHSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_SHA384_HASHSIZE is already defined
#endif
/** \brief  Hash size for SHA384. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SHA384_HASHSIZE 48U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SHA512_HASHSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_SHA512_HASHSIZE is already defined
#endif
/** \brief  Hash size for SHA512. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SHA512_HASHSIZE 64U

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Primitive info used for secondary job initialization. **/
extern CONST(Crypto_PrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_PrimitiveInfo;

/** \brief  Job primitive info used for secondary job initialization. **/
extern CONST(Crypto_JobPrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_JobPrimitiveInfo;

/** \brief  Job info used for secondary job initialization. **/
extern CONST(Crypto_JobInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_JobInfo;

/** \brief  Job used for secondary job initialization. **/
extern CONST(Crypto_JobType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob;

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Variable indicating whether the crypto driver has been initialized. **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
extern VAR(boolean, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_Initialized;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Get the Secondary Hash Algorithm length.
 **
 ** \param[in]      secondaryfamily        Secondary Hash Algorithm.
 **
 ** \returns  hash length.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetHashLen
(
  uint8 secondaryfamily
);

/** \brief  Sets the given job state.
 **
 ** Checks whether the given job and primitive exists and sets its state to the provided
 ** value.
 **
 ** \param[in]  objectId   Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job        Reference to the job whose state needs to be set.
 ** \param[in]  primitive  Pointer to the data structure describes the current primitive.
 ** \param[in]  value      Boolean value that is set as a job state.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SetJobRunning
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          boolean                                                                   value
);

/** \brief  Gets the given job state.
 **
 ** Checks whether the given job and primitive exists and returns its state.
 **
 ** \param[in]      objectId   Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]      job        Reference to the job whose state needs to be retrieved.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 ** \param[in,out]  value      Pointer to the memory location to hold the job state value.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetJobRunning
(
          uint32                                                                    objectId,
  P2CONST(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
    P2VAR(boolean,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
);

/** \brief  Callback notification function for a job's START operation mode.
 **
 ** This function completes the processing of a job's START operation mode.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be processed.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Start
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Callback notification function for a job's UPDATE operation mode.
 **
 ** This function completes the processing of a job's UPDATE operation mode.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be processed.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Update
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Callback notification function for a job's FINISH operation mode.
 **
 ** This function completes the processing of a job's FINISH operation mode.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be processed.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Finish
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Callback notification function for cancelling a job.
 **
 ** This function completes the processing of a job's cancelling.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be cancelled.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Callback notification function for reseting a job.
 **
 ** This function completes the processing of a job's reset.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be reset.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Callback notification function for restarting a job.
 **
 ** This function completes the processing of a job's restart.
 **
 ** \param[in]  objectId         Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job              Reference to the job that shall be restarted.
 ** \param[in]  primitive        Pointer to the data structure describes the current primitive.
 ** \param[in]  smOperationDone  Flag indicating the executed job's operation mode.
 ** \param[in]  cbkResult        Result of the executed job with that operation mode.
 ** \param[in]  workspaceSize    Size of the primitive's workspace.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
);

/** \brief  Checks whether the primitive configured to a given Csm job is provided by a
 **         Crypto Driver Object.
 **
 ** Search over all primitives provided by a single CDO whether there is a primitive matching the
 ** Csm 'Job' to check whether the Csm 'Job' is executable on the CDO or not.
 ** If the 'Job' primitive matches a primitive provided by the CDO 'primitivePtr' is set to this
 ** provided primitive. NULL_PTR otherwise.
 **
 ** \param[in]   objectId      Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]   job           Pointer to the Csm job whose shall be checkeded if it is executable
 **                            on the CDO.
 ** \param[out]  primitivePtr  Pointer to the global constant primitive description data structure
 **                            of the CDO that matches the Csm job or NULL_PTR.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      If a primitive matching the Csm job was found.
 ** \retval  E_NOT_OK  If no primitive matching the Csm job was found.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobPrimitive
(
          uint32                                                                                                                    objectId,
  P2CONST(Crypto_JobType,                                                                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  /* Deviation MISRAC2012-1 */
    P2VAR(P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA), AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr
);

/** \brief  Check if service of a given Csm job is supported by Crypto Driver Object.
 **
 ** Check whether the service of an requested Csm job is supported by at least one primitive
 ** provided by a CDO.
 **
 ** \param[in]  objectId  Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job       Pointer to the Csm job whose service shall be checked if it is supported.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      If at least one primitive supports the service of the requested Csm job.
 ** \retval  E_NOT_OK  If no primitive supports the service of the requested Csm job.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobService
(
          uint32                                                 objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);

/** \brief  This function XORs a block of data to another block of data.
 **
 ** \param[in,out]  destination  A pointer to the memory area which should hold the XOR-ed data.
 ** \param[in]      source       A pointer to the block of data which should be XOR-ed to the
 **                              destination.
 ** \param[in]      byteLength   Holds the amount of bytes which should be XOR-ed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonXOR
(
    P2VAR(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) destination,
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) source,
          uint32                                         byteLength
);

/** \brief  This function shifts a block of data by the amount provided to the left.
 **
 ** \param[in,out]  bufferPtr  A pointer to the memory area which should hold the data
 **                            to be shifted.
 ** \param[in]      bufferLen  Length of the buffer.
 ** \param[in]      count      Holds the amount of bits to be shifted in the buffer.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ShiftBufUint8Left
(
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) bufferPtr,
        uint32                                         bufferLen,
        uint32                                         count
);

/** \brief  This function converts a byte array to 32-bit word representation.
 **
 ** \param[in,out]  buf     A pointer to the memory area which holds the number as a byte array.
 ** \param[in]      bufLen  The length of the array in bytes.
 **
 ** \returns  Error value
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint8ToBufUint32
(
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                         buflen
);

/** \brief  This function converts the 32-bit word representation of a number to a byte array.
 **
 ** \param[in,out]  buf     A pointer to the memory area which holds the number.
 ** \param[in]      bufLen  The length of the array in bytes.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint32ToBufUint8
(
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                         buflen
);

/** \brief  This function converts a byte array to double word representation.
 **
 ** \param[in,out]  buf     A pointer to the memory area which holds the number as a byte array.
 ** \param[in]      bufLen  The length of the array in bytes.
 **
 ** \returns  Error value
 **
 ** \retval  E_OK      The conversion succeeded.
 ** \retval  E_NOT_OK  There was not enough space to store the number.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint8ToBufUint64
(
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                         buflen
);

/** \brief  This function converts the double word representation of a number to a byte array.
 **
 ** \param[in,out]  buf     A pointer to the memory area which holds the number.
 ** \param[in]      bufLen  The length of the array in bytes.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint64ToBufUint8
(
  P2VAR(uint64, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                         buflen
);

/** \brief  Compares two blocks of memory.
 **
 ** Compares at most the first 'len' bytes of the memory block 'buf1' to the first 'len' bytes of the memory block 'buf2'.
 ** If a mismatch is recognized before 'len' bytes are compared, the function returns immediately.
 ** This causes variable run times of the function depending on the position of a mismatch.
 **
 ** \param[in]  buf1  Pointer to the first memory block to compare
 ** \param[in]  buf2  Pointer to the second memory block to compare
 ** \param[in]  len   Amount of bytes to compare
 **
 ** \return  Comparison status
 ** \retval  E_OK      Both memory blocks compare equal
 ** \retval  E_NOT_OK  The memory blocks are not equal
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MemCmp
(
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf1,
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf2,
          uint32                                         len
);

/** \brief  Compares two blocks of memory.
 **
 ** Compares always the first 'len' bytes of the memory block 'buf1' to the first 'len' bytes of the memory block 'buf2'.
 ** If a mismatch is recognized before 'len' bytes are compared, the function does not return immediately.
 ** This causes constant run times of the function per 'len'.
 **
 ** \param[in]  buf1  Pointer to the first memory block to compare
 ** \param[in]  buf2  Pointer to the second memory block to compare
 ** \param[in]  len   Amount of bytes to compare
 **
 ** \return  Comparison status
 ** \retval  E_OK      Both memory blocks compare equal
 ** \retval  E_NOT_OK  The memory blocks are not equal
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MemCmpSec
(
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf1,
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf2,
          uint32                                         len
);

/** \brief  Checks the format of a padding
 **
 ** \param[in]  padType    The type of padding that shall be added, e.g.
 **                        CRYPTO_ALGOFAM_PADDING_PKCS7, CRYPTO_ALGOFAM_PADDING_TLS12
 ** \param[in]  padPtr     Contains the pointer to buffer of padding data that shall be checked
 ** \param[in]  padLength  Contains the number of bytes in 'padPtr'

 **
 ** \returns  Error value
 **
 ** \retval  E_OK      Padding ok.
 ** \retval  E_NOT_OK  Padding not ok.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Chk
(
               uint8                                         padType,
  CONSTP2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) padPtr,
               uint32                                        padLength
);
#endif /* #if (   (FALSE) ... */

/** \brief  Computes the padding for a given set of data respective to a specified blocksize and
 **         padding mechanism.
 **
 ** \param[in]      padType          The type of padding that shall be added, e.g.
 **                                  CRYPTO_ALGOFAM_PADDING_PKCS7, CRYPTO_ALGOFAM_PADDING_TLS12
 ** \param[in]      dataPtr          Contains the pointer to the data a padding shall be computed for
 ** \param[in]      dataLength       Contains the number of bytes in 'dataPtr'
 ** \param[in,out]  resultPtr        Contains the pointer to the buffer where the padding
 **                                  shall be stored.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the result
 **                                  length information is stored in bytes. On calling this function,
 **                                  this parameter shall contain the size of the buffer provided by
 **                                  'resultPtr'. When the request has finished, the actual length of
 **                                  the returned padding is stored.
 ** \param[in]      blockSize        The blocksize with respect to which the padding shall be
 **                                  computed
 **
 ** \returns  Error value
 **
 ** \retval  E_OK                   Operation succeeded
 ** \retval  E_NOT_OK               Operation failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided result buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Add
(
          uint8                                               padType,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr,
          uint8                                               blockSize
);
#endif /* #if (   (FALSE) ... */

/** \brief  Removes the padding from a given set of data respective to a specified blocksize and
 **         padding mechanism.
 **
 ** \param[in]      padType          The type of padding that shall be removed, e.g.
 **                                  CRYPTO_ALGOFAM_PADDING_PKCS7, CRYPTO_ALGOFAM_PADDING_TLS12
 ** \param[in]      dataPtr          Contains the pointer to the data from which a padding shall be
 **                                  removed
 ** \param[in,out]  outputLengthPtr  Holds a pointer to the memory location in which the
 **                                  length information for the output buffer is stored in bytes.
 **                                  On calling this function, this parameter shall contain the
 **                                  maximal possible size of the output buffer. When the request
 **                                  has finished, the actual, unpadded length of the data is stored.
 ** \param[in]      blockSize        The blocksize with respect to which the padding shall be
 **                                  removed
 **
 ** \returns  Error value
 **
 ** \retval  E_OK                  Operation succeeded
 ** \retval  E_NOT_OK              Padding format is incorrect
 ** \retval  CRYPTO_E_SMALL_BUFFER The output buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Del
(
        uint8                                          padType,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dataPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputLengthPtr,
        uint8                                          blockSize
);
#endif /* #if (   (FALSE) ... */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Callout function for storing persistent KeyElements.
 **
 ** This callout is only enabled if there is at least one persistently configured key element
 ** within all keys, that is not dedicated to key element storage locations provided
 ** by crypto hardware.
 ** This callout will be called by the Crypto driver if the Crypto driver shall store key element
 ** material of a persistently configured key element not dedicated to key element
 ** storage locations provided by crypto hardware in a non-volatile way.
 **
 ** \param[in]  keyId         Holds the identifier of the key <Ky> whose key element <Ke> shall be
 **                           set.
 ** \param[in]  keyElementId  Holds the identifier of the key element <Ke> which shall be set.
 ** \param[in]  dataPtr       Holds the pointer to the key element material to be stored.
 ** \param[in]  dataLength    Contains the number of byte to be stored.
 **
 ** \returns  The return code.
 **
 ** \retval  E_OK      Success.
 ** \retval  E_NOT_OK  Setting key element failed.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_KeyElement_SetData}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEYELEMENT_SETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_CODE) Crypto_xVIx_xAIx_KeyElement_SetData
(
          uint32                                                                            keyId,
          uint32                                                                            keyElementId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA) dataPtr,
          uint32                                                                            dataLength
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEYELEMENT_SETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON) */

/** \brief  Callout function for getting persistent KeyElements.
 **
 ** This callout is only enabled if there is at least one persistently configured key element
 ** within all keys, that is not dedicated to key element storage locations provided
 ** by crypto hardware.
 ** This callout will be called by the Crypto driver if the Crypto driver shall read key element
 ** material of a persistently configured key element not dedicated to key element
 ** storage locations provided by crypto hardware.
 **
 ** \param[in]     keyId         Holds the identifier of the key <Ky> whose key element <Ke> shall be
 **                              get.
 ** \param[in]     keyElementId  Holds the identifier of the key element <Ke> which shall be set.
 ** \param[out]    dataPtr       Holds the pointer to the memory location where the key element
 **                              material shall be copied to.
 ** \param[inout]  dataLength    Holds a pointer to the memory location in which the length in
 **                              bytes of the buffer referenced via dataPtr is stored. If this callout
 **                              is called by the Crypto driver this argument contains the buffer
 **                              length in bytes of the buffer referenced via dataPtr. If this callout
 **                              returns, it shall contain the actual number of written bytes.
 **
 ** \returns  The return code.
 **
 ** \retval  E_OK      Success.
 ** \retval  E_NOT_OK  Getting key element failed.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_KeyElement_GetData}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEYELEMENT_GETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_CODE) Crypto_xVIx_xAIx_KeyElement_GetData
(
        uint32                                                                             keyId,
        uint32                                                                             keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_APPL_DATA) dataPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_APPL_DATA) dataLength
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEYELEMENT_GETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON) */

/** \brief  Callout function for storing the Key valid state.
 **
 ** This callout is only enabled if there is at least one key with any persistently configured
 ** key elements.
 ** This callout will be called by the Crypto driver during Crypto_KeySetValid() (validState
 ** = TRUE) in any case and Crypto_KeyElementSet() (validState = FALSE) in case
 ** a persistently configured key element shall be set.
 **
 ** \param[in]  keyId       Holds the identifier of the key <Ky> whose valid state shall be set.
 ** \param[in]  validState  The new validState to be stored.
 **
 ** \returns  The return code.
 **
 ** \retval  E_OK      Success.
 ** \retval  E_NOT_OK  Setting valid state failed.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_Key_SetValid}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEY_SETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_SETVALID_CODE) Crypto_xVIx_xAIx_Key_SetValid
(
  uint32  keyId,
  boolean validState
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEY_SETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON) */

/** \brief  Callout function for getting the Key valid state.
 **
 ** This callout is only enabled if there is at least one key with any persistently configured
 ** key elements.
 ** This callout will be called by the Crypto driver during Crypto_Init() for all keys containing
 ** any persistent key elements to determine the last set valid state of the key.
 ** Additional key elements of the key <Ky> that are not configured as persistent and
 ** without an init value will change the restored valid state of the key during Crypto_Init()
 ** to INVALID.
 ** Additional key elements of the key <Ky> that are not configured as persistent but with
 ** an init value will have no effect on the restored valid state during Crypto_Init().
 **
 ** \param[in]  keyId       Holds the identifier of the key <Ky> whose valid state shall be
 **                         get.
 ** \param[out] validState  Holds the pointer to the memory location where the valid state
 **                         shall be copied to.
 **
 ** \returns  The return code.
 **
 ** \retval  E_OK      Success.
 ** \retval  E_NOT_OK  Getting key element failed.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_Key_SetValid}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEY_GETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_CODE) Crypto_xVIx_xAIx_Key_GetValid
(
        uint32                                                                         keyId,
  P2VAR(boolean, AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_APPL_DATA)  validState
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEY_GETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON) */

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_H */

/*==================[end of file]=================================================================*/

