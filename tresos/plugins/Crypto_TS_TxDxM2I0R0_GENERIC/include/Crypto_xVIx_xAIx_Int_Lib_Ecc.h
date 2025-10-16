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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_LIB_ECC_H
#define CRYPTO_XVIX_XAIX_INT_LIB_ECC_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_Lib_LN.h> /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.h/0002,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_Ecc_Cfg.h> /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc.h/0003,1 */

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_EC_DER_LENGTH)
#error CRYPTO_XVIX_XAIX_EC_DER_LENGTH is already defined
#endif
/** \brief Maximal length of DER-Encoding of a curve with its initial two bytes missing. */
#define CRYPTO_XVIX_XAIX_EC_DER_LENGTH 16U

#if (defined CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM)
#error CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM is already defined
#endif
/** \brief The number of supported Elliptic curves. */
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) && \
     (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS          == STD_ON) \
    )
#define CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM 4U
#elif (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
#define CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM 2U
#elif (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS == STD_ON)
#define CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM 2U
#else
#define CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM 0U
#endif

#if(defined CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary number.
 */
#define CRYPTO_XVIX_XAIX_EDX25519_TEMP_LEN_WORDS 17U

#if(defined CRYPTO_XVIX_XAIX_ECC_ARRAY_LEN)
#error CRYPTO_XVIX_XAIX_ECC_ARRAY_LEN is already defined
#endif
/** \brief The maximum length,which is needed for byte array representation **/
#define CRYPTO_XVIX_XAIX_ECC_ARRAY_LEN 48U

#if (defined CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number
 *         representation of the longest possible stored number.
 */
#define CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS                                  \
(                                                                           \
   (Crypto_xVIx_xAIx_LNWordType)                                            \
   (                                                                        \
      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_ECC_ARRAY_LEN) +      \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                      \
   )                                                                        \
)

#if (defined CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number
 *         representation of the longest possible temporary number.
 */
#define CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS                                     \
(                                                                               \
   (Crypto_xVIx_xAIx_LNWordType)                                                \
   (                                                                            \
      (CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS * (Crypto_xVIx_xAIx_LNWordType)2UL) - \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                          \
   )                                                                            \
)

#if(defined CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PRIVKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PRIVKEY_LEN_BYTES is already defined
#endif
/** \brief The private key length of the Ed25519/Ed25519ph in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PRIVKEY_LEN_BYTES 32U

#if(defined CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PUBKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PUBKEY_LEN_BYTES is already defined
#endif
/** \brief The public key length of the Ed25519/Ed25519ph in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_ED25519YY_PUBKEY_LEN_BYTES 32U

/*-- Signature Gen/Vrfy Default Curves -----------------------------------------------------------*/

#if (defined CRYPTO_XVIX_XAIX_SIGNATURE_ED25519YY_DEFAULT_CURVE)
#error CRYPTO_XVIX_XAIX_SIGNATURE_ED25519YY_DEFAULT_CURVE is already defined
#endif
/** \brief The default Curve of the Algorithm Family CRYPTO_ALGOFAM_ED25519/CRYPTO_ALGOFAM_ED25519PH
 *         for Signature generation and verification, which is supported.
 */
#define CRYPTO_XVIX_XAIX_SIGNATURE_ED25519YY_DEFAULT_CURVE 0U

/*-- Elliptic Curves Exchange --------------------------------------------------------------------*/

#if(defined CRYPTO_XVIX_XAIX_CURVE_X25519_PRIVKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_X25519_PRIVKEY_LEN_BYTES is already defined
#endif
/** \brief The private key length of the X25519 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_X25519_PRIVKEY_LEN_BYTES 32U

#if(defined CRYPTO_XVIX_XAIX_CURVE_X25519_PUBKEY_LEN_BYTES)
  #error CRYPTO_XVIX_XAIX_CURVE_X25519_PUBKEY_LEN_BYTES is already defined
#endif
/** \brief The public key length of the X25519 curve in bytes. */
#define CRYPTO_XVIX_XAIX_CURVE_X25519_PUBKEY_LEN_BYTES 32U

/*-- Key Exchange Default Curves -----------------------------------------------------------------*/

#if (defined CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE)
#error CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE is already defined
#endif
/** \brief The default Curve of the Algorithm Family CRYPTO_ALGOFAM_X25519
 *         for KeyExchange, which is supported.
 */
#define CRYPTO_XVIX_XAIX_KEYEXCHANGE_X25519_DEFAULT_CURVE 1U

/*-- Key Generate Default Curves -----------------------------------------------------------------*/

#if (defined CRYPTO_XVIX_XAIX_KEYGENERATE_ED25519YY_DEFAULT_CURVE)
#error CRYPTO_XVIX_XAIX_KEYGENERATE_ED25519YY_DEFAULT_CURVE is already defined
#endif
/** \brief The default Curve of the Algorithm Family CRYPTO_ALGOFAM_ED25519/CRYPTO_ALGOFAM_ED25519PH
 *         for KeyGenerate, which is supported.
 */
#define CRYPTO_XVIX_XAIX_KEYGENERATE_ED25519YY_DEFAULT_CURVE 0U

/*==================[type definitions]============================================================*/

/* --- Elliptic Curves -------------------------------------------------------------------------- */

/** \brief The Algorithm Family of the Elliptic Curve **/
typedef uint8 Crypto_xVIx_xAIx_ECAlgoFamType;

/** \brief A Point on an Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_ECPointType::XValue
 ** \brief The x-coordinate of the Point on the curve.
 **
 ** \var Crypto_xVIx_xAIx_ECPointType::YValue
 ** \brief The y-coordinate of the Point on the curve.
 **
 ** \var Crypto_xVIx_xAIx_ECPointType::ZValue
 ** \brief If the point is in projective coordinates, this is the z-coordinate of the Point.
 **/
typedef struct
{
  Crypto_xVIx_xAIx_LNWordType xValue[CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS];
  Crypto_xVIx_xAIx_LNWordType yValue[CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS];
  Crypto_xVIx_xAIx_LNWordType zValue[CRYPTO_XVIX_XAIX_ECC_TEMP_LEN_WORDS];
}
Crypto_xVIx_xAIx_ECPointType;

/** \brief The OID of the Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_ECDEREncodingType::Length
 ** \brief The length of OID.
 **
 ** \var Crypto_xVIx_xAIx_ECDEREncodingType::value
 ** \brief The OID of the Elliptic Curve.
 **/
typedef struct
{
  uint8      length;
  uint8      value[CRYPTO_XVIX_XAIX_EC_DER_LENGTH];
}
Crypto_xVIx_xAIx_ECDEREncodingType;

/** \brief The context which has to be used for Elliptic Curve arithmetic.
 **
 ** \var Crypto_xVIx_xAIx_ECCtxType::lnCtx
 ** \brief Context of underlying long number arithmetic functions.
 **
 ** \var Crypto_xVIx_xAIx_ECCtxType::currentBit
 ** \brief Current bit of the multiplicand in the multiplication.
 **
 ** \var Crypto_xVIx_xAIx_ECCtxType::curveIndex
 ** \brief Index of the curve in the elliptic curve information array.
 **
 ** \var Crypto_xVIx_xAIx_ECCtxType::x0
 ** \brief The least significant bit of the x-coordinate.
 **
 **/
typedef struct
{
  Crypto_xVIx_xAIx_LNCtxType       lnCtx;
  Crypto_xVIx_xAIx_LNWordType      currentBit;
  uint8                            curveIndex;
  uint8                            x0;
}
Crypto_xVIx_xAIx_ECCtxType;

/** \brief The different reduction functions for different elliptic curves all have an
 **        identical API. This function pointer type describes that API.
 **/
typedef P2FUNC(void, CRYPTO_xVIx_xAIx_APPL_DATA, Crypto_xVIx_xAIx_ECFastReductionFctType)
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Additional information for Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::basePoint
 ** \brief The Base Point for the Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::prime
 ** \brief Prime number of Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::modulus
 ** \brief The Order of p.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::coeff1
 ** \brief A real coefficient.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::coeff2
 ** \brief A real coefficient.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::ecDER
 ** \brief The DER-Encoding of the corresponding Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::algoFam
 ** \brief The Family Algorithm of the corresponding Elliptic Curve.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::privateKeyLength
 ** \brief The Length of the private key in LN-format.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::publicKeyLength
 ** \brief The Length of the Public key in LN-format.
 **
 ** \var Crypto_xVIx_xAIx_EllipticCurveInfoType::fastReductionFun
 ** \brief For each Curve, we have a function which can perform fast
 **        reduction modulo that prime.
 **
 **/
typedef struct
{
  Crypto_xVIx_xAIx_ECPointType             basePoint;
  Crypto_xVIx_xAIx_LNWordType              prime[CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS];
  Crypto_xVIx_xAIx_LNWordType              modulus[CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS];
  Crypto_xVIx_xAIx_LNWordType              coeff1[CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS];
  Crypto_xVIx_xAIx_LNWordType              coeff2[CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS];

  Crypto_xVIx_xAIx_ECDEREncodingType       ecDER;
  Crypto_xVIx_xAIx_ECAlgoFamType           algoFam;

  uint8                                    privateKeyLength;
  uint8                                    publicKeyLength;

  Crypto_xVIx_xAIx_ECFastReductionFctType  fastReductionFun;
}
Crypto_xVIx_xAIx_EllipticCurveInfoType;

/*==================[external constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief Informations of the supported Elliptic Curves. *
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO == STD_ON)
extern CONST(Crypto_xVIx_xAIx_EllipticCurveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_EllipticCurveInfo[CRYPTO_XVIX_XAIX_SUPPORTED_EC_NUM];
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* --- Elliptic Curves -------------------------------------------------------------------------- */

/** \brief Retrieve the corresponding Elliptic Curve`'s index
 **
 **        This Function retrieves the corresponding Elliptic Curve`'s index according to the OID.
 **
 **
 **  \param[in]     serviceInfo     The used Service of the processed Job.
 **  \param[in]     algorithmFamily The Family type of the processed Job.
 **  \param[in]     curveDER        Pointer to the DER-Encoding of the Elliptic Curve in KeyElement,
 **                                 which has to be compared.
 **  \param[in]     curveDERLength  The Length of the DER-Encoding, which has to be compared.
 **  \param[in,out] curveIndex      Pointer to the index of the corresponding Elliptic Curve, which
 **                                 will be used for key exchange.
 **
 **  \returns Error value
 **
 **  \RetVal E_OK      The Elliptic Curve is supported.
 **  \RetVal E_NOT_OK  The Elliptic Curve is not supported.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetECIndex
(
          uint8                                         serviceInfo,
          uint8                                         algorithmFamily,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) curveDER,
          uint8                                         curveDERLength,
    P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) curveIndex
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX == STD_ON) */

/*--- Ed25519 / Ed25519ph / X25519 ---------------------------------------------------------------*/

/** \brief  Fast reduction modulo the polynomial of Edwards curve.
 **
 ** This function performs the fast reduction modulo the reduction polynomial which is the
 ** base of the Edwrads curve 25519.
 ** It is based on the following observations:
 ** Let "value" have the binary notation
 ** value = c509*(2^509) + c508*(2^508) + ... + c1*2 + c0.
 ** where each cX is either 0 or 1.
 ** Then we can write value as the sum value = A1*(2^255) + A2 with the two 160-bit integers
 ** A1 = c509*(2^254) + c508*(2^253) + ... + c256*2 + c255 and
 ** A2 = c254*(2^254) + c253*(2^253) + ... + c1*2   + c0.
 ** We know that p = 2^255 - 19.
 ** From this follows that 2^255 = 2^4 + 3 (mod p) and therefore
 ** x*(2^255) = x*(2^4 + 3) (mod p) for all x.
 ** But this means that
 ** value = A1*(2^255)      + A2 (mod p)
 **       = A1*(2^4 + 3)    + A2 (mod p)
 **       = A1*(2^4) + 3*A1 + A2 (mod p).
 ** A1 + A2 (mod p) can be computed easily because A1 and A2 are both
 ** smaller than p. Now we want to reduce A1*(2^4) further.
 ** For this we write:
 ** A1*(2^4) = B
 ** A1*(2^4) = B1*(2^255) + B2
 ** Again we use the congruence from above to get
 ** A1*(2^4) = B1*(2^4) + 3*B1 + B2 (mod p)
 ** Everything taken together this yields
 ** value =  3*A1 + A2 + B1*(2^4) + 3*B1 + B2 (mod p)
 ** where all summands are smaller than p. We use this last congruence to
 ** compute the reduction.
 **
 ** \param[in]     value  Pointer to the start of an array which holds the number to be reduced.
 ** \param[in,out] ctxPtr Pointer to a context which holds the current state of the conversion.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_EdDSAFastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION == STD_ON) */

/* ============================================================================================== */
/*                      These functions are used just for ED25519/ED25519PH                       */
/* ============================================================================================== */

/** \brief  This function multiplies a point on an Edwards curve which is given in
 **         projective coordinates with an integer and returns the result again in projective coordinates.
 **
 ** \param[out]    result       Pointer to an Edwards curve point where the result of the
 **                             multiplication will be stored in projective coordinates.
 ** \param[in]     point        Pointer to an edwards curve point given in projective coordinates
 **                             which should multiplied. This parameter must not point to the same
 **                             memory location as the result "result".
 ** \param[in]     multiplicand Pointer to an edwards curve point with which the point should be multiplied.
 ** \param[in,out] tmp          Pointer to a buffer which is used as temporary storage for the calculation.
 ** \param[in]     edCtx        Pointer the the context.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  point,
  P2CONST(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  multiplicand,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION == STD_ON) */

/** \brief  This function adds two points on an elliptic curve which are given in
 **         projective coordinates and returns the result again in projective coordinates.
 **
 ** \param[out]    result  Pointer to an Edwards curve point where the result of the
 **                        addition will be stored in projective coordinates.
 ** \param[in]     addend1 Pointer to an Edwards curve point given in projective coordinates
 **                        which should be added. This parameter may Point to the same memory location
 **                        as the result point "result".
 ** \param[in]     addend2 Pointer to an Edwards curve point given in projective coordinates
 **                        which should be added. This parameter may point to the same memory location
 **                        as the result point "result".
 ** \param[in,out] tmp     Pointer to a buffer which is used as temporary storage for the calculation.
 ** \param[in]     edCtx   Pointer the the context.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION == STD_ON) */

/** \brief  This function converts a point given in projective coordinates to the same point in affine.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 ** \param[in]      edCtx      Pointer the the context.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF == STD_ON) */

/*----- ECC NIST --------------------------------------------------------------------------------*/
/** \brief    Fast reduction modulo the polynomial of Elliptic Curve secp256r1
 *
 *            This function performs the fast reduction modulo by using the reduction polynomial
 *            which is the base of the elliptic curve secp256r1 / NIST P-256.
 *
 * \param[in,out] value  Pointer to the start of an array which holds the number to be reduced.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the conversion.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP256FastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);
/** \brief    Fast reduction modulo the polynomial of Elliptic Curve secp384r1
 *
 *            This function performs the fast reduction modulo by using the reduction polynomial
 *            which is the base of the Elliptic Curve NIST polynomial P-384 / SecP384r1
 *
 * \param[in,out] value  Pointer to the start of an array which holds the number to be reduced.
 * \param[in,out] ctxPtr Pointer to a context which holds the current state of the conversion.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECP384FastReduction
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Point multiplication.
 *
 *         This function multiplies a Point on an Elliptic Curve which is given in
 *         projective coordinates with an integer and returns the result again in
 *         projective coordinates. The multiplication is performed
 *         in slices and the current slice is stored in the given context.
 *
 * \param[out]    result       Pointer to an Elliptic Curve Point where the result of the
 *                             multiplication will be stored in projective coordinates.
 * \param[in]     Point        Pointer to an Elliptic Curve Point given in projective coordinates
 *                             which should multiplied. This parameter must not Point to the same
 *                             memory location as the result "result".
 * \param[in]     Multiplicand Pointer an integer with which the Point should be multiplied.
 * \param[in,out] tmp1         An array which contains a buffer for a temporary number during
 *                             multiplication.
 * \param[in,out] tmp2         An array which contains a buffer for a temporary number during
 *                             multiplication.
 * \param[in,out] tmp3         An array which contains a buffer for a temporary number during
 *                             multiplication.
 * \param[in,out] tmp4         An array which contains a buffer for a temporary number during
 *                             multiplication.
 * \param[in,out] ctxPtr       Pointer to a context which holds the current state of the
 *                             multiplication.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointMultiplication
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2CONST(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) multiplicand,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Point addition
 *
 *         This function adds two points on an Elliptic Curve which are given in
 *         projective coordinates and returns the result again in
 *         projective coordinates. The addition is performed in slices and the
 *         current slice is stored in the given context.
 *
 * \param[in,out] result  Pointer to an Elliptic Curve Point where the result of the
 *                        addition will be stored in projective coordinates.
 * \param[in]     addend1 Pointer to an Elliptic Curve Point given in projective coordinates
 *                        which should be added. This parameter may Point to the
 *                        same memory location as the result Point "result".
 * \param[in]     addend2 Pointer to an Elliptic Curve Point given in projective coordinates
 *                        which should be added. This parameter may Point to the
 *                        same memory location as the result Point "result".
 * \param[in,out] tmp1    An array which contains a buffer for a temporary number during addition.
 * \param[in,out] tmp2    An array which contains a buffer for a temporary number during addition.
 * \param[in,out] tmp3    An array which contains a buffer for a temporary number during addition.
 * \param[in,out] tmp4    An array which contains a buffer for a temporary number during addition.
 * \param[in,out] ctxPtr  Pointer to a context which holds the current state of the addition.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECPointAddition
(
    P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) result,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend1,
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) addend2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3,
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4,
    P2VAR(Crypto_xVIx_xAIx_ECCtxType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) ctxPtr
);

/** \brief Check if the input Point is at infinity.
 *
 * \param[in] Point  Point to be checked.
 *
 * \returns If Point is at infinity
 * \retval FALSE     Point is not at infinity.
 * \retval TRUE      Point is at infinity.
 *
 * \Reentrancy{Nonreentrant}
 * \Synchronicity{Synchronous/Asynchronous}
 *
 */
extern FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ECProjectivePointOfInfinity
(
  P2CONST(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point
);
#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_LIB_ECC_H */

/*==================[end of file]=================================================================*/

