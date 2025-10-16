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

/* Nomenclature from "Edwards-curve Digital Signature Algorithm (EdDSA)"
 * www.tools.ietf.org/html/draft-irtf-cfrg-eddsa-08 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>
#include <Csm_Hash.h>
#include <Csm_SignatureGenerate.h>
#include <Csm_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>
#include <Cry_EdDSAGen.h>

#if (CRY_EDDSA_GEN_ENABLED == STD_ON)
/*==[Macros]==================================================================*/

#if (defined CRY_EDDSA_SIGN_SIZE)
#error CRY_EDDSA_SIGN_SIZE is already defined
#endif
/** \brief The EdDSA siganture size in bytes. */
#define CRY_EDDSA_SIGN_SIZE 64U

#if (defined CRY_EDDSA_G_ARRAY_LEN)
#error CRY_EDDSA_G_ARRAY_LEN is already defined
#endif
/** \brief The maximal allowed length for a Byte-array in bytes. */
#define CRY_EDDSA_G_ARRAY_LEN 32U

#if (defined CRY_EDDSA_G_HASH_MAX_LEN)
#error CRY_EDDSA_G_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes. */
#define CRY_EDDSA_G_HASH_MAX_LEN (CRY_EDDSA_G_ARRAY_LEN << 1U)

#if (defined CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK)
#error CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK is already defined
#endif
/** \brief Handle failing Hash service while processing the private key */
#define CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK do {                                                 \
                                Cry_EdDSAGenCtx.genState         = CRY_EdDSA_G_S_IDLE;             \
                                Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_INIT_1;           \
                                Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);           \
                                Csm_SignatureGenerateServiceFinishNotification();                  \
                              } while(0U)

#if (defined CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG)
#error CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG is already defined
#endif
/** \brief Handle failing Hash service while processing the message */
#define CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG do {                                              \
                          Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_IDLE;                  \
                          Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;     \
                          Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);            \
                          Csm_SignatureGenerateServiceFinishNotification();                   \
                        } while(0U)

#if (defined CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR)
#error CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR is already defined
#endif
/** \brief Handle failing Hash service while processing r */
#define CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR do {                                             \
                                     Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_IDLE;       \
                                     Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_INIT_2;     \
                                     Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK); \
                                     Csm_SignatureGenerateServiceFinishNotification();        \
                                    } while(0U)

#if (defined CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK)
#error CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK is already defined
#endif
/** \brief Handle failing Hash service while processing k */
#define CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK do {                                             \
                                      Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_IDLE;      \
                                      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_INIT_3;    \
                                      Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);\
                                      Csm_SignatureGenerateServiceFinishNotification();       \
                                    } while(0U)

/*==[Types]===================================================================*/

/** \brief State machine for signature generation */
typedef enum
{
  /** \brief Waiting for new operation */
  CRY_EdDSA_G_S_IDLE,

  /** \brief The signature generation is initialized */
  CRY_EdDSA_G_S_INITIALIZED,

  /** \brief Start hashing of the private key */
  CRY_EdDSA_G_S_HASH_PRIV_K,

  /** \brief Start hashing of the message */
  CRY_EdDSA_G_S_HASH_MESSAGE,

  /** \brief Calculate r */
  CRY_EdDSA_G_S_LITTLE_R,

  /** \brief Convert scalar r to LN */
  CRY_EdDSA_G_S_FINISH_SCALARR1,

  /** \brief Calculate k */
  CRY_EdDSA_G_S_LITTLE_K,

  /** \brief Convert the calculated hash into LN */
  CRY_EdDSA_G_S_FINISH_SIG
}
Cry_EdDSAGenStateType;

/** \brief Internal state of scalar calculation */
typedef enum
{
  /** \brief Convert scalar r to LN */
  CRY_EdDSA_G_S_FINISH_SCALARR1_INT,

  /** \brief Calculate r = r % lValue */
  CRY_EdDSA_G_S_FINISH_SCALARR2,

  /** \brief Calculate R = r * base point B */
  CRY_EdDSA_G_S_FINISH_SCALARR3
}
Cry_EdDSAGenScalarsStateType;

/** \brief Internal state for the finish of signature generation */
typedef enum
{
  /** \brief Convert the calculated hash into LN */
  CRY_EdDSA_G_S_FINISH_S1,

  /** \brief Calculate hash % lValue */
  CRY_EdDSA_G_S_FINISH_S2_TEMP,

  /** \brief Calculate HashResult * Scalar s */
  CRY_EdDSA_G_S_FINISH_S2,

  /** \brief Calculate r + (k * s) */
  CRY_EdDSA_G_S_FINISH_EXPORT,

  /** \brief Export the signature */
  CRY_EdDSA_G_S_FINISH_EXPORT_TEMP
}
Cry_EdDSAGenFinishSigStateType;

/** \brief Internal state of the message hashing */
typedef enum
{
  /** \brief Start hashing of the message */
  CRY_EdDSA_G_S_INIT_HASH_MESSAGE,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_G_S_WAIT_FOR_INIT_HASH_MESSAGE,

  /** \brief Hash message blocks */
  CRY_EdDSA_G_S_UPDATE_HASH_MESSAGE,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HASH_MESSAGE,

  /** \brief Finish the message hashing */
  CRY_EdDSA_G_S_FINISH_HASH_MESSAGE,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_MESSAGE
}
Cry_EdDSAGenHashMsgStateType;

/** \brief Internal state of the private key hashing */
typedef enum
{
  /** \brief Start hashing of the private key */
  CRY_EdDSA_G_S_INIT_1,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_G_S_WAIT_FOR_INIT_1,

  /** \brief Hash the private key */
  CRY_EdDSA_G_S_UPDATE_K,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_K,

  /** \brief Finish the private key hashing */
  CRY_EdDSA_G_S_FINISH_HASH_1,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_1,

  /** \brief Calculate the private scalar s */
  CRY_EdDSA_G_S_FINISH_SCALARS,

  /** \brief Calculate A = s * base point B */
  CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_1,

  /** \brief Encode A */
  CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_2
}
Cry_EdDSAGenPrivKeyHashStateType;

/** \brief Internal state of the r calculation */
typedef enum
{
  /** \brief Start hashing h_b to h_(2*b-1) */
  CRY_EdDSA_G_S_INIT_2,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_G_S_WAIT_FOR_INIT_2,

  /** \brief Hash Context string for Ed25519ph */
  CRY_EdDSA_G_S_UPDATE_DOM2_1,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_1,

  /** \brief Hash h_b to h_(2*b-1) */
  CRY_EdDSA_G_S_UPDATE_HB,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HB,

  /** \brief Hash again H(M) */
  CRY_EdDSA_G_S_UPDATE_M,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M,

  /** \brief Finish hashing, SHA512(dom||h_b,...,h_(2*b-1)||PH(M))*/
  CRY_EdDSA_G_S_FINISH_HASH_2,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_2
}
Cry_EdDSAGenLittleRStateType;

/** \brief Internal state of the k calculation */
typedef enum
{
  /** \brief Start hashing of (dom||R||A||PH(M)) */
  CRY_EdDSA_G_S_INIT_3,

  /** \brief Wait for the HashStart callback */
  CRY_EdDSA_G_S_WAIT_FOR_INIT_3,

  /** \brief Hash Context string for Ed25519ph. */
  CRY_EdDSA_G_S_UPDATE_DOM2_2,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_2,

  /** \brief Encode R and hash it */
  CRY_EdDSA_G_S_UPDATE_R,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_R,

  /** \brief Hash A */
  CRY_EdDSA_G_S_UPDATE_A,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_A,

  /** \brief Hash PH(M) */
  CRY_EdDSA_G_S_UPDATE_M2,

  /** \brief Wait for the HashUpdate callback */
  CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M2,

  /** \brief Finish hashing */
  CRY_EdDSA_G_S_FINISH_HASH_3,

  /** \brief Wait for the HashFinish callback */
  CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_3
}
Cry_EdDSAGenLittleKStateType;

/** \brief Context for the signature generation */
typedef struct
{
  /** \brief The length of the hash digest. */
  uint32                                                   hashResultLength;

  /** \brief The length of the data whose signature has to be generated. */
  uint32                                                   messageLength;

  /** \brief Length of the byte array. */
  uint32                                                   tmp2arrayLength;

  /** \brief Length of the byte array. */
  uint32                                                   tmp1arrayLength;

  /** \brief Length of the byte array. */
  uint32                                                   tmp3arrayLength;

  /** \brief Pointer to the current EdDSA signature generation configuration. */
  P2CONST(Cry_EdDSAGenConfigType, TYPEDEF, CRY_APPL_CONST) cfgPtr;

  /** \brief Pointer to message whose signature has to be generated. */
  P2CONST(uint8,                  TYPEDEF, CRY_APPL_CONST) message;

  /** \brief Pointer to a variable where the result of the signature generation is stored. */
  P2VAR(uint8,                    TYPEDEF, CRY_APPL_DATA ) result;

  /** \brief Pointer to a variable where the result length of the signature generation is stored. */
  P2VAR(uint32,                   TYPEDEF, CRY_APPL_DATA ) resultLength;

  /** \brief Pointer to the secret key which should be used for creating the signature. */
  P2CONST(Cry_EdDSAGenKeyType,    TYPEDEF, CRY_APPL_CONST) privateKeyPtr;

  /** \brief The context which has to be used for Edwards curve arithmetic. */
  Cry_EdDSACtxType                                         EdDSACtx;

  /** \brief The context which has to be used for long number arithmetic. */
  Cry_LNCtxType                                            LNCtx;

  /** \brief A point, which is used to store the result of R = ScalarR * base point. */
  Cry_EdDSAPointType                                       R;

  /** \brief A point which is used as a buffer during signature generation. */
  Cry_EdDSAPointType                                       A;

  /** \brief An array which is used as a buffer during signature generation. */
  Cry_LNWordType                                           tmp[6U * CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief An array which is used to store the scalar R. */
  Cry_LNWordType                                           scalarR[CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief An array which is used to store the scalar S. */
  Cry_LNWordType                                           scalarS[CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief The current state the EdDSA signature generation is in. */
  Cry_EdDSAGenStateType                                    genState;

  /** \brief The current state the EdDSA signature generation is in. */
  Cry_EdDSAGenFinishSigStateType                           genFinishSig;

  /** \brief The current state the EdDSA scalar generation is in. */
  Cry_EdDSAGenScalarsStateType                             scalarsState;

  /** \brief  The current state the private key hashing is in. */
  Cry_EdDSAGenPrivKeyHashStateType                         privKeyHashState;

  /** \brief  The current state the message hashing is in. */
  Cry_EdDSAGenHashMsgStateType                             msgHashState;

  /** \brief  The current state the calculation of r is in. */
  Cry_EdDSAGenLittleRStateType                             littleRState;

  /** \brief  The current state the calculation of k is in. */
  Cry_EdDSAGenLittleKStateType                             littleKState;

  /** \brief Pointer to the buffer where the hash value of the data will be saved. */
  uint8                                                    hashResult[CRY_EDDSA_G_HASH_MAX_LEN];

  /** \brief A byte array which is used as a buffer during signature generation. */
  uint8                                                    tmp1array[CRY_EDDSA_G_ARRAY_LEN];

  /** \brief A byte array which is used as a buffer during signature generation. */
  uint8                                                    tmp2array[CRY_EDDSA_G_ARRAY_LEN];

  /** \brief A byte array which is used as a buffer during signature generation. */
  uint8                                                    tmp3array[CRY_EDDSA_G_ARRAY_LEN];

  /** \brief Pointer to the buffer where the message to be hashed is stored. */
  uint8                                                    hashMessage[CRY_EDDSA_G_HASH_MAX_LEN];

  /** \brief Flag to indicate if the hashing of the message started. */
  boolean                                                  msgHashStarted;

  /** \brief Flag that states if the restart of the service is active. */
  boolean                                                  RestartFlag;
}
Cry_EdDSAGenCtxType;

/*==[Declaration of functions with internal linkage]==========================*/
#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Process the private key. */
static FUNC(void, CRY_CODE) Cry_EdDSAProcessPrivKey
(
  void
);

/** \brief Hash the message. */
static FUNC(void, CRY_CODE) Cry_EdDSAGenHashMsg
(
  void
);

/** \brief Calculate little r. */
static FUNC(void, CRY_CODE) Cry_EdDSACalculateLittleR
(
  void
);

/** \brief Calculate little k. */
static FUNC(void, CRY_CODE) Cry_EdDSAGenCalculateLittleK
(
  void
);

/** \brief Convert R to a byte array and encode it for the HashUpdate function. */
static FUNC(void, CRY_CODE) Cry_EdDSAEncodeAndHashR
(
  void
);

/** \brief Calculate the scalars. */
static FUNC(void, CRY_CODE) Cry_EdDSACalculateScalars
(
  void
);

/** \brief Finish the signature generation. */
static FUNC(void, CRY_CODE) Cry_EdDSAFinishSignature
(
  void
);

/** \brief Callback for the hash APIs in the k calculation.
 *
 */
static FUNC(void, CRY_CODE) Cry_EdDSALittleKCallback
(
  void
);

/** \brief Callback for the hash APIs in the r calculation. */
static FUNC(void, CRY_CODE) Cry_EdDSALittleRCallback
(
  void
);

/** \brief Callback for the hash APIs in the message hashing. */
static FUNC(void, CRY_CODE) Cry_EdDSAHashMsgCallback
(
  void
);

/** \brief Callback for the hash APIs in the private key hashing. */
static FUNC(void, CRY_CODE) Cry_EdDSAPrivKeyCallback
(
  void
);

/** \brief Prepare the final signature. */
static FUNC(void, CRY_CODE) Cry_EdDSAExportSign
(
  void
);

/** \brief Prepare S from digest. */
static FUNC(void, CRY_CODE) Cry_EdDSAEncodeSFromHash
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/
#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief EdDSA signature generation context */
static VAR(Cry_EdDSAGenCtxType, CRY_VAR) Cry_EdDSAGenCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0178,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenStart
(
  P2CONST(void,                   AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRY_APPL_DATA) privateKeyPtr
)
{
  Csm_ReturnType RetVal;

#if (CRY_EDDSAGEN_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_EdDSA_G_S_IDLE == Cry_EdDSAGenCtx.genState)
  {
    Cry_EdDSAGenCtx.RestartFlag = FALSE;

    /* Store data into context */
    Cry_EdDSAGenCtx.cfgPtr = (P2CONST(Cry_EdDSAGenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    /* Deviation MISRAC2012-1 */
    Cry_EdDSAGenCtx.privateKeyPtr =
                  (P2CONST(Cry_EdDSAGenKeyType, TYPEDEF, CRY_APPL_CONST))privateKeyPtr;

    /* Set state of the state machine */
    Cry_EdDSAGenCtx.genState = CRY_EdDSA_G_S_HASH_PRIV_K;

    Cry_EdDSAGenCtx.msgHashStarted = FALSE;

    RetVal = CSM_E_OK;
  }
  else if((Cry_EdDSAGenCtx.cfgPtr->SupportRestart == TRUE) && (Cry_EdDSAGenCtx.cfgPtr == cfgPtr))
  {
    /* !LINKSTO EB_Cry_Restart_CryEdDSAGen,1 */
    Cry_EdDSAGenCtx.RestartFlag = TRUE;

    /* Set state of the state machine */
    Cry_EdDSAGenCtx.genState = CRY_EdDSA_G_S_HASH_PRIV_K;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  /* Store data into context */
  Cry_EdDSAGenCtx.cfgPtr = (P2CONST(Cry_EdDSAGenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

  /* Deviation MISRAC2012-1 */
  Cry_EdDSAGenCtx.privateKeyPtr =
                (P2CONST(Cry_EdDSAGenKeyType, TYPEDEF, CRY_APPL_CONST))privateKeyPtr;

  /* Set state of the state machine */
  Cry_EdDSAGenCtx.genState = CRY_EdDSA_G_S_HASH_PRIV_K;

  Cry_EdDSAGenCtx.msgHashStarted = FALSE;

  RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0179,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if(CRY_EdDSA_G_S_IDLE == Cry_EdDSAGenCtx.genState)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_EdDSA_G_S_INITIALIZED == Cry_EdDSAGenCtx.genState)
  {
    /* Store data into context */
    Cry_EdDSAGenCtx.message = dataPtr;
    Cry_EdDSAGenCtx.messageLength = dataLength;

    /* First message block to be hashed */
    if(Cry_EdDSAGenCtx.msgHashStarted == FALSE)
    {
      Cry_EdDSAGenCtx.msgHashStarted = TRUE;
      Cry_EdDSAGenCtx.msgHashState   = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;
    }
    else
    {
      /* Subsequent message blocks to be hashed */
      Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_UPDATE_HASH_MESSAGE;
    }

    /* Set state of the state machine to update */
    Cry_EdDSAGenCtx.genState = CRY_EdDSA_G_S_HASH_MESSAGE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0180,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenFinish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr
)
{
  Csm_ReturnType RetVal;

  if(CRY_EdDSA_G_S_IDLE == Cry_EdDSAGenCtx.genState)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(*resultLengthPtr < CRY_EDDSA_SIGN_SIZE)
  {
    RetVal = CSM_E_SMALL_BUFFER;
  }
  else if((Cry_EdDSAGenCtx.msgHashStarted == TRUE                    ) &&
          (CRY_EdDSA_G_S_INITIALIZED      == Cry_EdDSAGenCtx.genState)
         )
  {
    /* Store data into context */
    Cry_EdDSAGenCtx.result = resultPtr;

    Cry_EdDSAGenCtx.resultLength = resultLengthPtr;

    /* Set state of the state machine to Update */
    Cry_EdDSAGenCtx.genState       = CRY_EdDSA_G_S_HASH_MESSAGE;
    Cry_EdDSAGenCtx.msgHashState   = CRY_EdDSA_G_S_FINISH_HASH_MESSAGE;
    Cry_EdDSAGenCtx.msgHashStarted = FALSE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0181,1 */
FUNC(void, CRY_APPL_CODE) Cry_EdDSAGenMainFunction
(
   void
)
{
  if (Cry_EdDSAGenCtx.RestartFlag == TRUE)
  {
    Cry_EdDSAGenCtx.genState    = CRY_EdDSA_G_S_HASH_PRIV_K;
    Cry_EdDSAGenCtx.RestartFlag = FALSE;
  }

  switch (Cry_EdDSAGenCtx.genState)
  {
    case CRY_EdDSA_G_S_HASH_PRIV_K:
      Cry_EdDSAProcessPrivKey();
      break;

    case CRY_EdDSA_G_S_HASH_MESSAGE:
      Cry_EdDSAGenHashMsg();
      break;

    case CRY_EdDSA_G_S_LITTLE_R:
     Cry_EdDSACalculateLittleR();
     break;

    case CRY_EdDSA_G_S_FINISH_SCALARR1:
      Cry_EdDSACalculateScalars();
      break;

    case CRY_EdDSA_G_S_LITTLE_K:
      Cry_EdDSAGenCalculateLittleK();
      break;

    case CRY_EdDSA_G_S_FINISH_SIG:
      Cry_EdDSAFinishSignature();
      break;

    case CRY_EdDSA_G_S_INITIALIZED:
    case CRY_EdDSA_G_S_IDLE:
      {
        break;
      }

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Cry_EdDSAGenCtx.genState         = CRY_EdDSA_G_S_IDLE;
        Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_INIT_1;
        Cry_EdDSAGenCtx.msgHashState     = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;
        Cry_EdDSAGenCtx.littleRState     = CRY_EdDSA_G_S_INIT_2;
        Cry_EdDSAGenCtx.scalarsState     = CRY_EdDSA_G_S_FINISH_SCALARR1_INT;
        Cry_EdDSAGenCtx.littleKState     = CRY_EdDSA_G_S_INIT_3;
        Cry_EdDSAGenCtx.genFinishSig     = CRY_EdDSA_G_S_FINISH_S1;

        Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);
        Csm_SignatureGenerateServiceFinishNotification();
        break;
      }
    /* CHECK: PARSE */
  }
}

/** \brief Several CSM sub-services are called during the signature generation and
 *         since each service calls a callback function to inform the caller that it
 *         has finished, this primitive must provide such a callback. This is that
 *         callback function. The name of this function has to be used in the
 *         configuration of the callback function of the relevant CSM sub-service.
 *
 * \param[in]       Result          The result of the underlying cryptographic service.
 *
 *  \returns        Error value.
 *
 *  \retval         CSM_E_OK        If the service can be started.
 *  \retval         CSM_E_NOT_OK    If the key is invalid.
 *  \retval         CSM_E_BUSY      If another instance of this service is already running.
 */
FUNC(Std_ReturnType, CRY_APPL_CODE) Cry_EdDSAGenCallback
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
    switch (Cry_EdDSAGenCtx.genState)
    {
      case CRY_EdDSA_G_S_HASH_PRIV_K:
        Cry_EdDSAPrivKeyCallback();
        break;

      case CRY_EdDSA_G_S_HASH_MESSAGE:
        Cry_EdDSAHashMsgCallback();
        break;

      case CRY_EdDSA_G_S_LITTLE_R:
        Cry_EdDSALittleRCallback();
        break;

      case CRY_EdDSA_G_S_LITTLE_K:
        Cry_EdDSALittleKCallback();
        break;

      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code.
       * This default case is required by MISRA-C:2004 */
      case CRY_EdDSA_G_S_INITIALIZED:
      case CRY_EdDSA_G_S_FINISH_SIG:
      case CRY_EdDSA_G_S_FINISH_SCALARR1:
      default:
        {
          break;
        }
      /* CHECK: PARSE */
    }
  }

  if( ProcessDone == TRUE )
  {
    Cry_EdDSAGenCtx.genState         = CRY_EdDSA_G_S_IDLE;
    Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_INIT_1;
    Cry_EdDSAGenCtx.msgHashState     = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;
    Cry_EdDSAGenCtx.littleRState     = CRY_EdDSA_G_S_INIT_2;
    Cry_EdDSAGenCtx.scalarsState     = CRY_EdDSA_G_S_FINISH_SCALARR1_INT;
    Cry_EdDSAGenCtx.littleKState     = CRY_EdDSA_G_S_INIT_3;
    Cry_EdDSAGenCtx.genFinishSig     = CRY_EdDSA_G_S_FINISH_S1;

    Csm_SignatureGenerateCallbackNotification(Result);
    Csm_SignatureGenerateServiceFinishNotification();
  }

  return E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_EdDSAProcessPrivKey
(
 void
)
{
  Csm_ReturnType RetVal;
  uint16 sliceCount;
  boolean finished;

  switch (Cry_EdDSAGenCtx.privKeyHashState)
  {
    case CRY_EdDSA_G_S_INIT_1:
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_WAIT_FOR_INIT_1;
      RetVal = Csm_HashStart(Cry_EdDSAGenCtx.cfgPtr->HashCfg);

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_INIT_1;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_UPDATE_K:
      /* convert the private key to Byte-Array, Result = Private Key */

      Cry_EdDSAGenCtx.tmp1arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

      /* CHECK: NOPARSE */
      /* This branch is unreachable as we have enough memory allocated in the context
       * to store the byte representation of the LN. */
      if (Cry_LNNumberToBEByteArray(Cry_EdDSAGenCtx.privateKeyPtr->D,
                                    Cry_EdDSAGenCtx.tmp1array,
                                    &(Cry_EdDSAGenCtx.tmp1arrayLength)
                                   ) != E_OK
         )
      {
        CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK;
      }
      else
      /* CHECK: PARSE */
      {
        Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_K;
        RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                                Cry_EdDSAGenCtx.tmp1array,
                                Cry_EdDSAGenCtx.tmp1arrayLength
                               );
        switch (RetVal)
        {
          case CSM_E_OK:
            break;

          case CSM_E_BUSY:
            Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_UPDATE_K;
            break;

          default:
            {
              CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK;
              break;
            }
        }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_HASH_1:
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_1;
      /* finish the hashing function and receive the hashed value */
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_1;
      Cry_EdDSAGenCtx.hashResultLength = sizeof(Cry_EdDSAGenCtx.hashResult);
      RetVal = Csm_HashFinish(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.hashResult,
                              &(Cry_EdDSAGenCtx.hashResultLength),
                              FALSE
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_FINISH_HASH_1;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_PRIVK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_SCALARS:
      /* calculate the private scalar */
      Cry_EdDSAPrivateScalar(Cry_EdDSAGenCtx.scalarS,
                             Cry_EdDSAGenCtx.hashResult,
                             (Cry_EdDSAGenCtx.hashResultLength >> 1U)
                            );

      /* start the multiplication */
      Cry_EdDSAPointMultiplicationStart(&Cry_EdDSAGenCtx.EdDSACtx);
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_1;

      break;

    case CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_1:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
            (finished == FALSE) &&
            (
             (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
             (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
            )
           )
      {
        sliceCount++;

        /* A = s * the point B */
        if (Cry_EdDSAPointMultiplication(&Cry_EdDSAGenCtx.EdDSACtx,
                                          &Cry_EdDSAGenCtx.A,
                                          &(Cry_EdDSACurveInfo.P),
                                          Cry_EdDSAGenCtx.scalarS,  /* to control the public key */
                                          Cry_EdDSAGenCtx.tmp
                                         ) == TRUE
            )
         {
           Cry_EdDSAGenCtx.tmp2arrayLength
                   = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

           Cry_EdDSAPointEncodingStart(&Cry_EdDSAGenCtx.EdDSACtx);

           Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_2;

           finished = TRUE;
         }
       }
     break;

   case CRY_EdDSA_G_S_FINISH_PUBLIC_KEY_2:
     finished = FALSE;
     sliceCount = 0U;

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
     while (
            (finished == FALSE) &&
            (
             (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
             (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
            )
           )
     {
       sliceCount++;

       /* converting the A to a byte array and encoding it for the HashUpdate function */
       if (Cry_EdDSAPointEncoding(&Cry_EdDSAGenCtx.EdDSACtx,
                                  &Cry_EdDSAGenCtx.A,
                                  Cry_EdDSAGenCtx.tmp,
                                  Cry_EdDSAGenCtx.tmp2array,  /* result = the public key */
                                  Cry_EdDSAGenCtx.tmp1array,
                                  Cry_EdDSAGenCtx.tmp2arrayLength,
                                  Cry_EdDSAGenCtx.tmp1arrayLength
                                 ) == TRUE
          )
       {
         Cry_EdDSAGenCtx.genState         = CRY_EdDSA_G_S_INITIALIZED;
         Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_INIT_1;

         Csm_SignatureGenerateCallbackNotification(CSM_E_OK);

         finished = TRUE;
       }
     }
     break;

    case CRY_EdDSA_G_S_WAIT_FOR_INIT_1:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_K:
    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_1:
    default:
     {
       break;
     }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAGenHashMsg
(
 void
)
{
  Csm_ReturnType RetVal;

  switch (Cry_EdDSAGenCtx.msgHashState)
  {
    case CRY_EdDSA_G_S_INIT_HASH_MESSAGE:
      Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_WAIT_FOR_INIT_HASH_MESSAGE;
      RetVal = Csm_HashStart(Cry_EdDSAGenCtx.cfgPtr->HashCfg);

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG;
            break;
          }
      }
     break;

    case CRY_EdDSA_G_S_UPDATE_HASH_MESSAGE:
       Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HASH_MESSAGE;
       RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                               Cry_EdDSAGenCtx.message,
                               Cry_EdDSAGenCtx.messageLength
                              );

       switch (RetVal)
       {
         case CSM_E_OK:
           break;

         case CSM_E_BUSY:
           Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_UPDATE_HASH_MESSAGE;
           break;

         default:
           {
             CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG;
             break;
           }
       }
       break;

    case CRY_EdDSA_G_S_FINISH_HASH_MESSAGE:
       Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_MESSAGE;
       Cry_EdDSAGenCtx.hashResultLength = sizeof(Cry_EdDSAGenCtx.hashMessage);
       RetVal = Csm_HashFinish(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                               Cry_EdDSAGenCtx.hashMessage,
                               &(Cry_EdDSAGenCtx.hashResultLength),
                               FALSE
                              );

       switch (RetVal)
       {
         case CSM_E_OK:
           break;

         case CSM_E_BUSY:
           Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_FINISH_HASH_MESSAGE;
           break;

         default:
           {
             CRY_EDDSA_G_HANDLE_FAILING_HASH_MSG;
             break;
           }
       }
       break;

    case CRY_EdDSA_G_S_WAIT_FOR_INIT_HASH_MESSAGE:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HASH_MESSAGE:
    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_MESSAGE:
    default:
       {
         break;
       }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSACalculateLittleR
(
 void
)
{
  Csm_ReturnType RetVal;

  switch (Cry_EdDSAGenCtx.littleRState)
  {
    case CRY_EdDSA_G_S_INIT_2:
     Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_INIT_2;
     RetVal = Csm_HashStart(Cry_EdDSAGenCtx.cfgPtr->HashCfg);

     switch (RetVal)
     {
       case CSM_E_OK:
         break;

       case CSM_E_BUSY:
         Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_INIT_2;
         break;

       default:
         {
           CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR;
           break;
         }
     }
     break;

    case CRY_EdDSA_G_S_UPDATE_DOM2_1:
     Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_1;
      /* Hash the parameter "dom" */
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_1;
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSADOM,
                              CRY_EDDSA_DOM_LEN
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_DOM2_1;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_UPDATE_HB:
       Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HB;
       /* Hash the prefix (h_b to h_(2*b-1)) */
       Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HB;
       RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                               &Cry_EdDSAGenCtx.hashResult
                               [
                                Cry_EdDSAGenCtx.hashResultLength / (uint32)2U
                               ],
                               (Cry_EdDSAGenCtx.hashResultLength / (uint32)2U)
                              );

       switch (RetVal)
       {
         case CSM_E_OK:
           break;

         case CSM_E_BUSY:
           Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_HB;
           break;

         default:
           {
             CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR;
             break;
           }
       }
       break;

    case CRY_EdDSA_G_S_UPDATE_M:
       Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M;
      /* Hash the prehashed message (H(M)) */
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M;
      Cry_EdDSAGenCtx.messageLength = sizeof(Cry_EdDSAGenCtx.hashMessage);
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.hashMessage,
                              Cry_EdDSAGenCtx.messageLength
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_M;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_HASH_2:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_2;
      /* finish the hashing function and receive the hashed value */
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_2;
      RetVal = Csm_HashFinish(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.hashResult,
                              &(Cry_EdDSAGenCtx.hashResultLength),
                              FALSE
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_FINISH_HASH_2;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITR;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_INIT_2:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HB:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_1:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M:
    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_2:
    default:
      {
        break;
      }

  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAGenCalculateLittleK
(
  void
)
{
  Csm_ReturnType RetVal;

  switch (Cry_EdDSAGenCtx.littleKState)
  {
    case CRY_EdDSA_G_S_INIT_3:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_INIT_3;
      Cry_EdDSAGenCtx.tmp3arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

      Cry_EdDSAPointEncodingStart(&Cry_EdDSAGenCtx.EdDSACtx);

      /* initialize the hash interface again for the computation of the S */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_INIT_3;
      RetVal = Csm_HashStart(Cry_EdDSAGenCtx.cfgPtr->HashCfg);

      switch (RetVal)
      {
        case CSM_E_OK:
          Cry_EdDSAGenCtx.tmp3arrayLength = (uint32)((uint32)Cry_EdDSACurveInfo.bValue >> 3U);

          Cry_EdDSAPointEncodingStart(&Cry_EdDSAGenCtx.EdDSACtx);
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_INIT_3;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_UPDATE_DOM2_2:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_2;
      /* Hash the parameter "dom" */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_2;
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSADOM,
                              CRY_EDDSA_DOM_LEN
                             );
      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_DOM2_2;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_UPDATE_R:
      /* converting the R to a byte array and encoding it for the HashUpdate function */
      Cry_EdDSAEncodeAndHashR();
      break;

    case CRY_EdDSA_G_S_UPDATE_A:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_A;
      /* Hash the public key (A) */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_A;
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.tmp2array,
                              Cry_EdDSAGenCtx.tmp2arrayLength
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_A;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_UPDATE_M2:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M2;
      /* Hash the pre-hashed message (PH(M)) */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M2;
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.hashMessage,
                              sizeof(Cry_EdDSAGenCtx.hashMessage)
                             );
      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_M2;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_HASH_3:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_3;
      /* finish the hashing function and receive the hashed value */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_3;
      RetVal = Csm_HashFinish(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.hashResult,
                              &(Cry_EdDSAGenCtx.hashResultLength),
                              FALSE
                             );

      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_FINISH_HASH_3;
          break;

        default:
          {
            CRY_EDDSA_G_HANDLE_FAILING_HASH_LITK;
            break;
          }
      }
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_INIT_3:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_2:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_R:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_A:
    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M2:
    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_3:
    default:
      {
        break;
      }

  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAEncodeAndHashR
(
  void
)
{
  Csm_ReturnType RetVal;
  boolean finished = FALSE;
  uint16 sliceCount = 0U;

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
  while (
         (finished == FALSE) &&
         (
          (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
          (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
         )
        )
  {
    sliceCount++;

    if (Cry_EdDSAPointEncoding(&Cry_EdDSAGenCtx.EdDSACtx,
                               &Cry_EdDSAGenCtx.R,
                               Cry_EdDSAGenCtx.tmp,
                               Cry_EdDSAGenCtx.tmp1array,
                               Cry_EdDSAGenCtx.tmp3array,
                               Cry_EdDSAGenCtx.tmp1arrayLength,
                               Cry_EdDSAGenCtx.tmp3arrayLength
                              ) == TRUE
       )
    {
      finished = TRUE;

      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_R;
      /* Result = ENC(R) */
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_UPDATE_R;
      RetVal = Csm_HashUpdate(Cry_EdDSAGenCtx.cfgPtr->HashCfg,
                              Cry_EdDSAGenCtx.tmp1array,
                              Cry_EdDSAGenCtx.tmp1arrayLength
                             );
      switch (RetVal)
      {
        case CSM_E_OK:
          break;

        case CSM_E_BUSY:
          Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_R;
          break;

        default:
          {
            Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_IDLE;
            Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_WAIT_FOR_INIT_3;

            Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

            Csm_SignatureGenerateServiceFinishNotification();
            break;
          }
      }
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSACalculateScalars
(
  void
)
{
  uint16 sliceCount;
  boolean finished;

  switch (Cry_EdDSAGenCtx.scalarsState)
  {
    case CRY_EdDSA_G_S_FINISH_SCALARR1_INT:
      /* Scalar r */

      /* CHECK: NOPARSE */
      /* This branch is unreachable as we have enough memory allocated in the context
       * to store the byte representation of the LN. */
      if
      (
        Cry_LNLEByteArrayToNumber
        (
          Cry_EdDSAGenCtx.hashResult,
          Cry_EdDSAGenCtx.hashResultLength,
          Cry_EdDSAGenCtx.scalarR,
          sizeof(Cry_EdDSAGenCtx.scalarR) / sizeof(Cry_EdDSAGenCtx.scalarR[0U])
        ) != E_OK
      )
      {
        Cry_EdDSAGenCtx.genState  = CRY_EdDSA_G_S_IDLE;

        Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

        Csm_SignatureGenerateServiceFinishNotification();
      }
      else
      /* CHECK: PARSE */
      {
        /* start the modulo function */
        Cry_LNModuloStart(&Cry_EdDSAGenCtx.LNCtx);
        Cry_EdDSAGenCtx.scalarsState = CRY_EdDSA_G_S_FINISH_SCALARR2;
      }
      break;

    case CRY_EdDSA_G_S_FINISH_SCALARR2:
      finished = FALSE;
      sliceCount = 0U;

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

      /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* r = r % lValue */
        if (Cry_LNModulo(Cry_EdDSAGenCtx.scalarR,
                         Cry_EdDSACurveInfo.lValue,
                         &Cry_EdDSAGenCtx.LNCtx
                        ) == TRUE
           )
        {
          /* start the multiplication */
          Cry_EdDSAPointMultiplicationStart(&Cry_EdDSAGenCtx.EdDSACtx);
          Cry_EdDSAGenCtx.scalarsState = CRY_EdDSA_G_S_FINISH_SCALARR3;

          finished = TRUE;
        }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_SCALARR3:
      finished = FALSE;
      sliceCount = 0U;

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* R = r * the point B */
        if (Cry_EdDSAPointMultiplication(&Cry_EdDSAGenCtx.EdDSACtx,
                                         &Cry_EdDSAGenCtx.R,
                                         &(Cry_EdDSACurveInfo.P),
                                         Cry_EdDSAGenCtx.scalarR,
                                         Cry_EdDSAGenCtx.tmp
                                        ) == TRUE
           )
        {
          Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_LITTLE_K;
          Cry_EdDSAGenCtx.scalarsState = CRY_EdDSA_G_S_FINISH_SCALARR1_INT;

          finished = TRUE;
        }
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        break;
      }
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAFinishSignature
(
  void
)
{
  uint16 sliceCount;
  boolean finished;

  switch (Cry_EdDSAGenCtx.genFinishSig)
  {
    case CRY_EdDSA_G_S_FINISH_S1:
      Cry_EdDSAEncodeSFromHash();
      break;

    case CRY_EdDSA_G_S_FINISH_S2_TEMP:
      finished = FALSE;
      sliceCount = 0U;

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* tmp1 = tmp1 % lValue */
        if (Cry_LNModulo(&Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                         Cry_EdDSACurveInfo.lValue,
                         &Cry_EdDSAGenCtx.LNCtx
                        ) == TRUE
           )
        {
          Cry_LNMultiplyStart(&Cry_EdDSAGenCtx.LNCtx);
          Cry_EdDSAGenCtx.genFinishSig = CRY_EdDSA_G_S_FINISH_S2;

          finished = TRUE;
        }
      }
      break;


    case CRY_EdDSA_G_S_FINISH_S2:
      finished = FALSE;
      sliceCount = 0U;

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* tmp1 = HashResult * Scalar s */
        if (Cry_LNMultiplyNumbers(&Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                                  &Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                                  Cry_EdDSAGenCtx.scalarS,
                                  &Cry_EdDSAGenCtx.LNCtx
                                 ) == TRUE
           )
        {
          Cry_LNModuloStart(&Cry_EdDSAGenCtx.LNCtx);
          Cry_EdDSAGenCtx.genFinishSig = CRY_EdDSA_G_S_FINISH_EXPORT_TEMP;

          finished = TRUE;
        }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_EXPORT_TEMP:
      finished = FALSE;
      sliceCount = 0U;

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue0,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValue1,1 */

     /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlicesValueGreaterThan1,1 */
      while (
             (finished == FALSE) &&
             (
              (Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices == 0U) ||
              (sliceCount < Cry_EdDSAGenCtx.cfgPtr->NumberOfTimeSlices)
             )
            )
      {
        sliceCount++;

        /* tmp1 = tmp1 % lValue */
        if (Cry_LNModulo(&Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                         Cry_EdDSACurveInfo.lValue,
                         &Cry_EdDSAGenCtx.LNCtx
                        ) == TRUE
           )
        {
          /* tmp2 = Scalar r + tmp1 */
          Cry_LNAdditionModular(&Cry_EdDSAGenCtx.tmp[2U * CRY_EdDSA_TEMP_LEN_WORDS],
                                Cry_EdDSAGenCtx.scalarR,
                                &Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                                Cry_EdDSACurveInfo.lValue
                              );
          Cry_EdDSAGenCtx.genFinishSig = CRY_EdDSA_G_S_FINISH_EXPORT;

          finished = TRUE;
        }
      }
      break;

    case CRY_EdDSA_G_S_FINISH_EXPORT:
      Cry_EdDSAExportSign();
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        break;
      }
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrivKeyCallback
(
  void
)
{
  switch (Cry_EdDSAGenCtx.privKeyHashState)
  {
    case CRY_EdDSA_G_S_WAIT_FOR_INIT_1:
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_UPDATE_K;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_K:
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_FINISH_HASH_1;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_1:
      Cry_EdDSAGenCtx.privKeyHashState = CRY_EdDSA_G_S_FINISH_SCALARS;
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

static FUNC(void, CRY_CODE) Cry_EdDSAHashMsgCallback
(
  void
)
{
  switch (Cry_EdDSAGenCtx.msgHashState)
  {
    case CRY_EdDSA_G_S_WAIT_FOR_INIT_HASH_MESSAGE:
      Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_UPDATE_HASH_MESSAGE;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HASH_MESSAGE:
      /* Wait for another Update call. */
      Cry_EdDSAGenCtx.genState = CRY_EdDSA_G_S_INITIALIZED;
      Csm_SignatureGenerateCallbackNotification(CSM_E_OK);
      break;


    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_MESSAGE:
      Cry_EdDSAGenCtx.msgHashState = CRY_EdDSA_G_S_INIT_HASH_MESSAGE;
      Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_LITTLE_R;
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

static FUNC(void, CRY_CODE) Cry_EdDSALittleRCallback
(
  void
)
{
  switch (Cry_EdDSAGenCtx.littleRState)
  {
    case CRY_EdDSA_G_S_WAIT_FOR_INIT_2:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_DOM2_1;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_1:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_HB;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_HB:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_UPDATE_M;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_FINISH_HASH_2;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_2:
      Cry_EdDSAGenCtx.littleRState = CRY_EdDSA_G_S_INIT_2;
      Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_FINISH_SCALARR1;
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

static FUNC(void, CRY_CODE) Cry_EdDSAExportSign
(
  void
)
{
  uint32 Temp;
  uint32 i;

  /* ENC(R): tmp1array - Little endian byte Array */
  Temp = *Cry_EdDSAGenCtx.resultLength;

  for (i = 0U; i < Cry_EdDSAGenCtx.tmp1arrayLength; i++)
  {
    Cry_EdDSAGenCtx.result[i] = Cry_EdDSAGenCtx.tmp1array[i];
  }

  Temp -= *Cry_EdDSAGenCtx.resultLength >> 1U;

  /* S: tmp2 in little endian byte array */

  (void)Cry_LNNumberToLEByteArray(&Cry_EdDSAGenCtx.tmp[2U * CRY_EdDSA_TEMP_LEN_WORDS],
                                  &Cry_EdDSAGenCtx.result[Temp],
                                  &Temp
                                 );

  Csm_SignatureGenerateCallbackNotification(CSM_E_OK);
  Csm_SignatureGenerateServiceFinishNotification();

  Cry_EdDSAGenCtx.genFinishSig = CRY_EdDSA_G_S_FINISH_S1;
  Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_IDLE;
}

static FUNC(void, CRY_CODE) Cry_EdDSAEncodeSFromHash
(
  void
)
{
  /* CHECK: NOPARSE */
  /* This branch is unreachable as we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  if (Cry_LNLEByteArrayToNumber(Cry_EdDSAGenCtx.hashResult,
                                Cry_EdDSAGenCtx.hashResultLength,
                                &Cry_EdDSAGenCtx.tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                                CRY_EdDSA_TEMP_LEN_WORDS
                               ) != E_OK
     )
  {
    Cry_EdDSAGenCtx.genState  = CRY_EdDSA_G_S_IDLE;
    Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);
    Csm_SignatureGenerateServiceFinishNotification();
  }
  else
  /* CHECK: PARSE */
  {
    Cry_LNModuloStart(&Cry_EdDSAGenCtx.LNCtx);
    Cry_EdDSAGenCtx.genFinishSig = CRY_EdDSA_G_S_FINISH_S2_TEMP;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSALittleKCallback
(
    void
)
{
  switch (Cry_EdDSAGenCtx.littleKState)
  {
    case CRY_EdDSA_G_S_WAIT_FOR_INIT_3:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_DOM2_2;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_DOM2_2:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_R;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_R:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_A;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_A:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_UPDATE_M2;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_UPDATE_M2:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_FINISH_HASH_3;
      break;

    case CRY_EdDSA_G_S_WAIT_FOR_FINISH_HASH_3:
      Cry_EdDSAGenCtx.littleKState = CRY_EdDSA_G_S_INIT_3;
      Cry_EdDSAGenCtx.genState     = CRY_EdDSA_G_S_FINISH_SIG;
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

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* (CRY_EDDSA_GEN_ENABLED == STD_ON) */

/** \brief Dummy definition preventing this file from being empty */
typedef void Cry_EdSAGen_EmptyTranslationUnitType;

#endif /* #if (CRY_EDDSA_GEN_ENABLED == STD_ON) */
