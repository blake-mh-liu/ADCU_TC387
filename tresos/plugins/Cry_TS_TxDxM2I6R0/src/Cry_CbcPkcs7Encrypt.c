/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Cry_Common.h>
#include <Cry_CbcPkcs7Encrypt.h>  /* !LINKSTO EB_CRY_0005,1 */
#include <Csm_SymEncrypt.h>

#if (CRY_CBC_PKCS7_ENC_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (defined CRY_CBC_PKCS7_ENCRYPT_BLOCK_LEN)
#error CRY_CBC_PKCS7_ENCRYPT_BLOCK_LEN is already defined
#endif
#define CRY_CBC_PKCS7_ENCRYPT_BLOCK_LEN 16U

/*==[Types]===================================================================*/

/** \brief  AES algorithm implementation state machine states.
 **/
typedef enum
{
  CRY_CBC_PKCS7_ENC_S_UNINIT,
  CRY_CBC_PKCS7_ENC_S_REQ_SB_ST,
  CRY_CBC_PKCS7_ENC_S_WAIT_SB_ST,
  CRY_CBC_PKCS7_ENC_S_INITIALIZED,
  CRY_CBC_PKCS7_ENC_S_CP_FROM_INP,
  CRY_CBC_PKCS7_ENC_S_REQ_SB_UPD,
  CRY_CBC_PKCS7_ENC_S_WAIT_SB_UPD,
  CRY_CBC_PKCS7_ENC_S_CP_TO_OUTP,
  CRY_CBC_PKCS7_ENC_S_PAD_LAST_BL,
  CRY_CBC_PKCS7_ENC_S_F_REQ_SB_UPD,
  CRY_CBC_PKCS7_ENC_S_F_WAIT_SB_UPD,
  CRY_CBC_PKCS7_ENC_S_CP_PAD,
  CRY_CBC_PKCS7_ENC_S_REQ_SB_FIN,
  CRY_CBC_PKCS7_ENC_S_WAIT_SB_FIN
}
Cry_CbcPkcs7EncryptStateType;

/* !LINKSTO EB_CRY_0022,1 */

typedef struct
{
          uint32                                    iputTextLength;
          uint32                                    oputTextLength;
          uint32                                    blockFilled;
  P2CONST(Csm_SymKeyType, TYPEDEF, CRY_APPL_DATA)   keyPtr;
    P2VAR(uint32,         TYPEDEF, CRY_APPL_DATA)   oputTextLengthPtr;
  P2CONST(uint8,          TYPEDEF, CRY_APPL_DATA)   iputTextPtr;
    P2VAR(uint8,          TYPEDEF, CRY_APPL_DATA)   oputTextPtr;
          Cry_CbcPkcs7EncryptStateType              ctxState;
          Csm_ConfigIdType                          cfgId;
          uint8                                     block[CRY_CBC_PKCS7_ENCRYPT_BLOCK_LEN];
          uint8                                     lastCipherText[CRY_CBC_PKCS7_ENCRYPT_BLOCK_LEN];

}
Cry_CbcPkcs7EncryptContextType;


/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief State: Request start of symmetrical block encryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbSt
(
  void
);

/**
 *
 * \brief State: Copy input data for processing
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpFromInp
(
  void
);

/**
 *
 * \brief State: Request update of symmetrical block encryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbUpd
(
  void
);

/**
 *
 * \brief State: Copy result data to output
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpToOutp
(
  void
);

/**
 *
 * \brief State: Pad the last block for encryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) CRY_CBCPkcs7EncStatePadLastBl
(
  void
);

/**
 *
 * \brief State: Request update of symmetrical block encryption for the last block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateFReqSbUpd
(
  void
);

/**
 *
 * \brief State: Copy input data for processing
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpPad
(
  void
);

/**
 *
 * \brief State: Request finish of symmetrical block encryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbFin
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_CbcPkcs7EncryptContextType, CRY_VAR) Cry_CbcPkcs7EncryptContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0075,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7EncryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr,
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) initVectorPtr,
          uint32                                    initVectorLength
)
{
  P2CONST(Cry_CbcPkcs7EncryptConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
          Csm_ReturnType                                           locRetVal;


  locCfgPtr = (P2CONST(Cry_CbcPkcs7EncryptConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;

  locRetVal = CSM_E_NOT_OK;

  if(initVectorLength == sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText))
  {

    locRetVal = CSM_E_OK;

    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_ST;


    Cry_CbcPkcs7EncryptContext.cfgId = locCfgPtr->symBlockEncryptCfgId;

    Cry_CbcPkcs7EncryptContext.keyPtr = keyPtr;

    Cry_CbcPkcs7EncryptContext.blockFilled = 0;

    Cry_CbcPkcs7EncryptContext.oputTextLength = 0;

    Cry_CommonCopy
    (
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      initVectorPtr,
      initVectorLength
    );
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0076,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7EncryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                            iputTextLength,
    P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if      ( Cry_CbcPkcs7EncryptContext.ctxState == CRY_CBC_PKCS7_ENC_S_UNINIT )
  {
    /* Reset the underlying AES primitive */
    (void) Csm_SymBlockEncryptFinish(Cry_CbcPkcs7EncryptContext.cfgId);
    Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CbcPkcs7EncryptContext.ctxState == CRY_CBC_PKCS7_ENC_S_INITIALIZED   )
  {
    /* context state administration */
    Cry_CbcPkcs7EncryptContext.ctxState   =  CRY_CBC_PKCS7_ENC_S_CP_FROM_INP;

    Cry_CbcPkcs7EncryptContext.oputTextLength = 0;

    /* copy input arguments into context variables */
    Cry_CbcPkcs7EncryptContext.iputTextPtr       = iputTextPtr;
    Cry_CbcPkcs7EncryptContext.iputTextLength    = iputTextLength;
    Cry_CbcPkcs7EncryptContext.oputTextPtr       = oputTextPtr;
    Cry_CbcPkcs7EncryptContext.oputTextLengthPtr = oputTextLengthPtr;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0077,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7EncryptFinish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if      ( Cry_CbcPkcs7EncryptContext.ctxState == CRY_CBC_PKCS7_ENC_S_UNINIT )
  {
    /* Reset the underlying AES primitive */
    (void) Csm_SymBlockEncryptFinish(Cry_CbcPkcs7EncryptContext.cfgId);
    Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CbcPkcs7EncryptContext.ctxState == CRY_CBC_PKCS7_ENC_S_INITIALIZED    )
  {
    /* context state administration */
    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_PAD_LAST_BL;

    Cry_CbcPkcs7EncryptContext.oputTextLength = 0;

    Cry_CbcPkcs7EncryptContext.oputTextPtr       = oputTextPtr;
    Cry_CbcPkcs7EncryptContext.oputTextLengthPtr = oputTextLengthPtr;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}


/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0078,1 */
FUNC(void,CRY_CODE) Cry_CbcPkcs7EncryptMainFunction
(
  void
)
{
  switch ( Cry_CbcPkcs7EncryptContext.ctxState )
  {
    case CRY_CBC_PKCS7_ENC_S_UNINIT:
    break;

    case CRY_CBC_PKCS7_ENC_S_REQ_SB_ST:
    {
      Cry_CBCPkcs7EncStateReqSbSt();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_INITIALIZED:
    break;

    case CRY_CBC_PKCS7_ENC_S_CP_FROM_INP:
    {
      Cry_CBCPkcs7EncStateCpFromInp();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_REQ_SB_UPD:
    {
      Cry_CBCPkcs7EncStateReqSbUpd();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_CP_TO_OUTP:
    {
      Cry_CBCPkcs7EncStateCpToOutp();
    }
    break;

    /* *** Cry_CbcPkcs7EncryptMainFunction > CRY_CBC_PKCS7_ENC_S_PAD_LAST_BL ******************** */
    case CRY_CBC_PKCS7_ENC_S_PAD_LAST_BL:
    {
      CRY_CBCPkcs7EncStatePadLastBl();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_F_REQ_SB_UPD:
    {
      Cry_CBCPkcs7EncStateFReqSbUpd();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_CP_PAD:
    {
      Cry_CBCPkcs7EncStateCpPad();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_REQ_SB_FIN:
    {
      Cry_CBCPkcs7EncStateReqSbFin();
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_ST:
    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_UPD:
    case CRY_CBC_PKCS7_ENC_S_F_WAIT_SB_UPD:
    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_FIN:
    {
    }
    break;


    /* *** Cry_CbcPkcs7EncryptMainFunction > DEFAULT *************************************** */
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;
    }
    break;
    /* CHECK: PARSE */
  }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_CbcPkcs7EncryptCallback
(
   Csm_ReturnType Result
)
{
  switch(Cry_CbcPkcs7EncryptContext.ctxState)
  {
    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_ST:
    {
      if(CSM_E_OK == Result)
      {
        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_INITIALIZED;
        Csm_SymEncryptCallbackNotification(CSM_E_OK);

      }
      else
      {
        Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_UPD:
    {
      if(CSM_E_OK == Result)
      {
        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_CP_TO_OUTP;
      }
      else
      {
        Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_F_WAIT_SB_UPD:
    {
      if(CSM_E_OK == Result)
      {
        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_CP_PAD;
      }
      else
      {
        Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

        Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

        Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymEncryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_PKCS7_ENC_S_WAIT_SB_FIN:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

      Csm_SymEncryptCallbackNotification(Result);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;

    default:
    {
      break;
    }
  }

  return E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbSt
(
  void
)
{
  Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_WAIT_SB_ST;

  switch
  (
    Csm_SymBlockEncryptStart
    (
      Cry_CbcPkcs7EncryptContext.cfgId,
      Cry_CbcPkcs7EncryptContext.keyPtr
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_ST;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpFromInp
(
  void
)
{
  if
  (
    (Cry_CbcPkcs7EncryptContext.blockFilled + Cry_CbcPkcs7EncryptContext.iputTextLength) >=
    sizeof(Cry_CbcPkcs7EncryptContext.block)
  )
  {
    uint8 newLen;


    newLen =
      (uint8)
      (sizeof(Cry_CbcPkcs7EncryptContext.block) - Cry_CbcPkcs7EncryptContext.blockFilled);

    Cry_CommonCopy
    (
      &Cry_CbcPkcs7EncryptContext.block[Cry_CbcPkcs7EncryptContext.blockFilled],
      Cry_CbcPkcs7EncryptContext.iputTextPtr,
      newLen
    );

    Cry_CbcPkcs7EncryptContext.iputTextPtr = &Cry_CbcPkcs7EncryptContext.iputTextPtr[newLen];

    Cry_CbcPkcs7EncryptContext.iputTextLength -= newLen;

    Cry_CbcPkcs7EncryptContext.blockFilled = sizeof(Cry_CbcPkcs7EncryptContext.block);

    Cry_CommonXOR
    (
      Cry_CbcPkcs7EncryptContext.block,
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      sizeof(Cry_CbcPkcs7EncryptContext.block)
    );

    /* context state administration */
    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_UPD;
  }
  else
  {
    Cry_CommonCopy
    (
      &Cry_CbcPkcs7EncryptContext.block[Cry_CbcPkcs7EncryptContext.blockFilled],
      Cry_CbcPkcs7EncryptContext.iputTextPtr,
      Cry_CbcPkcs7EncryptContext.iputTextLength
    );

    Cry_CbcPkcs7EncryptContext.blockFilled += Cry_CbcPkcs7EncryptContext.iputTextLength;

    *Cry_CbcPkcs7EncryptContext.oputTextLengthPtr = Cry_CbcPkcs7EncryptContext.oputTextLength;

    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_INITIALIZED;

    Csm_SymEncryptCallbackNotification(CSM_E_OK);
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbUpd
(
  void
)
{
  Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_WAIT_SB_UPD;

  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      Cry_CbcPkcs7EncryptContext.cfgId,
      Cry_CbcPkcs7EncryptContext.block,
      sizeof(Cry_CbcPkcs7EncryptContext.block),
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      &(Cry_CbcPkcs7EncryptContext.blockFilled)
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_UPD;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpToOutp
(
  void
)
{
  if
  (
    (*Cry_CbcPkcs7EncryptContext.oputTextLengthPtr - Cry_CbcPkcs7EncryptContext.oputTextLength)
    >=
    sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText)
  )
  {
    Cry_CommonCopy
    (
      Cry_CbcPkcs7EncryptContext.oputTextPtr,
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText)
    );

    Cry_CbcPkcs7EncryptContext.oputTextLength +=
      sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText);

    Cry_CbcPkcs7EncryptContext.oputTextPtr =
      &Cry_CbcPkcs7EncryptContext.oputTextPtr[sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText)];

    Cry_CbcPkcs7EncryptContext.blockFilled = 0;

    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_CP_FROM_INP;
  }
  else
  {
    Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));


    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

    /* !LINKSTO CSM0665,1 */
    Csm_SymEncryptCallbackNotification(CSM_E_SMALL_BUFFER);

    Csm_SymEncryptServiceFinishNotification();
  }
}

static FUNC(void, CRY_CODE) CRY_CBCPkcs7EncStatePadLastBl
(
  void
)
{
  uint32 i;

  for
  (
    i = 0;
    i < (sizeof(Cry_CbcPkcs7EncryptContext.block) - Cry_CbcPkcs7EncryptContext.blockFilled);
    i++
  )
  {
    Cry_CbcPkcs7EncryptContext.block[Cry_CbcPkcs7EncryptContext.blockFilled + i] =
      (uint8)
      (sizeof(Cry_CbcPkcs7EncryptContext.block) - Cry_CbcPkcs7EncryptContext.blockFilled);
  }

  Cry_CbcPkcs7EncryptContext.blockFilled = sizeof(Cry_CbcPkcs7EncryptContext.block);

  Cry_CommonXOR
  (
    Cry_CbcPkcs7EncryptContext.block,
    Cry_CbcPkcs7EncryptContext.lastCipherText,
    sizeof(Cry_CbcPkcs7EncryptContext.block)
  );

  Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_F_REQ_SB_UPD;
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateFReqSbUpd
(
  void
)
{
  Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_F_WAIT_SB_UPD;

  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      Cry_CbcPkcs7EncryptContext.cfgId,
      Cry_CbcPkcs7EncryptContext.block,
      sizeof(Cry_CbcPkcs7EncryptContext.block),
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      &(Cry_CbcPkcs7EncryptContext.blockFilled)
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_F_REQ_SB_UPD;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateCpPad
(
  void
)
{
  if
  (
    *Cry_CbcPkcs7EncryptContext.oputTextLengthPtr >=
    sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText)
  )
  {
    Cry_CommonCopy
    (
      Cry_CbcPkcs7EncryptContext.oputTextPtr,
      Cry_CbcPkcs7EncryptContext.lastCipherText,
      sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText)
    );

    *Cry_CbcPkcs7EncryptContext.oputTextLengthPtr =
        sizeof(Cry_CbcPkcs7EncryptContext.lastCipherText);

    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_FIN;
  }
  else
  {
    Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

    Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;

    /* !LINKSTO CSM0666,1 */
    Csm_SymEncryptCallbackNotification(CSM_E_SMALL_BUFFER);

    Csm_SymEncryptServiceFinishNotification();
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7EncStateReqSbFin
(
  void
)
{
  Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_WAIT_SB_FIN;

  switch ( Csm_SymBlockEncryptFinish(Cry_CbcPkcs7EncryptContext.cfgId) )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_REQ_SB_FIN;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7EncryptContext, sizeof(Cry_CbcPkcs7EncryptContext));

      Cry_CbcPkcs7EncryptContext.ctxState = CRY_CBC_PKCS7_ENC_S_UNINIT;
      Csm_SymEncryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymEncryptServiceFinishNotification();
    }
    break;
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*----------------------------------------------------------------------------*/

#else /* #if (CRY_CBC_PKCS7_ENC_ENABLED == STD_ON) */

typedef uint8 Cry_CbcPkcs7Encrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CBC_PKCS7_ENC_ENABLED == STD_ON) */
