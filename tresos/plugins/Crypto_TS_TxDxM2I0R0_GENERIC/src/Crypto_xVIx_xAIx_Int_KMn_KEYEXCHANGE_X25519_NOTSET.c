/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type
 * and a pointer to a different object type.
 *
 * Reason:
 * Problems could arise on little and big endian platform. But tests are successful on little and
 * big endian platform.
 *
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/*
 * Code-Metric Deviation List
 *
 * CODEMETRIC-1) Deviated Rule: HIS_VOCF
 * not 14.1 <= 12
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                    /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                      /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.c/0004,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>
#include <Crypto_xVIx_xAIx_Int_Lib_Ecc.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.h>

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PRIVKEY_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PRIVKEY_LENGTH is already defined
#endif
/** \brief The private key length of the X25519 curve in bytes. */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PRIVKEY_LENGTH 32U

#if(defined CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PUBKEY_LENGTH)
  #error CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PUBKEY_LENGTH is already defined
#endif
/** \brief The public key length of the X25519 curve in bytes. */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_PUBKEY_LENGTH 32U

#if(defined CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_BYTEARRAY_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_BYTEARRAY_LENGTH is already defined
#endif
/** \brief The maximum length,which is needed for byte array representation **/
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_BYTEARRAY_LENGTH 32U

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible stored number. This length depends on the configured curve.
 */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS                                    \
(                                                                                    \
   (Crypto_xVIx_xAIx_LNWordType)                                                     \
   (                                                                                 \
      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_BYTEARRAY_LENGTH) + \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                               \
   )                                                                                 \
)

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary number. This length depends on the
 *         configured curve.
 */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS                                     \
(                                                                                      \
   (Crypto_xVIx_xAIx_LNWordType)                                                       \
   (                                                                                   \
      (CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS * (Crypto_xVIx_xAIx_LNWordType)2UL) - \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                                 \
   )                                                                                   \
)

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
/** \brief Conditional swap.
 **
 ** This function swaps two numbers with using third variable and bitwise XOR as described
 ** in RFC 7748. The cswap function SHOULD be implemented in constant time.
 **
 ** \param[in,out] value1  Pointer to the first long number to swap.
 ** \param[in,out] value2  Pointer to the second long number to swap.
 ** \param[in]     dummy   Pointer a buffer which is used as temporary storage during the swapping.
 ** \param[in]     swap    Contains swap XOR the current bit of scalar. Is the result 0 the long
 **                        numbers would not be exchanged.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dummy,
       Crypto_xVIx_xAIx_LNWordType                                          swap
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

/** \brief Calculate the key.
 **
 ** This function is the recommended Montgomery-X-coordinate DH function and
 ** calculates the public key and the secret shared key.
 **
 **  \param[in]     scalar       Pointer to the memory location where the private
 **                              value is stored:
 **  \param[in]     value        Pointer to the memory location where the public
 **                              value or the u-coordinate is stored.
 **  \param[in,out] tmp          Pointer to a temporary buffer for the calculation.
 **  \param[in]     curveIndex   Index of the corresponding elliptic curve, which shall be used.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) scalar,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
          uint8                                                               curveIndex
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

/** \brief Helper Function for Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey.
 **
 ** This Function is a Helper Function for Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey. It calls
 ** Crypto_xVIx_xAIx_LNMultiplyNumbers until it is Finished.
 **
 **  \param[in,out] result         Pointer to the memory area which should contain
 **                                the long number representation of the result
 **                                of the multiplication.
 **  \param[in,out] multiplicand   Pointer to the long number representation of
 **                                the multiplicand.
 **  \param[in,out] multiplicator  Pointer to the long number representation of
 **                                the multiplicator
 **  \param[in,out] lnCtx          Pointer to a context which holds the current
 **                                state of the multiplication.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicator,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lnCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
/* --- Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCPUBVAL_X25519_NOTSET_Process ------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_KMn_KEYEXCHANGECALCPUBVAL_X25519_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCPUBVAL_X25519_NOTSET_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValuePtr,
    P2VAR(uint32,         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValueLengthPtr
)
{
  Std_ReturnType              retVal                                                  = E_NOT_OK;
  /* Set the curve index */
  uint8                       curveIndex                                              = CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE;
  boolean                     fromPrimitive                                           = FALSE;

  Crypto_xVIx_xAIx_LNWordType privateKeyLN[CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS] = { 0U };

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) privateKey;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ownPublicKey;

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(jobs);
  TS_PARAM_UNUSED(jobsLength);
  TS_PARAM_UNUSED(wkspDataLen);

  /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0021,1 */
  /* Check output buffer size */
  if (*publicValueLengthPtr < Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].publicKeyLength)
  {
    retVal = CRYPTO_E_SMALL_BUFFER;
  }
  else
  {
    /* Get the private key from key element */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYEXCHANGE_PRIVKEY,
                                                       &(privateKey),
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0009,1 */
    if (E_OK == retVal)
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, privateKey, fromPrimitive);
    }

    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0011,1 */
    if (E_OK == retVal)
    {
      /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0012,1 */
      if (Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength != privateKey->data->size)
      {
        retVal = E_NOT_OK;
      }
      else
      {
        /* Set the length of private key */
        privateKeyLN[0U] =
                CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength);

        /* The return value is ignored because the parameters are either from the context where they are
          properly defined or local variables which are properly defined before passing them to the function. */
        (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(privateKey->data->data,
                                                     privateKey->data->size,
                                                     privateKeyLN,
                                                     sizeof(privateKeyLN) /
                                                     sizeof(privateKeyLN[0U])
                                                    );

        /* Set the length of private key again for the bitmask patches */
        privateKeyLN[0U] = CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength);

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0010,1 */
        /* Clear the first 3 bits */
        privateKeyLN[1U] &= (Crypto_xVIx_xAIx_LNWordType)(~((Crypto_xVIx_xAIx_LNWordType)7U));

        /* Clear the highest bit of the last octet from the first hash half */
        privateKeyLN[privateKeyLN[0U]] &= (Crypto_xVIx_xAIx_LNWordType)(~(CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT));

        /* Set the second highest bit of the final octet from the first hash half */
        privateKeyLN[privateKeyLN[0U]] |= (Crypto_xVIx_xAIx_LNWordType)((CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT) >> 1U);

        /* Calculate the own public key */
        Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey(privateKeyLN,
                                    Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].coeff1, /* UCoordinate*/
                                    wkspDataPtr,
                                    curveIndex
                                   );

        /* Return value can be ignored as the length is already checked */
        /* Deviation MISRAC2012-1 <+3> */
        (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray
        (
          (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &wkspDataPtr[(16U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS)],
          publicValuePtr,
          publicValueLengthPtr
        );

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0017,1 */
        /* Store the public key in the key element */
        retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                            CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY,
                                                           &(ownPublicKey),
                                                            FALSE,
                                                            CRYPTO_XVIX_XAIX_SID_EMPTY
                                                          );

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0013,1 */
        if (E_OK == retVal)
        {
          fromPrimitive = FALSE;
          /* Deviation TASKING-1 */
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, ownPublicKey, fromPrimitive);
          /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0014,1 */
          if (E_OK == retVal)
          {
            /* Set the size */
            /* !LINKSTO Crypto.Asr.SWS_Crypto_00109,1 */
            ownPublicKey->data->size = *publicValueLengthPtr;
            /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/COMMON/0001,1 */
            /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/COMMON/0002,1 */
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(cryptoKeyId,
                                               CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY,
                                               ownPublicKey,
                                               publicValuePtr,
                                               ownPublicKey->data->size,
                                               retVal
                                              );
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(ownPublicKey);
          }
          else
          {
            retVal = E_NOT_OK;
          }
        }
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(privateKey);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCSECRET_X25519_NOTSET_Process ------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_KMn_KEYEXCHANGECALCSECRET_X25519_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCSECRET_X25519_NOTSET_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId,
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) partnerPublicValuePtr,
          uint32                                                 partnerPublicValueLength
)
{
  Std_ReturnType retVal                                                               = E_NOT_OK;
  /* Set the curve index */
  uint8          curveIndex                                                           = CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE;
  boolean        fromPrimitive                                                        = FALSE;

  Crypto_xVIx_xAIx_LNWordType privateKeyLN[CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS] = { 0U };
  Crypto_xVIx_xAIx_LNWordType paPubKeyLN[CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_NUM_LEN_WORDS  ] = { 0U };

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) privateKey;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sharedKey;

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(jobs);
  TS_PARAM_UNUSED(jobsLength);

  /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0022,1 */
  /* Check output buffer size */
  if (partnerPublicValueLength != Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].publicKeyLength)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* Get the private key from key element */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYEXCHANGE_PRIVKEY,
                                                       &(privateKey),
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0009,1 */
    if (E_OK == retVal)
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, privateKey, fromPrimitive);
    }

    /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0011,1 */
    if (E_OK == retVal)
    {
      /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0012,1 */
      if (Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength != privateKey->data->size)
      {
        retVal = E_NOT_OK;
      }
      else
      {
        /* Set the length of private key */
        privateKeyLN[0U] = CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength);

        /* Return value can be ignored as the length is already checked */
        (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(privateKey->data->data,
                                                     privateKey->data->size,
                                                     privateKeyLN,
                                                     sizeof(privateKeyLN) / sizeof(privateKeyLN[0U])
                                                    );

        /* Set the length of private key again for the bitmask patches */
        privateKeyLN[0U] = CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength);

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0010,1 */
        /* Clear the first 3 bits */
        privateKeyLN[1U] &= (Crypto_xVIx_xAIx_LNWordType)(~((Crypto_xVIx_xAIx_LNWordType)7U));

        /* Clear the highest bit of the last octet from the first hash half */
        privateKeyLN[privateKeyLN[0U]] &= (Crypto_xVIx_xAIx_LNWordType)(~(CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT));

        /* Set the second highest bit of the final octet from the first hash half */
        privateKeyLN[privateKeyLN[0U]] |= (Crypto_xVIx_xAIx_LNWordType)((CRYPTO_XVIX_XAIX_LN_WORD_HIGH_BIT) >> 1U);

        /* Set the length of the partner public key */
        paPubKeyLN[0U] = Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].publicKeyLength;

        /* Return value can be ignored as the length is already checked */
        (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(partnerPublicValuePtr,
                                                     partnerPublicValueLength,
                                                     paPubKeyLN,
                                                     sizeof(paPubKeyLN) / sizeof(paPubKeyLN[0U])
                                                    );

        /* Calculate the secret shared key */
        Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey(privateKeyLN,
                                    paPubKeyLN,
                                    wkspDataPtr,
                                    curveIndex
                                   );

        wkspDataLen = Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength;
        /* Return value can be ignored as the length is already checked */
        /* Deviation MISRAC2012-1 <+3> */
        (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray
        (
          (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &wkspDataPtr[(16U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS)],
          wkspDataPtr,
         &(wkspDataLen)
        );

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0017,1 */
        /* Store the public key in the key element */
        retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                            CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE,
                                                           &(sharedKey),
                                                            FALSE,
                                                            CRYPTO_XVIX_XAIX_SID_EMPTY
                                                          );

        /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0015,1 */
        if (E_OK == retVal)
        {
          fromPrimitive = FALSE;
          /* Deviation TASKING-1 */
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, sharedKey, fromPrimitive);
          /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0016,1 */
          if (E_OK == retVal)
          {
            /* Set the size */
            sharedKey->data->size = wkspDataLen;
            /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/COMMON/0001,1 */
            /* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/COMMON/0003,1 */
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(cryptoKeyId,
                                               CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE,
                                               sharedKey,
                                               wkspDataPtr,
                                               sharedKey->data->size,
                                               retVal
                                              );
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(sharedKey);
          }
          else
          {
            retVal = E_NOT_OK;
          }
        }
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(privateKey);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap ------------------------------------------- */

/* !LINKSTO Crypto.Req.KMn/KEYEXCHANGE_X25519_NOTSET/GENERAL/0023,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value1,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value2,
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dummy,
       Crypto_xVIx_xAIx_LNWordType                                          swap
)
{
  Crypto_xVIx_xAIx_LNWordType i;
  Crypto_xVIx_xAIx_LNWordType mask = 0U;

  if((value1[0U] != value2[0U]) && (1U == swap))
  {
    value1[0U] ^= value2[0U];
    value2[0U] ^= value1[0U];
    value1[0U] ^= value2[0U];
  }

  dummy[0U] = 8U;
  /* dummy = value1 XOR value2 dummy[0] stores the length*/
  for(i = 1U; i <= dummy[0U]; i++)
  {
    dummy[i] = value1[i] ^ value2[i];
  }

  /* mask(swap) = 0 - swap */
  if(1U == swap)
  {
    mask = 0xFFFFFFFFUL;
  }

  /* dummy = mask(swap) AND dummy */
  for(i = 1U; i <= dummy[0U]; i++)
  {
    dummy[i] &= mask;
  }

  /* value1 = value1 XOR dummy */
  for(i = 1U; i <= dummy[0U]; i++)
  {
    value1[i] ^= dummy[i];
  }

  /* value2 = value2 XOR dummy */
  for(i = 1U; i <= dummy[0U]; i++)
  {
    value2[i] ^= dummy[i];
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKey
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) scalar,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
    P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
          uint8                                                               curveIndex
)
{
  /* Current bit of the scalar */
  Crypto_xVIx_xAIx_LNWordType currentBit;
  Crypto_xVIx_xAIx_LNWordType bit;
  Crypto_xVIx_xAIx_LNCtxType  lnCtx;

  uint32                      i    = 0U;
  Crypto_xVIx_xAIx_LNWordType swap = 0U;

  /* buffer which will be used as temporary storage */
  /* Deviation MISRAC2012-1 <+14> */
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) x2   =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[0U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) z2   =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[4U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1 =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[8U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2 =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[12U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];
  /* result->xValue */
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) x3   =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[16U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];
  /* result->zValue */
  CONSTP2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) z3   =
      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) &tmp[20U * CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGE_X25519_NOTSET_TEMP_LEN_WORDS];

  /* x2 = 1 */
  x2[0U] = 1U;
  x2[1U] = 1U;

  /* z2 = 0 */
  z2[0U] = 1U;
  z2[1U] = 0U;

  /* z3 = 1 */
  z3[0U] = 1U;
  z3[1U] = 1U;

  /* u-coordinate and the public key of partner */
  /* x3 = value */
  x3[0U] = value[0U];

  for(i = 1U; i <= value[0U]; i++)
  {
    x3[i] = value[i];
  }

  /* The ladder-step computation */
  currentBit = Crypto_xVIx_xAIx_LNBitLengthOfNumber(scalar);

  while(0U < currentBit)
  {
    currentBit--;
    bit = CRYPTO_XVIX_XAIX_LN_GET_BIT(scalar, currentBit);
    swap ^= bit;
    /* conditional swap */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap(x2, x3, tmp1, swap);
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap(z2, z3, tmp1, swap);
    swap = bit;

    /* C: tmp1 = x3 + z3 */
    Crypto_xVIx_xAIx_LNAdditionModular(tmp1, x3, z3, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* D: x3 = x3 - z3 */
    Crypto_xVIx_xAIx_LNSubtractionModular(x3, x3, z3, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* A: z3 = x2 + z2 */
    Crypto_xVIx_xAIx_LNAdditionModular(z3, x2, z2, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* B: x2 = x2 - z2 */
    Crypto_xVIx_xAIx_LNSubtractionModular(x2, x2, z2, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* CB = C * B: tmp1 = tmp1 * x2 */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(tmp1, tmp1, x2, &lnCtx);

    /* DA = D * A: x3 = x3 * z3 */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(x3, x3, z3, &lnCtx);

    /* A^2: z3 = z3 * z3 */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(z3, z3, z3, &lnCtx);

    /* B^2: x2 = x2 * x2 */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(x2, x2, x2, &lnCtx);

    /* E = A^2 - B^2: tmp2 = z3 - x2 : tmp2 */
    Crypto_xVIx_xAIx_LNSubtractionModular(tmp2, z3, x2, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* z2 = a24(coeff2) * E */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper
    (
      z2,
      Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].coeff2,
      tmp2,
      &lnCtx
    );

    /* (A^2 + a24 * E): z2 = z2 + z3 */
    Crypto_xVIx_xAIx_LNAdditionModular(z2, z3, z2, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* E * (A^2 + a24 * E): z2 = z2 * tmp2 --> final result */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(z2, tmp2, z2, &lnCtx);

    /* A^2 * B^2: x2 = z3 * x2 --> final result */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(x2, z3, x2, &lnCtx);

    /* DA - CB: z3 = x3 - tmp1 */
    Crypto_xVIx_xAIx_LNSubtractionModular(z3, x3, tmp1, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* (DA - CB)^2: z3 */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(z3, z3, z3, &lnCtx);

    /* z3: value * (DA - CB)^2 = value * z3 --> final result */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(z3, value, z3, &lnCtx);

    /* DA + CB: x3 = x3 + tmp1 */
    Crypto_xVIx_xAIx_LNAdditionModular(x3, x3, tmp1, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime);

    /* x3: (DA + CB)^2 = x3 * x3 --> final result */
    Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(x3, x3, x3, &lnCtx);

  }
  /* conditional swap */
  Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap(x2, x3, tmp1, swap);
  Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_Swap(z2, z3, tmp1, swap);
  Crypto_xVIx_xAIx_LNInversion(tmp1, z2, x3, z3, tmp2, Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].prime, &lnCtx);

  /* result = x2 * 1/z2 */
  Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper(x3, x2, tmp1, &lnCtx);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper ---------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYEXCHANGE_X25519_NOTSET_CalcKeyHelper
(
    P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
  P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicator,
    P2VAR(Crypto_xVIx_xAIx_LNCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) lnCtx
)
{
  Crypto_xVIx_xAIx_ECCtxType eCCtx;

  eCCtx.curveIndex = CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE;

  Crypto_xVIx_xAIx_LNMultiplyNumbers(result, multiplicand, multiplicator, lnCtx);
  Crypto_xVIx_xAIx_EllipticCurveInfo[eCCtx.curveIndex].fastReductionFun
  (
    result,
    &eCCtx
  );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

