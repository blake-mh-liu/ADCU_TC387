/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_AES_DecryptConfig.h>
#include <Cry_AES_Common.h>
#include <Cry_AES_Decrypt.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_AES_DECRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)

/** \brief  The SubBytes operation.
 **
 ** In the SubBytes step, each byte in AES state is updated using the rijndael decryption sbox.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptSubBytes
(
  void
);

/** \brief  The ShiftRows operation.
 **
 ** The ShiftRows step operates on the rows of AES state;
 ** it cyclically shifts the bytes in each row by a certain offset.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptShiftRows
(
  void
);

/** \brief  The MixColumns operation.
 **
 ** In the MixColumns step, the four bytes of each column of AES state are combined
 ** using an invertible linear transformation.
 ** The MixColumns function takes four bytes as input and outputs four bytes, where each input byte
 ** affects all four output bytes.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptMixColumns
(
  void
);

#else

/** \brief  Calls Cry_AES_CommonCalculateKeySchedule to expand the key and applies the
 **         InvMixColumn transformation to the expanded key.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptCalculateKeySchedule
(
  void
);

/** \brief  Decrypts the ciphertext based on the extended key and on lookup tables which combine
 **         the InvByteSub, InvShiftRow and InvMixColumn transformations.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptCalculateRounds
(
  void
);

#endif

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  The context variable which is used to store the internal state of the AES computation.
**/

/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_AES_ContextType, CRY_VAR) Cry_AES_DecryptContext;

#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_ON )
static VAR(uint32, CRY_VAR)  Cry_AES_TurnCnt;
#if (CRY_AES_DECRYPT_IMPLEMENTATION != CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
static VAR(uint32, CRY_VAR)  Cry_AES_TurnCntOp;
#endif
#endif

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0037,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_DecryptStart
(
  P2CONST(void,           AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cry_AES_ConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
          Csm_ReturnType                                locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr = (P2CONST(Cry_AES_ConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;
  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* check input arguments */
  if ( (locCfgPtr->typeKey != CRY_AES_KEY_128) &&
       (locCfgPtr->typeKey != CRY_AES_KEY_192) &&
       (locCfgPtr->typeKey != CRY_AES_KEY_256)
     )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  if ( ((locCfgPtr->typeKey == CRY_AES_KEY_128) && (keyPtr->length != CRY_AES_KEY_128)) ||
       ((locCfgPtr->typeKey == CRY_AES_KEY_192) && (keyPtr->length != CRY_AES_KEY_192)) ||
       ((locCfgPtr->typeKey == CRY_AES_KEY_256) && (keyPtr->length != CRY_AES_KEY_256))
     )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  /* if input arguments are ok edit context */
  if ( locRetVal == CSM_E_OK )
  {
    /* context state administration */
    Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_START;

    /* copy reinterpreted data of argument 'cfgPtr' to 'Cry_AES_DecryptContext' */
    switch ( locCfgPtr->typeKey )
    {
      case CRY_AES_KEY_128:
        { Cry_AES_DecryptContext.szeKey = 4; Cry_AES_DecryptContext.szeTurn = 10; }
      break;
      case CRY_AES_KEY_192:
        { Cry_AES_DecryptContext.szeKey = 6; Cry_AES_DecryptContext.szeTurn = 12; }
      break;
      case CRY_AES_KEY_256:
        { Cry_AES_DecryptContext.szeKey = 8; Cry_AES_DecryptContext.szeTurn = 14; }
      break;
      /* CHECK: NOPARSE */
      /* Caution: this 'default' is required by MISRA-C:2004 */
      default:
      {
        break;
      }
      /* CHECK: PARSE */
    }

    /* copy reinterpretetd data of argument 'keyPtr' to 'Cry_AES_DecryptContext' */
    Cry_AES_DecryptContext.keySeedLen = keyPtr->length;
    Cry_CommonCopy( Cry_AES_DecryptContext.keySeed, keyPtr->data, keyPtr->length );

    /* set misc initial context values */
    Cry_AES_DecryptContext.ctxError = CSM_E_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0038_CSM_E_NOT_OK,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_DecryptUpdate
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

  if( Cry_AES_DecryptContext.ctxState == CRY_AES_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_AES_DecryptContext.ctxState == CRY_AES_STATE_INITIALIZED )
  {
    if ( ( iputTextLength    == CRY_AES_SZESTATE) &&
         (*oputTextLengthPtr == CRY_AES_SZESTATE) )
    {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState   =  CRY_AES_STATE_UPDATE;

      /* copy input arguments into context variables */
      Cry_AES_DecryptContext.txtIput    =  iputTextPtr;
      Cry_AES_DecryptContext.txtIputLen =  iputTextLength;
      Cry_AES_DecryptContext.txtOput    =  oputTextPtr;
      Cry_AES_DecryptContext.txtOputLen = *oputTextLengthPtr;
    }
    else
    {
      locRetVal = CSM_E_NOT_OK;
      /* reset state */
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_UNINITIALIZED;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0039,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_DecryptFinish
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if( Cry_AES_DecryptContext.ctxState == CRY_AES_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_AES_DecryptContext.ctxState == CRY_AES_STATE_INITIALIZED )
  {
    /* context state administration */
    Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_FINISH;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0040,1 */
FUNC(void, CRY_CODE) Cry_AES_DecryptMainFunction
(
  void
)
{
  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_AES_DecryptContext.ctxState )
  {
    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_UNINITIALIZED **************************** */
    case CRY_AES_STATE_UNINITIALIZED:
    break;

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_START_NORMAL ***************************** */
    case CRY_AES_STATE_START:
    {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_INITIALIZED;

#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
      /* key expansion */
      Cry_AES_DecryptContext.keyExpdLen = ( 16 * (Cry_AES_DecryptContext.szeTurn + 1) );
      Cry_AES_CommonKeyExpand( &Cry_AES_DecryptContext );
#endif

      /* initializations */
      Cry_AES_DecryptContext.cntTurn  = (uint8) Cry_AES_DecryptContext.szeTurn;

      /* callback */
      /* !LINKSTO CSM0454,1 */
      Csm_SymBlockDecryptCallbackNotification(Cry_AES_DecryptContext.ctxError);
    }
    break;

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_INITIALIZED ****************************** */
    case CRY_AES_STATE_INITIALIZED:
    break;

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_UPDATE *********************************** */
    case CRY_AES_STATE_UPDATE:
    {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_CALCULATING;

#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_ON )
#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
      Cry_AES_TurnCnt = Cry_AES_DecryptContext.szeTurn;
#else
      Cry_AES_TurnCnt = (Cry_AES_DecryptContext.szeTurn + (Cry_AES_DecryptContext.szeTurn/2U));
      Cry_AES_TurnCntOp = 1U;
#endif
#endif

      /* map */
      Cry_CommonCopy(Cry_AES_DecryptContext.aesState, Cry_AES_DecryptContext.txtIput, 16);
#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
      Cry_AES_CommonAesStateTranspose(&Cry_AES_DecryptContext);
#endif
    }
    break;

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_CALCULATING ****************************** */
    case CRY_AES_STATE_CALCULATING:
    {
#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF )
#if ( CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT )
      /* initial turn */
      Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 16*Cry_AES_DecryptContext.szeTurn);
      Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);

      /* main turns */
      for ( Cry_AES_DecryptContext.cntTurn = (uint8) (Cry_AES_DecryptContext.szeTurn - 1U);
            Cry_AES_DecryptContext.cntTurn > 0;
            Cry_AES_DecryptContext.cntTurn--
          )
      {
        Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 16*(uint32)Cry_AES_DecryptContext.cntTurn);
        Cry_AES_DecryptShiftRows   ();
        Cry_AES_DecryptSubBytes    ();
        Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);
        Cry_AES_DecryptMixColumns  ();
      }

      /* final turn */
      Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 0);
      Cry_AES_DecryptSubBytes    ();
      Cry_AES_DecryptShiftRows   ();
      Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);
#else
      /* Expand the key */
      Cry_AES_DecryptCalculateKeySchedule();
      /* Calculate the output of all rounds */
      Cry_AES_DecryptCalculateRounds();
#endif

      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_INITIALIZED;

      /* unmap */
#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
      Cry_AES_CommonAesStateTranspose(&Cry_AES_DecryptContext);
#endif
      Cry_CommonCopy(Cry_AES_DecryptContext.txtOput, Cry_AES_DecryptContext.aesState, 16);
      Cry_AES_DecryptContext.txtOputLen = 16;

      /* callback */
      /* !LINKSTO CSM0454, 1
      */
      Csm_SymBlockDecryptCallbackNotification(Cry_AES_DecryptContext.ctxError);
#else /* #if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF ) */
#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
      /* initial turn */
     if ( Cry_AES_TurnCnt == Cry_AES_DecryptContext.szeTurn)
     {
      Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 16*Cry_AES_DecryptContext.szeTurn);
      Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);
     }
     else if ( Cry_AES_TurnCnt > 0 )
     {
       Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 16*Cry_AES_TurnCnt);
       Cry_AES_DecryptShiftRows   ();
       Cry_AES_DecryptSubBytes    ();
       Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);
       Cry_AES_DecryptMixColumns  ();
     }
     /* CHECK: NOPARSE */
     /* This is the last step for Cry_AES_TurnCnt and it will be evaluated only
        one time for the true condition */
     else if ( Cry_AES_TurnCnt == 0)
     /* CHECK: PARSE */
      {
       /* final turn */
       Cry_AES_CommonTurnKeyCreate(&Cry_AES_DecryptContext, 0);
       Cry_AES_DecryptSubBytes    ();
       Cry_AES_DecryptShiftRows   ();
       Cry_AES_CommonTurnKeyAdd   (&Cry_AES_DecryptContext);
       /* unmap */
      Cry_AES_CommonAesStateTranspose(&Cry_AES_DecryptContext);
#else /* #if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT) */
      if ( Cry_AES_TurnCnt > ((Cry_AES_DecryptContext.szeTurn/2) + 1))
      {
        /* Expand the key */
        Cry_AES_DecryptCalculateKeySchedule();
      }
      if ((Cry_AES_TurnCnt <= ((Cry_AES_DecryptContext.szeTurn/2) + 1)) && (Cry_AES_TurnCnt > 1U))
      { /* Calculate the output of all rounds */
        Cry_AES_DecryptCalculateRounds();
      }
      /* CHECK: NOPARSE */
      /* This is the last step for Cry_AES_TurnCnt and it will be evaluated only
        one time for the true condition */
      else if ( Cry_AES_TurnCnt == 1U)
     /* CHECK: PARSE */
#endif  /* #if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT) */
     {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_INITIALIZED;
      Cry_CommonCopy(Cry_AES_DecryptContext.txtOput, Cry_AES_DecryptContext.aesState, 16);
      Cry_AES_DecryptContext.txtOputLen = 16;
       /* callback */
       /* !LINKSTO CSM0454, 1
      */
      Csm_SymBlockDecryptCallbackNotification(Cry_AES_DecryptContext.ctxError);
     }
#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
     }
#endif
     /* CHECK: NOPARSE */
     else
     {
        /* Nothing to do */
     }
     /* CHECK: PARSE */
     if (Cry_AES_TurnCnt > 0)
     {
        Cry_AES_TurnCnt--;
     }
#if ( CRY_AES_DECRYPT_IMPLEMENTATION != CRY_AES_DECRYPT_RESOURCE_EFFICIENT )
     Cry_AES_TurnCntOp++;
#endif
#endif /* #if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF ) */
    }
    break;

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_FINISH *********************************** */
    case CRY_AES_STATE_FINISH:
    {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_UNINITIALIZED;

      /* callback */
      /* !LINKSTO CSM0454, 1
      */
      Csm_SymBlockDecryptCallbackNotification(Cry_AES_DecryptContext.ctxError);
      Csm_SymBlockDecryptServiceFinishNotification();
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. */

    /* *** Cry_AES_DecryptMainFunction > CRY_AES_STATE_ERROR ************************************ */
    case CRY_AES_STATE_ERROR:
    break;

    /* *** Cry_AES_DecryptMainFunction > DEFAULT ************************************************ */
    default:
    {
      /* context state administration */
      Cry_AES_DecryptContext.ctxState = CRY_AES_STATE_ERROR;

      Cry_AES_DecryptContext.ctxError = CSM_E_NOT_OK;
    }
    break;

    /* CHECK: PARSE */
  }
}

/*==================[internal function definitions]===============================================*/

#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT)

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_DecryptSubBytes]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptSubBytes
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  for (locLoop = 0; locLoop < CRY_AES_SZESTATE; locLoop++)
  {
    Cry_AES_DecryptContext.aesState[locLoop] =
      Cry_AES_SboxInv[Cry_AES_DecryptContext.aesState[locLoop]];
  }
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_DecryptShiftRows]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptShiftRows
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop1;
  uint32 locLoop2;
  uint32 locLoop3;
  uint8  locTemp;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  for (locLoop1 = 1; locLoop1 < 4; locLoop1++)
  {
    for (locLoop2 = 0; locLoop2 < locLoop1; locLoop2++)
    {
      locTemp = Cry_AES_DecryptContext.aesState[(locLoop1*4)+3];
      for (locLoop3 = 3; locLoop3 > 0; locLoop3--)
      {
        Cry_AES_DecryptContext.aesState[(locLoop1*4)+locLoop3] =
          Cry_AES_DecryptContext.aesState[(locLoop1*4)+(locLoop3-1)];
      }
      Cry_AES_DecryptContext.aesState[(locLoop1*4)+0] = locTemp;
    }
  }
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_DecryptMixColumns]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptMixColumns
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop;
  uint8  locCopy[CRY_AES_SZESTATE];

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_CommonCopy(locCopy, Cry_AES_DecryptContext.aesState, CRY_AES_SZESTATE);

  for (locLoop = 0U; locLoop < 4U; locLoop++)
  {
    Cry_AES_DecryptContext.aesState[locLoop +  0U] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop +  0U], 0x0EU)  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  4U], 0x0BU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x0DU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x09U);

    Cry_AES_DecryptContext.aesState[locLoop +  4U] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop +  0U], 0x09U)  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  4U], 0x0EU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x0BU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x0DU);

    Cry_AES_DecryptContext.aesState[locLoop +  8U] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop +  0U], 0x0DU)  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  4U], 0x09U)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x0EU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x0BU);

    Cry_AES_DecryptContext.aesState[locLoop + 12U] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop +  0U], 0x0BU)  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  4U], 0x0DU)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x09U)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x0EU);
  }
}

#else /* #if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT) */

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_DecryptCalculateKeySchedule]------------------------------------------------------- */
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptCalculateKeySchedule
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF )
  uint8 index;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* Expand the key */
  Cry_AES_CommonCalculateKeySchedule(&Cry_AES_DecryptContext);
#else
 if ( Cry_AES_TurnCntOp == 1U)
 {
   Cry_AES_CommonCalculateKeySchedule(&Cry_AES_DecryptContext);
 }
#endif

#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF )
  /* Apply the InvMixColumn transformation to the expanded key */
  for (index = 1U; index < Cry_AES_DecryptContext.szeTurn; index++)
  {
    const uint8 loopOffset = index * 4U;

#else
  /*Apply the InvMixColumn transformation to the expanded key */
  /* CHECK: NOPARSE */
  /* Defensive programming, the comparison expression is always evaluated as true,
     the coverage can't be obtained in automatic test environment  */
  if(Cry_AES_TurnCntOp < Cry_AES_DecryptContext.szeTurn )
  /* CHECK: PARSE */
  {
    const uint8 loopOffset = (uint8)(Cry_AES_TurnCntOp * 4U);


#endif
    Cry_AES_DecryptContext.keyExpdFast[loopOffset + 0U] =
                           Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 0U] >> 24U)
                                                      ] & 0xFFU]  ^
      CRY_AES_COMMON_ROTL3(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 0U] >> 16U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL2(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 0U] >>  8U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL1(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 0U]       ) & 0xFFU
                                                      ] & 0xFFU]);
    Cry_AES_DecryptContext.keyExpdFast[loopOffset + 1U] =
                           Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 1U] >> 24U)
                                                      ] & 0xFFU]  ^
      CRY_AES_COMMON_ROTL3(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 1U] >> 16U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL2(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 1U] >>  8U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL1(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 1U]       ) & 0xFFU
                                                      ] & 0xFFU]);
    Cry_AES_DecryptContext.keyExpdFast[loopOffset + 2U] =
                           Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 2U] >> 24U)
                                                      ] & 0xFFU]  ^
      CRY_AES_COMMON_ROTL3(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 2U] >> 16U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL2(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 2U] >>  8U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL1(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 2U]       ) & 0xFFU
                                                      ] & 0xFFU]);
    Cry_AES_DecryptContext.keyExpdFast[loopOffset + 3U] =
                           Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 3U] >> 24U)
                                                      ] & 0xFFU]  ^
      CRY_AES_COMMON_ROTL3(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 3U] >> 16U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL2(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 3U] >>  8U) & 0xFFU
                                                      ] & 0xFFU]) ^
      CRY_AES_COMMON_ROTL1(Cry_AES_Td0[Cry_AES_SboxNrm[
                              (Cry_AES_DecryptContext.keyExpdFast[loopOffset + 3U]       ) & 0xFFU
                                                      ] & 0xFFU]);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_DecryptCalculateRounds]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_DecryptCalculateRounds
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  uint32 t0 = 0U;
  uint32 t1 = 0U;
  uint32 t2 = 0U;
  uint32 t3 = 0U;
  uint32 s0 = 0U;
  uint32 s1 = 0U;
  uint32 s2 = 0U;
  uint32 s3 = 0U;
  uint8  index;
  /* Each loop calculates two turns, hence the number of loops is half of the number of turns */
  const uint8 numberOfLoops = (uint8)(Cry_AES_DecryptContext.szeTurn / 2U);
  /* Start index of the second to last sub-key */
  const uint8 keyExpdFastOffset = (uint8)(Cry_AES_DecryptContext.szeTurn * 4U);

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* Initial turn */
  /* Map the input byte array to the state */
  Cry_AES_CommonMapState(&s0, &s1, &s2, &s3, &Cry_AES_DecryptContext);

#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_ON )
  if ( Cry_AES_TurnCnt == ((Cry_AES_DecryptContext.szeTurn/2) + 1U) )
#endif
  {
     /* KeyAddition */
  s0 ^= Cry_AES_DecryptContext.keyExpdFast[keyExpdFastOffset     ];
  s1 ^= Cry_AES_DecryptContext.keyExpdFast[keyExpdFastOffset + 1U];
  s2 ^= Cry_AES_DecryptContext.keyExpdFast[keyExpdFastOffset + 2U];
  s3 ^= Cry_AES_DecryptContext.keyExpdFast[keyExpdFastOffset + 3U];
  }
#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_OFF )
    for (index = 0U; index < numberOfLoops; index++)
  {
    const uint8 keyExpdFastLoopOffset = (keyExpdFastOffset - (index * 8U));

#else
  index = (uint8)(Cry_AES_TurnCntOp - Cry_AES_DecryptContext.szeTurn);
  /* CHECK: NOPARSE */
  /* Defensive programming, the comparison expression is always evaluated as true,
     the coverage can't be obtained in automatic test environment  */
  if (index < numberOfLoops)
  /* CHECK: PARSE */
  {
    const uint8 keyExpdFastLoopOffset = (keyExpdFastOffset - (index * 8U));
#endif

    t0 =                       Cry_AES_Td0[(s0 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(s3 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(s2 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(s1       ) & 0xFFU])) ^
         Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 4U];
    t1 =                       Cry_AES_Td0[(s1 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(s0 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(s3 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(s2       ) & 0xFFU])) ^
         Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 3U];
    t2 =                       Cry_AES_Td0[(s2 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(s1 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(s0 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(s3       ) & 0xFFU])) ^
         Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 2U];
    t3 =                       Cry_AES_Td0[(s3 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(s2 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(s1 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(s0       ) & 0xFFU])) ^
         Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 1U];

    /* The last turn does not use the InvMixColumn layer */
    if (index < (numberOfLoops - 1U))
    {
      s0 =                       Cry_AES_Td0[(t0 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(t3 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(t2 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(t1       ) & 0xFFU])) ^
           Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 8U];
      s1 =                       Cry_AES_Td0[(t1 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(t0 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(t3 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(t2       ) & 0xFFU])) ^
           Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 7U];
      s2 =                       Cry_AES_Td0[(t2 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(t1 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(t0 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(t3       ) & 0xFFU])) ^
           Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 6U];
      s3 =                       Cry_AES_Td0[(t3 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Td0[(t2 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Td0[(t1 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Td0[(t0       ) & 0xFFU])) ^
           Cry_AES_DecryptContext.keyExpdFast[keyExpdFastLoopOffset - 5U];
    }
  }

  /* Final turn */
#if ( PZ1A_CRY_OPTIM_AES_DECRY_EANABLED == STD_ON )
 if( index == (numberOfLoops - 1U))
#endif
  {
  s0 = ((uint32)((uint32)Cry_AES_SboxInv[(t0 >> 24U) & 0xFFU] << 24U)  ^
                ((uint32)Cry_AES_SboxInv[(t3 >> 16U) & 0xFFU] << 16U)  ^
                ((uint32)Cry_AES_SboxInv[(t2 >>  8U) & 0xFFU] <<  8U)  ^
                ((uint32)Cry_AES_SboxInv[(t1       ) & 0xFFU]       )) ^
       Cry_AES_DecryptContext.keyExpdFast[0U];
  s1 = ((uint32)((uint32)Cry_AES_SboxInv[(t1 >> 24U) & 0xFFU] << 24U)  ^
                ((uint32)Cry_AES_SboxInv[(t0 >> 16U) & 0xFFU] << 16U)  ^
                ((uint32)Cry_AES_SboxInv[(t3 >>  8U) & 0xFFU] <<  8U)  ^
                ((uint32)Cry_AES_SboxInv[(t2       ) & 0xFFU]       )) ^
       Cry_AES_DecryptContext.keyExpdFast[1U];
  s2 = ((uint32)((uint32)Cry_AES_SboxInv[(t2 >> 24U) & 0xFFU] << 24U)  ^
                ((uint32)Cry_AES_SboxInv[(t1 >> 16U) & 0xFFU] << 16U)  ^
                ((uint32)Cry_AES_SboxInv[(t0 >>  8U) & 0xFFU] <<  8U)  ^
                ((uint32)Cry_AES_SboxInv[(t3       ) & 0xFFU]       )) ^
       Cry_AES_DecryptContext.keyExpdFast[2U];
  s3 = ((uint32)((uint32)Cry_AES_SboxInv[(t3 >> 24U) & 0xFFU] << 24U)  ^
                ((uint32)Cry_AES_SboxInv[(t2 >> 16U) & 0xFFU] << 16U)  ^
                ((uint32)Cry_AES_SboxInv[(t1 >>  8U) & 0xFFU] <<  8U)  ^
                ((uint32)Cry_AES_SboxInv[(t0       ) & 0xFFU]       )) ^
       Cry_AES_DecryptContext.keyExpdFast[3U];

  }
  /* Computation is finished, unmap the state to the byte array */
  Cry_AES_CommonUnmapState(&s0, &s1, &s2, &s3, &Cry_AES_DecryptContext);
}

#endif /* #if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT) #else */

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_AES_DECRYPT_ENABLED == STD_ON) */

typedef uint8 Cry_AES_Decrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_AES_DECRYPT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
