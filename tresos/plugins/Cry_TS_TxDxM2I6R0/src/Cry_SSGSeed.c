/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_RandomSeed.h>
#include <Csm.h>
#include <Cry_SSGSeed.h>     /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_SSGSEED_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/** \enum  Cry_SSGSeedStateMachineType
 ** \brief Enumeration of the internal states of the SSG computation
 **
 ** \var Cry_SSGSeedStateMachineType::CRY_SSG_S_IDLE
 ** \brief The algorithm is in the idle state
 **
 ** \var Cry_SSGSeedStateMachineType::CRY_SSG_S_SEED_INITIALIZED
 ** \brief Seeding has been initialized
 **
 ** \var Cry_SSGSeedStateMachineType::CRY_SSG_S_SEED_START
 ** \brief Start of seeding is in progress
 **
 ** \var Cry_SSGSeedStateMachineType::CRY_SSG_S_SEED_UPDATE
 ** \brief Update of seeding is in process
 **
 ** \var Cry_SSGSeedStateMachineType::CRY_SSG_S_SEED_FINISH
 ** \brief Finishing of seeding is in process
 **
 **/
typedef enum
{
  CRY_SSG_S_IDLE,
  CRY_SSG_S_SEED_INITIALIZED,
  CRY_SSG_S_SEED_START,
  CRY_SSG_S_SEED_UPDATE,
  CRY_SSG_S_SEED_FINISH
}
Cry_SSGSeedStateMachineType;

/**
 ** \struct Cry_SSGGenerateConfigType
 ** \brief Structure which contains the context of the SSG algorithm
 **
 **
 ** \var Cry_SSGGenerateConfigType::ResultLength
 ** \brief The amount of bytes which should be written into the result
 ** buffer
 **
 ** \var Cry_SSGGenerateConfigType::SeedLength
 ** \brief The length of the seed
 **
 ** \var Cry_SSGGenerateConfigType::CfgPtr
 ** \brief A pointer to the current SHA2 configuration which has to be used
 **
 ** \var Cry_SSGGenerateConfigType::Result
 ** \brief A pointer to the start of a buffer where the created pseudo random
 ** bytes should be stored
 **
 ** \var Cry_SSGGenerateConfigType::Seed
 ** \brief A pointer to the start of an array where the seed is stored
 **
 ** \var Cry_SSGGenerateConfigType::State
 ** \brief IThe current state the SSG is in
 **
 **/
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
          uint32                                               ResultLength;
          uint32                                               SeedLength;
  P2CONST(Cry_SSGSeedConfigType,      TYPEDEF, CRY_APPL_DATA ) CfgPtr;
    P2VAR(uint8,                      TYPEDEF, CRY_APPL_DATA ) Result;
  P2CONST(uint8,                      TYPEDEF, CRY_APPL_DATA ) Seed;
          Cry_SSGSeedStateMachineType                          State;
}
Cry_SSGSeedCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief SSG Ctx
 **
 **  The context variable which is used to store the internal state of the
 **  self shrinking generator
 **
 **/
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_SSGSeedCtxType, CRY_VAR) Cry_SSGSeedCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0057,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SSGSeedStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SSGSEED_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_SSG_S_IDLE == Cry_SSGSeedCtx.State)
  {
    Cry_SSGSeedCtx.CfgPtr = (P2CONST(Cry_SSGSeedConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
    Cry_SSGSeedCtx.State  = CRY_SSG_S_SEED_START;
    RetVal                = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  Cry_SSGSeedCtx.CfgPtr = (P2CONST(Cry_SSGSeedConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;
  Cry_SSGSeedCtx.State  = CRY_SSG_S_SEED_START;
  RetVal                = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0058,1 */

FUNC(Csm_ReturnType, CRY_CODE) Cry_SSGSeedUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) seedPtr,
          uint32                           seedLength
)
{
  Csm_ReturnType RetVal;

  if(CRY_SSG_S_IDLE == Cry_SSGSeedCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SSG_S_SEED_INITIALIZED == Cry_SSGSeedCtx.State)
  {
    Cry_SSGSeedCtx.Seed = seedPtr;
    Cry_SSGSeedCtx.SeedLength = seedLength;

    Cry_SSGSeedCtx.State = CRY_SSG_S_SEED_UPDATE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0059,1 */
FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_SSGSeedFinish
(
  void
)
{
  Csm_ReturnType RetVal;

  if(CRY_SSG_S_IDLE == Cry_SSGSeedCtx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SSG_S_SEED_INITIALIZED == Cry_SSGSeedCtx.State)
  {
    Cry_SSGSeedCtx.State = CRY_SSG_S_SEED_FINISH;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0060,1 */
FUNC(void, CRY_CODE) Cry_SSGSeedMainFunction
(
  void
)
{
  uint32 Temp;

  switch(Cry_SSGSeedCtx.State)
  {
    case CRY_SSG_S_SEED_START:
      for(Temp = 0U; Temp < Cry_SSGSeedCtx.CfgPtr->LfsrLen; Temp++)
      {
        Cry_SSGSeedCtx.CfgPtr->LfsrState[Temp] = 0U;
      }

      Cry_SSGSeedCtx.State = CRY_SSG_S_SEED_INITIALIZED;
      /* !LINKSTO CSM0454, 1*/
      Csm_RandomSeedCallbackNotification(CSM_E_OK);
      break;

    case CRY_SSG_S_SEED_UPDATE:
      Temp = Cry_SSGSeedCtx.SeedLength;

      while(Temp > Cry_SSGSeedCtx.CfgPtr->LfsrLen)
      {
        Cry_CommonXOR
        (
          Cry_SSGSeedCtx.CfgPtr->LfsrState,
          &Cry_SSGSeedCtx.Seed[Cry_SSGSeedCtx.SeedLength - Temp],
          Cry_SSGSeedCtx.CfgPtr->LfsrLen
        );

        Temp -= Cry_SSGSeedCtx.CfgPtr->LfsrLen;
      }

      Cry_CommonXOR
      (
        Cry_SSGSeedCtx.CfgPtr->LfsrState,
        &Cry_SSGSeedCtx.Seed[Cry_SSGSeedCtx.SeedLength - Temp],
        Temp
      );

      Cry_SSGSeedCtx.State = CRY_SSG_S_SEED_INITIALIZED;
      /* !LINKSTO CSM0454, 1
      */
      Csm_RandomSeedCallbackNotification(CSM_E_OK);
      break;

    case CRY_SSG_S_SEED_FINISH:
      Cry_SSGSeedCtx.State = CRY_SSG_S_IDLE;

      Csm_RandomSeedCallbackNotification(CSM_E_OK);

      Csm_RandomSeedServiceFinishNotification();
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

#else /* #if (CRY_SSG_ENABLED == STD_ON) */

typedef uint8 Cry_SSGSeed_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SSG_ENABLED == STD_ON) #else */
