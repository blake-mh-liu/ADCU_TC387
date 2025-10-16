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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to object.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections.
 *
 * MISRAC2012-3) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * The given warnings at this point are false positives, as the macro itself is fully tested
 * for all possible paths of a ternary operator. But a given call of the macro will always go either
 * way of checking the length of the shift width.
 *
 */

/* Code-Metric Deviation List
 *
 * CODEMETRIC-1) Deviated Rule: HIS_VOCF
 * not 13.31 <= 12
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                              /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 19U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 13U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTIDLE)
#error CRYPTO_XVIX_XAIX_STATE_STARTIDLE already defined
#endif
/** \brief  The StartIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTIDLE 0U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTEXEC)
#error CRYPTO_XVIX_XAIX_STATE_STARTEXEC already defined
#endif
/** \brief  The StartExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTEXEC 1U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE already defined
#endif
/** \brief  The UpdateIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE 2U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC already defined
#endif
/** \brief  The UpdateExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC 3U

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS already defined
#endif
/** \brief  The UpdateProcess state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS 4U

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS)
#error CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS already defined
#endif
/** \brief  The UpdateCompress state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS 5U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE already defined
#endif
/** \brief  The UpdateFinishIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE 6U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXEC)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXEC already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXEC 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1 already defined
#endif
/** \brief  The FinishCompressLastBlock1of1 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1 8U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2 already defined
#endif
/** \brief  The FinishCompressLastBlock1of2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2 9U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2 already defined
#endif
/** \brief  The FinishCompressLastBlock2of2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2 10U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 11U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 12U

#if (defined CRYPTO_XVIX_XAIX_REG_A)
#error CRYPTO_XVIX_XAIX_REG_A already defined
#endif
/** \brief  Register A. **/
#define CRYPTO_XVIX_XAIX_REG_A 0x00U

#if (defined CRYPTO_XVIX_XAIX_REG_B)
#error CRYPTO_XVIX_XAIX_REG_B already defined
#endif
/** \brief  Register B. **/
#define CRYPTO_XVIX_XAIX_REG_B 0x01U

#if (defined CRYPTO_XVIX_XAIX_REG_C)
#error CRYPTO_XVIX_XAIX_REG_C already defined
#endif
/** \brief  Register C. **/
#define CRYPTO_XVIX_XAIX_REG_C 0x02U

#if (defined CRYPTO_XVIX_XAIX_REG_D)
#error CRYPTO_XVIX_XAIX_REG_D already defined
#endif
/** \brief  Register D. **/
#define CRYPTO_XVIX_XAIX_REG_D 0x03U

#if (defined CRYPTO_XVIX_XAIX_REG_E)
#error CRYPTO_XVIX_XAIX_REG_E already defined
#endif
/** \brief  Register E. **/
#define CRYPTO_XVIX_XAIX_REG_E 0x04U

#if (defined CRYPTO_XVIX_XAIX_REG_F)
#error CRYPTO_XVIX_XAIX_REG_F already defined
#endif
/** \brief  Register F. **/
#define CRYPTO_XVIX_XAIX_REG_F 0x05U

#if (defined CRYPTO_XVIX_XAIX_REG_G)
#error CRYPTO_XVIX_XAIX_REG_G already defined
#endif
/** \brief  Register G. **/
#define CRYPTO_XVIX_XAIX_REG_G 0x06U

#if (defined CRYPTO_XVIX_XAIX_REG_H)
#error CRYPTO_XVIX_XAIX_REG_H already defined
#endif
/** \brief  Register H. **/
#define CRYPTO_XVIX_XAIX_REG_H 0x07U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0010,1 */
#if (defined CRYPTO_XVIX_XAIX_CH)
#error CRYPTO_XVIX_XAIX_CH already defined
#endif
/** \brief  This macro represents the CH logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_CH(x, y ,z)                                               \
(                                                                                  \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_AND32((x), (y)                        ), \
                         CRYPTO_XVIX_XAIX_AND32(CRYPTO_XVIX_XAIX_NOT32((x)), (z))  \
                        )                                                          \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0011,1 */
#if (defined CRYPTO_XVIX_XAIX_MAJ)
#error CRYPTO_XVIX_XAIX_MAJ already defined
#endif
/** \brief  This macro represents the MAJ logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_MAJ(x, y, z)                                             \
(                                                                                 \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_AND32((x), (y)), \
                                                CRYPTO_XVIX_XAIX_AND32((x), (z))  \
                                               ),                                 \
                         CRYPTO_XVIX_XAIX_AND32((y), (z))                         \
                        )                                                         \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0012,1 */
#if (defined CRYPTO_XVIX_XAIX_BSIG0)
#error CRYPTO_XVIX_XAIX_BSIG0 already defined
#endif
/** \brief  This macro represents the BSIG0 logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_BSIG0(x)                                                 \
(                                                                                 \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_ROR32((x),  2U), \
                                                CRYPTO_XVIX_XAIX_ROR32((x), 13U)  \
                                               ),                                 \
                         CRYPTO_XVIX_XAIX_ROR32((x), 22U)                         \
                        )                                                         \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0013,1 */
#if (defined CRYPTO_XVIX_XAIX_BSIG1)
#error CRYPTO_XVIX_XAIX_BSIG1 already defined
#endif
/** \brief  This macro represents the BSIG1 logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_BSIG1(x)                                                 \
(                                                                                 \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_ROR32((x),  6U), \
                                                CRYPTO_XVIX_XAIX_ROR32((x), 11U)  \
                                               ),                                 \
                         CRYPTO_XVIX_XAIX_ROR32((x), 25U)                         \
                        )                                                         \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0014,1 */
#if (defined CRYPTO_XVIX_XAIX_SSIG0)
#error CRYPTO_XVIX_XAIX_SSIG0 already defined
#endif
/** \brief  This macro represents the SSIG0 logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_SSIG0(x)                                                 \
(                                                                                 \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_ROR32((x),  7U), \
                                                CRYPTO_XVIX_XAIX_ROR32((x), 18U)  \
                                               ),                                 \
                         CRYPTO_XVIX_XAIX_SHR32((x), 3U)                          \
                        )                                                         \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0015,1 */
#if (defined CRYPTO_XVIX_XAIX_SSIG1)
#error CRYPTO_XVIX_XAIX_SSIG1 already defined
#endif
/** \brief  This macro represents the SSIG1 logical function mentioned in Chapter 5.1 of rfc4634 **/
#define CRYPTO_XVIX_XAIX_SSIG1(x)                                                 \
(                                                                                 \
  CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_XOR32(CRYPTO_XVIX_XAIX_ROR32((x), 17U), \
                                                CRYPTO_XVIX_XAIX_ROR32((x), 19U)  \
                                               ),                                 \
                         CRYPTO_XVIX_XAIX_SHR32((x), 10U)                         \
                        )                                                         \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0016,1 */
#if (defined CRYPTO_XVIX_XAIX_T1)
#error CRYPTO_XVIX_XAIX_T1 already defined
#endif
/** \brief  This macro calculates the temporay word T1 as described in the rfc4634 **/
#define CRYPTO_XVIX_XAIX_T1(i)                                                                                                      \
(                                                                                                                                   \
  CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_ADD32(workspace->R[CRYPTO_XVIX_XAIX_REG_H],                        \
                                                                       CRYPTO_XVIX_XAIX_BSIG1(workspace->R[CRYPTO_XVIX_XAIX_REG_E]) \
                                                                      ),                                                            \
                                                CRYPTO_XVIX_XAIX_ADD32(Crypto_xVIx_xAIx_HASH_SHA2224_NOTSET_K[(i)],                                  \
                                                                       workspace->W[((i) == 0U) ? 0U : ((i) % 16U)]                  \
                                                                      )                                                             \
                                               ),                                                                                   \
                         CRYPTO_XVIX_XAIX_CH(workspace->R[CRYPTO_XVIX_XAIX_REG_E],                                                  \
                                             workspace->R[CRYPTO_XVIX_XAIX_REG_F],                                                  \
                                             workspace->R[CRYPTO_XVIX_XAIX_REG_G]                                                   \
                                            )                                                                                       \
                        )                                                                                                           \
)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0017,1 */
#if (defined CRYPTO_XVIX_XAIX_T2)
#error CRYPTO_XVIX_XAIX_T2 already defined
#endif
/** \brief  This macro calculates the temporay word T2 as described in the rfc4634 **/
#define CRYPTO_XVIX_XAIX_T2(i)                                                         \
(                                                                                      \
  CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_BSIG0(workspace->R[CRYPTO_XVIX_XAIX_REG_A]), \
                         CRYPTO_XVIX_XAIX_MAJ(workspace->R[CRYPTO_XVIX_XAIX_REG_A],    \
                                              workspace->R[CRYPTO_XVIX_XAIX_REG_B],    \
                                              workspace->R[CRYPTO_XVIX_XAIX_REG_C]     \
                                             )                                         \
                        )                                                              \
)

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_ERROR'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief Search the state transition table for the next state
 **
 ** This function searches the state trasition table for the next state that shall be processed.
 **
 ** \param[in,out]  smStateIndx    Pointer to the variable storing the index of the last processed
 **                                state. After the function call the index of the next state will
 **                                be stored in the variable.
 ** \param[in]      curState       Variable storing the current state.
 ** \parma[in]      resultAction   Variable storing the result of the previously called
 **                                action function.
 ** \parma[in]      jobProcessing  Variable stroing the processing type of the current job.
 ** \param[out]     nxtState       Pointer to the next state.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful.
 ** \retval  CRYPTO_E_BUSY  Further processing is needed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful.
 ** \retval  CRYPTO_E_BUSY  Further processing is needed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS'
 **         and
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1'
 **         and
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2'
 **         and
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful, trigger state transition function.
 ** \retval  CRYPTO_E_BUSY  Request not yet done.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Compress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* state transition functions */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK  Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateCompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock1Of22FinishCompressLastBlock2Of2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
 **         or
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_CANCEL'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK  Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                                    CRYPTO_XVIX_XAIX_STATE_STARTEXEC,                   CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                  CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,                                CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,                  CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,               CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,                          CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,               CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS,              CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateCompress2UpdateProcess,                            CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS,              CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,            CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,                  CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,                  CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock2StartIdle,                       CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock1Of22FinishCompressLastBlock2Of2, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                              CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock2StartIdle,                       CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                                        CRYPTO_XVIX_XAIX_STATE_CANCEL,                      CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                         CRYPTO_XVIX_XAIX_STATE_ERROR,                       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE                   */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC                   */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE                  */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC                  */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS               */ { Crypto_xVIx_xAIx_StateMachine_UpdateProcess },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATECOMPRESS              */ { Crypto_xVIx_xAIx_StateMachine_Compress      },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE            */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC                  */ { Crypto_xVIx_xAIx_StateMachine_FinishExec    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF1 */ { Crypto_xVIx_xAIx_StateMachine_Compress      },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK1OF2 */ { Crypto_xVIx_xAIx_StateMachine_Compress      },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPRESSLASTBLOCK2OF2 */ { Crypto_xVIx_xAIx_StateMachine_Compress      },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                      */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                       */ { NULL_PTR                                    }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>
#define CRYPTO_xVIx_xAIx_START_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The sequence of sixty-four constant 32-bit words, K0, K1, ..., K63
 **         used by HASH_SHA2224_NOTSET.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
/* !LINKSTO Crypto.Req.CPr/HASH_SHA2256_NOTSET/GENERAL/0002,1 */
/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0002,1 */
static CONST(uint32, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_HASH_SHA2224_NOTSET_K[CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_ROUNDS] =
{
  0x428A2F98U, 0x71374491U, 0xB5C0FBCFU, 0xE9B5DBA5U,
  0x3956C25BU, 0x59F111F1U, 0x923F82A4U, 0xAB1C5ED5U,
  0xD807AA98U, 0x12835B01U, 0x243185BEU, 0x550C7DC3U,
  0x72BE5D74U, 0x80DEB1FEU, 0x9BDC06A7U, 0xC19BF174U,
  0xE49B69C1U, 0xEFBE4786U, 0x0FC19DC6U, 0x240CA1CCU,
  0x2DE92C6FU, 0x4A7484AAU, 0x5CB0A9DCU, 0x76F988DAU,
  0x983E5152U, 0xA831C66DU, 0xB00327C8U, 0xBF597FC7U,
  0xC6E00BF3U, 0xD5A79147U, 0x06CA6351U, 0x14292967U,
  0x27B70A85U, 0x2E1B2138U, 0x4D2C6DFCU, 0x53380D13U,
  0x650A7354U, 0x766A0ABBU, 0x81C2C92EU, 0x92722C85U,
  0xA2BFE8A1U, 0xA81A664BU, 0xC24B8B70U, 0xC76C51A3U,
  0xD192E819U, 0xD6990624U, 0xF40E3585U, 0x106AA070U,
  0x19A4C116U, 0x1E376C08U, 0x2748774CU, 0x34B0BCB5U,
  0x391C0CB3U, 0x4ED8AA4AU, 0x5B9CCA4FU, 0x682E6FF3U,
  0x748F82EEU, 0x78A5636FU, 0x84C87814U, 0x8CC70208U,
  0x90BEFFFAU, 0xA4506CEBU, 0xBEF9A3F7U, 0xC67178F2U
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType           result         = E_NOT_OK;
  Crypto_OperationModeType jobMode        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  Crypto_ProcessingType    jobProcessing  = job->jobPrimitiveInfo->processingType;
  boolean                  runPrimitive   = FALSE;
  boolean                  jobIsProcessed = FALSE;

  workspace->paPrimitive = primitive;

  if (workspace->smState == CRYPTO_XVIX_XAIX_STATE_CANCEL)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0002,1 */
    result = CRYPTO_E_JOB_CANCELED;
  }
  else
  if (CRYPTO_OPERATIONMODE_START == (jobMode & CRYPTO_OPERATIONMODE_START))
  {
    /* !LINKSTO Crypto.Dsn.JobTransition.Idle2Active,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0003,1 */
    Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_BUSY;
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
    workspace->paObjectId                                                       = objectId;
    workspace->smStateIndx                                                      = 0U;
    /* !LINKSTO Crypto.Dsn.JobTransition.InitialActive2Start,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1 */
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    workspace->smState                                                          = CRYPTO_XVIX_XAIX_STATE_STARTEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    runPrimitive                                                                = TRUE;
  }
  else
  if (   (CRYPTO_OPERATIONMODE_UPDATE == (jobMode & CRYPTO_OPERATIONMODE_UPDATE))
      && (   (CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE       == workspace->smState)
          || (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == workspace->smState)
         )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1 */
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    runPrimitive       = TRUE;
  }
  else
  if (   (CRYPTO_OPERATIONMODE_FINISH             == (jobMode & CRYPTO_OPERATIONMODE_FINISH))
      && (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == workspace->smState                     )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00023,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1 */
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_FINISHEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    runPrimitive       = TRUE;
  }
  else
  {
    (void) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Reset(workspace->paObjectId, job, primitive);
  }

  if (TRUE == runPrimitive)
  {
    result = E_OK;
    /* all parameters given to this function are already checked in the ProcessJob function,
       hence this function can not fail in this case */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00027,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0004,1 */
    (void) Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, TRUE);

    workspace->smOperationDone = 0U;
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0005,1 */
    if (CRYPTO_PROCESSING_SYNC == jobProcessing)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00026,1 */
      do
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0013,1 */
        /* This function can only return E_OK */
        (void) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Main(objectId, job, primitive);

        result = Crypto_xVIx_xAIx_GetJobRunning(objectId, job, primitive, &jobIsProcessed);
      }
      while (    (TRUE == jobIsProcessed)
              && (E_OK == result        )
            );
      result = workspace->smResult;
    }
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Main ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType                                resultAction  = E_NOT_OK;
  Crypto_ProcessingType                         jobProcessing = job->jobPrimitiveInfo->processingType;
  Crypto_OperationModeType                      jobMode       = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState      = CRYPTO_XVIX_XAIX_STATE_ERROR;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType nxtState      = CRYPTO_XVIX_XAIX_STATE_ERROR;
  boolean                                       nxtStateFound = FALSE;
  boolean                                       flgExecute    = FALSE;
  uint8                                         smStateIndx   = workspace->smStateIndx;

  TS_PARAM_UNUSED(objectId);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0002,1 */
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0001,1 */
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  if (FALSE == workspace->lockMain)
  {
    workspace->lockMain = TRUE;
    flgExecute          = TRUE;
  }
  curState = workspace->smState;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0003,1 */
  if (TRUE == flgExecute)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0004,1 */
    if (   (CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE == curState                               )
        && (CRYPTO_OPERATIONMODE_UPDATE       == (jobMode & CRYPTO_OPERATIONMODE_UPDATE))
       )
    {
      curState = CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC;
    }
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0005,1 */
    if (   (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == curState                               )
        && (CRYPTO_OPERATIONMODE_FINISH             == (jobMode & CRYPTO_OPERATIONMODE_FINISH))
       )
    {
      curState = CRYPTO_XVIX_XAIX_STATE_FINISHEXEC;
    }
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    if (   (curState                      != workspace->smState)
        && (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)
       )
    {
      workspace->smState = curState;
    }
    else
    {
      curState = workspace->smState;
    }
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0007,1 */
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateActionTable[curState].fcnAction(job, primitive);
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0008,1 */
      resultAction = E_OK;
    }

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0009,1 */
    /* search for entry in state transition table in 2 steps */
    nxtStateFound = Crypto_xVIx_xAIx_GetNextState(&smStateIndx,
                                                  curState,
                                                  resultAction,
                                                  jobProcessing,
                                                  &nxtState
                                                 );
    /* CHECK: NOPARSE
     * The return value of GetNextState cannot be FALSE for HASH_SHA2224_NOTSET, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0011,1 */
        /* CHECK: NOPARSE
         * HASH primitives cannot reach error state as they can accept every input.
         */
        if (E_OK != workspace->smResult)
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00119,1 */
          nxtState = CRYPTO_XVIX_XAIX_STATE_ERROR;
        }
        /* CHECK: PARSE */
      }
    }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    else
    {
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_MAINFUNCTION,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
    }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0001,1 */
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    if (curState == workspace->smState)
    {
      workspace->smState = nxtState;
    }
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0012,1 */
    workspace->lockMain = FALSE;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Cancel --------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType                                result         = E_NOT_OK;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState       = CRYPTO_XVIX_XAIX_STATE_ERROR;
  boolean                                       jobIsProcessed = FALSE;

  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  curState = workspace->smState;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  if (   (CRYPTO_XVIX_XAIX_STATE_CANCEL != curState)
      && (CRYPTO_XVIX_XAIX_STATE_ERROR  != curState)
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0003,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_CANCEL;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    result             = CRYPTO_E_JOB_CANCELED;

    if (   (E_OK  == Crypto_xVIx_xAIx_GetJobRunning(objectId, job, primitive, &jobIsProcessed))
        && (FALSE == jobIsProcessed                                                           )
       )
    {
      /* If this path is reached the cancel function called by the main function will reset the
         workspace and set the state to StartIdle. This is why one Main call is sufficient */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0004,1 */
      /* This function can only return E_OK */
      (void) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Main(objectId, job, primitive);
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0005,1 */
      result = E_OK;
    }
  }
  /* CHECK: NOPARSE */
  else
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0006,1 */
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Reset ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Restart ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Callback ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
/* CHECK: NOPARSE
 * HASH primitives cannot reach error state as they can accept every input.
 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType result   = E_NOT_OK;
  Std_ReturnType smResult = E_NOT_OK;

  if (   (CRYPTO_XVIX_XAIX_STATE_ERROR == workspace->smState)
      && (                        E_OK == workspace->smResult ))
  {
    /* Unexpected error state reached, make sure to report E_NOT_OK back. */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00119,1 */
    workspace->smResult = E_NOT_OK;
  }
  else
  {
    smResult            = workspace->smResult;
  }
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00025,1 */
  result              = Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState,
  Std_ReturnType resultAction,
  Crypto_ProcessingType jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
)
{
  uint8   i             = 0U;
  boolean nxtStateFound = FALSE;

  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType                            result      = E_NOT_OK;
  uint32                                    bytesRemain = 0U;
  uint8                                     bytesFetch  = 0U;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) m           = (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M;

  bytesRemain = (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength - workspace->inputBytesFetched);
  bytesFetch  = (uint8) CRYPTO_XVIX_XAIX_MIN(((uint32) CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE - workspace->mLvl),
                                             bytesRemain
                                            );

  if (0U != bytesFetch)
  {
    TS_MemCpy(&(m[workspace->mLvl]),
              &(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr[workspace->inputBytesFetched]),
              bytesFetch
             );
    workspace->mLvl              += bytesFetch;
    workspace->inputBytesFetched += bytesFetch;
  }

  if (   ((CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE                           ) == workspace->mLvl)
      && (((uint32) CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE - workspace->mLvl) <  bytesRemain    )
     )
  {
    /* CHECK: NOPARSE
     * This is a platform specific check and both paths cannot be covered on the same platform.
     */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
      /* The block size is set to 16 so this function can not fail */
      (void) Crypto_xVIx_xAIx_BufUint8ToBufUint32((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE);
    }
#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
    /* CHECK: PARSE */

    workspace->rounds = 0U;

    result = CRYPTO_E_BUSY;
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec ------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType                            result = E_NOT_OK;
  uint32                                    L      = 0U;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) m      = (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M;

  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0006,1 */
  L                 = (workspace->mCnt * CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE) + workspace->mLvl; /* length of full message in bytes */
  workspace->length = L * 8U;                                                                           /* length of full message in bits  */
  workspace->rounds  = 0U;

  /* check whether last block padding causes no additional block
   * (blocksize byte - 1 byte (0x80) - doubled wordsize byte (length info))
   */
  /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0009,2 */
  if (   (L % CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE)
      <= (CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE - 1U - (CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_WORDSIZE * 2U))
     )
  {
    /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0010,1 */
    m[L % CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE] = 0x80U;

    /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0007,1 */
    /* CHECK: NOPARSE
     * This is a platform specific check and both paths cannot be covered on the same platform.
     */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
      /* The block size is set to 16 so this function can not fail */
      (void) Crypto_xVIx_xAIx_BufUint8ToBufUint32((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE);
    }
#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
    /* CHECK: PARSE */

    /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0005,1 */
    workspace->M[CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE - 1U] = workspace->length;

    result = E_OK;
  }
  else
  {
    /* add 0x80 for the padding to the current block */
    /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0010,1 */
    m[L % CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE] = 0x80U;

    /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0007,1 */
    /* CHECK: NOPARSE
     * This is a platform specific check and both paths cannot be covered on the same platform.
     */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
      /* The block size is set to 16 so this function can not fail */
      (void) Crypto_xVIx_xAIx_BufUint8ToBufUint32((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE);
    }
#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
    /* CHECK: PARSE */

    result = CRYPTO_E_BUSY;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Compress --------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Compress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;
  uint32         i      = 0U;
  uint8          j      = 0U;

  uint32  T1    = 0x00U;
  uint32  T2    = 0x00U;
  uint32* wRPtr = workspace->R;
  uint32* wWPtr = workspace->W;

  TS_PARAM_UNUSED(job);

  if (0U == workspace->rounds)
  {
    /* initialize the working variables */
    TS_MemCpy(wRPtr, workspace->H, (8U * CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_WORDSIZE));

    /* prepare the message schedule W */
    TS_MemCpy(wWPtr, workspace->M, (16U * CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_WORDSIZE));
  }

  for (i = workspace->rounds;
       (   (i < ((uint32) workspace->rounds + CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_COMPRESSLOOPS + 1U))
        && (i < CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_ROUNDS                                          )
       );
       i++
      )
  {
    if (15U < i)
    {
      j               = i % 16U;
      /* Deviation MISRAC2012-3 */
      wWPtr[j] = CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_ADD32(CRYPTO_XVIX_XAIX_SSIG1(wWPtr[(j + 14U) & 0x0FU]), wWPtr[(j + 9U) & 0x0FU]), CRYPTO_XVIX_XAIX_SSIG0(wWPtr[(j + 1U) & 0x0FU])), wWPtr[j]);
    }

    T1                            = CRYPTO_XVIX_XAIX_T1(i);
    T2                            = CRYPTO_XVIX_XAIX_T2(i);
    wRPtr[CRYPTO_XVIX_XAIX_REG_H] = wRPtr[CRYPTO_XVIX_XAIX_REG_G];
    wRPtr[CRYPTO_XVIX_XAIX_REG_G] = wRPtr[CRYPTO_XVIX_XAIX_REG_F];
    wRPtr[CRYPTO_XVIX_XAIX_REG_F] = wRPtr[CRYPTO_XVIX_XAIX_REG_E];
    wRPtr[CRYPTO_XVIX_XAIX_REG_E] = CRYPTO_XVIX_XAIX_ADD32(wRPtr[CRYPTO_XVIX_XAIX_REG_D], T1);
    wRPtr[CRYPTO_XVIX_XAIX_REG_D] = wRPtr[CRYPTO_XVIX_XAIX_REG_C];
    wRPtr[CRYPTO_XVIX_XAIX_REG_C] = wRPtr[CRYPTO_XVIX_XAIX_REG_B];
    wRPtr[CRYPTO_XVIX_XAIX_REG_B] = wRPtr[CRYPTO_XVIX_XAIX_REG_A];
    wRPtr[CRYPTO_XVIX_XAIX_REG_A] = CRYPTO_XVIX_XAIX_ADD32(T1, T2);
  }

  workspace->rounds += CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_COMPRESSLOOPS + 1U;

  if ((CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_ROUNDS - 1U) <= workspace->rounds)
  {
    for (i = 0U; i < 8U; i++)
    {
      workspace->H[i] = CRYPTO_XVIX_XAIX_ADD32(wRPtr[i], workspace->H[i]);
    }

    TS_MemBZero(wWPtr,        CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_ROUNDS        );
    TS_MemBZero(workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE);

    result = E_OK;
  }
  else
  {
    result = CRYPTO_E_BUSY;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);
/* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/GENERAL/0003,1 */
  workspace->H[0U] = 0xC1059ED8U;
  workspace->H[1U] = 0x367CD507U;
  workspace->H[2U] = 0x3070DD17U;
  workspace->H[3U] = 0xF70E5939U;
  workspace->H[4U] = 0xFFC00B31U;
  workspace->H[5U] = 0x68581511U;
  workspace->H[6U] = 0x64F98FA7U;
  workspace->H[7U] = 0xBEFA4FA4U;

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess ----------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->inputBytesFetched = 0U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateCompress2UpdateProcess ------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateCompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->mLvl  = 0U;
  workspace->mCnt += 1U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock1Of22FinishCompressLastBlock2Of2 ---- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock1Of22FinishCompressLastBlock2Of2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  TS_MemBZero(workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE_BYTE);
  workspace->rounds = 0U;
  workspace->M[CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_BLOCKSIZE - 1U] = workspace->length;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock2StartIdle --------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCompressLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  /* CHECK: NOPARSE
   * This is a platform specific check and both paths cannot be covered on the same platform.
   */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  {
    Crypto_xVIx_xAIx_BufUint32ToBufUint8(workspace->H, 8U);
  }
#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
  /* CHECK: PARSE */

  /* !LINKSTO Crypto.Req.CPr/HASH_SHA2224_NOTSET/FINISH/0008,2 */
  TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
            workspace->H,
            CRYPTO_XVIX_XAIX_MIN(*(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr),
                                 CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_RESULTSIZE
                                )
           );
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_MIN(*(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr),
                                                                                          CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA2224_NOTSET_RESULTSIZE
                                                                                         );

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA2224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

