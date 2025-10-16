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
#include <Csm_Hash.h>
#include <Cry_CommonConfig.h>
#include <Cry_Common.h>
#include <Cry_LN.h>                     /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Base64.h>                 /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_RsaSsaV15Verify.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_RsaSsaV15VerifyConfig.h>

#if (CRY_RSASSAV15VERIFY_ENABLED == STD_ON)

#if (CRY_RSASSAV15VERIFY_USE_CBK == STD_ON)
#include <Cry_RsaSsaV15VerifyCbk.h>
#endif

/*==[Macros]==================================================================*/

#if (defined CRY_SIGPKCS1_V_HASH_MAX_LEN)
#error CRY_SIGPKCS1_V_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes.
 */
#define CRY_SIGPKCS1_V_HASH_MAX_LEN 32U

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
#define CRY_RSA_HASH_START                                       \
  switch (Csm_HashStart(Cry_RsaSsaV15VerifyCtx.CfgPtr->HashCfg)) \
  {                                                              \
    case CSM_E_OK:                                               \
      break;                                                     \
    case CSM_E_BUSY:                                             \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_INIT;        \
      break;                                                     \
    default:                                                     \
    {                                                            \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_IDLE;        \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);     \
      Csm_SignatureVerifyServiceFinishNotification();            \
      break;                                                     \
    }                                                            \
  }

#if (defined CRY_RSA_HASH_UPDATE)
#error CRY_RSA_HASH_UPDATE is already defined
#endif

/** \brief Helper macro which calls the Csm_HashUpdate function
 **
 ** This function calls the function Csm_HashUpdate and performs state
 ** transitions according to the return value of the function Csm_HashUpdate.
 **
 ** \retval None
 **/
#define CRY_RSA_HASH_UPDATE                                      \
  switch (Csm_HashUpdate(Cry_RsaSsaV15VerifyCtx.CfgPtr->HashCfg, \
                         Cry_RsaSsaV15VerifyCtx.Data,            \
                         Cry_RsaSsaV15VerifyCtx.DataLength))     \
  {                                                              \
    case CSM_E_OK:                                               \
      break;                                                     \
    case CSM_E_BUSY:                                             \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_UPDATE;      \
      break;                                                     \
    default:                                                     \
    {                                                            \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_IDLE;        \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);     \
      Csm_SignatureVerifyServiceFinishNotification();            \
      break;                                                     \
    }                                                            \
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
 ** \retval None
 **/
#define CRY_RSA_HASH_FINISH                                                            \
  Cry_RsaSsaV15VerifyCtx.HashResultLength = sizeof(Cry_RsaSsaV15VerifyCtx.HashResult); \
  switch (Csm_HashFinish(Cry_RsaSsaV15VerifyCtx.CfgPtr->HashCfg,                       \
                         Cry_RsaSsaV15VerifyCtx.HashResult,                            \
                         &(Cry_RsaSsaV15VerifyCtx.HashResultLength),                   \
                         FALSE))                                                       \
  {                                                                                    \
    case CSM_E_OK:                                                                     \
      break;                                                                           \
    case CSM_E_BUSY:                                                                   \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_FINISH;                            \
      break;                                                                           \
    default:                                                                           \
    {                                                                                  \
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_IDLE;                              \
      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);                           \
      Csm_SignatureVerifyServiceFinishNotification();                                  \
      break;                                                                           \
    }                                                                                  \
  }

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_RsaSsaV15VerifyStateType
 * \brief Enumeration of the internal states of the RSASSA-PKCS1-v1_5 signature verification.
 *
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_IDLE
 * \brief The algorithm is in the idle state.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_INIT
 * \brief The initialization of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_WAIT_FOR_INIT
 * \brief The initialization of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_INITIALIZED
 * \brief The algorithm is initialized.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_UPDATE
 * \brief The update operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_WAIT_FOR_UPDATE
 * \brief The update operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_FINISH
 * \brief The finish operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_WAIT_FOR_FINISH
 * \brief The finish operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_FINISH_DECRYPT
 * \brief Decrypting with RSA is in process.
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_FINISH_COMPUTE_MODEXP
 * \brief The expected signature shall be verified via modular exponentiation
 *//**
 * \var Cry_RsaSsaV15VerifyStateType::CRY_RSASSA_V_S_FINISH_COMPARE
 * \brief The signature which shall be verified is compared with the expected signature.
 */
typedef enum
{
  CRY_RSASSA_V_S_IDLE,
  CRY_RSASSA_V_S_INIT,
  CRY_RSASSA_V_S_WAIT_FOR_INIT,
  CRY_RSASSA_V_S_INITIALIZED,
  CRY_RSASSA_V_S_UPDATE,
  CRY_RSASSA_V_S_WAIT_FOR_UPDATE,
  CRY_RSASSA_V_S_FINISH,
  CRY_RSASSA_V_S_WAIT_FOR_FINISH,
  CRY_RSASSA_V_S_FINISH_DECRYPT,
  CRY_RSASSA_V_S_FINISH_COMPUTE_MODEXP,
  CRY_RSASSA_V_S_FINISH_COMPARE
}
Cry_RsaSsaV15VerifyStateType;

/**
 * \struct Cry_RsaSsaV15VerifyCtxType
 * \brief Structure which contains the context of the RSASSA-PKCS1-v1_5 signature verification.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::SignatureLength
 * \brief The length of the signature to verify.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::DataLength
 * \brief The length of the data.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::HashResultLength
 * \brief The length of the hash value of the data.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::maximumNumberOfSlices
 * \brief Maximum number of time slices used for V15 signature calculation.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::CfgPtr
 * \brief A pointer to the current RSASSA-PKCS1-v1_5 signature verification
 *        configuration which has to be used.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::KeyPtr
 * \brief A pointer to the public key which should be used for verifying the signature.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::Signature
 * \brief A pointer to the start of a buffer where the signature to verify is stored.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::ResultPtr
 * \brief A pointer to a variable where the signature verification result has to be stored.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::Data
 * \brief A pointer to the start of an array where the data whose signature to verify is stored.
 *        data will be buffered during the computation.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::tmp1Value
 * \brief An array which is used as a buffer during signature verification.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::tmp5Value
 * \brief An array which is used as a buffer during signature verification.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::LNCtx
 * \brief The context which has to be used for long number arithmetic.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::HashResult
 * \brief A pointer to the start of an array where the hash value of the
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::EM
 * \brief sAn array which is used as a buffer for the value "EM" during the signature verification.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::State
 * \brief The current state the RSASSA-PKCS1-v1_5 signature verification is in.
 *//**
 * \var Cry_RsaSsaV15VerifyCtxType::RestartFlag
 * \brief Flag that states if the restart of the service is active.
 */
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
   uint32                                                           SignatureLength;
   uint32                                                           DataLength;
   uint32                                                           HashResultLength;
   uint32                                                           maximumNumberOfSlices;
   P2CONST(Cry_RsaSsaV15VerifyConfigType, TYPEDEF, CRY_APPL_DATA)   CfgPtr;
   P2CONST(Cry_RsaPublicKeyType,          TYPEDEF, CRY_APPL_DATA)   KeyPtr;
   P2CONST(uint8,                         TYPEDEF, CRY_APPL_DATA)   Signature;
   P2VAR(Csm_VerifyResultType,            TYPEDEF, CRY_APPL_DATA)   ResultPtr;
   P2CONST(uint8,                         TYPEDEF, CRY_APPL_DATA)   Data;
   Cry_LNWordType                                         tmp1Value[CRY_RSA_PUB_KEY_TEMP_LEN_WORDS];
   Cry_LNWordType                                         tmp5Value[CRY_RSAPUBKEY_NUM_LEN_WORDS];
   Cry_LNCtxType                                                    LNCtx;
   uint8                                                  HashResult[CRY_SIGPKCS1_V_HASH_MAX_LEN];
   uint8                                                  EM[CRY_RSAPUBKEY_NUM_LEN_BYTES];
   Cry_RsaSsaV15VerifyStateType                                     State;
   boolean                                                          RestartFlag;
}
Cry_RsaSsaV15VerifyCtxType;


/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Helper function for the state CRY_RSASSA_V_S_FINISH_DECRYPT.
 **
 ** Decode the signature which is checked and start the decryption
 ** of the signature.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaVrfyStateFinishDecrypt
(
  void
);

/** \brief Helper function for the state CRY_RSASSA_V_S_FINISH_COMPUTE_MODEXP.
 **
 ** This helper function computes signature via modular exponentiation.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) CryRsaSsaVrfyStateFinishComputeModularExp
(
  void
);

/** \brief Helper function for the state CRY_RSASSA_V_S_FINISH_COMPARE.
 **
 ** Perform the final steps for computing the result of the signature
 ** verification.
 **
 ** \retval None
 **/
static FUNC(void, CRY_CODE) Cry_RsaSsaVrfyStateFinishCompare
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief RSASSA-PKCS1-v1_5 signature verification context.
 *
 * The context variable which is used to store the internal state of the
 * RSASSA-PKCS1-v1_5 signature verification.
 */
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_RsaSsaV15VerifyCtxType, CRY_VAR) Cry_RsaSsaV15VerifyCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, EB_CSM0701_1,1
*/
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15VerifyStart
(
  P2CONST(void,                  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if((Cry_RsaSsaV15VerifyCtx.State == CRY_RSASSA_V_S_IDLE) ||
     (    (Cry_RsaSsaV15VerifyCtx.CfgPtr->SupportRestart == TRUE)
       && (Cry_RsaSsaV15VerifyCtx.CfgPtr == cfgPtr)              ))
  {
    Cry_RsaSsaV15VerifyCtx.RestartFlag = FALSE;
#endif

    Cry_RsaSsaV15VerifyCtx.CfgPtr    =
        (P2CONST(Cry_RsaSsaV15VerifyConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    /* Deviation MISRAC2012-1 */
    Cry_RsaSsaV15VerifyCtx.KeyPtr    =
        (P2CONST(Cry_RsaPublicKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;

    /* !LINKSTO CS_SECURE_CRY_0002_RsaSsaV15Verify,1
    */
   /* Deviation MISRAC2012-2 <START> */
  if (( FALSE == Cry_LNIsValid(Cry_RsaSsaV15VerifyCtx.KeyPtr->PublicExponent,
                                       CRY_RSAPUBKEY_NUM_LEN_WORDS
                              )
       )
        || ( FALSE == Cry_LNIsValid(Cry_RsaSsaV15VerifyCtx.KeyPtr->Modulus,
                                       CRY_RSAPUBKEY_NUM_LEN_WORDS
                                   )
           )
   /* Deviation MISRAC2012-2 <STOP> */
#if ((CRY_LN_USE_BARRETT == STD_ON) && (CRY_RSASSAV15VERIFY_BARRETT == STD_ON))
   /* Deviation MISRAC2012-2 */
           || ( (  TRUE == Cry_RsaSsaV15VerifyCtx.CfgPtr->UseBarrett )
           && ( FALSE == Cry_LNIsValid(Cry_RsaSsaV15VerifyCtx.KeyPtr->Barrett,
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
#if (CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED == STD_OFF)
      if(     (Cry_RsaSsaV15VerifyCtx.CfgPtr->SupportRestart == TRUE)
           && (Cry_RsaSsaV15VerifyCtx.State != CRY_RSASSA_V_S_IDLE))
      {
        /* !LINKSTO EB_Cry_Restart_CryRsaSsaV15_CryRsaSsaPss,1 */
        /* !LINKSTO EB_Cry_Restart_CryRsaSsaV15_CryRsaSsaPss_Hash,1 */
        Cry_RsaSsaV15VerifyCtx.RestartFlag = TRUE;
      }
#endif

      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_INIT;
      RetVal                       = CSM_E_OK;
    }

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#endif

  return RetVal;
}


/* !LINKSTO EB_CRY_0012,1, EB_CSM0702_1,1
*/
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15VerifyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;
  if (Cry_RsaSsaV15VerifyCtx.State == CRY_RSASSA_V_S_IDLE)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_RSASSA_V_S_INITIALIZED == Cry_RsaSsaV15VerifyCtx.State)
  {
    /* Store data into context */
    Cry_RsaSsaV15VerifyCtx.Data       = dataPtr;
    Cry_RsaSsaV15VerifyCtx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_RsaSsaV15VerifyCtx.State      = CRY_RSASSA_V_S_UPDATE;
    RetVal                            = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}


/* !LINKSTO EB_CRY_0013,1, EB_CSM0703_1, 1
 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15VerifyFinish
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
)
{
  Csm_ReturnType RetVal;

  if (Cry_RsaSsaV15VerifyCtx.State == CRY_RSASSA_V_S_IDLE)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_RSASSA_V_S_INITIALIZED == Cry_RsaSsaV15VerifyCtx.State)
  {
    /* Store data into context */
    Cry_RsaSsaV15VerifyCtx.Signature       = signaturePtr;
    Cry_RsaSsaV15VerifyCtx.SignatureLength = signatureLength;
    Cry_RsaSsaV15VerifyCtx.ResultPtr       = resultPtr;
    /* Set state of the state machine to finish */
    Cry_RsaSsaV15VerifyCtx.State           = CRY_RSASSA_V_S_FINISH;
    RetVal                                 = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, EB_CSM0773_2,1
 */
FUNC(void, CRY_CODE) Cry_RsaSsaV15VerifyMainFunction
(
  void
)
{
  if(Cry_RsaSsaV15VerifyCtx.RestartFlag == TRUE)
  {
    Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_INIT;
    Cry_RsaSsaV15VerifyCtx.RestartFlag = FALSE;
  }

  switch(Cry_RsaSsaV15VerifyCtx.State)
  {
    case CRY_RSASSA_V_S_INIT:
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_WAIT_FOR_INIT;
      CRY_RSA_HASH_START;
      break;

    case CRY_RSASSA_V_S_UPDATE:
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_WAIT_FOR_UPDATE;
      CRY_RSA_HASH_UPDATE;
      break;

    case CRY_RSASSA_V_S_FINISH:
      Cry_RsaSsaV15VerifyCtx.HashResultLength = sizeof(Cry_RsaSsaV15VerifyCtx.HashResult);
      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_WAIT_FOR_FINISH;
      CRY_RSA_HASH_FINISH;
      break;

    case CRY_RSASSA_V_S_FINISH_DECRYPT:
      Cry_RsaSsaVrfyStateFinishDecrypt();
      break;

    case CRY_RSASSA_V_S_FINISH_COMPUTE_MODEXP:
      CryRsaSsaVrfyStateFinishComputeModularExp();
      break;

    case CRY_RSASSA_V_S_FINISH_COMPARE:
      Cry_RsaSsaVrfyStateFinishCompare();
      break;

    case CRY_RSASSA_V_S_WAIT_FOR_INIT:
    case CRY_RSASSA_V_S_WAIT_FOR_UPDATE:
    case CRY_RSASSA_V_S_WAIT_FOR_FINISH:
    case CRY_RSASSA_V_S_INITIALIZED:
    default:
      {
        break;
      }
  }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_RsaSsaV15VerifyCallback
(
  Csm_ReturnType Result
)
{
  if(Result == CSM_E_OK)
  {
    switch(Cry_RsaSsaV15VerifyCtx.State)
    {
      case CRY_RSASSA_V_S_WAIT_FOR_INIT:
      case CRY_RSASSA_V_S_WAIT_FOR_UPDATE:
        Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_INITIALIZED;
        Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
        break;

      case CRY_RSASSA_V_S_WAIT_FOR_FINISH:
        Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_FINISH_DECRYPT;
        break;

      default:
        {
          break;
        }
    }
  }
  else
  {
    Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_IDLE;
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

static FUNC(void, CRY_CODE) Cry_RsaSsaVrfyStateFinishDecrypt
(
  void
)
{
  Csm_ReturnType CsmRetVal;
  Std_ReturnType StdRetVal;

  uint8  decodedSignature[CRY_RSAPUBKEY_NUM_LEN_BYTES];
  uint32 decodedSignatureLength;

  /* initialize the return values */
  CsmRetVal    = CSM_E_OK;

  if (TRUE == Cry_RsaSsaV15VerifyCtx.CfgPtr->Base64Encoded)
  {
    decodedSignatureLength = sizeof(decodedSignature);

    CsmRetVal = Cry_Base64Decode
    (
      Cry_RsaSsaV15VerifyCtx.Signature,
      Cry_RsaSsaV15VerifyCtx.SignatureLength,
      decodedSignature,
      &decodedSignatureLength
    );


    Cry_RsaSsaV15VerifyCtx.Signature =
        (P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)) decodedSignature;
    Cry_RsaSsaV15VerifyCtx.SignatureLength = decodedSignatureLength;

  }

  if (CSM_E_OK == CsmRetVal)
  {
    StdRetVal = Cry_LNBEByteArrayToNumber
      (
        Cry_RsaSsaV15VerifyCtx.Signature,
        Cry_RsaSsaV15VerifyCtx.SignatureLength,
        Cry_RsaSsaV15VerifyCtx.tmp5Value,
        (Cry_LNWordType)
          (sizeof(Cry_RsaSsaV15VerifyCtx.tmp5Value)/sizeof(Cry_RsaSsaV15VerifyCtx.tmp5Value[0]))
      );

    if (StdRetVal != E_OK)
    {
      /* failed to convert the byte array to an LN number */

      *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;

      Cry_RsaSsaV15VerifyCtx.State      = CRY_RSASSA_V_S_IDLE;
      /* !LINKSTO CSM0454, 1 */
      Csm_SignatureVerifyCallbackNotification(CSM_E_OK);

      Csm_SignatureVerifyServiceFinishNotification();
    }
    else
    {
      /* OK */

      Cry_LNModExpStart(&Cry_RsaSsaV15VerifyCtx.LNCtx);

#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
      /* !LINKSTO EB_Cry_Slicing_CryRsaSsaV15VerifyNumberOfTimeSlicesCbk,1
       */
#if (CRY_RSASSAV15VERIFY_USE_CBK == STD_ON)
      Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices =
        Cry_RsaSsaV15VerifyTimeSliceConfig.CryRsaSsaV15TimeSlicesCbk();
#else
      Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices = (uint32)CRY_RSASSAV15VERIFY_NR_OF_TIME_SLICES;
#endif
#endif

      Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_FINISH_COMPUTE_MODEXP;
    }
  }
  else
  {
    /* invalid base64 encoding */
    *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;

    Cry_RsaSsaV15VerifyCtx.State      = CRY_RSASSA_V_S_IDLE;
    /* !LINKSTO CSM0454, 1 */
    Csm_SignatureVerifyCallbackNotification(CSM_E_OK);

    Csm_SignatureVerifyServiceFinishNotification();
  }
}

static FUNC(void, CRY_CODE) CryRsaSsaVrfyStateFinishComputeModularExp
(
  void
)
{
  boolean Finished;

/* !LINKSTO EB_Cry_Slicing_RSA,1
*/
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaV15VerifyNumberOfTimeSlicesCbk_ret0,1
*/
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
  uint32 sliceCount;

  sliceCount = 0U;
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */

#if (CRY_RSASSAV15VERIFY_BARRETT == STD_OFF)
  do
  {
    Finished = Cry_LNModExp
    (
      Cry_RsaSsaV15VerifyCtx.tmp1Value,
      Cry_RsaSsaV15VerifyCtx.tmp5Value,
      Cry_RsaSsaV15VerifyCtx.KeyPtr->Modulus,
      Cry_RsaSsaV15VerifyCtx.KeyPtr->PublicExponent,
      &Cry_RsaSsaV15VerifyCtx.LNCtx
    );
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
    sliceCount++;
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
  }
  while ( (FALSE == Finished)
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
    && ((sliceCount < Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices)
    || (Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
  );
#else
  if (Cry_RsaSsaV15VerifyCtx.CfgPtr->UseBarrett == TRUE)
  {
    do
    {
      Finished = Cry_LNModExpBarrett
      (
        Cry_RsaSsaV15VerifyCtx.tmp1Value,
        Cry_RsaSsaV15VerifyCtx.tmp5Value,
        Cry_RsaSsaV15VerifyCtx.KeyPtr->Modulus,
        Cry_RsaSsaV15VerifyCtx.KeyPtr->PublicExponent,
        Cry_RsaSsaV15VerifyCtx.KeyPtr->Barrett,
        &Cry_RsaSsaV15VerifyCtx.LNCtx
      );
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
      sliceCount++;
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
    }
    while ( (FALSE == Finished)
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
      && ((sliceCount < Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices)
      || (Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
    );
  }
  else
  {
    do
    {
      Finished = Cry_LNModExp
      (
        Cry_RsaSsaV15VerifyCtx.tmp1Value,
        Cry_RsaSsaV15VerifyCtx.tmp5Value,
        Cry_RsaSsaV15VerifyCtx.KeyPtr->Modulus,
        Cry_RsaSsaV15VerifyCtx.KeyPtr->PublicExponent,
        &Cry_RsaSsaV15VerifyCtx.LNCtx
      );
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
      sliceCount++;
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
    }
    while ( (FALSE == Finished)
#if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON)
    && ((sliceCount < Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices)
    || (Cry_RsaSsaV15VerifyCtx.maximumNumberOfSlices == 0))
#endif /* #if (CRY_RSASSAV15VERIFY_USE_TIME_SLICES == STD_ON) */
    );
  }
#endif /* #if (CRY_RSASSAV15VERIFY_BARRETT == STD_OFF) */

  if (TRUE == Finished)
  {
    Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_FINISH_COMPARE;
  }
}

static FUNC(void, CRY_CODE) Cry_RsaSsaVrfyStateFinishCompare
(
  void
)
{
  uint32 NumberLength;
  uint32 AlgorithmIdLength;
  uint32 DerHeaderDigestInfoLength;
  uint32 DerHeaderDigestLength;
  uint32 i;
  P2CONST(uint8, CRY_VAR, AUTOMATIC) AlgorithmId;
  uint8 DerHeaderDigestBuffer[CRY_COMMON_DER_HEADER_MAX_LEN];
  uint8 DerHeaderDigestInfoBuffer[CRY_COMMON_DER_HEADER_MAX_LEN];

  NumberLength = sizeof(Cry_RsaSsaV15VerifyCtx.EM);

  /* CHECK: NOPARSE */
  /* Defensive Programming - unreachable code. */
  if
  (
    Cry_LNNumberToBEByteArray
    (
      Cry_RsaSsaV15VerifyCtx.tmp1Value,
      Cry_RsaSsaV15VerifyCtx.EM,
      &NumberLength
    ) != E_OK
  )
  /* CHECK: PARSE */
  {
    *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
  }
  else
  {
    AlgorithmId = Csm_HashAlgorithmId
    (
      Cry_RsaSsaV15VerifyCtx.CfgPtr->HashCfg,
      &AlgorithmIdLength
    );

    DerHeaderDigestLength = Cry_CommonDerHeaderOctetString
    (
      DerHeaderDigestBuffer,
      Cry_RsaSsaV15VerifyCtx.HashResultLength
    );

    DerHeaderDigestInfoLength = Cry_CommonDerHeaderSequence
    (
      DerHeaderDigestInfoBuffer,
      Cry_RsaSsaV15VerifyCtx.HashResultLength + DerHeaderDigestLength + AlgorithmIdLength
    );

    *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_OK;

    if
    (
      (Cry_RsaSsaV15VerifyCtx.EM[0] != (uint8)0x00U) ||
      (Cry_RsaSsaV15VerifyCtx.EM[1] != (uint8)0x01U)
    )
    {
      *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
    }

    if (NumberLength >=
        (1 +
         Cry_RsaSsaV15VerifyCtx.HashResultLength +
         AlgorithmIdLength +
         DerHeaderDigestLength +
         DerHeaderDigestInfoLength
        )
       )
    {
      for
      (
        i = 2;
        i < (NumberLength -
             (1 +
              (Cry_RsaSsaV15VerifyCtx.HashResultLength +
               (AlgorithmIdLength +
                (DerHeaderDigestLength +
                 DerHeaderDigestInfoLength))))
             );
        i++
      )
      {
        if (Cry_RsaSsaV15VerifyCtx.EM[i] != (uint8)0xFFU)
        {
          *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
        }
      }


      if (Cry_RsaSsaV15VerifyCtx.EM[i] != (uint8)0x00U)
      {
        *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }
      i++;

      if
      (
          Cry_CommonCompare
          (
            &Cry_RsaSsaV15VerifyCtx.EM[i],
            DerHeaderDigestInfoBuffer,
            DerHeaderDigestInfoLength
          ) != CRY_E_EQUAL
      )
      {
        *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }
      i += DerHeaderDigestInfoLength;

      if
      (
        Cry_CommonCompare
        (
          &Cry_RsaSsaV15VerifyCtx.EM[i],
          AlgorithmId,
          AlgorithmIdLength
        ) != CRY_E_EQUAL
      )
      {
        *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }
      i += AlgorithmIdLength;

      if
      (
        Cry_CommonCompare
        (
          &Cry_RsaSsaV15VerifyCtx.EM[i],
          DerHeaderDigestBuffer,
          DerHeaderDigestLength
        ) != CRY_E_EQUAL
      )
      {
        *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }
      i += DerHeaderDigestLength;

      if
      (
        Cry_CommonCompare
        (
          &Cry_RsaSsaV15VerifyCtx.EM[i],
          Cry_RsaSsaV15VerifyCtx.HashResult,
          Cry_RsaSsaV15VerifyCtx.HashResultLength
        ) != CRY_E_EQUAL
      )
      {
        *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
      }
    }
    else
    {
      *Cry_RsaSsaV15VerifyCtx.ResultPtr = CSM_E_VER_NOT_OK;
    }
  }

  Cry_RsaSsaV15VerifyCtx.State = CRY_RSASSA_V_S_IDLE;

  /* !LINKSTO CSM0454, 1 */
  Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
  Csm_SignatureVerifyServiceFinishNotification();
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_RSASSAV15VERIFY_ENABLED == STD_ON) */

/* Dummy type definition to prevent compiler warnings about empty translation units */
typedef uint8 Cry_RsaSsaV15Verify_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_RSASSAV15VERIFY_ENABLED == STD_ON) #else */

