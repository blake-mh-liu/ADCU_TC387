/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_RandomGenerate.h>
#include <Csm.h>
#include <Cry_SSGGenerate.h>     /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_SSGGENERATE_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (defined CRY_SSG_PRIM_POLY)
#error CRY_SSG_PRIM_POLY is already defined
#endif
/** \brief An array initializer which describes the primitive polynomial over
     GF_2^160 for the generator. Size of the polynomial will be the size of the
     state.
 **
 **/
#define CRY_SSG_PRIM_POLY  \
  0xB7U, 0x36U, 0xA6U, 0xEBU, 0x4AU, 0x68U, 0x19U, 0xF6U, 0x49U, 0xC7U, \
  0x9FU, 0x91U, 0x79U, 0xF3U, 0xB0U, 0x81U, 0x6CU, 0x8EU, 0x95U, 0x67U

/*==[Types]===================================================================*/

 /** \enum  Cry_SSGStateMachineType
  ** \brief Enumeration of the internal states of the SSG computation
  **
  ** \var Cry_SSGStateMachineType::CRY_SSG_S_IDLE
  ** \brief The algorithm is in the idle state
  **
  ** \var Cry_SSGStateMachineType::CRY_SSG_S_GENERATE
  ** \brief Generation of pseudo-random bytes is in progress
  **
  **/
typedef enum
{
  CRY_SSG_S_IDLE,
  CRY_SSG_S_GENERATE
}
Cry_SSGStateMachineType;

/** \struct Cry_SSGCtxType
 ** \brief  Structure which contains the context of the SSG algorithm
 **
 ** \var Cry_SSGCtxType::ResultLength
 ** \brief  The amount of bytes which should be written into the result buffer
 **
 ** \var Cry_SSGCtxType::SeedLength
 ** \brief The length of the seed.
 **
 ** \var Cry_SSGCtxType::CfgPtr
 ** \brief Pointer to the current SSG configuration which has to be used
 **
 ** \var Cry_SSGCtxType::Result
 ** \brief A pointer to the start of a buffer where the created pseudo random
 ** bytes should be stored
 **
 ** \var Cry_SSGCtxType::Seed
 ** \brief A pointer to the start of an array where the seed is stored
 ** finishes
 **
 ** \var Cry_SSGCtxType::State
 ** \brief The current state the SSG is in
 **/
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
          uint32                                              ResultLength;
          uint32                                              SeedLength;
  P2CONST(Cry_SSGGenerateConfigType, TYPEDEF, CRY_APPL_DATA)  CfgPtr;
    P2VAR(uint8,                     TYPEDEF, CRY_APPL_DATA)  Result;
  P2CONST(uint8,                     TYPEDEF, CRY_APPL_DATA)  Seed;
          Cry_SSGStateMachineType                             State;
}
Cry_SSGCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>
/**
 ** \brief This function performs as many rounds of the self shrinking generator as are
 ** needed to get a single pseudo random byte.
 **/
static FUNC(uint8, CRY_CODE) Cry_SSGGetByte(void);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief Primitive polynomial
 **
 ** The primitive polynomial used in the linear feedback shift register of the
 ** self shrinking generator
 **/
static CONST(uint8, CRY_CONST) Cry_SSGPrimPoly[] =
{
  CRY_SSG_PRIM_POLY
};

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief SSG Ctx
 **
 ** The context variable which is used to store the internal state of the
 ** self shrinking generator.
 **/
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_SSGCtxType, CRY_VAR) Cry_SSGCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>
/* !LINKSTO EB_CRY_0014,1, CS_SECURE_CRY_0061,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SSGGenerate
(
  P2CONST(void,  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) resultPtr,
          uint32                           resultLength
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_SSG_S_IDLE == Cry_SSGCtx.State)
  {
    Cry_SSGCtx.CfgPtr = (P2CONST(Cry_SSGGenerateConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    /* Store result buffer into context */
    Cry_SSGCtx.Result       = resultPtr;
    Cry_SSGCtx.ResultLength = resultLength;
    Cry_SSGCtx.State        = CRY_SSG_S_GENERATE;
    RetVal                  = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  Cry_SSGCtx.CfgPtr = (P2CONST(Cry_SSGGenerateConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

  /* Store result buffer into context */
  Cry_SSGCtx.Result       = resultPtr;
  Cry_SSGCtx.ResultLength = resultLength;
  Cry_SSGCtx.State        = CRY_SSG_S_GENERATE;
  RetVal                  = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0062,1 */
FUNC(void, CRY_CODE) Cry_SSGGenerateMainFunction
(
  void
)
{
  uint32 Temp;
  Csm_ReturnType ErrorCode = CSM_E_ENTROPY_EXHAUSTION;

  switch(Cry_SSGCtx.State)
  {
    case CRY_SSG_S_GENERATE:

      for(Temp = 0U; Temp < Cry_SSGCtx.CfgPtr->LfsrLen; Temp++)
      {
        if(Cry_SSGCtx.CfgPtr->LfsrState[Temp] != 0U)
        {
          ErrorCode = CSM_E_OK;
        }
      }

      if(ErrorCode != CSM_E_ENTROPY_EXHAUSTION)
      {
        for(Temp = 0U; Temp < Cry_SSGCtx.ResultLength; Temp++)
        {
          /* generate each byte individually */
          Cry_SSGCtx.Result[Temp] = Cry_SSGGetByte();
        }
      }

      Cry_SSGCtx.State = CRY_SSG_S_IDLE;

      /* !LINKSTO CSM0454, 1
      */
      Csm_RandomGenerateCallbackNotification(ErrorCode);
      Csm_RandomGenerateServiceFinishNotification();

      break;

    default:
    {
     break;
    }
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(uint8, CRY_CODE) Cry_SSGGetByte(void)
{
  uint8 RetByte;       /* the byte to return */
  uint8 BitCount;      /* the bit we just generate */
  uint8 k;       /* temporary word counter */
  boolean IsCheckBit;
  uint8 MustOutput;
  uint8 CurrentBit;

  IsCheckBit = TRUE;
  MustOutput = (uint8)0U;

  /* set return byte to zero and just set the '1' below */
  RetByte = (uint8)0U;

  /* loop over all eight bits of the byte */
  BitCount = (uint8)8U;
  do
  {
    CurrentBit = Cry_SSGCtx.CfgPtr->LfsrState[Cry_SSGCtx.CfgPtr->LfsrLen - 1U] & 1U;

    if(TRUE == IsCheckBit)
    {
      MustOutput = CurrentBit;

      IsCheckBit = FALSE;
    }
    else
    {
      if (MustOutput != 0U)
      {
        --BitCount;

        RetByte |= (uint8)(CurrentBit << BitCount);
      }

      IsCheckBit = TRUE;
    }

    k = Cry_SSGCtx.CfgPtr->LfsrLen - 1U;
    do
    {
      /* we only xor the state with the poly if the OutBit is != 0 */
      if (CurrentBit != 0U)
      {
        /* xor state and poly */
        Cry_SSGCtx.CfgPtr->LfsrState[k] ^= Cry_SSGPrimPoly[k];
      }

      /* right shift by one */
      Cry_SSGCtx.CfgPtr->LfsrState[k] >>= 1U;

      /* test lowest bit of previous word to look for a carry */
      if ((Cry_SSGCtx.CfgPtr->LfsrState[k - 1U] & 1U) != 0U)
      {
        /* set the highest bit */
        Cry_SSGCtx.CfgPtr->LfsrState[k] |= (uint8)0x80U;
      }

      /* go to next word */
      --k;

    } /* until all but the last word finished */
    while (k != 0U);

    /* the last word is the feedback word */
    if (CurrentBit != 0U)
    {
      /* xor with polynomial */
      Cry_SSGCtx.CfgPtr->LfsrState[0U] ^= Cry_SSGPrimPoly[0U];

      /* shift 0th word */
      Cry_SSGCtx.CfgPtr->LfsrState[0U] >>= 1U;
      /* this is the place to look for smaller polynomials!! */
      /* and feed back */
      Cry_SSGCtx.CfgPtr->LfsrState[0U] |= 0x80U;
    }
    else
    {
      /* the output bit was a zero, no feedback then */
      /* just shift the 0th word */
      Cry_SSGCtx.CfgPtr->LfsrState[0U] >>= 1U;
    }
  } /* until all bits are done */
  while (BitCount != (uint8)0U);

  return RetByte;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_SSG_ENABLED == STD_ON) */

typedef uint8 Cry_SSGGenerate_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SSG_ENABLED == STD_ON) #else */
