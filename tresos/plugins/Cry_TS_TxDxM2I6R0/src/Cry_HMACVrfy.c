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
#include <Cry_HMACVrfy.h>  /* !LINKSTO EB_CRY_0005,1 */

#if (CRY_HMAC_VRFY_ENABLED == TRUE)

/*==[Macros]==================================================================*/

#if (defined CRY_HMAC_V_HANDLE_FAILING_HASH)
#error CRY_HMAC_V_HANDLE_FAILING_HASH is already defined
#endif
/** \brief Clears the state of the HMAC verify algorithm and calls the
 **         Csm callbacks after a rejected hash operation
 **/
#define CRY_HMAC_V_HANDLE_FAILING_HASH                \
  do                                                  \
  {                                                   \
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_IDLE;          \
                                                      \
  Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);    \
                                                      \
  Csm_MacVerifyServiceFinishNotification();           \
  } while (0)

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_HMACVrfyStateType
 * \brief Enumeration of the internal states of the HMAC verification.
 *
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_IDLE
 * \brief Idle state of the HMAC routine.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_PREPAREKEY
 * \brief Copy the user-provided key to the "ProcessedKey" array
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_INIT1
 * \brief The underlying Hash Algorithm gets initialized.
 *        if the key is longer than CRY_HMAC_HASH_BLOCK_LEN_BYTES,
 *        CRY_HMAC_V_S_WAIT_FOR_HASHKEY is the next state. Otherwise
 *        CRY_HMAC_V_S_WAIT_FOR_INIT1 is the next state.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_HASHKEY
 * \brief If the given key is too long, it must be hshed.
 *        The routine waits in this state, for the initialized Hash algorithm.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_HASHKEY_UPDATE
 * \brief The key is given to the hash routine.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_HASHKEY_UPDATE
 * \brief Waiting for the hashroutine to handle the key.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_HASHKEY_FINISH
 * \brief The hash routine gets finished for the hashing of the key.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_HASHKEY_FINISH
 * \brief The routine is waiting for the underlying hash algorithm
 *        to finish processing of the key hash.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_HASHKEY_INIT
 * \brief The underlying hash routine has to be initilised again.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_INIT1
 * \brief The routine waits in this state, for the initialized Hash algorithm.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_INIT2
 * \brief Inner padding. Update the hash routine with the padded key.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_INIT2
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_INITIALIZED
 * \brief The HMAC routine is initialized..
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_UPDATE
 * \brief Update the hash algorithm with the given message.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_UPDATE
 * \brief Wait for the input message to be hashed.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_FINISH1
 * \brief Finish processing the hash with the inner padded key and the message.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_FINISH1
 * \brief The routine is waiting for the
 *        underlying hash algorithm to finish processing of the hash.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_FINISH2
 * \brief The underlying hash algorithm is initialized again.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_FINISH2
 * \brief The routine waits in this state, for the initialized Hash algorithm.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_FINISH3
 * \brief Outer padding. Update the hash routine with the padded.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_FINISH3
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_FINISH4
 * \brief Update the hashroutine with the hash result of calculated
 *        within state CRY_HMAC_V_S_FINISH1.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_FINISH4
 * \brief Wait for the hash routine to process the update.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_WAIT_FOR_FINISH5
 * \brief The routine is waiting for the
 *        underlying hash algorithm to finish processing of the hash.
 *//**
 * \var Cry_HMACVrfyStateType::CRY_HMAC_V_S_FINISH_COMPARE
 * \brief Compare HashResult with the Mac Buffer.
 */
typedef enum
{
  CRY_HMAC_V_S_IDLE,
  CRY_HMAC_V_S_PREPAREKEY,
  CRY_HMAC_V_S_INIT1,
  CRY_HMAC_V_S_WAIT_FOR_HASHKEY,
  CRY_HMAC_V_S_HASHKEY_UPDATE,
  CRY_HMAC_V_S_WAIT_FOR_HASHKEY_UPDATE,
  CRY_HMAC_V_S_HASHKEY_FINISH,
  CRY_HMAC_V_S_WAIT_FOR_HASHKEY_FINISH,
  CRY_HMAC_V_S_HASHKEY_INIT,
  CRY_HMAC_V_S_WAIT_FOR_INIT1,
  CRY_HMAC_V_S_INIT2,
  CRY_HMAC_V_S_WAIT_FOR_INIT2,
  CRY_HMAC_V_S_INITIALIZED,
  CRY_HMAC_V_S_UPDATE,
  CRY_HMAC_V_S_WAIT_FOR_UPDATE,
  CRY_HMAC_V_S_FINISH1,
  CRY_HMAC_V_S_WAIT_FOR_FINISH1,
  CRY_HMAC_V_S_FINISH2,
  CRY_HMAC_V_S_WAIT_FOR_FINISH2,
  CRY_HMAC_V_S_FINISH3,
  CRY_HMAC_V_S_WAIT_FOR_FINISH3,
  CRY_HMAC_V_S_FINISH4,
  CRY_HMAC_V_S_WAIT_FOR_FINISH4,
  CRY_HMAC_V_S_FINISH5,
  CRY_HMAC_V_S_WAIT_FOR_FINISH5,
  CRY_HMAC_V_S_FINISH_COMPARE
}
Cry_HMACVrfyStateType;

/**
 *
 * \struct Cry_HMACVrfyCtxType
 * \brief Structure which contains the context of the HMAC verification
 *
 *//**
 * \var Cry_HMACVrfyCtxType::MacLength
 * \brief The length of the signature to verify.
 *//**
 * \var Cry_HMACVrfyCtxType::DataLength
 * \brief The length of the data.
 *//**
 * \var Cry_HMACVrfyCtxType::HashResultLength
 * \brief The length of HashResult.
 *//**
 * \var Cry_HMACVrfyCtxType::ProcessedKeyLength
 * \brief Length of ProcessedKey.
 *//**
 * \var Cry_HMACVrfyCtxType::KeyPtr
 * \brief A pointer to the public key which should be used for verifying the
    signature.
 *//**
 * \var Cry_HMACVrfyCtxType::CfgPtr
 * \brief A pointer to the current HMAC verification
 *        configuration which is used.
 *//**
 * \var Cry_HMACVrfyCtxType::ResultPtr
 * \brief A pointer to a variable where the signature verification result
 *        has to be stored.
 *//**
 * \var Cry_HMACVrfyCtxType::Mac
 * \brief A pointer to the start of a buffer where the signature to verify
 *        is stored.
 *//**
 * \var Cry_HMACVrfyCtxType::Data
 * \brief A pointer to the start of an array where the data whose signature to
 *        verify is stored.
 *//**
 * \var Cry_HMACVrfyCtxType::State
 * \brief The current state in which is the HMAC verification.
 *//**
 * \var Cry_HMACVrfyCtxType::HashResult
 * \brief Array, where the hashed data is stored after hashing the inner
 *        padded key and the given message.
 *//**
 * \var Cry_HMACVrfyCtxType::ProcessedKey
 * \brief Holds the (hashed) key.
 */
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                                     MacLength;
  uint32                                                     DataLength;
  uint32                                                     HashResultLength;
  uint32                                                     ProcessedKeyLength;
  P2CONST(Cry_HMACKeyType,        TYPEDEF, CRY_APPL_DATA)    KeyPtr;
  P2CONST(Cry_HMACVrfyConfigType, TYPEDEF, CRY_APPL_DATA)    CfgPtr;
  P2VAR(Csm_VerifyResultType,     TYPEDEF, CRY_APPL_DATA)    ResultPtr;
  P2CONST(uint8,                  TYPEDEF, CRY_APPL_DATA)    Mac;
  P2CONST(uint8,                  TYPEDEF, CRY_APPL_DATA)    Data;
  Cry_HMACVrfyStateType                                      State;
  uint8                                                      HashResult[CRY_HMAC_HASH_MAX_LEN];
  uint8                                                      ProcessedKey[CRY_HMAC_HASH_BLOCK_LEN_BYTES];
}
Cry_HMACVrfyCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief State function: Copy the user-provided key in the "ProcessedKey" internal array
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStatePrepareKey(void);

/** \brief State function: Request starting of the underlying hashing algorithm
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateInit1(void);

/** \brief State function: Request update of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyUpdate(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyFinish(void);

/** \brief State function: Request starting of the underlying hashing algorithm.
 *         This state function is used only if the key length exceeds the
 *         hashing algorithm block length
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyInit(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the key XORed with the inner pad
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateInit2(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the user-provided message
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateUpdate(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function finishes the inner hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish1(void);

/** \brief State function: Request starting of the underlying hashing algorithm.
 *         This state function initializes the hashing algorithm to compute the outer hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish2(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the key XORed with the outer pad
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish3(void);

/** \brief State function: Request updating of the underlying hashing algorithm.
 *         This state function hashes the output of the inner hash
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish4(void);

/** \brief State function: Request finishing of the underlying hashing algorithm.
 *         This state function finishes the outer hash, which is the value of the HMAC
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish5(void);

/** \brief Compares the calculated and the provided MAC.
 *
 * \return MAC comparison result
 *
 * \retval E_OK      The value of the calculated MAC matches the provided MAC.
 * \retval E_NOT_OK  The value of the calculated MAC does not match the provided MAC.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous}
 */
static FUNC(Csm_ReturnType, CRY_CODE)Cry_HMACVrfyCompareHMAC(void);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/**
 *
 * \brief HMAC verification context
 *
 * The context variable which is used to store the internal state of the
 * HMAC verification.
 *
 */
/* !LINKSTO EB_CRY_0024,1 */
STATIC VAR(Cry_HMACVrfyCtxType, CRY_VAR) Cry_HMACVrfyCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0129,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACVrfyStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA)        cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA)        keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_HMAC_VRFY_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if (CRY_HMAC_V_S_IDLE == Cry_HMACVrfyCtx.State)
  {
    Cry_HMACVrfyCtx.CfgPtr =
       (P2CONST(Cry_HMACVrfyConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
    /* !LINKSTO CS_SECURE_CRY_0194,1 */
   /* Deviation MISRAC2012-1 */
    Cry_HMACVrfyCtx.KeyPtr =
       (P2CONST(Cry_HMACKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_PREPAREKEY;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  Cry_HMACVrfyCtx.CfgPtr =
     (P2CONST(Cry_HMACVrfyConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
  /* !LINKSTO CS_SECURE_CRY_0194,1 */
  /* Deviation MISRAC2012-1 */
  Cry_HMACVrfyCtx.KeyPtr =
     (P2CONST(Cry_HMACKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;

  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_PREPAREKEY;

  RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0130,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACVrfyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if (CRY_HMAC_V_S_IDLE == Cry_HMACVrfyCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_HMAC_V_S_INITIALIZED == Cry_HMACVrfyCtx.State)
  {
    /* Store data into context */
    Cry_HMACVrfyCtx.Data = dataPtr;
    Cry_HMACVrfyCtx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_UPDATE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0131,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACVrfyFinish
(
  P2CONST(uint8, AUTOMATIC,     CRY_APPL_DATA)                  authenticationPtr,
          uint32                                                authenticationLength,
  P2VAR  (Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA)       resultPtr
)
{
  Csm_ReturnType RetVal;

  if (CRY_HMAC_V_S_IDLE == Cry_HMACVrfyCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_HMAC_V_S_INITIALIZED == Cry_HMACVrfyCtx.State)
  {
    /* Store data into context */
    Cry_HMACVrfyCtx.ResultPtr = resultPtr;
    Cry_HMACVrfyCtx.HashResultLength = authenticationLength;
    Cry_HMACVrfyCtx.MacLength = authenticationLength;
    Cry_HMACVrfyCtx.Mac = authenticationPtr;
    /* Set state of the state machine to finish */
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH1;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0132,1 */
FUNC(void, CRY_CODE) Cry_HMACVrfyMainFunction
(
  void
)
{
  switch(Cry_HMACVrfyCtx.State)
  {
    case CRY_HMAC_V_S_PREPAREKEY:
      Cry_HMACVrfyStatePrepareKey();
    break;

    case CRY_HMAC_V_S_INIT1:
      Cry_HMACVrfyStateInit1();
    break;

    case CRY_HMAC_V_S_HASHKEY_UPDATE:
      Cry_HMACVrfyStateHashKeyUpdate();
    break;

    case CRY_HMAC_V_S_HASHKEY_FINISH:
      Cry_HMACVrfyStateHashKeyFinish();
    break;

    case CRY_HMAC_V_S_HASHKEY_INIT:
      Cry_HMACVrfyStateHashKeyInit();
    break;

    case CRY_HMAC_V_S_INIT2:
      Cry_HMACVrfyStateInit2();
    break;

    case CRY_HMAC_V_S_UPDATE:
      Cry_HMACVrfyStateUpdate();
    break;

    case CRY_HMAC_V_S_FINISH1:
      Cry_HMACVrfyStateFinish1();
    break;

    case CRY_HMAC_V_S_FINISH2:
      Cry_HMACVrfyStateFinish2();
    break;

    case CRY_HMAC_V_S_FINISH3:
      Cry_HMACVrfyStateFinish3();
    break;

    case CRY_HMAC_V_S_FINISH4:
      Cry_HMACVrfyStateFinish4();
    break;

    case CRY_HMAC_V_S_FINISH5:
      Cry_HMACVrfyStateFinish5();
    break;

    case CRY_HMAC_V_S_FINISH_COMPARE:
      if(Cry_HMACVrfyCompareHMAC() == CSM_E_OK)
      {
        /* !LINKSTO CS_SECURE_CRY_0203_VerificationSucceded,1 */
        *Cry_HMACVrfyCtx.ResultPtr = CSM_E_VER_OK;
      }
      else
      {
        /* !LINKSTO CS_SECURE_CRY_0203_VerificationFailed,1 */
        *Cry_HMACVrfyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }

      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_OK);

      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    break;

    case CRY_HMAC_V_S_INITIALIZED:
    case CRY_HMAC_V_S_WAIT_FOR_HASHKEY:
    case CRY_HMAC_V_S_WAIT_FOR_HASHKEY_UPDATE:
    case CRY_HMAC_V_S_WAIT_FOR_HASHKEY_FINISH:
    case CRY_HMAC_V_S_WAIT_FOR_INIT1:
    case CRY_HMAC_V_S_WAIT_FOR_INIT2:
    case CRY_HMAC_V_S_WAIT_FOR_UPDATE:
    case CRY_HMAC_V_S_WAIT_FOR_FINISH1:
    case CRY_HMAC_V_S_WAIT_FOR_FINISH2:
    case CRY_HMAC_V_S_WAIT_FOR_FINISH3:
    case CRY_HMAC_V_S_WAIT_FOR_FINISH4:
    case CRY_HMAC_V_S_WAIT_FOR_FINISH5:
    default:
    {
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStatePrepareKey
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0198_KeySizeSmallerThanBlockSize,1 */
  if (CRY_HMAC_HASH_BLOCK_LEN_BYTES >= Cry_HMACVrfyCtx.KeyPtr->KeyLength)
  {
    uint8 BytesDone = (uint8)0U;

    Cry_HMACVrfyCtx.ProcessedKeyLength = (uint32)Cry_HMACVrfyCtx.KeyPtr->KeyLength;

    do
    {
      Cry_HMACVrfyCtx.ProcessedKey[BytesDone] =
        (((uint8)Cry_HMACVrfyCtx.KeyPtr->Key[BytesDone]));
      BytesDone++;
    } while (BytesDone < (uint8)Cry_HMACVrfyCtx.ProcessedKeyLength);
  }

  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_INIT1;
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateInit1
(
  void
)
{
  /* Check key length */
  if(Cry_HMACVrfyCtx.KeyPtr->KeyLength > CRY_HMAC_HASH_BLOCK_LEN_BYTES)
  {
    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeLargerThanBlockSize,1 */
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_HASHKEY;
  }
  else
  {
    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeSmallerThanBlockSize,1 */

    /* !LINKSTO CS_SECURE_CRY_0198_KeySizeEqualToBlockSize,1 */
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_INIT1;
  }

  /* Initialize the underlying Hash Algorithm */
  switch(Csm_HashStart(Cry_HMACVrfyCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_INIT1;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyUpdate
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0198_KeySizeLargerThanBlockSize,1 */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_HASHKEY_UPDATE;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.KeyPtr->Key,
                    Cry_HMACVrfyCtx.KeyPtr->KeyLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_UPDATE;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyFinish
(
  void
)
{
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_HASHKEY_FINISH;
  Cry_HMACVrfyCtx.ProcessedKeyLength = sizeof(Cry_HMACVrfyCtx.HashResult);
  switch
  (
    Csm_HashFinish(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.ProcessedKey,
                    &(Cry_HMACVrfyCtx.ProcessedKeyLength),
                    FALSE
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_FINISH;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateHashKeyInit
(
  void
)
{
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_INIT1;
  switch(Csm_HashStart(Cry_HMACVrfyCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_INIT;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateInit2
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0200,1 */
  /* Bring the new key into the context of the hash algorithm */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_INIT2;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.ProcessedKey,
                    CRY_HMAC_HASH_BLOCK_LEN_BYTES
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_INIT2;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateUpdate
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0200,1 */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_UPDATE;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.Data,
                    Cry_HMACVrfyCtx.DataLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_UPDATE;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish1
(
  void
)
{
  /* Finish the hashing function and receive the hashed value */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_FINISH1;
  Cry_HMACVrfyCtx.HashResultLength = sizeof(Cry_HMACVrfyCtx.HashResult);
  switch
  (
    Csm_HashFinish(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.HashResult,
                    &(Cry_HMACVrfyCtx.HashResultLength),
                    FALSE
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH1;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish2
(
  void
)
{
  /* Initialize the hash interface again for the computation of the outer padding */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_FINISH2;
  switch(Csm_HashStart(Cry_HMACVrfyCtx.CfgPtr->HashCfg))
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
       Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH2;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish3
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0202,1 */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_FINISH3;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.ProcessedKey,
                    CRY_HMAC_HASH_BLOCK_LEN_BYTES
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH3;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish4
(
  void
)
{
  /* !LINKSTO CS_SECURE_CRY_0202,1 */
  /* Update Hash context with inner hash value */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_FINISH4;
  switch
  (
    Csm_HashUpdate(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.HashResult,
                    Cry_HMACVrfyCtx.HashResultLength
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH4;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_HMACVrfyStateFinish5
(
  void
)
{
  /* Compute the outer digest == MAC */
  Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_WAIT_FOR_FINISH5;
  switch
  (
    Csm_HashFinish(
                    Cry_HMACVrfyCtx.CfgPtr->HashCfg,
                    Cry_HMACVrfyCtx.HashResult,
                    &(Cry_HMACVrfyCtx.HashResultLength),
                    FALSE
                  )
  )
  {
    case CSM_E_OK:
    break;

    case CSM_E_BUSY:
      Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH5;
    break;

    default:
    {
      CRY_HMAC_V_HANDLE_FAILING_HASH;
      break;
    }
  }
}

 /**
 *
 * \brief Cry_HMACVrfyCompareHMAC
 *
 * Compares the calculated and the given Mac.
 *
 * \return Error code
 *
 * \retval CSM_E_OK      If the value calculated and the Mac are matching.
 * \retval CSM_E_NOT_OK  If the values are different.
 *
 *
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
static FUNC(Csm_ReturnType, CRY_CODE) Cry_HMACVrfyCompareHMAC(void)
{
  Csm_ReturnType RetVal = CSM_E_OK;
  uint8 i;
  uint8 Mask;

  /* Compare whole bytes */
  if((Cry_HMACVrfyCtx.HashResultLength * 8U) >= Cry_HMACVrfyCtx.MacLength)
  {
    for (i = 0U; i < (Cry_HMACVrfyCtx.MacLength / 8U); i++)
    {
      if (Cry_HMACVrfyCtx.Mac[i] != Cry_HMACVrfyCtx.HashResult[i])
      {
        RetVal = CSM_E_NOT_OK;
      }
    }

    /* Compare rest of bits */
    if (0U < (Cry_HMACVrfyCtx.MacLength % 8U))
    {
      Mask = 0x00U;

      for (i = 0U; i < (Cry_HMACVrfyCtx.MacLength % 8U); i++)
      {
        Mask = (Mask >> 1U) + 0x80U;
      }

      if (
          (
            (Cry_HMACVrfyCtx.Mac[(Cry_HMACVrfyCtx.MacLength / 8U)]) & Mask
          ) !=
          (
            (Cry_HMACVrfyCtx.HashResult[(Cry_HMACVrfyCtx.MacLength / 8U)]) & Mask
          )
         )
      {
        RetVal = CSM_E_NOT_OK;
      }
    }
  }
  else
  {
      RetVal = CSM_E_NOT_OK;
  }

  return RetVal;
}

/**
 *
 * \brief Callback function for called subservices
 *
 * Several CSM sub-services are called during the signature verification and
 * since each service calls a callback function to inform the caller that it
 * has finished, this primitive must provide such a callback. The name of this function has to be used in the
 * configuration of the callback function of the relevand CSM sub-service.
 *
 * \param[in]  result: The result of the called sub-service.
 * \Reentrancy{Not reentrant}
 * \Synchronicity{Asynchronous}
 */
FUNC(Std_ReturnType, CRY_CODE) Cry_HMACVrfyCallback
(
   Csm_ReturnType Result
)
{
  if (Result != CSM_E_OK)
  {
    Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_IDLE;

    /* !LINKSTO CSM0454, 1
     */
    Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);

    /* !LINKSTO CSM0454, 1
     */
    Csm_MacVerifyServiceFinishNotification();
  }
  else
  {
    switch(Cry_HMACVrfyCtx.State)
    {
      case CRY_HMAC_V_S_WAIT_FOR_INIT1:
      {
        uint8 BytesDone = (uint8)0U;

        /* !LINKSTO CS_SECURE_CRY_0199,1 */
        /* Fill the pad buffer */
        do
        {
          Cry_HMACVrfyCtx.ProcessedKey[BytesDone] =
             (((uint8)Cry_HMACVrfyCtx.ProcessedKey[BytesDone]) ^ ((uint8)CRY_HMAC_IPAD));
          BytesDone++;
        } while ((BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES) &&
                 (BytesDone < (uint8)Cry_HMACVrfyCtx.ProcessedKeyLength));

        /* Fill the rest of buffer with the ipad */
        while (BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES)
        {
          Cry_HMACVrfyCtx.ProcessedKey[BytesDone] = (uint8)CRY_HMAC_IPAD;
          BytesDone++;
        }

        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_INIT2;
      }
      break;

      case CRY_HMAC_V_S_WAIT_FOR_HASHKEY:
         Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_UPDATE;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_HASHKEY_UPDATE:
         Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_FINISH;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_HASHKEY_FINISH:
         Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_HASHKEY_INIT;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_INIT2:
      case CRY_HMAC_V_S_WAIT_FOR_UPDATE:
        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_INITIALIZED;
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacVerifyCallbackNotification(CSM_E_OK);
      break;

      case CRY_HMAC_V_S_WAIT_FOR_FINISH1:
        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH2;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_FINISH2:
      {
        uint8 BytesDone = (uint8)0U;
        uint8 IpadXorOpad = (((uint8)CRY_HMAC_OPAD) ^ ((uint8)CRY_HMAC_IPAD));

        /* !LINKSTO CS_SECURE_CRY_0201,1 */
        /* Fill the pad buffer of HashResult, but no more than 63 bytes */
        do
        {
           Cry_HMACVrfyCtx.ProcessedKey[BytesDone] =
              (uint8)((uint8)(Cry_HMACVrfyCtx.ProcessedKey[BytesDone]) ^ (IpadXorOpad));
           BytesDone++;
        } while (BytesDone < (uint8)CRY_HMAC_HASH_BLOCK_LEN_BYTES);

        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH3;
      }
      break;

      case CRY_HMAC_V_S_WAIT_FOR_FINISH3:
        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH4;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_FINISH4:
        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH5;
      break;

      case CRY_HMAC_V_S_WAIT_FOR_FINISH5:
        Cry_HMACVrfyCtx.State = CRY_HMAC_V_S_FINISH_COMPARE;
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

#else /* #if (CRY_HMAC_VRFY_ENABLED == TRUE) */

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

typedef uint8 Cry_HMACVrfy_PrvtEmptyTranslationUnitType;

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

#endif /* #if (CRY_HMAC_VRFY_ENABLED == TRUE) #else */
