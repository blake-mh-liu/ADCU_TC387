/* --------{ EB Automotive C Source File }-------- */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast shall not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the the original type.
 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>
#include <Csm_Hash.h>
#include <Csm_SignatureVerify.h>
#include <Csm_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>
#include <Cry_EdDSAVrfy.h>

#if (CRY_EDDSA_VRFY_ENABLED == STD_ON)
/*==[Macros]==================================================================*/

#if (defined CRY_EDDSA_V_ARRAY_LEN)
#error CRY_EDDSA_V_ARRAY_LEN is already defined
#endif
/** \brief The maximal allowed length for a Byte-array in bytes. */
#define CRY_EDDSA_V_ARRAY_LEN 32U

#if (defined CRY_EDDSA_V_HASH_MAX_LEN)
#error CRY_EDDSA_V_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes. */
#define CRY_EDDSA_V_HASH_MAX_LEN (CRY_EDDSA_V_ARRAY_LEN << 1U)

#if (defined CRY_EDDSA_V_SIG_S_START_POSITION)
#error CRY_EDDSA_V_SIG_S_START_POSITION is already defined
#endif
/** \brief Defines the start position of the S component in the reference signature */
#define CRY_EDDSA_V_SIG_S_START_POSITION 32U

#if (defined CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING)
#error CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING is already defined
#endif
/** \brief Handle failing public key decoding */
#define CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING do {                                           \
                                Cry_EdDSAVrfyCtx.vrfyState    = CRY_EdDSA_V_S_IDLE;                \
                                Cry_EdDSAVrfyCtx.decPubKeyState = CRY_EdDSA_V_S_CONVERT_PUBLICKEY; \
                                Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);             \
                                Csm_SignatureVerifyServiceFinishNotification();                    \
                              } while(0U)

#if (defined CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG)
#error CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG is already defined
#endif
/** \brief Handle failing Hash service while processing the message */
#define CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG do {                                                   \
                                  Cry_EdDSAVrfyCtx.vrfyState    = CRY_EdDSA_V_S_IDLE;              \
                                  Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_INIT_HASH_MESSAGE; \
                                  Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);           \
                                  Csm_SignatureVerifyServiceFinishNotification();                  \
                                } while(0U)

#if (defined CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP)
#error CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP is already defined
#endif
/** \brief Handle failing component validation while processing the signature */
#define CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP do {                                     \
                                  Cry_EdDSAVrfyCtx.vrfyState      = CRY_EdDSA_V_S_IDLE;      \
                                  Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_CONVERT_S; \
                                  *Cry_EdDSAVrfyCtx.resultPtr      = CSM_E_VER_NOT_OK;       \
                                  Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);     \
                                  Csm_SignatureVerifyServiceFinishNotification();            \
                                } while(0U)

#if (defined CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK)
#error CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK is already defined
#endif
/** \brief Handle failing Hash service while processing k */
#define CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK do {                                                  \
                                      Cry_EdDSAVrfyCtx.vrfyState    = CRY_EdDSA_V_S_IDLE;          \
                                      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_INIT_SIGN_HASH;\
                                      Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);       \
                                      Csm_SignatureVerifyServiceFinishNotification();              \
                                    } while(0U)

/*==[Types]===================================================================*/

/** \brief Internal states of signature verification */
typedef enum
{
  /** \brief Waiting for new operation */
  CRY_EdDSA_V_S_IDLE,

  /** \brief The signature verification is initialized */
  CRY_EdDSA_V_S_INITIALIZED,

  /** \brief Start the signature verification */
  CRY_EdDSA_V_S_VERIFY_START,

  /** \brief Hash the message */
  CRY_EdDSA_V_S_HASH_MSG,

  /** \brief Validate signature components (R and S) */
  CRY_EdDSA_V_S_VALIDATE_SIG_COMPONENTS,

  /** \brief Calculate k */
  CRY_EdDSA_V_S_LITTLE_K,

  /** \brief Calculate group equation */
  CRY_EdDSA_V_S_GROUP_EQUATIONS,

  /** \brief Compare S * B == R + (k * A) */
  CRY_EdDSA_V_S_FINISH_COMPARE
} Cry_EdDSAVrfyStateType;

/** \brief Internal states for public key decoding */
typedef enum
{
  /** \brief Convert the public key (A) from Long Number format to byte array */
  CRY_EdDSA_V_S_CONVERT_PUBLICKEY,

  /** \brief Decode the public key point */
  CRY_EdDSA_V_S_DECODE_PUBLICKEY
} Cry_EdDSAVrfyDecodePublicKeyStateType;

/** \brief Internal states for message hashing */
typedef enum
{
  /** \brief Start hashing of the message */
  CRY_EdDSA_V_S_INIT_HASH_MESSAGE,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_V_S_WAIT_FOR_INIT_HASH_MESSAGE,

  /** \brief Hash message blocks */
  CRY_EdDSA_V_S_UPDATE_MESSAGE,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_V_S_WAIT_FOR_UPDATE_MESSAGE,

  /** \brief Finish the message hashing */
  CRY_EdDSA_V_S_FINISH_MESSAGE,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_V_S_WAIT_FOR_FINISH_MESSAGE
} Cry_EdDSAVrfyHashMsgStateType;

/** \brief Internal states for public key decoding */
typedef enum
{
  /** \brief Convert the S component to Long Number format */
  CRY_EdDSA_V_S_CONVERT_S,

  /** \brief Check the range of S */
  CRY_EdDSA_V_S_CHECK_S,

  /** \brief Copy the R component of the signature */
  CRY_EdDSA_V_S_COPY_R,

  /** \brief Decode point R */
  CRY_EdDSA_V_S_DECODE_R
} Cry_EdDSAVrfyValSigCmpStateType;

/** \brief Internal state for little k calculation */
typedef enum
{
  /** \brief Start the signature hashing */
  CRY_EdDSA_V_S_INIT_SIGN_HASH,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_V_S_WAIT_FOR_INIT,

  /** \brief Hash Context string for Ed25519ph. */
  CRY_EdDSA_V_S_UPDATE_DOM2,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_V_S_WAIT_FOR_UPDATE_DOM2,

  /** \brief Hash the R block of the signature */
  CRY_EdDSA_V_S_UPDATE_ENC_R,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_R,

  /** \brief Encode and hash the pubKey A */
  CRY_EdDSA_V_S_UPDATE_ENC_A,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_A,

  /** \brief Hash again the H(M) */
  CRY_EdDSA_V_S_UPDATE_M,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_V_S_WAIT_FOR_UPDATE_M,

  /** \brief Finish the SHA512(dom||R||A||PH(M)) hashing */
  CRY_EdDSA_V_S_FINISH,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_V_S_WAIT_FOR_FINISH
} Cry_EdDSAVrfyLittleKStateType;

/** \brief Internal states of signature verification final equation */
typedef enum
{
  /** \brief Convert the hash result to a big integer */
  CRY_EdDSA_V_S_HASH,

  /** \brief Calculate hashValue % lValue */
  CRY_EdDSA_V_S_HASH_RED,

  /** \brief Calculate h * A */
  CRY_EdDSA_V_S_FINISH_EQUATION_1,

  /** \brief Calculate R + (h * A) */
  CRY_EdDSA_V_S_FINISH_EQUATION_2,

  /** \brief Encode R + (h * A) */
  CRY_EdDSA_V_S_FINISH_EQUATION_2_ENC,

  /** \brief Calculate S * B */
  CRY_EdDSA_V_S_FINISH_EQUATION_3,

  /** \brief Encode S * B */
  CRY_EdDSA_V_S_FINISH_EQUATION_3_ENC
} Cry_EdDSAVrfyFinishEquationStateType;

/** \brief Structure which contains the context of the EdDSA signature verification. */
typedef struct
{
  /** \brief The length of the data whose signature has to be verified. */
  uint32                                                    messageLength;

  /** \brief Length of the signature to verify. */
  uint32                                                    signatureLength;

  /** \brief The length of the hash digest. */
  uint32                                                    hashResultLength;

  /** \brief Length of the byte array. */
  uint32                                                    tmp1arrayLength;

  /** \brief Length of the byte array. */
  uint32                                                    tmp2arrayLength;

  /** \brief Length of the byte array. */
  uint32                                                    tmp3arrayLength;

  /** \brief Pointer to the current EdDSA signature verification configuration. */
  P2CONST(Cry_EdDSAVrfyConfigType, TYPEDEF, CRY_APPL_CONST) cfgPtr;

  /** \brief Pointer to the public key which should be used for creating the signature. */
  P2CONST(Cry_EdDSAVrfyKeyType,    TYPEDEF, CRY_APPL_CONST) keyPtr;

  /** \brief Pointer to message whose signature has to be verified. */
  P2CONST(uint8,                   TYPEDEF, CRY_APPL_CONST) message;

  /** \brief Pointer to the buffer where the created signature should be stored. */
  P2CONST(uint8,                   TYPEDEF, CRY_APPL_CONST) signature;

  /** \brief Pointer to a variable where the result of the signature verification is stored. */
  P2VAR(Csm_VerifyResultType,      TYPEDEF, CRY_APPL_DATA ) resultPtr;

  /** \brief The context which has to be used for Edwards curve arithmetic. */
  Cry_EdDSACtxType                                          EdDSACtx;

  /** \brief The context which has to be used for long number arithmetic. */
  Cry_LNCtxType                                             LNCtx;

  /** \brief A point which is used as a buffer during signature verification. */
  Cry_EdDSAPointType                                        tmp1Point;

  /** \brief A point which is used as a buffer during signature verification. */
  Cry_EdDSAPointType                                        tmp2Point;

  /** \brief A point which is used as a buffer during signature verification. */
  Cry_EdDSAPointType                                        tmp3Point;

  /** \brief A point which is used as a buffer during signature verification. */
  Cry_EdDSAPointType                                        tmp4Point;

  /** \brief An array which is used as a buffer during signature verification. */
  Cry_LNWordType                                            tmp[8U * CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief Pointer to the buffer where the hash value of the data will be saved. */
  uint8                                                     hashResult[CRY_EDDSA_V_HASH_MAX_LEN];

  /** \brief Pointer to the buffer where the message to be hashed is stored. */
  uint8                                                     hashMessage[CRY_EDDSA_V_HASH_MAX_LEN];

  /** \brief A byte array which is used as a buffer during signature verification. */
  uint8                                                     tmp1array[CRY_EDDSA_V_ARRAY_LEN];

  /** \brief A byte array which is used as a buffer during signature verification. */
  uint8                                                     tmp2array[CRY_EDDSA_V_ARRAY_LEN];

  /** \brief A byte array which is used as a buffer during signature verification. */
  uint8                                                     tmp3array[CRY_EDDSA_V_ARRAY_LEN];

  /** \brief The current state of the EdDSA verification. */
  Cry_EdDSAVrfyStateType                                    vrfyState;

  /** \brief Internal states for public key decoding */
  Cry_EdDSAVrfyDecodePublicKeyStateType                     decPubKeyState;

  /** \brief Internal states for message hashing */
  Cry_EdDSAVrfyHashMsgStateType                             hashMsgState;

  /** \brief Internal states for signature components (R and S) validation */
  Cry_EdDSAVrfyValSigCmpStateType                           valSigCmpState;

  /** \brief Internal state for little k calculation */
  Cry_EdDSAVrfyLittleKStateType                             littleKState;

  /** \brief Internal states of signature verification final equation */
  Cry_EdDSAVrfyFinishEquationStateType                      finishEquationState;

  /** \brief Flag to indicate if the hashing of the message started. */
  boolean                                                   msgHashStarted;

  /** \brief Flag that states if the restart of the service is active. */
  boolean                                                   RestartFlag;
} Cry_EdDSAVrfyCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Decode the public key. */
static FUNC(void, CRY_CODE) Cry_EdDSAVrfyDecodePublicKey
(
  void
);

/** \brief Hash the message. */
static FUNC(void, CRY_CODE) Cry_EdDSAVrfyHashMsg
(
 void
);

/** \brief Check the validity of the R and S componets of the signature */
static FUNC(void, CRY_CODE) Cry_EdDSAVrfyValSigCmp
(
  void
);

/** \brief Calculate little k. */
static FUNC(void, CRY_CODE) Cry_EdDSAVrfyCalculateLittleK
(
 void
);

/** \brief Finish the signature verification signature. */
static FUNC(void, CRY_CODE) Cry_EdDSAFinishEquation
(
 void
);

/** \brief Calculate the s * Base point. */
static FUNC(void, CRY_CODE) Cry_EdDSACalculateSB
(
 void
);

/** \brief Calculate the k * A. */
static FUNC(void, CRY_CODE) Cry_EdDSACalculateKA
(
 void
);

/** \brief Convert the hash digest to LN representation. */
static FUNC(void, CRY_CODE) Cry_EdDSAHashByteToNum
(
 void
);

/** \brief Calculate R + (k * A). */
static FUNC(void, CRY_CODE) Cry_EdDSACalculateRkA
(
 void
);

/** \brief Validate the computed signature. */
static FUNC(void, CRY_CODE) Cry_EdDSAValidateSignature
(
 void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief EdDSA signature verification context. */
static VAR(Cry_EdDSAVrfyCtxType, CRY_VAR) Cry_EdDSAVrfyCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with internal linkage]===========================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0173,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyStart
(
    P2CONST(void,                  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
    P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal;

#if (CRY_EDDSAVRFY_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_EdDSA_V_S_IDLE == Cry_EdDSAVrfyCtx.vrfyState)
  {
    Cry_EdDSAVrfyCtx.RestartFlag = FALSE;

    Cry_EdDSAVrfyCtx.cfgPtr =
              (P2CONST(Cry_EdDSAVrfyConfigType, TYPEDEF, CRY_APPL_CONST))cfgPtr;

    /* Deviation MISRAC2012-1 */
    Cry_EdDSAVrfyCtx.keyPtr =
              (P2CONST(Cry_EdDSAVrfyKeyType, TYPEDEF, CRY_APPL_CONST))keyPtr;

    Cry_EdDSAVrfyCtx.msgHashStarted = FALSE;

    /* Set state of the state machine */
    Cry_EdDSAVrfyCtx.vrfyState      = CRY_EdDSA_V_S_VERIFY_START;
    Cry_EdDSAVrfyCtx.decPubKeyState = CRY_EdDSA_V_S_CONVERT_PUBLICKEY;

    RetVal = CSM_E_OK;
  }
  else if((Cry_EdDSAVrfyCtx.cfgPtr->SupportRestart == TRUE) && (Cry_EdDSAVrfyCtx.cfgPtr == cfgPtr))
  {
    /* !LINKSTO EB_Cry_Restart_CryEdDSAVrfy,1 */
    Cry_EdDSAVrfyCtx.RestartFlag = TRUE;

    /* Set state of the state machine */
    Cry_EdDSAVrfyCtx.vrfyState = CRY_EdDSA_V_S_VERIFY_START;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  Cry_EdDSAVrfyCtx.cfgPtr = (P2CONST(Cry_EdDSAVrfyConfigType, TYPEDEF, CRY_APPL_CONST))cfgPtr;

  /* Deviation MISRAC2012-1 */
  Cry_EdDSAVrfyCtx.keyPtr =
            (P2CONST(Cry_EdDSAVrfyKeyType, TYPEDEF, CRY_APPL_CONST))keyPtr;

    Cry_EdDSAVrfyCtx.msgHashStarted = FALSE;

    /* Set state of the state machine */
    Cry_EdDSAVrfyCtx.vrfyState      = CRY_EdDSA_V_S_VERIFY_START;

  RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0174,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if(CRY_EdDSA_V_S_IDLE == Cry_EdDSAVrfyCtx.vrfyState)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_EdDSA_V_S_INITIALIZED == Cry_EdDSAVrfyCtx.vrfyState)
  {
    /* Store data into context */
    Cry_EdDSAVrfyCtx.message       = dataPtr;
    Cry_EdDSAVrfyCtx.messageLength = dataLength;

    /* First message block to be hashed */
    if(Cry_EdDSAVrfyCtx.msgHashStarted == FALSE)
    {
      Cry_EdDSAVrfyCtx.msgHashStarted = TRUE;
      Cry_EdDSAVrfyCtx.hashMsgState   = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
    }
    else
    {
      /* Subsequent message blocks to be hashed */
      Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_UPDATE_MESSAGE;
    }

    /* Set state of the state machine to update */
    Cry_EdDSAVrfyCtx.vrfyState = CRY_EdDSA_V_S_HASH_MSG;
    RetVal                     = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0175,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyFinish
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              signaturePtr,
   uint32                                                signatureLength,
   P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
)
{
  Csm_ReturnType RetVal;

  if (CRY_EdDSA_V_S_IDLE == Cry_EdDSAVrfyCtx.vrfyState)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if((Cry_EdDSAVrfyCtx.msgHashStarted == TRUE                      ) &&
          (CRY_EdDSA_V_S_INITIALIZED       == Cry_EdDSAVrfyCtx.vrfyState)
         )
  {
    /* Store data into context */
    Cry_EdDSAVrfyCtx.signature       = signaturePtr;
    Cry_EdDSAVrfyCtx.signatureLength = signatureLength;
    Cry_EdDSAVrfyCtx.resultPtr       = resultPtr;

    /* Set state of the state machine to Update */
    Cry_EdDSAVrfyCtx.vrfyState      = CRY_EdDSA_V_S_HASH_MSG;
    Cry_EdDSAVrfyCtx.hashMsgState   = CRY_EdDSA_V_S_FINISH_MESSAGE;

    Cry_EdDSAVrfyCtx.msgHashStarted = FALSE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0176,1 */
FUNC(void, CRY_APPL_CODE) Cry_EdDSAVrfyMainFunction
(
   void
)
{
  if (Cry_EdDSAVrfyCtx.RestartFlag == TRUE)
  {
    Cry_EdDSAVrfyCtx.vrfyState   = CRY_EdDSA_V_S_VERIFY_START;
    Cry_EdDSAVrfyCtx.RestartFlag = FALSE;
  }

  switch (Cry_EdDSAVrfyCtx.vrfyState)
  {
    case CRY_EdDSA_V_S_VERIFY_START:
      Cry_EdDSAVrfyDecodePublicKey();
      break;

    case CRY_EdDSA_V_S_HASH_MSG:
      Cry_EdDSAVrfyHashMsg();
      break;

    case CRY_EdDSA_V_S_VALIDATE_SIG_COMPONENTS:
      Cry_EdDSAVrfyValSigCmp();
      break;

    case CRY_EdDSA_V_S_LITTLE_K:
      Cry_EdDSAVrfyCalculateLittleK();
      break;

    case CRY_EdDSA_V_S_GROUP_EQUATIONS:
      Cry_EdDSAFinishEquation();
      break;

    case CRY_EdDSA_V_S_FINISH_COMPARE:
      Cry_EdDSAValidateSignature();
      break;

    case CRY_EdDSA_V_S_INITIALIZED:
    case CRY_EdDSA_V_S_IDLE:
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Cry_EdDSAVrfyCtx.vrfyState           = CRY_EdDSA_V_S_IDLE;
        Cry_EdDSAVrfyCtx.hashMsgState        = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
        Cry_EdDSAVrfyCtx.littleKState        = CRY_EdDSA_V_S_INIT_SIGN_HASH;
        Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_HASH;

        Csm_SignatureVerifyCallbackNotification(CSM_E_NOT_OK);
        Csm_SignatureVerifyServiceFinishNotification();
        break;
      }
    /* CHECK: PARSE */
  }
}

/** \brief                          Callback function for called subservices.
 *                                  Several CSM sub-services are called during the signature
 *                                  verification and since each service calls a callback function
 *                                  to inform the caller that it has finished, this primitive must
 *                                  provide such a callback. This is that callback function.
 *                                  The name of this function has to be used in the configuration
 *                                  of the callback function of the relevant CSM sub-service.
 *
 *  \param[in]      result          The result of the called sub-service.
 *
 *  \returns        Error value.
 *
 *  \retval         E_OK            Request successful.
 *  \retval         E_NOT_OK        Request failed.
 */
FUNC(Std_ReturnType, CRY_APPL_CODE) Cry_EdDSAVrfyCallback
(
  Csm_ReturnType Result
)
{
  uint8 ProcessDone = FALSE;

  if(Result != CSM_E_OK)
  {
    ProcessDone = TRUE;
  }
  else
  {
    switch (Cry_EdDSAVrfyCtx.vrfyState)
    {
      case CRY_EdDSA_V_S_HASH_MSG:
        switch (Cry_EdDSAVrfyCtx.hashMsgState)
        {
          case CRY_EdDSA_V_S_WAIT_FOR_INIT_HASH_MESSAGE:
            Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_UPDATE_MESSAGE;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_MESSAGE:
            Cry_EdDSAVrfyCtx.vrfyState    = CRY_EdDSA_V_S_INITIALIZED;
            Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
            Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_FINISH_MESSAGE:
            Cry_EdDSAVrfyCtx.vrfyState = CRY_EdDSA_V_S_VALIDATE_SIG_COMPONENTS;
            Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_CONVERT_S;
            Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
            break;

          /* CHECK: NOPARSE */
          /* Defensive Programming - unreachable code.
           * This default case is required by MISRA-C:2004 */
          default:
            {
              break;
            }
          /* CHECK: PARSE */
        }
        break;

      case CRY_EdDSA_V_S_LITTLE_K:
        switch (Cry_EdDSAVrfyCtx.littleKState)
        {
          case CRY_EdDSA_V_S_WAIT_FOR_INIT:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_DOM2;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_DOM2:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_ENC_R;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_R:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_ENC_A;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_A:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_M;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_M:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_FINISH;
            break;

          case CRY_EdDSA_V_S_WAIT_FOR_FINISH:
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_INIT_SIGN_HASH;
            Cry_EdDSAVrfyCtx.vrfyState    = CRY_EdDSA_V_S_GROUP_EQUATIONS;
            break;

          /* CHECK: NOPARSE */
          /* Defensive Programming - unreachable code.
           * This default case is required by MISRA-C:2004 */
          default:
            {
              break;
            }
          /* CHECK: PARSE */
        }
        break;

      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code.
       * This default case is required by MISRA-C:2004 */
      case CRY_EdDSA_V_S_GROUP_EQUATIONS:
      case CRY_EdDSA_V_S_FINISH_COMPARE:
      default:
        {
          break;
        }
      /* CHECK: PARSE */
    }
  }

  if (ProcessDone == TRUE)
  {
    Cry_EdDSAVrfyCtx.vrfyState           = CRY_EdDSA_V_S_IDLE;
    Cry_EdDSAVrfyCtx.decPubKeyState      = CRY_EdDSA_V_S_CONVERT_PUBLICKEY;
    Cry_EdDSAVrfyCtx.hashMsgState        = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
    Cry_EdDSAVrfyCtx.littleKState        = CRY_EdDSA_V_S_INIT_SIGN_HASH;
    Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_HASH;

    Csm_SignatureVerifyCallbackNotification(Result);

    Csm_SignatureVerifyServiceFinishNotification();
  }

  return E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>


/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_EdDSAVrfyDecodePublicKey
(
  void
)
{
  Csm_VerifyResultType decodeResult = CSM_E_VER_NOT_OK;
  uint8 index = 0U;
  uint16 sliceCount;
  boolean finished;


  switch (Cry_EdDSAVrfyCtx.decPubKeyState)
  {
    case CRY_EdDSA_V_S_CONVERT_PUBLICKEY:
      Cry_EdDSAVrfyCtx.tmp1arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

      /* CHECK: NOPARSE */
      /* This branch is unreachable as we have enough memory allocated in the context
       * to store the byte representation of the LN. */
      if (Cry_LNNumberToBEByteArray(Cry_EdDSAVrfyCtx.keyPtr->A,
                                    Cry_EdDSAVrfyCtx.tmp1array,
                                    &(Cry_EdDSAVrfyCtx.tmp1arrayLength)
                                   ) != E_OK
         )
      {
        CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING;
      }
      /* CHECK: PARSE */
      else
      {
        /* Copy tmp1array to tmp2array, as Cry_EdDSAPointDecoding changes
         * the value of the byte array
         */
        Cry_EdDSAVrfyCtx.tmp2arrayLength = Cry_EdDSAVrfyCtx.tmp1arrayLength;
        for (index = 0U; index < Cry_EdDSAVrfyCtx.tmp2arrayLength; index++)
        {
          Cry_EdDSAVrfyCtx.tmp2array[index] = Cry_EdDSAVrfyCtx.tmp1array[index];
        }

        /* The public key was converted to a byte array, start the point decoding */
        Cry_EdDSAPointDecodingStart(&Cry_EdDSAVrfyCtx.EdDSACtx);

        Cry_EdDSAVrfyCtx.decPubKeyState = CRY_EdDSA_V_S_DECODE_PUBLICKEY;
      }
      break;

    case CRY_EdDSA_V_S_DECODE_PUBLICKEY:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* Check if the public key is a valid point on the Edwards curve */
        if (Cry_EdDSAPointDecoding(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                   &Cry_EdDSAVrfyCtx.tmp1Point,
                                   Cry_EdDSAVrfyCtx.tmp,
                                   &decodeResult,
                                   Cry_EdDSAVrfyCtx.tmp2array,
                                   Cry_EdDSAVrfyCtx.tmp2arrayLength
                                  ) == TRUE
           )
        {
          if (decodeResult == CSM_E_VER_OK)
          {
            finished = TRUE;

            /* Point A decoded successfully */
            Cry_EdDSAVrfyCtx.decPubKeyState = CRY_EdDSA_V_S_CONVERT_PUBLICKEY;

            Cry_EdDSAVrfyCtx.vrfyState = CRY_EdDSA_V_S_INITIALIZED;
            Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
          }
          else
          {
            finished = TRUE;

            CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING;
          }
        }
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        CRY_EDDSA_V_HANDLE_FAILING_PUB_KEY_DECODING;
        break;
      }
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAVrfyHashMsg
(
 void
)
{
  Csm_ReturnType RetVal;

  switch (Cry_EdDSAVrfyCtx.hashMsgState)
  {
    case CRY_EdDSA_V_S_INIT_HASH_MESSAGE:
      Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_WAIT_FOR_INIT_HASH_MESSAGE;
      RetVal = Csm_HashStart(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg);

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_INIT_HASH_MESSAGE;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG;
            break;
          }
        }
      break;

    case CRY_EdDSA_V_S_UPDATE_MESSAGE:
        Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_MESSAGE;
        RetVal = Csm_HashUpdate(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                                Cry_EdDSAVrfyCtx.message,
                                Cry_EdDSAVrfyCtx.messageLength
                               );
        switch (RetVal)
        {
          case CSM_E_OK:
            break;

          case CSM_E_BUSY:
            Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_UPDATE_MESSAGE;
            break;

          default:
            {
              CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG;
              break;
            }
        }
      break;

    case CRY_EdDSA_V_S_FINISH_MESSAGE:
      /* hashMessage = PH(M) */
      Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_WAIT_FOR_FINISH_MESSAGE;
      Cry_EdDSAVrfyCtx.hashResultLength = sizeof(Cry_EdDSAVrfyCtx.hashMessage);
      RetVal = Csm_HashFinish(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSAVrfyCtx.hashMessage,
                              &Cry_EdDSAVrfyCtx.hashResultLength,
                              FALSE
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.hashMsgState = CRY_EdDSA_V_S_FINISH_MESSAGE;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_MSG;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_WAIT_FOR_INIT_HASH_MESSAGE:
    case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_MESSAGE:
    case CRY_EdDSA_V_S_WAIT_FOR_FINISH_MESSAGE:
    default:
      {
        break;
      }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAVrfyValSigCmp
(
  void
)
{
  Csm_VerifyResultType decodeResult;
  Cry_ReturnType comparisonZero;
  Cry_ReturnType comparisonL;
  uint8 i;
  uint16 sliceCount;
  boolean finished;


  switch (Cry_EdDSAVrfyCtx.valSigCmpState)
  {
    case CRY_EdDSA_V_S_CONVERT_S:
      /* Convert S to Long Number format */
      /* CHECK: NOPARSE */
      /* This branch is unreachable as we have enough memory allocated in the context
       * to store the byte representation of the LN.
       */
      if (Cry_LNLEByteArrayToNumber(&(Cry_EdDSAVrfyCtx.signature[CRY_EDDSA_V_SIG_S_START_POSITION]),
                                    CRY_EDDSA_V_ARRAY_LEN,
                                    &Cry_EdDSAVrfyCtx.tmp[7U * CRY_EdDSA_TEMP_LEN_WORDS],
                                    CRY_EdDSA_TEMP_LEN_WORDS
                                   ) != E_OK
          )
      {
        CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP;
      }
      else
      /* CHECK: PARSE */
      {
        Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_CHECK_S;
      }
    break;

    case CRY_EdDSA_V_S_CHECK_S:
      /* Use the second word of tmp as a zero value Long Number */
      Cry_EdDSAVrfyCtx.tmp[CRY_EdDSA_TEMP_LEN_WORDS     ] = 1U;
      Cry_EdDSAVrfyCtx.tmp[CRY_EdDSA_TEMP_LEN_WORDS + 1U] = 0U;

      /* Compare S with zero */
      comparisonZero = Cry_LNCompareNumbers(&(Cry_EdDSAVrfyCtx.tmp[7U * CRY_EdDSA_TEMP_LEN_WORDS]),
                                            &(Cry_EdDSAVrfyCtx.tmp[CRY_EdDSA_TEMP_LEN_WORDS]));
      /* Compare S with L */
      comparisonL = Cry_LNCompareNumbers(&(Cry_EdDSAVrfyCtx.tmp[7U * CRY_EdDSA_TEMP_LEN_WORDS]),
                                         &(Cry_EdDSACurveInfo.lValue[0]));

      /* Check if S is in the range [0; L) */
      if (((comparisonZero == CRY_E_EQUAL) || (comparisonZero == CRY_E_LARGER))
           &&
          (comparisonL == CRY_E_SMALLER))
      {
        Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_COPY_R;
      }
      else
      {
        CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP;
      }
    break;

    case CRY_EdDSA_V_S_COPY_R:
      /* tmp2array : first part of Signature, ENC(R) */
      Cry_EdDSAVrfyCtx.tmp2arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

      for(i = 0U; i < Cry_EdDSAVrfyCtx.tmp2arrayLength; i++)
      {
        Cry_EdDSAVrfyCtx.tmp2array[i] = Cry_EdDSAVrfyCtx.signature[i];
      }

      Cry_EdDSAPointDecodingStart(&Cry_EdDSAVrfyCtx.EdDSACtx);
      Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_DECODE_R;
    break;

    case CRY_EdDSA_V_S_DECODE_R:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        if (Cry_EdDSAPointDecoding(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                   &Cry_EdDSAVrfyCtx.tmp2Point,
                                   Cry_EdDSAVrfyCtx.tmp,
                                   &decodeResult,
                                   Cry_EdDSAVrfyCtx.tmp2array,
                                   Cry_EdDSAVrfyCtx.tmp2arrayLength
                                  ) == TRUE
           )
        {
          if (decodeResult == CSM_E_VER_OK)
          {
            /* Point R decoded successfully, proceed with calculating k */
            Cry_EdDSAVrfyCtx.valSigCmpState = CRY_EdDSA_V_S_CONVERT_S;

            Cry_EdDSAVrfyCtx.vrfyState = CRY_EdDSA_V_S_LITTLE_K;
            Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_INIT_SIGN_HASH;

            finished = TRUE;
          }
          else
          {
            finished = TRUE;

            CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP;
          }
        }
      }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      CRY_EDDSA_V_HANDLE_FAILING_VALIDATE_SIG_CMP;
      break;
    }
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAVrfyCalculateLittleK
(
 void
)
{
  Csm_ReturnType RetVal;

  switch (Cry_EdDSAVrfyCtx.littleKState)
  {
    case CRY_EdDSA_V_S_INIT_SIGN_HASH:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_INIT;
      RetVal = Csm_HashStart(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg);

      switch(RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_INIT_SIGN_HASH;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_UPDATE_DOM2:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_DOM2;
      /* Hash the parameter "dom" */
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_DOM2;
      RetVal = Csm_HashUpdate(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSADOM,
                              CRY_EDDSA_DOM_LEN
                             );
      switch(RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_DOM2;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_UPDATE_ENC_R:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_R;
      /* Hash ENC(R), the first half of the signature */
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_R;
      RetVal = Csm_HashUpdate(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSAVrfyCtx.signature,
                              (Cry_EdDSAVrfyCtx.signatureLength >> 1U)
                             );
      switch(RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_ENC_R;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_UPDATE_ENC_A:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_A;
      /* tmp1array: the public key, ENC(A) */
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_A;
      RetVal = Csm_HashUpdate(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSAVrfyCtx.tmp1array,
                              Cry_EdDSAVrfyCtx.tmp1arrayLength
                             );

      switch(RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_ENC_A;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_UPDATE_M:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_M;
     /* Hash the prehashed message (PH(M)) */
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_UPDATE_M;
      RetVal = Csm_HashUpdate(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSAVrfyCtx.hashMessage,
                              sizeof(Cry_EdDSAVrfyCtx.hashMessage)
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_UPDATE_M;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_FINISH:
      Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_WAIT_FOR_FINISH;
      Cry_EdDSAVrfyCtx.hashResultLength = sizeof(Cry_EdDSAVrfyCtx.hashResult);
      RetVal = Csm_HashFinish(Cry_EdDSAVrfyCtx.cfgPtr->HashCfg,
                              Cry_EdDSAVrfyCtx.hashResult,
                              &(Cry_EdDSAVrfyCtx.hashResultLength),
                              TRUE
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAVrfyCtx.littleKState = CRY_EdDSA_V_S_FINISH;
          break;

        default:
          {
            CRY_EDDSA_V_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_V_S_WAIT_FOR_INIT:
    case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_DOM2:
    case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_R:
    case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_ENC_A:
    case CRY_EdDSA_V_S_WAIT_FOR_UPDATE_M:
    case CRY_EdDSA_V_S_WAIT_FOR_FINISH:
    default:
      {
        break;
      }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAFinishEquation
(
 void
)
{
  uint16 sliceCount;
  boolean finished;

  switch (Cry_EdDSAVrfyCtx.finishEquationState)
  {
    case CRY_EdDSA_V_S_HASH:
      Cry_EdDSAHashByteToNum();
      break;

    case CRY_EdDSA_V_S_HASH_RED:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* tmp6 = hashValue % lValue */
        if (Cry_LNModulo(&Cry_EdDSAVrfyCtx.tmp[6U * CRY_EdDSA_TEMP_LEN_WORDS],
                         Cry_EdDSACurveInfo.lValue,
                         &Cry_EdDSAVrfyCtx.LNCtx
                        ) == TRUE
           )
        {
          Cry_EdDSAPointMultiplicationStart(&Cry_EdDSAVrfyCtx.EdDSACtx);
          Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_FINISH_EQUATION_1;

          finished = TRUE;
        }
      }
      break;

    case CRY_EdDSA_V_S_FINISH_EQUATION_1:
      Cry_EdDSACalculateKA();
      break;

    case CRY_EdDSA_V_S_FINISH_EQUATION_2:
      /* tmp1Point = R + (k * A): tmp2Point + tmp3Point */
      Cry_EdDSACalculateRkA();
      break;

    case CRY_EdDSA_V_S_FINISH_EQUATION_2_ENC:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* tmp1array = ENC(R + (k * A)) */
        if (Cry_EdDSAPointEncoding(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                   &Cry_EdDSAVrfyCtx.tmp4Point,
                                   Cry_EdDSAVrfyCtx.tmp,
                                   Cry_EdDSAVrfyCtx.tmp1array,
                                   Cry_EdDSAVrfyCtx.tmp2array,
                                   Cry_EdDSAVrfyCtx.tmp1arrayLength,
                                   Cry_EdDSAVrfyCtx.tmp2arrayLength
                                  ) == TRUE
           )
         {
           Cry_EdDSAPointMultiplicationStart(&Cry_EdDSAVrfyCtx.EdDSACtx);

           Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_FINISH_EQUATION_3;

           finished = TRUE;
         }
      }
      break;

    case CRY_EdDSA_V_S_FINISH_EQUATION_3:
      /* tmp2Point = S * B: tmp4 * Base Point */
      Cry_EdDSACalculateSB();
      break;

    case CRY_EdDSA_V_S_FINISH_EQUATION_3_ENC:
      /* tmp3array = ENC(S * B) */
      Cry_EdDSAVrfyCtx.tmp3arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        if (Cry_EdDSAPointEncoding(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                   &Cry_EdDSAVrfyCtx.tmp3Point,
                                   Cry_EdDSAVrfyCtx.tmp,
                                   Cry_EdDSAVrfyCtx.tmp3array,
                                   Cry_EdDSAVrfyCtx.tmp2array,
                                   Cry_EdDSAVrfyCtx.tmp3arrayLength,
                                   Cry_EdDSAVrfyCtx.tmp2arrayLength
                                  ) == TRUE
           )
        {
          Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_HASH;
          Cry_EdDSAVrfyCtx.vrfyState           = CRY_EdDSA_V_S_FINISH_COMPARE;

          finished = TRUE;
        }
      }
      break;

      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code.
       * This default case is required by MISRA-C:2004 */
      default:
      {
        break;
      }
      /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSACalculateSB
(
 void
)
{
  boolean finished = FALSE;
  uint16 sliceCount = 0U;

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
  while (
         (finished == FALSE) &&
         (
          (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
          (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
         )
        )
  {
    sliceCount++;

    if (Cry_EdDSAPointMultiplication(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                    &Cry_EdDSAVrfyCtx.tmp3Point,
                                    &(Cry_EdDSACurveInfo.P),
                                    &Cry_EdDSAVrfyCtx.tmp[7U * CRY_EdDSA_TEMP_LEN_WORDS],
                                    Cry_EdDSAVrfyCtx.tmp
                                    ) == TRUE
      )
    {
      Cry_EdDSAPointEncodingStart(&Cry_EdDSAVrfyCtx.EdDSACtx);
      Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_FINISH_EQUATION_3_ENC;

      finished = TRUE;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSACalculateKA
(
 void
)
{
  boolean finished = FALSE;
  uint16 sliceCount = 0U;

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
  while (
         (finished == FALSE) &&
         (
          (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
          (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
         )
        )
  {
    sliceCount++;

    /* tmp3Point = k * A: tmp6 * tmp1Point */
    if (Cry_EdDSAPointMultiplication(&Cry_EdDSAVrfyCtx.EdDSACtx,
                                     &Cry_EdDSAVrfyCtx.tmp3Point,
                                     &Cry_EdDSAVrfyCtx.tmp1Point,
                                     &Cry_EdDSAVrfyCtx.tmp[6U * CRY_EdDSA_TEMP_LEN_WORDS],
                                     Cry_EdDSAVrfyCtx.tmp
                                    ) == TRUE
       )
    {
      Cry_EdDSAPointAdditionStart(&Cry_EdDSAVrfyCtx.EdDSACtx);
      Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_FINISH_EQUATION_2;

      finished = TRUE;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAHashByteToNum
(
 void
)
{
  /* CHECK: NOPARSE */
  /* This branch is unreachable as we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  if (Cry_LNLEByteArrayToNumber(Cry_EdDSAVrfyCtx.hashResult,
                                Cry_EdDSAVrfyCtx.hashResultLength,
                                &Cry_EdDSAVrfyCtx.tmp[6U * CRY_EdDSA_TEMP_LEN_WORDS],
                                CRY_EdDSA_TEMP_LEN_WORDS
                               ) != E_OK
     )
  {
    Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_IDLE;

    Csm_SignatureVerifyCallbackNotification(CSM_E_SMALL_BUFFER);

    Csm_SignatureVerifyServiceFinishNotification();
  }
  else
  /* CHECK: PARSE */
  {
    Cry_LNModuloStart(&Cry_EdDSAVrfyCtx.LNCtx);
    Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_HASH_RED;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSACalculateRkA
(
  void
)
{
  boolean finished = FALSE;
  uint16 sliceCount = 0U;

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue0,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValue1,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureVerifyTimeSlicesValueGreaterThan1,1 */
  while (
      (finished == FALSE) &&
      (
       (Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
       (sliceCount < Cry_EdDSAVrfyCtx.cfgPtr->NumberOfTimeSlices)
      )
      )
  {
    sliceCount++;

    if (Cry_EdDSAPointAddition(&Cry_EdDSAVrfyCtx.EdDSACtx,
                               &Cry_EdDSAVrfyCtx.tmp4Point,
                               &Cry_EdDSAVrfyCtx.tmp2Point,
                               &Cry_EdDSAVrfyCtx.tmp3Point,
                               Cry_EdDSAVrfyCtx.tmp
                              ) == TRUE
       )
    {
      Cry_EdDSAPointEncodingStart(&Cry_EdDSAVrfyCtx.EdDSACtx);
      Cry_EdDSAVrfyCtx.finishEquationState = CRY_EdDSA_V_S_FINISH_EQUATION_2_ENC;

      finished = TRUE;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAValidateSignature
(
 void
)
{
  Csm_VerifyResultType Result;
  uint32 i;

  /*
   *  S * B == R + (k * A): tmp3Point == tmp4Point
   *  The other possibility would be:
   *  Cry_EdDSAVrfyCtx.tmp3array == Cry_EdDSAVrfyCtx.tmp1array
   *  The points are converted to Affine coordinate. There is no need to
   *  check the z-coordinate of the points.
   *
   */
  Result = CSM_E_VER_OK;

  /* CHECK: NOPARSE */
  /* Defensive Programming - unreachable code.
   * This default case is required by MISRA-C:2004
   * An invalid public key that it's still a valid point on the curve need to be found.
   */
  if ((Cry_EdDSAVrfyCtx.tmp3Point.xValue[0U] != Cry_EdDSAVrfyCtx.tmp4Point.xValue[0U]) ||
      (Cry_EdDSAVrfyCtx.tmp3Point.yValue[0U] != Cry_EdDSAVrfyCtx.tmp4Point.yValue[0U])
    )
  {
    Result = CSM_E_VER_NOT_OK;
  }
  else
  /* CHECK: PARSE */
  {
    for(i = 1U; i <= Cry_EdDSAVrfyCtx.tmp3Point.xValue[0U]; i++)
    {
      if(Cry_EdDSAVrfyCtx.tmp3Point.xValue[i] != Cry_EdDSAVrfyCtx.tmp4Point.xValue[i])
      {
        Result = CSM_E_VER_NOT_OK;
        break;
      }
    }

    for(i = 1U; i <= Cry_EdDSAVrfyCtx.tmp3Point.yValue[0U]; i++)
    {
      if(Cry_EdDSAVrfyCtx.tmp3Point.yValue[i] != Cry_EdDSAVrfyCtx.tmp4Point.yValue[i])
      {
        Result = CSM_E_VER_NOT_OK;
        break;
      }
    }
  }

  *Cry_EdDSAVrfyCtx.resultPtr = Result;
  Cry_EdDSAVrfyCtx.vrfyState  = CRY_EdDSA_V_S_IDLE;

  Csm_SignatureVerifyCallbackNotification(CSM_E_OK);
  Csm_SignatureVerifyServiceFinishNotification();
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* (CRY_EDDSA_VRFY_ENABLED == STD_ON) */

/** \brief Dummy definition preventing this file from being empty */
typedef void Cry_EdDSAVrfy_EmptyTranslationUnitType;

#endif /* (CRY_EDDSA_VRFY_ENABLED == STD_ON) */
