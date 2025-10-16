/* --------{ EB Automotive C Source File }-------- */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast should not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the the original type.
 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_LN.h>
#include <Cry_CommonConfig.h>
#include <Cry_Common.h>
#include <Cry_ExtractRsaPublicKeyConfig.h>
#include <Cry_ExtractRsaPublicKey.h>

#if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/** \brief  RSA public key extraction implementation state machine states.
 **/
typedef enum
{
  CRY_RSA_PUB_STATE_IDLE,
  CRY_RSA_PUB_STATE_START,
  CRY_RSA_PUB_STATE_INITIALIZED,
  CRY_RSA_PUB_STATE_UPDATE,
  CRY_RSA_PUB_STATE_FINISH
}
Cry_ExtractRsaPubKeyStateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief  RSA public key extraction implementation context structure.
 **/
typedef struct
{
  uint32                                               iputDataLength;
  uint32                                               keyBufFillLevel;
  uint32                                               keyLen;
  P2VAR(Csm_AsymPublicKeyType, TYPEDEF, CRY_APPL_DATA) oputDataPtr;
  P2VAR(uint8,                 TYPEDEF, CRY_APPL_DATA) iputDataPtr;
  Cry_ExtractRsaPubKeyStateType                        ctxState;
  Csm_ReturnType                                       ctxError;
  uint8                                                keyBuf[CRY_RSAPUBKEY_NUM_LEN_BYTES * 2U];
}
Cry_ExtractRsaPubKeyContextType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  The context variable which is used to store the internal state of the RSA Public key
 **         extraction computation.
 **/
STATIC VAR(Cry_ExtractRsaPubKeyContextType, CRY_VAR) Cry_ExtractRsaPublicKeyContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractRsaPublicKeyStart]---------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0152,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cry_ExtractRsaPubKeyConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr = (P2CONST(Cry_ExtractRsaPubKeyConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* context state administration */
  Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_START;

  /* initializations */
  Cry_ExtractRsaPublicKeyContext.keyBufFillLevel = 0U;

  /* get argument parameters into context */
  Cry_ExtractRsaPublicKeyContext.keyLen = locCfgPtr->KeyLength;

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractRsaPublicKeyContext.ctxError = CSM_E_OK;

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractRsaPublicKeyUpdate]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0153,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  VAR(uint32,    AUTOMATIC               ) dataLength
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Csm_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( Cry_ExtractRsaPublicKeyContext.ctxState == CRY_RSA_PUB_STATE_INITIALIZED )
  {
    /* check input arguments */
    if (dataLength >
        ((Cry_ExtractRsaPublicKeyContext.keyLen*2) - Cry_ExtractRsaPublicKeyContext.keyBufFillLevel)
       )
    {
      locRetVal = CSM_E_SMALL_BUFFER;
    }
    else
    {
    /* if input arguments are ok edit context */

      /* get argument parameters into context */
      Cry_CommonCopy(
          &Cry_ExtractRsaPublicKeyContext.keyBuf[Cry_ExtractRsaPublicKeyContext.keyBufFillLevel],
          dataPtr,
          dataLength
      );
      Cry_ExtractRsaPublicKeyContext.keyBufFillLevel += dataLength;

      /* context state administration */
      Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_UPDATE;

      locRetVal = CSM_E_OK;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractRsaPublicKeyContext.ctxError = locRetVal;
  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractRsaPublicKeyFinish]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0154,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractRsaPublicKeyFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(Csm_ReturnType, AUTOMATIC) locRetVal;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( Cry_ExtractRsaPublicKeyContext.ctxState == CRY_RSA_PUB_STATE_INITIALIZED )
  {
    /* get argument parameters into context */
    Cry_ExtractRsaPublicKeyContext.oputDataPtr = keyPtr;

    locRetVal = CSM_E_OK;

    /* context state administration */
    Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_FINISH;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractRsaPublicKeyContext.ctxError = locRetVal;
  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractRsaPublicKeyMainFunction]--------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0155,1 */
FUNC(void, CRY_CODE) Cry_ExtractRsaPublicKeyMainFunction
(
    void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  VAR(uint32,         AUTOMATIC) locLoop;
  VAR(Std_ReturnType, CRY_VAR  ) StdRet = E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_ExtractRsaPublicKeyContext.ctxState )
  {
    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_RSA_PUB_STATE_IDLE **************** */
    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_RSA_PUB_STATE_INITIALIZED ****************** */
    case CRY_RSA_PUB_STATE_IDLE:
    case CRY_RSA_PUB_STATE_INITIALIZED:
    break;

    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_RSA_PUB_STATE_START ************************ */
    case CRY_RSA_PUB_STATE_START:
    {
      /* init local data buffer */
      for ( locLoop = 0U; locLoop < sizeof(Cry_ExtractRsaPublicKeyContext.keyBuf); locLoop++ )
      {
        Cry_ExtractRsaPublicKeyContext.keyBuf[locLoop] = 0U;
      }

      /* context state administration */
      Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_INITIALIZED;

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractRsaPublicKeyContext.ctxError);

    }
    break;

    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_RSA_PUB_STATE_UPDATE *********************** */
    case CRY_RSA_PUB_STATE_UPDATE:
    {

      /* context state administration */
      Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_INITIALIZED;

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractRsaPublicKeyContext.ctxError);

    }
    break;

    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_RSA_PUB_STATE_FINISH *********************** */
    case CRY_RSA_PUB_STATE_FINISH:
    {
      /* Deviation MISRAC2012-1 */
      P2VAR(Cry_RsaPublicKeyType, AUTOMATIC, CRY_APPL_DATA) RsaPublicKeyPtr =
          (P2VAR(Cry_RsaPublicKeyType, AUTOMATIC, CRY_APPL_DATA))
          Cry_ExtractRsaPublicKeyContext.oputDataPtr;
      if  (Cry_ExtractRsaPublicKeyContext.keyBufFillLevel > Cry_ExtractRsaPublicKeyContext.keyLen)
      {
        /* copy to oput variables */
        /* transform the input data bytes -> words */
        StdRet = Cry_LNBEByteArrayToNumber
        (
          Cry_ExtractRsaPublicKeyContext.keyBuf,
          Cry_ExtractRsaPublicKeyContext.keyLen,
          RsaPublicKeyPtr->Modulus,
          CRY_RSAPUBKEY_NUM_LEN_WORDS
        );
      }

      if (E_OK == StdRet )
      {
        StdRet = Cry_LNBEByteArrayToNumber
        (
          &Cry_ExtractRsaPublicKeyContext.keyBuf[Cry_ExtractRsaPublicKeyContext.keyLen],
          (Cry_ExtractRsaPublicKeyContext.keyBufFillLevel - Cry_ExtractRsaPublicKeyContext.keyLen),
          RsaPublicKeyPtr->PublicExponent,
          CRY_RSAPUBKEY_NUM_LEN_WORDS
        );
      }

      if (E_OK != StdRet)
      {
        Cry_ExtractRsaPublicKeyContext.ctxError = CSM_E_NOT_OK;
      }

      /* context state administration */
      Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_IDLE;

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractRsaPublicKeyContext.ctxError);
      Csm_AsymPublicKeyExtractServiceFinishNotification();
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. */

    /* *** Cry_ExtractRsaPublicKeyMainFunction > DEFAULT **************************************** */
    default:
    {
      /* context state administration */
      Cry_ExtractRsaPublicKeyContext.ctxState = CRY_RSA_PUB_STATE_IDLE;

      Cry_ExtractRsaPublicKeyContext.ctxError = 0xFFU;
    }
    break;

    /* CHECK: PARSE */
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/

#endif /* #if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE) */

/*==================[end of file]=================================================================*/
