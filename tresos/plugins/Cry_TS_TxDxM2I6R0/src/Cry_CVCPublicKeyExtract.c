/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0004,1 */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast shall not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the the original type.
 *
 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_Base64.h>                     /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_DerCVC.h>                     /* !LINKSTO EB_CRY_0005,1 */
#include <Csm_SignatureVerify.h>
#include <Cry_CommonConfig.h>
#include <Cry_Common.h>
#include <Cry_LN.h>                         /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_CVCPublicKeyExtract.h>        /* !LINKSTO EB_CRY_0005,1 */
#include <Cry_CVCPublicKeyExtractConfig.h>

/*==[Macros]==================================================================*/

#if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON)

#if (defined MAX)
#error MAX is already defined
#endif
/**
 * \brief Macro for calculating the maximum of two numbers
 */
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/*==[Types]===================================================================*/

/** \brief  CVC public key extraction implementation state machine states.
 **/
typedef enum
{
  CRY_CVC_PUB_STATE_NOT_INITIALIZED,
  CRY_CVC_PUB_STATE_IDLE,
  CRY_CVC_PUB_STATE_START,
  CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN,
  CRY_CVC_PUB_STATE_SIG_EXTRACT,
#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
  CRY_CVC_PUB_STATE_WAITFOR_UPDATE_ROOT,
  CRY_CVC_PUB_STATE_ROOT_EXTRACT,
  CRY_CVC_PUB_STATE_SIG_VERIFY_START,
  CRY_CVC_PUB_STATE_SIG_VERIFY_START_CALLBACK,
  CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE,
  CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE_CALLBACK,
  CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH,
  CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK,
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
  CRY_CVC_PUB_STATE_WAITFOR_FINISH,
  CRY_CVC_PUB_STATE_FINISH
}
Cry_CVCPublicKeyExtractStateType;

/** \brief  CVC public key extraction implementation context structure.
 **/
/* !LINKSTO EB_CRY_0022,1 */
typedef struct
{
  uint32                                                             certLength;
  uint32                                                             signatureLength;
  uint32                                                             signedDataLength;
  P2CONST(Cry_CVCPublicKeyExtractConfigType, TYPEDEF, CRY_APPL_DATA) cfgPtr;
  P2CONST(uint8,                             TYPEDEF, CRY_APPL_DATA) certPtr;
  P2CONST(uint8,                             TYPEDEF, CRY_APPL_DATA) signaturePtr;
  P2CONST(uint8,                             TYPEDEF, CRY_APPL_DATA) signedDataPtr;
   P2VAR(Cry_RsaPublicKeyType,               TYPEDEF, CRY_APPL_DATA) resultKeyPtr;
  uint8        certificate[MAX(CRY_CVCPUBKEY_SIGCERT_LEN_BYTES,CRY_CVCPUBKEY_ROOTCERT_LEN_BYTES)];
  Cry_CVCPublicKeyExtractStateType                                   ctxState;
  Csm_VerifyResultType                                               verificationResult;
  Cry_RsaPublicKeyType                                               rootKeyRsa;
}
Cry_CVCPublicKeyExtractContextType;

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 *
 * \brief State: Extract the signature of the public certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateSigExtract
(
  void
);

#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
/**
 *
 * \brief State: Extract the public key of the root certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateRootExtract
(
  void
);

/**
 *
 * \brief State: Start the signature verification of the public certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyStart
(
  void
);

/**
 *
 * \brief State: Provide the data for the signature verification of the public certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyUpdate
(
  void
);

/**
 *
 * \brief State: Finish the signature verification of the public certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyFinish
(
  void
);
#endif /*#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */

/**
 *
 * \brief State: Return the extracted key from the public key certificate
 *
 * \retval None
 */
static FUNC(void, CRY_CODE) Cry_CVCPubStateFinish
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  Variable for storing the CVC public key extraction implementation context.
 **/
/* !LINKSTO EB_CRY_0024,1 */
static VAR(Cry_CVCPublicKeyExtractContextType, CRY_VAR) Cry_CVCPublicKeyExtractContext =
{
  0x00U,                                     /* certLength */
  0x00U,                                     /* signatureLength */
  0x00U,                                     /* signedDataLength */
  NULL_PTR,                                  /* cfgPtr*/
  NULL_PTR,                                  /* certPtr */
  NULL_PTR,                                  /* signaturePtr */
  NULL_PTR,                                  /* signedDataPtr */
  NULL_PTR,                                  /* resultKeyPtr */
  { 0x00U },                                 /* certificate */
  CRY_CVC_PUB_STATE_NOT_INITIALIZED,         /* ctxState */
  CSM_E_VER_OK,                              /* verificationResult */

#if (CRY_LN_USE_BARRETT == STD_OFF)
  { 0x00U, { 0x00U }, { 0x00U } }            /* rootKeyRsa */
#else
  { 0x00U, { 0x00U }, { 0x00U }, {0x00U } }  /* rootKeyRsa */
#endif
};

#define CRY_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>


#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  Variable for storing Expiration and Effective date from verify (root)
 * certificate
 **/
static VAR(CVDateInfoType, CRY_VAR) Cry_CVCPublicKeyExtractVerifyCVDate;

/** \brief  Variable for storing Expiration and Effective date from key (signing)
 * certificate
 **/
static VAR(CVDateInfoType, CRY_VAR) Cry_CVCPublicKeyExtractKeyCVDate;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0079,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  /* The start funcion can always be called to restart the service */
  Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_START;
  Cry_CVCPublicKeyExtractContext.cfgPtr =
      (P2CONST(Cry_CVCPublicKeyExtractConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;

  return CSM_E_OK;
}

/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0080,2 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
          uint32                            dataLength
)
{
  Csm_ReturnType locRetVal = CSM_E_OK;

  /* context state administration */
#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
  if (Cry_CVCPublicKeyExtractContext.ctxState == CRY_CVC_PUB_STATE_WAITFOR_UPDATE_ROOT)
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_ROOT_EXTRACT;

    Cry_CVCPublicKeyExtractContext.certPtr = dataPtr;
    Cry_CVCPublicKeyExtractContext.certLength = dataLength;
  }
  else if (Cry_CVCPublicKeyExtractContext.ctxState == CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN)
#else
  if (Cry_CVCPublicKeyExtractContext.ctxState == CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN)
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_EXTRACT;

    Cry_CVCPublicKeyExtractContext.certPtr = dataPtr;
    Cry_CVCPublicKeyExtractContext.certLength = dataLength;
  }
#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
  else if ((Cry_CVCPublicKeyExtractContext.ctxState < CRY_CVC_PUB_STATE_START) ||
           (Cry_CVCPublicKeyExtractContext.ctxState > CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK)
          )
#else
  else if ((Cry_CVCPublicKeyExtractContext.ctxState < CRY_CVC_PUB_STATE_START) ||
             (Cry_CVCPublicKeyExtractContext.ctxState > CRY_CVC_PUB_STATE_SIG_EXTRACT)
            )
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
  {
    /* The update function should not be called before the start function was called
     * The same holds for calling the update function after the cry state machine is
     * waiting for a call to the finish function */
    locRetVal = CSM_E_NOT_OK;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0081,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractFinish
(
  P2VAR(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
  Csm_ReturnType locRetVal = CSM_E_OK;

  if (Cry_CVCPublicKeyExtractContext.ctxState == CRY_CVC_PUB_STATE_WAITFOR_FINISH)
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_FINISH;
     /* Deviation MISRAC2012-1 <START> */
    Cry_CVCPublicKeyExtractContext.resultKeyPtr =
        (P2VAR(Cry_RsaPublicKeyType, AUTOMATIC, CRY_APPL_DATA)) keyPtr;
    /* Deviation MISRAC2012-1 <STOP> */
  }
  else if (Cry_CVCPublicKeyExtractContext.ctxState < CRY_CVC_PUB_STATE_WAITFOR_FINISH)
  {
    /* The finish function should not be called before the update function was called
     * twice and finished its processing. */
    locRetVal = CSM_E_NOT_OK;
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  return locRetVal;
}

/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0082,1 */
FUNC(void, CRY_CODE) Cry_CVCPublicKeyExtractMainFunction
(
  void
)
{
  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  switch ( Cry_CVCPublicKeyExtractContext.ctxState )
  {
    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_RSA_PUB_STATE_NOT_INITIALIZED ************* */

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_START ********************** */
    case CRY_CVC_PUB_STATE_START:
    {
#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
      if(TRUE == Cry_CVCPublicKeyExtractContext.cfgPtr->EnableCertChain)
      {
        /* context state administration */
        Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_WAITFOR_UPDATE_ROOT;
      }
      else
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
      {
        /* context state administration */
        /* !LINKSTO CS_SECURE_CRY_0080,2 */
        Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN;
      }
      /* callback */
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_OK);
    }
    break;

#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_WAITFOR_UPDATE_ROOT ******** */
    case CRY_CVC_PUB_STATE_WAITFOR_UPDATE_ROOT:
    break;

    /* *** Cry_ExtractRsaPublicKeyMainFunction > CRY_CVC_PUB_STATE_ROOT_EXTRACT **************** */
    case CRY_CVC_PUB_STATE_ROOT_EXTRACT:
    {
      Cry_CVCPubStateRootExtract();
    }
    break;
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN ******** */
    case CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN:
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_EXTRACT **************** */
    case CRY_CVC_PUB_STATE_SIG_EXTRACT:
    {
      Cry_CVCPubStateSigExtract();
    }
    break;

#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_START *********** */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_START:
    {
      Cry_CVCPubStateSigVerifyStart();
    }
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_START_CALLBACK ** */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_START_CALLBACK:
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE ********** */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE:
    {
      Cry_CVCPubStateSigVerifyUpdate();
    }
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE_CALLBACK * */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE_CALLBACK:
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH ********** */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH:
    {
      Cry_CVCPubStateSigVerifyFinish();
    }
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK * */
    case CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK:
    break;
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_WAITFOR_FINISH ************* */
    case CRY_CVC_PUB_STATE_WAITFOR_FINISH:
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > CRY_CVC_PUB_STATE_FINISH ********************* */
    case CRY_CVC_PUB_STATE_FINISH:
    {
      Cry_CVCPubStateFinish();
    }
    break;

    /* *** Cry_CVCPublicKeyExtractMainFunction > DEFAULT *************************************** */
    /* CHECK: NOPARSE */
    /* not reachable code, defensive programming.
     */
    default:
    {
      break;
    }
    /* CHECK: PARSE */
  }
  return;
}


#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
/** \brief Callback function for called sub-services.
 *
 * Several CSM sub-services are called during the public key extraction and
 * since each service calls a callback function to inform the caller that it
 * has finished, this primitive must provide such a callback. This is that
 * callback function. The name of this function has to be used in the
 * configuration of the callback function of the relevant CSM sub-service.
 *
 * \param[in] Result The result of the called sub-service.
 */
FUNC(Std_ReturnType, CRY_CODE) Cry_CVCPublicKeyExtractCallback
(
  Csm_ReturnType Result
)
{
  switch(Cry_CVCPublicKeyExtractContext.ctxState)
  {
  case CRY_CVC_PUB_STATE_SIG_VERIFY_START_CALLBACK:
    if (Result == CSM_E_OK)
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE;
    }
    else
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

      /* no other return value than CSM_E_NOT_OK makes sense here */
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
      Csm_AsymPublicKeyExtractServiceFinishNotification();
    }
    break;

  case CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE_CALLBACK:
    if (Result == CSM_E_OK)
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH;
    }
    else
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

      /* no other return value than CSM_E_NOT_OK makes sense here */
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
      Csm_AsymPublicKeyExtractServiceFinishNotification();
    }
    break;

  case CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK:
    if (Cry_CVCPublicKeyExtractContext.verificationResult != CSM_E_VER_OK)
    {
      /* !LINKSTO CS_SECURE_CRY_0033,2 */
      Result = CSM_E_NOT_OK;
    }

    if (Result == CSM_E_OK)
    {
      /* !LINKSTO CS_SECURE_CRY_0034,1 */
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_WAITFOR_FINISH;
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_OK);
    }
    else
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

      /* no other return value than CSM_E_NOT_OK makes sense here */
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
      Csm_AsymPublicKeyExtractServiceFinishNotification();
    }
    break;

  default:
    {
      break;
    }
  }

  return ((Result == CSM_E_OK) ? E_OK : E_NOT_OK);
}
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
static FUNC(void, CRY_CODE) Cry_CVCPubStateRootExtract
(
  void
)
{
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) derModulusPtr      = NULL_PTR;
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) derExponentPtr     = NULL_PTR;
   uint32                            derModulusLength   = 0U;
   uint32                            derExponentLength  = 0U;
   uint32                            newRootCertLength;
   Csm_ReturnType                    retVal;

  /* decode the data in Base64 format and write the result directly
   * to rootCertificate */
  newRootCertLength = CRY_CVCPUBKEY_ROOTCERT_LEN_BYTES;
  retVal = Cry_Base64Decode(
    Cry_CVCPublicKeyExtractContext.certPtr,
    Cry_CVCPublicKeyExtractContext.certLength,
    Cry_CVCPublicKeyExtractContext.certificate,
    &newRootCertLength
  );
  Cry_CVCPublicKeyExtractContext.certLength = newRootCertLength;

  /* make sure this certificate is a valid certificate before
   * further processing */
  if (retVal == CSM_E_OK)
  {
    if (Cry_DerCVCCheckCertificate
         (
            Cry_CVCPublicKeyExtractContext.certificate,
            Cry_CVCPublicKeyExtractContext.certLength
         ) != TRUE
       )
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  /* get the root key which consists of an exponent and a modulus and
   * get the Expiration and Effective date from the certificate
   * */
  if (retVal == CSM_E_OK)
  {
    /* !LINKSTO CS_SECURE_CRY_0026,1 */
    Cry_DerCVCGetDate
    (
        Cry_CVCPublicKeyExtractContext.certificate,
        &Cry_CVCPublicKeyExtractVerifyCVDate
    );

    /* !LINKSTO CS_SECURE_CRY_0026,1 */
    derModulusPtr = Cry_DerCVCRSAPubKeyGetModulus
    (
      Cry_CVCPublicKeyExtractContext.certificate,
      &derModulusLength
    );

    /* !LINKSTO CS_SECURE_CRY_0026,1 */
    derExponentPtr = Cry_DerCVCRSAPubKeyGetExponent
    (
      Cry_CVCPublicKeyExtractContext.certificate,
      &derExponentLength
    );
    /* CHECK: NOPARSE */
    /* not reachable code, if the modulus or exponent missing the Cry_DerCVCCheckCertificate
     * will fail
     */
    if ((derModulusPtr == NULL_PTR) || (derExponentPtr == NULL_PTR))
    {
      /* !LINKSTO CS_SECURE_CRY_0027,2 */
      retVal = CSM_E_NOT_OK;
    }
    /* CHECK: PARSE */
  }

  if (retVal == CSM_E_OK)
  {
    /* transform the input data bytes -> words */
    if (Cry_LNBEByteArrayToNumber
        (
          derModulusPtr,
          derModulusLength,
          Cry_CVCPublicKeyExtractContext.rootKeyRsa.Modulus,
          CRY_RSAPUBKEY_NUM_LEN_WORDS
        ) == E_OK)
    {
      retVal = CSM_E_OK;
    }
    else
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  if (retVal == CSM_E_OK)
  {
    /* transform the input data bytes -> words */
    if (Cry_LNBEByteArrayToNumber
    (
      derExponentPtr,
      derExponentLength,
      Cry_CVCPublicKeyExtractContext.rootKeyRsa.PublicExponent,
      CRY_RSAPUBKEY_NUM_LEN_WORDS
    ) == E_OK)
    {
      retVal = CSM_E_OK;
    }
    else
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  if (retVal == CSM_E_OK)
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_WAITFOR_UPDATE_SIGN;
    Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_OK);
  }
  else
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

    /* always return CSM_E_NOT_OK because other return values make no sense here */
    Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
    Csm_AsymPublicKeyExtractServiceFinishNotification();
  }
}
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */


static FUNC(void, CRY_CODE) Cry_CVCPubStateSigExtract
(
  void
)
{
  uint32         newSigCertLength;
  Csm_ReturnType retVal;


  /* decode the data from Base64 */
  newSigCertLength = CRY_CVCPUBKEY_SIGCERT_LEN_BYTES;
  retVal = Cry_Base64Decode(
    Cry_CVCPublicKeyExtractContext.certPtr,
    Cry_CVCPublicKeyExtractContext.certLength,
    Cry_CVCPublicKeyExtractContext.certificate,
    &newSigCertLength
  );
  Cry_CVCPublicKeyExtractContext.certLength = newSigCertLength;

  /* make sure this certificate is a valid certificate before
   * further processing */
  if (retVal == CSM_E_OK)
  {
    if (Cry_DerCVCCheckCertificate
         (
            Cry_CVCPublicKeyExtractContext.certificate,
            Cry_CVCPublicKeyExtractContext.certLength
         ) != TRUE
       )
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  if (retVal == CSM_E_OK)
  {
    /* !LINKSTO CS_SECURE_CRY_0028,2 */
    Cry_DerCVCGetDate
    (
        Cry_CVCPublicKeyExtractContext.certificate,
        &Cry_CVCPublicKeyExtractKeyCVDate
    );

    if (TRUE == Cry_CVCPublicKeyExtractContext.cfgPtr->EnableCertChain)
    {
      /* !LINKSTO CS_SECURE_CRY_0030,2 */
      if (Cry_CVCPublicKeyExtractKeyCVDate.EffectiveDate <
          Cry_CVCPublicKeyExtractVerifyCVDate.EffectiveDate)
      {
        /* !LINKSTO CS_SECURE_CRY_0033,2 */
        retVal = CSM_E_NOT_OK;
      }

      /* !LINKSTO CS_SECURE_CRY_0031,2 */
      if (Cry_CVCPublicKeyExtractKeyCVDate.EffectiveDate >
          Cry_CVCPublicKeyExtractVerifyCVDate.ExpirationDate)
      {
        /* !LINKSTO CS_SECURE_CRY_0033,2 */
        retVal = CSM_E_NOT_OK;
      }
    }
  }

  if (retVal == CSM_E_OK)
  {

    /* !LINKSTO CS_SECURE_CRY_0028,2 */
    Cry_CVCPublicKeyExtractContext.signaturePtr = Cry_DerCVCGetSignatureValue
        (
            Cry_CVCPublicKeyExtractContext.certificate,
            &Cry_CVCPublicKeyExtractContext.signatureLength
        );
    /* CHECK: NOPARSE */
    /* Defensive programming, if the certificate buffer is small or empty Cry_Base64Decode will
     * return error. And if the certificate is valid (checked with Cry_DerCVCCheckCertificate)
     * this function must return valid address (position inside certificate buffer).
     */
    if (Cry_CVCPublicKeyExtractContext.signaturePtr == NULL_PTR)
    {
      retVal = CSM_E_NOT_OK;
    }
    /* CHECK: PARSE */
  }

  if (retVal == CSM_E_OK)
  {
    Cry_CVCPublicKeyExtractContext.signedDataPtr = Cry_DerCVCGetSignedData
        (
            Cry_CVCPublicKeyExtractContext.certificate,
            &Cry_CVCPublicKeyExtractContext.signedDataLength
        );
    /* CHECK: NOPARSE */
    /* Defensive programming, if the certificate buffer is small or empty Cry_Base64Decode will
     * return error. And if the certificate is valid (checked with Cry_DerCVCCheckCertificate)
     * this function must return valid address (position inside certificate buffer).
     */
    if (Cry_CVCPublicKeyExtractContext.signedDataPtr == NULL_PTR)
    {
      retVal = CSM_E_NOT_OK;
    }
    /* CHECK: PARSE */
  }

  if (retVal == CSM_E_NOT_OK)
  {
    Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

    Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
    Csm_AsymPublicKeyExtractServiceFinishNotification();
  }
  else
  {
#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
    if (TRUE == Cry_CVCPublicKeyExtractContext.cfgPtr->EnableCertChain)
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_START;
    }
    else
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */
    {
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_WAITFOR_FINISH;

      /* Notify CSM that the data extraction from the key certificate is executed */
      Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_OK);
    }
  }
}

#if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON)
static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyStart
(
  void
)
{
  Csm_ReturnType retVal = CSM_E_OK;
  Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_START_CALLBACK;


  /* !LINKSTO CS_SECURE_CRY_0032,2 */
  /* Deviation MISRAC2012-1 <START> */
  retVal = Csm_SignatureVerifyStart
            (
              Cry_CVCPublicKeyExtractContext.cfgPtr->VerifySignatureCfg,
              (P2CONST(Csm_AsymPublicKeyType,AUTOMATIC,CRY_APPL_DATA))
               &Cry_CVCPublicKeyExtractContext.rootKeyRsa
            );
/* Deviation MISRAC2012-1 <STOP> */
  switch(retVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
      /* try to start the signature verification again */
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_START;
      break;

    default:
      {
        /* verifying the signature failed */
        Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

        Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
        Csm_AsymPublicKeyExtractServiceFinishNotification();
        break;
      }
  }
}

static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyUpdate
(
  void
)
{

  Csm_ReturnType retVal = CSM_E_OK;
  Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE_CALLBACK;

  retVal = Csm_SignatureVerifyUpdate
            (
                Cry_CVCPublicKeyExtractContext.cfgPtr->VerifySignatureCfg,
                Cry_CVCPublicKeyExtractContext.signedDataPtr,
                Cry_CVCPublicKeyExtractContext.signedDataLength
            );

  switch(retVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
      /* try to start the signature verification again */
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_UPDATE;
      break;

    default:
      {
        /* verifying the signature failed */
        Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

        Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
        Csm_AsymPublicKeyExtractServiceFinishNotification();
        break;
      }
  }
}

static FUNC(void, CRY_CODE) Cry_CVCPubStateSigVerifyFinish
(
  void
)
{

  Csm_ReturnType retVal = CSM_E_OK;
  Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH_CALLBACK;

  retVal = Csm_SignatureVerifyFinish
            (
                Cry_CVCPublicKeyExtractContext.cfgPtr->VerifySignatureCfg,
                Cry_CVCPublicKeyExtractContext.signaturePtr,
                Cry_CVCPublicKeyExtractContext.signatureLength,
                &Cry_CVCPublicKeyExtractContext.verificationResult
            );

  switch(retVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
      /* try to start the signature verification again */
      Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_SIG_VERIFY_FINISH;
      break;

    default:
      {
        /* verifying the signature failed */
        Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

        Csm_AsymPublicKeyExtractCallbackNotification(CSM_E_NOT_OK);
        Csm_AsymPublicKeyExtractServiceFinishNotification();
        break;
      }
  }
}
#endif /* #if(CRY_CVCPUBLICKEYEXTRACT_SIG_VERIFY_NOTIFI == STD_ON) */

static FUNC(void, CRY_CODE) Cry_CVCPubStateFinish
(
  void
)
{
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) derModulusPtr;
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) derExponentPtr;
          uint32                           derModulusLength;
          uint32                           derExponentLength;
  Csm_ReturnType                           retVal;

  Cry_CVCPublicKeyExtractContext.ctxState = CRY_CVC_PUB_STATE_IDLE;

  retVal = CSM_E_OK;
  /* !LINKSTO CS_SECURE_CRY_0028,2 */
  derModulusPtr = Cry_DerCVCRSAPubKeyGetModulus
  (
    Cry_CVCPublicKeyExtractContext.certificate,
    &derModulusLength
  );
  derExponentPtr = Cry_DerCVCRSAPubKeyGetExponent
  (
    Cry_CVCPublicKeyExtractContext.certificate,
    &derExponentLength
  );

  /* The modulus contains a leading zero, remove the leading zero.
   * The leading zero is an artifact of the DER encoding of an
   * integer. There cannot be more than one leading zero in the DER
   * encoding, therefore further bytes do not need to be checked
   * (See ISO/IEC 8825-1) */
  if ((derModulusPtr != NULL_PTR) && (derModulusPtr[0] == 0x00U))
  {
    derModulusPtr = &derModulusPtr[1];
    derModulusLength--;
  }

  /* The exponent contains a leading zero, remove the leading zero.
   * The leading zero is an artifact of the DER encoding of an
   * integer. There cannot be more than one leading zero in the DER
   * encoding, therefore further bytes do not need to be checked.
   * (See ISO/IEC 8825-1) */
  if ((derExponentPtr != NULL_PTR) && (derExponentPtr[0] == 0x00U))
  {
    derExponentPtr = &derExponentPtr[1];
    derExponentLength--;
  }

  /* The exponent shall be odd and larger than 2^16 and smaller than 2^32
   * It is assumed that the exponent is provided in big endian
   * representation (the most significant byte is at index 0) */
  /* CHECK: NOPARSE */
  /* defensive programming, these pointers cannot be NULL pointers while they point on certain
   * position inside provided certificate */
  if ((derModulusPtr == NULL_PTR) || (derExponentPtr == NULL_PTR))
  {
    /* !LINKSTO CS_SECURE_CRY_0029,1 */
    retVal = CSM_E_NOT_OK;
  }
  /* CHECK: PARSE */
  /* transform the input data bytes -> words */
  /* CHECK: NOPARSE */
  /* defensive programming, derModulusPtr and derExponentPtr pointers cannot be NULL pointers. */
  if (retVal == CSM_E_OK)
  /* CHECK: PARSE */
  {
    /* !LINKSTO CS_SECURE_CRY_0035,2 */
    if (Cry_LNBEByteArrayToNumber
      (
          derModulusPtr,
          derModulusLength,
          Cry_CVCPublicKeyExtractContext.resultKeyPtr->Modulus,
          CRY_RSAPUBKEY_NUM_LEN_WORDS
      ) == E_OK)
    {
      retVal = CSM_E_OK;
    }
    else
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  /* transform the input data bytes -> words */
  if (retVal == CSM_E_OK)
  {
    /* !LINKSTO CS_SECURE_CRY_0035,2 */
    if (Cry_LNBEByteArrayToNumber
    (
      derExponentPtr,
      derExponentLength,
      Cry_CVCPublicKeyExtractContext.resultKeyPtr->PublicExponent,
      CRY_RSAPUBKEY_NUM_LEN_WORDS
    ) == E_OK)
    {
      retVal = CSM_E_OK;
    }
    else
    {
      retVal = CSM_E_NOT_OK;
    }
  }

  /* if the last function fails this return value will be returned */
  Csm_AsymPublicKeyExtractCallbackNotification(retVal);
  Csm_AsymPublicKeyExtractServiceFinishNotification();
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else  /* #if (CRY_EXTRACTCVCPUBLICKEY_ENABLED == STD_ON) */

/* dummy definition to prevent empty translation unit */
typedef void Cry_CVCPublicKeyExtract_PreventEmptyTranslationUnit_t;

#endif /* #if (CRY_EXTRACTCVCPUBLICKEY_ENABLED == STD_ON) */
