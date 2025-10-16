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
 *
 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_ExtractECPubKeyConfig.h>
#include <Cry_ExtractECPubKey.h>

#include <Cry_Common.h>
#include <Cry_LN.h>

#if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  The context variable which is used to store the internal state of the
 **         ExtractPubKey extract computation.
**/
static VAR(Cry_ExtractECPubKeyCtxType, CRY_VAR) Cry_ExtractECPubKeyContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractECPubKeyStart]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_0187,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cry_ExtractECPubKeyCfgType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
  Csm_ReturnType                                                locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr = (P2CONST(Cry_ExtractECPubKeyCfgType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ((CRY_EXTRACT_ECPUBKEY_STATE_ERROR == Cry_ExtractECPubKeyContext.ctxState) ||
      (CRY_EXTRACT_ECPUBKEY_STATE_IDLE == Cry_ExtractECPubKeyContext.ctxState)
     )
  {
    /* check input arguments */
    if (locCfgPtr->keyType != CRY_EDC_255)
    {
      locRetVal = CSM_E_NOT_OK;
    }
    else
    {
      /* if input arguments are ok edit context */
      /* context state administration */
      Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_START;

      /* initializations */
      Cry_ExtractECPubKeyContext.keyLvl = 0U;

      /* get argument parameters into context */
      Cry_ExtractECPubKeyContext.keyLen = (uint32)locCfgPtr->keyBytesLength;

      locRetVal = CSM_E_OK;
    }
  }
  else if (CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED == Cry_ExtractECPubKeyContext.ctxState)
  {
    locRetVal = CSM_E_NOT_OK;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractECPubKeyContext.ctxError = locRetVal;

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractECPubKeyUpdate]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CS_SECURE_CRY_0188,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                    dataLength
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch (Cry_ExtractECPubKeyContext.ctxState)
  {
    case CRY_EXTRACT_ECPUBKEY_STATE_IDLE:
      locRetVal = CSM_E_NOT_OK;
      break;

    case CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED:
      {
        if (((0U == dataLength) || ((NULL_PTR != dataPtr) && (0U != dataLength))) &&
            ((sizeof(Cry_ExtractECPubKeyContext.keyBuf)>=Cry_ExtractECPubKeyContext.keyLen) &&
             ((Cry_ExtractECPubKeyContext.keyLen-Cry_ExtractECPubKeyContext.keyLvl) >= dataLength)))
        {
          /* get argument parameters into context */
          Cry_CommonCopy(
            &Cry_ExtractECPubKeyContext.keyBuf[Cry_ExtractECPubKeyContext.keyLvl],
            dataPtr,
            dataLength
          );
          Cry_ExtractECPubKeyContext.keyLvl += dataLength;

          /* context state administration */
          Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_UPDATE;

          locRetVal = CSM_E_OK;
        }
        else if((sizeof(Cry_ExtractECPubKeyContext.keyBuf)<Cry_ExtractECPubKeyContext.keyLen) ||
                ((Cry_ExtractECPubKeyContext.keyLen-Cry_ExtractECPubKeyContext.keyLvl) < dataLength)
               )
        {
          Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_ERROR;
          locRetVal = CSM_E_SMALL_BUFFER;
        }
        else
        {
          locRetVal = CSM_E_NOT_OK;
        }
      }
      break;

    default:
      {
        locRetVal = CSM_E_BUSY;
        break;
      }
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractECPubKeyContext.ctxError = locRetVal;
  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractECPubKeyFinish]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CS_SECURE_CRY_0189,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_ExtractECPubKeyFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType locRetVal;
  uint32         outSize;
  uint32         locSize;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch (Cry_ExtractECPubKeyContext.ctxState)
  {
    case CRY_EXTRACT_ECPUBKEY_STATE_IDLE:
      locRetVal = CSM_E_NOT_OK;
      break;

    case CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED:
      {
        /* get argument parameters into context */
        /* Deviation MISRAC2012-1 */
        Cry_ExtractECPubKeyContext.oputDataPtr =
          (P2VAR(Cry_ECKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;

        /* context state administration */
        Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_FINISH;
        locRetVal = CSM_E_OK;

        outSize = sizeof(*keyPtr);
        locSize = sizeof(uint32) + Cry_ExtractECPubKeyContext.keyLen;
        /* CHECK: NOPARSE */
        /* At this poit there is implemented only an elliptic curve primitive which is smaller
         * than the Csm_AsymPublicKeyType which can be 514bytes or 1028bytes long
         */
        if (outSize<locSize)
        {
          /* context state administration */
          Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_ERROR;
          locRetVal = CSM_E_SMALL_BUFFER;
        }
        /* CHECK: PARSE */
      }
      break;

    case CRY_EXTRACT_ECPUBKEY_STATE_ERROR:
      locRetVal = CSM_E_OK;
      break;

    default:
      {
        locRetVal = CSM_E_BUSY;
        break;
      }
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cry_ExtractECPubKeyContext.ctxError = locRetVal;
  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_ExtractECPubKeyMainFunction]------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/* !LINKSTO CS_SECURE_CRY_0190,1 */
FUNC(void, CRY_CODE) Cry_ExtractECPubKeyMainFunction
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Std_ReturnType locRetVal;
  uint32         locLoop;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_ExtractECPubKeyContext.ctxState )
  {
    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_IDLE **********************/
    case CRY_EXTRACT_ECPUBKEY_STATE_IDLE:
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_START *********************/
    case CRY_EXTRACT_ECPUBKEY_STATE_START:
    {
      /* context state administration */
      Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED;

      /* init local csm conform data buffer */
      for ( locLoop = 0U; locLoop < sizeof(Cry_ExtractECPubKeyContext.keyBuf); locLoop++ )
      {
        Cry_ExtractECPubKeyContext.keyBuf[locLoop] = 0U;
      }

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractECPubKeyContext.ctxError);
    }
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED ***************/
    case CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED:
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_UPDATE ********************/
    case CRY_EXTRACT_ECPUBKEY_STATE_UPDATE:
    {
      if ( Cry_ExtractECPubKeyContext.keyLvl != Cry_ExtractECPubKeyContext.keyLen )
      {
        /* context state administration */
        Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_INITIALIZED;
      }
      else
      {
        /* context state administration */
        Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED;
      }

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractECPubKeyContext.ctxError);
    }
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED ****************/
    case CRY_EXTRACT_ECPUBKEY_STATE_CALCULATED:
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_FINISH ********************/
    case CRY_EXTRACT_ECPUBKEY_STATE_FINISH:
    {
      /* copy to oput variables
       */

      locRetVal = Cry_LNBEByteArrayToNumber
      (
        Cry_ExtractECPubKeyContext.keyBuf,
        (Cry_ExtractECPubKeyContext.keyLvl),
        Cry_ExtractECPubKeyContext.oputDataPtr->Q.xValue,
        CRY_ECPUBKEY_TEMP_LEN_WORDS
      );

      /* CRY_ECPUBKEY_TEMP_LEN_WORDS is computed acording to the maximum byte length
       * of the elliptic curve primitives used in the configuration and also the
       * maximum Cry_ExtractECPubKeyContext.keyLvl is restricted acording to
       * the elliptic curve primitive selected in the configuration.
       */
      /* CHECK: NOPARSE */
      if(E_OK != locRetVal)
      {
        Cry_ExtractECPubKeyContext.ctxError = CSM_E_NOT_OK;
      }
      /* CHECK: PARSE */

      /* context state administration */
      Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_IDLE;

      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(Cry_ExtractECPubKeyContext.ctxError);
      Csm_AsymPublicKeyExtractServiceFinishNotification();
    }
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > CRY_EXTRACT_ECPUBKEY_STATE_ERROR *********************/
    case CRY_EXTRACT_ECPUBKEY_STATE_ERROR:
    break;

    /* *** Cry_ExtractECPubKeyMainFunction > DEFAULT **************************************** */
    /* CHECK: NOPARSE */
    /* Caution: this 'default' is required by MISRA-C:2004 */
    default:
    {
      /* context state administration */
      Cry_ExtractECPubKeyContext.ctxState = CRY_EXTRACT_ECPUBKEY_STATE_ERROR;

      Cry_ExtractECPubKeyContext.ctxError = CSM_E_NOT_OK;
    }
    break;
    /* CHECK: PARSE */
  }
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) */

typedef uint8 Cry_ExtractECPubKey_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/
