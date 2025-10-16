/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Cry_CbcPkcs7Decrypt.h>  /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>
#include <Csm_SymDecrypt.h>

#if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (defined CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN)
#error CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN is already defined
#endif
#define CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN 16U

/*==[Types]===================================================================*/

/** \brief  AES algorithm implementation state machine states.
 **/
typedef enum
{
  CRY_CBC_PKCS7_DEC_S_UNINIT,
  CRY_CBC_PKCS7_DEC_S_REQ_SB_ST,
  CRY_CBC_PKCS7_DEC_S_WAIT_SB_ST,
  CRY_CBC_PKCS7_DEC_S_INITIALIZED,
  CRY_CBC_PKCS7_DEC_S_READ_WRITE,
  CRY_CBC_PKCS7_DEC_S_REQ_SB_UPD,
  CRY_CBC_PKCS7_DEC_S_WAIT_SB_UPD,
  CRY_CBC_PKCS7_DEC_S_XOR,
  CRY_CBC_PKCS7_DEC_S_REQ_SB_FIN,
  CRY_CBC_PKCS7_DEC_S_WAIT_SB_FIN,
  CRY_CBC_PKCS7_DEC_S_CP_LAST_BL
}
Cry_CbcPkcs7DecryptStateType;

/* !LINKSTO EB_CRY_0022,1 */

typedef struct
{
          uint32                                   iputTextLength;
          uint32                                   oputTextLength;
          uint32                                   blockFilled;
  P2CONST(Csm_SymKeyType, TYPEDEF, CRY_APPL_DATA)  keyPtr;
    P2VAR(uint32,         TYPEDEF, CRY_APPL_DATA)  oputTextLengthPtr;
  P2CONST(uint8,          TYPEDEF, CRY_APPL_DATA)  iputTextPtr;
    P2VAR(uint8,          TYPEDEF, CRY_APPL_DATA)  oputTextPtr;
          uint8                                    block[CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN];
          uint8                                    lastCipherText[CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN];
          uint8                                    plainText[CRY_CBC_PKCS7_DECRYPT_BLOCK_LEN];
          Cry_CbcPkcs7DecryptStateType             ctxState;
          Csm_ConfigIdType                         cfgId;
          boolean                                  blockToWrite;

}
Cry_CbcPkcs7DecryptContextType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief State: Request start of symmetrical block decryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbSt
(
  void
);

/**
 *
 * \brief State: Write decrypted data to output
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReadWrite
(
  void
);

/**
 *
 * \brief State: Request update of symmetrical block decryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbUpd
(
  void
);

/**
 *
 * \brief State: XOR of a block of data
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateXOR
(
  void
);

/*
 *
 * \brief State: Write decrypted for last data block to output
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateCpLastBl
(
  void
);

/**
 *
 * \brief State: Request finish of symmetrical block decryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbFin
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
static VAR(Cry_CbcPkcs7DecryptContextType, CRY_VAR) Cry_CbcPkcs7DecryptContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0071,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7DecryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr,
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) initVectorPtr,
          uint32                                    initVectorLength
)
{
  P2CONST(Cry_CbcPkcs7DecryptConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
          Csm_ReturnType                                           locRetVal;


  locCfgPtr = (P2CONST(Cry_CbcPkcs7DecryptConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;

  locRetVal = CSM_E_NOT_OK;

  if(initVectorLength == sizeof(Cry_CbcPkcs7DecryptContext.lastCipherText))
  {
    locRetVal = CSM_E_OK;
    Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_ST;


    Cry_CbcPkcs7DecryptContext.cfgId = locCfgPtr->symBlockDecryptCfgId;

    Cry_CbcPkcs7DecryptContext.keyPtr = keyPtr;

    Cry_CbcPkcs7DecryptContext.blockFilled = 0;

    Cry_CbcPkcs7DecryptContext.oputTextLength = 0;

    Cry_CbcPkcs7DecryptContext.blockToWrite = FALSE;

    Cry_CommonCopy
    (
      Cry_CbcPkcs7DecryptContext.lastCipherText,
      initVectorPtr,
      initVectorLength
    );
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0072,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7DecryptUpdate
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

  if      ( Cry_CbcPkcs7DecryptContext.ctxState == CRY_CBC_PKCS7_DEC_S_UNINIT )
  {
    /* Reset the underlying AES primitive */
    (void) Csm_SymBlockDecryptFinish(Cry_CbcPkcs7DecryptContext.cfgId);
    Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CbcPkcs7DecryptContext.ctxState == CRY_CBC_PKCS7_DEC_S_INITIALIZED   )
  {
    /* context state administration */
    Cry_CbcPkcs7DecryptContext.ctxState   =  CRY_CBC_PKCS7_DEC_S_READ_WRITE;

    Cry_CbcPkcs7DecryptContext.oputTextLength = 0;

    /* copy input arguments into context variables */
    Cry_CbcPkcs7DecryptContext.iputTextPtr       = iputTextPtr;
    Cry_CbcPkcs7DecryptContext.iputTextLength    = iputTextLength;
    Cry_CbcPkcs7DecryptContext.oputTextPtr       = oputTextPtr;
    Cry_CbcPkcs7DecryptContext.oputTextLengthPtr = oputTextLengthPtr;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0073,1 */
FUNC(Csm_ReturnType,CRY_CODE) Cry_CbcPkcs7DecryptFinish
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

  if      ( Cry_CbcPkcs7DecryptContext.ctxState == CRY_CBC_PKCS7_DEC_S_UNINIT )
  {
    /* Reset the underlying AES primitive */
    (void) Csm_SymBlockDecryptFinish(Cry_CbcPkcs7DecryptContext.cfgId);
    Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_CbcPkcs7DecryptContext.ctxState == CRY_CBC_PKCS7_DEC_S_INITIALIZED    )
  {
    /* context state administration */
    Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_FIN;

    Cry_CbcPkcs7DecryptContext.oputTextLength = 0;

    Cry_CbcPkcs7DecryptContext.oputTextPtr       = oputTextPtr;
    Cry_CbcPkcs7DecryptContext.oputTextLengthPtr = oputTextLengthPtr;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0074,1 */
FUNC(void,CRY_CODE) Cry_CbcPkcs7DecryptMainFunction
(
  void
)
{
  switch ( Cry_CbcPkcs7DecryptContext.ctxState )
  {
    case CRY_CBC_PKCS7_DEC_S_UNINIT:
    break;

    case CRY_CBC_PKCS7_DEC_S_REQ_SB_ST:
    {
      Cry_CBCPkcs7DecStateReqSbSt();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_INITIALIZED:
    break;

    case CRY_CBC_PKCS7_DEC_S_READ_WRITE:
    {
      Cry_CBCPkcs7DecStateReadWrite();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_REQ_SB_UPD:
    {
      Cry_CBCPkcs7DecStateReqSbUpd();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_XOR:
    {
      Cry_CBCPkcs7DecStateXOR();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_REQ_SB_FIN:
    {
      Cry_CBCPkcs7DecStateReqSbFin();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_CP_LAST_BL:
    {
      Cry_CBCPkcs7DecStateCpLastBl();
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_ST:
    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_UPD:
    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_FIN:
    {
    }
    break;


    /* *** Cry_CbcPkcs7DecryptMainFunction > DEFAULT ****************************************** */
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
    {
      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;
    }
    break;
    /* CHECK: PARSE */
  }
}


FUNC(Std_ReturnType, CRY_CODE) Cry_CbcPkcs7DecryptCallback
(
   Csm_ReturnType Result
)
{
  switch(Cry_CbcPkcs7DecryptContext.ctxState)
  {
    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_ST:
    {
      if(CSM_E_OK == Result)
      {
        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_INITIALIZED;
        Csm_SymDecryptCallbackNotification(CSM_E_OK);
      }
      else
      {
        Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_UPD:
    {
      if(CSM_E_OK == Result)
      {
        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_XOR;
      }
      else
      {
        Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;

        Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
        Csm_SymDecryptServiceFinishNotification();
      }
    }
    break;

    case CRY_CBC_PKCS7_DEC_S_WAIT_SB_FIN:
    {
      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_CP_LAST_BL;
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

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbSt
(
  void
)
{
  Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_WAIT_SB_ST;

  switch
  (
    Csm_SymBlockDecryptStart
    (
      Cry_CbcPkcs7DecryptContext.cfgId,
      Cry_CbcPkcs7DecryptContext.keyPtr
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_ST;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;
      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReadWrite
(
  void
)
{
  if ( Cry_CbcPkcs7DecryptContext.iputTextLength == 0 )
  {
    *Cry_CbcPkcs7DecryptContext.oputTextLengthPtr = Cry_CbcPkcs7DecryptContext.oputTextLength;

    Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_INITIALIZED;

    Csm_SymDecryptCallbackNotification(CSM_E_OK);
  }
  else
  {
    Csm_ReturnType writeResult;


    writeResult = CSM_E_OK;

    if(TRUE == Cry_CbcPkcs7DecryptContext.blockToWrite)
    {
      if
      (
        (
          *Cry_CbcPkcs7DecryptContext.oputTextLengthPtr -
          Cry_CbcPkcs7DecryptContext.oputTextLength
        ) >=
        sizeof(Cry_CbcPkcs7DecryptContext.lastCipherText)
      )
      {
        Cry_CommonCopy
        (
          &Cry_CbcPkcs7DecryptContext.oputTextPtr[Cry_CbcPkcs7DecryptContext.oputTextLength],
          Cry_CbcPkcs7DecryptContext.plainText,
          sizeof(Cry_CbcPkcs7DecryptContext.plainText)
        );

        Cry_CbcPkcs7DecryptContext.oputTextLength +=
          sizeof(Cry_CbcPkcs7DecryptContext.lastCipherText);

        Cry_CbcPkcs7DecryptContext.blockFilled = 0;

        Cry_CbcPkcs7DecryptContext.blockToWrite = FALSE;
      }
      else
      {
        /* !LINKSTO CSM0667,1, CSM0668,1 */
        writeResult = CSM_E_SMALL_BUFFER;
      }
    }

    if(CSM_E_OK != writeResult)
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;

      Csm_SymDecryptCallbackNotification(writeResult);

      Csm_SymDecryptServiceFinishNotification();
    }
    else
    {
      if
      (
        (Cry_CbcPkcs7DecryptContext.blockFilled + Cry_CbcPkcs7DecryptContext.iputTextLength) >=
        sizeof(Cry_CbcPkcs7DecryptContext.block)
      )
      {
        uint32 newLen;


        newLen =
            (sizeof(Cry_CbcPkcs7DecryptContext.block) - Cry_CbcPkcs7DecryptContext.blockFilled);

        Cry_CommonCopy
        (
          &Cry_CbcPkcs7DecryptContext.block[Cry_CbcPkcs7DecryptContext.blockFilled],
          Cry_CbcPkcs7DecryptContext.iputTextPtr,
          newLen
        );

        Cry_CbcPkcs7DecryptContext.iputTextPtr =
            &Cry_CbcPkcs7DecryptContext.iputTextPtr[newLen];

        Cry_CbcPkcs7DecryptContext.iputTextLength -= newLen;

        Cry_CbcPkcs7DecryptContext.blockFilled = sizeof(Cry_CbcPkcs7DecryptContext.block);

        /* context state administration */
        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_UPD;
      }
      else
      {
        Cry_CommonCopy
        (
          &Cry_CbcPkcs7DecryptContext.block[Cry_CbcPkcs7DecryptContext.blockFilled],
          Cry_CbcPkcs7DecryptContext.iputTextPtr,
          Cry_CbcPkcs7DecryptContext.iputTextLength
        );

        Cry_CbcPkcs7DecryptContext.blockFilled += Cry_CbcPkcs7DecryptContext.iputTextLength;

        *Cry_CbcPkcs7DecryptContext.oputTextLengthPtr =
            Cry_CbcPkcs7DecryptContext.oputTextLength;

        Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_INITIALIZED;

        Csm_SymDecryptCallbackNotification(CSM_E_OK);
      }
    }
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbUpd
(
  void
)
{
  Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_WAIT_SB_UPD;

  switch
  (
    Csm_SymBlockDecryptUpdate
    (
      Cry_CbcPkcs7DecryptContext.cfgId,
      Cry_CbcPkcs7DecryptContext.block,
      sizeof(Cry_CbcPkcs7DecryptContext.block),
      Cry_CbcPkcs7DecryptContext.plainText,
      &(Cry_CbcPkcs7DecryptContext.blockFilled)
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_UPD;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;
      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateXOR
(
  void
)
{
  Cry_CbcPkcs7DecryptContext.blockFilled = 0;

  Cry_CommonXOR
  (
    Cry_CbcPkcs7DecryptContext.plainText,
    Cry_CbcPkcs7DecryptContext.lastCipherText,
    sizeof(Cry_CbcPkcs7DecryptContext.plainText)
  );

  Cry_CommonCopy
  (
    Cry_CbcPkcs7DecryptContext.lastCipherText,
    Cry_CbcPkcs7DecryptContext.block,
    sizeof(Cry_CbcPkcs7DecryptContext.block)
  );

  Cry_CbcPkcs7DecryptContext.blockToWrite = TRUE;

  Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_READ_WRITE;
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateCpLastBl
(
  void
)
{
  uint8 padding;
  uint8 lastPlainTextLength;

  padding =
    Cry_CbcPkcs7DecryptContext.plainText[sizeof(Cry_CbcPkcs7DecryptContext.plainText) - 1U];

  lastPlainTextLength = (uint8) (sizeof(Cry_CbcPkcs7DecryptContext.plainText) - padding);

  if
  (
    (Cry_CbcPkcs7DecryptContext.blockFilled != 0) ||
    (padding > sizeof(Cry_CbcPkcs7DecryptContext.plainText)) ||
    (*Cry_CbcPkcs7DecryptContext.oputTextLengthPtr < lastPlainTextLength)
  )
  {
    Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

    Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;

    Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);

    Csm_SymDecryptServiceFinishNotification();
  }
  else
  {
    Cry_CommonCopy
    (
      Cry_CbcPkcs7DecryptContext.oputTextPtr,
      Cry_CbcPkcs7DecryptContext.plainText,
      lastPlainTextLength
    );

    *Cry_CbcPkcs7DecryptContext.oputTextLengthPtr = lastPlainTextLength;

    Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;

    Csm_SymDecryptCallbackNotification(CSM_E_OK);
    Csm_SymDecryptServiceFinishNotification();
  }
}

static FUNC(void, CRY_CODE) Cry_CBCPkcs7DecStateReqSbFin
(
  void
)
{
  Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_WAIT_SB_FIN;

  switch ( Csm_SymBlockDecryptFinish(Cry_CbcPkcs7DecryptContext.cfgId) )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_REQ_SB_FIN;
    }
    break;

    default:
    {
      Cry_CommonResetCtx(&Cry_CbcPkcs7DecryptContext, sizeof(Cry_CbcPkcs7DecryptContext));

      Cry_CbcPkcs7DecryptContext.ctxState = CRY_CBC_PKCS7_DEC_S_UNINIT;
      Csm_SymDecryptCallbackNotification(CSM_E_NOT_OK);
      Csm_SymDecryptServiceFinishNotification();
    }
    break;
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON) */

typedef uint8 Cry_CbcPkcs7Decrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON) */
