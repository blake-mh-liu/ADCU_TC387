/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_AES_EncryptConfig.h>
#include <Cry_AES_Common.h>
#include <Cry_AES_Encrypt.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_AES_ENCRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)

/** \brief  The SubBytes operation.
 **
 ** In the SubBytes step, each byte in AES state is updated using the rijndael encryption sbox.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptSubBytes
(
  void
);

/** \brief  The ShiftRows operation.
 **
 ** The ShiftRows step operates on the rows of AES state;
 ** it cyclically shifts the bytes in each row by a certain offset.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptShiftRows
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
STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptMixColumns
(
  void
);

#else

/** \brief  Calls Cry_AES_CommonCalculateKeySchedule to expand the key.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptCalculateKeySchedule
(
  void
);

/** \brief  Encrypts the ciphertext based on the extended key and on lookup tables which combine
 **         the ByteSub, ShiftRow and MixColumn transformations.
 **/
STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptCalculateRounds
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
static VAR(Cry_AES_ContextType, CRY_VAR) Cry_AES_EncryptContext;

#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_ON )
STATIC VAR(uint32, CRY_VAR)  Cry_AES_TurnCnt;
#endif

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0041,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptStart
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
    Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_START;

    /* copy reinterpreted data of argument 'cfgPtr' to 'Cry_AES_EncryptContext' */
    switch ( locCfgPtr->typeKey )
    {
      case CRY_AES_KEY_128:
        { Cry_AES_EncryptContext.szeKey = 4; Cry_AES_EncryptContext.szeTurn = 10; }
      break;
      case CRY_AES_KEY_192:
        { Cry_AES_EncryptContext.szeKey = 6; Cry_AES_EncryptContext.szeTurn = 12; }
      break;
      case CRY_AES_KEY_256:
        { Cry_AES_EncryptContext.szeKey = 8; Cry_AES_EncryptContext.szeTurn = 14; }
      break;
      /* CHECK: NOPARSE */
      /* Caution: this 'default' is required by MISRA-C:2004 */
      default:
      {
        break;
      }
      /* CHECK: PARSE */
    }

    /* copy reinterpretetd data of argument 'keyPtr' to 'Cry_AES_EncryptContext' */
    Cry_AES_EncryptContext.keySeedLen = keyPtr->length;
    Cry_CommonCopy( Cry_AES_EncryptContext.keySeed, keyPtr->data, keyPtr->length );

    /* set misc initial context values */
    Cry_AES_EncryptContext.ctxError = CSM_E_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0042_CSM_E_NOT_OK,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptUpdate
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

  if      ( Cry_AES_EncryptContext.ctxState == CRY_AES_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_AES_EncryptContext.ctxState == CRY_AES_STATE_INITIALIZED   )
  {
    if ( ( iputTextLength    == CRY_AES_SZESTATE) &&
         (*oputTextLengthPtr == CRY_AES_SZESTATE)    )
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState   =  CRY_AES_STATE_UPDATE;

      /* copy input arguments into context variables */
      Cry_AES_EncryptContext.txtIput    =  iputTextPtr;
      Cry_AES_EncryptContext.txtIputLen =  iputTextLength;
      Cry_AES_EncryptContext.txtOput    =  oputTextPtr;
      Cry_AES_EncryptContext.txtOputLen = *oputTextLengthPtr;
    }
    else
    {
      locRetVal = CSM_E_NOT_OK;

      /* reset state */

      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_UNINITIALIZED;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0043,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_AES_EncryptFinish
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if      ( Cry_AES_EncryptContext.ctxState == CRY_AES_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_AES_EncryptContext.ctxState == CRY_AES_STATE_INITIALIZED    )
  {
    /* context state administration */
    Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_FINISH;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0044,1 */
FUNC(void, CRY_CODE) Cry_AES_EncryptMainFunction
(
  void
)
{
  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_AES_EncryptContext.ctxState )
  {
    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_UNINITIALIZED **************************** */
    case CRY_AES_STATE_UNINITIALIZED:
    break;

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_START ************************************ */
    case CRY_AES_STATE_START:
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_INITIALIZED;

#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      /* key expansion */
      Cry_AES_EncryptContext.keyExpdLen = ( 16 * (Cry_AES_EncryptContext.szeTurn + 1) );
      Cry_AES_CommonKeyExpand( &Cry_AES_EncryptContext );
#endif

      /* initializations */
      Cry_AES_EncryptContext.cntTurn  = 0;

      /* callback */
      /* !LINKSTO CSM0454, 1 */
      Csm_SymBlockEncryptCallbackNotification(Cry_AES_EncryptContext.ctxError);
    }
    break;

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_INITIALIZED ****************************** */
    case CRY_AES_STATE_INITIALIZED:
    break;

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_UPDATE *********************************** */
    case CRY_AES_STATE_UPDATE:
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_CALCULATING;

#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_ON )
      Cry_AES_TurnCnt = 0;
#endif

      /* map */
      Cry_CommonCopy(Cry_AES_EncryptContext.aesState, Cry_AES_EncryptContext.txtIput, 16);
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      Cry_AES_CommonAesStateTranspose(&Cry_AES_EncryptContext);
#endif
    }
    break;

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_CALCULATING ****************************** */
    case CRY_AES_STATE_CALCULATING:
    {
#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_OFF )
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      /* initial turn */
      Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 0);
      Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);

      /* main turns */
      for ( Cry_AES_EncryptContext.cntTurn = 1;
            Cry_AES_EncryptContext.cntTurn < Cry_AES_EncryptContext.szeTurn;
            Cry_AES_EncryptContext.cntTurn++
          )
      {
        Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 16*(uint32)Cry_AES_EncryptContext.cntTurn);
        Cry_AES_EncryptSubBytes    ();
        Cry_AES_EncryptShiftRows   ();
        Cry_AES_EncryptMixColumns  ();
        Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);
      }

      /* final turn */
      Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 16*Cry_AES_EncryptContext.szeTurn);
      Cry_AES_EncryptSubBytes    ();
      Cry_AES_EncryptShiftRows   ();
      Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);
#else
      /* Expand the key */
      Cry_AES_EncryptCalculateKeySchedule();
      /* Calculate the output of all rounds */
      Cry_AES_EncryptCalculateRounds();
#endif

      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_INITIALIZED;

      /* unmap */
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      Cry_AES_CommonAesStateTranspose(&Cry_AES_EncryptContext);
#endif
      Cry_CommonCopy(Cry_AES_EncryptContext.txtOput, Cry_AES_EncryptContext.aesState, 16);
      Cry_AES_EncryptContext.txtOputLen = 16;

      /* callback */
      /* !LINKSTO CSM0454, 1
      */
      Csm_SymBlockEncryptCallbackNotification(Cry_AES_EncryptContext.ctxError);
#else
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)

      if ( Cry_AES_TurnCnt == 0 )
      {
        /* initial turn */
        Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 0);
        Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);
      }
      else  if ( Cry_AES_TurnCnt < (Cry_AES_EncryptContext.szeTurn) )
      {
         /* main turns */
        Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 16*Cry_AES_TurnCnt);
        Cry_AES_EncryptSubBytes    ();
        Cry_AES_EncryptShiftRows   ();
        Cry_AES_EncryptMixColumns  ();
        Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);
      }
      /* CHECK: NOPARSE */
      /* This is the last step for Cry_AES_TurnCnt and it will be evaluated only
         one time for the true condition */
      else if ( Cry_AES_TurnCnt == Cry_AES_EncryptContext.szeTurn)
      /* CHECK: PARSE */
      {
        /* final turn */
        Cry_AES_CommonTurnKeyCreate(&Cry_AES_EncryptContext, 16*Cry_AES_EncryptContext.szeTurn);
        Cry_AES_EncryptSubBytes    ();
        Cry_AES_EncryptShiftRows   ();
        Cry_AES_CommonTurnKeyAdd   (&Cry_AES_EncryptContext);

#else
      /* Expand the key */
    if ( Cry_AES_TurnCnt == 0 )
    {
      Cry_AES_EncryptCalculateKeySchedule();
    }
    if ( Cry_AES_TurnCnt < Cry_AES_EncryptContext.szeTurn/2U )
    {
     /* Calculate the output of all rounds */
      Cry_AES_EncryptCalculateRounds();
    }
#endif
      /* unmap */
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      Cry_AES_CommonAesStateTranspose(&Cry_AES_EncryptContext);
#else
   if ( Cry_AES_TurnCnt == Cry_AES_EncryptContext.szeTurn/2U)
#endif
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_INITIALIZED;
      Cry_CommonCopy(Cry_AES_EncryptContext.txtOput, Cry_AES_EncryptContext.aesState, 16);
      Cry_AES_EncryptContext.txtOputLen = 16;
       /* !LINKSTO CSM0454, 1
      */
      /* callback */
      Csm_SymBlockEncryptCallbackNotification(Cry_AES_EncryptContext.ctxError);
    }
#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
      }
      else
      {
         /* Nothing to do */
      }
#endif
      Cry_AES_TurnCnt++;
#endif

    }
    break;

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_FINISH *********************************** */
    case CRY_AES_STATE_FINISH:
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_UNINITIALIZED;

      /* callback */
      /* !LINKSTO CSM0454, 1
      */
      Csm_SymBlockEncryptCallbackNotification(Cry_AES_EncryptContext.ctxError);
      Csm_SymBlockEncryptServiceFinishNotification();
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. */

    /* *** Cry_AES_EncryptMainFunction > CRY_AES_STATE_ERROR ************************************ */
    case CRY_AES_STATE_ERROR:
    break;

    /* *** Cry_AES_EncryptMainFunction > DEFAULT ************************************************ */
    default:
    {
      /* context state administration */
      Cry_AES_EncryptContext.ctxState = CRY_AES_STATE_ERROR;

      Cry_AES_EncryptContext.ctxError = CSM_E_NOT_OK;
    }
    break;

    /* CHECK: PARSE */
  }
}

/*==================[internal function definitions]===============================================*/

#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_EncryptSubBytes]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptSubBytes
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  for (locLoop = 0; locLoop < CRY_AES_SZESTATE; locLoop++)
  {
    Cry_AES_EncryptContext.aesState[locLoop] =
      Cry_AES_SboxNrm[Cry_AES_EncryptContext.aesState[locLoop]];
  }
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_EncryptShiftRows]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptShiftRows
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
      locTemp = Cry_AES_EncryptContext.aesState[(locLoop1*4)+0];
      for (locLoop3 = 0; locLoop3 < 3; locLoop3++)
      {
        Cry_AES_EncryptContext.aesState[(locLoop1*4)+locLoop3] =
          Cry_AES_EncryptContext.aesState[(locLoop1*4)+locLoop3+1];
      }
      Cry_AES_EncryptContext.aesState[(locLoop1*4)+3] = locTemp;
    }
  }
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_EncryptMixColumns]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptMixColumns
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop;
  uint8  locCopy[CRY_AES_SZESTATE];

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_CommonCopy(locCopy, Cry_AES_EncryptContext.aesState, CRY_AES_SZESTATE);

  for (locLoop = 0U; locLoop < 4U; locLoop++)
  {
    Cry_AES_EncryptContext.aesState[locLoop +  0U] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop + 0U], 0x02U)  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 4U], 0x03U)) ^
                                            locCopy[locLoop + 8U])         ^
                                            locCopy[locLoop + 12U];

    Cry_AES_EncryptContext.aesState[(locLoop +  4U)] =
      (uint8)((uint8)(                      locCopy[locLoop +  0U]           ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  4U], 0x02U))  ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x03U))  ^
                                            locCopy[locLoop + 12U];

    Cry_AES_EncryptContext.aesState[(locLoop +  8U)] =
      (uint8)((uint8)(                      locCopy[locLoop +  0U]          ^
                                            locCopy[locLoop +  4U])         ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop +  8U], 0x02U)) ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x03U);

    Cry_AES_EncryptContext.aesState[(locLoop + 12U)] =
      (uint8)((uint8)(CRY_AES_COMMONMULGF28(locCopy[locLoop +  0U], 0x03U)   ^
                                            locCopy[locLoop +  4U])          ^
                                            locCopy[locLoop +  8U])          ^
                      CRY_AES_COMMONMULGF28(locCopy[locLoop + 12U], 0x02U);
  }
}

#else /* #if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) */

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_EncryptCalculateKeySchedule]------------------------------------------------------- */
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptCalculateKeySchedule
(
  void
)
{
  /* Expand the key */
  Cry_AES_CommonCalculateKeySchedule(&Cry_AES_EncryptContext);
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_AES_EncryptCalculateRounds]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

STATIC FUNC(void, CRY_CODE) Cry_AES_EncryptCalculateRounds
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
  const uint8 numberOfLoops = (uint8)(Cry_AES_EncryptContext.szeTurn / 2U);
  /* Start index of the last sub-key */
  const uint8 keyExpdFastOffset = (uint8)(Cry_AES_EncryptContext.szeTurn * 4U);

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* Initial turn */
  /* Map the input byte array to the state */
  Cry_AES_CommonMapState(&s0, &s1, &s2, &s3, &Cry_AES_EncryptContext);
#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_ON )
  if ( Cry_AES_TurnCnt == 0 )
#endif
  {
     /* KeyAddition */
  s0 ^= Cry_AES_EncryptContext.keyExpdFast[0];
  s1 ^= Cry_AES_EncryptContext.keyExpdFast[1];
  s2 ^= Cry_AES_EncryptContext.keyExpdFast[2];
  s3 ^= Cry_AES_EncryptContext.keyExpdFast[3];
  }
#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_OFF )
  /* Main turns */
  for (index = 0U; index < numberOfLoops; index++)
  {
    const uint8 keyExpdFastLoopOffset = index * 8U;

#else
  /* CHECK: NOPARSE */
  /* Defensive programming, the comparison expression is always evaluated as true,
     the coverage can't be obtained in automatic test environment  */
  if ((uint8)Cry_AES_TurnCnt < numberOfLoops)
  /* CHECK: PARSE */
  {
     const uint32 keyExpdFastLoopOffset = Cry_AES_TurnCnt * 8U;
     index = (uint8)Cry_AES_TurnCnt;
#endif

    t0 =                       Cry_AES_Te0[(s0 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(s1 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(s2 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(s3       ) & 0xFFU])) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 4U];
    t1 =                       Cry_AES_Te0[(s1 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(s2 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(s3 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(s0       ) & 0xFFU])) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 5U];
    t2 =                       Cry_AES_Te0[(s2 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(s3 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(s0 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(s1       ) & 0xFFU])) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 6U];
    t3 =                       Cry_AES_Te0[(s3 >> 24U) & 0xFFU]   ^
         (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(s0 >> 16U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(s1 >>  8U) & 0xFFU])) ^
         (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(s2       ) & 0xFFU])) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 7U];

    /* The last turn does not use the MixColumn layer */
    if (index < (numberOfLoops - 1U))
    {
      s0 =                       Cry_AES_Te0[(t0 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(t1 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(t2 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(t3       ) & 0xFFU])) ^
           Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset +  8U];
      s1 =                       Cry_AES_Te0[(t1 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(t2 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(t3 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(t0       ) & 0xFFU])) ^
           Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset +  9U];
      s2 =                       Cry_AES_Te0[(t2 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(t3 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(t0 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(t1       ) & 0xFFU])) ^
           Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 10U];
      s3 =                       Cry_AES_Te0[(t3 >> 24U) & 0xFFU]   ^
           (CRY_AES_COMMON_ROTL3(Cry_AES_Te0[(t0 >> 16U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL2(Cry_AES_Te0[(t1 >>  8U) & 0xFFU])) ^
           (CRY_AES_COMMON_ROTL1(Cry_AES_Te0[(t2       ) & 0xFFU])) ^
           Cry_AES_EncryptContext.keyExpdFast[keyExpdFastLoopOffset + 11U];
    }
  }

#if ( PZ1A_CRY_OPTIM_AES_ENCRY_EANABLED == STD_ON )
  if ((uint8)Cry_AES_TurnCnt == (numberOfLoops - 1))
#endif
  {
    /* Final turn */
    s0 = ((uint32)((uint32)Cry_AES_SboxNrm[(t0 >> 24U) & 0xFFU] << 24U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t1 >> 16U) & 0xFFU] << 16U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t2 >>  8U) & 0xFFU] <<  8U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t3       ) & 0xFFU]       )) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastOffset + 0U];
    s1 = ((uint32)((uint32)Cry_AES_SboxNrm[(t1 >> 24U) & 0xFFU] << 24U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t2 >> 16U) & 0xFFU] << 16U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t3 >>  8U) & 0xFFU] <<  8U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t0       ) & 0xFFU]       )) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastOffset + 1U];
    s2 = ((uint32)((uint32)Cry_AES_SboxNrm[(t2 >> 24U) & 0xFFU] << 24U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t3 >> 16U) & 0xFFU] << 16U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t0 >>  8U) & 0xFFU] <<  8U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t1       ) & 0xFFU]       )) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastOffset + 2U];
    s3 = ((uint32)((uint32)Cry_AES_SboxNrm[(t3 >> 24U) & 0xFFU] << 24U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t0 >> 16U) & 0xFFU] << 16U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t1 >>  8U) & 0xFFU] <<  8U)  ^
                  ((uint32)Cry_AES_SboxNrm[(t2       ) & 0xFFU]       )) ^
         Cry_AES_EncryptContext.keyExpdFast[keyExpdFastOffset + 3U];
  }

  /* Computation is finished, unmap the state to the byte array */
  Cry_AES_CommonUnmapState(&s0, &s1, &s2, &s3, &Cry_AES_EncryptContext);
}
#endif /* #if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) #else */

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_AES_ENCRYPT_ENABLED == STD_ON) */

typedef uint8 Cry_AES_Encrypt_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_AES_ENCRYPT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
