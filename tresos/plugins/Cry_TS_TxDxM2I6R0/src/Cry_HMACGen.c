/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1, CSM0692,1 */

/*  MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast should not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the the original type.
 */

/* !LINKSTO CS_SECURE_CRY_0193,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Cry_HMAC.h>
#include <Cry_HMACGen.h>     /* !LINKSTO EB_CRY_0005,1 */

#if (CRY_HMAC_GEN_ENABLED == TRUE)

/*==[Macros]==================================================================*/

#if (defined CRY_HMAC_G_HANDLE_FAILING_HASH)
#error CRY_HMAC_G_HANDLE_FAILING_HASH is already defined
#endif
/** \brief Clears the state of the HMAC generate algorithm and calls the
 **         Csm callbacks after a rejected hash operation
 **/
#define CRY_HMAC_G_HANDLE_FAILING_HASH                \
  do                                                  \
  {                                                   \
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_IDLE;           \
                                                      \
  Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);  \
                                                      \
  Csm_MacGenerateServiceFinishNotification();         \
  } while (0)

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_HMACGenStateType
 * \brief Enumeration of the internal states of the HMAC generation.
 *
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_IDLE
 * \brief Idle state of the HMAC routine.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_PREPAREKEY
 * \brief Copy the user-provided key to the "ProcessedKey" array
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_INIT1
 * \brief The underlying Hash Algorithm gets initialized.
 *        if the key is longer than CRY_HMAC_HASH_BLOCK_LEN_BYTES,
 *        CRY_HMAC_G_S_WAIT_FOR_HASHKEY is the next state. Otherwise
 *        CRY_HMAC_G_S_WAIT_FOR_INIT1 is the next state.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_HASHKEY
 * \brief If the given key is longer than the block length, it must be hashed.
 *        In this state the routine waits for the hash algorithm to initialize.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_HASHKEY_UPDATE
 * \brief The key is given to the hash routine.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_HASHKEY_UPDATE
 * \brief Waiting for the hashroutine to handle the key.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_HASHKEY_FINISH
 * \brief The hash routine gets finished for the hashing of the key.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_HASHKEY_FINISH
 * \brief The routine is waiting for the underlying hash algorithm to finish processing of the key
 *        hash.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_HASHKEY_INIT
 * \brief The underlying hash routine has to be initilised again.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_INIT1
 * \brief Inner padding. Update the hash routine with the padded key.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_INIT2
 * \brief Pad last block if necessary and XOR it with K1 or K2.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_INIT2
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_INITIALIZED
 * \brief The HMAC routine is initialized.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_UPDATE
 * \brief Update the hash algorithm with the given message.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_G_S_WAIT_FOR_UPDATE
 * \brief Wait for the input message to be hashed.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_FINISH1
 * \brief Finish processing the hash with the inner padded key and the message.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_FINISH1
 * \brief The routine is waiting for the underlying hash algorithm to finish processing of the hash.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_FINISH2
 * \brief The underlying hash algorithm is initilized again.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_FINISH2
 * \brief The routine waits in this state, for the initialized Hash algorithm.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_FINISH3
 * \brief Outer padding. Update the hash routine with the padded key.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_FINISH3
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_FINISH4
 * \brief Update the hashroutine with the hash result of calculated within state
 *        CRY_HMAC_G_S_FINISH1.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_FINISH4
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_FINISH5
 * \brief Finish the hash.
 *//**
 * \var Cry_HMACGenStateType::CRY_HMAC_G_S_WAIT_FOR_FINISH5
 * \brief The routine is waiting for the underlying hash algorithm to finish processing of the hash.
  */
typedef enum
{
  CRY_HMAC_G_S_IDLE,
  CRY_HMAC_G_S_PREPAREKEY,
  CRY_HMAC_G_S_INIT1,
  CRY_HMAC_G_S_WAIT_FOR_HASHKEY,
  CRY_HMAC_G_S_HASHKEY_UPDATE,
  CRY_HMAC_G_S_WAIT_FOR_HASHKEY_UPDATE,
  CRY_HMAC_G_S_HASHKEY_FINISH,
  CRY_HMAC_G_S_WAIT_FOR_HASHKEY_FINISH,
  CRY_HMAC_G_S_HASHKEY_INIT,
  CRY_HMAC_G_S_WAIT_FOR_INIT1,
  CRY_HMAC_G_S_INIT2,
  CRY_HMAC_G_S_WAIT_FOR_INIT2,
  CRY_HMAC_G_S_INITIALIZED,
  CRY_HMAC_G_S_UPDATE,
  CRY_HMAC_G_S_WAIT_FOR_UPDATE,
  CRY_HMAC_G_S_FINISH1,
  CRY_HMAC_G_S_WAIT_FOR_FINISH1,
  CRY_HMAC_G_S_FINISH2,
  CRY_HMAC_G_S_WAIT_FOR_FINISH2,
  CRY_HMAC_G_S_FINISH3,
  CRY_HMAC_G_S_WAIT_FOR_FINISH3,
  CRY_HMAC_G_S_FINISH4,
  CRY_HMAC_G_S_WAIT_FOR_FINISH4,
  CRY_HMAC_G_S_FINISH5,
  CRY_HMAC_G_S_WAIT_FOR_FINISH5
}
Cry_HMACGenStateType;

/**
 *
 * \struct Cry_HMACGenCtxType
 * \brief Structure which contains the context of the HMAC generation
 *
 *//**
 * \var Cry_HMACGenCtxType::DataLength
 * \brief The length of the data to be signed.
 *//**
 * \var Cry_HMACGenCtxType::HashResultLength
 * \brief Length of HashResult.
 *//**
 * \var Cry_HMACGenCtxType::ProcessedKeyLength
 * \brief Length of ProcessedKey.
 *//**
 * \var Cry_HMACGenCtxType::CfgPtr
 * \brief A pointer to the current HMAC generation
 *        configuration which has to be used.
 *//**
 * \var Cry_HMACGenCtxType::KeyPtr
 * \brief A pointer to the secret key which should be used for creating the HMAC.
 *//**
 * \var Cry_HMACGenCtxType::Result
 * \brief A pointer to the start of a buffer where the created HMAC
 *        bytes should be stored.
 *//**
 * \var Cry_HMACGenCtxType::ResultLengthPtr
 * \brief A pointer to a variable which contains the maximal allowed
 *        space for the mac and where the length of the created mac
 *        should be stored.
 *//**
 * \var Cry_HMACGenCtxType::Data
 * \brief A pointer to the start of an array where the data to be signed is stored.
 *//**
 * \var Cry_HMACGenCtxType::State
 * \brief The current state the HMAC generation is in.
 *//**
 * \var Cry_HMACGenCtxType::TruncationIsAllowed
 * \brief Is truncation of the result allowed or should an error be
 *        returned when the Result buffer is too small.
 *//**
 * \var Cry_HMACGenCtxType::HashResult
 * \brief Array, where the hashed data is stored after hashing the inner padded key and the given
 *        message.
 *//**
 * \var Cry_HMACGenCtxType::ProcessedKey
 * \brief Holds the (hashed) key.
 */

/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                                    DataLength;
  uint32                                                    HashResultLength;
  uint32                                                    ProcessedKeyLength;
  P2VAR(uint32,                  TYPEDEF, CRY_APPL_DATA)    ResultLengthPtr;
  P2CONST(Cry_HMACKeyType,       TYPEDEF, CRY_APPL_DATA)    KeyPtr;
  P2CONST(Cry_HMACGenConfigType, TYPEDEF, CRY_APPL_DATA)    CfgPtr;
  P2VAR(uint8,                   TYPEDEF, CRY_APPL_DATA)    Result;
  P2CONST(uint8,                 TYPEDEF, CRY_APPL_DATA)    Data;
  Cry_HMACGenStateType                                      State;
  uint8                                                     HashResult[CRY_HMAC_HASH_MAX_LEN];
  uint8                                                     ProcessedKey[CRY_HMAC_HASH_BLOCK_LEN_BYTES];
  boolean                                                   TruncationIsAllowed;
}
Cry_HMACGenCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief State function: Copy the user-provided key in the "ProcessedKey" internal array
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStatePrepareKey(void);

/** \brief State function: Request starting of the underlying hashing algorithm
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateInit1(void);

/** \brief State function: Request update of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyUpdate(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyFinish(void);

/** \brief State function: Request starting of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyInit(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the key XORed with the inner pad
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateInit2(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the user-provided message
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateUpdate(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function finishes the inner hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish1(void);

/** \brief State function: Request starting of the underlying hashing algorithm.
 *         This state function initializes the hashing algorithm to compute the outer hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish2(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the key XORed with the outer pad
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish3(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the output of the inner hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish4(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function finishes the outer hash, which is the value of the HMAC
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish5(void);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/**
 *
 * \brief HMAC generation context
 *
 * The context variable which is used to store the internal state of the
 *  HMAC generation.
 *
 */
/* !LINKSTO EB_CRY_0024,1 */
STATIC VAR(Cry_HMACGenCtxType, CRY_VAR) Cry_HMACGenCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0125,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACGenStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA)   cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA)   keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if (CRY_HMAC_G_S_IDLE == Cry_HMACGenCtx.State)
  {
    Cry_HMACGenCtx.CfgPtr =
      (P2CONST(Cry_HMACGenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
    /* !LINKSTO CS_SECURE_CRY_0194,1 */
   /* Deviation MISRAC2012-1 */
    Cry_HMACGenCtx.KeyPtr =
      (P2CONST(Cry_HMACKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_PREPAREKEY;

    RetVal = CSM_E_OK;
  }
  else
  {
      RetVal = CSM_E_BUSY;
  }
#else
  Cry_HMACGenCtx.CfgPtr =
    (P2CONST(Cry_HMACGenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
  /* !LINKSTO CS_SECURE_CRY_0194,1 */
  /* Deviation MISRAC2012-1 */
  Cry_HMACGenCtx.KeyPtr =
    (P2CONST(Cry_HMACKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_PREPAREKEY;

  RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0126,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACGenUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if (CRY_HMAC_G_S_IDLE == Cry_HMACGenCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_HMAC_G_S_INITIALIZED == Cry_HMACGenCtx.State)
  {
    /* Store data into context */
    Cry_HMACGenCtx.Data = dataPtr;
    Cry_HMACGenCtx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_UPDATE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0127,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACGenFinish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 TruncationIsAllowed
)
{
  Csm_ReturnType RetVal;

  if (CRY_HMAC_G_S_IDLE == Cry_HMACGenCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_HMAC_G_S_INITIALIZED == Cry_HMACGenCtx.State)
  {
    /* Store data into context */
    Cry_HMACGenCtx.Result = resultPtr;
    Cry_HMACGenCtx.ResultLengthPtr = resultLengthPtr;
    Cry_HMACGenCtx.TruncationIsAllowed = TruncationIsAllowed;
    /* Set state of the state machine to finish */
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH1;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0128,1 */
FUNC(void, CRY_CODE) Cry_HMACGenMainFunction
(
  void
)
{
  switch(Cry_HMACGenCtx.State)
  {
    case CRY_HMAC_G_S_PREPAREKEY:
      Cry_HMACGenStatePrepareKey();
    break;

    case CRY_HMAC_G_S_INIT1:
      Cry_HMACGenStateInit1();
    break;

    case CRY_HMAC_G_S_HASHKEY_UPDATE:
      Cry_HMACGenStateHashKeyUpdate();
    break;

    case CRY_HMAC_G_S_HASHKEY_FINISH:
      Cry_HMACGenStateHashKeyFinish();
    break;

    case CRY_HMAC_G_S_HASHKEY_INIT:
      Cry_HMACGenStateHashKeyInit();
    break;

    case CRY_HMAC_G_S_INIT2:
      Cry_HMACGenStateInit2();
    break;

    case CRY_HMAC_G_S_UPDATE:
      Cry_HMACGenStateUpdate();
    break;

    case CRY_HMAC_G_S_FINISH1:
      Cry_HMACGenStateFinish1();
    break;

    case CRY_HMAC_G_S_FINISH2:
      Cry_HMACGenStateFinish2();
    break;

    case CRY_HMAC_G_S_FINISH3:
      Cry_HMACGenStateFinish3();
    break;

    case CRY_HMAC_G_S_FINISH4:
      Cry_HMACGenStateFinish4();
    break;

    case CRY_HMAC_G_S_FINISH5:
      Cry_HMACGenStateFinish5();
    break;

    case CRY_HMAC_G_S_INITIALIZED:
    case CRY_HMAC_G_S_WAIT_FOR_HASHKEY:
    case CRY_HMAC_G_S_WAIT_FOR_HASHKEY_UPDATE:
    case CRY_HMAC_G_S_WAIT_FOR_HASHKEY_FINISH:
    case CRY_HMAC_G_S_WAIT_FOR_INIT1:
    case CRY_HMAC_G_S_WAIT_FOR_INIT2:
    case CRY_HMAC_G_S_WAIT_FOR_UPDATE:
    case CRY_HMAC_G_S_WAIT_FOR_FINISH1:
    case CRY_HMAC_G_S_WAIT_FOR_FINISH2:
    case CRY_HMAC_G_S_WAIT_FOR_FINISH3:
    case CRY_HMAC_G_S_WAIT_FOR_FINISH4:
    case CRY_HMAC_G_S_WAIT_FOR_FINISH5:
    default:
    {
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStatePrepareKey
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0198_KeySizeSmallerThanBlockSize,1 */
  if (CRY_HMAC_HASH_BLOCK_LEN_BYTES >= Cry_HMACGenCtx.KeyPtr->KeyLength)
  {
    uint8 BytesDone = (uint8)0U;

    Cry_HMACGenCtx.ProcessedKeyLength = (uint32)Cry_HMACGenCtx.KeyPtr->KeyLength;

    do
    {
      Cry_HMACGenCtx.ProcessedKey[BytesDone] =
        (((uint8)Cry_HMACGenCtx.KeyPtr->Key[BytesDone]));
      BytesDone++;
    } while (BytesDone < (uint8)Cry_HMACGenCtx.ProcessedKeyLength);
  }

  Cry_HMACGenCtx.State = CRY_HMAC_G_S_INIT1;
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateInit1
(
  void
)
{
  /* Check key length */
  if (Cry_HMACGenCtx.KeyPtr->KeyLength > CRY_HMAC_HASH_BLOCK_LEN_BYTES)
  {
    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeLargerThanBlockSize,1 */
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_HASHKEY;
  }
  else
  {
    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeSmallerThanBlockSize,1 */

    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeEqualToBlockSize,1 */
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_INIT1;
  }

  /* Initialize the underlying Hash Algorithm */
  switch(Csm_HashStart(Cry_HMACGenCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_INIT1;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyUpdate
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0198_KeySizeLargerThanBlockSize,1 */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_HASHKEY_UPDATE;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.KeyPtr->Key,
                    Cry_HMACGenCtx.KeyPtr->KeyLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_UPDATE;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyFinish
(
  void
)
{
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_HASHKEY_FINISH;
  Cry_HMACGenCtx.ProcessedKeyLength = sizeof(Cry_HMACGenCtx.HashResult);
  switch
  (
    Csm_HashFinish(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.ProcessedKey,
                    &(Cry_HMACGenCtx.ProcessedKeyLength),
                    FALSE
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_FINISH;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateHashKeyInit
(
  void
)
{
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_INIT1;
  switch(Csm_HashStart(Cry_HMACGenCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_INIT;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateInit2
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0200,1 */
  /* Bring the new key into the context of the hash algorithm */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_INIT2;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.ProcessedKey,
                    CRY_HMAC_HASH_BLOCK_LEN_BYTES
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_INIT2;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateUpdate
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0200,1 */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_UPDATE;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.Data,
                    Cry_HMACGenCtx.DataLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_UPDATE;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish1
(
  void
)
{
  /* Finish the hashing function and receive the hashed value */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_FINISH1;
  Cry_HMACGenCtx.HashResultLength = sizeof(Cry_HMACGenCtx.HashResult);
  switch
  (
    Csm_HashFinish(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.HashResult,
                    &(Cry_HMACGenCtx.HashResultLength),
                    FALSE
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH1;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish2
(
  void
)
{
  /* Initialize the hash interface again for the computation of the outer padding */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_FINISH2;
  switch(Csm_HashStart(Cry_HMACGenCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH2;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish3
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0202,1 */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_FINISH3;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.ProcessedKey,
                    CRY_HMAC_HASH_BLOCK_LEN_BYTES
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH3;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish4
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0202,1 */
  /* Update Hash context with inner hash value */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_FINISH4;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.HashResult,
                    Cry_HMACGenCtx.HashResultLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH4;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACGenStateFinish5
(
  void
)
{
  /* Compute the outer digest == MAC */
  Cry_HMACGenCtx.State = CRY_HMAC_G_S_WAIT_FOR_FINISH5;
  switch
  (
    Csm_HashFinish(
                    Cry_HMACGenCtx.CfgPtr->HashCfg,
                    Cry_HMACGenCtx.Result,
                    Cry_HMACGenCtx.ResultLengthPtr,
                    Cry_HMACGenCtx.TruncationIsAllowed
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH5;
    break;

    default:
    {
      CRY_HMAC_G_HANDLE_FAILING_HASH;
      break;
    }
  }
}

/**
 *
 * \brief Callback function for called subservices
 *
 * Several CSM sub-services are called during the signature generation and
 * since each service calls a callback function to inform the caller that it
 * has finished, this primitive must provide such a callback.  The name of this function has to be
 * used in the configuration of the callback function of the relevand CSM sub-service.
 *
 * \param[in]  result: The result of the called sub-service.
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
FUNC(Std_ReturnType, CRY_CODE) Cry_HMACGenCallback
(
  Csm_ReturnType Result
)
{
  if (Result != CSM_E_OK)
  {
    Cry_HMACGenCtx.State = CRY_HMAC_G_S_IDLE;

    /* !LINKSTO CSM0454, 1
     */
    Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);

    /* !LINKSTO CSM0454, 1
     */
    Csm_MacGenerateServiceFinishNotification();
  }
  else
  {
    switch(Cry_HMACGenCtx.State)
    {
      case CRY_HMAC_G_S_WAIT_FOR_INIT1:
      {
        uint8 BytesDone = (uint8)0U;

        /* !LINKSTO CS_SECURE_CRY_0199,1 */
        /* Fill the pad buffer */
        do
        {
          Cry_HMACGenCtx.ProcessedKey[BytesDone] =
             (((uint8)Cry_HMACGenCtx.ProcessedKey[BytesDone]) ^ ((uint8)CRY_HMAC_IPAD));
          BytesDone++;
        } while ((BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES) &&
                 (BytesDone < (uint8)Cry_HMACGenCtx.ProcessedKeyLength));

        /* Fill the rest of buffer with the ipad */
        while (BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES)
        {
          Cry_HMACGenCtx.ProcessedKey[BytesDone] = (uint8)CRY_HMAC_IPAD;
          BytesDone++;
        }

        Cry_HMACGenCtx.State = CRY_HMAC_G_S_INIT2;
      }
      break;

      case CRY_HMAC_G_S_WAIT_FOR_HASHKEY:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_UPDATE;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_HASHKEY_UPDATE:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_FINISH;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_HASHKEY_FINISH:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_HASHKEY_INIT;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_INIT2:
      case CRY_HMAC_G_S_WAIT_FOR_UPDATE:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_INITIALIZED;
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacGenerateCallbackNotification(CSM_E_OK);
      break;

      case CRY_HMAC_G_S_WAIT_FOR_FINISH1:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH2;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_FINISH2:
      {
        uint8 BytesDone = (uint8)0U;
        uint8 IpadXorOpad = (((uint8)CRY_HMAC_OPAD) ^ ((uint8)CRY_HMAC_IPAD));

        /* !LINKSTO CS_SECURE_CRY_0201,1 */
        /* Fill the pad buffer of HashResult, but no more than 63 bytes */
        do
        {
           Cry_HMACGenCtx.ProcessedKey[BytesDone] =
              (uint8)((uint8)(Cry_HMACGenCtx.ProcessedKey[BytesDone]) ^ (IpadXorOpad));
           BytesDone++;
        } while (BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES);

        Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH3;
      }
      break;

      case CRY_HMAC_G_S_WAIT_FOR_FINISH3:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH4;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_FINISH4:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_FINISH5;
      break;

      case CRY_HMAC_G_S_WAIT_FOR_FINISH5:
        Cry_HMACGenCtx.State = CRY_HMAC_G_S_IDLE;
        /* !LINKSTO CSM0454, 1
        */
        Csm_MacGenerateCallbackNotification(CSM_E_OK);

        /* !LINKSTO CSM0454, 1
        */
        Csm_MacGenerateServiceFinishNotification();
      break;

      default:
      {
        break;
      }
    }
  }

  return CSM_E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if (CRY_HMAC_GEN_ENABLED == TRUE) */

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

typedef uint8 Cry_HMACGen_PrvtEmptyTranslationUnitType;

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

#endif /* #if (CRY_HMAC_GEN_ENABLED == TRUE) #else */
