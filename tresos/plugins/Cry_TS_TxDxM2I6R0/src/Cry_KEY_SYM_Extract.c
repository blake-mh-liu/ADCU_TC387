/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_KEY_SYM_ExtractConfig.h>
#include <Cry_KEY_SYM_Extract.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_Common.h>

#if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/** \brief  KEY_SYM extract implementation state machine states.
 **/
typedef enum
{
  CRY_KEY_SYM_STATE_UNINITIALIZED,
  CRY_KEY_SYM_STATE_START,
  CRY_KEY_SYM_STATE_INITIALIZED,
  CRY_KEY_SYM_STATE_UPDATE,
  CRY_KEY_SYM_STATE_CALCULATING,
  CRY_KEY_SYM_STATE_CALCULATED,
  CRY_KEY_SYM_STATE_FINISH
}
Cry_KEY_SYM_StateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief  KEY_SYM extract implementation context structure.
 **/
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
      uint32                                  iputDataLength;
      uint32                                  keyLvl;
      uint32                                  keyLen;
P2VAR(Csm_SymKeyType, TYPEDEF, CRY_APPL_DATA) oputDataPtr;
P2VAR(uint8,          TYPEDEF, CRY_APPL_DATA) iputDataPtr;
      uint8                                   keyBuf[CRY_KEY_BUFLEN];
      Cry_KEY_SYM_StateType                   ctxState;
}
Cry_KEY_SYM_ContextType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  The context variable which is used to store the internal state of the KEY_SYM extract
 **         computation.
**/
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_KEY_SYM_ContextType, CRY_VAR) Cry_KEY_SYM_ExtractContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0063,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cry_KEY_SYM_ConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
          Csm_ReturnType                                    locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr = (P2CONST(Cry_KEY_SYM_ConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;
  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if ( Cry_KEY_SYM_ExtractContext.ctxState == CRY_KEY_SYM_STATE_UNINITIALIZED )
  {
    /* !LINKSTO EB_Cry_KEY_SYM_Extract_BufferSize,1 */
    /* if the data in Csm_SymKeyType is smaller than the key size return CSM_E_NOT_OK */
    if (locCfgPtr->typeKey > (Cry_KEY_SYM_Type)(sizeof(Csm_SymKeyType) - sizeof(uint32)))
    {
      locRetVal = CSM_E_NOT_OK;
    }
    else
    {
      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_START;

      /* initializations */
      Cry_KEY_SYM_ExtractContext.keyLvl = 0U;
      Cry_KEY_SYM_ExtractContext.keyLen = 0U;

      /* get argument parameters into context */
      Cry_KEY_SYM_ExtractContext.keyLen = (uint32) locCfgPtr->typeKey;
    }
  }
  else
  {
    locRetVal = CSM_E_NOT_OK;
  }
#else
  /* context state administration */
  Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_START;

  /* initializations */
  Cry_KEY_SYM_ExtractContext.keyLvl = 0U;
  Cry_KEY_SYM_ExtractContext.keyLen = 0U;

  /* get argument parameters into context */
  Cry_KEY_SYM_ExtractContext.keyLen = (uint32) locCfgPtr->typeKey;
#endif

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0064,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
      uint32                                dataLength
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  if ( Cry_KEY_SYM_ExtractContext.ctxState == CRY_KEY_SYM_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_KEY_SYM_ExtractContext.ctxState == CRY_KEY_SYM_STATE_INITIALIZED )
  {
    /* check input arguments */
    if ( dataLength > (Cry_KEY_SYM_ExtractContext.keyLen - Cry_KEY_SYM_ExtractContext.keyLvl) )
    {
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_UNINITIALIZED;
      locRetVal = CSM_E_NOT_OK;
    }
    /* if input arguments are ok edit context */
    if ( locRetVal == CSM_E_OK )
    {
      /* get argument parameters into context */
      Cry_CommonCopy(
          &(Cry_KEY_SYM_ExtractContext.keyBuf[Cry_KEY_SYM_ExtractContext.keyLvl]),
        dataPtr,
        dataLength
      );
      Cry_KEY_SYM_ExtractContext.keyLvl += dataLength;

      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_UPDATE;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }


  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0065,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_KEY_SYM_ExtractFinish
(
  P2VAR(Csm_SymKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  if ( Cry_KEY_SYM_ExtractContext.ctxState == CRY_KEY_SYM_STATE_UNINITIALIZED )
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else if ( Cry_KEY_SYM_ExtractContext.ctxState == CRY_KEY_SYM_STATE_CALCULATED )
  {
    /* get argument parameters into context */
    Cry_KEY_SYM_ExtractContext.oputDataPtr = keyPtr;

    /* context state administration */
    Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_FINISH;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0066,1 */
FUNC(void, CRY_CODE) Cry_KEY_SYM_ExtractMainFunction
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  uint32 locLoop;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_KEY_SYM_ExtractContext.ctxState )
  {
    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_UNINITIALIZED ******************** */
    case CRY_KEY_SYM_STATE_UNINITIALIZED:
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_START **************************** */
    case CRY_KEY_SYM_STATE_START:
    {
      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_INITIALIZED;

      /* init local csm conform data buffer */
      for ( locLoop=0; locLoop<CRY_KEY_BUFLEN; locLoop++ )
      {
        Cry_KEY_SYM_ExtractContext.keyBuf[locLoop] = 0U;
      }

      /* callback */
      Csm_SymKeyExtractCallbackNotification(CSM_E_OK);
    }
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_INITIALIZED ********************** */
    case CRY_KEY_SYM_STATE_INITIALIZED:
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_UPDATE *************************** */
    case CRY_KEY_SYM_STATE_UPDATE:
    {
      if ( Cry_KEY_SYM_ExtractContext.keyLvl != Cry_KEY_SYM_ExtractContext.keyLen )
      {
        /* context state administration */
        Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_INITIALIZED;

        /* callback */
        Csm_SymKeyExtractCallbackNotification(CSM_E_OK);
      }
      else
      {
        /* context state administration */
        Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_CALCULATING;
      }
    }
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_CALCULATING ********************** */
    case CRY_KEY_SYM_STATE_CALCULATING:
    {
      /* do some actions if necessary */

      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_CALCULATED;

      /* callback */
      Csm_SymKeyExtractCallbackNotification(CSM_E_OK);
    }
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_CALCULATED *********************** */
    case CRY_KEY_SYM_STATE_CALCULATED:
    break;

    /* *** Cry_KEY_SYM_ExtractMainFunction > CRY_KEY_SYM_STATE_FINISH *************************** */
    case CRY_KEY_SYM_STATE_FINISH:
    {
      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_UNINITIALIZED;

      /* copy to oput variables */
      Cry_KEY_SYM_ExtractContext.oputDataPtr->length = Cry_KEY_SYM_ExtractContext.keyLen;
      Cry_CommonCopy(
        Cry_KEY_SYM_ExtractContext.oputDataPtr->data,
        Cry_KEY_SYM_ExtractContext.keyBuf,
        Cry_KEY_SYM_ExtractContext.keyLen
      );

      /* callback */
      Csm_SymKeyExtractCallbackNotification(CSM_E_OK);
      Csm_SymKeyExtractServiceFinishNotification();
    }
    break;


    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    /* *** Cry_KEY_SYM_ExtractMainFunction > DEFAULT ******************************************** */
    default:
    {
      /* context state administration */
      Cry_KEY_SYM_ExtractContext.ctxState = CRY_KEY_SYM_STATE_UNINITIALIZED;
      Csm_SymKeyExtractCallbackNotification(CSM_E_NOT_OK);
      Csm_SymKeyExtractServiceFinishNotification();
    }
    break;
    /* CHECK: PARSE */
  }
}

#define CRY_STOP_SEC_CODE

#include <MemMap.h>
/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON) */

/* Dummy type definition to prevent compiler warnings about empty translation units */
typedef uint8 Cry_KEY_SYM_Extract_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
