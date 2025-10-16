/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast should not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the original type.
 *
 *  MISRAC2012-2) Deviated Rule: 13.5 (required)
 *   "The right hand operand of a logical && or || operator shall not contain persistent side effects."
 *
 *   Reason:
 *   The MISRA rule is not violated. This is a constraint of the MISRA checker: When a function
 *   is called on the right hand side of a logical operator, the checker always raises this error
 *   because it does not know whether the function has side effects or not. In our case, none of
 *   the functions have side effects.
 */


/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_SignatureVerify.h>
#include <Csm.h>
#include <Cry_CommonConfig.h>
#include <Cry_Common.h>
#include <Cry_LN.h>                     /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Base64.h>                 /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_RsaSsaPssVerify.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_RsaSsaPssVerifyConfig.h>

#if (CRY_RSASSAPSSVERIFY_ENABLED == STD_ON)

#if (CRY_RSASSAPSSVERIFY_USE_CBK == STD_ON)
#include <Cry_RsaSsaPssVerifyCbk.h>
#endif

/*==[Macros]==================================================================*/

#if (defined CRY_RSASSA_PSS_HASH_MAX_LEN)
#error CRY_RSASSA_PSS_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes.
 */
#define CRY_RSASSA_PSS_HASH_MAX_LEN       32U

#if (defined CRY_RSASSA_PSS_SIG_MASK_CNT_LEN)
#error CRY_RSASSA_PSS_SIG_MASK_CNT_LEN is already defined
#endif
/** \brief The length of count unsed during MGF
 */
#define CRY_RSASSA_PSS_SIG_MASK_CNT_LEN   4U

#if (defined CRY_RSASSA_PSS_MAX_DB_LEN)
#error CRY_RSASSA_PSS_MAX_DB_LEN is already defined
#endif
/** \brief The maximum length to allocate of DB buffer. Not the actual size of DB
 */
#define CRY_RSASSA_PSS_MAX_DB_LEN        (CRY_RSAPUBKEY_NUM_LEN_BYTES)

#if (defined CRY_RSASSA_PSS_NULL_LEN)
#error CRY_RSASSA_PSS_NULL_LEN is already defined
#endif
/** \brief The length to zero padding during the final hash.
 */
#define CRY_RSASSA_PSS_NULL_LEN           8U

#if (defined CRY_RSASSA_PSS_DB_MSB_NULL_MASK)
#error CRY_RSASSA_PSS_DB_MSB_NULL_MASK is already defined
#endif
/** \brief The Masking of MSBs of DB. It is fixed in our case as this routine only
 *         supports lengths where the exponent of the RSA Key is exactly a multiple
 *         of 8.
 */
#define CRY_RSASSA_PSS_DB_MSB_NULL_MASK   0x80U

#if (defined CRY_RSASSA_PSS_EM_LAST_BYTE)
#error CRY_RSASSA_PSS_EM_LAST_BYTE is already defined
#endif
/** \brief The expected last byte of EM.
 */
#define CRY_RSASSA_PSS_EM_LAST_BYTE       0xbcU

#if (defined CRY_RSASSA_PSS_NULL_STRING_LENGTH)
#error CRY_RSASSA_PSS_NULL_STRING_LENGTH is already defined
#endif
/** \brief The length of the "Null String" used to compute a hash.
 */
#define CRY_RSASSA_PSS_NULL_STRING_LENGTH 8U

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_RsaSsaPssVerifyStateType
 * \brief Enumeration of the internal states of the RSASSA-PSS signature verification.
 *
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_IDLE
 * \brief The algorithm is in the idle state.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_INIT
 * \brief The initialization of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_INIT_WAIT
 * \brief The initialization of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_INITIALIZED
 * \brief The algorithm is initialized.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE
 * \brief The update operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE_WAIT
 * \brief The update operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINISH
 * \brief The finish operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINISH_WAIT
 * \brief The finish operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_START_EXP
 * \brief Starting the Exp calculation.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINISH_COMPUTE_MODEXP
 * \brief The expected signature shall be verified via modular exponentiation
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINISH_EXP
 * \brief Finishing the Exp calculation.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_START_MASK
 * \brief Starting the Mask Hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_START_MASK_WAIT
 * \brief Wait for the start Mask Hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE_MASK
 * \brief Update Mask Hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE_MASK_WAIT
 * \brief Wait for Update Mask Hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE_CNT_MASK
 * \brief Update Count for Mask Hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT
 * \brief Wait for Update Count for Mask Hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_END_MASK
 * \brief End the mask hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_END_MASK_WAIT
 * \brief Wait for the mask hash to end.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_DONE_MASK
 * \brief Final hash starting.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_DONE_MASK_WAIT
 * \brief Wait for Final hash start.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE
 * \brief Update the zeros in the final hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT
 * \brief Wait for Update the zeros in the final hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE
 * \brief Update the mask in the final hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT
 * \brief Wait for update to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE
 * \brief Update the Salt
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT
 * \brief Wait for Salt to update.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_FINISH
 * \brief Finish the final hash.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT
 * \brief Wait for final hash to finish.
 *//**
 * \var Cry_RsaSsaPssVerifyStateType::CRY_RSASSA_PSS_COMPARE
 * \brief State for signature comparison.
 *//**
 */
typedef enum
{
  CRY_RSASSA_PSS_IDLE,
  CRY_RSASSA_PSS_INIT,
  CRY_RSASSA_PSS_INIT_WAIT,
  CRY_RSASSA_PSS_INITIALIZED,
  CRY_RSASSA_PSS_UPDATE,
  CRY_RSASSA_PSS_UPDATE_WAIT,
  CRY_RSASSA_PSS_FINISH,
  CRY_RSASSA_PSS_FINISH_WAIT,
  CRY_RSASSA_PSS_START_EXP,
  CRY_RSASSA_PSS_FINISH_COMPUTE_MODEXP,
  CRY_RSASSA_PSS_FINISH_EXP,
  CRY_RSASSA_PSS_START_MASK,
  CRY_RSASSA_PSS_START_MASK_WAIT,
  CRY_RSASSA_PSS_UPDATE_MASK,
  CRY_RSASSA_PSS_UPDATE_MASK_WAIT,
  CRY_RSASSA_PSS_UPDATE_CNT_MASK,
  CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT,
  CRY_RSASSA_PSS_END_MASK,
  CRY_RSASSA_PSS_END_MASK_WAIT,
  CRY_RSASSA_PSS_DONE_MASK,
  CRY_RSASSA_PSS_DONE_MASK_WAIT,
  CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE,
  CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT,
  CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE,
  CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT,
  CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE,
  CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT,
  CRY_RSASSA_PSS_FINALHASH_FINISH,
  CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT,
  CRY_RSASSA_PSS_COMPARE
}
Cry_RsaSsaPssVerifyStateType;

/**
 * \struct Cry_RsaSsaPssVerifyCtxType
 * \brief Structure which contains the context of the RSASSA-PSS signature verification.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::SignatureLength
 * \brief The length of the signature to verify.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::DataLength
 * \brief The length of the data.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::HashResultLength
 * \brief The length of the hash value of the data.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::MaskHashResultLength
 * \brief The length of the mask hash value.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::sLen
 * \brief The length of the Salt.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::dbLen
 * \brief The length of the DB.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::MaskCnt
 * \brief The Count value for mask hash calculation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::MaskItr
 * \brief The value of mask hash iterations.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::maximumNumberOfSlices
 * \brief Maximum number of time slices used for Pss signature calculation.
 *//**
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::CfgPtr
 * \brief A pointer to the current RSASSA-PSS signature verification
 *        configuration which has to be used.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::KeyPtr
 * \brief A pointer to the public key which should be used for verifying the signature.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::Signature
 * \brief A pointer to the start of a buffer where the signature to verify is stored.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::ResultPtr
 * \brief A pointer to a variable where the signature verification result has to be stored.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::Data
 * \brief A pointer to the start of an array where the data whose signature to verify is stored.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::MaskCntStr
 * \brief Array where the count value is stored during the computation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::tmp1Value
 * \brief An array which is used as a buffer during signature verification.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::tmp5Value
 * \brief An array which is used as a buffer during signature verification.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::LNCtx
 * \brief The context which has to be used for long number arithmetic.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::State
 * \brief The current state the RSASSA-PSS signature verification is in.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::HashResult
 * \brief Array where the hash value of the
 *        data will be buffered during the computation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::Hashdash
 * \brief array where the hash value of the H'
 *        data will be buffered during the computation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::MaskHashPtr
 * \brief Temporary Pointer for the hash calculation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::dbMask
 * \brief Array where the maskedDB is stored during the computation.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::EM
 * \brief An array which is used as a buffer for the value "EM" during the signature verification.
 *//**
 * \var Cry_RsaSsaPssVerifyCtxType::RestartFlag
 * \brief Flag that states if the restart of the service is active.
 */
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                                           SignatureLength;
  uint32                                                           DataLength;
  uint32                                                           HashResultLength;
  uint32                                                           MaskHashResultLength;
  uint32                                                           sLen;
  uint32                                                           dblen;
  uint32                                                           MaskCnt;
  uint32                                                           MaskItr;
  uint32                                                           maximumNumberOfSlices;
  P2CONST(Cry_RsaSsaPssVerifyConfigType, TYPEDEF, CRY_APPL_DATA)   CfgPtr;
  P2CONST(Cry_RsaPublicKeyType,          TYPEDEF, CRY_APPL_DATA)   KeyPtr;
  P2CONST(uint8,                         TYPEDEF, CRY_APPL_DATA)   Signature;
  P2VAR(Csm_VerifyResultType,            TYPEDEF, CRY_APPL_DATA)   ResultPtr;
  P2CONST(uint8,                         TYPEDEF, CRY_APPL_DATA)   Data;
  P2VAR(uint8,                           TYPEDEF, CRY_APPL_DATA)   MaskHashPtr;
  Cry_LNWordType                                        tmp1Value[CRY_RSA_PUB_KEY_TEMP_LEN_WORDS];
  Cry_LNWordType                                        tmp5Value[CRY_RSAPUBKEY_NUM_LEN_WORDS];
  Cry_LNCtxType                                                    LNCtx;
  Cry_RsaSsaPssVerifyStateType                                     State;
  uint8                                                 HashResult[CRY_RSASSA_PSS_HASH_MAX_LEN];
  uint8                                                 Hashdash[CRY_RSASSA_PSS_HASH_MAX_LEN];
  uint8                                                 MaskCntStr[CRY_RSASSA_PSS_SIG_MASK_CNT_LEN];
  uint8                                                 dbMask[CRY_RSASSA_PSS_MAX_DB_LEN];
  uint8                                                 EM[CRY_RSAPUBKEY_NUM_LEN_BYTES];
  boolean                                                          RestartFlag;
}
Cry_RsaSsaPssVerifyCtxType;


/*==[Declaration of functions with internal linkage]==========================*/

#if (defined CRY_RSA_HASH_START)
#error CRY_RSA_HASH_START is already defined
#endif

/** \brief Helper macro which calls the Csm_HashStart function
 **
 ** This function calls the function Csm_HashStart and performs state
 ** transitions according to the return value of the function Csm_HashStart.
 **
 ** \retval None
 **/
#define CRY_RSA_HASH_START                                          \
  switch (Csm_HashStart(Cry_RsaSsaPssVerifyCtx.CfgPtr->HashCfg))    \
  {                                                                 \
    case CSM_E_OK:                                                  \
      break;                                                        \
    case CSM_E_BUSY:                                                \
      switch (Cry_RsaSsaPssVerifyCtx.State)                         \
      {                                                             \
        case CRY_RSASSA_PSS_INIT_WAIT:                              \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_INIT;       \
          break;                                                    \
        case CRY_RSASSA_PSS_START_MASK_WAIT:                        \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_START_MASK; \
          break;                                                    \
        case CRY_RSASSA_PSS_DONE_MASK_WAIT:                         \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_DONE_MASK;  \
          break;                                                    \
        default:                                                    \
        {                                                           \
          break;                                                    \
        }                                                           \
      }                                                             \
      break;                                                        \
    default:                                                        \
    {                                                               \
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_IDLE;           \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);        \
      Csm_SignatureVerifyServiceFinishNotification();               \
      break;                                                        \
    }                                                               \
  }

#if (defined CRY_RSA_HASH_UPDATE)
#error CRY_RSA_HASH_UPDATE is already defined
#endif

/** \brief Helper macro which calls the Csm_HashUpdate function
 **
 ** This function calls the function Csm_HashUpdate and performs state
 ** transitions according to the return value of the function Csm_HashUpdate.
 **
 ** \param[in] dataPtr Holds a pointer to the data to be hashed.
 **
 ** \param[in] dataLength Contains the number of bytes to be hashed.
 **
 ** \retval None
 **/
#define CRY_RSA_HASH_UPDATE(dataPtr, dataLength)                                           \
  switch (Csm_HashUpdate(Cry_RsaSsaPssVerifyCtx.CfgPtr->HashCfg, (dataPtr), (dataLength))) \
  {                                                                                        \
    case CSM_E_OK:                                                                         \
      break;                                                                               \
    case CSM_E_BUSY:                                                                       \
      switch (Cry_RsaSsaPssVerifyCtx.State)                                                \
      {                                                                                    \
        case CRY_RSASSA_PSS_UPDATE_WAIT:                                                   \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE;                            \
          break;                                                                           \
        case CRY_RSASSA_PSS_UPDATE_MASK_WAIT:                                              \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_MASK;                       \
          break;                                                                           \
        case CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT:                                          \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_CNT_MASK;                   \
          break;                                                                           \
        case CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT:                                    \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE;             \
          break;                                                                           \
        case CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT:                                    \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE;             \
          break;                                                                           \
        case CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT:                                    \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE;             \
          break;                                                                           \
        default:                                                                           \
        {                                                                                  \
          break;                                                                           \
        }                                                                                  \
      }                                                                                    \
      break;                                                                               \
    default:                                                                               \
    {                                                                                      \
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_IDLE;                                  \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);                               \
      Csm_SignatureVerifyServiceFinishNotification();                                      \
      break;                                                                               \
    }                                                                                      \
  }

#if (defined CRY_RSA_HASH_FINISH)
#error CRY_RSA_HASH_FINISH is already defined
#endif

/** \brief Helper macro which calls the Csm_HashFinish function
 **
 ** This function calls the function Csm_HashFinish and performs state
 ** transitions according to the return value of the function Csm_HashFinish.
 **
 ** \param[in] cfgId The Csm configuration which is used for the Hash computation.
 **
 ** \param[out] resultPtr Holds a pointer to the memory location which holds the
 **                       result of the hash value computation. If the result does
 **                       not fit into the given buffer, and truncation is allowed,
 **                       the result is truncated.
 **
 ** \param[in,out] resLenPtr Holds a pointer to the memory location in which the
 **                          length information is stored. On calling this function
 **                          this parameter must contain the size of the buffer
 **                          provided by resultPtr. When the request has finished,
 **                          the actual length of the result is stored here.
 **
 ** \retval None
 **/
#define CRY_RSA_HASH_FINISH(resPtr, resLenPtr)                                                  \
  switch (Csm_HashFinish(Cry_RsaSsaPssVerifyCtx.CfgPtr->HashCfg, (resPtr), (resLenPtr), FALSE)) \
  {                                                                                             \
    case CSM_E_OK:                                                                              \
      break;                                                                                    \
    case CSM_E_BUSY:                                                                            \
      switch (Cry_RsaSsaPssVerifyCtx.State)                                                     \
      {                                                                                         \
        case CRY_RSASSA_PSS_FINISH_WAIT:                                                        \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINISH;                                 \
          break;                                                                                \
        case CRY_RSASSA_PSS_END_MASK_WAIT:                                                      \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_END_MASK;                               \
          break;                                                                                \
        case CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT:                                              \
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_FINISH;                       \
          break;                                                                                \
        default:                                                                                \
        {                                                                                       \
          break;                                                                                \
        }                                                                                       \
      }                                                                                         \
      break;                                                                                    \
    default:                                                                                    \
    {                                                                                           \
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_IDLE;                                       \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);                                    \
      Csm_SignatureVerifyServiceFinishNotification();                                           \
      break;                                                                                    \
    }                                                                                           \
  }

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Helper function for the state CRY_RSASSA_PSS_START_EXP.
 **
 ** This helper function starts the exponentiation
 ** when performing the signature verification.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaPssStartExp
(
  void
);

/** \brief Helper function for the state CRY_RSASSA_PSS_FINISH_COMPUTE_MODEXP.
 **
 ** This helper function computes signature via modular exponentiation.
 **
 ** \retval None
 **
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaPssFinishComputeModularExp
(
  void
);

/** \brief Helper function for the state CRY_RSASSA_PSS_FINISH_EXP.
 **
 ** This helper function finishes the exponentiation
 ** when performing the signature verification.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaPssFinishExp
(
  void
);

/** \brief Helper function for the state CRY_RSASSA_PSS_DONE_MASK.
 **
 ** This helper function computes uses the DBMask to compute DB
 ** when performing the signature verification.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaPssDoneMask
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief "Null String" constant needed for signature verification.
 *
 * This constant provides a "Null String" needed during the signature verification.
 */
static CONST(uint8, CRY_CONST) Cry_RsaSsaPssVerify_Null_String[CRY_RSASSA_PSS_NULL_STRING_LENGTH] =
  {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief RSASSA-PSS signature verification context.
 *
 * The context variable which is used to store the internal state of the
 * RSASSA-PSS signature verification.
 */
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_RsaSsaPssVerifyCtxType, CRY_VAR) Cry_RsaSsaPssVerifyCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0053,1
*/
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaPssVerifyStart
(
  P2CONST(void,                  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if ( (Cry_RsaSsaPssVerifyCtx.State == CRY_RSASSA_PSS_IDLE) ||
       ( (Cry_RsaSsaPssVerifyCtx.CfgPtr->SupportRestart == TRUE)
         && (Cry_RsaSsaPssVerifyCtx.CfgPtr == cfgPtr)
       )
      )
  {
    Cry_RsaSsaPssVerifyCtx.RestartFlag = FALSE;
#endif

    Cry_RsaSsaPssVerifyCtx.CfgPtr    =
        (P2CONST(Cry_RsaSsaPssVerifyConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
     /* Deviation MISRAC2012-1 */
    Cry_RsaSsaPssVerifyCtx.KeyPtr    =
        (P2CONST(Cry_RsaPublicKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;

    /* !LINKSTO CS_SECURE_CRY_0002_RsaSsaPssVerify,1
     */
    /* Deviation MISRAC2012-2 */
    if (      ( FALSE == Cry_LNIsValid(Cry_RsaSsaPssVerifyCtx.KeyPtr->PublicExponent,
                                       CRY_RSAPUBKEY_NUM_LEN_WORDS
                                      )
              )
   /* Deviation MISRAC2012-2 */
           || ( FALSE == Cry_LNIsValid(Cry_RsaSsaPssVerifyCtx.KeyPtr->Modulus,
                                       CRY_RSAPUBKEY_NUM_LEN_WORDS
                                      )
              )
#if ((CRY_LN_USE_BARRETT == STD_ON) && (CRY_RSASSAPSSVERIFY_BARRETT == STD_ON))
   /* Deviation MISRAC2012-2 */
           || (    (  TRUE == Cry_RsaSsaPssVerifyCtx.CfgPtr->UseBarrett )
                && ( FALSE == Cry_LNIsValid(Cry_RsaSsaPssVerifyCtx.KeyPtr->Barrett,
                                            CRY_RSAPUBKEY_NUM_LEN_WORDS+1U
                                           )
                   )
              )
#endif
      )
    {
      RetVal = CSM_E_NOT_OK;
    }
    else
    {
      /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED == STD_OFF)
      if(    (Cry_RsaSsaPssVerifyCtx.CfgPtr->SupportRestart == TRUE)
          && (Cry_RsaSsaPssVerifyCtx.State != CRY_RSASSA_PSS_IDLE))
      {
        /* !LINKSTO EB_Cry_Restart_CryRsaSsaV15_CryRsaSsaPss,1 */
        /* !LINKSTO EB_Cry_Restart_CryRsaSsaV15_CryRsaSsaPss_Hash,1 */
        Cry_RsaSsaPssVerifyCtx.RestartFlag = TRUE;
      }
#endif

      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_INIT;
      RetVal                       = CSM_E_OK;
    }
  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#endif

  return RetVal;
}


/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0054,1
*/
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaPssVerifyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if (Cry_RsaSsaPssVerifyCtx.State == CRY_RSASSA_PSS_IDLE)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_RSASSA_PSS_INITIALIZED == Cry_RsaSsaPssVerifyCtx.State)
  {
    /* Store data into context */
    Cry_RsaSsaPssVerifyCtx.Data       = dataPtr;
    Cry_RsaSsaPssVerifyCtx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_RsaSsaPssVerifyCtx.State     = CRY_RSASSA_PSS_UPDATE;
    RetVal                           = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}


/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0055, 1
 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaPssVerifyFinish
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
)
{
  Csm_ReturnType RetVal;

  if (Cry_RsaSsaPssVerifyCtx.State == CRY_RSASSA_PSS_IDLE)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if (CRY_RSASSA_PSS_INITIALIZED == Cry_RsaSsaPssVerifyCtx.State)
  {
    /* Store data into context */
    Cry_RsaSsaPssVerifyCtx.Signature       = signaturePtr;
    Cry_RsaSsaPssVerifyCtx.SignatureLength = signatureLength;
    Cry_RsaSsaPssVerifyCtx.ResultPtr       = resultPtr;
    /* Set state of the state machine to finish */
    Cry_RsaSsaPssVerifyCtx.State     = CRY_RSASSA_PSS_FINISH;
    RetVal                           = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0056,1
 */
FUNC(void, CRY_CODE) Cry_RsaSsaPssVerifyMainFunction
(
  void
)
{
  if(Cry_RsaSsaPssVerifyCtx.RestartFlag == TRUE)
  {
    Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_INIT;
    Cry_RsaSsaPssVerifyCtx.RestartFlag = FALSE;
  }

  switch(Cry_RsaSsaPssVerifyCtx.State)
  {
    case CRY_RSASSA_PSS_INIT:
      /* !LINKSTO EB_Cry_Restart_CryRsaSsaV15_CryRsaSsaPss_Hash,1 */
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_INIT_WAIT;
      CRY_RSA_HASH_START;
      break;

    case CRY_RSASSA_PSS_UPDATE:
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_WAIT;
      CRY_RSA_HASH_UPDATE
      (
        Cry_RsaSsaPssVerifyCtx.Data,
        Cry_RsaSsaPssVerifyCtx.DataLength
      );
      break;

    case CRY_RSASSA_PSS_FINISH:
      Cry_RsaSsaPssVerifyCtx.HashResultLength = sizeof(Cry_RsaSsaPssVerifyCtx.HashResult);
      Cry_RsaSsaPssVerifyCtx.State            = CRY_RSASSA_PSS_FINISH_WAIT;
      CRY_RSA_HASH_FINISH
      (
        Cry_RsaSsaPssVerifyCtx.HashResult,
        &(Cry_RsaSsaPssVerifyCtx.HashResultLength)
      );
      break;

    case CRY_RSASSA_PSS_START_EXP:
      Cry_RsaSsaPssStartExp();
      break;

    case CRY_RSASSA_PSS_FINISH_COMPUTE_MODEXP:
      Cry_RsaSsaPssFinishComputeModularExp();
      break;

    case CRY_RSASSA_PSS_FINISH_EXP:
      Cry_RsaSsaPssFinishExp();
      break;

    case CRY_RSASSA_PSS_START_MASK:
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_START_MASK_WAIT;
      CRY_RSA_HASH_START;
      break;

    case CRY_RSASSA_PSS_UPDATE_MASK:
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_MASK_WAIT;
      CRY_RSA_HASH_UPDATE
      (
        &Cry_RsaSsaPssVerifyCtx.EM[Cry_RsaSsaPssVerifyCtx.dblen],
        CRY_RSASSA_PSS_HASH_MAX_LEN /*Cry_RsaSsaPssVerifyCtx.dblen*/
      );
      break;

    case CRY_RSASSA_PSS_UPDATE_CNT_MASK:
      Cry_RsaSsaPssVerifyCtx.MaskCntStr[0] = (uint8)((Cry_RsaSsaPssVerifyCtx.MaskCnt >> 24U) &
                                                     (uint8)0xFF);
      Cry_RsaSsaPssVerifyCtx.MaskCntStr[1] = (uint8)((Cry_RsaSsaPssVerifyCtx.MaskCnt >> 16U) &
                                                     (uint8)0xFF);
      Cry_RsaSsaPssVerifyCtx.MaskCntStr[2] = (uint8)((Cry_RsaSsaPssVerifyCtx.MaskCnt >>  8U) &
                                                     (uint8)0xFF);
      Cry_RsaSsaPssVerifyCtx.MaskCntStr[3] = (uint8)((Cry_RsaSsaPssVerifyCtx.MaskCnt       ) &
                                                     (uint8)0xFF);
      Cry_RsaSsaPssVerifyCtx.MaskCnt++;

      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT;
      CRY_RSA_HASH_UPDATE
      (
        &Cry_RsaSsaPssVerifyCtx.MaskCntStr[0],
        CRY_RSASSA_PSS_SIG_MASK_CNT_LEN
      );
      break;

    case CRY_RSASSA_PSS_END_MASK:
      Cry_RsaSsaPssVerifyCtx.MaskHashResultLength = CRY_RSASSA_PSS_HASH_MAX_LEN;
      Cry_RsaSsaPssVerifyCtx.State                = CRY_RSASSA_PSS_END_MASK_WAIT;
      CRY_RSA_HASH_FINISH
      (
        Cry_RsaSsaPssVerifyCtx.MaskHashPtr,
        &Cry_RsaSsaPssVerifyCtx.MaskHashResultLength
      );

      Cry_RsaSsaPssVerifyCtx.MaskHashPtr =
                  &Cry_RsaSsaPssVerifyCtx.MaskHashPtr[Cry_RsaSsaPssVerifyCtx.MaskHashResultLength];
      break;

    case CRY_RSASSA_PSS_DONE_MASK:
      Cry_RsaSsaPssDoneMask();
      break;

    case CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE:
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT;
      CRY_RSA_HASH_UPDATE
      (
        &Cry_RsaSsaPssVerify_Null_String[0],
        CRY_RSASSA_PSS_NULL_LEN
      );
      break;

    case CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE:
      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT;
      CRY_RSA_HASH_UPDATE
      (
        &Cry_RsaSsaPssVerifyCtx.HashResult[0],
        Cry_RsaSsaPssVerifyCtx.HashResultLength
      );
      break;

    case CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE:
      if( Cry_RsaSsaPssVerifyCtx.sLen > 0U )
      {
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT;
        CRY_RSA_HASH_UPDATE
        (
          &Cry_RsaSsaPssVerifyCtx.dbMask[Cry_RsaSsaPssVerifyCtx.dblen-Cry_RsaSsaPssVerifyCtx.sLen],
          Cry_RsaSsaPssVerifyCtx.sLen
        );
      }
      else
      {
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_FINISH;
      }
      break;

    case CRY_RSASSA_PSS_FINALHASH_FINISH:
      Cry_RsaSsaPssVerifyCtx.HashResultLength = sizeof(Cry_RsaSsaPssVerifyCtx.Hashdash);
      Cry_RsaSsaPssVerifyCtx.State            = CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT;
      CRY_RSA_HASH_FINISH
      (
        &Cry_RsaSsaPssVerifyCtx.Hashdash[0],
        &Cry_RsaSsaPssVerifyCtx.HashResultLength
      );
      break;

    case CRY_RSASSA_PSS_COMPARE:
      {
        /* Compare the signature */
        uint32 i;

        for(i = 0U; i < Cry_RsaSsaPssVerifyCtx.HashResultLength; i++)
        {
          if( Cry_RsaSsaPssVerifyCtx.EM[i+Cry_RsaSsaPssVerifyCtx.dblen] !=
              Cry_RsaSsaPssVerifyCtx.Hashdash[i]
            )
          {
            *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
            Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
            /* !LINKSTO CSM0454, 1 */
            Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
            Csm_SignatureVerifyServiceFinishNotification();
            break;
          }
        }

        if( i >= Cry_RsaSsaPssVerifyCtx.HashResultLength )
        {
          *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_OK;
          Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
          /* !LINKSTO CSM0454, 1 */
          Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
          Csm_SignatureVerifyServiceFinishNotification();
        }
      }
      break;

    case CRY_RSASSA_PSS_INIT_WAIT:
    case CRY_RSASSA_PSS_UPDATE_WAIT:
    case CRY_RSASSA_PSS_FINISH_WAIT:
    case CRY_RSASSA_PSS_INITIALIZED:
    case CRY_RSASSA_PSS_START_MASK_WAIT:
    case CRY_RSASSA_PSS_UPDATE_MASK_WAIT:
    case CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT:
    case CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT:
    case CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT:
    case CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT:
    case CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT:
    default:
      {
        break;
      }
  }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_RsaSsaPssVerifyCallback
(
  Csm_ReturnType Result
)
{
  if(Result == CSM_E_OK)
  {
    switch(Cry_RsaSsaPssVerifyCtx.State)
    {
      case CRY_RSASSA_PSS_INIT_WAIT:
      case CRY_RSASSA_PSS_UPDATE_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_INITIALIZED;
        /* !LINKSTO CSM0454, 1 */
        Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
        break;

      case CRY_RSASSA_PSS_FINISH_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_START_EXP;
        break;

      case CRY_RSASSA_PSS_START_MASK_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_MASK;
        break;

      case CRY_RSASSA_PSS_UPDATE_MASK_WAIT :
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_UPDATE_CNT_MASK;
        break;

      case CRY_RSASSA_PSS_UPDATE_CNT_MASK_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_END_MASK;
        break;

      case CRY_RSASSA_PSS_END_MASK_WAIT:
        if( Cry_RsaSsaPssVerifyCtx.MaskCnt < Cry_RsaSsaPssVerifyCtx.MaskItr )
        {
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_START_MASK;
        }
        else
        {
          Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_DONE_MASK;
        }
        break;

      case CRY_RSASSA_PSS_DONE_MASK_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE;
        break;

      case CRY_RSASSA_PSS_FINALHASH_ZERO_UPDATE_WAIT :
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE;
        break;

      case CRY_RSASSA_PSS_FINALHASH_HASH_UPDATE_WAIT :
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE;
        break;

      case CRY_RSASSA_PSS_FINALHASH_SALT_UPDATE_WAIT :
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINALHASH_FINISH;
        break;

      case CRY_RSASSA_PSS_FINALHASH_FINISH_WAIT:
        Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_COMPARE;
        break;

      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code. this 'default' is required by MISRA-C:2004. */
      default:
        {
          break;
        }
      /* CHECK: PARSE */
    }
  }
  else
  {
    Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_IDLE;
    Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);
    Csm_SignatureVerifyServiceFinishNotification();
  }

  return E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_RsaSsaPssStartExp
(
  void
)
{
  Csm_ReturnType CsmRetVal;
  Std_ReturnType StdRetVal;
  uint32 decodedSignatureLength;

  /* initialize the return values */
  CsmRetVal    = CSM_E_OK;

  if (TRUE == Cry_RsaSsaPssVerifyCtx.CfgPtr->Base64Encoded)
  {
    decodedSignatureLength = sizeof(Cry_RsaSsaPssVerifyCtx.EM);

    CsmRetVal = Cry_Base64Decode
    (
      Cry_RsaSsaPssVerifyCtx.Signature,
      Cry_RsaSsaPssVerifyCtx.SignatureLength,
      Cry_RsaSsaPssVerifyCtx.EM,
      &decodedSignatureLength
    );

    Cry_RsaSsaPssVerifyCtx.Signature =
        (P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)) Cry_RsaSsaPssVerifyCtx.EM;
    Cry_RsaSsaPssVerifyCtx.SignatureLength = decodedSignatureLength;

  }

  if (CSM_E_OK == CsmRetVal)
  {
    StdRetVal = Cry_LNBEByteArrayToNumber
      (
        Cry_RsaSsaPssVerifyCtx.Signature,
        Cry_RsaSsaPssVerifyCtx.SignatureLength,
        Cry_RsaSsaPssVerifyCtx.tmp5Value,
        (Cry_LNWordType)
          (sizeof(Cry_RsaSsaPssVerifyCtx.tmp5Value)/sizeof(Cry_RsaSsaPssVerifyCtx.tmp5Value[0]))
      );

    if (StdRetVal != E_OK)
    {
      /* failed to convert the byte array to an LN number */
      *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
      /* !LINKSTO CSM0454, 1 */
      Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
      Csm_SignatureVerifyServiceFinishNotification();

    }
    else
    {
      /* OK */
      Cry_LNModExpStart(&Cry_RsaSsaPssVerifyCtx.LNCtx);

#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
      /* !LINKSTO EB_Cry_Slicing_CryRsaSsaPssVerifyNumberOfTimeSlicesCbk,1
      */
#if (CRY_RSASSAPSSVERIFY_USE_CBK == STD_ON)
      Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices =
        Cry_RsaSsaPssVerifyTimeSliceConfig.CryRsaSsaPssTimeSlicesCbk();
#else
      Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices = (uint32)CRY_RSASSAPSSVERIFY_NR_OF_TIME_SLICES;
#endif
#endif

      Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINISH_COMPUTE_MODEXP;
    }
  }
  else
  {
    /* invalid base64 encoding */
    *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
    Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
    /* !LINKSTO CSM0454, 1 */
    Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
    Csm_SignatureVerifyServiceFinishNotification();
  }

}

static FUNC(void, CRY_CODE) Cry_RsaSsaPssFinishComputeModularExp
(
  void
)
{
  boolean Finished;

/* !LINKSTO EB_Cry_Slicing_RSA,1
*/
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaPssVerifyNumberOfTimeSlicesCbk_ret0,1
*/
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
  uint32 sliceCount;

  sliceCount = 0U;
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */

#if (CRY_RSASSAPSSVERIFY_BARRETT == STD_OFF)
  do
  {
    Finished = Cry_LNModExp
    (
      Cry_RsaSsaPssVerifyCtx.tmp1Value,
      Cry_RsaSsaPssVerifyCtx.tmp5Value,
      Cry_RsaSsaPssVerifyCtx.KeyPtr->Modulus,
      Cry_RsaSsaPssVerifyCtx.KeyPtr->PublicExponent,
      &Cry_RsaSsaPssVerifyCtx.LNCtx
    );
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
    sliceCount++;
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
  }
  while ( (FALSE == Finished)
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
    && ((sliceCount < Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices)
    || (Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
  );
#else
  if (Cry_RsaSsaPssVerifyCtx.CfgPtr->UseBarrett == TRUE)
  {
    do
    {
      Finished = Cry_LNModExpBarrett
      (
        Cry_RsaSsaPssVerifyCtx.tmp1Value,
        Cry_RsaSsaPssVerifyCtx.tmp5Value,
        Cry_RsaSsaPssVerifyCtx.KeyPtr->Modulus,
        Cry_RsaSsaPssVerifyCtx.KeyPtr->PublicExponent,
        Cry_RsaSsaPssVerifyCtx.KeyPtr->Barrett,
        &Cry_RsaSsaPssVerifyCtx.LNCtx
      );
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
      sliceCount++;
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
    }
    while ( (FALSE == Finished)
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
    && ((sliceCount < Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices)
    || (Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
    );
  }
  else
  {
    do
    {
      Finished = Cry_LNModExp
      (
        Cry_RsaSsaPssVerifyCtx.tmp1Value,
        Cry_RsaSsaPssVerifyCtx.tmp5Value,
        Cry_RsaSsaPssVerifyCtx.KeyPtr->Modulus,
        Cry_RsaSsaPssVerifyCtx.KeyPtr->PublicExponent,
        &Cry_RsaSsaPssVerifyCtx.LNCtx
      );
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
      sliceCount++;
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
    }
    while ( (FALSE == Finished)
#if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON)
    && ((sliceCount < Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices)
    || (Cry_RsaSsaPssVerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAPSSVERIFY_USE_TIME_SLICES == STD_ON) */
    );
  }
#endif /* #if (CRY_RSASSAPSSVERIFY_BARRETT == STD_OFF)*/

  if (TRUE == Finished)
  {
    Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_FINISH_EXP;
  }
}

static FUNC(void, CRY_CODE) Cry_RsaSsaPssFinishExp
(
  void
)
{
  uint32  NumberLength;

  NumberLength = sizeof(Cry_RsaSsaPssVerifyCtx.EM);

  /* CHECK: NOPARSE */
  /* Defensive Programming - unreachable code. */
  if
  (
    /* EM */
    Cry_LNNumberToBEByteArray
    (
      Cry_RsaSsaPssVerifyCtx.tmp1Value,
      Cry_RsaSsaPssVerifyCtx.EM,
      &NumberLength
    ) == E_OK
  )
  /* CHECK: PARSE */
  {
    if ( ( (Cry_RsaSsaPssVerifyCtx.EM[0] & CRY_RSASSA_PSS_DB_MSB_NULL_MASK) != 0x00U ) ||
         ( NumberLength < ( Cry_RsaSsaPssVerifyCtx.HashResultLength + 2U ) ) ||
         ( Cry_RsaSsaPssVerifyCtx.EM[NumberLength-1] != CRY_RSASSA_PSS_EM_LAST_BYTE )
       )
    {
       *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
       Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
       /* !LINKSTO CSM0454, 1 */
       Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
       Csm_SignatureVerifyServiceFinishNotification();
    }
    else
    {
      Cry_RsaSsaPssVerifyCtx.dblen = NumberLength - Cry_RsaSsaPssVerifyCtx.HashResultLength - 1U;

      Cry_RsaSsaPssVerifyCtx.State   = CRY_RSASSA_PSS_START_MASK;
      Cry_RsaSsaPssVerifyCtx.MaskCnt = 0;
      Cry_RsaSsaPssVerifyCtx.MaskItr = ( (Cry_RsaSsaPssVerifyCtx.dblen +
                                          Cry_RsaSsaPssVerifyCtx.HashResultLength) - 1U
                                       ) / Cry_RsaSsaPssVerifyCtx.HashResultLength;
      Cry_RsaSsaPssVerifyCtx.MaskHashPtr = &Cry_RsaSsaPssVerifyCtx.dbMask[0];
    }
  }
  else
  {
     *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
     Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
     /* !LINKSTO CSM0454, 1 */
     Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
     Csm_SignatureVerifyServiceFinishNotification();
  }

  /* tmp1Value no longer needed, reset it to 0 */
  Cry_CommonResetCtx(Cry_RsaSsaPssVerifyCtx.tmp1Value, sizeof(Cry_RsaSsaPssVerifyCtx.tmp1Value));

}

static FUNC(void, CRY_CODE) Cry_RsaSsaPssDoneMask
(
  void
)
{
  uint32  i;
  boolean finished = FALSE;

  Cry_RsaSsaPssVerifyCtx.dbMask[0] &= (uint8)(~(uint8)CRY_RSASSA_PSS_DB_MSB_NULL_MASK);

  for (i = 0U; i < Cry_RsaSsaPssVerifyCtx.dblen; i++ )
  {
    Cry_RsaSsaPssVerifyCtx.dbMask[i] ^= Cry_RsaSsaPssVerifyCtx.EM[i];
  }

  for (i = 0U; ((i < Cry_RsaSsaPssVerifyCtx.dblen) && (FALSE == finished)); i++ )
  {
    if ( Cry_RsaSsaPssVerifyCtx.dbMask[i] != 0U )
    {
      if ( Cry_RsaSsaPssVerifyCtx.dbMask[i] == 1U )
      {
          Cry_RsaSsaPssVerifyCtx.sLen = Cry_RsaSsaPssVerifyCtx.dblen - i - 1U;

          /* !LINKSTO CS_SECURE_CRY_0164_2,1 */
          if ((Cry_RsaSsaPssVerifyCtx.CfgPtr->SaltLength == 0                          ) ||
              (Cry_RsaSsaPssVerifyCtx.sLen >= Cry_RsaSsaPssVerifyCtx.CfgPtr->SaltLength)
             )
          {
            Cry_RsaSsaPssVerifyCtx.State = CRY_RSASSA_PSS_DONE_MASK_WAIT;
            CRY_RSA_HASH_START;
          }
          else
          {
            *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
            Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
            /* !LINKSTO CSM0454, 1 */
            Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
            Csm_SignatureVerifyServiceFinishNotification( );
          }
      }
      else
      {
        *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
        Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
        /* !LINKSTO CSM0454, 1 */
        Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
        Csm_SignatureVerifyServiceFinishNotification( );
      }
      finished = TRUE;
    }
  }

  if ( FALSE == finished )
  {
    *Cry_RsaSsaPssVerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
    Cry_RsaSsaPssVerifyCtx.State      = CRY_RSASSA_PSS_IDLE;
    /* !LINKSTO CSM0454, 1 */
    Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
    Csm_SignatureVerifyServiceFinishNotification();
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_RSASSAPSSVERIFY_ENABLED == STD_ON) */

/* Dummy type definition to prevent compiler warnings about empty translation units */
typedef uint8 Cry_RsaSsaPssVerify_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_RSASSAPSSVERIFY_ENABLED == STD_ON) #else */

