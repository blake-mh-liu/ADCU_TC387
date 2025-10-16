/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1, CSM0692,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>
#include <Cry_CMAC.h>
#include <Cry_CMACVrfy.h>
#include <Cry_CMACVrfyConfig.h>  /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_CMAC_VRFY_ENABLED == STD_ON)

/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/


/**
 *
 * \enum Cry_CMACVrfyStateType
 * \brief Enumeration of the internal states of the CMAC verification.
 *
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_IDLE
 * \brief Idle state of the CMAC routine.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_START_REQ_SB_START
 * \brief The underlying symmetrical block encryption a gets initialized.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_START_WAIT_SB_START
 * \brief Waiting for the encryption to finish starting.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_START_REQ_SB_UPD
 * \brief Request encryption of zero block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_START_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the zero block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_START_K1_AND_K2
 * \brief Create K1 and K2 and finish the starting of the CMAC.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_UPD_CP_FROM_INPUT
 * \brief Copy bytes from input data to encryption block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_UPD_REQ_SB_UPD
 * \brief Request encryption of data block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_UPD_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the data block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK
 * \brief Pad last block if necessary and XOR it with K1 or K2.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_REQ_SB_UPD
 * \brief Request encryption of last block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_WAIT_SB_UPD
 * \brief Waiting for the encryption to finish encrypting the last block.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_COMPARE
 * \brief Compare the given with the computed CMAC.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_REQ_SB_FIN
 * \brief Request finish of encryption.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_FIN_WAIT_SB_FIN
 * \brief Waiting for the encryption to finish.
 *//**
 * \var Cry_CMACVrfyStateType::CRY_CMAC_V_S_INITIALIZED
 * \brief the CMAC routine is initialized.
 */
typedef enum
{
  CRY_CMAC_V_S_IDLE,
  CRY_CMAC_V_S_START_REQ_SB_START,
  CRY_CMAC_V_S_START_WAIT_SB_START,
  CRY_CMAC_V_S_START_REQ_SB_UPD,
  CRY_CMAC_V_S_START_WAIT_SB_UPD,
  CRY_CMAC_V_S_START_K1_AND_K2,
  CRY_CMAC_V_S_UPD_CP_FROM_INPUT,
  CRY_CMAC_V_S_UPD_REQ_SB_UPD,
  CRY_CMAC_V_S_UPD_WAIT_SB_UPD,
  CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK,
  CRY_CMAC_V_S_FIN_REQ_SB_UPD,
  CRY_CMAC_V_S_FIN_WAIT_SB_UPD,
  CRY_CMAC_V_S_FIN_COMPARE,
  CRY_CMAC_V_S_FIN_REQ_SB_FIN,
  CRY_CMAC_V_S_FIN_WAIT_SB_FIN,
  CRY_CMAC_V_S_INITIALIZED
}
Cry_CMACVrfyStateType;

/**
 *
 * \struct Cry_CMACVrfyContextType
 * \brief Structure which contains the context of the CMAC verification
 *
 *//**
 * \var Cry_CMACVrfyContextType::DataLength
 * \brief The length of the data over which the CMAC has to be computed.
 *//**
 * \var Cry_CMACVrfyContextType::BytesStoredInBlock
 * \brief How many bytes of Cry_CMACVrfyContextType::Block are filled at the moment.
 *//**
 * \var Cry_CMACVrfyContextType::CmacLength
 * \brief The length of the CMAC to verify in bytes.
 *//**
 * \var Cry_CMACVrfyContextType::KeyPtr
 * \brief A pointer to the secret key which is used for creating the
 *        CMAC.
 *//**
 * \var Cry_CMACVrfyContextType::CfgPtr
 * \brief A pointer to the current CMAC verification
 *        configuration which is used.
 *//**
 * \var Cry_CMACVrfyContextType::CmacPtr
 * \brief A pointer to the start of a buffer where the CMAC to verify is stored.
 *//**
 * \var Cry_CMACVrfyContextType::DataPtr
 * \brief A pointer to the start of an array where the data is stored over which
 *        the CMAC has to be computed.
 *//**
 * \var Cry_CMACVrfyContextType::State
 * \brief The current state of the CMAC verification.
 *//**
 * \var Cry_CMACVrfyContextType::K1
 * \brief The CMAC subkey K1.
 *//**
 * \var Cry_CMACVrfyContextType::K2
 * \brief The CMAC subkey K2.
 *//**
 * \var Cry_CMACVrfyContextType::Block
 * \brief An array which contains the current block of data to encrypt.
 *//**
 * \var Cry_CMACVrfyContextType::LastEncryptedBlock
 * \brief The last encrypted block of data.
 */
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                          DataLength;
  uint32                                          BytesStoredInBlock;
  uint32                                          CmacLength;
  P2CONST(Csm_SymKeyType,         TYPEDEF, CRY_APPL_DATA) KeyPtr;
  P2CONST(Cry_CMACVrfyConfigType, TYPEDEF, CRY_APPL_DATA) CfgPtr;
  P2VAR(Csm_VerifyResultType,   TYPEDEF, CRY_APPL_DATA) ResultPtr;
  P2CONST(uint8,                  TYPEDEF, CRY_APPL_DATA) CmacPtr;
  P2CONST(uint8,                  TYPEDEF, CRY_APPL_DATA) DataPtr;
  Cry_CMACVrfyStateType                           State;
  uint8                                           K1[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                           K2[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                           Block[CRY_CMAC_BLOCK_LEN_BYTES];
  uint8                                           LastEncryptedBlock[CRY_CMAC_BLOCK_LEN_BYTES];
}
Cry_CMACVrfyContextType;


/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief State: Request starting of symmetrical block encryption during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartReqSBSt
(
  void
);

/**
 *
 * \brief State: Request update of symmetrical block encryption during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartReqSBUpd
(
  void
);

/**
 *
 * \brief State: Create K1 and K2 during CMAC start
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartK1AndK2
(
  void
);

/**
 *
 * \brief State: Copy data from input during CMAC update
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateUpdCpFromInput
(
  void
);

/**
 *
 * \brief State: Request the encryption of a data block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateUpdReqSbUpd
(
  void
);

/**
 *
 * \brief State: Pad the last block of data
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinPadLastBlock
(
  void
);

/**
 *
 * \brief State: Request the encryption of the last data block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinReqSbUpd
(
  void
);

/**
 *
 * \brief State: Compare the computed CMAC with the provided CMAC
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinCompare
(
  void
);

/**
 *
 * \brief State: Complete the encryption of a data block
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinReqSbFin
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
 * \brief CMAC verification context
 *
 * The context variable which is used to store the internal state of the
 * CMAC verification.
 *
 */
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_CMACVrfyContextType, CRY_VAR) Cry_CMACVrfyContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0049,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACVrfyStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType RetVal = CSM_E_OK;

  /* Store data into context */
  Cry_CMACVrfyContext.CfgPtr = (P2CONST(Cry_CMACVrfyConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
  Cry_CMACVrfyContext.KeyPtr = keyPtr;

  /* Set state of the state machine to start */
  Cry_CMACVrfyContext.State  = CRY_CMAC_V_S_START_REQ_SB_START;

  return RetVal;
}


/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0050,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACVrfyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;


  if
  (
    (CRY_CMAC_V_S_IDLE               == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_REQ_SB_UPD     == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_WAIT_SB_UPD    == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_COMPARE        == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_REQ_SB_FIN     == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_WAIT_SB_FIN    == Cry_CMACVrfyContext.State)
  )
  {
    /* We are either idle or finishing the computation. A call of the update function is
     * not expected here.
     */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_CMAC_V_S_INITIALIZED == Cry_CMACVrfyContext.State)
  {
    /* Store data into context */
    Cry_CMACVrfyContext.DataPtr = dataPtr;
    Cry_CMACVrfyContext.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_UPD_CP_FROM_INPUT;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0051,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CMACVrfyFinish
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA)              authenticationPtr,
   uint32                                                authenticationLength,
   P2VAR(Csm_VerifyResultType, AUTOMATIC, CRY_APPL_DATA) resultPtr
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;

  if
  (
    (CRY_CMAC_V_S_IDLE               == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_REQ_SB_UPD     == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_WAIT_SB_UPD    == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_COMPARE        == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_REQ_SB_FIN     == Cry_CMACVrfyContext.State) ||
    (CRY_CMAC_V_S_FIN_WAIT_SB_FIN    == Cry_CMACVrfyContext.State)
  )
  {
    /* We are either idle or finishing the computation. A call of the finish function is
     * not expected here.
     */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_CMAC_V_S_INITIALIZED == Cry_CMACVrfyContext.State)
  {
    if(authenticationLength > (8U*sizeof(Cry_CMACVrfyContext.LastEncryptedBlock)))
    {
      /* It is not possible to have a CMAC of the size given by the user. This is an error.
       */
      RetVal = CSM_E_NOT_OK;
    }
    else
    {
      /* Store data into context */
      Cry_CMACVrfyContext.CmacPtr = authenticationPtr;
      Cry_CMACVrfyContext.CmacLength = authenticationLength;
      Cry_CMACVrfyContext.ResultPtr = resultPtr;

      /* Set state of the state machine to finish */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK;

      RetVal = CSM_E_OK;
    }
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}



/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0052,1 */
FUNC(void, CRY_CODE) Cry_CMACVrfyMainFunction
(
  void
)
{
  switch(Cry_CMACVrfyContext.State)
  {
    case CRY_CMAC_V_S_START_REQ_SB_START:
    {
      Cry_CMACVrfyStateStartReqSBSt();
    }
    break;

    case CRY_CMAC_V_S_START_REQ_SB_UPD:
    {
      Cry_CMACVrfyStateStartReqSBUpd();
    }
    break;

    case CRY_CMAC_V_S_START_K1_AND_K2:
    {
      Cry_CMACVrfyStateStartK1AndK2();
    }
    break;

    case CRY_CMAC_V_S_UPD_CP_FROM_INPUT:
    {
      Cry_CMACVrfyStateUpdCpFromInput();
    }
    break;

    case CRY_CMAC_V_S_UPD_REQ_SB_UPD:
    {
      Cry_CMACVrfyStateUpdReqSbUpd();
    }
    break;

    case CRY_CMAC_V_S_FIN_PAD_LAST_BLOCK:
    {
      Cry_CMACVrfyStateFinPadLastBlock();
    }
    break;

    case CRY_CMAC_V_S_FIN_REQ_SB_UPD:
    {
      Cry_CMACVrfyStateFinReqSbUpd();
    }
    break;

    case CRY_CMAC_V_S_FIN_COMPARE:
    {
      Cry_CMACVrfyStateFinCompare();
    }
    break;

    case CRY_CMAC_V_S_FIN_REQ_SB_FIN:
    {
      Cry_CMACVrfyStateFinReqSbFin();
    }
    break;

    case CRY_CMAC_V_S_INITIALIZED:
    case CRY_CMAC_V_S_START_WAIT_SB_START:
    case CRY_CMAC_V_S_START_WAIT_SB_UPD:
    case CRY_CMAC_V_S_UPD_WAIT_SB_UPD:
    case CRY_CMAC_V_S_FIN_WAIT_SB_UPD:
    case CRY_CMAC_V_S_FIN_WAIT_SB_FIN:
    default:
    {
    }
    break;
  }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_CMACVrfyCallback
(
  Csm_ReturnType Result
)
{
  if(Result != CSM_E_OK)
  {
    /* Csm has encountered an error. Finish the CMAC computation with that error. */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacVerifyCallbackNotification(Result);
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacVerifyServiceFinishNotification();
  }
  else
  {
    switch(Cry_CMACVrfyContext.State)
    {
      case CRY_CMAC_V_S_START_WAIT_SB_START:
      {
        /* Starting the encryption has succeeded. Now we can request encryption of the zero
         * block.
         */
        Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_REQ_SB_UPD;
      }
      break;

      case CRY_CMAC_V_S_START_WAIT_SB_UPD:
      {
        /* Encryption of the zero block has succeeded. Now we can create K1 and K2.
         */
        Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_K1_AND_K2;
      }
      break;

      case CRY_CMAC_V_S_UPD_WAIT_SB_UPD:
      {
        /* Encryption of a block has succeeded. Now we can read more input data into the
         * block.
         */
        Cry_CMACVrfyContext.BytesStoredInBlock = 0;
        Cry_CMACVrfyContext.State = CRY_CMAC_V_S_UPD_CP_FROM_INPUT;
      }
      break;

      case CRY_CMAC_V_S_FIN_WAIT_SB_UPD:
      {
        /* Encryption of the last block has succeeded. Now we can compare the computed
         * CMAC with the CMAC given by the user.
         */
        Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_COMPARE;
      }
      break;

      case CRY_CMAC_V_S_FIN_WAIT_SB_FIN:
      {
        /* Finishing the encryption has succeeded. Now we can successfully finish the CMAC
         * verification.
         */
        Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacVerifyCallbackNotification(CSM_E_OK);
        /* !LINKSTO CSM0454, 1
         */
        Csm_MacVerifyServiceFinishNotification();
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

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartReqSBSt
(
  void
)
{
  /* Try requesting the start of the symmetrical block encryption with the CMAC key.
   * If the request succeeds, wait for the callback by the Csm.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_WAIT_SB_START;
  switch
  (
    Csm_SymBlockEncryptStart
    (
      Cry_CMACVrfyContext.CfgPtr->SymBlockEncryptCfg,
      Cry_CMACVrfyContext.KeyPtr
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
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_REQ_SB_START;
    }
    break;

    default:
    {
      /* Encryption could not be started. Finish the CMAC computation with an error. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    }
    break;
  }
}


static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartReqSBUpd
(
  void
)
{
  /* Try requesting the encryption of the zero block. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_WAIT_SB_UPD;
  Cry_CMACVrfyContext.BytesStoredInBlock = sizeof(Cry_CMACVrfyContext.K1);
  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACVrfyContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACZeroBlock,
      sizeof(Cry_CMACZeroBlock),
      Cry_CMACVrfyContext.K1,
      &Cry_CMACVrfyContext.BytesStoredInBlock
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
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_START_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    }
    break;
  }
}


static FUNC(void, CRY_CODE) Cry_CMACVrfyStateStartK1AndK2
(
  void
)
{
  uint8 Msb;

  /* Create constant K1 from the encrypted zero block. */
  Msb = (uint8)CRY_CMAC_BYTE_WITH_MSB_SET & Cry_CMACVrfyContext.K1[0U];

  if(Cry_CMACVrfyContext.CfgPtr->MacType == CRY_CMAC_TYPE_CMAC)
  {
    Cry_CMACShiftBlockOneBitLeft(Cry_CMACVrfyContext.K1);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACVrfyContext.K1,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACVrfyContext.K1)
                   );
    }

    /* Create constant K2 from K1. */
    Cry_CommonCopy(Cry_CMACVrfyContext.K2,
                   Cry_CMACVrfyContext.K1,
                   sizeof(Cry_CMACVrfyContext.K2)
                  );

    Msb = (uint8)CRY_CMAC_BYTE_WITH_MSB_SET & Cry_CMACVrfyContext.K2[0U];

    Cry_CMACShiftBlockOneBitLeft(Cry_CMACVrfyContext.K2);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACVrfyContext.K2,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACVrfyContext.K2)
                   );
    }
  }
  else
  {
    uint8 Lsb;

    /* Copy L to K2 for L * (u ^ -1) calculation */
    Cry_CommonCopy(Cry_CMACVrfyContext.K2,
                   Cry_CMACVrfyContext.K1,
                   sizeof(Cry_CMACVrfyContext.K2)
                  );

    Lsb = (uint8)
          CRY_CMAC_BYTE_WITH_LSB_SET & Cry_CMACVrfyContext.K1[sizeof(Cry_CMACVrfyContext.K1) - 1U];

    /* Calculate L * u */
    Cry_CMACShiftBlockOneBitLeft(Cry_CMACVrfyContext.K1);

    if(Msb != 0U)
    {
      Cry_CommonXOR(Cry_CMACVrfyContext.K1,
                    Cry_CMACSubKeyGenerationConstant,
                    sizeof(Cry_CMACVrfyContext.K1)
                   );
    }

    /* Calculate L * (u ^ -1) */
    Cry_CMACShiftBlockOneBitRight(Cry_CMACVrfyContext.K2);

    if(Lsb != 0U)
    {
      Cry_CommonXOR(Cry_CMACVrfyContext.K2,
                    Cry_CMACSubKeyGenerationConstantOMAC2,
                    sizeof(Cry_CMACVrfyContext.K2)
                   );
    }
  }

  /* Use the zero block as constant C0. */
  Cry_CommonCopy
  (
    Cry_CMACVrfyContext.LastEncryptedBlock,
    Cry_CMACZeroBlock,
    sizeof(Cry_CMACVrfyContext.Block)
  );

  /* We have not read any input data yet. */
  Cry_CMACVrfyContext.BytesStoredInBlock = 0;

  /* The starting of the CMAC computation has finished. We can now wait for the
   * input data.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_INITIALIZED;
  /* !LINKSTO CSM0454, 1
   */
  Csm_MacVerifyCallbackNotification(CSM_E_OK);
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateUpdCpFromInput
(
  void
)
{
  /* Fill the next block to encrypt with input data and, if there is enough data,
   * XOR it with the last encrypted block and start encrypting it.
   */

  if
  (
    (Cry_CMACVrfyContext.BytesStoredInBlock + Cry_CMACVrfyContext.DataLength) >
    sizeof(Cry_CMACVrfyContext.Block)
  )
  {
    uint32 newLen;


    /* We have enough data to fill a complete block to encrypt and we know that the
     * block will not be the last.
     */

    /* Copy input data to the block until it is full. */
    newLen = sizeof(Cry_CMACVrfyContext.Block) - Cry_CMACVrfyContext.BytesStoredInBlock;
    Cry_CommonCopy
    (
      &Cry_CMACVrfyContext.Block[Cry_CMACVrfyContext.BytesStoredInBlock],
      Cry_CMACVrfyContext.DataPtr,
      newLen
    );
    Cry_CMACVrfyContext.BytesStoredInBlock = sizeof(Cry_CMACVrfyContext.Block);

    /* Skip the bytes we have read in the input data. */
    Cry_CMACVrfyContext.DataPtr = &Cry_CMACVrfyContext.DataPtr[newLen];
    Cry_CMACVrfyContext.DataLength -= newLen;

    /* XOR the block of input data with the last encrypted block. */
    Cry_CommonXOR
    (
      Cry_CMACVrfyContext.Block,
      Cry_CMACVrfyContext.LastEncryptedBlock,
      sizeof(Cry_CMACVrfyContext.Block)
    );

    /* Request encryption of the block. */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_UPD_REQ_SB_UPD;
  }
  else
  {
    /* We do not have enough input data to fill a complete block or we do not know
     * whether the block will be the last one.
     */

    /* Copy the rest of the input data to the block. */
    Cry_CommonCopy
    (
      &Cry_CMACVrfyContext.Block[Cry_CMACVrfyContext.BytesStoredInBlock],
      Cry_CMACVrfyContext.DataPtr,
      Cry_CMACVrfyContext.DataLength
    );
    Cry_CMACVrfyContext.BytesStoredInBlock += Cry_CMACVrfyContext.DataLength;

    /* We are finished with the current update and wait for more input data or the
     * end of the CMAC computation.
     */
    Cry_CMACVrfyContext.State = CRY_CMAC_V_S_INITIALIZED;
    /* !LINKSTO CSM0454, 1
     */
    Csm_MacVerifyCallbackNotification(CSM_E_OK);
  }
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateUpdReqSbUpd
(
  void
)
{
  /* Try requesting the encryption of a block of data. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_UPD_WAIT_SB_UPD;
  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACVrfyContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACVrfyContext.Block,
      sizeof(Cry_CMACVrfyContext.Block),
      Cry_CMACVrfyContext.LastEncryptedBlock,
      &(Cry_CMACVrfyContext.BytesStoredInBlock)
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
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_UPD_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinPadLastBlock
(
  void
)
{
  /* Pad the last block if necessary and XOR it with K1 or K2. */

  if(Cry_CMACVrfyContext.BytesStoredInBlock == sizeof(Cry_CMACVrfyContext.Block))
  {
    /* The last block is a complete block, so XOR it with K1. */
    Cry_CommonXOR
    (
      Cry_CMACVrfyContext.Block,
      Cry_CMACVrfyContext.K1,
      sizeof(Cry_CMACVrfyContext.Block)
    );
  }
  else
  {
    /* The last block is not a complete block. */

    /* Pad the block */
    Cry_CMACVrfyContext.Block[Cry_CMACVrfyContext.BytesStoredInBlock] =
      (uint8)CRY_CMAC_BYTE_WITH_MSB_SET;
    Cry_CMACVrfyContext.BytesStoredInBlock++;
    for
    (
      ;
      Cry_CMACVrfyContext.BytesStoredInBlock < (uint32)sizeof(Cry_CMACVrfyContext.Block);
      Cry_CMACVrfyContext.BytesStoredInBlock++
    )
    {
      Cry_CMACVrfyContext.Block[Cry_CMACVrfyContext.BytesStoredInBlock] = 0;
    }

    /* XOR the padded block with K2. */
    Cry_CommonXOR
    (
      Cry_CMACVrfyContext.Block,
      Cry_CMACVrfyContext.K2,
      sizeof(Cry_CMACVrfyContext.Block)
    );
  }

  /* XOR the block with the last encrypted block. */
  Cry_CommonXOR
  (
    Cry_CMACVrfyContext.Block,
    Cry_CMACVrfyContext.LastEncryptedBlock,
    sizeof(Cry_CMACVrfyContext.Block)
  );

  /* Request encryption of the block. */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_REQ_SB_UPD;
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinReqSbUpd
(
  void
)
{
  /* Try requesting the encryption of the last block. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_WAIT_SB_UPD;

  switch
  (
    Csm_SymBlockEncryptUpdate
    (
      (Cry_CMACVrfyContext.CfgPtr)->SymBlockEncryptCfg,
      Cry_CMACVrfyContext.Block,
      sizeof(Cry_CMACVrfyContext.Block),
      Cry_CMACVrfyContext.LastEncryptedBlock,
      &(Cry_CMACVrfyContext.BytesStoredInBlock)
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
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_REQ_SB_UPD;
    }
    break;

    default:
    {
      /* Encryption could not be requested. Finish the CMAC computation with an error. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    }
    break;
  }
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinCompare
(
  void
)
{
  uint8 mask;
  uint8 pos;

  /* Compare the CMAC given by the user with the CMAC which has just been computed. */
  if
  (
  /* Compare whole bytes*/
    Cry_CommonCompare
    (
      Cry_CMACVrfyContext.LastEncryptedBlock,
      Cry_CMACVrfyContext.CmacPtr,
      Cry_CMACVrfyContext.CmacLength/8U
    ) == CRY_E_EQUAL
  )
  {
    *Cry_CMACVrfyContext.ResultPtr = CSM_E_VER_OK;

    /* Compare rest of bits */
    if (0U < (Cry_CMACVrfyContext.CmacLength%8U))
    {
      mask = 0x00U;
      for (pos = 0U; pos < (Cry_CMACVrfyContext.CmacLength%8U); pos++)
      {
        mask = (mask>>1) + 0x80U;
      }

      if (((Cry_CMACVrfyContext.LastEncryptedBlock[(Cry_CMACVrfyContext.CmacLength/8U)]) &
           (mask)
          )
          !=
          ((Cry_CMACVrfyContext.CmacPtr[(Cry_CMACVrfyContext.CmacLength/8U)]) &
           (mask)
          )
         )
      {
        *Cry_CMACVrfyContext.ResultPtr = CSM_E_VER_NOT_OK;
      }
    }
  }
  else
  {
    *Cry_CMACVrfyContext.ResultPtr = CSM_E_VER_NOT_OK;
  }

  /* We must still finish the symmetrical block encryption. */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_REQ_SB_FIN;
}

static FUNC(void, CRY_CODE) Cry_CMACVrfyStateFinReqSbFin
(
  void
)
{
  /* Try finishing the symmetrical block encryption. If the request succeeds, wait
   * for the callback by the Csm.
   */
  Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_WAIT_SB_FIN;

  switch ( Csm_SymBlockEncryptFinish((Cry_CMACVrfyContext.CfgPtr)->SymBlockEncryptCfg))
  {
    case CSM_E_OK:
    {
    }
    break;

    case CSM_E_BUSY:
    {
      /* Encryption is busy. Try it again at a later time. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_FIN_REQ_SB_FIN;
    }
    break;

    default:
    {
      /* Encryption could not be finished. Finish the CMAC computation with an error. */
      Cry_CMACVrfyContext.State = CRY_CMAC_V_S_IDLE;
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyCallbackNotification(CSM_E_NOT_OK);
      /* !LINKSTO CSM0454, 1
       */
      Csm_MacVerifyServiceFinishNotification();
    }
    break;
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_CMAC_VRFY_ENABLED == STD_ON) */

typedef uint8 Cry_CMACvrfy_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CMAC_VRFY_ENABLED == STD_ON) #else */

