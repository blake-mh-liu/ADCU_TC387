/* --------{ EB Automotive C Source File }-------- */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast should not be performed between a pointer to object type and a
 *    pointer to different object type."
 *
 *   Reason:
 *   The more generic type as specified by AUTOSAR must be used for the API function.
 *   It is ensured, that the type casted to is compatible to the original type.
 *
 *  MISRAC2012-2) Deviated Rule: 13.5 (required)
 *   "The right hand operand of a logical && or || operator shall not contain persistent side effects."
 *
 *   Reason:
 *   The MISRA rule is not violated. This is a constraint of the MISRA checker: When a function
 *   is called on the right hand side of a logical operator, the checker always raises this error
 *   because it does not know whether the function has side effects or not. In our case, none of
 *   the functions have side effects.
 */
/* !LINKSTO CS_SECURE_CRY_0148,1 */
/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_SignatureGenerate.h>
#include <Csm_Hash.h>

#include <Cry_LN.h>
#include <Cry_RsaSsaV15Gen.h>

#if (CRY_RSASSAV15_GEN_ENABLED == TRUE)

/*==[Macros]==================================================================*/

#if (defined CRY_RSASSAV15_G_HASH_MAX_LEN)
#error CRY_RSASSAV15_G_HASH_MAX_LEN is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes. */
#define CRY_RSASSAV15_G_HASH_MAX_LEN 32

#if (defined CRY_RSASSAV15_G_EM_STATIC_FIELDS_LEN)
#error CRY_RSASSAV15_G_EM_STATIC_FIELDS_LEN is already defined
#endif
/** \brief The length of the static EM fields, as described in Chapter 9.2 of the standard
 **        PKCS #1 v2.2: RSA Cryptography Standard
 **/
#define CRY_RSASSAV15_G_EM_STATIC_FIELDS_LEN          11U

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_RsaSsaV15GenStateType
 * \brief Enumeration of the internal states of the RSASSA-PKCS1-v1_5 signature verification.
 *
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_IDLE
 * \brief The algorithm is in the idle state.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_INIT
 * \brief The initialization of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_WAIT_FOR_INIT
 * \brief The initialization of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_INITIALIZED
 * \brief The algorithm is initialized.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_UPDATE
 * \brief The update operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_WAIT_FOR_UPDATE
 * \brief The update operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_FINISH
 * \brief The finish operation of the algorithm is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_WAIT_FOR_FINISH
 * \brief The finish operation of the subservices is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_FINISH_EM
 * \brief The generation of the encoded message is in progress.
 *//**
 * \var Cry_RsaSsaV15GenStateType::CRY_RSASSAV15_G_S_FINISH_S
 * \brief The exponentiation of the encoded message is in progress.
 */
typedef enum
{
  CRY_RSASSAV15_G_S_IDLE,
  CRY_RSASSAV15_G_S_INIT,
  CRY_RSASSAV15_G_S_WAIT_FOR_INIT,
  CRY_RSASSAV15_G_S_INITIALIZED,
  CRY_RSASSAV15_G_S_UPDATE,
  CRY_RSASSAV15_G_S_WAIT_FOR_UPDATE,
  CRY_RSASSAV15_G_S_FINISH,
  CRY_RSASSAV15_G_S_WAIT_FOR_FINISH,
  CRY_RSASSAV15_G_S_FINISH_EM,
  CRY_RSASSAV15_G_S_FINISH_S
}
Cry_RsaSsaV15GenStateType;

/**
 * \struct Cry_RsaSsaV15GenCtxType
 * \brief Structure which contains the context of the RSASSA-PKCS1-v1_5 signature generation
 *//**
 * \var Cry_RsaSsaV15GenCtxType::DataLength
 * \brief The length of the hash value of the data.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::HashResultLength
 * \brief The length of the hash value of the data.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::CfgPtr
 * \brief A pointer to the current RSASSA-PKCS1-v1_5 signature generation configuration which has
 *        to be used.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::KeyPtr
 * \brief A pointer to the secret key which should be used for creating the signature.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::Result
 * \brief A pointer to the start of a buffer where the created signature bytes should be stored.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::ResultLengthPtr
 * \brief A pointer to a variable which contains the maximal allowed space for the signature
 *        and where the length of the created signature should be stored.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::Data
 * \brief A pointer to the start of an array where the data to be signed is stored.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::LNCtx
 * \brief The context which has to be used for long number arithmetic.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::Signature
 * \brief An array which is used as a buffer for the long number representation of the signature
 *        during signature generation.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::tmp1Value
 * \brief An array which is used as a buffer during signature generation.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::State
 * \brief The current state the RSASSA-PKCS1-v1_5 signature generation is in.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::HashResult
 * \brief A pointer to the start of an array where the hash value of the data will be buffered
 *        during the computation.
 *//**
 * \var Cry_RsaSsaV15GenCtxType::EM
 * \brief An array which is used as a buffer for the value "EM" during the signature generation.
 */
typedef struct
{
   uint32                                                       DataLength;
   uint32                                                       HashResultLength;
   P2CONST(Cry_RsaSsaV15GenConfigType, TYPEDEF, CRY_APPL_DATA)  CfgPtr;
   P2CONST(Cry_RsaPrivateKeyType,      TYPEDEF, CRY_APPL_DATA)  KeyPtr;
   P2VAR(uint8,                        TYPEDEF, CRY_APPL_DATA)  Result;
   P2VAR(uint32,                       TYPEDEF, CRY_APPL_DATA)  ResultLengthPtr;
   P2CONST(uint8,                      TYPEDEF, CRY_APPL_DATA)  Data;
   Cry_LNCtxType                                                LNCtx;
   Cry_LNWordType                                        Signature[CRY_RSA_PRIV_KEY_TEMP_LEN_WORDS];
   Cry_LNWordType                                           tmp1Value[CRY_RSAPRIVKEY_NUM_LEN_WORDS];
   Cry_RsaSsaV15GenStateType                                    State;
   uint8                                                   HashResult[CRY_RSASSAV15_G_HASH_MAX_LEN];
   uint8                                                        EM[CRY_RSAPRIVKEY_NUM_LEN_BYTES];
}
Cry_RsaSsaV15GenCtxType;

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief RSASSA-PKCS1-v1_5 signature generation context.
 *
 * The context variable which is used to store the internal state of the
 * RSASSA-PKCS1-v1_5 signature generation.
 */
STATIC VAR(Cry_RsaSsaV15GenCtxType, CRY_VAR) Cry_RsaSsaV15GenCtx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_0140,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)      cfgPtr,
   P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
)
{
   Csm_ReturnType RetVal;


   if (CRY_RSASSAV15_G_S_IDLE == Cry_RsaSsaV15GenCtx.State)
   {
      Cry_RsaSsaV15GenCtx.CfgPtr =
           (P2CONST(Cry_RsaSsaV15GenConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

      /* Deviation MISRAC2012-1 <START> */
      Cry_RsaSsaV15GenCtx.KeyPtr =
              (P2CONST(Cry_RsaPrivateKeyType, AUTOMATIC, CRY_APPL_DATA))keyPtr;
     /* Deviation MISRAC2012-1 <STOP> */
      /* !LINKSTO CS_SECURE_CRY_0002_RsaSsaV15Gen,1 */
      /* Deviation MISRAC2012-2 <START> */
      if ((FALSE == Cry_LNIsValid(Cry_RsaSsaV15GenCtx.KeyPtr->SecretExponent,
                                  CRY_RSAPRIVKEY_NUM_LEN_BYTES)) ||
      /* Deviation MISRAC2012-2 <STOP> */
          (FALSE == Cry_LNIsValid(Cry_RsaSsaV15GenCtx.KeyPtr->Modulus,
                                  CRY_RSAPRIVKEY_NUM_LEN_BYTES)))
      {
        RetVal = CSM_E_NOT_OK;
      }
      else
      {
        Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_INIT;

        RetVal = CSM_E_OK;
      }
   }
   else
   {
      RetVal = CSM_E_BUSY;
   }

   return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_0141,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
)
{
   Csm_ReturnType RetVal;


   if(CRY_RSASSAV15_G_S_IDLE == Cry_RsaSsaV15GenCtx.State)
   {
      RetVal = CSM_E_NOT_OK;
   }
   else if(CRY_RSASSAV15_G_S_INITIALIZED == Cry_RsaSsaV15GenCtx.State)
   {
      /* Store data into context */
      Cry_RsaSsaV15GenCtx.Data = dataPtr;
      Cry_RsaSsaV15GenCtx.DataLength = dataLength;

      /* Set state of the state machine to update */
      Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_UPDATE;

      RetVal = CSM_E_OK;
   }
   else
   {
      RetVal = CSM_E_BUSY;
   }

   return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_0142,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenFinish
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr
)
{
   Csm_ReturnType RetVal;


   if(CRY_RSASSAV15_G_S_IDLE == Cry_RsaSsaV15GenCtx.State)
   {
      RetVal = CSM_E_NOT_OK;
   }
   else if(CRY_RSASSAV15_G_S_INITIALIZED == Cry_RsaSsaV15GenCtx.State)
   {
      /* Store data into context */
      Cry_RsaSsaV15GenCtx.Result = resultPtr;
      Cry_RsaSsaV15GenCtx.ResultLengthPtr = resultLengthPtr;
      /* Set state of the state machine to finish */
      Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_FINISH;

      RetVal = CSM_E_OK;
   }
   else
   {
      RetVal = CSM_E_BUSY;
   }

   return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_0143,1 */
FUNC(void, CRY_CODE) Cry_RsaSsaV15GenMainFunction
(
   void
)
{
   Csm_ReturnType RetVal;
   uint32 i;
   uint32 NumberLength;
   uint32 AlgorithmIdLength;
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) AlgorithmId;
   uint8          DerHeaderDigestBuffer[CRY_COMMON_DER_HEADER_MAX_LEN];
   uint32         DerHeaderDigestLength;
   uint8          DerHeaderDigestInfoBuffer[CRY_COMMON_DER_HEADER_MAX_LEN];
   uint32         DerHeaderDigestInfoLength;
   uint32         TLength;


   switch(Cry_RsaSsaV15GenCtx.State)
   {
      case CRY_RSASSAV15_G_S_INIT:
         Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_WAIT_FOR_INIT;
         RetVal = Csm_HashStart(Cry_RsaSsaV15GenCtx.CfgPtr->HashCfg);

         switch(RetVal)
         {
            case CSM_E_OK:
               break;

            case CSM_E_BUSY:
               Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_INIT;
               break;

            default:
               {
                 Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

                 Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

                 Csm_SignatureGenerateServiceFinishNotification();

                 break;
               }
         }
         break;

      case CRY_RSASSAV15_G_S_WAIT_FOR_INIT:
         break;

      case CRY_RSASSAV15_G_S_UPDATE:
         Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_WAIT_FOR_UPDATE;
         RetVal = Csm_HashUpdate
                  (
                     Cry_RsaSsaV15GenCtx.CfgPtr->HashCfg,
                     Cry_RsaSsaV15GenCtx.Data,
                     Cry_RsaSsaV15GenCtx.DataLength
                  );

         switch(RetVal)
         {
            case CSM_E_OK:
               break;

            case CSM_E_BUSY:
               Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_UPDATE;
               break;

            default:
               {
                 Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

                 Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

                 Csm_SignatureGenerateServiceFinishNotification();

                 break;
               }
         }
         break;

      case CRY_RSASSAV15_G_S_WAIT_FOR_UPDATE:
         break;

      case CRY_RSASSAV15_G_S_FINISH:
         Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_WAIT_FOR_FINISH;
         Cry_RsaSsaV15GenCtx.HashResultLength =
                                          sizeof(Cry_RsaSsaV15GenCtx.HashResult);

         RetVal = Csm_HashFinish
                  (
                     Cry_RsaSsaV15GenCtx.CfgPtr->HashCfg,
                     Cry_RsaSsaV15GenCtx.HashResult,
                     &(Cry_RsaSsaV15GenCtx.HashResultLength),
                     FALSE
                  );

         switch(RetVal)
         {
            case CSM_E_OK:
               break;

            case CSM_E_BUSY:
               Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_FINISH;
               break;

            default:
               {
                 Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

                 Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

                 Csm_SignatureGenerateServiceFinishNotification();

                 break;
               }
         }
         break;

      case CRY_RSASSAV15_G_S_WAIT_FOR_FINISH:
         break;

      case CRY_RSASSAV15_G_S_FINISH_EM:
         /* Get the length of the user-provided modulus (which is equal to the signature length) */
         NumberLength =
                    Cry_LNBitLengthOfNumber(Cry_RsaSsaV15GenCtx.KeyPtr->Modulus);

         /* Make a byte length from the bit length. */
         NumberLength >>= 3U;

         AlgorithmId = Csm_HashAlgorithmId
                       (
                          Cry_RsaSsaV15GenCtx.CfgPtr->HashCfg,
                          &AlgorithmIdLength
                       );

         DerHeaderDigestLength = Cry_CommonDerHeaderOctetString
                                 (
                                    DerHeaderDigestBuffer,
                                    Cry_RsaSsaV15GenCtx.HashResultLength
                                 );

         DerHeaderDigestInfoLength = Cry_CommonDerHeaderSequence
                                     (
                                        DerHeaderDigestInfoBuffer,
                                        Cry_RsaSsaV15GenCtx.HashResultLength
                                        + DerHeaderDigestLength
                                        + AlgorithmIdLength
                                     );

         /* Calculate the length of the T field */
         TLength = Cry_RsaSsaV15GenCtx.HashResultLength +
                   AlgorithmIdLength +
                   DerHeaderDigestLength +
                   DerHeaderDigestInfoLength;

         /* !LINKSTO CS_SECURE_CRY_0003_RsaSsaV15Gen,1 */
         if (NumberLength > (TLength + (uint32)CRY_RSASSAV15_G_EM_STATIC_FIELDS_LEN))
         {
           /* Set the first two bytes */
           Cry_RsaSsaV15GenCtx.EM[0] = (uint8)0x00U;
           Cry_RsaSsaV15GenCtx.EM[1] = (uint8)0x01U;

           /* Generate the PS field */
           for (i = 2U; i < (NumberLength - TLength - 1U); i++)
           {
              Cry_RsaSsaV15GenCtx.EM[i] = (uint8)0xFFU;
           }

           /* Add the zero byte after the PS field */
           Cry_RsaSsaV15GenCtx.EM[i] = (uint8)0x00U;
           i++;

           Cry_CommonCopy
           (
              &Cry_RsaSsaV15GenCtx.EM[i],
              DerHeaderDigestInfoBuffer,
              DerHeaderDigestInfoLength
           );
           i += DerHeaderDigestInfoLength;

           Cry_CommonCopy
           (
              &Cry_RsaSsaV15GenCtx.EM[i],
              AlgorithmId,
              AlgorithmIdLength
           );
           i += AlgorithmIdLength;

           Cry_CommonCopy
           (
              &Cry_RsaSsaV15GenCtx.EM[i],
              DerHeaderDigestBuffer,
              DerHeaderDigestLength
           );
           i += DerHeaderDigestLength;

           Cry_CommonCopy
           (
              &Cry_RsaSsaV15GenCtx.EM[i],
              Cry_RsaSsaV15GenCtx.HashResult,
              Cry_RsaSsaV15GenCtx.HashResultLength
           );

           /* CHECK: NOPARSE */
           /* Defensive Programming - unreachable code. */
           if
           (
              Cry_LNBEByteArrayToNumber
              (
                 Cry_RsaSsaV15GenCtx.EM,
                 NumberLength,
                 Cry_RsaSsaV15GenCtx.tmp1Value,
                 (Cry_LNWordType)(sizeof(Cry_RsaSsaV15GenCtx.tmp1Value) /
                    sizeof(Cry_RsaSsaV15GenCtx.tmp1Value[0]))
              ) != E_OK
           )
             /* CHECK: PARSE */
           {
              Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

              Csm_SignatureGenerateCallbackNotification(CSM_E_SMALL_BUFFER);

              Csm_SignatureGenerateServiceFinishNotification();
           }
           else
           {
              Cry_LNModExpStart(&Cry_RsaSsaV15GenCtx.LNCtx);

              Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_FINISH_S;
           }
         }
         else
         {
           Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

           Csm_SignatureGenerateCallbackNotification(CSM_E_NOT_OK);

           Csm_SignatureGenerateServiceFinishNotification();
         }
         break;

      case CRY_RSASSAV15_G_S_FINISH_S:
         /* Signature = EM^SecretExponent mod Modulus */
         if
         (
            Cry_LNModExp
            (
               Cry_RsaSsaV15GenCtx.Signature,
               Cry_RsaSsaV15GenCtx.tmp1Value,
               Cry_RsaSsaV15GenCtx.KeyPtr->Modulus,
               Cry_RsaSsaV15GenCtx.KeyPtr->SecretExponent,
               &Cry_RsaSsaV15GenCtx.LNCtx
            ) == TRUE
         )
         {
            Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;

            if
            (
               Cry_LNNumberToBEByteArray
               (
                  Cry_RsaSsaV15GenCtx.Signature,
                  Cry_RsaSsaV15GenCtx.Result,
                  Cry_RsaSsaV15GenCtx.ResultLengthPtr
               ) != E_OK
            )
            {
               Csm_SignatureGenerateCallbackNotification(CSM_E_SMALL_BUFFER);
            }
            else
            {
               Csm_SignatureGenerateCallbackNotification(CSM_E_OK);
            }

            Csm_SignatureGenerateServiceFinishNotification();
         }
         break;

      case CRY_RSASSAV15_G_S_INITIALIZED:
      default:
         {
           break;
         }
   }
}

FUNC(Std_ReturnType, CRY_CODE) Cry_RsaSsaV15GenCallback
(
   Csm_ReturnType Result
)
{
   switch(Cry_RsaSsaV15GenCtx.State)
   {
      case CRY_RSASSAV15_G_S_WAIT_FOR_INIT:
      case CRY_RSASSAV15_G_S_WAIT_FOR_UPDATE:
         Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_INITIALIZED;
         Csm_SignatureGenerateCallbackNotification(Result);
         break;

      case CRY_RSASSAV15_G_S_WAIT_FOR_FINISH:
         if(Result != CSM_E_OK)
         {
            Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_IDLE;
            Csm_SignatureGenerateCallbackNotification(Result);
            Csm_SignatureGenerateServiceFinishNotification();
         }
         else
         {
            Cry_RsaSsaV15GenCtx.State = CRY_RSASSAV15_G_S_FINISH_EM;
         }
         break;

      default:
         {
           break;
         }
   }

   return E_OK;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if (CRY_RSASSAV15_GEN_ENABLED == TRUE) */

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/* Dummy type definition to prevent compiler warnings about empty translation units */
typedef uint8 Cry_RsaSsaV15Gen_PrvtEmptyTranslationUnitType;

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

#endif /* #if (CRY_RSASSAV15_GEN_ENABLED == TRUE) #else */
