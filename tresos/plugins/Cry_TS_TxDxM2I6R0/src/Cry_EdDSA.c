/* --------{ EB Automotive C Source File }-------- */

/* This specification of EdDSA relies on [RFC 8032]. The RFC defines EdDSA for
   a 128 bit security level using edwards25519. */

/*==[Includes]================================================================*/
#include <Std_Types.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>

#if (CRY_EdDSA_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Calculate X^2 and do the fast reduction
 **
 ** \param[in] ctxPtr          Pointer to a context which holds the current state.
 **
 ** \param[in] checkHighestBit Pointer a to buffer on which the highest bit will be checked.
 **
 ** \param[in] valueToDouble   Pointer a to buffer that will be doubled.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStatePowerAndReduce
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) checkHighestBit,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) valueToDouble
);

/** \brief  Calculate result of (u * v^7) ^ ((p - 5) / 8)
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state.
 **
 ** \param[in] base    Pointer to the base which should be exponentiated.
 **
 ** \param[in] result  Pointer to the location where the result is stored.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ1
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) base,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) result
);

/** \brief  Calculate x = (u/v) ^ ((p + 3) / 8)
 **         This can be done using the following equation:
 **         (u * v^3) * (u * v^7) ^ ((p - 5) / 8)
 **
 ** \param[in] ctxPtr          Pointer to a context which holds the current state.
 **
 ** \param[out] point          Pointer to an Edwards curve point where the result will be stored.
 **
 ** \param[in] multiplicand    Pointer to the result of (u * v^3).
 **
 ** \param[in] multiplicator   Pointer to the result of (u * v^7) ^ ((p - 5) / 8).
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ2
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) multiplicand,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) multiplicator
);

/** \brief  Calculate the square of xValue
 **
 ** \param[in] ctxPtr    Pointer to a context which holds the current state.
 **
 ** \param[out] point    Pointer to an Edwards curve point where the result will be stored.
 **
 ** \param[in] squareOfX Pointer to the result of the squaring of xValue.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ3
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) squareOfX
);

/** \brief  Select the correct result for calculate the square root of xValue
 **
 ** \param[in] ctxPtr    Pointer to a context which holds the current state.
 **
 ** \param[in] tmp       Pointer to a buffer which will be used as temporary storage.
 **
 ** \param[out] result   Pointer to an Edwards curve point where the result will be stored.
 **
 ** \param[out] Finished Pointer to a flag that indicates if the operation is finished.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ4
(
  P2VAR(Cry_EdDSACtxType,       AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,         AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Csm_VerifyResultType,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(boolean,                AUTOMATIC, CRY_APPL_DATA) finished
);

/** \brief  Calculate 2^((p - 1) / 4)
 **
 ** \param[in] ctxPtr   Pointer to a context which holds the current state.
 **
 ** \param[out] point   Pointer to an Edwards curve point where the result will be stored.
 **
 ** \param[in] base     Pointer to the base which should be exponentiated.
 **
 ** \param[in] exponent Pointer to the location where the result of ((p - 1) / 4) is stored.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ5
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) base,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) exponent
);

/** \brief  Calculate tmp5 = Primzahl - 1
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result will be stored.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParams
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Check if either of the input points are at infinity.
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    addition will be stored in projective coordinates.
 **
 ** \param[in]  addend1 Pointer to an Edwards curve point given in projective coordinates
 **                     which should be added. This parameter may point to the same memory location
 **                     as the result point "result".
 **
 ** \param[in]  addend2 Pointer to an Edwards curve point given in projective coordinates
 **                     which should be added. This parameter may point to the same memory location
 **                     as the result point "result".
 **
 ** \param[out] Finished Pointer to a flag that indicates if the operation is finished.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCheckInfinity
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(boolean,              AUTOMATIC, CRY_APPL_DATA) finished
);

/** \brief  Calculate A^2
 **
 ** \param[in]  ctxPtr Pointer to a context which holds the current state of the addition.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateA2
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate Z^3
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    addition will be stored in projective coordinates.
 **
 ** \param[in]  addend1 Pointer to an Edwards curve point given in projective coordinates
 **                     which should be added. This parameter may point to the same memory location
 **                     as the result point "result".
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateZ3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate A * G
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateAG
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate temporary point
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateInterimTmp5
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate A * F
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    addition will be stored in projective coordinates.
 **
 ** \param[in]  addend2 Pointer to an Edwards curve point given in projective coordinates
 **                     which should be added. This parameter may point to the same memory location
 **                     as the result point "result".
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateAF
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate X3
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    addition will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateFinalX3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate Z3
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the doubling.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    doubling will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateZ3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate H
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the doubling.
 **
 ** \param[out] value  Pointer to an Edwards curve point where the result of the
 **                    doubling will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateH
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate B
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the doubling.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateB
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate E and F
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the doubling.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateEF
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate xValue * (2^tmp5)
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    decoding will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingXValue2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate the exponentiation
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingExp
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);


/** \brief  Calculate Y ^ 2
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    decoding will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsY2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate D * (Y ^ 2)
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[out] result Pointer to an Edwards curve point where the result of the
 **                    decoding will be stored in projective coordinates.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsDY2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate V ^ 2
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsV2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Calculate V ^ 3
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsV3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Do the state managemetn for the point decoding
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the decoding.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingStateMngmt
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  Calculate C, D and E
 **
 ** \param[in] ctxPtr  Pointer to a context which holds the current state of the addition.
 **
 ** \param[in] addend1 Pointer to an Edwards curve point given in projective coordinates
 **                    which should be added.
 **
 ** \param[in] addend2 Pointer to an Edwards curve point given in projective coordinates
 **                    which should be added.
 **
 ** \param[in] tmp     Pointer to a buffer which will be used as temporary storage.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateCDE
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

/** \brief  Reduce point A
 **
 ** \param[in]   tmp    Pointer to a buffer which will be used as
 **                     temporary storage during the reduction.
 **
 ** \param[out]  value  Value to be reduced.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAFastReductionCompA
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) value
);

/** \brief  Reduce point B
 **
 ** \param[out] tmp   Value to be reduced.
 **
 ** \param[in]  temp1 Pointer to a buffer which will be used as temporary storage
 **                   during the reduction.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAFastReductionCompB
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA)   tmp,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA)   temp1
);

/** \brief  Check if the input point is at infinity.
 **
 ** \param[in]  value   Point to be checked.
 **
 ** \returns boolean
 **
 ** \retval FALSE     Point is not at infinity.
 **
 ** \retval TRUE      Point is at infinity.
 **
 **/
static FUNC(boolean, CRY_CODE) Cry_EdDSAProjectivePointOfInfinity
(
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point
);

/** \brief  Start point doubling
 **
 **         This function modifies the given context such that, when the function
 **         Cry_EdDSAPointDoubling() is called with that context, it will perform
 **         a point doubling.
 **
 ** \param[in] ctxPtr  Pointer to a context which will be initialized such that
 **                    the function Cry_EdDSAPointDoubling() can be called with it.
 **
 **/
static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingStart
(
   P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
);

/** \brief  Point doubling
 **
 **         This function doubles a point on an Edwards curve which is given in
 **         projective coordinates and returns the result in projective coordinates.
 **         The doubling is performed in slices and the current slice is stored in the
 **         given context.
 **
 ** \param[inout] ctxPtr Pointer to a context which holds the current state of the
 **                      doubling. Before the first call of this function, the context has to
 **                      be initialized by a call to Cry_EdDSAPointDoublingStart().
 **
 ** \param[out]   result Pointer to an Edwards curve point where the result of the
 **                      doubling will be stored in projective coordinates.
 **
 ** \param[in]    value  Pointer to an Edwards curve point given in projective coordinates
 **                      which should be doubled.
 **
 ** \param[in]    tmp    Pointer to a buffer which will be used as temporary storage
 **
 ** \returns boolean
 **
 ** \retval FALSE     The doubling has not yet finished. It has to be called again with
 **                   the same parameters.
 **
 ** \retval TRUE      The doubling has finished. Now, "result" contains the result
 **                   of the doubling.
 **
 **/
static FUNC(boolean, CRY_CODE) Cry_EdDSAPointDoubling
(
   P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
   P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
   P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
   P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Prime number of Edwards curve.
 **        This is the prime number which creates the prime field on which the
 **        Edwards curve of the standard "SEC 2" is based.
 **/
STATIC CONST(Cry_LNWordType, CRY_CONST) Cry_EdDSAPrime[] =
{
  0x00000008UL,
  0xFFFFFFEDUL,
  0xFFFFFFFFUL,
  0xFFFFFFFFUL,
  0xFFFFFFFFUL,
  0xFFFFFFFFUL,
  0xFFFFFFFFUL,
  0xFFFFFFFFUL,
  0x7FFFFFFFUL
};

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief This array contains the curve information for the
 **        Edwards curve P-255.
 **/
CONST(Cry_EdDSAInfoType, CRY_CONST) Cry_EdDSACurveInfo =
{
  /* point */
  {
    /* X */
    {
             0x8UL,
      0x8f25d51aUL,
      0xc9562d60UL,
      0x9525a7b2UL,
      0x692cc760UL,
      0xfdd6dc5cUL,
      0xc0a4e231UL,
      0xcd6e53feUL,
      0x216936d3UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL
    },
    /* Y */
    {
            0x8UL,
      0x66666658UL,
      0x66666666UL,
      0x66666666UL,
      0x66666666UL,
      0x66666666UL,
      0x66666666UL,
      0x66666666UL,
      0x66666666UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL,
             0x0UL
    },
    /* Z */
    {
      0x1UL,
      0x1UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL
    }
  },
  /* n */
  {
      0x1UL,
     0xFEUL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL,
      0x0UL
  },
  /* d */
  {
           0x8UL,
    0x135978a3UL,
    0x75eb4dcaUL,
    0x4141d8abUL,
    0x00700a4dUL,
    0x7779e898UL,
    0x8cc74079UL,
    0x2b6ffe73UL,
    0x52036ceeUL
  },
  /* L */
  {
           0x8UL,
    0x5cf5d3edUL,
    0x5812631aUL,
    0xa2f79cd6UL,
    0x14def9deUL,
    0x00000000UL,
    0x00000000UL,
    0x00000000UL,
    0x10000000UL
  },
  /* b */
  256U,
  /* c */
  3U
};

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/**
 * \brief Context string for Ed25519ph.
 *
 * This variable is needed for Ed25519ph and contains:
 * The ASCII string "SigEd25519 no Ed25519
 * collisions" is converted into 32 octets. 0100 are 2 octets.
 * Hence, the variable dom consists of 34 octets.
 *
 */
CONST(uint8, CRY_CONST) Cry_EdDSADOM[CRY_EDDSA_DOM_LEN] =
{
  0x53, 0x69, 0x67, 0x45, 0x64, 0x32, 0x35, 0x35, 0x31, 0x39, 0x20, 0x6E, 0x6F,
  0x20, 0x45, 0x64, 0x32, 0x35, 0x35, 0x31, 0x39, 0x20, 0x63, 0x6F, 0x6C, 0x6C,
  0x69, 0x73, 0x69, 0x6F, 0x6E, 0x73, 0x01, 0x00
};

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(void, CRY_CODE) Cry_EdDSAPointEncodingStart
(
  P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
  ctxPtr->EncodingState = CRY_EdDSA_ENC_S_START;
}

FUNC(boolean, CRY_CODE) Cry_EdDSAPointEncoding
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(uint8,              AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(uint8,              AUTOMATIC, CRY_APPL_DATA) tmp1Array,
  uint32                                              tmp1ArrayLength,
  uint32                                              resultLength
)
{
 boolean Finished;
 uint8   X_0;

 Finished = FALSE;

 switch(ctxPtr->EncodingState)
 {

   case CRY_EdDSA_ENC_S_START:
     Cry_EdDSAPointConvertProj2AffStart(ctxPtr);
     ctxPtr->EncodingState = CRY_EdDSA_ENC_S_1;
     break;

   case CRY_EdDSA_ENC_S_1:
     if (Cry_EdDSAPointConvertProj2Aff(ctxPtr,
                                       value,
                                       &tmp[0U * CRY_EdDSA_TEMP_LEN_WORDS],
                                       &tmp[1U * CRY_EdDSA_TEMP_LEN_WORDS],
                                       &tmp[2U * CRY_EdDSA_TEMP_LEN_WORDS]
                                      ) == TRUE)
     {
       /* convert the yValue in little endian byte array */
       /* CHECK: NOPARSE */
       /* The 'else' branch is unreachable as we have enough memory allocated in the context
        * to store the byte representation of the LN. */
       if (Cry_LNNumberToLEByteArray(value->yValue, result, &resultLength) == E_OK)
       {
         ctxPtr->EncodingState = CRY_EdDSA_ENC_S_2;
       }
       /* CHECK: PARSE */
     }
     break;

   case CRY_EdDSA_ENC_S_2:

     /* CHECK: NOPARSE */
     /* This branch is unreachable as we have enough memory allocated in the context
      * to store the byte representation of the LN. */
     if (Cry_LNNumberToLEByteArray(value->xValue, tmp1Array, &tmp1ArrayLength) == E_OK)
     /* CHECK: PARSE */
     {
       /* the least significant bit of the x-coordinate */
       X_0 = (uint8)(tmp1Array[0U] & 0x01U);

       if(X_0 != 0U)
       {
         result[(Cry_EdDSACurveInfo.bValue >> 3U) - 1U] |= (uint8)((uint8)X_0 << 7U);
       }

       Finished = TRUE;
     }
     break;

   /* CHECK: NOPARSE */
   /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
   default:
     {
       Finished = TRUE;
       break;
     }
   /* CHECK: PARSE */
 }

 return Finished;
}

FUNC(void, CRY_CODE) Cry_EdDSAPrivateScalar
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(uint8,          AUTOMATIC, CRY_APPL_DATA) hashPtr,
  uint32                                          hashPtrLength
)
{
  /* clear the first 3 bits */
  hashPtr[0U] &= (uint8)0xf8U;

  /* clear the highest bit of the last octet from the first hash half */
  hashPtr[31U] &=  (uint8)(~(uint8)((uint8)1U << 7U));

  /* set the second highest bit of the final octet from the first hash half */
  hashPtr[31U] |= (uint8)(1U << 6U);

  /* Set the expected length of the Long Number before converting the bytearray
   * to a little-endian integer */
  result[0U] = (Cry_LNWordType)
                           ((Cry_LNWordType)((Cry_LNWordType)Cry_EdDSACurveInfo.bValue >> 5U) + 1U);

  /* copy the Hashresult to result */
  (void)Cry_LNLEByteArrayToNumber(hashPtr,
                                  hashPtrLength,
                                  result,
                                  result[0U]
                                 );
}

FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionStart
(
    P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
   ctxPtr->AdditionState = CRY_EdDSA_ADD_S_START;
}

FUNC(boolean, CRY_CODE) Cry_EdDSAPointAddition
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  boolean Finished;

  Finished = FALSE;

  switch (ctxPtr->AdditionState)
  {
    case CRY_EdDSA_ADD_S_START:
      Cry_EdDSAPointAdditionCheckInfinity(ctxPtr,
                                          result,
                                          addend1,
                                          addend2,
                                          &Finished
                                         );
      break;

    case CRY_EdDSA_ADD_S_CDE:
      /* calculate C, D and E */
      Cry_EdDSAPointAdditionCalculateCDE(ctxPtr,
                                         addend1,
                                         addend2,
                                         tmp
                                        );
      break;

    case CRY_EdDSA_ADD_S_5:
      /* A: tmp4 = Z1 * Z2 */
      if (Cry_LNMultiplyNumbers(&tmp[3U * CRY_EdDSA_TEMP_LEN_WORDS],
                                addend1->zValue,
                                addend2->zValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[3U * CRY_EdDSA_TEMP_LEN_WORDS]);

        Cry_LNMultiplyStart(&ctxPtr->LNCtx);

        ctxPtr->AdditionState = CRY_EdDSA_ADD_S_6;
      }
      break;

    case CRY_EdDSA_ADD_S_6:
      Cry_EdDSAPointAdditionCalculateA2(ctxPtr, tmp);
      break;

    case CRY_EdDSA_ADD_S_7:
      /* Z3 = tmp6 * tmp3 : Final result */
      Cry_EdDSAPointAdditionCalculateZ3(ctxPtr,
                                        result,
                                        addend1,
                                        tmp
                                       );
      break;

    case CRY_EdDSA_ADD_S_8:
      /* X3 = A * F: tmp4 * tmp6 */
      Cry_EdDSAPointAdditionCalculateAF(ctxPtr,
                                        result,
                                        addend2,
                                        tmp
                                       );
      break;

    case CRY_EdDSA_ADD_S_9:
      /* tmp5 = tmp5 * tmp6 */
      Cry_EdDSAPointAdditionCalculateInterimTmp5(ctxPtr, tmp);
      break;

    case CRY_EdDSA_ADD_S_10:
      /* X3 = X3 * tmp5 - Final result */
      Cry_EdDSAPointAdditionCalculateFinalX3(ctxPtr,
                                             result,
                                             tmp
                                            );

      break;

    case CRY_EdDSA_ADD_S_11:
      /* tmp4 = A * G: tmp4 * tmp3 */
      Cry_EdDSAPointAdditionCalculateAG(ctxPtr, tmp);
      break;

    case CRY_EdDSA_ADD_S_12:
      /* Y3 = tmp4 * tmp5 - Final result */
      if (Cry_LNMultiplyNumbers(result->yValue,
                                &tmp[3U * CRY_EdDSA_TEMP_LEN_WORDS],
                                &tmp[4U * CRY_EdDSA_TEMP_LEN_WORDS],
                                &ctxPtr->LNCtx
                               ) == TRUE
      )
      {
        Cry_EdDSAFastReduction(result->yValue);
        Finished = TRUE;
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }

  return Finished;
}

FUNC(void, CRY_CODE) Cry_EdDSAPointMultiplicationStart
(
   P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
   ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_START;
}

FUNC(boolean, CRY_CODE) Cry_EdDSAPointMultiplication
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2CONST(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) multiplicand,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp

)
{
  boolean Finished;
  Finished = FALSE;

  switch(ctxPtr->MultiplicationState)
  {
    case CRY_EdDSA_MULT_S_START:
      /* first the result shall be set to the point of infinity. */
      result->xValue[0U] = 0U;
      result->xValue[1U] = 0U;
      result->yValue[0U] = 1U;
      result->yValue[1U] = 1U;
      result->zValue[0U] = 1U;
      result->zValue[1U] = 1U;

      ctxPtr->CurrentBit = Cry_LNBitLengthOfNumber(multiplicand);

      ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_LOOP;
      break;

    case CRY_EdDSA_MULT_S_LOOP:
      if(ctxPtr->CurrentBit > 0U)
      {
        ctxPtr->CurrentBit--;
        Cry_EdDSAPointDoublingStart(ctxPtr);
        ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_DOUBLE;
      }
      else
      {
        Finished = TRUE;
      }
      break;

    case CRY_EdDSA_MULT_S_DOUBLE:
      if (Cry_EdDSAPointDoubling(ctxPtr,
                                 result,
                                 result,
                                 tmp
                                ) == TRUE
         )
      {
        if (1U == Cry_LNGetBit(multiplicand, ctxPtr->CurrentBit))
        {

          Cry_EdDSAPointAdditionStart(ctxPtr);
          ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_ADD;
        }
        else
        {
          ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_LOOP;
        }
      }
      break;

    case CRY_EdDSA_MULT_S_ADD:
      if (Cry_EdDSAPointAddition(ctxPtr,
                                 result,
                                 result,
                                 point,
                                 tmp
                                ) == TRUE
         )
      {
        ctxPtr->MultiplicationState = CRY_EdDSA_MULT_S_LOOP;
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }

  return Finished;
}

FUNC(void, CRY_CODE) Cry_EdDSAPointConvertProj2AffStart
(
  P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
  ctxPtr->ConvertProj2AffState = CRY_EdDSA_CONV_S_START;
}

FUNC(boolean, CRY_CODE) Cry_EdDSAPointConvertProj2Aff
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp1,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp2,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp3
)
{
  boolean Finished;

  Finished = FALSE;

  switch(ctxPtr->ConvertProj2AffState)
  {
    case CRY_EdDSA_CONV_S_START:
      /* z-coordinate = 0 then the conversion is the infinity */
      /* CHECK: NOPARSE */
      /* The Proj2Aff function is called just once, at the encoding of A = s * B.
       * As the point to infinity is a neutral point on the eliptic curve and B is
       * given as a "constant" from the algorithm specification we cannot have a point
       * to infinity as an argument. This part is not removed as it might be useful
       * in future extensions. */
      if (point->zValue[0U] == 0U)
      {
        point->xValue[0U] = 0U;
        point->xValue[1U] = 0U;
        point->yValue[0U] = 1U;
        point->yValue[1U] = 1U;

        Finished = TRUE;
      }
      else
      /* CHECK: PARSE */
      {
        Cry_LNInversionStart(&ctxPtr->LNCtx);
        ctxPtr->ConvertProj2AffState = CRY_EdDSA_CONV_S_INVERT;
      }
      break;

    case CRY_EdDSA_CONV_S_INVERT:
      /* Z = Z^(-1) */
      if (Cry_LNInversion(point->zValue,
                          point->zValue,
                          tmp1,
                          tmp2,
                          tmp3,
                          Cry_EdDSAPrime,
                          &ctxPtr->LNCtx
                         ) == TRUE
         )
        {
          Cry_LNMultiplyStart(&ctxPtr->LNCtx);
          ctxPtr->ConvertProj2AffState = CRY_EdDSA_CONV_S_X;
        }
      break;

    case CRY_EdDSA_CONV_S_X:
      /* X = X * Z */
      if (Cry_LNMultiplyNumbers(point->xValue,
                                point->xValue,
                                point->zValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
        {
          Cry_EdDSAFastReduction(point->xValue);
          Cry_LNMultiplyStart(&ctxPtr->LNCtx);
          ctxPtr->ConvertProj2AffState = CRY_EdDSA_CONV_S_Y;
        }
      break;

    case CRY_EdDSA_CONV_S_Y:
      /* Y = Y * Z */
      if (Cry_LNMultiplyNumbers(point->yValue,
                                point->yValue,
                                point->zValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
        {
          Cry_EdDSAFastReduction(point->yValue);
          Finished = TRUE;
        }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }

  return Finished;
}

FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingStart
(
    P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
   ctxPtr->DecodingState = CRY_EdDSA_DEC_S_START;
}

FUNC(boolean, CRY_CODE) Cry_EdDSAPointDecoding
(
  P2VAR(Cry_EdDSACtxType,       AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,     AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,         AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Csm_VerifyResultType,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint8,                  AUTOMATIC, CRY_APPL_DATA) value,
  uint32                                                  valueLength
)
{
  uint8   Sign;
  boolean Finished;

  Finished = FALSE;

  switch (ctxPtr->DecodingState)
  {
    case CRY_EdDSA_DEC_S_START:

      result->zValue[0U] = 1U;
      result->zValue[1U] = 1U;

      /* bit 255 of value is the least significant bit of the x-coordinate */
      ctxPtr->X_0 = (uint8)((uint8)(value[31U] & 0x80U) >> 7U);

      /* y-coordinate is recovered by clearing the bit 255 */
      value[31U] &= (uint8)(~(uint8)((uint8)1U << 7U));

      ctxPtr->DecodingState = CRY_EdDSA_DEC_S_1;
      break;

    case CRY_EdDSA_DEC_S_1:
      /* CHECK: NOPARSE */
      /* This branch is unreachable as we have enough memory allocated in the context
       * to store the byte representation of the LN. */
      if (Cry_LNLEByteArrayToNumber(value,
                                    valueLength,
                                    result->yValue,
                                    sizeof(result->yValue) / sizeof(result->yValue[0U])
                                   ) == E_OK
        )
      /* CHECK: PARSE */
      {
       /* Check if the resulting value is < p */
        if (Cry_LNCompareNumbers(Cry_EdDSAPrime, result->yValue) == CRY_E_LARGER)
        {
          /* The y coordinate is valid */
          Finished = FALSE;
          Cry_LNMultiplyStart(&ctxPtr->LNCtx);

          ctxPtr->DecodingState       = CRY_EdDSA_DEC_S_2;
          ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_INT_2;
        }
        else
        {
          /* The y coordinate is out of range */
          *resultPtr = CSM_E_VER_NOT_OK;

          Finished = TRUE;

          ctxPtr->DecodingState = CRY_EdDSA_DEC_S_START;
        }
      }
      break;

    case CRY_EdDSA_DEC_S_2:
      /* calculation of u * v^3 * (u * v^7)^((p - 5) / 8) */
      Cry_EdDSAPrepareCurveParams(ctxPtr,
                                  result,
                                  tmp
                                 );
      break;

    case CRY_EdDSA_DEC_S_3:
      /* state management for calculation of (u/v) ^ ((p + 3) / 8) */
      Cry_EdDSAPointDecodingStateMngmt(ctxPtr);
      break;

    case CRY_EdDSA_DEC_S_4:
      /* calculate x^2 and reduce, recalculate the root candidate if necessary */
      Cry_EdDSAStatePowerAndReduce(ctxPtr,
                                   &tmp[4U * CRY_EdDSA_TEMP_LEN_WORDS],
                                   &tmp[5U * CRY_EdDSA_TEMP_LEN_WORDS]
                                  );
      break;

    case CRY_EdDSA_DEC_S_5:
      /* calculate x^2 and reduce */
      Cry_EdDSAStateCalculateEQ1(ctxPtr,
                                 &tmp[2U * CRY_EdDSA_TEMP_LEN_WORDS],
                                 &tmp[5U * CRY_EdDSA_TEMP_LEN_WORDS]
                                );
      break;

    case CRY_EdDSA_DEC_S_6:
      /* calculate tmp4 * tmp6 : (u * v^3) * (p - 5) */
      Cry_EdDSAStateCalculateEQ2(ctxPtr,
                                 result,
                                 &tmp[3U * CRY_EdDSA_TEMP_LEN_WORDS],
                                 &tmp[5U * CRY_EdDSA_TEMP_LEN_WORDS]
                                );
      break;

    case CRY_EdDSA_DEC_S_7:
      /* tmp3 = xValue^2 */
      Cry_EdDSAStateCalculateEQ3(ctxPtr,
                                 result,
                                 &tmp[2U * CRY_EdDSA_TEMP_LEN_WORDS]
                                );
      break;

    case CRY_EdDSA_DEC_S_8:
      /* tmp3 = v * xValue^2 */
      Cry_EdDSAStateCalculateEQ4(ctxPtr,
                                 tmp,
                                 resultPtr,
                                 &Finished
                                );
      break;

    case CRY_EdDSA_DEC_S_9:
      /* tmp5 = Primzahl - 1 */
      Cry_EdDSAStateCalculateEQ5(ctxPtr,
                                 result,
                                 &tmp[0U * CRY_EdDSA_TEMP_LEN_WORDS],
                                 &tmp[4U * CRY_EdDSA_TEMP_LEN_WORDS]
                                );
      break;

    case CRY_EdDSA_DEC_S_10:
      Cry_EdDSAPointDecodingExp(ctxPtr, tmp);
      break;

    case CRY_EdDSA_DEC_S_11:
      /* xValue = xValue * (2^tmp5) */
      Cry_EdDSAPointDecodingXValue2(ctxPtr, result, tmp);
      break;

    case CRY_EdDSA_DEC_S_12:
      /* CHECK: NOPARSE */
      /* Unable to cover as we need to fulfill (xValue * (2^(P - 1)) == 0) or
       * ((v * xValue^2 - u) % Prime == 0) in the same time.
       * Nevertheless I think we need to keep this error check. */
      if ((result->xValue[0U] == 0U) && (ctxPtr->X_0 == 1U))
      {
        Finished              = TRUE;
        *resultPtr            = CSM_E_VER_NOT_OK;
        ctxPtr->DecodingState = CRY_EdDSA_DEC_S_START;
      }
      else
      /* CHECK: PARSE */
      {
        Sign = (uint8)(result->xValue[1U] & 0x01U);

        /* x = prime - x */
        if (Sign != ctxPtr->X_0)
        {
          Cry_LNSubtractionModular(result->xValue,
                                   Cry_EdDSAPrime,
                                   result->xValue,
                                   Cry_EdDSAPrime
                                  );
        }

        *resultPtr = CSM_E_VER_OK;

        Finished = TRUE;
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }

  return Finished;
}

FUNC(void, CRY_CODE) Cry_EdDSAFastReduction
(
  P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) value
)
{
  Cry_LNWordType tmp[sizeof(Cry_EdDSAPrime)/sizeof(Cry_EdDSAPrime[0U])];

#if (CPU_TYPE == CPU_TYPE_32)

  Cry_LNWordType temp1;

  /* set the higher positions of the value to zero if necessary */
  for (temp1 = (value[0U] + 1U);
       temp1 < ((2U * (sizeof(Cry_EdDSAPrime) / sizeof(Cry_EdDSAPrime[0U]))) - 1U);
       temp1++
      )
  {
    value[temp1] = 0U;
  }

  Cry_EdDSAFastReductionCompA(tmp, value);

  /* value = A1 + A2 */
  Cry_LNAdditionModular(value, tmp, value, Cry_EdDSAPrime);

  /* value = value + A1 = 2*A1 + A2 */
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);

  /* value = value + A1 = 3*A1 + A2 */
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);

  Cry_EdDSAFastReductionCompB(tmp, &temp1);

  /* value = value + B2 = 3.A1 + A2 + B2 */
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);

  /* tmp = B1 */
  tmp[1U] = temp1;
  tmp[0U] = 1U;

  Cry_LNNormalizeNumber(tmp);

  /* value = 3*A1 + A2 + B2 + 3*B1 */
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);

  /* tmp = B1*(2^4) */
  tmp[1U] = (Cry_LNWordType)(tmp[1U] << 4U);
  tmp[0U] = 1U;

  Cry_LNNormalizeNumber(tmp);

  /* value = value + tmp = 3*A1 + A2 + B2 + 3*B1 + B1*(2^4) */
  Cry_LNAdditionModular(value, value, tmp, Cry_EdDSAPrime);

#elif (CPU_TYPE == CPU_TYPE_16)

#error fixme Cry_EdDSAFastReduction

#else

#error Unknown register width

#endif

}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingStart
(
  P2VAR(Cry_EdDSACtxType, AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
  ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_START;
}

static FUNC(boolean, CRY_CODE) Cry_EdDSAPointDoubling
(
   P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
   P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
   P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
   P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  boolean Finished;
  /* tmp1    Offset where G is stored. */
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp2    Offset where G is stored. */
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp3    Offset where G is stored. */
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp4    Offset where A is stored. */
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp5    Offset where B is stored. */
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  Finished = FALSE;

  switch(ctxPtr->DoublingState)
  {
    case CRY_EdDSA_DOUB_S_START:

       /* if the point is infinity, no calculation is necessary */
       if (Cry_EdDSAProjectivePointOfInfinity(value) == TRUE)
       {
         result->xValue[0U] = 0U;
         result->xValue[1U] = 0U;
         result->yValue[0U] = 1U;
         result->yValue[1U] = 1U;
         result->zValue[0U] = 1U;
         result->zValue[1U] = 1U;

         Finished = TRUE;
       }
       else
       {
         /* tmp1 = X1 + Y1 */
         Cry_LNAdditionModular(&tmp[tmp1],
                               value->xValue,
                               value->yValue,
                               Cry_EdDSAPrime
                              );

         Cry_LNMultiplyStart(&ctxPtr->LNCtx);
         ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_1;
       }
       break;

    case CRY_EdDSA_DOUB_S_1:
      /* tmp2 = X1 * X1 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp2],
                                value->xValue,
                                value->xValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tmp2]);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_2;
      }
      break;

    case CRY_EdDSA_DOUB_S_2:
      /* tmp3 = Y1 * Y1 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp3],
                                value->yValue,
                                value->yValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tmp3]);

        /*
         * a = -1
         * tmp4 = Prime - 1
         */
        (&tmp[tmp5])[0U] = 1U;
        (&tmp[tmp5])[1U] = 1U;

        Cry_LNSubtractionModular(&tmp[tmp4],
                                 Cry_EdDSAPrime,
                                 &tmp[tmp5],
                                 Cry_EdDSAPrime
                                );

        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_3;
      }
      break;

    case CRY_EdDSA_DOUB_S_3:
      /* E : tmp4 = tmp4 * tmp2 */
      /* F = E + D: tmp4 + tmp3 */
      Cry_EdDSAPointDoublingCalculateEF(ctxPtr, tmp);
      break;

    case CRY_EdDSA_DOUB_S_4:
      /* B : tmp1 ^ 2 = (X1 + Y1)^2 */
      Cry_EdDSAPointDoublingCalculateB(ctxPtr, tmp);
      break;

    case CRY_EdDSA_DOUB_S_5:
      /* Y3 = F * (E - D): tmp5 * tmp4 */
      if (Cry_LNMultiplyNumbers(result->yValue,
                                &tmp[tmp5],
                                &tmp[tmp4],
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(result->yValue);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_6;
      }
      break;

    case CRY_EdDSA_DOUB_S_6:
      /* H: tmp4 = Z1 * Z1 */
      Cry_EdDSAPointDoublingCalculateH(ctxPtr,
                                       value,
                                       tmp
                                      );
      break;

    case CRY_EdDSA_DOUB_S_7:
      /* Z3 = F * J: tmp5 * tmp4 - Final result */
      Cry_EdDSAPointDoublingCalculateZ3(ctxPtr,
                                        result,
                                        tmp
                                       );
      break;

    case CRY_EdDSA_DOUB_S_8:
      /* X3 = tmp1 * J - Final result */
      if (Cry_LNMultiplyNumbers(result->xValue,
                                &tmp[tmp1],
                                &tmp[tmp4],
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(result->xValue);
        Finished = TRUE;
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        Finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
   }

   return Finished;
}

static FUNC(boolean, CRY_CODE) Cry_EdDSAProjectivePointOfInfinity
(
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point
)
{
  boolean result;

  /* In projective coordinates the point of infinity corresponds to
   * the point (X : Y : Z) = (0 : 1 : 1).
   */
  if ((0U                        == point->xValue[0U]        ) &&
      ((1U == point->yValue[0U]) && (1U == point->yValue[1U])) &&
      ((1U == point->zValue[0U]) && (1U == point->zValue[1U]))
     )
  {
    result = TRUE;
  }
  else
  {
    result = FALSE;
  }

  return result;
}

static FUNC(void, CRY_CODE) Cry_EdDSAStatePowerAndReduce
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) checkHighestBit,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) valueToDouble
)
{
  /* calculate x^2 */
  if (Cry_LNMultiplyNumbers(valueToDouble,
                            valueToDouble,
                            valueToDouble,
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(valueToDouble);

    if ((Cry_LNWordType)1U == Cry_LNGetBit(checkHighestBit, ((&ctxPtr->LNCtx)->Bits)))
    {
      Cry_LNMultiplyStart(&ctxPtr->LNCtx);
      ctxPtr->DecodingState = CRY_EdDSA_DEC_S_5;
    }
    else
    {
      ctxPtr->DecodingState = CRY_EdDSA_DEC_S_3;
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ1
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) base,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) result
)
{
  if (Cry_LNMultiplyNumbers(result,
                            result,
                            base,
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(result);

    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_3;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ2
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) multiplicand,
  P2CONST(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) multiplicator
)
{
  if (Cry_LNMultiplyNumbers(point->xValue,
                            multiplicand,
                            multiplicator,
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(point->xValue);

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_7;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ3
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) squareOfX
)
{
  if (Cry_LNMultiplyNumbers(squareOfX,
                            point->xValue,
                            point->xValue,
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(squareOfX);

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_8;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ4
(
  P2VAR(Cry_EdDSACtxType,       AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,         AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Csm_VerifyResultType,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(boolean,                AUTOMATIC, CRY_APPL_DATA) finished
)
{
  /* vValue    Offset where v is stored. */
  const uint32 vValue = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* uValue    Offset where u is stored. */
  const uint32 uValue = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* squareOfX Offset where the result of xValue^2 is stored. */
  const uint32 squareOfX = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* value1    Offset where the result of (v * xValue^2 - u) % Prime is stored. */
  const uint32 value1 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* value2    Offset where the result of (v * xValue^2 + u) % Prime is stored. */
  const uint32 value2 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* calculate v * squareOfX : v* xValue^2 */
  if (Cry_LNMultiplyNumbers(&tmp[squareOfX],
                            &tmp[vValue],
                            &tmp[squareOfX],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(&tmp[squareOfX]);

    /* value1 = (v * xValue^2 - u) % Prime */
    Cry_LNSubtractionModular(&tmp[value1],
                             &tmp[squareOfX],
                             &tmp[uValue],
                             Cry_EdDSAPrime
                            );

    /* value2 = (v * xValue^2 + u) % Prime */
    Cry_LNAdditionModular(&tmp[value2],
                          &tmp[squareOfX],
                          &tmp[uValue],
                          Cry_EdDSAPrime
                         );

    /* v * xValue^2 == u */
    if((&tmp[value1])[0U] == 0U)
    {
      *resultPtr = CSM_E_VER_OK;

      /* CHECK: NOPARSE */
      /* Unable to cover as we need to fulfill both ((v * xValue^2 + u) % Prime == 0) and
       * ((v * xValue^2 - u) % Prime == 0) in the same time.
       * Nevertheless I think we need to keep this error check. */
      if((&tmp[value2])[0U] == 0U)
      {
        /* invalid point, exit with CSM_E_VER_NOT_OK. */
        *finished             = TRUE;
        *resultPtr            = CSM_E_VER_NOT_OK;
        ctxPtr->DecodingState = CRY_EdDSA_DEC_S_START;
      }
      /* CHECK: PARSE */

      /* check the sign */
      ctxPtr->DecodingState = CRY_EdDSA_DEC_S_12;
    }
    else
    {
      if ((&tmp[value2])[0U] == 0U)
      {
        /* calculate x = x * 2^((p-1)/4) */
        ctxPtr->DecodingState = CRY_EdDSA_DEC_S_9;
        *resultPtr            = CSM_E_VER_OK;
      }
      else
      {
        /* invalid point, exit with CSM_E_VER_NOT_OK. */
        *finished             = TRUE;
        *resultPtr            = CSM_E_VER_NOT_OK;
        ctxPtr->DecodingState = CRY_EdDSA_DEC_S_START;
      }
    }
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAStateCalculateEQ5
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) point,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) base,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) exponent
)
{
  uint32  i;

  Cry_LNSubtractionModular(exponent,
                           Cry_EdDSAPrime,
                           point->zValue,
                           Cry_EdDSAPrime
                          );

  /* exponent = exponent / 4 */
  for(i = 1U ; i < exponent[0U]; i++)
  {
    exponent[i] = (Cry_LNWordType)(exponent[i] >> 2U) | (Cry_LNWordType)(exponent[i+1U] << 30U);
  }

  exponent[exponent[0U]] = (Cry_LNWordType)(exponent[exponent[0U]] >> 2U);

  /*tmp6 = 2^exponent */
  Cry_LNModExpStart(&ctxPtr->LNCtx);

  base[0U] = 1U;
  base[1U] = 2U;

  ctxPtr->DecodingState = CRY_EdDSA_DEC_S_10;
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParams
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  uint32  i;
  const uint32 tempIndex0 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex1 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex2 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex3 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex4 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex5 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  switch (ctxPtr->DecodingParamsState)
  {
    case CRY_EdDSA_DEC_S_INT_2:
      /* tmp2 = u = y^2 - 1 */
      Cry_EdDSAPrepareCurveParamsY2(ctxPtr, result, tmp);
      break;

    case CRY_EdDSA_DEC_S_P_3:
      /* tmp1 = v = d * (y^2) + 1 */
      Cry_EdDSAPrepareCurveParamsDY2(ctxPtr, result, tmp);
      break;

    case CRY_EdDSA_DEC_S_P_4:
      /* tmp3 = tmp1^2 : v^2 */
      Cry_EdDSAPrepareCurveParamsV2(ctxPtr, tmp);
      break;

    case CRY_EdDSA_DEC_S_P_5:
      /* tmp3 = tmp1^3 : v^3 */
      Cry_EdDSAPrepareCurveParamsV3(ctxPtr, tmp);
      break;

    case CRY_EdDSA_DEC_S_P_6:
      /* tmp4 = tmp2 * tmp3 : u * v^3  */
      if (Cry_LNMultiplyNumbers(&tmp[tempIndex3],
                                &tmp[tempIndex1],
                                &tmp[tempIndex2],
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tempIndex3]);

        (&tmp[tempIndex4])[0U] = 1U;
        (&tmp[tempIndex4])[1U] = 7U;

        Cry_LNModExpStart(&ctxPtr->LNCtx);
        ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_7;
      }
      break;

    case CRY_EdDSA_DEC_S_P_7:
      /* tmp3 = tmp1^7 : v^7 */
      if (Cry_LNModExp(&tmp[tempIndex2],
                       &tmp[tempIndex0],
                       Cry_EdDSAPrime,
                       &tmp[tempIndex4],
                       &ctxPtr->LNCtx
                      ) == TRUE
        )
      {
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_8;
      }
      break;

    case CRY_EdDSA_DEC_S_P_8:
      /* tmp3 = tmp2 * tmp1^7 : u * v^7  */
      if (Cry_LNMultiplyNumbers(&tmp[tempIndex2],
                                &tmp[tempIndex1],
                                &tmp[tempIndex2],
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tempIndex2]);

        (&tmp[tempIndex5])[0U] = 1U;
        (&tmp[tempIndex5])[1U] = 5U;

        /* tmp5 = primeModulus - 5 */
        Cry_LNSubtractionModular(&tmp[tempIndex4],
                                 Cry_EdDSAPrime,
                                 &tmp[tempIndex5],
                                 Cry_EdDSAPrime
                                );

        /* tmp5 = tmp5 / 8 : (p - 5) / 8 */
        for(i = 1U; i < (&tmp[tempIndex4])[0U]; i++)
        {
          (&tmp[tempIndex4])[i] = (Cry_LNWordType)((&tmp[tempIndex4])[i     ] >> 3U) |
                                  (Cry_LNWordType)((&tmp[tempIndex4])[i + 1U] << 29U);
        }
        (&tmp[tempIndex4])[(&tmp[tempIndex4])[0U]] =
                                 (Cry_LNWordType)((&tmp[tempIndex4])[(&tmp[tempIndex4])[0U]] >> 3U);

        (&ctxPtr->LNCtx)->Bits = Cry_LNBitLengthOfNumber(&tmp[tempIndex4]);

        /* tmp6 = result */
        (&tmp[tempIndex5])[0U]      = 1U;
        (&tmp[tempIndex5])[1U]      = 1U;
        ctxPtr->DecodingState       = CRY_EdDSA_DEC_S_3;
        ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_INT_2;
      }
      break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    default:
      {
        break;
      }
    /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCheckInfinity
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(boolean,              AUTOMATIC, CRY_APPL_DATA) finished
)
{
  Cry_LNWordType i;

  /* if the addend1 is the point of infinity, the result is the addend2 */
  if (TRUE == Cry_EdDSAProjectivePointOfInfinity(addend1))
  {
     for(i = 0U; i <= addend2->xValue[0U]; i++)
     {
       result->xValue[i] = addend2->xValue[i];
     }

     for(i = 0U; i <= addend2->yValue[0U]; i++)
     {
       result->yValue[i] = addend2->yValue[i];
     }

     for(i = 0U; i <= addend2->zValue[0U]; i++)
     {
       result->zValue[i] = addend2->zValue[i];
     }

     *finished = TRUE;
  }
  /* if the addend2 is the point of infinity, the result is the addend1 */
  else if (TRUE == Cry_EdDSAProjectivePointOfInfinity(addend2))
  {
     for(i = 0U; i <= addend1->xValue[0U]; i++)
     {
       result->xValue[i] = addend1->xValue[i];
     }

     for(i = 0U; i <= addend1->yValue[0U]; i++)
     {
       result->yValue[i] = addend1->yValue[i];
     }

     for(i = 0U; i <= addend1->zValue[0U]; i++)
     {
       result->zValue[i] = addend1->zValue[i];
     }

     *finished = TRUE;
  }
  else
  {
      Cry_LNMultiplyStart(&ctxPtr->LNCtx);
      ctxPtr->AdditionState = CRY_EdDSA_ADD_S_CDE;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateA2
(
  P2VAR(Cry_EdDSACtxType,   AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,     AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  /* tmp3    Offset where G is stored. */
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp4    Offset where A is stored. */
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp5    Offset where B is stored. */
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp6    Offset where F is stored. */
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* B = A^2: tmp5 = tmp4 * tmp4 */
  if (Cry_LNMultiplyNumbers(&tmp[tmp5],
                            &tmp[tmp4],
                            &tmp[tmp4],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(&tmp[tmp5]);

    /* F: tmp6 = tmp5 - tmp3 */
    Cry_LNSubtractionModular(&tmp[tmp6],
                             &tmp[tmp5],
                             &tmp[tmp3],
                             Cry_EdDSAPrime
                            );

    /* G: tmp3 = tmp5 + tmp3 */
    Cry_LNAdditionModular(&tmp[tmp3],
                          &tmp[tmp5],
                          &tmp[tmp3],
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_7;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateZ3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* Z3 = tmp6 * tmp3 : Final result */
  if (Cry_LNMultiplyNumbers(result->zValue,
                            &tmp[tmp6],
                            &tmp[tmp3],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(result->zValue);

    /* tmp5 = X1 + Y1 */
    Cry_LNAdditionModular(&tmp[tmp5],
                          addend1->xValue,
                          addend1->yValue,
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_8;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateAG
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(&tmp[tmp4],
                            &tmp[tmp4],
                            &tmp[tmp3],
                            &ctxPtr->LNCtx
                           ) == TRUE
  )
  {
    Cry_EdDSAFastReduction(&tmp[tmp4]);
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_12;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateInterimTmp5
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* tmp5 = tmp5 * tmp6 */
  if (Cry_LNMultiplyNumbers(&tmp[tmp5],
                            &tmp[tmp5],
                            &tmp[tmp6],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(&tmp[tmp5]);

    /* tmp5 = tmp5 - C */
    Cry_LNSubtractionModular(&tmp[tmp5],
                             &tmp[tmp5],
                             &tmp[tmp1],
                             Cry_EdDSAPrime
                            );

    /* tmp5 = tmp5 - tmp2 */
    Cry_LNSubtractionModular(&tmp[tmp5],
                             &tmp[tmp5],
                             &tmp[tmp2],
                             Cry_EdDSAPrime
                            );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_10;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateAF
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(result->xValue,
                            &tmp[tmp4],
                            &tmp[tmp6],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(result->xValue);

    /* tmp6 = X2 + Y2 */
    Cry_LNAdditionModular(&tmp[tmp6],
                          addend2->xValue,
                          addend2->yValue,
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_9;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateFinalX3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(result->xValue,
                            result->xValue,
                            &tmp[tmp5],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(result->xValue);

    /* tmp5 = D + C: tmp2 + tmp1 */
    Cry_LNAdditionModular(&tmp[tmp5],
                          &tmp[tmp2],
                          &tmp[tmp1],
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->AdditionState = CRY_EdDSA_ADD_S_11;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateZ3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(result->zValue,
                            &tmp[tmp5],
                            &tmp[tmp4],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {

    Cry_EdDSAFastReduction(result->zValue);

    /* tmp1 = B - C */
    Cry_LNSubtractionModular(&tmp[tmp1],
                             &tmp[tmp1],
                             &tmp[tmp2],
                             Cry_EdDSAPrime
                            );

    /* tmp1 = tmp1 - D */
    Cry_LNSubtractionModular(&tmp[tmp1],
                             &tmp[tmp1],
                             &tmp[tmp3],
                             Cry_EdDSAPrime
                            );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_8;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateH
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) value,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(&tmp[tmp4],
                            value->zValue,
                            value->zValue,
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(&tmp[tmp4]);

    /* tmp4 = 2 * H */
    Cry_LNAdditionModular(&tmp[tmp4],
                          &tmp[tmp4],
                          &tmp[tmp4],
                          Cry_EdDSAPrime
                         );

    /* J: tmp4 = tmp5 - tmp4 */
    Cry_LNSubtractionModular(&tmp[tmp4],
                             &tmp[tmp5],
                             &tmp[tmp4],
                             Cry_EdDSAPrime
                            );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_7;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateB
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);

  if(Cry_LNMultiplyNumbers(&tmp[tmp1], &tmp[tmp1], &tmp[tmp1], &ctxPtr->LNCtx) == TRUE)
  {
    Cry_EdDSAFastReduction(&tmp[tmp1]);

    /* tmp4 = E - D: tmp4 - tmp3 */
    Cry_LNSubtractionModular(&tmp[tmp4],
                             &tmp[tmp4],
                             &tmp[tmp3],
                             Cry_EdDSAPrime
                            );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_5;
  }

}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDoublingCalculateEF
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* E : tmp4 = tmp4 * tmp2 */
  if(Cry_LNMultiplyNumbers(&tmp[tmp4], &tmp[tmp4], &tmp[tmp2], &ctxPtr->LNCtx) == TRUE)
  {
    Cry_EdDSAFastReduction(&tmp[tmp4]);

    /* F = E + D: tmp4 + tmp3 */
    Cry_LNAdditionModular(&tmp[tmp5],
                          &tmp[tmp4],
                          &tmp[tmp3],
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DoublingState = CRY_EdDSA_DOUB_S_4;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingXValue2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_EdDSAPointType,   AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNMultiplyNumbers(result->xValue,
                            result->xValue,
                            &tmp[tmp6],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(result->xValue);

    /* check the sign */
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_12;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingExp
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tmp6 = (5U * CRY_EdDSA_TEMP_LEN_WORDS);

  if (Cry_LNModExp(&tmp[tmp6],
                   &tmp[tmp1],
                   Cry_EdDSAPrime,
                   &tmp[tmp5],
                   &ctxPtr->LNCtx
                  ) == TRUE
      )
  {
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_11;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsY2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tempIndex0 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex1 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* tmp1 = y^2 */
  if(Cry_LNMultiplyNumbers(&tmp[tempIndex0],
                           result->yValue,
                           result->yValue,
                           &ctxPtr->LNCtx
                          ) == TRUE)
  {
    Cry_EdDSAFastReduction(&tmp[tempIndex0]);

    /* tmp2: (y^2) - 1 = tmp1 - 1 */
    Cry_LNSubtractionModular(&tmp[tempIndex1],
                             &tmp[tempIndex0],
                             result->zValue,
                             Cry_EdDSAPrime
                            );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_3;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsDY2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) result,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tempIndex0 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* tmp1 = d * (y^2) */
  if (Cry_LNMultiplyNumbers(&tmp[tempIndex0],
                            Cry_EdDSACurveInfo.dValue,
                            &tmp[tempIndex0],
                            &ctxPtr->LNCtx
                           ) == TRUE
  )
  {
    Cry_EdDSAFastReduction(&tmp[tempIndex0]);

    /* a = -1 : tmp1 = (d * (y^2)) + 1 */
    Cry_LNAdditionModular(&tmp[tempIndex0],
                          &tmp[tempIndex0],
                          result->zValue,
                          Cry_EdDSAPrime
                         );

    Cry_LNMultiplyStart(&ctxPtr->LNCtx);

    ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_4;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsV2
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tempIndex0 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex2 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* tmp3 = tmp1^2 : v^2 */
  if (Cry_LNMultiplyNumbers(&tmp[tempIndex2],
                            &tmp[tempIndex0],
                            &tmp[tempIndex0],
                            &ctxPtr->LNCtx
                           ) == TRUE
     )
  {
    Cry_EdDSAFastReduction(&tmp[tempIndex2]);
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_5;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPrepareCurveParamsV3
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  const uint32 tempIndex0 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  const uint32 tempIndex2 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);

  /* tmp3 = tmp1^3 : v^3 */
  if (Cry_LNMultiplyNumbers(&tmp[tempIndex2],
                            &tmp[tempIndex2],
                            &tmp[tempIndex0],
                            &ctxPtr->LNCtx
                          ) == TRUE
    )
  {
    Cry_EdDSAFastReduction(&tmp[tempIndex2]);
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingParamsState = CRY_EdDSA_DEC_S_P_6;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointDecodingStateMngmt
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr
)
{
  /* state management for calculation of (u/v) ^ ((p + 3) / 8) */
  if (((&ctxPtr->LNCtx)->Bits) > (Cry_LNWordType)0U)
  {
    --(&ctxPtr->LNCtx)->Bits;
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_4;
  }
  else
  {
    Cry_LNMultiplyStart(&ctxPtr->LNCtx);
    ctxPtr->DecodingState = CRY_EdDSA_DEC_S_6;
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAPointAdditionCalculateCDE
(
  P2VAR(Cry_EdDSACtxType,     AUTOMATIC, CRY_APPL_DATA) ctxPtr,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend1,
  P2CONST(Cry_EdDSAPointType, AUTOMATIC, CRY_APPL_DATA) addend2,
  P2VAR(Cry_LNWordType,       AUTOMATIC, CRY_APPL_DATA) tmp
)
{
  /* tmp1    Offset where C is stored. */
  const uint32 tmp1 = (0U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp2    Offset where D is stored. */
  const uint32 tmp2 = (1U * CRY_EdDSA_TEMP_LEN_WORDS);
  /* tmp3    Offset where E is stored. */
  const uint32 tmp3 = (2U * CRY_EdDSA_TEMP_LEN_WORDS);

  switch (ctxPtr->AdditionCDEState)
  {
    case CRY_EdDSA_ADD_S_1:
      /* C: tmp1 = X1 * X2 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp1],
                                addend1->xValue,
                                addend2->xValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tmp1]);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->AdditionCDEState = CRY_EdDSA_ADD_S_2;
      }
      break;

    case CRY_EdDSA_ADD_S_2:
      /* D: tmp2 = Y1 * Y2 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp2],
                                addend1->yValue,
                                addend2->yValue,
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tmp2]);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->AdditionCDEState = CRY_EdDSA_ADD_S_3;
      }
      break;

    case CRY_EdDSA_ADD_S_3:
      /* E: tmp3 = dValue * tmp1 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp3],
                                Cry_EdDSACurveInfo.dValue,
                                &tmp[tmp1],
                                &ctxPtr->LNCtx
                               ) == TRUE
         )
      {
        Cry_EdDSAFastReduction(&tmp[tmp3]);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->AdditionCDEState = CRY_EdDSA_ADD_S_4;
      }
      break;

    case CRY_EdDSA_ADD_S_4:
      /* E: tmp3 = tmp3 * tmp2 */
      if (Cry_LNMultiplyNumbers(&tmp[tmp3],
                                &tmp[tmp3],
                                &tmp[tmp2],
                                &ctxPtr->LNCtx
                               ) == TRUE
      )
      {
        Cry_EdDSAFastReduction(&tmp[tmp3]);
        Cry_LNMultiplyStart(&ctxPtr->LNCtx);
        ctxPtr->AdditionState    = CRY_EdDSA_ADD_S_5;
        ctxPtr->AdditionCDEState = CRY_EdDSA_ADD_S_1;
      }
      break;

      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
      default:
      {
        break;
      }
      /* CHECK: PARSE */
  }
}

static FUNC(void, CRY_CODE) Cry_EdDSAFastReductionCompA
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp,
    P2VAR(Cry_LNWordType, AUTOMATIC, CRY_APPL_DATA) value
)
{
    /* A1, the last 8 items of value */
    tmp[8U] = (Cry_LNWordType)(value[16U] << 1U) | (Cry_LNWordType)(value[15U] >> 31U);
    tmp[7U] = (Cry_LNWordType)(value[15U] << 1U) | (Cry_LNWordType)(value[14U] >> 31U);
    tmp[6U] = (Cry_LNWordType)(value[14U] << 1U) | (Cry_LNWordType)(value[13U] >> 31U);
    tmp[5U] = (Cry_LNWordType)(value[13U] << 1U) | (Cry_LNWordType)(value[12U] >> 31U);
    tmp[4U] = (Cry_LNWordType)(value[12U] << 1U) | (Cry_LNWordType)(value[11U] >> 31U);
    tmp[3U] = (Cry_LNWordType)(value[11U] << 1U) | (Cry_LNWordType)(value[10U] >> 31U);
    tmp[2U] = (Cry_LNWordType)(value[10U] << 1U) | (Cry_LNWordType)(value[9U]  >> 31U);
    tmp[1U] = (Cry_LNWordType)(value[9U]  << 1U) | (Cry_LNWordType)(value[8U]  >> 31U);
    tmp[0U] = (Cry_LNWordType)8U;             /* the size of the number */

    /* normalize tmp */
    Cry_LNNormalizeNumber(tmp);

    /* value = A2 */
    value[0U]  = 8U;
    value[8U] &= (Cry_LNWordType)0x7fffffffUL;

    /* normalize value */
    Cry_LNNormalizeNumber(value);
}

static FUNC(void, CRY_CODE) Cry_EdDSAFastReductionCompB
(
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) tmp,
  P2VAR(Cry_LNWordType,   AUTOMATIC, CRY_APPL_DATA) temp1
)
{
    /* Store for B1 : 4-bits */
    *temp1 = tmp[8U] >> 27U;

    /* tmp = B2 */
    tmp[8U] = (Cry_LNWordType)(tmp[8U] << 4U) | (Cry_LNWordType)(tmp[7U] >> 28U);
    tmp[7U] = (Cry_LNWordType)(tmp[7U] << 4U) | (Cry_LNWordType)(tmp[6U] >> 28U);
    tmp[6U] = (Cry_LNWordType)(tmp[6U] << 4U) | (Cry_LNWordType)(tmp[5U] >> 28U);
    tmp[5U] = (Cry_LNWordType)(tmp[5U] << 4U) | (Cry_LNWordType)(tmp[4U] >> 28U);
    tmp[4U] = (Cry_LNWordType)(tmp[4U] << 4U) | (Cry_LNWordType)(tmp[3U] >> 28U);
    tmp[3U] = (Cry_LNWordType)(tmp[3U] << 4U) | (Cry_LNWordType)(tmp[2U] >> 28U);
    tmp[2U] = (Cry_LNWordType)(tmp[2U] << 4U) | (Cry_LNWordType)(tmp[1U] >> 28U);
    tmp[1U] = (Cry_LNWordType)(tmp[1U] << 4U);
    tmp[0U] = 8U;

    tmp[8U] &= (Cry_LNWordType)0x7fffffffUL;

    Cry_LNNormalizeNumber(tmp);
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>


#else /* (CRY_EdDSA_ENABLED == STD_ON) */

/** \brief Dummy definition preventing this file from being empty */
typedef void CryPrvntEmptyTranslationUnit_t;

#endif /* (CRY_ECC_P_ENABLED == STD_ON) */
