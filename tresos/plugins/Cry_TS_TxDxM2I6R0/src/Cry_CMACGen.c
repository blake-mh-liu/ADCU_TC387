/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1, CSM0692,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>
#include <Cry_CMAC.h>
#include <Cry_CMACGen.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_CMACGenConfig.h>
#include <Cry_Common.h>

#if (CRY_CMAC_GEN_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_CMACGenStateType
 * \brief Enumeration of the internal states of the CMAC generation.
 *
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_IDLE
 * \brief Idle state of the CMAC routine.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_START_REQ_SB_START
 * \brief The underlying symmetrical block encryption a gets initialized.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_START_WAIT_SB_START
 * \brief Waiting for the encryption to finish starting.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_START_REQ_SB_UPD
 * \brief Request encryption of zero block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_START_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the zero block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_START_K1_AND_K2
 * \brief Create K1 and K2 and finish the starting of the CMAC.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_UPD_CP_FROM_INPUT
 * \brief Copy bytes from input data to encryption block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_UPD_REQ_SB_UPD
 * \brief Request encryption of data block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_UPD_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the data block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK
 * \brief Pad last block if necessary and XOR it with K1 or K2.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_REQ_SB_UPD
 * \brief Request encryption of last block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the last block.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_CP_TO_RESULT
 * \brief Copy the CMAC to the output buffer.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_REQ_SB_FIN
 * \brief Request finish of encryption.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_FIN_WAIT_SB_FIN
 * \brief Waiting for the encryption to finish.
 *//**
 * \var Cry_CMACGenStateType::CRY_CMAC_G_S_INITIALIZED
 * \brief the CMAC routine is initialized.
 */
typedef enum
{
  CRY_CMAC_G_S_IDLE,
  CRY_CMAC_G_S_START_REQ_SB_START,
  CRY_CMAC_G_S_START_WAIT_SB_START,
  CRY_CMAC_G_S_START_REQ_SB_UPD,
  CRY_CMAC_G_S_START_WAIT_SB_UPD,
  CRY_CMAC_G_S_START_K1_AND_K2,
  CRY_CMAC_G_S_UPD_CP_FROM_INPUT,
  CRY_CMAC_G_S_UPD_REQ_SB_UPD,
  CRY_CMAC_G_S_UPD_WAIT_SB_UPD,
  CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK,
  CRY_CMAC_G_S_FIN_REQ_SB_UPD,
  CRY_CMAC_G_S_FIN_WAIT_SB_UPD,
  CRY_CMAC_G_S_FIN_CP_TO_RESULT,
  CRY_CMAC_G_S_FIN_REQ_SB_FIN,
  CRY_CMAC_G_S_FIN_WAIT_SB_FIN,
  CRY_CMAC_G_S_INITIALIZED
}
Cry_CMACGenStateType;

/**
 *
 * \struct Cry_CMACGenContextType
 * \brief Structure which contains the context of the CMAC generation
 *
 *//**
 * \var Cry_CMACGenContextType::DataLength
 * \brief The length of the data over which the CMAC has to be computed.
 *//**
 * \var Cry_CMACGenContextType::BytesStoredInBlock
 * \brief How many bytes of Cry_CMACGenContextType::Block are filled at the moment.
 *//**
 * \var Cry_CMACGenContextType::KeyPtr
 * \brief A pointer to the secret key which is used for creating the
 *        CMAC.
 *//**
 * \var Cry_CMACGenContextType::Result
 * \brief A pointer to the start of a buffer where the created CMAC
 *        bytes should be stored.
 *//**
 * \var Cry_CMACGenContextType::ResultLengthPtr
 * \brief A pointer to a variable which contains the maximal allowed
 *        space for the CMAC in bytes and where the length of the created CMAC
 *        should be stored.
 *//**
 * \var Cry_CMACGenContextType::CfgPtr
 * \brief A pointer to the current CMAC generation
 *        configuration which is used.
 *//**
 * \var Cry_CMACGenContextType::DataPtr
 * \brief A pointer to the start of an array where the data is stored over which
 *        the CMAC has to be computed.
 *//**
 * \var Cry_CMACGenContextType::TruncationIsAllowed
 * \brief Is truncation of the result allowed or should an error be
 *        returned when the Result buffer is too small.
 *//**
 * \var Cry_CMACGenContextType::State
 * \brief The current state of the CMAC generation.
 *//**
 * \var Cry_CMACGenContextType::K1
 * \brief The CMAC subkey K1.
 *//**
 * \var Cry_CMACGenContextType::K2
 * \brief The CMAC subkey K2.
 *//**
 * \var Cry_CMACGenContextType::Block
 * \brief An array which contains the current block of data to encrypt.
 *//**
 * \var Cry_CMACGenContextType::LastEncryptedBlock
 * \brief The last encrypted block of data.
 */
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                         DataLength;
  uint32                                         BytesStoredInBlock;
  P2CONST(Csm_SymKeyType,        TYPEDEF, CRY_APPL_DATA) KeyPtr;
  P2VAR(uint32,                TYPEDEF, CRY_APPL_DATA) ResultLengthPtr;
  P2CONST(Cry_CMACGenConfigType, TYPEDEF, CRY_APPL_DATA) CfgPtr;
  P2VAR(uint8,                 TYPEDEF, CRY_APPL_DATA) Result;
  P2CONST(uint8,                 TYPEDEF, CRY_APPL_DATA) DataPtr;
  Cry_CMACGenStateType                           State;
  boolean                                        TruncationIsAllowed;
  uint8                                          K1[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                          K2[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                          Block[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                          LastEncryptedBlock[CRY_CMAC_BLOCK_LEN_BYTES];
}
Cry_CMACGenContextType;


/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief State: Request starting of symmetrical block encryption during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateStartReqSBSt
(
  void
);

/**
 *
 * \brief State: Request update of symmetrical block encryption during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateStartReqSBUpd
(
  void
);

/**
 *
 * \brief State: Create K1 and K2 during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateStartK1AndK2
(
  void
);

/**
 *
 * \brief State: Copy data from input during CMAC update
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateUpdCpFromInput
(
  void
);

/**
 *
 * \brief State: Request the encryption of a data block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateUpdReqSbUpd
(
  void
);

/**
 *
 * \brief State: Pad the last block of data
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateFinPadLastBlock
(
  void
);

/**
 *
 * \brief State: Request the encryption of the last block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateFinReqSbUpd
(
  void
);

/**
 *
 * \brief State: Copy the result to the result buffer
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateFinCpToResult
(
  void
);

/**
 *
 * \brief State: Try finishing the symmetrical block encryption
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACGenStateFinReqSbFin
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/**
 *
 * \brief CMAC generation context
 *
 * The context variable which is used to store the internal state of the
 * CMAC generation.
 *
 */
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_CMACGenContextType, CRY_VAR) Cry_CMACGenContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0045,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal = CSM_E_OK;

  /* Store data into context */
  Cry_CMACGenContext.CfgPtr   = (P2CONST(Cry_CMACGenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
  Cry_CMACGenContext.KeyPtr   = keyPtr;

  /* Set state of the state machine to start */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_START_REQ_SB_START;

  return RetVal;
}


/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0046,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;


  if
  (
    (CRY_CMAC_G_S_IDLE               == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_REQ_SB_UPD     == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_WAIT_SB_UPD    == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_CP_TO_RESULT   == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_REQ_SB_FIN     == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_WAIT_SB_FIN    == Cry_CMACGenContext.State)
  )
  {
    /* We are either idle or finishing the computation. A call of the update function is
     * not expected here.
     */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_CMAC_G_S_INITIALIZED == Cry_CMACGenContext.State)
  {
    /* Store data into context */
    Cry_CMACGenContext.DataPtr = dataPtr;
    Cry_CMACGenContext.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_UPD_CP_FROM_INPUT;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}



/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0047,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACGenFinish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 TruncationIsAllowed
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;

  if
  (
    (CRY_CMAC_G_S_IDLE               == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_REQ_SB_UPD     == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_WAIT_SB_UPD    == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_CP_TO_RESULT   == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_REQ_SB_FIN     == Cry_CMACGenContext.State) ||
    (CRY_CMAC_G_S_FIN_WAIT_SB_FIN    == Cry_CMACGenContext.State)
  )
  {
    /* We are either idle or finishing the computation. A call of the finish function is
     * not expected here.
     */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_CMAC_G_S_INITIALIZED == Cry_CMACGenContext.State)
  {
    if
    (
      (TruncationIsAllowed == FALSE) &&
      (*resultLengthPtr < (8U*sizeof(Cry_CMACGenContext.LastEncryptedBlock)))
    )
    {
      /* The buffer is not large enough to hold the complete CMAC and truncation
       * is not allowed. This is an error.
       */
      /* !LINKSTO CSM0662_CSM_E_NOT_OK,1 */
      RetVal = CSM_E_NOT_OK;
    }
    else
    {
      /* Store data into context */
      Cry_CMACGenContext.Result = resultPtr;
      Cry_CMACGenContext.ResultLengthPtr = resultLengthPtr;
      Cry_CMACGenContext.TruncationIsAllowed = TruncationIsAllowed;

      /* Set state of the state machine to finish */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK;

      RetVal = CSM_E_OK;
    }
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}



/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0048,1 */
FUNC(void, CRY_CODE) Cry_CMACGenMainFunction
(
  void
)
{
  switch(Cry_CMACGenContext.State)
  {
    case CRY_CMAC_G_S_START_REQ_SB_START:
    {
      Cry_CMACGenStateStartReqSBSt();
    }
    break;

    case CRY_CMAC_G_S_START_REQ_SB_UPD:
    {
      Cry_CMACGenStateStartReqSBUpd();
    }
    break;

    case CRY_CMAC_G_S_START_K1_AND_K2:
    {
      Cry_CMACGenStateStartK1AndK2();
    }
    break;

    case CRY_CMAC_G_S_UPD_CP_FROM_INPUT:
    {
      Cry_CMACGenStateUpdCpFromInput();
    }
    break;

    case CRY_CMAC_G_S_UPD_REQ_SB_UPD:
    {
      Cry_CMACGenStateUpdReqSbUpd();
    }
    break;

    case CRY_CMAC_G_S_FIN_PAD_LAST_BLOCK:
    {
      Cry_CMACGenStateFinPadLastBlock();
    }
    break;

    case CRY_CMAC_G_S_FIN_REQ_SB_UPD:
    {
      Cry_CMACGenStateFinReqSbUpd();
    }
    break;

    case CRY_CMAC_G_S_FIN_CP_TO_RESULT:
    {
      Cry_CMACGenStateFinCpToResult();
    }
    break;

    case CRY_CMAC_G_S_FIN_REQ_SB_FIN:
    {
      Cry_CMACGenStateFinReqSbFin();
    }
    break;

    case CRY_CMAC_G_S_INITIALIZED:
    case CRY_CMAC_G_S_START_WAIT_SB_START:
    case CRY_CMAC_G_S_START_WAIT_SB_UPD:
    case CRY_CMAC_G_S_UPD_WAIT_SB_UPD:
    case CRY_CMAC_G_S_FIN_WAIT_SB_UPD:
    case CRY_CMAC_G_S_FIN_WAIT_SB_FIN:
    default:
    {
      break;
    }
  }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_CMACGenCallback
(
  Csm_ReturnType Result
)
{
  if(Result != CSM_E_OK)
  {
    /* Csm has encountered an error. Finish the CMAC computation with that error. */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacGenerateCallbackNotification(Result);
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacGenerateServiceFinishNotification();
  }
  else
  {
    switch(Cry_CMACGenContext.State)
    {
      case CRY_CMAC_G_S_START_WAIT_SB_START:
      {
        /* Starting the encryption has succeeded. Now we can request encryption of the zero
         * block.
         */
        Cry_CMACGenContext.State = CRY_CMAC_G_S_START_REQ_SB_UPD;
      }
      break;

      case CRY_CMAC_G_S_START_WAIT_SB_UPD:
      {
        /* Encryption of the zero block has succeeded. Now we can create K1 and K2.
         */
        Cry_CMACGenContext.State = CRY_CMAC_G_S_START_K1_AND_K2;
      }
      break;

      case CRY_CMAC_G_S_UPD_WAIT_SB_UPD:
      {
        /* Encryption of a block has succeeded. Now we can read more input data into the
         * block.
         */
        Cry_CMACGenContext.BytesStoredInBlock = 0;
        Cry_CMACGenContext.State = CRY_CMAC_G_S_UPD_CP_FROM_INPUT;
      }
      break;

      case CRY_CMAC_G_S_FIN_WAIT_SB_UPD:
      {
        /* Encryption of the last block has succeeded. Now we can copy the CMAC to the
         * output buffer.
         */
        Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_CP_TO_RESULT;
      }
      break;

      case CRY_CMAC_G_S_FIN_WAIT_SB_FIN:
      {
        /* Finishing the encryption has succeeded. Now we can successfully finish the CMAC
         * generation.
         */
        Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacGenerateCallbackNotification(CSM_E_OK);
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacGenerateServiceFinishNotification();
      }
      break;

      /* CHECK: NOPARSE */
      /* Caution: this 'default' is required by MISRA-C:2004 */
      default:
      {
      }
      break;
      /* CHECK: PARSE */
    }
  }
  return CSM_E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>


/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_CMACGenStateStartReqSBSt
(
  void
)
{
  /* Try requesting the start of the symmetrical block encryption with the CMAC key.
   * If the request succeeds, wait for the callback by the Csm.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_START_WAIT_SB_START;
  switch
  (
    Csm_SymBlockEncryptStart
    (
      Cry_CMACGenContext.CfgPtr->SymBlockEncryptCfg,
      Cry_CMACGenContext.KeyPtr
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_START_REQ_SB_START;
    }
    break;

    default:
    {
      /* Encryption could not be started. Finish the CMAC computation with an error. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateServiceFinishNotification();
    }
    break;
  }
}


static FUNC(void, CRY_CODE) Cry_CMACGenStateStartReqSBUpd
(
  void
)
{
  /* Try requesting the encryption of the zero block. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_START_WAIT_SB_UPD;
  Cry_CMACGenContext.BytesStoredInBlock = sizeof(Cry_CMACGenContext.K1);
  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACGenContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACZeroBlock,
      sizeof(Cry_CMACZeroBlock),
      Cry_CMACGenContext.K1,
      &Cry_CMACGenContext.BytesStoredInBlock
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_START_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateServiceFinishNotification();
    }
    break;
  }
}


static FUNC(void, CRY_CODE) Cry_CMACGenStateStartK1AndK2
(
  void
)
{
  uint8 Msb;

  /* Create constant K1 from the encrypted zero block. */
  Msb = (uint8)CRY_CMAC_BYTE_WITH_MSB_SET & Cry_CMACGenContext.K1[0U];

  if(Cry_CMACGenContext.CfgPtr->MacType == CRY_CMAC_TYPE_CMAC)
  {
    Cry_CMACShiftBlockOneBitLeft(Cry_CMACGenContext.K1);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACGenContext.K1,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACGenContext.K1)
                   );
    }

    /* Create constant K2 from K1. */
    Cry_CommonCopy(Cry_CMACGenContext.K2,
                   Cry_CMACGenContext.K1,
                   sizeof(Cry_CMACGenContext.K2)
                  );

    Msb = (uint8)CRY_CMAC_BYTE_WITH_MSB_SET & Cry_CMACGenContext.K2[0U];

    Cry_CMACShiftBlockOneBitLeft(Cry_CMACGenContext.K2);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACGenContext.K2,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACGenContext.K2)
                   );
    }
  }
  else
  {
    uint8 Lsb;

    /* Copy L to K2 for L * (u ^ -1) calculation */
    Cry_CommonCopy(Cry_CMACGenContext.K2,
                   Cry_CMACGenContext.K1,
                   sizeof(Cry_CMACGenContext.K2)
                  );

    Lsb =
      (uint8)CRY_CMAC_BYTE_WITH_LSB_SET & Cry_CMACGenContext.K1[sizeof(Cry_CMACGenContext.K1) - 1U];

    /* Calculate L * u */
    Cry_CMACShiftBlockOneBitLeft(Cry_CMACGenContext.K1);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACGenContext.K1,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACGenContext.K1)
                   );
    }

    /* Calculate L * (u ^ -1) */
    Cry_CMACShiftBlockOneBitRight(Cry_CMACGenContext.K2);

    if(Lsb != 0U)
    {
      Cry_CommonXOR(Cry_CMACGenContext.K2,
                    Cry_CMACSubKeyGenerationConstantOMAC2,
                    sizeof(Cry_CMACGenContext.K2)
                   );
    }
  }

  /* Use the zero block as constant C0. */
  Cry_CommonCopy
  (
    Cry_CMACGenContext.LastEncryptedBlock,
    Cry_CMACZeroBlock,
    sizeof(Cry_CMACGenContext.Block)
  );

  /* We have not read any input data yet. */
  Cry_CMACGenContext.BytesStoredInBlock = 0;

  /* The starting of the CMAC computation has finished. We can now wait for the
   * input data.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_INITIALIZED;
  /* !LINKSTO CSM0454, 1
   */
  Csm_MacGenerateCallbackNotification(CSM_E_OK);
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateUpdCpFromInput
(
  void
)
{
  /* Fill the next block to encrypt with input data and, if there is enough data,
   * XOR it with the last encrypted block and start encrypting it.
   */

  if
  (
    (Cry_CMACGenContext.BytesStoredInBlock + Cry_CMACGenContext.DataLength) >
    sizeof(Cry_CMACGenContext.Block)
  )
  {
    uint32 newLen;

    /* We have enough data to fill a complete block to encrypt and we know that the
     * block will not be the last.
     */

    /* Copy input data to the block until it is full. */
    newLen = sizeof(Cry_CMACGenContext.Block) - Cry_CMACGenContext.BytesStoredInBlock;
    Cry_CommonCopy
    (
      &Cry_CMACGenContext.Block[Cry_CMACGenContext.BytesStoredInBlock],
      Cry_CMACGenContext.DataPtr,
      newLen
    );
    Cry_CMACGenContext.BytesStoredInBlock = sizeof(Cry_CMACGenContext.Block);

    /* Skip the bytes we have read in the input data. */
    Cry_CMACGenContext.DataPtr = &Cry_CMACGenContext.DataPtr[newLen];
    Cry_CMACGenContext.DataLength -= newLen;

    /* XOR the block of input data with the last encrypted block. */
    Cry_CommonXOR
    (
      Cry_CMACGenContext.Block,
      Cry_CMACGenContext.LastEncryptedBlock,
      sizeof(Cry_CMACGenContext.Block)
    );

    /* Request encryption of the block. */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_UPD_REQ_SB_UPD;
  }
  else
  {
    /* We do not have enough input data to fill a complete block or we do not know
     * whether the block will be the last one.
     */

    /* Copy the rest of the input data to the block. */
    Cry_CommonCopy
    (
      &Cry_CMACGenContext.Block[Cry_CMACGenContext.BytesStoredInBlock],
      Cry_CMACGenContext.DataPtr,
      Cry_CMACGenContext.DataLength
    );
    Cry_CMACGenContext.BytesStoredInBlock += Cry_CMACGenContext.DataLength;

    /* We are finished with the current update and wait for more input data or the
     * end of the CMAC computation.
     */
    Cry_CMACGenContext.State = CRY_CMAC_G_S_INITIALIZED;
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacGenerateCallbackNotification(CSM_E_OK);
  }
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateUpdReqSbUpd
(
  void
)
{
  /* Try requesting the encryption of a block of data. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_UPD_WAIT_SB_UPD;
  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACGenContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACGenContext.Block,
      sizeof(Cry_CMACGenContext.Block),
      Cry_CMACGenContext.LastEncryptedBlock,
      &(Cry_CMACGenContext.BytesStoredInBlock)
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_UPD_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateFinPadLastBlock
(
  void
)
{
  /* Pad the last block if necessary and XOR it with K1 or K2. */

  if(Cry_CMACGenContext.BytesStoredInBlock == sizeof(Cry_CMACGenContext.Block))
  {
    /* The last block is a complete block, so XOR it with K1. */
    Cry_CommonXOR
    (
      Cry_CMACGenContext.Block,
      Cry_CMACGenContext.K1,
      sizeof(Cry_CMACGenContext.Block)
    );
  }
  else
  {
    /* The last block is not a complete block. */

    /* Pad the block */
    Cry_CMACGenContext.Block[Cry_CMACGenContext.BytesStoredInBlock] =
      (uint8)CRY_CMAC_BYTE_WITH_MSB_SET;
    Cry_CMACGenContext.BytesStoredInBlock++;
    for
    (
      ;
      Cry_CMACGenContext.BytesStoredInBlock < (uint32)sizeof(Cry_CMACGenContext.Block);
      Cry_CMACGenContext.BytesStoredInBlock++
    )
    {
      Cry_CMACGenContext.Block[Cry_CMACGenContext.BytesStoredInBlock] = 0;
    }

    /* XOR the padded block with K2. */
    Cry_CommonXOR
    (
      Cry_CMACGenContext.Block,
      Cry_CMACGenContext.K2,
      sizeof(Cry_CMACGenContext.Block)
    );
  }

  /* XOR the block with the last encrypted block. */
  Cry_CommonXOR
  (
    Cry_CMACGenContext.Block,
    Cry_CMACGenContext.LastEncryptedBlock,
    sizeof(Cry_CMACGenContext.Block)
  );

  /* Request encryption of the block. */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_REQ_SB_UPD;
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateFinReqSbUpd
(
  void
)
{
  /* Try requesting the encryption of the last block. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_WAIT_SB_UPD;

  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACGenContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACGenContext.Block,
      sizeof(Cry_CMACGenContext.Block),
      Cry_CMACGenContext.LastEncryptedBlock,
      &(Cry_CMACGenContext.BytesStoredInBlock)
    )
  )
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateFinCpToResult
(
  void
)
{
  uint8 mask;
  uint8 pos;

  if(*Cry_CMACGenContext.ResultLengthPtr > (8U*sizeof(Cry_CMACGenContext.LastEncryptedBlock)))
  {
    /* The output buffer for the CMAC is larger than the CMAC. Tell the user that
     * we only wrote as many bytes as there are in a CMAC.
     */
    *Cry_CMACGenContext.ResultLengthPtr = sizeof(Cry_CMACGenContext.LastEncryptedBlock)*8U;
  }

  /* Copy the (possibly truncated) CMAC to the output buffer. */
  Cry_CommonCopy
  (
    Cry_CMACGenContext.Result,
    Cry_CMACGenContext.LastEncryptedBlock,
    (*Cry_CMACGenContext.ResultLengthPtr)/8U
  );


  if (0U < ((*Cry_CMACGenContext.ResultLengthPtr)%8U))
  {
     mask = 0x80U;
     for (pos = 1U; pos < ((*Cry_CMACGenContext.ResultLengthPtr)%8U); pos++)
     {
        mask |= (uint8) mask>>1;
     }
     Cry_CMACGenContext.Result[((*Cry_CMACGenContext.ResultLengthPtr)/8U)] &= (uint8) ~mask;

     Cry_CMACGenContext.Result[((*Cry_CMACGenContext.ResultLengthPtr)/8U)] |=
       (Cry_CMACGenContext.LastEncryptedBlock[(*Cry_CMACGenContext.ResultLengthPtr)/8U] & mask);
  }

  /* We must still finish the symmetrical block encryption. */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_REQ_SB_FIN;
}

static FUNC(void, CRY_CODE) Cry_CMACGenStateFinReqSbFin
(
  void
)
{
  /* Try finishing the symmetrical block encryption. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_WAIT_SB_FIN;

  switch ( Csm_SymBlockEncryptFinish((Cry_CMACGenContext.CfgPtr)->SymBlockEncryptCfg))
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_FIN_REQ_SB_FIN;
    }
    break;

    default:
    {
      /* Encryption could not be finished. Finish the CMAC computation with an error. */
      Cry_CMACGenContext.State = CRY_CMAC_G_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacGenerateServiceFinishNotification();
    }
    break;
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) */

typedef uint8 Cry_CMACGen_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) #else */

