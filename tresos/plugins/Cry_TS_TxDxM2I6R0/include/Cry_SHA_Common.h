/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_SHA_COMMON_H
#define CRY_SHA_COMMON_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_SHA1Config.h>
#include <Cry_SHA2Config.h>
#include <Cry_SHA_CommonConfig.h>

#if ((CRY_SHA1_ENABLED == STD_ON) || (CRY_SHA2_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/**
 ** \enum Cry_SHAProcessInputStateType
 ** \brief Enumeration of the internal states of Cry_SHAProcessInput()
 **
 ** \var CRY_SHA_S_PROCESS_IDLE
 **
 ** \var CRY_SHA_S_PROCESS
 **
 ** \var CRY_SHA_S_PROCESS_COPY1
 **
 ** \var CRY_SHA_S_PROCESS_COMPRESS1
 **
 ** \var CRY_SHA_S_PROCESS_COMPRESS2
 **
 ** \var CRY_SHA_S_PROCESS_COPY2
 **
 **/
typedef enum
{
  CRY_SHA_S_PROCESS_IDLE,
  CRY_SHA_S_PROCESS,
  CRY_SHA_S_PROCESS_COPY1,
  CRY_SHA_S_PROCESS_COMPRESS1,
  CRY_SHA_S_PROCESS_COMPRESS2,
  CRY_SHA_S_PROCESS_COPY2
}
Cry_SHAProcessInputStateType;

/**
 ** \enum Cry_SHAStateType
 ** \brief Enumeration of the internal states of the SHA computation
 **
 ** \var CRY_SHA_S_IDLE
 ** \brief The algorithm is in the idle state
 **
 ** \var CRY_SHA_S_INIT
 ** \brief The initialization of the algorithm is in progress
 **
 ** \var CRY_SHA_S_INITIALIZED
 ** \brief The algorithm is initialized
 **
 ** \var CRY_SHA_S_UPDATE
 ** \brief The update operation of the algorithm is in progress
 **
 ** \var CRY_SHA_S_FINISH
 ** \brief The finish operation of the algorithm is in progress
 **
 ** \var CRY_SHA_S_FINISH_UPDATE1
 ** \brief The finish update1 operation of the algorithm is
 ** in progress
 **
 ** \var CRY_SHA_S_FINISH_UPDATE2
 ** \brief The finish update2 operation of the algorithm is in progress
 **
 ** \var CRY_SHA_S_FINISH_EXPORT
 ** \brief The finish export operation of the algorithm
 ** is in progress
 **
 **/
typedef enum
{
  CRY_SHA_S_IDLE,
  CRY_SHA_S_INIT,
  CRY_SHA_S_INITIALIZED,
  CRY_SHA_S_UPDATE,
  CRY_SHA_S_FINISH,
  CRY_SHA_S_FINISH_UPDATE1,
  CRY_SHA_S_FINISH_UPDATE2,
  CRY_SHA_S_FINISH_EXPORT
}
Cry_SHAStateType;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
/**
 ** \enum Cry_SHACompressStateType
 ** \brief Enumeration of the internal states of Cry_SHACompress()
 **
 ** \var CRY_SHA_S_COMPRESS_IDLE
 **
 ** \var CRY_SHA_S_COMPRESS
 **
 ** \var CRY_SHA_S_COMPRESS_EXPANSION
 **
 ** \var CRY_SHA_S_COMPRESS_TRANSFORM
 **
 **/
typedef enum
{
  CRY_SHA_S_COMPRESS_IDLE,
  CRY_SHA_S_COMPRESS,
  CRY_SHA_S_COMPRESS_EXPANSION,
  CRY_SHA_S_COMPRESS_TRANSFORM
}
Cry_SHACompressStateType;
#endif

/**
 **
 ** \struct Cry_SHACtxType
 ** \brief The configuration of the SHA hash
 **
 ** \var Cry_SHACtxType::DataLength
 ** \brief Length of the input data in bytes
 **
 ** \var Cry_SHACtxType::Count
 ** \brief Number of bytes already hashed
 **
 ** \var Cry_SHACtxType::left
 ** \brief Number of bytes left
 **
 ** \var Cry_SHACtxType::Internalstate
 ** \brief The internal state of the hash computation, i.e. the hash
 **  value of the data stored so far.
 **
 ** \var Cry_SHACtxType::W
 ** \brief Internal copy of the user data
 **
 ** \var Cry_SHACtxType::a
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::b
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::c
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::d
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::e
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::f
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::g
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::h
 ** \brief Variable to hold the internal state
 **
 ** \var Cry_SHACtxType::t1
 ** \brief Temporary variable
 **
 ** \var Cry_SHACtxType::t2
 ** \brief Temporary variable
 **
 ** \var Cry_SHACtxType::ResultLengthPtr
 ** \brief Pointer to a variable which contains the maximal result
 ** length and where the length of the result will be stored
 **
 ** \var Cry_SHACtxType::Result
 ** \brief Pointer to the memory location in which to store the result
 **
 ** \var Cry_SHACtxType::Data
 ** \brief Pointer to the input data
 **
 ** \var Cry_SHACtxType::p
 ** \brief Pointer into data
 **
 ** \var Cry_SHACtxType::CfgPtr
 ** \brief A pointer to the current SHA configuration which has to be used
 **
 ** \var Cry_SHACtxType::State
 ** \brief The current state of the hash computation
 **
 ** \var Cry_SHACtxType::ProcessInputState
 ** \brief Internal state of the function Cry_SHAProcessInput()
 **
 ** \var Cry_SHACtxType::SHACompressState
 ** \brief Internal state of the function Cry_SHACompress()
 **
 ** \var Cry_SHACtxType::SHAPad
 ** \brief Buffer to store the padded input data
 **
 ** \var Cry_SHACtxType::Partial
 ** \brief Input data to be hashed
 **
 ** \var Cry_SHACtxType::length
 ** \brief 64-bit representation of length of data
 **
 ** \var Cry_SHACtxType::copy
 ** \brief Number of bytes to copy
 **
 ** \var Cry_SHACtxType::offset
 ** \brief Offset into temporal buffer in Ctx
 **
 ** \var Cry_SHACtxType::i
 ** \brief Loop variable
 **
 ** \var Cry_SHACtxType::TruncationAllowed
 ** \brief Is truncation of the result allowed or should an error be
 ** returned when the Result buffer is too small
 **
 ** \var Cry_SHACtxType::RestartFlag
 ** \brief Flag that states if the restart of the service is active
 **
 **/
typedef struct
{
  uint32                                   DataLength;
  uint32                                   Count;
  uint32                                   left;
#if ((CRY_SHA2_WORD_SIZE == 32U) || (CRY_SHA1_ENABLED == STD_ON))
  uint32                                   Internalstate[CRY_SHA_STATE_WORDS];
  uint32                                   W[CRY_SHA_BLOCK_LEN_WORDS];
  uint32                                   a;
  uint32                                   b;
  uint32                                   c;
  uint32                                   d;
  uint32                                   e;
#if (CRY_SHA2_ENABLED == STD_ON)
  uint32                                   f;
  uint32                                   g;
  uint32                                   h;
  uint32                                   t2;
#endif
  uint32                                   t1;
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
  uint32                                   Internalstate[CRY_SHA_STATE_WORDS << 1U];
  uint32                                   W[CRY_SHA_BLOCK_LEN_WORDS];
  uint32                                   a[2U];
  uint32                                   b[2U];
  uint32                                   c[2U];
  uint32                                   d[2U];
  uint32                                   e[2U];
  uint32                                   f[2U];
  uint32                                   g[2U];
  uint32                                   h[2U];
  uint32                                   t1[2U];
  uint32                                   t2[2U];
#endif
  P2VAR(uint32, TYPEDEF, CRY_APPL_DATA)    ResultLengthPtr;
  P2VAR(uint8, TYPEDEF, CRY_APPL_DATA)     Result;
  P2CONST(uint8, TYPEDEF, CRY_APPL_DATA)   Data;
  P2CONST(uint8, TYPEDEF, CRY_APPL_DATA)   p;
  P2CONST(Cry_SHAConfigType, TYPEDEF, CRY_APPL_DATA) CfgPtr;
  Cry_SHAStateType                         State;
  Cry_SHAProcessInputStateType             ProcessInputState;
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
  Cry_SHACompressStateType                 SHACompressState;
#endif
  uint8                                    SHAPad[CRY_SHA_BLOCK_LEN_BYTES];
  uint8                                    Partial[CRY_SHA_BLOCK_LEN_BYTES];
#if ((CRY_SHA2_WORD_SIZE == 32U) || (CRY_SHA1_ENABLED == STD_ON))
  uint8                                    length[8U];
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
  uint8                                    length[16U];
#endif
  uint8                                    copy;
  uint8                                    offset;
  uint8                                    i;
  boolean                                  TruncationAllowed;
  boolean                                  RestartFlag;
}
Cry_SHACtxType;

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

extern FUNC(void, CRY_CODE) Cry_SHAMainFunction
(
  P2VAR(Cry_SHACtxType, AUTOMATIC, CRY_APPL_DATA) CtxPtr,
  Cry_SHAInitFctType                              InitFct,
  Cry_SHACompressFctType                          CompressFct
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if ((CRY_SHA1_ENABLED == STD_ON) || (CRY_SHA2_ENABLED == STD_ON)) */

#endif
