/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EDDSA_H_
#define CRY_EDDSA_H_

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>
#include <Cry_LN.h>
#include <Cry_Common.h>
#include <Cry_EdDSAConfig.h>

#if (CRY_EdDSA_ENABLED == STD_ON)

/*==================[Macros]================================================*/

#if (defined CRY_EdDSA_NUM_LEN_WORDS)
#error CRY_EdDSA_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible stored number. This length depends on the configured edwards curves.
 */
#define CRY_EdDSA_NUM_LEN_WORDS                             \
(                                                           \
   (Cry_LNWordType)                                         \
   (                                                        \
      Cry_LNNumberLen(CRY_EdDSA_NUMBER_LEN) +               \
      (Cry_LNWordType)1UL                                   \
   )                                                        \
)

#if (defined CRY_EdDSA_TEMP_LEN_WORDS)
#error CRY_EdDSA_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary number. This length depends on the
 *         configured edwards curves.
 */
#define CRY_EdDSA_TEMP_LEN_WORDS                        \
(                                                       \
   (Cry_LNWordType)                                     \
   (                                                    \
      (CRY_EdDSA_NUM_LEN_WORDS * (Cry_LNWordType)2UL) - \
      (Cry_LNWordType)1UL                               \
   )                                                    \
)


/** \brief The length of the Context string for Ed25519ph. */
#if (defined CRY_EDDSA_DOM_LEN)
#error CRY_EDDSA_DOM_LEN is already defined
#endif
#define CRY_EDDSA_DOM_LEN 34U

/*==[Types]===================================================================*/

/** \brief A point on an edwards curve. */
typedef struct
{
  /** \brief The x-coordinate of the point on the curve. */
  Cry_LNWordType xValue[CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief The y-coordinate of the point on the curve. */
  Cry_LNWordType yValue[CRY_EdDSA_TEMP_LEN_WORDS];

  /** \brief If the point is in projective coordinates, this is the z-coordinate of the point. */
  Cry_LNWordType zValue[CRY_EdDSA_TEMP_LEN_WORDS];
}
Cry_EdDSAPointType;

/** \brief Additional information for edwards curve. */
typedef struct
{
  /** \brief The base point. */
  Cry_EdDSAPointType P;

  /** \brief An integer n with c <= n <= b. */
  Cry_LNWordType   nValue[CRY_EdDSA_NUM_LEN_WORDS];

  /** \brief A non-square element d of G(p). */
  Cry_LNWordType   dValue[CRY_EdDSA_NUM_LEN_WORDS];

  /** \brief The order of G(p). */
  Cry_LNWordType   lValue[CRY_EdDSA_NUM_LEN_WORDS];

  /** \brief An integer b with 2^(b-1) > Prime. EdDSA public keys have exactly b
   *         bits, and EdDSA signatures have exactly 2*b bits.
   */
  uint16           bValue;

  /** \brief The integer in c = {2, 3} */
  uint16           c;
}
Cry_EdDSAInfoType;

/** \brief Internal states of the point addition */
typedef enum
{
  /** \brief Start of the addition; check if addend1 or addend2 are at infinity */
  CRY_EdDSA_ADD_S_START,

  /** \brief Calculate C, D and E */
  CRY_EdDSA_ADD_S_CDE,

  /** \brief Calculate Z1 * Z2 */
  CRY_EdDSA_ADD_S_5,

  /** \brief Calculate B, F, G */
  CRY_EdDSA_ADD_S_6,

  /** \brief Calculate final Z3 */
  CRY_EdDSA_ADD_S_7,

  /** \brief Calculate X3 = A * F */
  CRY_EdDSA_ADD_S_8,

  /** \brief Calculate B */
  CRY_EdDSA_ADD_S_9,

  /** \brief Calculate final X3 */
  CRY_EdDSA_ADD_S_10,

  /** \brief Calculate A * G */
  CRY_EdDSA_ADD_S_11,

  /** \brief Calculate final Y3 */
  CRY_EdDSA_ADD_S_12
}
Cry_EdDSAAdditionStateType;

/** \brief Intermediary internal states for the point addition */
typedef enum
{
  /** \brief Calculate X1 * X2 */
  CRY_EdDSA_ADD_S_1,

  /** \brief Calculate Y1 * Y2 */
  CRY_EdDSA_ADD_S_2,

  /** \brief Calculate D * X1 * X2 */
  CRY_EdDSA_ADD_S_3,

  /** \brief Calculate X1 * X2 * D * Y1 * Y2 */
  CRY_EdDSA_ADD_S_4
}
Cry_EdDSAAdditionCDEStateType;

/** \brief Internal states of the point doubling */
typedef enum
{
  /** \brief Start of point doubling and calculate X1 + Y1 */
  CRY_EdDSA_DOUB_S_START,

  /** \brief Calculate X1 * Y1 */
  CRY_EdDSA_DOUB_S_1,

  /** \brief Calculate Y1 * Y1 */
  CRY_EdDSA_DOUB_S_2,

  /** \brief Calculate F = E + D */
  CRY_EdDSA_DOUB_S_3,

  /** \brief Calculate (X1 + Y1)^2 */
  CRY_EdDSA_DOUB_S_4,

  /** \brief Calculate final Y3 value */
  CRY_EdDSA_DOUB_S_5,

  /** \brief Calculate J */
  CRY_EdDSA_DOUB_S_6,

  /** \brief Calculate final Z3 value */
  CRY_EdDSA_DOUB_S_7,

  /** \brief Calculate final X3 value */
  CRY_EdDSA_DOUB_S_8
}
Cry_EdDSADoublingStateType;

/** \brief Internal state of point multiplication  */
typedef enum
{
  /** \brief Start of multiplication; set the point to infinity */
  CRY_EdDSA_MULT_S_START,

  /** \brief Verify if the multiplicand is 0 */
  CRY_EdDSA_MULT_S_LOOP,

  /** \brief Calculate the double of the point */
  CRY_EdDSA_MULT_S_DOUBLE,

  /** \brief point addition */
  CRY_EdDSA_MULT_S_ADD
}
Cry_EdDSAMultiplicationStateType;

/** \brief Internal states of the coordinate conversion. */
typedef enum
{
  /** \brief The start of the coordinate conversion.*/
  CRY_EdDSA_CONV_S_START,

  /** \brief Calculate LN inversion. */
  CRY_EdDSA_CONV_S_INVERT,

  /** \brief Calculate X^2. */
  CRY_EdDSA_CONV_S_X,

  /** \brief Calculate Y^2. */
  CRY_EdDSA_CONV_S_Y
}
Cry_EdDSAConvertProj2AffStateType;

/** \brief Internal state of decoding */
typedef enum
{
  /** \brief Start of point decoding */
  CRY_EdDSA_DEC_S_START,

  /** \brief Convert from byte array to big int */
  CRY_EdDSA_DEC_S_1,

  /** \brief Prepare some of the curve parameters */
  CRY_EdDSA_DEC_S_2,

  /** \brief Calculate (u / v) ^ ((p + 3) / 8) */
  CRY_EdDSA_DEC_S_3,

  /** \brief Calculate root candidate */
  CRY_EdDSA_DEC_S_4,

  /** \brief Calculate tmp6^2 */
  CRY_EdDSA_DEC_S_5,

  /** \brief Calculate x = (u/v) ^ ((p+3) / 8) */
  CRY_EdDSA_DEC_S_6,

  /** \brief Calculate tmp3 = xValue^2 */
  CRY_EdDSA_DEC_S_7,

  /** \brief Calculate tmp3 = v * xValue^2 */
  CRY_EdDSA_DEC_S_8,

  /** \brief Calculate tmp5 = Primzahl - 1 */
  CRY_EdDSA_DEC_S_9,

  /** \brief Calculate the modulo exponentiation  */
  CRY_EdDSA_DEC_S_10,

  /** \brief Calculate xValue = xValue * (2^tmp5) */
  CRY_EdDSA_DEC_S_11,

  /** \brief Finish the decoding */
  CRY_EdDSA_DEC_S_12
}
Cry_EdDSADecodingStateType;

/** \brief Internal state of parameters calculation for point decoding */
typedef enum
{
  /** \brief Calculate (y^2 - 1) */
  CRY_EdDSA_DEC_S_INT_2,

  /** \brief Calculate (d * (y^2)) + 1 */
  CRY_EdDSA_DEC_S_P_3,

  /** \brief Calculate v^2 */
  CRY_EdDSA_DEC_S_P_4,

  /** \brief Calculate v^3 */
  CRY_EdDSA_DEC_S_P_5,

  /** \brief Calculate ((y^2) - 1) * v^3 */
  CRY_EdDSA_DEC_S_P_6,

  /** \brief Calculate v^7 */
  CRY_EdDSA_DEC_S_P_7,

  /** \brief Calculate (u * v^7)^((p - 5) / 8)  */
  CRY_EdDSA_DEC_S_P_8
} Cry_EdDSADecodingParamsStateType;

/** \brief Internal state of point encoding */
typedef enum
{
  /** \brief Start of point encoding */
  CRY_EdDSA_ENC_S_START,

  /** \brief Y point encoding */
  CRY_EdDSA_ENC_S_1,

  /** \brief X point encoding */
  CRY_EdDSA_ENC_S_2
}
Cry_EdDSAEncodingStateType;

/** \brief The context of the edwards curve functions. */
typedef struct
{
  /** \brief Context of underlying arithmetic functions. */
   Cry_LNCtxType                   LNCtx;

  /** \brief Current bit of the multiplicand in the multiplication. */
   Cry_LNWordType                  CurrentBit;

  /** \brief Internal state of the function Cry_EdDSAPPointMultiplication(). */
   Cry_EdDSAMultiplicationStateType  MultiplicationState;

  /** \brief Internal state of the function Cry_EdDSAPPointConvertProj2Aff(). */
   Cry_EdDSAConvertProj2AffStateType ConvertProj2AffState;

  /** \brief Intermediary internal state of the function Cry_EdDSAPPointDecoding(). */
   Cry_EdDSADecodingParamsStateType  DecodingParamsState;

  /** \brief Internal state of the function Cry_EdDSAPPointDecoding(). */
   Cry_EdDSADecodingStateType        DecodingState;

  /** \brief Internal state of the function Cry_EdDSAPPointEncoding(). */
   Cry_EdDSAEncodingStateType        EncodingState;

  /** \brief Intermediary internal state of the function Cry_EdDSAPPointAddition(). */
   Cry_EdDSAAdditionStateType        AdditionCDEState;

  /** \brief Internal state of the function Cry_EdDSAPPointAddition(). */
   Cry_EdDSAAdditionStateType        AdditionState;

  /** \brief Internal state of the function Cry_EdDSAPPointDoubling(). */
   Cry_EdDSADoublingStateType        DoublingState;

   /** \brief The least significant bit of the X coordinate. */
   uint8                             X_0;
}
Cry_EdDSACtxType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Additional information for Edwards curve. */
extern CONST(Cry_EdDSAInfoType,          CRY_CONST) Cry_EdDSACurveInfo;

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief Context string for Ed25519ph. */
extern CONST(uint8, CRY_CONST) Cry_EdDSADOM[CRY_EDDSA_DOM_LEN];

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Fast reduction modulo the polynomial of Edwards curve
 **
 **         This function performs the fast reduction modulo the reduction polynomial
 **         which is the base of the Edwrads curve 25519.
 **
 **         It is based on the following observations:
 **
 **         Let "value" have the binary notation
 **
 **         value = c509*(2^509) + c508*(2^508) + ... + c1*2 + c0.
 **
 **         where each cX is either 0 or 1. Then we can write value as the sum
 **
 **         value = A1*(2^255) + A2
 **
 **         with the two 160-bit integers
 **
 **         A1 = c509*(2^254) + c508*(2^253) + ... + c256*2 + c255 and
 **         A2 = c254*(2^254) + c253*(2^253) + ... + c1*2   + c0.
 **
 **         We know that
 **
 **         p = 2^255 - 19.
 **
 **         From this follows that
 **
 **         2^255 = 2^4 + 3 (mod p)
 **
 **         and therefore
 **
 **         x*(2^255) = x*(2^4 + 3) (mod p)
 **
 **         for all x. But this means that
 **
 **         value = A1*(2^255)      + A2 (mod p)
 **               = A1*(2^4 + 3)    + A2 (mod p)
 **               = A1*(2^4) + 3*A1 + A2 (mod p).
 **
 **         A1 + A2 (mod p) can be computed easily because A1 and A2 are both
 **         smaller than p. Now we want to reduce A1*(2^4) further. For this we
 **         write:
 **
 **         A1*(2^4) = B
 **
 **         A1*(2^4) = B1*(2^255) + B2
 **
 **         Again we use the congruence from above to get
 **
 **         A1*(2^4) = B1*(2^4) + 3*B1 + B2 (mod p)
 **
 **
 **         Everything taken together this yields
 **
 **         value =  3*A1 + A2 + B1*(2^4) + 3*B1 + B2 (mod p)
 **
 **         where all summands are smaller than p. We use this last congruence to
 **         compute the reduction.
 **
 ** \param[in]  value   Pointer to the start of an array which holds the number to be reduced.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAFastReduction
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) value
);

/** \brief  Start the Encoding.
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointEncoding() is called with that context, it will perform a point encoding.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointEncoding() can be called with it.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPointEncodingStart
(
  P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  This function encodes a point.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the
 **                    encoding.
 **
 ** \param[in] value   The point to be encoded.
 **
 ** \param[in] tmp     an array where buffers is used as temporary storage
 **                    during the multiplication.
 **
 ** \param[out] result Pointer to an edwards curve point where the result of the
 **                    encoding will be stored in projective coordinates.
 **
 ** \param[in] tmp1Array A byte-array which is used as a buffer during signature generation.
 **
 ** \param[in] tmp1ArrayLength The length of the byte-array.
 **
 ** \param[in] resultLength Length of the result.
 **
 ** \returns boolean
 **
 ** \retval FALSE     The encoding has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The encoding has finished. Now, "result" contains the result
 **                   of the encoding.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_EdDSAPointEncoding
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(uint8,              AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(uint8,              AUTOMATIC, CRY_APPL_DATA) tmp1Array,
  uint32                                              tmp1ArrayLength,
  uint32                                              resultLength
);

/** \brief  Calculate private scalar for an Edwards-curve
 **
 **         This function is implemented to calculate the secret scalar for an Edwards-curve.
 **         scalar = 2^n + sum(2^i * h_i) for c <= i < n
 **
 ** \param[out] result          Pointer to an edwards curve point where the result will be stored.
 **
 ** \param[in]  hashPtr         Pointer to the hash result.
 **
 ** \param[in]  hashPtrLength   Pointer to the hash length.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPrivateScalar
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(uint8,          AUTOMATIC, CRY_APPL_DATA) hashPtr,
  uint32                                          hashPtrLength
);

/** \brief  Start point addition
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointAddition() is called with that context, it will perform
 **         a point addition.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointAddition() can be called with it.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionStart
(
   P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  point addition
 **
 **         This function adds two points on an elliptic curve which are given in
 **         projective coordinates and returns the result again in
 **         projective coordinates. The addition is performed in slices and the
 **         current slice is stored in the given context.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the
 **                    addition. Before the first call of this function, the context has to
 **                    be initialized by a call to Cry_EdDSAPointAdditionStart().
 **
 ** \param[out] result Pointer to an edwards curve point where the result of the
 **                    addition will be stored in projective coordinates.
 **
 ** \param[in] addend1 Pointer to an edwards curve point given in projective coordinates
 **                    which should be added. This parameter may point to the same memory location
 **                    as the result point "result".
 **
 ** \param[in] addend2 Pointer to an edwards curve point given in projective coordinates
 **                    which should be added. This parameter may point to the same memory location
 **                    as the result point "result".
 **
 ** \param[in] tmp     an array where buffers is used as temporary storage
 **                    during the multiplication.
 **
 ** \returns boolean
 **
 ** \retval FALSE     The addition has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The addition has finished. Now, "result" contains the result
 **                   of the addition.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_EdDSAPointAddition
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Start Point multiplication.
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointMultiplication() is called with that context, it will perform
 **         a point multiplication.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointMultiplication() can be called with it.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPointMultiplicationStart
(
   P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  Point multiplication.
 **
 **         This function multiplies a point on an edwards curve which is given in
 **         projective coordinates with an integer and returns the result again in
 **         projective coordinates. The multiplication is performed
 **         in slices and the current slice is stored in the given context.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the
 **                    multiplication. Before the first call of this function, the context has to
 **                    be initialized by a call to Cry_EdDSAPointMultiplicationStart().
 **
 ** \param[out] result Pointer to an edwards curve point where the result of the
 **                    multiplication will be stored in projective coordinates.
 **
 ** \param[in] point   Pointer to an edwards curve point given in projective coordinates
 **                    which should multiplied. This parameter must not point to the same
 **                    memory location as the result "result".
 **
 ** \param[in] multiplicand Pointer an integer with which the point should be multiplied.
 **
 ** \param[in] tmp     an array where buffers is used as temporary storage
 **                    during the multiplication.
 **
 ** \returns boolean
 **
 ** \retval FALSE     The multiplication has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The multiplication has finished. Now, "result" contains the result
 **                   of the multiplication.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_EdDSAPointMultiplication
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2CONST(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) multiplicand,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Start the point conversion.
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointConvertProj2Aff() is called with that context, it will perform
 **         a point conversion.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointConvertProj2Aff() can be called with it.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPointConvertProj2AffStart
(
   P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  point conversion.
 **
 **         This function converts a point given in projective coordinates to the
 **         same point in affine coordinates. The conversion is performed
 **         in slices and the current slice is stored in the given context.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the conversion.
 **
 ** \param[in] point   Pointer to an edwards curve point given in projective coordinates
 **                    which should converted.
 **
 ** \param[in] tmp1    Pointer to a buffer is used as temporary storage during the conversion.
 **
 ** \param[in] tmp2    Pointer to a buffer is used as temporary storage during the conversion.
 **
 ** \param[in] tmp3    Pointer to a buffer is used as temporary storage during the conversion.
 **
 ** \returns boolean
 **
 ** \retval FALSE     The conversion has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The conversion has finished. Now, "point" contains the result
 **                   of the conversion.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_EdDSAPointConvertProj2Aff
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp1,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp2,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp3
);

/** \brief  Start point decoding
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointDecoding() is called with that context, it will perform
 **         a point decoding.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointDecoding() can be called with it.
 **
 **/
FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingStart
(
    P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  point decoding.
 **
 **         This function decode a given byte-array in a point an edwards curve in which
 **         the result is in projective coordinates.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[out] result Pointer to an edwards curve point where the result of the
 **                    decoding will be stored in projective coordinates.
 **
 ** \param[in] tmp     an array where buffers is used as temporary storage
 **                    during the multiplication.
 **
 *  \param[out] resultPtr Verification result.
 **
 ** \param[in] value   Pointer to an edwards curve point given in projective coordinates
 **                    which should decoded. This parameter must not point to the same
 **                    memory location as the result "result".
 **
 ** \param[in] valueLength Length of point to be decoded.
 **
 ** \returns boolean
 **
 ** \retval FALSE     The decoding has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The decoding has finished. Now, "result" contains the result
 **                   of the decoding.
 **
 **/
FUNC(boolean, CRY_CODE) Cry_EdDSAPointDecoding
(
  P2VAR(Cry_EdDSACtxType,       AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,     AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,         AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Csm_VerifyResultType,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint8,                  AUTOMATIC, CRY_APPL_DATA) value,
  uint32                                                  valueLength
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* (CRY_EdDSA_ENABLED == STD_ON) */

#endif /* CRY_EDDSA_H_ */
